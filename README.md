# MAC0499 - Trabalho de formatura supervisionado

Repositório do meu Trabalho de conclusão de curso no IME-USP @ 2022. [Veja aqui](./monografia/monografia.pdf) a monografia.

## Como executar

Neste projeto, utilizamos a ferramenta de copilação e teste [Bazel](https://bazel.build/), junto com o framework [Google Test](https://github.com/google/googletest) para testes unitários.

### Union-Find retroativo

Para copilar, basta usar:

```bash
$ bazel build //retroactiveUnionFind:retroactive-union-find
```

Ja para executar os testes, execute:

```bash
$ bazel test //retroactiveUnionFind:retroactive-union-find-test
```