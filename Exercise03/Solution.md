## Aufgabe 4

### a)
```
ConstDef  → const Type ident Init OptNInits ;
Type      → bool | int
Init      → = Val
Val       → false | true | OptSign number
OptSign   → ε | + | - 
OptNInits → ε | , ident Init OptNInits   
```

### b)

S.1) Für jede Regel A → α einen Übergang δ(Z, ε, A) = (Z, αR):
```
Für ConstDef → const Type ident Init OptNInits ;

δ(Z, ε, ConstDef) = (Z, ; OptNInits Init ident Type const)

Für Type → bool | int

δ(Z, ε, Type) = (Z, bool)
δ(Z, ε, Type) = (Z, int)

Für Init → = Val

δ(Z, ε, Init) = (Z, Val =)

Für Val → false | true | OptSign number

δ(Z, ε, Val) = (Z, false)
δ(Z, ε, Val) = (Z, true)
δ(Z, ε, Val) = (Z, number OptSign)

Für OptSign → ε | + | -

δ(Z, ε, OptSign) = (Z, ε)
δ(Z, ε, OptSign) = (Z, +)
δ(Z, ε, OptSign) = (Z, -)

Für OptNInits → ε | , ident Init OptNInits

δ(Z, ε, OptNInits) = (Z, ε)
δ(Z, ε, OptNInits) = (Z, OptNInits Init ident ,)

```

S.2) Für jedes Terminalsymbol a einen Übergang δ(Z, a, a) = (Z, ε):

```

δ(Z, const, const) = (Z, ε)
δ(Z, bool, bool) = (Z, ε)
δ(Z, int, int) = (Z, ε)
δ(Z, ident, ident) = (Z, ε)
δ(Z, =, =) = (Z, ε)
δ(Z, false, false) = (Z, ε)
δ(Z, true, true) = (Z, ε)
δ(Z, number, number) = (Z, ε)
δ(Z, +, +) = (Z, ε)
δ(Z, -, -) = (Z, ε)
δ(Z, ,, ,) = (Z, ε)
δ(Z, ;, ;) = (Z, ε)
```

### c)

S.1) Für jede Regel A → α einen Übergang δ(Z, ε, α) = (Z, A):

```
Für ConstDef → const Type ident Init OptNInits ;

δ(Z, ε, const Type ident Init OptNInits ;) = (Z, ConstDef)

Für Type → bool | int

δ(Z, ε, bool) = (Z, Type)
δ(Z, ε, int) = (Z, Type)

Für Init → = Val

δ(Z, ε, = Val) = (Z, Init)

Für Val → false | true | OptSign number

δ(Z, ε, false) = (Z, Val)
δ(Z, ε, true) = (Z, Val)
δ(Z, ε, OptSign number) = (Z, Val)

Für OptSign → ε | + | -

δ(Z, ε, ε) = (Z, OptSign)
δ(Z, ε, +) = (Z, OptSign)
δ(Z, ε, -) = (Z, OptSign)

Für OptNInits → ε | , ident Init OptNInits

δ(Z, ε, ε) = (Z, OptNInits)
δ(Z, ε, , ident Init OptNInits) = (Z, OptNInits)
```

S.2) Für jedes Terminalsymbol a und jedes x ∈ V ∪ {$}:

V = {`ConstDef`, `Type`, `Init`, `Val`, `OptSign`, `OptNInits`, `const`, `bool`, `int`, `ident`, `=`, `false`, `true`, `number`, `+`, `-`, `,` , `;`}

```
Für const:
δ(Z, const, x) = (Z, x const) für alle x ∈ V ∪ {$}

Für bool:
δ(Z, bool, x) = (Z, x bool) für alle x ∈ V ∪ {$}

Für int:
δ(Z, int, x) = (Z, x int) für alle x ∈ V ∪ {$}

Für ident:
δ(Z, ident, x) = (Z, x ident) für alle x ∈ V ∪ {$}

Für =:
δ(Z, =, x) = (Z, x =) für alle x ∈ V ∪ {$}

Für false:
δ(Z, false, x) = (Z, x false) für alle x ∈ V ∪ {$}

Für true:
δ(Z, true, x) = (Z, x true) für alle x ∈ V ∪ {$}

Für number:
δ(Z, number, x) = (Z, x number) für alle x ∈ V ∪ {$}

Für +:
δ(Z, +, x) = (Z, x +) für alle x ∈ V ∪ {$}

Für -:
δ(Z, -, x) = (Z, x -) für alle x ∈ V ∪ {$}

Für ,:
δ(Z, ,, x) = (Z, x ,) für alle x ∈ V ∪ {$}

Für ;:
δ(Z, ;, x) = (Z, x ;) für alle x ∈ V ∪ {$}
```

Beispielhaft wurde `const` evaluiert:
```
δ(Z, const, $) = (Z, $ const)
δ(Z, const, ConstDef) = (Z, ConstDef const)
δ(Z, const, Type) = (Z, Type const)
δ(Z, const, Init) = (Z, Init const)
δ(Z, const, Val) = (Z, Val const)
δ(Z, const, OptSign) = (Z, OptSign const)
δ(Z, const, OptNInits) = (Z, OptNInits const)
δ(Z, const, const) = (Z, const const)
δ(Z, const, bool) = (Z, bool const)
δ(Z, const, int) = (Z, int const)
δ(Z, const, ident) = (Z, ident const)
δ(Z, const, =) = (Z, = const)
δ(Z, const, false) = (Z, false const)
δ(Z, const, true) = (Z, true const)
δ(Z, const, number) = (Z, number const)
δ(Z, const, +) = (Z, + const)
δ(Z, const, -) = (Z, - const)
δ(Z, const, ,) = (Z, , const)
δ(Z, const, ;) = (Z, ; const)
```

S.3) Den Übergang für das Ende:

```
δ(Z, ε, $ConstDef) = (R, ε)
```
