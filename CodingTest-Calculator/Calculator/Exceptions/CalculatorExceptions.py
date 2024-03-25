class CommandNotFoundError(Exception):
   """
   Exception that is raised if a provided command is not supported. The currently supported commands are available in
   the parameters 'supported_functions' and 'supported_operators' in the Calculator class.
   """
   pass


class CircularDependencyError(Exception):
   """
   Exception that is raised if an evaluation of a register contains a circular dependency.
   """
   pass


class RegisterNamingError(Exception):
   """
   Exception that is raised if a register is named incorrectly
   """
   pass


class CommandComponentsError(Exception):
   """
   Exception that is raised if the provided command can't be interpreted
   """
   pass


class RegisterNotFoundError(Exception):
   """
   Exception that is raised if a register name doesn't exist
   """
   pass


class RegisterMissingValueError(Exception):
   """
   Exception that is raised if a register doesn't have a value assigned. Typically happens if a print operation is
   performed before any arithmetic operations
   """
   pass
