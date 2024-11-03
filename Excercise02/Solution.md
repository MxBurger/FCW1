# 1.

## a)


```
- v * ( v + v / v )
```
### Linkskanonisch
E => -T => -*T*  * F
=> - *F* * F => -v * *F* =>  -v *(*E*)
=> -v * (*E* + T) => -v * (*T* + T)
=> -v * (*E* + T) => -v * (v + *T*)
=> -v * (v + *T*/F) => -v * (v + *F*/F) 
=> -v * (v + v/*F*) =>  -v * (v + v/v)

### Rechtskanonisch

>TODO

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



