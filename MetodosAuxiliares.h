#ifndef AUXILIAR_H
#define AUXILIAR_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Instrucao.h"
#include "EstacaoReserva.h"

class Auxiliar
{
    public:
        static std::vector<Instrucao> lerInstrucoesArquivo(const std::string &filename);
        static void exibirInstrucoes(const std::vector<Instrucao> &instrucoes);
        static void exibirRegistradores(const std::vector<int> &registradores);
        static void exibirInformacoesPorInstante(const std::vector<EstacaoReserva> &estacoesReserva, int clock);

};

#endif // AUXILIAR_H