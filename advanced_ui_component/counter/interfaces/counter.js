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

const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const accessibility = requireNapi('accessibility');
const intl = requireNapi('intl');

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {});
}

export var CounterType;
(function (b14) {
  b14[(b14['LIST'] = 0)] = 'LIST';
  b14[(b14['COMPACT'] = 1)] = 'COMPACT';
  b14[(b14['INLINE'] = 2)] = 'INLINE';
  b14[(b14['INLINE_DATE'] = 3)] = 'INLINE_DATE';
})(CounterType || (CounterType = {}));
var FocusText;
(function (a14) {
  a14[(a14['NONE'] = 0)] = 'NONE';
  a14[(a14['TEXT1'] = 1)] = 'TEXT1';
  a14[(a14['TEXT2'] = 2)] = 'TEXT2';
  a14[(a14['TEXT3'] = 3)] = 'TEXT3';
})(FocusText || (FocusText = {}));
export class CommonOptions {}
export class InlineStyleOptions extends CommonOptions {}
export class NumberStyleOptions extends InlineStyleOptions {}
export class DateData {
  constructor(x13, y13, z13) {
    this.year = x13;
    this.month = y13;
    this.day = z13;
  }
  toString() {
    let u13 = this.year.toString() + '-';
    let v13 =
      this.month < 10 ? '0' + this.month.toString() : this.month.toString();
    u13 += v13 + '-';
    let w13 = this.day < 10 ? '0' + this.day.toString() : this.day.toString();
    u13 += w13;
    return u13;
  }
}
export class DateStyleOptions extends CommonOptions {}
export class CounterOptions {
  constructor() {
    this.type = CounterType.LIST;
  }
}
class CounterResource {}
CounterResource.BUTTON_BACKGROUD_COLOR = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_button_normal'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.BUTTON_ICON_COLOR = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_primary'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.BUTTON_BORDER_FOCUSED_COLOR = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_focused_outline'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.COUNTER_TEXT_COLOR = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_text_primary'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.COUNTER_BORDER_COLOR = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_component_normal'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.BUTTON_ADD_ICON = {
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_add'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.BUTTON_SUB_ICON = {
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_minus'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.BUTTON_ARROW_UP = {
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_arrow_up'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.BUTTON_ARROW_DOWN = {
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_arrow_down'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.BUTTON_BORDER_FOCUSED_WIDTH = '2vp';
CounterResource.BUTTON_BORDER_BLUR_WIDTH = '0vp';
CounterResource.COUNTER_BORDER_WIDTH_NUMBER = 1;
CounterResource.COUNTER_LIST_LABEL_SIZE = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_text_size_body1'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.COUNTER_LIST_NUMBER_SIZE = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_text_size_body1'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.COUNTER_COMPACT_LABEL_SIZE = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_text_size_body2'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.COUNTER_NUMBER_SIZE = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_text_size_body1'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.COUNTER_LIST_LEFT_PADDING = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_default_padding_start'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.COUNTER_LIST_RIGHT_PADDING = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_default_padding_end'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE = {
  id: -1,
  type: 10002,
  params: ['sys.float.button_icon_size'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.COUNTER_COMPACT_CONTAINER_HEIGHT = {
  id: -1,
  type: 10002,
  params: ['sys.float.container_height'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.COUNTER_BORDER_WIDTH = {
  id: -1,
  type: 10002,
  params: ['sys.float.border_width'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.COUNTER_COMPACT_BUTTON_SIZE = {
  id: -1,
  type: 10002,
  params: ['sys.float.button_size'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.COUNTER_COMPACT_CONTAINER_RADIUS = {
  id: -1,
  type: 10002,
  params: ['sys.float.container_radius'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
CounterResource.COUNTER_COMPACT_BUTTON_CONTAINER_MARGIN = {
  id: -1,
  type: 10002,
  params: ['sys.float.button_container_margin'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
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
class CounterConstant {}
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
  constructor(o13, p13, q13, r13 = -1, s13 = undefined, t13) {
    super(o13, q13, r13, t13);
    if (typeof s13 === 'function') {
      this.paramsGenerator_ = s13;
    }
    this.__options = new SynchedPropertyObjectOneWayPU(
      p13.options,
      this,
      'options'
    );
    this.__type = new ObservedPropertySimplePU(-1, this, 'type');
    this.__counterDirection = new ObservedPropertySimplePU(
      Direction.Auto,
      this,
      'counterDirection'
    );
    this.__choverEffect = new ObservedPropertySimplePU(
      HoverEffect.Auto,
      this,
      'choverEffect'
    );
    this.__focusEnable = new ObservedPropertySimplePU(
      true,
      this,
      'focusEnable'
    );
    this.__step = new ObservedPropertySimplePU(
      CounterConstant.COUNTER_INITIAL_STEP,
      this,
      'step'
    );
    this.__inputValue = new ObservedPropertySimplePU('0', this, 'inputValue');
    this.__inputYear = new ObservedPropertySimplePU(
      CounterConstant.COUNTER_MIN_YEAR,
      this,
      'inputYear'
    );
    this.__inputMoon = new ObservedPropertySimplePU(0, this, 'inputMoon');
    this.__inputDay = new ObservedPropertySimplePU(0, this, 'inputDay');
    this.__inputHour = new ObservedPropertySimplePU(0, this, 'inputHour');
    this.__inputMinute = new ObservedPropertySimplePU(0, this, 'inputMinute');
    this.__inputSecond = new ObservedPropertySimplePU(0, this, 'inputSecond');
    this.__subOpacity = new ObservedPropertySimplePU(
      CounterResource.COUNTER_BUTTON_INITIAL_OPACITY,
      this,
      'subOpacity'
    );
    this.__addOpacity = new ObservedPropertySimplePU(
      CounterResource.COUNTER_BUTTON_INITIAL_OPACITY,
      this,
      'addOpacity'
    );
    this.__subBtnStateEffect = new ObservedPropertySimplePU(
      true,
      this,
      'subBtnStateEffect'
    );
    this.__addBtnStateEffect = new ObservedPropertySimplePU(
      true,
      this,
      'addBtnStateEffect'
    );
    this.__focusText = new ObservedPropertySimplePU(
      FocusText.NONE,
      this,
      'focusText'
    );
    this.__hasFocusText1 = new ObservedPropertySimplePU(
      false,
      this,
      'hasFocusText1'
    );
    this.__hasFocusText2 = new ObservedPropertySimplePU(
      false,
      this,
      'hasFocusText2'
    );
    this.__hasFocusText3 = new ObservedPropertySimplePU(
      false,
      this,
      'hasFocusText3'
    );
    this.__subBtnFocusWidh = new ObservedPropertySimplePU(
      '0vp',
      this,
      'subBtnFocusWidh'
    );
    this.__addBtnFocusWidh = new ObservedPropertySimplePU(
      '0vp',
      this,
      'addBtnFocusWidh'
    );
    this.__value = new ObservedPropertySimplePU(0, this, 'value');
    this.__year = new ObservedPropertySimplePU(0, this, 'year');
    this.__month = new ObservedPropertySimplePU(0, this, 'month');
    this.__day = new ObservedPropertySimplePU(0, this, 'day');
    this.__hour = new ObservedPropertySimplePU(0, this, 'hour');
    this.__minute = new ObservedPropertySimplePU(0, this, 'minute');
    this.__second = new ObservedPropertySimplePU(0, this, 'second');
    this.__subBtnEnabled = new ObservedPropertySimplePU(
      true,
      this,
      'subBtnEnabled'
    );
    this.__addBtnEnabled = new ObservedPropertySimplePU(
      true,
      this,
      'addBtnEnabled'
    );
    this.__hasInputText1 = new ObservedPropertySimplePU(
      false,
      this,
      'hasInputText1'
    );
    this.__hasInputText2 = new ObservedPropertySimplePU(
      false,
      this,
      'hasInputText2'
    );
    this.__hasInputText3 = new ObservedPropertySimplePU(
      false,
      this,
      'hasInputText3'
    );
    this.__textWidth = new ObservedPropertySimplePU(0, this, 'textWidth');
    this.__min = new ObservedPropertySimplePU(
      CounterConstant.COUNTER_MIN_VALUE,
      this,
      'min'
    );
    this.__max = new ObservedPropertySimplePU(
      CounterConstant.COUNTER_MAX_VALUE,
      this,
      'max'
    );
    this.maxYear = CounterConstant.COUNTER_MAX_YEAR;
    this.minYear = CounterConstant.COUNTER_MIN_YEAR;
    this.numberStrList = [
      '00',
      '01',
      '02',
      '03',
      '04',
      '05',
      '06',
      '07',
      '08',
      '09',
    ];
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
    this.numberStyleOptions = new NumberStyleOptions();
    this.dateStyleOptions = new DateStyleOptions();
    this.inlineStyleOptions = new InlineStyleOptions();
    this.timeStamp = 0;
    this.hasTextWidth = false;
    this.controller1 = new TextInputController();
    this.controller2 = new TextInputController();
    this.controller3 = new TextInputController();
    this.initFlag = true;
    this.increaseStr = getContext().resourceManager.getStringSync(125834852);
    this.reduceStr = getContext().resourceManager.getStringSync(125834853);
    this.setInitiallyProvidedValue(p13);
    this.declareWatch('options', this.onOptionsChange);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(n13) {
    if (n13.type !== undefined) {
      this.type = n13.type;
    }
    if (n13.counterDirection !== undefined) {
      this.counterDirection = n13.counterDirection;
    }
    if (n13.choverEffect !== undefined) {
      this.choverEffect = n13.choverEffect;
    }
    if (n13.focusEnable !== undefined) {
      this.focusEnable = n13.focusEnable;
    }
    if (n13.step !== undefined) {
      this.step = n13.step;
    }
    if (n13.inputValue !== undefined) {
      this.inputValue = n13.inputValue;
    }
    if (n13.inputYear !== undefined) {
      this.inputYear = n13.inputYear;
    }
    if (n13.inputMoon !== undefined) {
      this.inputMoon = n13.inputMoon;
    }
    if (n13.inputDay !== undefined) {
      this.inputDay = n13.inputDay;
    }
    if (n13.inputHour !== undefined) {
      this.inputHour = n13.inputHour;
    }
    if (n13.inputMinute !== undefined) {
      this.inputMinute = n13.inputMinute;
    }
    if (n13.inputSecond !== undefined) {
      this.inputSecond = n13.inputSecond;
    }
    if (n13.subOpacity !== undefined) {
      this.subOpacity = n13.subOpacity;
    }
    if (n13.addOpacity !== undefined) {
      this.addOpacity = n13.addOpacity;
    }
    if (n13.subBtnStateEffect !== undefined) {
      this.subBtnStateEffect = n13.subBtnStateEffect;
    }
    if (n13.addBtnStateEffect !== undefined) {
      this.addBtnStateEffect = n13.addBtnStateEffect;
    }
    if (n13.focusText !== undefined) {
      this.focusText = n13.focusText;
    }
    if (n13.hasFocusText1 !== undefined) {
      this.hasFocusText1 = n13.hasFocusText1;
    }
    if (n13.hasFocusText2 !== undefined) {
      this.hasFocusText2 = n13.hasFocusText2;
    }
    if (n13.hasFocusText3 !== undefined) {
      this.hasFocusText3 = n13.hasFocusText3;
    }
    if (n13.subBtnFocusWidh !== undefined) {
      this.subBtnFocusWidh = n13.subBtnFocusWidh;
    }
    if (n13.addBtnFocusWidh !== undefined) {
      this.addBtnFocusWidh = n13.addBtnFocusWidh;
    }
    if (n13.value !== undefined) {
      this.value = n13.value;
    }
    if (n13.year !== undefined) {
      this.year = n13.year;
    }
    if (n13.month !== undefined) {
      this.month = n13.month;
    }
    if (n13.day !== undefined) {
      this.day = n13.day;
    }
    if (n13.hour !== undefined) {
      this.hour = n13.hour;
    }
    if (n13.minute !== undefined) {
      this.minute = n13.minute;
    }
    if (n13.second !== undefined) {
      this.second = n13.second;
    }
    if (n13.subBtnEnabled !== undefined) {
      this.subBtnEnabled = n13.subBtnEnabled;
    }
    if (n13.addBtnEnabled !== undefined) {
      this.addBtnEnabled = n13.addBtnEnabled;
    }
    if (n13.hasInputText1 !== undefined) {
      this.hasInputText1 = n13.hasInputText1;
    }
    if (n13.hasInputText2 !== undefined) {
      this.hasInputText2 = n13.hasInputText2;
    }
    if (n13.hasInputText3 !== undefined) {
      this.hasInputText3 = n13.hasInputText3;
    }
    if (n13.textWidth !== undefined) {
      this.textWidth = n13.textWidth;
    }
    if (n13.min !== undefined) {
      this.min = n13.min;
    }
    if (n13.max !== undefined) {
      this.max = n13.max;
    }
    if (n13.maxYear !== undefined) {
      this.maxYear = n13.maxYear;
    }
    if (n13.minYear !== undefined) {
      this.minYear = n13.minYear;
    }
    if (n13.numberStrList !== undefined) {
      this.numberStrList = n13.numberStrList;
    }
    if (n13.onHoverIncrease !== undefined) {
      this.onHoverIncrease = n13.onHoverIncrease;
    }
    if (n13.onHoverDecrease !== undefined) {
      this.onHoverDecrease = n13.onHoverDecrease;
    }
    if (n13.onFocusIncrease !== undefined) {
      this.onFocusIncrease = n13.onFocusIncrease;
    }
    if (n13.onFocusDecrease !== undefined) {
      this.onFocusDecrease = n13.onFocusDecrease;
    }
    if (n13.onBlurIncrease !== undefined) {
      this.onBlurIncrease = n13.onBlurIncrease;
    }
    if (n13.onBlurDecrease !== undefined) {
      this.onBlurDecrease = n13.onBlurDecrease;
    }
    if (n13.onChange !== undefined) {
      this.onChange = n13.onChange;
    }
    if (n13.onDateChange !== undefined) {
      this.onDateChange = n13.onDateChange;
    }
    if (n13.timeoutID1 !== undefined) {
      this.timeoutID1 = n13.timeoutID1;
    }
    if (n13.timeoutID2 !== undefined) {
      this.timeoutID2 = n13.timeoutID2;
    }
    if (n13.timeoutID3 !== undefined) {
      this.timeoutID3 = n13.timeoutID3;
    }
    if (n13.numberStyleOptions !== undefined) {
      this.numberStyleOptions = n13.numberStyleOptions;
    }
    if (n13.dateStyleOptions !== undefined) {
      this.dateStyleOptions = n13.dateStyleOptions;
    }
    if (n13.inlineStyleOptions !== undefined) {
      this.inlineStyleOptions = n13.inlineStyleOptions;
    }
    if (n13.timeStamp !== undefined) {
      this.timeStamp = n13.timeStamp;
    }
    if (n13.hasTextWidth !== undefined) {
      this.hasTextWidth = n13.hasTextWidth;
    }
    if (n13.controller1 !== undefined) {
      this.controller1 = n13.controller1;
    }
    if (n13.controller2 !== undefined) {
      this.controller2 = n13.controller2;
    }
    if (n13.controller3 !== undefined) {
      this.controller3 = n13.controller3;
    }
    if (n13.initFlag !== undefined) {
      this.initFlag = n13.initFlag;
    }
    if (n13.increaseStr !== undefined) {
      this.increaseStr = n13.increaseStr;
    }
    if (n13.reduceStr !== undefined) {
      this.reduceStr = n13.reduceStr;
    }
  }
  updateStateVars(m13) {
    this.__options.reset(m13.options);
  }
  purgeVariableDependenciesOnElmtId(l13) {
    this.__options.purgeDependencyOnElmtId(l13);
    this.__type.purgeDependencyOnElmtId(l13);
    this.__counterDirection.purgeDependencyOnElmtId(l13);
    this.__choverEffect.purgeDependencyOnElmtId(l13);
    this.__focusEnable.purgeDependencyOnElmtId(l13);
    this.__step.purgeDependencyOnElmtId(l13);
    this.__inputValue.purgeDependencyOnElmtId(l13);
    this.__inputYear.purgeDependencyOnElmtId(l13);
    this.__inputMoon.purgeDependencyOnElmtId(l13);
    this.__inputDay.purgeDependencyOnElmtId(l13);
    this.__inputHour.purgeDependencyOnElmtId(l13);
    this.__inputMinute.purgeDependencyOnElmtId(l13);
    this.__inputSecond.purgeDependencyOnElmtId(l13);
    this.__subOpacity.purgeDependencyOnElmtId(l13);
    this.__addOpacity.purgeDependencyOnElmtId(l13);
    this.__subBtnStateEffect.purgeDependencyOnElmtId(l13);
    this.__addBtnStateEffect.purgeDependencyOnElmtId(l13);
    this.__focusText.purgeDependencyOnElmtId(l13);
    this.__hasFocusText1.purgeDependencyOnElmtId(l13);
    this.__hasFocusText2.purgeDependencyOnElmtId(l13);
    this.__hasFocusText3.purgeDependencyOnElmtId(l13);
    this.__subBtnFocusWidh.purgeDependencyOnElmtId(l13);
    this.__addBtnFocusWidh.purgeDependencyOnElmtId(l13);
    this.__value.purgeDependencyOnElmtId(l13);
    this.__year.purgeDependencyOnElmtId(l13);
    this.__month.purgeDependencyOnElmtId(l13);
    this.__day.purgeDependencyOnElmtId(l13);
    this.__hour.purgeDependencyOnElmtId(l13);
    this.__minute.purgeDependencyOnElmtId(l13);
    this.__second.purgeDependencyOnElmtId(l13);
    this.__subBtnEnabled.purgeDependencyOnElmtId(l13);
    this.__addBtnEnabled.purgeDependencyOnElmtId(l13);
    this.__hasInputText1.purgeDependencyOnElmtId(l13);
    this.__hasInputText2.purgeDependencyOnElmtId(l13);
    this.__hasInputText3.purgeDependencyOnElmtId(l13);
    this.__textWidth.purgeDependencyOnElmtId(l13);
    this.__min.purgeDependencyOnElmtId(l13);
    this.__max.purgeDependencyOnElmtId(l13);
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
  set options(k13) {
    this.__options.set(k13);
  }
  get type() {
    return this.__type.get();
  }
  set type(j13) {
    this.__type.set(j13);
  }
  get counterDirection() {
    return this.__counterDirection.get();
  }
  set counterDirection(i13) {
    this.__counterDirection.set(i13);
  }
  get choverEffect() {
    return this.__choverEffect.get();
  }
  set choverEffect(h13) {
    this.__choverEffect.set(h13);
  }
  get focusEnable() {
    return this.__focusEnable.get();
  }
  set focusEnable(g13) {
    this.__focusEnable.set(g13);
  }
  get step() {
    return this.__step.get();
  }
  set step(f13) {
    this.__step.set(f13);
  }
  get inputValue() {
    return this.__inputValue.get();
  }
  set inputValue(e13) {
    this.__inputValue.set(e13);
  }
  get inputYear() {
    return this.__inputYear.get();
  }
  set inputYear(d13) {
    this.__inputYear.set(d13);
  }
  get inputMoon() {
    return this.__inputMoon.get();
  }
  set inputMoon(c13) {
    this.__inputMoon.set(c13);
  }
  get inputDay() {
    return this.__inputDay.get();
  }
  set inputDay(b13) {
    this.__inputDay.set(b13);
  }
  get inputHour() {
    return this.__inputHour.get();
  }
  set inputHour(a13) {
    this.__inputHour.set(a13);
  }
  get inputMinute() {
    return this.__inputMinute.get();
  }
  set inputMinute(z12) {
    this.__inputMinute.set(z12);
  }
  get inputSecond() {
    return this.__inputSecond.get();
  }
  set inputSecond(y12) {
    this.__inputSecond.set(y12);
  }
  get subOpacity() {
    return this.__subOpacity.get();
  }
  set subOpacity(x12) {
    this.__subOpacity.set(x12);
  }
  get addOpacity() {
    return this.__addOpacity.get();
  }
  set addOpacity(w12) {
    this.__addOpacity.set(w12);
  }
  get subBtnStateEffect() {
    return this.__subBtnStateEffect.get();
  }
  set subBtnStateEffect(v12) {
    this.__subBtnStateEffect.set(v12);
  }
  get addBtnStateEffect() {
    return this.__addBtnStateEffect.get();
  }
  set addBtnStateEffect(u12) {
    this.__addBtnStateEffect.set(u12);
  }
  get focusText() {
    return this.__focusText.get();
  }
  set focusText(t12) {
    this.__focusText.set(t12);
  }
  get hasFocusText1() {
    return this.__hasFocusText1.get();
  }
  set hasFocusText1(s12) {
    this.__hasFocusText1.set(s12);
  }
  get hasFocusText2() {
    return this.__hasFocusText2.get();
  }
  set hasFocusText2(r12) {
    this.__hasFocusText2.set(r12);
  }
  get hasFocusText3() {
    return this.__hasFocusText3.get();
  }
  set hasFocusText3(q12) {
    this.__hasFocusText3.set(q12);
  }
  get subBtnFocusWidh() {
    return this.__subBtnFocusWidh.get();
  }
  set subBtnFocusWidh(p12) {
    this.__subBtnFocusWidh.set(p12);
  }
  get addBtnFocusWidh() {
    return this.__addBtnFocusWidh.get();
  }
  set addBtnFocusWidh(o12) {
    this.__addBtnFocusWidh.set(o12);
  }
  get value() {
    return this.__value.get();
  }
  set value(n12) {
    this.__value.set(n12);
  }
  get year() {
    return this.__year.get();
  }
  set year(m12) {
    this.__year.set(m12);
  }
  get month() {
    return this.__month.get();
  }
  set month(l12) {
    this.__month.set(l12);
  }
  get day() {
    return this.__day.get();
  }
  set day(k12) {
    this.__day.set(k12);
  }
  get hour() {
    return this.__hour.get();
  }
  set hour(j12) {
    this.__hour.set(j12);
  }
  get minute() {
    return this.__minute.get();
  }
  set minute(i12) {
    this.__minute.set(i12);
  }
  get second() {
    return this.__second.get();
  }
  set second(h12) {
    this.__second.set(h12);
  }
  get subBtnEnabled() {
    return this.__subBtnEnabled.get();
  }
  set subBtnEnabled(g12) {
    this.__subBtnEnabled.set(g12);
  }
  get addBtnEnabled() {
    return this.__addBtnEnabled.get();
  }
  set addBtnEnabled(f12) {
    this.__addBtnEnabled.set(f12);
  }
  get hasInputText1() {
    return this.__hasInputText1.get();
  }
  set hasInputText1(e12) {
    this.__hasInputText1.set(e12);
  }
  get hasInputText2() {
    return this.__hasInputText2.get();
  }
  set hasInputText2(d12) {
    this.__hasInputText2.set(d12);
  }
  get hasInputText3() {
    return this.__hasInputText3.get();
  }
  set hasInputText3(c12) {
    this.__hasInputText3.set(c12);
  }
  get textWidth() {
    return this.__textWidth.get();
  }
  set textWidth(b12) {
    this.__textWidth.set(b12);
  }
  get min() {
    return this.__min.get();
  }
  set min(a12) {
    this.__min.set(a12);
  }
  get max() {
    return this.__max.get();
  }
  set max(z11) {
    this.__max.set(z11);
  }
  getTextInputFontSize() {
    let w11 = this.resourceToVp(CounterResource.COUNTER_NUMBER_SIZE);
    let x11 = this.getUIContext();
    let y11 = x11.getHostContext()?.config?.fontSizeScale ?? 1;
    if (y11 < 1) {
      return w11 + 'fp';
    } else {
      return w11 + 'vp';
    }
  }
  getDateYear() {
    let r11 = new intl.Locale();
    let s11 = r11.toString();
    let t11 = new Date(this.year, this.month - 1, this.day);
    let u11 = new intl.DateTimeFormat(s11, { year: 'numeric' });
    let v11 = u11.format(t11);
    return v11;
  }
  getDateMonth() {
    let m11 = new intl.Locale();
    let n11 = m11.toString();
    let o11 = new Date(this.year, this.month - 1, this.day);
    let p11 = new intl.DateTimeFormat(n11, { month: 'long' });
    let q11 = p11.format(o11);
    return q11;
  }
  getDateDay() {
    let l11 = new Map([
      [
        1,
        getContext().resourceManager.getStringByNameSync(
          'First_counter_accessibility_text'
        ),
      ],
      [
        2,
        getContext().resourceManager.getStringByNameSync(
          'Second_counter_accessibility_text'
        ),
      ],
      [
        3,
        getContext().resourceManager.getStringByNameSync(
          'Third_counter_accessibility_text'
        ),
      ],
      [
        4,
        getContext().resourceManager.getStringByNameSync(
          'Fourth_counter_accessibility_text'
        ),
      ],
      [
        5,
        getContext().resourceManager.getStringByNameSync(
          'Fifth_counter_accessibility_text'
        ),
      ],
      [
        6,
        getContext().resourceManager.getStringByNameSync(
          'Sixth_counter_accessibility_text'
        ),
      ],
      [
        7,
        getContext().resourceManager.getStringByNameSync(
          'Seventh_counter_accessibility_text'
        ),
      ],
      [
        8,
        getContext().resourceManager.getStringByNameSync(
          'Eighth_counter_accessibility_text'
        ),
      ],
      [
        9,
        getContext().resourceManager.getStringByNameSync(
          'Ninth_counter_accessibility_text'
        ),
      ],
      [
        10,
        getContext().resourceManager.getStringByNameSync(
          'Tenth_counter_accessibility_text'
        ),
      ],
      [
        11,
        getContext().resourceManager.getStringByNameSync(
          'Eleventh_counter_accessibility_text'
        ),
      ],
      [
        12,
        getContext().resourceManager.getStringByNameSync(
          'Twelfth_counter_accessibility_text'
        ),
      ],
      [
        13,
        getContext().resourceManager.getStringByNameSync(
          'Thirteenth_counter_accessibility_text'
        ),
      ],
      [
        14,
        getContext().resourceManager.getStringByNameSync(
          'Fourteenth_counter_accessibility_text'
        ),
      ],
      [
        15,
        getContext().resourceManager.getStringByNameSync(
          'Fifteenth_counter_accessibility_text'
        ),
      ],
      [
        16,
        getContext().resourceManager.getStringByNameSync(
          'Sixteenth_counter_accessibility_text'
        ),
      ],
      [
        17,
        getContext().resourceManager.getStringByNameSync(
          'Seventeenth_counter_accessibility_text'
        ),
      ],
      [
        18,
        getContext().resourceManager.getStringByNameSync(
          'Eighteenth_counter_accessibility_text'
        ),
      ],
      [
        19,
        getContext().resourceManager.getStringByNameSync(
          'Nineteenth_counter_accessibility_text'
        ),
      ],
      [
        20,
        getContext().resourceManager.getStringByNameSync(
          'Twentieth_counter_accessibility_text'
        ),
      ],
      [
        21,
        getContext().resourceManager.getStringByNameSync(
          'TwentyFirst_counter_accessibility_text'
        ),
      ],
      [
        22,
        getContext().resourceManager.getStringByNameSync(
          'TwentySecond_counter_accessibility_text'
        ),
      ],
      [
        23,
        getContext().resourceManager.getStringByNameSync(
          'TwentyThird_counter_accessibility_text'
        ),
      ],
      [
        24,
        getContext().resourceManager.getStringByNameSync(
          'TwentyFourth_counter_accessibility_text'
        ),
      ],
      [
        25,
        getContext().resourceManager.getStringByNameSync(
          'TwentyFifth_counter_accessibility_text'
        ),
      ],
      [
        26,
        getContext().resourceManager.getStringByNameSync(
          'TwentySixth_counter_accessibility_text'
        ),
      ],
      [
        27,
        getContext().resourceManager.getStringByNameSync(
          'TwentySeventh_counter_accessibility_text'
        ),
      ],
      [
        28,
        getContext().resourceManager.getStringByNameSync(
          'TwentyEighth_counter_accessibility_text'
        ),
      ],
      [
        29,
        getContext().resourceManager.getStringByNameSync(
          'TwentyNinth_counter_accessibility_text'
        ),
      ],
      [
        30,
        getContext().resourceManager.getStringByNameSync(
          'Thirtieth_counter_accessibility_text'
        ),
      ],
      [
        31,
        getContext().resourceManager.getStringByNameSync(
          'ThirtyFirst_counter_accessibility_text'
        ),
      ],
    ]);
    return l11.get(this.day);
  }
  convertNumberToString(k11) {
    if (k11 >= 0 && k11 < CounterConstant.COUNTER_TEN_NUMBER) {
      return this.numberStrList[k11];
    } else {
      return k11.toString();
    }
  }
  aboutToAppear() {
    let j11 = new Date();
    this.timeStamp = j11.getTime();
    if (this.options !== undefined && this.options !== null) {
      this.onOptionsChange();
    }
  }
  updateNumberStyleOptions() {
    if (this.numberStyleOptions.label === undefined) {
      this.numberStyleOptions.label = '';
    }
    if (this.initFlag) {
      this.initFlag = false;
      this.value =
        this.numberStyleOptions.value !== undefined
          ? this.numberStyleOptions.value
          : 0;
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
      } else {
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
    if (this.initFlag) {
      this.initFlag = false;
      this.value =
        this.inlineStyleOptions.value !== undefined
          ? this.inlineStyleOptions.value
          : 0;
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
      } else {
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
      } else {
        this.step = Math.floor(this.dateStyleOptions.step);
      }
    }
    if (this.dateStyleOptions.onHoverIncrease !== undefined) {
      this.onHoverIncrease = this.dateStyleOptions.onHoverIncrease;
    }
    if (this.dateStyleOptions.onHoverDecrease !== undefined) {
      this.onHoverDecrease = this.dateStyleOptions.onHoverDecrease;
    }
    if (
      this.dateStyleOptions.year !== undefined &&
      this.dateStyleOptions.year >= this.minYear &&
      this.dateStyleOptions.year <= this.maxYear
    ) {
      if (this.year === 0) {
        this.year = this.dateStyleOptions.year;
      }
    } else {
      this.year = CounterConstant.COUNTER_MIN_YEAR;
    }
    if (
      this.dateStyleOptions.month !== undefined &&
      this.dateStyleOptions.month <= CounterConstant.COUNTER_MAX_MONTH &&
      this.dateStyleOptions.month >= CounterConstant.COUNTER_MIN_MONTH
    ) {
      if (this.month === 0) {
        this.month = this.dateStyleOptions.month;
      }
    } else {
      this.month = CounterConstant.COUNTER_INITIAL_MONTH;
    }
    if (
      this.dateStyleOptions.day !== undefined &&
      this.dateStyleOptions.day <= this.getDayNumber() &&
      this.dateStyleOptions.day >= CounterConstant.COUNTER_MIN_DAY
    ) {
      if (this.day === 0) {
        this.day = this.dateStyleOptions.day;
      }
    } else {
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
    } else {
      this.counterDirection = Direction.Auto;
    }
    if (this.type === CounterType.LIST || this.type === CounterType.COMPACT) {
      if (this.options.numberOptions !== undefined) {
        this.numberStyleOptions = this.options.numberOptions;
      }
      this.updateNumberStyleOptions();
    } else if (this.type === CounterType.INLINE) {
      if (this.options.inlineOptions !== undefined) {
        this.inlineStyleOptions = this.options.inlineOptions;
      }
      this.updateInlineStyleOptions();
    } else if (this.type === CounterType.INLINE_DATE) {
      let i11 = this.options.dateOptions;
      if (i11 !== undefined) {
        i11.year = i11.year ? i11.year : CounterConstant.COUNTER_MIN_YEAR;
        i11.month = i11.month ? i11.month : CounterConstant.COUNTER_MIN_MONTH;
        i11.day = i11.day ? i11.day : CounterConstant.COUNTER_MIN_DAY;
        this.dateStyleOptions = i11;
      }
      this.updateDateStyleOptions();
    } else {
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
    } else {
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
    } else {
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
        if (
          (this.year % CounterConstant.AUSPICIOUS_FOUR === 0 &&
            this.year % CounterConstant.AUSPICIOUS_HUNDRED !== 0) ||
          this.year % CounterConstant.AUSPICIOUS_FOUR_HUNDRED === 0
        ) {
          return CounterConstant.AUSPICIOUS_FEBRUARY_DAYS;
        } else {
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
      } else {
        if (
          this.subOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
        ) {
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
        let a11 = new intl.Locale();
        let b11 = a11.toString();
        let c11 = new Date(this.year, this.month - 1, this.day);
        let d11 = new intl.DateTimeFormat(b11, { year: 'numeric' });
        let e11 = d11.format(c11);
        let f11 = new intl.DateTimeFormat(b11, { month: 'long' });
        let g11 = f11.format(c11);
        let h11 = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            e11 + ',' + e11 + '/' + g11 + '/' + this.getDateDay(),
        };
        accessibility.sendAccessibilityEvent(h11).then(() => {
          console.log('Accessility subYear click send event');
        });
      } catch (x10) {
        let y10 = x10.code;
        let z10 = x10.message;
        console.log(
          `Accessility subYear faild error code:${y10} message:${z10}`
        );
      }
    } else if (this.focusText === FocusText.TEXT2) {
      this.month -= this.step % CounterConstant.COUNTER_MAX_MONTH;
      if (this.month < CounterConstant.COUNTER_MIN_MONTH) {
        this.month += CounterConstant.COUNTER_MAX_MONTH;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
      try {
        let p10 = new intl.Locale();
        let q10 = p10.toString();
        let r10 = new Date(this.year, this.month - 1, this.day);
        let s10 = new intl.DateTimeFormat(q10, { year: 'numeric' });
        let t10 = s10.format(r10);
        let u10 = new intl.DateTimeFormat(q10, { month: 'long' });
        let v10 = u10.format(r10);
        let w10 = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            v10 + ',' + t10 + '/' + v10 + '/' + this.getDateDay(),
        };
        accessibility.sendAccessibilityEvent(w10).then(() => {
          console.log('Accessility subMonth click send event');
        });
      } catch (m10) {
        let n10 = m10.code;
        let o10 = m10.message;
        console.log(
          `Accessility subMonth faild error code:${n10} message:${o10}`
        );
      }
    } else if (this.focusText === FocusText.TEXT3) {
      this.day -= this.step % this.getDayNumber();
      if (this.day < CounterConstant.COUNTER_MIN_DAY) {
        this.day += this.getDayNumber();
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
      try {
        let e10 = new intl.Locale();
        let f10 = e10.toString();
        let g10 = new Date(this.year, this.month - 1, this.day);
        let h10 = new intl.DateTimeFormat(f10, { year: 'numeric' });
        let i10 = h10.format(g10);
        let j10 = new intl.DateTimeFormat(f10, { month: 'long' });
        let k10 = j10.format(g10);
        let l10 = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            this.getDateDay() + ',' + i10 + '/' + k10 + '/' + this.getDateDay(),
        };
        accessibility.sendAccessibilityEvent(l10).then(() => {
          console.log('Accessility subDay click send event');
        });
      } catch (b10) {
        let c10 = b10.code;
        let d10 = b10.message;
        console.log(
          `Accessility subDay faild error code:${c10} message:${d10}`
        );
      }
    } else {
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
      } else {
        if (
          this.subOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
        ) {
          this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        }
        if (!this.subBtnStateEffect) {
          this.subBtnStateEffect = true;
        }
        if (!this.subBtnEnabled) {
          this.subBtnEnabled = true;
        }
      }
    } else if (this.focusText === FocusText.TEXT2) {
      this.month -= this.step % CounterConstant.COUNTER_MAX_MONTH;
      if (this.month < CounterConstant.COUNTER_MIN_MONTH) {
        this.month += CounterConstant.COUNTER_MAX_MONTH;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (this.focusText === FocusText.TEXT3) {
      this.day -= this.step % this.getDayNumber();
      if (this.day < CounterConstant.COUNTER_MIN_DAY) {
        this.day += this.getDayNumber();
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
    } else {
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
      } else {
        if (
          this.addOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
        ) {
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
        let t9 = new intl.Locale();
        let u9 = t9.toString();
        let v9 = new Date(this.year, this.month - 1, this.day);
        let w9 = new intl.DateTimeFormat(u9, { year: 'numeric' });
        let x9 = w9.format(v9);
        let y9 = new intl.DateTimeFormat(u9, { month: 'long' });
        let z9 = y9.format(v9);
        let a10 = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            x9 + ',' + x9 + '/' + z9 + '/' + this.getDateDay(),
        };
        accessibility.sendAccessibilityEvent(a10).then(() => {
          console.log('Accessility addYear click send event');
        });
      } catch (q9) {
        let r9 = q9.code;
        let s9 = q9.message;
        console.log(
          `Accessility addYear click faild error code:${r9} message:${s9}`
        );
      }
    } else if (this.focusText === FocusText.TEXT2) {
      this.month += this.step % CounterConstant.COUNTER_MAX_MONTH;
      if (this.month > CounterConstant.COUNTER_MAX_MONTH) {
        this.month -= CounterConstant.COUNTER_MAX_MONTH;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
      try {
        let i9 = new intl.Locale();
        let j9 = i9.toString();
        let k9 = new Date(this.year, this.month - 1, this.day);
        let l9 = new intl.DateTimeFormat(j9, { year: 'numeric' });
        let m9 = l9.format(k9);
        let n9 = new intl.DateTimeFormat(j9, { month: 'long' });
        let o9 = n9.format(k9);
        let p9 = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            o9 + ',' + m9 + '/' + o9 + '/' + this.getDateDay(),
        };
        accessibility.sendAccessibilityEvent(p9).then(() => {
          console.log('Accessility addMonth click send event');
        });
      } catch (f9) {
        let g9 = f9.code;
        let h9 = f9.message;
        console.log(
          `Accessility addMonth faild error code:${g9} message:${h9}`
        );
      }
    } else if (this.focusText === FocusText.TEXT3) {
      this.day += this.step % this.getDayNumber();
      if (this.day > this.getDayNumber()) {
        this.day -= this.getDayNumber();
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
      try {
        let x8 = new intl.Locale();
        let y8 = x8.toString();
        let z8 = new Date(this.year, this.month - 1, this.day);
        let a9 = new intl.DateTimeFormat(y8, { year: 'numeric' });
        let b9 = a9.format(z8);
        let c9 = new intl.DateTimeFormat(y8, { month: 'long' });
        let d9 = c9.format(z8);
        let e9 = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            this.getDateDay() + ',' + b9 + '/' + d9 + '/' + this.getDateDay(),
        };
        accessibility.sendAccessibilityEvent(e9).then(() => {
          console.log('Accessility addDay click send event');
        });
      } catch (u8) {
        let v8 = u8.code;
        let w8 = u8.message;
        console.log(`Accessility addDay faild error code:${v8} message:${w8}`);
      }
    } else {
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
      } else {
        if (
          this.addOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
        ) {
          this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        }
        if (!this.addBtnStateEffect) {
          this.addBtnStateEffect = true;
        }
        if (!this.addBtnEnabled) {
          this.addBtnEnabled = true;
        }
      }
    } else if (this.focusText === FocusText.TEXT2) {
      this.month += this.step % CounterConstant.COUNTER_MAX_MONTH;
      if (this.month > CounterConstant.COUNTER_MAX_MONTH) {
        this.month -= CounterConstant.COUNTER_MAX_MONTH;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (this.focusText === FocusText.TEXT3) {
      this.day += this.step % this.getDayNumber();
      if (this.day > this.getDayNumber()) {
        this.day -= this.getDayNumber();
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
    } else {
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
    } else {
      this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
      this.addBtnStateEffect = true;
      this.addBtnEnabled = true;
    }
    if (this.value <= this.min) {
      this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
      this.subBtnStateEffect = false;
      this.subBtnEnabled = false;
    } else {
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
    } else {
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
    } else {
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
    let t8 = this.year.toString();
    if (t8.length === 1) {
      t8 = '000' + t8;
    } else if (t8.length === 2) {
      t8 = '00' + t8;
    } else if (t8.length === 3) {
      t8 = '0' + t8;
    } else {
      t8 = t8;
    }
    return t8;
  }
  focusWithTarget(r8) {
    setTimeout(() => {
      let s8 = focusControl.requestFocus(r8);
      if (s8) {
        console.log('Request success');
      } else {
        console.log('Request failed');
      }
    });
  }
  focusCurrentText(q8) {
    if (q8 === FocusText.TEXT1) {
      if (this.focusText === FocusText.NONE) {
        this.focusText = FocusText.TEXT1;
      }
      if (!this.hasFocusText1) {
        this.hasFocusText1 = true;
      }
    } else if (q8 === FocusText.TEXT2) {
      if (this.focusText === FocusText.NONE) {
        this.focusText = FocusText.TEXT2;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (q8 === FocusText.TEXT3) {
      if (this.focusText === FocusText.NONE) {
        this.focusText = FocusText.TEXT3;
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
    } else {
    }
  }
  getMaxLength() {
    if (this.max.toString().length > this.min.toString().length) {
      return this.max.toString().length + 1;
    } else {
      return this.min.toString().length + 1;
    }
  }
  resourceToVp(o8) {
    try {
      if (o8.id !== -1) {
        return px2vp(getContext(this).resourceManager.getNumber(o8.id));
      } else {
        return px2vp(
          getContext(this).resourceManager.getNumberByName(
            o8.params[0].split('.')[2]
          )
        );
      }
    } catch (p8) {
      return CounterResource.COUNTER_LIST_PADDING;
    }
  }
  getAccessibilityResource(j8) {
    let k8 = '';
    try {
      if (typeof j8 === 'string') {
        k8 = j8;
      } else {
        k8 = getContext()?.resourceManager?.getStringSync(j8?.id);
      }
    } catch (l8) {
      let m8 = l8.code;
      let n8 = l8.message;
      console.log(`Get accessility resource error code:${m8} message:${n8}`);
    }
    return k8;
  }
  initialRender() {
    this.observeComponentCreation2((a, b) => {
      If.create();
      if (this.type === CounterType.LIST) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((h8, i8) => {
            RelativeContainer.create();
            RelativeContainer.direction(this.counterDirection);
            RelativeContainer.width('100%');
            RelativeContainer.height(CounterResource.COUNTER_LIST_HEIGHT);
          }, RelativeContainer);
          this.observeComponentCreation2((f8, g8) => {
            Text.create(this.numberStyleOptions.label);
            Text.direction(this.counterDirection);
            Text.fontSize(CounterResource.COUNTER_LIST_LABEL_SIZE);
            Text.maxFontScale(
              CounterResource.COUNTER_LABEL_MAX_FONT_SIZE_SCALE
            );
            Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
            Text.margin({
              start: LengthMetrics.vp(
                this.resourceToVp(CounterResource.COUNTER_LIST_LEFT_PADDING)
              ),
            });
            Text.alignRules({
              center: { anchor: '__container__', align: VerticalAlign.Center },
              start: { anchor: '__container__', align: HorizontalAlign.Start },
              end: { anchor: 'Row1', align: HorizontalAlign.Start },
            });
            Text.id('Text');
          }, Text);
          Text.pop();
          this.observeComponentCreation2((d8, e8) => {
            Row.create();
            Row.direction(this.counterDirection);
            Row.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
            Row.margin({
              end: LengthMetrics.vp(
                this.resourceToVp(CounterResource.COUNTER_LIST_RIGHT_PADDING)
              ),
            });
            Row.alignRules({
              center: { anchor: '__container__', align: VerticalAlign.Center },
              end: { anchor: '__container__', align: HorizontalAlign.End },
            });
            Row.tabIndex(0);
            Row.id('Row1');
          }, Row);
          this.observeComponentCreation2((b8, c8) => {
            Stack.create();
            Stack.direction(this.counterDirection);
            Stack.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
            Stack.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
            Stack.borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS);
            Stack.borderWidth(this.subBtnFocusWidh);
            Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((z7, a8) => {
            Image.create(CounterResource.BUTTON_SUB_ICON);
            Image.direction(this.counterDirection);
            Image.width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
            Image.height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
            Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
            Image.opacity(this.subOpacity);
          }, Image);
          this.observeComponentCreation2((l7, m7) => {
            Button.createWithLabel({
              type: ButtonType.Circle,
              stateEffect: this.subBtnStateEffect,
            });
            Button.accessibilityText({
              id: -1,
              type: 10003,
              params: ['sys.string.reduce_used_for_accessibility_text'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            Button.accessibilityDescription(
              this.value === this.min ? '' : this.reduceStr
            );
            Button.direction(this.counterDirection);
            Button.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
            Button.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
            Button.responseRegion({
              x: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_X,
              y: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_Y,
              width: '150%',
              height: '150%',
            });
            Button.groupDefaultFocus(true);
            Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
            Button.opacity(this.subOpacity);
            Button.enabled(this.subBtnEnabled);
            Button.key('ListSubButton' + this.timeStamp.toString());
            Button.onKeyEvent((y7) => {
              this.subBtnFocusWidh =
                CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
              if (y7.keyCode === CounterConstant.KEYCODE_ESC) {
                this.resetFocusButton();
                y7.stopPropagation();
              }
              if (
                y7.type === KeyType.Down &&
                y7.keyCode === CounterConstant.KEYCODE_MOVE_HOME
              ) {
                y7.stopPropagation();
                this.homeFirstValue();
                this.focusWithTarget(
                  'ListAddButton' + this.timeStamp.toString()
                );
              }
              if (
                y7.type === KeyType.Down &&
                y7.keyCode === CounterConstant.KEYCODE_MOVE_END
              ) {
                y7.stopPropagation();
                if (this.addBtnStateEffect) {
                  this.addBtnStateEffect = false;
                  this.addOpacity =
                    CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                  this.addBtnEnabled = false;
                }
                this.endLastValue();
                this.focusWithTarget(
                  'ListAddButton' + this.timeStamp.toString()
                );
              }
            });
            Button.onClick((t7) => {
              this.subValue();
              this.onChange?.(this.value);
              if (
                t7.source === SourceType.Mouse ||
                t7.source === SourceType.TouchScreen
              ) {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
              }
              try {
                let x7 = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'click',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(x7).then(() => {
                  console.log('Accessility subValue click send event');
                });
              } catch (u7) {
                let v7 = u7.code;
                let w7 = u7.message;
                console.log(
                  `Accessility subValue faild error code:${v7} message:${w7}`
                );
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((s7) => {
              if (s7.repeat) {
                this.subValue();
                this.onChange?.(this.value);
              }
              this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
            });
            LongPressGesture.onActionEnd(() => {
              try {
                let r7 = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'common',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(r7).then(() => {
                  console.log('Accessility subValue longPress send event');
                });
              } catch (o7) {
                let p7 = o7.code;
                let q7 = o7.message;
                console.log(
                  `Accessility subValue longPress faild error code:${p7} message:${q7}`
                );
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((n7) => {
              this.onHoverDecrease && this.onHoverDecrease(n7);
            });
            Button.focusable(this.focusEnable);
            Button.onFocus(() => {
              this.subBtnFocusWidh =
                CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
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
          this.observeComponentCreation2((f7, g7) => {
            If.create();
            if (this.hasTextWidth) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((j7, k7) => {
                  Text.create(this.value.toString());
                  Text.accessibilityText(
                    this.getAccessibilityResource(
                      this.numberStyleOptions.label
                    ) +
                      '[n2]' +
                      this.value.toString() +
                      '[n0]'
                  );
                  Text.direction(this.counterDirection);
                  Text.width(this.textWidth.toString());
                  Text.textAlign(TextAlign.Center);
                  Text.fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE);
                  Text.maxFontScale(
                    CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE
                  );
                  Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                  Text.margin({
                    start: LengthMetrics.vp(
                      CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN
                    ),
                    end: LengthMetrics.vp(
                      CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN
                    ),
                  });
                }, Text);
                Text.pop();
              });
            } else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((h7, i7) => {
                  Text.create(this.value.toString());
                  Text.accessibilityText(
                    this.getAccessibilityResource(
                      this.numberStyleOptions.label
                    ) +
                      '[n2]' +
                      this.value.toString() +
                      '[n0]'
                  );
                  Text.direction(this.counterDirection);
                  Text.textAlign(TextAlign.Center);
                  Text.fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE);
                  Text.maxFontScale(
                    CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE
                  );
                  Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                  Text.margin({
                    start: LengthMetrics.vp(
                      CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN
                    ),
                    end: LengthMetrics.vp(
                      CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN
                    ),
                  });
                }, Text);
                Text.pop();
              });
            }
          }, If);
          If.pop();
          this.observeComponentCreation2((d7, e7) => {
            Stack.create();
            Stack.direction(this.counterDirection);
            Stack.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
            Stack.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
            Stack.borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS);
            Stack.borderWidth(this.addBtnFocusWidh);
            Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((b7, c7) => {
            Image.create(CounterResource.BUTTON_ADD_ICON);
            Image.direction(this.counterDirection);
            Image.width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
            Image.height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE);
            Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
            Image.opacity(this.addOpacity);
          }, Image);
          this.observeComponentCreation2((n6, o6) => {
            Button.createWithLabel({
              type: ButtonType.Circle,
              stateEffect: this.addBtnStateEffect,
            });
            Button.accessibilityText({
              id: -1,
              type: 10003,
              params: ['sys.string.increase_used_for_accessibility_text'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            Button.accessibilityDescription(
              this.value === this.max ? '' : this.increaseStr
            );
            Button.direction(this.counterDirection);
            Button.width(CounterResource.COUNTER_LIST_BUTTON_SIZE);
            Button.height(CounterResource.COUNTER_LIST_BUTTON_SIZE);
            Button.responseRegion({
              x: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_X,
              y: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_Y,
              width: '150%',
              height: '150%',
            });
            Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
            Button.opacity(this.addOpacity);
            Button.enabled(this.addBtnEnabled);
            Button.key('ListAddButton' + this.timeStamp.toString());
            Button.onKeyEvent((a7) => {
              this.addBtnFocusWidh =
                CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
              if (a7.keyCode === CounterConstant.KEYCODE_ESC) {
                this.resetFocusButton();
                a7.stopPropagation();
              }
              if (
                a7.type === KeyType.Down &&
                a7.keyCode === CounterConstant.KEYCODE_MOVE_HOME
              ) {
                a7.stopPropagation();
                this.homeFirstValue();
                if (this.subBtnStateEffect) {
                  this.subBtnStateEffect = false;
                  this.subOpacity =
                    CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                  this.subBtnEnabled = false;
                }
                this.focusWithTarget(
                  'ListAddButton' + this.timeStamp.toString()
                );
              }
              if (
                a7.type === KeyType.Down &&
                a7.keyCode === CounterConstant.KEYCODE_MOVE_END
              ) {
                a7.stopPropagation();
                this.endLastValue();
                this.focusWithTarget(
                  'ListSubButton' + this.timeStamp.toString()
                );
              }
            });
            Button.onClick((v6) => {
              this.addValue();
              this.onChange?.(this.value);
              if (
                v6.source === SourceType.Mouse ||
                v6.source === SourceType.TouchScreen
              ) {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
              }
              try {
                let z6 = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'click',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(z6).then(() => {
                  console.log('Accessility addValue click send event');
                });
              } catch (w6) {
                let x6 = w6.code;
                let y6 = w6.message;
                console.log(
                  `Accessility addValue click longPress faild error code:${x6} message:${y6}`
                );
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((u6) => {
              if (u6.repeat) {
                this.addValue();
                this.onChange?.(this.value);
              }
              this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
            });
            LongPressGesture.onActionEnd(() => {
              try {
                let t6 = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'common',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(t6).then(() => {
                  console.log('Accessility addValue longPress send event');
                });
              } catch (q6) {
                let r6 = q6.code;
                let s6 = q6.message;
                console.log(
                  `Accessility addValue longPress longPress faild error code:${r6} message:${s6}`
                );
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((p6) => {
              this.onHoverIncrease && this.onHoverIncrease(p6);
            });
            Button.focusable(this.focusEnable);
            Button.onFocus(() => {
              this.addBtnFocusWidh =
                CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
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
      } else if (this.type === CounterType.COMPACT) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((l6, m6) => {
            Column.create();
          }, Column);
          this.observeComponentCreation2((j6, k6) => {
            Row.create();
            Row.direction(this.counterDirection);
            Row.tabIndex(0);
            Row.height(CounterResource.COUNTER_COMPACT_CONTAINER_HEIGHT);
            Row.align(Alignment.Center);
            Row.borderWidth(CounterResource.COUNTER_BORDER_WIDTH);
            Row.borderColor(CounterResource.COUNTER_BORDER_COLOR);
            Row.borderRadius(CounterResource.COUNTER_COMPACT_CONTAINER_RADIUS);
          }, Row);
          this.observeComponentCreation2((h6, i6) => {
            Stack.create();
            Stack.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
            Stack.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
            Stack.borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS);
            Stack.borderWidth(this.subBtnFocusWidh);
            Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
            Stack.margin({
              start: LengthMetrics.vp(
                this.resourceToVp(
                  CounterResource.COUNTER_COMPACT_BUTTON_CONTAINER_MARGIN
                )
              ),
            });
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((f6, g6) => {
            Image.create(CounterResource.BUTTON_SUB_ICON);
            Image.direction(this.counterDirection);
            Image.width(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
            Image.height(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
            Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
            Image.opacity(this.subOpacity);
          }, Image);
          this.observeComponentCreation2((r5, s5) => {
            Button.createWithLabel({
              type: ButtonType.Circle,
              stateEffect: this.subBtnStateEffect,
            });
            Button.accessibilityText({
              id: -1,
              type: 10003,
              params: ['sys.string.reduce_used_for_accessibility_text'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            Button.accessibilityDescription(
              this.value === this.min ? '' : this.reduceStr
            );
            Button.direction(this.counterDirection);
            Button.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
            Button.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
            Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
            Button.opacity(this.subOpacity);
            Button.enabled(this.subBtnEnabled);
            Button.key('CompactSubButton' + this.timeStamp.toString());
            Button.onKeyEvent((e6) => {
              this.subBtnFocusWidh =
                CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
              if (e6.keyCode === CounterConstant.KEYCODE_ESC) {
                this.resetFocusButton();
                e6.stopPropagation();
              }
              if (
                e6.type === KeyType.Down &&
                e6.keyCode === CounterConstant.KEYCODE_MOVE_HOME
              ) {
                e6.stopPropagation();
                this.homeFirstValue();
                this.focusWithTarget(
                  'CompactAddButton' + this.timeStamp.toString()
                );
              }
              if (
                e6.type === KeyType.Down &&
                e6.keyCode === CounterConstant.KEYCODE_MOVE_END
              ) {
                e6.stopPropagation();
                this.endLastValue();
                if (this.addBtnStateEffect) {
                  this.addBtnStateEffect = false;
                  this.addOpacity =
                    CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                  this.addBtnEnabled = false;
                }
                this.focusWithTarget(
                  'CompactSubButton' + this.timeStamp.toString()
                );
              }
            });
            Button.onClick((z5) => {
              this.subValue();
              this.onChange?.(this.value);
              if (
                z5.source === SourceType.Mouse ||
                z5.source === SourceType.TouchScreen
              ) {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
              }
              try {
                let d6 = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'click',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(d6).then(() => {
                  console.log('Accessility subValue click send event');
                });
              } catch (a6) {
                let b6 = a6.code;
                let c6 = a6.message;
                console.log(
                  `Accessility subValue click longPress faild error code:${b6} message:${c6}`
                );
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((y5) => {
              if (y5.repeat) {
                this.subValue();
                this.onChange?.(this.value);
              }
              if (
                y5.source === SourceType.Mouse ||
                y5.source === SourceType.TouchScreen
              ) {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
              }
            });
            LongPressGesture.onActionEnd(() => {
              try {
                let x5 = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'common',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(x5).then(() => {
                  console.log('Accessility subValue longPress send event');
                });
              } catch (u5) {
                let v5 = u5.code;
                let w5 = u5.message;
                console.log(
                  `Accessility subValue longPress longPress faild error code:${v5} message:${w5}`
                );
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((t5) => {
              this.onHoverDecrease && this.onHoverDecrease(t5);
            });
            Button.focusable(this.focusEnable);
            Button.groupDefaultFocus(true);
            Button.onFocus(() => {
              this.subBtnFocusWidh =
                CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
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
          this.observeComponentCreation2((l5, m5) => {
            If.create();
            if (this.hasTextWidth) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((p5, q5) => {
                  Text.create(this.value.toString());
                  Text.accessibilityText(
                    this.getAccessibilityResource(
                      this.numberStyleOptions.label
                    ) +
                      '[n2]' +
                      this.value.toString() +
                      '[n0]'
                  );
                  Text.textAlign(TextAlign.Center);
                  Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                  Text.maxFontScale(
                    CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE
                  );
                  Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                  Text.width(this.textWidth.toString());
                  Text.margin({
                    start: LengthMetrics.vp(
                      CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN
                    ),
                    end: LengthMetrics.vp(
                      CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN
                    ),
                  });
                }, Text);
                Text.pop();
              });
            } else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((n5, o5) => {
                  Text.create(this.value.toString());
                  Text.accessibilityText(
                    this.getAccessibilityResource(
                      this.numberStyleOptions.label
                    ) +
                      '[n2]' +
                      this.value.toString() +
                      '[n0]'
                  );
                  Text.direction(this.counterDirection);
                  Text.textAlign(TextAlign.Center);
                  Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
                  Text.maxFontScale(
                    CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE
                  );
                  Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
                  Text.margin({
                    start: LengthMetrics.vp(
                      CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN
                    ),
                    end: LengthMetrics.vp(
                      CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN
                    ),
                  });
                }, Text);
                Text.pop();
              });
            }
          }, If);
          If.pop();
          this.observeComponentCreation2((j5, k5) => {
            Stack.create();
            Stack.direction(this.counterDirection);
            Stack.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
            Stack.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
            Stack.borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS);
            Stack.borderWidth(this.addBtnFocusWidh);
            Stack.borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
            Stack.margin({
              end: LengthMetrics.vp(
                this.resourceToVp(
                  CounterResource.COUNTER_COMPACT_BUTTON_CONTAINER_MARGIN
                )
              ),
            });
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((h5, i5) => {
            Image.create(CounterResource.BUTTON_ADD_ICON);
            Image.direction(this.counterDirection);
            Image.width(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
            Image.height(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE);
            Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
            Image.opacity(this.addOpacity);
          }, Image);
          this.observeComponentCreation2((t4, u4) => {
            Button.createWithLabel({
              type: ButtonType.Circle,
              stateEffect: this.addBtnStateEffect,
            });
            Button.accessibilityText({
              id: -1,
              type: 10003,
              params: ['sys.string.increase_used_for_accessibility_text'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            Button.accessibilityDescription(
              this.value === this.max ? '' : this.increaseStr
            );
            Button.direction(this.counterDirection);
            Button.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
            Button.height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE);
            Button.backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR);
            Button.opacity(this.addOpacity);
            Button.enabled(this.addBtnEnabled);
            Button.key('CompactAddButton' + this.timeStamp.toString());
            Button.onKeyEvent((g5) => {
              this.addBtnFocusWidh =
                CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
              if (g5.keyCode === CounterConstant.KEYCODE_ESC) {
                this.resetFocusButton();
                g5.stopPropagation();
              }
              if (
                g5.type === KeyType.Down &&
                g5.keyCode === CounterConstant.KEYCODE_MOVE_HOME
              ) {
                g5.stopPropagation();
                this.homeFirstValue();
                if (this.subBtnStateEffect) {
                  this.subBtnStateEffect = false;
                  this.subOpacity =
                    CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                  this.subBtnEnabled = false;
                }
                this.focusWithTarget(
                  'CompactAddButton' + this.timeStamp.toString()
                );
              }
              if (
                g5.type === KeyType.Down &&
                g5.keyCode === CounterConstant.KEYCODE_MOVE_END
              ) {
                g5.stopPropagation();
                this.endLastValue();
                this.focusWithTarget(
                  'CompactSubButton' + this.timeStamp.toString()
                );
              }
            });
            Button.onClick((b5) => {
              this.addValue();
              this.onChange?.(this.value);
              if (
                b5.source === SourceType.Mouse ||
                b5.source === SourceType.TouchScreen
              ) {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
              }
              try {
                let f5 = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'click',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(f5).then(() => {
                  console.log('Accessility addValue click send event');
                });
              } catch (c5) {
                let d5 = c5.code;
                let e5 = c5.message;
                console.log(
                  `Accessility addValue click longPress faild error code:${d5} message:${e5}`
                );
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((a5) => {
              if (a5.repeat) {
                this.addValue();
                this.onChange?.(this.value);
              }
              if (
                a5.source === SourceType.Mouse ||
                a5.source === SourceType.TouchScreen
              ) {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
              }
            });
            LongPressGesture.onActionEnd(() => {
              try {
                let z4 = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'common',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(z4).then(() => {
                  console.log('Accessility addValue longPress send event');
                });
              } catch (w4) {
                let x4 = w4.code;
                let y4 = w4.message;
                console.log(
                  `Accessility addValue longPress longPress faild error code:${x4} message:${y4}`
                );
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((v4) => {
              this.onHoverIncrease && this.onHoverIncrease(v4);
            });
            Button.focusable(this.focusEnable);
            Button.onFocus(() => {
              this.addBtnFocusWidh =
                CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
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
          this.observeComponentCreation2((r4, s4) => {
            Text.create(this.numberStyleOptions.label);
            Text.direction(this.counterDirection);
            Text.margin({
              top: CounterResource.COUNTER_COMPACT_CONTAINER_LABEL_DISTANCE,
            });
            Text.fontSize(CounterResource.COUNTER_COMPACT_LABEL_SIZE);
            Text.maxFontScale(
              CounterResource.COUNTER_LABEL_MAX_FONT_SIZE_SCALE
            );
            Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
            Text.align(Alignment.Top);
          }, Text);
          Text.pop();
          Column.pop();
        });
      } else if (this.type === CounterType.INLINE) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((p4, q4) => {
            Row.create();
            Row.direction(this.counterDirection);
            Row.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
            Row.borderWidth(CounterResource.COUNTER_BORDER_WIDTH);
            Row.borderColor(CounterResource.COUNTER_BORDER_COLOR);
            Row.borderRadius(CounterResource.COUNTER_INLINE_RADIUS);
            Row.clip(true);
          }, Row);
          this.observeComponentCreation2((r3, s3) => {
            If.create();
            if (this.hasTextWidth) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((n4, o4) => {
                  RelativeContainer.create();
                  RelativeContainer.direction(this.counterDirection);
                  RelativeContainer.margin({
                    start: LengthMetrics.vp(
                      CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN
                    ),
                    end: LengthMetrics.vp(
                      CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN
                    ),
                  });
                  RelativeContainer.height('100%');
                  RelativeContainer.width(this.textWidth);
                }, RelativeContainer);
                this.observeComponentCreation2((e4, f4) => {
                  TextInput.create({
                    text: this.hasInputText1
                      ? this.inputValue
                      : this.value.toString(),
                    controller: this.controller1,
                  });
                  TextInput.accessibilityDescription({
                    id: -1,
                    type: 10003,
                    params: [
                      'sys.string.input_counter_double_click_description',
                    ],
                    bundleName: '__harDefaultBundleName__',
                    moduleName: '__harDefaultModuleName__',
                  });
                  TextInput.alignRules({
                    center: {
                      anchor: '__container__',
                      align: VerticalAlign.Center,
                    },
                    middle: {
                      anchor: '__container__',
                      align: HorizontalAlign.Center,
                    },
                  });
                  TextInput.width(
                    Math.min(this.getValueLength() * 9.6, this.textWidth)
                  );
                  TextInput.height('20vp');
                  TextInput.padding(0);
                  TextInput.borderRadius(0);
                  TextInput.textAlign(TextAlign.Center);
                  TextInput.type(InputType.PhoneNumber);
                  TextInput.copyOption(CopyOptions.None);
                  TextInput.fontSize(this.getTextInputFontSize());
                  TextInput.fontWeight(FontWeight.Medium);
                  TextInput.fontColor(
                    this.hasFocusText1
                      ? Color.White
                      : CounterResource.COUNTER_TEXT_COLOR
                  );
                  TextInput.maxLength(this.getMaxLength());
                  TextInput.backgroundColor(
                    this.hasFocusText1
                      ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR
                      : Color.Transparent
                  );
                  TextInput.key('InlineTextInput' + this.timeStamp.toString());
                  TextInput.onKeyEvent((m4) => {
                    this.focusCurrentText(FocusText.TEXT1);
                    if (m4.keyCode === CounterConstant.KEYCODE_ESC) {
                      this.resetFocusText();
                      m4.stopPropagation();
                    }
                    if (
                      m4.type === KeyType.Down &&
                      m4.keyCode === CounterConstant.KEYCODE_DPAD_UP
                    ) {
                      this.addValue();
                      m4.stopPropagation();
                    }
                    if (
                      m4.type === KeyType.Down &&
                      m4.keyCode === CounterConstant.KEYCODE_MOVE_HOME
                    ) {
                      m4.stopPropagation();
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                    }
                    if (
                      m4.type === KeyType.Down &&
                      m4.keyCode === CounterConstant.KEYCODE_MOVE_END
                    ) {
                      m4.stopPropagation();
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                    }
                    if (
                      m4.type === KeyType.Down &&
                      m4.keyCode === CounterConstant.KEYCODE_DPAD_DOWN
                    ) {
                      this.subValue();
                      m4.stopPropagation();
                    }
                    if (
                      m4.type === KeyType.Down &&
                      m4.keyCode === CounterConstant.KEYCODE_DPAD_LEFT
                    ) {
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                      m4.stopPropagation();
                    }
                    if (
                      m4.type === KeyType.Down &&
                      m4.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT
                    ) {
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                      m4.stopPropagation();
                    }
                  });
                  TextInput.onChange((i4) => {
                    this.inputValue = i4;
                    for (let k4 = 0; k4 < i4.length; k4++) {
                      let l4 = i4[k4];
                      if (l4 === '+' || l4 === '*' || l4 === '#') {
                        this.value -= 1;
                        this.value += 1;
                        this.inputValue = this.value.toString();
                        return;
                      }
                      if (l4 === '-' && k4 !== 0) {
                        this.inputValue = l4;
                        break;
                      }
                    }
                    this.hasInputText1 = true;
                    let j4 = i4[i4.length - 1];
                    if (i4.length === this.getMaxLength()) {
                      this.inputValue = j4;
                    }
                    if (this.timeoutID1 !== -1) {
                      clearTimeout(this.timeoutID1);
                      this.timeoutID1 = -1;
                    }
                    if (
                      this.inputValue !== '' &&
                      Number(this.inputValue) <= this.max &&
                      Number(this.inputValue) >= this.min
                    ) {
                      this.value = Number(this.inputValue);
                      this.onChange?.(this.value);
                      this.hasInputText1 = false;
                    } else {
                      if (
                        Number(this.inputValue) > this.max ||
                        (Number(this.inputValue) < this.min &&
                          this.inputValue.length <= this.min.toString().length)
                      ) {
                        this.inputValue = j4;
                      }
                      if (i4.length < this.getMaxLength()) {
                        this.timeoutID1 = setTimeout(() => {
                          if (
                            this.inputValue !== '' &&
                            Number(this.inputValue) <= this.max &&
                            Number(this.inputValue) >= this.min
                          ) {
                            this.value = Number(this.inputValue);
                            this.onChange?.(this.value);
                          }
                          this.inputValue = this.value.toString();
                          this.hasInputText1 = false;
                          this.updateInlineEnableSate();
                        }, 1500);
                      }
                    }
                    this.updateInlineEnableSate();
                  });
                  TextInput.onSubmit((h4) => {
                    if (this.timeoutID1 != -1) {
                      clearTimeout(this.timeoutID1);
                      this.timeoutID1 = -1;
                    }
                    this.hasInputText1 = false;
                    this.value -= 1;
                    if (
                      Number(this.inputValue) >= this.min &&
                      Number(this.inputValue) <= this.max
                    ) {
                      this.value = Number(this.inputValue);
                      this.onChange?.(this.value);
                      this.updateInlineEnableSate();
                    } else {
                      this.value += 1;
                      this.inputValue = this.value.toString();
                    }
                  });
                  TextInput.focusable(true);
                  TextInput.focusOnTouch(true);
                  TextInput.onFocus(() => {
                    this.focusText = FocusText.TEXT1;
                    this.hasFocusText1 = true;
                    this.controller1.caretPosition(
                      this.value.toString().length
                    );
                  });
                  TextInput.onBlur(() => {
                    this.focusText = FocusText.NONE;
                    this.hasFocusText1 = false;
                  });
                  TextInput.onClick((g4) => {
                    this.focusText = FocusText.TEXT1;
                    this.hasFocusText1 = true;
                    this.focusWithTarget(
                      'InlineTextInput' + this.timeStamp.toString()
                    );
                    this.controller1.caretPosition(
                      this.value.toString().length
                    );
                  });
                }, TextInput);
                RelativeContainer.pop();
              });
            } else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((c4, d4) => {
                  Row.create();
                  Row.direction(this.counterDirection);
                  Row.margin({
                    start: LengthMetrics.vp(
                      CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN
                    ),
                    end: LengthMetrics.vp(
                      CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN
                    ),
                  });
                }, Row);
                this.observeComponentCreation2((t3, u3) => {
                  TextInput.create({
                    text: this.hasInputText1
                      ? this.inputValue
                      : this.value.toString(),
                    controller: this.controller1,
                  });
                  TextInput.accessibilityDescription({
                    id: -1,
                    type: 10003,
                    params: [
                      'sys.string.input_counter_double_click_description',
                    ],
                    bundleName: '__harDefaultBundleName__',
                    moduleName: '__harDefaultModuleName__',
                  });
                  TextInput.direction(this.counterDirection);
                  TextInput.width(this.getValueLength() * 9.6);
                  TextInput.height('20vp');
                  TextInput.padding(0);
                  TextInput.borderRadius(0);
                  TextInput.textAlign(TextAlign.Center);
                  TextInput.type(InputType.PhoneNumber);
                  TextInput.copyOption(CopyOptions.None);
                  TextInput.fontSize(this.getTextInputFontSize());
                  TextInput.fontWeight(FontWeight.Medium);
                  TextInput.fontColor(
                    this.hasFocusText1
                      ? Color.White
                      : CounterResource.COUNTER_TEXT_COLOR
                  );
                  TextInput.maxLength(this.getMaxLength());
                  TextInput.backgroundColor(
                    this.hasFocusText1
                      ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR
                      : Color.Transparent
                  );
                  TextInput.key('InlineTextInput' + this.timeStamp.toString());
                  TextInput.onKeyEvent((b4) => {
                    this.focusCurrentText(FocusText.TEXT1);
                    if (b4.keyCode === CounterConstant.KEYCODE_ESC) {
                      this.resetFocusText();
                      b4.stopPropagation();
                    }
                    if (
                      b4.type === KeyType.Down &&
                      b4.keyCode === CounterConstant.KEYCODE_DPAD_UP
                    ) {
                      this.addValue();
                      b4.stopPropagation();
                    }
                    if (
                      b4.type === KeyType.Down &&
                      b4.keyCode === CounterConstant.KEYCODE_DPAD_DOWN
                    ) {
                      this.subValue();
                      b4.stopPropagation();
                    }
                    if (
                      b4.type === KeyType.Down &&
                      b4.keyCode === CounterConstant.KEYCODE_DPAD_LEFT
                    ) {
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                      b4.stopPropagation();
                    }
                    if (
                      b4.type === KeyType.Down &&
                      b4.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT
                    ) {
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                      b4.stopPropagation();
                    }
                  });
                  TextInput.onChange((x3) => {
                    this.inputValue = x3;
                    for (let z3 = 0; z3 < x3.length; z3++) {
                      let a4 = x3[z3];
                      if (a4 === '+' || a4 === '*' || a4 === '#') {
                        this.value -= 1;
                        this.value += 1;
                        this.inputValue = this.value.toString();
                        return;
                      }
                      if (a4 === '-' && z3 !== 0) {
                        this.inputValue = a4;
                        break;
                      }
                    }
                    this.hasInputText1 = true;
                    let y3 = x3[x3.length - 1];
                    if (x3.length === this.getMaxLength()) {
                      this.inputValue = y3;
                    }
                    if (this.timeoutID1 !== -1) {
                      clearTimeout(this.timeoutID1);
                      this.timeoutID1 = -1;
                    }
                    if (
                      this.inputValue !== '' &&
                      Number(this.inputValue) <= this.max &&
                      Number(this.inputValue) >= this.min
                    ) {
                      this.value = Number(this.inputValue);
                      this.onChange?.(this.value);
                      this.hasInputText1 = false;
                    } else {
                      if (
                        Number(this.inputValue) > this.max ||
                        (Number(this.inputValue) < this.min &&
                          this.inputValue.length <= this.min.toString().length)
                      ) {
                        this.inputValue = y3;
                      }
                      if (x3.length < this.getMaxLength()) {
                        this.timeoutID1 = setTimeout(() => {
                          if (
                            this.inputValue !== '' &&
                            Number(this.inputValue) <= this.max &&
                            Number(this.inputValue) >= this.min
                          ) {
                            this.value = Number(this.inputValue);
                            this.onChange?.(this.value);
                          }
                          this.inputValue = this.value.toString();
                          this.hasInputText1 = false;
                          this.updateInlineEnableSate();
                        }, 1500);
                      }
                    }
                    this.updateInlineEnableSate();
                  });
                  TextInput.onSubmit((w3) => {
                    if (this.timeoutID1 !== -1) {
                      clearTimeout(this.timeoutID1);
                      this.timeoutID1 = -1;
                    }
                    this.hasInputText1 = false;
                    this.value -= 1;
                    if (
                      Number(this.inputValue) >= this.min &&
                      Number(this.inputValue) <= this.max
                    ) {
                      this.value = Number(this.inputValue);
                      this.onChange?.(this.value);
                      this.updateInlineEnableSate();
                    } else {
                      this.value += 1;
                      this.inputValue = this.value.toString();
                    }
                  });
                  TextInput.focusable(true);
                  TextInput.focusOnTouch(true);
                  TextInput.onFocus(() => {
                    this.focusText = FocusText.TEXT1;
                    this.hasFocusText1 = true;
                    this.controller1.caretPosition(
                      this.value.toString().length
                    );
                  });
                  TextInput.onBlur(() => {
                    this.focusText = FocusText.NONE;
                    this.hasFocusText1 = false;
                  });
                  TextInput.onClick((v3) => {
                    this.focusText = FocusText.TEXT1;
                    this.hasFocusText1 = true;
                    this.focusWithTarget(
                      'InlineTextInput' + this.timeStamp.toString()
                    );
                    this.controller1.caretPosition(
                      this.value.toString().length
                    );
                  });
                }, TextInput);
                Row.pop();
              });
            }
          }, If);
          If.pop();
          this.observeComponentCreation2((p3, q3) => {
            Column.create();
            Column.direction(this.counterDirection);
            Column.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
            Column.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
            Column.borderWidth({
              start: LengthMetrics.vp(
                CounterResource.COUNTER_BORDER_WIDTH_NUMBER
              ),
            });
            Column.borderColor(CounterResource.COUNTER_BORDER_COLOR);
          }, Column);
          this.observeComponentCreation2((n3, o3) => {
            Stack.create();
            Stack.direction(this.counterDirection);
            Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
            Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
            Stack.padding({ top: '1vp' });
            Stack.borderWidth({ bottom: '1vp' });
            Stack.borderColor(CounterResource.COUNTER_BORDER_COLOR);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((l3, m3) => {
            Rect.create();
            Rect.direction(this.counterDirection);
            Rect.width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH);
            Rect.height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT);
            Rect.radius([
              ['0vp', '0vp'],
              [
                CounterResource.COUNTER_INLINE_RADIUS,
                CounterResource.COUNTER_INLINE_RADIUS,
              ],
              ['0vp', '0vp'],
              ['0vp', '0vp'],
            ]);
            Rect.strokeWidth(this.addBtnFocusWidh);
            Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
            Rect.margin({ end: LengthMetrics.vp(2) });
            Rect.fillOpacity(0);
          }, Rect);
          this.observeComponentCreation2((j3, k3) => {
            Image.create(CounterResource.BUTTON_ARROW_UP);
            Image.direction(this.counterDirection);
            Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
            Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
            Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
            Image.opacity(this.addOpacity);
          }, Image);
          this.observeComponentCreation2((w2, x2) => {
            Button.createWithLabel({
              type: ButtonType.Normal,
              stateEffect: this.addBtnStateEffect,
            });
            Button.accessibilityText({
              id: -1,
              type: 10003,
              params: ['sys.string.increase_used_for_accessibility_text'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            Button.accessibilityDescription(
              this.value === this.max ? '' : this.increaseStr
            );
            Button.direction(this.counterDirection);
            Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
            Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
            Button.backgroundColor(Color.Transparent);
            Button.opacity(this.addOpacity);
            Button.enabled(this.addBtnEnabled);
            Button.onClick((e3) => {
              this.addValue();
              if (
                e3.source === SourceType.Mouse ||
                e3.source === SourceType.TouchScreen
              ) {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
              }
              try {
                let i3 = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'click',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(i3).then(() => {
                  console.log('Accessility addValue click send event');
                });
              } catch (f3) {
                let g3 = f3.code;
                let h3 = f3.message;
                console.log(
                  `Accessility addValue click longPress faild error code:${g3} message:${h3}`
                );
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((d3) => {
              if (d3.repeat) {
                this.addValue();
              }
              this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
            });
            LongPressGesture.onActionEnd(() => {
              try {
                let c3 = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'common',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(c3).then(() => {
                  console.log('Accessility addValue longPress send event');
                });
              } catch (z2) {
                let a3 = z2.code;
                let b3 = z2.message;
                console.log(
                  `Accessility addValue longPress faild error code:${a3} message:${b3}`
                );
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((y2) => {
              this.onHoverIncrease && this.onHoverIncrease(y2);
            });
            Button.focusable(false);
            Button.onFocus(() => {
              this.addBtnFocusWidh =
                CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
              this.onFocusIncrease && this.onFocusIncrease();
            });
            Button.onBlur(() => {
              this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
              this.onBlurIncrease && this.onBlurIncrease();
            });
          }, Button);
          Button.pop();
          Stack.pop();
          this.observeComponentCreation2((u2, v2) => {
            Stack.create();
            Stack.direction(this.counterDirection);
            Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
            Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((s2, t2) => {
            Rect.create();
            Rect.direction(this.counterDirection);
            Rect.width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH);
            Rect.height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT);
            Rect.radius([
              ['0vp', '0vp'],
              ['0vp', '0vp'],
              [
                CounterResource.COUNTER_INLINE_RADIUS,
                CounterResource.COUNTER_INLINE_RADIUS,
              ],
              ['0vp', '0vp'],
            ]);
            Rect.strokeWidth(this.subBtnFocusWidh);
            Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
            Rect.margin({
              top: LengthMetrics.vp(1),
              end: LengthMetrics.vp(1),
              bottom: LengthMetrics.vp(2),
            });
            Rect.fillOpacity(0);
          }, Rect);
          this.observeComponentCreation2((q2, r2) => {
            Image.create(CounterResource.BUTTON_ARROW_DOWN);
            Image.direction(this.counterDirection);
            Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
            Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
            Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
            Image.opacity(this.subOpacity);
          }, Image);
          this.observeComponentCreation2((d2, e2) => {
            Button.createWithLabel({
              type: ButtonType.Normal,
              stateEffect: this.subBtnStateEffect,
            });
            Button.accessibilityText({
              id: -1,
              type: 10003,
              params: ['sys.string.reduce_used_for_accessibility_text'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            Button.accessibilityDescription(
              this.value === this.min ? '' : this.reduceStr
            );
            Button.direction(this.counterDirection);
            Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
            Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
            Button.backgroundColor(Color.Transparent);
            Button.opacity(this.subOpacity);
            Button.enabled(this.subBtnEnabled);
            Button.onClick((l2) => {
              this.subValue();
              if (
                l2.source === SourceType.Mouse ||
                l2.source === SourceType.TouchScreen
              ) {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
              }
              try {
                let p2 = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'click',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(p2).then(() => {
                  console.log('Accessility subValue click send event');
                });
              } catch (m2) {
                let n2 = m2.code;
                let o2 = m2.message;
                console.log(
                  `Accessility subValue click faild error code:${n2} message:${o2}`
                );
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((k2) => {
              if (k2.repeat) {
                this.subValue();
              }
              this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
            });
            LongPressGesture.onActionEnd(() => {
              try {
                let j2 = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'common',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(j2).then(() => {
                  console.log('Accessility subValue longPress send event');
                });
              } catch (g2) {
                let h2 = g2.code;
                let i2 = g2.message;
                console.log(
                  `Accessility subValue longPress faild error code:${h2} message:${i2}`
                );
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((f2) => {
              this.onHoverDecrease && this.onHoverDecrease(f2);
            });
            Button.focusable(false);
            Button.onFocus(() => {
              this.subBtnFocusWidh =
                CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
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
      } else if (this.type === CounterType.INLINE_DATE) {
        this.ifElseBranchUpdateFunction(3, () => {
          this.observeComponentCreation2((b2, c2) => {
            Row.create();
            Row.direction(this.counterDirection);
            Row.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
            Row.borderWidth(CounterResource.COUNTER_BORDER_WIDTH);
            Row.borderColor(CounterResource.COUNTER_BORDER_COLOR);
            Row.borderRadius(CounterResource.COUNTER_INLINE_RADIUS);
            Row.clip(true);
          }, Row);
          this.observeComponentCreation2((z1, a2) => {
            Row.create();
            Row.direction(this.counterDirection);
            Row.width('92vp');
            Row.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
            Row.margin({
              start: LengthMetrics.vp(
                CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN
              ),
              end: LengthMetrics.vp(
                CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN
              ),
            });
          }, Row);
          this.observeComponentCreation2((s1, t1) => {
            TextInput.create({
              text: this.hasInputText1
                ? this.inputYear.toString()
                : this.getYear(),
              controller: this.controller1,
            });
            TextInput.accessibilityText(this.getDateYear());
            TextInput.accessibilityDescription({
              id: -1,
              type: 10003,
              params: ['sys.string.input_counter_double_click_description'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            TextInput.direction(this.counterDirection);
            TextInput.type(InputType.Number);
            TextInput.copyOption(CopyOptions.None);
            TextInput.fontSize(this.getTextInputFontSize());
            TextInput.fontWeight(FontWeight.Medium);
            TextInput.fontColor(
              this.hasFocusText1
                ? Color.White
                : CounterResource.COUNTER_TEXT_COLOR
            );
            TextInput.maxLength(5);
            TextInput.padding(0);
            TextInput.backgroundColor(
              this.hasFocusText1
                ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR
                : Color.Transparent
            );
            TextInput.width('38vp');
            TextInput.height('20vp');
            TextInput.borderRadius(0);
            TextInput.borderWidth(0);
            TextInput.key('DateTextInput1' + this.timeStamp.toString());
            TextInput.onKeyEvent((y1) => {
              this.focusCurrentText(FocusText.TEXT1);
              if (y1.keyCode === CounterConstant.KEYCODE_ESC) {
                this.resetFocusText();
                y1.stopPropagation();
              }
              if (
                y1.type === KeyType.Down &&
                y1.keyCode === CounterConstant.KEYCODE_DPAD_UP
              ) {
                this.addDate();
                y1.stopPropagation();
              }
              if (
                y1.type === KeyType.Down &&
                y1.keyCode === CounterConstant.KEYCODE_DPAD_DOWN
              ) {
                this.subDate();
                y1.stopPropagation();
              }
              if (
                y1.type === KeyType.Down &&
                y1.keyCode === CounterConstant.KEYCODE_MOVE_HOME
              ) {
                this.homeFocusText();
                y1.stopPropagation();
              }
              if (
                y1.type === KeyType.Down &&
                y1.keyCode === CounterConstant.KEYCODE_MOVE_END
              ) {
                this.endFocusText();
                y1.stopPropagation();
              }
              if (
                y1.type === KeyType.Down &&
                y1.keyCode === CounterConstant.KEYCODE_DPAD_LEFT
              ) {
                this.focusWithTarget(
                  'DateTextInput1' + this.timeStamp.toString()
                );
                y1.stopPropagation();
              }
              if (
                y1.type === KeyType.Down &&
                y1.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT
              ) {
                this.focusWithTarget(
                  'DateTextInput2' + this.timeStamp.toString()
                );
              }
            });
            TextInput.onChange((w1) => {
              if (w1.length !== 4) {
                this.hasInputText1 = true;
              }
              this.inputYear = Number(w1);
              if (w1.length === 5) {
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
              if (
                this.inputYear >= this.minYear &&
                this.inputYear <= this.maxYear
              ) {
                this.year = this.inputYear;
                this.updateDateEnableSate();
                this.updateDay();
              }
              if (w1.length === 4) {
                let x1 = new DateData(this.year, this.month, this.day);
                this.onDateChange?.(x1);
              }
            });
            TextInput.onSubmit((v1) => {
              if (this.timeoutID1 !== -1) {
                clearTimeout(this.timeoutID1);
                this.timeoutID1 = -1;
              }
              this.hasInputText1 = false;
              this.year -= 1;
              if (
                this.inputYear >= this.minYear &&
                this.inputYear <= this.maxYear
              ) {
                this.year = this.inputYear;
              } else {
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
            TextInput.onClick((u1) => {
              this.focusText = FocusText.TEXT1;
              this.hasFocusText1 = true;
              this.updateDateEnableSate();
              this.controller1.caretPosition(this.getYear().length);
            });
          }, TextInput);
          this.observeComponentCreation2((q1, r1) => {
            Text.create('/');
            Text.accessibilityLevel('no');
            Text.direction(this.counterDirection);
            Text.textAlign(TextAlign.Center);
            Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
            Text.maxFontScale(
              CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE
            );
            Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
            Text.width('8vp');
          }, Text);
          Text.pop();
          this.observeComponentCreation2((j1, k1) => {
            TextInput.create({
              text: this.hasInputText2
                ? this.inputMoon.toString()
                : this.convertNumberToString(this.month),
              controller: this.controller2,
            });
            TextInput.accessibilityText(this.getDateMonth());
            TextInput.accessibilityDescription({
              id: -1,
              type: 10003,
              params: ['sys.string.input_counter_double_click_description'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            TextInput.direction(this.counterDirection);
            TextInput.type(InputType.Number);
            TextInput.copyOption(CopyOptions.None);
            TextInput.fontSize(this.getTextInputFontSize());
            TextInput.fontWeight(FontWeight.Medium);
            TextInput.fontColor(
              this.hasFocusText2
                ? Color.White
                : CounterResource.COUNTER_TEXT_COLOR
            );
            TextInput.maxLength(3);
            TextInput.padding(0);
            TextInput.backgroundColor(
              this.hasFocusText2
                ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR
                : Color.Transparent
            );
            TextInput.width('19vp');
            TextInput.height('20vp');
            TextInput.borderRadius(0);
            TextInput.key('DateTextInput2' + this.timeStamp.toString());
            TextInput.onKeyEvent((p1) => {
              this.focusCurrentText(FocusText.TEXT2);
              if (p1.keyCode === CounterConstant.KEYCODE_ESC) {
                this.resetFocusText();
                p1.stopPropagation();
              }
              if (
                p1.type === KeyType.Down &&
                p1.keyCode === CounterConstant.KEYCODE_DPAD_DOWN
              ) {
                this.subDate();
                this.updateDay();
                p1.stopPropagation();
              }
              if (
                p1.type === KeyType.Down &&
                p1.keyCode === CounterConstant.KEYCODE_DPAD_UP
              ) {
                this.addDate();
                this.updateDay();
                p1.stopPropagation();
              }
              if (
                p1.type === KeyType.Down &&
                p1.keyCode === CounterConstant.KEYCODE_MOVE_HOME
              ) {
                this.homeFocusText();
                p1.stopPropagation();
              }
              if (
                p1.type === KeyType.Down &&
                p1.keyCode === CounterConstant.KEYCODE_MOVE_END
              ) {
                this.endFocusText();
                p1.stopPropagation();
              }
              if (
                p1.type === KeyType.Down &&
                p1.keyCode === CounterConstant.KEYCODE_DPAD_LEFT
              ) {
                this.focusWithTarget(
                  'DateTextInput1' + this.timeStamp.toString()
                );
              }
              if (
                p1.type === KeyType.Down &&
                p1.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT
              ) {
                this.focusWithTarget(
                  'DateTextInput3' + this.timeStamp.toString()
                );
              }
              if (
                p1.type === KeyType.Down &&
                p1.keyCode === CounterConstant.KEYCODE_TAB
              ) {
                p1.stopPropagation();
                this.focusWithTarget(
                  'DateTextInput1' + this.timeStamp.toString()
                );
              }
            });
            TextInput.onChange((n1) => {
              this.inputMoon = Number(n1);
              if (n1.length !== 2) {
                this.hasInputText2 = true;
              }
              if (n1.length === 3) {
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
                } else {
                  this.month += 1;
                  this.inputMoon = this.month;
                }
                this.updateDay();
              }, 1000);
              if (n1.length === 2) {
                this.hasInputText2 = false;
                this.month -= 1;
                if (this.inputMoon >= 1 && this.inputMoon <= 12) {
                  this.month = this.inputMoon;
                  let o1 = new DateData(this.year, this.month, this.day);
                  this.onDateChange?.(o1);
                } else {
                  this.month += 1;
                  this.inputMoon = this.month;
                }
                this.updateDay();
              }
            });
            TextInput.onSubmit((m1) => {
              if (this.timeoutID2 !== -1) {
                clearTimeout(this.timeoutID2);
                this.timeoutID2 = -1;
              }
              this.hasInputText2 = false;
              this.month -= 1;
              if (this.inputMoon >= 1 && this.inputMoon <= 12) {
                this.month = this.inputMoon;
                this.updateDay();
              } else {
                this.month += 1;
              }
            });
            TextInput.focusOnTouch(true);
            TextInput.tabIndex(-1);
            TextInput.focusable(true);
            TextInput.onFocus(() => {
              this.focusText = FocusText.TEXT2;
              this.hasFocusText2 = true;
              this.controller2.caretPosition(
                this.convertNumberToString(this.month).length
              );
            });
            TextInput.onBlur(() => {
              this.focusText = FocusText.NONE;
              this.hasFocusText2 = false;
            });
            TextInput.onClick((l1) => {
              this.focusText = FocusText.TEXT2;
              this.hasFocusText2 = true;
              this.controller2.caretPosition(
                this.convertNumberToString(this.month).length
              );
            });
          }, TextInput);
          this.observeComponentCreation2((h1, i1) => {
            Text.create('/');
            Text.accessibilityLevel('no');
            Text.direction(this.counterDirection);
            Text.textAlign(TextAlign.Center);
            Text.fontSize(CounterResource.COUNTER_NUMBER_SIZE);
            Text.maxFontScale(
              CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE
            );
            Text.fontColor(CounterResource.COUNTER_TEXT_COLOR);
            Text.width('8vp');
          }, Text);
          Text.pop();
          this.observeComponentCreation2((a1, b1) => {
            TextInput.create({
              text: this.hasInputText3
                ? this.inputDay.toString()
                : this.convertNumberToString(this.day),
              controller: this.controller3,
            });
            TextInput.accessibilityText(this.getDateDay());
            TextInput.accessibilityDescription({
              id: -1,
              type: 10003,
              params: ['sys.string.input_counter_double_click_description'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            TextInput.direction(this.counterDirection);
            TextInput.type(InputType.Number);
            TextInput.copyOption(CopyOptions.None);
            TextInput.fontSize(this.getTextInputFontSize());
            TextInput.fontWeight(FontWeight.Medium);
            TextInput.fontColor(
              this.hasFocusText3
                ? Color.White
                : CounterResource.COUNTER_TEXT_COLOR
            );
            TextInput.maxLength(3);
            TextInput.padding(0);
            TextInput.backgroundColor(
              this.hasFocusText3
                ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR
                : Color.Transparent
            );
            TextInput.width('19vp');
            TextInput.height('20vp');
            TextInput.borderRadius(0);
            TextInput.key('DateTextInput3' + this.timeStamp.toString());
            TextInput.onKeyEvent((g1) => {
              this.focusCurrentText(FocusText.TEXT3);
              if (g1.keyCode === CounterConstant.KEYCODE_ESC) {
                this.resetFocusText();
                g1.stopPropagation();
              }
              if (
                g1.type === KeyType.Down &&
                g1.keyCode === CounterConstant.KEYCODE_DPAD_DOWN
              ) {
                this.subDate();
                g1.stopPropagation();
              }
              if (
                g1.type === KeyType.Down &&
                g1.keyCode === CounterConstant.KEYCODE_DPAD_UP
              ) {
                this.addDate();
                g1.stopPropagation();
              }
              if (
                g1.type === KeyType.Down &&
                g1.keyCode === CounterConstant.KEYCODE_MOVE_HOME
              ) {
                this.homeFocusText();
                g1.stopPropagation();
              }
              if (
                g1.type === KeyType.Down &&
                g1.keyCode === CounterConstant.KEYCODE_MOVE_END
              ) {
                this.endFocusText();
                g1.stopPropagation();
              }
              if (
                g1.type === KeyType.Down &&
                g1.keyCode === CounterConstant.KEYCODE_DPAD_LEFT
              ) {
                this.focusWithTarget(
                  'DateTextInput2' + this.timeStamp.toString()
                );
              }
              if (
                g1.type === KeyType.Down &&
                g1.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT
              ) {
                this.focusWithTarget(
                  'DateTextInput3' + this.timeStamp.toString()
                );
                g1.stopPropagation();
              }
              if (
                g1.type === KeyType.Down &&
                g1.keyCode === CounterConstant.KEYCODE_TAB
              ) {
                g1.stopPropagation();
                this.focusWithTarget(
                  'DateTextInput1' + this.timeStamp.toString()
                );
              }
            });
            TextInput.onChange((e1) => {
              this.inputDay = Number(e1);
              if (e1.length !== 2) {
                this.hasInputText3 = true;
              }
              if (e1.length === 3) {
                this.inputDay = this.inputDay % 10;
              }
              if (this.timeoutID3 !== -1) {
                clearTimeout(this.timeoutID3);
                this.timeoutID3 = -1;
              }
              this.timeoutID3 = setTimeout(() => {
                this.hasInputText3 = false;
                this.day -= 1;
                if (
                  this.inputDay >= 1 &&
                  this.inputDay <= this.getDayNumber()
                ) {
                  this.day = this.inputDay;
                } else {
                  this.day += 1;
                  this.inputDay = this.day;
                }
              }, 1000);
              if (e1.length === 2) {
                this.hasInputText3 = false;
                this.day -= 1;
                if (
                  this.inputDay >= 1 &&
                  this.inputDay <= this.getDayNumber()
                ) {
                  this.day = this.inputDay;
                  let f1 = new DateData(this.year, this.month, this.day);
                  this.onDateChange?.(f1);
                } else {
                  this.day += 1;
                  this.inputDay = this.day;
                }
              }
            });
            TextInput.onSubmit((d1) => {
              if (this.timeoutID3 !== -1) {
                clearTimeout(this.timeoutID3);
                this.timeoutID3 = -1;
              }
              this.hasInputText3 = false;
              this.day -= 1;
              if (this.inputDay >= 1 && this.inputDay <= this.getDayNumber()) {
                this.day = this.inputDay;
              } else {
                this.day += 1;
              }
            });
            TextInput.tabIndex(-2);
            TextInput.focusOnTouch(true);
            TextInput.focusable(true);
            TextInput.onFocus(() => {
              this.focusText = FocusText.TEXT3;
              this.hasFocusText3 = true;
              this.controller3.caretPosition(
                this.convertNumberToString(this.day).length
              );
            });
            TextInput.onBlur(() => {
              this.focusText = FocusText.NONE;
              this.hasFocusText3 = false;
            });
            TextInput.onClick((c1) => {
              this.focusText = FocusText.TEXT3;
              this.hasFocusText3 = true;
              this.controller3.caretPosition(
                this.convertNumberToString(this.day).length
              );
            });
          }, TextInput);
          Row.pop();
          this.observeComponentCreation2((y, z) => {
            Column.create();
            Column.direction(this.counterDirection);
            Column.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
            Column.height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT);
            Column.borderWidth({
              start: LengthMetrics.vp(
                CounterResource.COUNTER_BORDER_WIDTH_NUMBER
              ),
            });
            Column.borderColor(CounterResource.COUNTER_BORDER_COLOR);
          }, Column);
          this.observeComponentCreation2((w, x) => {
            Stack.create();
            Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
            Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
            Stack.padding({ top: '1vp' });
            Stack.borderWidth({ bottom: '1vp' });
            Stack.borderColor(CounterResource.COUNTER_BORDER_COLOR);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((u, v) => {
            Rect.create();
            Rect.direction(this.counterDirection);
            Rect.width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH);
            Rect.height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT);
            Rect.radius([
              ['0vp', '0vp'],
              [
                CounterResource.COUNTER_INLINE_RADIUS,
                CounterResource.COUNTER_INLINE_RADIUS,
              ],
              ['0vp', '0vp'],
              ['0vp', '0vp'],
            ]);
            Rect.strokeWidth(this.addBtnFocusWidh);
            Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
            Rect.margin({ end: LengthMetrics.vp(1) });
            Rect.fillOpacity(0);
          }, Rect);
          this.observeComponentCreation2((s, t) => {
            Image.create(CounterResource.BUTTON_ARROW_UP);
            Image.direction(this.counterDirection);
            Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
            Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
            Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
            Image.opacity(this.addOpacity);
          }, Image);
          this.observeComponentCreation2((n, o) => {
            Button.createWithLabel({
              type: ButtonType.Normal,
              stateEffect: this.addBtnStateEffect,
            });
            Button.accessibilityText({
              id: -1,
              type: 10003,
              params: ['sys.string.increase_used_for_accessibility_text'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            Button.accessibilityDescription({
              id: -1,
              type: 10003,
              params: ['sys.string.increase_counter_double_click_description'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            Button.direction(this.counterDirection);
            Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
            Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
            Button.backgroundColor(Color.Transparent);
            Button.opacity(this.addOpacity);
            Button.enabled(this.addBtnEnabled);
            Button.onClick((r) => {
              this.accessibilityBroadcastAddDate();
              if (
                r.source === SourceType.Mouse ||
                r.source === SourceType.TouchScreen
              ) {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((q) => {
              if (q.repeat) {
                this.addDate();
              }
              this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
            });
            LongPressGesture.onActionEnd(() => {
              this.accessibilityBroadcastAddDate();
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((p) => {
              this.onHoverIncrease && this.onHoverIncrease(p);
            });
            Button.focusable(false);
            Button.onFocus(() => {
              this.addBtnFocusWidh =
                CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
              this.onFocusIncrease && this.onFocusIncrease();
            });
            Button.onBlur(() => {
              this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
              this.onBlurIncrease && this.onBlurIncrease();
            });
          }, Button);
          Button.pop();
          Stack.pop();
          this.observeComponentCreation2((l, m) => {
            Stack.create();
            Stack.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
            Stack.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((j, k) => {
            Rect.create();
            Rect.direction(this.counterDirection);
            Rect.width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH);
            Rect.height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT);
            Rect.radius([
              ['0vp', '0vp'],
              ['0vp', '0vp'],
              [
                CounterResource.COUNTER_INLINE_RADIUS,
                CounterResource.COUNTER_INLINE_RADIUS,
              ],
              ['0vp', '0vp'],
            ]);
            Rect.strokeWidth(this.subBtnFocusWidh);
            Rect.stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR);
            Rect.margin({
              top: LengthMetrics.vp(1),
              end: LengthMetrics.vp(1),
              bottom: LengthMetrics.vp(2),
            });
            Rect.fillOpacity(0);
          }, Rect);
          this.observeComponentCreation2((h, i) => {
            Image.create(CounterResource.BUTTON_ARROW_DOWN);
            Image.direction(this.counterDirection);
            Image.width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH);
            Image.height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT);
            Image.fillColor(CounterResource.BUTTON_ICON_COLOR);
            Image.opacity(this.subOpacity);
          }, Image);
          this.observeComponentCreation2((c, d) => {
            Button.createWithLabel({
              type: ButtonType.Normal,
              stateEffect: this.subBtnStateEffect,
            });
            Button.accessibilityText({
              id: -1,
              type: 10003,
              params: ['sys.string.reduce_used_for_accessibility_text'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            Button.accessibilityDescription({
              id: -1,
              type: 10003,
              params: ['sys.string.reduce_counter_double_click_description'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            Button.direction(this.counterDirection);
            Button.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH);
            Button.height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT);
            Button.backgroundColor(Color.Transparent);
            Button.opacity(this.subOpacity);
            Button.enabled(this.subBtnEnabled);
            Button.onClick((g) => {
              this.accessibilityBroadcastSubDate();
              if (
                g.source === SourceType.Mouse ||
                g.source === SourceType.TouchScreen
              ) {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((f) => {
              if (f.repeat) {
                this.subDate();
              }
              this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
            });
            LongPressGesture.onActionEnd(() => {
              this.accessibilityBroadcastSubDate();
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((e) => {
              this.onHoverDecrease && this.onHoverDecrease(e);
            });
            Button.focusable(false);
            Button.onFocus(() => {
              this.subBtnFocusWidh =
                CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
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
      } else {
        this.ifElseBranchUpdateFunction(4, () => {});
      }
    }, If);
    If.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export default {
  CommonOptions,
  NumberStyleOptions,
  InlineStyleOptions,
  DateStyleOptions,
  CounterType,
  DateData,
  CounterOptions,
  CounterComponent,
};
