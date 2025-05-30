//LotericaFipp Thales Eduardo Mendes de OLiveira, Renan Carvalho Silva

#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define TF 5

struct TpDezenas{
	int numero1, numero2;
};

struct TpData{
int dia, mes, ano;	
};

struct TpConcurso 
{
	int numConcurso; //chave primária
	TpData date;
	TpDezenas dezenasSorteadas[TF];
	char status;
};

struct TpApostadores{
	char cpf [12]; //chave primaria
	char nome [30];
	char numTel[12];
	char status;
};

struct TpApostas{
	int numAposta; //chave primaria
	int numConcurso;
	char cpf[15];
	int qtdeNumApostados;
	TpDezenas dezenas[TF];
	char status;
};

struct TpResumo{
	int numConcurso, premiados;
};

struct TpRankingConcurso{
	int numConcurso, totalApostas;
};

//validações
int validarCPF(char ncpf[15]);
int validarInt(char str[11]);

//Alteração
void AlterarApostador(void);
void AlterarConcurso(void);
void AlterarAposta(void);

//exclusões logicas
void exclusaoLogicaConcurso(void);
void exclusaoLogicaApostador(void);


//Metodos de Busca
int BuscarApostador(FILE *ptr, int cpf[15]);
int BuscarConcurso(FILE *ptr, int num);
int BuscarAposta(FILE *ptr, int num);


//Menus
char menu(void);
char menuNum(void);
char menuCad(void);
char menuExib(void);
char menuAlt(void);
char menuExclLF(void);
char menuExcl(void);
char menuRel(void);
char menuEst(void);

//Interface
void limparquadro(void);
void moldeMenuInicial(void);
void moldeMenuCadastro(void);
void moldeMenuExibir(void);
void moldeMenuAlterar(void);
void moldeMenuTipoExclusao(void);
void moldeMenuExcluir(void);
void moldeCadastrar(void);
void moldeMenuRelatorio(void);
void moldeMenuEstatisticas(void);
void moldura(int colunai, int linhai, int colunaf, int linhaf, int frente, int fundo);


//validações
int validarCPF(char ncpf[15]) {
	int i = 0, j = 10;
	int dig1, dig2;
	int soma = 0, resto;
	
	//se algum caracter for < 0 ou > 9 //quebra o codigo 
	if(validarInt(ncpf) != 1){
		return 0;
	}
		
	while (i < 9){
		soma += (ncpf[i] - 48) * j;
		i++;
		j--;
	}
	
	resto = soma % 11;
	if (resto < 2) // se resto < 2 o priemiro digito tem que ser = 0
		dig1 = 0;
	else  // se nao o digito tem que ser igual ao resto -11
		dig1 = 11 - resto;
	
	if ((ncpf[9] - 48) != dig1) //cpf invï¿½lido
		return 0;
	else {
		i = 0, j = 11, soma = 0;
	
		while (i < 10) {
			soma += (ncpf[i] - 48) * j;
			i++;
			j--;
		}
	
		resto = soma % 11;
		if (resto < 2)
			dig2 = 0;
		else
			dig2 = 11 - resto;
		
	}
	
	if ((ncpf[10] - 48) != dig2)
		return 0;
	else
		return 1;
}

int validarInt(char str[11]){
	int i;
	int TL = strlen(str);
	
	for(i = 0 ; i < TL - 1 ; i++)
		if(str[i] < 48 || str[i] > 57)
			return 0;
	
	return 1;
}

int validarData(int dia, int mes, int ano) {
    if (ano != 2025) return 0;
    if (mes < 1 || mes > 12) return 0;

    // Dias máximos por mês (2025 não é bissexto, então fevereiro tem 28 dias)
    int diasNoMes[12] = {31, 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31};

    if (dia < 1 || dia > diasNoMes[mes - 1]) return 0;

    return 1;
}


int lerInteiroValido(int l, int c, int maxColuna) {
    char buffer[100], ch;
    char *endptr;
    int num, valido=0, posCursor=0;
    

    while (!valido) {
        // Limpa a linha antes da entrada
        gotoxy(l, c);
        printf("                         ");
        gotoxy(l, c);

        posCursor = 0;

        while (1) {
            ch = getch();

            if (ch == '\r' || ch == '\n') {
                // Enter, finaliza a entrada
                buffer[posCursor] = '\0';
                break;
            }
            else if (ch == 8) { // Backspace
                if (posCursor > 0) {
                    posCursor--;
                    gotoxy(l + posCursor, c);
                    printf(" ");
                    gotoxy(l + posCursor, c);
                }
            }
            else if (ch >= '0' && ch <= '9') {
                if ((l + posCursor) < maxColuna) {
                    buffer[posCursor++] = ch;
                    printf("%c", ch);
                }
            }
        }

        num = (int)strtol(buffer, &endptr, 10);
        if (endptr != buffer && *endptr == '\0' && posCursor > 0) {
            valido = 1;
        } else {
            gotoxy(l, c + 1);
            printf("                                             "); // limpa a linha toda

            gotoxy(l, c + 1);
            printf("Entrada invalida! Digite um numero inteiro.");
            getch();

            gotoxy(l, c + 1);
            printf("                                             ");

           
            gotoxy(l, c);
            printf("                         ");
            gotoxy(l, c);
        }
    }
    return num;
}



void limparquadro(void){
	int l = 12, c = 9;
	
	while(c <= 22){
		gotoxy(l,c);
		printf("                                                               ");
		c++;
	}
}

void moldura(int colunai, int linhai, int colunaf, int linhaf, int frente, int fundo){
	textcolor(frente);
	textbackground(fundo);
	
	gotoxy(colunai, linhai); 
	printf("%c", 201); //canto superior esquerdo
	gotoxy(colunaf, linhai); 
	printf("%c", 187);//canto superior direito
	gotoxy(colunai, linhaf); 
	printf("%c", 200); //canto inferior esquerdo
	gotoxy(colunaf, linhaf); 
	printf("%c", 188);//canto inferior direito
	
	
	for(int a = colunai + 1; a < colunaf; a++){ 
		gotoxy(a, linhai); printf("%c", 205); 			
		gotoxy(a, linhaf); printf("%c", 205);
	}

	for(int b = linhai + 1; b < linhaf; b++){
		gotoxy(colunai, b); printf("%c", 186);
		gotoxy(colunaf, b); printf("%c", 186);
	}
	
	
	//voltar cores de texto e fundo padrÃ£o
	textcolor(7);
	textbackground(0);
	
}

void moldeCadastrar(void){
	//clrscr();
	
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	gotoxy(33, 7); 
	printf("* * * LOTERICAFIPP * * *");
			
}

void moldeMenuTipoExclusao(void){
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(19,13,37,17,7,5); //ITEM 1 a
	moldura(50,13,68,17,7,5); //ITEM 2

	gotoxy(33, 7); 
	printf("* * * EXCLUIR * * *");
}

void moldeMenuExcluir(void){
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(18,10,36,14,7,5); //ITEM 1 
	moldura(49,10,67,14,7,5); //ITEM 2

	moldura(18,17,36,21,7,5); //ITEM 3  

	gotoxy(33, 7); 
	printf("* * * EXCLUIR * * *");
}


void moldeMenuExcluirFisica(void){
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(18,10,36,14,7,5); //ITEM 1 
	moldura(49,10,67,14,7,5); //ITEM 2


	gotoxy(33, 7); 
	printf("* * * EXCLUIR * * *");
}

void moldeMenuAlterar(void){
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(18,10,36,14,7,3); //ITEM 1 
	moldura(49,10,67,14,7,3); //ITEM 2

	moldura(18,17,36,21,7,3); //ITEM 3 
	moldura(49,17,67,21,7,3); //ITEM 4  

	gotoxy(33, 7); 
	printf("* * * ALTERAR * * *");
}

void moldeMenuExibir(void){
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(18,10,36,14,7,1); //ITEM 1 
	moldura(49,10,67,14,7,1); //ITEM 2

	moldura(18,17,36,21,7,1); //ITEM 3 
	moldura(49,17,67,21,7,1); //ITEM 4  

	gotoxy(33, 7); 
	printf("* * * EXIBIR * * *");
}

void moldeMenuCadastro(void){
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(18,10,36,14,7,2); //ITEM 1 
	moldura(49,10,67,14,7,2); //ITEM 2

	moldura(18,17,36,21,7,2); //ITEM 3 
	moldura(49,17,67,21,7,2); //ITEM 4  

	gotoxy(33, 7); 
	printf("* * * CADASTRAR * * *");
}

void moldeMenuInicial(void){
	clrscr();
	
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(12,10,28,14,7,6); //ITEM 1 
	moldura(34,10,51,14,7,6); //ITEM 2 
	moldura(57,10,73,14,7,6); //ITEM 3 

	moldura(12,17,28,21,7,6); //ITEM 4 
	moldura(34,17,51,21,7,6); //ITEM 5 
	moldura(57,17,73,21,7,6); //ITEM 6 

	gotoxy(33, 7); 
	printf("* * * LOTERICA FIPP * * *");
	gotoxy(15, 25);
	printf("Feito por: Renan Carvalho Silva e Thales Eduardo Mendes de Oliveira");	
}

void moldeMenuRelatorio(void) {
	//clrscr();
	
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(12,10,28,14,13,14); //ITEM 1 
	moldura(34,10,51,14,13,14); //ITEM 2 
	moldura(57,10,73,14,13,14); //ITEM 3 

	moldura(21,17,37,21,13,14); //ITEM 4 
	moldura(48,17,64,21,13,14); //ITEM 5  

	gotoxy(33, 7); 
	printf("* * * RELATORIO * * *");
}

void moldeMenuEstatisticas(void) {
	//clrscr();
	
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(12,10,28,14,17,18); //ITEM 1 
	moldura(34,10,51,14,17,18); //ITEM 2 
	moldura(57,10,73,14,17,18); //ITEM 3 

	moldura(12,17,28,21,17,18); //ITEM 4 
	moldura(34,17,51,21,17,18); //ITEM 5 
	moldura(57,17,73,21,17,18); //ITEM 6 

	gotoxy(33, 7); 
	printf("* * * ESTATISTICA * * *");
}

//função que sorteia dezenas
void gerarDezenasSorteadas(TpDezenas dezenas[], int quantidade) {
    int usados[61] = {0};
    int count = 0;
    srand(time(NULL));

    while (count < quantidade) {
        int n1 = rand() % 60 + 1;
        int n2 = rand() % 60 + 1;

        if (n1 != n2 && usados[n1] == 0 && usados[n2] == 0) {
            dezenas[count].numero1 = n1;
            dezenas[count].numero2 = n2;
            usados[n1] = 1;
            usados[n2] = 1;
            count++;
        }
    }
}

//buscas
int BuscarApostador(FILE *PtrApostador, char cpf[15])
{
	TpApostadores RegApostador;
	rewind(PtrApostador);  //fseek(PtrVeiculo,0,0);
	fread(&RegApostador,sizeof(TpApostadores),1,PtrApostador);
	while (!feof(PtrApostador) && strcmp(cpf,RegApostador.cpf)!=0)
		fread(&RegApostador,sizeof(TpApostadores),1,PtrApostador);
		
	if (!feof(PtrApostador))
		return ftell(PtrApostador) - sizeof(TpApostadores);
	else
		return -1;
}


int BuscarConcurso (FILE * PtrConcurso, int numConcurso)
{
	TpConcurso RegConcurso;
	rewind(PtrConcurso);
	fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
	while(!feof(PtrConcurso) && numConcurso != RegConcurso.numConcurso)
		fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
	if (!feof(PtrConcurso))
		return ftell(PtrConcurso) - sizeof(TpConcurso);
	else
		return -1;
}

int BuscarAposta (FILE * PtrAposta, int NumAposta)
{
	TpApostas RegAposta;
	rewind(PtrAposta);
	fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
	while(!feof(PtrAposta) && NumAposta != RegAposta.numAposta)
		fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
	if(!feof(PtrAposta))
		return ftell(PtrAposta) - sizeof(TpApostas);
	else
		return -1; 
}

int BuscaBinariaConcurso(FILE *PtrConcurso, int numBusca) {
    TpConcurso RegConcurso;
    int ini = 0;
    int fim = 0;
    int meio;
    int pos = -1;

    fseek(PtrConcurso, 0, 2);  // fim do arquivo
    fim = ftell(PtrConcurso) / sizeof(TpConcurso) - 1;

    while (ini <= fim && pos == -1) {
        meio = (ini + fim) / 2;
        fseek(PtrConcurso, meio * sizeof(TpConcurso), 0);
        fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);

        if (RegConcurso.numConcurso == numBusca)
            pos = meio;
        else if (RegConcurso.numConcurso < numBusca)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    return pos;
}


//metodos de Ordenação
void BubbleSortResumo(TpResumo resumo[], int total) {
    int i = 0;
    while (i < total - 1) {
        int j = 0;
        while (j < total - i - 1) {
            if (resumo[j].premiados < resumo[j + 1].premiados) {
                TpResumo temp = resumo[j];
                resumo[j] = resumo[j + 1];
                resumo[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

void BubbleSortRanking(FILE *PtrRanking, int n) {
    TpRankingConcurso reg1, reg2;
    int i, trocou = 1;

    while (trocou == 1) {
        trocou = 0;
        i = 0;
        while (i < n - 1) {
            fseek(PtrRanking, i * sizeof(TpRankingConcurso), 0);
            fread(&reg1, sizeof(TpRankingConcurso), 1, PtrRanking);
            fread(&reg2, sizeof(TpRankingConcurso), 1, PtrRanking);

            if (reg1.totalApostas < reg2.totalApostas) {  // ordem decrescente
                fseek(PtrRanking, i * sizeof(TpRankingConcurso), 0);
                fwrite(&reg2, sizeof(TpRankingConcurso), 1, PtrRanking);
                fwrite(&reg1, sizeof(TpRankingConcurso), 1, PtrRanking);
                trocou = 1;
            }
            i++;
        }
        n--;
    }
}


void BubbleSortConcursoCrescente(FILE *PtrConcurso) {
    TpConcurso reg1, reg2;
    int i, j, n, trocou = 1;

    fseek(PtrConcurso, 0, 2);
    n = ftell(PtrConcurso) / sizeof(TpConcurso);

    while (trocou == 1) {
        trocou = 0;
        i = 0;
        while (i < n - 1) {
            fseek(PtrConcurso, i * sizeof(TpConcurso), 0);
            fread(&reg1, sizeof(TpConcurso), 1, PtrConcurso);
            fread(&reg2, sizeof(TpConcurso), 1, PtrConcurso);

            if (reg1.numConcurso > reg2.numConcurso) {
                fseek(PtrConcurso, i * sizeof(TpConcurso), 0);
                fwrite(&reg2, sizeof(TpConcurso), 1, PtrConcurso);
                fwrite(&reg1, sizeof(TpConcurso), 1, PtrConcurso);
                trocou = 1;
            }
            i = i + 1;
        }
        n = n - 1;
    }
}

void BubbleSortConcursoDecrescente(FILE *PtrConcurso) {
    TpConcurso reg1, reg2;
    int i, j, n, trocou = 1;

    fseek(PtrConcurso, 0, 2);
    n = ftell(PtrConcurso) / sizeof(TpConcurso);

    while (trocou == 1) {
        trocou = 0;
        i = 0;
        while (i < n - 1) {
            fseek(PtrConcurso, i * sizeof(TpConcurso), 0);
            fread(&reg1, sizeof(TpConcurso), 1, PtrConcurso);
            fread(&reg2, sizeof(TpConcurso), 1, PtrConcurso);

            if (reg1.numConcurso < reg2.numConcurso) {
                fseek(PtrConcurso, i * sizeof(TpConcurso), 0);
                fwrite(&reg2, sizeof(TpConcurso), 1, PtrConcurso);
                fwrite(&reg1, sizeof(TpConcurso), 1, PtrConcurso);
                trocou = 1;
            }
            i = i + 1;
        }
        n = n - 1;
    }
}


void entradaTextoControlada(int x, int y, int maxLen, char *buffer) {
    int pos = 0;
    char tecla;

    buffer[0] = '\0'; // inicia string vazia

    while (1) {
        gotoxy(x + pos, y);
        tecla = getch();

        if (tecla == 13) { // Enter tabela ASCII :)
            break;
        }
        else if (tecla == 8) { // Backspace tabela ASCII
            if (pos > 0) {
                pos--;
                buffer[pos] = '\0';

                gotoxy(x + pos, y);
                printf(" "); 
                gotoxy(x + pos, y);
            }
        }
        else if (pos < maxLen && tecla >= 32 && tecla <= 126) { // caractere imprimível
            buffer[pos] = tecla;
            pos++;
            buffer[pos] = '\0';

            printf("%c", tecla);
        }
        // Se ultrapassar maxLen, não deixa digitar mais
    }
}


void esconderCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Esconde o cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void travarCursor(short x, short y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x, y };
    SetConsoleCursorPosition(hConsole, pos);
}


//Cadastros
void CadastrarApostador(void)
{
	TpApostadores RegApostador;
	FILE *PtrApostador = fopen("Apostadores.dat", "ab+");
	char auxcpf[15];
	int Verifica, l = 25, c = 10;
	int sair = 0;

	moldeMenuCadastro();
	limparquadro();

	if (PtrApostador == NULL)
	{
		gotoxy(l, c);
		printf("Erro ao abrir o arquivo.");
		getch();
		return;
	}

	while (sair == 0)
	{
		l = 25;
		c = 10;
		limparquadro();

		gotoxy(l, c++);
		printf("## CADASTRAR APOSTADOR ##");
		gotoxy(l, c++);
		printf("CPF do APOSTADOR que deseja cadastrar:");
		gotoxy(l, c++);
		fflush(stdin);
		entradaTextoControlada(l,c, 30, auxcpf);

		if (strcmp(auxcpf, "\0") != 0)
		{
			if (validarCPF(auxcpf) == 1)
			{
				rewind(PtrApostador);
				Verifica = BuscarApostador(PtrApostador, auxcpf);

				if (Verifica == -1)
				{
					strcpy(RegApostador.cpf, auxcpf);

					gotoxy(l, c++);
					printf("Nome do APOSTADOR: ");
					fflush(stdin);
					entradaTextoControlada(l,c, 30, RegApostador.nome); 

					gotoxy(l, c);
					printf("Numero do telefone: "); fflush(stdin);
					c++;
					gotoxy(l, c++);
					entradaTextoControlada(l,c, 30, RegApostador.numTel); 

					RegApostador.status = 'A';
					fwrite(&RegApostador, sizeof(TpApostadores), 1, PtrApostador);

					gotoxy(l, c++);
					printf("APOSTADOR cadastrado com sucesso!");
					getch();
				}
				else
				{
					gotoxy(l, c++);
					printf("Apostador ja CADASTRADO.");
					getch();
				}
			}
			else
			{
				gotoxy(l, c++);
				printf("CPF invalido! Tente novamente.");
				getch();
			}
		}
		else
		{
			sair = 1; 
		}
	}

	fclose(PtrApostador);
}


void CadastrarConcurso (void){
	FILE *PtrConcurso = fopen("Concurso.dat", "ab+");
	TpConcurso RegConcurso;
	int Verifica, auxNum, l=25, c=10;

	moldeMenuCadastro();
	limparquadro();

	gotoxy(l,c);
	printf("## CADASTRO de CONCURSOS## ");
	c++;
	gotoxy(l,c);
	printf("NUMERO do CONCURSO: ");
	c++;
	auxNum = lerInteiroValido(l + 5, c, l + 15);
	c++;

	if(PtrConcurso == NULL) {
		gotoxy(l,c);
		printf("Erro de Abertura!!");
		c++;
	} else {
		while(auxNum > 0) {
			limparquadro();
			l = 25, c = 10;
			Verifica = BuscarConcurso(PtrConcurso, auxNum);
			if(Verifica == -1) { // Nao existe, então cadastra
				RegConcurso.numConcurso = auxNum;
				do {
					limparquadro();
					l=25, c=10;
					gotoxy(l,c);
					printf("DATA do CONCURSO (D M A): ");
					c++;
					gotoxy(l,c);
					scanf("%d/%d/%d", &RegConcurso.date.dia, &RegConcurso.date.mes, &RegConcurso.date.ano);
					if (!validarData(RegConcurso.date.dia, RegConcurso.date.mes, RegConcurso.date.ano)) {
						c++;
						gotoxy(l,c);
						printf("Data invalida. Informe uma data valida de 2025.");
						c++;
						getch();
						c--;
						c--;
					}
				} while (!validarData(RegConcurso.date.dia, RegConcurso.date.mes, RegConcurso.date.ano));

				gerarDezenasSorteadas(RegConcurso.dezenasSorteadas, TF);
				gotoxy(l,c);
				printf("Numeros sorteados neste concurso:");
				c++;
				limparquadro();
				for (int i = 0; i < TF; i++) {
					gotoxy(l,c);
					printf("Dezena %d: %02d e %02d", i + 1, RegConcurso.dezenasSorteadas[i].numero1, RegConcurso.dezenasSorteadas[i].numero2);
					c++;
					getch();
				}
				limparquadro();
				RegConcurso.status = 'A';
				fwrite(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
				gotoxy(l,c);
				printf("CONCURSO CADASTRADO com sucesso");
				c++;
				getch();
				limparquadro();
			} else {
				gotoxy(l,c);
				printf("CONCURSO JA CADASTRADO!!!");	
				c++;
				getch();
				limparquadro();
			}
			l = 25, c = 10;
			gotoxy(l,c);
			printf("## CADASTRO de CONCURSOS## ");
			c++;
			gotoxy(l,c);
			printf("NUMERO do CONCURSO: ");
			c++;
			auxNum = lerInteiroValido(l + 5, c, l + 15);
			c++;
		}
		getch();
		fclose(PtrConcurso);
	}
}




void CadastrarAposta(void) {
    FILE *PtrAposta = fopen("Apostas.dat", "ab+");
    FILE *PtrApostadores = fopen("Apostadores.dat", "rb");
    FILE *PtrConcurso = fopen("Concurso.dat", "rb");

    TpApostas RegAposta;
    int auxNum, VerificaApostador, VerificaConcurso, auxAposta, VerificaAposta, l=25, c=10;
    char auxCpf[15];

    moldeMenuCadastro();
    limparquadro();

    gotoxy(l,c); 
	printf("## CADASTRAR APOSTAS ##"); 
	c++;
    gotoxy(l,c); 
	printf("NUMERO DA APOSTA que deseja CADASTRAR: "); 
	c++;
    gotoxy(l,c); 
	auxAposta = lerInteiroValido(l, c, 73); 
	c++;

    if(PtrAposta == NULL) {
        gotoxy(l,c); 
		printf("Erro de abertura!!"); 
		c++;
    } else {
        while (auxAposta > 0) {
            rewind(PtrAposta);
            VerificaAposta = BuscarAposta(PtrAposta, auxAposta);

            if(VerificaAposta == -1) {
                do {
                    gotoxy(l,c); 
					printf("CPF do APOSTADOR: "); fflush(stdin); 
					c++;
                    gotoxy(l,c); 
					entradaTextoControlada(l, c, 14, auxCpf); 
					c++;
                    if (!validarCPF(auxCpf)) {
                        gotoxy(l,c); 
						printf("CPF invalido! Tente novamente."); 
						getch(); 
						limparquadro(); 
						c = 10; l = 25;
                    }
                } while (!validarCPF(auxCpf));

                gotoxy(l,c); 
				printf("NUMERO do CONCURSO: "); 
				c++;
                gotoxy(l,c); 
				auxNum = lerInteiroValido(l, c, 73);
				 c++;

                VerificaApostador = BuscarApostador(PtrApostadores, auxCpf);
                VerificaConcurso = BuscarConcurso(PtrConcurso, auxNum);

                if(VerificaApostador != -1 && VerificaConcurso != -1) {
                    RegAposta.numAposta = auxAposta;
                    strcpy(RegAposta.cpf, auxCpf);
                    RegAposta.numConcurso = auxNum;

                    limparquadro();
                    l = 25; c=10;
                    gotoxy(l,c); 
					printf("QUANTAS dezenas deseja apostar (max. %d): ", TF);
					 c++;
                    gotoxy(l,c); 
					RegAposta.qtdeNumApostados = lerInteiroValido(l, c, 73); 
					c++;

                    if (RegAposta.qtdeNumApostados >= 1 && RegAposta.qtdeNumApostados <= TF) {
                        int usados[61] = {0}, i = 0;

                        while (i < RegAposta.qtdeNumApostados) {
                            int n1, n2, valido = 1;
                            limparquadro(); l = 25; c = 10;
                            gotoxy(l,c); 
							printf("Digite os 2 numeros da %d\370 dezena (1 a 60):", i + 1); 
							c++;
                            gotoxy(l,c); 
							scanf("%d %d", &n1, &n2); 
							c++;

                            if (n1 < 1 || n1 > 60 || n2 < 1 || n2 > 60 || n1 == n2 || usados[n1] || usados[n2]) {
                                gotoxy(l,c); 
								printf("Numeros invalidos ou repetidos!"); 
								c++;
                                getch();
                                valido = 0;
                            }

                            if (valido) {
                                RegAposta.dezenas[i].numero1 = n1;
                                RegAposta.dezenas[i].numero2 = n2;
                                usados[n1] = 1;
                                usados[n2] = 1;
                                i++;
                            }
                        }

                        RegAposta.status = 'A';
                        fwrite(&RegAposta, sizeof(TpApostas), 1, PtrAposta);

                        gotoxy(l,c); 
						printf("APOSTA cadastrada com sucesso!"); 
						c++;
                        getch(); 
						limparquadro();
                        l = 25; c = 10;
                        gotoxy(l,c); 
						printf("Numeros apostados:"); 
						c++;
                        for (int j = 0; j < RegAposta.qtdeNumApostados; j++) {
                            gotoxy(l,c); 
							printf("Dezena %d: %02d e %02d", j+1, RegAposta.dezenas[j].numero1, RegAposta.dezenas[j].numero2);
							c++;
                            getch();
                        }
                    } else {
                        gotoxy(l,c); 
						printf("Quantidade de dezenas invalida."); 
						c++;
                        getch();
                    }

                } else if (VerificaApostador == -1) {
                    gotoxy(l,c); printf("APOSTADOR NAO cadastrado"); c++; getch();
                } else if (VerificaConcurso == -1) {
                    gotoxy(l,c); 
					printf("CONCURSO NAO cadastrado"); 
					c++; 
					getch();
                }
            } else {
                gotoxy(l,c); 
				printf("APOSTA ja CADASTRADA!"); 
				c++; 
				getch();
            }

            limparquadro();
            l = 25; c = 10;
            gotoxy(l,c); 
			printf("##CADASTRAR APOSTAS ##"); 
			c++;
            gotoxy(l,c); 
			printf("NUMERO DA APOSTA que deseja CADASTRAR: "); 
			c++;
            gotoxy(l,c); 
			auxAposta = lerInteiroValido(l, c, 73); 
			c++;
        }
        fclose(PtrAposta);
        fclose(PtrConcurso);
        fclose(PtrApostadores);
    }
}


//Alterar
void AlterarApostador() {
    FILE *PtrApostador = fopen("Apostadores.dat", "rb+");
    TpApostadores Registro;
    int Verifica, l = 25, c = 10;
    char opcao;
    char auxCpf[15];

    moldeMenuAlterar();
    limparquadro();

    gotoxy(l, c++);
    printf("** ALTERAR APOSTADOR **");

    if (PtrApostador == NULL) 
	{
        gotoxy(l, c++);
        printf("Erro em abrir o arquivo!");
        getch();
        return;
    }

    gotoxy(l, c);
    printf("Digite o CPF do apostador: ");
    c++;
    gotoxy(l, c);
    entradaTextoControlada(l, c, 14, auxCpf);

    if (validarCPF(auxCpf) != 1) 
	{
        c++;
        gotoxy(l, c++);
        printf("CPF invalido!");
        getch();
    } 
	else 
	{
        Verifica = BuscarApostador(PtrApostador, auxCpf);
        if (Verifica == -1) 
		{
            c++;
            gotoxy(l, c);
            printf("Apostador nao encontrado!");
            c++;
            getch();
        } 
		else 
		{
            fseek(PtrApostador, Verifica, SEEK_SET);
            fread(&Registro, sizeof(TpApostadores), 1, PtrApostador);

            c++;
            gotoxy(l, c); 
			printf("*** Detalhes do Apostador ***");
            c++;
            gotoxy(l, c); 
			printf("CPF: %s", Registro.cpf); 
			c++;
            gotoxy(l, c); 
			printf("Nome: %s", Registro.nome); 
			c++;
            gotoxy(l, c); 
			printf("Telefone: %s", Registro.numTel);
			c++;
            gotoxy(l, c); 
			printf("Status: %c", Registro.status);
			c++;
            gotoxy(l, c); 
			printf("Qual dado deseja alterar?");
			c++;
            gotoxy(l, c); 
			printf("[A] Nome \t [B] Telefone");
			c++;

            opcao = toupper(getche());

            limparquadro();
            l = 25; c = 10;

            if (opcao == 'A') {
                gotoxy(l, c); 
				printf("## Alterar Nome ##");
				c++;
                gotoxy(l, c); 
				printf("Digite novo nome: ");
				c++;
                gotoxy(l, c);
                entradaTextoControlada(l, c, 30, Registro.nome);
                c++;
            }

            if (opcao == 'B') {
                gotoxy(l, c); 
				printf("## Alterar Telefone ##");
				c++;
                gotoxy(l, c); 
				printf("Digite novo telefone: ");
				c++;
                gotoxy(l, c);
                entradaTextoControlada(l, c, 14, Registro.numTel);
                c++;
            }

            fseek(PtrApostador, -sizeof(TpApostadores), SEEK_CUR);
            fwrite(&Registro, sizeof(TpApostadores), 1, PtrApostador);

            gotoxy(l, c);
            printf("Dados atualizados com sucesso!");
            c++;
            getch();
        }
    }

    fclose(PtrApostador);
}



void AlterarConcurso(){
	
	FILE *PtrConcurso = fopen("Concurso.dat", "rb+");
	TpConcurso Registro;
	int Verifica, l=25,c=10;
	char opcao; 
	clrscr();
	
	moldeMenuAlterar();
	limparquadro();
	
	gotoxy(l,c);
	printf("** Alterar Concurso **");
	c++;
	if (PtrConcurso == NULL){
		gotoxy(l,c);
		printf("Erro Em Abrir Arquivo!");
		c++;
	}	
	else
	{
		gotoxy(l,c);
		printf("Digite o numero do concurso: ");
		c++;
		gotoxy(l,c); 
		Registro.numConcurso = lerInteiroValido(l, c, 55);
		c++;
		Verifica = BuscarConcurso(PtrConcurso, Registro.numConcurso);
		if(Verifica == -1){
			gotoxy(l,c);
			printf("Concurso Nao Encontrado!!!");
			c++;
			getch();
		}
			
		else
		{
				l=25, c=10;
				limparquadro();
				gotoxy(l,c);
				printf("** Detalhes do Concurso **");
				c++;
				
				fseek(PtrConcurso,Verifica,0);  //fseek(PtrVeic,desl,SEEK_SET);
				fread(&Registro,sizeof(TpConcurso),1,PtrConcurso);
				gotoxy(l,c);
				printf("Data: %d %d %d",Registro.date.dia,Registro.date.mes,Registro.date.ano);
				c++;
				gotoxy(l,c);
				printf("Numero do concurso: %d",Registro.numConcurso);
				c++;
				gotoxy(l,c);
				printf("Status: %c",Registro.status);
				c++;
				gotoxy(l,c);
				printf("Dezenas sorteadas: ");
				c++;
				for (int i = 0; i < TF; i++) {
					gotoxy(l,c);
    				printf("Dezena %d: %02d e %02d", i + 1,Registro.dezenasSorteadas[i].numero1, Registro.dezenasSorteadas[i].numero2);
    				c++;
    				getch();
				}
				limparquadro();
				l=25, c=10;
				gotoxy(l,c);
				printf("Qual Dado deseja Alterar?");
				c++;
				gotoxy(l,c);
				printf("[A] Data \t [B] Numeros sorteados");
				c++;
				opcao = toupper(getche());
				switch(opcao)
				{
					case 'A':
						{
							limparquadro();
							gotoxy(l,c);
							printf("## Alterar Data ## ");
							c++;
							gotoxy(l,c);
							printf("Digite nova data: ");
							c++;
							gotoxy(l,c);
							scanf("%d %d %d",&Registro.date.dia,&Registro.date.mes,&Registro.date.ano);
							c++;
							break;
						}
					case'B':
						{
							limparquadro();
							gotoxy(l,c);
							printf("** ALTERAR NUMEROS SORTEADOS **");
							c++;
							gerarDezenasSorteadas(Registro.dezenasSorteadas, TF);
							printf("Novas dezenas: ");
							for (int i = 0; i < TF; i++) 
							{
								gotoxy(l,c);
    							printf("Dezena %d: %02d e %02d", i + 1,Registro.dezenasSorteadas[i].numero1, Registro.dezenasSorteadas[i].numero2);
    							c++;
    							getch();
							}
						}
				}
				
				fseek(PtrConcurso, -sizeof(TpConcurso), 1); //posiciona o ponteiro onde vai ser alterado, o -sizeof acontece por que o ponteiro sempre anda mais um, e a posição que queremos está antes;
				fwrite(&Registro, sizeof(TpConcurso), 1, PtrConcurso); //grava no registro onde esta a posição atual do ponteiro.
				
				gotoxy(l,c);
				printf("Dados Atualizados!!");
				c++;
				getch();
				fclose(PtrConcurso);
		}
	}
}


void AlterarAposta(){
	
	FILE *PtrAposta = fopen("Apostas.dat", "rb+");
	TpApostas Registro;
	int Verifica, l=25, c=10;
	char opcao; 
	clrscr();
	
	moldeMenuAlterar();
	limparquadro();
	
	gotoxy(l,c);
	printf("** ALTERAR APOSTA **");
	c++;
	if (PtrAposta == NULL)
	{
		gotoxy(l,c);
		printf("Erro Em Abrir Arquivo!");
		c++;
	}
		
	else
	{
		gotoxy(l,c);
		printf(" Digite o numero da aposta: ");
		c++;
		gotoxy(l,c);
		scanf("%d",&Registro.numAposta);
		c++;
		Verifica = BuscarAposta(PtrAposta, Registro.numAposta);
		if(Verifica == -1)
			{
				gotoxy(l,c);
				printf("Aposta Nao Encontrada!!!");
				c++;
				getch();
			}
			
		else
		{
				l=25,c=10;
				limparquadro();
				gotoxy(l,c);
				printf("** Detalhes da Aposta **");
				c++;
				fseek(PtrAposta,Verifica,0);  //fseek(PtrVeic,desl,SEEK_SET);
				fread(&Registro,sizeof(TpApostas),1,PtrAposta);
				gotoxy(l,c);
				printf("CPF: %s",Registro.cpf);
				c++;
				gotoxy(l,c);
				printf("Numero de aposta: %d",Registro.numAposta);
				c++;
				gotoxy(l,c);
				printf("Numeros apostados: %d",Registro.dezenas);
				c++;
				gotoxy(l,c);
				printf("Quantidade De numeros apostados: %d",Registro.qtdeNumApostados);
				c++;
				gotoxy(l,c);
				printf("Status: %c",Registro.status);
				c++;
				gotoxy(l,c);
				printf("Qual Dado deseja Alterar?");
				c++;
				gotoxy(l,c);
				printf("[A] Numeros apostados \t [B]Quant. Num. Apostados ");
				c++;
				opcao = toupper(getch());
				switch (opcao) 
				{
              		case 'A': 
					{
    				int usados[61] = {0};
   					int i = 0, valido, n1, n2;

    				while (i < Registro.qtdeNumApostados) 
					{
        				do 
						{
            			limparquadro();
            			l = 25;
            			c = 10;

            			gotoxy(l, c);
            			printf("## Alterar Numeros Apostados ##");
            			c++;
            			gotoxy(l, c);
            			printf("Par %d - Digite dois números entre 1 e 60:", i + 1);
            			c++;
            			gotoxy(l, c);
            			scanf("%d %d", &n1, &n2);
            			c++;
            			valido = 1;

            			if (n1 < 1 || n1 > 60 || n2 < 1 || n2 > 60 || n1 == n2 || usados[n1] || usados[n2])
						{
                			gotoxy(l, c);
                			printf("Números invalidos ou ja usados!");
                			c++;
                			getch();
                			valido = 0;
            			}

        				}while (!valido);

        			Registro.dezenas[i].numero1 = n1;
        			Registro.dezenas[i].numero2 = n2;
        			usados[n1] = 1;
        			usados[n2] = 1;
        			i++;
        
    				}
					getch();            
    				break;
					}


                	case 'B': 
					{
    					int usados[61] = {0}, n1, n2, valido;
    					l = 25, c = 10;
    					limparquadro();
    					gotoxy(l, c);
    					printf("## Alterar Quantidade de Números Apostados ##");
    					c++;
    					gotoxy(l, c);
    					printf("Digite a nova quantidade de pares (máx: %d): ", TF);
    					c++;
    					scanf("%d", &Registro.qtdeNumApostados);

    					if (Registro.qtdeNumApostados > TF || Registro.qtdeNumApostados <= 0) 
						{
        					gotoxy(l, c);
        					printf("Quantidade inválida! Deve ser entre 1 e %d.", TF);
        					c++;
        					getch();
    					} 
						else 
						{
        					for (int i = 0; i < Registro.qtdeNumApostados; i++) 
							{
            					do 
								{
                					limparquadro();
                					l = 25;
                					c = 10;
                					gotoxy(l, c);
                					printf("## Alterar Quantidade de Números Apostados ##");
                					c++;
                					gotoxy(l, c);
                					printf("Par %d - Digite dois números entre 1 e 60:", i + 1);
               						c++;
                					gotoxy(l, c);
                					scanf("%d %d", &n1, &n2);
                					c++;
                					valido = 1;

                					if (n1 < 1 || n1 > 60 || n2 < 1 || n2 > 60 || n1 == n2 || usados[n1] || usados[n2]) 
									{
                    					gotoxy(l, c);
                    					printf("Números invalidos ou ja usados!");
                    					c++;
                    					getch();
                    					valido = 0;
                					}

            					} while (!valido);

            				Registro.dezenas[i].numero1 = n1;
            				Registro.dezenas[i].numero2 = n2;
            				usados[n1] = 1;
            				usados[n2] = 1;
        					}
    					}
    				break;
					}	
            	}
				
				fseek(PtrAposta, -sizeof(TpApostas), 1); //posiciona o ponteiro onde vai ser alterado, o -sizeof acontece por que o ponteiro sempre anda mais um, e a posição que queremos está antes;
				fwrite(&Registro, sizeof(TpApostas), 1, PtrAposta); //grava no registro onde esta a posição atual do ponteiro.
				gotoxy(l,c);
				printf("Dados Atualizados!!");
				c++;
				fclose(PtrAposta);
		}
	}
}

//Exibir
void exibirApostador(void){
	FILE *PtrApostador = fopen("Apostadores.dat", "rb");
	TpApostadores RegApostador;
	int l=25, c=10;
	moldeMenuExibir();
	limparquadro();
	gotoxy(l,c);
	printf("** EXIBIR APOSTADORES **");
	c++;
	if(PtrApostador == NULL)
	{
		gotoxy(l,c);
		printf("Erro de Abertura!");
		c++;
	}
	else{
		if(fread(&RegApostador, sizeof(TpApostadores), 1, PtrApostador) !=1 ){
			gotoxy(l,c);
			printf("Nenhum Apostador Cadastrado!");
			c++;
			getch();
		}
		else
	{
		rewind(PtrApostador);
		fread(&RegApostador, sizeof(TpApostadores), 1, PtrApostador);
		while(!feof(PtrApostador))
		{
			limparquadro();
			l = 25, c=10;
			gotoxy(l,c);
			printf("CPF: %s", RegApostador.cpf);
			c++;
			gotoxy(l,c);
			printf("Nome: %s", RegApostador.nome);
			c++;
			gotoxy(l,c);
			printf("Telefone: %s", RegApostador.numTel);
			c++;
			gotoxy(l,c);
			printf("Status: %c", RegApostador.status);
			c++;
			fread(&RegApostador, sizeof(TpApostadores), 1, PtrApostador);
			
			gotoxy(l,c);
			printf("Pressione uma tecla para proximo apostador...");
			c++;
			getch();
		}
	fclose(PtrApostador);	
	}
}

	}
	
void exibirConcurso(void){
    FILE *PtrConcurso = fopen("Concurso.dat", "rb");
    TpConcurso RegConcurso;
    int l = 25, c=10;

    moldeMenuExibir();
    limparquadro();  // corrigido

    gotoxy(l,c);
    printf("** EXIBIR CONCURSOS **");    
    c++;

    if(PtrConcurso == NULL)
    {
        gotoxy(l,c);
        printf("Erro de abertura!");
        c++;
    }
    else
    {
        // Tenta ler o primeiro registro
        if(fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso) != 1)
        {
            // Não conseguiu ler nenhum registro = arquivo vazio
            gotoxy(l,c);
            printf("Nenhum Concurso cadastrado");
            c++;
            getch();
        }
        else
        {
            do
            {
                limparquadro();
                l = 25; c=10;
                gotoxy(l,c);
                printf("** CONCURSOS **");
                c++;
                gotoxy(l,c);
                printf("Numero do concurso: %d", RegConcurso.numConcurso);
                c++;
                gotoxy(l,c);
                printf("Data do Concurso: %d/%d/%d", RegConcurso.date.dia, RegConcurso.date.mes, RegConcurso.date.ano);
                c++;
                gotoxy(l,c);
                printf("Status: %c", RegConcurso.status);
                c++;

                for (int i = 0; i < TF; i++) {
                    gotoxy(l,c);
                    printf("Dezena %d: %02d e %02d", i + 1, RegConcurso.dezenasSorteadas[i].numero1, RegConcurso.dezenasSorteadas[i].numero2);
                    c++;
                }
                gotoxy(l,c);
                printf("Pressione para exibir proximo concurso...");
                c++;
                getch();

            } while(fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso) == 1);

            fclose(PtrConcurso);
        }
    }
}



void exibirAposta(){
	FILE *PtrAposta = fopen("Apostas.dat", "rb");
	TpApostas RegAposta;
	int l = 25, c = 10;
	moldeMenuExibir();
	limparquadro();
	
	gotoxy(l,c);
	printf("** EXIBIR APOSTAS **");
	c++;
	if(PtrAposta == NULL)
	{
		gotoxy(l,c);
		printf("Nenhuma Aposta Cadastrada!!");
		c++;
		getch();
	}
	else{
		if(fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta) != 1){
			gotoxy(l,c);
			printf("Nenhuma aposta cadastrada!");
			c++;
			getch();
		}else
	{
		rewind(PtrAposta);
		fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
		while(!feof(PtrAposta))
		{
			limparquadro();
			l = 25, c = 10;
			gotoxy(l,c);
			printf("APOSTAS: ");
			c++;
			gotoxy(l,c);
			printf("Numero da Aposta: %d", RegAposta.numAposta);
			c++;
			gotoxy(l,c);
			printf("CPF do APOSTADOR: %s", RegAposta.cpf);
			c++;
			gotoxy(l,c);
			printf("Numero do Concurso: %d", RegAposta.numConcurso);
			c++;
			gotoxy(l,c);
			printf("Quantidade de dezenas apostadas: %d", RegAposta.qtdeNumApostados);
			c++;
			printf("Status: %c", RegAposta.status);
			
			fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
			
			gotoxy(l,c);
			printf("Pressione uma tecla para a proxima aposta...");
			c++;
			getch();
		}
		fclose(PtrAposta);
	}
}

	}
	
//Exclusões Lógicas
void exclusaoLogicaApostador(void)
{
	FILE *ptrApostador = fopen("Apostadores.dat", "rb+");
	TpApostadores RegApostador;
	
	moldeCadastrar();
	limparquadro();
	
	int Verifica, l=25, c=10;
	char op;
	gotoxy(l,c);
	printf("Excluir Logicamente o apostador(Log.)");
	c++;
	if(ptrApostador == NULL)
	{
		gotoxy(l,c);
		printf("Erro de Abertura!");
		c++;
	}	
	else 
	{
		gotoxy(l,c);
		printf("CPF do apostador que deseja excluir: ");
		c++;
		gotoxy(l,c);
		gets(RegApostador.cpf);
		c++;
		while(strcmp(RegApostador.cpf, "\0") != 0)
		{
			Verifica = BuscarApostador(ptrApostador, RegApostador.cpf);
			if(Verifica != -1)
			{
				limparquadro();
				l=25, c=10;
				fseek(ptrApostador, Verifica, 0);
				fread(&RegApostador, sizeof(TpApostadores), 1, ptrApostador);
				gotoxy(l,c);
				printf("** Informações do apostador **");
				c++;
				gotoxy(l,c);
				printf("CPF: %s", RegApostador.cpf);
				c++;
				gotoxy(l,c);
				printf("Nome: %s", RegApostador.nome);
				c++;
				gotoxy(l,c);
				printf("Telefone: %s", RegApostador.numTel);
				c++;
				gotoxy(l,c);
				printf("Status: %c", RegApostador.status);
				c++;
				gotoxy(l,c);
				printf("Deseja Excluir o Apostador? S/N");
				c++;
				if (toupper(getche() == 'S'))
				{
					RegApostador.status = 'I';
					fseek(ptrApostador, Verifica, 0);
					fwrite(&RegApostador, sizeof(TpApostadores), 1, ptrApostador);
					gotoxy(l,c);
					printf("Registro deletado");
					c++;
				}
			}
			
				else
				{
					gotoxy(l,c);
					printf("Apostador Nao Encontrado");
					c++;	
				}
				gotoxy(l,c);
				printf("CPF do apostador que deseja excluir(Log.): ");
				c++;
				gotoxy(l,c);
				gets(RegApostador.cpf);
				c++;
		}
		getch();
		fclose(ptrApostador);	 	
	}

}



void exclusaoLogicaConcurso(void)
{
	FILE *ptrConcurso = fopen("Concurso.dat", "rb+");
	TpConcurso RegConcurso;
	int l=25, c=10, Verifica;
	
	moldeCadastrar();
	limparquadro();
	
	gotoxy(l,c);
	printf("Exclusao de concursos(Log.)");
	c++;
	if(ptrConcurso == NULL)
	{
		gotoxy(l,c);
		printf("Erro de abertura!!");
		c++;
	}
	else{
		gotoxy(l,c);
		printf("Numero do concurso que deseja excluir: ");
		c++;
		gotoxy(l,c);
		scanf("%d", &RegConcurso.numConcurso);
		c++;
		while(RegConcurso.numConcurso > 0)
		{
			limparquadro();
			l=25, c=10;
			Verifica = BuscarConcurso(ptrConcurso, RegConcurso.numConcurso);
			if(Verifica != -1)
			{
				fseek(ptrConcurso, Verifica, 0);
				fread(&RegConcurso, sizeof(TpConcurso), 1, ptrConcurso);
				gotoxy(l,c);
				printf("** Dados do concurso **");
				c++;
				gotoxy(l,c);
				printf("Numero do concurso: %d", RegConcurso.numConcurso);
				c++;
				gotoxy(l,c);
				printf("Data do Concurso: %d/%d/%d", RegConcurso.date.dia, RegConcurso.date.mes, RegConcurso.date.ano);
				c++;
				gotoxy(l,c);
				printf("Status: %c", RegConcurso.status);
				c++;
				for (int i = 0; i < TF; i++) 
				{
					gotoxy(l,c);
    				printf("Dezena %d: %02d e %02d", i + 1,RegConcurso.dezenasSorteadas[i].numero1, RegConcurso.dezenasSorteadas[i].numero2);
    				c++;
    				getch();
				}
				gotoxy(l,c);
				printf("Deseja Excluir? S/N");
				c++;
				if(toupper(getche()) == 'S')
				{
					RegConcurso.status = 'I';
					fseek(ptrConcurso, Verifica, 0);
					fwrite(&RegConcurso, sizeof(TpConcurso), 1, ptrConcurso);
					printf("Registro Deletado!");
				}
			}
			else
			{
				gotoxy(l,c);
				printf("Concurso Não Encontrado");
				c++;
			}
			gotoxy(l,c);
			printf("Numero do concurso que deseja excluir: ");
			gotoxy(l,c);
			scanf("%d", &RegConcurso.numConcurso);
			c++;
		}
		getch();
		fclose(ptrConcurso);
	}
	
}

void exclusaoLogicaAposta(void){
	FILE *ptrAposta = fopen("Apostas.dat", "rb+");
	TpApostas RegAposta;
	int l=25, c=10, verifica;
	
	moldeCadastrar();
	limparquadro();
	
	gotoxy(l,c);
	printf("** EXCLUIR APOSTAS (log.) **");
	c++;
	if(ptrAposta == NULL){
		gotoxy(l,c);
		printf("Erro de abertura!!");
		c++;
	} 
	else{
		gotoxy(l,c);
		printf("Numero da aposta que deseja excluir: ");
		c++;
		gotoxy(l,c);
		scanf("%d", &RegAposta.numAposta);
		c++;
		while(RegAposta.numAposta > 0){
			limparquadro();
			l=25, c=10;
			verifica = BuscarAposta(ptrAposta, RegAposta.numAposta);
			if(verifica != -1){
				fseek(ptrAposta, verifica, 0);
				fread(&RegAposta, sizeof(TpApostas), 1, ptrAposta);
				gotoxy(l,c);
				printf("** Dados da aposta **");
				c++;
				gotoxy(l,c);
				printf("Numero da Aposta: %d", RegAposta.numAposta);
				c++;
				gotoxy(l,c);
				printf("CPF do APOSTADOR: %s", RegAposta.cpf);
				c++;
				gotoxy(l,c);
				printf("Numero do Concurso: %d", RegAposta.numConcurso);
				c++;
				gotoxy(l,c);
				printf("Quantidade de dezenas apostadas: %d", RegAposta.qtdeNumApostados);
				c++;
				gotoxy(l,c);
				printf("Status: %c", RegAposta.status);
				c++;
				gotoxy(l,c);
				printf("Confirma a Exclusão? S/N");
				c++;
				if(toupper(getche()) == 'S')
				{
					RegAposta.status = 'I';
					fseek(ptrAposta, verifica, 0);
					fwrite(&RegAposta, sizeof(TpApostas), 1, ptrAposta);
					gotoxy(l,c);
					printf("Registro Deletado");
					c++;
				}
			}
			else
			{
				gotoxy(l,c);
				printf("Aposta não encontrada");
				c++;
				getch();
			}
			
			limparquadro();
			l=25, c=10;
			gotoxy(l,c);
			printf("Numero da aposta que deseja excluir: ");
			c++;
			gotoxy(l,c);
			scanf("%d", &RegAposta.numAposta);
			c++;	
		}
		getch();
		fclose(ptrAposta);
	}
}


//Exclusoes fisicas
void exclusaoFisicaApostador(void)
{
    FILE *ptrApostador = fopen("Apostadores.dat", "rb");
    TpApostadores RegApostador;
    char AuxCPF[15];
    int l = 25, c = 10;
    int encontrouAtivo = 0;
    int cpfValido = 1;
    int cpfEncontrado = 0;
    int confirmarExclusao = 0;
    int apostasAtivas = 0;
    int podeExcluir = 1;

    limparquadro();
    moldeCadastrar();

    gotoxy(l, c);
    printf("### EXCLUIR APOSTADOR E SUAS APOSTAS###");
    c++;

    if (ptrApostador == NULL)
    {
        gotoxy(l, c);
        printf("Erro de abertura do arquivo de apostadores!");
        c++;
        podeExcluir = 0;
    }
    else
    {
        gotoxy(l, c);
        printf("CPF do apostador: ");
        fflush(stdin);
        c++;
        gets(AuxCPF);

        if (strcmp(AuxCPF, "\0") == 0)
        {
            cpfValido = 0;
            podeExcluir = 0;
        }
    }

    if (podeExcluir && cpfValido)
    {
        rewind(ptrApostador);
        fread(&RegApostador, sizeof(TpApostadores), 1, ptrApostador);
        while (!feof(ptrApostador) && !encontrouAtivo)
        {
            if (stricmp(AuxCPF, RegApostador.cpf) == 0 && RegApostador.status != 'I')
            {
                encontrouAtivo = 1;
                podeExcluir = 0;
            }
            fread(&RegApostador, sizeof(TpApostadores), 1, ptrApostador);
        }
    }

    if (encontrouAtivo)
    {
        gotoxy(l, c);
        printf("Apostador Ativo, exclua Logicamente primeiro");
        c++;
        getch();
    }
    else if (podeExcluir && cpfValido)
    {
        int verifica = BuscarApostador(ptrApostador, AuxCPF);
        if (verifica == -1)
        {
            gotoxy(l, c);
            printf("CPF não encontrado!");
            c++;
            cpfEncontrado = 0;
            podeExcluir = 0;
            getch();
        }
        else
        {
            cpfEncontrado = 1;
            fseek(ptrApostador, verifica, 0);
            fread(&RegApostador, sizeof(TpApostadores), 1, ptrApostador);

            gotoxy(l, c);
            printf("*** DADOS DO APOSTADOR ***");
            c++;
            gotoxy(l, c);
            printf("Nome: %s", RegApostador.nome);
            c++;
            gotoxy(l, c);
            printf("CPF: %s", RegApostador.cpf);
            gotoxy(l, c);
            printf("Telefone: %s", RegApostador.numTel);
            c++;

            gotoxy(l, c);
            printf("Confirma a Exclusao (S/N)? ");
            c++;

            if (toupper(getche()) == 'S')
            {
                confirmarExclusao = 1;
            }
            else
            {
                gotoxy(l, c);
                printf("Exclusão cancelada!");
                c++;
                podeExcluir = 0;
                getch();
            }
        }
    }

    if (confirmarExclusao && cpfEncontrado)
    {
        FILE *PtrTemp = fopen("TempApostadores.dat", "wb");
        rewind(ptrApostador);
        fread(&RegApostador, sizeof(TpApostadores), 1, ptrApostador);
        while (!feof(ptrApostador))
        {
            if (stricmp(AuxCPF, RegApostador.cpf) != 0)
                fwrite(&RegApostador, sizeof(TpApostadores), 1, PtrTemp);

            fread(&RegApostador, sizeof(TpApostadores), 1, ptrApostador);
        }
        fclose(PtrTemp);
        fclose(ptrApostador);
        remove("Apostadores.dat");
        rename("TempApostadores.dat", "Apostadores.dat");

        // Excluir apostas do apostador
        FILE *PtrAposta = fopen("Apostas.dat", "rb");
        FILE *PtrTempApostas = fopen("TempApostas.dat", "wb");
        TpApostas RegAposta;

        if (PtrAposta != NULL && PtrTempApostas != NULL)
        {
            fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
            while (!feof(PtrAposta) && apostasAtivas == 0)
            {
                if (stricmp(AuxCPF, RegAposta.cpf) == 0 && RegAposta.status != 'I')
                {
                    apostasAtivas = 1;
                    podeExcluir = 0;
                }
                fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
            }

            if (apostasAtivas)
            {
                gotoxy(l, c);
                printf("Aposta Ativa - exclua log. primeiro!");
                c++;
                getch();
            }
            else
            {
                rewind(PtrAposta);
                fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
                while (!feof(PtrAposta))
                {
                    if (stricmp(AuxCPF, RegAposta.cpf) != 0)
                        fwrite(&RegAposta, sizeof(TpApostas), 1, PtrTempApostas);

                    fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
                }

                gotoxy(l, c);
                printf("Apostador e apostas excluídos com sucesso!");
                c++;
                getch();
            }

            fclose(PtrAposta);
            fclose(PtrTempApostas);

            if (!apostasAtivas)
            {
                remove("Apostas.dat");
                rename("TempApostas.dat", "Apostas.dat");
            }
            else
            {
                remove("TempApostas.dat");
            }
        }
        else
        {
            gotoxy(l, c);
            printf("Erro ao abrir arquivos de apostas.");
            c++;
            getch();
        }
    }
    else
    {
        if (ptrApostador != NULL)
            fclose(ptrApostador);
    }
}



void exclusaoFisicaConcurso(void) {
    FILE *ptrConcurso = fopen("Concurso.dat", "rb");
    TpConcurso RegConcurso;
    int AuxNum;
    int verifica, l=25, c=10;

    limparquadro();
    moldeCadastrar();

    gotoxy(l,c);
    printf("### EXCLUIR CONCURSO E SUAS APOSTAS###");
    c++;
    if (ptrConcurso == NULL) {
        gotoxy(l,c);
        printf("Erro de abertura do arquivo de Concurso!");
        c++;
    } else {
        gotoxy(l,c);
        printf("Numero do Concurso: ");
        c++;
        scanf("%d", &AuxNum);

        if (AuxNum > 0) {
            verifica = BuscarConcurso(ptrConcurso, AuxNum);
            if (verifica == -1) {
                gotoxy(l,c);
                printf("Concurso não encontrado!");
                c++;
                fclose(ptrConcurso);
                getch();
            } else {
                gotoxy(l,c);
                printf("*** DADOS DO CONCURSO ***");
                c++;
                fseek(ptrConcurso, verifica, 0);
                fread(&RegConcurso, sizeof(TpConcurso), 1, ptrConcurso);
                gotoxy(l,c);
                printf("Numero do Concurso: %d", RegConcurso.numConcurso);
                c++;
                gotoxy(l,c);
                printf("Data: %d %d %d", RegConcurso.date.dia, RegConcurso.date.mes, RegConcurso.date.ano);
                c++;
                gotoxy(l,c);
                printf("Status: %c", RegConcurso.status);
                c++;
                gotoxy(l,c);
                printf("Confirma a Exclusao (S/N)? ");
                c++;
                if (toupper(getche()) == 'S') {
                    if (RegConcurso.status == 'A') {
                        gotoxy(l,c);
                        printf("Concurso esta ativo.");
                        c++;
                        fclose(ptrConcurso);
                        getch();
                    } else {
                        FILE *PtrTemp = fopen("TempConcurso.dat", "wb");
                        rewind(ptrConcurso);
                        fread(&RegConcurso, sizeof(TpConcurso), 1, ptrConcurso);
                        while (!feof(ptrConcurso)) {
                            if (AuxNum != RegConcurso.numConcurso)
                                fwrite(&RegConcurso, sizeof(TpConcurso), 1, PtrTemp);
                            fread(&RegConcurso, sizeof(TpConcurso), 1, ptrConcurso);
                        }
                        fclose(PtrTemp);
                        fclose(ptrConcurso);
                        remove("Concurso.dat");
                        rename("TempConcurso.dat", "Concurso.dat");

                        FILE *PtrAposta = fopen("Apostas.dat", "rb");
                        FILE *PtrTempApostas = fopen("TempApostas.dat", "wb");
                        TpApostas RegAposta;

                        if (PtrAposta != NULL && PtrTempApostas != NULL) {
                            int podeExcluir = 1;

                            fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
                            while (!feof(PtrAposta)) {
                                if (RegAposta.numConcurso == AuxNum && RegAposta.status != 'I')
                                    podeExcluir = 0;
                                fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
                            }

                            rewind(PtrAposta);

                            if (podeExcluir == 0) {
                                gotoxy(l,c);
                                printf("Existem apostas ativas no concurso. Exclua/inative antes.");
                                c++;
                                fclose(PtrAposta);
                                fclose(PtrTempApostas);
                                getch();
                            } else {
                                fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
                                while (!feof(PtrAposta)) {
                                    if (RegAposta.numConcurso != AuxNum)
                                        fwrite(&RegAposta, sizeof(TpApostas), 1, PtrTempApostas);
                                    fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
                                }
                                fclose(PtrAposta);
                                fclose(PtrTempApostas);
                                remove("Apostas.dat");
                                rename("TempApostas.dat", "Apostas.dat");

                                gotoxy(l,c);
                                printf("Concurso e apostas excluídos com sucesso!");
                                c++;
                                getch();
                            }
                        } else {
                            gotoxy(l,c);
                            printf("Erro ao abrir arquivos de apostas.");
                            c++;
                            getch();
                        }
                    }
                } else {
                    gotoxy(l,c);
                    printf("Exclusao cancelada!");
                    c++;
                    getch();
                }
            }
        } else {
            fclose(ptrConcurso);
        }
    }
}



void GerarRelatorioAcertos(void) {
    FILE *PtrAposta = fopen("Apostas.dat", "rb");
    FILE *PtrConcurso = fopen("Concurso.dat", "rb");
	
	moldeCadastrar();
	limparquadro();
	
    TpApostas RegAposta;
    TpConcurso RegConcurso;

    int totalTerno = 0, totalQuadra = 0, totalQuina = 0, l=25, c=10;

    if (PtrAposta != NULL && PtrConcurso != NULL) {
        int resultado = fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
        while (resultado == 1) {
            rewind(PtrConcurso);
            int encontrou = 0;
            int resultadoConc = fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
            while (resultadoConc == 1 && encontrou == 0) {
                if (RegAposta.numConcurso == RegConcurso.numConcurso) {
                    encontrou = 1;
                } else {
                    resultadoConc = fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
                }
            }

            if (encontrou == 1) {
                int acertos = 0;
                int i = 0;
                while (i < RegAposta.qtdeNumApostados) {
                    int j = 0;
                    int achouPar = 0;
                    while (j < TF && achouPar == 0) {
                        int a1 = RegAposta.dezenas[i].numero1;
                        int a2 = RegAposta.dezenas[i].numero2;
                        int s1 = RegConcurso.dezenasSorteadas[j].numero1;
                        int s2 = RegConcurso.dezenasSorteadas[j].numero2;

                        if ((a1 == s1 && a2 == s2) || (a1 == s2 && a2 == s1)) {
                            achouPar = 1;
                        }
                        j++;
                    }
                    if (achouPar == 1) {
                        acertos++;
                    }
                    i++;
                }

                if (acertos == 3) {
                    totalTerno++;
                    gotoxy(l,c);
                    printf("Aposta %d - CPF: %s fez TERNO!", RegAposta.numAposta, RegAposta.cpf);
                    c++;
                }
                if (acertos == 4) {
                    totalQuadra++;
                    gotoxy(l,c);
                    printf("Aposta %d - CPF: %s fez QUADRA!", RegAposta.numAposta, RegAposta.cpf);
                    c++;
                }
                if (acertos == 5) {
                    totalQuina++;
                    gotoxy(l,c);
                    printf("Aposta %d - CPF: %s fez QUINA!", RegAposta.numAposta, RegAposta.cpf);
                    c++;
                }
            }

            resultado = fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
        }
        getch();
        
        limparquadro();
        l=25,c=10;
        
		gotoxy(l,c);
        printf("RELATORIO FINAL:");
        c++;
        gotoxy(l,c);
        printf("Total de Ternos:  %d", totalTerno);
        c++;
        gotoxy(l,c);
        printf("Total de Quadras: %d", totalQuadra);
        c++;
        gotoxy(l,c);
        printf("Total de Quinas:  %d", totalQuina);
        c++;
		
		getch();
        fclose(PtrAposta);
        fclose(PtrConcurso);
    }
}

void GerarResumoPremiadosPorConcurso(void) {
    FILE *PtrAposta = fopen("Apostas.dat", "rb");
    FILE *PtrConcurso = fopen("Concurso.dat", "rb");

    if (PtrAposta == NULL || PtrConcurso == NULL) return;

    TpConcurso RegConcurso;
    TpApostas RegAposta;
    TpResumo resumo[100];
    int totalConcursos = 0;

    rewind(PtrConcurso);
    int r = fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
    while (r == 1) {
        resumo[totalConcursos].numConcurso = RegConcurso.numConcurso;
        resumo[totalConcursos].premiados = 0;

        rewind(PtrAposta);
        int s = fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
        while (s == 1) {
            if (RegAposta.numConcurso == RegConcurso.numConcurso) {
                int acertos = 0;
                int i = 0;
                while (i < RegAposta.qtdeNumApostados) {
                    int j = 0;
                    int achou = 0;
                    while (j < TF && achou == 0) {
                        int a1 = RegAposta.dezenas[i].numero1;
                        int a2 = RegAposta.dezenas[i].numero2;
                        int s1 = RegConcurso.dezenasSorteadas[j].numero1;
                        int s2 = RegConcurso.dezenasSorteadas[j].numero2;

                        if ((a1 == s1 && a2 == s2) || (a1 == s2 && a2 == s1)) 
                            achou = 1;
                        j++;
                    }
                    if (achou == 1) 
                        acertos++;
                    i++;
                }

                if (acertos >= 3) 
                    resumo[totalConcursos].premiados++;
                
            }

            s = fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
        }

        totalConcursos++;
        r = fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
    }

    BubbleSortResumo(resumo, totalConcursos);

    limparquadro();
    int l = 25, c = 10;
    gotoxy(l, c);
    printf("RESUMO DE PREMIADOS POR CONCURSO:");
    c++;

    int i = 0;
    while (i < totalConcursos) {
        gotoxy(l, c);
        printf("Concurso %d - Premiados: %d", resumo[i].numConcurso, resumo[i].premiados);
        c++;
        i++;
    }

    getch();
    fclose(PtrAposta);
    fclose(PtrConcurso);
}

void ListarAcertadoresPorQuantidade(void) {
    FILE *PtrAposta = fopen("Apostas.dat", "rb");
    FILE *PtrConcurso = fopen("Concurso.dat", "rb");

    if (PtrAposta == NULL || PtrConcurso == NULL) return;

    TpApostas RegAposta;
    TpConcurso RegConcurso;

    int l = 25, c = 10;
    int numeroConcurso, quantidadeDesejada;

    moldeCadastrar();
    limparquadro();

    gotoxy(l, c);
    printf("NUMERO DO CONCURSO: ");
    c++;
    gotoxy(l, c);
    numeroConcurso = lerInteiroValido(l, c, 70);
    c++;
    gotoxy(l, c);
    printf("QUANTIDADE DE ACERTOS (3, 4 ou 5): ");
    c++;
    gotoxy(l, c);
    quantidadeDesejada = lerInteiroValido(l, c, 70);
    c++;

    rewind(PtrConcurso);
    int achouConcurso = 0;
    int r = fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
    while (r == 1 && achouConcurso == 0) {
        if (RegConcurso.numConcurso == numeroConcurso) {
            achouConcurso = 1;
        } else {
            r = fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
        }
    }

    if (achouConcurso == 1 && (quantidadeDesejada >= 3 && quantidadeDesejada <= 5)) {
        rewind(PtrAposta);
        int encontrou = 0;
        int index = fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
        while (index == 1) {
            if (RegAposta.numConcurso == numeroConcurso) {
                int acertos = 0, i =0;
                TpDezenas acertosDezenas[TF];
                int idxAcertos = 0;

                while (i < RegAposta.qtdeNumApostados) {
                    int j = 0, achou = 0;
                    while (j < TF && achou == 0) {
                        int a1 = RegAposta.dezenas[i].numero1;
                        int a2 = RegAposta.dezenas[i].numero2;
                        int s1 = RegConcurso.dezenasSorteadas[j].numero1;
                        int s2 = RegConcurso.dezenasSorteadas[j].numero2;

                        if ((a1 == s1 && a2 == s2) || (a1 == s2 && a2 == s1)) {
                            achou = 1;
                            acertosDezenas[idxAcertos].numero1 = a1;
                            acertosDezenas[idxAcertos].numero2 = a2;
                            idxAcertos++;
                        }
                        j++;
                    }
                    if (achou == 1) {
                        acertos++;
                    }
                    i++;
                }

                if (acertos == quantidadeDesejada) {
                    gotoxy(l, c);
                    printf("Aposta %d - CPF: %s - %d acertos", RegAposta.numAposta, RegAposta.cpf, acertos);
                    c++;

                    for (int k = 0; k < idxAcertos; k++) {
                        gotoxy(l, c);
                        printf("  Dezena acertada %d: %02d e %02d", k + 1,
                               acertosDezenas[k].numero1, acertosDezenas[k].numero2);
                        c++;
                    }

                    encontrou = 1;
                }
            }
            index = fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
        }

        if (encontrou == 0) {
            gotoxy(l, c);
            printf("Nenhum apostador com %d acertos no concurso %d", quantidadeDesejada, numeroConcurso);
            c++;
        }
    } else {
        gotoxy(l, c);
        printf("Concurso nao encontrado ou quantidade invalida");
        c++;
    }

    getch();
    fclose(PtrAposta);
    fclose(PtrConcurso);
}

void NumerosMaisEMenosAparecem(void) {
	int l=25, c=10;
    FILE *PtrConcurso = fopen("Concurso.dat", "rb");
    if (PtrConcurso == NULL){
    	gotoxy(l,c);
    	printf("Erro de abertura");
    	c++;
	}
	else{
		  int frequencia[61] = {0}; // índice 1 a 60

    	TpConcurso RegConcurso;
    	int resultado = fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
    	while (resultado == 1) {
        	for (int i = 0; i < TF; i++) {
            	frequencia[RegConcurso.dezenasSorteadas[i].numero1]++;
            	frequencia[RegConcurso.dezenasSorteadas[i].numero2]++;
        	}
        	resultado = fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
    	}

    	int maisFreq = 0, menosFreq = 1000000;
    	int numMais = 0, numMenos = 0;

    	for (int i = 1; i <= 60; i++) {
        	if (frequencia[i] > maisFreq) {
           	 maisFreq = frequencia[i];
            	numMais = i;
        	}
        	if (frequencia[i] < menosFreq) {
            	menosFreq = frequencia[i];
            	numMenos = i;
        	}
    	}

    	 l = 25, c = 10;
    	moldeCadastrar();
    	limparquadro();

    	gotoxy(l, c);
    	printf("Numero que MAIS aparece: %02d, apareceu %d vezes", numMais, maisFreq);
    	c++;
    	gotoxy(l, c);
    	printf("Numero que MENOS aparece: %02d, apareceu %d vezes", numMenos, menosFreq);
    	c++;

    	getch();
    	fclose(PtrConcurso);
	}
	}

  

void NumerosMaisEMenosApostados(void) {
    FILE *PtrAposta = fopen("Apostas.dat", "rb");
    int l=25,c=10;
    if (PtrAposta == NULL){
    	gotoxy(l,c);
    	printf("Erro de Abertura!");
    	c++;
	}

    int frequencia[61] = {0}; // índice de 1 a 60

    TpApostas RegAposta;
    int resultado = fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
    while (resultado == 1) {
        for (int i = 0; i < RegAposta.qtdeNumApostados; i++) {
            frequencia[RegAposta.dezenas[i].numero1]++;
            frequencia[RegAposta.dezenas[i].numero2]++;
        }
        resultado = fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
    }

    int maisFreq = 0, menosFreq = 1000000;
    int numMais = 0, numMenos = 0;

    for (int i = 1; i <= 60; i++) {
        if (frequencia[i] > maisFreq) {
            maisFreq = frequencia[i];
            numMais = i;
        }
        if (frequencia[i] < menosFreq) {
            menosFreq = frequencia[i];
            numMenos = i;
        }
    }

     l = 25, c = 10;
    moldeCadastrar();
    limparquadro();

    gotoxy(20, c);
    printf("Numero que MAIS foi apostado: %02d, apostado %d vezes", numMais, maisFreq);
    c++;
    gotoxy(20, c);
    printf("Numero que MENOS foi apostado: %02d, apostado %d vezes", numMenos, menosFreq);
    c++;

    getch();
    fclose(PtrAposta);
}


//Estatisticas Adicionais
void consultarApostasPorCPF(void) {
    FILE *PtrApostadores = fopen("Apostadores.dat", "rb");
    FILE *PtrAposta = fopen("Apostas.dat", "rb");
    char auxCpf[15];
    int l = 25, c = 10, apostadorExiste = 0, encontrado = 0;
    TpApostas RegAposta;

    if (PtrApostadores != NULL && PtrAposta != NULL) {
        moldeMenuCadastro();
        limparquadro();
        gotoxy(l, c);
        printf("Digite o CPF do apostador para consulta: ");
        c++;
        entradaTextoControlada(l, c, 14, auxCpf);
        c++;

        int verifica = BuscarApostador(PtrApostadores, auxCpf);

        if (verifica == -1) {
            gotoxy(l, c);
            printf("Apostador nao cadastrado!");
            c++;
            gotoxy(l, c);
            printf("Pressione qualquer tecla para sair...");
            getch();
        } else {
            rewind(PtrAposta);
            while (fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta) == 1) {
                if (strcmp(RegAposta.cpf, auxCpf) == 0) {
                    encontrado = 1;
                    gotoxy(l, c);
                    printf("Aposta Nº %d - Concurso Nº %d - Qtde dezenas: %d", RegAposta.numAposta, RegAposta.numConcurso, RegAposta.qtdeNumApostados);
                    c++;
                    for (int i = 0; i < RegAposta.qtdeNumApostados; i++) {
                        gotoxy(l + 2, c);
                        printf("Dezena %d: %02d e %02d", i + 1, RegAposta.dezenas[i].numero1, RegAposta.dezenas[i].numero2);
                        c++;
                    }
                    c++;
                    if (c > 10) {
                        gotoxy(l, c);
                        printf("Pressione qualquer tecla para continuar...");
                        getch();
                        limparquadro();
                        c = 10;
                    }
                }
            }
            if (encontrado == 0) {
                gotoxy(l, c);
                printf("Nenhuma aposta encontrada para o CPF informado.");
                c++;
            }
            gotoxy(l, c);
            printf("Pressione qualquer tecla para sair...");
            getch();
        }
        fclose(PtrApostadores);
        fclose(PtrAposta);
    }
}


void ExibirArrecadacao(void) {
    int numConcurso, posConcurso;
    float valorAposta = 5.0, arrecadacao = 0.0;
    FILE *PtrConcurso = fopen("Concurso.dat", "rb+");
    FILE *PtrAposta = fopen("Apostas.dat", "rb");
    TpApostas RegAposta;
    int resultado, totalApostas = 0, abriuArquivos = 1, l=25, c=10;

    if (PtrConcurso == NULL || PtrAposta == NULL) {
        abriuArquivos = 0;
    }

    if (abriuArquivos == 1) {
        moldeMenuCadastro();
        limparquadro();
        gotoxy(l,c);
        printf("Digite o NUMERO do CONCURSO: ");
        c++;
        gotoxy(l,c);
        scanf("%d", &numConcurso);
        c++;

        BubbleSortConcursoDecrescente(PtrConcurso);
        posConcurso = BuscaBinariaConcurso(PtrConcurso, numConcurso);

        if (posConcurso == -1) {
            gotoxy(l,c);
            printf("CONCURSO nao encontrado.");
            c++;
        } 
		else {
            rewind(PtrAposta);
            resultado = fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
            while (resultado == 1) {
                if (RegAposta.numConcurso == numConcurso) 
                    totalApostas = totalApostas + 1;
                resultado = fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
            }
            arrecadacao = totalApostas * valorAposta;
            gotoxy(l,c);
            printf("Total arrecadado no concurso %d: R$ %.2f", numConcurso, arrecadacao);
            c++;
        }
        getch();
        limparquadro();
    } else {
        moldeMenuCadastro();
        limparquadro();
        gotoxy(l,c);
        printf("Erro ao abrir os arquivos.");
        c++;
        getch();
        limparquadro();
    }

    if (PtrConcurso != NULL) fclose(PtrConcurso);
    if (PtrAposta != NULL) fclose(PtrAposta);
}


void PercentualApostadoresSemAcerto(void) {
    FILE *PtrApostadores = fopen("Apostadores.dat", "rb");
    FILE *PtrApostas = fopen("Apostas.dat", "rb");
    FILE *PtrConcurso = fopen("Concurso.dat", "rb");

    TpApostadores RegApostador;
    TpApostas RegAposta;
    TpConcurso RegConcurso;

    int totalApostadores = 0,apostadoresSemAcerto = 0;

    if (PtrApostadores != NULL && PtrApostas != NULL && PtrConcurso != NULL) {
        int resultadoApostador = fread(&RegApostador, sizeof(TpApostadores), 1, PtrApostadores);
        while (resultadoApostador == 1) {
            totalApostadores++;

            int temAcerto = 0;

            rewind(PtrApostas);
            int resultadoAposta = fread(&RegAposta, sizeof(TpApostas), 1, PtrApostas);
            while (resultadoAposta == 1 && temAcerto == 0) {
                if (strcmp(RegApostador.cpf, RegAposta.cpf) == 0) {

                    rewind(PtrConcurso);
                    int resultadoConc = fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
                    int achouConcurso = 0;
                    while (resultadoConc == 1 && achouConcurso == 0) {
                        if (RegConcurso.numConcurso == RegAposta.numConcurso) {
                            achouConcurso = 1;
                        } else {
                            resultadoConc = fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
                        }
                    }

                    if (achouConcurso == 1) {
                        int acertos = 0;
                        int i = 0;
                        while (i < RegAposta.qtdeNumApostados && temAcerto == 0) {
                            int j = 0;
                            int achouPar = 0;
                            while (j < TF && achouPar == 0) {
                                int a1 = RegAposta.dezenas[i].numero1;
                                int a2 = RegAposta.dezenas[i].numero2;
                                int s1 = RegConcurso.dezenasSorteadas[j].numero1;
                                int s2 = RegConcurso.dezenasSorteadas[j].numero2;

                                if ((a1 == s1 && a2 == s2) || (a1 == s2 && a2 == s1)) {
                                    achouPar = 1;
                                }
                                j++;
                            }
                            if (achouPar == 1) {
                                acertos++;
                            }
                            i++;
                        }

                        if (acertos >= 3) {
                            temAcerto = 1;
                        }
                    }
                }
                if (temAcerto == 0) {
                    resultadoAposta = fread(&RegAposta, sizeof(TpApostas), 1, PtrApostas);
                }
            }

            if (temAcerto == 0) {
                apostadoresSemAcerto++;
            }

            resultadoApostador = fread(&RegApostador, sizeof(TpApostadores), 1, PtrApostadores);
        }

        float percentual = 0.0;
        if (totalApostadores > 0) {
            percentual = ((float)apostadoresSemAcerto / totalApostadores) * 100.0;
        }

        int l = 25, c = 10;
        limparquadro();
        gotoxy(l, c);
        printf("Total de apostadores: %d", totalApostadores);
        c++;
        gotoxy(l, c);
        printf("Apostadores sem acerto relevante: %d", apostadoresSemAcerto);
        c++;
        gotoxy(l, c);
        printf("Percentual sem acerto: %.2f%%", percentual);
        c++;

        fclose(PtrApostadores);
        fclose(PtrApostas);
        fclose(PtrConcurso);

        getch();
    }
}



void GerarRankingConcursos() {
    FILE *PtrApostas = fopen("Apostas.dat", "rb");
    FILE *PtrRanking = fopen("Ranking.dat", "wb+");

    if (PtrApostas == NULL || PtrRanking == NULL) return;

    TpApostas regAposta;
    TpRankingConcurso regRanking[1000]; 
    int countConcursos = 0, l=25,c=10;
    moldeCadastrar();
    limparquadro();

    while (fread(&regAposta, sizeof(TpApostas), 1, PtrApostas) == 1) {
        int i = 0, achou = 0;
        while (i < countConcursos && achou == 0) {
            if (regRanking[i].numConcurso == regAposta.numConcurso) {
                regRanking[i].totalApostas++;
                achou = 1;
            }
            i++;
        }
        if (achou == 0) {
            regRanking[countConcursos].numConcurso = regAposta.numConcurso;
            regRanking[countConcursos].totalApostas = 1;
            countConcursos++;
        }
    }

    for (int i = 0; i < countConcursos; i++) {
        fwrite(&regRanking[i], sizeof(TpRankingConcurso), 1, PtrRanking);
    }

    fclose(PtrApostas);

   
    BubbleSortRanking(PtrRanking, countConcursos);

    
    rewind(PtrRanking);
    TpRankingConcurso Reg;
    int pos = 1;
    while (fread(&Reg, sizeof(TpRankingConcurso), 1, PtrRanking) == 1) {
    	gotoxy(l,c);
        printf("%d - Concurso %d: %d apostas", pos, Reg.numConcurso, Reg.totalApostas);
        c++;
        pos++;
    }
	getch();
    fclose(PtrRanking);
}


void CalcularMediaAcertosPorApostador() {
    FILE *PtrApostador = fopen("Apostadores.dat", "rb");
    FILE *PtrAposta = fopen("Apostas.dat", "rb");
    FILE *PtrConcurso = fopen("Concurso.dat", "rb");

    TpApostadores RegApostador;
    TpApostas RegAposta;
    TpConcurso RegConcurso;

    int l = 25, c = 10;
    moldeCadastrar();
    limparquadro();

    if (PtrApostador != NULL && PtrAposta != NULL && PtrConcurso != NULL) {
        fread(&RegApostador, sizeof(TpApostadores), 1, PtrApostador);
        while (!feof(PtrApostador)) {
            int totalAcertos = 0, totalApostas = 0;

            rewind(PtrAposta);
            fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
            while (!feof(PtrAposta)) {
                if (strcmp(RegAposta.cpf, RegApostador.cpf) == 0) {
                    rewind(PtrConcurso);
                    fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
                    while (!feof(PtrConcurso)) {
                        if (RegAposta.numConcurso == RegConcurso.numConcurso) {
                            int acertos = 0, i = 0;
                            while (i < RegAposta.qtdeNumApostados) {
                                int j = 0, achou = 0;
                                while (j < TF && achou == 0) {
                                    int a1 = RegAposta.dezenas[i].numero1;
                                    int a2 = RegAposta.dezenas[i].numero2;
                                    int s1 = RegConcurso.dezenasSorteadas[j].numero1;
                                    int s2 = RegConcurso.dezenasSorteadas[j].numero2;

                                    if ((a1 == s1 && a2 == s2) || (a1 == s2 && a2 == s1)) {
                                        achou = 1;
                                    }
                                    j++;
                                }
                                if (achou == 1) {
                                    acertos++;
                                }
                                i++;
                            }

                            if (acertos >= 3) {
                                totalAcertos += acertos;
                            }

                            totalApostas++;
                        }

                        fread(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
                    }
                }

                fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
            }

            gotoxy(l, c);
            printf("CPF: %s - Media de Acertos: ", RegApostador.cpf);
            if (totalApostas > 0) {
                printf("%.2f", (float)totalAcertos / totalApostas);
            } else {
                printf("0.00");
            }
            c++;

            fread(&RegApostador, sizeof(TpApostadores), 1, PtrApostador);
        }

        gotoxy(l, c + 1);
        printf("Pressione qualquer tecla para continuar...");
        getch();

        fclose(PtrApostador);
        fclose(PtrAposta);
        fclose(PtrConcurso);
    }
}


void DistribuicaoParticipacaoApostadores() {
    FILE *PtrAposta = fopen("Apostas.dat", "rb");
    FILE *PtrApostador = fopen("Apostadores.dat", "rb");

    TpApostadores RegApostador;
    TpApostas RegAposta;

    int totalUm = 0, totalMaisDeUm = 0, maxApostas = 0, total = 0, i = 0;

    if (PtrAposta != NULL && PtrApostador != NULL) {
        fseek(PtrApostador, 0, 2);
        int totalApostadores = ftell(PtrApostador) / sizeof(TpApostadores);
        rewind(PtrApostador);

        while (i < totalApostadores) {
            fseek(PtrApostador, i * sizeof(TpApostadores), 0);
            fread(&RegApostador, sizeof(TpApostadores), 1, PtrApostador);

            int cont = 0;
            rewind(PtrAposta);
            fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
            while (!feof(PtrAposta)) {
                if (strcmp(RegAposta.cpf, RegApostador.cpf) == 0) {
                    cont++;
                }
                fread(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
            }

            if (cont == 1) {
                totalUm++;
            } else if (cont > 1) {
                totalMaisDeUm++;
            }

            if (cont > maxApostas) {
                maxApostas = cont;
            }

            i++;
        }

        limparquadro();
        moldeCadastrar();
        gotoxy(25, 10);
        printf("Total de apostadores com apenas uma aposta: %d", totalUm);
        gotoxy(25, 11);
        printf("Total de apostadores com mais de uma aposta: %d", totalMaisDeUm);
        gotoxy(25, 12);
        printf("Maior numero de apostas feitas por um apostador: %d", maxApostas);
        getch();

        fclose(PtrAposta);
        fclose(PtrApostador);
    }
}



char menu(void) {
	printf("# # # # MENU # # # # \n");
	textcolor(1);
	printf("[A] CADASTRAR APOSTADORES\n");
	printf("[B] CADASTRAR CONCURSOS\n");
	printf("[C] CADASTRAR APOSTAS\n");
	textcolor(2);
	printf("[E] ALTERAR APOSTADORES\n");
	printf("[F] ALTERAR CONCURSOS\n");
	printf("[G] ALTERAR APOSTAS \n");
	textcolor(3);
	printf("[I] EXIBIR APOSTADORES\n");
	printf("[J] EXIBIR CONCURSOS\n");
	printf("[K] EXIBIR APOSTAS\n");
	textcolor(5);
	printf("[M] Excluir CLIENTES\n");
	printf("[N] Excluir MOTOQUEIROS\n");
	printf("[O] Excluir PIZZAS\n");
	printf("[P] Excluir PEDIDOS\n");
	textcolor(7);
	
	return toupper(getche());
}

char menuNum(void) {
	esconderCursor();
	int x=30, y=10;
	travarCursor(x,y);
	clrscr();
	moldeMenuInicial();
	
	gotoxy(14,12);
	printf("[1] Cadastrar");

	gotoxy(38,12);
	printf("[2] Alterar");

	gotoxy(60,12);
	printf("[3] Exibir");

	gotoxy(15,19);
	printf("[4] Excluir");

	gotoxy(36,19);
	printf("[5] Relatorio");

	gotoxy(58,19);
	printf("[6] Estatistica");
	gotoxy(76,23);

while (kbhit()) getch();  // limpa o buffer de teclado antes de esperar tecla real
		

	return getch();
}

char menuCad(void) {
	clrscr();
	moldeMenuCadastro();
	
	gotoxy(22,12);
	printf("[1] APOSTADOR");

	gotoxy(51,12);
	printf("[2] CONCURSOS");

	gotoxy(23,19);
	printf("[3] APOSTAS");
	
	gotoxy(53,19);
	gotoxy(76,23);

	return getch();
}

char menuExib(void) {
	clrscr();
	moldeMenuExibir();
	
	gotoxy(22,12);
	printf("[1] APOSTADOR");

	gotoxy(51,12);
	printf("[2] CONCURSOS");

	gotoxy(23,19);
	printf("[3] APOSTAS");
	
	gotoxy(53,19);
	gotoxy(76,23);

	return getch();
}

char menuAlt(void) {
	clrscr();
	moldeMenuAlterar();
	
	gotoxy(22,12);
	printf("[1] APOSTADOR");

	gotoxy(51,12);
	printf("[2] CONCURSOS");

	gotoxy(23,19);
	printf("[3] APOSTAS");
	
	gotoxy(53,19);
	gotoxy(76,23);

	return getch();
}

char menuExclLF(void) {
	clrscr();
	moldeMenuTipoExclusao();

	gotoxy(23,15);
	printf("[1] LOGICA");
	
	gotoxy(54,15);
	printf("[2] FISICA");
	gotoxy(76,23);

	return getch();
}

char menuExcl(void) {
	clrscr();
	moldeMenuExcluir();
	
	gotoxy(22,12);
	printf("[1] APOSTADOR");

	gotoxy(51,12);
	printf("[2] CONCURSOS");

	gotoxy(23,19);
	printf("[3] APOSTAS");
	
	gotoxy(53,19);
	gotoxy(76,23);

	return getche();
}

char menuExclFisicaa(void) {
	clrscr();
	moldeMenuExcluirFisica();
	
	gotoxy(22,12);
	printf("[1] APOSTADOR");

	gotoxy(51,12);
	printf("[2] CONCURSOS");

	
	gotoxy(53,19);
	gotoxy(76,23);

	return getche();
}

char menuRel(void) {
	clrscr();
	moldeMenuRelatorio();

	gotoxy(17,11); printf("Exibir");
	gotoxy(13,12); printf("[1] Relatorio");
	gotoxy(17,13); printf("Acertos");

	gotoxy(40,11); printf("Relatorio");
	gotoxy(35,12); printf("[2]  Premiados");
	gotoxy(39,13); printf("por concurso");

	gotoxy(62,11); printf("Acertadores");
	gotoxy(58,12); printf("[3] por quant.");
	gotoxy(62,13); printf("Especifica");
	
	gotoxy(26,18); printf("Numeros");
	gotoxy(22,19); printf("[4]mais/menos ");
	gotoxy(26,20); printf("Aparecem");

	gotoxy(55,18); printf("Numeros");
	gotoxy(49,19); printf("[5] mais/menos");
	gotoxy(54,20); printf("Apostados");

	gotoxy(76,23);

	return getche();
}

char menuEst(void) {
	clrscr();
	moldeMenuEstatisticas();

	gotoxy(16,11); printf("Consultar");
	gotoxy(13,12); printf("[1]  Apostas");
	gotoxy(16,13); printf("por cpf");

	gotoxy(38,11); printf("Exibir");
	gotoxy(35,12); printf("[2] Arrecadacao");
	gotoxy(38,13); printf("por concurso");

	gotoxy(60,11); printf("Percentual");
	gotoxy(58,12); printf("[3]apostadores");
	gotoxy(64,13); printf("s/acertos");
	
	gotoxy(16,18); printf("Ranking");
	gotoxy(13,19); printf("[4]  Apostas");
	gotoxy(16,20); printf("por concurso");

	gotoxy(36,18); printf("Media de ");
	gotoxy(35,19); printf("[5]acertos cada");
	gotoxy(40,20); printf("apostador");

	gotoxy(59,18); printf("Distribuicao");
	gotoxy(58,19); printf("[6] de apostas");
	gotoxy(60,20); printf("");

	gotoxy(76,23);
	
	return getch();
}

int main(void){
	char op;
	do {
		op = menuNum();
		clrscr();
		
		switch(op){
			case '1':
				op = menuCad();

				switch (op) {
					case '1':
						CadastrarApostador();
						break;
						
					case '2':
						CadastrarConcurso();
						break;
						
					case '3':
						CadastrarAposta();
						break;
				}

			break;

			case '2':
				op = menuAlt();

				switch (op) {
					case '1':
						AlterarApostador();
						break;	
						
					case '2':
						AlterarConcurso();
						break;	
						
					case '3':
						AlterarAposta();
						break;
				}

			break;
			
			case '3':
				op = menuExib ();
				switch(op){
					case '1':
						exibirApostador();
						break;
					case '2':
						exibirConcurso();
						break;
					case '3':
						exibirAposta();
						break;
				}
			break;
			case '4':
			op = menuExclLF();
				switch(op){
					case '1':
						op = menuExcl();
							switch(op)
							{
								case '1':
									exclusaoLogicaApostador();
									break;
									
								case '2':
									exclusaoLogicaConcurso();
									break;
								case '3':
									exclusaoLogicaAposta();
									break;
							}
					break;
					case '2':
						op=menuExclFisicaa();
							switch(op){
								case '1':
									exclusaoFisicaApostador();
									break;
								case '2':
									exclusaoFisicaConcurso();
									break;
							}
							break;
				}
				break;
			case '5':
				op = menuRel();
					switch(op){
						case '1': GerarRelatorioAcertos();
						break;
						case '2':GerarResumoPremiadosPorConcurso();
						break;
						case '3':ListarAcertadoresPorQuantidade();
						break;
						case '4': NumerosMaisEMenosAparecem();
						break;
						case '5':NumerosMaisEMenosApostados();
						break;
					}
			case '6': 
				op = menuEst();
					switch(op){
						case '1': consultarApostasPorCPF();
						break;
						case '2': ExibirArrecadacao();
						break;
						case '3': PercentualApostadoresSemAcerto();
						break;
						case '4':GerarRankingConcursos();
						break;
						case '5': CalcularMediaAcertosPorApostador();
						break;
						case '6':DistribuicaoParticipacaoApostadores();
						break;
					}	
				break;
		}

	} while(op != 27);
}

