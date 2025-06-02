#ifndef TOMASULO_ES_H
#define TOMASULO_ES_H

class EstacaoReserva {
public:
    bool ocupado;        
    int estacaoJ;       
    int estacaoK;       
    int valorJ;         
    int valorK;         
    int latencia;       
    int opcode;       
    int resultado;      
    bool resultadoPronto; 
    int numeroInstrucao; 
    int latenciaIssue;   
    int latenciaWriteback; 

public:
    EstacaoReserva();
    EstacaoReserva(int, int);
};

#endif