class CommandNotFoundError(Exception):
   pass


class CircularDependencyError(Exception):
   pass


class RegisterNamingError(Exception):
   pass


class CommandComponentsError(Exception):
   pass


class CalculationError(Exception):
   pass