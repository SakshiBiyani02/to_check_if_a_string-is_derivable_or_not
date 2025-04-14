# To check whether a string is derivable or not from a given grammer 
## Aim: 
To implement a bottom-up parsing algorithm using a queue-based approach to simulate 
the parsing of a string based on a given context-free grammar (CFG). The program also provides 
tracing of the steps taken during the parsing process, allowing the user to see how the input string 
is being matched against the grammar productions. 
Compiler used: GCC (GNU Compiler Collection) 
Editor used : gedit 
## Algorithm 
1.  Input and Grammar Setup: 
• The program first takes the number of non-terminals in the grammar. 
• For each non-terminal: 
o The program takes the name of the non-terminal. 
o The number of productions for that non-terminal is inputted. 
o Each production is inputted as a string of symbols, where the symbols could be terminals or 
non-terminals. 
• Then, the program takes the input string that needs to be parsed. 
2.  Tokenization of Input: 
• The input string is split into tokens (characters) that will be matched against the grammar symbols. 
3.  Queue Initialization: 
• The parsing process is simulated using a queue: 
o The initial state is created with the start symbol (first non-terminal) and an input position 
pointing to the beginning of the input string. 
o This state is enqueued to begin the parsing process. 
4.  Parsing Process (Main Loop): 
• The main loop processes the queue: 
o Dequeue a state from the front of the queue. 
o Check if all symbols have been processed: 
▪ If the symbols are empty and the input position has reached the end of the input, the 
string is accepted. 
o If the front symbol is a non-terminal: 
▪ For each production of the non-terminal, apply the production by replacing the 
non-terminal with the symbols of the production. 
▪ The new state (with updated symbols) is enqueued. 
o If the front symbol is a terminal: 
▪ Match it with the current symbol from the input string. 
▪ If it matches, update the input position and move forward to the next state. 
o If a terminal or non-terminal can't match, the string is rejected. 
5.  Tracing the Parsing Process: 
• For each step of the parsing process (both production applications and terminal matches): 
o Print the current state: including the symbols being processed and the current input 
position. 
o Print the production applied or the terminal matched for each step. 
6.  Termination: 
• If the parsing finishes with the input string fully processed and accepted, print "String is accepted." 
• Otherwise, print "String is rejected."
## Input
The given context free grammar is : 
S-> AA 
A->aA|b

Case 1 :  
Input : aabb 

Case 2: 
Input : ab 
 
Case 3: 
Input : ababab 
 
Case 4 
Input : aaaaaab 

Case 5: 
Input : abb 
## Conclusion: 
In this program, we have implemented a bottom-up parser using a queue-based approach to 
simulate the parsing of a string against a given context-free grammar (CFG). The key feature of 
this implementation is the ability to trace the parsing process, which is helpful in understanding 
how the input string is gradually processed according to the grammar’s productions. 
The tracing feature was added to ensure that the path taken by the parser is clearly visualized. By 
printing each step, including the symbol being processed and productions applied, users can 
observe how the program moves through the grammar and matches the input string. This tracing of 
the path adds a level of clarity and transparency, making the parsing process more 
understandable, especially for educational purposes or debugging. 
The approach demonstrates a queue-based simulation of a parsing algorithm where non
terminals are progressively expanded into their respective productions, and terminals are matched 
to the input string. If a string is successfully parsed, the program outputs “String is accepted”; 
otherwise, it outputs “String is rejected.” 
To ensure uniqueness in this implementation, tracing the parsing path at each significant step is 
included. This feature allows the program to provide an in-depth look at how the parser processes 
the input string, providing a clear, step-by-step visualization of the parsing process. 
Overall, the implementation serves as a functional and informative tool for demonstrating the 
principles of context-free grammar parsing, with added traceability for improved understanding 
and debugging.
