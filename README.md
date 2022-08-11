# MAC0499 - Capstone Project

Repository of my Bachelor’s dissertation work at the Department of Computer Science of the University of São Paulo, Brazil.

Access the work page [here](https://linux.ime.usp.br/~felipen/mac0499/).

## Abstract

Retroactive data structures allow operations to be performed not only in the current state of the structure, but also in any of its past states. Furthermore, a link-cut tree is a data structure that allows the maintenance of a forest of rooted trees with weighted edges, and where the nodes of each tree have an arbitrary number of children. Such structure is widely used as a basis for the development of retroactive data structures, and in this work we will study the retroactive versions of the union-find and minimum spanning forest problems. To do so, we implement these structures in C++ and describe the ideas behind how they work. Furthermore, we present an improvement of the solution originally presented for the retroactive minimum spanning forest, which removes limitations without worsening its performance.

## Resumo

Estruturas de dados retroativas permitem a realização de operações que afetam não somente o estado atual da estrutura, mas também em qualquer um de seus estados passados. Além disso, uma link-cut tree é uma estrutura de dados que permite a manutenção de uma floresta de árvores enraizadas com peso nas arestas, e onde os nós de cada árvore possuem um número arbitrário de filhos. Tal estrutura é muito utilizada como base para o desenvolvimento de estruturas de dados retroativas, e neste trabalho estudaremos as versões retroativas dos problemas de union-find e floresta geradora mínima.  Para isso, implementamos essas estruturas em C++ e descrevemos as ideias por trás de seus funcionamentos. Ademais, apresentamos uma melhoria da solução originalmente apresentada para a floresta geradora mínima retroativa, que retira limitações sem piorar sua performance.

## How to run

In this project, we used the testing and building tool [Bazel](https://bazel.build/), alongside [Google Test](https://github.com/google/googletest) framework for unity tests.

The table below shows the commands to build and test each of the presented structures.

| Structure | Build | Test |
| --- | --- | --- |
| Link-Cut Tree | `bazel build //implementations:link-cut-tree` | `bazel test --test_output=all //implementations:link-cut-tree-test` |
| Retroative Union-Find  | `bazel build //implementations:retroactive-union-find` | `bazel test --test_output=all //implementations:retroactive-union-find-test` |
| Incremental MSF  | `bazel build //implementations:incremental-msf` | `bazel test --test_output=all //implementations:incremental-msf-test` |
| Semi-Retroative MSF | `bazel build //implementations:semi-retroactive-msf` | `bazel test --test_output=all //implementations:semi-retroactive-msf-test` |
