#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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

void execute(FILE* f1, FILE* f2){

  if(f1==NULL){
    printf("O ficheiro n existe!");
    exit(1);
  }
  if(f2==NULL){
    printf("O ficheiro n existe!");
    exit(1);
  }
  PPM image;
  FILE* f=tmpfile();
  read_word(f1,f);
  rewind(f);
  fscanf(f,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
  fprintf(f2,"P%d\n%d %d\n%d\n",image.magicNumber,image.width,image.height,image.maxval);

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
    int R=0;
    int G=0;
    int B=0;
    for (int i =0; i<image.height; i++){
      for (int j = 0; j < image.width; ++j){
        R+=image.mat[i][j].r;
        G+=image.mat[i][j].g;
        B+=image.mat[i][j].b;
      }
    }
    int mediaR=0;
    int mediaG=0;
    int mediaB=0;
    mediaR=R/(image.width*image.height);
    mediaG=G/(image.width*image.height);
    mediaB=B/(image.width*image.height);

    //agora imprimimos
    for (int i =0; i<image.height; i++)
    {
      for (int j = 0; j < image.width; ++j)
        {
          if(mediaR>mediaB && mediaR>mediaG)
            fprintf (f2,"%d 0 0\n", image.mat[i][j].r);
          if(mediaB>mediaR && mediaB>mediaG)
            fprintf (f2,"0 0 %d\n", image.mat[i][j].b);
          if(mediaG>mediaB && mediaG>mediaR)
            fprintf (f2,"0 %d 0\n", image.mat[i][j].g);
        }
    }
    fclose(f1);
    fclose(f2);
}

int main(int argc, char* argv[]){
  FILE* f1;
  FILE* f2;
  if(argc==1){
    f1=stdin; 
    f2=stdout;
    execute(f1,f2);
  }
  if(argc==2){
    f1=fopen(argv[1],"r");
    f2=stdout;
    execute(f1,f2);
  }
  for(int i=2;i<argc;i++){
    f1=fopen(argv[1],"r");
    f2=fopen(argv[2],"w");
    execute(f1,f2);
  } 
    return 0;
}