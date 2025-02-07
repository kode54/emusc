/*  
 *  This file is part of libEmuSC, a Sound Canvas emulator library
 *  Copyright (C) 2022  Håkon Skjelten
 *
 *  libEmuSC is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  libEmuSC is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libEmuSC. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef __AHDSR_H__
#define __AHDSR_H__


#include <stdint.h>


namespace EmuSC {


class AHDSR
{
public:
  AHDSR(double value[5], double duration[5], bool shape[5],uint32_t sampleRate);
  ~AHDSR();

  void start(void);
  double get_next_value(void);
  void release(void);

  inline bool finished(void) { return _finished; }

private:
  double _phaseValue[5];
  double _phaseDuration[5];
  bool   _phaseShape[5];        // Phase 0 = linear, 1 = logarithmic

  bool _finished;               // Flag indicating whether enveolope is finished

  uint32_t _sampleRate;

  uint32_t _phaseSampleIndex;
  uint32_t _phaseSampleNum;
  uint32_t _phaseSampleLen;
  
  double _phaseInitValue;
  double _currentValue;

  enum Phase {
    ahdsr_Off     = -1,
    ahdsr_Attack  =  0,
    ahdsr_Hold    =  1,
    ahdsr_Decay   =  2,
    ahdsr_Sustain =  3,
    ahdsr_Release =  4
  };
  enum Phase _phase;
  enum Phase _terminalPhase;

  AHDSR();

  void _init_new_phase(enum Phase newPhase);

  uint32_t _sampleNum;
//  std::ofstream _ofs;

};

}

#endif  // __AHDSR_H__
