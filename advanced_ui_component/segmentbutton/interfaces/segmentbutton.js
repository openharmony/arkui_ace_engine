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

var __decorate = (this && this.__decorate) || function (i47, j47, k47, l47) {
    var m47 = arguments.length,
        n47 = m47 < 3 ? j47 : l47 === null ? l47 = Object.getOwnPropertyDescriptor(j47, k47) : l47, o47;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        n47 = Reflect.decorate(i47, j47, k47, l47);
    else
        for (var p47 = i47.length - 1; p47 >= 0; p47--)
            if (o47 = i47[p47])
                n47 = (m47 < 3 ? o47(n47) : m47 > 3 ? o47(j47, k47, n47) : o47(j47, k47)) || n47;
    return m47 > 3 && n47 && Object.defineProperty(j47, k47, n47), n47;
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

function nearEqual(f47, g47) {
    return Math.abs(f47 - g47) < 0.001;
}

let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(e47) {
        this.icon = e47.icon;
        this.selectedIcon = e47.selectedIcon;
        this.text = e47.text;
    }
};
SegmentButtonItemOptions = __decorate([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends Array {
    constructor(b47) {
        super(typeof b47 === "number" ? b47 : 0);
        this.changeStartIndex = void 0;
        this.deleteCount = void 0;
        this.addLength = void 0;
        if (typeof b47 !== "number" && b47 !== void 0) {
            super.push(...b47.map((d47) => new SegmentButtonItemOptions(d47)));
        }
    }

    push(...y46) {
        if (this.length + y46.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        this.changeStartIndex = this.length;
        this.deleteCount = 0;
        this.addLength = y46.length;
        return super.push(...y46.map((a47) => new SegmentButtonItemOptions(a47)));
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

    unshift(...v46) {
        if (this.length + v46.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        if (v46.length > 0) {
            this.changeStartIndex = 0;
            this.deleteCount = 0;
            this.addLength = v46.length;
        }
        return super.unshift(...v46.map((x46) => new SegmentButtonItemOptions(x46)));
    }

    splice(r46, s46, ...t46) {
        let u46 = (this.length - s46) < 0 ? 0 : (this.length - s46);
        u46 += t46.length;
        if (u46 < MIN_ITEM_COUNT) {
            console.warn("Below the minimum number of elements (2).");
            return [];
        }
        if (u46 > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return [];
        }
        this.changeStartIndex = r46;
        this.deleteCount = s46;
        this.addLength = t46.length;
        return super.splice(r46, s46, ...t46);
    }

    static create(q46) {
        return new SegmentButtonItemOptionsArray_1(q46);
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

    set buttons(p46) {
        if (this._buttons !== void 0 && this._buttons !== p46) {
            this.onButtonsChange?.();
        }
        this._buttons = p46;
    }

    constructor(m46) {
        this.multiply = false;
        this.showText = false;
        this.showIcon = false;
        this._buttons = void 0;
        this.fontColor = m46.fontColor ?? segmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = m46.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = m46.fontSize ?? segmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = m46.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = m46.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = m46.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = m46.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = m46.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = m46.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = m46.buttonPadding;
        this.textPadding = m46.textPadding;
        this.type = m46.type;
        this.backgroundBlurStyle = m46.backgroundBlurStyle ?? segmentButtonTheme.BACKGROUND_BLUR_STYLE;
        this.localizedTextPadding = m46.localizedTextPadding;
        this.localizedButtonPadding = m46.localizedButtonPadding;
        this.direction = m46.direction ?? Direction.Auto;
        this.buttons = new SegmentButtonItemOptionsArray(m46.buttons);
        if (this.type === "capsule") {
            this.multiply = m46.multiply ?? false;
            this.buttons.forEach(o46 => {
                this.showText ||= o46.text !== void 0;
                this.showIcon ||= o46.icon !== void 0 || o46.selectedIcon !== void 0;
            });
            if (this.showText && this.showIcon) {
                this.iconTextRadius = 12;
                this.iconTextBackgroundRadius = 14;
            }
            this.selectedFontColor = m46.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = m46.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
        else {
            this.showText = true;
        }
        this.componentPadding = this.multiply ? 0 : 2;
    }

    static tab(l46) {
        return new SegmentButtonOptions_1({
            type: "tab",
            buttons: l46.buttons,
            fontColor: l46.fontColor,
            selectedFontColor: l46.selectedFontColor,
            fontSize: l46.fontSize,
            selectedFontSize: l46.selectedFontSize,
            fontWeight: l46.fontWeight,
            selectedFontWeight: l46.selectedFontWeight,
            backgroundColor: l46.backgroundColor,
            selectedBackgroundColor: l46.selectedBackgroundColor,
            imageSize: l46.imageSize,
            buttonPadding: l46.buttonPadding,
            textPadding: l46.textPadding,
            localizedTextPadding: l46.localizedTextPadding,
            localizedButtonPadding: l46.localizedButtonPadding,
            backgroundBlurStyle: l46.backgroundBlurStyle,
            direction: l46.direction
        });
    }

    static capsule(k46) {
        return new SegmentButtonOptions_1({
            type: "capsule",
            buttons: k46.buttons,
            multiply: k46.multiply,
            fontColor: k46.fontColor,
            selectedFontColor: k46.selectedFontColor,
            fontSize: k46.fontSize,
            selectedFontSize: k46.selectedFontSize,
            fontWeight: k46.fontWeight,
            selectedFontWeight: k46.selectedFontWeight,
            backgroundColor: k46.backgroundColor,
            selectedBackgroundColor: k46.selectedBackgroundColor,
            imageSize: k46.imageSize,
            buttonPadding: k46.buttonPadding,
            textPadding: k46.textPadding,
            localizedTextPadding: k46.localizedTextPadding,
            localizedButtonPadding: k46.localizedButtonPadding,
            backgroundBlurStyle: k46.backgroundBlurStyle,
            direction: k46.direction
        });
    }
};
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([
    Observed
], SegmentButtonOptions);

export { SegmentButtonOptions };

class MultiSelectBackground extends ViewPU {
    constructor(e46, f46, g46, h46 = -1, i46 = undefined, j46) {
        super(e46, g46, h46, j46);
        if (typeof i46 === "function") {
            this.paramsGenerator_ = i46;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(f46.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(f46.options, this, "options");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(f46);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(d46) {
        this.__optionsArray.set(d46.optionsArray);
        this.__options.set(d46.options);
    }

    updateStateVars(c46) {
        this.__optionsArray.set(c46.optionsArray);
        this.__options.set(c46.options);
    }

    purgeVariableDependenciesOnElmtId(b46) {
        this.__optionsArray.purgeDependencyOnElmtId(b46);
        this.__options.purgeDependencyOnElmtId(b46);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(b46);
        this.__buttonItemsSize.purgeDependencyOnElmtId(b46);
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

    set buttonBorderRadius(a46) {
        this.__buttonBorderRadius.set(a46);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(z45) {
        this.__buttonItemsSize.set(z45);
    }

    initialRender() {
        this.observeComponentCreation2((x45, y45) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((i45, j45) => {
            ForEach.create();
            const k45 = (m45, n45) => {
                const o45 = m45;
                this.observeComponentCreation2((q45, r45) => {
                    If.create();
                    if (n45 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((v45, w45) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[n45].height);
                                Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[n45]);
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
            this.forEachUpdateFunction(i45, this.optionsArray, k45, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SelectItem extends ViewPU {
    constructor(a45, b45, c45, d45 = -1, e45 = undefined, f45) {
        super(a45, c45, d45, f45);
        if (typeof e45 === "function") {
            this.paramsGenerator_ = e45;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(b45.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(b45.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(b45.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__selectedItemPosition = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(b45);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(z44) {
        this.__optionsArray.set(z44.optionsArray);
        this.__options.set(z44.options);
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
        this.__selectedItemPosition.purgeDependencyOnElmtId(x44);
        this.__zoomScaleArray.purgeDependencyOnElmtId(x44);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(x44);
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

    set selectedIndexes(w44) {
        this.__selectedIndexes.set(w44);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(v44) {
        this.__buttonItemsSize.set(v44);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(u44) {
        this.__selectedItemPosition.set(u44);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(t44) {
        this.__zoomScaleArray.set(t44);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(s44) {
        this.__buttonBorderRadius.set(s44);
    }

    initialRender() {
        this.observeComponentCreation2((l44, m44) => {
            If.create();
            if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q44, r44) => {
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
    constructor(b44, c44, d44, e44 = -1, f44 = undefined, g44) {
        super(b44, d44, e44, g44);
        if (typeof f44 === "function") {
            this.paramsGenerator_ = f44;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(c44.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(c44.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(c44.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__multiColor = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (i44, j44) => Color.Transparent), this, "multiColor");
        this.setInitiallyProvidedValue(c44);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(a44) {
        this.__optionsArray.set(a44.optionsArray);
        this.__options.set(a44.options);
        if (a44.multiColor !== undefined) {
            this.multiColor = a44.multiColor;
        }
    }

    updateStateVars(z43) {
        this.__optionsArray.set(z43.optionsArray);
        this.__options.set(z43.options);
    }

    purgeVariableDependenciesOnElmtId(y43) {
        this.__optionsArray.purgeDependencyOnElmtId(y43);
        this.__options.purgeDependencyOnElmtId(y43);
        this.__selectedIndexes.purgeDependencyOnElmtId(y43);
        this.__buttonItemsSize.purgeDependencyOnElmtId(y43);
        this.__zoomScaleArray.purgeDependencyOnElmtId(y43);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(y43);
        this.__multiColor.purgeDependencyOnElmtId(y43);
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

    set selectedIndexes(x43) {
        this.__selectedIndexes.set(x43);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(w43) {
        this.__buttonItemsSize.set(w43);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(v43) {
        this.__zoomScaleArray.set(v43);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(u43) {
        this.__buttonBorderRadius.set(u43);
    }

    get multiColor() {
        return this.__multiColor.get();
    }

    set multiColor(t43) {
        this.__multiColor.set(t43);
    }

    onOptionsChange() {
        for (let s43 = 0; s43 < this.selectedIndexes.length; s43++) {
            this.multiColor[this.selectedIndexes[s43]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    onSelectedChange() {
        for (let r43 = 0; r43 < MAX_ITEM_COUNT; r43++) {
            this.multiColor[r43] = Color.Transparent;
        }
        for (let q43 = 0; q43 < this.selectedIndexes.length; q43++) {
            this.multiColor[this.selectedIndexes[q43]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    aboutToAppear() {
        for (let p43 = 0; p43 < this.selectedIndexes.length; p43++) {
            this.multiColor[this.selectedIndexes[p43]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    initialRender() {
        this.observeComponentCreation2((n43, o43) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((y42, z42) => {
            ForEach.create();
            const a43 = (c43, d43) => {
                const e43 = c43;
                this.observeComponentCreation2((g43, h43) => {
                    If.create();
                    if (d43 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((l43, m43) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.width(this.buttonItemsSize[d43].width);
                                Stack.height(this.buttonItemsSize[d43].height);
                                Stack.backgroundColor(this.multiColor[d43]);
                                Stack.borderRadius(this.buttonBorderRadius[d43]);
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
            this.forEachUpdateFunction(y42, this.optionsArray, a43, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SegmentButtonItem extends ViewPU {
    constructor(q42, r42, s42, t42 = -1, u42 = undefined, v42) {
        super(q42, s42, t42, v42);
        if (typeof u42 === "function") {
            this.paramsGenerator_ = u42;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(r42.selectedIndexes, this, "selectedIndexes");
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(r42.focusIndex, this, "focusIndex");
        this.__itemOptions = new SynchedPropertyNesedObjectPU(r42.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(r42.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(r42.property, this, "property");
        this.__index = new SynchedPropertySimpleOneWayPU(r42.index, this, "index");
        this.groupId = "";
        this.setInitiallyProvidedValue(r42);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(p42) {
        this.__itemOptions.set(p42.itemOptions);
        this.__options.set(p42.options);
        this.__property.set(p42.property);
        if (p42.groupId !== undefined) {
            this.groupId = p42.groupId;
        }
    }

    updateStateVars(o42) {
        this.__itemOptions.set(o42.itemOptions);
        this.__options.set(o42.options);
        this.__property.set(o42.property);
        this.__index.reset(o42.index);
    }

    purgeVariableDependenciesOnElmtId(n42) {
        this.__selectedIndexes.purgeDependencyOnElmtId(n42);
        this.__focusIndex.purgeDependencyOnElmtId(n42);
        this.__itemOptions.purgeDependencyOnElmtId(n42);
        this.__options.purgeDependencyOnElmtId(n42);
        this.__property.purgeDependencyOnElmtId(n42);
        this.__index.purgeDependencyOnElmtId(n42);
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

    set selectedIndexes(m42) {
        this.__selectedIndexes.set(m42);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(l42) {
        this.__focusIndex.set(l42);
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

    set index(k42) {
        this.__index.set(k42);
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
        this.observeComponentCreation2((i42, j42) => {
            Column.create({ space: 2 });
            Column.direction(this.options.direction);
            Column.focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.getButtonPadding());
            Column.constraintSize({ minHeight: 28 });
        }, Column);
        this.observeComponentCreation2((b42, c42) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g42, h42) => {
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
        this.observeComponentCreation2((t41, u41) => {
            If.create();
            if (this.options.showText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y41, z41) => {
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
    constructor(k41, l41, m41, n41 = -1, o41 = undefined, p41) {
        super(k41, m41, n41, p41);
        if (typeof o41 === "function") {
            this.paramsGenerator_ = o41;
        }
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(l41.press, this, "press");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(l41.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__options = new SynchedPropertyNesedObjectPU(l41.options, this, "options");
        this.pressIndex = 0;
        this.pressColor = segmentButtonTheme.PRESS_COLOR;
        this.setInitiallyProvidedValue(l41);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(j41) {
        this.__colorProperty.set(j41.colorProperty);
        this.__options.set(j41.options);
        if (j41.pressIndex !== undefined) {
            this.pressIndex = j41.pressIndex;
        }
        if (j41.pressColor !== undefined) {
            this.pressColor = j41.pressColor;
        }
    }

    updateStateVars(i41) {
        this.__press.reset(i41.press);
        this.__colorProperty.set(i41.colorProperty);
        this.__options.set(i41.options);
    }

    purgeVariableDependenciesOnElmtId(h41) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(h41);
        this.__press.purgeDependencyOnElmtId(h41);
        this.__colorProperty.purgeDependencyOnElmtId(h41);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(h41);
        this.__options.purgeDependencyOnElmtId(h41);
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

    set buttonItemsSize(g41) {
        this.__buttonItemsSize.set(g41);
    }

    get press() {
        return this.__press.get();
    }

    set press(f41) {
        this.__press.set(f41);
    }

    get colorProperty() {
        return this.__colorProperty.get();
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(e41) {
        this.__buttonBorderRadius.set(e41);
    }

    get options() {
        return this.__options.get();
    }

    initialRender() {
        this.observeComponentCreation2((c41, d41) => {
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
    constructor(g40, h40, i40, j40 = -1, k40 = undefined, l40) {
        super(g40, i40, j40, l40);
        if (typeof k40 === "function") {
            this.paramsGenerator_ = k40;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(h40.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(h40.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(h40.selectedIndexes, this, "selectedIndexes");
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
        }, (z40, a41) => false), this, "pressArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (x40, y40) => new HoverColorProperty()), this, "hoverColorArray");
        this.__buttonWidth = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (v40, w40) => 0), this, "buttonWidth");
        this.__buttonHeight = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (t40, u40) => 0), this, "buttonHeight");
        this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (r40, s40) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.setInitiallyProvidedValue(h40);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(f40) {
        this.__optionsArray.set(f40.optionsArray);
        this.__options.set(f40.options);
        if (f40.pressArray !== undefined) {
            this.pressArray = f40.pressArray;
        }
        if (f40.hoverColorArray !== undefined) {
            this.hoverColorArray = f40.hoverColorArray;
        }
        if (f40.buttonWidth !== undefined) {
            this.buttonWidth = f40.buttonWidth;
        }
        if (f40.buttonHeight !== undefined) {
            this.buttonHeight = f40.buttonHeight;
        }
        if (f40.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = f40.buttonItemsRealHeight;
        }
        if (f40.groupId !== undefined) {
            this.groupId = f40.groupId;
        }
    }

    updateStateVars(e40) {
        this.__optionsArray.set(e40.optionsArray);
        this.__options.set(e40.options);
    }

    purgeVariableDependenciesOnElmtId(d40) {
        this.__optionsArray.purgeDependencyOnElmtId(d40);
        this.__options.purgeDependencyOnElmtId(d40);
        this.__selectedIndexes.purgeDependencyOnElmtId(d40);
        this.__componentSize.purgeDependencyOnElmtId(d40);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(d40);
        this.__buttonItemsSize.purgeDependencyOnElmtId(d40);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(d40);
        this.__focusIndex.purgeDependencyOnElmtId(d40);
        this.__zoomScaleArray.purgeDependencyOnElmtId(d40);
        this.__buttonItemProperty.purgeDependencyOnElmtId(d40);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(d40);
        this.__pressArray.purgeDependencyOnElmtId(d40);
        this.__hoverColorArray.purgeDependencyOnElmtId(d40);
        this.__buttonWidth.purgeDependencyOnElmtId(d40);
        this.__buttonHeight.purgeDependencyOnElmtId(d40);
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

    set selectedIndexes(c40) {
        this.__selectedIndexes.set(c40);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(b40) {
        this.__componentSize.set(b40);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(a40) {
        this.__buttonBorderRadius.set(a40);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(z39) {
        this.__buttonItemsSize.set(z39);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(y39) {
        this.__buttonItemsPosition.set(y39);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(x39) {
        this.__focusIndex.set(x39);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(w39) {
        this.__zoomScaleArray.set(w39);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(v39) {
        this.__buttonItemProperty.set(v39);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(u39) {
        this.__buttonItemsSelected.set(u39);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(t39) {
        this.__pressArray.set(t39);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(s39) {
        this.__hoverColorArray.set(s39);
    }

    get buttonWidth() {
        return this.__buttonWidth.get();
    }

    set buttonWidth(r39) {
        this.__buttonWidth.set(r39);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(q39) {
        this.__buttonHeight.set(q39);
    }

    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((o39, p39) => {
            this.buttonWidth[p39] = o39.width;
            this.buttonHeight[p39] = o39.height;
        });
    }

    changeSelectedIndexes(c39) {
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
            let d39 = this.selectedIndexes;
            for (let i39 = 0; i39 < this.optionsArray.deleteCount; i39++) {
                let j39 = d39.indexOf(this.optionsArray.changeStartIndex);
                let k39 = d39.map(m39 => this.optionsArray.changeStartIndex &&
                    (m39 > this.optionsArray.changeStartIndex) ? m39 - 1 : m39);
                if (j39 !== -1) {
                    k39.splice(j39, 1);
                }
                d39 = k39;
            }
            for (let e39 = 0; e39 < this.optionsArray.addLength; e39++) {
                let f39 = d39.map(h39 => this.optionsArray.changeStartIndex &&
                    (h39 >= this.optionsArray.changeStartIndex) ? h39 + 1 : h39);
                d39 = f39;
            }
            this.selectedIndexes = d39;
        }
    }

    changeFocusIndex(b39) {
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
        let a39 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 &&
            this.optionsArray.addLength !== void 0) {
            this.changeSelectedIndexes(a39);
            this.changeFocusIndex(a39);
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
        for (let z38 = 0; z38 < this.buttonItemsRealHeight.length; z38++) {
            this.buttonItemsRealHeight[z38] = 0;
        }
    }

    getBorderRadius(x38) {
        let y38 = this.buttonBorderRadius[x38];
        if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex]) {
            y38.topStart = LengthMetrics.vp(y38.topStart.value + 4);
            y38.topEnd = LengthMetrics.vp(y38.topEnd.value + 4);
            y38.bottomStart = LengthMetrics.vp(y38.bottomStart.value + 4);
            y38.bottomEnd = LengthMetrics.vp(y38.bottomEnd.value + 4);
        }
        return y38;
    }

    focusStack(p38, q38 = null) {
        this.observeComponentCreation2((v38, w38) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((t38, u38) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.borderRadius(this.getBorderRadius(p38));
            Stack.size({
                width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonWidth[p38] + 8 : this.buttonWidth[p38],
                height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonHeight[p38] + 8 : this.buttonHeight[p38]
            });
            Stack.borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR);
            Stack.borderWidth(2);
        }, Stack);
        Stack.pop();
        Stack.pop();
    }

    calculateBorderRadius() {
        let j38 = Array.from({
            length: MAX_ITEM_COUNT
        }, (n38, o38) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        });
        for (let l38 = 0; l38 < this.buttonBorderRadius.length; l38++) {
            let m38 = this.buttonItemsSize[l38].height / 2;
            if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                j38[l38].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? m38);
                j38[l38].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? m38);
                j38[l38].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? m38);
                j38[l38].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? m38);
            }
            else {
                if (l38 === 0) {
                    j38[l38].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? m38);
                    j38[l38].topEnd = LengthMetrics.vp(0);
                    j38[l38].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? m38);
                    j38[l38].bottomEnd = LengthMetrics.vp(0);
                }
                else if (this.options.buttons && l38 === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    j38[l38].topStart = LengthMetrics.vp(0);
                    j38[l38].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? m38);
                    j38[l38].bottomStart = LengthMetrics.vp(0);
                    j38[l38].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? m38);
                }
                else {
                    j38[l38].topStart = LengthMetrics.vp(0);
                    j38[l38].topEnd = LengthMetrics.vp(0);
                    j38[l38].bottomStart = LengthMetrics.vp(0);
                    j38[l38].bottomEnd = LengthMetrics.vp(0);
                }
            }
        }
        this.buttonBorderRadius = j38;
    }

    initialRender() {
        this.observeComponentCreation2((v35, w35) => {
            If.create();
            if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e38, f38) => {
                        Row.create({ space: 1 });
                        Row.direction(this.options.direction);
                        Row.focusScopeId(this.groupId, true);
                        Row.padding(this.options.componentPadding);
                        Row.onSizeChange((h38, i38) => {
                            this.componentSize = { width: i38.width, height: i38.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((b36, c36) => {
                        ForEach.create();
                        const d36 = (f36, g36) => {
                            const h36 = f36;
                            this.observeComponentCreation2((j36, k36) => {
                                If.create();
                                if (g36 < MAX_ITEM_COUNT) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((k37, l37) => {
                                            Stack.create();
                                            Stack.direction(this.options.direction);
                                            Stack.borderRadius(this.buttonBorderRadius[g36]);
                                            Stack.scale({
                                                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[g36],
                                                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[g36]
                                            });
                                            Stack.layoutWeight(1);
                                            Stack.onSizeChange((c38, d38) => {
                                                this.buttonItemsSize[g36] = {
                                                    width: d38.width,
                                                    height: this.buttonItemsSize[g36].height
                                                };
                                                if (d38.width) {
                                                    this.buttonItemsPosition[g36] = {
                                                        x: Number.parseFloat(this.options.componentPadding.toString()) +
                                                            (Number.parseFloat(d38.width.toString()) + 1) * g36,
                                                        y: Number.parseFloat(this.options.componentPadding.toString())
                                                    };
                                                }
                                            });
                                            ViewStackProcessor.visualState("normal");
                                            Stack.overlay(undefined);
                                            ViewStackProcessor.visualState("focused");
                                            Stack.overlay({
                                                builder: () => {
                                                    this.focusStack.call(this, g36);
                                                }
                                            }, {
                                                align: Alignment.Center
                                            });
                                            ViewStackProcessor.visualState();
                                            Stack.onFocus(() => {
                                                this.focusIndex = g36;
                                            });
                                            Stack.onTouch((z37) => {
                                                if (z37.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (z37.type === TouchType.Down) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[g36] = 0.95;
                                                    });
                                                }
                                                else if (z37.type === TouchType.Up) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[g36] = 1;
                                                    });
                                                }
                                            });
                                            Stack.onHover((w37) => {
                                                if (w37) {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[g36].hoverColor = (segmentButtonTheme.HOVER_COLOR);
                                                    });
                                                }
                                                else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[g36].hoverColor = Color.Transparent;
                                                    });
                                                }
                                            });
                                            Stack.onMouse((r37) => {
                                                switch (r37.action) {
                                                    case MouseAction.Press:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[g36] = 0.95;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[g36] = true;
                                                        });
                                                        break;
                                                    case MouseAction.Release:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[g36] = 1;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[g36] = false;
                                                        });
                                                        break;
                                                }
                                            });
                                        }, Stack);
                                        {
                                            this.observeComponentCreation2((e37, f37) => {
                                                if (f37) {
                                                    let g37 = new PressAndHoverEffect(this, {
                                                        pressIndex: g36,
                                                        colorProperty: this.hoverColorArray[g36],
                                                        press: this.pressArray[g36],
                                                        options: this.options,
                                                    }, undefined, e37, () => {
                                                    }, {
                                                        page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                        line: 771,
                                                        col: 15
                                                    });
                                                    ViewPU.create(g37);
                                                    let h37 = () => {
                                                        return {
                                                            pressIndex: g36,
                                                            colorProperty: this.hoverColorArray[g36],
                                                            press: this.pressArray[g36],
                                                            options: this.options
                                                        };
                                                    };
                                                    g37.paramsGenerator_ = h37;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(e37, {
                                                        colorProperty: this.hoverColorArray[g36],
                                                        press: this.pressArray[g36],
                                                        options: this.options
                                                    });
                                                }
                                            }, { name: "PressAndHoverEffect" });
                                        }
                                        this.observeComponentCreation2((w36, x36) => {
                                            __Common__.create();
                                            __Common__.onSizeChange((z36, a37) => {
                                                this.buttonItemsRealHeight[g36] = a37.height;
                                                let b37 = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ?
                                                this.options.buttons.length : 0));
                                                for (let c37 = 0; c37 < this.buttonItemsSize.length; c37++) {
                                                    this.buttonItemsSize[c37] = {
                                                        width: this.buttonItemsSize[c37].width,
                                                        height: b37
                                                    };
                                                }
                                                this.calculateBorderRadius();
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((q36, r36) => {
                                                if (r36) {
                                                    let s36 = new SegmentButtonItem(this, {
                                                        selectedIndexes: this.__selectedIndexes,
                                                        focusIndex: this.__focusIndex,
                                                        index: g36,
                                                        itemOptions: h36,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[g36],
                                                        groupId: this.groupId
                                                    }, undefined, q36, () => {
                                                    }, {
                                                        page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                        line: 777,
                                                        col: 15
                                                    });
                                                    ViewPU.create(s36);
                                                    let t36 = () => {
                                                        return {
                                                            selectedIndexes: this.selectedIndexes,
                                                            focusIndex: this.focusIndex,
                                                            index: g36,
                                                            itemOptions: h36,
                                                            options: this.options,
                                                            property: this.buttonItemProperty[g36],
                                                            groupId: this.groupId
                                                        };
                                                    };
                                                    s36.paramsGenerator_ = t36;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(q36, {
                                                        index: g36,
                                                        itemOptions: h36,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[g36]
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
                        this.forEachUpdateFunction(b36, this.optionsArray, d36, undefined, true, false);
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
    constructor(w34, x34, y34, z34 = -1, a35 = undefined, b35) {
        super(w34, y34, z34, b35);
        if (typeof a35 === "function") {
            this.paramsGenerator_ = a35;
        }
        this.__options = new SynchedPropertyNesedObjectPU(x34.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(x34.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, "componentSize");
        this.addProvidedVar("componentSize", this.__componentSize, false);
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (s35, t35) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        }), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.__buttonBorderRadius, false);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (q35, r35) => {
            return {};
        }), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.__buttonItemsSize, false);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (o35, p35) => {
            return {};
        }), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.__buttonItemsPosition, false);
        this.__buttonItemsSelected = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (m35, n35) => false), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected, false);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (k35, l35) => new ItemProperty()), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty, false);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex, false);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition, false);
        this.__zoomScaleArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (i35, j35) => 1.0), this, "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.__zoomScaleArray, false);
        this.doSelectedChangeAnimate = false;
        this.isCurrentPositionSelected = false;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = false;
        this.__shouldMirror = new ObservedPropertySimplePU(false, this, "shouldMirror");
        this.setInitiallyProvidedValue(x34);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.declareWatch("buttonItemsPosition", this.onItemsPositionChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(v34) {
        this.__options.set(v34.options);
        if (v34.componentSize !== undefined) {
            this.componentSize = v34.componentSize;
        }
        if (v34.buttonBorderRadius !== undefined) {
            this.buttonBorderRadius = v34.buttonBorderRadius;
        }
        if (v34.buttonItemsSize !== undefined) {
            this.buttonItemsSize = v34.buttonItemsSize;
        }
        if (v34.buttonItemsPosition !== undefined) {
            this.buttonItemsPosition = v34.buttonItemsPosition;
        }
        if (v34.buttonItemsSelected !== undefined) {
            this.buttonItemsSelected = v34.buttonItemsSelected;
        }
        if (v34.buttonItemProperty !== undefined) {
            this.buttonItemProperty = v34.buttonItemProperty;
        }
        if (v34.focusIndex !== undefined) {
            this.focusIndex = v34.focusIndex;
        }
        if (v34.selectedItemPosition !== undefined) {
            this.selectedItemPosition = v34.selectedItemPosition;
        }
        if (v34.zoomScaleArray !== undefined) {
            this.zoomScaleArray = v34.zoomScaleArray;
        }
        if (v34.doSelectedChangeAnimate !== undefined) {
            this.doSelectedChangeAnimate = v34.doSelectedChangeAnimate;
        }
        if (v34.isCurrentPositionSelected !== undefined) {
            this.isCurrentPositionSelected = v34.isCurrentPositionSelected;
        }
        if (v34.panGestureStartPoint !== undefined) {
            this.panGestureStartPoint = v34.panGestureStartPoint;
        }
        if (v34.isPanGestureMoved !== undefined) {
            this.isPanGestureMoved = v34.isPanGestureMoved;
        }
        if (v34.shouldMirror !== undefined) {
            this.shouldMirror = v34.shouldMirror;
        }
    }

    updateStateVars(u34) {
        this.__options.set(u34.options);
    }

    purgeVariableDependenciesOnElmtId(t34) {
        this.__options.purgeDependencyOnElmtId(t34);
        this.__selectedIndexes.purgeDependencyOnElmtId(t34);
        this.__componentSize.purgeDependencyOnElmtId(t34);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(t34);
        this.__buttonItemsSize.purgeDependencyOnElmtId(t34);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(t34);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(t34);
        this.__buttonItemProperty.purgeDependencyOnElmtId(t34);
        this.__focusIndex.purgeDependencyOnElmtId(t34);
        this.__selectedItemPosition.purgeDependencyOnElmtId(t34);
        this.__zoomScaleArray.purgeDependencyOnElmtId(t34);
        this.__shouldMirror.purgeDependencyOnElmtId(t34);
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

    set selectedIndexes(s34) {
        this.__selectedIndexes.set(s34);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(r34) {
        this.__componentSize.set(r34);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(q34) {
        this.__buttonBorderRadius.set(q34);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(p34) {
        this.__buttonItemsSize.set(p34);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(o34) {
        this.__buttonItemsPosition.set(o34);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(n34) {
        this.__buttonItemsSelected.set(n34);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(m34) {
        this.__buttonItemProperty.set(m34);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(l34) {
        this.__focusIndex.set(l34);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(k34) {
        this.__selectedItemPosition.set(k34);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(j34) {
        this.__zoomScaleArray.set(j34);
    }

    get shouldMirror() {
        return this.__shouldMirror.get();
    }

    set shouldMirror(i34) {
        this.__shouldMirror.set(i34);
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
        this.buttonItemsSelected.forEach((g34, h34) => {
            this.buttonItemsSelected[h34] = false;
        });
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            this.selectedIndexes.forEach(f34 => this.buttonItemsSelected[f34] = true);
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
        let a34 = this.selectedIndexes.some(c34 => {
            return (c34 === void 0 || c34 < 0 || (this.options.buttons && c34 >= this.options.buttons.length));
        });
        if (a34) {
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

    isMouseWheelScroll(y33) {
        return y33.source === SourceType.Mouse && !this.isPanGestureMoved;
    }

    isMovedFromPanGestureStartPoint(w33, x33) {
        return!nearEqual(w33, this.panGestureStartPoint.x) || !nearEqual(x33, this.panGestureStartPoint.y);
    }

    isShouldMirror() {
        if (this.options.direction == Direction.Rtl) {
            return true;
        }
        try {
            let v33 = I18n.System.getSystemLanguage();
            if (v33 === 'ug' && this.options.direction != Direction.Ltr) {
                return true;
            }
        }
        catch (u33) {
            console.error(`Ace SegmentButton getSystemLanguage, error: ${u33.toString()}`);
        }
        return false;
    }

    initialRender() {
        this.observeComponentCreation2((l32, m32) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.onBlur(() => {
                this.focusIndex = -1;
            });
            Stack.onKeyEvent((t33) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (t33.type === KeyType.Down) {
                    if (t33.keyCode === KeyCode.KEYCODE_SPACE || t33.keyCode === KeyCode.KEYCODE_ENTER ||
                        t33.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
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
            TapGesture.onAction((m33) => {
                this.focusIndex = -1;
                let n33 = m33.fingerList.find(Boolean);
                if (n33 === void 0) {
                    return;
                }
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                let o33 = n33.localX;
                let p33 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
                for (let q33 = 0; q33 < p33; q33++) {
                    o33 = o33 - this.buttonItemsSize[q33].width;
                    if (o33 >= 0) {
                        continue;
                    }
                    this.doSelectedChangeAnimate =
                        this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ? false : true;
                    let r33 = this.shouldMirror ? p33 - 1 - q33 : q33;
                    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                        let s33 = this.selectedIndexes.indexOf(r33);
                        if (s33 === -1) {
                            this.selectedIndexes.push(r33);
                        }
                        else {
                            this.selectedIndexes.splice(s33, 1);
                        }
                    }
                    else {
                        this.selectedIndexes[0] = r33;
                    }
                    this.doSelectedChangeAnimate = false;
                    break;
                }
            });
            TapGesture.pop();
            SwipeGesture.create();
            SwipeGesture.onAction((l33) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (this.isCurrentPositionSelected) {
                    return;
                }
                if (l33.angle > 0 && this.selectedIndexes[0] !== Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
                    this.doSelectedChangeAnimate = false;
                }
                else if (l33.angle < 0 && this.selectedIndexes[0] !== 0) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
                    this.doSelectedChangeAnimate = false;
                }
            });
            SwipeGesture.pop();
            PanGesture.create();
            PanGesture.onActionStart((h33) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let i33 = h33.fingerList.find(Boolean);
                if (i33 === void 0) {
                    return;
                }
                let j33 = i33.localX;
                this.panGestureStartPoint = { x: i33.globalX, y: i33.globalY };
                this.isPanGestureMoved = false;
                for (let k33 = 0; k33 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); k33++) {
                    j33 = j33 - this.buttonItemsSize[k33].width;
                    if (j33 < 0) {
                        this.isCurrentPositionSelected = k33 === this.selectedIndexes[0] ? true : false;
                        break;
                    }
                }
            });
            PanGesture.onActionUpdate((y32) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (!this.isCurrentPositionSelected) {
                    return;
                }
                let z32 = y32.fingerList.find(Boolean);
                if (z32 === void 0) {
                    return;
                }
                let a33 = z32.localX;
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(z32.globalX, z32.globalY)) {
                    this.isPanGestureMoved = true;
                }
                for (let g33 = 0; g33 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); g33++) {
                    a33 = a33 - this.buttonItemsSize[g33].width;
                    if (a33 < 0) {
                        this.doSelectedChangeAnimate = true;
                        this.selectedIndexes[0] = g33;
                        this.doSelectedChangeAnimate = false;
                        break;
                    }
                }
                this.zoomScaleArray.forEach((c33, d33) => {
                    if (d33 === this.selectedIndexes[0]) {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[d33] = 0.95;
                        });
                    }
                    else {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[d33] = 1;
                        });
                    }
                });
            });
            PanGesture.onActionEnd((u32) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let v32 = u32.fingerList.find(Boolean);
                if (v32 === void 0) {
                    return;
                }
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(v32.globalX, v32.globalY)) {
                    this.isPanGestureMoved = true;
                }
                if (this.isMouseWheelScroll(u32)) {
                    let x32 = u32.offsetX !== 0 ? u32.offsetX : u32.offsetY;
                    this.doSelectedChangeAnimate = true;
                    if (x32 > 0 && this.selectedIndexes[0] > 0) {
                        this.selectedIndexes[0] -= 1;
                    }
                    else if (x32 < 0 && this.selectedIndexes[0] < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
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
        this.observeComponentCreation2((p30, q30) => {
            If.create();
            if (this.options !== void 0 && this.options.buttons != void 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x31, y31) => {
                        If.create();
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                {
                                    this.observeComponentCreation2((f32, g32) => {
                                        if (g32) {
                                            let h32 = new MultiSelectBackground(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                            }, undefined, f32, () => {
                                            }, {
                                                page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                line: 1047,
                                                col: 11
                                            });
                                            ViewPU.create(h32);
                                            let i32 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options
                                                };
                                            };
                                            h32.paramsGenerator_ = i32;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(f32, {
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
                                this.observeComponentCreation2((b32, c32) => {
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
                    this.observeComponentCreation2((v31, w31) => {
                        Stack.create();
                        Stack.direction(this.options.direction);
                        Stack.size(ObservedObject.GetRawObject(this.componentSize));
                        Stack.borderRadius((this.options.type === 'capsule' && (this.options.multiply ?? false) ?
                        this.options.iconTextRadius : this.options.iconTextBackgroundRadius) ??
                            this.componentSize.height / 2);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((d31, e31) => {
                        If.create();
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                {
                                    this.observeComponentCreation2((p31, q31) => {
                                        if (q31) {
                                            let r31 = new MultiSelectItemArray(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, p31, () => {
                                            }, {
                                                page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                line: 1061,
                                                col: 13
                                            });
                                            ViewPU.create(r31);
                                            let s31 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            r31.paramsGenerator_ = s31;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(p31, {
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
                                    this.observeComponentCreation2((h31, i31) => {
                                        if (i31) {
                                            let j31 = new SelectItem(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, h31, () => {
                                            }, {
                                                page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                line: 1067,
                                                col: 13
                                            });
                                            ViewPU.create(j31);
                                            let k31 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            j31.paramsGenerator_ = k31;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(h31, {
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
                        this.observeComponentCreation2((x30, y30) => {
                            if (y30) {
                                let z30 = new SegmentButtonItemArrayComponent(this, {
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    selectedIndexes: this.__selectedIndexes,
                                }, undefined, x30, () => {
                                }, {
                                    page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                    line: 1081,
                                    col: 9
                                });
                                ViewPU.create(z30);
                                let a31 = () => {
                                    return {
                                        optionsArray: this.options.buttons,
                                        options: this.options,
                                        selectedIndexes: this.selectedIndexes
                                    };
                                };
                                z30.paramsGenerator_ = a31;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(x30, {
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
            let j30 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
            this.selectedItemPosition = this.selectedIndexes.length === 0 ? {
            } : this.buttonItemsPosition[this.shouldMirror ? (j30 - 1 - this.selectedIndexes[0]) : this.selectedIndexes[0]];
            this.buttonItemsSelected.forEach((l30, m30) => {
                this.buttonItemProperty[m30].fontColor = l30 ?
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

export default { SegmentButton, SegmentButtonOptions, SegmentButtonItemOptionsArray, SegmentButtonItemOptions };