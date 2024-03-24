

## Implementation details

### Naming of registries

Since the operators and the commands to print/quit are given in strings, there is nothing that prevents the user to use
the same strings for registries. This is not something that is specified in the instructions. Therefore, I have taken
the liberty of making a design decision to restrict the registry names a little bit.


### Case sensitive input

The instructions specify that all input should be case sensitive, yet they include two ways of inputting the 'quit'
command, i.e., 'quit' and 'QUIT'. I have decided to only allow the lower case form of 'quit'. However, it is something
that is easily changed if required.