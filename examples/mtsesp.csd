; Example using MTS-ESP to specify a tuning

<CsoundSynthesizer>
<CsOptions>
-odac
-Ma
-+rtmidi=portmidi
--midi-key=4
</CsOptions>
<CsInstruments>
sr = 44100
0dbfs = 1
nchnls = 2
ksmps = 64

instr 1
  kFreq mtsesp_notetofrequency p4
  iAmp = 0.3
  aVco vco2 iAmp, kFreq
  kEnv madsr 0.1, 0.4, 0.6, 0.7
  aLp moogladder aVco, 5000, 0.1
  outall aLp*kEnv
endin

</CsInstruments>
<CsScore>
</CsScore>
</CsoundSynthesizer>
