# Introduction

This coding test contains a simple calculator. The details of the calculator are not included in the documentation
as the files was asked to be kept anonymous.


## Setup

The only requirement to run the program is to have Python 3 installed. Program is tested with version 3.10.8.

To execute the tests the module pytest is required. To install the correct version run the following:

```Shell
python -m venv .venv
source .venv/Scripts/activate
python -m pip install -r requirements.txt
```

## Running calculator

If Python 3 is installed the calculator can be run in one of two ways:

**Interactively**

This requires the user to provide input via stdin.

```Shell
python Calculator/main.py
```

**From a file**

This requires the user to provide a path to a file that contains input.

```Shell
python Calculator/main.py -f <path-to-file>
```

## Running tests

To execute these tests do one of the following:

```Shell
cd Calculator
python3 main.py -f Calculator/Test/TestFiles/TestFile_1.txt
```

and look at the corresponding chapter for expected output.

Or run:

```Shell
cd Calculator
python -m pytest Test/
```

### Test cases

The sub chapters contains the expected output for some simple test cases.

#### [TestFile_1](Calculator/Test/TestFiles/TestFile_1.txt)

Example included from instructions.

Expected output:

```Shell
Output: 5.0
Output: 3.0
Output: 6.0
```

#### [TestFile_2](Calculator/Test/TestFiles/TestFile_2.txt)

Example included from instructions.

Expected output:

```Shell
Output: 11.0
```

#### [TestFile_3](Calculator/Test/TestFiles/TestFile_3.txt)

Example included from instructions.

Expected output:

```Shell
Output: 90.0
```

#### [TestFile_4](Calculator/Test/TestFiles/TestFile_4.txt)

Circular dependency when trying to evaluate register 'a'.

Expected output:

```Shell
Error! Encountered a circular dependency: Register 'b' contains a circular reference to register 'a'
```

#### [TestFile_5](Calculator/Test/TestFiles/TestFile_5.txt)

Register 'b' tries to perform 'divide' operation with register 'c' which does not have a value. Invalid operation
are skipped.

Expected output:

```Shell
Output: 20.0
Output: 20.0
The value/registry 'c' could not be resolved and can't be used for operation 'divide'.
Output: 400.0
```

#### [TestFile_6](Calculator/Test/TestFiles/TestFile_6.txt)

Register 'a' tries to use register 'c' before it is created. Once 'c' is created, both 'c' and 'a' can be
evaluated and printed.

Expected output:

```Shell
> Encountered a missing register: Can't perform 'print' on 'c' as it doesn't exist.
The value/registry 'c' could not be resolved and can't be used for operation 'add'.
> Encountered a register without value: Register 'a' has no value.
Output: 10.0
Output: 10.0
```

#### [TestFile_7](Calculator/Test/TestFiles/TestFile_7.txt)

Circular dependency between 'b' and 'a' causes first prints to fail. After clearing 'a', the dependency is removed and
both registers can be evaluated.

Expected output:

```Shell
> Encountered a circular dependency: Register 'a' contains a circular reference to register 'b'
Output: 8400.0
Output: 20.0
```

#### [TestFile_8](Calculator/Test/TestFiles/TestFile_8.txt)

Test to verify that negative values are handled correctly.

Expected output:

```Shell
Output: 0.0
Output: 6.0
```

## Implementation details

### Case sensitive input

The instructions specify that all input should be case sensitive, yet they include two ways of inputting the 'quit'
command, i.e., 'quit' and 'QUIT'. I have decided to only allow the lower case form of 'quit'. However, it is something
that is easily changed if desired.

### Initial value of registers

The instructions does not specify what should happen if a register is never assigned a value. This could happen in the
following example:

```Shell
A add #
print A
```

The first provided command is invalid since '#' is not a defined register. Meaning, 'A' doesn't contain a value. In this
case an error will be thrown, indicating that 'A' does not have a value (and that '#' is not a valid register).

### Circular dependencies

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

### Clear register

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

### Negative values

It isn't explicitly stated if negative values should be valid input. Although, it isn't stated that they shouldn't be
supported either. Regardless, it is allowed to input negative values in the commands.

The command:

```Shell
a add 3
a add -3
print a
a add 3
a subtract -3
```

Will produce:

```Shell
Output: 0.0
Output: 6.0
```