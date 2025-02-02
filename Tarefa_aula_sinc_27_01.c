#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

// Arquivo .pio
#include "pio_matrix.pio.h"

// Definições
#define LED_R 13
#define LED_G 12
#define LED_B 11
#define BOT_A 5
#define BOT_B 6
#define LED_COUNT 25
#define LED_PIN 7

// Variáveis globais
static volatile int numero_exibido = 0;
static volatile uint32_t tempo_anterior = 0;
static PIO pio;
static uint sm;

// Matriz multidimensional com os números a serem exibidos
int matriz_numeros[10][5][5][3] = {
    {//0
    {{0, 0, 0}, {42, 0, 0}, {42, 0, 0}, {42, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {42, 0, 0}, {0, 0, 0}, {42, 0, 0}, {0, 0, 0}}, 
    {{0, 0, 0}, {42, 0, 0}, {0, 0, 0}, {42, 0, 0}, {0, 0, 0}}, 
    {{0, 0, 0}, {42, 0, 0}, {0, 0, 0}, {42, 0, 0}, {0, 0, 0}}, 
    {{0, 0, 0}, {42, 0, 0}, {42, 0, 0}, {42, 0, 0}, {0, 0, 0}} 
},

{//1
    {{0, 0, 0}, {0, 0, 0}, {11, 42, 0}, {0, 0, 0}, {0, 0, 0}}, 
    {{0, 0, 0}, {0, 0, 0}, {11, 42, 0}, {0, 0, 0}, {0, 0, 0}}, 
    {{0, 0, 0}, {0, 0, 0}, {11, 42, 0}, {0, 0, 0}, {0, 0, 0}}, 
    {{0, 0, 0}, {0, 0, 0}, {11, 42, 0}, {0, 0, 0}, {0, 0, 0}}, 
    {{0, 0, 0}, {0, 0, 0}, {11, 42, 0}, {0, 0, 0}, {0, 0, 0}}  
},

{//2
    {{0, 0, 0}, {0, 2, 42}, {0, 2, 42}, {0, 2, 42}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 2, 42}, {0, 0, 0}},  
    {{0, 0, 0}, {0, 2, 42}, {0, 2, 42}, {0, 2, 42}, {0, 0, 0}},
    {{0, 0, 0}, {0, 2, 42}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},  
    {{0, 0, 0}, {0, 2, 42}, {0, 2, 42}, {0, 2, 42}, {0, 0, 0}}
},

{//3
    {{0, 0, 0}, {33, 0, 42}, {33, 0, 42}, {33, 0, 42}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {33, 0, 42}, {0, 0, 0}},
    {{0, 0, 0}, {33, 0, 42}, {33, 0, 42}, {33, 0, 42}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {33, 0, 42}, {0, 0, 0}},
    {{0, 0, 0}, {33, 0, 42}, {33, 0, 42}, {33, 0, 42}, {0, 0, 0}}
},

{//4
    {{0, 0, 0}, {0, 19, 42}, {0, 0, 0}, {0, 19, 42}, {0, 0, 0}},
    {{0, 0, 0}, {0, 19, 42}, {0, 0, 0}, {0, 19, 42}, {0, 0, 0}},
    {{0, 0, 0}, {0, 19, 42}, {0, 19, 42}, {0, 19, 42}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 19, 42}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 19, 42}, {0, 0, 0}}
},

{//5
    {{0, 0, 0}, {42, 40, 0}, {42, 40, 0}, {42, 40, 0}, {0, 0, 0}},
    {{0, 0, 0}, {42, 40, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {42, 40, 0}, {42, 40, 0}, {42, 40, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {42, 40, 0}, {0, 0, 0}},
    {{0, 0, 0}, {42, 40, 0}, {42, 40, 0}, {42, 40, 0}, {0, 0, 0}}
},

{//6
    {{0, 0, 0}, {11, 42, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {11, 42, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {11, 42, 0}, {11, 42, 0}, {11, 42, 0}, {0, 0, 0}},
    {{0, 0, 0}, {11, 42, 0}, {0, 0, 0}, {11, 42, 0}, {0, 0, 0}},
    {{0, 0, 0}, {11, 42, 0}, {11, 42, 0}, {11, 42, 0}, {0, 0, 0}}
},

{//7
    {{0, 0, 0}, {42, 0, 40}, {42, 0, 40}, {42, 0, 40}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {42, 0, 40}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {42, 0, 40}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {42, 0, 40}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {42, 0, 40}, {0, 0, 0}}
},

{//8
    {{0, 0, 0}, {42, 14, 0}, {42, 14, 0}, {42, 14, 0}, {0, 0, 0}},
    {{0, 0, 0}, {42, 14, 0}, {0, 0, 0}, {42, 14, 0}, {0, 0, 0}},
    {{0, 0, 0}, {42, 14, 0}, {42, 14, 0}, {42, 14, 0}, {0, 0, 0}},
    {{0, 0, 0}, {42, 14, 0}, {0, 0, 0}, {42, 14, 0}, {0, 0, 0}},
    {{0, 0, 0}, {42, 14, 0}, {42, 14, 0}, {42, 14, 0}, {0, 0, 0}}
},

{//9
    {{0, 0, 0}, {0, 32, 42}, {0, 32, 42}, {0, 32, 42}, {0, 0, 0}},
    {{0, 0, 0}, {0, 32, 42}, {0, 0, 0}, {0, 32, 42}, {0, 0, 0}},
    {{0, 0, 0}, {0, 32, 42}, {0, 32, 42}, {0, 32, 42}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 32, 42}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 32, 42}, {0, 0, 0}}
}
};

// Função para definir a intensidade de cores do LED  
// A função recebe os canais na ordem rgb, mas retorna na ordem GRB, necessárias para o correto funcionamentos dos LEDs ws2812.
static uint32_t matrix_rgb(double r, double g, double b){
  // Multiplique pelos fatores desejados para atenuar o brilho.
    // Os valores resultantes são convertidos para unsigned char.
    unsigned char R = (unsigned char)(r * 0.15);
    unsigned char G = (unsigned char)(g * 0.15);
    unsigned char B = (unsigned char)(b * 0.15);
    return ((uint32_t)G << 24) | ((uint32_t)R << 16) | ((uint32_t)B << 8);
}

// Rotina que desenha um número na matriz de LEDs utilizando PIO
void desenho_pio(int sprite, PIO pio, uint sm){   
    uint32_t valor_led;
    // Percorre cada linha e coluna de cada número
    for (int linha = 4; linha >= 0; linha--) // Percorre as linhas de baixo para cima. A lógica foi invertida somente para inverter a visualização na bitdoglab
    {
        for (int coluna = 0; coluna < 5; coluna++)
        {
            if(linha%2!=0){ // Se a linha for par, desenha da direita para a esquerda. A lógica foi invertida somente para inverter a visualização na bitdoglab
                valor_led = matrix_rgb(
                matriz_numeros[sprite][linha][coluna][0],
                matriz_numeros[sprite][linha][coluna][1],
                matriz_numeros[sprite][linha][coluna][2]);
                pio_sm_put_blocking(pio, sm, valor_led);
            }
            else{ // Se a linha for ímpar, desenha da direita para a esquerda
                valor_led = matrix_rgb(
                matriz_numeros[sprite][linha][4-coluna][0],
                matriz_numeros[sprite][linha][4-coluna][1],
                matriz_numeros[sprite][linha][4-coluna][2]);
                pio_sm_put_blocking(pio, sm, valor_led);
            }
        }
    }
}

// Função de callback para os botões, que altera o número a ser exibido
void call_back_dos_botoes(uint gpio, uint32_t events){
    uint32_t tempo_agora = to_ms_since_boot(get_absolute_time()); // Pega o tempo atual em milissegundos para debounce

    if (tempo_agora - tempo_anterior > 250){ // Verifica se o botão foi pressionado por mais de 250ms para evitar bounce
        tempo_anterior = tempo_agora; // Atualiza o tempo anterior
        if (gpio == BOT_A){
            if (numero_exibido < 9){ // Verifica se o número a ser exibido é menor que 9 para que seja exibido um número de no máximo 9
                numero_exibido++; // Incrementa o número a ser exibido se o botão A for pressionado
            }
        }else{
            if (numero_exibido > 0){ // Verifica se o número a ser exibido é maior que 0 para que não seja exibido um número negativo	
                numero_exibido--; // Decrementa o número a ser exibido se o botão B for pressionado
            }
        }
        desenho_pio(numero_exibido, pio, sm); // Chama a função para desenhar o número na matriz de LEDs
    }
}

void inicializa_GPIOs(void) {
    // Inicializa os GPIOs para os LEDs e botões
    gpio_init(LED_R);
    gpio_init(LED_G);
    gpio_init(LED_B);
    gpio_init(BOT_A);
    gpio_init(BOT_B);
    
    // Seta os GPIO's como saída para os LEDs
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_set_dir(LED_B, GPIO_OUT);
    
    // Seta os GPIO's como entrada para os botões
    gpio_set_dir(BOT_A, GPIO_IN);
    gpio_set_dir(BOT_B, GPIO_IN);
    
    // Seta os GPIO's com pull-up para os botões
    gpio_pull_up(BOT_A);
    gpio_pull_up(BOT_B);
    
    // Coloca os LEDs como desligados
    gpio_put(LED_R, 0);
    gpio_put(LED_G, 0);
    gpio_put(LED_B, 0);
}

void inicializa_PIO(void){
// Configura variaveis para o PIO
    pio = pio0; 
    bool ok;
    
    // Configura o clock para 128 MHz
    ok = set_sys_clock_khz(128000, false);

    printf("Iniciando a transmissão PIO\n");
    if (ok) printf("Clock set to %ld\n", clock_get_hz(clk_sys));

    // Configuração do PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, LED_PIN);

}

// Função principal
int main(){

    stdio_init_all();

    inicializa_GPIOs();

    inicializa_PIO();
    
    // Desenha o número inicial na matriz de LEDs toda vez que o programa é iniciado
    desenho_pio(numero_exibido, pio, sm);

    // Configura interrupções para os botões
    gpio_set_irq_enabled_with_callback(BOT_A, GPIO_IRQ_EDGE_FALL, true, &call_back_dos_botoes);
    gpio_set_irq_enabled_with_callback(BOT_B, GPIO_IRQ_EDGE_FALL, true, &call_back_dos_botoes);

    // Loop principal
    while (1){ // Loop infinito para piscar o LED vermelho
        // O LED deve piscar 5 vezes por segundo, portando o tempo total de ligado + desligado deve ser de no máximo 200ms por ciclo (neste caso 25 + 175)
        gpio_put(LED_R, 1);
        sleep_ms(25);
        gpio_put(LED_R, 0);
        sleep_ms(175);
    }
    return 0;
}
