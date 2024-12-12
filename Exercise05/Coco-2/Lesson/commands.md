*Ausführen in Visual-Studio Developer Shell*

Scanner-Generator aufrufen
```bash
SG.exe
```

`.atg` File übergeben
```bash
Calc.atg
```

Listing-Datei (`.lst`) wird erzeugt. Hier könnte man Fehler nachlesen.

---

Parser-Generator erzeugen

```bash
PGT.exe
```

`.atg` File übergeben
```bash
Calc.atg
```

`Main.frm` kopieren, umbennen in `Calc.cs` und alle `XXX` durch `Calc` ersetzen

---

Compiler bauen

```bash
csc *.cs
```

---

Calculator aufrufen
```bash
Calc.exe
```

Input-File übergeben
```
Expr.txt
```
