# Programas para Raspberry Pi Pico

Este repositório contém dois programas desenvolvidos para a Raspberry Pi Pico W, utilizando o Pico SDK e temporizadores para controle de LEDs.

## Programa 1: Semáforo (Ciclo Contínuo)

Este programa simula um semáforo simples utilizando três LEDs (vermelho, amarelo e verde). Cada LED acende por 3 segundos antes de passar para o próximo, repetindo o ciclo indefinidamente.

Funcionamento:  
1. O LED vermelho acende e permanece ligado por 3 segundos.  
2. O LED vermelho apaga, e o LED amarelo acende por 3 segundos.  
3. O LED amarelo apaga, e o LED verde acende por 3 segundos.  
4. O ciclo recomeça do início.  

A temporização é feita com a função `add_repeating_timer_ms()`, e as mudanças de estado são gerenciadas por um callback. O programa também imprime mensagens no terminal a cada segundo para acompanhamento da execução.

## Programa 2: Sequência com Botão

Neste programa, um botão é utilizado para iniciar a ativação dos LEDs. Quando o botão é pressionado, todos os LEDs acendem simultaneamente e, a cada 3 segundos, um LED é desligado até que todos estejam apagados. Enquanto o ciclo de desligamento não for concluído, o botão não pode ser acionado novamente.

Funcionamento:  
1. O usuário pressiona o botão, e todos os LEDs acendem ao mesmo tempo.  
2. Após 3 segundos, o LED azul apaga.  
3. Após mais 3 segundos, o LED vermelho apaga.  
4. Após mais 3 segundos, o LED verde apaga.  
5. O sistema fica pronto para receber um novo acionamento do botão.  

O controle da temporização é feito com `add_alarm_in_ms()`, utilizando callbacks para gerenciar o desligamento dos LEDs. O programa impede que o botão seja acionado novamente até que todos os LEDs tenham sido apagados.

## Requisitos Técnicos

- Hardware: Raspberry Pi Pico W, três LEDs (vermelho, amarelo e verde), resistores de 330Ω, pushbutton.  
- Software: Pico SDK, VS Code, Wokwi para simulação.  
- O código é escrito em C e deve ser compilado usando o SDK da Raspberry Pi Pico.  
- Opcionalmente, pode-se implementar um debounce por software para evitar acionamentos repetidos indesejados do botão.  

## Como Executar

### Execução do Programa 1

1. **Clone o repositório** e acesse a pasta do projeto.  
2. **Abra o projeto** no VS Code.  
3. **Compile o código** utilizando a extensão do Raspberry Pi Pico W.  
4. **Execute o programa** clicando em "Run" após a compilação.  

### Execução do Programa 2  
- Após compilar e rodar o programa, **pressione o botão A** para iniciar a sequência de desligamento dos LEDs.  
- O sistema aguardará o ciclo ser concluído antes de permitir um novo acionamento.

## Demonstração
Confira o vídeo explicativo neste link: [Vídeo no Google Drive](https://drive.google.com/file/d/1dhfBON9x2L55a3DeaMSivAd5tV9ht414/view?usp=drive_link)

