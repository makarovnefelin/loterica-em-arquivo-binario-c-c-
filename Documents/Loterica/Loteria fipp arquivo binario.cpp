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



//AlteraÃ§Ã£o
void AlterarApostador(void);
void AlterarConcurso(void);
void AlterarAposta(void);

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
	printf("* * * PIZZARIA * * *");
			
}

void moldeMenuTipoExclusao(void){
	moldura(10, 5, 75, 23, 7, 4); //borda externa //64
	moldura(11, 6, 74, 8, 7, 12); //titulo

	moldura(19,13,37,17,7,5); //ITEM 1 
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
	moldura(49,17,67,21,7,5); //ITEM 4  

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
	printf("* * * PIZZARIA * * *");
			
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
	TpApostadores RegApostador;
	FILE * PtrApostador = fopen("Apostadores.dat", "ab+");
	char auxcpf [15];
	int Verifica, l = 25, c=10; 
	
	moldeMenuCadastro();
	limparquadro();
	
	gotoxy(l,c);
	printf(" ## CADASTRAR APOSTADOR ##");
	c++;
	gotoxy(l,c);
	printf("CPF do APOSTADOR que deseja cadastrar"); fflush(stdin);
	c++;
	gotoxy(l,c);
	gets(auxcpf);
	c++;
		if(PtrApostador == NULL)
		{
			gotoxy(l,c);
			printf("Erro de Abertura");
			c++;
		}
		else
			{
					gotoxy(57, 22); printf("                  ");
					while (strcmp(auxcpf,"\0")!=0)
					{
						limparquadro();
						Verifica = BuscarApostador(PtrApostador, auxcpf);	
						if(Verifica == -1)
						{
							strcpy(RegApostador.cpf, auxcpf);
							gotoxy(l,c);
							printf("Nome do APOSTADOR: ");
							c++;
							gets(RegApostador.nome);
							gotoxy(l,c);
							printf("Numero do telefone: ");
							c++;
							gotoxy(l,c);
							scanf("%d", &RegApostador.numTel);
							c++;
							RegApostador.status = 'A';
							fwrite(&RegApostador, sizeof(TpApostadores), 1, PtrApostador);
							gotoxy(l,c);
							printf("APOSTADOR cadastrado com sucesso");
							c++;
						}
						else{
								gotoxy(l,c);
								printf("Apostador ja CADASTRADO");
								c++;
						}
							gotoxy(l,c);
							printf(" ##Cadastrar APOSTADOR ##");
							c++;
							gotoxy(l,c);
							printf("CPF do APOSTADOR que deseja cadastrar"); fflush(stdin);
							gotoxy(l,c);
							gotoxy(l,c);
							gets(auxcpf);
							c++;
				 	}
				fclose(PtrApostador);
			}
			
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
	gotoxy(l,c);
	scanf("%d", &auxNum);
	c++;
	if(PtrConcurso == NULL)
	{
		gotoxy(l,c);
		printf("Erro de Abertura!!");
		c++;
	}
		
	else
	{
		gotoxy(57, 22); printf("                  ");
		while(auxNum > 0)
			{
				Verifica = BuscarConcurso(PtrConcurso, auxNum);
				if(Verifica == -1)//Nao existe entao cadastra
				{
					RegConcurso.numConcurso = auxNum;
					gotoxy(l,c);
					printf("DATA do CONCURSO (D, M, A): ");
					c++;
					gotoxy(l,c);
					scanf("%d %d %d", &RegConcurso.date.dia, &RegConcurso.date.mes, &RegConcurso.date.ano);
					c++;
					//fazer uma busca para sortear os numeros
					RegConcurso.status = 'A';
					
					fwrite(&RegConcurso, sizeof(TpConcurso), 1, PtrConcurso);
					gotoxy(l,c);
					printf("CONCURSO CADASTRADO com sucesso");
					c++;
				}
				else{
					gotoxy(l,c);
					printf("CONCURSO JA CADASTRADO!!!");	
					c++;
				}
				gotoxy(l,c);
				printf("\n## CADASTRO de CONCURSOS## ");
				c++;
				gotoxy(l,c);
				printf("NUMERO do CONCURSO: ");
				c++;
				gotoxy(l,c);
				scanf("%d", &auxNum);
				c++;
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
	scanf("%d", &auxAposta);
	c++;
	if(PtrAposta == NULL){
		gotoxy(l,c);
		printf("Erro de abertura!!");
		c++;
	}
		
	else
	{
		while (auxAposta > 0)
		{
			rewind(PtrAposta);
			VerificaAposta = BuscarAposta(PtrAposta, auxAposta);
			if(VerificaAposta == -1)
			{
				gotoxy(l,c);
				printf("CPF do APOSTADOR: "); fflush (stdin);
				c++;
				gotoxy(l,c);	
				gets(auxCpf);
				c++;
				gotoxy(l,c);	
				printf("NUMERO do CONCURSO: ");
				c++;
				gotoxy(l,c);	
				scanf("%d",&auxNum);
				c++;
				VerificaApostador = BuscarApostador(PtrApostadores, auxCpf);
				VerificaConcurso = BuscarConcurso(PtrConcurso, auxNum);
				if(VerificaApostador != -1 && VerificaConcurso !=-1)
					{
						RegAposta.numAposta = auxAposta;
						strcpy(RegAposta.cpf, auxCpf);
						RegAposta.numConcurso = auxNum;
						
						gotoxy(l,c);
						printf("QUANTAS dezenas deseja apostar (max. 20): ");
						c++;
						gotoxy(l,c);	
						scanf("%d", &RegAposta.qtdeNumApostado);
						c++;
						if (RegAposta.qtdeNumApostado > 20)
						{
							gotoxy(l,c);	
							printf("NAO é possivel apostar mais de 20 dezenas. ");
							c++;
						}
							
						else
							{
								gotoxy(l,c);
								printf("QUAIS numeros deseja APOSTAR:");
								c++;
								//fazer um vetor para as dezenas
								fwrite(&RegAposta, sizeof(TpApostas), 1, PtrAposta);
								gotoxy(l,c);
								printf("APOSTA CADASTRADA com sucesso!");
								c++;
					}	
							}
			
				else if(VerificaApostador == -1)
				{
					gotoxy(l,c);	
					printf("APOSTADOR NAO Cadastrado");
					c++;
				}
					
				else if(VerificaConcurso == -1){
						gotoxy(l,c);
						printf("CONCURSO NAO Cadastrado");
						c++;
				}
				
			}
			else{
				gotoxy(l,c);	
				printf("APOSTA ja CADASTRADA!!");
				c++;
			}
				
			gotoxy(l,c);		
			printf("##CADASTRAR APOSTAS ##");
			c++;
			gotoxy(l,c);	
			printf("NUMERO DA APOSTA que deseja CADASTRAR: ");
			c++;
			gotoxy(l,c);	
			scanf("%d", &auxAposta);
			c++;
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
	int Verifica, l=25, c=10;
	char opcao; 
	
	moldeMenuAlterar();
	limparquadro();
	
	gotoxy(l,c);	
	printf("## ALTERAR APOSTADOR ##");
	c++;
	if (PtrApostador == NULL){
		gotoxy(l,c);	
		printf("Erro Em Abrir Arquivo!");
		c++;
	}
	
	else
	{
		gotoxy(l,c);
		printf("Digite o CPF do apostador: "); fflush(stdin);
		c++;
		gotoxy(l,c);	
		gets(Registro.cpf);
		c++;
		Verifica = BuscarApostador(PtrApostador, Registro.cpf);
		if(Verifica == -1){
			gotoxy(l,c);
			printf("Apostador Não Encontrado!!!");
			c++;
			getch();
		}
			
		else
		{
				gotoxy(l,c);
				printf("*** Detalhes do Apostador ***");
				c++;
				fseek(PtrApostador,Verifica,0);  //fseek(PtrVeic,desl,SEEK_SET);
				fread(&Registro,sizeof(TpApostadores),1,PtrApostador);
				gotoxy(l,c);	
				printf("CPF: %s",Registro.cpf);
				c++;
				gotoxy(l,c);	
				printf("Nome: %s",Registro.nome);
				c++;
				gotoxy(l,c);	
				printf("Telefone: %d",Registro.numTel);
				c++;
				gotoxy(l,c);	
				printf("Status: %c",Registro.status);
				c++;
				gotoxy(l,c);	
				printf("Qual Dado deseja Alterar?");
				c++;
				gotoxy(l,c);		
				printf("[A] Nome \t [B]Telefone");
				c++;
				opcao = toupper(getche());
				limparquadro();
				l = 25, c=10;
				switch(opcao)
				{
					case 'A':
						{
							gotoxy(l,c);	
							printf("## Alterar Nome ## ");
							c++;
							gotoxy(l,c);	
							printf("Digite novo nome: "); fflush(stdin);
							c++;
							gotoxy(l,c);	
							gets (Registro.nome);
							c++;
							break;
						}
					case 'B':{
						gotoxy(l,c);	
						printf("## Alterar Telefone ##");
						c++;
						gotoxy(l,c);	
						printf("Novo numero de telefone: "); 
						c++;
						gotoxy(l,c);	
						scanf("%d",&Registro.numTel);
						c++;
						break;
					}
				
				}
				
				fseek(PtrApostador, -sizeof(TpApostadores), 1); //posiciona o ponteiro onde vai ser alterado, o -sizeof acontece por que o ponteiro sempre anda mais um, e a posição que queremos está antes;
				fwrite(&Registro, sizeof(TpApostadores), 1, PtrApostador); //grava no registro onde esta a posição atual do ponteiro.
				gotoxy(l,c);	
				printf("Dados Atualizados!!");
				getch();
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

char menu(void) {
	printf("# # # # MENU # # # # \n");
	textcolor(1);
	printf("[A] Cadastrar APOSTADORES\n");
	printf("[B] Cadastrar CONCURSOS\n");
	printf("[C] Cadastrar APOSTAS\n");
	textcolor(2);
	printf("[E] Exibir CLIENTES\n");
	printf("[F] Exibir MOTOQUEIROS\n");
	printf("[G] Exibir PIZZAS\n");
	printf("[H] Exibir PEDIDOS\n");
	textcolor(3);
	printf("[I] Alterar APOSTADORES\n");
	printf("[J] Alterar CONCURSOS\n");
	printf("[K] Alterar APOSTAS\n");
	textcolor(5);
	printf("[M] Excluir CLIENTES\n");
	printf("[N] Excluir MOTOQUEIROS\n");
	printf("[O] Excluir PIZZAS\n");
	printf("[P] Excluir PEDIDOS\n");
	textcolor(7);
	
	return toupper(getche());
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
	printf("[1] APOSTADORES");

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
	printf("[1] APOSTADORES");

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
	printf("[1] APOSTADORES");

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
	printf("[2] CONCURSOS");

	gotoxy(23,19);
	printf("[3] APOSTAS");
	
	gotoxy(53,19);
	gotoxy(76,23);

	return getch();
}

char menuRel(void) {
	clrscr();
	moldeMenuRelatorio();

	gotoxy(17,11); printf("Exibir");
	gotoxy(13,12); printf("[1] Estado");
	gotoxy(17,13); printf("Pizza");

	gotoxy(40,11); printf("Filtrar");
	gotoxy(35,12); printf("[2]  Cliente");
	gotoxy(39,13); printf("por inicial");

	gotoxy(62,11); printf("Relatorio");
	gotoxy(58,12); printf("[3]    de");
	gotoxy(62,13); printf("Clientes");
	
	gotoxy(26,18); printf("Motoqueiro");
	gotoxy(22,19); printf("[4] com maior");
	gotoxy(26,20); printf("entrega");

	gotoxy(55,18); printf("Rank");
	gotoxy(49,19); printf("[5]    de");
	gotoxy(54,20); printf("Pizzas");

	gotoxy(76,23);

	return getch();
}

char menuEst(void) {
	clrscr();
	moldeMenuEstatisticas();

	gotoxy(16,11); printf("Relatorio");
	gotoxy(13,12); printf("[1]  Pizza");
	gotoxy(16,13); printf("mais pedida");

	gotoxy(38,11); printf("Relatorio");
	gotoxy(35,12); printf("[2]  Pizza");
	gotoxy(38,13); printf("menos pedida");

	gotoxy(60,11); printf("Cliente que");
	gotoxy(58,12); printf("[3] mais pede");
	gotoxy(64,13); printf("Pizza");
	
	gotoxy(16,18); printf("Motoqueiro");
	gotoxy(13,19); printf("[4]  menos");
	gotoxy(16,20); printf("experiente");

	gotoxy(36,18); printf("Motoqueiro com");
	gotoxy(35,19); printf("[5]mais entregas");
	gotoxy(40,20); printf("no dia");

	gotoxy(59,18); printf("Maior consumo");
	gotoxy(58,19); printf("[6] de pizza");
	gotoxy(60,20); printf("determinada");

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
		}

	} while(op != 27);
}

