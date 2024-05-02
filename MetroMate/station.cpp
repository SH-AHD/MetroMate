#include"station.h"

void Station::findTrips(system_clock::time_point tripTime) {
    for (auto& trainPair : stationSchedule) {
        if (trainPair.second.getTrainSchedule().getArrivalTime() == tripTime) {
            cout << trainPair.second.getTrainID();
        }
    }
}
