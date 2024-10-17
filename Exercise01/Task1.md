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

 >**_NOTE:_**
NOCH NICHT FERTIG

```
DS  -> DATA DDL DDR
DDR -> ε | DDR 
OC  -> ε | ,

// TODO ...

DV  ->
NOD -> num | id
NOS -> num | str
DVP -> ε | * id | * OPS num | * str // TODO adde second alternative here
OPS -> ε | + | -


// TODO ...

DDL -> ( id ( id )
CSV -> ε | , id CSV

```
Die Wirthsch'e EBNF halte ich für lesbarer, da die zusätzlichen Metasymbole sehr
ausdrucksstark sind und die Einführung zusätzlicher Nonterminalsymbole teilweise
überflüssig machen.


## de Zeichnen Sie den Syntaxbaum für folgenden Satz, verwenden Sie dazu die gegebene Grammatik G(DataStat) von oben:
```
DATA id, id / num * str /, ( id(id), id = expr, expr ) / num * num /
```
## Gibt es mehrere Syntaxbäume für diesen Satz? (Mit Begründung!)

 >**_NOTE:_**
TODO



# 2. Konstruktion einer Grammatik