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

var __decorate = (this && this.__decorate) || function (b17, c17, d17, e17) {
    var f17 = arguments.length,
        g17 = f17 < 3 ? c17 : e17 === null ? e17 = Object.getOwnPropertyDescriptor(c17, d17) : e17, h17;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        g17 = Reflect.decorate(b17, c17, d17, e17);
    else
        for (var i17 = b17.length - 1; i17 >= 0; i17--)
            if (h17 = b17[i17])
                g17 = (f17 < 3 ? h17(g17) : f17 > 3 ? h17(c17, d17, g17) : h17(c17, d17)) || g17;
    return f17 > 3 && g17 && Object.defineProperty(c17, d17, g17), g17;
};
var SegmentButtonItemOptionsArray_1, SegmentButtonOptions_1;
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}
const curves = globalThis.requireNativeModule("ohos.curves");
const KeyCode = globalThis.requireNapi("multimodalInput.keyCode").KeyCode;

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

function nearEqual(y16, z16) {
    return Math.abs(y16 - z16) < 0.001;
}

let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(x16) {
        this.icon = x16.icon;
        this.selectedIcon = x16.selectedIcon;
        this.text = x16.text;
    }
};
SegmentButtonItemOptions = __decorate([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends Array {
    constructor(u16) {
        super(typeof u16 === "number" ? u16 : 0);
        this.changeStartIndex = void 0;
        this.deleteCount = void 0;
        this.addLength = void 0;
        if (typeof u16 !== "number" && u16 !== void 0) {
            super.push(...u16.map((w16) => new SegmentButtonItemOptions(w16)));
        }
    }

    push(...r16) {
        if (this.length + r16.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        this.changeStartIndex = this.length;
        this.deleteCount = 0;
        this.addLength = r16.length;
        return super.push(...r16.map((t16) => new SegmentButtonItemOptions(t16)));
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

    unshift(...o16) {
        if (this.length + o16.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        if (o16.length > 0) {
            this.changeStartIndex = 0;
            this.deleteCount = 0;
            this.addLength = o16.length;
        }
        return super.unshift(...o16.map((q16) => new SegmentButtonItemOptions(q16)));
    }

    splice(k16, l16, ...m16) {
        let n16 = (this.length - l16) < 0 ? 0 : (this.length - l16);
        n16 += m16.length;
        if (n16 < MIN_ITEM_COUNT) {
            console.warn("Below the minimum number of elements (2).");
            return [];
        }
        if (n16 > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return [];
        }
        this.changeStartIndex = k16;
        this.deleteCount = l16;
        this.addLength = m16.length;
        return super.splice(k16, l16, ...m16);
    }

    static create(j16) {
        return new SegmentButtonItemOptionsArray_1(j16);
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

    set buttons(i16) {
        if (this._buttons !== void 0 && this._buttons !== i16) {
            this.onButtonsChange?.();
        }
        this._buttons = i16;
    }

    constructor(f16) {
        this.multiply = false;
        this.showText = false;
        this.showIcon = false;
        this._buttons = void 0;
        this.fontColor = f16.fontColor ?? SegmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = f16.selectedFontColor ?? SegmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = f16.fontSize ?? SegmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = f16.selectedFontSize ?? SegmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = f16.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = f16.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = f16.backgroundColor ?? SegmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = f16.selectedBackgroundColor ?? SegmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = f16.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = f16.buttonPadding ?? { top: 4, right: 8, bottom: 4, left: 8 };
        this.textPadding = f16.textPadding ?? 0;
        this.type = f16.type;
        this.backgroundBlurStyle = f16.backgroundBlurStyle ?? SegmentButtonTheme.BACKGROUND_BLUR_STYLE;
        this.buttons = new SegmentButtonItemOptionsArray(f16.buttons);
        if (this.type === "capsule") {
            this.multiply = f16.multiply ?? false;
            this.buttons.forEach(h16 => {
                this.showText ||= h16.text !== void 0;
                this.showIcon ||= h16.icon !== void 0 || h16.selectedIcon !== void 0;
            });
            if (this.showText && this.showIcon) {
                this.iconTextRadius = 12;
                this.buttonPadding = f16.buttonPadding ?? { top: 6, right: 8, bottom: 6, left: 8 };
                this.iconTextBackgroundRadius = 14;
            }
            this.selectedFontColor = f16.selectedFontColor ?? SegmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = f16.selectedBackgroundColor ?? SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
        else {
            this.showText = true;
        }
        this.componentPadding = this.multiply ? 0 : 2;
    }

    static tab(e16) {
        return new SegmentButtonOptions_1({
            type: "tab",
            buttons: e16.buttons,
            fontColor: e16.fontColor,
            selectedFontColor: e16.selectedFontColor,
            fontSize: e16.fontSize,
            selectedFontSize: e16.selectedFontSize,
            fontWeight: e16.fontWeight,
            selectedFontWeight: e16.selectedFontWeight,
            backgroundColor: e16.backgroundColor,
            selectedBackgroundColor: e16.selectedBackgroundColor,
            imageSize: e16.imageSize,
            buttonPadding: e16.buttonPadding,
            textPadding: e16.textPadding,
            backgroundBlurStyle: e16.backgroundBlurStyle
        });
    }

    static capsule(d16) {
        return new SegmentButtonOptions_1({
            type: "capsule",
            buttons: d16.buttons,
            multiply: d16.multiply,
            fontColor: d16.fontColor,
            selectedFontColor: d16.selectedFontColor,
            fontSize: d16.fontSize,
            selectedFontSize: d16.selectedFontSize,
            fontWeight: d16.fontWeight,
            selectedFontWeight: d16.selectedFontWeight,
            backgroundColor: d16.backgroundColor,
            selectedBackgroundColor: d16.selectedBackgroundColor,
            imageSize: d16.imageSize,
            buttonPadding: d16.buttonPadding,
            textPadding: d16.textPadding,
            backgroundBlurStyle: d16.backgroundBlurStyle
        });
    }
};
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([
    Observed
], SegmentButtonOptions);

export { SegmentButtonOptions };

class MultiSelectBackground extends ViewPU {
    constructor(x15, y15, z15, a16 = -1, b16 = undefined, c16) {
        super(x15, z15, a16, c16);
        if (typeof b16 === "function") {
            this.paramsGenerator_ = b16;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(y15.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(y15.options, this, "options");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(y15);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(w15) {
        this.__optionsArray.set(w15.optionsArray);
        this.__options.set(w15.options);
    }

    updateStateVars(v15) {
        this.__optionsArray.set(v15.optionsArray);
        this.__options.set(v15.options);
    }

    purgeVariableDependenciesOnElmtId(u15) {
        this.__optionsArray.purgeDependencyOnElmtId(u15);
        this.__options.purgeDependencyOnElmtId(u15);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(u15);
        this.__buttonItemsSize.purgeDependencyOnElmtId(u15);
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

    set buttonBorderRadius(t15) {
        this.__buttonBorderRadius.set(t15);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(s15) {
        this.__buttonItemsSize.set(s15);
    }

    initialRender() {
        this.observeComponentCreation2((q15, r15) => {
            Row.create({ space: 1 });
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((b15, c15) => {
            ForEach.create();
            const d15 = (f15, g15) => {
                const h15 = f15;
                this.observeComponentCreation2((j15, k15) => {
                    If.create();
                    if (g15 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((o15, p15) => {
                                Stack.create();
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[g15].height);
                                Stack.backgroundColor(this.options.backgroundColor ?? SegmentButtonTheme.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[g15]);
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
            this.forEachUpdateFunction(b15, this.optionsArray, d15, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SelectItem extends ViewPU {
    constructor(t14, u14, v14, w14 = -1, x14 = undefined, y14) {
        super(t14, v14, w14, y14);
        if (typeof x14 === "function") {
            this.paramsGenerator_ = x14;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(u14.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(u14.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(u14.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__selectedItemPosition = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(u14);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(s14) {
        this.__optionsArray.set(s14.optionsArray);
        this.__options.set(s14.options);
    }

    updateStateVars(r14) {
        this.__optionsArray.set(r14.optionsArray);
        this.__options.set(r14.options);
    }

    purgeVariableDependenciesOnElmtId(q14) {
        this.__optionsArray.purgeDependencyOnElmtId(q14);
        this.__options.purgeDependencyOnElmtId(q14);
        this.__selectedIndexes.purgeDependencyOnElmtId(q14);
        this.__buttonItemsSize.purgeDependencyOnElmtId(q14);
        this.__selectedItemPosition.purgeDependencyOnElmtId(q14);
        this.__zoomScaleArray.purgeDependencyOnElmtId(q14);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(q14);
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

    set selectedIndexes(p14) {
        this.__selectedIndexes.set(p14);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(o14) {
        this.__buttonItemsSize.set(o14);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(n14) {
        this.__selectedItemPosition.set(n14);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(m14) {
        this.__zoomScaleArray.set(m14);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(l14) {
        this.__buttonBorderRadius.set(l14);
    }

    initialRender() {
        this.observeComponentCreation2((e14, f14) => {
            If.create();
            if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j14, k14) => {
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
    constructor(u13, v13, w13, x13 = -1, y13 = undefined, z13) {
        super(u13, w13, x13, z13);
        if (typeof y13 === "function") {
            this.paramsGenerator_ = y13;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(v13.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(v13.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(v13.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__multiColor = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (b14, c14) => Color.Transparent), this, "multiColor");
        this.setInitiallyProvidedValue(v13);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(t13) {
        this.__optionsArray.set(t13.optionsArray);
        this.__options.set(t13.options);
        if (t13.multiColor !== undefined) {
            this.multiColor = t13.multiColor;
        }
    }

    updateStateVars(s13) {
        this.__optionsArray.set(s13.optionsArray);
        this.__options.set(s13.options);
    }

    purgeVariableDependenciesOnElmtId(r13) {
        this.__optionsArray.purgeDependencyOnElmtId(r13);
        this.__options.purgeDependencyOnElmtId(r13);
        this.__selectedIndexes.purgeDependencyOnElmtId(r13);
        this.__buttonItemsSize.purgeDependencyOnElmtId(r13);
        this.__zoomScaleArray.purgeDependencyOnElmtId(r13);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(r13);
        this.__multiColor.purgeDependencyOnElmtId(r13);
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

    set selectedIndexes(q13) {
        this.__selectedIndexes.set(q13);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(p13) {
        this.__buttonItemsSize.set(p13);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(o13) {
        this.__zoomScaleArray.set(o13);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(n13) {
        this.__buttonBorderRadius.set(n13);
    }

    get multiColor() {
        return this.__multiColor.get();
    }

    set multiColor(m13) {
        this.__multiColor.set(m13);
    }

    onOptionsChange() {
        for (let l13 = 0; l13 < this.selectedIndexes.length; l13++) {
            this.multiColor[this.selectedIndexes[l13]] = this.options.selectedBackgroundColor ?? SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    onSelectedChange() {
        for (let k13 = 0; k13 < MAX_ITEM_COUNT; k13++) {
            this.multiColor[k13] = Color.Transparent;
        }
        for (let j13 = 0; j13 < this.selectedIndexes.length; j13++) {
            this.multiColor[this.selectedIndexes[j13]] = this.options.selectedBackgroundColor ?? SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    aboutToAppear() {
        for (let i13 = 0; i13 < this.selectedIndexes.length; i13++) {
            this.multiColor[this.selectedIndexes[i13]] = this.options.selectedBackgroundColor ?? SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    initialRender() {
        this.observeComponentCreation2((g13, h13) => {
            Row.create({ space: 1 });
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((r12, s12) => {
            ForEach.create();
            const t12 = (v12, w12) => {
                const x12 = v12;
                this.observeComponentCreation2((z12, a13) => {
                    If.create();
                    if (w12 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((e13, f13) => {
                                Stack.create();
                                Stack.width(this.buttonItemsSize[w12].width);
                                Stack.height(this.buttonItemsSize[w12].height);
                                Stack.backgroundColor(this.multiColor[w12]);
                                Stack.borderRadius(this.buttonBorderRadius[w12]);
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
            this.forEachUpdateFunction(r12, this.optionsArray, t12, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SegmentButtonItem extends ViewPU {
    constructor(j12, k12, l12, m12 = -1, n12 = undefined, o12) {
        super(j12, l12, m12, o12);
        if (typeof n12 === "function") {
            this.paramsGenerator_ = n12;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(k12.selectedIndexes, this, "selectedIndexes");
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(k12.focusIndex, this, "focusIndex");
        this.__itemOptions = new SynchedPropertyNesedObjectPU(k12.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(k12.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(k12.property, this, "property");
        this.__index = new SynchedPropertySimpleOneWayPU(k12.index, this, "index");
        this.setInitiallyProvidedValue(k12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(i12) {
        this.__itemOptions.set(i12.itemOptions);
        this.__options.set(i12.options);
        this.__property.set(i12.property);
    }

    updateStateVars(h12) {
        this.__itemOptions.set(h12.itemOptions);
        this.__options.set(h12.options);
        this.__property.set(h12.property);
        this.__index.reset(h12.index);
    }

    purgeVariableDependenciesOnElmtId(g12) {
        this.__selectedIndexes.purgeDependencyOnElmtId(g12);
        this.__focusIndex.purgeDependencyOnElmtId(g12);
        this.__itemOptions.purgeDependencyOnElmtId(g12);
        this.__options.purgeDependencyOnElmtId(g12);
        this.__property.purgeDependencyOnElmtId(g12);
        this.__index.purgeDependencyOnElmtId(g12);
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

    set selectedIndexes(f12) {
        this.__selectedIndexes.set(f12);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(e12) {
        this.__focusIndex.set(e12);
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

    set index(d12) {
        this.__index.set(d12);
    }

    initialRender() {
        this.observeComponentCreation2((b12, c12) => {
            Column.create({ space: 2 });
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.options.buttonPadding ?? ((this.options.type === 'capsule' && this.options.showText && this.options.showIcon) ?
                { top: 6, right: 8, bottom: 6, left: 8 } : { top: 4, right: 8, bottom: 4, left: 8 }));
            Column.constraintSize({ minHeight: 28 });
        }, Column);
        this.observeComponentCreation2((u11, v11) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z11, a12) => {
                        Image.create(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon);
                        Image.size(this.options.imageSize ?? { width: 24, height: 24 });
                        Image.focusable(this.index == 0);
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
        this.observeComponentCreation2((m11, n11) => {
            If.create();
            if (this.options.showText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r11, s11) => {
                        Text.create(this.itemOptions.text);
                        Text.fontColor(this.property.fontColor);
                        Text.fontWeight(this.property.fontWeight);
                        Text.fontSize(this.property.fontSize);
                        Text.minFontSize(9);
                        Text.maxFontSize(this.property.fontSize);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(1);
                        Text.textAlign(TextAlign.Center);
                        Text.focusable(this.index == 0 && !this.options.showIcon);
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
    constructor(d11, e11, f11, g11 = -1, h11 = undefined, i11) {
        super(d11, f11, g11, i11);
        if (typeof h11 === "function") {
            this.paramsGenerator_ = h11;
        }
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(e11.press, this, "press");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(e11.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.pressIndex = 0;
        this.pressColor = SegmentButtonTheme.PRESS_COLOR;
        this.setInitiallyProvidedValue(e11);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(c11) {
        this.__colorProperty.set(c11.colorProperty);
        if (c11.pressIndex !== undefined) {
            this.pressIndex = c11.pressIndex;
        }
        if (c11.pressColor !== undefined) {
            this.pressColor = c11.pressColor;
        }
    }

    updateStateVars(b11) {
        this.__press.reset(b11.press);
        this.__colorProperty.set(b11.colorProperty);
    }

    purgeVariableDependenciesOnElmtId(a11) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(a11);
        this.__press.purgeDependencyOnElmtId(a11);
        this.__colorProperty.purgeDependencyOnElmtId(a11);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(a11);
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

    set buttonItemsSize(z10) {
        this.__buttonItemsSize.set(z10);
    }

    get press() {
        return this.__press.get();
    }

    set press(y10) {
        this.__press.set(y10);
    }

    get colorProperty() {
        return this.__colorProperty.get();
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(x10) {
        this.__buttonBorderRadius.set(x10);
    }

    initialRender() {
        this.observeComponentCreation2((v10, w10) => {
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
    constructor(z9, a10, b10, c10 = -1, d10 = undefined, e10) {
        super(z9, b10, c10, e10);
        if (typeof d10 === "function") {
            this.paramsGenerator_ = d10;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(a10.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(a10.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(a10.selectedIndexes, this, "selectedIndexes");
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
        }, (s10, t10) => false), this, "pressArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (q10, r10) => new HoverColorProperty()), this, "hoverColorArray");
        this.__buttonWidth = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (o10, p10) => 0), this, "buttonWidth");
        this.__buttonHeight = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (m10, n10) => 0), this, "buttonHeight");
        this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (k10, l10) => 0);
        this.setInitiallyProvidedValue(a10);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(y9) {
        this.__optionsArray.set(y9.optionsArray);
        this.__options.set(y9.options);
        if (y9.pressArray !== undefined) {
            this.pressArray = y9.pressArray;
        }
        if (y9.hoverColorArray !== undefined) {
            this.hoverColorArray = y9.hoverColorArray;
        }
        if (y9.buttonWidth !== undefined) {
            this.buttonWidth = y9.buttonWidth;
        }
        if (y9.buttonHeight !== undefined) {
            this.buttonHeight = y9.buttonHeight;
        }
        if (y9.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = y9.buttonItemsRealHeight;
        }
    }

    updateStateVars(x9) {
        this.__optionsArray.set(x9.optionsArray);
        this.__options.set(x9.options);
    }

    purgeVariableDependenciesOnElmtId(w9) {
        this.__optionsArray.purgeDependencyOnElmtId(w9);
        this.__options.purgeDependencyOnElmtId(w9);
        this.__selectedIndexes.purgeDependencyOnElmtId(w9);
        this.__componentSize.purgeDependencyOnElmtId(w9);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(w9);
        this.__buttonItemsSize.purgeDependencyOnElmtId(w9);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(w9);
        this.__focusIndex.purgeDependencyOnElmtId(w9);
        this.__zoomScaleArray.purgeDependencyOnElmtId(w9);
        this.__buttonItemProperty.purgeDependencyOnElmtId(w9);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(w9);
        this.__pressArray.purgeDependencyOnElmtId(w9);
        this.__hoverColorArray.purgeDependencyOnElmtId(w9);
        this.__buttonWidth.purgeDependencyOnElmtId(w9);
        this.__buttonHeight.purgeDependencyOnElmtId(w9);
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

    set selectedIndexes(v9) {
        this.__selectedIndexes.set(v9);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(u9) {
        this.__componentSize.set(u9);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(t9) {
        this.__buttonBorderRadius.set(t9);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(s9) {
        this.__buttonItemsSize.set(s9);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(r9) {
        this.__buttonItemsPosition.set(r9);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(q9) {
        this.__focusIndex.set(q9);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(p9) {
        this.__zoomScaleArray.set(p9);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(o9) {
        this.__buttonItemProperty.set(o9);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(n9) {
        this.__buttonItemsSelected.set(n9);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(m9) {
        this.__pressArray.set(m9);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(l9) {
        this.__hoverColorArray.set(l9);
    }

    get buttonWidth() {
        return this.__buttonWidth.get();
    }

    set buttonWidth(k9) {
        this.__buttonWidth.set(k9);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(j9) {
        this.__buttonHeight.set(j9);
    }

    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((h9, i9) => {
            this.buttonWidth[i9] = h9.width;
            this.buttonHeight[i9] = h9.height;
        });
    }

    changeSelectedIndexes(v8) {
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
            let w8 = this.selectedIndexes;
            for (let b9 = 0; b9 < this.optionsArray.deleteCount; b9++) {
                let c9 = w8.indexOf(this.optionsArray.changeStartIndex);
                let d9 = w8.map(f9 => this.optionsArray.changeStartIndex && (f9 > this.optionsArray.changeStartIndex) ? f9 - 1 : f9);
                if (c9 !== -1) {
                    d9.splice(c9, 1);
                }
                w8 = d9;
            }
            for (let x8 = 0; x8 < this.optionsArray.addLength; x8++) {
                let y8 = w8.map(a9 => this.optionsArray.changeStartIndex && (a9 >= this.optionsArray.changeStartIndex) ? a9 + 1 : a9);
                w8 = y8;
            }
            this.selectedIndexes = w8;
        }
    }

    changeFocusIndex(u8) {
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
        let t8 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 && this.optionsArray.addLength !== void 0) {
            this.changeSelectedIndexes(t8);
            this.changeFocusIndex(t8);
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
        for (let s8 = 0; s8 < this.buttonItemsRealHeight.length; s8++) {
            this.buttonItemsRealHeight[s8] = 0;
        }
    }

    focusStack(f8, g8 = null) {
        this.observeComponentCreation2((q8, r8) => {
            Stack.create();
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((j8, k8) => {
            If.create();
            if (f8 === this.focusIndex) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o8, p8) => {
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
        this.observeComponentCreation2((m5, n5) => {
            If.create();
            if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u7, v7) => {
                        Row.create({ space: 1 });
                        Row.padding(this.options.componentPadding);
                        Row.onSizeChange((x7, y7) => {
                            this.componentSize = { width: y7.width, height: y7.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((s5, t5) => {
                        ForEach.create();
                        const u5 = (w5, x5) => {
                            const y5 = w5;
                            this.observeComponentCreation2((a6, b6) => {
                                If.create();
                                if (x5 < MAX_ITEM_COUNT) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((b7, c7) => {
                                            Stack.create();
                                            Stack.borderRadius(this.buttonBorderRadius[x5]);
                                            Stack.scale({
                                                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[x5],
                                                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[x5]
                                            });
                                            Stack.layoutWeight(1);
                                            Stack.onSizeChange((s7, t7) => {
                                                this.buttonItemsSize[x5] = {
                                                    width: t7.width,
                                                    height: this.buttonItemsSize[x5].height
                                                };
                                                if (t7.width) {
                                                    this.buttonItemsPosition[x5] = {
                                                        x: Number.parseInt(this.options.componentPadding.toString()) + (Number.parseInt(t7.width.toString()) + 1) * x5,
                                                        y: Number.parseInt(this.options.componentPadding.toString())
                                                    };
                                                }
                                            });
                                            Stack.overlay({ builder: () => {
                                                this.focusStack.call(this, x5);
                                            } }, {
                                                align: Alignment.Center
                                            });
                                            Stack.onTouch((p7) => {
                                                if (p7.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (p7.type === TouchType.Down) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[x5] = 0.95;
                                                    });
                                                }
                                                else if (p7.type === TouchType.Up) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[x5] = 1;
                                                    });
                                                }
                                            });
                                            Stack.onHover((m7) => {
                                                if (m7) {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[x5].hoverColor = (SegmentButtonTheme.HOVER_COlOR);
                                                    });
                                                }
                                                else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[x5].hoverColor = Color.Transparent;
                                                    });
                                                }
                                            });
                                            Stack.onMouse((h7) => {
                                                switch (h7.action) {
                                                    case MouseAction.Press:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[x5] = 0.95;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[x5] = true;
                                                        });
                                                        break;
                                                    case MouseAction.Release:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[x5] = 1;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[x5] = false;
                                                        });
                                                        break;
                                                }
                                            });
                                        }, Stack);
                                        {
                                            this.observeComponentCreation2((v6, w6) => {
                                                if (w6) {
                                                    let x6 = new PressAndHoverEffect(this, {
                                                        pressIndex: x5,
                                                        colorProperty: this.hoverColorArray[x5],
                                                        press: this.pressArray[x5]
                                                    }, undefined, v6, () => {
                                                    }, {
                                                        page: "segmentbutton/src/main/ets/components/mainpage/MainPage.ets",
                                                        line: 680,
                                                        col: 15
                                                    });
                                                    ViewPU.create(x6);
                                                    let y6 = () => {
                                                        return {
                                                            pressIndex: x5,
                                                            colorProperty: this.hoverColorArray[x5],
                                                            press: this.pressArray[x5]
                                                        };
                                                    };
                                                    x6.paramsGenerator_ = y6;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(v6, {
                                                        colorProperty: this.hoverColorArray[x5],
                                                        press: this.pressArray[x5]
                                                    });
                                                }
                                            }, { name: "PressAndHoverEffect" });
                                        }
                                        this.observeComponentCreation2((n6, o6) => {
                                            __Common__.create();
                                            __Common__.onSizeChange((q6, r6) => {
                                                this.buttonItemsRealHeight[x5] = r6.height;
                                                let s6 = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ? this.options.buttons.length : 0));
                                                for (let t6 = 0; t6 < this.buttonItemsSize.length; t6++) {
                                                    this.buttonItemsSize[t6] = {
                                                        width: this.buttonItemsSize[t6].width,
                                                        height: s6
                                                    };
                                                }
                                                this.calculateBorderRadius();
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((h6, i6) => {
                                                if (i6) {
                                                    let j6 = new SegmentButtonItem(this, {
                                                        selectedIndexes: this.__selectedIndexes,
                                                        focusIndex: this.__focusIndex,
                                                        index: x5,
                                                        itemOptions: y5,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[x5]
                                                    }, undefined, h6, () => {
                                                    }, {
                                                        page: "segmentbutton/src/main/ets/components/mainpage/MainPage.ets",
                                                        line: 685,
                                                        col: 15
                                                    });
                                                    ViewPU.create(j6);
                                                    let k6 = () => {
                                                        return {
                                                            selectedIndexes: this.selectedIndexes,
                                                            focusIndex: this.focusIndex,
                                                            index: x5,
                                                            itemOptions: y5,
                                                            options: this.options,
                                                            property: this.buttonItemProperty[x5]
                                                        };
                                                    };
                                                    j6.paramsGenerator_ = k6;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(h6, {
                                                        index: x5,
                                                        itemOptions: y5,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[x5]
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
                        this.forEachUpdateFunction(s5, this.optionsArray, u5, undefined, true, false);
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
    constructor(n4, o4, p4, q4 = -1, r4 = undefined, s4) {
        super(n4, p4, q4, s4);
        if (typeof r4 === "function") {
            this.paramsGenerator_ = r4;
        }
        this.__options = new SynchedPropertyNesedObjectPU(o4.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(o4.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, "componentSize");
        this.addProvidedVar("componentSize", this.__componentSize, false);
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (j5, k5) => {
            return { topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 };
        }), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.__buttonBorderRadius, false);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (h5, i5) => {
            return {};
        }), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.__buttonItemsSize, false);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (f5, g5) => {
            return {};
        }), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.__buttonItemsPosition, false);
        this.__buttonItemsSelected = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (d5, e5) => false), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected, false);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (b5, c5) => new ItemProperty()), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty, false);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex, false);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition, false);
        this.__zoomScaleArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (z4, a5) => 1.0), this, "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.__zoomScaleArray, false);
        this.doSelectedChangeAnimate = false;
        this.isCurrentPositionSelected = false;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = false;
        this.setInitiallyProvidedValue(o4);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.declareWatch("buttonItemsPosition", this.onItemsPositionChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(m4) {
        this.__options.set(m4.options);
        if (m4.componentSize !== undefined) {
            this.componentSize = m4.componentSize;
        }
        if (m4.buttonBorderRadius !== undefined) {
            this.buttonBorderRadius = m4.buttonBorderRadius;
        }
        if (m4.buttonItemsSize !== undefined) {
            this.buttonItemsSize = m4.buttonItemsSize;
        }
        if (m4.buttonItemsPosition !== undefined) {
            this.buttonItemsPosition = m4.buttonItemsPosition;
        }
        if (m4.buttonItemsSelected !== undefined) {
            this.buttonItemsSelected = m4.buttonItemsSelected;
        }
        if (m4.buttonItemProperty !== undefined) {
            this.buttonItemProperty = m4.buttonItemProperty;
        }
        if (m4.focusIndex !== undefined) {
            this.focusIndex = m4.focusIndex;
        }
        if (m4.selectedItemPosition !== undefined) {
            this.selectedItemPosition = m4.selectedItemPosition;
        }
        if (m4.zoomScaleArray !== undefined) {
            this.zoomScaleArray = m4.zoomScaleArray;
        }
        if (m4.doSelectedChangeAnimate !== undefined) {
            this.doSelectedChangeAnimate = m4.doSelectedChangeAnimate;
        }
        if (m4.isCurrentPositionSelected !== undefined) {
            this.isCurrentPositionSelected = m4.isCurrentPositionSelected;
        }
        if (m4.panGestureStartPoint !== undefined) {
            this.panGestureStartPoint = m4.panGestureStartPoint;
        }
        if (m4.isPanGestureMoved !== undefined) {
            this.isPanGestureMoved = m4.isPanGestureMoved;
        }
    }

    updateStateVars(l4) {
        this.__options.set(l4.options);
    }

    purgeVariableDependenciesOnElmtId(k4) {
        this.__options.purgeDependencyOnElmtId(k4);
        this.__selectedIndexes.purgeDependencyOnElmtId(k4);
        this.__componentSize.purgeDependencyOnElmtId(k4);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(k4);
        this.__buttonItemsSize.purgeDependencyOnElmtId(k4);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(k4);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(k4);
        this.__buttonItemProperty.purgeDependencyOnElmtId(k4);
        this.__focusIndex.purgeDependencyOnElmtId(k4);
        this.__selectedItemPosition.purgeDependencyOnElmtId(k4);
        this.__zoomScaleArray.purgeDependencyOnElmtId(k4);
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

    set selectedIndexes(j4) {
        this.__selectedIndexes.set(j4);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(i4) {
        this.__componentSize.set(i4);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(h4) {
        this.__buttonBorderRadius.set(h4);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(g4) {
        this.__buttonItemsSize.set(g4);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(f4) {
        this.__buttonItemsPosition.set(f4);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(e4) {
        this.__buttonItemsSelected.set(e4);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(d4) {
        this.__buttonItemProperty.set(d4);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(c4) {
        this.__focusIndex.set(c4);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(b4) {
        this.__selectedItemPosition.set(b4);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(a4) {
        this.__zoomScaleArray.set(a4);
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
        this.buttonItemsSelected.forEach((y3, z3) => {
            this.buttonItemsSelected[z3] = false;
        });
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            this.selectedIndexes.forEach(x3 => this.buttonItemsSelected[x3] = true);
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
        let s3 = this.selectedIndexes.some(u3 => {
            return (u3 === void 0 || u3 < 0 || (this.options.buttons && u3 >= this.options.buttons.length));
        });
        if (s3) {
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

    isMouseWheelScroll(q3) {
        return q3.source === SourceType.Mouse && !this.isPanGestureMoved;
    }

    isMovedFromPanGestureStartPoint(o3, p3) {
        return!nearEqual(o3, this.panGestureStartPoint.x) || !nearEqual(p3, this.panGestureStartPoint.y);
    }

    initialRender() {
        this.observeComponentCreation2((h2, i2) => {
            Stack.create();
            Stack.onFocus(() => {
                if (this.options === void 0) {
                    return;
                }
                if (this.selectedIndexes === void 0 || this.selectedIndexes.length === 0) {
                    this.focusIndex = 0;
                    return;
                }
                if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                    this.focusIndex = this.selectedIndexes[0];
                }
                else {
                    this.focusIndex = Math.min(...this.selectedIndexes);
                }
            });
            Stack.onBlur(() => {
                this.focusIndex = -1;
            });
            Stack.onKeyEvent((n3) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (n3.type === KeyType.Down) {
                    if ((n3.keyCode === KeyCode.KEYCODE_DPAD_DOWN || n3.keyCode === KeyCode.KEYCODE_DPAD_RIGHT) && this.focusIndex < (Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1)) {
                        this.focusIndex = this.focusIndex + 1;
                    }
                    if ((n3.keyCode === KeyCode.KEYCODE_DPAD_UP || n3.keyCode === KeyCode.KEYCODE_DPAD_LEFT) && this.focusIndex > 0) {
                        this.focusIndex = this.focusIndex - 1;
                    }
                    if (n3.keyCode === KeyCode.KEYCODE_SPACE || n3.keyCode === KeyCode.KEYCODE_ENTER || n3.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
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
            TapGesture.onAction((j3) => {
                this.focusIndex = -1;
                let k3 = j3.fingerList.find(Boolean);
                if (k3 === void 0) {
                    return;
                }
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                let l3 = k3.localX;
                for (let m3 = 0; m3 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); m3++) {
                    l3 = l3 - this.buttonItemsSize[m3].width;
                    if (l3 >= 0) {
                        continue;
                    }
                    this.doSelectedChangeAnimate =
                        this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ? false : true;
                    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                        if (this.selectedIndexes.indexOf(m3) === -1) {
                            this.selectedIndexes.push(m3);
                        }
                        else {
                            this.selectedIndexes.splice(this.selectedIndexes.indexOf(m3), 1);
                        }
                    }
                    else {
                        this.selectedIndexes[0] = m3;
                    }
                    this.doSelectedChangeAnimate = false;
                    break;
                }
            });
            TapGesture.pop();
            SwipeGesture.create();
            SwipeGesture.onAction((i3) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (this.isCurrentPositionSelected) {
                    return;
                }
                if (i3.angle > 0 && this.selectedIndexes[0] !== Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
                    this.doSelectedChangeAnimate = false;
                }
                else if (i3.angle < 0 && this.selectedIndexes[0] !== 0) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
                    this.doSelectedChangeAnimate = false;
                }
            });
            SwipeGesture.pop();
            PanGesture.create();
            PanGesture.onActionStart((e3) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let f3 = e3.fingerList.find(Boolean);
                if (f3 === void 0) {
                    return;
                }
                let g3 = f3.localX;
                this.panGestureStartPoint = { x: f3.globalX, y: f3.globalY };
                this.isPanGestureMoved = false;
                for (let h3 = 0; h3 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); h3++) {
                    g3 = g3 - this.buttonItemsSize[h3].width;
                    if (g3 < 0) {
                        this.isCurrentPositionSelected = h3 === this.selectedIndexes[0] ? true : false;
                        break;
                    }
                }
            });
            PanGesture.onActionUpdate((v2) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (!this.isCurrentPositionSelected) {
                    return;
                }
                let w2 = v2.fingerList.find(Boolean);
                if (w2 === void 0) {
                    return;
                }
                let x2 = w2.localX;
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(w2.globalX, w2.globalY)) {
                    this.isPanGestureMoved = true;
                }
                for (let d3 = 0; d3 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); d3++) {
                    x2 = x2 - this.buttonItemsSize[d3].width;
                    if (x2 < 0) {
                        this.doSelectedChangeAnimate = true;
                        this.selectedIndexes[0] = d3;
                        this.doSelectedChangeAnimate = false;
                        break;
                    }
                }
                this.zoomScaleArray.forEach((z2, a3) => {
                    if (a3 === this.selectedIndexes[0]) {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[a3] = 0.95;
                        });
                    }
                    else {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[a3] = 1;
                        });
                    }
                });
            });
            PanGesture.onActionEnd((r2) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let s2 = r2.fingerList.find(Boolean);
                if (s2 === void 0) {
                    return;
                }
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(s2.globalX, s2.globalY)) {
                    this.isPanGestureMoved = true;
                }
                if (this.isMouseWheelScroll(r2)) {
                    let u2 = r2.offsetX !== 0 ? r2.offsetX : r2.offsetY;
                    this.doSelectedChangeAnimate = true;
                    if (u2 > 0 && this.selectedIndexes[0] > 0) {
                        this.selectedIndexes[0] -= 1;
                    }
                    else if (u2 < 0 && this.selectedIndexes[0] < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
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
                                                line: 915,
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
                                                line: 928,
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
                                                line: 934,
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
                                    line: 947,
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