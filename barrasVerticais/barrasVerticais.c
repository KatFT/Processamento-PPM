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

void execute(FILE* f1, FILE* f2,int npx,int R, int G,int B){

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

  PPMPIXEL a;
  a.r=R;
  a.g=G;
  a.b=B;

  for(int k=npx;k<image.width ;k+=2*npx){
      for(int j=0;j<image.height;j++){
          for(int i=0;i<npx && (k+i)<image.width;i++)
            image.mat[j][k+i]=a;
      }
  }

    fprintf(f2,"P%d\n%d %d\n%d\n",image.magicNumber,image.width,image.height,image.maxval);

    //agora imprimimos
    for (int j =0; j<image.height; j++)
    {
      for (int k = 0; k<image.width; k++)
        { 
          //if(j%npx==0){
            
              fprintf (f2,"%d ", image.mat[j][k].r);
              fprintf (f2,"%d ", image.mat[j][k].g);
              fprintf (f2,"%d\n", image.mat[j][k].b);
            

         /* }
          else{
              fprintf(f2,"%d %d %d\n",a.r,a.g,a.b);
          }*/
        }
    }
    fclose(f1);
    fclose(f2);
}


int main(int argc, char* argv[]){
  FILE* f1;
  FILE* f2;
  int npx= atoi(argv[1]);
  int R= atoi(argv[2]);
  int G= atoi(argv[3]);
  int B= atoi(argv[4]);
  if(argc==5){
    f1=stdin; 
    f2=stdout;
    execute(f1,f2,npx,R,G,B);
  }
  if(argc==6){
    f1=fopen(argv[5],"r");
    f2=stdout;
    execute(f1,f2,npx,R,G,B);
  }
  for(int i=6;i<argc;i++){
    f1=fopen(argv[5],"r");
    f2=fopen(argv[6],"w");
    execute(f1,f2,npx,R,G,B);
  }
    return 0;
}