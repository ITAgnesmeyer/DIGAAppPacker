# DIGAAppPacker
Tool for packing NET - Executables into a native Executable

# Goals
Dieses Tool soll dazu dienen, eine NET - Assembly in eine NATIVE - Executable zu verpacken. Hierbei soll die enthaltene Assembyl verschlüsselt werden.

Basierend auf dem Beispiel - Projekt von Mathias Högström  https://www.codeproject.com/Articles/416471/CLR-Hosting-Customizing-the-CLR
wurde eine Wrapper-Applikation erstlelt. Mit dem DIGAAppPacker - Tools wird nun eine Assembly gepackt und dann in die Resourcen der Nativen - App gelinkt. Bei Aufruf wird der NATIVEN - App wird dann, die Assembly aus den Resourcen geladen, im Speicher entpackt und ausgeführt.

# Voraussetzungen
Damit die Assembly ausgeführt wird muss derzeit noch die neutrale Sprache auf Deutsch(de-DE) gesetzt werden.


