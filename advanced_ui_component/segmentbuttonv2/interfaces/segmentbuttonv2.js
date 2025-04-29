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
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
      g7 = Reflect.decorate(b7, c7, d7, e7);
    } else {
      for (var i7 = b7.length - 1; i7 >= 0; i7--) {
        if ((h7 = b7[i7])) {
          g7 = (f7 < 3 ? h7(g7) : f7 > 3 ? h7(c7, d7, g7) : h7(c7, d7)) || g7;
        }
      }
    }
    return f7 > 3 && g7 && Object.defineProperty(c7, d7, g7), g7;
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

const SMALLEST_MAX_FONT_SCALE = 1;
const LARGEST_MAX_FONT_SCALE = 2;
const SMALLEST_MIN_FONT_SCALE = 0;
const LARGEST_MIN_FONT_SCALE = 1;
const tabSimpleTheme = {
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
  hybridButtonMinHeight: {
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
  hybridItemMinHeight: {
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
  itemMaxFontScale: SMALLEST_MAX_FONT_SCALE,
  itemMaxFontScaleSmallest: SMALLEST_MAX_FONT_SCALE,
  itemMaxFontScaleLargest: LARGEST_MAX_FONT_SCALE,
  itemMinFontScale: SMALLEST_MIN_FONT_SCALE,
  itemMinFontScaleSmallest: SMALLEST_MIN_FONT_SCALE,
  itemMinFontScaleLargest: LARGEST_MIN_FONT_SCALE,
};
const capsuleSimpleTheme = {
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
  hybridButtonMinHeight: {
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
  hybridItemMinHeight: {
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
  itemMaxFontScale: SMALLEST_MAX_FONT_SCALE,
  itemMaxFontScaleSmallest: SMALLEST_MAX_FONT_SCALE,
  itemMaxFontScaleLargest: LARGEST_MAX_FONT_SCALE,
  itemMinFontScale: SMALLEST_MIN_FONT_SCALE,
  itemMinFontScaleSmallest: SMALLEST_MIN_FONT_SCALE,
  itemMinFontScaleLargest: LARGEST_MIN_FONT_SCALE,
};
let SegmentButtonV2Item = class SegmentButtonV2Item {
  constructor(a7) {
    this.text = a7.text;
    this.icon = a7.icon;
    this.symbol = a7.symbol;
    this.enabled = a7.enabled ?? true;
    this.textModifier = a7.textModifier;
    this.iconModifier = a7.iconModifier;
    this.symbolModifier = a7.symbolModifier;
    this.accessibilityText = a7.accessibilityText;
    this.accessibilityDescription = a7.accessibilityDescription;
    this.accessibilityLevel = a7.accessibilityLevel;
  }

  get isHybrid() {
    return !!this.text && (!!this.icon || !!this.symbol);
  }
};
__decorate([Trace], SegmentButtonV2Item.prototype, 'text', void 0);
__decorate([Trace], SegmentButtonV2Item.prototype, 'icon', void 0);
__decorate([Trace], SegmentButtonV2Item.prototype, 'symbol', void 0);
__decorate([Trace], SegmentButtonV2Item.prototype, 'enabled', void 0);
__decorate([Trace], SegmentButtonV2Item.prototype, 'textModifier', void 0);
__decorate([Trace], SegmentButtonV2Item.prototype, 'iconModifier', void 0);
__decorate([Trace], SegmentButtonV2Item.prototype, 'symbolModifier', void 0);
__decorate([Trace], SegmentButtonV2Item.prototype, 'accessibilityText', void 0);
__decorate(
  [Trace],
  SegmentButtonV2Item.prototype,
  'accessibilityDescription',
  void 0
);
__decorate(
  [Trace],
  SegmentButtonV2Item.prototype,
  'accessibilityLevel',
  void 0
);
__decorate([Computed], SegmentButtonV2Item.prototype, 'isHybrid', null);
SegmentButtonV2Item = __decorate([ObservedV2], SegmentButtonV2Item);

export { SegmentButtonV2Item };
let SegmentButtonV2Items = class SegmentButtonV2Items extends Array {
  constructor(y6) {
    super(typeof y6 === 'number' ? y6 : 0);
    if (typeof y6 !== 'number' && y6 && y6.length) {
      for (let z6 of y6) {
        if (z6) {
          this.push(new SegmentButtonV2Item(z6));
        }
      }
    }
  }

  get hasHybrid() {
    return this.some((x6) => x6.isHybrid);
  }
};
__decorate([Computed], SegmentButtonV2Items.prototype, 'hasHybrid', null);
SegmentButtonV2Items = __decorate([ObservedV2], SegmentButtonV2Items);

export { SegmentButtonV2Items };
const EMPTY_ITEMS = new SegmentButtonV2Items([]);

export class TabSegmentButtonV2 extends ViewV2 {
  constructor(r6, s6, t6, u6 = -1, v6, w6) {
    super(r6, u6, w6);
    this.initParam('items', s6 && 'items' in s6 ? s6.items : undefined);
    this.initParam(
      'selectedIndex',
      s6 && 'selectedIndex' in s6 ? s6.selectedIndex : undefined
    );
    this.$selectedIndex = '$selectedIndex' in s6 ? s6.$selectedIndex : () => {};
    this.onItemClicked = 'onItemClicked' in s6 ? s6.onItemClicked : () => {};
    this.initParam(
      'itemMinFontScale',
      s6 && 'itemMinFontScale' in s6 ? s6.itemMinFontScale : undefined
    );
    this.initParam(
      'itemMaxFontScale',
      s6 && 'itemMaxFontScale' in s6 ? s6.itemMaxFontScale : undefined
    );
    this.initParam(
      'itemSpace',
      s6 && 'itemSpace' in s6 ? s6.itemSpace : undefined
    );
    this.initParam(
      'itemFontSize',
      s6 && 'itemFontSize' in s6 ? s6.itemFontSize : undefined
    );
    this.initParam(
      'itemSelectedFontSize',
      s6 && 'itemSelectedFontSize' in s6 ? s6.itemSelectedFontSize : undefined
    );
    this.initParam(
      'itemFontColor',
      s6 && 'itemFontColor' in s6 ? s6.itemFontColor : undefined
    );
    this.initParam(
      'itemSelectedFontColor',
      s6 && 'itemSelectedFontColor' in s6 ? s6.itemSelectedFontColor : undefined
    );
    this.initParam(
      'itemFontWeight',
      s6 && 'itemFontWeight' in s6 ? s6.itemFontWeight : undefined
    );
    this.initParam(
      'itemSelectedFontWeight',
      s6 && 'itemSelectedFontWeight' in s6
        ? s6.itemSelectedFontWeight
        : undefined
    );
    this.initParam(
      'itemBorderRadius',
      s6 && 'itemBorderRadius' in s6 ? s6.itemBorderRadius : undefined
    );
    this.initParam(
      'itemSelectedBackgroundColor',
      s6 && 'itemSelectedBackgroundColor' in s6
        ? s6.itemSelectedBackgroundColor
        : undefined
    );
    this.initParam(
      'itemIconSize',
      s6 && 'itemIconSize' in s6 ? s6.itemIconSize : undefined
    );
    this.initParam(
      'itemIconFillColor',
      s6 && 'itemIconFillColor' in s6 ? s6.itemIconFillColor : undefined
    );
    this.initParam(
      'itemSelectedIconFillColor',
      s6 && 'itemSelectedIconFillColor' in s6
        ? s6.itemSelectedIconFillColor
        : undefined
    );
    this.initParam(
      'itemSymbolFontSize',
      s6 && 'itemSymbolFontSize' in s6 ? s6.itemSymbolFontSize : undefined
    );
    this.initParam(
      'itemSymbolFontColor',
      s6 && 'itemSymbolFontColor' in s6 ? s6.itemSymbolFontColor : undefined
    );
    this.initParam(
      'itemSelectedSymbolFontColor',
      s6 && 'itemSelectedSymbolFontColor' in s6
        ? s6.itemSelectedSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemMinHeight',
      s6 && 'itemMinHeight' in s6 ? s6.itemMinHeight : undefined
    );
    this.initParam(
      'itemPadding',
      s6 && 'itemPadding' in s6 ? s6.itemPadding : undefined
    );
    this.initParam(
      'itemShadow',
      s6 && 'itemShadow' in s6 ? s6.itemShadow : undefined
    );
    this.initParam(
      'buttonBackgroundColor',
      s6 && 'buttonBackgroundColor' in s6 ? s6.buttonBackgroundColor : undefined
    );
    this.initParam(
      'buttonBackgroundBlurStyle',
      s6 && 'buttonBackgroundBlurStyle' in s6
        ? s6.buttonBackgroundBlurStyle
        : undefined
    );
    this.initParam(
      'buttonBackgroundBlurStyleOptions',
      s6 && 'buttonBackgroundBlurStyleOptions' in s6
        ? s6.buttonBackgroundBlurStyleOptions
        : undefined
    );
    this.initParam(
      'buttonBackgroundEffect',
      s6 && 'buttonBackgroundEffect' in s6
        ? s6.buttonBackgroundEffect
        : undefined
    );
    this.initParam(
      'buttonBorderRadius',
      s6 && 'buttonBorderRadius' in s6 ? s6.buttonBorderRadius : undefined
    );
    this.initParam(
      'buttonMinHeight',
      s6 && 'buttonMinHeight' in s6 ? s6.buttonMinHeight : undefined
    );
    this.initParam(
      'buttonPadding',
      s6 && 'buttonPadding' in s6 ? s6.buttonPadding : undefined
    );
    this.initParam(
      'languageDirection',
      s6 && 'languageDirection' in s6 ? s6.languageDirection : undefined
    );
    this.finalizeConstruction();
  }

  resetStateVarsOnReuse(q6) {
    this.resetParam('items', q6 && 'items' in q6 ? q6.items : undefined);
    this.resetParam(
      'selectedIndex',
      q6 && 'selectedIndex' in q6 ? q6.selectedIndex : undefined
    );
    this.$selectedIndex = '$selectedIndex' in q6 ? q6.$selectedIndex : () => {};
    this.onItemClicked = 'onItemClicked' in q6 ? q6.onItemClicked : () => {};
    this.resetParam(
      'itemMinFontScale',
      q6 && 'itemMinFontScale' in q6 ? q6.itemMinFontScale : undefined
    );
    this.resetParam(
      'itemMaxFontScale',
      q6 && 'itemMaxFontScale' in q6 ? q6.itemMaxFontScale : undefined
    );
    this.resetParam(
      'itemSpace',
      q6 && 'itemSpace' in q6 ? q6.itemSpace : undefined
    );
    this.resetParam(
      'itemFontSize',
      q6 && 'itemFontSize' in q6 ? q6.itemFontSize : undefined
    );
    this.resetParam(
      'itemSelectedFontSize',
      q6 && 'itemSelectedFontSize' in q6 ? q6.itemSelectedFontSize : undefined
    );
    this.resetParam(
      'itemFontColor',
      q6 && 'itemFontColor' in q6 ? q6.itemFontColor : undefined
    );
    this.resetParam(
      'itemSelectedFontColor',
      q6 && 'itemSelectedFontColor' in q6 ? q6.itemSelectedFontColor : undefined
    );
    this.resetParam(
      'itemFontWeight',
      q6 && 'itemFontWeight' in q6 ? q6.itemFontWeight : undefined
    );
    this.resetParam(
      'itemSelectedFontWeight',
      q6 && 'itemSelectedFontWeight' in q6
        ? q6.itemSelectedFontWeight
        : undefined
    );
    this.resetParam(
      'itemBorderRadius',
      q6 && 'itemBorderRadius' in q6 ? q6.itemBorderRadius : undefined
    );
    this.resetParam(
      'itemSelectedBackgroundColor',
      q6 && 'itemSelectedBackgroundColor' in q6
        ? q6.itemSelectedBackgroundColor
        : undefined
    );
    this.resetParam(
      'itemIconSize',
      q6 && 'itemIconSize' in q6 ? q6.itemIconSize : undefined
    );
    this.resetParam(
      'itemIconFillColor',
      q6 && 'itemIconFillColor' in q6 ? q6.itemIconFillColor : undefined
    );
    this.resetParam(
      'itemSelectedIconFillColor',
      q6 && 'itemSelectedIconFillColor' in q6
        ? q6.itemSelectedIconFillColor
        : undefined
    );
    this.resetParam(
      'itemSymbolFontSize',
      q6 && 'itemSymbolFontSize' in q6 ? q6.itemSymbolFontSize : undefined
    );
    this.resetParam(
      'itemSymbolFontColor',
      q6 && 'itemSymbolFontColor' in q6 ? q6.itemSymbolFontColor : undefined
    );
    this.resetParam(
      'itemSelectedSymbolFontColor',
      q6 && 'itemSelectedSymbolFontColor' in q6
        ? q6.itemSelectedSymbolFontColor
        : undefined
    );
    this.resetParam(
      'itemMinHeight',
      q6 && 'itemMinHeight' in q6 ? q6.itemMinHeight : undefined
    );
    this.resetParam(
      'itemPadding',
      q6 && 'itemPadding' in q6 ? q6.itemPadding : undefined
    );
    this.resetParam(
      'itemShadow',
      q6 && 'itemShadow' in q6 ? q6.itemShadow : undefined
    );
    this.resetParam(
      'buttonBackgroundColor',
      q6 && 'buttonBackgroundColor' in q6 ? q6.buttonBackgroundColor : undefined
    );
    this.resetParam(
      'buttonBackgroundBlurStyle',
      q6 && 'buttonBackgroundBlurStyle' in q6
        ? q6.buttonBackgroundBlurStyle
        : undefined
    );
    this.resetParam(
      'buttonBackgroundBlurStyleOptions',
      q6 && 'buttonBackgroundBlurStyleOptions' in q6
        ? q6.buttonBackgroundBlurStyleOptions
        : undefined
    );
    this.resetParam(
      'buttonBackgroundEffect',
      q6 && 'buttonBackgroundEffect' in q6
        ? q6.buttonBackgroundEffect
        : undefined
    );
    this.resetParam(
      'buttonBorderRadius',
      q6 && 'buttonBorderRadius' in q6 ? q6.buttonBorderRadius : undefined
    );
    this.resetParam(
      'buttonMinHeight',
      q6 && 'buttonMinHeight' in q6 ? q6.buttonMinHeight : undefined
    );
    this.resetParam(
      'buttonPadding',
      q6 && 'buttonPadding' in q6 ? q6.buttonPadding : undefined
    );
    this.resetParam(
      'languageDirection',
      q6 && 'languageDirection' in q6 ? q6.languageDirection : undefined
    );
  }

  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    {
      this.observeComponentCreation2(
        (k6, l6) => {
          if (l6) {
            let m6 = new SimpleSegmentButtonV2(
              this,
              {
                theme: tabSimpleTheme,
                items: this.items,
                selectedIndex: this.selectedIndex,
                $selectedIndex: (p6) => {
                  this.$selectedIndex?.(p6);
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
              k6,
              () => {},
              {
                page: 'library/src/main/ets/components/MainPage.ets',
                line: 295,
                col: 5,
              }
            );
            ViewV2.create(m6);
            let n6 = () => {
              return {
                theme: tabSimpleTheme,
                items: this.items,
                selectedIndex: this.selectedIndex,
                $selectedIndex: (o6) => {
                  this.$selectedIndex?.(o6);
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
            m6.paramsGenerator_ = n6;
          } else {
            this.updateStateVarsOfChildByElmtId(k6, {
              theme: tabSimpleTheme,
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

  updateStateVars(j6) {
    if (j6 === undefined) {
      return;
    }
    if ('items' in j6) {
      this.updateParam('items', j6.items);
    }
    if ('selectedIndex' in j6) {
      this.updateParam('selectedIndex', j6.selectedIndex);
    }
    if ('itemMinFontScale' in j6) {
      this.updateParam('itemMinFontScale', j6.itemMinFontScale);
    }
    if ('itemMaxFontScale' in j6) {
      this.updateParam('itemMaxFontScale', j6.itemMaxFontScale);
    }
    if ('itemSpace' in j6) {
      this.updateParam('itemSpace', j6.itemSpace);
    }
    if ('itemFontSize' in j6) {
      this.updateParam('itemFontSize', j6.itemFontSize);
    }
    if ('itemSelectedFontSize' in j6) {
      this.updateParam('itemSelectedFontSize', j6.itemSelectedFontSize);
    }
    if ('itemFontColor' in j6) {
      this.updateParam('itemFontColor', j6.itemFontColor);
    }
    if ('itemSelectedFontColor' in j6) {
      this.updateParam('itemSelectedFontColor', j6.itemSelectedFontColor);
    }
    if ('itemFontWeight' in j6) {
      this.updateParam('itemFontWeight', j6.itemFontWeight);
    }
    if ('itemSelectedFontWeight' in j6) {
      this.updateParam('itemSelectedFontWeight', j6.itemSelectedFontWeight);
    }
    if ('itemBorderRadius' in j6) {
      this.updateParam('itemBorderRadius', j6.itemBorderRadius);
    }
    if ('itemSelectedBackgroundColor' in j6) {
      this.updateParam(
        'itemSelectedBackgroundColor',
        j6.itemSelectedBackgroundColor
      );
    }
    if ('itemIconSize' in j6) {
      this.updateParam('itemIconSize', j6.itemIconSize);
    }
    if ('itemIconFillColor' in j6) {
      this.updateParam('itemIconFillColor', j6.itemIconFillColor);
    }
    if ('itemSelectedIconFillColor' in j6) {
      this.updateParam(
        'itemSelectedIconFillColor',
        j6.itemSelectedIconFillColor
      );
    }
    if ('itemSymbolFontSize' in j6) {
      this.updateParam('itemSymbolFontSize', j6.itemSymbolFontSize);
    }
    if ('itemSymbolFontColor' in j6) {
      this.updateParam('itemSymbolFontColor', j6.itemSymbolFontColor);
    }
    if ('itemSelectedSymbolFontColor' in j6) {
      this.updateParam(
        'itemSelectedSymbolFontColor',
        j6.itemSelectedSymbolFontColor
      );
    }
    if ('itemMinHeight' in j6) {
      this.updateParam('itemMinHeight', j6.itemMinHeight);
    }
    if ('itemPadding' in j6) {
      this.updateParam('itemPadding', j6.itemPadding);
    }
    if ('itemShadow' in j6) {
      this.updateParam('itemShadow', j6.itemShadow);
    }
    if ('buttonBackgroundColor' in j6) {
      this.updateParam('buttonBackgroundColor', j6.buttonBackgroundColor);
    }
    if ('buttonBackgroundBlurStyle' in j6) {
      this.updateParam(
        'buttonBackgroundBlurStyle',
        j6.buttonBackgroundBlurStyle
      );
    }
    if ('buttonBackgroundBlurStyleOptions' in j6) {
      this.updateParam(
        'buttonBackgroundBlurStyleOptions',
        j6.buttonBackgroundBlurStyleOptions
      );
    }
    if ('buttonBackgroundEffect' in j6) {
      this.updateParam('buttonBackgroundEffect', j6.buttonBackgroundEffect);
    }
    if ('buttonBorderRadius' in j6) {
      this.updateParam('buttonBorderRadius', j6.buttonBorderRadius);
    }
    if ('buttonMinHeight' in j6) {
      this.updateParam('buttonMinHeight', j6.buttonMinHeight);
    }
    if ('buttonPadding' in j6) {
      this.updateParam('buttonPadding', j6.buttonPadding);
    }
    if ('languageDirection' in j6) {
      this.updateParam('languageDirection', j6.languageDirection);
    }
  }

  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
__decorate([Param], TabSegmentButtonV2.prototype, 'items', void 0);
__decorate([Param], TabSegmentButtonV2.prototype, 'selectedIndex', void 0);
__decorate([Event], TabSegmentButtonV2.prototype, '$selectedIndex', void 0);
__decorate([Event], TabSegmentButtonV2.prototype, 'onItemClicked', void 0);
__decorate([Param], TabSegmentButtonV2.prototype, 'itemMinFontScale', void 0);
__decorate([Param], TabSegmentButtonV2.prototype, 'itemMaxFontScale', void 0);
__decorate([Param], TabSegmentButtonV2.prototype, 'itemSpace', void 0);
__decorate([Param], TabSegmentButtonV2.prototype, 'itemFontSize', void 0);
__decorate(
  [Param],
  TabSegmentButtonV2.prototype,
  'itemSelectedFontSize',
  void 0
);
__decorate([Param], TabSegmentButtonV2.prototype, 'itemFontColor', void 0);
__decorate(
  [Param],
  TabSegmentButtonV2.prototype,
  'itemSelectedFontColor',
  void 0
);
__decorate([Param], TabSegmentButtonV2.prototype, 'itemFontWeight', void 0);
__decorate(
  [Param],
  TabSegmentButtonV2.prototype,
  'itemSelectedFontWeight',
  void 0
);
__decorate([Param], TabSegmentButtonV2.prototype, 'itemBorderRadius', void 0);
__decorate(
  [Param],
  TabSegmentButtonV2.prototype,
  'itemSelectedBackgroundColor',
  void 0
);
__decorate([Param], TabSegmentButtonV2.prototype, 'itemIconSize', void 0);
__decorate([Param], TabSegmentButtonV2.prototype, 'itemIconFillColor', void 0);
__decorate(
  [Param],
  TabSegmentButtonV2.prototype,
  'itemSelectedIconFillColor',
  void 0
);
__decorate([Param], TabSegmentButtonV2.prototype, 'itemSymbolFontSize', void 0);
__decorate(
  [Param],
  TabSegmentButtonV2.prototype,
  'itemSymbolFontColor',
  void 0
);
__decorate(
  [Param],
  TabSegmentButtonV2.prototype,
  'itemSelectedSymbolFontColor',
  void 0
);
__decorate([Param], TabSegmentButtonV2.prototype, 'itemMinHeight', void 0);
__decorate([Param], TabSegmentButtonV2.prototype, 'itemPadding', void 0);
__decorate([Param], TabSegmentButtonV2.prototype, 'itemShadow', void 0);
__decorate(
  [Param],
  TabSegmentButtonV2.prototype,
  'buttonBackgroundColor',
  void 0
);
__decorate(
  [Param],
  TabSegmentButtonV2.prototype,
  'buttonBackgroundBlurStyle',
  void 0
);
__decorate(
  [Param],
  TabSegmentButtonV2.prototype,
  'buttonBackgroundBlurStyleOptions',
  void 0
);
__decorate(
  [Param],
  TabSegmentButtonV2.prototype,
  'buttonBackgroundEffect',
  void 0
);
__decorate([Param], TabSegmentButtonV2.prototype, 'buttonBorderRadius', void 0);
__decorate([Param], TabSegmentButtonV2.prototype, 'buttonMinHeight', void 0);
__decorate([Param], TabSegmentButtonV2.prototype, 'buttonPadding', void 0);
__decorate([Param], TabSegmentButtonV2.prototype, 'languageDirection', void 0);

export class CapsuleSegmentButtonV2 extends ViewV2 {
  constructor(d6, e6, f6, g6 = -1, h6, i6) {
    super(d6, g6, i6);
    this.initParam('items', e6 && 'items' in e6 ? e6.items : undefined);
    this.initParam(
      'selectedIndex',
      e6 && 'selectedIndex' in e6 ? e6.selectedIndex : undefined
    );
    this.$selectedIndex = '$selectedIndex' in e6 ? e6.$selectedIndex : () => {};
    this.onItemClicked = 'onItemClicked' in e6 ? e6.onItemClicked : () => {};
    this.initParam(
      'itemMinFontScale',
      e6 && 'itemMinFontScale' in e6 ? e6.itemMinFontScale : undefined
    );
    this.initParam(
      'itemMaxFontScale',
      e6 && 'itemMaxFontScale' in e6 ? e6.itemMaxFontScale : undefined
    );
    this.initParam(
      'itemSpace',
      e6 && 'itemSpace' in e6 ? e6.itemSpace : undefined
    );
    this.initParam(
      'itemFontColor',
      e6 && 'itemFontColor' in e6 ? e6.itemFontColor : undefined
    );
    this.initParam(
      'itemSelectedFontColor',
      e6 && 'itemSelectedFontColor' in e6 ? e6.itemSelectedFontColor : undefined
    );
    this.initParam(
      'itemFontSize',
      e6 && 'itemFontSize' in e6 ? e6.itemFontSize : undefined
    );
    this.initParam(
      'itemSelectedFontSize',
      e6 && 'itemSelectedFontSize' in e6 ? e6.itemSelectedFontSize : undefined
    );
    this.initParam(
      'itemFontWeight',
      e6 && 'itemFontWeight' in e6 ? e6.itemFontWeight : undefined
    );
    this.initParam(
      'itemSelectedFontWeight',
      e6 && 'itemSelectedFontWeight' in e6
        ? e6.itemSelectedFontWeight
        : undefined
    );
    this.initParam(
      'itemBorderRadius',
      e6 && 'itemBorderRadius' in e6 ? e6.itemBorderRadius : undefined
    );
    this.initParam(
      'itemSelectedBackgroundColor',
      e6 && 'itemSelectedBackgroundColor' in e6
        ? e6.itemSelectedBackgroundColor
        : undefined
    );
    this.initParam(
      'itemIconSize',
      e6 && 'itemIconSize' in e6 ? e6.itemIconSize : undefined
    );
    this.initParam(
      'itemIconFillColor',
      e6 && 'itemIconFillColor' in e6 ? e6.itemIconFillColor : undefined
    );
    this.initParam(
      'itemSelectedIconFillColor',
      e6 && 'itemSelectedIconFillColor' in e6
        ? e6.itemSelectedIconFillColor
        : undefined
    );
    this.initParam(
      'itemSymbolFontSize',
      e6 && 'itemSymbolFontSize' in e6 ? e6.itemSymbolFontSize : undefined
    );
    this.initParam(
      'itemSymbolFontColor',
      e6 && 'itemSymbolFontColor' in e6 ? e6.itemSymbolFontColor : undefined
    );
    this.initParam(
      'itemSelectedSymbolFontColor',
      e6 && 'itemSelectedSymbolFontColor' in e6
        ? e6.itemSelectedSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemMinHeight',
      e6 && 'itemMinHeight' in e6 ? e6.itemMinHeight : undefined
    );
    this.initParam(
      'itemPadding',
      e6 && 'itemPadding' in e6 ? e6.itemPadding : undefined
    );
    this.initParam(
      'itemShadow',
      e6 && 'itemShadow' in e6 ? e6.itemShadow : undefined
    );
    this.initParam(
      'buttonBackgroundColor',
      e6 && 'buttonBackgroundColor' in e6 ? e6.buttonBackgroundColor : undefined
    );
    this.initParam(
      'buttonBackgroundBlurStyle',
      e6 && 'buttonBackgroundBlurStyle' in e6
        ? e6.buttonBackgroundBlurStyle
        : undefined
    );
    this.initParam(
      'buttonBackgroundBlurStyleOptions',
      e6 && 'buttonBackgroundBlurStyleOptions' in e6
        ? e6.buttonBackgroundBlurStyleOptions
        : undefined
    );
    this.initParam(
      'buttonBackgroundEffect',
      e6 && 'buttonBackgroundEffect' in e6
        ? e6.buttonBackgroundEffect
        : undefined
    );
    this.initParam(
      'buttonBorderRadius',
      e6 && 'buttonBorderRadius' in e6 ? e6.buttonBorderRadius : undefined
    );
    this.initParam(
      'buttonMinHeight',
      e6 && 'buttonMinHeight' in e6 ? e6.buttonMinHeight : undefined
    );
    this.initParam(
      'buttonPadding',
      e6 && 'buttonPadding' in e6 ? e6.buttonPadding : undefined
    );
    this.initParam(
      'languageDirection',
      e6 && 'languageDirection' in e6 ? e6.languageDirection : undefined
    );
    this.finalizeConstruction();
  }

  resetStateVarsOnReuse(c6) {
    this.resetParam('items', c6 && 'items' in c6 ? c6.items : undefined);
    this.resetParam(
      'selectedIndex',
      c6 && 'selectedIndex' in c6 ? c6.selectedIndex : undefined
    );
    this.$selectedIndex = '$selectedIndex' in c6 ? c6.$selectedIndex : () => {};
    this.onItemClicked = 'onItemClicked' in c6 ? c6.onItemClicked : () => {};
    this.resetParam(
      'itemMinFontScale',
      c6 && 'itemMinFontScale' in c6 ? c6.itemMinFontScale : undefined
    );
    this.resetParam(
      'itemMaxFontScale',
      c6 && 'itemMaxFontScale' in c6 ? c6.itemMaxFontScale : undefined
    );
    this.resetParam(
      'itemSpace',
      c6 && 'itemSpace' in c6 ? c6.itemSpace : undefined
    );
    this.resetParam(
      'itemFontColor',
      c6 && 'itemFontColor' in c6 ? c6.itemFontColor : undefined
    );
    this.resetParam(
      'itemSelectedFontColor',
      c6 && 'itemSelectedFontColor' in c6 ? c6.itemSelectedFontColor : undefined
    );
    this.resetParam(
      'itemFontSize',
      c6 && 'itemFontSize' in c6 ? c6.itemFontSize : undefined
    );
    this.resetParam(
      'itemSelectedFontSize',
      c6 && 'itemSelectedFontSize' in c6 ? c6.itemSelectedFontSize : undefined
    );
    this.resetParam(
      'itemFontWeight',
      c6 && 'itemFontWeight' in c6 ? c6.itemFontWeight : undefined
    );
    this.resetParam(
      'itemSelectedFontWeight',
      c6 && 'itemSelectedFontWeight' in c6
        ? c6.itemSelectedFontWeight
        : undefined
    );
    this.resetParam(
      'itemBorderRadius',
      c6 && 'itemBorderRadius' in c6 ? c6.itemBorderRadius : undefined
    );
    this.resetParam(
      'itemSelectedBackgroundColor',
      c6 && 'itemSelectedBackgroundColor' in c6
        ? c6.itemSelectedBackgroundColor
        : undefined
    );
    this.resetParam(
      'itemIconSize',
      c6 && 'itemIconSize' in c6 ? c6.itemIconSize : undefined
    );
    this.resetParam(
      'itemIconFillColor',
      c6 && 'itemIconFillColor' in c6 ? c6.itemIconFillColor : undefined
    );
    this.resetParam(
      'itemSelectedIconFillColor',
      c6 && 'itemSelectedIconFillColor' in c6
        ? c6.itemSelectedIconFillColor
        : undefined
    );
    this.resetParam(
      'itemSymbolFontSize',
      c6 && 'itemSymbolFontSize' in c6 ? c6.itemSymbolFontSize : undefined
    );
    this.resetParam(
      'itemSymbolFontColor',
      c6 && 'itemSymbolFontColor' in c6 ? c6.itemSymbolFontColor : undefined
    );
    this.resetParam(
      'itemSelectedSymbolFontColor',
      c6 && 'itemSelectedSymbolFontColor' in c6
        ? c6.itemSelectedSymbolFontColor
        : undefined
    );
    this.resetParam(
      'itemMinHeight',
      c6 && 'itemMinHeight' in c6 ? c6.itemMinHeight : undefined
    );
    this.resetParam(
      'itemPadding',
      c6 && 'itemPadding' in c6 ? c6.itemPadding : undefined
    );
    this.resetParam(
      'itemShadow',
      c6 && 'itemShadow' in c6 ? c6.itemShadow : undefined
    );
    this.resetParam(
      'buttonBackgroundColor',
      c6 && 'buttonBackgroundColor' in c6 ? c6.buttonBackgroundColor : undefined
    );
    this.resetParam(
      'buttonBackgroundBlurStyle',
      c6 && 'buttonBackgroundBlurStyle' in c6
        ? c6.buttonBackgroundBlurStyle
        : undefined
    );
    this.resetParam(
      'buttonBackgroundBlurStyleOptions',
      c6 && 'buttonBackgroundBlurStyleOptions' in c6
        ? c6.buttonBackgroundBlurStyleOptions
        : undefined
    );
    this.resetParam(
      'buttonBackgroundEffect',
      c6 && 'buttonBackgroundEffect' in c6
        ? c6.buttonBackgroundEffect
        : undefined
    );
    this.resetParam(
      'buttonBorderRadius',
      c6 && 'buttonBorderRadius' in c6 ? c6.buttonBorderRadius : undefined
    );
    this.resetParam(
      'buttonMinHeight',
      c6 && 'buttonMinHeight' in c6 ? c6.buttonMinHeight : undefined
    );
    this.resetParam(
      'buttonPadding',
      c6 && 'buttonPadding' in c6 ? c6.buttonPadding : undefined
    );
    this.resetParam(
      'languageDirection',
      c6 && 'languageDirection' in c6 ? c6.languageDirection : undefined
    );
  }

  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    {
      this.observeComponentCreation2(
        (w5, x5) => {
          if (x5) {
            let y5 = new SimpleSegmentButtonV2(
              this,
              {
                theme: capsuleSimpleTheme,
                items: this.items,
                selectedIndex: this.selectedIndex,
                $selectedIndex: (b6) => {
                  this.$selectedIndex?.(b6);
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
              w5,
              () => {},
              {
                page: 'library/src/main/ets/components/MainPage.ets',
                line: 405,
                col: 5,
              }
            );
            ViewV2.create(y5);
            let z5 = () => {
              return {
                theme: capsuleSimpleTheme,
                items: this.items,
                selectedIndex: this.selectedIndex,
                $selectedIndex: (a6) => {
                  this.$selectedIndex?.(a6);
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
            y5.paramsGenerator_ = z5;
          } else {
            this.updateStateVarsOfChildByElmtId(w5, {
              theme: capsuleSimpleTheme,
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

  updateStateVars(v5) {
    if (v5 === undefined) {
      return;
    }
    if ('items' in v5) {
      this.updateParam('items', v5.items);
    }
    if ('selectedIndex' in v5) {
      this.updateParam('selectedIndex', v5.selectedIndex);
    }
    if ('itemMinFontScale' in v5) {
      this.updateParam('itemMinFontScale', v5.itemMinFontScale);
    }
    if ('itemMaxFontScale' in v5) {
      this.updateParam('itemMaxFontScale', v5.itemMaxFontScale);
    }
    if ('itemSpace' in v5) {
      this.updateParam('itemSpace', v5.itemSpace);
    }
    if ('itemFontColor' in v5) {
      this.updateParam('itemFontColor', v5.itemFontColor);
    }
    if ('itemSelectedFontColor' in v5) {
      this.updateParam('itemSelectedFontColor', v5.itemSelectedFontColor);
    }
    if ('itemFontSize' in v5) {
      this.updateParam('itemFontSize', v5.itemFontSize);
    }
    if ('itemSelectedFontSize' in v5) {
      this.updateParam('itemSelectedFontSize', v5.itemSelectedFontSize);
    }
    if ('itemFontWeight' in v5) {
      this.updateParam('itemFontWeight', v5.itemFontWeight);
    }
    if ('itemSelectedFontWeight' in v5) {
      this.updateParam('itemSelectedFontWeight', v5.itemSelectedFontWeight);
    }
    if ('itemBorderRadius' in v5) {
      this.updateParam('itemBorderRadius', v5.itemBorderRadius);
    }
    if ('itemSelectedBackgroundColor' in v5) {
      this.updateParam(
        'itemSelectedBackgroundColor',
        v5.itemSelectedBackgroundColor
      );
    }
    if ('itemIconSize' in v5) {
      this.updateParam('itemIconSize', v5.itemIconSize);
    }
    if ('itemIconFillColor' in v5) {
      this.updateParam('itemIconFillColor', v5.itemIconFillColor);
    }
    if ('itemSelectedIconFillColor' in v5) {
      this.updateParam(
        'itemSelectedIconFillColor',
        v5.itemSelectedIconFillColor
      );
    }
    if ('itemSymbolFontSize' in v5) {
      this.updateParam('itemSymbolFontSize', v5.itemSymbolFontSize);
    }
    if ('itemSymbolFontColor' in v5) {
      this.updateParam('itemSymbolFontColor', v5.itemSymbolFontColor);
    }
    if ('itemSelectedSymbolFontColor' in v5) {
      this.updateParam(
        'itemSelectedSymbolFontColor',
        v5.itemSelectedSymbolFontColor
      );
    }
    if ('itemMinHeight' in v5) {
      this.updateParam('itemMinHeight', v5.itemMinHeight);
    }
    if ('itemPadding' in v5) {
      this.updateParam('itemPadding', v5.itemPadding);
    }
    if ('itemShadow' in v5) {
      this.updateParam('itemShadow', v5.itemShadow);
    }
    if ('buttonBackgroundColor' in v5) {
      this.updateParam('buttonBackgroundColor', v5.buttonBackgroundColor);
    }
    if ('buttonBackgroundBlurStyle' in v5) {
      this.updateParam(
        'buttonBackgroundBlurStyle',
        v5.buttonBackgroundBlurStyle
      );
    }
    if ('buttonBackgroundBlurStyleOptions' in v5) {
      this.updateParam(
        'buttonBackgroundBlurStyleOptions',
        v5.buttonBackgroundBlurStyleOptions
      );
    }
    if ('buttonBackgroundEffect' in v5) {
      this.updateParam('buttonBackgroundEffect', v5.buttonBackgroundEffect);
    }
    if ('buttonBorderRadius' in v5) {
      this.updateParam('buttonBorderRadius', v5.buttonBorderRadius);
    }
    if ('buttonMinHeight' in v5) {
      this.updateParam('buttonMinHeight', v5.buttonMinHeight);
    }
    if ('buttonPadding' in v5) {
      this.updateParam('buttonPadding', v5.buttonPadding);
    }
    if ('languageDirection' in v5) {
      this.updateParam('languageDirection', v5.languageDirection);
    }
  }

  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
__decorate([Param], CapsuleSegmentButtonV2.prototype, 'items', void 0);
__decorate([Param], CapsuleSegmentButtonV2.prototype, 'selectedIndex', void 0);
__decorate([Event], CapsuleSegmentButtonV2.prototype, '$selectedIndex', void 0);
__decorate([Event], CapsuleSegmentButtonV2.prototype, 'onItemClicked', void 0);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemMinFontScale',
  void 0
);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemMaxFontScale',
  void 0
);
__decorate([Param], CapsuleSegmentButtonV2.prototype, 'itemSpace', void 0);
__decorate([Param], CapsuleSegmentButtonV2.prototype, 'itemFontColor', void 0);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemSelectedFontColor',
  void 0
);
__decorate([Param], CapsuleSegmentButtonV2.prototype, 'itemFontSize', void 0);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemSelectedFontSize',
  void 0
);
__decorate([Param], CapsuleSegmentButtonV2.prototype, 'itemFontWeight', void 0);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemSelectedFontWeight',
  void 0
);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemBorderRadius',
  void 0
);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemSelectedBackgroundColor',
  void 0
);
__decorate([Param], CapsuleSegmentButtonV2.prototype, 'itemIconSize', void 0);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemIconFillColor',
  void 0
);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemSelectedIconFillColor',
  void 0
);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemSymbolFontSize',
  void 0
);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemSymbolFontColor',
  void 0
);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'itemSelectedSymbolFontColor',
  void 0
);
__decorate([Param], CapsuleSegmentButtonV2.prototype, 'itemMinHeight', void 0);
__decorate([Param], CapsuleSegmentButtonV2.prototype, 'itemPadding', void 0);
__decorate([Param], CapsuleSegmentButtonV2.prototype, 'itemShadow', void 0);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'buttonBackgroundColor',
  void 0
);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'buttonBackgroundBlurStyle',
  void 0
);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'buttonBackgroundBlurStyleOptions',
  void 0
);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'buttonBackgroundEffect',
  void 0
);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'buttonBorderRadius',
  void 0
);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'buttonMinHeight',
  void 0
);
__decorate([Param], CapsuleSegmentButtonV2.prototype, 'buttonPadding', void 0);
__decorate(
  [Param],
  CapsuleSegmentButtonV2.prototype,
  'languageDirection',
  void 0
);

class SimpleSegmentButtonV2 extends ViewV2 {
  constructor(c4, d4, e4, f4 = -1, g4, h4) {
    super(c4, f4, h4);
    this.ContentLayer = () => {
      const t4 =
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.length
          ? PUV2ViewBase.contextStack[PUV2ViewBase.contextStack.length - 1]
          : null;
      this.observeComponentCreation2((i5, j5) => {
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
        PanGesture.onActionStart((s5) => {
          const t5 = s5.fingerList.find(Boolean);
          if (!t5) {
            return;
          }
          const u5 = this.getIndexByPosition(t5.globalX, t5.globalY);
          if (!this.isItemEnabled(u5)) {
            return;
          }
          if (s5.axisHorizontal !== 0 || s5.axisVertical !== 0) {
            this.isMouseWheelScroll = true;
            return;
          }
          if (u5 === this.normalizedSelectedIndex) {
            this.isDragging = true;
          }
          this.panStartGlobalX = t5.globalX;
          this.panStartIndex = u5;
        });
        PanGesture.onActionUpdate((p5) => {
          if (!this.isDragging) {
            return;
          }
          const q5 = p5.fingerList.find(Boolean);
          if (!q5) {
            return;
          }
          const r5 = this.getIndexByPosition(q5.globalX, q5.globalY);
          this.updateSelectedIndex(r5);
        });
        PanGesture.onActionEnd((k5) => {
          if (!this.isItemEnabled(this.panStartIndex)) {
            return;
          }
          if (this.isMouseWheelScroll) {
            const n5 = k5.offsetX !== 0 ? k5.offsetX : k5.offsetY;
            const o5 = n5 < 0 ? 1 : -1;
            this.updateSelectedIndex(this.normalizedSelectedIndex + o5);
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
          const l5 = k5.fingerList.find(Boolean);
          if (!l5) {
            return;
          }
          let m5 = l5.globalX - this.panStartGlobalX < 0 ? -1 : 1;
          if (this.isRTL()) {
            m5 = -m5;
          }
          this.updateSelectedIndex(this.normalizedSelectedIndex + m5);
        });
        PanGesture.onActionCancel(() => {
          this.isDragging = false;
          this.isMouseWheelScroll = false;
          this.panStartIndex = -1;
        });
        PanGesture.pop();
        Gesture.pop();
      }, Flex);
      this.observeComponentCreation2((u4, v4) => {
        Repeat(this.getItems(), this)
          .each((w4) => {
            this.observeComponentCreation2((b5, c5) => {
              Button.createWithChild({ type: ButtonType.Normal });
              Button.accessibilityGroup(true);
              Button.accessibilitySelected(this.isSelected(w4));
              Button.accessibilityText(this.getItemAccessibilityText(w4));
              Button.accessibilityDescription(
                this.getItemAccessibilityDescription(w4)
              );
              Button.accessibilityLevel(w4.item.accessibilityLevel);
              Button.backgroundColor(Color.Transparent);
              Button.borderRadius(this.getItemBorderRadius());
              Button.direction(this.languageDirection);
              Button.enabled(w4.item.enabled);
              Button.focusScopePriority(
                this.focusGroupId,
                this.getFocusPriority(w4)
              );
              Button.hoverEffect(HoverEffect.None);
              Button.layoutWeight(1);
              Button.padding(0);
              Button.scale(this.getItemScale(w4.index));
              Button.stateEffect(false);
              Button.onAreaChange((g5, h5) => {
                this.itemRects[w4.index] = {
                  size: {
                    width: h5.width,
                    height: h5.height,
                  },
                  position: {
                    x: h5.position.x,
                    y: h5.position.y,
                  },
                  globalPosition: {
                    x: h5.globalPosition.x,
                    y: h5.globalPosition.y,
                  },
                };
              });
              Gesture.create(GesturePriority.Low);
              TapGesture.create();
              TapGesture.onAction(() => {
                this.onItemClicked?.(w4.index);
                this.updateSelectedIndex(w4.index);
              });
              TapGesture.pop();
              Gesture.pop();
              Button.onTouch((f5) => {
                if (f5.type === TouchType.Down) {
                  if (this.isSelected(w4)) {
                    this.updateItemScale(0.95);
                  }
                  this.updateTouchPressedItemIndex(w4.index);
                } else if ([TouchType.Up, TouchType.Cancel].includes(f5.type)) {
                  this.updateItemScale(1);
                  this.updateTouchPressedItemIndex(-1);
                }
              });
              Button.onHover((e5) => {
                if (e5) {
                  this.updateHoveredItemIndex(w4.index);
                } else {
                  this.updateHoveredItemIndex(-1);
                }
              });
              Button.onMouse((d5) => {
                if (d5.action === MouseAction.Press) {
                  this.updateMousePressedItemIndex(w4.index);
                } else if (
                  [MouseAction.Release, MouseAction.CANCEL].includes(d5.action)
                ) {
                  this.updateMousePressedItemIndex(-1);
                }
              });
            }, Button);
            {
              this.observeComponentCreation2(
                (x4, y4) => {
                  if (y4) {
                    let z4 = new SegmentButtonV2ItemContent(
                      t4 ? t4 : this,
                      {
                        theme: this.theme,
                        item: w4.item,
                        selected: this.isSelected(w4),
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
                      x4,
                      () => {},
                      {
                        page: 'library/src/main/ets/components/MainPage.ets',
                        line: 577,
                        col: 13,
                      }
                    );
                    ViewV2.create(z4);
                    let a5 = () => {
                      return {
                        theme: this.theme,
                        item: w4.item,
                        selected: this.isSelected(w4),
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
                    z4.paramsGenerator_ = a5;
                  } else {
                    this.updateStateVarsOfChildByElmtId(x4, {
                      theme: this.theme,
                      item: w4.item,
                      selected: this.isSelected(w4),
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
          .key(generateUniqueKye(this.focusGroupId))
          .render(v4);
      }, Repeat);
      Flex.pop();
    };
    this.BackplateLayer = () => {
      const o4 =
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.length
          ? PUV2ViewBase.contextStack[PUV2ViewBase.contextStack.length - 1]
          : null;
      this.observeComponentCreation2((p4, q4) => {
        If.create();
        if (this.selectedItemRect) {
          this.ifElseBranchUpdateFunction(0, () => {
            this.observeComponentCreation2((r4, s4) => {
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
      const i4 =
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.length
          ? PUV2ViewBase.contextStack[PUV2ViewBase.contextStack.length - 1]
          : null;
      this.observeComponentCreation2((j4, k4) => {
        Repeat(this.getItemRects(), this)
          .each((l4) => {
            this.observeComponentCreation2((m4, n4) => {
              Stack.create();
              Stack.backgroundColor(this.getEffectBackgroundColor(l4));
              Stack.borderRadius(this.getItemBorderRadius());
              Stack.height(l4.item.size.height);
              Stack.position({
                x: l4.item.position.x,
                y: l4.item.position.y,
              });
              Stack.scale(this.getItemScale(l4.index));
              Stack.width(l4.item.size.width);
            }, Stack);
            Stack.pop();
          })
          .render(k4);
      }, Repeat);
    };
    this.initParam('items', d4 && 'items' in d4 ? d4.items : undefined);
    this.initParam(
      'selectedIndex',
      d4 && 'selectedIndex' in d4 ? d4.selectedIndex : undefined
    );
    this.$selectedIndex = '$selectedIndex' in d4 ? d4.$selectedIndex : () => {};
    this.initParam('theme', d4 && 'theme' in d4 ? d4.theme : undefined);
    this.onItemClicked = 'onItemClicked' in d4 ? d4.onItemClicked : () => {};
    this.initParam(
      'itemMinFontScale',
      d4 && 'itemMinFontScale' in d4 ? d4.itemMinFontScale : undefined
    );
    this.initParam(
      'itemMaxFontScale',
      d4 && 'itemMaxFontScale' in d4 ? d4.itemMaxFontScale : undefined
    );
    this.initParam(
      'itemSpace',
      d4 && 'itemSpace' in d4 ? d4.itemSpace : undefined
    );
    this.initParam(
      'itemFontColor',
      d4 && 'itemFontColor' in d4 ? d4.itemFontColor : undefined
    );
    this.initParam(
      'itemSelectedFontColor',
      d4 && 'itemSelectedFontColor' in d4 ? d4.itemSelectedFontColor : undefined
    );
    this.initParam(
      'itemFontSize',
      d4 && 'itemFontSize' in d4 ? d4.itemFontSize : undefined
    );
    this.initParam(
      'itemSelectedFontSize',
      d4 && 'itemSelectedFontSize' in d4 ? d4.itemSelectedFontSize : undefined
    );
    this.initParam(
      'itemFontWeight',
      d4 && 'itemFontWeight' in d4 ? d4.itemFontWeight : undefined
    );
    this.initParam(
      'itemSelectedFontWeight',
      d4 && 'itemSelectedFontWeight' in d4
        ? d4.itemSelectedFontWeight
        : undefined
    );
    this.initParam(
      'itemBorderRadius',
      d4 && 'itemBorderRadius' in d4 ? d4.itemBorderRadius : undefined
    );
    this.initParam(
      'itemSelectedBackgroundColor',
      d4 && 'itemSelectedBackgroundColor' in d4
        ? d4.itemSelectedBackgroundColor
        : undefined
    );
    this.initParam(
      'itemIconSize',
      d4 && 'itemIconSize' in d4 ? d4.itemIconSize : undefined
    );
    this.initParam(
      'itemIconFillColor',
      d4 && 'itemIconFillColor' in d4 ? d4.itemIconFillColor : undefined
    );
    this.initParam(
      'itemSelectedIconFillColor',
      d4 && 'itemSelectedIconFillColor' in d4
        ? d4.itemSelectedIconFillColor
        : undefined
    );
    this.initParam(
      'itemSymbolFontSize',
      d4 && 'itemSymbolFontSize' in d4 ? d4.itemSymbolFontSize : undefined
    );
    this.initParam(
      'itemSymbolFontColor',
      d4 && 'itemSymbolFontColor' in d4 ? d4.itemSymbolFontColor : undefined
    );
    this.initParam(
      'itemSelectedSymbolFontColor',
      d4 && 'itemSelectedSymbolFontColor' in d4
        ? d4.itemSelectedSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemMinHeight',
      d4 && 'itemMinHeight' in d4 ? d4.itemMinHeight : undefined
    );
    this.initParam(
      'itemPadding',
      d4 && 'itemPadding' in d4 ? d4.itemPadding : undefined
    );
    this.initParam(
      'itemShadow',
      d4 && 'itemShadow' in d4 ? d4.itemShadow : undefined
    );
    this.initParam(
      'buttonBackgroundColor',
      d4 && 'buttonBackgroundColor' in d4 ? d4.buttonBackgroundColor : undefined
    );
    this.initParam(
      'buttonBackgroundBlurStyle',
      d4 && 'buttonBackgroundBlurStyle' in d4
        ? d4.buttonBackgroundBlurStyle
        : undefined
    );
    this.initParam(
      'buttonBackgroundBlurStyleOptions',
      d4 && 'buttonBackgroundBlurStyleOptions' in d4
        ? d4.buttonBackgroundBlurStyleOptions
        : undefined
    );
    this.initParam(
      'buttonBackgroundEffect',
      d4 && 'buttonBackgroundEffect' in d4
        ? d4.buttonBackgroundEffect
        : undefined
    );
    this.initParam(
      'buttonBorderRadius',
      d4 && 'buttonBorderRadius' in d4 ? d4.buttonBorderRadius : undefined
    );
    this.initParam(
      'buttonMinHeight',
      d4 && 'buttonMinHeight' in d4 ? d4.buttonMinHeight : undefined
    );
    this.initParam(
      'buttonPadding',
      d4 && 'buttonPadding' in d4 ? d4.buttonPadding : undefined
    );
    this.initParam(
      'languageDirection',
      d4 && 'languageDirection' in d4 ? d4.languageDirection : undefined
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

  resetStateVarsOnReuse(b4) {
    this.resetParam('items', b4 && 'items' in b4 ? b4.items : undefined);
    this.resetParam(
      'selectedIndex',
      b4 && 'selectedIndex' in b4 ? b4.selectedIndex : undefined
    );
    this.$selectedIndex = '$selectedIndex' in b4 ? b4.$selectedIndex : () => {};
    this.resetParam('theme', b4 && 'theme' in b4 ? b4.theme : undefined);
    this.onItemClicked = 'onItemClicked' in b4 ? b4.onItemClicked : () => {};
    this.resetParam(
      'itemMinFontScale',
      b4 && 'itemMinFontScale' in b4 ? b4.itemMinFontScale : undefined
    );
    this.resetParam(
      'itemMaxFontScale',
      b4 && 'itemMaxFontScale' in b4 ? b4.itemMaxFontScale : undefined
    );
    this.resetParam(
      'itemSpace',
      b4 && 'itemSpace' in b4 ? b4.itemSpace : undefined
    );
    this.resetParam(
      'itemFontColor',
      b4 && 'itemFontColor' in b4 ? b4.itemFontColor : undefined
    );
    this.resetParam(
      'itemSelectedFontColor',
      b4 && 'itemSelectedFontColor' in b4 ? b4.itemSelectedFontColor : undefined
    );
    this.resetParam(
      'itemFontSize',
      b4 && 'itemFontSize' in b4 ? b4.itemFontSize : undefined
    );
    this.resetParam(
      'itemSelectedFontSize',
      b4 && 'itemSelectedFontSize' in b4 ? b4.itemSelectedFontSize : undefined
    );
    this.resetParam(
      'itemFontWeight',
      b4 && 'itemFontWeight' in b4 ? b4.itemFontWeight : undefined
    );
    this.resetParam(
      'itemSelectedFontWeight',
      b4 && 'itemSelectedFontWeight' in b4
        ? b4.itemSelectedFontWeight
        : undefined
    );
    this.resetParam(
      'itemBorderRadius',
      b4 && 'itemBorderRadius' in b4 ? b4.itemBorderRadius : undefined
    );
    this.resetParam(
      'itemSelectedBackgroundColor',
      b4 && 'itemSelectedBackgroundColor' in b4
        ? b4.itemSelectedBackgroundColor
        : undefined
    );
    this.resetParam(
      'itemIconSize',
      b4 && 'itemIconSize' in b4 ? b4.itemIconSize : undefined
    );
    this.resetParam(
      'itemIconFillColor',
      b4 && 'itemIconFillColor' in b4 ? b4.itemIconFillColor : undefined
    );
    this.resetParam(
      'itemSelectedIconFillColor',
      b4 && 'itemSelectedIconFillColor' in b4
        ? b4.itemSelectedIconFillColor
        : undefined
    );
    this.resetParam(
      'itemSymbolFontSize',
      b4 && 'itemSymbolFontSize' in b4 ? b4.itemSymbolFontSize : undefined
    );
    this.resetParam(
      'itemSymbolFontColor',
      b4 && 'itemSymbolFontColor' in b4 ? b4.itemSymbolFontColor : undefined
    );
    this.resetParam(
      'itemSelectedSymbolFontColor',
      b4 && 'itemSelectedSymbolFontColor' in b4
        ? b4.itemSelectedSymbolFontColor
        : undefined
    );
    this.resetParam(
      'itemMinHeight',
      b4 && 'itemMinHeight' in b4 ? b4.itemMinHeight : undefined
    );
    this.resetParam(
      'itemPadding',
      b4 && 'itemPadding' in b4 ? b4.itemPadding : undefined
    );
    this.resetParam(
      'itemShadow',
      b4 && 'itemShadow' in b4 ? b4.itemShadow : undefined
    );
    this.resetParam(
      'buttonBackgroundColor',
      b4 && 'buttonBackgroundColor' in b4 ? b4.buttonBackgroundColor : undefined
    );
    this.resetParam(
      'buttonBackgroundBlurStyle',
      b4 && 'buttonBackgroundBlurStyle' in b4
        ? b4.buttonBackgroundBlurStyle
        : undefined
    );
    this.resetParam(
      'buttonBackgroundBlurStyleOptions',
      b4 && 'buttonBackgroundBlurStyleOptions' in b4
        ? b4.buttonBackgroundBlurStyleOptions
        : undefined
    );
    this.resetParam(
      'buttonBackgroundEffect',
      b4 && 'buttonBackgroundEffect' in b4
        ? b4.buttonBackgroundEffect
        : undefined
    );
    this.resetParam(
      'buttonBorderRadius',
      b4 && 'buttonBorderRadius' in b4 ? b4.buttonBorderRadius : undefined
    );
    this.resetParam(
      'buttonMinHeight',
      b4 && 'buttonMinHeight' in b4 ? b4.buttonMinHeight : undefined
    );
    this.resetParam(
      'buttonPadding',
      b4 && 'buttonPadding' in b4 ? b4.buttonPadding : undefined
    );
    this.resetParam(
      'languageDirection',
      b4 && 'languageDirection' in b4 ? b4.languageDirection : undefined
    );
    this.itemRects = [];
    this.itemScale = 1;
    this.hoveredItemIndex = -1;
    this.mousePressedItemIndex = -1;
    this.touchPressedItemIndex = -1;
    this.resetComputed('normalizedSelectedIndex');
    this.resetComputed('selectedItemRect');
  }

  get normalizedSelectedIndex() {
    const a4 = this.getItems();
    return normalize(this.selectedIndex, 0, a4.length - 1);
  }

  get selectedItemRect() {
    return this.itemRects[this.normalizedSelectedIndex];
  }

  getFocusPriority(z3) {
    return this.normalizedSelectedIndex === z3.index
      ? FocusPriority.PREVIOUS
      : FocusPriority.AUTO;
  }

  isItemEnabled(x3) {
    const y3 = this.getItems();
    if (x3 < 0 || x3 >= y3.length) {
      return false;
    }
    return y3[x3].enabled;
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
    this.observeComponentCreation2((v3, w3) => {
      Stack.create();
      Stack.backgroundColor(this.getButtonBackgroundColor());
      Stack.backgroundEffect(this.buttonBackgroundEffect, { disableSystemAdaptation: true });
      Stack.borderRadius(this.getButtonBorderRadius());
      Stack.clip(false);
      Stack.constraintSize({
        minWidth: '100%',
        minHeight: this.getButtonMinHeight(),
      });
      Stack.direction(this.languageDirection);
    }, Stack);
    this.observeComponentCreation2((t3, u3) => {
      Stack.create();
      Stack.borderRadius(this.getButtonBorderRadius());
      Stack.backgroundBlurStyle(
        this.getButtonBackgroundBlurStyle(),
        this.getButtonBackgroundBlurStyleOptions(),
        { disableSystemAdaptation: true }
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
    return this.items ?? EMPTY_ITEMS;
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

  getItemScale(q3) {
    const r3 = this.isPressed(q3);
    const s3 = r3 ? 0.95 : 1;
    return { x: s3, y: s3 };
  }

  isPressed(p3) {
    return this.mousePressedItemIndex === p3;
  }

  updateHoveredItemIndex(o3) {
    if (o3 === this.hoveredItemIndex) {
      return;
    }
    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
      this.hoveredItemIndex = o3;
    });
  }

  updateMousePressedItemIndex(n3) {
    if (n3 === this.mousePressedItemIndex) {
      return;
    }
    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
      this.mousePressedItemIndex = n3;
    });
  }

  updateTouchPressedItemIndex(m3) {
    if (m3 === this.touchPressedItemIndex) {
      return;
    }
    Context.animateTo({ duration: 250, curve: Curve.Friction }, () => {
      this.touchPressedItemIndex = m3;
    });
  }

  isRTL() {
    if (this.languageDirection || this.languageDirection === Direction.Auto) {
      return i18n.isRTL(i18n.System.getSystemLanguage());
    }
    return this.languageDirection === Direction.Rtl;
  }

  getEffectBackgroundColor(l3) {
    if (l3.index === this.mousePressedItemIndex) {
      return {
        id: -1,
        type: 10001,
        params: ['sys.color.interactive_click'],
        bundleName: '__harDefaultBundleName__',
        moduleName: '__harDefaultModuleName__',
      };
    }
    if (l3.index === this.hoveredItemIndex) {
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
    if (
      this.itemBorderRadius &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemBorderRadius)
    ) {
      return LengthMetricsUtils.getInstance().stringify(this.itemBorderRadius);
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
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemSpace)
    ) {
      return this.itemSpace;
    }
    return this.theme.itemSpace;
  }

  getIndexByPosition(h3, i3) {
    let j3 = 0;
    while (j3 < this.itemRects.length) {
      const k3 = this.itemRects[j3];
      if (this.isPointOnRect(h3, i3, k3)) {
        return j3;
      }
      ++j3;
    }
    return -1;
  }

  isPointOnRect(e3, f3, g3) {
    return (
      e3 >= g3.globalPosition.x &&
      e3 <= g3.globalPosition.x + g3.size.width &&
      f3 >= g3.globalPosition.y &&
      f3 <= g3.globalPosition.y + g3.size.height
    );
  }

  updateSelectedIndex(d3) {
    if (!this.isItemEnabled(d3) || d3 === this.selectedIndex) {
      return;
    }
    this.getUIContext().animateTo(
      { curve: curves.springMotion(0.347, 0.99) },
      () => {
        this.$selectedIndex?.(d3);
      }
    );
  }

  updateItemScale(c3) {
    if (this.itemScale === c3) {
      return;
    }
    this.getUIContext().animateTo(
      { curve: curves.interpolatingSpring(10, 1, 410, 38) },
      () => {
        this.itemScale = c3;
      }
    );
  }

  getItemAccessibilityDescription(b3) {
    return b3.item.accessibilityDescription;
  }

  getItemAccessibilityText(a3) {
    return a3.item.accessibilityText;
  }

  isSelected(z2) {
    return z2.index === this.normalizedSelectedIndex;
  }

  getButtonPadding() {
    if (
      this.buttonPadding &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.buttonPadding)
    ) {
      return LengthMetricsUtils.getInstance().stringify(this.buttonPadding);
    }
    return this.theme.buttonPadding;
  }

  getButtonBorderRadius() {
    if (
      this.buttonBorderRadius &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.buttonBorderRadius)
    ) {
      return LengthMetricsUtils.getInstance().stringify(
        this.buttonBorderRadius
      );
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
    if (
      this.buttonMinHeight &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.buttonMinHeight)
    ) {
      return LengthMetricsUtils.getInstance().stringify(this.buttonMinHeight);
    }
    const y2 = this.getItems();
    return y2.hasHybrid
      ? this.theme.hybridButtonMinHeight
      : this.theme.buttonMinHeight;
  }

  updateStateVars(x2) {
    if (x2 === undefined) {
      return;
    }
    if ('items' in x2) {
      this.updateParam('items', x2.items);
    }
    if ('selectedIndex' in x2) {
      this.updateParam('selectedIndex', x2.selectedIndex);
    }
    if ('theme' in x2) {
      this.updateParam('theme', x2.theme);
    }
    if ('itemMinFontScale' in x2) {
      this.updateParam('itemMinFontScale', x2.itemMinFontScale);
    }
    if ('itemMaxFontScale' in x2) {
      this.updateParam('itemMaxFontScale', x2.itemMaxFontScale);
    }
    if ('itemSpace' in x2) {
      this.updateParam('itemSpace', x2.itemSpace);
    }
    if ('itemFontColor' in x2) {
      this.updateParam('itemFontColor', x2.itemFontColor);
    }
    if ('itemSelectedFontColor' in x2) {
      this.updateParam('itemSelectedFontColor', x2.itemSelectedFontColor);
    }
    if ('itemFontSize' in x2) {
      this.updateParam('itemFontSize', x2.itemFontSize);
    }
    if ('itemSelectedFontSize' in x2) {
      this.updateParam('itemSelectedFontSize', x2.itemSelectedFontSize);
    }
    if ('itemFontWeight' in x2) {
      this.updateParam('itemFontWeight', x2.itemFontWeight);
    }
    if ('itemSelectedFontWeight' in x2) {
      this.updateParam('itemSelectedFontWeight', x2.itemSelectedFontWeight);
    }
    if ('itemBorderRadius' in x2) {
      this.updateParam('itemBorderRadius', x2.itemBorderRadius);
    }
    if ('itemSelectedBackgroundColor' in x2) {
      this.updateParam(
        'itemSelectedBackgroundColor',
        x2.itemSelectedBackgroundColor
      );
    }
    if ('itemIconSize' in x2) {
      this.updateParam('itemIconSize', x2.itemIconSize);
    }
    if ('itemIconFillColor' in x2) {
      this.updateParam('itemIconFillColor', x2.itemIconFillColor);
    }
    if ('itemSelectedIconFillColor' in x2) {
      this.updateParam(
        'itemSelectedIconFillColor',
        x2.itemSelectedIconFillColor
      );
    }
    if ('itemSymbolFontSize' in x2) {
      this.updateParam('itemSymbolFontSize', x2.itemSymbolFontSize);
    }
    if ('itemSymbolFontColor' in x2) {
      this.updateParam('itemSymbolFontColor', x2.itemSymbolFontColor);
    }
    if ('itemSelectedSymbolFontColor' in x2) {
      this.updateParam(
        'itemSelectedSymbolFontColor',
        x2.itemSelectedSymbolFontColor
      );
    }
    if ('itemMinHeight' in x2) {
      this.updateParam('itemMinHeight', x2.itemMinHeight);
    }
    if ('itemPadding' in x2) {
      this.updateParam('itemPadding', x2.itemPadding);
    }
    if ('itemShadow' in x2) {
      this.updateParam('itemShadow', x2.itemShadow);
    }
    if ('buttonBackgroundColor' in x2) {
      this.updateParam('buttonBackgroundColor', x2.buttonBackgroundColor);
    }
    if ('buttonBackgroundBlurStyle' in x2) {
      this.updateParam(
        'buttonBackgroundBlurStyle',
        x2.buttonBackgroundBlurStyle
      );
    }
    if ('buttonBackgroundBlurStyleOptions' in x2) {
      this.updateParam(
        'buttonBackgroundBlurStyleOptions',
        x2.buttonBackgroundBlurStyleOptions
      );
    }
    if ('buttonBackgroundEffect' in x2) {
      this.updateParam('buttonBackgroundEffect', x2.buttonBackgroundEffect);
    }
    if ('buttonBorderRadius' in x2) {
      this.updateParam('buttonBorderRadius', x2.buttonBorderRadius);
    }
    if ('buttonMinHeight' in x2) {
      this.updateParam('buttonMinHeight', x2.buttonMinHeight);
    }
    if ('buttonPadding' in x2) {
      this.updateParam('buttonPadding', x2.buttonPadding);
    }
    if ('languageDirection' in x2) {
      this.updateParam('languageDirection', x2.languageDirection);
    }
  }

  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}

__decorate([Param], SimpleSegmentButtonV2.prototype, 'items', void 0);
__decorate([Param], SimpleSegmentButtonV2.prototype, 'selectedIndex', void 0);
__decorate([Event], SimpleSegmentButtonV2.prototype, '$selectedIndex', void 0);
__decorate([Param], SimpleSegmentButtonV2.prototype, 'theme', void 0);
__decorate([Event], SimpleSegmentButtonV2.prototype, 'onItemClicked', void 0);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'itemMinFontScale',
  void 0
);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'itemMaxFontScale',
  void 0
);
__decorate([Param], SimpleSegmentButtonV2.prototype, 'itemSpace', void 0);
__decorate([Param], SimpleSegmentButtonV2.prototype, 'itemFontColor', void 0);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'itemSelectedFontColor',
  void 0
);
__decorate([Param], SimpleSegmentButtonV2.prototype, 'itemFontSize', void 0);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'itemSelectedFontSize',
  void 0
);
__decorate([Param], SimpleSegmentButtonV2.prototype, 'itemFontWeight', void 0);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'itemSelectedFontWeight',
  void 0
);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'itemBorderRadius',
  void 0
);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'itemSelectedBackgroundColor',
  void 0
);
__decorate([Param], SimpleSegmentButtonV2.prototype, 'itemIconSize', void 0);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'itemIconFillColor',
  void 0
);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'itemSelectedIconFillColor',
  void 0
);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'itemSymbolFontSize',
  void 0
);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'itemSymbolFontColor',
  void 0
);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'itemSelectedSymbolFontColor',
  void 0
);
__decorate([Param], SimpleSegmentButtonV2.prototype, 'itemMinHeight', void 0);
__decorate([Param], SimpleSegmentButtonV2.prototype, 'itemPadding', void 0);
__decorate([Param], SimpleSegmentButtonV2.prototype, 'itemShadow', void 0);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'buttonBackgroundColor',
  void 0
);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'buttonBackgroundBlurStyle',
  void 0
);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'buttonBackgroundBlurStyleOptions',
  void 0
);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'buttonBackgroundEffect',
  void 0
);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'buttonBorderRadius',
  void 0
);
__decorate([Param], SimpleSegmentButtonV2.prototype, 'buttonMinHeight', void 0);
__decorate([Param], SimpleSegmentButtonV2.prototype, 'buttonPadding', void 0);
__decorate(
  [Param],
  SimpleSegmentButtonV2.prototype,
  'languageDirection',
  void 0
);
__decorate([Local], SimpleSegmentButtonV2.prototype, 'itemRects', void 0);
__decorate([Local], SimpleSegmentButtonV2.prototype, 'itemScale', void 0);
__decorate(
  [Local],
  SimpleSegmentButtonV2.prototype,
  'hoveredItemIndex',
  void 0
);
__decorate(
  [Local],
  SimpleSegmentButtonV2.prototype,
  'mousePressedItemIndex',
  void 0
);
__decorate(
  [Local],
  SimpleSegmentButtonV2.prototype,
  'touchPressedItemIndex',
  void 0
);
__decorate(
  [Computed],
  SimpleSegmentButtonV2.prototype,
  'normalizedSelectedIndex',
  null
);
__decorate(
  [Computed],
  SimpleSegmentButtonV2.prototype,
  'selectedItemRect',
  null
);
const multiplyCapsuleTheme = {
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
  hybridItemMinHeight: {
    id: -1,
    type: 10002,
    params: ['sys.float.segment_button_v2_multi_doubleline_height'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
  },
  itemMaxFontScale: SMALLEST_MAX_FONT_SCALE,
  itemMaxFontScaleSmallest: SMALLEST_MAX_FONT_SCALE,
  itemMaxFontScaleLargest: LARGEST_MAX_FONT_SCALE,
  itemMinFontScale: SMALLEST_MIN_FONT_SCALE,
  itemMinFontScaleSmallest: SMALLEST_MIN_FONT_SCALE,
  itemMinFontScaleLargest: LARGEST_MIN_FONT_SCALE,
};

export class MultiCapsuleSegmentButtonV2 extends ViewV2 {
  constructor(r2, s2, t2, u2 = -1, v2, w2) {
    super(r2, u2, w2);
    this.initParam('items', s2 && 'items' in s2 ? s2.items : undefined);
    this.initParam(
      'selectedIndexes',
      s2 && 'selectedIndexes' in s2 ? s2.selectedIndexes : undefined
    );
    this.$selectedIndexes =
      '$selectedIndexes' in s2 ? s2.$selectedIndexes : () => {};
    this.onItemClicked = 'onItemClicked' in s2 ? s2.onItemClicked : () => {};
    this.initParam(
      'itemMinFontScale',
      s2 && 'itemMinFontScale' in s2 ? s2.itemMinFontScale : undefined
    );
    this.initParam(
      'itemMaxFontScale',
      s2 && 'itemMaxFontScale' in s2 ? s2.itemMaxFontScale : undefined
    );
    this.initParam(
      'itemSpace',
      s2 && 'itemSpace' in s2 ? s2.itemSpace : undefined
    );
    this.initParam(
      'itemFontColor',
      s2 && 'itemFontColor' in s2 ? s2.itemFontColor : undefined
    );
    this.initParam(
      'itemSelectedFontColor',
      s2 && 'itemSelectedFontColor' in s2 ? s2.itemSelectedFontColor : undefined
    );
    this.initParam(
      'itemFontSize',
      s2 && 'itemFontSize' in s2 ? s2.itemFontSize : undefined
    );
    this.initParam(
      'itemSelectedFontSize',
      s2 && 'itemSelectedFontSize' in s2 ? s2.itemSelectedFontSize : undefined
    );
    this.initParam(
      'itemFontWeight',
      s2 && 'itemFontWeight' in s2 ? s2.itemFontWeight : undefined
    );
    this.initParam(
      'itemSelectedFontWeight',
      s2 && 'itemSelectedFontWeight' in s2
        ? s2.itemSelectedFontWeight
        : undefined
    );
    this.initParam(
      'itemBorderRadius',
      s2 && 'itemBorderRadius' in s2 ? s2.itemBorderRadius : undefined
    );
    this.initParam(
      'itemBackgroundColor',
      s2 && 'itemBackgroundColor' in s2 ? s2.itemBackgroundColor : undefined
    );
    this.initParam(
      'itemBackgroundEffect',
      s2 && 'itemBackgroundEffect' in s2 ? s2.itemBackgroundEffect : undefined
    );
    this.initParam(
      'itemBackgroundBlurStyle',
      s2 && 'itemBackgroundBlurStyle' in s2
        ? s2.itemBackgroundBlurStyle
        : undefined
    );
    this.initParam(
      'itemBackgroundBlurStyleOptions',
      s2 && 'itemBackgroundBlurStyleOptions' in s2
        ? s2.itemBackgroundBlurStyleOptions
        : undefined
    );
    this.initParam(
      'itemSelectedBackgroundColor',
      s2 && 'itemSelectedBackgroundColor' in s2
        ? s2.itemSelectedBackgroundColor
        : undefined
    );
    this.initParam(
      'itemIconSize',
      s2 && 'itemIconSize' in s2 ? s2.itemIconSize : undefined
    );
    this.initParam(
      'itemIconFillColor',
      s2 && 'itemIconFillColor' in s2 ? s2.itemIconFillColor : undefined
    );
    this.initParam(
      'itemSelectedIconFillColor',
      s2 && 'itemSelectedIconFillColor' in s2
        ? s2.itemSelectedIconFillColor
        : undefined
    );
    this.initParam(
      'itemSymbolFontSize',
      s2 && 'itemSymbolFontSize' in s2 ? s2.itemSymbolFontSize : undefined
    );
    this.initParam(
      'itemSymbolFontColor',
      s2 && 'itemSymbolFontColor' in s2 ? s2.itemSymbolFontColor : undefined
    );
    this.initParam(
      'itemSelectedSymbolFontColor',
      s2 && 'itemSelectedSymbolFontColor' in s2
        ? s2.itemSelectedSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemMinHeight',
      s2 && 'itemMinHeight' in s2 ? s2.itemMinHeight : undefined
    );
    this.initParam(
      'itemPadding',
      s2 && 'itemPadding' in s2 ? s2.itemPadding : undefined
    );
    this.initParam(
      'languageDirection',
      s2 && 'languageDirection' in s2 ? s2.languageDirection : undefined
    );
    this.theme = multiplyCapsuleTheme;
    this.focusGroupId = util.generateRandomUUID();
    this.finalizeConstruction();
  }

  resetStateVarsOnReuse(q2) {
    this.resetParam('items', q2 && 'items' in q2 ? q2.items : undefined);
    this.resetParam(
      'selectedIndexes',
      q2 && 'selectedIndexes' in q2 ? q2.selectedIndexes : undefined
    );
    this.$selectedIndexes =
      '$selectedIndexes' in q2 ? q2.$selectedIndexes : () => {};
    this.onItemClicked = 'onItemClicked' in q2 ? q2.onItemClicked : () => {};
    this.resetParam(
      'itemMinFontScale',
      q2 && 'itemMinFontScale' in q2 ? q2.itemMinFontScale : undefined
    );
    this.resetParam(
      'itemMaxFontScale',
      q2 && 'itemMaxFontScale' in q2 ? q2.itemMaxFontScale : undefined
    );
    this.resetParam(
      'itemSpace',
      q2 && 'itemSpace' in q2 ? q2.itemSpace : undefined
    );
    this.resetParam(
      'itemFontColor',
      q2 && 'itemFontColor' in q2 ? q2.itemFontColor : undefined
    );
    this.resetParam(
      'itemSelectedFontColor',
      q2 && 'itemSelectedFontColor' in q2 ? q2.itemSelectedFontColor : undefined
    );
    this.resetParam(
      'itemFontSize',
      q2 && 'itemFontSize' in q2 ? q2.itemFontSize : undefined
    );
    this.resetParam(
      'itemSelectedFontSize',
      q2 && 'itemSelectedFontSize' in q2 ? q2.itemSelectedFontSize : undefined
    );
    this.resetParam(
      'itemFontWeight',
      q2 && 'itemFontWeight' in q2 ? q2.itemFontWeight : undefined
    );
    this.resetParam(
      'itemSelectedFontWeight',
      q2 && 'itemSelectedFontWeight' in q2
        ? q2.itemSelectedFontWeight
        : undefined
    );
    this.resetParam(
      'itemBorderRadius',
      q2 && 'itemBorderRadius' in q2 ? q2.itemBorderRadius : undefined
    );
    this.resetParam(
      'itemBackgroundColor',
      q2 && 'itemBackgroundColor' in q2 ? q2.itemBackgroundColor : undefined
    );
    this.resetParam(
      'itemBackgroundEffect',
      q2 && 'itemBackgroundEffect' in q2 ? q2.itemBackgroundEffect : undefined
    );
    this.resetParam(
      'itemBackgroundBlurStyle',
      q2 && 'itemBackgroundBlurStyle' in q2
        ? q2.itemBackgroundBlurStyle
        : undefined
    );
    this.resetParam(
      'itemBackgroundBlurStyleOptions',
      q2 && 'itemBackgroundBlurStyleOptions' in q2
        ? q2.itemBackgroundBlurStyleOptions
        : undefined
    );
    this.resetParam(
      'itemSelectedBackgroundColor',
      q2 && 'itemSelectedBackgroundColor' in q2
        ? q2.itemSelectedBackgroundColor
        : undefined
    );
    this.resetParam(
      'itemIconSize',
      q2 && 'itemIconSize' in q2 ? q2.itemIconSize : undefined
    );
    this.resetParam(
      'itemIconFillColor',
      q2 && 'itemIconFillColor' in q2 ? q2.itemIconFillColor : undefined
    );
    this.resetParam(
      'itemSelectedIconFillColor',
      q2 && 'itemSelectedIconFillColor' in q2
        ? q2.itemSelectedIconFillColor
        : undefined
    );
    this.resetParam(
      'itemSymbolFontSize',
      q2 && 'itemSymbolFontSize' in q2 ? q2.itemSymbolFontSize : undefined
    );
    this.resetParam(
      'itemSymbolFontColor',
      q2 && 'itemSymbolFontColor' in q2 ? q2.itemSymbolFontColor : undefined
    );
    this.resetParam(
      'itemSelectedSymbolFontColor',
      q2 && 'itemSelectedSymbolFontColor' in q2
        ? q2.itemSelectedSymbolFontColor
        : undefined
    );
    this.resetParam(
      'itemMinHeight',
      q2 && 'itemMinHeight' in q2 ? q2.itemMinHeight : undefined
    );
    this.resetParam(
      'itemPadding',
      q2 && 'itemPadding' in q2 ? q2.itemPadding : undefined
    );
    this.resetParam(
      'languageDirection',
      q2 && 'languageDirection' in q2 ? q2.languageDirection : undefined
    );
  }

  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((o2, p2) => {
      Flex.create({
        alignItems: ItemAlign.Stretch,
        space: { main: this.getItemSpace() },
      });
      Flex.clip(false);
      Flex.direction(this.languageDirection);
      Flex.focusScopeId(this.focusGroupId, true);
    }, Flex);
    this.observeComponentCreation2((y1, z1) => {
      Repeat(this.getItems(), this)
        .each((a2) => {
          this.observeComponentCreation2((h2, i2) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.accessibilityGroup(true);
            Button.accessibilityChecked(this.isSelected(a2));
            Button.accessibilityText(this.getItemAccessibilityText(a2));
            Button.accessibilityDescription(
              this.getItemAccessibilityDescription(a2)
            );
            Button.accessibilityLevel(a2.item.accessibilityLevel);
            Button.backgroundColor(this.getItemBackgroundColor(a2));
            Button.backgroundEffect(this.itemBackgroundEffect, { disableSystemAdaptation: true });
            Button.borderRadius(this.getItemButtonBorderRadius(a2));
            Button.constraintSize({ minHeight: this.getItemMinHeight() });
            Button.direction(this.languageDirection);
            Button.enabled(a2.item.enabled);
            Button.focusScopePriority(
              this.focusGroupId,
              this.getFocusPriority(a2)
            );
            Button.layoutWeight(1);
            Button.padding(0);
            Button.onClick(() => {
              this.onItemClicked?.(a2.index);
              let j2;
              const k2 = this.getItems();
              const l2 = this.selectedIndexes ?? [];
              if (this.isSelected(a2)) {
                j2 = l2.filter((n2) => {
                  if (n2 < 0 || n2 > k2.length - 1) {
                    return false;
                  }
                  return n2 !== a2.index;
                });
              } else {
                j2 = l2
                  .filter((m2) => m2 >= 0 && m2 <= k2.length - 1)
                  .concat(a2.index);
              }
              this.$selectedIndexes(j2);
            });
          }, Button);
          this.observeComponentCreation2((f2, g2) => {
            __Common__.create();
            __Common__.borderRadius(this.getItemButtonBorderRadius(a2));
            __Common__.backgroundBlurStyle(
              this.getItemBackgroundBlurStyle(),
              this.getItemBackgroundBlurStyleOptions(),
              { disableSystemAdaptation: true }
            );
            __Common__.direction(this.languageDirection);
          }, __Common__);
          {
            this.observeComponentCreation2(
              (b2, c2) => {
                if (c2) {
                  let d2 = new SegmentButtonV2ItemContent(
                    this,
                    {
                      theme: this.theme,
                      item: a2.item,
                      selected: this.isSelected(a2),
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
                    b2,
                    () => {},
                    {
                      page: 'library/src/main/ets/components/MainPage.ets',
                      line: 1108,
                      col: 13,
                    }
                  );
                  ViewV2.create(d2);
                  let e2 = () => {
                    return {
                      theme: this.theme,
                      item: a2.item,
                      selected: this.isSelected(a2),
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
                  d2.paramsGenerator_ = e2;
                } else {
                  this.updateStateVarsOfChildByElmtId(b2, {
                    theme: this.theme,
                    item: a2.item,
                    selected: this.isSelected(a2),
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
        .key(generateUniqueKye(this.focusGroupId))
        .render(z1);
    }, Repeat);
    Flex.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }

  getFocusPriority(x1) {
    return Math.min(...this.selectedIndexes) === x1.index
      ? FocusPriority.PREVIOUS
      : FocusPriority.AUTO;
  }

  getItems() {
    return this.items ?? EMPTY_ITEMS;
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

  getItemAccessibilityDescription(w1) {
    return w1.item.accessibilityDescription;
  }

  getItemAccessibilityText(v1) {
    return v1.item.accessibilityText;
  }

  getItemSpace() {
    if (
      this.itemSpace &&
      this.itemSpace.unit !== LengthUnit.PERCENT &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemSpace)
    ) {
      return this.itemSpace;
    }
    return this.theme.itemSpace;
  }

  getItemMinHeight() {
    if (
      this.itemMinHeight &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemMinHeight)
    ) {
      return LengthMetricsUtils.getInstance().stringify(this.itemMinHeight);
    }
    return this.theme.itemMinHeight;
  }

  getItemBackgroundColor(u1) {
    if (this.isSelected(u1)) {
      return (
        this.itemSelectedBackgroundColor?.color ??
        this.theme.itemSelectedBackgroundColor
      );
    }
    return this.itemBackgroundColor?.color ?? this.theme.itemBackgroundColor;
  }

  isSelected(s1) {
    const t1 = this.selectedIndexes ?? [];
    return t1.includes(s1.index);
  }

  getItemButtonBorderRadius(m1) {
    const n1 = this.getItems();
    const o1 = LengthMetrics.vp(0);
    const p1 = {
      topStart: o1,
      bottomStart: o1,
      topEnd: o1,
      bottomEnd: o1,
    };
    if (m1.index === 0) {
      const r1 =
        this.itemBorderRadius ??
        LengthMetrics.resource(this.theme.itemBorderRadius);
      p1.topStart = r1;
      p1.bottomStart = r1;
    }
    if (m1.index === n1.length - 1) {
      const q1 =
        this.itemBorderRadius ??
        LengthMetrics.resource(this.theme.itemBorderRadius);
      p1.topEnd = q1;
      p1.bottomEnd = q1;
    }
    return p1;
  }

  updateStateVars(l1) {
    if (l1 === undefined) {
      return;
    }
    if ('items' in l1) {
      this.updateParam('items', l1.items);
    }
    if ('selectedIndexes' in l1) {
      this.updateParam('selectedIndexes', l1.selectedIndexes);
    }
    if ('itemMinFontScale' in l1) {
      this.updateParam('itemMinFontScale', l1.itemMinFontScale);
    }
    if ('itemMaxFontScale' in l1) {
      this.updateParam('itemMaxFontScale', l1.itemMaxFontScale);
    }
    if ('itemSpace' in l1) {
      this.updateParam('itemSpace', l1.itemSpace);
    }
    if ('itemFontColor' in l1) {
      this.updateParam('itemFontColor', l1.itemFontColor);
    }
    if ('itemSelectedFontColor' in l1) {
      this.updateParam('itemSelectedFontColor', l1.itemSelectedFontColor);
    }
    if ('itemFontSize' in l1) {
      this.updateParam('itemFontSize', l1.itemFontSize);
    }
    if ('itemSelectedFontSize' in l1) {
      this.updateParam('itemSelectedFontSize', l1.itemSelectedFontSize);
    }
    if ('itemFontWeight' in l1) {
      this.updateParam('itemFontWeight', l1.itemFontWeight);
    }
    if ('itemSelectedFontWeight' in l1) {
      this.updateParam('itemSelectedFontWeight', l1.itemSelectedFontWeight);
    }
    if ('itemBorderRadius' in l1) {
      this.updateParam('itemBorderRadius', l1.itemBorderRadius);
    }
    if ('itemBackgroundColor' in l1) {
      this.updateParam('itemBackgroundColor', l1.itemBackgroundColor);
    }
    if ('itemBackgroundEffect' in l1) {
      this.updateParam('itemBackgroundEffect', l1.itemBackgroundEffect);
    }
    if ('itemBackgroundBlurStyle' in l1) {
      this.updateParam('itemBackgroundBlurStyle', l1.itemBackgroundBlurStyle);
    }
    if ('itemBackgroundBlurStyleOptions' in l1) {
      this.updateParam(
        'itemBackgroundBlurStyleOptions',
        l1.itemBackgroundBlurStyleOptions
      );
    }
    if ('itemSelectedBackgroundColor' in l1) {
      this.updateParam(
        'itemSelectedBackgroundColor',
        l1.itemSelectedBackgroundColor
      );
    }
    if ('itemIconSize' in l1) {
      this.updateParam('itemIconSize', l1.itemIconSize);
    }
    if ('itemIconFillColor' in l1) {
      this.updateParam('itemIconFillColor', l1.itemIconFillColor);
    }
    if ('itemSelectedIconFillColor' in l1) {
      this.updateParam(
        'itemSelectedIconFillColor',
        l1.itemSelectedIconFillColor
      );
    }
    if ('itemSymbolFontSize' in l1) {
      this.updateParam('itemSymbolFontSize', l1.itemSymbolFontSize);
    }
    if ('itemSymbolFontColor' in l1) {
      this.updateParam('itemSymbolFontColor', l1.itemSymbolFontColor);
    }
    if ('itemSelectedSymbolFontColor' in l1) {
      this.updateParam(
        'itemSelectedSymbolFontColor',
        l1.itemSelectedSymbolFontColor
      );
    }
    if ('itemMinHeight' in l1) {
      this.updateParam('itemMinHeight', l1.itemMinHeight);
    }
    if ('itemPadding' in l1) {
      this.updateParam('itemPadding', l1.itemPadding);
    }
    if ('languageDirection' in l1) {
      this.updateParam('languageDirection', l1.languageDirection);
    }
  }

  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
__decorate([Param], MultiCapsuleSegmentButtonV2.prototype, 'items', void 0);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'selectedIndexes',
  void 0
);
__decorate(
  [Event],
  MultiCapsuleSegmentButtonV2.prototype,
  '$selectedIndexes',
  void 0
);
__decorate(
  [Event],
  MultiCapsuleSegmentButtonV2.prototype,
  'onItemClicked',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemMinFontScale',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemMaxFontScale',
  void 0
);
__decorate([Param], MultiCapsuleSegmentButtonV2.prototype, 'itemSpace', void 0);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemFontColor',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSelectedFontColor',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemFontSize',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSelectedFontSize',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemFontWeight',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSelectedFontWeight',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemBorderRadius',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemBackgroundColor',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemBackgroundEffect',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemBackgroundBlurStyle',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemBackgroundBlurStyleOptions',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSelectedBackgroundColor',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemIconSize',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemIconFillColor',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSelectedIconFillColor',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSymbolFontSize',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSymbolFontColor',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemSelectedSymbolFontColor',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemMinHeight',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'itemPadding',
  void 0
);
__decorate(
  [Param],
  MultiCapsuleSegmentButtonV2.prototype,
  'languageDirection',
  void 0
);

class SegmentButtonV2ItemContent extends ViewV2 {
  constructor(f1, g1, h1, i1 = -1, j1, k1) {
    super(f1, i1, k1);
    this.initParam(
      'hasHybrid',
      g1 && 'hasHybrid' in g1 ? g1.hasHybrid : undefined
    );
    this.initParam('item', g1 && 'item' in g1 ? g1.item : undefined);
    this.initParam(
      'selected',
      g1 && 'selected' in g1 ? g1.selected : undefined
    );
    this.initParam('theme', g1 && 'theme' in g1 ? g1.theme : undefined);
    this.initParam(
      'itemMinFontScale',
      g1 && 'itemMinFontScale' in g1 ? g1.itemMinFontScale : undefined
    );
    this.initParam(
      'itemMaxFontScale',
      g1 && 'itemMaxFontScale' in g1 ? g1.itemMaxFontScale : undefined
    );
    this.initParam(
      'itemFontColor',
      g1 && 'itemFontColor' in g1 ? g1.itemFontColor : undefined
    );
    this.initParam(
      'itemSelectedFontColor',
      g1 && 'itemSelectedFontColor' in g1 ? g1.itemSelectedFontColor : undefined
    );
    this.initParam(
      'itemFontSize',
      g1 && 'itemFontSize' in g1 ? g1.itemFontSize : undefined
    );
    this.initParam(
      'itemSelectedFontSize',
      g1 && 'itemSelectedFontSize' in g1 ? g1.itemSelectedFontSize : undefined
    );
    this.initParam(
      'itemFontWeight',
      g1 && 'itemFontWeight' in g1 ? g1.itemFontWeight : undefined
    );
    this.initParam(
      'itemSelectedFontWeight',
      g1 && 'itemSelectedFontWeight' in g1
        ? g1.itemSelectedFontWeight
        : undefined
    );
    this.initParam(
      'itemIconSize',
      g1 && 'itemIconSize' in g1 ? g1.itemIconSize : undefined
    );
    this.initParam(
      'itemIconFillColor',
      g1 && 'itemIconFillColor' in g1 ? g1.itemIconFillColor : undefined
    );
    this.initParam(
      'itemSelectedIconFillColor',
      g1 && 'itemSelectedIconFillColor' in g1
        ? g1.itemSelectedIconFillColor
        : undefined
    );
    this.initParam(
      'itemSymbolFontSize',
      g1 && 'itemSymbolFontSize' in g1 ? g1.itemSymbolFontSize : undefined
    );
    this.initParam(
      'itemSymbolFontColor',
      g1 && 'itemSymbolFontColor' in g1 ? g1.itemSymbolFontColor : undefined
    );
    this.initParam(
      'itemSelectedSymbolFontColor',
      g1 && 'itemSelectedSymbolFontColor' in g1
        ? g1.itemSelectedSymbolFontColor
        : undefined
    );
    this.initParam(
      'itemMinHeight',
      g1 && 'itemMinHeight' in g1 ? g1.itemMinHeight : undefined
    );
    this.initParam(
      'itemPadding',
      g1 && 'itemPadding' in g1 ? g1.itemPadding : undefined
    );
    this.initParam(
      'languageDirection',
      g1 && 'languageDirection' in g1 ? g1.languageDirection : undefined
    );
    this.finalizeConstruction();
  }

  resetStateVarsOnReuse(e1) {
    this.resetParam(
      'hasHybrid',
      e1 && 'hasHybrid' in e1 ? e1.hasHybrid : undefined
    );
    this.resetParam('item', e1 && 'item' in e1 ? e1.item : undefined);
    this.resetParam(
      'selected',
      e1 && 'selected' in e1 ? e1.selected : undefined
    );
    this.resetParam('theme', e1 && 'theme' in e1 ? e1.theme : undefined);
    this.resetParam(
      'itemMinFontScale',
      e1 && 'itemMinFontScale' in e1 ? e1.itemMinFontScale : undefined
    );
    this.resetParam(
      'itemMaxFontScale',
      e1 && 'itemMaxFontScale' in e1 ? e1.itemMaxFontScale : undefined
    );
    this.resetParam(
      'itemFontColor',
      e1 && 'itemFontColor' in e1 ? e1.itemFontColor : undefined
    );
    this.resetParam(
      'itemSelectedFontColor',
      e1 && 'itemSelectedFontColor' in e1 ? e1.itemSelectedFontColor : undefined
    );
    this.resetParam(
      'itemFontSize',
      e1 && 'itemFontSize' in e1 ? e1.itemFontSize : undefined
    );
    this.resetParam(
      'itemSelectedFontSize',
      e1 && 'itemSelectedFontSize' in e1 ? e1.itemSelectedFontSize : undefined
    );
    this.resetParam(
      'itemFontWeight',
      e1 && 'itemFontWeight' in e1 ? e1.itemFontWeight : undefined
    );
    this.resetParam(
      'itemSelectedFontWeight',
      e1 && 'itemSelectedFontWeight' in e1
        ? e1.itemSelectedFontWeight
        : undefined
    );
    this.resetParam(
      'itemIconSize',
      e1 && 'itemIconSize' in e1 ? e1.itemIconSize : undefined
    );
    this.resetParam(
      'itemIconFillColor',
      e1 && 'itemIconFillColor' in e1 ? e1.itemIconFillColor : undefined
    );
    this.resetParam(
      'itemSelectedIconFillColor',
      e1 && 'itemSelectedIconFillColor' in e1
        ? e1.itemSelectedIconFillColor
        : undefined
    );
    this.resetParam(
      'itemSymbolFontSize',
      e1 && 'itemSymbolFontSize' in e1 ? e1.itemSymbolFontSize : undefined
    );
    this.resetParam(
      'itemSymbolFontColor',
      e1 && 'itemSymbolFontColor' in e1 ? e1.itemSymbolFontColor : undefined
    );
    this.resetParam(
      'itemSelectedSymbolFontColor',
      e1 && 'itemSelectedSymbolFontColor' in e1
        ? e1.itemSelectedSymbolFontColor
        : undefined
    );
    this.resetParam(
      'itemMinHeight',
      e1 && 'itemMinHeight' in e1 ? e1.itemMinHeight : undefined
    );
    this.resetParam(
      'itemPadding',
      e1 && 'itemPadding' in e1 ? e1.itemPadding : undefined
    );
    this.resetParam(
      'languageDirection',
      e1 && 'languageDirection' in e1 ? e1.languageDirection : undefined
    );
  }

  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((c1, d1) => {
      Column.create({ space: 2 });
      Column.constraintSize({
        minHeight: this.getItemMinHeight(),
        minWidth: '100%',
      });
      Column.direction(this.languageDirection);
      Column.justifyContent(FlexAlign.Center);
      Column.padding(this.getItemPadding());
    }, Column);
    this.observeComponentCreation2((w, x) => {
      If.create();
      if (this.item.symbol || this.item.symbolModifier) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((a1, b1) => {
            SymbolGlyph.create(this.item.symbol);
            SymbolGlyph.fontSize(this.getSymbolFontSize());
            SymbolGlyph.fontColor([this.getItemSymbolFillColor()]);
            SymbolGlyph.direction(this.languageDirection);
            SymbolGlyph.attributeModifier.bind(this)(this.item.symbolModifier);
          }, SymbolGlyph);
        });
      } else if (this.item.icon) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((y, z) => {
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
    this.observeComponentCreation2((s, t) => {
      If.create();
      if (this.item.text) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((u, v) => {
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
      LengthMetricsUtils.getInstance().isNaturalNumber(
        this.itemSymbolFontSize
      ) &&
      this.itemSymbolFontSize.unit !== LengthUnit.PERCENT
    ) {
      return LengthMetricsUtils.getInstance().stringify(
        this.itemSymbolFontSize
      );
    }
    return this.theme.itemSymbolFontSize;
  }

  getItemMaxFontScale() {
    if (typeof this.itemMaxFontScale === 'number') {
      return normalize(
        this.itemMaxFontScale,
        this.theme.itemMaxFontScaleSmallest,
        this.theme.itemMaxFontScaleLargest
      );
    }
    if (typeof this.itemMaxFontScale === 'object') {
      const r =
        parseNumericResource(this.getUIContext(), this.itemMaxFontScale) ??
        SMALLEST_MAX_FONT_SCALE;
      return normalize(
        r,
        this.theme.itemMaxFontScaleSmallest,
        this.theme.itemMaxFontScaleLargest
      );
    }
    return SMALLEST_MAX_FONT_SCALE;
  }

  getItemMinFontScale() {
    if (typeof this.itemMinFontScale === 'number') {
      return normalize(
        this.itemMinFontScale,
        this.theme.itemMinFontScaleSmallest,
        this.theme.itemMinFontScaleLargest
      );
    }
    if (typeof this.itemMinFontScale === 'object') {
      const q =
        parseNumericResource(this.getUIContext(), this.itemMinFontScale) ??
        SMALLEST_MIN_FONT_SCALE;
      return normalize(
        q,
        this.theme.itemMinFontScaleSmallest,
        this.theme.itemMinFontScaleLargest
      );
    }
    return SMALLEST_MIN_FONT_SCALE;
  }

  getItemPadding() {
    const p = {
      top: this.theme.itemPadding.top,
      bottom: this.theme.itemPadding.bottom,
      start: this.theme.itemPadding.start,
      end: this.theme.itemPadding.end,
    };
    if (
      this.itemPadding?.top &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemPadding.top)
    ) {
      p.top = this.itemPadding.top;
    }
    if (
      this.itemPadding?.bottom &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemPadding.bottom)
    ) {
      p.bottom = this.itemPadding.bottom;
    }
    if (
      this.itemPadding?.start &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemPadding.start)
    ) {
      p.start = this.itemPadding.start;
    }
    if (
      this.itemPadding?.end &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemPadding.end)
    ) {
      p.end = this.itemPadding.end;
    }
    return p;
  }

  getItemMinHeight() {
    if (
      this.itemMinHeight &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemMinHeight)
    ) {
      return LengthMetricsUtils.getInstance().stringify(this.itemMinHeight);
    }
    return this.hasHybrid
      ? this.theme.hybridItemMinHeight
      : this.theme.itemMinHeight;
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
        LengthMetricsUtils.getInstance().isNaturalNumber(
          this.itemSelectedFontSize
        ) &&
        this.itemSelectedFontSize.unit !== LengthUnit.PERCENT
      ) {
        return LengthMetricsUtils.getInstance().stringify(
          this.itemSelectedFontSize
        );
      }
      return this.theme.itemFontSize;
    }
    if (
      this.itemFontSize &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemFontSize) &&
      this.itemFontSize.unit !== LengthUnit.PERCENT
    ) {
      return LengthMetricsUtils.getInstance().stringify(this.itemFontSize);
    }
    return this.theme.itemFontSize;
  }

  getItemIconHeight() {
    if (
      this.itemIconSize?.height &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemIconSize.height)
    ) {
      return LengthMetricsUtils.getInstance().stringify(
        this.itemIconSize.height
      );
    }
    return this.theme.itemIconSize;
  }

  getItemIconWidth() {
    if (
      this.itemIconSize?.width &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.itemIconSize.width)
    ) {
      return LengthMetricsUtils.getInstance().stringify(
        this.itemIconSize.width
      );
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

  updateStateVars(o) {
    if (o === undefined) {
      return;
    }
    if ('hasHybrid' in o) {
      this.updateParam('hasHybrid', o.hasHybrid);
    }
    if ('item' in o) {
      this.updateParam('item', o.item);
    }
    if ('selected' in o) {
      this.updateParam('selected', o.selected);
    }
    if ('theme' in o) {
      this.updateParam('theme', o.theme);
    }
    if ('itemMinFontScale' in o) {
      this.updateParam('itemMinFontScale', o.itemMinFontScale);
    }
    if ('itemMaxFontScale' in o) {
      this.updateParam('itemMaxFontScale', o.itemMaxFontScale);
    }
    if ('itemFontColor' in o) {
      this.updateParam('itemFontColor', o.itemFontColor);
    }
    if ('itemSelectedFontColor' in o) {
      this.updateParam('itemSelectedFontColor', o.itemSelectedFontColor);
    }
    if ('itemFontSize' in o) {
      this.updateParam('itemFontSize', o.itemFontSize);
    }
    if ('itemSelectedFontSize' in o) {
      this.updateParam('itemSelectedFontSize', o.itemSelectedFontSize);
    }
    if ('itemFontWeight' in o) {
      this.updateParam('itemFontWeight', o.itemFontWeight);
    }
    if ('itemSelectedFontWeight' in o) {
      this.updateParam('itemSelectedFontWeight', o.itemSelectedFontWeight);
    }
    if ('itemIconSize' in o) {
      this.updateParam('itemIconSize', o.itemIconSize);
    }
    if ('itemIconFillColor' in o) {
      this.updateParam('itemIconFillColor', o.itemIconFillColor);
    }
    if ('itemSelectedIconFillColor' in o) {
      this.updateParam(
        'itemSelectedIconFillColor',
        o.itemSelectedIconFillColor
      );
    }
    if ('itemSymbolFontSize' in o) {
      this.updateParam('itemSymbolFontSize', o.itemSymbolFontSize);
    }
    if ('itemSymbolFontColor' in o) {
      this.updateParam('itemSymbolFontColor', o.itemSymbolFontColor);
    }
    if ('itemSelectedSymbolFontColor' in o) {
      this.updateParam(
        'itemSelectedSymbolFontColor',
        o.itemSelectedSymbolFontColor
      );
    }
    if ('itemMinHeight' in o) {
      this.updateParam('itemMinHeight', o.itemMinHeight);
    }
    if ('itemPadding' in o) {
      this.updateParam('itemPadding', o.itemPadding);
    }
    if ('languageDirection' in o) {
      this.updateParam('languageDirection', o.languageDirection);
    }
  }

  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}

__decorate([Param], SegmentButtonV2ItemContent.prototype, 'hasHybrid', void 0);
__decorate([Param], SegmentButtonV2ItemContent.prototype, 'item', void 0);
__decorate([Param], SegmentButtonV2ItemContent.prototype, 'selected', void 0);
__decorate([Param], SegmentButtonV2ItemContent.prototype, 'theme', void 0);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemMinFontScale',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemMaxFontScale',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemFontColor',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemSelectedFontColor',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemFontSize',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemSelectedFontSize',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemFontWeight',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemSelectedFontWeight',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemIconSize',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemIconFillColor',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemSelectedIconFillColor',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemSymbolFontSize',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemSymbolFontColor',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemSelectedSymbolFontColor',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemMinHeight',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'itemPadding',
  void 0
);
__decorate(
  [Param],
  SegmentButtonV2ItemContent.prototype,
  'languageDirection',
  void 0
);

class LengthMetricsUtils {
  constructor() {}

  static getInstance() {
    if (!LengthMetricsUtils.instance) {
      LengthMetricsUtils.instance = new LengthMetricsUtils();
    }
    return LengthMetricsUtils.instance;
  }

  stringify(n) {
    switch (n.unit) {
      case LengthUnit.PX:
        return `${n.value}px`;
      case LengthUnit.VP:
        return `${n.value}vp`;
      case LengthUnit.FP:
        return `${n.value}fp`;
      case LengthUnit.PERCENT:
        return `${n.value}%`;
      case LengthUnit.LPX:
        return `${n.value}lpx`;
    }
  }

  isNaturalNumber(m) {
    return m.value >= 0;
  }
}

function parseNumericResource(i, j) {
  const k = i.getHostContext()?.resourceManager;
  if (!k) {
    return undefined;
  }
  try {
    return k.getNumber(j);
  } catch (l) {
    return undefined;
  }
}

function normalize(f, g, h) {
  return Math.min(Math.max(f, g), h);
}

function generateUniqueKye(b) {
  return (c, d) => {
    let e = b;
    if (c.text) {
      if (typeof c.text === 'string') {
        e += c.text;
      } else {
        e += getResourceUniqueId(c.text);
      }
    }
    if (c.icon) {
      if (typeof c.icon === 'string') {
        e += c.icon;
      } else {
        e += getResourceUniqueId(c.icon);
      }
    }
    if (c.symbol) {
      e += getResourceUniqueId(c.symbol);
    }
    return e;
  };
}

function getResourceUniqueId(a) {
  if (a.id !== -1) {
    return `${a.id}`;
  } else {
    return JSON.stringify(a);
  }
}

export default {
  SegmentButtonV2Item,
  SegmentButtonV2Items,
  TabSegmentButtonV2,
  CapsuleSegmentButtonV2,
  MultiCapsuleSegmentButtonV2,
};
