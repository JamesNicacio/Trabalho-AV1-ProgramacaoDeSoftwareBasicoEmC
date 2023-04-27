#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define BUFFER_SIZE 1000

void printFile(FILE *fptr){
    char ch;
    while((ch = fgetc(fptr)) != EOF)
        putchar(ch);
}

void deleteLine(FILE *src, FILE *temp, const int line){
    char buffer[BUFFER_SIZE];
    int count = 1;
    while ((fgets(buffer, BUFFER_SIZE, src)) != NULL){
        if (line != count)
            fputs(buffer, temp);
        count++;
    }
}

// function to calculate age from date of birth
int calculateAge(int day, int month, int year) {
    // get the current date
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    int current_year = local->tm_year + 1900;
    int current_month = local->tm_mon + 1;
    int current_day = local->tm_mday;
    
    // calculate age
    int age = current_year - year;
    if (current_month < month || (current_month == month && current_day < day)) {
        age--;
    }
    return age;
}


void removeChar(char str[], char charToRemmove){
    int i, j;
    int len = strlen(str);
    for(i=0; i<len; i++){
        if(str[i] == charToRemmove){
            for(j=i; j<len; j++){
                str[j] = str[j+1];
            }
            len--;
            i--;
        }
    }
}


int validarCPF(char *cpf){
    // char cpf[] = "111.111.111-10";
    int somaPrimeiroDigito = 0, somaSegundoDigito = 0, contadorDigito1 = 10, contadorDigito2 = 11;

    removeChar(cpf, '.');
    removeChar(cpf, '-');

    // inicia array baseado na quantidade de elementos em cpf
    int intCPF[strlen(cpf)];
    int len = sizeof(intCPF) / sizeof(int);
    printf("Tamanho do cpf: %d\n", len);

    // checa tamanho do cpf
    if(len < 11 || len > 11){
        printf("Tamanho invalido de CPF");
        return 0;
    }


    
    for (int i = 0; i < strlen(cpf); i++) {
        // Valida se cpf tem letras ou caracteres especiais
        // if(isalpha(cpf[i]) == 0 || isalnum(cpf[i]) == 0){
        //     printf("CPF invalido! Possui letras.");
        //     return 0;
        // }

        // Valida se eh um digito
        if(isdigit(cpf[i]) == 1){
            intCPF[i] = cpf[i] - '0';
            // Valida primeiro digito
            if(contadorDigito1 >=2){
                /*
                C and C++ store characters as integers using their underlying ASCII codes,
                so '0' is 48, '1' is 49, and so on. The easiest way to convert a single
                character to the integer it represents is to subtract the value of '0'.
                If we take '3' (ASCII code 51) and subtract '0' (ASCII code 48),
                we’ll be left with the integer 3, which is what we want
                */
                int digito = cpf[i] - '0';
                somaPrimeiroDigito += (digito * contadorDigito1);
                // printf("resultado::%d\n", somaPrimeiroDigito);
                // printf("%d * 10 / 11 = %d\n", somaPrimeiroDigito, (somaPrimeiroDigito*10)%11);
                /*
                Observação Importante: Se o resto da divisão for igual a 10, nós o consideramos como 0.
                */
            } else if(contadorDigito1 ==1){
                int digito = cpf[i] - '0';
                somaPrimeiroDigito = ((somaPrimeiroDigito*10)%11) == 10 ? 0 : (somaPrimeiroDigito*10)%11;
                if(digito == somaPrimeiroDigito){
                    printf("Primeiro digito eh igual\n");
                } else{
                    printf("Primeiro digito nao eh igual\n");
                    return 0;
                }
            }
            
            // Valida segundo digito
            if(contadorDigito2 >=2){
                int digito = cpf[i] - '0';
                somaSegundoDigito += (digito * contadorDigito2);
                // printf("resultado::%d\n", somaSegundoDigito);
                // printf("%d * 10 / 11 = %d\n", somaSegundoDigito, (somaSegundoDigito*10)%11);
                /*
                Observação Importante: Se o resto da divisão for igual a 10, nós o consideramos como 0.
                */
            } else if(contadorDigito2 ==1){
                int digito = cpf[i] - '0';
                somaSegundoDigito = ((somaSegundoDigito*10)%11) == 10 ? 0 : (somaSegundoDigito*10)%11;
                if(digito == somaSegundoDigito){
                    printf("Segundo digito eh igual\n");
                } else{
                    printf("Segundo digito nao eh igual\n");
                    return 0;
                }

            }
                contadorDigito1--;
                contadorDigito2--;
        } else{
            printf("CPF invalido!");
            return 0;
        }
    }
    // int len = sizeof(intCPF) / sizeof(int);
    // printf("%d", len);

    // int length = sizeof(intCPF) / sizeof(int);

    // Checa se todos os digitos sao iguais
    if(intCPF[0] == intCPF[1] &&
        intCPF[1] == intCPF[2] &&
        intCPF[2] == intCPF[3] &&
        intCPF[3] == intCPF[4] &&
        intCPF[4] == intCPF[5] &&
        intCPF[5] == intCPF[6] &&
        intCPF[6] == intCPF[7] &&
        intCPF[7] == intCPF[8] &&
        intCPF[8] == intCPF[9] &&
        intCPF[9] == intCPF[10]){
        printf("CPF invalido!!\n");
        printf("Todos os digitos sao iguais!!\n");
        return 0;
    }
    
    return 1;
}

void cadastrar(){
    char nome[25];
    int matricula, day, month, year;
    char cpf[14];
    double nota1, nota2;

    FILE *cfPtr;

    if ((cfPtr = fopen("registro.dat", "r+")) == NULL){
        printf("Arquivo nao pode ser aberto\n");

        // Se o arquivo não existe, cria um novo arquivo para gravação
        cfPtr = fopen("registro.dat", "w");
    }
    else {
        // O arquivo existe, abre ele para modificação
        printf("O arquivo existe e sera modificado\n");

        // Verifica se o arquivo está vazio antes de ler
        fseek(cfPtr, 0, SEEK_END);
        if (ftell(cfPtr) == 0) {
            printf("O arquivo esta vazio\n");
        }
        else {
            printf("O arquivo nao esta vazio\n");
            rewind(cfPtr);
        }

        // Depois de terminar a escrita ou leitura, assegure-se de fechar o arquivo
        fclose(cfPtr);

        // Abre o arquivo novamente para adicionar novos registros
        cfPtr = fopen("registro.dat", "a");
    }

    printf("Digite fim de arquivo para terminar a entrada\n");

    while (1){
        printf("Digite o nome: \n");
        if (scanf("%s", &nome) != 1) {
            printf("Entrada de dados invalida\n");
            break;
        }

        printf("Digite a matricula: \n");
        if (scanf("%d", &matricula) != 1) {
            printf("Entrada de dados invalida\n");
            break;
        }

        printf("Digite o cpf: \n");
        if (scanf("%s", &cpf) != 1) {
            printf("Entrada de dados invalida\n");
            break;
        }
        if(validarCPF(cpf) !=1){
            printf("CPF invalido!");
            break;
        }

        printf("Digite a data de nascimento no formato dd mm yyyy: \n");
        if (scanf("%d%d%d", &day, &month, &year) != 3) {
            printf("Entrada de dados invalida\n");
            break;
        }

        printf("Digite a primeira nota: \n");
        if (scanf("%lf", &nota1) != 1) {
            printf("Entrada de dados invalida\n");
            break;
        }

        printf("Digite a segunda nota: \n");
        if (scanf("%lf", &nota2) != 1) {
            printf("Entrada de dados invalida\n");
            break;
        }

        fprintf(cfPtr, "%s %d %s %d %d %d %.2f %.2f\n", nome, matricula, cpf, day, month, year, nota1, nota2);

        if (feof(stdin)) {
            break;
        }
    }

    fclose(cfPtr);
}


void consultar(){
    char nome[25]; /*nome*/
    int matricula, day, month, year, contador = 1;
    char cpf[14]; 
    double nota1, nota2; /*saldo da conta*/

    FILE *cfPtr; /*ponteiro de arquivo cfPtr = clients.dat*/

    /*fopen abre arquivo. Sai do programa se não pode criar arquivo*/
    if ((cfPtr = fopen("registro.dat", "r")) == NULL){
        printf("Arquivo nao pode ser aberto\n");
    } else{
        /*lê conta, nome, saldo e idade do arquivo*/
        printf("%-17s%-13s%-18s%-10s%-10s%s", "Nome", "Matricula", "CPF", "Idade", "Nota1", "Nota2\n");
        fscanf( cfPtr, "%s%d%s%d%d%d%lf%lf", &nome, &matricula, &cpf, &day, &month, &year, &nota1, &nota2);

        /*enquanto não é o fim do arquivo*/
        while (!feof( cfPtr)){
            int age = calculateAge(day,month,year);
            printf("%d-%-15s%-13d%-18s%-10d%4.2f%10.2f\n", contador, nome, matricula, cpf, age, nota1, nota2);
            fscanf(cfPtr, "%s%d%s%d%d%d%lf%lf", &nome, &matricula, &cpf, &day, &month, &year, &nota1, &nota2);
            contador++;
        }
        fclose(cfPtr);/*fclose fecha arquivo*/
    }
}


void alterar() {
    FILE *src;
    FILE *temp;
    char ch;
    int line;
    char nome[25];
    int matricula, day, month, year;
    char cpf[14];
    double nota1, nota2;

   consultar();

    printf("Digite a linha que deseja alterar: ");
    scanf("%d", &line);
    src  = fopen("registro.dat", "r");
    temp = fopen("delete.tmp", "w");
    if (src == NULL || temp == NULL){
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
        // exit(EXIT_FAILURE);
    }

     // Move src file pointer to beginning
    rewind(src);
    // Delete given line from file.
    deleteLine(src, temp, line);
    /* Close all open files */
    fclose(src);
    fclose(temp);
    /* Delete src file and rename temp file as src */
    remove("registro.dat");
    rename("delete.tmp", "registro.dat");
    // Open source file and print its contents
    src = fopen("registro.dat", "r");
    fclose(src);

    src  = fopen("registro.dat", "a");
    fseek(src, 0, SEEK_END);
    
        printf("Digite o nome: \n");
        if (scanf("%s", &nome) != 1) {
            printf("Entrada de dados invalida\n");
            exit(EXIT_FAILURE);
        }

        printf("Digite a matricula: \n");
        if (scanf("%d", &matricula) != 1) {
            printf("Entrada de dados invalida\n");
            exit(EXIT_FAILURE);
        }

        printf("Digite o cpf: \n");
        if (scanf("%s", &cpf) != 1) {
            printf("Entrada de dados invalida\n");
            exit(EXIT_FAILURE);

        }
        if(validarCPF(cpf) !=1){
            printf("CPF invalido!");
            exit(EXIT_FAILURE);

        }

        printf("Digite a data de nascimento no formato dd mm yyyy: \n");
        if (scanf("%d%d%d", &day, &month, &year) != 3) {
            printf("Entrada de dados invalida\n");
            exit(EXIT_FAILURE);

        }

        printf("Digite a primeira nota: \n");
        if (scanf("%lf", &nota1) != 1) {
            printf("Entrada de dados invalida\n");
            exit(EXIT_FAILURE);

        }

        printf("Digite a segunda nota: \n");
        if (scanf("%lf", &nota2) != 1) {
            printf("Entrada de dados invalida\n");
            exit(EXIT_FAILURE);

        }

        fprintf(src, "%s %d %s %d %d %d %.2f %.2f\n", nome, matricula, cpf, day, month, year, nota1, nota2);

        if (feof(stdin)) {
            exit(EXIT_FAILURE);

        }
        fclose(src);

        printf("Alteracao feita com sucesso");

}



void remover(){
    FILE *src;
    FILE *temp;
    int line;

   consultar();

    printf("Digite a linha que deseja remover: ");
    scanf("%d", &line);
    src  = fopen("registro.dat", "r");
    temp = fopen("delete.tmp", "w");
    if (src == NULL || temp == NULL){
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
        // exit(EXIT_FAILURE);
    }
    printf("\nConteudo antes de remover a linha\n\n");
    printFile(src);
    // Move src file pointer to beginning
    rewind(src);
    // Delete given line from file.
    deleteLine(src, temp, line);
    /* Close all open files */
    fclose(src);
    fclose(temp);
    /* Delete src file and rename temp file as src */
    remove("registro.dat");
    rename("delete.tmp", "registro.dat");
    printf("\n\n\nConteudo do arquivo apos remover  a linha: %d \n\n", line);
    // Open source file and print its contents
    src = fopen("registro.dat", "r");
    printFile(src);
    fclose(src);

    printf("Remocao feita com sucesso\n");

}