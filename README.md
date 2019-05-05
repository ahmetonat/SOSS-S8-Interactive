# SOSS-S8-Interactive

I had posted [**SOSS-S8: Simple-Open-Source-Servo-S8**](https://aviatorahmet.blogspot.com/2018/12/soss-s8-simple-open-source-servo-stm8s.html); a feedback position controller for DC motors using an incremental encoder for feedback. Its main purpose was education; to provide a platform where anyone can try out digital servo position control very cheaply. It only 

Now, I introduce **SOSS-S8 Interactive**: You can send commands over the serial port, to set: Reference position, reference mode (select between square wave, constant, or analog), and change the PID parameters. It is now much more versatile, and easy to control from an Arduino, for example.

![It looks like this...](https://github.com/ahmetonat/Simple-Open-Source-Servo-S8-SOSS-S8/blob/master/IMG_0923.JPG)

## Command set:
The command set can easily be changed to suit your needs. Currently there are two types of commands.

- Integer commands have the following structure:
**r=4867.**
It starts with a command letter, the equals sign '=', a number in the range (-20000,20000) and completes with a period '.'. No line feed or carriage return are necessary. The following command letters are available:
  - **r=xxx.**  Set position reference in encoder ticks. The motor immediately goes to this reference.
  - **t=xxx.**  Set square wave reference period in ms. This command seths how often the reference value changes. 
  - **m=x.**    Set command mode. 
    - m=0.: Hold constant position. The value is set separately using the **r=xxx.** command. Mode 0 allows you to generate arbitrary position trajectories by the motor under serial port supervision. You can connect several SOSS-S8's to a master processor to build a robot, for example. 
    - m=1.: Square wave reference. The reference value changes between '0' position and the value set by the **r=xxx.** command. The pperiod is set by the **t=xxx.** command.
    - m=2.: Reference is set by the voltage applied to A0, the analog input pin. It will work like a RC servo in this mode.
    
 - Parameter set commands have the following structure:
 **d=12500,4.**
 They start with a command letter and have two arguments separated by a comma; the first argument is a number in the range (-20000,20000) as before and the second argument is a single digit. The arguments form a block floating point number that, for the above example look like this: 12500 x 2^(-4), so it will be computed as 12500 x 0.03125=390.625 The following parameter set commands are available:
    - **p=xxx,e.**  Set proportional gain of PID. (However, currently e is ignored for this command due to laziness... Will fix!)
    - **i=xxx,e.**  Set integral gain of PID.
    - **d=xxx,e.**  Set derivative gain of PID.
    
    The parser is quite flexible, and parses the characters as soon as they arrive (does not accumulate them in a buffer). It will also terminate to the initial state as soon as an unexpected character is received (error). So if one command was in error, the next command should go through smoothly. The parser works with commands sent in rapid succession as well. So you can send them without worrying about putting some separation time between them.
    
It is possible to assign the commands from any serial port. Using the PC, you can use a terminal emulator, the "SerialPlot" program that is detailed in the SOSS-S8 main page, or even Arduino terminal screen. 

You can also send commands from a master microprocessor. This brings out the main power of SOSS-S8 Interactive. You can then build a robot, 3D printer etc. that can follow a pre-set trajectory.

So, go ahead and upgrade to SOSS-S8 Interactive! It is great fun, and backward compatible with SOSS-S8.


