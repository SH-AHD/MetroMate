# MetroMate: Metro System Simulation

![Contributors](https://img.shields.io/badge/Contributors-6-orange.svg)  

**MetroMate** is a console-based application designed to simulate a metro system. It allows users to manage their rides and subscriptions, while admins can manage trains, handle scheduling, and monitor system performance. This project provides a simplified model of a real-world metro system, focusing on subscription management, fare calculation, and ride tracking through a text-based interface.

---

## Table of Contents
1. [Overview](#overview)
2. [Features](#features)
3. [Metro Stages and Subscription Plans](#metro-stages-and-subscription-plans)
4. [Deliverables](#deliverables)
   - [User Functionalities](#user-functionalities)
   - [Admin Functionalities](#admin-functionalities)
5. [Development Tools](#development-tools)
6. [Bonus Opportunities](#bonus-opportunities)

---

## Overview

MetroMate is a simulation of a metro system that allows users to:
- Create and manage accounts.
- Purchase and manage subscriptions.
- Simulate ride check-ins and check-outs.
- View ride history and update personal information.

Admins can:
- Manage users, metro stations, and subscription plans.
- Monitor ride logs and station data.
- Adjust fare rates and manage trains.

This project is designed to demonstrate the effective use of data structures and clean coding practices.

---

## Features

- **User Management**: Register, log in, and manage personal information.
- **Subscription Plans**: Purchase and manage Student, Public, and Wallet subscriptions.
- **Ride Simulation**: Check-in and check-out for rides, with fare calculation based on metro stages.
- **Admin Controls**: Manage users, stations, subscription plans, and fare rates.
- **Data Persistence**: Load and save data to files for persistence.

---

## Metro Stages and Subscription Plans

### Metro Stages
- **Stage 1**: 6 LE (1 to 9 stations).
- **Stage 2**: 8 LE (10 to 16 stations).
- **Stage 3**: 12 LE (17 to 23 stations).
- **Stage 4**: 15 LE (more than 23 stations).

### Subscription Plans
1. **Student Cards**:
   - Fixed amount every 3 months for 180 trips.
   - Example: 33 LE (Stage 1), 41 LE (Stage 2), 50 LE (Stage 3), 65 LE (Stage 4).

2. **Public Cards**:
   - Monthly or yearly plans for 60 or 730 trips.
   - Example (Monthly): 230 LE (Stage 1), 290 LE (Stage 2), 340 LE (Stage 3), 450 LE (Stage 4).
   - Example (Yearly): 1500 LE (Stage 1), 2500 LE (Stage 2), 3500 LE (Stage 3), 4500 LE (Stage 4).

3. **Cash Wallet Cards**:
   - Pay in multiples of 10 LE anytime.
   - Card limit: 400 LE.
   - No time restrictions; charges based on metro stages.

---

## Deliverables

### User Functionalities
1. **Register/Sign Up**: Create a new account.
2. **Log In/Log Out**: Securely access and exit the account.
3. **Purchase Subscription**: Buy a subscription plan.
4. **Manage Subscription**: View, renew, or upgrade plans.
5. **Check-In/Check-Out**: Simulate rides and calculate fares using the shortest path algorithm.
6. **View Ride History**: Access logs of past rides.
7. **Update Personal Information**: Modify name, password, and contact details.

### Admin Functionalities
1. **User Management**: View, edit, and delete user accounts.
2. **Metro Management**: Add, edit, or remove metro stations and lines.
3. **Subscription Plan Management**: Create, modify, or remove subscription plans.
4. **View Ride Logs**: Access comprehensive ride logs across all users.
5. **Station Management**: Monitor station data (e.g., tickets sold, income, passenger count).
6. **Fare Management**: Adjust fare rates for metro stages.

---

## Development Tools

- **Programming Language**: C++.
- **Data Structures**: Different data structures (e.g., arrays, linked lists, graphs, queues, stacks).
- **File Handling**: Use file streams for data persistence.
- **Libraries**: Standard Template Library (STL).

---

## Bonus Opportunities

- **Zone-Based Subscriptions**: Replace stage-based subscriptions with zone-based ones.
- **Train Management**: Add, edit, or remove trains; handle breakdowns and provide ETA.
