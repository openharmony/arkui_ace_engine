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
(function (r5) {
    r5['NORMAL'] = 'NORMAL';
    r5['SMALL'] = 'SMALL';
})(ChipSize || (ChipSize = {}));
var IconType;
(function (q5) {
    q5['PREFIX_ICON'] = 'PREFIXICON';
    q5['SUFFIX_ICON'] = 'SUFFIXICON';
    q5['PREFIX_SYMBOL'] = 'PREFIXSYMBOL';
    q5['SUFFIX_SYMBOL'] = 'SUFFIXSYMBOL';
})(IconType || (IconType = {}));
var BreakPointsType;
(function (p5) {
    p5['SM'] = 'SM';
    p5['MD'] = 'MD';
    p5['LG'] = 'LG';
})(BreakPointsType || (BreakPointsType = {}));

export var AccessibilitySelectedType;
(function (o5) {
    o5[o5['CLICKED'] = 0] = 'CLICKED';
    o5[o5['CHECKED'] = 1] = 'CHECKED';
    o5[o5['SELECTED'] = 2] = 'SELECTED';
})(AccessibilitySelectedType || (AccessibilitySelectedType = {}));

export const defaultTheme = {
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
        normalSymbolFontSize: {
            'id': -1,
            'type': 10002,
            params: ['sys.float.chip_normal_icon_size'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        },
        smallSymbolFontSize: {
            'id': -1,
            'type': 10002,
            params: ['sys.float.chip_small_icon_size'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        },
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
        focusBtnScaleX: LengthMetrics.resource({
            'id': -1,
            'type': 10002,
            params: ['sys.float.chip_focused_btn_scale'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }).value,
        focusBtnScaleY: LengthMetrics.resource({
            'id': -1,
            'type': 10002,
            params: ['sys.float.chip_focused_btn_scale'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }).value,
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
const RESOURCE_TYPE_STRING = 10003;
const RESOURCE_TYPE_FLOAT = 10002;
const RESOURCE_TYPE_INTEGER = 10007;

export function Chip(d5, e5 = null) {
    const f5 = d5;
    {
        (e5 ? e5 : this).observeComponentCreation2((h5, i5, j5 = f5) => {
            if (i5) {
                let k5 = new ChipComponent(e5 ? e5 : this, {
                    chipSize: j5.size,
                    prefixIcon: j5.prefixIcon,
                    prefixSymbol: j5.prefixSymbol,
                    label: j5.label,
                    suffixIcon: j5.suffixIcon,
                    suffixSymbol: j5.suffixSymbol,
                    suffixSymbolOptions: j5.suffixSymbolOptions,
                    allowClose: j5.allowClose,
                    closeOptions: j5.closeOptions,
                    chipEnabled: j5.enabled,
                    chipActivated: j5.activated,
                    chipNodeBackgroundColor: j5.backgroundColor,
                    chipNodeActivatedBackgroundColor: j5.activatedBackgroundColor,
                    chipNodeRadius: j5.borderRadius,
                    chipDirection: j5.direction,
                    chipAccessibilitySelectedType: j5.accessibilitySelectedType,
                    chipAccessibilityDescription: j5.accessibilityDescription,
                    chipAccessibilityLevel: j5.accessibilityLevel,
                    onClose: j5.onClose,
                    onClicked: j5.onClicked,
                }, undefined, h5, () => {
                }, { page: 'library/src/main/ets/components/chip_v16.ets', line: 343, col: 3 });
                ViewPU.create(k5);
                let i2 = () => {
                    return {
                        chipSize: j5.size,
                        prefixIcon: j5.prefixIcon,
                        prefixSymbol: j5.prefixSymbol,
                        label: j5.label,
                        suffixIcon: j5.suffixIcon,
                        suffixSymbol: j5.suffixSymbol,
                        suffixSymbolOptions: j5.suffixSymbolOptions,
                        allowClose: j5.allowClose,
                        closeOptions: j5.closeOptions,
                        chipEnabled: j5.enabled,
                        chipActivated: j5.activated,
                        chipNodeBackgroundColor: j5.backgroundColor,
                        chipNodeActivatedBackgroundColor: j5.activatedBackgroundColor,
                        chipNodeRadius: j5.borderRadius,
                        chipDirection: j5.direction,
                        chipAccessibilitySelectedType: j5.accessibilitySelectedType,
                        chipAccessibilityDescription: j5.accessibilityDescription,
                        chipAccessibilityLevel: j5.accessibilityLevel,
                        onClose: j5.onClose,
                        onClicked: j5.onClicked
                    };
                };
                k5.paramsGenerator_ = i2;
            } else {
                (e5 ? e5 : this).updateStateVarsOfChildByElmtId(h5, {
                    chipSize: j5.size,
                    prefixIcon: j5.prefixIcon,
                    prefixSymbol: j5.prefixSymbol,
                    label: j5.label,
                    suffixIcon: j5.suffixIcon,
                    suffixSymbol: j5.suffixSymbol,
                    suffixSymbolOptions: j5.suffixSymbolOptions,
                    allowClose: j5.allowClose,
                    closeOptions: j5.closeOptions,
                    chipEnabled: j5.enabled,
                    chipActivated: j5.activated,
                    chipNodeBackgroundColor: j5.backgroundColor,
                    chipNodeActivatedBackgroundColor: j5.activatedBackgroundColor,
                    chipNodeRadius: j5.borderRadius,
                    chipDirection: j5.direction,
                    chipAccessibilitySelectedType: j5.accessibilitySelectedType,
                    chipAccessibilityDescription: j5.accessibilityDescription,
                    chipAccessibilityLevel: j5.accessibilityLevel
                });
            }
        }, { name: 'ChipComponent' });
    }
}

export class ChipComponent extends ViewPU {
    constructor(w4, x4, y4, z4 = -1, a5 = undefined, b5) {
        super(w4, y4, z4, b5);
        if (typeof a5 === 'function') {
            this.paramsGenerator_ = a5;
        }
        this.theme = defaultTheme;
        this.__chipSize = new SynchedPropertyObjectOneWayPU(x4.chipSize, this, 'chipSize');
        this.__allowClose = new SynchedPropertySimpleOneWayPU(x4.allowClose, this, 'allowClose');
        this.__closeOptions = new SynchedPropertyObjectOneWayPU(x4.closeOptions, this, 'closeOptions');
        this.__chipDirection = new SynchedPropertySimpleOneWayPU(x4.chipDirection, this, 'chipDirection');
        this.__prefixIcon = new SynchedPropertyObjectOneWayPU(x4.prefixIcon, this, 'prefixIcon');
        this.__prefixSymbol = new SynchedPropertyObjectOneWayPU(x4.prefixSymbol, this, 'prefixSymbol');
        this.__label = new SynchedPropertyObjectOneWayPU(x4.label, this, 'label');
        this.__suffixIcon = new SynchedPropertyObjectOneWayPU(x4.suffixIcon, this, 'suffixIcon');
        this.__suffixSymbol = new SynchedPropertyObjectOneWayPU(x4.suffixSymbol, this, 'suffixSymbol');
        this.__suffixSymbolOptions =
            new SynchedPropertyObjectOneWayPU(x4.suffixSymbolOptions, this, 'suffixSymbolOptions');
        this.__chipNodeBackgroundColor =
            new SynchedPropertyObjectOneWayPU(x4.chipNodeBackgroundColor, this, 'chipNodeBackgroundColor');
        this.__chipNodeActivatedBackgroundColor =
            new SynchedPropertyObjectOneWayPU(x4.chipNodeActivatedBackgroundColor, this,
                'chipNodeActivatedBackgroundColor');
        this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(x4.chipNodeRadius, this, 'chipNodeRadius');
        this.__chipEnabled = new SynchedPropertySimpleOneWayPU(x4.chipEnabled, this, 'chipEnabled');
        this.__chipActivated = new SynchedPropertySimpleOneWayPU(x4.chipActivated, this, 'chipActivated');
        this.__chipAccessibilitySelectedType =
            new SynchedPropertySimpleOneWayPU(x4.chipAccessibilitySelectedType, this, 'chipAccessibilitySelectedType');
        this.__chipAccessibilityDescription =
            new SynchedPropertyObjectOneWayPU(x4.chipAccessibilityDescription, this, 'chipAccessibilityDescription');
        this.__chipAccessibilityLevel =
            new SynchedPropertySimpleOneWayPU(x4.chipAccessibilityLevel, this, 'chipAccessibilityLevel');
        this.__isChipExist = new ObservedPropertySimplePU(true, this, 'isChipExist');
        this.__chipScale = new ObservedPropertyObjectPU({ x: 1, y: 1 }, this, 'chipScale');
        this.__chipOpacity = new ObservedPropertySimplePU(1, this, 'chipOpacity');
        this.__suffixSymbolHeight = new ObservedPropertySimplePU(0, this, 'suffixSymbolHeight');
        this.__suffixSymbolWidth = new ObservedPropertySimplePU(0, this, 'suffixSymbolWidth');
        this.__breakPoint = new ObservedPropertySimplePU(BreakPointsType.SM, this, 'breakPoint');
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.isSuffixIconFocusStyleCustomized = this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 0;
        this.isSuffixIconFocusable = this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 1;
        this.onClose = undefined;
        this.onClicked = undefined;
        this.__chipNodeInFocus = new ObservedPropertySimplePU(false, this, 'chipNodeInFocus');
        this.smListener = mediaquery.matchMediaSync('(0vp<width) and (width<600vp)');
        this.mdListener = mediaquery.matchMediaSync('(600vp<=width) and (width<840vp)');
        this.lgListener = mediaquery.matchMediaSync('(840vp<=width)');
        this.symbolEffect = new SymbolEffect();
        this.environmentCallbackID = undefined;
        this.environmentCallback = {
            onConfigurationUpdated: (b2) => {
                this.fontSizeScale = b2.fontSizeScale ?? 1;
            },
            onMemoryLevel() {
            }
        };
        this.setInitiallyProvidedValue(x4);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(v4) {
        if (v4.theme !== undefined) {
            this.theme = v4.theme;
        }
        if (v4.chipSize === undefined) {
            this.__chipSize.set(ChipSize.NORMAL);
        }
        if (v4.chipDirection === undefined) {
            this.__chipDirection.set(Direction.Auto);
        }
        if (v4.chipEnabled === undefined) {
            this.__chipEnabled.set(true);
        }
        if (v4.isChipExist !== undefined) {
            this.isChipExist = v4.isChipExist;
        }
        if (v4.chipScale !== undefined) {
            this.chipScale = v4.chipScale;
        }
        if (v4.chipOpacity !== undefined) {
            this.chipOpacity = v4.chipOpacity;
        }
        if (v4.suffixSymbolHeight !== undefined) {
            this.suffixSymbolHeight = v4.suffixSymbolHeight;
        }
        if (v4.suffixSymbolWidth !== undefined) {
            this.suffixSymbolWidth = v4.suffixSymbolWidth;
        }
        if (v4.breakPoint !== undefined) {
            this.breakPoint = v4.breakPoint;
        }
        if (v4.fontSizeScale !== undefined) {
            this.fontSizeScale = v4.fontSizeScale;
        }
        if (v4.isSuffixIconFocusStyleCustomized !== undefined) {
            this.isSuffixIconFocusStyleCustomized = v4.isSuffixIconFocusStyleCustomized;
        }
        if (v4.isSuffixIconFocusable !== undefined) {
            this.isSuffixIconFocusable = v4.isSuffixIconFocusable;
        }
        if (v4.onClose !== undefined) {
            this.onClose = v4.onClose;
        }
        if (v4.onClicked !== undefined) {
            this.onClicked = v4.onClicked;
        }
        if (v4.chipNodeInFocus !== undefined) {
            this.chipNodeInFocus = v4.chipNodeInFocus;
        }
        if (v4.smListener !== undefined) {
            this.smListener = v4.smListener;
        }
        if (v4.mdListener !== undefined) {
            this.mdListener = v4.mdListener;
        }
        if (v4.lgListener !== undefined) {
            this.lgListener = v4.lgListener;
        }
        if (v4.symbolEffect !== undefined) {
            this.symbolEffect = v4.symbolEffect;
        }
        if (v4.environmentCallbackID !== undefined) {
            this.environmentCallbackID = v4.environmentCallbackID;
        }
        if (v4.environmentCallback !== undefined) {
            this.environmentCallback = v4.environmentCallback;
        }
    }

    updateStateVars(u4) {
        this.__chipSize.reset(u4.chipSize);
        this.__allowClose.reset(u4.allowClose);
        this.__closeOptions.reset(u4.closeOptions);
        this.__chipDirection.reset(u4.chipDirection);
        this.__prefixIcon.reset(u4.prefixIcon);
        this.__prefixSymbol.reset(u4.prefixSymbol);
        this.__label.reset(u4.label);
        this.__suffixIcon.reset(u4.suffixIcon);
        this.__suffixSymbol.reset(u4.suffixSymbol);
        this.__suffixSymbolOptions.reset(u4.suffixSymbolOptions);
        this.__chipNodeBackgroundColor.reset(u4.chipNodeBackgroundColor);
        this.__chipNodeActivatedBackgroundColor.reset(u4.chipNodeActivatedBackgroundColor);
        this.__chipNodeRadius.reset(u4.chipNodeRadius);
        this.__chipEnabled.reset(u4.chipEnabled);
        this.__chipActivated.reset(u4.chipActivated);
        this.__chipAccessibilitySelectedType.reset(u4.chipAccessibilitySelectedType);
        this.__chipAccessibilityDescription.reset(u4.chipAccessibilityDescription);
        this.__chipAccessibilityLevel.reset(u4.chipAccessibilityLevel);
    }

    purgeVariableDependenciesOnElmtId(t4) {
        this.__chipSize.purgeDependencyOnElmtId(t4);
        this.__allowClose.purgeDependencyOnElmtId(t4);
        this.__closeOptions.purgeDependencyOnElmtId(t4);
        this.__chipDirection.purgeDependencyOnElmtId(t4);
        this.__prefixIcon.purgeDependencyOnElmtId(t4);
        this.__prefixSymbol.purgeDependencyOnElmtId(t4);
        this.__label.purgeDependencyOnElmtId(t4);
        this.__suffixIcon.purgeDependencyOnElmtId(t4);
        this.__suffixSymbol.purgeDependencyOnElmtId(t4);
        this.__suffixSymbolOptions.purgeDependencyOnElmtId(t4);
        this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(t4);
        this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(t4);
        this.__chipNodeRadius.purgeDependencyOnElmtId(t4);
        this.__chipEnabled.purgeDependencyOnElmtId(t4);
        this.__chipActivated.purgeDependencyOnElmtId(t4);
        this.__chipAccessibilitySelectedType.purgeDependencyOnElmtId(t4);
        this.__chipAccessibilityDescription.purgeDependencyOnElmtId(t4);
        this.__chipAccessibilityLevel.purgeDependencyOnElmtId(t4);
        this.__isChipExist.purgeDependencyOnElmtId(t4);
        this.__chipScale.purgeDependencyOnElmtId(t4);
        this.__chipOpacity.purgeDependencyOnElmtId(t4);
        this.__suffixSymbolHeight.purgeDependencyOnElmtId(t4);
        this.__suffixSymbolWidth.purgeDependencyOnElmtId(t4);
        this.__breakPoint.purgeDependencyOnElmtId(t4);
        this.__fontSizeScale.purgeDependencyOnElmtId(t4);
        this.__chipNodeInFocus.purgeDependencyOnElmtId(t4);
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

    set chipSize(s4) {
        this.__chipSize.set(s4);
    }

    get allowClose() {
        return this.__allowClose.get();
    }

    set allowClose(r4) {
        this.__allowClose.set(r4);
    }

    get closeOptions() {
        return this.__closeOptions.get();
    }

    set closeOptions(q4) {
        this.__closeOptions.set(q4);
    }

    get chipDirection() {
        return this.__chipDirection.get();
    }

    set chipDirection(p4) {
        this.__chipDirection.set(p4);
    }

    get prefixIcon() {
        return this.__prefixIcon.get();
    }

    set prefixIcon(o4) {
        this.__prefixIcon.set(o4);
    }

    get prefixSymbol() {
        return this.__prefixSymbol.get();
    }

    set prefixSymbol(n4) {
        this.__prefixSymbol.set(n4);
    }

    get label() {
        return this.__label.get();
    }

    set label(m4) {
        this.__label.set(m4);
    }

    get suffixIcon() {
        return this.__suffixIcon.get();
    }

    set suffixIcon(l4) {
        this.__suffixIcon.set(l4);
    }

    get suffixSymbol() {
        return this.__suffixSymbol.get();
    }

    set suffixSymbol(k4) {
        this.__suffixSymbol.set(k4);
    }

    get suffixSymbolOptions() {
        return this.__suffixSymbolOptions.get();
    }

    set suffixSymbolOptions(j4) {
        this.__suffixSymbolOptions.set(j4);
    }

    get chipNodeBackgroundColor() {
        return this.__chipNodeBackgroundColor.get();
    }

    set chipNodeBackgroundColor(i4) {
        this.__chipNodeBackgroundColor.set(i4);
    }

    get chipNodeActivatedBackgroundColor() {
        return this.__chipNodeActivatedBackgroundColor.get();
    }

    set chipNodeActivatedBackgroundColor(h4) {
        this.__chipNodeActivatedBackgroundColor.set(h4);
    }

    get chipNodeRadius() {
        return this.__chipNodeRadius.get();
    }

    set chipNodeRadius(g4) {
        this.__chipNodeRadius.set(g4);
    }

    get chipEnabled() {
        return this.__chipEnabled.get();
    }

    set chipEnabled(f4) {
        this.__chipEnabled.set(f4);
    }

    get chipActivated() {
        return this.__chipActivated.get();
    }

    set chipActivated(e4) {
        this.__chipActivated.set(e4);
    }

    get chipAccessibilitySelectedType() {
        return this.__chipAccessibilitySelectedType.get();
    }

    set chipAccessibilitySelectedType(d4) {
        this.__chipAccessibilitySelectedType.set(d4);
    }

    get chipAccessibilityDescription() {
        return this.__chipAccessibilityDescription.get();
    }

    set chipAccessibilityDescription(c4) {
        this.__chipAccessibilityDescription.set(c4);
    }

    get chipAccessibilityLevel() {
        return this.__chipAccessibilityLevel.get();
    }

    set chipAccessibilityLevel(b4) {
        this.__chipAccessibilityLevel.set(b4);
    }

    get isChipExist() {
        return this.__isChipExist.get();
    }

    set isChipExist(a4) {
        this.__isChipExist.set(a4);
    }

    get chipScale() {
        return this.__chipScale.get();
    }

    set chipScale(z3) {
        this.__chipScale.set(z3);
    }

    get chipOpacity() {
        return this.__chipOpacity.get();
    }

    set chipOpacity(y3) {
        this.__chipOpacity.set(y3);
    }

    get suffixSymbolHeight() {
        return this.__suffixSymbolHeight.get();
    }

    set suffixSymbolHeight(x3) {
        this.__suffixSymbolHeight.set(x3);
    }

    get suffixSymbolWidth() {
        return this.__suffixSymbolWidth.get();
    }

    set suffixSymbolWidth(w3) {
        this.__suffixSymbolWidth.set(w3);
    }

    get breakPoint() {
        return this.__breakPoint.get();
    }

    set breakPoint(v3) {
        this.__breakPoint.set(v3);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(u3) {
        this.__fontSizeScale.set(u3);
    }

    get chipNodeInFocus() {
        return this.__chipNodeInFocus.get();
    }

    set chipNodeInFocus(q3) {
        this.__chipNodeInFocus.set(q3);
    }

    aboutToAppear() {
        this.smListener.on('change', (p3) => {
            if (p3.matches) {
                this.breakPoint = BreakPointsType.SM;
            }
        });
        this.mdListener.on('change', (o3) => {
            if (o3.matches) {
                this.breakPoint = BreakPointsType.MD;
            }
        });
        this.lgListener.on('change', (n3) => {
            if (n3.matches) {
                this.breakPoint = BreakPointsType.LG;
            }
        });
        let j3 = this.getUIContext().getHostContext();
        if (j3) {
            this.fontSizeScale = j3.config?.fontSizeScale ?? 1;
            this.environmentCallbackID = j3.getApplicationContext().on('environment', this.environmentCallback);
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
        if (this.chipNodeActivatedBackgroundColor == null) {
            return false;
        }
        return ColorMetrics.resourceColor(this.chipNodeActivatedBackgroundColor).color !==
        ColorMetrics.resourceColor(this.theme.chipNode.activatedBackgroundColor).color;
    }

    isSetNormalChipBgColor() {
        if (this.chipNodeBackgroundColor == null) {
            return false;
        }
        return ColorMetrics.resourceColor(this.chipNodeBackgroundColor).color !==
        ColorMetrics.resourceColor(this.theme.chipNode.backgroundColor).color;
    }

    getShadowStyles() {
        let n1 = this.isSmallChipSize() ? this.theme.chipNode.smallShadowStyle :
        this.theme.chipNode.normalShadowStyle;
        if (this.resourceToNumber(n1, -1) === -1) {
            return undefined;
        }
        return this.resourceToNumber(n1, -1);
    }

    ChipBuilder(j1 = null) {
        this.observeComponentCreation2((d3, e3) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.clip(false);
            Button.shadow(this.chipNodeInFocus ? this.getShadowStyles() : undefined);
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
            Button.onKeyEvent((m1) => {
                if (m1.type === KeyType.Down && m1.keyCode === KeyCode.KEYCODE_FORWARD_DEL) {
                    this.deleteChip();
                }
            });
            Button.onFocus(() => {
                if (this.isSuffixIconFocusStyleCustomized) {
                    this.chipNodeInFocus = true;
                    this.chipScale = {
                        x: this.theme.chipNode.focusBtnScaleX ?? 1,
                        y: this.theme.chipNode.focusBtnScaleY ?? 1,
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
        this.observeComponentCreation2((b3, c3) => {
            Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
            Flex.direction(this.chipDirection);
            Flex.padding(this.getChipPadding());
            Flex.size(this.getChipSize());
            Flex.constraintSize(this.getChipConstraintSize());
        }, Flex);
        this.observeComponentCreation2((q2, r2) => {
            If.create();
            if (this.hasPrefixSymbol()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z2, a3) => {
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
                    this.observeComponentCreation2((v2, w2) => {
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
        this.observeComponentCreation2((o2, p2) => {
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
        this.observeComponentCreation2((p1, q1) => {
            If.create();
            if (this.hasSuffixSymbol()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m2, n2) => {
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
                    this.observeComponentCreation2((k2, l2) => {
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
                    this.observeComponentCreation2((f2, g2) => {
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
                    this.observeComponentCreation2((d2, e2) => {
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
                    this.observeComponentCreation2((x1, y1) => {
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
                    this.observeComponentCreation2((v1, w1) => {
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
        let h1 = { width: 0, height: 0 };
        if (typeof this.suffixIcon?.size?.width !== 'undefined' && this.isValidLength(this.suffixIcon.size.width)) {
            h1.width = this.suffixIcon.size.width;
        } else {
            h1.width =
                this.isSmallChipSize() ? this.theme.suffixIcon.smallSize.width : this.theme.suffixIcon.normalSize.width;
        }
        if (typeof this.suffixIcon?.size?.height !== 'undefined' && this.isValidLength(this.suffixIcon.size.height)) {
            h1.height = this.suffixIcon.size.height;
        } else {
            h1.height =
                this.isSmallChipSize() ? this.theme.suffixIcon.smallSize.height :
                this.theme.suffixIcon.normalSize.height;
        }
        return h1;
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
        let f1 = { width: 0, height: 0 };
        if (typeof this.prefixIcon?.size?.width !== 'undefined' && this.isValidLength(this.prefixIcon.size.width)) {
            f1.width = this.prefixIcon.size.width;
        } else {
            f1.width =
                this.isSmallChipSize() ? this.theme.prefixIcon.smallSize.width : this.theme.prefixIcon.normalSize.width;
        }
        if (typeof this.prefixIcon?.size?.height !== 'undefined' && this.isValidLength(this.prefixIcon.size.height)) {
            f1.height = this.prefixIcon.size.height;
        } else {
            f1.height =
                this.isSmallChipSize() ? this.theme.prefixIcon.smallSize.height :
                this.theme.prefixIcon.normalSize.height;
        }
        return f1;
    }

    getPrefixSymbolModifier() {
        if (this.isChipActivated()) {
            return this.prefixSymbol?.activated;
        }
        return this.prefixSymbol?.normal;
    }

    getDefaultSymbolColor(e1) {
        return this.isChipActivated() ? this.getSymbolActiveColor(e1) :
        this.getSymbolFillColor(e1);
    }

    getDefaultActiveIconColor(d1) {
        if (d1 === IconType.PREFIX_ICON) {
            return this.chipNodeInFocus ? this.theme.prefixIcon.focusActivatedColor :
            this.theme.prefixIcon.activatedFillColor;
        } else {
            return this.chipNodeInFocus ? this.theme.suffixIcon.focusActivatedColor :
            this.theme.suffixIcon.activatedFillColor;
        }
    }

    getDefaultFillIconColor(c1) {
        if (c1 === IconType.PREFIX_ICON) {
            return this.chipNodeInFocus ? this.theme.prefixIcon.focusFillColor : this.theme.prefixIcon.fillColor;
        } else {
            return this.chipNodeInFocus ? this.theme.suffixIcon.focusFillColor : this.theme.suffixIcon.fillColor;
        }
    }

    getSymbolActiveColor(b1) {
        if (!this.chipNodeInFocus) {
            return this.theme.defaultSymbol.activatedFontColor;
        }
        if (b1 === IconType.PREFIX_SYMBOL) {
            return [this.theme.prefixIcon.focusActivatedColor];
        }
        if (b1 === IconType.SUFFIX_SYMBOL) {
            return [this.theme.suffixIcon.focusActivatedColor];
        }
        return this.theme.defaultSymbol.activatedFontColor;
    }

    getSymbolFillColor(a1) {
        if (!this.chipNodeInFocus) {
            return this.theme.defaultSymbol.normalFontColor;
        }
        if (a1 === IconType.PREFIX_SYMBOL) {
            return [this.theme.prefixIcon.focusFillColor];
        }
        if (a1 === IconType.SUFFIX_SYMBOL) {
            return [this.theme.suffixIcon.focusFillColor];
        }
        return this.theme.defaultSymbol.normalFontColor;
    }

    hasPrefixSymbol() {
        return !!(this.prefixSymbol?.normal || this.prefixSymbol?.activated);
    }

    getChipConstraintSize() {
        const w = {};
        if (typeof this.chipSize === 'string') {
            w.maxWidth = this.getChipMaxWidth();
            w.minHeight =
                this.chipSize === ChipSize.SMALL ? this.theme.chipNode.smallHeight : this.theme.chipNode.normalHeight;
        } else {
            if (typeof this.chipSize?.width === 'undefined' || !this.isValidLength(this.chipSize.width)) {
                w.maxWidth = this.getChipMaxWidth();
            }
            if (typeof this.chipSize?.height === 'undefined' || !this.isValidLength(this.chipSize.height)) {
                w.minHeight = this.theme.chipNode.normalHeight;
            }
        }
        return w;
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
        const v = {
            width: 'auto',
            height: 'auto'
        };
        if (typeof this.chipSize !== 'string') {
            if (typeof this.chipSize?.width !== 'undefined' && this.isValidLength(this.chipSize.width)) {
                v.width = this.chipSize.width;
            }
            if (typeof this.chipSize?.height !== 'undefined' && this.isValidLength(this.chipSize.height)) {
                v.height = this.chipSize.height;
            }
        }
        return v;
    }

    getChipPadding() {
        return this.isSmallChipSize() ? this.theme.chipNode.localizedSmallPadding :
        this.theme.chipNode.localizedNormalPadding;
    }

    getLabelMargin() {
        const r = {
            start: LengthMetrics.vp(0),
            end: LengthMetrics.vp(0),
        };
        const s =
            this.isSmallChipSize() ? this.theme.label.localizedSmallMargin : this.theme.label.localizedNormalMargin;
        if (typeof this.label?.localizedLabelMargin?.start !== 'undefined' &&
            this.label.localizedLabelMargin.start.value >= 0) {
            r.start = this.label.localizedLabelMargin.start;
        } else if (this.hasPrefix()) {
            r.start = s.start;
        }
        if (typeof this.label?.localizedLabelMargin?.end !== 'undefined' &&
            this.label.localizedLabelMargin.end.value >= 0) {
            r.end = this.label.localizedLabelMargin.end;
        } else if (this.hasSuffix()) {
            r.end = s.end;
        }
        if (typeof this.label?.localizedLabelMargin === 'object') {
            return r;
        }
        if (typeof this.label.labelMargin === 'object') {
            const t = { left: 0, right: 0 };
            const u = this.isSmallChipSize() ? this.theme.label.smallMargin : this.theme.label.normalMargin;
            if (typeof this.label?.labelMargin?.left !== 'undefined' &&
            this.isValidLength(this.label.labelMargin.left)) {
                t.left = this.label.labelMargin.left;
            } else if (this.hasPrefix()) {
                t.left = u.left;
            }
            if (typeof this.label?.labelMargin?.right !== 'undefined' &&
            this.isValidLength(this.label.labelMargin.right)) {
                t.right = this.label.labelMargin.right;
            } else if (this.hasSuffix()) {
                t.right = u.right;
            }
            return t;
        }
        return r;
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
        return this.isChipActivated() ? FontWeight.Medium : FontWeight.Regular;
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
        let q = this.theme.chipNode;
        return this.isChipActivated() ? q.activatedBorderColor : q.borderColor;
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
        let n = this.theme.chipNode;
        if (this.isChipActivated()) {
            return this.chipNodeInFocus && !this.isSetActiveChipBgColor() ? n.focusActivatedBgColor :
            this.getColor(this.chipNodeActivatedBackgroundColor, n.activatedBackgroundColor);
        }
        return this.chipNodeInFocus && !this.isSetNormalChipBgColor() ? n.focusBgColor :
        this.getColor(this.chipNodeBackgroundColor, this.theme.chipNode.backgroundColor);
    }

    getColor(k, l) {
        if (!k) {
            return l;
        }
        try {
            ColorMetrics.resourceColor(k).color;
            return k;
        } catch (m) {
            console.error(`[Chip] failed to get color`);
            return Color.Transparent;
        }
    }

    isChipActivated() {
        return this.chipActivated ?? false;
    }

    resourceToNumber(x, y) {
        if (!x || !x.type) {
            console.error('[Chip] failed: resource get fail.');
            return y;
        }
        const z = this.getUIContext().getHostContext()?.resourceManager;
        if (!z) {
            console.error('[Chip] failed to get resourceManager.');
            return y;
        }
        switch (x.type) {
            case RESOURCE_TYPE_FLOAT:
            case RESOURCE_TYPE_INTEGER:
                if (x.id !== -1) {
                    return z.getNumber(x);
                }
                if (x.params && x.params.length > 0 && x.params[0] && x.params[0].split('.') > 2 &&
                x.params[0].split('.')[2]) {
                    let t1 = x.params[0].split('.')[2];
                    return z.getNumberByName(t1);
                }
                return y;
            default:
                return y;
        }
    }

    isValidLength(h) {
        if (typeof h === 'number') {
            return h >= 0;
        } else if (typeof h === 'string') {
            return this.isValidLengthString(h);
        } else if (typeof h === 'object') {
            const i = h;
            const j = this.getUIContext().getHostContext()?.resourceManager;
            if (!j) {
                console.error('[Chip] failed to get resourceManager.');
                return false;
            }
            switch (i.type) {
                case RESOURCE_TYPE_FLOAT:
                case RESOURCE_TYPE_INTEGER:
                    return j.getNumber(i) >= 0;
                case RESOURCE_TYPE_STRING:
                    return this.isValidLengthString(j.getStringSync(i));
                default:
                    return false;
            }
        }
        return false;
    }

    isValidLengthString(f) {
        const g = f.match(/(-?\d+(?:\.\d+)?)_?(fp|vp|px|lpx)?$/i);
        if (!g || g.length < 3) {
            return false;
        }
        return Number.parseInt(g[1], 10) >= 0;
    }

    initialRender() {
        this.observeComponentCreation2((b, c) => {
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