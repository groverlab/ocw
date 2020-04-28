![OCW logo](ocw.png)

# A really simple language for controlling microfluidic valves.




## Overview

OCW has three main commands that gave the language its name:

* `o`:  Open the specified valve (so `o3` opens valve number 3)

* `c`:  Close the specified valve (so `c5` closes valve number 5)

* `w`:  Wait for the specified amount of time, in milliseconds (so `w1000` waits for one second)

That's all you need to know to write basic OCW programs.  For more advanced stuff, read below for the [OCW syntax]().





## Implementations 

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
    * Arduino implementation:  FIXME
    * LabVIEW implementation:  The physical hardware associated with each valve number is assigned in *listener.vi*.
    * Perl/Linux implementation:  Valves 0 through 7 are assigned to the first parallel port address set by the `a` command (described below), valves 8 through 15 are assigned to the second port address set, and so on.

* `c`:  Close the specified valve (for example `c5` closes valve number 5).  If the valve is already closed, it stays closed.  Also see the implementation-specific notes under `o` above.

* `w`:  Wait for the specified amount of time, in milliseconds (so `w1000` waits for one second).  To wait "forever" (until the program is stopped, or until a user interacts with the program), once can simply wait for a very long time, like `w999999999999999`.  The accuracy of the `w` command is system-dependent and isn't guaranteed; for applications that require precise timing info, the user should verify that the requested wait times are accurate.

* `\`:  Comment.  Any line that starts with `\`, like `\Hello world`, is ignored by the OCW interpreter.  Also, some OCW implementations show the comment text to the user during operation:
    * LabVIEW implementation:  The comment text is shown to the user on the front panel of *ocw.vi*.
    * Perl/Linux implementation:  The comment text is shown to the user on the command line.
    * Arduino implementation:  Currently comment text is ignored because user interaction is highly implementation specific on the Arduino platform, but adding support for e.g. printing a comment to an LCD screen should be relatively straightforward.

* `stop` stops the execution of the OCW program until the user intervenes.  The specific intervention required is implementation-specific:
    * LabVIEW implementation:  Execution stops until the user presses *Resume* on the front panel of *ocw.vi*.
    * Perl/Linux implementation:  Execution stops until the user presses Enter/Return on the keyboard.
    * Arduino implementation:  Currently `stop` is not supported on the Arduino.

* `main`:  Start of the declaration of the `main` block.  Every OCW program needs a `main` block; it's where execution starts.

* `end`:  End of the current block (either `main` or a custom block).

* *block_name*:  A single word that isn't one of OCW's other commands is treated as the beginning of the declaration of a custom block by that name.  So for example `closeAllValves` and `shut_down` and `call-for-help` are all valid beginnings custom block declarations.  `end` ends the current block declaration.

* `call`:  Call (execute) a block defined elsewhere in the OCW program.  For example, `call closeAllValves` executes the code inside the custom block named `closeAllValves` defined elsewhere.  An optional numerical argument tells OCW how many times to execute the block's contents.  For example, `call pump_forward 100` executes the code inside the `pump_forward` custom block 100 times.  To keep repeating the block "forever," one can call it using a large number of repeats, like `call pump_forward 99999999999`.  To exit a repeated `call` early (before all of the repeats have been executed), the user can perform one of these implementation-specific operations:
    * LabVIEW implementation:  Escape a repeating `call` command early by clicking *Escape* on the front panel of *ocw.vi*.
    * Perl/Linux implementation:  Escape a repeating `call` command early by pressing Enter/Return on the keyboard.
    * Arduino implementation:  Currently escaping from a repeating `call` command early is not supported on the Arduino.
 
* `include`:  Include the contents of a separate OCW file, as if they were part of the current file.  For example, the command `include otherFile.ocw` opens the file named `otherFile.ocw` in the same directory as the current file, reads its contents, and operates on its contents as if they were inserted into the current file at the location of the `include` command.  *Supported only in the LabVIEW implementation of OCW.*

* `a`:  Specify which parallel port is used to control which set of eight valves *(used only in the Perl/Linux implementation of OCW)*.  For example, `a956` specifies that valves 0 through 7 will use the parallel port with the hardware address 956 in decimal or 0x3BC in hexadecimal.  The a command is called as many times as there are parallel ports to be used on the computer. The order in which the ports are called is used to determine which set of 8 valves is assigned to which parallel port. The first parallel port address set using a will control valves 0 through 7, the second port address set with a will control valves 8 through 15, and so on. The port address is set using the decimal equivalent of the (usually hexidecimal) parallel port address.  Some typical hexadecimal parallel port addresses and their decimal equivalents are:

    | Port address (hexidecimal) | OCW address-setting code (decimal) |
    | -------------------------- | -----------------------------------|
    |         0x3BC   |   a956   |
    |         0x378   |   a888   |
    |         0x278   |   a632   |
    |         0x368   |   a872   |
    |         0x268   |   a616   |
    |         0x358   |   a856   |
    |         0x258   |   a600   |  

* `armed`:  Without an armed command in the beginning of the file, the OCW code will execute but will not actually control the parallel ports (“debug mode”). Include the armed command to actually control the parallel ports.

* `negate`  Negate parallel port logic (Linux only).
The OCW interpreter ordinarily assumes that opening a valve corresponds to energizing a solenoid valve (sending out a “high” voltage from the parallel port) and closing a valve corresponds to de-energizing a solenoid valve (sending out a “low” voltage). Depending on the type of solenoid valve used and the construction of the pneumatic control system, this assumption may need to be reversed. If the negate command is included in the beginning of an OCW file, the de-energized state of the solenoid valve will correspond to an open valve and the energized state will correspond to a closed valve.

