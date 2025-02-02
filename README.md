Embarcatech

Tarefa da aula sincronado dia 27/01/2025

Aluno: Fábio Rocha Gomes Jardim  

Matrícula: TIC370100723  

## Vídeo    

https://drive.google.com/file/d/1KALqekmMrLb0E-MRqnojNJxBF86jWwVj/view?usp=sharing

## Análise e Explicação do Código   

Este código C, escrito para a plataforma BitdogLab (Raspberry Pi Pico W), controla uma matriz de LEDs usando o Peripheral Input/Output (PIO) e exibe números de 0 a 9. O código também inclui botões para incrementar e decrementar o número exibido. 

### Funcionalidades Principais: 

Exibição de Números: Uma matriz multidimensional armazena a representação de cada número, que é então mapeada para os LEDs da matriz.   

Controle por Botões: Dois botões controlam o incremento e decremento do número exibido.     

PIO: O PIO é utilizado para controlar os LEDs de forma eficiente, permitindo a criação de padrões.    

Debouncing: Um algorítmo simples de debouncing é implementado para evitar leituras espúrias dos botões.

### Explicação Detalhada:   

Inclusão de Bibliotecas: Inclui as bibliotecas necessárias para interagir com o hardware do Raspberry Pi Pico, como stdio.h, stdlib.h, e as bibliotecas específicas do Pico.    

Definições: Define os pinos dos LEDs, botões, número total de LEDs na matriz, pino do PIO e outras constantes.    

Variáveis Globais: Declara variáveis para armazenar o número atual, o tempo anterior para debouncing, e os handles do PIO e estado da máquina de estado.    

Matriz de Números: Uma matriz multidimensional armazena a representação de cada número. Cada elemento da matriz representa um pixel da matriz de LEDs e contém informações sobre a intensidade de cada cor (vermelho, verde, azul).   

Função matrix_rgb: Converte os valores RGB em um formato adequado para os LEDs WS2812, que utilizam o formato GRB.  

Função desenho_pio: Utiliza o PIO para desenhar o número atual na matriz de LEDs, percorrendo cada linha e coluna da matriz de números e configurando os LEDs correspondentes.  

Função call_back_dos_botoes: Função de callback que é chamada quando um dos botões é pressionado. Implementa a lógica para incrementar ou decrementar o número exibido e chama a função desenho_pio para atualizar a exibição.  

Funções de Inicialização: Inicializam os GPIOs, o PIO e configuram as interrupções para os botões.  

Loop Principal: O loop principal pisca um LED vermelho, 5  vezes porsegundo, para indicar que o programa está em execução.  

### Como Usar:  

Hardware: BitdogLab.    

Configure o ambiente de desenvolvimento para a Raspberry Pi Pico W, utilizando o SDK da Raspberry Pi.     

Certifique-se de incluir o arquivo pio_matrix.pio.h e seu respectivo programa PIO, que contém a lógica para comunicação com os LEDs WS2812.     

Software: Compile e carregue o código no Raspberry Pi Pico W.   

Funcionamento: Ao pressionar os botões, o número exibido na matriz de LEDs será incrementado ou decrementado. O LED vermelho piscará continuamente para indicar que o programa está em execução.  

### Pontos Chave:   

PIO: O uso do PIO permite um controle preciso e eficiente dos LEDs, permitindo a criação de animações e efeitos visuais complexos.  

Flexibilidade: A matriz de números pode ser facilmente modificada para exibir outros símbolos ou padrões.   

Eficiência: A função matrix_rgb otimiza a conversão de cores para o formato GRB.    

Debouncing: O mecanismo de debouncing evita que os botões sejam lidos múltiplas vezes por uma única pressão.    

### Possíveis Melhorias:    

Animações: Implementar animações mais complexas, como transições suaves entre números.  

Efeitos Visuais: Adicionar efeitos visuais como brilho, fade-in/fade-out e cores aleatórias.    

Interface de Usuário: Criar uma interface de usuário mais intuitiva, por exemplo, utilizando um display LCD para mostrar o número atual.    

Configuração: Permitir a configuração do número de LEDs, tamanho da matriz e outros parâmetros através de um arquivo de configuração.   

Este código serve como um excelente ponto de partida para projetos mais complexos envolvendo o controle de LEDs e o uso do PIO no Raspberry Pi Pico.

## Observações:

O código assume que o arquivo pio_matrix.pio.h contém a definição do programa PIO para controlar os LEDs.   

A lógica de inversão das linhas e colunas na função desenho_pio foi adicionada para corrigir um problema específico de visualização na bitdoglab.   

Os valores dos multiplicadores na função matrix_rgb podem ser ajustados para controlar o brilho dos LEDs.   
