# Graph Theory Project

project developed as an evaluation activity for the Graph Theory discipline at the Federal University of Alagoas.

## Algorithms

- __Dijkstra__
- __Prim__
- __Kosaraju__
- __Kruskal__
- __Floyd-Warshall__

Each algorithm must pass a rigorous battery of tests, tests present in the "Bat1" folder, in addition to a second battery of tests, provided by the teacher in the classroom. The Floyd-Warshall algorithm in particular will undergo a battery of tests provided by myself, present in "__BatMANN__" folder, as part of the evaluation.

## giving execution permission to .sh files

go to the folder where your "file.sh" is located and open the terminal in the folder, type the following command in the terminal:

```bash
chmod +x file.sh
```

Now you can run the file with the command ./file.sh in the terminal.

## Makefile

Each algorithm has a folder, named after the algorithm, and a Makefile.

- __Makefile structure__

each Makefile has 3 commands

```bash
make
```

The basic command, when giving this command the algorithm in the folder will be compiled and moved to the test folder, so that the test can be executed, be sure you moved every other archive to the test folder, before giving this command.

```bash
make run
```

This command will compile the algorithm and run a test, present in the "entrada.txt" file, after which the output will be stored in a file called "saida.txt" in the same folder as the algorithm.

```bash
make move
```

This command will compile the algorithm and move it to the test folder, "__Bat1__" or "__BatMANN__", depending on which algorithm folder you are in.

## Alunos

- Davi Vieira Lourenço Correia ✉️(<dvlc@ic.ufal.br>)
- Wellington Cezario dos Santos ✉️(<wcs@ic.ufal.br>)
