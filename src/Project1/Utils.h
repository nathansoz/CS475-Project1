#define XMIN	 0.f
#define XMAX	 3.f
#define YMIN	 0.f
#define YMAX	 3.f

#define TOPZ00  0.f
#define TOPZ10  1.f
#define TOPZ20  0.f
#define TOPZ30  0.f

#define TOPZ01  1.f
#define TOPZ11  6.f
#define TOPZ21  1.f
#define TOPZ31  0.f

#define TOPZ02  0.f
#define TOPZ12  1.f
#define TOPZ22  0.f
#define TOPZ32  4.f

#define TOPZ03  3.f
#define TOPZ13  2.f
#define TOPZ23  3.f
#define TOPZ33  3.f

#define BOTZ00  0.f
#define BOTZ10  -3.f
#define BOTZ20  0.f
#define BOTZ30  0.f

#define BOTZ01  -2.f
#define BOTZ11  10.f
#define BOTZ21  -2.f
#define BOTZ31  0.f

#define BOTZ02  0.f
#define BOTZ12  -5.f
#define BOTZ22  0.f
#define BOTZ32  -6.f

#define BOTZ03  -3.f
#define BOTZ13   2.f
#define BOTZ23  -8.f
#define BOTZ33  -3.f

#include <omp.h>
#include <iostream>
#include <string>

namespace Project1 
{
	class Utils 
	{
	public:
		static float Height(int iu, int iv, int numberOfNodes);
		static float FullTileArea(int numberOfNodes);
		static float GetTileWeight(int iu, int iv, int numberOfNodes);
		static int EnableDynamicThreading();
		static std::string GetProgramDirectory();
	};
}