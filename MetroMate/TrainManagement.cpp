#include "TrainManagement.h"


Schedule::Schedule() {
    string date,departureStation,destinationStation, departureTime, arrivalTime;
    int delay = 0;
    cout << "Enter Date:\n";
    cin >> date;
    setDate(date);
    cout << "=======================================\n";
    cout << "Enter Departure Station :\n";
    cin >>departureStation;
    setDepartureStation(departureStation);
    cout << "Enter Destination Station :\n";
    cin >> destinationStation;
    setDestinationStation(destinationStation);
    cout << "Enter Departure Time :\n";
    cin >> departureTime;
    setDepartureTime(DateTime::timeInputString(departureTime));
    cout << "Enter Arrival Time :\n";
    cin >> arrivalTime;
    setArrivalTime(DateTime::timeInputString(arrivalTime));
}
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





Train::Train() {
   
    cout << "Enter Train ID:\n";
    cin >> ID;
    setTrainID(ID);
    cout << "Enter Line ID:\n";
    cin >> lineID;
    setLineID(lineID);
  
}

Train::Train(int id, int lid) {
    this->ID = id;
    this->lineID = lid;
}

int Train::getTrainID() { return ID; }
string Train::getStatus() { return status; }
int Train::getLineID() { return lineID; }
vector<Schedule> Train::getTrainSchedule() { return trainSchedule; }

void Train::setTrainID(int trainID) { this->ID = trainID; }
void Train::setStatus(string status) { this->status = status; }
void Train::setLineID(int lineID) { this->lineID = lineID; }
void Train::setTrainSchedule(Schedule tschedule) { this-> trainSchedule.push_back(tschedule); }

minutes Train::calculateETA(string depTime,string arrTime) {
    system_clock::time_point departureTime= DateTime::timeInputString(depTime);
   system_clock::time_point  arrivalTime = DateTime::timeInputString(arrTime);
    
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
int Train::getCurrentTripIndex() { return currentTripIndex; }

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
void Train::setTrainInfo() {
    int ID,lineID;
    cout << "Enter Train ID:\n";
    cin >> ID;
    setTrainID(ID);
    cout << "Enter Line ID:\n";
    cin >> lineID;
    setLineID(lineID);
    
}
void Train::displaySchedule(string date) {
    cout << "Train Schedule:" << "\n";
   // cout <<DateTime::dateDay(date) << "-" << date << " \n";
    for (auto& schedule : trainSchedule) {
        if (schedule.getDate() == date) {
            cout << "Train Departure Station:" << schedule.getDepartureStation()<<"\n";
            cout << "Train Departure Time:";
            DateTime::outputTimePoint(schedule.getDepartureTime());
            cout<< "\n";
            cout << "Train Destination Station:"<<schedule.getDestinationStation()<< "\n";
            cout << "Train Departure Time:";
            DateTime::outputTimePoint(schedule.getArrivalTime());
            cout << "\n";
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

//void Line::simulateTrainBreakdown(Train brokenTrain) {
//    for (auto& t : trains) {
//        if (t.getTrainID() == brokenTrain.getTrainID()) {
//            t.setStatus("Breakdown");
//            int newDelay = rand() % 21 + 10;
//           t.getTrainSchedule().setDelay(newDelay);
//            break;
//        }
//      
//    }
//}

size_t Line::findScheduleIndex( Train train, string stationName) {
    for (size_t i = 0; i < train.trainSchedule.size(); ++i) {
        if (train.trainSchedule[i].getDestinationStation() == stationName) {
            return i; // Found the schedule with the specified station name
        }
    }
    // Schedule not found, return a value indicating failure (e.g., -1 or train.trainSchedule.size())
    return std::string::npos; // Using npos to indicate failure
}

void Line::simulateTrainBreakdown(Train brokenTrain, string stationName) {
    for (auto& t : trains) {
        if (t.getTrainID() == brokenTrain.getTrainID()) {
            t.setStatus("Breakdown");
            size_t scheduleIndex = findScheduleIndex(t, stationName);
            if (scheduleIndex != std::string::npos) {
                int newDelay = rand() % 21 + 10;
                t.trainSchedule[scheduleIndex].setDelay(newDelay);
            }
            else {
                cout << "Schedule for station \"" << stationName << "\" not found." << endl;
            }
            break;
        }
    }
}




void Line::displayTrains() {
    cout << "Trains in Line:" << endl;
    for ( auto& train : trains) {
        train.displayTrainInfo();
    }
}
//deque<Train> Metro::getLineTrains(int lineID) { return lines[lineID]; }


//Station::Station(unordered_map<system_clock::time_point&, deque<Train>>& stationSchedule) {
//    this->stationSchedule = stationSchedule;
//}

// Station::Station(unordered_map<system_clock::time_point, deque<Train>>& schedule)
//     : stationSchedule(schedule) {
   
// }

// void Station::findTrips(system_clock::time_point tripTime) {
//     for (auto& trainPair : stationSchedule) {
//         if (trainPair.second.getTrainSchedule().getArrivalTime() == tripTime) {
//             cout << trainPair.second.getTrainID();
//         }
//     }
// }

