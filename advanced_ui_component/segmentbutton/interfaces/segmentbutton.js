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
    return c > 3 && r && Object.defineProperty(target, key, r), r;
  };
var SegmentButtonItemOptionsArray_1, SegmentButtonOptions_1;
if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {});
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
const CAPSULE_FOCUS_SELECTED_OFFSET = 4;
// Space character for selected accessibility description - prevents screen readers from announcing
const ACCESSIBILITY_SELECTED_DESCRIPTION = ' ';
const ACCESSIBILITY_DEFAULT_DESCRIPTION = '';
const segmentButtonTheme = {
  FONT_COLOR: {
    id: -1,
    type: 10001,
    params: ['sys.color.segment_button_unselected_text_color'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  TAB_SELECTED_FONT_COLOR: {
    id: -1,
    type: 10001,
    params: ['sys.color.segment_button_checked_text_color'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  CAPSULE_SELECTED_FONT_COLOR: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_foreground_contrary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  FONT_SIZE: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_unselected_text_size'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SELECTED_FONT_SIZE: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_checked_text_size'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  BACKGROUND_COLOR: {
    id: -1,
    type: 10001,
    params: ['sys.color.segment_button_backboard_color'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  TAB_SELECTED_BACKGROUND_COLOR: {
    id: -1,
    type: 10001,
    params: ['sys.color.segment_button_checked_foreground_color'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  CAPSULE_SELECTED_BACKGROUND_COLOR: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_emphasize'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  FOCUS_BORDER_COLOR: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_focused_outline'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  HOVER_COLOR: {
    id: -1,
    type: 10001,
    params: ['sys.color.segment_button_hover_color'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  PRESS_COLOR: {
    id: -1,
    type: 10001,
    params: ['sys.color.segment_button_press_color'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  BACKGROUND_BLUR_STYLE: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_background_blur_style'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  CONSTRAINT_SIZE_MIN_HEIGHT: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_height'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_MIN_FONT_SIZE: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_min_font_size'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_NORMAL_BORDER_RADIUS: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_normal_border_radius'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_ITEM_TEXT_OVERFLOW: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_marquee'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_FOCUS_TEXT_COLOR: {
    id: -1,
    type: 10001,
    params: ['sys.color.segment_button_focus_text_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_SHADOW: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_shadow'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_TEXT_HORIZONTAL_PADDING: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_text_l_r_padding'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_TEXT_VERTICAL_PADDING: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_text_u_d_padding'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_text_capsule_u_d_padding'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR: {
    id: -1,
    type: 10001,
    params: ['sys.color.segment_button_focus_backboard_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_FOCUS_STYLE_CUSTOMIZED: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_focus_control'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_CONTAINER_SHAPE: {
    id: -1,
    type: 10002,
    params: ['sys.float.segmentbutton_container_shape'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_SELECTED_BACKGROUND_SHAPE: {
    id: -1,
    type: 10002,
    params: ['sys.float.segmentbutton_selected_background_shape'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
};
function nearEqual(first, second) {
  return Math.abs(first - second) < 0.001;
}
export var BorderRadiusMode;
(function (BorderRadiusMode) {
  /**
   * DEFAULT Mode, the framework automatically calculates the border radius
   */
  BorderRadiusMode[(BorderRadiusMode['DEFAULT'] = 0)] = 'DEFAULT';
  /**
   * CUSTOM Mode, the developer sets the border radius
   */
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
    this.backgroundBlurStyle =
      options.backgroundBlurStyle ?? LengthMetrics.resource(segmentButtonTheme.BACKGROUND_BLUR_STYLE).value;
    this.localizedTextPadding = options.localizedTextPadding;
    this.localizedButtonPadding = options.localizedButtonPadding;
    this.direction = options.direction ?? Direction.Auto;
    this.borderRadiusMode = options.borderRadiusMode ?? BorderRadiusMode.DEFAULT;
    if (this.borderRadiusMode !== BorderRadiusMode.DEFAULT && this.borderRadiusMode !== BorderRadiusMode.CUSTOM) {
      this.borderRadiusMode = BorderRadiusMode.DEFAULT;
    }
    this.backgroundBorderRadius =
      options.backgroundBorderRadius ?? LengthMetrics.resource(segmentButtonTheme.SEGMENT_BUTTON_CONTAINER_SHAPE);
    this.itemBorderRadius =
      options.itemBorderRadius ?? LengthMetrics.resource(segmentButtonTheme.SEGMENT_BUTTON_SELECTED_BACKGROUND_SHAPE);
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
      id: -1,
      type: 10002,
      params: ['sys.float.segment_button_baseplate_padding'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }).value;
    this.componentPadding = this.multiply ? 0 : themePadding;
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
    this.__buttonItemsSize = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
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
    this.__buttonItemsSize = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.__selectedItemPosition = this.initializeConsume('selectedItemPosition', 'selectedItemPosition');
    this.__zoomScaleArray = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
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
            Stack.backgroundColor(
              this.options.selectedBackgroundColor ??
                (this.options.type === 'tab'
                  ? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR
                  : segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR)
            );
            Stack.position(ObservedObject.GetRawObject(this.selectedItemPosition));
            Stack.scale({
              x: this.zoomScaleArray[this.selectedIndexes[0]],
              y: this.zoomScaleArray[this.selectedIndexes[0]],
            });
            Stack.shadow(
              resourceToNumber(this.getUIContext()?.getHostContext(), segmentButtonTheme.SEGMENT_BUTTON_SHADOW, 0)
            );
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
    this.__buttonItemsSize = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
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
                Stack.width(this.buttonItemsSize[index].width);
                Stack.height(this.buttonItemsSize[index].height);
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
      Column.focusScopePriority(
        this.groupId,
        Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO
      );
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
                        { page: 'library/src/main/ets/components/MainPage.ets', line: 730, col: 13 }
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
    this.__componentSize = this.initializeConsume('componentSize', 'componentSize');
    this.__buttonBorderRadius = this.initializeConsume('buttonBorderRadius', 'buttonBorderRadius');
    this.__buttonItemsSize = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.__buttonItemsPosition = this.initializeConsume('buttonItemsPosition', 'buttonItemsPosition');
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
    this.__componentSize.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonItemsPosition.purgeDependencyOnElmtId(rmElmtId);
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
        } else if (this.options.type === 'capsule') {
          this.selectedIndexes = [];
        }
      } else {
        this.selectedIndexes[0] = this.selectedIndexes[0] - this.optionsArray.deleteCount + this.optionsArray.addLength;
      }
    } else {
      // Multi-select
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
      Stack.visibility(!this.isSegmentFocusStyleCustomized && this.focusIndex === index ? Visibility.Visible : Visibility.None);
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
    // Calculate the border radius for each button
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
    const setAllCorners = (array, index, value) => {
      if (!array || index < 0 || index >= array.length) {
        return;
      }
      const safeValue = Math.max(0, value);
      array[index].topStart = LengthMetrics.vp(safeValue);
      array[index].topEnd = LengthMetrics.vp(safeValue);
      array[index].bottomStart = LengthMetrics.vp(safeValue);
      array[index].bottomEnd = LengthMetrics.vp(safeValue);
    };
    const setLeftCorners = (array, index, value) => {
      if (!array || index < 0 || index >= array.length) {
        return;
      }
      const safeValue = Math.max(0, value);
      array[index].topStart = LengthMetrics.vp(safeValue);
      array[index].topEnd = LengthMetrics.vp(0);
      array[index].bottomStart = LengthMetrics.vp(safeValue);
      array[index].bottomEnd = LengthMetrics.vp(0);
    };
    const setRightCorners = (array, index, value) => {
      if (!array || index < 0 || index >= array.length) {
        return;
      }
      const safeValue = Math.max(0, value);
      array[index].topStart = LengthMetrics.vp(0);
      array[index].topEnd = LengthMetrics.vp(safeValue);
      array[index].bottomStart = LengthMetrics.vp(0);
      array[index].bottomEnd = LengthMetrics.vp(safeValue);
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
      let radius = this.options.iconTextRadius ?? halfButtonItemsSizeHeight; // default radius
      const isCustomMode =
        this.options.borderRadiusMode === BorderRadiusMode.CUSTOM && this.options.itemBorderRadius !== undefined;
      const radiusValue = isCustomMode ? this.options.itemBorderRadius.value : radius;
      if (isSingleSelect) {
        // single-select
        setAllCorners(borderRadiusArray, index, radiusValue);
      } else {
        // multi-select
        if (index === 0) {
          setLeftCorners(borderRadiusArray, index, radiusValue);
        } else if (index === buttonsLength - 1) {
          setRightCorners(borderRadiusArray, index, radiusValue);
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
                      Button.createWithChild();
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
                        //measure position
                        if (newValue.width) {
                          this.buttonItemsPosition[index] = {
                            start: LengthMetrics.vp(
                              Number.parseFloat(this.options.componentPadding.toString()) +
                                (Number.parseFloat(newValue.width.toString()) + 1) * index
                            ),
                            top: LengthMetrics.px(
                              Math.floor(
                                this.getUIContext().vp2px(Number.parseFloat(this.options.componentPadding.toString()))
                              )
                            ),
                          };
                        }
                      });
                      Button.overlay({
                        builder: () => {
                          this.focusStack.call(this, index);
                        }
                      }, { align: Alignment.Center });
                      Button.attributeModifier.bind(this)(this.isSegmentFocusStyleCustomized ? undefined :
                        new FocusStyleButtonModifier((isFocused) => {
                          if (!isFocused && this.focusIndex === index) {
                            this.focusIndex = -1;
                            return;
                          }
                          if (isFocused) {
                            this.focusIndex = index;
                          }
                        }));
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
                      Gesture.create(GesturePriority.Low);
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
                      Gesture.pop();
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
                        // Calculate height of items
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
                              { page: 'library/src/main/ets/components/MainPage.ets', line: 1048, col: 15 }
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
  /**
   * 设置segmentbutton获焦时的样式
   * @param index
   */
  customizeSegmentFocusStyle(index) {
    if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0 && this.selectedIndexes[0] === index) {
      // 选中态
      this.hoverColorArray[index].hoverColor = this.isDefaultSelectedBgColor()
        ? segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR
        : this.options.selectedBackgroundColor;
    } else {
      // 未选中态
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
    this.__options = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(params.selectedIndexes, this, 'selectedIndexes');
    this.onItemClicked = undefined;
    this.__maxFontScale = new SynchedPropertyObjectOneWayPU(params.maxFontScale, this, 'maxFontScale');
    this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, 'componentSize');
    this.addProvidedVar('componentSize', this.__componentSize, false);
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
    this.__buttonItemsPosition = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: MAX_ITEM_COUNT,
        },
        (_, index) => {
          return {};
        }
      ),
      this,
      'buttonItemsPosition'
    );
    this.addProvidedVar('buttonItemsPosition', this.__buttonItemsPosition, false);
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
    this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, 'selectedItemPosition');
    this.addProvidedVar('selectedItemPosition', this.__selectedItemPosition, false);
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
    this.panGestureStartPoint = { x: 0, y: 0 };
    this.isPanGestureMoved = false;
    this.__shouldMirror = new ObservedPropertySimplePU(false, this, 'shouldMirror');
    this.isSegmentFocusStyleCustomized =
      resourceToNumber(
        this.getUIContext()?.getHostContext(),
        segmentButtonTheme.SEGMENT_FOCUS_STYLE_CUSTOMIZED,
        1.0
      ) === 0.0;
    this.isGestureInProgress = false;
    this.setInitiallyProvidedValue(params);
    this.declareWatch('options', this.onOptionsChange);
    this.declareWatch('selectedIndexes', this.onSelectedChange);
    this.declareWatch('buttonItemsPosition', this.onItemsPositionChange);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.__options.set(params.options);
    if (params.onItemClicked !== undefined) {
      this.onItemClicked = params.onItemClicked;
    }
    if (params.maxFontScale === undefined) {
      this.__maxFontScale.set(DEFAULT_MAX_FONT_SCALE);
    }
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
    if (params.panGestureStartPoint !== undefined) {
      this.panGestureStartPoint = params.panGestureStartPoint;
    }
    if (params.isPanGestureMoved !== undefined) {
      this.isPanGestureMoved = params.isPanGestureMoved;
    }
    if (params.shouldMirror !== undefined) {
      this.shouldMirror = params.shouldMirror;
    }
    if (params.isSegmentFocusStyleCustomized !== undefined) {
      this.isSegmentFocusStyleCustomized = params.isSegmentFocusStyleCustomized;
    }
    if (params.isGestureInProgress !== undefined) {
      this.isGestureInProgress = params.isGestureInProgress;
    }
  }
  updateStateVars(params) {
    this.__options.set(params.options);
    this.__maxFontScale.reset(params.maxFontScale);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__options.purgeDependencyOnElmtId(rmElmtId);
    this.__selectedIndexes.purgeDependencyOnElmtId(rmElmtId);
    this.__maxFontScale.purgeDependencyOnElmtId(rmElmtId);
    this.__componentSize.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonItemsSize.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonItemsPosition.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonItemsSelected.purgeDependencyOnElmtId(rmElmtId);
    this.__buttonItemProperty.purgeDependencyOnElmtId(rmElmtId);
    this.__focusIndex.purgeDependencyOnElmtId(rmElmtId);
    this.__selectedItemPosition.purgeDependencyOnElmtId(rmElmtId);
    this.__zoomScaleArray.purgeDependencyOnElmtId(rmElmtId);
    this.__pressArray.purgeDependencyOnElmtId(rmElmtId);
    this.__hoverArray.purgeDependencyOnElmtId(rmElmtId);
    this.__hoverColorArray.purgeDependencyOnElmtId(rmElmtId);
    this.__shouldMirror.purgeDependencyOnElmtId(rmElmtId);
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
  set selectedIndexes(newValue) {
    this.__selectedIndexes.set(newValue);
  }
  get maxFontScale() {
    return this.__maxFontScale.get();
  }
  set maxFontScale(newValue) {
    this.__maxFontScale.set(newValue);
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
  isMouseWheelScroll(event) {
    return event.source === SourceType.Mouse && !this.isPanGestureMoved;
  }
  isMovedFromPanGestureStartPoint(x, y) {
    return !nearEqual(x, this.panGestureStartPoint.x) || !nearEqual(y, this.panGestureStartPoint.y);
  }
  isShouldMirror() {
    if (this.options.direction == Direction.Rtl) {
      return true;
    }
    // 获取系统语言
    try {
      let systemLanguage = I18n.System.getSystemLanguage();
      if (I18n.isRTL(systemLanguage) && this.options.direction != Direction.Ltr) {
        return true;
      }
    } catch (error) {
      console.error(`Ace SegmentButton getSystemLanguage, error: ${error.toString()}`);
    }
    return false;
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Stack.create();
      Stack.direction(this.options ? this.options.direction : undefined);
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
                // Select
                this.selectedIndexes.push(this.focusIndex);
              } else {
                // Unselect
                this.selectedIndexes.splice(this.selectedIndexes.indexOf(this.focusIndex), 1);
              }
            } else {
              // Pressed
              this.selectedIndexes[0] = this.focusIndex;
            }
          }
        }
      });
      Stack.accessibilityLevel('no');
      Gesture.create(GesturePriority.High);
      GestureGroup.create(GestureMode.Parallel);
      TapGesture.create();
      TapGesture.onAction(event => {
        if (this.isGestureInProgress) {
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
        if (this.options === void 0 || this.options.buttons === void 0 || event.sourceTool === SourceTool.TOUCHPAD) {
          return;
        }
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
          // Non swipe gesture in multi-select mode
          return;
        }
        if (this.isCurrentPositionSelected) {
          return;
        }
        if (
          Math.abs(event.angle) < 90 &&
          this.selectedIndexes[0] !== Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1
        ) {
          // Move to next
          this.doSelectedChangeAnimate = true;
          this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
          this.doSelectedChangeAnimate = false;
        } else if (Math.abs(event.angle) > 90 && this.selectedIndexes[0] !== 0) {
          // Move to previous
          this.doSelectedChangeAnimate = true;
          this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
          this.doSelectedChangeAnimate = false;
        }
      });
      SwipeGesture.pop();
      PanGesture.create();
      PanGesture.onActionStart(event => {
        this.isGestureInProgress = true;
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
      PanGesture.onActionUpdate(event => {
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
          } else {
            Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
              this.zoomScaleArray[index] = 1;
            });
          }
        });
      });
      PanGesture.onActionEnd(event => {
        this.isGestureInProgress = false;
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
          } else if (
            offset < 0 &&
            this.selectedIndexes[0] < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1
          ) {
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
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.options !== void 0 && this.options.buttons != void 0) {
        this.ifElseBranchUpdateFunction(0, () => {
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
                          { page: 'library/src/main/ets/components/MainPage.ets', line: 1390, col: 11 }
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
                  Stack.size(ObservedObject.GetRawObject(this.componentSize));
                  Stack.backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR);
                  Stack.borderRadius(getBackgroundBorderRadius(this.options, this.componentSize.height / 2));
                  Stack.backgroundBlurStyle(this.options.backgroundBlurStyle, undefined, {
                    disableSystemAdaptation: true,
                  });
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
                                { page: 'library/src/main/ets/components/MainPage.ets', line: 1397, col: 15 }
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
            Context.animation({ duration: 0 });
            Stack.direction(this.options.direction);
            Stack.size(ObservedObject.GetRawObject(this.componentSize));
            Context.animation(null);
            Stack.borderRadius(getBackgroundBorderRadius(this.options, this.componentSize.height / 2));
            Stack.clip(true);
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
                          { page: 'library/src/main/ets/components/MainPage.ets', line: 1417, col: 13 }
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
                          },
                          undefined,
                          elmtId,
                          () => {},
                          { page: 'library/src/main/ets/components/MainPage.ets', line: 1423, col: 13 }
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
                      isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                    },
                    undefined,
                    elmtId,
                    () => {},
                    { page: 'library/src/main/ets/components/MainPage.ets', line: 1439, col: 9 }
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
                      isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                    };
                  };
                  componentCall.paramsGenerator_ = paramsLambda;
                } else {
                  this.updateStateVarsOfChildByElmtId(elmtId, {
                    optionsArray: this.options.buttons,
                    options: this.options,
                    maxFontScale: this.getMaxFontSize(),
                    isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                  });
                }
              },
              { name: 'SegmentButtonItemArrayComponent' }
            );
          }
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
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
      this.selectedItemPosition =
        this.selectedIndexes.length === 0 ? {} : this.buttonItemsPosition[this.selectedIndexes[0]];
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
      Context.animateTo({ curve: curve }, setAnimatedPropertyFunc);
    } else {
      setAnimatedPropertyFunc();
    }
    this.buttonItemsSelected.forEach((selected, index) => {
      this.buttonItemProperty[index].fontSize = selected
        ? (this.options.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE)
        : (this.options.fontSize ?? segmentButtonTheme.FONT_SIZE);
      this.buttonItemProperty[index].fontWeight = selected
        ? (this.options.selectedFontWeight ?? FontWeight.Medium)
        : (this.options.fontWeight ?? FontWeight.Regular);
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
function getBackgroundBorderRadius(options, defaultRadius) {
  if (options.borderRadiusMode === BorderRadiusMode.CUSTOM) {
    // For capsule multi-select buttons, use itemBorderRadius
    if (options.type === 'capsule' && (options.multiply ?? false) && options.itemBorderRadius !== undefined) {
      return options.itemBorderRadius.value;
    } else if (options.backgroundBorderRadius !== undefined) {
      return options.backgroundBorderRadius.value;
    }
  }
  if (options.type === 'capsule' && (options.multiply ?? false)) {
    return options.iconTextRadius ?? options.iconTextBackgroundRadius ?? defaultRadius;
  }
  return options.iconTextBackgroundRadius ?? defaultRadius;
}

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
