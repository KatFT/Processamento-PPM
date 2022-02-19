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

void execute(FILE* f1, FILE* f2,int dR,int dG,int dB){

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
    int nR=0;
    int nG=0;
    int nB=0;

    //agora imprimimos
    for (int j =0; j<image.height; j++)
    {
      for (int k = 0; k < image.width; ++k)
        {
          nR=image.mat[j][k].r+dR;
          if(nR<0) nR=0;
          else if(nR>image.maxval) nR=image.maxval;
          nG=image.mat[j][k].g+dG;
          if(nG<0) nG=0;
          else if(nG>image.maxval) nG=image.maxval;
          nB=image.mat[j][k].b+dB;
          if(nB<0) nB=0;
          else if(nB>image.maxval) nB=image.maxval;
          fprintf (f2,"%d ", nR);
          fprintf (f2,"%d ", nG);
          fprintf (f2,"%d\n", nB);
        }
    }
    fclose(f1);
    fclose(f2);
}

int main(int argc, char* argv[]){
  FILE* f1;
  FILE* f2;
  int dR= atoi(argv[1]);
  int dG= atoi(argv[2]);
  int dB= atoi(argv[3]);
  if(argc==4){
    f1=stdin; 
    f2=stdout;
    execute(f1,f2,dR,dG,dB);
  }
  if(argc==5){
    f1=fopen(argv[4],"r");
    f2=stdout;
    execute(f1,f2,dR,dG,dB);
  }
  for(int i=5;i<argc;i++){
    f1=fopen(argv[4],"r");
    f2=fopen(argv[5],"w");
    execute(f1,f2,dR,dG,dB);
  } 
  return 0;
}