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
  //int row,col;
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

  //agora vamos trocar os indices
  int mid = image.height / 2;
  PPMPIXEL a;

    for (int j = 0; j < mid; ++j){
      for (int k = 0; k < image.width; ++k){
          a = image.mat[j][k];
          image.mat[j][k] = image.mat[image.height-1-j][k];
          image.mat[image.height-1-j][k] = a;
        }
    }

    //agora imprimimos
    for (int j =0; j<image.height; j++)
    {
      for (int k = 0; k < image.width; ++k)
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