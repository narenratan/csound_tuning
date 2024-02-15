; Example using Scala scl and kbm files to specify a tuning

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

; Set tuning from Scala scl and kbm files
giTuning[] scalatuning "19EDO.scl", "launchpad.kbm"

instr 1
  iFreq = giTuning[p4]
  iAmp = 0.3
  aVco vco2 iAmp, iFreq
  kEnv madsr 0.1, 0.4, 0.6, 0.7
  aLp moogladder aVco, 5000, 0.1
  outall aLp*kEnv
endin

</CsInstruments>
<CsScore>
</CsScore>
</CsoundSynthesizer>
