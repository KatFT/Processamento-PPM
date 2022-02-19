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

int matrix(PPM image1, PPM image, int i, int j){
  for(int k=0;k<image.height&& (k+i)<image.height;k++){
    for(int l=0;l<image.width && (l+j)<image.width;l++){
      if((image1.mat[k+i][l+j].r!=image.mat[k][l].r)&&(image1.mat[k+i][l+j].g!=image.mat[k][l].g)&&
      (image1.mat[k+i][l+j].b!=image.mat[k][l].b))
        return 0;          
    }
  }
  return 1;
}


void execute(FILE* f1, FILE* f2, int delta){

  if(f1==NULL){
    printf("O ficheiro n existe!");
    exit(1);
  }
  if(f2==NULL){
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

  fscanf(f,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
  fscanf(f3,"P%d\n%d %d\n%d\n",&image1.magicNumber,&image1.width,&image1.height,&image1.maxval);

  
  //1ºficheiro/imagem
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

  //2ºficheiro/imagem
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

  //começa na coordenada q queremos e percorremos ate ao final
  for(int i=0;i<image1.height;i++){
    for(int j=0;j<image1.width ;j++){
      
      if((image.mat[0][0].r-delta<=image1.mat[i][j].r && image1.mat[i][j].r <=image.mat[0][0].r+delta)&&
      (image.mat[0][0].g-delta<=image1.mat[i][j].g && image1.mat[i][j].g <=image.mat[0][0].g+delta)&&
      (image.mat[0][0].b-delta<=image1.mat[i][j].b && image1.mat[i][j].b <=image.mat[0][0].b+delta)){
        if((image1.mat[i][j].r==image.mat[0][0].r) &&(image1.mat[i][j].g==image.mat[0][0].g)&&
        (image1.mat[i][j].g==image.mat[0][0].g)){
          if(matrix(image1,image, i,j)!=0)
            printf("(%d,%d) ",i,j);
        }
         
      }
    }
  }
  printf("\n");
  fclose(f1);
  fclose(f2);

}


int main(int argc, char* argv[]){
  FILE* f1;
  FILE* f2;
  
  int delta= atoi(argv[1]);
  if(argc==3){
    f1=fopen(argv[2],"r");
    f2=stdin;
    execute(f1,f2,delta);
  }
  if(argc==4){
    f1=fopen(argv[2],"r");
    f2=fopen(argv[3],"r");
    execute(f1,f2,delta);
  }
  
  return 0;
}