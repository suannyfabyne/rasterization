# rasterization

### Implementando um algoritmo de rasterização
##### DUPLA: SUANNY FABYNE E JUAN ALBUQUERQUE






### Uma breve introdução
 
  A atividade é baseada na realização de um algoritmo de rasterização de pontos e linhas, sendo necessário triângulos desenhados através de construção de arestas (linhas rasterizadas). As cores atribuidas a cada vértice formam um efeito suave ao longo da linha que conecta os mesmos através da técnica de interpolação, obtendo-se um efeito degradê caso os vértices (ou pontos extremos) tenham cores distintas. A rasterização é feita através da escrita direta na memória, utilizando um framework para simular o acesso à memória de vídeo.
  
Em resumo, há a implementação de 3 funções principais:

*PutPixel: Rasteriza um ponto na memória de vídeo.
*DrawLine: Função que rasteriza uma linha na tela com interpolação linear das cores dos vértices.
*DrawTriangle: Desenha as arestas de um triângulo na tela
