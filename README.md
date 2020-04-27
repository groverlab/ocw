![OCW logo](ocw.png)

# A really simple language for controlling microfluidic valves.




## Overview

OCW has three main commands that gave the language its name:

* `o`:  Open the specified valve (so `o3` opens valve number 3)

* `c`:  Close the specified valve (so `c5` closes valve number 5)

* `w`:  Wait for the specified amount of time, in milliseconds (so `w1000` waits for one second)

That's all you need to know to write basic OCW programs.  For more advanced stuff, read below for the [OCW syntax]().





## Platforms

This repository contains three different implementations of OCW, each intended for a different platform:

* [arduino](arduino/) contains a new version of OCW that can run on Arduino microcontrollers.

* [labview](labview/) contains a version of OCW implemented in LabVIEW.  It runs on any computer that can run LabVIEW, and uses National Instruments hardware to control microfluidic valves.

* [perl](perl/) contains the original (circa 1999!) implementation of OCW.  This version is written in Perl, runs on Linux, and controls microfluidic valves using parallel ports.  Since parallel ports are getting hard to come by, this version is probably of limited use today.  







## A simple example

To introduce OCW's syntax, here's a simple OCW program:

<pre>
<i>/ I'm a comment!</i>
<b>main</b>
<b>o23</b>
<b>w1000</b>
<b>c23</b>
<b>end</b>
</pre>

The first line, `/ I'm a comment!`, is a comment.  Any line that starts with `/` is ignored by the OCW intrepreter.  Some implementations of OCW (like the LabVIEW implementation) show comment text to the user, so comments can be a handy tool for user interaction, like telling the user to `/ Fill the buffer reservoir` or `/ Empty the waste reservoir`.

The next line, `main`, means that this is the start of the `main` block.  All OCW programs need a `main` block; it tells the OCW interpreter where to begin executing the code.  The contents of the `main` block are all the lines between `main` and `end`.

The next line, `o23`, tells OCW to open valve number 23.  How the OCW interpreter knows which physical valve corresponds to a particular number is implementation-specific; details below.  

The following line, `w1000`, makes the OCW interpreter wait or pause for 1000 milliseconds (or 1 second).  This is how we control the timing and speed of execution of an OCW program.

The next line, `c23`, closes valve number 23.

The last line, `end`, marks the end of the `main` block.  Execution of the OCW program stops here.




## A more complex example

Here's a more complex complex example that defines and calls a custom block named `pump`.  Custom blocks enable the user to define a snippet of OCW code and then execute that code elsewhere in the program.

<pre>
<i>/ This OCW code pumps fluid using three valves as a diaphragm pump.</i>

<i>/ The "main" block calls the "pump" block ten times, then stops:</i>
<b>main</b>
<b>call pump 10</b>
<b>end</b>

<i>/ Here is the definition of the "pump" block.</i>
<i>/ This contains all the valve open/close steps necessary for one pumping cycle,</i>
<i>/ waiting for one second between steps:</i>
<b>pump</b>
<b>o0</b>
<b>w1000</b>
<b>c2</b>
<b>w1000</b>
<b>o1</b>
<b>w1000</b>
<b>c0</b>
<b>w1000</b>
<b>o2</b>
<b>w1000</b>
<b>c1</b>
<end>
</pre>






 on

cn
wt
Available valve numbers are 0 through 8n − 1 where n is the number of parallel ports (Linux only) or digital output ports (LabVIEW only) available on the system. In the Linux version of OCW, valves 0 through 7 are assigned to the first port address set, valves 8 through 15 are assigned to the second port address set, and so on (see the a command below). In the LabVIEW version of OCW, the order of the digital output ports is set in on the front panel of the VI. If the valve is already open, it will remain open.
Close valve n.
Available valve numbers are the same as for the o command. If the valve is
already closed, it will remain closed.
Wait t milliseconds.
The accuracy of the wait command is system-dependent; extremely short waits (< 100 ms) may be inaccurate.
stop
main
end
225
If the forward-slash / is placed at the beginning of a line, all remaining text on that line is ignored. In addition, comments within executed functions (either main or a subroutine) are printed on the screen during execution. Comments placed before a stop command can therefore be used to tell the operator what to do during that stop, e.g. “/Add more buffer”.
Stop program execution for operator intervention.
Execution stops until the operator presses ENTER (Linux only) or clicks Resume (LabVIEW only).
Begin main function.
Every OCW program must have a main function. The main function cannot be repeated arbitrarily like subroutines can. Instead, place the contents of the main function in a subroutine and call that subroutine from main using repeats (see call below).
End main program or a subroutine.
The main function and each subroutine are terminated by end commands. The code lying between main and the main function’s end is the main function; code between the declaration of a subroutine (see below) and that subroutine’s end is that subroutine’s code.
/comment Comment line.

sfname Begin definition of the subroutine named sfname.
Any line containing a single word that isn’t another OCW function is assumed to be the declaration of a subroutine. The name of the subroutine marks the beginning of the subroutine’s code, and the corresponding end command marks the end of the code. Underscores can be included in the subroutine names for legibility, as in pump forward.
call sfname n Call subroutine sfname n times, once if n is omitted.
When a subroutine is called, its code is executed as if the subroutine’s code was actually inserted in the program at the call command. Adding an inte- ger number n after the function name in the call command will repeat that subroutine’s code n times; if the number is omitted the code is executed once. By specifying a excessively large number of repeats and pressing ENTER (Linux only) or clicking Escape (LabVIEW only) at runtime to escape the repeating subroutine, the number of repeats executed can be controlled at runtime by the operator (see below).
include filename.ocw Includecontentsoffilefilename.ocw(LabVIEWonly).
The include command allows a complex OCW program to span multiple source files. The contents of an included file are executed when the include state- ment is encountered, as if they were part of the current file. Commonly-used subroutines like pump forward or close all valves can be defined once in a sin-
226

an
227
gle, shared file and included into other files without having to redefining them, making the resulting OCW scripts much shorter and easier to understand.
Set next parallel port address to n (Linux only).
The a command is called as many times as there are parallel ports to be used on the computer. The order in which the ports are called is used to determine which set of 8 valves is assigned to which parallel port. The first parallel port address set using a will control valves 0 through 7, the second port address set with a will control valves 8 through 15, and so on. The port address is set using the decimal equivalent of the (usually hexidecimal) parallel port address, as shown in Table A.2.
Port address (hexidecimal)
         0x3BC
         0x378
         0x278
         0x368
         0x268
         0x358
         0x258
OCW code (decimal)
a956 a888 a632 a872 a616 a856 a600
 Table A.2: Common hexidecimal parallel port addresses and corresponding decimal OCW a commands.
armed Activate parallel ports (Linux only).
Without an armed command in the beginning of the file, the OCW code will execute but will not actually control the parallel ports (“debug mode”). Include the armed command to actually control the parallel ports.

negate Negate parallel port logic (Linux only).
The OCW interpreter ordinarily assumes that opening a valve corresponds to energizing a solenoid valve (sending out a “high” voltage from the parallel port) and closing a valve corresponds to de-energizing a solenoid valve (sending out a “low” voltage). Depending on the type of solenoid valve used and the construc- tion of the pneumatic control system, this assumption may need to be reversed. If the negate command is included in the beginning of an OCW file, the de- energized state of the solenoid valve will correspond to an open valve and the energized state will correspond to a closed valve.
Finally, a few commands may be typed or clicked while the OCW program is running. These commands affect the execution of the OCW program being run:
ENTER Resume ENTER Escape Pause
Resume execution following a stop command (Linux only). Resume execution following a stop command (LabVIEW only). Escape the current repeating subroutine (Linux only).
Escape the current repeating subroutine (LabVIEW only). Pause program execution (LabVIEW only).