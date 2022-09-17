# XGE_demo: X-ray generation Geant4 demo codes.
## Transmission source mode.
## The geometry includes a word, tube, W target on the diamond substrate, and a energy spectrum detecter underneath the target.
## The W target, Diamond substate, and the energy spectrum are set as sensitive detector.
## It records the X-ray spectrum genetrated in the W target and in the diamond, respectively. 
## The energy spectrum detector records the X-ray spectrum which is filtered by the W and diamond substrate.
## All the data are retrieved at the **SD.cc file, and filed into ROOT histogram in EvenAction.cc file. The ROOT histgram are set in the RunAction.cc file.
## Geometry parameters are set here: FAASTZGBParameters.cc
## The Electron beam is set here: run2.mac (bash mode); vis.mac(visulization mode).
### Start the bash mode: open a terminal, ./startrun2.sh. It will run 20000000 electron in the current terminal and generate a ROOT file under the build folder.
### Start the visulization mode: open a terminal, ./startrun1.sh. It will open a QT to show the model, it runs 30 electrons.
