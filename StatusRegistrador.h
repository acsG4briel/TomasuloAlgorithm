#ifndef TOMASULO_STATUSREG_H
#define TOMASULO_STATUSREG_H

class StatusRegistrador {
    public:
        bool ocupado;
        int estacao;
    public:
        StatusRegistrador();
        StatusRegistrador(int);
};


#endif