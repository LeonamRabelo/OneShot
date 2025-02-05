﻿# OneShot
Temporizador de um disparo (One Shot).

**Descrição**
Todos os LEDs iniciam apagados. Ao pressionar o botão, todos são acesos. Em seguida, os LEDs são apagados um a um, até que todos estejam desligados. Durante esse processo, pressionar o botão novamente não terá efeito até que a sequência atual seja concluída.

# Compilando e Executando

- Necessário:
Instale o SDK do Raspberry Pi Pico e configure o ambiente de desenvolvimento.
VSCode com as extensões "Raspberry Pi Pico Project" e "Wokwi Simulator".
CMake

- Importe o projeto (pasta) a partir da extensão do Raspberry Pi Pico Project
- Compile o projeto, também por meio da extensão.

**No Wokwi VScode:**
- Abra o arquivo 'diagram.json' e execute (Play).

*Utilizando a placa física, como a BitDogLab:*
- Envie o arquivo gerado (.uf2) para a placa Raspberry Pi Pico.

**Dependências**
Este projeto requer a biblioteca pico-sdk, que deve estar corretamente configurada no ambiente de desenvolvimento.

# Vídeo utilizando a BitDogLab e simulando no Wokwi
Link para o vídeo: https://www.youtube.com/watch?v=70ny3v7k5_o
Ps.: Lembrando que na placa BitDogLab a sequeência de cores RGB ativos serão: Branco (Vermelho + Verde + Azul ativos), Vermelho + Verde, e Verde.
