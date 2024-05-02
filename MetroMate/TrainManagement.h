//#include <iostream>
//#include <deque>
//#include<unordered_map>
//#include<chrono>
//#include<ctime>
//#include <random>
//#include <string>
//
//using namespace std;
//using namespace std::chrono;
//
//class Schedule {
//private:
//    strind date;
//    string departureStation;
//    string destinationStation;
//    system_clock::time_point departureTime;
//    system_clock::time_point arrivalTime;
//    int delay=0;
//    //static  int currentTripIndex ;
//public:
//    string getDate();
//    int  getDelay();
//    string getDepartureStation();
//    string getDestinationStation();
//    system_clock::time_point getDepartureTime();
//    system_clock::time_point getArrivalTime();
//    //setter
//    void setDate(strind date);
//    void setDelay(int delay);
//    void setDepartureStation(string departureStation)
//    void setDestinationStation(string destinationStation);
//    void setgetDepartureTime(system_clock::time_point departureTime);
//    void Schedule::setArrivalTime(system_clock::time_point time);
//    //constructor
//    Schedule();
//    
//};
//
//
//class Train {
//private:
//
//    int ID;
//    int lineID;
//    bool isBrokenDown = false; // Flag to indicate if the train is broken down
//    string status;
//    int currentTripIndex = 0;
//public:
//
//    vector<Schedule> trainSchedule;
//    // Getter methods
//    int  getTrainID();
//    string  getStatus();
//    int  getLineID();
//    Schedule getTrainSchedule();
//    //setter 
//    void setTrainID(int trainID);
//    void  setStatus(string status);
//    void  setLineID(int lineID);
//    void setTrainSchedule(Schedule tschedule);
//    //methods
//    minutes calculateETA(system_clock::time_point departureTime, system_clock::time_point arrivalTime);
//    void adjustNextTripDepartureTime();
//    void setCurrentTripIndex(int index);
//    void incrementTripIndex();
//};
//  
//
//class Metro{
//private:
//    unordered_map<int, deque<Train>> lines;
//public:
////    void addLine(int lineID);
////    void addTrain(int lineID, int trainID);
////    Train removeTrain(int lineID, int trainID);
////    void Metro::addTrainSchedule(Train train, vector<Schedule> schedule);
////    void editTrainSchedule(int lineID, int trainID,vector<Schedule> newSchedule);
//// void simulateTrainBreakdown(int line_id, int train_id);
//    deque<Train> getLineTrains(int lineID);
//
//};
//
//
//class Line {
//public:
//    deque<Train> trains;
//
//    void addTrain(Train newTrain);
//    void removeTrain(Train removedTrain);
//    void addTrainSchedule(Train train, Schedule schedule);
//    void editTrainSchedule(int lineID, int trainID, Schedule newSchedule);
//    void simulateTrainBreakdown(Train brokenTrain);
//
//
//};
//
//
//class Station {
//public:
//    unordered_map<system_clock::time_point, deque<Train>> stationSchedule;
//
//    void findTrips(system_clock::time_point tripTime);
//
//};



#include <iostream>
#include <deque>
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <random>
#include <string>

#include "UserAccount.h"

using namespace std;
using namespace std::chrono;

class Schedule {
private:
    string date;
    string departureStation;
    string destinationStation;
    system_clock::time_point departureTime;
    system_clock::time_point arrivalTime;
    int delay = 0;

public:
    string getDate();
    int getDelay();
    string getDepartureStation();
    string getDestinationStation();
    system_clock::time_point getDepartureTime();
    system_clock::time_point getArrivalTime();
    void setDate(string date);
    void setDelay(int delay);
    void setDepartureStation(string departureStation);
    void setDestinationStation(string destinationStation);
    void setDepartureTime(system_clock::time_point departureTime);
    void setArrivalTime(system_clock::time_point arrivalTime);
    Schedule();
};

class Train {
private:
    int ID;
    int lineID;
    bool isBrokenDown = false;
    string status;
    int currentTripIndex = 0;

public:
    Train();
    Train(int id, int lid);
    vector<Schedule> trainSchedule;
    int getTrainID();
    string getStatus();
    int getLineID();
    Schedule getTrainSchedule();
    void setTrainID(int trainID);
    void setStatus(string status);
    void setLineID(int lineID);
    void setTrainSchedule(Schedule tschedule);
    minutes calculateETA(system_clock::time_point departureTime, system_clock::time_point arrivalTime);
    void adjustNextTripDepartureTime();
    void setCurrentTripIndex(int index);
    void incrementTripIndex();
    void displayTrainInfo();
    void displaySchedule();
};

class Metro {
public:
    unordered_map<int, deque<Train>&> lines;


    deque<Train> getLineTrains(int lineID);
};

class Line {
public:
    Line();
    deque<Train> trains;

    void addTrain(Train newTrain);
    void removeTrain(Train removedTrain);
    void addTrainSchedule(Train train, Schedule schedule);
    void editTrainSchedule(int lineID, Train train, Schedule newSchedule);
    void simulateTrainBreakdown(Train brokenTrain);
    void displayTrains();
};

class Station {
    unordered_map<system_clock::time_point&, deque<Train>>& stationSchedule;
  /*  string name;
    int lineNumber;

    station(string n, int num) {
        name = n;
        lineNumber = num;
    }
    station() {

    }*/
    void findTrips(system_clock::time_point tripTime);
};
