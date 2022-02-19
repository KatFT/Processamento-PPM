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

void execute(FILE* f1, FILE* f2,int t){

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

  if(t<0 || t> image.maxval){
    printf("Error: Treeshold must be between 0 and maxval\n");
    exit(1);
  }
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
    int grey=0;
    int a=0;
    //agora imprimimos
    for (int j =0; j<image.height; j++)
    {
      for (int k = 0; k < image.width; ++k)
        {
          grey=round(0.2126*image.mat[j][k].r+0.7152*image.mat[j][k].g+0.0722*image.mat[j][k].b);
          if(grey>t){
            fprintf (f2,"%d ", image.maxval);
            fprintf (f2,"%d ", image.maxval);
            fprintf (f2,"%d\n", image.maxval);
          }
          else{
            fprintf (f2,"%d ", a);
            fprintf (f2,"%d ", a);
            fprintf (f2,"%d\n", a);
          }
        }
    }

    fclose(f1);
    fclose(f2);
}

int main(int argc, char* argv[]){
  FILE* f1;
  FILE* f2;
  int t= atoi(argv[1]);
  if(argc==2){
    f1=stdin; 
    f2=stdout;
    execute(f1,f2,t);
  }
  if(argc==3){
    f1=fopen(argv[2],"r");
    f2=stdout;
    execute(f1,f2,t);
  }
  for(int i=3;i<argc;i++){
    f1=fopen(argv[2],"r");
    f2=fopen(argv[3],"w");
    execute(f1,f2,t);
  } 
    return 0;
}