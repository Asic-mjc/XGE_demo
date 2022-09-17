# XGE_demo: X-ray generation using Geant4
## OS and Geant4 version
- OS: Ubuntu 16.04.6 LTS              
- Geant4 version: geant4.10.04.p01.tar.gz
## Transmission source mode
- Simulate the X-ray spectrum generated in the W target and Diamond substrate.
- Simulate a spectrum (flux) detector to collect the X-ray spectrum emit from the entire source.

## Geometry
- The geometry includes a Word, tube, W foil target on the diamond substrate, and an energy spectrum (flux) detecter underneath the substrate.
- The 3D geometry model is as follows:
![3D gemotry model](https://user-images.githubusercontent.com/32512895/190873983-db63d48c-65ae-40c2-9778-04a7eac2a030.png)

## Input
- Geometry parameters are set here: FAASTZGBParameters.cc
- The Electron beam is set here: run2.mac (bash mode); vis.mac(visulization mode).

## Output
- The W target, Diamond substate, and the energy spectrum detector (which also can be thought as a flux detector by summing the spectrum) are set as sensitive detectors, respectively.
- The W target, Diamond substate sensitive detector record the X-ray spectrum genetrated in the W target and in the diamond, respectively. 
- The energy spectrum detector records the X-ray spectrum which is filtered by the W and diamond substrate.
- All the data are retrieved at the **SD.cc file, and filed into ROOT histogram in EvenAction.cc file. The ROOT histgram are set in the RunAction.cc file.

## Physical Process
- For our application case of X-ray imaging or X-ray tube, Penelope and Livemore may be the best options. I got this idea from a paper. [Guthoff, M., O. Brovchenko, W. De Boer, A. Dierlamm, T. Müller, A. Ritter, M. Schmanau, and H-J. Simonis. "Geant4 simulation of a filtered X-ray source for radiation damage studies." Nuclear Instruments and Methods in Physics Research Section A: Accelerators, Spectrometers, Detectors and Associated Equipment 675 (2012): 118-122.](https://www.sciencedirect.com/science/article/pii/S0168900212000691)
- According to this idea, I set a PhysicsList to refer to an example in G4. /examples/extended/electomagnetic/TestEm2/src/PhysicsList.cc. And I set the Penelope as the default physics process.
- I use a PhysicsListMessenger.cc to set it as a mac commend, ref /examples/extended/electomagnetic/TestEm2/src/PhysicsListMessenger.cc. So, we can set/change the physical process in run2.mac, for example: `/FAASTS/phys/addPhysics emlivermore` 

## Run
- Start the **bash mode**: open a terminal, `./startrun2.sh`. It will run 20000000 electrons which can be changed in run2.mac in the current terminal and generate a ROOT file under the build folder.
- Start the **visulization mode**: open a terminal, `./startrun1.sh`. It will open a QT to show the 3D model, it runs 30 electrons which can be changed at vis.mac.

## Grab or visualize the ROOT data
- Open a bash terminal at the current directory of ROOT file, then input `root` to open a root environment, then type `TBrowser b` to open a ROOT GUI. Use `.q` to quit the ROOT environment in the current terminal.
- Open a bash terminal at the current directory of ROOT file, then type `root -l plotfluxspectrum.C`. Note: We need to prepare the *.C file by ourselves, I put a demo in the folder of  **ROOT-demo**.

## References
- [Geant4 Tutorial 2015 @ MIT](https://www.slac.stanford.edu/xorg/geant4/MIT2015/MIT2015_Agenda.html) 
- A good start for beginner is the excecises in the [Hands On Sessions](https://indico.slac.stanford.edu/event/148/contributions/222/attachments/227/342/HandsOnIntro.pdf)
