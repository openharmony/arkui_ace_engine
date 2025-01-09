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

var __decorate = (this && this.__decorate) || function (r37, s37, t37, u37) {
    var v37 = arguments.length,
        w37 = v37 < 3 ? s37 : u37 === null ? u37 = Object.getOwnPropertyDescriptor(s37, t37) : u37, x37;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") {
        w37 = Reflect.decorate(r37, s37, t37, u37);
    } else {
        for (var y37 = r37.length - 1; y37 >= 0; y37--) {
            if (x37 = r37[y37]) {
                w37 = (v37 < 3 ? x37(w37) : v37 > 3 ? x37(s37, t37, w37) : x37(s37, t37)) || w37;
            }
        }
    }
    return v37 > 3 && w37 && Object.defineProperty(s37, t37, w37), w37;
};
var SegmentButtonItemOptionsArray_1, SegmentButtonOptions_1;
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}
const curves = globalThis.requireNativeModule('ohos.curves');
const KeyCode = globalThis.requireNapi('multimodalInput.keyCode').KeyCode;
const util = globalThis.requireNapi('util');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const I18n = requireNapi('i18n');

const MIN_ITEM_COUNT = 2;
const MAX_ITEM_COUNT = 5;
const DEFAULT_MAX_FONT_SCALE = 1;
const MAX_MAX_FONT_SCALE = 2;
const MIN_MAX_FONT_SCALE = 1;
const segmentButtonTheme = {
    FONT_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_unselected_text_color'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    TAB_SELECTED_FONT_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_checked_text_color'],
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
        params: ['sys.float.segment_button_unselected_text_size'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    SELECTED_FONT_SIZE: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_checked_text_size'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    BACKGROUND_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_backboard_color'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    TAB_SELECTED_BACKGROUND_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_checked_foreground_color'],
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
        params: ['sys.color.ohos_id_color_focused_outline'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    HOVER_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_hover_color'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    PRESS_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_press_color'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    BACKGROUND_BLUR_STYLE: LengthMetrics.resource({
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_background_blur_style'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    })
        .value,
    SEGMENT_BUTTON_PADDING: LengthMetrics.resource({
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_baseplate_padding'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    }).value,
    CONSTRAINT_SIZE_MIN_HEIGHT: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_height'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    SEGMENT_BUTTON_MIN_FONT_SIZE: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_min_font_size'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    SEGMENT_BUTTON_NORMAL_BORDER_RADIUS: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_normal_border_radius'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    SEGMENT_ITEM_TEXT_OVERFLOW: LengthMetrics.resource({
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_marquee'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    }).value === 0.0,
    SEGMENT_BUTTON_FOCUS_TEXT_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_focus_text_primary'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    SEGMENT_BUTTON_SHADOW: LengthMetrics.resource({
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_shadow'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    }).value,
    SEGMENT_TEXT_HORIZONTAL_PADDING: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_text_l_r_padding'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    SEGMENT_TEXT_VERTICAL_PADDING: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_text_u_d_padding'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_button_text_capsule_u_d_padding'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR: {
        "id": -1,
        "type": 10001,
        params: ['sys.color.segment_button_focus_backboard_primary'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    },
    SEGMENT_FOCUS_STYLE_CUSTOMIZED: LengthMetrics.resource({
        "id": -1,
        "type": 10002,
        params: ['sys.float.segment_focus_control'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    }).value === 0.0
};

function nearEqual(o37, p37) {
    return Math.abs(o37 - p37) < 0.001;
}

let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(n37) {
        this.icon = n37.icon;
        this.selectedIcon = n37.selectedIcon;
        this.text = n37.text;
        this.iconAccessibilityText = n37.iconAccessibilityText;
        this.selectedIconAccessibilityText = n37.selectedIconAccessibilityText;
        this.accessibilityLevel = n37.accessibilityLevel;
        this.accessibilityDescription = n37.accessibilityDescription;
    }
};
SegmentButtonItemOptions = __decorate([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray =
    SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends Array {
        constructor(k37) {
            super(typeof k37 === 'number' ? k37 : 0);
            this.changeStartIndex = void 0;
            this.deleteCount = void 0;
            this.addLength = void 0;
            if (typeof k37 !== 'number' && k37 !== void 0) {
                super.push(...k37.map((m37) => new SegmentButtonItemOptions(m37)));
            }
        }

        push(...h37) {
            if (this.length + h37.length > MAX_ITEM_COUNT) {
                console.warn('Exceeded the maximum number of elements (5).');
                return this.length;
            }
            this.changeStartIndex = this.length;
            this.deleteCount = 0;
            this.addLength = h37.length;
            return super.push(...h37.map((j37) => new SegmentButtonItemOptions(j37)));
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

        unshift(...e37) {
            if (this.length + e37.length > MAX_ITEM_COUNT) {
                console.warn('Exceeded the maximum number of elements (5).');
                return this.length;
            }
            if (e37.length > 0) {
                this.changeStartIndex = 0;
                this.deleteCount = 0;
                this.addLength = e37.length;
            }
            return super.unshift(...e37.map((g37) => new SegmentButtonItemOptions(g37)));
        }

        splice(a37, b37, ...c37) {
            let d37 = (this.length - b37) < 0 ? 0 : (this.length - b37);
            d37 += c37.length;
            if (d37 < MIN_ITEM_COUNT) {
                console.warn('Below the minimum number of elements (2).');
                return [];
            }
            if (d37 > MAX_ITEM_COUNT) {
                console.warn('Exceeded the maximum number of elements (5).');
                return [];
            }
            this.changeStartIndex = a37;
            this.deleteCount = b37;
            this.addLength = c37.length;
            return super.splice(a37, b37, ...c37);
        }

        static create(z36) {
            return new SegmentButtonItemOptionsArray_1(z36);
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

    set buttons(y36) {
        if (this._buttons !== void 0 && this._buttons !== y36) {
            this.onButtonsChange?.();
        }
        this._buttons = y36;
    }

    constructor(x36) {
        this.multiply = false;
        this.showText = false;
        this.showIcon = false;
        this._buttons = void 0;
        this.fontColor = x36.fontColor ?? segmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = x36.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = x36.fontSize ?? segmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = x36.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = x36.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = x36.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = x36.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = x36.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = x36.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = x36.buttonPadding;
        this.textPadding = x36.textPadding;
        this.type = x36.type;
        this.backgroundBlurStyle = x36.backgroundBlurStyle ?? segmentButtonTheme.BACKGROUND_BLUR_STYLE;
        this.localizedTextPadding = x36.localizedTextPadding;
        this.localizedButtonPadding = x36.localizedButtonPadding;
        this.direction = x36.direction ?? Direction.Auto;
        this.buttons = new SegmentButtonItemOptionsArray(x36.buttons);
        if (this.type === 'capsule') {
            this.multiply = x36.multiply ?? false;
            this.onButtonsUpdated();
            this.selectedFontColor = x36.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = x36.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        } else {
            this.showText = true;
        }
        this.componentPadding = this.multiply ? 0 : segmentButtonTheme.SEGMENT_BUTTON_PADDING;
    }

    onButtonsUpdated() {
        this.buttons?.forEach(w36 => {
            this.showText ||= w36.text !== void 0;
            this.showIcon ||= w36.icon !== void 0 || w36.selectedIcon !== void 0;
        });
        if (this.showText && this.showIcon) {
            this.iconTextRadius = 12;
            this.iconTextBackgroundRadius = 14;
        }
    }

    static tab(u36) {
        return new SegmentButtonOptions_1({
            type: 'tab',
            buttons: u36.buttons,
            fontColor: u36.fontColor,
            selectedFontColor: u36.selectedFontColor,
            fontSize: u36.fontSize,
            selectedFontSize: u36.selectedFontSize,
            fontWeight: u36.fontWeight,
            selectedFontWeight: u36.selectedFontWeight,
            backgroundColor: u36.backgroundColor,
            selectedBackgroundColor: u36.selectedBackgroundColor,
            imageSize: u36.imageSize,
            buttonPadding: u36.buttonPadding,
            textPadding: u36.textPadding,
            localizedTextPadding: u36.localizedTextPadding,
            localizedButtonPadding: u36.localizedButtonPadding,
            backgroundBlurStyle: u36.backgroundBlurStyle,
            direction: u36.direction
        });
    }

    static capsule(t36) {
        return new SegmentButtonOptions_1({
            type: 'capsule',
            buttons: t36.buttons,
            multiply: t36.multiply,
            fontColor: t36.fontColor,
            selectedFontColor: t36.selectedFontColor,
            fontSize: t36.fontSize,
            selectedFontSize: t36.selectedFontSize,
            fontWeight: t36.fontWeight,
            selectedFontWeight: t36.selectedFontWeight,
            backgroundColor: t36.backgroundColor,
            selectedBackgroundColor: t36.selectedBackgroundColor,
            imageSize: t36.imageSize,
            buttonPadding: t36.buttonPadding,
            textPadding: t36.textPadding,
            localizedTextPadding: t36.localizedTextPadding,
            localizedButtonPadding: t36.localizedButtonPadding,
            backgroundBlurStyle: t36.backgroundBlurStyle,
            direction: t36.direction
        });
    }
};
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([
    Observed
], SegmentButtonOptions);

export { SegmentButtonOptions };

class MultiSelectBackground extends ViewPU {
    constructor(n36, o36, p36, q36 = -1, r36 = undefined, s36) {
        super(n36, p36, q36, s36);
        if (typeof r36 === "function") {
            this.paramsGenerator_ = r36;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(o36.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(o36.options, this, "options");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(o36);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(m36) {
        this.__optionsArray.set(m36.optionsArray);
        this.__options.set(m36.options);
    }

    updateStateVars(l36) {
        this.__optionsArray.set(l36.optionsArray);
        this.__options.set(l36.options);
    }

    purgeVariableDependenciesOnElmtId(k36) {
        this.__optionsArray.purgeDependencyOnElmtId(k36);
        this.__options.purgeDependencyOnElmtId(k36);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(k36);
        this.__buttonItemsSize.purgeDependencyOnElmtId(k36);
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

    set buttonBorderRadius(j36) {
        this.__buttonBorderRadius.set(j36);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(i36) {
        this.__buttonItemsSize.set(i36);
    }

    initialRender() {
        this.observeComponentCreation2((g36, h36) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((r35, s35) => {
            ForEach.create();
            const t35 = (v35, w35) => {
                const x35 = v35;
                this.observeComponentCreation2((z35, a36) => {
                    If.create();
                    if (w35 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((e36, f36) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[w35].height);
                                Stack.backgroundColor(this.options.backgroundColor ??
                                segmentButtonTheme.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[w35]);
                                Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
                            }, Stack);
                            Stack.pop();
                        });
                    } else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(r35, this.optionsArray, t35, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SelectItem extends ViewPU {
    constructor(j35, k35, l35, m35 = -1, n35 = undefined, o35) {
        super(j35, l35, m35, o35);
        if (typeof n35 === "function") {
            this.paramsGenerator_ = n35;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(k35.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(k35.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(k35.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__selectedItemPosition = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(k35);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(i35) {
        this.__optionsArray.set(i35.optionsArray);
        this.__options.set(i35.options);
    }

    updateStateVars(h35) {
        this.__optionsArray.set(h35.optionsArray);
        this.__options.set(h35.options);
    }

    purgeVariableDependenciesOnElmtId(g35) {
        this.__optionsArray.purgeDependencyOnElmtId(g35);
        this.__options.purgeDependencyOnElmtId(g35);
        this.__selectedIndexes.purgeDependencyOnElmtId(g35);
        this.__buttonItemsSize.purgeDependencyOnElmtId(g35);
        this.__selectedItemPosition.purgeDependencyOnElmtId(g35);
        this.__zoomScaleArray.purgeDependencyOnElmtId(g35);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(g35);
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

    set selectedIndexes(f35) {
        this.__selectedIndexes.set(f35);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(e35) {
        this.__buttonItemsSize.set(e35);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(d35) {
        this.__selectedItemPosition.set(d35);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(c35) {
        this.__zoomScaleArray.set(c35);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(b35) {
        this.__buttonBorderRadius.set(b35);
    }

    initialRender() {
        this.observeComponentCreation2((u34, v34) => {
            If.create();
            if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z34, a35) => {
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
                        Stack.shadow(segmentButtonTheme.SEGMENT_BUTTON_SHADOW);
                    }, Stack);
                    Stack.pop();
                });
            } else {
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
    constructor(k34, l34, m34, n34 = -1, o34 = undefined, p34) {
        super(k34, m34, n34, p34);
        if (typeof o34 === "function") {
            this.paramsGenerator_ = o34;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(l34.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(l34.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(l34.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__multiColor =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (r34, s34) => Color.Transparent), this,
                "multiColor");
        this.setInitiallyProvidedValue(l34);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(j34) {
        this.__optionsArray.set(j34.optionsArray);
        this.__options.set(j34.options);
        if (j34.multiColor !== undefined) {
            this.multiColor = j34.multiColor;
        }
    }

    updateStateVars(i34) {
        this.__optionsArray.set(i34.optionsArray);
        this.__options.set(i34.options);
    }

    purgeVariableDependenciesOnElmtId(h34) {
        this.__optionsArray.purgeDependencyOnElmtId(h34);
        this.__options.purgeDependencyOnElmtId(h34);
        this.__selectedIndexes.purgeDependencyOnElmtId(h34);
        this.__buttonItemsSize.purgeDependencyOnElmtId(h34);
        this.__zoomScaleArray.purgeDependencyOnElmtId(h34);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(h34);
        this.__multiColor.purgeDependencyOnElmtId(h34);
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

    set selectedIndexes(g34) {
        this.__selectedIndexes.set(g34);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(f34) {
        this.__buttonItemsSize.set(f34);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(e34) {
        this.__zoomScaleArray.set(e34);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(d34) {
        this.__buttonBorderRadius.set(d34);
    }

    get multiColor() {
        return this.__multiColor.get();
    }

    set multiColor(c34) {
        this.__multiColor.set(c34);
    }

    onOptionsChange() {
        for (let b34 = 0; b34 < this.selectedIndexes.length; b34++) {
            this.multiColor[this.selectedIndexes[b34]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    onSelectedChange() {
        for (let a34 = 0; a34 < MAX_ITEM_COUNT; a34++) {
            this.multiColor[a34] = Color.Transparent;
        }
        for (let z33 = 0; z33 < this.selectedIndexes.length; z33++) {
            this.multiColor[this.selectedIndexes[z33]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    aboutToAppear() {
        for (let y33 = 0; y33 < this.selectedIndexes.length; y33++) {
            this.multiColor[this.selectedIndexes[y33]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    initialRender() {
        this.observeComponentCreation2((w33, x33) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((h33, i33) => {
            ForEach.create();
            const j33 = (l33, m33) => {
                const n33 = l33;
                this.observeComponentCreation2((p33, q33) => {
                    If.create();
                    if (m33 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((u33, v33) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.width(this.buttonItemsSize[m33].width);
                                Stack.height(this.buttonItemsSize[m33].height);
                                Stack.backgroundColor(this.multiColor[m33]);
                                Stack.borderRadius(this.buttonBorderRadius[m33]);
                            }, Stack);
                            Stack.pop();
                        });
                    } else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(h33, this.optionsArray, j33, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SegmentButtonItem extends ViewPU {
    constructor(z32, a33, b33, c33 = -1, d33 = undefined, e33) {
        super(z32, b33, c33, e33);
        if (typeof d33 === "function") {
            this.paramsGenerator_ = d33;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(a33.selectedIndexes, this, "selectedIndexes");
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(a33.focusIndex, this, "focusIndex");
        this.__maxFontScale = new SynchedPropertyObjectOneWayPU(a33.maxFontScale, this, "maxFontScale");
        this.__itemOptions = new SynchedPropertyNesedObjectPU(a33.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(a33.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(a33.property, this, "property");
        this.__index = new SynchedPropertySimpleOneWayPU(a33.index, this, "index");
        this.__isTextSupportMarquee =
            new ObservedPropertySimplePU(segmentButtonTheme.SEGMENT_ITEM_TEXT_OVERFLOW, this, "isTextSupportMarquee");
        this.__isMarqueeAndFadeout =
            new SynchedPropertySimpleOneWayPU(a33.isMarqueeAndFadeout, this, "isMarqueeAndFadeout");
        this.__isSegmentFocusStyleCustomized =
            new SynchedPropertySimpleOneWayPU(a33.isSegmentFocusStyleCustomized, this, "isSegmentFocusStyleCustomized");
        this.__isTextInMarqueeCondition = new ObservedPropertySimplePU(false, this, "isTextInMarqueeCondition");
        this.__isButtonTextFadeout = new ObservedPropertySimplePU(false, this, "isButtonTextFadeout");
        this.groupId = '';
        this.__hover = new SynchedPropertySimpleOneWayPU(a33.hover, this, "hover");
        this.setInitiallyProvidedValue(a33);
        this.declareWatch("focusIndex", this.onFocusIndex);
        this.declareWatch("hover", this.onFocusIndex);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(y32) {
        this.__itemOptions.set(y32.itemOptions);
        this.__options.set(y32.options);
        this.__property.set(y32.property);
        if (y32.isTextSupportMarquee !== undefined) {
            this.isTextSupportMarquee = y32.isTextSupportMarquee;
        }
        if (y32.isTextInMarqueeCondition !== undefined) {
            this.isTextInMarqueeCondition = y32.isTextInMarqueeCondition;
        }
        if (y32.isButtonTextFadeout !== undefined) {
            this.isButtonTextFadeout = y32.isButtonTextFadeout;
        }
        if (y32.groupId !== undefined) {
            this.groupId = y32.groupId;
        }
    }

    updateStateVars(x32) {
        this.__maxFontScale.reset(x32.maxFontScale);
        this.__itemOptions.set(x32.itemOptions);
        this.__options.set(x32.options);
        this.__property.set(x32.property);
        this.__index.reset(x32.index);
        this.__isMarqueeAndFadeout.reset(x32.isMarqueeAndFadeout);
        this.__isSegmentFocusStyleCustomized.reset(x32.isSegmentFocusStyleCustomized);
        this.__hover.reset(x32.hover);
    }

    purgeVariableDependenciesOnElmtId(w32) {
        this.__selectedIndexes.purgeDependencyOnElmtId(w32);
        this.__focusIndex.purgeDependencyOnElmtId(w32);
        this.__maxFontScale.purgeDependencyOnElmtId(w32);
        this.__itemOptions.purgeDependencyOnElmtId(w32);
        this.__options.purgeDependencyOnElmtId(w32);
        this.__property.purgeDependencyOnElmtId(w32);
        this.__index.purgeDependencyOnElmtId(w32);
        this.__isTextSupportMarquee.purgeDependencyOnElmtId(w32);
        this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(w32);
        this.__isSegmentFocusStyleCustomized.purgeDependencyOnElmtId(w32);
        this.__isTextInMarqueeCondition.purgeDependencyOnElmtId(w32);
        this.__isButtonTextFadeout.purgeDependencyOnElmtId(w32);
        this.__hover.purgeDependencyOnElmtId(w32);
    }

    aboutToBeDeleted() {
        this.__selectedIndexes.aboutToBeDeleted();
        this.__focusIndex.aboutToBeDeleted();
        this.__maxFontScale.aboutToBeDeleted();
        this.__itemOptions.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__property.aboutToBeDeleted();
        this.__index.aboutToBeDeleted();
        this.__isTextSupportMarquee.aboutToBeDeleted();
        this.__isMarqueeAndFadeout.aboutToBeDeleted();
        this.__isSegmentFocusStyleCustomized.aboutToBeDeleted();
        this.__isTextInMarqueeCondition.aboutToBeDeleted();
        this.__isButtonTextFadeout.aboutToBeDeleted();
        this.__hover.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }

    set selectedIndexes(v32) {
        this.__selectedIndexes.set(v32);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(u32) {
        this.__focusIndex.set(u32);
    }

    get maxFontScale() {
        return this.__maxFontScale.get();
    }

    set maxFontScale(t32) {
        this.__maxFontScale.set(t32);
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

    set index(s32) {
        this.__index.set(s32);
    }

    get isTextSupportMarquee() {
        return this.__isTextSupportMarquee.get();
    }

    set isTextSupportMarquee(r32) {
        this.__isTextSupportMarquee.set(r32);
    }

    get isMarqueeAndFadeout() {
        return this.__isMarqueeAndFadeout.get();
    }

    set isMarqueeAndFadeout(q32) {
        this.__isMarqueeAndFadeout.set(q32);
    }

    get isSegmentFocusStyleCustomized() {
        return this.__isSegmentFocusStyleCustomized.get();
    }

    set isSegmentFocusStyleCustomized(p32) {
        this.__isSegmentFocusStyleCustomized.set(p32);
    }

    get isTextInMarqueeCondition() {
        return this.__isTextInMarqueeCondition.get();
    }

    set isTextInMarqueeCondition(o32) {
        this.__isTextInMarqueeCondition.set(o32);
    }

    get isButtonTextFadeout() {
        return this.__isButtonTextFadeout.get();
    }

    set isButtonTextFadeout(n32) {
        this.__isButtonTextFadeout.set(n32);
    }

    get hover() {
        return this.__hover.get();
    }

    set hover(m32) {
        this.__hover.set(m32);
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
                top: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING),
                bottom: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING),
                start: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING),
                end: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING)
            };
        }
        return {
            top: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_VERTICAL_PADDING),
            bottom: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_VERTICAL_PADDING),
            start: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING),
            end: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING)
        };
    }

    onFocusIndex() {
        this.isTextInMarqueeCondition =
            this.isSegmentFocusStyleCustomized && (this.focusIndex === this.index || this.hover);
    }

    aboutToAppear() {
        this.isButtonTextFadeout = this.isSegmentFocusStyleCustomized;
    }

    isDefaultSelectedFontColor() {
        if (this.options.type === 'tab') {
            return this.options.selectedFontColor === segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        } else if (this.options.type === 'capsule') {
            return this.options.selectedFontColor === segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
        }
        return false;
    }

    getFontColor() {
        if (this.property.isSelected) {
            if (this.isDefaultSelectedFontColor() && this.isSegmentFocusStyleCustomized &&
                this.focusIndex === this.index) {
                return segmentButtonTheme.SEGMENT_BUTTON_FOCUS_TEXT_COLOR;
            }
            return this.options.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
        } else {
            if (this.options.fontColor === segmentButtonTheme.FONT_COLOR && this.isSegmentFocusStyleCustomized &&
                this.focusIndex === this.index) {
                return segmentButtonTheme.SEGMENT_BUTTON_FOCUS_TEXT_COLOR;
            }
            return this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
        }
    }

    getAccessibilityText() {
        if (this.selectedIndexes.includes(this.index) &&
            typeof this.itemOptions.selectedIconAccessibilityText !== undefined) {
            return this.itemOptions.selectedIconAccessibilityText;
        } else if (!this.selectedIndexes.includes(this.index) &&
            typeof this.itemOptions.iconAccessibilityText !== undefined) {
            return this.itemOptions.iconAccessibilityText;
        }
        return undefined;
    }

    initialRender() {
        this.observeComponentCreation2((k32, l32) => {
            Column.create({ space: 2 });
            Column.direction(this.options.direction);
            Column.focusScopePriority(this.groupId,
                Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.getButtonPadding());
            Column.constraintSize({ minHeight: segmentButtonTheme.CONSTRAINT_SIZE_MIN_HEIGHT });
        }, Column);
        this.observeComponentCreation2((d32, e32) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i32, j32) => {
                        Image.create(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon);
                        Image.direction(this.options.direction);
                        Image.size(this.options.imageSize ?? { width: 24, height: 24 });
                        Image.draggable(false);
                        Image.fillColor(this.getFontColor());
                        Image.accessibilityText(this.getAccessibilityText());
                    }, Image);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((w31, x31) => {
            If.create();
            if (this.options.showText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b32, c32) => {
                        Text.create(this.itemOptions.text);
                        Text.direction(this.options.direction);
                        Text.fontColor(this.getFontColor());
                        Text.fontWeight(this.property.fontWeight);
                        Text.fontSize(this.property.fontSize);
                        Text.minFontSize(9);
                        Text.maxFontSize(this.property.fontSize);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.maxFontScale));
                        Text.textOverflow({
                            overflow: this.isTextSupportMarquee ? TextOverflow.MARQUEE : TextOverflow.Ellipsis
                        });
                        Text.marqueeOptions({
                            start: this.isTextInMarqueeCondition,
                            fadeout: this.isButtonTextFadeout,
                            marqueeStartPolicy: MarqueeStartPolicy.DEFAULT
                        });
                        Text.maxLines(1);
                        Text.textAlign(TextAlign.Center);
                        Text.padding(this.getTextPadding());
                    }, Text);
                    Text.pop();
                });
            } else {
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
    constructor(n31, o31, p31, q31 = -1, r31 = undefined, s31) {
        super(n31, p31, q31, s31);
        if (typeof r31 === "function") {
            this.paramsGenerator_ = r31;
        }
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(o31.press, this, "press");
        this.__hover = new SynchedPropertySimpleOneWayPU(o31.hover, this, "hover");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(o31.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__options = new SynchedPropertyNesedObjectPU(o31.options, this, "options");
        this.pressIndex = 0;
        this.pressColor = segmentButtonTheme.PRESS_COLOR;
        this.setInitiallyProvidedValue(o31);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(m31) {
        this.__colorProperty.set(m31.colorProperty);
        this.__options.set(m31.options);
        if (m31.pressIndex !== undefined) {
            this.pressIndex = m31.pressIndex;
        }
        if (m31.pressColor !== undefined) {
            this.pressColor = m31.pressColor;
        }
    }

    updateStateVars(l31) {
        this.__press.reset(l31.press);
        this.__hover.reset(l31.hover);
        this.__colorProperty.set(l31.colorProperty);
        this.__options.set(l31.options);
    }

    purgeVariableDependenciesOnElmtId(k31) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(k31);
        this.__press.purgeDependencyOnElmtId(k31);
        this.__hover.purgeDependencyOnElmtId(k31);
        this.__colorProperty.purgeDependencyOnElmtId(k31);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(k31);
        this.__options.purgeDependencyOnElmtId(k31);
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

    set buttonItemsSize(j31) {
        this.__buttonItemsSize.set(j31);
    }

    get press() {
        return this.__press.get();
    }

    set press(i31) {
        this.__press.set(i31);
    }

    get hover() {
        return this.__hover.get();
    }

    set hover(h31) {
        this.__hover.set(h31);
    }

    get colorProperty() {
        return this.__colorProperty.get();
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(g31) {
        this.__buttonBorderRadius.set(g31);
    }

    get options() {
        return this.__options.get();
    }

    initialRender() {
        this.observeComponentCreation2((e31, f31) => {
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

class PressAndHoverEffectArray extends ViewPU {
    constructor(x30, y30, z30, a31 = -1, b31 = undefined, c31) {
        super(x30, z30, a31, c31);
        if (typeof b31 === "function") {
            this.paramsGenerator_ = b31;
        }
        this.__buttons = new SynchedPropertyNesedObjectPU(y30.buttons, this, "buttons");
        this.__options = new SynchedPropertyNesedObjectPU(y30.options, this, "options");
        this.__pressArray = new SynchedPropertyObjectTwoWayPU(y30.pressArray, this, "pressArray");
        this.__hoverArray = new SynchedPropertyObjectTwoWayPU(y30.hoverArray, this, "hoverArray");
        this.__hoverColorArray = new SynchedPropertyObjectTwoWayPU(y30.hoverColorArray, this, "hoverColorArray");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.setInitiallyProvidedValue(y30);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(w30) {
        this.__buttons.set(w30.buttons);
        this.__options.set(w30.options);
    }

    updateStateVars(v30) {
        this.__buttons.set(v30.buttons);
        this.__options.set(v30.options);
    }

    purgeVariableDependenciesOnElmtId(u30) {
        this.__buttons.purgeDependencyOnElmtId(u30);
        this.__options.purgeDependencyOnElmtId(u30);
        this.__pressArray.purgeDependencyOnElmtId(u30);
        this.__hoverArray.purgeDependencyOnElmtId(u30);
        this.__hoverColorArray.purgeDependencyOnElmtId(u30);
        this.__zoomScaleArray.purgeDependencyOnElmtId(u30);
    }

    aboutToBeDeleted() {
        this.__buttons.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__pressArray.aboutToBeDeleted();
        this.__hoverArray.aboutToBeDeleted();
        this.__hoverColorArray.aboutToBeDeleted();
        this.__zoomScaleArray.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get buttons() {
        return this.__buttons.get();
    }

    get options() {
        return this.__options.get();
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(t30) {
        this.__pressArray.set(t30);
    }

    get hoverArray() {
        return this.__hoverArray.get();
    }

    set hoverArray(s30) {
        this.__hoverArray.set(s30);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(r30) {
        this.__hoverColorArray.set(r30);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(q30) {
        this.__zoomScaleArray.set(q30);
    }

    initialRender() {
        this.observeComponentCreation2((o30, p30) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
        }, Row);
        this.observeComponentCreation2((s29, t29) => {
            ForEach.create();
            const u29 = (w29, x29) => {
                const y29 = w29;
                this.observeComponentCreation2((a30, b30) => {
                    If.create();
                    if (x29 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((m30, n30) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.scale({
                                    x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 :
                                    this.zoomScaleArray[x29],
                                    y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 :
                                    this.zoomScaleArray[x29]
                                });
                            }, Stack);
                            {
                                this.observeComponentCreation2((g30, h30) => {
                                    if (h30) {
                                        let i30 = new PressAndHoverEffect(this, {
                                            pressIndex: x29,
                                            colorProperty: this.hoverColorArray[x29],
                                            press: this.pressArray[x29],
                                            hover: this.hoverArray[x29],
                                            options: this.options,
                                        }, undefined, g30, () => {
                                        }, {
                                            page: "library/src/main/ets/components/segmentbutton.ets",
                                            line: 684,
                                            col: 13
                                        });
                                        ViewPU.create(i30);
                                        let j30 = () => {
                                            return {
                                                pressIndex: x29,
                                                colorProperty: this.hoverColorArray[x29],
                                                press: this.pressArray[x29],
                                                hover: this.hoverArray[x29],
                                                options: this.options
                                            };
                                        };
                                        i30.paramsGenerator_ = j30;
                                    } else {
                                        this.updateStateVarsOfChildByElmtId(g30, {
                                            colorProperty: this.hoverColorArray[x29],
                                            press: this.pressArray[x29],
                                            hover: this.hoverArray[x29],
                                            options: this.options
                                        });
                                    }
                                }, { name: "PressAndHoverEffect" });
                            }
                            Stack.pop();
                        });
                    } else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(s29, this.buttons, u29, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SegmentButtonItemArrayComponent extends ViewPU {
    constructor(b29, c29, d29, e29 = -1, f29 = undefined, g29) {
        super(b29, d29, e29, g29);
        if (typeof f29 === "function") {
            this.paramsGenerator_ = f29;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(c29.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(c29.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(c29.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = this.initializeConsume("componentSize", "componentSize");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__buttonItemsPosition = this.initializeConsume("buttonItemsPosition", "buttonItemsPosition");
        this.__focusIndex = this.initializeConsume("focusIndex", "focusIndex");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonItemProperty = this.initializeConsume("buttonItemProperty", "buttonItemProperty");
        this.__buttonItemsSelected = this.initializeConsume("buttonItemsSelected", "buttonItemsSelected");
        this.__pressArray = new SynchedPropertyObjectTwoWayPU(c29.pressArray, this, "pressArray");
        this.__hoverArray = new SynchedPropertyObjectTwoWayPU(c29.hoverArray, this, "hoverArray");
        this.__hoverColorArray = new SynchedPropertyObjectTwoWayPU(c29.hoverColorArray, this, "hoverColorArray");
        this.__maxFontScale = new SynchedPropertyObjectOneWayPU(c29.maxFontScale, this, "maxFontScale");
        this.__buttonWidth =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (o29, p29) => 0), this, "buttonWidth");
        this.__buttonHeight =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (m29, n29) => 0), this, "buttonHeight");
        this.__isMarqueeAndFadeout = new ObservedPropertySimplePU(false, this, "isMarqueeAndFadeout");
        this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (k29, l29) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.onItemClicked = undefined;
        this.__isSegmentFocusStyleCustomized =
            new SynchedPropertySimpleOneWayPU(c29.isSegmentFocusStyleCustomized, this, "isSegmentFocusStyleCustomized");
        this.setInitiallyProvidedValue(c29);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange);
        this.declareWatch("focusIndex", this.onFocusIndex);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(a29) {
        this.__optionsArray.set(a29.optionsArray);
        this.__options.set(a29.options);
        if (a29.buttonWidth !== undefined) {
            this.buttonWidth = a29.buttonWidth;
        }
        if (a29.buttonHeight !== undefined) {
            this.buttonHeight = a29.buttonHeight;
        }
        if (a29.isMarqueeAndFadeout !== undefined) {
            this.isMarqueeAndFadeout = a29.isMarqueeAndFadeout;
        }
        if (a29.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = a29.buttonItemsRealHeight;
        }
        if (a29.groupId !== undefined) {
            this.groupId = a29.groupId;
        }
        if (a29.onItemClicked !== undefined) {
            this.onItemClicked = a29.onItemClicked;
        }
    }

    updateStateVars(z28) {
        this.__optionsArray.set(z28.optionsArray);
        this.__options.set(z28.options);
        this.__maxFontScale.reset(z28.maxFontScale);
        this.__isSegmentFocusStyleCustomized.reset(z28.isSegmentFocusStyleCustomized);
    }

    purgeVariableDependenciesOnElmtId(y28) {
        this.__optionsArray.purgeDependencyOnElmtId(y28);
        this.__options.purgeDependencyOnElmtId(y28);
        this.__selectedIndexes.purgeDependencyOnElmtId(y28);
        this.__componentSize.purgeDependencyOnElmtId(y28);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(y28);
        this.__buttonItemsSize.purgeDependencyOnElmtId(y28);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(y28);
        this.__focusIndex.purgeDependencyOnElmtId(y28);
        this.__zoomScaleArray.purgeDependencyOnElmtId(y28);
        this.__buttonItemProperty.purgeDependencyOnElmtId(y28);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(y28);
        this.__pressArray.purgeDependencyOnElmtId(y28);
        this.__hoverArray.purgeDependencyOnElmtId(y28);
        this.__hoverColorArray.purgeDependencyOnElmtId(y28);
        this.__maxFontScale.purgeDependencyOnElmtId(y28);
        this.__buttonWidth.purgeDependencyOnElmtId(y28);
        this.__buttonHeight.purgeDependencyOnElmtId(y28);
        this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(y28);
        this.__isSegmentFocusStyleCustomized.purgeDependencyOnElmtId(y28);
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
        this.__maxFontScale.aboutToBeDeleted();
        this.__buttonWidth.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__isMarqueeAndFadeout.aboutToBeDeleted();
        this.__isSegmentFocusStyleCustomized.aboutToBeDeleted();
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

    set selectedIndexes(x28) {
        this.__selectedIndexes.set(x28);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(w28) {
        this.__componentSize.set(w28);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(v28) {
        this.__buttonBorderRadius.set(v28);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(u28) {
        this.__buttonItemsSize.set(u28);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(t28) {
        this.__buttonItemsPosition.set(t28);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(s28) {
        this.__focusIndex.set(s28);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(r28) {
        this.__zoomScaleArray.set(r28);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(q28) {
        this.__buttonItemProperty.set(q28);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(p28) {
        this.__buttonItemsSelected.set(p28);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(o28) {
        this.__pressArray.set(o28);
    }

    get hoverArray() {
        return this.__hoverArray.get();
    }

    set hoverArray(n28) {
        this.__hoverArray.set(n28);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(m28) {
        this.__hoverColorArray.set(m28);
    }

    get maxFontScale() {
        return this.__maxFontScale.get();
    }

    set maxFontScale(l28) {
        this.__maxFontScale.set(l28);
    }

    get buttonWidth() {
        return this.__buttonWidth.get();
    }

    set buttonWidth(k28) {
        this.__buttonWidth.set(k28);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(j28) {
        this.__buttonHeight.set(j28);
    }

    get isMarqueeAndFadeout() {
        return this.__isMarqueeAndFadeout.get();
    }

    set isMarqueeAndFadeout(i28) {
        this.__isMarqueeAndFadeout.set(i28);
    }

    get isSegmentFocusStyleCustomized() {
        return this.__isSegmentFocusStyleCustomized.get();
    }

    set isSegmentFocusStyleCustomized(h28) {
        this.__isSegmentFocusStyleCustomized.set(h28);
    }

    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((f28, g28) => {
            this.buttonWidth[g28] = f28.width;
            this.buttonHeight[g28] = f28.height;
        });
    }

    changeSelectedIndexes(t27) {
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
                } else if (this.options.type === 'capsule') {
                    this.selectedIndexes = [];
                }
            } else {
                this.selectedIndexes[0] =
                    this.selectedIndexes[0] - this.optionsArray.deleteCount + this.optionsArray.addLength;
            }
        } else {
            let u27 = this.selectedIndexes;
            for (let z27 = 0; z27 < this.optionsArray.deleteCount; z27++) {
                let a28 = u27.indexOf(this.optionsArray.changeStartIndex);
                let b28 = u27.map(d28 => this.optionsArray.changeStartIndex &&
                    (d28 > this.optionsArray.changeStartIndex) ? d28 - 1 : d28);
                if (a28 !== -1) {
                    b28.splice(a28, 1);
                }
                u27 = b28;
            }
            for (let v27 = 0; v27 < this.optionsArray.addLength; v27++) {
                let w27 = u27.map(y27 => this.optionsArray.changeStartIndex &&
                    (y27 >= this.optionsArray.changeStartIndex) ? y27 + 1 : y27);
                u27 = w27;
            }
            this.selectedIndexes = u27;
        }
    }

    changeFocusIndex(s27) {
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
        } else {
            this.focusIndex = this.focusIndex - this.optionsArray.deleteCount + this.optionsArray.addLength;
        }
    }

    onOptionsArrayChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        let r27 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 &&
            this.optionsArray.addLength !== void 0) {
            this.changeSelectedIndexes(r27);
            this.changeFocusIndex(r27);
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
        this.isMarqueeAndFadeout = this.isSegmentFocusStyleCustomized && !this.isMarqueeAndFadeout;
    }

    aboutToAppear() {
        for (let q27 = 0; q27 < this.buttonItemsRealHeight.length; q27++) {
            this.buttonItemsRealHeight[q27] = 0;
        }
    }

    getBorderRadius(o27) {
        let p27 = this.buttonBorderRadius[o27];
        if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex]) {
            return {
                topStart: LengthMetrics.vp((p27.topStart?.value ?? 0) + 4),
                topEnd: LengthMetrics.vp((p27.topEnd?.value ?? 0) + 4),
                bottomStart: LengthMetrics.vp((p27.bottomStart?.value ?? 0) + 4),
                bottomEnd: LengthMetrics.vp((p27.bottomEnd?.value ?? 0) + 4)
            };
        }
        return p27;
    }

    focusStack(g27, h27 = null) {
        this.observeComponentCreation2((m27, n27) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((k27, l27) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.borderRadius(this.getBorderRadius(g27));
            Stack.size({
                width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ?
                    this.buttonWidth[g27] + 8 : this.buttonWidth[g27],
                height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ?
                    this.buttonHeight[g27] + 8 : this.buttonHeight[g27]
            });
            Stack.borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR);
            Stack.borderWidth(2);
        }, Stack);
        Stack.pop();
        Stack.pop();
    }

    calculateBorderRadius() {
        let a27 = Array.from({
            length: MAX_ITEM_COUNT
        }, (e27, f27) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        });
        for (let c27 = 0; c27 < this.buttonBorderRadius.length; c27++) {
            let d27 = this.buttonItemsSize[c27].height / 2;
            if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                a27[c27].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? d27);
                a27[c27].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? d27);
                a27[c27].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? d27);
                a27[c27].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? d27);
            } else {
                if (c27 === 0) {
                    a27[c27].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? d27);
                    a27[c27].topEnd = LengthMetrics.vp(0);
                    a27[c27].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? d27);
                    a27[c27].bottomEnd = LengthMetrics.vp(0);
                } else if (this.options.buttons &&
                    c27 === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    a27[c27].topStart = LengthMetrics.vp(0);
                    a27[c27].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? d27);
                    a27[c27].bottomStart = LengthMetrics.vp(0);
                    a27[c27].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? d27);
                } else {
                    a27[c27].topStart = LengthMetrics.vp(0);
                    a27[c27].topEnd = LengthMetrics.vp(0);
                    a27[c27].bottomStart = LengthMetrics.vp(0);
                    a27[c27].bottomEnd = LengthMetrics.vp(0);
                }
            }
        }
        this.buttonBorderRadius = a27;
    }

    getAccessibilityDescription(z26) {
        return (typeof z26 !== undefined) ? z26 : undefined;
    }

    isDefaultSelectedBgColor() {
        if (this.options.type === 'tab') {
            return this.options.selectedBackgroundColor === segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        } else if (this.options.type === 'capsule') {
            return this.options.selectedBackgroundColor === segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
        return true;
    }

    initialRender() {
        this.observeComponentCreation2((q24, r24) => {
            If.create();
            if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u26, v26) => {
                        Row.create({ space: 1 });
                        Row.direction(this.options.direction);
                        Row.focusScopeId(this.groupId, true);
                        Row.padding(this.options.componentPadding);
                        Row.onSizeChange((x26, y26) => {
                            this.componentSize = { width: y26.width, height: y26.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((w24, x24) => {
                        ForEach.create();
                        const y24 = (a25, b25) => {
                            const c25 = a25;
                            this.observeComponentCreation2((e25, f25) => {
                                If.create();
                                if (b25 < MAX_ITEM_COUNT) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((y25, z25) => {
                                            Button.createWithChild();
                                            Button.type(ButtonType.Normal);
                                            Button.stateEffect(false);
                                            Button.hoverEffect(HoverEffect.None);
                                            Button.backgroundColor(Color.Transparent);
                                            Button.accessibilityLevel(c25.accessibilityLevel);
                                            Button.accessibilitySelected(this.options.multiply ? undefined :
                                            this.selectedIndexes.includes(z25));
                                            Button.accessibilityChecked(this.options.multiply ?
                                            this.selectedIndexes.includes(z25) : undefined);
                                            Button.accessibilityDescription(this.getAccessibilityDescription(c25.accessibilityDescription));
                                            Button.direction(this.options.direction);
                                            Button.borderRadius(this.buttonBorderRadius[b25]);
                                            Button.scale({
                                                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ?
                                                    1 : this.zoomScaleArray[b25],
                                                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ?
                                                    1 : this.zoomScaleArray[b25]
                                            });
                                            Button.layoutWeight(1);
                                            Button.padding(0);
                                            Button.onSizeChange((s26, t26) => {
                                                this.buttonItemsSize[b25] =
                                                    { width: t26.width, height: this.buttonItemsSize[b25].height };
                                                if (t26.width) {
                                                    this.buttonItemsPosition[b25] = {
                                                        start: LengthMetrics.vp(Number.parseFloat(this.options.componentPadding.toString()) +
                                                            (Number.parseFloat(t26.width.toString()) + 1) * b25),
                                                        top: LengthMetrics.px(Math.floor(this.getUIContext()
                                                            .vp2px(Number.parseFloat(this.options.componentPadding.toString()))))
                                                    };
                                                }
                                            });
                                            ViewStackProcessor.visualState("normal");
                                            Button.overlay(undefined);
                                            ViewStackProcessor.visualState("focused");
                                            Button.overlay({
                                                builder: () => {
                                                    this.focusStack.call(this, b25);
                                                }
                                            }, {
                                                align: Alignment.Center
                                            });
                                            ViewStackProcessor.visualState();
                                            Button.onFocus(() => {
                                                this.focusIndex = b25;
                                                if (this.isSegmentFocusStyleCustomized) {
                                                    this.customizeSegmentFocusStyle(b25);
                                                }
                                            });
                                            Button.onBlur(() => {
                                                this.focusIndex = -1;
                                                this.hoverColorArray[b25].hoverColor = Color.Transparent;
                                            });
                                            Gesture.create(GesturePriority.Low);
                                            TapGesture.create();
                                            TapGesture.onAction(() => {
                                                if (this.onItemClicked) {
                                                    this.onItemClicked(b25);
                                                }
                                                if (this.options.type === 'capsule' &&
                                                    (this.options.multiply ?? false)) {
                                                    if (this.selectedIndexes.indexOf(b25) === -1) {
                                                        this.selectedIndexes.push(b25);
                                                    } else {
                                                        this.selectedIndexes.splice(this.selectedIndexes.indexOf(b25),
                                                            1);
                                                    }
                                                } else {
                                                    this.selectedIndexes[0] = b25;
                                                }
                                            });
                                            TapGesture.pop();
                                            Gesture.pop();
                                            Button.onTouch((p26) => {
                                                if (this.isSegmentFocusStyleCustomized) {
                                                    this.getUIContext().getFocusController().clearFocus();
                                                }
                                                if (p26.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (p26.type === TouchType.Down) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[b25] = 0.95;
                                                    });
                                                } else if (p26.type === TouchType.Up || p26.type === TouchType.Cancel) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[b25] = 1;
                                                    });
                                                }
                                            });
                                            Button.onHover((m26) => {
                                                this.hoverArray[b25] = m26;
                                                if (m26) {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[b25].hoverColor =
                                                            this.isSegmentFocusStyleCustomized &&
                                                                this.focusIndex === b25 ?
                                                            segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR :
                                                            segmentButtonTheme.HOVER_COLOR;
                                                    });
                                                } else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[b25].hoverColor =
                                                            this.isSegmentFocusStyleCustomized &&
                                                                this.focusIndex === b25 ?
                                                            segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR :
                                                            Color.Transparent;
                                                    });
                                                }
                                            });
                                            Button.onMouse((h26) => {
                                                switch (h26.action) {
                                                    case MouseAction.Press:
                                                        Context.animateTo({ curve: curves.springMotion(0.347, 0.99) },
                                                            () => {
                                                                this.zoomScaleArray[b25] = 0.95;
                                                            });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[b25] = true;
                                                        });
                                                        break;
                                                    case MouseAction.Release:
                                                        Context.animateTo({ curve: curves.springMotion(0.347, 0.99) },
                                                            () => {
                                                                this.zoomScaleArray[b25] = 1;
                                                            });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[b25] = false;
                                                        });
                                                        break;
                                                }
                                            });
                                        }, Button);
                                        this.observeComponentCreation2((r25, s25) => {
                                            __Common__.create();
                                            __Common__.onSizeChange((u25, v25) => {
                                                this.buttonItemsRealHeight[b25] = v25.height;
                                                let w25 = Math.max(...this.buttonItemsRealHeight.slice(0,
                                                    this.options.buttons ?
                                                    this.options.buttons.length : 0));
                                                for (let x25 = 0; x25 < this.buttonItemsSize.length; x25++) {
                                                    this.buttonItemsSize[x25] =
                                                        { width: this.buttonItemsSize[x25].width, height: w25 };
                                                }
                                                this.calculateBorderRadius();
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((l25, m25) => {
                                                if (m25) {
                                                    let n25 = new SegmentButtonItem(this, {
                                                        isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                                                        isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                                                        selectedIndexes: this.__selectedIndexes,
                                                        focusIndex: this.__focusIndex,
                                                        index: b25,
                                                        itemOptions: c25,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[b25],
                                                        groupId: this.groupId,
                                                        maxFontScale: this.maxFontScale,
                                                        hover: this.hoverArray[b25],
                                                    }, undefined, l25, () => {
                                                    }, {
                                                        page: "library/src/main/ets/components/segmentbutton.ets",
                                                        line: 921,
                                                        col: 15
                                                    });
                                                    ViewPU.create(n25);
                                                    let o25 = () => {
                                                        return {
                                                            isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                                                            isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                                                            selectedIndexes: this.selectedIndexes,
                                                            focusIndex: this.focusIndex,
                                                            index: b25,
                                                            itemOptions: c25,
                                                            options: this.options,
                                                            property: this.buttonItemProperty[b25],
                                                            groupId: this.groupId,
                                                            maxFontScale: this.maxFontScale,
                                                            hover: this.hoverArray[b25]
                                                        };
                                                    };
                                                    n25.paramsGenerator_ = o25;
                                                } else {
                                                    this.updateStateVarsOfChildByElmtId(l25, {
                                                        isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                                                        isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                                                        index: b25,
                                                        itemOptions: c25,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[b25],
                                                        maxFontScale: this.maxFontScale,
                                                        hover: this.hoverArray[b25]
                                                    });
                                                }
                                            }, { name: "SegmentButtonItem" });
                                        }
                                        __Common__.pop();
                                        Button.pop();
                                    });
                                } else {
                                    this.ifElseBranchUpdateFunction(1, () => {
                                    });
                                }
                            }, If);
                            If.pop();
                        };
                        this.forEachUpdateFunction(w24, this.optionsArray, y24, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                    Row.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    customizeSegmentFocusStyle(o24) {
        if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0 &&
            this.selectedIndexes[0] === o24) {
            this.hoverColorArray[o24].hoverColor = this.isDefaultSelectedBgColor() ?
            segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : this.options.selectedBackgroundColor;
        } else {
            this.hoverColorArray[o24].hoverColor =
                this.options.backgroundColor === segmentButtonTheme.BACKGROUND_COLOR ?
                segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : this.options.backgroundColor;
        }
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
    constructor(h23, i23, j23, k23 = -1, l23 = undefined, m23) {
        super(h23, j23, k23, m23);
        if (typeof l23 === "function") {
            this.paramsGenerator_ = l23;
        }
        this.__options = new SynchedPropertyNesedObjectPU(i23.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(i23.selectedIndexes, this, "selectedIndexes");
        this.onItemClicked = undefined;
        this.__maxFontScale = new SynchedPropertyObjectOneWayPU(i23.maxFontScale, this, "maxFontScale");
        this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, "componentSize");
        this.addProvidedVar("componentSize", this.__componentSize, false);
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (m24, n24) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        }), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.__buttonBorderRadius, false);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (k24, l24) => {
            return {};
        }), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.__buttonItemsSize, false);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (i24, j24) => {
            return {};
        }), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.__buttonItemsPosition, false);
        this.__buttonItemsSelected =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (g24, h24) => false), this,
                "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected, false);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (e24, f24) => new ItemProperty()), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty, false);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex, false);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition, false);
        this.__zoomScaleArray =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (c24, d24) => 1.0), this,
                "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.__zoomScaleArray, false);
        this.__pressArray =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (a24, b24) => false), this,
                "pressArray");
        this.__hoverArray =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (y23, z23) => false), this,
                "hoverArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (w23, x23) => new HoverColorProperty()), this, "hoverColorArray");
        this.doSelectedChangeAnimate = false;
        this.isCurrentPositionSelected = false;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = false;
        this.__shouldMirror = new ObservedPropertySimplePU(false, this, "shouldMirror");
        this.isSegmentFocusStyleCustomized = segmentButtonTheme.SEGMENT_FOCUS_STYLE_CUSTOMIZED;
        this.setInitiallyProvidedValue(i23);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.declareWatch("buttonItemsPosition", this.onItemsPositionChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(g23) {
        this.__options.set(g23.options);
        if (g23.onItemClicked !== undefined) {
            this.onItemClicked = g23.onItemClicked;
        }
        if (g23.maxFontScale === undefined) {
            this.__maxFontScale.set(DEFAULT_MAX_FONT_SCALE);
        }
        if (g23.componentSize !== undefined) {
            this.componentSize = g23.componentSize;
        }
        if (g23.buttonBorderRadius !== undefined) {
            this.buttonBorderRadius = g23.buttonBorderRadius;
        }
        if (g23.buttonItemsSize !== undefined) {
            this.buttonItemsSize = g23.buttonItemsSize;
        }
        if (g23.buttonItemsPosition !== undefined) {
            this.buttonItemsPosition = g23.buttonItemsPosition;
        }
        if (g23.buttonItemsSelected !== undefined) {
            this.buttonItemsSelected = g23.buttonItemsSelected;
        }
        if (g23.buttonItemProperty !== undefined) {
            this.buttonItemProperty = g23.buttonItemProperty;
        }
        if (g23.focusIndex !== undefined) {
            this.focusIndex = g23.focusIndex;
        }
        if (g23.selectedItemPosition !== undefined) {
            this.selectedItemPosition = g23.selectedItemPosition;
        }
        if (g23.zoomScaleArray !== undefined) {
            this.zoomScaleArray = g23.zoomScaleArray;
        }
        if (g23.pressArray !== undefined) {
            this.pressArray = g23.pressArray;
        }
        if (g23.hoverArray !== undefined) {
            this.hoverArray = g23.hoverArray;
        }
        if (g23.hoverColorArray !== undefined) {
            this.hoverColorArray = g23.hoverColorArray;
        }
        if (g23.doSelectedChangeAnimate !== undefined) {
            this.doSelectedChangeAnimate = g23.doSelectedChangeAnimate;
        }
        if (g23.isCurrentPositionSelected !== undefined) {
            this.isCurrentPositionSelected = g23.isCurrentPositionSelected;
        }
        if (g23.panGestureStartPoint !== undefined) {
            this.panGestureStartPoint = g23.panGestureStartPoint;
        }
        if (g23.isPanGestureMoved !== undefined) {
            this.isPanGestureMoved = g23.isPanGestureMoved;
        }
        if (g23.shouldMirror !== undefined) {
            this.shouldMirror = g23.shouldMirror;
        }
        if (g23.isSegmentFocusStyleCustomized !== undefined) {
            this.isSegmentFocusStyleCustomized = g23.isSegmentFocusStyleCustomized;
        }
    }

    updateStateVars(f23) {
        this.__options.set(f23.options);
        this.__maxFontScale.reset(f23.maxFontScale);
    }

    purgeVariableDependenciesOnElmtId(e23) {
        this.__options.purgeDependencyOnElmtId(e23);
        this.__selectedIndexes.purgeDependencyOnElmtId(e23);
        this.__maxFontScale.purgeDependencyOnElmtId(e23);
        this.__componentSize.purgeDependencyOnElmtId(e23);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(e23);
        this.__buttonItemsSize.purgeDependencyOnElmtId(e23);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(e23);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(e23);
        this.__buttonItemProperty.purgeDependencyOnElmtId(e23);
        this.__focusIndex.purgeDependencyOnElmtId(e23);
        this.__selectedItemPosition.purgeDependencyOnElmtId(e23);
        this.__zoomScaleArray.purgeDependencyOnElmtId(e23);
        this.__pressArray.purgeDependencyOnElmtId(e23);
        this.__hoverArray.purgeDependencyOnElmtId(e23);
        this.__hoverColorArray.purgeDependencyOnElmtId(e23);
        this.__shouldMirror.purgeDependencyOnElmtId(e23);
    }

    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__maxFontScale.aboutToBeDeleted();
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

    set selectedIndexes(d23) {
        this.__selectedIndexes.set(d23);
    }

    get maxFontScale() {
        return this.__maxFontScale.get();
    }

    set maxFontScale(c23) {
        this.__maxFontScale.set(c23);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(b23) {
        this.__componentSize.set(b23);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(a23) {
        this.__buttonBorderRadius.set(a23);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(z22) {
        this.__buttonItemsSize.set(z22);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(y22) {
        this.__buttonItemsPosition.set(y22);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(x22) {
        this.__buttonItemsSelected.set(x22);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(w22) {
        this.__buttonItemProperty.set(w22);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(v22) {
        this.__focusIndex.set(v22);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(u22) {
        this.__selectedItemPosition.set(u22);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(t22) {
        this.__zoomScaleArray.set(t22);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(s22) {
        this.__pressArray.set(s22);
    }

    get hoverArray() {
        return this.__hoverArray.get();
    }

    set hoverArray(r22) {
        this.__hoverArray.set(r22);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(q22) {
        this.__hoverColorArray.set(q22);
    }

    get shouldMirror() {
        return this.__shouldMirror.get();
    }

    set shouldMirror(p22) {
        this.__shouldMirror.set(p22);
    }

    onItemsPositionChange() {
        if (this.options === void 0 || this.options.buttons === void 0) {
            return;
        }
        if (this.options.type === 'capsule') {
            this.options.onButtonsUpdated();
        }
        if (this.doSelectedChangeAnimate) {
            this.updateAnimatedProperty(this.getSelectedChangeCurve());
        } else {
            this.updateAnimatedProperty(null);
        }
    }

    setItemsSelected() {
        this.buttonItemsSelected.forEach((n22, o22) => {
            this.buttonItemsSelected[o22] = false;
        });
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            this.selectedIndexes.forEach(m22 => this.buttonItemsSelected[m22] = true);
        } else {
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
        let h22 = this.selectedIndexes.some(j22 => {
            return (j22 === void 0 || j22 < 0 || (this.options.buttons && j22 >= this.options.buttons.length));
        });
        if (h22) {
            if (this.options.type === 'tab') {
                this.selectedIndexes = [0];
            } else {
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
        } else {
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
            } else {
                this.selectedIndexes = [];
            }
        };
        this.shouldMirror = this.isShouldMirror();
        this.updateSelectedIndexes();
        this.setItemsSelected();
        this.updateAnimatedProperty(null);
    }

    isMouseWheelScroll(f22) {
        return f22.source === SourceType.Mouse && !this.isPanGestureMoved;
    }

    isMovedFromPanGestureStartPoint(d22, e22) {
        return !nearEqual(d22, this.panGestureStartPoint.x) || !nearEqual(e22, this.panGestureStartPoint.y);
    }

    isShouldMirror() {
        if (this.options.direction == Direction.Rtl) {
            return true;
        }
        try {
            let c22 = I18n.System.getSystemLanguage();
            if (c22 === 'ug' && this.options.direction != Direction.Ltr) {
                return true;
            }
        } catch (b22) {
            console.error(`Ace SegmentButton getSystemLanguage, error: ${b22.toString()}`);
        }
        return false;
    }

    initialRender() {
        this.observeComponentCreation2((q20, r20) => {
            Stack.create();
            Stack.direction(this.options ? this.options.direction : undefined);
            Stack.onBlur(() => {
                this.focusIndex = -1;
            });
            Stack.onKeyEvent((a22) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (a22.type === KeyType.Down) {
                    if (a22.keyCode === KeyCode.KEYCODE_SPACE || a22.keyCode === KeyCode.KEYCODE_ENTER ||
                        a22.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            if (this.selectedIndexes.indexOf(this.focusIndex) === -1) {
                                this.selectedIndexes.push(this.focusIndex);
                            } else {
                                this.selectedIndexes.splice(this.selectedIndexes.indexOf(this.focusIndex), 1);
                            }
                        } else {
                            this.selectedIndexes[0] = this.focusIndex;
                        }
                    }
                }
            });
            Stack.accessibilityLevel('no');
            Gesture.create(GesturePriority.High);
            GestureGroup.create(GestureMode.Parallel);
            TapGesture.create();
            TapGesture.onAction((t21) => {
                let u21 = t21.fingerList.find(Boolean);
                if (u21 === void 0) {
                    return;
                }
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                let v21 = u21.localX;
                let w21 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
                for (let x21 = 0; x21 < w21; x21++) {
                    v21 = v21 - this.buttonItemsSize[x21].width;
                    if (v21 >= 0) {
                        continue;
                    }
                    this.doSelectedChangeAnimate =
                        this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ?
                            false : true;
                    let y21 = this.isShouldMirror() ? w21 - 1 - x21 : x21;
                    if (this.onItemClicked) {
                        this.onItemClicked(y21);
                    }
                    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                        let z21 = this.selectedIndexes.indexOf(y21);
                        if (z21 === -1) {
                            this.selectedIndexes.push(y21);
                        } else {
                            this.selectedIndexes.splice(z21, 1);
                        }
                    } else {
                        this.selectedIndexes[0] = y21;
                    }
                    this.doSelectedChangeAnimate = false;
                    break;
                }
            });
            TapGesture.pop();
            SwipeGesture.create();
            SwipeGesture.onAction((s21) => {
                if (this.options === void 0 || this.options.buttons === void 0 ||
                    s21.sourceTool === SourceTool.TOUCHPAD) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (this.isCurrentPositionSelected) {
                    return;
                }
                if (Math.abs(s21.angle) < 90 && this.selectedIndexes[0] !==
                    Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
                    this.doSelectedChangeAnimate = false;
                } else if (Math.abs(s21.angle) > 90 && this.selectedIndexes[0] !== 0) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
                    this.doSelectedChangeAnimate = false;
                }
            });
            SwipeGesture.pop();
            PanGesture.create();
            PanGesture.onActionStart((o21) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let p21 = o21.fingerList.find(Boolean);
                if (p21 === void 0) {
                    return;
                }
                let q21 = p21.localX;
                this.panGestureStartPoint = { x: p21.globalX, y: p21.globalY };
                this.isPanGestureMoved = false;
                for (let r21 = 0; r21 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); r21++) {
                    q21 = q21 - this.buttonItemsSize[r21].width;
                    if (q21 < 0) {
                        this.isCurrentPositionSelected = r21 === this.selectedIndexes[0] ? true : false;
                        break;
                    }
                }
            });
            PanGesture.onActionUpdate((f21) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (!this.isCurrentPositionSelected) {
                    return;
                }
                let g21 = f21.fingerList.find(Boolean);
                if (g21 === void 0) {
                    return;
                }
                let h21 = g21.localX;
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(g21.globalX, g21.globalY)) {
                    this.isPanGestureMoved = true;
                }
                for (let n21 = 0; n21 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); n21++) {
                    h21 = h21 - this.buttonItemsSize[n21].width;
                    if (h21 < 0) {
                        this.doSelectedChangeAnimate = true;
                        this.selectedIndexes[0] = n21;
                        this.doSelectedChangeAnimate = false;
                        break;
                    }
                }
                this.zoomScaleArray.forEach((j21, k21) => {
                    if (k21 === this.selectedIndexes[0]) {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[k21] = 0.95;
                        });
                    } else {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[k21] = 1;
                        });
                    }
                });
            });
            PanGesture.onActionEnd((b21) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let c21 = b21.fingerList.find(Boolean);
                if (c21 === void 0) {
                    return;
                }
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(c21.globalX, c21.globalY)) {
                    this.isPanGestureMoved = true;
                }
                if (this.isMouseWheelScroll(b21)) {
                    let e21 = b21.offsetX !== 0 ? b21.offsetX : b21.offsetY;
                    this.doSelectedChangeAnimate = true;
                    if (e21 > 0 && this.selectedIndexes[0] > 0) {
                        this.selectedIndexes[0] -= 1;
                    } else if (e21 < 0 && this.selectedIndexes[0] <
                        Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                        this.selectedIndexes[0] += 1;
                    }
                    this.doSelectedChangeAnimate = false;
                }
                Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                    this.zoomScaleArray[this.selectedIndexes[0]] = 1;
                });
                this.isCurrentPositionSelected = false;
            });
            PanGesture.onActionCancel(() => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
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
        this.observeComponentCreation2((i18, j18) => {
            If.create();
            if (this.options !== void 0 && this.options.buttons != void 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q19, r19) => {
                        If.create();
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                {
                                    this.observeComponentCreation2((k20, l20) => {
                                        if (l20) {
                                            let m20 = new MultiSelectBackground(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                            }, undefined, k20, () => {
                                            }, {
                                                page: "library/src/main/ets/components/segmentbutton.ets",
                                                line: 1260,
                                                col: 11
                                            });
                                            ViewPU.create(m20);
                                            let n20 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options
                                                };
                                            };
                                            m20.paramsGenerator_ = n20;
                                        } else {
                                            this.updateStateVarsOfChildByElmtId(k20, {
                                                optionsArray: this.options.buttons,
                                                options: this.options
                                            });
                                        }
                                    }, { name: "MultiSelectBackground" });
                                }
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((g20, h20) => {
                                    Stack.create();
                                    Stack.direction(this.options.direction);
                                    Stack.size(ObservedObject.GetRawObject(this.componentSize));
                                    Stack.backgroundColor(this.options.backgroundColor ??
                                    segmentButtonTheme.BACKGROUND_COLOR);
                                    Stack.borderRadius(this.options.iconTextBackgroundRadius ??
                                        this.componentSize.height / 2);
                                    Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
                                }, Stack);
                                this.observeComponentCreation2((v19, w19) => {
                                    If.create();
                                    if (this.options.buttons !== void 0 && this.options.buttons.length > 1) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            {
                                                this.observeComponentCreation2((a20, b20) => {
                                                    if (b20) {
                                                        let c20 = new PressAndHoverEffectArray(this, {
                                                            options: this.options,
                                                            buttons: this.options.buttons,
                                                            pressArray: this.__pressArray,
                                                            hoverArray: this.__hoverArray,
                                                            hoverColorArray: this.__hoverColorArray
                                                        }, undefined, a20, () => {
                                                        }, {
                                                            page: "library/src/main/ets/components/segmentbutton.ets",
                                                            line: 1267,
                                                            col: 15
                                                        });
                                                        ViewPU.create(c20);
                                                        let d20 = () => {
                                                            return {
                                                                options: this.options,
                                                                buttons: this.options.buttons,
                                                                pressArray: this.pressArray,
                                                                hoverArray: this.hoverArray,
                                                                hoverColorArray: this.hoverColorArray
                                                            };
                                                        };
                                                        c20.paramsGenerator_ = d20;
                                                    } else {
                                                        this.updateStateVarsOfChildByElmtId(a20, {
                                                            options: this.options,
                                                            buttons: this.options.buttons
                                                        });
                                                    }
                                                }, { name: "PressAndHoverEffectArray" });
                                            }
                                        });
                                    } else {
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
                    this.observeComponentCreation2((o19, p19) => {
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
                    this.observeComponentCreation2((w18, x18) => {
                        If.create();
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                {
                                    this.observeComponentCreation2((i19, j19) => {
                                        if (j19) {
                                            let k19 = new MultiSelectItemArray(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, i19, () => {
                                            }, {
                                                page: "library/src/main/ets/components/segmentbutton.ets",
                                                line: 1284,
                                                col: 13
                                            });
                                            ViewPU.create(k19);
                                            let l19 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            k19.paramsGenerator_ = l19;
                                        } else {
                                            this.updateStateVarsOfChildByElmtId(i19, {
                                                optionsArray: this.options.buttons,
                                                options: this.options
                                            });
                                        }
                                    }, { name: "MultiSelectItemArray" });
                                }
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                {
                                    this.observeComponentCreation2((a19, b19) => {
                                        if (b19) {
                                            let c19 = new SelectItem(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, a19, () => {
                                            }, {
                                                page: "library/src/main/ets/components/segmentbutton.ets",
                                                line: 1290,
                                                col: 13
                                            });
                                            ViewPU.create(c19);
                                            let d19 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            c19.paramsGenerator_ = d19;
                                        } else {
                                            this.updateStateVarsOfChildByElmtId(a19, {
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
                        this.observeComponentCreation2((q18, r18) => {
                            if (r18) {
                                let s18 = new SegmentButtonItemArrayComponent(this, {
                                    pressArray: this.__pressArray,
                                    hoverArray: this.__hoverArray,
                                    hoverColorArray: this.__hoverColorArray,
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    selectedIndexes: this.__selectedIndexes,
                                    maxFontScale: this.getMaxFontSize(),
                                    onItemClicked: this.onItemClicked,
                                    isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized
                                }, undefined, q18, () => {
                                }, { page: "library/src/main/ets/components/segmentbutton.ets", line: 1305, col: 9 });
                                ViewPU.create(s18);
                                let t18 = () => {
                                    return {
                                        pressArray: this.pressArray,
                                        hoverArray: this.hoverArray,
                                        hoverColorArray: this.hoverColorArray,
                                        optionsArray: this.options.buttons,
                                        options: this.options,
                                        selectedIndexes: this.selectedIndexes,
                                        maxFontScale: this.getMaxFontSize(),
                                        onItemClicked: this.onItemClicked,
                                        isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized
                                    };
                                };
                                s18.paramsGenerator_ = t18;
                            } else {
                                this.updateStateVarsOfChildByElmtId(q18, {
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    maxFontScale: this.getMaxFontSize(),
                                    isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized
                                });
                            }
                        }, { name: "SegmentButtonItemArrayComponent" });
                    }
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Stack.pop();
    }

    getMaxFontSize() {
        if (typeof this.maxFontScale === void 0) {
            return DEFAULT_MAX_FONT_SCALE;
        }
        if (typeof this.maxFontScale === 'number') {
            return Math.max(Math.min(this.maxFontScale, MAX_MAX_FONT_SCALE), MIN_MAX_FONT_SCALE);
        }
        const e18 = this.getUIContext().getHostContext()?.resourceManager;
        if (!e18) {
            return DEFAULT_MAX_FONT_SCALE;
        }
        try {
            return e18.getNumber(this.maxFontScale.id);
        } catch (f18) {
            console.error(`Ace SegmentButton getMaxFontSize, error: ${f18.toString()}`);
            return DEFAULT_MAX_FONT_SCALE;
        }
    }

    getSelectedChangeCurve() {
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            return null;
        }
        return curves.springMotion(0.347, 0.99);
    }

    updateAnimatedProperty(v17) {
        let w17 = () => {
            this.selectedItemPosition =
                this.selectedIndexes.length === 0 ? {} : this.buttonItemsPosition[this.selectedIndexes[0]];
            this.buttonItemsSelected.forEach((c18, d18) => {
                this.buttonItemProperty[d18].fontColor = c18 ?
                    this.options.selectedFontColor ?? (this.options.type === 'tab' ?
                    segmentButtonTheme.TAB_SELECTED_FONT_COLOR : segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR) :
                    this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
            });
        };
        if (v17) {
            Context.animateTo({ curve: v17 }, w17);
        } else {
            w17();
        }
        this.buttonItemsSelected.forEach((z17, a18) => {
            this.buttonItemProperty[a18].fontSize = z17 ? this.options.selectedFontSize ??
            segmentButtonTheme.SELECTED_FONT_SIZE : this.options.fontSize ?? segmentButtonTheme.FONT_SIZE;
            this.buttonItemProperty[a18].fontWeight = z17 ? this.options.selectedFontWeight ?? FontWeight.Medium :
                this.options.fontWeight ?? FontWeight.Regular;
            this.buttonItemProperty[a18].isSelected = z17;
        });
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    SegmentButton,
    SegmentButtonOptions,
    SegmentButtonItemOptionsArray,
    SegmentButtonItemOptions,
};
