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

void execute(FILE* f1, FILE* f2, FILE* f4,int X,int Y, float alfa){

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
  PPMPIXEL a;
  //começa na coordenada q queremos e percorremos ate ao final
  for(int i=Y;i<image1.height && (i-Y)<image.height;i++){
    for(int j=X;j<image1.width && (j-X)<image.width;j++){
      //image1.mat[i][j]=image.mat[i-Y][j-X];

      a.r=(1-alfa)*image1.mat[i][j].r+alfa*image.mat[i-Y][j-X].r;
      a.g=(1-alfa)*image1.mat[i][j].g+alfa*image.mat[i-Y][j-X].g;
      a.b=(1-alfa)*image1.mat[i][j].b+alfa*image.mat[i-Y][j-X].b;
      image1.mat[i][j].r=a.r;
      image1.mat[i][j].g=a.g;
      image1.mat[i][j].b=a.b;
    }
  }


  fprintf(f4,"P%d\n%d %d\n%d\n",image1.magicNumber,image1.width,image1.height,image1.maxval);
  //agora imprimimos
  for (int j =0; j<image1.height; j++)
  {
    for (int k = 0; k<image1.width; k++)
      {
        fprintf (f4,"%d ", image1.mat[j][k].r);
        fprintf (f4,"%d ", image1.mat[j][k].g);
        fprintf (f4,"%d\n", image1.mat[j][k].b);
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
  float alfa= atof(argv[1]);
  int X= atoi(argv[2]);
  int Y= atoi(argv[3]);
  if(argc==5){
    f1=fopen(argv[4],"r");
    f2=stdin;
    f3=stdout;
    execute(f1,f2,f3,X,Y,alfa);
  }
  if(argc==6){
    f1=fopen(argv[4],"r");
    f2=fopen(argv[5],"r");
    f3=stdout;
    execute(f1,f2,f3,X,Y,alfa);
  }
  for(int i=6;i<argc;i++){
    f1=fopen(argv[4],"r");
    f2=fopen(argv[5],"r");
    f3=fopen(argv[6],"w");
    execute(f1,f2,f3,X,Y,alfa);
  }
  return 0;
}