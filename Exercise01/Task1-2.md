# 1. Grammatiken – Grundbegriffe

## a) Bestimmen Sie die Mengen VT und VN
```
Satzsymbol = DataStat
Vt = { DataDeclRest, DataDeclRest, DataNameList, 
       DataName, DataValueList, DataValue, DataDoList,
       DDataDoListRest }
Vn = { "DATA",",", "/", id, num, "*", "+", "-", str, "(", ")", expr }

Anmerkung: id, num, str und expr sind Terminalklassen!
ε ist kein Terminalsymbol
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

```
DataStat                -> DATA DataDecl DataDeclRest
DataDeclRest            -> ε | DataDeclRest OptionalComma DataDecl
OptionalComma           -> ε | ,
DataDecl                -> DataNameList / DataValueList /
DataNameList            -> DataName | DataName , DataNameList
DataName                -> id | DataDoList
DataValueList           -> DataValue | DataValueList , DataValue
DataValue               -> NumOrId OptionalValue | SignedNumOrStr
NumOrId                 -> num | id
NumOrStr                -> num | str
OptionalValue           -> ε | * id | * OptinalSign num | * str
SignedNumOrStr          -> OptinalSign num | OptinalSign str
OptinalSign             -> ε | + | -
DataDoList              -> ( ODDL DataDoListRest )
ODDL                    -> IdList | DataDoList
IdList                  -> id ( CommaSeparatedId ) 
CommaSeparatedId        -> ε | , id CommaSeparatedId
DataDoListRest          -> ε | DataDoListRest , 
DataDoListRestOption    -> id Expression | DataDoList
Expression              -> ( ExpressionList ) | = expr , expr expr | = expr , expr
ExpressionList          -> expr | expr , ExpressionList
```

Die Wirthsch'e EBNF halte ich für lesbarer, da die zusätzlichen Metasymbole sehr
ausdrucksstark sind und die Einführung zusätzlicher Nonterminalsymbole teilweise überflüssig machen. Die von Niklaus Wirth gewählten Metasymbole sind außerdem leicht in herkömmlichen Texteditoren zu verwenden. (keine fancy zeilenübergreifenden Symbole)


## e) Zeichnen Sie den Syntaxbaum für folgenden Satz, verwenden Sie dazu die gegebene Grammatik G(DataStat) von oben:
```
DATA id, id / num * str /, ( id(id), id = expr, expr ) / num * num /
```

![Syntaxtree](pictures/Syntaxtree.png)

## Gibt es mehrere Syntaxbäume für diesen Satz? (Mit Begründung!)

 >**_NOTE:_**
TODO



# 2. Konstruktion einer Grammatik

Z...Zahl
ZF...Ziffernfolge
UZ...Ungerade Ziffer
MZ...Mehrstellige Zahl
SZ...Start-Ziffer
MTZ...Mittlere Ziffer

```
Z -> + ZF | - ZF | ZF
ZF -> UZ | MZ
UZ -> 1 | 3 | 5 | 7 | 9 
MZ -> SZ MTZ UZ
SZ -> 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
MTZ -> 0 MTZ | 1 MTZ | 2 MTZ | 3 MTZ | 4 MTZ | 5 MTZ | 6 MTZ | 7 MTZ | 8 MTZ | 9 MTZ |  ε
```

in Wirth'scher EBNF
```
Z = [ "+" | "-" ] 
[
    ( "1", "2", "3", "4", "5", "6", "7", "8", "9" )
    { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" }
]
( "1" | "3" | "5" | "7" | "9" ) .
```

