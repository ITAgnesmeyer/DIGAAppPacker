// ----------------------------------------------------------------------------------------------
// Copyright (c) Mattias Högström.
// ----------------------------------------------------------------------------------------------
// This source code is subject to terms and conditions of the Microsoft Public License. A 
// copy of the license can be found in the License.html file at the root of this distribution. 
// If you cannot locate the Microsoft Public License, please send an email to 
// dlr@microsoft.com. By using this source code in any fashion, you are agreeing to be bound 
// by the terms of the Microsoft Public License.
// ----------------------------------------------------------------------------------------------
// You must not remove this notice, or any other, from this software.
// ----------------------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Security.Policy;
using System.Text.RegularExpressions;
using System.Threading;

namespace SampleAppDomainManager
{
    [Guid("0C19678A-CE6C-487B-AD36-0A8B7D7CC035")]
    [ComVisible(true)]
    public sealed class CustomAppDomainManager:AppDomainManager, ICustomAppDomainManager,IDisposable
    {

        private bool _lastResult;
        private string _lastMessage;

        public CustomAppDomainManager()
        {
            this.AssamblyList = new List<Assembly>();

            Console.WriteLine("*** Instantiated CustomAppDomainManager");
        }

        private List<Assembly> AssamblyList { get; }

        public override void InitializeNewDomain(AppDomainSetup appDomainInfo)
        {
            Console.WriteLine("*** InitializeNewDomain");

            this.InitializationFlags = AppDomainManagerInitializationOptions.RegisterWithHost;
        }


        public void Run(string assemblyFilename, string friendlyName)
        {
            this._lastResult = true;
            this._lastMessage = string.Empty;

            if (!File.Exists(assemblyFilename))
            {
                const string message = "Application cannot be found";
                Trace.WriteLine(message);
                Console.Error.WriteLine(message);
                this._lastMessage = message;
                this._lastResult = false;
                return;
            }

            AppDomain ad = null;
            try
            {
                
                ad = AppDomain.CreateDomain(friendlyName);
                //ad = AppDomain.CreateDomain(barray);
                var exitCode = ad.ExecuteAssembly(assemblyFilename);
                Trace.WriteLine(string.Format("ExitCode={0}", exitCode));
            }
            catch (Exception)
            {
                var message = string.Format("Unhandled Exception in {0}",
                    Path.GetFileNameWithoutExtension(assemblyFilename));
                Console.Error.WriteLine(message);
                this._lastMessage = message;
                this._lastResult = false;
            }
            finally
            {
                if (ad != null)
                {
                    AppDomain.Unload(ad);
                    Console.WriteLine("*** Unloaded AppDomain {0}", friendlyName);
                }
            }
        }

        public void Run(byte[] assembylBytes, string friendlyName)
        {
            AppDomain ad = null;
            this._lastResult = true;
            this._lastMessage = string.Empty;
            try
            {
                if (!LoadAssemblyByteInCurrentDomain(assembylBytes))
                {
                    Console.WriteLine("Could not load Assembyl" + friendlyName);
                    this._lastResult = false;
                    this._lastMessage = "Could not load Assembyl" + friendlyName;
                    Console.WriteLine(this._lastMessage);
                    return;
                }

                var assembly= this.AssamblyList.FirstOrDefault(x => x.FullName.StartsWith(friendlyName));
                if (assembly == null)
                {
                    this._lastResult = false;
                    this._lastMessage = "Could not resolve Assembyl by Name";
                    Console.WriteLine(this.LastMessage);
                    return;
                }
                
                Console.WriteLine("Try To Find Entry Point");
                CultureInfo newCulture = CultureInfo.CreateSpecificCulture("de-DE");
                Thread.CurrentThread.CurrentUICulture = newCulture;
                var entryPoint = assembly.EntryPoint;
                //var comandArgs = new string[0];
                //var result = entryPoint.Invoke(null, new object[] {comandArgs});
                object[] args;
                if (entryPoint.GetParameters().Length > 0)
                {
                    var commandArgs = new string[0];
                    args = new object[] {commandArgs};
                }
                else
                {
                    args = new object[] { };
                }

                object result = null;
               
                result = entryPoint.Invoke(null, BindingFlags.InvokeMethod | BindingFlags.Static, null, args, CultureInfo.CurrentCulture);
               
                //result = entryPoint.Invoke(null,BindingFlags.InvokeMethod | BindingFlags.Static,null, args ,CultureInfo.CurrentCulture);

                Trace.WriteLine( $"ExitCode={result}");
            }
            catch (Exception ex)
            {
                this._lastResult = false;
                var message = $"Unhandled Exception in {friendlyName}";
                this._lastMessage = message;
                Console.Error.WriteLine(message);
                message = ex.ToString();
                this._lastMessage += message;
                Console.Error.WriteLine(message);
            }
            finally
            {
                if (ad != null)
                {
                    AppDomain.Unload(ad);
                    Console.WriteLine("*** Unloaded AppDomain {0}", friendlyName);
                }
            }
        }

        public bool LoadAssemblyInCurrentDomain(string assemblyName)
        {
            this._lastResult = true;
            Console.WriteLine("versuche Assembly zu laden!");
            if (!File.Exists(assemblyName))
            {
                string message = $"Error: File does not exist!==>{assemblyName}";
                Console.Error.WriteLine(message);
                Console.WriteLine(message);
                this._lastMessage = message;
                return false;
            }

            try
            {
                AppDomain.CurrentDomain.AssemblyLoad += OnAssemblyLoad;
                AppDomain.CurrentDomain.AssemblyResolve += OnAssemblyResolve;

                var ass = Assembly.LoadFile(assemblyName);
                this.AssamblyList.Add(ass);
                return true;
            }
            catch (Exception ex)
            {
                string message = $"Error:{ex.Message}";
                Console.Error.WriteLine(message);
                Console.WriteLine(message);
                this._lastMessage = message;
                this._lastResult = false;
                return false;
            }
        }

        public object CreateObjectFromDomain(string typeName)
        {
            var nameStrings = typeName.Split('.');
            if (nameStrings.Length < 2)
                throw new MissingFieldException("parameter not Correkt!");

            var assName = nameStrings[0];
            var tName = nameStrings[1];

            var assList = AppDomain.CurrentDomain.GetAssemblies().ToList();
            var finder = from a in assList where a.FullName.StartsWith(assName) select a;
            return (from item in finder from typeItem in item.GetTypes().ToList() where typeItem.Name == tName select Activator.CreateInstance(typeItem, new object[] {})).FirstOrDefault();
        }

        public string GetTypeName(object obj)
        {
            string retString;
            if (obj == null)
                throw new NullReferenceException("No given Name!");

            var s = obj as string;
            if (s != null)
            {
                retString = s;
                var assList = AppDomain.CurrentDomain.GetAssemblies().ToList();
                if (assList.Any(x => x.GetName().Name == retString))
                {
                    var foundAss = assList.FirstOrDefault(x => x.GetName().Name == retString);

                    if (foundAss != null)
                        return foundAss.FullName;
                    return string.Empty;
                }
                return string.Empty;
            }

            return obj.GetType().FullName;
        }

        public override AppDomain CreateDomain(string friendlyName, Evidence securityInfo, AppDomainSetup appDomainInfo)
        {
            var appDomain = base.CreateDomain(friendlyName, securityInfo, appDomainInfo);
            Console.WriteLine("*** Created AppDomain {0}", friendlyName);
            return appDomain;
        }

        private Assembly OnAssemblyResolve(object sender, ResolveEventArgs args)
        {
            Console.WriteLine("Versuche zu Laden:" + args.Name);
            return args.RequestingAssembly;
        }

        private void OnAssemblyLoad(object sender, AssemblyLoadEventArgs args)
        {
            Console.WriteLine("Load:" + args.LoadedAssembly.FullName);
        }

        #region IDisposable Support
        private bool _disposedValue = false; // Dient zur Erkennung redundanter Aufrufe.
   

        void Dispose(bool disposing)
        {
            if (!_disposedValue)
            {
                if (disposing)
                {
                    // TODO: verwalteten Zustand (verwaltete Objekte) entsorgen.
                    this.AssamblyList?.Clear();
                    AppDomain.Unload(AppDomain.CurrentDomain);
                }

                // TODO: nicht verwaltete Ressourcen (nicht verwaltete Objekte) freigeben und Finalizer weiter unten überschreiben.
                // TODO: große Felder auf Null setzen.

                this._disposedValue = true;
            }
        }

        // TODO: Finalizer nur überschreiben, wenn Dispose(bool disposing) weiter oben Code für die Freigabe nicht verwalteter Ressourcen enthält.
        // ~CustomAppDomainManager() {
        //   // Ändern Sie diesen Code nicht. Fügen Sie Bereinigungscode in Dispose(bool disposing) weiter oben ein.
        //   Dispose(false);
        // }

        // Dieser Code wird hinzugefügt, um das Dispose-Muster richtig zu implementieren.
        public void Dispose()
        {
            // Ändern Sie diesen Code nicht. Fügen Sie Bereinigungscode in Dispose(bool disposing) weiter oben ein.
            Dispose(true);
            // TODO: Auskommentierung der folgenden Zeile aufheben, wenn der Finalizer weiter oben überschrieben wird.
            // GC.SuppressFinalize(this);
        }

        public bool LoadAssemblyByteInCurrentDomain(byte[] assemblyBytes)
        {
            this._lastResult = true;
            this._lastMessage = string.Empty;
            try
            {
                Console.WriteLine("Add Events!");
                AppDomain.CurrentDomain.AssemblyLoad += OnAssemblyLoad;
                AppDomain.CurrentDomain.AssemblyResolve += OnAssemblyResolve;
                Console.WriteLine("Events Added!");
                Console.WriteLine("Try To Load Assembyl!");
               
                var ass = Assembly.Load(assemblyBytes);
                Console.WriteLine("Assembly loaded!");
                this.AssamblyList.Add(ass);
                return true;
            }
            catch (Exception ex)
            {
                string message = $"Error:{ex.Message}";
                Console.Error.WriteLine(message);
                Console.WriteLine(message);
                this._lastMessage = message;
                this._lastResult = false;
                return false;
            }
        }

        public bool LastResult
        {
            get { return this._lastResult; }
        }

        public string LastMessage
        {
            get { return this._lastMessage; }
        }

        #endregion
    }
}