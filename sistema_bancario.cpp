#include <iostream>
#include <string>
using namespace std;

class Cliente {
    private:
    string nome;
    string cpf;
    
    public:
    //construtor
    Cliente(string n, string c) : nome(n), cpf(c) {}
    
    //getter pra pegar as infos privadas
    string getnome(){
        return nome;
    }
    string getcpf(){
        return cpf;
    }
};

class ContaBancaria {
    private:
    int numero;
    double saldo;
    Cliente titular;
    
    public:
    //construtor
    ContaBancaria(int n, Cliente t, double s = 0.0) : numero(n), titular(t), saldo(s) {} 
    
    //get pro numero que é usado no void de transferir
    int getnumero(){
        return numero;
    }

    //depositar
    void depositar(double valor){
        saldo += valor;
    }

    //sacar
    void sacar(double valor){
        if (valor <= saldo){
            saldo -= valor;
        }
    }

    //transferir pra uma conta só
    void transferir(double valor, ContaBancaria &destino){
        if (valor <= saldo){
            saldo -= valor;
            destino.depositar(valor);
            cout << "Transferido: R$ " << valor 
             << " da conta " << numero 
             << " para a conta " << destino.getnumero() << endl;
        }
    }

    //transferir pra duas contas
    void transferir(double valor, ContaBancaria &destino1, ContaBancaria &destino2){
        if (valor <= saldo){
            saldo -= valor;
            double metade = valor/2.0;
            destino1.depositar(metade);
            destino2.depositar(metade);
            cout << "Transferido: R$ " << metade 
             << " para cada conta (" << destino1.getnumero() 
             << " e " << destino2.getnumero() 
             << ") da conta " << numero << endl;
        }
    }

    //mostra o saldo
    void exibirSaldo(){
        cout << "Saldo atual da conta " << numero << ": R$ " << saldo << endl;
    }

    //mostra as informações
    void exibirInformacoes(){
        cout << "Titular: " << titular.getnome() << ", CPF: " << titular.getcpf() << endl;
        cout << "Número da conta: " << numero << ", Saldo: R$ " << saldo << endl;
    }
};

int main() {
    // Criação dos clientes
    Cliente cliente1("Ana", "111.111.111-11");
    Cliente cliente2("Bruno", "222.222.222-22");
    Cliente cliente3("Carla", "333.333.333-33");

    // Criação das contas bancárias com saldos iniciais
    ContaBancaria conta1(1001, cliente1, 1000.0);
    ContaBancaria conta2(1002, cliente2);
    ContaBancaria conta3(1003, cliente3);

    // Exibe o saldo inicial da conta de Ana
    conta1.exibirSaldo();

    // Ana transfere R$200 para Bruno
    conta1.transferir(200.0, conta2);

    // Ana transfere R$300 divididos entre Bruno e Carla
    conta1.transferir(300.0, conta2, conta3);

    // Exibição dos saldos finais
    cout << endl;
    conta1.exibirInformacoes();
    conta2.exibirInformacoes();
    conta3.exibirInformacoes();

    return 0;
}