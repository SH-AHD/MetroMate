//#include"trainManagement.h"
#include "TrainManagement.h"
//#include "UserAccount.h"

//#include <iostream>
//#include<chrono>
//#include<ctime>
//using namespace std;
//using namespace std::chrono;


//// Schedule class
//
//// Getter methods
//int Schedule::getDelay() { retuen delay; }
//string Schedule::getDate() { return Date; }
//string  Schedule::getDepartureStation() { return departureStation; }
//string Schedule::getDestinationStation() { return destinationStation; }
//system_clock::time_point Schedule::getDepartureTime() { return departureTime; }
//system_clock::time_point Schedule::getArrivalTime() { return arrivalTime; }
//// Setter methods
//void Schedule::setArrivalTime(system_clock::time_point time) { arrivalTime = time; }
//void Schedule::setDate(strind date){
//    this->date = date;
//}
//void Schedule::setDelay(int delay){
//    this->delay = delay;
//}
//void Schedule::setDepartureStation(string departureStation){
//    this->departureStation = departureStation;
//}
//void Schedule::setDestinationStation(string destinationStation){
//    this->destinationStation = destinationStation;
//}
//void Schedule::setgetDepartureTime(system_clock::time_point departureTime){
//    this->departureTime = departureTime;
//}
// /*Schedule::Schedule(){
//
//  DateTime::dateDay ( DateTime::inputDateString(date));
//  cout << "Enter Departure Station: ";
//   cin >> departureStation;
//   cout << "Enter Destination Station: ";
//   cin >> destinationStation;
//   cout << "Enter Departure Time: ";
//   cin >> departureTime;
//   cout << "Enter Arrival Time: ";
//   cin >> arrivalTime;
//   cout << "Enter Delay Time \"Enter zero if there is no delay\" : ";
//   cin >> delay ;
//}*/
//
//Schedule::Schedule() {
//    // Initialization of Schedule attributes
//}
//
//
////Train class
//
//// Getter methods
//int Train:: getTrainID() { return trainID; }
//string Train::getStatus() { return status; }
//int Train::getLineID() { return lineID; }
//Schedule Train::getTrainSchedule() { return trainSchedule; }
//Schedule Train::getTrainScheduleCurrentTripIndex() { return trainSchedule[currentTripIndex]; }
////setter
//void setTrainID(int trainID) {
//    this->trainID = trainID;
//}
//void  setStatus(string status) {
//    this->status = status;
//}
//void  setLineID(int lineID) {
//    this->lineID = lineID;
//}
//void Train::setTrainSchedule(Schedule tschedule) { trainSchedule.push_back(tschedule); }
//
////methods
//minutes  Train::calculateETA(system_clock::time_point departureTime, system_clock::time_point arrivalTime) {
//    if (bool isBrokenDown==false) {
//        // Calculate ETA based on current time and departure time
//        auto duration = DateTime::calculateTimeDifferenceMinutes(departureTime, arrivalTime);
//        return duration;
//    }
//    else {
//        // If train is broken down, return a default ETA of 0 minutes
//        return minutes(0);
//    }
//}
//
//
//void Train::adjustNextTripDepartureTime() {
//    if (currentTripIndex + 1 < trainSchedule.size() && trainSchedule[currentTripIndex].getDelay() > 0) {
//        // Adjust departure time of the next trip
//        auto& nextTrip = trainSchedule[currentTripIndex + 1];
//        nextTrip.setDepartureTime(nextTrip.getDepartureTime() + minutes(trainSchedule[currentTripIndex].getDelay()));
//    }
//}
//
//// Set the current trip index
//void Train::setCurrentTripIndex(int index) {
//    currentTripIndex = index;
//}
//
//
//void Train::incrementTripIndex() {
//    if (currentTripIndex + 1 < trainSchedule.size()) {
//        ++currentTripIndex;
//    }
//}
//
////Line class
//void  Line:: addTrain(Train newTrain){
//    trains.push_back(newTrain);
//}
//
//
////void Line::removeTrain(Train removedTrain) {
////    for (auto it = trains.begin(); it != trains.end(); ++it) {
////        if (it->getTrainID() == removedTrain.getTrainID()) {
////            cout << "Train \"" << removedTrain.getTrainID() << "\" has been successfully deleted.";
////            trains.erase(it);
////            break;
////        }
////    }
////}
//
//
//void Line::removeTrain(Train removedTrain){
//   /* for (auto& train : trains) {
//   if (train.getTrainID() == removedTrain.getTrainID()) { trains.erase() }   }*/
//
//    if (trains.find(removedTrain)) {
//      cout<<"Train \""<<removedTrain.getTrainID()<<"\" has been successfully deleted."
//        trains.erase(removedTrain);
//    }
//}
//
//void Line::addTrainSchedule(Train train, Schedule s){
//    if (trains.find(train)) {
//        train.setTrainSchedule(s);
//    }
//}
//void Line::editTrainSchedule(int lineID, Train train, Schedule  newSchedule){
//    if (trains.find(train.getTrainID())) {
//        train.setTrainSchedule(newSchedule);
//    }
//}
//void  Line::simulateTrainBreakdown(Train brokenTrain){
//
//    if (trains.find(brokenTrain.getTrainID())) {
//        brokenTrain.setStatus("Breakdown");
//      
//        int newDelay = rand() % 21 + 10; // Simulate random delay between 10-30 minutes "random val between 0 and 20 say 16 and % by 21 it = 16 and after that +10 => 26 mins"
//        brokenTrain.getTrainSchedule().setDelay(newDelay);
//    }
//
//}
//
//
//
//
////Metro class
//deque<Train> Metro::getLineTrains(int lineID) {
//    return lines[lineID];
//}
//
////
////void Station::findTrips(system_clock::time_point tripTime) {
////    if (stationSchedule.find(tripTime)->second.getTrainSchedule().getArrivalTime() == tripTime) {
////
////        cout << getTrainID();
////    }
//
//    void Station::findTrips(system_clock::time_point tripTime) {
//        for (auto& trainPair : stationSchedule) {
//            if (trainPair.second.getTrainSchedule().getArrivalTime() == tripTime) {
//                cout << trainPair.second.getTrainID();
//            }
//        }
//    }



string Schedule::getDate() { return date; }
int Schedule::getDelay() { return delay; }
string Schedule::getDepartureStation() { return departureStation; }
string Schedule::getDestinationStation() { return destinationStation; }
system_clock::time_point Schedule::getDepartureTime() { return departureTime; }
system_clock::time_point Schedule::getArrivalTime() { return arrivalTime; }

void Schedule::setDate(string date) { this->date = date; }
void Schedule::setDelay(int delay) { this->delay = delay; }
void Schedule::setDepartureStation(string departureStation) { this->departureStation = departureStation; }
void Schedule::setDestinationStation(string destinationStation) { this->destinationStation = destinationStation; }
void Schedule::setDepartureTime(system_clock::time_point departureTime) { this->departureTime = departureTime; }
void Schedule::setArrivalTime(system_clock::time_point arrivalTime) { this->arrivalTime = arrivalTime; }

//Schedule::Schedule() {}


Train::Train() {
    this->ID = 0;
    this->lineID = 0;
}

Train::Train(int id, int lid) {
    this->ID = id;
    this->lineID = lid;
}

int Train::getTrainID() { return ID; }
string Train::getStatus() { return status; }
int Train::getLineID() { return lineID; }
Schedule Train::getTrainSchedule() { return trainSchedule; }

void Train::setTrainID(int trainID) { this->ID = trainID; }
void Train::setStatus(string status) { this->status = status; }
void Train::setLineID(int lineID) { this->lineID = lineID; }
void Train::setTrainSchedule(Schedule tschedule) { this-> trainSchedule.push_back(tschedule); }

minutes Train::calculateETA(system_clock::time_point departureTime, system_clock::time_point arrivalTime) {
    if (!isBrokenDown) {
        auto duration = std::chrono::duration_cast<std::chrono::minutes>(arrivalTime - departureTime);
        return duration;
    }
    else {
        return minutes(0);
    }
}

void Train::adjustNextTripDepartureTime() {
    if (currentTripIndex + 1 < trainSchedule.size() && trainSchedule[currentTripIndex].getDelay() > 0) {
        auto& nextTrip = trainSchedule[currentTripIndex + 1];
        nextTrip.setDepartureTime(nextTrip.getDepartureTime() + minutes(trainSchedule[currentTripIndex].getDelay()));
    }
}

void Train::setCurrentTripIndex(int index) { currentTripIndex = index; }

void Train::incrementTripIndex() {
    if (currentTripIndex + 1 < trainSchedule.size()) {
        ++currentTripIndex;
    }
}

void Train::displayTrainInfo() {
    cout << "Train ID:" << ID << "\n";
    cout << "Line ID:" << lineID << "\n";
    cout << "Train Status:" <<status << "\n";

}

void Train::displaySchedule(string date) {
    cout << "Train Schedule:" << "\n";
    cout <<DateTime::dateDay(date) << "-" << date << " \n";
    for (auto& schedule : trainSchedule) {
        if (schedule.getDate() == date) {
            cout << "Train Departure Station:" << schedule.getDepartureStation()<<"\n";
            cout << "Train Departure Time:" << schedule.getDepartureTime() << "\n";
            cout << "Train Destination Station:" << schedule.getDestinationStation() << "\n";
            cout << "Train Departure Time:" << schedule.getArrivalTime() << "\n";
            if(schedule.getDelay()>0)
            cout << "Train Delay:" << schedule.getDelay() << "\n";

        }
    }
}

Line::Line() {


}
void Line::addTrain(Train newTrain) { trains.push_back(newTrain); }

void Line::removeTrain(Train removedTrain) {
    for (auto it = trains.begin(); it != trains.end(); ++it) {
        if (it->getTrainID() == removedTrain.getTrainID()) {
            cout << "Train \"" << removedTrain.getTrainID() << "\" has been successfully deleted." << endl;
            trains.erase(it);
            break;
        }
    }
}

void Line::addTrainSchedule(Train train, Schedule schedule) {
    for (auto& t : trains) {
        if (t.getTrainID() == train.getTrainID()) {
            t.setTrainSchedule(schedule);
            break;
        }
    }
}

void Line::editTrainSchedule(int lineID, Train train, Schedule newSchedule) {
    for (auto& t : trains) {
        if (t.getTrainID() == train.getTrainID()) {
            t.setTrainSchedule(newSchedule);
            break;
        }
    }
}

void Line::simulateTrainBreakdown(Train brokenTrain) {
    for (auto& t : trains) {
        if (t.getTrainID() == brokenTrain.getTrainID()) {
            t.setStatus("Breakdown");
            int newDelay = rand() % 21 + 10;
            t.getTrainSchedule().setDelay(newDelay);
            break;
        }
    }
}

void Line::displayTrains() {
    cout << "Trains in Line:" << endl;
    for (const auto& train : trains) {
        train.displayTrainInfo();
    }
}
deque<Train> Metro::getLineTrains(int lineID) { return lines[lineID]; }


//Station::Station(unordered_map<system_clock::time_point&, deque<Train>>& stationSchedule) {
//    this->stationSchedule = stationSchedule;
//}

Station::Station(unordered_map<system_clock::time_point, deque<Train>>& schedule)
    : stationSchedule(schedule) {
   
}

void Station::findTrips(system_clock::time_point tripTime) {
    for (auto& trainPair : stationSchedule) {
        if (trainPair.second.getTrainSchedule().getArrivalTime() == tripTime) {
            cout << trainPair.second.getTrainID();
        }
    }
}

