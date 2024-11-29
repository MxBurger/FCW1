## Lexer source generieren

```shell
flex Calc.l
```


## Compiler source erstellen
```shell
bison -d Calc.y
```
`-d` für HeaderFile-Erzeugung
 
## Compiler bauen

```
gcc lex.yy.c Calc.tab.c -o Calc
```

## mehr flags

```shell
bison -d -v -g Calc.y
```
`-d` für HeaderFile-Erzeugung
`-v` für verbose Output-Info (`*.output`)
`-g` für grafische ausgabe (`*.dot`)
