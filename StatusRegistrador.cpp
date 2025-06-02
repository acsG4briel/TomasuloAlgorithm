#include "StatusRegistrador.h"

StatusRegistrador::StatusRegistrador(){
    ocupado = false;
    estacao = 0;
}
StatusRegistrador::StatusRegistrador(int statusRegistradorVazio) {
    estacao = statusRegistradorVazio;
}