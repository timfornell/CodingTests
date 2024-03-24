class CommandNotFoundError(Exception):
   """
   Exception that is thrown if a provided command is not supported. The currently supported commands are available in
   the parameters 'supported_functions' and 'supported_operators' in the Calculator class.
   """
   pass


class CircularDependencyError(Exception):
   """
   Exception that is thrown if an evaluation of a register contains a circular dependency.
   """
   pass


class RegisterNamingError(Exception):
   pass


class CommandComponentsError(Exception):
   pass


class RegisterNotFoundError(Exception):
   pass


class RegisterMissingValueError(Exception):
   pass