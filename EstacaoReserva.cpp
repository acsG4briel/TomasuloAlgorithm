#include "EstacaoReserva.h"

EstacaoReserva::EstacaoReserva(){
    ocupado = false;
    opcode = 0;
    latencia = 0;
    resultado = 0;
    resultadoPronto = false;
    estacaoJ = 1;
    estacaoK = 1;
    valorJ = 0;
    valorK = 0;
    numeroInstrucao = 100000;
    latenciaIssue = 0;
    latenciaWriteback = 0;
}
EstacaoReserva::EstacaoReserva(int OPCODE, int estacaoDisponivel){
    ocupado = false;
    opcode = OPCODE;
    latencia = 0;
    resultado = 0;
    resultadoPronto = false;
    estacaoJ = estacaoDisponivel;
    estacaoK = estacaoDisponivel;
    valorJ = 0;
    valorK = 0;
    numeroInstrucao = 100000;
    latenciaIssue = 0;
    latenciaWriteback = 0;

}