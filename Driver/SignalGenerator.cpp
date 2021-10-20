#include "SignalGenerator.h"

#define PI 3.1415

SignalGenerator::SignalGenerator(PinName p_outPort) : _out(p_outPort), _asyncTicker(), _debugLed(LED4) {
    _debugLed = 0;
    _mode = true; // _num_pixels is fixed, _twait is computed
    _stop = false;
    _values = NULL;
    SetSignalFrequency();
} // End of SignalGenerator::SignalGenerator

SignalGenerator::~SignalGenerator() {
    if (_values != NULL) {
        delete [] _values;
    }
} // End of SignalGenerator::~SignalGenerator

void SignalGenerator::SetSignalFrequency(SignalGenerator::SignalGeneratorType p_signalType, int p_frequency, int p_num_pixels) {
    DEBUG_ENTER("SignalGenerator::SetSignalFrequency")
    if (_values != NULL) {
        DEBUG("SignalGenerator::SetSignalFrequency: Delete _values");
        delete [] _values;
    }

    _signalType = p_signalType;
    _frequency = p_frequency;
    _num_pixels = p_num_pixels;
    DEBUG("SignalGenerator::SetSignalFrequency: _frequency=%d", _frequency)
    if (_mode) {
        //_twait = 1000000.0f / (_frequency * _num_pixels); // _num_pixels is set to 1000 pixels/T
        _twait = 1.0f / (_frequency * _num_pixels); // _num_pixels is set to 1000 pixels/T
    } else {
        _twait = 0.000001f; // 1us
        _num_pixels = (int)(1.0f / (_frequency * _twait)); // t_w is set to 1us and we fix at least 1000 pixels per period (T >> t_w): T >= 1000 * t_w ==> F < 1KHz
    }
    DEBUG("SignalGenerator::SetSignalFrequency: _twait=%f", _twait)
    DEBUG("SignalGenerator::SetSignalFrequency: _num_pixels=%d", _num_pixels)
    _values = new float[_num_pixels];
    PrepareSignal();
    DEBUG_LEAVE("SignalGenerator::SetSignalFrequency")
} // End of SignalGenerator::SetSignalFrequency

void SignalGenerator::PrepareSignal() {
    switch (_signalType) {
        case SquareSignal:
            PrepareSquareSignal();
            break;
        case TriangleSignal:
            PrepareTriangleSignal();
            break;
        case SawtoothSignal:
            PrepareSawtoothSignal();
            break;
        case ReverseSawtoothSignal:
            PrepareReverseSawtoothSignal();
            break;
        case SinusSignal:
            PrepareSinusSignal();
            break;
    } // End of 'switch' statement
} // End of SignalGenerator::PrepareSignal

void SignalGenerator::Run() {
    DEBUG_ENTER("SignalGenerator::Run")
    do {
        for (int i = 0; i < _num_pixels; i++) {
            _out = *(_values + i);
            //DEBUG_1f("SignalGenerator::Run: Current=", (float)_out)
            wait(_twait);
        }
    } while (!_stop);
    _out = 0.0f; // Reset output
    DEBUG_LEAVE("SignalGenerator::Run")
} // End of SignalGenerator::Run

void SignalGenerator::Stop() {
    DEBUG_ENTER("SignalGenerator::Stop")
    _stop = true;
    DEBUG_LEAVE("SignalGenerator::Stop")
} // End of SignalGenerator::Stop

int SignalGenerator::BeginRunAsync() {
    DEBUG_ENTER("SignalGenerator::BeginRunAsync")
    if (_twait < 0.000007f) {
        return -1;
    } else {
        _asynckCounter = 0;
        _asyncTicker.attach(this, &SignalGenerator::RunAsync, _twait);
    }
    DEBUG_LEAVE("SignalGenerator::BeginRunAsync")
    return 0;
} // End of SignalGenerator::BeginRunAsync

void SignalGenerator::RunAsync() {
    //DEBUG_ENTER("SignalGenerator::RunAsync")
    _debugLed = !_debugLed;
    _out = *(_values + _asynckCounter++);
    _asynckCounter %= _num_pixels;
    //DEBUG_LEAVE("SignalGenerator::RunAsync")
} // End of SignalGenerator::RunAsync

void SignalGenerator::EndRunAsync() {
    DEBUG_ENTER("SignalGenerator::EndRunAsync")
    _asyncTicker.detach();
    _out = 0.0f; // Reset output
    DEBUG_LEAVE("SignalGenerator::EndRunAsync")
} // End of SignalGenerator::EndRunAsync

SignalGenerator& SignalGenerator::operator =(const int& p_frequency) {
    DEBUG_ENTER("SignalGenerator::operator =")
    if (_frequency != p_frequency) {
        this->SetSignalFrequency(_signalType, p_frequency);
    }
    DEBUG_LEAVE("SignalGenerator::operator =")
    return *this;
} // End of SignalGenerator::operator =

SignalGenerator& SignalGenerator::operator =(const bool& p_mode) {
    DEBUG_ENTER("SignalGenerator::operator =")
    if (_mode != p_mode) {
        _mode = p_mode;
        this->SetSignalFrequency(_signalType, _frequency);
    }
    DEBUG_LEAVE("SignalGenerator::operator =")
    return *this;
} // End of SignalGenerator::operator =

SignalGenerator& SignalGenerator::operator =(const SignalGenerator::SignalGeneratorType& p_signalType) {
    DEBUG_ENTER("SignalGenerator::operator =")
    this->SetSignalFrequency(p_signalType, _frequency);
    DEBUG_LEAVE("SignalGenerator::operator =")
    return *this;
   
} // End of SignalGenerator::operator =

void SignalGenerator::PrepareSquareSignal() {
    DEBUG_ENTER("SignalGenerator::PrepareSquareSignal")
    int step = _num_pixels / 2;
    for (int i = 0; i < step; i += 1) {
        *(_values + i) = 1.0f;
    } // End of 'for' statement
    for (int i = step; i < _num_pixels; i += 1) {
        *(_values + i) = 0.0f;
    } // End of 'for' statement
    DEBUG_ENTER("SignalGenerator::PrepareSquareSignal")
} // End of SignalGenerator::PrepareSquareSignal

void SignalGenerator::PrepareTriangleSignal() {
    float step = 1.0f / (_num_pixels / 2.0f);
    int counter = 0;
    float i = 0.0f;
    for ( ; i < 1.0f; i += step) {
        *(_values + counter++) = i;
    } // End of 'for' statement
    for ( ; i >= 0.0f; i -= step) {
        *(_values + counter++) = i;
    } // End of 'for' statement
} // End of SignalGenerator::PrepareTriangleSignal

void SignalGenerator::PrepareSawtoothSignal() {
    float step = 1.0f / _num_pixels;
    int counter = 0;
    for (float i = 0.0f; i < 1.0f; i += step) {
        *(_values + counter++) = i;
    } // End of 'for' statement
} // End of SignalGenerator::PrepareSawtoothSignal

void SignalGenerator::PrepareReverseSawtoothSignal() {
    float step = 1.0f / _num_pixels;
    int counter = 0;
    for (float i = 0.0f; i < 1.0f; i += step) {
        *(_values + counter++) = (1.0f - i);
    } // End of 'for' statement
} // End of SignalGenerator::PrepareReverseSawtoothSignal

void SignalGenerator::PrepareSinusSignal() {
    float step = 1.0f / _num_pixels;
    int counter = 0;
    for (float i = 0.0f; i < 1.0f; i += step) {
        *(_values + counter++) = sin(2 * PI * i);
    } // End of 'for' statement
} // End of SignalGenerator::PrepareSinusSignal