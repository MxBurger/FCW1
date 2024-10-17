# 1. Grammatiken – Grundbegriffe

## a) Bestimmen Sie die Mengen VT und VN
```
Satzsymbol = DataStat
Vt = { DataDeclRest, DataDeclRest, DataNameList, 
       DataName, DataValueList, DataValue, DataDoList,
       DDataDoListRest }
Vn = { "DATA",",", "/", id, num, "*", "+", "-", str, "(", ")", expr }

Anmerkung: id, num, str und expr sind Terminalklassen!
epsilon ist kein Terminalsymbol
```

## b) Geben Sie den/die kürzesten Satz/Sätze an, den/die man mit dieser Grammatik bilden kann.

DS => DATA *DD* *DDR* =>
DATA *DNL* / *DVL* / *DDR* =>
DATA *DN* / *DVL* / *DDR* =>
DATA id / *DVL* / *DDR* =>
DATA id / *DV* / *DDR* =>
DATA id / id / *DDR* =>
DATA id / id /

## c) Ermitteln Sie alle rekursiven Nonterminalsymbole. Geben Sie für jedes dieser Nonterminalsymbole an, ob es direkt- oder indirekt- und links-, zentral- oder rechtsrekursiv ist.

**NT** ...Nonterminalsymbol
**d/i**...direkt oder indirekt rekursiv
**l/z/r**...links, zentral oder rechts rekursiv

| NT  | d / i | l / z / r |
|---  |---    | ---       |
| DDR  |   d |  l   |
| DNL  |   d |  r   |
| DVL  |   d |  l   |
| DDL  |   d |  z   |
| DDL  |   i |  z   |
| DDLR |   d |  l   |
| DDLR |   i |  z   |


## d) Transformieren Sie die gegebene Grammatik in das Regelsystem der formalen Sprachen. Welche Grammatikschreibweise halten Sie für lesbarer? Begründen Sie Ihre Antwort.

[IMPORTANT]
NOCH NICHT FERTIG

```
DS  -> DATA DDL DDR
DDR -> ε | DDR 
OC  -> ε | ,

// TODO ...

DV  ->


```
