/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Jean Pierre Cimalando
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef UI_REGRADER_H
#define UI_REGRADER_H

#include "DistrhoUI.hpp"
#include "PluginRegrader.hpp"
#include "global.h"
#include "ui/Control.h"
#include <list>

class Slider;
class CheckBox;

namespace Igorski {

class UIRegrader : public UI, CControlListener {
public:
    UIRegrader();
    ~UIRegrader();

protected:
    void parameterChanged(uint32_t, float value) override;
    void sampleRateChanged(double newSampleRate) override;

    void onDisplay() override;

private:
    enum ControlFlags {
        kControlInverted = 1,
        kControlLogarithmic = 2,
    };

    void createSlider(int id, int x, int y, int w, int h, int flags = 0);
    void createCheckBox(int id, int x, int y, int w, int h, int flags = 0);

private:
    void controlValueChanged(CControl &) override;
    void controlBeganChangeGesture(CControl &) override;
    void controlEndedChangeGesture(CControl &) override;

private:
    Slider **fSliderById;
    CheckBox **fCheckBoxById;

    std::list<Widget *> fSubwidgets;

private:
    struct ParameterRangesSimple
    {
        float def, min, max;
    };

    ParameterRangesSimple *fParameterRanges;

private:
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIRegrader)
};

}

#endif
