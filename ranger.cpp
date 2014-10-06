#include <string>
#include <assert.h>
// #include <math.h>

#include "common.h"
#include "ranger.h"

using namespace std;

/* Hunt for the croc! */
void Ranger::StartHunting(void){
	_session->StartGame();
	_session->GetGameDistributions(_waterholeStat.calcium, 
								   _waterholeStat.salinity,
								   _waterholeStat.alkalinity);
	
}

/* Retrieve current game stat */
TrackingData Ranger::GetGameState(void){
	TrackingData td;
	_session->GetGameState(td.score, 
						   td.rangerLocation,
						   td.backpakers.first,
						   td.backpakers.second,
						   td.sensorEmissions.calciumReading,
						   td.sensorEmissions.salineReading,
						   td.sensorEmissions.alkalinityReading);
	return td;
}

/* Move to the neighbor location */
bool Ranger::move(int& from, int& to){
	bool ongoing = _session->makeMove(toWString(from),toWString(to),_totalScore);

	#if ASSERT_MODE > 0
		TrackingData td = GetGameState();
		assert(td.rangerLocation==to);
	#endif

	return ongoing;
}

/* Search for the croc in the current location */
bool Ranger::search(int& currentLocation){
	bool ongoing = _session->makeMove(toWString(currentLocation),L"S",_totalScore);

	return ongoing;
}

/* Probability density function for the normal distribution */
double pdf(double x, double mean, double deviation){
	double factor = M_1_SQRT2PI/deviation;
	double power = (x - mean)/deviation;

	return factor*exp(-0.5f*power*power);
}