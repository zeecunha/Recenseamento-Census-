# Recenseamento-Census-
Este projeto tem como finalidade implementar, parcialmente, alguns algoritmos de processamento de um sistema de informação de recenseamento de pessoas de uma freguesia de Portugal || This project aims to partially implement some algorithms for processing a census information system for people from a parish in Portugal.

Não se pretende que desenvolva uma interface de utilizador completamente funcional.
Pretende-se que desenvolva uma API de funções que satisfaçam os requisitos listados a seguir e funções de teste tal como descrito. De seguida descreve-se a lista dos requisitos a cumprir neste projeto de programação. O programa desenvolvido deverá permitir:

R1. Fazer a ordenação das pessoas no sistema usando ordenação tipo string sorting (LSD e MSD). Deverá poder fazer a ordenação por nif, nome, data de nascimento ou código postal.

R2. Deverá permitir, usando conectividade dinâmica, suportar a implementação de uma API union-find no conjunto de pessoas, usando a ligação familiares diretos para unir pessoas a outras pessoas e testar se duas pessoas estão ligadas por um caminho constituído por familiares diretos.

R3. Fazer a pesquisa de pessoas nas estruturas ordenadas, por nif, nome, data de nascimento ou código postal, usando pesquisa binária.

R4. Disponibilizar funções para inserir, remover, editar e listar pessoas na base de dados.

R5. Listar todas as pessoas da base de dados (e escrever em ficheiro de texto).

R6. Permitir a manipulação das estruturas de dados (e respectivas funcionalidades solicitadas) através da entrada e saída de dados via ficheiros de texto.

R7. Correr cenários de teste (funções de teste) para todas as funcionalidades implementadas. Deverá implementar mecanismos / instrumentos de medição temporal da execução das principais funções de ordenação e pesquisa nesses testes. Esses cenários deverão incluir nos testes a leitura e escrita de ficheiros com dados. Os resultados dos testes deverão ser escritos para ficheiro de texto.
Para cada teste realizado deverá ser explicitada (no ficheiro de texto) a função testada e o resultado do teste.
