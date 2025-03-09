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
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const measure = requireNapi('measure');
const mediaquery = requireNapi('mediaquery');
const resourceManager = requireNapi('resourceManager');
const componentUtils = requireNapi('arkui.componentUtils');
const hilog = requireNapi('hilog');
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;

const RESOURCE_TYPE_STRING = 10003;
const RESOURCE_TYPE_FLOAT = 10002;
const RESOURCE_TYPE_INTEGER = 10007;
export var ChipSize;
(function (k6) {
  k6['NORMAL'] = 'NORMAL';
  k6['SMALL'] = 'SMALL';
})(ChipSize || (ChipSize = {}));
var IconType;
(function (j6) {
  j6['PREFIX_ICON'] = 'PREFIXICON';
  j6['SUFFIX_ICON'] = 'SUFFIXICON';
  j6['PREFIX_SYMBOL'] = 'PREFIXSYMBOL';
  j6['SUFFIX_SYMBOL'] = 'SUFFIXSYMBOL';
})(IconType || (IconType = {}));
var BreakPointsType;
(function (i6) {
  i6['SM'] = 'SM';
  i6['MD'] = 'MD';
  i6['LG'] = 'LG';
})(BreakPointsType || (BreakPointsType = {}));
export var AccessibilitySelectedType;
(function (h6) {
  h6[(h6['CLICKED'] = 0)] = 'CLICKED';
  h6[(h6['CHECKED'] = 1)] = 'CHECKED';
  h6[(h6['SELECTED'] = 2)] = 'SELECTED';
})(AccessibilitySelectedType || (AccessibilitySelectedType = {}));
const noop = () => {};
export function Chip(y5, a6 = null) {
  const b6 = y5;
  {
    (a6 ? a6 : this).observeComponentCreation2(
      (c6, d6, e6 = b6) => {
        if (d6) {
          let f6 = new ChipComponent(
            a6 ? a6 : this,
            {
              chipSize: e6.size,
              prefixIcon: e6.prefixIcon,
              prefixSymbol: e6.prefixSymbol,
              label: e6.label,
              suffixIcon: e6.suffixIcon,
              suffixSymbol: e6.suffixSymbol,
              suffixSymbolOptions: e6.suffixSymbolOptions,
              allowClose: e6.allowClose,
              closeOptions: e6.closeOptions,
              chipEnabled: e6.enabled,
              chipActivated: e6.activated,
              chipNodeBackgroundColor: e6.backgroundColor,
              chipNodeActivatedBackgroundColor: e6.activatedBackgroundColor,
              chipNodeRadius: e6.borderRadius,
              chipDirection: e6.direction,
              chipAccessibilitySelectedType: e6.accessibilitySelectedType,
              chipAccessibilityDescription: e6.accessibilityDescription,
              chipAccessibilityLevel: e6.accessibilityLevel,
              onClose: e6.onClose,
              onClicked: e6.onClicked,
            },
            undefined,
            c6,
            () => {},
            {
              page: 'library/src/main/ets/components/MainPage.ets',
              line: 231,
              col: 3,
            }
          );
          ViewPU.create(f6);
          let l = () => {
            return {
              chipSize: e6.size,
              prefixIcon: e6.prefixIcon,
              prefixSymbol: e6.prefixSymbol,
              label: e6.label,
              suffixIcon: e6.suffixIcon,
              suffixSymbol: e6.suffixSymbol,
              suffixSymbolOptions: e6.suffixSymbolOptions,
              allowClose: e6.allowClose,
              closeOptions: e6.closeOptions,
              chipEnabled: e6.enabled,
              chipActivated: e6.activated,
              chipNodeBackgroundColor: e6.backgroundColor,
              chipNodeActivatedBackgroundColor: e6.activatedBackgroundColor,
              chipNodeRadius: e6.borderRadius,
              chipDirection: e6.direction,
              chipAccessibilitySelectedType: e6.accessibilitySelectedType,
              chipAccessibilityDescription: e6.accessibilityDescription,
              chipAccessibilityLevel: e6.accessibilityLevel,
              onClose: e6.onClose,
              onClicked: e6.onClicked,
            };
          };
          f6.paramsGenerator_ = l;
        } else {
          (a6 ? a6 : this).updateStateVarsOfChildByElmtId(c6, {
            chipSize: e6.size,
            prefixIcon: e6.prefixIcon,
            prefixSymbol: e6.prefixSymbol,
            label: e6.label,
            suffixIcon: e6.suffixIcon,
            suffixSymbol: e6.suffixSymbol,
            suffixSymbolOptions: e6.suffixSymbolOptions,
            allowClose: e6.allowClose,
            closeOptions: e6.closeOptions,
            chipEnabled: e6.enabled,
            chipActivated: e6.activated,
            chipNodeBackgroundColor: e6.backgroundColor,
            chipNodeActivatedBackgroundColor: e6.activatedBackgroundColor,
            chipNodeRadius: e6.borderRadius,
            chipDirection: e6.direction,
            chipAccessibilitySelectedType: e6.accessibilitySelectedType,
            chipAccessibilityDescription: e6.accessibilityDescription,
            chipAccessibilityLevel: e6.accessibilityLevel,
          });
        }
      },
      { name: 'ChipComponent' }
    );
  }
}
function isValidString(u5, v5) {
  const w5 = u5.match(v5);
  if (!w5 || w5.length < 3) {
    return false;
  }
  const x5 = Number.parseFloat(w5[1]);
  return x5 >= 0;
}
function isValidDimensionString(t5) {
  return isValidString(
    t5,
    new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i')
  );
}
function isValidResource(q5, r5) {
  const s5 = q5?.resourceManager;
  if (r5 === void 0 || r5 === null || s5 === void 0) {
    return false;
  }
  if (
    r5.type !== RESOURCE_TYPE_STRING &&
    r5.type !== RESOURCE_TYPE_INTEGER &&
    r5.type !== RESOURCE_TYPE_FLOAT
  ) {
    return false;
  }
  if (r5.type === RESOURCE_TYPE_INTEGER || r5.type === RESOURCE_TYPE_FLOAT) {
    if (s5.getNumber(r5.id) >= 0) {
      return true;
    } else {
      return false;
    }
  }
  if (
    r5.type === RESOURCE_TYPE_STRING &&
    !isValidDimensionString(s5.getStringSync(r5.id))
  ) {
    return false;
  } else {
    return true;
  }
}
export class ChipComponent extends ViewPU {
  constructor(j5, k5, l5, m5 = -1, n5 = undefined, o5) {
    super(j5, l5, m5, o5);
    if (typeof n5 === 'function') {
      this.paramsGenerator_ = n5;
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
            params: ['sys.color.ohos_id_color_secondary'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        ],
        activatedFontColor: [
          {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary_contrary'],
            bundleName: '__harDefaultBundleName__',
            moduleName: '__harDefaultModuleName__',
          },
        ],
        smallSymbolFontSize: LengthMetrics.resource({
          id: -1,
          type: 10002,
          params: ['sys.float.chip_normal_icon_size'],
          bundleName: '__harDefaultBundleName__',
          moduleName: '__harDefaultModuleName__',
        }).value,
        normalSymbolFontSize: LengthMetrics.resource({
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
    this.__chipSize = new SynchedPropertyObjectOneWayPU(
      k5.chipSize,
      this,
      'chipSize'
    );
    this.__allowClose = new SynchedPropertySimpleOneWayPU(
      k5.allowClose,
      this,
      'allowClose'
    );
    this.__closeOptions = new SynchedPropertyObjectOneWayPU(
      k5.closeOptions,
      this,
      'closeOptions'
    );
    this.__chipDirection = new SynchedPropertySimpleOneWayPU(
      k5.chipDirection,
      this,
      'chipDirection'
    );
    this.__prefixIcon = new SynchedPropertyObjectOneWayPU(
      k5.prefixIcon,
      this,
      'prefixIcon'
    );
    this.__prefixSymbol = new SynchedPropertyObjectOneWayPU(
      k5.prefixSymbol,
      this,
      'prefixSymbol'
    );
    this.__label = new SynchedPropertyObjectOneWayPU(k5.label, this, 'label');
    this.__suffixIcon = new SynchedPropertyObjectOneWayPU(
      k5.suffixIcon,
      this,
      'suffixIcon'
    );
    this.__suffixSymbol = new SynchedPropertyObjectOneWayPU(
      k5.suffixSymbol,
      this,
      'suffixSymbol'
    );
    this.__suffixSymbolOptions = new SynchedPropertyObjectOneWayPU(
      k5.suffixSymbolOptions,
      this,
      'suffixSymbolOptions'
    );
    this.__chipNodeBackgroundColor = new SynchedPropertyObjectOneWayPU(
      k5.chipNodeBackgroundColor,
      this,
      'chipNodeBackgroundColor'
    );
    this.__chipNodeActivatedBackgroundColor = new SynchedPropertyObjectOneWayPU(
      k5.chipNodeActivatedBackgroundColor,
      this,
      'chipNodeActivatedBackgroundColor'
    );
    this.__isHovering = new ObservedPropertySimplePU(false, this, 'isHovering');
    this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(
      k5.chipNodeRadius,
      this,
      'chipNodeRadius'
    );
    this.__chipEnabled = new SynchedPropertySimpleOneWayPU(
      k5.chipEnabled,
      this,
      'chipEnabled'
    );
    this.__chipActivated = new SynchedPropertySimpleOneWayPU(
      k5.chipActivated,
      this,
      'chipActivated'
    );
    this.__chipAccessibilitySelectedType = new SynchedPropertySimpleOneWayPU(
      k5.chipAccessibilitySelectedType,
      this,
      'chipAccessibilitySelectedType'
    );
    this.__chipAccessibilityDescription = new SynchedPropertyObjectOneWayPU(
      k5.chipAccessibilityDescription,
      this,
      'chipAccessibilityDescription'
    );
    this.__chipAccessibilityLevel = new SynchedPropertySimpleOneWayPU(
      k5.chipAccessibilityLevel,
      this,
      'chipAccessibilityLevel'
    );
    this.__isHover = new ObservedPropertySimplePU(false, this, 'isHover');
    this.__chipScale = new ObservedPropertyObjectPU(
      { x: 1, y: 1 },
      this,
      'chipScale'
    );
    this.__chipOpacity = new ObservedPropertySimplePU(1, this, 'chipOpacity');
    this.__chipBlendColor = new ObservedPropertyObjectPU(
      Color.Transparent,
      this,
      'chipBlendColor'
    );
    this.__deleteChip = new ObservedPropertySimplePU(false, this, 'deleteChip');
    this.__chipNodeOnFocus = new ObservedPropertySimplePU(
      false,
      this,
      'chipNodeOnFocus'
    );
    this.__useDefaultSuffixIcon = new ObservedPropertySimplePU(
      false,
      this,
      'useDefaultSuffixIcon'
    );
    this.chipNodeSize = {};
    this.onClose = noop;
    this.onClicked = noop;
    this.__suffixIconOnFocus = new ObservedPropertySimplePU(
      false,
      this,
      'suffixIconOnFocus'
    );
    this.__chipBreakPoints = new ObservedPropertySimplePU(
      BreakPointsType.SM,
      this,
      'chipBreakPoints'
    );
    this.smListener = mediaquery.matchMediaSync(
      '(0vp<width) and (width<600vp)'
    );
    this.mdListener = mediaquery.matchMediaSync(
      '(600vp<=width) and (width<840vp)'
    );
    this.lgListener = mediaquery.matchMediaSync('(840vp<=width)');
    this.isSuffixIconFocusStyleCustomized =
      this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 0;
    this.__isShowPressedBackGroundColor = new ObservedPropertySimplePU(
      false,
      this,
      'isShowPressedBackGroundColor'
    );
    this.__fontSizeScale = new ObservedPropertyObjectPU(
      0,
      this,
      'fontSizeScale'
    );
    this.__fontWeightScale = new ObservedPropertyObjectPU(
      0,
      this,
      'fontWeightScale'
    );
    this.callbacks = {
      onConfigurationUpdated: (p5) => {
        this.fontSizeScale = p5.fontSizeScale;
        this.fontWeightScale = p5.fontWeightScale;
      },
      onMemoryLevel() {},
    };
    this.callbackId = undefined;
    this.__prefixSymbolWidth = new ObservedPropertyObjectPU(
      this.toVp(
        componentUtils.getRectangleById('PrefixSymbolGlyph')?.size?.width
      ),
      this,
      'prefixSymbolWidth'
    );
    this.__suffixSymbolWidth = new ObservedPropertyObjectPU(
      this.toVp(
        componentUtils.getRectangleById('SuffixSymbolGlyph')?.size?.width
      ),
      this,
      'suffixSymbolWidth'
    );
    this.__allowCloseSymbolWidth = new ObservedPropertyObjectPU(
      this.toVp(
        componentUtils.getRectangleById('AllowCloseSymbolGlyph')?.size?.width
      ),
      this,
      'allowCloseSymbolWidth'
    );
    this.__symbolEffect = new ObservedPropertyObjectPU(
      new SymbolEffect(),
      this,
      'symbolEffect'
    );
    this.setInitiallyProvidedValue(k5);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(i5) {
    if (i5.theme !== undefined) {
      this.theme = i5.theme;
    }
    if (i5.chipSize === undefined) {
      this.__chipSize.set(ChipSize.NORMAL);
    }
    if (i5.allowClose === undefined) {
      this.__allowClose.set(true);
    }
    if (i5.chipDirection === undefined) {
      this.__chipDirection.set(Direction.Auto);
    }
    if (i5.prefixIcon === undefined) {
      this.__prefixIcon.set({ src: '' });
    }
    if (i5.label === undefined) {
      this.__label.set({ text: '' });
    }
    if (i5.suffixIcon === undefined) {
      this.__suffixIcon.set({ src: '' });
    }
    if (i5.chipNodeBackgroundColor === undefined) {
      this.__chipNodeBackgroundColor.set(this.theme.chipNode.backgroundColor);
    }
    if (i5.chipNodeActivatedBackgroundColor === undefined) {
      this.__chipNodeActivatedBackgroundColor.set(
        this.theme.chipNode.activatedBackgroundColor
      );
    }
    if (i5.isHovering !== undefined) {
      this.isHovering = i5.isHovering;
    }
    if (i5.chipNodeRadius === undefined) {
      this.__chipNodeRadius.set(void 0);
    }
    if (i5.chipEnabled === undefined) {
      this.__chipEnabled.set(true);
    }
    if (i5.isHover !== undefined) {
      this.isHover = i5.isHover;
    }
    if (i5.chipScale !== undefined) {
      this.chipScale = i5.chipScale;
    }
    if (i5.chipOpacity !== undefined) {
      this.chipOpacity = i5.chipOpacity;
    }
    if (i5.chipBlendColor !== undefined) {
      this.chipBlendColor = i5.chipBlendColor;
    }
    if (i5.deleteChip !== undefined) {
      this.deleteChip = i5.deleteChip;
    }
    if (i5.chipNodeOnFocus !== undefined) {
      this.chipNodeOnFocus = i5.chipNodeOnFocus;
    }
    if (i5.useDefaultSuffixIcon !== undefined) {
      this.useDefaultSuffixIcon = i5.useDefaultSuffixIcon;
    }
    if (i5.chipNodeSize !== undefined) {
      this.chipNodeSize = i5.chipNodeSize;
    }
    if (i5.onClose !== undefined) {
      this.onClose = i5.onClose;
    }
    if (i5.onClicked !== undefined) {
      this.onClicked = i5.onClicked;
    }
    if (i5.suffixIconOnFocus !== undefined) {
      this.suffixIconOnFocus = i5.suffixIconOnFocus;
    }
    if (i5.chipBreakPoints !== undefined) {
      this.chipBreakPoints = i5.chipBreakPoints;
    }
    if (i5.smListener !== undefined) {
      this.smListener = i5.smListener;
    }
    if (i5.mdListener !== undefined) {
      this.mdListener = i5.mdListener;
    }
    if (i5.lgListener !== undefined) {
      this.lgListener = i5.lgListener;
    }
    if (i5.isSuffixIconFocusStyleCustomized !== undefined) {
      this.isSuffixIconFocusStyleCustomized =
        i5.isSuffixIconFocusStyleCustomized;
    }
    if (i5.isShowPressedBackGroundColor !== undefined) {
      this.isShowPressedBackGroundColor = i5.isShowPressedBackGroundColor;
    }
    if (i5.fontSizeScale !== undefined) {
      this.fontSizeScale = i5.fontSizeScale;
    }
    if (i5.fontWeightScale !== undefined) {
      this.fontWeightScale = i5.fontWeightScale;
    }
    if (i5.callbacks !== undefined) {
      this.callbacks = i5.callbacks;
    }
    if (i5.callbackId !== undefined) {
      this.callbackId = i5.callbackId;
    }
    if (i5.prefixSymbolWidth !== undefined) {
      this.prefixSymbolWidth = i5.prefixSymbolWidth;
    }
    if (i5.suffixSymbolWidth !== undefined) {
      this.suffixSymbolWidth = i5.suffixSymbolWidth;
    }
    if (i5.allowCloseSymbolWidth !== undefined) {
      this.allowCloseSymbolWidth = i5.allowCloseSymbolWidth;
    }
    if (i5.symbolEffect !== undefined) {
      this.symbolEffect = i5.symbolEffect;
    }
  }
  updateStateVars(h5) {
    this.__chipSize.reset(h5.chipSize);
    this.__allowClose.reset(h5.allowClose);
    this.__closeOptions.reset(h5.closeOptions);
    this.__chipDirection.reset(h5.chipDirection);
    this.__prefixIcon.reset(h5.prefixIcon);
    this.__prefixSymbol.reset(h5.prefixSymbol);
    this.__label.reset(h5.label);
    this.__suffixIcon.reset(h5.suffixIcon);
    this.__suffixSymbol.reset(h5.suffixSymbol);
    this.__suffixSymbolOptions.reset(h5.suffixSymbolOptions);
    this.__chipNodeBackgroundColor.reset(h5.chipNodeBackgroundColor);
    this.__chipNodeActivatedBackgroundColor.reset(
      h5.chipNodeActivatedBackgroundColor
    );
    this.__chipNodeRadius.reset(h5.chipNodeRadius);
    this.__chipEnabled.reset(h5.chipEnabled);
    this.__chipActivated.reset(h5.chipActivated);
    this.__chipAccessibilitySelectedType.reset(
      h5.chipAccessibilitySelectedType
    );
    this.__chipAccessibilityDescription.reset(h5.chipAccessibilityDescription);
    this.__chipAccessibilityLevel.reset(h5.chipAccessibilityLevel);
  }
  purgeVariableDependenciesOnElmtId(g5) {
    this.__chipSize.purgeDependencyOnElmtId(g5);
    this.__allowClose.purgeDependencyOnElmtId(g5);
    this.__closeOptions.purgeDependencyOnElmtId(g5);
    this.__chipDirection.purgeDependencyOnElmtId(g5);
    this.__prefixIcon.purgeDependencyOnElmtId(g5);
    this.__prefixSymbol.purgeDependencyOnElmtId(g5);
    this.__label.purgeDependencyOnElmtId(g5);
    this.__suffixIcon.purgeDependencyOnElmtId(g5);
    this.__suffixSymbol.purgeDependencyOnElmtId(g5);
    this.__suffixSymbolOptions.purgeDependencyOnElmtId(g5);
    this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(g5);
    this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(g5);
    this.__isHovering.purgeDependencyOnElmtId(g5);
    this.__chipNodeRadius.purgeDependencyOnElmtId(g5);
    this.__chipEnabled.purgeDependencyOnElmtId(g5);
    this.__chipActivated.purgeDependencyOnElmtId(g5);
    this.__chipAccessibilitySelectedType.purgeDependencyOnElmtId(g5);
    this.__chipAccessibilityDescription.purgeDependencyOnElmtId(g5);
    this.__chipAccessibilityLevel.purgeDependencyOnElmtId(g5);
    this.__isHover.purgeDependencyOnElmtId(g5);
    this.__chipScale.purgeDependencyOnElmtId(g5);
    this.__chipOpacity.purgeDependencyOnElmtId(g5);
    this.__chipBlendColor.purgeDependencyOnElmtId(g5);
    this.__deleteChip.purgeDependencyOnElmtId(g5);
    this.__chipNodeOnFocus.purgeDependencyOnElmtId(g5);
    this.__useDefaultSuffixIcon.purgeDependencyOnElmtId(g5);
    this.__suffixIconOnFocus.purgeDependencyOnElmtId(g5);
    this.__chipBreakPoints.purgeDependencyOnElmtId(g5);
    this.__isShowPressedBackGroundColor.purgeDependencyOnElmtId(g5);
    this.__fontSizeScale.purgeDependencyOnElmtId(g5);
    this.__fontWeightScale.purgeDependencyOnElmtId(g5);
    this.__prefixSymbolWidth.purgeDependencyOnElmtId(g5);
    this.__suffixSymbolWidth.purgeDependencyOnElmtId(g5);
    this.__allowCloseSymbolWidth.purgeDependencyOnElmtId(g5);
    this.__symbolEffect.purgeDependencyOnElmtId(g5);
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
    this.__isHovering.aboutToBeDeleted();
    this.__chipNodeRadius.aboutToBeDeleted();
    this.__chipEnabled.aboutToBeDeleted();
    this.__chipActivated.aboutToBeDeleted();
    this.__chipAccessibilitySelectedType.aboutToBeDeleted();
    this.__chipAccessibilityDescription.aboutToBeDeleted();
    this.__chipAccessibilityLevel.aboutToBeDeleted();
    this.__isHover.aboutToBeDeleted();
    this.__chipScale.aboutToBeDeleted();
    this.__chipOpacity.aboutToBeDeleted();
    this.__chipBlendColor.aboutToBeDeleted();
    this.__deleteChip.aboutToBeDeleted();
    this.__chipNodeOnFocus.aboutToBeDeleted();
    this.__useDefaultSuffixIcon.aboutToBeDeleted();
    this.__suffixIconOnFocus.aboutToBeDeleted();
    this.__chipBreakPoints.aboutToBeDeleted();
    this.__isShowPressedBackGroundColor.aboutToBeDeleted();
    this.__fontSizeScale.aboutToBeDeleted();
    this.__fontWeightScale.aboutToBeDeleted();
    this.__prefixSymbolWidth.aboutToBeDeleted();
    this.__suffixSymbolWidth.aboutToBeDeleted();
    this.__allowCloseSymbolWidth.aboutToBeDeleted();
    this.__symbolEffect.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get chipSize() {
    return this.__chipSize.get();
  }
  set chipSize(f5) {
    this.__chipSize.set(f5);
  }
  get allowClose() {
    return this.__allowClose.get();
  }
  set allowClose(e5) {
    this.__allowClose.set(e5);
  }
  get closeOptions() {
    return this.__closeOptions.get();
  }
  set closeOptions(d5) {
    this.__closeOptions.set(d5);
  }
  get chipDirection() {
    return this.__chipDirection.get();
  }
  set chipDirection(c5) {
    this.__chipDirection.set(c5);
  }
  get prefixIcon() {
    return this.__prefixIcon.get();
  }
  set prefixIcon(b5) {
    this.__prefixIcon.set(b5);
  }
  get prefixSymbol() {
    return this.__prefixSymbol.get();
  }
  set prefixSymbol(z4) {
    this.__prefixSymbol.set(z4);
  }
  get label() {
    return this.__label.get();
  }
  set label(y4) {
    this.__label.set(y4);
  }
  get suffixIcon() {
    return this.__suffixIcon.get();
  }
  set suffixIcon(x4) {
    this.__suffixIcon.set(x4);
  }
  get suffixSymbol() {
    return this.__suffixSymbol.get();
  }
  set suffixSymbol(w4) {
    this.__suffixSymbol.set(w4);
  }
  get suffixSymbolOptions() {
    return this.__suffixSymbolOptions.get();
  }
  set suffixSymbolOptions(v4) {
    this.__suffixSymbolOptions.set(v4);
  }
  get chipNodeBackgroundColor() {
    return this.__chipNodeBackgroundColor.get();
  }
  set chipNodeBackgroundColor(u4) {
    this.__chipNodeBackgroundColor.set(u4);
  }
  get chipNodeActivatedBackgroundColor() {
    return this.__chipNodeActivatedBackgroundColor.get();
  }
  set chipNodeActivatedBackgroundColor(t4) {
    this.__chipNodeActivatedBackgroundColor.set(t4);
  }
  get isHovering() {
    return this.__isHovering.get();
  }
  set isHovering(s4) {
    this.__isHovering.set(s4);
  }
  get chipNodeRadius() {
    return this.__chipNodeRadius.get();
  }
  set chipNodeRadius(r4) {
    this.__chipNodeRadius.set(r4);
  }
  get chipEnabled() {
    return this.__chipEnabled.get();
  }
  set chipEnabled(q4) {
    this.__chipEnabled.set(q4);
  }
  get chipActivated() {
    return this.__chipActivated.get();
  }
  set chipActivated(p4) {
    this.__chipActivated.set(p4);
  }
  get chipAccessibilitySelectedType() {
    return this.__chipAccessibilitySelectedType.get();
  }
  set chipAccessibilitySelectedType(o4) {
    this.__chipAccessibilitySelectedType.set(o4);
  }
  get chipAccessibilityDescription() {
    return this.__chipAccessibilityDescription.get();
  }
  set chipAccessibilityDescription(n4) {
    this.__chipAccessibilityDescription.set(n4);
  }
  get chipAccessibilityLevel() {
    return this.__chipAccessibilityLevel.get();
  }
  set chipAccessibilityLevel(m4) {
    this.__chipAccessibilityLevel.set(m4);
  }
  get isHover() {
    return this.__isHover.get();
  }
  set isHover(l4) {
    this.__isHover.set(l4);
  }
  get chipScale() {
    return this.__chipScale.get();
  }
  set chipScale(k4) {
    this.__chipScale.set(k4);
  }
  get chipOpacity() {
    return this.__chipOpacity.get();
  }
  set chipOpacity(j4) {
    this.__chipOpacity.set(j4);
  }
  get chipBlendColor() {
    return this.__chipBlendColor.get();
  }
  set chipBlendColor(i4) {
    this.__chipBlendColor.set(i4);
  }
  get deleteChip() {
    return this.__deleteChip.get();
  }
  set deleteChip(h4) {
    this.__deleteChip.set(h4);
  }
  get chipNodeOnFocus() {
    return this.__chipNodeOnFocus.get();
  }
  set chipNodeOnFocus(g4) {
    this.__chipNodeOnFocus.set(g4);
  }
  get useDefaultSuffixIcon() {
    return this.__useDefaultSuffixIcon.get();
  }
  set useDefaultSuffixIcon(f4) {
    this.__useDefaultSuffixIcon.set(f4);
  }
  get suffixIconOnFocus() {
    return this.__suffixIconOnFocus.get();
  }
  set suffixIconOnFocus(e4) {
    this.__suffixIconOnFocus.set(e4);
  }
  get chipBreakPoints() {
    return this.__chipBreakPoints.get();
  }
  set chipBreakPoints(d4) {
    this.__chipBreakPoints.set(d4);
  }
  get isShowPressedBackGroundColor() {
    return this.__isShowPressedBackGroundColor.get();
  }
  set isShowPressedBackGroundColor(c4) {
    this.__isShowPressedBackGroundColor.set(c4);
  }
  get fontSizeScale() {
    return this.__fontSizeScale.get();
  }
  set fontSizeScale(b4) {
    this.__fontSizeScale.set(b4);
  }
  get fontWeightScale() {
    return this.__fontWeightScale.get();
  }
  set fontWeightScale(a4) {
    this.__fontWeightScale.set(a4);
  }
  get prefixSymbolWidth() {
    return this.__prefixSymbolWidth.get();
  }
  set prefixSymbolWidth(z3) {
    this.__prefixSymbolWidth.set(z3);
  }
  get suffixSymbolWidth() {
    return this.__suffixSymbolWidth.get();
  }
  set suffixSymbolWidth(y3) {
    this.__suffixSymbolWidth.set(y3);
  }
  get allowCloseSymbolWidth() {
    return this.__allowCloseSymbolWidth.get();
  }
  set allowCloseSymbolWidth(x3) {
    this.__allowCloseSymbolWidth.set(x3);
  }
  get symbolEffect() {
    return this.__symbolEffect.get();
  }
  set symbolEffect(w3) {
    this.__symbolEffect.set(w3);
  }
  isChipSizeEnum() {
    return typeof this.chipSize === 'string';
  }
  isShowCloseIconMargin() {
    return (
      this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 0 &&
      this.allowClose
    );
  }
  getLabelFontSize() {
    if (
      this.label?.fontSize !== void 0 &&
      this.toVp(this.label.fontSize) >= 0
    ) {
      return this.label.fontSize;
    } else {
      if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
        try {
          resourceManager
            .getSystemResourceManager()
            .getNumberByName(
              this.theme.label.smallFontSize.params[0].split('.')[2]
            );
          return this.theme.label.smallFontSize;
        } catch (v3) {
          return this.theme.label.defaultFontSize;
        }
      } else {
        try {
          resourceManager
            .getSystemResourceManager()
            .getNumberByName(
              this.theme.label.normalFontSize.params[0].split('.')[2]
            );
          return this.theme.label.normalFontSize;
        } catch (u3) {
          return this.theme.label.defaultFontSize;
        }
      }
    }
  }
  defaultSymbolFontsize() {
    return this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL
      ? this.theme.defaultSymbol.smallSymbolFontSize
      : this.theme.defaultSymbol.normalSymbolFontSize;
  }
  resourceToVp(s3) {
    let t3 = LengthMetrics.resource(s3);
    return this.lengthMetricsToVp(t3);
  }
  getActiveFontColor() {
    return this.chipNodeOnFocus
      ? this.theme.label.focusActiveFontColor
      : this.theme.label.activatedFontColor;
  }
  getFontColor() {
    return this.chipNodeOnFocus
      ? this.theme.label.focusFontColor
      : this.theme.label.fontColor;
  }
  getLabelFontColor() {
    if (this.getChipActive()) {
      return this.label?.activatedFontColor ?? this.getActiveFontColor();
    }
    return this.label?.fontColor ?? this.getFontColor();
  }
  getLabelFontFamily() {
    return this.label?.fontFamily ?? this.theme.label.fontFamily;
  }
  getLabelFontWeight() {
    if (this.getChipActive()) {
      return FontWeight.Medium;
    }
    return this.resourceToNumber(
      this.theme.label.fontWeight,
      FontWeight.Regular
    );
  }
  lengthMetricsToVp(q3) {
    let r3 = 0;
    if (q3) {
      switch (q3.unit) {
        case LengthUnit.PX:
          return px2vp(q3.value);
        case LengthUnit.VP:
          return q3.value;
        case LengthUnit.FP:
          return px2vp(fp2px(q3.value));
        case LengthUnit.PERCENT:
          return Number.NEGATIVE_INFINITY;
        case LengthUnit.LPX:
          return px2vp(lpx2px(q3.value));
      }
    }
    return r3;
  }
  toVp(j3) {
    if (j3 === void 0) {
      return Number.NEGATIVE_INFINITY;
    }
    switch (typeof j3) {
      case 'number':
        return j3;
      case 'object':
        try {
          let p3 = this.lengthMetricsToVp(LengthMetrics.resource(j3));
          if (p3 === 0 && !isValidResource(getContext(this), j3)) {
            return Number.NEGATIVE_INFINITY;
          }
          return p3;
        } catch (o3) {
          return Number.NEGATIVE_INFINITY;
        }
      case 'string':
        let k3 = new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i');
        let l3 = j3.match(k3);
        if (!l3) {
          return Number.NEGATIVE_INFINITY;
        }
        let m3 = Number(l3?.[1] ?? 0);
        let n3 = l3?.[2] ?? 'vp';
        switch (n3.toLowerCase()) {
          case 'px':
            m3 = px2vp(m3);
            break;
          case 'fp':
            m3 = px2vp(fp2px(m3));
            break;
          case 'lpx':
            m3 = px2vp(lpx2px(m3));
            break;
          case '%':
            m3 = Number.NEGATIVE_INFINITY;
            break;
          case 'vp':
            break;
          default:
            break;
        }
        return m3;
      default:
        return Number.NEGATIVE_INFINITY;
    }
  }
  getChipNodeBorderWidth() {
    return this.resourceToVp(this.theme.chipNode.defaultBorderWidth);
  }
  getChipNodeBorderColor() {
    let i3 = this.theme.chipNode;
    return this.getChipActive() ? i3.activatedBorderColor : i3.borderColor;
  }
  getLabelMargin() {
    let h3 = { left: 0, right: 0 };
    if (
      this.label?.labelMargin?.left !== void 0 &&
      this.toVp(this.label.labelMargin.left) >= 0
    ) {
      h3.left = this.label?.labelMargin?.left;
    } else if (
      this.prefixSymbol?.normal ||
      this.prefixSymbol?.activated ||
      this.prefixIcon?.src
    ) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        h3.left = this.theme.label.smallMargin.left;
      } else {
        h3.left = this.theme.label.normalMargin.left;
      }
    }
    if (
      this.label?.labelMargin?.right !== void 0 &&
      this.toVp(this.label.labelMargin.right) >= 0
    ) {
      h3.right = this.label?.labelMargin?.right;
    } else if (
      this.suffixSymbol?.normal ||
      this.suffixSymbol?.activated ||
      this.suffixIcon?.src ||
      this.useDefaultSuffixIcon
    ) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        h3.right = this.theme.label.smallMargin.right;
      } else {
        h3.right = this.theme.label.normalMargin.right;
      }
    }
    return h3;
  }
  getLocalizedLabelMargin() {
    let g3 = { start: LengthMetrics.vp(0), end: LengthMetrics.vp(0) };
    if (
      this.label?.localizedLabelMargin?.start?.value !== void 0 &&
      this.lengthMetricsToVp(this.label.localizedLabelMargin.start) >= 0
    ) {
      g3.start = this.label?.localizedLabelMargin?.start;
    } else if (
      this.prefixSymbol?.normal ||
      this.prefixSymbol?.activated ||
      this.prefixIcon?.src
    ) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        g3.start = this.theme.label.localizedSmallMargin.start;
      } else {
        g3.start = this.theme.label.localizedNormalMargin.start;
      }
    }
    if (
      this.label?.localizedLabelMargin?.end?.value !== void 0 &&
      this.lengthMetricsToVp(this.label.localizedLabelMargin.end) >= 0
    ) {
      g3.end = this.label?.localizedLabelMargin?.end;
    } else if (
      this.suffixSymbol?.normal ||
      this.suffixSymbol?.activated ||
      this.suffixIcon?.src ||
      this.useDefaultSuffixIcon ||
      this.isShowCloseIconMargin()
    ) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        g3.end = this.theme.label.localizedSmallMargin.end;
      } else {
        g3.end = this.theme.label.localizedNormalMargin.end;
      }
    }
    return g3;
  }
  getLabelStartEndVp() {
    let e3 = this.getLocalizedLabelMargin();
    if (
      this.label &&
      this.label.labelMargin !== void 0 &&
      this.label.localizedLabelMargin === void 0
    ) {
      let f3 = this.getLabelMargin();
      return {
        start: LengthMetrics.vp(this.toVp(f3.left)),
        end: LengthMetrics.vp(this.toVp(f3.right)),
      };
    }
    return {
      start: LengthMetrics.vp(this.lengthMetricsToVp(e3.start)),
      end: LengthMetrics.vp(this.lengthMetricsToVp(e3.end)),
    };
  }
  getActualLabelMargin() {
    let d3 = this.getLocalizedLabelMargin();
    if (this.label && this.label.localizedLabelMargin !== void 0) {
      return d3;
    }
    if (this.label && this.label.labelMargin !== void 0) {
      return this.getLabelMargin();
    }
    return d3;
  }
  getSuffixIconSize() {
    let c3 = { width: 0, height: 0 };
    if (
      this.suffixIcon?.size?.width !== void 0 &&
      this.toVp(this.suffixIcon?.size?.width) >= 0
    ) {
      c3.width = this.suffixIcon?.size?.width;
    } else {
      if (this.getSuffixIconSrc()) {
        c3.width =
          this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL
            ? this.theme.suffixIcon.smallSize.width
            : this.theme.suffixIcon.normalSize.width;
      } else {
        c3.width = 0;
      }
    }
    if (
      this.suffixIcon?.size?.height !== void 0 &&
      this.toVp(this.suffixIcon?.size?.height) >= 0
    ) {
      c3.height = this.suffixIcon?.size?.height;
    } else {
      if (this.getSuffixIconSrc()) {
        c3.height =
          this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL
            ? this.theme.suffixIcon.smallSize.height
            : this.theme.suffixIcon.normalSize.height;
      } else {
        c3.height = 0;
      }
    }
    return c3;
  }
  getPrefixIconSize() {
    let b3 = { width: 0, height: 0 };
    if (
      this.prefixIcon?.size?.width !== void 0 &&
      this.toVp(this.prefixIcon?.size?.width) >= 0
    ) {
      b3.width = this.prefixIcon?.size?.width;
    } else {
      if (this.prefixIcon?.src) {
        b3.width =
          this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL
            ? this.theme.prefixIcon.smallSize.width
            : this.theme.prefixIcon.normalSize.width;
      } else {
        b3.width = 0;
      }
    }
    if (
      this.prefixIcon?.size?.height !== void 0 &&
      this.toVp(this.prefixIcon?.size?.height) >= 0
    ) {
      b3.height = this.prefixIcon?.size?.height;
    } else {
      if (this.prefixIcon?.src) {
        b3.height =
          this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL
            ? this.theme.prefixIcon.smallSize.height
            : this.theme.prefixIcon.normalSize.height;
      } else {
        b3.height = 0;
      }
    }
    return b3;
  }
  getDefaultActiveIconColor(a3) {
    if (a3 === IconType.PREFIX_ICON) {
      return this.chipNodeOnFocus
        ? this.theme.prefixIcon.focusActivatedColor
        : this.theme.prefixIcon.activatedFillColor;
    } else {
      return this.chipNodeOnFocus
        ? this.theme.suffixIcon.focusActivatedColor
        : this.theme.suffixIcon.activatedFillColor;
    }
  }
  getDefaultFillIconColor(z2) {
    if (z2 === IconType.PREFIX_ICON) {
      return this.chipNodeOnFocus
        ? this.theme.prefixIcon.focusFillColor
        : this.theme.prefixIcon.fillColor;
    } else {
      return this.chipNodeOnFocus
        ? this.theme.suffixIcon.focusFillColor
        : this.theme.suffixIcon.fillColor;
    }
  }
  getSymbolActiveColor(y2) {
    if (y2 === IconType.PREFIX_SYMBOL) {
      return this.getColorArray(
        this.prefixIcon?.activatedFillColor,
        this.theme.prefixIcon.focusActivatedColor,
        this.theme.prefixIcon.activatedFillColor
      );
    } else if (y2 === IconType.SUFFIX_SYMBOL) {
      return this.getColorArray(
        this.suffixIcon?.activatedFillColor,
        this.theme.suffixIcon.focusActivatedColor,
        this.theme.suffixIcon.activatedFillColor
      );
    } else {
      return this.theme.defaultSymbol.activatedFontColor;
    }
  }
  getSymbolFillColor(x2) {
    if (x2 === IconType.PREFIX_SYMBOL) {
      return this.getColorArray(
        this.prefixIcon?.fillColor,
        this.theme.prefixIcon.focusFillColor,
        this.theme.prefixIcon.fillColor
      );
    } else if (x2 === IconType.SUFFIX_SYMBOL) {
      return this.getColorArray(
        this.suffixIcon?.fillColor,
        this.theme.suffixIcon.focusFillColor,
        this.theme.suffixIcon.fillColor
      );
    } else {
      return this.theme.defaultSymbol.normalFontColor;
    }
  }
  getColorArray(u2, v2, w2) {
    if (u2) {
      return [u2];
    }
    return this.chipNodeOnFocus ? [v2] : [w2];
  }
  getPrefixIconFilledColor() {
    if (this.getChipActive()) {
      return (
        this.prefixIcon?.activatedFillColor ??
        this.getDefaultActiveIconColor(IconType.PREFIX_ICON)
      );
    }
    return (
      this.prefixIcon?.fillColor ??
      this.getDefaultFillIconColor(IconType.PREFIX_ICON)
    );
  }
  getSuffixIconFilledColor() {
    if (this.getChipActive()) {
      return (
        this.suffixIcon?.activatedFillColor ??
        this.getDefaultActiveIconColor(IconType.SUFFIX_ICON)
      );
    }
    return (
      this.suffixIcon?.fillColor ??
      this.getDefaultFillIconColor(IconType.SUFFIX_ICON)
    );
  }
  getDefaultSymbolColor(t2) {
    if (this.getChipActive()) {
      return this.getSymbolActiveColor(t2);
    }
    return this.getSymbolFillColor(t2);
  }
  getPrefixSymbolModifier() {
    if (this.getChipActive()) {
      return this.prefixSymbol?.activated;
    }
    return this.prefixSymbol?.normal;
  }
  getSuffixSymbolModifier() {
    if (this.getChipActive()) {
      return this.suffixSymbol?.activated;
    }
    return this.suffixSymbol?.normal;
  }
  getSuffixIconFocusable() {
    return (
      !this.isSuffixIconFocusStyleCustomized &&
      ((this.useDefaultSuffixIcon && (this.allowClose ?? true)) ||
        this.suffixIcon?.action !== void 0)
    );
  }
  getChipNodePadding() {
    return this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL
      ? this.theme.chipNode.localizedSmallPadding
      : this.theme.chipNode.localizedNormalPadding;
  }
  getChipNodeRadius() {
    if (this.chipNodeRadius !== void 0 && this.toVp(this.chipNodeRadius) >= 0) {
      return this.chipNodeRadius;
    } else {
      return this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL
        ? this.theme.chipNode.smallBorderRadius
        : this.theme.chipNode.normalBorderRadius;
    }
  }
  getChipNodeBackGroundColor() {
    let p2;
    let q2 = this.theme.chipNode;
    if (this.getChipActive()) {
      p2 =
        this.chipNodeOnFocus && !this.isSetActiveChipBgColor()
          ? q2.focusActivatedBgColor
          : this.chipNodeActivatedBackgroundColor ??
            this.theme.chipNode.activatedBackgroundColor;
    } else {
      p2 =
        this.chipNodeOnFocus && !this.isSetNormalChipBgColor()
          ? q2.focusBgColor
          : this.chipNodeBackgroundColor ?? this.theme.chipNode.backgroundColor;
    }
    let r2;
    try {
      r2 = ColorMetrics.resourceColor(p2);
    } catch (s2) {
      hilog.error(0x3900, 'Ace', `Chip resourceColor, error: ${s2.toString()}`);
      r2 = ColorMetrics.resourceColor(Color.Transparent);
    }
    if (!this.isShowPressedBackGroundColor) {
      return r2.color;
    }
    return r2.blendColor(ColorMetrics.resourceColor('#19000000')).color;
  }
  getChipNodeHeight() {
    if (this.isChipSizeEnum()) {
      return this.chipSize === ChipSize.SMALL
        ? this.theme.chipNode.smallHeight
        : this.theme.chipNode.normalHeight;
    } else {
      this.chipNodeSize = this.chipSize;
      return this.chipNodeSize?.height !== void 0 &&
        this.toVp(this.chipNodeSize?.height) >= 0
        ? this.toVp(this.chipNodeSize?.height)
        : this.theme.chipNode.normalHeight;
    }
  }
  getLabelWidth() {
    return px2vp(
      measure.measureText({
        textContent: this.label?.text ?? '',
        fontSize: this.getLabelFontSize(),
        fontFamily: this.label?.fontFamily ?? this.theme.label.fontFamily,
        fontWeight: this.getLabelFontWeight(),
        maxLines: 1,
        overflow: TextOverflow.Ellipsis,
        textAlign: TextAlign.Center,
      })
    );
  }
  getCalculateChipNodeWidth() {
    let n2 = 0;
    let o2 = this.getLabelStartEndVp();
    n2 += this.getChipNodeBorderWidth() * 2;
    n2 += this.getChipNodePadding().start?.value ?? 0;
    n2 += this.toVp(this.getPrefixChipWidth());
    n2 += this.toVp(o2.start?.value ?? 0);
    n2 += this.getLabelWidth();
    n2 += this.toVp(o2.end?.value ?? 0);
    n2 += this.toVp(this.getSuffixChipWidth());
    n2 += this.getChipNodePadding().end?.value ?? 0;
    return n2;
  }
  getPrefixChipWidth() {
    if (this.prefixSymbol?.normal || this.prefixSymbol?.activated) {
      return this.prefixSymbolWidth;
    } else if (this.prefixIcon?.src) {
      return this.getPrefixIconSize().width;
    } else {
      return 0;
    }
  }
  getSuffixChipWidth() {
    if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
      return this.suffixSymbolWidth;
    } else if (this.suffixIcon?.src) {
      return this.getSuffixIconSize().width;
    } else if (!this.suffixIcon?.src && (this.allowClose ?? true)) {
      return this.allowCloseSymbolWidth;
    } else {
      return 0;
    }
  }
  getReserveChipNodeWidth() {
    return (
      this.getCalculateChipNodeWidth() -
      this.getLabelWidth() +
      this.theme.chipNode.minLabelWidth
    );
  }
  getChipEnable() {
    return this.chipEnabled || this.chipEnabled === void 0;
  }
  getChipActive() {
    if (typeof this.chipActivated === 'undefined') {
      return false;
    }
    return this.chipActivated;
  }
  getChipNodeOpacity() {
    return this.chipOpacity;
  }
  handleTouch(m2) {
    if (!this.getChipEnable()) {
      return;
    }
    if (this.isHover) {
      if (m2.type === TouchType.Down || m2.type === TouchType.Move) {
        this.isShowPressedBackGroundColor = true;
      } else if (m2.type === TouchType.Up) {
        this.isShowPressedBackGroundColor = false;
      } else {
        this.isShowPressedBackGroundColor = false;
      }
    } else {
      if (m2.type === TouchType.Down || m2.type === TouchType.Move) {
        this.isShowPressedBackGroundColor = true;
      } else if (m2.type === TouchType.Up) {
        this.isShowPressedBackGroundColor = false;
      } else {
        this.isShowPressedBackGroundColor = false;
      }
    }
  }
  hoverAnimate(l2) {
    if (!this.getChipEnable()) {
      return;
    }
    this.isHover = l2;
    if (this.isHover) {
      this.isShowPressedBackGroundColor = true;
    } else {
      this.isShowPressedBackGroundColor = false;
    }
  }
  deleteChipNodeAnimate() {
    Context.animateTo({ duration: 150, curve: Curve.Sharp }, () => {
      this.chipOpacity = 0;
      this.chipBlendColor = Color.Transparent;
    });
    Context.animateTo(
      {
        duration: 150,
        curve: Curve.FastOutLinearIn,
        onFinish: () => {
          this.deleteChip = true;
        },
      },
      () => {
        this.chipScale = { x: 0.85, y: 0.85 };
      }
    );
  }
  getSuffixIconSrc() {
    this.useDefaultSuffixIcon =
      !this.suffixIcon?.src && (this.allowClose ?? true);
    return this.useDefaultSuffixIcon
      ? this.theme.suffixIcon.defaultDeleteIcon
      : this.suffixIcon?.src ?? void 0;
  }
  getChipNodeWidth() {
    if (!this.isChipSizeEnum()) {
      this.chipNodeSize = this.chipSize;
      if (
        this.chipNodeSize?.width !== void 0 &&
        this.toVp(this.chipNodeSize.width) >= 0
      ) {
        return this.toVp(this.chipNodeSize.width);
      }
    }
    let k2 = this.getChipConstraintWidth();
    return Math.min(
      Math.max(this.getCalculateChipNodeWidth(), k2.minWidth),
      k2.maxWidth
    );
  }
  getFocusOverlaySize() {
    return {
      width:
        Math.max(
          this.getChipNodeWidth(),
          this.getChipConstraintWidth().minWidth
        ) + 8,
      height: this.getChipNodeHeight() + 8,
    };
  }
  getChipConstraintWidth() {
    let h2 = this.getReserveChipNodeWidth();
    let i2 = this.getCalculateChipNodeWidth();
    let j2;
    switch (this.chipBreakPoints) {
      case BreakPointsType.SM:
        j2 = {
          minWidth: h2,
          maxWidth: Math.min(
            i2,
            this.theme.chipNode.breakPointConstraintWidth.breakPointSmMaxWidth
          ),
        };
        break;
      case BreakPointsType.MD:
        j2 = {
          minWidth: Math.max(
            i2,
            this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth
          ),
          maxWidth: Math.min(
            i2,
            this.theme.chipNode.breakPointConstraintWidth.breakPointMdMaxWidth
          ),
        };
        break;
      case BreakPointsType.LG:
        j2 = {
          minWidth: Math.max(
            i2,
            this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth
          ),
          maxWidth: Math.min(
            i2,
            this.theme.chipNode.breakPointConstraintWidth.breakPointLgMaxWidth
          ),
        };
        break;
      default:
        j2 = { minWidth: h2, maxWidth: i2 };
        break;
    }
    j2.minWidth = Math.min(
      Math.max(this.getCalculateChipNodeWidth(), j2.minWidth),
      j2.maxWidth
    );
    j2.minHeight = this.getChipNodeHeight();
    if (
      !this.isChipSizeEnum() &&
      this.chipNodeSize?.height !== void 0 &&
      this.toVp(this.chipNodeSize?.height) >= 0
    ) {
      j2.maxHeight = this.toVp(this.chipNodeSize.height);
      j2.minHeight = this.toVp(this.chipNodeSize.height);
    }
    if (
      !this.isChipSizeEnum() &&
      this.chipNodeSize?.width !== void 0 &&
      this.toVp(this.chipNodeSize?.width) >= 0
    ) {
      j2.minWidth = this.toVp(this.chipNodeSize.width);
      j2.maxWidth = this.toVp(this.chipNodeSize.width);
    } else if (
      this.toVp(this.fontSizeScale) >= this.theme.chipNode.suitAgeScale
    ) {
      j2.minWidth = void 0;
      j2.maxWidth = void 0;
    }
    return j2;
  }
  focusOverlay(z1 = null) {
    this.observeComponentCreation2((f2, g2) => {
      Stack.create();
      Stack.direction(this.chipDirection);
      Stack.size({ width: 1, height: 1 });
      Stack.align(Alignment.Center);
    }, Stack);
    this.observeComponentCreation2((a2, b2) => {
      If.create();
      if (this.chipNodeOnFocus && !this.suffixIconOnFocus) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((c2, d2) => {
            Stack.create();
            Stack.direction(this.chipDirection);
            Stack.borderRadius(this.toVp(this.getChipNodeRadius()) + 4);
            Stack.size(this.getFocusOverlaySize());
            Stack.borderColor(this.theme.chipNode.focusOutlineColor);
            Stack.borderWidth(this.theme.chipNode.borderWidth);
          }, Stack);
          Stack.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
      }
    }, If);
    If.pop();
    Stack.pop();
  }
  aboutToAppear() {
    let v1 = this.getUIContext();
    this.fontSizeScale = v1.getHostContext()?.config?.fontSizeScale ?? 1;
    this.smListener.on('change', (y1) => {
      if (y1.matches) {
        this.chipBreakPoints = BreakPointsType.SM;
      }
    });
    this.mdListener.on('change', (x1) => {
      if (x1.matches) {
        this.chipBreakPoints = BreakPointsType.MD;
      }
    });
    this.lgListener.on('change', (w1) => {
      if (w1.matches) {
        this.chipBreakPoints = BreakPointsType.LG;
      }
    });
    this.callbackId = this.getUIContext()
      .getHostContext()
      ?.getApplicationContext()
      ?.on('environment', this.callbacks);
  }
  getVisibility() {
    if (this.toVp(this.getChipNodeHeight()) > 0) {
      return Visibility.Visible;
    } else {
      return Visibility.None;
    }
  }
  isSetActiveChipBgColor() {
    if (!this.chipNodeActivatedBackgroundColor) {
      return false;
    }
    try {
      return (
        ColorMetrics.resourceColor(this.chipNodeActivatedBackgroundColor)
          .color !==
        ColorMetrics.resourceColor(this.theme.chipNode.activatedBackgroundColor)
          .color
      );
    } catch (u1) {
      console.error(`[Chip] failed to get resourceColor`);
      return false;
    }
  }
  isSetNormalChipBgColor() {
    if (!this.chipNodeBackgroundColor) {
      return false;
    }
    try {
      return (
        ColorMetrics.resourceColor(this.chipNodeBackgroundColor).color !==
        ColorMetrics.resourceColor(this.theme.chipNode.backgroundColor).color
      );
    } catch (t1) {
      console.error(`[Chip] failed to get resourceColor`);
      return false;
    }
  }
  getShadowStyles() {
    if (!this.chipNodeOnFocus) {
      return undefined;
    }
    return this.resourceToNumber(
      this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL
        ? this.theme.chipNode.smallShadowStyle
        : this.theme.chipNode.normalShadowStyle,
      -1
    );
  }
  aboutToDisappear() {
    this.smListener.off('change');
    this.mdListener.off('change');
    this.lgListener.off('change');
    if (this.callbackId) {
      this.getUIContext()
        ?.getHostContext()
        ?.getApplicationContext()
        ?.off('environment', this.callbackId);
      this.callbackId = void 0;
    }
  }
  chipBuilder(g = null) {
    this.observeComponentCreation2((m1, n1) => {
      Button.createWithChild();
      Button.constraintSize(this.getChipConstraintWidth());
      Button.direction(this.chipDirection);
      Button.type(ButtonType.Normal);
      Button.clip(false);
      Button.backgroundColor(this.getChipNodeBackGroundColor());
      Button.borderRadius(this.getChipNodeRadius());
      Button.borderWidth(this.getChipNodeBorderWidth());
      Button.borderColor(this.getChipNodeBorderColor());
      Button.enabled(this.getChipEnable());
      Button.scale(ObservedObject.GetRawObject(this.chipScale));
      Button.focusable(true);
      Button.opacity(this.getChipNodeOpacity());
      Button.shadow(this.getShadowStyles());
      Button.padding(0);
      Button.accessibilityGroup(true);
      Button.accessibilityDescription(this.getAccessibilityDescription());
      Button.accessibilityLevel(this.getAccessibilityLevel());
      Button.accessibilityChecked(this.getAccessibilityChecked());
      Button.accessibilitySelected(this.getAccessibilitySelected());
      Button.onFocus(() => {
        this.chipNodeOnFocus = true;
        if (this.isSuffixIconFocusStyleCustomized) {
          this.chipScale = {
            x: this.resourceToNumber(this.theme.chipNode.focusBtnScaleX, 1),
            y: this.resourceToNumber(this.theme.chipNode.focusBtnScaleY, 1),
          };
        }
      });
      Button.onBlur(() => {
        this.chipNodeOnFocus = false;
        if (this.isSuffixIconFocusStyleCustomized) {
          this.chipScale = {
            x: 1,
            y: 1,
          };
        }
      });
      Button.onTouch((s1) => {
        this.handleTouch(s1);
      });
      Button.onHover((r1) => {
        if (r1) {
          this.isShowPressedBackGroundColor = true;
        } else {
          if (!this.isShowPressedBackGroundColor && r1) {
            this.isShowPressedBackGroundColor = true;
          } else {
            this.isShowPressedBackGroundColor = false;
          }
        }
      });
      Button.onKeyEvent((o1) => {
        if (!o1 || o1.type === null || o1.type !== KeyType.Down) {
          return;
        }
        let p1 =
          o1.keyCode === KeyCode.KEYCODE_FORWARD_DEL && !this.suffixIconOnFocus;
        let q1 =
          o1.keyCode === KeyCode.KEYCODE_ENTER &&
          this.allowClose !== false &&
          !this.suffixIcon?.src &&
          this.isSuffixIconFocusStyleCustomized;
        if (p1 || q1) {
          this.deleteChipNodeAnimate();
        }
      });
      Button.onClick(
        this.onClicked === noop ? undefined : this.onClicked.bind(this)
      );
    }, Button);
    this.observeComponentCreation2((k1, l1) => {
      Row.create();
      Row.direction(this.chipDirection);
      Row.alignItems(VerticalAlign.Center);
      Row.justifyContent(FlexAlign.Center);
      Row.padding(this.getChipNodePadding());
      Row.constraintSize(this.getChipConstraintWidth());
    }, Row);
    this.observeComponentCreation2((c1, d1) => {
      If.create();
      if (this.prefixSymbol?.normal || this.prefixSymbol?.activated) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((g1, h1) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(this.defaultSymbolFontsize());
            SymbolGlyph.fontColor(
              this.getDefaultSymbolColor(IconType.PREFIX_SYMBOL)
            );
            SymbolGlyph.attributeModifier.bind(this)(
              this.getPrefixSymbolModifier()
            );
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(
              ObservedObject.GetRawObject(this.symbolEffect),
              false
            );
            SymbolGlyph.symbolEffect(
              ObservedObject.GetRawObject(this.symbolEffect),
              this.theme.defaultSymbol.defaultEffect
            );
            SymbolGlyph.onSizeChange((i1, j1) => {
              this.prefixSymbolWidth = j1?.width;
            });
            SymbolGlyph.key('PrefixSymbolGlyph');
          }, SymbolGlyph);
        });
      } else if (this.prefixIcon?.src !== '') {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((e1, f1) => {
            Image.create(this.prefixIcon?.src);
            Image.direction(this.chipDirection);
            Image.opacity(this.getChipNodeOpacity());
            Image.size(this.getPrefixIconSize());
            Image.fillColor(this.getPrefixIconFilledColor());
            Image.enabled(this.getChipEnable());
            Image.objectFit(ImageFit.Cover);
            Image.focusable(false);
            Image.flexShrink(0);
            Image.visibility(this.getVisibility());
            Image.draggable(false);
          }, Image);
        });
      } else {
        this.ifElseBranchUpdateFunction(2, () => {});
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((a1, b1) => {
      Text.create(this.label?.text ?? '');
      Text.direction(this.chipDirection);
      Text.opacity(this.getChipNodeOpacity());
      Text.fontSize(this.getLabelFontSize());
      Text.fontColor(this.getLabelFontColor());
      Text.fontFamily(this.getLabelFontFamily());
      Text.fontWeight(this.getLabelFontWeight());
      Text.margin(this.getActualLabelMargin());
      Text.enabled(this.getChipEnable());
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.flexShrink(1);
      Text.focusable(true);
      Text.textAlign(TextAlign.Center);
      Text.visibility(this.getVisibility());
      Text.draggable(false);
    }, Text);
    Text.pop();
    this.observeComponentCreation2((h, i) => {
      If.create();
      if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((y, z) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.onClick(this.getSuffixSymbolAction());
            Button.accessibilityText(this.getSuffixSymbolAccessibilityText());
            Button.accessibilityDescription(
              this.getSuffixSymbolAccessibilityDescription()
            );
            Button.accessibilityLevel(this.getSuffixSymbolAccessibilityLevel());
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius(0);
            Button.padding(0);
            Button.stateEffect(false);
            Button.focusable(!this.isSuffixIconFocusStyleCustomized);
          }, Button);
          this.observeComponentCreation2((u, v) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(this.defaultSymbolFontsize());
            SymbolGlyph.fontColor(
              this.getDefaultSymbolColor(IconType.SUFFIX_SYMBOL)
            );
            SymbolGlyph.attributeModifier.bind(this)(
              this.getSuffixSymbolModifier()
            );
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(
              ObservedObject.GetRawObject(this.symbolEffect),
              false
            );
            SymbolGlyph.symbolEffect(
              ObservedObject.GetRawObject(this.symbolEffect),
              this.theme.defaultSymbol.defaultEffect
            );
            SymbolGlyph.onSizeChange((w, x) => {
              this.suffixSymbolWidth = x?.width;
            });
            SymbolGlyph.key('SuffixSymbolGlyph');
          }, SymbolGlyph);
          Button.pop();
        });
      } else if (this.suffixIcon?.src !== '') {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((s, t) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius(0);
            Button.padding(0);
            Button.size(this.getSuffixIconSize());
            Button.accessibilityText(this.getSuffixIconAccessibilityText());
            Button.accessibilityDescription(
              this.getSuffixIconAccessibilityDescription()
            );
            Button.accessibilityLevel(this.getSuffixIconAccessibilityLevel());
            Button.onClick(() => {
              if (!this.getChipEnable()) {
                return;
              }
              if (this.suffixIcon?.action) {
                this.suffixIcon.action();
                return;
              }
              if ((this.allowClose ?? true) && this.useDefaultSuffixIcon) {
                this.onClose();
                this.deleteChipNodeAnimate();
                return;
              }
              this.onClicked();
            });
            Button.focusable(this.getSuffixIconFocusable());
          }, Button);
          this.observeComponentCreation2((q, r) => {
            Image.create(this.getSuffixIconSrc());
            Image.direction(this.chipDirection);
            Image.opacity(this.getChipNodeOpacity());
            Image.size(this.getSuffixIconSize());
            Image.fillColor(this.getSuffixIconFilledColor());
            Image.enabled(this.getChipEnable());
            Image.objectFit(ImageFit.Cover);
            Image.flexShrink(0);
            Image.visibility(this.getVisibility());
            Image.draggable(false);
            Image.onFocus(() => {
              this.suffixIconOnFocus = true;
            });
            Image.onBlur(() => {
              this.suffixIconOnFocus = false;
            });
          }, Image);
          Button.pop();
        });
      } else if (this.allowClose ?? true) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((o, p) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius(0);
            Button.padding(0);
            Button.accessibilityText(this.getCloseIconAccessibilityText());
            Button.accessibilityDescription(
              this.getCloseIconAccessibilityDescription()
            );
            Button.accessibilityLevel(this.getCloseIconAccessibilityLevel());
            Button.onClick(() => {
              if (!this.getChipEnable()) {
                return;
              }
              this.onClose();
              this.deleteChipNodeAnimate();
            });
            Button.focusable(!this.isSuffixIconFocusStyleCustomized);
          }, Button);
          this.observeComponentCreation2((j, k) => {
            SymbolGlyph.create({
              id: -1,
              type: 40000,
              params: ['sys.symbol.xmark'],
              bundleName: '__harDefaultBundleName__',
              moduleName: '__harDefaultModuleName__',
            });
            SymbolGlyph.fontSize(this.defaultSymbolFontsize());
            SymbolGlyph.fontColor(
              this.getDefaultSymbolColor(IconType.SUFFIX_SYMBOL)
            );
            SymbolGlyph.onSizeChange((m, n) => {
              this.allowCloseSymbolWidth = n?.width;
            });
            SymbolGlyph.key('AllowCloseSymbolGlyph');
          }, SymbolGlyph);
          Button.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(3, () => {});
      }
    }, If);
    If.pop();
    Row.pop();
    Button.pop();
  }
  getSuffixSymbolAccessibilityLevel() {
    if (this.getChipActive()) {
      if (
        this.suffixSymbolOptions?.activatedAccessibility?.accessibilityLevel ===
          'no' ||
        this.suffixSymbolOptions?.activatedAccessibility?.accessibilityLevel ===
          'no-hide-descendants'
      ) {
        return this.suffixSymbolOptions.activatedAccessibility
          .accessibilityLevel;
      }
      return this.suffixSymbolOptions?.action ? 'yes' : 'no';
    }
    if (
      this.suffixSymbolOptions?.normalAccessibility?.accessibilityLevel ===
        'no' ||
      this.suffixSymbolOptions?.normalAccessibility?.accessibilityLevel ===
        'no-hide-descendants'
    ) {
      return this.suffixSymbolOptions.normalAccessibility.accessibilityLevel;
    }
    return this.suffixSymbolOptions?.action ? 'yes' : 'no';
  }
  getSuffixSymbolAccessibilityDescription() {
    if (this.getChipActive()) {
      if (
        typeof this.suffixSymbolOptions?.activatedAccessibility
          ?.accessibilityDescription !== 'undefined'
      ) {
        return this.suffixSymbolOptions.activatedAccessibility
          .accessibilityDescription;
      }
      return undefined;
    }
    if (
      typeof this.suffixSymbolOptions?.normalAccessibility
        ?.accessibilityDescription !== 'undefined'
    ) {
      return this.suffixSymbolOptions.normalAccessibility
        .accessibilityDescription;
    }
    return undefined;
  }
  getSuffixSymbolAccessibilityText() {
    if (this.getChipActive()) {
      if (
        typeof this.suffixSymbolOptions?.activatedAccessibility
          ?.accessibilityText !== 'undefined'
      ) {
        return this.suffixSymbolOptions.activatedAccessibility
          .accessibilityText;
      }
      return undefined;
    }
    if (
      typeof this.suffixSymbolOptions?.normalAccessibility
        ?.accessibilityText !== 'undefined'
    ) {
      return this.suffixSymbolOptions.normalAccessibility.accessibilityText;
    }
    return undefined;
  }
  getSuffixSymbolAction() {
    if (typeof this.suffixSymbolOptions?.action === 'undefined') {
      return undefined;
    }
    return () => {
      if (!this.getChipEnable()) {
        return;
      }
      this.suffixSymbolOptions?.action?.();
    };
  }
  getAccessibilitySelected() {
    if (
      this.getChipAccessibilitySelectedType() ===
      AccessibilitySelectedType.SELECTED
    ) {
      return this.getChipActive();
    }
    return undefined;
  }
  getAccessibilityChecked() {
    if (
      this.getChipAccessibilitySelectedType() ===
      AccessibilitySelectedType.CHECKED
    ) {
      return this.getChipActive();
    }
    return undefined;
  }
  getChipAccessibilitySelectedType() {
    if (typeof this.chipActivated === 'undefined') {
      return AccessibilitySelectedType.CLICKED;
    }
    return (
      this.chipAccessibilitySelectedType ?? AccessibilitySelectedType.CHECKED
    );
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
      return undefined;
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
  getSuffixIconAccessibilityLevel() {
    if (
      this.suffixIcon?.accessibilityLevel === 'no' ||
      this.suffixIcon?.accessibilityLevel === 'no-hide-descendants'
    ) {
      return this.suffixIcon.accessibilityLevel;
    }
    return this.suffixIcon?.action ? 'yes' : 'no';
  }
  getSuffixIconAccessibilityDescription() {
    if (typeof this.suffixIcon?.accessibilityDescription === 'undefined') {
      return undefined;
    }
    return this.suffixIcon.accessibilityDescription;
  }
  getSuffixIconAccessibilityText() {
    if (typeof this.suffixIcon?.accessibilityText === 'undefined') {
      return undefined;
    }
    return this.suffixIcon.accessibilityText;
  }
  getAccessibilityLevel() {
    return this.chipAccessibilityLevel;
  }
  getAccessibilityDescription() {
    if (typeof this.chipAccessibilityDescription === 'undefined') {
      return undefined;
    }
    return this.chipAccessibilityDescription;
  }
  resourceToNumber(c, d) {
    if (!c || !c.type) {
      console.error('[Chip] failed: resource get fail.');
      return d;
    }
    const e = this.getUIContext().getHostContext()?.resourceManager;
    if (!e) {
      console.error('[Chip] failed to get resourceManager.');
      return d;
    }
    switch (c.type) {
      case RESOURCE_TYPE_FLOAT:
      case RESOURCE_TYPE_INTEGER:
        try {
          if (c.id !== -1) {
            return e.getNumber(c);
          }
          return e.getNumberByName(c.params[0].split('.')[2]);
        } catch (f) {
          console.error(`[Chip] get resource error, return defaultValue`);
          return d;
        }
      default:
        return d;
    }
  }
  initialRender() {
    this.observeComponentCreation2((a, b) => {
      If.create();
      if (!this.deleteChip) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.chipBuilder.bind(this)();
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

export default {
  Chip,
  ChipSize,
  AccessibilitySelectedType,
};
