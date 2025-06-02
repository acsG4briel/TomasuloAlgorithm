#include "Instrucao.h"

Instrucao::Instrucao() {
    registradorDestino = 0;
    registrador1 = 0;
    registrador2 = 0;
    opcode = 0;
    instanteIssue = 0;
    instanteInicioExecucao = 0;
    instanteFimExecucao = 0;
    instanteWriteback = 0;
}

Instrucao::Instrucao(int RD,int R1, int R2, int OPCODE) {
    registradorDestino = RD;
    registrador1 = R1;
    registrador2 = R2;
    opcode = OPCODE;
    instanteIssue = 0;
    instanteInicioExecucao = 0;
    instanteFimExecucao = 0;
    instanteWriteback = 0;
}