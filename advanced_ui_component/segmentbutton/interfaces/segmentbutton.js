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

var a6 =
  (this && this.a6) ||
  function (y13, target, key, desc) {
    var c = arguments.length,
      r =
        c < 3
          ? target
          : desc === null
          ? (desc = Object.getOwnPropertyDescriptor(target, key))
          : desc,
      d;
    if (typeof Reflect === 'object' && typeof Reflect.o4 === 'function')
      r = Reflect.o4(y13, target, key, desc);
    else
      for (var z13 = y13.length - 1; z13 >= 0; z13--)
        if ((d = y13[z13]))
          r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
  };
var b6, c6;
if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {});
}
const curves = globalThis.requireNativeModule('ohos.curves');
const KeyCode = globalThis.requireNapi('multimodalInput.keyCode').KeyCode;
const util = globalThis.requireNapi('util');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const d6 = requireNapi('i18n');
const e6 = 2;
const f6 = 5;
const g6 = 1;
const h6 = 2;
const i6 = 1;
const j6 = {
  q4: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_text_secondary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  r4: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_text_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  s4: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_foreground_contrary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  t4: {
    id: -1,
    type: 10002,
    params: ['sys.float.ohos_id_text_size_body2'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  u4: {
    id: -1,
    type: 10002,
    params: ['sys.float.ohos_id_text_size_body2'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  BACKGROUND_COLOR: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_button_normal'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  v4: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_foreground_contrary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  w4: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_emphasize'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  x4: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_focused_outline'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  y4: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_hover'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  z4: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_click_effect'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  a5: BlurStyle.NONE,
};
function z5(first, second) {
  return Math.abs(first - second) < 0.001;
}
let SegmentButtonItemOptions = class SegmentButtonItemOptions {
  constructor(options) {
    this.icon = options.icon;
    this.selectedIcon = options.selectedIcon;
    this.text = options.text;
    this.b5 = options.b5;
    this.c5 = options.c5;
    this.accessibilityLevel = options.accessibilityLevel;
    this.accessibilityDescription = options.accessibilityDescription;
  }
};
SegmentButtonItemOptions = a6([Observed], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray =
  (b6 = class SegmentButtonItemOptionsArray extends Array {
    constructor(v13) {
      super(typeof v13 === 'number' ? v13 : 0);
      this.d5 = void 0;
      this.deleteCount = void 0;
      this.e5 = void 0;
      if (typeof v13 !== 'number' && v13 !== void 0) {
        super.push(
          ...v13.map((element) => new SegmentButtonItemOptions(element))
        );
      }
    }
    push(...items) {
      if (this.length + items.length > f6) {
        console.warn('Exceeded the maximum number of elements (5).');
        return this.length;
      }
      this.d5 = this.length;
      this.deleteCount = 0;
      this.e5 = items.length;
      return super.push(
        ...items.map((element) => new SegmentButtonItemOptions(element))
      );
    }
    pop() {
      if (this.length <= e6) {
        console.warn('Below the minimum number of elements (2).');
        return void 0;
      }
      this.d5 = this.length - 1;
      this.deleteCount = 1;
      this.e5 = 0;
      return super.pop();
    }
    shift() {
      if (this.length <= e6) {
        console.warn('Below the minimum number of elements (2).');
        return void 0;
      }
      this.d5 = 0;
      this.deleteCount = 1;
      this.e5 = 0;
      return super.shift();
    }
    unshift(...items) {
      if (this.length + items.length > f6) {
        console.warn('Exceeded the maximum number of elements (5).');
        return this.length;
      }
      if (items.length > 0) {
        this.d5 = 0;
        this.deleteCount = 0;
        this.e5 = items.length;
      }
      return super.unshift(
        ...items.map((element) => new SegmentButtonItemOptions(element))
      );
    }
    splice(start, deleteCount, ...items) {
      let length =
        this.length - deleteCount < 0 ? 0 : this.length - deleteCount;
      length += items.length;
      if (length < e6) {
        console.warn('Below the minimum number of elements (2).');
        return [];
      }
      if (length > f6) {
        console.warn('Exceeded the maximum number of elements (5).');
        return [];
      }
      this.d5 = start;
      this.deleteCount = deleteCount;
      this.e5 = items.length;
      return super.splice(start, deleteCount, ...items);
    }
    static create(elements) {
      return new b6(elements);
    }
  });
SegmentButtonItemOptionsArray = b6 = a6(
  [Observed],
  SegmentButtonItemOptionsArray
);
export { SegmentButtonItemOptionsArray };
let SegmentButtonOptions = (c6 = class SegmentButtonOptions {
  get buttons() {
    return this.f5;
  }
  set buttons(val) {
    if (this.f5 !== void 0 && this.f5 !== val) {
      this.g5?.();
    }
    this.f5 = val;
  }
  constructor(options) {
    this.multiply = false;
    this.h5 = false;
    this.showIcon = false;
    this.f5 = void 0;
    this.fontColor = options.fontColor ?? j6.q4;
    this.selectedFontColor = options.selectedFontColor ?? j6.r4;
    this.fontSize = options.fontSize ?? j6.t4;
    this.selectedFontSize = options.selectedFontSize ?? j6.u4;
    this.fontWeight = options.fontWeight ?? FontWeight.Regular;
    this.selectedFontWeight = options.selectedFontWeight ?? FontWeight.Medium;
    this.backgroundColor = options.backgroundColor ?? j6.BACKGROUND_COLOR;
    this.selectedBackgroundColor = options.selectedBackgroundColor ?? j6.v4;
    this.imageSize = options.imageSize ?? { width: 24, height: 24 };
    this.buttonPadding = options.buttonPadding;
    this.textPadding = options.textPadding;
    this.type = options.type;
    this.backgroundBlurStyle = options.backgroundBlurStyle ?? j6.a5;
    this.localizedTextPadding = options.localizedTextPadding;
    this.localizedButtonPadding = options.localizedButtonPadding;
    this.direction = options.direction ?? Direction.Auto;
    this.buttons = new SegmentButtonItemOptionsArray(options.buttons);
    if (this.type === 'capsule') {
      this.multiply = options.multiply ?? false;
      this.buttons.forEach((button) => {
        this.h5 ||= button.text !== void 0;
        this.showIcon ||=
          button.icon !== void 0 || button.selectedIcon !== void 0;
      });
      if (this.h5 && this.showIcon) {
        this.i5 = 12;
        this.j5 = 14;
      }
      this.selectedFontColor = options.selectedFontColor ?? j6.s4;
      this.selectedBackgroundColor = options.selectedBackgroundColor ?? j6.w4;
    } else {
      this.h5 = true;
    }
    this.k5 = this.multiply ? 0 : 2;
  }
  static tab(options) {
    return new c6({
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
    });
  }
  static capsule(options) {
    return new c6({
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
    });
  }
});
SegmentButtonOptions = c6 = a6([Observed], SegmentButtonOptions);
export { SegmentButtonOptions };
class k6 extends ViewPU {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda = undefined,
    extraInfo
  ) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.l5 = new SynchedPropertyNesedObjectPU(
      params.optionsArray,
      this,
      'optionsArray'
    );
    this.m5 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.n5 = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.o5 = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.l5.set(params.optionsArray);
    this.m5.set(params.options);
  }
  updateStateVars(params) {
    this.l5.set(params.optionsArray);
    this.m5.set(params.options);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.l5.purgeDependencyOnElmtId(rmElmtId);
    this.m5.purgeDependencyOnElmtId(rmElmtId);
    this.n5.purgeDependencyOnElmtId(rmElmtId);
    this.o5.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.l5.aboutToBeDeleted();
    this.m5.aboutToBeDeleted();
    this.n5.aboutToBeDeleted();
    this.o5.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get optionsArray() {
    return this.l5.get();
  }
  get options() {
    return this.m5.get();
  }
  get buttonBorderRadius() {
    return this.n5.get();
  }
  set buttonBorderRadius(newValue) {
    this.n5.set(newValue);
  }
  get buttonItemsSize() {
    return this.o5.get();
  }
  set buttonItemsSize(newValue) {
    this.o5.set(newValue);
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create({ space: 1 });
      Row.direction(this.options.direction);
      Row.padding(this.options.k5);
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      ForEach.create();
      const forEachItemGenFunction = (_item, index) => {
        const n13 = _item;
        this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (index < f6) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((elmtId, isInitialRender) => {
                Stack.create();
                Stack.direction(this.options.direction);
                Stack.layoutWeight(1);
                Stack.height(this.buttonItemsSize[index].height);
                Stack.backgroundColor(
                  this.options.backgroundColor ?? j6.BACKGROUND_COLOR
                );
                Stack.borderRadius(this.buttonBorderRadius[index]);
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
        elmtId,
        this.optionsArray,
        forEachItemGenFunction,
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
class l6 extends ViewPU {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda = undefined,
    extraInfo
  ) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.l5 = new SynchedPropertyNesedObjectPU(
      params.optionsArray,
      this,
      'optionsArray'
    );
    this.m5 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.h4 = new SynchedPropertyObjectTwoWayPU(
      params.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.o5 = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.p5 = this.initializeConsume(
      'selectedItemPosition',
      'selectedItemPosition'
    );
    this.q5 = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
    this.n5 = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.l5.set(params.optionsArray);
    this.m5.set(params.options);
  }
  updateStateVars(params) {
    this.l5.set(params.optionsArray);
    this.m5.set(params.options);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.l5.purgeDependencyOnElmtId(rmElmtId);
    this.m5.purgeDependencyOnElmtId(rmElmtId);
    this.h4.purgeDependencyOnElmtId(rmElmtId);
    this.o5.purgeDependencyOnElmtId(rmElmtId);
    this.p5.purgeDependencyOnElmtId(rmElmtId);
    this.q5.purgeDependencyOnElmtId(rmElmtId);
    this.n5.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.l5.aboutToBeDeleted();
    this.m5.aboutToBeDeleted();
    this.h4.aboutToBeDeleted();
    this.o5.aboutToBeDeleted();
    this.p5.aboutToBeDeleted();
    this.q5.aboutToBeDeleted();
    this.n5.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get optionsArray() {
    return this.l5.get();
  }
  get options() {
    return this.m5.get();
  }
  get selectedIndexes() {
    return this.h4.get();
  }
  set selectedIndexes(newValue) {
    this.h4.set(newValue);
  }
  get buttonItemsSize() {
    return this.o5.get();
  }
  set buttonItemsSize(newValue) {
    this.o5.set(newValue);
  }
  get selectedItemPosition() {
    return this.p5.get();
  }
  set selectedItemPosition(newValue) {
    this.p5.set(newValue);
  }
  get zoomScaleArray() {
    return this.q5.get();
  }
  set zoomScaleArray(newValue) {
    this.q5.set(newValue);
  }
  get buttonBorderRadius() {
    return this.n5.get();
  }
  set buttonBorderRadius(newValue) {
    this.n5.set(newValue);
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (
        this.selectedIndexes !== void 0 &&
        this.selectedIndexes.length !== 0
      ) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.options.direction);
            Stack.borderRadius(
              this.buttonBorderRadius[this.selectedIndexes[0]]
            );
            Stack.size(this.buttonItemsSize[this.selectedIndexes[0]]);
            Stack.backgroundColor(
              this.options.selectedBackgroundColor ??
                (this.options.type === 'tab' ? j6.v4 : j6.w4)
            );
            Stack.position(
              ObservedObject.GetRawObject(this.selectedItemPosition)
            );
            Stack.scale({
              x: this.zoomScaleArray[this.selectedIndexes[0]],
              y: this.zoomScaleArray[this.selectedIndexes[0]],
            });
            Stack.shadow(ShadowStyle.OUTER_DEFAULT_XS);
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
class m6 extends ViewPU {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda = undefined,
    extraInfo
  ) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.l5 = new SynchedPropertyNesedObjectPU(
      params.optionsArray,
      this,
      'optionsArray'
    );
    this.m5 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.h4 = new SynchedPropertyObjectTwoWayPU(
      params.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.o5 = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.q5 = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
    this.n5 = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.r5 = new ObservedPropertyObjectPU(
      Array.from({ length: f6 }, (f13, index) => Color.Transparent),
      this,
      'multiColor'
    );
    this.setInitiallyProvidedValue(params);
    this.declareWatch('options', this.onOptionsChange);
    this.declareWatch('selectedIndexes', this.onSelectedChange);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.l5.set(params.optionsArray);
    this.m5.set(params.options);
    if (params.multiColor !== undefined) {
      this.multiColor = params.multiColor;
    }
  }
  updateStateVars(params) {
    this.l5.set(params.optionsArray);
    this.m5.set(params.options);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.l5.purgeDependencyOnElmtId(rmElmtId);
    this.m5.purgeDependencyOnElmtId(rmElmtId);
    this.h4.purgeDependencyOnElmtId(rmElmtId);
    this.o5.purgeDependencyOnElmtId(rmElmtId);
    this.q5.purgeDependencyOnElmtId(rmElmtId);
    this.n5.purgeDependencyOnElmtId(rmElmtId);
    this.r5.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.l5.aboutToBeDeleted();
    this.m5.aboutToBeDeleted();
    this.h4.aboutToBeDeleted();
    this.o5.aboutToBeDeleted();
    this.q5.aboutToBeDeleted();
    this.n5.aboutToBeDeleted();
    this.r5.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get optionsArray() {
    return this.l5.get();
  }
  get options() {
    return this.m5.get();
  }
  get selectedIndexes() {
    return this.h4.get();
  }
  set selectedIndexes(newValue) {
    this.h4.set(newValue);
  }
  get buttonItemsSize() {
    return this.o5.get();
  }
  set buttonItemsSize(newValue) {
    this.o5.set(newValue);
  }
  get zoomScaleArray() {
    return this.q5.get();
  }
  set zoomScaleArray(newValue) {
    this.q5.set(newValue);
  }
  get buttonBorderRadius() {
    return this.n5.get();
  }
  set buttonBorderRadius(newValue) {
    this.n5.set(newValue);
  }
  get multiColor() {
    return this.r5.get();
  }
  set multiColor(newValue) {
    this.r5.set(newValue);
  }
  onOptionsChange() {
    for (let d13 = 0; d13 < this.selectedIndexes.length; d13++) {
      this.multiColor[this.selectedIndexes[d13]] =
        this.options.selectedBackgroundColor ?? j6.w4;
    }
  }
  onSelectedChange() {
    for (let c13 = 0; c13 < f6; c13++) {
      this.multiColor[c13] = Color.Transparent;
    }
    for (let b13 = 0; b13 < this.selectedIndexes.length; b13++) {
      this.multiColor[this.selectedIndexes[b13]] =
        this.options.selectedBackgroundColor ?? j6.w4;
    }
  }
  aboutToAppear() {
    for (let a13 = 0; a13 < this.selectedIndexes.length; a13++) {
      this.multiColor[this.selectedIndexes[a13]] =
        this.options.selectedBackgroundColor ?? j6.w4;
    }
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create({ space: 1 });
      Row.direction(this.options.direction);
      Row.padding(this.options.k5);
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      ForEach.create();
      const forEachItemGenFunction = (_item, index) => {
        const v12 = _item;
        this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (index < f6) {
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
      this.forEachUpdateFunction(
        elmtId,
        this.optionsArray,
        forEachItemGenFunction,
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
class n6 extends ViewPU {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda = undefined,
    extraInfo
  ) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.h4 = new SynchedPropertyObjectTwoWayPU(
      params.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.s5 = new SynchedPropertySimpleTwoWayPU(
      params.focusIndex,
      this,
      'focusIndex'
    );
    this.t5 = new SynchedPropertyObjectOneWayPU(
      params.maxFontScale,
      this,
      'maxFontScale'
    );
    this.u5 = new SynchedPropertyNesedObjectPU(
      params.itemOptions,
      this,
      'itemOptions'
    );
    this.m5 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.v5 = new SynchedPropertyNesedObjectPU(
      params.property,
      this,
      'property'
    );
    this.w5 = new SynchedPropertySimpleOneWayPU(params.index, this, 'index');
    this.groupId = '';
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.u5.set(params.itemOptions);
    this.m5.set(params.options);
    this.v5.set(params.property);
    if (params.groupId !== undefined) {
      this.groupId = params.groupId;
    }
  }
  updateStateVars(params) {
    this.t5.reset(params.maxFontScale);
    this.u5.set(params.itemOptions);
    this.m5.set(params.options);
    this.v5.set(params.property);
    this.w5.reset(params.index);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.h4.purgeDependencyOnElmtId(rmElmtId);
    this.s5.purgeDependencyOnElmtId(rmElmtId);
    this.t5.purgeDependencyOnElmtId(rmElmtId);
    this.u5.purgeDependencyOnElmtId(rmElmtId);
    this.m5.purgeDependencyOnElmtId(rmElmtId);
    this.v5.purgeDependencyOnElmtId(rmElmtId);
    this.w5.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.h4.aboutToBeDeleted();
    this.s5.aboutToBeDeleted();
    this.t5.aboutToBeDeleted();
    this.u5.aboutToBeDeleted();
    this.m5.aboutToBeDeleted();
    this.v5.aboutToBeDeleted();
    this.w5.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get selectedIndexes() {
    return this.h4.get();
  }
  set selectedIndexes(newValue) {
    this.h4.set(newValue);
  }
  get focusIndex() {
    return this.s5.get();
  }
  set focusIndex(newValue) {
    this.s5.set(newValue);
  }
  get maxFontScale() {
    return this.t5.get();
  }
  set maxFontScale(newValue) {
    this.t5.set(newValue);
  }
  get itemOptions() {
    return this.u5.get();
  }
  get options() {
    return this.m5.get();
  }
  get property() {
    return this.v5.get();
  }
  get index() {
    return this.w5.get();
  }
  set index(newValue) {
    this.w5.set(newValue);
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
      this.options.h5 &&
      this.options.showIcon
    ) {
      return {
        top: LengthMetrics.vp(6),
        bottom: LengthMetrics.vp(6),
        start: LengthMetrics.vp(8),
        end: LengthMetrics.vp(8),
      };
    }
    return {
      top: LengthMetrics.vp(4),
      bottom: LengthMetrics.vp(4),
      start: LengthMetrics.vp(8),
      end: LengthMetrics.vp(8),
    };
  }
  getAccessibilityText() {
    if (this.selectedIndexes.includes(this.index) && this.itemOptions.c5) {
      return typeof this.itemOptions.c5 === 'string'
        ? this.itemOptions.c5
        : getContext(this).resourceManager.getStringSync(
            this.itemOptions.c5.id
          );
    } else if (this.itemOptions.b5) {
      return typeof this.itemOptions.b5 === 'string'
        ? this.itemOptions.b5
        : getContext(this).resourceManager.getStringSync(
            this.itemOptions.b5.id
          );
    }
    return '';
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
      Column.constraintSize({ minHeight: 28 });
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.options.showIcon) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(
              this.property.isSelected
                ? this.itemOptions.selectedIcon
                : this.itemOptions.icon
            );
            Image.direction(this.options.direction);
            Image.size(this.options.imageSize ?? { width: 24, height: 24 });
            Image.focusable(!this.options.h5);
            Image.draggable(false);
            Image.fillColor(
              this.property.isSelected
                ? this.options.selectedFontColor ?? j6.s4
                : this.options.fontColor ?? j6.q4
            );
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
      if (this.options.h5) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.itemOptions.text);
            Text.direction(this.options.direction);
            Text.fontColor(this.property.fontColor);
            Text.fontWeight(this.property.fontWeight);
            Text.fontSize(this.property.fontSize);
            Text.minFontSize(9);
            Text.maxFontSize(this.property.fontSize);
            Text.maxFontScale(ObservedObject.GetRawObject(this.maxFontScale));
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(1);
            Text.textAlign(TextAlign.Center);
            Text.focusable(true);
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
let o6 = class HoverColorProperty {
  constructor() {
    this.x5 = Color.Transparent;
  }
};
o6 = a6([Observed], o6);
class p6 extends ViewPU {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda = undefined,
    extraInfo
  ) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.o5 = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.y5 = new SynchedPropertySimpleOneWayPU(params.press, this, 'press');
    this.s6 = new SynchedPropertySimpleOneWayPU(params.hover, this, 'hover');
    this.t6 = new SynchedPropertyNesedObjectPU(
      params.colorProperty,
      this,
      'colorProperty'
    );
    this.n5 = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.m5 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.pressIndex = 0;
    this.pressColor = j6.z4;
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.t6.set(params.colorProperty);
    this.m5.set(params.options);
    if (params.pressIndex !== undefined) {
      this.pressIndex = params.pressIndex;
    }
    if (params.pressColor !== undefined) {
      this.pressColor = params.pressColor;
    }
  }
  updateStateVars(params) {
    this.y5.reset(params.press);
    this.s6.reset(params.hover);
    this.t6.set(params.colorProperty);
    this.m5.set(params.options);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.o5.purgeDependencyOnElmtId(rmElmtId);
    this.y5.purgeDependencyOnElmtId(rmElmtId);
    this.s6.purgeDependencyOnElmtId(rmElmtId);
    this.t6.purgeDependencyOnElmtId(rmElmtId);
    this.n5.purgeDependencyOnElmtId(rmElmtId);
    this.m5.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.o5.aboutToBeDeleted();
    this.y5.aboutToBeDeleted();
    this.s6.aboutToBeDeleted();
    this.t6.aboutToBeDeleted();
    this.n5.aboutToBeDeleted();
    this.m5.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get buttonItemsSize() {
    return this.o5.get();
  }
  set buttonItemsSize(newValue) {
    this.o5.set(newValue);
  }
  get press() {
    return this.y5.get();
  }
  set press(newValue) {
    this.y5.set(newValue);
  }
  get hover() {
    return this.s6.get();
  }
  set hover(newValue) {
    this.s6.set(newValue);
  }
  get colorProperty() {
    return this.t6.get();
  }
  get buttonBorderRadius() {
    return this.n5.get();
  }
  set buttonBorderRadius(newValue) {
    this.n5.set(newValue);
  }
  get options() {
    return this.m5.get();
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Stack.create();
      Stack.direction(this.options.direction);
      Stack.size(this.buttonItemsSize[this.pressIndex]);
      Stack.backgroundColor(
        this.press && this.hover ? this.pressColor : this.colorProperty.x5
      );
      Stack.borderRadius(this.buttonBorderRadius[this.pressIndex]);
    }, Stack);
    Stack.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class q6 extends ViewPU {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda = undefined,
    extraInfo
  ) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.l5 = new SynchedPropertyNesedObjectPU(
      params.optionsArray,
      this,
      'optionsArray'
    );
    this.m5 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.h4 = new SynchedPropertyObjectTwoWayPU(
      params.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.u6 = this.initializeConsume('componentSize', 'componentSize');
    this.n5 = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.o5 = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.v6 = this.initializeConsume(
      'buttonItemsPosition',
      'buttonItemsPosition'
    );
    this.s5 = this.initializeConsume('focusIndex', 'focusIndex');
    this.q5 = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
    this.w6 = this.initializeConsume(
      'buttonItemProperty',
      'buttonItemProperty'
    );
    this.x6 = this.initializeConsume(
      'buttonItemsSelected',
      'buttonItemsSelected'
    );
    this.y6 = new SynchedPropertyObjectTwoWayPU(
      params.pressArray,
      this,
      'pressArray'
    );
    this.z6 = new SynchedPropertyObjectTwoWayPU(
      params.hoverArray,
      this,
      'hoverArray'
    );
    this.a7 = new SynchedPropertyObjectTwoWayPU(
      params.hoverColorArray,
      this,
      'hoverColorArray'
    );
    this.t5 = new SynchedPropertyObjectOneWayPU(
      params.maxFontScale,
      this,
      'maxFontScale'
    );
    this.b7 = new ObservedPropertyObjectPU(
      Array.from({ length: f6 }, (h12, index) => 0),
      this,
      'buttonWidth'
    );
    this.c7 = new ObservedPropertyObjectPU(
      Array.from({ length: f6 }, (g12, index) => 0),
      this,
      'buttonHeight'
    );
    this.buttonItemsRealHeight = Array.from({ length: f6 }, (f12, index) => 0);
    this.groupId = util.generateRandomUUID(true);
    this.setInitiallyProvidedValue(params);
    this.declareWatch('optionsArray', this.onOptionsArrayChange);
    this.declareWatch('options', this.onOptionsChange);
    this.declareWatch('buttonItemsSize', this.onButtonItemsSizeChange);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.l5.set(params.optionsArray);
    this.m5.set(params.options);
    if (params.buttonWidth !== undefined) {
      this.buttonWidth = params.buttonWidth;
    }
    if (params.buttonHeight !== undefined) {
      this.buttonHeight = params.buttonHeight;
    }
    if (params.buttonItemsRealHeight !== undefined) {
      this.buttonItemsRealHeight = params.buttonItemsRealHeight;
    }
    if (params.groupId !== undefined) {
      this.groupId = params.groupId;
    }
  }
  updateStateVars(params) {
    this.l5.set(params.optionsArray);
    this.m5.set(params.options);
    this.t5.reset(params.maxFontScale);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.l5.purgeDependencyOnElmtId(rmElmtId);
    this.m5.purgeDependencyOnElmtId(rmElmtId);
    this.h4.purgeDependencyOnElmtId(rmElmtId);
    this.u6.purgeDependencyOnElmtId(rmElmtId);
    this.n5.purgeDependencyOnElmtId(rmElmtId);
    this.o5.purgeDependencyOnElmtId(rmElmtId);
    this.v6.purgeDependencyOnElmtId(rmElmtId);
    this.s5.purgeDependencyOnElmtId(rmElmtId);
    this.q5.purgeDependencyOnElmtId(rmElmtId);
    this.w6.purgeDependencyOnElmtId(rmElmtId);
    this.x6.purgeDependencyOnElmtId(rmElmtId);
    this.y6.purgeDependencyOnElmtId(rmElmtId);
    this.z6.purgeDependencyOnElmtId(rmElmtId);
    this.a7.purgeDependencyOnElmtId(rmElmtId);
    this.t5.purgeDependencyOnElmtId(rmElmtId);
    this.b7.purgeDependencyOnElmtId(rmElmtId);
    this.c7.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.l5.aboutToBeDeleted();
    this.m5.aboutToBeDeleted();
    this.h4.aboutToBeDeleted();
    this.u6.aboutToBeDeleted();
    this.n5.aboutToBeDeleted();
    this.o5.aboutToBeDeleted();
    this.v6.aboutToBeDeleted();
    this.s5.aboutToBeDeleted();
    this.q5.aboutToBeDeleted();
    this.w6.aboutToBeDeleted();
    this.x6.aboutToBeDeleted();
    this.y6.aboutToBeDeleted();
    this.z6.aboutToBeDeleted();
    this.a7.aboutToBeDeleted();
    this.t5.aboutToBeDeleted();
    this.b7.aboutToBeDeleted();
    this.c7.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get optionsArray() {
    return this.l5.get();
  }
  get options() {
    return this.m5.get();
  }
  get selectedIndexes() {
    return this.h4.get();
  }
  set selectedIndexes(newValue) {
    this.h4.set(newValue);
  }
  get componentSize() {
    return this.u6.get();
  }
  set componentSize(newValue) {
    this.u6.set(newValue);
  }
  get buttonBorderRadius() {
    return this.n5.get();
  }
  set buttonBorderRadius(newValue) {
    this.n5.set(newValue);
  }
  get buttonItemsSize() {
    return this.o5.get();
  }
  set buttonItemsSize(newValue) {
    this.o5.set(newValue);
  }
  get buttonItemsPosition() {
    return this.v6.get();
  }
  set buttonItemsPosition(newValue) {
    this.v6.set(newValue);
  }
  get focusIndex() {
    return this.s5.get();
  }
  set focusIndex(newValue) {
    this.s5.set(newValue);
  }
  get zoomScaleArray() {
    return this.q5.get();
  }
  set zoomScaleArray(newValue) {
    this.q5.set(newValue);
  }
  get buttonItemProperty() {
    return this.w6.get();
  }
  set buttonItemProperty(newValue) {
    this.w6.set(newValue);
  }
  get buttonItemsSelected() {
    return this.x6.get();
  }
  set buttonItemsSelected(newValue) {
    this.x6.set(newValue);
  }
  get pressArray() {
    return this.y6.get();
  }
  set pressArray(newValue) {
    this.y6.set(newValue);
  }
  get hoverArray() {
    return this.z6.get();
  }
  set hoverArray(newValue) {
    this.z6.set(newValue);
  }
  get hoverColorArray() {
    return this.a7.get();
  }
  set hoverColorArray(newValue) {
    this.a7.set(newValue);
  }
  get maxFontScale() {
    return this.t5.get();
  }
  set maxFontScale(newValue) {
    this.t5.set(newValue);
  }
  get buttonWidth() {
    return this.b7.get();
  }
  set buttonWidth(newValue) {
    this.b7.set(newValue);
  }
  get buttonHeight() {
    return this.c7.get();
  }
  set buttonHeight(newValue) {
    this.c7.set(newValue);
  }
  onButtonItemsSizeChange() {
    this.buttonItemsSize.forEach((value, index) => {
      this.buttonWidth[index] = value.width;
      this.buttonHeight[index] = value.height;
    });
  }
  changeSelectedIndexes(u11) {
    if (
      this.optionsArray.d5 === void 0 ||
      this.optionsArray.deleteCount === void 0 ||
      this.optionsArray.e5 === void 0
    ) {
      return;
    }
    if (!(this.options.multiply ?? false)) {
      if (this.selectedIndexes[0] === void 0) {
        return;
      }
      if (this.selectedIndexes[0] < this.optionsArray.d5) {
        return;
      }
      if (
        this.optionsArray.d5 + this.optionsArray.deleteCount >
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
          this.optionsArray.e5;
      }
    } else {
      let v11 = this.selectedIndexes;
      for (let y11 = 0; y11 < this.optionsArray.deleteCount; y11++) {
        let z11 = v11.indexOf(this.optionsArray.d5);
        let indexes = v11.map((value) =>
          this.optionsArray.d5 && value > this.optionsArray.d5
            ? value - 1
            : value
        );
        if (z11 !== -1) {
          indexes.splice(z11, 1);
        }
        v11 = indexes;
      }
      for (let w11 = 0; w11 < this.optionsArray.e5; w11++) {
        let indexes = v11.map((value) =>
          this.optionsArray.d5 && value >= this.optionsArray.d5
            ? value + 1
            : value
        );
        v11 = indexes;
      }
      this.selectedIndexes = v11;
    }
  }
  changeFocusIndex(t11) {
    if (
      this.optionsArray.d5 === void 0 ||
      this.optionsArray.deleteCount === void 0 ||
      this.optionsArray.e5 === void 0
    ) {
      return;
    }
    if (this.focusIndex === -1) {
      return;
    }
    if (this.focusIndex < this.optionsArray.d5) {
      return;
    }
    if (
      this.optionsArray.d5 + this.optionsArray.deleteCount >
      this.focusIndex
    ) {
      this.focusIndex = 0;
    } else {
      this.focusIndex =
        this.focusIndex - this.optionsArray.deleteCount + this.optionsArray.e5;
    }
  }
  onOptionsArrayChange() {
    if (this.options === void 0 || this.options.buttons === void 0) {
      return;
    }
    let s11 = Math.min(
      this.options.buttons.length,
      this.buttonItemsSize.length
    );
    if (
      this.optionsArray.d5 !== void 0 &&
      this.optionsArray.deleteCount !== void 0 &&
      this.optionsArray.e5 !== void 0
    ) {
      this.changeSelectedIndexes(s11);
      this.changeFocusIndex(s11);
      this.optionsArray.d5 = void 0;
      this.optionsArray.deleteCount = void 0;
      this.optionsArray.e5 = void 0;
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
    if (
      this.options.type === 'capsule' &&
      this.buttonItemsSelected[this.focusIndex]
    ) {
      borderRadius.topStart = LengthMetrics.vp(
        (borderRadius.topStart?.value ?? 0) + 4
      );
      borderRadius.topEnd = LengthMetrics.vp(
        (borderRadius.topEnd?.value ?? 0) + 4
      );
      borderRadius.bottomStart = LengthMetrics.vp(
        (borderRadius.bottomStart?.value ?? 0) + 4
      );
      borderRadius.bottomEnd = LengthMetrics.vp(
        (borderRadius.bottomEnd?.value ?? 0) + 4
      );
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
        width:
          this.options.type === 'capsule' &&
          this.buttonItemsSelected[this.focusIndex]
            ? this.buttonWidth[index] + 8
            : this.buttonWidth[index],
        height:
          this.options.type === 'capsule' &&
          this.buttonItemsSelected[this.focusIndex]
            ? this.buttonHeight[index] + 8
            : this.buttonHeight[index],
      });
      Stack.borderColor(j6.x4);
      Stack.borderWidth(2);
    }, Stack);
    Stack.pop();
    Stack.pop();
  }
  calculateBorderRadius() {
    let m11 = Array.from(
      {
        length: f6,
      },
      (p11, index) => {
        return {
          topStart: LengthMetrics.vp(0),
          topEnd: LengthMetrics.vp(0),
          bottomStart: LengthMetrics.vp(0),
          bottomEnd: LengthMetrics.vp(0),
        };
      }
    );
    for (let index = 0; index < this.buttonBorderRadius.length; index++) {
      let o11 = this.buttonItemsSize[index].height / 2;
      if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
        m11[index].topStart = LengthMetrics.vp(this.options.i5 ?? o11);
        m11[index].topEnd = LengthMetrics.vp(this.options.i5 ?? o11);
        m11[index].bottomStart = LengthMetrics.vp(this.options.i5 ?? o11);
        m11[index].bottomEnd = LengthMetrics.vp(this.options.i5 ?? o11);
      } else {
        if (index === 0) {
          m11[index].topStart = LengthMetrics.vp(this.options.i5 ?? o11);
          m11[index].topEnd = LengthMetrics.vp(0);
          m11[index].bottomStart = LengthMetrics.vp(this.options.i5 ?? o11);
          m11[index].bottomEnd = LengthMetrics.vp(0);
        } else if (
          this.options.buttons &&
          index ===
            Math.min(this.options.buttons.length, this.buttonItemsSize.length) -
              1
        ) {
          m11[index].topStart = LengthMetrics.vp(0);
          m11[index].topEnd = LengthMetrics.vp(this.options.i5 ?? o11);
          m11[index].bottomStart = LengthMetrics.vp(0);
          m11[index].bottomEnd = LengthMetrics.vp(this.options.i5 ?? o11);
        } else {
          m11[index].topStart = LengthMetrics.vp(0);
          m11[index].topEnd = LengthMetrics.vp(0);
          m11[index].bottomStart = LengthMetrics.vp(0);
          m11[index].bottomEnd = LengthMetrics.vp(0);
        }
      }
    }
    this.buttonBorderRadius = m11;
  }
  getAccessibilityDescription(value) {
    if (value) {
      return typeof value === 'string'
        ? value
        : getContext(this).resourceManager.getStringSync(value.id);
    } else {
      return '';
    }
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
            Row.padding(this.options.k5);
            Row.onSizeChange((l11, newValue) => {
              this.componentSize = {
                width: newValue.width,
                height: newValue.height,
              };
            });
          }, Row);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
              const item = _item;
              this.observeComponentCreation2((elmtId, isInitialRender) => {
                If.create();
                if (index < f6) {
                  this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2(
                      (elmtId, isInitialRender) => {
                        Button.createWithChild();
                        Button.type(ButtonType.Normal);
                        Button.stateEffect(false);
                        Button.hoverEffect(HoverEffect.None);
                        Button.backgroundColor(Color.Transparent);
                        Button.accessibilityLevel(item.accessibilityLevel);
                        Button.accessibilitySelected(this.options.multiply ? undefined :
                        this.selectedIndexes.includes(index));
                        Button.accessibilityChecked(this.options.multiply ?
                        this.selectedIndexes.includes(index) : undefined);
                        Button.accessibilityDescription(
                          this.getAccessibilityDescription(
                            item.accessibilityDescription
                          )
                        );
                        Button.direction(this.options.direction);
                        Button.borderRadius(this.buttonBorderRadius[index]);
                        Button.scale({
                          x:
                            this.options.type === 'capsule' &&
                            (this.options.multiply ?? false)
                              ? 1
                              : this.zoomScaleArray[index],
                          y:
                            this.options.type === 'capsule' &&
                            (this.options.multiply ?? false)
                              ? 1
                              : this.zoomScaleArray[index],
                        });
                        Button.layoutWeight(1);
                        Button.padding(0);
                        Button.onSizeChange((j11, newValue) => {
                          this.buttonItemsSize[index] = {
                            width: newValue.width,
                            height: this.buttonItemsSize[index].height,
                          };
                          if (newValue.width) {
                            this.buttonItemsPosition[index] = {
                              start: LengthMetrics.vp(
                                Number.parseFloat(this.options.k5.toString()) +
                                  (Number.parseFloat(
                                    newValue.width.toString()
                                  ) +
                                    1) *
                                    index
                              ),
                              top: LengthMetrics.px(
                                Math.floor(
                                  this.getUIContext().vp2px(
                                    Number.parseFloat(
                                      this.options.k5.toString()
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
                              this.focusStack.call(this, index);
                            },
                          },
                          {
                            align: Alignment.Center,
                          }
                        );
                        ViewStackProcessor.visualState();
                        Button.onFocus(() => {
                          this.focusIndex = index;
                        });
                        Gesture.create(GesturePriority.Low);
                        TapGesture.create();
                        TapGesture.onAction(() => {
                          this.focusIndex = -1;
                          if (
                            this.options.type === 'capsule' &&
                            (this.options.multiply ?? false)
                          ) {
                            if (this.selectedIndexes.indexOf(index) === -1) {
                              this.selectedIndexes.push(index);
                            } else {
                              this.selectedIndexes.splice(
                                this.selectedIndexes.indexOf(index),
                                1
                              );
                            }
                          } else {
                            this.selectedIndexes[0] = index;
                          }
                        });
                        TapGesture.pop();
                        Gesture.pop();
                        Button.onTouch((event) => {
                          if (event.source !== SourceType.TouchScreen) {
                            return;
                          }
                          if (event.type === TouchType.Down) {
                            Context.animateTo(
                              {
                                curve: curves.interpolatingSpring(
                                  10,
                                  1,
                                  410,
                                  38
                                ),
                              },
                              () => {
                                this.zoomScaleArray[index] = 0.95;
                              }
                            );
                          } else if (event.type === TouchType.Up) {
                            Context.animateTo(
                              {
                                curve: curves.interpolatingSpring(
                                  10,
                                  1,
                                  410,
                                  38
                                ),
                              },
                              () => {
                                this.zoomScaleArray[index] = 1;
                              }
                            );
                          }
                        });
                        Button.onHover((isHover) => {
                          this.hoverArray[index] = isHover;
                          if (isHover) {
                            Context.animateTo(
                              { duration: 250, curve: Curve.Friction },
                              () => {
                                this.hoverColorArray[index].x5 = j6.y4;
                              }
                            );
                          } else {
                            Context.animateTo(
                              { duration: 250, curve: Curve.Friction },
                              () => {
                                this.hoverColorArray[index].x5 =
                                  Color.Transparent;
                              }
                            );
                          }
                        });
                        Button.onMouse((event) => {
                          switch (event.action) {
                            case MouseAction.Press:
                              Context.animateTo(
                                { curve: curves.springMotion(0.347, 0.99) },
                                () => {
                                  this.zoomScaleArray[index] = 0.95;
                                }
                              );
                              Context.animateTo(
                                { duration: 100, curve: Curve.Sharp },
                                () => {
                                  this.pressArray[index] = true;
                                }
                              );
                              break;
                            case MouseAction.Release:
                              Context.animateTo(
                                { curve: curves.springMotion(0.347, 0.99) },
                                () => {
                                  this.zoomScaleArray[index] = 1;
                                }
                              );
                              Context.animateTo(
                                { duration: 100, curve: Curve.Sharp },
                                () => {
                                  this.pressArray[index] = false;
                                }
                              );
                              break;
                          }
                        });
                      },
                      Button
                    );
                    this.observeComponentCreation2(
                      (elmtId, isInitialRender) => {
                        __Common__.create();
                        __Common__.onSizeChange((u10, newValue) => {
                          this.buttonItemsRealHeight[index] = newValue.height;
                          let maxHeight = Math.max(
                            ...this.buttonItemsRealHeight.slice(
                              0,
                              this.options.buttons
                                ? this.options.buttons.length
                                : 0
                            )
                          );
                          for (
                            let index = 0;
                            index < this.buttonItemsSize.length;
                            index++
                          ) {
                            this.buttonItemsSize[index] = {
                              width: this.buttonItemsSize[index].width,
                              height: maxHeight,
                            };
                          }
                          this.calculateBorderRadius();
                        });
                      },
                      __Common__
                    );
                    {
                      this.observeComponentCreation2(
                        (elmtId, isInitialRender) => {
                          if (isInitialRender) {
                            let componentCall = new n6(
                              this,
                              {
                                selectedIndexes: this.h4,
                                focusIndex: this.s5,
                                index: index,
                                itemOptions: item,
                                options: this.options,
                                property: this.buttonItemProperty[index],
                                groupId: this.groupId,
                                maxFontScale: this.maxFontScale,
                              },
                              undefined,
                              elmtId,
                              () => {},
                              {
                                page: 'advancedComponents/src/main/ets/components/SegmentButton.ets',
                                line: 812,
                                l2: 15,
                              }
                            );
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
                                maxFontScale: this.maxFontScale,
                              };
                            };
                            componentCall.paramsGenerator_ = paramsLambda;
                          } else {
                            this.updateStateVarsOfChildByElmtId(elmtId, {
                              index: index,
                              itemOptions: item,
                              options: this.options,
                              property: this.buttonItemProperty[index],
                              maxFontScale: this.maxFontScale,
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
              elmtId,
              this.optionsArray,
              forEachItemGenFunction,
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
  rerender() {
    this.updateDirtyElements();
  }
}
let r6 = class ItemProperty {
  constructor() {
    this.fontColor = j6.q4;
    this.fontSize = j6.t4;
    this.fontWeight = FontWeight.Regular;
    this.isSelected = false;
  }
};
r6 = a6([Observed], r6);
export class SegmentButton extends ViewPU {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda = undefined,
    extraInfo
  ) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.m5 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.h4 = new SynchedPropertyObjectTwoWayPU(
      params.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.onItemClicked = undefined;
    this.t5 = new SynchedPropertyObjectOneWayPU(
      params.maxFontScale,
      this,
      'maxFontScale'
    );
    this.u6 = new ObservedPropertyObjectPU(
      { width: 0, height: 0 },
      this,
      'componentSize'
    );
    this.addProvidedVar('componentSize', this.u6, false);
    this.n5 = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: f6,
        },
        (e10, index) => {
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
    this.addProvidedVar('buttonBorderRadius', this.n5, false);
    this.o5 = new ObservedPropertyObjectPU(
      Array.from({ length: f6 }, (d10, index) => {
        return {};
      }),
      this,
      'buttonItemsSize'
    );
    this.addProvidedVar('buttonItemsSize', this.o5, false);
    this.v6 = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: f6,
        },
        (c10, index) => {
          return {};
        }
      ),
      this,
      'buttonItemsPosition'
    );
    this.addProvidedVar('buttonItemsPosition', this.v6, false);
    this.x6 = new ObservedPropertyObjectPU(
      Array.from({ length: f6 }, (b10, index) => false),
      this,
      'buttonItemsSelected'
    );
    this.addProvidedVar('buttonItemsSelected', this.x6, false);
    this.w6 = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: f6,
        },
        (a10, index) => new r6()
      ),
      this,
      'buttonItemProperty'
    );
    this.addProvidedVar('buttonItemProperty', this.w6, false);
    this.s5 = new ObservedPropertySimplePU(-1, this, 'focusIndex');
    this.addProvidedVar('focusIndex', this.s5, false);
    this.p5 = new ObservedPropertyObjectPU({}, this, 'selectedItemPosition');
    this.addProvidedVar('selectedItemPosition', this.p5, false);
    this.q5 = new ObservedPropertyObjectPU(
      Array.from({ length: f6 }, (z9, index) => 1.0),
      this,
      'zoomScaleArray'
    );
    this.addProvidedVar('zoomScaleArray', this.q5, false);
    this.y6 = new ObservedPropertyObjectPU(
      Array.from({ length: f6 }, (y9, index) => false),
      this,
      'pressArray'
    );
    this.z6 = new ObservedPropertyObjectPU(
      Array.from({ length: f6 }, (x9, index) => false),
      this,
      'hoverArray'
    );
    this.a7 = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: f6,
        },
        (w9, index) => new o6()
      ),
      this,
      'hoverColorArray'
    );
    this.doSelectedChangeAnimate = false;
    this.isCurrentPositionSelected = false;
    this.panGestureStartPoint = { x: 0, y: 0 };
    this.isPanGestureMoved = false;
    this.d7 = new ObservedPropertySimplePU(false, this, 'shouldMirror');
    this.setInitiallyProvidedValue(params);
    this.declareWatch('options', this.onOptionsChange);
    this.declareWatch('selectedIndexes', this.onSelectedChange);
    this.declareWatch('buttonItemsPosition', this.onItemsPositionChange);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.m5.set(params.options);
    if (params.onItemClicked !== undefined) {
      this.onItemClicked = params.onItemClicked;
    }
    if (params.maxFontScale === undefined) {
      this.t5.set(g6);
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
  }
  updateStateVars(params) {
    this.m5.set(params.options);
    this.t5.reset(params.maxFontScale);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.m5.purgeDependencyOnElmtId(rmElmtId);
    this.h4.purgeDependencyOnElmtId(rmElmtId);
    this.t5.purgeDependencyOnElmtId(rmElmtId);
    this.u6.purgeDependencyOnElmtId(rmElmtId);
    this.n5.purgeDependencyOnElmtId(rmElmtId);
    this.o5.purgeDependencyOnElmtId(rmElmtId);
    this.v6.purgeDependencyOnElmtId(rmElmtId);
    this.x6.purgeDependencyOnElmtId(rmElmtId);
    this.w6.purgeDependencyOnElmtId(rmElmtId);
    this.s5.purgeDependencyOnElmtId(rmElmtId);
    this.p5.purgeDependencyOnElmtId(rmElmtId);
    this.q5.purgeDependencyOnElmtId(rmElmtId);
    this.y6.purgeDependencyOnElmtId(rmElmtId);
    this.z6.purgeDependencyOnElmtId(rmElmtId);
    this.a7.purgeDependencyOnElmtId(rmElmtId);
    this.d7.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.m5.aboutToBeDeleted();
    this.h4.aboutToBeDeleted();
    this.t5.aboutToBeDeleted();
    this.u6.aboutToBeDeleted();
    this.n5.aboutToBeDeleted();
    this.o5.aboutToBeDeleted();
    this.v6.aboutToBeDeleted();
    this.x6.aboutToBeDeleted();
    this.w6.aboutToBeDeleted();
    this.s5.aboutToBeDeleted();
    this.p5.aboutToBeDeleted();
    this.q5.aboutToBeDeleted();
    this.y6.aboutToBeDeleted();
    this.z6.aboutToBeDeleted();
    this.a7.aboutToBeDeleted();
    this.d7.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get options() {
    return this.m5.get();
  }
  get selectedIndexes() {
    return this.h4.get();
  }
  set selectedIndexes(newValue) {
    this.h4.set(newValue);
  }
  get maxFontScale() {
    return this.t5.get();
  }
  set maxFontScale(newValue) {
    this.t5.set(newValue);
  }
  get componentSize() {
    return this.u6.get();
  }
  set componentSize(newValue) {
    this.u6.set(newValue);
  }
  get buttonBorderRadius() {
    return this.n5.get();
  }
  set buttonBorderRadius(newValue) {
    this.n5.set(newValue);
  }
  get buttonItemsSize() {
    return this.o5.get();
  }
  set buttonItemsSize(newValue) {
    this.o5.set(newValue);
  }
  get buttonItemsPosition() {
    return this.v6.get();
  }
  set buttonItemsPosition(newValue) {
    this.v6.set(newValue);
  }
  get buttonItemsSelected() {
    return this.x6.get();
  }
  set buttonItemsSelected(newValue) {
    this.x6.set(newValue);
  }
  get buttonItemProperty() {
    return this.w6.get();
  }
  set buttonItemProperty(newValue) {
    this.w6.set(newValue);
  }
  get focusIndex() {
    return this.s5.get();
  }
  set focusIndex(newValue) {
    this.s5.set(newValue);
  }
  get selectedItemPosition() {
    return this.p5.get();
  }
  set selectedItemPosition(newValue) {
    this.p5.set(newValue);
  }
  get zoomScaleArray() {
    return this.q5.get();
  }
  set zoomScaleArray(newValue) {
    this.q5.set(newValue);
  }
  get pressArray() {
    return this.y6.get();
  }
  set pressArray(newValue) {
    this.y6.set(newValue);
  }
  get hoverArray() {
    return this.z6.get();
  }
  set hoverArray(newValue) {
    this.z6.set(newValue);
  }
  get hoverColorArray() {
    return this.a7.get();
  }
  set hoverColorArray(newValue) {
    this.a7.set(newValue);
  }
  get shouldMirror() {
    return this.d7.get();
  }
  set shouldMirror(newValue) {
    this.d7.set(newValue);
  }
  onItemsPositionChange() {
    if (this.options === void 0 || this.options.buttons === void 0) {
      return;
    }
    if (this.doSelectedChangeAnimate) {
      this.updateAnimatedProperty(this.getSelectedChangeCurve());
    } else {
      this.updateAnimatedProperty(null);
    }
  }
  setItemsSelected() {
    this.buttonItemsSelected.forEach((m9, index) => {
      this.buttonItemsSelected[index] = false;
    });
    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
      this.selectedIndexes.forEach(
        (index) => (this.buttonItemsSelected[index] = true)
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
    let i9 = this.selectedIndexes.some((index) => {
      return (
        index === void 0 ||
        index < 0 ||
        (this.options.buttons && index >= this.options.buttons.length)
      );
    });
    if (i9) {
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
    this.options.g5 = () => {
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
    return (
      !z5(x, this.panGestureStartPoint.x) || !z5(y, this.panGestureStartPoint.y)
    );
  }
  isShouldMirror() {
    if (this.options.direction == Direction.Rtl) {
      return true;
    }
    try {
      let g9 = d6.System.getSystemLanguage();
      if (g9 === 'ug' && this.options.direction != Direction.Ltr) {
        return true;
      }
    } catch (error) {
      console.error(
        `Ace SegmentButton getSystemLanguage, error: ${error.toString()}`
      );
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
      Stack.onKeyEvent((event) => {
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (event.type === KeyType.Down) {
          if (
            event.keyCode === KeyCode.KEYCODE_SPACE ||
            event.keyCode === KeyCode.KEYCODE_ENTER ||
            event.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER
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
      TapGesture.onAction((event) => {
        this.focusIndex = -1;
        let b9 = event.fingerList.find(Boolean);
        if (b9 === void 0) {
          return;
        }
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        let c9 = b9.localX;
        let d9 = Math.min(
          this.options.buttons.length,
          this.buttonItemsSize.length
        );
        for (let e9 = 0; e9 < d9; e9++) {
          c9 = c9 - this.buttonItemsSize[e9].width;
          if (c9 >= 0) {
            continue;
          }
          this.doSelectedChangeAnimate =
            this.selectedIndexes[0] >
            Math.min(this.options.buttons.length, this.buttonItemsSize.length)
              ? false
              : true;
          let f9 = this.isShouldMirror() ? d9 - 1 - e9 : e9;
          if (this.onItemClicked) {
            this.onItemClicked(f9);
          }
          if (
            this.options.type === 'capsule' &&
            (this.options.multiply ?? false)
          ) {
            let selectedIndex = this.selectedIndexes.indexOf(f9);
            if (selectedIndex === -1) {
              this.selectedIndexes.push(f9);
            } else {
              this.selectedIndexes.splice(selectedIndex, 1);
            }
          } else {
            this.selectedIndexes[0] = f9;
          }
          this.doSelectedChangeAnimate = false;
          break;
        }
      });
      TapGesture.pop();
      SwipeGesture.create();
      SwipeGesture.onAction((event) => {
        if (
          this.options === void 0 ||
          this.options.buttons === void 0 ||
          event.sourceTool === SourceTool.TOUCHPAD
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
          Math.abs(event.angle) < 90 &&
          this.selectedIndexes[0] !==
            Math.min(this.options.buttons.length, this.buttonItemsSize.length) -
              1
        ) {
          this.doSelectedChangeAnimate = true;
          this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
          this.doSelectedChangeAnimate = false;
        } else if (
          Math.abs(event.angle) > 90 &&
          this.selectedIndexes[0] !== 0
        ) {
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
        if (
          this.options.type === 'capsule' &&
          (this.options.multiply ?? false)
        ) {
          return;
        }
        let y8 = event.fingerList.find(Boolean);
        if (y8 === void 0) {
          return;
        }
        let z8 = y8.localX;
        this.panGestureStartPoint = { x: y8.globalX, y: y8.globalY };
        this.isPanGestureMoved = false;
        for (
          let a9 = 0;
          a9 <
          Math.min(this.options.buttons.length, this.buttonItemsSize.length);
          a9++
        ) {
          z8 = z8 - this.buttonItemsSize[a9].width;
          if (z8 < 0) {
            this.isCurrentPositionSelected =
              a9 === this.selectedIndexes[0] ? true : false;
            break;
          }
        }
      });
      PanGesture.onActionUpdate((event) => {
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
        let r8 = event.fingerList.find(Boolean);
        if (r8 === void 0) {
          return;
        }
        let s8 = r8.localX;
        if (
          !this.isPanGestureMoved &&
          this.isMovedFromPanGestureStartPoint(r8.globalX, r8.globalY)
        ) {
          this.isPanGestureMoved = true;
        }
        for (
          let x8 = 0;
          x8 <
          Math.min(this.options.buttons.length, this.buttonItemsSize.length);
          x8++
        ) {
          s8 = s8 - this.buttonItemsSize[x8].width;
          if (s8 < 0) {
            this.doSelectedChangeAnimate = true;
            this.selectedIndexes[0] = x8;
            this.doSelectedChangeAnimate = false;
            break;
          }
        }
        this.zoomScaleArray.forEach((u8, index) => {
          if (index === this.selectedIndexes[0]) {
            Context.animateTo(
              { curve: curves.interpolatingSpring(10, 1, 410, 38) },
              () => {
                this.zoomScaleArray[index] = 0.95;
              }
            );
          } else {
            Context.animateTo(
              { curve: curves.interpolatingSpring(10, 1, 410, 38) },
              () => {
                this.zoomScaleArray[index] = 1;
              }
            );
          }
        });
      });
      PanGesture.onActionEnd((event) => {
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        if (
          this.options.type === 'capsule' &&
          (this.options.multiply ?? false)
        ) {
          return;
        }
        let p8 = event.fingerList.find(Boolean);
        if (p8 === void 0) {
          return;
        }
        if (
          !this.isPanGestureMoved &&
          this.isMovedFromPanGestureStartPoint(p8.globalX, p8.globalY)
        ) {
          this.isPanGestureMoved = true;
        }
        if (this.isMouseWheelScroll(event)) {
          let offset = event.offsetX !== 0 ? event.offsetX : event.offsetY;
          this.doSelectedChangeAnimate = true;
          if (offset > 0 && this.selectedIndexes[0] > 0) {
            this.selectedIndexes[0] -= 1;
          } else if (
            offset < 0 &&
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
            if (
              this.options.type === 'capsule' &&
              (this.options.multiply ?? false)
            ) {
              this.ifElseBranchUpdateFunction(0, () => {
                {
                  this.observeComponentCreation2(
                    (elmtId, isInitialRender) => {
                      if (isInitialRender) {
                        let componentCall = new k6(
                          this,
                          {
                            optionsArray: this.options.buttons,
                            options: this.options,
                          },
                          undefined,
                          elmtId,
                          () => {},
                          {
                            page: 'advancedComponents/src/main/ets/components/SegmentButton.ets',
                            line: 1111,
                            l2: 11,
                          }
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
                  Stack.backgroundColor(
                    this.options.backgroundColor ?? j6.BACKGROUND_COLOR
                  );
                  Stack.borderRadius(
                    this.options.j5 ?? this.componentSize.height / 2
                  );
                  Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
                }, Stack);
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  If.create();
                  if (
                    this.options.buttons !== void 0 &&
                    this.options.buttons.length > 1
                  ) {
                    this.ifElseBranchUpdateFunction(0, () => {
                      this.observeComponentCreation2(
                        (elmtId, isInitialRender) => {
                          Row.create({ space: 1 });
                          Row.direction(this.options.direction);
                        },
                        Row
                      );
                      this.observeComponentCreation2(
                        (elmtId, isInitialRender) => {
                          ForEach.create();
                          const forEachItemGenFunction = (_item, index) => {
                            const item = _item;
                            this.observeComponentCreation2(
                              (elmtId, isInitialRender) => {
                                If.create();
                                if (index < f6) {
                                  this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2(
                                      (elmtId, isInitialRender) => {
                                        Stack.create();
                                        Stack.direction(this.options.direction);
                                        Stack.scale({
                                          x:
                                            this.options.type === 'capsule' &&
                                            (this.options.multiply ?? false)
                                              ? 1
                                              : this.zoomScaleArray[index],
                                          y:
                                            this.options.type === 'capsule' &&
                                            (this.options.multiply ?? false)
                                              ? 1
                                              : this.zoomScaleArray[index],
                                        });
                                      },
                                      Stack
                                    );
                                    {
                                      this.observeComponentCreation2(
                                        (elmtId, isInitialRender) => {
                                          if (isInitialRender) {
                                            let componentCall = new p6(
                                              this,
                                              {
                                                pressIndex: index,
                                                colorProperty:
                                                  this.hoverColorArray[index],
                                                press: this.pressArray[index],
                                                hover: this.hoverArray[index],
                                                options: this.options,
                                              },
                                              undefined,
                                              elmtId,
                                              () => {},
                                              {
                                                page: 'advancedComponents/src/main/ets/components/SegmentButton.ets',
                                                line: 1122,
                                                l2: 23,
                                              }
                                            );
                                            ViewPU.create(componentCall);
                                            let paramsLambda = () => {
                                              return {
                                                pressIndex: index,
                                                colorProperty:
                                                  this.hoverColorArray[index],
                                                press: this.pressArray[index],
                                                hover: this.hoverArray[index],
                                                options: this.options,
                                              };
                                            };
                                            componentCall.paramsGenerator_ =
                                              paramsLambda;
                                          } else {
                                            this.updateStateVarsOfChildByElmtId(
                                              elmtId,
                                              {
                                                colorProperty:
                                                  this.hoverColorArray[index],
                                                press: this.pressArray[index],
                                                hover: this.hoverArray[index],
                                                options: this.options,
                                              }
                                            );
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
                              },
                              If
                            );
                            If.pop();
                          };
                          this.forEachUpdateFunction(
                            elmtId,
                            this.options.buttons,
                            forEachItemGenFunction,
                            undefined,
                            true,
                            false
                          );
                        },
                        ForEach
                      );
                      ForEach.pop();
                      Row.pop();
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
            Stack.borderRadius(
              (this.options.type === 'capsule' &&
              (this.options.multiply ?? false)
                ? this.options.i5
                : this.options.j5) ?? this.componentSize.height / 2
            );
            Stack.clip(true);
          }, Stack);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (
              this.options.type === 'capsule' &&
              (this.options.multiply ?? false)
            ) {
              this.ifElseBranchUpdateFunction(0, () => {
                {
                  this.observeComponentCreation2(
                    (elmtId, isInitialRender) => {
                      if (isInitialRender) {
                        let componentCall = new m6(
                          this,
                          {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.h4,
                          },
                          undefined,
                          elmtId,
                          () => {},
                          {
                            page: 'advancedComponents/src/main/ets/components/SegmentButton.ets',
                            line: 1150,
                            l2: 13,
                          }
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
                        let componentCall = new l6(
                          this,
                          {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.h4,
                          },
                          undefined,
                          elmtId,
                          () => {},
                          {
                            page: 'advancedComponents/src/main/ets/components/SegmentButton.ets',
                            line: 1156,
                            l2: 13,
                          }
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
                  let componentCall = new q6(
                    this,
                    {
                      pressArray: this.y6,
                      hoverArray: this.z6,
                      hoverColorArray: this.a7,
                      optionsArray: this.options.buttons,
                      options: this.options,
                      selectedIndexes: this.h4,
                      maxFontScale: this.getMaxFontSize(),
                    },
                    undefined,
                    elmtId,
                    () => {},
                    {
                      page: 'advancedComponents/src/main/ets/components/SegmentButton.ets',
                      line: 1171,
                      l2: 9,
                    }
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
                    };
                  };
                  componentCall.paramsGenerator_ = paramsLambda;
                } else {
                  this.updateStateVarsOfChildByElmtId(elmtId, {
                    optionsArray: this.options.buttons,
                    options: this.options,
                    maxFontScale: this.getMaxFontSize(),
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
      return g6;
    }
    if (typeof this.maxFontScale === 'number') {
      return Math.max(Math.min(this.maxFontScale, h6), i6);
    }
    const resourceManager =
      this.getUIContext().getHostContext()?.resourceManager;
    if (!resourceManager) {
      return g6;
    }
    try {
      return resourceManager.getNumber(this.maxFontScale.id);
    }
    catch (error) {
      console.error(`Ace SegmentButton getMaxFontSize, error: ${error.toString()}`);
      return g6;
    }
  }
  getSelectedChangeCurve() {
    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
      return null;
    }
    return curves.springMotion(0.347, 0.99);
  }
  updateAnimatedProperty(curve) {
    let t6 = () => {
      this.selectedItemPosition =
        this.selectedIndexes.length === 0
          ? {}
          : this.buttonItemsPosition[this.selectedIndexes[0]];
      this.buttonItemsSelected.forEach((selected, index) => {
        this.buttonItemProperty[index].fontColor = selected
          ? this.options.selectedFontColor ??
            (this.options.type === 'tab' ? j6.r4 : j6.s4)
          : this.options.fontColor ?? j6.q4;
      });
    };
    if (curve) {
      Context.animateTo({ curve: curve }, t6);
    } else {
      t6();
    }
    this.buttonItemsSelected.forEach((selected, index) => {
      this.buttonItemProperty[index].fontSize = selected
        ? this.options.selectedFontSize ?? j6.u4
        : this.options.fontSize ?? j6.t4;
      this.buttonItemProperty[index].fontWeight = selected
        ? this.options.selectedFontWeight ?? FontWeight.Medium
        : this.options.fontWeight ?? FontWeight.Regular;
      this.buttonItemProperty[index].isSelected = selected;
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
