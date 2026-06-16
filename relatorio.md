# Relatorio - Parte 2 do Trabalho Pratico
**Aluno**: Caio Justino
**Disciplina**: Algoritmos e Estruturas de Dados II - UFOP

---

## Entidade escolhida

Os metodos da Parte 2 foram implementados somente para a entidade **Filme**,
conforme permitido pelo enunciado. A base desordenada usada nos testes eh
gerada pelo proprio TAD de filmes.

---

## Metodos escolhidos

- **Questao 1** (ordenacao em disco): **Selection Sort em Disco**.
  Foi escolhido por ser simples, trabalhar diretamente no arquivo e ser
  diferente do Insertion Sort usado na Parte 1.

- **Questao 2** (geracao de particoes ordenadas): **Selecao com Substituicao**.
  O metodo usa uma area de memoria com M registros, gera particoes ordenadas
  e congela registros que pertencem a proxima particao.

- **Questao 3** (intercalacao): **Intercalacao Otima**.
  O metodo intercala ate F-1 particoes por fase, mantendo uma saida por fase,
  reduzindo o numero de passadas necessarias sobre os arquivos.

---

## Resultados dos testes (Questao 4)

Os tempos foram medidos em maquina local. Para o Selection Sort em bases de
100.000 e 500.000 registros, foi usada **extrapolacao matematica**, pois a
complexidade O(N^2) torna a execucao real muito demorada.

A extrapolacao usa:

```
tempo_estimado(N) = tempo_medido(1000) * (N / 1000)^2
```

### Tabela comparativa

| Base    | Selection Sort em Disco            | Selecao + Intercalacao |
|---------|------------------------------------|------------------------|
| 1.000   | 1,5990 s (medido)                  | 0,0080 s               |
| 10.000  | 164,0910 s (medido)                | 0,1110 s               |
| 100.000 | 15.990,0 s (extrapolado, O(N^2))   | 1,6810 s               |
| 500.000 | 399.750,0 s (extrapolado, O(N^2))  | 9,4510 s               |

Os logs completos dos testes estao em `log_q4.txt`.

---

## Conclusao

O **Selection Sort em Disco** funciona corretamente, mas seu custo cresce muito
rapido porque o metodo faz muitas comparacoes e acessos ao arquivo. Por isso,
ele eh adequado apenas para bases pequenas ou para demonstracao didatica.

A combinacao **Selecao com Substituicao + Intercalacao Otima** foi muito mais
eficiente para bases grandes. Ela aproveita uma area limitada de memoria para
gerar particoes ordenadas e depois intercala essas particoes ate formar o
arquivo final ordenado.

A conclusao pratica eh que, para arquivos grandes, os metodos de ordenacao
externa sao mais adequados que metodos simples de ordenacao direta em disco.

---

## Como executar

Compilacao:

```
gcc -o sistema.exe main.c filme.c usuario.c favorito.c buscaSequencial.c buscaBinaria.c insertionSort.c log.c operacoes.c interacoes.c selectionSortDisco.c selecaoSubstituicao.c intercalacaoOtima.c testesParte2.c
```

No Windows, tambem eh possivel executar:

```
compilar.bat
```

Execucao:

```
.\sistema.exe
```

No menu inicial:

- **1** executa a Parte 1: CRUD, buscas, logs e interacoes entre entidades.
- **2** executa a Parte 2: ordenacao externa sobre a entidade Filme.

Na Parte 2:

- **Opcao 1** demonstra o Selection Sort em Disco.
- **Opcao 2** demonstra Selecao com Substituicao + Intercalacao Otima.
- **Opcao 3** executa os testes comparativos da Questao 4.
