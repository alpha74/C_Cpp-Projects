# Ricart Agarwala MCA Simulation

### Great at:
- Understanding the working of RA MCA.
- Messages sent: are shown step-by-step.


### Shortcomings
- Not uses TCP/IP.
- Not uses Socket programming.


### Build
- `g++ ricart_agarwala_sim.cpp`.
- Or Compile in any C++ editor.
- For Linux/Mac users
  - remove line `system("CLS")` as this `CLS` command is for Windows OS.
  
### Execution
- Prompts to enter number of processes. Press ENTER.
- Stops at each clock cycle, and asks input:
  - Enter any `process ID` to make that process send a `requestCS` message to all.
  - Enter `-1` to continue without making any new `requestCS`. 
  - Enter a number > largest `process ID` to stop the execution.
  
  
### Sample screenshot

![Screenshot_1](https://github.com/alpha74/C_Cpp-Projects/blob/master/Ricart_Agarwala_MCA/img/ra_mca_ss_1.png)
