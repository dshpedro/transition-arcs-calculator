# Transition Arcs Calculator
Calculates transition arcs for a given SOP expression.

## Compiling the program
- Simply type `make` to compile it

## Input
- To input an expression `x`, use the command:
`./arcs.out 'x'`
- You can also use an optional `-d` debug flag after the expression `x` to print the minterms and the truth table. For example:
`./arcs.out 'x' -d`

### Input characters
- **Variables**: a-z (must be in lowercase)
- **Operators**:
    - `!` (NOT)
    - `*` (AND)
    - `+` (OR)
- **Space Character**: can only appear around the OR operator.
    - **Note**: Factored forms (with parentheses) will not be passed. For example: `x*(w + y)` will be passed as `x*w + x*y`.

### SOP expressions
- The input expression has to be in a Summ Of Products format.

