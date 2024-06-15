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

var __decorate = (this && this.__decorate) || function (h48, i48, j48, k48) {
    var l48 = arguments.length,
        m48 = l48 < 3 ? i48 : k48 === null ? k48 = Object.getOwnPropertyDescriptor(i48, j48) : k48, n48;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        m48 = Reflect.decorate(h48, i48, j48, k48);
    else
        for (var o48 = h48.length - 1; o48 >= 0; o48--)
            if (n48 = h48[o48])
                m48 = (l48 < 3 ? n48(m48) : l48 > 3 ? n48(i48, j48, m48) : n48(i48, j48)) || m48;
    return l48 > 3 && m48 && Object.defineProperty(i48, j48, m48), m48;
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

function nearEqual(e48, f48) {
    return Math.abs(e48 - f48) < 0.001;
}

let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(d48) {
        this.icon = d48.icon;
        this.selectedIcon = d48.selectedIcon;
        this.text = d48.text;
    }
};
SegmentButtonItemOptions = __decorate([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends Array {
    constructor(a48) {
        super(typeof a48 === "number" ? a48 : 0);
        this.changeStartIndex = void 0;
        this.deleteCount = void 0;
        this.addLength = void 0;
        if (typeof a48 !== "number" && a48 !== void 0) {
            super.push(...a48.map((c48) => new SegmentButtonItemOptions(c48)));
        }
    }

    push(...x47) {
        if (this.length + x47.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        this.changeStartIndex = this.length;
        this.deleteCount = 0;
        this.addLength = x47.length;
        return super.push(...x47.map((z47) => new SegmentButtonItemOptions(z47)));
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

    unshift(...u47) {
        if (this.length + u47.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        if (u47.length > 0) {
            this.changeStartIndex = 0;
            this.deleteCount = 0;
            this.addLength = u47.length;
        }
        return super.unshift(...u47.map((w47) => new SegmentButtonItemOptions(w47)));
    }

    splice(q47, r47, ...s47) {
        let t47 = (this.length - r47) < 0 ? 0 : (this.length - r47);
        t47 += s47.length;
        if (t47 < MIN_ITEM_COUNT) {
            console.warn("Below the minimum number of elements (2).");
            return [];
        }
        if (t47 > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return [];
        }
        this.changeStartIndex = q47;
        this.deleteCount = r47;
        this.addLength = s47.length;
        return super.splice(q47, r47, ...s47);
    }

    static create(p47) {
        return new SegmentButtonItemOptionsArray_1(p47);
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

    set buttons(o47) {
        if (this._buttons !== void 0 && this._buttons !== o47) {
            this.onButtonsChange?.();
        }
        this._buttons = o47;
    }

    constructor(l47) {
        this.multiply = false;
        this.showText = false;
        this.showIcon = false;
        this._buttons = void 0;
        this.fontColor = l47.fontColor ?? segmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = l47.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = l47.fontSize ?? segmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = l47.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = l47.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = l47.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = l47.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = l47.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = l47.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = l47.buttonPadding;
        this.textPadding = l47.textPadding;
        this.type = l47.type;
        this.backgroundBlurStyle = l47.backgroundBlurStyle ?? segmentButtonTheme.BACKGROUND_BLUR_STYLE;
        this.localizedTextPadding = l47.localizedTextPadding;
        this.localizedButtonPadding = l47.localizedButtonPadding;
        this.direction = l47.direction ?? Direction.Auto;
        this.buttons = new SegmentButtonItemOptionsArray(l47.buttons);
        if (this.type === "capsule") {
            this.multiply = l47.multiply ?? false;
            this.buttons.forEach(n47 => {
                this.showText ||= n47.text !== void 0;
                this.showIcon ||= n47.icon !== void 0 || n47.selectedIcon !== void 0;
            });
            if (this.showText && this.showIcon) {
                this.iconTextRadius = 12;
                this.iconTextBackgroundRadius = 14;
            }
            this.selectedFontColor = l47.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = l47.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
        else {
            this.showText = true;
        }
        this.componentPadding = this.multiply ? 0 : 2;
    }

    static tab(k47) {
        return new SegmentButtonOptions_1({
            type: "tab",
            buttons: k47.buttons,
            fontColor: k47.fontColor,
            selectedFontColor: k47.selectedFontColor,
            fontSize: k47.fontSize,
            selectedFontSize: k47.selectedFontSize,
            fontWeight: k47.fontWeight,
            selectedFontWeight: k47.selectedFontWeight,
            backgroundColor: k47.backgroundColor,
            selectedBackgroundColor: k47.selectedBackgroundColor,
            imageSize: k47.imageSize,
            buttonPadding: k47.buttonPadding,
            textPadding: k47.textPadding,
            localizedTextPadding: k47.localizedTextPadding,
            localizedButtonPadding: k47.localizedButtonPadding,
            backgroundBlurStyle: k47.backgroundBlurStyle,
            direction: k47.direction
        });
    }

    static capsule(j47) {
        return new SegmentButtonOptions_1({
            type: "capsule",
            buttons: j47.buttons,
            multiply: j47.multiply,
            fontColor: j47.fontColor,
            selectedFontColor: j47.selectedFontColor,
            fontSize: j47.fontSize,
            selectedFontSize: j47.selectedFontSize,
            fontWeight: j47.fontWeight,
            selectedFontWeight: j47.selectedFontWeight,
            backgroundColor: j47.backgroundColor,
            selectedBackgroundColor: j47.selectedBackgroundColor,
            imageSize: j47.imageSize,
            buttonPadding: j47.buttonPadding,
            textPadding: j47.textPadding,
            localizedTextPadding: j47.localizedTextPadding,
            localizedButtonPadding: j47.localizedButtonPadding,
            backgroundBlurStyle: j47.backgroundBlurStyle,
            direction: j47.direction
        });
    }
};
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([
    Observed
], SegmentButtonOptions);

export { SegmentButtonOptions };

class MultiSelectBackground extends ViewPU {
    constructor(d47, e47, f47, g47 = -1, h47 = undefined, i47) {
        super(d47, f47, g47, i47);
        if (typeof h47 === "function") {
            this.paramsGenerator_ = h47;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(e47.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(e47.options, this, "options");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(e47);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(c47) {
        this.__optionsArray.set(c47.optionsArray);
        this.__options.set(c47.options);
    }

    updateStateVars(b47) {
        this.__optionsArray.set(b47.optionsArray);
        this.__options.set(b47.options);
    }

    purgeVariableDependenciesOnElmtId(a47) {
        this.__optionsArray.purgeDependencyOnElmtId(a47);
        this.__options.purgeDependencyOnElmtId(a47);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(a47);
        this.__buttonItemsSize.purgeDependencyOnElmtId(a47);
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

    set buttonBorderRadius(z46) {
        this.__buttonBorderRadius.set(z46);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(y46) {
        this.__buttonItemsSize.set(y46);
    }

    initialRender() {
        this.observeComponentCreation2((w46, x46) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((h46, i46) => {
            ForEach.create();
            const j46 = (l46, m46) => {
                const n46 = l46;
                this.observeComponentCreation2((p46, q46) => {
                    If.create();
                    if (m46 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((u46, v46) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[m46].height);
                                Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[m46]);
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
            this.forEachUpdateFunction(h46, this.optionsArray, j46, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SelectItem extends ViewPU {
    constructor(z45, a46, b46, c46 = -1, d46 = undefined, e46) {
        super(z45, b46, c46, e46);
        if (typeof d46 === "function") {
            this.paramsGenerator_ = d46;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(a46.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(a46.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(a46.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__selectedItemPosition = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(a46);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(y45) {
        this.__optionsArray.set(y45.optionsArray);
        this.__options.set(y45.options);
    }

    updateStateVars(x45) {
        this.__optionsArray.set(x45.optionsArray);
        this.__options.set(x45.options);
    }

    purgeVariableDependenciesOnElmtId(w45) {
        this.__optionsArray.purgeDependencyOnElmtId(w45);
        this.__options.purgeDependencyOnElmtId(w45);
        this.__selectedIndexes.purgeDependencyOnElmtId(w45);
        this.__buttonItemsSize.purgeDependencyOnElmtId(w45);
        this.__selectedItemPosition.purgeDependencyOnElmtId(w45);
        this.__zoomScaleArray.purgeDependencyOnElmtId(w45);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(w45);
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

    set selectedIndexes(v45) {
        this.__selectedIndexes.set(v45);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(u45) {
        this.__buttonItemsSize.set(u45);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(t45) {
        this.__selectedItemPosition.set(t45);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(s45) {
        this.__zoomScaleArray.set(s45);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(r45) {
        this.__buttonBorderRadius.set(r45);
    }

    initialRender() {
        this.observeComponentCreation2((k45, l45) => {
            If.create();
            if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p45, q45) => {
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
    constructor(a45, b45, c45, d45 = -1, e45 = undefined, f45) {
        super(a45, c45, d45, f45);
        if (typeof e45 === "function") {
            this.paramsGenerator_ = e45;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(b45.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(b45.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(b45.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__multiColor = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (h45, i45) => Color.Transparent), this, "multiColor");
        this.setInitiallyProvidedValue(b45);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(z44) {
        this.__optionsArray.set(z44.optionsArray);
        this.__options.set(z44.options);
        if (z44.multiColor !== undefined) {
            this.multiColor = z44.multiColor;
        }
    }

    updateStateVars(y44) {
        this.__optionsArray.set(y44.optionsArray);
        this.__options.set(y44.options);
    }

    purgeVariableDependenciesOnElmtId(x44) {
        this.__optionsArray.purgeDependencyOnElmtId(x44);
        this.__options.purgeDependencyOnElmtId(x44);
        this.__selectedIndexes.purgeDependencyOnElmtId(x44);
        this.__buttonItemsSize.purgeDependencyOnElmtId(x44);
        this.__zoomScaleArray.purgeDependencyOnElmtId(x44);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(x44);
        this.__multiColor.purgeDependencyOnElmtId(x44);
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

    set selectedIndexes(w44) {
        this.__selectedIndexes.set(w44);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(v44) {
        this.__buttonItemsSize.set(v44);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(u44) {
        this.__zoomScaleArray.set(u44);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(t44) {
        this.__buttonBorderRadius.set(t44);
    }

    get multiColor() {
        return this.__multiColor.get();
    }

    set multiColor(s44) {
        this.__multiColor.set(s44);
    }

    onOptionsChange() {
        for (let r44 = 0; r44 < this.selectedIndexes.length; r44++) {
            this.multiColor[this.selectedIndexes[r44]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    onSelectedChange() {
        for (let q44 = 0; q44 < MAX_ITEM_COUNT; q44++) {
            this.multiColor[q44] = Color.Transparent;
        }
        for (let p44 = 0; p44 < this.selectedIndexes.length; p44++) {
            this.multiColor[this.selectedIndexes[p44]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    aboutToAppear() {
        for (let o44 = 0; o44 < this.selectedIndexes.length; o44++) {
            this.multiColor[this.selectedIndexes[o44]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    initialRender() {
        this.observeComponentCreation2((m44, n44) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((x43, y43) => {
            ForEach.create();
            const z43 = (b44, c44) => {
                const d44 = b44;
                this.observeComponentCreation2((f44, g44) => {
                    If.create();
                    if (c44 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((k44, l44) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.width(this.buttonItemsSize[c44].width);
                                Stack.height(this.buttonItemsSize[c44].height);
                                Stack.backgroundColor(this.multiColor[c44]);
                                Stack.borderRadius(this.buttonBorderRadius[c44]);
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
            this.forEachUpdateFunction(x43, this.optionsArray, z43, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SegmentButtonItem extends ViewPU {
    constructor(p43, q43, r43, s43 = -1, t43 = undefined, u43) {
        super(p43, r43, s43, u43);
        if (typeof t43 === "function") {
            this.paramsGenerator_ = t43;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(q43.selectedIndexes, this, "selectedIndexes");
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(q43.focusIndex, this, "focusIndex");
        this.__itemOptions = new SynchedPropertyNesedObjectPU(q43.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(q43.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(q43.property, this, "property");
        this.__index = new SynchedPropertySimpleOneWayPU(q43.index, this, "index");
        this.groupId = "";
        this.setInitiallyProvidedValue(q43);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(o43) {
        this.__itemOptions.set(o43.itemOptions);
        this.__options.set(o43.options);
        this.__property.set(o43.property);
        if (o43.groupId !== undefined) {
            this.groupId = o43.groupId;
        }
    }

    updateStateVars(n43) {
        this.__itemOptions.set(n43.itemOptions);
        this.__options.set(n43.options);
        this.__property.set(n43.property);
        this.__index.reset(n43.index);
    }

    purgeVariableDependenciesOnElmtId(m43) {
        this.__selectedIndexes.purgeDependencyOnElmtId(m43);
        this.__focusIndex.purgeDependencyOnElmtId(m43);
        this.__itemOptions.purgeDependencyOnElmtId(m43);
        this.__options.purgeDependencyOnElmtId(m43);
        this.__property.purgeDependencyOnElmtId(m43);
        this.__index.purgeDependencyOnElmtId(m43);
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

    set selectedIndexes(l43) {
        this.__selectedIndexes.set(l43);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(k43) {
        this.__focusIndex.set(k43);
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

    set index(j43) {
        this.__index.set(j43);
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
        this.observeComponentCreation2((h43, i43) => {
            Column.create({ space: 2 });
            Column.direction(this.options.direction);
            Column.focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.getButtonPadding());
            Column.constraintSize({ minHeight: 28 });
        }, Column);
        this.observeComponentCreation2((a43, b43) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f43, g43) => {
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
        this.observeComponentCreation2((s42, t42) => {
            If.create();
            if (this.options.showText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x42, y42) => {
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
    constructor(j42, k42, l42, m42 = -1, n42 = undefined, o42) {
        super(j42, l42, m42, o42);
        if (typeof n42 === "function") {
            this.paramsGenerator_ = n42;
        }
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(k42.press, this, "press");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(k42.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__options = new SynchedPropertyNesedObjectPU(k42.options, this, "options");
        this.pressIndex = 0;
        this.pressColor = segmentButtonTheme.PRESS_COLOR;
        this.setInitiallyProvidedValue(k42);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(i42) {
        this.__colorProperty.set(i42.colorProperty);
        this.__options.set(i42.options);
        if (i42.pressIndex !== undefined) {
            this.pressIndex = i42.pressIndex;
        }
        if (i42.pressColor !== undefined) {
            this.pressColor = i42.pressColor;
        }
    }

    updateStateVars(h42) {
        this.__press.reset(h42.press);
        this.__colorProperty.set(h42.colorProperty);
        this.__options.set(h42.options);
    }

    purgeVariableDependenciesOnElmtId(g42) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(g42);
        this.__press.purgeDependencyOnElmtId(g42);
        this.__colorProperty.purgeDependencyOnElmtId(g42);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(g42);
        this.__options.purgeDependencyOnElmtId(g42);
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

    set buttonItemsSize(f42) {
        this.__buttonItemsSize.set(f42);
    }

    get press() {
        return this.__press.get();
    }

    set press(e42) {
        this.__press.set(e42);
    }

    get colorProperty() {
        return this.__colorProperty.get();
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(d42) {
        this.__buttonBorderRadius.set(d42);
    }

    get options() {
        return this.__options.get();
    }

    initialRender() {
        this.observeComponentCreation2((b42, c42) => {
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
    constructor(l41, m41, n41, o41 = -1, p41 = undefined, q41) {
        super(l41, n41, o41, q41);
        if (typeof p41 === "function") {
            this.paramsGenerator_ = p41;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(m41.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(m41.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(m41.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = this.initializeConsume("componentSize", "componentSize");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__buttonItemsPosition = this.initializeConsume("buttonItemsPosition", "buttonItemsPosition");
        this.__focusIndex = this.initializeConsume("focusIndex", "focusIndex");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonItemProperty = this.initializeConsume("buttonItemProperty", "buttonItemProperty");
        this.__buttonItemsSelected = this.initializeConsume("buttonItemsSelected", "buttonItemsSelected");
        this.__pressArray = new SynchedPropertyObjectTwoWayPU(m41.pressArray, this, "pressArray");
        this.__hoverColorArray = new SynchedPropertyObjectTwoWayPU(m41.hoverColorArray, this, "hoverColorArray");
        this.__buttonWidth = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (y41, z41) => 0), this, "buttonWidth");
        this.__buttonHeight = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (w41, x41) => 0), this, "buttonHeight");
        this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (u41, v41) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.setInitiallyProvidedValue(m41);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(k41) {
        this.__optionsArray.set(k41.optionsArray);
        this.__options.set(k41.options);
        if (k41.buttonWidth !== undefined) {
            this.buttonWidth = k41.buttonWidth;
        }
        if (k41.buttonHeight !== undefined) {
            this.buttonHeight = k41.buttonHeight;
        }
        if (k41.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = k41.buttonItemsRealHeight;
        }
        if (k41.groupId !== undefined) {
            this.groupId = k41.groupId;
        }
    }

    updateStateVars(j41) {
        this.__optionsArray.set(j41.optionsArray);
        this.__options.set(j41.options);
    }

    purgeVariableDependenciesOnElmtId(i41) {
        this.__optionsArray.purgeDependencyOnElmtId(i41);
        this.__options.purgeDependencyOnElmtId(i41);
        this.__selectedIndexes.purgeDependencyOnElmtId(i41);
        this.__componentSize.purgeDependencyOnElmtId(i41);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(i41);
        this.__buttonItemsSize.purgeDependencyOnElmtId(i41);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(i41);
        this.__focusIndex.purgeDependencyOnElmtId(i41);
        this.__zoomScaleArray.purgeDependencyOnElmtId(i41);
        this.__buttonItemProperty.purgeDependencyOnElmtId(i41);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(i41);
        this.__pressArray.purgeDependencyOnElmtId(i41);
        this.__hoverColorArray.purgeDependencyOnElmtId(i41);
        this.__buttonWidth.purgeDependencyOnElmtId(i41);
        this.__buttonHeight.purgeDependencyOnElmtId(i41);
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

    set selectedIndexes(h41) {
        this.__selectedIndexes.set(h41);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(g41) {
        this.__componentSize.set(g41);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(f41) {
        this.__buttonBorderRadius.set(f41);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(e41) {
        this.__buttonItemsSize.set(e41);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(d41) {
        this.__buttonItemsPosition.set(d41);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(c41) {
        this.__focusIndex.set(c41);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(b41) {
        this.__zoomScaleArray.set(b41);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(a41) {
        this.__buttonItemProperty.set(a41);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(z40) {
        this.__buttonItemsSelected.set(z40);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(y40) {
        this.__pressArray.set(y40);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(x40) {
        this.__hoverColorArray.set(x40);
    }

    get buttonWidth() {
        return this.__buttonWidth.get();
    }

    set buttonWidth(w40) {
        this.__buttonWidth.set(w40);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(v40) {
        this.__buttonHeight.set(v40);
    }

    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((t40, u40) => {
            this.buttonWidth[u40] = t40.width;
            this.buttonHeight[u40] = t40.height;
        });
    }

    changeSelectedIndexes(h40) {
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
            let i40 = this.selectedIndexes;
            for (let n40 = 0; n40 < this.optionsArray.deleteCount; n40++) {
                let o40 = i40.indexOf(this.optionsArray.changeStartIndex);
                let p40 = i40.map(r40 => this.optionsArray.changeStartIndex &&
                    (r40 > this.optionsArray.changeStartIndex) ? r40 - 1 : r40);
                if (o40 !== -1) {
                    p40.splice(o40, 1);
                }
                i40 = p40;
            }
            for (let j40 = 0; j40 < this.optionsArray.addLength; j40++) {
                let k40 = i40.map(m40 => this.optionsArray.changeStartIndex &&
                    (m40 >= this.optionsArray.changeStartIndex) ? m40 + 1 : m40);
                i40 = k40;
            }
            this.selectedIndexes = i40;
        }
    }

    changeFocusIndex(g40) {
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
        let f40 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 &&
            this.optionsArray.addLength !== void 0) {
            this.changeSelectedIndexes(f40);
            this.changeFocusIndex(f40);
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
        for (let e40 = 0; e40 < this.buttonItemsRealHeight.length; e40++) {
            this.buttonItemsRealHeight[e40] = 0;
        }
    }

    getBorderRadius(c40) {
        let d40 = this.buttonBorderRadius[c40];
        if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex]) {
            d40.topStart = LengthMetrics.vp((d40.topStart?.value ?? 0) + 4);
            d40.topEnd = LengthMetrics.vp((d40.topEnd?.value ?? 0) + 4);
            d40.bottomStart = LengthMetrics.vp((d40.bottomStart?.value ?? 0) + 4);
            d40.bottomEnd = LengthMetrics.vp((d40.bottomEnd?.value ?? 0) + 4);
        }
        return d40;
    }

    focusStack(u39, v39 = null) {
        this.observeComponentCreation2((a40, b40) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((y39, z39) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.borderRadius(this.getBorderRadius(u39));
            Stack.size({
                width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonWidth[u39] + 8 : this.buttonWidth[u39],
                height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonHeight[u39] + 8 : this.buttonHeight[u39]
            });
            Stack.borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR);
            Stack.borderWidth(2);
        }, Stack);
        Stack.pop();
        Stack.pop();
    }

    calculateBorderRadius() {
        let o39 = Array.from({
            length: MAX_ITEM_COUNT
        }, (s39, t39) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        });
        for (let q39 = 0; q39 < this.buttonBorderRadius.length; q39++) {
            let r39 = this.buttonItemsSize[q39].height / 2;
            if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                o39[q39].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? r39);
                o39[q39].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? r39);
                o39[q39].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? r39);
                o39[q39].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? r39);
            }
            else {
                if (q39 === 0) {
                    o39[q39].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? r39);
                    o39[q39].topEnd = LengthMetrics.vp(0);
                    o39[q39].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? r39);
                    o39[q39].bottomEnd = LengthMetrics.vp(0);
                }
                else if (this.options.buttons && q39 === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    o39[q39].topStart = LengthMetrics.vp(0);
                    o39[q39].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? r39);
                    o39[q39].bottomStart = LengthMetrics.vp(0);
                    o39[q39].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? r39);
                }
                else {
                    o39[q39].topStart = LengthMetrics.vp(0);
                    o39[q39].topEnd = LengthMetrics.vp(0);
                    o39[q39].bottomStart = LengthMetrics.vp(0);
                    o39[q39].bottomEnd = LengthMetrics.vp(0);
                }
            }
        }
        this.buttonBorderRadius = o39;
    }

    initialRender() {
        this.observeComponentCreation2((h37, i37) => {
            If.create();
            if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j39, k39) => {
                        Row.create({ space: 1 });
                        Row.direction(this.options.direction);
                        Row.focusScopeId(this.groupId, true);
                        Row.padding(this.options.componentPadding);
                        Row.onSizeChange((m39, n39) => {
                            this.componentSize = { width: n39.width, height: n39.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((n37, o37) => {
                        ForEach.create();
                        const p37 = (r37, s37) => {
                            const t37 = r37;
                            this.observeComponentCreation2((v37, w37) => {
                                If.create();
                                if (s37 < MAX_ITEM_COUNT) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((p38, q38) => {
                                            Stack.create();
                                            Stack.direction(this.options.direction);
                                            Stack.borderRadius(this.buttonBorderRadius[s37]);
                                            Stack.scale({
                                                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[s37],
                                                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[s37]
                                            });
                                            Stack.layoutWeight(1);
                                            Stack.onSizeChange((h39, i39) => {
                                                this.buttonItemsSize[s37] = {
                                                    width: i39.width,
                                                    height: this.buttonItemsSize[s37].height
                                                };
                                                if (i39.width) {
                                                    this.buttonItemsPosition[s37] = {
                                                        start: LengthMetrics.vp(Number.parseFloat(this.options.componentPadding.toString()) +
                                                            (Number.parseFloat(i39.width.toString()) + 1) * s37),
                                                        top: LengthMetrics.vp(Number.parseFloat(this.options.componentPadding.toString()))
                                                    };
                                                }
                                            });
                                            ViewStackProcessor.visualState("normal");
                                            Stack.overlay(undefined);
                                            ViewStackProcessor.visualState("focused");
                                            Stack.overlay({
                                                builder: () => {
                                                    this.focusStack.call(this, s37);
                                                }
                                            }, {
                                                align: Alignment.Center
                                            });
                                            ViewStackProcessor.visualState();
                                            Stack.onFocus(() => {
                                                this.focusIndex = s37;
                                            });
                                            Stack.onTouch((e39) => {
                                                if (e39.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (e39.type === TouchType.Down) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[s37] = 0.95;
                                                    });
                                                }
                                                else if (e39.type === TouchType.Up) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[s37] = 1;
                                                    });
                                                }
                                            });
                                            Stack.onHover((b39) => {
                                                if (b39) {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[s37].hoverColor = (segmentButtonTheme.HOVER_COLOR);
                                                    });
                                                }
                                                else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[s37].hoverColor = Color.Transparent;
                                                    });
                                                }
                                            });
                                            Stack.onMouse((w38) => {
                                                switch (w38.action) {
                                                    case MouseAction.Press:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[s37] = 0.95;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[s37] = true;
                                                        });
                                                        break;
                                                    case MouseAction.Release:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[s37] = 1;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[s37] = false;
                                                        });
                                                        break;
                                                }
                                            });
                                        }, Stack);
                                        this.observeComponentCreation2((i38, j38) => {
                                            __Common__.create();
                                            __Common__.onSizeChange((l38, m38) => {
                                                this.buttonItemsRealHeight[s37] = m38.height;
                                                let n38 = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ?
                                                this.options.buttons.length : 0));
                                                for (let o38 = 0; o38 < this.buttonItemsSize.length; o38++) {
                                                    this.buttonItemsSize[o38] = {
                                                        width: this.buttonItemsSize[o38].width,
                                                        height: n38
                                                    };
                                                }
                                                this.calculateBorderRadius();
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((c38, d38) => {
                                                if (d38) {
                                                    let e38 = new SegmentButtonItem(this, {
                                                        selectedIndexes: this.__selectedIndexes,
                                                        focusIndex: this.__focusIndex,
                                                        index: s37,
                                                        itemOptions: t37,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[s37],
                                                        groupId: this.groupId
                                                    }, undefined, c38, () => {
                                                    }, {
                                                        page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                        line: 769,
                                                        col: 15
                                                    });
                                                    ViewPU.create(e38);
                                                    let f38 = () => {
                                                        return {
                                                            selectedIndexes: this.selectedIndexes,
                                                            focusIndex: this.focusIndex,
                                                            index: s37,
                                                            itemOptions: t37,
                                                            options: this.options,
                                                            property: this.buttonItemProperty[s37],
                                                            groupId: this.groupId
                                                        };
                                                    };
                                                    e38.paramsGenerator_ = f38;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(c38, {
                                                        index: s37,
                                                        itemOptions: t37,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[s37]
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
                        this.forEachUpdateFunction(n37, this.optionsArray, p37, undefined, true, false);
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
    constructor(c36, d36, e36, f36 = -1, g36 = undefined, h36) {
        super(c36, e36, f36, h36);
        if (typeof g36 === "function") {
            this.paramsGenerator_ = g36;
        }
        this.__options = new SynchedPropertyNesedObjectPU(d36.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(d36.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, "componentSize");
        this.addProvidedVar("componentSize", this.__componentSize, false);
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (e37, f37) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        }), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.__buttonBorderRadius, false);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (c37, d37) => {
            return {};
        }), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.__buttonItemsSize, false);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (a37, b37) => {
            return {};
        }), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.__buttonItemsPosition, false);
        this.__buttonItemsSelected = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (y36, z36) => false), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected, false);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (w36, x36) => new ItemProperty()), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty, false);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex, false);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition, false);
        this.__zoomScaleArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (u36, v36) => 1.0), this, "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.__zoomScaleArray, false);
        this.__pressArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (s36, t36) => false), this, "pressArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (q36, r36) => new HoverColorProperty()), this, "hoverColorArray");
        this.doSelectedChangeAnimate = false;
        this.isCurrentPositionSelected = false;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = false;
        this.__shouldMirror = new ObservedPropertySimplePU(false, this, "shouldMirror");
        this.setInitiallyProvidedValue(d36);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.declareWatch("buttonItemsPosition", this.onItemsPositionChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(b36) {
        this.__options.set(b36.options);
        if (b36.componentSize !== undefined) {
            this.componentSize = b36.componentSize;
        }
        if (b36.buttonBorderRadius !== undefined) {
            this.buttonBorderRadius = b36.buttonBorderRadius;
        }
        if (b36.buttonItemsSize !== undefined) {
            this.buttonItemsSize = b36.buttonItemsSize;
        }
        if (b36.buttonItemsPosition !== undefined) {
            this.buttonItemsPosition = b36.buttonItemsPosition;
        }
        if (b36.buttonItemsSelected !== undefined) {
            this.buttonItemsSelected = b36.buttonItemsSelected;
        }
        if (b36.buttonItemProperty !== undefined) {
            this.buttonItemProperty = b36.buttonItemProperty;
        }
        if (b36.focusIndex !== undefined) {
            this.focusIndex = b36.focusIndex;
        }
        if (b36.selectedItemPosition !== undefined) {
            this.selectedItemPosition = b36.selectedItemPosition;
        }
        if (b36.zoomScaleArray !== undefined) {
            this.zoomScaleArray = b36.zoomScaleArray;
        }
        if (b36.pressArray !== undefined) {
            this.pressArray = b36.pressArray;
        }
        if (b36.hoverColorArray !== undefined) {
            this.hoverColorArray = b36.hoverColorArray;
        }
        if (b36.doSelectedChangeAnimate !== undefined) {
            this.doSelectedChangeAnimate = b36.doSelectedChangeAnimate;
        }
        if (b36.isCurrentPositionSelected !== undefined) {
            this.isCurrentPositionSelected = b36.isCurrentPositionSelected;
        }
        if (b36.panGestureStartPoint !== undefined) {
            this.panGestureStartPoint = b36.panGestureStartPoint;
        }
        if (b36.isPanGestureMoved !== undefined) {
            this.isPanGestureMoved = b36.isPanGestureMoved;
        }
        if (b36.shouldMirror !== undefined) {
            this.shouldMirror = b36.shouldMirror;
        }
    }

    updateStateVars(a36) {
        this.__options.set(a36.options);
    }

    purgeVariableDependenciesOnElmtId(z35) {
        this.__options.purgeDependencyOnElmtId(z35);
        this.__selectedIndexes.purgeDependencyOnElmtId(z35);
        this.__componentSize.purgeDependencyOnElmtId(z35);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(z35);
        this.__buttonItemsSize.purgeDependencyOnElmtId(z35);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(z35);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(z35);
        this.__buttonItemProperty.purgeDependencyOnElmtId(z35);
        this.__focusIndex.purgeDependencyOnElmtId(z35);
        this.__selectedItemPosition.purgeDependencyOnElmtId(z35);
        this.__zoomScaleArray.purgeDependencyOnElmtId(z35);
        this.__pressArray.purgeDependencyOnElmtId(z35);
        this.__hoverColorArray.purgeDependencyOnElmtId(z35);
        this.__shouldMirror.purgeDependencyOnElmtId(z35);
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

    set selectedIndexes(y35) {
        this.__selectedIndexes.set(y35);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(x35) {
        this.__componentSize.set(x35);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(w35) {
        this.__buttonBorderRadius.set(w35);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(v35) {
        this.__buttonItemsSize.set(v35);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(u35) {
        this.__buttonItemsPosition.set(u35);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(t35) {
        this.__buttonItemsSelected.set(t35);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(s35) {
        this.__buttonItemProperty.set(s35);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(r35) {
        this.__focusIndex.set(r35);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(q35) {
        this.__selectedItemPosition.set(q35);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(p35) {
        this.__zoomScaleArray.set(p35);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(o35) {
        this.__pressArray.set(o35);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(n35) {
        this.__hoverColorArray.set(n35);
    }

    get shouldMirror() {
        return this.__shouldMirror.get();
    }

    set shouldMirror(m35) {
        this.__shouldMirror.set(m35);
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
        this.buttonItemsSelected.forEach((k35, l35) => {
            this.buttonItemsSelected[l35] = false;
        });
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            this.selectedIndexes.forEach(j35 => this.buttonItemsSelected[j35] = true);
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
        let e35 = this.selectedIndexes.some(g35 => {
            return (g35 === void 0 || g35 < 0 || (this.options.buttons && g35 >= this.options.buttons.length));
        });
        if (e35) {
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

    isMouseWheelScroll(c35) {
        return c35.source === SourceType.Mouse && !this.isPanGestureMoved;
    }

    isMovedFromPanGestureStartPoint(a35, b35) {
        return!nearEqual(a35, this.panGestureStartPoint.x) || !nearEqual(b35, this.panGestureStartPoint.y);
    }

    isShouldMirror() {
        if (this.options.direction == Direction.Rtl) {
            return true;
        }
        try {
            let z34 = I18n.System.getSystemLanguage();
            if (z34 === 'ug' && this.options.direction != Direction.Ltr) {
                return true;
            }
        }
        catch (y34) {
            console.error(`Ace SegmentButton getSystemLanguage, error: ${y34.toString()}`);
        }
        return false;
    }

    initialRender() {
        this.observeComponentCreation2((p33, q33) => {
            Stack.create();
            Stack.direction(this.options ? this.options.direction : undefined);
            Stack.onBlur(() => {
                this.focusIndex = -1;
            });
            Stack.onKeyEvent((x34) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (x34.type === KeyType.Down) {
                    if (x34.keyCode === KeyCode.KEYCODE_SPACE || x34.keyCode === KeyCode.KEYCODE_ENTER ||
                        x34.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
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
            TapGesture.onAction((q34) => {
                this.focusIndex = -1;
                let r34 = q34.fingerList.find(Boolean);
                if (r34 === void 0) {
                    return;
                }
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                let s34 = r34.localX;
                let t34 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
                for (let u34 = 0; u34 < t34; u34++) {
                    s34 = s34 - this.buttonItemsSize[u34].width;
                    if (s34 >= 0) {
                        continue;
                    }
                    this.doSelectedChangeAnimate =
                        this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ? false : true;
                    let v34 = this.isShouldMirror() ? t34 - 1 - u34 : u34;
                    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                        let w34 = this.selectedIndexes.indexOf(v34);
                        if (w34 === -1) {
                            this.selectedIndexes.push(v34);
                        }
                        else {
                            this.selectedIndexes.splice(w34, 1);
                        }
                    }
                    else {
                        this.selectedIndexes[0] = v34;
                    }
                    this.doSelectedChangeAnimate = false;
                    break;
                }
            });
            TapGesture.pop();
            SwipeGesture.create();
            SwipeGesture.onAction((p34) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (this.isCurrentPositionSelected) {
                    return;
                }
                if (p34.angle > 0 && this.selectedIndexes[0] !== Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
                    this.doSelectedChangeAnimate = false;
                }
                else if (p34.angle < 0 && this.selectedIndexes[0] !== 0) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
                    this.doSelectedChangeAnimate = false;
                }
            });
            SwipeGesture.pop();
            PanGesture.create();
            PanGesture.onActionStart((l34) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let m34 = l34.fingerList.find(Boolean);
                if (m34 === void 0) {
                    return;
                }
                let n34 = m34.localX;
                this.panGestureStartPoint = { x: m34.globalX, y: m34.globalY };
                this.isPanGestureMoved = false;
                for (let o34 = 0; o34 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); o34++) {
                    n34 = n34 - this.buttonItemsSize[o34].width;
                    if (n34 < 0) {
                        this.isCurrentPositionSelected = o34 === this.selectedIndexes[0] ? true : false;
                        break;
                    }
                }
            });
            PanGesture.onActionUpdate((c34) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (!this.isCurrentPositionSelected) {
                    return;
                }
                let d34 = c34.fingerList.find(Boolean);
                if (d34 === void 0) {
                    return;
                }
                let e34 = d34.localX;
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(d34.globalX, d34.globalY)) {
                    this.isPanGestureMoved = true;
                }
                for (let k34 = 0; k34 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); k34++) {
                    e34 = e34 - this.buttonItemsSize[k34].width;
                    if (e34 < 0) {
                        this.doSelectedChangeAnimate = true;
                        this.selectedIndexes[0] = k34;
                        this.doSelectedChangeAnimate = false;
                        break;
                    }
                }
                this.zoomScaleArray.forEach((g34, h34) => {
                    if (h34 === this.selectedIndexes[0]) {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[h34] = 0.95;
                        });
                    }
                    else {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[h34] = 1;
                        });
                    }
                });
            });
            PanGesture.onActionEnd((y33) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let z33 = y33.fingerList.find(Boolean);
                if (z33 === void 0) {
                    return;
                }
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(z33.globalX, z33.globalY)) {
                    this.isPanGestureMoved = true;
                }
                if (this.isMouseWheelScroll(y33)) {
                    let b34 = y33.offsetX !== 0 ? y33.offsetX : y33.offsetY;
                    this.doSelectedChangeAnimate = true;
                    if (b34 > 0 && this.selectedIndexes[0] > 0) {
                        this.selectedIndexes[0] -= 1;
                    }
                    else if (b34 < 0 && this.selectedIndexes[0] < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
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
        this.observeComponentCreation2((o30, p30) => {
            If.create();
            if (this.options !== void 0 && this.options.buttons != void 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w31, x31) => {
                        If.create();
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                {
                                    this.observeComponentCreation2((j33, k33) => {
                                        if (k33) {
                                            let l33 = new MultiSelectBackground(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                            }, undefined, j33, () => {
                                            }, {
                                                page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                line: 1043,
                                                col: 11
                                            });
                                            ViewPU.create(l33);
                                            let m33 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options
                                                };
                                            };
                                            l33.paramsGenerator_ = m33;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(j33, {
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
                                this.observeComponentCreation2((f33, g33) => {
                                    Stack.create();
                                    Stack.direction(this.options.direction);
                                    Stack.size(ObservedObject.GetRawObject(this.componentSize));
                                    Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                                    Stack.borderRadius(this.options.iconTextBackgroundRadius ?? this.componentSize.height / 2);
                                    Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
                                }, Stack);
                                this.observeComponentCreation2((b32, c32) => {
                                    If.create();
                                    if (this.options.buttons !== void 0 && this.options.buttons.length > 1) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((d33, e33) => {
                                                Row.create({ space: 1 });
                                            }, Row);
                                            this.observeComponentCreation2((h32, i32) => {
                                                ForEach.create();
                                                const j32 = (l32, m32) => {
                                                    const n32 = l32;
                                                    this.observeComponentCreation2((p32, q32) => {
                                                        If.create();
                                                        if (m32 < MAX_ITEM_COUNT) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.observeComponentCreation2((b33, c33) => {
                                                                    Stack.create();
                                                                    Stack.scale({
                                                                        x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[m32],
                                                                        y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[m32]
                                                                    });
                                                                }, Stack);
                                                                {
                                                                    this.observeComponentCreation2((v32, w32) => {
                                                                        if (w32) {
                                                                            let x32 = new PressAndHoverEffect(this, {
                                                                                pressIndex: m32,
                                                                                colorProperty: this.hoverColorArray[m32],
                                                                                press: this.pressArray[m32],
                                                                                options: this.options,
                                                                            }, undefined, v32, () => {
                                                                            }, {
                                                                                page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                                                line: 1054,
                                                                                col: 23
                                                                            });
                                                                            ViewPU.create(x32);
                                                                            let y32 = () => {
                                                                                return {
                                                                                    pressIndex: m32,
                                                                                    colorProperty: this.hoverColorArray[m32],
                                                                                    press: this.pressArray[m32],
                                                                                    options: this.options
                                                                                };
                                                                            };
                                                                            x32.paramsGenerator_ = y32;
                                                                        }
                                                                        else {
                                                                            this.updateStateVarsOfChildByElmtId(v32, {
                                                                                colorProperty: this.hoverColorArray[m32],
                                                                                press: this.pressArray[m32],
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
                                                this.forEachUpdateFunction(h32, this.options.buttons, j32, undefined, true, false);
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
                    this.observeComponentCreation2((u31, v31) => {
                        Stack.create();
                        Stack.direction(this.options.direction);
                        Stack.size(ObservedObject.GetRawObject(this.componentSize));
                        Stack.borderRadius((this.options.type === 'capsule' && (this.options.multiply ?? false) ?
                        this.options.iconTextRadius : this.options.iconTextBackgroundRadius) ??
                            this.componentSize.height / 2);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((c31, d31) => {
                        If.create();
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                {
                                    this.observeComponentCreation2((o31, p31) => {
                                        if (p31) {
                                            let q31 = new MultiSelectItemArray(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, o31, () => {
                                            }, {
                                                page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                line: 1078,
                                                col: 13
                                            });
                                            ViewPU.create(q31);
                                            let r31 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            q31.paramsGenerator_ = r31;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(o31, {
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
                                    this.observeComponentCreation2((g31, h31) => {
                                        if (h31) {
                                            let i31 = new SelectItem(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, g31, () => {
                                            }, {
                                                page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                line: 1084,
                                                col: 13
                                            });
                                            ViewPU.create(i31);
                                            let j31 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            i31.paramsGenerator_ = j31;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(g31, {
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
                        this.observeComponentCreation2((w30, x30) => {
                            if (x30) {
                                let y30 = new SegmentButtonItemArrayComponent(this, {
                                    pressArray: this.__pressArray,
                                    hoverColorArray: this.__hoverColorArray,
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    selectedIndexes: this.__selectedIndexes,
                                }, undefined, w30, () => {
                                }, {
                                    page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                    line: 1098,
                                    col: 9
                                });
                                ViewPU.create(y30);
                                let z30 = () => {
                                    return {
                                        pressArray: this.pressArray,
                                        hoverColorArray: this.hoverColorArray,
                                        optionsArray: this.options.buttons,
                                        options: this.options,
                                        selectedIndexes: this.selectedIndexes
                                    };
                                };
                                y30.paramsGenerator_ = z30;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(w30, {
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

    updateAnimatedProperty(d30) {
        let e30 = () => {
            this.selectedItemPosition = this.selectedIndexes.length === 0 ? {
            } : this.buttonItemsPosition[this.selectedIndexes[0]];
            this.buttonItemsSelected.forEach((k30, l30) => {
                this.buttonItemProperty[l30].fontColor = k30 ?
                    this.options.selectedFontColor ?? (this.options.type === 'tab' ?
                    segmentButtonTheme.TAB_SELECTED_FONT_COLOR : segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR) :
                    this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
            });
        };
        if (d30) {
            Context.animateTo({ curve: d30 }, e30);
        }
        else {
            e30();
        }
        this.buttonItemsSelected.forEach((h30, i30) => {
            this.buttonItemProperty[i30].fontSize = h30 ? this.options.selectedFontSize ??
            segmentButtonTheme.SELECTED_FONT_SIZE : this.options.fontSize ?? segmentButtonTheme.FONT_SIZE;
            this.buttonItemProperty[i30].fontWeight = h30 ? this.options.selectedFontWeight ?? FontWeight.Medium :
                this.options.fontWeight ?? FontWeight.Regular;
            this.buttonItemProperty[i30].isSelected = h30;
        });
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    SegmentButton, SegmentButtonOptions, SegmentButtonItemOptionsArray, SegmentButtonItemOptions
};