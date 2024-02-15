# Csound tuning
[Csound](https://csound.com) plugin for microtonal tunings.

Opcodes:

- `scalatuning` loads tunings from scl and kbm files using the [Surge Synth
  Team Tuning Library](https://github.com/surge-synthesizer/tuning-library)
- `mtsesp_notetofrequency` queries tunings with [ODDSound MTS-ESP](https://github.com/ODDSound/MTS-ESP)

## Examples

### Scala files
Load tuning from Scala scl and kbm files:
```
igTuning[] scalatuning "scale.scl", "keyboardmap.kbm"
```

Load tuning from scl file using default keyboard map:
```
igTuning[] scalatuning "scale.scl", ""
```

Here `igTuning` is an array of 128 frequencies in Hz, the frequency for each midi note.

### ODDSound MTS-ESP
Get frequency in Hz for midi note `p4` from an MTS-ESP master:
```
iFreq mtsesp_notetofrequency p4
```

Get frequency for midi note `p4`, updated throughout note:
```
kFreq mtsesp_notetofrequency p4
```

Optionally pass midi channel to use per-channel MTS-ESP tuning tables:
```
ichn midichn
kFreq mtsesp_notetofrequency p4, ichn
```

## Installation
```
$ git clone https://github.com/narenratan/csound_tuning.git
$ cd csound_tuning
$ cmake -B build
$ cmake --build build
```
On Linux this produces a shared object `libtuning.so` in the `build` directory.
Putting this in the `~/.local/lib/csound/6.0/plugins64` directory makes it
available to Csound (for Csound version >= 6.16; for more details see the
[Csound Plugins docs](https://csound-plugins.github.io/csound-plugins/Installation.html)).

## See also
- Built-in Csound [tuning opcodes](https://csound.com/docs/manual/PitchTuning.html) and [GEN51](https://csound.com/manual/GEN51.html)
- A [user defined opcode](https://github.com/csudo/csudo/blob/master/tables/create/TbScala.csd) for reading scala files
- An [article](http://www.csounds.com/journal/issue12/tuningmidikeyboard.html) on tuning in Csound
- The [Microcsound](http://www.csounds.com/journal/issue15/microcsound.html) score language and frontend
