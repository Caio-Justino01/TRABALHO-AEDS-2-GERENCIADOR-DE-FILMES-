@echo off
gcc -Wall -Wextra -o sistema.exe main.c filme.c usuario.c favorito.c buscaSequencial.c buscaBinaria.c insertionSort.c log.c operacoes.c interacoes.c selectionSortDisco.c selecaoSubstituicao.c intercalacaoOtima.c testesParte2.c
if errorlevel 1 (
    echo.
    echo Erro na compilacao.
    pause
    exit /b 1
)
echo.
echo Compilacao concluida: sistema.exe
pause
