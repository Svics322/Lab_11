#include "pch.h"
#include "CppUnitTest.h"
#include "..\PDS_11\Graph.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestGetPath)
		{
			Graph graph(6);
			graph.addEdge(1, 2, 1);
			graph.addEdge(1, 3, 6);
			graph.addEdge(1, 4, 2);
			graph.addEdge(2, 3, 4);
			graph.addEdge(2, 5, 2);
			graph.addEdge(3, 6, 3);
			graph.addEdge(4, 5, 5);
			graph.addEdge(5, 6, 4);
			graph.floydWarshall();

			PathInfo pathInfo = graph.getPath(0, 5);
			Assert::AreEqual(7u, pathInfo.distance);
			Assert::AreEqual(4u, (unsigned int)pathInfo.path.size());
			Assert::AreEqual(1, pathInfo.path[0]);
			Assert::AreEqual(2, pathInfo.path[1]);
			Assert::AreEqual(5, pathInfo.path[2]);
			Assert::AreEqual(6, pathInfo.path[3]);
		}

		TEST_METHOD(TestNoPath)
		{
			Graph graph(2);
			graph.floydWarshall();

			PathInfo pathInfo = graph.getPath(0, 1);
			Assert::AreEqual(UINT_MAX, pathInfo.distance);
			Assert::AreEqual(0u, (unsigned int)pathInfo.path.size());
		}

		TEST_METHOD(TestPathToSelf)
		{
			Graph graph(3);
			graph.addEdge(1, 2, 1);
			graph.addEdge(2, 3, 2);
			graph.floydWarshall();

			PathInfo pathInfo = graph.getPath(0, 0);
			Assert::AreEqual(0u, pathInfo.distance);
			Assert::AreEqual(1u, (unsigned int)pathInfo.path.size());
			Assert::AreEqual(1, pathInfo.path[0]);
		}
	};
}
