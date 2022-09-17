# XGE_demo: X-ray generation Geant4 demo codes.
## Transmission source mode.

## Geometry
- The geometry includes a word, tube, W target on the diamond substrate, and a energy spectrum detecter underneath the substrate.
- The 3D geometry model is as follows:
![3D gemotry model](https://user-images.githubusercontent.com/32512895/190873983-db63d48c-65ae-40c2-9778-04a7eac2a030.png)

## Input
- Geometry parameters are set here: FAASTZGBParameters.cc
- The Electron beam is set here: run2.mac (bash mode); vis.mac(visulization mode).

## Output
- The W target, Diamond substate, and the energy spectrum detector (which also can be thought as a flux detector by summing the spectrum) are set as sensitive detector, respectively.
- It records the X-ray spectrum genetrated in the W target and in the diamond, respectively. 
- The energy spectrum detector records the X-ray spectrum which is filtered by the W and diamond substrate.
- All the data are retrieved at the **SD.cc file, and filed into ROOT histogram in EvenAction.cc file. The ROOT histgram are set in the RunAction.cc file.

## Physical Process
- For our application case of X-ray imaging or X-ray tube, Penelope and Livemore may be the best options. I got this idea from a paper. [Guthoff, M., O. Brovchenko, W. De Boer, A. Dierlamm, T. Müller, A. Ritter, M. Schmanau, and H-J. Simonis. "Geant4 simulation of a filtered X-ray source for radiation damage studies." Nuclear Instruments and Methods in Physics Research Section A: Accelerators, Spectrometers, Detectors and Associated Equipment 675 (2012): 118-122.](https://www.sciencedirect.com/science/article/pii/S0168900212000691)
- According to this idea, I set a PhysicsList to refer to an example in G4. /examples/extended/electomagnetic/TestEm2/src/PhysicsList.cc. And I set the Penelope as the default physics process.
- I use a PhysicsListMessenger.cc to set it a mac commend, ref /examples/extended/electomagnetic/TestEm2/src/PhysicsListMessenger.cc. So, we can set/change the physical process in run2.mac, for example: /FAASTS/phys/addPhysics emlivermore 

## Run
- Start the **bash mode**: open a terminal, ./startrun2.sh. It will run 20000000 electron in the current terminal and generate a ROOT file under the build folder.
- Start the **visulization mode**: open a terminal, ./startrun1.sh. It will open a QT to show the model, it runs 30 electrons.

## Grab or visulize the ROOT data
- Open a bash terminal at the current directory of ROOT file, then input "root" to open a root environment, then type "TBrowser b" to open a ROOT GUI. Use ".q" to quit the ROOT environment in the current terminal.
- Open a bash terminal at the current directory of ROOT file, then type "root -l plotfluxspectrum.C". Note: We need to prepare the *.C file by ourselves

