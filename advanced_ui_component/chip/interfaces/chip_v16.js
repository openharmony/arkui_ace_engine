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
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const mediaquery = requireNapi('mediaquery');

export var ChipSize;
(function (i4) {
    i4['NORMAL'] = 'NORMAL';
    i4['SMALL'] = 'SMALL';
})(ChipSize || (ChipSize = {}));
var IconType;
(function (h4) {
    h4['PREFIX_ICON'] = 'PREFIXICON';
    h4['SUFFIX_ICON'] = 'SUFFIXICON';
    h4['PREFIX_SYMBOL'] = 'PREFIXSYMBOL';
    h4['SUFFIX_SYMBOL'] = 'SUFFIXSYMBOL';
})(IconType || (IconType = {}));
var BreakPointsType;
(function (g4) {
    g4['SM'] = 'SM';
    g4['MD'] = 'MD';
    g4['LG'] = 'LG';
})(BreakPointsType || (BreakPointsType = {}));

export var AccessibilitySelectedType;
(function (f4) {
    f4[f4['CLICKED'] = 0] = 'CLICKED';
    f4[f4['CHECKED'] = 1] = 'CHECKED';
    f4[f4['SELECTED'] = 2] = 'SELECTED';
})(AccessibilitySelectedType || (AccessibilitySelectedType = {}));
const RESOURCE_TYPE_STRING = 10003;
const RESOURCE_TYPE_FLOAT = 10002;
const RESOURCE_TYPE_INTEGER = 10007;

export function Chip(x3, y3 = null) {
    const z3 = x3;
    {
        (y3 ? y3 : this).observeComponentCreation2((a4, b4, c4 = z3) => {
            if (b4) {
                let d4 = new ChipComponent(y3 ? y3 : this, {
                    chipSize: c4.size,
                    prefixIcon: c4.prefixIcon,
                    prefixSymbol: c4.prefixSymbol,
                    label: c4.label,
                    suffixIcon: c4.suffixIcon,
                    suffixSymbol: c4.suffixSymbol,
                    suffixSymbolOptions: c4.suffixSymbolOptions,
                    allowClose: c4.allowClose,
                    closeOptions: c4.closeOptions,
                    chipEnabled: c4.enabled,
                    chipActivated: c4.activated,
                    chipNodeBackgroundColor: c4.backgroundColor,
                    chipNodeActivatedBackgroundColor: c4.activatedBackgroundColor,
                    chipNodeRadius: c4.borderRadius,
                    chipDirection: c4.direction,
                    chipAccessibilitySelectedType: c4.accessibilitySelectedType,
                    chipAccessibilityDescription: c4.accessibilityDescription,
                    chipAccessibilityLevel: c4.accessibilityLevel,
                    onClose: c4.onClose,
                    onClicked: c4.onClicked,
                }, undefined, a4, () => {
                }, { page: 'library/src/main/ets/components/chip_v16.ets', line: 224, col: 3 });
                ViewPU.create(d4);
                let e4 = () => {
                    return {
                        chipSize: c4.size,
                        prefixIcon: c4.prefixIcon,
                        prefixSymbol: c4.prefixSymbol,
                        label: c4.label,
                        suffixIcon: c4.suffixIcon,
                        suffixSymbol: c4.suffixSymbol,
                        suffixSymbolOptions: c4.suffixSymbolOptions,
                        allowClose: c4.allowClose,
                        closeOptions: c4.closeOptions,
                        chipEnabled: c4.enabled,
                        chipActivated: c4.activated,
                        chipNodeBackgroundColor: c4.backgroundColor,
                        chipNodeActivatedBackgroundColor: c4.activatedBackgroundColor,
                        chipNodeRadius: c4.borderRadius,
                        chipDirection: c4.direction,
                        chipAccessibilitySelectedType: c4.accessibilitySelectedType,
                        chipAccessibilityDescription: c4.accessibilityDescription,
                        chipAccessibilityLevel: c4.accessibilityLevel,
                        onClose: c4.onClose,
                        onClicked: c4.onClicked
                    };
                };
                d4.paramsGenerator_ = e4;
            } else {
                (y3 ? y3 : this).updateStateVarsOfChildByElmtId(a4, {
                    chipSize: c4.size,
                    prefixIcon: c4.prefixIcon,
                    prefixSymbol: c4.prefixSymbol,
                    label: c4.label,
                    suffixIcon: c4.suffixIcon,
                    suffixSymbol: c4.suffixSymbol,
                    suffixSymbolOptions: c4.suffixSymbolOptions,
                    allowClose: c4.allowClose,
                    closeOptions: c4.closeOptions,
                    chipEnabled: c4.enabled,
                    chipActivated: c4.activated,
                    chipNodeBackgroundColor: c4.backgroundColor,
                    chipNodeActivatedBackgroundColor: c4.activatedBackgroundColor,
                    chipNodeRadius: c4.borderRadius,
                    chipDirection: c4.direction,
                    chipAccessibilitySelectedType: c4.accessibilitySelectedType,
                    chipAccessibilityDescription: c4.accessibilityDescription,
                    chipAccessibilityLevel: c4.accessibilityLevel
                });
            }
        }, { name: 'ChipComponent' });
    }
}

export class ChipComponent extends ViewPU {
    constructor(q3, r3, s3, t3 = -1, u3 = undefined, v3) {
        super(q3, s3, t3, v3);
        if (typeof u3 === 'function') {
            this.paramsGenerator_ = u3;
        }
        this.theme = {
            prefixIcon: {
                normalSize: {
                    width: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_normal_icon_size'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    },
                    height: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_normal_icon_size'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }
                },
                smallSize: {
                    width: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_small_icon_size'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    },
                    height: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_small_icon_size'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }
                },
                fillColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_usually_icon_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                activatedFillColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_active_icon_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                focusFillColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_icon_focus_fill'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                focusActivatedColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_icon_activated_focus_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            },
            label: {
                normalFontSize: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_normal_font_size'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                smallFontSize: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_small_font_size'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                focusFontColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_focus_text'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                focusActiveFontColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_activated_focus_font_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                fontColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_font_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                activatedFontColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_activated_fontcolor'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                fontFamily: 'HarmonyOS Sans',
                fontWeight: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_text_font_weight'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                normalMargin: {
                    left: 6,
                    right: 6,
                    top: 0,
                    bottom: 0
                },
                smallMargin: {
                    left: 4,
                    right: 4,
                    top: 0,
                    bottom: 0
                },
                defaultFontSize: 14,
                localizedNormalMargin: {
                    start: LengthMetrics.resource({
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_normal_text_margin'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }),
                    end: LengthMetrics.resource({
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_normal_text_margin'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }),
                    top: LengthMetrics.vp(0),
                    bottom: LengthMetrics.vp(0)
                },
                localizedSmallMargin: {
                    start: LengthMetrics.resource({
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_small_text_margin'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }),
                    end: LengthMetrics.resource({
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_small_text_margin'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }),
                    top: LengthMetrics.vp(0),
                    bottom: LengthMetrics.vp(0),
                }
            },
            suffixIcon: {
                normalSize: {
                    width: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_normal_icon_size'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    },
                    height: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_normal_icon_size'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }
                },
                smallSize: {
                    width: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_small_icon_size'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    },
                    height: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_small_icon_size'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }
                },
                fillColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_usually_icon_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                activatedFillColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_active_icon_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                focusFillColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_icon_focus_fill'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                focusActivatedColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_icon_activated_focus_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                defaultDeleteIcon: {
                    'id': -1,
                    'type': 20000,
                    params: ['sys.media.ohos_ic_public_cancel', 16, 16],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                focusable: false,
                isShowMargin: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_show_close_icon_margin'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            },
            defaultSymbol: {
                normalFontColor: [{
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_usually_icon_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }],
                activatedFontColor: [{
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_active_icon_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }],
                normalSymbolFontSize: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_normal_icon_size'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }).value,
                smallSymbolFontSize: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_small_icon_size'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }).value,
                defaultEffect: -1,
            },
            chipNode: {
                suitAgeScale: 1.75,
                minLabelWidth: 12,
                normalHeight: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_normal_height'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                smallHeight: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_small_height'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                enabled: true,
                activated: false,
                backgroundColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_background_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                activatedBackgroundColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_container_activated_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                focusOutlineColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_focused_outline'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                focusOutlineMargin: 2,
                borderColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_border_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                defaultBorderWidth: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_border_width'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                activatedBorderColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_activated_border_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                normalBorderRadius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_border_radius_normal'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                smallBorderRadius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_border_radius_small'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                borderWidth: 2,
                focusBtnScaleX: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_focused_btn_scale'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                focusBtnScaleY: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_focused_btn_scale'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                localizedNormalPadding: {
                    start: LengthMetrics.resource({
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_normal_text_padding'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }),
                    end: LengthMetrics.resource({
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_normal_text_padding'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }),
                    top: LengthMetrics.vp(4),
                    bottom: LengthMetrics.vp(4)
                },
                localizedSmallPadding: {
                    start: LengthMetrics.resource({
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_small_text_padding'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }),
                    end: LengthMetrics.resource({
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.chip_small_text_padding'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }),
                    top: LengthMetrics.vp(4),
                    bottom: LengthMetrics.vp(4)
                },
                hoverBlendColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_hover_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                pressedBlendColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_press_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                focusBgColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_focus_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                focusActivatedBgColor: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.chip_container_activated_focus_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                opacity: { normal: 1, hover: 0.95, pressed: 0.9 },
                normalShadowStyle: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_normal_shadow_style'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                smallShadowStyle: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.chip_small_shadow_style'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                breakPointConstraintWidth: {
                    breakPointMinWidth: 128,
                    breakPointSmMaxWidth: 156,
                    breakPointMdMaxWidth: 280,
                    breakPointLgMaxWidth: 400
                }
            }
        };
        this.__chipSize = new SynchedPropertyObjectOneWayPU(r3.chipSize, this, 'chipSize');
        this.__allowClose = new SynchedPropertySimpleOneWayPU(r3.allowClose, this, 'allowClose');
        this.__closeOptions = new SynchedPropertyObjectOneWayPU(r3.closeOptions, this, 'closeOptions');
        this.__chipDirection = new SynchedPropertySimpleOneWayPU(r3.chipDirection, this, 'chipDirection');
        this.__prefixIcon = new SynchedPropertyObjectOneWayPU(r3.prefixIcon, this, 'prefixIcon');
        this.__prefixSymbol = new SynchedPropertyObjectOneWayPU(r3.prefixSymbol, this, 'prefixSymbol');
        this.__label = new SynchedPropertyObjectOneWayPU(r3.label, this, 'label');
        this.__suffixIcon = new SynchedPropertyObjectOneWayPU(r3.suffixIcon, this, 'suffixIcon');
        this.__suffixSymbol = new SynchedPropertyObjectOneWayPU(r3.suffixSymbol, this, 'suffixSymbol');
        this.__suffixSymbolOptions =
            new SynchedPropertyObjectOneWayPU(r3.suffixSymbolOptions, this, 'suffixSymbolOptions');
        this.__chipNodeBackgroundColor =
            new SynchedPropertyObjectOneWayPU(r3.chipNodeBackgroundColor, this, 'chipNodeBackgroundColor');
        this.__chipNodeActivatedBackgroundColor =
            new SynchedPropertyObjectOneWayPU(r3.chipNodeActivatedBackgroundColor, this,
                'chipNodeActivatedBackgroundColor');
        this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(r3.chipNodeRadius, this, 'chipNodeRadius');
        this.__chipEnabled = new SynchedPropertySimpleOneWayPU(r3.chipEnabled, this, 'chipEnabled');
        this.__chipActivated = new SynchedPropertySimpleOneWayPU(r3.chipActivated, this, 'chipActivated');
        this.__chipAccessibilitySelectedType =
            new SynchedPropertySimpleOneWayPU(r3.chipAccessibilitySelectedType, this, 'chipAccessibilitySelectedType');
        this.__chipAccessibilityDescription =
            new SynchedPropertyObjectOneWayPU(r3.chipAccessibilityDescription, this, 'chipAccessibilityDescription');
        this.__chipAccessibilityLevel =
            new SynchedPropertySimpleOneWayPU(r3.chipAccessibilityLevel, this, 'chipAccessibilityLevel');
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
            onConfigurationUpdated: (w3) => {
                this.fontSizeScale = w3.fontSizeScale ?? 1;
            },
            onMemoryLevel() {
            }
        };
        this.setInitiallyProvidedValue(r3);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(p3) {
        if (p3.theme !== undefined) {
            this.theme = p3.theme;
        }
        if (p3.chipSize === undefined) {
            this.__chipSize.set(ChipSize.NORMAL);
        }
        if (p3.chipDirection === undefined) {
            this.__chipDirection.set(Direction.Auto);
        }
        if (p3.chipEnabled === undefined) {
            this.__chipEnabled.set(true);
        }
        if (p3.isChipExist !== undefined) {
            this.isChipExist = p3.isChipExist;
        }
        if (p3.chipScale !== undefined) {
            this.chipScale = p3.chipScale;
        }
        if (p3.chipOpacity !== undefined) {
            this.chipOpacity = p3.chipOpacity;
        }
        if (p3.suffixSymbolHeight !== undefined) {
            this.suffixSymbolHeight = p3.suffixSymbolHeight;
        }
        if (p3.suffixSymbolWidth !== undefined) {
            this.suffixSymbolWidth = p3.suffixSymbolWidth;
        }
        if (p3.breakPoint !== undefined) {
            this.breakPoint = p3.breakPoint;
        }
        if (p3.fontSizeScale !== undefined) {
            this.fontSizeScale = p3.fontSizeScale;
        }
        if (p3.isSuffixIconFocusStyleCustomized !== undefined) {
            this.isSuffixIconFocusStyleCustomized = p3.isSuffixIconFocusStyleCustomized;
        }
        if (p3.isSuffixIconFocusable !== undefined) {
            this.isSuffixIconFocusable = p3.isSuffixIconFocusable;
        }
        if (p3.onClose !== undefined) {
            this.onClose = p3.onClose;
        }
        if (p3.onClicked !== undefined) {
            this.onClicked = p3.onClicked;
        }
        if (p3.chipNodeInFocus !== undefined) {
            this.chipNodeInFocus = p3.chipNodeInFocus;
        }
        if (p3.smListener !== undefined) {
            this.smListener = p3.smListener;
        }
        if (p3.mdListener !== undefined) {
            this.mdListener = p3.mdListener;
        }
        if (p3.lgListener !== undefined) {
            this.lgListener = p3.lgListener;
        }
        if (p3.symbolEffect !== undefined) {
            this.symbolEffect = p3.symbolEffect;
        }
        if (p3.environmentCallbackID !== undefined) {
            this.environmentCallbackID = p3.environmentCallbackID;
        }
        if (p3.environmentCallback !== undefined) {
            this.environmentCallback = p3.environmentCallback;
        }
    }

    updateStateVars(o3) {
        this.__chipSize.reset(o3.chipSize);
        this.__allowClose.reset(o3.allowClose);
        this.__closeOptions.reset(o3.closeOptions);
        this.__chipDirection.reset(o3.chipDirection);
        this.__prefixIcon.reset(o3.prefixIcon);
        this.__prefixSymbol.reset(o3.prefixSymbol);
        this.__label.reset(o3.label);
        this.__suffixIcon.reset(o3.suffixIcon);
        this.__suffixSymbol.reset(o3.suffixSymbol);
        this.__suffixSymbolOptions.reset(o3.suffixSymbolOptions);
        this.__chipNodeBackgroundColor.reset(o3.chipNodeBackgroundColor);
        this.__chipNodeActivatedBackgroundColor.reset(o3.chipNodeActivatedBackgroundColor);
        this.__chipNodeRadius.reset(o3.chipNodeRadius);
        this.__chipEnabled.reset(o3.chipEnabled);
        this.__chipActivated.reset(o3.chipActivated);
        this.__chipAccessibilitySelectedType.reset(o3.chipAccessibilitySelectedType);
        this.__chipAccessibilityDescription.reset(o3.chipAccessibilityDescription);
        this.__chipAccessibilityLevel.reset(o3.chipAccessibilityLevel);
    }

    purgeVariableDependenciesOnElmtId(n3) {
        this.__chipSize.purgeDependencyOnElmtId(n3);
        this.__allowClose.purgeDependencyOnElmtId(n3);
        this.__closeOptions.purgeDependencyOnElmtId(n3);
        this.__chipDirection.purgeDependencyOnElmtId(n3);
        this.__prefixIcon.purgeDependencyOnElmtId(n3);
        this.__prefixSymbol.purgeDependencyOnElmtId(n3);
        this.__label.purgeDependencyOnElmtId(n3);
        this.__suffixIcon.purgeDependencyOnElmtId(n3);
        this.__suffixSymbol.purgeDependencyOnElmtId(n3);
        this.__suffixSymbolOptions.purgeDependencyOnElmtId(n3);
        this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(n3);
        this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(n3);
        this.__chipNodeRadius.purgeDependencyOnElmtId(n3);
        this.__chipEnabled.purgeDependencyOnElmtId(n3);
        this.__chipActivated.purgeDependencyOnElmtId(n3);
        this.__chipAccessibilitySelectedType.purgeDependencyOnElmtId(n3);
        this.__chipAccessibilityDescription.purgeDependencyOnElmtId(n3);
        this.__chipAccessibilityLevel.purgeDependencyOnElmtId(n3);
        this.__isChipExist.purgeDependencyOnElmtId(n3);
        this.__chipScale.purgeDependencyOnElmtId(n3);
        this.__chipOpacity.purgeDependencyOnElmtId(n3);
        this.__suffixSymbolHeight.purgeDependencyOnElmtId(n3);
        this.__suffixSymbolWidth.purgeDependencyOnElmtId(n3);
        this.__breakPoint.purgeDependencyOnElmtId(n3);
        this.__fontSizeScale.purgeDependencyOnElmtId(n3);
        this.__chipNodeInFocus.purgeDependencyOnElmtId(n3);
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

    set chipSize(m3) {
        this.__chipSize.set(m3);
    }

    get allowClose() {
        return this.__allowClose.get();
    }

    set allowClose(l3) {
        this.__allowClose.set(l3);
    }

    get closeOptions() {
        return this.__closeOptions.get();
    }

    set closeOptions(k3) {
        this.__closeOptions.set(k3);
    }

    get chipDirection() {
        return this.__chipDirection.get();
    }

    set chipDirection(j3) {
        this.__chipDirection.set(j3);
    }

    get prefixIcon() {
        return this.__prefixIcon.get();
    }

    set prefixIcon(i3) {
        this.__prefixIcon.set(i3);
    }

    get prefixSymbol() {
        return this.__prefixSymbol.get();
    }

    set prefixSymbol(h3) {
        this.__prefixSymbol.set(h3);
    }

    get label() {
        return this.__label.get();
    }

    set label(g3) {
        this.__label.set(g3);
    }

    get suffixIcon() {
        return this.__suffixIcon.get();
    }

    set suffixIcon(f3) {
        this.__suffixIcon.set(f3);
    }

    get suffixSymbol() {
        return this.__suffixSymbol.get();
    }

    set suffixSymbol(e3) {
        this.__suffixSymbol.set(e3);
    }

    get suffixSymbolOptions() {
        return this.__suffixSymbolOptions.get();
    }

    set suffixSymbolOptions(d3) {
        this.__suffixSymbolOptions.set(d3);
    }

    get chipNodeBackgroundColor() {
        return this.__chipNodeBackgroundColor.get();
    }

    set chipNodeBackgroundColor(c3) {
        this.__chipNodeBackgroundColor.set(c3);
    }

    get chipNodeActivatedBackgroundColor() {
        return this.__chipNodeActivatedBackgroundColor.get();
    }

    set chipNodeActivatedBackgroundColor(b3) {
        this.__chipNodeActivatedBackgroundColor.set(b3);
    }

    get chipNodeRadius() {
        return this.__chipNodeRadius.get();
    }

    set chipNodeRadius(a3) {
        this.__chipNodeRadius.set(a3);
    }

    get chipEnabled() {
        return this.__chipEnabled.get();
    }

    set chipEnabled(z2) {
        this.__chipEnabled.set(z2);
    }

    get chipActivated() {
        return this.__chipActivated.get();
    }

    set chipActivated(y2) {
        this.__chipActivated.set(y2);
    }

    get chipAccessibilitySelectedType() {
        return this.__chipAccessibilitySelectedType.get();
    }

    set chipAccessibilitySelectedType(x2) {
        this.__chipAccessibilitySelectedType.set(x2);
    }

    get chipAccessibilityDescription() {
        return this.__chipAccessibilityDescription.get();
    }

    set chipAccessibilityDescription(w2) {
        this.__chipAccessibilityDescription.set(w2);
    }

    get chipAccessibilityLevel() {
        return this.__chipAccessibilityLevel.get();
    }

    set chipAccessibilityLevel(v2) {
        this.__chipAccessibilityLevel.set(v2);
    }

    get isChipExist() {
        return this.__isChipExist.get();
    }

    set isChipExist(u2) {
        this.__isChipExist.set(u2);
    }

    get chipScale() {
        return this.__chipScale.get();
    }

    set chipScale(t2) {
        this.__chipScale.set(t2);
    }

    get chipOpacity() {
        return this.__chipOpacity.get();
    }

    set chipOpacity(s2) {
        this.__chipOpacity.set(s2);
    }

    get suffixSymbolHeight() {
        return this.__suffixSymbolHeight.get();
    }

    set suffixSymbolHeight(r2) {
        this.__suffixSymbolHeight.set(r2);
    }

    get suffixSymbolWidth() {
        return this.__suffixSymbolWidth.get();
    }

    set suffixSymbolWidth(q2) {
        this.__suffixSymbolWidth.set(q2);
    }

    get breakPoint() {
        return this.__breakPoint.get();
    }

    set breakPoint(p2) {
        this.__breakPoint.set(p2);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(o2) {
        this.__fontSizeScale.set(o2);
    }

    get chipNodeInFocus() {
        return this.__chipNodeInFocus.get();
    }

    set chipNodeInFocus(n2) {
        this.__chipNodeInFocus.set(n2);
    }

    aboutToAppear() {
        this.smListener.on('change', (m2) => {
            if (m2.matches) {
                this.breakPoint = BreakPointsType.SM;
            }
        });
        this.mdListener.on('change', (l2) => {
            if (l2.matches) {
                this.breakPoint = BreakPointsType.MD;
            }
        });
        this.lgListener.on('change', (k2) => {
            if (k2.matches) {
                this.breakPoint = BreakPointsType.LG;
            }
        });
        let j2 = this.getUIContext().getHostContext();
        if (j2) {
            this.fontSizeScale = j2.config?.fontSizeScale ?? 1;
            this.environmentCallbackID = j2.getApplicationContext().on('environment', this.environmentCallback);
        }
    }

    aboutToDisappear() {
        this.smListener.off('change');
        this.mdListener.off('change');
        this.lgListener.off('change');
        if (this.environmentCallbackID) {
            this.getUIContext().getHostContext()?.getApplicationContext().off('environment',
                this.environmentCallbackID);
            this.environmentCallbackID = void 0;
        }
    }

    isSetActiveChipBgColor() {
        if (this.chipNodeActivatedBackgroundColor) {
            return false;
        }
        try {
            return ColorMetrics.resourceColor(this.chipNodeActivatedBackgroundColor).color !==
            ColorMetrics.resourceColor(this.theme.chipNode.activatedBackgroundColor).color;
        } catch (i2) {
            console.error(`[Chip] failed to get ColorMetrics.resourceColor`);
            return false;
        }
    }

    isSetNormalChipBgColor() {
        if (this.chipNodeBackgroundColor) {
            return false;
        }
        try {
            return ColorMetrics.resourceColor(this.chipNodeBackgroundColor).color !==
            ColorMetrics.resourceColor(this.theme.chipNode.backgroundColor).color;
        } catch (h2) {
            console.error(`[Chip] failed to get resourceColor`);
            return false;
        }
    }

    getShadowStyles() {
        if (!this.chipNodeInFocus) {
            return undefined;
        }
        return this.resourceToNumber(this.isSmallChipSize() ? this.theme.chipNode.smallShadowStyle :
        this.theme.chipNode.normalShadowStyle, -1);
    }

    ChipBuilder(d1 = null) {
        this.observeComponentCreation2((c2, d2) => {
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
            Button.onKeyEvent((e2) => {
                if (!e2 || e2.type === null || e2.type !== KeyType.Down) {
                    return;
                }
                let f2 = e2.keyCode === KeyCode.KEYCODE_FORWARD_DEL;
                let g2 = e2.keyCode === KeyCode.KEYCODE_ENTER && this.allowClose !== false && !this.suffixIcon?.src &&
                    this.isSuffixIconFocusStyleCustomized;
                if (f2 || g2) {
                    this.deleteChip();
                }
            });
            Button.onFocus(() => {
                if (this.isSuffixIconFocusStyleCustomized) {
                    this.chipNodeInFocus = true;
                    this.chipScale = {
                        x: this.resourceToNumber(this.theme.chipNode.focusBtnScaleX, 1),
                        y: this.resourceToNumber(this.theme.chipNode.focusBtnScaleY, 1),
                    };
                }
            });
            Button.onBlur(() => {
                if (this.isSuffixIconFocusStyleCustomized) {
                    this.chipNodeInFocus = false;
                    this.chipScale = {
                        x: 1, y: 1
                    };
                }
            });
        }, Button);
        this.observeComponentCreation2((a2, b2) => {
            Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
            Flex.direction(this.chipDirection);
            Flex.padding(this.getChipPadding());
            Flex.size(this.getChipSize());
            Flex.constraintSize(this.getChipConstraintSize());
        }, Flex);
        this.observeComponentCreation2((u1, v1) => {
            If.create();
            if (this.hasPrefixSymbol()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y1, z1) => {
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
                    this.observeComponentCreation2((w1, x1) => {
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
                this.ifElseBranchUpdateFunction(2, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((s1, t1) => {
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
        this.observeComponentCreation2((e1, f1) => {
            If.create();
            if (this.hasSuffixSymbol()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q1, r1) => {
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
                    this.observeComponentCreation2((o1, p1) => {
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
                    this.observeComponentCreation2((m1, n1) => {
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
                    this.observeComponentCreation2((k1, l1) => {
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
                    this.observeComponentCreation2((i1, j1) => {
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
                    this.observeComponentCreation2((g1, h1) => {
                        SymbolGlyph.create({
                            'id': -1,
                            'type': 40000,
                            params: ['sys.symbol.xmark'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.fontSize(this.defaultSymbolFontsize());
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_SYMBOL));
                    }, SymbolGlyph);
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(3, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
        Button.pop();
    }

    getCloseIconAccessibilityLevel() {
        if (this.closeOptions?.accessibilityLevel === 'no' ||
            this.closeOptions?.accessibilityLevel === 'no-hide-descendants') {
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
                'id': -1,
                'type': 10003,
                params: ['sys.string.delete_used_for_accessibility_text'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
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
        let c1 = { width: 0, height: 0 };
        if (typeof this.suffixIcon?.size?.width !== 'undefined' && this.isValidLength(this.suffixIcon.size.width)) {
            c1.width = this.suffixIcon.size.width;
        } else {
            c1.width =
                this.isSmallChipSize() ? this.theme.suffixIcon.smallSize.width : this.theme.suffixIcon.normalSize.width;
        }
        if (typeof this.suffixIcon?.size?.height !== 'undefined' && this.isValidLength(this.suffixIcon.size.height)) {
            c1.height = this.suffixIcon.size.height;
        } else {
            c1.height =
                this.isSmallChipSize() ? this.theme.suffixIcon.smallSize.height :
                this.theme.suffixIcon.normalSize.height;
        }
        return c1;
    }

    getSuffixIconAccessibilityLevel() {
        if (this.suffixIcon?.accessibilityLevel === 'no' ||
            this.suffixIcon?.accessibilityLevel === 'no-hide-descendants') {
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
            if (this.suffixSymbolOptions?.activatedAccessibility?.accessibilityLevel === 'no' ||
                this.suffixSymbolOptions?.activatedAccessibility?.accessibilityLevel === 'no-hide-descendants') {
                return this.suffixSymbolOptions.activatedAccessibility.accessibilityLevel;
            }
            return this.suffixSymbolOptions?.action ? 'yes' : 'no';
        }
        if (this.suffixSymbolOptions?.normalAccessibility?.accessibilityLevel === 'no' ||
            this.suffixSymbolOptions?.normalAccessibility?.accessibilityLevel === 'no-hide-descendants') {
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
        let b1 = { width: 0, height: 0 };
        if (typeof this.prefixIcon?.size?.width !== 'undefined' && this.isValidLength(this.prefixIcon.size.width)) {
            b1.width = this.prefixIcon.size.width;
        } else {
            b1.width =
                this.isSmallChipSize() ? this.theme.prefixIcon.smallSize.width : this.theme.prefixIcon.normalSize.width;
        }
        if (typeof this.prefixIcon?.size?.height !== 'undefined' && this.isValidLength(this.prefixIcon.size.height)) {
            b1.height = this.prefixIcon.size.height;
        } else {
            b1.height =
                this.isSmallChipSize() ? this.theme.prefixIcon.smallSize.height :
                this.theme.prefixIcon.normalSize.height;
        }
        return b1;
    }

    getPrefixSymbolModifier() {
        if (this.isChipActivated()) {
            return this.prefixSymbol?.activated;
        }
        return this.prefixSymbol?.normal;
    }

    getDefaultSymbolColor(a1) {
        return this.isChipActivated() ? this.getSymbolActiveColor(a1) :
        this.getSymbolFillColor(a1);
    }

    getDefaultActiveIconColor(z) {
        if (z === IconType.PREFIX_ICON) {
            return this.chipNodeInFocus ? this.theme.prefixIcon.focusActivatedColor :
            this.theme.prefixIcon.activatedFillColor;
        } else {
            return this.chipNodeInFocus ? this.theme.suffixIcon.focusActivatedColor :
            this.theme.suffixIcon.activatedFillColor;
        }
    }

    getDefaultFillIconColor(y) {
        if (y === IconType.PREFIX_ICON) {
            return this.chipNodeInFocus ? this.theme.prefixIcon.focusFillColor : this.theme.prefixIcon.fillColor;
        } else {
            return this.chipNodeInFocus ? this.theme.suffixIcon.focusFillColor : this.theme.suffixIcon.fillColor;
        }
    }

    getSymbolActiveColor(x) {
        if (!this.chipNodeInFocus) {
            return this.theme.defaultSymbol.activatedFontColor;
        }
        if (x === IconType.PREFIX_SYMBOL) {
            return [this.theme.prefixIcon.focusActivatedColor];
        }
        if (x === IconType.SUFFIX_SYMBOL) {
            return [this.theme.suffixIcon.focusActivatedColor];
        }
        return this.theme.defaultSymbol.activatedFontColor;
    }

    getSymbolFillColor(w) {
        if (!this.chipNodeInFocus) {
            return this.theme.defaultSymbol.normalFontColor;
        }
        if (w === IconType.PREFIX_SYMBOL) {
            return [this.theme.prefixIcon.focusFillColor];
        }
        if (w === IconType.SUFFIX_SYMBOL) {
            return [this.theme.suffixIcon.focusFillColor];
        }
        return this.theme.defaultSymbol.normalFontColor;
    }

    hasPrefixSymbol() {
        return !!(this.prefixSymbol?.normal || this.prefixSymbol?.activated);
    }

    getChipConstraintSize() {
        const v = {};
        if (typeof this.chipSize === 'string') {
            v.maxWidth = this.getChipMaxWidth();
            v.minHeight =
                this.chipSize === ChipSize.SMALL ? this.theme.chipNode.smallHeight : this.theme.chipNode.normalHeight;
        } else {
            if (typeof this.chipSize?.width === 'undefined' || !this.isValidLength(this.chipSize.width)) {
                v.maxWidth = this.getChipMaxWidth();
            }
            if (typeof this.chipSize?.height === 'undefined' || !this.isValidLength(this.chipSize.height)) {
                v.minHeight = this.theme.chipNode.normalHeight;
            }
        }
        return v;
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
        const u = {
            width: 'auto',
            height: 'auto'
        };
        if (typeof this.chipSize !== 'string') {
            if (typeof this.chipSize?.width !== 'undefined' && this.isValidLength(this.chipSize.width)) {
                u.width = this.chipSize.width;
            }
            if (typeof this.chipSize?.height !== 'undefined' && this.isValidLength(this.chipSize.height)) {
                u.height = this.chipSize.height;
            }
        }
        return u;
    }

    getChipPadding() {
        return this.isSmallChipSize() ? this.theme.chipNode.localizedSmallPadding :
        this.theme.chipNode.localizedNormalPadding;
    }

    getLabelMargin() {
        const q = {
            start: LengthMetrics.vp(0),
            end: LengthMetrics.vp(0),
        };
        const r =
            this.isSmallChipSize() ? this.theme.label.localizedSmallMargin : this.theme.label.localizedNormalMargin;
        if (typeof this.label?.localizedLabelMargin?.start !== 'undefined' &&
            this.label.localizedLabelMargin.start.value >= 0) {
            q.start = this.label.localizedLabelMargin.start;
        } else if (this.hasPrefix()) {
            q.start = r.start;
        }
        if (typeof this.label?.localizedLabelMargin?.end !== 'undefined' &&
            this.label.localizedLabelMargin.end.value >= 0) {
            q.end = this.label.localizedLabelMargin.end;
        } else if (this.hasSuffix()) {
            q.end = r.end;
        }
        if (typeof this.label?.localizedLabelMargin === 'object') {
            return q;
        }
        if (typeof this.label.labelMargin === 'object') {
            const s = { left: 0, right: 0 };
            const t = this.isSmallChipSize() ? this.theme.label.smallMargin : this.theme.label.normalMargin;
            if (typeof this.label?.labelMargin?.left !== 'undefined' &&
            this.isValidLength(this.label.labelMargin.left)) {
                s.left = this.label.labelMargin.left;
            } else if (this.hasPrefix()) {
                s.left = t.left;
            }
            if (typeof this.label?.labelMargin?.right !== 'undefined' &&
            this.isValidLength(this.label.labelMargin.right)) {
                s.right = this.label.labelMargin.right;
            } else if (this.hasSuffix()) {
                s.right = t.right;
            }
            return s;
        }
        return q;
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
        return this.isSmallChipSize() ? this.theme.defaultSymbol.smallSymbolFontSize :
        this.theme.defaultSymbol.normalSymbolFontSize;
    }

    getActiveFontColor() {
        return this.chipNodeInFocus ? this.theme.label.focusActiveFontColor : this.theme.label.activatedFontColor;
    }

    getFontColor() {
        return this.chipNodeInFocus ? this.theme.label.focusFontColor : this.theme.label.fontColor;
    }

    getChipNodeBorderColor() {
        let p = this.theme.chipNode;
        return this.isChipActivated() ? p.activatedBorderColor : p.borderColor;
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
        Context.animateTo({
            curve: Curve.FastOutLinearIn,
            duration: 150,
            onFinish: () => {
                this.isChipExist = false;
            }
        }, () => {
            this.chipScale = { x: 0.85, y: 0.85 };
        });
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
        let o = this.theme.chipNode;
        if (this.isChipActivated()) {
            return this.chipNodeInFocus && !this.isSetActiveChipBgColor() ? o.focusActivatedBgColor :
            this.getColor(this.chipNodeActivatedBackgroundColor, o.activatedBackgroundColor);
        }
        return this.chipNodeInFocus && !this.isSetNormalChipBgColor() ? o.focusBgColor :
        this.getColor(this.chipNodeBackgroundColor, this.theme.chipNode.backgroundColor);
    }

    getColor(l, m) {
        if (!l) {
            return m;
        }
        try {
            ColorMetrics.resourceColor(l).color;
            return l;
        } catch (n) {
            console.error(`[Chip] failed to get color`);
            return Color.Transparent;
        }
    }

    isChipActivated() {
        return this.chipActivated ?? false;
    }

    resourceToNumber(h, i) {
        if (!h || !h.type) {
            console.error('[Chip] failed: resource get fail');
            return i;
        }
        const j = this.getUIContext().getHostContext()?.resourceManager;
        if (!j) {
            console.error('[Chip] failed to get resourceManager');
            return i;
        }
        switch (h.type) {
            case RESOURCE_TYPE_FLOAT:
            case RESOURCE_TYPE_INTEGER:
                try {
                    if (h.id !== -1) {
                        return j.getNumber(h);
                    }
                    return j.getNumberByName(h.params[0].split('.')[2]);
                } catch (k) {
                    console.error(`[Chip] get resource error, return defaultValue`);
                    return i;
                }
            default:
                return i;
        }
    }

    isValidLength(e) {
        if (typeof e === 'number') {
            return e >= 0;
        } else if (typeof e === 'string') {
            return this.isValidLengthString(e);
        } else if (typeof e === 'object') {
            const f = e;
            const g = this.getUIContext().getHostContext()?.resourceManager;
            if (!g) {
                console.error('[Chip] failed to get resourceManager.');
                return false;
            }
            switch (f.type) {
                case RESOURCE_TYPE_FLOAT:
                case RESOURCE_TYPE_INTEGER:
                    return g.getNumber(f) >= 0;
                case RESOURCE_TYPE_STRING:
                    return this.isValidLengthString(g.getStringSync(f));
                default:
                    return false;
            }
        }
        return false;
    }

    isValidLengthString(c) {
        const d = c.match(/(-?\d+(?:\.\d+)?)_?(fp|vp|px|lpx)?$/i);
        if (!d || d.length < 3) {
            return false;
        }
        return Number.parseInt(d[1], 10) >= 0;
    }

    initialRender() {
        this.observeComponentCreation2((a, b) => {
            If.create();
            if (this.isChipExist) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ChipBuilder.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
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
