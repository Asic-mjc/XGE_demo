# XGE_demo: X-ray generation Geant4 demo codes.
## The geometry includes a word, tube, W target on the diamond substrate, and a energy spectrum detecter underneath the target 
## The W target, Diamond substate, and the energy spectrum are set as sensitive detector
## It records the X-ray spectrum genetrated in the W target and in the diamond, respectively. 
## The energy spectrum detector records the X-ray spectrum which is filtered by the W and diamond substrate.
## All the data are retrieved at the **SD.cc file, and filed into ROOT histogram in EvenAction.cc file. The ROOT histgram are set in the RunAction.cc file.
