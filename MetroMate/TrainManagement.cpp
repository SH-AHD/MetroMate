#include "TrainManagement.h"
#include <algorithm>

#include"DateTime.h" 



Schedule::Schedule() {
    
}
Schedule::Schedule(string date, string departureStation, string destinationStation, string departureTime, string arrivalTime){
   
     setDate(date);
    
     setDepartureStation(departureStation);
    
     setDestinationStation(destinationStation);
  
     setDepartureTime(DateTime::timeInputString(departureTime));
  
     setArrivalTime(DateTime::timeInputString(arrivalTime));


}
string Schedule::getDate() { return date; }

int Schedule::getDelay() { return delay; }

string Schedule::getDepartureStation() { return departureStation; }

string Schedule::getDestinationStation() { return destinationStation; }

system_clock::time_point Schedule::getDepartureTime() { return departureTime; }

system_clock::time_point Schedule::getArrivalTime() { return arrivalTime; }

bool Schedule::getBroken() { return broken; }

void Schedule::setBroken(bool broken) { this->broken = broken; }
void Schedule::setDate(string date) { this->date = date; }
void Schedule::setDelay(int delay) { this->delay = delay; }
void Schedule::setDepartureStation(string departureStation) { this->departureStation = departureStation; }
void Schedule::setDestinationStation(string destinationStation) { this->destinationStation = destinationStation; }
void Schedule::setDepartureTime(system_clock::time_point departureTime) { this->departureTime = departureTime; }
void Schedule::setArrivalTime(system_clock::time_point arrivalTime) { this->arrivalTime = arrivalTime; }

void Schedule::setTripScheduleInfo() {
    string date, departureStation, destinationStation, departureTime, arrivalTime;
    int delay = 0;
    MetroMate metroo;
    /* cout << "Enter Date:\n";
     cin >> date;*/
    setDate(DateTime::inputDateString());
    cout << "=======================================\n";
    cout << "Choose Departure Station :\n";
    //cin >> departureStation;
    metroo.displayStations();
    
   // if(departureStation== station.getName())
    departureStation = (metroo.chooseStation())->getName();
    setDepartureStation(departureStation);
    cout << "Choose Destination Station : \n";
    //cin >> destinationStation;
    metroo.displayStations();
    //station = metro.chooseStation();
    // if(departureStation== station.getName())
    destinationStation = (metroo.chooseStation())->getName();
    setDestinationStation(destinationStation);
    do {
        cout << "Enter Departure Time :\n";
        cin >> departureTime;
        setDepartureTime(DateTime::timeInputString(departureTime));
    } while (getDepartureTime() == system_clock::time_point());

    do {
        cout << "Enter Arrival Time :\n";
        cin >> arrivalTime;
        setArrivalTime(DateTime::timeInputString(arrivalTime));
    } while (getArrivalTime() == system_clock::time_point());

    //setTripIndex(getNextTripCount());
}

void Schedule::displaySchedule() {
    cout << "Schedule Date:" << getDate() << "\n";
    cout << "Train Departure Station:" << getDepartureStation() << "\n";
    cout << "Train Departure Time:";
    DateTime::outputTimePoint(getDepartureTime());
    cout << "\n";
    cout << "Train Destination Station:" << getDestinationStation() << "\n";
    cout << "Train Departure Time:";
    DateTime::outputTimePoint(getArrivalTime());
    cout << "\n";
    cout << "Train Delay:" << getDelay() << "\n";
}


Train::Train() {

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
void Train::setTrainSchedule(Schedule tschedule) { this->trainSchedule.push_back(tschedule); }



int Train::calculateETA(string depTime, string arrTime) {
    system_clock::time_point departureTime = DateTime::timeInputString(depTime);
    system_clock::time_point arrivalTime = DateTime::timeInputString(arrTime);

    auto duration = std::chrono::duration_cast<std::chrono::minutes>(arrivalTime - departureTime);
    return static_cast<int>(duration.count()); // Convert duration to integer

}


Schedule Train::setTripInfo() {

    string date, departureStation, destinationStation, departureTime, arrivalTime;
    int delay = 0;
    Schedule schedule;
    // cout << "setTripInfo";
    /* cout << "Enter Date in the format (DD-MM-YYYY):";
     cin >> date;*/
    schedule.setDate(DateTime::inputDateString());
    cout << "=======================================\n";
    cout << "Enter Departure Station :\n";
    cin >> departureStation;
    schedule.setDepartureStation(departureStation);
    cout << "Enter Destination Station :\n";
    cin >> destinationStation;
    schedule.setDestinationStation(destinationStation);
   

        do {
            cout << "Enter Departure Time :\n";
            cin >> departureTime;
            schedule.setDepartureTime(DateTime::timeInputString(departureTime));
        } while (schedule.getDepartureTime() == system_clock::time_point());


       do {
           cout << "Enter Arrival Time :\n";
           cin >> arrivalTime;
           if (arrivalTime > departureTime) {
               schedule.setArrivalTime(DateTime::timeInputString(arrivalTime));
           }else{
               cout << "Arrival time must be > depature time\n";
               schedule.setArrivalTime(system_clock::time_point());
           }
       } while (schedule.getArrivalTime() == system_clock::time_point());


      //  schedule.setTripIndex(schedule.getNextTripCount());
    return schedule;
}

void Train::addTripSchedule(Schedule trip) {

    trainSchedule.push_back(trip);
    currentTripIndex++;

}
void Train::setCurrentTripIndex(int index) { currentTripIndex = index; }
int Train::getCurrentTripIndex() { return currentTripIndex; }

void Train::incrementTripIndex() {
    if (currentTripIndex + 1 < trainSchedule.size()) {
        ++currentTripIndex;
    }
}





void Train::displaySchedule(string date) {
    
 
    for (auto& schedule : trainSchedule) {
        cout << "!!!!!!!!!";
        if (schedule.getDate() == date) {
            cout << "Trip Date :"  << schedule.getDate() << "\n";
                cout << "Train Departure Station:" << schedule.getDepartureStation() << "\n";
            cout << "Train Departure Time:";
            DateTime::outputTimePoint(schedule.getDepartureTime());
            cout << "\n";
            cout << "Train Destination Station:" << schedule.getDestinationStation() << "\n";
            cout << "Train Departure Time:";
            DateTime::outputTimePoint(schedule.getArrivalTime());
            cout << "\n";
            //if (schedule.getDelay() > 0)
            cout << "Train Delay:" << schedule.getDelay() << "\n";
        }
        else {
            cout << "Date not found!";
        }
        
    }



}


void Train::displaySchedule(string date, string DepartureTime) {
    cout << "Train Schedule:" << "\n";
    // cout <<DateTime::dateDay(date) << "-" << date << " \n";
    for (auto& schedule : trainSchedule) {
        auto zero = std::chrono::minutes(0);
        //auto timeDifference = DateTime::calculateTimeDifferenceMinutes(DateTime::timeInputString(DepartureTime), schedule.getDepartureTime());

        if (schedule.getDate() == date && DateTime::calculateTimeDifferenceMinutes(DateTime::timeInputString(DepartureTime), schedule.getDepartureTime()) == zero) {
            cout << "Train Departure Station:" << schedule.getDepartureStation() << "\n";
            cout << "Train Departure Time:";
            DateTime::outputTimePoint(schedule.getDepartureTime());
            cout << "\n";
            cout << "Train Destination Station:" << schedule.getDestinationStation() << "\n";
            cout << "Train Departure Time:";
            DateTime::outputTimePoint(schedule.getArrivalTime());
            cout << "\n";
            if (schedule.getDelay() > 0)
                cout << "Train Delay:" << schedule.getDelay() << "\n";
            break;
        }
    }
}

void Train::displayTrainInfoWithDate(string date) {

    cout << "Train ID:" << ID << "\n";
    cout << "Line ID:" << lineID << "\n";
    cout << "Train Status:" << status << "\n";
    displaySchedule(date);
}

void Train::displayTrainInfo() {

    cout << "Train ID: " << ID << "\n";
    cout << "Line ID: " << lineID << "\n";
    cout << "Train Status: " << status << "\n";
    displayTrainSchedule();
}


void Train::setTrainInfo() {

    cout << "Enter Train ID:\n";
    cin >> ID;
    setTrainID(ID);
    cout << "Enter Line ID:\n";
    cin >> lineID;
    setLineID(lineID);
    //cout << "===================\nAdd Schedule: \n============\n";

   // addTripSchedule(setTripInfo());
}


Schedule Train::getTripInfo(Schedule s) {

    s.getDate();
    s.getDepartureStation();
    s.getDepartureTime();
    s.getDestinationStation();
    s.getArrivalTime();
    s.getBroken();
    s.getDelay();
  
    return s;
}



void Train::adjustNextTripDepartureTime() {
    if (currentTripIndex + 1 < trainSchedule.size() && trainSchedule[currentTripIndex].getDelay() > 0) {

        for (int i = 1; i < trainSchedule.size(); i++) {
            auto& nextTrip = trainSchedule[currentTripIndex + i];
            if (nextTrip.getDepartureStation() == trainSchedule[currentTripIndex].getDestinationStation()) {
                nextTrip.setDepartureTime(nextTrip.getDepartureTime() + minutes(trainSchedule[currentTripIndex].getDelay()));
                nextTrip.setArrivalTime(nextTrip.getArrivalTime() + minutes(trainSchedule[currentTripIndex].getDelay()));
            }
        }
        
    }
   
}


void Train::displayTrainSchedule() {
   
    cout << "Train " << ID << " Schedule:" << "\n";

    for (int i = 0; i < trainSchedule.size();i++) {

        cout << "Trip " << i << "\n";
        cout << "Schedule Date:" << trainSchedule[i].getDate() << "\n";
        cout << "Train Departure Station:" << trainSchedule[i].getDepartureStation() << "\n";
        cout << "Train Departure Time:";
        DateTime::outputTimePoint(trainSchedule[i].getDepartureTime());
        cout << "\n";
        cout << "Train Destination Station:" << trainSchedule[i].getDestinationStation() << "\n";
        cout << "Train Departure Time:";
        DateTime::outputTimePoint(trainSchedule[i].getArrivalTime());
        cout << "\n";
        //if (schedule.getDelay() > 0)
        cout << "Train Delay:" << trainSchedule[i].getDelay() << "\n";

       
    }

}




int Train::getETAForTrip(string stationName, string checkindate, chrono::system_clock::time_point currentTime) {
    // Sort the trainSchedule based on arrivalTime
    sort(trainSchedule.begin(), trainSchedule.end(), []( Schedule& a,  Schedule& b) {
        return a.getArrivalTime() < b.getArrivalTime();
        });

    for (auto& schedule : trainSchedule) {
        // Check if the schedule matches the specified station, date, and arrival time condition
        if (schedule.getDate() == checkindate &&
            schedule.getDestinationStation() == stationName &&
            schedule.getArrivalTime() >= currentTime)
        {
            // Calculate the time difference between the current time and the arrival time
            auto arrtime = DateTime::calculateTimeDifferenceMinutes(schedule.getArrivalTime(), currentTime);
            cout << "The train will arrive in " << arrtime.count() << " minutes.";
            return 1;
        }
    }

    // If no matching schedule is found, return 0
    return 0;
}



