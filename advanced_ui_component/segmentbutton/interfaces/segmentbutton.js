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

var __decorate =
  (this && this.__decorate) ||
  function (b7, c7, d7, e7) {
    var f7 = arguments.length,
      g7 =
        f7 < 3
          ? c7
          : e7 === null
          ? (e7 = Object.getOwnPropertyDescriptor(c7, d7))
          : e7,
      h7;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function')
      g7 = Reflect.decorate(b7, c7, d7, e7);
    else
      for (var i7 = b7.length - 1; i7 >= 0; i7--)
        if ((h7 = b7[i7]))
          g7 = (f7 < 3 ? h7(g7) : f7 > 3 ? h7(c7, d7, g7) : h7(c7, d7)) || g7;
    return f7 > 3 && g7 && Object.defineProperty(c7, d7, g7), g7;
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
  BACKGROUND_BLUR_STYLE: LengthMetrics.resource({
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_background_blur_style'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  }).value,
  SEGMENT_BUTTON_PADDING: LengthMetrics.resource({
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_baseplate_padding'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  }).value,
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
  SEGMENT_ITEM_TEXT_OVERFLOW:
    LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.segment_marquee'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }).value === 0.0,
  SEGMENT_BUTTON_FOCUS_TEXT_COLOR: {
    id: -1,
    type: 10001,
    params: ['sys.color.segment_button_focus_text_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  SEGMENT_BUTTON_SHADOW: LengthMetrics.resource({
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_shadow'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  }).value,
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
  SEGMENT_FOCUS_STYLE_CUSTOMIZED:
    LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.segment_focus_control'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }).value === 0.0,
};
function nearEqual(m21, n21) {
  return Math.abs(m21 - n21) < 0.001;
}
let SegmentButtonItemOptions = class SegmentButtonItemOptions {
  constructor(l21) {
    this.icon = l21.icon;
    this.selectedIcon = l21.selectedIcon;
    this.text = l21.text;
    this.iconAccessibilityText = l21.iconAccessibilityText;
    this.selectedIconAccessibilityText = l21.selectedIconAccessibilityText;
    this.accessibilityLevel = l21.accessibilityLevel;
    this.accessibilityDescription = l21.accessibilityDescription;
  }
};
SegmentButtonItemOptions = __decorate([Observed], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray =
  (SegmentButtonItemOptionsArray_1 = class SegmentButtonItemOptionsArray extends (
    Array
  ) {
    constructor(j21) {
      super(typeof j21 === 'number' ? j21 : 0);
      this.changeStartIndex = void 0;
      this.deleteCount = void 0;
      this.addLength = void 0;
      if (typeof j21 !== 'number' && j21 !== void 0) {
        super.push(...j21.map((k21) => new SegmentButtonItemOptions(k21)));
      }
    }
    push(...h21) {
      if (this.length + h21.length > MAX_ITEM_COUNT) {
        console.warn('Exceeded the maximum number of elements (5).');
        return this.length;
      }
      this.changeStartIndex = this.length;
      this.deleteCount = 0;
      this.addLength = h21.length;
      return super.push(...h21.map((i21) => new SegmentButtonItemOptions(i21)));
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
    unshift(...f21) {
      if (this.length + f21.length > MAX_ITEM_COUNT) {
        console.warn('Exceeded the maximum number of elements (5).');
        return this.length;
      }
      if (f21.length > 0) {
        this.changeStartIndex = 0;
        this.deleteCount = 0;
        this.addLength = f21.length;
      }
      return super.unshift(
        ...f21.map((g21) => new SegmentButtonItemOptions(g21))
      );
    }
    splice(b21, c21, ...d21) {
      let e21 = this.length - c21 < 0 ? 0 : this.length - c21;
      e21 += d21.length;
      if (e21 < MIN_ITEM_COUNT) {
        console.warn('Below the minimum number of elements (2).');
        return [];
      }
      if (e21 > MAX_ITEM_COUNT) {
        console.warn('Exceeded the maximum number of elements (5).');
        return [];
      }
      this.changeStartIndex = b21;
      this.deleteCount = c21;
      this.addLength = d21.length;
      return super.splice(b21, c21, ...d21);
    }
    static create(a21) {
      return new SegmentButtonItemOptionsArray_1(a21);
    }
  });
SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = __decorate(
  [Observed],
  SegmentButtonItemOptionsArray
);
export { SegmentButtonItemOptionsArray };
let SegmentButtonOptions =
  (SegmentButtonOptions_1 = class SegmentButtonOptions {
    get buttons() {
      return this._buttons;
    }
    set buttons(z20) {
      if (this._buttons !== void 0 && this._buttons !== z20) {
        this.onButtonsChange?.();
      }
      this._buttons = z20;
    }
    constructor(y20) {
      this.multiply = false;
      this.showText = false;
      this.showIcon = false;
      this._buttons = void 0;
      this.fontColor = y20.fontColor ?? segmentButtonTheme.FONT_COLOR;
      this.selectedFontColor =
        y20.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
      this.fontSize = y20.fontSize ?? segmentButtonTheme.FONT_SIZE;
      this.selectedFontSize =
        y20.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
      this.fontWeight = y20.fontWeight ?? FontWeight.Regular;
      this.selectedFontWeight = y20.selectedFontWeight ?? FontWeight.Medium;
      this.backgroundColor =
        y20.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
      this.selectedBackgroundColor =
        y20.selectedBackgroundColor ??
        segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
      this.imageSize = y20.imageSize ?? { width: 24, height: 24 };
      this.buttonPadding = y20.buttonPadding;
      this.textPadding = y20.textPadding;
      this.type = y20.type;
      this.backgroundBlurStyle =
        y20.backgroundBlurStyle ?? segmentButtonTheme.BACKGROUND_BLUR_STYLE;
      this.localizedTextPadding = y20.localizedTextPadding;
      this.localizedButtonPadding = y20.localizedButtonPadding;
      this.direction = y20.direction ?? Direction.Auto;
      this.buttons = new SegmentButtonItemOptionsArray(y20.buttons);
      if (this.type === 'capsule') {
        this.multiply = y20.multiply ?? false;
        this.onButtonsUpdated();
        this.selectedFontColor =
          y20.selectedFontColor ??
          segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
        this.selectedBackgroundColor =
          y20.selectedBackgroundColor ??
          segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
      } else {
        this.showText = true;
      }
      this.componentPadding = this.multiply
        ? 0
        : segmentButtonTheme.SEGMENT_BUTTON_PADDING;
    }
    onButtonsUpdated() {
      this.buttons?.forEach((x20) => {
        this.showText ||= x20.text !== void 0;
        this.showIcon ||= x20.icon !== void 0 || x20.selectedIcon !== void 0;
      });
      if (this.showText && this.showIcon) {
        this.iconTextRadius = 12;
        this.iconTextBackgroundRadius = 14;
      }
    }
    static tab(w20) {
      return new SegmentButtonOptions_1({
        type: 'tab',
        buttons: w20.buttons,
        fontColor: w20.fontColor,
        selectedFontColor: w20.selectedFontColor,
        fontSize: w20.fontSize,
        selectedFontSize: w20.selectedFontSize,
        fontWeight: w20.fontWeight,
        selectedFontWeight: w20.selectedFontWeight,
        backgroundColor: w20.backgroundColor,
        selectedBackgroundColor: w20.selectedBackgroundColor,
        imageSize: w20.imageSize,
        buttonPadding: w20.buttonPadding,
        textPadding: w20.textPadding,
        localizedTextPadding: w20.localizedTextPadding,
        localizedButtonPadding: w20.localizedButtonPadding,
        backgroundBlurStyle: w20.backgroundBlurStyle,
        direction: w20.direction,
      });
    }
    static capsule(v20) {
      return new SegmentButtonOptions_1({
        type: 'capsule',
        buttons: v20.buttons,
        multiply: v20.multiply,
        fontColor: v20.fontColor,
        selectedFontColor: v20.selectedFontColor,
        fontSize: v20.fontSize,
        selectedFontSize: v20.selectedFontSize,
        fontWeight: v20.fontWeight,
        selectedFontWeight: v20.selectedFontWeight,
        backgroundColor: v20.backgroundColor,
        selectedBackgroundColor: v20.selectedBackgroundColor,
        imageSize: v20.imageSize,
        buttonPadding: v20.buttonPadding,
        textPadding: v20.textPadding,
        localizedTextPadding: v20.localizedTextPadding,
        localizedButtonPadding: v20.localizedButtonPadding,
        backgroundBlurStyle: v20.backgroundBlurStyle,
        direction: v20.direction,
      });
    }
  });
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate(
  [Observed],
  SegmentButtonOptions
);
export { SegmentButtonOptions };
class MultiSelectBackground extends ViewPU {
  constructor(p20, q20, r20, s20 = -1, t20 = undefined, u20) {
    super(p20, r20, s20, u20);
    if (typeof t20 === 'function') {
      this.paramsGenerator_ = t20;
    }
    this.__optionsArray = new SynchedPropertyNesedObjectPU(
      q20.optionsArray,
      this,
      'optionsArray'
    );
    this.__options = new SynchedPropertyNesedObjectPU(
      q20.options,
      this,
      'options'
    );
    this.__buttonBorderRadius = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.__buttonItemsSize = this.initializeConsume(
      'buttonItemsSize',
      'buttonItemsSize'
    );
    this.setInitiallyProvidedValue(q20);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(o20) {
    this.__optionsArray.set(o20.optionsArray);
    this.__options.set(o20.options);
  }
  updateStateVars(n20) {
    this.__optionsArray.set(n20.optionsArray);
    this.__options.set(n20.options);
  }
  purgeVariableDependenciesOnElmtId(m20) {
    this.__optionsArray.purgeDependencyOnElmtId(m20);
    this.__options.purgeDependencyOnElmtId(m20);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(m20);
    this.__buttonItemsSize.purgeDependencyOnElmtId(m20);
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
  set buttonBorderRadius(l20) {
    this.__buttonBorderRadius.set(l20);
  }
  get buttonItemsSize() {
    return this.__buttonItemsSize.get();
  }
  set buttonItemsSize(k20) {
    this.__buttonItemsSize.set(k20);
  }
  initialRender() {
    this.observeComponentCreation2((i20, j20) => {
      Row.create({ space: 1 });
      Row.direction(this.options.direction);
      Row.padding(this.options.componentPadding);
    }, Row);
    this.observeComponentCreation2((y19, z19) => {
      ForEach.create();
      const a20 = (b20, c20) => {
        const d20 = b20;
        this.observeComponentCreation2((e20, f20) => {
          If.create();
          if (c20 < MAX_ITEM_COUNT) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((g20, h20) => {
                Stack.create();
                Stack.direction(this.options.direction);
                Stack.layoutWeight(1);
                Stack.height(this.buttonItemsSize[c20].height);
                Stack.backgroundColor(
                  this.options.backgroundColor ??
                    segmentButtonTheme.BACKGROUND_COLOR
                );
                Stack.borderRadius(this.buttonBorderRadius[c20]);
                Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
              }, Stack);
              Stack.pop();
            });
          } else {
            this.ifElseBranchUpdateFunction(1, () => {});
          }
        }, If);
        If.pop();
      };
      this.forEachUpdateFunction(
        y19,
        this.optionsArray,
        a20,
        undefined,
        true,
        false
      );
    }, ForEach);
    ForEach.pop();
    Row.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class SelectItem extends ViewPU {
  constructor(s19, t19, u19, v19 = -1, w19 = undefined, x19) {
    super(s19, u19, v19, x19);
    if (typeof w19 === 'function') {
      this.paramsGenerator_ = w19;
    }
    this.__optionsArray = new SynchedPropertyNesedObjectPU(
      t19.optionsArray,
      this,
      'optionsArray'
    );
    this.__options = new SynchedPropertyNesedObjectPU(
      t19.options,
      this,
      'options'
    );
    this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(
      t19.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.__buttonItemsSize = this.initializeConsume(
      'buttonItemsSize',
      'buttonItemsSize'
    );
    this.__selectedItemPosition = this.initializeConsume(
      'selectedItemPosition',
      'selectedItemPosition'
    );
    this.__zoomScaleArray = this.initializeConsume(
      'zoomScaleArray',
      'zoomScaleArray'
    );
    this.__buttonBorderRadius = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.setInitiallyProvidedValue(t19);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(r19) {
    this.__optionsArray.set(r19.optionsArray);
    this.__options.set(r19.options);
  }
  updateStateVars(q19) {
    this.__optionsArray.set(q19.optionsArray);
    this.__options.set(q19.options);
  }
  purgeVariableDependenciesOnElmtId(p19) {
    this.__optionsArray.purgeDependencyOnElmtId(p19);
    this.__options.purgeDependencyOnElmtId(p19);
    this.__selectedIndexes.purgeDependencyOnElmtId(p19);
    this.__buttonItemsSize.purgeDependencyOnElmtId(p19);
    this.__selectedItemPosition.purgeDependencyOnElmtId(p19);
    this.__zoomScaleArray.purgeDependencyOnElmtId(p19);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(p19);
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
  set selectedIndexes(o19) {
    this.__selectedIndexes.set(o19);
  }
  get buttonItemsSize() {
    return this.__buttonItemsSize.get();
  }
  set buttonItemsSize(n19) {
    this.__buttonItemsSize.set(n19);
  }
  get selectedItemPosition() {
    return this.__selectedItemPosition.get();
  }
  set selectedItemPosition(m19) {
    this.__selectedItemPosition.set(m19);
  }
  get zoomScaleArray() {
    return this.__zoomScaleArray.get();
  }
  set zoomScaleArray(l19) {
    this.__zoomScaleArray.set(l19);
  }
  get buttonBorderRadius() {
    return this.__buttonBorderRadius.get();
  }
  set buttonBorderRadius(k19) {
    this.__buttonBorderRadius.set(k19);
  }
  initialRender() {
    this.observeComponentCreation2((g19, h19) => {
      If.create();
      if (
        this.selectedIndexes !== void 0 &&
        this.selectedIndexes.length !== 0
      ) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((i19, j19) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.borderRadius(
              this.buttonBorderRadius[this.selectedIndexes[0]]
            );
            Stack.size(this.buttonItemsSize[this.selectedIndexes[0]]);
            Stack.backgroundColor(
              this.options.selectedBackgroundColor ??
                (this.options.type === 'tab'
                  ? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR
                  : segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR)
            );
            Stack.position(
              ObservedObject.GetRawObject(this.selectedItemPosition)
            );
            Stack.scale({
              x: this.zoomScaleArray[this.selectedIndexes[0]],
              y: this.zoomScaleArray[this.selectedIndexes[0]],
            });
            Stack.shadow(segmentButtonTheme.SEGMENT_BUTTON_SHADOW);
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
  constructor(y18, z18, a19, b19 = -1, c19 = undefined, d19) {
    super(y18, a19, b19, d19);
    if (typeof c19 === 'function') {
      this.paramsGenerator_ = c19;
    }
    this.__optionsArray = new SynchedPropertyNesedObjectPU(
      z18.optionsArray,
      this,
      'optionsArray'
    );
    this.__options = new SynchedPropertyNesedObjectPU(
      z18.options,
      this,
      'options'
    );
    this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(
      z18.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.__buttonItemsSize = this.initializeConsume(
      'buttonItemsSize',
      'buttonItemsSize'
    );
    this.__zoomScaleArray = this.initializeConsume(
      'zoomScaleArray',
      'zoomScaleArray'
    );
    this.__buttonBorderRadius = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.__multiColor = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (e19, f19) => Color.Transparent),
      this,
      'multiColor'
    );
    this.setInitiallyProvidedValue(z18);
    this.declareWatch('options', this.onOptionsChange);
    this.declareWatch('selectedIndexes', this.onSelectedChange);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(x18) {
    this.__optionsArray.set(x18.optionsArray);
    this.__options.set(x18.options);
    if (x18.multiColor !== undefined) {
      this.multiColor = x18.multiColor;
    }
  }
  updateStateVars(w18) {
    this.__optionsArray.set(w18.optionsArray);
    this.__options.set(w18.options);
  }
  purgeVariableDependenciesOnElmtId(v18) {
    this.__optionsArray.purgeDependencyOnElmtId(v18);
    this.__options.purgeDependencyOnElmtId(v18);
    this.__selectedIndexes.purgeDependencyOnElmtId(v18);
    this.__buttonItemsSize.purgeDependencyOnElmtId(v18);
    this.__zoomScaleArray.purgeDependencyOnElmtId(v18);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(v18);
    this.__multiColor.purgeDependencyOnElmtId(v18);
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
  set selectedIndexes(u18) {
    this.__selectedIndexes.set(u18);
  }
  get buttonItemsSize() {
    return this.__buttonItemsSize.get();
  }
  set buttonItemsSize(t18) {
    this.__buttonItemsSize.set(t18);
  }
  get zoomScaleArray() {
    return this.__zoomScaleArray.get();
  }
  set zoomScaleArray(s18) {
    this.__zoomScaleArray.set(s18);
  }
  get buttonBorderRadius() {
    return this.__buttonBorderRadius.get();
  }
  set buttonBorderRadius(r18) {
    this.__buttonBorderRadius.set(r18);
  }
  get multiColor() {
    return this.__multiColor.get();
  }
  set multiColor(q18) {
    this.__multiColor.set(q18);
  }
  onOptionsChange() {
    for (let p18 = 0; p18 < this.selectedIndexes.length; p18++) {
      this.multiColor[this.selectedIndexes[p18]] =
        this.options.selectedBackgroundColor ??
        segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
    }
  }
  onSelectedChange() {
    for (let o18 = 0; o18 < MAX_ITEM_COUNT; o18++) {
      this.multiColor[o18] = Color.Transparent;
    }
    for (let n18 = 0; n18 < this.selectedIndexes.length; n18++) {
      this.multiColor[this.selectedIndexes[n18]] =
        this.options.selectedBackgroundColor ??
        segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
    }
  }
  aboutToAppear() {
    for (let m18 = 0; m18 < this.selectedIndexes.length; m18++) {
      this.multiColor[this.selectedIndexes[m18]] =
        this.options.selectedBackgroundColor ??
        segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
    }
  }
  initialRender() {
    this.observeComponentCreation2((k18, l18) => {
      Row.create({ space: 1 });
      Row.direction(this.options.direction);
      Row.padding(this.options.componentPadding);
    }, Row);
    this.observeComponentCreation2((a18, b18) => {
      ForEach.create();
      const c18 = (d18, e18) => {
        const f18 = d18;
        this.observeComponentCreation2((g18, h18) => {
          If.create();
          if (e18 < MAX_ITEM_COUNT) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((i18, j18) => {
                Stack.create();
                Stack.direction(this.options.direction);
                Stack.width(this.buttonItemsSize[e18].width);
                Stack.height(this.buttonItemsSize[e18].height);
                Stack.backgroundColor(this.multiColor[e18]);
                Stack.borderRadius(this.buttonBorderRadius[e18]);
              }, Stack);
              Stack.pop();
            });
          } else {
            this.ifElseBranchUpdateFunction(1, () => {});
          }
        }, If);
        If.pop();
      };
      this.forEachUpdateFunction(
        a18,
        this.optionsArray,
        c18,
        undefined,
        true,
        false
      );
    }, ForEach);
    ForEach.pop();
    Row.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class SegmentButtonItem extends ViewPU {
  constructor(u17, v17, w17, x17 = -1, y17 = undefined, z17) {
    super(u17, w17, x17, z17);
    if (typeof y17 === 'function') {
      this.paramsGenerator_ = y17;
    }
    this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(
      v17.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.__focusIndex = new SynchedPropertySimpleTwoWayPU(
      v17.focusIndex,
      this,
      'focusIndex'
    );
    this.__maxFontScale = new SynchedPropertyObjectOneWayPU(
      v17.maxFontScale,
      this,
      'maxFontScale'
    );
    this.__itemOptions = new SynchedPropertyNesedObjectPU(
      v17.itemOptions,
      this,
      'itemOptions'
    );
    this.__options = new SynchedPropertyNesedObjectPU(
      v17.options,
      this,
      'options'
    );
    this.__property = new SynchedPropertyNesedObjectPU(
      v17.property,
      this,
      'property'
    );
    this.__index = new SynchedPropertySimpleOneWayPU(v17.index, this, 'index');
    this.__isTextSupportMarquee = new ObservedPropertySimplePU(
      segmentButtonTheme.SEGMENT_ITEM_TEXT_OVERFLOW,
      this,
      'isTextSupportMarquee'
    );
    this.__isMarqueeAndFadeout = new SynchedPropertySimpleOneWayPU(
      v17.isMarqueeAndFadeout,
      this,
      'isMarqueeAndFadeout'
    );
    this.__isSegmentFocusStyleCustomized = new SynchedPropertySimpleOneWayPU(
      v17.isSegmentFocusStyleCustomized,
      this,
      'isSegmentFocusStyleCustomized'
    );
    this.__isTextInMarqueeCondition = new ObservedPropertySimplePU(
      false,
      this,
      'isTextInMarqueeCondition'
    );
    this.__isButtonTextFadeout = new ObservedPropertySimplePU(
      false,
      this,
      'isButtonTextFadeout'
    );
    this.groupId = '';
    this.__hover = new SynchedPropertySimpleOneWayPU(v17.hover, this, 'hover');
    this.setInitiallyProvidedValue(v17);
    this.declareWatch('focusIndex', this.onFocusIndex);
    this.declareWatch('hover', this.onFocusIndex);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(t17) {
    this.__itemOptions.set(t17.itemOptions);
    this.__options.set(t17.options);
    this.__property.set(t17.property);
    if (t17.isTextSupportMarquee !== undefined) {
      this.isTextSupportMarquee = t17.isTextSupportMarquee;
    }
    if (t17.isTextInMarqueeCondition !== undefined) {
      this.isTextInMarqueeCondition = t17.isTextInMarqueeCondition;
    }
    if (t17.isButtonTextFadeout !== undefined) {
      this.isButtonTextFadeout = t17.isButtonTextFadeout;
    }
    if (t17.groupId !== undefined) {
      this.groupId = t17.groupId;
    }
  }
  updateStateVars(s17) {
    this.__maxFontScale.reset(s17.maxFontScale);
    this.__itemOptions.set(s17.itemOptions);
    this.__options.set(s17.options);
    this.__property.set(s17.property);
    this.__index.reset(s17.index);
    this.__isMarqueeAndFadeout.reset(s17.isMarqueeAndFadeout);
    this.__isSegmentFocusStyleCustomized.reset(
      s17.isSegmentFocusStyleCustomized
    );
    this.__hover.reset(s17.hover);
  }
  purgeVariableDependenciesOnElmtId(r17) {
    this.__selectedIndexes.purgeDependencyOnElmtId(r17);
    this.__focusIndex.purgeDependencyOnElmtId(r17);
    this.__maxFontScale.purgeDependencyOnElmtId(r17);
    this.__itemOptions.purgeDependencyOnElmtId(r17);
    this.__options.purgeDependencyOnElmtId(r17);
    this.__property.purgeDependencyOnElmtId(r17);
    this.__index.purgeDependencyOnElmtId(r17);
    this.__isTextSupportMarquee.purgeDependencyOnElmtId(r17);
    this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(r17);
    this.__isSegmentFocusStyleCustomized.purgeDependencyOnElmtId(r17);
    this.__isTextInMarqueeCondition.purgeDependencyOnElmtId(r17);
    this.__isButtonTextFadeout.purgeDependencyOnElmtId(r17);
    this.__hover.purgeDependencyOnElmtId(r17);
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
  set selectedIndexes(q17) {
    this.__selectedIndexes.set(q17);
  }
  get focusIndex() {
    return this.__focusIndex.get();
  }
  set focusIndex(p17) {
    this.__focusIndex.set(p17);
  }
  get maxFontScale() {
    return this.__maxFontScale.get();
  }
  set maxFontScale(o17) {
    this.__maxFontScale.set(o17);
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
  set index(n17) {
    this.__index.set(n17);
  }
  get isTextSupportMarquee() {
    return this.__isTextSupportMarquee.get();
  }
  set isTextSupportMarquee(m17) {
    this.__isTextSupportMarquee.set(m17);
  }
  get isMarqueeAndFadeout() {
    return this.__isMarqueeAndFadeout.get();
  }
  set isMarqueeAndFadeout(l17) {
    this.__isMarqueeAndFadeout.set(l17);
  }
  get isSegmentFocusStyleCustomized() {
    return this.__isSegmentFocusStyleCustomized.get();
  }
  set isSegmentFocusStyleCustomized(k17) {
    this.__isSegmentFocusStyleCustomized.set(k17);
  }
  get isTextInMarqueeCondition() {
    return this.__isTextInMarqueeCondition.get();
  }
  set isTextInMarqueeCondition(j17) {
    this.__isTextInMarqueeCondition.set(j17);
  }
  get isButtonTextFadeout() {
    return this.__isButtonTextFadeout.get();
  }
  set isButtonTextFadeout(i17) {
    this.__isButtonTextFadeout.set(i17);
  }
  get hover() {
    return this.__hover.get();
  }
  set hover(h17) {
    this.__hover.set(h17);
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
    if (
      this.options.type === 'capsule' &&
      this.options.showText &&
      this.options.showIcon
    ) {
      return {
        top: LengthMetrics.resource(
          segmentButtonTheme.SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING
        ),
        bottom: LengthMetrics.resource(
          segmentButtonTheme.SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING
        ),
        start: LengthMetrics.resource(
          segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING
        ),
        end: LengthMetrics.resource(
          segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING
        ),
      };
    }
    return {
      top: LengthMetrics.resource(
        segmentButtonTheme.SEGMENT_TEXT_VERTICAL_PADDING
      ),
      bottom: LengthMetrics.resource(
        segmentButtonTheme.SEGMENT_TEXT_VERTICAL_PADDING
      ),
      start: LengthMetrics.resource(
        segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING
      ),
      end: LengthMetrics.resource(
        segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING
      ),
    };
  }
  onFocusIndex() {
    this.isTextInMarqueeCondition =
      this.isSegmentFocusStyleCustomized &&
      (this.focusIndex === this.index || this.hover);
  }
  aboutToAppear() {
    this.isButtonTextFadeout = this.isSegmentFocusStyleCustomized;
  }
  isDefaultSelectedFontColor() {
    if (this.options.type === 'tab') {
      return (
        this.options.selectedFontColor ===
        segmentButtonTheme.TAB_SELECTED_FONT_COLOR
      );
    } else if (this.options.type === 'capsule') {
      return (
        this.options.selectedFontColor ===
        segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR
      );
    }
    return false;
  }
  getFontColor() {
    if (this.property.isSelected) {
      if (
        this.isDefaultSelectedFontColor() &&
        this.isSegmentFocusStyleCustomized &&
        this.focusIndex === this.index
      ) {
        return segmentButtonTheme.SEGMENT_BUTTON_FOCUS_TEXT_COLOR;
      }
      return (
        this.options.selectedFontColor ??
        segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR
      );
    } else {
      if (
        this.options.fontColor === segmentButtonTheme.FONT_COLOR &&
        this.isSegmentFocusStyleCustomized &&
        this.focusIndex === this.index
      ) {
        return segmentButtonTheme.SEGMENT_BUTTON_FOCUS_TEXT_COLOR;
      }
      return this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
    }
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
    this.observeComponentCreation2((f17, g17) => {
      Column.create({ space: 2 });
      Column.direction(this.options.direction);
      Column.focusScopePriority(
        this.groupId,
        Math.min(...this.selectedIndexes) === this.index
          ? FocusPriority.PREVIOUS
          : FocusPriority.AUTO
      );
      Column.justifyContent(FlexAlign.Center);
      Column.padding(this.getButtonPadding());
      Column.constraintSize({
        minHeight: segmentButtonTheme.CONSTRAINT_SIZE_MIN_HEIGHT,
      });
    }, Column);
    this.observeComponentCreation2((b17, c17) => {
      If.create();
      if (this.options.showIcon) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((d17, e17) => {
            Image.create(
              this.property.isSelected
                ? this.itemOptions.selectedIcon
                : this.itemOptions.icon
            );
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
    this.observeComponentCreation2((x16, y16) => {
      If.create();
      if (this.options.showText) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((z16, a17) => {
            Text.create(this.itemOptions.text);
            Text.direction(this.options.direction);
            Text.fontColor(this.getFontColor());
            Text.fontWeight(this.property.fontWeight);
            Text.fontSize(this.property.fontSize);
            Text.minFontSize(9);
            Text.maxFontSize(this.property.fontSize);
            Text.maxFontScale(ObservedObject.GetRawObject(this.maxFontScale));
            Text.textOverflow({
              overflow: this.isTextSupportMarquee
                ? TextOverflow.MARQUEE
                : TextOverflow.Ellipsis,
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
  constructor(r16, s16, t16, u16 = -1, v16 = undefined, w16) {
    super(r16, t16, u16, w16);
    if (typeof v16 === 'function') {
      this.paramsGenerator_ = v16;
    }
    this.__buttonItemsSize = this.initializeConsume(
      'buttonItemsSize',
      'buttonItemsSize'
    );
    this.__press = new SynchedPropertySimpleOneWayPU(s16.press, this, 'press');
    this.__hover = new SynchedPropertySimpleOneWayPU(s16.hover, this, 'hover');
    this.__colorProperty = new SynchedPropertyNesedObjectPU(
      s16.colorProperty,
      this,
      'colorProperty'
    );
    this.__buttonBorderRadius = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.__options = new SynchedPropertyNesedObjectPU(
      s16.options,
      this,
      'options'
    );
    this.pressIndex = 0;
    this.pressColor = segmentButtonTheme.PRESS_COLOR;
    this.setInitiallyProvidedValue(s16);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(q16) {
    this.__colorProperty.set(q16.colorProperty);
    this.__options.set(q16.options);
    if (q16.pressIndex !== undefined) {
      this.pressIndex = q16.pressIndex;
    }
    if (q16.pressColor !== undefined) {
      this.pressColor = q16.pressColor;
    }
  }
  updateStateVars(p16) {
    this.__press.reset(p16.press);
    this.__hover.reset(p16.hover);
    this.__colorProperty.set(p16.colorProperty);
    this.__options.set(p16.options);
  }
  purgeVariableDependenciesOnElmtId(o16) {
    this.__buttonItemsSize.purgeDependencyOnElmtId(o16);
    this.__press.purgeDependencyOnElmtId(o16);
    this.__hover.purgeDependencyOnElmtId(o16);
    this.__colorProperty.purgeDependencyOnElmtId(o16);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(o16);
    this.__options.purgeDependencyOnElmtId(o16);
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
  set buttonItemsSize(n16) {
    this.__buttonItemsSize.set(n16);
  }
  get press() {
    return this.__press.get();
  }
  set press(m16) {
    this.__press.set(m16);
  }
  get hover() {
    return this.__hover.get();
  }
  set hover(l16) {
    this.__hover.set(l16);
  }
  get colorProperty() {
    return this.__colorProperty.get();
  }
  get buttonBorderRadius() {
    return this.__buttonBorderRadius.get();
  }
  set buttonBorderRadius(k16) {
    this.__buttonBorderRadius.set(k16);
  }
  get options() {
    return this.__options.get();
  }
  initialRender() {
    this.observeComponentCreation2((i16, j16) => {
      Stack.create();
      Stack.direction(this.options.direction);
      Stack.size(this.buttonItemsSize[this.pressIndex]);
      Stack.backgroundColor(
        this.press && this.hover
          ? this.pressColor
          : this.colorProperty.hoverColor
      );
      Stack.borderRadius(this.buttonBorderRadius[this.pressIndex]);
    }, Stack);
    Stack.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class PressAndHoverEffectArray extends ViewPU {
  constructor(c16, d16, e16, f16 = -1, g16 = undefined, h16) {
    super(c16, e16, f16, h16);
    if (typeof g16 === 'function') {
      this.paramsGenerator_ = g16;
    }
    this.__buttons = new SynchedPropertyNesedObjectPU(
      d16.buttons,
      this,
      'buttons'
    );
    this.__options = new SynchedPropertyNesedObjectPU(
      d16.options,
      this,
      'options'
    );
    this.__pressArray = new SynchedPropertyObjectTwoWayPU(
      d16.pressArray,
      this,
      'pressArray'
    );
    this.__hoverArray = new SynchedPropertyObjectTwoWayPU(
      d16.hoverArray,
      this,
      'hoverArray'
    );
    this.__hoverColorArray = new SynchedPropertyObjectTwoWayPU(
      d16.hoverColorArray,
      this,
      'hoverColorArray'
    );
    this.__zoomScaleArray = this.initializeConsume(
      'zoomScaleArray',
      'zoomScaleArray'
    );
    this.setInitiallyProvidedValue(d16);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(b16) {
    this.__buttons.set(b16.buttons);
    this.__options.set(b16.options);
  }
  updateStateVars(a16) {
    this.__buttons.set(a16.buttons);
    this.__options.set(a16.options);
  }
  purgeVariableDependenciesOnElmtId(z15) {
    this.__buttons.purgeDependencyOnElmtId(z15);
    this.__options.purgeDependencyOnElmtId(z15);
    this.__pressArray.purgeDependencyOnElmtId(z15);
    this.__hoverArray.purgeDependencyOnElmtId(z15);
    this.__hoverColorArray.purgeDependencyOnElmtId(z15);
    this.__zoomScaleArray.purgeDependencyOnElmtId(z15);
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
  set pressArray(y15) {
    this.__pressArray.set(y15);
  }
  get hoverArray() {
    return this.__hoverArray.get();
  }
  set hoverArray(x15) {
    this.__hoverArray.set(x15);
  }
  get hoverColorArray() {
    return this.__hoverColorArray.get();
  }
  set hoverColorArray(w15) {
    this.__hoverColorArray.set(w15);
  }
  get zoomScaleArray() {
    return this.__zoomScaleArray.get();
  }
  set zoomScaleArray(v15) {
    this.__zoomScaleArray.set(v15);
  }
  initialRender() {
    this.observeComponentCreation2((t15, u15) => {
      Row.create({ space: 1 });
      Row.direction(this.options.direction);
    }, Row);
    this.observeComponentCreation2((f15, g15) => {
      ForEach.create();
      const h15 = (i15, j15) => {
        const k15 = i15;
        this.observeComponentCreation2((l15, m15) => {
          If.create();
          if (j15 < MAX_ITEM_COUNT) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((r15, s15) => {
                Stack.create();
                Stack.direction(this.options.direction);
                Stack.scale({
                  x:
                    this.options.type === 'capsule' &&
                    (this.options.multiply ?? false)
                      ? 1
                      : this.zoomScaleArray[j15],
                  y:
                    this.options.type === 'capsule' &&
                    (this.options.multiply ?? false)
                      ? 1
                      : this.zoomScaleArray[j15],
                });
              }, Stack);
              {
                this.observeComponentCreation2(
                  (n15, o15) => {
                    if (o15) {
                      let p15 = new PressAndHoverEffect(
                        this,
                        {
                          pressIndex: j15,
                          colorProperty: this.hoverColorArray[j15],
                          press: this.pressArray[j15],
                          hover: this.hoverArray[j15],
                          options: this.options,
                        },
                        undefined,
                        n15,
                        () => {},
                        {
                          page: 'library/src/main/ets/components/MainPage.ets',
                          line: 684,
                          col: 13,
                        }
                      );
                      ViewPU.create(p15);
                      let q15 = () => {
                        return {
                          pressIndex: j15,
                          colorProperty: this.hoverColorArray[j15],
                          press: this.pressArray[j15],
                          hover: this.hoverArray[j15],
                          options: this.options,
                        };
                      };
                      p15.paramsGenerator_ = q15;
                    } else {
                      this.updateStateVarsOfChildByElmtId(n15, {
                        colorProperty: this.hoverColorArray[j15],
                        press: this.pressArray[j15],
                        hover: this.hoverArray[j15],
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
      this.forEachUpdateFunction(
        f15,
        this.buttons,
        h15,
        undefined,
        true,
        false
      );
    }, ForEach);
    ForEach.pop();
    Row.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class SegmentButtonItemArrayComponent extends ViewPU {
  constructor(t14, u14, v14, w14 = -1, x14 = undefined, y14) {
    super(t14, v14, w14, y14);
    if (typeof x14 === 'function') {
      this.paramsGenerator_ = x14;
    }
    this.__optionsArray = new SynchedPropertyNesedObjectPU(
      u14.optionsArray,
      this,
      'optionsArray'
    );
    this.__options = new SynchedPropertyNesedObjectPU(
      u14.options,
      this,
      'options'
    );
    this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(
      u14.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.__componentSize = this.initializeConsume(
      'componentSize',
      'componentSize'
    );
    this.__buttonBorderRadius = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.__buttonItemsSize = this.initializeConsume(
      'buttonItemsSize',
      'buttonItemsSize'
    );
    this.__buttonItemsPosition = this.initializeConsume(
      'buttonItemsPosition',
      'buttonItemsPosition'
    );
    this.__focusIndex = this.initializeConsume('focusIndex', 'focusIndex');
    this.__zoomScaleArray = this.initializeConsume(
      'zoomScaleArray',
      'zoomScaleArray'
    );
    this.__buttonItemProperty = this.initializeConsume(
      'buttonItemProperty',
      'buttonItemProperty'
    );
    this.__buttonItemsSelected = this.initializeConsume(
      'buttonItemsSelected',
      'buttonItemsSelected'
    );
    this.__pressArray = new SynchedPropertyObjectTwoWayPU(
      u14.pressArray,
      this,
      'pressArray'
    );
    this.__hoverArray = new SynchedPropertyObjectTwoWayPU(
      u14.hoverArray,
      this,
      'hoverArray'
    );
    this.__hoverColorArray = new SynchedPropertyObjectTwoWayPU(
      u14.hoverColorArray,
      this,
      'hoverColorArray'
    );
    this.__maxFontScale = new SynchedPropertyObjectOneWayPU(
      u14.maxFontScale,
      this,
      'maxFontScale'
    );
    this.__buttonWidth = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (d15, e15) => 0),
      this,
      'buttonWidth'
    );
    this.__buttonHeight = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (b15, c15) => 0),
      this,
      'buttonHeight'
    );
    this.__isMarqueeAndFadeout = new ObservedPropertySimplePU(
      false,
      this,
      'isMarqueeAndFadeout'
    );
    this.buttonItemsRealHeight = Array.from(
      { length: MAX_ITEM_COUNT },
      (z14, a15) => 0
    );
    this.groupId = util.generateRandomUUID(true);
    this.onItemClicked = undefined;
    this.__isSegmentFocusStyleCustomized = new SynchedPropertySimpleOneWayPU(
      u14.isSegmentFocusStyleCustomized,
      this,
      'isSegmentFocusStyleCustomized'
    );
    this.setInitiallyProvidedValue(u14);
    this.declareWatch('optionsArray', this.onOptionsArrayChange);
    this.declareWatch('options', this.onOptionsChange);
    this.declareWatch('buttonItemsSize', this.onButtonItemsSizeChange);
    this.declareWatch('focusIndex', this.onFocusIndex);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(s14) {
    this.__optionsArray.set(s14.optionsArray);
    this.__options.set(s14.options);
    if (s14.buttonWidth !== undefined) {
      this.buttonWidth = s14.buttonWidth;
    }
    if (s14.buttonHeight !== undefined) {
      this.buttonHeight = s14.buttonHeight;
    }
    if (s14.isMarqueeAndFadeout !== undefined) {
      this.isMarqueeAndFadeout = s14.isMarqueeAndFadeout;
    }
    if (s14.buttonItemsRealHeight !== undefined) {
      this.buttonItemsRealHeight = s14.buttonItemsRealHeight;
    }
    if (s14.groupId !== undefined) {
      this.groupId = s14.groupId;
    }
    if (s14.onItemClicked !== undefined) {
      this.onItemClicked = s14.onItemClicked;
    }
  }
  updateStateVars(r14) {
    this.__optionsArray.set(r14.optionsArray);
    this.__options.set(r14.options);
    this.__maxFontScale.reset(r14.maxFontScale);
    this.__isSegmentFocusStyleCustomized.reset(
      r14.isSegmentFocusStyleCustomized
    );
  }
  purgeVariableDependenciesOnElmtId(q14) {
    this.__optionsArray.purgeDependencyOnElmtId(q14);
    this.__options.purgeDependencyOnElmtId(q14);
    this.__selectedIndexes.purgeDependencyOnElmtId(q14);
    this.__componentSize.purgeDependencyOnElmtId(q14);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(q14);
    this.__buttonItemsSize.purgeDependencyOnElmtId(q14);
    this.__buttonItemsPosition.purgeDependencyOnElmtId(q14);
    this.__focusIndex.purgeDependencyOnElmtId(q14);
    this.__zoomScaleArray.purgeDependencyOnElmtId(q14);
    this.__buttonItemProperty.purgeDependencyOnElmtId(q14);
    this.__buttonItemsSelected.purgeDependencyOnElmtId(q14);
    this.__pressArray.purgeDependencyOnElmtId(q14);
    this.__hoverArray.purgeDependencyOnElmtId(q14);
    this.__hoverColorArray.purgeDependencyOnElmtId(q14);
    this.__maxFontScale.purgeDependencyOnElmtId(q14);
    this.__buttonWidth.purgeDependencyOnElmtId(q14);
    this.__buttonHeight.purgeDependencyOnElmtId(q14);
    this.__isMarqueeAndFadeout.purgeDependencyOnElmtId(q14);
    this.__isSegmentFocusStyleCustomized.purgeDependencyOnElmtId(q14);
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
  set selectedIndexes(p14) {
    this.__selectedIndexes.set(p14);
  }
  get componentSize() {
    return this.__componentSize.get();
  }
  set componentSize(o14) {
    this.__componentSize.set(o14);
  }
  get buttonBorderRadius() {
    return this.__buttonBorderRadius.get();
  }
  set buttonBorderRadius(n14) {
    this.__buttonBorderRadius.set(n14);
  }
  get buttonItemsSize() {
    return this.__buttonItemsSize.get();
  }
  set buttonItemsSize(m14) {
    this.__buttonItemsSize.set(m14);
  }
  get buttonItemsPosition() {
    return this.__buttonItemsPosition.get();
  }
  set buttonItemsPosition(l14) {
    this.__buttonItemsPosition.set(l14);
  }
  get focusIndex() {
    return this.__focusIndex.get();
  }
  set focusIndex(k14) {
    this.__focusIndex.set(k14);
  }
  get zoomScaleArray() {
    return this.__zoomScaleArray.get();
  }
  set zoomScaleArray(j14) {
    this.__zoomScaleArray.set(j14);
  }
  get buttonItemProperty() {
    return this.__buttonItemProperty.get();
  }
  set buttonItemProperty(i14) {
    this.__buttonItemProperty.set(i14);
  }
  get buttonItemsSelected() {
    return this.__buttonItemsSelected.get();
  }
  set buttonItemsSelected(h14) {
    this.__buttonItemsSelected.set(h14);
  }
  get pressArray() {
    return this.__pressArray.get();
  }
  set pressArray(g14) {
    this.__pressArray.set(g14);
  }
  get hoverArray() {
    return this.__hoverArray.get();
  }
  set hoverArray(f14) {
    this.__hoverArray.set(f14);
  }
  get hoverColorArray() {
    return this.__hoverColorArray.get();
  }
  set hoverColorArray(e14) {
    this.__hoverColorArray.set(e14);
  }
  get maxFontScale() {
    return this.__maxFontScale.get();
  }
  set maxFontScale(d14) {
    this.__maxFontScale.set(d14);
  }
  get buttonWidth() {
    return this.__buttonWidth.get();
  }
  set buttonWidth(c14) {
    this.__buttonWidth.set(c14);
  }
  get buttonHeight() {
    return this.__buttonHeight.get();
  }
  set buttonHeight(b14) {
    this.__buttonHeight.set(b14);
  }
  get isMarqueeAndFadeout() {
    return this.__isMarqueeAndFadeout.get();
  }
  set isMarqueeAndFadeout(a14) {
    this.__isMarqueeAndFadeout.set(a14);
  }
  get isSegmentFocusStyleCustomized() {
    return this.__isSegmentFocusStyleCustomized.get();
  }
  set isSegmentFocusStyleCustomized(z13) {
    this.__isSegmentFocusStyleCustomized.set(z13);
  }
  onButtonItemsSizeChange() {
    this.buttonItemsSize.forEach((x13, y13) => {
      this.buttonWidth[y13] = x13.width;
      this.buttonHeight[y13] = x13.height;
    });
  }
  changeSelectedIndexes(o13) {
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
      if (
        this.optionsArray.changeStartIndex + this.optionsArray.deleteCount >
        this.selectedIndexes[0]
      ) {
        if (this.options.type === 'tab') {
          this.selectedIndexes[0] = 0;
        } else if (this.options.type === 'capsule') {
          this.selectedIndexes = [];
        }
      } else {
        this.selectedIndexes[0] =
          this.selectedIndexes[0] -
          this.optionsArray.deleteCount +
          this.optionsArray.addLength;
      }
    } else {
      let p13 = this.selectedIndexes;
      for (let t13 = 0; t13 < this.optionsArray.deleteCount; t13++) {
        let u13 = p13.indexOf(this.optionsArray.changeStartIndex);
        let v13 = p13.map((w13) =>
          this.optionsArray.changeStartIndex &&
          w13 > this.optionsArray.changeStartIndex
            ? w13 - 1
            : w13
        );
        if (u13 !== -1) {
          v13.splice(u13, 1);
        }
        p13 = v13;
      }
      for (let q13 = 0; q13 < this.optionsArray.addLength; q13++) {
        let r13 = p13.map((s13) =>
          this.optionsArray.changeStartIndex &&
          s13 >= this.optionsArray.changeStartIndex
            ? s13 + 1
            : s13
        );
        p13 = r13;
      }
      this.selectedIndexes = p13;
    }
  }
  changeFocusIndex(n13) {
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
    if (
      this.optionsArray.changeStartIndex + this.optionsArray.deleteCount >
      this.focusIndex
    ) {
      this.focusIndex = 0;
    } else {
      this.focusIndex =
        this.focusIndex -
        this.optionsArray.deleteCount +
        this.optionsArray.addLength;
    }
  }
  onOptionsArrayChange() {
    if (this.options === void 0 || this.options.buttons === void 0) {
      return;
    }
    let m13 = Math.min(
      this.options.buttons.length,
      this.buttonItemsSize.length
    );
    if (
      this.optionsArray.changeStartIndex !== void 0 &&
      this.optionsArray.deleteCount !== void 0 &&
      this.optionsArray.addLength !== void 0
    ) {
      this.changeSelectedIndexes(m13);
      this.changeFocusIndex(m13);
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
    this.isMarqueeAndFadeout =
      this.isSegmentFocusStyleCustomized && !this.isMarqueeAndFadeout;
  }
  aboutToAppear() {
    for (let l13 = 0; l13 < this.buttonItemsRealHeight.length; l13++) {
      this.buttonItemsRealHeight[l13] = 0;
    }
  }
  getBorderRadius(j13) {
    let k13 = this.buttonBorderRadius[j13];
    if (
      this.options.type === 'capsule' &&
      this.buttonItemsSelected[this.focusIndex]
    ) {
      return {
        topStart: LengthMetrics.vp((k13.topStart?.value ?? 0) + 4),
        topEnd: LengthMetrics.vp((k13.topEnd?.value ?? 0) + 4),
        bottomStart: LengthMetrics.vp((k13.bottomStart?.value ?? 0) + 4),
        bottomEnd: LengthMetrics.vp((k13.bottomEnd?.value ?? 0) + 4),
      };
    }
    return k13;
  }
  focusStack(d13, e13 = null) {
    this.observeComponentCreation2((h13, i13) => {
      Stack.create();
      Stack.direction(this.options.direction);
      Stack.size({ width: 1, height: 1 });
      Stack.align(Alignment.Center);
    }, Stack);
    this.observeComponentCreation2((f13, g13) => {
      Stack.create();
      Stack.direction(this.options.direction);
      Stack.borderRadius(this.getBorderRadius(d13));
      Stack.size({
        width:
          this.options.type === 'capsule' &&
          this.buttonItemsSelected[this.focusIndex]
            ? this.buttonWidth[d13] + 8
            : this.buttonWidth[d13],
        height:
          this.options.type === 'capsule' &&
          this.buttonItemsSelected[this.focusIndex]
            ? this.buttonHeight[d13] + 8
            : this.buttonHeight[d13],
      });
      Stack.borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR);
      Stack.borderWidth(2);
    }, Stack);
    Stack.pop();
    Stack.pop();
  }
  calculateBorderRadius() {
    let y12 = Array.from(
      {
        length: MAX_ITEM_COUNT,
      },
      (b13, c13) => {
        return {
          topStart: LengthMetrics.vp(0),
          topEnd: LengthMetrics.vp(0),
          bottomStart: LengthMetrics.vp(0),
          bottomEnd: LengthMetrics.vp(0),
        };
      }
    );
    for (let z12 = 0; z12 < this.buttonBorderRadius.length; z12++) {
      let a13 = this.buttonItemsSize[z12].height / 2;
      if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
        y12[z12].topStart = LengthMetrics.vp(
          this.options.iconTextRadius ?? a13
        );
        y12[z12].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? a13);
        y12[z12].bottomStart = LengthMetrics.vp(
          this.options.iconTextRadius ?? a13
        );
        y12[z12].bottomEnd = LengthMetrics.vp(
          this.options.iconTextRadius ?? a13
        );
      } else {
        if (z12 === 0) {
          y12[z12].topStart = LengthMetrics.vp(
            this.options.iconTextRadius ?? a13
          );
          y12[z12].topEnd = LengthMetrics.vp(0);
          y12[z12].bottomStart = LengthMetrics.vp(
            this.options.iconTextRadius ?? a13
          );
          y12[z12].bottomEnd = LengthMetrics.vp(0);
        } else if (
          this.options.buttons &&
          z12 ===
            Math.min(this.options.buttons.length, this.buttonItemsSize.length) -
              1
        ) {
          y12[z12].topStart = LengthMetrics.vp(0);
          y12[z12].topEnd = LengthMetrics.vp(
            this.options.iconTextRadius ?? a13
          );
          y12[z12].bottomStart = LengthMetrics.vp(0);
          y12[z12].bottomEnd = LengthMetrics.vp(
            this.options.iconTextRadius ?? a13
          );
        } else {
          y12[z12].topStart = LengthMetrics.vp(0);
          y12[z12].topEnd = LengthMetrics.vp(0);
          y12[z12].bottomStart = LengthMetrics.vp(0);
          y12[z12].bottomEnd = LengthMetrics.vp(0);
        }
      }
    }
    this.buttonBorderRadius = y12;
  }
  getAccessibilityDescription(x12) {
    return typeof x12 !== undefined ? x12 : undefined;
  }
  isDefaultSelectedBgColor() {
    if (this.options.type === 'tab') {
      return (
        this.options.selectedBackgroundColor ===
        segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR
      );
    } else if (this.options.type === 'capsule') {
      return (
        this.options.selectedBackgroundColor ===
        segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR
      );
    }
    return true;
  }
  initialRender() {
    this.observeComponentCreation2((s11, t11) => {
      If.create();
      if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((t12, u12) => {
            Row.create({ space: 1 });
            Row.direction(this.options.direction);
            Row.focusScopeId(this.groupId, true);
            Row.padding(this.options.componentPadding);
            Row.onSizeChange((v12, w12) => {
              this.componentSize = { width: w12.width, height: w12.height };
            });
          }, Row);
          this.observeComponentCreation2((u11, v11) => {
            ForEach.create();
            const w11 = (x11, y11) => {
              const z11 = x11;
              this.observeComponentCreation2((a12, b12) => {
                If.create();
                if (y11 < MAX_ITEM_COUNT) {
                  this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m12, n12) => {
                      Button.createWithChild();
                      Button.type(ButtonType.Normal);
                      Button.stateEffect(false);
                      Button.hoverEffect(HoverEffect.None);
                      Button.backgroundColor(Color.Transparent);
                      Button.accessibilityLevel(z11.accessibilityLevel);
                      Button.accessibilitySelected(
                        this.options.multiply
                          ? undefined
                          : this.selectedIndexes.includes(y11)
                      );
                      Button.accessibilityChecked(
                        this.options.multiply
                          ? this.selectedIndexes.includes(y11)
                          : undefined
                      );
                      Button.accessibilityDescription(
                        this.getAccessibilityDescription(
                          z11.accessibilityDescription
                        )
                      );
                      Button.direction(this.options.direction);
                      Button.borderRadius(this.buttonBorderRadius[y11]);
                      Button.scale({
                        x:
                          this.options.type === 'capsule' &&
                          (this.options.multiply ?? false)
                            ? 1
                            : this.zoomScaleArray[y11],
                        y:
                          this.options.type === 'capsule' &&
                          (this.options.multiply ?? false)
                            ? 1
                            : this.zoomScaleArray[y11],
                      });
                      Button.layoutWeight(1);
                      Button.padding(0);
                      Button.onSizeChange((r12, s12) => {
                        this.buttonItemsSize[y11] = {
                          width: s12.width,
                          height: this.buttonItemsSize[y11].height,
                        };
                        if (s12.width) {
                          this.buttonItemsPosition[y11] = {
                            start: LengthMetrics.vp(
                              Number.parseFloat(
                                this.options.componentPadding.toString()
                              ) +
                                (Number.parseFloat(s12.width.toString()) + 1) *
                                  y11
                            ),
                            top: LengthMetrics.px(
                              Math.floor(
                                this.getUIContext().vp2px(
                                  Number.parseFloat(
                                    this.options.componentPadding.toString()
                                  )
                                )
                              )
                            ),
                          };
                        }
                      });
                      ViewStackProcessor.visualState('normal');
                      Button.overlay(undefined);
                      ViewStackProcessor.visualState('focused');
                      Button.overlay(
                        {
                          builder: () => {
                            this.focusStack.call(this, y11);
                          },
                        },
                        {
                          align: Alignment.Center,
                        }
                      );
                      ViewStackProcessor.visualState();
                      Button.onFocus(() => {
                        this.focusIndex = y11;
                        if (this.isSegmentFocusStyleCustomized) {
                          this.customizeSegmentFocusStyle(y11);
                        }
                      });
                      Button.onBlur(() => {
                        this.focusIndex = -1;
                        this.hoverColorArray[y11].hoverColor =
                          Color.Transparent;
                      });
                      Gesture.create(GesturePriority.Low);
                      TapGesture.create();
                      TapGesture.onAction(() => {
                        if (this.onItemClicked) {
                          this.onItemClicked(y11);
                        }
                        if (
                          this.options.type === 'capsule' &&
                          (this.options.multiply ?? false)
                        ) {
                          if (this.selectedIndexes.indexOf(y11) === -1) {
                            this.selectedIndexes.push(y11);
                          } else {
                            this.selectedIndexes.splice(
                              this.selectedIndexes.indexOf(y11),
                              1
                            );
                          }
                        } else {
                          this.selectedIndexes[0] = y11;
                        }
                      });
                      TapGesture.pop();
                      Gesture.pop();
                      Button.onTouch((q12) => {
                        if (this.isSegmentFocusStyleCustomized) {
                          this.getUIContext().getFocusController().clearFocus();
                        }
                        if (q12.source !== SourceType.TouchScreen) {
                          return;
                        }
                        if (q12.type === TouchType.Down) {
                          Context.animateTo(
                            {
                              curve: curves.interpolatingSpring(10, 1, 410, 38),
                            },
                            () => {
                              this.zoomScaleArray[y11] = 0.95;
                            }
                          );
                        } else if (
                          q12.type === TouchType.Up ||
                          q12.type === TouchType.Cancel
                        ) {
                          Context.animateTo(
                            {
                              curve: curves.interpolatingSpring(10, 1, 410, 38),
                            },
                            () => {
                              this.zoomScaleArray[y11] = 1;
                            }
                          );
                        }
                      });
                      Button.onHover((p12) => {
                        this.hoverArray[y11] = p12;
                        if (p12) {
                          Context.animateTo(
                            { duration: 250, curve: Curve.Friction },
                            () => {
                              this.hoverColorArray[y11].hoverColor =
                                this.isSegmentFocusStyleCustomized &&
                                this.focusIndex === y11
                                  ? segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR
                                  : segmentButtonTheme.HOVER_COLOR;
                            }
                          );
                        } else {
                          Context.animateTo(
                            { duration: 250, curve: Curve.Friction },
                            () => {
                              this.hoverColorArray[y11].hoverColor =
                                this.isSegmentFocusStyleCustomized &&
                                this.focusIndex === y11
                                  ? segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR
                                  : Color.Transparent;
                            }
                          );
                        }
                      });
                      Button.onMouse((o12) => {
                        switch (o12.action) {
                          case MouseAction.Press:
                            Context.animateTo(
                              { curve: curves.springMotion(0.347, 0.99) },
                              () => {
                                this.zoomScaleArray[y11] = 0.95;
                              }
                            );
                            Context.animateTo(
                              { duration: 100, curve: Curve.Sharp },
                              () => {
                                this.pressArray[y11] = true;
                              }
                            );
                            break;
                          case MouseAction.Release:
                            Context.animateTo(
                              { curve: curves.springMotion(0.347, 0.99) },
                              () => {
                                this.zoomScaleArray[y11] = 1;
                              }
                            );
                            Context.animateTo(
                              { duration: 100, curve: Curve.Sharp },
                              () => {
                                this.pressArray[y11] = false;
                              }
                            );
                            break;
                        }
                      });
                    }, Button);
                    this.observeComponentCreation2((g12, h12) => {
                      __Common__.create();
                      __Common__.onSizeChange((i12, j12) => {
                        this.buttonItemsRealHeight[y11] = j12.height;
                        let k12 = Math.max(
                          ...this.buttonItemsRealHeight.slice(
                            0,
                            this.options.buttons
                              ? this.options.buttons.length
                              : 0
                          )
                        );
                        for (
                          let l12 = 0;
                          l12 < this.buttonItemsSize.length;
                          l12++
                        ) {
                          this.buttonItemsSize[l12] = {
                            width: this.buttonItemsSize[l12].width,
                            height: k12,
                          };
                        }
                        this.calculateBorderRadius();
                      });
                    }, __Common__);
                    {
                      this.observeComponentCreation2(
                        (c12, d12) => {
                          if (d12) {
                            let e12 = new SegmentButtonItem(
                              this,
                              {
                                isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                                isSegmentFocusStyleCustomized:
                                  this.isSegmentFocusStyleCustomized,
                                selectedIndexes: this.__selectedIndexes,
                                focusIndex: this.__focusIndex,
                                index: y11,
                                itemOptions: z11,
                                options: this.options,
                                property: this.buttonItemProperty[y11],
                                groupId: this.groupId,
                                maxFontScale: this.maxFontScale,
                                hover: this.hoverArray[y11],
                              },
                              undefined,
                              c12,
                              () => {},
                              {
                                page: 'library/src/main/ets/components/MainPage.ets',
                                line: 921,
                                col: 15,
                              }
                            );
                            ViewPU.create(e12);
                            let f12 = () => {
                              return {
                                isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                                isSegmentFocusStyleCustomized:
                                  this.isSegmentFocusStyleCustomized,
                                selectedIndexes: this.selectedIndexes,
                                focusIndex: this.focusIndex,
                                index: y11,
                                itemOptions: z11,
                                options: this.options,
                                property: this.buttonItemProperty[y11],
                                groupId: this.groupId,
                                maxFontScale: this.maxFontScale,
                                hover: this.hoverArray[y11],
                              };
                            };
                            e12.paramsGenerator_ = f12;
                          } else {
                            this.updateStateVarsOfChildByElmtId(c12, {
                              isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                              isSegmentFocusStyleCustomized:
                                this.isSegmentFocusStyleCustomized,
                              index: y11,
                              itemOptions: z11,
                              options: this.options,
                              property: this.buttonItemProperty[y11],
                              maxFontScale: this.maxFontScale,
                              hover: this.hoverArray[y11],
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
            this.forEachUpdateFunction(
              u11,
              this.optionsArray,
              w11,
              undefined,
              true,
              false
            );
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
  customizeSegmentFocusStyle(r11) {
    if (
      this.selectedIndexes !== void 0 &&
      this.selectedIndexes.length !== 0 &&
      this.selectedIndexes[0] === r11
    ) {
      this.hoverColorArray[r11].hoverColor = this.isDefaultSelectedBgColor()
        ? segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR
        : this.options.selectedBackgroundColor;
    } else {
      this.hoverColorArray[r11].hoverColor =
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
  constructor(t10, u10, v10, w10 = -1, x10 = undefined, y10) {
    super(t10, v10, w10, y10);
    if (typeof x10 === 'function') {
      this.paramsGenerator_ = x10;
    }
    this.__options = new SynchedPropertyNesedObjectPU(
      u10.options,
      this,
      'options'
    );
    this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(
      u10.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.onItemClicked = undefined;
    this.__maxFontScale = new SynchedPropertyObjectOneWayPU(
      u10.maxFontScale,
      this,
      'maxFontScale'
    );
    this.__componentSize = new ObservedPropertyObjectPU(
      { width: 0, height: 0 },
      this,
      'componentSize'
    );
    this.addProvidedVar('componentSize', this.__componentSize, false);
    this.__buttonBorderRadius = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: MAX_ITEM_COUNT,
        },
        (p11, q11) => {
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
      Array.from({ length: MAX_ITEM_COUNT }, (n11, o11) => {
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
        (l11, m11) => {
          return {};
        }
      ),
      this,
      'buttonItemsPosition'
    );
    this.addProvidedVar(
      'buttonItemsPosition',
      this.__buttonItemsPosition,
      false
    );
    this.__buttonItemsSelected = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (j11, k11) => false),
      this,
      'buttonItemsSelected'
    );
    this.addProvidedVar(
      'buttonItemsSelected',
      this.__buttonItemsSelected,
      false
    );
    this.__buttonItemProperty = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: MAX_ITEM_COUNT,
        },
        (h11, i11) => new ItemProperty()
      ),
      this,
      'buttonItemProperty'
    );
    this.addProvidedVar('buttonItemProperty', this.__buttonItemProperty, false);
    this.__focusIndex = new ObservedPropertySimplePU(-1, this, 'focusIndex');
    this.addProvidedVar('focusIndex', this.__focusIndex, false);
    this.__selectedItemPosition = new ObservedPropertyObjectPU(
      {},
      this,
      'selectedItemPosition'
    );
    this.addProvidedVar(
      'selectedItemPosition',
      this.__selectedItemPosition,
      false
    );
    this.__zoomScaleArray = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (f11, g11) => 1.0),
      this,
      'zoomScaleArray'
    );
    this.addProvidedVar('zoomScaleArray', this.__zoomScaleArray, false);
    this.__pressArray = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (d11, e11) => false),
      this,
      'pressArray'
    );
    this.__hoverArray = new ObservedPropertyObjectPU(
      Array.from({ length: MAX_ITEM_COUNT }, (b11, c11) => false),
      this,
      'hoverArray'
    );
    this.__hoverColorArray = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: MAX_ITEM_COUNT,
        },
        (z10, a11) => new HoverColorProperty()
      ),
      this,
      'hoverColorArray'
    );
    this.doSelectedChangeAnimate = false;
    this.isCurrentPositionSelected = false;
    this.panGestureStartPoint = { x: 0, y: 0 };
    this.isPanGestureMoved = false;
    this.__shouldMirror = new ObservedPropertySimplePU(
      false,
      this,
      'shouldMirror'
    );
    this.isSegmentFocusStyleCustomized =
      segmentButtonTheme.SEGMENT_FOCUS_STYLE_CUSTOMIZED;
    this.isGestureInProgress = false;
    this.setInitiallyProvidedValue(u10);
    this.declareWatch('options', this.onOptionsChange);
    this.declareWatch('selectedIndexes', this.onSelectedChange);
    this.declareWatch('buttonItemsPosition', this.onItemsPositionChange);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(s10) {
    this.__options.set(s10.options);
    if (s10.onItemClicked !== undefined) {
      this.onItemClicked = s10.onItemClicked;
    }
    if (s10.maxFontScale === undefined) {
      this.__maxFontScale.set(DEFAULT_MAX_FONT_SCALE);
    }
    if (s10.componentSize !== undefined) {
      this.componentSize = s10.componentSize;
    }
    if (s10.buttonBorderRadius !== undefined) {
      this.buttonBorderRadius = s10.buttonBorderRadius;
    }
    if (s10.buttonItemsSize !== undefined) {
      this.buttonItemsSize = s10.buttonItemsSize;
    }
    if (s10.buttonItemsPosition !== undefined) {
      this.buttonItemsPosition = s10.buttonItemsPosition;
    }
    if (s10.buttonItemsSelected !== undefined) {
      this.buttonItemsSelected = s10.buttonItemsSelected;
    }
    if (s10.buttonItemProperty !== undefined) {
      this.buttonItemProperty = s10.buttonItemProperty;
    }
    if (s10.focusIndex !== undefined) {
      this.focusIndex = s10.focusIndex;
    }
    if (s10.selectedItemPosition !== undefined) {
      this.selectedItemPosition = s10.selectedItemPosition;
    }
    if (s10.zoomScaleArray !== undefined) {
      this.zoomScaleArray = s10.zoomScaleArray;
    }
    if (s10.pressArray !== undefined) {
      this.pressArray = s10.pressArray;
    }
    if (s10.hoverArray !== undefined) {
      this.hoverArray = s10.hoverArray;
    }
    if (s10.hoverColorArray !== undefined) {
      this.hoverColorArray = s10.hoverColorArray;
    }
    if (s10.doSelectedChangeAnimate !== undefined) {
      this.doSelectedChangeAnimate = s10.doSelectedChangeAnimate;
    }
    if (s10.isCurrentPositionSelected !== undefined) {
      this.isCurrentPositionSelected = s10.isCurrentPositionSelected;
    }
    if (s10.panGestureStartPoint !== undefined) {
      this.panGestureStartPoint = s10.panGestureStartPoint;
    }
    if (s10.isPanGestureMoved !== undefined) {
      this.isPanGestureMoved = s10.isPanGestureMoved;
    }
    if (s10.shouldMirror !== undefined) {
      this.shouldMirror = s10.shouldMirror;
    }
    if (s10.isSegmentFocusStyleCustomized !== undefined) {
      this.isSegmentFocusStyleCustomized = s10.isSegmentFocusStyleCustomized;
    }
    if (s10.isGestureInProgress !== undefined) {
      this.isGestureInProgress = s10.isGestureInProgress;
    }
  }
  updateStateVars(r10) {
    this.__options.set(r10.options);
    this.__maxFontScale.reset(r10.maxFontScale);
  }
  purgeVariableDependenciesOnElmtId(q10) {
    this.__options.purgeDependencyOnElmtId(q10);
    this.__selectedIndexes.purgeDependencyOnElmtId(q10);
    this.__maxFontScale.purgeDependencyOnElmtId(q10);
    this.__componentSize.purgeDependencyOnElmtId(q10);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(q10);
    this.__buttonItemsSize.purgeDependencyOnElmtId(q10);
    this.__buttonItemsPosition.purgeDependencyOnElmtId(q10);
    this.__buttonItemsSelected.purgeDependencyOnElmtId(q10);
    this.__buttonItemProperty.purgeDependencyOnElmtId(q10);
    this.__focusIndex.purgeDependencyOnElmtId(q10);
    this.__selectedItemPosition.purgeDependencyOnElmtId(q10);
    this.__zoomScaleArray.purgeDependencyOnElmtId(q10);
    this.__pressArray.purgeDependencyOnElmtId(q10);
    this.__hoverArray.purgeDependencyOnElmtId(q10);
    this.__hoverColorArray.purgeDependencyOnElmtId(q10);
    this.__shouldMirror.purgeDependencyOnElmtId(q10);
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
  set selectedIndexes(p10) {
    this.__selectedIndexes.set(p10);
  }
  get maxFontScale() {
    return this.__maxFontScale.get();
  }
  set maxFontScale(o10) {
    this.__maxFontScale.set(o10);
  }
  get componentSize() {
    return this.__componentSize.get();
  }
  set componentSize(n10) {
    this.__componentSize.set(n10);
  }
  get buttonBorderRadius() {
    return this.__buttonBorderRadius.get();
  }
  set buttonBorderRadius(m10) {
    this.__buttonBorderRadius.set(m10);
  }
  get buttonItemsSize() {
    return this.__buttonItemsSize.get();
  }
  set buttonItemsSize(l10) {
    this.__buttonItemsSize.set(l10);
  }
  get buttonItemsPosition() {
    return this.__buttonItemsPosition.get();
  }
  set buttonItemsPosition(k10) {
    this.__buttonItemsPosition.set(k10);
  }
  get buttonItemsSelected() {
    return this.__buttonItemsSelected.get();
  }
  set buttonItemsSelected(j10) {
    this.__buttonItemsSelected.set(j10);
  }
  get buttonItemProperty() {
    return this.__buttonItemProperty.get();
  }
  set buttonItemProperty(i10) {
    this.__buttonItemProperty.set(i10);
  }
  get focusIndex() {
    return this.__focusIndex.get();
  }
  set focusIndex(h10) {
    this.__focusIndex.set(h10);
  }
  get selectedItemPosition() {
    return this.__selectedItemPosition.get();
  }
  set selectedItemPosition(g10) {
    this.__selectedItemPosition.set(g10);
  }
  get zoomScaleArray() {
    return this.__zoomScaleArray.get();
  }
  set zoomScaleArray(f10) {
    this.__zoomScaleArray.set(f10);
  }
  get pressArray() {
    return this.__pressArray.get();
  }
  set pressArray(e10) {
    this.__pressArray.set(e10);
  }
  get hoverArray() {
    return this.__hoverArray.get();
  }
  set hoverArray(d10) {
    this.__hoverArray.set(d10);
  }
  get hoverColorArray() {
    return this.__hoverColorArray.get();
  }
  set hoverColorArray(c10) {
    this.__hoverColorArray.set(c10);
  }
  get shouldMirror() {
    return this.__shouldMirror.get();
  }
  set shouldMirror(b10) {
    this.__shouldMirror.set(b10);
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
    this.buttonItemsSelected.forEach((z9, a10) => {
      this.buttonItemsSelected[a10] = false;
    });
    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
      this.selectedIndexes.forEach(
        (y9) => (this.buttonItemsSelected[y9] = true)
      );
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
      if (
        this.options.type === 'capsule' &&
        !(this.options.multiply ?? false)
      ) {
        this.selectedIndexes = [];
      }
    }
    let w9 = this.selectedIndexes.some((x9) => {
      return (
        x9 === void 0 ||
        x9 < 0 ||
        (this.options.buttons && x9 >= this.options.buttons.length)
      );
    });
    if (w9) {
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
  isMouseWheelScroll(v9) {
    return v9.source === SourceType.Mouse && !this.isPanGestureMoved;
  }
  isMovedFromPanGestureStartPoint(t9, u9) {
    return (
      !nearEqual(t9, this.panGestureStartPoint.x) ||
      !nearEqual(u9, this.panGestureStartPoint.y)
    );
  }
  isShouldMirror() {
    if (this.options.direction == Direction.Rtl) {
      return true;
    }
    try {
      let s9 = I18n.System.getSystemLanguage();
      if (I18n.isRTL(s9) && this.options.direction != Direction.Ltr) {
        return true;
      }
    } catch (r9) {
      console.error(
        `Ace SegmentButton getSystemLanguage, error: ${r9.toString()}`
      );
    }
    return false;
  }
  initialRender() {
    this.observeComponentCreation2((t8, u8) => {
      Stack.create();
      Stack.direction(this.options ? this.options.direction : undefined);
      Stack.onBlur(() => {
        this.focusIndex = -1;
      });
      Stack.onKeyEvent((q9) => {
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (q9.type === KeyType.Down) {
          if (
            q9.keyCode === KeyCode.KEYCODE_SPACE ||
            q9.keyCode === KeyCode.KEYCODE_ENTER ||
            q9.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER
          ) {
            if (
              this.options.type === 'capsule' &&
              (this.options.multiply ?? false)
            ) {
              if (this.selectedIndexes.indexOf(this.focusIndex) === -1) {
                this.selectedIndexes.push(this.focusIndex);
              } else {
                this.selectedIndexes.splice(
                  this.selectedIndexes.indexOf(this.focusIndex),
                  1
                );
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
      TapGesture.onAction((j9) => {
        if (this.isGestureInProgress) {
          return;
        }
        let k9 = j9.fingerList.find(Boolean);
        if (k9 === void 0) {
          return;
        }
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        let l9 = k9.localX;
        let m9 = Math.min(
          this.options.buttons.length,
          this.buttonItemsSize.length
        );
        for (let n9 = 0; n9 < m9; n9++) {
          l9 = l9 - this.buttonItemsSize[n9].width;
          if (l9 >= 0) {
            continue;
          }
          this.doSelectedChangeAnimate =
            this.selectedIndexes[0] >
            Math.min(this.options.buttons.length, this.buttonItemsSize.length)
              ? false
              : true;
          let o9 = this.isShouldMirror() ? m9 - 1 - n9 : n9;
          if (this.onItemClicked) {
            this.onItemClicked(o9);
          }
          if (
            this.options.type === 'capsule' &&
            (this.options.multiply ?? false)
          ) {
            let p9 = this.selectedIndexes.indexOf(o9);
            if (p9 === -1) {
              this.selectedIndexes.push(o9);
            } else {
              this.selectedIndexes.splice(p9, 1);
            }
          } else {
            this.selectedIndexes[0] = o9;
          }
          this.doSelectedChangeAnimate = false;
          break;
        }
      });
      TapGesture.pop();
      SwipeGesture.create();
      SwipeGesture.onAction((i9) => {
        if (
          this.options === void 0 ||
          this.options.buttons === void 0 ||
          i9.sourceTool === SourceTool.TOUCHPAD
        ) {
          return;
        }
        if (
          this.options.type === 'capsule' &&
          (this.options.multiply ?? false)
        ) {
          return;
        }
        if (this.isCurrentPositionSelected) {
          return;
        }
        if (
          Math.abs(i9.angle) < 90 &&
          this.selectedIndexes[0] !==
            Math.min(this.options.buttons.length, this.buttonItemsSize.length) -
              1
        ) {
          this.doSelectedChangeAnimate = true;
          this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
          this.doSelectedChangeAnimate = false;
        } else if (Math.abs(i9.angle) > 90 && this.selectedIndexes[0] !== 0) {
          this.doSelectedChangeAnimate = true;
          this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
          this.doSelectedChangeAnimate = false;
        }
      });
      SwipeGesture.pop();
      PanGesture.create();
      PanGesture.onActionStart((e9) => {
        this.isGestureInProgress = true;
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (
          this.options.type === 'capsule' &&
          (this.options.multiply ?? false)
        ) {
          return;
        }
        let f9 = e9.fingerList.find(Boolean);
        if (f9 === void 0) {
          return;
        }
        let g9 = f9.localX;
        this.panGestureStartPoint = { x: f9.globalX, y: f9.globalY };
        this.isPanGestureMoved = false;
        for (
          let h9 = 0;
          h9 <
          Math.min(this.options.buttons.length, this.buttonItemsSize.length);
          h9++
        ) {
          g9 = g9 - this.buttonItemsSize[h9].width;
          if (g9 < 0) {
            this.isCurrentPositionSelected =
              h9 === this.selectedIndexes[0] ? true : false;
            break;
          }
        }
      });
      PanGesture.onActionUpdate((y8) => {
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (
          this.options.type === 'capsule' &&
          (this.options.multiply ?? false)
        ) {
          return;
        }
        if (!this.isCurrentPositionSelected) {
          return;
        }
        let z8 = y8.fingerList.find(Boolean);
        if (z8 === void 0) {
          return;
        }
        let a9 = z8.localX;
        if (
          !this.isPanGestureMoved &&
          this.isMovedFromPanGestureStartPoint(z8.globalX, z8.globalY)
        ) {
          this.isPanGestureMoved = true;
        }
        for (
          let d9 = 0;
          d9 <
          Math.min(this.options.buttons.length, this.buttonItemsSize.length);
          d9++
        ) {
          a9 = a9 - this.buttonItemsSize[d9].width;
          if (a9 < 0) {
            this.doSelectedChangeAnimate = true;
            this.selectedIndexes[0] = d9;
            this.doSelectedChangeAnimate = false;
            break;
          }
        }
        this.zoomScaleArray.forEach((b9, c9) => {
          if (c9 === this.selectedIndexes[0]) {
            Context.animateTo(
              { curve: curves.interpolatingSpring(10, 1, 410, 38) },
              () => {
                this.zoomScaleArray[c9] = 0.95;
              }
            );
          } else {
            Context.animateTo(
              { curve: curves.interpolatingSpring(10, 1, 410, 38) },
              () => {
                this.zoomScaleArray[c9] = 1;
              }
            );
          }
        });
      });
      PanGesture.onActionEnd((v8) => {
        this.isGestureInProgress = false;
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (
          this.options.type === 'capsule' &&
          (this.options.multiply ?? false)
        ) {
          return;
        }
        let w8 = v8.fingerList.find(Boolean);
        if (w8 === void 0) {
          return;
        }
        if (
          !this.isPanGestureMoved &&
          this.isMovedFromPanGestureStartPoint(w8.globalX, w8.globalY)
        ) {
          this.isPanGestureMoved = true;
        }
        if (this.isMouseWheelScroll(v8)) {
          let x8 = v8.offsetX !== 0 ? v8.offsetX : v8.offsetY;
          this.doSelectedChangeAnimate = true;
          if (x8 > 0 && this.selectedIndexes[0] > 0) {
            this.selectedIndexes[0] -= 1;
          } else if (
            x8 < 0 &&
            this.selectedIndexes[0] <
              Math.min(
                this.options.buttons.length,
                this.buttonItemsSize.length
              ) -
                1
          ) {
            this.selectedIndexes[0] += 1;
          }
          this.doSelectedChangeAnimate = false;
        }
        Context.animateTo(
          { curve: curves.interpolatingSpring(10, 1, 410, 38) },
          () => {
            this.zoomScaleArray[this.selectedIndexes[0]] = 1;
          }
        );
        this.isCurrentPositionSelected = false;
      });
      PanGesture.onActionCancel(() => {
        this.isGestureInProgress = false;
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (
          this.options.type === 'capsule' &&
          (this.options.multiply ?? false)
        ) {
          return;
        }
        Context.animateTo(
          { curve: curves.interpolatingSpring(10, 1, 410, 38) },
          () => {
            this.zoomScaleArray[this.selectedIndexes[0]] = 1;
          }
        );
        this.isCurrentPositionSelected = false;
      });
      PanGesture.pop();
      GestureGroup.pop();
      Gesture.pop();
    }, Stack);
    this.observeComponentCreation2((n7, o7) => {
      If.create();
      if (this.options !== void 0 && this.options.buttons != void 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((f8, g8) => {
            If.create();
            if (
              this.options.type === 'capsule' &&
              (this.options.multiply ?? false)
            ) {
              this.ifElseBranchUpdateFunction(0, () => {
                {
                  this.observeComponentCreation2(
                    (p8, q8) => {
                      if (q8) {
                        let r8 = new MultiSelectBackground(
                          this,
                          {
                            optionsArray: this.options.buttons,
                            options: this.options,
                          },
                          undefined,
                          p8,
                          () => {},
                          {
                            page: 'library/src/main/ets/components/MainPage.ets',
                            line: 1261,
                            col: 11,
                          }
                        );
                        ViewPU.create(r8);
                        let s8 = () => {
                          return {
                            optionsArray: this.options.buttons,
                            options: this.options,
                          };
                        };
                        r8.paramsGenerator_ = s8;
                      } else {
                        this.updateStateVarsOfChildByElmtId(p8, {
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
                this.observeComponentCreation2((n8, o8) => {
                  Stack.create();
                  Stack.direction(this.options.direction);
                  Stack.size(ObservedObject.GetRawObject(this.componentSize));
                  Stack.backgroundColor(
                    this.options.backgroundColor ??
                      segmentButtonTheme.BACKGROUND_COLOR
                  );
                  Stack.borderRadius(
                    this.options.iconTextBackgroundRadius ??
                      this.componentSize.height / 2
                  );
                  Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
                }, Stack);
                this.observeComponentCreation2((h8, i8) => {
                  If.create();
                  if (
                    this.options.buttons !== void 0 &&
                    this.options.buttons.length > 1
                  ) {
                    this.ifElseBranchUpdateFunction(0, () => {
                      {
                        this.observeComponentCreation2(
                          (j8, k8) => {
                            if (k8) {
                              let l8 = new PressAndHoverEffectArray(
                                this,
                                {
                                  options: this.options,
                                  buttons: this.options.buttons,
                                  pressArray: this.__pressArray,
                                  hoverArray: this.__hoverArray,
                                  hoverColorArray: this.__hoverColorArray,
                                },
                                undefined,
                                j8,
                                () => {},
                                {
                                  page: 'library/src/main/ets/components/MainPage.ets',
                                  line: 1268,
                                  col: 15,
                                }
                              );
                              ViewPU.create(l8);
                              let m8 = () => {
                                return {
                                  options: this.options,
                                  buttons: this.options.buttons,
                                  pressArray: this.pressArray,
                                  hoverArray: this.hoverArray,
                                  hoverColorArray: this.hoverColorArray,
                                };
                              };
                              l8.paramsGenerator_ = m8;
                            } else {
                              this.updateStateVarsOfChildByElmtId(j8, {
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
          this.observeComponentCreation2((d8, e8) => {
            Stack.create();
            Context.animation({ duration: 0 });
            Stack.direction(this.options.direction);
            Stack.size(ObservedObject.GetRawObject(this.componentSize));
            Context.animation(null);
            Stack.borderRadius(
              (this.options.type === 'capsule' &&
              (this.options.multiply ?? false)
                ? this.options.iconTextRadius
                : this.options.iconTextBackgroundRadius) ??
                this.componentSize.height / 2
            );
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((t7, u7) => {
            If.create();
            if (
              this.options.type === 'capsule' &&
              (this.options.multiply ?? false)
            ) {
              this.ifElseBranchUpdateFunction(0, () => {
                {
                  this.observeComponentCreation2(
                    (z7, a8) => {
                      if (a8) {
                        let b8 = new MultiSelectItemArray(
                          this,
                          {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.__selectedIndexes,
                          },
                          undefined,
                          z7,
                          () => {},
                          {
                            page: 'library/src/main/ets/components/MainPage.ets',
                            line: 1285,
                            col: 13,
                          }
                        );
                        ViewPU.create(b8);
                        let c8 = () => {
                          return {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.selectedIndexes,
                          };
                        };
                        b8.paramsGenerator_ = c8;
                      } else {
                        this.updateStateVarsOfChildByElmtId(z7, {
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
                    (v7, w7) => {
                      if (w7) {
                        let x7 = new SelectItem(
                          this,
                          {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.__selectedIndexes,
                          },
                          undefined,
                          v7,
                          () => {},
                          {
                            page: 'library/src/main/ets/components/MainPage.ets',
                            line: 1291,
                            col: 13,
                          }
                        );
                        ViewPU.create(x7);
                        let y7 = () => {
                          return {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.selectedIndexes,
                          };
                        };
                        x7.paramsGenerator_ = y7;
                      } else {
                        this.updateStateVarsOfChildByElmtId(v7, {
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
              (p7, q7) => {
                if (q7) {
                  let r7 = new SegmentButtonItemArrayComponent(
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
                      isSegmentFocusStyleCustomized:
                        this.isSegmentFocusStyleCustomized,
                    },
                    undefined,
                    p7,
                    () => {},
                    {
                      page: 'library/src/main/ets/components/MainPage.ets',
                      line: 1306,
                      col: 9,
                    }
                  );
                  ViewPU.create(r7);
                  let s7 = () => {
                    return {
                      pressArray: this.pressArray,
                      hoverArray: this.hoverArray,
                      hoverColorArray: this.hoverColorArray,
                      optionsArray: this.options.buttons,
                      options: this.options,
                      selectedIndexes: this.selectedIndexes,
                      maxFontScale: this.getMaxFontSize(),
                      onItemClicked: this.onItemClicked,
                      isSegmentFocusStyleCustomized:
                        this.isSegmentFocusStyleCustomized,
                    };
                  };
                  r7.paramsGenerator_ = s7;
                } else {
                  this.updateStateVarsOfChildByElmtId(p7, {
                    optionsArray: this.options.buttons,
                    options: this.options,
                    maxFontScale: this.getMaxFontSize(),
                    isSegmentFocusStyleCustomized:
                      this.isSegmentFocusStyleCustomized,
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
      return Math.max(
        Math.min(this.maxFontScale, MAX_MAX_FONT_SCALE),
        MIN_MAX_FONT_SCALE
      );
    }
    const l7 = this.getUIContext().getHostContext()?.resourceManager;
    if (!l7) {
      return DEFAULT_MAX_FONT_SCALE;
    }
    try {
      return l7.getNumber(this.maxFontScale.id);
    } catch (m7) {
      console.error(
        `Ace SegmentButton getMaxFontSize, error: ${m7.toString()}`
      );
      return DEFAULT_MAX_FONT_SCALE;
    }
  }
  getSelectedChangeCurve() {
    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
      return null;
    }
    return curves.springMotion(0.347, 0.99);
  }
  updateAnimatedProperty(e2) {
    let a5 = () => {
      this.selectedItemPosition =
        this.selectedIndexes.length === 0
          ? {}
          : this.buttonItemsPosition[this.selectedIndexes[0]];
      this.buttonItemsSelected.forEach((j7, k7) => {
        this.buttonItemProperty[k7].fontColor = j7
          ? this.options.selectedFontColor ??
            (this.options.type === 'tab'
              ? segmentButtonTheme.TAB_SELECTED_FONT_COLOR
              : segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR)
          : this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
      });
    };
    if (e2) {
      Context.animateTo({ curve: e2 }, a5);
    } else {
      a5();
    }
    this.buttonItemsSelected.forEach((z5, n6) => {
      this.buttonItemProperty[n6].fontSize = z5
        ? this.options.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE
        : this.options.fontSize ?? segmentButtonTheme.FONT_SIZE;
      this.buttonItemProperty[n6].fontWeight = z5
        ? this.options.selectedFontWeight ?? FontWeight.Medium
        : this.options.fontWeight ?? FontWeight.Regular;
      this.buttonItemProperty[n6].isSelected = z5;
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
