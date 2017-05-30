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
using System.Runtime.InteropServices;

namespace SampleAppDomainManager
{
    [GuidAttribute("8331B385-9344-4A36-BC0A-BEA67D17BC70"), ComVisible(true)]
    public interface ICustomAppDomainManager
    {
        void InitializeNewDomain(AppDomainSetup appDomainInfo);

        void Run(string assemblyFilename, string friendlyName);

        void Run(byte[] assembylBytes, string friendlyName);

        bool LoadAssemblyInCurrentDomain(string assemblyName);

        object CreateObjectFromDomain(string typeName);

        string GetTypeName(object obj);

        bool LoadAssemblyByteInCurrentDomain(byte[] assemblyBytes);

        bool LastResult { get; }

        string LastMessage { get; }
    }
}
