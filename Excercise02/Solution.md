# 1. Kanonische Ableitung und Reduktion
## a) Leiten Sie aus dem Satzsymbol E einmal links- und einmal rechtskanonisch folgenden Satz ab:


```
- v * ( v + v / v )
```
### Linkskanonisch

<u>E</u>
⇒ -<u>T</u>
⇒ -<u>T</u>  * F
⇒ - <u>F</u> * F
⇒ -v * <u>F</u>
⇒  -v *(<u>E</u>)
⇒ -v * (<u>E</u> + T)
⇒ -v * (<u>T</u> + T)
⇒ -v * (<u>E</u> + T)
⇒ -v * (v + <u>T</u>)
⇒ -v * (v + <u>T</u>/F)
⇒ -v * (v + <u>F</u>/F) 
⇒ -v * (v + v/<u>F</u>)
⇒  -v * (v + v/v)

### Rechtskanonisch

<u>E</u>
⇒ -<u>T</u>
⇒ -T  * <u>F</u>
⇒ -T  * (<u>E</u>)
⇒ -T * (E + <u>T</u>)
⇒ -T * (E + T / <u>F</u>)
⇒ -T * (E + <u>T</u> / v)
⇒ -T * (E + <u>F</u> / v)
⇒ -T * (<u>E</u> + v / v)
⇒ -T * (<u>T</u> + v / v)
⇒ -T * (<u>F</u> + v / v)
⇒ -<u>T</u> * (v + v / v)
⇒ -<u>F</u> * (v + v / v)
⇒ -v * (v + v / v)


<!-- pagebreak -->




## b) Reduzieren Sie folgenden Satz

```
( ( v + v ) * v / v ) – ( v / v )
```

### Linkskanonisch

( ( <u>v</u> + v ) * v / v ) – ( v / v )   ⊢
( ( <u>F</u> + v ) * v / v ) – ( v / v )   ⊢
( ( <u>T</u> + v ) * v / v ) – ( v / v )   ⊢
( ( E + <u>v</u> ) * v / v ) – ( v / v )   ⊢
( ( E + <u>F</u> ) * v / v ) – ( v / v )   ⊢
( ( <u>E + T</u> ) * v / v ) – ( v / v )   ⊢
( <u>( E )</u> * v / v ) – ( v / v )       ⊢
(  <u>F</u>  * v / v ) – ( v / v )         ⊢
(  T  * <u>v</u> / v ) – ( v / v )         ⊢
(  <u>T  * F</u> / v ) – ( v / v )         ⊢
( <u>T/F</u> ) - ( v / v )                 ⊢
( <u>T</u> ) - ( v / v )                   ⊢
<u>( E )</u> - ( v / v )                   ⊢
<u>F</u> - ( v / v )                       ⊢
<u>T</u> - ( v / v )                       ⊢
E -( <u>v</u> / v)                         ⊢
E - ( <u>F</u> / v)                        ⊢
E - (T / <u>v</u>)                         ⊢
E - ( <u> T / F </u> )                     ⊢
E - ( <u>T</u> )                           ⊢
E - <u>(E)</u>                             ⊢
E - <u>F</u>                               ⊢
<u>E - T</u>                               ⊢
E                                          ⊢

### Rechtskanonisch
( ( v + v ) * v / v ) – ( v / <u>v</u> )   ⊢
( ( v + v ) * v / v ) – ( <u>v</u> / F )   ⊢
( ( v + v ) * v / v ) – ( <u>F</u> / F )   ⊢
( ( v + v ) * v / v ) – ( <u>T / F</u> )   ⊢
( ( v + v ) * v / v ) – ( <u>T</u> )       ⊢
( ( v + v ) * v / v ) – <u>( E )</u>       ⊢
( ( v + v ) * v / v ) – <u>F</u>           ⊢
( ( v + v ) * v / <u>v</u> ) – T           ⊢
( ( v + v ) * <u>v</u> / F ) – T           ⊢
( ( v + <u>v</u> ) * F / F ) – T           ⊢
( ( v + <u>F</u> ) * F / F ) – T           ⊢
( ( <u>v</u> + T ) * F / F ) – T           ⊢
( ( <u>F</u> + T ) * F / F ) – T           ⊢
( ( <u>T</u> + T ) * F / F ) – T           ⊢
( ( <u>E + T</u> ) * F / F ) – T           ⊢
( ( <u>( E )</u> ) * F / F ) – T           ⊢
( <u>F</u>  * F / F ) – T                  ⊢
( <u>T  * F</u> / F ) – T                  ⊢
( <u>T  / F</u>  ) – T                     ⊢
( <u>T</u>  ) – T                          ⊢
<u>( E  )</u> – T                          ⊢
<u>F</u> – T                               ⊢
<u>T</u> – T                               ⊢
<u>E – T </u>                              ⊢
E                                          ⊢


![Syntaxtree](images/1b.png){ width="400" style="display: block; margin: 0 auto" }
Ich stelle fest der Syntaxbaum lässt sich direkt aus der Reduktions- / Ableitungsfolge erkennen.
Wird bei linkskanonischer Ableitung von links nach rechts aufgebaut, bei rechtskanonischer entsprechend umgekehrt. 

<!-- pagebreak -->




# 2. Mehrdeutigkeit, Beschreibung und Schreibweisen
## a) Ist diese Grammatik mehrdeutig? Begründen Sie Ihre Antwort und transformieren Sie diese Grammatik – wenn nötig – in eine äquivalente eindeutige Grammatik.
Nein, nicht eindeutig (es gibt für einen Satz mehr als einen Syntaxbaum)
![Syntaxbaum](images/2a.png){ width="400" style="display: block; margin: 0 auto" }
```
frac -> frac d | ϵ
```

## b) Geben Sie eine möglichst kurze Grammatik für L(G(real)) in Wirth'scher EBNF an.
```
Real = [ "+" | "-"]
       d {d}
       ["."{d}]
       ["E" ["+" | "-"] d{d}]
d = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```

<!-- pagebreak -->



# 3. Reguläre Grammatiken 

![Zustands-Automat](images/3a.png){ width="250" style="display: block; margin: 0 auto" }

## a) Geben Sie eine äquivalente umgekehrt reguläre Grammatik an.


```
E -> A b | B b | ϵ
A -> b | A a
B -> a | C a
C -> B b 
```

## b) Geben Sie einen regulären Ausdruck an, der die Sprache dieser Grammatik beschreibt/erkennt
```
ϵ +
b a* b +
a (b a)* b 
```

# 4. Bezeichner in der Programmiersprache Ada

![Zustands-Automat](images/4a.png){ width="250" style="display: block; margin: 0 auto" }

## a) Geben Sie eine reguläre Grammatik an, die diese Bezeichner beschreibt.

```
B -> l E | l
E -> _ U | d E | l E | d | l
U -> l E | d E | l | d
```

## b) Geben Sie eine umgekehrt reguläre Grammatik an, die diese Bezeichner beschreibt.
```
E -> l | E l | E d | U l | U d
U -> E _
```

## c) Leiten Sie aus der regulären Grammatik einen regulären Ausdruck ab, der die Menge aller Bezeichner beschreibt. Kann man den so hergeleiteten Ausdruck noch verkürzen?
```
l (_(d + l) + d + l)*
```

# 5. Transformation zwischen Darstellungsformen regulärer Sprachen

## a)


### Nicht deterministischer Automat
![NFA](images/5a.png)

|   | $a$ | $b$ |
| --- | --- | --- |
|$\rhd$ $S$ | $\{A, AB\} $ | $\{BA\}$  |
| $\circ A$ | $\{A \}$  | -  |
| $AB$ | -  | $\{AB*\}$  |
| $\circ AB*$ | $\{AB\}$  | $\{BA\}$  |
| $BA$ | $\{BA*\}$  | -  |
| $\circ BA*$ | -  | $\{BA\}$  |
|        |       |         |
| $\{A,AB\}$ | $\{A\}$  | $\{AB*\}$  |


### deterministischer Automat
![DFA](images/5a_nfa.png)



## b) 

**Auswirkungen:**
- Das Anhängen von $0$ an eine Zahl $x$ ergibt $2 * x$
- Das Anhängen von $1$ an eine Zahl $x$ ergibt $2*x+1$


**Fall:** Anhängen einer $0$ an $x$ (neue Zahl heißt dann $x_0$)
- $x_0 = 2*x$
- Wenn $x \ mod \ 3 = 0 $, dann ergibt $(2*0) \ mod \ 3 = 0$. Rest ist $0$
- Wenn $x \ mod \ 3 = 1 $, dann ergibt $(2*1) \ mod \ 3 = 2$. Rest ist $2$
- Wenn $x \ mod \ 3 = 2 $, dann ergibt $(2*2) \ mod \ 3 = 1$. Rest ist $1$

**Fall:** Anhängen einer $1$ an $x$ (neue Zahl heißt dann $x_1$)
- $x_1 = 2*x+1$
- Wenn $x \ mod \ 3 = 0 $, dann ergibt $(2*0+1) \ mod \ 3 = 1$. Rest ist $1$
- Wenn $x \ mod \ 3 = 1 $, dann ergibt $(2*1+1) \ mod \ 3 = 0$. Rest ist $0$
- Wenn $x \ mod \ 3 = 2 $, dann ergibt $(2*2+1) \ mod \ 3 = 2$. Rest ist $2$



![DreiModuloBinär](images/5b.png)





