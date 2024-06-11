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

var __decorate = (this && this.__decorate) || function (e18, f18, g18, h18) {
    var i18 = arguments.length,
        j18 = i18 < 3 ? f18 : h18 === null ? h18 = Object.getOwnPropertyDescriptor(f18, g18) : h18, k18;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        j18 = Reflect.decorate(e18, f18, g18, h18);
    else
        for (var l18 = e18.length - 1; l18 >= 0; l18--)
            if (k18 = e18[l18])
                j18 = (i18 < 3 ? k18(j18) : i18 > 3 ? k18(f18, g18, j18) : k18(f18, g18)) || j18;
    return i18 > 3 && j18 && Object.defineProperty(f18, g18, j18), j18;
};
var SegmentButtonItemOptionsArray_1, SegmentButtonOptions_1;
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}
const curves = globalThis.requireNativeModule("ohos.curves");
const KeyCode = globalThis.requireNapi("multimodalInput.keyCode").KeyCode;
const util = globalThis.requireNapi("util");
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const I18n = requireNapi('i18n');

const MIN_ITEM_COUNT = 2;
const MAX_ITEM_COUNT = 5;
const segmentButtonTheme = {
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
    HOVER_COLOR: {
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

function nearEqual(b18, c18) {
    return Math.abs(b18 - c18) < 0.001;
}

let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(a18) {
        this.icon = a18.icon;
        this.selectedIcon = a18.selectedIcon;
        this.text = a18.text;
    }
};
SegmentButtonItemOptions = __decorate([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends Array {
    constructor(x17) {
        super(typeof x17 === "number" ? x17 : 0);
        this.changeStartIndex = void 0;
        this.deleteCount = void 0;
        this.addLength = void 0;
        if (typeof x17 !== "number" && x17 !== void 0) {
            super.push(...x17.map((z17) => new SegmentButtonItemOptions(z17)));
        }
    }

    push(...u17) {
        if (this.length + u17.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        this.changeStartIndex = this.length;
        this.deleteCount = 0;
        this.addLength = u17.length;
        return super.push(...u17.map((w17) => new SegmentButtonItemOptions(w17)));
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

    unshift(...r17) {
        if (this.length + r17.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        if (r17.length > 0) {
            this.changeStartIndex = 0;
            this.deleteCount = 0;
            this.addLength = r17.length;
        }
        return super.unshift(...r17.map((t17) => new SegmentButtonItemOptions(t17)));
    }

    splice(n17, o17, ...p17) {
        let q17 = (this.length - o17) < 0 ? 0 : (this.length - o17);
        q17 += p17.length;
        if (q17 < MIN_ITEM_COUNT) {
            console.warn("Below the minimum number of elements (2).");
            return [];
        }
        if (q17 > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return [];
        }
        this.changeStartIndex = n17;
        this.deleteCount = o17;
        this.addLength = p17.length;
        return super.splice(n17, o17, ...p17);
    }

    static create(m17) {
        return new SegmentButtonItemOptionsArray_1(m17);
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

    set buttons(l17) {
        if (this._buttons !== void 0 && this._buttons !== l17) {
            this.onButtonsChange?.();
        }
        this._buttons = l17;
    }

    constructor(i17) {
        this.multiply = false;
        this.showText = false;
        this.showIcon = false;
        this._buttons = void 0;
        this.fontColor = i17.fontColor ?? segmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = i17.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = i17.fontSize ?? segmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = i17.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = i17.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = i17.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = i17.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = i17.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = i17.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = i17.buttonPadding;
        this.textPadding = i17.textPadding;
        this.type = i17.type;
        this.backgroundBlurStyle = i17.backgroundBlurStyle ?? segmentButtonTheme.BACKGROUND_BLUR_STYLE;
        this.localizedTextPadding = i17.localizedTextPadding;
        this.localizedButtonPadding = i17.localizedButtonPadding;
        this.direction = i17.direction ?? Direction.Auto;
        this.buttons = new SegmentButtonItemOptionsArray(i17.buttons);
        if (this.type === "capsule") {
            this.multiply = i17.multiply ?? false;
            this.buttons.forEach(k17 => {
                this.showText ||= k17.text !== void 0;
                this.showIcon ||= k17.icon !== void 0 || k17.selectedIcon !== void 0;
            });
            if (this.showText && this.showIcon) {
                this.iconTextRadius = 12;
                this.iconTextBackgroundRadius = 14;
            }
            this.selectedFontColor = i17.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = i17.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
        else {
            this.showText = true;
        }
        this.componentPadding = this.multiply ? 0 : 2;
    }

    static tab(h17) {
        return new SegmentButtonOptions_1({
            type: "tab",
            buttons: h17.buttons,
            fontColor: h17.fontColor,
            selectedFontColor: h17.selectedFontColor,
            fontSize: h17.fontSize,
            selectedFontSize: h17.selectedFontSize,
            fontWeight: h17.fontWeight,
            selectedFontWeight: h17.selectedFontWeight,
            backgroundColor: h17.backgroundColor,
            selectedBackgroundColor: h17.selectedBackgroundColor,
            imageSize: h17.imageSize,
            buttonPadding: h17.buttonPadding,
            textPadding: h17.textPadding,
            localizedTextPadding: h17.localizedTextPadding,
            localizedButtonPadding: h17.localizedButtonPadding,
            backgroundBlurStyle: h17.backgroundBlurStyle,
            direction: h17.direction
        });
    }

    static capsule(g17) {
        return new SegmentButtonOptions_1({
            type: "capsule",
            buttons: g17.buttons,
            multiply: g17.multiply,
            fontColor: g17.fontColor,
            selectedFontColor: g17.selectedFontColor,
            fontSize: g17.fontSize,
            selectedFontSize: g17.selectedFontSize,
            fontWeight: g17.fontWeight,
            selectedFontWeight: g17.selectedFontWeight,
            backgroundColor: g17.backgroundColor,
            selectedBackgroundColor: g17.selectedBackgroundColor,
            imageSize: g17.imageSize,
            buttonPadding: g17.buttonPadding,
            textPadding: g17.textPadding,
            localizedTextPadding: g17.localizedTextPadding,
            localizedButtonPadding: g17.localizedButtonPadding,
            backgroundBlurStyle: g17.backgroundBlurStyle,
            direction: g17.direction
        });
    }
};
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([
    Observed
], SegmentButtonOptions);

export { SegmentButtonOptions };

class MultiSelectBackground extends ViewPU {
    constructor(a17, b17, c17, d17 = -1, e17 = undefined, f17) {
        super(a17, c17, d17, f17);
        if (typeof e17 === "function") {
            this.paramsGenerator_ = e17;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(b17.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(b17.options, this, "options");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(b17);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(z16) {
        this.__optionsArray.set(z16.optionsArray);
        this.__options.set(z16.options);
    }

    updateStateVars(y16) {
        this.__optionsArray.set(y16.optionsArray);
        this.__options.set(y16.options);
    }

    purgeVariableDependenciesOnElmtId(x16) {
        this.__optionsArray.purgeDependencyOnElmtId(x16);
        this.__options.purgeDependencyOnElmtId(x16);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(x16);
        this.__buttonItemsSize.purgeDependencyOnElmtId(x16);
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

    set buttonBorderRadius(w16) {
        this.__buttonBorderRadius.set(w16);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(v16) {
        this.__buttonItemsSize.set(v16);
    }

    initialRender() {
        this.observeComponentCreation2((t16, u16) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((e16, f16) => {
            ForEach.create();
            const g16 = (i16, j16) => {
                const k16 = i16;
                this.observeComponentCreation2((m16, n16) => {
                    If.create();
                    if (j16 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((r16, s16) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[j16].height);
                                Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[j16]);
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
            this.forEachUpdateFunction(e16, this.optionsArray, g16, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SelectItem extends ViewPU {
    constructor(w15, x15, y15, z15 = -1, a16 = undefined, b16) {
        super(w15, y15, z15, b16);
        if (typeof a16 === "function") {
            this.paramsGenerator_ = a16;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(x15.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(x15.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(x15.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__selectedItemPosition = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(x15);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(v15) {
        this.__optionsArray.set(v15.optionsArray);
        this.__options.set(v15.options);
    }

    updateStateVars(u15) {
        this.__optionsArray.set(u15.optionsArray);
        this.__options.set(u15.options);
    }

    purgeVariableDependenciesOnElmtId(t15) {
        this.__optionsArray.purgeDependencyOnElmtId(t15);
        this.__options.purgeDependencyOnElmtId(t15);
        this.__selectedIndexes.purgeDependencyOnElmtId(t15);
        this.__buttonItemsSize.purgeDependencyOnElmtId(t15);
        this.__selectedItemPosition.purgeDependencyOnElmtId(t15);
        this.__zoomScaleArray.purgeDependencyOnElmtId(t15);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(t15);
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

    set selectedIndexes(s15) {
        this.__selectedIndexes.set(s15);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(r15) {
        this.__buttonItemsSize.set(r15);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(q15) {
        this.__selectedItemPosition.set(q15);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(p15) {
        this.__zoomScaleArray.set(p15);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(o15) {
        this.__buttonBorderRadius.set(o15);
    }

    initialRender() {
        this.observeComponentCreation2((h15, i15) => {
            If.create();
            if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m15, n15) => {
                        Stack.create();
                        Stack.direction(this.options.direction);
                        Stack.borderRadius(this.buttonBorderRadius[this.selectedIndexes[0]]);
                        Stack.size(this.buttonItemsSize[this.selectedIndexes[0]]);
                        Stack.backgroundColor(this.options.selectedBackgroundColor ??
                            (this.options.type === 'tab' ? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR :
                            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR));
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
    constructor(x14, y14, z14, a15 = -1, b15 = undefined, c15) {
        super(x14, z14, a15, c15);
        if (typeof b15 === "function") {
            this.paramsGenerator_ = b15;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(y14.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(y14.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(y14.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__multiColor = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (e15, f15) => Color.Transparent), this, "multiColor");
        this.setInitiallyProvidedValue(y14);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(w14) {
        this.__optionsArray.set(w14.optionsArray);
        this.__options.set(w14.options);
        if (w14.multiColor !== undefined) {
            this.multiColor = w14.multiColor;
        }
    }

    updateStateVars(v14) {
        this.__optionsArray.set(v14.optionsArray);
        this.__options.set(v14.options);
    }

    purgeVariableDependenciesOnElmtId(u14) {
        this.__optionsArray.purgeDependencyOnElmtId(u14);
        this.__options.purgeDependencyOnElmtId(u14);
        this.__selectedIndexes.purgeDependencyOnElmtId(u14);
        this.__buttonItemsSize.purgeDependencyOnElmtId(u14);
        this.__zoomScaleArray.purgeDependencyOnElmtId(u14);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(u14);
        this.__multiColor.purgeDependencyOnElmtId(u14);
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

    set selectedIndexes(t14) {
        this.__selectedIndexes.set(t14);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(s14) {
        this.__buttonItemsSize.set(s14);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(r14) {
        this.__zoomScaleArray.set(r14);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(q14) {
        this.__buttonBorderRadius.set(q14);
    }

    get multiColor() {
        return this.__multiColor.get();
    }

    set multiColor(p14) {
        this.__multiColor.set(p14);
    }

    onOptionsChange() {
        for (let o14 = 0; o14 < this.selectedIndexes.length; o14++) {
            this.multiColor[this.selectedIndexes[o14]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    onSelectedChange() {
        for (let n14 = 0; n14 < MAX_ITEM_COUNT; n14++) {
            this.multiColor[n14] = Color.Transparent;
        }
        for (let m14 = 0; m14 < this.selectedIndexes.length; m14++) {
            this.multiColor[this.selectedIndexes[m14]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    aboutToAppear() {
        for (let l14 = 0; l14 < this.selectedIndexes.length; l14++) {
            this.multiColor[this.selectedIndexes[l14]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    initialRender() {
        this.observeComponentCreation2((j14, k14) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((u13, v13) => {
            ForEach.create();
            const w13 = (y13, z13) => {
                const a14 = y13;
                this.observeComponentCreation2((c14, d14) => {
                    If.create();
                    if (z13 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((h14, i14) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.width(this.buttonItemsSize[z13].width);
                                Stack.height(this.buttonItemsSize[z13].height);
                                Stack.backgroundColor(this.multiColor[z13]);
                                Stack.borderRadius(this.buttonBorderRadius[z13]);
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
            this.forEachUpdateFunction(u13, this.optionsArray, w13, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SegmentButtonItem extends ViewPU {
    constructor(m13, n13, o13, p13 = -1, q13 = undefined, r13) {
        super(m13, o13, p13, r13);
        if (typeof q13 === "function") {
            this.paramsGenerator_ = q13;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(n13.selectedIndexes, this, "selectedIndexes");
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(n13.focusIndex, this, "focusIndex");
        this.__itemOptions = new SynchedPropertyNesedObjectPU(n13.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(n13.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(n13.property, this, "property");
        this.__index = new SynchedPropertySimpleOneWayPU(n13.index, this, "index");
        this.groupId = "";
        this.setInitiallyProvidedValue(n13);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(l13) {
        this.__itemOptions.set(l13.itemOptions);
        this.__options.set(l13.options);
        this.__property.set(l13.property);
        if (l13.groupId !== undefined) {
            this.groupId = l13.groupId;
        }
    }

    updateStateVars(k13) {
        this.__itemOptions.set(k13.itemOptions);
        this.__options.set(k13.options);
        this.__property.set(k13.property);
        this.__index.reset(k13.index);
    }

    purgeVariableDependenciesOnElmtId(j13) {
        this.__selectedIndexes.purgeDependencyOnElmtId(j13);
        this.__focusIndex.purgeDependencyOnElmtId(j13);
        this.__itemOptions.purgeDependencyOnElmtId(j13);
        this.__options.purgeDependencyOnElmtId(j13);
        this.__property.purgeDependencyOnElmtId(j13);
        this.__index.purgeDependencyOnElmtId(j13);
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

    set selectedIndexes(i13) {
        this.__selectedIndexes.set(i13);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(h13) {
        this.__focusIndex.set(h13);
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

    set index(g13) {
        this.__index.set(g13);
    }

    getTextPadding() {
        if (this.options.localizedTextPadding) {
            return this.options.localizedTextPadding;
        }
        if (this.options.textPadding) {
            return this.options.textPadding;
        }
        return 0;
    }

    getButtonPadding() {
        if (this.options.localizedButtonPadding) {
            return this.options.localizedButtonPadding;
        }
        if (this.options.buttonPadding) {
            return this.options.buttonPadding;
        }
        if (this.options.type === 'capsule' && this.options.showText && this.options.showIcon) {
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

    initialRender() {
        this.observeComponentCreation2((e13, f13) => {
            Column.create({ space: 2 });
            Column.direction(this.options.direction);
            Column.focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.getButtonPadding());
            Column.constraintSize({ minHeight: 28 });
        }, Column);
        this.observeComponentCreation2((x12, y12) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c13, d13) => {
                        Image.create(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon);
                        Image.direction(this.options.direction);
                        Image.matchTextDirection(this.options.direction == Direction.Ltr ? false : true);
                        Image.size(this.options.imageSize ?? { width: 24, height: 24 });
                        Image.focusable(!this.options.showText);
                        Image.draggable(false);
                        Image.fillColor(this.property.isSelected ? (this.options.selectedFontColor ??
                        segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR) : (this.options.fontColor ??
                        segmentButtonTheme.FONT_COLOR));
                    }, Image);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((p12, q12) => {
            If.create();
            if (this.options.showText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u12, v12) => {
                        Text.create(this.itemOptions.text);
                        Text.direction(this.options.direction);
                        Text.fontColor(this.property.fontColor);
                        Text.fontWeight(this.property.fontWeight);
                        Text.fontSize(this.property.fontSize);
                        Text.minFontSize(9);
                        Text.maxFontSize(this.property.fontSize);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(1);
                        Text.textAlign(TextAlign.Center);
                        Text.focusable(true);
                        Text.padding(this.getTextPadding());
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
    constructor(g12, h12, i12, j12 = -1, k12 = undefined, l12) {
        super(g12, i12, j12, l12);
        if (typeof k12 === "function") {
            this.paramsGenerator_ = k12;
        }
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(h12.press, this, "press");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(h12.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__options = new SynchedPropertyNesedObjectPU(h12.options, this, "options");
        this.pressIndex = 0;
        this.pressColor = segmentButtonTheme.PRESS_COLOR;
        this.setInitiallyProvidedValue(h12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(f12) {
        this.__colorProperty.set(f12.colorProperty);
        this.__options.set(f12.options);
        if (f12.pressIndex !== undefined) {
            this.pressIndex = f12.pressIndex;
        }
        if (f12.pressColor !== undefined) {
            this.pressColor = f12.pressColor;
        }
    }

    updateStateVars(e12) {
        this.__press.reset(e12.press);
        this.__colorProperty.set(e12.colorProperty);
        this.__options.set(e12.options);
    }

    purgeVariableDependenciesOnElmtId(d12) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(d12);
        this.__press.purgeDependencyOnElmtId(d12);
        this.__colorProperty.purgeDependencyOnElmtId(d12);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(d12);
        this.__options.purgeDependencyOnElmtId(d12);
    }

    aboutToBeDeleted() {
        this.__buttonItemsSize.aboutToBeDeleted();
        this.__press.aboutToBeDeleted();
        this.__colorProperty.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(c12) {
        this.__buttonItemsSize.set(c12);
    }

    get press() {
        return this.__press.get();
    }

    set press(b12) {
        this.__press.set(b12);
    }

    get colorProperty() {
        return this.__colorProperty.get();
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(a12) {
        this.__buttonBorderRadius.set(a12);
    }

    get options() {
        return this.__options.get();
    }

    initialRender() {
        this.observeComponentCreation2((y11, z11) => {
            Stack.create();
            Stack.direction(this.options.direction);
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
    constructor(i11, j11, k11, l11 = -1, m11 = undefined, n11) {
        super(i11, k11, l11, n11);
        if (typeof m11 === "function") {
            this.paramsGenerator_ = m11;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(j11.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(j11.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(j11.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = this.initializeConsume("componentSize", "componentSize");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__buttonItemsPosition = this.initializeConsume("buttonItemsPosition", "buttonItemsPosition");
        this.__focusIndex = this.initializeConsume("focusIndex", "focusIndex");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonItemProperty = this.initializeConsume("buttonItemProperty", "buttonItemProperty");
        this.__buttonItemsSelected = this.initializeConsume("buttonItemsSelected", "buttonItemsSelected");
        this.__pressArray = new SynchedPropertyObjectTwoWayPU(j11.pressArray, this, "pressArray");
        this.__hoverColorArray = new SynchedPropertyObjectTwoWayPU(j11.hoverColorArray, this, "hoverColorArray");
        this.__buttonWidth = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (v11, w11) => 0), this, "buttonWidth");
        this.__buttonHeight = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (t11, u11) => 0), this, "buttonHeight");
        this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (r11, s11) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.setInitiallyProvidedValue(j11);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(h11) {
        this.__optionsArray.set(h11.optionsArray);
        this.__options.set(h11.options);
        if (h11.buttonWidth !== undefined) {
            this.buttonWidth = h11.buttonWidth;
        }
        if (h11.buttonHeight !== undefined) {
            this.buttonHeight = h11.buttonHeight;
        }
        if (h11.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = h11.buttonItemsRealHeight;
        }
        if (h11.groupId !== undefined) {
            this.groupId = h11.groupId;
        }
    }

    updateStateVars(g11) {
        this.__optionsArray.set(g11.optionsArray);
        this.__options.set(g11.options);
    }

    purgeVariableDependenciesOnElmtId(f11) {
        this.__optionsArray.purgeDependencyOnElmtId(f11);
        this.__options.purgeDependencyOnElmtId(f11);
        this.__selectedIndexes.purgeDependencyOnElmtId(f11);
        this.__componentSize.purgeDependencyOnElmtId(f11);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(f11);
        this.__buttonItemsSize.purgeDependencyOnElmtId(f11);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(f11);
        this.__focusIndex.purgeDependencyOnElmtId(f11);
        this.__zoomScaleArray.purgeDependencyOnElmtId(f11);
        this.__buttonItemProperty.purgeDependencyOnElmtId(f11);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(f11);
        this.__pressArray.purgeDependencyOnElmtId(f11);
        this.__hoverColorArray.purgeDependencyOnElmtId(f11);
        this.__buttonWidth.purgeDependencyOnElmtId(f11);
        this.__buttonHeight.purgeDependencyOnElmtId(f11);
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

    set selectedIndexes(e11) {
        this.__selectedIndexes.set(e11);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(d11) {
        this.__componentSize.set(d11);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(c11) {
        this.__buttonBorderRadius.set(c11);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(b11) {
        this.__buttonItemsSize.set(b11);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(a11) {
        this.__buttonItemsPosition.set(a11);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(z10) {
        this.__focusIndex.set(z10);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(y10) {
        this.__zoomScaleArray.set(y10);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(x10) {
        this.__buttonItemProperty.set(x10);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(w10) {
        this.__buttonItemsSelected.set(w10);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(v10) {
        this.__pressArray.set(v10);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(u10) {
        this.__hoverColorArray.set(u10);
    }

    get buttonWidth() {
        return this.__buttonWidth.get();
    }

    set buttonWidth(t10) {
        this.__buttonWidth.set(t10);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(s10) {
        this.__buttonHeight.set(s10);
    }

    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((q10, r10) => {
            this.buttonWidth[r10] = q10.width;
            this.buttonHeight[r10] = q10.height;
        });
    }

    changeSelectedIndexes(e10) {
        if (this.optionsArray.changeStartIndex === void 0 || this.optionsArray.deleteCount === void 0 ||
            this.optionsArray.addLength === void 0) {
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
            let f10 = this.selectedIndexes;
            for (let k10 = 0; k10 < this.optionsArray.deleteCount; k10++) {
                let l10 = f10.indexOf(this.optionsArray.changeStartIndex);
                let m10 = f10.map(o10 => this.optionsArray.changeStartIndex &&
                    (o10 > this.optionsArray.changeStartIndex) ? o10 - 1 : o10);
                if (l10 !== -1) {
                    m10.splice(l10, 1);
                }
                f10 = m10;
            }
            for (let g10 = 0; g10 < this.optionsArray.addLength; g10++) {
                let h10 = f10.map(j10 => this.optionsArray.changeStartIndex &&
                    (j10 >= this.optionsArray.changeStartIndex) ? j10 + 1 : j10);
                f10 = h10;
            }
            this.selectedIndexes = f10;
        }
    }

    changeFocusIndex(d10) {
        if (this.optionsArray.changeStartIndex === void 0 || this.optionsArray.deleteCount === void 0 ||
            this.optionsArray.addLength === void 0) {
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
        let c10 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 &&
            this.optionsArray.addLength !== void 0) {
            this.changeSelectedIndexes(c10);
            this.changeFocusIndex(c10);
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
        for (let b10 = 0; b10 < this.buttonItemsRealHeight.length; b10++) {
            this.buttonItemsRealHeight[b10] = 0;
        }
    }

    getBorderRadius(z9) {
        let a10 = this.buttonBorderRadius[z9];
        if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex]) {
            a10.topStart = LengthMetrics.vp(a10.topStart.value + 4);
            a10.topEnd = LengthMetrics.vp(a10.topEnd.value + 4);
            a10.bottomStart = LengthMetrics.vp(a10.bottomStart.value + 4);
            a10.bottomEnd = LengthMetrics.vp(a10.bottomEnd.value + 4);
        }
        return a10;
    }

    focusStack(r9, s9 = null) {
        this.observeComponentCreation2((x9, y9) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((v9, w9) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.borderRadius(this.getBorderRadius(r9));
            Stack.size({
                width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonWidth[r9] + 8 : this.buttonWidth[r9],
                height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonHeight[r9] + 8 : this.buttonHeight[r9]
            });
            Stack.borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR);
            Stack.borderWidth(2);
        }, Stack);
        Stack.pop();
        Stack.pop();
    }

    calculateBorderRadius() {
        let l9 = Array.from({
            length: MAX_ITEM_COUNT
        }, (p9, q9) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        });
        for (let n9 = 0; n9 < this.buttonBorderRadius.length; n9++) {
            let o9 = this.buttonItemsSize[n9].height / 2;
            if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                l9[n9].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? o9);
                l9[n9].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? o9);
                l9[n9].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? o9);
                l9[n9].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? o9);
            }
            else {
                if (n9 === 0) {
                    l9[n9].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? o9);
                    l9[n9].topEnd = LengthMetrics.vp(0);
                    l9[n9].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? o9);
                    l9[n9].bottomEnd = LengthMetrics.vp(0);
                }
                else if (this.options.buttons && n9 === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    l9[n9].topStart = LengthMetrics.vp(0);
                    l9[n9].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? o9);
                    l9[n9].bottomStart = LengthMetrics.vp(0);
                    l9[n9].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? o9);
                }
                else {
                    l9[n9].topStart = LengthMetrics.vp(0);
                    l9[n9].topEnd = LengthMetrics.vp(0);
                    l9[n9].bottomStart = LengthMetrics.vp(0);
                    l9[n9].bottomEnd = LengthMetrics.vp(0);
                }
            }
        }
        this.buttonBorderRadius = l9;
    }

    initialRender() {
        this.observeComponentCreation2((e7, f7) => {
            If.create();
            if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g9, h9) => {
                        Row.create({ space: 1 });
                        Row.direction(this.options.direction);
                        Row.focusScopeId(this.groupId, true);
                        Row.padding(this.options.componentPadding);
                        Row.onSizeChange((j9, k9) => {
                            this.componentSize = { width: k9.width, height: k9.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((k7, l7) => {
                        ForEach.create();
                        const m7 = (o7, p7) => {
                            const q7 = o7;
                            this.observeComponentCreation2((s7, t7) => {
                                If.create();
                                if (p7 < MAX_ITEM_COUNT) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((m8, n8) => {
                                            Stack.create();
                                            Stack.direction(this.options.direction);
                                            Stack.borderRadius(this.buttonBorderRadius[p7]);
                                            Stack.scale({
                                                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[p7],
                                                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[p7]
                                            });
                                            Stack.layoutWeight(1);
                                            Stack.onSizeChange((e9, f9) => {
                                                this.buttonItemsSize[p7] = {
                                                    width: f9.width,
                                                    height: this.buttonItemsSize[p7].height
                                                };
                                                if (f9.width) {
                                                    this.buttonItemsPosition[p7] = {
                                                        start: LengthMetrics.vp(Number.parseFloat(this.options.componentPadding.toString()) +
                                                            (Number.parseFloat(f9.width.toString()) + 1) * p7),
                                                        top: LengthMetrics.vp(Number.parseFloat(this.options.componentPadding.toString()))
                                                    };
                                                }
                                            });
                                            ViewStackProcessor.visualState("normal");
                                            Stack.overlay(undefined);
                                            ViewStackProcessor.visualState("focused");
                                            Stack.overlay({ builder: () => {
                                                this.focusStack.call(this, p7);
                                            } }, {
                                                align: Alignment.Center
                                            });
                                            ViewStackProcessor.visualState();
                                            Stack.onFocus(() => {
                                                this.focusIndex = p7;
                                            });
                                            Stack.onTouch((b9) => {
                                                if (b9.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (b9.type === TouchType.Down) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[p7] = 0.95;
                                                    });
                                                }
                                                else if (b9.type === TouchType.Up) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[p7] = 1;
                                                    });
                                                }
                                            });
                                            Stack.onHover((y8) => {
                                                if (y8) {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[p7].hoverColor = (segmentButtonTheme.HOVER_COLOR);
                                                    });
                                                }
                                                else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[p7].hoverColor = Color.Transparent;
                                                    });
                                                }
                                            });
                                            Stack.onMouse((t8) => {
                                                switch (t8.action) {
                                                    case MouseAction.Press:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[p7] = 0.95;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[p7] = true;
                                                        });
                                                        break;
                                                    case MouseAction.Release:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[p7] = 1;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[p7] = false;
                                                        });
                                                        break;
                                                }
                                            });
                                        }, Stack);
                                        this.observeComponentCreation2((f8, g8) => {
                                            __Common__.create();
                                            __Common__.onSizeChange((i8, j8) => {
                                                this.buttonItemsRealHeight[p7] = j8.height;
                                                let k8 = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ?
                                                this.options.buttons.length : 0));
                                                for (let l8 = 0; l8 < this.buttonItemsSize.length; l8++) {
                                                    this.buttonItemsSize[l8] = {
                                                        width: this.buttonItemsSize[l8].width,
                                                        height: k8
                                                    };
                                                }
                                                this.calculateBorderRadius();
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((z7, a8) => {
                                                if (a8) {
                                                    let b8 = new SegmentButtonItem(this, {
                                                        selectedIndexes: this.__selectedIndexes,
                                                        focusIndex: this.__focusIndex,
                                                        index: p7,
                                                        itemOptions: q7,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[p7],
                                                        groupId: this.groupId
                                                    }, undefined, z7, () => {
                                                    }, {
                                                        page: "segmentbutton/src/main/ets/components/mainpage/MainPage.ets",
                                                        line: 769,
                                                        col: 15
                                                    });
                                                    ViewPU.create(b8);
                                                    let c8 = () => {
                                                        return {
                                                            selectedIndexes: this.selectedIndexes,
                                                            focusIndex: this.focusIndex,
                                                            index: p7,
                                                            itemOptions: q7,
                                                            options: this.options,
                                                            property: this.buttonItemProperty[p7],
                                                            groupId: this.groupId
                                                        };
                                                    };
                                                    b8.paramsGenerator_ = c8;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(z7, {
                                                        index: p7,
                                                        itemOptions: q7,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[p7]
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
                        this.forEachUpdateFunction(k7, this.optionsArray, m7, undefined, true, false);
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
        this.fontColor = segmentButtonTheme.FONT_COLOR;
        this.fontSize = segmentButtonTheme.FONT_SIZE;
        this.fontWeight = FontWeight.Regular;
        this.isSelected = false;
    }
};
ItemProperty = __decorate([
    Observed
], ItemProperty);

export class SegmentButton extends ViewPU {
    constructor(z5, a6, b6, c6 = -1, d6 = undefined, e6) {
        super(z5, b6, c6, e6);
        if (typeof d6 === "function") {
            this.paramsGenerator_ = d6;
        }
        this.__options = new SynchedPropertyNesedObjectPU(a6.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(a6.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, "componentSize");
        this.addProvidedVar("componentSize", this.__componentSize, false);
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (b7, c7) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        }), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.__buttonBorderRadius, false);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (z6, a7) => {
            return {};
        }), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.__buttonItemsSize, false);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (x6, y6) => {
            return {};
        }), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.__buttonItemsPosition, false);
        this.__buttonItemsSelected = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (v6, w6) => false), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected, false);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (t6, u6) => new ItemProperty()), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty, false);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex, false);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition, false);
        this.__zoomScaleArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (r6, s6) => 1.0), this, "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.__zoomScaleArray, false);
        this.__pressArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (p6, q6) => false), this, "pressArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (n6, o6) => new HoverColorProperty()), this, "hoverColorArray");
        this.doSelectedChangeAnimate = false;
        this.isCurrentPositionSelected = false;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = false;
        this.__shouldMirror = new ObservedPropertySimplePU(false, this, "shouldMirror");
        this.setInitiallyProvidedValue(a6);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.declareWatch("buttonItemsPosition", this.onItemsPositionChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(y5) {
        this.__options.set(y5.options);
        if (y5.componentSize !== undefined) {
            this.componentSize = y5.componentSize;
        }
        if (y5.buttonBorderRadius !== undefined) {
            this.buttonBorderRadius = y5.buttonBorderRadius;
        }
        if (y5.buttonItemsSize !== undefined) {
            this.buttonItemsSize = y5.buttonItemsSize;
        }
        if (y5.buttonItemsPosition !== undefined) {
            this.buttonItemsPosition = y5.buttonItemsPosition;
        }
        if (y5.buttonItemsSelected !== undefined) {
            this.buttonItemsSelected = y5.buttonItemsSelected;
        }
        if (y5.buttonItemProperty !== undefined) {
            this.buttonItemProperty = y5.buttonItemProperty;
        }
        if (y5.focusIndex !== undefined) {
            this.focusIndex = y5.focusIndex;
        }
        if (y5.selectedItemPosition !== undefined) {
            this.selectedItemPosition = y5.selectedItemPosition;
        }
        if (y5.zoomScaleArray !== undefined) {
            this.zoomScaleArray = y5.zoomScaleArray;
        }
        if (y5.pressArray !== undefined) {
            this.pressArray = y5.pressArray;
        }
        if (y5.hoverColorArray !== undefined) {
            this.hoverColorArray = y5.hoverColorArray;
        }
        if (y5.doSelectedChangeAnimate !== undefined) {
            this.doSelectedChangeAnimate = y5.doSelectedChangeAnimate;
        }
        if (y5.isCurrentPositionSelected !== undefined) {
            this.isCurrentPositionSelected = y5.isCurrentPositionSelected;
        }
        if (y5.panGestureStartPoint !== undefined) {
            this.panGestureStartPoint = y5.panGestureStartPoint;
        }
        if (y5.isPanGestureMoved !== undefined) {
            this.isPanGestureMoved = y5.isPanGestureMoved;
        }
        if (y5.shouldMirror !== undefined) {
            this.shouldMirror = y5.shouldMirror;
        }
    }

    updateStateVars(x5) {
        this.__options.set(x5.options);
    }

    purgeVariableDependenciesOnElmtId(w5) {
        this.__options.purgeDependencyOnElmtId(w5);
        this.__selectedIndexes.purgeDependencyOnElmtId(w5);
        this.__componentSize.purgeDependencyOnElmtId(w5);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(w5);
        this.__buttonItemsSize.purgeDependencyOnElmtId(w5);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(w5);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(w5);
        this.__buttonItemProperty.purgeDependencyOnElmtId(w5);
        this.__focusIndex.purgeDependencyOnElmtId(w5);
        this.__selectedItemPosition.purgeDependencyOnElmtId(w5);
        this.__zoomScaleArray.purgeDependencyOnElmtId(w5);
        this.__pressArray.purgeDependencyOnElmtId(w5);
        this.__hoverColorArray.purgeDependencyOnElmtId(w5);
        this.__shouldMirror.purgeDependencyOnElmtId(w5);
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
        this.__pressArray.aboutToBeDeleted();
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

    set selectedIndexes(v5) {
        this.__selectedIndexes.set(v5);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(u5) {
        this.__componentSize.set(u5);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(t5) {
        this.__buttonBorderRadius.set(t5);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(s5) {
        this.__buttonItemsSize.set(s5);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(r5) {
        this.__buttonItemsPosition.set(r5);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(q5) {
        this.__buttonItemsSelected.set(q5);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(p5) {
        this.__buttonItemProperty.set(p5);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(o5) {
        this.__focusIndex.set(o5);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(n5) {
        this.__selectedItemPosition.set(n5);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(m5) {
        this.__zoomScaleArray.set(m5);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(l5) {
        this.__pressArray.set(l5);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(k5) {
        this.__hoverColorArray.set(k5);
    }

    get shouldMirror() {
        return this.__shouldMirror.get();
    }

    set shouldMirror(j5) {
        this.__shouldMirror.set(j5);
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
        this.buttonItemsSelected.forEach((h5, i5) => {
            this.buttonItemsSelected[i5] = false;
        });
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            this.selectedIndexes.forEach(g5 => this.buttonItemsSelected[g5] = true);
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
        let b5 = this.selectedIndexes.some(d5 => {
            return (d5 === void 0 || d5 < 0 || (this.options.buttons && d5 >= this.options.buttons.length));
        });
        if (b5) {
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
        this.shouldMirror = this.isShouldMirror();
        this.updateSelectedIndexes();
        this.setItemsSelected();
        this.updateAnimatedProperty(null);
    }

    isMouseWheelScroll(z4) {
        return z4.source === SourceType.Mouse && !this.isPanGestureMoved;
    }

    isMovedFromPanGestureStartPoint(x4, y4) {
        return!nearEqual(x4, this.panGestureStartPoint.x) || !nearEqual(y4, this.panGestureStartPoint.y);
    }

    isShouldMirror() {
        if (this.options.direction == Direction.Rtl) {
            return true;
        }
        try {
            let w4 = I18n.System.getSystemLanguage();
            if (w4 === 'ug' && this.options.direction != Direction.Ltr) {
                return true;
            }
        }
        catch (v4) {
            console.error(`Ace SegmentButton getSystemLanguage, error: ${v4.toString()}`);
        }
        return false;
    }

    initialRender() {
        this.observeComponentCreation2((m3, n3) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.onBlur(() => {
                this.focusIndex = -1;
            });
            Stack.onKeyEvent((u4) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (u4.type === KeyType.Down) {
                    if (u4.keyCode === KeyCode.KEYCODE_SPACE || u4.keyCode === KeyCode.KEYCODE_ENTER ||
                        u4.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
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
            TapGesture.onAction((n4) => {
                this.focusIndex = -1;
                let o4 = n4.fingerList.find(Boolean);
                if (o4 === void 0) {
                    return;
                }
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                let p4 = o4.localX;
                let q4 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
                for (let r4 = 0; r4 < q4; r4++) {
                    p4 = p4 - this.buttonItemsSize[r4].width;
                    if (p4 >= 0) {
                        continue;
                    }
                    this.doSelectedChangeAnimate =
                        this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ? false : true;
                    let s4 = this.isShouldMirror() ? q4 - 1 - r4 : r4;
                    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                        let t4 = this.selectedIndexes.indexOf(s4);
                        if (t4 === -1) {
                            this.selectedIndexes.push(s4);
                        }
                        else {
                            this.selectedIndexes.splice(t4, 1);
                        }
                    }
                    else {
                        this.selectedIndexes[0] = s4;
                    }
                    this.doSelectedChangeAnimate = false;
                    break;
                }
            });
            TapGesture.pop();
            SwipeGesture.create();
            SwipeGesture.onAction((m4) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (this.isCurrentPositionSelected) {
                    return;
                }
                if (m4.angle > 0 && this.selectedIndexes[0] !== Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
                    this.doSelectedChangeAnimate = false;
                }
                else if (m4.angle < 0 && this.selectedIndexes[0] !== 0) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
                    this.doSelectedChangeAnimate = false;
                }
            });
            SwipeGesture.pop();
            PanGesture.create();
            PanGesture.onActionStart((i4) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let j4 = i4.fingerList.find(Boolean);
                if (j4 === void 0) {
                    return;
                }
                let k4 = j4.localX;
                this.panGestureStartPoint = { x: j4.globalX, y: j4.globalY };
                this.isPanGestureMoved = false;
                for (let l4 = 0; l4 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); l4++) {
                    k4 = k4 - this.buttonItemsSize[l4].width;
                    if (k4 < 0) {
                        this.isCurrentPositionSelected = l4 === this.selectedIndexes[0] ? true : false;
                        break;
                    }
                }
            });
            PanGesture.onActionUpdate((z3) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (!this.isCurrentPositionSelected) {
                    return;
                }
                let a4 = z3.fingerList.find(Boolean);
                if (a4 === void 0) {
                    return;
                }
                let b4 = a4.localX;
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(a4.globalX, a4.globalY)) {
                    this.isPanGestureMoved = true;
                }
                for (let h4 = 0; h4 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); h4++) {
                    b4 = b4 - this.buttonItemsSize[h4].width;
                    if (b4 < 0) {
                        this.doSelectedChangeAnimate = true;
                        this.selectedIndexes[0] = h4;
                        this.doSelectedChangeAnimate = false;
                        break;
                    }
                }
                this.zoomScaleArray.forEach((d4, e4) => {
                    if (e4 === this.selectedIndexes[0]) {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[e4] = 0.95;
                        });
                    }
                    else {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[e4] = 1;
                        });
                    }
                });
            });
            PanGesture.onActionEnd((v3) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let w3 = v3.fingerList.find(Boolean);
                if (w3 === void 0) {
                    return;
                }
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(w3.globalX, w3.globalY)) {
                    this.isPanGestureMoved = true;
                }
                if (this.isMouseWheelScroll(v3)) {
                    let y3 = v3.offsetX !== 0 ? v3.offsetX : v3.offsetY;
                    this.doSelectedChangeAnimate = true;
                    if (y3 > 0 && this.selectedIndexes[0] > 0) {
                        this.selectedIndexes[0] -= 1;
                    }
                    else if (y3 < 0 && this.selectedIndexes[0] < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
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
                                    this.observeComponentCreation2((g3, h3) => {
                                        if (h3) {
                                            let i3 = new MultiSelectBackground(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                            }, undefined, g3, () => {
                                            }, {
                                                page: "segmentbutton/src/main/ets/components/mainpage/MainPage.ets",
                                                line: 1043,
                                                col: 11
                                            });
                                            ViewPU.create(i3);
                                            let j3 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options
                                                };
                                            };
                                            i3.paramsGenerator_ = j3;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(g3, {
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
                                this.observeComponentCreation2((c3, d3) => {
                                    Stack.create();
                                    Stack.direction(this.options.direction);
                                    Stack.size(ObservedObject.GetRawObject(this.componentSize));
                                    Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                                    Stack.borderRadius(this.options.iconTextBackgroundRadius ?? this.componentSize.height / 2);
                                    Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
                                }, Stack);
                                this.observeComponentCreation2((y1, z1) => {
                                    If.create();
                                    if (this.options.buttons !== void 0 && this.options.buttons.length > 1) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((a3, b3) => {
                                                Row.create({ space: 1 });
                                            }, Row);
                                            this.observeComponentCreation2((e2, f2) => {
                                                ForEach.create();
                                                const g2 = (i2, j2) => {
                                                    const k2 = i2;
                                                    this.observeComponentCreation2((m2, n2) => {
                                                        If.create();
                                                        if (j2 < MAX_ITEM_COUNT) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.observeComponentCreation2((y2, z2) => {
                                                                    Stack.create();
                                                                    Stack.scale({
                                                                        x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[j2],
                                                                        y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[j2]
                                                                    });
                                                                }, Stack);
                                                                {
                                                                    this.observeComponentCreation2((s2, t2) => {
                                                                        if (t2) {
                                                                            let u2 = new PressAndHoverEffect(this, {
                                                                                pressIndex: j2,
                                                                                colorProperty: this.hoverColorArray[j2],
                                                                                press: this.pressArray[j2],
                                                                                options: this.options,
                                                                            }, undefined, s2, () => {
                                                                            }, {
                                                                                page: "segmentbutton/src/main/ets/components/mainpage/MainPage.ets",
                                                                                line: 1054,
                                                                                col: 23
                                                                            });
                                                                            ViewPU.create(u2);
                                                                            let v2 = () => {
                                                                                return {
                                                                                    pressIndex: j2,
                                                                                    colorProperty: this.hoverColorArray[j2],
                                                                                    press: this.pressArray[j2],
                                                                                    options: this.options
                                                                                };
                                                                            };
                                                                            u2.paramsGenerator_ = v2;
                                                                        }
                                                                        else {
                                                                            this.updateStateVarsOfChildByElmtId(s2, {
                                                                                colorProperty: this.hoverColorArray[j2],
                                                                                press: this.pressArray[j2],
                                                                                options: this.options
                                                                            });
                                                                        }
                                                                    }, { name: "PressAndHoverEffect" });
                                                                }
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
                                                this.forEachUpdateFunction(e2, this.options.buttons, g2, undefined, true, false);
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
                                Stack.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((r1, s1) => {
                        Stack.create();
                        Stack.direction(this.options.direction);
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
                                                line: 1078,
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
                                                line: 1084,
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
                                    pressArray: this.__pressArray,
                                    hoverColorArray: this.__hoverColorArray,
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    selectedIndexes: this.__selectedIndexes,
                                }, undefined, t, () => {
                                }, {
                                    page: "segmentbutton/src/main/ets/components/mainpage/MainPage.ets",
                                    line: 1098,
                                    col: 9
                                });
                                ViewPU.create(v);
                                let w = () => {
                                    return {
                                        pressArray: this.pressArray,
                                        hoverColorArray: this.hoverColorArray,
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
                    segmentButtonTheme.TAB_SELECTED_FONT_COLOR : segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR) :
                    this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
            });
        };
        if (a) {
            Context.animateTo({ curve: a }, b);
        }
        else {
            b();
        }
        this.buttonItemsSelected.forEach((e, f) => {
            this.buttonItemProperty[f].fontSize = e ? this.options.selectedFontSize ??
            segmentButtonTheme.SELECTED_FONT_SIZE : this.options.fontSize ?? segmentButtonTheme.FONT_SIZE;
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