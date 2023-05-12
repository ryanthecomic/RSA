#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define PRIMO 1
#define NAO_PRIMO 0

long long numero_primo(long long p){
    long long i;
    double j;

    j = sqrt(p);

    for (i = 2; i <= j; i++){
        if (p % i == 0)
            return NAO_PRIMO;
    }
    return PRIMO;
}

long long int mdc(long long int a,long long int b){
    if (a>b){
        if (!(a%b)){
            return b;
        }
        else {
            mdc(b,a%b);
        }
    }
    else{
        if (!(b%a)){
            return a;
        }
        else{
            mdc(a,b%a);
        }
    }
}

int find(char letras[], char str[], int n, int j, int i){
    if (str[i] == letras[j]){
        return j;
    }
    else{
        j++;
        return find(letras, str, n, j, i);
    }
    return find(letras, str, n, j, i);
}

void cripto(char letras[], int tabela[], char str[], unsigned long int new[], int n, int i){
    if (i == n){
        return;
    }
    else{
        int pos;
        pos = find(letras, str, n, 0, i);
        new[i] = tabela[pos];
    }
    cripto(letras, tabela, str, new, n, i + 1);
}

long potencia(long long a, long long e, long long n){
    long long A = a, P = 1, E = e;
     while (1){
        if (E == 0)
            return P;
        else if (E % 2 != 0){
            P = (A * P) % n;
            E = (E - 1) / 2;
        }
        else{
            E = E / 2;
        }
        A = (A * A) % n;
    }
}

int associacao(int tabela[], long long new[], int n, int j, int i){
    if (new[i] == tabela[j]){
        return j;
    }
    else{
        j++;
        return associacao(tabela, new, n, j, i);
    }
    return associacao(tabela, new, n, j, i);
}

void decifrar(char letra[], int tabela[], long long new[], char crip[], int n, int i){
    if (i == n){
        crip[i] = '\0';
        return;
    }
    else{
        long pos;
        pos = associacao(tabela, new, n, 0, i);
        crip[i] = letra[pos];
    }

    decifrar(letra, tabela, new, crip, n, i + 1);
}

void Gerador_de_Chaves(){
    FILE *chave_pul;
    FILE *chave_pri;
    long long int p, q, e, n, phi;
    system("clear");
    printf(">> Insira dois numeros primos e um expoente:\n");
    scanf("%lld %lld %lld", &p, &q, &e);

    while(!numero_primo(p) || !numero_primo(q) || mdc(e,((p-1)*(q-1)))!=1){
        system("clear");
        printf(">> Um dos numeros que voce digitou resultou em invalido.\nLembre-se de que o expoente deve ser coprimo a (p-1)*(q-1).\nInsira os valores novamente:\n");
        scanf("%lld %lld %lld", &p, &q, &e);
    }
  
    
    n = p * q;
    phi = (p - 1) * (q - 1);

    int d = 0;

    while((d * e) % phi != 1)
    {
        d++;
    }

    chave_pul = fopen("chave_publica.txt", "w");
    chave_pri = fopen("chave_privada.txt", "w");
    fprintf(chave_pul , "Sua chave publica: n => %lld e => %lld", n, e);
    fprintf(chave_pri , "Sua chave privada: p => %lld q => %lld d => %d", p, q, d);
    fclose(chave_pul);
    fclose(chave_pri);
    system("clear");
    printf(">> As chaves foram criadas com sucesso! ");
    
}

void Encriptar(){
    system("clear");
    long long int e, n;
    FILE *destino;
    destino = fopen("Mensagem_criptografada.txt", "w");
    char letras[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};
    int tabela[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
    char str[99999];

    printf(">> Insira a mensagem que deseja criptografar: \n");
    scanf(" %[^\n]", str);
    system("clear");
    printf(">> Insira a chave publica ('n' e 'e'): \n");
    scanf(" %lld %lld", &n, &e);
    system("clear");

    int tam = strlen(str);
    unsigned long int new[tam], crip[tam];
    unsigned long int val[tam];

    for (int i = 0; i < tam; i++){
        str[i] = tolower(str[i]);
    }
    cripto(letras, tabela, str, new, tam, 0);

    for (int i = 0; i < tam; i++){
        crip[i] = potencia(new[i], e, n);
    }

    for (int i = 0; i < tam; i++){
        fprintf(destino, "%lu ", crip[i]);
    }
    fclose(destino);
    printf(">> A criptografia foi concluida com sucesso! ");
}

void Desencriptar(){
    FILE *desencriptada;
    FILE *encriptada;

    long long value[999];
    
    char letras[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};
    int  tabela[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
    
    encriptada = fopen("Mensagem_criptografada.txt", "r");

    long long phi, e, p, q, n;
    int x, y;

    system("clear");
    printf(">> Insira a chave privada (ou p,q,e):\n");
    scanf("%lld %lld %lld", &p, &q, &e);
    system("clear");
    
    phi = (p - 1) * (q - 1);
    n = p * q;

    int d = 0, tam = 0, numero;

    while((d * e) % phi != 1)
    {
        d++;
    }

    while (fscanf(encriptada, "%lld", &value[tam]) != EOF){
        tam++;
    }

    long long new[tam];
    char crip[tam];

    for (int c = 0; c < tam; c++){
        new[c] = potencia(value[c], d, n);
    }

    desencriptada = fopen("Mensagem_descriptografada.txt", "w");
    decifrar(letras, tabela, new, crip, tam, 0);

    fprintf(desencriptada, "%s", crip);
    printf(">> A descriptografia foi concluida com sucesso! ");

    fclose(desencriptada);
    fclose(encriptada);
}

int main(){
    int programa = 1;
    while (programa != 0){
        int tarefa;
        
        printf("\n\n\t\t~PROJETO DE CRIPTOGRAFIA RSA~\n\n [1] Gerar Chave Publica\n [2] Encriptar Arquivo\n [3] Desencriptar Arquivo\n [4] Sair\n\n >> Insira a tarefa desejada: ");
        scanf("%d", &tarefa);

        while(tarefa != 1 && tarefa != 2 && tarefa != 3 && tarefa != 4){
            system("clear");
            printf("Opcao inexistente, escolha uma opcao dentre as possiveis abaixo: \n\n [1] Gerar Chave Publica\n [2] Encriptar Arquivo\n [3] Desencriptar Arquivo\n [4] Sair\n\n >> Insira a tarefa desejada: ");
            scanf("%d", &tarefa);
        }

        switch(tarefa){
            case 1:
                Gerador_de_Chaves(); break;

            case 2:
                Encriptar();         break;

            case 3:
                Desencriptar();      break;
            
            case 4:
              
              remove("chave_privada.txt");
              remove("chave_publica.txt");
              remove("Mensagem_criptografada.txt");
              remove("Mensagem_descriptografada.txt");
              
                system("clear");
                printf("CREDITOS:\nPlacido Augustus de Oliveira Cordeiro\nCaio Oliveira Franca dos Anjos\nPedro Henrique Santos da Silva\nNelson Alves Sousa Moreira\nRian Antonio da Silva Gaiao\n\nObrigado! \n");
                programa = 0;
            break;
        }
    }

    return 0;
}