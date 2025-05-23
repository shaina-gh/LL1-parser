# LL(1) Parser Construction in C

## 🧠 Aim

The goal of this project is to construct an LL(1) parsing table for a given context-free grammar and use it to parse an input string to determine whether it can be derived from the grammar. This is an essential step in compiler design to validate the syntactic structure during the parsing phase.

## 🧾 Description

This C program performs the following tasks:
- Calculates **FIRST** and **FOLLOW** sets for each non-terminal in the grammar.
- Constructs the **LL(1) parsing table**.
- Parses an input string using the constructed table to determine acceptance or rejection.

The implementation is interactive, allowing users to input their grammar and test strings directly via the command line.

## ⚙️ Logic and Flow

1. **Input Grammar**: User inputs a list of grammar productions in the form `A=α`, where `A` is a non-terminal and `α` is a string of terminals and/or non-terminals.
2. **Compute FIRST and FOLLOW Sets**:
   - `FIRST(X)`: Set of terminals that begin the strings derivable from `X`.
   - `FOLLOW(X)`: Set of terminals that can appear immediately to the right of `X`.
3. **Build LL(1) Parsing Table**:
   - Based on the FIRST and FOLLOW sets, a table is constructed where each cell corresponds to a non-terminal and a terminal.
4. **Parse Input String**:
   - A stack-based approach is used to parse the string using the table.
   - Actions like match (POP), push production rule, or rejection are shown step-by-step.

## 📥 Sample Input

```yaml
Enter number of productions: 4
Enter productions:
E=TR
R=+TR
R=#
T=FY
...
Enter the input string: id+id*id
```

## 📤 Sample Output

```yaml
First(E)= { id }
First(R)= { +, # }
First(T)= { id }
...

Follow(E)= { $, ) }
Follow(R)= { $, ) }
...

The LL(1) Parsing Table:
| id + * ( ) $
E | E=TR
R | R=+TR R=# R=#
...

Stack Input Action
$E id+idid E=TR
$R id+idid T=FY
...
String ACCEPTED!
```


## 🌍 Real-World Applications

- **Compiler Design**: LL(1) parsers are foundational in constructing the syntax analysis phase of a compiler.
- **Language Processing Tools**: Used in interpreters and language tools like linters and formatters.
- **Syntax Checking**: Ensures structured data (e.g., config files, DSLs) adheres to predefined rules.

## 🛠 How to Run

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/ll1-parser-c.git
   cd ll1-parser-c
   ```
2. Compile the program:
   ```bash
   gcc ll1_parser.c -o ll1_parser
   ```
3. Run the program:
   ```bash
   ./ll1_parser
   ```

   

