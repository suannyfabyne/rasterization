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
<img src="file:///home/suannyfabyne/Imagens/Captura%20de%20tela%20de%202019-02-13%2017-51-25.png">

Já o código abaixo mostra a função pronta, onde recebe um objeto da classe Pixel como paramêtro. Nela, contém as coordenadas x e y e os valores R, G, B e A, onde FBptr é um ponteiro que aponta para o primeiro byte do color buffer simulado, onde seu índice representa a posição na tela, e o conteúdo a componente RGBA.
 ```c
void PutPixel(Pixel paramPixel)
{
    FBptr[4*paramPixel.getX() + 4*paramPixel.getY()*IMAGE_WIDTH + 0] = paramPixel.getR(); 
    FBptr[4*paramPixel.getX() + 4*paramPixel.getY()*IMAGE_WIDTH + 1] = paramPixel.getG(); 
    FBptr[4*paramPixel.getX() + 4*paramPixel.getY()*IMAGE_WIDTH + 2] = paramPixel.getB(); 
    FBptr[4*paramPixel.getX() + 4*paramPixel.getY()*IMAGE_WIDTH + 3] = paramPixel.getA(); 
}
 ```

