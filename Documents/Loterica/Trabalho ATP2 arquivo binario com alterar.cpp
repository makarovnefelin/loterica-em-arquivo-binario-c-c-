//LotericaFipp Thales Eduardo Mendes de OLiveira, Renan Carvalho Silva , Carlos Francisco 

#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#define TF 10

struct TpData{
int dia, mes, ano;	
};

struct TpConcurso 
{
	int numConcurso; //chave primária
	TpData date;
	int numSorteados[TF];
	char status;
};

struct TpApostadores{
	char cpf [15]; //chave primaria
	char nome [30];
	int numTel;
	char status;
};

struct TpApostas{
	int numAposta; //chave primaria
	int numConcurso;
	char cpf[15];
	int qtdeNumApostado;
	int numApostados[TF];
	char status;
};
//menu
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

void moldura(int colunai, int linhai, int colunaf, int linhaf, int frente, int fundo){
	textcolor(frente);
	textbackground(fundo);
	
	gotoxy(colunai, linhai); 
	printf("%c", 201); 
	gotoxy(colunaf, linhai); 
	printf("%c", 187);
	gotoxy(colunai, linhaf); 
	printf("%c", 200); 
	gotoxy(colunaf, linhaf); 
	printf("%c", 188);
	
	for(int a = colunai + 1; a < colunaf; a++){ 
		gotoxy(a, linhai); printf("%c", 205); 			
		gotoxy(a, linhaf); printf("%c", 205);
	}
	for(int b = linhai + 1; b < linhaf; b++){
		gotoxy(colunai, b); printf("%c", 186);
		gotoxy(colunaf, b); printf("%c", 186);
	}
	textcolor(7);
	textbackground(0);
	
}

void moldeCadastrar(void){
	moldura(10, 5, 75, 23, 7, 4);
	moldura(11, 6, 74, 8, 7, 12); 
	gotoxy(33, 7); 
	printf("* * * LOTERICA FIPP * * *");
			
}

void moldeMenuTipoExclusao(void){
	moldura(10, 5, 75, 23, 7, 4); 
	moldura(11, 6, 74, 8, 7, 12); 

	moldura(19,13,37,17,7,5); 
	moldura(50,13,68,17,7,5); 

	gotoxy(33, 7); 
	printf("* * * EXCLUIR * * *");
}

void moldeMenuExcluir(void){
	moldura(10, 5, 75, 23, 7, 4); 
	moldura(11, 6, 74, 8, 7, 12); 

	moldura(18,10,36,14,7,5);  
	moldura(49,10,67,14,7,5); 

	gotoxy(33, 7); 
	printf("* * * EXCLUIR * * *");
}

void moldeMenuAlterar(void){
	moldura(10, 5, 75, 23, 7, 4); 
	moldura(11, 6, 74, 8, 7, 12); 

	moldura(18,10,36,14,7,3); 
	moldura(49,10,67,14,7,3); 

	moldura(18,17,36,21,7,3); 

	gotoxy(33, 7); 
	printf("* * * ALTERAR * * *");
}

void moldeMenuExibir(void){
	moldura(10, 5, 75, 23, 7, 4); 
	moldura(11, 6, 74, 8, 7, 12);

	moldura(18,10,36,14,7,1);  
	moldura(49,10,67,14,7,1); 

	moldura(18,17,36,21,7,1); 

	gotoxy(33, 7); 
	printf("* * * EXIBIR * * *");
}

void moldeMenuCadastro(void){
	moldura(10, 5, 75, 23, 7, 4); 
	moldura(11, 6, 74, 8, 7, 12);

	moldura(18,10,36,14,7,2); 
	moldura(49,10,67,14,7,2); 

	moldura(18,17,36,21,7,2);  

	gotoxy(33, 7); 
	printf("* * * CADASTRAR * * *");
}

void moldeMenuInicial(void){
	
	moldura(10, 5, 75, 23, 7, 4); 
	moldura(11, 6, 74, 8, 7, 12); 
	
	moldura(12,10,28,14,7,6); 
	moldura(34,10,51,14,7,6); 
	moldura(57,10,73,14,7,6); 
	
	moldura(12,17,28,21,7,6);  
	moldura(34,17,51,21,7,6); 

	gotoxy(33, 7); 
	printf("* * * LOTERICA FIPP * * *");	
}

void moldeMenuRelatorio(void) {
	
	moldura(10, 5, 75, 23, 7, 4); 
	moldura(11, 6, 74, 8, 7, 12); 

	moldura(12,10,28,14,13,14); 
	moldura(34,10,51,14,13,14); 
	moldura(57,10,73,14,13,14); 

	moldura(21,17,37,21,13,14); 
	moldura(48,17,64,21,13,14);   

	gotoxy(33, 7); 
	printf("* * * RELATORIO * * *");
}


char menuCad(void) {
	clrscr();
	moldeMenuCadastro();
	
	gotoxy(22,12);
	printf("[1] APOSTADORES");

	gotoxy(51,12);
	printf("[2] CONCURSO");

	gotoxy(23,19);
	printf("[3] APOSTAS");
	gotoxy(76,23);

	return getch();
}

char menuExib(void) {
	clrscr();
	moldeMenuExibir();
	
	gotoxy(22,12);
	printf("[1] APOSTADORES");

	gotoxy(51,12);
	printf("[2] CONCURSO");

	gotoxy(23,19);
	printf("[3] APOSTAS");
	
	gotoxy(76,23);
	return getch();
}

char menuAlt(void) {
	clrscr();
	moldeMenuAlterar();
	
	gotoxy(22,12);
	printf("[1] APOSTADORES");

	gotoxy(51,12);
	printf("[2] CONCURSO");

	gotoxy(23,19);
	printf("[3] APOSTAS");
	
	gotoxy(76,23);

	return getch();
}

char menuExclLF(void) {
	clrscr();
	moldeMenuTipoExclusao();

	gotoxy(23,15);
	printf("[1] FISICA");
	
	gotoxy(54,15);
	printf("[2] LOGICA");
	gotoxy(76,23);

	return getch();
}

char menuExcl(void) {
	clrscr();
	moldeMenuExcluir();
	
	gotoxy(22,12);
	printf("[1] APOSTADORES");

	gotoxy(51,12);
	printf("[2] CONCURSO");
	gotoxy(76,23);
	return getch();
}
void limparquadro(void){
	int l = 12, c = 9;
	
	while(c <= 22){
		gotoxy(l,c);
		printf("                                                               ");
		c++;
	}
}

char menuRel(void) {
	limparquadro();
	moldeMenuRelatorio();

	gotoxy(17,11); printf("Exibir");
	gotoxy(13,12); printf("[1] Bolao");
	gotoxy(17,13); printf("Apostas");

	gotoxy(40,11); printf("Resumo");
	gotoxy(35,12); printf("[2]  Apostador");
	gotoxy(39,13); printf("quantidade");

	gotoxy(62,11); printf("Relatorio");
	gotoxy(58,12); printf("[3]Numeros");
	gotoxy(62,13); printf("Especificos");
	
	gotoxy(26,18); printf("Exibir");
	gotoxy(22,19); printf("[4] Num");
	gotoxy(26,20); printf("Maior/Menor");

	gotoxy(55,18); printf("Exibir");
	gotoxy(49,19); printf("[5]Num mais/menos");
	gotoxy(54,20); printf("Apostados");

	gotoxy(76,23);

	return getch();
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

//Cadastros
void CadastrarApostador(void)
{
	moldeCadastrar();
	TpApostadores RegApostador;
	FILE * PtrApostador = fopen("Apostadores.dat", "ab+");
	char auxcpf [15];
	int Verifica; 
	printf("\n ##Cadastrar APOSTADOR ##\n");
	printf("CPF do APOSTADOR que deseja cadastrar (000.000.000-00)\n"); fflush(stdin);
	gets(auxcpf);
		if(PtrApostador == NULL)
			printf("Erro de Abertura\n");
		else
			{
				
					while (strcmp(auxcpf,"\0")!=0)
					{
						Verifica = BuscarApostador(PtrApostador, auxcpf);	
						if(Verifica == -1)
						{
							strcpy(RegApostador.cpf, auxcpf);
							printf("Nome do APOSTADOR: \n");
							gets(RegApostador.nome);
							printf("Numero do telefone: \n");
							scanf("%d", &RegApostador.numTel);
							RegApostador.status = 'A';
							fwrite(&RegApostador, sizeof(TpApostadores), 1, PtrApostador);
							printf("APOSTADOR cadastrado com sucesso\n");
						}
						else{
								printf("Apostador ja CADASTRADO\n");
						}
							printf("\n ##Cadastrar APOSTADOR ##\n");
							printf("CPF do APOSTADOR que deseja cadastrar\n"); fflush(stdin);
							gets(auxcpf);
				 	}
				fclose(PtrApostador);
				getch();
			}
			
}


void CadastrarConcurso (void){
	FILE *PtrConcurso = fopen("Concurso.dat", "ab+");
	TpConcurso RegConcurso;
	int Verifica, auxNum;
	printf("\n## CADASTRO de CONCURSOS## \n");
	printf("NUMERO do CONCURSO: \n");
	scanf("%d", &auxNum);
	if(PtrConcurso == NULL)
		printf("Erro de Abertura!!\n");
	else
	{
		while(auxNum > 0)
			{
				Verifica = BuscarConcurso(PtrConcurso, auxNum);
				if(Verifica == -1)//Nao existe entao cadastra
				{
					RegConcurso.numConcurso = auxNum;
					printf("DATA do CONCURSO (D, M, A): \n");
					scanf("%d %d %d", &RegConcurso.date.dia, &RegConcurso.date.mes, &RegConcurso.date.ano);
					//fazer uma busca para sortear os numeros
					RegConcurso.status = 'A';
					
					fwrite(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
					printf("CONCURSO CADASTRADO com sucesso\n");
				}
				else{
					printf("CONCURSO JA CADASTRADO!!!\n");	
				}
				printf("\n## CADASTRO de CONCURSOS## \n");
				printf("NUMERO do CONCURSO: \n");
				scanf("%d", &auxNum);
			}
		getch();
		fclose (PtrConcurso);
	}
}



void CadastrarAposta(void){
	FILE *PtrAposta = fopen("Apostas.dat", "ab+");
	FILE *PtrApostadores = fopen("Apostadores.dat", "rb");
	FILE *PtrConcurso = fopen("Concurso.dat", "rb");
	TpApostas RegAposta;
	int auxNum, VerificaApostador, VerificaConcurso, auxAposta, VerificaAposta;
	char auxCpf[15];
	printf("\n##CADASTRAR APOSTAS ##\n");
	printf("NUMERO DA APOSTA que deseja CADASTRAR: \n");
	scanf("%d", &auxAposta);
	if(PtrAposta == NULL)
		printf("Erro de abertura!!\n");
	else
	{
		while (auxAposta > 0)
		{
			rewind(PtrAposta);
			VerificaAposta = BuscarAposta(PtrAposta, auxAposta);
			if(VerificaAposta == -1)
			{
				printf("CPF do APOSTADOR: "); fflush (stdin);
				gets(auxCpf);
				printf("NUMERO do CONCURSO: \n");
				scanf("%d",&auxNum);
				VerificaApostador = BuscarApostador(PtrApostadores, auxCpf);
				VerificaConcurso = BuscarConcurso(PtrConcurso, auxNum);
				if(VerificaApostador != -1 && VerificaConcurso !=-1)
					{
						RegAposta.numAposta = auxAposta;
						strcpy(RegAposta.cpf, auxCpf);
						RegAposta.numConcurso = auxNum;
						
						printf("QUANTAS dezenas deseja apostar (max. 20): ");
						scanf("%d", &RegAposta.qtdeNumApostado);
						if (RegAposta.qtdeNumApostado > 20)
							printf("NAO é possivel apostar. \n");
						else
							{
								printf("QUAIS numeros deseja APOSTAR:");
								//fazer um vetor para as dezenas
								fwrite(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
								printf("APOSTA CADASTRADA com sucesso!\n");
					}	
							}
			
				else if(VerificaApostador == -1)
					printf("APOSTADOR NAO Cadastrado\n");
				else if(VerificaConcurso == -1)
					printf("CONCURSO NAO Cadastrado");
			}
			else
				printf("APOSTA ja CADASTRADA!!");
				
			printf("\n##CADASTRAR APOSTAS ##\n");
			printf("NUMERO DA APOSTA que deseja CADASTRAR: \n");
			scanf("%d", &auxAposta);
		}
	fclose(PtrAposta);
	fclose(PtrConcurso);
	fclose(PtrApostadores);
	}
}
void AlterarApostador ()
{
	FILE *PtrApostador = fopen("Apostadores.dat", "rb+");
	TpApostadores Registro;
	int Verifica;
	char opcao; 
	clrscr();
	printf("\n## Alterar Apostador ##\n");
	if (PtrApostador == NULL)
		printf("Erro Em Abrir Arquivo!\n");
	else
	{
		printf(" Digite o CPF do apostador: \n"); fflush(stdin);
		gets(Registro.cpf);
		Verifica = BuscarApostador(PtrApostador, Registro.cpf);
		if(Verifica == -1)
			printf("Apostador Não Encontrado!!!\n");
		else
		{
				printf("\n*** Detalhes do Apostador ***\n");
				fseek(PtrApostador,Verifica,0);  //fseek(PtrVeic,desl,SEEK_SET);
				fread(&Registro,sizeof(TpApostadores),1,PtrApostador);
				printf("\nCPF: %s\n",Registro.cpf);
				printf("Nome: %s\n",Registro.nome);
				printf("Telefone: %d\n",Registro.numTel);
				printf("Status: %c\n",Registro.status);
				printf("Qual Dado deseja Alterar? (Não é possivel alterar o CPF)\n");
				printf("[A] Nome \t [B]Telefone\n");
				opcao = toupper(getche());
				switch(opcao)
				{
					case 'A':
						{
							printf("\n## Alterar Nome ## \n");
							printf("Digite novo nome: \n"); fflush(stdin);
							gets (Registro.nome);
							break;
						}
					case 'B':{
						printf("\n## Alterar Telefone ##\n");
						printf("Novo numero de telefone: \n"); 
						scanf("%d",&Registro.numTel);
						break;
					}
				
				}
				
				fseek(PtrApostador, -sizeof(TpApostadores), 1); //posiciona o ponteiro onde vai ser alterado, o -sizeof acontece por que o ponteiro sempre anda mais um, e a posição que queremos está antes;
				fwrite(&Registro, sizeof(TpApostadores), 1, PtrApostador); //grava no registro onde esta a posição atual do ponteiro.
				printf("Dados Atualizados!!");
				fclose(PtrApostador);
		}
	}
}
void AlterarConcurso(){
	
	FILE *PtrConcurso = fopen("Concurso.dat", "rb+");
	TpConcurso Registro;
	int Verifica;
	char opcao; 
	clrscr();
	printf("\n## Alterar Concurso ##\n");
	if (PtrConcurso == NULL)
		printf("Erro Em Abrir Arquivo!\n");
	else
	{
		printf(" Digite o numero do concurso: \n"); 
		scanf("%d",&Registro.numConcurso);
		Verifica = BuscarConcurso(PtrConcurso, Registro.numConcurso);
		if(Verifica == -1)
			printf("Concurso Não Encontrado!!!\n");
		else
		{
				printf("\n*** Detalhes do Concurso ***\n");
				fseek(PtrConcurso,Verifica,0);  //fseek(PtrVeic,desl,SEEK_SET);
				fread(&Registro,sizeof(TpConcurso),1,PtrConcurso);
				printf("\nData: %d %d %d\n",Registro.date.dia,Registro.date.mes,Registro.date.ano);
				printf("Numero do concurso: %d\n",Registro.numConcurso);
				printf("Numeros sorteados: %d\n",Registro.numSorteados);
				printf("Status: %c\n",Registro.status);
				printf("Qual Dado deseja Alterar? (Não é possivel alterar o numero do concurso)\n");
				printf("[A] Data \t [B] Numeros sorteados\n");
				opcao = toupper(getche());
				switch(opcao)
				{
					case 'A':
						{
							printf("\n## Alterar Data ## \n");
							printf("Digite nova data: \n");
							scanf("%d %d %d",&Registro.date.dia,&Registro.date.mes,&Registro.date.ano);
							break;
						}
				//	case 'B':{
				//		printf("\n## Alterar  ##\n");
				//		printf("Novo numero e telefone: \n"); fflush(stdin);
				//		scanf("%d",&Registro.numTel);
				//		break;
				//	}
				
				}
				
				fseek(PtrConcurso, -sizeof(TpConcurso), 1); //posiciona o ponteiro onde vai ser alterado, o -sizeof acontece por que o ponteiro sempre anda mais um, e a posição que queremos está antes;
				fwrite(&Registro, sizeof(TpConcurso), 1, PtrConcurso); //grava no registro onde esta a posição atual do ponteiro.
				printf("Dados Atualizados!!");
				fclose(PtrConcurso);
		}
	}
}
void AlterarAposta(){
	
	FILE *PtrAposta = fopen("Apostas.dat", "rb+");
	TpApostas Registro;
	int Verifica;
	char opcao; 
	clrscr();
	printf("\n## Alterar Aposta ##\n");
	if (PtrAposta == NULL)
		printf("Erro Em Abrir Arquivo!\n");
	else
	{
		printf(" Digite o numero da aposta: \n");
		scanf("%d",&Registro.numAposta);
		Verifica = BuscarAposta(PtrAposta, Registro.numAposta);
		if(Verifica == -1)
			printf("Aposta Não Encontrado!!!\n");
		else
		{
				printf("\n*** Detalhes da Aposta ***\n");
				fseek(PtrAposta,Verifica,0);  //fseek(PtrVeic,desl,SEEK_SET);
				fread(&Registro,sizeof(TpApostas),1,PtrAposta);
				printf("\nCPF: %s\n",Registro.cpf);
				printf("Numero de aposta: %d\n",Registro.numAposta);
				printf("Numeros apostados: %d\n",Registro.numApostados);
				printf("Quantidade De numeros apostados: %d",Registro.qtdeNumApostado);
				printf("Status: %c\n",Registro.status);
				printf("Qual Dado deseja Alterar? (Não é possivel alterar o CPF e Numero de aposta)\n");
				printf("[A] Numeros apostados \t [B]Quantidade de numeros apostados \n");
				opcao = toupper(getche());
				switch(opcao)
				{
					case 'A':
						{
							printf("\n## Alterar Numeros apostados ## \n");
							printf("Digite: \n"); 
							scanf("%d",&Registro.numApostados);
							break;
						}
					case 'B':{
						printf("\n## Alterar quantidade de numeros apostados ##\n");
						printf("Digite: \n");
						scanf("%d",&Registro.qtdeNumApostado);
						break;
					}
				
				}
				
				fseek(PtrAposta, -sizeof(TpApostas), 1); //posiciona o ponteiro onde vai ser alterado, o -sizeof acontece por que o ponteiro sempre anda mais um, e a posição que queremos está antes;
				fwrite(&Registro, sizeof(TpApostas), 1, PtrAposta); //grava no registro onde esta a posição atual do ponteiro.
				printf("Dados Atualizados!!");
				fclose(PtrAposta);
		}
	}
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

			case '3':
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

		}

	} while(op != 27);
	return 0;
}
char menuNum(void) {
	clrscr();
	moldeMenuInicial();
	
	gotoxy(14,12);
	printf("[1] Cadastrar");

	gotoxy(38,12);
	printf("[2] Exibir");

	gotoxy(60,12);
	printf("[3] Alterar");

	gotoxy(15,19);
	printf("[4] Excluir");

	gotoxy(36,19);
	printf("[5] Relatorio");


	return getch();
}

char menu(void) {
	printf("# # # # MENU # # # # \n");
	textcolor(1);
	printf("[A] Cadastrar APOSTADORES\n");
	printf("[B] Cadastrar CONCURSO\n");
	printf("[C] Cadastrar APOSTAS\n");
	textcolor(2);
	printf("[E] Exibir APOSTADORES\n");
	printf("[F] Exibir CONCURSO\n");
	printf("[G] Exibir APOSTAS\n");
	textcolor(3);
	printf("[I] Alterar APOSTADORES\n");
	printf("[J] Alterar CONCURSO\n");
	printf("[K] Alterar APOSTAS\n");
	textcolor(5);
	printf("[M] Excluir APOSTADORES\n");
	printf("[N] Excluir CONCURSO\n");
	printf("[O] Excluir APOSTAS\n");
	textcolor(7);
	
	return toupper(getche());
}
