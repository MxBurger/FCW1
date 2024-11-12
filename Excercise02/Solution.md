# 1.
Gegeben sei folgende Grammatik für einfache arithmetische Ausdrücke:
```
E → T | + T | - T | E + T | E - T
T → F | T * F | T / F
F → v | ( E )
```

## a)


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
⇒ -T  *  E + (<u>T</u>)
⇒ -T  *  E + (T / <u>F</u>)
⇒ -T  *  E + (<u>T</u> / v)
⇒ -T  *  E + (<u>T</u> / v)
⇒ -T  *  E + (<u>F</u> / v)

## b)

```
( ( v + v ) * v / v ) – ( v / v )
```

### Linkskanonisch

( ( *v* + v ) * v / v ) – ( v / v )   |-
( ( *F* + v ) * v / v ) – ( v / v )   |-
( ( *T* + v ) * v / v ) – ( v / v )   |-
( ( E + *v* ) * v / v ) – ( v / v )   |-
( ( E + *F* ) * v / v ) – ( v / v )   |-
( ( E + T ) * v / v ) – ( v / v )     |-
( ( *E + T* ) * v / v ) – ( v / v )   |-
( *( E )* * v / v ) – ( v / v )       |-
(  *F*  * v / v ) – ( v / v )         |-
(  T  * *v* / v ) – ( v / v )         |-
(  *T  * F* / v ) – ( v / v )         |-
( T/F ) -(v/v)                        |-
( *T/F* ) -(v/v)                      |-
( *T* ) -(v/v)                        |-
*( E )* -(v/v)                        |-
*F* - ( v / v)                        |-
*T* - (v / v)                         |-
E -(*v*/v)                            |-
E - (*F* / v)                         |-
E - (T / *v*)                         |-
E - ( *T/F*)                          |-
E - ( *T* )                           |-
E - *(E)*                             |-
E - *F*                               |-
*E - T*                               |-
E                                     |-

### Rechtskanonisch

# 2.
## a)
nein, nicht eindeutig (es gibt für einen Satz mehr als einen Syntaxbaum)

>TODO: insert syntaxtree here
```
frac -> frac d | ϵ
```

## b)

> TODO define d
```
Real = [ "+" | "-"]
       d {d}
       ["."{d}]
       ["E" ["+" | "-"] d{d}]

d = ...
```

# 3.
```
S → b A | a B | ϵ
A → b A | b
B → b C | b
C → a B
```

## a)
```
E -> A b | B b | ϵ
A -> b | A a
B -> a | C a
C -> B b 
```

## b)
```
ϵ +
b a* b +
a (b a)* b 
```

# 4.
## a)

```
B -> l E | l
E -> _ U | d E | l E | d | l
U -> l E | d E | l | d
```

## b)
```
E -> l | E l | E d | U l | U d
U -> E _
```

## c)
```
l (_(d + l) + d + l)
```

# 5.

## a)



