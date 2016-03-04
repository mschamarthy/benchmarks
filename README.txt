README.txt
====================

This Implementation of the benchmarking measures CPU, Memory and Disk performance of a system. The benchmarking suite is implemented in C and includes bash scripts to handle the program builds.

====================
Project Structure:

src
|
|--cpu\
|--disk\
|--lib\
|--memory\
|--scripts\
|--reports\ (Created after the first build)
|--benchmarking.sh

====================
First Time Usage:

- The entire benchmarking suite must be build by running the "benchmark.sh" script.
- run "benchmark.sh" script by running the following in the terminal of the target machine.
	"sh benchmark.sh"
- This checks and installs all the prerequisite software in the target system.
- Next, builds all of the benchmarking programs and run those programs for some common parameter spaces.
- After the first run of the benchmark.sh script, a "report" folder is created that contains the CPU, Memory and Disk benchmarking reports.

====================
CPU Benchmarking Usage:

- After running the First Time Usage instructions, we can run just the CPU benchmarking with parameter by running the following command

	"./cpu/cpu <no. of Threads>"
	
	no_of_threads		: 1, 2, 3, 4

- For example, in order to run CPU benchmarking using 2 threads, use
	"./cpu/cpu 2"

- The resulting GFLOPS & GIOPS is displayed on the terminal.

====================
Memory Benchmarking Usage:

- After running the First Time Usage instructions, we can run just the Memory benchmarking with parameter by running the following command

	"./memory/memory <no_of_threads> <block_size> <seq_or_random>"

	no_of_threads		: 1, 2, 3, 4
	block_size		: 0 = 1B, 1 = 1KB, 2 = 1MB
	seq_or_random		: 0 = Seqential, 1 = Random

- For example, in order to run Memory benchmarking using 2 threads, 1KB block size and random access, use
	"./memory/memory 2 1 1"

- The resulting Throughput and Latency is displayed on the terminal.

====================
Disk Benchmarking Usage:

- After running the First Time Usage instructions, we can run just the Disk benchmarking with parameter by running the following command

	"./disk/disk <read_write> <no_of_threads> <block_size> <seq_or_random>"

	read_write		: 0 = read, 1 = write
	no_of_threads		: 1, 2, 3, 4
	block_size		: 0 = 1B, 1 = 1KB, 2 = 1MB
	seq_or_random		: 0 = Seqential, 1 = Random

- For example, in order to run Disk read benchmarking using 2 threads, 1KB block size and random access, use
	"./disk/disk 0 2 1 1"

- For example, in order to run Disk write benchmarking using 2 threads, 1KB block size and random access, use
	"./disk/disk 1 2 1 1"

- The resulting Throughput and Latency is displayed on the terminal.
