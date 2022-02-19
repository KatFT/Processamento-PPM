# Processamento-PPM

Pretende-se que implemente um conjunto de operações de processamento de imagem em formato de
armazenamento ASCII/Plain Portable Pixel Map (PPM).
A descrição do formato ASCII/Plain PPM está disponível em http://netpbm.sourceforge.net/doc/ppm.html,
e em https://en.wikipedia.org/wiki/Netpbm.
Por exemplo, o conteúdo do ficheiro img.ppm, correspondente à seguinte imagem:

<p align="center">
  <img src="./img.png" width="200" height="150" />
</p>




é:

```
P3
3 2
255
# The part above is the header
# "P3" means this is a RGB color image in ASCII
# "3 2" is the width and height of the image in pixels
# "255" is the maximum value for each color
# The part below is image data: RGB triplets
255 0 0 # red
0 255 0 # green
0 0 255 # blue
255 255 0 # yellow
255 255 255 # white
0 0 0 # black
```
A especial atenção que se teve no programa e que foi várias vezes salientada pelo professor é que o ficheiro .pp tinha de ser primeiramente tratado de forma a que não houvesse presença de comentários.
Por exemplo a imagem .ppm acima depois do tratamento ficaria da seuinte forma:

```
P3
3 2
255
255 0 0 
0 255 0 
0 0 255 
255 255 0 
255 255 255 
0 0 0 
 ```

As operações/programas pedidos ao longo do semestre foram os seguintes:
* Rotação Horizontal
* Rotação Vertical
* Rotação Diagonal
* Ajuste de componentes de cor RGB
* Conversão para escala de cinzentos
* Conversão para duas cores (Preto e Branco)
* Rotação 90º Direita
* Rotação 90º Esquerda
* adicionar moldura
* Justaposição de imagens
* Recortar imagem
* Sobreposição de imagens
* Sobreposição de imagens com efeito transparência
* Pesquisa em imagens

 
