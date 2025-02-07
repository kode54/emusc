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


#ifndef __TVF_H__
#define __TVF_H__


#include "control_rom.h"
#include "lowpass_filter.h"
#include "ahdsr.h"

#include <stdint.h>


namespace EmuSC {


class TVF
{
private:
  AHDSR *_ahdsr;
  LowPassFilter *_lpFilter;

  ControlRom::InstPartial *_instPartial;

  uint32_t _sampleRate;
  
  double _convert_time_to_sec(uint8_t time);

  TVF();

public:
  TVF(ControlRom::InstPartial instPartial, uint32_t sampleRate);
  ~TVF();

  double apply(double input);
  void note_off();

  inline bool finished(void) { if (_ahdsr) return _ahdsr->finished(); }

};

}

#endif  // __TVF_H__
