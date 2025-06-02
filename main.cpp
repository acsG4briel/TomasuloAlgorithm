#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "EstacaoReserva.h"
#include "Instrucao.h"
#include "StatusRegistrador.h"
#include "MetodosAuxiliares.h"

using namespace std;

// Variáveis globais de configuração do simulador

// Quantidades estacoes de reserva para cada tipo de operacao
const int quantidadeEstacoesReserva_ADD = 4;
const int quantidadeEstacoesReserva_MULT = 2;
const int quantidadeEstacoesReserva_DIV = 3;

// Opcodes
const int AddOp = 0;
const int SubOp = 1;
const int MultOp = 2;
const int DivOp = 3;

// Latencias das estações de reserva
const int latenciaAdd = 4;
const int latenciaMult = 12;
const int latenciaDiv = 38;

// Latencia dos estagios do algoritmo
const int latenciaIssue = 1;
const int latenciaWriteback = 1;

// Clock do sistema
int Clock = 0;

// Variaveis para determinar se o programa pode ser encerrado
bool pronto = true;
int totalWritebacks = 0;

// Contador para instrucao atual em ISSUE
int instrucaoAtualIssue = 0;

// Definicação valores iniciais
const int VALOR_REGISTRADOR_0 = 100;
const int StatusRegistradorPronto = 1000;
const int OperandoDisponivel = 1001;
const int OperandoVazio = 1002;

// FUNÇÕES PARA EXECUTAR O ALGORITMO DE TOMASULO
int Issue(vector<Instrucao> &Instrucoes,
          vector<EstacaoReserva> &EstacoesReserva,
          vector<StatusRegistrador> &StatusRegistradores,
          vector<int> &Registradores);
void Execute(vector<Instrucao> &Instrucoes,
             vector<EstacaoReserva> &EstacoesReserva,
             vector<StatusRegistrador> &StatusRegistradores,
             vector<int> &Registradores);
void Writeback(vector<Instrucao> &Instrucoes,
               vector<EstacaoReserva> &EstacoesReserva,
               vector<StatusRegistrador> &StatusRegistradores,
               vector<int> &Registradores);

void ExecutarCicloTomasulo(vector<Instrucao> &Instrucoes,
                           vector<EstacaoReserva> &EstacoesReserva,
                           vector<StatusRegistrador> &StatusRegistradores,
                           vector<int> &Registradores);

// Funcoes para instanciar os objetos necessários para simulação
vector<EstacaoReserva> instanciarEstacoesReserva();
vector<StatusRegistrador> instanciarStatusRegistradores();

// Simulacao principal
int main()
{
    Auxiliar aux;

    // Leitura das instruções do arquivo e criação
    vector<Instrucao> Instrucoes = aux.lerInstrucoesArquivo("instructionFile.txt");

    // Instância estações de reserva
    vector<EstacaoReserva> EstacoesReserva = instanciarEstacoesReserva();

    // Instância Status Registradores
    vector<StatusRegistrador> StatusRegistradores = instanciarStatusRegistradores();

    // Instância registradores
    vector<int> Registradores = {VALOR_REGISTRADOR_0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    // Inicio da simulação
    cout << "Valores Iniciais:" << endl;
    aux.exibirInstrucoes(Instrucoes);
    aux.exibirRegistradores(Registradores);
    cout << endl;

    // Loop para executar as instruções de acordo com o algoritmo
    do
    {
        Clock++;

        ExecutarCicloTomasulo(Instrucoes, EstacoesReserva, StatusRegistradores, Registradores);

        // Exibir estado dos registradores e Estacoes de Reserva
        aux.exibirRegistradores(Registradores);
        aux.exibirInformacoesPorInstante(EstacoesReserva, Clock);
        cout << endl;

        // Condição de parada: número de writebacks deve ser o mesmo da quantidade de instruções
        pronto = false;
        if (totalWritebacks == Instrucoes.size())
            pronto = true;
        cout << endl;
    } while (!pronto);

    return 0;
}

// Funções de Instância
vector<EstacaoReserva> instanciarEstacoesReserva()
{
    EstacaoReserva
        Add1(AddOp, OperandoVazio),
        Add2(AddOp, OperandoVazio),
        Add3(AddOp, OperandoVazio),
        Add4(AddOp, OperandoVazio);
    EstacaoReserva
        Mult1(MultOp, OperandoVazio),
        Mult2(MultOp, OperandoVazio);
    EstacaoReserva
        Div1(DivOp, OperandoVazio),
        Div2(DivOp, OperandoVazio),
        Div3(DivOp, OperandoVazio);

    vector<EstacaoReserva> EstacoesReserva = {Add1, Add2, Add3, Add4, Mult1, Mult2, Div1, Div2, Div3};

    return EstacoesReserva;
}

vector<StatusRegistrador> instanciarStatusRegistradores()
{
    StatusRegistrador
        F0(StatusRegistradorPronto),
        F1(StatusRegistradorPronto),
        F2(StatusRegistradorPronto), F3(StatusRegistradorPronto),
        F4(StatusRegistradorPronto), F5(StatusRegistradorPronto),
        F6(StatusRegistradorPronto), F7(StatusRegistradorPronto),
        F8(StatusRegistradorPronto), F9(StatusRegistradorPronto),
        F10(StatusRegistradorPronto), F11(StatusRegistradorPronto),
        F12(StatusRegistradorPronto), F13(StatusRegistradorPronto),
        F14(StatusRegistradorPronto), F15(StatusRegistradorPronto),
        F16(StatusRegistradorPronto), F17(StatusRegistradorPronto),
        F18(StatusRegistradorPronto), F19(StatusRegistradorPronto),
        F20(StatusRegistradorPronto), F21(StatusRegistradorPronto),
        F22(StatusRegistradorPronto), F23(StatusRegistradorPronto),
        F24(StatusRegistradorPronto), F25(StatusRegistradorPronto),
        F26(StatusRegistradorPronto), F27(StatusRegistradorPronto),
        F28(StatusRegistradorPronto), F29(StatusRegistradorPronto),
        F30(StatusRegistradorPronto), F31(StatusRegistradorPronto);

    vector<StatusRegistrador> StatusRegistradores = {
        F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23,
        F24, F25, F26, F27, F28, F29, F30, F31};

    return StatusRegistradores;
}

// Funções que executam o algoritmo de Tomasulo
void ExecutarCicloTomasulo(vector<Instrucao> &Instrucoes,
                           vector<EstacaoReserva> &EstacoesReserva,
                           vector<StatusRegistrador> &StatusRegistradores,
                           vector<int> &Registradores)
{
    Issue(Instrucoes, EstacoesReserva, StatusRegistradores, Registradores);
    Execute(Instrucoes, EstacoesReserva, StatusRegistradores, Registradores);
    Writeback(Instrucoes, EstacoesReserva, StatusRegistradores, Registradores);
}

int Issue(vector<Instrucao> &Instrucoes,
          vector<EstacaoReserva> &EstacoesReserva,
          vector<StatusRegistrador> &StatusRegistradores,
          vector<int> &Registradores)
{
    int r = 0;
    bool estacaoLivre = false;

    // Verifica se todas as instruções já foram emitidas
    if (instrucaoAtualIssue >= Instrucoes.size())
        return 0;

    // Obtém o código de operação da instrução atual
    r = Instrucoes[instrucaoAtualIssue].opcode;

    // Define os índices de início e fim para cada tipo de estação de reserva
    int InicioEstacaoAdd = quantidadeEstacoesReserva_ADD - quantidadeEstacoesReserva_ADD;
    int FimEstacaoAdd = quantidadeEstacoesReserva_ADD;
    int InicioEstacaoSub = quantidadeEstacoesReserva_ADD - quantidadeEstacoesReserva_ADD;
    int FimEstacaoSub = quantidadeEstacoesReserva_ADD;
    int InicioEstacaoMult = quantidadeEstacoesReserva_ADD;
    int FimEstacaoMult = quantidadeEstacoesReserva_ADD + quantidadeEstacoesReserva_MULT;
    int InicioEstacaoDiv = quantidadeEstacoesReserva_ADD + quantidadeEstacoesReserva_MULT;
    int FimEstacaoDiv = quantidadeEstacoesReserva_ADD + quantidadeEstacoesReserva_MULT + quantidadeEstacoesReserva_DIV;

    // Procura uma estação de reserva livre com base no tipo de operação
    switch (r)
    {
    case AddOp:
        for (int i = InicioEstacaoAdd; i < FimEstacaoAdd; i++)
        {
            if (!EstacoesReserva[i].ocupado)
            {
                r = i;
                instrucaoAtualIssue++;
                EstacoesReserva[i].opcode = AddOp;
                estacaoLivre = true;
                break;
            }
        }

        if (!estacaoLivre)
            return 1;
        break;
    case SubOp:
        for (int i = InicioEstacaoSub; i < FimEstacaoSub; i++)
        {
            if (!EstacoesReserva[i].ocupado)
            {
                r = i;
                instrucaoAtualIssue++;
                EstacoesReserva[i].opcode = SubOp;
                estacaoLivre = true;
                break;
            }
        }
        if (!estacaoLivre)
            return 1;
        break;
    case MultOp:
        for (int i = InicioEstacaoMult; i < FimEstacaoMult; i++)
        {
            if (!EstacoesReserva[i].ocupado)
            {
                r = i;
                instrucaoAtualIssue++;
                EstacoesReserva[i].opcode = MultOp;
                estacaoLivre = true;
                break;
            }
        }
        if (!estacaoLivre)
            return 1;
        break;
    case DivOp:
        for (int i = InicioEstacaoDiv; i < FimEstacaoDiv; i++)
        {
            if (!EstacoesReserva[i].ocupado)
            {
                r = i;
                instrucaoAtualIssue++;
                EstacoesReserva[i].opcode = DivOp;
                estacaoLivre = true;
                break;
            }
        }
        if (!estacaoLivre)
            return 1;
        break;
    default:
        break;
    }

    // Verifica se o primeiro operando está pronto ou precisa esperar
    if (StatusRegistradores[Instrucoes[instrucaoAtualIssue - 1].registrador1].estacao == StatusRegistradorPronto)
    {
        // Se o registrador está pronto, obtém o valor diretamente
        EstacoesReserva[r].valorJ = Registradores[Instrucoes[instrucaoAtualIssue - 1].registrador1];
        EstacoesReserva[r].estacaoJ = OperandoDisponivel;
    }
    else
    {
        // Se o registrador não está pronto, armazena a estação que produzirá o valor
        EstacoesReserva[r].estacaoJ = StatusRegistradores[Instrucoes[instrucaoAtualIssue - 1].registrador1].estacao;
    }

    // Verifica se o segundo operando está pronto ou precisa esperar
    if (StatusRegistradores[Instrucoes[instrucaoAtualIssue - 1].registrador2].estacao == StatusRegistradorPronto)
    {
        // Se o registrador está pronto, obtém o valor diretamente
        EstacoesReserva[r].valorK = Registradores[Instrucoes[instrucaoAtualIssue - 1].registrador2];
        EstacoesReserva[r].estacaoK = OperandoDisponivel;
    }
    else
    {
        // Se o registrador não está pronto, armazena a estação que produzirá o valor
        EstacoesReserva[r].estacaoK = StatusRegistradores[Instrucoes[instrucaoAtualIssue - 1].registrador2].estacao;
    }

    // Marca a estação como ocupada
    EstacoesReserva[r].ocupado = true;
    EstacoesReserva[r].latenciaIssue = 0;

    // Armazena o número da instrução na estação de reserva
    EstacoesReserva[r].numeroInstrucao = instrucaoAtualIssue - 1;

    // Registra o instante de clock em que a instrução foi emitida
    Instrucoes[instrucaoAtualIssue - 1].instanteIssue = Clock;

    // Atualiza o status do registrador de destino para indicar qual estação produzirá seu valor
    StatusRegistradores[Instrucoes[instrucaoAtualIssue - 1].registradorDestino].estacao = r;
    return 2;
}

void Execute(vector<Instrucao> &Instrucoes,
             vector<EstacaoReserva> &EstacoesReserva,
             vector<StatusRegistrador> &StatusRegistradores,
             vector<int> &Registradores)
{
    // Loop para percorrer as estações de reserva
    for (int r = 0; r < EstacoesReserva.size(); r++)
    {
        // Verifica se a estação está ocupada
        if (EstacoesReserva[r].ocupado == true)
        {
            // Verifica se já passou o tempo de latência necessário após o issue
            if (EstacoesReserva[r].latenciaIssue >= latenciaIssue)
            {
                // Verifica se ambos os operandos estão disponíveis
                if (EstacoesReserva[r].estacaoJ == OperandoDisponivel &&
                    EstacoesReserva[r].estacaoK == OperandoDisponivel)
                {
                    // Se for a primeira vez que a instrução está sendo executada, registra o instante de início
                    if (Instrucoes[EstacoesReserva[r].numeroInstrucao].instanteInicioExecucao == 0)
                        Instrucoes[EstacoesReserva[r].numeroInstrucao].instanteInicioExecucao = Clock;

                    EstacoesReserva[r].latencia++;

                    // Verifica o tipo de operação e executa quando atingir a latência necessária
                    switch (EstacoesReserva[r].opcode)
                    {
                    case (AddOp):
                        if (EstacoesReserva[r].latencia == latenciaAdd)
                        {
                            EstacoesReserva[r].resultado = EstacoesReserva[r].valorJ + EstacoesReserva[r].valorK;
                            EstacoesReserva[r].resultadoPronto = true;
                            EstacoesReserva[r].latencia = 0;
                            Instrucoes[EstacoesReserva[r].numeroInstrucao].instanteFimExecucao = Clock;
                            EstacoesReserva[r].latenciaIssue = 0;
                        }
                    case (SubOp):
                        if (EstacoesReserva[r].latencia == latenciaAdd)
                        {
                            EstacoesReserva[r].resultado = EstacoesReserva[r].valorJ - EstacoesReserva[r].valorK;
                            EstacoesReserva[r].resultadoPronto = true;
                            EstacoesReserva[r].latencia = 0;
                            Instrucoes[EstacoesReserva[r].numeroInstrucao].instanteFimExecucao = Clock;
                            EstacoesReserva[r].latenciaIssue = 0;
                        }
                    case (MultOp):
                        if (EstacoesReserva[r].latencia == latenciaMult)
                        {
                            EstacoesReserva[r].resultado = EstacoesReserva[r].valorJ * EstacoesReserva[r].valorK;
                            EstacoesReserva[r].resultadoPronto = true;
                            EstacoesReserva[r].latencia = 0;
                            Instrucoes[EstacoesReserva[r].numeroInstrucao].instanteFimExecucao = Clock;
                            EstacoesReserva[r].latenciaIssue = 0;
                        }
                    case (DivOp):
                        if (EstacoesReserva[r].latencia == latenciaDiv)
                        {
                            EstacoesReserva[r].resultado = EstacoesReserva[r].valorJ / EstacoesReserva[r].valorK;
                            EstacoesReserva[r].resultadoPronto = true;
                            EstacoesReserva[r].latencia = 0;
                            Instrucoes[EstacoesReserva[r].numeroInstrucao].instanteFimExecucao = Clock;
                            EstacoesReserva[r].latenciaIssue = 0;
                        }
                    default:
                        break;
                    }
                }
            }
            // Se ainda não passou o tempo de latência após o issue, incrementa o contador
            else
                EstacoesReserva[r].latenciaIssue++;
        }
    }
}

void Writeback(vector<Instrucao> &Instrucoes,
               vector<EstacaoReserva> &EstacoesReserva,
               vector<StatusRegistrador> &StatusRegistradores,
               vector<int> &Registradores)
{
    // Percorre todas as estações de reserva
    for (int r = 0; r < EstacoesReserva.size(); r++)
    {
        // Verifica se o resultado está pronto para ser escrito
        if (EstacoesReserva[r].resultadoPronto)
        {
            // Verifica se já passou o tempo de latência necessário para o writeback
            if (EstacoesReserva[r].latenciaWriteback == latenciaWriteback)
            {
                // Se for a primeira vez que a instrução está fazendo writeback, registra o instante
                if (Instrucoes[EstacoesReserva[r].numeroInstrucao].instanteWriteback == 0)
                    Instrucoes[EstacoesReserva[r].numeroInstrucao].instanteWriteback = Clock;

                // Percorre todos os registradores para atualizar aqueles que dependem desta estaçãO
                for (int x = 0; x < Registradores.size(); x++)
                {
                    // Se o registrador está esperando o resultado desta estação
                    if (StatusRegistradores[x].estacao == r)
                    {
                        // Atualiza o valor do registrador com o resultado calculado
                        Registradores[x] = EstacoesReserva[r].resultado;
                        // Marca o registrador como pronto (não depende mais de nenhuma estação)
                        StatusRegistradores[x].estacao = StatusRegistradorPronto;
                    }
                }
                
                // Percorre todas as estações de reserva para atualizar aquelas que dependem desta estação
                for (int y = 0; y < EstacoesReserva.size(); y++)
                {
                    if (EstacoesReserva[y].estacaoJ == r)
                    {
                        EstacoesReserva[y].valorJ = EstacoesReserva[r].resultado;
                        EstacoesReserva[y].estacaoJ = OperandoDisponivel;
                    }
                    if (EstacoesReserva[y].estacaoK == r)
                    {
                        EstacoesReserva[y].valorK = EstacoesReserva[r].resultado;
                        EstacoesReserva[y].estacaoK = OperandoDisponivel;
                    }
                }

                // Limpa a estação de reserva para que possa ser reutilizada
                EstacoesReserva[r].resultadoPronto = false;
                EstacoesReserva[r].ocupado = false;
                EstacoesReserva[r].estacaoJ = OperandoVazio;
                EstacoesReserva[r].estacaoK = OperandoVazio;
                EstacoesReserva[r].valorJ = 0;
                EstacoesReserva[r].valorK = 0;
                EstacoesReserva[r].latenciaWriteback = 0;
                totalWritebacks++;
            }
            else
                // Se ainda não passou o tempo de latência para o writeback, incrementa o contador
                EstacoesReserva[r].latenciaWriteback++;
        }
    }
}
