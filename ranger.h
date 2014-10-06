#ifndef RANGER_H
#define RANGER_H

#define M_1_SQRT2PI 0.39894228040143267794

typedef std::vector<std::vector<int>> GameGraph;
typedef std::vector<std::pair<double,double>> MeanDev; // <mean,deviation>
typedef std::pair<int,int> Backpackers; // locations of two backpackers 

/* 
   Means and standard deviations of calcium, salinity and alkalinity 
   distributions for each waterhole. These are different each game. 
*/
struct WaterholeStat {
	MeanDev calcium;
	MeanDev salinity;
	MeanDev alkalinity;
};

/* Levels of emissions from the sensors */
struct SensorEmissions {
	double calciumReading;
	double salineReading;
	double alkalinityReading;
};

/* Current game state */
struct TrackingData {
	SensorEmissions sensorEmissions; // observable emissions
	Backpackers backpakers; // locations of two backpackers 
	int rangerLocation; // ranger's location
	int score; // current ranger's score
};

class Ranger{
	CrocSession *_session; // pointer to external game session object
	const GameGraph _gameGraph; // graph of the game nodes
	WaterholeStat _waterholeStat; // means and standard deviations
	int _totalScore;
public:
	Ranger(CrocSession* session):_session(session),_gameGraph(_session->getPaths()){}

	void StartHunting(void);
	TrackingData GetGameState(void);

	~Ranger(void){ delete _session; }
private:
	bool move(int& from, int& to);
	bool search(int& currentLocation);
	double pdf(double x, double mean, double deviation);
};

#endif