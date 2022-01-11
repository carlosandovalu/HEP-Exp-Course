# ATLAS Open Data **C++** code for analysis and computer system's performance tests

  To be run under [CERN](https://home.cern) [ROOT analysis framework](https://root.cern.ch)

* **Author**: [arturos@cern.ch](arturos@cern.ch)
* **Created**: 12/03/2017
* **Updated**: 07/06/2018
<hr>

  **a)** This analysis example runs a TSelector ROOT class
  
  **b)** The analysis for test and to be used as an example is the H->WW in [this CDS note](https://cds.cern.ch/record/2156957)
  
  **c)** The code can be run in a single core, i.e. in a linear mode.
  
  **d)** The code can be run in a multicore machine, i.e. more that one core, using PROOF Lite
  
  **e)** The code is intended to be use with the 8 TeV data&MC samples in the [ATLAS Open Data website](http://opendata.atlas.cern/extendedanalysis/datasets.php)


## To run the code:

**0)** Download the samples or get the path in the [ATLAS Open Data Website](http://opendata.atlas.cern/extendedanalysis/datasets.php) 

**1)** To run the code, you will need to use/update **ROOT** to at least **version 6.X**. More in the [ROOT site](https://root.cern.ch/releases)
  
**2)** Open the main files called like `main_youranalysis.C` and change the lines `10` and `12` with *your* correct path to the ntuple's samples.
  
* The path can be where the ntuple input files are in your local host  (line `10`)
* Or the URL into the ATLAS OpenData portal (line `12`)
* See below for an example in **Extra guides**

**3)** Change the permissions of the script:

     chmod 755 analysis.sh

**4)** To run the code in parallel mode execute the command line:

     time ./analysis.sh main_youranalysis 1

**5)** To run the code in linear mode execute the command line:

     time ./analysis.sh main_youranalysis 0

**6)** In both cases, the output will be a single ROOT ntuple file with many histograms inside. Just few of them are filled for the moment.


<hr>
## Notes:

* This instructions are inside file called "analysis.sh" as well.
* The instruction `time` inside the command will print you the time that the application takes to run,
* It is not necessary to run the code, but very useful to have a concrete idea of the performance of the code/host.
* This code does not produce any useful physics results. It should be use as an example of the tool and technique.

<hr>


# Extra guides

#### in files like `main_youranalysis.C`, between lines `10` or `12`, it can be replaced for a local path or a URL

```
void main_youranalysis(int proof)
{
  // path to your local directory *or* URL, please change the default one!
  /* Local path example */
  //TString path = "/User/arturos/ATLAS/Outreach/atlas-samples-release/2016/july/complete_set_of_ATLAS_open_data_samples_July_2016/Input/";
  /* The URL to the ATLAS Open Data website repository */
  TString path = "http://opendata.atlas.cern/release/samples/";
```

#### When running the code on a terminal, it will look like this:

* **Using a single CPU, or so-called "linear" mode**

```
$  time ./analysis.sh main_youranalysis 0
Thu Jun  7 13:52:31 CEST 2018
starting ROOT
Info in <TUnixSystem::ACLiC>: creating shared library /tmp/ROOT_cpp_code_ATLAS_OpenData_for_tests/./HWWAnalysis_C.so

end of ROOT execution
Thu Jun  7 14:12:09 CEST 2018

real	19m37.739s
user	4m44.822s
sys	0m20.723s
```

* **Using a multiple CPU, or so-called "parallel" mode**

```
$  time ./analysis.sh main_youranalysis 1
Thu Jun  7 14:14:00 CEST 2018
starting ROOT
 +++ Starting PROOF-Lite with 24 workers +++
Opening connections to workers: OK (24 workers)                 
Setting up worker servers: OK (24 workers)                 
PROOF set to parallel mode (24 workers)
 
Info in <TProofLite::SetQueryRunning>: starting query: 1
Info in <TProofQueryResult::SetRunning>: nwrks: 24
Looking up for exact location of files: OK (44 files)                 
Looking up for exact location of files: OK (44 files)                 
Info in <TPacketizer::TPacketizer>: Initial number of workers: 24
Validating files: OK (44 files)                 
[TProof::Progress] Total 59939257 eventsworkers |====================| 100.00 % [219596.3 evts/s, 36.5 MB/s, time left: 0.0 s]]
 Query processing time: 273.0 s
Lite-0: all output objects have been merged                                                         
end of ROOT execution
Thu Jun  7 14:18:43 CEST 2018

real	4m42.740s
user	1m7.615s
sys	3m31.593s
```

