# LGTCPTester
This is a small C++ command prompt program, to display and can log output signals from arcade game emulators, gamming tool programs, or the game program itself. It connects to the TCP Socket on localhost (IP 127.0.0.1), on port 8000, which is the standard network connection used on most, if not all, arcade game programs. 

## Debug

Main purpose for this program is for debugging problems with Hook Of The Reaper. Many times a program will hook into Hook Of The Reaper, and then it will not send Output Signals, or certain Output Signal, during the game. Every time this has happen in the past, it is do to the person not setting up the game or emulator correctly. Since it hooked into Hook Of The Reaper, the person wrongly assumes it's a problem with Hook Of The Reaper. Because of this, I now ask people to verify the Output Signals during the game. It was not the easiest thing to do, as there were only 2 methods. The first is to lower the display refresh of Hook Of The Reaper, and try to see the Output Signals toggling. Easy for 'Rumble', but not for 'Recoil'. Second method was to use a program called 'putty'. This would only display the last Output Signal that was changed though.

To fix this, I created this tool. Now a person can run everything, even with Hook Of The Reaper now. A person can run the program before anything. Also, log the Output Signals to a log. Once running, the person can run the game set-up. The person can play the game normally, and make sure to get hit, so that the 'Rumble' Output Signal is active. Then can close the game, and then CNTRL-C on the command prompt, to make the LGTCPTester program stop running. Then the display, or the log, can be viewed and attach to 'Issuses' for Hook Of The Reaper. If the 'Recoil' & 'Rumble' Output Signals are not toggling during the game, then Hook Of The Reaper will not do anything, and is not at fault. The person has to figure out themselfs, what they did wrong. All the times in the past, the game or emulator was set-up incorrectly.

If the Output Signals are toggling during the game, then it could be a bug for Hook Of The Reaper. It depends if the game file is set-up correctly, or not. As Hook Of The Reaper loads the game file, to know what Output Signals to observre, and do actions for. If the game file is not correct, and then needs to be updated. If the game file is correct, then it might be a bug with Hook Of The Reaper. 

## Run Program

Display Output Signals
> .\LGTCPTester.exe 

Display & Log Output Signals to 'log.txt'
> .\LGTCPTester.exe -l

Display & Log Output Signals to Certain Log File
> .\LGTCPTester.exe -n nameOfLogFile.txt

Version & Help Info
> .\LGTCPTester.exe -h

