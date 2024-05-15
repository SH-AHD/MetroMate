#include "TrainManagement.h"
#include <algorithm>

#include"DateTime.h" 



Schedule::Schedule() {
    /*  string date,departureStation,destinationStation, departureTime, arrivalTime;
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
      setArrivalTime(DateTime::timeInputString(arrivalTime));*/
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
    // cout<<"const";
   //   cout << "Enter Train ID:\n";
   //   cin >> ID;
   //   setTrainID(ID);
   //   cout << "Enter Line ID:\n";
   //   cin >> lineID;
   //   setLineID(lineID);
   //   cout << "===================\nAdd Schedule: \n============\n";
   ///* Schedule();*/
   //   addTripSchedule();
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

//minutes Train::calculateETA(string depTime,string arrTime) {
//    system_clock::time_point departureTime= DateTime::timeInputString(depTime);
//   system_clock::time_point  arrivalTime = DateTime::timeInputString(arrTime);
//    
//    if (!isBrokenDown) {
//        auto duration = std::chrono::duration_cast<std::chrono::minutes>(arrivalTime - departureTime);
//        return duration;
//    }
//    else {
//        return minutes(0);
//    }
//}


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
    //do {
    //    cout << "OK!!!!!!!!!!!!";
    //    cout << "Enter Departure Time :\n";
    //    cin >> departureTime;
    //    cout << "Enter Arrival Time :\n";
    //    cin >> arrivalTime;
    //    //deptime ?5 : 15 && arrivaltime?24 : 00 && arrivaltime - deptime>=3
    //    auto departureTimePoint = DateTime::timeInputString(departureTime);
    //    auto arrivalTimePoint = DateTime::timeInputString(arrivalTime);
    //    // auto now = std::chrono::system_clock::now();
    //     // Get the start of the current day
    //     //auto startOfDay = std::chrono::time_point_cast<std::chrono::hours>(now);
    //     // Calculate minTime and maxTime
    //     //auto minTime = startOfDay + std::chrono::hours(5) + std::chrono::minutes(15);
    //     //auto maxTime = startOfDay + std::chrono::hours(24) + std::chrono::minutes(0);
    //    //auto startOfDay = std::chrono::time_point_cast<std::chrono::hours>(0);
    //    auto minTime = std::chrono::hours(5) + std::chrono::minutes(15);
    //    auto maxTime =  std::chrono::hours(24) + std::chrono::minutes(0);
    //    //auto minTime = std::chrono::hours(5) + std::chrono::minutes(15);
    //    //auto maxTime = std::chrono::hours(24) + std::chrono::minutes(0);
    //    auto minDuration = std::chrono::minutes(3);
    //    auto timeDifference = std::chrono::duration_cast<std::chrono::minutes>(arrivalTimePoint - departureTimePoint);
    //    if (departureTimePoint >= minTime && arrivalTimePoint <= maxTime && timeDifference >= minDuration) {
    //        //if (DateTime::timeInputString(departureTime)>= minTime && DateTime::timeInputString(arrivalTime)<= maxTime && DateTime::calculateTimeDifferenceMinutes(DateTime::timeInputString(arrivalTime) ,DateTime::timeInputString(departureTime)) >= minDuration) {
    //        schedule.setArrivalTime(DateTime::timeInputString(arrivalTime));
    //        schedule.setDepartureTime(DateTime::timeInputString(departureTime));
    //    }
    //    else {
    //        cout << "The departure time must be from 05:15 AM and above and the arrival time must be before 24:00.\n ";
    //        cout << "The difference between the arrival time and the departure time must be >= 3 minutes.\n";
    //        schedule.getDepartureTime() == system_clock::time_point();
    //        schedule.getArrivalTime() == system_clock::time_point();
    //    }
    //} while (schedule.getDepartureTime() == system_clock::time_point() && schedule.getArrivalTime() == system_clock::time_point());

    //do {
    //    cout << "OK!!!!!!!!!!!!";
    //    cout << "Enter Departure Time (HH:MM): ";
    //    cin >> departureTime;
    //    cout << "Enter Arrival Time (HH:MM): ";
    //    cin >> arrivalTime;

    //   // // Convert to time_point objects
    //   // auto departureTimePoint = DateTime::timeInputString(departureTime);
    //   // auto arrivalTimePoint = DateTime::timeInputString(arrivalTime);

    //   // // Calculate durations relative to a reference point (e.g., midnight)
    //   // // You might need to adjust this based on your timekeeping approach
    //   // auto referencePoint = std::chrono::hours(0);// Assuming midnight as reference
    //   // auto minTime = DateTime::timeInputString("5:15");
    //   // auto maxTime = DateTime::timeInputString("24:00");
    //   // auto minTimeDuration= minTime- referencePoint;
    //   //  auto maxTimeDuration =maxTime- referencePoint;
    //   // auto departureDuration = departureTimePoint - referencePoint;
    //   // auto arrivalDuration = arrivalTimePoint - referencePoint;

    //   // // Minimum duration requirement (3 minutes)
    //   // auto minDuration = std::chrono::minutes(3); // Duration representing 3 minutes
    //   // auto tripDuration = DateTime::timeInputString(departureTime) + minDuration;

    //   ///* if (departureDuration >= std::chrono::hours(5) + std::chrono::minutes(15) &&
    //   //     arrivalDuration <= std::chrono::hours(24) &&
    //   //     arrivalDuration >= departureDuration + minDuration) {*/

    //   //     if ((departureDuration >= minTimeDuration) &&
    //   //         (arrivalDuration <= maxTimeDuration) &&
    //   //         (arrivalDuration >= minDuration)) {


    //    //// Convert to time_point objects
    //    //auto departureTimePoint = DateTime::timeInputString(departureTime);
    //    //auto arrivalTimePoint = DateTime::timeInputString(arrivalTime);

    //    //// Calculate durations relative to a reference point (midnight)
    //    //auto minTime = DateTime::timeInputString("5:15");
    //    //auto maxTime = DateTime::timeInputString("24:00");
    //    //auto minTimeDuration = minTime - DateTime::timeInputString("00:00");
    //    //auto maxTimeDuration = maxTime - DateTime::timeInputString("00:00");
    //    //auto departureDuration = departureTimePoint - DateTime::timeInputString("00:00");
    //    //auto arrivalDuration = arrivalTimePoint - DateTime::timeInputString("00:00");

    //    //// Minimum duration requirement (3 minutes)
    //    //auto minDuration = std::chrono::minutes(3);

    //    //// Check if the schedule satisfies the conditions
    //    //if ((departureDuration >= minTimeDuration) &&
    //    //    (arrivalDuration <= maxTimeDuration) &&
    //    //    (arrivalDuration >= departureDuration + minDuration))
    //    //{


    //        schedule.setArrivalTime(DateTime::timeInputString(arrivalTime));
    //         schedule.setDepartureTime(DateTime::timeInputString(departureTime));
    //    //}
    //    //else {
    //    //    cout << "Invalid time input.\n";
    //    //    cout << "  - Departure time must be after 5:15 AM.\n";
    //    //    cout << "  - Arrival time must be before midnight.\n";
    //    //    cout << "  - The trip duration must be at least 3 minutes.\n";
    //    //    // Clear invalid times from the schedule object (optional)
    //    //    schedule.getDepartureTime() = system_clock::time_point();
    //    //    schedule.getArrivalTime() = system_clock::time_point();
    //    //}
    //} while (schedule.getDepartureTime() == system_clock::time_point() &&
    //    schedule.getArrivalTime() == system_clock::time_point());

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


//for (auto& t : trains) {
//    if (t.getTrainID() == trainID) {
//
//        for (auto& schedule : t.getTrainSchedule()) {
//            if (schedule.getDate() == date) {
//                if (DateTime::calculateTimeDifferenceMinutes(DateTime::timeInputString(DepartureTime), schedule.getDepartureTime()) == 0)
//                {
//                    Schedule.
//                }
//                else {
//                    cout << "Departure Time not found";
//                    return;
//
//                }
//
//            }
//            else {
//                cout << "Date not found";
//                return;
//            }
//
//        }
//    }
//}


void Train::displaySchedule(string date) {
    
    // cout <<DateTime::dateDay(date) << "-" << date << " \n";
   /* for (auto& schedule : trainSchedule) {
        cout<<"!!!!!!!!!";
        if (schedule.getDate() == date) {

            cout << "Train Schedule:" << "\n";
             cout << "Date:" << schedule.getDate() << "\n";
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

        }
        else {
            cout << "Date not found!";
        }
    }*/
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
    /* s.getNextTripCount();
     s.getTripIndex();
     s.getTripNum();*/
    return s;
}

//
//void Train::adjustNextTripDepartureTime() {
//    if (currentTripIndex + 1 < trainSchedule.size() && trainSchedule[currentTripIndex].getDelay() > 0) {
//        auto& nextTrip = trainSchedule[currentTripIndex + 1];
//        nextTrip.setDepartureTime(nextTrip.getDepartureTime() + minutes(trainSchedule[currentTripIndex].getDelay()));
//    }
//}


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


//void Train::setTrainInfo() {
//    int ID,lineID;
//   
//    cout << "Enter Train ID:\n";
//    cin >> ID;
//    setTrainID(ID);
//    cout << "Enter Line ID:\n";
//    cin >> lineID;
//    setLineID(lineID);
//    
//}
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

//int Train::getETAForTrip(string stationName, string checkindate, string checkinTime) {
//    sort(trainSchedule.begin(), trainSchedule.end(), [](const Schedule& a, const Schedule& b) {
//        return a.arrivalTime < b.arrivalTime;
//
//        }
//    for (auto& schedule : trainSchedule) {
//
//        if (schedule.getDate() == checkindate && schedule.getDestinationStation() == stationName && schedule.getArrivalTime() >= DateTime::timeInputString(checkinTime))
//        {
//          auto arrtime=  DateTime::calculateTimeDifferenceMinutes(schedule.getArrivalTime(), DateTime::timeInputString(checkinTime));
//            cout << "The train will arrive in " <<arrtime << " minutes.";
//            return 1;
//        }
//    }
//
//}
//


int Train::getETAForTrip(string stationName, string checkindate, string checkinTime) {
    // Sort the trainSchedule based on arrivalTime
    sort(trainSchedule.begin(), trainSchedule.end(), []( Schedule& a,  Schedule& b) {
        return a.getArrivalTime() < b.getArrivalTime();
        });

    for (auto& schedule : trainSchedule) {
        // Check if the schedule matches the specified station, date, and arrival time condition
        if (schedule.getDate() == checkindate &&
            schedule.getDestinationStation() == stationName &&
            schedule.getArrivalTime() >= DateTime::timeInputString(checkinTime))
        {
            // Calculate the time difference between the current time and the arrival time
            auto arrtime = DateTime::calculateTimeDifferenceMinutes(schedule.getArrivalTime(), DateTime::timeInputString(checkinTime));
            cout << "The train will arrive in " << arrtime.count() << " minutes.";
            return 1;
        }
    }

    // If no matching schedule is found, return 0
    return 0;
}




//
//Line::Line() {
//
//
//}
//void Line::addTrain(Train newTrain) { 
//    trains.push_back(newTrain); 
//    cout << "Train \"" << newTrain.getTrainID() << "\" has been successfully added." << endl;
//
//}
//
//void Line::editTrain(Train editTrain) {
//    for (auto it = trains.begin(); it != trains.end(); ++it) {
//        if (it->getTrainID() == editTrain.getTrainID()) {
//            it->setTrainInfo();
//            break;
//        }
//    }
//}
//
//void Line::removeTrain(Train removedTrain) {
//    for (auto it = trains.begin(); it != trains.end(); ++it) {
//        if (it->getTrainID() == removedTrain.getTrainID()) {
//            cout << "Train \"" << removedTrain.getTrainID() << "\" has been successfully deleted." << endl;
//            trains.erase(it);
//            break;
//        }
//    }
//}
//
//void Line::addTripToTrainSchedule(Train train, Schedule schedule) {
//    for (auto& t : trains) {
//        if (t.getTrainID() == train.getTrainID()) {
//            t.setTrainSchedule(schedule);
//            cout << "The trip  has been successfully added!\n";
//            break;
//        }
//    }
//}
//
////void Line::modifyTripFromTrainSchedule(int lineID, int id, Schedule oldSchedule) {
////    for (auto& t : trains) {
////        if (t.getTrainID() == id) {
////            auto it = find(t.trainSchedule.begin(), t.trainSchedule.end(), oldSchedule);
////            if (it != t.trainSchedule.end()) {
////                oldSchedule.setTripScheduleInfo();
////                cout << "The trip information has been successfully modified!\n";
////            }
////                break;
////        }
////    }
////}
//
//void Line::modifyTripFromTrainSchedule(int lineID, int id, Schedule oldSchedule) {
//    for (auto& t : trains) {
//        if (t.getTrainID() == id) {
//            for (auto& schedule : t.getTrainSchedule()) {
//                long t1 = DateTime::calculateTimeDifferenceMinutes(schedule.getDepartureTime(), oldSchedule.getDepartureTime());;
//                long t2 = DateTime::calculateTimeDifferenceMinutes(schedule.getArrivalTime(), oldSchedule.getArrivalTime());;
//             
//                // Compare relevant properties of the schedules
//                if (schedule.getDate() == oldSchedule.getDate()&& 
//                    schedule.getDelay() == oldSchedule.getDelay()&&
//                    schedule.getDepartureStation() == oldSchedule.getDepartureStation() &&
//                    schedule.getDestinationStation() == oldSchedule.getDestinationStation() &&
//                    t1 == 0 && t2 == 0&&
//                    schedule.getBroken()== oldSchedule.getBroken()) {                    
//                    schedule.setTripScheduleInfo(); 
//                    cout << "The trip information has been successfully modified!\n";
//                    return; // Exit the function after modifying the trip
//                }
//            }
//        }
//    }
//    // If the loop completes without finding the schedule
//    cout << "Schedule not found for modification.\n";
//}
//
//
//
//
//void Line::deleteTripFromTrainSchedule(int trainID, Schedule deleteSchedule) {
//    for (auto& t : trains) {
//        if (t.getTrainID() == trainID ) {
//         /*   auto it = t.trainSchedule.find(t.trainSchedule.front(), t.trainSchedule.end(), deleteSchedule);
//            if (it != t.trainSchedule.end()) {
//                t.trainSchedule.erase(it);
//                cout << "The trip has been successfully deleted!\n";
//            }*/
//            auto it = find(t.getTrainSchedule().begin(), t.getTrainSchedule().end(), deleteSchedule);
//            if (it != t.getTrainSchedule().end()) {
//                t.getTrainSchedule().erase(it); // Erase the found element
//            }
//            
//            break;
//        }
//    }
//
//}
//
//
////void Line::simulateTrainBreakdown(Train brokenTrain) {
////    for (auto& t : trains) {
////        if (t.getTrainID() == brokenTrain.getTrainID()) {
////            t.setStatus("Breakdown");
////            int newDelay = rand() % 21 + 10;
////           t.getTrainSchedule().setDelay(newDelay);
////            break;
////        }
////      
////    }
////}
//
//size_t Line::findScheduleIndex( Train train, string time,string date) {
//    for (size_t i = 0; i < train.getTrainSchedule().size(); ++i) {
//        if (train.getTrainSchedule()[i].getDate()==date&& train.getTrainSchedule()[i].getDepartureTime()==DateTime::timeInputString(time)) {
//            return i; // Found the schedule with the specified station name
//       
//        }
//    }
//    // Schedule not found, return a value indicating failure (e.g., -1 or train.trainSchedule.size())
//    return std::string::npos; // Using npos to indicate failure
//}
//
//void Line::simulateTrainBreakdown(int brokenTrainID, string time, string date) {
//    for (auto& t : trains) {
//        if (t.getTrainID() == brokenTrainID) {
//            t.setStatus("Breakdown");
//            size_t scheduleIndex = findScheduleIndex(t, time,date);
//            if (scheduleIndex != std::string::npos) {
//                int newDelay = rand() % 26 + 5;//0->25 +5
//                t.getTrainSchedule()[scheduleIndex].setDelay(newDelay);
//                t.adjustNextTripDepartureTime();
//                adjustNextTrainDepartureTime(t);
//                cout << "Train " << brokenTrainID << " broke down!!\n";
//            }
//            else {
//                cout << "Train "<< brokenTrainID <<"has no trips at this \"" << date << "  " << time << "\"." << endl;
//            }
//            break;
//        }
//    }
//}
//
//
//
//
//
//    //void Line::adjustNextTrainDepartureTime() {
//    //    // Check if there is a next train in the deque and if the current train has a positive delay
//    //    if (!trains.empty() && currentTrainIndex + 1 < trains.size() && trains[currentTrainIndex].getDelay() > 0) {
//    //        // Access the next trains in the deque
//    //        for (int i = currentTrainIndex + 1; i; i < trains.size(); i++) {
//    //            Train& nextTrain = trains[i];
//    //            //want to access trip schedule & setDelay()>0
//    //                auto& tripSchedule = nextTrain.getTripInfo((nextTrain.getTrainSchedule()).at(i));
//    //                if (tripSchedule.getDepartureStation() == trains[currentTrainIndex].getTripInfo(trains[currentTrainIndex].getTrainSchedule()).at(i)).getDistinationStation());
//    //                // Adjust the departure time of the next train
//    //                    nextTrain.adjustNextTripDepartureTime();
//    //        }
//    //    }
//    //}
//
//void Line::adjustNextTrainDepartureTime(Train t) {
//   this-> trains;
//    // Check if there is a next train in the deque and if the current train has a positive delay
//    if (!trains.empty() && t.getCurrentTripIndex() + 1 < trains.size() && t.getTrainSchedule().size() > 0 &&
//        t.getTrainSchedule()[0].getDelay() > 0) {
//        // Access the next trains in the deque
//        for (size_t i = t.getCurrentTripIndex()+ 1; i < trains.size(); i++) {
//            Train& nextTrain = trains[i];
//            // Access the trip schedule of the next train
//            auto tripSchedule = nextTrain.getTrainSchedule();
//
//            // Access the current trip schedule
//           // auto currentTripSchedule = trains[currentTrainIndex].getTrainSchedule();
//
//            // Perform any necessary operations on the trip schedule
//            // Example: Check if the departure station of the next train matches some condition
//            if (!tripSchedule.empty() && !t.getTrainSchedule().empty() && tripSchedule.size() == t.getTrainSchedule().size()) {
//                for (int j = 0; j < tripSchedule.size(); ++j) {
//                    if (tripSchedule[j].getDepartureStation() == t.getTrainSchedule()[j].getDestinationStation()) {
//                        // Adjust the departure time of the next train
//                        tripSchedule[j].setDelay(t.getTrainSchedule()[j].getDelay());
//                        nextTrain.adjustNextTripDepartureTime();
//                        cout << "adjustNextTrainDepartureTime--\n";
//                    }
//                }
//            }
//        }
//    }
//    cout << "adjustNextTrainDepartureTime--out\n";
//}



//
//void Line::adjustNextTrainDepartureTime() {
//    // Check if there is a next train in the deque and if the current train has a positive delay
//    if (!trains.empty() && currentTrainIndex + 1 < trains.size() && trains[currentTrainIndex].getTrainSchedule().getDelay() > 0) {
//        // Access the next trains in the deque
//        for (size_t i = currentTrainIndex + 1; i < trains.size(); i++) {
//            auto& currentTripSchedule = trains[currentTrainIndex].getTrainSchedule();
//            Train& nextTrain = trains[i];
//
//            // Access the trip schedule of the next train (assuming it returns a vector of trip info objects)
//            auto& tripSchedule = nextTrain.getTrainSchedule();
//
//            // Perform any necessary operations on the trip schedule
//            // Example: Check if the departure station of the next train matches some condition
//            if (!tripSchedule.empty() && tripSchedule[i].getDepartureStation() == currentTripSchedule[i].getDestinationStation()) {
//                // Adjust the departure time of the next train
//                tripSchedule[i].setDelay(currentTripSchedule[i].getDelay());
//                nextTrain.adjustNextTripDepartureTime();
//            }
//        }
//    }
//}


//void Line::displayTrains() {
//    cout << "Trains in Line:" << endl;
//    for ( auto& train : trains) {
//        train.displayTrainInfo();
//    }
//}
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

