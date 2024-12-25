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

var j = (this && this.j) || function (t3, target, key, desc) {
    var c = arguments.length,
        r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.o1 === "function") {
        r = Reflect.o1(t3, target, key, desc);
    } else {
        for (var u3 = t3.length - 1; u3 >= 0; u3--) {
            if (d = t3[u3]) {
                r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
            }
        }
    }
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var m, o;
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}
const curves = globalThis.requireNativeModule('ohos.curves');
const KeyCode = globalThis.requireNapi('multimodalInput.keyCode').KeyCode;
const util = globalThis.requireNapi('util');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const t = requireNapi('i18n');

const u = 2;
const a1 = 5;
const b1 = 1;
const c1 = 2;
const d1 = 1;
const e1 = {
    q1: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_text_secondary'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    s1: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_text_primary'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    t1: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_foreground_contrary'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    u1: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.ohos_id_text_size_body2'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    v1: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.ohos_id_text_size_body2'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    BACKGROUND_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_button_normal'],
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
        "type": 10001,
        params: ['sys.color.ohos_id_color_emphasize'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    a2: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_focused_outline'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    b2: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_hover'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    c2: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_click_effect'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    d2: BlurStyle.NONE
};

function i(first, second) {
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
SegmentButtonItemOptions = j([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = m = class SegmentButtonItemOptionsArray extends Array {
    constructor(s3) {
        super(typeof s3 === 'number' ? s3 : 0);
        this.e2 = void 0;
        this.deleteCount = void 0;
        this.f2 = void 0;
        if (typeof s3 !== 'number' && s3 !== void 0) {
            super.push(...s3.map((element) => new SegmentButtonItemOptions(element)));
        }
    }

    push(...items) {
        if (this.length + items.length > a1) {
            console.warn('Exceeded the maximum number of elements (5).');
            return this.length;
        }
        this.e2 = this.length;
        this.deleteCount = 0;
        this.f2 = items.length;
        return super.push(...items.map((element) => new SegmentButtonItemOptions(element)));
    }

    pop() {
        if (this.length <= u) {
            console.warn('Below the minimum number of elements (2).');
            return void 0;
        }
        this.e2 = this.length - 1;
        this.deleteCount = 1;
        this.f2 = 0;
        return super.pop();
    }

    shift() {
        if (this.length <= u) {
            console.warn('Below the minimum number of elements (2).');
            return void 0;
        }
        this.e2 = 0;
        this.deleteCount = 1;
        this.f2 = 0;
        return super.shift();
    }

    unshift(...items) {
        if (this.length + items.length > a1) {
            console.warn('Exceeded the maximum number of elements (5).');
            return this.length;
        }
        if (items.length > 0) {
            this.e2 = 0;
            this.deleteCount = 0;
            this.f2 = items.length;
        }
        return super.unshift(...items.map((element) => new SegmentButtonItemOptions(element)));
    }

    splice(start, deleteCount, ...items) {
        let length = (this.length - deleteCount) < 0 ? 0 : (this.length - deleteCount);
        length += items.length;
        if (length < u) {
            console.warn('Below the minimum number of elements (2).');
            return [];
        }
        if (length > a1) {
            console.warn('Exceeded the maximum number of elements (5).');
            return [];
        }
        this.e2 = start;
        this.deleteCount = deleteCount;
        this.f2 = items.length;
        return super.splice(start, deleteCount, ...items);
    }

    static create(elements) {
        return new m(elements);
    }
};
SegmentButtonItemOptionsArray = m = j([
    Observed
], SegmentButtonItemOptionsArray);

export { SegmentButtonItemOptionsArray };
let SegmentButtonOptions = o = class SegmentButtonOptions {
    get buttons() {
        return this.g2;
    }

    set buttons(val) {
        if (this.g2 !== void 0 && this.g2 !== val) {
            this.h2?.();
        }
        this.g2 = val;
    }

    constructor(options) {
        this.multiply = false;
        this.i2 = false;
        this.showIcon = false;
        this.g2 = void 0;
        this.fontColor = options.fontColor ?? e1.q1;
        this.selectedFontColor = options.selectedFontColor ?? e1.s1;
        this.fontSize = options.fontSize ?? e1.u1;
        this.selectedFontSize = options.selectedFontSize ?? e1.v1;
        this.fontWeight = options.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = options.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = options.backgroundColor ?? e1.BACKGROUND_COLOR;
        this.selectedBackgroundColor = options.selectedBackgroundColor ?? e1.w1;
        this.imageSize = options.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = options.buttonPadding;
        this.textPadding = options.textPadding;
        this.type = options.type;
        this.backgroundBlurStyle = options.backgroundBlurStyle ?? e1.d2;
        this.localizedTextPadding = options.localizedTextPadding;
        this.localizedButtonPadding = options.localizedButtonPadding;
        this.direction = options.direction ?? Direction.Auto;
        this.buttons = new SegmentButtonItemOptionsArray(options.buttons);
        if (this.type === 'capsule') {
            this.multiply = options.multiply ?? false;
            this.j2();
            this.selectedFontColor = options.selectedFontColor ?? e1.t1;
            this.selectedBackgroundColor = options.selectedBackgroundColor ??
            e1.z1;
        } else {
            this.i2 = true;
        }
        this.l2 = this.multiply ? 0 : 2;
    }

    j2() {
        this.buttons?.forEach(button => {
            this.i2 ||= button.text !== void 0;
            this.showIcon ||= button.icon !== void 0 || button.selectedIcon !== void 0;
        });
        if (this.i2 && this.showIcon) {
            this.m2 = 12;
            this.n2 = 14;
        }
    }

    static tab(options) {
        return new o({
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
        return new o({
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
SegmentButtonOptions = o = j([
    Observed
], SegmentButtonOptions);

export { SegmentButtonOptions };

class f1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(params.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.__optionsArray.set(params.optionsArray);
        this.__options.set(params.options);
    }

    updateStateVars(params) {
        this.__optionsArray.set(params.optionsArray);
        this.__options.set(params.options);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__optionsArray.purgeDependencyOnElmtId(rmElmtId);
        this.__options.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__optionsArray.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        this.__buttonItemsSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get optionsArray() {
        return this.__optionsArray.get();
    }

    get options() {
        return this.__options.get();
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(newValue) {
        this.__buttonBorderRadius.set(newValue);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(newValue) {
        this.__buttonItemsSize.set(newValue);
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.l2);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const r3 = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (index < a1) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[index].height);
                                Stack.backgroundColor(this.options.backgroundColor ?? e1.BACKGROUND_COLOR);
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

class g1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(params.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__selectedItemPosition = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.__optionsArray.set(params.optionsArray);
        this.__options.set(params.options);
    }

    updateStateVars(params) {
        this.__optionsArray.set(params.optionsArray);
        this.__options.set(params.options);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__optionsArray.purgeDependencyOnElmtId(rmElmtId);
        this.__options.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedIndexes.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedItemPosition.purgeDependencyOnElmtId(rmElmtId);
        this.__zoomScaleArray.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__optionsArray.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__buttonItemsSize.aboutToBeDeleted();
        this.__selectedItemPosition.aboutToBeDeleted();
        this.__zoomScaleArray.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get optionsArray() {
        return this.__optionsArray.get();
    }

    get options() {
        return this.__options.get();
    }

    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }

    set selectedIndexes(newValue) {
        this.__selectedIndexes.set(newValue);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(newValue) {
        this.__buttonItemsSize.set(newValue);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(newValue) {
        this.__selectedItemPosition.set(newValue);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(newValue) {
        this.__zoomScaleArray.set(newValue);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(newValue) {
        this.__buttonBorderRadius.set(newValue);
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
                            (this.options.type === 'tab' ? e1.w1 :
                            e1.z1));
                        Stack.position(ObservedObject.GetRawObject(this.selectedItemPosition));
                        Stack.scale({
                            x: this.zoomScaleArray[this.selectedIndexes[0]],
                            y: this.zoomScaleArray[this.selectedIndexes[0]]
                        });
                        Stack.shadow(ShadowStyle.OUTER_DEFAULT_XS);
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

class h1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(params.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__multiColor =
            new ObservedPropertyObjectPU(Array.from({ length: a1 }, (q3, index) => Color.Transparent), this,
                "multiColor");
        this.setInitiallyProvidedValue(params);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.__optionsArray.set(params.optionsArray);
        this.__options.set(params.options);
        if (params.multiColor !== undefined) {
            this.multiColor = params.multiColor;
        }
    }

    updateStateVars(params) {
        this.__optionsArray.set(params.optionsArray);
        this.__options.set(params.options);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__optionsArray.purgeDependencyOnElmtId(rmElmtId);
        this.__options.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedIndexes.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
        this.__zoomScaleArray.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
        this.__multiColor.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__optionsArray.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__buttonItemsSize.aboutToBeDeleted();
        this.__zoomScaleArray.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        this.__multiColor.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get optionsArray() {
        return this.__optionsArray.get();
    }

    get options() {
        return this.__options.get();
    }

    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }

    set selectedIndexes(newValue) {
        this.__selectedIndexes.set(newValue);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(newValue) {
        this.__buttonItemsSize.set(newValue);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(newValue) {
        this.__zoomScaleArray.set(newValue);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(newValue) {
        this.__buttonBorderRadius.set(newValue);
    }

    get multiColor() {
        return this.__multiColor.get();
    }

    set multiColor(newValue) {
        this.__multiColor.set(newValue);
    }

    onOptionsChange() {
        for (let p3 = 0; p3 < this.selectedIndexes.length; p3++) {
            this.multiColor[this.selectedIndexes[p3]] = this.options.selectedBackgroundColor ??
            e1.z1;
        }
    }

    onSelectedChange() {
        for (let n3 = 0; n3 < a1; n3++) {
            this.multiColor[n3] = Color.Transparent;
        }
        for (let m3 = 0; m3 < this.selectedIndexes.length; m3++) {
            this.multiColor[this.selectedIndexes[m3]] = this.options.selectedBackgroundColor ??
            e1.z1;
        }
    }

    aboutToAppear() {
        for (let l3 = 0; l3 < this.selectedIndexes.length; l3++) {
            this.multiColor[this.selectedIndexes[l3]] = this.options.selectedBackgroundColor ??
            e1.z1;
        }
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.l2);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const k3 = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (index < a1) {
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

class i1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, "selectedIndexes");
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(params.focusIndex, this, "focusIndex");
        this.__maxFontScale = new SynchedPropertyObjectOneWayPU(params.maxFontScale, this, "maxFontScale");
        this.__itemOptions = new SynchedPropertyNesedObjectPU(params.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(params.property, this, "property");
        this.__index = new SynchedPropertySimpleOneWayPU(params.index, this, "index");
        this.groupId = '';
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.__itemOptions.set(params.itemOptions);
        this.__options.set(params.options);
        this.__property.set(params.property);
        if (params.groupId !== undefined) {
            this.groupId = params.groupId;
        }
    }

    updateStateVars(params) {
        this.__maxFontScale.reset(params.maxFontScale);
        this.__itemOptions.set(params.itemOptions);
        this.__options.set(params.options);
        this.__property.set(params.property);
        this.__index.reset(params.index);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__selectedIndexes.purgeDependencyOnElmtId(rmElmtId);
        this.__focusIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__maxFontScale.purgeDependencyOnElmtId(rmElmtId);
        this.__itemOptions.purgeDependencyOnElmtId(rmElmtId);
        this.__options.purgeDependencyOnElmtId(rmElmtId);
        this.__property.purgeDependencyOnElmtId(rmElmtId);
        this.__index.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__selectedIndexes.aboutToBeDeleted();
        this.__focusIndex.aboutToBeDeleted();
        this.__maxFontScale.aboutToBeDeleted();
        this.__itemOptions.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__property.aboutToBeDeleted();
        this.__index.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }

    set selectedIndexes(newValue) {
        this.__selectedIndexes.set(newValue);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(newValue) {
        this.__focusIndex.set(newValue);
    }

    get maxFontScale() {
        return this.__maxFontScale.get();
    }

    set maxFontScale(newValue) {
        this.__maxFontScale.set(newValue);
    }

    get itemOptions() {
        return this.__itemOptions.get();
    }

    get options() {
        return this.__options.get();
    }

    get property() {
        return this.__property.get();
    }

    get index() {
        return this.__index.get();
    }

    set index(newValue) {
        this.__index.set(newValue);
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
        if (this.options.type === 'capsule' && this.options.i2 && this.options.showIcon) {
            return {
                top: LengthMetrics.vp(6),
                bottom: LengthMetrics.vp(6),
                start: LengthMetrics.vp(8),
                end: LengthMetrics.vp(8)
            };
        }
        return {
            top: LengthMetrics.vp(4),
            bottom: LengthMetrics.vp(4),
            start: LengthMetrics.vp(8),
            end: LengthMetrics.vp(8)
        };
    }

    getAccessibilityText() {
        if (this.selectedIndexes.includes(this.index) &&
            typeof this.itemOptions.selectedIconAccessibilityText !== undefined) {
            return this.itemOptions.selectedIconAccessibilityText;
        } else if (!this.selectedIndexes.includes(this.index) &&
            typeof this.itemOptions.iconAccessibilityText !== undefined) {
            return this.itemOptions.iconAccessibilityText;
        }
        return undefined;
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create({ space: 2 });
            Column.direction(this.options.direction);
            Column.focusScopePriority(this.groupId,
                Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.getButtonPadding());
            Column.constraintSize({ minHeight: 28 });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon);
                        Image.direction(this.options.direction);
                        Image.size(this.options.imageSize ?? { width: 24, height: 24 });
                        Image.draggable(false);
                        Image.fillColor(this.property.isSelected ? (this.options.selectedFontColor ??
                        e1.t1) : (this.options.fontColor ??
                        e1.q1));
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
            if (this.options.i2) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.itemOptions.text);
                        Text.direction(this.options.direction);
                        Text.fontColor(this.property.fontColor);
                        Text.fontWeight(this.property.fontWeight);
                        Text.fontSize(this.property.fontSize);
                        Text.minFontSize(9);
                        Text.maxFontSize(this.property.fontSize);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.maxFontScale));
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
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

let j1 = class HoverColorProperty {
    constructor() {
        this.o2 = Color.Transparent;
    }
};
j1 = j([
    Observed
], j1);

class l1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(params.press, this, "press");
        this.__hover = new SynchedPropertySimpleOneWayPU(params.hover, this, "hover");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(params.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__options = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.pressIndex = 0;
        this.pressColor = e1.c2;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.__colorProperty.set(params.colorProperty);
        this.__options.set(params.options);
        if (params.pressIndex !== undefined) {
            this.pressIndex = params.pressIndex;
        }
        if (params.pressColor !== undefined) {
            this.pressColor = params.pressColor;
        }
    }

    updateStateVars(params) {
        this.__press.reset(params.press);
        this.__hover.reset(params.hover);
        this.__colorProperty.set(params.colorProperty);
        this.__options.set(params.options);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
        this.__press.purgeDependencyOnElmtId(rmElmtId);
        this.__hover.purgeDependencyOnElmtId(rmElmtId);
        this.__colorProperty.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
        this.__options.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__buttonItemsSize.aboutToBeDeleted();
        this.__press.aboutToBeDeleted();
        this.__hover.aboutToBeDeleted();
        this.__colorProperty.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(newValue) {
        this.__buttonItemsSize.set(newValue);
    }

    get press() {
        return this.__press.get();
    }

    set press(newValue) {
        this.__press.set(newValue);
    }

    get hover() {
        return this.__hover.get();
    }

    set hover(newValue) {
        this.__hover.set(newValue);
    }

    get colorProperty() {
        return this.__colorProperty.get();
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(newValue) {
        this.__buttonBorderRadius.set(newValue);
    }

    get options() {
        return this.__options.get();
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.size(this.buttonItemsSize[this.pressIndex]);
            Stack.backgroundColor(this.press && this.hover ? this.pressColor : this.colorProperty.o2);
            Stack.borderRadius(this.buttonBorderRadius[this.pressIndex]);
        }, Stack);
        Stack.pop();
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
        this.__optionsArray = new SynchedPropertyNesedObjectPU(params.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = this.initializeConsume("componentSize", "componentSize");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__buttonItemsPosition = this.initializeConsume("buttonItemsPosition", "buttonItemsPosition");
        this.__focusIndex = this.initializeConsume("focusIndex", "focusIndex");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonItemProperty = this.initializeConsume("buttonItemProperty", "buttonItemProperty");
        this.__buttonItemsSelected = this.initializeConsume("buttonItemsSelected", "buttonItemsSelected");
        this.__pressArray = new SynchedPropertyObjectTwoWayPU(params.pressArray, this, "pressArray");
        this.__hoverArray = new SynchedPropertyObjectTwoWayPU(params.hoverArray, this, "hoverArray");
        this.__hoverColorArray = new SynchedPropertyObjectTwoWayPU(params.hoverColorArray, this, "hoverColorArray");
        this.__maxFontScale = new SynchedPropertyObjectOneWayPU(params.maxFontScale, this, "maxFontScale");
        this.__buttonWidth =
            new ObservedPropertyObjectPU(Array.from({ length: a1 }, (j3, index) => 0), this, "buttonWidth");
        this.__buttonHeight =
            new ObservedPropertyObjectPU(Array.from({ length: a1 }, (i3, index) => 0), this, "buttonHeight");
        this.buttonItemsRealHeight = Array.from({ length: a1 }, (h3, index) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.onItemClicked = undefined;
        this.setInitiallyProvidedValue(params);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.__optionsArray.set(params.optionsArray);
        this.__options.set(params.options);
        if (params.buttonWidth !== undefined) {
            this.buttonWidth = params.buttonWidth;
        }
        if (params.buttonHeight !== undefined) {
            this.buttonHeight = params.buttonHeight;
        }
        if (params.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = params.buttonItemsRealHeight;
        }
        if (params.groupId !== undefined) {
            this.groupId = params.groupId;
        }
        if (params.onItemClicked !== undefined) {
            this.onItemClicked = params.onItemClicked;
        }
    }

    updateStateVars(params) {
        this.__optionsArray.set(params.optionsArray);
        this.__options.set(params.options);
        this.__maxFontScale.reset(params.maxFontScale);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__optionsArray.purgeDependencyOnElmtId(rmElmtId);
        this.__options.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedIndexes.purgeDependencyOnElmtId(rmElmtId);
        this.__componentSize.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(rmElmtId);
        this.__focusIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__zoomScaleArray.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemProperty.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(rmElmtId);
        this.__pressArray.purgeDependencyOnElmtId(rmElmtId);
        this.__hoverArray.purgeDependencyOnElmtId(rmElmtId);
        this.__hoverColorArray.purgeDependencyOnElmtId(rmElmtId);
        this.__maxFontScale.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonHeight.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__optionsArray.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__componentSize.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        this.__buttonItemsSize.aboutToBeDeleted();
        this.__buttonItemsPosition.aboutToBeDeleted();
        this.__focusIndex.aboutToBeDeleted();
        this.__zoomScaleArray.aboutToBeDeleted();
        this.__buttonItemProperty.aboutToBeDeleted();
        this.__buttonItemsSelected.aboutToBeDeleted();
        this.__pressArray.aboutToBeDeleted();
        this.__hoverArray.aboutToBeDeleted();
        this.__hoverColorArray.aboutToBeDeleted();
        this.__maxFontScale.aboutToBeDeleted();
        this.__buttonWidth.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get optionsArray() {
        return this.__optionsArray.get();
    }

    get options() {
        return this.__options.get();
    }

    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }

    set selectedIndexes(newValue) {
        this.__selectedIndexes.set(newValue);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(newValue) {
        this.__componentSize.set(newValue);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(newValue) {
        this.__buttonBorderRadius.set(newValue);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(newValue) {
        this.__buttonItemsSize.set(newValue);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(newValue) {
        this.__buttonItemsPosition.set(newValue);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(newValue) {
        this.__focusIndex.set(newValue);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(newValue) {
        this.__zoomScaleArray.set(newValue);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(newValue) {
        this.__buttonItemProperty.set(newValue);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(newValue) {
        this.__buttonItemsSelected.set(newValue);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(newValue) {
        this.__pressArray.set(newValue);
    }

    get hoverArray() {
        return this.__hoverArray.get();
    }

    set hoverArray(newValue) {
        this.__hoverArray.set(newValue);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(newValue) {
        this.__hoverColorArray.set(newValue);
    }

    get maxFontScale() {
        return this.__maxFontScale.get();
    }

    set maxFontScale(newValue) {
        this.__maxFontScale.set(newValue);
    }

    get buttonWidth() {
        return this.__buttonWidth.get();
    }

    set buttonWidth(newValue) {
        this.__buttonWidth.set(newValue);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(newValue) {
        this.__buttonHeight.set(newValue);
    }

    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((value, index) => {
            this.buttonWidth[index] = value.width;
            this.buttonHeight[index] = value.height;
        });
    }

    changeSelectedIndexes(c3) {
        if (this.optionsArray.e2 === void 0 || this.optionsArray.deleteCount === void 0 ||
            this.optionsArray.f2 === void 0) {
            return;
        }
        if (!(this.options.multiply ?? false)) {
            if (this.selectedIndexes[0] === void 0) {
                return;
            }
            if (this.selectedIndexes[0] < this.optionsArray.e2) {
                return;
            }
            if (this.optionsArray.e2 + this.optionsArray.deleteCount > this.selectedIndexes[0]) {
                if (this.options.type === 'tab') {
                    this.selectedIndexes[0] = 0;
                } else if (this.options.type === 'capsule') {
                    this.selectedIndexes = [];
                }
            } else {
                this.selectedIndexes[0] =
                    this.selectedIndexes[0] - this.optionsArray.deleteCount + this.optionsArray.f2;
            }
        } else {
            let d3 = this.selectedIndexes;
            for (let f3 = 0; f3 < this.optionsArray.deleteCount; f3++) {
                let g3 = d3.indexOf(this.optionsArray.e2);
                let indexes = d3.map(value => this.optionsArray.e2 &&
                    (value > this.optionsArray.e2) ? value - 1 : value);
                if (g3 !== -1) {
                    indexes.splice(g3, 1);
                }
                d3 = indexes;
            }
            for (let e3 = 0; e3 < this.optionsArray.f2; e3++) {
                let indexes = d3.map(value => this.optionsArray.e2 &&
                    (value >= this.optionsArray.e2) ? value + 1 : value);
                d3 = indexes;
            }
            this.selectedIndexes = d3;
        }
    }

    changeFocusIndex(b3) {
        if (this.optionsArray.e2 === void 0 || this.optionsArray.deleteCount === void 0 ||
            this.optionsArray.f2 === void 0) {
            return;
        }
        if (this.focusIndex === -1) {
            return;
        }
        if (this.focusIndex < this.optionsArray.e2) {
            return;
        }
        if (this.optionsArray.e2 + this.optionsArray.deleteCount > this.focusIndex) {
            this.focusIndex = 0;
        } else {
            this.focusIndex = this.focusIndex - this.optionsArray.deleteCount + this.optionsArray.f2;
        }
    }

    onOptionsArrayChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        let a3 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.e2 !== void 0 && this.optionsArray.deleteCount !== void 0 &&
            this.optionsArray.f2 !== void 0) {
            this.changeSelectedIndexes(a3);
            this.changeFocusIndex(a3);
            this.optionsArray.e2 = void 0;
            this.optionsArray.deleteCount = void 0;
            this.optionsArray.f2 = void 0;
        }
    }

    onOptionsChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        this.calculateBorderRadius();
    }

    aboutToAppear() {
        for (let index = 0; index < this.buttonItemsRealHeight.length; index++) {
            this.buttonItemsRealHeight[index] = 0;
        }
    }

    getBorderRadius(index) {
        let borderRadius = this.buttonBorderRadius[index];
        if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex]) {
            return {
                topStart: LengthMetrics.vp((borderRadius.topStart?.value ?? 0) + 4),
                topEnd: LengthMetrics.vp((borderRadius.topEnd?.value ?? 0) + 4),
                bottomStart: LengthMetrics.vp((borderRadius.bottomStart?.value ?? 0) + 4),
                bottomEnd: LengthMetrics.vp((borderRadius.bottomEnd?.value ?? 0) + 4)
            };
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
            Stack.borderColor(e1.a2);
            Stack.borderWidth(2);
        }, Stack);
        Stack.pop();
        Stack.pop();
    }

    calculateBorderRadius() {
        let v2 = Array.from({
            length: a1
        }, (z2, index) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        });
        for (let index = 0; index < this.buttonBorderRadius.length; index++) {
            let w2 = this.buttonItemsSize[index].height / 2;
            if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                v2[index].topStart = LengthMetrics.vp(this.options.m2 ?? w2);
                v2[index].topEnd = LengthMetrics.vp(this.options.m2 ?? w2);
                v2[index].bottomStart = LengthMetrics.vp(this.options.m2 ?? w2);
                v2[index].bottomEnd = LengthMetrics.vp(this.options.m2 ?? w2);
            } else {
                if (index === 0) {
                    v2[index].topStart = LengthMetrics.vp(this.options.m2 ?? w2);
                    v2[index].topEnd = LengthMetrics.vp(0);
                    v2[index].bottomStart = LengthMetrics.vp(this.options.m2 ?? w2);
                    v2[index].bottomEnd = LengthMetrics.vp(0);
                } else if (this.options.buttons &&
                    index === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    v2[index].topStart = LengthMetrics.vp(0);
                    v2[index].topEnd = LengthMetrics.vp(this.options.m2 ?? w2);
                    v2[index].bottomStart = LengthMetrics.vp(0);
                    v2[index].bottomEnd = LengthMetrics.vp(this.options.m2 ?? w2);
                } else {
                    v2[index].topStart = LengthMetrics.vp(0);
                    v2[index].topEnd = LengthMetrics.vp(0);
                    v2[index].bottomStart = LengthMetrics.vp(0);
                    v2[index].bottomEnd = LengthMetrics.vp(0);
                }
            }
        }
        this.buttonBorderRadius = v2;
    }

    getAccessibilityDescription(value) {
        return (typeof value !== undefined) ? value : undefined;
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
                        Row.padding(this.options.l2);
                        Row.onSizeChange((u2, newValue) => {
                            this.componentSize = { width: newValue.width, height: newValue.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        ForEach.create();
                        const forEachItemGenFunction = (_item, index) => {
                            const item = _item;
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                If.create();
                                if (index < a1) {
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
                                            Button.onSizeChange((t2, newValue) => {
                                                this.buttonItemsSize[index] = {
                                                    width: newValue.width,
                                                    height: this.buttonItemsSize[index].height
                                                };
                                                if (newValue.width) {
                                                    this.buttonItemsPosition[index] = {
                                                        start: LengthMetrics.vp(Number.parseFloat(this.options.l2.toString()) +
                                                            (Number.parseFloat(newValue.width.toString()) + 1) * index),
                                                        top: LengthMetrics.px(Math.floor(this.getUIContext()
                                                            .vp2px(Number.parseFloat(this.options.l2.toString()))))
                                                    };
                                                }
                                            });
                                            ViewStackProcessor.visualState("normal");
                                            Button.overlay(undefined);
                                            ViewStackProcessor.visualState("focused");
                                            Button.overlay({
                                                builder: () => {
                                                    this.focusStack.call(this, index);
                                                }
                                            }, {
                                                align: Alignment.Center
                                            });
                                            ViewStackProcessor.visualState();
                                            Button.onFocus(() => {
                                                this.focusIndex = index;
                                            });
                                            Gesture.create(GesturePriority.Low);
                                            TapGesture.create();
                                            TapGesture.onAction(() => {
                                                if (this.onItemClicked) {
                                                    this.onItemClicked(index);
                                                }
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
                                                if (event.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (event.type === TouchType.Down) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[index] = 0.95;
                                                    });
                                                } else if (event.type === TouchType.Up ||
                                                    event.type === TouchType.Cancel) {
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
                                                        this.hoverColorArray[index].o2 = (e1.b2);
                                                    });
                                                } else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[index].o2 = Color.Transparent;
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
                                            __Common__.create();
                                            __Common__.onSizeChange((s2, newValue) => {
                                                this.buttonItemsRealHeight[index] = newValue.height;
                                                let maxHeight = Math.max(...this.buttonItemsRealHeight.slice(0,
                                                    this.options.buttons ?
                                                    this.options.buttons.length : 0));
                                                for (let index = 0; index < this.buttonItemsSize.length; index++) {
                                                    this.buttonItemsSize[index] =
                                                        { width: this.buttonItemsSize[index].width, height: maxHeight };
                                                }
                                                this.calculateBorderRadius();
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                if (isInitialRender) {
                                                    let componentCall = new i1(this, {
                                                        selectedIndexes: this.__selectedIndexes,
                                                        focusIndex: this.__focusIndex,
                                                        index: index,
                                                        itemOptions: item,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[index],
                                                        groupId: this.groupId,
                                                        maxFontScale: this.maxFontScale
                                                    }, undefined, elmtId, () => {
                                                    }, {
                                                        page: "segmentbutton/src/main/ets/components/MainPage.ets",
                                                        line: 805,
                                                        q2: 15
                                                    });
                                                    ViewPU.create(componentCall);
                                                    let paramsLambda = () => {
                                                        return {
                                                            selectedIndexes: this.selectedIndexes,
                                                            focusIndex: this.focusIndex,
                                                            index: index,
                                                            itemOptions: item,
                                                            options: this.options,
                                                            property: this.buttonItemProperty[index],
                                                            groupId: this.groupId,
                                                            maxFontScale: this.maxFontScale
                                                        };
                                                    };
                                                    componentCall.paramsGenerator_ = paramsLambda;
                                                } else {
                                                    this.updateStateVarsOfChildByElmtId(elmtId, {
                                                        index: index,
                                                        itemOptions: item,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[index],
                                                        maxFontScale: this.maxFontScale
                                                    });
                                                }
                                            }, { name: "SegmentButtonItem" });
                                        }
                                        __Common__.pop();
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

let n1 = class ItemProperty {
    constructor() {
        this.fontColor = e1.q1;
        this.fontSize = e1.u1;
        this.fontWeight = FontWeight.Regular;
        this.isSelected = false;
    }
};
n1 = j([
    Observed
], n1);

export class SegmentButton extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__options = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, "selectedIndexes");
        this.onItemClicked = undefined;
        this.__maxFontScale = new SynchedPropertyObjectOneWayPU(params.maxFontScale, this, "maxFontScale");
        this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, "componentSize");
        this.addProvidedVar("componentSize", this.__componentSize, false);
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({
            length: a1
        }, (r2, index) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        }), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.__buttonBorderRadius, false);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: a1 }, (q2, index) => {
            return {};
        }), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.__buttonItemsSize, false);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({
            length: a1
        }, (o2, index) => {
            return {};
        }), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.__buttonItemsPosition, false);
        this.__buttonItemsSelected =
            new ObservedPropertyObjectPU(Array.from({ length: a1 }, (n2, index) => false), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected, false);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: a1
        }, (m2, index) => new n1()), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty, false);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex, false);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition, false);
        this.__zoomScaleArray =
            new ObservedPropertyObjectPU(Array.from({ length: a1 }, (l2, index) => 1.0), this, "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.__zoomScaleArray, false);
        this.__pressArray =
            new ObservedPropertyObjectPU(Array.from({ length: a1 }, (k2, index) => false), this, "pressArray");
        this.__hoverArray =
            new ObservedPropertyObjectPU(Array.from({ length: a1 }, (j2, index) => false), this, "hoverArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: a1
        }, (i2, index) => new j1()), this, "hoverColorArray");
        this.doSelectedChangeAnimate = false;
        this.isCurrentPositionSelected = false;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = false;
        this.__shouldMirror = new ObservedPropertySimplePU(false, this, "shouldMirror");
        this.setInitiallyProvidedValue(params);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.declareWatch("buttonItemsPosition", this.onItemsPositionChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.__options.set(params.options);
        if (params.onItemClicked !== undefined) {
            this.onItemClicked = params.onItemClicked;
        }
        if (params.maxFontScale === undefined) {
            this.__maxFontScale.set(b1);
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
        this.__options.set(params.options);
        this.__maxFontScale.reset(params.maxFontScale);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__options.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedIndexes.purgeDependencyOnElmtId(rmElmtId);
        this.__maxFontScale.purgeDependencyOnElmtId(rmElmtId);
        this.__componentSize.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemProperty.purgeDependencyOnElmtId(rmElmtId);
        this.__focusIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedItemPosition.purgeDependencyOnElmtId(rmElmtId);
        this.__zoomScaleArray.purgeDependencyOnElmtId(rmElmtId);
        this.__pressArray.purgeDependencyOnElmtId(rmElmtId);
        this.__hoverArray.purgeDependencyOnElmtId(rmElmtId);
        this.__hoverColorArray.purgeDependencyOnElmtId(rmElmtId);
        this.__shouldMirror.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__maxFontScale.aboutToBeDeleted();
        this.__componentSize.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        this.__buttonItemsSize.aboutToBeDeleted();
        this.__buttonItemsPosition.aboutToBeDeleted();
        this.__buttonItemsSelected.aboutToBeDeleted();
        this.__buttonItemProperty.aboutToBeDeleted();
        this.__focusIndex.aboutToBeDeleted();
        this.__selectedItemPosition.aboutToBeDeleted();
        this.__zoomScaleArray.aboutToBeDeleted();
        this.__pressArray.aboutToBeDeleted();
        this.__hoverArray.aboutToBeDeleted();
        this.__hoverColorArray.aboutToBeDeleted();
        this.__shouldMirror.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get options() {
        return this.__options.get();
    }

    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }

    set selectedIndexes(newValue) {
        this.__selectedIndexes.set(newValue);
    }

    get maxFontScale() {
        return this.__maxFontScale.get();
    }

    set maxFontScale(newValue) {
        this.__maxFontScale.set(newValue);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(newValue) {
        this.__componentSize.set(newValue);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(newValue) {
        this.__buttonBorderRadius.set(newValue);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(newValue) {
        this.__buttonItemsSize.set(newValue);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(newValue) {
        this.__buttonItemsPosition.set(newValue);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(newValue) {
        this.__buttonItemsSelected.set(newValue);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(newValue) {
        this.__buttonItemProperty.set(newValue);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(newValue) {
        this.__focusIndex.set(newValue);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(newValue) {
        this.__selectedItemPosition.set(newValue);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(newValue) {
        this.__zoomScaleArray.set(newValue);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(newValue) {
        this.__pressArray.set(newValue);
    }

    get hoverArray() {
        return this.__hoverArray.get();
    }

    set hoverArray(newValue) {
        this.__hoverArray.set(newValue);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(newValue) {
        this.__hoverColorArray.set(newValue);
    }

    get shouldMirror() {
        return this.__shouldMirror.get();
    }

    set shouldMirror(newValue) {
        this.__shouldMirror.set(newValue);
    }

    onItemsPositionChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        if (this.options.type === 'capsule') {
            this.options.j2();
        }
        if (this.doSelectedChangeAnimate) {
            this.updateAnimatedProperty(this.getSelectedChangeCurve());
        } else {
            this.updateAnimatedProperty(null);
        }
    }

    setItemsSelected() {
        this.buttonItemsSelected.forEach((h2, index) => {
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
        let g2 = this.selectedIndexes.some(index => {
            return (index === void 0 || index < 0 || (this.options.buttons && index >= this.options.buttons.length));
        });
        if (g2) {
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
        this.options.h2 = () => {
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
        return !i(x, this.panGestureStartPoint.x) || !i(y, this.panGestureStartPoint.y);
    }

    isShouldMirror() {
        if (this.options.direction == Direction.Rtl) {
            return true;
        }
        try {
            let f2 = t.System.getSystemLanguage();
            if (f2 === 'ug' && this.options.direction != Direction.Ltr) {
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
                let a2 = event.fingerList.find(Boolean);
                if (a2 === void 0) {
                    return;
                }
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                let b2 = a2.localX;
                let c2 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
                for (let d2 = 0; d2 < c2; d2++) {
                    b2 = b2 - this.buttonItemsSize[d2].width;
                    if (b2 >= 0) {
                        continue;
                    }
                    this.doSelectedChangeAnimate =
                        this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ?
                            false : true;
                    let e2 = this.isShouldMirror() ? c2 - 1 - d2 : d2;
                    if (this.onItemClicked) {
                        this.onItemClicked(e2);
                    }
                    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                        let selectedIndex = this.selectedIndexes.indexOf(e2);
                        if (selectedIndex === -1) {
                            this.selectedIndexes.push(e2);
                        } else {
                            this.selectedIndexes.splice(selectedIndex, 1);
                        }
                    } else {
                        this.selectedIndexes[0] = e2;
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
                let v1 = event.fingerList.find(Boolean);
                if (v1 === void 0) {
                    return;
                }
                let w1 = v1.localX;
                this.panGestureStartPoint = { x: v1.globalX, y: v1.globalY };
                this.isPanGestureMoved = false;
                for (let z1 = 0; z1 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); z1++) {
                    w1 = w1 - this.buttonItemsSize[z1].width;
                    if (w1 < 0) {
                        this.isCurrentPositionSelected = z1 === this.selectedIndexes[0] ? true : false;
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
                let q1 = event.fingerList.find(Boolean);
                if (q1 === void 0) {
                    return;
                }
                let s1 = q1.localX;
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(q1.globalX, q1.globalY)) {
                    this.isPanGestureMoved = true;
                }
                for (let u1 = 0; u1 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); u1++) {
                    s1 = s1 - this.buttonItemsSize[u1].width;
                    if (s1 < 0) {
                        this.doSelectedChangeAnimate = true;
                        this.selectedIndexes[0] = u1;
                        this.doSelectedChangeAnimate = false;
                        break;
                    }
                }
                this.zoomScaleArray.forEach((t1, index) => {
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
                let p1 = event.fingerList.find(Boolean);
                if (p1 === void 0) {
                    return;
                }
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(p1.globalX, p1.globalY)) {
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
            PanGesture.onActionCancel(() => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
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
                                            let componentCall = new f1(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                            }, undefined, elmtId, () => {
                                            }, {
                                                page: "segmentbutton/src/main/ets/components/MainPage.ets",
                                                line: 1111,
                                                q2: 11
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
                                    Stack.backgroundColor(this.options.backgroundColor ?? e1.BACKGROUND_COLOR);
                                    Stack.borderRadius(this.options.n2 ?? this.componentSize.height / 2);
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
                                                        if (index < a1) {
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
                                                                {
                                                                    this.observeComponentCreation2((elmtId,
                                                                        isInitialRender) => {
                                                                        if (isInitialRender) {
                                                                            let componentCall = new l1(this, {
                                                                                pressIndex: index,
                                                                                colorProperty: this.hoverColorArray[index],
                                                                                press: this.pressArray[index],
                                                                                hover: this.hoverArray[index],
                                                                                options: this.options,
                                                                            }, undefined, elmtId, () => {
                                                                            }, {
                                                                                page: "segmentbutton/src/main/ets/components/MainPage.ets",
                                                                                line: 1122,
                                                                                q2: 23
                                                                            });
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
                                                                            componentCall.paramsGenerator_ =
                                                                                paramsLambda;
                                                                        } else {
                                                                            this.updateStateVarsOfChildByElmtId(elmtId,
                                                                                {
                                                                                    colorProperty: this.hoverColorArray[index],
                                                                                    press: this.pressArray[index],
                                                                                    hover: this.hoverArray[index],
                                                                                    options: this.options
                                                                                });
                                                                        }
                                                                    }, { name: "PressAndHoverEffect" });
                                                                }
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
                        this.options.m2 : this.options.n2) ??
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
                                            let componentCall = new h1(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, elmtId, () => {
                                            }, {
                                                page: "segmentbutton/src/main/ets/components/MainPage.ets",
                                                line: 1148,
                                                q2: 13
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
                                            let componentCall = new g1(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, elmtId, () => {
                                            }, {
                                                page: "segmentbutton/src/main/ets/components/MainPage.ets",
                                                line: 1154,
                                                q2: 13
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
                                let componentCall = new m1(this, {
                                    pressArray: this.__pressArray,
                                    hoverArray: this.__hoverArray,
                                    hoverColorArray: this.__hoverColorArray,
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    selectedIndexes: this.__selectedIndexes,
                                    maxFontScale: this.getMaxFontSize(),
                                    onItemClicked: this.onItemClicked
                                }, undefined, elmtId, () => {
                                }, { page: "segmentbutton/src/main/ets/components/MainPage.ets", line: 1169, q2: 9 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        pressArray: this.pressArray,
                                        hoverArray: this.hoverArray,
                                        hoverColorArray: this.hoverColorArray,
                                        optionsArray: this.options.buttons,
                                        options: this.options,
                                        selectedIndexes: this.selectedIndexes,
                                        maxFontScale: this.getMaxFontSize(),
                                        onItemClicked: this.onItemClicked
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
            return b1;
        }
        if (typeof this.maxFontScale === 'number') {
            return Math.max(Math.min(this.maxFontScale, c1), d1);
        }
        const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
        if (!resourceManager) {
            return b1;
        }
        try {
            return resourceManager.getNumber(this.maxFontScale.id);
        } catch (error) {
            console.error(`Ace SegmentButton getMaxFontSize, error: ${error.toString()}`);
            return b1;
        }
    }

    getSelectedChangeCurve() {
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            return null;
        }
        return curves.springMotion(0.347, 0.99);
    }

    updateAnimatedProperty(curve) {
        let o1 = () => {
            this.selectedItemPosition =
                this.selectedIndexes.length === 0 ? {} : this.buttonItemsPosition[this.selectedIndexes[0]];
            this.buttonItemsSelected.forEach((selected, index) => {
                this.buttonItemProperty[index].fontColor = selected ?
                    this.options.selectedFontColor ?? (this.options.type === 'tab' ?
                    e1.s1 : e1.t1) :
                    this.options.fontColor ?? e1.q1;
            });
        };
        if (curve) {
            Context.animateTo({ curve: curve }, o1);
        } else {
            o1();
        }
        this.buttonItemsSelected.forEach((selected, index) => {
            this.buttonItemProperty[index].fontSize = selected ? this.options.selectedFontSize ??
            e1.v1 : this.options.fontSize ?? e1.u1;
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
