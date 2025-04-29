/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to  in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {});
}
if (PUV2ViewBase.contextStack === undefined) {
  Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const Chip = requireNapi('arkui.advanced.Chip').Chip;
const ChipSize = requireNapi('arkui.advanced.Chip').ChipSize;
const AccessibilitySelectedType = requireNapi('arkui.advanced.Chip').AccessibilitySelectedType;
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;
const c1 = (selectedIndexes) => {};
const colorStops = [
  ['rgba(0, 0, 0, 1)', 0],
  ['rgba(0, 0, 0, 0)', 1],
];
const b1 = {
  itemStyle: {
    size: ChipSize.NORMAL,
    backgroundColor: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_button_normal'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    fontColor: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_text_primary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    selectedFontColor: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_text_primary_contrary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    selectedBackgroundColor: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_emphasize'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    fillColor: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_secondary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
    h4: {
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_text_primary_contrary'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    },
  },
  chipGroupSpace: { itemSpace: 8, startSpace: 16, endSpace: 16 },
  chipGroupPadding: { top: 14, bottom: 14 },
};
const e4 = {
  backgroundColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_button_normal'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  borderRadius: {
    id: -1,
    type: 10002,
    params: ['sys.float.ohos_id_corner_radius_tips_instant_tip'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  i4: 16,
  j4: 24,
  l4: 28,
  m4: 36,
  marginLeft: 8,
  marginRight: 16,
  fillColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.ohos_id_color_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  o1: -1,
};
var f4;
(function (s4) {
  s4[(s4['NORMAL'] = 36)] = 'NORMAL';
  s4[(s4['SMALL'] = 28)] = 'SMALL';
})(f4 || (f4 = {}));
function c4(uiContext, value, isValid, defaultValue) {
  if (value === void 0 || value === null) {
    return defaultValue;
  }
  const resourceManager = uiContext.getHostContext()?.resourceManager;
  if (!resourceManager) {
    return defaultValue;
  }
  if (typeof value === 'object') {
    let r4 = value;
    if (r4.type === 10002 || r4.type === 10007) {
      if (resourceManager.getNumber(r4.id) >= 0) {
        return value;
      }
    } else if (r4.type === 10003) {
      if (j(resourceManager.getStringSync(r4.id))) {
        return value;
      }
    }
  } else if (typeof value === 'number') {
    if (value >= 0) {
      return value;
    }
  } else if (typeof value === 'string') {
    if (isValid(value)) {
      return value;
    }
  }
  return defaultValue;
}
function i(dimension, q4) {
  const matches = dimension.match(q4);
  if (!matches || matches.length < 3) {
    return false;
  }
  const value = Number.parseFloat(matches[1]);
  return value >= 0;
}
function j(dimension) {
  return i(
    dimension,
    new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i')
  );
}
function d4(dimension) {
  return i(
    dimension,
    new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx)?$', 'i')
  );
}
export class IconGroupSuffix extends ViewPU {
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
    this.n2 = this.initializeConsume('chipSize', 'chipSize');
    this.n4 = new SynchedPropertyObjectOneWayPU(params.items, this, 'items');
    this.symbolEffect = new SymbolEffect();
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    if (params.items === undefined) {
      this.n4.set([]);
    }
    if (params.symbolEffect !== undefined) {
      this.symbolEffect = params.symbolEffect;
    }
  }
  updateStateVars(params) {
    this.n4.reset(params.items);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.n2.purgeDependencyOnElmtId(rmElmtId);
    this.n4.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.n2.aboutToBeDeleted();
    this.n4.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get chipSize() {
    return this.n2.get();
  }
  set chipSize(newValue) {
    this.n2.set(newValue);
  }
  get items() {
    return this.n4.get();
  }
  set items(newValue) {
    this.n4.set(newValue);
  }
  getBackgroundSize() {
    if (this.chipSize === ChipSize.SMALL) {
      return e4.l4;
    } else {
      return e4.m4;
    }
  }
  getIconSize(val) {
    if (val === undefined) {
      return this.chipSize === ChipSize.SMALL ? e4.i4 : e4.j4;
    }
    let value;
    if (this.chipSize === ChipSize.SMALL) {
      value = c4(this.getUIContext(), val, j, e4.i4);
    } else {
      value = c4(this.getUIContext(), val, j, e4.j4);
    }
    return value;
  }
  SymbolItemBuilder(item, parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      SymbolGlyph.create();
      SymbolGlyph.fontColor([e4.fillColor]);
      SymbolGlyph.fontSize(this.getIconSize());
      SymbolGlyph.attributeModifier.bind(this)(item.symbol);
      SymbolGlyph.focusable(true);
      SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
      SymbolGlyph.symbolEffect(this.symbolEffect, false);
      SymbolGlyph.symbolEffect(this.symbolEffect, e4.o1);
    }, SymbolGlyph);
  }
  IconItemBuilder(item, parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Image.create(item.icon.src);
      Image.fillColor(e4.fillColor);
      Image.size({
        width: this.getIconSize(item.icon.size?.width),
        height: this.getIconSize(item.icon.size?.height),
      });
      Image.focusable(true);
    }, Image);
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create({ space: 8 });
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      ForEach.create();
      const forEachItemGenFunction = (_item) => {
        const p4 = _item;
        this.observeComponentCreation2((elmtId, isInitialRender) => {
          Button.createWithChild();
          Button.size({
            width: this.getBackgroundSize(),
            height: this.getBackgroundSize(),
          });
          Button.backgroundColor(e4.backgroundColor);
          Button.borderRadius(e4.borderRadius);
          Button.accessibilityText(this.getAccessibilityText(p4));
          Button.accessibilityDescription(this.getAccessibilityDescription(p4));
          Button.accessibilityLevel(this.getAccessibilityLevel(p4));
          Button.onClick(() => {
            if (!(p4 instanceof SymbolGlyphModifier)) {
              p4.action();
            }
          });
          Button.borderRadius(e4.borderRadius);
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (p4 instanceof SymbolGlyphModifier) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((elmtId, isInitialRender) => {
                SymbolGlyph.create();
                SymbolGlyph.fontColor([e4.fillColor]);
                SymbolGlyph.fontSize(this.getIconSize());
                SymbolGlyph.attributeModifier.bind(this)(p4);
                SymbolGlyph.focusable(true);
                SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                SymbolGlyph.symbolEffect(this.symbolEffect, false);
                SymbolGlyph.symbolEffect(this.symbolEffect, e4.o1);
              }, SymbolGlyph);
            });
          } else if (this.isSymbolItem(p4)) {
            this.ifElseBranchUpdateFunction(1, () => {
              this.SymbolItemBuilder.bind(this)(p4);
            });
          } else {
            this.ifElseBranchUpdateFunction(2, () => {
              this.IconItemBuilder.bind(this)(p4);
            });
          }
        }, If);
        If.pop();
        Button.pop();
      };
      this.forEachUpdateFunction(
        elmtId,
        this.items || [],
        forEachItemGenFunction
      );
    }, ForEach);
    ForEach.pop();
    Row.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
  isSymbolItem(item) {
    return typeof item.symbol !== 'undefined';
  }
  getAccessibilityLevel(item) {
    if (item instanceof SymbolGlyphModifier) {
      return 'auto';
    }
    return item.accessibilityLevel ?? 'auto';
  }
  getAccessibilityDescription(item) {
    if (
      item instanceof SymbolGlyphModifier ||
      typeof item.accessibilityDescription === 'undefined'
    ) {
      return undefined;
    }
    return item.accessibilityDescription;
  }
  getAccessibilityText(item) {
    if (
      item instanceof SymbolGlyphModifier ||
      typeof item.accessibilityText === 'undefined'
    ) {
      return undefined;
    }
    return item.accessibilityText;
  }
  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
export class ChipGroup extends ViewPU {
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
    this.n4 = new SynchedPropertyObjectOneWayPU(params.items, this, 'items');
    this.o4 = new SynchedPropertyObjectOneWayPU(
      params.itemStyle,
      this,
      'itemStyle'
    );
    this.n2 = new ObservedPropertyObjectPU(b1.itemStyle.size, this, 'chipSize');
    this.addProvidedVar('chipSize', this.n2, false);
    this.q4 = new SynchedPropertyObjectOneWayPU(
      params.selectedIndexes,
      this,
      'selectedIndexes'
    );
    this.r4 = new SynchedPropertySimpleOneWayPU(
      params.multiple,
      this,
      'multiple'
    );
    this.s4 = new SynchedPropertyObjectOneWayPU(
      params.chipGroupSpace,
      this,
      'chipGroupSpace'
    );
    this.suffix = undefined;
    this.onChange = c1;
    this.scroller = new Scroller();
    this.t4 = new ObservedPropertySimplePU(
      this.scroller.isAtEnd(),
      this,
      'isReachEnd'
    );
    this.u4 = new SynchedPropertyObjectOneWayPU(
      params.chipGroupPadding,
      this,
      'chipGroupPadding'
    );
    this.v4 = new ObservedPropertySimplePU(true, this, 'isRefresh');
    this.setInitiallyProvidedValue(params);
    this.declareWatch('items', this.onItemsChange);
    this.declareWatch('itemStyle', this.itemStyleOnChange);
    this.declareWatch('multiple', this.onMultipleChange);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    if (params.items === undefined) {
      this.n4.set([]);
    }
    if (params.itemStyle === undefined) {
      this.o4.set(b1.itemStyle);
    }
    if (params.chipSize !== undefined) {
      this.chipSize = params.chipSize;
    }
    if (params.selectedIndexes === undefined) {
      this.q4.set([0]);
    }
    if (params.multiple === undefined) {
      this.r4.set(false);
    }
    if (params.chipGroupSpace === undefined) {
      this.s4.set(b1.chipGroupSpace);
    }
    if (params.suffix !== undefined) {
      this.suffix = params.suffix;
    }
    if (params.onChange !== undefined) {
      this.onChange = params.onChange;
    }
    if (params.scroller !== undefined) {
      this.scroller = params.scroller;
    }
    if (params.isReachEnd !== undefined) {
      this.isReachEnd = params.isReachEnd;
    }
    if (params.chipGroupPadding === undefined) {
      this.u4.set(b1.chipGroupPadding);
    }
    if (params.isRefresh !== undefined) {
      this.isRefresh = params.isRefresh;
    }
  }
  updateStateVars(params) {
    this.n4.reset(params.items);
    this.o4.reset(params.itemStyle);
    this.q4.reset(params.selectedIndexes);
    this.r4.reset(params.multiple);
    this.s4.reset(params.chipGroupSpace);
    this.u4.reset(params.chipGroupPadding);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.n4.purgeDependencyOnElmtId(rmElmtId);
    this.o4.purgeDependencyOnElmtId(rmElmtId);
    this.n2.purgeDependencyOnElmtId(rmElmtId);
    this.q4.purgeDependencyOnElmtId(rmElmtId);
    this.r4.purgeDependencyOnElmtId(rmElmtId);
    this.s4.purgeDependencyOnElmtId(rmElmtId);
    this.t4.purgeDependencyOnElmtId(rmElmtId);
    this.u4.purgeDependencyOnElmtId(rmElmtId);
    this.v4.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.n4.aboutToBeDeleted();
    this.o4.aboutToBeDeleted();
    this.n2.aboutToBeDeleted();
    this.q4.aboutToBeDeleted();
    this.r4.aboutToBeDeleted();
    this.s4.aboutToBeDeleted();
    this.t4.aboutToBeDeleted();
    this.u4.aboutToBeDeleted();
    this.v4.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get items() {
    return this.n4.get();
  }
  set items(newValue) {
    this.n4.set(newValue);
  }
  get itemStyle() {
    return this.o4.get();
  }
  set itemStyle(newValue) {
    this.o4.set(newValue);
  }
  get chipSize() {
    return this.n2.get();
  }
  set chipSize(newValue) {
    this.n2.set(newValue);
  }
  get selectedIndexes() {
    return this.q4.get();
  }
  set selectedIndexes(newValue) {
    this.q4.set(newValue);
  }
  get multiple() {
    return this.r4.get();
  }
  set multiple(newValue) {
    this.r4.set(newValue);
  }
  get chipGroupSpace() {
    return this.s4.get();
  }
  set chipGroupSpace(newValue) {
    this.s4.set(newValue);
  }
  get isReachEnd() {
    return this.t4.get();
  }
  set isReachEnd(newValue) {
    this.t4.set(newValue);
  }
  get chipGroupPadding() {
    return this.u4.get();
  }
  set chipGroupPadding(newValue) {
    this.u4.set(newValue);
  }
  get isRefresh() {
    return this.v4.get();
  }
  set isRefresh(newValue) {
    this.v4.set(newValue);
  }
  onItemsChange() {
    this.isRefresh = !this.isRefresh;
  }
  onMultipleChange() {
    this.selectedIndexes = this.getSelectedIndexes();
  }
  itemStyleOnChange() {
    this.chipSize = this.getChipSize();
  }
  aboutToAppear() {
    this.itemStyleOnChange();
    if (this.getSelectedIndexes().length === 0) {
      this.selectedIndexes = [0];
    }
  }
  getChipSize() {
    if (this.itemStyle && this.itemStyle.size) {
      if (typeof this.itemStyle.size === 'object') {
        if (
          !this.itemStyle.size.width ||
          !this.itemStyle.size.height ||
          !this.itemStyle.size
        ) {
          return b1.itemStyle.size;
        }
      }
      return this.itemStyle.size;
    }
    return b1.itemStyle.size;
  }
  getFontColor() {
    if (this.itemStyle && this.itemStyle.fontColor) {
      if (typeof this.itemStyle.fontColor === 'object') {
        let o4 = this.itemStyle.fontColor;
        if (o4 == undefined || o4 == null) {
          return b1.itemStyle.fontColor;
        }
        if (o4.type === 10001) {
          return this.itemStyle.fontColor;
        }
        return b1.itemStyle.fontColor;
      }
      return this.itemStyle.fontColor;
    }
    return b1.itemStyle.fontColor;
  }
  getSelectedFontColor() {
    if (this.itemStyle && this.itemStyle.selectedFontColor) {
      if (typeof this.itemStyle.selectedFontColor === 'object') {
        let n4 = this.itemStyle.selectedFontColor;
        if (n4 == undefined || n4 == null) {
          return b1.itemStyle.selectedFontColor;
        }
        if (n4.type === 10001) {
          return this.itemStyle.selectedFontColor;
        }
        return b1.itemStyle.selectedFontColor;
      }
      return this.itemStyle.selectedFontColor;
    }
    return b1.itemStyle.selectedFontColor;
  }
  getFillColor() {
    if (this.itemStyle && this.itemStyle.fontColor) {
      return this.itemStyle.fontColor;
    }
    return b1.itemStyle.fillColor;
  }
  getSelectedFillColor() {
    if (this.itemStyle && this.itemStyle.selectedFontColor) {
      return this.itemStyle.selectedFontColor;
    }
    return b1.itemStyle.h4;
  }
  getBackgroundColor() {
    if (this.itemStyle && this.itemStyle.backgroundColor) {
      if (typeof this.itemStyle.backgroundColor === 'object') {
        let m4 = this.itemStyle.backgroundColor;
        if (m4 == undefined || m4 == null) {
          return b1.itemStyle.backgroundColor;
        }
        if (m4.type === 10001) {
          return this.itemStyle.backgroundColor;
        }
        return b1.itemStyle.backgroundColor;
      }
      return this.itemStyle.backgroundColor;
    }
    return b1.itemStyle.backgroundColor;
  }
  getSelectedBackgroundColor() {
    if (this.itemStyle && this.itemStyle.selectedBackgroundColor) {
      if (typeof this.itemStyle.selectedBackgroundColor === 'object') {
        let l4 = this.itemStyle.selectedBackgroundColor;
        if (l4 == undefined || l4 == null) {
          return b1.itemStyle.selectedBackgroundColor;
        }
        if (l4.type === 10001) {
          return this.itemStyle.selectedBackgroundColor;
        }
        return b1.itemStyle.selectedBackgroundColor;
      }
      return this.itemStyle.selectedBackgroundColor;
    }
    return b1.itemStyle.selectedBackgroundColor;
  }
  getSelectedIndexes() {
    let k4 = [];
    k4 = (this.selectedIndexes ?? [0]).filter((element, index, array) => {
      return (
        element >= 0 &&
        element % 1 == 0 &&
        element != null &&
        element != undefined &&
        array.indexOf(element) === index &&
        element < (this.items || []).length
      );
    });
    return k4;
  }
  isMultiple() {
    return this.multiple ?? false;
  }
  getChipGroupItemSpace() {
    if (this.chipGroupSpace == undefined) {
      return b1.chipGroupSpace.itemSpace;
    }
    return c4(
      this.getUIContext(),
      this.chipGroupSpace.itemSpace,
      d4,
      b1.chipGroupSpace.itemSpace
    );
  }
  getChipGroupStartSpace() {
    if (this.chipGroupSpace == undefined) {
      return b1.chipGroupSpace.startSpace;
    }
    return c4(
      this.getUIContext(),
      this.chipGroupSpace.startSpace,
      d4,
      b1.chipGroupSpace.startSpace
    );
  }
  getChipGroupEndSpace() {
    if (this.chipGroupSpace == undefined) {
      return b1.chipGroupSpace.endSpace;
    }
    return c4(
      this.getUIContext(),
      this.chipGroupSpace.endSpace,
      d4,
      b1.chipGroupSpace.endSpace
    );
  }
  getOnChange() {
    return this.onChange ?? c1;
  }
  isSelected(itemIndex) {
    if (!this.isMultiple()) {
      return itemIndex == this.getSelectedIndexes()[0];
    } else {
      return this.getSelectedIndexes().some((element, index, array) => {
        return element == itemIndex;
      });
    }
  }
  getPaddingTop() {
    if (!this.chipGroupPadding || !this.chipGroupPadding.top) {
      return b1.chipGroupPadding.top;
    }
    return c4(
      this.getUIContext(),
      this.chipGroupPadding.top,
      d4,
      b1.chipGroupPadding.top
    );
  }
  getPaddingBottom() {
    if (!this.chipGroupPadding || !this.chipGroupPadding.bottom) {
      return b1.chipGroupPadding.bottom;
    }
    return c4(
      this.getUIContext(),
      this.chipGroupPadding.bottom,
      d4,
      b1.chipGroupPadding.bottom
    );
  }
  getChipGroupHeight() {
    if (typeof this.chipSize === 'string') {
      if (this.chipSize === ChipSize.NORMAL) {
        return f4.NORMAL;
      } else {
        return f4.SMALL;
      }
    } else if (typeof this.chipSize === 'object') {
      return this.chipSize.height;
    } else {
      return f4.NORMAL;
    }
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create();
      Row.align(Alignment.End);
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Stack.create();
      Stack.padding({
        top: this.getPaddingTop(),
        bottom: this.getPaddingBottom(),
      });
      Stack.layoutWeight(1);
      Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
      Stack.alignContent(Alignment.End);
    }, Stack);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Scroll.create(this.scroller);
      Scroll.scrollable(ScrollDirection.Horizontal);
      Scroll.scrollBar(BarState.Off);
      Scroll.align(Alignment.Start);
      Scroll.width('100%');
      Scroll.clip(false);
      Scroll.onScroll(() => {
        this.isReachEnd = this.scroller.isAtEnd();
      });
    }, Scroll);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create({ space: this.getChipGroupItemSpace() });
      Row.padding({
        left: this.getChipGroupStartSpace(),
        right: this.getChipGroupEndSpace(),
      });
      Row.constraintSize({ minWidth: '100%' });
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      ForEach.create();
      const forEachItemGenFunction = (_item, index) => {
        const j4 = _item;
        this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (j4) {
            this.ifElseBranchUpdateFunction(0, () => {
              Chip.bind(this)(
                makeBuilderParameterProxy('Chip', {
                  prefixIcon: () => this.getPrefixIcon(j4),
                  prefixSymbol: () => j4?.prefixSymbol,
                  label: () => ({
                    text: j4?.label?.text ?? ' ',
                    fontColor: this.getFontColor(),
                    activatedFontColor: this.getSelectedFontColor(),
                  }),
                  suffixIcon: () => this.getSuffixIcon(j4),
                  suffixSymbol: () => j4?.suffixSymbol,
                  suffixSymbolOptions: () => j4.suffixSymbolOptions,
                  allowClose: () => j4.allowClose ?? false,
                  closeOptions: () => j4.closeOptions,
                  enabled: () => true,
                  activated: () => this.isSelected(index),
                  backgroundColor: () => this.getBackgroundColor(),
                  size: () => this.getChipSize(),
                  activatedBackgroundColor: () =>
                    this.getSelectedBackgroundColor(),
                  accessibilitySelectedType: () =>
                    this.multiple
                      ? AccessibilitySelectedType.CHECKED
                      : AccessibilitySelectedType.SELECTED,
                  accessibilityDescription: () => j4.accessibilityDescription,
                  accessibilityLevel: () => j4.accessibilityLevel,
                  onClicked: () => () => {
                    if (this.isSelected(index)) {
                      if (!!this.isMultiple()) {
                        if (this.getSelectedIndexes().length > 1) {
                          this.selectedIndexes.splice(
                            this.selectedIndexes.indexOf(index),
                            1
                          );
                        }
                      }
                    } else {
                      if (
                        !this.selectedIndexes ||
                        this.selectedIndexes.length === 0
                      ) {
                        this.selectedIndexes = this.getSelectedIndexes();
                      }
                      if (!this.isMultiple()) {
                        this.selectedIndexes = [];
                      }
                      this.selectedIndexes.push(index);
                    }
                    this.getOnChange()(this.getSelectedIndexes());
                  },
                })
              );
            });
          } else {
            this.ifElseBranchUpdateFunction(1, () => {});
          }
        }, If);
        If.pop();
      };
      this.forEachUpdateFunction(
        elmtId,
        this.items || [],
        forEachItemGenFunction,
        () => {
          return JSON.stringify(this.isRefresh);
        },
        true,
        false
      );
    }, ForEach);
    ForEach.pop();
    Row.pop();
    Scroll.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.suffix && !this.isReachEnd) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.width(e4.m4);
            Stack.height(this.getChipGroupHeight());
            Stack.linearGradient({ angle: 90, colors: colorStops });
            Stack.blendMode(BlendMode.DST_IN, BlendApplyType.OFFSCREEN);
            Stack.hitTestBehavior(HitTestMode.None);
          }, Stack);
          Stack.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
      }
    }, If);
    If.pop();
    Stack.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.suffix) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.padding({
              left: e4.marginLeft,
              right: e4.marginRight,
            });
          }, Row);
          this.suffix.bind(this)();
          Row.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
      }
    }, If);
    If.pop();
    Row.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
  getPrefixIcon(i4) {
    return {
      src: i4.prefixIcon?.src ?? '',
      size: i4.prefixIcon?.size ?? undefined,
      fillColor: this.getFillColor(),
      activatedFillColor: this.getSelectedFillColor(),
    };
  }
  getSuffixIcon(h4) {
    if (typeof h4.suffixImageIcon !== 'undefined') {
      return {
        src: h4.suffixImageIcon.src,
        size: h4.suffixImageIcon.size,
        fillColor: this.getFillColor(),
        activatedFillColor: this.getSelectedFillColor(),
        action: h4.suffixImageIcon.action,
        accessibilityText: h4.suffixImageIcon.accessibilityText,
        accessibilityDescription: h4.suffixImageIcon.accessibilityDescription,
        accessibilityLevel: h4.suffixImageIcon.accessibilityLevel,
      };
    }
    return {
      src: h4.suffixIcon?.src ?? '',
      size: h4.suffixIcon?.size ?? undefined,
      fillColor: this.getFillColor(),
      activatedFillColor: this.getSelectedFillColor(),
    };
  }
  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}

export default {
  ChipGroup,
  IconGroupSuffix,
};
