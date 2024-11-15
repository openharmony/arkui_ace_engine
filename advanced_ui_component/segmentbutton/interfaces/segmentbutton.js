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

var t = (this && this.t) || function (e4, target, key, desc) {
    var c = arguments.length,
        r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.t1 === "function") {
        r = Reflect.t1(e4, target, key, desc);
    } else {
        for (var f4 = e4.length - 1; f4 >= 0; f4--) {
            if (d = e4[f4]) {
                r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
            }
        }
    }
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var u, a1;
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}
const curves = globalThis.requireNativeModule('ohos.curves');
const KeyCode = globalThis.requireNapi('multimodalInput.keyCode').KeyCode;
const util = globalThis.requireNapi('util');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const b1 = requireNapi('i18n');

const c1 = 2;
const d1 = 5;
const e1 = 1;
const f1 = 2;
const g1 = 1;

function m(c4, defaultValue, getContext) {
    if (c4 && c4.params && Array.isArray(c4.params) &&
    c4.params[0] && c4.params[0].includes('.') &&
        c4.params[0].split('.').length > 2) {
        try {
            let d4 = getContext.resourceManager.getNumberByName((c4.params[0]).split('.')[2]);
            return d4;
        } catch (error) {
            return defaultValue;
        }
    }
    return defaultValue;
}

const h1 = {
    u1: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_unselected_text_color'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    v1: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_checked_text_color'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    w1: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_foreground_contrary'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    z1: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_unselected_text_size'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    a2: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_checked_text_size'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    BACKGROUND_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_backboard_color'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    b2: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_checked_foreground_color'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    c2: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_emphasize'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    d2: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_focused_outline'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    e2: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_hover_color'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    f2: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_press_color'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    g2: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_background_blur_style'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    h2: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_baseplate_padding'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    i2: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_height'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    j2: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_min_font_size'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    l2: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_normal_border_radius'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    n2: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_marquee'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    o2: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_focus_text_primary'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    }
};

function o(first, second) {
    return Math.abs(first - second) < 0.001;
}

let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(options) {
        this.icon = options.icon;
        this.selectedIcon = options.selectedIcon;
        this.text = options.text;
        this.iconAccessibilityText = options.iconAccessibilityText;
        this.selectedIconAccessibilityText = options.selectedIconAccessibilityText;
        this.accessibilityLevel = options.accessibilityLevel;
        this.accessibilityDescription = options.accessibilityDescription;
    }
};
SegmentButtonItemOptions = t([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = u = class SegmentButtonItemOptionsArray extends Array {
    constructor(b4) {
        super(typeof b4 === 'number' ? b4 : 0);
        this.q2 = void 0;
        this.deleteCount = void 0;
        this.s2 = void 0;
        if (typeof b4 !== 'number' && b4 !== void 0) {
            super.push(...b4.map((element) => new SegmentButtonItemOptions(element)));
        }
    }

    push(...items) {
        if (this.length + items.length > d1) {
            console.warn('Exceeded the maximum number of elements (5).');
            return this.length;
        }
        this.q2 = this.length;
        this.deleteCount = 0;
        this.s2 = items.length;
        return super.push(...items.map((element) => new SegmentButtonItemOptions(element)));
    }

    pop() {
        if (this.length <= c1) {
            console.warn('Below the minimum number of elements (2).');
            return void 0;
        }
        this.q2 = this.length - 1;
        this.deleteCount = 1;
        this.s2 = 0;
        return super.pop();
    }

    shift() {
        if (this.length <= c1) {
            console.warn('Below the minimum number of elements (2).');
            return void 0;
        }
        this.q2 = 0;
        this.deleteCount = 1;
        this.s2 = 0;
        return super.shift();
    }

    unshift(...items) {
        if (this.length + items.length > d1) {
            console.warn('Exceeded the maximum number of elements (5).');
            return this.length;
        }
        if (items.length > 0) {
            this.q2 = 0;
            this.deleteCount = 0;
            this.s2 = items.length;
        }
        return super.unshift(...items.map((element) => new SegmentButtonItemOptions(element)));
    }

    splice(start, deleteCount, ...items) {
        let length = (this.length - deleteCount) < 0 ? 0 : (this.length - deleteCount);
        length += items.length;
        if (length < c1) {
            console.warn('Below the minimum number of elements (2).');
            return [];
        }
        if (length > d1) {
            console.warn('Exceeded the maximum number of elements (5).');
            return [];
        }
        this.q2 = start;
        this.deleteCount = deleteCount;
        this.s2 = items.length;
        return super.splice(start, deleteCount, ...items);
    }

    static create(elements) {
        return new u(elements);
    }
};
SegmentButtonItemOptionsArray = u = t([
    Observed
], SegmentButtonItemOptionsArray);

export { SegmentButtonItemOptionsArray };
let SegmentButtonOptions = a1 = class SegmentButtonOptions {
    get buttons() {
        return this.t2;
    }

    set buttons(val) {
        if (this.t2 !== void 0 && this.t2 !== val) {
            this.u2?.();
        }
        this.t2 = val;
    }

    constructor(options) {
        this.multiply = false;
        this.v2 = false;
        this.showIcon = false;
        this.t2 = void 0;
        this.fontColor = options.fontColor ?? h1.u1;
        this.selectedFontColor = options.selectedFontColor ?? h1.v1;
        this.fontSize = options.fontSize ?? h1.z1;
        this.selectedFontSize = options.selectedFontSize ?? h1.a2;
        this.fontWeight = options.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = options.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = options.backgroundColor ?? h1.BACKGROUND_COLOR;
        this.selectedBackgroundColor = options.selectedBackgroundColor ?? h1.b2;
        this.imageSize = options.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = options.buttonPadding;
        this.textPadding = options.textPadding;
        this.type = options.type;
        this.backgroundBlurStyle = options.backgroundBlurStyle ?? m(h1.g2, 0, getContext(this));
        this.localizedTextPadding = options.localizedTextPadding;
        this.localizedButtonPadding = options.localizedButtonPadding;
        this.direction = options.direction ?? Direction.Auto;
        this.buttons = new SegmentButtonItemOptionsArray(options.buttons);
        if (this.type === 'capsule') {
            this.multiply = options.multiply ?? false;
            this.buttons.forEach(button => {
                this.v2 ||= button.text !== void 0;
                this.showIcon ||= button.icon !== void 0 || button.selectedIcon !== void 0;
            });
            if (this.v2 && this.showIcon) {
                this.w2 = 12;
                this.z2 = 14;
            }
            this.selectedFontColor = options.selectedFontColor ?? h1.w1;
            this.selectedBackgroundColor = options.selectedBackgroundColor ??
            h1.c2;
        } else {
            this.v2 = true;
        }
        this.a3 = this.multiply ? 0 : 2;
    }

    static tab(options) {
        return new a1({
            type: 'tab',
            buttons: options.buttons,
            fontColor: options.fontColor,
            selectedFontColor: options.selectedFontColor,
            fontSize: options.fontSize,
            selectedFontSize: options.selectedFontSize,
            fontWeight: options.fontWeight,
            selectedFontWeight: options.selectedFontWeight,
            backgroundColor: options.backgroundColor,
            selectedBackgroundColor: options.selectedBackgroundColor,
            imageSize: options.imageSize,
            buttonPadding: options.buttonPadding,
            textPadding: options.textPadding,
            localizedTextPadding: options.localizedTextPadding,
            localizedButtonPadding: options.localizedButtonPadding,
            backgroundBlurStyle: options.backgroundBlurStyle,
            direction: options.direction
        });
    }

    static capsule(options) {
        return new a1({
            type: 'capsule',
            buttons: options.buttons,
            multiply: options.multiply,
            fontColor: options.fontColor,
            selectedFontColor: options.selectedFontColor,
            fontSize: options.fontSize,
            selectedFontSize: options.selectedFontSize,
            fontWeight: options.fontWeight,
            selectedFontWeight: options.selectedFontWeight,
            backgroundColor: options.backgroundColor,
            selectedBackgroundColor: options.selectedBackgroundColor,
            imageSize: options.imageSize,
            buttonPadding: options.buttonPadding,
            textPadding: options.textPadding,
            localizedTextPadding: options.localizedTextPadding,
            localizedButtonPadding: options.localizedButtonPadding,
            backgroundBlurStyle: options.backgroundBlurStyle,
            direction: options.direction
        });
    }
};
SegmentButtonOptions = a1 = t([
    Observed
], SegmentButtonOptions);

export { SegmentButtonOptions };

class i1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.b3 = new SynchedPropertyNesedObjectPU(params.optionsArray, this, "optionsArray");
        this.c3 = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.d3 = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.e3 = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.b3.set(params.optionsArray);
        this.c3.set(params.options);
    }

    updateStateVars(params) {
        this.b3.set(params.optionsArray);
        this.c3.set(params.options);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.b3.purgeDependencyOnElmtId(rmElmtId);
        this.c3.purgeDependencyOnElmtId(rmElmtId);
        this.d3.purgeDependencyOnElmtId(rmElmtId);
        this.e3.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.b3.aboutToBeDeleted();
        this.c3.aboutToBeDeleted();
        this.d3.aboutToBeDeleted();
        this.e3.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get optionsArray() {
        return this.b3.get();
    }

    get options() {
        return this.c3.get();
    }

    get buttonBorderRadius() {
        return this.d3.get();
    }

    set buttonBorderRadius(newValue) {
        this.d3.set(newValue);
    }

    get buttonItemsSize() {
        return this.e3.get();
    }

    set buttonItemsSize(newValue) {
        this.e3.set(newValue);
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.a3);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const a4 = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (index < d1) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[index].height);
                                Stack.backgroundColor(this.options.backgroundColor ?? h1.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[index]);
                                Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
                            }, Stack);
                            Stack.pop();
                        });
                    } else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(elmtId, this.optionsArray, forEachItemGenFunction, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class j1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.b3 = new SynchedPropertyNesedObjectPU(params.optionsArray, this, "optionsArray");
        this.c3 = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.f3 = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, "selectedIndexes");
        this.e3 = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.g3 = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.h3 = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.d3 = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.b3.set(params.optionsArray);
        this.c3.set(params.options);
    }

    updateStateVars(params) {
        this.b3.set(params.optionsArray);
        this.c3.set(params.options);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.b3.purgeDependencyOnElmtId(rmElmtId);
        this.c3.purgeDependencyOnElmtId(rmElmtId);
        this.f3.purgeDependencyOnElmtId(rmElmtId);
        this.e3.purgeDependencyOnElmtId(rmElmtId);
        this.g3.purgeDependencyOnElmtId(rmElmtId);
        this.h3.purgeDependencyOnElmtId(rmElmtId);
        this.d3.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.b3.aboutToBeDeleted();
        this.c3.aboutToBeDeleted();
        this.f3.aboutToBeDeleted();
        this.e3.aboutToBeDeleted();
        this.g3.aboutToBeDeleted();
        this.h3.aboutToBeDeleted();
        this.d3.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get optionsArray() {
        return this.b3.get();
    }

    get options() {
        return this.c3.get();
    }

    get selectedIndexes() {
        return this.f3.get();
    }

    set selectedIndexes(newValue) {
        this.f3.set(newValue);
    }

    get buttonItemsSize() {
        return this.e3.get();
    }

    set buttonItemsSize(newValue) {
        this.e3.set(newValue);
    }

    get selectedItemPosition() {
        return this.g3.get();
    }

    set selectedItemPosition(newValue) {
        this.g3.set(newValue);
    }

    get zoomScaleArray() {
        return this.h3.get();
    }

    set zoomScaleArray(newValue) {
        this.h3.set(newValue);
    }

    get buttonBorderRadius() {
        return this.d3.get();
    }

    set buttonBorderRadius(newValue) {
        this.d3.set(newValue);
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.direction(this.options.direction);
                        Stack.borderRadius(this.buttonBorderRadius[this.selectedIndexes[0]]);
                        Stack.size(this.buttonItemsSize[this.selectedIndexes[0]]);
                        Stack.backgroundColor(this.options.selectedBackgroundColor ??
                            (this.options.type === 'tab' ? h1.b2 :
                            h1.c2));
                        Stack.position(ObservedObject.GetRawObject(this.selectedItemPosition));
                        Stack.scale({
                            x: this.zoomScaleArray[this.selectedIndexes[0]],
                            y: this.zoomScaleArray[this.selectedIndexes[0]]
                        });
                        Stack.shadow(m({
                            "id": -1,
                            "type": 10002,
                            params: ['sys.float.segment_button_shadow'],
                            "bundleName": "__harDefaultBundleName__",
                            "moduleName": "__harDefaultModuleName__"
                        }, 0, getContext(this)));
                    }, Stack);
                    Stack.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class l1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.b3 = new SynchedPropertyNesedObjectPU(params.optionsArray, this, "optionsArray");
        this.c3 = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.f3 = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, "selectedIndexes");
        this.e3 = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.h3 = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.d3 = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.i3 = new ObservedPropertyObjectPU(Array.from({ length: d1 }, (z3, index) => Color.Transparent), this,
            "multiColor");
        this.setInitiallyProvidedValue(params);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.b3.set(params.optionsArray);
        this.c3.set(params.options);
        if (params.multiColor !== undefined) {
            this.multiColor = params.multiColor;
        }
    }

    updateStateVars(params) {
        this.b3.set(params.optionsArray);
        this.c3.set(params.options);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.b3.purgeDependencyOnElmtId(rmElmtId);
        this.c3.purgeDependencyOnElmtId(rmElmtId);
        this.f3.purgeDependencyOnElmtId(rmElmtId);
        this.e3.purgeDependencyOnElmtId(rmElmtId);
        this.h3.purgeDependencyOnElmtId(rmElmtId);
        this.d3.purgeDependencyOnElmtId(rmElmtId);
        this.i3.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.b3.aboutToBeDeleted();
        this.c3.aboutToBeDeleted();
        this.f3.aboutToBeDeleted();
        this.e3.aboutToBeDeleted();
        this.h3.aboutToBeDeleted();
        this.d3.aboutToBeDeleted();
        this.i3.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get optionsArray() {
        return this.b3.get();
    }

    get options() {
        return this.c3.get();
    }

    get selectedIndexes() {
        return this.f3.get();
    }

    set selectedIndexes(newValue) {
        this.f3.set(newValue);
    }

    get buttonItemsSize() {
        return this.e3.get();
    }

    set buttonItemsSize(newValue) {
        this.e3.set(newValue);
    }

    get zoomScaleArray() {
        return this.h3.get();
    }

    set zoomScaleArray(newValue) {
        this.h3.set(newValue);
    }

    get buttonBorderRadius() {
        return this.d3.get();
    }

    set buttonBorderRadius(newValue) {
        this.d3.set(newValue);
    }

    get multiColor() {
        return this.i3.get();
    }

    set multiColor(newValue) {
        this.i3.set(newValue);
    }

    onOptionsChange() {
        for (let y3 = 0; y3 < this.selectedIndexes.length; y3++) {
            this.multiColor[this.selectedIndexes[y3]] = this.options.selectedBackgroundColor ??
            h1.c2;
        }
    }

    onSelectedChange() {
        for (let x3 = 0; x3 < d1; x3++) {
            this.multiColor[x3] = Color.Transparent;
        }
        for (let w3 = 0; w3 < this.selectedIndexes.length; w3++) {
            this.multiColor[this.selectedIndexes[w3]] = this.options.selectedBackgroundColor ??
            h1.c2;
        }
    }

    aboutToAppear() {
        for (let v3 = 0; v3 < this.selectedIndexes.length; v3++) {
            this.multiColor[this.selectedIndexes[v3]] = this.options.selectedBackgroundColor ??
            h1.c2;
        }
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.a3);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const u3 = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (index < d1) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.width(this.buttonItemsSize[index].width);
                                Stack.height(this.buttonItemsSize[index].height);
                                Stack.backgroundColor(this.multiColor[index]);
                                Stack.borderRadius(this.buttonBorderRadius[index]);
                            }, Stack);
                            Stack.pop();
                        });
                    } else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(elmtId, this.optionsArray, forEachItemGenFunction, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class m1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.f3 = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, "selectedIndexes");
        this.j3 = new SynchedPropertySimpleTwoWayPU(params.focusIndex, this, "focusIndex");
        this.l3 = new SynchedPropertyObjectOneWayPU(params.maxFontScale, this, "maxFontScale");
        this.m3 = new SynchedPropertyNesedObjectPU(params.itemOptions, this, "itemOptions");
        this.c3 = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.n3 = new SynchedPropertyNesedObjectPU(params.property, this, "property");
        this.q3 = new SynchedPropertySimpleOneWayPU(params.index, this, "index");
        this.r3 = new SynchedPropertySimpleOneWayPU(params.marquee, this, "marquee");
        this.s3 = new SynchedPropertySimpleOneWayPU(params.isMarqueeAndFadeout, this, "isMarqueeAndFadeout");
        this.t3 = new ObservedPropertySimplePU(false, this, "isMarquee");
        this.u3 = new ObservedPropertySimplePU(false, this, "isFadeout");
        this.groupId = '';
        this.setInitiallyProvidedValue(params);
        this.declareWatch("focusIndex", this.onFocusIndex);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.m3.set(params.itemOptions);
        this.c3.set(params.options);
        this.n3.set(params.property);
        if (params.isMarquee !== undefined) {
            this.isMarquee = params.isMarquee;
        }
        if (params.isFadeout !== undefined) {
            this.isFadeout = params.isFadeout;
        }
        if (params.groupId !== undefined) {
            this.groupId = params.groupId;
        }
    }

    updateStateVars(params) {
        this.l3.reset(params.maxFontScale);
        this.m3.set(params.itemOptions);
        this.c3.set(params.options);
        this.n3.set(params.property);
        this.q3.reset(params.index);
        this.r3.reset(params.marquee);
        this.s3.reset(params.isMarqueeAndFadeout);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.f3.purgeDependencyOnElmtId(rmElmtId);
        this.j3.purgeDependencyOnElmtId(rmElmtId);
        this.l3.purgeDependencyOnElmtId(rmElmtId);
        this.m3.purgeDependencyOnElmtId(rmElmtId);
        this.c3.purgeDependencyOnElmtId(rmElmtId);
        this.n3.purgeDependencyOnElmtId(rmElmtId);
        this.q3.purgeDependencyOnElmtId(rmElmtId);
        this.r3.purgeDependencyOnElmtId(rmElmtId);
        this.s3.purgeDependencyOnElmtId(rmElmtId);
        this.t3.purgeDependencyOnElmtId(rmElmtId);
        this.u3.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.f3.aboutToBeDeleted();
        this.j3.aboutToBeDeleted();
        this.l3.aboutToBeDeleted();
        this.m3.aboutToBeDeleted();
        this.c3.aboutToBeDeleted();
        this.n3.aboutToBeDeleted();
        this.q3.aboutToBeDeleted();
        this.r3.aboutToBeDeleted();
        this.s3.aboutToBeDeleted();
        this.t3.aboutToBeDeleted();
        this.u3.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get selectedIndexes() {
        return this.f3.get();
    }

    set selectedIndexes(newValue) {
        this.f3.set(newValue);
    }

    get focusIndex() {
        return this.j3.get();
    }

    set focusIndex(newValue) {
        this.j3.set(newValue);
    }

    get maxFontScale() {
        return this.l3.get();
    }

    set maxFontScale(newValue) {
        this.l3.set(newValue);
    }

    get itemOptions() {
        return this.m3.get();
    }

    get options() {
        return this.c3.get();
    }

    get property() {
        return this.n3.get();
    }

    get index() {
        return this.q3.get();
    }

    set index(newValue) {
        this.q3.set(newValue);
    }

    get marquee() {
        return this.r3.get();
    }

    set marquee(newValue) {
        this.r3.set(newValue);
    }

    get isMarqueeAndFadeout() {
        return this.s3.get();
    }

    set isMarqueeAndFadeout(newValue) {
        this.s3.set(newValue);
    }

    get isMarquee() {
        return this.t3.get();
    }

    set isMarquee(newValue) {
        this.t3.set(newValue);
    }

    get isFadeout() {
        return this.u3.get();
    }

    set isFadeout(newValue) {
        this.u3.set(newValue);
    }

    getTextPadding() {
        if (this.options.localizedTextPadding) {
            return this.options.localizedTextPadding;
        }
        if (this.options.textPadding !== void (0)) {
            return this.options.textPadding;
        }
        return 0;
    }

    getButtonPadding() {
        if (this.options.localizedButtonPadding) {
            return this.options.localizedButtonPadding;
        }
        if (this.options.buttonPadding !== void (0)) {
            return this.options.buttonPadding;
        }
        if (this.options.type === 'capsule' && this.options.v2 && this.options.showIcon) {
            return {
                top: LengthMetrics.resource({
                    "id": -1,
                    "type": 10002,
                    params: ['sys.float.segment_button_text_capsule_u_d_padding'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                }),
                bottom: LengthMetrics.resource({
                    "id": -1,
                    "type": 10002,
                    params: ['sys.float.segment_button_text_capsule_u_d_padding'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                }),
                start: LengthMetrics.resource({
                    "id": -1,
                    "type": 10002,
                    params: ['sys.float.segment_button_text_l_r_padding'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                }),
                end: LengthMetrics.resource({
                    "id": -1,
                    "type": 10002,
                    params: ['sys.float.segment_button_text_l_r_padding'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                })
            };
        }
        return {
            top: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.segment_button_text_u_d_padding'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }),
            bottom: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.segment_button_text_u_d_padding'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }),
            start: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.segment_button_text_l_r_padding'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }),
            end: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.segment_button_text_l_r_padding'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            })
        };
    }

    onFocusIndex() {
        this.isMarquee = this.marquee && this.focusIndex === this.index;
    }

    aboutToAppear() {
        this.isFadeout = this.marquee;
    }

    setFontColor() {
        if (this.property.isSelected) {
            return this.options.selectedFontColor ?? h1.w1;
        } else {
            return this.options.fontColor ?? h1.u1;
        }
    }

    getFontColor() {
        let p3 = (typeof this.options.selectedFontColor) === 'object';
        let q3 = false;
        if (p3) {
            let r3 = h1.w1.id;
            let s3 = h1.v1.id;
            let t3 = this.options.selectedFontColor.id;
            q3 = this.options.type === 'tab' ? t3 === s3 :
                t3 === r3;
        }
        if (this.property.isSelected && !q3) {
            return this.options.selectedFontColor;
        } else {
            return this.isMarquee ? h1.o2 : this.setFontColor();
        }
    }

    getAccessibilityText() {
        try {
            if (this.selectedIndexes.includes(this.index) && this.itemOptions.selectedIconAccessibilityText) {
                return (typeof this.itemOptions.selectedIconAccessibilityText === 'string') ?
                this.itemOptions.selectedIconAccessibilityText :
                getContext(this).resourceManager.getStringSync(this.itemOptions.selectedIconAccessibilityText.id);
            } else if (this.itemOptions.iconAccessibilityText) {
                return (typeof this.itemOptions.iconAccessibilityText === 'string') ?
                this.itemOptions.iconAccessibilityText :
                getContext(this).resourceManager.getStringSync(this.itemOptions.iconAccessibilityText.id);
            }
        } catch (error) {
            console.error(`Ace SegmentButton getAccessibilityText, error: ${error.toString()}`);
        }
        return '';
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create({ space: 2 });
            Column.focusable(false);
            Column.direction(this.options.direction);
            Column.focusScopePriority(this.groupId,
                Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.getButtonPadding());
            Column.constraintSize({ minHeight: h1.i2 });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon);
                        Image.direction(this.options.direction);
                        Image.size(this.options.imageSize ?? { width: 24, height: 24 });
                        Image.focusable(!this.options.v2);
                        Image.draggable(false);
                        Image.fillColor(this.getFontColor());
                        Image.accessibilityText(this.getAccessibilityText());
                    }, Image);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.options.v2) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.itemOptions.text);
                        Text.direction(this.options.direction);
                        Text.fontColor(this.getFontColor());
                        Text.fontWeight(this.property.fontWeight);
                        Text.fontSize(this.property.fontSize);
                        Text.minFontSize(this.property.minFontSize);
                        Text.maxFontSize(this.property.fontSize);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.maxFontScale));
                        Text.textOverflow({ overflow: this.marquee ? TextOverflow.MARQUEE : TextOverflow.Ellipsis });
                        Text.marqueeOptions({
                            start: this.isMarquee,
                            fadeout: this.isFadeout,
                            marqueeStartPolicy: MarqueeStartPolicy.DEFAULT
                        });
                        Text.maxLines(1);
                        Text.textAlign(TextAlign.Center);
                        Text.padding(this.getTextPadding());
                    }, Text);
                    Text.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

let n1 = class HoverColorProperty {
    constructor() {
        this.v3 = Color.Transparent;
    }
};
n1 = t([
    Observed
], n1);

class o1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.e3 = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.w3 = new SynchedPropertySimpleOneWayPU(params.press, this, "press");
        this.x3 = new SynchedPropertySimpleOneWayPU(params.hover, this, "hover");
        this.y3 = new SynchedPropertyNesedObjectPU(params.colorProperty, this, "colorProperty");
        this.d3 = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.c3 = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.pressIndex = 0;
        this.pressColor = h1.f2;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.y3.set(params.colorProperty);
        this.c3.set(params.options);
        if (params.pressIndex !== undefined) {
            this.pressIndex = params.pressIndex;
        }
        if (params.pressColor !== undefined) {
            this.pressColor = params.pressColor;
        }
    }

    updateStateVars(params) {
        this.w3.reset(params.press);
        this.x3.reset(params.hover);
        this.y3.set(params.colorProperty);
        this.c3.set(params.options);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.e3.purgeDependencyOnElmtId(rmElmtId);
        this.w3.purgeDependencyOnElmtId(rmElmtId);
        this.x3.purgeDependencyOnElmtId(rmElmtId);
        this.y3.purgeDependencyOnElmtId(rmElmtId);
        this.d3.purgeDependencyOnElmtId(rmElmtId);
        this.c3.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.e3.aboutToBeDeleted();
        this.w3.aboutToBeDeleted();
        this.x3.aboutToBeDeleted();
        this.y3.aboutToBeDeleted();
        this.d3.aboutToBeDeleted();
        this.c3.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get buttonItemsSize() {
        return this.e3.get();
    }

    set buttonItemsSize(newValue) {
        this.e3.set(newValue);
    }

    get press() {
        return this.w3.get();
    }

    set press(newValue) {
        this.w3.set(newValue);
    }

    get hover() {
        return this.x3.get();
    }

    set hover(newValue) {
        this.x3.set(newValue);
    }

    get colorProperty() {
        return this.y3.get();
    }

    get buttonBorderRadius() {
        return this.d3.get();
    }

    set buttonBorderRadius(newValue) {
        this.d3.set(newValue);
    }

    get options() {
        return this.c3.get();
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.size(this.buttonItemsSize[this.pressIndex]);
            Stack.backgroundColor(this.press && this.hover ? this.pressColor : this.colorProperty.v3);
            Stack.borderRadius(this.buttonBorderRadius[this.pressIndex]);
        }, Stack);
        Stack.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class q1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.b3 = new SynchedPropertyNesedObjectPU(params.optionsArray, this, "optionsArray");
        this.c3 = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.f3 = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, "selectedIndexes");
        this.z3 = this.initializeConsume("componentSize", "componentSize");
        this.d3 = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.e3 = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.a4 = this.initializeConsume("buttonItemsPosition", "buttonItemsPosition");
        this.j3 = this.initializeConsume("focusIndex", "focusIndex");
        this.h3 = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.b4 = this.initializeConsume("buttonItemProperty", "buttonItemProperty");
        this.c4 = this.initializeConsume("buttonItemsSelected", "buttonItemsSelected");
        this.d4 = new SynchedPropertyObjectTwoWayPU(params.pressArray, this, "pressArray");
        this.e4 = new SynchedPropertyObjectTwoWayPU(params.hoverArray, this, "hoverArray");
        this.f4 = new SynchedPropertyObjectTwoWayPU(params.hoverColorArray, this, "hoverColorArray");
        this.l3 = new SynchedPropertyObjectOneWayPU(params.maxFontScale, this, "maxFontScale");
        this.g4 = new ObservedPropertyObjectPU(Array.from({ length: d1 }, (n3, index) => 0), this, "buttonWidth");
        this.h4 = new ObservedPropertyObjectPU(Array.from({ length: d1 }, (m3, index) => 0), this, "buttonHeight");
        this.r3 = new ObservedPropertySimplePU(m(h1.n2, 1, getContext(this)) === 0, this, "marquee");
        this.s3 = new ObservedPropertySimplePU(false, this, "isMarqueeAndFadeout");
        this.buttonItemsRealHeight = Array.from({ length: d1 }, (l3, index) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.segmentFocusControl = m({
            "id": -1,
            "type": 10002,
            params: ['sys.float.segment_focus_control'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, 1, getContext(this)) === 1;
        this.segmentButtonPadding = m({
            "id": -1,
            "type": 10002,
            params: ['sys.float.segment_button_baseplate_padding'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, 0, getContext(this));
        this.setInitiallyProvidedValue(params);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.declareWatch("focusIndex", this.onFocusIndex);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.b3.set(params.optionsArray);
        this.c3.set(params.options);
        if (params.buttonWidth !== undefined) {
            this.buttonWidth = params.buttonWidth;
        }
        if (params.buttonHeight !== undefined) {
            this.buttonHeight = params.buttonHeight;
        }
        if (params.marquee !== undefined) {
            this.marquee = params.marquee;
        }
        if (params.isMarqueeAndFadeout !== undefined) {
            this.isMarqueeAndFadeout = params.isMarqueeAndFadeout;
        }
        if (params.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = params.buttonItemsRealHeight;
        }
        if (params.groupId !== undefined) {
            this.groupId = params.groupId;
        }
        if (params.segmentFocusControl !== undefined) {
            this.segmentFocusControl = params.segmentFocusControl;
        }
        if (params.segmentButtonPadding !== undefined) {
            this.segmentButtonPadding = params.segmentButtonPadding;
        }
    }

    updateStateVars(params) {
        this.b3.set(params.optionsArray);
        this.c3.set(params.options);
        this.l3.reset(params.maxFontScale);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.b3.purgeDependencyOnElmtId(rmElmtId);
        this.c3.purgeDependencyOnElmtId(rmElmtId);
        this.f3.purgeDependencyOnElmtId(rmElmtId);
        this.z3.purgeDependencyOnElmtId(rmElmtId);
        this.d3.purgeDependencyOnElmtId(rmElmtId);
        this.e3.purgeDependencyOnElmtId(rmElmtId);
        this.a4.purgeDependencyOnElmtId(rmElmtId);
        this.j3.purgeDependencyOnElmtId(rmElmtId);
        this.h3.purgeDependencyOnElmtId(rmElmtId);
        this.b4.purgeDependencyOnElmtId(rmElmtId);
        this.c4.purgeDependencyOnElmtId(rmElmtId);
        this.d4.purgeDependencyOnElmtId(rmElmtId);
        this.e4.purgeDependencyOnElmtId(rmElmtId);
        this.f4.purgeDependencyOnElmtId(rmElmtId);
        this.l3.purgeDependencyOnElmtId(rmElmtId);
        this.g4.purgeDependencyOnElmtId(rmElmtId);
        this.h4.purgeDependencyOnElmtId(rmElmtId);
        this.r3.purgeDependencyOnElmtId(rmElmtId);
        this.s3.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.b3.aboutToBeDeleted();
        this.c3.aboutToBeDeleted();
        this.f3.aboutToBeDeleted();
        this.z3.aboutToBeDeleted();
        this.d3.aboutToBeDeleted();
        this.e3.aboutToBeDeleted();
        this.a4.aboutToBeDeleted();
        this.j3.aboutToBeDeleted();
        this.h3.aboutToBeDeleted();
        this.b4.aboutToBeDeleted();
        this.c4.aboutToBeDeleted();
        this.d4.aboutToBeDeleted();
        this.e4.aboutToBeDeleted();
        this.f4.aboutToBeDeleted();
        this.l3.aboutToBeDeleted();
        this.g4.aboutToBeDeleted();
        this.h4.aboutToBeDeleted();
        this.r3.aboutToBeDeleted();
        this.s3.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get optionsArray() {
        return this.b3.get();
    }

    get options() {
        return this.c3.get();
    }

    get selectedIndexes() {
        return this.f3.get();
    }

    set selectedIndexes(newValue) {
        this.f3.set(newValue);
    }

    get componentSize() {
        return this.z3.get();
    }

    set componentSize(newValue) {
        this.z3.set(newValue);
    }

    get buttonBorderRadius() {
        return this.d3.get();
    }

    set buttonBorderRadius(newValue) {
        this.d3.set(newValue);
    }

    get buttonItemsSize() {
        return this.e3.get();
    }

    set buttonItemsSize(newValue) {
        this.e3.set(newValue);
    }

    get buttonItemsPosition() {
        return this.a4.get();
    }

    set buttonItemsPosition(newValue) {
        this.a4.set(newValue);
    }

    get focusIndex() {
        return this.j3.get();
    }

    set focusIndex(newValue) {
        this.j3.set(newValue);
    }

    get zoomScaleArray() {
        return this.h3.get();
    }

    set zoomScaleArray(newValue) {
        this.h3.set(newValue);
    }

    get buttonItemProperty() {
        return this.b4.get();
    }

    set buttonItemProperty(newValue) {
        this.b4.set(newValue);
    }

    get buttonItemsSelected() {
        return this.c4.get();
    }

    set buttonItemsSelected(newValue) {
        this.c4.set(newValue);
    }

    get pressArray() {
        return this.d4.get();
    }

    set pressArray(newValue) {
        this.d4.set(newValue);
    }

    get hoverArray() {
        return this.e4.get();
    }

    set hoverArray(newValue) {
        this.e4.set(newValue);
    }

    get hoverColorArray() {
        return this.f4.get();
    }

    set hoverColorArray(newValue) {
        this.f4.set(newValue);
    }

    get maxFontScale() {
        return this.l3.get();
    }

    set maxFontScale(newValue) {
        this.l3.set(newValue);
    }

    get buttonWidth() {
        return this.g4.get();
    }

    set buttonWidth(newValue) {
        this.g4.set(newValue);
    }

    get buttonHeight() {
        return this.h4.get();
    }

    set buttonHeight(newValue) {
        this.h4.set(newValue);
    }

    get marquee() {
        return this.r3.get();
    }

    set marquee(newValue) {
        this.r3.set(newValue);
    }

    get isMarqueeAndFadeout() {
        return this.s3.get();
    }

    set isMarqueeAndFadeout(newValue) {
        this.s3.set(newValue);
    }

    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((value, index) => {
            this.buttonWidth[index] = value.width;
            this.buttonHeight[index] = value.height;
        });
    }

    changeSelectedIndexes(g3) {
        if (this.optionsArray.q2 === void 0 || this.optionsArray.deleteCount === void 0 ||
            this.optionsArray.s2 === void 0) {
            return;
        }
        if (!(this.options.multiply ?? false)) {
            if (this.selectedIndexes[0] === void 0) {
                return;
            }
            if (this.selectedIndexes[0] < this.optionsArray.q2) {
                return;
            }
            if (this.optionsArray.q2 + this.optionsArray.deleteCount > this.selectedIndexes[0]) {
                if (this.options.type === 'tab') {
                    this.selectedIndexes[0] = 0;
                } else if (this.options.type === 'capsule') {
                    this.selectedIndexes = [];
                }
            } else {
                this.selectedIndexes[0] =
                    this.selectedIndexes[0] - this.optionsArray.deleteCount + this.optionsArray.s2;
            }
        } else {
            let h3 = this.selectedIndexes;
            for (let j3 = 0; j3 < this.optionsArray.deleteCount; j3++) {
                let k3 = h3.indexOf(this.optionsArray.q2);
                let indexes = h3.map(value => this.optionsArray.q2 &&
                    (value > this.optionsArray.q2) ? value - 1 : value);
                if (k3 !== -1) {
                    indexes.splice(k3, 1);
                }
                h3 = indexes;
            }
            for (let i3 = 0; i3 < this.optionsArray.s2; i3++) {
                let indexes = h3.map(value => this.optionsArray.q2 &&
                    (value >= this.optionsArray.q2) ? value + 1 : value);
                h3 = indexes;
            }
            this.selectedIndexes = h3;
        }
    }

    changeFocusIndex(f3) {
        if (this.optionsArray.q2 === void 0 || this.optionsArray.deleteCount === void 0 ||
            this.optionsArray.s2 === void 0) {
            return;
        }
        if (this.focusIndex === -1) {
            return;
        }
        if (this.focusIndex < this.optionsArray.q2) {
            return;
        }
        if (this.optionsArray.q2 + this.optionsArray.deleteCount > this.focusIndex) {
            this.focusIndex = 0;
        } else {
            this.focusIndex = this.focusIndex - this.optionsArray.deleteCount + this.optionsArray.s2;
        }
    }

    onOptionsArrayChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        let e3 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.q2 !== void 0 && this.optionsArray.deleteCount !== void 0 &&
            this.optionsArray.s2 !== void 0) {
            this.changeSelectedIndexes(e3);
            this.changeFocusIndex(e3);
            this.optionsArray.q2 = void 0;
            this.optionsArray.deleteCount = void 0;
            this.optionsArray.s2 = void 0;
        }
    }

    onOptionsChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        this.calculateBorderRadius();
    }

    onFocusIndex() {
        this.isMarqueeAndFadeout = this.marquee && !this.isMarqueeAndFadeout;
    }

    aboutToAppear() {
        for (let index = 0; index < this.buttonItemsRealHeight.length; index++) {
            this.buttonItemsRealHeight[index] = 0;
        }
    }

    getBorderRadius(index) {
        let borderRadius = this.buttonBorderRadius[index];
        if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex]) {
            borderRadius.topStart = LengthMetrics.vp((borderRadius.topStart?.value ?? 0) + 4);
            borderRadius.topEnd = LengthMetrics.vp((borderRadius.topEnd?.value ?? 0) + 4);
            borderRadius.bottomStart = LengthMetrics.vp((borderRadius.bottomStart?.value ?? 0) + 4);
            borderRadius.bottomEnd = LengthMetrics.vp((borderRadius.bottomEnd?.value ?? 0) + 4);
        }
        return borderRadius;
    }

    focusStack(index, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.borderRadius(this.getBorderRadius(index));
            Stack.size({
                width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ?
                    this.buttonWidth[index] + 8 : this.buttonWidth[index],
                height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ?
                    this.buttonHeight[index] + 8 : this.buttonHeight[index]
            });
            Stack.borderColor(h1.d2);
            Stack.borderWidth(2);
        }, Stack);
        Stack.pop();
        Stack.pop();
    }

    calculateBorderRadius() {
        let b3 = Array.from({
            length: d1
        }, (d3, index) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        });
        for (let index = 0; index < this.buttonBorderRadius.length; index++) {
            let c3 = this.buttonItemsSize[index].height / 2;
            if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                b3[index].topStart = LengthMetrics.vp(this.options.w2 ?? c3);
                b3[index].topEnd = LengthMetrics.vp(this.options.w2 ?? c3);
                b3[index].bottomStart = LengthMetrics.vp(this.options.w2 ?? c3);
                b3[index].bottomEnd = LengthMetrics.vp(this.options.w2 ?? c3);
            } else {
                if (index === 0) {
                    b3[index].topStart = LengthMetrics.vp(this.options.w2 ?? c3);
                    b3[index].topEnd = LengthMetrics.vp(0);
                    b3[index].bottomStart = LengthMetrics.vp(this.options.w2 ?? c3);
                    b3[index].bottomEnd = LengthMetrics.vp(0);
                } else if (this.options.buttons &&
                    index === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    b3[index].topStart = LengthMetrics.vp(0);
                    b3[index].topEnd = LengthMetrics.vp(this.options.w2 ?? c3);
                    b3[index].bottomStart = LengthMetrics.vp(0);
                    b3[index].bottomEnd = LengthMetrics.vp(this.options.w2 ?? c3);
                } else {
                    b3[index].topStart = LengthMetrics.vp(0);
                    b3[index].topEnd = LengthMetrics.vp(0);
                    b3[index].bottomStart = LengthMetrics.vp(0);
                    b3[index].bottomEnd = LengthMetrics.vp(0);
                }
            }
        }
        this.buttonBorderRadius = b3;
    }

    getAccessibilityDescription(value) {
        if (value) {
            try {
                return (typeof value === 'string') ? value :
                getContext(this).resourceManager.getStringSync(value.id);
            } catch (error) {
                console.error(`Ace SegmentButton getAccessibilityDescription, error: ${error.toString()}`);
            }
        }
        return '';
    }

    SegmentButtonFocus(index, item, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
        }, Stack);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new o1(this, {
                        pressIndex: index,
                        colorProperty: this.hoverColorArray[index],
                        press: this.pressArray[index],
                        hover: this.hoverArray[index],
                        options: this.options,
                    }, undefined, elmtId, () => {
                    }, { page: "library/src/main/ets/components/segmentbutton.ets", line: 880, i4: 7 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            pressIndex: index,
                            colorProperty: this.hoverColorArray[index],
                            press: this.pressArray[index],
                            hover: this.hoverArray[index],
                            options: this.options
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {
                        colorProperty: this.hoverColorArray[index],
                        press: this.pressArray[index],
                        hover: this.hoverArray[index],
                        options: this.options
                    });
                }
            }, { name: "PressAndHoverEffect" });
        }
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            __Common__.onSizeChange((a3, newValue) => {
                this.buttonItemsRealHeight[index] = newValue.height;
                let maxHeight = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ?
                this.options.buttons.length : 0));
                for (let index = 0; index < this.buttonItemsSize.length; index++) {
                    this.buttonItemsSize[index] = { width: this.buttonItemsSize[index].width, height: maxHeight };
                }
                this.calculateBorderRadius();
            });
        }, __Common__);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new m1(this, {
                        isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                        selectedIndexes: this.f3,
                        focusIndex: this.j3,
                        index: index,
                        itemOptions: item,
                        options: this.options,
                        property: this.buttonItemProperty[index],
                        groupId: this.groupId,
                        maxFontScale: this.maxFontScale,
                        marquee: this.marquee
                    }, undefined, elmtId, () => {
                    }, { page: "library/src/main/ets/components/segmentbutton.ets", line: 887, i4: 7 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                            selectedIndexes: this.selectedIndexes,
                            focusIndex: this.focusIndex,
                            index: index,
                            itemOptions: item,
                            options: this.options,
                            property: this.buttonItemProperty[index],
                            groupId: this.groupId,
                            maxFontScale: this.maxFontScale,
                            marquee: this.marquee
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {
                        isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                        index: index,
                        itemOptions: item,
                        options: this.options,
                        property: this.buttonItemProperty[index],
                        maxFontScale: this.maxFontScale,
                        marquee: this.marquee
                    });
                }
            }, { name: "SegmentButtonItem" });
        }
        __Common__.pop();
        Stack.pop();
    }

    stackClick(index) {
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            if (this.selectedIndexes.indexOf(index) > -1) {
                this.selectedIndexes.splice(this.selectedIndexes.indexOf(index), 1);
            } else {
                this.selectedIndexes.push(index);
            }
        } else {
            this.selectedIndexes[0] = index;
        }
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create({ space: 1 });
                        Row.direction(this.options.direction);
                        Row.focusScopeId(this.groupId, true);
                        Row.padding(this.options?.multiply ? 0 : h1.h2);
                        Row.onSizeChange((z2, newValue) => {
                            this.componentSize = { width: newValue.width, height: newValue.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        ForEach.create();
                        const forEachItemGenFunction = (_item, index) => {
                            const item = _item;
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                If.create();
                                if (index < d1) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Button.createWithChild();
                                            Button.type(ButtonType.Normal);
                                            Button.stateEffect(false);
                                            Button.hoverEffect(HoverEffect.None);
                                            Button.backgroundColor(Color.Transparent);
                                            Button.accessibilityLevel(item.accessibilityLevel);
                                            Button.accessibilitySelected(this.options.multiply ? undefined :
                                            this.selectedIndexes.includes(index));
                                            Button.accessibilityChecked(this.options.multiply ?
                                            this.selectedIndexes.includes(index) : undefined);
                                            Button.accessibilityDescription(this.getAccessibilityDescription(item.accessibilityDescription));
                                            Button.direction(this.options.direction);
                                            Button.borderRadius(this.buttonBorderRadius[index]);
                                            Button.scale({
                                                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ?
                                                    1 : this.zoomScaleArray[index],
                                                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ?
                                                    1 : this.zoomScaleArray[index]
                                            });
                                            Button.layoutWeight(1);
                                            Button.padding(0);
                                            Button.onSizeChange((w2, newValue) => {
                                                this.buttonItemsSize[index] = {
                                                    width: newValue.width,
                                                    height: this.buttonItemsSize[index].height
                                                };
                                                if (newValue.width) {
                                                    this.buttonItemsPosition[index] = {
                                                        start: LengthMetrics.vp(this.segmentButtonPadding +
                                                            (Number.parseFloat(newValue.width.toString()) + 1) * index),
                                                        top: LengthMetrics.px(Math.floor(this.getUIContext()
                                                            .vp2px(this.segmentButtonPadding)))
                                                    };
                                                }
                                            });
                                            Button.onClick(() => {
                                                this.stackClick(index);
                                            });
                                            Button.focusable(true);
                                            Button.focusScopePriority(this.groupId,
                                                Math.min(...this.selectedIndexes) === index ?
                                                FocusPriority.PREVIOUS : FocusPriority.AUTO);
                                            Button.onFocus(() => {
                                                this.focusIndex = index;
                                                this.marquee = m(h1.n2, 1, getContext(this)) === 0;
                                                if (this.marquee) {
                                                    this.hoverColorArray[index].v3 = {
                                                        "id": -1,
                                                        "type": 10001,
                                                        params: ['sys.color.segment_button_focus_backboard_primary'],
                                                        "bundleName": "__harDefaultBundleName__",
                                                        "moduleName": "__harDefaultModuleName__"
                                                    };
                                                }
                                            });
                                            Button.onBlur(() => {
                                                this.focusIndex = -1;
                                                this.hoverColorArray[index].v3 = Color.Transparent;
                                            });
                                            Gesture.create(GesturePriority.Low);
                                            TapGesture.create();
                                            TapGesture.onAction(() => {
                                                this.focusIndex = -1;
                                                if (this.options.type === 'capsule' &&
                                                    (this.options.multiply ?? false)) {
                                                    if (this.selectedIndexes.indexOf(index) === -1) {
                                                        this.selectedIndexes.push(index);
                                                    } else {
                                                        this.selectedIndexes.splice(this.selectedIndexes.indexOf(index),
                                                            1);
                                                    }
                                                } else {
                                                    this.selectedIndexes[0] = index;
                                                }
                                            });
                                            TapGesture.pop();
                                            Gesture.pop();
                                            Button.onTouch((event) => {
                                                if (this.marquee) {
                                                    this.getUIContext().getFocusController().clearFocus();
                                                }
                                                if (event.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (event.type === TouchType.Down) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[index] = 0.95;
                                                    });
                                                } else if (event.type === TouchType.Up) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[index] = 1;
                                                    });
                                                }
                                            });
                                            Button.onHover((isHover) => {
                                                this.hoverArray[index] = isHover;
                                                if (isHover) {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[index].v3 =
                                                            this.marquee && this.focusIndex === index ? {
                                                                "id": -1,
                                                                "type": 10001,
                                                                params: ['sys.color.segment_button_focus_backboard_primary'],
                                                                "bundleName": "__harDefaultBundleName__",
                                                                "moduleName": "__harDefaultModuleName__"
                                                            } : (h1.e2);
                                                    });
                                                } else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[index].v3 =
                                                            this.marquee && this.focusIndex === index ? {
                                                                "id": -1,
                                                                "type": 10001,
                                                                params: ['sys.color.segment_button_focus_backboard_primary'],
                                                                "bundleName": "__harDefaultBundleName__",
                                                                "moduleName": "__harDefaultModuleName__"
                                                            } : Color.Transparent;
                                                    });
                                                }
                                            });
                                            Button.onMouse((event) => {
                                                switch (event.action) {
                                                    case MouseAction.Press:
                                                        Context.animateTo({ curve: curves.springMotion(0.347, 0.99) },
                                                            () => {
                                                                this.zoomScaleArray[index] = 0.95;
                                                            });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[index] = true;
                                                        });
                                                        break;
                                                    case MouseAction.Release:
                                                        Context.animateTo({ curve: curves.springMotion(0.347, 0.99) },
                                                            () => {
                                                                this.zoomScaleArray[index] = 1;
                                                            });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[index] = false;
                                                        });
                                                        break;
                                                }
                                            });
                                        }, Button);
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            If.create();
                                            if (this.segmentFocusControl) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Stack.create();
                                                        ViewStackProcessor.visualState("normal");
                                                        Stack.overlay(undefined);
                                                        ViewStackProcessor.visualState("focused");
                                                        Stack.overlay({
                                                            builder: () => {
                                                                this.focusStack.call(this, index);
                                                            }
                                                        }, {
                                                            align: Alignment.Center
                                                        });
                                                        ViewStackProcessor.visualState();
                                                        Stack.onClick(() => {
                                                            this.stackClick(index);
                                                        });
                                                    }, Stack);
                                                    this.SegmentButtonFocus.bind(this)(index, item);
                                                    Stack.pop();
                                                });
                                            } else {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.SegmentButtonFocus.bind(this)(index, item);
                                                });
                                            }
                                        }, If);
                                        If.pop();
                                        Button.pop();
                                    });
                                } else {
                                    this.ifElseBranchUpdateFunction(1, () => {
                                    });
                                }
                            }, If);
                            If.pop();
                        };
                        this.forEachUpdateFunction(elmtId, this.optionsArray, forEachItemGenFunction, undefined, true,
                            false);
                    }, ForEach);
                    ForEach.pop();
                    Row.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

let s1 = class ItemProperty {
    constructor() {
        this.fontColor = h1.u1;
        this.fontSize = h1.z1;
        this.fontWeight = FontWeight.Regular;
        this.isSelected = false;
        this.minFontSize = h1.j2 || 9;
    }
};
s1 = t([
    Observed
], s1);

export class SegmentButton extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.c3 = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.f3 = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, "selectedIndexes");
        this.onItemClicked = undefined;
        this.l3 = new SynchedPropertyObjectOneWayPU(params.maxFontScale, this, "maxFontScale");
        this.z3 = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, "componentSize");
        this.addProvidedVar("componentSize", this.z3, false);
        this.d3 = new ObservedPropertyObjectPU(Array.from({
            length: d1
        }, (v2, index) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        }), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.d3, false);
        this.e3 = new ObservedPropertyObjectPU(Array.from({ length: d1 }, (u2, index) => {
            return {};
        }), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.e3, false);
        this.a4 = new ObservedPropertyObjectPU(Array.from({
            length: d1
        }, (t2, index) => {
            return {};
        }), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.a4, false);
        this.c4 =
            new ObservedPropertyObjectPU(Array.from({ length: d1 }, (s2, index) => false), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.c4, false);
        this.b4 = new ObservedPropertyObjectPU(Array.from({
            length: d1
        }, (r2, index) => new s1()), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.b4, false);
        this.j3 = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.j3, false);
        this.g3 = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.g3, false);
        this.h3 = new ObservedPropertyObjectPU(Array.from({ length: d1 }, (q2, index) => 1.0), this, "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.h3, false);
        this.d4 = new ObservedPropertyObjectPU(Array.from({ length: d1 }, (o2, index) => false), this, "pressArray");
        this.e4 = new ObservedPropertyObjectPU(Array.from({ length: d1 }, (n2, index) => false), this, "hoverArray");
        this.f4 = new ObservedPropertyObjectPU(Array.from({
            length: d1
        }, (m2, index) => new n1()), this, "hoverColorArray");
        this.doSelectedChangeAnimate = false;
        this.isCurrentPositionSelected = false;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = false;
        this.j4 = new ObservedPropertySimplePU(false, this, "shouldMirror");
        this.setInitiallyProvidedValue(params);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.declareWatch("buttonItemsPosition", this.onItemsPositionChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.c3.set(params.options);
        if (params.onItemClicked !== undefined) {
            this.onItemClicked = params.onItemClicked;
        }
        if (params.maxFontScale === undefined) {
            this.l3.set(e1);
        }
        if (params.componentSize !== undefined) {
            this.componentSize = params.componentSize;
        }
        if (params.buttonBorderRadius !== undefined) {
            this.buttonBorderRadius = params.buttonBorderRadius;
        }
        if (params.buttonItemsSize !== undefined) {
            this.buttonItemsSize = params.buttonItemsSize;
        }
        if (params.buttonItemsPosition !== undefined) {
            this.buttonItemsPosition = params.buttonItemsPosition;
        }
        if (params.buttonItemsSelected !== undefined) {
            this.buttonItemsSelected = params.buttonItemsSelected;
        }
        if (params.buttonItemProperty !== undefined) {
            this.buttonItemProperty = params.buttonItemProperty;
        }
        if (params.focusIndex !== undefined) {
            this.focusIndex = params.focusIndex;
        }
        if (params.selectedItemPosition !== undefined) {
            this.selectedItemPosition = params.selectedItemPosition;
        }
        if (params.zoomScaleArray !== undefined) {
            this.zoomScaleArray = params.zoomScaleArray;
        }
        if (params.pressArray !== undefined) {
            this.pressArray = params.pressArray;
        }
        if (params.hoverArray !== undefined) {
            this.hoverArray = params.hoverArray;
        }
        if (params.hoverColorArray !== undefined) {
            this.hoverColorArray = params.hoverColorArray;
        }
        if (params.doSelectedChangeAnimate !== undefined) {
            this.doSelectedChangeAnimate = params.doSelectedChangeAnimate;
        }
        if (params.isCurrentPositionSelected !== undefined) {
            this.isCurrentPositionSelected = params.isCurrentPositionSelected;
        }
        if (params.panGestureStartPoint !== undefined) {
            this.panGestureStartPoint = params.panGestureStartPoint;
        }
        if (params.isPanGestureMoved !== undefined) {
            this.isPanGestureMoved = params.isPanGestureMoved;
        }
        if (params.shouldMirror !== undefined) {
            this.shouldMirror = params.shouldMirror;
        }
    }

    updateStateVars(params) {
        this.c3.set(params.options);
        this.l3.reset(params.maxFontScale);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.c3.purgeDependencyOnElmtId(rmElmtId);
        this.f3.purgeDependencyOnElmtId(rmElmtId);
        this.l3.purgeDependencyOnElmtId(rmElmtId);
        this.z3.purgeDependencyOnElmtId(rmElmtId);
        this.d3.purgeDependencyOnElmtId(rmElmtId);
        this.e3.purgeDependencyOnElmtId(rmElmtId);
        this.a4.purgeDependencyOnElmtId(rmElmtId);
        this.c4.purgeDependencyOnElmtId(rmElmtId);
        this.b4.purgeDependencyOnElmtId(rmElmtId);
        this.j3.purgeDependencyOnElmtId(rmElmtId);
        this.g3.purgeDependencyOnElmtId(rmElmtId);
        this.h3.purgeDependencyOnElmtId(rmElmtId);
        this.d4.purgeDependencyOnElmtId(rmElmtId);
        this.e4.purgeDependencyOnElmtId(rmElmtId);
        this.f4.purgeDependencyOnElmtId(rmElmtId);
        this.j4.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.c3.aboutToBeDeleted();
        this.f3.aboutToBeDeleted();
        this.l3.aboutToBeDeleted();
        this.z3.aboutToBeDeleted();
        this.d3.aboutToBeDeleted();
        this.e3.aboutToBeDeleted();
        this.a4.aboutToBeDeleted();
        this.c4.aboutToBeDeleted();
        this.b4.aboutToBeDeleted();
        this.j3.aboutToBeDeleted();
        this.g3.aboutToBeDeleted();
        this.h3.aboutToBeDeleted();
        this.d4.aboutToBeDeleted();
        this.e4.aboutToBeDeleted();
        this.f4.aboutToBeDeleted();
        this.j4.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get options() {
        return this.c3.get();
    }

    get selectedIndexes() {
        return this.f3.get();
    }

    set selectedIndexes(newValue) {
        this.f3.set(newValue);
    }

    get maxFontScale() {
        return this.l3.get();
    }

    set maxFontScale(newValue) {
        this.l3.set(newValue);
    }

    get componentSize() {
        return this.z3.get();
    }

    set componentSize(newValue) {
        this.z3.set(newValue);
    }

    get buttonBorderRadius() {
        return this.d3.get();
    }

    set buttonBorderRadius(newValue) {
        this.d3.set(newValue);
    }

    get buttonItemsSize() {
        return this.e3.get();
    }

    set buttonItemsSize(newValue) {
        this.e3.set(newValue);
    }

    get buttonItemsPosition() {
        return this.a4.get();
    }

    set buttonItemsPosition(newValue) {
        this.a4.set(newValue);
    }

    get buttonItemsSelected() {
        return this.c4.get();
    }

    set buttonItemsSelected(newValue) {
        this.c4.set(newValue);
    }

    get buttonItemProperty() {
        return this.b4.get();
    }

    set buttonItemProperty(newValue) {
        this.b4.set(newValue);
    }

    get focusIndex() {
        return this.j3.get();
    }

    set focusIndex(newValue) {
        this.j3.set(newValue);
    }

    get selectedItemPosition() {
        return this.g3.get();
    }

    set selectedItemPosition(newValue) {
        this.g3.set(newValue);
    }

    get zoomScaleArray() {
        return this.h3.get();
    }

    set zoomScaleArray(newValue) {
        this.h3.set(newValue);
    }

    get pressArray() {
        return this.d4.get();
    }

    set pressArray(newValue) {
        this.d4.set(newValue);
    }

    get hoverArray() {
        return this.e4.get();
    }

    set hoverArray(newValue) {
        this.e4.set(newValue);
    }

    get hoverColorArray() {
        return this.f4.get();
    }

    set hoverColorArray(newValue) {
        this.f4.set(newValue);
    }

    get shouldMirror() {
        return this.j4.get();
    }

    set shouldMirror(newValue) {
        this.j4.set(newValue);
    }

    onItemsPositionChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        if (this.doSelectedChangeAnimate) {
            this.updateAnimatedProperty(this.getSelectedChangeCurve());
        } else {
            this.updateAnimatedProperty(null);
        }
    }

    setItemsSelected() {
        this.buttonItemsSelected.forEach((l2, index) => {
            this.buttonItemsSelected[index] = false;
        });
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            this.selectedIndexes.forEach(index => this.buttonItemsSelected[index] = true);
        } else {
            this.buttonItemsSelected[this.selectedIndexes[0]] = true;
        }
    }

    updateSelectedIndexes() {
        if (this.selectedIndexes === void 0) {
            this.selectedIndexes = [];
        }
        if (this.options.type === 'tab' && this.selectedIndexes.length === 0) {
            this.selectedIndexes[0] = 0;
        }
        if (this.selectedIndexes.length > 1) {
            if (this.options.type === 'tab') {
                this.selectedIndexes = [0];
            }
            if (this.options.type === 'capsule' && !(this.options.multiply ?? false)) {
                this.selectedIndexes = [];
            }
        }
        let k2 = this.selectedIndexes.some(index => {
            return (index === void 0 || index < 0 || (this.options.buttons && index >= this.options.buttons.length));
        });
        if (k2) {
            if (this.options.type === 'tab') {
                this.selectedIndexes = [0];
            } else {
                this.selectedIndexes = [];
            }
        }
    }

    onOptionsChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        this.shouldMirror = this.isShouldMirror();
        this.updateSelectedIndexes();
        this.setItemsSelected();
        this.updateAnimatedProperty(null);
    }

    onSelectedChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        this.updateSelectedIndexes();
        this.setItemsSelected();
        if (this.doSelectedChangeAnimate) {
            this.updateAnimatedProperty(this.getSelectedChangeCurve());
        } else {
            this.updateAnimatedProperty(null);
        }
    }

    aboutToAppear() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        this.options.u2 = () => {
            if (this.options.type === 'tab') {
                this.selectedIndexes = [0];
            } else {
                this.selectedIndexes = [];
            }
        };
        this.shouldMirror = this.isShouldMirror();
        this.updateSelectedIndexes();
        this.setItemsSelected();
        this.updateAnimatedProperty(null);
    }

    isMouseWheelScroll(event) {
        return event.source === SourceType.Mouse && !this.isPanGestureMoved;
    }

    isMovedFromPanGestureStartPoint(x, y) {
        return !o(x, this.panGestureStartPoint.x) || !o(y, this.panGestureStartPoint.y);
    }

    isShouldMirror() {
        if (this.options.direction == Direction.Rtl) {
            return true;
        }
        try {
            let j2 = b1.System.getSystemLanguage();
            if (j2 === 'ug' && this.options.direction != Direction.Ltr) {
                return true;
            }
        } catch (error) {
            console.error(`Ace SegmentButton getSystemLanguage, error: ${error.toString()}`);
        }
        return false;
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.options ? this.options.direction : undefined);
            Stack.onBlur(() => {
                this.focusIndex = -1;
            });
            Stack.onKeyEvent((event) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (event.type === KeyType.Down) {
                    if (event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER ||
                        event.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            if (this.selectedIndexes.indexOf(this.focusIndex) === -1) {
                                this.selectedIndexes.push(this.focusIndex);
                            } else {
                                this.selectedIndexes.splice(this.selectedIndexes.indexOf(this.focusIndex), 1);
                            }
                        } else {
                            this.selectedIndexes[0] = this.focusIndex;
                        }
                    }
                }
            });
            Stack.accessibilityLevel('no');
            Gesture.create(GesturePriority.High);
            GestureGroup.create(GestureMode.Parallel);
            TapGesture.create();
            TapGesture.onAction((event) => {
                this.focusIndex = -1;
                let e2 = event.fingerList.find(Boolean);
                if (e2 === void 0) {
                    return;
                }
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                let f2 = e2.localX;
                let g2 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
                for (let h2 = 0; h2 < g2; h2++) {
                    f2 = f2 - this.buttonItemsSize[h2].width;
                    if (f2 >= 0) {
                        continue;
                    }
                    this.doSelectedChangeAnimate =
                        this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ?
                            false : true;
                    let i2 = this.isShouldMirror() ? g2 - 1 - h2 : h2;
                    if (this.onItemClicked) {
                        this.onItemClicked(i2);
                    }
                    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                        let selectedIndex = this.selectedIndexes.indexOf(i2);
                        if (selectedIndex === -1) {
                            this.selectedIndexes.push(i2);
                        } else {
                            this.selectedIndexes.splice(selectedIndex, 1);
                        }
                    } else {
                        this.selectedIndexes[0] = i2;
                    }
                    this.doSelectedChangeAnimate = false;
                    break;
                }
            });
            TapGesture.pop();
            SwipeGesture.create();
            SwipeGesture.onAction((event) => {
                if (this.options === void 0 || this.options.buttons === void 0 ||
                    event.sourceTool === SourceTool.TOUCHPAD) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (this.isCurrentPositionSelected) {
                    return;
                }
                if (Math.abs(event.angle) < 90 && this.selectedIndexes[0] !==
                    Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
                    this.doSelectedChangeAnimate = false;
                } else if (Math.abs(event.angle) > 90 && this.selectedIndexes[0] !== 0) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
                    this.doSelectedChangeAnimate = false;
                }
            });
            SwipeGesture.pop();
            PanGesture.create();
            PanGesture.onActionStart((event) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let b2 = event.fingerList.find(Boolean);
                if (b2 === void 0) {
                    return;
                }
                let c2 = b2.localX;
                this.panGestureStartPoint = { x: b2.globalX, y: b2.globalY };
                this.isPanGestureMoved = false;
                for (let d2 = 0; d2 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); d2++) {
                    c2 = c2 - this.buttonItemsSize[d2].width;
                    if (c2 < 0) {
                        this.isCurrentPositionSelected = d2 === this.selectedIndexes[0] ? true : false;
                        break;
                    }
                }
            });
            PanGesture.onActionUpdate((event) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (!this.isCurrentPositionSelected) {
                    return;
                }
                let v1 = event.fingerList.find(Boolean);
                if (v1 === void 0) {
                    return;
                }
                let w1 = v1.localX;
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(v1.globalX, v1.globalY)) {
                    this.isPanGestureMoved = true;
                }
                for (let a2 = 0; a2 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); a2++) {
                    w1 = w1 - this.buttonItemsSize[a2].width;
                    if (w1 < 0) {
                        this.doSelectedChangeAnimate = true;
                        this.selectedIndexes[0] = a2;
                        this.doSelectedChangeAnimate = false;
                        break;
                    }
                }
                this.zoomScaleArray.forEach((z1, index) => {
                    if (index === this.selectedIndexes[0]) {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[index] = 0.95;
                        });
                    } else {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[index] = 1;
                        });
                    }
                });
            });
            PanGesture.onActionEnd((event) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let u1 = event.fingerList.find(Boolean);
                if (u1 === void 0) {
                    return;
                }
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(u1.globalX, u1.globalY)) {
                    this.isPanGestureMoved = true;
                }
                if (this.isMouseWheelScroll(event)) {
                    let offset = event.offsetX !== 0 ? event.offsetX : event.offsetY;
                    this.doSelectedChangeAnimate = true;
                    if (offset > 0 && this.selectedIndexes[0] > 0) {
                        this.selectedIndexes[0] -= 1;
                    } else if (offset < 0 && this.selectedIndexes[0] <
                        Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                        this.selectedIndexes[0] += 1;
                    }
                    this.doSelectedChangeAnimate = false;
                }
                Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                    this.zoomScaleArray[this.selectedIndexes[0]] = 1;
                });
                this.isCurrentPositionSelected = false;
            });
            PanGesture.pop();
            GestureGroup.pop();
            Gesture.pop();
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.options !== void 0 && this.options.buttons != void 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                {
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        if (isInitialRender) {
                                            let componentCall = new i1(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                            }, undefined, elmtId, () => {
                                            }, {
                                                page: "library/src/main/ets/components/segmentbutton.ets",
                                                line: 1239,
                                                i4: 11
                                            });
                                            ViewPU.create(componentCall);
                                            let paramsLambda = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options
                                                };
                                            };
                                            componentCall.paramsGenerator_ = paramsLambda;
                                        } else {
                                            this.updateStateVarsOfChildByElmtId(elmtId, {
                                                optionsArray: this.options.buttons,
                                                options: this.options
                                            });
                                        }
                                    }, { name: "MultiSelectBackground" });
                                }
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Stack.create();
                                    Stack.direction(this.options.direction);
                                    Stack.size(ObservedObject.GetRawObject(this.componentSize));
                                    Stack.backgroundColor(this.options.backgroundColor ?? h1.BACKGROUND_COLOR);
                                    Stack.borderRadius(this.options.z2 ?? this.componentSize.height / 2);
                                    Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
                                }, Stack);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (this.options.buttons !== void 0 && this.options.buttons.length > 1) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                Row.create({ space: 1 });
                                                Row.direction(this.options.direction);
                                            }, Row);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = (_item, index) => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        If.create();
                                                        if (index < d1) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.observeComponentCreation2((elmtId,
                                                                    isInitialRender) => {
                                                                    Stack.create();
                                                                    Stack.direction(this.options.direction);
                                                                    Stack.scale({
                                                                        x: this.options.type === 'capsule' &&
                                                                            (this.options.multiply ?? false) ? 1 :
                                                                        this.zoomScaleArray[index],
                                                                        y: this.options.type === 'capsule' &&
                                                                            (this.options.multiply ?? false) ? 1 :
                                                                        this.zoomScaleArray[index]
                                                                    });
                                                                }, Stack);
                                                                Stack.pop();
                                                            });
                                                        } else {
                                                            this.ifElseBranchUpdateFunction(1, () => {
                                                            });
                                                        }
                                                    }, If);
                                                    If.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.options.buttons,
                                                    forEachItemGenFunction, undefined, true, false);
                                            }, ForEach);
                                            ForEach.pop();
                                            Row.pop();
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                        });
                                    }
                                }, If);
                                If.pop();
                                Stack.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Context.animation({ duration: 0 });
                        Stack.direction(this.options.direction);
                        Stack.size(ObservedObject.GetRawObject(this.componentSize));
                        Context.animation(null);
                        Stack.borderRadius((this.options.type === 'capsule' && (this.options.multiply ?? false) ?
                        this.options.w2 : this.options.z2) ??
                            this.componentSize.height / 2);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                {
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        if (isInitialRender) {
                                            let componentCall = new l1(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.f3
                                            }, undefined, elmtId, () => {
                                            }, {
                                                page: "library/src/main/ets/components/segmentbutton.ets",
                                                line: 1269,
                                                i4: 13
                                            });
                                            ViewPU.create(componentCall);
                                            let paramsLambda = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            componentCall.paramsGenerator_ = paramsLambda;
                                        } else {
                                            this.updateStateVarsOfChildByElmtId(elmtId, {
                                                optionsArray: this.options.buttons,
                                                options: this.options
                                            });
                                        }
                                    }, { name: "MultiSelectItemArray" });
                                }
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                {
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        if (isInitialRender) {
                                            let componentCall = new j1(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.f3
                                            }, undefined, elmtId, () => {
                                            }, {
                                                page: "library/src/main/ets/components/segmentbutton.ets",
                                                line: 1275,
                                                i4: 13
                                            });
                                            ViewPU.create(componentCall);
                                            let paramsLambda = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            componentCall.paramsGenerator_ = paramsLambda;
                                        } else {
                                            this.updateStateVarsOfChildByElmtId(elmtId, {
                                                optionsArray: this.options.buttons,
                                                options: this.options
                                            });
                                        }
                                    }, { name: "SelectItem" });
                                }
                            });
                        }
                    }, If);
                    If.pop();
                    Stack.pop();
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new q1(this, {
                                    pressArray: this.d4,
                                    hoverArray: this.e4,
                                    hoverColorArray: this.f4,
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    selectedIndexes: this.f3,
                                    maxFontScale: this.getMaxFontSize()
                                }, undefined, elmtId, () => {
                                }, { page: "library/src/main/ets/components/segmentbutton.ets", line: 1290, i4: 9 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        pressArray: this.pressArray,
                                        hoverArray: this.hoverArray,
                                        hoverColorArray: this.hoverColorArray,
                                        optionsArray: this.options.buttons,
                                        options: this.options,
                                        selectedIndexes: this.selectedIndexes,
                                        maxFontScale: this.getMaxFontSize()
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            } else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    maxFontScale: this.getMaxFontSize()
                                });
                            }
                        }, { name: "SegmentButtonItemArrayComponent" });
                    }
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Stack.pop();
    }

    getMaxFontSize() {
        if (typeof this.maxFontScale === void 0) {
            return e1;
        }
        if (typeof this.maxFontScale === 'number') {
            return Math.max(Math.min(this.maxFontScale, f1), g1);
        }
        const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
        if (!resourceManager) {
            return e1;
        }
        try {
            return resourceManager.getNumber(this.maxFontScale.id);
        } catch (error) {
            console.error(`Ace SegmentButton getMaxFontSize, error: ${error.toString()}`);
            return e1;
        }
    }

    getSelectedChangeCurve() {
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            return null;
        }
        return curves.springMotion(0.347, 0.99);
    }

    updateAnimatedProperty(curve) {
        let t1 = () => {
            this.selectedItemPosition =
                this.selectedIndexes.length === 0 ? {} : this.buttonItemsPosition[this.selectedIndexes[0]];
            this.buttonItemsSelected.forEach((selected, index) => {
                this.buttonItemProperty[index].fontColor = selected ?
                    this.options.selectedFontColor ?? (this.options.type === 'tab' ?
                    h1.v1 : h1.w1) :
                    this.options.fontColor ?? h1.u1;
            });
        };
        if (curve) {
            Context.animateTo({ curve: curve }, t1);
        } else {
            t1();
        }
        this.buttonItemsSelected.forEach((selected, index) => {
            this.buttonItemProperty[index].fontSize = selected ? this.options.selectedFontSize ??
            h1.a2 : this.options.fontSize ?? h1.z1;
            this.buttonItemProperty[index].fontWeight =
                selected ? this.options.selectedFontWeight ?? FontWeight.Medium :
                    this.options.fontWeight ?? FontWeight.Regular;
            this.buttonItemProperty[index].isSelected = selected;
        });
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default {
  SegmentButton,
  SegmentButtonOptions,
  SegmentButtonItemOptionsArray,
  SegmentButtonItemOptions,
};
