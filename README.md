# Aircraft_Cargo_Blance_System

- en [English](README.md)
- zh_CN [简体中文](readme/README.zh_CN.md)

<p align="center">
  🇬🇧 <a href="README.zh_CN.md">English</a>
  &nbsp;
  🇨🇳 <a href="readme/README.zh_CN.md">Chinese</a>
</p>

## Project Introduction
Aircraft Cargo Balance System is an open-source system designed for managing aircraft cargo balance. This system aims to assist airlines and cargo operators in efficiently planning and managing the distribution of cargo on airplanes, ensuring a proper balance during flights to enhance flight safety and fuel efficiency.

## Key Features
1. **Cargo Management:** Provides an intuitive interface for users to easily add, remove, and edit cargo information on the airplane.
2. **Balance Calculation:** Based on the aircraft model and cargo distribution, calculates the aircraft's center of gravity and balance conditions, ensuring a reasonable balance at various flight stages.
3. **Report Generation:** Generates detailed balance reports, including center of gravity charts, load charts, etc., for reference by pilots and ground personnel.

## Technical Architecture
1. **Raspberry Pi**
   - **Sensor Interface:** Connects sensors through GPIO interfaces to real-time retrieve cargo weight data.
   - **Data Processing:** Uses Python for data processing, calculating balance conditions and generating weight heatmaps.
   - **Local Area Network Server:** Implements a server using Flask or FastAPI to provide APIs for access by STM32 and the web frontend.

2. **STM32 Microcontroller**
   - **Connection to Raspberry Pi:** Communicates with the Raspberry Pi through serial communication or other protocols to receive balance commands.
   - **Conveyor Control:** Controls the conveyor belt motor to achieve real-time balance adjustments.
   - **Sensor Interface:** Connects to cargo sensors to obtain real-time cargo position information.

3. **Web Frontend**
   - **Frontend Interface:** Built with Vue to create a user-friendly interface displaying real-time cargo balance status and weight heatmaps.
   - **Communication with Raspberry Pi:** Uses WebSocket or HTTP polling to fetch real-time data from the Raspberry Pi.
   - **User Control:** Enables users to send control commands through the interface to adjust the conveyor belt position and view real-time data.

## Project Framework and Structure
```
Aircraft_Cargo_Balance_System/
|-- backend/                  
|   |-- app/                  
|   |   |-- __init__.py
|   |   |-- routes.py         
|   |   |-- controllers/      
|   |       |-- __init__.py
|   |       |-- balance_controller.py   
|   |-- config/               
|   |   |-- config.py         
|   |-- models/               
|   |   |-- __init__.py
|   |   |-- cargo_model.py    
|   |   |-- balance_model.py  
|   |-- utils/                
|       |-- __init__.py
|       |-- calculations.py   
|-- frontend/                 
|   |-- public/
|   |-- src/
|   |   |-- components/       
|   |   |   |-- BalanceChart.js    
|   |   |   |-- ControlPanel.js   
|   |   |-- pages/            
|   |   |   |-- Dashboard.js      
|   |   |-- services/         
|   |   |   |-- api.js         
|   |   |-- App.js            
|   |   |-- index.js          
|-- stm32/                    
|   |-- src/                  
|   |   |-- main.c            
|   |   |-- communication.c   
|   |   |-- conveyor.c        
|-- README.md                 
|-- LICENSE                   
```