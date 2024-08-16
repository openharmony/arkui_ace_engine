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

var __decorate = (this && this.__decorate) || function (z17, a18, b18, c18) {
    var d18 = arguments.length, e18 = d18 < 3 ? a18 : c18 === null ? c18 = Object.getOwnPropertyDescriptor(a18, b18) : c18, f18;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        e18 = Reflect.decorate(z17, a18, b18, c18);
    else
        for (var g18 = z17.length - 1; g18 >= 0; g18--)
            if (f18 = z17[g18])
                e18 = (d18 < 3 ? f18(e18) : d18 > 3 ? f18(a18, b18, e18) : f18(a18, b18)) || e18;
    return d18 > 3 && e18 && Object.defineProperty(a18, b18, e18), e18;
};
var SegmentButtonItemOptionsArray_1, SegmentButtonOptions_1;
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const curves = globalThis.requireNativeModule('ohos.curves');
const KeyCode = globalThis.requireNapi('multimodalInput.keyCode').KeyCode;
const util = globalThis.requireNapi('util');
const LengthMetrics = requireNapi('arkui.node').LengthMetric
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
function nearEqual(w17, x17) {
    return Math.abs(w17 - x17) < 0.001;
}
let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(v17) {
        this.icon = v17.icon;
        this.selectedIcon = v17.selectedIcon;
        this.text = v17.text;
    }
};
SegmentButtonItemOptions = __decorate([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends Array {
    constructor(s17) {
        super(typeof s17 === "number" ? s17 : 0);
        this.changeStartIndex = void 0;
        this.deleteCount = void 0;
        this.addLength = void 0;
        if (typeof s17 !== "number" && s17 !== void 0) {
            super.push(...s17.map((u17) => new SegmentButtonItemOptions(u17)));
        }
    }
    push(...p17) {
        if (this.length + p17.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        this.changeStartIndex = this.length;
        this.deleteCount = 0;
        this.addLength = p17.length;
        return super.push(...p17.map((r17) => new SegmentButtonItemOptions(r17)));
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
    unshift(...m17) {
        if (this.length + m17.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        if (m17.length > 0) {
            this.changeStartIndex = 0;
            this.deleteCount = 0;
            this.addLength = m17.length;
        }
        return super.unshift(...m17.map((o17) => new SegmentButtonItemOptions(o17)));
    }
    splice(i17, j17, ...k17) {
        let l17 = (this.length - j17) < 0 ? 0 : (this.length - j17);
        l17 += k17.length;
        if (l17 < MIN_ITEM_COUNT) {
            console.warn("Below the minimum number of elements (2).");
            return [];
        }
        if (l17 > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return [];
        }
        this.changeStartIndex = i17;
        this.deleteCount = j17;
        this.addLength = k17.length;
        return super.splice(i17, j17, ...k17);
    }
    static create(h17) {
        return new SegmentButtonItemOptionsArray_1(h17);
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
    set buttons(g17) {
        if (this._buttons !== void 0 && this._buttons !== g17) {
            this.onButtonsChange?.();
        }
        this._buttons = g17;
    }
    constructor(d17) {
        this.multiply = false;
        this.showText = false;
        this.showIcon = false;
        this._buttons = void 0;
        this.fontColor = d17.fontColor ?? segmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = d17.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = d17.fontSize ?? segmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = d17.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = d17.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = d17.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = d17.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = d17.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = d17.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = d17.buttonPadding;
        this.textPadding = d17.textPadding;
        this.type = d17.type;
        this.backgroundBlurStyle = d17.backgroundBlurStyle ?? segmentButtonTheme.BACKGROUND_BLUR_STYLE;
        this.localizedTextPadding = d17.localizedButtonPadding;
        this.localizedButtonPadding = d17.localizedButtonPadding;
        this.direction = d17.direction ?? Direction.Auto;
        this.buttons = new SegmentButtonItemOptionsArray(d17.buttons);
        if (this.type === "capsule") {
            this.multiply = d17.multiply ?? false;
            this.buttons.forEach(f17 => {
                this.showText ||= f17.text !== void 0;
                this.showIcon ||= f17.icon !== void 0 || f17.selectedIcon !== void 0;
            });
            if (this.showText && this.showIcon) {
                this.iconTextRadius = 12;
                this.iconTextBackgroundRadius = 14;
            }
            this.selectedFontColor = d17.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = d17.selectedBackgroundColor ??
                segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
        else {
            this.showText = true;
        }
        this.componentPadding = this.multiply ? 0 : 2;
    }
    static tab(c17) {
        return new SegmentButtonOptions_1({
            type: "tab",
            buttons: c17.buttons,
            fontColor: c17.fontColor,
            selectedFontColor: c17.selectedFontColor,
            fontSize: c17.fontSize,
            selectedFontSize: c17.selectedFontSize,
            fontWeight: c17.fontWeight,
            selectedFontWeight: c17.selectedFontWeight,
            backgroundColor: c17.backgroundColor,
            selectedBackgroundColor: c17.selectedBackgroundColor,
            imageSize: c17.imageSize,
            buttonPadding: c17.buttonPadding,
            textPadding: c17.textPadding,
            localizedTextPadding: c17.localizedTextPadding,
            localizedButtonPadding: c17.localizedButtonPadding,
            backgroundBlurStyle: c17.backgroundBlurStyle,
            direction: c17.direction
        });
    }
    static capsule(b17) {
        return new SegmentButtonOptions_1({
            type: "capsule",
            buttons: b17.buttons,
            multiply: b17.multiply,
            fontColor: b17.fontColor,
            selectedFontColor: b17.selectedFontColor,
            fontSize: b17.fontSize,
            selectedFontSize: b17.selectedFontSize,
            fontWeight: b17.fontWeight,
            selectedFontWeight: b17.selectedFontWeight,
            backgroundColor: b17.backgroundColor,
            selectedBackgroundColor: b17.selectedBackgroundColor,
            imageSize: b17.imageSize,
            buttonPadding: b17.buttonPadding,
            textPadding: b17.textPadding,
            localizedTextPadding: b17.localizedTextPadding,
            localizedButtonPadding: b17.localizedButtonPadding,
            backgroundBlurStyle: b17.backgroundBlurStyle,
            direction: b17.direction
        });
    }
};
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([
    Observed
], SegmentButtonOptions);
export { SegmentButtonOptions };
class MultiSelectBackground extends ViewPU {
    constructor(v16, w16, x16, y16 = -1, z16 = undefined, a17) {
        super(v16, x16, y16, a17);
        if (typeof z16 === "function") {
            this.paramsGenerator_ = z16;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(w16.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(w16.options, this, "options");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(w16);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(u16) {
        this.__optionsArray.set(u16.optionsArray);
        this.__options.set(u16.options);
    }
    updateStateVars(t16) {
        this.__optionsArray.set(t16.optionsArray);
        this.__options.set(t16.options);
    }
    purgeVariableDependenciesOnElmtId(s16) {
        this.__optionsArray.purgeDependencyOnElmtId(s16);
        this.__options.purgeDependencyOnElmtId(s16);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(s16);
        this.__buttonItemsSize.purgeDependencyOnElmtId(s16);
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
    set buttonBorderRadius(r16) {
        this.__buttonBorderRadius.set(r16);
    }
    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }
    set buttonItemsSize(q16) {
        this.__buttonItemsSize.set(q16);
    }
    initialRender() {
        this.observeComponentCreation2((o16, p16) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((z15, a16) => {
            ForEach.create();
            const e2 = (d16, e16) => {
                const f16 = d16;
                this.observeComponentCreation2((h16, i16) => {
                    If.create();
                    if (e16 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((m16, n16) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[e16].height);
                                Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[e16]);
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
            this.forEachUpdateFunction(z15, this.optionsArray, e2, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class SelectItem extends ViewPU {
    constructor(r15, s15, t15, u15 = -1, v15 = undefined, w15) {
        super(r15, t15, u15, w15);
        if (typeof v15 === "function") {
            this.paramsGenerator_ = v15;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(s15.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(s15.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(s15.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__selectedItemPosition = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(s15);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q15) {
        this.__optionsArray.set(q15.optionsArray);
        this.__options.set(q15.options);
    }
    updateStateVars(p15) {
        this.__optionsArray.set(p15.optionsArray);
        this.__options.set(p15.options);
    }
    purgeVariableDependenciesOnElmtId(o15) {
        this.__optionsArray.purgeDependencyOnElmtId(o15);
        this.__options.purgeDependencyOnElmtId(o15);
        this.__selectedIndexes.purgeDependencyOnElmtId(o15);
        this.__buttonItemsSize.purgeDependencyOnElmtId(o15);
        this.__selectedItemPosition.purgeDependencyOnElmtId(o15);
        this.__zoomScaleArray.purgeDependencyOnElmtId(o15);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(o15);
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
    set selectedIndexes(n15) {
        this.__selectedIndexes.set(n15);
    }
    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }
    set buttonItemsSize(m15) {
        this.__buttonItemsSize.set(m15);
    }
    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }
    set selectedItemPosition(l15) {
        this.__selectedItemPosition.set(l15);
    }
    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }
    set zoomScaleArray(k15) {
        this.__zoomScaleArray.set(k15);
    }
    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }
    set buttonBorderRadius(j15) {
        this.__buttonBorderRadius.set(j15);
    }
    initialRender() {
        this.observeComponentCreation2((c15, d15) => {
            If.create();
            if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h15, i15) => {
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
    constructor(s14, t14, u14, v14 = -1, w14 = undefined, x14) {
        super(s14, u14, v14, x14);
        if (typeof w14 === "function") {
            this.paramsGenerator_ = w14;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(t14.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(t14.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(t14.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__multiColor = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (z14, a15) => Color.Transparent), this, "multiColor");
        this.setInitiallyProvidedValue(t14);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r14) {
        this.__optionsArray.set(r14.optionsArray);
        this.__options.set(r14.options);
        if (r14.multiColor !== undefined) {
            this.multiColor = r14.multiColor;
        }
    }
    updateStateVars(q14) {
        this.__optionsArray.set(q14.optionsArray);
        this.__options.set(q14.options);
    }
    purgeVariableDependenciesOnElmtId(p14) {
        this.__optionsArray.purgeDependencyOnElmtId(p14);
        this.__options.purgeDependencyOnElmtId(p14);
        this.__selectedIndexes.purgeDependencyOnElmtId(p14);
        this.__buttonItemsSize.purgeDependencyOnElmtId(p14);
        this.__zoomScaleArray.purgeDependencyOnElmtId(p14);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(p14);
        this.__multiColor.purgeDependencyOnElmtId(p14);
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
    set selectedIndexes(o14) {
        this.__selectedIndexes.set(o14);
    }
    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }
    set buttonItemsSize(n14) {
        this.__buttonItemsSize.set(n14);
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
    get multiColor() {
        return this.__multiColor.get();
    }
    set multiColor(k14) {
        this.__multiColor.set(k14);
    }
    onOptionsChange() {
        for (let j14 = 0; j14 < this.selectedIndexes.length; j14++) {
            this.multiColor[this.selectedIndexes[j14]] = this.options.selectedBackgroundColor ??
                segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }
    onSelectedChange() {
        for (let i14 = 0; i14 < MAX_ITEM_COUNT; i14++) {
            this.multiColor[i14] = Color.Transparent;
        }
        for (let h14 = 0; h14 < this.selectedIndexes.length; h14++) {
            this.multiColor[this.selectedIndexes[h14]] = this.options.selectedBackgroundColor ??
                segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }
    aboutToAppear() {
        for (let g14 = 0; g14 < this.selectedIndexes.length; g14++) {
            this.multiColor[this.selectedIndexes[g14]] = this.options.selectedBackgroundColor ??
                segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }
    initialRender() {
        this.observeComponentCreation2((e14, f14) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((p13, q13) => {
            ForEach.create();
            const p1 = (t13, u13) => {
                const v13 = t13;
                this.observeComponentCreation2((x13, y13) => {
                    If.create();
                    if (u13 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((c14, d14) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.width(this.buttonItemsSize[u13].width);
                                Stack.height(this.buttonItemsSize[u13].height);
                                Stack.backgroundColor(this.multiColor[u13]);
                                Stack.borderRadius(this.buttonBorderRadius[u13]);
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
            this.forEachUpdateFunction(p13, this.optionsArray, p1, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class SegmentButtonItem extends ViewPU {
    constructor(h13, i13, j13, k13 = -1, l13 = undefined, m13) {
        super(h13, j13, k13, m13);
        if (typeof l13 === "function") {
            this.paramsGenerator_ = l13;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(i13.selectedIndexes, this, "selectedIndexes");
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(i13.focusIndex, this, "focusIndex");
        this.__itemOptions = new SynchedPropertyNesedObjectPU(i13.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(i13.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(i13.property, this, "property");
        this.__index = new SynchedPropertySimpleOneWayPU(i13.index, this, "index");
        this.__marquee = new SynchedPropertySimpleOneWayPU(i13.marquee, this, "marquee");
        this.__focusedIndex = new SynchedPropertySimpleOneWayPU(i13.focusedIndex, this, "focusedIndex");
        this.__isMarqueeAndFadeout = new SynchedPropertySimpleOneWayPU(i13.isMarqueeAndFadeout, this, "isMarqueeAndFadeout");
        this.__isMarquee = new ObservedPropertySimplePU(false, this, "isMarquee");
        this.__isFadeout = new ObservedPropertySimplePU(false, this, "isFadeout");
        this.groupId = "";
        this.setInitiallyProvidedValue(i13);
        this.declareWatch("isMarqueeAndFadeout", this.onIsMarqueeAndFadeout);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(g13) {
        this.__itemOptions.set(g13.itemOptions);
        this.__options.set(g13.options);
        this.__property.set(g13.property);
        if (g13.focusedIndex === undefined) {
            this.__focusedIndex.set(-1);
        }
        if (g13.isMarquee !== undefined) {
            this.isMarquee = g13.isMarquee;
        }
        if (g13.isFadeout !== undefined) {
            this.isFadeout = g13.isFadeout;
        }
        if (g13.groupId !== undefined) {
            this.groupId = g13.groupId;
        }
    }
    updateStateVars(f13) {
        this.__itemOptions.set(f13.itemOptions);
        this.__options.set(f13.options);
        this.__property.set(f13.property);
        this.__index.reset(f13.index);
        this.__marquee.reset(f13.marquee);
        this.__focusedIndex.reset(f13.focusedIndex);
        this.__isMarqueeAndFadeout.reset(f13.isMarqueeAndFadeout);
    }
    purgeVariableDependenciesOnElmtId(e13) {
        this.__selectedIndexes.purgeDependencyOnElmtId(e13);
        this.__focusIndex.purgeDependencyOnElmtId(e13);
        this.__itemOptions.purgeDependencyOnElmtId(e13);
        this.__options.purgeDependencyOnElmtId(e13);
        this.__property.purgeDependencyOnElmtId(e13);
        this.__index.purgeDependencyOnElmtId(e13);
        this.__marquee.purgeDependencyOnElmtId(e13);
        this.__focusedIndex.purgeDependencyOnElmtId(e13);
        this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(e13);
        this.__isMarquee.purgeDependencyOnElmtId(e13);
        this.__isFadeout.purgeDependencyOnElmtId(e13);
    }
    aboutToBeDeleted() {
        this.__selectedIndexes.aboutToBeDeleted();
        this.__focusIndex.aboutToBeDeleted();
        this.__itemOptions.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__property.aboutToBeDeleted();
        this.__index.aboutToBeDeleted();
        this.__marquee.aboutToBeDeleted();
        this.__focusedIndex.aboutToBeDeleted();
        this.__isMarqueeAndFadeout.aboutToBeDeleted();
        this.__isMarquee.aboutToBeDeleted();
        this.__isFadeout.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }
    set selectedIndexes(d13) {
        this.__selectedIndexes.set(d13);
    }
    get focusIndex() {
        return this.__focusIndex.get();
    }
    set focusIndex(c13) {
        this.__focusIndex.set(c13);
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
    set index(b13) {
        this.__index.set(b13);
    }
    get marquee() {
        return this.__marquee.get();
    }
    set marquee(a13) {
        this.__marquee.set(a13);
    }
    get focusedIndex() {
        return this.__focusedIndex.get();
    }
    set focusedIndex(z12) {
        this.__focusedIndex.set(z12);
    }
    get isMarqueeAndFadeout() {
        return this.__isMarqueeAndFadeout.get();
    }
    set isMarqueeAndFadeout(y12) {
        this.__isMarqueeAndFadeout.set(y12);
    }
    get isMarquee() {
        return this.__isMarquee.get();
    }
    set isMarquee(x12) {
        this.__isMarquee.set(x12);
    }
    get isFadeout() {
        return this.__isFadeout.get();
    }
    set isFadeout(w12) {
        this.__isFadeout.set(w12);
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
    onIsMarqueeAndFadeout() {
        this.isFadeout = true;
        this.isMarquee = this.focusedIndex === this.index;
    }
    aboutToAppear() {
        this.isMarquee = true;
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
    getFillColor() {
        return this.marquee && this.focusedIndex === this.index ? segmentButtonTheme.SEGMENT_BUTTON_FOCUS_TEXT_COLOR : this.setFontColor();
    }
    getFontColor() {
        return this.marquee && this.focusedIndex === this.index ? this.options.selectedFontColor ?? segmentButtonTheme.SEGMENT_BUTTON_FOCUS_TEXT_COLOR : this.setFontColor();
    }
    initialRender() {
        this.observeComponentCreation2((u12, v12) => {
            Column.create({ space: 2 });
            Column.focusable(false);
            Column.direction(this.options.direction);
            Column.focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.getButtonPadding());
            Column.constraintSize({ minHeight: segmentButtonTheme.CONSTRAINT_SIZE_MIN_HEIGHT });
        }, Column);
        this.observeComponentCreation2((n12, o12) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s12, t12) => {
                        Image.create(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon);
                        Image.direction(this.options.direction);
                        Image.matchTextDirection(this.options.direction == Direction.Ltr ? false : true);
                        Image.size(this.options.imageSize ?? { width: 24, height: 24 });
                        Image.focusable(!this.options.showText);
                        Image.draggable(false);
                        Image.fillColor(this.getFillColor());
                    }, Image);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((f12, g12) => {
            If.create();
            if (this.options.showText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k12, l12) => {
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
    constructor(w11, x11, y11, z11 = -1, a12 = undefined, b12) {
        super(w11, y11, z11, b12);
        if (typeof a12 === "function") {
            this.paramsGenerator_ = a12;
        }
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(x11.press, this, "press");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(x11.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__options = new SynchedPropertyNesedObjectPU(x11.options, this, "options");
        this.pressIndex = 0;
        this.pressColor = segmentButtonTheme.PRESS_COLOR;
        this.setInitiallyProvidedValue(x11);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(v11) {
        this.__colorProperty.set(v11.colorProperty);
        this.__options.set(v11.options);
        if (v11.pressIndex !== undefined) {
            this.pressIndex = v11.pressIndex;
        }
        if (v11.pressColor !== undefined) {
            this.pressColor = v11.pressColor;
        }
    }
    updateStateVars(u11) {
        this.__press.reset(u11.press);
        this.__colorProperty.set(u11.colorProperty);
        this.__options.set(u11.options);
    }
    purgeVariableDependenciesOnElmtId(t11) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(t11);
        this.__press.purgeDependencyOnElmtId(t11);
        this.__colorProperty.purgeDependencyOnElmtId(t11);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(t11);
        this.__options.purgeDependencyOnElmtId(t11);
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
    set buttonItemsSize(s11) {
        this.__buttonItemsSize.set(s11);
    }
    get press() {
        return this.__press.get();
    }
    set press(r11) {
        this.__press.set(r11);
    }
    get colorProperty() {
        return this.__colorProperty.get();
    }
    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }
    set buttonBorderRadius(q11) {
        this.__buttonBorderRadius.set(q11);
    }
    get options() {
        return this.__options.get();
    }
    initialRender() {
        this.observeComponentCreation2((o11, p11) => {
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
    constructor(s10, t10, u10, v10 = -1, w10 = undefined, x10) {
        super(s10, u10, v10, x10);
        if (typeof w10 === "function") {
            this.paramsGenerator_ = w10;
        }
        this.__focusedIndex = new ObservedPropertySimplePU(-1, this, "focusedIndex");
        this.__focusIdx = new ObservedPropertyObjectPU(null, this, "focusIdx");
        this.__optionsArray = new SynchedPropertyNesedObjectPU(t10.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(t10.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(t10.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = this.initializeConsume("componentSize", "componentSize");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__buttonItemsPosition = this.initializeConsume("buttonItemsPosition", "buttonItemsPosition");
        this.__focusIndex = this.initializeConsume("focusIndex", "focusIndex");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonItemProperty = this.initializeConsume("buttonItemProperty", "buttonItemProperty");
        this.__buttonItemsSelected = this.initializeConsume("buttonItemsSelected", "buttonItemsSelected");
        this.__pressArray = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (l11, m11) => false), this, "pressArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (j11, k11) => new HoverColorProperty()), this, "hoverColorArray");
        this.__buttonWidth = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (h11, i11) => 0), this, "buttonWidth");
        this.__buttonHeight = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (f11, g11) => 0), this, "buttonHeight");
        this.__marquee = new ObservedPropertySimplePU(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_marquee'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value === 0, this, "marquee");
        this.__isMarqueeAndFadeout = new ObservedPropertySimplePU(false, this, "isMarqueeAndFadeout");
        this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (h1, o1) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.segmentFocusControl = LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_focus_control'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value === 1;
        this.setInitiallyProvidedValue(t10);
        this.declareWatch("focusedIndex", this.onFocusIndex);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r10) {
        if (r10.focusedIndex !== undefined) {
            this.focusedIndex = r10.focusedIndex;
        }
        if (r10.focusIdx !== undefined) {
            this.focusIdx = r10.focusIdx;
        }
        this.__optionsArray.set(r10.optionsArray);
        this.__options.set(r10.options);
        if (r10.pressArray !== undefined) {
            this.pressArray = r10.pressArray;
        }
        if (r10.hoverColorArray !== undefined) {
            this.hoverColorArray = r10.hoverColorArray;
        }
        if (r10.buttonWidth !== undefined) {
            this.buttonWidth = r10.buttonWidth;
        }
        if (r10.buttonHeight !== undefined) {
            this.buttonHeight = r10.buttonHeight;
        }
        if (r10.marquee !== undefined) {
            this.marquee = r10.marquee;
        }
        if (r10.isMarqueeAndFadeout !== undefined) {
            this.isMarqueeAndFadeout = r10.isMarqueeAndFadeout;
        }
        if (r10.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = r10.buttonItemsRealHeight;
        }
        if (r10.groupId !== undefined) {
            this.groupId = r10.groupId;
        }
        if (r10.segmentFocusControl !== undefined) {
            this.segmentFocusControl = r10.segmentFocusControl;
        }
    }
    updateStateVars(q10) {
        this.__optionsArray.set(q10.optionsArray);
        this.__options.set(q10.options);
    }
    purgeVariableDependenciesOnElmtId(p10) {
        this.__focusedIndex.purgeDependencyOnElmtId(p10);
        this.__focusIdx.purgeDependencyOnElmtId(p10);
        this.__optionsArray.purgeDependencyOnElmtId(p10);
        this.__options.purgeDependencyOnElmtId(p10);
        this.__selectedIndexes.purgeDependencyOnElmtId(p10);
        this.__componentSize.purgeDependencyOnElmtId(p10);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(p10);
        this.__buttonItemsSize.purgeDependencyOnElmtId(p10);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(p10);
        this.__focusIndex.purgeDependencyOnElmtId(p10);
        this.__zoomScaleArray.purgeDependencyOnElmtId(p10);
        this.__buttonItemProperty.purgeDependencyOnElmtId(p10);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(p10);
        this.__pressArray.purgeDependencyOnElmtId(p10);
        this.__hoverColorArray.purgeDependencyOnElmtId(p10);
        this.__buttonWidth.purgeDependencyOnElmtId(p10);
        this.__buttonHeight.purgeDependencyOnElmtId(p10);
        this.__marquee.purgeDependencyOnElmtId(p10);
        this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(p10);
    }
    aboutToBeDeleted() {
        this.__focusedIndex.aboutToBeDeleted();
        this.__focusIdx.aboutToBeDeleted();
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
    get focusedIndex() {
        return this.__focusedIndex.get();
    }
    set focusedIndex(o10) {
        this.__focusedIndex.set(o10);
    }
    get focusIdx() {
        return this.__focusIdx.get();
    }
    set focusIdx(n10) {
        this.__focusIdx.set(n10);
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
    set selectedIndexes(m10) {
        this.__selectedIndexes.set(m10);
    }
    get componentSize() {
        return this.__componentSize.get();
    }
    set componentSize(l10) {
        this.__componentSize.set(l10);
    }
    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }
    set buttonBorderRadius(k10) {
        this.__buttonBorderRadius.set(k10);
    }
    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }
    set buttonItemsSize(j10) {
        this.__buttonItemsSize.set(j10);
    }
    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }
    set buttonItemsPosition(i10) {
        this.__buttonItemsPosition.set(i10);
    }
    get focusIndex() {
        return this.__focusIndex.get();
    }
    set focusIndex(h10) {
        this.__focusIndex.set(h10);
    }
    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }
    set zoomScaleArray(g10) {
        this.__zoomScaleArray.set(g10);
    }
    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }
    set buttonItemProperty(f10) {
        this.__buttonItemProperty.set(f10);
    }
    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }
    set buttonItemsSelected(e10) {
        this.__buttonItemsSelected.set(e10);
    }
    get pressArray() {
        return this.__pressArray.get();
    }
    set pressArray(d10) {
        this.__pressArray.set(d10);
    }
    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }
    set hoverColorArray(c10) {
        this.__hoverColorArray.set(c10);
    }
    get buttonWidth() {
        return this.__buttonWidth.get();
    }
    set buttonWidth(b10) {
        this.__buttonWidth.set(b10);
    }
    get buttonHeight() {
        return this.__buttonHeight.get();
    }
    set buttonHeight(a10) {
        this.__buttonHeight.set(a10);
    }
    get marquee() {
        return this.__marquee.get();
    }
    set marquee(z9) {
        this.__marquee.set(z9);
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
        this.isMarqueeAndFadeout = this.marquee ? !this.isMarqueeAndFadeout : false;
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
                    }, undefined, i8, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton2.ets", line: 822, col: 7 });
                    ViewPU.create(k8);
                    let g1 = () => {
                        return {
                            pressIndex: o7,
                            colorProperty: this.hoverColorArray[o7],
                            press: this.pressArray[o7],
                            options: this.options
                        };
                    };
                    k8.paramsGenerator_ = g1;
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
                        focusedIndex: this.focusedIndex,
                        selectedIndexes: this.__selectedIndexes,
                        focusIndex: this.__focusIndex,
                        index: o7,
                        itemOptions: p7,
                        options: this.options,
                        property: this.buttonItemProperty[o7],
                        groupId: this.groupId,
                        marquee: this.marquee
                    }, undefined, u7, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton2.ets", line: 828, col: 7 });
                    ViewPU.create(w7);
                    let x = () => {
                        return {
                            isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                            focusedIndex: this.focusedIndex,
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
                    w7.paramsGenerator_ = x;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(u7, {
                        isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                        focusedIndex: this.focusedIndex,
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
                                            Stack.focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === w5 ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
                                            Stack.onFocus(() => {
                                                this.focusedIndex = w5;
                                                this.focusIndex = w5;
                                                this.marquee = segmentButtonTheme.SEGMENT_MARQUEE === 0;
                                                if (this.marquee) {
                                                    this.hoverColorArray[w5].hoverColor = { "id": -1, "type": 10001, params: ['sys.color.segment_button_focus_backboard_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                                }
                                            });
                                            Stack.onBlur(() => {
                                                this.focusedIndex = -1;
                                                this.hoverColorArray[w5].hoverColor = Color.Transparent;
                                            });
                                            Stack.onTouch((e7) => {
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
                                                if (b7) {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        if (this.marquee && this.focusedIndex === w5) {
                                                            this.hoverColorArray[w5].hoverColor = { "id": -1, "type": 10001, params: ['sys.color.segment_button_focus_backboard_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                                        }
                                                        else {
                                                            this.hoverColorArray[w5].hoverColor = (segmentButtonTheme.HOVER_COLOR);
                                                        }
                                                    });
                                                }
                                                else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        if (this.marquee && this.focusedIndex === w5) {
                                                            this.hoverColorArray[w5].hoverColor = { "id": -1, "type": 10001, params: ['sys.color.segment_button_focus_backboard_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                                        }
                                                        else {
                                                            this.hoverColorArray[w5].hoverColor = Color.Transparent;
                                                        }
                                                    });
                                                }
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
                                            }, undefined, b2, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton2.ets", line: 1134, col: 11 });
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
                                    Stack.borderRadius(this.options.iconTextBackgroundRadius ?? this.componentSize.height / LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_normal_border_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value);
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
                                            }, undefined, l1, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton2.ets", line: 1148, col: 13 });
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
                                            }, undefined, d1, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton2.ets", line: 1154, col: 13 });
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
                                }, undefined, t, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton2.ets", line: 1168, col: 9 });
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

export default {SegmentButton, SegmentButtonOptions, SegmentButtonItemOptionsArray, SegmentButtonItemOptions};
