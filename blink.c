#include "pico/stdlib.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // Para gerar números aleatórios
#include <ctime>   // Para usar o tempo atual como semente para números aleatórios

// Definir o pino do buzzer
const uint buzzerPin = 15;  // Conecte o buzzer ao pino 15

// Função para simular um "bip" do buzzer
void beep() {
    gpio_put(buzzerPin, 1);  // Liga o buzzer
    sleep_ms(100);            // Mantém ligado por 100ms
    gpio_put(buzzerPin, 0);  // Desliga o buzzer
    sleep_ms(100);            // Aguarda 100ms antes de permitir outro bip
}

// Função para simular leitura de dados (temperatura e umidade)
void ler_dados(float &temperatura, float &umidade) {
    // Simula dados de temperatura e umidade aleatórios
    temperatura = 25 + (rand() % 5);  // Temperatura entre 25 e 30°C
    umidade = 50 + (rand() % 20);     // Umidade entre 50% e 70%
}

// Função para salvar os dados em um arquivo
void salvar_dados(float temperatura, float umidade) {
    // Abre o arquivo (se não existir, será criado)
    std::ofstream arquivo("dados.txt", std::ios::app);  // 'app' para adicionar ao arquivo existente
    if (arquivo.is_open()) {
        // Escreve os dados no arquivo
        arquivo << "Temperatura: " << temperatura << "°C, Umidade: " << umidade << "%" << std::endl;
        arquivo.close();  // Fecha o arquivo
    } else {
        std::cerr << "Erro ao abrir o arquivo para escrita!" << std::endl;
    }
}

int main() {
    // Inicializa o pino do buzzer
    gpio_init(buzzerPin);
    gpio_set_dir(buzzerPin, GPIO_OUT);

    // Semente para a função rand() para gerar números aleatórios baseados no tempo
    srand(time(NULL));

    // Variáveis para armazenar os dados simulados
    float temperatura, umidade;

    while (true) {
        // Simula a leitura de dados
        ler_dados(temperatura, umidade);

        // Exibe os dados na tela
        std::cout << "Temperatura: " << temperatura << "°C, Umidade: " << umidade << "%" << std::endl;

        // Salva os dados no arquivo
        salvar_dados(temperatura, umidade);

        // Emite o som do buzzer
        beep();

        // Aguarda 2 segundos antes de gerar novos dados
        sleep_ms(2000);
    }

    return 0;
}
