/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

var __decorate =
  (this && this.__decorate) ||
  function (decorators, target, key, desc) {
    var c = arguments.length,
      r = c < 3 ? target : desc === null ? (desc = Object.getOwnPropertyDescriptor(target, key)) : desc,
      d;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function')
      r = Reflect.decorate(decorators, target, key, desc);
    else
      for (var i = decorators.length - 1; i >= 0; i--)
        if ((d = decorators[i])) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return (c > 3 && r && Object.defineProperty(target, key, r), r);
  };
var SegmentButtonItemOptionsArray_1, SegmentButtonOptions_1;
if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {});
}
const curves = globalThis.requireNativeModule('ohos.curves');
const KeyCode = globalThis.requireNapi('multimodalInput.keyCode').KeyCode;
const util = globalThis.requireNapi('util');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const I18n = requireNapi('i18n');
const uiMaterial = requireNapi('arkui.uiMaterial');
const deviceInfo = requireNapi('deviceInfo');
const CustomLayoutAlgorithm = requireNapi('arkui.layoutAlgorithm').CustomLayoutAlgorithm;
const DynamicLayout = requireNapi('arkui.components.ArkDynamicLayout').DynamicLayout;
const MIN_ITEM_COUNT = 2;
const MAX_ITEM_COUNT = 5;
const DEFAULT_MAX_FONT_SCALE = 1;
const MAX_MAX_FONT_SCALE = 2;
const MIN_MAX_FONT_SCALE = 1;
const RESOURCE_TYPE_FLOAT = 10002;
const RESOURCE_TYPE_INTEGER = 10007;
const ACCESSIBILITY_SELECTED_DESCRIPTION = ' ';
const ACCESSIBILITY_DEFAULT_DESCRIPTION = '';
const CAPSULE_FOCUS_SELECTED_OFFSET = 4;
const segmentButtonTheme = {
  FONT_COLOR: {
    id: 125834608,
    type: 10001,
    params: ['sys.color.segment_button_unselected_text_color'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  TAB_SELECTED_FONT_COLOR: {
    id: 125834606,
    type: 10001,
    params: ['sys.color.segment_button_checked_text_color'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  CAPSULE_SELECTED_FONT_COLOR: {
    id: 125829123,
    type: 10001,
    params: ['sys.color.ohos_id_color_foreground_contrary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  FONT_SIZE: {
    id: 125834603,
    type: 10002,
    params: ['sys.float.segment_button_unselected_text_size'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SELECTED_FONT_SIZE: {
    id: 125834602,
    type: 10002,
    params: ['sys.float.segment_button_checked_text_size'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  ADAPTIVE_ITEM_FONT_SIZE: {
    id: 125830974,
    type: 10002,
    params: ['sys.float.Caption_M'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  BACKGROUND_COLOR: {
    id: 125834609,
    type: 10001,
    params: ['sys.color.segment_button_backboard_color'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  TAB_SELECTED_BACKGROUND_COLOR: {
    id: 125834607,
    type: 10001,
    params: ['sys.color.segment_button_checked_foreground_color'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  CAPSULE_SELECTED_BACKGROUND_COLOR: {
    id: 125829135,
    type: 10001,
    params: ['sys.color.ohos_id_color_emphasize'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  FOCUS_BORDER_COLOR: {
    id: 125829180,
    type: 10001,
    params: ['sys.color.ohos_id_color_focused_outline'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  HOVER_COLOR: {
    id: 125834610,
    type: 10001,
    params: ['sys.color.segment_button_hover_color'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  PRESS_COLOR: {
    id: 125834611,
    type: 10001,
    params: ['sys.color.segment_button_press_color'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  BACKGROUND_BLUR_STYLE: {
    id: 125834604,
    type: 10002,
    params: ['sys.float.segment_button_background_blur_style'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  CONSTRAINT_SIZE_MIN_HEIGHT: {
    id: 125834592,
    type: 10002,
    params: ['sys.float.segment_button_height'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_MIN_FONT_SIZE: {
    id: 125834598,
    type: 10002,
    params: ['sys.float.segment_button_min_font_size'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_NORMAL_BORDER_RADIUS: {
    id: 125834599,
    type: 10002,
    params: ['sys.float.segment_button_normal_border_radius'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_ITEM_TEXT_OVERFLOW: {
    id: 125834600,
    type: 10002,
    params: ['sys.float.segment_marquee'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_FOCUS_TEXT_COLOR: {
    id: 125834613,
    type: 10001,
    params: ['sys.color.segment_button_focus_text_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_TEXT_HORIZONTAL_PADDING: {
    id: 125834597,
    type: 10002,
    params: ['sys.float.segment_button_text_l_r_padding'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_TEXT_VERTICAL_PADDING: {
    id: 125834595,
    type: 10002,
    params: ['sys.float.segment_button_text_u_d_padding'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING: {
    id: 125834596,
    type: 10002,
    params: ['sys.float.segment_button_text_capsule_u_d_padding'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR: {
    id: 125834612,
    type: 10001,
    params: ['sys.color.segment_button_focus_backboard_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_FOCUS_STYLE_CUSTOMIZED: {
    id: 125834601,
    type: 10002,
    params: ['sys.float.segment_focus_control'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_CONTAINER_SHAPE: {
    id: 125835654,
    type: 10002,
    params: ['sys.float.segmentbutton_container_shape'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_SELECTED_BACKGROUND_SHAPE: {
    id: 125835653,
    type: 10002,
    params: ['sys.float.segmentbutton_selected_background_shape'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_UNSELECTED_FONT_WEIGHT: {
    id: 125835711,
    type: 10002,
    params: ['sys.float.segment_button_unselected_font_weight'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_BORDER_WIDTH: {
    id: 125835712,
    type: 10002,
    params: ['sys.float.segment_button_border_width'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_BORDER_COLOR: {
    id: 125835713,
    type: 10001,
    params: ['sys.color.segment_button_border_color'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
};
function nearEqual(first, second) {
  return Math.abs(first - second) < 0.001;
}
function validateLengthMetrics(value, defaultValue) {
  const actualValue = value ?? defaultValue;
  return actualValue.value < 0 || actualValue.unit === LengthUnit.PERCENT ? defaultValue : actualValue;
}
function initFontWeight(defaultValue) {
  const value = LengthMetrics.resource(segmentButtonTheme.SEGMENT_BUTTON_UNSELECTED_FONT_WEIGHT).value;
  switch (value) {
    case 100:
      return FontWeight.Lighter;
    case 400:
      return FontWeight.Regular;
    case 500:
      return FontWeight.Medium;
    case 700:
      return FontWeight.Bold;
    case 900:
      return FontWeight.Bolder;
    default:
      return defaultValue;
  }
}
export var BorderRadiusMode;
(function (BorderRadiusMode) {
  BorderRadiusMode[(BorderRadiusMode['DEFAULT'] = 0)] = 'DEFAULT';
  BorderRadiusMode[(BorderRadiusMode['CUSTOM'] = 1)] = 'CUSTOM';
})(BorderRadiusMode || (BorderRadiusMode = {}));
let SegmentButtonItemOptions = class SegmentButtonItemOptions {
  constructor(options) {
    this.icon = options.icon;
    this.selectedIcon = options.selectedIcon;
    this.text = options.text;
    this.iconAccessibilityText = options.iconAccessibilityText;
    this.selectedIconAccessibilityText = options.selectedIconAccessibilityText;
    this.accessibilityLevel = options.accessibilityLevel;
    this.accessibilityDescription = options.accessibilityDescription;
  }
};
SegmentButtonItemOptions = __decorate([Observed], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = (SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends (
  Array
) {
  constructor(elementsOrLength) {
    super(typeof elementsOrLength === 'number' ? elementsOrLength : 0);
    this.changeStartIndex = void 0;
    this.deleteCount = void 0;
    this.addLength = void 0;
    if (typeof elementsOrLength !== 'number' && elementsOrLength !== void 0) {
      super.push(...elementsOrLength.map(element => new SegmentButtonItemOptions(element)));
    }
  }
  push(...items) {
    if (this.length + items.length > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).');
      return this.length;
    }
    this.changeStartIndex = this.length;
    this.deleteCount = 0;
    this.addLength = items.length;
    return super.push(...items.map(element => new SegmentButtonItemOptions(element)));
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
  unshift(...items) {
    if (this.length + items.length > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).');
      return this.length;
    }
    if (items.length > 0) {
      this.changeStartIndex = 0;
      this.deleteCount = 0;
      this.addLength = items.length;
    }
    return super.unshift(...items.map(element => new SegmentButtonItemOptions(element)));
  }
  splice(start, deleteCount, ...items) {
    let length = this.length - deleteCount < 0 ? 0 : this.length - deleteCount;
    length += items.length;
    if (length < MIN_ITEM_COUNT) {
      console.warn('Below the minimum number of elements (2).');
      return [];
    }
    if (length > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).');
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
});
SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = __decorate([Observed], SegmentButtonItemOptionsArray);
export { SegmentButtonItemOptionsArray };
let SegmentButtonOptions = (SegmentButtonOptions_1 = class SegmentButtonOptions {
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
    this.hasFontSize = false;
    this.hasSelectedFontSize = false;
    this._buttons = void 0;
    this.fontColor = options.fontColor ?? segmentButtonTheme.FONT_COLOR;
    this.selectedFontColor = options.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
    this.fontSize = options.fontSize ?? segmentButtonTheme.FONT_SIZE;
    this.selectedFontSize = options.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
    this.hasFontSize = options.fontSize !== undefined ? true : false;
    this.hasSelectedFontSize = options.selectedFontSize !== undefined ? true : false;
    this.fontWeight = options.fontWeight ?? initFontWeight(FontWeight.Regular);
    this.selectedFontWeight = options.selectedFontWeight ?? FontWeight.Medium;
    this.backgroundColor = options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
    this.selectedBackgroundColor = options.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
    this.imageSize = options.imageSize ?? { width: 24, height: 24 };
    this.buttonPadding = options.buttonPadding;
    this.textPadding = options.textPadding;
    this.type = options.type;
    this.backgroundBlurStyle =
      options.backgroundBlurStyle ?? LengthMetrics.resource(segmentButtonTheme.BACKGROUND_BLUR_STYLE).value;
    this.localizedTextPadding = options.localizedTextPadding;
    this.localizedButtonPadding = options.localizedButtonPadding;
    this.direction = options.direction ?? Direction.Auto;
    this.borderRadiusMode = options.borderRadiusMode ?? BorderRadiusMode.DEFAULT;
    if (this.borderRadiusMode !== BorderRadiusMode.DEFAULT && this.borderRadiusMode !== BorderRadiusMode.CUSTOM) {
      this.borderRadiusMode = BorderRadiusMode.DEFAULT;
    }
    this.backgroundBorderRadius = validateLengthMetrics(
      options.backgroundBorderRadius,
      LengthMetrics.resource(segmentButtonTheme.SEGMENT_BUTTON_CONTAINER_SHAPE)
    );
    this.itemBorderRadius = validateLengthMetrics(
      options.itemBorderRadius,
      LengthMetrics.resource(segmentButtonTheme.SEGMENT_BUTTON_SELECTED_BACKGROUND_SHAPE)
    );
    this.buttons = new SegmentButtonItemOptionsArray(options.buttons);
    if (this.type === 'capsule') {
      this.multiply = options.multiply ?? false;
      this.onButtonsUpdated();
      this.selectedFontColor = options.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
      this.selectedBackgroundColor =
        options.selectedBackgroundColor ?? segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
    } else {
      this.showText = true;
    }
    let themePadding = LengthMetrics.resource({
      id: 125830920,
      type: 10002,
      params: ['sys.float.padding_level1'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }).value;
    this.componentPadding = this.multiply ? 0 : themePadding;
    let info = uiMaterial.getMaterialInfo();
    if (info.state === uiMaterial.MaterialState.ENABLE && !options.backgroundSystemMaterial) {
      this.backgroundSystemMaterial = new uiMaterial.ImmersiveMaterial({
        style: uiMaterial.ImmersiveStyle.THIN,
      });
    } else if (info.state !== uiMaterial.MaterialState.DISABLE) {
      this.backgroundSystemMaterial = options.backgroundSystemMaterial;
    }
  }
  onButtonsUpdated() {
    this.buttons?.forEach(button => {
      this.showText ||= button.text !== void 0;
      this.showIcon ||= button.icon !== void 0 || button.selectedIcon !== void 0;
    });
    if (this.showText && this.showIcon) {
      this.iconTextRadius = 12;
      this.iconTextBackgroundRadius = 14;
    }
  }
  static tab(options) {
    return new SegmentButtonOptions_1({
      type: 'tab',
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
      direction: options.direction,
      borderRadiusMode: options.borderRadiusMode,
      backgroundBorderRadius: options.backgroundBorderRadius,
      itemBorderRadius: options.itemBorderRadius,
      backgroundSystemMaterial: options.backgroundSystemMaterial,
    });
  }
  static capsule(options) {
    return new SegmentButtonOptions_1({
      type: 'capsule',
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
      direction: options.direction,
      borderRadiusMode: options.borderRadiusMode,
      backgroundBorderRadius: options.backgroundBorderRadius,
      itemBorderRadius: options.itemBorderRadius,
      backgroundSystemMaterial: options.backgroundSystemMaterial,
    });
  }
});
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([Observed], SegmentButtonOptions);
export { SegmentButtonOptions };
class MultiSelectBackground extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.__optionsArray = new SynchedPropertyNesedObjectPU(params.optionsArray, this, 'optionsArray');
    this.__options = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.__buttonBorderRadius = this.initializeConsume('buttonBorderRadius', 'buttonBorderRadius');
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
  }
  aboutToBeDeleted() {
    this.__optionsArray.aboutToBeDeleted();
    this.__options.aboutToBeDeleted();
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
  get buttonBorderRadius() {
    return this.__buttonBorderRadius.get();
  }
  set buttonBorderRadius(newValue) {
    this.__buttonBorderRadius.set(newValue);
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
                Stack.height('100%');
                Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                Stack.borderRadius(this.buttonBorderRadius[index]);
                Stack.backgroundBlurStyle(this.options.backgroundBlurStyle, undefined, {
                  disableSystemAdaptation: true,
                });
              }, Stack);
              Stack.pop();
            });
          } else {
            this.ifElseBranchUpdateFunction(1, () => {});
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
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.__optionsArray = new SynchedPropertyNesedObjectPU(params.optionsArray, this, 'optionsArray');
    this.__options = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, 'selectedIndexes');
    this.__zoomScaleArray = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
    this.__buttonBorderRadius = this.initializeConsume('buttonBorderRadius', 'buttonBorderRadius');
    this.__isSegmentFocusStyleCustomized = new SynchedPropertySimpleOneWayPU(
      params.isSegmentFocusStyleCustomized,
      this,
      'isSegmentFocusStyleCustomized'
    );
    this.__openSelectedItemSystemMaterial = this.initializeConsume(
      'openSelectedItemSystemMaterial',
      'openSelectedItemSystemMaterial',
      false
    );
    this.__selectedItemScale = this.initializeConsume('selectedItemScale', 'selectedItemScale');
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
    this.__isSegmentFocusStyleCustomized.reset(params.isSegmentFocusStyleCustomized);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__optionsArray.purgeDependencyOnElmtId(rmElmtId);
    this.__options.purgeDependencyOnElmtId(rmElmtId);
    this.__selectedIndexes.purgeDependencyOnElmtId(rmElmtId);
    this.__zoomScaleArray.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
    this.__isSegmentFocusStyleCustomized.purgeDependencyOnElmtId(rmElmtId);
    this.__openSelectedItemSystemMaterial.purgeDependencyOnElmtId(rmElmtId);
    this.__selectedItemScale.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.__optionsArray.aboutToBeDeleted();
    this.__options.aboutToBeDeleted();
    this.__selectedIndexes.aboutToBeDeleted();
    this.__zoomScaleArray.aboutToBeDeleted();
    this.__buttonBorderRadius.aboutToBeDeleted();
    this.__isSegmentFocusStyleCustomized.aboutToBeDeleted();
    this.__openSelectedItemSystemMaterial.aboutToBeDeleted();
    this.__selectedItemScale.aboutToBeDeleted();
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
  get isSegmentFocusStyleCustomized() {
    return this.__isSegmentFocusStyleCustomized.get();
  }
  set isSegmentFocusStyleCustomized(newValue) {
    this.__isSegmentFocusStyleCustomized.set(newValue);
  }
  get openSelectedItemSystemMaterial() {
    return this.__openSelectedItemSystemMaterial.get();
  }
  set openSelectedItemSystemMaterial(newValue) {
    this.__openSelectedItemSystemMaterial.set(newValue);
  }
  get selectedItemScale() {
    return this.__selectedItemScale.get();
  }
  set selectedItemScale(newValue) {
    this.__selectedItemScale.set(newValue);
  }
  getBackgroundColor() {
    if (this.options.selectedBackgroundColor) {
      return this.options.selectedBackgroundColor;
    }
    if (this.options.type === 'tab') {
      return segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
    } else {
      return segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
    }
  }
  getScale() {
    if (this.openSelectedItemSystemMaterial) {
      return this.selectedItemScale;
    } else {
      return {
        x: this.zoomScaleArray[this.selectedIndexes[0]],
        y: this.zoomScaleArray[this.selectedIndexes[0]],
      };
    }
  }
  getOpacity() {
    if (this.openSelectedItemSystemMaterial) {
      return 0.7;
    } else {
      return 1;
    }
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
            Stack.width('100%');
            Stack.height('100%');
            Stack.backgroundColor(this.getBackgroundColor());
            Stack.scale(this.getScale());
            Stack.opacity(this.getOpacity());
          }, Stack);
          Stack.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
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
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.__optionsArray = new SynchedPropertyNesedObjectPU(params.optionsArray, this, 'optionsArray');
    this.__options = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, 'selectedIndexes');
    this.__zoomScaleArray = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
    this.__buttonBorderRadius = this.initializeConsume('buttonBorderRadius', 'buttonBorderRadius');
    this.__multiColor = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (_, index) => Color.Transparent),
      this,
      'multiColor'
    );
    this.setInitiallyProvidedValue(params);
    this.declareWatch('options', this.onOptionsChange);
    this.declareWatch('selectedIndexes', this.onSelectedChange);
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
    this.__zoomScaleArray.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
    this.__multiColor.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.__optionsArray.aboutToBeDeleted();
    this.__options.aboutToBeDeleted();
    this.__selectedIndexes.aboutToBeDeleted();
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
      this.multiColor[this.selectedIndexes[i]] =
        this.options.selectedBackgroundColor ?? segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
    }
  }
  onSelectedChange() {
    for (let i = 0; i < MAX_ITEM_COUNT; i++) {
      this.multiColor[i] = Color.Transparent;
    }
    for (let i = 0; i < this.selectedIndexes.length; i++) {
      this.multiColor[this.selectedIndexes[i]] =
        this.options.selectedBackgroundColor ?? segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
    }
  }
  aboutToAppear() {
    for (let i = 0; i < this.selectedIndexes.length; i++) {
      this.multiColor[this.selectedIndexes[i]] =
        this.options.selectedBackgroundColor ?? segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
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
                Stack.layoutWeight(1);
                Stack.height('100%');
                Stack.backgroundColor(this.multiColor[index]);
                Stack.borderRadius(this.buttonBorderRadius[index]);
              }, Stack);
              Stack.pop();
            });
          } else {
            this.ifElseBranchUpdateFunction(1, () => {});
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
class SegmentButtonItem extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, 'selectedIndexes');
    this.__focusIndex = new SynchedPropertySimpleTwoWayPU(params.focusIndex, this, 'focusIndex');
    this.__maxFontScale = new SynchedPropertyObjectOneWayPU(params.maxFontScale, this, 'maxFontScale');
    this.__itemOptions = new SynchedPropertyNesedObjectPU(params.itemOptions, this, 'itemOptions');
    this.__options = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.__property = new SynchedPropertyNesedObjectPU(params.property, this, 'property');
    this.__index = new SynchedPropertySimpleOneWayPU(params.index, this, 'index');
    this.__isTextSupportMarquee = new ObservedPropertySimplePU(
      resourceToNumber(this.getUIContext()?.getHostContext(), segmentButtonTheme.SEGMENT_ITEM_TEXT_OVERFLOW, 1.0) ===
        0.0,
      this,
      'isTextSupportMarquee'
    );
    this.__isMarqueeAndFadeout = new SynchedPropertySimpleOneWayPU(
      params.isMarqueeAndFadeout,
      this,
      'isMarqueeAndFadeout'
    );
    this.__isSegmentFocusStyleCustomized = new SynchedPropertySimpleOneWayPU(
      params.isSegmentFocusStyleCustomized,
      this,
      'isSegmentFocusStyleCustomized'
    );
    this.__isTextInMarqueeCondition = new ObservedPropertySimplePU(false, this, 'isTextInMarqueeCondition');
    this.__isButtonTextFadeout = new ObservedPropertySimplePU(false, this, 'isButtonTextFadeout');
    this.__useAdaptiveLineHeight = this.initializeConsume('useAdaptiveLineHeight', 'useAdaptiveLineHeight');
    this.groupId = '';
    this.__hover = new SynchedPropertySimpleOneWayPU(params.hover, this, 'hover');
    this.setInitiallyProvidedValue(params);
    this.declareWatch('focusIndex', this.onFocusIndex);
    this.declareWatch('hover', this.onFocusIndex);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.__itemOptions.set(params.itemOptions);
    this.__options.set(params.options);
    this.__property.set(params.property);
    if (params.isTextSupportMarquee !== undefined) {
      this.isTextSupportMarquee = params.isTextSupportMarquee;
    }
    if (params.isTextInMarqueeCondition !== undefined) {
      this.isTextInMarqueeCondition = params.isTextInMarqueeCondition;
    }
    if (params.isButtonTextFadeout !== undefined) {
      this.isButtonTextFadeout = params.isButtonTextFadeout;
    }
    if (params.groupId !== undefined) {
      this.groupId = params.groupId;
    }
  }
  updateStateVars(params) {
    this.__maxFontScale.reset(params.maxFontScale);
    this.__itemOptions.set(params.itemOptions);
    this.__options.set(params.options);
    this.__property.set(params.property);
    this.__index.reset(params.index);
    this.__isMarqueeAndFadeout.reset(params.isMarqueeAndFadeout);
    this.__isSegmentFocusStyleCustomized.reset(params.isSegmentFocusStyleCustomized);
    this.__hover.reset(params.hover);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__selectedIndexes.purgeDependencyOnElmtId(rmElmtId);
    this.__focusIndex.purgeDependencyOnElmtId(rmElmtId);
    this.__maxFontScale.purgeDependencyOnElmtId(rmElmtId);
    this.__itemOptions.purgeDependencyOnElmtId(rmElmtId);
    this.__options.purgeDependencyOnElmtId(rmElmtId);
    this.__property.purgeDependencyOnElmtId(rmElmtId);
    this.__index.purgeDependencyOnElmtId(rmElmtId);
    this.__isTextSupportMarquee.purgeDependencyOnElmtId(rmElmtId);
    this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(rmElmtId);
    this.__isSegmentFocusStyleCustomized.purgeDependencyOnElmtId(rmElmtId);
    this.__isTextInMarqueeCondition.purgeDependencyOnElmtId(rmElmtId);
    this.__isButtonTextFadeout.purgeDependencyOnElmtId(rmElmtId);
    this.__useAdaptiveLineHeight.purgeDependencyOnElmtId(rmElmtId);
    this.__hover.purgeDependencyOnElmtId(rmElmtId);
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
    this.__useAdaptiveLineHeight.aboutToBeDeleted();
    this.__hover.aboutToBeDeleted();
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
  get maxFontScale() {
    return this.__maxFontScale.get();
  }
  set maxFontScale(newValue) {
    this.__maxFontScale.set(newValue);
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
  get isTextSupportMarquee() {
    return this.__isTextSupportMarquee.get();
  }
  set isTextSupportMarquee(newValue) {
    this.__isTextSupportMarquee.set(newValue);
  }
  get isMarqueeAndFadeout() {
    return this.__isMarqueeAndFadeout.get();
  }
  set isMarqueeAndFadeout(newValue) {
    this.__isMarqueeAndFadeout.set(newValue);
  }
  get isSegmentFocusStyleCustomized() {
    return this.__isSegmentFocusStyleCustomized.get();
  }
  set isSegmentFocusStyleCustomized(newValue) {
    this.__isSegmentFocusStyleCustomized.set(newValue);
  }
  get isTextInMarqueeCondition() {
    return this.__isTextInMarqueeCondition.get();
  }
  set isTextInMarqueeCondition(newValue) {
    this.__isTextInMarqueeCondition.set(newValue);
  }
  get isButtonTextFadeout() {
    return this.__isButtonTextFadeout.get();
  }
  set isButtonTextFadeout(newValue) {
    this.__isButtonTextFadeout.set(newValue);
  }
  get useAdaptiveLineHeight() {
    return this.__useAdaptiveLineHeight.get();
  }
  set useAdaptiveLineHeight(newValue) {
    this.__useAdaptiveLineHeight.set(newValue);
  }
  get hover() {
    return this.__hover.get();
  }
  set hover(newValue) {
    this.__hover.set(newValue);
  }
  getTextPadding() {
    if (this.options.localizedTextPadding) {
      return this.options.localizedTextPadding;
    }
    if (this.options.textPadding !== void 0) {
      return this.options.textPadding;
    }
    return 0;
  }
  getButtonPadding() {
    if (this.options.localizedButtonPadding) {
      return this.options.localizedButtonPadding;
    }
    if (this.options.buttonPadding !== void 0) {
      return this.options.buttonPadding;
    }
    if (this.options.type === 'capsule' && this.options.showText && this.options.showIcon) {
      return {
        top: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING),
        bottom: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING),
        start: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING),
        end: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING),
      };
    }
    return {
      top: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_VERTICAL_PADDING),
      bottom: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_VERTICAL_PADDING),
      start: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING),
      end: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING),
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
      if (this.isDefaultSelectedFontColor() && this.isSegmentFocusStyleCustomized && this.focusIndex === this.index) {
        return segmentButtonTheme.SEGMENT_BUTTON_FOCUS_TEXT_COLOR;
      }
      return this.options.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
    }
    return this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
  }
  getAccessibilityText() {
    if (
      this.selectedIndexes.includes(this.index) &&
      typeof this.itemOptions.selectedIconAccessibilityText !== undefined
    ) {
      return this.itemOptions.selectedIconAccessibilityText;
    } else if (
      !this.selectedIndexes.includes(this.index) &&
      typeof this.itemOptions.iconAccessibilityText !== undefined
    ) {
      return this.itemOptions.iconAccessibilityText;
    }
    return undefined;
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create({ space: 2 });
      Column.direction(this.options.direction);
      Column.justifyContent(FlexAlign.Center);
      Column.padding(this.getButtonPadding());
      Column.constraintSize({ minHeight: segmentButtonTheme.CONSTRAINT_SIZE_MIN_HEIGHT });
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.options.showIcon) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon);
            Image.direction(this.options.direction);
            Image.size(this.options.imageSize ?? { width: 24, height: 24 });
            Image.draggable(false);
            Image.fillColor(this.getFontColor());
            Image.accessibilityText(this.getAccessibilityText());
          }, Image);
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
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
            Text.fontColor(this.getFontColor());
            Text.fontWeight(this.property.fontWeight);
            Text.fontSize(this.property.fontSize);
            Text.minFontSize(this.isSegmentFocusStyleCustomized ? this.property.fontSize : 9);
            Text.maxFontSize(this.property.fontSize);
            Text.maxFontScale(ObservedObject.GetRawObject(this.maxFontScale));
            Text.textOverflow({
              overflow: this.isTextSupportMarquee ? TextOverflow.MARQUEE : TextOverflow.Ellipsis,
            });
            Text.marqueeOptions({
              start: this.isTextInMarqueeCondition,
              fadeout: this.isButtonTextFadeout,
              marqueeStartPolicy: MarqueeStartPolicy.DEFAULT,
            });
            Text.maxLines(1);
            Text.textAlign(TextAlign.Center);
            Text.padding(this.getTextPadding());
            Text.includeFontPadding(this.useAdaptiveLineHeight);
            Text.fallbackLineSpacing(this.useAdaptiveLineHeight);
          }, Text);
          Text.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
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
HoverColorProperty = __decorate([Observed], HoverColorProperty);
class PressAndHoverEffect extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.__buttonItemsSize = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.__press = new SynchedPropertySimpleOneWayPU(params.press, this, 'press');
    this.__hover = new SynchedPropertySimpleOneWayPU(params.hover, this, 'hover');
    this.__colorProperty = new SynchedPropertyNesedObjectPU(params.colorProperty, this, 'colorProperty');
    this.__buttonBorderRadius = this.initializeConsume('buttonBorderRadius', 'buttonBorderRadius');
    this.__options = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
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
    this.__hover.reset(params.hover);
    this.__colorProperty.set(params.colorProperty);
    this.__options.set(params.options);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
    this.__press.purgeDependencyOnElmtId(rmElmtId);
    this.__hover.purgeDependencyOnElmtId(rmElmtId);
    this.__colorProperty.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
    this.__options.purgeDependencyOnElmtId(rmElmtId);
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
  set buttonItemsSize(newValue) {
    this.__buttonItemsSize.set(newValue);
  }
  get press() {
    return this.__press.get();
  }
  set press(newValue) {
    this.__press.set(newValue);
  }
  get hover() {
    return this.__hover.get();
  }
  set hover(newValue) {
    this.__hover.set(newValue);
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
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.__buttons = new SynchedPropertyNesedObjectPU(params.buttons, this, 'buttons');
    this.__options = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.__pressArray = new SynchedPropertyObjectTwoWayPU(params.pressArray, this, 'pressArray');
    this.__hoverArray = new SynchedPropertyObjectTwoWayPU(params.hoverArray, this, 'hoverArray');
    this.__hoverColorArray = new SynchedPropertyObjectTwoWayPU(params.hoverColorArray, this, 'hoverColorArray');
    this.__zoomScaleArray = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.__buttons.set(params.buttons);
    this.__options.set(params.options);
  }
  updateStateVars(params) {
    this.__buttons.set(params.buttons);
    this.__options.set(params.options);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__buttons.purgeDependencyOnElmtId(rmElmtId);
    this.__options.purgeDependencyOnElmtId(rmElmtId);
    this.__pressArray.purgeDependencyOnElmtId(rmElmtId);
    this.__hoverArray.purgeDependencyOnElmtId(rmElmtId);
    this.__hoverColorArray.purgeDependencyOnElmtId(rmElmtId);
    this.__zoomScaleArray.purgeDependencyOnElmtId(rmElmtId);
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
  set pressArray(newValue) {
    this.__pressArray.set(newValue);
  }
  get hoverArray() {
    return this.__hoverArray.get();
  }
  set hoverArray(newValue) {
    this.__hoverArray.set(newValue);
  }
  get hoverColorArray() {
    return this.__hoverColorArray.get();
  }
  set hoverColorArray(newValue) {
    this.__hoverColorArray.set(newValue);
  }
  get zoomScaleArray() {
    return this.__zoomScaleArray.get();
  }
  set zoomScaleArray(newValue) {
    this.__zoomScaleArray.set(newValue);
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create({ space: 1 });
      Row.direction(this.options.direction);
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
                Stack.scale({
                  x:
                    this.options.type === 'capsule' && (this.options.multiply ?? false)
                      ? 1
                      : this.zoomScaleArray[index],
                  y:
                    this.options.type === 'capsule' && (this.options.multiply ?? false)
                      ? 1
                      : this.zoomScaleArray[index],
                });
              }, Stack);
              {
                this.observeComponentCreation2(
                  (elmtId, isInitialRender) => {
                    if (isInitialRender) {
                      let componentCall = new PressAndHoverEffect(
                        this,
                        {
                          pressIndex: index,
                          colorProperty: this.hoverColorArray[index],
                          press: this.pressArray[index],
                          hover: this.hoverArray[index],
                          options: this.options,
                        },
                        undefined,
                        elmtId,
                        () => {},
                        { page: 'library/src/main/ets/components/SegmentButton.ets', line: 807, col: 13 }
                      );
                      ViewPU.create(componentCall);
                      let paramsLambda = () => {
                        return {
                          pressIndex: index,
                          colorProperty: this.hoverColorArray[index],
                          press: this.pressArray[index],
                          hover: this.hoverArray[index],
                          options: this.options,
                        };
                      };
                      componentCall.paramsGenerator_ = paramsLambda;
                    } else {
                      this.updateStateVarsOfChildByElmtId(elmtId, {
                        colorProperty: this.hoverColorArray[index],
                        press: this.pressArray[index],
                        hover: this.hoverArray[index],
                        options: this.options,
                      });
                    }
                  },
                  { name: 'PressAndHoverEffect' }
                );
              }
              Stack.pop();
            });
          } else {
            this.ifElseBranchUpdateFunction(1, () => {});
          }
        }, If);
        If.pop();
      };
      this.forEachUpdateFunction(elmtId, this.buttons, forEachItemGenFunction, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    Row.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class SegmentButtonItemArrayComponent extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.__optionsArray = new SynchedPropertyNesedObjectPU(params.optionsArray, this, 'optionsArray');
    this.__options = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, 'selectedIndexes');
    this.__buttonBorderRadius = this.initializeConsume('buttonBorderRadius', 'buttonBorderRadius');
    this.__buttonItemsSize = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.__positionTrigger = this.initializeConsume('positionTrigger', 'positionTrigger');
    this.__focusIndex = this.initializeConsume('focusIndex', 'focusIndex');
    this.__zoomScaleArray = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
    this.__buttonItemProperty = this.initializeConsume('buttonItemProperty', 'buttonItemProperty');
    this.__buttonItemsSelected = this.initializeConsume('buttonItemsSelected', 'buttonItemsSelected');
    this.__pressArray = new SynchedPropertyObjectTwoWayPU(params.pressArray, this, 'pressArray');
    this.__hoverArray = new SynchedPropertyObjectTwoWayPU(params.hoverArray, this, 'hoverArray');
    this.__hoverColorArray = new SynchedPropertyObjectTwoWayPU(params.hoverColorArray, this, 'hoverColorArray');
    this.__maxFontScale = new SynchedPropertyObjectOneWayPU(params.maxFontScale, this, 'maxFontScale');
    this.__buttonWidth = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (_, index) => 0),
      this,
      'buttonWidth'
    );
    this.__buttonHeight = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (_, index) => 0),
      this,
      'buttonHeight'
    );
    this.__isMarqueeAndFadeout = new ObservedPropertySimplePU(false, this, 'isMarqueeAndFadeout');
    this.buttonItemsRealHeight = Array.from({ length: MAX_ITEM_COUNT }, (_, index) => 0);
    this.groupId = util.generateRandomUUID(true);
    this.onItemClicked = undefined;
    this.__isSegmentFocusStyleCustomized = new SynchedPropertySimpleOneWayPU(
      params.isSegmentFocusStyleCustomized,
      this,
      'isSegmentFocusStyleCustomized'
    );
    this.setInitiallyProvidedValue(params);
    this.declareWatch('optionsArray', this.onOptionsArrayChange);
    this.declareWatch('options', this.onOptionsChange);
    this.declareWatch('buttonItemsSize', this.onButtonItemsSizeChange);
    this.declareWatch('focusIndex', this.onFocusIndex);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.__optionsArray.set(params.optionsArray);
    this.__options.set(params.options);
    if (params.buttonWidth !== undefined) {
      this.buttonWidth = params.buttonWidth;
    }
    if (params.buttonHeight !== undefined) {
      this.buttonHeight = params.buttonHeight;
    }
    if (params.isMarqueeAndFadeout !== undefined) {
      this.isMarqueeAndFadeout = params.isMarqueeAndFadeout;
    }
    if (params.buttonItemsRealHeight !== undefined) {
      this.buttonItemsRealHeight = params.buttonItemsRealHeight;
    }
    if (params.groupId !== undefined) {
      this.groupId = params.groupId;
    }
    if (params.onItemClicked !== undefined) {
      this.onItemClicked = params.onItemClicked;
    }
  }
  updateStateVars(params) {
    this.__optionsArray.set(params.optionsArray);
    this.__options.set(params.options);
    this.__maxFontScale.reset(params.maxFontScale);
    this.__isSegmentFocusStyleCustomized.reset(params.isSegmentFocusStyleCustomized);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__optionsArray.purgeDependencyOnElmtId(rmElmtId);
    this.__options.purgeDependencyOnElmtId(rmElmtId);
    this.__selectedIndexes.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
    this.__positionTrigger.purgeDependencyOnElmtId(rmElmtId);
    this.__focusIndex.purgeDependencyOnElmtId(rmElmtId);
    this.__zoomScaleArray.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonItemProperty.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonItemsSelected.purgeDependencyOnElmtId(rmElmtId);
    this.__pressArray.purgeDependencyOnElmtId(rmElmtId);
    this.__hoverArray.purgeDependencyOnElmtId(rmElmtId);
    this.__hoverColorArray.purgeDependencyOnElmtId(rmElmtId);
    this.__maxFontScale.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonWidth.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonHeight.purgeDependencyOnElmtId(rmElmtId);
    this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(rmElmtId);
    this.__isSegmentFocusStyleCustomized.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.__optionsArray.aboutToBeDeleted();
    this.__options.aboutToBeDeleted();
    this.__selectedIndexes.aboutToBeDeleted();
    this.__buttonBorderRadius.aboutToBeDeleted();
    this.__buttonItemsSize.aboutToBeDeleted();
    this.__positionTrigger.aboutToBeDeleted();
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
  set selectedIndexes(newValue) {
    this.__selectedIndexes.set(newValue);
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
  get positionTrigger() {
    return this.__positionTrigger.get();
  }
  set positionTrigger(newValue) {
    this.__positionTrigger.set(newValue);
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
  get hoverArray() {
    return this.__hoverArray.get();
  }
  set hoverArray(newValue) {
    this.__hoverArray.set(newValue);
  }
  get hoverColorArray() {
    return this.__hoverColorArray.get();
  }
  set hoverColorArray(newValue) {
    this.__hoverColorArray.set(newValue);
  }
  get maxFontScale() {
    return this.__maxFontScale.get();
  }
  set maxFontScale(newValue) {
    this.__maxFontScale.set(newValue);
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
  get isMarqueeAndFadeout() {
    return this.__isMarqueeAndFadeout.get();
  }
  set isMarqueeAndFadeout(newValue) {
    this.__isMarqueeAndFadeout.set(newValue);
  }
  get isSegmentFocusStyleCustomized() {
    return this.__isSegmentFocusStyleCustomized.get();
  }
  set isSegmentFocusStyleCustomized(newValue) {
    this.__isSegmentFocusStyleCustomized.set(newValue);
  }
  onButtonItemsSizeChange() {
    this.buttonItemsSize.forEach((value, index) => {
      this.buttonWidth[index] = value.width;
      this.buttonHeight[index] = value.height;
    });
  }
  changeSelectedIndexes(buttonsLength) {
    if (
      this.optionsArray.changeStartIndex === void 0 ||
      this.optionsArray.deleteCount === void 0 ||
      this.optionsArray.addLength === void 0
    ) {
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
        this.selectedIndexes[0] = this.selectedIndexes[0] - this.optionsArray.deleteCount + this.optionsArray.addLength;
      }
    } else {
      let saveIndexes = this.selectedIndexes;
      for (let i = 0; i < this.optionsArray.deleteCount; i++) {
        let deleteIndex = saveIndexes.indexOf(this.optionsArray.changeStartIndex);
        let indexes = saveIndexes.map(value =>
          this.optionsArray.changeStartIndex && value > this.optionsArray.changeStartIndex ? value - 1 : value
        );
        if (deleteIndex !== -1) {
          indexes.splice(deleteIndex, 1);
        }
        saveIndexes = indexes;
      }
      for (let i = 0; i < this.optionsArray.addLength; i++) {
        let indexes = saveIndexes.map(value =>
          this.optionsArray.changeStartIndex && value >= this.optionsArray.changeStartIndex ? value + 1 : value
        );
        saveIndexes = indexes;
      }
      this.selectedIndexes = saveIndexes;
    }
  }
  changeFocusIndex(buttonsLength) {
    if (
      this.optionsArray.changeStartIndex === void 0 ||
      this.optionsArray.deleteCount === void 0 ||
      this.optionsArray.addLength === void 0
    ) {
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
    let buttonsLength = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
    if (
      this.optionsArray.changeStartIndex !== void 0 &&
      this.optionsArray.deleteCount !== void 0 &&
      this.optionsArray.addLength !== void 0
    ) {
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
  onFocusIndex() {
    this.isMarqueeAndFadeout = this.isSegmentFocusStyleCustomized && !this.isMarqueeAndFadeout;
  }
  aboutToAppear() {
    for (let index = 0; index < this.buttonItemsRealHeight.length; index++) {
      this.buttonItemsRealHeight[index] = 0;
    }
  }
  getFocusItemBorderRadius(index) {
    if (index < 0 || index >= this.buttonBorderRadius.length) {
      return {
        topStart: LengthMetrics.vp(0),
        topEnd: LengthMetrics.vp(0),
        bottomStart: LengthMetrics.vp(0),
        bottomEnd: LengthMetrics.vp(0),
      };
    }
    let focusOffset = 0;
    if (
      this.options.type === 'capsule' &&
      this.focusIndex >= 0 &&
      this.focusIndex < this.buttonItemsSelected.length &&
      this.buttonItemsSelected[this.focusIndex]
    ) {
      focusOffset = CAPSULE_FOCUS_SELECTED_OFFSET;
    }
    let borderRadius = this.buttonBorderRadius[index];
    return {
      topStart: LengthMetrics.vp((borderRadius.topStart?.value ?? 0) + focusOffset),
      topEnd: LengthMetrics.vp((borderRadius.topEnd?.value ?? 0) + focusOffset),
      bottomStart: LengthMetrics.vp((borderRadius.bottomStart?.value ?? 0) + focusOffset),
      bottomEnd: LengthMetrics.vp((borderRadius.bottomEnd?.value ?? 0) + focusOffset),
    };
  }
  getFocusStackSize(index) {
    const isCapsuleAndSelected =
      this.options.type === 'capsule' &&
      this.focusIndex >= 0 &&
      this.focusIndex < this.buttonItemsSelected.length &&
      this.buttonItemsSelected[this.focusIndex];
    return {
      width: isCapsuleAndSelected
        ? this.buttonWidth[index] + CAPSULE_FOCUS_SELECTED_OFFSET * 2
        : this.buttonWidth[index],
      height: isCapsuleAndSelected
        ? this.buttonHeight[index] + CAPSULE_FOCUS_SELECTED_OFFSET * 2
        : this.buttonHeight[index],
    };
  }
  focusStack(index, parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Stack.create();
      Stack.direction(this.options.direction);
      Stack.size({ width: 1, height: 1 });
      Stack.align(Alignment.Center);
      Stack.visibility(
        !this.isSegmentFocusStyleCustomized && this.focusIndex === index ? Visibility.Visible : Visibility.None
      );
    }, Stack);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Stack.create();
      Stack.direction(this.options.direction);
      Stack.borderRadius(this.getFocusItemBorderRadius(index));
      Stack.size(this.getFocusStackSize(index));
      Stack.borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR);
      Stack.borderWidth(2);
    }, Stack);
    Stack.pop();
    Stack.pop();
  }
  calculateBorderRadius() {
    let borderRadiusArray = Array.from(
      {
        length: MAX_ITEM_COUNT,
      },
      _ => {
        return {
          topStart: LengthMetrics.vp(0),
          topEnd: LengthMetrics.vp(0),
          bottomStart: LengthMetrics.vp(0),
          bottomEnd: LengthMetrics.vp(0),
        };
      }
    );
    const isSingleSelect = this.options.type === 'tab' || !(this.options.multiply ?? false);
    const buttonsLength = this.options.buttons
      ? Math.min(this.options.buttons.length, this.buttonItemsSize.length)
      : MIN_ITEM_COUNT;
    const setAllCorners = (array, index, lengthMetrics) => {
      if (!array || index < 0 || index >= array.length) {
        return;
      }
      const safeLengthMetrics = lengthMetrics.value < 0 ? LengthMetrics.vp(0) : lengthMetrics;
      array[index].topStart = safeLengthMetrics;
      array[index].topEnd = safeLengthMetrics;
      array[index].bottomStart = safeLengthMetrics;
      array[index].bottomEnd = safeLengthMetrics;
    };
    const setLeftCorners = (array, index, lengthMetrics) => {
      if (!array || index < 0 || index >= array.length) {
        return;
      }
      const safeLengthMetrics = lengthMetrics.value < 0 ? LengthMetrics.vp(0) : lengthMetrics;
      const zeroLengthMetrics = LengthMetrics.vp(0);
      array[index].topStart = safeLengthMetrics;
      array[index].topEnd = zeroLengthMetrics;
      array[index].bottomStart = safeLengthMetrics;
      array[index].bottomEnd = zeroLengthMetrics;
    };
    const setRightCorners = (array, index, lengthMetrics) => {
      if (!array || index < 0 || index >= array.length) {
        return;
      }
      const safeLengthMetrics = lengthMetrics.value < 0 ? LengthMetrics.vp(0) : lengthMetrics;
      const zeroLengthMetrics = LengthMetrics.vp(0);
      array[index].topStart = zeroLengthMetrics;
      array[index].topEnd = safeLengthMetrics;
      array[index].bottomStart = zeroLengthMetrics;
      array[index].bottomEnd = safeLengthMetrics;
    };
    const setMiddleCorners = (array, index) => {
      if (!array || index < 0 || index >= array.length) {
        return;
      }
      array[index].topStart = LengthMetrics.vp(0);
      array[index].topEnd = LengthMetrics.vp(0);
      array[index].bottomStart = LengthMetrics.vp(0);
      array[index].bottomEnd = LengthMetrics.vp(0);
    };
    for (let index = 0; index < this.buttonBorderRadius.length; index++) {
      let halfButtonItemsSizeHeight = this.buttonItemsSize[index].height / 2;
      let radius = this.options.iconTextRadius ?? halfButtonItemsSizeHeight;
      const isCustomMode =
        this.options.borderRadiusMode === BorderRadiusMode.CUSTOM && this.options.itemBorderRadius !== undefined;
      let radiusLengthMetrics;
      if (isCustomMode && this.options.itemBorderRadius) {
        radiusLengthMetrics = this.options.itemBorderRadius;
      } else {
        radiusLengthMetrics = LengthMetrics.vp(radius);
      }
      if (isSingleSelect) {
        setAllCorners(borderRadiusArray, index, radiusLengthMetrics);
      } else {
        if (index === 0) {
          setLeftCorners(borderRadiusArray, index, radiusLengthMetrics);
        } else if (index === buttonsLength - 1) {
          setRightCorners(borderRadiusArray, index, radiusLengthMetrics);
        } else {
          setMiddleCorners(borderRadiusArray, index);
        }
      }
    }
    this.buttonBorderRadius = borderRadiusArray;
  }
  getAccessibilityDescription(value, index) {
    if (value !== undefined) {
      return value;
    }
    const isSingleSelect = this.options.type === 'tab' || !this.options.multiply;
    if (isSingleSelect && index !== undefined && this.selectedIndexes.includes(index)) {
      return ACCESSIBILITY_SELECTED_DESCRIPTION;
    }
    return ACCESSIBILITY_DEFAULT_DESCRIPTION;
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
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.focusScopeId(this.groupId, true);
            Row.padding(this.options.componentPadding);
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
                      Button.createWithChild();
                      Button.focusScopePriority(
                        this.groupId,
                        Math.min(...this.selectedIndexes) === index ? FocusPriority.PREVIOUS : FocusPriority.AUTO
                      );
                      Button.type(ButtonType.Normal);
                      Button.stateEffect(false);
                      Button.hoverEffect(HoverEffect.None);
                      Button.backgroundColor(Color.Transparent);
                      Button.accessibilityLevel(item.accessibilityLevel);
                      Button.accessibilitySelected(
                        this.options.multiply ? undefined : this.selectedIndexes.includes(index)
                      );
                      Button.accessibilityChecked(
                        this.options.multiply ? this.selectedIndexes.includes(index) : undefined
                      );
                      Button.accessibilityDescription(
                        this.getAccessibilityDescription(item.accessibilityDescription, index)
                      );
                      Button.direction(this.options.direction);
                      Button.borderRadius(this.buttonBorderRadius[index]);
                      Button.scale({
                        x:
                          this.options.type === 'capsule' && (this.options.multiply ?? false)
                            ? 1
                            : this.zoomScaleArray[index],
                        y:
                          this.options.type === 'capsule' && (this.options.multiply ?? false)
                            ? 1
                            : this.zoomScaleArray[index],
                      });
                      Button.layoutWeight(1);
                      Button.padding(0);
                      Button.onSizeChange((_, newValue) => {
                        this.buttonItemsSize[index] = {
                          width: newValue.width,
                          height: this.buttonItemsSize[index].height,
                        };
                        if (newValue.width) {
                          this.positionTrigger = (this.positionTrigger + 1) & 0xfffff;
                        }
                      });
                      Button.overlay(
                        {
                          builder: () => {
                            this.focusStack.call(this, index);
                          },
                        },
                        { align: Alignment.Center }
                      );
                      Button.attributeModifier.bind(this)(
                        this.isSegmentFocusStyleCustomized
                          ? undefined
                          : new FocusStyleButtonModifier(isFocused => {
                              if (!isFocused && this.focusIndex === index) {
                                this.focusIndex = -1;
                                return;
                              }
                              if (isFocused) {
                                this.focusIndex = index;
                              }
                            })
                      );
                      Button.onFocus(() => {
                        this.focusIndex = index;
                        if (this.isSegmentFocusStyleCustomized) {
                          this.customizeSegmentFocusStyle(index);
                        }
                      });
                      Button.onBlur(() => {
                        if (this.focusIndex === index) {
                          this.focusIndex = -1;
                        }
                        this.hoverColorArray[index].hoverColor = Color.Transparent;
                      });
                      globalThis.Gesture.create(GesturePriority.Low);
                      TapGesture.create();
                      TapGesture.onAction(() => {
                        if (this.onItemClicked) {
                          this.onItemClicked(index);
                        }
                        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                          if (this.selectedIndexes.indexOf(index) === -1) {
                            this.selectedIndexes.push(index);
                          } else {
                            this.selectedIndexes.splice(this.selectedIndexes.indexOf(index), 1);
                          }
                        } else {
                          this.selectedIndexes[0] = index;
                        }
                      });
                      TapGesture.pop();
                      globalThis.Gesture.pop();
                      Button.onTouch(event => {
                        if (this.isSegmentFocusStyleCustomized) {
                          this.getUIContext().getFocusController().clearFocus();
                        }
                        if (event.source !== SourceType.TouchScreen) {
                          return;
                        }
                        if (event.type === TouchType.Down) {
                          Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[index] = 0.95;
                          });
                        } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                          Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                            this.zoomScaleArray[index] = 1;
                          });
                        }
                      });
                      Button.onHover(isHover => {
                        this.hoverArray[index] = isHover;
                        if (isHover) {
                          Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                            this.hoverColorArray[index].hoverColor =
                              this.isSegmentFocusStyleCustomized && this.focusIndex === index
                                ? segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR
                                : segmentButtonTheme.HOVER_COLOR;
                          });
                        } else {
                          Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                            this.hoverColorArray[index].hoverColor =
                              this.isSegmentFocusStyleCustomized && this.focusIndex === index
                                ? segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR
                                : Color.Transparent;
                          });
                        }
                      });
                      Button.onMouse(event => {
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
                    }, Button);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                      __Common__.create();
                      __Common__.onSizeChange((_, newValue) => {
                        this.buttonItemsRealHeight[index] = newValue.height;
                        let maxHeight = Math.max(
                          ...this.buttonItemsRealHeight.slice(0, this.options.buttons ? this.options.buttons.length : 0)
                        );
                        for (let index = 0; index < this.buttonItemsSize.length; index++) {
                          this.buttonItemsSize[index] = { width: this.buttonItemsSize[index].width, height: maxHeight };
                        }
                        this.calculateBorderRadius();
                      });
                    }, __Common__);
                    {
                      this.observeComponentCreation2(
                        (elmtId, isInitialRender) => {
                          if (isInitialRender) {
                            let componentCall = new SegmentButtonItem(
                              this,
                              {
                                isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                                isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                                selectedIndexes: this.__selectedIndexes,
                                focusIndex: this.__focusIndex,
                                index: index,
                                itemOptions: item,
                                options: this.options,
                                property: this.buttonItemProperty[index],
                                groupId: this.groupId,
                                maxFontScale: this.maxFontScale,
                                hover: this.hoverArray[index],
                              },
                              undefined,
                              elmtId,
                              () => {},
                              { page: 'library/src/main/ets/components/SegmentButton.ets', line: 1138, col: 15 }
                            );
                            ViewPU.create(componentCall);
                            let paramsLambda = () => {
                              return {
                                isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                                isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                                selectedIndexes: this.selectedIndexes,
                                focusIndex: this.focusIndex,
                                index: index,
                                itemOptions: item,
                                options: this.options,
                                property: this.buttonItemProperty[index],
                                groupId: this.groupId,
                                maxFontScale: this.maxFontScale,
                                hover: this.hoverArray[index],
                              };
                            };
                            componentCall.paramsGenerator_ = paramsLambda;
                          } else {
                            this.updateStateVarsOfChildByElmtId(elmtId, {
                              isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                              isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                              index: index,
                              itemOptions: item,
                              options: this.options,
                              property: this.buttonItemProperty[index],
                              maxFontScale: this.maxFontScale,
                              hover: this.hoverArray[index],
                            });
                          }
                        },
                        { name: 'SegmentButtonItem' }
                      );
                    }
                    __Common__.pop();
                    Button.pop();
                  });
                } else {
                  this.ifElseBranchUpdateFunction(1, () => {});
                }
              }, If);
              If.pop();
            };
            this.forEachUpdateFunction(elmtId, this.optionsArray, forEachItemGenFunction, undefined, true, false);
          }, ForEach);
          ForEach.pop();
          Row.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
      }
    }, If);
    If.pop();
  }
  customizeSegmentFocusStyle(index) {
    if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0 && this.selectedIndexes[0] === index) {
      this.hoverColorArray[index].hoverColor = this.isDefaultSelectedBgColor()
        ? segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR
        : this.options.selectedBackgroundColor;
    } else {
      this.hoverColorArray[index].hoverColor =
        this.options.backgroundColor === segmentButtonTheme.BACKGROUND_COLOR
          ? segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR
          : this.options.backgroundColor;
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
ItemProperty = __decorate([Observed], ItemProperty);
export class SegmentButton extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.__enableStateAnimation = new SynchedPropertySimpleOneWayPU(
      params.enableStateAnimation,
      this,
      'enableStateAnimation'
    );
    this.__options = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, 'selectedIndexes');
    this.onItemClicked = undefined;
    this.__maxFontScale = new SynchedPropertyObjectOneWayPU(params.maxFontScale, this, 'maxFontScale');
    this.__buttonBorderRadius = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: MAX_ITEM_COUNT,
        },
        (_, index) => {
          return {
            topStart: LengthMetrics.vp(0),
            topEnd: LengthMetrics.vp(0),
            bottomStart: LengthMetrics.vp(0),
            bottomEnd: LengthMetrics.vp(0),
          };
        }
      ),
      this,
      'buttonBorderRadius'
    );
    this.addProvidedVar('buttonBorderRadius', this.__buttonBorderRadius, false);
    this.__buttonItemsSize = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (_, index) => {
        return {};
      }),
      this,
      'buttonItemsSize'
    );
    this.addProvidedVar('buttonItemsSize', this.__buttonItemsSize, false);
    this.__positionTrigger = new ObservedPropertySimplePU(0, this, 'positionTrigger');
    this.addProvidedVar('positionTrigger', this.__positionTrigger, false);
    this.__buttonItemsSelected = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (_, index) => false),
      this,
      'buttonItemsSelected'
    );
    this.addProvidedVar('buttonItemsSelected', this.__buttonItemsSelected, false);
    this.__buttonItemProperty = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: MAX_ITEM_COUNT,
        },
        (_, index) => new ItemProperty()
      ),
      this,
      'buttonItemProperty'
    );
    this.addProvidedVar('buttonItemProperty', this.__buttonItemProperty, false);
    this.__focusIndex = new ObservedPropertySimplePU(-1, this, 'focusIndex');
    this.addProvidedVar('focusIndex', this.__focusIndex, false);
    this.__selectedItemOffsetX = new ObservedPropertySimplePU(0, this, 'selectedItemOffsetX');
    this.__zoomScaleArray = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (_, index) => 1.0),
      this,
      'zoomScaleArray'
    );
    this.addProvidedVar('zoomScaleArray', this.__zoomScaleArray, false);
    this.__pressArray = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (_, index) => false),
      this,
      'pressArray'
    );
    this.__hoverArray = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (_, index) => false),
      this,
      'hoverArray'
    );
    this.__hoverColorArray = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: MAX_ITEM_COUNT,
        },
        (_, index) => new HoverColorProperty()
      ),
      this,
      'hoverColorArray'
    );
    this.doSelectedChangeAnimate = false;
    this.isCurrentPositionSelected = false;
    this.isCurrentPositionPressed = false;
    this.panGestureStartPoint = { x: 0, y: 0 };
    this.isPanGestureMoved = false;
    this.__shouldMirror = new ObservedPropertySimplePU(false, this, 'shouldMirror');
    this.isGestureInProgress = false;
    this.swipeHandled = false;
    this.isCustomizedCache = undefined;
    this.__openSelectedItemSystemMaterial = new ObservedPropertySimplePU(false, this, 'openSelectedItemSystemMaterial');
    this.addProvidedVar('openSelectedItemSystemMaterial', this.__openSelectedItemSystemMaterial, false);
    this.__selectedItemScale = new ObservedPropertyObjectPU(undefined, this, 'selectedItemScale');
    this.addProvidedVar('selectedItemScale', this.__selectedItemScale, false);
    this.__useAdaptiveLineHeight = new ObservedPropertySimplePU(false, this, 'useAdaptiveLineHeight');
    this.addProvidedVar('useAdaptiveLineHeight', this.__useAdaptiveLineHeight, false);
    this.environmentCallbackID = undefined;
    this.environmentCallback = {
      onConfigurationUpdated: configuration => {
        this.updateLanguageLineHeight();
        this.layoutAlgorithm.shouldMirror = this.isShouldMirror();
      },
      onMemoryLevel() {},
    };
    this.layoutAlgorithm = new SegmentButtonLayoutAlgorithm();
    this.setInitiallyProvidedValue(params);
    this.declareWatch('options', this.onOptionsChange);
    this.declareWatch('selectedIndexes', this.onSelectedChange);
    this.declareWatch('positionTrigger', this.onItemsPositionChange);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    if (params.enableStateAnimation === undefined) {
      this.__enableStateAnimation.set(false);
    }
    this.__options.set(params.options);
    if (params.onItemClicked !== undefined) {
      this.onItemClicked = params.onItemClicked;
    }
    if (params.maxFontScale === undefined) {
      this.__maxFontScale.set(DEFAULT_MAX_FONT_SCALE);
    }
    if (params.buttonBorderRadius !== undefined) {
      this.buttonBorderRadius = params.buttonBorderRadius;
    }
    if (params.buttonItemsSize !== undefined) {
      this.buttonItemsSize = params.buttonItemsSize;
    }
    if (params.positionTrigger !== undefined) {
      this.positionTrigger = params.positionTrigger;
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
    if (params.selectedItemOffsetX !== undefined) {
      this.selectedItemOffsetX = params.selectedItemOffsetX;
    }
    if (params.zoomScaleArray !== undefined) {
      this.zoomScaleArray = params.zoomScaleArray;
    }
    if (params.pressArray !== undefined) {
      this.pressArray = params.pressArray;
    }
    if (params.hoverArray !== undefined) {
      this.hoverArray = params.hoverArray;
    }
    if (params.hoverColorArray !== undefined) {
      this.hoverColorArray = params.hoverColorArray;
    }
    if (params.doSelectedChangeAnimate !== undefined) {
      this.doSelectedChangeAnimate = params.doSelectedChangeAnimate;
    }
    if (params.isCurrentPositionSelected !== undefined) {
      this.isCurrentPositionSelected = params.isCurrentPositionSelected;
    }
    if (params.isCurrentPositionPressed !== undefined) {
      this.isCurrentPositionPressed = params.isCurrentPositionPressed;
    }
    if (params.panGestureStartPoint !== undefined) {
      this.panGestureStartPoint = params.panGestureStartPoint;
    }
    if (params.isPanGestureMoved !== undefined) {
      this.isPanGestureMoved = params.isPanGestureMoved;
    }
    if (params.shouldMirror !== undefined) {
      this.shouldMirror = params.shouldMirror;
    }
    if (params.isGestureInProgress !== undefined) {
      this.isGestureInProgress = params.isGestureInProgress;
    }
    if (params.swipeHandled !== undefined) {
      this.swipeHandled = params.swipeHandled;
    }
    if (params.isCustomizedCache !== undefined) {
      this.isCustomizedCache = params.isCustomizedCache;
    }
    if (params.openSelectedItemSystemMaterial !== undefined) {
      this.openSelectedItemSystemMaterial = params.openSelectedItemSystemMaterial;
    }
    if (params.selectedItemScale !== undefined) {
      this.selectedItemScale = params.selectedItemScale;
    }
    if (params.useAdaptiveLineHeight !== undefined) {
      this.useAdaptiveLineHeight = params.useAdaptiveLineHeight;
    }
    if (params.environmentCallbackID !== undefined) {
      this.environmentCallbackID = params.environmentCallbackID;
    }
    if (params.environmentCallback !== undefined) {
      this.environmentCallback = params.environmentCallback;
    }
    if (params.layoutAlgorithm !== undefined) {
      this.layoutAlgorithm = params.layoutAlgorithm;
    }
  }
  updateStateVars(params) {
    this.__enableStateAnimation.reset(params.enableStateAnimation);
    this.__options.set(params.options);
    this.__maxFontScale.reset(params.maxFontScale);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__enableStateAnimation.purgeDependencyOnElmtId(rmElmtId);
    this.__options.purgeDependencyOnElmtId(rmElmtId);
    this.__selectedIndexes.purgeDependencyOnElmtId(rmElmtId);
    this.__maxFontScale.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
    this.__positionTrigger.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonItemsSelected.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonItemProperty.purgeDependencyOnElmtId(rmElmtId);
    this.__focusIndex.purgeDependencyOnElmtId(rmElmtId);
    this.__selectedItemOffsetX.purgeDependencyOnElmtId(rmElmtId);
    this.__zoomScaleArray.purgeDependencyOnElmtId(rmElmtId);
    this.__pressArray.purgeDependencyOnElmtId(rmElmtId);
    this.__hoverArray.purgeDependencyOnElmtId(rmElmtId);
    this.__hoverColorArray.purgeDependencyOnElmtId(rmElmtId);
    this.__shouldMirror.purgeDependencyOnElmtId(rmElmtId);
    this.__openSelectedItemSystemMaterial.purgeDependencyOnElmtId(rmElmtId);
    this.__selectedItemScale.purgeDependencyOnElmtId(rmElmtId);
    this.__useAdaptiveLineHeight.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.__enableStateAnimation.aboutToBeDeleted();
    this.__options.aboutToBeDeleted();
    this.__selectedIndexes.aboutToBeDeleted();
    this.__maxFontScale.aboutToBeDeleted();
    this.__buttonBorderRadius.aboutToBeDeleted();
    this.__buttonItemsSize.aboutToBeDeleted();
    this.__positionTrigger.aboutToBeDeleted();
    this.__buttonItemsSelected.aboutToBeDeleted();
    this.__buttonItemProperty.aboutToBeDeleted();
    this.__focusIndex.aboutToBeDeleted();
    this.__selectedItemOffsetX.aboutToBeDeleted();
    this.__zoomScaleArray.aboutToBeDeleted();
    this.__pressArray.aboutToBeDeleted();
    this.__hoverArray.aboutToBeDeleted();
    this.__hoverColorArray.aboutToBeDeleted();
    this.__shouldMirror.aboutToBeDeleted();
    this.__openSelectedItemSystemMaterial.aboutToBeDeleted();
    this.__selectedItemScale.aboutToBeDeleted();
    this.__useAdaptiveLineHeight.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get enableStateAnimation() {
    return this.__enableStateAnimation.get();
  }
  set enableStateAnimation(newValue) {
    this.__enableStateAnimation.set(newValue);
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
  get maxFontScale() {
    return this.__maxFontScale.get();
  }
  set maxFontScale(newValue) {
    this.__maxFontScale.set(newValue);
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
  get positionTrigger() {
    return this.__positionTrigger.get();
  }
  set positionTrigger(newValue) {
    this.__positionTrigger.set(newValue);
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
  get selectedItemOffsetX() {
    return this.__selectedItemOffsetX.get();
  }
  set selectedItemOffsetX(newValue) {
    this.__selectedItemOffsetX.set(newValue);
  }
  get zoomScaleArray() {
    return this.__zoomScaleArray.get();
  }
  set zoomScaleArray(newValue) {
    this.__zoomScaleArray.set(newValue);
  }
  get pressArray() {
    return this.__pressArray.get();
  }
  set pressArray(newValue) {
    this.__pressArray.set(newValue);
  }
  get hoverArray() {
    return this.__hoverArray.get();
  }
  set hoverArray(newValue) {
    this.__hoverArray.set(newValue);
  }
  get hoverColorArray() {
    return this.__hoverColorArray.get();
  }
  set hoverColorArray(newValue) {
    this.__hoverColorArray.set(newValue);
  }
  get shouldMirror() {
    return this.__shouldMirror.get();
  }
  set shouldMirror(newValue) {
    this.__shouldMirror.set(newValue);
  }
  get openSelectedItemSystemMaterial() {
    return this.__openSelectedItemSystemMaterial.get();
  }
  set openSelectedItemSystemMaterial(newValue) {
    this.__openSelectedItemSystemMaterial.set(newValue);
  }
  get selectedItemScale() {
    return this.__selectedItemScale.get();
  }
  set selectedItemScale(newValue) {
    this.__selectedItemScale.set(newValue);
  }
  get useAdaptiveLineHeight() {
    return this.__useAdaptiveLineHeight.get();
  }
  set useAdaptiveLineHeight(newValue) {
    this.__useAdaptiveLineHeight.set(newValue);
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
    this.buttonItemsSelected.forEach((_, index) => {
      this.buttonItemsSelected[index] = false;
    });
    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
      this.selectedIndexes.forEach(index => (this.buttonItemsSelected[index] = true));
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
    let invalid = this.selectedIndexes.some(index => {
      return index === void 0 || index < 0 || (this.options.buttons && index >= this.options.buttons.length);
    });
    if (invalid) {
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
    this.layoutAlgorithm.componentPadding = this.getUIContext().vp2px(
      Number.parseFloat(this.options.componentPadding.toString())
    );
    this.layoutAlgorithm.rowSpace = this.getUIContext().vp2px(1);
    this.layoutAlgorithm.selectedIndex = this.selectedIndexes.length > 0 ? this.selectedIndexes[0] : -1;
    this.layoutAlgorithm.multiply = this.options.type === 'capsule' && (this.options.multiply ?? false);
    this.layoutAlgorithm.shouldMirror = this.shouldMirror;
    this.updateAnimatedProperty(null);
    if (this.environmentCallbackID === undefined && deviceInfo.sdkApiVersion >= 26) {
      let abilityContext = this.getUIContext().getHostContext();
      if (abilityContext) {
        this.environmentCallbackID = abilityContext.getApplicationContext().on('environment', this.environmentCallback);
      }
    }
  }
  onSelectedChange() {
    if (this.options === void 0 || this.options.buttons === void 0) {
      return;
    }
    this.updateSelectedIndexes();
    this.setItemsSelected();
    const oldIndex = this.layoutAlgorithm.selectedIndex;
    const newIndex = this.selectedIndexes.length > 0 ? this.selectedIndexes[0] : -1;
    if (oldIndex >= 0 && newIndex >= 0 && oldIndex !== newIndex && this.layoutAlgorithm.buttonWidth > 0) {
      const deltaX = this.layoutAlgorithm.getButtonX(oldIndex) - this.layoutAlgorithm.getButtonX(newIndex);
      this.selectedItemOffsetX = this.getUIContext().px2vp(deltaX);
    }
    this.layoutAlgorithm.selectedIndex = newIndex;
    if (this.doSelectedChangeAnimate || this.enableStateAnimation) {
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
    if (deviceInfo.sdkApiVersion >= 26) {
      this.updateLanguageLineHeight();
      let abilityContext = this.getUIContext().getHostContext();
      if (abilityContext) {
        this.environmentCallbackID = abilityContext.getApplicationContext().on('environment', this.environmentCallback);
      }
    }
  }
  aboutToDisappear() {
    if (deviceInfo.sdkApiVersion >= 26 && this.environmentCallbackID) {
      let abilityContext = this.getUIContext().getHostContext();
      if (abilityContext) {
        abilityContext.getApplicationContext().off('environment', this.environmentCallbackID);
      }
      this.environmentCallbackID = void 0;
    }
  }
  updateLanguageLineHeight() {
    const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resourceManager) {
      console.error(`[SegmentButton] failed to get resourceManager`);
      return;
    }
    try {
      this.useAdaptiveLineHeight = resourceManager.getStringByNameSync('text_fallback_line_spacing') === 'true';
    } catch (e) {
      console.error(`[SegmentButton] failed to get text_fallback_line_spacing resource`);
    }
  }
  isMouseWheelScroll(event) {
    return event.source === SourceType.Mouse && !this.isPanGestureMoved;
  }
  isMovedFromPanGestureStartPoint(x, y) {
    return !nearEqual(x, this.panGestureStartPoint.x) || !nearEqual(y, this.panGestureStartPoint.y);
  }
  isShouldMirror() {
    if (this.options.direction === Direction.Rtl) {
      return true;
    } else if (this.options.direction === Direction.Ltr) {
      return false;
    }
    try {
      let appPreferredLanguage = I18n.System.getAppPreferredLanguage();
      if (I18n.isRTL(appPreferredLanguage)) {
        return true;
      }
    } catch (error) {
      console.error(`Ace SegmentButton getSystemLanguage, error: ${error.toString()}`);
    }
    return false;
  }
  isMultiplyCapsule() {
    return this.options !== undefined && this.options.type === 'capsule' && (this.options.multiply ?? false);
  }
  shouldShowBackground() {
    return !this.isMultiplyCapsule() && this.isBackgroundSystemMaterialEnabled();
  }
  getButtonBackgroundColor() {
    if (!this.shouldShowBackground()) {
      return undefined;
    }
    return this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
  }
  getButtonBorderRadius() {
    if (!this.shouldShowBackground()) {
      return undefined;
    }
    return getBackgroundBorderRadius(this.options, this.layoutAlgorithm.refSize.height / 2);
  }
  getButtonSystemMaterial() {
    if (!this.shouldShowBackground()) {
      return undefined;
    }
    if (this.layoutAlgorithm.refSize.height === 0) {
      return undefined;
    }
    return this.options.backgroundSystemMaterial;
  }
  isSegmentFocusStyleCustomized() {
    if (this.isCustomizedCache === undefined) {
      this.isCustomizedCache =
        resourceToNumber(
          this.getUIContext()?.getHostContext(),
          segmentButtonTheme.SEGMENT_FOCUS_STYLE_CUSTOMIZED,
          1.0
        ) < 0.1;
    }
    return this.isCustomizedCache;
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Stack.create();
      Stack.direction(this.options ? this.options.direction : undefined);
      Stack.backgroundColor(this.getButtonBackgroundColor());
      Stack.borderRadius(this.getButtonBorderRadius());
      Stack.clip(false);
      Stack.systemMaterial(this.getButtonSystemMaterial());
      Stack.onBlur(() => {
        this.focusIndex = -1;
      });
      Stack.onKeyEvent(event => {
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (event.type === KeyType.Down) {
          if (
            event.keyCode === KeyCode.KEYCODE_SPACE ||
            event.keyCode === KeyCode.KEYCODE_ENTER ||
            event.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER
          ) {
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
      globalThis.Gesture.create(GesturePriority.High);
      GestureGroup.create(GestureMode.Parallel);
      TapGesture.create();
      TapGesture.onAction(event => {
        if (this.isGestureInProgress || this.isPanGestureMoved) {
          return;
        }
        let fingerInfo = event.fingerList.find(Boolean);
        if (fingerInfo === void 0) {
          return;
        }
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        let selectedInfo = fingerInfo.localX;
        let buttonLength = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        for (let i = 0; i < buttonLength; i++) {
          selectedInfo = selectedInfo - this.buttonItemsSize[i].width;
          if (selectedInfo >= 0) {
            continue;
          }
          this.doSelectedChangeAnimate =
            this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ? false : true;
          let realClickIndex = this.isShouldMirror() ? buttonLength - 1 - i : i;
          if (this.onItemClicked) {
            this.onItemClicked(realClickIndex);
          }
          if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            let selectedIndex = this.selectedIndexes.indexOf(realClickIndex);
            if (selectedIndex === -1) {
              this.selectedIndexes.push(realClickIndex);
            } else {
              this.selectedIndexes.splice(selectedIndex, 1);
            }
          } else {
            this.selectedIndexes[0] = realClickIndex;
          }
          this.doSelectedChangeAnimate = false;
          break;
        }
      });
      TapGesture.pop();
      SwipeGesture.create();
      SwipeGesture.onAction(event => {
        if (this.swipeHandled) {
          return;
        }
        if (this.options === void 0 || this.options.buttons === void 0 || event.sourceTool === SourceTool.TOUCHPAD) {
          return;
        }
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
          return;
        }
        if (this.isCurrentPositionSelected) {
          return;
        }
        let isHorizontalSwipe = Math.abs(event.angle) <= 45 || Math.abs(event.angle) >= 135;
        if (!isHorizontalSwipe) {
          return;
        }
        let isSwipeRight = Math.abs(event.angle) <= 45;
        let isSwipeLeft = Math.abs(event.angle) >= 135;
        let isSwipeToNext = this.isShouldMirror() ? isSwipeLeft : isSwipeRight;
        let isSwipeToPrevious = this.isShouldMirror() ? isSwipeRight : isSwipeLeft;
        if (
          isSwipeToNext &&
          this.selectedIndexes[0] !== Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1
        ) {
          this.swipeHandled = true;
          this.doSelectedChangeAnimate = true;
          this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
          this.doSelectedChangeAnimate = false;
        } else if (isSwipeToPrevious && this.selectedIndexes[0] !== 0) {
          this.swipeHandled = true;
          this.doSelectedChangeAnimate = true;
          this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
          this.doSelectedChangeAnimate = false;
        }
      });
      SwipeGesture.pop();
      LongPressGesture.create({ repeat: false, duration: 200 });
      LongPressGesture.onAction(event => {
        if (!this.isBackgroundSystemMaterialEnabled()) {
          return;
        }
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
          return;
        }
        let fingerInfo = event.fingerList.find(Boolean);
        if (fingerInfo === void 0) {
          return;
        }
        let selectedInfo = fingerInfo.localX;
        let buttonLength = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        for (let i = 0; i < buttonLength; i++) {
          selectedInfo = selectedInfo - this.buttonItemsSize[i].width;
          if (selectedInfo < 0) {
            let realIndex = this.isShouldMirror() ? buttonLength - 1 - i : i;
            this.isCurrentPositionPressed = realIndex === this.selectedIndexes[0] ? true : false;
            break;
          }
        }
        if (this.isCurrentPositionPressed && !this.openSelectedItemSystemMaterial) {
          this.startSelectMaterialAnimation();
        }
      });
      LongPressGesture.onActionCancel(event => {
        if (!this.isBackgroundSystemMaterialEnabled()) {
          return;
        }
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
          return;
        }
        if (this.isCurrentPositionPressed && this.openSelectedItemSystemMaterial) {
          this.finishSelectMaterialAnimation();
        }
        this.isCurrentPositionPressed = false;
      });
      LongPressGesture.onActionEnd(event => {
        if (!this.isBackgroundSystemMaterialEnabled()) {
          return;
        }
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
          return;
        }
        if (this.isCurrentPositionPressed && this.openSelectedItemSystemMaterial) {
          this.finishSelectMaterialAnimation();
        }
        this.isCurrentPositionPressed = false;
      });
      LongPressGesture.pop();
      PanGesture.create({ direction: PanDirection.Horizontal });
      PanGesture.onActionStart(event => {
        this.isGestureInProgress = true;
        this.swipeHandled = false;
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
          return;
        }
        let fingerInfo = event.fingerList.find(Boolean);
        if (fingerInfo === void 0) {
          return;
        }
        let selectedInfo = fingerInfo.localX;
        this.panGestureStartPoint = { x: fingerInfo.globalX, y: fingerInfo.globalY };
        this.isPanGestureMoved = false;
        let buttonLength = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        for (let i = 0; i < buttonLength; i++) {
          selectedInfo = selectedInfo - this.buttonItemsSize[i].width;
          if (selectedInfo < 0) {
            let realIndex = this.isShouldMirror() ? buttonLength - 1 - i : i;
            this.isCurrentPositionSelected = realIndex === this.selectedIndexes[0] ? true : false;
            break;
          }
        }
        if (this.isBackgroundSystemMaterialEnabled() && this.isCurrentPositionSelected) {
          this.getUIContext().animateTo(
            {
              curve: curves.interpolatingSpring(0, 1, 195, 14),
            },
            () => {
              this.selectedItemScale = { x: 1.01, y: 0.99 };
            }
          );
        }
      });
      PanGesture.onActionUpdate(event => {
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
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
        if (this.isBackgroundSystemMaterialEnabled()) {
          const alg = this.layoutAlgorithm;
          let buttonLength = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
          const startX = Math.min(alg.getButtonX(0), alg.getButtonX(buttonLength - 1));
          const endX = Math.max(alg.getButtonX(0), alg.getButtonX(buttonLength - 1));
          const fingerOffset = this.getUIContext().vp2px(fingerInfo.globalX - this.panGestureStartPoint.x);
          const currentButtonX = alg.getButtonX(this.selectedIndexes[0]);
          let nowX = fingerOffset + currentButtonX;
          nowX = Math.max(startX, nowX);
          nowX = Math.min(endX, nowX);
          this.selectedItemOffsetX = this.getUIContext().px2vp(nowX - currentButtonX);
        } else {
          let buttonLength = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
          for (let i = 0; i < buttonLength; i++) {
            selectedInfo = selectedInfo - this.buttonItemsSize[i].width;
            if (selectedInfo < 0) {
              let realIndex = this.isShouldMirror() ? buttonLength - 1 - i : i;
              this.doSelectedChangeAnimate = true;
              this.selectedIndexes[0] = realIndex;
              this.doSelectedChangeAnimate = false;
              break;
            }
          }
          this.zoomScaleArray.forEach((_, index) => {
            if (index === this.selectedIndexes[0]) {
              Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                this.zoomScaleArray[index] = 0.95;
              });
            } else {
              Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                this.zoomScaleArray[index] = 1;
              });
            }
          });
        }
      });
      PanGesture.onActionEnd(event => {
        this.isGestureInProgress = false;
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
          return;
        }
        let fingerInfo = event.fingerList.find(Boolean);
        if (fingerInfo === void 0) {
          return;
        }
        if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(fingerInfo.globalX, fingerInfo.globalY)) {
          this.isPanGestureMoved = true;
        }
        if (!this.isCurrentPositionSelected) {
          if (this.swipeHandled) {
            Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
              this.zoomScaleArray[this.selectedIndexes[0]] = 1;
            });
            this.isCurrentPositionSelected = false;
            return;
          }
          this.swipeHandled = true;
          if (this.isMouseWheelScroll(event)) {
            let offset = event.offsetX !== 0 ? event.offsetX : event.offsetY;
            this.doSelectedChangeAnimate = true;
            let shouldMoveNext = this.isShouldMirror() ? offset > 0 : offset < 0;
            let shouldMovePrevious = this.isShouldMirror() ? offset < 0 : offset > 0;
            if (shouldMovePrevious && this.selectedIndexes[0] > 0) {
              this.selectedIndexes[0] -= 1;
            } else if (
              shouldMoveNext &&
              this.selectedIndexes[0] < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1
            ) {
              this.selectedIndexes[0] += 1;
            }
            this.doSelectedChangeAnimate = false;
          } else {
            let deltaIndex = fingerInfo.globalX - this.panGestureStartPoint.x < 0 ? -1 : 1;
            if (this.isShouldMirror()) {
              deltaIndex = -deltaIndex;
            }
            let newIndex = this.selectedIndexes[0] + deltaIndex;
            let buttonLength = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
            if (newIndex >= 0 && newIndex < buttonLength) {
              this.doSelectedChangeAnimate = true;
              this.selectedIndexes[0] = newIndex;
              this.doSelectedChangeAnimate = false;
            }
          }
          Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
            this.zoomScaleArray[this.selectedIndexes[0]] = 1;
          });
          this.isCurrentPositionSelected = false;
          return;
        }
        if (this.isBackgroundSystemMaterialEnabled()) {
          let selectedInfo = fingerInfo.localX;
          let buttonLength = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
          let realIndex = -1;
          for (let i = 0; i < buttonLength; i++) {
            selectedInfo = selectedInfo - this.buttonItemsSize[i].width;
            if (selectedInfo < 0) {
              realIndex = this.isShouldMirror() ? buttonLength - 1 - i : i;
              break;
            }
          }
          if (realIndex === -1) {
            realIndex = this.isShouldMirror() ? 0 : buttonLength - 1;
          }
          this.getUIContext().animateTo({ curve: this.getSelectedChangeCurve() }, () => {
            this.selectedIndexes[0] = realIndex;
            this.selectedItemOffsetX = 0;
          });
          this.finishSelectMaterialAnimation();
        } else {
          if (this.isMouseWheelScroll(event)) {
            let offset = event.offsetX !== 0 ? event.offsetX : event.offsetY;
            this.doSelectedChangeAnimate = true;
            let shouldMoveNext = this.isShouldMirror() ? offset > 0 : offset < 0;
            let shouldMovePrevious = this.isShouldMirror() ? offset < 0 : offset > 0;
            if (shouldMovePrevious && this.selectedIndexes[0] > 0) {
              this.selectedIndexes[0] -= 1;
            } else if (
              shouldMoveNext &&
              this.selectedIndexes[0] < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1
            ) {
              this.selectedIndexes[0] += 1;
            }
            this.doSelectedChangeAnimate = false;
          }
          Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
            this.zoomScaleArray[this.selectedIndexes[0]] = 1;
          });
        }
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
        if (this.isBackgroundSystemMaterialEnabled()) {
          this.finishSelectMaterialAnimation();
        }
      });
      PanGesture.pop();
      GestureGroup.pop();
      globalThis.Gesture.pop();
    }, Stack);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.options !== void 0 && this.options.buttons != void 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            DynamicLayout.create(this.layoutAlgorithm);
          }, DynamicLayout);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              this.ifElseBranchUpdateFunction(0, () => {
                {
                  this.observeComponentCreation2(
                    (elmtId, isInitialRender) => {
                      if (isInitialRender) {
                        let componentCall = new MultiSelectBackground(
                          this,
                          {
                            optionsArray: this.options.buttons,
                            options: this.options,
                          },
                          undefined,
                          elmtId,
                          () => {},
                          { page: 'library/src/main/ets/components/SegmentButton.ets', line: 1587, col: 13 }
                        );
                        ViewPU.create(componentCall);
                        let paramsLambda = () => {
                          return {
                            optionsArray: this.options.buttons,
                            options: this.options,
                          };
                        };
                        componentCall.paramsGenerator_ = paramsLambda;
                      } else {
                        this.updateStateVarsOfChildByElmtId(elmtId, {
                          optionsArray: this.options.buttons,
                          options: this.options,
                        });
                      }
                    },
                    { name: 'MultiSelectBackground' }
                  );
                }
              });
            } else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  Stack.create();
                  Stack.direction(this.options.direction);
                  Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                  Stack.borderRadius(getBackgroundBorderRadius(this.options, this.layoutAlgorithm.refSize.height / 2));
                  Stack.backgroundBlurStyle(this.options.backgroundBlurStyle, undefined, {
                    disableSystemAdaptation: true,
                  });
                  Stack.borderWidth(
                    this.options.backgroundSystemMaterial ? undefined : segmentButtonTheme.SEGMENT_BUTTON_BORDER_WIDTH
                  );
                  Stack.borderColor(
                    this.options.backgroundSystemMaterial ? undefined : segmentButtonTheme.SEGMENT_BUTTON_BORDER_COLOR
                  );
                  Stack.systemMaterial(this.options.backgroundSystemMaterial);
                  Stack.visibility(this.layoutAlgorithm.refSize.height > 0 ? Visibility.Visible : Visibility.None);
                }, Stack);
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  If.create();
                  if (this.options.buttons !== void 0 && this.options.buttons.length > 1) {
                    this.ifElseBranchUpdateFunction(0, () => {
                      {
                        this.observeComponentCreation2(
                          (elmtId, isInitialRender) => {
                            if (isInitialRender) {
                              let componentCall = new PressAndHoverEffectArray(
                                this,
                                {
                                  options: this.options,
                                  buttons: this.options.buttons,
                                  pressArray: this.__pressArray,
                                  hoverArray: this.__hoverArray,
                                  hoverColorArray: this.__hoverColorArray,
                                },
                                undefined,
                                elmtId,
                                () => {},
                                { page: 'library/src/main/ets/components/SegmentButton.ets', line: 1594, col: 17 }
                              );
                              ViewPU.create(componentCall);
                              let paramsLambda = () => {
                                return {
                                  options: this.options,
                                  buttons: this.options.buttons,
                                  pressArray: this.pressArray,
                                  hoverArray: this.hoverArray,
                                  hoverColorArray: this.hoverColorArray,
                                };
                              };
                              componentCall.paramsGenerator_ = paramsLambda;
                            } else {
                              this.updateStateVarsOfChildByElmtId(elmtId, {
                                options: this.options,
                                buttons: this.options.buttons,
                              });
                            }
                          },
                          { name: 'PressAndHoverEffectArray' }
                        );
                      }
                    });
                  } else {
                    this.ifElseBranchUpdateFunction(1, () => {});
                  }
                }, If);
                If.pop();
                Stack.pop();
              });
            }
          }, If);
          If.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            globalThis.Context.animation({ duration: 0 });
            Stack.direction(this.options.direction);
            globalThis.Context.animation(null);
            Stack.borderRadius(getBackgroundBorderRadius(this.options, this.layoutAlgorithm.refSize.height / 2));
            Stack.translate({ x: this.selectedItemOffsetX });
            Stack.visibility(this.layoutAlgorithm.refSize.height > 0 ? Visibility.Visible : Visibility.None);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              this.ifElseBranchUpdateFunction(0, () => {
                {
                  this.observeComponentCreation2(
                    (elmtId, isInitialRender) => {
                      if (isInitialRender) {
                        let componentCall = new MultiSelectItemArray(
                          this,
                          {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.__selectedIndexes,
                          },
                          undefined,
                          elmtId,
                          () => {},
                          { page: 'library/src/main/ets/components/SegmentButton.ets', line: 1619, col: 15 }
                        );
                        ViewPU.create(componentCall);
                        let paramsLambda = () => {
                          return {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.selectedIndexes,
                          };
                        };
                        componentCall.paramsGenerator_ = paramsLambda;
                      } else {
                        this.updateStateVarsOfChildByElmtId(elmtId, {
                          optionsArray: this.options.buttons,
                          options: this.options,
                        });
                      }
                    },
                    { name: 'MultiSelectItemArray' }
                  );
                }
              });
            } else {
              this.ifElseBranchUpdateFunction(1, () => {
                {
                  this.observeComponentCreation2(
                    (elmtId, isInitialRender) => {
                      if (isInitialRender) {
                        let componentCall = new SelectItem(
                          this,
                          {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.__selectedIndexes,
                            isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized(),
                          },
                          undefined,
                          elmtId,
                          () => {},
                          { page: 'library/src/main/ets/components/SegmentButton.ets', line: 1625, col: 15 }
                        );
                        ViewPU.create(componentCall);
                        let paramsLambda = () => {
                          return {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.selectedIndexes,
                            isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized(),
                          };
                        };
                        componentCall.paramsGenerator_ = paramsLambda;
                      } else {
                        this.updateStateVarsOfChildByElmtId(elmtId, {
                          optionsArray: this.options.buttons,
                          options: this.options,
                          isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized(),
                        });
                      }
                    },
                    { name: 'SelectItem' }
                  );
                }
              });
            }
          }, If);
          If.pop();
          Stack.pop();
          {
            this.observeComponentCreation2(
              (elmtId, isInitialRender) => {
                if (isInitialRender) {
                  let componentCall = new SegmentButtonItemArrayComponent(
                    this,
                    {
                      pressArray: this.__pressArray,
                      hoverArray: this.__hoverArray,
                      hoverColorArray: this.__hoverColorArray,
                      optionsArray: this.options.buttons,
                      options: this.options,
                      selectedIndexes: this.__selectedIndexes,
                      maxFontScale: this.getMaxFontSize(),
                      onItemClicked: this.onItemClicked,
                      isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized(),
                    },
                    undefined,
                    elmtId,
                    () => {},
                    { page: 'library/src/main/ets/components/SegmentButton.ets', line: 1642, col: 11 }
                  );
                  ViewPU.create(componentCall);
                  let paramsLambda = () => {
                    return {
                      pressArray: this.pressArray,
                      hoverArray: this.hoverArray,
                      hoverColorArray: this.hoverColorArray,
                      optionsArray: this.options.buttons,
                      options: this.options,
                      selectedIndexes: this.selectedIndexes,
                      maxFontScale: this.getMaxFontSize(),
                      onItemClicked: this.onItemClicked,
                      isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized(),
                    };
                  };
                  componentCall.paramsGenerator_ = paramsLambda;
                } else {
                  this.updateStateVarsOfChildByElmtId(elmtId, {
                    optionsArray: this.options.buttons,
                    options: this.options,
                    maxFontScale: this.getMaxFontSize(),
                    isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized(),
                  });
                }
              },
              { name: 'SegmentButtonItemArrayComponent' }
            );
          }
          DynamicLayout.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
      }
    }, If);
    If.pop();
    Stack.pop();
  }
  isBackgroundSystemMaterialEnabled() {
    return this.options !== undefined && this.options.backgroundSystemMaterial !== undefined;
  }
  startSelectMaterialAnimation() {
    if (!this.openSelectedItemSystemMaterial) {
      this.getUIContext().animateTo(
        {
          curve: curves.interpolatingSpring(0, 1, 195, 14),
        },
        () => {
          this.selectedItemScale = { x: 1.05, y: 1.18 };
          this.openSelectedItemSystemMaterial = true;
        }
      );
    }
  }
  finishSelectMaterialAnimation() {
    if (this.openSelectedItemSystemMaterial) {
      this.getUIContext().animateTo({ curve: curves.interpolatingSpring(0, 1, 195, 14) }, () => {
        this.selectedItemScale = { x: 1.05, y: 1.18 };
      });
      this.getUIContext().animateTo(
        {
          curve: curves.interpolatingSpring(0, 1, 195, 14),
          delay: 300,
          onFinish: () => {},
        },
        () => {
          this.openSelectedItemSystemMaterial = false;
          this.selectedItemScale = undefined;
        }
      );
    }
  }
  getMaxFontSize() {
    if (typeof this.maxFontScale === void 0) {
      return DEFAULT_MAX_FONT_SCALE;
    }
    if (typeof this.maxFontScale === 'number') {
      return Math.max(Math.min(this.maxFontScale, MAX_MAX_FONT_SCALE), MIN_MAX_FONT_SCALE);
    }
    const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resourceManager) {
      return DEFAULT_MAX_FONT_SCALE;
    }
    try {
      return resourceManager.getNumber(this.maxFontScale.id);
    } catch (error) {
      console.error(`Ace SegmentButton getMaxFontSize, error: ${error.toString()}`);
      return DEFAULT_MAX_FONT_SCALE;
    }
  }
  getSelectedChangeCurve() {
    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
      return null;
    }
    return curves.springMotion(0.347, 0.99);
  }
  updateAnimatedProperty(curve) {
    let setAnimatedPropertyFunc = () => {
      this.selectedItemOffsetX = 0;
      this.buttonItemsSelected.forEach((selected, index) => {
        this.buttonItemProperty[index].fontColor = selected
          ? (this.options.selectedFontColor ??
            (this.options.type === 'tab'
              ? segmentButtonTheme.TAB_SELECTED_FONT_COLOR
              : segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR))
          : (this.options.fontColor ?? segmentButtonTheme.FONT_COLOR);
      });
    };
    if (curve) {
      if (this.options.backgroundSystemMaterial) {
        this.getUIContext().animateTo(
          {
            curve: curves.interpolatingSpring(0, 1, 195, 14),
          },
          () => {
            this.selectedItemScale = { x: 1.01, y: 0.99 };
            this.openSelectedItemSystemMaterial = true;
          }
        );
        this.getUIContext().animateTo({ curve: curve }, setAnimatedPropertyFunc);
        this.getUIContext().animateTo(
          {
            curve: curves.interpolatingSpring(0, 1, 195, 14),
            delay: 200,
          },
          () => {
            this.openSelectedItemSystemMaterial = false;
          }
        );
      } else {
        this.getUIContext().animateTo({ curve: curve }, setAnimatedPropertyFunc);
      }
    } else {
      setAnimatedPropertyFunc();
    }
    this.updateButtonFont();
  }
  updateButtonFont() {
    this.buttonItemsSelected.forEach((selected, index) => {
      const selectedFontSize = this.options.hasSelectedFontSize
        ? this.options.selectedFontSize
        : this.useAdaptiveLineHeight
          ? segmentButtonTheme.ADAPTIVE_ITEM_FONT_SIZE
          : segmentButtonTheme.SELECTED_FONT_SIZE;
      const normalFontSize = this.options.hasFontSize
        ? this.options.fontSize
        : this.useAdaptiveLineHeight
          ? segmentButtonTheme.ADAPTIVE_ITEM_FONT_SIZE
          : segmentButtonTheme.FONT_SIZE;
      this.buttonItemProperty[index].fontSize = selected ? selectedFontSize : normalFontSize;
      this.buttonItemProperty[index].fontWeight = selected
        ? (this.options.selectedFontWeight ?? FontWeight.Medium)
        : (this.options.fontWeight ?? initFontWeight(FontWeight.Regular));
      this.buttonItemProperty[index].isSelected = selected;
    });
  }
  rerender() {
    this.updateDirtyElements();
  }
}
function resourceToNumber(context, resource, defaultValue) {
  if (!resource || !resource.type || !context) {
    console.error('[SegmentButton] failed: resource get fail.');
    return defaultValue;
  }
  let resourceManager = context?.resourceManager;
  if (!resourceManager) {
    console.error('[SegmentButton] failed to get resourceManager.');
    return defaultValue;
  }
  switch (resource.type) {
    case RESOURCE_TYPE_FLOAT:
    case RESOURCE_TYPE_INTEGER:
      try {
        if (resource.id !== -1) {
          return resourceManager.getNumber(resource);
        }
        return resourceManager.getNumberByName(resource.params[0].split('.')[2]);
      } catch (error) {
        console.error(`[SegmentButton] get resource error, return defaultValue`);
        return defaultValue;
      }
    default:
      return defaultValue;
  }
}
class LengthMetricsUtils {
  constructor() {}
  static getInstance() {
    if (!LengthMetricsUtils.instance) {
      LengthMetricsUtils.instance = new LengthMetricsUtils();
    }
    return LengthMetricsUtils.instance;
  }
  stringify(metrics) {
    switch (metrics.unit) {
      case LengthUnit.PX:
        return `${metrics.value}px`;
      case LengthUnit.VP:
        return `${metrics.value}vp`;
      case LengthUnit.FP:
        return `${metrics.value}fp`;
      case LengthUnit.PERCENT:
        return `${metrics.value}%`;
      case LengthUnit.LPX:
        return `${metrics.value}lpx`;
    }
  }
  isNaturalNumber(metrics) {
    return metrics.value >= 0;
  }
}
function getBackgroundBorderRadius(options, defaultRadius) {
  if (options.borderRadiusMode === BorderRadiusMode.CUSTOM) {
    if (options.type === 'capsule' && (options.multiply ?? false) && options.itemBorderRadius !== undefined) {
      return LengthMetricsUtils.getInstance().stringify(options.itemBorderRadius);
    } else if (options.backgroundBorderRadius !== undefined) {
      return LengthMetricsUtils.getInstance().stringify(options.backgroundBorderRadius);
    }
  }
  if (options.type === 'capsule' && (options.multiply ?? false)) {
    return options.iconTextRadius ?? options.iconTextBackgroundRadius ?? defaultRadius;
  }
  return options.iconTextBackgroundRadius ?? defaultRadius;
}
let SegmentButtonLayoutAlgorithm = class SegmentButtonLayoutAlgorithm extends CustomLayoutAlgorithm {
  constructor() {
    super(...arguments);
    this.selectedIndex = -1;
    this.componentPadding = 0;
    this.multiply = false;
    this.refHeight = 0;
    this.selHeight = 0;
    this.buttonWidth = 0;
    this.rowSpace = 0;
    this.shouldMirror = false;
    this.buttonCount = 0;
    this.refSize = { width: 0, height: 0 };
  }
  getButtonX(index) {
    const effectiveIndex = this.shouldMirror ? this.buttonCount - 1 - index : index;
    return this.componentPadding + (this.buttonWidth + this.rowSpace) * effectiveIndex;
  }
  onMeasure(self, constraint) {
    const childCount = self.getChildrenCount();
    if (childCount === 0) {
      self.setMeasuredSize({ width: 0, height: 0 });
      return;
    }
    const buttonLayer = self.getChild(childCount - 1);
    if (buttonLayer) {
      buttonLayer.measure(constraint);
    }
    const refSize = buttonLayer ? buttonLayer.getMeasuredSize() : { width: 0, height: 0 };
    if (this.refSize.width !== refSize.width || this.refSize.height !== refSize.height) {
      this.refSize = refSize;
    }
    let buttonWidth = 0;
    if (buttonLayer) {
      this.buttonCount = buttonLayer.getChildrenCount();
      if (this.buttonCount > 0) {
        const contentWidth = refSize.width - 2 * this.componentPadding;
        buttonWidth = (contentWidth - (this.buttonCount - 1) * this.rowSpace) / this.buttonCount;
        if (buttonWidth < 0) {
          buttonWidth = 0;
        }
      }
    }
    this.refHeight = refSize.height;
    this.selHeight = Math.max(0, refSize.height - 2 * this.componentPadding);
    this.buttonWidth = buttonWidth;
    const fullSizeConstraint = { width: refSize.width, height: refSize.height };
    const bgChild = self.getChild(0);
    if (bgChild) {
      const bgConstraint = {
        maxSize: fullSizeConstraint,
        minSize: fullSizeConstraint,
        percentReference: constraint.percentReference,
      };
      bgChild.measure(bgConstraint);
    }
    if (childCount >= 2) {
      const selChild = self.getChild(1);
      if (selChild) {
        if (this.multiply) {
          const fullConstraint = {
            maxSize: fullSizeConstraint,
            minSize: fullSizeConstraint,
            percentReference: constraint.percentReference,
          };
          selChild.measure(fullConstraint);
        } else {
          const selConstraint = {
            maxSize: { width: this.buttonWidth, height: this.selHeight },
            minSize: { width: this.buttonWidth, height: this.selHeight },
            percentReference: constraint.percentReference,
          };
          selChild.measure(selConstraint);
        }
      }
    }
    self.setMeasuredSize(refSize);
  }
  onLayout(self, position) {
    const childCount = self.getChildrenCount();
    const bgChild = self.getChild(0);
    if (bgChild) {
      bgChild.layout({ x: 0, y: 0 });
    }
    if (childCount >= 2) {
      const selChild = self.getChild(1);
      if (selChild) {
        if (this.multiply) {
          selChild.layout({ x: 0, y: 0 });
        } else {
          selChild.layout({ x: this.getButtonX(Math.max(0, this.selectedIndex)), y: this.componentPadding });
        }
      }
    }
    const btnLayer = self.getChild(childCount - 1);
    if (btnLayer) {
      btnLayer.layout({ x: 0, y: 0 });
    }
    self.setLayoutPosition({ x: position.x, y: position.y });
  }
};
__decorate([Trace], SegmentButtonLayoutAlgorithm.prototype, 'refSize', void 0);
SegmentButtonLayoutAlgorithm = __decorate([ObservedV2], SegmentButtonLayoutAlgorithm);
class FocusStyleButtonModifier {
  constructor(stateStyleAction) {
    this.stateStyleAction = stateStyleAction;
  }
  applyNormalAttribute(instance) {
    this.stateStyleAction && this.stateStyleAction(false);
  }
  applyFocusedAttribute(instance) {
    this.stateStyleAction && this.stateStyleAction(true);
  }
}

export default {
  SegmentButton,
  SegmentButtonOptions,
  SegmentButtonItemOptionsArray,
  SegmentButtonItemOptions,
  BorderRadiusMode,
};
