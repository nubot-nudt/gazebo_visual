# Package Summary   

- Maintainer status: maintained
- Maintainer: Weijia Yao <abcgarden@126.com>
- Author: Weijia Yao <abcgarden@126.com>
- License: Apache
- Bug / feature tracker: https://github.com/nubot-nudt/gazebo_visual/issues
- Source: git https://github.com/nubot-nudt/gazebo_visual (branch: master)


# Note: This is for SIMULATION. The following packages should be used together:
1. gazebo_visual                    # for gazebo visulization
2. nubot_ws			                # for real robot code
3. coach4sim		            # for sending game command such as kickoff to robots; this does not require rtdb

# Configuration of computer A and computer B

>   The recommended way to run simulation is with two computers running nubot_ws and gazebo_visual seperately.

> For example,computer A runs gazebo_visual to display the movement of robots. Computer B runs nubot_ws to calculate and send  movement commands to robots. In addition, computer B should also run coach to send game command such as game start. 

>   The communication between computer A and computer B is via ROS master. The following is the configuration steps:
    
1. In computer A, add computer B's IP address in /etc/hosts; and in computer B, add computer A's IP address in /etc/hosts
e.g. In computer A, `$ sudo gedit /etc/hosts and add "Maggie 192.168.8.100"`
     In computer B, `$ sudo gedit /etc/hosts and add "Bart   192.168.8.101"`
2. In computer A, run gazebo_visual; In computer B, before you run nubot_ws, you should export ROS_MASTER_URI.
e.g. In computer B, ` $ export ROS_MASTER_URI=http://Bart:11311`
3. In computer B, run coach and send game command

## Compiling nubot_ws
1. $ sudo chmod +x configure
2. $ ./configure
3. $ catkin_make

## To run nubot_ws   
` $ ./cyan_spawn_model.sh   or   $ ./magenta_spawn_model.sh`   

## To run gazeo_visual
1. ./configure
2. $ roslaunch nubot_gazebo game_ready.launch
You can edit global_config to change simulation parameters such as the number of robots

## To run coach4sim
1. $ roslaunch nubot_coach nubot_coach.launch


> **NOTE:** if used with RTDB, then you should change absolute path in rtdb files:

> 1. rtdb/parser/CMakeLists.txt:

>    (1) SET(RTDB_USER_H_FILE   /home/nubot8/nubot_ws/src/nubot/world_model/include/nubot/rtdb/rtdb_user.h)

>    (2) SET(RTDB_INI_FILE      /home/nubot8/nubot_ws/src/nubot/world_model/config/rtdb.ini )

>    (3) SET(RTDB_Config_FILE   /home/nubot8/nubot_ws/src/nubot/world_model/config/rtdb.config )

> 2. rtdb/rtdb_api.cpp:    
>    std::string ini_config_file="/home/nubot8/nubot_ws/src/nubot/world_model/config/rtdb.ini";
> 3. rtdb/comm.cpp: 'wlano' or 'wlan1'
> 4. coach_info_pub.cpp: DB_get(AGENT), this AGENT depends your coach's agent number
