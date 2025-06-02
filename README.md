# TomasuloAlgorithm

**Autores:** Gabriel Araujo e Gabriel Rangel

## Referências

- [Algoritmo de Tomasulo - UNICAMP](https://www.ic.unicamp.br/~rodolfo/Cursos/mo401/2s2005/Trabalho/049239-tomasulo.pdf)
- Hennessy, J. L., & Patterson, D. A. (2011). Computer Architecture: A Quantitative Approach (5th Edition). Morgan Kaufmann.

## Introdução

O algoritmo de Tomasulo é uma técnica avançada para resolver dependências verdadeiras em pipelines superescalares. Ele utiliza estações de reserva para armazenar instruções enquanto aguardam que seus operandos se tornem disponíveis. Nossa implementação simula um sistema com:

- 32 registradores
- 9 estações de reserva
- 4 tipos de instruções: ADD, SUB, MULT e DIV

## Implementação

O projeto foi estruturado em 5 classes para melhor organização e abstração do hardware:

| Classe | Descrição |
|--------|-----------|
| **Instrucao** | Representa comandos em linguagem de máquina, contendo operandos e timestamps de cada etapa do algoritmo |
| **EstacaoReserva** | Buffers para armazenar instruções com dependências, incluindo referências a outras estações |
| **StatusRegistrador** | Mantém informações sobre o estado dos registradores e suas dependências |
| **MetodosAuxiliares** | Agrupa funções utilitárias para exibição de dados e leitura de arquivos |
| **main.cpp** | Contém as variáveis principais e implementa as três etapas do algoritmo em um loop |

### Detalhes Técnicos

- **Latências**: Diferentes operações possuem diferentes tempos de execução (ex: DIV > ADD)
- **Valores especiais**:
- `1000`: Registrador pronto (não depende de nenhuma estação)
- `1001` e `1002`: Indicadores de status para operandos em estações de reserva
- **Registradores**: Inicializados com valores aleatórios, com o primeiro definido como 100 para facilitar verificação

## Funcionamento do Algoritmo

O algoritmo de Tomasulo opera em três fases principais:

### 1. Issue

<details>
<summary>Detalhes da fase de Issue</summary>

- Verifica se há instruções pendentes
- Identifica o tipo de operação (ADD, SUB, MULT, DIV)
- Procura uma estação de reserva livre apropriada
- Verifica a disponibilidade dos operandos:
- Se disponível: copia o valor diretamente
- Se indisponível: armazena referência à estação que produzirá o valor
- Atualiza o status do registrador de destino (renomeação de registradores)
</details>

### 2. Execute

<details>
<summary>Detalhes da fase de Execute</summary>

- Para cada estação ocupada, verifica:
- Se passou o tempo de latência após o Issue
- Se ambos os operandos estão disponíveis
- Quando as condições são satisfeitas:
- Registra o instante de início
- Incrementa o contador de latência
- Quando atinge a latência específica da operação:
  - Realiza a operação aritmética
  - Armazena o resultado
  - Registra o instante de fim
  - Marca o resultado como pronto para escrita
</details>

### 3. Writeback

<details>
<summary>Detalhes da fase de Writeback</summary>

- Para cada estação com resultado pronto:
- Verifica se passou o tempo de latência para Writeback
- Registra o instante de Writeback
- Atualiza os registradores dependentes
- Propaga o resultado para estações que o aguardam
- Libera a estação para reutilização
- Incrementa o contador de Writebacks concluídos
</details>

### Condição de Parada

O programa termina quando o contador de operações de Writeback concluídas iguala o número total de instruções, garantindo que todas foram processadas corretamente.

## Como Usar

### Requisitos
- Compilador C++ (g++)

### Compilação e Execução

```bash
# Compilar o programa
g++ -g main.cpp Instrucao.cpp EstacaoReserva.cpp StatusRegistrador.cpp MetodosAuxiliares.cpp -o main.exe

# Executar
./main.exe