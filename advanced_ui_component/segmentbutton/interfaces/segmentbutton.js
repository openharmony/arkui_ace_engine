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

var __decorate = (this && this.__decorate) || function (h47, i47, j47, k47) {
    var l47 = arguments.length,
        m47 = l47 < 3 ? i47 : k47 === null ? k47 = Object.getOwnPropertyDescriptor(i47, j47) : k47, n47;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        m47 = Reflect.decorate(h47, i47, j47, k47);
    else
        for (var o47 = h47.length - 1; o47 >= 0; o47--)
            if (n47 = h47[o47])
                m47 = (l47 < 3 ? n47(m47) : l47 > 3 ? n47(i47, j47, m47) : n47(i47, j47)) || m47;
    return l47 > 3 && m47 && Object.defineProperty(i47, j47, m47), m47;
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

function nearEqual(e47, f47) {
    return Math.abs(e47 - f47) < 0.001;
}

let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(d47) {
        this.icon = d47.icon;
        this.selectedIcon = d47.selectedIcon;
        this.text = d47.text;
    }
};
SegmentButtonItemOptions = __decorate([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends Array {
    constructor(a47) {
        super(typeof a47 === "number" ? a47 : 0);
        this.changeStartIndex = void 0;
        this.deleteCount = void 0;
        this.addLength = void 0;
        if (typeof a47 !== "number" && a47 !== void 0) {
            super.push(...a47.map((c47) => new SegmentButtonItemOptions(c47)));
        }
    }

    push(...x46) {
        if (this.length + x46.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        this.changeStartIndex = this.length;
        this.deleteCount = 0;
        this.addLength = x46.length;
        return super.push(...x46.map((z46) => new SegmentButtonItemOptions(z46)));
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

    unshift(...u46) {
        if (this.length + u46.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        if (u46.length > 0) {
            this.changeStartIndex = 0;
            this.deleteCount = 0;
            this.addLength = u46.length;
        }
        return super.unshift(...u46.map((w46) => new SegmentButtonItemOptions(w46)));
    }

    splice(q46, r46, ...s46) {
        let t46 = (this.length - r46) < 0 ? 0 : (this.length - r46);
        t46 += s46.length;
        if (t46 < MIN_ITEM_COUNT) {
            console.warn("Below the minimum number of elements (2).");
            return [];
        }
        if (t46 > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return [];
        }
        this.changeStartIndex = q46;
        this.deleteCount = r46;
        this.addLength = s46.length;
        return super.splice(q46, r46, ...s46);
    }

    static create(p46) {
        return new SegmentButtonItemOptionsArray_1(p46);
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

    set buttons(o46) {
        if (this._buttons !== void 0 && this._buttons !== o46) {
            this.onButtonsChange?.();
        }
        this._buttons = o46;
    }

    constructor(l46) {
        this.multiply = false;
        this.showText = false;
        this.showIcon = false;
        this._buttons = void 0;
        this.fontColor = l46.fontColor ?? segmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = l46.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = l46.fontSize ?? segmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = l46.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = l46.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = l46.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = l46.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = l46.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = l46.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = l46.buttonPadding;
        this.textPadding = l46.textPadding;
        this.type = l46.type;
        this.backgroundBlurStyle = l46.backgroundBlurStyle ?? segmentButtonTheme.BACKGROUND_BLUR_STYLE;
        this.localizedTextPadding = l46.localizedTextPadding;
        this.localizedButtonPadding = l46.localizedButtonPadding;
        this.direction = l46.direction ?? Direction.Auto;
        this.buttons = new SegmentButtonItemOptionsArray(l46.buttons);
        if (this.type === "capsule") {
            this.multiply = l46.multiply ?? false;
            this.buttons.forEach(n46 => {
                this.showText ||= n46.text !== void 0;
                this.showIcon ||= n46.icon !== void 0 || n46.selectedIcon !== void 0;
            });
            if (this.showText && this.showIcon) {
                this.iconTextRadius = 12;
                this.iconTextBackgroundRadius = 14;
            }
            this.selectedFontColor = l46.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = l46.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
        else {
            this.showText = true;
        }
        this.componentPadding = this.multiply ? 0 : 2;
    }

    static tab(k46) {
        return new SegmentButtonOptions_1({
            type: "tab",
            buttons: k46.buttons,
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

    static capsule(j46) {
        return new SegmentButtonOptions_1({
            type: "capsule",
            buttons: j46.buttons,
            multiply: j46.multiply,
            fontColor: j46.fontColor,
            selectedFontColor: j46.selectedFontColor,
            fontSize: j46.fontSize,
            selectedFontSize: j46.selectedFontSize,
            fontWeight: j46.fontWeight,
            selectedFontWeight: j46.selectedFontWeight,
            backgroundColor: j46.backgroundColor,
            selectedBackgroundColor: j46.selectedBackgroundColor,
            imageSize: j46.imageSize,
            buttonPadding: j46.buttonPadding,
            textPadding: j46.textPadding,
            localizedTextPadding: j46.localizedTextPadding,
            localizedButtonPadding: j46.localizedButtonPadding,
            backgroundBlurStyle: j46.backgroundBlurStyle,
            direction: j46.direction
        });
    }
};
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([
    Observed
], SegmentButtonOptions);

export { SegmentButtonOptions };

class MultiSelectBackground extends ViewPU {
    constructor(d46, e46, f46, g46 = -1, h46 = undefined, i46) {
        super(d46, f46, g46, i46);
        if (typeof h46 === "function") {
            this.paramsGenerator_ = h46;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(e46.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(e46.options, this, "options");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(e46);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(c46) {
        this.__optionsArray.set(c46.optionsArray);
        this.__options.set(c46.options);
    }

    updateStateVars(b46) {
        this.__optionsArray.set(b46.optionsArray);
        this.__options.set(b46.options);
    }

    purgeVariableDependenciesOnElmtId(a46) {
        this.__optionsArray.purgeDependencyOnElmtId(a46);
        this.__options.purgeDependencyOnElmtId(a46);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(a46);
        this.__buttonItemsSize.purgeDependencyOnElmtId(a46);
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

    set buttonBorderRadius(z45) {
        this.__buttonBorderRadius.set(z45);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(y45) {
        this.__buttonItemsSize.set(y45);
    }

    initialRender() {
        this.observeComponentCreation2((w45, x45) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((h45, i45) => {
            ForEach.create();
            const j45 = (l45, m45) => {
                const n45 = l45;
                this.observeComponentCreation2((p45, q45) => {
                    If.create();
                    if (m45 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((u45, v45) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[m45].height);
                                Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[m45]);
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
            this.forEachUpdateFunction(h45, this.optionsArray, j45, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SelectItem extends ViewPU {
    constructor(z44, a45, b45, c45 = -1, d45 = undefined, e45) {
        super(z44, b45, c45, e45);
        if (typeof d45 === "function") {
            this.paramsGenerator_ = d45;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(a45.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(a45.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(a45.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__selectedItemPosition = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(a45);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(y44) {
        this.__optionsArray.set(y44.optionsArray);
        this.__options.set(y44.options);
    }

    updateStateVars(x44) {
        this.__optionsArray.set(x44.optionsArray);
        this.__options.set(x44.options);
    }

    purgeVariableDependenciesOnElmtId(w44) {
        this.__optionsArray.purgeDependencyOnElmtId(w44);
        this.__options.purgeDependencyOnElmtId(w44);
        this.__selectedIndexes.purgeDependencyOnElmtId(w44);
        this.__buttonItemsSize.purgeDependencyOnElmtId(w44);
        this.__selectedItemPosition.purgeDependencyOnElmtId(w44);
        this.__zoomScaleArray.purgeDependencyOnElmtId(w44);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(w44);
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

    set selectedIndexes(v44) {
        this.__selectedIndexes.set(v44);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(u44) {
        this.__buttonItemsSize.set(u44);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(t44) {
        this.__selectedItemPosition.set(t44);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(s44) {
        this.__zoomScaleArray.set(s44);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(r44) {
        this.__buttonBorderRadius.set(r44);
    }

    initialRender() {
        this.observeComponentCreation2((k44, l44) => {
            If.create();
            if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p44, q44) => {
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
    constructor(a44, b44, c44, d44 = -1, e44 = undefined, f44) {
        super(a44, c44, d44, f44);
        if (typeof e44 === "function") {
            this.paramsGenerator_ = e44;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(b44.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(b44.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(b44.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__multiColor = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (h44, i44) => Color.Transparent), this, "multiColor");
        this.setInitiallyProvidedValue(b44);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(z43) {
        this.__optionsArray.set(z43.optionsArray);
        this.__options.set(z43.options);
        if (z43.multiColor !== undefined) {
            this.multiColor = z43.multiColor;
        }
    }

    updateStateVars(y43) {
        this.__optionsArray.set(y43.optionsArray);
        this.__options.set(y43.options);
    }

    purgeVariableDependenciesOnElmtId(x43) {
        this.__optionsArray.purgeDependencyOnElmtId(x43);
        this.__options.purgeDependencyOnElmtId(x43);
        this.__selectedIndexes.purgeDependencyOnElmtId(x43);
        this.__buttonItemsSize.purgeDependencyOnElmtId(x43);
        this.__zoomScaleArray.purgeDependencyOnElmtId(x43);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(x43);
        this.__multiColor.purgeDependencyOnElmtId(x43);
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

    set selectedIndexes(w43) {
        this.__selectedIndexes.set(w43);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(v43) {
        this.__buttonItemsSize.set(v43);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(u43) {
        this.__zoomScaleArray.set(u43);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(t43) {
        this.__buttonBorderRadius.set(t43);
    }

    get multiColor() {
        return this.__multiColor.get();
    }

    set multiColor(s43) {
        this.__multiColor.set(s43);
    }

    onOptionsChange() {
        for (let r43 = 0; r43 < this.selectedIndexes.length; r43++) {
            this.multiColor[this.selectedIndexes[r43]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    onSelectedChange() {
        for (let q43 = 0; q43 < MAX_ITEM_COUNT; q43++) {
            this.multiColor[q43] = Color.Transparent;
        }
        for (let p43 = 0; p43 < this.selectedIndexes.length; p43++) {
            this.multiColor[this.selectedIndexes[p43]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    aboutToAppear() {
        for (let o43 = 0; o43 < this.selectedIndexes.length; o43++) {
            this.multiColor[this.selectedIndexes[o43]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    initialRender() {
        this.observeComponentCreation2((m43, n43) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((x42, y42) => {
            ForEach.create();
            const z42 = (b43, c43) => {
                const d43 = b43;
                this.observeComponentCreation2((f43, g43) => {
                    If.create();
                    if (c43 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((k43, l43) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.width(this.buttonItemsSize[c43].width);
                                Stack.height(this.buttonItemsSize[c43].height);
                                Stack.backgroundColor(this.multiColor[c43]);
                                Stack.borderRadius(this.buttonBorderRadius[c43]);
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
            this.forEachUpdateFunction(x42, this.optionsArray, z42, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SegmentButtonItem extends ViewPU {
    constructor(p42, q42, r42, s42 = -1, t42 = undefined, u42) {
        super(p42, r42, s42, u42);
        if (typeof t42 === "function") {
            this.paramsGenerator_ = t42;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(q42.selectedIndexes, this, "selectedIndexes");
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(q42.focusIndex, this, "focusIndex");
        this.__itemOptions = new SynchedPropertyNesedObjectPU(q42.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(q42.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(q42.property, this, "property");
        this.__index = new SynchedPropertySimpleOneWayPU(q42.index, this, "index");
        this.groupId = "";
        this.setInitiallyProvidedValue(q42);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(o42) {
        this.__itemOptions.set(o42.itemOptions);
        this.__options.set(o42.options);
        this.__property.set(o42.property);
        if (o42.groupId !== undefined) {
            this.groupId = o42.groupId;
        }
    }

    updateStateVars(n42) {
        this.__itemOptions.set(n42.itemOptions);
        this.__options.set(n42.options);
        this.__property.set(n42.property);
        this.__index.reset(n42.index);
    }

    purgeVariableDependenciesOnElmtId(m42) {
        this.__selectedIndexes.purgeDependencyOnElmtId(m42);
        this.__focusIndex.purgeDependencyOnElmtId(m42);
        this.__itemOptions.purgeDependencyOnElmtId(m42);
        this.__options.purgeDependencyOnElmtId(m42);
        this.__property.purgeDependencyOnElmtId(m42);
        this.__index.purgeDependencyOnElmtId(m42);
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

    set selectedIndexes(l42) {
        this.__selectedIndexes.set(l42);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(k42) {
        this.__focusIndex.set(k42);
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

    set index(j42) {
        this.__index.set(j42);
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
        this.observeComponentCreation2((h42, i42) => {
            Column.create({ space: 2 });
            Column.direction(this.options.direction);
            Column.focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.getButtonPadding());
            Column.constraintSize({ minHeight: 28 });
        }, Column);
        this.observeComponentCreation2((a42, b42) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f42, g42) => {
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
        this.observeComponentCreation2((s41, t41) => {
            If.create();
            if (this.options.showText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x41, y41) => {
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
    constructor(j41, k41, l41, m41 = -1, n41 = undefined, o41) {
        super(j41, l41, m41, o41);
        if (typeof n41 === "function") {
            this.paramsGenerator_ = n41;
        }
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(k41.press, this, "press");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(k41.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__options = new SynchedPropertyNesedObjectPU(k41.options, this, "options");
        this.pressIndex = 0;
        this.pressColor = segmentButtonTheme.PRESS_COLOR;
        this.setInitiallyProvidedValue(k41);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(i41) {
        this.__colorProperty.set(i41.colorProperty);
        this.__options.set(i41.options);
        if (i41.pressIndex !== undefined) {
            this.pressIndex = i41.pressIndex;
        }
        if (i41.pressColor !== undefined) {
            this.pressColor = i41.pressColor;
        }
    }

    updateStateVars(h41) {
        this.__press.reset(h41.press);
        this.__colorProperty.set(h41.colorProperty);
        this.__options.set(h41.options);
    }

    purgeVariableDependenciesOnElmtId(g41) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(g41);
        this.__press.purgeDependencyOnElmtId(g41);
        this.__colorProperty.purgeDependencyOnElmtId(g41);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(g41);
        this.__options.purgeDependencyOnElmtId(g41);
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

    set buttonItemsSize(f41) {
        this.__buttonItemsSize.set(f41);
    }

    get press() {
        return this.__press.get();
    }

    set press(e41) {
        this.__press.set(e41);
    }

    get colorProperty() {
        return this.__colorProperty.get();
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(d41) {
        this.__buttonBorderRadius.set(d41);
    }

    get options() {
        return this.__options.get();
    }

    initialRender() {
        this.observeComponentCreation2((b41, c41) => {
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
    constructor(f40, g40, h40, i40 = -1, j40 = undefined, k40) {
        super(f40, h40, i40, k40);
        if (typeof j40 === "function") {
            this.paramsGenerator_ = j40;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(g40.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(g40.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(g40.selectedIndexes, this, "selectedIndexes");
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
        }, (y40, z40) => false), this, "pressArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (w40, x40) => new HoverColorProperty()), this, "hoverColorArray");
        this.__buttonWidth = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (u40, v40) => 0), this, "buttonWidth");
        this.__buttonHeight = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (s40, t40) => 0), this, "buttonHeight");
        this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (q40, r40) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.setInitiallyProvidedValue(g40);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(e40) {
        this.__optionsArray.set(e40.optionsArray);
        this.__options.set(e40.options);
        if (e40.pressArray !== undefined) {
            this.pressArray = e40.pressArray;
        }
        if (e40.hoverColorArray !== undefined) {
            this.hoverColorArray = e40.hoverColorArray;
        }
        if (e40.buttonWidth !== undefined) {
            this.buttonWidth = e40.buttonWidth;
        }
        if (e40.buttonHeight !== undefined) {
            this.buttonHeight = e40.buttonHeight;
        }
        if (e40.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = e40.buttonItemsRealHeight;
        }
        if (e40.groupId !== undefined) {
            this.groupId = e40.groupId;
        }
    }

    updateStateVars(d40) {
        this.__optionsArray.set(d40.optionsArray);
        this.__options.set(d40.options);
    }

    purgeVariableDependenciesOnElmtId(c40) {
        this.__optionsArray.purgeDependencyOnElmtId(c40);
        this.__options.purgeDependencyOnElmtId(c40);
        this.__selectedIndexes.purgeDependencyOnElmtId(c40);
        this.__componentSize.purgeDependencyOnElmtId(c40);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(c40);
        this.__buttonItemsSize.purgeDependencyOnElmtId(c40);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(c40);
        this.__focusIndex.purgeDependencyOnElmtId(c40);
        this.__zoomScaleArray.purgeDependencyOnElmtId(c40);
        this.__buttonItemProperty.purgeDependencyOnElmtId(c40);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(c40);
        this.__pressArray.purgeDependencyOnElmtId(c40);
        this.__hoverColorArray.purgeDependencyOnElmtId(c40);
        this.__buttonWidth.purgeDependencyOnElmtId(c40);
        this.__buttonHeight.purgeDependencyOnElmtId(c40);
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

    set selectedIndexes(b40) {
        this.__selectedIndexes.set(b40);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(a40) {
        this.__componentSize.set(a40);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(z39) {
        this.__buttonBorderRadius.set(z39);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(y39) {
        this.__buttonItemsSize.set(y39);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(x39) {
        this.__buttonItemsPosition.set(x39);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(w39) {
        this.__focusIndex.set(w39);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(v39) {
        this.__zoomScaleArray.set(v39);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(u39) {
        this.__buttonItemProperty.set(u39);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(t39) {
        this.__buttonItemsSelected.set(t39);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(s39) {
        this.__pressArray.set(s39);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(r39) {
        this.__hoverColorArray.set(r39);
    }

    get buttonWidth() {
        return this.__buttonWidth.get();
    }

    set buttonWidth(q39) {
        this.__buttonWidth.set(q39);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(p39) {
        this.__buttonHeight.set(p39);
    }

    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((n39, o39) => {
            this.buttonWidth[o39] = n39.width;
            this.buttonHeight[o39] = n39.height;
        });
    }

    changeSelectedIndexes(b39) {
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
            let c39 = this.selectedIndexes;
            for (let h39 = 0; h39 < this.optionsArray.deleteCount; h39++) {
                let i39 = c39.indexOf(this.optionsArray.changeStartIndex);
                let j39 = c39.map(l39 => this.optionsArray.changeStartIndex &&
                    (l39 > this.optionsArray.changeStartIndex) ? l39 - 1 : l39);
                if (i39 !== -1) {
                    j39.splice(i39, 1);
                }
                c39 = j39;
            }
            for (let d39 = 0; d39 < this.optionsArray.addLength; d39++) {
                let e39 = c39.map(g39 => this.optionsArray.changeStartIndex &&
                    (g39 >= this.optionsArray.changeStartIndex) ? g39 + 1 : g39);
                c39 = e39;
            }
            this.selectedIndexes = c39;
        }
    }

    changeFocusIndex(a39) {
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
        let z38 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 &&
            this.optionsArray.addLength !== void 0) {
            this.changeSelectedIndexes(z38);
            this.changeFocusIndex(z38);
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
        for (let y38 = 0; y38 < this.buttonItemsRealHeight.length; y38++) {
            this.buttonItemsRealHeight[y38] = 0;
        }
    }

    getBorderRadius(w38) {
        let x38 = this.buttonBorderRadius[w38];
        if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex]) {
            x38.topStart = LengthMetrics.vp(x38.topStart.value + 4);
            x38.topEnd = LengthMetrics.vp(x38.topEnd.value + 4);
            x38.bottomStart = LengthMetrics.vp(x38.bottomStart.value + 4);
            x38.bottomEnd = LengthMetrics.vp(x38.bottomEnd.value + 4);
        }
        return x38;
    }

    focusStack(o38, p38 = null) {
        this.observeComponentCreation2((u38, v38) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((s38, t38) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.borderRadius(this.getBorderRadius(o38));
            Stack.size({
                width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonWidth[o38] + 8 : this.buttonWidth[o38],
                height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonHeight[o38] + 8 : this.buttonHeight[o38]
            });
            Stack.borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR);
            Stack.borderWidth(2);
        }, Stack);
        Stack.pop();
        Stack.pop();
    }

    calculateBorderRadius() {
        let i38 = Array.from({
            length: MAX_ITEM_COUNT
        }, (m38, n38) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        });
        for (let k38 = 0; k38 < this.buttonBorderRadius.length; k38++) {
            let l38 = this.buttonItemsSize[k38].height / 2;
            if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                i38[k38].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? l38);
                i38[k38].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? l38);
                i38[k38].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? l38);
                i38[k38].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? l38);
            }
            else {
                if (k38 === 0) {
                    i38[k38].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? l38);
                    i38[k38].topEnd = LengthMetrics.vp(0);
                    i38[k38].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? l38);
                    i38[k38].bottomEnd = LengthMetrics.vp(0);
                }
                else if (this.options.buttons && k38 === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    i38[k38].topStart = LengthMetrics.vp(0);
                    i38[k38].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? l38);
                    i38[k38].bottomStart = LengthMetrics.vp(0);
                    i38[k38].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? l38);
                }
                else {
                    i38[k38].topStart = LengthMetrics.vp(0);
                    i38[k38].topEnd = LengthMetrics.vp(0);
                    i38[k38].bottomStart = LengthMetrics.vp(0);
                    i38[k38].bottomEnd = LengthMetrics.vp(0);
                }
            }
        }
        this.buttonBorderRadius = i38;
    }

    initialRender() {
        this.observeComponentCreation2((u35, v35) => {
            If.create();
            if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d38, e38) => {
                        Row.create({ space: 1 });
                        Row.direction(this.options.direction);
                        Row.focusScopeId(this.groupId, true);
                        Row.padding(this.options.componentPadding);
                        Row.onSizeChange((g38, h38) => {
                            this.componentSize = { width: h38.width, height: h38.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((a36, b36) => {
                        ForEach.create();
                        const c36 = (e36, f36) => {
                            const g36 = e36;
                            this.observeComponentCreation2((i36, j36) => {
                                If.create();
                                if (f36 < MAX_ITEM_COUNT) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((j37, k37) => {
                                            Stack.create();
                                            Stack.direction(this.options.direction);
                                            Stack.borderRadius(this.buttonBorderRadius[f36]);
                                            Stack.scale({
                                                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[f36],
                                                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[f36]
                                            });
                                            Stack.layoutWeight(1);
                                            Stack.onSizeChange((b38, c38) => {
                                                this.buttonItemsSize[f36] = {
                                                    width: c38.width,
                                                    height: this.buttonItemsSize[f36].height
                                                };
                                                if (c38.width) {
                                                    this.buttonItemsPosition[f36] = {
                                                        start: LengthMetrics.vp(Number.parseFloat(this.options.componentPadding.toString()) +
                                                            (Number.parseFloat(c38.width.toString()) + 1) * f36),
                                                        top: LengthMetrics.vp(Number.parseFloat(this.options.componentPadding.toString()))
                                                    };
                                                }
                                            });
                                            ViewStackProcessor.visualState("normal");
                                            Stack.overlay(undefined);
                                            ViewStackProcessor.visualState("focused");
                                            Stack.overlay({
                                                builder: () => {
                                                    this.focusStack.call(this, f36);
                                                }
                                            }, {
                                                align: Alignment.Center
                                            });
                                            ViewStackProcessor.visualState();
                                            Stack.onFocus(() => {
                                                this.focusIndex = f36;
                                            });
                                            Stack.onTouch((y37) => {
                                                if (y37.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (y37.type === TouchType.Down) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[f36] = 0.95;
                                                    });
                                                }
                                                else if (y37.type === TouchType.Up) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[f36] = 1;
                                                    });
                                                }
                                            });
                                            Stack.onHover((v37) => {
                                                if (v37) {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[f36].hoverColor = (segmentButtonTheme.HOVER_COLOR);
                                                    });
                                                }
                                                else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[f36].hoverColor = Color.Transparent;
                                                    });
                                                }
                                            });
                                            Stack.onMouse((q37) => {
                                                switch (q37.action) {
                                                    case MouseAction.Press:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[f36] = 0.95;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[f36] = true;
                                                        });
                                                        break;
                                                    case MouseAction.Release:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[f36] = 1;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[f36] = false;
                                                        });
                                                        break;
                                                }
                                            });
                                        }, Stack);
                                        {
                                            this.observeComponentCreation2((d37, e37) => {
                                                if (e37) {
                                                    let f37 = new PressAndHoverEffect(this, {
                                                        pressIndex: f36,
                                                        colorProperty: this.hoverColorArray[f36],
                                                        press: this.pressArray[f36],
                                                        options: this.options,
                                                    }, undefined, d37, () => {
                                                    }, {
                                                        page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                        line: 771,
                                                        col: 15
                                                    });
                                                    ViewPU.create(f37);
                                                    let g37 = () => {
                                                        return {
                                                            pressIndex: f36,
                                                            colorProperty: this.hoverColorArray[f36],
                                                            press: this.pressArray[f36],
                                                            options: this.options
                                                        };
                                                    };
                                                    f37.paramsGenerator_ = g37;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(d37, {
                                                        colorProperty: this.hoverColorArray[f36],
                                                        press: this.pressArray[f36],
                                                        options: this.options
                                                    });
                                                }
                                            }, { name: "PressAndHoverEffect" });
                                        }
                                        this.observeComponentCreation2((v36, w36) => {
                                            __Common__.create();
                                            __Common__.onSizeChange((y36, z36) => {
                                                this.buttonItemsRealHeight[f36] = z36.height;
                                                let a37 = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ?
                                                this.options.buttons.length : 0));
                                                for (let b37 = 0; b37 < this.buttonItemsSize.length; b37++) {
                                                    this.buttonItemsSize[b37] = {
                                                        width: this.buttonItemsSize[b37].width,
                                                        height: a37
                                                    };
                                                }
                                                this.calculateBorderRadius();
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((p36, q36) => {
                                                if (q36) {
                                                    let r36 = new SegmentButtonItem(this, {
                                                        selectedIndexes: this.__selectedIndexes,
                                                        focusIndex: this.__focusIndex,
                                                        index: f36,
                                                        itemOptions: g36,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[f36],
                                                        groupId: this.groupId
                                                    }, undefined, p36, () => {
                                                    }, {
                                                        page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                        line: 777,
                                                        col: 15
                                                    });
                                                    ViewPU.create(r36);
                                                    let s36 = () => {
                                                        return {
                                                            selectedIndexes: this.selectedIndexes,
                                                            focusIndex: this.focusIndex,
                                                            index: f36,
                                                            itemOptions: g36,
                                                            options: this.options,
                                                            property: this.buttonItemProperty[f36],
                                                            groupId: this.groupId
                                                        };
                                                    };
                                                    r36.paramsGenerator_ = s36;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(p36, {
                                                        index: f36,
                                                        itemOptions: g36,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[f36]
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
                        this.forEachUpdateFunction(a36, this.optionsArray, c36, undefined, true, false);
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
    constructor(v34, w34, x34, y34 = -1, z34 = undefined, a35) {
        super(v34, x34, y34, a35);
        if (typeof z34 === "function") {
            this.paramsGenerator_ = z34;
        }
        this.__options = new SynchedPropertyNesedObjectPU(w34.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(w34.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, "componentSize");
        this.addProvidedVar("componentSize", this.__componentSize, false);
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (r35, s35) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        }), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.__buttonBorderRadius, false);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (p35, q35) => {
            return {};
        }), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.__buttonItemsSize, false);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (n35, o35) => {
            return {};
        }), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.__buttonItemsPosition, false);
        this.__buttonItemsSelected = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (l35, m35) => false), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected, false);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (j35, k35) => new ItemProperty()), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty, false);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex, false);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition, false);
        this.__zoomScaleArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (h35, i35) => 1.0), this, "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.__zoomScaleArray, false);
        this.doSelectedChangeAnimate = false;
        this.isCurrentPositionSelected = false;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = false;
        this.__shouldMirror = new ObservedPropertySimplePU(false, this, "shouldMirror");
        this.setInitiallyProvidedValue(w34);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.declareWatch("buttonItemsPosition", this.onItemsPositionChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(u34) {
        this.__options.set(u34.options);
        if (u34.componentSize !== undefined) {
            this.componentSize = u34.componentSize;
        }
        if (u34.buttonBorderRadius !== undefined) {
            this.buttonBorderRadius = u34.buttonBorderRadius;
        }
        if (u34.buttonItemsSize !== undefined) {
            this.buttonItemsSize = u34.buttonItemsSize;
        }
        if (u34.buttonItemsPosition !== undefined) {
            this.buttonItemsPosition = u34.buttonItemsPosition;
        }
        if (u34.buttonItemsSelected !== undefined) {
            this.buttonItemsSelected = u34.buttonItemsSelected;
        }
        if (u34.buttonItemProperty !== undefined) {
            this.buttonItemProperty = u34.buttonItemProperty;
        }
        if (u34.focusIndex !== undefined) {
            this.focusIndex = u34.focusIndex;
        }
        if (u34.selectedItemPosition !== undefined) {
            this.selectedItemPosition = u34.selectedItemPosition;
        }
        if (u34.zoomScaleArray !== undefined) {
            this.zoomScaleArray = u34.zoomScaleArray;
        }
        if (u34.doSelectedChangeAnimate !== undefined) {
            this.doSelectedChangeAnimate = u34.doSelectedChangeAnimate;
        }
        if (u34.isCurrentPositionSelected !== undefined) {
            this.isCurrentPositionSelected = u34.isCurrentPositionSelected;
        }
        if (u34.panGestureStartPoint !== undefined) {
            this.panGestureStartPoint = u34.panGestureStartPoint;
        }
        if (u34.isPanGestureMoved !== undefined) {
            this.isPanGestureMoved = u34.isPanGestureMoved;
        }
        if (u34.shouldMirror !== undefined) {
            this.shouldMirror = u34.shouldMirror;
        }
    }

    updateStateVars(t34) {
        this.__options.set(t34.options);
    }

    purgeVariableDependenciesOnElmtId(s34) {
        this.__options.purgeDependencyOnElmtId(s34);
        this.__selectedIndexes.purgeDependencyOnElmtId(s34);
        this.__componentSize.purgeDependencyOnElmtId(s34);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(s34);
        this.__buttonItemsSize.purgeDependencyOnElmtId(s34);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(s34);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(s34);
        this.__buttonItemProperty.purgeDependencyOnElmtId(s34);
        this.__focusIndex.purgeDependencyOnElmtId(s34);
        this.__selectedItemPosition.purgeDependencyOnElmtId(s34);
        this.__zoomScaleArray.purgeDependencyOnElmtId(s34);
        this.__shouldMirror.purgeDependencyOnElmtId(s34);
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

    set selectedIndexes(r34) {
        this.__selectedIndexes.set(r34);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(q34) {
        this.__componentSize.set(q34);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(p34) {
        this.__buttonBorderRadius.set(p34);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(o34) {
        this.__buttonItemsSize.set(o34);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(n34) {
        this.__buttonItemsPosition.set(n34);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(m34) {
        this.__buttonItemsSelected.set(m34);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(l34) {
        this.__buttonItemProperty.set(l34);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(k34) {
        this.__focusIndex.set(k34);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(j34) {
        this.__selectedItemPosition.set(j34);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(i34) {
        this.__zoomScaleArray.set(i34);
    }

    get shouldMirror() {
        return this.__shouldMirror.get();
    }

    set shouldMirror(h34) {
        this.__shouldMirror.set(h34);
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
        this.buttonItemsSelected.forEach((f34, g34) => {
            this.buttonItemsSelected[g34] = false;
        });
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            this.selectedIndexes.forEach(e34 => this.buttonItemsSelected[e34] = true);
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
        let z33 = this.selectedIndexes.some(b34 => {
            return (b34 === void 0 || b34 < 0 || (this.options.buttons && b34 >= this.options.buttons.length));
        });
        if (z33) {
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

    isMouseWheelScroll(x33) {
        return x33.source === SourceType.Mouse && !this.isPanGestureMoved;
    }

    isMovedFromPanGestureStartPoint(v33, w33) {
        return!nearEqual(v33, this.panGestureStartPoint.x) || !nearEqual(w33, this.panGestureStartPoint.y);
    }

    isShouldMirror() {
        if (this.options.direction == Direction.Rtl) {
            return true;
        }
        try {
            let u33 = I18n.System.getSystemLanguage();
            if (u33 === 'ug' && this.options.direction != Direction.Ltr) {
                return true;
            }
        }
        catch (t33) {
            console.error(`Ace SegmentButton getSystemLanguage, error: ${t33.toString()}`);
        }
        return false;
    }

    initialRender() {
        this.observeComponentCreation2((k32, l32) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.onBlur(() => {
                this.focusIndex = -1;
            });
            Stack.onKeyEvent((s33) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (s33.type === KeyType.Down) {
                    if (s33.keyCode === KeyCode.KEYCODE_SPACE || s33.keyCode === KeyCode.KEYCODE_ENTER ||
                        s33.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
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
            TapGesture.onAction((l33) => {
                this.focusIndex = -1;
                let m33 = l33.fingerList.find(Boolean);
                if (m33 === void 0) {
                    return;
                }
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                let n33 = m33.localX;
                let o33 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
                for (let p33 = 0; p33 < o33; p33++) {
                    n33 = n33 - this.buttonItemsSize[p33].width;
                    if (n33 >= 0) {
                        continue;
                    }
                    this.doSelectedChangeAnimate =
                        this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ? false : true;
                    let q33 = this.isShouldMirror() ? o33 - 1 - p33 : p33;
                    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                        let r33 = this.selectedIndexes.indexOf(q33);
                        if (r33 === -1) {
                            this.selectedIndexes.push(q33);
                        }
                        else {
                            this.selectedIndexes.splice(r33, 1);
                        }
                    }
                    else {
                        this.selectedIndexes[0] = q33;
                    }
                    this.doSelectedChangeAnimate = false;
                    break;
                }
            });
            TapGesture.pop();
            SwipeGesture.create();
            SwipeGesture.onAction((k33) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (this.isCurrentPositionSelected) {
                    return;
                }
                if (k33.angle > 0 && this.selectedIndexes[0] !== Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
                    this.doSelectedChangeAnimate = false;
                }
                else if (k33.angle < 0 && this.selectedIndexes[0] !== 0) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
                    this.doSelectedChangeAnimate = false;
                }
            });
            SwipeGesture.pop();
            PanGesture.create();
            PanGesture.onActionStart((g33) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let h33 = g33.fingerList.find(Boolean);
                if (h33 === void 0) {
                    return;
                }
                let i33 = h33.localX;
                this.panGestureStartPoint = { x: h33.globalX, y: h33.globalY };
                this.isPanGestureMoved = false;
                for (let j33 = 0; j33 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); j33++) {
                    i33 = i33 - this.buttonItemsSize[j33].width;
                    if (i33 < 0) {
                        this.isCurrentPositionSelected = j33 === this.selectedIndexes[0] ? true : false;
                        break;
                    }
                }
            });
            PanGesture.onActionUpdate((x32) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (!this.isCurrentPositionSelected) {
                    return;
                }
                let y32 = x32.fingerList.find(Boolean);
                if (y32 === void 0) {
                    return;
                }
                let z32 = y32.localX;
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(y32.globalX, y32.globalY)) {
                    this.isPanGestureMoved = true;
                }
                for (let f33 = 0; f33 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); f33++) {
                    z32 = z32 - this.buttonItemsSize[f33].width;
                    if (z32 < 0) {
                        this.doSelectedChangeAnimate = true;
                        this.selectedIndexes[0] = f33;
                        this.doSelectedChangeAnimate = false;
                        break;
                    }
                }
                this.zoomScaleArray.forEach((b33, c33) => {
                    if (c33 === this.selectedIndexes[0]) {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[c33] = 0.95;
                        });
                    }
                    else {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[c33] = 1;
                        });
                    }
                });
            });
            PanGesture.onActionEnd((t32) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let u32 = t32.fingerList.find(Boolean);
                if (u32 === void 0) {
                    return;
                }
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(u32.globalX, u32.globalY)) {
                    this.isPanGestureMoved = true;
                }
                if (this.isMouseWheelScroll(t32)) {
                    let w32 = t32.offsetX !== 0 ? t32.offsetX : t32.offsetY;
                    this.doSelectedChangeAnimate = true;
                    if (w32 > 0 && this.selectedIndexes[0] > 0) {
                        this.selectedIndexes[0] -= 1;
                    }
                    else if (w32 < 0 && this.selectedIndexes[0] < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
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
                                    this.observeComponentCreation2((e32, f32) => {
                                        if (f32) {
                                            let g32 = new MultiSelectBackground(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                            }, undefined, e32, () => {
                                            }, {
                                                page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                line: 1047,
                                                col: 11
                                            });
                                            ViewPU.create(g32);
                                            let h32 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options
                                                };
                                            };
                                            g32.paramsGenerator_ = h32;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(e32, {
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
                                this.observeComponentCreation2((a32, b32) => {
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
                                                line: 1061,
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
                                                line: 1067,
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
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    selectedIndexes: this.__selectedIndexes,
                                }, undefined, w30, () => {
                                }, {
                                    page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                    line: 1081,
                                    col: 9
                                });
                                ViewPU.create(y30);
                                let z30 = () => {
                                    return {
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

export default { SegmentButton, SegmentButtonOptions, SegmentButtonItemOptionsArray, SegmentButtonItemOptions };