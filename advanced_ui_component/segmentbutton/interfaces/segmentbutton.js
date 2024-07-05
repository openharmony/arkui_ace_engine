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

var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var SegmentButtonItemOptionsArray_1, SegmentButtonOptions_1;
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const curves = globalThis.requireNativeModule("ohos.curves");
const KeyCode = globalThis.requireNapi("multimodalInput.keyCode").KeyCode;
const util = globalThis.requireNapi("util");
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const resourceManager = requireNapi("resourceManager");
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
    HOVER_COLOR: { "id": -1, "type": 10001, params: ["sys.color.segment_button_color_hovered"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    PRESS_COLOR: { "id": -1, "type": 10001, params: ["sys.color.segment_button_color_Press"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    BACKGROUND_BLUR_STYLE: getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_background_blur_style'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
    SEGMENT_BUTTON_PADDING: { "id": -1, "type": 10002, params: ['sys.float.segment_button_baseplate_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    CONSTRAINT_SIZE_MIN_WIDTH: { "id": -1, "type": 10002, params: ['sys.float.segment_min_button_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    CONSTRAINT_SIZE_MIN_HEIGHT: { "id": -1, "type": 10002, params: ['sys.float.segment_button_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    SEGMENT_BUTTON_MIN_FONT_SIZE: { "id": -1, "type": 10002, params: ['sys.float.segment_button_min_font_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    SEGMENT_BUTTON_NORMAL_BORDER_RADIUS: { "id": -1, "type": 10002, params: ['sys.float.segment_button_normal_border_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
};
function nearEqual(first, second) {
    return Math.abs(first - second) < 0.001;
}
let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(options) {
        this.icon = options.icon;
        this.selectedIcon = options.selectedIcon;
        this.text = options.text;
    }
};
SegmentButtonItemOptions = __decorate([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends Array {
    constructor(elementsOrLength) {
        super(typeof elementsOrLength === "number" ? elementsOrLength : 0);
        this.changeStartIndex = void 0;
        this.deleteCount = void 0;
        this.addLength = void 0;
        if (typeof elementsOrLength !== "number" && elementsOrLength !== void 0) {
            super.push(...elementsOrLength.map((element) => new SegmentButtonItemOptions(element)));
        }
    }
    push(...items) {
        if (this.length + items.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        this.changeStartIndex = this.length;
        this.deleteCount = 0;
        this.addLength = items.length;
        return super.push(...items.map((element) => new SegmentButtonItemOptions(element)));
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
    unshift(...items) {
        if (this.length + items.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        if (items.length > 0) {
            this.changeStartIndex = 0;
            this.deleteCount = 0;
            this.addLength = items.length;
        }
        return super.unshift(...items.map((element) => new SegmentButtonItemOptions(element)));
    }
    splice(start, deleteCount, ...items) {
        let length = (this.length - deleteCount) < 0 ? 0 : (this.length - deleteCount);
        length += items.length;
        if (length < MIN_ITEM_COUNT) {
            console.warn("Below the minimum number of elements (2).");
            return [];
        }
        if (length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return [];
        }
        this.changeStartIndex = start;
        this.deleteCount = deleteCount;
        this.addLength = items.length;
        return super.splice(start, deleteCount, ...items);
    }
    static create(elements) {
        return new SegmentButtonItemOptionsArray_1(elements);
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
    set buttons(val) {
        if (this._buttons !== void 0 && this._buttons !== val) {
            this.onButtonsChange?.();
        }
        this._buttons = val;
    }
    constructor(options) {
        this.multiply = false;
        this.showText = false;
        this.showIcon = false;
        this._buttons = void 0;
        this.fontColor = options.fontColor ?? segmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = options.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = options.fontSize ?? segmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = options.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = options.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = options.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = options.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = options.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = options.buttonPadding;
        this.textPadding = options.textPadding;
        this.type = options.type;
        this.backgroundBlurStyle = options.backgroundBlurStyle ?? segmentButtonTheme.BACKGROUND_BLUR_STYLE;
        this.localizedTextPadding = options.localizedButtonPadding;
        this.localizedButtonPadding = options.localizedButtonPadding;
        this.direction = options.direction ?? Direction.Auto;
        this.buttons = new SegmentButtonItemOptionsArray(options.buttons);
        if (this.type === "capsule") {
            this.multiply = options.multiply ?? false;
            this.buttons.forEach(button => {
                this.showText ||= button.text !== void 0;
                this.showIcon ||= button.icon !== void 0 || button.selectedIcon !== void 0;
            });
            if (this.showText && this.showIcon) {
                this.iconTextRadius = 12;
                this.iconTextBackgroundRadius = 14;
            }
            this.selectedFontColor = options.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
        else {
            this.showText = true;
        }
        this.componentPadding = this.multiply ? 0 : 2;
    }
    static tab(options) {
        return new SegmentButtonOptions_1({
            type: "tab",
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
        return new SegmentButtonOptions_1({
            type: "capsule",
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
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([
    Observed
], SegmentButtonOptions);
export { SegmentButtonOptions };
class MultiSelectBackground extends ViewPU {
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
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const _ = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (index < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[index].height);
                                Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[index]);
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
            this.forEachUpdateFunction(elmtId, this.optionsArray, forEachItemGenFunction, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class SelectItem extends ViewPU {
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
                            (this.options.type === 'tab' ? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR :
                            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR));
                        Stack.position(ObservedObject.GetRawObject(this.selectedItemPosition));
                        Stack.scale({ x: this.zoomScaleArray[this.selectedIndexes[0]], y: this.zoomScaleArray[this.selectedIndexes[0]] });
                        Stack.shadow(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_shadow'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) || 0);
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
        this.__multiColor = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (_, index) => Color.Transparent), this, "multiColor");
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
        for (let i = 0; i < this.selectedIndexes.length; i++) {
            this.multiColor[this.selectedIndexes[i]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }
    onSelectedChange() {
        for (let i = 0; i < MAX_ITEM_COUNT; i++) {
            this.multiColor[i] = Color.Transparent;
        }
        for (let i = 0; i < this.selectedIndexes.length; i++) {
            this.multiColor[this.selectedIndexes[i]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }
    aboutToAppear() {
        for (let i = 0; i < this.selectedIndexes.length; i++) {
            this.multiColor[this.selectedIndexes[i]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const _ = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (index < MAX_ITEM_COUNT) {
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
                    }
                    else {
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
/**
 * get resource size
 *
 * @param resourceName resource name
 * @returns resource size
 */
function getNumberByResource(resourceName) {
    try {
        return resourceManager.getSystemResourceManager().getNumber(resourceName);
    }
    catch (error) {
        return null;
    }
}
class SegmentButtonItem extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, "selectedIndexes");
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(params.focusIndex, this, "focusIndex");
        this.__itemOptions = new SynchedPropertyNesedObjectPU(params.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(params.property, this, "property");
        this.__index = new SynchedPropertySimpleOneWayPU(params.index, this, "index");
        this.__marquee = new SynchedPropertySimpleOneWayPU(params.marquee, this, "marquee");
        this.groupId = "";
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
        this.__itemOptions.set(params.itemOptions);
        this.__options.set(params.options);
        this.__property.set(params.property);
        this.__index.reset(params.index);
        this.__marquee.reset(params.marquee);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__selectedIndexes.purgeDependencyOnElmtId(rmElmtId);
        this.__focusIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__itemOptions.purgeDependencyOnElmtId(rmElmtId);
        this.__options.purgeDependencyOnElmtId(rmElmtId);
        this.__property.purgeDependencyOnElmtId(rmElmtId);
        this.__index.purgeDependencyOnElmtId(rmElmtId);
        this.__marquee.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__selectedIndexes.aboutToBeDeleted();
        this.__focusIndex.aboutToBeDeleted();
        this.__itemOptions.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__property.aboutToBeDeleted();
        this.__index.aboutToBeDeleted();
        this.__marquee.aboutToBeDeleted();
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
    get marquee() {
        return this.__marquee.get();
    }
    set marquee(newValue) {
        this.__marquee.set(newValue);
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
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create({ space: 2 });
            Column.focusable(false);
            Column.direction(this.options.direction);
            Column.focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.getButtonPadding());
            Column.constraintSize(this.property.constraintSize);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.options.showText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.itemOptions.text);
                        Text.direction(this.options.direction);
                        Text.fontColor(this.property.fontColor);
                        Text.fontWeight(this.property.fontWeight);
                        Text.fontSize(this.property.fontSize);
                        Text.minFontSize(this.property.minFontSize);
                        Text.maxFontSize(this.property.fontSize);
                        __Text__fancy();
                        Text.marqueeOptions({ start: this.marquee, fadeout: true });
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
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(params.press, this, "press");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(params.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__options = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.pressIndex = 0;
        this.pressColor = segmentButtonTheme.PRESS_COLOR;
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
        this.__colorProperty.set(params.colorProperty);
        this.__options.set(params.options);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
        this.__press.purgeDependencyOnElmtId(rmElmtId);
        this.__colorProperty.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
        this.__options.purgeDependencyOnElmtId(rmElmtId);
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
    set buttonItemsSize(newValue) {
        this.__buttonItemsSize.set(newValue);
    }
    get press() {
        return this.__press.get();
    }
    set press(newValue) {
        this.__press.set(newValue);
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
            Stack.focusable(false);
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
function __Text__fancy() { Text.textOverflow({ overflow: TextOverflow.MARQUEE }); }
class SegmentButtonItemArrayComponent extends ViewPU {
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
        this.__pressArray = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (_, index) => false), this, "pressArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (_, index) => new HoverColorProperty()), this, "hoverColorArray");
        this.__buttonWidth = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (_, index) => 0), this, "buttonWidth");
        this.__buttonHeight = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (_, index) => 0), this, "buttonHeight");
        this.__marquee = new ObservedPropertySimplePU(false, this, "marquee");
        this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (_, index) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.setInitiallyProvidedValue(params);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        this.__optionsArray.set(params.optionsArray);
        this.__options.set(params.options);
        if (params.pressArray !== undefined) {
            this.pressArray = params.pressArray;
        }
        if (params.hoverColorArray !== undefined) {
            this.hoverColorArray = params.hoverColorArray;
        }
        if (params.buttonWidth !== undefined) {
            this.buttonWidth = params.buttonWidth;
        }
        if (params.buttonHeight !== undefined) {
            this.buttonHeight = params.buttonHeight;
        }
        if (params.marquee !== undefined) {
            this.marquee = params.marquee;
        }
        if (params.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = params.buttonItemsRealHeight;
        }
        if (params.groupId !== undefined) {
            this.groupId = params.groupId;
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
        this.__componentSize.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(rmElmtId);
        this.__focusIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__zoomScaleArray.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemProperty.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(rmElmtId);
        this.__pressArray.purgeDependencyOnElmtId(rmElmtId);
        this.__hoverColorArray.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__marquee.purgeDependencyOnElmtId(rmElmtId);
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
    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }
    set hoverColorArray(newValue) {
        this.__hoverColorArray.set(newValue);
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
    get marquee() {
        return this.__marquee.get();
    }
    set marquee(newValue) {
        this.__marquee.set(newValue);
    }
    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((value, index) => {
            this.buttonWidth[index] = value.width;
            this.buttonHeight[index] = value.height;
        });
    }
    changeSelectedIndexes(buttonsLength) {
        if (this.optionsArray.changeStartIndex === void 0 || this.optionsArray.deleteCount === void 0 ||
            this.optionsArray.addLength === void 0) {
            return;
        }
        if (!(this.options.multiply ?? false)) {
            // Single-select
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
            // Multi-select
            let saveIndexes = this.selectedIndexes;
            for (let i = 0; i < this.optionsArray.deleteCount; i++) {
                let deleteIndex = saveIndexes.indexOf(this.optionsArray.changeStartIndex);
                let indexes = saveIndexes.map(value => this.optionsArray.changeStartIndex &&
                    (value > this.optionsArray.changeStartIndex) ? value - 1 : value);
                if (deleteIndex !== -1) {
                    indexes.splice(deleteIndex, 1);
                }
                saveIndexes = indexes;
            }
            for (let i = 0; i < this.optionsArray.addLength; i++) {
                let indexes = saveIndexes.map(value => this.optionsArray.changeStartIndex &&
                    (value >= this.optionsArray.changeStartIndex) ? value + 1 : value);
                saveIndexes = indexes;
            }
            this.selectedIndexes = saveIndexes;
        }
    }
    changeFocusIndex(buttonsLength) {
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
        let buttonsLength = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 &&
            this.optionsArray.addLength !== void 0) {
            this.changeSelectedIndexes(buttonsLength);
            this.changeFocusIndex(buttonsLength);
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
        for (let index = 0; index < this.buttonItemsRealHeight.length; index++) {
            this.buttonItemsRealHeight[index] = 0;
        }
    }
    getBorderRadius(index) {
        let borderRadius = this.buttonBorderRadius[index];
        if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] && borderRadius.topStart) {
            borderRadius.topStart = LengthMetrics.vp(borderRadius.topStart.value + 4);
            borderRadius.topEnd = LengthMetrics.vp(borderRadius.topStart.value + 4);
            borderRadius.bottomStart = LengthMetrics.vp(borderRadius.topStart.value + 4);
            borderRadius.bottomEnd = LengthMetrics.vp(borderRadius.topStart.value + 4);
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
                width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonWidth[index] + 8 : this.buttonWidth[index],
                height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonHeight[index] + 8 : this.buttonHeight[index]
            });
            Stack.borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR);
            Stack.borderWidth(2);
        }, Stack);
        Stack.pop();
        Stack.pop();
    }
    calculateBorderRadius() {
        let borderRadiusArray = Array.from({
            length: MAX_ITEM_COUNT
        }, (_, index) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        });
        for (let index = 0; index < this.buttonBorderRadius.length; index++) {
            let halfButtonItemsSizeHeight = this.buttonItemsSize[index].height / 2;
            if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                borderRadiusArray[index].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
                borderRadiusArray[index].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
                borderRadiusArray[index].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
                borderRadiusArray[index].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
            }
            else {
                if (index === 0) {
                    borderRadiusArray[index].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
                    borderRadiusArray[index].topEnd = LengthMetrics.vp(0);
                    borderRadiusArray[index].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
                    borderRadiusArray[index].bottomEnd = LengthMetrics.vp(0);
                }
                else if (this.options.buttons && index === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    borderRadiusArray[index].topStart = LengthMetrics.vp(0);
                    borderRadiusArray[index].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
                    borderRadiusArray[index].bottomStart = LengthMetrics.vp(0);
                    borderRadiusArray[index].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
                }
                else {
                    borderRadiusArray[index].topStart = LengthMetrics.vp(0);
                    borderRadiusArray[index].topEnd = LengthMetrics.vp(0);
                    borderRadiusArray[index].bottomStart = LengthMetrics.vp(0);
                    borderRadiusArray[index].bottomEnd = LengthMetrics.vp(0);
                }
            }
        }
        this.buttonBorderRadius = borderRadiusArray;
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
                        Row.padding(segmentButtonTheme.SEGMENT_BUTTON_PADDING || 2);
                        Row.onSizeChange((_, newValue) => {
                            this.componentSize = { width: newValue.width, height: newValue.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        ForEach.create();
                        const forEachItemGenFunction = (_item, index) => {
                            const item = _item;
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                If.create();
                                if (index < MAX_ITEM_COUNT) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Stack.create();
                                            Stack.direction(this.options.direction);
                                            Stack.borderRadius(this.buttonBorderRadius[index]);
                                            Stack.scale({
                                                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[index],
                                                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[index]
                                            });
                                            Stack.layoutWeight(1);
                                            Stack.onSizeChange((_, newValue) => {
                                                this.buttonItemsSize[index] = { width: newValue.width, height: this.buttonItemsSize[index].height };
                                                //measure position
                                                if (newValue.width) {
                                                    this.buttonItemsPosition[index] = {
                                                        x: Number.parseFloat(this.options.componentPadding.toString()) +
                                                            (Number.parseFloat(newValue.width.toString()) + 1) * index,
                                                        y: Number.parseFloat(this.options.componentPadding.toString())
                                                    };
                                                }
                                            });
                                            ViewStackProcessor.visualState("normal");
                                            Stack.overlay(undefined);
                                            ViewStackProcessor.visualState("focused");
                                            Stack.overlay({ builder: () => {
                                                this.focusStack.call(this, index);
                                            } }, {
                                                align: Alignment.Center
                                            });
                                            ViewStackProcessor.visualState();
                                            Stack.onClick(() => {
                                            });
                                            Stack.focusable(true);
                                            Stack.onFocus(() => {
                                                this.focusIndex = index;
                                                if (getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.segment_marquee'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) === 0) {
                                                    this.marquee = true;
                                                }
                                                else {
                                                    this.marquee = false;
                                                }
                                            });
                                            Stack.onTouch((event) => {
                                                if (event.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (event.type === TouchType.Down) {
                                                    Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                                                        this.zoomScaleArray[index] = 0.95;
                                                    });
                                                }
                                                else if (event.type === TouchType.Up) {
                                                    Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                                                        this.zoomScaleArray[index] = 1;
                                                    });
                                                }
                                            });
                                            Stack.onHover((isHover) => {
                                                if (isHover) {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[index].hoverColor = (segmentButtonTheme.HOVER_COLOR);
                                                    });
                                                }
                                                else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[index].hoverColor = Color.Transparent;
                                                    });
                                                }
                                            });
                                            Stack.onMouse((event) => {
                                                switch (event.action) {
                                                    case MouseAction.Press:
                                                        Context.animateTo({ curve: curves.springMotion(0.347, 0.99) }, () => {
                                                            this.zoomScaleArray[index] = 0.95;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[index] = true;
                                                        });
                                                        break;
                                                    case MouseAction.Release:
                                                        Context.animateTo({ curve: curves.springMotion(0.347, 0.99) }, () => {
                                                            this.zoomScaleArray[index] = 1;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[index] = false;
                                                        });
                                                        break;
                                                }
                                            });
                                        }, Stack);
                                        {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                if (isInitialRender) {
                                                    let componentCall = new PressAndHoverEffect(this, {
                                                        pressIndex: index,
                                                        colorProperty: this.hoverColorArray[index],
                                                        press: this.pressArray[index],
                                                        options: this.options,
                                                    }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton.ets", line: 802, col: 15 });
                                                    ViewPU.create(componentCall);
                                                    let paramsLambda = () => {
                                                        return {
                                                            pressIndex: index,
                                                            colorProperty: this.hoverColorArray[index],
                                                            press: this.pressArray[index],
                                                            options: this.options
                                                        };
                                                    };
                                                    componentCall.paramsGenerator_ = paramsLambda;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(elmtId, {
                                                        colorProperty: this.hoverColorArray[index],
                                                        press: this.pressArray[index],
                                                        options: this.options
                                                    });
                                                }
                                            }, { name: "PressAndHoverEffect" });
                                        }
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            __Common__.create();
                                            __Common__.onSizeChange((_, newValue) => {
                                                // Calculate height of items
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
                                                    let componentCall = new SegmentButtonItem(this, {
                                                        selectedIndexes: this.__selectedIndexes,
                                                        focusIndex: this.__focusIndex,
                                                        index: index,
                                                        itemOptions: item,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[index],
                                                        groupId: this.groupId,
                                                        marquee: this.marquee
                                                    }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton.ets", line: 808, col: 15 });
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
                                                            marquee: this.marquee
                                                        };
                                                    };
                                                    componentCall.paramsGenerator_ = paramsLambda;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(elmtId, {
                                                        index: index,
                                                        itemOptions: item,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[index],
                                                        marquee: this.marquee
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
                        this.forEachUpdateFunction(elmtId, this.optionsArray, forEachItemGenFunction, undefined, true, false);
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
        this.constraintSize = { minWidth: segmentButtonTheme.CONSTRAINT_SIZE_MIN_WIDTH, minHeight: segmentButtonTheme.CONSTRAINT_SIZE_MIN_HEIGHT } || { minWidth: 48, minHeight: 28 };
        this.minFontSize = segmentButtonTheme.SEGMENT_BUTTON_MIN_FONT_SIZE || 9;
        this.normalborderRadius = segmentButtonTheme.SEGMENT_BUTTON_NORMAL_BORDER_RADIUS || 2;
    }
};
ItemProperty = __decorate([
    Observed
], ItemProperty);
export class SegmentButton extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__options = new SynchedPropertyNesedObjectPU(params.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, "componentSize");
        this.addProvidedVar("componentSize", this.__componentSize, false);
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (_, index) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        }), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.__buttonBorderRadius, false);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (_, index) => {
            return {};
        }), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.__buttonItemsSize, false);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (_, index) => {
            return {};
        }), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.__buttonItemsPosition, false);
        this.__buttonItemsSelected = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (_, index) => false), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected, false);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (_, index) => new ItemProperty()), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty, false);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex, false);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition, false);
        this.__zoomScaleArray = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (_, index) => 1.0), this, "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.__zoomScaleArray, false);
        this.doSelectedChangeAnimate = false;
        this.isCurrentPositionSelected = false;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = false;
        this.setInitiallyProvidedValue(params);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.declareWatch("buttonItemsPosition", this.onItemsPositionChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        this.__options.set(params.options);
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
    }
    updateStateVars(params) {
        this.__options.set(params.options);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__options.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedIndexes.purgeDependencyOnElmtId(rmElmtId);
        this.__componentSize.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonItemProperty.purgeDependencyOnElmtId(rmElmtId);
        this.__focusIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedItemPosition.purgeDependencyOnElmtId(rmElmtId);
        this.__zoomScaleArray.purgeDependencyOnElmtId(rmElmtId);
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
        this.buttonItemsSelected.forEach((_, index) => {
            this.buttonItemsSelected[index] = false;
        });
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            this.selectedIndexes.forEach(index => this.buttonItemsSelected[index] = true);
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
        let invalid = this.selectedIndexes.some(index => {
            return (index === void 0 || index < 0 || (this.options.buttons && index >= this.options.buttons.length));
        });
        if (invalid) {
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
    isMouseWheelScroll(event) {
        return event.source === SourceType.Mouse && !this.isPanGestureMoved;
    }
    isMovedFromPanGestureStartPoint(x, y) {
        return !nearEqual(x, this.panGestureStartPoint.x) || !nearEqual(y, this.panGestureStartPoint.y);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.options.direction);
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
                                // Select
                                this.selectedIndexes.push(this.focusIndex);
                            }
                            else {
                                // Unselect
                                this.selectedIndexes.splice(this.selectedIndexes.indexOf(this.focusIndex), 1);
                            }
                        }
                        else {
                            // Pressed
                            this.selectedIndexes[0] = this.focusIndex;
                        }
                    }
                }
            });
            Gesture.create(GesturePriority.High);
            GestureGroup.create(GestureMode.Parallel);
            TapGesture.create();
            TapGesture.onAction((event) => {
                this.focusIndex = -1;
                let fingerInfo = event.fingerList.find(Boolean);
                if (fingerInfo === void 0) {
                    return;
                }
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                let selectedInfo = fingerInfo.localX;
                for (let i = 0; i < Math.min(this.options.buttons.length, this.buttonItemsSize.length); i++) {
                    selectedInfo = selectedInfo - this.buttonItemsSize[i].width;
                    if (selectedInfo >= 0) {
                        continue;
                    }
                    this.doSelectedChangeAnimate =
                        this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ? false : true;
                    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                        if (this.selectedIndexes.indexOf(i) === -1) {
                            this.selectedIndexes.push(i);
                        }
                        else {
                            this.selectedIndexes.splice(this.selectedIndexes.indexOf(i), 1);
                        }
                    }
                    else {
                        this.selectedIndexes[0] = i;
                    }
                    this.doSelectedChangeAnimate = false;
                    break;
                }
            });
            TapGesture.pop();
            SwipeGesture.create();
            SwipeGesture.onAction((event) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    // Non swipe gesture in multi-select mode
                    return;
                }
                if (this.isCurrentPositionSelected) {
                    return;
                }
                if (event.angle > 0 && this.selectedIndexes[0] !== Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    // Move to next
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
                    this.doSelectedChangeAnimate = false;
                }
                else if (event.angle < 0 && this.selectedIndexes[0] !== 0) {
                    // Move to previous
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
                    // Non drag gesture in multi-select mode
                    return;
                }
                let fingerInfo = event.fingerList.find(Boolean);
                if (fingerInfo === void 0) {
                    return;
                }
                let selectedInfo = fingerInfo.localX;
                this.panGestureStartPoint = { x: fingerInfo.globalX, y: fingerInfo.globalY };
                this.isPanGestureMoved = false;
                for (let i = 0; i < Math.min(this.options.buttons.length, this.buttonItemsSize.length); i++) {
                    selectedInfo = selectedInfo - this.buttonItemsSize[i].width;
                    if (selectedInfo < 0) {
                        this.isCurrentPositionSelected = i === this.selectedIndexes[0] ? true : false;
                        break;
                    }
                }
            });
            PanGesture.onActionUpdate((event) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    // Non drag gesture in multi-select mode
                    return;
                }
                if (!this.isCurrentPositionSelected) {
                    return;
                }
                let fingerInfo = event.fingerList.find(Boolean);
                if (fingerInfo === void 0) {
                    return;
                }
                let selectedInfo = fingerInfo.localX;
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(fingerInfo.globalX, fingerInfo.globalY)) {
                    this.isPanGestureMoved = true;
                }
                for (let i = 0; i < Math.min(this.options.buttons.length, this.buttonItemsSize.length); i++) {
                    selectedInfo = selectedInfo - this.buttonItemsSize[i].width;
                    if (selectedInfo < 0) {
                        this.doSelectedChangeAnimate = true;
                        this.selectedIndexes[0] = i;
                        this.doSelectedChangeAnimate = false;
                        break;
                    }
                }
                this.zoomScaleArray.forEach((_, index) => {
                    if (index === this.selectedIndexes[0]) {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[index] = 0.95;
                        });
                    }
                    else {
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
                    // Non drag gesture in multi-select mode
                    return;
                }
                let fingerInfo = event.fingerList.find(Boolean);
                if (fingerInfo === void 0) {
                    return;
                }
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(fingerInfo.globalX, fingerInfo.globalY)) {
                    this.isPanGestureMoved = true;
                }
                if (this.isMouseWheelScroll(event)) {
                    let offset = event.offsetX !== 0 ? event.offsetX : event.offsetY;
                    this.doSelectedChangeAnimate = true;
                    if (offset > 0 && this.selectedIndexes[0] > 0) {
                        this.selectedIndexes[0] -= 1;
                    }
                    else if (offset < 0 && this.selectedIndexes[0] < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
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
                                            let componentCall = new MultiSelectBackground(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                            }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton.ets", line: 1074, col: 11 });
                                            ViewPU.create(componentCall);
                                            let paramsLambda = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options
                                                };
                                            };
                                            componentCall.paramsGenerator_ = paramsLambda;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(elmtId, {
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
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Stack.create();
                                    Stack.direction(this.options.direction);
                                    Stack.size(ObservedObject.GetRawObject(this.componentSize));
                                    Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                                    Stack.borderRadius(this.options.iconTextBackgroundRadius ?? this.componentSize.height / (getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.segment_button_normal_border_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) || 2));
                                    Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
                                }, Stack);
                                Stack.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.direction(this.options.direction);
                        Stack.size(ObservedObject.GetRawObject(this.componentSize));
                        Stack.borderRadius((this.options.type === 'capsule' && (this.options.multiply ?? false) ?
                        this.options.iconTextRadius : this.options.iconTextBackgroundRadius) ??
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
                                            let componentCall = new MultiSelectItemArray(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton.ets", line: 1088, col: 13 });
                                            ViewPU.create(componentCall);
                                            let paramsLambda = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            componentCall.paramsGenerator_ = paramsLambda;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(elmtId, {
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
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        if (isInitialRender) {
                                            let componentCall = new SelectItem(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton.ets", line: 1094, col: 13 });
                                            ViewPU.create(componentCall);
                                            let paramsLambda = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            componentCall.paramsGenerator_ = paramsLambda;
                                        }
                                        else {
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
                                let componentCall = new SegmentButtonItemArrayComponent(this, {
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    selectedIndexes: this.__selectedIndexes,
                                }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/segmentbutton.ets", line: 1108, col: 9 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        optionsArray: this.options.buttons,
                                        options: this.options,
                                        selectedIndexes: this.selectedIndexes
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
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
    updateAnimatedProperty(curve) {
        let setAnimatedPropertyFunc = () => {
            this.selectedItemPosition = this.selectedIndexes.length === 0 ? {} : this.buttonItemsPosition[this.selectedIndexes[0]];
            this.buttonItemsSelected.forEach((selected, index) => {
                this.buttonItemProperty[index].fontColor = selected ?
                    this.options.selectedFontColor ?? (this.options.type === 'tab' ?
                    segmentButtonTheme.TAB_SELECTED_FONT_COLOR : segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR) :
                    this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
            });
        };
        if (curve) {
            Context.animateTo({ curve: curve }, setAnimatedPropertyFunc);
        }
        else {
            setAnimatedPropertyFunc();
        }
        this.buttonItemsSelected.forEach((selected, index) => {
            this.buttonItemProperty[index].fontSize = selected ? this.options.selectedFontSize ??
            segmentButtonTheme.SELECTED_FONT_SIZE : this.options.fontSize ?? segmentButtonTheme.FONT_SIZE;
            this.buttonItemProperty[index].fontWeight = selected ? this.options.selectedFontWeight ?? FontWeight.Medium :
                this.options.fontWeight ?? FontWeight.Regular;
            this.buttonItemProperty[index].isSelected = selected;
        });
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default { SegmentButton, SegmentButtonOptions, SegmentButtonItemOptionsArray, SegmentButtonItemOptions };
