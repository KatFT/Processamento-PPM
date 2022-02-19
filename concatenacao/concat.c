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

int min(int a, int b){
  return (a > b ) ? b : a;
}

void execute(FILE* f1, FILE* f2, FILE* f4){

  if(f1==NULL){
    printf("O ficheiro n existe!");
    exit(1);
  }
  if(f2==NULL){
    printf("O ficheiro n existe!");
    exit(1);
  }
  if(f4==NULL){
    printf("O ficheiro n existe!");
    exit(1);
  }
  PPM image;
  PPM image1;
  //1º ficheiro
  //cria ficheiro temporario para colocar a img sem comentarios
  FILE* f=tmpfile();
  read_word(f1,f);
  rewind(f);//mete a posiçao do ficheiro no inicio do ficheiro da stream
  //2ºficheiro
  FILE* f3=tmpfile();
  read_word(f2,f3);
  rewind(f3);

  //int row,col;
  fscanf(f,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
  fscanf(f3,"P%d\n%d %d\n%d\n",&image1.magicNumber,&image1.width,&image1.height,&image1.maxval);

  
  //1ºficheiro
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

  //2ºficheiro
  //alocar array de linhas
  image1.mat= (PPMPIXEL **) malloc(image1.height * sizeof(PPMPIXEL *));

  //ISTO AQUI LE A IMAGEM
  for(int i=0;i<image1.height;i++){
    //alocar linha i
    image1.mat[i]= (PPMPIXEL *) malloc(image1.width*sizeof(PPMPIXEL));
    for(int j=0;j<image1.width;j++){
      PPMPIXEL p;
      //lemos os pixeis e guardamos
      fscanf(f3,"%d %d %d\n",&p.r, &p.g,&p.b);
      image1.mat[i][j]=p;
    }
  }
  //novo alocamento de mem para guardar a nova imagem rodada
  PPM new;
  new.magicNumber=image.magicNumber;
  new.maxval=image.maxval;
  new.height=min(image.height,image1.height);
  new.width=image.width+image1.width;
  new.mat=(PPMPIXEL **) malloc(new.height*sizeof(PPMPIXEL*));

    for (int j = 0; j < new.height; ++j){
      new.mat[j]=(PPMPIXEL *) malloc(new.width * sizeof(PPMPIXEL ));
     
    }

    //vamos por a 1º imagem 
    for(int j=0;j<new.height;j++){
      for(int k=0;k<image.width;k++){
        new.mat[j][k]=image.mat[j][k];
      }
    }
    //vamos por a 2º imagem 
    for(int j=0;j<new.height;j++){
      for(int k=image.width;k<new.width;k++){
        new.mat[j][k]=image1.mat[j][k-image.width];
      }
    }

    fprintf(f4,"P%d\n%d %d\n%d\n",new.magicNumber,new.width,new.height,new.maxval);
    //agora imprimimos
    for (int j =0; j<new.height; j++)
    {
      for (int k = 0; k<new.width; k++)
        {
          fprintf (f4,"%d ", new.mat[j][k].r);
          fprintf (f4,"%d ", new.mat[j][k].g);
          fprintf (f4,"%d\n", new.mat[j][k].b);
        }
    }
    fclose(f1);
    fclose(f2);
    fclose(f4);
}

int main(int argc, char* argv[]){
  FILE* f1;
  FILE* f2;
  FILE* f3;
  if(argc==3){
    f1=fopen(argv[1],"r");
    f2=fopen(argv[2],"r");
    f3=stdout;
    execute(f1,f2,f3);
  }
  for(int i=3;i<argc;i++){
    f1=fopen(argv[1],"r");
    f2=fopen(argv[2],"r");
    f3=fopen(argv[3],"w");
    execute(f1,f2,f3);
  }
  return 0;
}