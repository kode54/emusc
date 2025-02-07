/*
 *  This file is part of EmuSC, a Sound Canvas emulator
 *  Copyright (C) 2022  Håkon Skjelten
 *
 *  EmuSC is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  EmuSC is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with EmuSC. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef EMULATOR_H
#define EMULATOR_H

#include "emusc/control_rom.h"
#include "emusc/pcm_rom.h"
#include "emusc/synth.h"

#include "audio_output.h"
#include "midi_input.h"

#include <QString>
#include <QVector>
#include <QStandardItemModel>
#include <QTimer>
#include <QWidget>

#include <inttypes.h>


class Emulator : public QObject
{
  Q_OBJECT

public:
  Emulator(void);
  virtual ~Emulator();

  void load_control_rom(QString romPath);
  void load_pcm_rom(QVector<QString> romPaths);

  bool has_valid_control_rom(void);
  bool has_valid_pcm_rom(void);

  void start(void);
  void stop(void);

  QString control_rom_model(void);
  QString control_rom_version(void);
  QString control_rom_date(void);
  QString pcm_rom_version(void);
  QString pcm_rom_date(void);

  QStandardItemModel *get_instruments_list(void);
  QStandardItemModel *get_partials_list(void);
  QStandardItemModel *get_samples_list(void);
  QStandardItemModel *get_variations_list(void);
  QStandardItemModel *get_drum_sets_list(void);

  int dump_demo_songs(QString path);
  QVector<uint8_t> get_intro_anim(void);
  bool control_rom_changed(void);

  void all_sounds_off(void);

  QVector<bool> get_part_amplitude_vector(void);

signals:
  void emulator_started(void);
  void emulator_stopped(void);

  void new_bar_display(QVector<bool>*);
  void display_part_updated(QString text);
  void display_instrument_updated(QString text);
  void display_level_updated(QString text);
  void display_pan_updated(QString text);
  void display_reverb_updated(QString text);
  void display_chorus_updated(QString text);
  void display_key_shift_updated(QString text);
  void display_midi_channel_updated(QString text);

  void all_button_changed(bool state);
  void mute_button_changed(bool state);

public slots:
  void select_all();
  void select_mute();

  void select_next_part();
  void select_prev_part();
  void select_next_instrument();
  void select_prev_instrument();
  void select_next_level();
  void select_prev_level();
  void select_next_pan();
  void select_prev_pan();
  void select_next_reverb();
  void select_prev_reverb();
  void select_next_chorus();
  void select_prev_chorus();
  void select_next_key_shift();
  void select_prev_key_shift();
  void select_next_midi_channel();
  void select_prev_midi_channel();

  void change_volume(int volume);

  void generate_bar_display(void);
  void play_intro_anim_bar_display(void);

private:
  EmuSC::ControlRom *_emuscControlRom;
  EmuSC::PcmRom *_emuscPcmRom;
  EmuSC::Synth *_emuscSynth;

  QString _ctrlRomModel;
  QString _ctrlRomVersion;
  QString _ctrlRomDate;
  QString _pcmRomVersion;
  QString _pcmRomDate;

  AudioOutput *_audioOutput;
  MidiInput   *_midiInput;

  bool _ctrlRomUpdated;

  uint8_t _selectedPart;

  QVector<bool> _barDisplay;

  struct lcdBarDisplayPartHist {
    bool falling;
    int value;
    int time;
  };
  QVector<struct lcdBarDisplayPartHist> _lcdBarDisplayHistVect;

  QTimer *_lcdDisplayTimer;

  int _introFrameIndex;
  QVector<uint8_t> _introAnimData;

  bool _allMode;

  void _start_midi_subsystem();
  void _start_audio_subsystem();

  void set_all(void);
  void set_part(uint8_t value);

  void set_instrument(uint8_t index, uint8_t bank, bool update);
  void set_level(uint8_t value, bool update);
  void set_pan(uint8_t value, bool update);
  void set_reverb(uint8_t value, bool update);
  void set_chorus(uint8_t value, bool update);
  void set_key_shift(int8_t value, bool update);
  void set_midi_channel(uint8_t value, bool update);

  void part_mod_callback(const int partId);
};


#endif // EMULATOR_H
