# AccelStepper
Use a circular buffer to bufferize nexts steps timings. Interrupt based timer write it to stepper output pins
Time consuming operations (float mutiplication ...) are now made on background ovoiding step to be delayed.

# Side effects
There is a few ms (steps) latency for AccelStepper command to be handled, it corresponds to already buffered steps.
You can modify CircularStepBuffer.h : struct Command command[128] buffer to change this latency
