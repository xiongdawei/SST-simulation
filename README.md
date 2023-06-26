# SST-simulation
Simulation for RACERSim for summer research

How to Install SST on your macbook. 

## Some problems
The detail step for how to download SST on mac is given in this link. However, you may encounter several problems during installment so I'll write down a few problems that I've met.
http://sst-simulator.org/SSTPages/SSTBuildAndInstall_13dot0dot0_SeriesDetailedBuildInstructions/

### Problem 1
make all & make install usually take a long time especially for sst-elements-library. Remember to use
```
make -j all & make -j install to utilize all the cores on your computer to facilitate this process.
```
### Problem 2
It would be better if you have MPI installed otherwise you have to disable it in the 
```
./configure
```
configuration stage. During installation stage of open-mpi, I've encountered prblem like this. You have to get those library ready. You can reference the dependency graph in this link. 
https://docs.open-mpi.org/en/v5.0.x/installing-open-mpi/required-support-libraries.html
The solution is given in the link. I used the last solution: 
```
./configure --with-hwloc-libdir=/usr/local/lib --with-libevent-libdir=/usr/local/lib
```
  where you need to explicitly point out where to find these libraries. 

  ## How to create external library
  There is a quick tutorial on how to create your own external library based on SST

  $ ./tree-md .
# Project tree
* src
  --
* test
  --
  

