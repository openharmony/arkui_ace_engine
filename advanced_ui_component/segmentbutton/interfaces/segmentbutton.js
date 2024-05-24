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

var __decorate = (this && this.__decorate) || function (w16, x16, y16, z16) {
    var a17 = arguments.length,
        b17 = a17 < 3 ? x16 : z16 === null ? z16 = Object.getOwnPropertyDescriptor(x16, y16) : z16, c17;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        b17 = Reflect.decorate(w16, x16, y16, z16);
    else
        for (var d17 = w16.length - 1; d17 >= 0; d17--)
            if (c17 = w16[d17])
                b17 = (a17 < 3 ? c17(b17) : a17 > 3 ? c17(x16, y16, b17) : c17(x16, y16)) || b17;
    return a17 > 3 && b17 && Object.defineProperty(x16, y16, b17), b17;
};
var SegmentButtonItemOptionsArray_1, SegmentButtonOptions_1;
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}
const curves = globalThis.requireNativeModule("ohos.curves");
const KeyCode = globalThis.requireNapi("multimodalInput.keyCode").KeyCode;
const util = globalThis.requireNativeModule("@ohos.util");

const MIN_ITEM_COUNT = 2;
const MAX_ITEM_COUNT = 5;
const SegmentButtonTheme = {
    FONT_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_text_secondary'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    TAB_SELECTED_FONT_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_text_primary'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    CAPSULE_SELECTED_FONT_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_foreground_contrary'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    FONT_SIZE: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.ohos_id_text_size_body2'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    SELECTED_FONT_SIZE: {
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
    TAB_SELECTED_BACKGROUND_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_foreground_contrary'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    CAPSULE_SELECTED_BACKGROUND_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.ohos_id_color_emphasize'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    FOCUS_BORDER_COLOR: {
        "id": -1,
        "type": 10001,
        params: ["sys.color.ohos_id_color_focused_outline"],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    HOVER_COlOR: {
        "id": -1,
        "type": 10001,
        params: ["sys.color.ohos_id_color_hover"],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    PRESS_COLOR: {
        "id": -1,
        "type": 10001,
        params: ["sys.color.ohos_id_color_click_effect"],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    BACKGROUND_BLUR_STYLE: BlurStyle.NONE
};

function nearEqual(t16, u16) {
    return Math.abs(t16 - u16) < 0.001;
}

let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(s16) {
        this.icon = s16.icon;
        this.selectedIcon = s16.selectedIcon;
        this.text = s16.text;
    }
};
SegmentButtonItemOptions = __decorate([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends Array {
    constructor(p16) {
        super(typeof p16 === "number" ? p16 : 0);
        this.changeStartIndex = void 0;
        this.deleteCount = void 0;
        this.addLength = void 0;
        if (typeof p16 !== "number" && p16 !== void 0) {
            super.push(...p16.map((r16) => new SegmentButtonItemOptions(r16)));
        }
    }

    push(...m16) {
        if (this.length + m16.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        this.changeStartIndex = this.length;
        this.deleteCount = 0;
        this.addLength = m16.length;
        return super.push(...m16.map((o16) => new SegmentButtonItemOptions(o16)));
    }

    pop() {
        if (this.length <= MIN_ITEM_COUNT) {
            console.warn("Below the minimum number of elements (2).");
            return void 0;
        }
        this.changeStartIndex = this.length - 1;
        this.deleteCount = 1;
        this.addLength = 0;
        return super.pop();
    }

    shift() {
        if (this.length <= MIN_ITEM_COUNT) {
            console.warn("Below the minimum number of elements (2).");
            return void 0;
        }
        this.changeStartIndex = 0;
        this.deleteCount = 1;
        this.addLength = 0;
        return super.shift();
    }

    unshift(...j16) {
        if (this.length + j16.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        if (j16.length > 0) {
            this.changeStartIndex = 0;
            this.deleteCount = 0;
            this.addLength = j16.length;
        }
        return super.unshift(...j16.map((l16) => new SegmentButtonItemOptions(l16)));
    }

    splice(f16, g16, ...h16) {
        let i16 = (this.length - g16) < 0 ? 0 : (this.length - g16);
        i16 += h16.length;
        if (i16 < MIN_ITEM_COUNT) {
            console.warn("Below the minimum number of elements (2).");
            return [];
        }
        if (i16 > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return [];
        }
        this.changeStartIndex = f16;
        this.deleteCount = g16;
        this.addLength = h16.length;
        return super.splice(f16, g16, ...h16);
    }

    static create(e16) {
        return new SegmentButtonItemOptionsArray_1(e16);
    }
};
SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = __decorate([
    Observed
], SegmentButtonItemOptionsArray);

export { SegmentButtonItemOptionsArray };
let SegmentButtonOptions = SegmentButtonOptions_1 = class SegmentButtonOptions {
    get buttons() {
        return this._buttons;
    }

    set buttons(d16) {
        if (this._buttons !== void 0 && this._buttons !== d16) {
            this.onButtonsChange?.();
        }
        this._buttons = d16;
    }

    constructor(a16) {
        this.multiply = false;
        this.showText = false;
        this.showIcon = false;
        this._buttons = void 0;
        this.fontColor = a16.fontColor ?? SegmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = a16.selectedFontColor ?? SegmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = a16.fontSize ?? SegmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = a16.selectedFontSize ?? SegmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = a16.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = a16.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = a16.backgroundColor ?? SegmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = a16.selectedBackgroundColor ?? SegmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = a16.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = a16.buttonPadding ?? { top: 4, right: 8, bottom: 4, left: 8 };
        this.textPadding = a16.textPadding ?? 0;
        this.type = a16.type;
        this.backgroundBlurStyle = a16.backgroundBlurStyle ?? SegmentButtonTheme.BACKGROUND_BLUR_STYLE;
        this.buttons = new SegmentButtonItemOptionsArray(a16.buttons);
        if (this.type === "capsule") {
            this.multiply = a16.multiply ?? false;
            this.buttons.forEach(c16 => {
                this.showText ||= c16.text !== void 0;
                this.showIcon ||= c16.icon !== void 0 || c16.selectedIcon !== void 0;
            });
            if (this.showText && this.showIcon) {
                this.iconTextRadius = 12;
                this.buttonPadding = a16.buttonPadding ?? { top: 6, right: 8, bottom: 6, left: 8 };
                this.iconTextBackgroundRadius = 14;
            }
            this.selectedFontColor = a16.selectedFontColor ?? SegmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = a16.selectedBackgroundColor ?? SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
        else {
            this.showText = true;
        }
        this.componentPadding = this.multiply ? 0 : 2;
    }

    static tab(z15) {
        return new SegmentButtonOptions_1({
            type: "tab",
            buttons: z15.buttons,
            fontColor: z15.fontColor,
            selectedFontColor: z15.selectedFontColor,
            fontSize: z15.fontSize,
            selectedFontSize: z15.selectedFontSize,
            fontWeight: z15.fontWeight,
            selectedFontWeight: z15.selectedFontWeight,
            backgroundColor: z15.backgroundColor,
            selectedBackgroundColor: z15.selectedBackgroundColor,
            imageSize: z15.imageSize,
            buttonPadding: z15.buttonPadding,
            textPadding: z15.textPadding,
            backgroundBlurStyle: z15.backgroundBlurStyle
        });
    }

    static capsule(y15) {
        return new SegmentButtonOptions_1({
            type: "capsule",
            buttons: y15.buttons,
            multiply: y15.multiply,
            fontColor: y15.fontColor,
            selectedFontColor: y15.selectedFontColor,
            fontSize: y15.fontSize,
            selectedFontSize: y15.selectedFontSize,
            fontWeight: y15.fontWeight,
            selectedFontWeight: y15.selectedFontWeight,
            backgroundColor: y15.backgroundColor,
            selectedBackgroundColor: y15.selectedBackgroundColor,
            imageSize: y15.imageSize,
            buttonPadding: y15.buttonPadding,
            textPadding: y15.textPadding,
            backgroundBlurStyle: y15.backgroundBlurStyle
        });
    }
};
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([
    Observed
], SegmentButtonOptions);

export { SegmentButtonOptions };

class MultiSelectBackground extends ViewPU {
    constructor(s15, t15, u15, v15 = -1, w15 = undefined, x15) {
        super(s15, u15, v15, x15);
        if (typeof w15 === "function") {
            this.paramsGenerator_ = w15;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(t15.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(t15.options, this, "options");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(t15);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(r15) {
        this.__optionsArray.set(r15.optionsArray);
        this.__options.set(r15.options);
    }

    updateStateVars(q15) {
        this.__optionsArray.set(q15.optionsArray);
        this.__options.set(q15.options);
    }

    purgeVariableDependenciesOnElmtId(p15) {
        this.__optionsArray.purgeDependencyOnElmtId(p15);
        this.__options.purgeDependencyOnElmtId(p15);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(p15);
        this.__buttonItemsSize.purgeDependencyOnElmtId(p15);
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

    set buttonBorderRadius(o15) {
        this.__buttonBorderRadius.set(o15);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(n15) {
        this.__buttonItemsSize.set(n15);
    }

    initialRender() {
        this.observeComponentCreation2((l15, m15) => {
            Row.create({ space: 1 });
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((w14, x14) => {
            ForEach.create();
            const y14 = (a15, b15) => {
                const c15 = a15;
                this.observeComponentCreation2((e15, f15) => {
                    If.create();
                    if (b15 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((j15, k15) => {
                                Stack.create();
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[b15].height);
                                Stack.backgroundColor(this.options.backgroundColor ?? SegmentButtonTheme.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[b15]);
                                Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
                            }, Stack);
                            Stack.pop();
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(w14, this.optionsArray, y14, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SelectItem extends ViewPU {
    constructor(o14, p14, q14, r14 = -1, s14 = undefined, t14) {
        super(o14, q14, r14, t14);
        if (typeof s14 === "function") {
            this.paramsGenerator_ = s14;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(p14.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(p14.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(p14.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__selectedItemPosition = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(p14);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(n14) {
        this.__optionsArray.set(n14.optionsArray);
        this.__options.set(n14.options);
    }

    updateStateVars(m14) {
        this.__optionsArray.set(m14.optionsArray);
        this.__options.set(m14.options);
    }

    purgeVariableDependenciesOnElmtId(l14) {
        this.__optionsArray.purgeDependencyOnElmtId(l14);
        this.__options.purgeDependencyOnElmtId(l14);
        this.__selectedIndexes.purgeDependencyOnElmtId(l14);
        this.__buttonItemsSize.purgeDependencyOnElmtId(l14);
        this.__selectedItemPosition.purgeDependencyOnElmtId(l14);
        this.__zoomScaleArray.purgeDependencyOnElmtId(l14);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(l14);
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

    set selectedIndexes(k14) {
        this.__selectedIndexes.set(k14);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(j14) {
        this.__buttonItemsSize.set(j14);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(i14) {
        this.__selectedItemPosition.set(i14);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(h14) {
        this.__zoomScaleArray.set(h14);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(g14) {
        this.__buttonBorderRadius.set(g14);
    }

    initialRender() {
        this.observeComponentCreation2((z13, a14) => {
            If.create();
            if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e14, f14) => {
                        Stack.create();
                        Stack.borderRadius(this.buttonBorderRadius[this.selectedIndexes[0]]);
                        Stack.size(this.buttonItemsSize[this.selectedIndexes[0]]);
                        Stack.backgroundColor(this.options.selectedBackgroundColor ??
                            (this.options.type === 'tab' ? SegmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR :
                            SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR));
                        Stack.position(ObservedObject.GetRawObject(this.selectedItemPosition));
                        Stack.scale({
                            x: this.zoomScaleArray[this.selectedIndexes[0]],
                            y: this.zoomScaleArray[this.selectedIndexes[0]]
                        });
                        Stack.shadow(ShadowStyle.OUTER_DEFAULT_XS);
                        Stack.pixelRound({
                            top: PixelRoundCalcPolicy.FORCE_FLOOR
                        });
                    }, Stack);
                    Stack.pop();
                });
            }
            else {
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

class MultiSelectItemArray extends ViewPU {
    constructor(p13, q13, r13, s13 = -1, t13 = undefined, u13) {
        super(p13, r13, s13, u13);
        if (typeof t13 === "function") {
            this.paramsGenerator_ = t13;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(q13.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(q13.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(q13.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__multiColor = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (w13, x13) => Color.Transparent), this, "multiColor");
        this.setInitiallyProvidedValue(q13);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(o13) {
        this.__optionsArray.set(o13.optionsArray);
        this.__options.set(o13.options);
        if (o13.multiColor !== undefined) {
            this.multiColor = o13.multiColor;
        }
    }

    updateStateVars(n13) {
        this.__optionsArray.set(n13.optionsArray);
        this.__options.set(n13.options);
    }

    purgeVariableDependenciesOnElmtId(m13) {
        this.__optionsArray.purgeDependencyOnElmtId(m13);
        this.__options.purgeDependencyOnElmtId(m13);
        this.__selectedIndexes.purgeDependencyOnElmtId(m13);
        this.__buttonItemsSize.purgeDependencyOnElmtId(m13);
        this.__zoomScaleArray.purgeDependencyOnElmtId(m13);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(m13);
        this.__multiColor.purgeDependencyOnElmtId(m13);
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

    set selectedIndexes(l13) {
        this.__selectedIndexes.set(l13);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(k13) {
        this.__buttonItemsSize.set(k13);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(j13) {
        this.__zoomScaleArray.set(j13);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(i13) {
        this.__buttonBorderRadius.set(i13);
    }

    get multiColor() {
        return this.__multiColor.get();
    }

    set multiColor(h13) {
        this.__multiColor.set(h13);
    }

    onOptionsChange() {
        for (let g13 = 0; g13 < this.selectedIndexes.length; g13++) {
            this.multiColor[this.selectedIndexes[g13]] = this.options.selectedBackgroundColor ?? SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    onSelectedChange() {
        for (let f13 = 0; f13 < MAX_ITEM_COUNT; f13++) {
            this.multiColor[f13] = Color.Transparent;
        }
        for (let e13 = 0; e13 < this.selectedIndexes.length; e13++) {
            this.multiColor[this.selectedIndexes[e13]] = this.options.selectedBackgroundColor ?? SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    aboutToAppear() {
        for (let d13 = 0; d13 < this.selectedIndexes.length; d13++) {
            this.multiColor[this.selectedIndexes[d13]] = this.options.selectedBackgroundColor ?? SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    initialRender() {
        this.observeComponentCreation2((b13, c13) => {
            Row.create({ space: 1 });
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((m12, n12) => {
            ForEach.create();
            const o12 = (q12, r12) => {
                const s12 = q12;
                this.observeComponentCreation2((u12, v12) => {
                    If.create();
                    if (r12 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((z12, a13) => {
                                Stack.create();
                                Stack.width(this.buttonItemsSize[r12].width);
                                Stack.height(this.buttonItemsSize[r12].height);
                                Stack.backgroundColor(this.multiColor[r12]);
                                Stack.borderRadius(this.buttonBorderRadius[r12]);
                            }, Stack);
                            Stack.pop();
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(m12, this.optionsArray, o12, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SegmentButtonItem extends ViewPU {
    constructor(e12, f12, g12, h12 = -1, i12 = undefined, j12) {
        super(e12, g12, h12, j12);
        if (typeof i12 === "function") {
            this.paramsGenerator_ = i12;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(f12.selectedIndexes, this, "selectedIndexes");
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(f12.focusIndex, this, "focusIndex");
        this.__itemOptions = new SynchedPropertyNesedObjectPU(f12.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(f12.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(f12.property, this, "property");
        this.__index = new SynchedPropertySimpleOneWayPU(f12.index, this, "index");
        this.groupId = "";
        this.setInitiallyProvidedValue(f12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(d12) {
        this.__itemOptions.set(d12.itemOptions);
        this.__options.set(d12.options);
        this.__property.set(d12.property);
        if (d12.groupId !== undefined) {
            this.groupId = d12.groupId;
        }
    }

    updateStateVars(c12) {
        this.__itemOptions.set(c12.itemOptions);
        this.__options.set(c12.options);
        this.__property.set(c12.property);
        this.__index.reset(c12.index);
    }

    purgeVariableDependenciesOnElmtId(b12) {
        this.__selectedIndexes.purgeDependencyOnElmtId(b12);
        this.__focusIndex.purgeDependencyOnElmtId(b12);
        this.__itemOptions.purgeDependencyOnElmtId(b12);
        this.__options.purgeDependencyOnElmtId(b12);
        this.__property.purgeDependencyOnElmtId(b12);
        this.__index.purgeDependencyOnElmtId(b12);
    }

    aboutToBeDeleted() {
        this.__selectedIndexes.aboutToBeDeleted();
        this.__focusIndex.aboutToBeDeleted();
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

    set selectedIndexes(a12) {
        this.__selectedIndexes.set(a12);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(z11) {
        this.__focusIndex.set(z11);
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

    set index(y11) {
        this.__index.set(y11);
    }

    initialRender() {
        this.observeComponentCreation2((w11, x11) => {
            Column.create({ space: 2 });
            Column.focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.options.buttonPadding ?? ((this.options.type === 'capsule' && this.options.showText && this.options.showIcon) ?
                { top: 6, right: 8, bottom: 6, left: 8 } : { top: 4, right: 8, bottom: 4, left: 8 }));
            Column.constraintSize({ minHeight: 28 });
        }, Column);
        this.observeComponentCreation2((p11, q11) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u11, v11) => {
                        Image.create(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon);
                        Image.size(this.options.imageSize ?? { width: 24, height: 24 });
                        Image.focusable(!this.options.showText);
                        Image.draggable(false);
                        Image.fillColor(this.property.isSelected ? (this.options.selectedFontColor ?? SegmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR) :
                            (this.options.fontColor ?? SegmentButtonTheme.FONT_COLOR));
                    }, Image);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((h11, i11) => {
            If.create();
            if (this.options.showText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m11, n11) => {
                        Text.create(this.itemOptions.text);
                        Text.fontColor(this.property.fontColor);
                        Text.fontWeight(this.property.fontWeight);
                        Text.fontSize(this.property.fontSize);
                        Text.minFontSize(9);
                        Text.maxFontSize(this.property.fontSize);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(1);
                        Text.textAlign(TextAlign.Center);
                        Text.focusable(true);
                        Text.padding(this.options.textPadding ?? 0);
                        Gesture.create(GesturePriority.Low);
                        TapGesture.create();
                        TapGesture.onAction(() => {
                            this.focusIndex = -1;
                            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                                if (this.selectedIndexes.indexOf(this.index) === -1) {
                                    this.selectedIndexes.push(this.index);
                                }
                                else {
                                    this.selectedIndexes.splice(this.selectedIndexes.indexOf(this.index), 1);
                                }
                            }
                            else {
                                this.selectedIndexes[0] = this.index;
                            }
                        });
                        TapGesture.pop();
                        Gesture.pop();
                    }, Text);
                    Text.pop();
                });
            }
            else {
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

let HoverColorProperty = class HoverColorProperty {
    constructor() {
        this.hoverColor = Color.Transparent;
    }
};
HoverColorProperty = __decorate([
    Observed
], HoverColorProperty);

class PressAndHoverEffect extends ViewPU {
    constructor(y10, z10, a11, b11 = -1, c11 = undefined, d11) {
        super(y10, a11, b11, d11);
        if (typeof c11 === "function") {
            this.paramsGenerator_ = c11;
        }
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(z10.press, this, "press");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(z10.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.pressIndex = 0;
        this.pressColor = SegmentButtonTheme.PRESS_COLOR;
        this.setInitiallyProvidedValue(z10);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(x10) {
        this.__colorProperty.set(x10.colorProperty);
        if (x10.pressIndex !== undefined) {
            this.pressIndex = x10.pressIndex;
        }
        if (x10.pressColor !== undefined) {
            this.pressColor = x10.pressColor;
        }
    }

    updateStateVars(w10) {
        this.__press.reset(w10.press);
        this.__colorProperty.set(w10.colorProperty);
    }

    purgeVariableDependenciesOnElmtId(v10) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(v10);
        this.__press.purgeDependencyOnElmtId(v10);
        this.__colorProperty.purgeDependencyOnElmtId(v10);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(v10);
    }

    aboutToBeDeleted() {
        this.__buttonItemsSize.aboutToBeDeleted();
        this.__press.aboutToBeDeleted();
        this.__colorProperty.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(u10) {
        this.__buttonItemsSize.set(u10);
    }

    get press() {
        return this.__press.get();
    }

    set press(t10) {
        this.__press.set(t10);
    }

    get colorProperty() {
        return this.__colorProperty.get();
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(s10) {
        this.__buttonBorderRadius.set(s10);
    }

    initialRender() {
        this.observeComponentCreation2((q10, r10) => {
            Stack.create();
            Stack.size(this.buttonItemsSize[this.pressIndex]);
            Stack.backgroundColor(this.press ? this.pressColor : this.colorProperty.hoverColor);
            Stack.borderRadius(this.buttonBorderRadius[this.pressIndex]);
        }, Stack);
        Stack.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SegmentButtonItemArrayComponent extends ViewPU {
    constructor(u9, v9, w9, x9 = -1, y9 = undefined, z9) {
        super(u9, w9, x9, z9);
        if (typeof y9 === "function") {
            this.paramsGenerator_ = y9;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(v9.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(v9.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(v9.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = this.initializeConsume("componentSize", "componentSize");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__buttonItemsPosition = this.initializeConsume("buttonItemsPosition", "buttonItemsPosition");
        this.__focusIndex = this.initializeConsume("focusIndex", "focusIndex");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonItemProperty = this.initializeConsume("buttonItemProperty", "buttonItemProperty");
        this.__buttonItemsSelected = this.initializeConsume("buttonItemsSelected", "buttonItemsSelected");
        this.__pressArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (n10, o10) => false), this, "pressArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (l10, m10) => new HoverColorProperty()), this, "hoverColorArray");
        this.__buttonWidth = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (j10, k10) => 0), this, "buttonWidth");
        this.__buttonHeight = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (h10, i10) => 0), this, "buttonHeight");
        this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (f10, g10) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.setInitiallyProvidedValue(v9);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(t9) {
        this.__optionsArray.set(t9.optionsArray);
        this.__options.set(t9.options);
        if (t9.pressArray !== undefined) {
            this.pressArray = t9.pressArray;
        }
        if (t9.hoverColorArray !== undefined) {
            this.hoverColorArray = t9.hoverColorArray;
        }
        if (t9.buttonWidth !== undefined) {
            this.buttonWidth = t9.buttonWidth;
        }
        if (t9.buttonHeight !== undefined) {
            this.buttonHeight = t9.buttonHeight;
        }
        if (t9.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = t9.buttonItemsRealHeight;
        }
        if (t9.groupId !== undefined) {
            this.groupId = t9.groupId;
        }
    }

    updateStateVars(s9) {
        this.__optionsArray.set(s9.optionsArray);
        this.__options.set(s9.options);
    }

    purgeVariableDependenciesOnElmtId(r9) {
        this.__optionsArray.purgeDependencyOnElmtId(r9);
        this.__options.purgeDependencyOnElmtId(r9);
        this.__selectedIndexes.purgeDependencyOnElmtId(r9);
        this.__componentSize.purgeDependencyOnElmtId(r9);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(r9);
        this.__buttonItemsSize.purgeDependencyOnElmtId(r9);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(r9);
        this.__focusIndex.purgeDependencyOnElmtId(r9);
        this.__zoomScaleArray.purgeDependencyOnElmtId(r9);
        this.__buttonItemProperty.purgeDependencyOnElmtId(r9);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(r9);
        this.__pressArray.purgeDependencyOnElmtId(r9);
        this.__hoverColorArray.purgeDependencyOnElmtId(r9);
        this.__buttonWidth.purgeDependencyOnElmtId(r9);
        this.__buttonHeight.purgeDependencyOnElmtId(r9);
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
        this.__hoverColorArray.aboutToBeDeleted();
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

    set selectedIndexes(q9) {
        this.__selectedIndexes.set(q9);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(p9) {
        this.__componentSize.set(p9);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(o9) {
        this.__buttonBorderRadius.set(o9);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(n9) {
        this.__buttonItemsSize.set(n9);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(m9) {
        this.__buttonItemsPosition.set(m9);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(l9) {
        this.__focusIndex.set(l9);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(k9) {
        this.__zoomScaleArray.set(k9);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(j9) {
        this.__buttonItemProperty.set(j9);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(i9) {
        this.__buttonItemsSelected.set(i9);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(h9) {
        this.__pressArray.set(h9);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(g9) {
        this.__hoverColorArray.set(g9);
    }

    get buttonWidth() {
        return this.__buttonWidth.get();
    }

    set buttonWidth(f9) {
        this.__buttonWidth.set(f9);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(e9) {
        this.__buttonHeight.set(e9);
    }

    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((c9, d9) => {
            this.buttonWidth[d9] = c9.width;
            this.buttonHeight[d9] = c9.height;
        });
    }

    changeSelectedIndexes(q8) {
        if (this.optionsArray.changeStartIndex === void 0 || this.optionsArray.deleteCount === void 0 || this.optionsArray.addLength === void 0) {
            return;
        }
        if (!(this.options.multiply ?? false)) {
            if (this.selectedIndexes[0] === void 0) {
                return;
            }
            if (this.selectedIndexes[0] < this.optionsArray.changeStartIndex) {
                return;
            }
            if (this.optionsArray.changeStartIndex + this.optionsArray.deleteCount > this.selectedIndexes[0]) {
                if (this.options.type === 'tab') {
                    this.selectedIndexes[0] = 0;
                }
                else if (this.options.type === 'capsule') {
                    this.selectedIndexes = [];
                }
            }
            else {
                this.selectedIndexes[0] = this.selectedIndexes[0] - this.optionsArray.deleteCount + this.optionsArray.addLength;
            }
        }
        else {
            let r8 = this.selectedIndexes;
            for (let w8 = 0; w8 < this.optionsArray.deleteCount; w8++) {
                let x8 = r8.indexOf(this.optionsArray.changeStartIndex);
                let y8 = r8.map(a9 => this.optionsArray.changeStartIndex && (a9 > this.optionsArray.changeStartIndex) ? a9 - 1 : a9);
                if (x8 !== -1) {
                    y8.splice(x8, 1);
                }
                r8 = y8;
            }
            for (let s8 = 0; s8 < this.optionsArray.addLength; s8++) {
                let t8 = r8.map(v8 => this.optionsArray.changeStartIndex && (v8 >= this.optionsArray.changeStartIndex) ? v8 + 1 : v8);
                r8 = t8;
            }
            this.selectedIndexes = r8;
        }
    }

    changeFocusIndex(p8) {
        if (this.optionsArray.changeStartIndex === void 0 || this.optionsArray.deleteCount === void 0 || this.optionsArray.addLength === void 0) {
            return;
        }
        if (this.focusIndex === -1) {
            return;
        }
        if (this.focusIndex < this.optionsArray.changeStartIndex) {
            return;
        }
        if (this.optionsArray.changeStartIndex + this.optionsArray.deleteCount > this.focusIndex) {
            this.focusIndex = 0;
        }
        else {
            this.focusIndex = this.focusIndex - this.optionsArray.deleteCount + this.optionsArray.addLength;
        }
    }

    onOptionsArrayChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        let o8 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 && this.optionsArray.addLength !== void 0) {
            this.changeSelectedIndexes(o8);
            this.changeFocusIndex(o8);
            this.optionsArray.changeStartIndex = void 0;
            this.optionsArray.deleteCount = void 0;
            this.optionsArray.addLength = void 0;
        }
    }

    onOptionsChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        this.calculateBorderRadius();
    }

    aboutToAppear() {
        for (let n8 = 0; n8 < this.buttonItemsRealHeight.length; n8++) {
            this.buttonItemsRealHeight[n8] = 0;
        }
    }

    focusStack(f8, g8 = null) {
        this.observeComponentCreation2((l8, m8) => {
            Stack.create();
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((j8, k8) => {
            Stack.create();
            Stack.borderRadius({
                topLeft: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonBorderRadius[f8].topLeft + 4 : this.buttonBorderRadius[f8].topLeft,
                topRight: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonBorderRadius[f8].topRight + 4 : this.buttonBorderRadius[f8].topRight,
                bottomLeft: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonBorderRadius[f8].bottomLeft + 4 : this.buttonBorderRadius[f8].bottomLeft,
                bottomRight: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonBorderRadius[f8].bottomRight + 4 : this.buttonBorderRadius[f8].bottomRight
            });
            Stack.size({
                width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonWidth[f8] + 8 : this.buttonWidth[f8],
                height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonHeight[f8] + 8 : this.buttonHeight[f8]
            });
            Stack.borderColor(SegmentButtonTheme.FOCUS_BORDER_COLOR);
            Stack.borderWidth(2);
        }, Stack);
        Stack.pop();
        Stack.pop();
    }

    calculateBorderRadius() {
        let z7 = Array.from({
            length: MAX_ITEM_COUNT
        }, (d8, e8) => {
            return { topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 };
        });
        for (let b8 = 0; b8 < this.buttonBorderRadius.length; b8++) {
            let c8 = this.buttonItemsSize[b8].height / 2;
            if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                z7[b8].topLeft = this.options.iconTextRadius ?? c8;
                z7[b8].topRight = this.options.iconTextRadius ?? c8;
                z7[b8].bottomLeft = this.options.iconTextRadius ?? c8;
                z7[b8].bottomRight = this.options.iconTextRadius ?? c8;
            }
            else {
                if (b8 === 0) {
                    z7[b8].topLeft = this.options.iconTextRadius ?? c8;
                    z7[b8].topRight = 0;
                    z7[b8].bottomLeft = this.options.iconTextRadius ?? c8;
                    z7[b8].bottomRight = 0;
                }
                else if (this.options.buttons && b8 === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    z7[b8].topLeft = 0;
                    z7[b8].topRight = this.options.iconTextRadius ?? c8;
                    z7[b8].bottomLeft = 0;
                    z7[b8].bottomRight = this.options.iconTextRadius ?? c8;
                }
                else {
                    z7[b8].topLeft = 0;
                    z7[b8].topRight = 0;
                    z7[b8].bottomLeft = 0;
                    z7[b8].bottomRight = 0;
                }
            }
        }
        this.buttonBorderRadius = z7;
    }

    initialRender() {
        this.observeComponentCreation2((l5, m5) => {
            If.create();
            if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u7, v7) => {
                        Row.create({ space: 1 });
                        Row.focusScopeId(this.groupId, true);
                        Row.padding(this.options.componentPadding);
                        Row.onSizeChange((x7, y7) => {
                            this.componentSize = { width: y7.width, height: y7.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((r5, s5) => {
                        ForEach.create();
                        const t5 = (v5, w5) => {
                            const x5 = v5;
                            this.observeComponentCreation2((z5, a6) => {
                                If.create();
                                if (w5 < MAX_ITEM_COUNT) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((a7, b7) => {
                                            Stack.create();
                                            Stack.borderRadius(this.buttonBorderRadius[w5]);
                                            Stack.scale({
                                                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[w5],
                                                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[w5]
                                            });
                                            Stack.layoutWeight(1);
                                            Stack.onSizeChange((s7, t7) => {
                                                this.buttonItemsSize[w5] = {
                                                    width: t7.width,
                                                    height: this.buttonItemsSize[w5].height
                                                };
                                                if (t7.width) {
                                                    this.buttonItemsPosition[w5] = {
                                                        x: Number.parseFloat(this.options.componentPadding.toString()) + (Number.parseFloat(t7.width.toString()) + 1) * w5,
                                                        y: Number.parseFloat(this.options.componentPadding.toString())
                                                    };
                                                }
                                            });
                                            ViewStackProcessor.visualState("normal");
                                            Stack.overlay(undefined);
                                            ViewStackProcessor.visualState("focused");
                                            Stack.overlay({ builder: () => {
                                                this.focusStack.call(this, w5);
                                            } }, {
                                                align: Alignment.Center
                                            });
                                            ViewStackProcessor.visualState();
                                            Stack.onFocus(() => {
                                                this.focusIndex = w5;
                                            });
                                            Stack.onTouch((p7) => {
                                                if (p7.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (p7.type === TouchType.Down) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[w5] = 0.95;
                                                    });
                                                }
                                                else if (p7.type === TouchType.Up) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[w5] = 1;
                                                    });
                                                }
                                            });
                                            Stack.onHover((m7) => {
                                                if (m7) {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[w5].hoverColor = (SegmentButtonTheme.HOVER_COlOR);
                                                    });
                                                }
                                                else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[w5].hoverColor = Color.Transparent;
                                                    });
                                                }
                                            });
                                            Stack.onMouse((h7) => {
                                                switch (h7.action) {
                                                    case MouseAction.Press:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[w5] = 0.95;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[w5] = true;
                                                        });
                                                        break;
                                                    case MouseAction.Release:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[w5] = 1;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[w5] = false;
                                                        });
                                                        break;
                                                }
                                            });
                                        }, Stack);
                                        {
                                            this.observeComponentCreation2((u6, v6) => {
                                                if (v6) {
                                                    let w6 = new PressAndHoverEffect(this, {
                                                        pressIndex: w5,
                                                        colorProperty: this.hoverColorArray[w5],
                                                        press: this.pressArray[w5]
                                                    }, undefined, u6, () => {
                                                    }, {
                                                        page: "segmentbutton/src/main/ets/components/mainpage/MainPage.ets",
                                                        line: 682,
                                                        col: 15
                                                    });
                                                    ViewPU.create(w6);
                                                    let x6 = () => {
                                                        return {
                                                            pressIndex: w5,
                                                            colorProperty: this.hoverColorArray[w5],
                                                            press: this.pressArray[w5]
                                                        };
                                                    };
                                                    w6.paramsGenerator_ = x6;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(u6, {
                                                        colorProperty: this.hoverColorArray[w5],
                                                        press: this.pressArray[w5]
                                                    });
                                                }
                                            }, { name: "PressAndHoverEffect" });
                                        }
                                        this.observeComponentCreation2((m6, n6) => {
                                            __Common__.create();
                                            __Common__.onSizeChange((p6, q6) => {
                                                this.buttonItemsRealHeight[w5] = q6.height;
                                                let r6 = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ? this.options.buttons.length : 0));
                                                for (let s6 = 0; s6 < this.buttonItemsSize.length; s6++) {
                                                    this.buttonItemsSize[s6] = {
                                                        width: this.buttonItemsSize[s6].width,
                                                        height: r6
                                                    };
                                                }
                                                this.calculateBorderRadius();
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((g6, h6) => {
                                                if (h6) {
                                                    let i6 = new SegmentButtonItem(this, {
                                                        selectedIndexes: this.__selectedIndexes,
                                                        focusIndex: this.__focusIndex,
                                                        index: w5,
                                                        itemOptions: x5,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[w5],
                                                        groupId: this.groupId
                                                    }, undefined, g6, () => {
                                                    }, {
                                                        page: "segmentbutton/src/main/ets/components/mainpage/MainPage.ets",
                                                        line: 687,
                                                        col: 15
                                                    });
                                                    ViewPU.create(i6);
                                                    let j6 = () => {
                                                        return {
                                                            selectedIndexes: this.selectedIndexes,
                                                            focusIndex: this.focusIndex,
                                                            index: w5,
                                                            itemOptions: x5,
                                                            options: this.options,
                                                            property: this.buttonItemProperty[w5],
                                                            groupId: this.groupId
                                                        };
                                                    };
                                                    i6.paramsGenerator_ = j6;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(g6, {
                                                        index: w5,
                                                        itemOptions: x5,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[w5]
                                                    });
                                                }
                                            }, { name: "SegmentButtonItem" });
                                        }
                                        __Common__.pop();
                                        Stack.pop();
                                    });
                                }
                                else {
                                    this.ifElseBranchUpdateFunction(1, () => {
                                    });
                                }
                            }, If);
                            If.pop();
                        };
                        this.forEachUpdateFunction(r5, this.optionsArray, t5, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                    Row.pop();
                });
            }
            else {
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

let ItemProperty = class ItemProperty {
    constructor() {
        this.fontColor = SegmentButtonTheme.FONT_COLOR;
        this.fontSize = SegmentButtonTheme.FONT_SIZE;
        this.fontWeight = FontWeight.Regular;
        this.isSelected = false;
    }
};
ItemProperty = __decorate([
    Observed
], ItemProperty);

export class SegmentButton extends ViewPU {
    constructor(m4, n4, o4, p4 = -1, q4 = undefined, r4) {
        super(m4, o4, p4, r4);
        if (typeof q4 === "function") {
            this.paramsGenerator_ = q4;
        }
        this.__options = new SynchedPropertyNesedObjectPU(n4.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(n4.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, "componentSize");
        this.addProvidedVar("componentSize", this.__componentSize, false);
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (i5, j5) => {
            return { topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 };
        }), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.__buttonBorderRadius, false);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (g5, h5) => {
            return {};
        }), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.__buttonItemsSize, false);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (e5, f5) => {
            return {};
        }), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.__buttonItemsPosition, false);
        this.__buttonItemsSelected = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (c5, d5) => false), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected, false);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (a5, b5) => new ItemProperty()), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty, false);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex, false);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition, false);
        this.__zoomScaleArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (y4, z4) => 1.0), this, "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.__zoomScaleArray, false);
        this.doSelectedChangeAnimate = false;
        this.isCurrentPositionSelected = false;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = false;
        this.setInitiallyProvidedValue(n4);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.declareWatch("buttonItemsPosition", this.onItemsPositionChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(l4) {
        this.__options.set(l4.options);
        if (l4.componentSize !== undefined) {
            this.componentSize = l4.componentSize;
        }
        if (l4.buttonBorderRadius !== undefined) {
            this.buttonBorderRadius = l4.buttonBorderRadius;
        }
        if (l4.buttonItemsSize !== undefined) {
            this.buttonItemsSize = l4.buttonItemsSize;
        }
        if (l4.buttonItemsPosition !== undefined) {
            this.buttonItemsPosition = l4.buttonItemsPosition;
        }
        if (l4.buttonItemsSelected !== undefined) {
            this.buttonItemsSelected = l4.buttonItemsSelected;
        }
        if (l4.buttonItemProperty !== undefined) {
            this.buttonItemProperty = l4.buttonItemProperty;
        }
        if (l4.focusIndex !== undefined) {
            this.focusIndex = l4.focusIndex;
        }
        if (l4.selectedItemPosition !== undefined) {
            this.selectedItemPosition = l4.selectedItemPosition;
        }
        if (l4.zoomScaleArray !== undefined) {
            this.zoomScaleArray = l4.zoomScaleArray;
        }
        if (l4.doSelectedChangeAnimate !== undefined) {
            this.doSelectedChangeAnimate = l4.doSelectedChangeAnimate;
        }
        if (l4.isCurrentPositionSelected !== undefined) {
            this.isCurrentPositionSelected = l4.isCurrentPositionSelected;
        }
        if (l4.panGestureStartPoint !== undefined) {
            this.panGestureStartPoint = l4.panGestureStartPoint;
        }
        if (l4.isPanGestureMoved !== undefined) {
            this.isPanGestureMoved = l4.isPanGestureMoved;
        }
    }

    updateStateVars(k4) {
        this.__options.set(k4.options);
    }

    purgeVariableDependenciesOnElmtId(j4) {
        this.__options.purgeDependencyOnElmtId(j4);
        this.__selectedIndexes.purgeDependencyOnElmtId(j4);
        this.__componentSize.purgeDependencyOnElmtId(j4);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(j4);
        this.__buttonItemsSize.purgeDependencyOnElmtId(j4);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(j4);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(j4);
        this.__buttonItemProperty.purgeDependencyOnElmtId(j4);
        this.__focusIndex.purgeDependencyOnElmtId(j4);
        this.__selectedItemPosition.purgeDependencyOnElmtId(j4);
        this.__zoomScaleArray.purgeDependencyOnElmtId(j4);
    }

    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__componentSize.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        this.__buttonItemsSize.aboutToBeDeleted();
        this.__buttonItemsPosition.aboutToBeDeleted();
        this.__buttonItemsSelected.aboutToBeDeleted();
        this.__buttonItemProperty.aboutToBeDeleted();
        this.__focusIndex.aboutToBeDeleted();
        this.__selectedItemPosition.aboutToBeDeleted();
        this.__zoomScaleArray.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get options() {
        return this.__options.get();
    }

    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }

    set selectedIndexes(i4) {
        this.__selectedIndexes.set(i4);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(h4) {
        this.__componentSize.set(h4);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(g4) {
        this.__buttonBorderRadius.set(g4);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(f4) {
        this.__buttonItemsSize.set(f4);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(e4) {
        this.__buttonItemsPosition.set(e4);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(d4) {
        this.__buttonItemsSelected.set(d4);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(c4) {
        this.__buttonItemProperty.set(c4);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(b4) {
        this.__focusIndex.set(b4);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(a4) {
        this.__selectedItemPosition.set(a4);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(z3) {
        this.__zoomScaleArray.set(z3);
    }

    onItemsPositionChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        if (this.doSelectedChangeAnimate) {
            this.updateAnimatedProperty(this.getSelectedChangeCurve());
        }
        else {
            this.updateAnimatedProperty(null);
        }
    }

    setItemsSelected() {
        this.buttonItemsSelected.forEach((x3, y3) => {
            this.buttonItemsSelected[y3] = false;
        });
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            this.selectedIndexes.forEach(w3 => this.buttonItemsSelected[w3] = true);
        }
        else {
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
        let r3 = this.selectedIndexes.some(t3 => {
            return (t3 === void 0 || t3 < 0 || (this.options.buttons && t3 >= this.options.buttons.length));
        });
        if (r3) {
            if (this.options.type === 'tab') {
                this.selectedIndexes = [0];
            }
            else {
                this.selectedIndexes = [];
            }
        }
    }

    onOptionsChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
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
        }
        else {
            this.updateAnimatedProperty(null);
        }
    }

    aboutToAppear() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        this.options.onButtonsChange = () => {
            if (this.options.type === 'tab') {
                this.selectedIndexes = [0];
            }
            else {
                this.selectedIndexes = [];
            }
        };
        this.updateSelectedIndexes();
        this.setItemsSelected();
        this.updateAnimatedProperty(null);
    }

    isMouseWheelScroll(p3) {
        return p3.source === SourceType.Mouse && !this.isPanGestureMoved;
    }

    isMovedFromPanGestureStartPoint(n3, o3) {
        return!nearEqual(n3, this.panGestureStartPoint.x) || !nearEqual(o3, this.panGestureStartPoint.y);
    }

    initialRender() {
        this.observeComponentCreation2((h2, i2) => {
            Stack.create();
            Stack.onBlur(() => {
                this.focusIndex = -1;
            });
            Stack.onKeyEvent((m3) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (m3.type === KeyType.Down) {
                    if (m3.keyCode === KeyCode.KEYCODE_SPACE || m3.keyCode === KeyCode.KEYCODE_ENTER || m3.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            if (this.selectedIndexes.indexOf(this.focusIndex) === -1) {
                                this.selectedIndexes.push(this.focusIndex);
                            }
                            else {
                                this.selectedIndexes.splice(this.selectedIndexes.indexOf(this.focusIndex), 1);
                            }
                        }
                        else {
                            this.selectedIndexes[0] = this.focusIndex;
                        }
                    }
                }
            });
            Gesture.create(GesturePriority.High);
            GestureGroup.create(GestureMode.Parallel);
            TapGesture.create();
            TapGesture.onAction((i3) => {
                this.focusIndex = -1;
                let j3 = i3.fingerList.find(Boolean);
                if (j3 === void 0) {
                    return;
                }
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                let k3 = j3.localX;
                for (let l3 = 0; l3 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); l3++) {
                    k3 = k3 - this.buttonItemsSize[l3].width;
                    if (k3 >= 0) {
                        continue;
                    }
                    this.doSelectedChangeAnimate =
                        this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ? false : true;
                    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                        if (this.selectedIndexes.indexOf(l3) === -1) {
                            this.selectedIndexes.push(l3);
                        }
                        else {
                            this.selectedIndexes.splice(this.selectedIndexes.indexOf(l3), 1);
                        }
                    }
                    else {
                        this.selectedIndexes[0] = l3;
                    }
                    this.doSelectedChangeAnimate = false;
                    break;
                }
            });
            TapGesture.pop();
            SwipeGesture.create();
            SwipeGesture.onAction((h3) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (this.isCurrentPositionSelected) {
                    return;
                }
                if (h3.angle > 0 && this.selectedIndexes[0] !== Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
                    this.doSelectedChangeAnimate = false;
                }
                else if (h3.angle < 0 && this.selectedIndexes[0] !== 0) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
                    this.doSelectedChangeAnimate = false;
                }
            });
            SwipeGesture.pop();
            PanGesture.create();
            PanGesture.onActionStart((d3) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let e3 = d3.fingerList.find(Boolean);
                if (e3 === void 0) {
                    return;
                }
                let f3 = e3.localX;
                this.panGestureStartPoint = { x: e3.globalX, y: e3.globalY };
                this.isPanGestureMoved = false;
                for (let g3 = 0; g3 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); g3++) {
                    f3 = f3 - this.buttonItemsSize[g3].width;
                    if (f3 < 0) {
                        this.isCurrentPositionSelected = g3 === this.selectedIndexes[0] ? true : false;
                        break;
                    }
                }
            });
            PanGesture.onActionUpdate((u2) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (!this.isCurrentPositionSelected) {
                    return;
                }
                let v2 = u2.fingerList.find(Boolean);
                if (v2 === void 0) {
                    return;
                }
                let w2 = v2.localX;
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(v2.globalX, v2.globalY)) {
                    this.isPanGestureMoved = true;
                }
                for (let c3 = 0; c3 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); c3++) {
                    w2 = w2 - this.buttonItemsSize[c3].width;
                    if (w2 < 0) {
                        this.doSelectedChangeAnimate = true;
                        this.selectedIndexes[0] = c3;
                        this.doSelectedChangeAnimate = false;
                        break;
                    }
                }
                this.zoomScaleArray.forEach((y2, z2) => {
                    if (z2 === this.selectedIndexes[0]) {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[z2] = 0.95;
                        });
                    }
                    else {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[z2] = 1;
                        });
                    }
                });
            });
            PanGesture.onActionEnd((q2) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let r2 = q2.fingerList.find(Boolean);
                if (r2 === void 0) {
                    return;
                }
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(r2.globalX, r2.globalY)) {
                    this.isPanGestureMoved = true;
                }
                if (this.isMouseWheelScroll(q2)) {
                    let t2 = q2.offsetX !== 0 ? q2.offsetX : q2.offsetY;
                    this.doSelectedChangeAnimate = true;
                    if (t2 > 0 && this.selectedIndexes[0] > 0) {
                        this.selectedIndexes[0] -= 1;
                    }
                    else if (t2 < 0 && this.selectedIndexes[0] < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
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
        this.observeComponentCreation2((l, m) => {
            If.create();
            if (this.options !== void 0 && this.options.buttons != void 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t1, u1) => {
                        If.create();
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                {
                                    this.observeComponentCreation2((b2, c2) => {
                                        if (c2) {
                                            let d2 = new MultiSelectBackground(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                            }, undefined, b2, () => {
                                            }, {
                                                page: "segmentbutton/src/main/ets/components/mainpage/MainPage.ets",
                                                line: 929,
                                                col: 11
                                            });
                                            ViewPU.create(d2);
                                            let e2 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options
                                                };
                                            };
                                            d2.paramsGenerator_ = e2;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(b2, {
                                                optionsArray: this.options.buttons,
                                                options: this.options
                                            });
                                        }
                                    }, { name: "MultiSelectBackground" });
                                }
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((x1, y1) => {
                                    Stack.create();
                                    Stack.size(ObservedObject.GetRawObject(this.componentSize));
                                    Stack.backgroundColor(this.options.backgroundColor ?? SegmentButtonTheme.BACKGROUND_COLOR);
                                    Stack.borderRadius(this.options.iconTextBackgroundRadius ?? this.componentSize.height / 2);
                                    Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
                                }, Stack);
                                Stack.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((r1, s1) => {
                        Stack.create();
                        Stack.size(ObservedObject.GetRawObject(this.componentSize));
                        Stack.borderRadius((this.options.type === 'capsule' && (this.options.multiply ?? false) ?
                        this.options.iconTextRadius : this.options.iconTextBackgroundRadius) ??
                            this.componentSize.height / 2);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((z, a1) => {
                        If.create();
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                {
                                    this.observeComponentCreation2((l1, m1) => {
                                        if (m1) {
                                            let n1 = new MultiSelectItemArray(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, l1, () => {
                                            }, {
                                                page: "segmentbutton/src/main/ets/components/mainpage/MainPage.ets",
                                                line: 942,
                                                col: 13
                                            });
                                            ViewPU.create(n1);
                                            let o1 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            n1.paramsGenerator_ = o1;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(l1, {
                                                optionsArray: this.options.buttons,
                                                options: this.options
                                            });
                                        }
                                    }, { name: "MultiSelectItemArray" });
                                }
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                {
                                    this.observeComponentCreation2((d1, e1) => {
                                        if (e1) {
                                            let f1 = new SelectItem(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, d1, () => {
                                            }, {
                                                page: "segmentbutton/src/main/ets/components/mainpage/MainPage.ets",
                                                line: 948,
                                                col: 13
                                            });
                                            ViewPU.create(f1);
                                            let g1 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            f1.paramsGenerator_ = g1;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(d1, {
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
                        this.observeComponentCreation2((t, u) => {
                            if (u) {
                                let v = new SegmentButtonItemArrayComponent(this, {
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    selectedIndexes: this.__selectedIndexes,
                                }, undefined, t, () => {
                                }, {
                                    page: "segmentbutton/src/main/ets/components/mainpage/MainPage.ets",
                                    line: 961,
                                    col: 9
                                });
                                ViewPU.create(v);
                                let w = () => {
                                    return {
                                        optionsArray: this.options.buttons,
                                        options: this.options,
                                        selectedIndexes: this.selectedIndexes
                                    };
                                };
                                v.paramsGenerator_ = w;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(t, {
                                    optionsArray: this.options.buttons,
                                    options: this.options
                                });
                            }
                        }, { name: "SegmentButtonItemArrayComponent" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Stack.pop();
    }

    getSelectedChangeCurve() {
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            return null;
        }
        return curves.springMotion(0.347, 0.99);
    }

    updateAnimatedProperty(a) {
        let b = () => {
            this.selectedItemPosition = this.selectedIndexes.length === 0 ? {
            } : this.buttonItemsPosition[this.selectedIndexes[0]];
            this.buttonItemsSelected.forEach((h, i) => {
                this.buttonItemProperty[i].fontColor = h ?
                    this.options.selectedFontColor ?? (this.options.type === 'tab' ?
                    SegmentButtonTheme.TAB_SELECTED_FONT_COLOR : SegmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR) :
                    this.options.fontColor ?? SegmentButtonTheme.FONT_COLOR;
            });
        };
        if (a) {
            Context.animateTo({ curve: a }, b);
        }
        else {
            b();
        }
        this.buttonItemsSelected.forEach((e, f) => {
            this.buttonItemProperty[f].fontSize = e ? this.options.selectedFontSize ?? SegmentButtonTheme.SELECTED_FONT_SIZE
                : this.options.fontSize ?? SegmentButtonTheme.FONT_SIZE;
            this.buttonItemProperty[f].fontWeight = e ? this.options.selectedFontWeight ?? FontWeight.Medium :
                this.options.fontWeight ?? FontWeight.Regular;
            this.buttonItemProperty[f].isSelected = e;
        });
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default { SegmentButton, SegmentButtonOptions, SegmentButtonItemOptionsArray, SegmentButtonItemOptions };