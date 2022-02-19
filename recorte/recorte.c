#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct ppmPixel{
  int r,g,b;
};
typedef struct ppmPixel PPMPIXEL;

struct ppmImage{
  int magicNumber;
  int width,height,maxval;
  PPMPIXEL** mat;
};
typedef struct ppmImage PPM;

//nesta função damos um ficheiro e tiramos tds os comentarios
//e retornamos um novo ficheiro com isso alterado
void read_word(FILE* f,FILE* f1){
  char frase[1000];

  while(fgets(frase,1000,f)!=NULL){
    for(int i=0;i<strlen(frase);i++){
      if(frase[i]=='#'){
        frase[i]='\0';
      } 
    }
  fprintf(f1,"%s",frase);

  }
}

void execute(FILE* f1, FILE* f2,int A,int B,int C, int D){

  if(f1==NULL){
    printf("O ficheiro n existe!");
    exit(1);
  }
  if(f2==NULL){
    printf("O ficheiro n existe!");
    exit(1);
  }
  PPM image;
  //cria ficheiro temporario para colocar a img sem comentarios
  FILE* f=tmpfile();
  read_word(f1,f);
  rewind(f);//mete a posiçao do ficheiro no inicio do ficheiro da stream
  //int row,col;
  fscanf(f,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);

  //alocar array de linhas
  image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *));

  //ISTO AQUI LE A IMAGEM
  for(int i=0;i<image.height;i++){
    //alocar linha i
    image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
    for(int j=0;j<image.width;j++){
      PPMPIXEL p;
      //lemos os pixeis e guardamos
      fscanf(f,"%d %d %d\n",&p.r, &p.g,&p.b);
      image.mat[i][j]=p;
    }
  }
  if(A<0) A=0;
  if(A>= image.width) A= image.width-1;
  if(C<0) C=0;
  if(C>= image.width) C= image.width-1;
  if(B<0) B=0;
  if(B>= image.height) B= image.height-1;
  if(D<0) D=0;
  if(D>= image.height) D= image.height-1;


  //novo alocamento de mem para guardar a nova imagem rodada
  PPM new;
  new.magicNumber=image.magicNumber;
  new.maxval=image.maxval;
  new.height=D-B+1;
  new.width=C-A+1;

  fprintf(f2,"P%d\n%d %d\n%d\n",new.magicNumber,new.width,new.height,new.maxval);

  //agora imprimimos
  for (int j =B; j<=D; j++)
  {
    for (int k = A; k<=C; k++)
      {   
        fprintf (f2,"%d ", image.mat[j][k].r);
        fprintf (f2,"%d ", image.mat[j][k].g);
        fprintf (f2,"%d\n", image.mat[j][k].b);
      }
  }
  fclose(f1);
  fclose(f2);
}


int main(int argc, char* argv[]){
  FILE* f1;
  FILE* f2;
  int A= atoi(argv[1]);
  int B= atoi(argv[2]);
  int C= atoi(argv[3]);
  int D= atoi(argv[4]);
  if(argc==5){
    f1=stdin; 
    f2=stdout;
    execute(f1,f2,A,B,C,D);
  }
  if(argc==6){
    f1=fopen(argv[5],"r");
    f2=stdout;
    execute(f1,f2,A,B,C,D);
  }
  for(int i=6;i<argc;i++){
    f1=fopen(argv[5],"r");
    f2=fopen(argv[6],"w");
    execute(f1,f2,A,B,C,D);
  }
  return 0;
}