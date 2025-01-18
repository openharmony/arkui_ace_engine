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
(function (CounterType) {
    CounterType[CounterType["LIST"] = 0] = "LIST";
    CounterType[CounterType["COMPACT"] = 1] = "COMPACT";
    CounterType[CounterType["INLINE"] = 2] = "INLINE";
    CounterType[CounterType["INLINE_DATE"] = 3] = "INLINE_DATE";
})(CounterType || (CounterType = {}));
var o;
(function (h1) {
    h1[h1["NONE"] = 0] = "NONE";
    h1[h1["TEXT1"] = 1] = "TEXT1";
    h1[h1["TEXT2"] = 2] = "TEXT2";
    h1[h1["TEXT3"] = 3] = "TEXT3";
})(o || (o = {}));
export class t {
}
export class u extends t {
}
export class a1 extends u {
}
export class DateData {
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
export class b1 extends t {
}
export class CounterOptions {
    constructor() {
        this.type = CounterType.LIST;
    }
}
class c1 {
}
c1.e1 = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.f1 = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.g1 = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.h1 = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.i1 = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_component_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.j1 = { "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_add"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.l1 = { "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_minus"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.m1 = { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_arrow_up'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.n1 = { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_arrow_down'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.o1 = '2vp';
c1.q1 = '0vp';
c1.s1 = 1;
c1.t1 = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.u1 = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.v1 = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.w1 = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.z1 = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_default_padding_start'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.a2 = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_default_padding_end'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.b2 = { "id": -1, "type": 10002, params: ['sys.float.button_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.c2 = { "id": -1, "type": 10002, params: ['sys.float.container_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.d2 = { "id": -1, "type": 10002, params: ['sys.float.border_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.e2 = { "id": -1, "type": 10002, params: ['sys.float.button_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.f2 = { "id": -1, "type": 10002, params: ['sys.float.container_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.g2 = { "id": -1, "type": 10002, params: ['sys.float.button_container_margin'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
c1.h2 = 12;
c1.i2 = '48vp';
c1.j2 = '20vp';
c1.l2 = '32vp';
c1.m2 = '16vp';
c1.n2 = '8vp';
c1.o2 = 8;
c1.q2 = '30vp';
c1.s2 = '15vp';
c1.t2 = '-8vp';
c1.u2 = '-8vp';
c1.v2 = '12vp';
c1.w2 = '10vp';
c1.z2 = 10;
c1.a3 = '8vp';
c1.b3 = '22vp';
c1.c3 = '11vp';
c1.d3 = '24vp';
c1.e3 = '12vp';
c1.f3 = '12vp';
c1.g3 = '32vp';
c1.h3 = '32vp';
c1.i3 = '16vp';
c1.j3 = '8vp';
c1.l3 = '28vp';
c1.m3 = '13.5vp';
c1.n3 = 12;
c1.q3 = 12;
c1.r3 = 1;
c1.s3 = 0.4;
c1.t3 = 2;
c1.u3 = 1;
class d1 {
}
d1.v3 = 5000;
d1.w3 = 1;
d1.x3 = 1;
d1.y3 = 1;
d1.z3 = 1;
d1.a4 = 10;
d1.b4 = 1;
d1.c4 = 12;
d1.d4 = 1;
d1.KEYCODE_DPAD_UP = 2012;
d1.KEYCODE_DPAD_DOWN = 2013;
d1.KEYCODE_DPAD_LEFT = 2014;
d1.KEYCODE_DPAD_RIGHT = 2015;
d1.KEYCODE_MOVE_HOME = 2081;
d1.KEYCODE_MOVE_END = 2082;
d1.KEYCODE_TAB = 2049;
d1.e4 = 2070;
d1.f4 = 0;
d1.g4 = 999;
d1.h4 = 1;
d1.i4 = 2;
d1.j4 = 3;
d1.l4 = 4;
d1.m4 = 5;
d1.n4 = 6;
d1.o4 = 7;
d1.q4 = 8;
d1.r4 = 9;
d1.s4 = 10;
d1.t4 = 11;
d1.u4 = 12;
d1.v4 = 31;
d1.w4 = 30;
d1.x4 = 28;
d1.y4 = 29;
d1.z4 = 4;
d1.a5 = 100;
d1.b5 = 400;
export class CounterComponent extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.c5 = new SynchedPropertyObjectOneWayPU(params.options, this, "options");
        this.d5 = new ObservedPropertySimplePU(-1, this, "type");
        this.e5 = new ObservedPropertySimplePU(Direction.Auto, this, "counterDirection");
        this.f5 = new ObservedPropertySimplePU(HoverEffect.Auto, this, "choverEffect");
        this.g5 = new ObservedPropertySimplePU(true, this, "focusEnable");
        this.h5 = new ObservedPropertySimplePU(d1.z3, this, "step");
        this.i5 = new ObservedPropertySimplePU('0', this, "inputValue");
        this.j5 = new ObservedPropertySimplePU(d1.w3, this, "inputYear");
        this.k5 = new ObservedPropertySimplePU(0, this, "inputMoon");
        this.l5 = new ObservedPropertySimplePU(0, this, "inputDay");
        this.m5 = new ObservedPropertySimplePU(0, this, "inputHour");
        this.n5 = new ObservedPropertySimplePU(0, this, "inputMinute");
        this.o5 = new ObservedPropertySimplePU(0, this, "inputSecond");
        this.p5 = new ObservedPropertySimplePU(c1.r3, this, "subOpacity");
        this.q5 = new ObservedPropertySimplePU(c1.r3, this, "addOpacity");
        this.r5 = new ObservedPropertySimplePU(true, this, "subBtnStateEffect");
        this.s5 = new ObservedPropertySimplePU(true, this, "addBtnStateEffect");
        this.t5 = new ObservedPropertySimplePU(o.NONE, this, "focusText");
        this.u5 = new ObservedPropertySimplePU(false, this, "hasFocusText1");
        this.v5 = new ObservedPropertySimplePU(false, this, "hasFocusText2");
        this.w5 = new ObservedPropertySimplePU(false, this, "hasFocusText3");
        this.x5 = new ObservedPropertySimplePU('0vp', this, "subBtnFocusWidh");
        this.y5 = new ObservedPropertySimplePU('0vp', this, "addBtnFocusWidh");
        this.z5 = new ObservedPropertySimplePU(0, this, "value");
        this.a6 = new ObservedPropertySimplePU(0, this, "year");
        this.b6 = new ObservedPropertySimplePU(0, this, "month");
        this.c6 = new ObservedPropertySimplePU(0, this, "day");
        this.d6 = new ObservedPropertySimplePU(0, this, "hour");
        this.e6 = new ObservedPropertySimplePU(0, this, "minute");
        this.f6 = new ObservedPropertySimplePU(0, this, "second");
        this.g6 = new ObservedPropertySimplePU(true, this, "subBtnEnabled");
        this.h6 = new ObservedPropertySimplePU(true, this, "addBtnEnabled");
        this.i6 = new ObservedPropertySimplePU(false, this, "hasInputText1");
        this.j6 = new ObservedPropertySimplePU(false, this, "hasInputText2");
        this.k6 = new ObservedPropertySimplePU(false, this, "hasInputText3");
        this.l6 = new ObservedPropertySimplePU(0, this, "textWidth");
        this.m6 = new ObservedPropertySimplePU(d1.f4, this, "min");
        this.n6 = new ObservedPropertySimplePU(d1.g4, this, "max");
        this.maxYear = d1.v3;
        this.minYear = d1.w3;
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
        this.numberStyleOptions = new a1();
        this.dateStyleOptions = new b1();
        this.inlineStyleOptions = new u();
        this.timeStamp = 0;
        this.hasTextWidth = false;
        this.controller1 = new TextInputController();
        this.controller2 = new TextInputController();
        this.controller3 = new TextInputController();
        this.initFlag = true;
        this.setInitiallyProvidedValue(params);
        this.declareWatch("options", this.onOptionsChange);
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
    }
    updateStateVars(params) {
        this.c5.reset(params.options);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.c5.purgeDependencyOnElmtId(rmElmtId);
        this.d5.purgeDependencyOnElmtId(rmElmtId);
        this.e5.purgeDependencyOnElmtId(rmElmtId);
        this.f5.purgeDependencyOnElmtId(rmElmtId);
        this.g5.purgeDependencyOnElmtId(rmElmtId);
        this.h5.purgeDependencyOnElmtId(rmElmtId);
        this.i5.purgeDependencyOnElmtId(rmElmtId);
        this.j5.purgeDependencyOnElmtId(rmElmtId);
        this.k5.purgeDependencyOnElmtId(rmElmtId);
        this.l5.purgeDependencyOnElmtId(rmElmtId);
        this.m5.purgeDependencyOnElmtId(rmElmtId);
        this.n5.purgeDependencyOnElmtId(rmElmtId);
        this.o5.purgeDependencyOnElmtId(rmElmtId);
        this.p5.purgeDependencyOnElmtId(rmElmtId);
        this.q5.purgeDependencyOnElmtId(rmElmtId);
        this.r5.purgeDependencyOnElmtId(rmElmtId);
        this.s5.purgeDependencyOnElmtId(rmElmtId);
        this.t5.purgeDependencyOnElmtId(rmElmtId);
        this.u5.purgeDependencyOnElmtId(rmElmtId);
        this.v5.purgeDependencyOnElmtId(rmElmtId);
        this.w5.purgeDependencyOnElmtId(rmElmtId);
        this.x5.purgeDependencyOnElmtId(rmElmtId);
        this.y5.purgeDependencyOnElmtId(rmElmtId);
        this.z5.purgeDependencyOnElmtId(rmElmtId);
        this.a6.purgeDependencyOnElmtId(rmElmtId);
        this.b6.purgeDependencyOnElmtId(rmElmtId);
        this.c6.purgeDependencyOnElmtId(rmElmtId);
        this.d6.purgeDependencyOnElmtId(rmElmtId);
        this.e6.purgeDependencyOnElmtId(rmElmtId);
        this.f6.purgeDependencyOnElmtId(rmElmtId);
        this.g6.purgeDependencyOnElmtId(rmElmtId);
        this.h6.purgeDependencyOnElmtId(rmElmtId);
        this.i6.purgeDependencyOnElmtId(rmElmtId);
        this.j6.purgeDependencyOnElmtId(rmElmtId);
        this.k6.purgeDependencyOnElmtId(rmElmtId);
        this.l6.purgeDependencyOnElmtId(rmElmtId);
        this.m6.purgeDependencyOnElmtId(rmElmtId);
        this.n6.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.c5.aboutToBeDeleted();
        this.d5.aboutToBeDeleted();
        this.e5.aboutToBeDeleted();
        this.f5.aboutToBeDeleted();
        this.g5.aboutToBeDeleted();
        this.h5.aboutToBeDeleted();
        this.i5.aboutToBeDeleted();
        this.j5.aboutToBeDeleted();
        this.k5.aboutToBeDeleted();
        this.l5.aboutToBeDeleted();
        this.m5.aboutToBeDeleted();
        this.n5.aboutToBeDeleted();
        this.o5.aboutToBeDeleted();
        this.p5.aboutToBeDeleted();
        this.q5.aboutToBeDeleted();
        this.r5.aboutToBeDeleted();
        this.s5.aboutToBeDeleted();
        this.t5.aboutToBeDeleted();
        this.u5.aboutToBeDeleted();
        this.v5.aboutToBeDeleted();
        this.w5.aboutToBeDeleted();
        this.x5.aboutToBeDeleted();
        this.y5.aboutToBeDeleted();
        this.z5.aboutToBeDeleted();
        this.a6.aboutToBeDeleted();
        this.b6.aboutToBeDeleted();
        this.c6.aboutToBeDeleted();
        this.d6.aboutToBeDeleted();
        this.e6.aboutToBeDeleted();
        this.f6.aboutToBeDeleted();
        this.g6.aboutToBeDeleted();
        this.h6.aboutToBeDeleted();
        this.i6.aboutToBeDeleted();
        this.j6.aboutToBeDeleted();
        this.k6.aboutToBeDeleted();
        this.l6.aboutToBeDeleted();
        this.m6.aboutToBeDeleted();
        this.n6.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get options() {
        return this.c5.get();
    }
    set options(newValue) {
        this.c5.set(newValue);
    }
    get type() {
        return this.d5.get();
    }
    set type(newValue) {
        this.d5.set(newValue);
    }
    get counterDirection() {
        return this.e5.get();
    }
    set counterDirection(newValue) {
        this.e5.set(newValue);
    }
    get choverEffect() {
        return this.f5.get();
    }
    set choverEffect(newValue) {
        this.f5.set(newValue);
    }
    get focusEnable() {
        return this.g5.get();
    }
    set focusEnable(newValue) {
        this.g5.set(newValue);
    }
    get step() {
        return this.h5.get();
    }
    set step(newValue) {
        this.h5.set(newValue);
    }
    get inputValue() {
        return this.i5.get();
    }
    set inputValue(newValue) {
        this.i5.set(newValue);
    }
    get inputYear() {
        return this.j5.get();
    }
    set inputYear(newValue) {
        this.j5.set(newValue);
    }
    get inputMoon() {
        return this.k5.get();
    }
    set inputMoon(newValue) {
        this.k5.set(newValue);
    }
    get inputDay() {
        return this.l5.get();
    }
    set inputDay(newValue) {
        this.l5.set(newValue);
    }
    get inputHour() {
        return this.m5.get();
    }
    set inputHour(newValue) {
        this.m5.set(newValue);
    }
    get inputMinute() {
        return this.n5.get();
    }
    set inputMinute(newValue) {
        this.n5.set(newValue);
    }
    get inputSecond() {
        return this.o5.get();
    }
    set inputSecond(newValue) {
        this.o5.set(newValue);
    }
    get subOpacity() {
        return this.p5.get();
    }
    set subOpacity(newValue) {
        this.p5.set(newValue);
    }
    get addOpacity() {
        return this.q5.get();
    }
    set addOpacity(newValue) {
        this.q5.set(newValue);
    }
    get subBtnStateEffect() {
        return this.r5.get();
    }
    set subBtnStateEffect(newValue) {
        this.r5.set(newValue);
    }
    get addBtnStateEffect() {
        return this.s5.get();
    }
    set addBtnStateEffect(newValue) {
        this.s5.set(newValue);
    }
    get focusText() {
        return this.t5.get();
    }
    set focusText(newValue) {
        this.t5.set(newValue);
    }
    get hasFocusText1() {
        return this.u5.get();
    }
    set hasFocusText1(newValue) {
        this.u5.set(newValue);
    }
    get hasFocusText2() {
        return this.v5.get();
    }
    set hasFocusText2(newValue) {
        this.v5.set(newValue);
    }
    get hasFocusText3() {
        return this.w5.get();
    }
    set hasFocusText3(newValue) {
        this.w5.set(newValue);
    }
    get subBtnFocusWidh() {
        return this.x5.get();
    }
    set subBtnFocusWidh(newValue) {
        this.x5.set(newValue);
    }
    get addBtnFocusWidh() {
        return this.y5.get();
    }
    set addBtnFocusWidh(newValue) {
        this.y5.set(newValue);
    }
    get value() {
        return this.z5.get();
    }
    set value(newValue) {
        this.z5.set(newValue);
    }
    get year() {
        return this.a6.get();
    }
    set year(newValue) {
        this.a6.set(newValue);
    }
    get month() {
        return this.b6.get();
    }
    set month(newValue) {
        this.b6.set(newValue);
    }
    get day() {
        return this.c6.get();
    }
    set day(newValue) {
        this.c6.set(newValue);
    }
    get hour() {
        return this.d6.get();
    }
    set hour(newValue) {
        this.d6.set(newValue);
    }
    get minute() {
        return this.e6.get();
    }
    set minute(newValue) {
        this.e6.set(newValue);
    }
    get second() {
        return this.f6.get();
    }
    set second(newValue) {
        this.f6.set(newValue);
    }
    get subBtnEnabled() {
        return this.g6.get();
    }
    set subBtnEnabled(newValue) {
        this.g6.set(newValue);
    }
    get addBtnEnabled() {
        return this.h6.get();
    }
    set addBtnEnabled(newValue) {
        this.h6.set(newValue);
    }
    get hasInputText1() {
        return this.i6.get();
    }
    set hasInputText1(newValue) {
        this.i6.set(newValue);
    }
    get hasInputText2() {
        return this.j6.get();
    }
    set hasInputText2(newValue) {
        this.j6.set(newValue);
    }
    get hasInputText3() {
        return this.k6.get();
    }
    set hasInputText3(newValue) {
        this.k6.set(newValue);
    }
    get textWidth() {
        return this.l6.get();
    }
    set textWidth(newValue) {
        this.l6.set(newValue);
    }
    get min() {
        return this.m6.get();
    }
    set min(newValue) {
        this.m6.set(newValue);
    }
    get max() {
        return this.n6.get();
    }
    set max(newValue) {
        this.n6.set(newValue);
    }
    getTextInputFontSize() {
        let fontSize = this.resourceToVp(c1.w1);
        let uiContext = this.getUIContext();
        let fontSizeScale = uiContext.getHostContext()?.config?.fontSizeScale ?? 1;
        if (fontSizeScale < 1) {
            return fontSize + 'fp';
        }
        else {
            return fontSize + 'vp';
        }
    }
    convertNumberToString(value) {
        if (value >= 0 && value < d1.a4) {
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
            this.onOptionsChange();
        }
    }
    updateNumberStyleOptions() {
        if (this.numberStyleOptions.label === undefined) {
            this.numberStyleOptions.label = '';
        }
        if (this.initFlag) {
            this.initFlag = false;
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
        if (this.initFlag) {
            this.initFlag = false;
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
            this.year = d1.w3;
        }
        if (this.dateStyleOptions.month !== undefined &&
            this.dateStyleOptions.month <= d1.c4 &&
            this.dateStyleOptions.month >= d1.b4) {
            if (this.month === 0) {
                this.month = this.dateStyleOptions.month;
            }
        }
        else {
            this.month = d1.x3;
        }
        if (this.dateStyleOptions.day !== undefined &&
            this.dateStyleOptions.day <= this.getDayNumber() &&
            this.dateStyleOptions.day >= d1.d4) {
            if (this.day === 0) {
                this.day = this.dateStyleOptions.day;
            }
        }
        else {
            this.day = d1.y3;
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
            if (this.options.numberOptions !== undefined) {
                this.numberStyleOptions = this.options.numberOptions;
            }
            this.updateNumberStyleOptions();
        }
        else if (this.type === CounterType.INLINE) {
            if (this.options.inlineOptions !== undefined) {
                this.inlineStyleOptions = this.options.inlineOptions;
            }
            this.updateInlineStyleOptions();
        }
        else if (this.type === CounterType.INLINE_DATE) {
            let options = this.options.dateOptions;
            if (options !== undefined) {
                options.year = options.year ? options.year : d1.w3;
                options.month = options.month ? options.month : d1.b4;
                options.day = options.day ? options.day : d1.d4;
                this.dateStyleOptions = options;
            }
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
            this.addOpacity = c1.r3;
            this.addBtnEnabled = true;
        }
        if (this.value <= this.min) {
            this.value = this.min;
            this.subOpacity = c1.s3;
            this.subBtnStateEffect = false;
            this.subBtnEnabled = false;
        }
        else {
            if (this.subOpacity === c1.s3) {
                this.subOpacity = c1.r3;
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
            if (this.focusText === o.NONE) {
                this.focusText = o.TEXT1;
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
            this.subOpacity = c1.r3;
            this.subBtnEnabled = true;
        }
        if (this.value >= this.max) {
            this.value = this.max;
            this.addOpacity = c1.s3;
            this.addBtnStateEffect = false;
            this.addBtnEnabled = false;
        }
        else {
            if (this.addOpacity === c1.s3) {
                this.addOpacity = c1.r3;
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
            case d1.h4:
            case d1.j4:
            case d1.m4:
            case d1.o4:
            case d1.q4:
            case d1.s4:
            case d1.u4:
                return d1.v4;
                break;
            case d1.l4:
            case d1.n4:
            case d1.r4:
            case d1.t4:
                return d1.w4;
                break;
            case d1.i4:
                if ((this.year % d1.z4 === 0 &&
                    this.year % d1.a5 !== 0) ||
                    this.year % d1.b5 === 0) {
                    return d1.y4;
                }
                else {
                    return d1.x4;
                }
                break;
            default:
                return d1.w4;
                break;
        }
    }
    subDate() {
        if (this.focusText === o.TEXT1) {
            if (this.subBtnStateEffect) {
                this.inputYear = this.year;
                this.year -= this.step;
                if (!this.hasFocusText1) {
                    this.hasFocusText1 = true;
                }
            }
            if (!this.addBtnStateEffect) {
                this.addBtnStateEffect = true;
                this.addOpacity = c1.r3;
                this.addBtnEnabled = true;
            }
            if (this.year <= this.minYear) {
                this.subOpacity = c1.s3;
                this.subBtnStateEffect = false;
                this.subBtnEnabled = false;
            }
            else {
                if (this.subOpacity === c1.s3) {
                    this.subOpacity = c1.r3;
                }
                if (!this.subBtnStateEffect) {
                    this.subBtnStateEffect = true;
                }
                if (!this.subBtnEnabled) {
                    this.subBtnEnabled = true;
                }
            }
        }
        else if (this.focusText === o.TEXT2) {
            this.month -= this.step % d1.c4;
            if (this.month < d1.b4) {
                this.month += d1.c4;
            }
            if (!this.hasFocusText2) {
                this.hasFocusText2 = true;
            }
        }
        else if (this.focusText === o.TEXT3) {
            this.day -= this.step % this.getDayNumber();
            if (this.day < d1.d4) {
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
        this.focusText = o.TEXT3;
        this.hasFocusText3 = true;
        this.day -= this.step % this.getDayNumber();
        if (this.day < d1.d4) {
            this.day += this.getDayNumber();
        }
        this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
    }
    addDate() {
        if (this.focusText === o.TEXT1) {
            if (this.addBtnStateEffect) {
                this.inputYear = this.year;
                this.year += this.step;
                if (!this.hasFocusText1) {
                    this.hasFocusText1 = true;
                }
            }
            if (!this.subBtnStateEffect) {
                this.subBtnStateEffect = true;
                this.subOpacity = c1.r3;
                this.subBtnEnabled = true;
            }
            if (this.year >= this.maxYear) {
                this.addOpacity = c1.s3;
                this.addBtnStateEffect = false;
                this.addBtnEnabled = false;
            }
            else {
                if (this.addOpacity === c1.s3) {
                    this.addOpacity = c1.r3;
                }
                if (!this.addBtnStateEffect) {
                    this.addBtnStateEffect = true;
                }
                if (!this.addBtnEnabled) {
                    this.addBtnEnabled = true;
                }
            }
        }
        else if (this.focusText === o.TEXT2) {
            this.month += this.step % d1.c4;
            if (this.month > d1.c4) {
                this.month -= d1.c4;
            }
            if (!this.hasFocusText2) {
                this.hasFocusText2 = true;
            }
        }
        else if (this.focusText === o.TEXT3) {
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
        this.focusText = o.TEXT3;
        this.hasFocusText3 = true;
        this.day += this.step % this.getDayNumber();
        if (this.day > this.getDayNumber()) {
            this.day -= this.getDayNumber();
        }
        this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
    }
    updateInlineEnableSate() {
        if (this.value >= this.max) {
            this.addOpacity = c1.s3;
            this.addBtnStateEffect = false;
            this.addBtnEnabled = false;
        }
        else {
            this.addOpacity = c1.r3;
            this.addBtnStateEffect = true;
            this.addBtnEnabled = true;
        }
        if (this.value <= this.min) {
            this.subOpacity = c1.s3;
            this.subBtnStateEffect = false;
            this.subBtnEnabled = false;
        }
        else {
            this.subOpacity = c1.r3;
            this.subBtnStateEffect = true;
            this.subBtnEnabled = true;
        }
    }
    updateDateEnableSate() {
        if (this.year === this.maxYear && this.focusText === o.TEXT1) {
            this.addOpacity = c1.s3;
            this.addBtnStateEffect = false;
            this.addBtnEnabled = false;
        }
        else {
            if (this.addOpacity === c1.s3) {
                this.addOpacity = c1.r3;
            }
            if (!this.addBtnStateEffect) {
                this.addBtnStateEffect = true;
            }
            if (!this.addBtnEnabled) {
                this.addBtnEnabled = true;
            }
        }
        if (this.year === this.minYear && this.focusText === o.TEXT1) {
            this.subOpacity = c1.s3;
            this.subBtnStateEffect = false;
            this.subBtnEnabled = false;
        }
        else {
            if (this.subOpacity === c1.s3) {
                this.subOpacity = c1.r3;
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
        this.focusText = o.NONE;
        this.hasFocusText1 = false;
        this.hasFocusText2 = false;
        this.hasFocusText3 = false;
    }
    resetFocusButton() {
        if (this.addBtnFocusWidh === c1.o1) {
            this.addBtnFocusWidh = c1.q1;
            this.onBlurIncrease && this.onBlurIncrease();
        }
        if (this.subBtnFocusWidh === c1.o1) {
            this.subBtnFocusWidh = c1.q1;
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
            this.addOpacity = c1.r3;
            this.addBtnEnabled = true;
        }
    }
    endLastValue() {
        this.value = this.max;
        if (!this.subBtnStateEffect) {
            this.subBtnStateEffect = true;
            this.subOpacity = c1.r3;
            this.subBtnEnabled = true;
        }
    }
    updateButtonStatus() {
        if (this.value <= this.min) {
            if (!this.addBtnStateEffect && this.max != this.min) {
                this.addBtnStateEffect = true;
                this.addOpacity = c1.r3;
                this.addBtnEnabled = true;
            }
            this.subOpacity = c1.s3;
            this.subBtnStateEffect = false;
            this.subBtnEnabled = false;
        }
        if (this.value >= this.max) {
            if (!this.subBtnStateEffect && this.max != this.min) {
                this.subBtnStateEffect = true;
                this.subOpacity = c1.r3;
                this.subBtnEnabled = true;
            }
            this.addOpacity = c1.s3;
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
            let g1 = focusControl.requestFocus(key);
            if (g1) {
                console.log('Request success');
            }
            else {
                console.log('Request failed');
            }
        });
    }
    focusCurrentText(text) {
        if (text === o.TEXT1) {
            if (this.focusText === o.NONE) {
                this.focusText = o.TEXT1;
            }
            if (!this.hasFocusText1) {
                this.hasFocusText1 = true;
            }
        }
        else if (text === o.TEXT2) {
            if (this.focusText === o.NONE) {
                this.focusText = o.TEXT2;
            }
            if (!this.hasFocusText2) {
                this.hasFocusText2 = true;
            }
        }
        else if (text === o.TEXT3) {
            if (this.focusText === o.NONE) {
                this.focusText = o.TEXT3;
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
                return px2vp(getContext(this).resourceManager.getNumber(value.id));
            }
            else {
                return px2vp(getContext(this)
                    .resourceManager
                    .getNumberByName((value.params[0]).split('.')[2]));
            }
        }
        catch (error) {
            return c1.h2;
        }
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
                        RelativeContainer.height(c1.i2);
                    }, RelativeContainer);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.numberStyleOptions.label);
                        Text.direction(this.counterDirection);
                        Text.fontSize(c1.t1);
                        Text.maxFontScale(c1.t3);
                        Text.fontColor(c1.h1);
                        Text.margin({
                            start: LengthMetrics.vp(this.resourceToVp(c1.z1))
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
                        Row.height(c1.l2);
                        Row.margin({
                            end: LengthMetrics.vp(this.resourceToVp(c1.a2))
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
                        Stack.width(c1.l2);
                        Stack.height(c1.l2);
                        Stack.borderRadius(c1.m2);
                        Stack.borderWidth(this.subBtnFocusWidh);
                        Stack.borderColor(c1.g1);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(c1.l1);
                        Image.direction(this.counterDirection);
                        Image.width(c1.j2);
                        Image.height(c1.j2);
                        Image.fillColor(c1.f1);
                        Image.opacity(this.subOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(c1.l2);
                        Button.height(c1.l2);
                        Button.responseRegion({
                            x: c1.t2,
                            y: c1.u2,
                            width: '150%',
                            height: '150%'
                        });
                        Button.groupDefaultFocus(true);
                        Button.backgroundColor(c1.e1);
                        Button.opacity(this.subOpacity);
                        Button.enabled(this.subBtnEnabled);
                        Button.key('ListSubButton' + this.timeStamp.toString());
                        Button.onKeyEvent((event) => {
                            this.subBtnFocusWidh = c1.o1;
                            if (event.keyCode === d1.e4) {
                                this.resetFocusButton();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_HOME) {
                                event.stopPropagation();
                                this.homeFirstValue();
                                this.focusWithTarget('ListAddButton' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_END) {
                                event.stopPropagation();
                                if (this.addBtnStateEffect) {
                                    this.addBtnStateEffect = false;
                                    this.addOpacity = c1.s3;
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
                                this.subBtnFocusWidh = c1.q1;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.subValue();
                                this.onChange?.(this.value);
                            }
                            this.subBtnFocusWidh = c1.q1;
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverDecrease && this.onHoverDecrease(isHover);
                        });
                        Button.focusable(this.focusEnable);
                        Button.onFocus(() => {
                            this.subBtnFocusWidh = c1.o1;
                            this.onFocusDecrease && this.onFocusDecrease();
                            this.updateButtonStatus();
                        });
                        Button.onBlur(() => {
                            this.subBtnFocusWidh = c1.q1;
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
                                    Text.direction(this.counterDirection);
                                    Text.width(this.textWidth.toString());
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontSize(c1.u1);
                                    Text.maxFontScale(c1.u3);
                                    Text.fontColor(c1.h1);
                                    Text.margin({
                                        start: LengthMetrics.vp(c1.o2),
                                        end: LengthMetrics.vp(c1.o2)
                                    });
                                }, Text);
                                Text.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.value.toString());
                                    Text.direction(this.counterDirection);
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontSize(c1.u1);
                                    Text.maxFontScale(c1.u3);
                                    Text.fontColor(c1.h1);
                                    Text.margin({
                                        start: LengthMetrics.vp(c1.o2),
                                        end: LengthMetrics.vp(c1.o2)
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
                        Stack.width(c1.l2);
                        Stack.height(c1.l2);
                        Stack.borderRadius(c1.m2);
                        Stack.borderWidth(this.addBtnFocusWidh);
                        Stack.borderColor(c1.g1);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(c1.j1);
                        Image.direction(this.counterDirection);
                        Image.width(c1.j2);
                        Image.height(c1.j2);
                        Image.fillColor(c1.f1);
                        Image.opacity(this.addOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(c1.l2);
                        Button.height(c1.l2);
                        Button.responseRegion({
                            x: c1.t2,
                            y: c1.u2,
                            width: '150%',
                            height: '150%'
                        });
                        Button.backgroundColor(c1.e1);
                        Button.opacity(this.addOpacity);
                        Button.enabled(this.addBtnEnabled);
                        Button.key('ListAddButton' + this.timeStamp.toString());
                        Button.onKeyEvent((event) => {
                            this.addBtnFocusWidh = c1.o1;
                            if (event.keyCode === d1.e4) {
                                this.resetFocusButton();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_HOME) {
                                event.stopPropagation();
                                this.homeFirstValue();
                                if (this.subBtnStateEffect) {
                                    this.subBtnStateEffect = false;
                                    this.subOpacity = c1.s3;
                                    this.subBtnEnabled = false;
                                }
                                this.focusWithTarget('ListAddButton' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_END) {
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
                                this.addBtnFocusWidh = c1.q1;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.addValue();
                                this.onChange?.(this.value);
                            }
                            this.addBtnFocusWidh = c1.q1;
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverIncrease && this.onHoverIncrease(isHover);
                        });
                        Button.focusable(this.focusEnable);
                        Button.onFocus(() => {
                            this.addBtnFocusWidh = c1.o1;
                            this.onFocusIncrease && this.onFocusIncrease();
                            this.updateButtonStatus();
                        });
                        Button.onBlur(() => {
                            this.addBtnFocusWidh = c1.q1;
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.direction(this.counterDirection);
                        Row.tabIndex(0);
                        Row.height(c1.c2);
                        Row.align(Alignment.Center);
                        Row.borderWidth(c1.d2);
                        Row.borderColor(c1.i1);
                        Row.borderRadius(c1.f2);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.width(c1.e2);
                        Stack.height(c1.e2);
                        Stack.borderRadius(c1.v2);
                        Stack.borderWidth(this.subBtnFocusWidh);
                        Stack.borderColor(c1.g1);
                        Stack.margin({
                            start: LengthMetrics.vp(this.resourceToVp(c1.g2))
                        });
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(c1.l1);
                        Image.direction(this.counterDirection);
                        Image.width(c1.b2);
                        Image.height(c1.b2);
                        Image.fillColor(c1.f1);
                        Image.opacity(this.subOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(c1.e2);
                        Button.height(c1.e2);
                        Button.backgroundColor(c1.e1);
                        Button.opacity(this.subOpacity);
                        Button.enabled(this.subBtnEnabled);
                        Button.key('CompactSubButton' + this.timeStamp.toString());
                        Button.onKeyEvent((event) => {
                            this.subBtnFocusWidh = c1.o1;
                            if (event.keyCode === d1.e4) {
                                this.resetFocusButton();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_HOME) {
                                event.stopPropagation();
                                this.homeFirstValue();
                                this.focusWithTarget('CompactAddButton' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_END) {
                                event.stopPropagation();
                                this.endLastValue();
                                if (this.addBtnStateEffect) {
                                    this.addBtnStateEffect = false;
                                    this.addOpacity = c1.s3;
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
                                this.subBtnFocusWidh = c1.q1;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.subValue();
                                this.onChange?.(this.value);
                            }
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.subBtnFocusWidh = c1.q1;
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
                            this.subBtnFocusWidh = c1.o1;
                            this.onFocusDecrease && this.onFocusDecrease();
                            this.updateButtonStatus();
                        });
                        Button.onBlur(() => {
                            this.subBtnFocusWidh = c1.q1;
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
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontSize(c1.w1);
                                    Text.maxFontScale(c1.u3);
                                    Text.fontColor(c1.h1);
                                    Text.width(this.textWidth.toString());
                                    Text.margin({
                                        start: LengthMetrics.vp(c1.z2),
                                        end: LengthMetrics.vp(c1.z2)
                                    });
                                }, Text);
                                Text.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.value.toString());
                                    Text.direction(this.counterDirection);
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontSize(c1.w1);
                                    Text.maxFontScale(c1.u3);
                                    Text.fontColor(c1.h1);
                                    Text.margin({
                                        start: LengthMetrics.vp(c1.z2),
                                        end: LengthMetrics.vp(c1.z2)
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
                        Stack.width(c1.e2);
                        Stack.height(c1.e2);
                        Stack.borderRadius(c1.v2);
                        Stack.borderWidth(this.addBtnFocusWidh);
                        Stack.borderColor(c1.g1);
                        Stack.margin({
                            end: LengthMetrics.vp(this.resourceToVp(c1.g2))
                        });
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(c1.j1);
                        Image.direction(this.counterDirection);
                        Image.width(c1.b2);
                        Image.height(c1.b2);
                        Image.fillColor(c1.f1);
                        Image.opacity(this.addOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(c1.e2);
                        Button.height(c1.e2);
                        Button.backgroundColor(c1.e1);
                        Button.opacity(this.addOpacity);
                        Button.enabled(this.addBtnEnabled);
                        Button.key('CompactAddButton' + this.timeStamp.toString());
                        Button.onKeyEvent((event) => {
                            this.addBtnFocusWidh = c1.o1;
                            if (event.keyCode === d1.e4) {
                                this.resetFocusButton();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_HOME) {
                                event.stopPropagation();
                                this.homeFirstValue();
                                if (this.subBtnStateEffect) {
                                    this.subBtnStateEffect = false;
                                    this.subOpacity = c1.s3;
                                    this.subBtnEnabled = false;
                                }
                                this.focusWithTarget('CompactAddButton' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_END) {
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
                                this.addBtnFocusWidh = c1.q1;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.addValue();
                                this.onChange?.(this.value);
                            }
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.addBtnFocusWidh = c1.q1;
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
                            this.addBtnFocusWidh = c1.o1;
                            this.onFocusIncrease && this.onFocusIncrease();
                            this.updateButtonStatus();
                        });
                        Button.onBlur(() => {
                            this.addBtnFocusWidh = c1.q1;
                            this.onBlurIncrease && this.onBlurIncrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.numberStyleOptions.label);
                        Text.direction(this.counterDirection);
                        Text.margin({ top: c1.a3 });
                        Text.fontSize(c1.v1);
                        Text.maxFontScale(c1.t3);
                        Text.fontColor(c1.h1);
                        Text.align(Alignment.Top);
                    }, Text);
                    Text.pop();
                    Column.pop();
                });
            }
            else if (this.type === CounterType.INLINE) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.direction(this.counterDirection);
                        Row.height(c1.g3);
                        Row.borderWidth(c1.d2);
                        Row.borderColor(c1.i1);
                        Row.borderRadius(c1.j3);
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
                                        start: LengthMetrics.vp(c1.q3),
                                        end: LengthMetrics.vp(c1.q3)
                                    });
                                    RelativeContainer.height('100%');
                                    RelativeContainer.width(this.textWidth);
                                }, RelativeContainer);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                                    TextInput.copyOption(CopyOptions.None);
                                    TextInput.fontSize(this.getTextInputFontSize());
                                    TextInput.fontWeight(FontWeight.Medium);
                                    TextInput.fontColor(this.hasFocusText1 ? Color.White : c1.h1);
                                    TextInput.maxLength(this.getMaxLength());
                                    TextInput.backgroundColor(this.hasFocusText1 ? c1.g1 : Color.Transparent);
                                    TextInput.key('InlineTextInput' + this.timeStamp.toString());
                                    TextInput.onKeyEvent((event) => {
                                        this.focusCurrentText(o.TEXT1);
                                        if (event.keyCode === d1.e4) {
                                            this.resetFocusText();
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === d1.KEYCODE_DPAD_UP) {
                                            this.addValue();
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === d1.KEYCODE_MOVE_HOME) {
                                            event.stopPropagation();
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === d1.KEYCODE_MOVE_END) {
                                            event.stopPropagation();
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === d1.KEYCODE_DPAD_DOWN) {
                                            this.subValue();
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === d1.KEYCODE_DPAD_LEFT) {
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === d1.KEYCODE_DPAD_RIGHT) {
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
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
                                        if (this.inputValue !== '' && Number(this.inputValue) <= this.max &&
                                            Number(this.inputValue) >= this.min) {
                                            this.value = Number(this.inputValue);
                                            this.onChange?.(this.value);
                                            this.hasInputText1 = false;
                                        }
                                        else {
                                            if (Number(this.inputValue) > this.max ||
                                                (Number(this.inputValue) < this.min &&
                                                    this.inputValue.length <= this.min.toString().length)) {
                                                this.inputValue = c;
                                            }
                                            if (value.length < this.getMaxLength()) {
                                                this.timeoutID1 = setTimeout(() => {
                                                    if (this.inputValue !== '' && Number(this.inputValue) <= this.max &&
                                                        Number(this.inputValue) >= this.min) {
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
                                        if (Number(this.inputValue) >= this.min && Number(this.inputValue) <= this.max) {
                                            this.value = Number(this.inputValue);
                                            this.onChange?.(this.value);
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
                                        this.focusText = o.TEXT1;
                                        this.hasFocusText1 = true;
                                        this.controller1.caretPosition(this.value.toString().length);
                                    });
                                    TextInput.onBlur(() => {
                                        this.focusText = o.NONE;
                                        this.hasFocusText1 = false;
                                    });
                                    TextInput.onClick((event) => {
                                        this.focusText = o.TEXT1;
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
                                        start: LengthMetrics.vp(c1.q3),
                                        end: LengthMetrics.vp(c1.q3)
                                    });
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                                    TextInput.copyOption(CopyOptions.None);
                                    TextInput.fontSize(this.getTextInputFontSize());
                                    TextInput.fontWeight(FontWeight.Medium);
                                    TextInput.fontColor(this.hasFocusText1 ? Color.White : c1.h1);
                                    TextInput.maxLength(this.getMaxLength());
                                    TextInput.backgroundColor(this.hasFocusText1 ? c1.g1 : Color.Transparent);
                                    TextInput.key('InlineTextInput' + this.timeStamp.toString());
                                    TextInput.onKeyEvent((event) => {
                                        this.focusCurrentText(o.TEXT1);
                                        if (event.keyCode === d1.e4) {
                                            this.resetFocusText();
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === d1.KEYCODE_DPAD_UP) {
                                            this.addValue();
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === d1.KEYCODE_DPAD_DOWN) {
                                            this.subValue();
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === d1.KEYCODE_DPAD_LEFT) {
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                            event.stopPropagation();
                                        }
                                        if (event.type === KeyType.Down &&
                                            event.keyCode === d1.KEYCODE_DPAD_RIGHT) {
                                            this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                                            event.stopPropagation();
                                        }
                                    });
                                    TextInput.onChange((value) => {
                                        this.inputValue = value;
                                        for (let e1 = 0; e1 < value.length; e1++) {
                                            let c = value[e1];
                                            if (c === '+' || c === '*' || c === '#') {
                                                this.value -= 1;
                                                this.value += 1;
                                                this.inputValue = this.value.toString();
                                                return;
                                            }
                                            if (c === '-' && e1 !== 0) {
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
                                        if (this.inputValue !== '' && Number(this.inputValue) <= this.max &&
                                            Number(this.inputValue) >= this.min) {
                                            this.value = Number(this.inputValue);
                                            this.onChange?.(this.value);
                                            this.hasInputText1 = false;
                                        }
                                        else {
                                            if (Number(this.inputValue) > this.max ||
                                                (Number(this.inputValue) < this.min &&
                                                    this.inputValue.length <= this.min.toString().length)) {
                                                this.inputValue = c;
                                            }
                                            if (value.length < this.getMaxLength()) {
                                                this.timeoutID1 = setTimeout(() => {
                                                    if (this.inputValue !== '' && Number(this.inputValue) <= this.max &&
                                                        Number(this.inputValue) >= this.min) {
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
                                        if (Number(this.inputValue) >= this.min && Number(this.inputValue) <= this.max) {
                                            this.value = Number(this.inputValue);
                                            this.onChange?.(this.value);
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
                                        this.focusText = o.TEXT1;
                                        this.hasFocusText1 = true;
                                        this.controller1.caretPosition(this.value.toString().length);
                                    });
                                    TextInput.onBlur(() => {
                                        this.focusText = o.NONE;
                                        this.hasFocusText1 = false;
                                    });
                                    TextInput.onClick((event) => {
                                        this.focusText = o.TEXT1;
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
                        Column.width(c1.h3);
                        Column.height(c1.g3);
                        Column.borderWidth({ start: LengthMetrics.vp(c1.s1) });
                        Column.borderColor(c1.i1);
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.direction(this.counterDirection);
                        Stack.width(c1.h3);
                        Stack.height(c1.i3);
                        Stack.padding({ top: '1vp' });
                        Stack.borderWidth({ bottom: '1vp' });
                        Stack.borderColor(c1.i1);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Rect.create();
                        Rect.direction(this.counterDirection);
                        Rect.width(c1.l3);
                        Rect.height(c1.m3);
                        Rect.radius([
                            ['0vp', '0vp'],
                            [c1.j3, c1.j3],
                            ['0vp', '0vp'],
                            ['0vp', '0vp']
                        ]);
                        Rect.strokeWidth(this.addBtnFocusWidh);
                        Rect.stroke(c1.g1);
                        Rect.margin({ end: LengthMetrics.vp(2) });
                        Rect.fillOpacity(0);
                    }, Rect);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(c1.m1);
                        Image.direction(this.counterDirection);
                        Image.width(c1.d3);
                        Image.height(c1.e3);
                        Image.fillColor(c1.f1);
                        Image.opacity(this.addOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(c1.h3);
                        Button.height(c1.i3);
                        Button.backgroundColor(Color.Transparent);
                        Button.opacity(this.addOpacity);
                        Button.enabled(this.addBtnEnabled);
                        Button.onClick((event) => {
                            this.addValue();
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.addBtnFocusWidh = c1.q1;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.addValue();
                            }
                            this.addBtnFocusWidh = c1.q1;
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverIncrease && this.onHoverIncrease(isHover);
                        });
                        Button.focusable(false);
                        Button.onFocus(() => {
                            this.addBtnFocusWidh = c1.o1;
                            this.onFocusIncrease && this.onFocusIncrease();
                        });
                        Button.onBlur(() => {
                            this.addBtnFocusWidh = c1.q1;
                            this.onBlurIncrease && this.onBlurIncrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.direction(this.counterDirection);
                        Stack.width(c1.h3);
                        Stack.height(c1.i3);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Rect.create();
                        Rect.direction(this.counterDirection);
                        Rect.width(c1.l3);
                        Rect.height(c1.m3);
                        Rect.radius([
                            ['0vp', '0vp'],
                            ['0vp', '0vp'],
                            [c1.j3, c1.j3],
                            ['0vp', '0vp']
                        ]);
                        Rect.strokeWidth(this.subBtnFocusWidh);
                        Rect.stroke(c1.g1);
                        Rect.margin({ top: LengthMetrics.vp(1), end: LengthMetrics.vp(1), bottom: LengthMetrics.vp(2) });
                        Rect.fillOpacity(0);
                    }, Rect);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(c1.n1);
                        Image.direction(this.counterDirection);
                        Image.width(c1.d3);
                        Image.height(c1.e3);
                        Image.fillColor(c1.f1);
                        Image.opacity(this.subOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(c1.h3);
                        Button.height(c1.i3);
                        Button.backgroundColor(Color.Transparent);
                        Button.opacity(this.subOpacity);
                        Button.enabled(this.subBtnEnabled);
                        Button.onClick((event) => {
                            this.subValue();
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.subBtnFocusWidh = c1.q1;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.subValue();
                            }
                            this.subBtnFocusWidh = c1.q1;
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverDecrease && this.onHoverDecrease(isHover);
                        });
                        Button.focusable(false);
                        Button.onFocus(() => {
                            this.subBtnFocusWidh = c1.o1;
                            this.onFocusDecrease && this.onFocusDecrease();
                        });
                        Button.onBlur(() => {
                            this.subBtnFocusWidh = c1.q1;
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.direction(this.counterDirection);
                        Row.height(c1.g3);
                        Row.borderWidth(c1.d2);
                        Row.borderColor(c1.i1);
                        Row.borderRadius(c1.j3);
                        Row.clip(true);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.direction(this.counterDirection);
                        Row.width('92vp');
                        Row.height(c1.g3);
                        Row.margin({
                            start: LengthMetrics.vp(c1.n3),
                            end: LengthMetrics.vp(c1.n3)
                        });
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        TextInput.create({
                            text: this.hasInputText1 ? this.inputYear.toString() : this.getYear(),
                            controller: this.controller1
                        });
                        TextInput.direction(this.counterDirection);
                        TextInput.type(InputType.Number);
                        TextInput.copyOption(CopyOptions.None);
                        TextInput.fontSize(this.getTextInputFontSize());
                        TextInput.fontWeight(FontWeight.Medium);
                        TextInput.fontColor(this.hasFocusText1 ? Color.White : c1.h1);
                        TextInput.maxLength(5);
                        TextInput.padding(0);
                        TextInput.backgroundColor(this.hasFocusText1 ? c1.g1 : Color.Transparent);
                        TextInput.width('38vp');
                        TextInput.height('20vp');
                        TextInput.borderRadius(0);
                        TextInput.borderWidth(0);
                        TextInput.key('DateTextInput1' + this.timeStamp.toString());
                        TextInput.onKeyEvent((event) => {
                            this.focusCurrentText(o.TEXT1);
                            if (event.keyCode === d1.e4) {
                                this.resetFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_DPAD_UP) {
                                this.addDate();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_DPAD_DOWN) {
                                this.subDate();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_HOME) {
                                this.homeFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_END) {
                                this.endFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_DPAD_LEFT) {
                                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_DPAD_RIGHT) {
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
                                this.updateDateEnableSate();
                                this.updateDay();
                            }, 1500);
                            if (this.inputYear >= this.minYear && this.inputYear <= this.maxYear) {
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
                            this.focusText = o.TEXT1;
                            this.hasFocusText1 = true;
                            this.updateDateEnableSate();
                            this.controller1.caretPosition(this.getYear().length);
                        });
                        TextInput.onBlur(() => {
                            this.focusText = o.NONE;
                            this.hasFocusText1 = false;
                            this.updateDateEnableSate();
                        });
                        TextInput.onClick((event) => {
                            this.focusText = o.TEXT1;
                            this.hasFocusText1 = true;
                            this.updateDateEnableSate();
                            this.controller1.caretPosition(this.getYear().length);
                        });
                    }, TextInput);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create('/');
                        Text.direction(this.counterDirection);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize(c1.w1);
                        Text.maxFontScale(c1.u3);
                        Text.fontColor(c1.h1);
                        Text.width('8vp');
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        TextInput.create({
                            text: this.hasInputText2 ? this.inputMoon.toString() : this.convertNumberToString(this.month),
                            controller: this.controller2
                        });
                        TextInput.direction(this.counterDirection);
                        TextInput.type(InputType.Number);
                        TextInput.copyOption(CopyOptions.None);
                        TextInput.fontSize(this.getTextInputFontSize());
                        TextInput.fontWeight(FontWeight.Medium);
                        TextInput.fontColor(this.hasFocusText2 ? Color.White : c1.h1);
                        TextInput.maxLength(3);
                        TextInput.padding(0);
                        TextInput.backgroundColor(this.hasFocusText2 ? c1.g1 : Color.Transparent);
                        TextInput.width('19vp');
                        TextInput.height('20vp');
                        TextInput.borderRadius(0);
                        TextInput.key('DateTextInput2' + this.timeStamp.toString());
                        TextInput.onKeyEvent((event) => {
                            this.focusCurrentText(o.TEXT2);
                            if (event.keyCode === d1.e4) {
                                this.resetFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_DPAD_DOWN) {
                                this.subDate();
                                this.updateDay();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_DPAD_UP) {
                                this.addDate();
                                this.updateDay();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_HOME) {
                                this.homeFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_END) {
                                this.endFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_DPAD_LEFT) {
                                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_DPAD_RIGHT) {
                                this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_TAB) {
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
                                    let date = new DateData(this.year, this.month, this.day);
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
                            this.focusText = o.TEXT2;
                            this.hasFocusText2 = true;
                            this.controller2.caretPosition(this.convertNumberToString(this.month).length);
                        });
                        TextInput.onBlur(() => {
                            this.focusText = o.NONE;
                            this.hasFocusText2 = false;
                        });
                        TextInput.onClick((event) => {
                            this.focusText = o.TEXT2;
                            this.hasFocusText2 = true;
                            this.controller2.caretPosition(this.convertNumberToString(this.month).length);
                        });
                    }, TextInput);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create('/');
                        Text.direction(this.counterDirection);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize(c1.w1);
                        Text.maxFontScale(c1.u3);
                        Text.fontColor(c1.h1);
                        Text.width('8vp');
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        TextInput.create({
                            text: this.hasInputText3 ? this.inputDay.toString() : this.convertNumberToString(this.day),
                            controller: this.controller3
                        });
                        TextInput.direction(this.counterDirection);
                        TextInput.type(InputType.Number);
                        TextInput.copyOption(CopyOptions.None);
                        TextInput.fontSize(this.getTextInputFontSize());
                        TextInput.fontWeight(FontWeight.Medium);
                        TextInput.fontColor(this.hasFocusText3 ? Color.White : c1.h1);
                        TextInput.maxLength(3);
                        TextInput.padding(0);
                        TextInput.backgroundColor(this.hasFocusText3 ? c1.g1 : Color.Transparent);
                        TextInput.width('19vp');
                        TextInput.height('20vp');
                        TextInput.borderRadius(0);
                        TextInput.key('DateTextInput3' + this.timeStamp.toString());
                        TextInput.onKeyEvent((event) => {
                            this.focusCurrentText(o.TEXT3);
                            if (event.keyCode === d1.e4) {
                                this.resetFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_DPAD_DOWN) {
                                this.subDate();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_DPAD_UP) {
                                this.addDate();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_HOME) {
                                this.homeFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_MOVE_END) {
                                this.endFocusText();
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_DPAD_LEFT) {
                                this.focusWithTarget('DateTextInput2' + this.timeStamp.toString());
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_DPAD_RIGHT) {
                                this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
                                event.stopPropagation();
                            }
                            if (event.type === KeyType.Down &&
                                event.keyCode === d1.KEYCODE_TAB) {
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
                                    let date = new DateData(this.year, this.month, this.day);
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
                            this.focusText = o.TEXT3;
                            this.hasFocusText3 = true;
                            this.controller3.caretPosition(this.convertNumberToString(this.day).length);
                        });
                        TextInput.onBlur(() => {
                            this.focusText = o.NONE;
                            this.hasFocusText3 = false;
                        });
                        TextInput.onClick((event) => {
                            this.focusText = o.TEXT3;
                            this.hasFocusText3 = true;
                            this.controller3.caretPosition(this.convertNumberToString(this.day).length);
                        });
                    }, TextInput);
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.direction(this.counterDirection);
                        Column.width(c1.h3);
                        Column.height(c1.g3);
                        Column.borderWidth({ start: LengthMetrics.vp(c1.s1) });
                        Column.borderColor(c1.i1);
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.width(c1.h3);
                        Stack.height(c1.i3);
                        Stack.padding({ top: '1vp' });
                        Stack.borderWidth({ bottom: '1vp' });
                        Stack.borderColor(c1.i1);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Rect.create();
                        Rect.direction(this.counterDirection);
                        Rect.width(c1.l3);
                        Rect.height(c1.m3);
                        Rect.radius([
                            ['0vp', '0vp'],
                            [c1.j3, c1.j3],
                            ['0vp', '0vp'],
                            ['0vp', '0vp']
                        ]);
                        Rect.strokeWidth(this.addBtnFocusWidh);
                        Rect.stroke(c1.g1);
                        Rect.margin({ end: LengthMetrics.vp(1) });
                        Rect.fillOpacity(0);
                    }, Rect);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(c1.m1);
                        Image.direction(this.counterDirection);
                        Image.width(c1.d3);
                        Image.height(c1.e3);
                        Image.fillColor(c1.f1);
                        Image.opacity(this.addOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(c1.h3);
                        Button.height(c1.i3);
                        Button.backgroundColor(Color.Transparent);
                        Button.opacity(this.addOpacity);
                        Button.enabled(this.addBtnEnabled);
                        Button.onClick((event) => {
                            this.addDate();
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.addBtnFocusWidh = c1.q1;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.addDate();
                            }
                            this.addBtnFocusWidh = c1.q1;
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverIncrease && this.onHoverIncrease(isHover);
                        });
                        Button.focusable(false);
                        Button.onFocus(() => {
                            this.addBtnFocusWidh = c1.o1;
                            this.onFocusIncrease && this.onFocusIncrease();
                        });
                        Button.onBlur(() => {
                            this.addBtnFocusWidh = c1.q1;
                            this.onBlurIncrease && this.onBlurIncrease();
                        });
                    }, Button);
                    Button.pop();
                    Stack.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.width(c1.h3);
                        Stack.height(c1.i3);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Rect.create();
                        Rect.direction(this.counterDirection);
                        Rect.width(c1.l3);
                        Rect.height(c1.m3);
                        Rect.radius([
                            ['0vp', '0vp'],
                            ['0vp', '0vp'],
                            [c1.j3, c1.j3],
                            ['0vp', '0vp']
                        ]);
                        Rect.strokeWidth(this.subBtnFocusWidh);
                        Rect.stroke(c1.g1);
                        Rect.margin({ top: LengthMetrics.vp(1), end: LengthMetrics.vp(1), bottom: LengthMetrics.vp(2) });
                        Rect.fillOpacity(0);
                    }, Rect);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(c1.n1);
                        Image.direction(this.counterDirection);
                        Image.width(c1.d3);
                        Image.height(c1.e3);
                        Image.fillColor(c1.f1);
                        Image.opacity(this.subOpacity);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect });
                        Button.direction(this.counterDirection);
                        Button.width(c1.h3);
                        Button.height(c1.i3);
                        Button.backgroundColor(Color.Transparent);
                        Button.opacity(this.subOpacity);
                        Button.enabled(this.subBtnEnabled);
                        Button.onClick((event) => {
                            this.subDate();
                            if (event.source === SourceType.Mouse ||
                                event.source === SourceType.TouchScreen) {
                                this.subBtnFocusWidh = c1.q1;
                            }
                        });
                        Gesture.create(GesturePriority.Low);
                        LongPressGesture.create({ repeat: true });
                        LongPressGesture.onAction((event) => {
                            if (event.repeat) {
                                this.subDate();
                            }
                            this.subBtnFocusWidh = c1.q1;
                        });
                        LongPressGesture.pop();
                        Gesture.pop();
                        Button.hoverEffect(this.choverEffect);
                        Button.onHover((isHover) => {
                            this.onHoverDecrease && this.onHoverDecrease(isHover);
                        });
                        Button.focusable(false);
                        Button.onFocus(() => {
                            this.subBtnFocusWidh = c1.o1;
                            this.onFocusDecrease && this.onFocusDecrease();
                        });
                        Button.onBlur(() => {
                            this.subBtnFocusWidh = c1.q1;
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

export default {CounterType, t, u, a1,
    DateData, b1, CounterOptions, CounterComponent};
