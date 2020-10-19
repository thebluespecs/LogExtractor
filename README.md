# Log Extractor
A log extractor built as a part of interview assignent for MCQDB LLC.
## Implementation
### Algorithm
1. Iterate through the directory contents or the logfiles
2. Load every file in the virtual memory because file size could overload a buffer or ram memory in some cases.
3. There are two cases in which required logs can occur : \
    A. Same file : check if the start time and end time lie between the first log and last log of the file.\
    B. Span over multiples files : starting at the start time lying in file, keep track of the files till the end time occurs in one. The array is the required files.

### BottleNeck
The major bottle neck is reading the file into the physical memory. but that can be solved if creating memory maps of files or reading the large file buffer by buffer.\

Some benchmarks of major methods are given below. These were recorded on files with size greator than 4G.\
method	 millions of int. per/s \
C read	         70\
C fread	        124\
C++ ifstream	  124\
mmap	          125


### Logging
The program uses a header-only libray called "speedlog" for synchronised multithreaded logging.
https://github.com/gabime/spdlog

### Improvement
The program currently makes use of the ifstream making dynamic buffers on read on huge files. we can use memory mapping. Instead of reading blocks of data, we map the content of the file to a pointer and the operating system is responsible with filling in the data. It has the reputation to be very fast because the data on disk can be mapped directly to memory without any undue copying. However, in my experience, it is also less stable: we are unlikely to cause a bus error with fread or ifstream, but the slightest mistake with memory mapping and program can crash.\ 
Synchronous multithreading can also make the program faster, as threads can read batches of data. This would make the current program a multithreaded read instead of the single one right now.

## Execution Information

There are no dependent libraries that are statically linked. but the program requires a compiler with c++17 standards.

**BUIDLING**
  1. `mkdir build && cd build`
  2. `cmake ..`
  3. `make`

**RUN** \
`./LogExtractor -f 2020-10-14T16:39:43.394Z{startTime} -t 2020-10-14T16:39:43.395Z{endTime} -i ../logs{logDirectory}`
