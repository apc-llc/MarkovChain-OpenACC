This is a demonstration of OpenACC usage inside of R package

Based on original CPU MarkovChain package: https://github.com/Orbifold/Rcpp

```
$ PGI_ACC_TIME=1 R

R version 3.0.2 (2013-09-25) -- "Frisbee Sailing"

> library(MarkovChain)
> m = new("MarkovChain", c("a", "a", "b"), TRUE)
libcupti.so not found
Using OpenACC implementation of MarkovChain
> q()
Save workspace image? [y/n/c]: n

Accelerator Kernel Timing data
/usr/lib/R/site-library/Rcpp/include/Rcpp/routines.h
  _ZN44_INTERNAL_22_MarkovChainOpenACC_cpp_c334669514openacc_kernelEPdS0_i  NVIDIA  devicenum=0
    time(us): 37
    9: compute region reached 1 time
        14: kernel launched 1 time
            grid: [1x2]  block: [128]
            elapsed time(us): total=41 max=41 min=41 avg=41
    9: data region reached 2 times
        9: data copyin transfers: 2
             device time(us): total=26 max=16 min=10 avg=13
        19: data copyout transfers: 1
             device time(us): total=11 max=11 min=11 avg=11
```
