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


char* read_word(FILE* f){
  char* frase;
  frase= (char*)malloc(sizeof(char));
  char ch;
  while(fgets(frase,1000,f)!=NULL){
    for(int i=0;i<strlen(frase);i++){
      //ch= frase[i];
      if(frase[i]=='#'){
        frase[i]='\0';
      } 
      if(frase[0]=='\n') frase[0]=' ';
      frase[strlen(frase)-1]='\n';

    }
  printf("%s",frase);

  }
  return frase;
}


/*char* read_word(FILE* f){
  char* frase;
  frase= (char*)malloc(sizeof(char));
  fgets(frase,1000,f);
  for(int i=0;i<strlen(frase);i++){
    
    if(frase[i]=='#'){
      frase[i]='\0';
      if(frase[i]=='\n')
        frase[i]=' ';
    }
    //if(frase[0]=='\n') frase[0]=' ';
    
        
    frase[strlen(frase)-1]='\n';
  }

  printf("%s",frase);
  return frase;
}
*/

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
  char* word;
  // read magicNumber
  if ((word = read_word(f1)) == NULL || sscanf(word, "P%d\n", &image.magicNumber) !=1 ){
    printf("adeus1\n");
    exit(-1);
  }
  else
    fprintf(f2,"P%d\n",image.magicNumber);

  /*word=read_word(f1);
  printf("aaa%s\n",word );
  if(sscanf(word, "%d %d", &image.width,&image.height) ==1) printf("cxona");
*/
  // read width and height
  if ((word = read_word(f1)) == NULL || (image.width= strtoul(word,&word,10))==0 ||(image.height= strtoul(word,&word,10))==0 ){
    //printf("%s",word);
    printf("adeus2\n");
    exit(-1);
  } else fprintf(f2,"%d %d\n",image.width,image.height);
 

  // read maxval
  if ((word = read_word(f1)) == NULL || sscanf(word, "%d\n", &image.maxval) !=1 ){
    printf("adeus4\n");
    exit(-1);
  }else fprintf(f2,"%d\n",image.maxval);

  //int row,col;
  //fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
  //fprintf(f2,"P%d\n%d %d\n%d\n",image.magicNumber,image.width,image.height,image.maxval);

  

  //alocar array de linhas
  image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *));



  //ISTO AQUI LE A IMAGEM
  for(int i=0;i<image.height;i++){
    //alocar linha i
    image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
    for(int j=0;j<image.width;j++){
      PPMPIXEL p;
      //lemos os pixeis e guardamos
   
          if (((word=read_word(f1))==NULL)||(p.r=strtoul(word,&word,10)<0)||(p.g=strtoul(word,&word,10)<0)||(p.b=strtoul(word,&word,10)<0)){
            printf("adeus5\n");

            exit(-1);
          }
        image.mat[i][j]=p;

      

        //fscanf(f1,"%d %d %d\n",&p.r, &p.g,&p.b);
    }
  }

  //agora vamos trocar os indices
  int mid = image.width / 2;
  PPMPIXEL a;

    for (int j = 0; j < image.height; ++j){
      for (int k = 0; k < mid; ++k){
          a = image.mat[j][k];
          image.mat[j][k] = image.mat[j][image.width - k - 1];
          image.mat[j][image.width - k - 1] = a;
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
    free(image.mat);
}
//AINDA NAO ESTA FEITA ESTA PARTE
void execute2(FILE* f1){

  PPM image;
  char* word;
   
  if(f1==NULL){
    printf("O ficheiro n existe!");
    exit(1);
  }
  // read magicNumber
  if ((word = read_word(f1)) == NULL || sscanf(word, "P%d", &image.magicNumber) !=1 ){
    printf("adeus\n");
    exit(-1);
  }
  else
    printf("P%d\n",image.magicNumber);

  // read width
  if ((word = read_word(f1)) == NULL || sscanf(word, "%d", &image.width) !=1 ){
    printf("adeus\n");
    exit(-1);
  }
  else printf("%d ",image.width);
  // read heigth
  if ((word = read_word(f1)) == NULL || sscanf(word, "%d", &image.height) !=1 ){
    printf("adeus\n");
    exit(-1);
  }
  else printf("%d\n",image.height);
  // read maxval
  if ((word = read_word(f1)) == NULL || sscanf(word, "%d", &image.maxval) !=1 ){
    printf("adeus\n");
    exit(-1);
  }else printf("%d\n",image.maxval);
  //fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
  //printf("P%d\n%d %d\n%d\n",image.magicNumber,image.width,image.height,image.maxval);

  //alocar array de linhas
  image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *));

  //ISTO AQUI LE A IMAGEM
  for(int i=0;i<image.height;i++){
    //alocar linha i
    image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
    for(int j=0;j<image.width;j++){
      PPMPIXEL p;
      //lemos os pixeis e guardamos
      if ((word = read_word(f1)) == NULL || sscanf(word, "%d", &p.r) !=1 ){
        printf("adeus\n");
        exit(-1);
      }
  
      if ((word = read_word(f1)) == NULL || sscanf(word, "%d", &p.g) !=1 ){
        printf("adeus\n");
        exit(-1);
      }
      if ((word = read_word(f1)) == NULL || sscanf(word, "%d", &p.b) !=1 ){
        printf("adeus\n");
        exit(-1);
      }
      //fscanf(f1,"%d %d %d\n",&p.r, &p.g,&p.b);
      image.mat[i][j]=p;
    }
  }

  //agora vamos trocar os indices
  int mid = image.width / 2;
  PPMPIXEL a;

    for (int j = 0; j < image.height; ++j){
      for (int k = 0; k < mid; ++k){
          a = image.mat[j][k];
          image.mat[j][k] = image.mat[j][image.width - k - 1];
          image.mat[j][image.width - k - 1] = a;
        }
    }

    //agora imprimimos
    for (int j =0; j<image.height; j++)
    {
      for (int k = 0; k < image.width; ++k)
        {
          printf ("%d ", image.mat[j][k].r);
          printf ("%d ", image.mat[j][k].g);
          printf ("%d\n", image.mat[j][k].b);
        }
    }
    fclose(f1);
    free(image.mat);
}


int main(int argc, char* argv[]){
  FILE* f1;
  FILE* f2;
  if(argc==1){
    f1=stdin; 
    execute2(f1);
  }
  if(argc==2){
    f1=fopen(argv[1],"r");
    execute2(f1);
  }
  for(int i=2;i<argc;i++){
    f1=fopen(argv[1],"r");
    f2=fopen(argv[2],"w");
    if(f1==NULL){
          printf(" <file>: No such file or directory");
          getchar();
          exit(1);
            }
    execute(f1,f2);
  }
  

  
    return 0;


}