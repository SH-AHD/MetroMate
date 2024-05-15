#pragma once
#include <iostream>
#include <deque>
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <random>
#include <string>
#include <algorithm>
//#include "UserAccount.h"
#include "MetroMate.h"

using namespace std;
using namespace std::chrono;

class Train;
class Schedule;
//class Line;


class Schedule {
private:
    string date;
    string departureStation;
    string destinationStation;
    system_clock::time_point departureTime;
    system_clock::time_point arrivalTime;
    int delay = 0;
    bool broken;

public:
  
    //station *station;
    Schedule();
    Schedule(string date, string departureStation, string destinationStation, string departureTime, string arrivalTime);
    string getDate();
    int getDelay();
    string getDepartureStation();
    string getDestinationStation();
    system_clock::time_point getDepartureTime();
    system_clock::time_point getArrivalTime();
    //int getTripNum();
    void setBroken(bool broken);
    bool getBroken();
    void setDate(string date);
    void setDelay(int delay);
    void setDepartureStation(string departureStation);
    void setDestinationStation(string destinationStation);
    void setDepartureTime(system_clock::time_point departureTime);
    void setArrivalTime(system_clock::time_point arrivalTime);


    void setTripScheduleInfo();
    void displaySchedule();
    //bool operator==(const Schedule& other) const :
    //The function takes a constant reference to another Schedule object (other) as its parameter.
    //The const qualifier at the end of the function indicates that 
    // the function does not modify the state of the current object(this).

    bool operator==(const Schedule& other) const {
        // Compare relevant properties of the schedules
        return (date == other.date &&
            delay == other.delay &&
            departureStation == other.departureStation &&
            departureTime == other.departureTime &&
            destinationStation == other.destinationStation &&
            arrivalTime == other.arrivalTime &&
            broken == other.broken);
    }
    ;

};

class Train {
private:
    int ID = 0;
    int lineID = 0;
    bool isBrokenDown = false;
    string status = "Running";
    int currentTripIndex = 0;
  
public:
    vector<Schedule> trainSchedule;
    Train();
    Train(int id, int lid);
    
    int getTrainID();
    string getStatus();
    int getLineID();
    vector<Schedule> getTrainSchedule();
    int getCurrentTripIndex();
    Schedule getTripInfo(Schedule s);
    int getETAForTrip(string stationName, string date, string time);

    void setTrainID(int trainID);
    void setStatus(string status);
    void setLineID(int lineID);
    void setTrainSchedule(Schedule tschedule);
    void setTrainInfo();
    void setCurrentTripIndex(int index);


    //minutes calculateETA(string departureTime, string arrivalTime);
    int calculateETA(string departureTime, string arrivalTime);
    void adjustNextTripDepartureTime();


    void incrementTripIndex();
    Schedule setTripInfo();
    void addTripSchedule(Schedule trip);


    void displayTrainInfo();
    void displaySchedule(string date);
    void displaySchedule(string date, string time);
    void displayTrainInfoWithDate(string date);
    void displayTrainSchedule();
};

//class Metro {
//public:
//    unordered_map<int, deque<Train>&> lines;
//
//
//    deque<Train> getLineTrains(int lineID);
//};
//
//class Line {
//public:
//    int lineID=0;
//    Line();
//    deque<Train> trains;
//
//    void addTrain(Train newTrain);
//    void editTrain(Train editTrain);
//    void removeTrain(Train removedTrain);
//    void addTripToTrainSchedule(Train train, Schedule schedule);
//    void modifyTripFromTrainSchedule(int lineID, int id, Schedule oldSchedule);
//    void deleteTripFromTrainSchedule(int trainID, Schedule deleteSchedule);
//    void simulateTrainBreakdown(int  brokenTrainID, string time, string date);
//    size_t findScheduleIndex(Train train, string time, string date);
//    void adjustNextTrainDepartureTime(Train t);
//    void displayTrains();
//};

// class Station {
//     unordered_map<system_clock::time_point&, deque<Train>>& stationSchedule;

//     void findTrips(system_clock::time_point tripTime);
// };
