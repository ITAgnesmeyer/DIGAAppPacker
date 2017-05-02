# DIGAAppPacker
Tool for packing NET - Executables into a native Executable

# Ziele
Dieses Tool soll dazu dienen, eine NET - Assembly in eine NATIVE - Executable zu verpacken. Hierbei soll die enthaltene Assembly verschlüsselt werden.

Basierend auf dem Beispiel - Projekt von Mathias Högström  https://www.codeproject.com/Articles/416471/CLR-Hosting-Customizing-the-CLR
wurde eine Wrapper-Applikation erstellt. Mit dem DIGAAppPacker - Tools wird nun eine Assembly gepackt und dann in die Ressourcen der Nativen - App gelinkt. Bei Aufruf wird der NATIVEN - App wird dann, die Assembly aus den Ressourcen geladen, im Speicher entpackt und ausgeführt.

# Goals
This tool is intended to pack a NET assembly into a NATIVE executable. In this case, the contained assembly is to be encrypted.

Based on the sample project of Mathias Högström https://www.codeproject.com/Articles/416471/CLR-Hosting-Customizing-the-CLR a wrapper application was created. With the DIGAAppPacker tools, an assembly is now packed and then linked into the resources of the native app. When called, the NATIVE app is then unpacked and run from the resources, loaded into the 

# Voraussetzungen
Damit die Assembly ausgeführt wird muss derzeit noch die neutrale Sprache auf Deutsch(de-DE) gesetzt werden.
Zusätzlich muss in dem Zielverzeichnis die "SampleAppDomainManager.dll" liegen.

# Requirements
For the assembly to run, the neutral language must still be set to German (en-DE).
In addition, the "SampleAppDomainManager.dll" must reside in the target directory

# Ausführen
Um die Anwendung auszuführen laden Sie sich bitte den Release - Ordner herunter.
Führen Sie die Anwendung aus diesem Ordner aus.

1) In der Oberfläche tragen Sie den Pfad zu Ihrer Anwendung ein.
2) Geben Sie einen Zielordner an.
3) Geben Sie den Namespace Ihrer Anwendung an.
4) Betätigen Sie den Button "Create Executable". Wenn das Erstellen funktioniert hat, wird eine entsprechende Meldungsbox ausgegeben.
5) Kopieren Sie die "SampleAppDomainManager.dll" in das Ausgabeverzeichnis.
6) Starten Sie die Anwendung.

# Execute
To run the application, please download the release folder.
Run the application from this folder.

1) In the interface, enter the path to your application.
2) Specify a destination folder.
3) Specify the namespace of your application.
4) Press the "Create Executable" button. If the creation has worked, a corresponding message box is output.
5) Copy the "SampleAppDomainManager.dll" to the output directory.
6) Start the application.

<image src="https://github.com/ITAgnesmeyer/DIGAAppPacker/blob/master/Doku/Screenshot.png"/>





