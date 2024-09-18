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

var __decorate = (this && this.__decorate) || function (z19, a20, b20, c20) {
    var d20 = arguments.length, e20 = d20 < 3 ? a20 : c20 === null ? c20 = Object.getOwnPropertyDescriptor(a20, b20) : c20, f20;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        e20 = Reflect.decorate(z19, a20, b20, c20);
    else
        for (var g20 = z19.length - 1; g20 >= 0; g20--)
            if (f20 = z19[g20])
                e20 = (d20 < 3 ? f20(e20) : d20 > 3 ? f20(a20, b20, e20) : f20(a20, b20)) || e20;
    return d20 > 3 && e20 && Object.defineProperty(a20, b20, e20), e20;
};
var SegmentButtonItemOptionsArray_1, SegmentButtonOptions_1;
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const curves = globalThis.requireNativeModule("ohos.curves");
const KeyCode = globalThis.requireNapi("multimodalInput.keyCode").KeyCode;
const util = globalThis.requireNapi("util");
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const I18n = requireNapi('i18n');

const MIN_ITEM_COUNT = 2;
const MAX_ITEM_COUNT = 5;
function verifyResource(t19, u19, v19) {
    if (t19 && t19.params && Array.isArray(t19.params) &&
    t19.params[0] && t19.params[0].includes('.') &&
        t19.params[0].split('.').length > 2) {
        try {
            let x19 = v19.resourceManager.getNumberByName((t19.params[0]).split('.')[2]);
            return x19;
        }
        catch (w19) {
            return u19;
        }
    }
    return u19;
}
const segmentButtonTheme = {
    FONT_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_unselected_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    TAB_SELECTED_FONT_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_checked_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    CAPSULE_SELECTED_FONT_COLOR: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_foreground_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    FONT_SIZE: { "id": -1, "type": 10002, params: ['sys.float.segment_button_unselected_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    SELECTED_FONT_SIZE: { "id": -1, "type": 10002, params: ['sys.float.segment_button_checked_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    BACKGROUND_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_backboard_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    TAB_SELECTED_BACKGROUND_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_checked_foreground_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    CAPSULE_SELECTED_BACKGROUND_COLOR: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    FOCUS_BORDER_COLOR: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    HOVER_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    PRESS_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_color_Press'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    BACKGROUND_BLUR_STYLE: { "id": -1, "type": 10002, params: ['sys.float.segment_button_background_blur_style'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    SEGMENT_BUTTON_PADDING: { "id": -1, "type": 10002, params: ['sys.float.segment_button_baseplate_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    CONSTRAINT_SIZE_MIN_HEIGHT: { "id": -1, "type": 10002, params: ['sys.float.segment_button_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    SEGMENT_BUTTON_MIN_FONT_SIZE: { "id": -1, "type": 10002, params: ['sys.float.segment_button_min_font_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    SEGMENT_BUTTON_NORMAL_BORDER_RADIUS: { "id": -1, "type": 10002, params: ['sys.float.segment_button_normal_border_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    SEGMENT_BUTTON_PADDING_NUMBER: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_baseplate_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value,
    SEGMENT_MARQUEE: { "id": -1, "type": 10002, params: ['sys.float.segment_marquee'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    SEGMENT_BUTTON_FOCUS_TEXT_COLOR: { "id": -1, "type": 10001, params: ['sys.color.segment_button_focus_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
};
function nearEqual(r19, s19) {
    return Math.abs(r19 - s19) < 0.001;
}
let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(q19) {
        this.icon = q19.icon;
        this.selectedIcon = q19.selectedIcon;
        this.text = q19.text;
    }
};
SegmentButtonItemOptions = __decorate([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends Array {
    constructor(n19) {
        super(typeof n19 === 'number' ? n19 : 0);
        this.changeStartIndex = void 0;
        this.deleteCount = void 0;
        this.addLength = void 0;
        if (typeof n19 !== 'number' && n19 !== void 0) {
            super.push(...n19.map((p19) => new SegmentButtonItemOptions(p19)));
        }
    }
    push(...k19) {
        if (this.length + k19.length > MAX_ITEM_COUNT) {
            console.warn('Exceeded the maximum number of elements (5).');
            return this.length;
        }
        this.changeStartIndex = this.length;
        this.deleteCount = 0;
        this.addLength = k19.length;
        return super.push(...k19.map((m19) => new SegmentButtonItemOptions(m19)));
    }
    pop() {
        if (this.length <= MIN_ITEM_COUNT) {
            console.warn('Below the minimum number of elements (2).');
            return void 0;
        }
        this.changeStartIndex = this.length - 1;
        this.deleteCount = 1;
        this.addLength = 0;
        return super.pop();
    }
    shift() {
        if (this.length <= MIN_ITEM_COUNT) {
            console.warn('Below the minimum number of elements (2).');
            return void 0;
        }
        this.changeStartIndex = 0;
        this.deleteCount = 1;
        this.addLength = 0;
        return super.shift();
    }
    unshift(...h19) {
        if (this.length + h19.length > MAX_ITEM_COUNT) {
            console.warn('Exceeded the maximum number of elements (5).');
            return this.length;
        }
        if (h19.length > 0) {
            this.changeStartIndex = 0;
            this.deleteCount = 0;
            this.addLength = h19.length;
        }
        return super.unshift(...h19.map((j19) => new SegmentButtonItemOptions(j19)));
    }
    splice(d19, e19, ...f19) {
        let g19 = (this.length - e19) < 0 ? 0 : (this.length - e19);
        g19 += f19.length;
        if (g19 < MIN_ITEM_COUNT) {
            console.warn('Below the minimum number of elements (2).');
            return [];
        }
        if (g19 > MAX_ITEM_COUNT) {
            console.warn('Exceeded the maximum number of elements (5).');
            return [];
        }
        this.changeStartIndex = d19;
        this.deleteCount = e19;
        this.addLength = f19.length;
        return super.splice(d19, e19, ...f19);
    }
    static create(c19) {
        return new SegmentButtonItemOptionsArray_1(c19);
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
    set buttons(b19) {
        if (this._buttons !== void 0 && this._buttons !== b19) {
            this.onButtonsChange?.();
        }
        this._buttons = b19;
    }
    constructor(y18) {
        this.multiply = false;
        this.showText = false;
        this.showIcon = false;
        this._buttons = void 0;
        this.fontColor = y18.fontColor ?? segmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = y18.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = y18.fontSize ?? segmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = y18.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = y18.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = y18.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = y18.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = y18.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = y18.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = y18.buttonPadding;
        this.textPadding = y18.textPadding;
        this.type = y18.type;
        this.backgroundBlurStyle = y18.backgroundBlurStyle ?? verifyResource(segmentButtonTheme.BACKGROUND_BLUR_STYLE, 0, getContext(this));
        this.localizedTextPadding = y18.localizedTextPadding;
        this.localizedButtonPadding = y18.localizedButtonPadding;
        this.direction = y18.direction ?? Direction.Auto;
        this.buttons = new SegmentButtonItemOptionsArray(y18.buttons);
        if (this.type === 'capsule') {
            this.multiply = y18.multiply ?? false;
            this.buttons.forEach(a19 => {
                this.showText ||= a19.text !== void 0;
                this.showIcon ||= a19.icon !== void 0 || a19.selectedIcon !== void 0;
            });
            if (this.showText && this.showIcon) {
                this.iconTextRadius = 12;
                this.iconTextBackgroundRadius = 14;
            }
            this.selectedFontColor = y18.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = y18.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
        else {
            this.showText = true;
        }
        this.componentPadding = this.multiply ? 0 : 2;
    }
    static tab(x18) {
        return new SegmentButtonOptions_1({
            type: 'tab',
            buttons: x18.buttons,
            fontColor: x18.fontColor,
            selectedFontColor: x18.selectedFontColor,
            fontSize: x18.fontSize,
            selectedFontSize: x18.selectedFontSize,
            fontWeight: x18.fontWeight,
            selectedFontWeight: x18.selectedFontWeight,
            backgroundColor: x18.backgroundColor,
            selectedBackgroundColor: x18.selectedBackgroundColor,
            imageSize: x18.imageSize,
            buttonPadding: x18.buttonPadding,
            textPadding: x18.textPadding,
            localizedTextPadding: x18.localizedTextPadding,
            localizedButtonPadding: x18.localizedButtonPadding,
            backgroundBlurStyle: x18.backgroundBlurStyle,
            direction: x18.direction
        });
    }
    static capsule(w18) {
        return new SegmentButtonOptions_1({
            type: 'capsule',
            buttons: w18.buttons,
            multiply: w18.multiply,
            fontColor: w18.fontColor,
            selectedFontColor: w18.selectedFontColor,
            fontSize: w18.fontSize,
            selectedFontSize: w18.selectedFontSize,
            fontWeight: w18.fontWeight,
            selectedFontWeight: w18.selectedFontWeight,
            backgroundColor: w18.backgroundColor,
            selectedBackgroundColor: w18.selectedBackgroundColor,
            imageSize: w18.imageSize,
            buttonPadding: w18.buttonPadding,
            textPadding: w18.textPadding,
            localizedTextPadding: w18.localizedTextPadding,
            localizedButtonPadding: w18.localizedButtonPadding,
            backgroundBlurStyle: w18.backgroundBlurStyle,
            direction: w18.direction
        });
    }
};
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([
    Observed
], SegmentButtonOptions);
export { SegmentButtonOptions };
class MultiSelectBackground extends ViewPU {
    constructor(q18, r18, s18, t18 = -1, u18 = undefined, v18) {
        super(q18, s18, t18, v18);
        if (typeof u18 === "function") {
            this.paramsGenerator_ = u18;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(r18.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(r18.options, this, "options");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(r18);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(p18) {
        this.__optionsArray.set(p18.optionsArray);
        this.__options.set(p18.options);
    }
    updateStateVars(o18) {
        this.__optionsArray.set(o18.optionsArray);
        this.__options.set(o18.options);
    }
    purgeVariableDependenciesOnElmtId(n18) {
        this.__optionsArray.purgeDependencyOnElmtId(n18);
        this.__options.purgeDependencyOnElmtId(n18);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(n18);
        this.__buttonItemsSize.purgeDependencyOnElmtId(n18);
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
    set buttonBorderRadius(m18) {
        this.__buttonBorderRadius.set(m18);
    }
    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }
    set buttonItemsSize(l18) {
        this.__buttonItemsSize.set(l18);
    }
    initialRender() {
        this.observeComponentCreation2((j18, k18) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((u17, v17) => {
            ForEach.create();
            const s = (y17, z17) => {
                const a18 = y17;
                this.observeComponentCreation2((c18, d18) => {
                    If.create();
                    if (z17 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((h18, i18) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[z17].height);
                                Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[z17]);
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
            this.forEachUpdateFunction(u17, this.optionsArray, s, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class SelectItem extends ViewPU {
    constructor(m17, n17, o17, p17 = -1, q17 = undefined, r17) {
        super(m17, o17, p17, r17);
        if (typeof q17 === "function") {
            this.paramsGenerator_ = q17;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(n17.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(n17.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(n17.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__selectedItemPosition = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(n17);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l17) {
        this.__optionsArray.set(l17.optionsArray);
        this.__options.set(l17.options);
    }
    updateStateVars(k17) {
        this.__optionsArray.set(k17.optionsArray);
        this.__options.set(k17.options);
    }
    purgeVariableDependenciesOnElmtId(j17) {
        this.__optionsArray.purgeDependencyOnElmtId(j17);
        this.__options.purgeDependencyOnElmtId(j17);
        this.__selectedIndexes.purgeDependencyOnElmtId(j17);
        this.__buttonItemsSize.purgeDependencyOnElmtId(j17);
        this.__selectedItemPosition.purgeDependencyOnElmtId(j17);
        this.__zoomScaleArray.purgeDependencyOnElmtId(j17);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(j17);
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
    set selectedIndexes(i17) {
        this.__selectedIndexes.set(i17);
    }
    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }
    set buttonItemsSize(h17) {
        this.__buttonItemsSize.set(h17);
    }
    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }
    set selectedItemPosition(g17) {
        this.__selectedItemPosition.set(g17);
    }
    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }
    set zoomScaleArray(f17) {
        this.__zoomScaleArray.set(f17);
    }
    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }
    set buttonBorderRadius(e17) {
        this.__buttonBorderRadius.set(e17);
    }
    initialRender() {
        this.observeComponentCreation2((x16, y16) => {
            If.create();
            if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c17, d17) => {
                        Stack.create();
                        Stack.direction(this.options.direction);
                        Stack.borderRadius(this.buttonBorderRadius[this.selectedIndexes[0]]);
                        Stack.size(this.buttonItemsSize[this.selectedIndexes[0]]);
                        Stack.backgroundColor(this.options.selectedBackgroundColor ??
                            (this.options.type === 'tab' ? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR :
                            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR));
                        Stack.position(ObservedObject.GetRawObject(this.selectedItemPosition));
                        Stack.scale({ x: this.zoomScaleArray[this.selectedIndexes[0]], y: this.zoomScaleArray[this.selectedIndexes[0]] });
                        Stack.shadow(verifyResource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_shadow'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, 0, getContext(this)));
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
    constructor(n16, o16, p16, q16 = -1, r16 = undefined, s16) {
        super(n16, p16, q16, s16);
        if (typeof r16 === "function") {
            this.paramsGenerator_ = r16;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(o16.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(o16.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(o16.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__multiColor = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (u16, v16) => Color.Transparent), this, "multiColor");
        this.setInitiallyProvidedValue(o16);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(m16) {
        this.__optionsArray.set(m16.optionsArray);
        this.__options.set(m16.options);
        if (m16.multiColor !== undefined) {
            this.multiColor = m16.multiColor;
        }
    }
    updateStateVars(l16) {
        this.__optionsArray.set(l16.optionsArray);
        this.__options.set(l16.options);
    }
    purgeVariableDependenciesOnElmtId(k16) {
        this.__optionsArray.purgeDependencyOnElmtId(k16);
        this.__options.purgeDependencyOnElmtId(k16);
        this.__selectedIndexes.purgeDependencyOnElmtId(k16);
        this.__buttonItemsSize.purgeDependencyOnElmtId(k16);
        this.__zoomScaleArray.purgeDependencyOnElmtId(k16);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(k16);
        this.__multiColor.purgeDependencyOnElmtId(k16);
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
    set selectedIndexes(j16) {
        this.__selectedIndexes.set(j16);
    }
    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }
    set buttonItemsSize(i16) {
        this.__buttonItemsSize.set(i16);
    }
    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }
    set zoomScaleArray(h16) {
        this.__zoomScaleArray.set(h16);
    }
    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }
    set buttonBorderRadius(g16) {
        this.__buttonBorderRadius.set(g16);
    }
    get multiColor() {
        return this.__multiColor.get();
    }
    set multiColor(f16) {
        this.__multiColor.set(f16);
    }
    onOptionsChange() {
        for (let e16 = 0; e16 < this.selectedIndexes.length; e16++) {
            this.multiColor[this.selectedIndexes[e16]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }
    onSelectedChange() {
        for (let d16 = 0; d16 < MAX_ITEM_COUNT; d16++) {
            this.multiColor[d16] = Color.Transparent;
        }
        for (let c16 = 0; c16 < this.selectedIndexes.length; c16++) {
            this.multiColor[this.selectedIndexes[c16]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }
    aboutToAppear() {
        for (let b16 = 0; b16 < this.selectedIndexes.length; b16++) {
            this.multiColor[this.selectedIndexes[b16]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }
    initialRender() {
        this.observeComponentCreation2((z15, a16) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((k15, l15) => {
            ForEach.create();
            const r = (o15, p15) => {
                const q15 = o15;
                this.observeComponentCreation2((s15, t15) => {
                    If.create();
                    if (p15 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((x15, y15) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.width(this.buttonItemsSize[p15].width);
                                Stack.height(this.buttonItemsSize[p15].height);
                                Stack.backgroundColor(this.multiColor[p15]);
                                Stack.borderRadius(this.buttonBorderRadius[p15]);
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
            this.forEachUpdateFunction(k15, this.optionsArray, r, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class SegmentButtonItem extends ViewPU {
    constructor(c15, d15, e15, f15 = -1, g15 = undefined, h15) {
        super(c15, e15, f15, h15);
        if (typeof g15 === "function") {
            this.paramsGenerator_ = g15;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(d15.selectedIndexes, this, "selectedIndexes");
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(d15.focusIndex, this, "focusIndex");
        this.__itemOptions = new SynchedPropertyNesedObjectPU(d15.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(d15.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(d15.property, this, "property");
        this.__index = new SynchedPropertySimpleOneWayPU(d15.index, this, "index");
        this.__marquee = new SynchedPropertySimpleOneWayPU(d15.marquee, this, "marquee");
        this.__isMarqueeAndFadeout = new SynchedPropertySimpleOneWayPU(d15.isMarqueeAndFadeout, this, "isMarqueeAndFadeout");
        this.__isMarquee = new ObservedPropertySimplePU(false, this, "isMarquee");
        this.__isFadeout = new ObservedPropertySimplePU(false, this, "isFadeout");
        this.groupId = '';
        this.setInitiallyProvidedValue(d15);
        this.declareWatch("focusIndex", this.onFocusIndex);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(b15) {
        this.__itemOptions.set(b15.itemOptions);
        this.__options.set(b15.options);
        this.__property.set(b15.property);
        if (b15.isMarquee !== undefined) {
            this.isMarquee = b15.isMarquee;
        }
        if (b15.isFadeout !== undefined) {
            this.isFadeout = b15.isFadeout;
        }
        if (b15.groupId !== undefined) {
            this.groupId = b15.groupId;
        }
    }
    updateStateVars(a15) {
        this.__itemOptions.set(a15.itemOptions);
        this.__options.set(a15.options);
        this.__property.set(a15.property);
        this.__index.reset(a15.index);
        this.__marquee.reset(a15.marquee);
        this.__isMarqueeAndFadeout.reset(a15.isMarqueeAndFadeout);
    }
    purgeVariableDependenciesOnElmtId(z14) {
        this.__selectedIndexes.purgeDependencyOnElmtId(z14);
        this.__focusIndex.purgeDependencyOnElmtId(z14);
        this.__itemOptions.purgeDependencyOnElmtId(z14);
        this.__options.purgeDependencyOnElmtId(z14);
        this.__property.purgeDependencyOnElmtId(z14);
        this.__index.purgeDependencyOnElmtId(z14);
        this.__marquee.purgeDependencyOnElmtId(z14);
        this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(z14);
        this.__isMarquee.purgeDependencyOnElmtId(z14);
        this.__isFadeout.purgeDependencyOnElmtId(z14);
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
    set selectedIndexes(y14) {
        this.__selectedIndexes.set(y14);
    }
    get focusIndex() {
        return this.__focusIndex.get();
    }
    set focusIndex(x14) {
        this.__focusIndex.set(x14);
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
    set index(w14) {
        this.__index.set(w14);
    }
    get marquee() {
        return this.__marquee.get();
    }
    set marquee(v14) {
        this.__marquee.set(v14);
    }
    get isMarqueeAndFadeout() {
        return this.__isMarqueeAndFadeout.get();
    }
    set isMarqueeAndFadeout(u14) {
        this.__isMarqueeAndFadeout.set(u14);
    }
    get isMarquee() {
        return this.__isMarquee.get();
    }
    set isMarquee(t14) {
        this.__isMarquee.set(t14);
    }
    get isFadeout() {
        return this.__isFadeout.get();
    }
    set isFadeout(s14) {
        this.__isFadeout.set(s14);
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
        let n14 = (typeof this.options.selectedFontColor) === 'object';
        let o14 = false;
        if (n14) {
            let p14 = segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR.id;
            let q14 = segmentButtonTheme.TAB_SELECTED_FONT_COLOR.id;
            let r14 = this.options.selectedFontColor.id;
            o14 = this.options.type === 'tab' ? r14 === q14 :
                r14 === p14;
        }
        if (this.property.isSelected && !o14) {
            return this.options.selectedFontColor;
        }
        else {
            return this.isMarquee ? segmentButtonTheme.SEGMENT_BUTTON_FOCUS_TEXT_COLOR : this.setFontColor();
        }
    }
    initialRender() {
        this.observeComponentCreation2((l14, m14) => {
            Column.create({ space: 2 });
            Column.focusable(false);
            Column.direction(this.options.direction);
            Column.focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.getButtonPadding());
            Column.constraintSize({ minHeight: segmentButtonTheme.CONSTRAINT_SIZE_MIN_HEIGHT });
        }, Column);
        this.observeComponentCreation2((e14, f14) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j14, k14) => {
                        Image.create(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon);
                        Image.direction(this.options.direction);
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
        this.observeComponentCreation2((w13, x13) => {
            If.create();
            if (this.options.showText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b14, c14) => {
                        Text.create(this.itemOptions.text);
                        Text.direction(this.options.direction);
                        Text.fontColor(this.getFontColor());
                        Text.fontWeight(this.property.fontWeight);
                        Text.fontSize(this.property.fontSize);
                        Text.minFontSize(this.property.minFontSize);
                        Text.maxFontSize(this.property.fontSize);
                        Text.textOverflow({ overflow: this.marquee ? TextOverflow.MARQUEE : TextOverflow.Ellipsis });
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
    constructor(n13, o13, p13, q13 = -1, r13 = undefined, s13) {
        super(n13, p13, q13, s13);
        if (typeof r13 === "function") {
            this.paramsGenerator_ = r13;
        }
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(o13.press, this, "press");
        this.__hover = new SynchedPropertySimpleOneWayPU(o13.hover, this, "hover");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(o13.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__options = new SynchedPropertyNesedObjectPU(o13.options, this, "options");
        this.pressIndex = 0;
        this.pressColor = segmentButtonTheme.PRESS_COLOR;
        this.setInitiallyProvidedValue(o13);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(m13) {
        this.__colorProperty.set(m13.colorProperty);
        this.__options.set(m13.options);
        if (m13.pressIndex !== undefined) {
            this.pressIndex = m13.pressIndex;
        }
        if (m13.pressColor !== undefined) {
            this.pressColor = m13.pressColor;
        }
    }
    updateStateVars(l13) {
        this.__press.reset(l13.press);
        this.__hover.reset(l13.hover);
        this.__colorProperty.set(l13.colorProperty);
        this.__options.set(l13.options);
    }
    purgeVariableDependenciesOnElmtId(k13) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(k13);
        this.__press.purgeDependencyOnElmtId(k13);
        this.__hover.purgeDependencyOnElmtId(k13);
        this.__colorProperty.purgeDependencyOnElmtId(k13);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(k13);
        this.__options.purgeDependencyOnElmtId(k13);
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
    set buttonItemsSize(j13) {
        this.__buttonItemsSize.set(j13);
    }
    get press() {
        return this.__press.get();
    }
    set press(i13) {
        this.__press.set(i13);
    }
    get hover() {
        return this.__hover.get();
    }
    set hover(h13) {
        this.__hover.set(h13);
    }
    get colorProperty() {
        return this.__colorProperty.get();
    }
    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }
    set buttonBorderRadius(g13) {
        this.__buttonBorderRadius.set(g13);
    }
    get options() {
        return this.__options.get();
    }
    initialRender() {
        this.observeComponentCreation2((e13, f13) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.size(this.buttonItemsSize[this.pressIndex]);
            Stack.backgroundColor(this.press && this.hover ? this.pressColor : this.colorProperty.hoverColor);
            Stack.borderRadius(this.buttonBorderRadius[this.pressIndex]);
        }, Stack);
        Stack.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class SegmentButtonItemArrayComponent extends ViewPU {
    constructor(o12, p12, q12, r12 = -1, s12 = undefined, t12) {
        super(o12, q12, r12, t12);
        if (typeof s12 === "function") {
            this.paramsGenerator_ = s12;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(p12.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(p12.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(p12.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = this.initializeConsume("componentSize", "componentSize");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__buttonItemsPosition = this.initializeConsume("buttonItemsPosition", "buttonItemsPosition");
        this.__focusIndex = this.initializeConsume("focusIndex", "focusIndex");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonItemProperty = this.initializeConsume("buttonItemProperty", "buttonItemProperty");
        this.__buttonItemsSelected = this.initializeConsume("buttonItemsSelected", "buttonItemsSelected");
        this.__pressArray = new SynchedPropertyObjectTwoWayPU(p12.pressArray, this, "pressArray");
        this.__hoverArray = new SynchedPropertyObjectTwoWayPU(p12.hoverArray, this, "hoverArray");
        this.__hoverColorArray = new SynchedPropertyObjectTwoWayPU(p12.hoverColorArray, this, "hoverColorArray");
        this.__buttonWidth = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (b13, c13) => 0), this, "buttonWidth");
        this.__buttonHeight = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (z12, a13) => 0), this, "buttonHeight");
        this.__marquee = new ObservedPropertySimplePU(verifyResource(segmentButtonTheme.SEGMENT_MARQUEE, 1, getContext(this)) === 0, this, "marquee");
        this.__isMarqueeAndFadeout = new ObservedPropertySimplePU(false, this, "isMarqueeAndFadeout");
        this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (x12, y12) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.segmentFocusControl = verifyResource({ "id": -1, "type": 10002, params: ['sys.float.segment_focus_control'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, 1, getContext(this)) === 1;
        this.setInitiallyProvidedValue(p12);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.declareWatch("focusIndex", this.onFocusIndex);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(n12) {
        this.__optionsArray.set(n12.optionsArray);
        this.__options.set(n12.options);
        if (n12.buttonWidth !== undefined) {
            this.buttonWidth = n12.buttonWidth;
        }
        if (n12.buttonHeight !== undefined) {
            this.buttonHeight = n12.buttonHeight;
        }
        if (n12.marquee !== undefined) {
            this.marquee = n12.marquee;
        }
        if (n12.isMarqueeAndFadeout !== undefined) {
            this.isMarqueeAndFadeout = n12.isMarqueeAndFadeout;
        }
        if (n12.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = n12.buttonItemsRealHeight;
        }
        if (n12.groupId !== undefined) {
            this.groupId = n12.groupId;
        }
        if (n12.segmentFocusControl !== undefined) {
            this.segmentFocusControl = n12.segmentFocusControl;
        }
    }
    updateStateVars(m12) {
        this.__optionsArray.set(m12.optionsArray);
        this.__options.set(m12.options);
    }
    purgeVariableDependenciesOnElmtId(l12) {
        this.__optionsArray.purgeDependencyOnElmtId(l12);
        this.__options.purgeDependencyOnElmtId(l12);
        this.__selectedIndexes.purgeDependencyOnElmtId(l12);
        this.__componentSize.purgeDependencyOnElmtId(l12);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(l12);
        this.__buttonItemsSize.purgeDependencyOnElmtId(l12);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(l12);
        this.__focusIndex.purgeDependencyOnElmtId(l12);
        this.__zoomScaleArray.purgeDependencyOnElmtId(l12);
        this.__buttonItemProperty.purgeDependencyOnElmtId(l12);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(l12);
        this.__pressArray.purgeDependencyOnElmtId(l12);
        this.__hoverArray.purgeDependencyOnElmtId(l12);
        this.__hoverColorArray.purgeDependencyOnElmtId(l12);
        this.__buttonWidth.purgeDependencyOnElmtId(l12);
        this.__buttonHeight.purgeDependencyOnElmtId(l12);
        this.__marquee.purgeDependencyOnElmtId(l12);
        this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(l12);
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
    set selectedIndexes(k12) {
        this.__selectedIndexes.set(k12);
    }
    get componentSize() {
        return this.__componentSize.get();
    }
    set componentSize(j12) {
        this.__componentSize.set(j12);
    }
    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }
    set buttonBorderRadius(i12) {
        this.__buttonBorderRadius.set(i12);
    }
    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }
    set buttonItemsSize(h12) {
        this.__buttonItemsSize.set(h12);
    }
    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }
    set buttonItemsPosition(g12) {
        this.__buttonItemsPosition.set(g12);
    }
    get focusIndex() {
        return this.__focusIndex.get();
    }
    set focusIndex(f12) {
        this.__focusIndex.set(f12);
    }
    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }
    set zoomScaleArray(e12) {
        this.__zoomScaleArray.set(e12);
    }
    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }
    set buttonItemProperty(d12) {
        this.__buttonItemProperty.set(d12);
    }
    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }
    set buttonItemsSelected(c12) {
        this.__buttonItemsSelected.set(c12);
    }
    get pressArray() {
        return this.__pressArray.get();
    }
    set pressArray(b12) {
        this.__pressArray.set(b12);
    }
    get hoverArray() {
        return this.__hoverArray.get();
    }
    set hoverArray(a12) {
        this.__hoverArray.set(a12);
    }
    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }
    set hoverColorArray(z11) {
        this.__hoverColorArray.set(z11);
    }
    get buttonWidth() {
        return this.__buttonWidth.get();
    }
    set buttonWidth(y11) {
        this.__buttonWidth.set(y11);
    }
    get buttonHeight() {
        return this.__buttonHeight.get();
    }
    set buttonHeight(x11) {
        this.__buttonHeight.set(x11);
    }
    get marquee() {
        return this.__marquee.get();
    }
    set marquee(w11) {
        this.__marquee.set(w11);
    }
    get isMarqueeAndFadeout() {
        return this.__isMarqueeAndFadeout.get();
    }
    set isMarqueeAndFadeout(v11) {
        this.__isMarqueeAndFadeout.set(v11);
    }
    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((t11, u11) => {
            this.buttonWidth[u11] = t11.width;
            this.buttonHeight[u11] = t11.height;
        });
    }
    changeSelectedIndexes(h11) {
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
            let i11 = this.selectedIndexes;
            for (let n11 = 0; n11 < this.optionsArray.deleteCount; n11++) {
                let o11 = i11.indexOf(this.optionsArray.changeStartIndex);
                let p11 = i11.map(r11 => this.optionsArray.changeStartIndex &&
                    (r11 > this.optionsArray.changeStartIndex) ? r11 - 1 : r11);
                if (o11 !== -1) {
                    p11.splice(o11, 1);
                }
                i11 = p11;
            }
            for (let j11 = 0; j11 < this.optionsArray.addLength; j11++) {
                let k11 = i11.map(m11 => this.optionsArray.changeStartIndex &&
                    (m11 >= this.optionsArray.changeStartIndex) ? m11 + 1 : m11);
                i11 = k11;
            }
            this.selectedIndexes = i11;
        }
    }
    changeFocusIndex(g11) {
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
        let f11 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 &&
            this.optionsArray.addLength !== void 0) {
            this.changeSelectedIndexes(f11);
            this.changeFocusIndex(f11);
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
        for (let e11 = 0; e11 < this.buttonItemsRealHeight.length; e11++) {
            this.buttonItemsRealHeight[e11] = 0;
        }
    }
    getBorderRadius(c11) {
        let d11 = this.buttonBorderRadius[c11];
        if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex]) {
            d11.topStart = LengthMetrics.vp((d11.topStart?.value ?? 0) + 4);
            d11.topEnd = LengthMetrics.vp((d11.topEnd?.value ?? 0) + 4);
            d11.bottomStart = LengthMetrics.vp((d11.bottomStart?.value ?? 0) + 4);
            d11.bottomEnd = LengthMetrics.vp((d11.bottomEnd?.value ?? 0) + 4);
        }
        return d11;
    }
    focusStack(u10, v10 = null) {
        this.observeComponentCreation2((a11, b11) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((y10, z10) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.borderRadius(this.getBorderRadius(u10));
            Stack.size({
                width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonWidth[u10] + 8 : this.buttonWidth[u10],
                height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonHeight[u10] + 8 : this.buttonHeight[u10]
            });
            Stack.borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR);
            Stack.borderWidth(2);
        }, Stack);
        Stack.pop();
        Stack.pop();
    }
    calculateBorderRadius() {
        let o10 = Array.from({
            length: MAX_ITEM_COUNT
        }, (s10, t10) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        });
        for (let q10 = 0; q10 < this.buttonBorderRadius.length; q10++) {
            let r10 = this.buttonItemsSize[q10].height / 2;
            if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                o10[q10].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? r10);
                o10[q10].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? r10);
                o10[q10].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? r10);
                o10[q10].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? r10);
            }
            else {
                if (q10 === 0) {
                    o10[q10].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? r10);
                    o10[q10].topEnd = LengthMetrics.vp(0);
                    o10[q10].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? r10);
                    o10[q10].bottomEnd = LengthMetrics.vp(0);
                }
                else if (this.options.buttons && q10 === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    o10[q10].topStart = LengthMetrics.vp(0);
                    o10[q10].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? r10);
                    o10[q10].bottomStart = LengthMetrics.vp(0);
                    o10[q10].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? r10);
                }
                else {
                    o10[q10].topStart = LengthMetrics.vp(0);
                    o10[q10].topEnd = LengthMetrics.vp(0);
                    o10[q10].bottomStart = LengthMetrics.vp(0);
                    o10[q10].bottomEnd = LengthMetrics.vp(0);
                }
            }
        }
        this.buttonBorderRadius = o10;
    }
    SegmentButtonFocus(m9, n9, o9 = null) {
        this.observeComponentCreation2((m10, n10) => {
            Stack.create();
        }, Stack);
        {
            this.observeComponentCreation2((g10, h10) => {
                if (h10) {
                    let i10 = new PressAndHoverEffect(this, {
                        pressIndex: m9,
                        colorProperty: this.hoverColorArray[m9],
                        press: this.pressArray[m9],
                        hover: this.hoverArray[m9],
                        options: this.options,
                    }, undefined, g10, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton0822NewF.ets", line: 835, col: 7 });
                    ViewPU.create(i10);
                    let q = () => {
                        return {
                            pressIndex: m9,
                            colorProperty: this.hoverColorArray[m9],
                            press: this.pressArray[m9],
                            hover: this.hoverArray[m9],
                            options: this.options
                        };
                    };
                    i10.paramsGenerator_ = q;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(g10, {
                        colorProperty: this.hoverColorArray[m9],
                        press: this.pressArray[m9],
                        hover: this.hoverArray[m9],
                        options: this.options
                    });
                }
            }, { name: "PressAndHoverEffect" });
        }
        this.observeComponentCreation2((y9, z9) => {
            __Common__.create();
            __Common__.onSizeChange((b10, c10) => {
                this.buttonItemsRealHeight[m9] = c10.height;
                let d10 = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ?
                this.options.buttons.length : 0));
                for (let e10 = 0; e10 < this.buttonItemsSize.length; e10++) {
                    this.buttonItemsSize[e10] = { width: this.buttonItemsSize[e10].width, height: d10 };
                }
                this.calculateBorderRadius();
            });
        }, __Common__);
        {
            this.observeComponentCreation2((s9, t9) => {
                if (t9) {
                    let u9 = new SegmentButtonItem(this, {
                        isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                        selectedIndexes: this.__selectedIndexes,
                        focusIndex: this.__focusIndex,
                        index: m9,
                        itemOptions: n9,
                        options: this.options,
                        property: this.buttonItemProperty[m9],
                        groupId: this.groupId,
                        marquee: this.marquee
                    }, undefined, s9, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton0822NewF.ets", line: 842, col: 7 });
                    ViewPU.create(u9);
                    let p = () => {
                        return {
                            isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                            selectedIndexes: this.selectedIndexes,
                            focusIndex: this.focusIndex,
                            index: m9,
                            itemOptions: n9,
                            options: this.options,
                            property: this.buttonItemProperty[m9],
                            groupId: this.groupId,
                            marquee: this.marquee
                        };
                    };
                    u9.paramsGenerator_ = p;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(s9, {
                        isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                        index: m9,
                        itemOptions: n9,
                        options: this.options,
                        property: this.buttonItemProperty[m9],
                        marquee: this.marquee
                    });
                }
            }, { name: "SegmentButtonItem" });
        }
        __Common__.pop();
        Stack.pop();
    }
    stackClick(l9) {
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            if (this.selectedIndexes.indexOf(l9) > -1) {
                this.selectedIndexes.splice(this.selectedIndexes.indexOf(l9), 1);
            }
            else {
                this.selectedIndexes.push(l9);
            }
        }
        else {
            this.selectedIndexes[0] = l9;
        }
    }
    initialRender() {
        this.observeComponentCreation2((i7, j7) => {
            If.create();
            if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g9, h9) => {
                        Row.create({ space: 1 });
                        Row.direction(this.options.direction);
                        Row.focusScopeId(this.groupId, true);
                        Row.padding(this.options?.multiply ? 0 : segmentButtonTheme.SEGMENT_BUTTON_PADDING);
                        Row.onSizeChange((j9, k9) => {
                            this.componentSize = { width: k9.width, height: k9.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((o7, p7) => {
                        ForEach.create();
                        const o = (s7, t7) => {
                            const u7 = s7;
                            this.observeComponentCreation2((w7, x7) => {
                                If.create();
                                if (t7 < MAX_ITEM_COUNT) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((k8, l8) => {
                                            Stack.create();
                                            Stack.direction(this.options.direction);
                                            Stack.borderRadius(this.buttonBorderRadius[t7]);
                                            Stack.scale({
                                                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[t7],
                                                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[t7]
                                            });
                                            Stack.layoutWeight(1);
                                            Stack.onSizeChange((e9, f9) => {
                                                this.buttonItemsSize[t7] = { width: f9.width, height: this.buttonItemsSize[t7].height };
                                                if (f9.width) {
                                                    this.buttonItemsPosition[t7] = {
                                                        start: LengthMetrics.vp(Number.parseFloat(segmentButtonTheme.SEGMENT_BUTTON_PADDING_NUMBER.toString()) +
                                                            (Number.parseFloat(f9.width.toString()) + 1) * t7),
                                                        top: LengthMetrics.px(Math.floor(this.getUIContext()
                                                            .vp2px(Number.parseFloat(segmentButtonTheme.SEGMENT_BUTTON_PADDING_NUMBER.toString()))))
                                                    };
                                                }
                                            });
                                            Stack.onClick(() => {
                                                this.stackClick(t7);
                                            });
                                            Stack.focusable(true);
                                            Stack.focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === t7 ?
                                            FocusPriority.PREVIOUS : FocusPriority.AUTO);
                                            Stack.onFocus(() => {
                                                this.focusIndex = t7;
                                                this.marquee = verifyResource(segmentButtonTheme.SEGMENT_MARQUEE, 1, getContext(this)) === 0;
                                                if (this.marquee) {
                                                    this.hoverColorArray[t7].hoverColor = { "id": -1, "type": 10001, params: ['sys.color.segment_button_focus_backboard_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                                }
                                            });
                                            Stack.onBlur(() => {
                                                this.focusIndex = -1;
                                                this.hoverColorArray[t7].hoverColor = Color.Transparent;
                                            });
                                            Stack.onTouch((b9) => {
                                                if (this.marquee) {
                                                    this.getUIContext().getFocusController().clearFocus();
                                                }
                                                if (b9.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (b9.type === TouchType.Down) {
                                                    Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                                                        this.zoomScaleArray[t7] = 0.95;
                                                    });
                                                }
                                                else if (b9.type === TouchType.Up) {
                                                    Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                                                        this.zoomScaleArray[t7] = 1;
                                                    });
                                                }
                                            });
                                            Stack.onHover((y8) => {
                                                this.hoverArray[t7] = y8;
                                                if (y8) {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[t7].hoverColor = this.marquee && this.focusIndex === t7 ? { "id": -1, "type": 10001, params: ['sys.color.segment_button_focus_backboard_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : (segmentButtonTheme.HOVER_COLOR);
                                                    });
                                                }
                                                else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[t7].hoverColor = this.marquee && this.focusIndex === t7 ? { "id": -1, "type": 10001, params: ['sys.color.segment_button_focus_backboard_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : Color.Transparent;
                                                    });
                                                }
                                            });
                                            Stack.onMouse((t8) => {
                                                switch (t8.action) {
                                                    case MouseAction.Press:
                                                        Context.animateTo({ curve: curves.springMotion(0.347, 0.99) }, () => {
                                                            this.zoomScaleArray[t7] = 0.95;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[t7] = true;
                                                        });
                                                        break;
                                                    case MouseAction.Release:
                                                        Context.animateTo({ curve: curves.springMotion(0.347, 0.99) }, () => {
                                                            this.zoomScaleArray[t7] = 1;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[t7] = false;
                                                        });
                                                        break;
                                                }
                                            });
                                        }, Stack);
                                        this.observeComponentCreation2((c8, d8) => {
                                            If.create();
                                            if (this.segmentFocusControl) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((h8, i8) => {
                                                        Stack.create();
                                                        ViewStackProcessor.visualState("normal");
                                                        Stack.overlay(undefined);
                                                        ViewStackProcessor.visualState("focused");
                                                        Stack.overlay({ builder: () => {
                                                            this.focusStack.call(this, t7);
                                                        } }, {
                                                            align: Alignment.Center
                                                        });
                                                        ViewStackProcessor.visualState();
                                                        Stack.onClick(() => {
                                                            this.stackClick(t7);
                                                        });
                                                    }, Stack);
                                                    this.SegmentButtonFocus.bind(this)(t7, u7);
                                                    Stack.pop();
                                                });
                                            }
                                            else {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.SegmentButtonFocus.bind(this)(t7, u7);
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
                        this.forEachUpdateFunction(o7, this.optionsArray, o, undefined, true, false);
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
    }
};
ItemProperty = __decorate([
    Observed
], ItemProperty);
export class SegmentButton extends ViewPU {
    constructor(a6, b6, c6, d6 = -1, e6 = undefined, f6) {
        super(a6, c6, d6, f6);
        if (typeof e6 === "function") {
            this.paramsGenerator_ = e6;
        }
        this.__options = new SynchedPropertyNesedObjectPU(b6.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(b6.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, "componentSize");
        this.addProvidedVar("componentSize", this.__componentSize, false);
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (f7, g7) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        }), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.__buttonBorderRadius, false);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (d7, e7) => {
            return {};
        }), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.__buttonItemsSize, false);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (b7, c7) => {
            return {};
        }), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.__buttonItemsPosition, false);
        this.__buttonItemsSelected = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (z6, a7) => false), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected, false);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (x6, y6) => new ItemProperty()), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty, false);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex, false);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition, false);
        this.__zoomScaleArray = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (v6, w6) => 1.0), this, "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.__zoomScaleArray, false);
        this.__pressArray = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (t6, u6) => false), this, "pressArray");
        this.__hoverArray = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (r6, s6) => false), this, "hoverArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (p6, q6) => new HoverColorProperty()), this, "hoverColorArray");
        this.doSelectedChangeAnimate = false;
        this.isCurrentPositionSelected = false;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = false;
        this.__shouldMirror = new ObservedPropertySimplePU(false, this, "shouldMirror");
        this.setInitiallyProvidedValue(b6);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.declareWatch("buttonItemsPosition", this.onItemsPositionChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z5) {
        this.__options.set(z5.options);
        if (z5.componentSize !== undefined) {
            this.componentSize = z5.componentSize;
        }
        if (z5.buttonBorderRadius !== undefined) {
            this.buttonBorderRadius = z5.buttonBorderRadius;
        }
        if (z5.buttonItemsSize !== undefined) {
            this.buttonItemsSize = z5.buttonItemsSize;
        }
        if (z5.buttonItemsPosition !== undefined) {
            this.buttonItemsPosition = z5.buttonItemsPosition;
        }
        if (z5.buttonItemsSelected !== undefined) {
            this.buttonItemsSelected = z5.buttonItemsSelected;
        }
        if (z5.buttonItemProperty !== undefined) {
            this.buttonItemProperty = z5.buttonItemProperty;
        }
        if (z5.focusIndex !== undefined) {
            this.focusIndex = z5.focusIndex;
        }
        if (z5.selectedItemPosition !== undefined) {
            this.selectedItemPosition = z5.selectedItemPosition;
        }
        if (z5.zoomScaleArray !== undefined) {
            this.zoomScaleArray = z5.zoomScaleArray;
        }
        if (z5.pressArray !== undefined) {
            this.pressArray = z5.pressArray;
        }
        if (z5.hoverArray !== undefined) {
            this.hoverArray = z5.hoverArray;
        }
        if (z5.hoverColorArray !== undefined) {
            this.hoverColorArray = z5.hoverColorArray;
        }
        if (z5.doSelectedChangeAnimate !== undefined) {
            this.doSelectedChangeAnimate = z5.doSelectedChangeAnimate;
        }
        if (z5.isCurrentPositionSelected !== undefined) {
            this.isCurrentPositionSelected = z5.isCurrentPositionSelected;
        }
        if (z5.panGestureStartPoint !== undefined) {
            this.panGestureStartPoint = z5.panGestureStartPoint;
        }
        if (z5.isPanGestureMoved !== undefined) {
            this.isPanGestureMoved = z5.isPanGestureMoved;
        }
        if (z5.shouldMirror !== undefined) {
            this.shouldMirror = z5.shouldMirror;
        }
    }
    updateStateVars(y5) {
        this.__options.set(y5.options);
    }
    purgeVariableDependenciesOnElmtId(x5) {
        this.__options.purgeDependencyOnElmtId(x5);
        this.__selectedIndexes.purgeDependencyOnElmtId(x5);
        this.__componentSize.purgeDependencyOnElmtId(x5);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(x5);
        this.__buttonItemsSize.purgeDependencyOnElmtId(x5);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(x5);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(x5);
        this.__buttonItemProperty.purgeDependencyOnElmtId(x5);
        this.__focusIndex.purgeDependencyOnElmtId(x5);
        this.__selectedItemPosition.purgeDependencyOnElmtId(x5);
        this.__zoomScaleArray.purgeDependencyOnElmtId(x5);
        this.__pressArray.purgeDependencyOnElmtId(x5);
        this.__hoverArray.purgeDependencyOnElmtId(x5);
        this.__hoverColorArray.purgeDependencyOnElmtId(x5);
        this.__shouldMirror.purgeDependencyOnElmtId(x5);
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
    set selectedIndexes(w5) {
        this.__selectedIndexes.set(w5);
    }
    get componentSize() {
        return this.__componentSize.get();
    }
    set componentSize(v5) {
        this.__componentSize.set(v5);
    }
    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }
    set buttonBorderRadius(u5) {
        this.__buttonBorderRadius.set(u5);
    }
    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }
    set buttonItemsSize(t5) {
        this.__buttonItemsSize.set(t5);
    }
    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }
    set buttonItemsPosition(s5) {
        this.__buttonItemsPosition.set(s5);
    }
    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }
    set buttonItemsSelected(r5) {
        this.__buttonItemsSelected.set(r5);
    }
    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }
    set buttonItemProperty(q5) {
        this.__buttonItemProperty.set(q5);
    }
    get focusIndex() {
        return this.__focusIndex.get();
    }
    set focusIndex(p5) {
        this.__focusIndex.set(p5);
    }
    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }
    set selectedItemPosition(o5) {
        this.__selectedItemPosition.set(o5);
    }
    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }
    set zoomScaleArray(n5) {
        this.__zoomScaleArray.set(n5);
    }
    get pressArray() {
        return this.__pressArray.get();
    }
    set pressArray(m5) {
        this.__pressArray.set(m5);
    }
    get hoverArray() {
        return this.__hoverArray.get();
    }
    set hoverArray(l5) {
        this.__hoverArray.set(l5);
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
        return !nearEqual(x4, this.panGestureStartPoint.x) || !nearEqual(y4, this.panGestureStartPoint.y);
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
            Stack.direction(this.options ? this.options.direction : undefined);
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
                if (this.options === void 0 || this.options.buttons === void 0 || m4.sourceTool === SourceTool.TOUCHPAD) {
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
                                            }, undefined, g3, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton0822NewF.ets", line: 1172, col: 11 });
                                            ViewPU.create(i3);
                                            let n = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options
                                                };
                                            };
                                            i3.paramsGenerator_ = n;
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
                                                Row.direction(this.options.direction);
                                            }, Row);
                                            this.observeComponentCreation2((e2, f2) => {
                                                ForEach.create();
                                                const j = (i2, j2) => {
                                                    const k2 = i2;
                                                    this.observeComponentCreation2((m2, n2) => {
                                                        If.create();
                                                        if (j2 < MAX_ITEM_COUNT) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.observeComponentCreation2((y2, z2) => {
                                                                    Stack.create();
                                                                    Stack.direction(this.options.direction);
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
                                                                                hover: this.hoverArray[j2],
                                                                                options: this.options,
                                                                            }, undefined, s2, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton0822NewF.ets", line: 1183, col: 23 });
                                                                            ViewPU.create(u2);
                                                                            let k = () => {
                                                                                return {
                                                                                    pressIndex: j2,
                                                                                    colorProperty: this.hoverColorArray[j2],
                                                                                    press: this.pressArray[j2],
                                                                                    hover: this.hoverArray[j2],
                                                                                    options: this.options
                                                                                };
                                                                            };
                                                                            u2.paramsGenerator_ = k;
                                                                        }
                                                                        else {
                                                                            this.updateStateVarsOfChildByElmtId(s2, {
                                                                                colorProperty: this.hoverColorArray[j2],
                                                                                press: this.pressArray[j2],
                                                                                hover: this.hoverArray[j2],
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
                                                this.forEachUpdateFunction(e2, this.options.buttons, j, undefined, true, false);
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
                        Context.animation({ duration: 0 });
                        Stack.direction(this.options.direction);
                        Stack.size(ObservedObject.GetRawObject(this.componentSize));
                        Context.animation(null);
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
                                            }, undefined, l1, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton0822NewF.ets", line: 1209, col: 13 });
                                            ViewPU.create(n1);
                                            let g = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            n1.paramsGenerator_ = g;
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
                                            }, undefined, d1, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton0822NewF.ets", line: 1215, col: 13 });
                                            ViewPU.create(f1);
                                            let d = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            f1.paramsGenerator_ = d;
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
                                    hoverArray: this.__hoverArray,
                                    hoverColorArray: this.__hoverColorArray,
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    selectedIndexes: this.__selectedIndexes,
                                }, undefined, t, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton0822NewF.ets", line: 1230, col: 9 });
                                ViewPU.create(v);
                                let c = () => {
                                    return {
                                        pressArray: this.pressArray,
                                        hoverArray: this.hoverArray,
                                        hoverColorArray: this.hoverColorArray,
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