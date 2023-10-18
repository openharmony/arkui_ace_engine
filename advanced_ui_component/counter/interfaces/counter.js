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

export var CounterType;
!function(t){
    t[t.LIST=0] = "LIST";
    t[t.COMPACT=1] = "COMPACT";
    t[t.INLINE=2] = "INLINE";
    t[t.INLINE_DATE=3] = "INLINE_DATE"
}(CounterType || (CounterType = {}));
var FocusText;
!function(t){
    t[t.NONE=0] = "NONE";
    t[t.TEXT1=1] = "TEXT1";
    t[t.TEXT2=2] = "TEXT2";
    t[t.TEXT3=3] = "TEXT3"
}(FocusText || (FocusText = {}));

export class CommonOptions {
}

export class InlineStyleOptions extends CommonOptions {
}

export class NumberStyleOptions extends InlineStyleOptions {
}

export class DateData {
    constructor(t, e, o) {
        this.year = t;
        this.month = e;
        this.day = o
    }

    toString() {
        let t = this.year.toString() + "-";
        t += (this.month < 10 ? "0" + this.month.toString() : this.month.toString()) + "-";
        t += this.day < 10 ? "0" + this.day.toString() : this.day.toString();
        return t
    }
}

export class DateStyleOptions extends CommonOptions {
}

export class CounterOptions {
}

class CounterResource {
}

CounterResource.BUTTON_BACKGROUD_COLOR = {
    id: -1,
    type: 10001,
    params: ["sys.color.ohos_id_color_button_normal"],
    bundleName: "",
    moduleName: ""
};
CounterResource.BUTTON_ICON_COLOR = {
    id: -1,
    type: 10001,
    params: ["sys.color.ohos_id_color_primary"],
    bundleName: "",
    moduleName: ""
};
CounterResource.BUTTON_BORDER_FOCUSED_COLOR = {
    id: -1,
    type: 10001,
    params: ["sys.color.ohos_id_color_focused_outline"],
    bundleName: "",
    moduleName: ""
};
CounterResource.COUNTER_TEXT_COLOR = {
    id: -1,
    type: 10001,
    params: ["sys.color.ohos_id_color_text_primary"],
    bundleName: "",
    moduleName: ""
};
CounterResource.COUNTER_BORDER_COLOR = {
    id: -1,
    type: 10001,
    params: ["sys.color.ohos_id_color_component_normal"],
    bundleName: "",
    moduleName: ""
};
CounterResource.BUTTON_ADD_ICON = {
    id: -1,
    type: 2e4,
    params: ["sys.media.ohos_ic_public_add"],
    bundleName: "",
    moduleName: ""
};
CounterResource.BUTTON_SUB_ICON = {
    id: -1,
    type: 2e4,
    params: ["sys.media.ohos_ic_public_minus"],
    bundleName: "",
    moduleName: ""
};
CounterResource.BUTTON_ARROW_UP = {
    id: -1,
    type: 2e4,
    params: ["sys.media.ohos_ic_public_arrow_up"],
    bundleName: "",
    moduleName: ""
};
CounterResource.BUTTON_ARROW_DOWN = {
    id: -1,
    type: 2e4,
    params: ["sys.media.ohos_ic_public_arrow_down"],
    bundleName: "",
    moduleName: ""
};
CounterResource.BUTTON_BORDER_FOCUSED_WIDTH = "2vp";
CounterResource.BUTTON_BORDER_BLUR_WIDTH = "0vp";
CounterResource.COUNTER_BORDER_WIDTH = "1vp";
CounterResource.COUNTER_LIST_LABEL_SIZE = {
    id: -1,
    type: 10002,
    params: ["sys.float.ohos_id_text_size_body1"],
    bundleName: "",
    moduleName: ""
};
CounterResource.COUNTER_LIST_NUMBER_SIZE = {
    id: -1,
    type: 10002,
    params: ["sys.float.ohos_id_text_size_body1"],
    bundleName: "",
    moduleName: ""
};
CounterResource.COUNTER_COMPACT_LABEL_SIZE = {
    id: -1,
    type: 10002,
    params: ["sys.float.ohos_id_text_size_body2"],
    bundleName: "",
    moduleName: ""
};
CounterResource.COUNTER_NUMBER_SIZE = {
    id: -1,
    type: 10002,
    params: ["sys.float.ohos_id_text_size_body1"],
    bundleName: "",
    moduleName: ""
};
CounterResource.COUNTER_LIST_LEFT_PADDING = {
    id: -1,
    type: 10002,
    params: ["sys.float.ohos_id_default_padding_start"],
    bundleName: "",
    moduleName: ""
};
CounterResource.COUNTER_LIST_RIGHT_PADDING = {
    id: -1,
    type: 10002,
    params: ["sys.float.ohos_id_default_padding_end"],
    bundleName: "",
    moduleName: ""
};
CounterResource.COUNTER_LIST_HEIGHT = "48vp";
CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE = "20vp";
CounterResource.COUNTER_LIST_BUTTON_SIZE = "32vp";
CounterResource.COUNTER_LIST_BUTTON_RADIUS = "16vp";
CounterResource.COUNTER_LIST_BUTTON_TEXT_DISTANCE = "8vp";
CounterResource.COUNTER_LIST_FOCUS_BORDER_SIZE = "30vp";
CounterResource.COUNTER_LIST_FOCUS_BORDER_RADIUS = "15vp";
CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_X = "-8vp";
CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_Y = "-8vp";
CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE = "16vp";
CounterResource.COUNTER_COMPACT_BUTTON_SIZE = "24vp";
CounterResource.COUNTER_COMPACT_BUTTON_RADIUS = "12vp";
CounterResource.COUNTER_COMPACT_BUTTON_TEXT_DISTANCE = "10vp";
CounterResource.COUNTER_COMPACT_CONTAINER_HEIGHT = "28vp";
CounterResource.COUNTER_COMPACT_CONTAINER_RADIUS = "14vp";
CounterResource.COUNTER_COMPACT_CONTAINER_LABEL_DISTANCE = "8vp";
CounterResource.COUNTER_COMPACT_FOCUS_BORDER_SIZE = "22vp";
CounterResource.COUNTER_COMPACT_FOCUS_BORDER_RADIUS = "11vp";
CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH = "24vp";
CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT = "12vp";
CounterResource.COUNTER_INLINE_BUTTON_TEXT_DISTANCE = "12vp";
CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT = "32vp";
CounterResource.COUNTER_INLINE_BUTTON_WIDTH = "32vp";
CounterResource.COUNTER_INLINE_BUTTON_HEIGHT = "16vp";
CounterResource.COUNTER_INLINE_RADIUS = "8vp";
CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH = "28vp";
CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT = "13.5vp";
CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN = "12vp";
CounterResource.COUNTER_BUTTON_INITIAL_OPACITY = 1;
CounterResource.COUNTER_BUTTON_DISABLE_OPACITY = .4;

class CounterConstant {
}

CounterConstant.COUNTER_MAX_YEAR = 5e3;
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
    constructor(t, e, o, s = -1) {
        super(t, o, s);
        this.__options = new SynchedPropertyObjectOneWayPU(e.options, this, "options");
        this.__type = new ObservedPropertySimplePU(-1, this, "type");
        this.__choverEffect = new ObservedPropertySimplePU(HoverEffect.Auto, this, "choverEffect");
        this.__focusEnable = new ObservedPropertySimplePU(!0, this, "focusEnable");
        this.__step = new ObservedPropertySimplePU(CounterConstant.COUNTER_INITIAL_STEP, this, "step");
        this.__inputValue = new ObservedPropertySimplePU("0", this, "inputValue");
        this.__inputYear = new ObservedPropertySimplePU(CounterConstant.COUNTER_MIN_YEAR, this, "inputYear");
        this.__inputMoon = new ObservedPropertySimplePU(0, this, "inputMoon");
        this.__inputDay = new ObservedPropertySimplePU(0, this, "inputDay");
        this.__inputHour = new ObservedPropertySimplePU(0, this, "inputHour");
        this.__inputMinute = new ObservedPropertySimplePU(0, this, "inputMinute");
        this.__inputSecond = new ObservedPropertySimplePU(0, this, "inputSecond");
        this.__subOpacity = new ObservedPropertySimplePU(CounterResource.COUNTER_BUTTON_INITIAL_OPACITY, this,
            "subOpacity");
        this.__addOpacity = new ObservedPropertySimplePU(CounterResource.COUNTER_BUTTON_INITIAL_OPACITY, this,
            "addOpacity");
        this.__subBtnStateEffect = new ObservedPropertySimplePU(!0, this, "subBtnStateEffect");
        this.__addBtnStateEffect = new ObservedPropertySimplePU(!0, this, "addBtnStateEffect");
        this.__focusText = new ObservedPropertySimplePU(FocusText.NONE, this, "focusText");
        this.__hasFocusText1 = new ObservedPropertySimplePU(!1, this, "hasFocusText1");
        this.__hasFocusText2 = new ObservedPropertySimplePU(!1, this, "hasFocusText2");
        this.__hasFocusText3 = new ObservedPropertySimplePU(!1, this, "hasFocusText3");
        this.__subBtnFocusWidh = new ObservedPropertySimplePU("0vp", this, "subBtnFocusWidh");
        this.__addBtnFocusWidh = new ObservedPropertySimplePU("0vp", this, "addBtnFocusWidh");
        this.__value = new ObservedPropertySimplePU(0, this, "value");
        this.__year = new ObservedPropertySimplePU(CounterConstant.COUNTER_MIN_YEAR, this, "year");
        this.__month = new ObservedPropertySimplePU(CounterConstant.COUNTER_INITIAL_MONTH, this, "month");
        this.__day = new ObservedPropertySimplePU(CounterConstant.COUNTER_INITIAL_DAY, this, "day");
        this.__hour = new ObservedPropertySimplePU(0, this, "hour");
        this.__minute = new ObservedPropertySimplePU(0, this, "minute");
        this.__second = new ObservedPropertySimplePU(0, this, "second");
        this.__subBtnEnabled = new ObservedPropertySimplePU(!0, this, "subBtnEnabled");
        this.__addBtnEnabled = new ObservedPropertySimplePU(!0, this, "addBtnEnabled");
        this.__hasInputText1 = new ObservedPropertySimplePU(!1, this, "hasInputText1");
        this.__hasInputText2 = new ObservedPropertySimplePU(!1, this, "hasInputText2");
        this.__hasInputText3 = new ObservedPropertySimplePU(!1, this, "hasInputText3");
        this.__textWidth = new ObservedPropertySimplePU(0, this, "textWidth");
        this.__min = new ObservedPropertySimplePU(CounterConstant.COUNTER_MIN_VALUE, this, "min");
        this.__max = new ObservedPropertySimplePU(CounterConstant.COUNTER_MAX_VALUE, this, "max");
        this.maxYear = CounterConstant.COUNTER_MAX_YEAR;
        this.minYear = CounterConstant.COUNTER_MIN_YEAR;
        this.numberStrList = ["00", "01", "02", "03", "04", "05", "06", "07", "08", "09"];
        this.onHoverIncrease = void 0;
        this.onHoverDecrease = void 0;
        this.onFocusIncrease = void 0;
        this.onFocusDecrease = void 0;
        this.onBlurIncrease = void 0;
        this.onBlurDecrease = void 0;
        this.onChange = void 0;
        this.onDateChange = void 0;
        this.timeoutID1 = -1;
        this.timeoutID2 = -1;
        this.timeoutID3 = -1;
        this.numberStyleOptions = void 0;
        this.dateStyleOptions = void 0;
        this.inlineStyleOptions = void 0;
        this.timeStamp = 0;
        this.hasTextWidth = !1;
        this.controller1 = new TextInputController;
        this.controller2 = new TextInputController;
        this.controller3 = new TextInputController;
        this.setInitiallyProvidedValue(e);
        this.declareWatch("options", this.onOptionsChange)
    }

    setInitiallyProvidedValue(t) {
        void 0 !== t.type && (this.type = t.type);
        void 0 !== t.choverEffect && (this.choverEffect = t.choverEffect);
        void 0 !== t.focusEnable && (this.focusEnable = t.focusEnable);
        void 0 !== t.step && (this.step = t.step);
        void 0 !== t.inputValue && (this.inputValue = t.inputValue);
        void 0 !== t.inputYear && (this.inputYear = t.inputYear);
        void 0 !== t.inputMoon && (this.inputMoon = t.inputMoon);
        void 0 !== t.inputDay && (this.inputDay = t.inputDay);
        void 0 !== t.inputHour && (this.inputHour = t.inputHour);
        void 0 !== t.inputMinute && (this.inputMinute = t.inputMinute);
        void 0 !== t.inputSecond && (this.inputSecond = t.inputSecond);
        void 0 !== t.subOpacity && (this.subOpacity = t.subOpacity);
        void 0 !== t.addOpacity && (this.addOpacity = t.addOpacity);
        void 0 !== t.subBtnStateEffect && (this.subBtnStateEffect = t.subBtnStateEffect);
        void 0 !== t.addBtnStateEffect && (this.addBtnStateEffect = t.addBtnStateEffect);
        void 0 !== t.focusText && (this.focusText = t.focusText);
        void 0 !== t.hasFocusText1 && (this.hasFocusText1 = t.hasFocusText1);
        void 0 !== t.hasFocusText2 && (this.hasFocusText2 = t.hasFocusText2);
        void 0 !== t.hasFocusText3 && (this.hasFocusText3 = t.hasFocusText3);
        void 0 !== t.subBtnFocusWidh && (this.subBtnFocusWidh = t.subBtnFocusWidh);
        void 0 !== t.addBtnFocusWidh && (this.addBtnFocusWidh = t.addBtnFocusWidh);
        void 0 !== t.value && (this.value = t.value);
        void 0 !== t.year && (this.year = t.year);
        void 0 !== t.month && (this.month = t.month);
        void 0 !== t.day && (this.day = t.day);
        void 0 !== t.hour && (this.hour = t.hour);
        void 0 !== t.minute && (this.minute = t.minute);
        void 0 !== t.second && (this.second = t.second);
        void 0 !== t.subBtnEnabled && (this.subBtnEnabled = t.subBtnEnabled);
        void 0 !== t.addBtnEnabled && (this.addBtnEnabled = t.addBtnEnabled);
        void 0 !== t.hasInputText1 && (this.hasInputText1 = t.hasInputText1);
        void 0 !== t.hasInputText2 && (this.hasInputText2 = t.hasInputText2);
        void 0 !== t.hasInputText3 && (this.hasInputText3 = t.hasInputText3);
        void 0 !== t.textWidth && (this.textWidth = t.textWidth);
        void 0 !== t.min && (this.min = t.min);
        void 0 !== t.max && (this.max = t.max);
        void 0 !== t.maxYear && (this.maxYear = t.maxYear);
        void 0 !== t.minYear && (this.minYear = t.minYear);
        void 0 !== t.numberStrList && (this.numberStrList = t.numberStrList);
        void 0 !== t.onHoverIncrease && (this.onHoverIncrease = t.onHoverIncrease);
        void 0 !== t.onHoverDecrease && (this.onHoverDecrease = t.onHoverDecrease);
        void 0 !== t.onFocusIncrease && (this.onFocusIncrease = t.onFocusIncrease);
        void 0 !== t.onFocusDecrease && (this.onFocusDecrease = t.onFocusDecrease);
        void 0 !== t.onBlurIncrease && (this.onBlurIncrease = t.onBlurIncrease);
        void 0 !== t.onBlurDecrease && (this.onBlurDecrease = t.onBlurDecrease);
        void 0 !== t.onChange && (this.onChange = t.onChange);
        void 0 !== t.onDateChange && (this.onDateChange = t.onDateChange);
        void 0 !== t.timeoutID1 && (this.timeoutID1 = t.timeoutID1);
        void 0 !== t.timeoutID2 && (this.timeoutID2 = t.timeoutID2);
        void 0 !== t.timeoutID3 && (this.timeoutID3 = t.timeoutID3);
        void 0 !== t.numberStyleOptions && (this.numberStyleOptions = t.numberStyleOptions);
        void 0 !== t.dateStyleOptions && (this.dateStyleOptions = t.dateStyleOptions);
        void 0 !== t.inlineStyleOptions && (this.inlineStyleOptions = t.inlineStyleOptions);
        void 0 !== t.timeStamp && (this.timeStamp = t.timeStamp);
        void 0 !== t.hasTextWidth && (this.hasTextWidth = t.hasTextWidth);
        void 0 !== t.controller1 && (this.controller1 = t.controller1);
        void 0 !== t.controller2 && (this.controller2 = t.controller2);
        void 0 !== t.controller3 && (this.controller3 = t.controller3)
    }

    updateStateVars(t) {
        this.__options.reset(t.options)
    }

    purgeVariableDependenciesOnElmtId(t) {
        this.__options.purgeDependencyOnElmtId(t);
        this.__type.purgeDependencyOnElmtId(t);
        this.__choverEffect.purgeDependencyOnElmtId(t);
        this.__focusEnable.purgeDependencyOnElmtId(t);
        this.__step.purgeDependencyOnElmtId(t);
        this.__inputValue.purgeDependencyOnElmtId(t);
        this.__inputYear.purgeDependencyOnElmtId(t);
        this.__inputMoon.purgeDependencyOnElmtId(t);
        this.__inputDay.purgeDependencyOnElmtId(t);
        this.__inputHour.purgeDependencyOnElmtId(t);
        this.__inputMinute.purgeDependencyOnElmtId(t);
        this.__inputSecond.purgeDependencyOnElmtId(t);
        this.__subOpacity.purgeDependencyOnElmtId(t);
        this.__addOpacity.purgeDependencyOnElmtId(t);
        this.__subBtnStateEffect.purgeDependencyOnElmtId(t);
        this.__addBtnStateEffect.purgeDependencyOnElmtId(t);
        this.__focusText.purgeDependencyOnElmtId(t);
        this.__hasFocusText1.purgeDependencyOnElmtId(t);
        this.__hasFocusText2.purgeDependencyOnElmtId(t);
        this.__hasFocusText3.purgeDependencyOnElmtId(t);
        this.__subBtnFocusWidh.purgeDependencyOnElmtId(t);
        this.__addBtnFocusWidh.purgeDependencyOnElmtId(t);
        this.__value.purgeDependencyOnElmtId(t);
        this.__year.purgeDependencyOnElmtId(t);
        this.__month.purgeDependencyOnElmtId(t);
        this.__day.purgeDependencyOnElmtId(t);
        this.__hour.purgeDependencyOnElmtId(t);
        this.__minute.purgeDependencyOnElmtId(t);
        this.__second.purgeDependencyOnElmtId(t);
        this.__subBtnEnabled.purgeDependencyOnElmtId(t);
        this.__addBtnEnabled.purgeDependencyOnElmtId(t);
        this.__hasInputText1.purgeDependencyOnElmtId(t);
        this.__hasInputText2.purgeDependencyOnElmtId(t);
        this.__hasInputText3.purgeDependencyOnElmtId(t);
        this.__textWidth.purgeDependencyOnElmtId(t);
        this.__min.purgeDependencyOnElmtId(t);
        this.__max.purgeDependencyOnElmtId(t)
    }

    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__type.aboutToBeDeleted();
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
        this.aboutToBeDeletedInternal()
    }

    get options() {
        return this.__options.get()
    }

    set options(t) {
        this.__options.set(t)
    }

    get type() {
        return this.__type.get()
    }

    set type(t) {
        this.__type.set(t)
    }

    get choverEffect() {
        return this.__choverEffect.get()
    }

    set choverEffect(t) {
        this.__choverEffect.set(t)
    }

    get focusEnable() {
        return this.__focusEnable.get()
    }

    set focusEnable(t) {
        this.__focusEnable.set(t)
    }

    get step() {
        return this.__step.get()
    }

    set step(t) {
        this.__step.set(t)
    }

    get inputValue() {
        return this.__inputValue.get()
    }

    set inputValue(t) {
        this.__inputValue.set(t)
    }

    get inputYear() {
        return this.__inputYear.get()
    }

    set inputYear(t) {
        this.__inputYear.set(t)
    }

    get inputMoon() {
        return this.__inputMoon.get()
    }

    set inputMoon(t) {
        this.__inputMoon.set(t)
    }

    get inputDay() {
        return this.__inputDay.get()
    }

    set inputDay(t) {
        this.__inputDay.set(t)
    }

    get inputHour() {
        return this.__inputHour.get()
    }

    set inputHour(t) {
        this.__inputHour.set(t)
    }

    get inputMinute() {
        return this.__inputMinute.get()
    }

    set inputMinute(t) {
        this.__inputMinute.set(t)
    }

    get inputSecond() {
        return this.__inputSecond.get()
    }

    set inputSecond(t) {
        this.__inputSecond.set(t)
    }

    get subOpacity() {
        return this.__subOpacity.get()
    }

    set subOpacity(t) {
        this.__subOpacity.set(t)
    }

    get addOpacity() {
        return this.__addOpacity.get()
    }

    set addOpacity(t) {
        this.__addOpacity.set(t)
    }

    get subBtnStateEffect() {
        return this.__subBtnStateEffect.get()
    }

    set subBtnStateEffect(t) {
        this.__subBtnStateEffect.set(t)
    }

    get addBtnStateEffect() {
        return this.__addBtnStateEffect.get()
    }

    set addBtnStateEffect(t) {
        this.__addBtnStateEffect.set(t)
    }

    get focusText() {
        return this.__focusText.get()
    }

    set focusText(t) {
        this.__focusText.set(t)
    }

    get hasFocusText1() {
        return this.__hasFocusText1.get()
    }

    set hasFocusText1(t) {
        this.__hasFocusText1.set(t)
    }

    get hasFocusText2() {
        return this.__hasFocusText2.get()
    }

    set hasFocusText2(t) {
        this.__hasFocusText2.set(t)
    }

    get hasFocusText3() {
        return this.__hasFocusText3.get()
    }

    set hasFocusText3(t) {
        this.__hasFocusText3.set(t)
    }

    get subBtnFocusWidh() {
        return this.__subBtnFocusWidh.get()
    }

    set subBtnFocusWidh(t) {
        this.__subBtnFocusWidh.set(t)
    }

    get addBtnFocusWidh() {
        return this.__addBtnFocusWidh.get()
    }

    set addBtnFocusWidh(t) {
        this.__addBtnFocusWidh.set(t)
    }

    get value() {
        return this.__value.get()
    }

    set value(t) {
        this.__value.set(t)
    }

    get year() {
        return this.__year.get()
    }

    set year(t) {
        this.__year.set(t)
    }

    get month() {
        return this.__month.get()
    }

    set month(t) {
        this.__month.set(t)
    }

    get day() {
        return this.__day.get()
    }

    set day(t) {
        this.__day.set(t)
    }

    get hour() {
        return this.__hour.get()
    }

    set hour(t) {
        this.__hour.set(t)
    }

    get minute() {
        return this.__minute.get()
    }

    set minute(t) {
        this.__minute.set(t)
    }

    get second() {
        return this.__second.get()
    }

    set second(t) {
        this.__second.set(t)
    }

    get subBtnEnabled() {
        return this.__subBtnEnabled.get()
    }

    set subBtnEnabled(t) {
        this.__subBtnEnabled.set(t)
    }

    get addBtnEnabled() {
        return this.__addBtnEnabled.get()
    }

    set addBtnEnabled(t) {
        this.__addBtnEnabled.set(t)
    }

    get hasInputText1() {
        return this.__hasInputText1.get()
    }

    set hasInputText1(t) {
        this.__hasInputText1.set(t)
    }

    get hasInputText2() {
        return this.__hasInputText2.get()
    }

    set hasInputText2(t) {
        this.__hasInputText2.set(t)
    }

    get hasInputText3() {
        return this.__hasInputText3.get()
    }

    set hasInputText3(t) {
        this.__hasInputText3.set(t)
    }

    get textWidth() {
        return this.__textWidth.get()
    }

    set textWidth(t) {
        this.__textWidth.set(t)
    }

    get min() {
        return this.__min.get()
    }

    set min(t) {
        this.__min.set(t)
    }

    get max() {
        return this.__max.get()
    }

    set max(t) {
        this.__max.set(t)
    }

    convertNumberToString(t) {
        return t >= 0 && t < CounterConstant.COUNTER_TEN_NUMBER ? this.numberStrList[t] : t.toString()
    }

    aboutToAppear() {
        let t = new Date;
        this.timeStamp = t.getTime();
        void 0 !== this.options && null !== this.options && this.onOptionsChange()
    }

    updateNumberStyleOptions() {
        void 0 === this.numberStyleOptions.label && (this.numberStyleOptions.label = "");
        if (void 0 !== this.numberStyleOptions.value) {
            this.value = this.numberStyleOptions.value;
            this.inputValue = this.value.toString()
        }
        void 0 !== this.numberStyleOptions.min && this.numberStyleOptions.min < this.max &&
            this.numberStyleOptions.min >= this.min && (this.min = this.numberStyleOptions.min);
        void 0 !== this.numberStyleOptions.max && this.numberStyleOptions.max > this.min &&
            this.numberStyleOptions.max <= this.max && (this.max = this.numberStyleOptions.max);
        if (void 0 !== this.numberStyleOptions.textWidth) {
            this.textWidth = this.numberStyleOptions.textWidth;
            this.textWidth < 0 && (this.textWidth = 0);
            this.hasTextWidth = !0
        }
        if (this.value <= this.min) {
            this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.subBtnStateEffect = !1;
            this.subBtnEnabled = !1;
            this.value = this.min;
            this.inputValue = this.value.toString()
        }
        if (this.value >= this.max) {
            this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.addBtnStateEffect = !1;
            this.addBtnEnabled = !1;
            this.value = this.max;
            this.inputValue = this.value.toString()
        }
        void 0 !== this.numberStyleOptions.step && (this.step = this.numberStyleOptions.step);
        this.updateNumberStyleOptionsEvent()
    }

    updateNumberStyleOptionsEvent() {
        void 0 !== this.numberStyleOptions.onHoverIncrease &&
            (this.onHoverIncrease = this.numberStyleOptions.onHoverIncrease);
        void 0 !== this.numberStyleOptions.onHoverDecrease &&
            (this.onHoverDecrease = this.numberStyleOptions.onHoverDecrease);
        void 0 !== this.numberStyleOptions.onFocusIncrease &&
            (this.onFocusIncrease = this.numberStyleOptions.onFocusIncrease);
        void 0 !== this.numberStyleOptions.onFocusDecrease &&
            (this.onFocusDecrease = this.numberStyleOptions.onFocusDecrease);
        void 0 !== this.numberStyleOptions.onBlurIncrease &&
            (this.onBlurIncrease = this.numberStyleOptions.onBlurIncrease);
        void 0 !== this.numberStyleOptions.onBlurDecrease &&
            (this.onBlurDecrease = this.numberStyleOptions.onBlurDecrease);
        void 0 !== this.numberStyleOptions.onChange && (this.onChange = this.numberStyleOptions.onChange);
        void 0 !== this.numberStyleOptions.focusable && (this.focusEnable = this.numberStyleOptions.focusable)
    }

    updateInlineStyleOptions() {
        if (void 0 !== this.inlineStyleOptions.value) {
            this.value = this.inlineStyleOptions.value;
            this.inputValue = this.value.toString()
        }
        void 0 !== this.inlineStyleOptions.min && (this.min = this.inlineStyleOptions.min);
        void 0 !== this.inlineStyleOptions.max && (this.max = this.inlineStyleOptions.max);
        this.min > this.max && (this.min = this.max);
        if (void 0 !== this.inlineStyleOptions.textWidth) {
            this.textWidth = this.inlineStyleOptions.textWidth;
            this.textWidth < 0 && (this.textWidth = 0);
            this.hasTextWidth = !0
        }
        if (this.value <= this.min) {
            this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.subBtnStateEffect = !1;
            this.subBtnEnabled = !1;
            this.value = this.min;
            this.inputValue = this.value.toString()
        }
        if (this.value >= this.max) {
            this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.addBtnStateEffect = !1;
            this.addBtnEnabled = !1;
            this.value = this.max;
            this.inputValue = this.value.toString()
        }
        void 0 !== this.inlineStyleOptions.step && (this.step = this.inlineStyleOptions.step);
        this.updateInlineStyleOptionsEvent()
    }

    updateInlineStyleOptionsEvent() {
        void 0 !== this.inlineStyleOptions.onHoverIncrease &&
            (this.onHoverIncrease = this.inlineStyleOptions.onHoverIncrease);
        void 0 !== this.inlineStyleOptions.onHoverDecrease &&
            (this.onHoverDecrease = this.inlineStyleOptions.onHoverDecrease);
        void 0 !== this.inlineStyleOptions.onChange && (this.onChange = this.inlineStyleOptions.onChange);
        void 0 !== this.inlineStyleOptions.focusable && (this.focusEnable = this.inlineStyleOptions.focusable)
    }

    updateDateStyleOptions() {
        void 0 !== this.dateStyleOptions.step && (this.step = this.dateStyleOptions.step);
        void 0 !== this.dateStyleOptions.onHoverIncrease &&
            (this.onHoverIncrease = this.dateStyleOptions.onHoverIncrease);
        void 0 !== this.dateStyleOptions.onHoverDecrease &&
            (this.onHoverDecrease = this.dateStyleOptions.onHoverDecrease);
        void 0 !== this.dateStyleOptions.year && this.dateStyleOptions.year >= this.minYear &&
            this.dateStyleOptions.year <= this.maxYear && (this.year = this.dateStyleOptions.year);
        void 0 !== this.dateStyleOptions.month && this.dateStyleOptions.month <= CounterConstant.COUNTER_MAX_MONTH &&
            this.dateStyleOptions.month >= CounterConstant.COUNTER_MIN_MONTH &&
            (this.month = this.dateStyleOptions.month);
        void 0 !== this.dateStyleOptions.day && this.dateStyleOptions.day <= this.getDayNumber() &&
            this.dateStyleOptions.day >= CounterConstant.COUNTER_MIN_DAY && (this.day = this.dateStyleOptions.day);
        void 0 !== this.dateStyleOptions.onDateChange && (this.onDateChange = this.dateStyleOptions.onDateChange);
        void 0 !== this.dateStyleOptions.focusable && (this.focusEnable = this.dateStyleOptions.focusable);
        this.updateDay()
    }

    onOptionsChange() {
        this.type = this.options.type;
        if (this.type === CounterType.LIST || this.type === CounterType.COMPACT) {
            this.numberStyleOptions = this.options.numberOptions;
            this.updateNumberStyleOptions()
        } else if (this.type === CounterType.INLINE) {
            this.inlineStyleOptions = this.options.inlineOptions;
            this.updateInlineStyleOptions()
        } else if (this.type === CounterType.INLINE_DATE) {
            this.dateStyleOptions = this.options.dateOptions;
            this.updateDateStyleOptions()
        }
    }

    subValue() {
        this.subBtnStateEffect && (this.value -= this.step);
        if (!this.addBtnStateEffect) {
            this.addBtnStateEffect = !0;
            this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            this.addBtnEnabled = !0
        }
        if (this.value <= this.min) {
            this.value = this.min;
            this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.subBtnStateEffect = !1;
            this.subBtnEnabled = !1
        } else {
            this.subOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY &&
                (this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY);
            this.subBtnStateEffect || (this.subBtnStateEffect = !0);
            this.subBtnEnabled || (this.subBtnEnabled = !0)
        }
        this.focusText1()
    }

    focusText1() {
        if (this.type === CounterType.INLINE && this.focusText === FocusText.NONE) {
            this.focusText = FocusText.TEXT1;
            this.hasFocusText1 = !0;
            this.focusWithTarget("InlineTextInput" + this.timeStamp.toString())
        }
    }

    addValue() {
        this.addBtnStateEffect && (this.value += this.step);
        if (!this.subBtnStateEffect) {
            this.subBtnStateEffect = !0;
            this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            this.subBtnEnabled = !0
        }
        if (this.value >= this.max) {
            this.value = this.max;
            this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.addBtnStateEffect = !1;
            this.addBtnEnabled = !1
        } else {
            this.addOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY &&
                (this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY);
            this.addBtnStateEffect || (this.addBtnStateEffect = !0);
            this.addBtnEnabled || (this.addBtnEnabled = !0)
        }
        this.focusText1()
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
            case CounterConstant.APRIL:
            case CounterConstant.JUNE:
            case CounterConstant.SEPTEMBER:
            case CounterConstant.NOVEMBER:
                return CounterConstant.SMALL_MONTH_DAYS;
            case CounterConstant.FEBRUARY:
                return this.year % CounterConstant.AUSPICIOUS_FOUR == 0 &&
                    this.year % CounterConstant.AUSPICIOUS_HUNDRED != 0 ||
                    this.year % CounterConstant.AUSPICIOUS_FOUR_HUNDRED == 0 ?
                    CounterConstant.AUSPICIOUS_FEBRUARY_DAYS : CounterConstant.FEBRUARY_DAYS
        }
    }

    subDate() {
        if (this.focusText === FocusText.TEXT1) {
            if (this.subBtnStateEffect) {
                this.inputYear = this.year;
                this.year -= this.step;
                this.hasFocusText1 || (this.hasFocusText1 = !0)
            }
            if (!this.addBtnStateEffect) {
                this.addBtnStateEffect = !0;
                this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                this.addBtnEnabled = !0
            }
            if (this.year <= this.minYear) {
                this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                this.subBtnStateEffect = !1;
                this.subBtnEnabled = !1
            } else {
                this.subOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY &&
                    (this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY);
                this.subBtnStateEffect || (this.subBtnStateEffect = !0);
                this.subBtnEnabled || (this.subBtnEnabled = !0)
            }
        } else if (this.focusText === FocusText.TEXT2) {
            this.month -= this.step % CounterConstant.COUNTER_MAX_MONTH;
            this.month < CounterConstant.COUNTER_MIN_MONTH && (this.month += CounterConstant.COUNTER_MAX_MONTH);
            this.hasFocusText2 || (this.hasFocusText2 = !0)
        } else if (this.focusText === FocusText.TEXT3) {
            this.day -= this.step % this.getDayNumber();
            this.day < CounterConstant.COUNTER_MIN_DAY && (this.day += this.getDayNumber());
            this.hasFocusText3 || (this.hasFocusText3 = !0)
        } else this.focusDayWitdhSub()
    }

    focusDayWitdhSub() {
        this.focusText = FocusText.TEXT3;
        this.hasFocusText3 = !0;
        this.day -= this.step % this.getDayNumber();
        this.day < CounterConstant.COUNTER_MIN_DAY && (this.day += this.getDayNumber());
        this.focusWithTarget("DateTextInput3" + this.timeStamp.toString())
    }

    addDate() {
        if (this.focusText === FocusText.TEXT1) {
            if (this.addBtnStateEffect) {
                this.inputYear = this.year;
                this.year += this.step;
                this.hasFocusText1 || (this.hasFocusText1 = !0)
            }
            if (!this.subBtnStateEffect) {
                this.subBtnStateEffect = !0;
                this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                this.subBtnEnabled = !0
            }
            if (this.year >= this.maxYear) {
                this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                this.addBtnStateEffect = !1;
                this.addBtnEnabled = !1
            } else {
                this.addOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY &&
                    (this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY);
                this.addBtnStateEffect || (this.addBtnStateEffect = !0);
                this.addBtnEnabled || (this.addBtnEnabled = !0)
            }
        } else if (this.focusText === FocusText.TEXT2) {
            this.month += this.step % CounterConstant.COUNTER_MAX_MONTH;
            this.month > CounterConstant.COUNTER_MAX_MONTH && (this.month -= CounterConstant.COUNTER_MAX_MONTH);
            this.hasFocusText2 || (this.hasFocusText2 = !0)
        } else if (this.focusText === FocusText.TEXT3) {
            this.day += this.step % this.getDayNumber();
            this.day > this.getDayNumber() && (this.day -= this.getDayNumber());
            this.hasFocusText3 || (this.hasFocusText3 = !0)
        } else this.focusDayWithAdd()
    }

    focusDayWithAdd() {
        this.focusText = FocusText.TEXT3;
        this.hasFocusText3 = !0;
        this.day += this.step % this.getDayNumber();
        this.day > this.getDayNumber() && (this.day -= this.getDayNumber());
        this.focusWithTarget("DateTextInput3" + this.timeStamp.toString())
    }

    updateInlineEnableSate() {
        if (this.value >= this.max) {
            this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.addBtnStateEffect = !1;
            this.addBtnEnabled = !1
        } else {
            this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            this.addBtnStateEffect = !0;
            this.addBtnEnabled = !0
        }
        if (this.value <= this.min) {
            this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.subBtnStateEffect = !1;
            this.subBtnEnabled = !1
        } else {
            this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            this.subBtnStateEffect = !0;
            this.subBtnEnabled = !0
        }
    }

    updateDateEnableSate() {
        if (this.year === this.maxYear && this.focusText === FocusText.TEXT1) {
            this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.addBtnStateEffect = !1;
            this.addBtnEnabled = !1
        } else {
            this.addOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY &&
                (this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY);
            this.addBtnStateEffect || (this.addBtnStateEffect = !0);
            this.addBtnEnabled || (this.addBtnEnabled = !0)
        }
        if (this.year === this.minYear && this.focusText === FocusText.TEXT1) {
            this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.subBtnStateEffect = !1;
            this.subBtnEnabled = !1
        } else {
            this.subOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY &&
                (this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY);
            this.subBtnStateEffect || (this.subBtnStateEffect = !0);
            this.subBtnEnabled || (this.subBtnEnabled = !0)
        }
    }

    updateDay() {
        this.day > this.getDayNumber() && (this.day = this.getDayNumber())
    }

    resetFocusText() {
        this.focusText = FocusText.NONE;
        this.hasFocusText1 = !1;
        this.hasFocusText2 = !1;
        this.hasFocusText3 = !1
    }

    resetFocusButton() {
        if (this.addBtnFocusWidh === CounterResource.BUTTON_BORDER_FOCUSED_WIDTH) {
            this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
            this.onBlurIncrease && this.onBlurIncrease()
        }
        if (this.subBtnFocusWidh === CounterResource.BUTTON_BORDER_FOCUSED_WIDTH) {
            this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
            this.onBlurDecrease && this.onBlurDecrease()
        }
    }

    homeFocusText() {
        this.focusWithTarget("DateTextInput1" + this.timeStamp.toString())
    }

    endFocusText() {
        this.focusWithTarget("DateTextInput3" + this.timeStamp.toString())
    }

    homeFirstValue() {
        this.value = this.min;
        if (!this.addBtnStateEffect) {
            this.addBtnStateEffect = !0;
            this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            this.addBtnEnabled = !0
        }
    }

    endLastValue() {
        this.value = this.max;
        if (!this.subBtnStateEffect) {
            this.subBtnStateEffect = !0;
            this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
            this.subBtnEnabled = !0
        }
    }

    updateButtonStatus() {
        if (this.value <= this.min) {
            if (!this.addBtnStateEffect) {
                this.addBtnStateEffect = !0;
                this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                this.addBtnEnabled = !0
            }
            this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.subBtnStateEffect = !1;
            this.subBtnEnabled = !1
        }
        if (this.value >= this.max) {
            if (!this.subBtnStateEffect) {
                this.subBtnStateEffect = !0;
                this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                this.subBtnEnabled = !0
            }
            this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.addBtnStateEffect = !1;
            this.addBtnEnabled = !1
        }
    }

    getValue() {
        return this.hasInputText1 ? this.inputValue : this.value.toString()
    }

    getValueLength() {
        return this.getValue().length > 0 ? this.getValue().length : 1
    }

    getYear() {
        let t = this.year.toString();
            1 === t.length ? t = "000" + t : 2 === t.length ? t = "00" + t : 3 === t.length && (t = "0" + t);
        return t
    }

    focusWithTarget(t) {
        setTimeout((() => {
            focusControl.requestFocus(t) ? console.log("Request success") : console.log("Request failed")
        }))
    }

    focusCurrentText(t) {
        if (t === FocusText.TEXT1) {
            this.focusText === FocusText.NONE && (this.focusText = FocusText.TEXT1);
            this.hasFocusText1 || (this.hasFocusText1 = !0)
        } else if (t === FocusText.TEXT2) {
            this.focusText === FocusText.NONE && (this.focusText = FocusText.TEXT2);
            this.hasFocusText2 || (this.hasFocusText2 = !0)
        } else if (t === FocusText.TEXT3) {
            this.focusText === FocusText.NONE && (this.focusText = FocusText.TEXT3);
            this.hasFocusText3 || (this.hasFocusText3 = !0)
        }
    }

    getMaxLength() {
        return this.max.toString().length > this.min.toString().length ?
            this.max.toString().length + 1 : this.min.toString().length + 1
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
                this.type === CounterType.LIST ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    RelativeContainer.create();
                    RelativeContainer.width("100%");
                    RelativeContainer.height(CounterResource.COUNTER_LIST_HEIGHT);
                    e || RelativeContainer.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Text.create(this.numberStyleOptions.label);
                    Text.fontSize(CounterResource.COUNTER_LIST_LABEL_SIZE);
                    Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                    Text.margin({ left: CounterResource.COUNTER_LIST_LEFT_PADDING });
                    Text.alignRules({
                        center: { anchor: "__container__", align: VerticalAlign.Center },
                        left: { anchor: "__container__", align: HorizontalAlign.Start }
                    });
                    Text.id("Text");
                    e || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Row.create();
                    Row.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                    Row.margin({ right: CounterResource.COUNTER_LIST_RIGHT_PADDING });
                    Row.alignRules({
                        center: { anchor: "__container__", align: VerticalAlign.Center },
                        right: { anchor: "__container__", align: HorizontalAlign.End }
                    });
                    Row.tabIndex(0);
                    Row.id("Row1");
                    e || Row.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Stack.create();
                    Stack.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                    Stack.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                    Stack.borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS);
                    Stack.borderWidth(this.subBtnFocusWidh);
                    Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                    Stack.clip(!0);
                    e || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Image.create(CounterResource.BUTTON_SUB_ICON);
                    Image.width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
                    Image.height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
                    Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                    Image.opacity(this.subOpacity);
                    e || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect });
                    Button.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                    Button.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                    Button.responseRegion({
                        x: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_X,
                        y: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_Y,
                        width: "150%",
                        height: "150%"
                    });
                    Button.groupDefaultFocus(!0);
                    Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
                    Button.opacity(this.subOpacity);
                    Button.enabled(this.subBtnEnabled);
                    Button.key("ListSubButton" + this.timeStamp.toString());
                    Button.onKeyEvent((t => {
                        this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                        if (t.keyCode === CounterConstant.KEYCODE_ESC) {
                            this.resetFocusButton();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                            t.stopPropagation();
                            this.homeFirstValue();
                            this.focusWithTarget("ListAddButton" + this.timeStamp.toString())
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                            t.stopPropagation();
                            if (this.addBtnStateEffect) {
                                this.addBtnStateEffect = !1;
                                this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                                this.addBtnEnabled = !1
                            }
                            this.endLastValue();
                            this.focusWithTarget("ListAddButton" + this.timeStamp.toString())
                        }
                    }));
                    Button.onClick((t => {
                        this.subValue();
                        this.onChange && this.onChange(this.value);
                        t.source !== SourceType.Mouse && t.source !== SourceType.TouchScreen ||
                            (this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH)
                    }));
                    Gesture.create(GesturePriority.Low);
                    LongPressGesture.create({ repeat: !0 });
                    LongPressGesture.onAction((t => {
                        if (t.repeat) {
                            this.subValue();
                            this.onChange && this.onChange(this.value)
                        }
                        this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                    }));
                    LongPressGesture.pop();
                    Gesture.pop();
                    Button.hoverEffect(this.choverEffect);
                    Button.onHover((t => {
                        this.onHoverDecrease && this.onHoverDecrease(t)
                    }));
                    Button.focusable(this.focusEnable);
                    Button.onFocus((() => {
                        this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                        this.onFocusDecrease && this.onFocusDecrease();
                        this.updateButtonStatus()
                    }));
                    Button.onBlur((() => {
                        this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        this.onBlurDecrease && this.onBlurDecrease()
                    }));
                    e || Button.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Button.pop();
                Stack.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    If.create();
                    this.hasTextWidth ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.observeComponentCreation(((t, e) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            Text.create(this.value.toString());
                            Text.width(this.textWidth.toString());
                            Text.textAlign(TextAlign.Center);
                            Text.fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE);
                            Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                            Text.margin({
                                left: CounterResource.COUNTER_LIST_BUTTON_TEXT_DISTANCE,
                                right: CounterResource.COUNTER_LIST_BUTTON_TEXT_DISTANCE
                            });
                            e || Text.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Text.pop()
                    })) : this.ifElseBranchUpdateFunction(1, (() => {
                        this.observeComponentCreation(((t, e) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            Text.create(this.value.toString());
                            Text.textAlign(TextAlign.Center);
                            Text.fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE);
                            Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                            Text.margin({
                                left: CounterResource.COUNTER_LIST_BUTTON_TEXT_DISTANCE,
                                right: CounterResource.COUNTER_LIST_BUTTON_TEXT_DISTANCE
                            });
                            e || Text.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Text.pop()
                    }));
                    e || If.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                If.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Stack.create();
                    Stack.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                    Stack.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                    Stack.borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS);
                    Stack.borderWidth(this.addBtnFocusWidh);
                    Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                    Stack.clip(!0);
                    e || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Image.create(CounterResource.BUTTON_ADD_ICON);
                    Image.width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
                    Image.height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
                    Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                    Image.opacity(this.addOpacity);
                    e || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect });
                    Button.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                    Button.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                    Button.responseRegion({
                        x: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_X,
                        y: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_Y,
                        width: "150%",
                        height: "150%"
                    });
                    Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
                    Button.opacity(this.addOpacity);
                    Button.enabled(this.addBtnEnabled);
                    Button.key("ListAddButton" + this.timeStamp.toString());
                    Button.onKeyEvent((t => {
                        this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                        if (t.keyCode === CounterConstant.KEYCODE_ESC) {
                            this.resetFocusButton();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                            t.stopPropagation();
                            this.homeFirstValue();
                            if (this.subBtnStateEffect) {
                                this.subBtnStateEffect = !1;
                                this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                                this.subBtnEnabled = !1
                            }
                            this.focusWithTarget("ListAddButton" + this.timeStamp.toString())
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                            t.stopPropagation();
                            this.endLastValue();
                            this.focusWithTarget("ListSubButton" + this.timeStamp.toString())
                        }
                    }));
                    Button.onClick((t => {
                        this.addValue();
                        this.onChange && this.onChange(this.value);
                        t.source !== SourceType.Mouse && t.source !== SourceType.TouchScreen ||
                            (this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH)
                    }));
                    Gesture.create(GesturePriority.Low);
                    LongPressGesture.create({ repeat: !0 });
                    LongPressGesture.onAction((t => {
                        if (t.repeat) {
                            this.addValue();
                            this.onChange && this.onChange(this.value)
                        }
                        this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                    }));
                    LongPressGesture.pop();
                    Gesture.pop();
                    Button.hoverEffect(this.choverEffect);
                    Button.onHover((t => {
                        this.onHoverIncrease && this.onHoverIncrease(t)
                    }));
                    Button.focusable(this.focusEnable);
                    Button.onFocus((() => {
                        this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                        this.onFocusIncrease && this.onFocusIncrease();
                        this.updateButtonStatus()
                    }));
                    Button.onBlur((() => {
                        this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        this.onBlurIncrease && this.onBlurIncrease()
                    }));
                    e || Button.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Button.pop();
                Stack.pop();
                Row.pop();
                RelativeContainer.pop()
            })) : this.type === CounterType.COMPACT ? this.ifElseBranchUpdateFunction(1, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Column.create();
                    e || Column.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Row.create();
                    Row.tabIndex(0);
                    Row.height(CounterResource.COUNTER_COMPACT_CONTAINER_HEIGHT);
                    Row.align(Alignment.Center);
                    Row.borderWidth(CounterResource.COUNTER_BORDER_WIDTH);
                    Row.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                    Row.borderRadius(CounterResource.COUNTER_COMPACT_CONTAINER_RADIUS);
                    e || Row.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Stack.create();
                    Stack.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                    Stack.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                    Stack.borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS);
                    Stack.borderWidth(this.subBtnFocusWidh);
                    Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                    Stack.margin({ left: "1vp" });
                    Stack.clip(!0);
                    e || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Image.create(CounterResource.BUTTON_SUB_ICON);
                    Image.width(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
                    Image.height(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
                    Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                    Image.opacity(this.subOpacity);
                    e || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect });
                    Button.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                    Button.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                    Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
                    Button.opacity(this.subOpacity);
                    Button.enabled(this.subBtnEnabled);
                    Button.key("CompactSubButton" + this.timeStamp.toString());
                    Button.onKeyEvent((t => {
                        this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                        if (t.keyCode === CounterConstant.KEYCODE_ESC) {
                            this.resetFocusButton();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                            t.stopPropagation();
                            this.homeFirstValue();
                            this.focusWithTarget("CompactAddButton" + this.timeStamp.toString())
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                            t.stopPropagation();
                            this.endLastValue();
                            if (this.addBtnStateEffect) {
                                this.addBtnStateEffect = !1;
                                this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                                this.addBtnEnabled = !1
                            }
                            this.focusWithTarget("CompactSubButton" + this.timeStamp.toString())
                        }
                    }));
                    Button.onClick((t => {
                        this.subValue();
                        this.onChange && this.onChange(this.value);
                        t.source !== SourceType.Mouse && t.source !== SourceType.TouchScreen ||
                            (this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH)
                    }));
                    Gesture.create(GesturePriority.Low);
                    LongPressGesture.create({ repeat: !0 });
                    LongPressGesture.onAction((t => {
                        if (t.repeat) {
                            this.subValue();
                            this.onChange && this.onChange(this.value)
                        }
                        t.source !== SourceType.Mouse && t.source !== SourceType.TouchScreen ||
                            (this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH)
                    }));
                    LongPressGesture.pop();
                    Gesture.pop();
                    Button.hoverEffect(this.choverEffect);
                    Button.onHover((t => {
                        this.onHoverDecrease && this.onHoverDecrease(t)
                    }));
                    Button.focusable(this.focusEnable);
                    Button.groupDefaultFocus(!0);
                    Button.onFocus((() => {
                        this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                        this.onFocusDecrease && this.onFocusDecrease();
                        this.updateButtonStatus()
                    }));
                    Button.onBlur((() => {
                        this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        this.onBlurDecrease && this.onBlurDecrease()
                    }));
                    e || Button.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Button.pop();
                Stack.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    If.create();
                    this.hasTextWidth ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.observeComponentCreation(((t, e) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            Text.create(this.value.toString());
                            Text.textAlign(TextAlign.Center);
                            Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                            Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                            Text.width(this.textWidth.toString());
                            Text.margin({
                                left: CounterResource.COUNTER_COMPACT_BUTTON_TEXT_DISTANCE,
                                right: CounterResource.COUNTER_COMPACT_BUTTON_TEXT_DISTANCE
                            });
                            e || Text.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Text.pop()
                    })) : this.ifElseBranchUpdateFunction(1, (() => {
                        this.observeComponentCreation(((t, e) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            Text.create(this.value.toString());
                            Text.textAlign(TextAlign.Center);
                            Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                            Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                            Text.margin({
                                left: CounterResource.COUNTER_COMPACT_BUTTON_TEXT_DISTANCE,
                                right: CounterResource.COUNTER_COMPACT_BUTTON_TEXT_DISTANCE
                            });
                            e || Text.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Text.pop()
                    }));
                    e || If.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                If.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Stack.create();
                    Stack.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                    Stack.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                    Stack.borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS);
                    Stack.borderWidth(this.addBtnFocusWidh);
                    Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                    Stack.margin({ right: "1vp" });
                    Stack.clip(!0);
                    e || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Image.create(CounterResource.BUTTON_ADD_ICON);
                    Image.width(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
                    Image.height(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
                    Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                    Image.opacity(this.addOpacity);
                    e || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect });
                    Button.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                    Button.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                    Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
                    Button.opacity(this.addOpacity);
                    Button.enabled(this.addBtnEnabled);
                    Button.key("CompactAddButton" + this.timeStamp.toString());
                    Button.onKeyEvent((t => {
                        this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                        if (t.keyCode === CounterConstant.KEYCODE_ESC) {
                            this.resetFocusButton();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                            t.stopPropagation();
                            this.homeFirstValue();
                            if (this.subBtnStateEffect) {
                                this.subBtnStateEffect = !1;
                                this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                                this.subBtnEnabled = !1
                            }
                            this.focusWithTarget("CompactAddButton" + this.timeStamp.toString())
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                            t.stopPropagation();
                            this.endLastValue();
                            this.focusWithTarget("CompactSubButton" + this.timeStamp.toString())
                        }
                    }));
                    Button.onClick((t => {
                        this.addValue();
                        this.onChange && this.onChange(this.value);
                        t.source !== SourceType.Mouse && t.source !== SourceType.TouchScreen ||
                            (this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH)
                    }));
                    Gesture.create(GesturePriority.Low);
                    LongPressGesture.create({ repeat: !0 });
                    LongPressGesture.onAction((t => {
                        if (t.repeat) {
                            this.addValue();
                            this.onChange && this.onChange(this.value)
                        }
                        t.source !== SourceType.Mouse && t.source !== SourceType.TouchScreen ||
                            (this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH)
                    }));
                    LongPressGesture.pop();
                    Gesture.pop();
                    Button.hoverEffect(this.choverEffect);
                    Button.onHover((t => {
                        this.onHoverIncrease && this.onHoverIncrease(t)
                    }));
                    Button.focusable(this.focusEnable);
                    Button.onFocus((() => {
                        this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                        this.onFocusIncrease && this.onFocusIncrease();
                        this.updateButtonStatus()
                    }));
                    Button.onBlur((() => {
                        this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        this.onBlurIncrease && this.onBlurIncrease()
                    }));
                    e || Button.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Button.pop();
                Stack.pop();
                Row.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Text.create(this.numberStyleOptions.label);
                    Text.margin({ top: CounterResource.COUNTER_COMPACT_CONTAINER_LABEL_DISTANCE });
                    Text.fontSize(CounterResource.COUNTER_COMPACT_LABEL_SIZE);
                    Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                    Text.align(Alignment.Top);
                    e || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                Column.pop()
            })) : this.type === CounterType.INLINE ? this.ifElseBranchUpdateFunction(2, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Row.create();
                    Row.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                    Row.borderWidth(CounterResource.COUNTER_BORDER_WIDTH);
                    Row.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                    Row.borderRadius(CounterResource.COUNTER_INLINE_RADIUS);
                    Row.clip(!0);
                    e || Row.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    If.create();
                    this.hasTextWidth ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.observeComponentCreation(((t, e) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            RelativeContainer.create();
                            RelativeContainer.margin({ left: "12vp", right: "12vp" });
                            RelativeContainer.height("100%");
                            RelativeContainer.width(this.textWidth);
                            e || RelativeContainer.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        this.observeComponentCreation(((t, e) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            TextInput.create({
                                text: this.hasInputText1 ? this.inputValue : this.value.toString(),
                                controller: this.controller1
                            });
                            TextInput.alignRules({
                                center: { anchor: "__container__", align: VerticalAlign.Center },
                                middle: { anchor: "__container__", align: HorizontalAlign.Center }
                            });
                            TextInput.width(9.6 * this.getValueLength());
                            TextInput.height("20vp");
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
                            TextInput.backgroundColor(this.hasFocusText1 ?
                                CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent);
                            TextInput.key("InlineTextInput" + this.timeStamp.toString());
                            TextInput.onKeyEvent((t => {
                                this.focusCurrentText(FocusText.TEXT1);
                                if (t.keyCode === CounterConstant.KEYCODE_ESC) {
                                    this.resetFocusText();
                                    t.stopPropagation()
                                }
                                if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                                    this.addValue();
                                    t.stopPropagation()
                                }
                                if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                    t.stopPropagation();
                                    this.focusWithTarget("InlineTextInput" + this.timeStamp.toString())
                                }
                                if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                    t.stopPropagation();
                                    this.focusWithTarget("InlineTextInput" + this.timeStamp.toString())
                                }
                                if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                                    this.subValue();
                                    t.stopPropagation()
                                }
                                if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                                    this.focusWithTarget("InlineTextInput" + this.timeStamp.toString());
                                    t.stopPropagation()
                                }
                                if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                                    this.focusWithTarget("InlineTextInput" + this.timeStamp.toString());
                                    t.stopPropagation()
                                }
                            }));
                            TextInput.onChange((t => {
                                this.inputValue = t;
                                for (let e = 0;e < t.length; e++) {
                                    let o = t[e];
                                    if ("+" === o || "*" === o || "#" === o) {
                                        this.value -= 1;
                                        this.value += 1;
                                        this.inputValue = this.value.toString();
                                        return
                                    }
                                    if ("-" === o && 0 !== e) {
                                        this.inputValue = o;
                                        break
                                    }
                                }
                                this.hasInputText1 = !0;
                                let e = t[t.length-1];
                                t.length === this.getMaxLength() && (this.inputValue = e);
                                if (-1 !== this.timeoutID1) {
                                    clearTimeout(this.timeoutID1);
                                    this.timeoutID1 = -1
                                }
                                if ("" !== this.inputValue && Number(this.inputValue) <= this.max &&
                                    Number(this.inputValue) >= this.min) {
                                    this.value = Number(this.inputValue);
                                    this.hasInputText1 = !1
                                } else {
                                    (Number(this.inputValue) > this.max || Number(this.inputValue) < this.min &&
                                        this.inputValue.length <= this.min.toString().length) && (this.inputValue = e);
                                    t.length < this.getMaxLength() && (this.timeoutID1 = setTimeout((() => {
                                        "" !== this.inputValue && Number(this.inputValue) <= this.max &&
                                            Number(this.inputValue) >= this.min &&
                                            (this.value = Number(this.inputValue));
                                        this.inputValue = this.value.toString();
                                        this.hasInputText1 = !1;
                                        this.updateInlineEnableSate()
                                    }), 1500))
                                }
                                this.updateInlineEnableSate()
                            }));
                            TextInput.onSubmit((t => {
                                if (-1 != this.timeoutID1) {
                                    clearTimeout(this.timeoutID1);
                                    this.timeoutID1 = -1
                                }
                                this.hasInputText1 = !1;
                                this.value -= 1;
                                if (Number(this.inputValue) >= this.min && Number(this.inputValue) <= this.max) {
                                    this.value = Number(this.inputValue);
                                    this.updateInlineEnableSate()
                                } else {
                                    this.value += 1;
                                    this.inputValue = this.value.toString()
                                }
                            }));
                            TextInput.focusable(this.focusEnable);
                            TextInput.focusOnTouch(!0);
                            TextInput.onFocus((() => {
                                this.focusText = FocusText.TEXT1;
                                this.hasFocusText1 = !0;
                                this.controller1.caretPosition(this.value.toString().length)
                            }));
                            TextInput.onBlur((() => {
                                this.focusText = FocusText.NONE;
                                this.hasFocusText1 = !1
                            }));
                            TextInput.onClick((t => {
                                this.focusText = FocusText.TEXT1;
                                this.hasFocusText1 = !0;
                                this.focusWithTarget("InlineTextInput" + this.timeStamp.toString());
                                this.controller1.caretPosition(this.value.toString().length)
                            }));
                            e || TextInput.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        RelativeContainer.pop()
                    })) : this.ifElseBranchUpdateFunction(1, (() => {
                        this.observeComponentCreation(((t, e) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            Row.create();
                            Row.margin({ left: "12vp", right: "12vp" });
                            e || Row.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        this.observeComponentCreation(((t, e) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            TextInput.create({
                                text: this.hasInputText1 ? this.inputValue : this.value.toString(),
                                controller: this.controller1
                            });
                            TextInput.width(9.6 * this.getValueLength());
                            TextInput.height("20vp");
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
                            TextInput.backgroundColor(this.hasFocusText1 ?
                                CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent);
                            TextInput.key("InlineTextInput" + this.timeStamp.toString());
                            TextInput.onKeyEvent((t => {
                                this.focusCurrentText(FocusText.TEXT1);
                                if (t.keyCode === CounterConstant.KEYCODE_ESC) {
                                    this.resetFocusText();
                                    t.stopPropagation()
                                }
                                if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                                    this.addValue();
                                    t.stopPropagation()
                                }
                                if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                                    this.subValue();
                                    t.stopPropagation()
                                }
                                if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                                    this.focusWithTarget("InlineTextInput" + this.timeStamp.toString());
                                    t.stopPropagation()
                                }
                                if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                                    this.focusWithTarget("InlineTextInput" + this.timeStamp.toString());
                                    t.stopPropagation()
                                }
                            }));
                            TextInput.onChange((t => {
                                this.inputValue = t;
                                for (let e = 0;e < t.length; e++) {
                                    let o = t[e];
                                    if ("+" === o || "*" === o || "#" === o) {
                                        this.value -= 1;
                                        this.value += 1;
                                        this.inputValue = this.value.toString();
                                        return
                                    }
                                    if ("-" === o && 0 !== e) {
                                        this.inputValue = o;
                                        break
                                    }
                                }
                                this.hasInputText1 = !0;
                                let e = t[t.length-1];
                                t.length === this.getMaxLength() && (this.inputValue = e);
                                if (-1 !== this.timeoutID1) {
                                    clearTimeout(this.timeoutID1);
                                    this.timeoutID1 = -1
                                }
                                if ("" !== this.inputValue && Number(this.inputValue) <= this.max &&
                                    Number(this.inputValue) >= this.min) {
                                    this.value = Number(this.inputValue);
                                    this.hasInputText1 = !1
                                } else {
                                    (Number(this.inputValue) > this.max || Number(this.inputValue) < this.min &&
                                        this.inputValue.length <= this.min.toString().length) && (this.inputValue = e);
                                    t.length < this.getMaxLength() && (this.timeoutID1 = setTimeout((() => {
                                        "" !== this.inputValue && Number(this.inputValue) <= this.max &&
                                            Number(this.inputValue) >= this.min &&
                                            (this.value = Number(this.inputValue));
                                        this.inputValue = this.value.toString();
                                        this.hasInputText1 = !1;
                                        this.updateInlineEnableSate()
                                    }), 1500))
                                }
                                this.updateInlineEnableSate()
                            }));
                            TextInput.onSubmit((t => {
                                if (-1 !== this.timeoutID1) {
                                    clearTimeout(this.timeoutID1);
                                    this.timeoutID1 = -1
                                }
                                this.hasInputText1 = !1;
                                this.value -= 1;
                                if (Number(this.inputValue) >= this.min && Number(this.inputValue) <= this.max) {
                                    this.value = Number(this.inputValue);
                                    this.updateInlineEnableSate()
                                } else {
                                    this.value += 1;
                                    this.inputValue = this.value.toString()
                                }
                            }));
                            TextInput.focusable(this.focusEnable);
                            TextInput.focusOnTouch(!0);
                            TextInput.onFocus((() => {
                                this.focusText = FocusText.TEXT1;
                                this.hasFocusText1 = !0;
                                this.controller1.caretPosition(this.value.toString().length)
                            }));
                            TextInput.onBlur((() => {
                                this.focusText = FocusText.NONE;
                                this.hasFocusText1 = !1
                            }));
                            TextInput.onClick((t => {
                                this.focusText = FocusText.TEXT1;
                                this.hasFocusText1 = !0;
                                this.focusWithTarget("InlineTextInput" + this.timeStamp.toString());
                                this.controller1.caretPosition(this.value.toString().length)
                            }));
                            e || TextInput.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Row.pop()
                    }));
                    e || If.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                If.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Column.create();
                    Column.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                    Column.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                    Column.borderWidth({ left: CounterResource.COUNTER_BORDER_WIDTH });
                    Column.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                    e || Column.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Stack.create();
                    Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                    Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                    Stack.padding({ top: "1vp" });
                    Stack.borderWidth({ bottom: "1vp" });
                    Stack.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                    Stack.clip(!0);
                    e || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Rect.create();
                    Rect.width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH);
                    Rect.height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT);
                    Rect.radius([["0vp", "0vp"], [CounterResource.COUNTER_INLINE_RADIUS,
                        CounterResource.COUNTER_INLINE_RADIUS], ["0vp", "0vp"], ["0vp", "0vp"]]);
                    Rect.strokeWidth(this.addBtnFocusWidh);
                    Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                    Rect.margin({ right: "2vp" });
                    Rect.fillOpacity(0);
                    e || Rect.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Image.create(CounterResource.BUTTON_ARROW_UP);
                    Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
                    Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
                    Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                    Image.opacity(this.addOpacity);
                    e || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect });
                    Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                    Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                    Button.backgroundColor(Color.Transparent);
                    Button.opacity(this.addOpacity);
                    Button.enabled(this.addBtnEnabled);
                    Button.onClick((t => {
                        this.addValue();
                        this.onChange && this.onChange(this.value);
                        t.source !== SourceType.Mouse && t.source !== SourceType.TouchScreen ||
                            (this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH)
                    }));
                    Gesture.create(GesturePriority.Low);
                    LongPressGesture.create({ repeat: !0 });
                    LongPressGesture.onAction((t => {
                        if (t.repeat) {
                            this.addValue();
                            this.onChange && this.onChange(this.value)
                        }
                        this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                    }));
                    LongPressGesture.pop();
                    Gesture.pop();
                    Button.hoverEffect(this.choverEffect);
                    Button.onHover((t => {
                        this.onHoverIncrease && this.onHoverIncrease(t)
                    }));
                    Button.focusable(!1);
                    Button.onFocus((() => {
                        this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                        this.onFocusIncrease && this.onFocusIncrease()
                    }));
                    Button.onBlur((() => {
                        this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        this.onBlurIncrease && this.onBlurIncrease()
                    }));
                    e || Button.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Button.pop();
                Stack.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Stack.create();
                    Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                    Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                    Stack.clip(!0);
                    e || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Rect.create();
                    Rect.width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH);
                    Rect.height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT);
                    Rect.radius([["0vp", "0vp"], ["0vp", "0vp"], [CounterResource.COUNTER_INLINE_RADIUS,
                        CounterResource.COUNTER_INLINE_RADIUS], ["0vp", "0vp"]]);
                    Rect.strokeWidth(this.subBtnFocusWidh);
                    Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                    Rect.margin({ top: "1vp", right: "1vp", bottom: "2vp" });
                    Rect.fillOpacity(0);
                    e || Rect.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Image.create(CounterResource.BUTTON_ARROW_DOWN);
                    Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
                    Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
                    Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                    Image.opacity(this.subOpacity);
                    e || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect });
                    Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                    Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                    Button.backgroundColor(Color.Transparent);
                    Button.opacity(this.subOpacity);
                    Button.enabled(this.subBtnEnabled);
                    Button.onClick((t => {
                        this.subValue();
                        this.onChange && this.onChange(this.value);
                        t.source !== SourceType.Mouse && t.source !== SourceType.TouchScreen ||
                            (this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH)
                    }));
                    Gesture.create(GesturePriority.Low);
                    LongPressGesture.create({ repeat: !0 });
                    LongPressGesture.onAction((t => {
                        if (t.repeat) {
                            this.subValue();
                            this.onChange && this.onChange(this.value)
                        }
                        this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                    }));
                    LongPressGesture.pop();
                    Gesture.pop();
                    Button.hoverEffect(this.choverEffect);
                    Button.onHover((t => {
                        this.onHoverDecrease && this.onHoverDecrease(t)
                    }));
                    Button.focusable(!1);
                    Button.onFocus((() => {
                        this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                        this.onFocusDecrease && this.onFocusDecrease()
                    }));
                    Button.onBlur((() => {
                        this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        this.onBlurDecrease && this.onBlurDecrease()
                    }));
                    e || Button.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Button.pop();
                Stack.pop();
                Column.pop();
                Row.pop()
            })) : this.type === CounterType.INLINE_DATE ? this.ifElseBranchUpdateFunction(3, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Row.create();
                    Row.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                    Row.borderWidth(CounterResource.COUNTER_BORDER_WIDTH);
                    Row.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                    Row.borderRadius(CounterResource.COUNTER_INLINE_RADIUS);
                    Row.clip(!0);
                    e || Row.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Row.create();
                    Row.width("92vp");
                    Row.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                    Row.margin({
                        left: CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN,
                        right: CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN
                    });
                    e || Row.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    TextInput.create({
                        text: this.hasInputText1 ? this.inputYear.toString() : this.getYear(),
                        controller: this.controller1
                    });
                    TextInput.type(InputType.Number);
                    TextInput.caretColor(Color.Transparent);
                    TextInput.copyOption(CopyOptions.None);
                    TextInput.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                    TextInput.fontWeight(FontWeight.Medium);
                    TextInput.fontColor(this.hasFocusText1 ? Color.White : CounterResource.COUNTER_TEXT_COLOR);
                    TextInput.maxLength(5);
                    TextInput.padding(0);
                    TextInput.backgroundColor(this.hasFocusText1 ?
                        CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent);
                    TextInput.width("38vp");
                    TextInput.height("20vp");
                    TextInput.borderRadius(0);
                    TextInput.borderWidth(0);
                    TextInput.key("DateTextInput1" + this.timeStamp.toString());
                    TextInput.onKeyEvent((t => {
                        this.focusCurrentText(FocusText.TEXT1);
                        if (t.keyCode === CounterConstant.KEYCODE_ESC) {
                            this.resetFocusText();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                            this.addDate();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                            this.subDate();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                            this.homeFocusText();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                            this.endFocusText();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                            this.focusWithTarget("DateTextInput1" + this.timeStamp.toString());
                            t.stopPropagation()
                        }
                        t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT &&
                            this.focusWithTarget("DateTextInput2" + this.timeStamp.toString())
                    }));
                    TextInput.onChange((t => {
                        4 !== t.length && (this.hasInputText1 = !0);
                        this.inputYear = Number(t);
                        5 === t.length && (this.inputYear = this.inputYear % 10);
                        if (-1 !== this.timeoutID1) {
                            clearTimeout(this.timeoutID1);
                            this.timeoutID1 = -1
                        }
                        this.timeoutID1 = setTimeout((() => {
                            this.hasInputText1 = !1;
                            this.inputYear = this.year;
                            this.updateDateEnableSate();
                            this.updateDay()
                        }), 1500);
                        if (this.inputYear >= this.minYear && this.inputYear <= this.maxYear) {
                            this.year = this.inputYear;
                            this.updateDateEnableSate();
                            this.updateDay()
                        }
                    }));
                    TextInput.onSubmit((t => {
                        if (-1 !== this.timeoutID1) {
                            clearTimeout(this.timeoutID1);
                            this.timeoutID1 = -1
                        }
                        this.hasInputText1 = !1;
                        this.year -= 1;
                        if (this.inputYear >= this.minYear && this.inputYear <= this.maxYear)
                            this.year = this.inputYear;
                        else {
                            this.year += 1;
                            this.inputYear = this.year
                        }
                        this.updateDateEnableSate();
                        this.updateDay()
                    }));
                    TextInput.tabIndex(0);
                    TextInput.focusOnTouch(!0);
                    TextInput.focusable(!0);
                    TextInput.onFocus((() => {
                        this.focusText = FocusText.TEXT1;
                        this.hasFocusText1 = !0;
                        this.updateDateEnableSate();
                        this.controller1.caretPosition(this.getYear().length)
                    }));
                    TextInput.onBlur((() => {
                        this.focusText = FocusText.NONE;
                        this.hasFocusText1 = !1;
                        this.updateDateEnableSate()
                    }));
                    TextInput.onClick((t => {
                        this.focusText = FocusText.TEXT1;
                        this.hasFocusText1 = !0;
                        this.updateDateEnableSate();
                        this.controller1.caretPosition(this.getYear().length)
                    }));
                    e || TextInput.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Text.create("/");
                    Text.textAlign(TextAlign.Center);
                    Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                    Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                    Text.width("8vp");
                    e || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    TextInput.create({
                        text: this.hasInputText2 ? this.inputMoon.toString() : this.convertNumberToString(this.month),
                        controller: this.controller2
                    });
                    TextInput.type(InputType.Number);
                    TextInput.caretColor(Color.Transparent);
                    TextInput.copyOption(CopyOptions.None);
                    TextInput.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                    TextInput.fontWeight(FontWeight.Medium);
                    TextInput.fontColor(this.hasFocusText2 ? Color.White : CounterResource.COUNTER_TEXT_COLOR);
                    TextInput.maxLength(3);
                    TextInput.padding(0);
                    TextInput.backgroundColor(this.hasFocusText2 ?
                        CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent);
                    TextInput.width("19vp");
                    TextInput.height("20vp");
                    TextInput.borderRadius(0);
                    TextInput.key("DateTextInput2" + this.timeStamp.toString());
                    TextInput.onKeyEvent((t => {
                        this.focusCurrentText(FocusText.TEXT2);
                        if (t.keyCode === CounterConstant.KEYCODE_ESC) {
                            this.resetFocusText();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                            this.subDate();
                            this.updateDay();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                            this.addDate();
                            this.updateDay();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                            this.homeFocusText();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                            this.endFocusText();
                            t.stopPropagation()
                        }
                        t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_LEFT &&
                            this.focusWithTarget("DateTextInput1" + this.timeStamp.toString());
                        t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT &&
                            this.focusWithTarget("DateTextInput3" + this.timeStamp.toString());
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_TAB) {
                            t.stopPropagation();
                            this.focusWithTarget("DateTextInput1" + this.timeStamp.toString())
                        }
                    }));
                    TextInput.onChange((t => {
                        this.inputMoon = Number(t);
                        2 !== t.length && (this.hasInputText2 = !0);
                        3 === t.length && (this.inputMoon = this.inputMoon % 10);
                        if (-1 !== this.timeoutID2) {
                            clearTimeout(this.timeoutID2);
                            this.timeoutID2 = -1
                        }
                        this.timeoutID2 = setTimeout((() => {
                            this.hasInputText2 = !1;
                            this.month -= 1;
                            if (this.inputMoon >= 1 && this.inputMoon <= 12)
                                this.month = this.inputMoon;
                            else {
                                this.month += 1;
                                this.inputMoon = this.month
                            }
                            this.updateDay()
                        }), 1e3);
                        if (2 === t.length) {
                            this.hasInputText2 = !1;
                            this.month -= 1;
                            if (this.inputMoon >= 1 && this.inputMoon <= 12)
                                this.month = this.inputMoon;
                            else {
                                this.month += 1;
                                this.inputMoon = this.month
                            }
                            this.updateDay()
                        }
                    }));
                    TextInput.onSubmit((t => {
                        if (-1 !== this.timeoutID2) {
                            clearTimeout(this.timeoutID2);
                            this.timeoutID2 = -1
                        }
                        this.hasInputText2 = !1;
                        this.month -= 1;
                        if (this.inputMoon >= 1 && this.inputMoon <= 12) {
                            this.month = this.inputMoon;
                            this.updateDay()
                        } else this.month += 1
                    }));
                    TextInput.focusOnTouch(!0);
                    TextInput.tabIndex(-1);
                    TextInput.focusable(!0);
                    TextInput.onFocus((() => {
                        this.focusText = FocusText.TEXT2;
                        this.hasFocusText2 = !0;
                        this.controller2.caretPosition(this.convertNumberToString(this.month).length)
                    }));
                    TextInput.onBlur((() => {
                        this.focusText = FocusText.NONE;
                        this.hasFocusText2 = !1
                    }));
                    TextInput.onClick((t => {
                        this.focusText = FocusText.TEXT2;
                        this.hasFocusText2 = !0;
                        this.controller2.caretPosition(this.convertNumberToString(this.month).length)
                    }));
                    e || TextInput.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Text.create("/");
                    Text.textAlign(TextAlign.Center);
                    Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                    Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                    Text.width("8vp");
                    e || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    TextInput.create({
                        text: this.hasInputText3 ? this.inputDay.toString() : this.convertNumberToString(this.day),
                        controller: this.controller3
                    });
                    TextInput.type(InputType.Number);
                    TextInput.caretColor(Color.Transparent);
                    TextInput.copyOption(CopyOptions.None);
                    TextInput.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                    TextInput.fontWeight(FontWeight.Medium);
                    TextInput.fontColor(this.hasFocusText3 ? Color.White : CounterResource.COUNTER_TEXT_COLOR);
                    TextInput.maxLength(3);
                    TextInput.padding(0);
                    TextInput.backgroundColor(this.hasFocusText3 ?
                        CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent);
                    TextInput.width("19vp");
                    TextInput.height("20vp");
                    TextInput.borderRadius(0);
                    TextInput.key("DateTextInput3" + this.timeStamp.toString());
                    TextInput.onKeyEvent((t => {
                        this.focusCurrentText(FocusText.TEXT3);
                        if (t.keyCode === CounterConstant.KEYCODE_ESC) {
                            this.resetFocusText();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                            this.subDate();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                            this.addDate();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                            this.homeFocusText();
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                            this.endFocusText();
                            t.stopPropagation()
                        }
                        t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_LEFT &&
                            this.focusWithTarget("DateTextInput2" + this.timeStamp.toString());
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                            this.focusWithTarget("DateTextInput3" + this.timeStamp.toString());
                            t.stopPropagation()
                        }
                        if (t.type === KeyType.Down && t.keyCode === CounterConstant.KEYCODE_TAB) {
                            t.stopPropagation();
                            this.focusWithTarget("DateTextInput1" + this.timeStamp.toString())
                        }
                    }));
                    TextInput.onChange((t => {
                        this.inputDay = Number(t);
                        2 !== t.length && (this.hasInputText3 = !0);
                        3 === t.length && (this.inputDay = this.inputDay % 10);
                        if (-1 !== this.timeoutID3) {
                            clearTimeout(this.timeoutID3);
                            this.timeoutID3 = -1
                        }
                        this.timeoutID3 = setTimeout((() => {
                            this.hasInputText3 = !1;
                            this.day -= 1;
                            if (this.inputDay >= 1 && this.inputDay <= this.getDayNumber())
                                this.day = this.inputDay;
                            else {
                                this.day += 1;
                                this.inputDay = this.day
                            }
                        }), 1e3);
                        if (2 === t.length) {
                            this.hasInputText3 = !1;
                            this.day -= 1;
                            if (this.inputDay >= 1 && this.inputDay <= this.getDayNumber())
                                this.day = this.inputDay;
                            else {
                                this.day += 1;
                                this.inputDay = this.day
                            }
                        }
                    }));
                    TextInput.onSubmit((t => {
                        if (-1 !== this.timeoutID3) {
                            clearTimeout(this.timeoutID3);
                            this.timeoutID3 = -1
                        }
                        this.hasInputText3 = !1;
                        this.day -= 1;
                        this.inputDay >= 1 && this.inputDay <= this.getDayNumber() ?
                            this.day = this.inputDay : this.day += 1
                    }));
                    TextInput.tabIndex(-2);
                    TextInput.focusOnTouch(!0);
                    TextInput.focusable(!0);
                    TextInput.onFocus((() => {
                        this.focusText = FocusText.TEXT3;
                        this.hasFocusText3 = !0;
                        this.controller3.caretPosition(this.convertNumberToString(this.day).length)
                    }));
                    TextInput.onBlur((() => {
                        this.focusText = FocusText.NONE;
                        this.hasFocusText3 = !1
                    }));
                    TextInput.onClick((t => {
                        this.focusText = FocusText.TEXT3;
                        this.hasFocusText3 = !0;
                        this.controller3.caretPosition(this.convertNumberToString(this.day).length)
                    }));
                    e || TextInput.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Row.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Column.create();
                    Column.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                    Column.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                    Column.borderWidth({ left: CounterResource.COUNTER_BORDER_WIDTH });
                    Column.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                    e || Column.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Stack.create();
                    Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                    Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                    Stack.padding({ top: "1vp" });
                    Stack.borderWidth({ bottom: "1vp" });
                    Stack.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                    Stack.clip(!0);
                    e || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Rect.create();
                    Rect.width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH);
                    Rect.height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT);
                    Rect.radius([["0vp", "0vp"], [CounterResource.COUNTER_INLINE_RADIUS,
                        CounterResource.COUNTER_INLINE_RADIUS], ["0vp", "0vp"], ["0vp", "0vp"]]);
                    Rect.strokeWidth(this.addBtnFocusWidh);
                    Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                    Rect.margin({ right: "1vp" });
                    Rect.fillOpacity(0);
                    e || Rect.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Image.create(CounterResource.BUTTON_ARROW_UP);
                    Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
                    Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
                    Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                    Image.opacity(this.addOpacity);
                    e || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect });
                    Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                    Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                    Button.backgroundColor(Color.Transparent);
                    Button.opacity(this.addOpacity);
                    Button.enabled(this.addBtnEnabled);
                    Button.onClick((t => {
                        this.addDate();
                        let e = new DateData(this.year, this.month, this.day);
                        this.onDateChange && this.onDateChange(e);
                        t.source !== SourceType.Mouse && t.source !== SourceType.TouchScreen ||
                            (this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH)
                    }));
                    Gesture.create(GesturePriority.Low);
                    LongPressGesture.create({ repeat: !0 });
                    LongPressGesture.onAction((t => {
                        if (t.repeat) {
                            this.addDate();
                            let t = new DateData(this.year, this.month, this.day);
                            this.onDateChange && this.onDateChange(t)
                        }
                        this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                    }));
                    LongPressGesture.pop();
                    Gesture.pop();
                    Button.hoverEffect(this.choverEffect);
                    Button.onHover((t => {
                        this.onHoverIncrease && this.onHoverIncrease(t)
                    }));
                    Button.focusable(!1);
                    Button.onFocus((() => {
                        this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                        this.onFocusIncrease && this.onFocusIncrease()
                    }));
                    Button.onBlur((() => {
                        this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        this.onBlurIncrease && this.onBlurIncrease()
                    }));
                    e || Button.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Button.pop();
                Stack.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Stack.create();
                    Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                    Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                    Stack.clip(!0);
                    e || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Rect.create();
                    Rect.width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH);
                    Rect.height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT);
                    Rect.radius([["0vp", "0vp"], ["0vp", "0vp"], [CounterResource.COUNTER_INLINE_RADIUS,
                        CounterResource.COUNTER_INLINE_RADIUS], ["0vp", "0vp"]]);
                    Rect.strokeWidth(this.subBtnFocusWidh);
                    Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                    Rect.margin({ top: "1vp", right: "1vp", bottom: "2vp" });
                    Rect.fillOpacity(0);
                    e || Rect.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Image.create(CounterResource.BUTTON_ARROW_DOWN);
                    Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
                    Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
                    Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                    Image.opacity(this.subOpacity);
                    e || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect });
                    Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                    Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                    Button.backgroundColor(Color.Transparent);
                    Button.opacity(this.subOpacity);
                    Button.enabled(this.subBtnEnabled);
                    Button.onClick((t => {
                        this.subDate();
                        let e = new DateData(this.year, this.month, this.day);
                        this.onDateChange && this.onDateChange(e);
                        t.source !== SourceType.Mouse && t.source !== SourceType.TouchScreen ||
                            (this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH)
                    }));
                    Gesture.create(GesturePriority.Low);
                    LongPressGesture.create({ repeat: !0 });
                    LongPressGesture.onAction((t => {
                        if (t.repeat) {
                            this.subDate();
                            let t = new DateData(this.year, this.month, this.day);
                            this.onDateChange && this.onDateChange(t)
                        }
                        this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                    }));
                    LongPressGesture.pop();
                    Gesture.pop();
                    Button.hoverEffect(this.choverEffect);
                    Button.onHover((t => {
                        this.onHoverDecrease && this.onHoverDecrease(t)
                    }));
                    Button.focusable(!1);
                    Button.onFocus((() => {
                        this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                        this.onFocusDecrease && this.onFocusDecrease()
                    }));
                    Button.onBlur((() => {
                        this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        this.onBlurDecrease && this.onBlurDecrease()
                    }));
                    e || Button.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Button.pop();
                Stack.pop();
                Column.pop();
                Row.pop()
            })) : this.ifElseBranchUpdateFunction(4, (() => {
            }));
            e || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

export default {CounterType, CommonOptions, InlineStyleOptions, NumberStyleOptions,
    DateData, DateStyleOptions, CounterOptions, CounterComponent};
