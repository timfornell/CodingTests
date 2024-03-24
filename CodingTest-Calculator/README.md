# Introduction



# Implementation details

## Case sensitive input

The instructions specify that all input should be case sensitive, yet they include two ways of inputting the 'quit'
command, i.e., 'quit' and 'QUIT'. I have decided to only allow the lower case form of 'quit'. However, it is something
that is easily changed if desired.

## Initial value of registers

The instructions does not specify what should happen if a register is never assigned a value. This could happen in the
following example:

```Shell
A add #
print A
```

The first provided command is invalid since '#' is not a defined register. Meaning, 'A' doesn't contain a value. In this
case an error will be thrown, indicating that 'A' does not have a value (and that '#' is not a valid register).

## Circular dependencies

The instruction does not specify how circular dependencies between registers should be handled. One very simple example
of a circular dependency is this:

```Shell
a add b
b add 10
b multiply a
print b
```

As is clearly visible, the registry 'a' depends on 'b' and the registry 'b' depends on 'a'. When 'print b' is
evaluated, the order in which the evaluation should be performed is undefined. Namely, should the value obtained by the
operation 'a add b' contain the value after evaluating only 'b add 10', since b is equal to 10 when the expression
'a add b' is being evaluated, or should it not be allowed since 'a' is referencing a register whose value is currently
being evaluated?

The easiest solution to prevent an infinite loop from being started, where 'b' can't be evaluated before 'a' is
evaluated and 'a' can't be evaluated before 'b' is evaluated, is to prevent registers that depend on another register
that hasn't been completely evaluated. Without knowing the entire use case of the program and if this is desired
functionality, I am of the opinion that this solution is to prefer. Mainly because it does not introduce extra logic
into the code that can make it difficult to predict the behavior of the program.


## Clear register

A consequence of the design decision described in [Circular dependencies](#circular-dependencies) is that a once a
circular dependency has been created, that register is more or less useless. As illustrated below:

```Shell
a add b
b add 10
b multiply a
print b
b add 20
a add 20
b multiply a
print b
```

Since the register 'a' won't be possible to evaluate at the first 'print b' it will never be assigned any value and
if 'b' is to be evaluated again, even after 'a' has had values added, the circular dependency is still present. To allow
some flexibility when running, I added a "clear" command. That would clear any stored operations from a register.
Meaning the example above can be modified like this:

```Shell
a add b
b add 10
b multiply a
print b
clear a <- New line
b add 20
a add 20
b multiply a
print b
```

Which would make the register 'a' usable again.