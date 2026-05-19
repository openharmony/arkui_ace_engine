/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        r = Reflect.decorate(decorators, target, key, desc);
    else
        for (var i = decorators.length - 1; i >= 0; i--)
            if (d = decorators[i])
                r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const accessibility = requireNapi('accessibility');
const intl = requireNapi('intl');
const i18n = requireNapi('i18n');
const systemDateTime = requireNapi('systemDateTime');
export var CounterV2Type;
(function (CounterV2Type) {
    CounterV2Type[CounterV2Type["LIST"] = 0] = "LIST";
    CounterV2Type[CounterV2Type["COMPACT"] = 1] = "COMPACT";
    CounterV2Type[CounterV2Type["INLINE"] = 2] = "INLINE";
    CounterV2Type[CounterV2Type["INLINE_DATE"] = 3] = "INLINE_DATE";
})(CounterV2Type || (CounterV2Type = {}));
var FocusText;
(function (FocusText) {
    FocusText[FocusText["NONE"] = 0] = "NONE";
    FocusText[FocusText["TEXT1"] = 1] = "TEXT1";
    FocusText[FocusText["TEXT2"] = 2] = "TEXT2";
    FocusText[FocusText["TEXT3"] = 3] = "TEXT3";
})(FocusText || (FocusText = {}));
let CounterV2CommonOptions = class CounterV2CommonOptions {
};
__decorate([
    Trace
], CounterV2CommonOptions.prototype, "focusable", void 0);
__decorate([
    Trace
], CounterV2CommonOptions.prototype, "step", void 0);
CounterV2CommonOptions = __decorate([
    ObservedV2
], CounterV2CommonOptions);
export { CounterV2CommonOptions };
let CounterV2InlineStyleOptions = class CounterV2InlineStyleOptions extends CounterV2CommonOptions {
};
__decorate([
    Trace
], CounterV2InlineStyleOptions.prototype, "value", void 0);
__decorate([
    Trace
], CounterV2InlineStyleOptions.prototype, "min", void 0);
__decorate([
    Trace
], CounterV2InlineStyleOptions.prototype, "max", void 0);
__decorate([
    Trace
], CounterV2InlineStyleOptions.prototype, "textWidth", void 0);
CounterV2InlineStyleOptions = __decorate([
    ObservedV2
], CounterV2InlineStyleOptions);
export { CounterV2InlineStyleOptions };
let CounterV2NumberStyleOptions = class CounterV2NumberStyleOptions extends CounterV2InlineStyleOptions {
};
__decorate([
    Trace
], CounterV2NumberStyleOptions.prototype, "label", void 0);
CounterV2NumberStyleOptions = __decorate([
    ObservedV2
], CounterV2NumberStyleOptions);
export { CounterV2NumberStyleOptions };
export class CounterV2DateData {
    constructor(year, month, day) {
        this.year = year;
        this.month = month;
        this.day = day;
    }
    toString() {
        let date = this.year.toString() + '-';
        let month = this.month < 10 ? '0' + this.month.toString() : this.month.toString();
        date += month + '-';
        let day = this.day < 10 ? '0' + this.day.toString() : this.day.toString();
        date += day;
        return date;
    }
}
let CounterV2DateStyleOptions = class CounterV2DateStyleOptions extends CounterV2CommonOptions {
};
__decorate([
    Trace
], CounterV2DateStyleOptions.prototype, "year", void 0);
__decorate([
    Trace
], CounterV2DateStyleOptions.prototype, "month", void 0);
__decorate([
    Trace
], CounterV2DateStyleOptions.prototype, "day", void 0);
CounterV2DateStyleOptions = __decorate([
    ObservedV2
], CounterV2DateStyleOptions);
export { CounterV2DateStyleOptions };
let CounterV2Options = class CounterV2Options {
    constructor() {
        this.type = CounterV2Type.LIST;
    }
};
__decorate([
    Trace
], CounterV2Options.prototype, "type", void 0);
__decorate([
    Trace
], CounterV2Options.prototype, "direction", void 0);
__decorate([
    Trace
], CounterV2Options.prototype, "numberOptions", void 0);
__decorate([
    Trace
], CounterV2Options.prototype, "inlineOptions", void 0);
__decorate([
    Trace
], CounterV2Options.prototype, "dateOptions", void 0);
CounterV2Options = __decorate([
    ObservedV2
], CounterV2Options);
export { CounterV2Options };
class CounterResource {
}
CounterResource.BUTTON_BACKGROUD_COLOR = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.BUTTON_ICON_COLOR = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.BUTTON_BORDER_FOCUSED_COLOR = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.COUNTER_TEXT_COLOR = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.COUNTER_BORDER_COLOR = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_component_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.BUTTON_ADD_ICON = { "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_add"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.BUTTON_SUB_ICON = { "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_minus"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.BUTTON_ARROW_UP = { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_arrow_up'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.BUTTON_ARROW_DOWN = { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_arrow_down'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.BUTTON_BORDER_FOCUSED_WIDTH = '2vp';
CounterResource.BUTTON_BORDER_BLUR_WIDTH = '0vp';
CounterResource.COUNTER_BORDER_WIDTH_NUMBER = 1;
CounterResource.COUNTER_LIST_LABEL_SIZE = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.COUNTER_LIST_NUMBER_SIZE = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.COUNTER_COMPACT_LABEL_SIZE = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.COUNTER_NUMBER_SIZE = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.COUNTER_LIST_LEFT_PADDING = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_default_padding_start'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.COUNTER_LIST_RIGHT_PADDING = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_default_padding_end'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE = { "id": -1, "type": 10002, params: ['sys.float.button_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.COUNTER_COMPACT_CONTAINER_HEIGHT = { "id": -1, "type": 10002, params: ['sys.float.container_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.COUNTER_BORDER_WIDTH = { "id": -1, "type": 10002, params: ['sys.float.border_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.COUNTER_COMPACT_BUTTON_SIZE = { "id": -1, "type": 10002, params: ['sys.float.button_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.COUNTER_COMPACT_CONTAINER_RADIUS = { "id": -1, "type": 10002, params: ['sys.float.container_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
CounterResource.COUNTER_COMPACT_BUTTON_CONTAINER_MARGIN = { "id": -1, "type": 10002, params: ['sys.float.button_container_margin'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
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
CounterResource.COUNTER_COMPACT_BUTTON_RADIUS = '12vp';
CounterResource.COUNTER_COMPACT_BUTTON_TEXT_DISTANCE = '10vp';
CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN = 10;
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
CounterResource.COUNTER_LABEL_MAX_FONT_SIZE_SCALE = 2;
CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE = 1;
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
export class CounterV2Component extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("options", (params && "options" in params) ? params.options : undefined);
        this.type = -1;
        this.counterDirection = Direction.Auto;
        this.choverEffect = HoverEffect.Auto;
        this.focusEnable = true;
        this.step = CounterConstant.COUNTER_INITIAL_STEP;
        this.inputValue = '0';
        this.inputYear = CounterConstant.COUNTER_MIN_YEAR;
        this.inputMoon = 0;
        this.inputDay = 0;
        this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.subBtnStateEffect = true;
        this.addBtnStateEffect = true;
        this.focusText = FocusText.NONE;
        this.hasFocusText1 = false;
        this.hasFocusText2 = false;
        this.hasFocusText3 = false;
        this.subBtnFocusWidth = '0vp';
        this.addBtnFocusWidth = '0vp';
        this.value = 0;
        this.year = 0;
        this.month = 0;
        this.day = 0;
        this.hour = 0;
        this.minute = 0;
        this.second = 0;
        this.subBtnEnabled = true;
        this.addBtnEnabled = true;
        this.hasInputText1 = false;
        this.hasInputText2 = false;
        this.hasInputText3 = false;
        this.textWidth = 0;
        this.min = CounterConstant.COUNTER_MIN_VALUE;
        this.max = CounterConstant.COUNTER_MAX_VALUE;
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
        this.numberStyleOptions = new CounterV2NumberStyleOptions();
        this.dateStyleOptions = new CounterV2DateStyleOptions();
        this.inlineStyleOptions = new CounterV2InlineStyleOptions();
        this.timeStamp = 0;
        this.hasTextWidth = false;
        this.controller1 = new TextInputController();
        this.controller2 = new TextInputController();
        this.controller3 = new TextInputController();
        this.yearTextWidth = 0;
        this.monthDayTextWidth = 0;
        this.dateDayMap = null;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("options", (params && "options" in params) ? params.options : undefined);
        this.type = -1;
        this.counterDirection = Direction.Auto;
        this.choverEffect = HoverEffect.Auto;
        this.focusEnable = true;
        this.step = CounterConstant.COUNTER_INITIAL_STEP;
        this.inputValue = '0';
        this.inputYear = CounterConstant.COUNTER_MIN_YEAR;
        this.inputMoon = 0;
        this.inputDay = 0;
        this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.subBtnStateEffect = true;
        this.addBtnStateEffect = true;
        this.focusText = FocusText.NONE;
        this.hasFocusText1 = false;
        this.hasFocusText2 = false;
        this.hasFocusText3 = false;
        this.subBtnFocusWidth = '0vp';
        this.addBtnFocusWidth = '0vp';
        this.value = 0;
        this.year = 0;
        this.month = 0;
        this.day = 0;
        this.hour = 0;
        this.minute = 0;
        this.second = 0;
        this.subBtnEnabled = true;
        this.addBtnEnabled = true;
        this.hasInputText1 = false;
        this.hasInputText2 = false;
        this.hasInputText3 = false;
        this.textWidth = 0;
        this.min = CounterConstant.COUNTER_MIN_VALUE;
        this.max = CounterConstant.COUNTER_MAX_VALUE;
        this.resetMonitorsOnReuse();
    }
    getTextInputFontSize() {
        let fontSize = this.resourceToVp(CounterResource.COUNTER_NUMBER_SIZE);
        let uiContext = this.getUIContext();
        let fontSizeScale = uiContext.getHostContext()?.config?.fontSizeScale ?? 1;
        if (fontSizeScale < 1) {
            return fontSize + 'fp';
        }
        else {
            return fontSize + 'vp';
        }
    }
    getMeasuredTextWidth(text) {
        let measureUtils = this.getUIContext().getMeasureUtils();
        let widthPx = measureUtils.measureText({
            textContent: text,
            fontSize: this.getTextInputFontSize(),
            fontWeight: FontWeight.Medium,
        });
        return px2vp(widthPx);
    }
    getDate(value) {
        return `[n2] ${value} [n0]`;
    }
    getDateYear(value) {
        let locale = new intl.Locale();
        let localeID = locale.toString();
        let date = new Date(this.year, this.month - 1, this.day);
        date.setFullYear(this.year);
        let dateFormatYear;
        try {
            dateFormatYear = new Intl.DateTimeFormat(localeID, {
                year: 'numeric',
                timeZone: systemDateTime.getTimezoneSync(),
            });
        }
        catch (error) {
            console.log(`Accessility getDateYear fail. message: ${error.message}, code: ${error.code}`);
        }
        if (!dateFormatYear) {
            dateFormatYear = new Intl.DateTimeFormat(localeID, { year: 'numeric' });
        }
        let formattedDateYear = dateFormatYear.format(date);
        return this.getDate(formattedDateYear);
    }
    getDateMonth(value) {
        let locale = new intl.Locale();
        let localeID = locale.toString();
        let date = new Date(this.year, this.month - 1, this.day);
        date.setFullYear(this.year);
        let dateFormatMonth;
        try {
            dateFormatMonth = new Intl.DateTimeFormat(localeID, {
                month: 'long',
                timeZone: systemDateTime.getTimezoneSync()
            });
        }
        catch (error) {
            console.log(`Accessility getDateMonth fail. message: ${error.message}, code: ${error.code}`);
        }
        if (!dateFormatMonth) {
            dateFormatMonth = new Intl.DateTimeFormat(localeID, { month: 'long' });
        }
        let formattedDateMonth = dateFormatMonth.format(date);
        return this.getDate(formattedDateMonth);
    }
    getDateDay(value) {
        try {
            if (!this.dateDayMap) {
                const manager = this.getUIContext().getHostContext()?.resourceManager;
                if (!manager) {
                    return this.getDate('');
                }
                this.dateDayMap = new Map([
                    [1, manager.getStringByNameSync('First_counter_accessibility_text')],
                    [2, manager.getStringByNameSync('Second_counter_accessibility_text')],
                    [3, manager.getStringByNameSync('Third_counter_accessibility_text')],
                    [4, manager.getStringByNameSync('Fourth_counter_accessibility_text')],
                    [5, manager.getStringByNameSync('Fifth_counter_accessibility_text')],
                    [6, manager.getStringByNameSync('Sixth_counter_accessibility_text')],
                    [7, manager.getStringByNameSync('Seventh_counter_accessibility_text')],
                    [8, manager.getStringByNameSync('Eighth_counter_accessibility_text')],
                    [9, manager.getStringByNameSync('Ninth_counter_accessibility_text')],
                    [10, manager.getStringByNameSync('Tenth_counter_accessibility_text')],
                    [11, manager.getStringByNameSync('Eleventh_counter_accessibility_text')],
                    [12, manager.getStringByNameSync('Twelfth_counter_accessibility_text')],
                    [13, manager.getStringByNameSync('Thirteenth_counter_accessibility_text')],
                    [14, manager.getStringByNameSync('Fourteenth_counter_accessibility_text')],
                    [15, manager.getStringByNameSync('Fifteenth_counter_accessibility_text')],
                    [16, manager.getStringByNameSync('Sixteenth_counter_accessibility_text')],
                    [17, manager.getStringByNameSync('Seventeenth_counter_accessibility_text')],
                    [18, manager.getStringByNameSync('Eighteenth_counter_accessibility_text')],
                    [19, manager.getStringByNameSync('Nineteenth_counter_accessibility_text')],
                    [20, manager.getStringByNameSync('Twentieth_counter_accessibility_text')],
                    [21, manager.getStringByNameSync('TwentyFirst_counter_accessibility_text')],
                    [22, manager.getStringByNameSync('TwentySecond_counter_accessibility_text')],
                    [23, manager.getStringByNameSync('TwentyThird_counter_accessibility_text')],
                    [24, manager.getStringByNameSync('TwentyFourth_counter_accessibility_text')],
                    [25, manager.getStringByNameSync('TwentyFifth_counter_accessibility_text')],
                    [26, manager.getStringByNameSync('TwentySixth_counter_accessibility_text')],
                    [27, manager.getStringByNameSync('TwentySeventh_counter_accessibility_text')],
                    [28, manager.getStringByNameSync('TwentyEighth_counter_accessibility_text')],
                    [29, manager.getStringByNameSync('TwentyNinth_counter_accessibility_text')],
                    [30, manager.getStringByNameSync('Thirtieth_counter_accessibility_text')],
                    [31, manager.getStringByNameSync('ThirtyFirst_counter_accessibility_text')],
                ]);
            }
            return this.getDate(this.dateDayMap.get(this.day) ?? '');
        }
        catch (error) {
            console.log(`Accessility getDate fail. message: ${error.message}, code: ${error.code}`);
            return '';
        }
    }
    convertNumberToString(value) {
        if (value >= 0 && value < CounterConstant.COUNTER_TEN_NUMBER) {
            return this.numberStrList[value];
        }
        else {
            return value.toString();
        }
    }
    aboutToAppear() {
        let dateTime = new Date();
        this.timeStamp = dateTime.getTime();
        if (this.options !== undefined && this.options !== null) {
            this.applyOptions(this.options);
        }
    }
    updateNumberStyleOptions() {
        if (this.numberStyleOptions.label === undefined) {
            this.numberStyleOptions.label = '';
        }
        const prevValue = this.value;
        if (this.numberStyleOptions.value !== undefined) {
            this.value = this.numberStyleOptions.value;
        }
        else {
            this.value = 0;
        }
        this.inputValue = this.value.toString();
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
            this.inputValue = this.value.toString();
        }
        if (this.value >= this.max) {
            this.value = this.max;
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
        if (this.value !== prevValue) {
            this.onChange?.(this.value);
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
        const prevValue = this.value;
        const truncatedValue = Math.trunc(this.inlineStyleOptions.value ?? 0);
        this.value = Number.isFinite(truncatedValue) ? truncatedValue : 0;
        this.inputValue = this.value.toString();
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
            this.inputValue = this.value.toString();
        }
        if (this.value >= this.max) {
            this.value = this.max;
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
        if (this.value !== prevValue) {
            this.onChange?.(this.value);
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
                this.step = Math.floor(this.dateStyleOptions.step);
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
    applyOptions(options) {
        this.type = options.type;
        if (options.direction) {
            this.counterDirection = options.direction;
        }
        else {
            this.counterDirection = Direction.Auto;
        }
        if (this.type === CounterV2Type.LIST ||
            this.type === CounterV2Type.COMPACT) {
            if (options.numberOptions !== undefined) {
                this.numberStyleOptions = options.numberOptions;
            }
            this.updateNumberStyleOptions();
        }
        else if (this.type === CounterV2Type.INLINE) {
            if (options.inlineOptions !== undefined) {
                this.inlineStyleOptions = options.inlineOptions;
            }
            this.updateInlineStyleOptions();
        }
        else if (this.type === CounterV2Type.INLINE_DATE) {
            let dateOptions = options.dateOptions;
            if (dateOptions !== undefined) {
                dateOptions.year = dateOptions.year ? dateOptions.year : CounterConstant.COUNTER_MIN_YEAR;
                dateOptions.month = dateOptions.month ? dateOptions.month : CounterConstant.COUNTER_MIN_MONTH;
                dateOptions.day = dateOptions.day ? dateOptions.day : CounterConstant.COUNTER_MIN_DAY;
                this.dateStyleOptions = dateOptions;
            }
            this.updateDateStyleOptions();
            if (this.yearTextWidth <= 0) {
                this.yearTextWidth = this.getMeasuredTextWidth('0000');
            }
            if (this.monthDayTextWidth <= 0) {
                this.monthDayTextWidth = this.getMeasuredTextWidth('00');
            }
        }
        else {
        }
    }
    onOptionsChange(monitor) {
        const options = monitor.value('options')?.now;
        if (options === undefined) {
            return;
        }
        this.applyOptions(options);
    }
    subValue() {
        this.validateInlineInput();
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
        if (this.type === CounterV2Type.INLINE) {
            if (this.focusText === FocusText.NONE) {
                this.focusText = FocusText.TEXT1;
                this.hasFocusText1 = true;
                this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
            }
        }
    }
    validateInlineInput() {
        if (this.type !== CounterV2Type.INLINE) {
            return;
        }
        if (!this.hasInputText1) {
            return;
        }
        let num = Number(this.inputValue);
        if (this.inputValue !== '' && !isNaN(num) && Number.isInteger(num) && num <= this.max && num >= this.min) {
            this.value = num;
        }
        else {
            this.inputValue = this.value.toString();
        }
        this.hasInputText1 = false;
    }
    addValue() {
        this.validateInlineInput();
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
                return CounterConstant.SMALL_MONTH_DAYS;
                break;
        }
    }
    accessibilityBroadcastSubDate() {
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
            try {
                let eventInfo = ({
                    type: 'announceForAccessibility',
                    bundleName: this.getUIContext().getHostContext()?.abilityInfo?.bundleName,
                    triggerAction: 'click',
                    textAnnouncedForAccessibility: (this.getDateYear(this.year) + ',' + this.getDateYear(this.year) +
                        '/' +
                        this.getDateMonth(this.month) + '/' + this.getDateDay(this.day))
                });
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    console.log('Accessility subYear click send event');
                });
            }
            catch (exception) {
                let code = exception.code;
                let message = exception.message;
                console.log(`Accessility subYear faild error code:${code} message:${message}`);
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
            try {
                let eventInfo = ({
                    type: 'announceForAccessibility',
                    bundleName: this.getUIContext().getHostContext()?.abilityInfo?.bundleName,
                    triggerAction: 'click',
                    textAnnouncedForAccessibility: (this.getDateMonth(this.month) + ',' + this.getDateYear(this.year) +
                        '/' +
                        this.getDateMonth(this.month) + '/' + this.getDateDay(this.day))
                });
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    console.log('Accessility subMonth click send event');
                });
            }
            catch (exception) {
                let code = exception.code;
                let message = exception.message;
                console.log(`Accessility subMonth faild error code:${code} message:${message}`);
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
            try {
                let eventInfo = ({
                    type: 'announceForAccessibility',
                    bundleName: this.getUIContext().getHostContext()?.abilityInfo?.bundleName,
                    triggerAction: 'click',
                    textAnnouncedForAccessibility: (this.getDateDay(this.day) + ',' + this.getDateYear(this.year) +
                        '/' +
                        this.getDateMonth(this.month) + '/' + this.getDateDay(this.day))
                });
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    console.log('Accessility subDay click send event');
                });
            }
            catch (exception) {
                let code = exception.code;
                let message = exception.message;
                console.log(`Accessility subDay faild error code:${code} message:${message}`);
            }
        }
        else {
            this.focusDayWitdhSub();
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
    accessibilityBroadcastAddDate() {
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
            try {
                let eventInfo = ({
                    type: 'announceForAccessibility',
                    bundleName: this.getUIContext().getHostContext()?.abilityInfo?.bundleName,
                    triggerAction: 'click',
                    textAnnouncedForAccessibility: (this.getDateYear(this.year) + ',' + this.getDateYear(this.year) +
                        '/' +
                        this.getDateMonth(this.month) + '/' + this.getDateDay(this.day))
                });
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    console.log('Accessility addYear click send event');
                });
            }
            catch (exception) {
                let code = exception.code;
                let message = exception.message;
                console.log(`Accessility addYear click faild error code:${code} message:${message}`);
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
            try {
                let eventInfo = ({
                    type: 'announceForAccessibility',
                    bundleName: this.getUIContext().getHostContext()?.abilityInfo?.bundleName,
                    triggerAction: 'click',
                    textAnnouncedForAccessibility: (this.getDateMonth(this.month) + ',' + this.getDateYear(this.year) +
                        '/' +
                        this.getDateMonth(this.month) + '/' + this.getDateDay(this.day))
                });
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    console.log('Accessility addMonth click send event');
                });
            }
            catch (exception) {
                let code = exception.code;
                let message = exception.message;
                console.log(`Accessility addMonth faild error code:${code} message:${message}`);
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
            try {
                let eventInfo = ({
                    type: 'announceForAccessibility',
                    bundleName: this.getUIContext().getHostContext()?.abilityInfo?.bundleName,
                    triggerAction: 'click',
                    textAnnouncedForAccessibility: (this.getDateDay(this.day) + ',' + this.getDateYear(this.year) +
                        '/' +
                        this.getDateMonth(this.month) + '/' + this.getDateDay(this.day))
                });
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    console.log('Accessility addDay click send event');
                });
            }
            catch (exception) {
                let code = exception.code;
                let message = exception.message;
                console.log(`Accessility addDay faild error code:${code} message:${message}`);
            }
        }
        else {
            this.focusDayWithAdd();
        }
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
    updateInlineEnableState() {
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
    updateDateEnableState() {
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
        if (this.addBtnFocusWidth === CounterResource.BUTTON_BORDER_FOCUSED_WIDTH) {
            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
            this.onBlurIncrease && this.onBlurIncrease();
        }
        if (this.subBtnFocusWidth === CounterResource.BUTTON_BORDER_FOCUSED_WIDTH) {
            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
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
            if (!this.addBtnStateEffect && this.max !== this.min) {
                this.addBtnStateEffect = true;
                this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                this.addBtnEnabled = true;
            }
            this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.subBtnStateEffect = false;
            this.subBtnEnabled = false;
        }
        if (this.value >= this.max) {
            if (!this.subBtnStateEffect && this.max !== this.min) {
                this.subBtnStateEffect = true;
                this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                this.subBtnEnabled = true;
            }
            this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
            this.addBtnStateEffect = false;
            this.addBtnEnabled = false;
        }
        if (this.value > this.min && this.value < this.max) {
            if (!this.addBtnStateEffect) {
                this.addBtnStateEffect = true;
                this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                this.addBtnEnabled = true;
            }
            if (!this.subBtnStateEffect) {
                this.subBtnStateEffect = true;
                this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
                this.subBtnEnabled = true;
            }
        }
    }
    getValue() {
        if (this.inputValue === undefined || this.inputValue === null) {
            this.inputValue = '';
        }
        return this.hasInputText1 ? this.inputValue : this.value.toString();
    }
    getYear() {
        let year = this.year.toString();
        if (year.length === 1) {
            year = '000' + year;
        }
        else if (year.length === 2) {
            year = '00' + year;
        }
        else if (year.length === 3) {
            year = '0' + year;
        }
        else {
            year = year;
        }
        return year;
    }
    focusWithTarget(key) {
        setTimeout(() => {
            let res = focusControl.requestFocus(key);
            if (res) {
                console.log('Request success');
            }
            else {
                console.log('Request failed');
            }
        });
    }
    focusCurrentText(text) {
        if (text === FocusText.TEXT1) {
            if (this.focusText === FocusText.NONE) {
                this.focusText = FocusText.TEXT1;
            }
            if (!this.hasFocusText1) {
                this.hasFocusText1 = true;
            }
        }
        else if (text === FocusText.TEXT2) {
            if (this.focusText === FocusText.NONE) {
                this.focusText = FocusText.TEXT2;
            }
            if (!this.hasFocusText2) {
                this.hasFocusText2 = true;
            }
        }
        else if (text === FocusText.TEXT3) {
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
    resourceToVp(value) {
        try {
            if (value.id !== -1) {
                return px2vp(this.getUIContext().getHostContext()?.resourceManager.getNumber(value.id));
            }
            else {
                return px2vp(this.getUIContext().getHostContext()
                    ?.resourceManager
                    .getNumberByName((value.params[0]).split('.')[2]));
            }
        }
        catch (error) {
            return CounterResource.COUNTER_LIST_PADDING;
        }
    }
    getAccessibilityResource(resource) {
        let accessibilityResource = '';
        try {
            if (typeof resource === 'string') {
                accessibilityResource = resource;
            }
            else {
                accessibilityResource = this.getUIContext().getHostContext()?.resourceManager?.getStringSync(resource?.id) ?? '';
            }
        }
        catch (error) {
            let code = error.code;
            let message = error.message;
            console.log(`Get accessility resource error code:${code} message:${message}`);
        }
        return accessibilityResource;
    }
    getTextDirection() {
        if (this.counterDirection === Direction.Auto) {
            return i18n.isRTL(i18n.getSystemLanguage()) ? Direction.Rtl : Direction.Ltr;
        }
        else {
            return this.counterDirection;
        }
    }
    getIncreaseStr() {
        return this.getUIContext().getHostContext()?.resourceManager?.getStringSync(125834852) ?? '';
    }
    getReduceStr() {
        return this.getUIContext().getHostContext()?.resourceManager?.getStringSync(125834853) ?? '';
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.type === CounterV2Type.LIST) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        RelativeContainer.create();
                        RelativeContainer.direction(this.counterDirection);
                        RelativeContainer.width('100%');
                        RelativeContainer.height(CounterResource.COUNTER_LIST_HEIGHT);
                    }, RelativeContainer);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.numberStyleOptions.label);
                        Text.direction(this.getTextDirection());
                        Text.fontSize(CounterResource.COUNTER_LIST_LABEL_SIZE);
                        Text.maxFontScale(CounterResource.COUNTER_LABEL_MAX_FONT_SIZE_SCALE);
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.direction(this.counterDirection);
                        Stack.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                        Stack.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                        Stack.borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS);
                        Stack.borderWidth(this.subBtnFocusWidth);
                        Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(CounterResource.BUTTON_SUB_ICON);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
                        Image.height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.subOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect });
                        Button.accessibilityText({ "id": -1, "type": 10003, params: ['sys.string.reduce_used_for_accessibility_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.accessibilityDescription(this.value === this.min ? '' : this.getReduceStr());
                        Button.accessibilityFocusDrawLevel(FocusDrawLevel.TOP);
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
                        Button.onKeyEvent((event) => {
                            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusButton();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                event.stopPropagation();
                                this.homeFirstValue();
                                this.focusWithTarget('ListAddButton' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                event.stopPropagation();
                                if (this.addBtnStateEffect) {
                                    this.addBtnStateEffect = false;
                                    this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                                    this.addBtnEnabled = false;
                                }
                                this.endLastValue();
                                this.focusWithTarget('ListAddButton' + this.timeStamp.toString());
                            }
                        });
                        Button.onClick((event) => {
                            this.subValue();
                            this.onChange?.(this.value);
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                            try {
                                let eventInfo = ({
                                    type: 'announceForAccessibility',
                                    bundleName: this.getUIContext()
                                        .getHostContext()?.abilityInfo?.bundleName,
                                    triggerAction: 'click',
                                    textAnnouncedForAccessibility: this.value?.toString()
                                });
                                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                    console.log('Accessility subValue click send event');
                                });
                            }
                            catch (exception) {
                                let code = exception.code;
                                let message = exception.message;
                                console.log(`Accessility subValue faild error code:${code} message:${message}`);
                            }
                        });
                        globalThis.Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.subValue();
                                this.onChange?.(this.value);
                            }
                            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        });
                        LongPressGesture.onActionEnd(() => {
                            try {
                                let eventInfo = ({
                                    type: 'announceForAccessibility',
                                    bundleName: this.getUIContext()
                                        .getHostContext()?.abilityInfo?.bundleName,
                                    triggerAction: 'common',
                                    textAnnouncedForAccessibility: this.value?.toString()
                                });
                                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                    console.log('Accessility subValue longPress send event');
                                });
                            }
                            catch (exception) {
                                let code = exception.code;
                                let message = exception.message;
                                console.log(`Accessility subValue longPress faild error code:${code} message:${message}`);
                            }
                        });
                        LongPressGesture.pop();
                        globalThis.Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverDecrease && this.onHoverDecrease(isHover);
                        });
                        Button.focusable(this.focusEnable);
                        Button.onFocus(() => {
                            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusDecrease && this.onFocusDecrease();
                            this.updateButtonStatus();
                        });
                        Button.onBlur(() => {
                            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurDecrease && this.onBlurDecrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.hasTextWidth) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.value.toString());
                                    Text.accessibilityText(this.getAccessibilityResource(this.numberStyleOptions.label) + '[n2]' +
                                        this.value.toString() + '[n0]');
                                    Text.direction(this.counterDirection);
                                    Text.width(this.textWidth.toString());
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE);
                                    Text.maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE);
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
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.value.toString());
                                    Text.accessibilityText(this.getAccessibilityResource(this.numberStyleOptions.label) + '[n2]' +
                                        this.value.toString() + '[n0]');
                                    Text.direction(this.counterDirection);
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE);
                                    Text.maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE);
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.direction(this.counterDirection);
                        Stack.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                        Stack.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
                        Stack.borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS);
                        Stack.borderWidth(this.addBtnFocusWidth);
                        Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(CounterResource.BUTTON_ADD_ICON);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
                        Image.height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.addOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect });
                        Button.accessibilityText({ "id": -1, "type": 10003, params: ['sys.string.increase_used_for_accessibility_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.accessibilityDescription(this.value === this.max ? '' : this.getIncreaseStr());
                        Button.accessibilityFocusDrawLevel(FocusDrawLevel.TOP);
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
                        Button.onKeyEvent((event) => {
                            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusButton();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                event.stopPropagation();
                                this.homeFirstValue();
                                if (this.subBtnStateEffect) {
                                    this.subBtnStateEffect = false;
                                    this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                                    this.subBtnEnabled = false;
                                }
                                this.focusWithTarget('ListAddButton' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                event.stopPropagation();
                                this.endLastValue();
                                this.focusWithTarget('ListSubButton' + this.timeStamp.toString());
                            }
                        });
                        Button.onClick((event) => {
                            this.addValue();
                            this.onChange?.(this.value);
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                            try {
                                let eventInfo = ({
                                    type: 'announceForAccessibility',
                                    bundleName: this.getUIContext()
                                        .getHostContext()?.abilityInfo?.bundleName,
                                    triggerAction: 'click',
                                    textAnnouncedForAccessibility: this.value?.toString()
                                });
                                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                    console.log('Accessility addValue click send event');
                                });
                            }
                            catch (exception) {
                                let code = exception.code;
                                let message = exception.message;
                                console.log(`Accessility addValue click longPress faild error code:${code} message:${message}`);
                            }
                        });
                        globalThis.Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.addValue();
                                this.onChange?.(this.value);
                            }
                            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        });
                        LongPressGesture.onActionEnd(() => {
                            try {
                                let eventInfo = ({
                                    type: 'announceForAccessibility',
                                    bundleName: this.getUIContext()
                                        .getHostContext()?.abilityInfo?.bundleName,
                                    triggerAction: 'common',
                                    textAnnouncedForAccessibility: this.value?.toString()
                                });
                                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                    console.log('Accessility addValue longPress send event');
                                });
                            }
                            catch (exception) {
                                let code = exception.code;
                                let message = exception.message;
                                console.log(`Accessility addValue longPress longPress faild error code:${code} message:${message}`);
                            }
                        });
                        LongPressGesture.pop();
                        globalThis.Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverIncrease && this.onHoverIncrease(isHover);
                        });
                        Button.focusable(this.focusEnable);
                        Button.onFocus(() => {
                            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusIncrease && this.onFocusIncrease();
                            this.updateButtonStatus();
                        });
                        Button.onBlur(() => {
                            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurIncrease && this.onBlurIncrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    Row.pop();
                    RelativeContainer.pop();
                });
            }
            else if (this.type === CounterV2Type.COMPACT) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.direction(this.counterDirection);
                        Row.tabIndex(0);
                        Row.height(CounterResource.COUNTER_COMPACT_CONTAINER_HEIGHT);
                        Row.align(Alignment.Center);
                        Row.borderWidth(CounterResource.COUNTER_BORDER_WIDTH);
                        Row.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                        Row.borderRadius(CounterResource.COUNTER_COMPACT_CONTAINER_RADIUS);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Stack.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Stack.borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS);
                        Stack.borderWidth(this.subBtnFocusWidth);
                        Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Stack.margin({
                            start: LengthMetrics.vp(this.resourceToVp(CounterResource.COUNTER_COMPACT_BUTTON_CONTAINER_MARGIN))
                        });
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(CounterResource.BUTTON_SUB_ICON);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
                        Image.height(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.subOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect });
                        Button.accessibilityText({ "id": -1, "type": 10003, params: ['sys.string.reduce_used_for_accessibility_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.accessibilityDescription(this.value === this.min ? '' : this.getReduceStr());
                        Button.accessibilityFocusDrawLevel(FocusDrawLevel.TOP);
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Button.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
                        Button.opacity(this.subOpacity);
                        Button.enabled(this.subBtnEnabled);
                        Button.key('CompactSubButton' + this.timeStamp.toString());
                        Button.onKeyEvent((event) => {
                            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusButton();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                event.stopPropagation();
                                this.homeFirstValue();
                                this.focusWithTarget('CompactAddButton' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                event.stopPropagation();
                                this.endLastValue();
                                if (this.addBtnStateEffect) {
                                    this.addBtnStateEffect = false;
                                    this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                                    this.addBtnEnabled = false;
                                }
                                this.focusWithTarget('CompactSubButton' + this.timeStamp.toString());
                            }
                        });
                        Button.onClick((event) => {
                            this.subValue();
                            this.onChange?.(this.value);
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                            try {
                                let eventInfo = ({
                                    type: 'announceForAccessibility',
                                    bundleName: this.getUIContext()
                                        .getHostContext()?.abilityInfo?.bundleName,
                                    triggerAction: 'click',
                                    textAnnouncedForAccessibility: this.value?.toString()
                                });
                                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                    console.log('Accessility subValue click send event');
                                });
                            }
                            catch (exception) {
                                let code = exception.code;
                                let message = exception.message;
                                console.log(`Accessility subValue click longPress faild error code:${code} message:${message}`);
                            }
                        });
                        globalThis.Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.subValue();
                                this.onChange?.(this.value);
                            }
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        LongPressGesture.onActionEnd(() => {
                            try {
                                let eventInfo = ({
                                    type: 'announceForAccessibility',
                                    bundleName: this.getUIContext()
                                        .getHostContext()?.abilityInfo?.bundleName,
                                    triggerAction: 'common',
                                    textAnnouncedForAccessibility: this.value?.toString()
                                });
                                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                    console.log('Accessility subValue longPress send event');
                                });
                            }
                            catch (exception) {
                                let code = exception.code;
                                let message = exception.message;
                                console.log(`Accessility subValue longPress longPress faild error code:${code} message:${message}`);
                            }
                        });
                        LongPressGesture.pop();
                        globalThis.Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverDecrease && this.onHoverDecrease(isHover);
                        });
                        Button.focusable(this.focusEnable);
                        Button.groupDefaultFocus(true);
                        Button.onFocus(() => {
                            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusDecrease && this.onFocusDecrease();
                            this.updateButtonStatus();
                        });
                        Button.onBlur(() => {
                            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurDecrease && this.onBlurDecrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.hasTextWidth) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.value.toString());
                                    Text.accessibilityText(this.getAccessibilityResource(this.numberStyleOptions.label) + '[n2]' +
                                        this.value.toString() + '[n0]');
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                                    Text.maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE);
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
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.value.toString());
                                    Text.accessibilityText(this.getAccessibilityResource(this.numberStyleOptions.label) + '[n2]' +
                                        this.value.toString() + '[n0]');
                                    Text.direction(this.counterDirection);
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                                    Text.maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE);
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.direction(this.counterDirection);
                        Stack.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Stack.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Stack.borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS);
                        Stack.borderWidth(this.addBtnFocusWidth);
                        Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Stack.margin({
                            end: LengthMetrics.vp(this.resourceToVp(CounterResource.COUNTER_COMPACT_BUTTON_CONTAINER_MARGIN))
                        });
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(CounterResource.BUTTON_ADD_ICON);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
                        Image.height(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.addOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect });
                        Button.accessibilityText({ "id": -1, "type": 10003, params: ['sys.string.increase_used_for_accessibility_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.accessibilityDescription(this.value === this.max ? '' : this.getIncreaseStr());
                        Button.accessibilityFocusDrawLevel(FocusDrawLevel.TOP);
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Button.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
                        Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
                        Button.opacity(this.addOpacity);
                        Button.enabled(this.addBtnEnabled);
                        Button.key('CompactAddButton' + this.timeStamp.toString());
                        Button.onKeyEvent((event) => {
                            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusButton();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                event.stopPropagation();
                                this.homeFirstValue();
                                if (this.subBtnStateEffect) {
                                    this.subBtnStateEffect = false;
                                    this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                                    this.subBtnEnabled = false;
                                }
                                this.focusWithTarget('CompactAddButton' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                event.stopPropagation();
                                this.endLastValue();
                                this.focusWithTarget('CompactSubButton' + this.timeStamp.toString());
                            }
                        });
                        Button.onClick((event) => {
                            this.addValue();
                            this.onChange?.(this.value);
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                            try {
                                let eventInfo = ({
                                    type: 'announceForAccessibility',
                                    bundleName: this.getUIContext()
                                        .getHostContext()?.abilityInfo?.bundleName,
                                    triggerAction: 'click',
                                    textAnnouncedForAccessibility: this.value?.toString()
                                });
                                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                    console.log('Accessility addValue click send event');
                                });
                            }
                            catch (exception) {
                                let code = exception.code;
                                let message = exception.message;
                                console.log(`Accessility addValue click longPress faild error code:${code} message:${message}`);
                            }
                        });
                        globalThis.Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.addValue();
                                this.onChange?.(this.value);
                            }
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        LongPressGesture.onActionEnd(() => {
                            try {
                                let eventInfo = ({
                                    type: 'announceForAccessibility',
                                    bundleName: this.getUIContext()
                                        .getHostContext()?.abilityInfo?.bundleName,
                                    triggerAction: 'common',
                                    textAnnouncedForAccessibility: this.value?.toString()
                                });
                                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                    console.log('Accessility addValue longPress send event');
                                });
                            }
                            catch (exception) {
                                let code = exception.code;
                                let message = exception.message;
                                console.log(`Accessility addValue longPress longPress faild error code:${code} message:${message}`);
                            }
                        });
                        LongPressGesture.pop();
                        globalThis.Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverIncrease && this.onHoverIncrease(isHover);
                        });
                        Button.focusable(this.focusEnable);
                        Button.onFocus(() => {
                            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusIncrease && this.onFocusIncrease();
                            this.updateButtonStatus();
                        });
                        Button.onBlur(() => {
                            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurIncrease && this.onBlurIncrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.numberStyleOptions.label);
                        Text.direction(this.counterDirection);
                        Text.margin({ top: CounterResource.COUNTER_COMPACT_CONTAINER_LABEL_DISTANCE });
                        Text.fontSize(CounterResource.COUNTER_COMPACT_LABEL_SIZE);
                        Text.maxFontScale(CounterResource.COUNTER_LABEL_MAX_FONT_SIZE_SCALE);
                        Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                        Text.align(Alignment.Top);
                    }, Text);
                    Text.pop();
                    Column.pop();
                });
            }
            else if (this.type === CounterV2Type.INLINE) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.direction(this.counterDirection);
                        Row.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                        Row.borderWidth(CounterResource.COUNTER_BORDER_WIDTH);
                        Row.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                        Row.borderRadius(CounterResource.COUNTER_INLINE_RADIUS);
                        Row.clip(true);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.hasTextWidth) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    RelativeContainer.create();
                                    RelativeContainer.direction(this.counterDirection);
                                    RelativeContainer.margin({
                                        start: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN),
                                        end: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN)
                                    });
                                    RelativeContainer.height('100%');
                                    RelativeContainer.width(this.textWidth);
                                }, RelativeContainer);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    TextInput.create({
                                        text: this.hasInputText1 ? this.inputValue : this.value.toString(),
                                        controller: this.controller1
                                    });
                                    TextInput.accessibilityDescription({ "id": -1, "type": 10003, params: ['sys.string.input_counter_double_click_description'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    TextInput.alignRules({
                                        center: { anchor: '__container__', align: VerticalAlign.Center },
                                        middle: { anchor: '__container__', align: HorizontalAlign.Center }
                                    });
                                    TextInput.width('100%');
                                    TextInput.height('20vp');
                                    TextInput.padding(0);
                                    TextInput.borderRadius(0);
                                    TextInput.textAlign(TextAlign.Center);
                                    TextInput.type(InputType.PhoneNumber);
                                    TextInput.copyOption(CopyOptions.None);
                                    TextInput.fontSize(this.getTextInputFontSize());
                                    TextInput.fontWeight(FontWeight.Medium);
                                    TextInput.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                                    TextInput.maxLength(this.getMaxLength());
                                    TextInput.backgroundColor(Color.Transparent);
                                    TextInput.key('InlineTextInput' + this.timeStamp.toString());
                                    TextInput.onKeyEvent((event) => {
                                        this.focusCurrentText(FocusText.TEXT1);
                                        if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                                            this.resetFocusText();
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                                            this.addValue();
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                            event.stopPropagation();
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                            event.stopPropagation();
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                                            this.subValue();
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                            event.stopPropagation();
                                        }
                                    });
                                    TextInput.onChange((value) => {
                                        this.inputValue = value;
                                        this.hasInputText1 = true;
                                        let c = value[value.length - 1];
                                        if (value.length === this.getMaxLength()) {
                                            this.inputValue = c;
                                        }
                                        this.updateInlineEnableState();
                                    });
                                    TextInput.onSubmit((enterKey) => {
                                        this.hasInputText1 = false;
                                        let submitNum = Number(this.inputValue);
                                        if (Number.isInteger(submitNum) && submitNum >= this.min && submitNum <= this.max) {
                                            this.value = submitNum;
                                            this.onChange?.(this.value);
                                        }
                                        else {
                                            this.inputValue = this.value.toString();
                                        }
                                        this.updateInlineEnableState();
                                    });
                                    TextInput.focusable(true);
                                    TextInput.focusOnTouch(true);
                                    TextInput.onFocus(() => {
                                        this.focusText = FocusText.TEXT1;
                                        this.hasFocusText1 = true;
                                        this.controller1.caretPosition(this.value.toString().length);
                                    });
                                    TextInput.onBlur(() => {
                                        if (this.hasInputText1) {
                                            let oldValue = this.value;
                                            this.validateInlineInput();
                                            if (this.value !== oldValue) {
                                                this.onChange?.(this.value);
                                            }
                                        }
                                        this.focusText = FocusText.NONE;
                                        this.hasFocusText1 = false;
                                    });
                                    TextInput.onClick((event) => {
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
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.direction(this.counterDirection);
                                    Row.margin({
                                        start: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN),
                                        end: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN)
                                    });
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    TextInput.create({
                                        text: this.hasInputText1 ? this.inputValue : this.value.toString(),
                                        controller: this.controller1
                                    });
                                    TextInput.accessibilityDescription({ "id": -1, "type": 10003, params: ['sys.string.input_counter_double_click_description'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    TextInput.direction(this.counterDirection);
                                    TextInput.width(this.getMeasuredTextWidth(this.getValue()));
                                    TextInput.height('20vp');
                                    TextInput.padding(0);
                                    TextInput.borderRadius(0);
                                    TextInput.textAlign(TextAlign.Center);
                                    TextInput.type(InputType.PhoneNumber);
                                    TextInput.copyOption(CopyOptions.None);
                                    TextInput.fontSize(this.getTextInputFontSize());
                                    TextInput.fontWeight(FontWeight.Medium);
                                    TextInput.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                                    TextInput.maxLength(this.getMaxLength());
                                    TextInput.backgroundColor(Color.Transparent);
                                    TextInput.key('InlineTextInput' + this.timeStamp.toString());
                                    TextInput.onKeyEvent((event) => {
                                        this.focusCurrentText(FocusText.TEXT1);
                                        if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                                            this.resetFocusText();
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                                            this.addValue();
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                                            this.subValue();
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                            event.stopPropagation();
                                        }
                                    });
                                    TextInput.onChange((value) => {
                                        this.inputValue = value;
                                        this.hasInputText1 = true;
                                        let c = value[value.length - 1];
                                        if (value.length === this.getMaxLength()) {
                                            this.inputValue = c;
                                        }
                                        this.updateInlineEnableState();
                                    });
                                    TextInput.onSubmit((enterKey) => {
                                        this.hasInputText1 = false;
                                        let submitNum = Number(this.inputValue);
                                        if (Number.isInteger(submitNum) && submitNum >= this.min && submitNum <= this.max) {
                                            this.value = submitNum;
                                            this.onChange?.(this.value);
                                        }
                                        else {
                                            this.inputValue = this.value.toString();
                                        }
                                        this.updateInlineEnableState();
                                    });
                                    TextInput.focusable(true);
                                    TextInput.focusOnTouch(true);
                                    TextInput.onFocus(() => {
                                        this.focusText = FocusText.TEXT1;
                                        this.hasFocusText1 = true;
                                        this.controller1.caretPosition(this.value.toString().length);
                                    });
                                    TextInput.onBlur(() => {
                                        if (this.hasInputText1) {
                                            let oldValue = this.value;
                                            this.validateInlineInput();
                                            if (this.value !== oldValue) {
                                                this.onChange?.(this.value);
                                            }
                                        }
                                        this.focusText = FocusText.NONE;
                                        this.hasFocusText1 = false;
                                    });
                                    TextInput.onClick((event) => {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.direction(this.counterDirection);
                        Column.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Column.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                        Column.borderWidth({ start: LengthMetrics.vp(CounterResource.COUNTER_BORDER_WIDTH_NUMBER) });
                        Column.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.direction(this.counterDirection);
                        Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Stack.padding({ top: '1vp' });
                        Stack.borderWidth({ bottom: '1vp' });
                        Stack.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        Rect.strokeWidth(this.addBtnFocusWidth);
                        Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Rect.margin({ end: LengthMetrics.vp(2) });
                        Rect.fillOpacity(0);
                    }, Rect);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(CounterResource.BUTTON_ARROW_UP);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
                        Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.addOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect });
                        Button.accessibilityText({ "id": -1, "type": 10003, params: ['sys.string.increase_used_for_accessibility_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.accessibilityDescription(this.value === this.max ? '' : this.getIncreaseStr());
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Button.backgroundColor(Color.Transparent);
                        Button.opacity(this.addOpacity);
                        Button.enabled(this.addBtnEnabled);
                        Button.onClick((event) => {
                            this.addValue();
                            this.onChange?.(this.value);
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                            try {
                                let eventInfo = ({
                                    type: 'announceForAccessibility',
                                    bundleName: this.getUIContext()
                                        .getHostContext()?.abilityInfo?.bundleName,
                                    triggerAction: 'click',
                                    textAnnouncedForAccessibility: this.value?.toString()
                                });
                                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                    console.log('Accessility addValue click send event');
                                });
                            }
                            catch (exception) {
                                let code = exception.code;
                                let message = exception.message;
                                console.log(`Accessility addValue click longPress faild error code:${code} message:${message}`);
                            }
                        });
                        globalThis.Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.addValue();
                            }
                            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        });
                        LongPressGesture.onActionEnd(() => {
                            try {
                                let eventInfo = ({
                                    type: 'announceForAccessibility',
                                    bundleName: this.getUIContext()
                                        .getHostContext()?.abilityInfo?.bundleName,
                                    triggerAction: 'common',
                                    textAnnouncedForAccessibility: this.value?.toString()
                                });
                                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                    console.log('Accessility addValue longPress send event');
                                });
                            }
                            catch (exception) {
                                let code = exception.code;
                                let message = exception.message;
                                console.log(`Accessility addValue longPress faild error code:${code} message:${message}`);
                            }
                        });
                        LongPressGesture.pop();
                        globalThis.Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverIncrease && this.onHoverIncrease(isHover);
                        });
                        Button.focusable(false);
                        Button.onFocus(() => {
                            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusIncrease && this.onFocusIncrease();
                        });
                        Button.onBlur(() => {
                            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurIncrease && this.onBlurIncrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.direction(this.counterDirection);
                        Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        Rect.strokeWidth(this.subBtnFocusWidth);
                        Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Rect.margin({ top: LengthMetrics.vp(1), end: LengthMetrics.vp(1), bottom: LengthMetrics.vp(2) });
                        Rect.fillOpacity(0);
                    }, Rect);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(CounterResource.BUTTON_ARROW_DOWN);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
                        Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.subOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect });
                        Button.accessibilityText({ "id": -1, "type": 10003, params: ['sys.string.reduce_used_for_accessibility_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.accessibilityDescription(this.value === this.min ? '' : this.getReduceStr());
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Button.backgroundColor(Color.Transparent);
                        Button.opacity(this.subOpacity);
                        Button.enabled(this.subBtnEnabled);
                        Button.onClick((event) => {
                            this.subValue();
                            this.onChange?.(this.value);
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                            try {
                                let eventInfo = ({
                                    type: 'announceForAccessibility',
                                    bundleName: this.getUIContext()
                                        .getHostContext()?.abilityInfo?.bundleName,
                                    triggerAction: 'click',
                                    textAnnouncedForAccessibility: this.value?.toString()
                                });
                                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                    console.log('Accessility subValue click send event');
                                });
                            }
                            catch (exception) {
                                let code = exception.code;
                                let message = exception.message;
                                console.log(`Accessility subValue click faild error code:${code} message:${message}`);
                            }
                        });
                        globalThis.Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.subValue();
                            }
                            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        });
                        LongPressGesture.onActionEnd(() => {
                            try {
                                let eventInfo = ({
                                    type: 'announceForAccessibility',
                                    bundleName: this.getUIContext()
                                        .getHostContext()?.abilityInfo?.bundleName,
                                    triggerAction: 'common',
                                    textAnnouncedForAccessibility: this.value?.toString()
                                });
                                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                                    console.log('Accessility subValue longPress send event');
                                });
                            }
                            catch (exception) {
                                let code = exception.code;
                                let message = exception.message;
                                console.log(`Accessility subValue longPress faild error code:${code} message:${message}`);
                            }
                        });
                        LongPressGesture.pop();
                        globalThis.Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverDecrease && this.onHoverDecrease(isHover);
                        });
                        Button.focusable(false);
                        Button.onFocus(() => {
                            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusDecrease && this.onFocusDecrease();
                        });
                        Button.onBlur(() => {
                            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurDecrease && this.onBlurDecrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    Column.pop();
                    Row.pop();
                });
            }
            else if (this.type === CounterV2Type.INLINE_DATE) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.direction(this.counterDirection);
                        Row.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                        Row.borderWidth(CounterResource.COUNTER_BORDER_WIDTH);
                        Row.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                        Row.borderRadius(CounterResource.COUNTER_INLINE_RADIUS);
                        Row.clip(true);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.direction(this.counterDirection);
                        Row.width('92vp');
                        Row.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                        Row.margin({
                            start: LengthMetrics.vp(CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN),
                            end: LengthMetrics.vp(CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN)
                        });
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        TextInput.create({
                            text: this.hasInputText1 ? this.inputYear.toString() : this.getYear(),
                            controller: this.controller1
                        });
                        TextInput.accessibilityText(this.getDateYear(this.year));
                        TextInput.accessibilityDescription({ "id": -1, "type": 10003, params: ['sys.string.input_counter_double_click_description'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        TextInput.direction(this.counterDirection);
                        TextInput.type(InputType.Number);
                        TextInput.copyOption(CopyOptions.None);
                        TextInput.fontSize(this.getTextInputFontSize());
                        TextInput.fontWeight(FontWeight.Medium);
                        TextInput.fontColor(this.hasFocusText1 ? Color.White : CounterResource.COUNTER_TEXT_COLOR);
                        TextInput.maxLength(5);
                        TextInput.padding(0);
                        TextInput.backgroundColor(this.hasFocusText1 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent);
                        TextInput.width(this.yearTextWidth);
                        TextInput.height('20vp');
                        TextInput.borderRadius(0);
                        TextInput.borderWidth(0);
                        TextInput.key('DateTextInput1' + this.timeStamp.toString());
                        TextInput.onKeyEvent((event) => {
                            this.focusCurrentText(FocusText.TEXT1);
                            if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                                this.addDate();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                                this.subDate();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                this.homeFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                this.endFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                                this.focusWithTarget('DateTextInput2' + this.timeStamp.toString());
                            }
                        });
                        TextInput.onChange((value) => {
                            if (value.length !== 4) {
                                this.hasInputText1 = true;
                            }
                            this.inputYear = Number(value);
                            if (value.length === 5) {
                                this.inputYear = this.inputYear % 10;
                            }
                            if (this.timeoutID1 !== -1) {
                                clearTimeout(this.timeoutID1);
                                this.timeoutID1 = -1;
                            }
                            this.timeoutID1 = setTimeout(() => {
                                this.hasInputText1 = false;
                                this.inputYear = this.year;
                                this.updateDateEnableState();
                                this.updateDay();
                            }, 1500);
                            if (this.inputYear >= this.minYear && this.inputYear <= this.maxYear) {
                                this.year = this.inputYear;
                                this.updateDateEnableState();
                                this.updateDay();
                            }
                            if (value.length === 4) {
                                let date = new CounterV2DateData(this.year, this.month, this.day);
                                this.onDateChange?.(date);
                            }
                        });
                        TextInput.onSubmit((enterKey) => {
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
                            this.updateDateEnableState();
                            this.updateDay();
                        });
                        TextInput.tabIndex(0);
                        TextInput.focusOnTouch(true);
                        TextInput.focusable(true);
                        TextInput.onFocus(() => {
                            this.focusText = FocusText.TEXT1;
                            this.hasFocusText1 = true;
                            this.updateDateEnableState();
                            this.controller1.caretPosition(this.getYear().length);
                        });
                        TextInput.onBlur(() => {
                            this.focusText = FocusText.NONE;
                            this.hasFocusText1 = false;
                            this.updateDateEnableState();
                        });
                        TextInput.onClick((event) => {
                            this.focusText = FocusText.TEXT1;
                            this.hasFocusText1 = true;
                            this.updateDateEnableState();
                            this.controller1.caretPosition(this.getYear().length);
                        });
                    }, TextInput);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create('/');
                        Text.accessibilityLevel('no');
                        Text.direction(this.counterDirection);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                        Text.maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE);
                        Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                        Text.width('8vp');
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        TextInput.create({
                            text: this.hasInputText2 ? this.inputMoon.toString() : this.convertNumberToString(this.month),
                            controller: this.controller2
                        });
                        TextInput.accessibilityText(this.getDateMonth(this.month));
                        TextInput.accessibilityDescription({ "id": -1, "type": 10003, params: ['sys.string.input_counter_double_click_description'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        TextInput.direction(this.counterDirection);
                        TextInput.type(InputType.Number);
                        TextInput.copyOption(CopyOptions.None);
                        TextInput.fontSize(this.getTextInputFontSize());
                        TextInput.fontWeight(FontWeight.Medium);
                        TextInput.fontColor(this.hasFocusText2 ? Color.White : CounterResource.COUNTER_TEXT_COLOR);
                        TextInput.maxLength(3);
                        TextInput.padding(0);
                        TextInput.backgroundColor(this.hasFocusText2 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent);
                        TextInput.width(this.monthDayTextWidth);
                        TextInput.height('20vp');
                        TextInput.borderRadius(0);
                        TextInput.key('DateTextInput2' + this.timeStamp.toString());
                        TextInput.onKeyEvent((event) => {
                            this.focusCurrentText(FocusText.TEXT2);
                            if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                                this.subDate();
                                this.updateDay();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                                this.addDate();
                                this.updateDay();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                this.homeFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                this.endFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                                this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_TAB) {
                                event.stopPropagation();
                                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
                            }
                        });
                        TextInput.onChange((value) => {
                            this.inputMoon = Number(value);
                            if (value.length !== 2) {
                                this.hasInputText2 = true;
                            }
                            if (value.length === 3) {
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
                            if (value.length === 2) {
                                this.hasInputText2 = false;
                                this.month -= 1;
                                if (this.inputMoon >= 1 && this.inputMoon <= 12) {
                                    this.month = this.inputMoon;
                                    let date = new CounterV2DateData(this.year, this.month, this.day);
                                    this.onDateChange?.(date);
                                }
                                else {
                                    this.month += 1;
                                    this.inputMoon = this.month;
                                }
                                this.updateDay();
                            }
                        });
                        TextInput.onSubmit((enterKey) => {
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
                        TextInput.onClick((event) => {
                            this.focusText = FocusText.TEXT2;
                            this.hasFocusText2 = true;
                            this.controller2.caretPosition(this.convertNumberToString(this.month).length);
                        });
                    }, TextInput);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create('/');
                        Text.accessibilityLevel('no');
                        Text.direction(this.counterDirection);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                        Text.maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE);
                        Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                        Text.width('8vp');
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        TextInput.create({
                            text: this.hasInputText3 ? this.inputDay.toString() : this.convertNumberToString(this.day),
                            controller: this.controller3
                        });
                        TextInput.accessibilityText(this.getDateDay(this.day));
                        TextInput.accessibilityDescription({ "id": -1, "type": 10003, params: ['sys.string.input_counter_double_click_description'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        TextInput.direction(this.counterDirection);
                        TextInput.type(InputType.Number);
                        TextInput.copyOption(CopyOptions.None);
                        TextInput.fontSize(this.getTextInputFontSize());
                        TextInput.fontWeight(FontWeight.Medium);
                        TextInput.fontColor(this.hasFocusText3 ? Color.White : CounterResource.COUNTER_TEXT_COLOR);
                        TextInput.maxLength(3);
                        TextInput.padding(0);
                        TextInput.backgroundColor(this.hasFocusText3 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent);
                        TextInput.width(this.monthDayTextWidth);
                        TextInput.height('20vp');
                        TextInput.borderRadius(0);
                        TextInput.key('DateTextInput3' + this.timeStamp.toString());
                        TextInput.onKeyEvent((event) => {
                            this.focusCurrentText(FocusText.TEXT3);
                            if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                                this.resetFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                                this.subDate();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                                this.addDate();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                                this.homeFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                                this.endFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                                this.focusWithTarget('DateTextInput2' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                                this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === CounterConstant.KEYCODE_TAB) {
                                event.stopPropagation();
                                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
                            }
                        });
                        TextInput.onChange((value) => {
                            this.inputDay = Number(value);
                            if (value.length !== 2) {
                                this.hasInputText3 = true;
                            }
                            if (value.length === 3) {
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
                            if (value.length === 2) {
                                this.hasInputText3 = false;
                                this.day -= 1;
                                if (this.inputDay >= 1 && this.inputDay <= this.getDayNumber()) {
                                    this.day = this.inputDay;
                                    let date = new CounterV2DateData(this.year, this.month, this.day);
                                    this.onDateChange?.(date);
                                }
                                else {
                                    this.day += 1;
                                    this.inputDay = this.day;
                                }
                            }
                        });
                        TextInput.onSubmit((enterKey) => {
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
                        TextInput.onClick((event) => {
                            this.focusText = FocusText.TEXT3;
                            this.hasFocusText3 = true;
                            this.controller3.caretPosition(this.convertNumberToString(this.day).length);
                        });
                    }, TextInput);
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.direction(this.counterDirection);
                        Column.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Column.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
                        Column.borderWidth({ start: LengthMetrics.vp(CounterResource.COUNTER_BORDER_WIDTH_NUMBER) });
                        Column.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Stack.padding({ top: '1vp' });
                        Stack.borderWidth({ bottom: '1vp' });
                        Stack.borderColor(CounterResource.COUNTER_BORDER_COLOR);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        Rect.strokeWidth(this.addBtnFocusWidth);
                        Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Rect.margin({ end: LengthMetrics.vp(1) });
                        Rect.fillOpacity(0);
                    }, Rect);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(CounterResource.BUTTON_ARROW_UP);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
                        Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.addOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect });
                        Button.accessibilityText({ "id": -1, "type": 10003, params: ['sys.string.increase_used_for_accessibility_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.accessibilityDescription({ "id": -1, "type": 10003, params: ['sys.string.increase_counter_double_click_description'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Button.backgroundColor(Color.Transparent);
                        Button.opacity(this.addOpacity);
                        Button.enabled(this.addBtnEnabled);
                        Button.onClick((event) => {
                            this.accessibilityBroadcastAddDate();
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        globalThis.Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.addDate();
                            }
                            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        });
                        LongPressGesture.onActionEnd(() => {
                            this.accessibilityBroadcastAddDate();
                        });
                        LongPressGesture.pop();
                        globalThis.Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverIncrease && this.onHoverIncrease(isHover);
                        });
                        Button.focusable(false);
                        Button.onFocus(() => {
                            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusIncrease && this.onFocusIncrease();
                        });
                        Button.onBlur(() => {
                            this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            this.onBlurIncrease && this.onBlurIncrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        Rect.strokeWidth(this.subBtnFocusWidth);
                        Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
                        Rect.margin({ top: LengthMetrics.vp(1), end: LengthMetrics.vp(1), bottom: LengthMetrics.vp(2) });
                        Rect.fillOpacity(0);
                    }, Rect);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(CounterResource.BUTTON_ARROW_DOWN);
                        Image.direction(this.counterDirection);
                        Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
                        Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
                        Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
                        Image.opacity(this.subOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect });
                        Button.accessibilityText({ "id": -1, "type": 10003, params: ['sys.string.reduce_used_for_accessibility_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.accessibilityDescription({ "id": -1, "type": 10003, params: ['sys.string.reduce_counter_double_click_description'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.direction(this.counterDirection);
                        Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
                        Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
                        Button.backgroundColor(Color.Transparent);
                        Button.opacity(this.subOpacity);
                        Button.enabled(this.subBtnEnabled);
                        Button.onClick((event) => {
                            this.accessibilityBroadcastSubDate();
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                            }
                        });
                        globalThis.Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.subDate();
                            }
                            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                        });
                        LongPressGesture.onActionEnd(() => {
                            this.accessibilityBroadcastSubDate();
                        });
                        LongPressGesture.pop();
                        globalThis.Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverDecrease && this.onHoverDecrease(isHover);
                        });
                        Button.focusable(false);
                        Button.onFocus(() => {
                            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                            this.onFocusDecrease && this.onFocusDecrease();
                        });
                        Button.onBlur(() => {
                            this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
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
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("options" in params) {
            this.updateParam("options", params.options);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], CounterV2Component.prototype, "options", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "type", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "counterDirection", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "choverEffect", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "focusEnable", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "step", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "inputValue", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "inputYear", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "inputMoon", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "inputDay", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "subOpacity", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "addOpacity", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "subBtnStateEffect", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "addBtnStateEffect", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "focusText", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "hasFocusText1", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "hasFocusText2", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "hasFocusText3", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "subBtnFocusWidth", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "addBtnFocusWidth", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "value", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "year", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "month", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "day", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "hour", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "minute", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "second", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "subBtnEnabled", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "addBtnEnabled", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "hasInputText1", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "hasInputText2", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "hasInputText3", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "textWidth", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "min", void 0);
__decorate([
    Local
], CounterV2Component.prototype, "max", void 0);
__decorate([
    Monitor('options', 'options.type', 'options.direction', 'options.numberOptions', 'options.inlineOptions', 'options.dateOptions')
], CounterV2Component.prototype, "onOptionsChange", null);

export default {
    CounterV2CommonOptions,
    CounterV2NumberStyleOptions,
    CounterV2InlineStyleOptions,
    CounterV2DateStyleOptions,
    CounterV2Type,
    CounterV2DateData,
    CounterV2Options,
    CounterV2Component,
};
