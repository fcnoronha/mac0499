# MAC0499 - Trabalho de formatura supervisionado

Repositório do meu Trabalho de conclusão de curso no IME-USP @ 2022. [Acesse aqui](https://linux.ime.usp.br/~felipen/mac0499/) a pagina do trabalho.

## Como executar

Neste projeto, utilizamos a ferramenta de copilação e teste [Bazel](https://bazel.build/), junto com o framework [Google Test](https://github.com/google/googletest) para testes unitários.

A tabela abaixo mostra os comandos para copilar e testar cada uma das estruturas apresentadas.

| Estrutura | Copilar | Testar |
| --- | --- | --- |
| Link-Cut Tree | `bazel build //implementations:link-cut-tree` | `bazel test --test_output=all //implementations:link-cut-tree-test` |
| Union-Find Retroativo | `bazel build //implementations:retroactive-union-find` | `bazel test --test_output=all //implementations:retroactive-union-find-test` |
| MSF Incremental | `bazel build //implementations:incremental-msf` | `bazel test --test_output=all //implementations:incremental-msf-test` |
