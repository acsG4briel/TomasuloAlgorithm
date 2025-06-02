#ifndef TOMASULO_INSTRUCAO_H
#define TOMASULO_INSTRUCAO_H

class Instrucao {
    public:
        //Atributos da classe que representa as Instruções
        int registradorDestino;
        int registrador1;
        int registrador2;
        int opcode;

        //Atributos para salvar os instantes de cada momento da Instrucao
        int instanteIssue;
        int instanteInicioExecucao;
        int instanteFimExecucao;
        int instanteWriteback;

    public:
        Instrucao();
        Instrucao(int,int,int,int);
};

#endif
