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

let locale = new intl.Locale();
let i = locale.toString();
let j = new Map([
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
export var CounterType;
(function (CounterType) {
  CounterType[(CounterType['LIST'] = 0)] = 'LIST';
  CounterType[(CounterType['COMPACT'] = 1)] = 'COMPACT';
  CounterType[(CounterType['INLINE'] = 2)] = 'INLINE';
  CounterType[(CounterType['INLINE_DATE'] = 3)] = 'INLINE_DATE';
})(CounterType || (CounterType = {}));
var m;
(function (o2) {
  o2[(o2['NONE'] = 0)] = 'NONE';
  o2[(o2['TEXT1'] = 1)] = 'TEXT1';
  o2[(o2['TEXT2'] = 2)] = 'TEXT2';
  o2[(o2['TEXT3'] = 3)] = 'TEXT3';
})(m || (m = {}));
export class o {}
export class t extends o {}
export class u extends t {}
export class DateData {
  constructor(year, month, day) {
    this.year = year;
    this.month = month;
    this.day = day;
  }
  toString() {
    let date = this.year.toString() + '-';
    let month =
      this.month < 10 ? '0' + this.month.toString() : this.month.toString();
    date += month + '-';
    let day = this.day < 10 ? '0' + this.day.toString() : this.day.toString();
    date += day;
    return date;
  }
}
export class a1 extends o {}
export class CounterOptions {
  constructor() {
    this.type = CounterType.LIST;
  }
}
class b1 {}
b1.q2 = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_button_normal'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.s2 = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_primary'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.t2 = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_focused_outline'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.u2 = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_text_primary'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.v2 = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_component_normal'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.w2 = {
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_add'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.z2 = {
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_minus'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.a3 = {
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_arrow_up'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.b3 = {
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_arrow_down'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.c3 = '2vp';
b1.d3 = '0vp';
b1.e3 = 1;
b1.f3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_text_size_body1'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.g3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_text_size_body1'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.h3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_text_size_body2'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.i3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_text_size_body1'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.j3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_default_padding_start'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.l3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_default_padding_end'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.m3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.button_icon_size'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.n3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.container_height'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.q3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.border_width'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.r3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.button_size'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.s3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.container_radius'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.t3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.button_container_margin'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
b1.u3 = 12;
b1.v3 = '48vp';
b1.w3 = '20vp';
b1.x3 = '32vp';
b1.y3 = '16vp';
b1.z3 = '8vp';
b1.a4 = 8;
b1.b4 = '30vp';
b1.c4 = '15vp';
b1.d4 = '-8vp';
b1.e4 = '-8vp';
b1.f4 = '12vp';
b1.g4 = '10vp';
b1.h4 = 10;
b1.i4 = '8vp';
b1.j4 = '22vp';
b1.l4 = '11vp';
b1.m4 = '24vp';
b1.n4 = '12vp';
b1.o4 = '12vp';
b1.q4 = '32vp';
b1.r4 = '32vp';
b1.s4 = '16vp';
b1.t4 = '8vp';
b1.u4 = '28vp';
b1.v4 = '13.5vp';
b1.w4 = 12;
b1.x4 = 12;
b1.y4 = 1;
b1.z4 = 0.4;
b1.a5 = 2;
b1.b5 = 1;
class c1 {}
c1.c5 = 5000;
c1.d5 = 1;
c1.e5 = 1;
c1.f5 = 1;
c1.g5 = 1;
c1.h5 = 10;
c1.i5 = 1;
c1.j5 = 12;
c1.k5 = 1;
c1.KEYCODE_DPAD_UP = 2012;
c1.KEYCODE_DPAD_DOWN = 2013;
c1.KEYCODE_DPAD_LEFT = 2014;
c1.KEYCODE_DPAD_RIGHT = 2015;
c1.KEYCODE_MOVE_HOME = 2081;
c1.KEYCODE_MOVE_END = 2082;
c1.KEYCODE_TAB = 2049;
c1.l5 = 2070;
c1.m5 = 0;
c1.n5 = 999;
c1.o5 = 1;
c1.p5 = 2;
c1.q5 = 3;
c1.r5 = 4;
c1.s5 = 5;
c1.t5 = 6;
c1.u5 = 7;
c1.v5 = 8;
c1.w5 = 9;
c1.x5 = 10;
c1.y5 = 11;
c1.z5 = 12;
c1.a6 = 31;
c1.b6 = 30;
c1.c6 = 28;
c1.d6 = 29;
c1.e6 = 4;
c1.f6 = 100;
c1.g6 = 400;
export class CounterComponent extends ViewPU {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda = undefined,
    extraInfo
  ) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.__options = new SynchedPropertyObjectOneWayPU(
      params.options,
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
    this.__step = new ObservedPropertySimplePU(c1.g5, this, 'step');
    this.__inputValue = new ObservedPropertySimplePU('0', this, 'inputValue');
    this.__inputYear = new ObservedPropertySimplePU(c1.d5, this, 'inputYear');
    this.__inputMoon = new ObservedPropertySimplePU(0, this, 'inputMoon');
    this.__inputDay = new ObservedPropertySimplePU(0, this, 'inputDay');
    this.__inputHour = new ObservedPropertySimplePU(0, this, 'inputHour');
    this.__inputMinute = new ObservedPropertySimplePU(0, this, 'inputMinute');
    this.__inputSecond = new ObservedPropertySimplePU(0, this, 'inputSecond');
    this.__subOpacity = new ObservedPropertySimplePU(b1.y4, this, 'subOpacity');
    this.__addOpacity = new ObservedPropertySimplePU(b1.y4, this, 'addOpacity');
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
    this.__focusText = new ObservedPropertySimplePU(m.NONE, this, 'focusText');
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
    this.__min = new ObservedPropertySimplePU(c1.m5, this, 'min');
    this.__max = new ObservedPropertySimplePU(c1.n5, this, 'max');
    this.maxYear = c1.c5;
    this.minYear = c1.d5;
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
    this.numberStyleOptions = new u();
    this.dateStyleOptions = new a1();
    this.inlineStyleOptions = new t();
    this.timeStamp = 0;
    this.hasTextWidth = false;
    this.controller1 = new TextInputController();
    this.controller2 = new TextInputController();
    this.controller3 = new TextInputController();
    this.initFlag = true;
    this.increaseStr = getContext().resourceManager.getStringSync(125834852);
    this.reduceStr = getContext().resourceManager.getStringSync(125834853);
    this.setInitiallyProvidedValue(params);
    this.declareWatch('options', this.onOptionsChange);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    if (params.type !== undefined) {
      this.type = params.type;
    }
    if (params.counterDirection !== undefined) {
      this.counterDirection = params.counterDirection;
    }
    if (params.choverEffect !== undefined) {
      this.choverEffect = params.choverEffect;
    }
    if (params.focusEnable !== undefined) {
      this.focusEnable = params.focusEnable;
    }
    if (params.step !== undefined) {
      this.step = params.step;
    }
    if (params.inputValue !== undefined) {
      this.inputValue = params.inputValue;
    }
    if (params.inputYear !== undefined) {
      this.inputYear = params.inputYear;
    }
    if (params.inputMoon !== undefined) {
      this.inputMoon = params.inputMoon;
    }
    if (params.inputDay !== undefined) {
      this.inputDay = params.inputDay;
    }
    if (params.inputHour !== undefined) {
      this.inputHour = params.inputHour;
    }
    if (params.inputMinute !== undefined) {
      this.inputMinute = params.inputMinute;
    }
    if (params.inputSecond !== undefined) {
      this.inputSecond = params.inputSecond;
    }
    if (params.subOpacity !== undefined) {
      this.subOpacity = params.subOpacity;
    }
    if (params.addOpacity !== undefined) {
      this.addOpacity = params.addOpacity;
    }
    if (params.subBtnStateEffect !== undefined) {
      this.subBtnStateEffect = params.subBtnStateEffect;
    }
    if (params.addBtnStateEffect !== undefined) {
      this.addBtnStateEffect = params.addBtnStateEffect;
    }
    if (params.focusText !== undefined) {
      this.focusText = params.focusText;
    }
    if (params.hasFocusText1 !== undefined) {
      this.hasFocusText1 = params.hasFocusText1;
    }
    if (params.hasFocusText2 !== undefined) {
      this.hasFocusText2 = params.hasFocusText2;
    }
    if (params.hasFocusText3 !== undefined) {
      this.hasFocusText3 = params.hasFocusText3;
    }
    if (params.subBtnFocusWidh !== undefined) {
      this.subBtnFocusWidh = params.subBtnFocusWidh;
    }
    if (params.addBtnFocusWidh !== undefined) {
      this.addBtnFocusWidh = params.addBtnFocusWidh;
    }
    if (params.value !== undefined) {
      this.value = params.value;
    }
    if (params.year !== undefined) {
      this.year = params.year;
    }
    if (params.month !== undefined) {
      this.month = params.month;
    }
    if (params.day !== undefined) {
      this.day = params.day;
    }
    if (params.hour !== undefined) {
      this.hour = params.hour;
    }
    if (params.minute !== undefined) {
      this.minute = params.minute;
    }
    if (params.second !== undefined) {
      this.second = params.second;
    }
    if (params.subBtnEnabled !== undefined) {
      this.subBtnEnabled = params.subBtnEnabled;
    }
    if (params.addBtnEnabled !== undefined) {
      this.addBtnEnabled = params.addBtnEnabled;
    }
    if (params.hasInputText1 !== undefined) {
      this.hasInputText1 = params.hasInputText1;
    }
    if (params.hasInputText2 !== undefined) {
      this.hasInputText2 = params.hasInputText2;
    }
    if (params.hasInputText3 !== undefined) {
      this.hasInputText3 = params.hasInputText3;
    }
    if (params.textWidth !== undefined) {
      this.textWidth = params.textWidth;
    }
    if (params.min !== undefined) {
      this.min = params.min;
    }
    if (params.max !== undefined) {
      this.max = params.max;
    }
    if (params.maxYear !== undefined) {
      this.maxYear = params.maxYear;
    }
    if (params.minYear !== undefined) {
      this.minYear = params.minYear;
    }
    if (params.numberStrList !== undefined) {
      this.numberStrList = params.numberStrList;
    }
    if (params.onHoverIncrease !== undefined) {
      this.onHoverIncrease = params.onHoverIncrease;
    }
    if (params.onHoverDecrease !== undefined) {
      this.onHoverDecrease = params.onHoverDecrease;
    }
    if (params.onFocusIncrease !== undefined) {
      this.onFocusIncrease = params.onFocusIncrease;
    }
    if (params.onFocusDecrease !== undefined) {
      this.onFocusDecrease = params.onFocusDecrease;
    }
    if (params.onBlurIncrease !== undefined) {
      this.onBlurIncrease = params.onBlurIncrease;
    }
    if (params.onBlurDecrease !== undefined) {
      this.onBlurDecrease = params.onBlurDecrease;
    }
    if (params.onChange !== undefined) {
      this.onChange = params.onChange;
    }
    if (params.onDateChange !== undefined) {
      this.onDateChange = params.onDateChange;
    }
    if (params.timeoutID1 !== undefined) {
      this.timeoutID1 = params.timeoutID1;
    }
    if (params.timeoutID2 !== undefined) {
      this.timeoutID2 = params.timeoutID2;
    }
    if (params.timeoutID3 !== undefined) {
      this.timeoutID3 = params.timeoutID3;
    }
    if (params.numberStyleOptions !== undefined) {
      this.numberStyleOptions = params.numberStyleOptions;
    }
    if (params.dateStyleOptions !== undefined) {
      this.dateStyleOptions = params.dateStyleOptions;
    }
    if (params.inlineStyleOptions !== undefined) {
      this.inlineStyleOptions = params.inlineStyleOptions;
    }
    if (params.timeStamp !== undefined) {
      this.timeStamp = params.timeStamp;
    }
    if (params.hasTextWidth !== undefined) {
      this.hasTextWidth = params.hasTextWidth;
    }
    if (params.controller1 !== undefined) {
      this.controller1 = params.controller1;
    }
    if (params.controller2 !== undefined) {
      this.controller2 = params.controller2;
    }
    if (params.controller3 !== undefined) {
      this.controller3 = params.controller3;
    }
    if (params.initFlag !== undefined) {
      this.initFlag = params.initFlag;
    }
    if (params.increaseStr !== undefined) {
      this.increaseStr = params.increaseStr;
    }
    if (params.reduceStr !== undefined) {
      this.reduceStr = params.reduceStr;
    }
  }
  updateStateVars(params) {
    this.__options.reset(params.options);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__options.purgeDependencyOnElmtId(rmElmtId);
    this.__type.purgeDependencyOnElmtId(rmElmtId);
    this.__counterDirection.purgeDependencyOnElmtId(rmElmtId);
    this.__choverEffect.purgeDependencyOnElmtId(rmElmtId);
    this.__focusEnable.purgeDependencyOnElmtId(rmElmtId);
    this.__step.purgeDependencyOnElmtId(rmElmtId);
    this.__inputValue.purgeDependencyOnElmtId(rmElmtId);
    this.__inputYear.purgeDependencyOnElmtId(rmElmtId);
    this.__inputMoon.purgeDependencyOnElmtId(rmElmtId);
    this.__inputDay.purgeDependencyOnElmtId(rmElmtId);
    this.__inputHour.purgeDependencyOnElmtId(rmElmtId);
    this.__inputMinute.purgeDependencyOnElmtId(rmElmtId);
    this.__inputSecond.purgeDependencyOnElmtId(rmElmtId);
    this.__subOpacity.purgeDependencyOnElmtId(rmElmtId);
    this.__addOpacity.purgeDependencyOnElmtId(rmElmtId);
    this.__subBtnStateEffect.purgeDependencyOnElmtId(rmElmtId);
    this.__addBtnStateEffect.purgeDependencyOnElmtId(rmElmtId);
    this.__focusText.purgeDependencyOnElmtId(rmElmtId);
    this.__hasFocusText1.purgeDependencyOnElmtId(rmElmtId);
    this.__hasFocusText2.purgeDependencyOnElmtId(rmElmtId);
    this.__hasFocusText3.purgeDependencyOnElmtId(rmElmtId);
    this.__subBtnFocusWidh.purgeDependencyOnElmtId(rmElmtId);
    this.__addBtnFocusWidh.purgeDependencyOnElmtId(rmElmtId);
    this.__value.purgeDependencyOnElmtId(rmElmtId);
    this.__year.purgeDependencyOnElmtId(rmElmtId);
    this.__month.purgeDependencyOnElmtId(rmElmtId);
    this.__day.purgeDependencyOnElmtId(rmElmtId);
    this.__hour.purgeDependencyOnElmtId(rmElmtId);
    this.__minute.purgeDependencyOnElmtId(rmElmtId);
    this.__second.purgeDependencyOnElmtId(rmElmtId);
    this.__subBtnEnabled.purgeDependencyOnElmtId(rmElmtId);
    this.__addBtnEnabled.purgeDependencyOnElmtId(rmElmtId);
    this.__hasInputText1.purgeDependencyOnElmtId(rmElmtId);
    this.__hasInputText2.purgeDependencyOnElmtId(rmElmtId);
    this.__hasInputText3.purgeDependencyOnElmtId(rmElmtId);
    this.__textWidth.purgeDependencyOnElmtId(rmElmtId);
    this.__min.purgeDependencyOnElmtId(rmElmtId);
    this.__max.purgeDependencyOnElmtId(rmElmtId);
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
  set options(newValue) {
    this.__options.set(newValue);
  }
  get type() {
    return this.__type.get();
  }
  set type(newValue) {
    this.__type.set(newValue);
  }
  get counterDirection() {
    return this.__counterDirection.get();
  }
  set counterDirection(newValue) {
    this.__counterDirection.set(newValue);
  }
  get choverEffect() {
    return this.__choverEffect.get();
  }
  set choverEffect(newValue) {
    this.__choverEffect.set(newValue);
  }
  get focusEnable() {
    return this.__focusEnable.get();
  }
  set focusEnable(newValue) {
    this.__focusEnable.set(newValue);
  }
  get step() {
    return this.__step.get();
  }
  set step(newValue) {
    this.__step.set(newValue);
  }
  get inputValue() {
    return this.__inputValue.get();
  }
  set inputValue(newValue) {
    this.__inputValue.set(newValue);
  }
  get inputYear() {
    return this.__inputYear.get();
  }
  set inputYear(newValue) {
    this.__inputYear.set(newValue);
  }
  get inputMoon() {
    return this.__inputMoon.get();
  }
  set inputMoon(newValue) {
    this.__inputMoon.set(newValue);
  }
  get inputDay() {
    return this.__inputDay.get();
  }
  set inputDay(newValue) {
    this.__inputDay.set(newValue);
  }
  get inputHour() {
    return this.__inputHour.get();
  }
  set inputHour(newValue) {
    this.__inputHour.set(newValue);
  }
  get inputMinute() {
    return this.__inputMinute.get();
  }
  set inputMinute(newValue) {
    this.__inputMinute.set(newValue);
  }
  get inputSecond() {
    return this.__inputSecond.get();
  }
  set inputSecond(newValue) {
    this.__inputSecond.set(newValue);
  }
  get subOpacity() {
    return this.__subOpacity.get();
  }
  set subOpacity(newValue) {
    this.__subOpacity.set(newValue);
  }
  get addOpacity() {
    return this.__addOpacity.get();
  }
  set addOpacity(newValue) {
    this.__addOpacity.set(newValue);
  }
  get subBtnStateEffect() {
    return this.__subBtnStateEffect.get();
  }
  set subBtnStateEffect(newValue) {
    this.__subBtnStateEffect.set(newValue);
  }
  get addBtnStateEffect() {
    return this.__addBtnStateEffect.get();
  }
  set addBtnStateEffect(newValue) {
    this.__addBtnStateEffect.set(newValue);
  }
  get focusText() {
    return this.__focusText.get();
  }
  set focusText(newValue) {
    this.__focusText.set(newValue);
  }
  get hasFocusText1() {
    return this.__hasFocusText1.get();
  }
  set hasFocusText1(newValue) {
    this.__hasFocusText1.set(newValue);
  }
  get hasFocusText2() {
    return this.__hasFocusText2.get();
  }
  set hasFocusText2(newValue) {
    this.__hasFocusText2.set(newValue);
  }
  get hasFocusText3() {
    return this.__hasFocusText3.get();
  }
  set hasFocusText3(newValue) {
    this.__hasFocusText3.set(newValue);
  }
  get subBtnFocusWidh() {
    return this.__subBtnFocusWidh.get();
  }
  set subBtnFocusWidh(newValue) {
    this.__subBtnFocusWidh.set(newValue);
  }
  get addBtnFocusWidh() {
    return this.__addBtnFocusWidh.get();
  }
  set addBtnFocusWidh(newValue) {
    this.__addBtnFocusWidh.set(newValue);
  }
  get value() {
    return this.__value.get();
  }
  set value(newValue) {
    this.__value.set(newValue);
  }
  get year() {
    return this.__year.get();
  }
  set year(newValue) {
    this.__year.set(newValue);
  }
  get month() {
    return this.__month.get();
  }
  set month(newValue) {
    this.__month.set(newValue);
  }
  get day() {
    return this.__day.get();
  }
  set day(newValue) {
    this.__day.set(newValue);
  }
  get hour() {
    return this.__hour.get();
  }
  set hour(newValue) {
    this.__hour.set(newValue);
  }
  get minute() {
    return this.__minute.get();
  }
  set minute(newValue) {
    this.__minute.set(newValue);
  }
  get second() {
    return this.__second.get();
  }
  set second(newValue) {
    this.__second.set(newValue);
  }
  get subBtnEnabled() {
    return this.__subBtnEnabled.get();
  }
  set subBtnEnabled(newValue) {
    this.__subBtnEnabled.set(newValue);
  }
  get addBtnEnabled() {
    return this.__addBtnEnabled.get();
  }
  set addBtnEnabled(newValue) {
    this.__addBtnEnabled.set(newValue);
  }
  get hasInputText1() {
    return this.__hasInputText1.get();
  }
  set hasInputText1(newValue) {
    this.__hasInputText1.set(newValue);
  }
  get hasInputText2() {
    return this.__hasInputText2.get();
  }
  set hasInputText2(newValue) {
    this.__hasInputText2.set(newValue);
  }
  get hasInputText3() {
    return this.__hasInputText3.get();
  }
  set hasInputText3(newValue) {
    this.__hasInputText3.set(newValue);
  }
  get textWidth() {
    return this.__textWidth.get();
  }
  set textWidth(newValue) {
    this.__textWidth.set(newValue);
  }
  get min() {
    return this.__min.get();
  }
  set min(newValue) {
    this.__min.set(newValue);
  }
  get max() {
    return this.__max.get();
  }
  set max(newValue) {
    this.__max.set(newValue);
  }
  getTextInputFontSize() {
    let fontSize = this.resourceToVp(b1.i3);
    let uiContext = this.getUIContext();
    let fontSizeScale = uiContext.getHostContext()?.config?.fontSizeScale ?? 1;
    if (fontSizeScale < 1) {
      return fontSize + 'fp';
    } else {
      return fontSize + 'vp';
    }
  }
  getDateYear() {
    let date = new Date(this.year, this.month - 1, this.day);
    let m2 = new intl.DateTimeFormat(i, { year: 'numeric' });
    let n2 = m2.format(date);
    return n2;
  }
  getDateMonth() {
    let date = new Date(this.year, this.month - 1, this.day);
    let k2 = new intl.DateTimeFormat(i, { month: 'long' });
    let l2 = k2.format(date);
    return l2;
  }
  convertNumberToString(value) {
    if (value >= 0 && value < c1.h5) {
      return this.numberStrList[value];
    } else {
      return value.toString();
    }
  }
  aboutToAppear() {
    let dateTime = new Date();
    this.timeStamp = dateTime.getTime();
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
      this.year = c1.d5;
    }
    if (
      this.dateStyleOptions.month !== undefined &&
      this.dateStyleOptions.month <= c1.j5 &&
      this.dateStyleOptions.month >= c1.i5
    ) {
      if (this.month === 0) {
        this.month = this.dateStyleOptions.month;
      }
    } else {
      this.month = c1.e5;
    }
    if (
      this.dateStyleOptions.day !== undefined &&
      this.dateStyleOptions.day <= this.getDayNumber() &&
      this.dateStyleOptions.day >= c1.k5
    ) {
      if (this.day === 0) {
        this.day = this.dateStyleOptions.day;
      }
    } else {
      this.day = c1.f5;
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
      let options = this.options.dateOptions;
      if (options !== undefined) {
        options.year = options.year ? options.year : c1.d5;
        options.month = options.month ? options.month : c1.i5;
        options.day = options.day ? options.day : c1.k5;
        this.dateStyleOptions = options;
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
      this.addOpacity = b1.y4;
      this.addBtnEnabled = true;
    }
    if (this.value <= this.min) {
      this.value = this.min;
      this.subOpacity = b1.z4;
      this.subBtnStateEffect = false;
      this.subBtnEnabled = false;
    } else {
      if (this.subOpacity === b1.z4) {
        this.subOpacity = b1.y4;
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
      if (this.focusText === m.NONE) {
        this.focusText = m.TEXT1;
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
      this.subOpacity = b1.y4;
      this.subBtnEnabled = true;
    }
    if (this.value >= this.max) {
      this.value = this.max;
      this.addOpacity = b1.z4;
      this.addBtnStateEffect = false;
      this.addBtnEnabled = false;
    } else {
      if (this.addOpacity === b1.z4) {
        this.addOpacity = b1.y4;
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
      case c1.o5:
      case c1.q5:
      case c1.s5:
      case c1.u5:
      case c1.v5:
      case c1.x5:
      case c1.z5:
        return c1.a6;
        break;
      case c1.r5:
      case c1.t5:
      case c1.w5:
      case c1.y5:
        return c1.b6;
        break;
      case c1.p5:
        if (
          (this.year % c1.e6 === 0 && this.year % c1.f6 !== 0) ||
          this.year % c1.g6 === 0
        ) {
          return c1.d6;
        } else {
          return c1.c6;
        }
        break;
      default:
        return c1.b6;
        break;
    }
  }
  accessibilityBroadcastSubDate() {
    if (this.focusText === m.TEXT1) {
      if (this.subBtnStateEffect) {
        this.inputYear = this.year;
        this.year -= this.step;
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true;
        this.addOpacity = b1.y4;
        this.addBtnEnabled = true;
      }
      if (this.year <= this.minYear) {
        this.subOpacity = b1.z4;
        this.subBtnStateEffect = false;
        this.subBtnEnabled = false;
      } else {
        if (this.subOpacity === b1.z4) {
          this.subOpacity = b1.y4;
        }
        if (!this.subBtnStateEffect) {
          this.subBtnStateEffect = true;
        }
        if (!this.subBtnEnabled) {
          this.subBtnEnabled = true;
        }
      }
      try {
        let date = new Date(this.year, this.month - 1, this.day);
        let i2 = new intl.DateTimeFormat(i, { year: 'numeric' });
        let j2 = i2.format(date);
        let eventInfo = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            j2 +
            ',' +
            this.year.toString() +
            '/' +
            this.month.toString() +
            '/' +
            this.day.toString(),
        };
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessility subYear click send event');
        });
      } catch (h2) {
        let code = h2.code;
        let message = h2.message;
        console.log(
          `Accessility subYear faild error code:${code} message:${message}`
        );
      }
    } else if (this.focusText === m.TEXT2) {
      this.month -= this.step % c1.j5;
      if (this.month < c1.i5) {
        this.month += c1.j5;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
      try {
        let date = new Date(this.year, this.month - 1, this.day);
        let f2 = new intl.DateTimeFormat(i, { month: 'long' });
        let g2 = f2.format(date);
        let eventInfo = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            g2 +
            ',' +
            this.year.toString() +
            '/' +
            this.month.toString() +
            '/' +
            this.day.toString(),
        };
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessility subMonth click send event');
        });
      } catch (e2) {
        let code = e2.code;
        let message = e2.message;
        console.log(
          `Accessility subMonth faild error code:${code} message:${message}`
        );
      }
    } else if (this.focusText === m.TEXT3) {
      this.day -= this.step % this.getDayNumber();
      if (this.day < c1.k5) {
        this.day += this.getDayNumber();
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
      try {
        let eventInfo = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            j.get(this.day) +
            ',' +
            this.year.toString() +
            '/' +
            this.month.toString() +
            '/' +
            this.day.toString(),
        };
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessility subDay click send event');
        });
      } catch (d2) {
        let code = d2.code;
        let message = d2.message;
        console.log(
          `Accessility subDay faild error code:${code} message:${message}`
        );
      }
    } else {
      this.focusDayWitdhSub();
    }
  }
  subDate() {
    if (this.focusText === m.TEXT1) {
      if (this.subBtnStateEffect) {
        this.inputYear = this.year;
        this.year -= this.step;
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true;
        this.addOpacity = b1.y4;
        this.addBtnEnabled = true;
      }
      if (this.year <= this.minYear) {
        this.subOpacity = b1.z4;
        this.subBtnStateEffect = false;
        this.subBtnEnabled = false;
      } else {
        if (this.subOpacity === b1.z4) {
          this.subOpacity = b1.y4;
        }
        if (!this.subBtnStateEffect) {
          this.subBtnStateEffect = true;
        }
        if (!this.subBtnEnabled) {
          this.subBtnEnabled = true;
        }
      }
    } else if (this.focusText === m.TEXT2) {
      this.month -= this.step % c1.j5;
      if (this.month < c1.i5) {
        this.month += c1.j5;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (this.focusText === m.TEXT3) {
      this.day -= this.step % this.getDayNumber();
      if (this.day < c1.k5) {
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
    this.focusText = m.TEXT3;
    this.hasFocusText3 = true;
    this.day -= this.step % this.getDayNumber();
    if (this.day < c1.k5) {
      this.day += this.getDayNumber();
    }
    this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
  }
  accessibilityBroadcastAddDate() {
    if (this.focusText === m.TEXT1) {
      if (this.addBtnStateEffect) {
        this.inputYear = this.year;
        this.year += this.step;
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.subBtnStateEffect) {
        this.subBtnStateEffect = true;
        this.subOpacity = b1.y4;
        this.subBtnEnabled = true;
      }
      if (this.year >= this.maxYear) {
        this.addOpacity = b1.z4;
        this.addBtnStateEffect = false;
        this.addBtnEnabled = false;
      } else {
        if (this.addOpacity === b1.z4) {
          this.addOpacity = b1.y4;
        }
        if (!this.addBtnStateEffect) {
          this.addBtnStateEffect = true;
        }
        if (!this.addBtnEnabled) {
          this.addBtnEnabled = true;
        }
      }
      try {
        let date = new Date(this.year, this.month - 1, this.day);
        let b2 = new intl.DateTimeFormat(i, { year: 'numeric' });
        let c2 = b2.format(date);
        let eventInfo = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            c2 +
            ',' +
            this.year.toString() +
            '/' +
            this.month.toString() +
            '/' +
            this.day.toString(),
        };
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessility addYear click send event');
        });
      } catch (a2) {
        let code = a2.code;
        let message = a2.message;
        console.log(
          `Accessility addYear click faild error code:${code} message:${message}`
        );
      }
    } else if (this.focusText === m.TEXT2) {
      this.month += this.step % c1.j5;
      if (this.month > c1.j5) {
        this.month -= c1.j5;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
      try {
        let date = new Date(this.year, this.month - 1, this.day);
        let w1 = new intl.DateTimeFormat(i, { month: 'long' });
        let z1 = w1.format(date);
        let eventInfo = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            z1 +
            ',' +
            this.year.toString() +
            '/' +
            this.month.toString() +
            '/' +
            this.day.toString(),
        };
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessility addMonth click send event');
        });
      } catch (v1) {
        let code = v1.code;
        let message = v1.message;
        console.log(
          `Accessility addMonth faild error code:${code} message:${message}`
        );
      }
    } else if (this.focusText === m.TEXT3) {
      this.day += this.step % this.getDayNumber();
      if (this.day > this.getDayNumber()) {
        this.day -= this.getDayNumber();
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
      try {
        let eventInfo = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            j.get(this.day) +
            ',' +
            this.year.toString() +
            '/' +
            this.month.toString() +
            '/' +
            this.day.toString(),
        };
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessility addDay click send event');
        });
      } catch (u1) {
        let code = u1.code;
        let message = u1.message;
        console.log(
          `Accessility addDay faild error code:${code} message:${message}`
        );
      }
    } else {
      this.focusDayWithAdd();
    }
  }
  addDate() {
    if (this.focusText === m.TEXT1) {
      if (this.addBtnStateEffect) {
        this.inputYear = this.year;
        this.year += this.step;
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.subBtnStateEffect) {
        this.subBtnStateEffect = true;
        this.subOpacity = b1.y4;
        this.subBtnEnabled = true;
      }
      if (this.year >= this.maxYear) {
        this.addOpacity = b1.z4;
        this.addBtnStateEffect = false;
        this.addBtnEnabled = false;
      } else {
        if (this.addOpacity === b1.z4) {
          this.addOpacity = b1.y4;
        }
        if (!this.addBtnStateEffect) {
          this.addBtnStateEffect = true;
        }
        if (!this.addBtnEnabled) {
          this.addBtnEnabled = true;
        }
      }
    } else if (this.focusText === m.TEXT2) {
      this.month += this.step % c1.j5;
      if (this.month > c1.j5) {
        this.month -= c1.j5;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (this.focusText === m.TEXT3) {
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
    this.focusText = m.TEXT3;
    this.hasFocusText3 = true;
    this.day += this.step % this.getDayNumber();
    if (this.day > this.getDayNumber()) {
      this.day -= this.getDayNumber();
    }
    this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
  }
  updateInlineEnableSate() {
    if (this.value >= this.max) {
      this.addOpacity = b1.z4;
      this.addBtnStateEffect = false;
      this.addBtnEnabled = false;
    } else {
      this.addOpacity = b1.y4;
      this.addBtnStateEffect = true;
      this.addBtnEnabled = true;
    }
    if (this.value <= this.min) {
      this.subOpacity = b1.z4;
      this.subBtnStateEffect = false;
      this.subBtnEnabled = false;
    } else {
      this.subOpacity = b1.y4;
      this.subBtnStateEffect = true;
      this.subBtnEnabled = true;
    }
  }
  updateDateEnableSate() {
    if (this.year === this.maxYear && this.focusText === m.TEXT1) {
      this.addOpacity = b1.z4;
      this.addBtnStateEffect = false;
      this.addBtnEnabled = false;
    } else {
      if (this.addOpacity === b1.z4) {
        this.addOpacity = b1.y4;
      }
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true;
      }
      if (!this.addBtnEnabled) {
        this.addBtnEnabled = true;
      }
    }
    if (this.year === this.minYear && this.focusText === m.TEXT1) {
      this.subOpacity = b1.z4;
      this.subBtnStateEffect = false;
      this.subBtnEnabled = false;
    } else {
      if (this.subOpacity === b1.z4) {
        this.subOpacity = b1.y4;
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
    this.focusText = m.NONE;
    this.hasFocusText1 = false;
    this.hasFocusText2 = false;
    this.hasFocusText3 = false;
  }
  resetFocusButton() {
    if (this.addBtnFocusWidh === b1.c3) {
      this.addBtnFocusWidh = b1.d3;
      this.onBlurIncrease && this.onBlurIncrease();
    }
    if (this.subBtnFocusWidh === b1.c3) {
      this.subBtnFocusWidh = b1.d3;
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
      this.addOpacity = b1.y4;
      this.addBtnEnabled = true;
    }
  }
  endLastValue() {
    this.value = this.max;
    if (!this.subBtnStateEffect) {
      this.subBtnStateEffect = true;
      this.subOpacity = b1.y4;
      this.subBtnEnabled = true;
    }
  }
  updateButtonStatus() {
    if (this.value <= this.min) {
      if (!this.addBtnStateEffect && this.max != this.min) {
        this.addBtnStateEffect = true;
        this.addOpacity = b1.y4;
        this.addBtnEnabled = true;
      }
      this.subOpacity = b1.z4;
      this.subBtnStateEffect = false;
      this.subBtnEnabled = false;
    }
    if (this.value >= this.max) {
      if (!this.subBtnStateEffect && this.max != this.min) {
        this.subBtnStateEffect = true;
        this.subOpacity = b1.y4;
        this.subBtnEnabled = true;
      }
      this.addOpacity = b1.z4;
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
    let year = this.year.toString();
    if (year.length === 1) {
      year = '000' + year;
    } else if (year.length === 2) {
      year = '00' + year;
    } else if (year.length === 3) {
      year = '0' + year;
    } else {
      year = year;
    }
    return year;
  }
  focusWithTarget(key) {
    setTimeout(() => {
      let t1 = focusControl.requestFocus(key);
      if (t1) {
        console.log('Request success');
      } else {
        console.log('Request failed');
      }
    });
  }
  focusCurrentText(text) {
    if (text === m.TEXT1) {
      if (this.focusText === m.NONE) {
        this.focusText = m.TEXT1;
      }
      if (!this.hasFocusText1) {
        this.hasFocusText1 = true;
      }
    } else if (text === m.TEXT2) {
      if (this.focusText === m.NONE) {
        this.focusText = m.TEXT2;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (text === m.TEXT3) {
      if (this.focusText === m.NONE) {
        this.focusText = m.TEXT3;
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
  resourceToVp(value) {
    try {
      if (value.id !== -1) {
        return px2vp(getContext(this).resourceManager.getNumber(value.id));
      } else {
        return px2vp(
          getContext(this).resourceManager.getNumberByName(
            value.params[0].split('.')[2]
          )
        );
      }
    } catch (error) {
      return b1.u3;
    }
  }
  getAccessibilityResource(resource) {
    let s1 = '';
    try {
      if (typeof resource === 'string') {
        s1 = resource;
      } else {
        s1 = getContext()?.resourceManager?.getStringSync(resource?.id);
      }
    } catch (error) {
      let code = error.code;
      let message = error.message;
      console.log(
        `Get accessility resource error code:${code} message:${message}`
      );
    }
    return s1;
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.type === CounterType.LIST) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            RelativeContainer.create();
            RelativeContainer.direction(this.counterDirection);
            RelativeContainer.width('100%');
            RelativeContainer.height(b1.v3);
          }, RelativeContainer);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.numberStyleOptions.label);
            Text.direction(this.counterDirection);
            Text.fontSize(b1.f3);
            Text.maxFontScale(b1.a5);
            Text.fontColor(b1.u2);
            Text.margin({
              start: LengthMetrics.vp(this.resourceToVp(b1.j3)),
            });
            Text.alignRules({
              center: { anchor: '__container__', align: VerticalAlign.Center },
              start: { anchor: '__container__', align: HorizontalAlign.Start },
              end: { anchor: 'Row1', align: HorizontalAlign.Start },
            });
            Text.id('Text');
          }, Text);
          Text.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.direction(this.counterDirection);
            Row.height(b1.x3);
            Row.margin({
              end: LengthMetrics.vp(this.resourceToVp(b1.l3)),
            });
            Row.alignRules({
              center: { anchor: '__container__', align: VerticalAlign.Center },
              end: { anchor: '__container__', align: HorizontalAlign.End },
            });
            Row.tabIndex(0);
            Row.id('Row1');
          }, Row);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.counterDirection);
            Stack.width(b1.x3);
            Stack.height(b1.x3);
            Stack.borderRadius(b1.y3);
            Stack.borderWidth(this.subBtnFocusWidh);
            Stack.borderColor(b1.t2);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(b1.z2);
            Image.direction(this.counterDirection);
            Image.width(b1.w3);
            Image.height(b1.w3);
            Image.fillColor(b1.s2);
            Image.opacity(this.subOpacity);
          }, Image);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            Button.width(b1.x3);
            Button.height(b1.x3);
            Button.responseRegion({
              x: b1.d4,
              y: b1.e4,
              width: '150%',
              height: '150%',
            });
            Button.groupDefaultFocus(true);
            Button.backgroundColor(b1.q2);
            Button.opacity(this.subOpacity);
            Button.enabled(this.subBtnEnabled);
            Button.key('ListSubButton' + this.timeStamp.toString());
            Button.onKeyEvent((event) => {
              this.subBtnFocusWidh = b1.c3;
              if (event.keyCode === c1.l5) {
                this.resetFocusButton();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_HOME
              ) {
                event.stopPropagation();
                this.homeFirstValue();
                this.focusWithTarget(
                  'ListAddButton' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_END
              ) {
                event.stopPropagation();
                if (this.addBtnStateEffect) {
                  this.addBtnStateEffect = false;
                  this.addOpacity = b1.z4;
                  this.addBtnEnabled = false;
                }
                this.endLastValue();
                this.focusWithTarget(
                  'ListAddButton' + this.timeStamp.toString()
                );
              }
            });
            Button.onClick((event) => {
              this.subValue();
              this.onChange?.(this.value);
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.subBtnFocusWidh = b1.d3;
              }
              try {
                let eventInfo = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'click',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                  console.log('Accessility subValue click send event');
                });
              } catch (q1) {
                let code = q1.code;
                let message = q1.message;
                console.log(
                  `Accessility subValue faild error code:${code} message:${message}`
                );
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((event) => {
              if (event.repeat) {
                this.subValue();
                this.onChange?.(this.value);
              }
              this.subBtnFocusWidh = b1.d3;
            });
            LongPressGesture.onActionEnd(() => {
              try {
                let eventInfo = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'common',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                  console.log('Accessility subValue longPress send event');
                });
              } catch (p1) {
                let code = p1.code;
                let message = p1.message;
                console.log(
                  `Accessility subValue longPress faild error code:${code} message:${message}`
                );
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((isHover) => {
              this.onHoverDecrease && this.onHoverDecrease(isHover);
            });
            Button.focusable(this.focusEnable);
            Button.onFocus(() => {
              this.subBtnFocusWidh = b1.c3;
              this.onFocusDecrease && this.onFocusDecrease();
              this.updateButtonStatus();
            });
            Button.onBlur(() => {
              this.subBtnFocusWidh = b1.d3;
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
                  Text.fontSize(b1.g3);
                  Text.maxFontScale(b1.b5);
                  Text.fontColor(b1.u2);
                  Text.margin({
                    start: LengthMetrics.vp(b1.a4),
                    end: LengthMetrics.vp(b1.a4),
                  });
                }, Text);
                Text.pop();
              });
            } else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                  Text.fontSize(b1.g3);
                  Text.maxFontScale(b1.b5);
                  Text.fontColor(b1.u2);
                  Text.margin({
                    start: LengthMetrics.vp(b1.a4),
                    end: LengthMetrics.vp(b1.a4),
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
            Stack.width(b1.x3);
            Stack.height(b1.x3);
            Stack.borderRadius(b1.y3);
            Stack.borderWidth(this.addBtnFocusWidh);
            Stack.borderColor(b1.t2);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(b1.w2);
            Image.direction(this.counterDirection);
            Image.width(b1.w3);
            Image.height(b1.w3);
            Image.fillColor(b1.s2);
            Image.opacity(this.addOpacity);
          }, Image);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            Button.width(b1.x3);
            Button.height(b1.x3);
            Button.responseRegion({
              x: b1.d4,
              y: b1.e4,
              width: '150%',
              height: '150%',
            });
            Button.backgroundColor(b1.q2);
            Button.opacity(this.addOpacity);
            Button.enabled(this.addBtnEnabled);
            Button.key('ListAddButton' + this.timeStamp.toString());
            Button.onKeyEvent((event) => {
              this.addBtnFocusWidh = b1.c3;
              if (event.keyCode === c1.l5) {
                this.resetFocusButton();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_HOME
              ) {
                event.stopPropagation();
                this.homeFirstValue();
                if (this.subBtnStateEffect) {
                  this.subBtnStateEffect = false;
                  this.subOpacity = b1.z4;
                  this.subBtnEnabled = false;
                }
                this.focusWithTarget(
                  'ListAddButton' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_END
              ) {
                event.stopPropagation();
                this.endLastValue();
                this.focusWithTarget(
                  'ListSubButton' + this.timeStamp.toString()
                );
              }
            });
            Button.onClick((event) => {
              this.addValue();
              this.onChange?.(this.value);
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.addBtnFocusWidh = b1.d3;
              }
              try {
                let eventInfo = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'click',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                  console.log('Accessility addValue click send event');
                });
              } catch (o1) {
                let code = o1.code;
                let message = o1.message;
                console.log(
                  `Accessility addValue click longPress faild error code:${code} message:${message}`
                );
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((event) => {
              if (event.repeat) {
                this.addValue();
                this.onChange?.(this.value);
              }
              this.addBtnFocusWidh = b1.d3;
            });
            LongPressGesture.onActionEnd(() => {
              try {
                let eventInfo = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'common',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                  console.log('Accessility addValue longPress send event');
                });
              } catch (n1) {
                let code = n1.code;
                let message = n1.message;
                console.log(
                  `Accessility addValue longPress longPress faild error code:${code} message:${message}`
                );
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((isHover) => {
              this.onHoverIncrease && this.onHoverIncrease(isHover);
            });
            Button.focusable(this.focusEnable);
            Button.onFocus(() => {
              this.addBtnFocusWidh = b1.c3;
              this.onFocusIncrease && this.onFocusIncrease();
              this.updateButtonStatus();
            });
            Button.onBlur(() => {
              this.addBtnFocusWidh = b1.d3;
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
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
          }, Column);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.direction(this.counterDirection);
            Row.tabIndex(0);
            Row.height(b1.n3);
            Row.align(Alignment.Center);
            Row.borderWidth(b1.q3);
            Row.borderColor(b1.v2);
            Row.borderRadius(b1.s3);
          }, Row);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.width(b1.r3);
            Stack.height(b1.r3);
            Stack.borderRadius(b1.f4);
            Stack.borderWidth(this.subBtnFocusWidh);
            Stack.borderColor(b1.t2);
            Stack.margin({
              start: LengthMetrics.vp(this.resourceToVp(b1.t3)),
            });
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(b1.z2);
            Image.direction(this.counterDirection);
            Image.width(b1.m3);
            Image.height(b1.m3);
            Image.fillColor(b1.s2);
            Image.opacity(this.subOpacity);
          }, Image);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            Button.width(b1.r3);
            Button.height(b1.r3);
            Button.backgroundColor(b1.q2);
            Button.opacity(this.subOpacity);
            Button.enabled(this.subBtnEnabled);
            Button.key('CompactSubButton' + this.timeStamp.toString());
            Button.onKeyEvent((event) => {
              this.subBtnFocusWidh = b1.c3;
              if (event.keyCode === c1.l5) {
                this.resetFocusButton();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_HOME
              ) {
                event.stopPropagation();
                this.homeFirstValue();
                this.focusWithTarget(
                  'CompactAddButton' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_END
              ) {
                event.stopPropagation();
                this.endLastValue();
                if (this.addBtnStateEffect) {
                  this.addBtnStateEffect = false;
                  this.addOpacity = b1.z4;
                  this.addBtnEnabled = false;
                }
                this.focusWithTarget(
                  'CompactSubButton' + this.timeStamp.toString()
                );
              }
            });
            Button.onClick((event) => {
              this.subValue();
              this.onChange?.(this.value);
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.subBtnFocusWidh = b1.d3;
              }
              try {
                let eventInfo = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'click',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                  console.log('Accessility subValue click send event');
                });
              } catch (m1) {
                let code = m1.code;
                let message = m1.message;
                console.log(
                  `Accessility subValue click longPress faild error code:${code} message:${message}`
                );
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((event) => {
              if (event.repeat) {
                this.subValue();
                this.onChange?.(this.value);
              }
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.subBtnFocusWidh = b1.d3;
              }
            });
            LongPressGesture.onActionEnd(() => {
              try {
                let eventInfo = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'common',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                  console.log('Accessility subValue longPress send event');
                });
              } catch (l1) {
                let code = l1.code;
                let message = l1.message;
                console.log(
                  `Accessility subValue longPress longPress faild error code:${code} message:${message}`
                );
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((isHover) => {
              this.onHoverDecrease && this.onHoverDecrease(isHover);
            });
            Button.focusable(this.focusEnable);
            Button.groupDefaultFocus(true);
            Button.onFocus(() => {
              this.subBtnFocusWidh = b1.c3;
              this.onFocusDecrease && this.onFocusDecrease();
              this.updateButtonStatus();
            });
            Button.onBlur(() => {
              this.subBtnFocusWidh = b1.d3;
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
                  Text.accessibilityText(
                    this.getAccessibilityResource(
                      this.numberStyleOptions.label
                    ) +
                      '[n2]' +
                      this.value.toString() +
                      '[n0]'
                  );
                  Text.textAlign(TextAlign.Center);
                  Text.fontSize(b1.i3);
                  Text.maxFontScale(b1.b5);
                  Text.fontColor(b1.u2);
                  Text.width(this.textWidth.toString());
                  Text.margin({
                    start: LengthMetrics.vp(b1.h4),
                    end: LengthMetrics.vp(b1.h4),
                  });
                }, Text);
                Text.pop();
              });
            } else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                  Text.fontSize(b1.i3);
                  Text.maxFontScale(b1.b5);
                  Text.fontColor(b1.u2);
                  Text.margin({
                    start: LengthMetrics.vp(b1.h4),
                    end: LengthMetrics.vp(b1.h4),
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
            Stack.width(b1.r3);
            Stack.height(b1.r3);
            Stack.borderRadius(b1.f4);
            Stack.borderWidth(this.addBtnFocusWidh);
            Stack.borderColor(b1.t2);
            Stack.margin({
              end: LengthMetrics.vp(this.resourceToVp(b1.t3)),
            });
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(b1.w2);
            Image.direction(this.counterDirection);
            Image.width(b1.m3);
            Image.height(b1.m3);
            Image.fillColor(b1.s2);
            Image.opacity(this.addOpacity);
          }, Image);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            Button.width(b1.r3);
            Button.height(b1.r3);
            Button.backgroundColor(b1.q2);
            Button.opacity(this.addOpacity);
            Button.enabled(this.addBtnEnabled);
            Button.key('CompactAddButton' + this.timeStamp.toString());
            Button.onKeyEvent((event) => {
              this.addBtnFocusWidh = b1.c3;
              if (event.keyCode === c1.l5) {
                this.resetFocusButton();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_HOME
              ) {
                event.stopPropagation();
                this.homeFirstValue();
                if (this.subBtnStateEffect) {
                  this.subBtnStateEffect = false;
                  this.subOpacity = b1.z4;
                  this.subBtnEnabled = false;
                }
                this.focusWithTarget(
                  'CompactAddButton' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_END
              ) {
                event.stopPropagation();
                this.endLastValue();
                this.focusWithTarget(
                  'CompactSubButton' + this.timeStamp.toString()
                );
              }
            });
            Button.onClick((event) => {
              this.addValue();
              this.onChange?.(this.value);
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.addBtnFocusWidh = b1.d3;
              }
              try {
                let eventInfo = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'click',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                  console.log('Accessility addValue click send event');
                });
              } catch (k1) {
                let code = k1.code;
                let message = k1.message;
                console.log(
                  `Accessility addValue click longPress faild error code:${code} message:${message}`
                );
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((event) => {
              if (event.repeat) {
                this.addValue();
                this.onChange?.(this.value);
              }
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.addBtnFocusWidh = b1.d3;
              }
            });
            LongPressGesture.onActionEnd(() => {
              try {
                let eventInfo = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'common',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                  console.log('Accessility addValue longPress send event');
                });
              } catch (j1) {
                let code = j1.code;
                let message = j1.message;
                console.log(
                  `Accessility addValue longPress longPress faild error code:${code} message:${message}`
                );
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((isHover) => {
              this.onHoverIncrease && this.onHoverIncrease(isHover);
            });
            Button.focusable(this.focusEnable);
            Button.onFocus(() => {
              this.addBtnFocusWidh = b1.c3;
              this.onFocusIncrease && this.onFocusIncrease();
              this.updateButtonStatus();
            });
            Button.onBlur(() => {
              this.addBtnFocusWidh = b1.d3;
              this.onBlurIncrease && this.onBlurIncrease();
            });
          }, Button);
          Button.pop();
          Stack.pop();
          Row.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.numberStyleOptions.label);
            Text.direction(this.counterDirection);
            Text.margin({ top: b1.i4 });
            Text.fontSize(b1.h3);
            Text.maxFontScale(b1.a5);
            Text.fontColor(b1.u2);
            Text.align(Alignment.Top);
          }, Text);
          Text.pop();
          Column.pop();
        });
      } else if (this.type === CounterType.INLINE) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.direction(this.counterDirection);
            Row.height(b1.q4);
            Row.borderWidth(b1.q3);
            Row.borderColor(b1.v2);
            Row.borderRadius(b1.t4);
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
                    start: LengthMetrics.vp(b1.x4),
                    end: LengthMetrics.vp(b1.x4),
                  });
                  RelativeContainer.height('100%');
                  RelativeContainer.width(this.textWidth);
                }, RelativeContainer);
                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                  TextInput.fontColor(this.hasFocusText1 ? Color.White : b1.u2);
                  TextInput.maxLength(this.getMaxLength());
                  TextInput.backgroundColor(
                    this.hasFocusText1 ? b1.t2 : Color.Transparent
                  );
                  TextInput.key('InlineTextInput' + this.timeStamp.toString());
                  TextInput.onKeyEvent((event) => {
                    this.focusCurrentText(m.TEXT1);
                    if (event.keyCode === c1.l5) {
                      this.resetFocusText();
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === c1.KEYCODE_DPAD_UP
                    ) {
                      this.addValue();
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === c1.KEYCODE_MOVE_HOME
                    ) {
                      event.stopPropagation();
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === c1.KEYCODE_MOVE_END
                    ) {
                      event.stopPropagation();
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === c1.KEYCODE_DPAD_DOWN
                    ) {
                      this.subValue();
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === c1.KEYCODE_DPAD_LEFT
                    ) {
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === c1.KEYCODE_DPAD_RIGHT
                    ) {
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                      event.stopPropagation();
                    }
                  });
                  TextInput.onChange((value) => {
                    this.inputValue = value;
                    for (let i1 = 0; i1 < value.length; i1++) {
                      let c = value[i1];
                      if (c === '+' || c === '*' || c === '#') {
                        this.value -= 1;
                        this.value += 1;
                        this.inputValue = this.value.toString();
                        return;
                      }
                      if (c === '-' && i1 !== 0) {
                        this.inputValue = c;
                        break;
                      }
                    }
                    this.hasInputText1 = true;
                    let c = value[value.length - 1];
                    if (value.length === this.getMaxLength()) {
                      this.inputValue = c;
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
                        this.inputValue = c;
                      }
                      if (value.length < this.getMaxLength()) {
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
                  TextInput.onSubmit((enterKey) => {
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
                    this.focusText = m.TEXT1;
                    this.hasFocusText1 = true;
                    this.controller1.caretPosition(
                      this.value.toString().length
                    );
                  });
                  TextInput.onBlur(() => {
                    this.focusText = m.NONE;
                    this.hasFocusText1 = false;
                  });
                  TextInput.onClick((event) => {
                    this.focusText = m.TEXT1;
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
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  Row.create();
                  Row.direction(this.counterDirection);
                  Row.margin({
                    start: LengthMetrics.vp(b1.x4),
                    end: LengthMetrics.vp(b1.x4),
                  });
                }, Row);
                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                  TextInput.fontColor(this.hasFocusText1 ? Color.White : b1.u2);
                  TextInput.maxLength(this.getMaxLength());
                  TextInput.backgroundColor(
                    this.hasFocusText1 ? b1.t2 : Color.Transparent
                  );
                  TextInput.key('InlineTextInput' + this.timeStamp.toString());
                  TextInput.onKeyEvent((event) => {
                    this.focusCurrentText(m.TEXT1);
                    if (event.keyCode === c1.l5) {
                      this.resetFocusText();
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === c1.KEYCODE_DPAD_UP
                    ) {
                      this.addValue();
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === c1.KEYCODE_DPAD_DOWN
                    ) {
                      this.subValue();
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === c1.KEYCODE_DPAD_LEFT
                    ) {
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === c1.KEYCODE_DPAD_RIGHT
                    ) {
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                      event.stopPropagation();
                    }
                  });
                  TextInput.onChange((value) => {
                    this.inputValue = value;
                    for (let h1 = 0; h1 < value.length; h1++) {
                      let c = value[h1];
                      if (c === '+' || c === '*' || c === '#') {
                        this.value -= 1;
                        this.value += 1;
                        this.inputValue = this.value.toString();
                        return;
                      }
                      if (c === '-' && h1 !== 0) {
                        this.inputValue = c;
                        break;
                      }
                    }
                    this.hasInputText1 = true;
                    let c = value[value.length - 1];
                    if (value.length === this.getMaxLength()) {
                      this.inputValue = c;
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
                        this.inputValue = c;
                      }
                      if (value.length < this.getMaxLength()) {
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
                  TextInput.onSubmit((enterKey) => {
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
                    this.focusText = m.TEXT1;
                    this.hasFocusText1 = true;
                    this.controller1.caretPosition(
                      this.value.toString().length
                    );
                  });
                  TextInput.onBlur(() => {
                    this.focusText = m.NONE;
                    this.hasFocusText1 = false;
                  });
                  TextInput.onClick((event) => {
                    this.focusText = m.TEXT1;
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
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.direction(this.counterDirection);
            Column.width(b1.r4);
            Column.height(b1.q4);
            Column.borderWidth({ start: LengthMetrics.vp(b1.e3) });
            Column.borderColor(b1.v2);
          }, Column);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.counterDirection);
            Stack.width(b1.r4);
            Stack.height(b1.s4);
            Stack.padding({ top: '1vp' });
            Stack.borderWidth({ bottom: '1vp' });
            Stack.borderColor(b1.v2);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Rect.create();
            Rect.direction(this.counterDirection);
            Rect.width(b1.u4);
            Rect.height(b1.v4);
            Rect.radius([
              ['0vp', '0vp'],
              [b1.t4, b1.t4],
              ['0vp', '0vp'],
              ['0vp', '0vp'],
            ]);
            Rect.strokeWidth(this.addBtnFocusWidh);
            Rect.stroke(b1.t2);
            Rect.margin({ end: LengthMetrics.vp(2) });
            Rect.fillOpacity(0);
          }, Rect);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(b1.a3);
            Image.direction(this.counterDirection);
            Image.width(b1.m4);
            Image.height(b1.n4);
            Image.fillColor(b1.s2);
            Image.opacity(this.addOpacity);
          }, Image);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            Button.width(b1.r4);
            Button.height(b1.s4);
            Button.backgroundColor(Color.Transparent);
            Button.opacity(this.addOpacity);
            Button.enabled(this.addBtnEnabled);
            Button.onClick((event) => {
              this.addValue();
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.addBtnFocusWidh = b1.d3;
              }
              try {
                let eventInfo = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'click',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                  console.log('Accessility addValue click send event');
                });
              } catch (g1) {
                let code = g1.code;
                let message = g1.message;
                console.log(
                  `Accessility addValue click longPress faild error code:${code} message:${message}`
                );
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((event) => {
              if (event.repeat) {
                this.addValue();
              }
              this.addBtnFocusWidh = b1.d3;
            });
            LongPressGesture.onActionEnd(() => {
              try {
                let eventInfo = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'common',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                  console.log('Accessility addValue longPress send event');
                });
              } catch (f1) {
                let code = f1.code;
                let message = f1.message;
                console.log(
                  `Accessility addValue longPress faild error code:${code} message:${message}`
                );
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((isHover) => {
              this.onHoverIncrease && this.onHoverIncrease(isHover);
            });
            Button.focusable(false);
            Button.onFocus(() => {
              this.addBtnFocusWidh = b1.c3;
              this.onFocusIncrease && this.onFocusIncrease();
            });
            Button.onBlur(() => {
              this.addBtnFocusWidh = b1.d3;
              this.onBlurIncrease && this.onBlurIncrease();
            });
          }, Button);
          Button.pop();
          Stack.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.counterDirection);
            Stack.width(b1.r4);
            Stack.height(b1.s4);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Rect.create();
            Rect.direction(this.counterDirection);
            Rect.width(b1.u4);
            Rect.height(b1.v4);
            Rect.radius([
              ['0vp', '0vp'],
              ['0vp', '0vp'],
              [b1.t4, b1.t4],
              ['0vp', '0vp'],
            ]);
            Rect.strokeWidth(this.subBtnFocusWidh);
            Rect.stroke(b1.t2);
            Rect.margin({
              top: LengthMetrics.vp(1),
              end: LengthMetrics.vp(1),
              bottom: LengthMetrics.vp(2),
            });
            Rect.fillOpacity(0);
          }, Rect);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(b1.b3);
            Image.direction(this.counterDirection);
            Image.width(b1.m4);
            Image.height(b1.n4);
            Image.fillColor(b1.s2);
            Image.opacity(this.subOpacity);
          }, Image);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            Button.width(b1.r4);
            Button.height(b1.s4);
            Button.backgroundColor(Color.Transparent);
            Button.opacity(this.subOpacity);
            Button.enabled(this.subBtnEnabled);
            Button.onClick((event) => {
              this.subValue();
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.subBtnFocusWidh = b1.d3;
              }
              try {
                let eventInfo = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'click',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                  console.log('Accessility subValue click send event');
                });
              } catch (e1) {
                let code = e1.code;
                let message = e1.message;
                console.log(
                  `Accessility subValue click faild error code:${code} message:${message}`
                );
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((event) => {
              if (event.repeat) {
                this.subValue();
              }
              this.subBtnFocusWidh = b1.d3;
            });
            LongPressGesture.onActionEnd(() => {
              try {
                let eventInfo = {
                  type: 'announceForAccessibility',
                  bundleName: getContext()?.abilityInfo?.bundleName,
                  triggerAction: 'common',
                  textAnnouncedForAccessibility: this.value?.toString(),
                };
                accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                  console.log('Accessility subValue longPress send event');
                });
              } catch (d1) {
                let code = d1.code;
                let message = d1.message;
                console.log(
                  `Accessility subValue longPress faild error code:${code} message:${message}`
                );
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((isHover) => {
              this.onHoverDecrease && this.onHoverDecrease(isHover);
            });
            Button.focusable(false);
            Button.onFocus(() => {
              this.subBtnFocusWidh = b1.c3;
              this.onFocusDecrease && this.onFocusDecrease();
            });
            Button.onBlur(() => {
              this.subBtnFocusWidh = b1.d3;
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
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.direction(this.counterDirection);
            Row.height(b1.q4);
            Row.borderWidth(b1.q3);
            Row.borderColor(b1.v2);
            Row.borderRadius(b1.t4);
            Row.clip(true);
          }, Row);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.direction(this.counterDirection);
            Row.width('92vp');
            Row.height(b1.q4);
            Row.margin({
              start: LengthMetrics.vp(b1.w4),
              end: LengthMetrics.vp(b1.w4),
            });
          }, Row);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            TextInput.fontColor(this.hasFocusText1 ? Color.White : b1.u2);
            TextInput.maxLength(5);
            TextInput.padding(0);
            TextInput.backgroundColor(
              this.hasFocusText1 ? b1.t2 : Color.Transparent
            );
            TextInput.width('38vp');
            TextInput.height('20vp');
            TextInput.borderRadius(0);
            TextInput.borderWidth(0);
            TextInput.key('DateTextInput1' + this.timeStamp.toString());
            TextInput.onKeyEvent((event) => {
              this.focusCurrentText(m.TEXT1);
              if (event.keyCode === c1.l5) {
                this.resetFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_DPAD_UP
              ) {
                this.addDate();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_DPAD_DOWN
              ) {
                this.subDate();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_HOME
              ) {
                this.homeFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_END
              ) {
                this.endFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_DPAD_LEFT
              ) {
                this.focusWithTarget(
                  'DateTextInput1' + this.timeStamp.toString()
                );
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_DPAD_RIGHT
              ) {
                this.focusWithTarget(
                  'DateTextInput2' + this.timeStamp.toString()
                );
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
              if (value.length === 4) {
                let date = new DateData(this.year, this.month, this.day);
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
              this.focusText = m.TEXT1;
              this.hasFocusText1 = true;
              this.updateDateEnableSate();
              this.controller1.caretPosition(this.getYear().length);
            });
            TextInput.onBlur(() => {
              this.focusText = m.NONE;
              this.hasFocusText1 = false;
              this.updateDateEnableSate();
            });
            TextInput.onClick((event) => {
              this.focusText = m.TEXT1;
              this.hasFocusText1 = true;
              this.updateDateEnableSate();
              this.controller1.caretPosition(this.getYear().length);
            });
          }, TextInput);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('/');
            Text.accessibilityLevel('no');
            Text.direction(this.counterDirection);
            Text.textAlign(TextAlign.Center);
            Text.fontSize(b1.i3);
            Text.maxFontScale(b1.b5);
            Text.fontColor(b1.u2);
            Text.width('8vp');
          }, Text);
          Text.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            TextInput.fontColor(this.hasFocusText2 ? Color.White : b1.u2);
            TextInput.maxLength(3);
            TextInput.padding(0);
            TextInput.backgroundColor(
              this.hasFocusText2 ? b1.t2 : Color.Transparent
            );
            TextInput.width('19vp');
            TextInput.height('20vp');
            TextInput.borderRadius(0);
            TextInput.key('DateTextInput2' + this.timeStamp.toString());
            TextInput.onKeyEvent((event) => {
              this.focusCurrentText(m.TEXT2);
              if (event.keyCode === c1.l5) {
                this.resetFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_DPAD_DOWN
              ) {
                this.subDate();
                this.updateDay();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_DPAD_UP
              ) {
                this.addDate();
                this.updateDay();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_HOME
              ) {
                this.homeFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_END
              ) {
                this.endFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_DPAD_LEFT
              ) {
                this.focusWithTarget(
                  'DateTextInput1' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_DPAD_RIGHT
              ) {
                this.focusWithTarget(
                  'DateTextInput3' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_TAB
              ) {
                event.stopPropagation();
                this.focusWithTarget(
                  'DateTextInput1' + this.timeStamp.toString()
                );
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
                } else {
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
                  let date = new DateData(this.year, this.month, this.day);
                  this.onDateChange?.(date);
                } else {
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
              } else {
                this.month += 1;
              }
            });
            TextInput.focusOnTouch(true);
            TextInput.tabIndex(-1);
            TextInput.focusable(true);
            TextInput.onFocus(() => {
              this.focusText = m.TEXT2;
              this.hasFocusText2 = true;
              this.controller2.caretPosition(
                this.convertNumberToString(this.month).length
              );
            });
            TextInput.onBlur(() => {
              this.focusText = m.NONE;
              this.hasFocusText2 = false;
            });
            TextInput.onClick((event) => {
              this.focusText = m.TEXT2;
              this.hasFocusText2 = true;
              this.controller2.caretPosition(
                this.convertNumberToString(this.month).length
              );
            });
          }, TextInput);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('/');
            Text.accessibilityLevel('no');
            Text.direction(this.counterDirection);
            Text.textAlign(TextAlign.Center);
            Text.fontSize(b1.i3);
            Text.maxFontScale(b1.b5);
            Text.fontColor(b1.u2);
            Text.width('8vp');
          }, Text);
          Text.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            TextInput.create({
              text: this.hasInputText3
                ? this.inputDay.toString()
                : this.convertNumberToString(this.day),
              controller: this.controller3,
            });
            TextInput.accessibilityText(j.get(this.day));
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
            TextInput.fontColor(this.hasFocusText3 ? Color.White : b1.u2);
            TextInput.maxLength(3);
            TextInput.padding(0);
            TextInput.backgroundColor(
              this.hasFocusText3 ? b1.t2 : Color.Transparent
            );
            TextInput.width('19vp');
            TextInput.height('20vp');
            TextInput.borderRadius(0);
            TextInput.key('DateTextInput3' + this.timeStamp.toString());
            TextInput.onKeyEvent((event) => {
              this.focusCurrentText(m.TEXT3);
              if (event.keyCode === c1.l5) {
                this.resetFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_DPAD_DOWN
              ) {
                this.subDate();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_DPAD_UP
              ) {
                this.addDate();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_HOME
              ) {
                this.homeFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_MOVE_END
              ) {
                this.endFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_DPAD_LEFT
              ) {
                this.focusWithTarget(
                  'DateTextInput2' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_DPAD_RIGHT
              ) {
                this.focusWithTarget(
                  'DateTextInput3' + this.timeStamp.toString()
                );
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === c1.KEYCODE_TAB
              ) {
                event.stopPropagation();
                this.focusWithTarget(
                  'DateTextInput1' + this.timeStamp.toString()
                );
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
              if (value.length === 2) {
                this.hasInputText3 = false;
                this.day -= 1;
                if (
                  this.inputDay >= 1 &&
                  this.inputDay <= this.getDayNumber()
                ) {
                  this.day = this.inputDay;
                  let date = new DateData(this.year, this.month, this.day);
                  this.onDateChange?.(date);
                } else {
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
              } else {
                this.day += 1;
              }
            });
            TextInput.tabIndex(-2);
            TextInput.focusOnTouch(true);
            TextInput.focusable(true);
            TextInput.onFocus(() => {
              this.focusText = m.TEXT3;
              this.hasFocusText3 = true;
              this.controller3.caretPosition(
                this.convertNumberToString(this.day).length
              );
            });
            TextInput.onBlur(() => {
              this.focusText = m.NONE;
              this.hasFocusText3 = false;
            });
            TextInput.onClick((event) => {
              this.focusText = m.TEXT3;
              this.hasFocusText3 = true;
              this.controller3.caretPosition(
                this.convertNumberToString(this.day).length
              );
            });
          }, TextInput);
          Row.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.direction(this.counterDirection);
            Column.width(b1.r4);
            Column.height(b1.q4);
            Column.borderWidth({ start: LengthMetrics.vp(b1.e3) });
            Column.borderColor(b1.v2);
          }, Column);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.width(b1.r4);
            Stack.height(b1.s4);
            Stack.padding({ top: '1vp' });
            Stack.borderWidth({ bottom: '1vp' });
            Stack.borderColor(b1.v2);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Rect.create();
            Rect.direction(this.counterDirection);
            Rect.width(b1.u4);
            Rect.height(b1.v4);
            Rect.radius([
              ['0vp', '0vp'],
              [b1.t4, b1.t4],
              ['0vp', '0vp'],
              ['0vp', '0vp'],
            ]);
            Rect.strokeWidth(this.addBtnFocusWidh);
            Rect.stroke(b1.t2);
            Rect.margin({ end: LengthMetrics.vp(1) });
            Rect.fillOpacity(0);
          }, Rect);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(b1.a3);
            Image.direction(this.counterDirection);
            Image.width(b1.m4);
            Image.height(b1.n4);
            Image.fillColor(b1.s2);
            Image.opacity(this.addOpacity);
          }, Image);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            Button.width(b1.r4);
            Button.height(b1.s4);
            Button.backgroundColor(Color.Transparent);
            Button.opacity(this.addOpacity);
            Button.enabled(this.addBtnEnabled);
            Button.onClick((event) => {
              this.accessibilityBroadcastAddDate();
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.addBtnFocusWidh = b1.d3;
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((event) => {
              if (event.repeat) {
                this.addDate();
              }
              this.addBtnFocusWidh = b1.d3;
            });
            LongPressGesture.onActionEnd(() => {
              this.accessibilityBroadcastAddDate();
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((isHover) => {
              this.onHoverIncrease && this.onHoverIncrease(isHover);
            });
            Button.focusable(false);
            Button.onFocus(() => {
              this.addBtnFocusWidh = b1.c3;
              this.onFocusIncrease && this.onFocusIncrease();
            });
            Button.onBlur(() => {
              this.addBtnFocusWidh = b1.d3;
              this.onBlurIncrease && this.onBlurIncrease();
            });
          }, Button);
          Button.pop();
          Stack.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.width(b1.r4);
            Stack.height(b1.s4);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Rect.create();
            Rect.direction(this.counterDirection);
            Rect.width(b1.u4);
            Rect.height(b1.v4);
            Rect.radius([
              ['0vp', '0vp'],
              ['0vp', '0vp'],
              [b1.t4, b1.t4],
              ['0vp', '0vp'],
            ]);
            Rect.strokeWidth(this.subBtnFocusWidh);
            Rect.stroke(b1.t2);
            Rect.margin({
              top: LengthMetrics.vp(1),
              end: LengthMetrics.vp(1),
              bottom: LengthMetrics.vp(2),
            });
            Rect.fillOpacity(0);
          }, Rect);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(b1.b3);
            Image.direction(this.counterDirection);
            Image.width(b1.m4);
            Image.height(b1.n4);
            Image.fillColor(b1.s2);
            Image.opacity(this.subOpacity);
          }, Image);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            Button.width(b1.r4);
            Button.height(b1.s4);
            Button.backgroundColor(Color.Transparent);
            Button.opacity(this.subOpacity);
            Button.enabled(this.subBtnEnabled);
            Button.onClick((event) => {
              this.accessibilityBroadcastSubDate();
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.subBtnFocusWidh = b1.d3;
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((event) => {
              if (event.repeat) {
                this.subDate();
              }
              this.subBtnFocusWidh = b1.d3;
            });
            LongPressGesture.onActionEnd(() => {
              this.accessibilityBroadcastSubDate();
            });
            LongPressGesture.pop();
            Gesture.pop();
            Button.hoverEffect(this.choverEffect);
            Button.onHover((isHover) => {
              this.onHoverDecrease && this.onHoverDecrease(isHover);
            });
            Button.focusable(false);
            Button.onFocus(() => {
              this.subBtnFocusWidh = b1.c3;
              this.onFocusDecrease && this.onFocusDecrease();
            });
            Button.onBlur(() => {
              this.subBtnFocusWidh = b1.d3;
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
  j,
  o,
  m,
  t,
  CounterType,
  DateData,
  CounterOptions,
  CounterComponent,
};
