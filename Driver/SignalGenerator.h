/* mbed signal generator implementation using LPC1768 DAC
 * Copyright (c) 2010 ygarcia
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#if !defined(__SIGNALGERNERATOR_H__)
#define __SIGNALGERNERATOR_H__

#include "Debug.h"

/** This class provides methods to generate differents signale wave form. V0.0.0.2
 *
 * Note that the maximum update rate of 1 MHz, so Fmax = 1MHz / _num_pixels
 *
 * Note that Vout is given by the relation below (UM10360 - Table 537. D/A Pin Description):
 *    Vout = VALUE * ((Vrefp - Vrefn) / 1024) + Vrefn
 *    in which:
 *        - Vrefp: tied to VDD (e.g. 3.3V)
 *        - Vrefn: tied to Vss
 * @see UM10360 - Chapter 30: LPC17xx Digital-to-Analog Converter (DAC)
 * @remark This class was validated with Tektronix TDS2014 oscilloscope
 * @author Yann Garcia (Don't hesitate to contact me: garcia.yann@gmail.com)
 * References:
 * - http://fabrice.sincere.pagesperso-orange.fr/cm_electronique/projet_pic/gbf/gbf.htm
 * @todo 1) Enhance comments 2) Add support of user-defined signal in byte array format
 */
class SignalGenerator
{
public:
    /** List of supported signals
     */
    enum SignalGeneratorType {
        SquareSignal = 0, //<! Square signal (50% duty cycle)
        TriangleSignal = 1, //<! Triangle signal
        SawtoothSignal = 2, //<! Sawtooth signal
        ReverseSawtoothSignal = 3, //<! Reversed sawtooth signal
        SinusSignal = 4 //<! Sinusoidal signal
    }; // End of SignalGeneratorType enum
public:
    /** Default ctor
     *
     * Initialize the internal datas. Default values are:
     * - signal type: SquareSignal
     * - frequency: 1000Hz
     * - # of pixels is fixed, _twait is adjusted
     * 
     * @param p_outPort: Pin name of the Analog out port (e.g. p18 for LPC1768)
     */
    SignalGenerator(PinName p_outPort);
    /** Default dtor
     *
     * Free resources
     */
    virtual ~SignalGenerator();
    
    /** Set the frequency of the signal.
     *
     * @param p_signalType: Signal type. Default value is square signal
     * @param p_frequency: Signal frequency. Default value is 1000Hz
     * @param p_num_pixels: Number of pixels ber period. Default value is 64
     * @see UM10360 - Chapter 30: LPC17xx Digital-to-Analog Converter (DAC)
     * @code
     * // Prepare a sinus signal at 500Hz
     * signal.SetSignalFrequency(SignalGenerator::SinusSignal,500);
     * // Launch execution
     * signal.BeginRunAsync();
     * // Here signal generation is running. Use Led or oscilloscope to vizualize output
     * printf("Press any key to terminate");
     * getchar();
     * // Terminate execution
     * signal.EndRunAsync();
     * @endcode
     */
    void SetSignalFrequency(SignalGenerator::SignalGeneratorType p_signalType = SignalGenerator::SquareSignal, int p_frequency = 1000, int p_num_pixels = 64);
    /** Generate the signal in synchrnous mode
     *
     * @see Stop() method
     */
    void Run();
    /** Method called to terminate synchronous running mode
     */
    void Stop();
    /** Method called to prepare an asynchronous running mode
     *
     * @return 0 on success, -1 if _twait less that 7us. On error, you shall use synchronous method
     */
    int BeginRunAsync();
    /** Method called to launch the asynchronous running mode
     */
    void RunAsync();
    /** Method called to terminate asynchronous running mode
     */
    void EndRunAsync();

    SignalGenerator& operator =(const bool& p_mode);
    SignalGenerator& operator =(const int& p_frequency);
    SignalGenerator& operator =(const SignalGenerator::SignalGeneratorType& p_signalType);
private:
    /** Set the signal type to generate and build the lookup table according to the signal frequency.
     */
    void PrepareSignal();
    /** Build the lookup table for a square signal according to the signal frequency.
     *
     * Note that the duty cycle is 50%. For different values, please refer to PwmOut class
     */
    void PrepareSquareSignal();
    /** Build the lookup table for a triangle signal according to the signal frequency.
     */
    void PrepareTriangleSignal();
    /** Build the lookup table for a reverse sawtooth signal according to the signal frequency.
     */
    void PrepareSawtoothSignal();
    /** Build the lookup table for a sawtooth sinal according to the signal frequency.
     */
    void PrepareReverseSawtoothSignal();
    /** Build the lookup table for a 'sinus' sinal according to the signal frequency.
     */
    void PrepareSinusSignal();
private:
   SignalGenerator::SignalGeneratorType _signalType; //<! Signal selected - Default value is SquareSignal
   int _frequency; // Required frequency of the signal
   float *_values; //<! Pointer to the array of calculated values for the selected signal
   int _num_pixels; // <! Number of calculated points, this is the _values length
   float _twait; //<! Time between each changes of the analog output
   bool _mode; //<! # of pixels is fixed (128 pixels)
   AnalogOut _out; //<! Analog out pin of the LPC1768
   bool _stop; //<! Set to tru to stop the signal generation
   int _asynckCounter; //<! Index on _values when asynchronous run is used
   Ticker _asyncTicker; //<! Ticker to ipdate DAC when asynchronous run is used
   DigitalOut _debugLed; //<! For debug with oscilloscope purpose
}; // End of class SignalGenerator
  
#endif // __SIGNALGERNERATOR_H__
