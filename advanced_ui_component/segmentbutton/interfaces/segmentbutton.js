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

var __decorate = (this && this.__decorate) || function (f25, g25, h25, i25) {
    var j25 = arguments.length,
        k25 = j25 < 3 ? g25 : i25 === null ? i25 = Object.getOwnPropertyDescriptor(g25, h25) : i25, l25;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        k25 = Reflect.decorate(f25, g25, h25, i25);
    } else {
        for (var m25 = f25.length - 1; m25 >= 0; m25--) {
            if (l25 = f25[m25]) {
                k25 = (j25 < 3 ? l25(k25) : j25 > 3 ? l25(g25, h25, k25) : l25(g25, h25)) || k25;
            }
        }
    }
    return j25 > 3 && k25 && Object.defineProperty(g25, h25, k25), k25;
};
var SegmentButtonItemOptionsArray_1, SegmentButtonOptions_1;
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
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
const RESOURCE_TYPE_FLOAT = 10002;
const RESOURCE_TYPE_INTEGER = 10007;
const segmentButtonTheme = {
    FONT_COLOR: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.segment_button_unselected_text_color'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    TAB_SELECTED_FONT_COLOR: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.segment_button_checked_text_color'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    CAPSULE_SELECTED_FONT_COLOR: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_foreground_contrary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    FONT_SIZE: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.segment_button_unselected_text_size'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    SELECTED_FONT_SIZE: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.segment_button_checked_text_size'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    BACKGROUND_COLOR: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.segment_button_backboard_color'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    TAB_SELECTED_BACKGROUND_COLOR: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.segment_button_checked_foreground_color'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    CAPSULE_SELECTED_BACKGROUND_COLOR: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_emphasize'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    FOCUS_BORDER_COLOR: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_focused_outline'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    HOVER_COLOR: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.segment_button_hover_color'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    PRESS_COLOR: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.segment_button_press_color'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    BACKGROUND_BLUR_STYLE: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.segment_button_background_blur_style'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    CONSTRAINT_SIZE_MIN_HEIGHT: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.segment_button_height'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    SEGMENT_BUTTON_MIN_FONT_SIZE: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.segment_button_min_font_size'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    SEGMENT_BUTTON_NORMAL_BORDER_RADIUS: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.segment_button_normal_border_radius'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    SEGMENT_ITEM_TEXT_OVERFLOW: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.segment_marquee'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    SEGMENT_BUTTON_FOCUS_TEXT_COLOR: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.segment_button_focus_text_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    SEGMENT_BUTTON_SHADOW: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.segment_button_shadow'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    SEGMENT_TEXT_HORIZONTAL_PADDING: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.segment_button_text_l_r_padding'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    SEGMENT_TEXT_VERTICAL_PADDING: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.segment_button_text_u_d_padding'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.segment_button_text_capsule_u_d_padding'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.segment_button_focus_backboard_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    SEGMENT_FOCUS_STYLE_CUSTOMIZED: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.segment_focus_control'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }
};

function nearEqual(d25, e25) {
    return Math.abs(d25 - e25) < 0.001;
}

let SegmentButtonItemOptions = class SegmentButtonItemOptions {
    constructor(c25) {
        this.icon = c25.icon;
        this.selectedIcon = c25.selectedIcon;
        this.text = c25.text;
        this.iconAccessibilityText = c25.iconAccessibilityText;
        this.selectedIconAccessibilityText = c25.selectedIconAccessibilityText;
        this.accessibilityLevel = c25.accessibilityLevel;
        this.accessibilityDescription = c25.accessibilityDescription;
    }
};
SegmentButtonItemOptions = __decorate([
    Observed
], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray =
    SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends Array {
        constructor(a25) {
            super(typeof a25 === 'number' ? a25 : 0);
            this.changeStartIndex = void 0;
            this.deleteCount = void 0;
            this.addLength = void 0;
            if (typeof a25 !== 'number' && a25 !== void 0) {
                super.push(...a25.map((b25) => new SegmentButtonItemOptions(b25)));
            }
        }

        push(...y24) {
            if (this.length + y24.length > MAX_ITEM_COUNT) {
                console.warn('Exceeded the maximum number of elements (5).');
                return this.length;
            }
            this.changeStartIndex = this.length;
            this.deleteCount = 0;
            this.addLength = y24.length;
            return super.push(...y24.map((z24) => new SegmentButtonItemOptions(z24)));
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

        unshift(...w24) {
            if (this.length + w24.length > MAX_ITEM_COUNT) {
                console.warn('Exceeded the maximum number of elements (5).');
                return this.length;
            }
            if (w24.length > 0) {
                this.changeStartIndex = 0;
                this.deleteCount = 0;
                this.addLength = w24.length;
            }
            return super.unshift(...w24.map((x24) => new SegmentButtonItemOptions(x24)));
        }

        splice(s24, t24, ...u24) {
            let v24 = (this.length - t24) < 0 ? 0 : (this.length - t24);
            v24 += u24.length;
            if (v24 < MIN_ITEM_COUNT) {
                console.warn('Below the minimum number of elements (2).');
                return [];
            }
            if (v24 > MAX_ITEM_COUNT) {
                console.warn('Exceeded the maximum number of elements (5).');
                return [];
            }
            this.changeStartIndex = s24;
            this.deleteCount = t24;
            this.addLength = u24.length;
            return super.splice(s24, t24, ...u24);
        }

        static create(r24) {
            return new SegmentButtonItemOptionsArray_1(r24);
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

    set buttons(q24) {
        if (this._buttons !== void 0 && this._buttons !== q24) {
            this.onButtonsChange?.();
        }
        this._buttons = q24;
    }

    constructor(o24) {
        this.multiply = false;
        this.showText = false;
        this.showIcon = false;
        this._buttons = void 0;
        this.fontColor = o24.fontColor ?? segmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = o24.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = o24.fontSize ?? segmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = o24.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = o24.fontWeight ?? FontWeight.Regular;
        this.selectedFontWeight = o24.selectedFontWeight ?? FontWeight.Medium;
        this.backgroundColor = o24.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = o24.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = o24.imageSize ?? { width: 24, height: 24 };
        this.buttonPadding = o24.buttonPadding;
        this.textPadding = o24.textPadding;
        this.type = o24.type;
        this.backgroundBlurStyle =
            o24.backgroundBlurStyle ??
            LengthMetrics.resource(segmentButtonTheme.BACKGROUND_BLUR_STYLE).value;
        this.localizedTextPadding = o24.localizedTextPadding;
        this.localizedButtonPadding = o24.localizedButtonPadding;
        this.direction = o24.direction ?? Direction.Auto;
        this.buttons = new SegmentButtonItemOptionsArray(o24.buttons);
        if (this.type === 'capsule') {
            this.multiply = o24.multiply ?? false;
            this.onButtonsUpdated();
            this.selectedFontColor = o24.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = o24.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        } else {
            this.showText = true;
        }
        let p24 = LengthMetrics.resource({
            'id': -1,
            'type': 10002,
            params: ['sys.float.segment_button_baseplate_padding'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }).value;
        this.componentPadding = this.multiply ? 0 : p24;
    }

    onButtonsUpdated() {
        this.buttons?.forEach(n24 => {
            this.showText ||= n24.text !== void 0;
            this.showIcon ||= n24.icon !== void 0 || n24.selectedIcon !== void 0;
        });
        if (this.showText && this.showIcon) {
            this.iconTextRadius = 12;
            this.iconTextBackgroundRadius = 14;
        }
    }

    static tab(m24) {
        return new SegmentButtonOptions_1({
            type: 'tab',
            buttons: m24.buttons,
            fontColor: m24.fontColor,
            selectedFontColor: m24.selectedFontColor,
            fontSize: m24.fontSize,
            selectedFontSize: m24.selectedFontSize,
            fontWeight: m24.fontWeight,
            selectedFontWeight: m24.selectedFontWeight,
            backgroundColor: m24.backgroundColor,
            selectedBackgroundColor: m24.selectedBackgroundColor,
            imageSize: m24.imageSize,
            buttonPadding: m24.buttonPadding,
            textPadding: m24.textPadding,
            localizedTextPadding: m24.localizedTextPadding,
            localizedButtonPadding: m24.localizedButtonPadding,
            backgroundBlurStyle: m24.backgroundBlurStyle,
            direction: m24.direction
        });
    }

    static capsule(l24) {
        return new SegmentButtonOptions_1({
            type: 'capsule',
            buttons: l24.buttons,
            multiply: l24.multiply,
            fontColor: l24.fontColor,
            selectedFontColor: l24.selectedFontColor,
            fontSize: l24.fontSize,
            selectedFontSize: l24.selectedFontSize,
            fontWeight: l24.fontWeight,
            selectedFontWeight: l24.selectedFontWeight,
            backgroundColor: l24.backgroundColor,
            selectedBackgroundColor: l24.selectedBackgroundColor,
            imageSize: l24.imageSize,
            buttonPadding: l24.buttonPadding,
            textPadding: l24.textPadding,
            localizedTextPadding: l24.localizedTextPadding,
            localizedButtonPadding: l24.localizedButtonPadding,
            backgroundBlurStyle: l24.backgroundBlurStyle,
            direction: l24.direction
        });
    }
};
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([
    Observed
], SegmentButtonOptions);

export { SegmentButtonOptions };

class MultiSelectBackground extends ViewPU {
    constructor(f24, g24, h24, i24 = -1, j24 = undefined, k24) {
        super(f24, h24, i24, k24);
        if (typeof j24 === 'function') {
            this.paramsGenerator_ = j24;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(g24.optionsArray, this, 'optionsArray');
        this.__options = new SynchedPropertyNesedObjectPU(g24.options, this, 'options');
        this.__buttonBorderRadius = this.initializeConsume('buttonBorderRadius', 'buttonBorderRadius');
        this.__buttonItemsSize = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
        this.setInitiallyProvidedValue(g24);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(e24) {
        this.__optionsArray.set(e24.optionsArray);
        this.__options.set(e24.options);
    }

    updateStateVars(d24) {
        this.__optionsArray.set(d24.optionsArray);
        this.__options.set(d24.options);
    }

    purgeVariableDependenciesOnElmtId(c24) {
        this.__optionsArray.purgeDependencyOnElmtId(c24);
        this.__options.purgeDependencyOnElmtId(c24);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(c24);
        this.__buttonItemsSize.purgeDependencyOnElmtId(c24);
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

    set buttonBorderRadius(b24) {
        this.__buttonBorderRadius.set(b24);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(a24) {
        this.__buttonItemsSize.set(a24);
    }

    initialRender() {
        this.observeComponentCreation2((y23, z23) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((o23, p23) => {
            ForEach.create();
            const q23 = (r23, s23) => {
                const t23 = r23;
                this.observeComponentCreation2((u23, v23) => {
                    If.create();
                    if (s23 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((w23, x23) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.layoutWeight(1);
                                Stack.height(this.buttonItemsSize[s23].height);
                                Stack.backgroundColor(this.options.backgroundColor ??
                                segmentButtonTheme.BACKGROUND_COLOR);
                                Stack.borderRadius(this.buttonBorderRadius[s23]);
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
            this.forEachUpdateFunction(o23, this.optionsArray, q23, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SelectItem extends ViewPU {
    constructor(i23, j23, k23, l23 = -1, m23 = undefined, n23) {
        super(i23, k23, l23, n23);
        if (typeof m23 === 'function') {
            this.paramsGenerator_ = m23;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(j23.optionsArray, this, 'optionsArray');
        this.__options = new SynchedPropertyNesedObjectPU(j23.options, this, 'options');
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(j23.selectedIndexes, this, 'selectedIndexes');
        this.__buttonItemsSize = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
        this.__selectedItemPosition = this.initializeConsume('selectedItemPosition', 'selectedItemPosition');
        this.__zoomScaleArray = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
        this.__buttonBorderRadius = this.initializeConsume('buttonBorderRadius', 'buttonBorderRadius');
        this.setInitiallyProvidedValue(j23);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(h23) {
        this.__optionsArray.set(h23.optionsArray);
        this.__options.set(h23.options);
    }

    updateStateVars(g23) {
        this.__optionsArray.set(g23.optionsArray);
        this.__options.set(g23.options);
    }

    purgeVariableDependenciesOnElmtId(f23) {
        this.__optionsArray.purgeDependencyOnElmtId(f23);
        this.__options.purgeDependencyOnElmtId(f23);
        this.__selectedIndexes.purgeDependencyOnElmtId(f23);
        this.__buttonItemsSize.purgeDependencyOnElmtId(f23);
        this.__selectedItemPosition.purgeDependencyOnElmtId(f23);
        this.__zoomScaleArray.purgeDependencyOnElmtId(f23);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(f23);
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

    set selectedIndexes(e23) {
        this.__selectedIndexes.set(e23);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(d23) {
        this.__buttonItemsSize.set(d23);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(c23) {
        this.__selectedItemPosition.set(c23);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(b23) {
        this.__zoomScaleArray.set(b23);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(a23) {
        this.__buttonBorderRadius.set(a23);
    }

    initialRender() {
        this.observeComponentCreation2((w22, x22) => {
            If.create();
            if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y22, z22) => {
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
                        Stack.shadow(resourceToNumber(this.getUIContext()?.getHostContext(),
                            segmentButtonTheme.SEGMENT_BUTTON_SHADOW, 0));
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
    constructor(o22, p22, q22, r22 = -1, s22 = undefined, t22) {
        super(o22, q22, r22, t22);
        if (typeof s22 === 'function') {
            this.paramsGenerator_ = s22;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(p22.optionsArray, this, 'optionsArray');
        this.__options = new SynchedPropertyNesedObjectPU(p22.options, this, 'options');
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(p22.selectedIndexes, this, 'selectedIndexes');
        this.__buttonItemsSize = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
        this.__zoomScaleArray = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
        this.__buttonBorderRadius = this.initializeConsume('buttonBorderRadius', 'buttonBorderRadius');
        this.__multiColor =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (u22, v22) => Color.Transparent), this,
                'multiColor');
        this.setInitiallyProvidedValue(p22);
        this.declareWatch('options', this.onOptionsChange);
        this.declareWatch('selectedIndexes', this.onSelectedChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(n22) {
        this.__optionsArray.set(n22.optionsArray);
        this.__options.set(n22.options);
        if (n22.multiColor !== undefined) {
            this.multiColor = n22.multiColor;
        }
    }

    updateStateVars(m22) {
        this.__optionsArray.set(m22.optionsArray);
        this.__options.set(m22.options);
    }

    purgeVariableDependenciesOnElmtId(l22) {
        this.__optionsArray.purgeDependencyOnElmtId(l22);
        this.__options.purgeDependencyOnElmtId(l22);
        this.__selectedIndexes.purgeDependencyOnElmtId(l22);
        this.__buttonItemsSize.purgeDependencyOnElmtId(l22);
        this.__zoomScaleArray.purgeDependencyOnElmtId(l22);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(l22);
        this.__multiColor.purgeDependencyOnElmtId(l22);
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

    set selectedIndexes(k22) {
        this.__selectedIndexes.set(k22);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(j22) {
        this.__buttonItemsSize.set(j22);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(i22) {
        this.__zoomScaleArray.set(i22);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(h22) {
        this.__buttonBorderRadius.set(h22);
    }

    get multiColor() {
        return this.__multiColor.get();
    }

    set multiColor(g22) {
        this.__multiColor.set(g22);
    }

    onOptionsChange() {
        for (let f22 = 0; f22 < this.selectedIndexes.length; f22++) {
            this.multiColor[this.selectedIndexes[f22]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    onSelectedChange() {
        for (let e22 = 0; e22 < MAX_ITEM_COUNT; e22++) {
            this.multiColor[e22] = Color.Transparent;
        }
        for (let d22 = 0; d22 < this.selectedIndexes.length; d22++) {
            this.multiColor[this.selectedIndexes[d22]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    aboutToAppear() {
        for (let c22 = 0; c22 < this.selectedIndexes.length; c22++) {
            this.multiColor[this.selectedIndexes[c22]] = this.options.selectedBackgroundColor ??
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
        }
    }

    initialRender() {
        this.observeComponentCreation2((a22, b22) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.padding(this.options.componentPadding);
        }, Row);
        this.observeComponentCreation2((q21, r21) => {
            ForEach.create();
            const s21 = (t21, u21) => {
                const v21 = t21;
                this.observeComponentCreation2((w21, x21) => {
                    If.create();
                    if (u21 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((y21, z21) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.width(this.buttonItemsSize[u21].width);
                                Stack.height(this.buttonItemsSize[u21].height);
                                Stack.backgroundColor(this.multiColor[u21]);
                                Stack.borderRadius(this.buttonBorderRadius[u21]);
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
            this.forEachUpdateFunction(q21, this.optionsArray, s21, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SegmentButtonItem extends ViewPU {
    constructor(k21, l21, m21, n21 = -1, o21 = undefined, p21) {
        super(k21, m21, n21, p21);
        if (typeof o21 === 'function') {
            this.paramsGenerator_ = o21;
        }
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(l21.selectedIndexes, this, 'selectedIndexes');
        this.__focusIndex = new SynchedPropertySimpleTwoWayPU(l21.focusIndex, this, 'focusIndex');
        this.__maxFontScale = new SynchedPropertyObjectOneWayPU(l21.maxFontScale, this, 'maxFontScale');
        this.__itemOptions = new SynchedPropertyNesedObjectPU(l21.itemOptions, this, 'itemOptions');
        this.__options = new SynchedPropertyNesedObjectPU(l21.options, this, 'options');
        this.__property = new SynchedPropertyNesedObjectPU(l21.property, this, 'property');
        this.__index = new SynchedPropertySimpleOneWayPU(l21.index, this, 'index');
        this.__isTextSupportMarquee =
            new ObservedPropertySimplePU(resourceToNumber(this.getUIContext()?.getHostContext(),
                segmentButtonTheme.SEGMENT_ITEM_TEXT_OVERFLOW, 1.0) === 0.0, this, 'isTextSupportMarquee');
        this.__isMarqueeAndFadeout =
            new SynchedPropertySimpleOneWayPU(l21.isMarqueeAndFadeout, this, 'isMarqueeAndFadeout');
        this.__isSegmentFocusStyleCustomized =
            new SynchedPropertySimpleOneWayPU(l21.isSegmentFocusStyleCustomized, this, 'isSegmentFocusStyleCustomized');
        this.__isTextInMarqueeCondition = new ObservedPropertySimplePU(false, this, 'isTextInMarqueeCondition');
        this.__isButtonTextFadeout = new ObservedPropertySimplePU(false, this, 'isButtonTextFadeout');
        this.groupId = '';
        this.__hover = new SynchedPropertySimpleOneWayPU(l21.hover, this, 'hover');
        this.setInitiallyProvidedValue(l21);
        this.declareWatch('focusIndex', this.onFocusIndex);
        this.declareWatch('hover', this.onFocusIndex);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(j21) {
        this.__itemOptions.set(j21.itemOptions);
        this.__options.set(j21.options);
        this.__property.set(j21.property);
        if (j21.isTextSupportMarquee !== undefined) {
            this.isTextSupportMarquee = j21.isTextSupportMarquee;
        }
        if (j21.isTextInMarqueeCondition !== undefined) {
            this.isTextInMarqueeCondition = j21.isTextInMarqueeCondition;
        }
        if (j21.isButtonTextFadeout !== undefined) {
            this.isButtonTextFadeout = j21.isButtonTextFadeout;
        }
        if (j21.groupId !== undefined) {
            this.groupId = j21.groupId;
        }
    }

    updateStateVars(i21) {
        this.__maxFontScale.reset(i21.maxFontScale);
        this.__itemOptions.set(i21.itemOptions);
        this.__options.set(i21.options);
        this.__property.set(i21.property);
        this.__index.reset(i21.index);
        this.__isMarqueeAndFadeout.reset(i21.isMarqueeAndFadeout);
        this.__isSegmentFocusStyleCustomized.reset(i21.isSegmentFocusStyleCustomized);
        this.__hover.reset(i21.hover);
    }

    purgeVariableDependenciesOnElmtId(h21) {
        this.__selectedIndexes.purgeDependencyOnElmtId(h21);
        this.__focusIndex.purgeDependencyOnElmtId(h21);
        this.__maxFontScale.purgeDependencyOnElmtId(h21);
        this.__itemOptions.purgeDependencyOnElmtId(h21);
        this.__options.purgeDependencyOnElmtId(h21);
        this.__property.purgeDependencyOnElmtId(h21);
        this.__index.purgeDependencyOnElmtId(h21);
        this.__isTextSupportMarquee.purgeDependencyOnElmtId(h21);
        this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(h21);
        this.__isSegmentFocusStyleCustomized.purgeDependencyOnElmtId(h21);
        this.__isTextInMarqueeCondition.purgeDependencyOnElmtId(h21);
        this.__isButtonTextFadeout.purgeDependencyOnElmtId(h21);
        this.__hover.purgeDependencyOnElmtId(h21);
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

    set selectedIndexes(g21) {
        this.__selectedIndexes.set(g21);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(f21) {
        this.__focusIndex.set(f21);
    }

    get maxFontScale() {
        return this.__maxFontScale.get();
    }

    set maxFontScale(e21) {
        this.__maxFontScale.set(e21);
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

    set index(d21) {
        this.__index.set(d21);
    }

    get isTextSupportMarquee() {
        return this.__isTextSupportMarquee.get();
    }

    set isTextSupportMarquee(c21) {
        this.__isTextSupportMarquee.set(c21);
    }

    get isMarqueeAndFadeout() {
        return this.__isMarqueeAndFadeout.get();
    }

    set isMarqueeAndFadeout(b21) {
        this.__isMarqueeAndFadeout.set(b21);
    }

    get isSegmentFocusStyleCustomized() {
        return this.__isSegmentFocusStyleCustomized.get();
    }

    set isSegmentFocusStyleCustomized(a21) {
        this.__isSegmentFocusStyleCustomized.set(a21);
    }

    get isTextInMarqueeCondition() {
        return this.__isTextInMarqueeCondition.get();
    }

    set isTextInMarqueeCondition(z20) {
        this.__isTextInMarqueeCondition.set(z20);
    }

    get isButtonTextFadeout() {
        return this.__isButtonTextFadeout.get();
    }

    set isButtonTextFadeout(y20) {
        this.__isButtonTextFadeout.set(y20);
    }

    get hover() {
        return this.__hover.get();
    }

    set hover(x20) {
        this.__hover.set(x20);
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
        this.observeComponentCreation2((v20, w20) => {
            Column.create({ space: 2 });
            Column.direction(this.options.direction);
            Column.focusScopePriority(this.groupId,
                Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO);
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.getButtonPadding());
            Column.constraintSize({ minHeight: segmentButtonTheme.CONSTRAINT_SIZE_MIN_HEIGHT });
        }, Column);
        this.observeComponentCreation2((r20, s20) => {
            If.create();
            if (this.options.showIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t20, u20) => {
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
        this.observeComponentCreation2((n20, o20) => {
            If.create();
            if (this.options.showText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p20, q20) => {
                        Text.create(this.itemOptions.text);
                        Text.direction(this.options.direction);
                        Text.fontColor(this.getFontColor());
                        Text.fontWeight(this.property.fontWeight);
                        Text.fontSize(this.property.fontSize);
                        Text.minFontSize(this.isSegmentFocusStyleCustomized ? this.property.fontSize : 9);
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
    constructor(h20, i20, j20, k20 = -1, l20 = undefined, m20) {
        super(h20, j20, k20, m20);
        if (typeof l20 === 'function') {
            this.paramsGenerator_ = l20;
        }
        this.__buttonItemsSize = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
        this.__press = new SynchedPropertySimpleOneWayPU(i20.press, this, 'press');
        this.__hover = new SynchedPropertySimpleOneWayPU(i20.hover, this, 'hover');
        this.__colorProperty = new SynchedPropertyNesedObjectPU(i20.colorProperty, this, 'colorProperty');
        this.__buttonBorderRadius = this.initializeConsume('buttonBorderRadius', 'buttonBorderRadius');
        this.__options = new SynchedPropertyNesedObjectPU(i20.options, this, 'options');
        this.pressIndex = 0;
        this.pressColor = segmentButtonTheme.PRESS_COLOR;
        this.setInitiallyProvidedValue(i20);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(g20) {
        this.__colorProperty.set(g20.colorProperty);
        this.__options.set(g20.options);
        if (g20.pressIndex !== undefined) {
            this.pressIndex = g20.pressIndex;
        }
        if (g20.pressColor !== undefined) {
            this.pressColor = g20.pressColor;
        }
    }

    updateStateVars(f20) {
        this.__press.reset(f20.press);
        this.__hover.reset(f20.hover);
        this.__colorProperty.set(f20.colorProperty);
        this.__options.set(f20.options);
    }

    purgeVariableDependenciesOnElmtId(e20) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(e20);
        this.__press.purgeDependencyOnElmtId(e20);
        this.__hover.purgeDependencyOnElmtId(e20);
        this.__colorProperty.purgeDependencyOnElmtId(e20);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(e20);
        this.__options.purgeDependencyOnElmtId(e20);
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

    set buttonItemsSize(d20) {
        this.__buttonItemsSize.set(d20);
    }

    get press() {
        return this.__press.get();
    }

    set press(c20) {
        this.__press.set(c20);
    }

    get hover() {
        return this.__hover.get();
    }

    set hover(b20) {
        this.__hover.set(b20);
    }

    get colorProperty() {
        return this.__colorProperty.get();
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(a20) {
        this.__buttonBorderRadius.set(a20);
    }

    get options() {
        return this.__options.get();
    }

    initialRender() {
        this.observeComponentCreation2((y19, z19) => {
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
    constructor(s19, t19, u19, v19 = -1, w19 = undefined, x19) {
        super(s19, u19, v19, x19);
        if (typeof w19 === 'function') {
            this.paramsGenerator_ = w19;
        }
        this.__buttons = new SynchedPropertyNesedObjectPU(t19.buttons, this, 'buttons');
        this.__options = new SynchedPropertyNesedObjectPU(t19.options, this, 'options');
        this.__pressArray = new SynchedPropertyObjectTwoWayPU(t19.pressArray, this, 'pressArray');
        this.__hoverArray = new SynchedPropertyObjectTwoWayPU(t19.hoverArray, this, 'hoverArray');
        this.__hoverColorArray = new SynchedPropertyObjectTwoWayPU(t19.hoverColorArray, this, 'hoverColorArray');
        this.__zoomScaleArray = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
        this.setInitiallyProvidedValue(t19);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(r19) {
        this.__buttons.set(r19.buttons);
        this.__options.set(r19.options);
    }

    updateStateVars(q19) {
        this.__buttons.set(q19.buttons);
        this.__options.set(q19.options);
    }

    purgeVariableDependenciesOnElmtId(p19) {
        this.__buttons.purgeDependencyOnElmtId(p19);
        this.__options.purgeDependencyOnElmtId(p19);
        this.__pressArray.purgeDependencyOnElmtId(p19);
        this.__hoverArray.purgeDependencyOnElmtId(p19);
        this.__hoverColorArray.purgeDependencyOnElmtId(p19);
        this.__zoomScaleArray.purgeDependencyOnElmtId(p19);
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

    set pressArray(o19) {
        this.__pressArray.set(o19);
    }

    get hoverArray() {
        return this.__hoverArray.get();
    }

    set hoverArray(n19) {
        this.__hoverArray.set(n19);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(m19) {
        this.__hoverColorArray.set(m19);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(l19) {
        this.__zoomScaleArray.set(l19);
    }

    initialRender() {
        this.observeComponentCreation2((j19, k19) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
        }, Row);
        this.observeComponentCreation2((v18, w18) => {
            ForEach.create();
            const x18 = (y18, z18) => {
                const a19 = y18;
                this.observeComponentCreation2((b19, c19) => {
                    If.create();
                    if (z18 < MAX_ITEM_COUNT) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((h19, i19) => {
                                Stack.create();
                                Stack.direction(this.options.direction);
                                Stack.scale({
                                    x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 :
                                    this.zoomScaleArray[z18],
                                    y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 :
                                    this.zoomScaleArray[z18]
                                });
                            }, Stack);
                            {
                                this.observeComponentCreation2((d19, e19) => {
                                    if (e19) {
                                        let f19 = new PressAndHoverEffect(this, {
                                            pressIndex: z18,
                                            colorProperty: this.hoverColorArray[z18],
                                            press: this.pressArray[z18],
                                            hover: this.hoverArray[z18],
                                            options: this.options,
                                        }, undefined, d19, () => {
                                        }, {
                                            page: 'library/src/main/ets/components/segmentbutton.ets',
                                            line: 688,
                                            col: 13
                                        });
                                        ViewPU.create(f19);
                                        let g19 = () => {
                                            return {
                                                pressIndex: z18,
                                                colorProperty: this.hoverColorArray[z18],
                                                press: this.pressArray[z18],
                                                hover: this.hoverArray[z18],
                                                options: this.options
                                            };
                                        };
                                        f19.paramsGenerator_ = g19;
                                    } else {
                                        this.updateStateVarsOfChildByElmtId(d19, {
                                            colorProperty: this.hoverColorArray[z18],
                                            press: this.pressArray[z18],
                                            hover: this.hoverArray[z18],
                                            options: this.options
                                        });
                                    }
                                }, { name: 'PressAndHoverEffect' });
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
            this.forEachUpdateFunction(v18, this.buttons, x18, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SegmentButtonItemArrayComponent extends ViewPU {
    constructor(j18, k18, l18, m18 = -1, n18 = undefined, o18) {
        super(j18, l18, m18, o18);
        if (typeof n18 === 'function') {
            this.paramsGenerator_ = n18;
        }
        this.__optionsArray = new SynchedPropertyNesedObjectPU(k18.optionsArray, this, 'optionsArray');
        this.__options = new SynchedPropertyNesedObjectPU(k18.options, this, 'options');
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(k18.selectedIndexes, this, 'selectedIndexes');
        this.__componentSize = this.initializeConsume('componentSize', 'componentSize');
        this.__buttonBorderRadius = this.initializeConsume('buttonBorderRadius', 'buttonBorderRadius');
        this.__buttonItemsSize = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
        this.__buttonItemsPosition = this.initializeConsume('buttonItemsPosition', 'buttonItemsPosition');
        this.__focusIndex = this.initializeConsume('focusIndex', 'focusIndex');
        this.__zoomScaleArray = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
        this.__buttonItemProperty = this.initializeConsume('buttonItemProperty', 'buttonItemProperty');
        this.__buttonItemsSelected = this.initializeConsume('buttonItemsSelected', 'buttonItemsSelected');
        this.__pressArray = new SynchedPropertyObjectTwoWayPU(k18.pressArray, this, 'pressArray');
        this.__hoverArray = new SynchedPropertyObjectTwoWayPU(k18.hoverArray, this, 'hoverArray');
        this.__hoverColorArray = new SynchedPropertyObjectTwoWayPU(k18.hoverColorArray, this, 'hoverColorArray');
        this.__maxFontScale = new SynchedPropertyObjectOneWayPU(k18.maxFontScale, this, 'maxFontScale');
        this.__buttonWidth =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (t18, u18) => 0), this, 'buttonWidth');
        this.__buttonHeight =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (r18, s18) => 0), this, 'buttonHeight');
        this.__isMarqueeAndFadeout = new ObservedPropertySimplePU(false, this, 'isMarqueeAndFadeout');
        this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (p18, q18) => 0);
        this.groupId = util.generateRandomUUID(true);
        this.onItemClicked = undefined;
        this.__isSegmentFocusStyleCustomized =
            new SynchedPropertySimpleOneWayPU(k18.isSegmentFocusStyleCustomized, this, 'isSegmentFocusStyleCustomized');
        this.setInitiallyProvidedValue(k18);
        this.declareWatch('optionsArray', this.onOptionsArrayChange);
        this.declareWatch('options', this.onOptionsChange);
        this.declareWatch('buttonItemsSize', this.onButtonItemsSizeChange);
        this.declareWatch('focusIndex', this.onFocusIndex);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(i18) {
        this.__optionsArray.set(i18.optionsArray);
        this.__options.set(i18.options);
        if (i18.buttonWidth !== undefined) {
            this.buttonWidth = i18.buttonWidth;
        }
        if (i18.buttonHeight !== undefined) {
            this.buttonHeight = i18.buttonHeight;
        }
        if (i18.isMarqueeAndFadeout !== undefined) {
            this.isMarqueeAndFadeout = i18.isMarqueeAndFadeout;
        }
        if (i18.buttonItemsRealHeight !== undefined) {
            this.buttonItemsRealHeight = i18.buttonItemsRealHeight;
        }
        if (i18.groupId !== undefined) {
            this.groupId = i18.groupId;
        }
        if (i18.onItemClicked !== undefined) {
            this.onItemClicked = i18.onItemClicked;
        }
    }

    updateStateVars(h18) {
        this.__optionsArray.set(h18.optionsArray);
        this.__options.set(h18.options);
        this.__maxFontScale.reset(h18.maxFontScale);
        this.__isSegmentFocusStyleCustomized.reset(h18.isSegmentFocusStyleCustomized);
    }

    purgeVariableDependenciesOnElmtId(g18) {
        this.__optionsArray.purgeDependencyOnElmtId(g18);
        this.__options.purgeDependencyOnElmtId(g18);
        this.__selectedIndexes.purgeDependencyOnElmtId(g18);
        this.__componentSize.purgeDependencyOnElmtId(g18);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(g18);
        this.__buttonItemsSize.purgeDependencyOnElmtId(g18);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(g18);
        this.__focusIndex.purgeDependencyOnElmtId(g18);
        this.__zoomScaleArray.purgeDependencyOnElmtId(g18);
        this.__buttonItemProperty.purgeDependencyOnElmtId(g18);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(g18);
        this.__pressArray.purgeDependencyOnElmtId(g18);
        this.__hoverArray.purgeDependencyOnElmtId(g18);
        this.__hoverColorArray.purgeDependencyOnElmtId(g18);
        this.__maxFontScale.purgeDependencyOnElmtId(g18);
        this.__buttonWidth.purgeDependencyOnElmtId(g18);
        this.__buttonHeight.purgeDependencyOnElmtId(g18);
        this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(g18);
        this.__isSegmentFocusStyleCustomized.purgeDependencyOnElmtId(g18);
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

    set selectedIndexes(f18) {
        this.__selectedIndexes.set(f18);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(e18) {
        this.__componentSize.set(e18);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(d18) {
        this.__buttonBorderRadius.set(d18);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(c18) {
        this.__buttonItemsSize.set(c18);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(b18) {
        this.__buttonItemsPosition.set(b18);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(a18) {
        this.__focusIndex.set(a18);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(z17) {
        this.__zoomScaleArray.set(z17);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(y17) {
        this.__buttonItemProperty.set(y17);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(x17) {
        this.__buttonItemsSelected.set(x17);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(w17) {
        this.__pressArray.set(w17);
    }

    get hoverArray() {
        return this.__hoverArray.get();
    }

    set hoverArray(v17) {
        this.__hoverArray.set(v17);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(u17) {
        this.__hoverColorArray.set(u17);
    }

    get maxFontScale() {
        return this.__maxFontScale.get();
    }

    set maxFontScale(t17) {
        this.__maxFontScale.set(t17);
    }

    get buttonWidth() {
        return this.__buttonWidth.get();
    }

    set buttonWidth(s17) {
        this.__buttonWidth.set(s17);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(r17) {
        this.__buttonHeight.set(r17);
    }

    get isMarqueeAndFadeout() {
        return this.__isMarqueeAndFadeout.get();
    }

    set isMarqueeAndFadeout(q17) {
        this.__isMarqueeAndFadeout.set(q17);
    }

    get isSegmentFocusStyleCustomized() {
        return this.__isSegmentFocusStyleCustomized.get();
    }

    set isSegmentFocusStyleCustomized(p17) {
        this.__isSegmentFocusStyleCustomized.set(p17);
    }

    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach((n17, o17) => {
            this.buttonWidth[o17] = n17.width;
            this.buttonHeight[o17] = n17.height;
        });
    }

    changeSelectedIndexes(e17) {
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
            let f17 = this.selectedIndexes;
            for (let j17 = 0; j17 < this.optionsArray.deleteCount; j17++) {
                let k17 = f17.indexOf(this.optionsArray.changeStartIndex);
                let l17 = f17.map(m17 => this.optionsArray.changeStartIndex &&
                    (m17 > this.optionsArray.changeStartIndex) ? m17 - 1 : m17);
                if (k17 !== -1) {
                    l17.splice(k17, 1);
                }
                f17 = l17;
            }
            for (let g17 = 0; g17 < this.optionsArray.addLength; g17++) {
                let h17 = f17.map(i17 => this.optionsArray.changeStartIndex &&
                    (i17 >= this.optionsArray.changeStartIndex) ? i17 + 1 : i17);
                f17 = h17;
            }
            this.selectedIndexes = f17;
        }
    }

    changeFocusIndex(d17) {
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
        let c17 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 &&
            this.optionsArray.addLength !== void 0) {
            this.changeSelectedIndexes(c17);
            this.changeFocusIndex(c17);
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
        for (let b17 = 0; b17 < this.buttonItemsRealHeight.length; b17++) {
            this.buttonItemsRealHeight[b17] = 0;
        }
    }

    getBorderRadius(z16) {
        let a17 = this.buttonBorderRadius[z16];
        if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex]) {
            return {
                topStart: LengthMetrics.vp((a17.topStart?.value ?? 0) + 4),
                topEnd: LengthMetrics.vp((a17.topEnd?.value ?? 0) + 4),
                bottomStart: LengthMetrics.vp((a17.bottomStart?.value ?? 0) + 4),
                bottomEnd: LengthMetrics.vp((a17.bottomEnd?.value ?? 0) + 4)
            };
        }
        return a17;
    }

    focusStack(t16, u16 = null) {
        this.observeComponentCreation2((x16, y16) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((v16, w16) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.borderRadius(this.getBorderRadius(t16));
            Stack.size({
                width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ?
                    this.buttonWidth[t16] + 8 : this.buttonWidth[t16],
                height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ?
                    this.buttonHeight[t16] + 8 : this.buttonHeight[t16]
            });
            Stack.borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR);
            Stack.borderWidth(2);
        }, Stack);
        Stack.pop();
        Stack.pop();
    }

    calculateBorderRadius() {
        let o16 = Array.from({
            length: MAX_ITEM_COUNT
        }, (r16, s16) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        });
        for (let p16 = 0; p16 < this.buttonBorderRadius.length; p16++) {
            let q16 = this.buttonItemsSize[p16].height / 2;
            if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
                o16[p16].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? q16);
                o16[p16].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? q16);
                o16[p16].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? q16);
                o16[p16].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? q16);
            } else {
                if (p16 === 0) {
                    o16[p16].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? q16);
                    o16[p16].topEnd = LengthMetrics.vp(0);
                    o16[p16].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? q16);
                    o16[p16].bottomEnd = LengthMetrics.vp(0);
                } else if (this.options.buttons &&
                    p16 === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    o16[p16].topStart = LengthMetrics.vp(0);
                    o16[p16].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? q16);
                    o16[p16].bottomStart = LengthMetrics.vp(0);
                    o16[p16].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? q16);
                } else {
                    o16[p16].topStart = LengthMetrics.vp(0);
                    o16[p16].topEnd = LengthMetrics.vp(0);
                    o16[p16].bottomStart = LengthMetrics.vp(0);
                    o16[p16].bottomEnd = LengthMetrics.vp(0);
                }
            }
        }
        this.buttonBorderRadius = o16;
    }

    getAccessibilityDescription(n16) {
        return (typeof n16 !== undefined) ? n16 : undefined;
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
        this.observeComponentCreation2((i15, j15) => {
            If.create();
            if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j16, k16) => {
                        Row.create({ space: 1 });
                        Row.direction(this.options.direction);
                        Row.focusScopeId(this.groupId, true);
                        Row.padding(this.options.componentPadding);
                        Row.onSizeChange((l16, m16) => {
                            this.componentSize = { width: m16.width, height: m16.height };
                        });
                    }, Row);
                    this.observeComponentCreation2((k15, l15) => {
                        ForEach.create();
                        const m15 = (n15, o15) => {
                            const p15 = n15;
                            this.observeComponentCreation2((q15, r15) => {
                                If.create();
                                if (o15 < MAX_ITEM_COUNT) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((c16, d16) => {
                                            Button.createWithChild();
                                            Button.type(ButtonType.Normal);
                                            Button.stateEffect(false);
                                            Button.hoverEffect(HoverEffect.None);
                                            Button.backgroundColor(Color.Transparent);
                                            Button.accessibilityLevel(p15.accessibilityLevel);
                                            Button.accessibilitySelected(this.options.multiply ? undefined :
                                            this.selectedIndexes.includes(o15));
                                            Button.accessibilityChecked(this.options.multiply ?
                                            this.selectedIndexes.includes(o15) : undefined);
                                            Button.accessibilityDescription(this.getAccessibilityDescription(p15.accessibilityDescription));
                                            Button.direction(this.options.direction);
                                            Button.borderRadius(this.buttonBorderRadius[o15]);
                                            Button.scale({
                                                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ?
                                                    1 : this.zoomScaleArray[o15],
                                                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ?
                                                    1 : this.zoomScaleArray[o15]
                                            });
                                            Button.layoutWeight(1);
                                            Button.padding(0);
                                            Button.onSizeChange((h16, i16) => {
                                                this.buttonItemsSize[o15] =
                                                    { width: i16.width, height: this.buttonItemsSize[o15].height };
                                                if (i16.width) {
                                                    this.buttonItemsPosition[o15] = {
                                                        start: LengthMetrics.vp(Number.parseFloat(this.options.componentPadding.toString()) +
                                                            (Number.parseFloat(i16.width.toString()) + 1) * o15),
                                                        top: LengthMetrics.px(Math.floor(this.getUIContext()
                                                            .vp2px(Number.parseFloat(this.options.componentPadding.toString()))))
                                                    };
                                                }
                                            });
                                            ViewStackProcessor.visualState('normal');
                                            Button.overlay(undefined);
                                            ViewStackProcessor.visualState('focused');
                                            Button.overlay({
                                                builder: () => {
                                                    this.focusStack.call(this, o15);
                                                }
                                            }, {
                                                align: Alignment.Center
                                            });
                                            ViewStackProcessor.visualState();
                                            Button.onFocus(() => {
                                                this.focusIndex = o15;
                                                if (this.isSegmentFocusStyleCustomized) {
                                                    this.customizeSegmentFocusStyle(o15);
                                                }
                                            });
                                            Button.onBlur(() => {
                                                this.focusIndex = -1;
                                                this.hoverColorArray[o15].hoverColor = Color.Transparent;
                                            });
                                            Gesture.create(GesturePriority.Low);
                                            TapGesture.create();
                                            TapGesture.onAction(() => {
                                                if (this.onItemClicked) {
                                                    this.onItemClicked(o15);
                                                }
                                                if (this.options.type === 'capsule' &&
                                                    (this.options.multiply ?? false)) {
                                                    if (this.selectedIndexes.indexOf(o15) === -1) {
                                                        this.selectedIndexes.push(o15);
                                                    } else {
                                                        this.selectedIndexes.splice(this.selectedIndexes.indexOf(o15),
                                                            1);
                                                    }
                                                } else {
                                                    this.selectedIndexes[0] = o15;
                                                }
                                            });
                                            TapGesture.pop();
                                            Gesture.pop();
                                            Button.onTouch((g16) => {
                                                if (this.isSegmentFocusStyleCustomized) {
                                                    this.getUIContext().getFocusController().clearFocus();
                                                }
                                                if (g16.source !== SourceType.TouchScreen) {
                                                    return;
                                                }
                                                if (g16.type === TouchType.Down) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[o15] = 0.95;
                                                    });
                                                } else if (g16.type === TouchType.Up || g16.type === TouchType.Cancel) {
                                                    Context.animateTo({
                                                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                                                    }, () => {
                                                        this.zoomScaleArray[o15] = 1;
                                                    });
                                                }
                                            });
                                            Button.onHover((f16) => {
                                                this.hoverArray[o15] = f16;
                                                if (f16) {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[o15].hoverColor =
                                                            this.isSegmentFocusStyleCustomized &&
                                                                this.focusIndex === o15 ?
                                                            segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR :
                                                            segmentButtonTheme.HOVER_COLOR;
                                                    });
                                                } else {
                                                    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                                                        this.hoverColorArray[o15].hoverColor =
                                                            this.isSegmentFocusStyleCustomized &&
                                                                this.focusIndex === o15 ?
                                                            segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR :
                                                            Color.Transparent;
                                                    });
                                                }
                                            });
                                            Button.onMouse((e16) => {
                                                switch (e16.action) {
                                                    case MouseAction.Press:
                                                        Context.animateTo({ curve: curves.springMotion(0.347, 0.99) },
                                                            () => {
                                                                this.zoomScaleArray[o15] = 0.95;
                                                            });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[o15] = true;
                                                        });
                                                        break;
                                                    case MouseAction.Release:
                                                        Context.animateTo({ curve: curves.springMotion(0.347, 0.99) },
                                                            () => {
                                                                this.zoomScaleArray[o15] = 1;
                                                            });
                                                        Context.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                                                            this.pressArray[o15] = false;
                                                        });
                                                        break;
                                                }
                                            });
                                        }, Button);
                                        this.observeComponentCreation2((w15, x15) => {
                                            __Common__.create();
                                            __Common__.onSizeChange((y15, z15) => {
                                                this.buttonItemsRealHeight[o15] = z15.height;
                                                let a16 = Math.max(...this.buttonItemsRealHeight.slice(0,
                                                    this.options.buttons ?
                                                    this.options.buttons.length : 0));
                                                for (let b16 = 0; b16 < this.buttonItemsSize.length; b16++) {
                                                    this.buttonItemsSize[b16] =
                                                        { width: this.buttonItemsSize[b16].width, height: a16 };
                                                }
                                                this.calculateBorderRadius();
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((s15, t15) => {
                                                if (t15) {
                                                    let u15 = new SegmentButtonItem(this, {
                                                        isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                                                        isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                                                        selectedIndexes: this.__selectedIndexes,
                                                        focusIndex: this.__focusIndex,
                                                        index: o15,
                                                        itemOptions: p15,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[o15],
                                                        groupId: this.groupId,
                                                        maxFontScale: this.maxFontScale,
                                                        hover: this.hoverArray[o15],
                                                    }, undefined, s15, () => {
                                                    }, {
                                                        page: 'library/src/main/ets/components/segmentbutton.ets',
                                                        line: 925,
                                                        col: 15
                                                    });
                                                    ViewPU.create(u15);
                                                    let v15 = () => {
                                                        return {
                                                            isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                                                            isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                                                            selectedIndexes: this.selectedIndexes,
                                                            focusIndex: this.focusIndex,
                                                            index: o15,
                                                            itemOptions: p15,
                                                            options: this.options,
                                                            property: this.buttonItemProperty[o15],
                                                            groupId: this.groupId,
                                                            maxFontScale: this.maxFontScale,
                                                            hover: this.hoverArray[o15]
                                                        };
                                                    };
                                                    u15.paramsGenerator_ = v15;
                                                } else {
                                                    this.updateStateVarsOfChildByElmtId(s15, {
                                                        isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                                                        isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                                                        index: o15,
                                                        itemOptions: p15,
                                                        options: this.options,
                                                        property: this.buttonItemProperty[o15],
                                                        maxFontScale: this.maxFontScale,
                                                        hover: this.hoverArray[o15]
                                                    });
                                                }
                                            }, { name: 'SegmentButtonItem' });
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
                        this.forEachUpdateFunction(k15, this.optionsArray, m15, undefined, true, false);
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

    customizeSegmentFocusStyle(h15) {
        if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0 &&
            this.selectedIndexes[0] === h15) {
            this.hoverColorArray[h15].hoverColor = this.isDefaultSelectedBgColor() ?
            segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : this.options.selectedBackgroundColor;
        } else {
            this.hoverColorArray[h15].hoverColor =
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
    constructor(j14, k14, l14, m14 = -1, n14 = undefined, o14) {
        super(j14, l14, m14, o14);
        if (typeof n14 === 'function') {
            this.paramsGenerator_ = n14;
        }
        this.__options = new SynchedPropertyNesedObjectPU(k14.options, this, 'options');
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(k14.selectedIndexes, this, 'selectedIndexes');
        this.onItemClicked = undefined;
        this.__maxFontScale = new SynchedPropertyObjectOneWayPU(k14.maxFontScale, this, 'maxFontScale');
        this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, 'componentSize');
        this.addProvidedVar('componentSize', this.__componentSize, false);
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (f15, g15) => {
            return {
                topStart: LengthMetrics.vp(0),
                topEnd: LengthMetrics.vp(0),
                bottomStart: LengthMetrics.vp(0),
                bottomEnd: LengthMetrics.vp(0)
            };
        }), this, 'buttonBorderRadius');
        this.addProvidedVar('buttonBorderRadius', this.__buttonBorderRadius, false);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (d15, e15) => {
            return {};
        }), this, 'buttonItemsSize');
        this.addProvidedVar('buttonItemsSize', this.__buttonItemsSize, false);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (b15, c15) => {
            return {};
        }), this, 'buttonItemsPosition');
        this.addProvidedVar('buttonItemsPosition', this.__buttonItemsPosition, false);
        this.__buttonItemsSelected =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (z14, a15) => false), this,
                'buttonItemsSelected');
        this.addProvidedVar('buttonItemsSelected', this.__buttonItemsSelected, false);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (x14, y14) => new ItemProperty()), this, 'buttonItemProperty');
        this.addProvidedVar('buttonItemProperty', this.__buttonItemProperty, false);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, 'focusIndex');
        this.addProvidedVar('focusIndex', this.__focusIndex, false);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, 'selectedItemPosition');
        this.addProvidedVar('selectedItemPosition', this.__selectedItemPosition, false);
        this.__zoomScaleArray =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (v14, w14) => 1.0), this,
                'zoomScaleArray');
        this.addProvidedVar('zoomScaleArray', this.__zoomScaleArray, false);
        this.__pressArray =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (t14, u14) => false), this,
                'pressArray');
        this.__hoverArray =
            new ObservedPropertyObjectPU(Array.from({ length: MAX_ITEM_COUNT }, (r14, s14) => false), this,
                'hoverArray');
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: MAX_ITEM_COUNT
        }, (p14, q14) => new HoverColorProperty()), this, 'hoverColorArray');
        this.doSelectedChangeAnimate = false;
        this.isCurrentPositionSelected = false;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = false;
        this.__shouldMirror = new ObservedPropertySimplePU(false, this, 'shouldMirror');
        this.isSegmentFocusStyleCustomized =
            resourceToNumber(this.getUIContext()?.getHostContext(), segmentButtonTheme.SEGMENT_FOCUS_STYLE_CUSTOMIZED,
                1.0) ===
                0.0;
        this.isGestureInProgress = false;
        this.setInitiallyProvidedValue(k14);
        this.declareWatch('options', this.onOptionsChange);
        this.declareWatch('selectedIndexes', this.onSelectedChange);
        this.declareWatch('buttonItemsPosition', this.onItemsPositionChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(i14) {
        this.__options.set(i14.options);
        if (i14.onItemClicked !== undefined) {
            this.onItemClicked = i14.onItemClicked;
        }
        if (i14.maxFontScale === undefined) {
            this.__maxFontScale.set(DEFAULT_MAX_FONT_SCALE);
        }
        if (i14.componentSize !== undefined) {
            this.componentSize = i14.componentSize;
        }
        if (i14.buttonBorderRadius !== undefined) {
            this.buttonBorderRadius = i14.buttonBorderRadius;
        }
        if (i14.buttonItemsSize !== undefined) {
            this.buttonItemsSize = i14.buttonItemsSize;
        }
        if (i14.buttonItemsPosition !== undefined) {
            this.buttonItemsPosition = i14.buttonItemsPosition;
        }
        if (i14.buttonItemsSelected !== undefined) {
            this.buttonItemsSelected = i14.buttonItemsSelected;
        }
        if (i14.buttonItemProperty !== undefined) {
            this.buttonItemProperty = i14.buttonItemProperty;
        }
        if (i14.focusIndex !== undefined) {
            this.focusIndex = i14.focusIndex;
        }
        if (i14.selectedItemPosition !== undefined) {
            this.selectedItemPosition = i14.selectedItemPosition;
        }
        if (i14.zoomScaleArray !== undefined) {
            this.zoomScaleArray = i14.zoomScaleArray;
        }
        if (i14.pressArray !== undefined) {
            this.pressArray = i14.pressArray;
        }
        if (i14.hoverArray !== undefined) {
            this.hoverArray = i14.hoverArray;
        }
        if (i14.hoverColorArray !== undefined) {
            this.hoverColorArray = i14.hoverColorArray;
        }
        if (i14.doSelectedChangeAnimate !== undefined) {
            this.doSelectedChangeAnimate = i14.doSelectedChangeAnimate;
        }
        if (i14.isCurrentPositionSelected !== undefined) {
            this.isCurrentPositionSelected = i14.isCurrentPositionSelected;
        }
        if (i14.panGestureStartPoint !== undefined) {
            this.panGestureStartPoint = i14.panGestureStartPoint;
        }
        if (i14.isPanGestureMoved !== undefined) {
            this.isPanGestureMoved = i14.isPanGestureMoved;
        }
        if (i14.shouldMirror !== undefined) {
            this.shouldMirror = i14.shouldMirror;
        }
        if (i14.isSegmentFocusStyleCustomized !== undefined) {
            this.isSegmentFocusStyleCustomized = i14.isSegmentFocusStyleCustomized;
        }
        if (i14.isGestureInProgress !== undefined) {
            this.isGestureInProgress = i14.isGestureInProgress;
        }
    }

    updateStateVars(h14) {
        this.__options.set(h14.options);
        this.__maxFontScale.reset(h14.maxFontScale);
    }

    purgeVariableDependenciesOnElmtId(g14) {
        this.__options.purgeDependencyOnElmtId(g14);
        this.__selectedIndexes.purgeDependencyOnElmtId(g14);
        this.__maxFontScale.purgeDependencyOnElmtId(g14);
        this.__componentSize.purgeDependencyOnElmtId(g14);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(g14);
        this.__buttonItemsSize.purgeDependencyOnElmtId(g14);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(g14);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(g14);
        this.__buttonItemProperty.purgeDependencyOnElmtId(g14);
        this.__focusIndex.purgeDependencyOnElmtId(g14);
        this.__selectedItemPosition.purgeDependencyOnElmtId(g14);
        this.__zoomScaleArray.purgeDependencyOnElmtId(g14);
        this.__pressArray.purgeDependencyOnElmtId(g14);
        this.__hoverArray.purgeDependencyOnElmtId(g14);
        this.__hoverColorArray.purgeDependencyOnElmtId(g14);
        this.__shouldMirror.purgeDependencyOnElmtId(g14);
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

    set selectedIndexes(f14) {
        this.__selectedIndexes.set(f14);
    }

    get maxFontScale() {
        return this.__maxFontScale.get();
    }

    set maxFontScale(e14) {
        this.__maxFontScale.set(e14);
    }

    get componentSize() {
        return this.__componentSize.get();
    }

    set componentSize(d14) {
        this.__componentSize.set(d14);
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get();
    }

    set buttonBorderRadius(c14) {
        this.__buttonBorderRadius.set(c14);
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get();
    }

    set buttonItemsSize(b14) {
        this.__buttonItemsSize.set(b14);
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get();
    }

    set buttonItemsPosition(a14) {
        this.__buttonItemsPosition.set(a14);
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get();
    }

    set buttonItemsSelected(z13) {
        this.__buttonItemsSelected.set(z13);
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get();
    }

    set buttonItemProperty(y13) {
        this.__buttonItemProperty.set(y13);
    }

    get focusIndex() {
        return this.__focusIndex.get();
    }

    set focusIndex(x13) {
        this.__focusIndex.set(x13);
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get();
    }

    set selectedItemPosition(w13) {
        this.__selectedItemPosition.set(w13);
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get();
    }

    set zoomScaleArray(v13) {
        this.__zoomScaleArray.set(v13);
    }

    get pressArray() {
        return this.__pressArray.get();
    }

    set pressArray(u13) {
        this.__pressArray.set(u13);
    }

    get hoverArray() {
        return this.__hoverArray.get();
    }

    set hoverArray(t13) {
        this.__hoverArray.set(t13);
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get();
    }

    set hoverColorArray(s13) {
        this.__hoverColorArray.set(s13);
    }

    get shouldMirror() {
        return this.__shouldMirror.get();
    }

    set shouldMirror(r13) {
        this.__shouldMirror.set(r13);
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
        this.buttonItemsSelected.forEach((p13, q13) => {
            this.buttonItemsSelected[q13] = false;
        });
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            this.selectedIndexes.forEach(o13 => this.buttonItemsSelected[o13] = true);
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
        let m13 = this.selectedIndexes.some(n13 => {
            return (n13 === void 0 || n13 < 0 || (this.options.buttons && n13 >= this.options.buttons.length));
        });
        if (m13) {
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

    isMouseWheelScroll(l13) {
        return l13.source === SourceType.Mouse && !this.isPanGestureMoved;
    }

    isMovedFromPanGestureStartPoint(j13, k13) {
        return !nearEqual(j13, this.panGestureStartPoint.x) || !nearEqual(k13, this.panGestureStartPoint.y);
    }

    isShouldMirror() {
        if (this.options.direction == Direction.Rtl) {
            return true;
        }
        try {
            let i13 = I18n.System.getSystemLanguage();
            if (I18n.isRTL(i13) && this.options.direction != Direction.Ltr) {
                return true;
            }
        } catch (h13) {
            console.error(`Ace SegmentButton getSystemLanguage, error: ${h13.toString()}`);
        }
        return false;
    }

    initialRender() {
        this.observeComponentCreation2((j12, k12) => {
            Stack.create();
            Stack.direction(this.options ? this.options.direction : undefined);
            Stack.onBlur(() => {
                this.focusIndex = -1;
            });
            Stack.onKeyEvent((g13) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (g13.type === KeyType.Down) {
                    if (g13.keyCode === KeyCode.KEYCODE_SPACE || g13.keyCode === KeyCode.KEYCODE_ENTER ||
                        g13.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
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
            TapGesture.onAction((z12) => {
                if (this.isGestureInProgress) {
                    return;
                }
                let a13 = z12.fingerList.find(Boolean);
                if (a13 === void 0) {
                    return;
                }
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                let b13 = a13.localX;
                let c13 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
                for (let d13 = 0; d13 < c13; d13++) {
                    b13 = b13 - this.buttonItemsSize[d13].width;
                    if (b13 >= 0) {
                        continue;
                    }
                    this.doSelectedChangeAnimate =
                        this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ?
                            false : true;
                    let e13 = this.isShouldMirror() ? c13 - 1 - d13 : d13;
                    if (this.onItemClicked) {
                        this.onItemClicked(e13);
                    }
                    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                        let f13 = this.selectedIndexes.indexOf(e13);
                        if (f13 === -1) {
                            this.selectedIndexes.push(e13);
                        } else {
                            this.selectedIndexes.splice(f13, 1);
                        }
                    } else {
                        this.selectedIndexes[0] = e13;
                    }
                    this.doSelectedChangeAnimate = false;
                    break;
                }
            });
            TapGesture.pop();
            SwipeGesture.create();
            SwipeGesture.onAction((y12) => {
                if (this.options === void 0 || this.options.buttons === void 0 ||
                    y12.sourceTool === SourceTool.TOUCHPAD) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (this.isCurrentPositionSelected) {
                    return;
                }
                if (Math.abs(y12.angle) < 90 && this.selectedIndexes[0] !==
                    Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
                    this.doSelectedChangeAnimate = false;
                } else if (Math.abs(y12.angle) > 90 && this.selectedIndexes[0] !== 0) {
                    this.doSelectedChangeAnimate = true;
                    this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
                    this.doSelectedChangeAnimate = false;
                }
            });
            SwipeGesture.pop();
            PanGesture.create();
            PanGesture.onActionStart((u12) => {
                this.isGestureInProgress = true;
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let v12 = u12.fingerList.find(Boolean);
                if (v12 === void 0) {
                    return;
                }
                let w12 = v12.localX;
                this.panGestureStartPoint = { x: v12.globalX, y: v12.globalY };
                this.isPanGestureMoved = false;
                for (let x12 = 0; x12 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); x12++) {
                    w12 = w12 - this.buttonItemsSize[x12].width;
                    if (w12 < 0) {
                        this.isCurrentPositionSelected = x12 === this.selectedIndexes[0] ? true : false;
                        break;
                    }
                }
            });
            PanGesture.onActionUpdate((o12) => {
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                if (!this.isCurrentPositionSelected) {
                    return;
                }
                let p12 = o12.fingerList.find(Boolean);
                if (p12 === void 0) {
                    return;
                }
                let q12 = p12.localX;
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(p12.globalX, p12.globalY)) {
                    this.isPanGestureMoved = true;
                }
                for (let t12 = 0; t12 < Math.min(this.options.buttons.length, this.buttonItemsSize.length); t12++) {
                    q12 = q12 - this.buttonItemsSize[t12].width;
                    if (q12 < 0) {
                        this.doSelectedChangeAnimate = true;
                        this.selectedIndexes[0] = t12;
                        this.doSelectedChangeAnimate = false;
                        break;
                    }
                }
                this.zoomScaleArray.forEach((r12, s12) => {
                    if (s12 === this.selectedIndexes[0]) {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[s12] = 0.95;
                        });
                    } else {
                        Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[s12] = 1;
                        });
                    }
                });
            });
            PanGesture.onActionEnd((l12) => {
                this.isGestureInProgress = false;
                if (this.options === void 0 || this.options.buttons === void 0) {
                    return;
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                    return;
                }
                let m12 = l12.fingerList.find(Boolean);
                if (m12 === void 0) {
                    return;
                }
                if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(m12.globalX, m12.globalY)) {
                    this.isPanGestureMoved = true;
                }
                if (this.isMouseWheelScroll(l12)) {
                    let n12 = l12.offsetX !== 0 ? l12.offsetX : l12.offsetY;
                    this.doSelectedChangeAnimate = true;
                    if (n12 > 0 && this.selectedIndexes[0] > 0) {
                        this.selectedIndexes[0] -= 1;
                    } else if (n12 < 0 && this.selectedIndexes[0] <
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
                this.isGestureInProgress = false;
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
        this.observeComponentCreation2((d11, e11) => {
            If.create();
            if (this.options !== void 0 && this.options.buttons != void 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v11, w11) => {
                        If.create();
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                {
                                    this.observeComponentCreation2((f12, g12) => {
                                        if (g12) {
                                            let h12 = new MultiSelectBackground(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                            }, undefined, f12, () => {
                                            }, {
                                                page: 'library/src/main/ets/components/segmentbutton.ets',
                                                line: 1267,
                                                col: 11
                                            });
                                            ViewPU.create(h12);
                                            let i12 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options
                                                };
                                            };
                                            h12.paramsGenerator_ = i12;
                                        } else {
                                            this.updateStateVarsOfChildByElmtId(f12, {
                                                optionsArray: this.options.buttons,
                                                options: this.options
                                            });
                                        }
                                    }, { name: 'MultiSelectBackground' });
                                }
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((d12, e12) => {
                                    Stack.create();
                                    Stack.direction(this.options.direction);
                                    Stack.size(ObservedObject.GetRawObject(this.componentSize));
                                    Stack.backgroundColor(this.options.backgroundColor ??
                                    segmentButtonTheme.BACKGROUND_COLOR);
                                    Stack.borderRadius(this.options.iconTextBackgroundRadius ??
                                        this.componentSize.height / 2);
                                    Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
                                }, Stack);
                                this.observeComponentCreation2((x11, y11) => {
                                    If.create();
                                    if (this.options.buttons !== void 0 && this.options.buttons.length > 1) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            {
                                                this.observeComponentCreation2((z11, a12) => {
                                                    if (a12) {
                                                        let b12 = new PressAndHoverEffectArray(this, {
                                                            options: this.options,
                                                            buttons: this.options.buttons,
                                                            pressArray: this.__pressArray,
                                                            hoverArray: this.__hoverArray,
                                                            hoverColorArray: this.__hoverColorArray
                                                        }, undefined, z11, () => {
                                                        }, {
                                                            page: 'library/src/main/ets/components/segmentbutton.ets',
                                                            line: 1274,
                                                            col: 15
                                                        });
                                                        ViewPU.create(b12);
                                                        let c12 = () => {
                                                            return {
                                                                options: this.options,
                                                                buttons: this.options.buttons,
                                                                pressArray: this.pressArray,
                                                                hoverArray: this.hoverArray,
                                                                hoverColorArray: this.hoverColorArray
                                                            };
                                                        };
                                                        b12.paramsGenerator_ = c12;
                                                    } else {
                                                        this.updateStateVarsOfChildByElmtId(z11, {
                                                            options: this.options,
                                                            buttons: this.options.buttons
                                                        });
                                                    }
                                                }, { name: 'PressAndHoverEffectArray' });
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
                    this.observeComponentCreation2((t11, u11) => {
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
                    this.observeComponentCreation2((j11, k11) => {
                        If.create();
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                {
                                    this.observeComponentCreation2((p11, q11) => {
                                        if (q11) {
                                            let r11 = new MultiSelectItemArray(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, p11, () => {
                                            }, {
                                                page: 'library/src/main/ets/components/segmentbutton.ets',
                                                line: 1291,
                                                col: 13
                                            });
                                            ViewPU.create(r11);
                                            let s11 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            r11.paramsGenerator_ = s11;
                                        } else {
                                            this.updateStateVarsOfChildByElmtId(p11, {
                                                optionsArray: this.options.buttons,
                                                options: this.options
                                            });
                                        }
                                    }, { name: 'MultiSelectItemArray' });
                                }
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                {
                                    this.observeComponentCreation2((l11, m11) => {
                                        if (m11) {
                                            let n11 = new SelectItem(this, {
                                                optionsArray: this.options.buttons,
                                                options: this.options,
                                                selectedIndexes: this.__selectedIndexes
                                            }, undefined, l11, () => {
                                            }, {
                                                page: 'library/src/main/ets/components/segmentbutton.ets',
                                                line: 1297,
                                                col: 13
                                            });
                                            ViewPU.create(n11);
                                            let o11 = () => {
                                                return {
                                                    optionsArray: this.options.buttons,
                                                    options: this.options,
                                                    selectedIndexes: this.selectedIndexes
                                                };
                                            };
                                            n11.paramsGenerator_ = o11;
                                        } else {
                                            this.updateStateVarsOfChildByElmtId(l11, {
                                                optionsArray: this.options.buttons,
                                                options: this.options
                                            });
                                        }
                                    }, { name: 'SelectItem' });
                                }
                            });
                        }
                    }, If);
                    If.pop();
                    Stack.pop();
                    {
                        this.observeComponentCreation2((f11, g11) => {
                            if (g11) {
                                let h11 = new SegmentButtonItemArrayComponent(this, {
                                    pressArray: this.__pressArray,
                                    hoverArray: this.__hoverArray,
                                    hoverColorArray: this.__hoverColorArray,
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    selectedIndexes: this.__selectedIndexes,
                                    maxFontScale: this.getMaxFontSize(),
                                    onItemClicked: this.onItemClicked,
                                    isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized
                                }, undefined, f11, () => {
                                }, { page: 'library/src/main/ets/components/segmentbutton.ets', line: 1312, col: 9 });
                                ViewPU.create(h11);
                                let i11 = () => {
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
                                h11.paramsGenerator_ = i11;
                            } else {
                                this.updateStateVarsOfChildByElmtId(f11, {
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    maxFontScale: this.getMaxFontSize(),
                                    isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized
                                });
                            }
                        }, { name: 'SegmentButtonItemArrayComponent' });
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
        const b11 = this.getUIContext().getHostContext()?.resourceManager;
        if (!b11) {
            return DEFAULT_MAX_FONT_SCALE;
        }
        try {
            return b11.getNumber(this.maxFontScale.id);
        } catch (c11) {
            console.error(`Ace SegmentButton getMaxFontSize, error: ${c11.toString()}`);
            return DEFAULT_MAX_FONT_SCALE;
        }
    }

    getSelectedChangeCurve() {
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            return null;
        }
        return curves.springMotion(0.347, 0.99);
    }

    updateAnimatedProperty(v10) {
        let w10 = () => {
            this.selectedItemPosition =
                this.selectedIndexes.length === 0 ? {} : this.buttonItemsPosition[this.selectedIndexes[0]];
            this.buttonItemsSelected.forEach((z10, a11) => {
                this.buttonItemProperty[a11].fontColor = z10 ?
                    this.options.selectedFontColor ?? (this.options.type === 'tab' ?
                    segmentButtonTheme.TAB_SELECTED_FONT_COLOR : segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR) :
                    this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
            });
        };
        if (v10) {
            Context.animateTo({ curve: v10 }, w10);
        } else {
            w10();
        }
        this.buttonItemsSelected.forEach((x10, y10) => {
            this.buttonItemProperty[y10].fontSize = x10 ? this.options.selectedFontSize ??
            segmentButtonTheme.SELECTED_FONT_SIZE : this.options.fontSize ?? segmentButtonTheme.FONT_SIZE;
            this.buttonItemProperty[y10].fontWeight = x10 ? this.options.selectedFontWeight ?? FontWeight.Medium :
                this.options.fontWeight ?? FontWeight.Regular;
            this.buttonItemProperty[y10].isSelected = x10;
        });
    }

    rerender() {
        this.updateDirtyElements();
    }
}

function resourceToNumber(q10, r10, s10) {
    if (!r10 || !r10.type || !q10) {
        console.error('[SegmentButton] failed: resource get fail.');
        return s10;
    }
    let t10 = q10?.resourceManager;
    if (!t10) {
        console.error('[SegmentButton] failed to get resourceManager.');
        return s10;
    }
    switch (r10.type) {
        case RESOURCE_TYPE_FLOAT:
        case RESOURCE_TYPE_INTEGER:
            try {
                if (r10.id !== -1) {
                    return t10.getNumber(r10);
                }
                return t10.getNumberByName(r10.params[0].split('.')[2]);
            } catch (u10) {
                console.error(`[SegmentButton] get resource error, return defaultValue`);
                return s10;
            }
        default:
            return s10;
    }
}

export default {
    SegmentButton,
    SegmentButtonOptions,
    SegmentButtonItemOptionsArray,
    SegmentButtonItemOptions,
};