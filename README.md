# The quadratic equation!)

Hello everyone, I present to your attention the best program for solving quadratic equations in the most effective way — using the discriminant.

This amazing program has many features, which will be described below, but believe me, it’s really worth checking out (the most important thing is that it includes nanoAi, which will never let you get bored).

*nanoAi: эртээртэ*

## Building quard

If you want to build my program and experiment with it yourself, you can simply run 
```sh
build.bat
``` 
on your device after installing my project. The program will greet you and provide further instructions on how to proceed.

### Compilation flags

In the current version of the program, only compilation with a single flag is available.

But still, the flags are really cool; you can familiarize yourself with them by entering `--help`; you can learn more about what the flags do by reviewing the **console_helper.h** file or down in README.


- **--help**  *Shows the list of cmd commands to user*
- **--token count** *Gives extra tokens to user (only for admin mode!!!)*
- **--version** *Shows the current version of "Quard"*
- **--quiert** *Turns the program into little one, only for counting simple quadrs*
- **--loud** *Make AI to SHOUT*
- **--tester quard** *Runs tests for a quard_eq from some file, shows how good my solver is in solving eq.*
- **--tester parser** *Runs tests for a parser from some file, shows how good this parser at getting coefs.*

## Program features

### Working with files

You can read the coefficients of a quadratic equation from a certain file and write them to another file in a convenient and visually appealing format.

<img width="1086" height="446" alt="files_work_demonstration" src="https://github.com/user-attachments/assets/56fe2dc8-8b80-48fe-8214-70c0462b2003" />

You can also run the tester `--tester parser` or `--tester quard` from files (samples are in the examples folder).

<img width="704" height="961" alt="quard_tester" src="https://github.com/user-attachments/assets/e591094b-d4c3-4a66-82b6-da3fd3faa71c" />
<img width="866" height="590" alt="parser_tester" src="https://github.com/user-attachments/assets/855f7825-287c-4cf9-91c3-a017d84ed8cb" />

### Parser

You can parse quadratic equations of various types. The main input methods are shown in the image above. The parser supports a different number of terms and analyzes the equation on both sides of the equal sign, taking into account the sign of the expression. Currently, the parser does not support parentheses, multiplication and division symbols, or various other exotic operations not shown in the image above.
To enter parser mode, select standard input (stdin) and start entering the expression, first entering the underscore character.

### Graph of a parabola

If you are interested in the graphical aspect of mathematics, you can use the built‑in functions for constructing a parabola (this can be done simply by pressing the symbol p (from the English “parabola”)) after calculating the roots of the corresponding equation. After constructing a parabola based on the entered quadratic equation, you can also experiment with another way of entering the function — using three points (to use this function, simply follow the instructions that will appear after constructing the first parabola).

Attention! Be careful! For now, the parabola is only built on a 15 × 15‑unit field; if these values are exceeded, the function simply won’t be displayed.

<img width="379" height="451" alt="parabola_by_coefs" src="https://github.com/user-attachments/assets/a172ee58-3011-4b45-9827-949e5c6f28d2" />   <img width="504" height="451" alt="parabola_by_dots" src="https://github.com/user-attachments/assets/468fa486-ed0c-4c4d-ba1d-2ccae55f081f" />

### NanoAi
In order not to be bored, my program also has your little friend, nanoAi. He will keep an eye on you and count your tokens) If you don't have enough tokens, he can kindly provide you with some more in a kind way. You can also have fun playing tic tac toe with him.
<img width="1162" height="708" alt="ai_show" src="https://github.com/user-attachments/assets/84ede156-350f-418b-9a0e-3f004c2911f8" />

### Other small details
#### Support for complex numbers
The program can solve equations in complex numbers, compare them, and display the results in a visually appealing way.
#### Beautiful display of equations
The program does not display leading zeros and ones; it tries to bring equations to a uniform form to improve readability.
#### A competent error handler
It handles various input format errors, verifies the correctness of the entered files, and considers extreme cases when solving the equation.
