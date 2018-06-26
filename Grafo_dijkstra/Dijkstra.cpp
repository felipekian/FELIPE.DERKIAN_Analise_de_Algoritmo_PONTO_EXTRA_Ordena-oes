#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <list>
#include <queue>

#define INFINITO 10000000 //dar a impressao de infinito

using namespace std;

class Grafo{
private:
	int V; // n�mero de v�rtices

	// ponteiro para um array contendo as listas de adjac�ncias
	list<pair<int, int> > * adj;

public:
	// construtor
	Grafo(int V)
	{
		this->V = V; // atribui o n�mero de v�rtices
		adj = new list<pair<int, int> >[V];
	}

	// adiciona uma aresta ao grafo de v1 � v2
	void addAresta(int v1, int v2, int custo)
	{
		adj[v1].push_back(make_pair(v2, custo));
	}

	// algoritmo de Dijkstra
	int dijkstra(int orig, int dest)
	{
		// vetor de dist�ncias
        int dist[V];
		int visitados[V];

		// fila de prioridades de pair (distancia, v�rtice)
		priority_queue < pair<int, int>,
					   vector<pair<int, int> >, greater<pair<int, int> > > pq;

		// inicia o vetor de dist�ncias e visitados
		for(int i = 0; i < V; i++)
		{
			dist[i] = INFINITO;
			visitados[i] = false;
		}

		// a dist�ncia de orig para orig � 0
		dist[orig] = 0;

		// insere na fila
		pq.push(make_pair(dist[orig], orig));

		// loop do algoritmo
		while(!pq.empty())
		{
			pair<int, int> p = pq.top(); // extrai o pair do topo
			int u = p.second; // obt�m o v�rtice do pair
			pq.pop(); // remove da fila

			// verifica se o v�rtice n�o foi expandido
			if(visitados[u] == false)
			{
				// marca como visitado
				visitados[u] = true;

				list<pair<int, int> >::iterator it;

				// percorre os v�rtices "v" adjacentes de "u"
				for(it = adj[u].begin(); it != adj[u].end(); it++)
				{
					// obt�m o v�rtice adjacente e o custo da aresta
					int v = it->first;
					int custo_aresta = it->second;

					// relaxamento (u, v)
					if(dist[v] > (dist[u] + custo_aresta))
					{
						// atualiza a dist�ncia de "v" e insere na fila
						dist[v] = dist[u] + custo_aresta;
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}
		// retorna a dist�ncia m�nima at� o destino
		return dist[dest];
	}
};

int main(){
    int tam = 5;

	Grafo g(tam); //cria o grafo com o tamanho de tam

    //abre o arquivo texto.txt com as informa��es do grafo
    FILE * fp =fopen("texto.txt","r");

    //variaveis auxiliares
    int vertice , aresta , peso;

    //ler o arquivo ate o final
    while(!feof(fp))
    {
        fscanf(fp,"%d %d %d\n",&vertice,&aresta,&peso);
        //adiciona as informa��es do texto.txt no grafo
        g.addAresta(vertice,aresta,peso);
    }
    //fecha o arquivo
    fclose(fp);

    //variaveis para pedir do usuario o vertice inicio e destino para colocar no dijkstra
    int origem,destino;
    while(1)
    {

            system("cls");
            printf("**Algoritmo de Dijkstra**\n\n");
            printf("Informe a origem: ");
            scanf("%d",&origem);
            printf("Informe o destino: ");
            scanf("%d",&destino);

            //se os valores informados nao existirem imprime a mensagem
            if(origem>tam || destino>tam)
            {
                system("cls");
                printf("vertice nao existe!\n");

            }else //senao manda rodar o algoritmo
                cout << "\n\nO custo do caminho " << origem << " para o destino " << destino << " = " << g.dijkstra(origem, destino) << "\n" << endl;

            system("pause");
    }

	return 0;
}
