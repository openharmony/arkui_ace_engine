/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

var __decorate = (this && this.__decorate) || function (v17, w17, x17, y17) {
    var z17 = arguments.length, a18 = z17 < 3 ? w17 : y17 === null ? y17 = Object.getOwnPropertyDescriptor(w17, x17) : y17, b18;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        a18 = Reflect.decorate(v17, w17, x17, y17);
    else
        for (var c18 = v17.length - 1; c18 >= 0; c18--)
            if (b18 = v17[c18])
                a18 = (z17 < 3 ? b18(a18) : z17 > 3 ? b18(w17, x17, a18) : b18(w17, x17)) || a18;
    return z17 > 3 && a18 && Object.defineProperty(w17, x17, a18), a18;
};
var SegmentButtonItemOptionsArray_1, SegmentButtonOptions_1;
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const curves = globalThis.requireNativeModule("ohos.curves");
const KeyCode = globalThis.requireNapi("multimodalInput.keyCode").KeyCode;
const util = globalThis.requireNapi("util");
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const MIN_ITEM_COUNT = 2;
const MAX_ITEM_COUNT = 5;
const segmentButtonTheme = {
    FONT_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_unselected_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    TAB_SELECTED_FONT_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_checked_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    CAPSULE_SELECTED_FONT_COLOR: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_foreground_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    FONT_SIZE: { "id": -1, "type": 10002, params: ['sys.float.segment_button_checked_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    SELECTED_FONT_SIZE: { "id": -1, "type": 10002, params: ['sys.float.segment_button_unselected_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    BACKGROUND_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_backboard_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    TAB_SELECTED_BACKGROUND_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_checked_foreground_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    CAPSULE_SELECTED_BACKGROUND_COLOR: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    FOCUS_BORDER_COLOR: { "id": -1, "type": 10001, params: ["sys.color.ohos_id_color_focused_outline"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    HOVER_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    PRESS_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_color_Press'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    BACKGROUND_BLUR_STYLE: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_background_blur_style'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value,
    SEGMENT_BUTTON_PADDING: { "id": -1, "type": 10002, params: ['sys.float.segment_button_baseplate_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    CONSTRAINT_SIZE_MIN_HEIGHT: { "id": -1, "type": 10002, params: ['sys.float.segment_button_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    SEGMENT_BUTTON_MIN_FONT_SIZE: { "id": -1, "type": 10002, params: ['sys.float.segment_button_min_font_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    SEGMENT_BUTTON_NORMAL_BORDER_RADIUS: { "id": -1, "type": 10002, params: ['sys.float.segment_button_normal_border_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    SEGMENT_BUTTON_PADDING_NUMBER: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_baseplate_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value,
    SEGMENT_MARQUEE: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_marquee'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value,
    SEGMENT_BUTTON_FOCUS_TEXT_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_focus_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
};
function nearEqual(s17, t17) {
    return Math.abs(s17 - t17) < 0.001;
}
let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(r17) {
        this.icon = r17.icon;
        this.selectedIcon = r17.selectedIcon;
        this.text = r17.text;
    }
};
SegmentButtonItemOptions = __decorate([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends Array {
    constructor(o17) {
        super(typeof o17 === "number" ? o17 : 0);
        this.changeStartIndex = void 0;
        this.deleteCount = void 0;
        this.addLength = void 0;
        if (typeof o17 !== "number" && o17 !== void 0) {
            super.push(...o17.map((q17) => new SegmentButtonItemOptions(q17)));
        }
    }
    push(...l17) {
        if (this.length + l17.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        this.changeStartIndex = this.length;
        this.deleteCount = 0;
        this.addLength = l17.length;
        return super.push(...l17.map((n17) => new SegmentButtonItemOptions(n17)));
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
    unshift(...i17) {
        if (this.length + i17.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        if (i17.length > 0) {
            this.changeStartIndex = 0;
            this.deleteCount = 0;
            this.addLength = i17.length;
        }
        return super.unshift(...i17.map((k17) => new SegmentButtonItemOptions(k17)));
    }
    splice(e17, f17, ...g17) {
        let h17 = (this.length - f17) < 0 ? 0 : (this.length - f17);
        h17 += g17.length;
        if (h17 < MIN_ITEM_COUNT) {
            console.warn("Below the minimum number of elements (2).");
            return [];
        }
        if (h17 > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return [];
        }
        this.changeStartIndex = e17;
        this.deleteCount = f17;
        this.addLength = g17.length;
        return super.splice(e17, f17, ...g17);
    }
    static create(d17) {
        return new SegmentButtonItemOptionsArray_1(d17);
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
    set buttons(c17) {
        if (this._buttons !== void 0 && this._buttons !== c17) {
            this.onButtonsChange?.();
        }
        this._buttons = c17;
    }
    constructor(z16) {
        this.multiply = false;
        this.showText = false;
        this.showIcon = false;
        this._buttons = void 0;
        this.fontColor = z16.fontColor ?? segmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = z16.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = z16.fontSize ?? segmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = z16.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = z16.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = z16.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = z16.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = z16.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = z16.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = z16.buttonPadding;
        this.textPadding = z16.textPadding;
        this.type = z16.type;
        this.backgroundBlurStyle = z16.backgroundBlurStyle ?? segmentButtonTheme.BACKGROUND_BLUR_STYLE;
        this.localizedTextPadding = z16.localizedButtonPadding;
        this.localizedButtonPadding = z16.localizedButtonPadding;
        this.direction = z16.direction ?? Direction.Auto;
        this.buttons = new SegmentButtonItemOptionsArray(z16.buttons);
        if (this.type === "capsule") {
            this.multiply = z16.multiply ?? false;
            this.buttons.forEach(b17 => {
                this.showText ||= b17.text !== void 0;
                this.showIcon ||= b17.icon !== void 0 || b17.selectedIcon !== void 0;
            });
            if (this.showText && this.showIcon) {
                this.iconTextRadius = 12;
                this.iconTextBackgroundRadius = 14;
            }
            this.selectedFontColor = z16.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = z16.selectedBackgroundColor ??
                segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
        else {
            this.showText = true;
        }
        this.componentPadding = this.multiply ? 0 : 2;
    }
    static tab(y16) {
        return new SegmentButtonOptions_1({
            type: "tab",
            buttons: y16.buttons,
            fontColor: y16.fontColor,
            selectedFontColor: y16.selectedFontColor,
            fontSize: y16.fontSize,
            selectedFontSize: y16.selectedFontSize,
            fontWeight: y16.fontWeight,
            selectedFontWeight: y16.selectedFontWeight,
            backgroundColor: y16.backgroundColor,
            selectedBackgroundColor: y16.selectedBackgroundColor,
            imageSize: y16.imageSize,
            buttonPadding: y16.buttonPadding,
            textPadding: y16.textPadding,
            localizedTextPadding: y16.localizedTextPadding,
            localizedButtonPadding: y16.localizedButtonPadding,
            backgroundBlurStyle: y16.backgroundBlurStyle,
            direction: y16.direction
        });
    }
    static capsule(x16) {
        return new SegmentButtonOptions_1({
            type: "capsule",
            buttons: x16.buttons,
            multiply: x16.multiply,
            fontColor: x16.fontColor,
            selectedFontColor: x16.selectedFontColor,
            fontSize: x16.fontSize,
            selectedFontSize: x16.selectedFontSize,
            fontWeight: x16.fontWeight,
            selectedFontWeight: x16.selectedFontWeight,
            backgroundColor: x16.backgroundColor,
            selectedBackgroundColor: x16.selectedBackgroundColor,
            imageSize: x16.imageSize,
            buttonPadding: x16.buttonPadding,
            textPadding: x16.textPadding,
            localizedTextPadding: x16.localizedTextPadding,
            localizedButtonPadding: x16.localizedButtonPadding,
            backgroundBlurStyle: x16.backgroundBlurStyle,
            direction: x16.direction
        });
    }
};
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([
    Observed
], SegmentButtonOptions);
export { SegmentButtonOptions };
class MultiSelectBackground extends ViewPU {
    constructor(r16, s16, t16, u16 = -1, v16 = undefined, w16) {
        super(r16, t16, u16, w16);
        if (typeof v16 === "function") {
            this.paramsGenerator_ = v16;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(s16.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(s16.options, this, "options");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(s16);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q16) {
        this.__optionsArray.set(q16.optionsArray);
        this.__options.set(q16.options);
    }
    updateStateVars(p16) {
        this.__optionsArray.set(p16.optionsArray);
        this.__options.set(p16.options);
    }
    purgeVariableDependenciesOnElmtId(o16) {
        this.__optionsArray.purgeDependencyOnElmtId(o16);
        this.__options.purgeDependencyOnElmtId(o16);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(o16);
        this.__buttonItemsSize.purgeDependencyOnElmtId(o16);
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
    set buttonBorderRadius(n16) {
        this.__buttonBorderRadius.set(n16);
    }
    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }
    set buttonItemsSize(m16) {
        this.__buttonItemsSize.set(m16);
    }
    initialRender() {
        this.observeComponentCreation2((k16, l16) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((v15, w15) => {
            ForEach.create();
            const j2 = (z15, a16) => {
                const b16 = z15;
                this.observeComponentCreation2((d16, e16) => {
                    If.create();
                    if (a16 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((i16, j16) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[a16].height);
                                Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[a16]);
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
            this.forEachUpdateFunction(v15, this.optionsArray, j2, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class SelectItem extends ViewPU {
    constructor(n15, o15, p15, q15 = -1, r15 = undefined, s15) {
        super(n15, p15, q15, s15);
        if (typeof r15 === "function") {
            this.paramsGenerator_ = r15;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(o15.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(o15.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(o15.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__selectedItemPosition = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(o15);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(m15) {
        this.__optionsArray.set(m15.optionsArray);
        this.__options.set(m15.options);
    }
    updateStateVars(l15) {
        this.__optionsArray.set(l15.optionsArray);
        this.__options.set(l15.options);
    }
    purgeVariableDependenciesOnElmtId(k15) {
        this.__optionsArray.purgeDependencyOnElmtId(k15);
        this.__options.purgeDependencyOnElmtId(k15);
        this.__selectedIndexes.purgeDependencyOnElmtId(k15);
        this.__buttonItemsSize.purgeDependencyOnElmtId(k15);
        this.__selectedItemPosition.purgeDependencyOnElmtId(k15);
        this.__zoomScaleArray.purgeDependencyOnElmtId(k15);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(k15);
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
    set selectedIndexes(j15) {
        this.__selectedIndexes.set(j15);
    }
    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }
    set buttonItemsSize(i15) {
        this.__buttonItemsSize.set(i15);
    }
    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }
    set selectedItemPosition(h15) {
        this.__selectedItemPosition.set(h15);
    }
    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }
    set zoomScaleArray(g15) {
        this.__zoomScaleArray.set(g15);
    }
    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }
    set buttonBorderRadius(f15) {
        this.__buttonBorderRadius.set(f15);
    }
    initialRender() {
        this.observeComponentCreation2((y14, z14) => {
            If.create();
            if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d15, e15) => {
                        Stack.create();
                        Stack.direction(this.options.direction);
                        Stack.borderRadius(this.buttonBorderRadius[this.selectedIndexes[0]]);
                        Stack.size(this.buttonItemsSize[this.selectedIndexes[0]]);
                        Stack.backgroundColor(this.options.selectedBackgroundColor ??
                            (this.options.type === 'tab' ? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR :
                                segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR));
                        Stack.position(ObservedObject.GetRawObject(this.selectedItemPosition));
                        Stack.scale({ x: this.zoomScaleArray[this.selectedIndexes[0]], y: this.zoomScaleArray[this.selectedIndexes[0]] });
                        Stack.shadow(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_shadow'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value);
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
    constructor(o14, p14, q14, r14 = -1, s14 = undefined, t14) {
        super(o14, q14, r14, t14);
        if (typeof s14 === "function") {
            this.paramsGenerator_ = s14;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(p14.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(p14.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(p14.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__multiColor = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (v14, w14) => Color.Transparent), this, "multiColor");
        this.setInitiallyProvidedValue(p14);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(n14) {
        this.__optionsArray.set(n14.optionsArray);
        this.__options.set(n14.options);
        if (n14.multiColor !== undefined) {
            this.multiColor = n14.multiColor;
        }
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
        this.__zoomScaleArray.purgeDependencyOnElmtId(l14);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(l14);
        this.__multiColor.purgeDependencyOnElmtId(l14);
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
    set selectedIndexes(k14) {
        this.__selectedIndexes.set(k14);
    }
    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }
    set buttonItemsSize(j14) {
        this.__buttonItemsSize.set(j14);
    }
    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }
    set zoomScaleArray(i14) {
        this.__zoomScaleArray.set(i14);
    }
    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }
    set buttonBorderRadius(h14) {
        this.__buttonBorderRadius.set(h14);
    }
    get multiColor() {
        return this.__multiColor.get();
    }
    set multiColor(g14) {
        this.__multiColor.set(g14);
    }
    onOptionsChange() {
        for (let f14 = 0; f14 < this.selectedIndexes.length; f14++) {
            this.multiColor[this.selectedIndexes[f14]] = this.options.selectedBackgroundColor ??
                segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }
    onSelectedChange() {
        for (let e14 = 0; e14 < MAX_ITEM_COUNT; e14++) {
            this.multiColor[e14] = Color.Transparent;
        }
        for (let d14 = 0; d14 < this.selectedIndexes.length; d14++) {
            this.multiColor[this.selectedIndexes[d14]] = this.options.selectedBackgroundColor ??
                segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }
    aboutToAppear() {
        for (let c14 = 0; c14 < this.selectedIndexes.length; c14++) {
            this.multiColor[this.selectedIndexes[c14]] = this.options.selectedBackgroundColor ??
                segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }
    initialRender() {
        this.observeComponentCreation2((a14, b14) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((l13, m13) => {
            ForEach.create();
            const p1 = (p13, q13) => {
                const r13 = p13;
                this.observeComponentCreation2((t13, u13) => {
                    If.create();
                    if (q13 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((y13, z13) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.width(this.buttonItemsSize[q13].width);
                                Stack.height(this.buttonItemsSize[q13].height);
                                Stack.backgroundColor(this.multiColor[q13]);
                                Stack.borderRadius(this.buttonBorderRadius[q13]);
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
            this.forEachUpdateFunction(l13, this.optionsArray, p1, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class SegmentButtonItem extends ViewPU {
    constructor(d13, e13, f13, g13 = -1, h13 = undefined, i13) {
        super(d13, f13, g13, i13);
        if (typeof h13 === "function") {
            this.paramsGenerator_ = h13;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(e13.selectedIndexes, this, "selectedIndexes");
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(e13.focusIndex, this, "focusIndex");
        this.__itemOptions = new SynchedPropertyNesedObjectPU(e13.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(e13.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(e13.property, this, "property");
        this.__index = new SynchedPropertySimpleOneWayPU(e13.index, this, "index");
        this.__marquee = new SynchedPropertySimpleOneWayPU(e13.marquee, this, "marquee");
        this.__isMarqueeAndFadeout = new SynchedPropertySimpleOneWayPU(e13.isMarqueeAndFadeout, this, "isMarqueeAndFadeout");
        this.__isMarquee = new ObservedPropertySimplePU(false, this, "isMarquee");
        this.__isFadeout = new ObservedPropertySimplePU(false, this, "isFadeout");
        this.groupId = "";
        this.setInitiallyProvidedValue(e13);
        this.declareWatch("focusIndex", this.onFocusIndex);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(c13) {
        this.__itemOptions.set(c13.itemOptions);
        this.__options.set(c13.options);
        this.__property.set(c13.property);
        if (c13.isMarquee !== undefined) {
            this.isMarquee = c13.isMarquee;
        }
        if (c13.isFadeout !== undefined) {
            this.isFadeout = c13.isFadeout;
        }
        if (c13.groupId !== undefined) {
            this.groupId = c13.groupId;
        }
    }
    updateStateVars(b13) {
        this.__itemOptions.set(b13.itemOptions);
        this.__options.set(b13.options);
        this.__property.set(b13.property);
        this.__index.reset(b13.index);
        this.__marquee.reset(b13.marquee);
        this.__isMarqueeAndFadeout.reset(b13.isMarqueeAndFadeout);
    }
    purgeVariableDependenciesOnElmtId(a13) {
        this.__selectedIndexes.purgeDependencyOnElmtId(a13);
        this.__focusIndex.purgeDependencyOnElmtId(a13);
        this.__itemOptions.purgeDependencyOnElmtId(a13);
        this.__options.purgeDependencyOnElmtId(a13);
        this.__property.purgeDependencyOnElmtId(a13);
        this.__index.purgeDependencyOnElmtId(a13);
        this.__marquee.purgeDependencyOnElmtId(a13);
        this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(a13);
        this.__isMarquee.purgeDependencyOnElmtId(a13);
        this.__isFadeout.purgeDependencyOnElmtId(a13);
    }
    aboutToBeDeleted() {
        this.__selectedIndexes.aboutToBeDeleted();
        this.__focusIndex.aboutToBeDeleted();
        this.__itemOptions.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__property.aboutToBeDeleted();
        this.__index.aboutToBeDeleted();
        this.__marquee.aboutToBeDeleted();
        this.__isMarqueeAndFadeout.aboutToBeDeleted();
        this.__isMarquee.aboutToBeDeleted();
        this.__isFadeout.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }
    set selectedIndexes(z12) {
        this.__selectedIndexes.set(z12);
    }
    get focusIndex() {
        return this.__focusIndex.get();
    }
    set focusIndex(y12) {
        this.__focusIndex.set(y12);
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
    set index(x12) {
        this.__index.set(x12);
    }
    get marquee() {
        return this.__marquee.get();
    }
    set marquee(w12) {
        this.__marquee.set(w12);
    }
    get isMarqueeAndFadeout() {
        return this.__isMarqueeAndFadeout.get();
    }
    set isMarqueeAndFadeout(v12) {
        this.__isMarqueeAndFadeout.set(v12);
    }
    get isMarquee() {
        return this.__isMarquee.get();
    }
    set isMarquee(u12) {
        this.__isMarquee.set(u12);
    }
    get isFadeout() {
        return this.__isFadeout.get();
    }
    set isFadeout(t12) {
        this.__isFadeout.set(t12);
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
                top: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_text_capsule_u_d_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                bottom: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_text_capsule_u_d_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_text_l_r_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_text_l_r_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
            };
        }
        return {
            top: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_text_u_d_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            bottom: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_text_u_d_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_text_l_r_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_text_l_r_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
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
            return this.options.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
        }
        else {
            return this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
        }
    }
    getFontColor() {
        let e2 = (typeof this.options.selectedFontColor) === 'object';
        let f2 = false;
        if (e2) {
            let n2 = segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR.id;
            let o2 = segmentButtonTheme.TAB_SELECTED_FONT_COLOR.id;
            let l2 = this.options.selectedFontColor.id;
            f2 = this.options.type === 'tab' ? l2 === o2 :
                l2 === n2;
        }
        if (this.property.isSelected && !f2) {
            return this.options.selectedFontColor;
        }
        else {
            return this.isMarquee ? segmentButtonTheme.SEGMENT_BUTTON_FOCUS_TEXT_COLOR : this.setFontColor();
        }
    }
    initialRender() {
        this.observeComponentCreation2((r12, s12) => {
            Column.create({ space: 2 });
            Column.focusable(false);
            Column.direction(this.options.direction);
            Column.focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.getButtonPadding());
            Column.constraintSize({ minHeight: segmentButtonTheme.CONSTRAINT_SIZE_MIN_HEIGHT });
        }, Column);
        this.observeComponentCreation2((k12, l12) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p12, q12) => {
                        Image.create(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon);
                        Image.direction(this.options.direction);
                        Image.matchTextDirection(this.options.direction == Direction.Ltr ? false : true);
                        Image.size(this.options.imageSize ?? { width: 24, height: 24 });
                        Image.focusable(!this.options.showText);
                        Image.draggable(false);
                        Image.fillColor(this.getFontColor());
                    }, Image);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((c12, d12) => {
            If.create();
            if (this.options.showText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h12, i12) => {
                        Text.create(this.itemOptions.text);
                        Text.direction(this.options.direction);
                        Text.fontColor(this.getFontColor());
                        Text.fontWeight(this.property.fontWeight);
                        Text.fontSize(this.property.fontSize);
                        Text.minFontSize(this.property.minFontSize);
                        Text.maxFontSize(this.property.fontSize);
                        Text.textOverflow(this.marquee ? { overflow: TextOverflow.MARQUEE } : { overflow: TextOverflow.Ellipsis });
                        Text.marqueeOptions({ start: this.isMarquee, fadeout: this.isFadeout });
                        Text.maxLines(1);
                        Text.textAlign(TextAlign.Center);
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
    constructor(t11, u11, v11, w11 = -1, x11 = undefined, y11) {
        super(t11, v11, w11, y11);
        if (typeof x11 === "function") {
            this.paramsGenerator_ = x11;
        }
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(u11.press, this, "press");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(u11.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__options = new SynchedPropertyNesedObjectPU(u11.options, this, "options");
        this.pressIndex = 0;
        this.pressColor = segmentButtonTheme.PRESS_COLOR;
        this.setInitiallyProvidedValue(u11);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(s11) {
        this.__colorProperty.set(s11.colorProperty);
        this.__options.set(s11.options);
        if (s11.pressIndex !== undefined) {
            this.pressIndex = s11.pressIndex;
        }
        if (s11.pressColor !== undefined) {
            this.pressColor = s11.pressColor;
        }
    }
    updateStateVars(r11) {
        this.__press.reset(r11.press);
        this.__colorProperty.set(r11.colorProperty);
        this.__options.set(r11.options);
    }
    purgeVariableDependenciesOnElmtId(q11) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(q11);
        this.__press.purgeDependencyOnElmtId(q11);
        this.__colorProperty.purgeDependencyOnElmtId(q11);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(q11);
        this.__options.purgeDependencyOnElmtId(q11);
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
    set buttonItemsSize(p11) {
        this.__buttonItemsSize.set(p11);
    }
    get press() {
        return this.__press.get();
    }
    set press(o11) {
        this.__press.set(o11);
    }
    get colorProperty() {
        return this.__colorProperty.get();
    }
    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }
    set buttonBorderRadius(n11) {
        this.__buttonBorderRadius.set(n11);
    }
    get options() {
        return this.__options.get();
    }
    initialRender() {
        this.observeComponentCreation2((l11, m11) => {
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
    constructor(p10, q10, r10, s10 = -1, t10 = undefined, u10) {
        super(p10, r10, s10, u10);
        if (typeof t10 === "function") {
            this.paramsGenerator_ = t10;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(q10.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(q10.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(q10.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = this.initializeConsume("componentSize", "componentSize");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__buttonItemsPosition = this.initializeConsume("buttonItemsPosition", "buttonItemsPosition");
        this.__focusIndex = this.initializeConsume("focusIndex", "focusIndex");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonItemProperty = this.initializeConsume("buttonItemProperty", "buttonItemProperty");
        this.__buttonItemsSelected = this.initializeConsume("buttonItemsSelected", "buttonItemsSelected");
        this.__pressArray = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (i11, j11) => false), this, "pressArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (g11, h11) => new HoverColorProperty()), this, "hoverColorArray");
        this.__buttonWidth = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (e11, f11) => 0), this, "buttonWidth");
        this.__buttonHeight = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (c11, d11) => 0), this, "buttonHeight");
        this.__marquee = new ObservedPropertySimplePU(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_marquee'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value === 0, this, "marquee");
        this.__isMarqueeAndFadeout = new ObservedPropertySimplePU(false, this, "isMarqueeAndFadeout");
        this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (a11, b11) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.segmentFocusControl = LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_focus_control'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value === 1;
        this.setInitiallyProvidedValue(q10);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.declareWatch("focusIndex", this.onFocusIndex);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(o10) {
        this.__optionsArray.set(o10.optionsArray);
        this.__options.set(o10.options);
        if (o10.pressArray !== undefined) {
            this.pressArray = o10.pressArray;
        }
        if (o10.hoverColorArray !== undefined) {
            this.hoverColorArray = o10.hoverColorArray;
        }
        if (o10.buttonWidth !== undefined) {
            this.buttonWidth = o10.buttonWidth;
        }
        if (o10.buttonHeight !== undefined) {
            this.buttonHeight = o10.buttonHeight;
        }
        if (o10.marquee !== undefined) {
            this.marquee = o10.marquee;
        }
        if (o10.isMarqueeAndFadeout !== undefined) {
            this.isMarqueeAndFadeout = o10.isMarqueeAndFadeout;
        }
        if (o10.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = o10.buttonItemsRealHeight;
        }
        if (o10.groupId !== undefined) {
            this.groupId = o10.groupId;
        }
        if (o10.segmentFocusControl !== undefined) {
            this.segmentFocusControl = o10.segmentFocusControl;
        }
    }
    updateStateVars(n10) {
        this.__optionsArray.set(n10.optionsArray);
        this.__options.set(n10.options);
    }
    purgeVariableDependenciesOnElmtId(m10) {
        this.__optionsArray.purgeDependencyOnElmtId(m10);
        this.__options.purgeDependencyOnElmtId(m10);
        this.__selectedIndexes.purgeDependencyOnElmtId(m10);
        this.__componentSize.purgeDependencyOnElmtId(m10);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(m10);
        this.__buttonItemsSize.purgeDependencyOnElmtId(m10);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(m10);
        this.__focusIndex.purgeDependencyOnElmtId(m10);
        this.__zoomScaleArray.purgeDependencyOnElmtId(m10);
        this.__buttonItemProperty.purgeDependencyOnElmtId(m10);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(m10);
        this.__pressArray.purgeDependencyOnElmtId(m10);
        this.__hoverColorArray.purgeDependencyOnElmtId(m10);
        this.__buttonWidth.purgeDependencyOnElmtId(m10);
        this.__buttonHeight.purgeDependencyOnElmtId(m10);
        this.__marquee.purgeDependencyOnElmtId(m10);
        this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(m10);
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
        this.__marquee.aboutToBeDeleted();
        this.__isMarqueeAndFadeout.aboutToBeDeleted();
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
    set selectedIndexes(l10) {
        this.__selectedIndexes.set(l10);
    }
    get componentSize() {
        return this.__componentSize.get();
    }
    set componentSize(k10) {
        this.__componentSize.set(k10);
    }
    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }
    set buttonBorderRadius(j10) {
        this.__buttonBorderRadius.set(j10);
    }
    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }
    set buttonItemsSize(i10) {
        this.__buttonItemsSize.set(i10);
    }
    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }
    set buttonItemsPosition(h10) {
        this.__buttonItemsPosition.set(h10);
    }
    get focusIndex() {
        return this.__focusIndex.get();
    }
    set focusIndex(g10) {
        this.__focusIndex.set(g10);
    }
    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }
    set zoomScaleArray(f10) {
        this.__zoomScaleArray.set(f10);
    }
    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }
    set buttonItemProperty(e10) {
        this.__buttonItemProperty.set(e10);
    }
    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }
    set buttonItemsSelected(d10) {
        this.__buttonItemsSelected.set(d10);
    }
    get pressArray() {
        return this.__pressArray.get();
    }
    set pressArray(c10) {
        this.__pressArray.set(c10);
    }
    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }
    set hoverColorArray(b10) {
        this.__hoverColorArray.set(b10);
    }
    get buttonWidth() {
        return this.__buttonWidth.get();
    }
    set buttonWidth(a10) {
        this.__buttonWidth.set(a10);
    }
    get buttonHeight() {
        return this.__buttonHeight.get();
    }
    set buttonHeight(z9) {
        this.__buttonHeight.set(z9);
    }
    get marquee() {
        return this.__marquee.get();
    }
    set marquee(y9) {
        this.__marquee.set(y9);
    }
    get isMarqueeAndFadeout() {
        return this.__isMarqueeAndFadeout.get();
    }
    set isMarqueeAndFadeout(x9) {
        this.__isMarqueeAndFadeout.set(x9);
    }
    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((v9, w9) => {
            this.buttonWidth[w9] = v9.width;
            this.buttonHeight[w9] = v9.height;
        });
    }
    changeSelectedIndexes(j9) {
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
            let k9 = this.selectedIndexes;
            for (let p9 = 0; p9 < this.optionsArray.deleteCount; p9++) {
                let q9 = k9.indexOf(this.optionsArray.changeStartIndex);
                let r9 = k9.map(t9 => this.optionsArray.changeStartIndex &&
                    (t9 > this.optionsArray.changeStartIndex) ? t9 - 1 : t9);
                if (q9 !== -1) {
                    r9.splice(q9, 1);
                }
                k9 = r9;
            }
            for (let l9 = 0; l9 < this.optionsArray.addLength; l9++) {
                let m9 = k9.map(o9 => this.optionsArray.changeStartIndex &&
                    (o9 >= this.optionsArray.changeStartIndex) ? o9 + 1 : o9);
                k9 = m9;
            }
            this.selectedIndexes = k9;
        }
    }
    changeFocusIndex(i9) {
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
        let h9 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 &&
            this.optionsArray.addLength !== void 0) {
            this.changeSelectedIndexes(h9);
            this.changeFocusIndex(h9);
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
    onFocusIndex() {
        this.isMarqueeAndFadeout = this.marquee && !this.isMarqueeAndFadeout;
    }
    aboutToAppear() {
        for (let g9 = 0; g9 < this.buttonItemsRealHeight.length; g9++) {
            this.buttonItemsRealHeight[g9] = 0;
        }
    }
    getBorderRadius(e9) {
        let f9 = this.buttonBorderRadius[e9];
        if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] && f9.topStart) {
            f9.topStart = LengthMetrics.vp(f9.topStart.value + 4);
            f9.topEnd = LengthMetrics.vp(f9.topStart.value + 4);
            f9.bottomStart = LengthMetrics.vp(f9.topStart.value + 4);
            f9.bottomEnd = LengthMetrics.vp(f9.topStart.value + 4);
        }
        return f9;
    }
    focusStack(w8, x8 = null) {
        this.observeComponentCreation2((c9, d9) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((a9, b9) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.borderRadius(this.getBorderRadius(w8));
            Stack.size({
                width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonWidth[w8] + 8 : this.buttonWidth[w8],
                height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonHeight[w8] + 8 : this.buttonHeight[w8]
            });
            Stack.borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR);
            Stack.borderWidth(2);
        }, Stack);
        Stack.pop();
        Stack.pop();
    }
    calculateBorderRadius() {
        let q8 = Array.from({
            length: MAX_ITEM_COUNT
        }, (u8, v8) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        });
        for (let s8 = 0; s8 < this.buttonBorderRadius.length; s8++) {
            let t8 = this.buttonItemsSize[s8].height / 2;
            if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                q8[s8].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? t8);
                q8[s8].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? t8);
                q8[s8].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? t8);
                q8[s8].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? t8);
            }
            else {
                if (s8 === 0) {
                    q8[s8].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? t8);
                    q8[s8].topEnd = LengthMetrics.vp(0);
                    q8[s8].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? t8);
                    q8[s8].bottomEnd = LengthMetrics.vp(0);
                }
                else if (this.options.buttons && s8 === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    q8[s8].topStart = LengthMetrics.vp(0);
                    q8[s8].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? t8);
                    q8[s8].bottomStart = LengthMetrics.vp(0);
                    q8[s8].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? t8);
                }
                else {
                    q8[s8].topStart = LengthMetrics.vp(0);
                    q8[s8].topEnd = LengthMetrics.vp(0);
                    q8[s8].bottomStart = LengthMetrics.vp(0);
                    q8[s8].bottomEnd = LengthMetrics.vp(0);
                }
            }
        }
        this.buttonBorderRadius = q8;
    }
    SegmentButtonFocus(o7, p7, q7 = null) {
        this.observeComponentCreation2((o8, p8) => {
            Stack.create();
        }, Stack);
        {
            this.observeComponentCreation2((i8, j8) => {
                if (j8) {
                    let k8 = new PressAndHoverEffect(ViewPU.__proto__ !== NativeViewPartialUpdate && q7 instanceof PUV2ViewBase ? q7 : this, {
                        pressIndex: o7,
                        colorProperty: this.hoverColorArray[o7],
                        press: this.pressArray[o7],
                        options: this.options,
                    }, undefined, i8, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton222.ets", line: 824, col: 7 });
                    ViewPU.create(k8);
                    let o1 = () => {
                        return {
                            pressIndex: o7,
                            colorProperty: this.hoverColorArray[o7],
                            press: this.pressArray[o7],
                            options: this.options
                        };
                    };
                    k8.paramsGenerator_ = o1;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(i8, {
                        colorProperty: this.hoverColorArray[o7],
                        press: this.pressArray[o7],
                        options: this.options
                    });
                }
            }, { name: "PressAndHoverEffect" });
        }
        this.observeComponentCreation2((a8, b8) => {
            __Common__.create();
            __Common__.onSizeChange((d8, e8) => {
                this.buttonItemsRealHeight[o7] = e8.height;
                let f8 = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ?
                    this.options.buttons.length : 0));
                for (let g8 = 0; g8 < this.buttonItemsSize.length; g8++) {
                    this.buttonItemsSize[g8] = { width: this.buttonItemsSize[g8].width, height: f8 };
                }
                this.calculateBorderRadius();
            });
        }, __Common__);
        {
            this.observeComponentCreation2((u7, v7) => {
                if (v7) {
                    let w7 = new SegmentButtonItem(ViewPU.__proto__ !== NativeViewPartialUpdate && q7 instanceof PUV2ViewBase ? q7 : this, {
                        isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                        selectedIndexes: this.__selectedIndexes,
                        focusIndex: this.__focusIndex,
                        index: o7,
                        itemOptions: p7,
                        options: this.options,
                        property: this.buttonItemProperty[o7],
                        groupId: this.groupId,
                        marquee: this.marquee
                    }, undefined, u7, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton222.ets", line: 830, col: 7 });
                    ViewPU.create(w7);
                    let h1 = () => {
                        return {
                            isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                            selectedIndexes: this.selectedIndexes,
                            focusIndex: this.focusIndex,
                            index: o7,
                            itemOptions: p7,
                            options: this.options,
                            property: this.buttonItemProperty[o7],
                            groupId: this.groupId,
                            marquee: this.marquee
                        };
                    };
                    w7.paramsGenerator_ = h1;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(u7, {
                        isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                        index: o7,
                        itemOptions: p7,
                        options: this.options,
                        property: this.buttonItemProperty[o7],
                        marquee: this.marquee
                    });
                }
            }, { name: "SegmentButtonItem" });
        }
        __Common__.pop();
        Stack.pop();
    }
    initialRender() {
        this.observeComponentCreation2((l5, m5) => {
            If.create();
            if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j7, k7) => {
                        Row.create({ space: 1 });
                        Row.direction(this.options.direction);
                        Row.focusScopeId(this.groupId, true);
                        Row.padding(this.options?.multiply ? 0 : segmentButtonTheme.SEGMENT_BUTTON_PADDING);
                        Row.onSizeChange((m7, n7) => {
                            this.componentSize = { width: n7.width, height: n7.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((r5, s5) => {
                        ForEach.create();
                        const w = (v5, w5) => {
                            const x5 = v5;
                            this.observeComponentCreation2((z5, a6) => {
                                If.create();
                                if (w5 < MAX_ITEM_COUNT) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((n6, o6) => {
                                            Stack.create();
                                            Stack.direction(this.options.direction);
                                            Stack.borderRadius(this.buttonBorderRadius[w5]);
                                            Stack.scale({
                                                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[w5],
                                                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[w5]
                                            });
                                            Stack.layoutWeight(1);
                                            Stack.onSizeChange((h7, i7) => {
                                                this.buttonItemsSize[w5] = { width: i7.width, height: this.buttonItemsSize[w5].height };
                                                if (i7.width) {
                                                    this.buttonItemsPosition[w5] = {
                                                        x: this.options.multiply ? 0 : Number(segmentButtonTheme.SEGMENT_BUTTON_PADDING_NUMBER) +
                                                            (Number.parseFloat(i7.width.toString()) + 1) * w5,
                                                        y: Number(segmentButtonTheme.SEGMENT_BUTTON_PADDING_NUMBER)
                                                    };
                                                }
                                            });
                                            Stack.onClick(() => {
                                                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                                                    if (this.selectedIndexes.indexOf(w5) > -1) {
                                                        this.selectedIndexes.splice(this.selectedIndexes.indexOf(w5), 1);
                                                    }
                                                    else {
                                                        this.selectedIndexes.push(w5);
                                                    }
                                                }
                                                else {
                                                    this.selectedIndexes[0] = w5;
                                                }
                                            });
                                            Stack.focusable(true);
                                            Stack.focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === w5 ?
                                                FocusPriority.PREVIOUS : FocusPriority.AUTO);
                                            Stack.onFocus(() => {
                                                this.focusIndex = w5;
                                                this.marquee = segmentButtonTheme.SEGMENT_MARQUEE === 0;
                                                if (this.marquee) {
                                                    this.hoverColorArray[w5].hoverColor = { "id": -1, "type": 10001, params: ['sys.color.segment_button_focus_backboard_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                                }
                                            });
                                            Stack.onBlur(() => {
                                                this.focusIndex = -1;
                                                this.hoverColorArray[w5].hoverColor = Color.Transparent;
                                            });
                                            Stack.onTouch((e7) => {
                                                if (this.marquee) {
                                                    this.getUIContext().getFocusController().clearFocus();
                                                }
                                                if (e7.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (e7.type === TouchType.Down) {
                                                    Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                                                        this.zoomScaleArray[w5] = 0.95;
                                                    });
                                                }
                                                else if (e7.type === TouchType.Up) {
                                                    Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                                                        this.zoomScaleArray[w5] = 1;
                                                    });
                                                }
                                            });
                                            Stack.onHover((b7) => {
                                                Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                    if (b7) {
                                                        this.hoverColorArray[w5].hoverColor = this.marquee && this.focusIndex === w5 ? { "id": -1, "type": 10001, params: ['sys.color.segment_button_focus_backboard_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : (segmentButtonTheme.HOVER_COLOR);
                                                    }
                                                    else {
                                                        this.hoverColorArray[w5].hoverColor = this.marquee && this.focusIndex === w5 ? { "id": -1, "type": 10001, params: ['sys.color.segment_button_focus_backboard_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : Color.Transparent;
                                                    }
                                                });
                                            });
                                            Stack.onMouse((w6) => {
                                                switch (w6.action) {
                                                    case MouseAction.Press:
                                                        Context.animateTo({ curve: curves.springMotion(0.347, 0.99) }, () => {
                                                            this.zoomScaleArray[w5] = 0.95;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[w5] = true;
                                                        });
                                                        break;
                                                    case MouseAction.Release:
                                                        Context.animateTo({ curve: curves.springMotion(0.347, 0.99) }, () => {
                                                            this.zoomScaleArray[w5] = 1;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[w5] = false;
                                                        });
                                                        break;
                                                }
                                            });
                                        }, Stack);
                                        this.observeComponentCreation2((f6, g6) => {
                                            If.create();
                                            if (this.segmentFocusControl) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((k6, l6) => {
                                                        Stack.create();
                                                        ViewStackProcessor.visualState("normal");
                                                        Stack.overlay(undefined);
                                                        ViewStackProcessor.visualState("focused");
                                                        Stack.overlay({ builder: () => {
                                                                this.focusStack.call(this, w5);
                                                            } }, {
                                                            align: Alignment.Center
                                                        });
                                                        ViewStackProcessor.visualState();
                                                        Stack.onClick(() => {
                                                            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                                                                if (this.selectedIndexes.indexOf(w5) > -1) {
                                                                    this.selectedIndexes.splice(this.selectedIndexes.indexOf(w5), 1);
                                                                }
                                                                else {
                                                                    this.selectedIndexes.push(w5);
                                                                }
                                                            }
                                                            else {
                                                                this.selectedIndexes[0] = w5;
                                                            }
                                                        });
                                                    }, Stack);
                                                    this.SegmentButtonFocus.bind(this)(w5, x5, this);
                                                    Stack.pop();
                                                });
                                            }
                                            else {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.SegmentButtonFocus.bind(this)(w5, x5, this);
                                                });
                                            }
                                        }, If);
                                        If.pop();
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
                        this.forEachUpdateFunction(r5, this.optionsArray, w, undefined, true, false);
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
        this.minFontSize = segmentButtonTheme.SEGMENT_BUTTON_MIN_FONT_SIZE || 9;
        this.normalborderRadius = segmentButtonTheme.SEGMENT_BUTTON_NORMAL_BORDER_RADIUS || 2;
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
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
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
        this.__buttonItemsSelected = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (c5, d5) => false), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected, false);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (a5, b5) => new ItemProperty()), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty, false);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex, false);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition, false);
        this.__zoomScaleArray = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (y4, z4) => 1.0), this, "zoomScaleArray");
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
        return !nearEqual(n3, this.panGestureStartPoint.x) || !nearEqual(o3, this.panGestureStartPoint.y);
    }
    initialRender() {
        this.observeComponentCreation2((h2, i2) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.onBlur(() => {
                this.focusIndex = -1;
            });
            Stack.onKeyEvent((m3) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (m3.type === KeyType.Down) {
                    if (m3.keyCode === KeyCode.KEYCODE_SPACE || m3.keyCode === KeyCode.KEYCODE_ENTER ||
                        m3.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
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
                                            }, undefined, b2, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton222.ets", line: 1138, col: 11 });
                                            ViewPU.create(d2);
                                            let q = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options
                                                };
                                            };
                                            d2.paramsGenerator_ = q;
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
                                    Stack.direction(this.options.direction);
                                    Stack.size(ObservedObject.GetRawObject(this.componentSize));
                                    Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
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
                                            }, undefined, l1, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton222.ets", line: 1152, col: 13 });
                                            ViewPU.create(n1);
                                            let p = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            n1.paramsGenerator_ = p;
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
                                            }, undefined, d1, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton222.ets", line: 1158, col: 13 });
                                            ViewPU.create(f1);
                                            let j = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            f1.paramsGenerator_ = j;
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
                                }, undefined, t, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton222.ets", line: 1172, col: 9 });
                                ViewPU.create(v);
                                let c = () => {
                                    return {
                                        optionsArray: this.options.buttons,
                                        options: this.options,
                                        selectedIndexes: this.selectedIndexes
                                    };
                                };
                                v.paramsGenerator_ = c;
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
            this.selectedItemPosition = this.selectedIndexes.length === 0 ? {} : this.buttonItemsPosition[this.selectedIndexes[0]];
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