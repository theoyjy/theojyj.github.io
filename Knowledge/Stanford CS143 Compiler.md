[Anarion-zuo/Stanford-CS143 (github.com)](https://github.com/Anarion-zuo/Stanford-CS143)
# Overall

>[!Abstract] Structure of a Compiler
> 1. Lexical Analysis -- identify words (*not trivial*)
> 2. Parsing -- identify sentences = diagramming 
>![[Stanford CS143 Compiler-20240507131428013.webp|412]]
> 3. Semantic Analysis -- analyze sentences
> 	-- there are many types, for example: **variable bindings**
> 		```
> 			int i = 3;
> 			{
> 				int i = 4;
> 				std::cout << i; // use the inner local variable
> 			}
> 		```
> 1. Optimization -- editing => **To run faster, use less memory, conserve some resources**
> 	for example: `x=y*0 ==> x = 0`
> 2. Code Generation -- translation

## IR
>[!INFO] Intermediate Representations(IR)
> IRs are generally ordered in descending level of abstraction
> * highest is source
> * lowest if assembly
>![[Stanford CS143 Compiler-20240507132433440.webp|200]]
>
>IRS are useful because lower levels expose features hidden by higher levels:
>* registers
>* memory layout
>* raw pointers
>* ...
>
>But lower levels **obscures** high-level meaning:
>* classes
>* higher-order functions
>* even loops
>

## Abstraction
>[!Success] Benefits of Abstraction
>* detached from concrete details -- selective ignorance
>* necessary to build any complex system -- expose only essentials
>* Modes of abstractions:
>	* Via languages/compilers: high-level code, few machine dependencies
>	* Via functions and subroutines: Abstract interface to behavior
>	* Via modules: Export interfaces, hide implementation
>	* Via classes/abstract data types: Bundle data with its operations

## Method
>[!Warning] Method Table
>![[Stanford CS143 Compiler-20240507143749354.webp]]
>![[Stanford CS143 Compiler-20240507143827618.webp]]
>

# Lexical Analysis

## Outline
>[!warning] Issues
>1. look ahead:
>	may be required to decide where one token ends and the next token begins, for instance:
>		![[Stanford CS143 Compiler-20240507150805159.webp|94]]
>1. ambiguities

>[!success] Goal: Partition input string into substrings(tokens)

### Tokens
#### Definition
>[!info] A token class corresponds to a set of strings:
>1. Identifier: name of variables, methods, class, modules (strings of letters or digits, starting with a letter)
>2. Integer: a non-empty string of digits
>3. Keyword: `else`, `if`, `while`...
>4. Whitespace: a non-empty sequences of blanks, newlines and tabs

#### Purposes
>[!Important]
>1. Classify program substrings according to role
>2. Produces a stream of tokens, which are the inputs to the parser


## Design a Lexical Analyzer
### 1. **Define a finite set of tokens**
	* Tokens describe all items of interest • Identifiers, integers, keywords 
	* Choice of tokens depends on • language • design of parse
	![[Stanford CS143 Compiler-20240507145935033.webp|491]]
>[!tip] usually **discards “uninteresting” tokens** that don’t contribute to parsing: **whitespace, comments**

### 2. Describe which strings belong to each token
	The lexer thus returns token-lexeme pairs – And potentially also line numbers, file names, etc. to improve later error messages
