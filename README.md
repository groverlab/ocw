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

The first line, `/ I'm a comment!`, is a comment.  Any line that starts with `/` is ignored by the OCW interpreter.  Some implementations of OCW (like the LabVIEW implementation) show comment text to the user, so comments can be a handy tool for user interaction, like telling the user to `/ Fill the buffer reservoir` or `/ Empty the waste reservoir`.

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
<end></pre>

As in the previous example, we see the mandatory `main` block defined by `main` and `end`.  This main block contains a single line, `call pump 10`.  This code tells the OCW interpreter to look for the custom block named `pump` elsewhere in the file and run its contents 10 times.  The number of repeats is optional; if it is omitted (as in `call pump`) then the named block will be run just once.

The remainder of the code is the definition of the `pump` custom block.  The definition begins with just the name of the custom block on a line by itself (that's the line that says `pump`) and ends with `end`, just as the `main` block ends with `end`.  

Inside the definition of the `pump` block we find instructions for opening and closing three microfluidic valves in a peristaltic pumping pattern (see [this paper]() for more details).  Interspersed between the `o` and `c` commands are `w` (wait) commands that dictate the timing of this code.  With six `w` commands in the `pump` block, each of which waits for 1000 milliseconds or 1 second, the whole `pump` block will take 6 seconds to execute.  Since the `main` block repeats the `pump` block 10 times, this whole OCW program will take 60 seconds or 1 minute to execute.




## OCW syntax reference

* `o`:  Open the specified valve (for example, `o3` opens valve number 3).  If the valve is already open, it stays open.  There are differences between how the different OCW implementations associate a physical valve with a particular valve number:
** Arduino implementation:  FIXME
** LabVIEW implementation:  The physical hardware associated with each valve number is assigned in *listener.vi*.
** Perl/Linux implementation:  Valves 0 through 7 are assigned to the first parallel port address set by the `a` command (described below), valves 8 through 15 are assigned to the second port address set, and so on.

* `c`:  Close the specified valve (for example `c5` closes valve number 5).  If the valve is already closed, it stays closed.  Also see the implementation-specific notes under `o` above.

* `w`:  Wait for the specified amount of time, in milliseconds (so `w1000` waits for one second).  To wait "forever" (until the program is stopped, or until a user interacts with the program), once can simply wait for a very long time, like `w999999999999999`.  The accuracy of the `w` command is system-dependent and isn't guaranteed; for applications that require precise timing info, the user should verify that the requested wait times are accurate.

* `\`:  Comment.  Any line that starts with `\`, like `\Hello world`, is ignored by the OCW interpreter.  Also, some OCW implementations show the comment text to the user during operation:
** LabVIEW implementation:  The comment text is shown to the user on the front panel of *manual.vi*.
** Perl/Linux implementation:  The comment text is shown to the user on the command line.
** Arduino implementation:  Currently comment text is ignored because user interaction is highly implementation specific on the Arduino platform, but adding support for e.g. printing a comment to an LCD screen should be relatively straightforward.


* `main`:  Start of the declaration of the `main` block.  Every OCW program needs a `main` block; it's where execution starts.

* `end`:  End of the current block (either `main` or a custom block).

* *block_name*:  A single word that isn't one of OCW's other commands is treated as the beginning of the declaration of a custom block by that name.  So for example the code
```
closeItAll
c0
c1
c2
end
```
defines 




 


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