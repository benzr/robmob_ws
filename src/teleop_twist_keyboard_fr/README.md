# teleop_twist_keyboard
Generic Keyboard Teleop for ROS
adapted to French keyboard layout.
4 arrows added (^ forward, < turn left, > turn right , v backward)

# Launch
Run.
```
rosrun teleop_twist_keyboard_fr teleop_twist_keyboard_fr.py
```

With custom values.
```
rosrun teleop_twist_keyboard_fr teleop_twist_keyboard_fr.py _speed:=0.9 _turn:=0.8
```

Publishing to a different topic (in this case `my_cmd_vel`).
```
rosrun teleop_twist_keyboard_fr teleop_twist_keyboard_fr.py cmd_vel:=my_cmd_vel
```

# Usage
```
Reading from the keyboard  and Publishing to Twist!
---------------------------
Cursor arrows moving
         up
   left     right
        down 

---------------------------
Moving around:
   u    i    o
   j    k    l
   m    ,    .

For Holonomic mode (strafing), hold down the shift key:
---------------------------
   U    I    O
   J    K    L
   M    <    >

t : up (+z)
b : down (-z)

anything else : stop

q/z : increase/decrease max speeds by 10%
w/x : increase/decrease only linear speed by 10%
e/c : increase/decrease only angular speed by 10%

CTRL-C to quit
```

