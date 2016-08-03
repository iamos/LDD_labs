/*lab4: Multiple Periodic Kernel Timers
	Write a module that launches two periodic kernel timer functions; i.e., they shuld re-install themselves.
	One periodic sequence shuld be for less than 256 ticks (so it falls in the tv1 vector), and the other
	should be for less than 16 K ticks (so it falls in the tv2 vector.)

	Each time the timer functions execute, print out the elapsed time since the module was laded (in jiffies.)

	For one of the functions, also read the TSC and calibrate with the CPU frequency
	(as read from /proc/cpuinfo or the zpu_khz variable) to print out the elapsed time (hopefully) more accurately.
*/