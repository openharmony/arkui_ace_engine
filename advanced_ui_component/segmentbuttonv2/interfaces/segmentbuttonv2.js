/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

var o =
  (this && this.o) ||
  function (o1, target, key, desc) {
    var c = arguments.length,
      r =
        c < 3
          ? target
          : desc === null
          ? (desc = Object.getOwnPropertyDescriptor(target, key))
          : desc,
      d;
    if (typeof Reflect === 'object' && typeof Reflect.j1 === 'function')
      r = Reflect.j1(o1, target, key, desc);
    else
      for (var p1 = o1.length - 1; p1 >= 0; p1--)
        if ((d = o1[p1]))
          r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
  };
if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {});
}
if (PUV2ViewBase.contextStack === undefined) {
  Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const curves = requireNativeModule('ohos.curves');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const i18n = requireNapi('i18n');
const util = requireNapi('util');
const t = 1;
const u = 2;
const a1 = 0;
const b1 = 1;
const c1 = {
  buttonBackgroundColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.segment_button_v2_tab_button_background'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  buttonBorderRadius: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_background_corner_radius'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  buttonMinHeight: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_singleline_background_height'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  l1: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_doubleline_background_height'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  buttonPadding: {
    id: -1,
    type: 10002,
    params: ['sys.float.padding_level1'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSelectedBackgroundColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.segment_button_v2_tab_selected_item_background'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemBorderRadius: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_selected_corner_radius'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSpace: LengthMetrics.vp(0),
  itemFontSize: {
    id: -1,
    type: 10002,
    params: ['sys.float.ohos_id_text_size_button2'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemFontColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_secondary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSelectedFontColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemFontWeight: FontWeight.Medium,
  itemSelectedFontWeight: FontWeight.Medium,
  itemIconSize: 24,
  itemIconFillColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_secondary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSelectedIconFillColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSymbolFontSize: 20,
  itemSymbolFontColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_secondary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSelectedSymbolFontColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemMinHeight: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_singleline_selected_height'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  m1: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_doubleline_selected_height'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemPadding: {
    top: LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.padding_level2'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }),
    bottom: LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.padding_level2'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }),
    start: LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.padding_level4'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }),
    end: LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.padding_level4'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }),
  },
  itemShadow: ShadowStyle.OUTER_DEFAULT_XS,
  itemMaxFontScale: t,
  n1: t,
  o1: u,
  itemMinFontScale: a1,
  q1: a1,
  s1: b1,
};
const d1 = {
  buttonBackgroundColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.segment_button_v2_tab_button_background'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  buttonBorderRadius: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_background_corner_radius'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  buttonMinHeight: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_singleline_background_height'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  l1: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_doubleline_background_height'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  buttonPadding: {
    id: -1,
    type: 10002,
    params: ['sys.float.padding_level1'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSelectedBackgroundColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.comp_background_emphasize'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemBorderRadius: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_selected_corner_radius'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSpace: LengthMetrics.vp(0),
  itemFontSize: {
    id: -1,
    type: 10002,
    params: ['sys.float.ohos_id_text_size_button2'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemFontColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_secondary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSelectedFontColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_on_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemFontWeight: FontWeight.Medium,
  itemSelectedFontWeight: FontWeight.Medium,
  itemIconSize: 24,
  itemIconFillColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.icon_secondary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSelectedIconFillColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_on_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSymbolFontSize: 20,
  itemSymbolFontColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_secondary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSelectedSymbolFontColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_on_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemMinHeight: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_singleline_selected_height'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  m1: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_doubleline_selected_height'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemPadding: {
    top: LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.padding_level2'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }),
    bottom: LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.padding_level2'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }),
    start: LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.padding_level4'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }),
    end: LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.padding_level4'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }),
  },
  itemShadow: ShadowStyle.OUTER_DEFAULT_XS,
  itemMaxFontScale: t,
  n1: t,
  o1: u,
  itemMinFontScale: a1,
  q1: a1,
  s1: b1,
};
let SegmentButtonV2Item = class SegmentButtonV2Item {
  constructor(options) {
    this.text = options.text;
    this.icon = options.icon;
    this.symbol = options.symbol;
    this.enabled = options.enabled ?? true;
    this.textModifier = options.textModifier;
    this.iconModifier = options.iconModifier;
    this.symbolModifier = options.symbolModifier;
    this.accessibilityText = options.accessibilityText;
    this.accessibilityDescription = options.accessibilityDescription;
    this.accessibilityLevel = options.accessibilityLevel;
  }
  get isHybrid() {
    return !!this.text && (!!this.icon || !!this.symbol);
  }
};
o([Trace], SegmentButtonV2Item.prototype, 'text', void 0);
o([Trace], SegmentButtonV2Item.prototype, 'icon', void 0);
o([Trace], SegmentButtonV2Item.prototype, 'symbol', void 0);
o([Trace], SegmentButtonV2Item.prototype, 'enabled', void 0);
o([Trace], SegmentButtonV2Item.prototype, 'textModifier', void 0);
o([Trace], SegmentButtonV2Item.prototype, 'iconModifier', void 0);
o([Trace], SegmentButtonV2Item.prototype, 'symbolModifier', void 0);
o([Trace], SegmentButtonV2Item.prototype, 'accessibilityText', void 0);
o([Trace], SegmentButtonV2Item.prototype, 'accessibilityDescription', void 0);
o([Trace], SegmentButtonV2Item.prototype, 'accessibilityLevel', void 0);
o([Computed], SegmentButtonV2Item.prototype, 'isHybrid', null);
SegmentButtonV2Item = o([ObservedV2], SegmentButtonV2Item);
export { SegmentButtonV2Item };
let SegmentButtonV2Items = class SegmentButtonV2Items extends Array {
  constructor(n1) {
    super(typeof n1 === 'number' ? n1 : 0);
    if (typeof n1 !== 'number' && n1 && n1.length) {
      for (let options of n1) {
        if (options) {
          this.push(new SegmentButtonV2Item(options));
        }
      }
    }
  }
  get hasHybrid() {
    return this.some((item) => item.isHybrid);
  }
};
o([Computed], SegmentButtonV2Items.prototype, 'hasHybrid', null);
SegmentButtonV2Items = o([ObservedV2], SegmentButtonV2Items);
export { SegmentButtonV2Items };
const e1 = new SegmentButtonV2Items([]);
export class TabSegmentButtonV2 extends ViewV2 {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda,
    extraInfo
  ) {
    super(parent, elmtId, extraInfo);
    this.initParam(
      'items',
      params && 'items' in params ? params.items : undefined
    );
    this.initParam(
      'selectedIndex',
      params && 'selectedIndex' in params ? params.selectedIndex : undefined
    );
    this.$selectedIndex =
      '$selectedIndex' in params ? params.$selectedIndex : () => {};
    this.onItemClicked =
      'onItemClicked' in params ? params.onItemClicked : () => {};
    this.initParam(
      'itemMinFontScale',
      params && 'itemMinFontScale' in params
        ? params.itemMinFontScale
        : undefined
    );
    this.initParam(
      'itemMaxFontScale',
      params && 'itemMaxFontScale' in params
        ? params.itemMaxFontScale
        : undefined
    );
    this.initParam(
      'itemSpace',
      params && 'itemSpace' in params ? params.itemSpace : undefined
    );
    this.initParam(
      'itemFontSize',
      params && 'itemFontSize' in params ? params.itemFontSize : undefined
    );
    this.initParam(
      'itemSelectedFontSize',
      params && 'itemSelectedFontSize' in params
        ? params.itemSelectedFontSize
        : undefined
    );
    this.initParam(
      'itemFontColor',
      params && 'itemFontColor' in params ? params.itemFontColor : undefined
    );
    this.initParam(
      'itemSelectedFontColor',
      params && 'itemSelectedFontColor' in params
        ? params.itemSelectedFontColor
        : undefined
    );
    this.initParam(
      'itemFontWeight',
      params && 'itemFontWeight' in params ? params.itemFontWeight : undefined
    );
    this.initParam(
      'itemSelectedFontWeight',
      params && 'itemSelectedFontWeight' in params
        ? params.itemSelectedFontWeight
        : undefined
    );
    this.initParam(
      'itemBorderRadius',
      params && 'itemBorderRadius' in params
        ? params.itemBorderRadius
        : undefined
    );
    this.initParam(
      'itemSelectedBackgroundColor',
      params && 'itemSelectedBackgroundColor' in params
        ? params.itemSelectedBackgroundColor
        : undefined
    );
    this.initParam(
      'itemIconSize',
      params && 'itemIconSize' in params ? params.itemIconSize : undefined
    );
    this.initParam(
      'itemIconFillColor',
      params && 'itemIconFillColor' in params
        ? params.itemIconFillColor
        : undefined
    );
    this.initParam(
      'itemSelectedIconFillColor',
      params && 'itemSelectedIconFillColor' in params
        ? params.itemSelectedIconFillColor
        : undefined
    );
    this.initParam(
      'itemSymbolFontSize',
      params && 'itemSymbolFontSize' in params
        ? params.itemSymbolFontSize
        : undefined
    );
    this.initParam(
      'itemSymbolFontColor',
      params && 'itemSymbolFontColor' in params
        ? params.itemSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemSelectedSymbolFontColor',
      params && 'itemSelectedSymbolFontColor' in params
        ? params.itemSelectedSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemMinHeight',
      params && 'itemMinHeight' in params ? params.itemMinHeight : undefined
    );
    this.initParam(
      'itemPadding',
      params && 'itemPadding' in params ? params.itemPadding : undefined
    );
    this.initParam(
      'itemShadow',
      params && 'itemShadow' in params ? params.itemShadow : undefined
    );
    this.initParam(
      'buttonBackgroundColor',
      params && 'buttonBackgroundColor' in params
        ? params.buttonBackgroundColor
        : undefined
    );
    this.initParam(
      'buttonBackgroundBlurStyle',
      params && 'buttonBackgroundBlurStyle' in params
        ? params.buttonBackgroundBlurStyle
        : undefined
    );
    this.initParam(
      'buttonBackgroundBlurStyleOptions',
      params && 'buttonBackgroundBlurStyleOptions' in params
        ? params.buttonBackgroundBlurStyleOptions
        : undefined
    );
    this.initParam(
      'buttonBackgroundEffect',
      params && 'buttonBackgroundEffect' in params
        ? params.buttonBackgroundEffect
        : undefined
    );
    this.initParam(
      'buttonBorderRadius',
      params && 'buttonBorderRadius' in params
        ? params.buttonBorderRadius
        : undefined
    );
    this.initParam(
      'buttonMinHeight',
      params && 'buttonMinHeight' in params ? params.buttonMinHeight : undefined
    );
    this.initParam(
      'buttonPadding',
      params && 'buttonPadding' in params ? params.buttonPadding : undefined
    );
    this.initParam(
      'languageDirection',
      params && 'languageDirection' in params
        ? params.languageDirection
        : undefined
    );
    this.finalizeConstruction();
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    {
      this.observeComponentCreation2(
        (elmtId, isInitialRender) => {
          if (isInitialRender) {
            let componentCall = new f1(
              this,
              {
                theme: c1,
                items: this.items,
                selectedIndex: this.selectedIndex,
                $selectedIndex: (selectedIndex) => {
                  this.$selectedIndex?.(selectedIndex);
                },
                onItemClicked: this.onItemClicked,
                itemMinFontScale: this.itemMinFontScale,
                itemMaxFontScale: this.itemMaxFontScale,
                itemSpace: this.itemSpace,
                itemFontColor: this.itemFontColor,
                itemSelectedFontColor: this.itemSelectedFontColor,
                itemFontSize: this.itemFontSize,
                itemSelectedFontSize: this.itemSelectedFontSize,
                itemFontWeight: this.itemFontWeight,
                itemSelectedFontWeight: this.itemSelectedFontWeight,
                itemSelectedBackgroundColor: this.itemSelectedBackgroundColor,
                itemIconSize: this.itemIconSize,
                itemIconFillColor: this.itemIconFillColor,
                itemSelectedIconFillColor: this.itemSelectedIconFillColor,
                itemSymbolFontSize: this.itemSymbolFontSize,
                itemSymbolFontColor: this.itemSymbolFontColor,
                itemSelectedSymbolFontColor: this.itemSelectedSymbolFontColor,
                itemBorderRadius: this.itemBorderRadius,
                itemMinHeight: this.itemMinHeight,
                itemPadding: this.itemPadding,
                itemShadow: this.itemShadow,
                buttonBackgroundColor: this.buttonBackgroundColor,
                buttonBackgroundBlurStyle: this.buttonBackgroundBlurStyle,
                buttonBackgroundBlurStyleOptions:
                  this.buttonBackgroundBlurStyleOptions,
                buttonBackgroundEffect: this.buttonBackgroundEffect,
                buttonBorderRadius: this.buttonBorderRadius,
                buttonMinHeight: this.buttonMinHeight,
                buttonPadding: this.buttonPadding,
                languageDirection: this.languageDirection,
              },
              undefined,
              elmtId,
              () => {},
              {
                page: 'advancedComponents/src/main/ets/components/SegmentButtonV2.ets',
                line: 295,
                t1: 5,
              }
            );
            ViewV2.create(componentCall);
            let paramsLambda = () => {
              return {
                theme: c1,
                items: this.items,
                selectedIndex: this.selectedIndex,
                $selectedIndex: (selectedIndex) => {
                  this.$selectedIndex?.(selectedIndex);
                },
                onItemClicked: this.onItemClicked,
                itemMinFontScale: this.itemMinFontScale,
                itemMaxFontScale: this.itemMaxFontScale,
                itemSpace: this.itemSpace,
                itemFontColor: this.itemFontColor,
                itemSelectedFontColor: this.itemSelectedFontColor,
                itemFontSize: this.itemFontSize,
                itemSelectedFontSize: this.itemSelectedFontSize,
                itemFontWeight: this.itemFontWeight,
                itemSelectedFontWeight: this.itemSelectedFontWeight,
                itemSelectedBackgroundColor: this.itemSelectedBackgroundColor,
                itemIconSize: this.itemIconSize,
                itemIconFillColor: this.itemIconFillColor,
                itemSelectedIconFillColor: this.itemSelectedIconFillColor,
                itemSymbolFontSize: this.itemSymbolFontSize,
                itemSymbolFontColor: this.itemSymbolFontColor,
                itemSelectedSymbolFontColor: this.itemSelectedSymbolFontColor,
                itemBorderRadius: this.itemBorderRadius,
                itemMinHeight: this.itemMinHeight,
                itemPadding: this.itemPadding,
                itemShadow: this.itemShadow,
                buttonBackgroundColor: this.buttonBackgroundColor,
                buttonBackgroundBlurStyle: this.buttonBackgroundBlurStyle,
                buttonBackgroundBlurStyleOptions:
                  this.buttonBackgroundBlurStyleOptions,
                buttonBackgroundEffect: this.buttonBackgroundEffect,
                buttonBorderRadius: this.buttonBorderRadius,
                buttonMinHeight: this.buttonMinHeight,
                buttonPadding: this.buttonPadding,
                languageDirection: this.languageDirection,
              };
            };
            componentCall.paramsGenerator_ = paramsLambda;
          } else {
            this.updateStateVarsOfChildByElmtId(elmtId, {
              theme: c1,
              items: this.items,
              selectedIndex: this.selectedIndex,
              itemMinFontScale: this.itemMinFontScale,
              itemMaxFontScale: this.itemMaxFontScale,
              itemSpace: this.itemSpace,
              itemFontColor: this.itemFontColor,
              itemSelectedFontColor: this.itemSelectedFontColor,
              itemFontSize: this.itemFontSize,
              itemSelectedFontSize: this.itemSelectedFontSize,
              itemFontWeight: this.itemFontWeight,
              itemSelectedFontWeight: this.itemSelectedFontWeight,
              itemSelectedBackgroundColor: this.itemSelectedBackgroundColor,
              itemIconSize: this.itemIconSize,
              itemIconFillColor: this.itemIconFillColor,
              itemSelectedIconFillColor: this.itemSelectedIconFillColor,
              itemSymbolFontSize: this.itemSymbolFontSize,
              itemSymbolFontColor: this.itemSymbolFontColor,
              itemSelectedSymbolFontColor: this.itemSelectedSymbolFontColor,
              itemBorderRadius: this.itemBorderRadius,
              itemMinHeight: this.itemMinHeight,
              itemPadding: this.itemPadding,
              itemShadow: this.itemShadow,
              buttonBackgroundColor: this.buttonBackgroundColor,
              buttonBackgroundBlurStyle: this.buttonBackgroundBlurStyle,
              buttonBackgroundBlurStyleOptions:
                this.buttonBackgroundBlurStyleOptions,
              buttonBackgroundEffect: this.buttonBackgroundEffect,
              buttonBorderRadius: this.buttonBorderRadius,
              buttonMinHeight: this.buttonMinHeight,
              buttonPadding: this.buttonPadding,
              languageDirection: this.languageDirection,
            });
          }
        },
        { name: 'SimpleSegmentButtonV2' }
      );
    }
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('items' in params) {
      this.updateParam('items', params.items);
    }
    if ('selectedIndex' in params) {
      this.updateParam('selectedIndex', params.selectedIndex);
    }
    if ('itemMinFontScale' in params) {
      this.updateParam('itemMinFontScale', params.itemMinFontScale);
    }
    if ('itemMaxFontScale' in params) {
      this.updateParam('itemMaxFontScale', params.itemMaxFontScale);
    }
    if ('itemSpace' in params) {
      this.updateParam('itemSpace', params.itemSpace);
    }
    if ('itemFontSize' in params) {
      this.updateParam('itemFontSize', params.itemFontSize);
    }
    if ('itemSelectedFontSize' in params) {
      this.updateParam('itemSelectedFontSize', params.itemSelectedFontSize);
    }
    if ('itemFontColor' in params) {
      this.updateParam('itemFontColor', params.itemFontColor);
    }
    if ('itemSelectedFontColor' in params) {
      this.updateParam('itemSelectedFontColor', params.itemSelectedFontColor);
    }
    if ('itemFontWeight' in params) {
      this.updateParam('itemFontWeight', params.itemFontWeight);
    }
    if ('itemSelectedFontWeight' in params) {
      this.updateParam('itemSelectedFontWeight', params.itemSelectedFontWeight);
    }
    if ('itemBorderRadius' in params) {
      this.updateParam('itemBorderRadius', params.itemBorderRadius);
    }
    if ('itemSelectedBackgroundColor' in params) {
      this.updateParam(
        'itemSelectedBackgroundColor',
        params.itemSelectedBackgroundColor
      );
    }
    if ('itemIconSize' in params) {
      this.updateParam('itemIconSize', params.itemIconSize);
    }
    if ('itemIconFillColor' in params) {
      this.updateParam('itemIconFillColor', params.itemIconFillColor);
    }
    if ('itemSelectedIconFillColor' in params) {
      this.updateParam(
        'itemSelectedIconFillColor',
        params.itemSelectedIconFillColor
      );
    }
    if ('itemSymbolFontSize' in params) {
      this.updateParam('itemSymbolFontSize', params.itemSymbolFontSize);
    }
    if ('itemSymbolFontColor' in params) {
      this.updateParam('itemSymbolFontColor', params.itemSymbolFontColor);
    }
    if ('itemSelectedSymbolFontColor' in params) {
      this.updateParam(
        'itemSelectedSymbolFontColor',
        params.itemSelectedSymbolFontColor
      );
    }
    if ('itemMinHeight' in params) {
      this.updateParam('itemMinHeight', params.itemMinHeight);
    }
    if ('itemPadding' in params) {
      this.updateParam('itemPadding', params.itemPadding);
    }
    if ('itemShadow' in params) {
      this.updateParam('itemShadow', params.itemShadow);
    }
    if ('buttonBackgroundColor' in params) {
      this.updateParam('buttonBackgroundColor', params.buttonBackgroundColor);
    }
    if ('buttonBackgroundBlurStyle' in params) {
      this.updateParam(
        'buttonBackgroundBlurStyle',
        params.buttonBackgroundBlurStyle
      );
    }
    if ('buttonBackgroundBlurStyleOptions' in params) {
      this.updateParam(
        'buttonBackgroundBlurStyleOptions',
        params.buttonBackgroundBlurStyleOptions
      );
    }
    if ('buttonBackgroundEffect' in params) {
      this.updateParam('buttonBackgroundEffect', params.buttonBackgroundEffect);
    }
    if ('buttonBorderRadius' in params) {
      this.updateParam('buttonBorderRadius', params.buttonBorderRadius);
    }
    if ('buttonMinHeight' in params) {
      this.updateParam('buttonMinHeight', params.buttonMinHeight);
    }
    if ('buttonPadding' in params) {
      this.updateParam('buttonPadding', params.buttonPadding);
    }
    if ('languageDirection' in params) {
      this.updateParam('languageDirection', params.languageDirection);
    }
  }
  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
o([Param], TabSegmentButtonV2.prototype, 'items', void 0);
o([Param], TabSegmentButtonV2.prototype, 'selectedIndex', void 0);
o([Event], TabSegmentButtonV2.prototype, '$selectedIndex', void 0);
o([Event], TabSegmentButtonV2.prototype, 'onItemClicked', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemMinFontScale', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemMaxFontScale', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemSpace', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemFontSize', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemSelectedFontSize', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemFontColor', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemSelectedFontColor', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemFontWeight', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemSelectedFontWeight', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemBorderRadius', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemSelectedBackgroundColor', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemIconSize', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemIconFillColor', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemSelectedIconFillColor', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemSymbolFontSize', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemSymbolFontColor', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemSelectedSymbolFontColor', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemMinHeight', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemPadding', void 0);
o([Param], TabSegmentButtonV2.prototype, 'itemShadow', void 0);
o([Param], TabSegmentButtonV2.prototype, 'buttonBackgroundColor', void 0);
o([Param], TabSegmentButtonV2.prototype, 'buttonBackgroundBlurStyle', void 0);
o(
  [Param],
  TabSegmentButtonV2.prototype,
  'buttonBackgroundBlurStyleOptions',
  void 0
);
o([Param], TabSegmentButtonV2.prototype, 'buttonBackgroundEffect', void 0);
o([Param], TabSegmentButtonV2.prototype, 'buttonBorderRadius', void 0);
o([Param], TabSegmentButtonV2.prototype, 'buttonMinHeight', void 0);
o([Param], TabSegmentButtonV2.prototype, 'buttonPadding', void 0);
o([Param], TabSegmentButtonV2.prototype, 'languageDirection', void 0);
export class CapsuleSegmentButtonV2 extends ViewV2 {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda,
    extraInfo
  ) {
    super(parent, elmtId, extraInfo);
    this.initParam(
      'items',
      params && 'items' in params ? params.items : undefined
    );
    this.initParam(
      'selectedIndex',
      params && 'selectedIndex' in params ? params.selectedIndex : undefined
    );
    this.$selectedIndex =
      '$selectedIndex' in params ? params.$selectedIndex : () => {};
    this.onItemClicked =
      'onItemClicked' in params ? params.onItemClicked : () => {};
    this.initParam(
      'itemMinFontScale',
      params && 'itemMinFontScale' in params
        ? params.itemMinFontScale
        : undefined
    );
    this.initParam(
      'itemMaxFontScale',
      params && 'itemMaxFontScale' in params
        ? params.itemMaxFontScale
        : undefined
    );
    this.initParam(
      'itemSpace',
      params && 'itemSpace' in params ? params.itemSpace : undefined
    );
    this.initParam(
      'itemFontColor',
      params && 'itemFontColor' in params ? params.itemFontColor : undefined
    );
    this.initParam(
      'itemSelectedFontColor',
      params && 'itemSelectedFontColor' in params
        ? params.itemSelectedFontColor
        : undefined
    );
    this.initParam(
      'itemFontSize',
      params && 'itemFontSize' in params ? params.itemFontSize : undefined
    );
    this.initParam(
      'itemSelectedFontSize',
      params && 'itemSelectedFontSize' in params
        ? params.itemSelectedFontSize
        : undefined
    );
    this.initParam(
      'itemFontWeight',
      params && 'itemFontWeight' in params ? params.itemFontWeight : undefined
    );
    this.initParam(
      'itemSelectedFontWeight',
      params && 'itemSelectedFontWeight' in params
        ? params.itemSelectedFontWeight
        : undefined
    );
    this.initParam(
      'itemBorderRadius',
      params && 'itemBorderRadius' in params
        ? params.itemBorderRadius
        : undefined
    );
    this.initParam(
      'itemSelectedBackgroundColor',
      params && 'itemSelectedBackgroundColor' in params
        ? params.itemSelectedBackgroundColor
        : undefined
    );
    this.initParam(
      'itemIconSize',
      params && 'itemIconSize' in params ? params.itemIconSize : undefined
    );
    this.initParam(
      'itemIconFillColor',
      params && 'itemIconFillColor' in params
        ? params.itemIconFillColor
        : undefined
    );
    this.initParam(
      'itemSelectedIconFillColor',
      params && 'itemSelectedIconFillColor' in params
        ? params.itemSelectedIconFillColor
        : undefined
    );
    this.initParam(
      'itemSymbolFontSize',
      params && 'itemSymbolFontSize' in params
        ? params.itemSymbolFontSize
        : undefined
    );
    this.initParam(
      'itemSymbolFontColor',
      params && 'itemSymbolFontColor' in params
        ? params.itemSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemSelectedSymbolFontColor',
      params && 'itemSelectedSymbolFontColor' in params
        ? params.itemSelectedSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemMinHeight',
      params && 'itemMinHeight' in params ? params.itemMinHeight : undefined
    );
    this.initParam(
      'itemPadding',
      params && 'itemPadding' in params ? params.itemPadding : undefined
    );
    this.initParam(
      'itemShadow',
      params && 'itemShadow' in params ? params.itemShadow : undefined
    );
    this.initParam(
      'buttonBackgroundColor',
      params && 'buttonBackgroundColor' in params
        ? params.buttonBackgroundColor
        : undefined
    );
    this.initParam(
      'buttonBackgroundBlurStyle',
      params && 'buttonBackgroundBlurStyle' in params
        ? params.buttonBackgroundBlurStyle
        : undefined
    );
    this.initParam(
      'buttonBackgroundBlurStyleOptions',
      params && 'buttonBackgroundBlurStyleOptions' in params
        ? params.buttonBackgroundBlurStyleOptions
        : undefined
    );
    this.initParam(
      'buttonBackgroundEffect',
      params && 'buttonBackgroundEffect' in params
        ? params.buttonBackgroundEffect
        : undefined
    );
    this.initParam(
      'buttonBorderRadius',
      params && 'buttonBorderRadius' in params
        ? params.buttonBorderRadius
        : undefined
    );
    this.initParam(
      'buttonMinHeight',
      params && 'buttonMinHeight' in params ? params.buttonMinHeight : undefined
    );
    this.initParam(
      'buttonPadding',
      params && 'buttonPadding' in params ? params.buttonPadding : undefined
    );
    this.initParam(
      'languageDirection',
      params && 'languageDirection' in params
        ? params.languageDirection
        : undefined
    );
    this.finalizeConstruction();
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    {
      this.observeComponentCreation2(
        (elmtId, isInitialRender) => {
          if (isInitialRender) {
            let componentCall = new f1(
              this,
              {
                theme: d1,
                items: this.items,
                selectedIndex: this.selectedIndex,
                $selectedIndex: (selectedIndex) => {
                  this.$selectedIndex?.(selectedIndex);
                },
                onItemClicked: this.onItemClicked,
                itemMinFontScale: this.itemMinFontScale,
                itemMaxFontScale: this.itemMaxFontScale,
                itemSpace: this.itemSpace,
                itemFontColor: this.itemFontColor,
                itemSelectedFontColor: this.itemSelectedFontColor,
                itemFontSize: this.itemFontSize,
                itemSelectedFontSize: this.itemSelectedFontSize,
                itemFontWeight: this.itemFontWeight,
                itemSelectedFontWeight: this.itemSelectedFontWeight,
                itemSelectedBackgroundColor: this.itemSelectedBackgroundColor,
                itemIconSize: this.itemIconSize,
                itemIconFillColor: this.itemIconFillColor,
                itemSelectedIconFillColor: this.itemSelectedIconFillColor,
                itemSymbolFontSize: this.itemSymbolFontSize,
                itemSymbolFontColor: this.itemSymbolFontColor,
                itemSelectedSymbolFontColor: this.itemSelectedSymbolFontColor,
                itemBorderRadius: this.itemBorderRadius,
                itemMinHeight: this.itemMinHeight,
                itemPadding: this.itemPadding,
                itemShadow: this.itemShadow,
                buttonBackgroundColor: this.buttonBackgroundColor,
                buttonBackgroundBlurStyle: this.buttonBackgroundBlurStyle,
                buttonBackgroundBlurStyleOptions:
                  this.buttonBackgroundBlurStyleOptions,
                buttonBackgroundEffect: this.buttonBackgroundEffect,
                buttonBorderRadius: this.buttonBorderRadius,
                buttonMinHeight: this.buttonMinHeight,
                buttonPadding: this.buttonPadding,
                languageDirection: this.languageDirection,
              },
              undefined,
              elmtId,
              () => {},
              {
                page: 'advancedComponents/src/main/ets/components/SegmentButtonV2.ets',
                line: 405,
                t1: 5,
              }
            );
            ViewV2.create(componentCall);
            let paramsLambda = () => {
              return {
                theme: d1,
                items: this.items,
                selectedIndex: this.selectedIndex,
                $selectedIndex: (selectedIndex) => {
                  this.$selectedIndex?.(selectedIndex);
                },
                onItemClicked: this.onItemClicked,
                itemMinFontScale: this.itemMinFontScale,
                itemMaxFontScale: this.itemMaxFontScale,
                itemSpace: this.itemSpace,
                itemFontColor: this.itemFontColor,
                itemSelectedFontColor: this.itemSelectedFontColor,
                itemFontSize: this.itemFontSize,
                itemSelectedFontSize: this.itemSelectedFontSize,
                itemFontWeight: this.itemFontWeight,
                itemSelectedFontWeight: this.itemSelectedFontWeight,
                itemSelectedBackgroundColor: this.itemSelectedBackgroundColor,
                itemIconSize: this.itemIconSize,
                itemIconFillColor: this.itemIconFillColor,
                itemSelectedIconFillColor: this.itemSelectedIconFillColor,
                itemSymbolFontSize: this.itemSymbolFontSize,
                itemSymbolFontColor: this.itemSymbolFontColor,
                itemSelectedSymbolFontColor: this.itemSelectedSymbolFontColor,
                itemBorderRadius: this.itemBorderRadius,
                itemMinHeight: this.itemMinHeight,
                itemPadding: this.itemPadding,
                itemShadow: this.itemShadow,
                buttonBackgroundColor: this.buttonBackgroundColor,
                buttonBackgroundBlurStyle: this.buttonBackgroundBlurStyle,
                buttonBackgroundBlurStyleOptions:
                  this.buttonBackgroundBlurStyleOptions,
                buttonBackgroundEffect: this.buttonBackgroundEffect,
                buttonBorderRadius: this.buttonBorderRadius,
                buttonMinHeight: this.buttonMinHeight,
                buttonPadding: this.buttonPadding,
                languageDirection: this.languageDirection,
              };
            };
            componentCall.paramsGenerator_ = paramsLambda;
          } else {
            this.updateStateVarsOfChildByElmtId(elmtId, {
              theme: d1,
              items: this.items,
              selectedIndex: this.selectedIndex,
              itemMinFontScale: this.itemMinFontScale,
              itemMaxFontScale: this.itemMaxFontScale,
              itemSpace: this.itemSpace,
              itemFontColor: this.itemFontColor,
              itemSelectedFontColor: this.itemSelectedFontColor,
              itemFontSize: this.itemFontSize,
              itemSelectedFontSize: this.itemSelectedFontSize,
              itemFontWeight: this.itemFontWeight,
              itemSelectedFontWeight: this.itemSelectedFontWeight,
              itemSelectedBackgroundColor: this.itemSelectedBackgroundColor,
              itemIconSize: this.itemIconSize,
              itemIconFillColor: this.itemIconFillColor,
              itemSelectedIconFillColor: this.itemSelectedIconFillColor,
              itemSymbolFontSize: this.itemSymbolFontSize,
              itemSymbolFontColor: this.itemSymbolFontColor,
              itemSelectedSymbolFontColor: this.itemSelectedSymbolFontColor,
              itemBorderRadius: this.itemBorderRadius,
              itemMinHeight: this.itemMinHeight,
              itemPadding: this.itemPadding,
              itemShadow: this.itemShadow,
              buttonBackgroundColor: this.buttonBackgroundColor,
              buttonBackgroundBlurStyle: this.buttonBackgroundBlurStyle,
              buttonBackgroundBlurStyleOptions:
                this.buttonBackgroundBlurStyleOptions,
              buttonBackgroundEffect: this.buttonBackgroundEffect,
              buttonBorderRadius: this.buttonBorderRadius,
              buttonMinHeight: this.buttonMinHeight,
              buttonPadding: this.buttonPadding,
              languageDirection: this.languageDirection,
            });
          }
        },
        { name: 'SimpleSegmentButtonV2' }
      );
    }
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('items' in params) {
      this.updateParam('items', params.items);
    }
    if ('selectedIndex' in params) {
      this.updateParam('selectedIndex', params.selectedIndex);
    }
    if ('itemMinFontScale' in params) {
      this.updateParam('itemMinFontScale', params.itemMinFontScale);
    }
    if ('itemMaxFontScale' in params) {
      this.updateParam('itemMaxFontScale', params.itemMaxFontScale);
    }
    if ('itemSpace' in params) {
      this.updateParam('itemSpace', params.itemSpace);
    }
    if ('itemFontColor' in params) {
      this.updateParam('itemFontColor', params.itemFontColor);
    }
    if ('itemSelectedFontColor' in params) {
      this.updateParam('itemSelectedFontColor', params.itemSelectedFontColor);
    }
    if ('itemFontSize' in params) {
      this.updateParam('itemFontSize', params.itemFontSize);
    }
    if ('itemSelectedFontSize' in params) {
      this.updateParam('itemSelectedFontSize', params.itemSelectedFontSize);
    }
    if ('itemFontWeight' in params) {
      this.updateParam('itemFontWeight', params.itemFontWeight);
    }
    if ('itemSelectedFontWeight' in params) {
      this.updateParam('itemSelectedFontWeight', params.itemSelectedFontWeight);
    }
    if ('itemBorderRadius' in params) {
      this.updateParam('itemBorderRadius', params.itemBorderRadius);
    }
    if ('itemSelectedBackgroundColor' in params) {
      this.updateParam(
        'itemSelectedBackgroundColor',
        params.itemSelectedBackgroundColor
      );
    }
    if ('itemIconSize' in params) {
      this.updateParam('itemIconSize', params.itemIconSize);
    }
    if ('itemIconFillColor' in params) {
      this.updateParam('itemIconFillColor', params.itemIconFillColor);
    }
    if ('itemSelectedIconFillColor' in params) {
      this.updateParam(
        'itemSelectedIconFillColor',
        params.itemSelectedIconFillColor
      );
    }
    if ('itemSymbolFontSize' in params) {
      this.updateParam('itemSymbolFontSize', params.itemSymbolFontSize);
    }
    if ('itemSymbolFontColor' in params) {
      this.updateParam('itemSymbolFontColor', params.itemSymbolFontColor);
    }
    if ('itemSelectedSymbolFontColor' in params) {
      this.updateParam(
        'itemSelectedSymbolFontColor',
        params.itemSelectedSymbolFontColor
      );
    }
    if ('itemMinHeight' in params) {
      this.updateParam('itemMinHeight', params.itemMinHeight);
    }
    if ('itemPadding' in params) {
      this.updateParam('itemPadding', params.itemPadding);
    }
    if ('itemShadow' in params) {
      this.updateParam('itemShadow', params.itemShadow);
    }
    if ('buttonBackgroundColor' in params) {
      this.updateParam('buttonBackgroundColor', params.buttonBackgroundColor);
    }
    if ('buttonBackgroundBlurStyle' in params) {
      this.updateParam(
        'buttonBackgroundBlurStyle',
        params.buttonBackgroundBlurStyle
      );
    }
    if ('buttonBackgroundBlurStyleOptions' in params) {
      this.updateParam(
        'buttonBackgroundBlurStyleOptions',
        params.buttonBackgroundBlurStyleOptions
      );
    }
    if ('buttonBackgroundEffect' in params) {
      this.updateParam('buttonBackgroundEffect', params.buttonBackgroundEffect);
    }
    if ('buttonBorderRadius' in params) {
      this.updateParam('buttonBorderRadius', params.buttonBorderRadius);
    }
    if ('buttonMinHeight' in params) {
      this.updateParam('buttonMinHeight', params.buttonMinHeight);
    }
    if ('buttonPadding' in params) {
      this.updateParam('buttonPadding', params.buttonPadding);
    }
    if ('languageDirection' in params) {
      this.updateParam('languageDirection', params.languageDirection);
    }
  }
  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
o([Param], CapsuleSegmentButtonV2.prototype, 'items', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'selectedIndex', void 0);
o([Event], CapsuleSegmentButtonV2.prototype, '$selectedIndex', void 0);
o([Event], CapsuleSegmentButtonV2.prototype, 'onItemClicked', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemMinFontScale', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemMaxFontScale', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemSpace', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemFontColor', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemSelectedFontColor', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemFontSize', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemSelectedFontSize', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemFontWeight', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemSelectedFontWeight', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemBorderRadius', void 0);
o(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemSelectedBackgroundColor',
  void 0
);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemIconSize', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemIconFillColor', void 0);
o(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemSelectedIconFillColor',
  void 0
);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemSymbolFontSize', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemSymbolFontColor', void 0);
o(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemSelectedSymbolFontColor',
  void 0
);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemMinHeight', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemPadding', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'itemShadow', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'buttonBackgroundColor', void 0);
o(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'buttonBackgroundBlurStyle',
  void 0
);
o(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'buttonBackgroundBlurStyleOptions',
  void 0
);
o([Param], CapsuleSegmentButtonV2.prototype, 'buttonBackgroundEffect', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'buttonBorderRadius', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'buttonMinHeight', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'buttonPadding', void 0);
o([Param], CapsuleSegmentButtonV2.prototype, 'languageDirection', void 0);
class f1 extends ViewV2 {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda,
    extraInfo
  ) {
    super(parent, elmtId, extraInfo);
    this.ContentLayer = () => {
      const parent =
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.length
          ? PUV2ViewBase.contextStack[PUV2ViewBase.contextStack.length - 1]
          : null;
      this.observeComponentCreation2((elmtId, isInitialRender) => {
        Flex.create({
          alignItems: ItemAlign.Stretch,
          space: { main: this.getItemSpace() },
        });
        Flex.constraintSize({
          minWidth: '100%',
          minHeight: this.getButtonMinHeight(),
        });
        Flex.clip(false);
        Flex.direction(this.languageDirection);
        Flex.focusScopeId(this.focusGroupId, true);
        Flex.padding(this.getButtonPadding());
        Gesture.create(GesturePriority.High);
        PanGesture.create();
        PanGesture.onActionStart((event) => {
          const finger = event.fingerList.find(Boolean);
          if (!finger) {
            return;
          }
          const index = this.getIndexByPosition(finger.globalX, finger.globalY);
          if (!this.isItemEnabled(index)) {
            return;
          }
          if (event.axisHorizontal !== 0 || event.axisVertical !== 0) {
            this.isMouseWheelScroll = true;
            return;
          }
          if (index === this.normalizedSelectedIndex) {
            this.isDragging = true;
          }
          this.panStartGlobalX = finger.globalX;
          this.panStartIndex = index;
        });
        PanGesture.onActionUpdate((event) => {
          if (!this.isDragging) {
            return;
          }
          const finger = event.fingerList.find(Boolean);
          if (!finger) {
            return;
          }
          const index = this.getIndexByPosition(finger.globalX, finger.globalY);
          this.updateSelectedIndex(index);
        });
        PanGesture.onActionEnd((event) => {
          if (!this.isItemEnabled(this.panStartIndex)) {
            return;
          }
          if (this.isMouseWheelScroll) {
            const offset = event.offsetX !== 0 ? event.offsetX : event.offsetY;
            const m1 = offset < 0 ? 1 : -1;
            this.updateSelectedIndex(this.normalizedSelectedIndex + m1);
            this.isMouseWheelScroll = false;
            return;
          }
          if (this.isDragging) {
            this.isDragging = false;
            return;
          }
          if (!this.isItemEnabled(this.normalizedSelectedIndex)) {
            return;
          }
          const finger = event.fingerList.find(Boolean);
          if (!finger) {
            return;
          }
          let l1 = finger.globalX - this.panStartGlobalX < 0 ? -1 : 1;
          if (this.isRTL()) {
            l1 = -l1;
          }
          this.updateSelectedIndex(this.normalizedSelectedIndex + l1);
        });
        PanGesture.onActionCancel(() => {
          this.isDragging = false;
          this.isMouseWheelScroll = false;
          this.panStartIndex = -1;
        });
        PanGesture.pop();
        Gesture.pop();
      }, Flex);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
        Repeat(this.getItems(), this)
          .each((repeatItem) => {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
              Button.createWithChild({ type: ButtonType.Normal });
              Button.accessibilityGroup(true);
              Button.accessibilitySelected(this.isSelected(repeatItem));
              Button.accessibilityText(
                this.getItemAccessibilityText(repeatItem)
              );
              Button.accessibilityDescription(
                this.getItemAccessibilityDescription(repeatItem)
              );
              Button.accessibilityLevel(repeatItem.item.accessibilityLevel);
              Button.backgroundColor(Color.Transparent);
              Button.borderRadius(this.getItemBorderRadius());
              Button.direction(this.languageDirection);
              Button.enabled(repeatItem.item.enabled);
              Button.focusScopePriority(
                this.focusGroupId,
                this.getFocusPriority(repeatItem)
              );
              Button.hoverEffect(HoverEffect.None);
              Button.layoutWeight(1);
              Button.padding(0);
              Button.scale(this.getItemScale(repeatItem.index));
              Button.stateEffect(false);
              Button.onAreaChange((k1, area) => {
                this.itemRects[repeatItem.index] = {
                  size: {
                    width: area.width,
                    height: area.height,
                  },
                  position: {
                    x: area.position.x,
                    y: area.position.y,
                  },
                  globalPosition: {
                    x: area.globalPosition.x,
                    y: area.globalPosition.y,
                  },
                };
              });
              Gesture.create(GesturePriority.Low);
              TapGesture.create();
              TapGesture.onAction(() => {
                this.onItemClicked?.(repeatItem.index);
                this.updateSelectedIndex(repeatItem.index);
              });
              TapGesture.pop();
              Gesture.pop();
              Button.onTouch((event) => {
                if (event.type === TouchType.Down) {
                  if (this.isSelected(repeatItem)) {
                    this.updateItemScale(0.95);
                  }
                  this.updateTouchPressedItemIndex(repeatItem.index);
                } else if (
                  [TouchType.Up, TouchType.Cancel].includes(event.type)
                ) {
                  this.updateItemScale(1);
                  this.updateTouchPressedItemIndex(-1);
                }
              });
              Button.onHover((isHover) => {
                if (isHover) {
                  this.updateHoveredItemIndex(repeatItem.index);
                } else {
                  this.updateHoveredItemIndex(-1);
                }
              });
              Button.onMouse((event) => {
                if (event.action === MouseAction.Press) {
                  this.updateMousePressedItemIndex(repeatItem.index);
                } else if (
                  [MouseAction.Release, MouseAction.CANCEL].includes(
                    event.action
                  )
                ) {
                  this.updateMousePressedItemIndex(-1);
                }
              });
            }, Button);
            {
              this.observeComponentCreation2(
                (elmtId, isInitialRender) => {
                  if (isInitialRender) {
                    let componentCall = new h1(
                      parent ? parent : this,
                      {
                        theme: this.theme,
                        item: repeatItem.item,
                        selected: this.isSelected(repeatItem),
                        itemMinFontScale: this.itemMinFontScale,
                        itemMaxFontScale: this.itemMaxFontScale,
                        itemFontColor: this.itemFontColor,
                        itemSelectedFontColor: this.itemSelectedFontColor,
                        itemFontSize: this.itemFontSize,
                        itemSelectedFontSize: this.itemSelectedFontSize,
                        itemFontWeight: this.itemFontWeight,
                        itemSelectedFontWeight: this.itemSelectedFontWeight,
                        itemIconSize: this.itemIconSize,
                        itemIconFillColor: this.itemIconFillColor,
                        itemSelectedIconFillColor:
                          this.itemSelectedIconFillColor,
                        itemSymbolFontSize: this.itemSymbolFontSize,
                        itemSymbolFontColor: this.itemSymbolFontColor,
                        itemSelectedSymbolFontColor:
                          this.itemSelectedSymbolFontColor,
                        itemMinHeight: this.itemMinHeight,
                        itemPadding: this.itemPadding,
                        languageDirection: this.languageDirection,
                        hasHybrid: this.getItems().hasHybrid,
                      },
                      undefined,
                      elmtId,
                      () => {},
                      {
                        page: 'advancedComponents/src/main/ets/components/SegmentButtonV2.ets',
                        line: 577,
                        t1: 13,
                      }
                    );
                    ViewV2.create(componentCall);
                    let paramsLambda = () => {
                      return {
                        theme: this.theme,
                        item: repeatItem.item,
                        selected: this.isSelected(repeatItem),
                        itemMinFontScale: this.itemMinFontScale,
                        itemMaxFontScale: this.itemMaxFontScale,
                        itemFontColor: this.itemFontColor,
                        itemSelectedFontColor: this.itemSelectedFontColor,
                        itemFontSize: this.itemFontSize,
                        itemSelectedFontSize: this.itemSelectedFontSize,
                        itemFontWeight: this.itemFontWeight,
                        itemSelectedFontWeight: this.itemSelectedFontWeight,
                        itemIconSize: this.itemIconSize,
                        itemIconFillColor: this.itemIconFillColor,
                        itemSelectedIconFillColor:
                          this.itemSelectedIconFillColor,
                        itemSymbolFontSize: this.itemSymbolFontSize,
                        itemSymbolFontColor: this.itemSymbolFontColor,
                        itemSelectedSymbolFontColor:
                          this.itemSelectedSymbolFontColor,
                        itemMinHeight: this.itemMinHeight,
                        itemPadding: this.itemPadding,
                        languageDirection: this.languageDirection,
                        hasHybrid: this.getItems().hasHybrid,
                      };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                  } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {
                      theme: this.theme,
                      item: repeatItem.item,
                      selected: this.isSelected(repeatItem),
                      itemMinFontScale: this.itemMinFontScale,
                      itemMaxFontScale: this.itemMaxFontScale,
                      itemFontColor: this.itemFontColor,
                      itemSelectedFontColor: this.itemSelectedFontColor,
                      itemFontSize: this.itemFontSize,
                      itemSelectedFontSize: this.itemSelectedFontSize,
                      itemFontWeight: this.itemFontWeight,
                      itemSelectedFontWeight: this.itemSelectedFontWeight,
                      itemIconSize: this.itemIconSize,
                      itemIconFillColor: this.itemIconFillColor,
                      itemSelectedIconFillColor: this.itemSelectedIconFillColor,
                      itemSymbolFontSize: this.itemSymbolFontSize,
                      itemSymbolFontColor: this.itemSymbolFontColor,
                      itemSelectedSymbolFontColor:
                        this.itemSelectedSymbolFontColor,
                      itemMinHeight: this.itemMinHeight,
                      itemPadding: this.itemPadding,
                      languageDirection: this.languageDirection,
                      hasHybrid: this.getItems().hasHybrid,
                    });
                  }
                },
                { name: 'SegmentButtonV2ItemContent' }
              );
            }
            Button.pop();
          })
          .key(j(this.focusGroupId))
          .render(isInitialRender);
      }, Repeat);
      Flex.pop();
    };
    this.BackplateLayer = () => {
      const parent =
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.length
          ? PUV2ViewBase.contextStack[PUV2ViewBase.contextStack.length - 1]
          : null;
      this.observeComponentCreation2((elmtId, isInitialRender) => {
        If.create();
        if (this.selectedItemRect) {
          this.ifElseBranchUpdateFunction(0, () => {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
              Stack.create();
              Stack.position({
                x: this.selectedItemRect.position.x,
                y: this.selectedItemRect.position.y,
              });
              Stack.backgroundColor(this.getItemSelectedBackgroundColor());
              Stack.borderRadius(this.getItemBorderRadius());
              Stack.scale({ x: this.itemScale, y: this.itemScale });
              Stack.shadow(this.getItemBackplateShadow());
              Stack.height(this.selectedItemRect.size.height);
              Stack.width(this.selectedItemRect.size.width);
            }, Stack);
            Stack.pop();
          });
        } else {
          this.ifElseBranchUpdateFunction(1, () => {});
        }
      }, If);
      If.pop();
    };
    this.EffectLayer = () => {
      const parent =
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.length
          ? PUV2ViewBase.contextStack[PUV2ViewBase.contextStack.length - 1]
          : null;
      this.observeComponentCreation2((elmtId, isInitialRender) => {
        Repeat(this.getItemRects(), this)
          .each((repeatItem) => {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
              Stack.create();
              Stack.backgroundColor(this.getEffectBackgroundColor(repeatItem));
              Stack.borderRadius(this.getItemBorderRadius());
              Stack.height(repeatItem.item.size.height);
              Stack.position({
                x: repeatItem.item.position.x,
                y: repeatItem.item.position.y,
              });
              Stack.scale(this.getItemScale(repeatItem.index));
              Stack.width(repeatItem.item.size.width);
            }, Stack);
            Stack.pop();
          })
          .render(isInitialRender);
      }, Repeat);
    };
    this.initParam(
      'items',
      params && 'items' in params ? params.items : undefined
    );
    this.initParam(
      'selectedIndex',
      params && 'selectedIndex' in params ? params.selectedIndex : undefined
    );
    this.$selectedIndex =
      '$selectedIndex' in params ? params.$selectedIndex : () => {};
    this.initParam(
      'theme',
      params && 'theme' in params ? params.theme : undefined
    );
    this.onItemClicked =
      'onItemClicked' in params ? params.onItemClicked : () => {};
    this.initParam(
      'itemMinFontScale',
      params && 'itemMinFontScale' in params
        ? params.itemMinFontScale
        : undefined
    );
    this.initParam(
      'itemMaxFontScale',
      params && 'itemMaxFontScale' in params
        ? params.itemMaxFontScale
        : undefined
    );
    this.initParam(
      'itemSpace',
      params && 'itemSpace' in params ? params.itemSpace : undefined
    );
    this.initParam(
      'itemFontColor',
      params && 'itemFontColor' in params ? params.itemFontColor : undefined
    );
    this.initParam(
      'itemSelectedFontColor',
      params && 'itemSelectedFontColor' in params
        ? params.itemSelectedFontColor
        : undefined
    );
    this.initParam(
      'itemFontSize',
      params && 'itemFontSize' in params ? params.itemFontSize : undefined
    );
    this.initParam(
      'itemSelectedFontSize',
      params && 'itemSelectedFontSize' in params
        ? params.itemSelectedFontSize
        : undefined
    );
    this.initParam(
      'itemFontWeight',
      params && 'itemFontWeight' in params ? params.itemFontWeight : undefined
    );
    this.initParam(
      'itemSelectedFontWeight',
      params && 'itemSelectedFontWeight' in params
        ? params.itemSelectedFontWeight
        : undefined
    );
    this.initParam(
      'itemBorderRadius',
      params && 'itemBorderRadius' in params
        ? params.itemBorderRadius
        : undefined
    );
    this.initParam(
      'itemSelectedBackgroundColor',
      params && 'itemSelectedBackgroundColor' in params
        ? params.itemSelectedBackgroundColor
        : undefined
    );
    this.initParam(
      'itemIconSize',
      params && 'itemIconSize' in params ? params.itemIconSize : undefined
    );
    this.initParam(
      'itemIconFillColor',
      params && 'itemIconFillColor' in params
        ? params.itemIconFillColor
        : undefined
    );
    this.initParam(
      'itemSelectedIconFillColor',
      params && 'itemSelectedIconFillColor' in params
        ? params.itemSelectedIconFillColor
        : undefined
    );
    this.initParam(
      'itemSymbolFontSize',
      params && 'itemSymbolFontSize' in params
        ? params.itemSymbolFontSize
        : undefined
    );
    this.initParam(
      'itemSymbolFontColor',
      params && 'itemSymbolFontColor' in params
        ? params.itemSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemSelectedSymbolFontColor',
      params && 'itemSelectedSymbolFontColor' in params
        ? params.itemSelectedSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemMinHeight',
      params && 'itemMinHeight' in params ? params.itemMinHeight : undefined
    );
    this.initParam(
      'itemPadding',
      params && 'itemPadding' in params ? params.itemPadding : undefined
    );
    this.initParam(
      'itemShadow',
      params && 'itemShadow' in params ? params.itemShadow : undefined
    );
    this.initParam(
      'buttonBackgroundColor',
      params && 'buttonBackgroundColor' in params
        ? params.buttonBackgroundColor
        : undefined
    );
    this.initParam(
      'buttonBackgroundBlurStyle',
      params && 'buttonBackgroundBlurStyle' in params
        ? params.buttonBackgroundBlurStyle
        : undefined
    );
    this.initParam(
      'buttonBackgroundBlurStyleOptions',
      params && 'buttonBackgroundBlurStyleOptions' in params
        ? params.buttonBackgroundBlurStyleOptions
        : undefined
    );
    this.initParam(
      'buttonBackgroundEffect',
      params && 'buttonBackgroundEffect' in params
        ? params.buttonBackgroundEffect
        : undefined
    );
    this.initParam(
      'buttonBorderRadius',
      params && 'buttonBorderRadius' in params
        ? params.buttonBorderRadius
        : undefined
    );
    this.initParam(
      'buttonMinHeight',
      params && 'buttonMinHeight' in params ? params.buttonMinHeight : undefined
    );
    this.initParam(
      'buttonPadding',
      params && 'buttonPadding' in params ? params.buttonPadding : undefined
    );
    this.initParam(
      'languageDirection',
      params && 'languageDirection' in params
        ? params.languageDirection
        : undefined
    );
    this.itemRects = [];
    this.itemScale = 1;
    this.hoveredItemIndex = -1;
    this.mousePressedItemIndex = -1;
    this.touchPressedItemIndex = -1;
    this.isMouseWheelScroll = false;
    this.isDragging = false;
    this.panStartGlobalX = 0;
    this.panStartIndex = -1;
    this.focusGroupId = util.generateRandomUUID();
    this.finalizeConstruction();
  }
  get normalizedSelectedIndex() {
    const items = this.getItems();
    return normalize(this.selectedIndex, 0, items.length - 1);
  }
  get selectedItemRect() {
    return this.itemRects[this.normalizedSelectedIndex];
  }
  getFocusPriority(repeatItem) {
    return this.normalizedSelectedIndex === repeatItem.index
      ? FocusPriority.PREVIOUS
      : FocusPriority.AUTO;
  }
  isItemEnabled(index) {
    const items = this.getItems();
    if (index < 0 || index >= items.length) {
      return false;
    }
    return items[index].enabled;
  }
  getItemRects() {
    if (!this.items) {
      return [];
    }
    if (this.items.length === this.itemRects.length) {
      return this.itemRects;
    }
    return this.itemRects.slice(0, this.items.length);
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Stack.create();
      Stack.backgroundColor(this.getButtonBackgroundColor());
      Stack.backgroundEffect(this.buttonBackgroundEffect);
      Stack.borderRadius(this.getButtonBorderRadius());
      Stack.clip(false);
      Stack.constraintSize({
        minWidth: '100%',
        minHeight: this.getButtonMinHeight(),
      });
      Stack.direction(this.languageDirection);
    }, Stack);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Stack.create();
      Stack.borderRadius(this.getButtonBorderRadius());
      Stack.backgroundBlurStyle(
        this.getButtonBackgroundBlurStyle(),
        this.getButtonBackgroundBlurStyleOptions()
      );
      Stack.clip(false);
      Stack.direction(this.languageDirection);
    }, Stack);
    this.EffectLayer.bind(this)();
    this.BackplateLayer.bind(this)();
    this.ContentLayer.bind(this)();
    Stack.pop();
    Stack.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
  getItems() {
    return this.items ?? e1;
  }
  getItemBackplateShadow() {
    return this.itemShadow ?? this.theme.itemShadow;
  }
  getButtonBackgroundBlurStyle() {
    if (this.buttonBackgroundEffect) {
      return undefined;
    }
    return this.buttonBackgroundBlurStyle;
  }
  getButtonBackgroundBlurStyleOptions() {
    if (this.buttonBackgroundEffect) {
      return undefined;
    }
    return this.buttonBackgroundBlurStyleOptions;
  }
  getItemScale(index) {
    const pressed = this.isPressed(index);
    const scale = pressed ? 0.95 : 1;
    return { x: scale, y: scale };
  }
  isPressed(index) {
    return this.mousePressedItemIndex === index;
  }
  updateHoveredItemIndex(index) {
    if (index === this.hoveredItemIndex) {
      return;
    }
    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
      this.hoveredItemIndex = index;
    });
  }
  updateMousePressedItemIndex(index) {
    if (index === this.mousePressedItemIndex) {
      return;
    }
    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
      this.mousePressedItemIndex = index;
    });
  }
  updateTouchPressedItemIndex(index) {
    if (index === this.touchPressedItemIndex) {
      return;
    }
    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
      this.touchPressedItemIndex = index;
    });
  }
  isRTL() {
    if (this.languageDirection || this.languageDirection === Direction.Auto) {
      return i18n.isRTL(i18n.System.getSystemLanguage());
    }
    return this.languageDirection === Direction.Rtl;
  }
  getEffectBackgroundColor(repeatItem) {
    if (repeatItem.index === this.mousePressedItemIndex) {
      return {
        id: -1,
        type: 10001,
        params: ['sys.color.interactive_click'],
        bundleName: '__harDefaultBundleName__',
        moduleName: '__harDefaultModuleName__',
      };
    }
    if (repeatItem.index === this.hoveredItemIndex) {
      return {
        id: -1,
        type: 10001,
        params: ['sys.color.interactive_hover'],
        bundleName: '__harDefaultBundleName__',
        moduleName: '__harDefaultModuleName__',
      };
    }
    return Color.Transparent;
  }
  getItemBorderRadius() {
    if (this.itemBorderRadius && i1.getInstance().u1(this.itemBorderRadius)) {
      return i1.getInstance().stringify(this.itemBorderRadius);
    }
    return this.theme.itemBorderRadius;
  }
  getItemSelectedBackgroundColor() {
    if (this.itemSelectedBackgroundColor) {
      return this.itemSelectedBackgroundColor.color;
    }
    return this.theme.itemSelectedBackgroundColor;
  }
  getItemSpace() {
    if (
      this.itemSpace &&
      this.itemSpace.unit !== LengthUnit.PERCENT &&
      i1.getInstance().u1(this.itemSpace)
    ) {
      return this.itemSpace;
    }
    return this.theme.itemSpace;
  }
  getIndexByPosition(globalX, globalY) {
    let index = 0;
    while (index < this.itemRects.length) {
      const rect = this.itemRects[index];
      if (this.isPointOnRect(globalX, globalY, rect)) {
        return index;
      }
      ++index;
    }
    return -1;
  }
  isPointOnRect(globalX, globalY, rect) {
    return (
      globalX >= rect.globalPosition.x &&
      globalX <= rect.globalPosition.x + rect.size.width &&
      globalY >= rect.globalPosition.y &&
      globalY <= rect.globalPosition.y + rect.size.height
    );
  }
  updateSelectedIndex(selectedIndex) {
    if (
      !this.isItemEnabled(selectedIndex) ||
      selectedIndex === this.selectedIndex
    ) {
      return;
    }
    this.getUIContext().animateTo(
      { curve: curves.springMotion(0.347, 0.99) },
      () => {
        this.$selectedIndex?.(selectedIndex);
      }
    );
  }
  updateItemScale(scale) {
    if (this.itemScale === scale) {
      return;
    }
    this.getUIContext().animateTo(
      { curve: curves.interpolatingSpring(10, 1, 410, 38) },
      () => {
        this.itemScale = scale;
      }
    );
  }
  getItemAccessibilityDescription(repeatItem) {
    return repeatItem.item.accessibilityDescription;
  }
  getItemAccessibilityText(repeatItem) {
    return repeatItem.item.accessibilityText;
  }
  isSelected(repeatItem) {
    return repeatItem.index === this.normalizedSelectedIndex;
  }
  getButtonPadding() {
    if (this.buttonPadding && i1.getInstance().u1(this.buttonPadding)) {
      return i1.getInstance().stringify(this.buttonPadding);
    }
    return this.theme.buttonPadding;
  }
  getButtonBorderRadius() {
    if (
      this.buttonBorderRadius &&
      i1.getInstance().u1(this.buttonBorderRadius)
    ) {
      return i1.getInstance().stringify(this.buttonBorderRadius);
    }
    return this.theme.buttonBorderRadius;
  }
  getButtonBackgroundColor() {
    if (this.buttonBackgroundColor) {
      return this.buttonBackgroundColor.color;
    }
    return this.theme.buttonBackgroundColor;
  }
  getButtonMinHeight() {
    if (this.buttonMinHeight && i1.getInstance().u1(this.buttonMinHeight)) {
      return i1.getInstance().stringify(this.buttonMinHeight);
    }
    const items = this.getItems();
    return items.hasHybrid ? this.theme.l1 : this.theme.buttonMinHeight;
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('items' in params) {
      this.updateParam('items', params.items);
    }
    if ('selectedIndex' in params) {
      this.updateParam('selectedIndex', params.selectedIndex);
    }
    if ('theme' in params) {
      this.updateParam('theme', params.theme);
    }
    if ('itemMinFontScale' in params) {
      this.updateParam('itemMinFontScale', params.itemMinFontScale);
    }
    if ('itemMaxFontScale' in params) {
      this.updateParam('itemMaxFontScale', params.itemMaxFontScale);
    }
    if ('itemSpace' in params) {
      this.updateParam('itemSpace', params.itemSpace);
    }
    if ('itemFontColor' in params) {
      this.updateParam('itemFontColor', params.itemFontColor);
    }
    if ('itemSelectedFontColor' in params) {
      this.updateParam('itemSelectedFontColor', params.itemSelectedFontColor);
    }
    if ('itemFontSize' in params) {
      this.updateParam('itemFontSize', params.itemFontSize);
    }
    if ('itemSelectedFontSize' in params) {
      this.updateParam('itemSelectedFontSize', params.itemSelectedFontSize);
    }
    if ('itemFontWeight' in params) {
      this.updateParam('itemFontWeight', params.itemFontWeight);
    }
    if ('itemSelectedFontWeight' in params) {
      this.updateParam('itemSelectedFontWeight', params.itemSelectedFontWeight);
    }
    if ('itemBorderRadius' in params) {
      this.updateParam('itemBorderRadius', params.itemBorderRadius);
    }
    if ('itemSelectedBackgroundColor' in params) {
      this.updateParam(
        'itemSelectedBackgroundColor',
        params.itemSelectedBackgroundColor
      );
    }
    if ('itemIconSize' in params) {
      this.updateParam('itemIconSize', params.itemIconSize);
    }
    if ('itemIconFillColor' in params) {
      this.updateParam('itemIconFillColor', params.itemIconFillColor);
    }
    if ('itemSelectedIconFillColor' in params) {
      this.updateParam(
        'itemSelectedIconFillColor',
        params.itemSelectedIconFillColor
      );
    }
    if ('itemSymbolFontSize' in params) {
      this.updateParam('itemSymbolFontSize', params.itemSymbolFontSize);
    }
    if ('itemSymbolFontColor' in params) {
      this.updateParam('itemSymbolFontColor', params.itemSymbolFontColor);
    }
    if ('itemSelectedSymbolFontColor' in params) {
      this.updateParam(
        'itemSelectedSymbolFontColor',
        params.itemSelectedSymbolFontColor
      );
    }
    if ('itemMinHeight' in params) {
      this.updateParam('itemMinHeight', params.itemMinHeight);
    }
    if ('itemPadding' in params) {
      this.updateParam('itemPadding', params.itemPadding);
    }
    if ('itemShadow' in params) {
      this.updateParam('itemShadow', params.itemShadow);
    }
    if ('buttonBackgroundColor' in params) {
      this.updateParam('buttonBackgroundColor', params.buttonBackgroundColor);
    }
    if ('buttonBackgroundBlurStyle' in params) {
      this.updateParam(
        'buttonBackgroundBlurStyle',
        params.buttonBackgroundBlurStyle
      );
    }
    if ('buttonBackgroundBlurStyleOptions' in params) {
      this.updateParam(
        'buttonBackgroundBlurStyleOptions',
        params.buttonBackgroundBlurStyleOptions
      );
    }
    if ('buttonBackgroundEffect' in params) {
      this.updateParam('buttonBackgroundEffect', params.buttonBackgroundEffect);
    }
    if ('buttonBorderRadius' in params) {
      this.updateParam('buttonBorderRadius', params.buttonBorderRadius);
    }
    if ('buttonMinHeight' in params) {
      this.updateParam('buttonMinHeight', params.buttonMinHeight);
    }
    if ('buttonPadding' in params) {
      this.updateParam('buttonPadding', params.buttonPadding);
    }
    if ('languageDirection' in params) {
      this.updateParam('languageDirection', params.languageDirection);
    }
  }
  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
o([Param], f1.prototype, 'items', void 0);
o([Param], f1.prototype, 'selectedIndex', void 0);
o([Event], f1.prototype, '$selectedIndex', void 0);
o([Param], f1.prototype, 'theme', void 0);
o([Event], f1.prototype, 'onItemClicked', void 0);
o([Param], f1.prototype, 'itemMinFontScale', void 0);
o([Param], f1.prototype, 'itemMaxFontScale', void 0);
o([Param], f1.prototype, 'itemSpace', void 0);
o([Param], f1.prototype, 'itemFontColor', void 0);
o([Param], f1.prototype, 'itemSelectedFontColor', void 0);
o([Param], f1.prototype, 'itemFontSize', void 0);
o([Param], f1.prototype, 'itemSelectedFontSize', void 0);
o([Param], f1.prototype, 'itemFontWeight', void 0);
o([Param], f1.prototype, 'itemSelectedFontWeight', void 0);
o([Param], f1.prototype, 'itemBorderRadius', void 0);
o([Param], f1.prototype, 'itemSelectedBackgroundColor', void 0);
o([Param], f1.prototype, 'itemIconSize', void 0);
o([Param], f1.prototype, 'itemIconFillColor', void 0);
o([Param], f1.prototype, 'itemSelectedIconFillColor', void 0);
o([Param], f1.prototype, 'itemSymbolFontSize', void 0);
o([Param], f1.prototype, 'itemSymbolFontColor', void 0);
o([Param], f1.prototype, 'itemSelectedSymbolFontColor', void 0);
o([Param], f1.prototype, 'itemMinHeight', void 0);
o([Param], f1.prototype, 'itemPadding', void 0);
o([Param], f1.prototype, 'itemShadow', void 0);
o([Param], f1.prototype, 'buttonBackgroundColor', void 0);
o([Param], f1.prototype, 'buttonBackgroundBlurStyle', void 0);
o([Param], f1.prototype, 'buttonBackgroundBlurStyleOptions', void 0);
o([Param], f1.prototype, 'buttonBackgroundEffect', void 0);
o([Param], f1.prototype, 'buttonBorderRadius', void 0);
o([Param], f1.prototype, 'buttonMinHeight', void 0);
o([Param], f1.prototype, 'buttonPadding', void 0);
o([Param], f1.prototype, 'languageDirection', void 0);
o([Local], f1.prototype, 'itemRects', void 0);
o([Local], f1.prototype, 'itemScale', void 0);
o([Local], f1.prototype, 'hoveredItemIndex', void 0);
o([Local], f1.prototype, 'mousePressedItemIndex', void 0);
o([Local], f1.prototype, 'touchPressedItemIndex', void 0);
o([Computed], f1.prototype, 'normalizedSelectedIndex', null);
o([Computed], f1.prototype, 'selectedItemRect', null);
const g1 = {
  itemBorderRadius: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_multi_corner_radius'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemBackgroundColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.segment_button_v2_multi_capsule_button_background'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSelectedBackgroundColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.comp_background_emphasize'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSpace: LengthMetrics.vp(1),
  itemFontColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_secondary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSelectedFontColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_on_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemFontWeight: FontWeight.Medium,
  itemSelectedFontWeight: FontWeight.Medium,
  itemIconFillColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.icon_secondary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSelectedIconFillColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_on_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSymbolFontColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_secondary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemSelectedSymbolFontColor: {
    id: -1,
    type: 10001,
    params: ['sys.color.font_on_primary'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemFontSize: {
    id: -1,
    type: 10002,
    params: ['sys.float.ohos_id_text_size_button2'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemIconSize: 24,
  itemSymbolFontSize: 20,
  itemPadding: {
    top: LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.padding_level2'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }),
    bottom: LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.padding_level2'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }),
    start: LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.padding_level4'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }),
    end: LengthMetrics.resource({
      id: -1,
      type: 10002,
      params: ['sys.float.padding_level4'],
      bundleName: '__harDefaultBundleName__',
      moduleName: '__harDefaultModuleName__',
    }),
  },
  itemMinHeight: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_multi_singleline_height'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  m1: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_multi_doubleline_height'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemMaxFontScale: t,
  n1: t,
  o1: u,
  itemMinFontScale: a1,
  q1: a1,
  s1: b1,
};
export class MultiCapsuleSegmentButtonV2 extends ViewV2 {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda,
    extraInfo
  ) {
    super(parent, elmtId, extraInfo);
    this.initParam(
      'items',
      params && 'items' in params ? params.items : undefined
    );
    this.initParam(
      'selectedIndexes',
      params && 'selectedIndexes' in params ? params.selectedIndexes : undefined
    );
    this.$selectedIndexes =
      '$selectedIndexes' in params ? params.$selectedIndexes : () => {};
    this.onItemClicked =
      'onItemClicked' in params ? params.onItemClicked : () => {};
    this.initParam(
      'itemMinFontScale',
      params && 'itemMinFontScale' in params
        ? params.itemMinFontScale
        : undefined
    );
    this.initParam(
      'itemMaxFontScale',
      params && 'itemMaxFontScale' in params
        ? params.itemMaxFontScale
        : undefined
    );
    this.initParam(
      'itemSpace',
      params && 'itemSpace' in params ? params.itemSpace : undefined
    );
    this.initParam(
      'itemFontColor',
      params && 'itemFontColor' in params ? params.itemFontColor : undefined
    );
    this.initParam(
      'itemSelectedFontColor',
      params && 'itemSelectedFontColor' in params
        ? params.itemSelectedFontColor
        : undefined
    );
    this.initParam(
      'itemFontSize',
      params && 'itemFontSize' in params ? params.itemFontSize : undefined
    );
    this.initParam(
      'itemSelectedFontSize',
      params && 'itemSelectedFontSize' in params
        ? params.itemSelectedFontSize
        : undefined
    );
    this.initParam(
      'itemFontWeight',
      params && 'itemFontWeight' in params ? params.itemFontWeight : undefined
    );
    this.initParam(
      'itemSelectedFontWeight',
      params && 'itemSelectedFontWeight' in params
        ? params.itemSelectedFontWeight
        : undefined
    );
    this.initParam(
      'itemBorderRadius',
      params && 'itemBorderRadius' in params
        ? params.itemBorderRadius
        : undefined
    );
    this.initParam(
      'itemBackgroundColor',
      params && 'itemBackgroundColor' in params
        ? params.itemBackgroundColor
        : undefined
    );
    this.initParam(
      'itemBackgroundEffect',
      params && 'itemBackgroundEffect' in params
        ? params.itemBackgroundEffect
        : undefined
    );
    this.initParam(
      'itemBackgroundBlurStyle',
      params && 'itemBackgroundBlurStyle' in params
        ? params.itemBackgroundBlurStyle
        : undefined
    );
    this.initParam(
      'itemBackgroundBlurStyleOptions',
      params && 'itemBackgroundBlurStyleOptions' in params
        ? params.itemBackgroundBlurStyleOptions
        : undefined
    );
    this.initParam(
      'itemSelectedBackgroundColor',
      params && 'itemSelectedBackgroundColor' in params
        ? params.itemSelectedBackgroundColor
        : undefined
    );
    this.initParam(
      'itemIconSize',
      params && 'itemIconSize' in params ? params.itemIconSize : undefined
    );
    this.initParam(
      'itemIconFillColor',
      params && 'itemIconFillColor' in params
        ? params.itemIconFillColor
        : undefined
    );
    this.initParam(
      'itemSelectedIconFillColor',
      params && 'itemSelectedIconFillColor' in params
        ? params.itemSelectedIconFillColor
        : undefined
    );
    this.initParam(
      'itemSymbolFontSize',
      params && 'itemSymbolFontSize' in params
        ? params.itemSymbolFontSize
        : undefined
    );
    this.initParam(
      'itemSymbolFontColor',
      params && 'itemSymbolFontColor' in params
        ? params.itemSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemSelectedSymbolFontColor',
      params && 'itemSelectedSymbolFontColor' in params
        ? params.itemSelectedSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemMinHeight',
      params && 'itemMinHeight' in params ? params.itemMinHeight : undefined
    );
    this.initParam(
      'itemPadding',
      params && 'itemPadding' in params ? params.itemPadding : undefined
    );
    this.initParam(
      'languageDirection',
      params && 'languageDirection' in params
        ? params.languageDirection
        : undefined
    );
    this.theme = g1;
    this.focusGroupId = util.generateRandomUUID();
    this.finalizeConstruction();
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Flex.create({
        alignItems: ItemAlign.Stretch,
        space: { main: this.getItemSpace() },
      });
      Flex.clip(false);
      Flex.direction(this.languageDirection);
      Flex.focusScopeId(this.focusGroupId, true);
    }, Flex);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Repeat(this.getItems(), this)
        .each((repeatItem) => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.accessibilityGroup(true);
            Button.accessibilityChecked(this.isSelected(repeatItem));
            Button.accessibilityText(this.getItemAccessibilityText(repeatItem));
            Button.accessibilityDescription(
              this.getItemAccessibilityDescription(repeatItem)
            );
            Button.accessibilityLevel(repeatItem.item.accessibilityLevel);
            Button.backgroundColor(this.getItemBackgroundColor(repeatItem));
            Button.backgroundEffect(this.itemBackgroundEffect);
            Button.borderRadius(this.getItemButtonBorderRadius(repeatItem));
            Button.constraintSize({ minHeight: this.getItemMinHeight() });
            Button.direction(this.languageDirection);
            Button.enabled(repeatItem.item.enabled);
            Button.focusScopePriority(
              this.focusGroupId,
              this.getFocusPriority(repeatItem)
            );
            Button.layoutWeight(1);
            Button.padding(0);
            Button.onClick(() => {
              this.onItemClicked?.(repeatItem.index);
              let selection;
              const items = this.getItems();
              const selectedIndexes = this.selectedIndexes ?? [];
              if (this.isSelected(repeatItem)) {
                selection = selectedIndexes.filter((index) => {
                  if (index < 0 || index > items.length - 1) {
                    return false;
                  }
                  return index !== repeatItem.index;
                });
              } else {
                selection = selectedIndexes
                  .filter((index) => index >= 0 && index <= items.length - 1)
                  .concat(repeatItem.index);
              }
              this.$selectedIndexes(selection);
            });
          }, Button);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            __Common__.borderRadius(this.getItemButtonBorderRadius(repeatItem));
            __Common__.backgroundBlurStyle(
              this.getItemBackgroundBlurStyle(),
              this.getItemBackgroundBlurStyleOptions()
            );
            __Common__.direction(this.languageDirection);
          }, __Common__);
          {
            this.observeComponentCreation2(
              (elmtId, isInitialRender) => {
                if (isInitialRender) {
                  let componentCall = new h1(
                    this,
                    {
                      theme: this.theme,
                      item: repeatItem.item,
                      selected: this.isSelected(repeatItem),
                      hasHybrid: this.getItems().hasHybrid,
                      itemMinFontScale: this.itemMinFontScale,
                      itemMaxFontScale: this.itemMaxFontScale,
                      itemFontColor: this.itemFontColor,
                      itemSelectedFontColor: this.itemSelectedFontColor,
                      itemFontSize: this.itemFontSize,
                      itemSelectedFontSize: this.itemSelectedFontSize,
                      itemFontWeight: this.itemFontWeight,
                      itemSelectedFontWeight: this.itemSelectedFontWeight,
                      itemIconSize: this.itemIconSize,
                      itemIconFillColor: this.itemIconFillColor,
                      itemSelectedIconFillColor: this.itemSelectedIconFillColor,
                      itemSymbolFontSize: this.itemSymbolFontSize,
                      itemSymbolFontColor: this.itemSymbolFontColor,
                      itemSelectedSymbolFontColor:
                        this.itemSelectedSymbolFontColor,
                      itemMinHeight: this.itemMinHeight,
                      itemPadding: this.itemPadding,
                      languageDirection: this.languageDirection,
                    },
                    undefined,
                    elmtId,
                    () => {},
                    {
                      page: 'advancedComponents/src/main/ets/components/SegmentButtonV2.ets',
                      line: 1108,
                      t1: 13,
                    }
                  );
                  ViewV2.create(componentCall);
                  let paramsLambda = () => {
                    return {
                      theme: this.theme,
                      item: repeatItem.item,
                      selected: this.isSelected(repeatItem),
                      hasHybrid: this.getItems().hasHybrid,
                      itemMinFontScale: this.itemMinFontScale,
                      itemMaxFontScale: this.itemMaxFontScale,
                      itemFontColor: this.itemFontColor,
                      itemSelectedFontColor: this.itemSelectedFontColor,
                      itemFontSize: this.itemFontSize,
                      itemSelectedFontSize: this.itemSelectedFontSize,
                      itemFontWeight: this.itemFontWeight,
                      itemSelectedFontWeight: this.itemSelectedFontWeight,
                      itemIconSize: this.itemIconSize,
                      itemIconFillColor: this.itemIconFillColor,
                      itemSelectedIconFillColor: this.itemSelectedIconFillColor,
                      itemSymbolFontSize: this.itemSymbolFontSize,
                      itemSymbolFontColor: this.itemSymbolFontColor,
                      itemSelectedSymbolFontColor:
                        this.itemSelectedSymbolFontColor,
                      itemMinHeight: this.itemMinHeight,
                      itemPadding: this.itemPadding,
                      languageDirection: this.languageDirection,
                    };
                  };
                  componentCall.paramsGenerator_ = paramsLambda;
                } else {
                  this.updateStateVarsOfChildByElmtId(elmtId, {
                    theme: this.theme,
                    item: repeatItem.item,
                    selected: this.isSelected(repeatItem),
                    hasHybrid: this.getItems().hasHybrid,
                    itemMinFontScale: this.itemMinFontScale,
                    itemMaxFontScale: this.itemMaxFontScale,
                    itemFontColor: this.itemFontColor,
                    itemSelectedFontColor: this.itemSelectedFontColor,
                    itemFontSize: this.itemFontSize,
                    itemSelectedFontSize: this.itemSelectedFontSize,
                    itemFontWeight: this.itemFontWeight,
                    itemSelectedFontWeight: this.itemSelectedFontWeight,
                    itemIconSize: this.itemIconSize,
                    itemIconFillColor: this.itemIconFillColor,
                    itemSelectedIconFillColor: this.itemSelectedIconFillColor,
                    itemSymbolFontSize: this.itemSymbolFontSize,
                    itemSymbolFontColor: this.itemSymbolFontColor,
                    itemSelectedSymbolFontColor:
                      this.itemSelectedSymbolFontColor,
                    itemMinHeight: this.itemMinHeight,
                    itemPadding: this.itemPadding,
                    languageDirection: this.languageDirection,
                  });
                }
              },
              { name: 'SegmentButtonV2ItemContent' }
            );
          }
          __Common__.pop();
          Button.pop();
        })
        .key(j(this.focusGroupId))
        .render(isInitialRender);
    }, Repeat);
    Flex.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
  getFocusPriority(repeatItem) {
    return Math.min(...this.selectedIndexes) === repeatItem.index
      ? FocusPriority.PREVIOUS
      : FocusPriority.AUTO;
  }
  getItems() {
    return this.items ?? e1;
  }
  getItemBackgroundBlurStyleOptions() {
    if (this.itemBackgroundEffect) {
      return undefined;
    }
    return this.itemBackgroundBlurStyleOptions;
  }
  getItemBackgroundBlurStyle() {
    if (this.itemBackgroundEffect) {
      return undefined;
    }
    return this.itemBackgroundBlurStyle;
  }
  getItemAccessibilityDescription(repeatItem) {
    return repeatItem.item.accessibilityDescription;
  }
  getItemAccessibilityText(repeatItem) {
    return repeatItem.item.accessibilityText;
  }
  getItemSpace() {
    if (
      this.itemSpace &&
      this.itemSpace.unit !== LengthUnit.PERCENT &&
      i1.getInstance().u1(this.itemSpace)
    ) {
      return this.itemSpace;
    }
    return this.theme.itemSpace;
  }
  getItemMinHeight() {
    if (this.itemMinHeight && i1.getInstance().u1(this.itemMinHeight)) {
      return i1.getInstance().stringify(this.itemMinHeight);
    }
    return this.theme.itemMinHeight;
  }
  getItemBackgroundColor(repeatItem) {
    if (this.isSelected(repeatItem)) {
      return (
        this.itemSelectedBackgroundColor?.color ??
        this.theme.itemSelectedBackgroundColor
      );
    }
    return this.itemBackgroundColor?.color ?? this.theme.itemBackgroundColor;
  }
  isSelected(repeatItem) {
    const selectedIndexes = this.selectedIndexes ?? [];
    return selectedIndexes.includes(repeatItem.index);
  }
  getItemButtonBorderRadius(repeatItem) {
    const items = this.getItems();
    const j1 = LengthMetrics.vp(0);
    const borderRadiuses = {
      topStart: j1,
      bottomStart: j1,
      topEnd: j1,
      bottomEnd: j1,
    };
    if (repeatItem.index === 0) {
      const borderRadius =
        this.itemBorderRadius ??
        LengthMetrics.resource(this.theme.itemBorderRadius);
      borderRadiuses.topStart = borderRadius;
      borderRadiuses.bottomStart = borderRadius;
    }
    if (repeatItem.index === items.length - 1) {
      const borderRadius =
        this.itemBorderRadius ??
        LengthMetrics.resource(this.theme.itemBorderRadius);
      borderRadiuses.topEnd = borderRadius;
      borderRadiuses.bottomEnd = borderRadius;
    }
    return borderRadiuses;
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('items' in params) {
      this.updateParam('items', params.items);
    }
    if ('selectedIndexes' in params) {
      this.updateParam('selectedIndexes', params.selectedIndexes);
    }
    if ('itemMinFontScale' in params) {
      this.updateParam('itemMinFontScale', params.itemMinFontScale);
    }
    if ('itemMaxFontScale' in params) {
      this.updateParam('itemMaxFontScale', params.itemMaxFontScale);
    }
    if ('itemSpace' in params) {
      this.updateParam('itemSpace', params.itemSpace);
    }
    if ('itemFontColor' in params) {
      this.updateParam('itemFontColor', params.itemFontColor);
    }
    if ('itemSelectedFontColor' in params) {
      this.updateParam('itemSelectedFontColor', params.itemSelectedFontColor);
    }
    if ('itemFontSize' in params) {
      this.updateParam('itemFontSize', params.itemFontSize);
    }
    if ('itemSelectedFontSize' in params) {
      this.updateParam('itemSelectedFontSize', params.itemSelectedFontSize);
    }
    if ('itemFontWeight' in params) {
      this.updateParam('itemFontWeight', params.itemFontWeight);
    }
    if ('itemSelectedFontWeight' in params) {
      this.updateParam('itemSelectedFontWeight', params.itemSelectedFontWeight);
    }
    if ('itemBorderRadius' in params) {
      this.updateParam('itemBorderRadius', params.itemBorderRadius);
    }
    if ('itemBackgroundColor' in params) {
      this.updateParam('itemBackgroundColor', params.itemBackgroundColor);
    }
    if ('itemBackgroundEffect' in params) {
      this.updateParam('itemBackgroundEffect', params.itemBackgroundEffect);
    }
    if ('itemBackgroundBlurStyle' in params) {
      this.updateParam(
        'itemBackgroundBlurStyle',
        params.itemBackgroundBlurStyle
      );
    }
    if ('itemBackgroundBlurStyleOptions' in params) {
      this.updateParam(
        'itemBackgroundBlurStyleOptions',
        params.itemBackgroundBlurStyleOptions
      );
    }
    if ('itemSelectedBackgroundColor' in params) {
      this.updateParam(
        'itemSelectedBackgroundColor',
        params.itemSelectedBackgroundColor
      );
    }
    if ('itemIconSize' in params) {
      this.updateParam('itemIconSize', params.itemIconSize);
    }
    if ('itemIconFillColor' in params) {
      this.updateParam('itemIconFillColor', params.itemIconFillColor);
    }
    if ('itemSelectedIconFillColor' in params) {
      this.updateParam(
        'itemSelectedIconFillColor',
        params.itemSelectedIconFillColor
      );
    }
    if ('itemSymbolFontSize' in params) {
      this.updateParam('itemSymbolFontSize', params.itemSymbolFontSize);
    }
    if ('itemSymbolFontColor' in params) {
      this.updateParam('itemSymbolFontColor', params.itemSymbolFontColor);
    }
    if ('itemSelectedSymbolFontColor' in params) {
      this.updateParam(
        'itemSelectedSymbolFontColor',
        params.itemSelectedSymbolFontColor
      );
    }
    if ('itemMinHeight' in params) {
      this.updateParam('itemMinHeight', params.itemMinHeight);
    }
    if ('itemPadding' in params) {
      this.updateParam('itemPadding', params.itemPadding);
    }
    if ('languageDirection' in params) {
      this.updateParam('languageDirection', params.languageDirection);
    }
  }
  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'items', void 0);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'selectedIndexes', void 0);
o([Event], MultiCapsuleSegmentButtonV2.prototype, '$selectedIndexes', void 0);
o([Event], MultiCapsuleSegmentButtonV2.prototype, 'onItemClicked', void 0);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'itemMinFontScale', void 0);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'itemMaxFontScale', void 0);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'itemSpace', void 0);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'itemFontColor', void 0);
o(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSelectedFontColor',
  void 0
);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'itemFontSize', void 0);
o(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSelectedFontSize',
  void 0
);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'itemFontWeight', void 0);
o(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSelectedFontWeight',
  void 0
);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'itemBorderRadius', void 0);
o(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemBackgroundColor',
  void 0
);
o(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemBackgroundEffect',
  void 0
);
o(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemBackgroundBlurStyle',
  void 0
);
o(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemBackgroundBlurStyleOptions',
  void 0
);
o(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSelectedBackgroundColor',
  void 0
);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'itemIconSize', void 0);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'itemIconFillColor', void 0);
o(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSelectedIconFillColor',
  void 0
);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'itemSymbolFontSize', void 0);
o(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSymbolFontColor',
  void 0
);
o(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSelectedSymbolFontColor',
  void 0
);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'itemMinHeight', void 0);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'itemPadding', void 0);
o([Param], MultiCapsuleSegmentButtonV2.prototype, 'languageDirection', void 0);
class h1 extends ViewV2 {
  constructor(
    parent,
    params,
    __localStorage,
    elmtId = -1,
    paramsLambda,
    extraInfo
  ) {
    super(parent, elmtId, extraInfo);
    this.initParam(
      'hasHybrid',
      params && 'hasHybrid' in params ? params.hasHybrid : undefined
    );
    this.initParam(
      'item',
      params && 'item' in params ? params.item : undefined
    );
    this.initParam(
      'selected',
      params && 'selected' in params ? params.selected : undefined
    );
    this.initParam(
      'theme',
      params && 'theme' in params ? params.theme : undefined
    );
    this.initParam(
      'itemMinFontScale',
      params && 'itemMinFontScale' in params
        ? params.itemMinFontScale
        : undefined
    );
    this.initParam(
      'itemMaxFontScale',
      params && 'itemMaxFontScale' in params
        ? params.itemMaxFontScale
        : undefined
    );
    this.initParam(
      'itemFontColor',
      params && 'itemFontColor' in params ? params.itemFontColor : undefined
    );
    this.initParam(
      'itemSelectedFontColor',
      params && 'itemSelectedFontColor' in params
        ? params.itemSelectedFontColor
        : undefined
    );
    this.initParam(
      'itemFontSize',
      params && 'itemFontSize' in params ? params.itemFontSize : undefined
    );
    this.initParam(
      'itemSelectedFontSize',
      params && 'itemSelectedFontSize' in params
        ? params.itemSelectedFontSize
        : undefined
    );
    this.initParam(
      'itemFontWeight',
      params && 'itemFontWeight' in params ? params.itemFontWeight : undefined
    );
    this.initParam(
      'itemSelectedFontWeight',
      params && 'itemSelectedFontWeight' in params
        ? params.itemSelectedFontWeight
        : undefined
    );
    this.initParam(
      'itemIconSize',
      params && 'itemIconSize' in params ? params.itemIconSize : undefined
    );
    this.initParam(
      'itemIconFillColor',
      params && 'itemIconFillColor' in params
        ? params.itemIconFillColor
        : undefined
    );
    this.initParam(
      'itemSelectedIconFillColor',
      params && 'itemSelectedIconFillColor' in params
        ? params.itemSelectedIconFillColor
        : undefined
    );
    this.initParam(
      'itemSymbolFontSize',
      params && 'itemSymbolFontSize' in params
        ? params.itemSymbolFontSize
        : undefined
    );
    this.initParam(
      'itemSymbolFontColor',
      params && 'itemSymbolFontColor' in params
        ? params.itemSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemSelectedSymbolFontColor',
      params && 'itemSelectedSymbolFontColor' in params
        ? params.itemSelectedSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemMinHeight',
      params && 'itemMinHeight' in params ? params.itemMinHeight : undefined
    );
    this.initParam(
      'itemPadding',
      params && 'itemPadding' in params ? params.itemPadding : undefined
    );
    this.initParam(
      'languageDirection',
      params && 'languageDirection' in params
        ? params.languageDirection
        : undefined
    );
    this.finalizeConstruction();
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create({ space: 2 });
      Column.constraintSize({
        minHeight: this.getItemMinHeight(),
        minWidth: '100%',
      });
      Column.direction(this.languageDirection);
      Column.justifyContent(FlexAlign.Center);
      Column.padding(this.getItemPadding());
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.item.symbol || this.item.symbolModifier) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create(this.item.symbol);
            SymbolGlyph.fontSize(this.getSymbolFontSize());
            SymbolGlyph.fontColor([this.getItemSymbolFillColor()]);
            SymbolGlyph.direction(this.languageDirection);
            SymbolGlyph.attributeModifier.bind(this)(this.item.symbolModifier);
          }, SymbolGlyph);
        });
      } else if (this.item.icon) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.item.icon);
            Image.fillColor(this.getItemIconFillColor());
            Image.width(this.getItemIconWidth());
            Image.height(this.getItemIconHeight());
            Image.direction(this.languageDirection);
            Image.draggable(false);
            Image.attributeModifier.bind(this)(this.item.iconModifier);
          }, Image);
        });
      } else {
        this.ifElseBranchUpdateFunction(2, () => {});
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.item.text) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.item.text);
            Text.direction(this.languageDirection);
            Text.fontSize(this.getItemFontSize());
            Text.fontColor(this.getItemFontColor());
            Text.fontWeight(this.getItemFontWeight());
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(1);
            Text.maxFontScale(this.getItemMaxFontScale());
            Text.minFontScale(this.getItemMinFontScale());
            Text.attributeModifier.bind(this)(this.item.textModifier);
          }, Text);
          Text.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
      }
    }, If);
    If.pop();
    Column.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
  getItemFontWeight() {
    if (this.selected) {
      return this.itemSelectedFontWeight ?? this.theme.itemSelectedFontWeight;
    }
    return this.itemFontWeight ?? this.theme.itemFontWeight;
  }
  getItemSymbolFillColor() {
    if (this.selected) {
      return (
        this.itemSelectedSymbolFontColor?.color ??
        this.theme.itemSelectedSymbolFontColor
      );
    }
    return this.itemSymbolFontColor?.color ?? this.theme.itemSymbolFontColor;
  }
  getSymbolFontSize() {
    if (
      this.itemSymbolFontSize &&
      i1.getInstance().u1(this.itemSymbolFontSize)
    ) {
      return i1.getInstance().stringify(this.itemSymbolFontSize);
    }
    return this.theme.itemSymbolFontSize;
  }
  getItemMaxFontScale() {
    if (typeof this.itemMaxFontScale === 'number') {
      return normalize(this.itemMaxFontScale, this.theme.n1, this.theme.o1);
    }
    if (typeof this.itemMaxFontScale === 'object') {
      const itemMaxFontScale =
        i(this.getUIContext(), this.itemMaxFontScale) ?? t;
      return normalize(itemMaxFontScale, this.theme.n1, this.theme.o1);
    }
    return t;
  }
  getItemMinFontScale() {
    if (typeof this.itemMinFontScale === 'number') {
      return normalize(this.itemMinFontScale, this.theme.q1, this.theme.s1);
    }
    if (typeof this.itemMinFontScale === 'object') {
      const itemMinFontScale =
        i(this.getUIContext(), this.itemMinFontScale) ?? a1;
      return normalize(itemMinFontScale, this.theme.q1, this.theme.s1);
    }
    return a1;
  }
  getItemPadding() {
    const itemPadding = {
      top: this.theme.itemPadding.top,
      bottom: this.theme.itemPadding.bottom,
      start: this.theme.itemPadding.start,
      end: this.theme.itemPadding.end,
    };
    if (this.itemPadding?.top && i1.getInstance().u1(this.itemPadding.top)) {
      itemPadding.top = this.itemPadding.top;
    }
    if (
      this.itemPadding?.bottom &&
      i1.getInstance().u1(this.itemPadding.bottom)
    ) {
      itemPadding.bottom = this.itemPadding.bottom;
    }
    if (
      this.itemPadding?.start &&
      i1.getInstance().u1(this.itemPadding.start)
    ) {
      itemPadding.start = this.itemPadding.start;
    }
    if (this.itemPadding?.end && i1.getInstance().u1(this.itemPadding.end)) {
      itemPadding.end = this.itemPadding.end;
    }
    return itemPadding;
  }
  getItemMinHeight() {
    if (this.itemMinHeight && i1.getInstance().u1(this.itemMinHeight)) {
      return i1.getInstance().stringify(this.itemMinHeight);
    }
    return this.hasHybrid ? this.theme.m1 : this.theme.itemMinHeight;
  }
  getItemFontColor() {
    if (this.selected) {
      if (this.itemSelectedFontColor) {
        return this.itemSelectedFontColor.color;
      }
      return this.theme.itemSelectedFontColor;
    }
    if (this.itemFontColor) {
      return this.itemFontColor.color;
    }
    return this.theme.itemFontColor;
  }
  getItemFontSize() {
    if (this.selected) {
      if (
        this.itemSelectedFontSize &&
        i1.getInstance().u1(this.itemSelectedFontSize)
      ) {
        return i1.getInstance().stringify(this.itemSelectedFontSize);
      }
      return this.theme.itemFontSize;
    }
    if (this.itemFontSize && i1.getInstance().u1(this.itemFontSize)) {
      return i1.getInstance().stringify(this.itemFontSize);
    }
    return this.theme.itemFontSize;
  }
  getItemIconHeight() {
    if (
      this.itemIconSize?.height &&
      i1.getInstance().u1(this.itemIconSize.height)
    ) {
      return i1.getInstance().stringify(this.itemIconSize.height);
    }
    return this.theme.itemIconSize;
  }
  getItemIconWidth() {
    if (
      this.itemIconSize?.width &&
      i1.getInstance().u1(this.itemIconSize.width)
    ) {
      return i1.getInstance().stringify(this.itemIconSize.width);
    }
    return this.theme.itemIconSize;
  }
  getItemIconFillColor() {
    if (this.selected) {
      if (this.itemSelectedIconFillColor) {
        return this.itemSelectedIconFillColor.color;
      }
      return this.theme.itemSelectedIconFillColor;
    }
    if (this.itemIconFillColor) {
      return this.itemIconFillColor.color;
    }
    return this.theme.itemIconFillColor;
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('hasHybrid' in params) {
      this.updateParam('hasHybrid', params.hasHybrid);
    }
    if ('item' in params) {
      this.updateParam('item', params.item);
    }
    if ('selected' in params) {
      this.updateParam('selected', params.selected);
    }
    if ('theme' in params) {
      this.updateParam('theme', params.theme);
    }
    if ('itemMinFontScale' in params) {
      this.updateParam('itemMinFontScale', params.itemMinFontScale);
    }
    if ('itemMaxFontScale' in params) {
      this.updateParam('itemMaxFontScale', params.itemMaxFontScale);
    }
    if ('itemFontColor' in params) {
      this.updateParam('itemFontColor', params.itemFontColor);
    }
    if ('itemSelectedFontColor' in params) {
      this.updateParam('itemSelectedFontColor', params.itemSelectedFontColor);
    }
    if ('itemFontSize' in params) {
      this.updateParam('itemFontSize', params.itemFontSize);
    }
    if ('itemSelectedFontSize' in params) {
      this.updateParam('itemSelectedFontSize', params.itemSelectedFontSize);
    }
    if ('itemFontWeight' in params) {
      this.updateParam('itemFontWeight', params.itemFontWeight);
    }
    if ('itemSelectedFontWeight' in params) {
      this.updateParam('itemSelectedFontWeight', params.itemSelectedFontWeight);
    }
    if ('itemIconSize' in params) {
      this.updateParam('itemIconSize', params.itemIconSize);
    }
    if ('itemIconFillColor' in params) {
      this.updateParam('itemIconFillColor', params.itemIconFillColor);
    }
    if ('itemSelectedIconFillColor' in params) {
      this.updateParam(
        'itemSelectedIconFillColor',
        params.itemSelectedIconFillColor
      );
    }
    if ('itemSymbolFontSize' in params) {
      this.updateParam('itemSymbolFontSize', params.itemSymbolFontSize);
    }
    if ('itemSymbolFontColor' in params) {
      this.updateParam('itemSymbolFontColor', params.itemSymbolFontColor);
    }
    if ('itemSelectedSymbolFontColor' in params) {
      this.updateParam(
        'itemSelectedSymbolFontColor',
        params.itemSelectedSymbolFontColor
      );
    }
    if ('itemMinHeight' in params) {
      this.updateParam('itemMinHeight', params.itemMinHeight);
    }
    if ('itemPadding' in params) {
      this.updateParam('itemPadding', params.itemPadding);
    }
    if ('languageDirection' in params) {
      this.updateParam('languageDirection', params.languageDirection);
    }
  }
  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
o([Param], h1.prototype, 'hasHybrid', void 0);
o([Param], h1.prototype, 'item', void 0);
o([Param], h1.prototype, 'selected', void 0);
o([Param], h1.prototype, 'theme', void 0);
o([Param], h1.prototype, 'itemMinFontScale', void 0);
o([Param], h1.prototype, 'itemMaxFontScale', void 0);
o([Param], h1.prototype, 'itemFontColor', void 0);
o([Param], h1.prototype, 'itemSelectedFontColor', void 0);
o([Param], h1.prototype, 'itemFontSize', void 0);
o([Param], h1.prototype, 'itemSelectedFontSize', void 0);
o([Param], h1.prototype, 'itemFontWeight', void 0);
o([Param], h1.prototype, 'itemSelectedFontWeight', void 0);
o([Param], h1.prototype, 'itemIconSize', void 0);
o([Param], h1.prototype, 'itemIconFillColor', void 0);
o([Param], h1.prototype, 'itemSelectedIconFillColor', void 0);
o([Param], h1.prototype, 'itemSymbolFontSize', void 0);
o([Param], h1.prototype, 'itemSymbolFontColor', void 0);
o([Param], h1.prototype, 'itemSelectedSymbolFontColor', void 0);
o([Param], h1.prototype, 'itemMinHeight', void 0);
o([Param], h1.prototype, 'itemPadding', void 0);
o([Param], h1.prototype, 'languageDirection', void 0);
class i1 {
  constructor() {}
  static getInstance() {
    if (!i1.instance) {
      i1.instance = new i1();
    }
    return i1.instance;
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
  u1(metrics) {
    return metrics.value >= 0;
  }
}
function i(context, resource) {
  const resourceManager = context.getHostContext()?.resourceManager;
  if (!resourceManager) {
    return undefined;
  }
  try {
    return resourceManager.getNumber(resource);
  } catch (err) {
    return undefined;
  }
}
function normalize(value, min, max) {
  return Math.min(Math.max(value, min), max);
}
function j(groupId) {
  return (item, index) => {
    let key = groupId;
    if (item.text) {
      if (typeof item.text === 'string') {
        key += item.text;
      } else {
        key += m(item.text);
      }
    }
    if (item.icon) {
      if (typeof item.icon === 'string') {
        key += item.icon;
      } else {
        key += m(item.icon);
      }
    }
    if (item.symbol) {
      key += m(item.symbol);
    }
    return key;
  };
}
function m(resource) {
  if (resource.id !== -1) {
    return `${resource.id}`;
  } else {
    return JSON.stringify(resource);
  }
}

export default {
  SegmentButtonV2Item,
  SegmentButtonV2Items,
  TabSegmentButtonV2,
  CapsuleSegmentButtonV2,
  MultiCapsuleSegmentButtonV2,
};
