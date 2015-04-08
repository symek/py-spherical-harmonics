Pysh meant to gather a couple of code snippets from Siggraph papers & similar sources for computing things like spherical harmonics and other image related techniques to be used in computer graphics. There are dozens of stuff like that out there, so I thought it would be cool to have some of them in one place. All nicely warped with Python for convenience.

Ideally Pysh should stay lightweight, compile without dependencies, and get as much as possible under one umbrella.

Note: this is basically a personal project, aimed to get me used to c++.

### roadmap ###

  * Open/save probe maps.
  * Filter with various bands, project back to probes or export coefficients.
  * Structured Importance Sampling (good for light domes).
  * Wavelet Importance Sampling (?)
  * Long-lat to mirror and vice versa.
  * Hdr images from set of ldrs.
  * Normalizing Hdrs: trilateral filter etc.
  * Example codes in VEX/RSL.

### usage ###

For a picture of current usability see ./test.py