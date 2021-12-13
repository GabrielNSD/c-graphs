//#include "pch.h"
//#include "../src/grafos/grafomatadj.h"

#include <gtest/gtest.h>

#include "../src/grafomatadjexercicio.h"

class GrafoMatrizAdjTest : public ::testing::Test
{
protected:
	void freeGrafo(struct GrafoMatrizAdj *grafo)
	{
		for (int i = 0; i < grafo->maxNumVertices; i++)
		{
			free(grafo->arestas[i]);
		}
		free(grafo->arestas);
		free(grafo->rotuloVertices);
		free(grafo);
		std::cout << "terminou o free" << std::endl;
	}

	virtual void TearDown()
	{
		// std::cout << "iniciou o teardown" << std::endl;
		freeGrafo(grafoNaoPonderado);
		freeGrafo(grafoPonderado);
		std::cout << "termiou o teardown" << std::endl;
	}

	virtual void SetUp()
	{
		std::cout << "iniCIOU SETUP " << std::endl;
		grafoNaoPonderado = inicializar(9, false);
		// std::cout << "setou Npond" << std::endl;
		grafoPonderado = inicializar(9, true);
		std::cout << "setou pond" << std::endl;
	}

	struct GrafoMatrizAdj *grafoNaoPonderado;
	struct GrafoMatrizAdj *grafoPonderado;
};

TEST_F(GrafoMatrizAdjTest, InsercaoVerticeGrafo)
{
	EXPECT_EQ(grafoNaoPonderado->verticesInseridos, 0);
	inserirVertice(grafoNaoPonderado, "v1");
	EXPECT_EQ(grafoNaoPonderado->verticesInseridos, 1);
	inserirVertice(grafoNaoPonderado, "v2");
	EXPECT_EQ(grafoNaoPonderado->verticesInseridos, 2);
	inserirVertice(grafoNaoPonderado, "v3");
	EXPECT_EQ(grafoNaoPonderado->verticesInseridos, 3);
}

void inserirVertices(struct GrafoMatrizAdj *grafo)
{
	inserirVertice(grafo, "v1");
	inserirVertice(grafo, "v2");
	inserirVertice(grafo, "v3");
	inserirVertice(grafo, "v4");
	inserirVertice(grafo, "v5");
	inserirVertice(grafo, "v6");
	inserirVertice(grafo, "v7");
	inserirVertice(grafo, "v8");
	inserirVertice(grafo, "v9");
}

TEST_F(GrafoMatrizAdjTest, ObterVerticeExistente)
{
	inserirVertices(grafoNaoPonderado);
	std::cout << "inseriu " << std::endl;
	EXPECT_EQ(grafoNaoPonderado->verticesInseridos, 9);
	std::cout << "testou 1 " << std::endl;
	EXPECT_EQ(obterIndiceVertice(grafoNaoPonderado, "v1"), 0);
	std::cout << "terminou 1 aqui " << std::endl;
	EXPECT_EQ(obterIndiceVertice(grafoNaoPonderado, "v5"), 4);
	std::cout << "terminou 2 aqui " << std::endl;
	EXPECT_EQ(obterIndiceVertice(grafoNaoPonderado, "v9"), 8);
	std::cout << "terminou aqui " << std::endl;
	// std::cout << "terminou aqui 2" << std::endl;
}

TEST_F(GrafoMatrizAdjTest, ObterVerticeInexistente)
{
	std::cout << "iniCIOU OVI " << std::endl;
	inserirVertices(grafoNaoPonderado);
	std::cout << "inseriu " << std::endl;
	EXPECT_EQ(obterIndiceVertice(grafoNaoPonderado, "v0"), -1);
	std::cout << "terminou 1 aqui " << std::endl;
	EXPECT_EQ(obterIndiceVertice(grafoNaoPonderado, "v10"), -1);
	std::cout << "terminou 2 aqui " << std::endl;
	std::cout << "terminou aqui " << std::endl;
}

void inserirArestaNaoDirecionada(struct GrafoMatrizAdj *grafo, char *vOrigem, char *vDestino, int peso)
{
	// std::cout << "iniCIOU OVI " << std::endl;
	//  std::cout << "iniciou aqui " << std::endl;
	inserirAresta(grafo, vOrigem, vDestino, peso);
	inserirAresta(grafo, vDestino, vOrigem, peso);
}

TEST_F(GrafoMatrizAdjTest, InserirArestasSemPeso)
{
	std::cout << "iniciou aqui IASP" << std::endl;
	inserirVertices(grafoNaoPonderado);
	inserirArestaNaoDirecionada(grafoNaoPonderado, "v1", "v2", 1);
	inserirArestaNaoDirecionada(grafoNaoPonderado, "v1", "v3", 1);
	inserirArestaNaoDirecionada(grafoNaoPonderado, "v2", "v4", 1);
	inserirArestaNaoDirecionada(grafoNaoPonderado, "v3", "v4", 1);
	inserirArestaNaoDirecionada(grafoNaoPonderado, "v3", "v5", 1);
	inserirArestaNaoDirecionada(grafoNaoPonderado, "v4", "v6", 1);
	inserirArestaNaoDirecionada(grafoNaoPonderado, "v4", "v7", 1);
	inserirArestaNaoDirecionada(grafoNaoPonderado, "v5", "v9", 1);
	inserirArestaNaoDirecionada(grafoNaoPonderado, "v6", "v8", 1);
	inserirArestaNaoDirecionada(grafoNaoPonderado, "v8", "v9", 1);
	std::cout << "t1 " << std::endl;
	EXPECT_TRUE(saoConectados(grafoNaoPonderado, "v1", "v2"));
	std::cout << "t2 " << std::endl;
	EXPECT_TRUE(saoConectados(grafoNaoPonderado, "v2", "v1"));
	std::cout << "t3 " << std::endl;
	EXPECT_TRUE(saoConectados(grafoNaoPonderado, "v8", "v9"));
	std::cout << "t4 " << std::endl;
	EXPECT_TRUE(saoConectados(grafoNaoPonderado, "v9", "v8"));
	std::cout << "t5 " << std::endl;
	EXPECT_FALSE(saoConectados(grafoNaoPonderado, "v0", "v9"));
	std::cout << "fechou " << std::endl;
}

TEST_F(GrafoMatrizAdjTest, InserirArestasComPeso)
{
	std::cout << "iniCIOU IACP " << std::endl;
	inserirVertices(grafoPonderado);
	inserirArestaNaoDirecionada(grafoPonderado, "v1", "v2", 6);
	inserirArestaNaoDirecionada(grafoPonderado, "v1", "v3", 4);
	inserirArestaNaoDirecionada(grafoPonderado, "v2", "v4", 5);
	inserirArestaNaoDirecionada(grafoPonderado, "v3", "v4", 2);
	inserirArestaNaoDirecionada(grafoPonderado, "v3", "v5", 4);
	inserirArestaNaoDirecionada(grafoPonderado, "v4", "v6", 5);
	inserirArestaNaoDirecionada(grafoPonderado, "v4", "v7", 5);
	inserirArestaNaoDirecionada(grafoPonderado, "v5", "v9", 9);
	inserirArestaNaoDirecionada(grafoPonderado, "v6", "v8", 6);
	inserirArestaNaoDirecionada(grafoPonderado, "v8", "v9", 8);
	EXPECT_TRUE(saoConectados(grafoPonderado, "v1", "v2"));
	EXPECT_TRUE(saoConectados(grafoPonderado, "v2", "v1"));
	EXPECT_TRUE(saoConectados(grafoPonderado, "v8", "v9"));
	EXPECT_TRUE(saoConectados(grafoPonderado, "v9", "v8"));
	EXPECT_FALSE(saoConectados(grafoPonderado, "v0", "v9"));
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}