/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {});
}
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const mediaquery = requireNapi('mediaquery');

export var ChipSize;
(function (ChipSize) {
  ChipSize['NORMAL'] = 'NORMAL';
  ChipSize['SMALL'] = 'SMALL';
})(ChipSize || (ChipSize = {}));
var IconType;
(function (IconType) {
  IconType['PREFIX_ICON'] = 'PREFIXICON';
  IconType['SUFFIX_ICON'] = 'SUFFIXICON';
  IconType['PREFIX_SYMBOL'] = 'PREFIXSYMBOL';
  IconType['SUFFIX_SYMBOL'] = 'SUFFIXSYMBOL';
})(IconType || (IconType = {}));
var BreakPointsType;
(function (BreakPointsType) {
  BreakPointsType['SM'] = 'SM';
  BreakPointsType['MD'] = 'MD';
  BreakPointsType['LG'] = 'LG';
})(BreakPointsType || (BreakPointsType = {}));
export var AccessibilitySelectedType;
(function (AccessibilitySelectedType) {
  AccessibilitySelectedType[(AccessibilitySelectedType['CLICKED'] = 0)] = 'CLICKED';
  AccessibilitySelectedType[(AccessibilitySelectedType['CHECKED'] = 1)] = 'CHECKED';
  AccessibilitySelectedType[(AccessibilitySelectedType['SELECTED'] = 2)] = 'SELECTED';
})(AccessibilitySelectedType || (AccessibilitySelectedType = {}));
const RESOURCE_TYPE_STRING = 10003;
const RESOURCE_TYPE_FLOAT = 10002;
const RESOURCE_TYPE_INTEGER = 10007;
export function Chip(options, parent = null) {
  const __options__ = options;
  {
    (parent ? parent : this).observeComponentCreation2(
      (elmtId, isInitialRender, options = __options__) => {
        if (isInitialRender) {
          let componentCall = new ChipComponent(
            parent ? parent : this,
            {
              chipSize: options.size,
              prefixIcon: options.prefixIcon,
              prefixSymbol: options.prefixSymbol,
              label: options.label,
              suffixIcon: options.suffixIcon,
              suffixSymbol: options.suffixSymbol,
              suffixSymbolOptions: options.suffixSymbolOptions,
              allowClose: options.allowClose,
              closeOptions: options.closeOptions,
              chipEnabled: options.enabled,
              chipActivated: options.activated,
              chipNodeBackgroundColor: options.backgroundColor,
              chipNodeActivatedBackgroundColor: options.activatedBackgroundColor,
              chipNodeRadius: options.borderRadius,
              chipDirection: options.direction,
              chipAccessibilitySelectedType: options.accessibilitySelectedType,
              chipAccessibilityDescription: options.accessibilityDescription,
              chipAccessibilityLevel: options.accessibilityLevel,
              onClose: options.onClose,
              onClicked: options.onClicked,
            },
            undefined,
            elmtId,
            () => {},
            { page: 'library/src/main/ets/components/MainPage.ets', line: 224, col: 3 }
          );
          ViewPU.create(componentCall);
          let paramsLambda = () => {
            return {
              chipSize: options.size,
              prefixIcon: options.prefixIcon,
              prefixSymbol: options.prefixSymbol,
              label: options.label,
              suffixIcon: options.suffixIcon,
              suffixSymbol: options.suffixSymbol,
              suffixSymbolOptions: options.suffixSymbolOptions,
              allowClose: options.allowClose,
              closeOptions: options.closeOptions,
              chipEnabled: options.enabled,
              chipActivated: options.activated,
              chipNodeBackgroundColor: options.backgroundColor,
              chipNodeActivatedBackgroundColor: options.activatedBackgroundColor,
              chipNodeRadius: options.borderRadius,
              chipDirection: options.direction,
              chipAccessibilitySelectedType: options.accessibilitySelectedType,
              chipAccessibilityDescription: options.accessibilityDescription,
              chipAccessibilityLevel: options.accessibilityLevel,
              onClose: options.onClose,
              onClicked: options.onClicked,
            };
          };
          componentCall.paramsGenerator_ = paramsLambda;
        } else {
          (parent ? parent : this).updateStateVarsOfChildByElmtId(elmtId, {
            chipSize: options.size,
            prefixIcon: options.prefixIcon,
            prefixSymbol: options.prefixSymbol,
            label: options.label,
            suffixIcon: options.suffixIcon,
            suffixSymbol: options.suffixSymbol,
            suffixSymbolOptions: options.suffixSymbolOptions,
            allowClose: options.allowClose,
            closeOptions: options.closeOptions,
            chipEnabled: options.enabled,
            chipActivated: options.activated,
            chipNodeBackgroundColor: options.backgroundColor,
            chipNodeActivatedBackgroundColor: options.activatedBackgroundColor,
            chipNodeRadius: options.borderRadius,
            chipDirection: options.direction,
            chipAccessibilitySelectedType: options.accessibilitySelectedType,
            chipAccessibilityDescription: options.accessibilityDescription,
            chipAccessibilityLevel: options.accessibilityLevel,
          });
        }
      },
      { name: 'ChipComponent' }
    );
  }
}
export class ChipComponent extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.theme = {
      prefixIcon: {
        normalSize: {
          width: {
            id: -1,
            type: 10002,
            params: ['sys.float.chip_normal_icon_size'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          height: {
            id: -1,
            type: 10002,
            params: ['sys.float.chip_normal_icon_size'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        },
        smallSize: {
          width: {
            id: -1,
            type: 10002,
            params: ['sys.float.chip_small_icon_size'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          height: {
            id: -1,
            type: 10002,
            params: ['sys.float.chip_small_icon_size'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        },
        fillColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_usually_icon_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        activatedFillColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_active_icon_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        focusFillColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_icon_focus_fill'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        focusActivatedColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_icon_activated_focus_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
      },
      label: {
        normalFontSize: {
          id: -1,
          type: 10002,
          params: ['sys.float.chip_normal_font_size'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        smallFontSize: {
          id: -1,
          type: 10002,
          params: ['sys.float.chip_small_font_size'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        focusFontColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_focus_text'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        focusActiveFontColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_activated_focus_font_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        fontColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_font_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        activatedFontColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_activated_fontcolor'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        fontFamily: 'HarmonyOS Sans',
        fontWeight: {
          id: -1,
          type: 10002,
          params: ['sys.float.chip_text_font_weight'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        normalMargin: {
          left: 6,
          right: 6,
          top: 0,
          bottom: 0,
        },
        smallMargin: {
          left: 4,
          right: 4,
          top: 0,
          bottom: 0,
        },
        defaultFontSize: 14,
        localizedNormalMargin: {
          start: LengthMetrics.resource({
            id: -1,
            type: 10002,
            params: ['sys.float.chip_normal_text_margin'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          }),
          end: LengthMetrics.resource({
            id: -1,
            type: 10002,
            params: ['sys.float.chip_normal_text_margin'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          }),
          top: LengthMetrics.vp(0),
          bottom: LengthMetrics.vp(0),
        },
        localizedSmallMargin: {
          start: LengthMetrics.resource({
            id: -1,
            type: 10002,
            params: ['sys.float.chip_small_text_margin'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          }),
          end: LengthMetrics.resource({
            id: -1,
            type: 10002,
            params: ['sys.float.chip_small_text_margin'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          }),
          top: LengthMetrics.vp(0),
          bottom: LengthMetrics.vp(0),
        },
      },
      suffixIcon: {
        normalSize: {
          width: {
            id: -1,
            type: 10002,
            params: ['sys.float.chip_normal_icon_size'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          height: {
            id: -1,
            type: 10002,
            params: ['sys.float.chip_normal_icon_size'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        },
        smallSize: {
          width: {
            id: -1,
            type: 10002,
            params: ['sys.float.chip_small_icon_size'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
          height: {
            id: -1,
            type: 10002,
            params: ['sys.float.chip_small_icon_size'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        },
        fillColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_usually_icon_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        activatedFillColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_active_icon_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        focusFillColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_icon_focus_fill'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        focusActivatedColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_icon_activated_focus_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        defaultDeleteIcon: {
          id: -1,
          type: 20000,
          params: ['sys.media.ohos_ic_public_cancel', 16, 16],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        focusable: false,
        isShowMargin: {
          id: -1,
          type: 10002,
          params: ['sys.float.chip_show_close_icon_margin'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
      },
      defaultSymbol: {
        normalFontColor: [
          {
            id: -1,
            type: 10001,
            params: ['sys.color.chip_usually_icon_color'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        ],
        activatedFontColor: [
          {
            id: -1,
            type: 10001,
            params: ['sys.color.chip_active_icon_color'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        ],
        normalSymbolFontSize: LengthMetrics.resource({
          id: -1,
          type: 10002,
          params: ['sys.float.chip_normal_icon_size'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        }).value,
        smallSymbolFontSize: LengthMetrics.resource({
          id: -1,
          type: 10002,
          params: ['sys.float.chip_small_icon_size'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        }).value,
        defaultEffect: -1,
      },
      chipNode: {
        suitAgeScale: 1.75,
        minLabelWidth: 12,
        normalHeight: {
          id: -1,
          type: 10002,
          params: ['sys.float.chip_normal_height'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        smallHeight: {
          id: -1,
          type: 10002,
          params: ['sys.float.chip_small_height'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        enabled: true,
        activated: false,
        backgroundColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_background_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        activatedBackgroundColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_container_activated_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        focusOutlineColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.ohos_id_color_focused_outline'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        focusOutlineMargin: 2,
        borderColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_border_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        defaultBorderWidth: {
          id: -1,
          type: 10002,
          params: ['sys.float.chip_border_width'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        activatedBorderColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_activated_border_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        normalBorderRadius: {
          id: -1,
          type: 10002,
          params: ['sys.float.chip_border_radius_normal'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        smallBorderRadius: {
          id: -1,
          type: 10002,
          params: ['sys.float.chip_border_radius_small'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        borderWidth: 2,
        focusBtnScaleX: {
          id: -1,
          type: 10002,
          params: ['sys.float.chip_focused_btn_scale'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        focusBtnScaleY: {
          id: -1,
          type: 10002,
          params: ['sys.float.chip_focused_btn_scale'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        localizedNormalPadding: {
          start: LengthMetrics.resource({
            id: -1,
            type: 10002,
            params: ['sys.float.chip_normal_text_padding'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          }),
          end: LengthMetrics.resource({
            id: -1,
            type: 10002,
            params: ['sys.float.chip_normal_text_padding'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          }),
          top: LengthMetrics.vp(4),
          bottom: LengthMetrics.vp(4),
        },
        localizedSmallPadding: {
          start: LengthMetrics.resource({
            id: -1,
            type: 10002,
            params: ['sys.float.chip_small_text_padding'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          }),
          end: LengthMetrics.resource({
            id: -1,
            type: 10002,
            params: ['sys.float.chip_small_text_padding'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          }),
          top: LengthMetrics.vp(4),
          bottom: LengthMetrics.vp(4),
        },
        hoverBlendColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_hover_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        pressedBlendColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_press_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        focusBgColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_focus_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        focusActivatedBgColor: {
          id: -1,
          type: 10001,
          params: ['sys.color.chip_container_activated_focus_color'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        opacity: { normal: 1, hover: 0.95, pressed: 0.9 },
        normalShadowStyle: {
          id: -1,
          type: 10002,
          params: ['sys.float.chip_normal_shadow_style'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        smallShadowStyle: {
          id: -1,
          type: 10002,
          params: ['sys.float.chip_small_shadow_style'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        },
        breakPointConstraintWidth: {
          breakPointMinWidth: 128,
          breakPointSmMaxWidth: 156,
          breakPointMdMaxWidth: 280,
          breakPointLgMaxWidth: 400,
        },
      },
    };
    this.__chipSize = new SynchedPropertyObjectOneWayPU(params.chipSize, this, 'chipSize');
    this.__allowClose = new SynchedPropertySimpleOneWayPU(params.allowClose, this, 'allowClose');
    this.__closeOptions = new SynchedPropertyObjectOneWayPU(params.closeOptions, this, 'closeOptions');
    this.__chipDirection = new SynchedPropertySimpleOneWayPU(params.chipDirection, this, 'chipDirection');
    this.__prefixIcon = new SynchedPropertyObjectOneWayPU(params.prefixIcon, this, 'prefixIcon');
    this.__prefixSymbol = new SynchedPropertyObjectOneWayPU(params.prefixSymbol, this, 'prefixSymbol');
    this.__label = new SynchedPropertyObjectOneWayPU(params.label, this, 'label');
    this.__suffixIcon = new SynchedPropertyObjectOneWayPU(params.suffixIcon, this, 'suffixIcon');
    this.__suffixSymbol = new SynchedPropertyObjectOneWayPU(params.suffixSymbol, this, 'suffixSymbol');
    this.__suffixSymbolOptions = new SynchedPropertyObjectOneWayPU(
      params.suffixSymbolOptions,
      this,
      'suffixSymbolOptions'
    );
    this.__chipNodeBackgroundColor = new SynchedPropertyObjectOneWayPU(
      params.chipNodeBackgroundColor,
      this,
      'chipNodeBackgroundColor'
    );
    this.__chipNodeActivatedBackgroundColor = new SynchedPropertyObjectOneWayPU(
      params.chipNodeActivatedBackgroundColor,
      this,
      'chipNodeActivatedBackgroundColor'
    );
    this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(params.chipNodeRadius, this, 'chipNodeRadius');
    this.__chipEnabled = new SynchedPropertySimpleOneWayPU(params.chipEnabled, this, 'chipEnabled');
    this.__chipActivated = new SynchedPropertySimpleOneWayPU(params.chipActivated, this, 'chipActivated');
    this.__chipAccessibilitySelectedType = new SynchedPropertySimpleOneWayPU(
      params.chipAccessibilitySelectedType,
      this,
      'chipAccessibilitySelectedType'
    );
    this.__chipAccessibilityDescription = new SynchedPropertyObjectOneWayPU(
      params.chipAccessibilityDescription,
      this,
      'chipAccessibilityDescription'
    );
    this.__chipAccessibilityLevel = new SynchedPropertySimpleOneWayPU(
      params.chipAccessibilityLevel,
      this,
      'chipAccessibilityLevel'
    );
    this.__isChipExist = new ObservedPropertySimplePU(true, this, 'isChipExist');
    this.__chipScale = new ObservedPropertyObjectPU({ x: 1, y: 1 }, this, 'chipScale');
    this.__chipOpacity = new ObservedPropertySimplePU(1, this, 'chipOpacity');
    this.__suffixSymbolHeight = new ObservedPropertySimplePU(0, this, 'suffixSymbolHeight');
    this.__suffixSymbolWidth = new ObservedPropertySimplePU(0, this, 'suffixSymbolWidth');
    this.__breakPoint = new ObservedPropertySimplePU(BreakPointsType.SM, this, 'breakPoint');
    this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
    this.isSuffixIconFocusStyleCustomized = this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 0;
    this.isSuffixIconFocusable = this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 0;
    this.onClose = undefined;
    this.onClicked = undefined;
    this.__chipNodeInFocus = new ObservedPropertySimplePU(false, this, 'chipNodeInFocus');
    this.smListener = mediaquery.matchMediaSync('(0vp<width) and (width<600vp)');
    this.mdListener = mediaquery.matchMediaSync('(600vp<=width) and (width<840vp)');
    this.lgListener = mediaquery.matchMediaSync('(840vp<=width)');
    this.symbolEffect = new SymbolEffect();
    this.environmentCallbackID = undefined;
    this.environmentCallback = {
      onConfigurationUpdated: configuration => {
        this.fontSizeScale = configuration.fontSizeScale ?? 1;
      },
      onMemoryLevel() {},
    };
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
    if (params.theme !== undefined) {
      this.theme = params.theme;
    }
    if (params.chipSize === undefined) {
      this.__chipSize.set(ChipSize.NORMAL);
    }
    if (params.chipDirection === undefined) {
      this.__chipDirection.set(Direction.Auto);
    }
    if (params.chipEnabled === undefined) {
      this.__chipEnabled.set(true);
    }
    if (params.isChipExist !== undefined) {
      this.isChipExist = params.isChipExist;
    }
    if (params.chipScale !== undefined) {
      this.chipScale = params.chipScale;
    }
    if (params.chipOpacity !== undefined) {
      this.chipOpacity = params.chipOpacity;
    }
    if (params.suffixSymbolHeight !== undefined) {
      this.suffixSymbolHeight = params.suffixSymbolHeight;
    }
    if (params.suffixSymbolWidth !== undefined) {
      this.suffixSymbolWidth = params.suffixSymbolWidth;
    }
    if (params.breakPoint !== undefined) {
      this.breakPoint = params.breakPoint;
    }
    if (params.fontSizeScale !== undefined) {
      this.fontSizeScale = params.fontSizeScale;
    }
    if (params.isSuffixIconFocusStyleCustomized !== undefined) {
      this.isSuffixIconFocusStyleCustomized = params.isSuffixIconFocusStyleCustomized;
    }
    if (params.isSuffixIconFocusable !== undefined) {
      this.isSuffixIconFocusable = params.isSuffixIconFocusable;
    }
    if (params.onClose !== undefined) {
      this.onClose = params.onClose;
    }
    if (params.onClicked !== undefined) {
      this.onClicked = params.onClicked;
    }
    if (params.chipNodeInFocus !== undefined) {
      this.chipNodeInFocus = params.chipNodeInFocus;
    }
    if (params.smListener !== undefined) {
      this.smListener = params.smListener;
    }
    if (params.mdListener !== undefined) {
      this.mdListener = params.mdListener;
    }
    if (params.lgListener !== undefined) {
      this.lgListener = params.lgListener;
    }
    if (params.symbolEffect !== undefined) {
      this.symbolEffect = params.symbolEffect;
    }
    if (params.environmentCallbackID !== undefined) {
      this.environmentCallbackID = params.environmentCallbackID;
    }
    if (params.environmentCallback !== undefined) {
      this.environmentCallback = params.environmentCallback;
    }
  }
  updateStateVars(params) {
    this.__chipSize.reset(params.chipSize);
    this.__allowClose.reset(params.allowClose);
    this.__closeOptions.reset(params.closeOptions);
    this.__chipDirection.reset(params.chipDirection);
    this.__prefixIcon.reset(params.prefixIcon);
    this.__prefixSymbol.reset(params.prefixSymbol);
    this.__label.reset(params.label);
    this.__suffixIcon.reset(params.suffixIcon);
    this.__suffixSymbol.reset(params.suffixSymbol);
    this.__suffixSymbolOptions.reset(params.suffixSymbolOptions);
    this.__chipNodeBackgroundColor.reset(params.chipNodeBackgroundColor);
    this.__chipNodeActivatedBackgroundColor.reset(params.chipNodeActivatedBackgroundColor);
    this.__chipNodeRadius.reset(params.chipNodeRadius);
    this.__chipEnabled.reset(params.chipEnabled);
    this.__chipActivated.reset(params.chipActivated);
    this.__chipAccessibilitySelectedType.reset(params.chipAccessibilitySelectedType);
    this.__chipAccessibilityDescription.reset(params.chipAccessibilityDescription);
    this.__chipAccessibilityLevel.reset(params.chipAccessibilityLevel);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__chipSize.purgeDependencyOnElmtId(rmElmtId);
    this.__allowClose.purgeDependencyOnElmtId(rmElmtId);
    this.__closeOptions.purgeDependencyOnElmtId(rmElmtId);
    this.__chipDirection.purgeDependencyOnElmtId(rmElmtId);
    this.__prefixIcon.purgeDependencyOnElmtId(rmElmtId);
    this.__prefixSymbol.purgeDependencyOnElmtId(rmElmtId);
    this.__label.purgeDependencyOnElmtId(rmElmtId);
    this.__suffixIcon.purgeDependencyOnElmtId(rmElmtId);
    this.__suffixSymbol.purgeDependencyOnElmtId(rmElmtId);
    this.__suffixSymbolOptions.purgeDependencyOnElmtId(rmElmtId);
    this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(rmElmtId);
    this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(rmElmtId);
    this.__chipNodeRadius.purgeDependencyOnElmtId(rmElmtId);
    this.__chipEnabled.purgeDependencyOnElmtId(rmElmtId);
    this.__chipActivated.purgeDependencyOnElmtId(rmElmtId);
    this.__chipAccessibilitySelectedType.purgeDependencyOnElmtId(rmElmtId);
    this.__chipAccessibilityDescription.purgeDependencyOnElmtId(rmElmtId);
    this.__chipAccessibilityLevel.purgeDependencyOnElmtId(rmElmtId);
    this.__isChipExist.purgeDependencyOnElmtId(rmElmtId);
    this.__chipScale.purgeDependencyOnElmtId(rmElmtId);
    this.__chipOpacity.purgeDependencyOnElmtId(rmElmtId);
    this.__suffixSymbolHeight.purgeDependencyOnElmtId(rmElmtId);
    this.__suffixSymbolWidth.purgeDependencyOnElmtId(rmElmtId);
    this.__breakPoint.purgeDependencyOnElmtId(rmElmtId);
    this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
    this.__chipNodeInFocus.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.__chipSize.aboutToBeDeleted();
    this.__allowClose.aboutToBeDeleted();
    this.__closeOptions.aboutToBeDeleted();
    this.__chipDirection.aboutToBeDeleted();
    this.__prefixIcon.aboutToBeDeleted();
    this.__prefixSymbol.aboutToBeDeleted();
    this.__label.aboutToBeDeleted();
    this.__suffixIcon.aboutToBeDeleted();
    this.__suffixSymbol.aboutToBeDeleted();
    this.__suffixSymbolOptions.aboutToBeDeleted();
    this.__chipNodeBackgroundColor.aboutToBeDeleted();
    this.__chipNodeActivatedBackgroundColor.aboutToBeDeleted();
    this.__chipNodeRadius.aboutToBeDeleted();
    this.__chipEnabled.aboutToBeDeleted();
    this.__chipActivated.aboutToBeDeleted();
    this.__chipAccessibilitySelectedType.aboutToBeDeleted();
    this.__chipAccessibilityDescription.aboutToBeDeleted();
    this.__chipAccessibilityLevel.aboutToBeDeleted();
    this.__isChipExist.aboutToBeDeleted();
    this.__chipScale.aboutToBeDeleted();
    this.__chipOpacity.aboutToBeDeleted();
    this.__suffixSymbolHeight.aboutToBeDeleted();
    this.__suffixSymbolWidth.aboutToBeDeleted();
    this.__breakPoint.aboutToBeDeleted();
    this.__fontSizeScale.aboutToBeDeleted();
    this.__chipNodeInFocus.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get chipSize() {
    return this.__chipSize.get();
  }
  set chipSize(newValue) {
    this.__chipSize.set(newValue);
  }
  get allowClose() {
    return this.__allowClose.get();
  }
  set allowClose(newValue) {
    this.__allowClose.set(newValue);
  }
  get closeOptions() {
    return this.__closeOptions.get();
  }
  set closeOptions(newValue) {
    this.__closeOptions.set(newValue);
  }
  get chipDirection() {
    return this.__chipDirection.get();
  }
  set chipDirection(newValue) {
    this.__chipDirection.set(newValue);
  }
  get prefixIcon() {
    return this.__prefixIcon.get();
  }
  set prefixIcon(newValue) {
    this.__prefixIcon.set(newValue);
  }
  get prefixSymbol() {
    return this.__prefixSymbol.get();
  }
  set prefixSymbol(newValue) {
    this.__prefixSymbol.set(newValue);
  }
  get label() {
    return this.__label.get();
  }
  set label(newValue) {
    this.__label.set(newValue);
  }
  get suffixIcon() {
    return this.__suffixIcon.get();
  }
  set suffixIcon(newValue) {
    this.__suffixIcon.set(newValue);
  }
  get suffixSymbol() {
    return this.__suffixSymbol.get();
  }
  set suffixSymbol(newValue) {
    this.__suffixSymbol.set(newValue);
  }
  get suffixSymbolOptions() {
    return this.__suffixSymbolOptions.get();
  }
  set suffixSymbolOptions(newValue) {
    this.__suffixSymbolOptions.set(newValue);
  }
  get chipNodeBackgroundColor() {
    return this.__chipNodeBackgroundColor.get();
  }
  set chipNodeBackgroundColor(newValue) {
    this.__chipNodeBackgroundColor.set(newValue);
  }
  get chipNodeActivatedBackgroundColor() {
    return this.__chipNodeActivatedBackgroundColor.get();
  }
  set chipNodeActivatedBackgroundColor(newValue) {
    this.__chipNodeActivatedBackgroundColor.set(newValue);
  }
  get chipNodeRadius() {
    return this.__chipNodeRadius.get();
  }
  set chipNodeRadius(newValue) {
    this.__chipNodeRadius.set(newValue);
  }
  get chipEnabled() {
    return this.__chipEnabled.get();
  }
  set chipEnabled(newValue) {
    this.__chipEnabled.set(newValue);
  }
  get chipActivated() {
    return this.__chipActivated.get();
  }
  set chipActivated(newValue) {
    this.__chipActivated.set(newValue);
  }
  get chipAccessibilitySelectedType() {
    return this.__chipAccessibilitySelectedType.get();
  }
  set chipAccessibilitySelectedType(newValue) {
    this.__chipAccessibilitySelectedType.set(newValue);
  }
  get chipAccessibilityDescription() {
    return this.__chipAccessibilityDescription.get();
  }
  set chipAccessibilityDescription(newValue) {
    this.__chipAccessibilityDescription.set(newValue);
  }
  get chipAccessibilityLevel() {
    return this.__chipAccessibilityLevel.get();
  }
  set chipAccessibilityLevel(newValue) {
    this.__chipAccessibilityLevel.set(newValue);
  }
  get isChipExist() {
    return this.__isChipExist.get();
  }
  set isChipExist(newValue) {
    this.__isChipExist.set(newValue);
  }
  get chipScale() {
    return this.__chipScale.get();
  }
  set chipScale(newValue) {
    this.__chipScale.set(newValue);
  }
  get chipOpacity() {
    return this.__chipOpacity.get();
  }
  set chipOpacity(newValue) {
    this.__chipOpacity.set(newValue);
  }
  get suffixSymbolHeight() {
    return this.__suffixSymbolHeight.get();
  }
  set suffixSymbolHeight(newValue) {
    this.__suffixSymbolHeight.set(newValue);
  }
  get suffixSymbolWidth() {
    return this.__suffixSymbolWidth.get();
  }
  set suffixSymbolWidth(newValue) {
    this.__suffixSymbolWidth.set(newValue);
  }
  get breakPoint() {
    return this.__breakPoint.get();
  }
  set breakPoint(newValue) {
    this.__breakPoint.set(newValue);
  }
  get fontSizeScale() {
    return this.__fontSizeScale.get();
  }
  set fontSizeScale(newValue) {
    this.__fontSizeScale.set(newValue);
  }
  get chipNodeInFocus() {
    return this.__chipNodeInFocus.get();
  }
  set chipNodeInFocus(newValue) {
    this.__chipNodeInFocus.set(newValue);
  }
  aboutToAppear() {
    this.smListener.on('change', mediaQueryResult => {
      if (mediaQueryResult.matches) {
        this.breakPoint = BreakPointsType.SM;
      }
    });
    this.mdListener.on('change', mediaQueryResult => {
      if (mediaQueryResult.matches) {
        this.breakPoint = BreakPointsType.MD;
      }
    });
    this.lgListener.on('change', mediaQueryResult => {
      if (mediaQueryResult.matches) {
        this.breakPoint = BreakPointsType.LG;
      }
    });
    let abilityContext = this.getUIContext().getHostContext();
    if (abilityContext) {
      this.fontSizeScale = abilityContext.config?.fontSizeScale ?? 1;
      this.environmentCallbackID = abilityContext.getApplicationContext().on('environment', this.environmentCallback);
    }
  }
  aboutToDisappear() {
    this.smListener.off('change');
    this.mdListener.off('change');
    this.lgListener.off('change');
    if (this.environmentCallbackID) {
      this.getUIContext()?.getHostContext()?.getApplicationContext().off('environment', this.environmentCallbackID);
      this.environmentCallbackID = void 0;
    }
  }
  isSetActiveChipBgColor() {
    if (this.chipNodeActivatedBackgroundColor) {
      return false;
    }
    try {
      return (
        ColorMetrics.resourceColor(this.chipNodeActivatedBackgroundColor).color !==
        ColorMetrics.resourceColor(this.theme.chipNode.activatedBackgroundColor).color
      );
    } catch (error) {
      console.error(`[Chip] failed to get ColorMetrics.resourceColor`);
      return false;
    }
  }
  isSetNormalChipBgColor() {
    if (this.chipNodeBackgroundColor) {
      return false;
    }
    try {
      return (
        ColorMetrics.resourceColor(this.chipNodeBackgroundColor).color !==
        ColorMetrics.resourceColor(this.theme.chipNode.backgroundColor).color
      );
    } catch (error) {
      console.error(`[Chip] failed to get resourceColor`);
      return false;
    }
  }
  getShadowStyles() {
    if (!this.chipNodeInFocus) {
      return undefined;
    }
    return this.resourceToNumber(
      this.isSmallChipSize() ? this.theme.chipNode.smallShadowStyle : this.theme.chipNode.normalShadowStyle,
      -1
    );
  }
  ChipBuilder(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Button.createWithChild({ type: ButtonType.Normal });
      Button.clip(false);
      Button.shadow(this.getShadowStyles());
      Button.padding(0);
      Button.focusable(true);
      Button.size(this.getChipSize());
      Button.enabled(this.isChipEnabled());
      Button.direction(this.chipDirection);
      Button.backgroundColor(this.getChipBackgroundColor());
      Button.borderWidth(this.theme.chipNode.defaultBorderWidth);
      Button.borderColor(this.getChipNodeBorderColor());
      Button.borderRadius(this.getChipBorderRadius());
      Button.scale(ObservedObject.GetRawObject(this.chipScale));
      Button.opacity(this.chipOpacity);
      Button.accessibilityGroup(true);
      Button.accessibilityDescription(this.getAccessibilityDescription());
      Button.accessibilityLevel(this.getAccessibilityLevel());
      Button.accessibilityChecked(this.getAccessibilityChecked());
      Button.accessibilitySelected(this.getAccessibilitySelected());
      Button.onClick(this.getChipOnClicked());
      Button.onKeyEvent(event => {
        if (!event || event.type === null || event.type !== KeyType.Down) {
          return;
        }
        let isDeleteChip = event.keyCode === KeyCode.KEYCODE_FORWARD_DEL;
        let isEnterDeleteChip =
          event.keyCode === KeyCode.KEYCODE_ENTER &&
          this.allowClose !== false &&
          !this.suffixIcon?.src &&
          this.isSuffixIconFocusStyleCustomized;
        if (isDeleteChip || isEnterDeleteChip) {
          this.deleteChip();
        }
      });
      Button.onFocus(() => {
        if (this.isSuffixIconFocusStyleCustomized) {
          this.chipNodeInFocus = true;
        }
        this.chipZoomIn();
      });
      Button.onBlur(() => {
        if (this.isSuffixIconFocusStyleCustomized) {
          this.chipNodeInFocus = false;
        }
        this.chipZoomOut();
      });
      Button.onHover(
        !this.isSuffixIconFocusStyleCustomized
          ? undefined
          : isHover => {
              isHover ? this.chipZoomIn() : this.chipZoomOut();
            }
      );
    }, Button);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
      Flex.direction(this.chipDirection);
      Flex.padding(this.getChipPadding());
      Flex.size(this.getChipSize());
      Flex.constraintSize(this.getChipConstraintSize());
    }, Flex);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.hasPrefixSymbol()) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(this.defaultSymbolFontsize());
            SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.PREFIX_SYMBOL));
            SymbolGlyph.flexShrink(0);
            SymbolGlyph.attributeModifier.bind(this)(this.getPrefixSymbolModifier());
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(this.symbolEffect, false);
            SymbolGlyph.symbolEffect(this.symbolEffect, this.theme.defaultSymbol.defaultEffect);
          }, SymbolGlyph);
        });
      } else if (this.prefixIcon?.src) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.prefixIcon.src);
            Image.direction(this.chipDirection);
            Image.size(this.getPrefixIconSize());
            Image.fillColor(this.getPrefixIconFilledColor());
            Image.objectFit(ImageFit.Cover);
            Image.focusable(false);
            Image.flexShrink(0);
            Image.draggable(false);
          }, Image);
        });
      } else {
        this.ifElseBranchUpdateFunction(2, () => {});
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Text.create(this.getChipText());
      Text.draggable(false);
      Text.flexShrink(1);
      Text.focusable(true);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.textAlign(TextAlign.Center);
      Text.direction(this.chipDirection);
      Text.fontSize(this.getLabelFontSize());
      Text.fontColor(this.getLabelFontColor());
      Text.fontFamily(this.getLabelFontFamily());
      Text.fontWeight(this.getLabelFontWeight());
      Text.margin(this.getLabelMargin());
    }, Text);
    Text.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.hasSuffixSymbol()) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.onClick(this.getSuffixSymbolAction());
            Button.accessibilityText(this.getSuffixSymbolAccessibilityText());
            Button.accessibilityDescription(this.getSuffixSymbolAccessibilityDescription());
            Button.accessibilityLevel(this.getSuffixSymbolAccessibilityLevel());
            Button.flexShrink(0);
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius(0);
            Button.padding(0);
            Button.stateEffect(false);
            Button.hoverEffect(HoverEffect.None);
            Button.focusable(this.isSuffixIconFocusable);
          }, Button);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(this.defaultSymbolFontsize());
            SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_SYMBOL));
            SymbolGlyph.attributeModifier.bind(this)(this.getSuffixSymbolModifier());
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(this.symbolEffect, false);
            SymbolGlyph.symbolEffect(this.symbolEffect, this.theme.defaultSymbol.defaultEffect);
          }, SymbolGlyph);
          Button.pop();
        });
      } else if (this.suffixIcon?.src) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius(0);
            Button.padding(0);
            Button.flexShrink(0);
            Button.stateEffect(false);
            Button.hoverEffect(HoverEffect.None);
            Button.size(this.getSuffixIconSize());
            Button.accessibilityText(this.getSuffixIconAccessibilityText());
            Button.accessibilityDescription(this.getSuffixIconAccessibilityDescription());
            Button.accessibilityLevel(this.getSuffixIconAccessibilityLevel());
            Button.onClick(this.getSuffixIconAction());
            Button.focusable(this.isSuffixIconFocusable);
          }, Button);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.suffixIcon.src);
            Image.direction(this.chipDirection);
            Image.size(this.getSuffixIconSize());
            Image.fillColor(this.getSuffixIconFilledColor());
            Image.objectFit(ImageFit.Cover);
            Image.draggable(false);
          }, Image);
          Button.pop();
        });
      } else if (this.isClosable()) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius(0);
            Button.padding(0);
            Button.flexShrink(0);
            Button.stateEffect(false);
            Button.hoverEffect(HoverEffect.None);
            Button.accessibilityText(this.getCloseIconAccessibilityText());
            Button.accessibilityDescription(this.getCloseIconAccessibilityDescription());
            Button.accessibilityLevel(this.getCloseIconAccessibilityLevel());
            Button.onClick(() => {
              if (!this.isChipEnabled()) {
                return;
              }
              this.onClose?.();
              this.deleteChip();
            });
            Button.focusable(this.isSuffixIconFocusable);
          }, Button);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create({
              id: -1,
              type: 40000,
              params: ['sys.symbol.xmark'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            SymbolGlyph.fontSize(this.defaultSymbolFontsize());
            SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_SYMBOL));
          }, SymbolGlyph);
          Button.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(3, () => {});
      }
    }, If);
    If.pop();
    Flex.pop();
    Button.pop();
  }
  getCloseIconAccessibilityLevel() {
    if (
      this.closeOptions?.accessibilityLevel === 'no' ||
      this.closeOptions?.accessibilityLevel === 'no-hide-descendants'
    ) {
      return this.closeOptions.accessibilityLevel;
    }
    return 'yes';
  }
  getCloseIconAccessibilityDescription() {
    if (typeof this.closeOptions?.accessibilityDescription === 'undefined') {
      return void 0;
    }
    return this.closeOptions.accessibilityDescription;
  }
  getCloseIconAccessibilityText() {
    if (typeof this.closeOptions?.accessibilityText === 'undefined') {
      return {
        id: -1,
        type: 10003,
        params: ['sys.string.delete_used_for_accessibility_text'],
        bundleName: '__harDefaultBundleName__',
        moduleName: '__harDefaultModuleName__',
      };
    }
    return this.closeOptions.accessibilityText;
  }
  getSuffixIconAction() {
    if (this.suffixIcon?.src) {
      if (!this.suffixIcon?.action) {
        return void 0;
      }
      return () => {
        if (this.isChipEnabled()) {
          this.suffixIcon?.action?.();
        }
      };
    }
    return void 0;
  }
  getSuffixIconFilledColor() {
    if (this.isChipActivated()) {
      return this.suffixIcon?.activatedFillColor ?? this.getDefaultActiveIconColor(IconType.PREFIX_ICON);
    }
    return this.suffixIcon?.fillColor ?? this.getDefaultFillIconColor(IconType.SUFFIX_ICON);
  }
  getSuffixIconSize() {
    let suffixIconSize = { width: 0, height: 0 };
    if (typeof this.suffixIcon?.size?.width !== 'undefined' && this.isValidLength(this.suffixIcon.size.width)) {
      suffixIconSize.width = this.suffixIcon.size.width;
    } else {
      suffixIconSize.width = this.isSmallChipSize()
        ? this.theme.suffixIcon.smallSize.width
        : this.theme.suffixIcon.normalSize.width;
    }
    if (typeof this.suffixIcon?.size?.height !== 'undefined' && this.isValidLength(this.suffixIcon.size.height)) {
      suffixIconSize.height = this.suffixIcon.size.height;
    } else {
      suffixIconSize.height = this.isSmallChipSize()
        ? this.theme.suffixIcon.smallSize.height
        : this.theme.suffixIcon.normalSize.height;
    }
    return suffixIconSize;
  }
  getSuffixIconAccessibilityLevel() {
    if (this.suffixIcon?.accessibilityLevel === 'no' || this.suffixIcon?.accessibilityLevel === 'no-hide-descendants') {
      return this.suffixIcon.accessibilityLevel;
    }
    return this.suffixIcon?.action ? 'yes' : 'no';
  }
  getSuffixIconAccessibilityDescription() {
    if (typeof this.suffixIcon?.accessibilityDescription === 'undefined') {
      return void 0;
    }
    return this.suffixIcon.accessibilityDescription;
  }
  getSuffixIconAccessibilityText() {
    if (typeof this.suffixIcon?.accessibilityText === 'undefined') {
      return void 0;
    }
    return this.suffixIcon.accessibilityText;
  }
  isClosable() {
    return this.allowClose ?? true;
  }
  getSuffixSymbolModifier() {
    if (this.isChipActivated()) {
      return this.suffixSymbol?.activated;
    }
    return this.suffixSymbol?.normal;
  }
  getSuffixSymbolAccessibilityLevel() {
    if (this.isChipActivated()) {
      if (
        this.suffixSymbolOptions?.activatedAccessibility?.accessibilityLevel === 'no' ||
        this.suffixSymbolOptions?.activatedAccessibility?.accessibilityLevel === 'no-hide-descendants'
      ) {
        return this.suffixSymbolOptions.activatedAccessibility.accessibilityLevel;
      }
      return this.suffixSymbolOptions?.action ? 'yes' : 'no';
    }
    if (
      this.suffixSymbolOptions?.normalAccessibility?.accessibilityLevel === 'no' ||
      this.suffixSymbolOptions?.normalAccessibility?.accessibilityLevel === 'no-hide-descendants'
    ) {
      return this.suffixSymbolOptions.normalAccessibility.accessibilityLevel;
    }
    return this.suffixSymbolOptions?.action ? 'yes' : 'no';
  }
  getSuffixSymbolAccessibilityDescription() {
    if (this.isChipActivated()) {
      if (typeof this.suffixSymbolOptions?.activatedAccessibility?.accessibilityDescription !== 'undefined') {
        return this.suffixSymbolOptions.activatedAccessibility.accessibilityDescription;
      }
      return void 0;
    }
    if (typeof this.suffixSymbolOptions?.normalAccessibility?.accessibilityDescription !== 'undefined') {
      return this.suffixSymbolOptions.normalAccessibility.accessibilityDescription;
    }
    return void 0;
  }
  getSuffixSymbolAccessibilityText() {
    if (this.isChipActivated()) {
      if (typeof this.suffixSymbolOptions?.activatedAccessibility?.accessibilityText !== 'undefined') {
        return this.suffixSymbolOptions.activatedAccessibility.accessibilityText;
      }
      return void 0;
    }
    if (typeof this.suffixSymbolOptions?.normalAccessibility?.accessibilityText !== 'undefined') {
      return this.suffixSymbolOptions.normalAccessibility.accessibilityText;
    }
    return void 0;
  }
  getSuffixSymbolAction() {
    if (typeof this.suffixSymbolOptions?.action === 'undefined') {
      return void 0;
    }
    return () => {
      if (!this.isChipEnabled()) {
        return;
      }
      this.suffixSymbolOptions?.action?.();
    };
  }
  hasSuffixSymbol() {
    return !!(this.suffixSymbol?.normal || this.suffixSymbol?.activated);
  }
  getPrefixIconFilledColor() {
    if (this.isChipActivated()) {
      return this.prefixIcon?.activatedFillColor ?? this.getDefaultActiveIconColor(IconType.PREFIX_ICON);
    }
    return this.prefixIcon?.fillColor ?? this.getDefaultFillIconColor(IconType.PREFIX_ICON);
  }
  getPrefixIconSize() {
    let prefixIconSize = { width: 0, height: 0 };
    if (typeof this.prefixIcon?.size?.width !== 'undefined' && this.isValidLength(this.prefixIcon.size.width)) {
      prefixIconSize.width = this.prefixIcon.size.width;
    } else {
      prefixIconSize.width = this.isSmallChipSize()
        ? this.theme.prefixIcon.smallSize.width
        : this.theme.prefixIcon.normalSize.width;
    }
    if (typeof this.prefixIcon?.size?.height !== 'undefined' && this.isValidLength(this.prefixIcon.size.height)) {
      prefixIconSize.height = this.prefixIcon.size.height;
    } else {
      prefixIconSize.height = this.isSmallChipSize()
        ? this.theme.prefixIcon.smallSize.height
        : this.theme.prefixIcon.normalSize.height;
    }
    return prefixIconSize;
  }
  getPrefixSymbolModifier() {
    if (this.isChipActivated()) {
      return this.prefixSymbol?.activated;
    }
    return this.prefixSymbol?.normal;
  }
  getDefaultSymbolColor(iconType) {
    return this.isChipActivated() ? this.getSymbolActiveColor(iconType) : this.getSymbolFillColor(iconType);
  }
  getDefaultActiveIconColor(iconType) {
    if (iconType === IconType.PREFIX_ICON) {
      return this.chipNodeInFocus
        ? this.theme.prefixIcon.focusActivatedColor
        : this.theme.prefixIcon.activatedFillColor;
    } else {
      return this.chipNodeInFocus
        ? this.theme.suffixIcon.focusActivatedColor
        : this.theme.suffixIcon.activatedFillColor;
    }
  }
  getDefaultFillIconColor(iconType) {
    if (iconType === IconType.PREFIX_ICON) {
      return this.chipNodeInFocus ? this.theme.prefixIcon.focusFillColor : this.theme.prefixIcon.fillColor;
    } else {
      return this.chipNodeInFocus ? this.theme.suffixIcon.focusFillColor : this.theme.suffixIcon.fillColor;
    }
  }
  getSymbolActiveColor(iconType) {
    if (!this.chipNodeInFocus) {
      return this.theme.defaultSymbol.activatedFontColor;
    }
    if (iconType === IconType.PREFIX_SYMBOL) {
      return [this.theme.prefixIcon.focusActivatedColor];
    }
    if (iconType === IconType.SUFFIX_SYMBOL) {
      return [this.theme.suffixIcon.focusActivatedColor];
    }
    return this.theme.defaultSymbol.activatedFontColor;
  }
  getSymbolFillColor(iconType) {
    if (!this.chipNodeInFocus) {
      return this.theme.defaultSymbol.normalFontColor;
    }
    if (iconType === IconType.PREFIX_SYMBOL) {
      return [this.theme.prefixIcon.focusFillColor];
    }
    if (iconType === IconType.SUFFIX_SYMBOL) {
      return [this.theme.suffixIcon.focusFillColor];
    }
    return this.theme.defaultSymbol.normalFontColor;
  }
  hasPrefixSymbol() {
    return !!(this.prefixSymbol?.normal || this.prefixSymbol?.activated);
  }
  getChipConstraintSize() {
    const constraintSize = {};
    if (typeof this.chipSize === 'string') {
      constraintSize.maxWidth = this.getChipMaxWidth();
      constraintSize.minHeight =
        this.chipSize === ChipSize.SMALL ? this.theme.chipNode.smallHeight : this.theme.chipNode.normalHeight;
    } else {
      if (typeof this.chipSize?.width === 'undefined' || !this.isValidLength(this.chipSize.width)) {
        constraintSize.maxWidth = this.getChipMaxWidth();
      }
      if (typeof this.chipSize?.height === 'undefined' || !this.isValidLength(this.chipSize.height)) {
        constraintSize.minHeight = this.theme.chipNode.normalHeight;
      }
    }
    return constraintSize;
  }
  getChipMaxWidth() {
    if (this.fontSizeScale >= this.theme.chipNode.suitAgeScale) {
      return void 0;
    }
    if (this.breakPoint === BreakPointsType.SM) {
      return this.theme.chipNode.breakPointConstraintWidth.breakPointSmMaxWidth;
    }
    if (this.breakPoint === BreakPointsType.MD) {
      return this.theme.chipNode.breakPointConstraintWidth.breakPointMdMaxWidth;
    }
    if (this.breakPoint === BreakPointsType.LG) {
      return this.theme.chipNode.breakPointConstraintWidth.breakPointLgMaxWidth;
    }
    return void 0;
  }
  getChipSize() {
    const chipSize = {
      width: 'auto',
      height: 'auto',
    };
    if (typeof this.chipSize !== 'string') {
      if (typeof this.chipSize?.width !== 'undefined' && this.isValidLength(this.chipSize.width)) {
        chipSize.width = this.chipSize.width;
      }
      if (typeof this.chipSize?.height !== 'undefined' && this.isValidLength(this.chipSize.height)) {
        chipSize.height = this.chipSize.height;
      }
    }
    return chipSize;
  }
  getChipPadding() {
    return this.isSmallChipSize()
      ? this.theme.chipNode.localizedSmallPadding
      : this.theme.chipNode.localizedNormalPadding;
  }
  getLabelMargin() {
    const localizedLabelMargin = {
      start: LengthMetrics.vp(0),
      end: LengthMetrics.vp(0),
    };
    const defaultLocalizedMargin = this.isSmallChipSize()
      ? this.theme.label.localizedSmallMargin
      : this.theme.label.localizedNormalMargin;
    if (
      typeof this.label?.localizedLabelMargin?.start !== 'undefined' &&
      this.label.localizedLabelMargin.start.value >= 0
    ) {
      localizedLabelMargin.start = this.label.localizedLabelMargin.start;
    } else if (this.hasPrefix()) {
      localizedLabelMargin.start = defaultLocalizedMargin.start;
    }
    if (
      typeof this.label?.localizedLabelMargin?.end !== 'undefined' &&
      this.label.localizedLabelMargin.end.value >= 0
    ) {
      localizedLabelMargin.end = this.label.localizedLabelMargin.end;
    } else if (this.hasSuffix()) {
      localizedLabelMargin.end = defaultLocalizedMargin.end;
    }
    if (typeof this.label?.localizedLabelMargin === 'object') {
      return localizedLabelMargin;
    }
    if (typeof this.label.labelMargin === 'object') {
      const labelMargin = { left: 0, right: 0 };
      const defaultLabelMargin = this.isSmallChipSize() ? this.theme.label.smallMargin : this.theme.label.normalMargin;
      if (typeof this.label?.labelMargin?.left !== 'undefined' && this.isValidLength(this.label.labelMargin.left)) {
        labelMargin.left = this.label.labelMargin.left;
      } else if (this.hasPrefix()) {
        labelMargin.left = defaultLabelMargin.left;
      }
      if (typeof this.label?.labelMargin?.right !== 'undefined' && this.isValidLength(this.label.labelMargin.right)) {
        labelMargin.right = this.label.labelMargin.right;
      } else if (this.hasSuffix()) {
        labelMargin.right = defaultLabelMargin.right;
      }
      return labelMargin;
    }
    return localizedLabelMargin;
  }
  hasSuffix() {
    if (this.suffixIcon?.src) {
      return true;
    }
    return this.isChipActivated() ? !!this.suffixSymbol?.activated : !!this.suffixSymbol?.normal;
  }
  hasPrefix() {
    if (this.prefixIcon?.src) {
      return true;
    }
    return this.isChipActivated() ? !!this.prefixSymbol?.activated : !!this.prefixSymbol?.normal;
  }
  getLabelFontWeight() {
    if (this.isChipActivated()) {
      return FontWeight.Medium;
    }
    return this.resourceToNumber(this.theme.label.fontWeight, FontWeight.Regular);
  }
  getLabelFontFamily() {
    return this.label?.fontFamily ?? this.theme.label.fontFamily;
  }
  defaultSymbolFontsize() {
    return this.isSmallChipSize()
      ? this.theme.defaultSymbol.smallSymbolFontSize
      : this.theme.defaultSymbol.normalSymbolFontSize;
  }
  getActiveFontColor() {
    return this.chipNodeInFocus ? this.theme.label.focusActiveFontColor : this.theme.label.activatedFontColor;
  }
  getFontColor() {
    return this.chipNodeInFocus ? this.theme.label.focusFontColor : this.theme.label.fontColor;
  }
  getChipNodeBorderColor() {
    let themeChipNode = this.theme.chipNode;
    return this.isChipActivated() ? themeChipNode.activatedBorderColor : themeChipNode.borderColor;
  }
  getLabelFontColor() {
    if (this.isChipActivated()) {
      return this.label?.activatedFontColor ?? this.getActiveFontColor();
    }
    return this.label?.fontColor ?? this.getFontColor();
  }
  getLabelFontSize() {
    if (typeof this.label.fontSize !== 'undefined' && this.isValidLength(this.label.fontSize)) {
      return this.label.fontSize;
    }
    if (this.isSmallChipSize()) {
      return this.theme.label.smallFontSize;
    }
    return this.theme.label.normalFontSize;
  }
  getChipText() {
    return this.label?.text ?? '';
  }
  deleteChip() {
    Context.animateTo({ curve: Curve.Sharp, duration: 150 }, () => {
      this.chipOpacity = 0;
    });
    Context.animateTo(
      {
        curve: Curve.FastOutLinearIn,
        duration: 150,
        onFinish: () => {
          this.isChipExist = false;
        },
      },
      () => {
        this.chipScale = { x: 0.85, y: 0.85 };
      }
    );
  }
  getChipOnClicked() {
    if (this.onClicked) {
      return this.onClicked.bind(this);
    }
    return void 0;
  }
  getAccessibilitySelected() {
    if (this.getChipAccessibilitySelectedType() === AccessibilitySelectedType.SELECTED) {
      return this.isChipActivated();
    }
    return void 0;
  }
  getAccessibilityChecked() {
    if (this.getChipAccessibilitySelectedType() === AccessibilitySelectedType.CHECKED) {
      return this.isChipActivated();
    }
    return void 0;
  }
  getChipAccessibilitySelectedType() {
    if (typeof this.chipActivated === 'undefined') {
      return AccessibilitySelectedType.CLICKED;
    }
    return this.chipAccessibilitySelectedType ?? AccessibilitySelectedType.CHECKED;
  }
  getAccessibilityLevel() {
    return this.chipAccessibilityLevel;
  }
  getAccessibilityDescription() {
    if (typeof this.chipAccessibilityDescription === 'undefined') {
      return void 0;
    }
    return this.chipAccessibilityDescription;
  }
  isChipEnabled() {
    return this.chipEnabled ?? true;
  }
  getChipBorderRadius() {
    if (typeof this.chipNodeRadius !== 'undefined' && this.isValidLength(this.chipNodeRadius)) {
      return this.chipNodeRadius;
    }
    return this.isSmallChipSize() ? this.theme.chipNode.smallBorderRadius : this.theme.chipNode.normalBorderRadius;
  }
  isSmallChipSize() {
    return typeof this.chipSize === 'string' && this.chipSize === ChipSize.SMALL;
  }
  getChipBackgroundColor() {
    let themeChipNode = this.theme.chipNode;
    if (this.isChipActivated()) {
      return this.chipNodeInFocus && !this.isSetActiveChipBgColor()
        ? themeChipNode.focusActivatedBgColor
        : this.getColor(this.chipNodeActivatedBackgroundColor, themeChipNode.activatedBackgroundColor);
    }
    return this.chipNodeInFocus && !this.isSetNormalChipBgColor()
      ? themeChipNode.focusBgColor
      : this.getColor(this.chipNodeBackgroundColor, this.theme.chipNode.backgroundColor);
  }
  getColor(color, defaultColor) {
    if (!color) {
      return defaultColor;
    }
    try {
      ColorMetrics.resourceColor(color).color;
      return color;
    } catch (e) {
      console.error(`[Chip] failed to get color`);
      return Color.Transparent;
    }
  }
  isChipActivated() {
    return this.chipActivated ?? false;
  }
  resourceToNumber(resource, defaultValue) {
    if (!resource || !resource.type) {
      console.error('[Chip] failed: resource get fail');
      return defaultValue;
    }
    const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resourceManager) {
      console.error('[Chip] failed to get resourceManager');
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
          console.error(`[Chip] get resource error, return defaultValue`);
          return defaultValue;
        }
      default:
        return defaultValue;
    }
  }
  isValidLength(length) {
    if (typeof length === 'number') {
      return length >= 0;
    } else if (typeof length === 'string') {
      return this.isValidLengthString(length);
    } else if (typeof length === 'object') {
      const resource = length;
      const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
      if (!resourceManager) {
        console.error('[Chip] failed to get resourceManager.');
        return false;
      }
      switch (resource.type) {
        case RESOURCE_TYPE_FLOAT:
        case RESOURCE_TYPE_INTEGER:
          return resourceManager.getNumber(resource) >= 0;
        case RESOURCE_TYPE_STRING:
          return this.isValidLengthString(resourceManager.getStringSync(resource));
        default:
          return false;
      }
    }
    return false;
  }
  isValidLengthString(length) {
    const matches = length.match(/(-?\d+(?:\.\d+)?)_?(fp|vp|px|lpx)?$/i);
    if (!matches || matches.length < 3) {
      return false;
    }
    return Number.parseInt(matches[1], 10) >= 0;
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.isChipExist) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.ChipBuilder.bind(this)();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
      }
    }, If);
    If.pop();
  }
  chipZoomOut() {
   if (this.isSuffixIconFocusStyleCustomized) {
    this.chipScale = {
     x: 1,
     y: 1,
    };
   }
  }
  chipZoomIn() {
   if (this.isSuffixIconFocusStyleCustomized) {
     this.chipScale = {
      x: this.resourceToNumber(this.theme.chipNode.focusBtnScaleX, 1),
      y: this.resourceToNumber(this.theme.chipNode.focusBtnScaleY, 1),
     };
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export default {
  Chip,
  ChipSize,
  AccessibilitySelectedType,
};
