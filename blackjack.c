#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Comeco com 1000 pontos
    int saldo = 1000, sucessoScan = 0;

    // Vetor com os nomes das cartas pra deixar as mensagens bonitinhas
    const char *nomes[] = {"As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Valete", "Dama", "Rei"};

    printf("Bem-vindo ao 21");

    // Loop principal: roda enquanto o jogador tiver saldo
    while (saldo > 0)
    {
        printf("\nPontuacao atual: %d\n", saldo);

        int aposta;

        // Pede uma aposta valida ao jogador
        do
        {
            printf("Quanto deseja apostar? (entre 1 e %d) ", saldo);
            sucessoScan = scanf("%d", &aposta);

            // Verifica se a aposta esta dentro dos limites
            if (sucessoScan != 1 || aposta <= 0 || aposta > saldo)
            {
                printf("Aposta invalida. Tente novamente.\n");
                fflush(stdin);
                sucessoScan = 0;
            }
        } while (sucessoScan != 1);

        int corte;

        // Pede o corte do baralho (vai ser usado como seed do rand)
        do
        {
            printf("Corte o baralho (informe um numero entre 1 e 52): ");
            sucessoScan = scanf("%d", &corte);

            if (sucessoScan != 1 || corte < 1 || corte > 52)
            {
                printf("Valor invalido. Tente novamente.\n");
                fflush(stdin);
                sucessoScan = 0;
            }
        } while (sucessoScan != 1);

        // Variaveis principais da rodada
        int carta, valorCarta, totalJogador = 0, totalBanca = 0, qtdAsJogador = 0, qtdAsBanca = 0;
        char opcao;
        int contadorCartas[13] = {0}; // Aqui eu vou contar quantas vezes cada carta ja saiu (maximo 4 por tipo)

        srand(corte); // Semente aleatoria com base no corte

        // Sorteio da primeira carta do jogador, garantindo que nao passou de 4 repeticoes
        do {
            carta = rand() % 13 + 1;
        } while (contadorCartas[carta - 1] >= 4);
        contadorCartas[carta - 1]++;

        // Definindo o valor da carta sorteada
        if (carta == 1)
        {
            valorCarta = 11;
            qtdAsJogador += 1;
        }
        else if (carta >= 11 && carta <= 13)
        {
            valorCarta = 10;
        }
        else
        {
            valorCarta = carta;
        }

        totalJogador += valorCarta;

        // Mostra a carta e o total atual
        printf("\nSua carta:\n");
        printf(" - %s (%d pontos)\n", nomes[carta - 1], valorCarta);
        printf("Total: %d pontos\n", totalJogador);

        // Jogador decide se quer continuar
        while (totalJogador < 21)
        {
            do
            {
                fflush(stdin);
                printf("\nDeseja retirar outra carta? (s/n): ");
                sucessoScan = scanf(" %c", &opcao);

                if (sucessoScan != 1 || (opcao != 's' && opcao != 'S' && opcao != 'n' && opcao != 'N'))
                {
                    printf("Opcao invalida. Digite novamente (s/n).\n");
                    fflush(stdin);
                    sucessoScan = 0;
                }
            } while (sucessoScan != 1);

            if (opcao == 'n' || opcao == 'N')
            {
                break;
            }

            // Nova carta sorteada (com limite de 4 vezes por tipo)
            do {
                carta = rand() % 13 + 1;
            } while (contadorCartas[carta - 1] >= 4);
            contadorCartas[carta - 1]++;

            if (carta == 1)
            {
                valorCarta = 11;
                qtdAsJogador += 1;
            }
            else if (carta >= 11 && carta <= 13)
            {
                valorCarta = 10;
            }
            else
            {
                valorCarta = carta;
            }

            totalJogador += valorCarta;

            printf("\nVoce retirou: %s (%d pontos)\n", nomes[carta - 1], valorCarta);
            printf("Total: %d pontos\n", totalJogador);

            // Se passou de 21 e tem As, transforma As de 11 pra 1
            if (totalJogador > 21 && qtdAsJogador > 0)
            {
                printf("\n=====================================================");
                printf("\nVoce ultrapassou os 21 pontos e teve %d As sorteado(s)", qtdAsJogador);
                printf("\n=====================================================");
                printf("\nPor isso, %d pontos serao subtraidos do seu total\n", qtdAsJogador * 10);

                totalJogador -= qtdAsJogador * 10;
                qtdAsJogador = 0;
                printf("Novo total: %d pontos\n", totalJogador);
            }
        }

        // Verifica se o jogador perdeu direto
        if (totalJogador > 21)
        {
            printf("\nVoce estourou! A banca venceu!\n");
            saldo -= aposta;
        }
        else
        {
            if (totalJogador == 21)
            {
                printf("\nVoce fez 21 pontos! Nem deu chance para a banca jogar!\n");
            }
            else
            {
                printf("\nBanca revela as cartas...\n");

                while (totalBanca < 17)
                {
                    // Sorteio da banca com limite de 4 cartas
                    do {
                        carta = rand() % 13 + 1;
                    } while (contadorCartas[carta - 1] >= 4);
                    contadorCartas[carta - 1]++;

                    if (carta == 1)
                    {
                        valorCarta = 11;
                        qtdAsBanca += 1;
                    }
                    else if (carta >= 11 && carta <= 13)
                    {
                        valorCarta = 10;
                    }
                    else
                    {
                        valorCarta = carta;
                    }

                    totalBanca += valorCarta;

                    printf("Banca retirou: %s (%d pontos) | Total: %d\n", nomes[carta - 1], valorCarta, totalBanca);

                    if (totalBanca > 21 && qtdAsBanca > 0)
                    {
                        printf("\n========================================================");
                        printf("\nA banca ultrapassou os 21 pontos e teve %d As sorteado(s)", qtdAsBanca);
                        printf("\n========================================================");
                        printf("\nPor isso, %d pontos serao subtraidos do total da banca\n", qtdAsBanca * 10);

                        totalBanca -= qtdAsBanca * 10;
                        qtdAsBanca = 0;
                        printf("Novo total da banca: %d pontos\n", totalBanca);
                    }
                }

                // Mostra resultado da rodada
                printf("Seu total: %d\n", totalJogador);
                printf("Total da banca: %d\n", totalBanca);
            }

            // Decide vencedor da rodada
            if (totalBanca > 21 || totalJogador > totalBanca)
            {
                printf("Voce venceu!\n");
                saldo += aposta;
            }
            else if (totalJogador == totalBanca)
            {
                printf("Empate! Aposta devolvida.\n");
            }
            else
            {
                printf("A banca venceu!\n");
                saldo -= aposta;
            }
        }

        // Condicao de fim de jogo
        if (saldo <= 0)
        {
            printf("\nVoce ficou sem pontos.\nFim de jogo.\n");
            break;
        }
        else if (saldo >= 10000)
        {
            printf("\nA banca quebrou! Parabens, voce venceu!");
            printf("\nPontuacao final: %d", saldo);
            printf("\nFim de jogo.\n");
            break;
        }

        // Pergunta se o jogador quer continuar jogando
        do
        {
            fflush(stdin);
            printf("\nDeseja jogar outra rodada? (s/n): ");
            sucessoScan = scanf(" %c", &opcao);

            if (sucessoScan != 1 || (opcao != 's' && opcao != 'S' && opcao != 'n' && opcao != 'N'))
            {
                printf("\nOpcao invalida. Digite novamente (s/n).\n");
                fflush(stdin);
                sucessoScan = 0;
            }
        } while (sucessoScan != 1);

        if (opcao == 'n' || opcao == 'N')
        {
            printf("\nPontuacao final: %d\nObrigado por jogar 21! Ate a proxima!", saldo);
            break;
        }
    }

    return 0;
}