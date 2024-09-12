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

var j =
  (this && this.j) ||
  function (x8, target, key, desc) {
    var c = arguments.length,
      r =
        c < 3
          ? target
          : desc === null
          ? (desc = Object.getOwnPropertyDescriptor(target, key))
          : desc,
      d;
    if (typeof Reflect === 'object' && typeof Reflect.l1 === 'function')
      r = Reflect.l1(x8, target, key, desc);
    else
      for (var y8 = x8.length - 1; y8 >= 0; y8--)
        if ((d = x8[y8]))
          r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
  };
var m, o;
if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {});
}
const curves = globalThis.requireNativeModule('ohos.curves');
const KeyCode = globalThis.requireNapi('multimodalInput.keyCode').KeyCode;
const util = globalThis.requireNapi('util');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const I18n = requireNapi('i18n');

const u = 2;
const a1 = 5;
const b1 = {
  m1: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_text_secondary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  n1: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_text_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  o1: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_foreground_contrary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  q1: {
    id: -1,
    type: 10002,
    params: ['sys.float.ohos_id_text_size_body2'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  s1: {
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
  t1: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_foreground_contrary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  u1: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_emphasize'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  v1: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_focused_outline'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  w1: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_hover'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  z1: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_click_effect'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  a2: BlurStyle.NONE,
};
function i(first, second) {
  return Math.abs(first - second) < 0.001;
}
let SegmentButtonItemOptions = class SegmentButtonItemOptions {
  constructor(options) {
    this.icon = options.icon;
    this.selectedIcon = options.selectedIcon;
    this.text = options.text;
  }
};
SegmentButtonItemOptions = j([Observed], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray =
  (m = class SegmentButtonItemOptionsArray extends Array {
    constructor(u8) {
      super(typeof u8 === 'number' ? u8 : 0);
      this.b2 = void 0;
      this.deleteCount = void 0;
      this.c2 = void 0;
      if (typeof u8 !== 'number' && u8 !== void 0) {
        super.push(
          ...u8.map((element) => new SegmentButtonItemOptions(element))
        );
      }
    }
    push(...items) {
      if (this.length + items.length > a1) {
        console.warn('Exceeded the maximum number of elements (5).');
        return this.length;
      }
      this.b2 = this.length;
      this.deleteCount = 0;
      this.c2 = items.length;
      return super.push(
        ...items.map((element) => new SegmentButtonItemOptions(element))
      );
    }
    pop() {
      if (this.length <= u) {
        console.warn('Below the minimum number of elements (2).');
        return void 0;
      }
      this.b2 = this.length - 1;
      this.deleteCount = 1;
      this.c2 = 0;
      return super.pop();
    }
    shift() {
      if (this.length <= u) {
        console.warn('Below the minimum number of elements (2).');
        return void 0;
      }
      this.b2 = 0;
      this.deleteCount = 1;
      this.c2 = 0;
      return super.shift();
    }
    unshift(...items) {
      if (this.length + items.length > a1) {
        console.warn('Exceeded the maximum number of elements (5).');
        return this.length;
      }
      if (items.length > 0) {
        this.b2 = 0;
        this.deleteCount = 0;
        this.c2 = items.length;
      }
      return super.unshift(
        ...items.map((element) => new SegmentButtonItemOptions(element))
      );
    }
    splice(start, deleteCount, ...items) {
      let length =
        this.length - deleteCount < 0 ? 0 : this.length - deleteCount;
      length += items.length;
      if (length < u) {
        console.warn('Below the minimum number of elements (2).');
        return [];
      }
      if (length > a1) {
        console.warn('Exceeded the maximum number of elements (5).');
        return [];
      }
      this.b2 = start;
      this.deleteCount = deleteCount;
      this.c2 = items.length;
      return super.splice(start, deleteCount, ...items);
    }
    static create(elements) {
      return new m(elements);
    }
  });
SegmentButtonItemOptionsArray = m = j(
  [Observed],
  SegmentButtonItemOptionsArray
);
export { SegmentButtonItemOptionsArray };
let SegmentButtonOptions = (o = class SegmentButtonOptions {
  get buttons() {
    return this.d2;
  }
  set buttons(val) {
    if (this.d2 !== void 0 && this.d2 !== val) {
      this.e2?.();
    }
    this.d2 = val;
  }
  constructor(options) {
    this.multiply = false;
    this.f2 = false;
    this.showIcon = false;
    this.d2 = void 0;
    this.fontColor = options.fontColor ?? b1.m1;
    this.selectedFontColor = options.selectedFontColor ?? b1.n1;
    this.fontSize = options.fontSize ?? b1.q1;
    this.selectedFontSize = options.selectedFontSize ?? b1.s1;
    this.fontWeight = options.fontWeight ?? FontWeight.Regular;
    this.selectedFontWeight = options.selectedFontWeight ?? FontWeight.Medium;
    this.backgroundColor = options.backgroundColor ?? b1.BACKGROUND_COLOR;
    this.selectedBackgroundColor = options.selectedBackgroundColor ?? b1.t1;
    this.imageSize = options.imageSize ?? { width: 24, height: 24 };
    this.buttonPadding = options.buttonPadding ?? 0;
    this.textPadding = options.textPadding ?? 0;
    this.type = options.type;
    this.backgroundBlurStyle = options.backgroundBlurStyle ?? b1.a2;
    this.localizedTextPadding = options.localizedTextPadding;
    this.localizedButtonPadding = options.localizedButtonPadding;
    this.direction = options.direction ?? Direction.Auto;
    this.buttons = new SegmentButtonItemOptionsArray(options.buttons);
    if (this.type === 'capsule') {
      this.multiply = options.multiply ?? false;
      this.buttons.forEach((button) => {
        this.f2 ||= button.text !== void 0;
        this.showIcon ||=
          button.icon !== void 0 || button.selectedIcon !== void 0;
      });
      if (this.f2 && this.showIcon) {
        this.g2 = 12;
        this.h2 = 14;
      }
      this.selectedFontColor = options.selectedFontColor ?? b1.o1;
      this.selectedBackgroundColor = options.selectedBackgroundColor ?? b1.u1;
    } else {
      this.f2 = true;
    }
    this.i2 = this.multiply ? 0 : 2;
  }
  static tab(options) {
    return new o({
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
    return new o({
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
SegmentButtonOptions = o = j([Observed], SegmentButtonOptions);
export { SegmentButtonOptions };
class c1 extends ViewPU {
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
    this.j2 = new SynchedPropertyNesedObjectPU(
      params.optionsArray,
      this,
      'optionsArray'
    );
    this.l2 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.m2 = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.n2 = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.j2.set(params.optionsArray);
    this.l2.set(params.options);
  }
  updateStateVars(params) {
    this.j2.set(params.optionsArray);
    this.l2.set(params.options);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.j2.purgeDependencyOnElmtId(rmElmtId);
    this.l2.purgeDependencyOnElmtId(rmElmtId);
    this.m2.purgeDependencyOnElmtId(rmElmtId);
    this.n2.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.j2.aboutToBeDeleted();
    this.l2.aboutToBeDeleted();
    this.m2.aboutToBeDeleted();
    this.n2.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get optionsArray() {
    return this.j2.get();
  }
  get options() {
    return this.l2.get();
  }
  get buttonBorderRadius() {
    return this.m2.get();
  }
  set buttonBorderRadius(newValue) {
    this.m2.set(newValue);
  }
  get buttonItemsSize() {
    return this.n2.get();
  }
  set buttonItemsSize(newValue) {
    this.n2.set(newValue);
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create({ space: 1 });
      Row.direction(this.options.direction);
      Row.padding(this.options.i2);
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      ForEach.create();
      const forEachItemGenFunction = (_item, index) => {
        const m8 = _item;
        this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (index < a1) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((elmtId, isInitialRender) => {
                Stack.create();
                Stack.direction(this.options.direction);
                Stack.layoutWeight(1);
                Stack.height(this.buttonItemsSize[index].height);
                Stack.backgroundColor(
                  this.options.backgroundColor ?? b1.BACKGROUND_COLOR
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
class d1 extends ViewPU {
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
    this.j2 = new SynchedPropertyNesedObjectPU(
      params.optionsArray,
      this,
      'optionsArray'
    );
    this.l2 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.o2 = new SynchedPropertyObjectTwoWayPU(
      params.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.n2 = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.q2 = this.initializeConsume(
      'selectedItemPosition',
      'selectedItemPosition'
    );
    this.s2 = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
    this.m2 = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.j2.set(params.optionsArray);
    this.l2.set(params.options);
  }
  updateStateVars(params) {
    this.j2.set(params.optionsArray);
    this.l2.set(params.options);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.j2.purgeDependencyOnElmtId(rmElmtId);
    this.l2.purgeDependencyOnElmtId(rmElmtId);
    this.o2.purgeDependencyOnElmtId(rmElmtId);
    this.n2.purgeDependencyOnElmtId(rmElmtId);
    this.q2.purgeDependencyOnElmtId(rmElmtId);
    this.s2.purgeDependencyOnElmtId(rmElmtId);
    this.m2.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.j2.aboutToBeDeleted();
    this.l2.aboutToBeDeleted();
    this.o2.aboutToBeDeleted();
    this.n2.aboutToBeDeleted();
    this.q2.aboutToBeDeleted();
    this.s2.aboutToBeDeleted();
    this.m2.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get optionsArray() {
    return this.j2.get();
  }
  get options() {
    return this.l2.get();
  }
  get selectedIndexes() {
    return this.o2.get();
  }
  set selectedIndexes(newValue) {
    this.o2.set(newValue);
  }
  get buttonItemsSize() {
    return this.n2.get();
  }
  set buttonItemsSize(newValue) {
    this.n2.set(newValue);
  }
  get selectedItemPosition() {
    return this.q2.get();
  }
  set selectedItemPosition(newValue) {
    this.q2.set(newValue);
  }
  get zoomScaleArray() {
    return this.s2.get();
  }
  set zoomScaleArray(newValue) {
    this.s2.set(newValue);
  }
  get buttonBorderRadius() {
    return this.m2.get();
  }
  set buttonBorderRadius(newValue) {
    this.m2.set(newValue);
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
                (this.options.type === 'tab' ? b1.t1 : b1.u1)
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
class e1 extends ViewPU {
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
    this.j2 = new SynchedPropertyNesedObjectPU(
      params.optionsArray,
      this,
      'optionsArray'
    );
    this.l2 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.o2 = new SynchedPropertyObjectTwoWayPU(
      params.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.n2 = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.s2 = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
    this.m2 = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.t2 = new ObservedPropertyObjectPU(
      Array.from({ length: a1 }, (e8, index) => Color.Transparent),
      this,
      'multiColor'
    );
    this.setInitiallyProvidedValue(params);
    this.declareWatch('options', this.onOptionsChange);
    this.declareWatch('selectedIndexes', this.onSelectedChange);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.j2.set(params.optionsArray);
    this.l2.set(params.options);
    if (params.multiColor !== undefined) {
      this.multiColor = params.multiColor;
    }
  }
  updateStateVars(params) {
    this.j2.set(params.optionsArray);
    this.l2.set(params.options);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.j2.purgeDependencyOnElmtId(rmElmtId);
    this.l2.purgeDependencyOnElmtId(rmElmtId);
    this.o2.purgeDependencyOnElmtId(rmElmtId);
    this.n2.purgeDependencyOnElmtId(rmElmtId);
    this.s2.purgeDependencyOnElmtId(rmElmtId);
    this.m2.purgeDependencyOnElmtId(rmElmtId);
    this.t2.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.j2.aboutToBeDeleted();
    this.l2.aboutToBeDeleted();
    this.o2.aboutToBeDeleted();
    this.n2.aboutToBeDeleted();
    this.s2.aboutToBeDeleted();
    this.m2.aboutToBeDeleted();
    this.t2.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get optionsArray() {
    return this.j2.get();
  }
  get options() {
    return this.l2.get();
  }
  get selectedIndexes() {
    return this.o2.get();
  }
  set selectedIndexes(newValue) {
    this.o2.set(newValue);
  }
  get buttonItemsSize() {
    return this.n2.get();
  }
  set buttonItemsSize(newValue) {
    this.n2.set(newValue);
  }
  get zoomScaleArray() {
    return this.s2.get();
  }
  set zoomScaleArray(newValue) {
    this.s2.set(newValue);
  }
  get buttonBorderRadius() {
    return this.m2.get();
  }
  set buttonBorderRadius(newValue) {
    this.m2.set(newValue);
  }
  get multiColor() {
    return this.t2.get();
  }
  set multiColor(newValue) {
    this.t2.set(newValue);
  }
  onOptionsChange() {
    for (let c8 = 0; c8 < this.selectedIndexes.length; c8++) {
      this.multiColor[this.selectedIndexes[c8]] =
        this.options.selectedBackgroundColor ?? b1.u1;
    }
  }
  onSelectedChange() {
    for (let b8 = 0; b8 < a1; b8++) {
      this.multiColor[b8] = Color.Transparent;
    }
    for (let a8 = 0; a8 < this.selectedIndexes.length; a8++) {
      this.multiColor[this.selectedIndexes[a8]] =
        this.options.selectedBackgroundColor ?? b1.u1;
    }
  }
  aboutToAppear() {
    for (let z7 = 0; z7 < this.selectedIndexes.length; z7++) {
      this.multiColor[this.selectedIndexes[z7]] =
        this.options.selectedBackgroundColor ?? b1.u1;
    }
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create({ space: 1 });
      Row.direction(this.options.direction);
      Row.padding(this.options.i2);
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      ForEach.create();
      const forEachItemGenFunction = (_item, index) => {
        const u7 = _item;
        this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (index < a1) {
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
class f1 extends ViewPU {
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
    this.o2 = new SynchedPropertyObjectTwoWayPU(
      params.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.u2 = new SynchedPropertySimpleTwoWayPU(
      params.focusIndex,
      this,
      'focusIndex'
    );
    this.v2 = new SynchedPropertyNesedObjectPU(
      params.itemOptions,
      this,
      'itemOptions'
    );
    this.l2 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.w2 = new SynchedPropertyNesedObjectPU(
      params.property,
      this,
      'property'
    );
    this.z2 = new SynchedPropertySimpleOneWayPU(params.index, this, 'index');
    this.groupId = '';
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.v2.set(params.itemOptions);
    this.l2.set(params.options);
    this.w2.set(params.property);
    if (params.groupId !== undefined) {
      this.groupId = params.groupId;
    }
  }
  updateStateVars(params) {
    this.v2.set(params.itemOptions);
    this.l2.set(params.options);
    this.w2.set(params.property);
    this.z2.reset(params.index);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.o2.purgeDependencyOnElmtId(rmElmtId);
    this.u2.purgeDependencyOnElmtId(rmElmtId);
    this.v2.purgeDependencyOnElmtId(rmElmtId);
    this.l2.purgeDependencyOnElmtId(rmElmtId);
    this.w2.purgeDependencyOnElmtId(rmElmtId);
    this.z2.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.o2.aboutToBeDeleted();
    this.u2.aboutToBeDeleted();
    this.v2.aboutToBeDeleted();
    this.l2.aboutToBeDeleted();
    this.w2.aboutToBeDeleted();
    this.z2.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get selectedIndexes() {
    return this.o2.get();
  }
  set selectedIndexes(newValue) {
    this.o2.set(newValue);
  }
  get focusIndex() {
    return this.u2.get();
  }
  set focusIndex(newValue) {
    this.u2.set(newValue);
  }
  get itemOptions() {
    return this.v2.get();
  }
  get options() {
    return this.l2.get();
  }
  get property() {
    return this.w2.get();
  }
  get index() {
    return this.z2.get();
  }
  set index(newValue) {
    this.z2.set(newValue);
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
      this.options.f2 &&
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
            Image.focusable(!this.options.f2);
            Image.draggable(false);
            Image.fillColor(
              this.property.isSelected
                ? this.options.selectedFontColor ?? b1.o1
                : this.options.fontColor ?? b1.m1
            );
          }, Image);
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.options.f2) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
              if (
                this.options.type === 'capsule' &&
                (this.options.multiply ?? false)
              ) {
                if (this.selectedIndexes.indexOf(this.index) === -1) {
                  this.selectedIndexes.push(this.index);
                } else {
                  this.selectedIndexes.splice(
                    this.selectedIndexes.indexOf(this.index),
                    1
                  );
                }
              } else {
                this.selectedIndexes[0] = this.index;
              }
            });
            TapGesture.pop();
            Gesture.pop();
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
let g1 = class HoverColorProperty {
  constructor() {
    this.a3 = Color.Transparent;
  }
};
g1 = j([Observed], g1);
class h1 extends ViewPU {
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
    this.n2 = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.b3 = new SynchedPropertySimpleOneWayPU(params.press, this, 'press');
    this.c3 = new SynchedPropertySimpleOneWayPU(params.hover, this, 'hover');
    this.d3 = new SynchedPropertyNesedObjectPU(
      params.colorProperty,
      this,
      'colorProperty'
    );
    this.m2 = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.l2 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.pressIndex = 0;
    this.pressColor = b1.z1;
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.d3.set(params.colorProperty);
    this.l2.set(params.options);
    if (params.pressIndex !== undefined) {
      this.pressIndex = params.pressIndex;
    }
    if (params.pressColor !== undefined) {
      this.pressColor = params.pressColor;
    }
  }
  updateStateVars(params) {
    this.b3.reset(params.press);
    this.c3.reset(params.hover);
    this.d3.set(params.colorProperty);
    this.l2.set(params.options);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.n2.purgeDependencyOnElmtId(rmElmtId);
    this.b3.purgeDependencyOnElmtId(rmElmtId);
    this.c3.purgeDependencyOnElmtId(rmElmtId);
    this.d3.purgeDependencyOnElmtId(rmElmtId);
    this.m2.purgeDependencyOnElmtId(rmElmtId);
    this.l2.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.n2.aboutToBeDeleted();
    this.b3.aboutToBeDeleted();
    this.c3.aboutToBeDeleted();
    this.d3.aboutToBeDeleted();
    this.m2.aboutToBeDeleted();
    this.l2.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get buttonItemsSize() {
    return this.n2.get();
  }
  set buttonItemsSize(newValue) {
    this.n2.set(newValue);
  }
  get press() {
    return this.b3.get();
  }
  set press(newValue) {
    this.b3.set(newValue);
  }
  get hover() {
    return this.c3.get();
  }
  set hover(newValue) {
    this.c3.set(newValue);
  }
  get colorProperty() {
    return this.d3.get();
  }
  get buttonBorderRadius() {
    return this.m2.get();
  }
  set buttonBorderRadius(newValue) {
    this.m2.set(newValue);
  }
  get options() {
    return this.l2.get();
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Stack.create();
      Stack.direction(this.options.direction);
      Stack.size(this.buttonItemsSize[this.pressIndex]);
      Stack.backgroundColor(
        this.press && this.hover ? this.pressColor : this.colorProperty.a3
      );
      Stack.borderRadius(this.buttonBorderRadius[this.pressIndex]);
    }, Stack);
    Stack.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class i1 extends ViewPU {
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
    this.j2 = new SynchedPropertyNesedObjectPU(
      params.optionsArray,
      this,
      'optionsArray'
    );
    this.l2 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.o2 = new SynchedPropertyObjectTwoWayPU(
      params.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.e3 = this.initializeConsume('componentSize', 'componentSize');
    this.m2 = this.initializeConsume(
      'buttonBorderRadius',
      'buttonBorderRadius'
    );
    this.n2 = this.initializeConsume('buttonItemsSize', 'buttonItemsSize');
    this.f3 = this.initializeConsume(
      'buttonItemsPosition',
      'buttonItemsPosition'
    );
    this.u2 = this.initializeConsume('focusIndex', 'focusIndex');
    this.s2 = this.initializeConsume('zoomScaleArray', 'zoomScaleArray');
    this.g3 = this.initializeConsume(
      'buttonItemProperty',
      'buttonItemProperty'
    );
    this.h3 = this.initializeConsume(
      'buttonItemsSelected',
      'buttonItemsSelected'
    );
    this.i3 = new SynchedPropertyObjectTwoWayPU(
      params.pressArray,
      this,
      'pressArray'
    );
    this.j3 = new SynchedPropertyObjectTwoWayPU(
      params.hoverArray,
      this,
      'hoverArray'
    );
    this.l3 = new SynchedPropertyObjectTwoWayPU(
      params.hoverColorArray,
      this,
      'hoverColorArray'
    );
    this.m3 = new ObservedPropertyObjectPU(
      Array.from({ length: a1 }, (f7, index) => 0),
      this,
      'buttonWidth'
    );
    this.n3 = new ObservedPropertyObjectPU(
      Array.from({ length: a1 }, (e7, index) => 0),
      this,
      'buttonHeight'
    );
    this.buttonItemsRealHeight = Array.from({ length: a1 }, (d7, index) => 0);
    this.groupId = util.generateRandomUUID(true);
    this.setInitiallyProvidedValue(params);
    this.declareWatch('optionsArray', this.onOptionsArrayChange);
    this.declareWatch('options', this.onOptionsChange);
    this.declareWatch('buttonItemsSize', this.onButtonItemsSizeChange);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.j2.set(params.optionsArray);
    this.l2.set(params.options);
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
    this.j2.set(params.optionsArray);
    this.l2.set(params.options);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.j2.purgeDependencyOnElmtId(rmElmtId);
    this.l2.purgeDependencyOnElmtId(rmElmtId);
    this.o2.purgeDependencyOnElmtId(rmElmtId);
    this.e3.purgeDependencyOnElmtId(rmElmtId);
    this.m2.purgeDependencyOnElmtId(rmElmtId);
    this.n2.purgeDependencyOnElmtId(rmElmtId);
    this.f3.purgeDependencyOnElmtId(rmElmtId);
    this.u2.purgeDependencyOnElmtId(rmElmtId);
    this.s2.purgeDependencyOnElmtId(rmElmtId);
    this.g3.purgeDependencyOnElmtId(rmElmtId);
    this.h3.purgeDependencyOnElmtId(rmElmtId);
    this.i3.purgeDependencyOnElmtId(rmElmtId);
    this.j3.purgeDependencyOnElmtId(rmElmtId);
    this.l3.purgeDependencyOnElmtId(rmElmtId);
    this.m3.purgeDependencyOnElmtId(rmElmtId);
    this.n3.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.j2.aboutToBeDeleted();
    this.l2.aboutToBeDeleted();
    this.o2.aboutToBeDeleted();
    this.e3.aboutToBeDeleted();
    this.m2.aboutToBeDeleted();
    this.n2.aboutToBeDeleted();
    this.f3.aboutToBeDeleted();
    this.u2.aboutToBeDeleted();
    this.s2.aboutToBeDeleted();
    this.g3.aboutToBeDeleted();
    this.h3.aboutToBeDeleted();
    this.i3.aboutToBeDeleted();
    this.j3.aboutToBeDeleted();
    this.l3.aboutToBeDeleted();
    this.m3.aboutToBeDeleted();
    this.n3.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get optionsArray() {
    return this.j2.get();
  }
  get options() {
    return this.l2.get();
  }
  get selectedIndexes() {
    return this.o2.get();
  }
  set selectedIndexes(newValue) {
    this.o2.set(newValue);
  }
  get componentSize() {
    return this.e3.get();
  }
  set componentSize(newValue) {
    this.e3.set(newValue);
  }
  get buttonBorderRadius() {
    return this.m2.get();
  }
  set buttonBorderRadius(newValue) {
    this.m2.set(newValue);
  }
  get buttonItemsSize() {
    return this.n2.get();
  }
  set buttonItemsSize(newValue) {
    this.n2.set(newValue);
  }
  get buttonItemsPosition() {
    return this.f3.get();
  }
  set buttonItemsPosition(newValue) {
    this.f3.set(newValue);
  }
  get focusIndex() {
    return this.u2.get();
  }
  set focusIndex(newValue) {
    this.u2.set(newValue);
  }
  get zoomScaleArray() {
    return this.s2.get();
  }
  set zoomScaleArray(newValue) {
    this.s2.set(newValue);
  }
  get buttonItemProperty() {
    return this.g3.get();
  }
  set buttonItemProperty(newValue) {
    this.g3.set(newValue);
  }
  get buttonItemsSelected() {
    return this.h3.get();
  }
  set buttonItemsSelected(newValue) {
    this.h3.set(newValue);
  }
  get pressArray() {
    return this.i3.get();
  }
  set pressArray(newValue) {
    this.i3.set(newValue);
  }
  get hoverArray() {
    return this.j3.get();
  }
  set hoverArray(newValue) {
    this.j3.set(newValue);
  }
  get hoverColorArray() {
    return this.l3.get();
  }
  set hoverColorArray(newValue) {
    this.l3.set(newValue);
  }
  get buttonWidth() {
    return this.m3.get();
  }
  set buttonWidth(newValue) {
    this.m3.set(newValue);
  }
  get buttonHeight() {
    return this.n3.get();
  }
  set buttonHeight(newValue) {
    this.n3.set(newValue);
  }
  onButtonItemsSizeChange() {
    this.buttonItemsSize.forEach((value, index) => {
      this.buttonWidth[index] = value.width;
      this.buttonHeight[index] = value.height;
    });
  }
  changeSelectedIndexes(s6) {
    if (
      this.optionsArray.b2 === void 0 ||
      this.optionsArray.deleteCount === void 0 ||
      this.optionsArray.c2 === void 0
    ) {
      return;
    }
    if (!(this.options.multiply ?? false)) {
      if (this.selectedIndexes[0] === void 0) {
        return;
      }
      if (this.selectedIndexes[0] < this.optionsArray.b2) {
        return;
      }
      if (
        this.optionsArray.b2 + this.optionsArray.deleteCount >
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
          this.optionsArray.c2;
      }
    } else {
      let t6 = this.selectedIndexes;
      for (let w6 = 0; w6 < this.optionsArray.deleteCount; w6++) {
        let x6 = t6.indexOf(this.optionsArray.b2);
        let indexes = t6.map((value) =>
          this.optionsArray.b2 && value > this.optionsArray.b2
            ? value - 1
            : value
        );
        if (x6 !== -1) {
          indexes.splice(x6, 1);
        }
        t6 = indexes;
      }
      for (let u6 = 0; u6 < this.optionsArray.c2; u6++) {
        let indexes = t6.map((value) =>
          this.optionsArray.b2 && value >= this.optionsArray.b2
            ? value + 1
            : value
        );
        t6 = indexes;
      }
      this.selectedIndexes = t6;
    }
  }
  changeFocusIndex(r6) {
    if (
      this.optionsArray.b2 === void 0 ||
      this.optionsArray.deleteCount === void 0 ||
      this.optionsArray.c2 === void 0
    ) {
      return;
    }
    if (this.focusIndex === -1) {
      return;
    }
    if (this.focusIndex < this.optionsArray.b2) {
      return;
    }
    if (
      this.optionsArray.b2 + this.optionsArray.deleteCount >
      this.focusIndex
    ) {
      this.focusIndex = 0;
    } else {
      this.focusIndex =
        this.focusIndex - this.optionsArray.deleteCount + this.optionsArray.c2;
    }
  }
  onOptionsArrayChange() {
    if (this.options === void 0 || this.options.buttons === void 0) {
      return;
    }
    let q6 = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
    if (
      this.optionsArray.b2 !== void 0 &&
      this.optionsArray.deleteCount !== void 0 &&
      this.optionsArray.c2 !== void 0
    ) {
      this.changeSelectedIndexes(q6);
      this.changeFocusIndex(q6);
      this.optionsArray.b2 = void 0;
      this.optionsArray.deleteCount = void 0;
      this.optionsArray.c2 = void 0;
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
      Stack.borderColor(b1.v1);
      Stack.borderWidth(2);
    }, Stack);
    Stack.pop();
    Stack.pop();
  }
  calculateBorderRadius() {
    let k6 = Array.from(
      {
        length: a1,
      },
      (n6, index) => {
        return {
          topStart: LengthMetrics.vp(0),
          topEnd: LengthMetrics.vp(0),
          bottomStart: LengthMetrics.vp(0),
          bottomEnd: LengthMetrics.vp(0),
        };
      }
    );
    for (let index = 0; index < this.buttonBorderRadius.length; index++) {
      let m6 = this.buttonItemsSize[index].height / 2;
      if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
        k6[index].topStart = LengthMetrics.vp(this.options.g2 ?? m6);
        k6[index].topEnd = LengthMetrics.vp(this.options.g2 ?? m6);
        k6[index].bottomStart = LengthMetrics.vp(this.options.g2 ?? m6);
        k6[index].bottomEnd = LengthMetrics.vp(this.options.g2 ?? m6);
      } else {
        if (index === 0) {
          k6[index].topStart = LengthMetrics.vp(this.options.g2 ?? m6);
          k6[index].topEnd = LengthMetrics.vp(0);
          k6[index].bottomStart = LengthMetrics.vp(this.options.g2 ?? m6);
          k6[index].bottomEnd = LengthMetrics.vp(0);
        } else if (
          this.options.buttons &&
          index ===
            Math.min(this.options.buttons.length, this.buttonItemsSize.length) -
              1
        ) {
          k6[index].topStart = LengthMetrics.vp(0);
          k6[index].topEnd = LengthMetrics.vp(this.options.g2 ?? m6);
          k6[index].bottomStart = LengthMetrics.vp(0);
          k6[index].bottomEnd = LengthMetrics.vp(this.options.g2 ?? m6);
        } else {
          k6[index].topStart = LengthMetrics.vp(0);
          k6[index].topEnd = LengthMetrics.vp(0);
          k6[index].bottomStart = LengthMetrics.vp(0);
          k6[index].bottomEnd = LengthMetrics.vp(0);
        }
      }
    }
    this.buttonBorderRadius = k6;
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
            Row.padding(this.options.i2);
            Row.onSizeChange((j6, newValue) => {
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
                if (index < a1) {
                  this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2(
                      (elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.direction(this.options.direction);
                        Stack.borderRadius(this.buttonBorderRadius[index]);
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
                        Stack.layoutWeight(1);
                        Stack.onSizeChange((h6, newValue) => {
                          this.buttonItemsSize[index] = {
                            width: newValue.width,
                            height: this.buttonItemsSize[index].height,
                          };
                          if (newValue.width) {
                            this.buttonItemsPosition[index] = {
                              start: LengthMetrics.vp(
                                Number.parseFloat(this.options.i2.toString()) +
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
                                      this.options.i2.toString()
                                    )
                                  )
                                )
                              ),
                            };
                          }
                        });
                        ViewStackProcessor.visualState('normal');
                        Stack.overlay(undefined);
                        ViewStackProcessor.visualState('focused');
                        Stack.overlay(
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
                        Stack.onFocus(() => {
                          this.focusIndex = index;
                        });
                        Stack.onTouch((event) => {
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
                        Stack.onHover((isHover) => {
                          this.hoverArray[index] = isHover;
                          if (isHover) {
                            Context.animateTo(
                              { duration: 250, curve: Curve.Friction },
                              () => {
                                this.hoverColorArray[index].a3 = b1.w1;
                              }
                            );
                          } else {
                            Context.animateTo(
                              { duration: 250, curve: Curve.Friction },
                              () => {
                                this.hoverColorArray[index].a3 =
                                  Color.Transparent;
                              }
                            );
                          }
                        });
                        Stack.onMouse((event) => {
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
                      Stack
                    );
                    this.observeComponentCreation2(
                      (elmtId, isInitialRender) => {
                        __Common__.create();
                        __Common__.onSizeChange((t5, newValue) => {
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
                            let componentCall = new f1(
                              this,
                              {
                                selectedIndexes: this.o2,
                                focusIndex: this.u2,
                                index: index,
                                itemOptions: item,
                                options: this.options,
                                property: this.buttonItemProperty[index],
                                groupId: this.groupId,
                              },
                              undefined,
                              elmtId,
                              () => {},
                              {
                                page: 'components/src/main/ets/components/SegmentButton.ets',
                                line: 774,
                                q3: 15,
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
                              };
                            };
                            componentCall.paramsGenerator_ = paramsLambda;
                          } else {
                            this.updateStateVarsOfChildByElmtId(elmtId, {
                              index: index,
                              itemOptions: item,
                              options: this.options,
                              property: this.buttonItemProperty[index],
                            });
                          }
                        },
                        { name: 'SegmentButtonItem' }
                      );
                    }
                    __Common__.pop();
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
let j1 = class ItemProperty {
  constructor() {
    this.fontColor = b1.m1;
    this.fontSize = b1.q1;
    this.fontWeight = FontWeight.Regular;
    this.isSelected = false;
  }
};
j1 = j([Observed], j1);
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
    this.l2 = new SynchedPropertyNesedObjectPU(params.options, this, 'options');
    this.o2 = new SynchedPropertyObjectTwoWayPU(
      params.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.onClicked = undefined;
    this.e3 = new ObservedPropertyObjectPU(
      { width: 0, height: 0 },
      this,
      'componentSize'
    );
    this.addProvidedVar('componentSize', this.e3, false);
    this.m2 = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: a1,
        },
        (d5, index) => {
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
    this.addProvidedVar('buttonBorderRadius', this.m2, false);
    this.n2 = new ObservedPropertyObjectPU(
      Array.from({ length: a1 }, (c5, index) => {
        return {};
      }),
      this,
      'buttonItemsSize'
    );
    this.addProvidedVar('buttonItemsSize', this.n2, false);
    this.f3 = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: a1,
        },
        (b5, index) => {
          return {};
        }
      ),
      this,
      'buttonItemsPosition'
    );
    this.addProvidedVar('buttonItemsPosition', this.f3, false);
    this.h3 = new ObservedPropertyObjectPU(
      Array.from({ length: a1 }, (a5, index) => false),
      this,
      'buttonItemsSelected'
    );
    this.addProvidedVar('buttonItemsSelected', this.h3, false);
    this.g3 = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: a1,
        },
        (z4, index) => new j1()
      ),
      this,
      'buttonItemProperty'
    );
    this.addProvidedVar('buttonItemProperty', this.g3, false);
    this.u2 = new ObservedPropertySimplePU(-1, this, 'focusIndex');
    this.addProvidedVar('focusIndex', this.u2, false);
    this.q2 = new ObservedPropertyObjectPU({}, this, 'selectedItemPosition');
    this.addProvidedVar('selectedItemPosition', this.q2, false);
    this.s2 = new ObservedPropertyObjectPU(
      Array.from({ length: a1 }, (y4, index) => 1.0),
      this,
      'zoomScaleArray'
    );
    this.addProvidedVar('zoomScaleArray', this.s2, false);
    this.i3 = new ObservedPropertyObjectPU(
      Array.from({ length: a1 }, (x4, index) => false),
      this,
      'pressArray'
    );
    this.j3 = new ObservedPropertyObjectPU(
      Array.from({ length: a1 }, (w4, index) => false),
      this,
      'hoverArray'
    );
    this.l3 = new ObservedPropertyObjectPU(
      Array.from(
        {
          length: a1,
        },
        (v4, index) => new g1()
      ),
      this,
      'hoverColorArray'
    );
    this.doSelectedChangeAnimate = false;
    this.isCurrentPositionSelected = false;
    this.panGestureStartPoint = { x: 0, y: 0 };
    this.isPanGestureMoved = false;
    this.r3 = new ObservedPropertySimplePU(false, this, 'shouldMirror');
    this.setInitiallyProvidedValue(params);
    this.declareWatch('options', this.onOptionsChange);
    this.declareWatch('selectedIndexes', this.onSelectedChange);
    this.declareWatch('buttonItemsPosition', this.onItemsPositionChange);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    this.l2.set(params.options);
    if (params.onClicked !== undefined) {
      this.onClicked = params.onClicked;
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
    this.l2.set(params.options);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.l2.purgeDependencyOnElmtId(rmElmtId);
    this.o2.purgeDependencyOnElmtId(rmElmtId);
    this.e3.purgeDependencyOnElmtId(rmElmtId);
    this.m2.purgeDependencyOnElmtId(rmElmtId);
    this.n2.purgeDependencyOnElmtId(rmElmtId);
    this.f3.purgeDependencyOnElmtId(rmElmtId);
    this.h3.purgeDependencyOnElmtId(rmElmtId);
    this.g3.purgeDependencyOnElmtId(rmElmtId);
    this.u2.purgeDependencyOnElmtId(rmElmtId);
    this.q2.purgeDependencyOnElmtId(rmElmtId);
    this.s2.purgeDependencyOnElmtId(rmElmtId);
    this.i3.purgeDependencyOnElmtId(rmElmtId);
    this.j3.purgeDependencyOnElmtId(rmElmtId);
    this.l3.purgeDependencyOnElmtId(rmElmtId);
    this.r3.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.l2.aboutToBeDeleted();
    this.o2.aboutToBeDeleted();
    this.e3.aboutToBeDeleted();
    this.m2.aboutToBeDeleted();
    this.n2.aboutToBeDeleted();
    this.f3.aboutToBeDeleted();
    this.h3.aboutToBeDeleted();
    this.g3.aboutToBeDeleted();
    this.u2.aboutToBeDeleted();
    this.q2.aboutToBeDeleted();
    this.s2.aboutToBeDeleted();
    this.i3.aboutToBeDeleted();
    this.j3.aboutToBeDeleted();
    this.l3.aboutToBeDeleted();
    this.r3.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get options() {
    return this.l2.get();
  }
  get selectedIndexes() {
    return this.o2.get();
  }
  set selectedIndexes(newValue) {
    this.o2.set(newValue);
  }
  get componentSize() {
    return this.e3.get();
  }
  set componentSize(newValue) {
    this.e3.set(newValue);
  }
  get buttonBorderRadius() {
    return this.m2.get();
  }
  set buttonBorderRadius(newValue) {
    this.m2.set(newValue);
  }
  get buttonItemsSize() {
    return this.n2.get();
  }
  set buttonItemsSize(newValue) {
    this.n2.set(newValue);
  }
  get buttonItemsPosition() {
    return this.f3.get();
  }
  set buttonItemsPosition(newValue) {
    this.f3.set(newValue);
  }
  get buttonItemsSelected() {
    return this.h3.get();
  }
  set buttonItemsSelected(newValue) {
    this.h3.set(newValue);
  }
  get buttonItemProperty() {
    return this.g3.get();
  }
  set buttonItemProperty(newValue) {
    this.g3.set(newValue);
  }
  get focusIndex() {
    return this.u2.get();
  }
  set focusIndex(newValue) {
    this.u2.set(newValue);
  }
  get selectedItemPosition() {
    return this.q2.get();
  }
  set selectedItemPosition(newValue) {
    this.q2.set(newValue);
  }
  get zoomScaleArray() {
    return this.s2.get();
  }
  set zoomScaleArray(newValue) {
    this.s2.set(newValue);
  }
  get pressArray() {
    return this.i3.get();
  }
  set pressArray(newValue) {
    this.i3.set(newValue);
  }
  get hoverArray() {
    return this.j3.get();
  }
  set hoverArray(newValue) {
    this.j3.set(newValue);
  }
  get hoverColorArray() {
    return this.l3.get();
  }
  set hoverColorArray(newValue) {
    this.l3.set(newValue);
  }
  get shouldMirror() {
    return this.r3.get();
  }
  set shouldMirror(newValue) {
    this.r3.set(newValue);
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
    this.buttonItemsSelected.forEach((l4, index) => {
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
    let h4 = this.selectedIndexes.some((index) => {
      return (
        index === void 0 ||
        index < 0 ||
        (this.options.buttons && index >= this.options.buttons.length)
      );
    });
    if (h4) {
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
    this.options.e2 = () => {
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
      !i(x, this.panGestureStartPoint.x) || !i(y, this.panGestureStartPoint.y)
    );
  }
  isShouldMirror() {
    if (this.options.direction == Direction.Rtl) {
      return true;
    }
    try {
      let f4 = I18n.System.getSystemLanguage();
      if (f4 === 'ug' && this.options.direction != Direction.Ltr) {
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
        let a4 = event.fingerList.find(Boolean);
        if (a4 === void 0) {
          return;
        }
        if (this.options === void 0 || this.options.buttons === void 0) {
          return;
        }
        let b4 = a4.localX;
        let c4 = Math.min(
          this.options.buttons.length,
          this.buttonItemsSize.length
        );
        for (let d4 = 0; d4 < c4; d4++) {
          b4 = b4 - this.buttonItemsSize[d4].width;
          if (b4 >= 0) {
            continue;
          }
          this.doSelectedChangeAnimate =
            this.selectedIndexes[0] >
            Math.min(this.options.buttons.length, this.buttonItemsSize.length)
              ? false
              : true;
          let e4 = this.isShouldMirror() ? c4 - 1 - d4 : d4;
          if (this.onClicked) {
            this.onClicked(e4);
          }
          if (
            this.options.type === 'capsule' &&
            (this.options.multiply ?? false)
          ) {
            let selectedIndex = this.selectedIndexes.indexOf(e4);
            if (selectedIndex === -1) {
              this.selectedIndexes.push(e4);
            } else {
              this.selectedIndexes.splice(selectedIndex, 1);
            }
          } else {
            this.selectedIndexes[0] = e4;
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
          event.angle > 0 &&
          this.selectedIndexes[0] !==
            Math.min(this.options.buttons.length, this.buttonItemsSize.length) -
              1
        ) {
          this.doSelectedChangeAnimate = true;
          this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
          this.doSelectedChangeAnimate = false;
        } else if (event.angle < 0 && this.selectedIndexes[0] !== 0) {
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
        let x3 = event.fingerList.find(Boolean);
        if (x3 === void 0) {
          return;
        }
        let y3 = x3.localX;
        this.panGestureStartPoint = { x: x3.globalX, y: x3.globalY };
        this.isPanGestureMoved = false;
        for (
          let z3 = 0;
          z3 <
          Math.min(this.options.buttons.length, this.buttonItemsSize.length);
          z3++
        ) {
          y3 = y3 - this.buttonItemsSize[z3].width;
          if (y3 < 0) {
            this.isCurrentPositionSelected =
              z3 === this.selectedIndexes[0] ? true : false;
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
        let q3 = event.fingerList.find(Boolean);
        if (q3 === void 0) {
          return;
        }
        let r3 = q3.localX;
        if (
          !this.isPanGestureMoved &&
          this.isMovedFromPanGestureStartPoint(q3.globalX, q3.globalY)
        ) {
          this.isPanGestureMoved = true;
        }
        for (
          let w3 = 0;
          w3 <
          Math.min(this.options.buttons.length, this.buttonItemsSize.length);
          w3++
        ) {
          r3 = r3 - this.buttonItemsSize[w3].width;
          if (r3 < 0) {
            this.doSelectedChangeAnimate = true;
            this.selectedIndexes[0] = w3;
            this.doSelectedChangeAnimate = false;
            break;
          }
        }
        this.zoomScaleArray.forEach((t3, index) => {
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
        let n3 = event.fingerList.find(Boolean);
        if (n3 === void 0) {
          return;
        }
        if (
          !this.isPanGestureMoved &&
          this.isMovedFromPanGestureStartPoint(n3.globalX, n3.globalY)
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
                        let componentCall = new c1(
                          this,
                          {
                            optionsArray: this.options.buttons,
                            options: this.options,
                          },
                          undefined,
                          elmtId,
                          () => {},
                          {
                            page: 'components/src/main/ets/components/SegmentButton.ets',
                            line: 1052,
                            q3: 11,
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
                    this.options.backgroundColor ?? b1.BACKGROUND_COLOR
                  );
                  Stack.borderRadius(
                    this.options.h2 ?? this.componentSize.height / 2
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
                                if (index < a1) {
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
                                            let componentCall = new h1(
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
                                                page: 'components/src/main/ets/components/SegmentButton.ets',
                                                line: 1063,
                                                q3: 23,
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
                ? this.options.g2
                : this.options.h2) ?? this.componentSize.height / 2
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
                        let componentCall = new e1(
                          this,
                          {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.o2,
                          },
                          undefined,
                          elmtId,
                          () => {},
                          {
                            page: 'components/src/main/ets/components/SegmentButton.ets',
                            line: 1091,
                            q3: 13,
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
                        let componentCall = new d1(
                          this,
                          {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.o2,
                          },
                          undefined,
                          elmtId,
                          () => {},
                          {
                            page: 'components/src/main/ets/components/SegmentButton.ets',
                            line: 1097,
                            q3: 13,
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
                  let componentCall = new i1(
                    this,
                    {
                      pressArray: this.i3,
                      hoverArray: this.j3,
                      hoverColorArray: this.l3,
                      optionsArray: this.options.buttons,
                      options: this.options,
                      selectedIndexes: this.o2,
                    },
                    undefined,
                    elmtId,
                    () => {},
                    {
                      page: 'components/src/main/ets/components/SegmentButton.ets',
                      line: 1112,
                      q3: 9,
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
  getSelectedChangeCurve() {
    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
      return null;
    }
    return curves.springMotion(0.347, 0.99);
  }
  updateAnimatedProperty(curve) {
    let l1 = () => {
      this.selectedItemPosition =
        this.selectedIndexes.length === 0
          ? {}
          : this.buttonItemsPosition[this.selectedIndexes[0]];
      this.buttonItemsSelected.forEach((selected, index) => {
        this.buttonItemProperty[index].fontColor = selected
          ? this.options.selectedFontColor ??
            (this.options.type === 'tab' ? b1.n1 : b1.o1)
          : this.options.fontColor ?? b1.m1;
      });
    };
    if (curve) {
      Context.animateTo({ curve: curve }, l1);
    } else {
      l1();
    }
    this.buttonItemsSelected.forEach((selected, index) => {
      this.buttonItemProperty[index].fontSize = selected
        ? this.options.selectedFontSize ?? b1.s1
        : this.options.fontSize ?? b1.q1;
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
