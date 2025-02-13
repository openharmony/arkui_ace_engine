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

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {});
}
export var CounterType;
(function (CounterType) {
  CounterType[(CounterType['LIST'] = 0)] = 'LIST';
  CounterType[(CounterType['COMPACT'] = 1)] = 'COMPACT';
  CounterType[(CounterType['INLINE'] = 2)] = 'INLINE';
  CounterType[(CounterType['INLINE_DATE'] = 3)] = 'INLINE_DATE';
})(CounterType || (CounterType = {}));
var i;
(function (a2) {
  a2[(a2['NONE'] = 0)] = 'NONE';
  a2[(a2['TEXT1'] = 1)] = 'TEXT1';
  a2[(a2['TEXT2'] = 2)] = 'TEXT2';
  a2[(a2['TEXT3'] = 3)] = 'TEXT3';
})(i || (i = {}));
export class j {}
export class m extends j {}
export class o extends m {}
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
export class t extends j {}
export class CounterOptions {
  constructor() {
    this.type = CounterType.LIST;
  }
}
class u {}
u.b2 = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_button_normal'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.c2 = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_primary'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.d2 = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_focused_outline'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.e2 = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_text_primary'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.f2 = {
  id: -1,
  type: 10001,
  params: ['sys.color.ohos_id_color_component_normal'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.g2 = {
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_add'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.h2 = {
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_minus'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.i2 = {
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_arrow_up'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.j2 = {
  id: -1,
  type: 20000,
  params: ['sys.media.ohos_ic_public_arrow_down'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.l2 = '2vp';
u.m2 = '0vp';
u.n2 = 1;
u.o2 = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_text_size_body1'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.q2 = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_text_size_body1'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.s2 = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_text_size_body2'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.t2 = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_text_size_body1'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.u2 = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_default_padding_start'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.v2 = {
  id: -1,
  type: 10002,
  params: ['sys.float.ohos_id_default_padding_end'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.w2 = {
  id: -1,
  type: 10002,
  params: ['sys.float.button_icon_size'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.z2 = {
  id: -1,
  type: 10002,
  params: ['sys.float.container_height'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.a3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.border_width'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.b3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.button_size'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.c3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.container_radius'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.d3 = {
  id: -1,
  type: 10002,
  params: ['sys.float.button_container_margin'],
  bundleName: '__harDefaultBundleName__',
  moduleName: '__harDefaultModuleName__',
};
u.e3 = 12;
u.f3 = '48vp';
u.g3 = '20vp';
u.h3 = '32vp';
u.i3 = '16vp';
u.j3 = '8vp';
u.l3 = 8;
u.m3 = '30vp';
u.n3 = '15vp';
u.q3 = '-8vp';
u.r3 = '-8vp';
u.s3 = '12vp';
u.t3 = '10vp';
u.u3 = 10;
u.v3 = '8vp';
u.w3 = '22vp';
u.x3 = '11vp';
u.y3 = '24vp';
u.z3 = '12vp';
u.a4 = '12vp';
u.b4 = '32vp';
u.c4 = '32vp';
u.d4 = '16vp';
u.e4 = '8vp';
u.f4 = '28vp';
u.g4 = '13.5vp';
u.h4 = 12;
u.i4 = 12;
u.j4 = 1;
u.l4 = 0.4;
u.m4 = 2;
u.n4 = 1;
class a1 {}
a1.o4 = 5000;
a1.q4 = 1;
a1.r4 = 1;
a1.s4 = 1;
a1.t4 = 1;
a1.u4 = 10;
a1.v4 = 1;
a1.w4 = 12;
a1.x4 = 1;
a1.KEYCODE_DPAD_UP = 2012;
a1.KEYCODE_DPAD_DOWN = 2013;
a1.KEYCODE_DPAD_LEFT = 2014;
a1.KEYCODE_DPAD_RIGHT = 2015;
a1.KEYCODE_MOVE_HOME = 2081;
a1.KEYCODE_MOVE_END = 2082;
a1.KEYCODE_TAB = 2049;
a1.y4 = 2070;
a1.z4 = 0;
a1.a5 = 999;
a1.b5 = 1;
a1.c5 = 2;
a1.d5 = 3;
a1.e5 = 4;
a1.f5 = 5;
a1.g5 = 6;
a1.h5 = 7;
a1.i5 = 8;
a1.j5 = 9;
a1.k5 = 10;
a1.l5 = 11;
a1.m5 = 12;
a1.n5 = 31;
a1.o5 = 30;
a1.p5 = 28;
a1.q5 = 29;
a1.r5 = 4;
a1.s5 = 100;
a1.t5 = 400;
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
    this.__step = new ObservedPropertySimplePU(a1.t4, this, 'step');
    this.__inputValue = new ObservedPropertySimplePU('0', this, 'inputValue');
    this.__inputYear = new ObservedPropertySimplePU(a1.q4, this, 'inputYear');
    this.__inputMoon = new ObservedPropertySimplePU(0, this, 'inputMoon');
    this.__inputDay = new ObservedPropertySimplePU(0, this, 'inputDay');
    this.__inputHour = new ObservedPropertySimplePU(0, this, 'inputHour');
    this.__inputMinute = new ObservedPropertySimplePU(0, this, 'inputMinute');
    this.__inputSecond = new ObservedPropertySimplePU(0, this, 'inputSecond');
    this.__subOpacity = new ObservedPropertySimplePU(u.j4, this, 'subOpacity');
    this.__addOpacity = new ObservedPropertySimplePU(u.j4, this, 'addOpacity');
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
    this.__focusText = new ObservedPropertySimplePU(i.NONE, this, 'focusText');
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
    this.__min = new ObservedPropertySimplePU(a1.z4, this, 'min');
    this.__max = new ObservedPropertySimplePU(a1.a5, this, 'max');
    this.maxYear = a1.o4;
    this.minYear = a1.q4;
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
    this.numberStyleOptions = new o();
    this.dateStyleOptions = new t();
    this.inlineStyleOptions = new m();
    this.timeStamp = 0;
    this.hasTextWidth = false;
    this.controller1 = new TextInputController();
    this.controller2 = new TextInputController();
    this.controller3 = new TextInputController();
    this.initFlag = true;
    this.yearStr = getContext().resourceManager.getStringSync(125834849);
    this.monthStr = getContext().resourceManager.getStringSync(125834850);
    this.dayStr = getContext().resourceManager.getStringSync(125834851);
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
    if (params.yearStr !== undefined) {
      this.yearStr = params.yearStr;
    }
    if (params.monthStr !== undefined) {
      this.monthStr = params.monthStr;
    }
    if (params.dayStr !== undefined) {
      this.dayStr = params.dayStr;
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
    let fontSize = this.resourceToVp(u.t2);
    let uiContext = this.getUIContext();
    let fontSizeScale = uiContext.getHostContext()?.config?.fontSizeScale ?? 1;
    if (fontSizeScale < 1) {
      return fontSize + 'fp';
    } else {
      return fontSize + 'vp';
    }
  }
  convertNumberToString(value) {
    if (value >= 0 && value < a1.u4) {
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
      this.year = a1.q4;
    }
    if (
      this.dateStyleOptions.month !== undefined &&
      this.dateStyleOptions.month <= a1.w4 &&
      this.dateStyleOptions.month >= a1.v4
    ) {
      if (this.month === 0) {
        this.month = this.dateStyleOptions.month;
      }
    } else {
      this.month = a1.r4;
    }
    if (
      this.dateStyleOptions.day !== undefined &&
      this.dateStyleOptions.day <= this.getDayNumber() &&
      this.dateStyleOptions.day >= a1.x4
    ) {
      if (this.day === 0) {
        this.day = this.dateStyleOptions.day;
      }
    } else {
      this.day = a1.s4;
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
        options.year = options.year ? options.year : a1.q4;
        options.month = options.month ? options.month : a1.v4;
        options.day = options.day ? options.day : a1.x4;
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
      this.addOpacity = u.j4;
      this.addBtnEnabled = true;
    }
    if (this.value <= this.min) {
      this.value = this.min;
      this.subOpacity = u.l4;
      this.subBtnStateEffect = false;
      this.subBtnEnabled = false;
    } else {
      if (this.subOpacity === u.l4) {
        this.subOpacity = u.j4;
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
      if (this.focusText === i.NONE) {
        this.focusText = i.TEXT1;
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
      this.subOpacity = u.j4;
      this.subBtnEnabled = true;
    }
    if (this.value >= this.max) {
      this.value = this.max;
      this.addOpacity = u.l4;
      this.addBtnStateEffect = false;
      this.addBtnEnabled = false;
    } else {
      if (this.addOpacity === u.l4) {
        this.addOpacity = u.j4;
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
      case a1.b5:
      case a1.d5:
      case a1.f5:
      case a1.h5:
      case a1.i5:
      case a1.k5:
      case a1.m5:
        return a1.n5;
        break;
      case a1.e5:
      case a1.g5:
      case a1.j5:
      case a1.l5:
        return a1.o5;
        break;
      case a1.c5:
        if (
          (this.year % a1.r5 === 0 && this.year % a1.s5 !== 0) ||
          this.year % a1.t5 === 0
        ) {
          return a1.q5;
        } else {
          return a1.p5;
        }
        break;
      default:
        return a1.o5;
        break;
    }
  }
  accessibilityBroadcastSubDate() {
    if (this.focusText === i.TEXT1) {
      if (this.subBtnStateEffect) {
        this.inputYear = this.year;
        this.year -= this.step;
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true;
        this.addOpacity = u.j4;
        this.addBtnEnabled = true;
      }
      if (this.year <= this.minYear) {
        this.subOpacity = u.l4;
        this.subBtnStateEffect = false;
        this.subBtnEnabled = false;
      } else {
        if (this.subOpacity === u.l4) {
          this.subOpacity = u.j4;
        }
        if (!this.subBtnStateEffect) {
          this.subBtnStateEffect = true;
        }
        if (!this.subBtnEnabled) {
          this.subBtnEnabled = true;
        }
      }
      try {
        let eventInfo = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            this.year.toString() +
            this.yearStr +
            ' ' +
            this.year.toString() +
            this.yearStr +
            this.month.toString() +
            this.monthStr +
            this.day.toString() +
            this.dayStr,
        };
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessility subYear click send event');
        });
      } catch (z1) {
        let code = z1.code;
        let message = z1.message;
        console.log(
          `Accessility subYear faild error code:${code} message:${message}`
        );
      }
    } else if (this.focusText === i.TEXT2) {
      this.month -= this.step % a1.w4;
      if (this.month < a1.v4) {
        this.month += a1.w4;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
      try {
        let eventInfo = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            this.month.toString() +
            this.monthStr +
            ' ' +
            this.year.toString() +
            this.yearStr +
            this.month.toString() +
            this.monthStr +
            this.day.toString() +
            this.dayStr,
        };
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessility subMonth click send event');
        });
      } catch (w1) {
        let code = w1.code;
        let message = w1.message;
        console.log(
          `Accessility subMonth faild error code:${code} message:${message}`
        );
      }
    } else if (this.focusText === i.TEXT3) {
      this.day -= this.step % this.getDayNumber();
      if (this.day < a1.x4) {
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
            this.day.toString() +
            this.dayStr +
            ' ' +
            this.year.toString() +
            this.yearStr +
            this.month.toString() +
            this.monthStr +
            this.day.toString() +
            this.dayStr,
        };
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessility subDay click send event');
        });
      } catch (v1) {
        let code = v1.code;
        let message = v1.message;
        console.log(
          `Accessility subDay faild error code:${code} message:${message}`
        );
      }
    } else {
      this.focusDayWitdhSub();
    }
  }
  subDate() {
    if (this.focusText === i.TEXT1) {
      if (this.subBtnStateEffect) {
        this.inputYear = this.year;
        this.year -= this.step;
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true;
        this.addOpacity = u.j4;
        this.addBtnEnabled = true;
      }
      if (this.year <= this.minYear) {
        this.subOpacity = u.l4;
        this.subBtnStateEffect = false;
        this.subBtnEnabled = false;
      } else {
        if (this.subOpacity === u.l4) {
          this.subOpacity = u.j4;
        }
        if (!this.subBtnStateEffect) {
          this.subBtnStateEffect = true;
        }
        if (!this.subBtnEnabled) {
          this.subBtnEnabled = true;
        }
      }
    } else if (this.focusText === i.TEXT2) {
      this.month -= this.step % a1.w4;
      if (this.month < a1.v4) {
        this.month += a1.w4;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (this.focusText === i.TEXT3) {
      this.day -= this.step % this.getDayNumber();
      if (this.day < a1.x4) {
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
    this.focusText = i.TEXT3;
    this.hasFocusText3 = true;
    this.day -= this.step % this.getDayNumber();
    if (this.day < a1.x4) {
      this.day += this.getDayNumber();
    }
    this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
  }
  accessibilityBroadcastAddDate() {
    if (this.focusText === i.TEXT1) {
      if (this.addBtnStateEffect) {
        this.inputYear = this.year;
        this.year += this.step;
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.subBtnStateEffect) {
        this.subBtnStateEffect = true;
        this.subOpacity = u.j4;
        this.subBtnEnabled = true;
      }
      if (this.year >= this.maxYear) {
        this.addOpacity = u.l4;
        this.addBtnStateEffect = false;
        this.addBtnEnabled = false;
      } else {
        if (this.addOpacity === u.l4) {
          this.addOpacity = u.j4;
        }
        if (!this.addBtnStateEffect) {
          this.addBtnStateEffect = true;
        }
        if (!this.addBtnEnabled) {
          this.addBtnEnabled = true;
        }
      }
      try {
        let eventInfo = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            this.year.toString() +
            this.yearStr +
            ' ' +
            this.year.toString() +
            this.yearStr +
            this.month.toString() +
            this.monthStr +
            this.day.toString() +
            this.dayStr,
        };
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessility addYear click send event');
        });
      } catch (u1) {
        let code = u1.code;
        let message = u1.message;
        console.log(
          `Accessility addYear click faild error code:${code} message:${message}`
        );
      }
    } else if (this.focusText === i.TEXT2) {
      this.month += this.step % a1.w4;
      if (this.month > a1.w4) {
        this.month -= a1.w4;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
      try {
        let eventInfo = {
          type: 'announceForAccessibility',
          bundleName: getContext()?.abilityInfo?.bundleName,
          triggerAction: 'click',
          textAnnouncedForAccessibility:
            this.month.toString() +
            this.monthStr +
            ' ' +
            this.year.toString() +
            this.yearStr +
            this.month.toString() +
            this.monthStr +
            this.day.toString() +
            this.dayStr,
        };
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessility addMonth click send event');
        });
      } catch (t1) {
        let code = t1.code;
        let message = t1.message;
        console.log(
          `Accessility addMonth faild error code:${code} message:${message}`
        );
      }
    } else if (this.focusText === i.TEXT3) {
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
            this.day.toString() +
            this.dayStr +
            ' ' +
            this.year.toString() +
            this.yearStr +
            this.month.toString() +
            this.monthStr +
            this.day.toString() +
            this.dayStr,
        };
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessility addDay click send event');
        });
      } catch (s1) {
        let code = s1.code;
        let message = s1.message;
        console.log(
          `Accessility addDay faild error code:${code} message:${message}`
        );
      }
    } else {
      this.focusDayWithAdd();
    }
  }
  addDate() {
    if (this.focusText === i.TEXT1) {
      if (this.addBtnStateEffect) {
        this.inputYear = this.year;
        this.year += this.step;
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.subBtnStateEffect) {
        this.subBtnStateEffect = true;
        this.subOpacity = u.j4;
        this.subBtnEnabled = true;
      }
      if (this.year >= this.maxYear) {
        this.addOpacity = u.l4;
        this.addBtnStateEffect = false;
        this.addBtnEnabled = false;
      } else {
        if (this.addOpacity === u.l4) {
          this.addOpacity = u.j4;
        }
        if (!this.addBtnStateEffect) {
          this.addBtnStateEffect = true;
        }
        if (!this.addBtnEnabled) {
          this.addBtnEnabled = true;
        }
      }
    } else if (this.focusText === i.TEXT2) {
      this.month += this.step % a1.w4;
      if (this.month > a1.w4) {
        this.month -= a1.w4;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (this.focusText === i.TEXT3) {
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
    this.focusText = i.TEXT3;
    this.hasFocusText3 = true;
    this.day += this.step % this.getDayNumber();
    if (this.day > this.getDayNumber()) {
      this.day -= this.getDayNumber();
    }
    this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
  }
  updateInlineEnableSate() {
    if (this.value >= this.max) {
      this.addOpacity = u.l4;
      this.addBtnStateEffect = false;
      this.addBtnEnabled = false;
    } else {
      this.addOpacity = u.j4;
      this.addBtnStateEffect = true;
      this.addBtnEnabled = true;
    }
    if (this.value <= this.min) {
      this.subOpacity = u.l4;
      this.subBtnStateEffect = false;
      this.subBtnEnabled = false;
    } else {
      this.subOpacity = u.j4;
      this.subBtnStateEffect = true;
      this.subBtnEnabled = true;
    }
  }
  updateDateEnableSate() {
    if (this.year === this.maxYear && this.focusText === i.TEXT1) {
      this.addOpacity = u.l4;
      this.addBtnStateEffect = false;
      this.addBtnEnabled = false;
    } else {
      if (this.addOpacity === u.l4) {
        this.addOpacity = u.j4;
      }
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true;
      }
      if (!this.addBtnEnabled) {
        this.addBtnEnabled = true;
      }
    }
    if (this.year === this.minYear && this.focusText === i.TEXT1) {
      this.subOpacity = u.l4;
      this.subBtnStateEffect = false;
      this.subBtnEnabled = false;
    } else {
      if (this.subOpacity === u.l4) {
        this.subOpacity = u.j4;
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
    this.focusText = i.NONE;
    this.hasFocusText1 = false;
    this.hasFocusText2 = false;
    this.hasFocusText3 = false;
  }
  resetFocusButton() {
    if (this.addBtnFocusWidh === u.l2) {
      this.addBtnFocusWidh = u.m2;
      this.onBlurIncrease && this.onBlurIncrease();
    }
    if (this.subBtnFocusWidh === u.l2) {
      this.subBtnFocusWidh = u.m2;
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
      this.addOpacity = u.j4;
      this.addBtnEnabled = true;
    }
  }
  endLastValue() {
    this.value = this.max;
    if (!this.subBtnStateEffect) {
      this.subBtnStateEffect = true;
      this.subOpacity = u.j4;
      this.subBtnEnabled = true;
    }
  }
  updateButtonStatus() {
    if (this.value <= this.min) {
      if (!this.addBtnStateEffect && this.max != this.min) {
        this.addBtnStateEffect = true;
        this.addOpacity = u.j4;
        this.addBtnEnabled = true;
      }
      this.subOpacity = u.l4;
      this.subBtnStateEffect = false;
      this.subBtnEnabled = false;
    }
    if (this.value >= this.max) {
      if (!this.subBtnStateEffect && this.max != this.min) {
        this.subBtnStateEffect = true;
        this.subOpacity = u.j4;
        this.subBtnEnabled = true;
      }
      this.addOpacity = u.l4;
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
      let q1 = focusControl.requestFocus(key);
      if (q1) {
        console.log('Request success');
      } else {
        console.log('Request failed');
      }
    });
  }
  focusCurrentText(text) {
    if (text === i.TEXT1) {
      if (this.focusText === i.NONE) {
        this.focusText = i.TEXT1;
      }
      if (!this.hasFocusText1) {
        this.hasFocusText1 = true;
      }
    } else if (text === i.TEXT2) {
      if (this.focusText === i.NONE) {
        this.focusText = i.TEXT2;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (text === i.TEXT3) {
      if (this.focusText === i.NONE) {
        this.focusText = i.TEXT3;
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
      return u.e3;
    }
  }
  getAccessibilityResource(resource) {
    let p1 = '';
    try {
      if (typeof resource === 'string') {
        p1 = resource;
      } else {
        p1 = getContext()?.resourceManager?.getStringSync(resource?.id);
      }
    } catch (error) {
      let code = error.code;
      let message = error.message;
      console.log(
        `Get accessility resource error code:${code} message:${message}`
      );
    }
    return p1;
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
            RelativeContainer.height(u.f3);
          }, RelativeContainer);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.numberStyleOptions.label);
            Text.direction(this.counterDirection);
            Text.fontSize(u.o2);
            Text.maxFontScale(u.m4);
            Text.fontColor(u.e2);
            Text.margin({
              start: LengthMetrics.vp(this.resourceToVp(u.u2)),
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
            Row.height(u.h3);
            Row.margin({
              end: LengthMetrics.vp(this.resourceToVp(u.v2)),
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
            Stack.width(u.h3);
            Stack.height(u.h3);
            Stack.borderRadius(u.i3);
            Stack.borderWidth(this.subBtnFocusWidh);
            Stack.borderColor(u.d2);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(u.h2);
            Image.direction(this.counterDirection);
            Image.width(u.g3);
            Image.height(u.g3);
            Image.fillColor(u.c2);
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
            Button.width(u.h3);
            Button.height(u.h3);
            Button.responseRegion({
              x: u.q3,
              y: u.r3,
              width: '150%',
              height: '150%',
            });
            Button.groupDefaultFocus(true);
            Button.backgroundColor(u.b2);
            Button.opacity(this.subOpacity);
            Button.enabled(this.subBtnEnabled);
            Button.key('ListSubButton' + this.timeStamp.toString());
            Button.onKeyEvent((event) => {
              this.subBtnFocusWidh = u.l2;
              if (event.keyCode === a1.y4) {
                this.resetFocusButton();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_HOME
              ) {
                event.stopPropagation();
                this.homeFirstValue();
                this.focusWithTarget(
                  'ListAddButton' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_END
              ) {
                event.stopPropagation();
                if (this.addBtnStateEffect) {
                  this.addBtnStateEffect = false;
                  this.addOpacity = u.l4;
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
                this.subBtnFocusWidh = u.m2;
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
              } catch (o1) {
                let code = o1.code;
                let message = o1.message;
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
              this.subBtnFocusWidh = u.m2;
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
              } catch (n1) {
                let code = n1.code;
                let message = n1.message;
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
              this.subBtnFocusWidh = u.l2;
              this.onFocusDecrease && this.onFocusDecrease();
              this.updateButtonStatus();
            });
            Button.onBlur(() => {
              this.subBtnFocusWidh = u.m2;
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
                    ) + this.value.toString()
                  );
                  Text.direction(this.counterDirection);
                  Text.width(this.textWidth.toString());
                  Text.textAlign(TextAlign.Center);
                  Text.fontSize(u.q2);
                  Text.maxFontScale(u.n4);
                  Text.fontColor(u.e2);
                  Text.margin({
                    start: LengthMetrics.vp(u.l3),
                    end: LengthMetrics.vp(u.l3),
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
                    ) + this.value.toString()
                  );
                  Text.direction(this.counterDirection);
                  Text.textAlign(TextAlign.Center);
                  Text.fontSize(u.q2);
                  Text.maxFontScale(u.n4);
                  Text.fontColor(u.e2);
                  Text.margin({
                    start: LengthMetrics.vp(u.l3),
                    end: LengthMetrics.vp(u.l3),
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
            Stack.width(u.h3);
            Stack.height(u.h3);
            Stack.borderRadius(u.i3);
            Stack.borderWidth(this.addBtnFocusWidh);
            Stack.borderColor(u.d2);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(u.g2);
            Image.direction(this.counterDirection);
            Image.width(u.g3);
            Image.height(u.g3);
            Image.fillColor(u.c2);
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
            Button.width(u.h3);
            Button.height(u.h3);
            Button.responseRegion({
              x: u.q3,
              y: u.r3,
              width: '150%',
              height: '150%',
            });
            Button.backgroundColor(u.b2);
            Button.opacity(this.addOpacity);
            Button.enabled(this.addBtnEnabled);
            Button.key('ListAddButton' + this.timeStamp.toString());
            Button.onKeyEvent((event) => {
              this.addBtnFocusWidh = u.l2;
              if (event.keyCode === a1.y4) {
                this.resetFocusButton();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_HOME
              ) {
                event.stopPropagation();
                this.homeFirstValue();
                if (this.subBtnStateEffect) {
                  this.subBtnStateEffect = false;
                  this.subOpacity = u.l4;
                  this.subBtnEnabled = false;
                }
                this.focusWithTarget(
                  'ListAddButton' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_END
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
                this.addBtnFocusWidh = u.m2;
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
              } catch (m1) {
                let code = m1.code;
                let message = m1.message;
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
              this.addBtnFocusWidh = u.m2;
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
              } catch (l1) {
                let code = l1.code;
                let message = l1.message;
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
              this.addBtnFocusWidh = u.l2;
              this.onFocusIncrease && this.onFocusIncrease();
              this.updateButtonStatus();
            });
            Button.onBlur(() => {
              this.addBtnFocusWidh = u.m2;
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
            Row.height(u.z2);
            Row.align(Alignment.Center);
            Row.borderWidth(u.a3);
            Row.borderColor(u.f2);
            Row.borderRadius(u.c3);
          }, Row);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.width(u.b3);
            Stack.height(u.b3);
            Stack.borderRadius(u.s3);
            Stack.borderWidth(this.subBtnFocusWidh);
            Stack.borderColor(u.d2);
            Stack.margin({
              start: LengthMetrics.vp(this.resourceToVp(u.d3)),
            });
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(u.h2);
            Image.direction(this.counterDirection);
            Image.width(u.w2);
            Image.height(u.w2);
            Image.fillColor(u.c2);
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
            Button.width(u.b3);
            Button.height(u.b3);
            Button.backgroundColor(u.b2);
            Button.opacity(this.subOpacity);
            Button.enabled(this.subBtnEnabled);
            Button.key('CompactSubButton' + this.timeStamp.toString());
            Button.onKeyEvent((event) => {
              this.subBtnFocusWidh = u.l2;
              if (event.keyCode === a1.y4) {
                this.resetFocusButton();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_HOME
              ) {
                event.stopPropagation();
                this.homeFirstValue();
                this.focusWithTarget(
                  'CompactAddButton' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_END
              ) {
                event.stopPropagation();
                this.endLastValue();
                if (this.addBtnStateEffect) {
                  this.addBtnStateEffect = false;
                  this.addOpacity = u.l4;
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
                this.subBtnFocusWidh = u.m2;
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
              } catch (k1) {
                let code = k1.code;
                let message = k1.message;
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
                this.subBtnFocusWidh = u.m2;
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
              } catch (j1) {
                let code = j1.code;
                let message = j1.message;
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
              this.subBtnFocusWidh = u.l2;
              this.onFocusDecrease && this.onFocusDecrease();
              this.updateButtonStatus();
            });
            Button.onBlur(() => {
              this.subBtnFocusWidh = u.m2;
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
                    ) + this.value.toString()
                  );
                  Text.textAlign(TextAlign.Center);
                  Text.fontSize(u.t2);
                  Text.maxFontScale(u.n4);
                  Text.fontColor(u.e2);
                  Text.width(this.textWidth.toString());
                  Text.margin({
                    start: LengthMetrics.vp(u.u3),
                    end: LengthMetrics.vp(u.u3),
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
                    ) + this.value.toString()
                  );
                  Text.direction(this.counterDirection);
                  Text.textAlign(TextAlign.Center);
                  Text.fontSize(u.t2);
                  Text.maxFontScale(u.n4);
                  Text.fontColor(u.e2);
                  Text.margin({
                    start: LengthMetrics.vp(u.u3),
                    end: LengthMetrics.vp(u.u3),
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
            Stack.width(u.b3);
            Stack.height(u.b3);
            Stack.borderRadius(u.s3);
            Stack.borderWidth(this.addBtnFocusWidh);
            Stack.borderColor(u.d2);
            Stack.margin({
              end: LengthMetrics.vp(this.resourceToVp(u.d3)),
            });
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(u.g2);
            Image.direction(this.counterDirection);
            Image.width(u.w2);
            Image.height(u.w2);
            Image.fillColor(u.c2);
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
            Button.width(u.b3);
            Button.height(u.b3);
            Button.backgroundColor(u.b2);
            Button.opacity(this.addOpacity);
            Button.enabled(this.addBtnEnabled);
            Button.key('CompactAddButton' + this.timeStamp.toString());
            Button.onKeyEvent((event) => {
              this.addBtnFocusWidh = u.l2;
              if (event.keyCode === a1.y4) {
                this.resetFocusButton();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_HOME
              ) {
                event.stopPropagation();
                this.homeFirstValue();
                if (this.subBtnStateEffect) {
                  this.subBtnStateEffect = false;
                  this.subOpacity = u.l4;
                  this.subBtnEnabled = false;
                }
                this.focusWithTarget(
                  'CompactAddButton' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_END
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
                this.addBtnFocusWidh = u.m2;
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
              } catch (i1) {
                let code = i1.code;
                let message = i1.message;
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
                this.addBtnFocusWidh = u.m2;
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
              } catch (h1) {
                let code = h1.code;
                let message = h1.message;
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
              this.addBtnFocusWidh = u.l2;
              this.onFocusIncrease && this.onFocusIncrease();
              this.updateButtonStatus();
            });
            Button.onBlur(() => {
              this.addBtnFocusWidh = u.m2;
              this.onBlurIncrease && this.onBlurIncrease();
            });
          }, Button);
          Button.pop();
          Stack.pop();
          Row.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.numberStyleOptions.label);
            Text.direction(this.counterDirection);
            Text.margin({ top: u.v3 });
            Text.fontSize(u.s2);
            Text.maxFontScale(u.m4);
            Text.fontColor(u.e2);
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
            Row.height(u.b4);
            Row.borderWidth(u.a3);
            Row.borderColor(u.f2);
            Row.borderRadius(u.e4);
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
                    start: LengthMetrics.vp(u.i4),
                    end: LengthMetrics.vp(u.i4),
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
                  TextInput.fontColor(this.hasFocusText1 ? Color.White : u.e2);
                  TextInput.maxLength(this.getMaxLength());
                  TextInput.backgroundColor(
                    this.hasFocusText1 ? u.d2 : Color.Transparent
                  );
                  TextInput.key('InlineTextInput' + this.timeStamp.toString());
                  TextInput.onKeyEvent((event) => {
                    this.focusCurrentText(i.TEXT1);
                    if (event.keyCode === a1.y4) {
                      this.resetFocusText();
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === a1.KEYCODE_DPAD_UP
                    ) {
                      this.addValue();
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === a1.KEYCODE_MOVE_HOME
                    ) {
                      event.stopPropagation();
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === a1.KEYCODE_MOVE_END
                    ) {
                      event.stopPropagation();
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === a1.KEYCODE_DPAD_DOWN
                    ) {
                      this.subValue();
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === a1.KEYCODE_DPAD_LEFT
                    ) {
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === a1.KEYCODE_DPAD_RIGHT
                    ) {
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                      event.stopPropagation();
                    }
                  });
                  TextInput.onChange((value) => {
                    this.inputValue = value;
                    for (let g1 = 0; g1 < value.length; g1++) {
                      let c = value[g1];
                      if (c === '+' || c === '*' || c === '#') {
                        this.value -= 1;
                        this.value += 1;
                        this.inputValue = this.value.toString();
                        return;
                      }
                      if (c === '-' && g1 !== 0) {
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
                    this.focusText = i.TEXT1;
                    this.hasFocusText1 = true;
                    this.controller1.caretPosition(
                      this.value.toString().length
                    );
                  });
                  TextInput.onBlur(() => {
                    this.focusText = i.NONE;
                    this.hasFocusText1 = false;
                  });
                  TextInput.onClick((event) => {
                    this.focusText = i.TEXT1;
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
                    start: LengthMetrics.vp(u.i4),
                    end: LengthMetrics.vp(u.i4),
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
                  TextInput.fontColor(this.hasFocusText1 ? Color.White : u.e2);
                  TextInput.maxLength(this.getMaxLength());
                  TextInput.backgroundColor(
                    this.hasFocusText1 ? u.d2 : Color.Transparent
                  );
                  TextInput.key('InlineTextInput' + this.timeStamp.toString());
                  TextInput.onKeyEvent((event) => {
                    this.focusCurrentText(i.TEXT1);
                    if (event.keyCode === a1.y4) {
                      this.resetFocusText();
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === a1.KEYCODE_DPAD_UP
                    ) {
                      this.addValue();
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === a1.KEYCODE_DPAD_DOWN
                    ) {
                      this.subValue();
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === a1.KEYCODE_DPAD_LEFT
                    ) {
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                      event.stopPropagation();
                    }
                    if (
                      event.type === KeyType.Down &&
                      event.keyCode === a1.KEYCODE_DPAD_RIGHT
                    ) {
                      this.focusWithTarget(
                        'InlineTextInput' + this.timeStamp.toString()
                      );
                      event.stopPropagation();
                    }
                  });
                  TextInput.onChange((value) => {
                    this.inputValue = value;
                    for (let f1 = 0; f1 < value.length; f1++) {
                      let c = value[f1];
                      if (c === '+' || c === '*' || c === '#') {
                        this.value -= 1;
                        this.value += 1;
                        this.inputValue = this.value.toString();
                        return;
                      }
                      if (c === '-' && f1 !== 0) {
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
                    this.focusText = i.TEXT1;
                    this.hasFocusText1 = true;
                    this.controller1.caretPosition(
                      this.value.toString().length
                    );
                  });
                  TextInput.onBlur(() => {
                    this.focusText = i.NONE;
                    this.hasFocusText1 = false;
                  });
                  TextInput.onClick((event) => {
                    this.focusText = i.TEXT1;
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
            Column.width(u.c4);
            Column.height(u.b4);
            Column.borderWidth({ start: LengthMetrics.vp(u.n2) });
            Column.borderColor(u.f2);
          }, Column);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.counterDirection);
            Stack.width(u.c4);
            Stack.height(u.d4);
            Stack.padding({ top: '1vp' });
            Stack.borderWidth({ bottom: '1vp' });
            Stack.borderColor(u.f2);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Rect.create();
            Rect.direction(this.counterDirection);
            Rect.width(u.f4);
            Rect.height(u.g4);
            Rect.radius([
              ['0vp', '0vp'],
              [u.e4, u.e4],
              ['0vp', '0vp'],
              ['0vp', '0vp'],
            ]);
            Rect.strokeWidth(this.addBtnFocusWidh);
            Rect.stroke(u.d2);
            Rect.margin({ end: LengthMetrics.vp(2) });
            Rect.fillOpacity(0);
          }, Rect);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(u.i2);
            Image.direction(this.counterDirection);
            Image.width(u.y3);
            Image.height(u.z3);
            Image.fillColor(u.c2);
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
            Button.width(u.c4);
            Button.height(u.d4);
            Button.backgroundColor(Color.Transparent);
            Button.opacity(this.addOpacity);
            Button.enabled(this.addBtnEnabled);
            Button.onClick((event) => {
              this.addValue();
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.addBtnFocusWidh = u.m2;
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
              } catch (e1) {
                let code = e1.code;
                let message = e1.message;
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
              this.addBtnFocusWidh = u.m2;
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
              } catch (d1) {
                let code = d1.code;
                let message = d1.message;
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
              this.addBtnFocusWidh = u.l2;
              this.onFocusIncrease && this.onFocusIncrease();
            });
            Button.onBlur(() => {
              this.addBtnFocusWidh = u.m2;
              this.onBlurIncrease && this.onBlurIncrease();
            });
          }, Button);
          Button.pop();
          Stack.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.counterDirection);
            Stack.width(u.c4);
            Stack.height(u.d4);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Rect.create();
            Rect.direction(this.counterDirection);
            Rect.width(u.f4);
            Rect.height(u.g4);
            Rect.radius([
              ['0vp', '0vp'],
              ['0vp', '0vp'],
              [u.e4, u.e4],
              ['0vp', '0vp'],
            ]);
            Rect.strokeWidth(this.subBtnFocusWidh);
            Rect.stroke(u.d2);
            Rect.margin({
              top: LengthMetrics.vp(1),
              end: LengthMetrics.vp(1),
              bottom: LengthMetrics.vp(2),
            });
            Rect.fillOpacity(0);
          }, Rect);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(u.j2);
            Image.direction(this.counterDirection);
            Image.width(u.y3);
            Image.height(u.z3);
            Image.fillColor(u.c2);
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
            Button.width(u.c4);
            Button.height(u.d4);
            Button.backgroundColor(Color.Transparent);
            Button.opacity(this.subOpacity);
            Button.enabled(this.subBtnEnabled);
            Button.onClick((event) => {
              this.subValue();
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.subBtnFocusWidh = u.m2;
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
              } catch (c1) {
                let code = c1.code;
                let message = c1.message;
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
              this.subBtnFocusWidh = u.m2;
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
              } catch (b1) {
                let code = b1.code;
                let message = b1.message;
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
              this.subBtnFocusWidh = u.l2;
              this.onFocusDecrease && this.onFocusDecrease();
            });
            Button.onBlur(() => {
              this.subBtnFocusWidh = u.m2;
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
            Row.height(u.b4);
            Row.borderWidth(u.a3);
            Row.borderColor(u.f2);
            Row.borderRadius(u.e4);
            Row.clip(true);
          }, Row);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.direction(this.counterDirection);
            Row.width('92vp');
            Row.height(u.b4);
            Row.margin({
              start: LengthMetrics.vp(u.h4),
              end: LengthMetrics.vp(u.h4),
            });
          }, Row);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            TextInput.create({
              text: this.hasInputText1
                ? this.inputYear.toString()
                : this.getYear(),
              controller: this.controller1,
            });
            TextInput.accessibilityText(this.year.toString() + this.yearStr);
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
            TextInput.fontColor(this.hasFocusText1 ? Color.White : u.e2);
            TextInput.maxLength(5);
            TextInput.padding(0);
            TextInput.backgroundColor(
              this.hasFocusText1 ? u.d2 : Color.Transparent
            );
            TextInput.width('38vp');
            TextInput.height('20vp');
            TextInput.borderRadius(0);
            TextInput.borderWidth(0);
            TextInput.key('DateTextInput1' + this.timeStamp.toString());
            TextInput.onKeyEvent((event) => {
              this.focusCurrentText(i.TEXT1);
              if (event.keyCode === a1.y4) {
                this.resetFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_DPAD_UP
              ) {
                this.addDate();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_DPAD_DOWN
              ) {
                this.subDate();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_HOME
              ) {
                this.homeFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_END
              ) {
                this.endFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_DPAD_LEFT
              ) {
                this.focusWithTarget(
                  'DateTextInput1' + this.timeStamp.toString()
                );
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_DPAD_RIGHT
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
              this.focusText = i.TEXT1;
              this.hasFocusText1 = true;
              this.updateDateEnableSate();
              this.controller1.caretPosition(this.getYear().length);
            });
            TextInput.onBlur(() => {
              this.focusText = i.NONE;
              this.hasFocusText1 = false;
              this.updateDateEnableSate();
            });
            TextInput.onClick((event) => {
              this.focusText = i.TEXT1;
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
            Text.fontSize(u.t2);
            Text.maxFontScale(u.n4);
            Text.fontColor(u.e2);
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
            TextInput.accessibilityText(this.month.toString() + this.monthStr);
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
            TextInput.fontColor(this.hasFocusText2 ? Color.White : u.e2);
            TextInput.maxLength(3);
            TextInput.padding(0);
            TextInput.backgroundColor(
              this.hasFocusText2 ? u.d2 : Color.Transparent
            );
            TextInput.width('19vp');
            TextInput.height('20vp');
            TextInput.borderRadius(0);
            TextInput.key('DateTextInput2' + this.timeStamp.toString());
            TextInput.onKeyEvent((event) => {
              this.focusCurrentText(i.TEXT2);
              if (event.keyCode === a1.y4) {
                this.resetFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_DPAD_DOWN
              ) {
                this.subDate();
                this.updateDay();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_DPAD_UP
              ) {
                this.addDate();
                this.updateDay();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_HOME
              ) {
                this.homeFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_END
              ) {
                this.endFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_DPAD_LEFT
              ) {
                this.focusWithTarget(
                  'DateTextInput1' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_DPAD_RIGHT
              ) {
                this.focusWithTarget(
                  'DateTextInput3' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_TAB
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
              this.focusText = i.TEXT2;
              this.hasFocusText2 = true;
              this.controller2.caretPosition(
                this.convertNumberToString(this.month).length
              );
            });
            TextInput.onBlur(() => {
              this.focusText = i.NONE;
              this.hasFocusText2 = false;
            });
            TextInput.onClick((event) => {
              this.focusText = i.TEXT2;
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
            Text.fontSize(u.t2);
            Text.maxFontScale(u.n4);
            Text.fontColor(u.e2);
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
            TextInput.accessibilityText(this.day.toString() + this.dayStr);
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
            TextInput.fontColor(this.hasFocusText3 ? Color.White : u.e2);
            TextInput.maxLength(3);
            TextInput.padding(0);
            TextInput.backgroundColor(
              this.hasFocusText3 ? u.d2 : Color.Transparent
            );
            TextInput.width('19vp');
            TextInput.height('20vp');
            TextInput.borderRadius(0);
            TextInput.key('DateTextInput3' + this.timeStamp.toString());
            TextInput.onKeyEvent((event) => {
              this.focusCurrentText(i.TEXT3);
              if (event.keyCode === a1.y4) {
                this.resetFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_DPAD_DOWN
              ) {
                this.subDate();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_DPAD_UP
              ) {
                this.addDate();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_HOME
              ) {
                this.homeFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_MOVE_END
              ) {
                this.endFocusText();
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_DPAD_LEFT
              ) {
                this.focusWithTarget(
                  'DateTextInput2' + this.timeStamp.toString()
                );
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_DPAD_RIGHT
              ) {
                this.focusWithTarget(
                  'DateTextInput3' + this.timeStamp.toString()
                );
                event.stopPropagation();
              }
              if (
                event.type === KeyType.Down &&
                event.keyCode === a1.KEYCODE_TAB
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
              this.focusText = i.TEXT3;
              this.hasFocusText3 = true;
              this.controller3.caretPosition(
                this.convertNumberToString(this.day).length
              );
            });
            TextInput.onBlur(() => {
              this.focusText = i.NONE;
              this.hasFocusText3 = false;
            });
            TextInput.onClick((event) => {
              this.focusText = i.TEXT3;
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
            Column.width(u.c4);
            Column.height(u.b4);
            Column.borderWidth({ start: LengthMetrics.vp(u.n2) });
            Column.borderColor(u.f2);
          }, Column);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.width(u.c4);
            Stack.height(u.d4);
            Stack.padding({ top: '1vp' });
            Stack.borderWidth({ bottom: '1vp' });
            Stack.borderColor(u.f2);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Rect.create();
            Rect.direction(this.counterDirection);
            Rect.width(u.f4);
            Rect.height(u.g4);
            Rect.radius([
              ['0vp', '0vp'],
              [u.e4, u.e4],
              ['0vp', '0vp'],
              ['0vp', '0vp'],
            ]);
            Rect.strokeWidth(this.addBtnFocusWidh);
            Rect.stroke(u.d2);
            Rect.margin({ end: LengthMetrics.vp(1) });
            Rect.fillOpacity(0);
          }, Rect);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(u.i2);
            Image.direction(this.counterDirection);
            Image.width(u.y3);
            Image.height(u.z3);
            Image.fillColor(u.c2);
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
            Button.width(u.c4);
            Button.height(u.d4);
            Button.backgroundColor(Color.Transparent);
            Button.opacity(this.addOpacity);
            Button.enabled(this.addBtnEnabled);
            Button.onClick((event) => {
              this.accessibilityBroadcastAddDate();
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.addBtnFocusWidh = u.m2;
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((event) => {
              if (event.repeat) {
                this.addDate();
              }
              this.addBtnFocusWidh = u.m2;
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
              this.addBtnFocusWidh = u.l2;
              this.onFocusIncrease && this.onFocusIncrease();
            });
            Button.onBlur(() => {
              this.addBtnFocusWidh = u.m2;
              this.onBlurIncrease && this.onBlurIncrease();
            });
          }, Button);
          Button.pop();
          Stack.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.width(u.c4);
            Stack.height(u.d4);
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Rect.create();
            Rect.direction(this.counterDirection);
            Rect.width(u.f4);
            Rect.height(u.g4);
            Rect.radius([
              ['0vp', '0vp'],
              ['0vp', '0vp'],
              [u.e4, u.e4],
              ['0vp', '0vp'],
            ]);
            Rect.strokeWidth(this.subBtnFocusWidh);
            Rect.stroke(u.d2);
            Rect.margin({
              top: LengthMetrics.vp(1),
              end: LengthMetrics.vp(1),
              bottom: LengthMetrics.vp(2),
            });
            Rect.fillOpacity(0);
          }, Rect);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(u.j2);
            Image.direction(this.counterDirection);
            Image.width(u.y3);
            Image.height(u.z3);
            Image.fillColor(u.c2);
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
            Button.width(u.c4);
            Button.height(u.d4);
            Button.backgroundColor(Color.Transparent);
            Button.opacity(this.subOpacity);
            Button.enabled(this.subBtnEnabled);
            Button.onClick((event) => {
              this.accessibilityBroadcastSubDate();
              if (
                event.source === SourceType.Mouse ||
                event.source === SourceType.TouchScreen
              ) {
                this.subBtnFocusWidh = u.m2;
              }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((event) => {
              if (event.repeat) {
                this.subDate();
              }
              this.subBtnFocusWidh = u.m2;
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
              this.subBtnFocusWidh = u.l2;
              this.onFocusDecrease && this.onFocusDecrease();
            });
            Button.onBlur(() => {
              this.subBtnFocusWidh = u.m2;
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
