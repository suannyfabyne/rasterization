# rasterization

### Implementando um algoritmo de rasterização
##### DUPLA: SUANNY FABYNE E JUAN ALBUQUERQUE

<br><br>



### Uma breve introdução
 
  <p>A atividade é baseada na realização de um algoritmo de rasterização de pontos e linhas, sendo necessário triângulos desenhados através de construção de arestas (linhas rasterizadas). As cores atribuidas a cada vértice formam um efeito suave ao longo da linha que conecta os mesmos através da técnica de interpolação, obtendo-se um efeito degradê caso os vértices (ou pontos extremos) tenham cores distintas. A rasterização é feita através da escrita direta na memória, utilizando um framework para simular o acesso à memória de vídeo.</p>
  
Em resumo, há a implementação de 3 funções principais:

<ol>
  <li><b>PutPixel</b>: Rasteriza um ponto na memória de vídeo.</li>
  <li><b>DrawLine</b>: Função que rasteriza uma linha na tela com interpolação linear das cores dos vértices.</li>
  <li><b>DrawTriangle</b>: Desenha as arestas de um triângulo na tela</li>
</ol>

<br>

### PutPixel()

Essa função gera um ponto no espaço cuja sua localidade é determinada pela coordenada (x,y), como também necessita de valores RGBA para determinar a cor e a opacidade deste ponto. Deve-se salientar que o ponto (0,0) fica localizado no canto superior esquerdo da tela. Podemos ver na imagem abaixo um ponto rasterizado na origem com os componentes RGBA(255,0,0,255):
<br><br>

``` 
In: Pixel paramPixel(0,0,255,0,0,255);
    PutPixel(paramPixel);
Out:   
```
![alt text](https://github.com/suannyfabyne/rasterization/blob/master/prints/putpixel.png)


Já o código abaixo mostra a função pronta, onde recebe um objeto da classe Pixel como paramêtro. Nela, contém as coordenadas x e y e os valores R, G, B e A, onde FBptr é um ponteiro que aponta para o primeiro byte do color buffer simulado, onde seu índice representa a posição na tela, e o conteúdo a componente RGBA.


 
 
```c
void PutPixel(Pixel paramPixel) {
    FBptr[4*paramPixel.getX() + 4*paramPixel.getY()*IMAGE_WIDTH + 0] = paramPixel.getR(); 
    FBptr[4*paramPixel.getX() + 4*paramPixel.getY()*IMAGE_WIDTH + 1] = paramPixel.getG(); 
    FBptr[4*paramPixel.getX() + 4*paramPixel.getY()*IMAGE_WIDTH + 2] = paramPixel.getB(); 
    FBptr[4*paramPixel.getX() + 4*paramPixel.getY()*IMAGE_WIDTH + 3] = paramPixel.getA(); 
}
```

### DrawLine()

A função drawline consiste em rasterizar uma linha atravez de modificação direta da memória de pixel por pixel, onde se tem dois pontos extremos e o Algoritmo de Bresenham diz qual é o pixel certo a ser modificado pare que uma linha mais uniforme possivel seja construída. A tela não possui infinitos pixels para que se desenhe uma linha perfeita, então o Algoritmo de Bresenham toma a decisão para que o desenho construido seja o mais proximo possivel do esperado. A imagem abaixo mostra um exemplo de decisão do algoritmo, onde é decidido pelo pixel mais próximo a linha. 
<br><br>
![alt text](https://3.bp.blogspot.com/-mvcFsWyhnmc/V6pFAr3QdzI/AAAAAAAAAI0/aWCEe16ugu4xkyTJ76QuamhiYUeFDLkzwCLcB/s1600/aula2.png)
<br><br>

Nos foi disponibilizado em aula o algoritmo onde apenas aplica-se ao primeiro octante de um plano, e a maior dificuldade foi poder adaptá-lo a todos os octantes ou condições possíveis. Para isso, precisamos atender a algumas condições:
</br><br>
![alt text](https://3.bp.blogspot.com/-Pclf4WPES_Y/V6dTCQR1OGI/AAAAAAAAACM/U_Bwy1Ov0FUGcIDSY4eqi7S-piw-5F_5wCLcB/s640/octantesreal.gif)
<br><br>

Essas condições variam em relação a um delta Y e um delta X. Esses deltas determinam a inclinação da reta e são obtidos através da diferença entre pontos finais e pontos inicias da reta, determinando em qual octante a mesma está localizada. Essas condições são utilizadas como restrições para determinar varíações feitas no código, a partir do inicial disponibilizado em aula. Um exemplo da função DrawLine, onde delimita o octante 2, é exemplificada abaixo:

```c
else if(abs(dy)>abs(dx) && dx!=0 && dy!=0){ //LIMITA O 2
		if(dy > 0 && dx > 0){
			Treatment(x, y, x0, y0, dx, dy, d, incr_e, incr_ne);
			paramPixel.setX(x);
			paramPixel.setY(y);
			PutPixel(paramPixel);
			while (y < y1) {
				if (d <= 0) {
					d += incr_e;
					y++;
				} else {
					d += incr_ne;
					x++;
					y++;
				}
				paramPixel.setX(x);
				paramPixel.setY(y);
				Interpolacao(Vertice_1, Vertice_2, paramPixel, x, y);
				PutPixel(paramPixel);
			}
		} 
```

Usamos um outro objeto (paramPixel), que representa o ponto atual a ser rasterizado, e também uma funcão de Tratamento, para otimizarmos a mudança de alguns parâmetros necessários da função de rasterização do octante em questão. Variáveis como incr_e, incr_ne,d, etc, são variáveis que caracterizam o Algoritmo de Breseham e determinam o ponto a ser rasterizado.

A imagem abaixo gerada a partir de vértices encontrados no primeiro octante:
<br><br>
![alt text](https://github.com/suannyfabyne/rasterization/blob/master/prints/linha1.png)
<br><br>

Já a próxima, mostra pontos em diferentes octantes:
<br><br>
![alt text](https://github.com/suannyfabyne/rasterization/blob/master/prints/octantes.png)
<br><br>

Assim feita as retas, inicia-se a implementação da Interpolação de Cores, funcionando como um degradê. Nela, a cor de um vértice inicia-se de uma cor, e vai sendo alterada, suavemente, para a cor do próximo vértice. A função implementada calcula a diferença entre a cor do primeiro vértice com a do segundo vértice para cada componente RGBA, e é calculado, para cada delta, uma variação de cor a ser adicionada nas cores do pixel, de acordo com o seu andamento na reta. Essa variação é calculada pela divisão entre a diferença das cores e a distância entre os vértices. Dessa maneira, a cor do pixel atual a ser colorido é modificada e forma a suavização da reta.

<br><br>
![alt text](https://github.com/suannyfabyne/rasterization/blob/master/prints/ultima.png)
<br><br>

### DrawTriangle()


