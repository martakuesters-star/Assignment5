# Small Language Model (SLM)
Marta Florindo Kuesters | Assignment 5 | DA4007

## Description (Lab Report)
This project implements an "Artificial Idiot," a small language model that generates text based on a given training file. It works by breaking the input text into $k$-grams (sequences of characters of length $k$) and calculating the transition probabilities for the character that immediately follows each $k$-gram. 

The software utilizes a Markov chain algorithm to generate new text. It selects a starting $k$-gram based on its frequency in the training data, then iteratively samples subsequent characters using the calculated probability distribution (`std::discrete_distribution`). 

To handle $k$-grams that might not have a specific transition in the training text, the model supports an optional pseudocount ($\alpha$). This applies Laplace smoothing, allowing for a little "creativity" in the generated text by assigning a small non-zero probability to unobserved character transitions.

## Project Structure
* `src/main.cpp`: Entry point, handles user error exceptions.
* `src/appslm.h` / `src/appslm.cpp`: Manages command-line arguments and application flow.
* `src/slm.h` / `src/slm.cpp`: Core mathematical model, manages file reading, state transitions, and random generation.
* `Makefile`: Build instructions.

## How to Compile
The project includes a Makefile for easy compilation. Open your terminal in the top project directory (where the Makefile is located) and run:

```bash
make
```

This will compile the source code in the `src/` folder and create an executable named `slm` in the top directory. To remove the compiled object files and the executable, run:

```bash
make clean
```

## How to Use
The tool is run from the command line and takes three required arguments, plus one optional argument for the pseudocount.

**Syntax:**
```bash
./out/slm [-a alpha] <k> <training_file> <output_length>
```

* `-a alpha` (Optional): A non-negative floating-point number representing the pseudocount. If omitted, defaults to `0`.
* `k`: An integer determining the size of the $k$-gram (word size). Must be a positive integer.
* `training_file`: The path to the plain ASCII text file used to train the model.
* `output_length`: The total number of characters to generate (including the starting $k$-gram). Must be at least `k`.

### Examples

**Basic run (k=2, output length of 40 characters):**
```bash
./out/slm 2 moby_dick.txt 40
```

**Run with a pseudocount ($\alpha = 0.01$, k=3, output length of 100 characters):**
```bash
./out/slm -a 0.01 3 moby_dick.txt 100
```