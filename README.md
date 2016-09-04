# Package Summary   

- Maintainer status: maintained
- Maintainer: Weijia Yao <abcgarden@126.com>
- Author: Weijia Yao <abcgarden@126.com>
- License: Apache
- Bug / feature tracker: https://github.com/nubot-nudt/gazebo_visual/issues
- Source: git https://github.com/nubot-nudt/gazebo_visual (branch: master)


# Note: This is for SIMULATION. The following packages should be used together:
package|description|
:------|:----------|
[gazebo_visual](https://github.com/nubot-nudt/gazebo_visual) | For gazebo visulization |
[nubot_ws](https://github.com/nubot-nudt/nubot_ws)  | For real robot code |
[coach4sim](https://github.com/nubot-nudt/coach4sim)	| For sending game command such as kickoff to robots; this does not require rtdb |

**Note**   
If you want to use coach4sim, you need to install Qt. For those who don't want to install Qt, a solution is using command line to send game commands as follows:    
In another terminal, input the following to send a game command:   
```    
rostopic pub -r 1 /nubot/receive_from_coach  nubot_common/CoachInfo "
MatchMode: 10
MatchType: 0" 
```   
  Indeed, when you input until nubot_common/CoachInfo, you could press 'Tab' twice and then the whole definition of the message would show up. Then you could fill up the message. However, you only need to fill in two fields: 'MatchMode' and 'MatchType', where 'MatchMode' is the current game command, 'MatchType' is the previous game command. The coding of the game commands is in core.hpp. For quick reference:   
```   
enum MatchMode {
                  STOPROBOT  =  0,
                  OUR_KICKOFF = 1,
                  OPP_KICKOFF = 2,
                  OUR_THROWIN = 3,
                  OPP_THROWIN = 4,
                  OUR_PENALTY = 5,
                  OPP_PENALTY = 6,
                  OUR_GOALKICK = 7 ,
                  OPP_GOALKICK = 8,
                  OUR_CORNERKICK = 9,
                  OPP_CORNERKICK = 10,
                  OUR_FREEKICK = 11,
                  OPP_FREEKICK = 12,
                  DROPBALL     = 13,
                  STARTROBOT   = 15,
                  PARKINGROBOT = 25,
                  TEST = 27
                };
```   

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

## To run gazeo_visual
1. `./configure `   
2. `$ source devel/setup.bash`   
2. `$ roslaunch nubot_gazebo game_ready.launch`   	
You can edit global_config to change simulation parameters such as the number of robots   

## To run nubot_ws   
` $ ./src/cyan_spawn_model.sh`      
or   
` $ ./src/magenta_spawn_model.sh`    

## To run coach4sim
1. `$ source devel/setup.bash`   
2. ` $ roslaunch nubot_coach cyan_sim.launch`   
or    
` $ roslaunch nubot_coach magenta_sim.launch`   



