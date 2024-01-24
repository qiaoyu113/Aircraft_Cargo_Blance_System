# Aircraft Cargo auto Blance System

<p align="center">
<svg style="width:12px;height:12px;" t="1706099735946" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg" p-id="19568" width="200" height="200"><path d="M905.386667 226.133333L562.517333 28.842667c-31.744-18.773333-71.68-18.773333-102.912 0L117.589333 226.133333c-31.744 18.773333-51.882667 52.394667-51.882666 89.770667v395.434667c0 36.864 19.626667 70.485333 51.882666 89.770666L459.434667 998.4c15.701333 9.045333 33.28 13.653333 51.882666 13.653333 18.090667 0 35.84-5.12 51.882667-13.653333l342.357333-197.290667c31.744-18.773333 51.882667-52.394667 51.882667-89.770666V315.733333c-1.024-36.693333-20.821333-71.509333-52.053333-89.6z m-12.117334 484.010667c0 14.677333-7.509333 27.136-20.138666 34.816L531.114667 942.592c-12.117333 6.997333-27.136 6.997333-40.448 0L148.821333 744.96c-12.117333-6.997333-19.626667-20.138667-19.626666-34.816V315.733333c0-14.677333 7.509333-27.136 19.626666-34.816L491.349333 83.285333c5.973333-3.584 12.970667-5.461333 19.626667-5.461333 6.997333 0 13.653333 1.536 19.626667 5.461333l342.357333 197.290667c12.117333 6.997333 19.626667 20.138667 19.626667 34.816v394.410667l0.682666 0.341333z" fill="#1296db" p-id="19569"></path><path d="M469.411919 737.437712a25.6 39.936 31.185 1 0 41.357966-68.330484 25.6 39.936 31.185 1 0-41.357966 68.330484Z" fill="#1296db" p-id="19570"></path><path d="M609.949482 664.238808a25.6 39.936 31.185 1 0 41.357966-68.330484 25.6 39.936 31.185 1 0-41.357966 68.330484Z" fill="#1296db" p-id="19571"></path><path d="M733.489691 596.07907a25.6 39.936 31.185 1 0 41.357966-68.330484 25.6 39.936 31.185 1 0-41.357966 68.330484Z" fill="#1296db" p-id="19572"></path><path d="M646.144 241.152l-1.194667 0.512 1.194667-0.512-232.96 141.994667v117.76l-61.610667-39.253334v-112.981333l232.106667-141.824 0.853333-0.512-13.141333-7.338667-62.464-35.328-228.864 136.362667v207.36l206.165333 128 225.962667-132.266667V278.528z" fill="#1296db" p-id="19573"></path><path d="M712.362667 419.84v26.112l111.274666 61.44v90.453333L475.989333 788.309333c-10.24 5.632-22.698667 5.290667-32.597333-0.853333l-229.717333-140.288c-12.970667-7.850667-18.773333-23.893333-13.824-37.888 10.069333-28.672 32.256-50.858667 51.370666-65.536v-28.16c-23.381333 15.530667-58.368 44.544-73.045333 86.016-8.533333 24.234667 1.365333 51.541333 23.552 65.024l229.717333 140.288c8.874667 5.461333 18.773333 8.021333 28.842667 8.021333 9.216 0 18.261333-2.218667 26.624-6.826666L846.506667 611.498667v-117.589334L712.362667 419.84z" fill="#1296db" p-id="19574"></path><path d="M558.762667 192l110.592 62.122667-34.304 8.362666-122.197334-64.682666 25.088-4.437334z" fill="#1296db" p-id="19575"></path></svg>
  🇬🇧 <a href="README.md">English</a>
  &nbsp;
  🇨🇳 <a href="README.zh_CN.md">Chinese</a>
</p>

## Project Introduction
Aircraft Cargo Balance System is an open-source system designed for managing aircraft cargo balance. This system aims to assist airlines and cargo operators in efficiently planning and managing the distribution of cargo on airplanes, ensuring a proper balance during flights to enhance flight safety and fuel efficiency.

## Project Members

| Name      | Email                                   | Contribution                                       | GitHub                              |
| --------- | --------------------------------------- | -------------------------------------------------- | ----------------------------------- |
| Yu Qiao | [Email](mailto:qy0803@yeah.net)        | Brief description of the main contribution by Qiao Yu | [GitHubUsername1](GitHubLink1)    |
| Yuhang Liu | [Email](mailto:yuhanliu123@outlook.com) | Brief description of the main contribution by Liu Yuhang | [GitHubUsername2](GitHubLink2)    |
| Yiling Deng | [Email](mailto:2840572D@student.gla.ac.uk) | Brief description of the main contribution by Deng Yiling | [GitHubUsername3](GitHubLink3)    |
| Chanzhang He | [Email](mailto:2949931H@student.gla.ac.uk) | Brief description of the main contribution by He Chanzhang | [GitHubUsername4](GitHubLink4)    |


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