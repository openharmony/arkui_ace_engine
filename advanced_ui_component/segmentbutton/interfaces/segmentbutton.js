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

var __decorate = (this && this.__decorate) || function (b47, c47, d47, e47) {
    var f47 = arguments.length,
        g47 = f47 < 3 ? c47 : e47 === null ? e47 = Object.getOwnPropertyDescriptor(c47, d47) : e47, h47;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        g47 = Reflect.decorate(b47, c47, d47, e47);
    else
        for (var i47 = b47.length - 1; i47 >= 0; i47--)
            if (h47 = b47[i47])
                g47 = (f47 < 3 ? h47(g47) : f47 > 3 ? h47(c47, d47, g47) : h47(c47, d47)) || g47;
    return f47 > 3 && g47 && Object.defineProperty(c47, d47, g47), g47;
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

function nearEqual(y46, z46) {
    return Math.abs(y46 - z46) < 0.001;
}

let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(x46) {
        this.icon = x46.icon;
        this.selectedIcon = x46.selectedIcon;
        this.text = x46.text;
    }
};
SegmentButtonItemOptions = __decorate([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends Array {
    constructor(u46) {
        super(typeof u46 === "number" ? u46 : 0);
        this.changeStartIndex = void 0;
        this.deleteCount = void 0;
        this.addLength = void 0;
        if (typeof u46 !== "number" && u46 !== void 0) {
            super.push(...u46.map((w46) => new SegmentButtonItemOptions(w46)));
        }
    }

    push(...r46) {
        if (this.length + r46.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        this.changeStartIndex = this.length;
        this.deleteCount = 0;
        this.addLength = r46.length;
        return super.push(...r46.map((t46) => new SegmentButtonItemOptions(t46)));
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

    unshift(...o46) {
        if (this.length + o46.length > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length;
        }
        if (o46.length > 0) {
            this.changeStartIndex = 0;
            this.deleteCount = 0;
            this.addLength = o46.length;
        }
        return super.unshift(...o46.map((q46) => new SegmentButtonItemOptions(q46)));
    }

    splice(k46, l46, ...m46) {
        let n46 = (this.length - l46) < 0 ? 0 : (this.length - l46);
        n46 += m46.length;
        if (n46 < MIN_ITEM_COUNT) {
            console.warn("Below the minimum number of elements (2).");
            return [];
        }
        if (n46 > MAX_ITEM_COUNT) {
            console.warn("Exceeded the maximum number of elements (5).");
            return [];
        }
        this.changeStartIndex = k46;
        this.deleteCount = l46;
        this.addLength = m46.length;
        return super.splice(k46, l46, ...m46);
    }

    static create(j46) {
        return new SegmentButtonItemOptionsArray_1(j46);
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

    set buttons(i46) {
        if (this._buttons !== void 0 && this._buttons !== i46) {
            this.onButtonsChange?.();
        }
        this._buttons = i46;
    }

    constructor(f46) {
        this.multiply = false;
        this.showText = false;
        this.showIcon = false;
        this._buttons = void 0;
        this.fontColor = f46.fontColor ?? segmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = f46.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = f46.fontSize ?? segmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = f46.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = f46.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = f46.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = f46.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = f46.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = f46.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = f46.buttonPadding;
        this.textPadding = f46.textPadding;
        this.type = f46.type;
        this.backgroundBlurStyle = f46.backgroundBlurStyle ?? segmentButtonTheme.BACKGROUND_BLUR_STYLE;
        this.localizedTextPadding = f46.localizedButtonPadding;
        this.localizedButtonPadding = f46.localizedButtonPadding;
        this.direction = f46.direction ?? Direction.Auto;
        this.buttons = new SegmentButtonItemOptionsArray(f46.buttons);
        if (this.type === "capsule") {
            this.multiply = f46.multiply ?? false;
            this.buttons.forEach(h46 => {
                this.showText ||= h46.text !== void 0;
                this.showIcon ||= h46.icon !== void 0 || h46.selectedIcon !== void 0;
            });
            if (this.showText && this.showIcon) {
                this.iconTextRadius = 12;
                this.iconTextBackgroundRadius = 14;
            }
            this.selectedFontColor = f46.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = f46.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
        else {
            this.showText = true;
        }
        this.componentPadding = this.multiply ? 0 : 2;
    }

    static tab(e46) {
        return new SegmentButtonOptions_1({
            type: "tab",
            buttons: e46.buttons,
            fontColor: e46.fontColor,
            selectedFontColor: e46.selectedFontColor,
            fontSize: e46.fontSize,
            selectedFontSize: e46.selectedFontSize,
            fontWeight: e46.fontWeight,
            selectedFontWeight: e46.selectedFontWeight,
            backgroundColor: e46.backgroundColor,
            selectedBackgroundColor: e46.selectedBackgroundColor,
            imageSize: e46.imageSize,
            buttonPadding: e46.buttonPadding,
            textPadding: e46.textPadding,
            localizedTextPadding: e46.localizedTextPadding,
            localizedButtonPadding: e46.localizedButtonPadding,
            backgroundBlurStyle: e46.backgroundBlurStyle,
            direction: e46.direction
        });
    }

    static capsule(d46) {
        return new SegmentButtonOptions_1({
            type: "capsule",
            buttons: d46.buttons,
            multiply: d46.multiply,
            fontColor: d46.fontColor,
            selectedFontColor: d46.selectedFontColor,
            fontSize: d46.fontSize,
            selectedFontSize: d46.selectedFontSize,
            fontWeight: d46.fontWeight,
            selectedFontWeight: d46.selectedFontWeight,
            backgroundColor: d46.backgroundColor,
            selectedBackgroundColor: d46.selectedBackgroundColor,
            imageSize: d46.imageSize,
            buttonPadding: d46.buttonPadding,
            textPadding: d46.textPadding,
            localizedTextPadding: d46.localizedTextPadding,
            localizedButtonPadding: d46.localizedButtonPadding,
            backgroundBlurStyle: d46.backgroundBlurStyle,
            direction: d46.direction
        });
    }
};
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([
    Observed
], SegmentButtonOptions);

export { SegmentButtonOptions };

class MultiSelectBackground extends ViewPU {
    constructor(x45, y45, z45, a46 = -1, b46 = undefined, c46) {
        super(x45, z45, a46, c46);
        if (typeof b46 === "function") {
            this.paramsGenerator_ = b46;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(y45.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(y45.options, this, "options");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(y45);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(w45) {
        this.__optionsArray.set(w45.optionsArray);
        this.__options.set(w45.options);
    }

    updateStateVars(v45) {
        this.__optionsArray.set(v45.optionsArray);
        this.__options.set(v45.options);
    }

    purgeVariableDependenciesOnElmtId(u45) {
        this.__optionsArray.purgeDependencyOnElmtId(u45);
        this.__options.purgeDependencyOnElmtId(u45);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(u45);
        this.__buttonItemsSize.purgeDependencyOnElmtId(u45);
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

    set buttonBorderRadius(t45) {
        this.__buttonBorderRadius.set(t45);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(s45) {
        this.__buttonItemsSize.set(s45);
    }

    initialRender() {
        this.observeComponentCreation2((q45, r45) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((b45, c45) => {
            ForEach.create();
            const d45 = (f45, g45) => {
                const h45 = f45;
                this.observeComponentCreation2((j45, k45) => {
                    If.create();
                    if (g45 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((o45, p45) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[g45].height);
                                Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[g45]);
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
            this.forEachUpdateFunction(b45, this.optionsArray, d45, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SelectItem extends ViewPU {
    constructor(t44, u44, v44, w44 = -1, x44 = undefined, y44) {
        super(t44, v44, w44, y44);
        if (typeof x44 === "function") {
            this.paramsGenerator_ = x44;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(u44.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(u44.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(u44.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__selectedItemPosition = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(u44);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(s44) {
        this.__optionsArray.set(s44.optionsArray);
        this.__options.set(s44.options);
    }

    updateStateVars(r44) {
        this.__optionsArray.set(r44.optionsArray);
        this.__options.set(r44.options);
    }

    purgeVariableDependenciesOnElmtId(q44) {
        this.__optionsArray.purgeDependencyOnElmtId(q44);
        this.__options.purgeDependencyOnElmtId(q44);
        this.__selectedIndexes.purgeDependencyOnElmtId(q44);
        this.__buttonItemsSize.purgeDependencyOnElmtId(q44);
        this.__selectedItemPosition.purgeDependencyOnElmtId(q44);
        this.__zoomScaleArray.purgeDependencyOnElmtId(q44);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(q44);
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

    set selectedIndexes(p44) {
        this.__selectedIndexes.set(p44);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(o44) {
        this.__buttonItemsSize.set(o44);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(n44) {
        this.__selectedItemPosition.set(n44);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(m44) {
        this.__zoomScaleArray.set(m44);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(l44) {
        this.__buttonBorderRadius.set(l44);
    }

    initialRender() {
        this.observeComponentCreation2((e44, f44) => {
            If.create();
            if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j44, k44) => {
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
    constructor(u43, v43, w43, x43 = -1, y43 = undefined, z43) {
        super(u43, w43, x43, z43);
        if (typeof y43 === "function") {
            this.paramsGenerator_ = y43;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(v43.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(v43.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(v43.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__multiColor = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (b44, c44) => Color.Transparent), this, "multiColor");
        this.setInitiallyProvidedValue(v43);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(t43) {
        this.__optionsArray.set(t43.optionsArray);
        this.__options.set(t43.options);
        if (t43.multiColor !== undefined) {
            this.multiColor = t43.multiColor;
        }
    }

    updateStateVars(s43) {
        this.__optionsArray.set(s43.optionsArray);
        this.__options.set(s43.options);
    }

    purgeVariableDependenciesOnElmtId(r43) {
        this.__optionsArray.purgeDependencyOnElmtId(r43);
        this.__options.purgeDependencyOnElmtId(r43);
        this.__selectedIndexes.purgeDependencyOnElmtId(r43);
        this.__buttonItemsSize.purgeDependencyOnElmtId(r43);
        this.__zoomScaleArray.purgeDependencyOnElmtId(r43);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(r43);
        this.__multiColor.purgeDependencyOnElmtId(r43);
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

    set selectedIndexes(q43) {
        this.__selectedIndexes.set(q43);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(p43) {
        this.__buttonItemsSize.set(p43);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(o43) {
        this.__zoomScaleArray.set(o43);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(n43) {
        this.__buttonBorderRadius.set(n43);
    }

    get multiColor() {
        return this.__multiColor.get();
    }

    set multiColor(m43) {
        this.__multiColor.set(m43);
    }

    onOptionsChange() {
        for (let l43 = 0; l43 < this.selectedIndexes.length; l43++) {
            this.multiColor[this.selectedIndexes[l43]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    onSelectedChange() {
        for (let k43 = 0; k43 < MAX_ITEM_COUNT; k43++) {
            this.multiColor[k43] = Color.Transparent;
        }
        for (let j43 = 0; j43 < this.selectedIndexes.length; j43++) {
            this.multiColor[this.selectedIndexes[j43]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    aboutToAppear() {
        for (let i43 = 0; i43 < this.selectedIndexes.length; i43++) {
            this.multiColor[this.selectedIndexes[i43]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    initialRender() {
        this.observeComponentCreation2((g43, h43) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((r42, s42) => {
            ForEach.create();
            const t42 = (v42, w42) => {
                const x42 = v42;
                this.observeComponentCreation2((z42, a43) => {
                    If.create();
                    if (w42 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((e43, f43) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.width(this.buttonItemsSize[w42].width);
                                Stack.height(this.buttonItemsSize[w42].height);
                                Stack.backgroundColor(this.multiColor[w42]);
                                Stack.borderRadius(this.buttonBorderRadius[w42]);
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
            this.forEachUpdateFunction(r42, this.optionsArray, t42, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SegmentButtonItem extends ViewPU {
    constructor(j42, k42, l42, m42 = -1, n42 = undefined, o42) {
        super(j42, l42, m42, o42);
        if (typeof n42 === "function") {
            this.paramsGenerator_ = n42;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(k42.selectedIndexes, this, "selectedIndexes");
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(k42.focusIndex, this, "focusIndex");
        this.__itemOptions = new SynchedPropertyNesedObjectPU(k42.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(k42.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(k42.property, this, "property");
        this.__index = new SynchedPropertySimpleOneWayPU(k42.index, this, "index");
        this.groupId = "";
        this.setInitiallyProvidedValue(k42);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(i42) {
        this.__itemOptions.set(i42.itemOptions);
        this.__options.set(i42.options);
        this.__property.set(i42.property);
        if (i42.groupId !== undefined) {
            this.groupId = i42.groupId;
        }
    }

    updateStateVars(h42) {
        this.__itemOptions.set(h42.itemOptions);
        this.__options.set(h42.options);
        this.__property.set(h42.property);
        this.__index.reset(h42.index);
    }

    purgeVariableDependenciesOnElmtId(g42) {
        this.__selectedIndexes.purgeDependencyOnElmtId(g42);
        this.__focusIndex.purgeDependencyOnElmtId(g42);
        this.__itemOptions.purgeDependencyOnElmtId(g42);
        this.__options.purgeDependencyOnElmtId(g42);
        this.__property.purgeDependencyOnElmtId(g42);
        this.__index.purgeDependencyOnElmtId(g42);
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

    set selectedIndexes(f42) {
        this.__selectedIndexes.set(f42);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(e42) {
        this.__focusIndex.set(e42);
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

    set index(d42) {
        this.__index.set(d42);
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
        this.observeComponentCreation2((b42, c42) => {
            Column.create({ space: 2 });
            Column.direction(this.options.direction);
            Column.focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.getButtonPadding());
            Column.constraintSize({ minHeight: 28 });
        }, Column);
        this.observeComponentCreation2((u41, v41) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z41, a42) => {
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
        this.observeComponentCreation2((m41, n41) => {
            If.create();
            if (this.options.showText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r41, s41) => {
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
    constructor(d41, e41, f41, g41 = -1, h41 = undefined, i41) {
        super(d41, f41, g41, i41);
        if (typeof h41 === "function") {
            this.paramsGenerator_ = h41;
        }
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(e41.press, this, "press");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(e41.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__options = new SynchedPropertyNesedObjectPU(e41.options, this, "options");
        this.pressIndex = 0;
        this.pressColor = segmentButtonTheme.PRESS_COLOR;
        this.setInitiallyProvidedValue(e41);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(c41) {
        this.__colorProperty.set(c41.colorProperty);
        this.__options.set(c41.options);
        if (c41.pressIndex !== undefined) {
            this.pressIndex = c41.pressIndex;
        }
        if (c41.pressColor !== undefined) {
            this.pressColor = c41.pressColor;
        }
    }

    updateStateVars(b41) {
        this.__press.reset(b41.press);
        this.__colorProperty.set(b41.colorProperty);
        this.__options.set(b41.options);
    }

    purgeVariableDependenciesOnElmtId(a41) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(a41);
        this.__press.purgeDependencyOnElmtId(a41);
        this.__colorProperty.purgeDependencyOnElmtId(a41);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(a41);
        this.__options.purgeDependencyOnElmtId(a41);
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

    set buttonItemsSize(z40) {
        this.__buttonItemsSize.set(z40);
    }

    get press() {
        return this.__press.get();
    }

    set press(y40) {
        this.__press.set(y40);
    }

    get colorProperty() {
        return this.__colorProperty.get();
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(x40) {
        this.__buttonBorderRadius.set(x40);
    }

    get options() {
        return this.__options.get();
    }

    initialRender() {
        this.observeComponentCreation2((v40, w40) => {
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
    constructor(z39, a40, b40, c40 = -1, d40 = undefined, e40) {
        super(z39, b40, c40, e40);
        if (typeof d40 === "function") {
            this.paramsGenerator_ = d40;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(a40.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(a40.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(a40.selectedIndexes, this, "selectedIndexes");
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
        }, (s40, t40) => false), this, "pressArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (q40, r40) => new HoverColorProperty()), this, "hoverColorArray");
        this.__buttonWidth = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (o40, p40) => 0), this, "buttonWidth");
        this.__buttonHeight = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (m40, n40) => 0), this, "buttonHeight");
        this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (k40, l40) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.setInitiallyProvidedValue(a40);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(y39) {
        this.__optionsArray.set(y39.optionsArray);
        this.__options.set(y39.options);
        if (y39.pressArray !== undefined) {
            this.pressArray = y39.pressArray;
        }
        if (y39.hoverColorArray !== undefined) {
            this.hoverColorArray = y39.hoverColorArray;
        }
        if (y39.buttonWidth !== undefined) {
            this.buttonWidth = y39.buttonWidth;
        }
        if (y39.buttonHeight !== undefined) {
            this.buttonHeight = y39.buttonHeight;
        }
        if (y39.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = y39.buttonItemsRealHeight;
        }
        if (y39.groupId !== undefined) {
            this.groupId = y39.groupId;
        }
    }

    updateStateVars(x39) {
        this.__optionsArray.set(x39.optionsArray);
        this.__options.set(x39.options);
    }

    purgeVariableDependenciesOnElmtId(w39) {
        this.__optionsArray.purgeDependencyOnElmtId(w39);
        this.__options.purgeDependencyOnElmtId(w39);
        this.__selectedIndexes.purgeDependencyOnElmtId(w39);
        this.__componentSize.purgeDependencyOnElmtId(w39);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(w39);
        this.__buttonItemsSize.purgeDependencyOnElmtId(w39);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(w39);
        this.__focusIndex.purgeDependencyOnElmtId(w39);
        this.__zoomScaleArray.purgeDependencyOnElmtId(w39);
        this.__buttonItemProperty.purgeDependencyOnElmtId(w39);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(w39);
        this.__pressArray.purgeDependencyOnElmtId(w39);
        this.__hoverColorArray.purgeDependencyOnElmtId(w39);
        this.__buttonWidth.purgeDependencyOnElmtId(w39);
        this.__buttonHeight.purgeDependencyOnElmtId(w39);
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

    set selectedIndexes(v39) {
        this.__selectedIndexes.set(v39);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(u39) {
        this.__componentSize.set(u39);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(t39) {
        this.__buttonBorderRadius.set(t39);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(s39) {
        this.__buttonItemsSize.set(s39);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(r39) {
        this.__buttonItemsPosition.set(r39);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(q39) {
        this.__focusIndex.set(q39);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(p39) {
        this.__zoomScaleArray.set(p39);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(o39) {
        this.__buttonItemProperty.set(o39);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(n39) {
        this.__buttonItemsSelected.set(n39);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(m39) {
        this.__pressArray.set(m39);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(l39) {
        this.__hoverColorArray.set(l39);
    }

    get buttonWidth() {
        return this.__buttonWidth.get();
    }

    set buttonWidth(k39) {
        this.__buttonWidth.set(k39);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(j39) {
        this.__buttonHeight.set(j39);
    }

    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((h39, i39) => {
            this.buttonWidth[i39] = h39.width;
            this.buttonHeight[i39] = h39.height;
        });
    }

    changeSelectedIndexes(v38) {
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
            let w38 = this.selectedIndexes;
            for (let b39 = 0; b39 < this.optionsArray.deleteCount; b39++) {
                let c39 = w38.indexOf(this.optionsArray.changeStartIndex);
                let d39 = w38.map(f39 => this.optionsArray.changeStartIndex &&
                    (f39 > this.optionsArray.changeStartIndex) ? f39 - 1 : f39);
                if (c39 !== -1) {
                    d39.splice(c39, 1);
                }
                w38 = d39;
            }
            for (let x38 = 0; x38 < this.optionsArray.addLength; x38++) {
                let y38 = w38.map(a39 => this.optionsArray.changeStartIndex &&
                    (a39 >= this.optionsArray.changeStartIndex) ? a39 + 1 : a39);
                w38 = y38;
            }
            this.selectedIndexes = w38;
        }
    }

    changeFocusIndex(u38) {
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
        let t38 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 &&
            this.optionsArray.addLength !== void 0) {
            this.changeSelectedIndexes(t38);
            this.changeFocusIndex(t38);
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
        for (let s38 = 0; s38 < this.buttonItemsRealHeight.length; s38++) {
            this.buttonItemsRealHeight[s38] = 0;
        }
    }

    getBorderRadius(q38) {
        let r38 = this.buttonBorderRadius[q38];
        if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex]) {
            r38.topStart = LengthMetrics.vp(r38.topStart.value + 4);
            r38.topEnd = LengthMetrics.vp(r38.topStart.value + 4);
            r38.bottomStart = LengthMetrics.vp(r38.topStart.value + 4);
            r38.bottomEnd = LengthMetrics.vp(r38.topStart.value + 4);
        }
        return r38;
    }

    focusStack(i38, j38 = null) {
        this.observeComponentCreation2((o38, p38) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((m38, n38) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.borderRadius(this.getBorderRadius(i38));
            Stack.size({
                width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonWidth[i38] + 8 : this.buttonWidth[i38],
                height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonHeight[i38] + 8 : this.buttonHeight[i38]
            });
            Stack.borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR);
            Stack.borderWidth(2);
        }, Stack);
        Stack.pop();
        Stack.pop();
    }

    calculateBorderRadius() {
        let c38 = Array.from({
            length: MAX_ITEM_COUNT
        }, (g38, h38) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        });
        for (let e38 = 0; e38 < this.buttonBorderRadius.length; e38++) {
            let f38 = this.buttonItemsSize[e38].height / 2;
            if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                c38[e38].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? f38);
                c38[e38].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? f38);
                c38[e38].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? f38);
                c38[e38].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? f38);
            }
            else {
                if (e38 === 0) {
                    c38[e38].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? f38);
                    c38[e38].topEnd = LengthMetrics.vp(0);
                    c38[e38].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? f38);
                    c38[e38].bottomEnd = LengthMetrics.vp(0);
                }
                else if (this.options.buttons && e38 === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    c38[e38].topStart = LengthMetrics.vp(0);
                    c38[e38].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? f38);
                    c38[e38].bottomStart = LengthMetrics.vp(0);
                    c38[e38].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? f38);
                }
                else {
                    c38[e38].topStart = LengthMetrics.vp(0);
                    c38[e38].topEnd = LengthMetrics.vp(0);
                    c38[e38].bottomStart = LengthMetrics.vp(0);
                    c38[e38].bottomEnd = LengthMetrics.vp(0);
                }
            }
        }
        this.buttonBorderRadius = c38;
    }

    initialRender() {
        this.observeComponentCreation2((o35, p35) => {
            If.create();
            if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x37, y37) => {
                        Row.create({ space: 1 });
                        Row.direction(this.options.direction);
                        Row.focusScopeId(this.groupId, true);
                        Row.padding(this.options.componentPadding);
                        Row.onSizeChange((a38, b38) => {
                            this.componentSize = { width: b38.width, height: b38.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((u35, v35) => {
                        ForEach.create();
                        const w35 = (y35, z35) => {
                            const a36 = y35;
                            this.observeComponentCreation2((c36, d36) => {
                                If.create();
                                if (z35 < MAX_ITEM_COUNT) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((d37, e37) => {
                                            Stack.create();
                                            Stack.direction(this.options.direction);
                                            Stack.borderRadius(this.buttonBorderRadius[z35]);
                                            Stack.scale({
                                                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[z35],
                                                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[z35]
                                            });
                                            Stack.layoutWeight(1);
                                            Stack.onSizeChange((v37, w37) => {
                                                this.buttonItemsSize[z35] = {
                                                    width: w37.width,
                                                    height: this.buttonItemsSize[z35].height
                                                };
                                                if (w37.width) {
                                                    this.buttonItemsPosition[z35] = {
                                                        x: Number.parseFloat(this.options.componentPadding.toString()) +
                                                            (Number.parseFloat(w37.width.toString()) + 1) * z35,
                                                        y: Number.parseFloat(this.options.componentPadding.toString())
                                                    };
                                                }
                                            });
                                            ViewStackProcessor.visualState("normal");
                                            Stack.overlay(undefined);
                                            ViewStackProcessor.visualState("focused");
                                            Stack.overlay({ builder: () => {
                                                this.focusStack.call(this, z35);
                                            } }, {
                                                align: Alignment.Center
                                            });
                                            ViewStackProcessor.visualState();
                                            Stack.onFocus(() => {
                                                this.focusIndex = z35;
                                            });
                                            Stack.onTouch((s37) => {
                                                if (s37.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (s37.type === TouchType.Down) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[z35] = 0.95;
                                                    });
                                                }
                                                else if (s37.type === TouchType.Up) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[z35] = 1;
                                                    });
                                                }
                                            });
                                            Stack.onHover((p37) => {
                                                if (p37) {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[z35].hoverColor = (segmentButtonTheme.HOVER_COLOR);
                                                    });
                                                }
                                                else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[z35].hoverColor = Color.Transparent;
                                                    });
                                                }
                                            });
                                            Stack.onMouse((k37) => {
                                                switch (k37.action) {
                                                    case MouseAction.Press:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[z35] = 0.95;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[z35] = true;
                                                        });
                                                        break;
                                                    case MouseAction.Release:
                                                        Context.animateTo({
                                                            curve: curves.springMotion(0.347, 0.99)
                                                        }, () => {
                                                            this.zoomScaleArray[z35] = 1;
                                                        });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[z35] = false;
                                                        });
                                                        break;
                                                }
                                            });
                                        }, Stack);
                                        {
                                            this.observeComponentCreation2((x36, y36) => {
                                                if (y36) {
                                                    let z36 = new PressAndHoverEffect(this, {
                                                        pressIndex: z35,
                                                        colorProperty: this.hoverColorArray[z35],
                                                        press: this.pressArray[z35],
                                                        options: this.options,
                                                    }, undefined, x36, () => {
                                                    }, {
                                                        page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                        line: 770,
                                                        col: 15
                                                    });
                                                    ViewPU.create(z36);
                                                    let a37 = () => {
                                                        return {
                                                            pressIndex: z35,
                                                            colorProperty: this.hoverColorArray[z35],
                                                            press: this.pressArray[z35],
                                                            options: this.options
                                                        };
                                                    };
                                                    z36.paramsGenerator_ = a37;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(x36, {
                                                        colorProperty: this.hoverColorArray[z35],
                                                        press: this.pressArray[z35],
                                                        options: this.options
                                                    });
                                                }
                                            }, { name: "PressAndHoverEffect" });
                                        }
                                        this.observeComponentCreation2((p36, q36) => {
                                            __Common__.create();
                                            __Common__.onSizeChange((s36, t36) => {
                                                this.buttonItemsRealHeight[z35] = t36.height;
                                                let u36 = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ?
                                                this.options.buttons.length : 0));
                                                for (let v36 = 0; v36 < this.buttonItemsSize.length; v36++) {
                                                    this.buttonItemsSize[v36] = {
                                                        width: this.buttonItemsSize[v36].width,
                                                        height: u36
                                                    };
                                                }
                                                this.calculateBorderRadius();
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((j36, k36) => {
                                                if (k36) {
                                                    let l36 = new SegmentButtonItem(this, {
                                                        selectedIndexes: this.__selectedIndexes,
                                                        focusIndex: this.__focusIndex,
                                                        index: z35,
                                                        itemOptions: a36,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[z35],
                                                        groupId: this.groupId
                                                    }, undefined, j36, () => {
                                                    }, {
                                                        page: "library/src/main/ets/components/segmentbutton/segmentbutton.ets",
                                                        line: 776,
                                                        col: 15
                                                    });
                                                    ViewPU.create(l36);
                                                    let m36 = () => {
                                                        return {
                                                            selectedIndexes: this.selectedIndexes,
                                                            focusIndex: this.focusIndex,
                                                            index: z35,
                                                            itemOptions: a36,
                                                            options: this.options,
                                                            property: this.buttonItemProperty[z35],
                                                            groupId: this.groupId
                                                        };
                                                    };
                                                    l36.paramsGenerator_ = m36;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(j36, {
                                                        index: z35,
                                                        itemOptions: a36,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[z35]
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
                        this.forEachUpdateFunction(u35, this.optionsArray, w35, undefined, true, false);
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
    constructor(p34, q34, r34, s34 = -1, t34 = undefined, u34) {
        super(p34, r34, s34, u34);
        if (typeof t34 === "function") {
            this.paramsGenerator_ = t34;
        }
        this.__options = new SynchedPropertyNesedObjectPU(q34.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(q34.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, "componentSize");
        this.addProvidedVar("componentSize", this.__componentSize, false);
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (l35, m35) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        }), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.__buttonBorderRadius, false);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (j35, k35) => {
            return {};
        }), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.__buttonItemsSize, false);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (h35, i35) => {
            return {};
        }), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.__buttonItemsPosition, false);
        this.__buttonItemsSelected = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (f35, g35) => false), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected, false);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (d35, e35) => new ItemProperty()), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty, false);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex, false);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition, false);
        this.__zoomScaleArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (b35, c35) => 1.0), this, "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.__zoomScaleArray, false);
        this.doSelectedChangeAnimate = false;
        this.isCurrentPositionSelected = false;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = false;
        this.setInitiallyProvidedValue(q34);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.declareWatch("buttonItemsPosition", this.onItemsPositionChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(o34) {
        this.__options.set(o34.options);
        if (o34.componentSize !== undefined) {
            this.componentSize = o34.componentSize;
        }
        if (o34.buttonBorderRadius !== undefined) {
            this.buttonBorderRadius = o34.buttonBorderRadius;
        }
        if (o34.buttonItemsSize !== undefined) {
            this.buttonItemsSize = o34.buttonItemsSize;
        }
        if (o34.buttonItemsPosition !== undefined) {
            this.buttonItemsPosition = o34.buttonItemsPosition;
        }
        if (o34.buttonItemsSelected !== undefined) {
            this.buttonItemsSelected = o34.buttonItemsSelected;
        }
        if (o34.buttonItemProperty !== undefined) {
            this.buttonItemProperty = o34.buttonItemProperty;
        }
        if (o34.focusIndex !== undefined) {
            this.focusIndex = o34.focusIndex;
        }
        if (o34.selectedItemPosition !== undefined) {
            this.selectedItemPosition = o34.selectedItemPosition;
        }
        if (o34.zoomScaleArray !== undefined) {
            this.zoomScaleArray = o34.zoomScaleArray;
        }
        if (o34.doSelectedChangeAnimate !== undefined) {
            this.doSelectedChangeAnimate = o34.doSelectedChangeAnimate;
        }
        if (o34.isCurrentPositionSelected !== undefined) {
            this.isCurrentPositionSelected = o34.isCurrentPositionSelected;
        }
        if (o34.panGestureStartPoint !== undefined) {
            this.panGestureStartPoint = o34.panGestureStartPoint;
        }
        if (o34.isPanGestureMoved !== undefined) {
            this.isPanGestureMoved = o34.isPanGestureMoved;
        }
    }

    updateStateVars(n34) {
        this.__options.set(n34.options);
    }

    purgeVariableDependenciesOnElmtId(m34) {
        this.__options.purgeDependencyOnElmtId(m34);
        this.__selectedIndexes.purgeDependencyOnElmtId(m34);
        this.__componentSize.purgeDependencyOnElmtId(m34);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(m34);
        this.__buttonItemsSize.purgeDependencyOnElmtId(m34);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(m34);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(m34);
        this.__buttonItemProperty.purgeDependencyOnElmtId(m34);
        this.__focusIndex.purgeDependencyOnElmtId(m34);
        this.__selectedItemPosition.purgeDependencyOnElmtId(m34);
        this.__zoomScaleArray.purgeDependencyOnElmtId(m34);
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

    set selectedIndexes(l34) {
        this.__selectedIndexes.set(l34);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(k34) {
        this.__componentSize.set(k34);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(j34) {
        this.__buttonBorderRadius.set(j34);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(i34) {
        this.__buttonItemsSize.set(i34);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(h34) {
        this.__buttonItemsPosition.set(h34);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(g34) {
        this.__buttonItemsSelected.set(g34);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(f34) {
        this.__buttonItemProperty.set(f34);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(e34) {
        this.__focusIndex.set(e34);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(d34) {
        this.__selectedItemPosition.set(d34);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(c34) {
        this.__zoomScaleArray.set(c34);
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
        this.buttonItemsSelected.forEach((a34, b34) => {
            this.buttonItemsSelected[b34] = false;
        });
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            this.selectedIndexes.forEach(z33 => this.buttonItemsSelected[z33] = true);
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
        let u33 = this.selectedIndexes.some(w33 => {
            return (w33 === void 0 || w33 < 0 || (this.options.buttons && w33 >= this.options.buttons.length));
        });
        if (u33) {
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

    isMouseWheelScroll(s33) {
        return s33.source === SourceType.Mouse && !this.isPanGestureMoved;
    }

    isMovedFromPanGestureStartPoint(q33, r33) {
        return!nearEqual(q33, this.panGestureStartPoint.x) || !nearEqual(r33, this.panGestureStartPoint.y);
    }

    initialRender() {
        this.observeComponentCreation2((k32, l32) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.onBlur(() => {
                this.focusIndex = -1;
            });
            Stack.onKeyEvent((p33) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (p33.type === KeyType.Down) {
                    if (p33.keyCode === KeyCode.KEYCODE_SPACE || p33.keyCode === KeyCode.KEYCODE_ENTER ||
                        p33.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
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
                for (let o33 = 0; o33 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); o33++) {
                    n33 = n33 - this.buttonItemsSize[o33].width;
                    if (n33 >= 0) {
                        continue;
                    }
                    this.doSelectedChangeAnimate =
                        this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ? false : true;
                    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                        if (this.selectedIndexes.indexOf(o33) === -1) {
                            this.selectedIndexes.push(o33);
                        }
                        else {
                            this.selectedIndexes.splice(this.selectedIndexes.indexOf(o33), 1);
                        }
                    }
                    else {
                        this.selectedIndexes[0] = o33;
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
                                                line: 1027,
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
                                                line: 1041,
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
                                                line: 1047,
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
                                    line: 1061,
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