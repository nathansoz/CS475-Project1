// Project1.cpp : Defines the entry point for the application.
//

#include "Config.h"
#include "Project1.h"
#include "Utils.h"
#include <experimental/filesystem>
#include <vector>

using namespace std;

void doWork(int);

int main()
{
#ifndef _OPENMP
	std::cerr << "OpenMP is not supported here -- sorry." << std::endl;
	return 1;
#endif

	std::vector<int> threads;
	std::vector<int> nodes;

	auto programDirectory = std::experimental::filesystem::path(Project1::Utils::GetProgramDirectory());
	std::string configFileName = "runtimeconfig.json";
	auto configFileFullPath = programDirectory.append(configFileName);

	if (std::experimental::filesystem::exists(configFileFullPath))
	{
		auto config = Project1::Config::FromFile(configFileFullPath.string());
		threads = config.Threads;
		nodes = config.Nodes;
	}
	else
	{
		std::cout << "Configuration file " << configFileFullPath << " does not exist!" << std::endl;
		std::cout << "Using default values..." << std::endl;
		threads.push_back(NUMTHREADS);
		nodes.push_back(NUMNODES);
	}
	
	//if (Project1::Utils::EnableDynamicThreading() != 0)
	//{
	//	std::cerr << "Dynamic threading is not supported here -- sorry." << std::endl;
	//	return 1;
	//}

	for (const int& threadCount : threads)
	{
		omp_set_num_threads(threadCount);

		for (const int& nodeCount : nodes)
		{
			doWork(nodeCount);
		}
	}
}

void doWork(int nodes)
{
	std::cout << "Using " << omp_get_max_threads() << " threads." << std::endl;
	std::cout << "Calculating for " << nodes << " nodes." << std::endl;

	float fullTileArea = Project1::Utils::FullTileArea(nodes);

	double sumMegaVolumes = 0.;
	double maxMegaVolumes = 0.;
	double solution = 0.;

	for (int loop = 0; loop < NUMTRIES; loop++)
	{
		double volume = 0.0;

		double beforeTime = omp_get_wtime();

		#pragma omp parallel for reduction(+:volume)
		for (int i = 0; i < nodes*nodes; i++)
		{
			int iu = i % nodes;
			int iv = i / nodes;

			float height = Project1::Utils::Height(iu, iv, nodes);
			float weight = Project1::Utils::GetTileWeight(iu, iv, nodes);

			volume += height * weight * fullTileArea;
		}

		double afterTime = omp_get_wtime();
		double megaVolumes = (double)nodes*nodes / (afterTime - beforeTime) / 1000000.;

		sumMegaVolumes += megaVolumes;
		if (megaVolumes > maxMegaVolumes)
		{
			maxMegaVolumes = megaVolumes;
		}

		solution = volume;
	}

	double averageMegaVolumes = sumMegaVolumes / (double)NUMTRIES;
	std::cout << "   Peak Performance = " << maxMegaVolumes << " MegaVolumes/Sec" << std::endl;
	std::cout << "Average Performance = " << averageMegaVolumes << " MegaVolumes/Sec" << std::endl;
	std::cout << std::setprecision(10) << "           Solution = " << solution << std::endl;
}
