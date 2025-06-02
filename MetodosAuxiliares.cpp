#include "MetodosAuxiliares.h"

using namespace std;

vector<Instrucao> Auxiliar::lerInstrucoesArquivo(const string &filename)
{
    vector<Instrucao> Inst;

    ifstream instructionFile(filename);
    if (!instructionFile.is_open())
    {
        cerr << "Error opening instruction file: " << filename << endl;
        return Inst;
    }

    string line;
    int lineCount = 0;

    while (lineCount < 6 && getline(instructionFile, line))
    {
        lineCount++;
    }

    while (getline(instructionFile, line))
    {
        if (line.empty() || line.find_first_not_of(" \t\r\n") == string::npos)
        {
            continue;
        }

        stringstream ss(line);
        string token;
        vector<int> values;

        try
        {
            while (getline(ss, token, ','))
            {
                token.erase(0, token.find_first_not_of(" \t\r\n"));
                token.erase(token.find_last_not_of(" \t\r\n") + 1);

                if (!token.empty())
                {
                    values.push_back(stoi(token));
                }
            }

            if (values.size() == 4)
            {
                int rd = values[0];
                int rs = values[1];
                int rt = values[2];
                int opcode = values[3];

                int operation;
                switch (opcode)
                {
                case 0:
                    operation = 0; //Add
                    break;
                case 1:
                    operation = 1; //Sub
                    break;
                case 2:
                    operation = 2; //Mult
                    break;
                case 3:
                    operation = 3; //Div
                    break;
                default:
                    cerr << "Operacao invalida: " << opcode << endl;
                    continue;
                }

                Instrucao instr(rd, rs, rt, operation);
                Inst.push_back(instr);
            }
        }
        catch (const std::exception &e)
        {
            cerr << "Erro no parsing da linha: " << line << " - " << e.what() << endl;
        }
    }
    instructionFile.close();

    return Inst;
}

void Auxiliar::exibirInstrucoes(const vector<Instrucao> &instrucoes)
{
    for (int i = 0; i < instrucoes.size(); i++)
    {
        string operacaoStr;
        string sinalOperacao;
        switch (instrucoes[i].opcode)
        {
        case 0:
            operacaoStr = "ADD";
            sinalOperacao = "+";
            break;
        case 1:
            operacaoStr = "SUB";
            sinalOperacao = "-";
            break;
        case 2:
            operacaoStr = "MULT";
            sinalOperacao = "*";
            break;
        case 3:
            operacaoStr = "DIV";
            sinalOperacao = "/";
            break;
        default:
            operacaoStr = "";
            break;
        }

        cout << "Instrucao #: " << i << "  Operacao: " << operacaoStr << "  "
             << instrucoes[i].registradorDestino << " <- "
             << instrucoes[i].registrador1 << " " << sinalOperacao << " "
             << instrucoes[i].registrador2 << endl;
    }
}

void Auxiliar::exibirRegistradores(const vector<int> &registradores)
{
    cout << "Conteudo Registradores:" << endl;
    for (int i = 0; i < registradores.size(); i++)
        cout << registradores[i] << ' ';
    cout << endl;
}

void Auxiliar::exibirInformacoesPorInstante(const vector<EstacaoReserva> &estacoes, int clock)
{
    char espaco = ' ';
    const int largura = 12;
    char espacoLinha = '-';
    const int larguraLinha = 96;

    cout << "\nEstacoes de Reserva:" << endl;

    cout << left << setw(largura) << setfill(espaco) << "Ocupado";
    cout << left << setw(largura) << setfill(espaco) << "Opcode";
    cout << left << setw(largura) << setfill(espaco) << "ValorJ";
    cout << left << setw(largura) << setfill(espaco) << "ValorK";
    cout << left << setw(largura) << setfill(espaco) << "EstacaoJ";
    cout << left << setw(largura) << setfill(espaco) << "EstacaoK";
    cout << left << setw(largura) << setfill(espaco) << "Resultado";
    cout << right << setw(largura) << setfill(espaco) << clock;
    cout << endl;
    cout << left << setw(larguraLinha) << setfill(espacoLinha) << "";
    cout << endl;

    for (int i = 0; i < estacoes.size(); i++)
    {
        string opcodeStr = "";
        switch (estacoes[i].opcode)
        {
        case 0:
            opcodeStr = "ADD";
            break;
        case 1:
            opcodeStr = "SUB";
            break;
        case 2:
            opcodeStr = "MULT";
            break;
        case 3:
            opcodeStr = "DIV";
            break;
        default:
            opcodeStr = "N/A";
            break;
        }

        cout << left << setw(largura) << setfill(espaco) << (estacoes[i].ocupado ? "Sim" : "Nao");
        cout << left << setw(largura) << setfill(espaco) << opcodeStr;
        cout << left << setw(largura) << setfill(espaco) << estacoes[i].valorJ;
        cout << left << setw(largura) << setfill(espaco) << estacoes[i].valorK;
        cout << left << setw(largura) << setfill(espaco) << estacoes[i].estacaoJ;
        cout << left << setw(largura) << setfill(espaco) << estacoes[i].estacaoK;
        cout << left << setw(largura) << setfill(espaco) << estacoes[i].resultado;
        cout << endl;
    }
}