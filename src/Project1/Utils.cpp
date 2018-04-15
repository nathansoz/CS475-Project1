#include "Utils.h"

using namespace Project1;

float Utils::Height(int iu, int iv, int numberOfNodes)
{
	float u = (float)iu / (float)(numberOfNodes - 1);
	float v = (float)iv / (float)(numberOfNodes - 1);

	// the basis functions:

	float bu0 = (1.f - u) * (1.f - u) * (1.f - u);
	float bu1 = 3.f * u * (1.f - u) * (1.f - u);
	float bu2 = 3.f * u * u * (1.f - u);
	float bu3 = u * u * u;

	float bv0 = (1.f - v) * (1.f - v) * (1.f - v);
	float bv1 = 3.f * v * (1.f - v) * (1.f - v);
	float bv2 = 3.f * v * v * (1.f - v);
	float bv3 = v * v * v;

	// finally, we get to compute something:


	float top = bu0 * (bv0*TOPZ00 + bv1 * TOPZ01 + bv2 * TOPZ02 + bv3 * TOPZ03)
		+ bu1 * (bv0*TOPZ10 + bv1 * TOPZ11 + bv2 * TOPZ12 + bv3 * TOPZ13)
		+ bu2 * (bv0*TOPZ20 + bv1 * TOPZ21 + bv2 * TOPZ22 + bv3 * TOPZ23)
		+ bu3 * (bv0*TOPZ30 + bv1 * TOPZ31 + bv2 * TOPZ32 + bv3 * TOPZ33);

	float bot = bu0 * (bv0*BOTZ00 + bv1 * BOTZ01 + bv2 * BOTZ02 + bv3 * BOTZ03)
		+ bu1 * (bv0*BOTZ10 + bv1 * BOTZ11 + bv2 * BOTZ12 + bv3 * BOTZ13)
		+ bu2 * (bv0*BOTZ20 + bv1 * BOTZ21 + bv2 * BOTZ22 + bv3 * BOTZ23)
		+ bu3 * (bv0*BOTZ30 + bv1 * BOTZ31 + bv2 * BOTZ32 + bv3 * BOTZ33);

	return top - bot;	// if the bottom surface sticks out above the top surface
						// then that contribution to the overall volume is negative
}

float Utils::FullTileArea(int numberOfNodes)
{
	return (((XMAX - XMIN) / (float)(numberOfNodes - 1)) * ((YMAX - YMIN) / (float)(numberOfNodes - 1)));
}

float Utils::GetTileWeight(int iu, int iv, int numberOfNodes)
{
	// The common case, not a corner or an edge
	if (iu != 0 && iv != 0 && iu != numberOfNodes - 1 && iv != numberOfNodes - 1)
	{
		return 1.0f;
	}

	// If we got here, it is a corner or edge
	if ((iu == 0 && iv == 0) || // bottom left
		(iu == numberOfNodes - 1 && iv == numberOfNodes - 1) || // top right
		(iu == 0 && iv == numberOfNodes - 1) || // top left
		(iu == numberOfNodes - 1 && iv == 0)) // bottom right
	{
		return 0.25f;
	}
	else
	{
		return 0.5f;
	}
}

int Utils::EnableDynamicThreading()
{
	if (omp_get_dynamic() != 0)
	{
		std::cout << "Dynamic thread allocation is enabled" << std::endl;
	}
	else
	{
		std::cout << "omp_get_dynamic() returned 0, dynamic threading is not enabled..." << std::endl;
		std::cout << "Attempting to enable dynamic threading..." << std::endl;
		omp_set_dynamic(1);

		if (omp_get_dynamic() == 0)
		{
			std::cerr << "Dynamic thread allocation could not be enabled!" << std::endl;
			return 1;
		}
		else
		{
			std::cout << "omp_get_dynamic() returned non 0 value" << std::endl;
		}
	}

	int threadVal = omp_get_max_threads();
	std::cout << "omp_get_num_threads() returned: " << threadVal << std::endl;

	int threadTest = 6;
	if (threadTest == threadVal)
	{
		threadTest--;
	}

	std::cout << "Setting number of threads to: " << threadTest << std::endl;
	omp_set_num_threads(threadTest);

	int newThreadVal = omp_get_max_threads();
	std::cout << "omp_get_num_threads() returned: " << newThreadVal << std::endl;

	if (threadTest != newThreadVal)
	{
		std::cerr << "Failed to adjust thread count!" << std::endl;
		return 1;
	}

	std::cout << "Setting number of threads to: " << threadVal << std::endl;
	omp_set_num_threads(threadVal);

	newThreadVal = omp_get_max_threads();
	std::cout << "omp_get_max_threads() returned: " << newThreadVal << std::endl;

	if (threadVal != newThreadVal)
	{
		std::cerr << "Failed to adjust thread count!" << std::endl;
		return 1;
	}

	return 0;
}

std::string Utils::GetProgramDirectory()
{
#ifdef _WIN32
	char* pgmptr;
	_get_pgmptr(&pgmptr);
	std::string path(pgmptr);
	return path.substr(0, path.find_last_of("/\\"));
#else

#endif
}