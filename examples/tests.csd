; Tests for scalatuning and mtsesp_notetofrequency opcodes

; Run `csound tests.csd` in the examples directory
; If tests pass they print 'TESTS PASSED' and exit 0
; If tests fail they exit 1

<CsoundSynthesizer>
<CsOptions>
-odac
--opcode-lib=../build/libtuning.so
</CsOptions>
<CsInstruments>
sr = 44100
0dbfs = 1
nchnls = 2
ksmps = 64

; Set tuning from Scala scl and kbm files
giTuning[] scalatuning "19EDO.scl", "launchpad.kbm"
if (round(10^6 * (giTuning[11] - 220.0)) != 0.0) then
  prints "\nTest 1 failed\n\n"
  exitnow 1
endif

; Set tuning from a Scala scl file (uses default keyboard mapping)
giTuningNoKBM[] scalatuning "19EDO.scl", ""
if (round(10^6 * (giTuningNoKBM[60] - 261.625565)) != 0.0) then
  prints "\nTest 2 failed\n\n"
  exitnow 1
endif

instr 1
  ; Get i-rate note frequency with MTS-ESP
  iFreq mtsesp_notetofrequency p4
  if (round(10^6 * (iFreq - 440.0)) != 0.0) then
      prints "\nTest 3 failed\n\n"
      exitnow 1
  endif

  ; Get k-rate note frequency with MTS-ESP
  kFreq mtsesp_notetofrequency p4

  ; Get i-rate note frequency with MTS-ESP, specifying midi channel 0
  iFreqChannel mtsesp_notetofrequency p4, 0
  if (round(10^6 * (iFreqChannel - 440.0)) != 0.0) then
      prints "\nTest 4 failed\n\n"
      exitnow 1
  endif

  ; Get k-rate note frequency with MTS-ESP, specifying midi channel 0
  kFreqChannel mtsesp_notetofrequency p4, 0

  prints "\n\nTESTS PASSED\n\n\n"
endin

</CsInstruments>
<CsScore>
i1 0 0 69
</CsScore>
</CsoundSynthesizer>
