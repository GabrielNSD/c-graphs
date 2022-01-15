#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define POS_INF 1000000000
#define NEG_INF -1000000000

class GrafoListaAdj
{
private:
    vector<string> vertices;

    // first é o indice do vertice, second é o peso (caso o grafo seja ponderado)
    vector<vector<pair<int, int>>> arestas;

    /**
     * A principio nao temos nenhuma ordenacao usando os rotulos.
     * Portanto, usaremos busca linear.
     **/
    int obterIndiceVertice(string rotuloVertice)
    {
        int index = -1;
        for (int i = 0; i < vertices.size(); i++)
        {
            if (rotuloVertice == vertices[i])
            {
                index = i;
            }
        }
        return index;
    }

    /**
     * O argumento indicesVerticesVisitados serve para controlar quais
     * vertices já foram visitados.
     * Lembrando que DFS é uma função recursiva.
     **/
    void dfs(string rotuloVOrigem, bool *indicesVerticesVisitados)
    {
        int index = obterIndiceVertice(rotuloVOrigem);
        if (indicesVerticesVisitados[index])
        {
            return;
        }
        else
        {
            indicesVerticesVisitados[index] = true;
            for (int i = 0; i < arestas[index].size(); i++)
            {
                string newOrigin = vertices[arestas[index][i].first];
                dfs(newOrigin, indicesVerticesVisitados);
            }
        }
        // IMPLEMENTAR
    }

public:
    /**
     * Lembrem-se:
     *       1) nao podemos inserir vertices com mesmo rotulo
     *       2) toda vez que inserirmos um novo v�rtice, precisaremos
     *          inserir um vetor para representar as conex�es daquele
     *          v�rtice na lista de adjac�ncias
     **/
    void inserirVertice(string rotuloVertice)
    {
        int index = obterIndiceVertice(rotuloVertice);
        if (index < 0)
        {
            vertices.push_back(rotuloVertice);
            vector<pair<int, int>> tempVector;
            arestas.push_back(tempVector);
        }
    }

    /**
     * Sempre que o grafo for n�o ponderado, adicionaremos o peso 1,
     * por conveni�ncia.
     **/
    void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, peso);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, peso);
    }

    /**
     * Inserir uma aresta entre rotuloVOrigem e rotuloVDestino com o peso
     * especificado.
     **/
    void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso)
    {
        int indiceOrigem = obterIndiceVertice(rotuloVOrigem);
        int indiceDestino = obterIndiceVertice(rotuloVDestino);

        if (indiceOrigem < 0 || indiceDestino < 0)
        {
            return;
        }
        pair<int, int> tempPair; //(indiceDestino, peso);
        tempPair.first = indiceDestino;
        tempPair.second = peso;
        arestas[indiceOrigem].push_back(tempPair);
    }

    /**
     * Verifica se v�rtice rotuloVOrigem e v�rtice rotuloVDestino s�o
     * conectados (vizinhos).
     **/
    bool saoConectados(string rotuloVOrigem, string rotuloVDestino)
    {
        int indiceOrigem = obterIndiceVertice(rotuloVOrigem);
        int indiceDestino = obterIndiceVertice(rotuloVDestino);

        bool resultado = false;

        if (indiceOrigem < 0 || indiceDestino < 0)
        {
            return false;
        }

        for (int j = 0; j < arestas[indiceOrigem].size(); j++)
        {
            if (arestas[indiceOrigem][j].first == indiceDestino)
            {
                resultado = true;
            }
        }

        return resultado;
    }

    /**
     * Verifica se há algum caminho entre vértice rotuloVOrigem e
     * vértice rotuloVDestino.
     * A melhor forma de fazer isto é reusando a função dfs.
     **/
    bool haCaminho(string rotuloVOrigem, string rotuloVDestino)
    {

        int indexOrigem = obterIndiceVertice(rotuloVOrigem);
        int indexDestino = obterIndiceVertice(rotuloVDestino);
        bool *indicesVerticesVisitados = new bool[vertices.size()]{false};
        if (indexOrigem == 0 && indexDestino == 0)
        {
            return false;
        }
        dfs(rotuloVOrigem, indicesVerticesVisitados);
        if (indicesVerticesVisitados[indexOrigem] && indicesVerticesVisitados[indexDestino])
        {
            delete[] indicesVerticesVisitados;
            return true;
        }
        else
        {
            delete[] indicesVerticesVisitados;
            return false;
        }
    }

    /**
     * Muda os rótulos do vértices dos diferentes componentes para
     * nomes que representam cores.
     * Dica: procura componentes partindo do vértice v0 ou v1, em ordem
     * crescente (mas você pode usar outra ordem se desejar).
     * Retorna a quantidade de componentes.
     * A melhor forma de fazer isto é reusando a função dfs.
     **/
    int colorir()
    {
        int size = vertices.size();
        if (size == 0)
        {
            return 0;
        }
        else
        {
            bool *visitados = new bool[size]{0};
            int count = 0;

            for (int i = 0; i < size; i++)
            {
                string origem = vertices[i];
                bool change = false;
                bool *tempVisitados = new bool[size]{0};
                copy(visitados, visitados + size, tempVisitados);

                if (visitados[i] == false)
                {
                    count++;
                    change = true;
                    dfs(origem, visitados);
                }

                if (change)
                {
                    for (int j = i; j < size; j++)
                    {
                        if (visitados[j] != tempVisitados[j])
                        {
                            vertices[j] = origem;
                        }
                    }
                }
            }

            delete[] visitados;
            return count;
        }
    }

    /**
     * Usa a abordagem de navegação BFS para listar as distâncias
     * entre o vértice rotuloVOrigem e cada um dos demais vértices.
     * A função BFS consegue listar a menor distância entre um vértice
     * e os demais se o grafo for NÃO-PONDERADO.
     * Retorna um vetor de inteiros com a quantidade de arestas
     * (distância) e o vértice rotuloVOrigem e cada um dos demais vértices.
     * Não é uma função recursiva.
     * É necessário utilizar a ED fila.
     **/
    int *bfs(string rotuloVOrigem)
    {
        queue<int> filaDeVertices;
        int *distancias = new int[vertices.size()]{0};
        bool *visitados = new bool[vertices.size()]{0};
        int indiceOrigem = obterIndiceVertice(rotuloVOrigem);
        filaDeVertices.push(indiceOrigem);
        visitados[indiceOrigem] = true;
        distancias[indiceOrigem];

        while (!filaDeVertices.empty())
        {
            int s = filaDeVertices.front();
            filaDeVertices.pop();

            for (auto u : arestas[s])
            {
                if (!visitados[u.first])
                {
                    visitados[u.first] = true;
                    int distancia = distancias[s] + u.second;
                    distancias[u.first] = distancias[s] + u.second;
                    filaDeVertices.push(u.first);
                }
            }
        }

        delete[] visitados;
        return distancias;
    }

    /**
     * Usamos o BellmanFord para encontrar menor caminho
     * em grafos com arestas com pesos negativos.
     * O BellmanFord consegue detectar ciclos negativos
     * e atribuir o valor NEG_INF (constante definida nesse arquivo)
     * aos vértices que pertenáam ao ciclo.
     * POS_INF deve ser atribu�do aos vértices inalcançáveis.
     * O aspecto negativo é sua complexidade de tempo: O(V*E).
     * Isto acontece pois, como possui arestas negativas, cada vértice
     * do grafo precisa ser processado V vezes.
     * Pseudo-c�digo: https://github.com/eduardolfalcao/edii/blob/master/conteudos/Grafos.md#bellman-ford
     **/
    int *bellmanFord(string rotuloVOrigem)
    {
        // IMPLEMENTAR
        int numeroVertices = vertices.size();
        int *distancias = new int[numeroVertices];
        fill(distancias, distancias + numeroVertices, POS_INF);

        int indiceVerticeOrigem = obterIndiceVertice(rotuloVOrigem);

        distancias[indiceVerticeOrigem] = 0;

        bool lastRelax = false;
        for (int i = 0; i < numeroVertices - 1; i++)
        {
            bool relax = false;
            for (int j = 0; j < arestas.size(); j++)
            {
                for (auto a : arestas[j])
                {
                    if (distancias[j] + a.second < distancias[a.first])
                    {
                        distancias[a.first] = distancias[j] + a.second;
                        relax = true;
                    }
                }
            }
            if (i == (numeroVertices - 2) && relax) // verifica que houve relaxamento na última iteração
            {
                lastRelax = true;
            }
        }

        if (lastRelax) // garante execução de verificação do ciclo negativo apenas se houver relaxamento até última iteração de menor caminho
        {
            // cout << "RODOU" << endl;
            for (int i = 0; i < numeroVertices - 1; i++)
            {
                for (int j = 0; j < arestas.size(); j++)
                {
                    for (auto a : arestas[j])
                    {
                        if (distancias[j] + a.second < distancias[a.first])
                        {
                            distancias[a.first] = NEG_INF;
                        }
                    }
                }
            }
        }

        return distancias;
    }

    /**
     * Usamos o Dijkstra para encontrar menor caminho
     * em grafos sem arestas com pesos negativos.
     * O Dijkstra retorna respostas incorretas caso o grafo
     * possua arestas negativas, e portanto n�o consegue
     * detectar ciclos negativos. Este � o aspecto negativo.
     * POS_INF deve ser atribu�do aos v�rtices inalcan��veis.
     * O aspecto positivo � sua complexidade de tempo: O(V+E).
     * Isto acontece pois, como o grafo n�o possui arestas negativas,
     * cada v�rtice do grafo precisa ser processado apenas 1 vez.
     * Pseudo-c�digo: https://github.com/eduardolfalcao/edii/blob/master/conteudos/Grafos.md#dijkstra
     * Ilustra��o: https://docs.google.com/drawings/d/1NmkJPHpcg8uVcDZ24FQiYs3uHR5n-rdm1AZwD74WiMY/edit?usp=sharing
     **/
    int *dijkstra(string rotuloVOrigem)
    {
        // IMPLEMENTAR
        int numeroVertices = vertices.size();

        bool *visitados = new bool[numeroVertices]{false};
        int *distancias = new int[numeroVertices];
        fill(distancias, distancias + numeroVertices, POS_INF);

        priority_queue<pair<int, int>> filaPrioridade;

        int indiceOrigem = obterIndiceVertice(rotuloVOrigem);

        distancias[indiceOrigem] = 0;

        filaPrioridade.push({0, indiceOrigem});

        while (!filaPrioridade.empty())
        {
            int indice = filaPrioridade.top().second;
            filaPrioridade.pop();
            if (visitados[indice])
                continue;
            visitados[indice] = true;

            for (auto a : arestas[indice])
            {
                int vertice = a.first;
                int peso = a.second;
                if (distancias[indice] + peso < distancias[vertice])
                {
                    distancias[vertice] = distancias[indice] + peso;
                    filaPrioridade.push({-distancias[vertice], vertice});
                }
            }
        }
        return distancias;
    }

    vector<string> getVertices()
    {
        return vertices;
    }

    vector<vector<pair<int, int>>> getArestas()
    {
        return arestas;
    }
};