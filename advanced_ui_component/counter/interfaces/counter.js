/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;

export var CounterType;
(function (j21) {
    j21[j21["LIST"] = 0] = "LIST";
    j21[j21["COMPACT"] = 1] = "COMPACT";
    j21[j21["INLINE"] = 2] = "INLINE";
    j21[j21["INLINE_DATE"] = 3] = "INLINE_DATE";
})(CounterType || (CounterType = {}));
var FocusText;
(function (i21) {
    i21[i21["NONE"] = 0] = "NONE";
    i21[i21["TEXT1"] = 1] = "TEXT1";
    i21[i21["TEXT2"] = 2] = "TEXT2";
    i21[i21["TEXT3"] = 3] = "TEXT3";
})(FocusText || (FocusText = {}));

export class CommonOptions {
}

export class InlineStyleOptions extends CommonOptions {
}

export class NumberStyleOptions extends InlineStyleOptions {
}

export class DateData {
    constructor(f21, g21, h21) {
        this.year = f21;
        this.month = g21;
        this.day = h21;
    }

    toString() {
        let c21 = this.year.toString() + '-';
        let d21 = this.month < 10 ? '0' + this.month.toString() : this.month.toString();
        c21 += d21 + '-';
        let e21 = this.day < 10 ? '0' + this.day.toString() : this.day.toString();
        c21 += e21;
        return c21;
    }
}

export class DateStyleOptions extends CommonOptions {
}

export class CounterOptions {
}

class CounterResource {
}

CounterResource.BUTTON_BACKGROUD_COLOR = {
    "id": -1,
    "type": 10001,
    params: ['sys.color.ohos_id_color_button_normal'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.BUTTON_ICON_COLOR = {
    "id": -1,
    "type": 10001,
    params: ['sys.color.ohos_id_color_primary'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.BUTTON_BORDER_FOCUSED_COLOR = {
    "id": -1,
    "type": 10001,
    params: ['sys.color.ohos_id_color_focused_outline'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.COUNTER_TEXT_COLOR = {
    "id": -1,
    "type": 10001,
    params: ['sys.color.ohos_id_color_text_primary'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.COUNTER_BORDER_COLOR = {
    "id": -1,
    "type": 10001,
    params: ['sys.color.ohos_id_color_component_normal'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.BUTTON_ADD_ICON = {
    "id": -1,
    "type": 20000,
    params: ["sys.media.ohos_ic_public_add"],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.BUTTON_SUB_ICON = {
    "id": -1,
    "type": 20000,
    params: ["sys.media.ohos_ic_public_minus"],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.BUTTON_ARROW_UP = {
    "id": -1,
    "type": 20000,
    params: ['sys.media.ohos_ic_public_arrow_up'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.BUTTON_ARROW_DOWN = {
    "id": -1,
    "type": 20000,
    params: ['sys.media.ohos_ic_public_arrow_down'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.BUTTON_BORDER_FOCUSED_WIDTH = '2vp';
CounterResource.BUTTON_BORDER_BLUR_WIDTH = '0vp';
CounterResource.COUNTER_BORDER_WIDTH = '1vp';
CounterResource.COUNTER_BORDER_WIDTH_NUMBER = 1;
CounterResource.COUNTER_LIST_LABEL_SIZE = {
    "id": -1,
    "type": 10002,
    params: ['sys.float.ohos_id_text_size_body1'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.COUNTER_LIST_NUMBER_SIZE = {
    "id": -1,
    "type": 10002,
    params: ['sys.float.ohos_id_text_size_body1'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.COUNTER_COMPACT_LABEL_SIZE = {
    "id": -1,
    "type": 10002,
    params: ['sys.float.ohos_id_text_size_body2'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.COUNTER_NUMBER_SIZE = {
    "id": -1,
    "type": 10002,
    params: ['sys.float.ohos_id_text_size_body1'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.COUNTER_LIST_LEFT_PADDING = {
    "id": -1,
    "type": 10002,
    params: ['sys.float.ohos_id_default_padding_start'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.COUNTER_LIST_RIGHT_PADDING = {
    "id": -1,
    "type": 10002,
    params: ['sys.float.ohos_id_default_padding_end'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
CounterResource.COUNTER_LIST_PADDING = 12;
CounterResource.COUNTER_LIST_HEIGHT = '48vp';
CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE = '20vp';
CounterResource.COUNTER_LIST_BUTTON_SIZE = '32vp';
CounterResource.COUNTER_LIST_BUTTON_RADIUS = '16vp';
CounterResource.COUNTER_LIST_BUTTON_TEXT_DISTANCE = '8vp';
CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN = 8;
CounterResource.COUNTER_LIST_FOCUS_BORDER_SIZE = '30vp';
CounterResource.COUNTER_LIST_FOCUS_BORDER_RADIUS = '15vp';
CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_X = '-8vp';
CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_Y = '-8vp';
CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE = '16vp';
CounterResource.COUNTER_COMPACT_BUTTON_SIZE = '24vp';
CounterResource.COUNTER_COMPACT_BUTTON_RADIUS = '12vp';
CounterResource.COUNTER_COMPACT_BUTTON_TEXT_DISTANCE = '10vp';
CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN = 10;
CounterResource.COUNTER_COMPACT_CONTAINER_HEIGHT = '28vp';
CounterResource.COUNTER_COMPACT_CONTAINER_RADIUS = '14vp';
CounterResource.COUNTER_COMPACT_CONTAINER_LABEL_DISTANCE = '8vp';
CounterResource.COUNTER_COMPACT_FOCUS_BORDER_SIZE = '22vp';
CounterResource.COUNTER_COMPACT_FOCUS_BORDER_RADIUS = '11vp';
CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH = '24vp';
CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT = '12vp';
CounterResource.COUNTER_INLINE_BUTTON_TEXT_DISTANCE = '12vp';
CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT = '32vp';
CounterResource.COUNTER_INLINE_BUTTON_WIDTH = '32vp';
CounterResource.COUNTER_INLINE_BUTTON_HEIGHT = '16vp';
CounterResource.COUNTER_INLINE_RADIUS = '8vp';
CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH = '28vp';
CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT = '13.5vp';
CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN = 12;
CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN = 12;
CounterResource.COUNTER_BUTTON_INITIAL_OPACITY = 1;
CounterResource.COUNTER_BUTTON_DISABLE_OPACITY = 0.4;

class CounterConstant {
}

CounterConstant.COUNTER_MAX_YEAR = 5000;
CounterConstant.COUNTER_MIN_YEAR = 1;
CounterConstant.COUNTER_INITIAL_MONTH = 1;
CounterConstant.COUNTER_INITIAL_DAY = 1;
CounterConstant.COUNTER_INITIAL_STEP = 1;
CounterConstant.COUNTER_TEN_NUMBER = 10;
CounterConstant.COUNTER_MIN_MONTH = 1;
CounterConstant.COUNTER_MAX_MONTH = 12;
CounterConstant.COUNTER_MIN_DAY = 1;
CounterConstant.KEYCODE_DPAD_UP = 2012;
CounterConstant.KEYCODE_DPAD_DOWN = 2013;
CounterConstant.KEYCODE_DPAD_LEFT = 2014;
CounterConstant.KEYCODE_DPAD_RIGHT = 2015;
CounterConstant.KEYCODE_MOVE_HOME = 2081;
CounterConstant.KEYCODE_MOVE_END = 2082;
CounterConstant.KEYCODE_TAB = 2049;
CounterConstant.KEYCODE_ESC = 2070;
CounterConstant.COUNTER_MIN_VALUE = 0;
CounterConstant.COUNTER_MAX_VALUE = 999;
CounterConstant.JANUARY = 1;
CounterConstant.FEBRUARY = 2;
CounterConstant.MARCH = 3;
CounterConstant.APRIL = 4;
CounterConstant.MAY = 5;
CounterConstant.JUNE = 6;
CounterConstant.JULY = 7;
CounterConstant.AUGUST = 8;
CounterConstant.SEPTEMBER = 9;
CounterConstant.OCTOBER = 10;
CounterConstant.NOVEMBER = 11;
CounterConstant.DECEMBER = 12;
CounterConstant.BIG_MONTH_DAYS = 31;
CounterConstant.SMALL_MONTH_DAYS = 30;
CounterConstant.FEBRUARY_DAYS = 28;
CounterConstant.AUSPICIOUS_FEBRUARY_DAYS = 29;
CounterConstant.AUSPICIOUS_FOUR = 4;
CounterConstant.AUSPICIOUS_HUNDRED = 100;
CounterConstant.AUSPICIOUS_FOUR_HUNDRED = 400;

export class CounterComponent extends ViewPU {
    constructor(w20, x20, y20, z20 = -1, a21 = undefined, b21) {
        super(w20, y20, z20, b21);
        if (typeof a21 === "function") {
            this.paramsGenerator_ = a21;
        }
        this.__options = new SynchedPropertyObjectOneWayPU(x20.options, this, "options");
        this.__type = new ObservedPropertySimplePU(-1, this, "type");
        this.__counterDirection = new ObservedPropertySimplePU(Direction.Auto, this, "counterDirection");
        this.__choverEffect = new ObservedPropertySimplePU(HoverEffect.Auto, this, "choverEffect");
        this.__focusEnable = new ObservedPropertySimplePU(true, this, "focusEnable");
        this.__step = new ObservedPropertySimplePU(CounterConstant.COUNTER_INITIAL_STEP, this, "step");
        this.__inputValue = new ObservedPropertySimplePU('0', this, "inputValue");
        this.__inputYear = new ObservedPropertySimplePU(CounterConstant.COUNTER_MIN_YEAR, this, "inputYear");
        this.__inputMoon = new ObservedPropertySimplePU(0, this, "inputMoon");
        this.__inputDay = new ObservedPropertySimplePU(0, this, "inputDay");
        this.__inputHour = new ObservedPropertySimplePU(0, this, "inputHour");
        this.__inputMinute = new ObservedPropertySimplePU(0, this, "inputMinute");
        this.__inputSecond = new ObservedPropertySimplePU(0, this, "inputSecond");
        this.__subOpacity = new ObservedPropertySimplePU(CounterResource.COUNTER_BUTTON_INITIAL_OPACITY, this, "subOpacity");
        this.__addOpacity = new ObservedPropertySimplePU(CounterResource.COUNTER_BUTTON_INITIAL_OPACITY, this, "addOpacity");
        this.__subBtnStateEffect = new ObservedPropertySimplePU(true, this, "subBtnStateEffect");
        this.__addBtnStateEffect = new ObservedPropertySimplePU(true, this, "addBtnStateEffect");
        this.__focusText = new ObservedPropertySimplePU(FocusText.NONE, this, "focusText");
        this.__hasFocusText1 = new ObservedPropertySimplePU(false, this, "hasFocusText1");
        this.__hasFocusText2 = new ObservedPropertySimplePU(false, this, "hasFocusText2");
        this.__hasFocusText3 = new ObservedPropertySimplePU(false, this, "hasFocusText3");
        this.__subBtnFocusWidh = new ObservedPropertySimplePU('0vp', this, "subBtnFocusWidh");
        this.__addBtnFocusWidh = new ObservedPropertySimplePU('0vp', this, "addBtnFocusWidh");
        this.__value = new ObservedPropertyObjectPU(undefined, this, "value");
        this.__year = new ObservedPropertySimplePU(0, this, "year");
        this.__month = new ObservedPropertySimplePU(0, this, "month");
        this.__day = new ObservedPropertySimplePU(0, this, "day");
        this.__hour = new ObservedPropertySimplePU(0, this, "hour");
        this.__minute = new ObservedPropertySimplePU(0, this, "minute");
        this.__second = new ObservedPropertySimplePU(0, this, "second");
        this.__subBtnEnabled = new ObservedPropertySimplePU(true, this, "subBtnEnabled");
        this.__addBtnEnabled = new ObservedPropertySimplePU(true, this, "addBtnEnabled");
        this.__hasInputText1 = new ObservedPropertySimplePU(false, this, "hasInputText1");
        this.__hasInputText2 = new ObservedPropertySimplePU(false, this, "hasInputText2");
        this.__hasInputText3 = new ObservedPropertySimplePU(false, this, "hasInputText3");
        this.__textWidth = new ObservedPropertySimplePU(0, this, "textWidth");
        this.__min = new ObservedPropertySimplePU(CounterConstant.COUNTER_MIN_VALUE, this, "min");
        this.__max = new ObservedPropertySimplePU(CounterConstant.COUNTER_MAX_VALUE, this, "max");
        this.maxYear = CounterConstant.COUNTER_MAX_YEAR;
        this.minYear = CounterConstant.COUNTER_MIN_YEAR;
        this.numberStrList = ['00', '01', '02', '03', '04', '05', '06', '07', '08', '09'];
        this.onHoverIncrease = undefined;
        this.onHoverDecrease = undefined;
        this.onFocusIncrease = undefined;
        this.onFocusDecrease = undefined;
        this.onBlurIncrease = undefined;
        this.onBlurDecrease = undefined;
        this.onChange = undefined;
        this.onDateChange = undefined;
        this.timeoutID1 = -1;
        this.timeoutID2 = -1;
        this.timeoutID3 = -1;
        this.numberStyleOptions = undefined;
        this.dateStyleOptions = undefined;
        this.inlineStyleOptions = undefined;
        this.timeStamp = 0;
        this.hasTextWidth = false;
        this.controller1 = new TextInputController();
        this.controller2 = new TextInputController();
        this.controller3 = new TextInputController();
        this.setInitiallyProvidedValue(x20);
        this.declareWatch("options", this.onOptionsChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(v20) {
        if (v20.type !== undefined) {
            this.type = v20.type;
        }
        if (v20.counterDirection !== undefined) {
            this.counterDirection = v20.counterDirection;
        }
        if (v20.choverEffect !== undefined) {
            this.choverEffect = v20.choverEffect;
        }
        if (v20.focusEnable !== undefined) {
            this.focusEnable = v20.focusEnable;
        }
        if (v20.step !== undefined) {
            this.step = v20.step;
        }
        if (v20.inputValue !== undefined) {
            this.inputValue = v20.inputValue;
        }
        if (v20.inputYear !== undefined) {
            this.inputYear = v20.inputYear;
        }
        if (v20.inputMoon !== undefined) {
            this.inputMoon = v20.inputMoon;
        }
        if (v20.inputDay !== undefined) {
            this.inputDay = v20.inputDay;
        }
        if (v20.inputHour !== undefined) {
            this.inputHour = v20.inputHour;
        }
        if (v20.inputMinute !== undefined) {
            this.inputMinute = v20.inputMinute;
        }
        if (v20.inputSecond !== undefined) {
            this.inputSecond = v20.inputSecond;
        }
        if (v20.subOpacity !== undefined) {
            this.subOpacity = v20.subOpacity;
        }
        if (v20.addOpacity !== undefined) {
            this.addOpacity = v20.addOpacity;
        }
        if (v20.subBtnStateEffect !== undefined) {
            this.subBtnStateEffect = v20.subBtnStateEffect;
        }
        if (v20.addBtnStateEffect !== undefined) {
            this.addBtnStateEffect = v20.addBtnStateEffect;
        }
        if (v20.focusText !== undefined) {
            this.focusText = v20.focusText;
        }
        if (v20.hasFocusText1 !== undefined) {
            this.hasFocusText1 = v20.hasFocusText1;
        }
        if (v20.hasFocusText2 !== undefined) {
            this.hasFocusText2 = v20.hasFocusText2;
        }
        if (v20.hasFocusText3 !== undefined) {
            this.hasFocusText3 = v20.hasFocusText3;
        }
        if (v20.subBtnFocusWidh !== undefined) {
            this.subBtnFocusWidh = v20.subBtnFocusWidh;
        }
        if (v20.addBtnFocusWidh !== undefined) {
            this.addBtnFocusWidh = v20.addBtnFocusWidh;
        }
        if (v20.value !== undefined) {
            this.value = v20.value;
        }
        if (v20.year !== undefined) {
            this.year = v20.year;
        }
        if (v20.month !== undefined) {
            this.month = v20.month;
        }
        if (v20.day !== undefined) {
            this.day = v20.day;
        }
        if (v20.hour !== undefined) {
            this.hour = v20.hour;
        }
        if (v20.minute !== undefined) {
            this.minute = v20.minute;
        }
        if (v20.second !== undefined) {
            this.second = v20.second;
        }
        if (v20.subBtnEnabled !== undefined) {
            this.subBtnEnabled = v20.subBtnEnabled;
        }
        if (v20.addBtnEnabled !== undefined) {
            this.addBtnEnabled = v20.addBtnEnabled;
        }
        if (v20.hasInputText1 !== undefined) {
            this.hasInputText1 = v20.hasInputText1;
        }
        if (v20.hasInputText2 !== undefined) {
            this.hasInputText2 = v20.hasInputText2;
        }
        if (v20.hasInputText3 !== undefined) {
            this.hasInputText3 = v20.hasInputText3;
        }
        if (v20.textWidth !== undefined) {
            this.textWidth = v20.textWidth;
        }
        if (v20.min !== undefined) {
            this.min = v20.min;
        }
        if (v20.max !== undefined) {
            this.max = v20.max;
        }
        if (v20.maxYear !== undefined) {
            this.maxYear = v20.maxYear;
        }
        if (v20.minYear !== undefined) {
            this.minYear = v20.minYear;
        }
        if (v20.numberStrList !== undefined) {
            this.numberStrList = v20.numberStrList;
        }
        if (v20.onHoverIncrease !== undefined) {
            this.onHoverIncrease = v20.onHoverIncrease;
        }
        if (v20.onHoverDecrease !== undefined) {
            this.onHoverDecrease = v20.onHoverDecrease;
        }
        if (v20.onFocusIncrease !== undefined) {
            this.onFocusIncrease = v20.onFocusIncrease;
        }
        if (v20.onFocusDecrease !== undefined) {
            this.onFocusDecrease = v20.onFocusDecrease;
        }
        if (v20.onBlurIncrease !== undefined) {
            this.onBlurIncrease = v20.onBlurIncrease;
        }
        if (v20.onBlurDecrease !== undefined) {
            this.onBlurDecrease = v20.onBlurDecrease;
        }
        if (v20.onChange !== undefined) {
            this.onChange = v20.onChange;
        }
        if (v20.onDateChange !== undefined) {
            this.onDateChange = v20.onDateChange;
        }
        if (v20.timeoutID1 !== undefined) {
            this.timeoutID1 = v20.timeoutID1;
        }
        if (v20.timeoutID2 !== undefined) {
            this.timeoutID2 = v20.timeoutID2;
        }
        if (v20.timeoutID3 !== undefined) {
            this.timeoutID3 = v20.timeoutID3;
        }
        if (v20.numberStyleOptions !== undefined) {
            this.numberStyleOptions = v20.numberStyleOptions;
        }
        if (v20.dateStyleOptions !== undefined) {
            this.dateStyleOptions = v20.dateStyleOptions;
        }
        if (v20.inlineStyleOptions !== undefined) {
            this.inlineStyleOptions = v20.inlineStyleOptions;
        }
        if (v20.timeStamp !== undefined) {
            this.timeStamp = v20.timeStamp;
        }
        if (v20.hasTextWidth !== undefined) {
            this.hasTextWidth = v20.hasTextWidth;
        }
        if (v20.controller1 !== undefined) {
            this.controller1 = v20.controller1;
        }
        if (v20.controller2 !== undefined) {
            this.controller2 = v20.controller2;
        }
        if (v20.controller3 !== undefined) {
            this.controller3 = v20.controller3;
        }
    }

    updateStateVars(u20) {
        this.__options.reset(u20.options);
    }

    purgeVariableDependenciesOnElmtId(t20) {
        this.__options.purgeDependencyOnElmtId(t20);
        this.__type.purgeDependencyOnElmtId(t20);
        this.__counterDirection.purgeDependencyOnElmtId(t20);
        this.__choverEffect.purgeDependencyOnElmtId(t20);
        this.__focusEnable.purgeDependencyOnElmtId(t20);
        this.__step.purgeDependencyOnElmtId(t20);
        this.__inputValue.purgeDependencyOnElmtId(t20);
        this.__inputYear.purgeDependencyOnElmtId(t20);
        this.__inputMoon.purgeDependencyOnElmtId(t20);
        this.__inputDay.purgeDependencyOnElmtId(t20);
        this.__inputHour.purgeDependencyOnElmtId(t20);
        this.__inputMinute.purgeDependencyOnElmtId(t20);
        this.__inputSecond.purgeDependencyOnElmtId(t20);
        this.__subOpacity.purgeDependencyOnElmtId(t20);
        this.__addOpacity.purgeDependencyOnElmtId(t20);
        this.__subBtnStateEffect.purgeDependencyOnElmtId(t20);
        this.__addBtnStateEffect.purgeDependencyOnElmtId(t20);
        this.__focusText.purgeDependencyOnElmtId(t20);
        this.__hasFocusText1.purgeDependencyOnElmtId(t20);
        this.__hasFocusText2.purgeDependencyOnElmtId(t20);
        this.__hasFocusText3.purgeDependencyOnElmtId(t20);
        this.__subBtnFocusWidh.purgeDependencyOnElmtId(t20);
        this.__addBtnFocusWidh.purgeDependencyOnElmtId(t20);
        this.__value.purgeDependencyOnElmtId(t20);
        this.__year.purgeDependencyOnElmtId(t20);
        this.__month.purgeDependencyOnElmtId(t20);
        this.__day.purgeDependencyOnElmtId(t20);
        this.__hour.purgeDependencyOnElmtId(t20);
        this.__minute.purgeDependencyOnElmtId(t20);
        this.__second.purgeDependencyOnElmtId(t20);
        this.__subBtnEnabled.purgeDependencyOnElmtId(t20);
        this.__addBtnEnabled.purgeDependencyOnElmtId(t20);
        this.__hasInputText1.purgeDependencyOnElmtId(t20);
        this.__hasInputText2.purgeDependencyOnElmtId(t20);
        this.__hasInputText3.purgeDependencyOnElmtId(t20);
        this.__textWidth.purgeDependencyOnElmtId(t20);
        this.__min.purgeDependencyOnElmtId(t20);
        this.__max.purgeDependencyOnElmtId(t20);
    }

    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__type.aboutToBeDeleted();
        this.__counterDirection.aboutToBeDeleted();
        this.__choverEffect.aboutToBeDeleted();
        this.__focusEnable.aboutToBeDeleted();
        this.__step.aboutToBeDeleted();
        this.__inputValue.aboutToBeDeleted();
        this.__inputYear.aboutToBeDeleted();
        this.__inputMoon.aboutToBeDeleted();
        this.__inputDay.aboutToBeDeleted();
        this.__inputHour.aboutToBeDeleted();
        this.__inputMinute.aboutToBeDeleted();
        this.__inputSecond.aboutToBeDeleted();
        this.__subOpacity.aboutToBeDeleted();
        this.__addOpacity.aboutToBeDeleted();
        this.__subBtnStateEffect.aboutToBeDeleted();
        this.__addBtnStateEffect.aboutToBeDeleted();
        this.__focusText.aboutToBeDeleted();
        this.__hasFocusText1.aboutToBeDeleted();
        this.__hasFocusText2.aboutToBeDeleted();
        this.__hasFocusText3.aboutToBeDeleted();
        this.__subBtnFocusWidh.aboutToBeDeleted();
        this.__addBtnFocusWidh.aboutToBeDeleted();
        this.__value.aboutToBeDeleted();
        this.__year.aboutToBeDeleted();
        this.__month.aboutToBeDeleted();
        this.__day.aboutToBeDeleted();
        this.__hour.aboutToBeDeleted();
        this.__minute.aboutToBeDeleted();
        this.__second.aboutToBeDeleted();
        this.__subBtnEnabled.aboutToBeDeleted();
        this.__addBtnEnabled.aboutToBeDeleted();
        this.__hasInputText1.aboutToBeDeleted();
        this.__hasInputText2.aboutToBeDeleted();
        this.__hasInputText3.aboutToBeDeleted();
        this.__textWidth.aboutToBeDeleted();
        this.__min.aboutToBeDeleted();
        this.__max.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get options() {
        return this.__options.get();
    }

    set options(s20) {
        this.__options.set(s20);
    }

    get type() {
        return this.__type.get();
    }

    set type(r20) {
        this.__type.set(r20);
    }

    get counterDirection() {
        return this.__counterDirection.get();
    }

    set counterDirection(q20) {
        this.__counterDirection.set(q20);
    }

    get choverEffect() {
        return this.__choverEffect.get();
    }

    set choverEffect(p20) {
        this.__choverEffect.set(p20);
    }

    get focusEnable() {
        return this.__focusEnable.get();
    }

    set focusEnable(o20) {
        this.__focusEnable.set(o20);
    }

    get step() {
        return this.__step.get();
    }

    set step(n20) {
        this.__step.set(n20);
    }

    get inputValue() {
        return this.__inputValue.get();
    }

    set inputValue(m20) {
        this.__inputValue.set(m20);
    }

    get inputYear() {
        return this.__inputYear.get();
    }

    set inputYear(l20) {
        this.__inputYear.set(l20);
    }

    get inputMoon() {
        return this.__inputMoon.get();
    }

    set inputMoon(k20) {
        this.__inputMoon.set(k20);
    }

    get inputDay() {
        return this.__inputDay.get();
    }

    set inputDay(j20) {
        this.__inputDay.set(j20);
    }

    get inputHour() {
        return this.__inputHour.get();
    }

    set inputHour(i20) {
        this.__inputHour.set(i20);
    }

    get inputMinute() {
        return this.__inputMinute.get();
    }

    set inputMinute(h20) {
        this.__inputMinute.set(h20);
    }

    get inputSecond() {
        return this.__inputSecond.get();
    }

    set inputSecond(g20) {
        this.__inputSecond.set(g20);
    }

    get subOpacity() {
        return this.__subOpacity.get();
    }

    set subOpacity(f20) {
        this.__subOpacity.set(f20);
    }

    get addOpacity() {
        return this.__addOpacity.get();
    }

    set addOpacity(e20) {
        this.__addOpacity.set(e20);
    }

    get subBtnStateEffect() {
        return this.__subBtnStateEffect.get();
    }

    set subBtnStateEffect(d20) {
        this.__subBtnStateEffect.set(d20);
    }

    get addBtnStateEffect() {
        return this.__addBtnStateEffect.get();
    }

    set addBtnStateEffect(c20) {
        this.__addBtnStateEffect.set(c20);
    }

    get focusText() {
        return this.__focusText.get();
    }

    set focusText(b20) {
        this.__focusText.set(b20);
    }

    get hasFocusText1() {
        return this.__hasFocusText1.get();
    }

    set hasFocusText1(a20) {
        this.__hasFocusText1.set(a20);
    }

    get hasFocusText2() {
        return this.__hasFocusText2.get();
    }

    set hasFocusText2(z19) {
        this.__hasFocusText2.set(z19);
    }

    get hasFocusText3() {
        return this.__hasFocusText3.get();
    }

    set hasFocusText3(y19) {
        this.__hasFocusText3.set(y19);
    }

    get subBtnFocusWidh() {
        return this.__subBtnFocusWidh.get();
    }

    set subBtnFocusWidh(x19) {
        this.__subBtnFocusWidh.set(x19);
    }

    get addBtnFocusWidh() {
        return this.__addBtnFocusWidh.get();
    }

    set addBtnFocusWidh(w19) {
        this.__addBtnFocusWidh.set(w19);
    }

    get value() {
        return this.__value.get();
    }

    set value(v19) {
        this.__value.set(v19);
    }

    get year() {
        return this.__year.get();
    }

    set year(u19) {
        this.__year.set(u19);
    }

    get month() {
        return this.__month.get();
    }

    set month(t19) {
        this.__month.set(t19);
    }

    get day() {
        return this.__day.get();
    }

    set day(s19) {
        this.__day.set(s19);
    }

    get hour() {
        return this.__hour.get();
    }

    set hour(r19) {
        this.__hour.set(r19);
    }

    get minute() {
        return this.__minute.get();
    }

    set minute(q19) {
        this.__minute.set(q19);
    }

    get second() {
        return this.__second.get();
    }

    set second(p19) {
        this.__second.set(p19);
    }

    get subBtnEnabled() {
        return this.__subBtnEnabled.get();
    }

    set subBtnEnabled(o19) {
        this.__subBtnEnabled.set(o19);
    }

    get addBtnEnabled() {
        return this.__addBtnEnabled.get();
    }

    set addBtnEnabled(n19) {
        this.__addBtnEnabled.set(n19);
    }

    get hasInputText1() {
        return this.__hasInputText1.get();
    }

    set hasInputText1(m19) {
        this.__hasInputText1.set(m19);
    }

    get hasInputText2() {
        return this.__hasInputText2.get();
    }

    set hasInputText2(l19) {
        this.__hasInputText2.set(l19);
    }

    get hasInputText3() {
        return this.__hasInputText3.get();
    }

    set hasInputText3(k19) {
        this.__hasInputText3.set(k19);
    }

    get textWidth() {
        return this.__textWidth.get();
    }

    set textWidth(j19) {
        this.__textWidth.set(j19);
    }

    get min() {
        return this.__min.get();
    }

    set min(i19) {
        this.__min.set(i19);
    }

    get max() {
        return this.__max.get();
    }

    set max(h19) {
        this.__max.set(h19);
    }

    convertNumberToString(g19) {
        if (g19 >= 0 && g19 < CounterConstant.COUNTER_TEN_NUMBER) {
            return this.numberStrList[g19];
        }
        else {
            return g19.toString();
        }
    }

    aboutToAppear() {
        let f19 = new Date();
        this.timeStamp = f19.getTime();
        if (this.options !== undefined && this.options !== null) {
            this.onOptionsChange();
        }
    }

    updateNumberStyleOptions() {
        if (this.numberStyleOptions.label === undefined) {
            this.numberStyleOptions.label = '';
        }
        if (this.value === undefined) {
            this.value = this.numberStyleOptions.value !== undefined ? this.numberStyleOptions.value : 0;
            this.onChange?.(this.value);
            this.inputValue = this.value.toString();
        }
        if (this.numberStyleOptions.min !== undefined) {
            this.min = this.numberStyleOptions.min;
        }
        if (this.numberStyleOptions.max !== undefined) {
            this.max = this.numberStyleOptions.max;
        }
        if (this.min > this.max) {
            this.min = this.max;
        }
        if (this.numberStyleOptions.textWidth !== undefined) {
            this.textWidth = this.numberStyleOptions.textWidth;
            if (this.textWidth < 0) {
                this.textWidth = 0;
            }
            this.hasTextWidth = true;
        }
        if (this.value <= this.min) {
            this.value = this.min;
            this.onChange?.(this.value);
            this.inputValue = this.value.toString();
        }
        if (this.value >= this.max) {
            this.value = this.max;
            this.onChange?.(this.value);
            this.inputValue = this.value.toString();
        }
        if (this.numberStyleOptions.step !== undefined) {
            if (this.numberStyleOptions.step < 1) {
                this.step = 1;
            }
            else {
                this.step = this.numberStyleOptions.step;
            }
        }
        this.updateButtonStatus();
        this.updateNumberStyleOptionsEvent();
    }

    updateNumberStyleOptionsEvent() {
        if (this.numberStyleOptions.onHoverIncrease !== undefined) {
            this.onHoverIncrease = this.numberStyleOptions.onHoverIncrease;
        }
        if (this.numberStyleOptions.onHoverDecrease !== undefined) {
            this.onHoverDecrease = this.numberStyleOptions.onHoverDecrease;
        }
        if (this.numberStyleOptions.onFocusIncrease !== undefined) {
            this.onFocusIncrease = this.numberStyleOptions.onFocusIncrease;
        }
        if (this.numberStyleOptions.onFocusDecrease !== undefined) {
            this.onFocusDecrease = this.numberStyleOptions.onFocusDecrease;
        }
        if (this.numberStyleOptions.onBlurIncrease !== undefined) {
            this.onBlurIncrease = this.numberStyleOptions.onBlurIncrease;
        }
        if (this.numberStyleOptions.onBlurDecrease !== undefined) {
            this.onBlurDecrease = this.numberStyleOptions.onBlurDecrease;
        }
        if (this.numberStyleOptions.onChange !== undefined) {
            this.onChange = this.numberStyleOptions.onChange;
        }
        if (this.numberStyleOptions.focusable !== undefined) {
            this.focusEnable = this.numberStyleOptions.focusable;
        }
    }

    updateInlineStyleOptions() {
        if (this.value === undefined) {
            this.value = this.inlineStyleOptions.value !== undefined ? this.inlineStyleOptions.value : 0;
            this.onChange?.(this.value);
            this.inputValue = this.value.toString();
        }
        if (this.inlineStyleOptions.min !== undefined) {
            this.min = this.inlineStyleOptions.min;
        }
        if (this.inlineStyleOptions.max !== undefined) {
            this.max = this.inlineStyleOptions.max;
        }
        if (this.min > this.max) {
            this.min = this.max;
        }
        if (this.inlineStyleOptions.textWidth !== undefined) {
            this.textWidth = this.inlineStyleOptions.textWidth;
            if (this.textWidth < 0) {
                this.textWidth = 0;
            }
            this.hasTextWidth = true;
        }
        if (this.value <= this.min) {
            this.value = this.min;
            this.onChange?.(this.value);
            this.inputValue = this.value.toString();
        }
        if (this.value >= this.max) {
            this.value = this.max;
            this.onChange?.(this.value);
            this.inputValue = this.value.toString();
        }
        if (this.inlineStyleOptions.step !== undefined) {
            if (this.inlineStyleOptions.step < 1) {
                this.step = 1;
            }
            else {
                this.step = this.inlineStyleOptions.step;
            }
        }
        this.updateButtonStatus();
        this.updateInlineStyleOptionsEvent();
    }

    updateInlineStyleOptionsEvent() {
        if (this.inlineStyleOptions.onHoverIncrease !== undefined) {
            this.onHoverIncrease = this.inlineStyleOptions.onHoverIncrease;
        }
        if (this.inlineStyleOptions.onHoverDecrease !== undefined) {
            this.onHoverDecrease = this.inlineStyleOptions.onHoverDecrease;
        }
        if (this.inlineStyleOptions.onChange !== undefined) {
            this.onChange = this.inlineStyleOptions.onChange;
        }
        if (this.inlineStyleOptions.focusable !== undefined) {
            this.focusEnable = this.inlineStyleOptions.focusable;
        }
    }

    updateDateStyleOptions() {
        if (this.dateStyleOptions.step !== undefined) {
            if (this.dateStyleOptions.step < 1) {
                this.step = 1;
            }
            else {
                this.step = this.dateStyleOptions.step;
            }
        }
        if (this.dateStyleOptions.onHoverIncrease !== undefined) {
            this.onHoverIncrease = this.dateStyleOptions.onHoverIncrease;
        }
        if (this.dateStyleOptions.onHoverDecrease !== undefined) {
            this.onHoverDecrease = this.dateStyleOptions.onHoverDecrease;
        }
        if (this.dateStyleOptions.year !== undefined &&
            this.dateStyleOptions.year >= this.minYear &&
            this.dateStyleOptions.year <= this.maxYear) {
            if (this.year === 0) {
                this.year = this.dateStyleOptions.year;
            }
        }
        else {
            this.year = CounterConstant.COUNTER_MIN_YEAR;
        }
        if (this.dateStyleOptions.month !== undefined &&
            this.dateStyleOptions.month <= CounterConstant.COUNTER_MAX_MONTH &&
            this.dateStyleOptions.month >= CounterConstant.COUNTER_MIN_MONTH) {
            if (this.month === 0) {
                this.month = this.dateStyleOptions.month;
            }
        }
        else {
            this.month = CounterConstant.COUNTER_INITIAL_MONTH;
        }
        if (this.dateStyleOptions.day !== undefined &&
            this.dateStyleOptions.day <= this.getDayNumber() &&
            this.dateStyleOptions.day >= CounterConstant.COUNTER_MIN_DAY) {
            if (this.day === 0) {
                this.day = this.dateStyleOptions.day;
            }
        }
        else {
            this.day = CounterConstant.COUNTER_INITIAL_DAY;
        }
        if (this.dateStyleOptions.onDateChange !== undefined) {
            this.onDateChange = this.dateStyleOptions.onDateChange;
        }
        if (this.dateStyleOptions.focusable !== undefined) {
            this.focusEnable = this.dateStyleOptions.focusable;
        }
        this.updateDay();
    }

    onOptionsChange() {
        this.type = this.options.type;
        if (this.options.direction) {
            this.counterDirection = this.options.direction;
        }
        else {
            this.counterDirection = Direction.Auto;
        }
        if (this.type === CounterType.LIST ||
            this.type === CounterType.COMPACT) {
            this.numberStyleOptions = this.options.numberOptions;
            this.updateNumberStyleOptions();
        }
        else if (this.type === CounterType.INLINE) {
            this.inlineStyleOptions = this.options.inlineOptions;
            this.updateInlineStyleOptions();
        }
        else if (this.type === CounterType.INLINE_DATE) {
            let y18 = this.options.dateOptions;
            y18.year = y18.year ? y18.year : CounterConstant.COUNTER_MIN_YEAR;
            y18.month = y18.month ? y18.month : CounterConstant.COUNTER_MIN_MONTH;
            y18.day = y18.day ? y18.day : CounterConstant.COUNTER_MIN_DAY;
            this.dateStyleOptions = y18;
            this.updateDateStyleOptions();
        }
        else {
        }
    }

    subValue() {
        if (this.subBtnStateEffect) {
            this.value -= this.step;
        }
        if (!this.addBtnStateEffect) {
            this.addBtnStateEffect = true;
            this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            this.addBtnEnabled = true;
        }
        if (this.value <= this.min) {
            this.value = this.min;
            this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.subBtnStateEffect = false;
            this.subBtnEnabled = false;
        }
        else {
            if (this.subOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
                this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            }
            if (!this.subBtnStateEffect) {
                this.subBtnStateEffect = true;
            }
            if (!this.subBtnEnabled) {
                this.subBtnEnabled = true;
            }
        }
        this.focusText1();
    }

    focusText1() {
        if (this.type === CounterType.INLINE) {
            if (this.focusText === FocusText.NONE) {
                this.focusText = FocusText.TEXT1;
                this.hasFocusText1 = true;
                this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
            }
        }
    }

    addValue() {
        if (this.addBtnStateEffect) {
            this.value += this.step;
        }
        if (!this.subBtnStateEffect) {
            this.subBtnStateEffect = true;
            this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            this.subBtnEnabled = true;
        }
        if (this.value >= this.max) {
            this.value = this.max;
            this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.addBtnStateEffect = false;
            this.addBtnEnabled = false;
        }
        else {
            if (this.addOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
                this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            }
            if (!this.addBtnStateEffect) {
                this.addBtnStateEffect = true;
            }
            if (!this.addBtnEnabled) {
                this.addBtnEnabled = true;
            }
        }
        this.focusText1();
    }

    getDayNumber() {
        switch (this.month) {
            case CounterConstant.JANUARY:
            case CounterConstant.MARCH:
            case CounterConstant.MAY:
            case CounterConstant.JULY:
            case CounterConstant.AUGUST:
            case CounterConstant.OCTOBER:
            case CounterConstant.DECEMBER:
                return CounterConstant.BIG_MONTH_DAYS;
                break;
            case CounterConstant.APRIL:
            case CounterConstant.JUNE:
            case CounterConstant.SEPTEMBER:
            case CounterConstant.NOVEMBER:
                return CounterConstant.SMALL_MONTH_DAYS;
                break;
            case CounterConstant.FEBRUARY:
                if ((this.year % CounterConstant.AUSPICIOUS_FOUR === 0 &&
                    this.year % CounterConstant.AUSPICIOUS_HUNDRED !== 0) ||
                    this.year % CounterConstant.AUSPICIOUS_FOUR_HUNDRED === 0) {
                    return CounterConstant.AUSPICIOUS_FEBRUARY_DAYS;
                }
                else {
                    return CounterConstant.FEBRUARY_DAYS;
                }
                break;
            default:
                break;
        }
    }

    subDate() {
        if (this.focusText === FocusText.TEXT1) {
            if (this.subBtnStateEffect) {
                this.inputYear = this.year;
                this.year -= this.step;
                if (!this.hasFocusText1) {
                    this.hasFocusText1 = true;
                }
            }
            if (!this.addBtnStateEffect) {
                this.addBtnStateEffect = true;
                this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                this.addBtnEnabled = true;
            }
            if (this.year <= this.minYear) {
                this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                this.subBtnStateEffect = false;
                this.subBtnEnabled = false;
            }
            else {
                if (this.subOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
                    this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                }
                if (!this.subBtnStateEffect) {
                    this.subBtnStateEffect = true;
                }
                if (!this.subBtnEnabled) {
                    this.subBtnEnabled = true;
                }
            }
        }
        else if (this.focusText === FocusText.TEXT2) {
            this.month -= this.step % CounterConstant.COUNTER_MAX_MONTH;
            if (this.month < CounterConstant.COUNTER_MIN_MONTH) {
                this.month += CounterConstant.COUNTER_MAX_MONTH;
            }
            if (!this.hasFocusText2) {
                this.hasFocusText2 = true;
            }
        }
        else if (this.focusText === FocusText.TEXT3) {
            this.day -= this.step % this.getDayNumber();
            if (this.day < CounterConstant.COUNTER_MIN_DAY) {
                this.day += this.getDayNumber();
            }
            if (!this.hasFocusText3) {
                this.hasFocusText3 = true;
            }
        }
        else {
            this.focusDayWitdhSub();
        }
    }

    focusDayWitdhSub() {
        this.focusText = FocusText.TEXT3;
        this.hasFocusText3 = true;
        this.day -= this.step % this.getDayNumber();
        if (this.day < CounterConstant.COUNTER_MIN_DAY) {
            this.day += this.getDayNumber();
        }
        this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
    }

    addDate() {
        if (this.focusText === FocusText.TEXT1) {
            if (this.addBtnStateEffect) {
                this.inputYear = this.year;
                this.year += this.step;
                if (!this.hasFocusText1) {
                    this.hasFocusText1 = true;
                }
            }
            if (!this.subBtnStateEffect) {
                this.subBtnStateEffect = true;
                this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                this.subBtnEnabled = true;
            }
            if (this.year >= this.maxYear) {
                this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                this.addBtnStateEffect = false;
                this.addBtnEnabled = false;
            }
            else {
                if (this.addOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
                    this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                }
                if (!this.addBtnStateEffect) {
                    this.addBtnStateEffect = true;
                }
                if (!this.addBtnEnabled) {
                    this.addBtnEnabled = true;
                }
            }
        }
        else if (this.focusText === FocusText.TEXT2) {
            this.month += this.step % CounterConstant.COUNTER_MAX_MONTH;
            if (this.month > CounterConstant.COUNTER_MAX_MONTH) {
                this.month -= CounterConstant.COUNTER_MAX_MONTH;
            }
            if (!this.hasFocusText2) {
                this.hasFocusText2 = true;
            }
        }
        else if (this.focusText === FocusText.TEXT3) {
            this.day += this.step % this.getDayNumber();
            if (this.day > this.getDayNumber()) {
                this.day -= this.getDayNumber();
            }
            if (!this.hasFocusText3) {
                this.hasFocusText3 = true;
            }
        }
        else {
            this.focusDayWithAdd();
        }
    }

    focusDayWithAdd() {
        this.focusText = FocusText.TEXT3;
        this.hasFocusText3 = true;
        this.day += this.step % this.getDayNumber();
        if (this.day > this.getDayNumber()) {
            this.day -= this.getDayNumber();
        }
        this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
    }

    updateInlineEnableSate() {
        if (this.value >= this.max) {
            this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.addBtnStateEffect = false;
            this.addBtnEnabled = false;
        }
        else {
            this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            this.addBtnStateEffect = true;
            this.addBtnEnabled = true;
        }
        if (this.value <= this.min) {
            this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.subBtnStateEffect = false;
            this.subBtnEnabled = false;
        }
        else {
            this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            this.subBtnStateEffect = true;
            this.subBtnEnabled = true;
        }
    }

    updateDateEnableSate() {
        if (this.year === this.maxYear && this.focusText === FocusText.TEXT1) {
            this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.addBtnStateEffect = false;
            this.addBtnEnabled = false;
        }
        else {
            if (this.addOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
                this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            }
            if (!this.addBtnStateEffect) {
                this.addBtnStateEffect = true;
            }
            if (!this.addBtnEnabled) {
                this.addBtnEnabled = true;
            }
        }
        if (this.year === this.minYear && this.focusText === FocusText.TEXT1) {
            this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.subBtnStateEffect = false;
            this.subBtnEnabled = false;
        }
        else {
            if (this.subOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
                this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            }
            if (!this.subBtnStateEffect) {
                this.subBtnStateEffect = true;
            }
            if (!this.subBtnEnabled) {
                this.subBtnEnabled = true;
            }
        }
    }

    updateDay() {
        if (this.day > this.getDayNumber()) {
            this.day = this.getDayNumber();
        }
    }

    resetFocusText() {
        this.focusText = FocusText.NONE;
        this.hasFocusText1 = false;
        this.hasFocusText2 = false;
        this.hasFocusText3 = false;
    }

    resetFocusButton() {
        if (this.addBtnFocusWidh === CounterResource.BUTTON_BORDER_FOCUSED_WIDTH) {
            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
            this.onBlurIncrease && this.onBlurIncrease();
        }
        if (this.subBtnFocusWidh === CounterResource.BUTTON_BORDER_FOCUSED_WIDTH) {
            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
            this.onBlurDecrease && this.onBlurDecrease();
        }
    }

    homeFocusText() {
        this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
    }

    endFocusText() {
        this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
    }

    homeFirstValue() {
        this.value = this.min;
        if (!this.addBtnStateEffect) {
            this.addBtnStateEffect = true;
            this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            this.addBtnEnabled = true;
        }
    }

    endLastValue() {
        this.value = this.max;
        if (!this.subBtnStateEffect) {
            this.subBtnStateEffect = true;
            this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            this.subBtnEnabled = true;
        }
    }

    updateButtonStatus() {
        if (this.value <= this.min) {
            if (!this.addBtnStateEffect && this.max != this.min) {
                this.addBtnStateEffect = true;
                this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                this.addBtnEnabled = true;
            }
            this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.subBtnStateEffect = false;
            this.subBtnEnabled = false;
        }
        if (this.value >= this.max) {
            if (!this.subBtnStateEffect && this.max != this.min) {
                this.subBtnStateEffect = true;
                this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                this.subBtnEnabled = true;
            }
            this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.addBtnStateEffect = false;
            this.addBtnEnabled = false;
        }
    }

    getValue() {
        if (this.inputValue == undefined) {
            this.inputValue = '';
        }
        return this.hasInputText1 ? this.inputValue : this.value.toString();
    }

    getValueLength() {
        return this.getValue().length > 0 ? this.getValue().length : 1;
    }

    getYear() {
        let x18 = this.year.toString();
        if (x18.length === 1) {
            x18 = '000' + x18;
        }
        else if (x18.length === 2) {
            x18 = '00' + x18;
        }
        else if (x18.length === 3) {
            x18 = '0' + x18;
        }
        else {
            x18 = x18;
        }
        return x18;
    }

    focusWithTarget(u18) {
        setTimeout(() => {
            var w18 = focusControl.requestFocus(u18);
            if (w18) {
                console.log('Request success');
            }
            else {
                console.log('Request failed');
            }
        });
    }

    focusCurrentText(t18) {
        if (t18 === FocusText.TEXT1) {
            if (this.focusText === FocusText.NONE) {
                this.focusText = FocusText.TEXT1;
            }
            if (!this.hasFocusText1) {
                this.hasFocusText1 = true;
            }
        }
        else if (t18 === FocusText.TEXT2) {
            if (this.focusText === FocusText.NONE) {
                this.focusText = FocusText.TEXT2;
            }
            if (!this.hasFocusText2) {
                this.hasFocusText2 = true;
            }
        }
        else if (t18 === FocusText.TEXT3) {
            if (this.focusText === FocusText.NONE) {
                this.focusText = FocusText.TEXT3;
            }
            if (!this.hasFocusText3) {
                this.hasFocusText3 = true;
            }
        }
        else {
        }
    }

    getMaxLength() {
        if (this.max.toString().length > this.min.toString().length) {
            return this.max.toString().length + 1;
        }
        else {
            return this.min.toString().length + 1;
        }
    }

    resourceToVp(r18) {
        try {
            if (r18.id !== -1) {
                return px2vp(getContext(this).resourceManager.getNumber(r18.id));
            }
            else {
                return px2vp(getContext(this)
                    .resourceManager
                    .getNumberByName((r18.params[0]).split('.')[2]));
            }
        }
        catch (s18) {
            return CounterResource.COUNTER_LIST_PADDING;
        }
    }

    initialRender() {
        this.observeComponentCreation2((g6, h6) => {
            If.create();
            if (this.type === CounterType.LIST) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p18, q18) => {
                        RelativeContainer.create();
                        RelativeContainer.direction(this.counterDirection);
                        RelativeContainer.width('100%');
                        RelativeContainer.height(CounterResource.COUNTER_LIST_HEIGHT);
                    }, RelativeContainer);
                    this.observeComponentCreation2((n18, o18) => {
                        Text.create(this.numberStyleOptions.label);
                        Text.direction(this.counterDirection);
                        Text.fontSize(CounterResource.COUNTER_LIST_LABEL_SIZE);
                        Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                        Text.margin({
                            start: LengthMetrics.vp(this.resourceToVp(CounterResource.COUNTER_LIST_LEFT_PADDING))
                        });
                        Text.alignRules({
                            center: { anchor: '__container__', align: VerticalAlign.Center },
                            start: { anchor: '__container__', align: HorizontalAlign.Start },
                            end: { anchor: 'Row1', align: HorizontalAlign.Start }
                        });
                        Text.id('Text');
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((l18, m18) => {
                        Row.create();
                        Row.direction(this.counterDirection);
                        Row.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                        Row.margin({
                            end: LengthMetrics.vp(this.resourceToVp(CounterResource.COUNTER_LIST_RIGHT_PADDING))
                        });
                        Row.alignRules({
                            center: { anchor: '__container__', align: VerticalAlign.Center },
                            end: { anchor: '__container__', align: HorizontalAlign.End }
                        });
                        Row.tabIndex(0);
                        Row.id('Row1');
                    }, Row);
                    this.observeComponentCreation2((j18, k18) => {
                        Stack.create();
                        Stack.direction(this.counterDirection);
                        Stack.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                        Stack.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                        Stack.borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS);
                        Stack.borderWidth(this.subBtnFocusWidh);
                        Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((h18, i18) => {
                        Image.create(CounterResource.BUTTON_SUB_ICON);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
                        Image.height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.subOpacity);
                    }, Image);
                    this.observeComponentCreation2((v17, w17) => {
                        Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                        Button.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                        Button.responseRegion({
                            x: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_X,
                            y: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_Y,
                            width: '150%',
                            height: '150%'
                        });
                        Button.groupDefaultFocus(true);
                        Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
                        Button.opacity(this.subOpacity);
                        Button.enabled(this.subBtnEnabled);
                        Button.key('ListSubButton' + this.timeStamp.toString());
                        Button.onKeyEvent((g18) => {
                            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            if (g18.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusButton();
                                g18.stopPropagation();
                            }
                            if (g18.type === KeyType.Down &&
                                g18.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                g18.stopPropagation();
                                this.homeFirstValue();
                                this.focusWithTarget('ListAddButton' + this.timeStamp.toString());
                            }
                            if (g18.type === KeyType.Down &&
                                g18.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                g18.stopPropagation();
                                if (this.addBtnStateEffect) {
                                    this.addBtnStateEffect = false;
                                    this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                                    this.addBtnEnabled = false;
                                }
                                this.endLastValue();
                                this.focusWithTarget('ListAddButton' + this.timeStamp.toString());
                            }
                        });
                        Button.onClick((f18) => {
                            this.subValue();
                            this.onChange?.(ObservedObject.GetRawObject(this.value));
                            if (f18.source === SourceType.Mouse ||
                                f18.source === SourceType.TouchScreen) {
                                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((e18) => {
                            if (e18.repeat) {
                                this.subValue();
                                this.onChange?.(ObservedObject.GetRawObject(this.value));
                            }
                            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((d18) => {
                            this.onHoverDecrease && this.onHoverDecrease(d18);
                        });
                        Button.focusable(this.focusEnable);
                        Button.onFocus(() => {
                            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusDecrease && this.onFocusDecrease();
                            this.updateButtonStatus();
                        });
                        Button.onBlur(() => {
                            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurDecrease && this.onBlurDecrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    this.observeComponentCreation2((l17, m17) => {
                        If.create();
                        if (this.hasTextWidth) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((t17, u17) => {
                                    Text.create(this.value.toString());
                                    Text.direction(this.counterDirection);
                                    Text.width(this.textWidth.toString());
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE);
                                    Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                                    Text.margin({
                                        start: LengthMetrics.vp(CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN),
                                        end: LengthMetrics.vp(CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN)
                                    });
                                }, Text);
                                Text.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((p17, q17) => {
                                    Text.create(this.value.toString());
                                    Text.direction(this.counterDirection);
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE);
                                    Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                                    Text.margin({
                                        start: LengthMetrics.vp(CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN),
                                        end: LengthMetrics.vp(CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN)
                                    });
                                }, Text);
                                Text.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((j17, k17) => {
                        Stack.create();
                        Stack.direction(this.counterDirection);
                        Stack.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                        Stack.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                        Stack.borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS);
                        Stack.borderWidth(this.addBtnFocusWidh);
                        Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((h17, i17) => {
                        Image.create(CounterResource.BUTTON_ADD_ICON);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
                        Image.height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.addOpacity);
                    }, Image);
                    this.observeComponentCreation2((v16, w16) => {
                        Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                        Button.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                        Button.responseRegion({
                            x: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_X,
                            y: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_Y,
                            width: '150%',
                            height: '150%'
                        });
                        Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
                        Button.opacity(this.addOpacity);
                        Button.enabled(this.addBtnEnabled);
                        Button.key('ListAddButton' + this.timeStamp.toString());
                        Button.onKeyEvent((g17) => {
                            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            if (g17.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusButton();
                                g17.stopPropagation();
                            }
                            if (g17.type === KeyType.Down &&
                                g17.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                g17.stopPropagation();
                                this.homeFirstValue();
                                if (this.subBtnStateEffect) {
                                    this.subBtnStateEffect = false;
                                    this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                                    this.subBtnEnabled = false;
                                }
                                this.focusWithTarget('ListAddButton' + this.timeStamp.toString());
                            }
                            if (g17.type === KeyType.Down &&
                                g17.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                g17.stopPropagation();
                                this.endLastValue();
                                this.focusWithTarget('ListSubButton' + this.timeStamp.toString());
                            }
                        });
                        Button.onClick((f17) => {
                            this.addValue();
                            this.onChange?.(ObservedObject.GetRawObject(this.value));
                            if (f17.source === SourceType.Mouse ||
                                f17.source === SourceType.TouchScreen) {
                                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((e17) => {
                            if (e17.repeat) {
                                this.addValue();
                                this.onChange?.(ObservedObject.GetRawObject(this.value));
                            }
                            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((d17) => {
                            this.onHoverIncrease && this.onHoverIncrease(d17);
                        });
                        Button.focusable(this.focusEnable);
                        Button.onFocus(() => {
                            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusIncrease && this.onFocusIncrease();
                            this.updateButtonStatus();
                        });
                        Button.onBlur(() => {
                            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurIncrease && this.onBlurIncrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    Row.pop();
                    RelativeContainer.pop();
                });
            }
            else if (this.type === CounterType.COMPACT) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((i16, j16) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((g16, h16) => {
                        Row.create();
                        Row.direction(this.counterDirection);
                        Row.tabIndex(0);
                        Row.height(CounterResource.COUNTER_COMPACT_CONTAINER_HEIGHT);
                        Row.align(Alignment.Center);
                        Row.borderWidth(CounterResource.COUNTER_BORDER_WIDTH);
                        Row.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                        Row.borderRadius(CounterResource.COUNTER_COMPACT_CONTAINER_RADIUS);
                    }, Row);
                    this.observeComponentCreation2((e16, f16) => {
                        Stack.create();
                        Stack.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Stack.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Stack.borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS);
                        Stack.borderWidth(this.subBtnFocusWidh);
                        Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Stack.margin({ start: LengthMetrics.vp(1) });
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((c16, d16) => {
                        Image.create(CounterResource.BUTTON_SUB_ICON);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
                        Image.height(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.subOpacity);
                    }, Image);
                    this.observeComponentCreation2((q15, r15) => {
                        Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Button.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
                        Button.opacity(this.subOpacity);
                        Button.enabled(this.subBtnEnabled);
                        Button.key('CompactSubButton' + this.timeStamp.toString());
                        Button.onKeyEvent((b16) => {
                            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            if (b16.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusButton();
                                b16.stopPropagation();
                            }
                            if (b16.type === KeyType.Down &&
                                b16.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                b16.stopPropagation();
                                this.homeFirstValue();
                                this.focusWithTarget('CompactAddButton' + this.timeStamp.toString());
                            }
                            if (b16.type === KeyType.Down &&
                                b16.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                b16.stopPropagation();
                                this.endLastValue();
                                if (this.addBtnStateEffect) {
                                    this.addBtnStateEffect = false;
                                    this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                                    this.addBtnEnabled = false;
                                }
                                this.focusWithTarget('CompactSubButton' + this.timeStamp.toString());
                            }
                        });
                        Button.onClick((a16) => {
                            this.subValue();
                            this.onChange?.(ObservedObject.GetRawObject(this.value));
                            if (a16.source === SourceType.Mouse ||
                                a16.source === SourceType.TouchScreen) {
                                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((z15) => {
                            if (z15.repeat) {
                                this.subValue();
                                this.onChange?.(ObservedObject.GetRawObject(this.value));
                            }
                            if (z15.source === SourceType.Mouse ||
                                z15.source === SourceType.TouchScreen) {
                                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((y15) => {
                            this.onHoverDecrease && this.onHoverDecrease(y15);
                        });
                        Button.focusable(this.focusEnable);
                        Button.groupDefaultFocus(true);
                        Button.onFocus(() => {
                            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusDecrease && this.onFocusDecrease();
                            this.updateButtonStatus();
                        });
                        Button.onBlur(() => {
                            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurDecrease && this.onBlurDecrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    this.observeComponentCreation2((g15, h15) => {
                        If.create();
                        if (this.hasTextWidth) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((o15, p15) => {
                                    Text.create(this.value.toString());
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                                    Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                                    Text.width(this.textWidth.toString());
                                    Text.margin({
                                        start: LengthMetrics.vp(CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN),
                                        end: LengthMetrics.vp(CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN)
                                    });
                                }, Text);
                                Text.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((k15, l15) => {
                                    Text.create(this.value.toString());
                                    Text.direction(this.counterDirection);
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                                    Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                                    Text.margin({
                                        start: LengthMetrics.vp(CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN),
                                        end: LengthMetrics.vp(CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN)
                                    });
                                }, Text);
                                Text.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((e15, f15) => {
                        Stack.create();
                        Stack.direction(this.counterDirection);
                        Stack.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Stack.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Stack.borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS);
                        Stack.borderWidth(this.addBtnFocusWidh);
                        Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Stack.margin({ end: LengthMetrics.vp(1) });
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((c15, d15) => {
                        Image.create(CounterResource.BUTTON_ADD_ICON);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
                        Image.height(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.addOpacity);
                    }, Image);
                    this.observeComponentCreation2((q14, r14) => {
                        Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Button.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
                        Button.opacity(this.addOpacity);
                        Button.enabled(this.addBtnEnabled);
                        Button.key('CompactAddButton' + this.timeStamp.toString());
                        Button.onKeyEvent((b15) => {
                            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            if (b15.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusButton();
                                b15.stopPropagation();
                            }
                            if (b15.type === KeyType.Down &&
                                b15.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                b15.stopPropagation();
                                this.homeFirstValue();
                                if (this.subBtnStateEffect) {
                                    this.subBtnStateEffect = false;
                                    this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                                    this.subBtnEnabled = false;
                                }
                                this.focusWithTarget('CompactAddButton' + this.timeStamp.toString());
                            }
                            if (b15.type === KeyType.Down &&
                                b15.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                b15.stopPropagation();
                                this.endLastValue();
                                this.focusWithTarget('CompactSubButton' + this.timeStamp.toString());
                            }
                        });
                        Button.onClick((a15) => {
                            this.addValue();
                            this.onChange?.(ObservedObject.GetRawObject(this.value));
                            if (a15.source === SourceType.Mouse ||
                                a15.source === SourceType.TouchScreen) {
                                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((z14) => {
                            if (z14.repeat) {
                                this.addValue();
                                this.onChange?.(ObservedObject.GetRawObject(this.value));
                            }
                            if (z14.source === SourceType.Mouse ||
                                z14.source === SourceType.TouchScreen) {
                                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((y14) => {
                            this.onHoverIncrease && this.onHoverIncrease(y14);
                        });
                        Button.focusable(this.focusEnable);
                        Button.onFocus(() => {
                            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusIncrease && this.onFocusIncrease();
                            this.updateButtonStatus();
                        });
                        Button.onBlur(() => {
                            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurIncrease && this.onBlurIncrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    Row.pop();
                    this.observeComponentCreation2((o14, p14) => {
                        Text.create(this.numberStyleOptions.label);
                        Text.direction(this.counterDirection);
                        Text.margin({ top: CounterResource.COUNTER_COMPACT_CONTAINER_LABEL_DISTANCE });
                        Text.fontSize(CounterResource.COUNTER_COMPACT_LABEL_SIZE);
                        Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                        Text.align(Alignment.Top);
                    }, Text);
                    Text.pop();
                    Column.pop();
                });
            }
            else if (this.type === CounterType.INLINE) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((b14, c14) => {
                        Row.create();
                        Row.direction(this.counterDirection);
                        Row.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                        Row.borderWidth(CounterResource.COUNTER_BORDER_WIDTH);
                        Row.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                        Row.borderRadius(CounterResource.COUNTER_INLINE_RADIUS);
                        Row.clip(true);
                    }, Row);
                    this.observeComponentCreation2((j12, k12) => {
                        If.create();
                        if (this.hasTextWidth) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((z13, a14) => {
                                    RelativeContainer.create();
                                    RelativeContainer.direction(this.counterDirection);
                                    RelativeContainer.margin({
                                        start: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN),
                                        end: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN)
                                    });
                                    RelativeContainer.height('100%');
                                    RelativeContainer.width(this.textWidth);
                                }, RelativeContainer);
                                this.observeComponentCreation2((j13, k13) => {
                                    TextInput.create({
                                        text: this.hasInputText1 ? this.inputValue : this.value.toString(),
                                        controller: this.controller1
                                    });
                                    TextInput.alignRules({
                                        center: { anchor: '__container__', align: VerticalAlign.Center },
                                        middle: { anchor: '__container__', align: HorizontalAlign.Center }
                                    });
                                    TextInput.width(Math.min(this.getValueLength() * 9.6, this.textWidth));
                                    TextInput.height('20vp');
                                    TextInput.padding(0);
                                    TextInput.borderRadius(0);
                                    TextInput.textAlign(TextAlign.Center);
                                    TextInput.type(InputType.PhoneNumber);
                                    TextInput.caretColor(Color.Transparent);
                                    TextInput.copyOption(CopyOptions.None);
                                    TextInput.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                                    TextInput.fontWeight(FontWeight.Medium);
                                    TextInput.fontColor(this.hasFocusText1 ? Color.White : CounterResource.COUNTER_TEXT_COLOR);
                                    TextInput.maxLength(this.getMaxLength());
                                    TextInput.backgroundColor(this.hasFocusText1 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent);
                                    TextInput.key('InlineTextInput' + this.timeStamp.toString());
                                    TextInput.onKeyEvent((y13) => {
                                        this.focusCurrentText(FocusText.TEXT1);
                                        if (y13.keyCode === CounterConstant.KEYCODE_ESC) {
                                            this.resetFocusText();
                                            y13.stopPropagation();
                                        }
                                        if (y13.type === KeyType.Down &&
                                            y13.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                                            this.addValue();
                                            y13.stopPropagation();
                                        }
                                        if (y13.type === KeyType.Down &&
                                            y13.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                            y13.stopPropagation();
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                        }
                                        if (y13.type === KeyType.Down &&
                                            y13.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                            y13.stopPropagation();
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                        }
                                        if (y13.type === KeyType.Down &&
                                            y13.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                                            this.subValue();
                                            y13.stopPropagation();
                                        }
                                        if (y13.type === KeyType.Down &&
                                            y13.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                            y13.stopPropagation();
                                        }
                                        if (y13.type === KeyType.Down &&
                                            y13.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                            y13.stopPropagation();
                                        }
                                    });
                                    TextInput.onChange((t13) => {
                                        this.inputValue = t13;
                                        for (let w13 = 0; w13 < t13.length; w13++) {
                                            let x13 = t13[w13];
                                            if (x13 === '+' || x13 === '*' || x13 === '#') {
                                                this.value -= 1;
                                                this.value += 1;
                                                this.inputValue = this.value.toString();
                                                return;
                                            }
                                            if (x13 === '-' && w13 !== 0) {
                                                this.inputValue = x13;
                                                break;
                                            }
                                        }
                                        this.hasInputText1 = true;
                                        let u13 = t13[t13.length - 1];
                                        if (t13.length === this.getMaxLength()) {
                                            this.inputValue = u13;
                                        }
                                        if (this.timeoutID1 !== -1) {
                                            clearTimeout(this.timeoutID1);
                                            this.timeoutID1 = -1;
                                        }
                                        if (this.inputValue !== '' && Number(this.inputValue) <= this.max &&
                                            Number(this.inputValue) >= this.min) {
                                            this.value = Number(this.inputValue);
                                            this.onChange?.(ObservedObject.GetRawObject(this.value));
                                            this.hasInputText1 = false;
                                        }
                                        else {
                                            if (Number(this.inputValue) > this.max ||
                                                (Number(this.inputValue) < this.min &&
                                                    this.inputValue.length <= this.min.toString().length)) {
                                                this.inputValue = u13;
                                            }
                                            if (t13.length < this.getMaxLength()) {
                                                this.timeoutID1 = setTimeout(() => {
                                                    if (this.inputValue !== '' && Number(this.inputValue) <= this.max &&
                                                        Number(this.inputValue) >= this.min) {
                                                        this.value = Number(this.inputValue);
                                                        this.onChange?.(ObservedObject.GetRawObject(this.value));
                                                    }
                                                    this.inputValue = this.value.toString();
                                                    this.hasInputText1 = false;
                                                    this.updateInlineEnableSate();
                                                }, 1500);
                                            }
                                        }
                                        this.updateInlineEnableSate();
                                    });
                                    TextInput.onSubmit((s13) => {
                                        if (this.timeoutID1 != -1) {
                                            clearTimeout(this.timeoutID1);
                                            this.timeoutID1 = -1;
                                        }
                                        this.hasInputText1 = false;
                                        this.value -= 1;
                                        if (Number(this.inputValue) >= this.min && Number(this.inputValue) <= this.max) {
                                            this.value = Number(this.inputValue);
                                            this.onChange?.(ObservedObject.GetRawObject(this.value));
                                            this.updateInlineEnableSate();
                                        }
                                        else {
                                            this.value += 1;
                                            this.inputValue = this.value.toString();
                                        }
                                    });
                                    TextInput.focusable(true);
                                    TextInput.focusOnTouch(true);
                                    TextInput.onFocus(() => {
                                        this.focusText = FocusText.TEXT1;
                                        this.hasFocusText1 = true;
                                        this.controller1.caretPosition(this.value.toString().length);
                                    });
                                    TextInput.onBlur(() => {
                                        this.focusText = FocusText.NONE;
                                        this.hasFocusText1 = false;
                                    });
                                    TextInput.onClick((r13) => {
                                        this.focusText = FocusText.TEXT1;
                                        this.hasFocusText1 = true;
                                        this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                        this.controller1.caretPosition(this.value.toString().length);
                                    });
                                }, TextInput);
                                RelativeContainer.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((e13, f13) => {
                                    Row.create();
                                    Row.direction(this.counterDirection);
                                    Row.margin({
                                        start: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN),
                                        end: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN)
                                    });
                                }, Row);
                                this.observeComponentCreation2((o12, p12) => {
                                    TextInput.create({
                                        text: this.hasInputText1 ? this.inputValue : this.value.toString(),
                                        controller: this.controller1
                                    });
                                    TextInput.direction(this.counterDirection);
                                    TextInput.width(this.getValueLength() * 9.6);
                                    TextInput.height('20vp');
                                    TextInput.padding(0);
                                    TextInput.borderRadius(0);
                                    TextInput.textAlign(TextAlign.Center);
                                    TextInput.type(InputType.PhoneNumber);
                                    TextInput.caretColor(Color.Transparent);
                                    TextInput.copyOption(CopyOptions.None);
                                    TextInput.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                                    TextInput.fontWeight(FontWeight.Medium);
                                    TextInput.fontColor(this.hasFocusText1 ? Color.White : CounterResource.COUNTER_TEXT_COLOR);
                                    TextInput.maxLength(this.getMaxLength());
                                    TextInput.backgroundColor(this.hasFocusText1 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent);
                                    TextInput.key('InlineTextInput' + this.timeStamp.toString());
                                    TextInput.onKeyEvent((d13) => {
                                        this.focusCurrentText(FocusText.TEXT1);
                                        if (d13.keyCode === CounterConstant.KEYCODE_ESC) {
                                            this.resetFocusText();
                                            d13.stopPropagation();
                                        }
                                        if (d13.type === KeyType.Down &&
                                            d13.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                                            this.addValue();
                                            d13.stopPropagation();
                                        }
                                        if (d13.type === KeyType.Down &&
                                            d13.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                                            this.subValue();
                                            d13.stopPropagation();
                                        }
                                        if (d13.type === KeyType.Down &&
                                            d13.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                            d13.stopPropagation();
                                        }
                                        if (d13.type === KeyType.Down &&
                                            d13.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                            d13.stopPropagation();
                                        }
                                    });
                                    TextInput.onChange((y12) => {
                                        this.inputValue = y12;
                                        for (let b13 = 0; b13 < y12.length; b13++) {
                                            let c13 = y12[b13];
                                            if (c13 === '+' || c13 === '*' || c13 === '#') {
                                                this.value -= 1;
                                                this.value += 1;
                                                this.inputValue = this.value.toString();
                                                return;
                                            }
                                            if (c13 === '-' && b13 !== 0) {
                                                this.inputValue = c13;
                                                break;
                                            }
                                        }
                                        this.hasInputText1 = true;
                                        let z12 = y12[y12.length - 1];
                                        if (y12.length === this.getMaxLength()) {
                                            this.inputValue = z12;
                                        }
                                        if (this.timeoutID1 !== -1) {
                                            clearTimeout(this.timeoutID1);
                                            this.timeoutID1 = -1;
                                        }
                                        if (this.inputValue !== '' && Number(this.inputValue) <= this.max &&
                                            Number(this.inputValue) >= this.min) {
                                            this.value = Number(this.inputValue);
                                            this.onChange?.(ObservedObject.GetRawObject(this.value));
                                            this.hasInputText1 = false;
                                        }
                                        else {
                                            if (Number(this.inputValue) > this.max ||
                                                (Number(this.inputValue) < this.min &&
                                                    this.inputValue.length <= this.min.toString().length)) {
                                                this.inputValue = z12;
                                            }
                                            if (y12.length < this.getMaxLength()) {
                                                this.timeoutID1 = setTimeout(() => {
                                                    if (this.inputValue !== '' && Number(this.inputValue) <= this.max &&
                                                        Number(this.inputValue) >= this.min) {
                                                        this.value = Number(this.inputValue);
                                                        this.onChange?.(ObservedObject.GetRawObject(this.value));
                                                    }
                                                    this.inputValue = this.value.toString();
                                                    this.hasInputText1 = false;
                                                    this.updateInlineEnableSate();
                                                }, 1500);
                                            }
                                        }
                                        this.updateInlineEnableSate();
                                    });
                                    TextInput.onSubmit((x12) => {
                                        if (this.timeoutID1 !== -1) {
                                            clearTimeout(this.timeoutID1);
                                            this.timeoutID1 = -1;
                                        }
                                        this.hasInputText1 = false;
                                        this.value -= 1;
                                        if (Number(this.inputValue) >= this.min && Number(this.inputValue) <= this.max) {
                                            this.value = Number(this.inputValue);
                                            this.onChange?.(ObservedObject.GetRawObject(this.value));
                                            this.updateInlineEnableSate();
                                        }
                                        else {
                                            this.value += 1;
                                            this.inputValue = this.value.toString();
                                        }
                                    });
                                    TextInput.focusable(true);
                                    TextInput.focusOnTouch(true);
                                    TextInput.onFocus(() => {
                                        this.focusText = FocusText.TEXT1;
                                        this.hasFocusText1 = true;
                                        this.controller1.caretPosition(this.value.toString().length);
                                    });
                                    TextInput.onBlur(() => {
                                        this.focusText = FocusText.NONE;
                                        this.hasFocusText1 = false;
                                    });
                                    TextInput.onClick((w12) => {
                                        this.focusText = FocusText.TEXT1;
                                        this.hasFocusText1 = true;
                                        this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                        this.controller1.caretPosition(this.value.toString().length);
                                    });
                                }, TextInput);
                                Row.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((h12, i12) => {
                        Column.create();
                        Column.direction(this.counterDirection);
                        Column.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Column.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                        Column.borderWidth({ start: LengthMetrics.vp(CounterResource.COUNTER_BORDER_WIDTH_NUMBER) });
                        Column.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                    }, Column);
                    this.observeComponentCreation2((f12, g12) => {
                        Stack.create();
                        Stack.direction(this.counterDirection);
                        Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Stack.padding({ top: '1vp' });
                        Stack.borderWidth({ bottom: '1vp' });
                        Stack.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((d12, e12) => {
                        Rect.create();
                        Rect.direction(this.counterDirection);
                        Rect.width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH);
                        Rect.height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT);
                        Rect.radius([
                            ['0vp', '0vp'],
                            [CounterResource.COUNTER_INLINE_RADIUS, CounterResource.COUNTER_INLINE_RADIUS],
                            ['0vp', '0vp'],
                            ['0vp', '0vp']
                        ]);
                        Rect.strokeWidth(this.addBtnFocusWidh);
                        Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Rect.margin({ end: LengthMetrics.vp(2) });
                        Rect.fillOpacity(0);
                    }, Rect);
                    this.observeComponentCreation2((b12, c12) => {
                        Image.create(CounterResource.BUTTON_ARROW_UP);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
                        Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.addOpacity);
                    }, Image);
                    this.observeComponentCreation2((r11, s11) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Button.backgroundColor(Color.Transparent);
                        Button.opacity(this.addOpacity);
                        Button.enabled(this.addBtnEnabled);
                        Button.onClick((a12) => {
                            this.addValue();
                            if (a12.source === SourceType.Mouse ||
                                a12.source === SourceType.TouchScreen) {
                                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((z11) => {
                            if (z11.repeat) {
                                this.addValue();
                            }
                            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((y11) => {
                            this.onHoverIncrease && this.onHoverIncrease(y11);
                        });
                        Button.focusable(false);
                        Button.onFocus(() => {
                            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusIncrease && this.onFocusIncrease();
                        });
                        Button.onBlur(() => {
                            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurIncrease && this.onBlurIncrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    this.observeComponentCreation2((p11, q11) => {
                        Stack.create();
                        Stack.direction(this.counterDirection);
                        Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((n11, o11) => {
                        Rect.create();
                        Rect.direction(this.counterDirection);
                        Rect.width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH);
                        Rect.height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT);
                        Rect.radius([
                            ['0vp', '0vp'],
                            ['0vp', '0vp'],
                            [CounterResource.COUNTER_INLINE_RADIUS, CounterResource.COUNTER_INLINE_RADIUS],
                            ['0vp', '0vp']
                        ]);
                        Rect.strokeWidth(this.subBtnFocusWidh);
                        Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Rect.margin({
                            top: LengthMetrics.vp(1),
                            end: LengthMetrics.vp(1),
                            bottom: LengthMetrics.vp(2)
                        });
                        Rect.fillOpacity(0);
                    }, Rect);
                    this.observeComponentCreation2((l11, m11) => {
                        Image.create(CounterResource.BUTTON_ARROW_DOWN);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
                        Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.subOpacity);
                    }, Image);
                    this.observeComponentCreation2((b11, c11) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Button.backgroundColor(Color.Transparent);
                        Button.opacity(this.subOpacity);
                        Button.enabled(this.subBtnEnabled);
                        Button.onClick((k11) => {
                            this.subValue();
                            if (k11.source === SourceType.Mouse ||
                                k11.source === SourceType.TouchScreen) {
                                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((j11) => {
                            if (j11.repeat) {
                                this.subValue();
                            }
                            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((i11) => {
                            this.onHoverDecrease && this.onHoverDecrease(i11);
                        });
                        Button.focusable(false);
                        Button.onFocus(() => {
                            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusDecrease && this.onFocusDecrease();
                        });
                        Button.onBlur(() => {
                            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurDecrease && this.onBlurDecrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    Column.pop();
                    Row.pop();
                });
            }
            else if (this.type === CounterType.INLINE_DATE) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.observeComponentCreation2((n10, o10) => {
                        Row.create();
                        Row.direction(this.counterDirection);
                        Row.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                        Row.borderWidth(CounterResource.COUNTER_BORDER_WIDTH);
                        Row.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                        Row.borderRadius(CounterResource.COUNTER_INLINE_RADIUS);
                        Row.clip(true);
                    }, Row);
                    this.observeComponentCreation2((l10, m10) => {
                        Row.create();
                        Row.direction(this.counterDirection);
                        Row.width('92vp');
                        Row.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                        Row.margin({
                            start: LengthMetrics.vp(CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN),
                            end: LengthMetrics.vp(CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN)
                        });
                    }, Row);
                    this.observeComponentCreation2((w9, x9) => {
                        TextInput.create({
                            text: this.hasInputText1 ? this.inputYear.toString() : this.getYear(),
                            controller: this.controller1
                        });
                        TextInput.direction(this.counterDirection);
                        TextInput.type(InputType.Number);
                        TextInput.caretColor(Color.Transparent);
                        TextInput.copyOption(CopyOptions.None);
                        TextInput.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                        TextInput.fontWeight(FontWeight.Medium);
                        TextInput.fontColor(this.hasFocusText1 ? Color.White : CounterResource.COUNTER_TEXT_COLOR);
                        TextInput.maxLength(5);
                        TextInput.padding(0);
                        TextInput.backgroundColor(this.hasFocusText1 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent);
                        TextInput.width('38vp');
                        TextInput.height('20vp');
                        TextInput.borderRadius(0);
                        TextInput.borderWidth(0);
                        TextInput.key('DateTextInput1' + this.timeStamp.toString());
                        TextInput.onKeyEvent((k10) => {
                            this.focusCurrentText(FocusText.TEXT1);
                            if (k10.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusText();
                                k10.stopPropagation();
                            }
                            if (k10.type === KeyType.Down &&
                                k10.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                                this.addDate();
                                k10.stopPropagation();
                            }
                            if (k10.type === KeyType.Down &&
                                k10.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                                this.subDate();
                                k10.stopPropagation();
                            }
                            if (k10.type === KeyType.Down &&
                                k10.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                this.homeFocusText();
                                k10.stopPropagation();
                            }
                            if (k10.type === KeyType.Down &&
                                k10.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                this.endFocusText();
                                k10.stopPropagation();
                            }
                            if (k10.type === KeyType.Down &&
                                k10.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
                                k10.stopPropagation();
                            }
                            if (k10.type === KeyType.Down &&
                                k10.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                                this.focusWithTarget('DateTextInput2' + this.timeStamp.toString());
                            }
                        });
                        TextInput.onChange((h10) => {
                            if (h10.length !== 4) {
                                this.hasInputText1 = true;
                            }
                            this.inputYear = Number(h10);
                            if (h10.length === 5) {
                                this.inputYear = this.inputYear % 10;
                            }
                            if (this.timeoutID1 !== -1) {
                                clearTimeout(this.timeoutID1);
                                this.timeoutID1 = -1;
                            }
                            this.timeoutID1 = setTimeout(() => {
                                this.hasInputText1 = false;
                                this.inputYear = this.year;
                                this.updateDateEnableSate();
                                this.updateDay();
                            }, 1500);
                            if (this.inputYear >= this.minYear && this.inputYear <= this.maxYear) {
                                this.year = this.inputYear;
                                this.updateDateEnableSate();
                                this.updateDay();
                            }
                            if (h10.length === 4) {
                                let j10 = new DateData(this.year, this.month, this.day);
                                this.onDateChange?.(j10);
                            }
                        });
                        TextInput.onSubmit((f10) => {
                            if (this.timeoutID1 !== -1) {
                                clearTimeout(this.timeoutID1);
                                this.timeoutID1 = -1;
                            }
                            this.hasInputText1 = false;
                            this.year -= 1;
                            if (this.inputYear >= this.minYear && this.inputYear <= this.maxYear) {
                                this.year = this.inputYear;
                            }
                            else {
                                this.year += 1;
                                this.inputYear = this.year;
                            }
                            this.updateDateEnableSate();
                            this.updateDay();
                        });
                        TextInput.tabIndex(0);
                        TextInput.focusOnTouch(true);
                        TextInput.focusable(true);
                        TextInput.onFocus(() => {
                            this.focusText = FocusText.TEXT1;
                            this.hasFocusText1 = true;
                            this.updateDateEnableSate();
                            this.controller1.caretPosition(this.getYear().length);
                        });
                        TextInput.onBlur(() => {
                            this.focusText = FocusText.NONE;
                            this.hasFocusText1 = false;
                            this.updateDateEnableSate();
                        });
                        TextInput.onClick((e10) => {
                            this.focusText = FocusText.TEXT1;
                            this.hasFocusText1 = true;
                            this.updateDateEnableSate();
                            this.controller1.caretPosition(this.getYear().length);
                        });
                    }, TextInput);
                    this.observeComponentCreation2((u9, v9) => {
                        Text.create('/');
                        Text.direction(this.counterDirection);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                        Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                        Text.width('8vp');
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((e9, f9) => {
                        TextInput.create({
                            text: this.hasInputText2 ? this.inputMoon.toString() : this.convertNumberToString(this.month),
                            controller: this.controller2
                        });
                        TextInput.direction(this.counterDirection);
                        TextInput.type(InputType.Number);
                        TextInput.caretColor(Color.Transparent);
                        TextInput.copyOption(CopyOptions.None);
                        TextInput.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                        TextInput.fontWeight(FontWeight.Medium);
                        TextInput.fontColor(this.hasFocusText2 ? Color.White : CounterResource.COUNTER_TEXT_COLOR);
                        TextInput.maxLength(3);
                        TextInput.padding(0);
                        TextInput.backgroundColor(this.hasFocusText2 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent);
                        TextInput.width('19vp');
                        TextInput.height('20vp');
                        TextInput.borderRadius(0);
                        TextInput.key('DateTextInput2' + this.timeStamp.toString());
                        TextInput.onKeyEvent((t9) => {
                            this.focusCurrentText(FocusText.TEXT2);
                            if (t9.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusText();
                                t9.stopPropagation();
                            }
                            if (t9.type === KeyType.Down &&
                                t9.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                                this.subDate();
                                this.updateDay();
                                t9.stopPropagation();
                            }
                            if (t9.type === KeyType.Down &&
                                t9.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                                this.addDate();
                                this.updateDay();
                                t9.stopPropagation();
                            }
                            if (t9.type === KeyType.Down &&
                                t9.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                this.homeFocusText();
                                t9.stopPropagation();
                            }
                            if (t9.type === KeyType.Down &&
                                t9.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                this.endFocusText();
                                t9.stopPropagation();
                            }
                            if (t9.type === KeyType.Down &&
                                t9.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
                            }
                            if (t9.type === KeyType.Down &&
                                t9.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                                this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
                            }
                            if (t9.type === KeyType.Down &&
                                t9.keyCode === CounterConstant.KEYCODE_TAB) {
                                t9.stopPropagation();
                                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
                            }
                        });
                        TextInput.onChange((p9) => {
                            this.inputMoon = Number(p9);
                            if (p9.length !== 2) {
                                this.hasInputText2 = true;
                            }
                            if (p9.length === 3) {
                                this.inputMoon = this.inputMoon % 10;
                            }
                            if (this.timeoutID2 !== -1) {
                                clearTimeout(this.timeoutID2);
                                this.timeoutID2 = -1;
                            }
                            this.timeoutID2 = setTimeout(() => {
                                this.hasInputText2 = false;
                                this.month -= 1;
                                if (this.inputMoon >= 1 && this.inputMoon <= 12) {
                                    this.month = this.inputMoon;
                                }
                                else {
                                    this.month += 1;
                                    this.inputMoon = this.month;
                                }
                                this.updateDay();
                            }, 1000);
                            if (p9.length === 2) {
                                this.hasInputText2 = false;
                                this.month -= 1;
                                if (this.inputMoon >= 1 && this.inputMoon <= 12) {
                                    this.month = this.inputMoon;
                                    let r9 = new DateData(this.year, this.month, this.day);
                                    this.onDateChange?.(r9);
                                }
                                else {
                                    this.month += 1;
                                    this.inputMoon = this.month;
                                }
                                this.updateDay();
                            }
                        });
                        TextInput.onSubmit((n9) => {
                            if (this.timeoutID2 !== -1) {
                                clearTimeout(this.timeoutID2);
                                this.timeoutID2 = -1;
                            }
                            this.hasInputText2 = false;
                            this.month -= 1;
                            if (this.inputMoon >= 1 && this.inputMoon <= 12) {
                                this.month = this.inputMoon;
                                this.updateDay();
                            }
                            else {
                                this.month += 1;
                            }
                        });
                        TextInput.focusOnTouch(true);
                        TextInput.tabIndex(-1);
                        TextInput.focusable(true);
                        TextInput.onFocus(() => {
                            this.focusText = FocusText.TEXT2;
                            this.hasFocusText2 = true;
                            this.controller2.caretPosition(this.convertNumberToString(this.month).length);
                        });
                        TextInput.onBlur(() => {
                            this.focusText = FocusText.NONE;
                            this.hasFocusText2 = false;
                        });
                        TextInput.onClick((m9) => {
                            this.focusText = FocusText.TEXT2;
                            this.hasFocusText2 = true;
                            this.controller2.caretPosition(this.convertNumberToString(this.month).length);
                        });
                    }, TextInput);
                    this.observeComponentCreation2((c9, d9) => {
                        Text.create('/');
                        Text.direction(this.counterDirection);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                        Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                        Text.width('8vp');
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((m8, n8) => {
                        TextInput.create({
                            text: this.hasInputText3 ? this.inputDay.toString() : this.convertNumberToString(this.day),
                            controller: this.controller3
                        });
                        TextInput.direction(this.counterDirection);
                        TextInput.type(InputType.Number);
                        TextInput.caretColor(Color.Transparent);
                        TextInput.copyOption(CopyOptions.None);
                        TextInput.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                        TextInput.fontWeight(FontWeight.Medium);
                        TextInput.fontColor(this.hasFocusText3 ? Color.White : CounterResource.COUNTER_TEXT_COLOR);
                        TextInput.maxLength(3);
                        TextInput.padding(0);
                        TextInput.backgroundColor(this.hasFocusText3 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent);
                        TextInput.width('19vp');
                        TextInput.height('20vp');
                        TextInput.borderRadius(0);
                        TextInput.key('DateTextInput3' + this.timeStamp.toString());
                        TextInput.onKeyEvent((b9) => {
                            this.focusCurrentText(FocusText.TEXT3);
                            if (b9.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusText();
                                b9.stopPropagation();
                            }
                            if (b9.type === KeyType.Down &&
                                b9.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                                this.subDate();
                                b9.stopPropagation();
                            }
                            if (b9.type === KeyType.Down &&
                                b9.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                                this.addDate();
                                b9.stopPropagation();
                            }
                            if (b9.type === KeyType.Down &&
                                b9.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                this.homeFocusText();
                                b9.stopPropagation();
                            }
                            if (b9.type === KeyType.Down &&
                                b9.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                this.endFocusText();
                                b9.stopPropagation();
                            }
                            if (b9.type === KeyType.Down &&
                                b9.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                                this.focusWithTarget('DateTextInput2' + this.timeStamp.toString());
                            }
                            if (b9.type === KeyType.Down &&
                                b9.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                                this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
                                b9.stopPropagation();
                            }
                            if (b9.type === KeyType.Down &&
                                b9.keyCode === CounterConstant.KEYCODE_TAB) {
                                b9.stopPropagation();
                                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
                            }
                        });
                        TextInput.onChange((x8) => {
                            this.inputDay = Number(x8);
                            if (x8.length !== 2) {
                                this.hasInputText3 = true;
                            }
                            if (x8.length === 3) {
                                this.inputDay = this.inputDay % 10;
                            }
                            if (this.timeoutID3 !== -1) {
                                clearTimeout(this.timeoutID3);
                                this.timeoutID3 = -1;
                            }
                            this.timeoutID3 = setTimeout(() => {
                                this.hasInputText3 = false;
                                this.day -= 1;
                                if (this.inputDay >= 1 && this.inputDay <= this.getDayNumber()) {
                                    this.day = this.inputDay;
                                }
                                else {
                                    this.day += 1;
                                    this.inputDay = this.day;
                                }
                            }, 1000);
                            if (x8.length === 2) {
                                this.hasInputText3 = false;
                                this.day -= 1;
                                if (this.inputDay >= 1 && this.inputDay <= this.getDayNumber()) {
                                    this.day = this.inputDay;
                                    let z8 = new DateData(this.year, this.month, this.day);
                                    this.onDateChange?.(z8);
                                }
                                else {
                                    this.day += 1;
                                    this.inputDay = this.day;
                                }
                            }
                        });
                        TextInput.onSubmit((v8) => {
                            if (this.timeoutID3 !== -1) {
                                clearTimeout(this.timeoutID3);
                                this.timeoutID3 = -1;
                            }
                            this.hasInputText3 = false;
                            this.day -= 1;
                            if (this.inputDay >= 1 && this.inputDay <= this.getDayNumber()) {
                                this.day = this.inputDay;
                            }
                            else {
                                this.day += 1;
                            }
                        });
                        TextInput.tabIndex(-2);
                        TextInput.focusOnTouch(true);
                        TextInput.focusable(true);
                        TextInput.onFocus(() => {
                            this.focusText = FocusText.TEXT3;
                            this.hasFocusText3 = true;
                            this.controller3.caretPosition(this.convertNumberToString(this.day).length);
                        });
                        TextInput.onBlur(() => {
                            this.focusText = FocusText.NONE;
                            this.hasFocusText3 = false;
                        });
                        TextInput.onClick((u8) => {
                            this.focusText = FocusText.TEXT3;
                            this.hasFocusText3 = true;
                            this.controller3.caretPosition(this.convertNumberToString(this.day).length);
                        });
                    }, TextInput);
                    Row.pop();
                    this.observeComponentCreation2((k8, l8) => {
                        Column.create();
                        Column.direction(this.counterDirection);
                        Column.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Column.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                        Column.borderWidth({ start: LengthMetrics.vp(CounterResource.COUNTER_BORDER_WIDTH_NUMBER) });
                        Column.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                    }, Column);
                    this.observeComponentCreation2((i8, j8) => {
                        Stack.create();
                        Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Stack.padding({ top: '1vp' });
                        Stack.borderWidth({ bottom: '1vp' });
                        Stack.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((g8, h8) => {
                        Rect.create();
                        Rect.direction(this.counterDirection);
                        Rect.width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH);
                        Rect.height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT);
                        Rect.radius([
                            ['0vp', '0vp'],
                            [CounterResource.COUNTER_INLINE_RADIUS, CounterResource.COUNTER_INLINE_RADIUS],
                            ['0vp', '0vp'],
                            ['0vp', '0vp']
                        ]);
                        Rect.strokeWidth(this.addBtnFocusWidh);
                        Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Rect.margin({ end: LengthMetrics.vp(1) });
                        Rect.fillOpacity(0);
                    }, Rect);
                    this.observeComponentCreation2((e8, f8) => {
                        Image.create(CounterResource.BUTTON_ARROW_UP);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
                        Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.addOpacity);
                    }, Image);
                    this.observeComponentCreation2((s7, t7) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Button.backgroundColor(Color.Transparent);
                        Button.opacity(this.addOpacity);
                        Button.enabled(this.addBtnEnabled);
                        Button.onClick((c8) => {
                            this.addDate();
                            if (c8.source === SourceType.Mouse ||
                                c8.source === SourceType.TouchScreen) {
                                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((a8) => {
                            if (a8.repeat) {
                                this.addDate();
                            }
                            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((z7) => {
                            this.onHoverIncrease && this.onHoverIncrease(z7);
                        });
                        Button.focusable(false);
                        Button.onFocus(() => {
                            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusIncrease && this.onFocusIncrease();
                        });
                        Button.onBlur(() => {
                            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurIncrease && this.onBlurIncrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    this.observeComponentCreation2((q7, r7) => {
                        Stack.create();
                        Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((o7, p7) => {
                        Rect.create();
                        Rect.direction(this.counterDirection);
                        Rect.width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH);
                        Rect.height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT);
                        Rect.radius([
                            ['0vp', '0vp'],
                            ['0vp', '0vp'],
                            [CounterResource.COUNTER_INLINE_RADIUS, CounterResource.COUNTER_INLINE_RADIUS],
                            ['0vp', '0vp']
                        ]);
                        Rect.strokeWidth(this.subBtnFocusWidh);
                        Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Rect.margin({
                            top: LengthMetrics.vp(1),
                            end: LengthMetrics.vp(1),
                            bottom: LengthMetrics.vp(2)
                        });
                        Rect.fillOpacity(0);
                    }, Rect);
                    this.observeComponentCreation2((m7, n7) => {
                        Image.create(CounterResource.BUTTON_ARROW_DOWN);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
                        Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.subOpacity);
                    }, Image);
                    this.observeComponentCreation2((a7, b7) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Button.backgroundColor(Color.Transparent);
                        Button.opacity(this.subOpacity);
                        Button.enabled(this.subBtnEnabled);
                        Button.onClick((k7) => {
                            this.subDate();
                            if (k7.source === SourceType.Mouse ||
                                k7.source === SourceType.TouchScreen) {
                                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((i7) => {
                            if (i7.repeat) {
                                this.subDate();
                            }
                            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((h7) => {
                            this.onHoverDecrease && this.onHoverDecrease(h7);
                        });
                        Button.focusable(false);
                        Button.onFocus(() => {
                            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusDecrease && this.onFocusDecrease();
                        });
                        Button.onBlur(() => {
                            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurDecrease && this.onBlurDecrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    Column.pop();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(4, () => {
                });
            }
        }, If);
        If.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default {CounterType, CommonOptions, InlineStyleOptions, NumberStyleOptions,
    DateData, DateStyleOptions, CounterOptions, CounterComponent};
