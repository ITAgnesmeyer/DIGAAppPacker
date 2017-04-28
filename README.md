# DIGAAppPacker
Tool for packing NET - Executables into a native Executable

# Goals
Dieses Tool soll dazu dienen, eine NET - Assembly in eine NATIVE - Executable zu verpacken. Hierbei soll die enthaltene Assembly verschlüsselt werden.

Basierend auf dem Beispiel - Projekt von Mathias Högström  https://www.codeproject.com/Articles/416471/CLR-Hosting-Customizing-the-CLR
wurde eine Wrapper-Applikation erstellt. Mit dem DIGAAppPacker - Tools wird nun eine Assembly gepackt und dann in die Ressourcen der Nativen - App gelinkt. Bei Aufruf wird der NATIVEN - App wird dann, die Assembly aus den Ressourcen geladen, im Speicher entpackt und ausgeführt.

# Voraussetzungen
Damit die Assembly ausgeführt wird muss derzeit noch die neutrale Sprache auf Deutsch(de-DE) gesetzt werden.
Zusätzlich muss in dem Zielverzeichnis die "SampleAppDomainManager.dll" liegen.

# Ausführen
Um die Anwendung auszuführen laden Sie sich bitte den Release - Ordner herunter.
Führen Sie die Anwendung aus diesem Ordner aus.

1) In der Oberfläche tragen Sie den Pfad zu Ihrer Anwendung ein.
2) Geben Sie einen Zielordner an.
3) Geben Sie den Namespace Ihrer Anwendung an.
4) Betätigen Sie den Button "Create Executable". Wenn das Erstellen funktioniert hat, wird eine entsprechende Meldungsbox ausgegeben.
5) Kopieren Sie die "SampleAppDomainManager.dll" in das Ausgabeverzeichnis.
6) Starten Sie die Anwendung.

<image src="https://github.com/ITAgnesmeyer/DIGAAppPacker/blob/master/Doku/Screenshot.png"/>





