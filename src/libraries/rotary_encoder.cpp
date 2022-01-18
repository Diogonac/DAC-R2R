#include "rotary_encoder.h"
#include "mbed.h"

QEI::QEI(PinName channelA, PinName channelB, int pulsesPerRev)
    : channelA_(channelA), channelB_(channelB) {

  pulses_ = 0;
  lcdPulses_ = 0;
  round_rev_d = 0;
  round_rev_f = 0;
  pulsesPerRev_ = pulsesPerRev;

  // Workout what the current state is.
  bool chanA = channelA_.read();
  bool chanB = channelB_.read();

  // 2-bit state.
  currState_ = (chanA << 1) | (chanB);
  prevState_ = currState_;

  channelA_.rise(this, &QEI::encode);
  channelA_.fall(this, &QEI::encode);
}

//エンコーダの初期化
void QEI::reset(void) {
  pulses_ = 0;
  round_rev_d = 0;
  round_rev_f = 0;
  sumangle = angle_ = 0;
  lcdPulses_ = 0;
}

//パルス数,回転回数の再設定(現在地の再設定てきな？)
void QEI::set(int pul, int rev) {
  pulses_ = pul;
  round_rev_d = rev;
  round_rev_f = rev;
}

//エンコーダ起動からのパルス数
int QEI::getPulses(void) { return pulses_; }

//エンコーダ起動からのパルス数
int QEI::getPulsesLCD(void) { return lcdPulses_; }

//回転回数(int型)
int QEI::getRev_d() { return round_rev_d; }

//回転回数(float型)
double QEI::getRev_f() { return round_rev_f; }

//回転角(-360 < angle < 360)
double QEI::getAngle() { return angle_; }

//今までの回転角
double QEI::getSumangle() { return sumangle; }

//現在のRPM(rotations per minute：分間回転数)
double QEI::getRPM() {
  static double prev_angle;
  Mper.stop();

  RPM = (sumangle - prev_angle) / Mper.read() * 60.0 / 360;
  Mper.reset();
  Mper.start();
  prev_angle = sumangle;
  return RPM;
}

// Interruptするたびに実行される
void QEI::encode(void) {
  bool chanA = channelA_.read();
  bool chanB = channelB_.read();

  currState_ = (chanA << 1) | (chanB);
  if ((prevState_ == 0x3 && currState_ == 0x0) ||
      (prevState_ == 0x0 && currState_ == 0x3)) {

    angle_pulses++;

    // if (lcdPulses_ > 14) {
    //   lcdPulses_ = 15;
    // } else {
    //   lcdPulses_++;
    // }

        if (lcdPulses_ > 1) {
      lcdPulses_ = 2;
    } else {
      lcdPulses_++;
    }

    if (pulses_ > 300) {
      pulses_ = 300;
    } else {
      pulses_++;
    }

  } else if ((prevState_ == 0x2 && currState_ == 0x1) ||
             (prevState_ == 0x1 && currState_ == 0x2)) {

    angle_pulses--;

    // if (lcdPulses_ < -1) {
    //   lcdPulses_ = 0;
    // } else {
    //   lcdPulses_--;
    // }

        if (lcdPulses_ < 1) {
      lcdPulses_ = 0;
    } else {
      lcdPulses_--;
      
    }

        if (pulses_ < 1) {
      pulses_ = 1;
    } else {
      pulses_--;
    }


  }
  angle_ = angle_pulses * 360 / ((double)pulsesPerRev_ * 2);
  sumangle = pulses_ * 360 / ((double)pulsesPerRev_ * 2);
  round_rev_f = sumangle / 360;
  if (angle_ >= 360) {
    angle_pulses = angle_ = 0;
    round_rev_d++;
  } else if (angle_ <= -360) {
    angle_pulses = angle_ = 0;
    round_rev_d--;
  }
  prevState_ = currState_;
}