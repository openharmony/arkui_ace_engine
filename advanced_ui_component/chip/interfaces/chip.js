/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
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
(function (k11) {
    k11['NORMAL'] = 'NORMAL';
    k11['SMALL'] = 'SMALL';
})(ChipSize || (ChipSize = {}));
var IconType;
(function (j11) {
    j11['PREFIX_ICON'] = 'PREFIXICON';
    j11['SUFFIX_ICON'] = 'SUFFIXICON';
    j11['PREFIX_SYMBOL'] = 'PREFIXSYMBOL';
    j11['SUFFIX_SYMBOL'] = 'SUFFIXSYMBOL';
})(IconType || (IconType = {}));
var BreakPointsType;
(function (i11) {
    i11['SM'] = 'SM';
    i11['MD'] = 'MD';
    i11['LG'] = 'LG';
})(BreakPointsType || (BreakPointsType = {}));

export var AccessibilitySelectedType;
(function (h11) {
    h11[h11['CLICKED'] = 0] = 'CLICKED';
    h11[h11['CHECKED'] = 1] = 'CHECKED';
    h11[h11['SELECTED'] = 2] = 'SELECTED';
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
            params: ['sys.color.ohos_id_color_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }],
        activatedFontColor: [{
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_primary_contrary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }],
        smallSymbolFontSize: LengthMetrics.resource({
            'id': -1,
            'type': 10002,
            params: ['sys.float.chip_normal_icon_size'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }).value,
        normalSymbolFontSize: LengthMetrics.resource({
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
const noop = () => {
};

export function Chip(w10, x10 = null) {
    const y10 = w10;
    {
        (x10 ? x10 : this).observeComponentCreation2((a11, b11, c11 = y10) => {
            if (b11) {
                let d11 = new ChipComponent(x10 ? x10 : this, {
                    chipSize: c11.size,
                    prefixIcon: c11.prefixIcon,
                    prefixSymbol: c11.prefixSymbol,
                    label: c11.label,
                    suffixIcon: c11.suffixIcon,
                    suffixSymbol: c11.suffixSymbol,
                    suffixSymbolOptions: c11.suffixSymbolOptions,
                    allowClose: c11.allowClose,
                    closeOptions: c11.closeOptions,
                    chipEnabled: c11.enabled,
                    chipActivated: c11.activated,
                    chipNodeBackgroundColor: c11.backgroundColor,
                    chipNodeActivatedBackgroundColor: c11.activatedBackgroundColor,
                    chipNodeRadius: c11.borderRadius,
                    chipDirection: c11.direction,
                    chipAccessibilitySelectedType: c11.accessibilitySelectedType,
                    chipAccessibilityDescription: c11.accessibilityDescription,
                    chipAccessibilityLevel: c11.accessibilityLevel,
                    onClose: c11.onClose,
                    onClicked: c11.onClicked,
                }, undefined, a11, () => {
                }, { page: 'library/src/main/ets/components/chip.ets', line: 352, col: 3 });
                ViewPU.create(d11);
                let a = () => {
                    return {
                        chipSize: c11.size,
                        prefixIcon: c11.prefixIcon,
                        prefixSymbol: c11.prefixSymbol,
                        label: c11.label,
                        suffixIcon: c11.suffixIcon,
                        suffixSymbol: c11.suffixSymbol,
                        suffixSymbolOptions: c11.suffixSymbolOptions,
                        allowClose: c11.allowClose,
                        closeOptions: c11.closeOptions,
                        chipEnabled: c11.enabled,
                        chipActivated: c11.activated,
                        chipNodeBackgroundColor: c11.backgroundColor,
                        chipNodeActivatedBackgroundColor: c11.activatedBackgroundColor,
                        chipNodeRadius: c11.borderRadius,
                        chipDirection: c11.direction,
                        chipAccessibilitySelectedType: c11.accessibilitySelectedType,
                        chipAccessibilityDescription: c11.accessibilityDescription,
                        chipAccessibilityLevel: c11.accessibilityLevel,
                        onClose: c11.onClose,
                        onClicked: c11.onClicked
                    };
                };
                d11.paramsGenerator_ = a;
            } else {
                (x10 ? x10 : this).updateStateVarsOfChildByElmtId(a11, {
                    chipSize: c11.size,
                    prefixIcon: c11.prefixIcon,
                    prefixSymbol: c11.prefixSymbol,
                    label: c11.label,
                    suffixIcon: c11.suffixIcon,
                    suffixSymbol: c11.suffixSymbol,
                    suffixSymbolOptions: c11.suffixSymbolOptions,
                    allowClose: c11.allowClose,
                    closeOptions: c11.closeOptions,
                    chipEnabled: c11.enabled,
                    chipActivated: c11.activated,
                    chipNodeBackgroundColor: c11.backgroundColor,
                    chipNodeActivatedBackgroundColor: c11.activatedBackgroundColor,
                    chipNodeRadius: c11.borderRadius,
                    chipDirection: c11.direction,
                    chipAccessibilitySelectedType: c11.accessibilitySelectedType,
                    chipAccessibilityDescription: c11.accessibilityDescription,
                    chipAccessibilityLevel: c11.accessibilityLevel
                });
            }
        }, { name: 'ChipComponent' });
    }
}

function isValidString(s10, t10) {
    const u10 = s10.match(t10);
    if (!u10 || u10.length < 3) {
        return false;
    }
    const v10 = Number.parseFloat(u10[1]);
    return v10 >= 0;
}

function isValidDimensionString(r10) {
    return isValidString(r10, new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i'));
}

function isValidResource(o10, p10) {
    const q10 = o10?.resourceManager;
    if (p10 === void (0) || p10 === null || q10 === void (0)) {
        return false;
    }
    if (p10.type !== RESOURCE_TYPE_STRING && p10.type !== RESOURCE_TYPE_INTEGER &&
        p10.type !== RESOURCE_TYPE_FLOAT) {
        return false;
    }
    if (p10.type === RESOURCE_TYPE_INTEGER || p10.type === RESOURCE_TYPE_FLOAT) {
        if (q10.getNumber(p10.id) >= 0) {
            return true;
        } else {
            return false;
        }
    }
    if (p10.type === RESOURCE_TYPE_STRING && !isValidDimensionString(q10.getStringSync(p10.id))) {
        return false;
    } else {
        return true;
    }
}

export class ChipComponent extends ViewPU {
    constructor(h10, i10, j10, k10 = -1, l10 = undefined, m10) {
        super(h10, j10, k10, m10);
        if (typeof l10 === 'function') {
            this.paramsGenerator_ = l10;
        }
        this.theme = defaultTheme;
        this.__chipSize = new SynchedPropertyObjectOneWayPU(i10.chipSize, this, 'chipSize');
        this.__allowClose = new SynchedPropertySimpleOneWayPU(i10.allowClose, this, 'allowClose');
        this.__closeOptions = new SynchedPropertyObjectOneWayPU(i10.closeOptions, this, 'closeOptions');
        this.__chipDirection = new SynchedPropertySimpleOneWayPU(i10.chipDirection, this, 'chipDirection');
        this.__prefixIcon = new SynchedPropertyObjectOneWayPU(i10.prefixIcon, this, 'prefixIcon');
        this.__prefixSymbol = new SynchedPropertyObjectOneWayPU(i10.prefixSymbol, this, 'prefixSymbol');
        this.__label = new SynchedPropertyObjectOneWayPU(i10.label, this, 'label');
        this.__suffixIcon = new SynchedPropertyObjectOneWayPU(i10.suffixIcon, this, 'suffixIcon');
        this.__suffixSymbol = new SynchedPropertyObjectOneWayPU(i10.suffixSymbol, this, 'suffixSymbol');
        this.__suffixSymbolOptions =
            new SynchedPropertyObjectOneWayPU(i10.suffixSymbolOptions, this, 'suffixSymbolOptions');
        this.__chipNodeBackgroundColor =
            new SynchedPropertyObjectOneWayPU(i10.chipNodeBackgroundColor, this, 'chipNodeBackgroundColor');
        this.__chipNodeActivatedBackgroundColor =
            new SynchedPropertyObjectOneWayPU(i10.chipNodeActivatedBackgroundColor, this,
                'chipNodeActivatedBackgroundColor');
        this.__isHovering = new ObservedPropertySimplePU(false, this, 'isHovering');
        this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(i10.chipNodeRadius, this, 'chipNodeRadius');
        this.__chipEnabled = new SynchedPropertySimpleOneWayPU(i10.chipEnabled, this, 'chipEnabled');
        this.__chipActivated = new SynchedPropertySimpleOneWayPU(i10.chipActivated, this, 'chipActivated');
        this.__chipAccessibilitySelectedType =
            new SynchedPropertySimpleOneWayPU(i10.chipAccessibilitySelectedType, this, 'chipAccessibilitySelectedType');
        this.__chipAccessibilityDescription =
            new SynchedPropertyObjectOneWayPU(i10.chipAccessibilityDescription, this, 'chipAccessibilityDescription');
        this.__chipAccessibilityLevel =
            new SynchedPropertySimpleOneWayPU(i10.chipAccessibilityLevel, this, 'chipAccessibilityLevel');
        this.__isHover = new ObservedPropertySimplePU(false, this, 'isHover');
        this.__chipScale = new ObservedPropertyObjectPU({ x: 1, y: 1 }, this, 'chipScale');
        this.__chipOpacity = new ObservedPropertySimplePU(1, this, 'chipOpacity');
        this.__chipBlendColor = new ObservedPropertyObjectPU(Color.Transparent, this, 'chipBlendColor');
        this.__deleteChip = new ObservedPropertySimplePU(false, this, 'deleteChip');
        this.__chipNodeOnFocus = new ObservedPropertySimplePU(false, this, 'chipNodeOnFocus');
        this.__useDefaultSuffixIcon = new ObservedPropertySimplePU(false, this, 'useDefaultSuffixIcon');
        this.chipNodeSize = {};
        this.onClose = noop;
        this.onClicked = noop;
        this.__suffixIconOnFocus = new ObservedPropertySimplePU(false, this, 'suffixIconOnFocus');
        this.__chipBreakPoints = new ObservedPropertySimplePU(BreakPointsType.SM, this, 'chipBreakPoints');
        this.smListener = mediaquery.matchMediaSync('(0vp<width) and (width<600vp)');
        this.mdListener = mediaquery.matchMediaSync('(600vp<=width) and (width<840vp)');
        this.lgListener = mediaquery.matchMediaSync('(840vp<=width)');
        this.isSuffixIconFocusStyleCustomized = this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 0;
        this.__isShowPressedBackGroundColor = new ObservedPropertySimplePU(false, this, 'isShowPressedBackGroundColor');
        this.__fontSizeScale = new ObservedPropertyObjectPU(0, this, 'fontSizeScale');
        this.__fontWeightScale = new ObservedPropertyObjectPU(0, this, 'fontWeightScale');
        this.callbacks = {
            onConfigurationUpdated: (n10) => {
                this.fontSizeScale = n10.fontSizeScale;
                this.fontWeightScale = n10.fontWeightScale;
            },
            onMemoryLevel() {
            }
        };
        this.callbackId = undefined;
        this.__prefixSymbolWidth =
            new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById('PrefixSymbolGlyph')?.size?.width),
                this, 'prefixSymbolWidth');
        this.__suffixSymbolWidth =
            new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById('SuffixSymbolGlyph')?.size?.width),
                this, 'suffixSymbolWidth');
        this.__allowCloseSymbolWidth =
            new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById('AllowCloseSymbolGlyph')?.size?.width),
                this, 'allowCloseSymbolWidth');
        this.__symbolEffect = new ObservedPropertyObjectPU(new SymbolEffect(), this, 'symbolEffect');
        this.setInitiallyProvidedValue(i10);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(g10) {
        if (g10.theme !== undefined) {
            this.theme = g10.theme;
        }
        if (g10.chipSize === undefined) {
            this.__chipSize.set(ChipSize.NORMAL);
        }
        if (g10.allowClose === undefined) {
            this.__allowClose.set(true);
        }
        if (g10.chipDirection === undefined) {
            this.__chipDirection.set(Direction.Auto);
        }
        if (g10.prefixIcon === undefined) {
            this.__prefixIcon.set({ src: '' });
        }
        if (g10.label === undefined) {
            this.__label.set({ text: '' });
        }
        if (g10.suffixIcon === undefined) {
            this.__suffixIcon.set({ src: '' });
        }
        if (g10.chipNodeBackgroundColor === undefined) {
            this.__chipNodeBackgroundColor.set(this.theme.chipNode.backgroundColor);
        }
        if (g10.chipNodeActivatedBackgroundColor === undefined) {
            this.__chipNodeActivatedBackgroundColor.set(this.theme.chipNode.activatedBackgroundColor);
        }
        if (g10.isHovering !== undefined) {
            this.isHovering = g10.isHovering;
        }
        if (g10.chipNodeRadius === undefined) {
            this.__chipNodeRadius.set(void (0));
        }
        if (g10.chipEnabled === undefined) {
            this.__chipEnabled.set(true);
        }
        if (g10.isHover !== undefined) {
            this.isHover = g10.isHover;
        }
        if (g10.chipScale !== undefined) {
            this.chipScale = g10.chipScale;
        }
        if (g10.chipOpacity !== undefined) {
            this.chipOpacity = g10.chipOpacity;
        }
        if (g10.chipBlendColor !== undefined) {
            this.chipBlendColor = g10.chipBlendColor;
        }
        if (g10.deleteChip !== undefined) {
            this.deleteChip = g10.deleteChip;
        }
        if (g10.chipNodeOnFocus !== undefined) {
            this.chipNodeOnFocus = g10.chipNodeOnFocus;
        }
        if (g10.useDefaultSuffixIcon !== undefined) {
            this.useDefaultSuffixIcon = g10.useDefaultSuffixIcon;
        }
        if (g10.chipNodeSize !== undefined) {
            this.chipNodeSize = g10.chipNodeSize;
        }
        if (g10.onClose !== undefined) {
            this.onClose = g10.onClose;
        }
        if (g10.onClicked !== undefined) {
            this.onClicked = g10.onClicked;
        }
        if (g10.suffixIconOnFocus !== undefined) {
            this.suffixIconOnFocus = g10.suffixIconOnFocus;
        }
        if (g10.chipBreakPoints !== undefined) {
            this.chipBreakPoints = g10.chipBreakPoints;
        }
        if (g10.smListener !== undefined) {
            this.smListener = g10.smListener;
        }
        if (g10.mdListener !== undefined) {
            this.mdListener = g10.mdListener;
        }
        if (g10.lgListener !== undefined) {
            this.lgListener = g10.lgListener;
        }
        if (g10.isSuffixIconFocusStyleCustomized !== undefined) {
            this.isSuffixIconFocusStyleCustomized = g10.isSuffixIconFocusStyleCustomized;
        }
        if (g10.isShowPressedBackGroundColor !== undefined) {
            this.isShowPressedBackGroundColor = g10.isShowPressedBackGroundColor;
        }
        if (g10.fontSizeScale !== undefined) {
            this.fontSizeScale = g10.fontSizeScale;
        }
        if (g10.fontWeightScale !== undefined) {
            this.fontWeightScale = g10.fontWeightScale;
        }
        if (g10.callbacks !== undefined) {
            this.callbacks = g10.callbacks;
        }
        if (g10.callbackId !== undefined) {
            this.callbackId = g10.callbackId;
        }
        if (g10.prefixSymbolWidth !== undefined) {
            this.prefixSymbolWidth = g10.prefixSymbolWidth;
        }
        if (g10.suffixSymbolWidth !== undefined) {
            this.suffixSymbolWidth = g10.suffixSymbolWidth;
        }
        if (g10.allowCloseSymbolWidth !== undefined) {
            this.allowCloseSymbolWidth = g10.allowCloseSymbolWidth;
        }
        if (g10.symbolEffect !== undefined) {
            this.symbolEffect = g10.symbolEffect;
        }
    }

    updateStateVars(f10) {
        this.__chipSize.reset(f10.chipSize);
        this.__allowClose.reset(f10.allowClose);
        this.__closeOptions.reset(f10.closeOptions);
        this.__chipDirection.reset(f10.chipDirection);
        this.__prefixIcon.reset(f10.prefixIcon);
        this.__prefixSymbol.reset(f10.prefixSymbol);
        this.__label.reset(f10.label);
        this.__suffixIcon.reset(f10.suffixIcon);
        this.__suffixSymbol.reset(f10.suffixSymbol);
        this.__suffixSymbolOptions.reset(f10.suffixSymbolOptions);
        this.__chipNodeBackgroundColor.reset(f10.chipNodeBackgroundColor);
        this.__chipNodeActivatedBackgroundColor.reset(f10.chipNodeActivatedBackgroundColor);
        this.__chipNodeRadius.reset(f10.chipNodeRadius);
        this.__chipEnabled.reset(f10.chipEnabled);
        this.__chipActivated.reset(f10.chipActivated);
        this.__chipAccessibilitySelectedType.reset(f10.chipAccessibilitySelectedType);
        this.__chipAccessibilityDescription.reset(f10.chipAccessibilityDescription);
        this.__chipAccessibilityLevel.reset(f10.chipAccessibilityLevel);
    }

    purgeVariableDependenciesOnElmtId(e10) {
        this.__chipSize.purgeDependencyOnElmtId(e10);
        this.__allowClose.purgeDependencyOnElmtId(e10);
        this.__closeOptions.purgeDependencyOnElmtId(e10);
        this.__chipDirection.purgeDependencyOnElmtId(e10);
        this.__prefixIcon.purgeDependencyOnElmtId(e10);
        this.__prefixSymbol.purgeDependencyOnElmtId(e10);
        this.__label.purgeDependencyOnElmtId(e10);
        this.__suffixIcon.purgeDependencyOnElmtId(e10);
        this.__suffixSymbol.purgeDependencyOnElmtId(e10);
        this.__suffixSymbolOptions.purgeDependencyOnElmtId(e10);
        this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(e10);
        this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(e10);
        this.__isHovering.purgeDependencyOnElmtId(e10);
        this.__chipNodeRadius.purgeDependencyOnElmtId(e10);
        this.__chipEnabled.purgeDependencyOnElmtId(e10);
        this.__chipActivated.purgeDependencyOnElmtId(e10);
        this.__chipAccessibilitySelectedType.purgeDependencyOnElmtId(e10);
        this.__chipAccessibilityDescription.purgeDependencyOnElmtId(e10);
        this.__chipAccessibilityLevel.purgeDependencyOnElmtId(e10);
        this.__isHover.purgeDependencyOnElmtId(e10);
        this.__chipScale.purgeDependencyOnElmtId(e10);
        this.__chipOpacity.purgeDependencyOnElmtId(e10);
        this.__chipBlendColor.purgeDependencyOnElmtId(e10);
        this.__deleteChip.purgeDependencyOnElmtId(e10);
        this.__chipNodeOnFocus.purgeDependencyOnElmtId(e10);
        this.__useDefaultSuffixIcon.purgeDependencyOnElmtId(e10);
        this.__suffixIconOnFocus.purgeDependencyOnElmtId(e10);
        this.__chipBreakPoints.purgeDependencyOnElmtId(e10);
        this.__isShowPressedBackGroundColor.purgeDependencyOnElmtId(e10);
        this.__fontSizeScale.purgeDependencyOnElmtId(e10);
        this.__fontWeightScale.purgeDependencyOnElmtId(e10);
        this.__prefixSymbolWidth.purgeDependencyOnElmtId(e10);
        this.__suffixSymbolWidth.purgeDependencyOnElmtId(e10);
        this.__allowCloseSymbolWidth.purgeDependencyOnElmtId(e10);
        this.__symbolEffect.purgeDependencyOnElmtId(e10);
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

    set chipSize(d10) {
        this.__chipSize.set(d10);
    }

    get allowClose() {
        return this.__allowClose.get();
    }

    set allowClose(c10) {
        this.__allowClose.set(c10);
    }

    get closeOptions() {
        return this.__closeOptions.get();
    }

    set closeOptions(b10) {
        this.__closeOptions.set(b10);
    }

    get chipDirection() {
        return this.__chipDirection.get();
    }

    set chipDirection(a10) {
        this.__chipDirection.set(a10);
    }

    get prefixIcon() {
        return this.__prefixIcon.get();
    }

    set prefixIcon(z9) {
        this.__prefixIcon.set(z9);
    }

    get prefixSymbol() {
        return this.__prefixSymbol.get();
    }

    set prefixSymbol(y9) {
        this.__prefixSymbol.set(y9);
    }

    get label() {
        return this.__label.get();
    }

    set label(x9) {
        this.__label.set(x9);
    }

    get suffixIcon() {
        return this.__suffixIcon.get();
    }

    set suffixIcon(w9) {
        this.__suffixIcon.set(w9);
    }

    get suffixSymbol() {
        return this.__suffixSymbol.get();
    }

    set suffixSymbol(v9) {
        this.__suffixSymbol.set(v9);
    }

    get suffixSymbolOptions() {
        return this.__suffixSymbolOptions.get();
    }

    set suffixSymbolOptions(u9) {
        this.__suffixSymbolOptions.set(u9);
    }

    get chipNodeBackgroundColor() {
        return this.__chipNodeBackgroundColor.get();
    }

    set chipNodeBackgroundColor(t9) {
        this.__chipNodeBackgroundColor.set(t9);
    }

    get chipNodeActivatedBackgroundColor() {
        return this.__chipNodeActivatedBackgroundColor.get();
    }

    set chipNodeActivatedBackgroundColor(s9) {
        this.__chipNodeActivatedBackgroundColor.set(s9);
    }

    get isHovering() {
        return this.__isHovering.get();
    }

    set isHovering(r9) {
        this.__isHovering.set(r9);
    }

    get chipNodeRadius() {
        return this.__chipNodeRadius.get();
    }

    set chipNodeRadius(q9) {
        this.__chipNodeRadius.set(q9);
    }

    get chipEnabled() {
        return this.__chipEnabled.get();
    }

    set chipEnabled(p9) {
        this.__chipEnabled.set(p9);
    }

    get chipActivated() {
        return this.__chipActivated.get();
    }

    set chipActivated(o9) {
        this.__chipActivated.set(o9);
    }

    get chipAccessibilitySelectedType() {
        return this.__chipAccessibilitySelectedType.get();
    }

    set chipAccessibilitySelectedType(n9) {
        this.__chipAccessibilitySelectedType.set(n9);
    }

    get chipAccessibilityDescription() {
        return this.__chipAccessibilityDescription.get();
    }

    set chipAccessibilityDescription(m9) {
        this.__chipAccessibilityDescription.set(m9);
    }

    get chipAccessibilityLevel() {
        return this.__chipAccessibilityLevel.get();
    }

    set chipAccessibilityLevel(l9) {
        this.__chipAccessibilityLevel.set(l9);
    }

    get isHover() {
        return this.__isHover.get();
    }

    set isHover(k9) {
        this.__isHover.set(k9);
    }

    get chipScale() {
        return this.__chipScale.get();
    }

    set chipScale(j9) {
        this.__chipScale.set(j9);
    }

    get chipOpacity() {
        return this.__chipOpacity.get();
    }

    set chipOpacity(i9) {
        this.__chipOpacity.set(i9);
    }

    get chipBlendColor() {
        return this.__chipBlendColor.get();
    }

    set chipBlendColor(h9) {
        this.__chipBlendColor.set(h9);
    }

    get deleteChip() {
        return this.__deleteChip.get();
    }

    set deleteChip(g9) {
        this.__deleteChip.set(g9);
    }

    get chipNodeOnFocus() {
        return this.__chipNodeOnFocus.get();
    }

    set chipNodeOnFocus(f9) {
        this.__chipNodeOnFocus.set(f9);
    }

    get useDefaultSuffixIcon() {
        return this.__useDefaultSuffixIcon.get();
    }

    set useDefaultSuffixIcon(e9) {
        this.__useDefaultSuffixIcon.set(e9);
    }

    get suffixIconOnFocus() {
        return this.__suffixIconOnFocus.get();
    }

    set suffixIconOnFocus(d9) {
        this.__suffixIconOnFocus.set(d9);
    }

    get chipBreakPoints() {
        return this.__chipBreakPoints.get();
    }

    set chipBreakPoints(c9) {
        this.__chipBreakPoints.set(c9);
    }

    get isShowPressedBackGroundColor() {
        return this.__isShowPressedBackGroundColor.get();
    }

    set isShowPressedBackGroundColor(b9) {
        this.__isShowPressedBackGroundColor.set(b9);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(a9) {
        this.__fontSizeScale.set(a9);
    }

    get fontWeightScale() {
        return this.__fontWeightScale.get();
    }

    set fontWeightScale(z8) {
        this.__fontWeightScale.set(z8);
    }

    get prefixSymbolWidth() {
        return this.__prefixSymbolWidth.get();
    }

    set prefixSymbolWidth(y8) {
        this.__prefixSymbolWidth.set(y8);
    }

    get suffixSymbolWidth() {
        return this.__suffixSymbolWidth.get();
    }

    set suffixSymbolWidth(x8) {
        this.__suffixSymbolWidth.set(x8);
    }

    get allowCloseSymbolWidth() {
        return this.__allowCloseSymbolWidth.get();
    }

    set allowCloseSymbolWidth(w8) {
        this.__allowCloseSymbolWidth.set(w8);
    }

    get symbolEffect() {
        return this.__symbolEffect.get();
    }

    set symbolEffect(v8) {
        this.__symbolEffect.set(v8);
    }

    isChipSizeEnum() {
        return typeof (this.chipSize) === 'string';
    }

    isShowCloseIconMargin() {
        return this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 0 && this.allowClose;
    }

    getLabelFontSize() {
        if (this.label?.fontSize !== void (0) && this.toVp(this.label.fontSize) >= 0) {
            return this.label.fontSize;
        } else {
            if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
                try {
                    resourceManager.getSystemResourceManager()
                        .getNumberByName((this.theme.label.smallFontSize.params[0]).split('.')[2]);
                    return this.theme.label.smallFontSize;
                } catch (u8) {
                    return this.theme.label.defaultFontSize;
                }
            } else {
                try {
                    resourceManager.getSystemResourceManager()
                        .getNumberByName((this.theme.label.normalFontSize.params[0]).split('.')[2]);
                    return this.theme.label.normalFontSize;
                } catch (t8) {
                    return this.theme.label.defaultFontSize;
                }
            }
        }
    }

    defaultSymbolFontsize() {
        return this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ? this.theme.defaultSymbol.smallSymbolFontSize :
        this.theme.defaultSymbol.normalSymbolFontSize;
    }

    resourceToVp(r8) {
        let s8 = LengthMetrics.resource(r8);
        return this.lengthMetricsToVp(s8);
    }

    getActiveFontColor() {
        return this.chipNodeOnFocus ? this.theme.label.focusActiveFontColor : this.theme.label.activatedFontColor;
    }

    getFontColor() {
        return this.chipNodeOnFocus ? this.theme.label.focusFontColor : this.theme.label.fontColor;
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
        return this.resourceToNumber(this.theme.label.fontWeight, FontWeight.Regular);
    }

    lengthMetricsToVp(p8) {
        let q8 = 0;
        if (p8) {
            switch (p8.unit) {
                case LengthUnit.PX:
                    return px2vp(p8.value);
                case LengthUnit.VP:
                    return p8.value;
                case LengthUnit.FP:
                    return px2vp(fp2px(p8.value));
                case LengthUnit.PERCENT:
                    return Number.NEGATIVE_INFINITY;
                case LengthUnit.LPX:
                    return px2vp(lpx2px(p8.value));
            }
        }
        return q8;
    }

    toVp(i8) {
        if (i8 === void (0)) {
            return Number.NEGATIVE_INFINITY;
        }
        switch (typeof (i8)) {
            case 'number':
                return i8;
            case 'object':
                try {
                    let o8 = this.lengthMetricsToVp(LengthMetrics.resource(i8));
                    if (o8 === 0 &&
                        !isValidResource(getContext(this), i8)) {
                        return Number.NEGATIVE_INFINITY;
                    }
                    return o8;
                } catch (n8) {
                    return Number.NEGATIVE_INFINITY;
                }
            case 'string':
                let j8 = new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i');
                let k8 = i8.match(j8);
                if (!k8) {
                    return Number.NEGATIVE_INFINITY;
                }
                let l8 = Number(k8?.[1] ?? 0);
                let m8 = k8?.[2] ?? 'vp';
                switch (m8.toLowerCase()) {
                    case 'px':
                        l8 = px2vp(l8);
                        break;
                    case 'fp':
                        l8 = px2vp(fp2px(l8));
                        break;
                    case 'lpx':
                        l8 = px2vp(lpx2px(l8));
                        break;
                    case '%':
                        l8 = Number.NEGATIVE_INFINITY;
                        break;
                    case 'vp':
                        break;
                    default:
                        break;
                }
                return l8;
            default:
                return Number.NEGATIVE_INFINITY;
        }
    }

    getChipNodeBorderWidth() {
        return this.resourceToVp(this.theme.chipNode.defaultBorderWidth);
    }

    getChipNodeBorderColor() {
        let h8 = this.theme.chipNode;
        return this.getChipActive() ? h8.activatedBorderColor : h8.borderColor;
    }

    getLabelMargin() {
        let g8 = { left: 0, right: 0 };
        if (this.label?.labelMargin?.left !== void (0) && this.toVp(this.label.labelMargin.left) >= 0) {
            g8.left = this.label?.labelMargin?.left;
        } else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                g8.left = this.theme.label.smallMargin.left;
            } else {
                g8.left = this.theme.label.normalMargin.left;
            }
        }
        if (this.label?.labelMargin?.right !== void (0) && this.toVp(this.label.labelMargin.right) >= 0) {
            g8.right = this.label?.labelMargin?.right;
        } else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
            this.suffixIcon?.src || this.useDefaultSuffixIcon) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                g8.right = this.theme.label.smallMargin.right;
            } else {
                g8.right = this.theme.label.normalMargin.right;
            }
        }
        return g8;
    }

    getLocalizedLabelMargin() {
        let f8 = { start: LengthMetrics.vp(0), end: LengthMetrics.vp(0) };
        if (this.label?.localizedLabelMargin?.start?.value !== void (0) &&
            this.lengthMetricsToVp(this.label.localizedLabelMargin.start) >= 0) {
            f8.start = this.label?.localizedLabelMargin?.start;
        } else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                f8.start = this.theme.label.localizedSmallMargin.start;
            } else {
                f8.start = this.theme.label.localizedNormalMargin.start;
            }
        }
        if (this.label?.localizedLabelMargin?.end?.value !== void (0) &&
            this.lengthMetricsToVp(this.label.localizedLabelMargin.end) >= 0) {
            f8.end = this.label?.localizedLabelMargin?.end;
        } else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
            this.suffixIcon?.src || this.useDefaultSuffixIcon || this.isShowCloseIconMargin()) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                f8.end = this.theme.label.localizedSmallMargin.end;
            } else {
                f8.end = this.theme.label.localizedNormalMargin.end;
            }
        }
        return f8;
    }

    getLabelStartEndVp() {
        let d8 = this.getLocalizedLabelMargin();
        if (this.label && (this.label.labelMargin !== void (0)) && (this.label.localizedLabelMargin === void (0))) {
            let e8 = this.getLabelMargin();
            return {
                start: LengthMetrics.vp(this.toVp(e8.left)),
                end: LengthMetrics.vp(this.toVp(e8.right))
            };
        }
        return {
            start: LengthMetrics.vp(this.lengthMetricsToVp(d8.start)),
            end: LengthMetrics.vp(this.lengthMetricsToVp(d8.end))
        };
    }

    getActualLabelMargin() {
        let c8 = this.getLocalizedLabelMargin();
        if (this.label && this.label.localizedLabelMargin !== void (0)) {
            return c8;
        }
        if (this.label && this.label.labelMargin !== void (0)) {
            return this.getLabelMargin();
        }
        return c8;
    }

    getSuffixIconSize() {
        let b8 = { width: 0, height: 0 };
        if (this.suffixIcon?.size?.width !== void (0) && this.toVp(this.suffixIcon?.size?.width) >= 0) {
            b8.width = this.suffixIcon?.size?.width;
        } else {
            if (this.getSuffixIconSrc()) {
                b8.width = this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ?
                this.theme.suffixIcon.smallSize.width : this.theme.suffixIcon.normalSize.width;
            } else {
                b8.width = 0;
            }
        }
        if (this.suffixIcon?.size?.height !== void (0) && this.toVp(this.suffixIcon?.size?.height) >= 0) {
            b8.height = this.suffixIcon?.size?.height;
        } else {
            if (this.getSuffixIconSrc()) {
                b8.height = this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ?
                this.theme.suffixIcon.smallSize.height : this.theme.suffixIcon.normalSize.height;
            } else {
                b8.height = 0;
            }
        }
        return b8;
    }

    getPrefixIconSize() {
        let a8 = { width: 0, height: 0 };
        if (this.prefixIcon?.size?.width !== void (0) && this.toVp(this.prefixIcon?.size?.width) >= 0) {
            a8.width = this.prefixIcon?.size?.width;
        } else {
            if (this.prefixIcon?.src) {
                a8.width =
                    this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ? this.theme.prefixIcon.smallSize.width :
                    this.theme.prefixIcon.normalSize.width;
            } else {
                a8.width = 0;
            }
        }
        if (this.prefixIcon?.size?.height !== void (0) && this.toVp(this.prefixIcon?.size?.height) >= 0) {
            a8.height = this.prefixIcon?.size?.height;
        } else {
            if (this.prefixIcon?.src) {
                a8.height =
                    this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ? this.theme.prefixIcon.smallSize.height :
                    this.theme.prefixIcon.normalSize.height;
            } else {
                a8.height = 0;
            }
        }
        return a8;
    }

    getDefaultActiveIconColor(z7) {
        if (z7 === IconType.PREFIX_ICON) {
            return this.chipNodeOnFocus ? this.theme.prefixIcon.focusActivatedColor :
            this.theme.prefixIcon.activatedFillColor;
        } else {
            return this.chipNodeOnFocus ? this.theme.suffixIcon.focusActivatedColor :
            this.theme.suffixIcon.activatedFillColor;
        }
    }

    getDefaultFillIconColor(y7) {
        if (y7 === IconType.PREFIX_ICON) {
            return this.chipNodeOnFocus ? this.theme.prefixIcon.focusFillColor : this.theme.prefixIcon.fillColor;
        } else {
            return this.chipNodeOnFocus ? this.theme.suffixIcon.focusFillColor : this.theme.suffixIcon.fillColor;
        }
    }

    getSymbolActiveColor(x7) {
        if (x7 === IconType.PREFIX_SYMBOL) {
            return this.getColorArray(this.prefixIcon?.activatedFillColor, this.theme.prefixIcon.focusActivatedColor,
                this.theme.prefixIcon.activatedFillColor);
        } else if (x7 === IconType.SUFFIX_SYMBOL) {
            return this.getColorArray(this.suffixIcon?.activatedFillColor, this.theme.suffixIcon.focusActivatedColor,
                this.theme.suffixIcon.activatedFillColor);
        } else {
            return this.theme.defaultSymbol.activatedFontColor;
        }
    }

    getSymbolFillColor(w7) {
        if (w7 === IconType.PREFIX_SYMBOL) {
            return this.getColorArray(this.prefixIcon?.fillColor, this.theme.prefixIcon.focusFillColor,
                this.theme.prefixIcon.fillColor);
        } else if (w7 === IconType.SUFFIX_SYMBOL) {
            return this.getColorArray(this.suffixIcon?.fillColor, this.theme.suffixIcon.focusFillColor,
                this.theme.suffixIcon.fillColor);
        } else {
            return this.theme.defaultSymbol.normalFontColor;
        }
    }

    getColorArray(t7, u7, v7) {
        if (t7) {
            return [t7];
        }
        return this.chipNodeOnFocus ? [u7] : [v7];
    }

    getPrefixIconFilledColor() {
        if (this.getChipActive()) {
            return this.prefixIcon?.activatedFillColor ?? this.getDefaultActiveIconColor(IconType.PREFIX_ICON);
        }
        return this.prefixIcon?.fillColor ?? this.getDefaultFillIconColor(IconType.PREFIX_ICON);
    }

    getSuffixIconFilledColor() {
        if (this.getChipActive()) {
            return this.suffixIcon?.activatedFillColor ?? this.getDefaultActiveIconColor(IconType.SUFFIX_ICON);
        }
        return this.suffixIcon?.fillColor ?? this.getDefaultFillIconColor(IconType.SUFFIX_ICON);
    }

    getDefaultSymbolColor(s7) {
        if (this.getChipActive()) {
            return this.getSymbolActiveColor(s7);
        }
        return this.getSymbolFillColor(s7);
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
        return !this.isSuffixIconFocusStyleCustomized && ((this.useDefaultSuffixIcon && (this.allowClose ?? true)) ||
            this.suffixIcon?.action !== void (0));
    }

    getChipNodePadding() {
        return (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) ? this.theme.chipNode.localizedSmallPadding :
        this.theme.chipNode.localizedNormalPadding;
    }

    getChipNodeRadius() {
        if (this.chipNodeRadius !== void (0) && this.toVp(this.chipNodeRadius) >= 0) {
            return this.chipNodeRadius;
        } else {
            return ((this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) ?
            this.theme.chipNode.smallBorderRadius : this.theme.chipNode.normalBorderRadius);
        }
    }

    getChipNodeBackGroundColor() {
        let o7;
        let p7 = this.theme.chipNode;
        if (this.getChipActive()) {
            o7 = this.chipNodeOnFocus && !this.isSetActiveChipBgColor() ? p7.focusActivatedBgColor :
                this.chipNodeActivatedBackgroundColor ?? this.theme.chipNode.activatedBackgroundColor;
        } else {
            o7 = this.chipNodeOnFocus && !this.isSetNormalChipBgColor() ? p7.focusBgColor :
                this.chipNodeBackgroundColor ?? this.theme.chipNode.backgroundColor;
        }
        let q7;
        try {
            q7 = ColorMetrics.resourceColor(o7);
        } catch (r7) {
            hilog.error(0x3900, 'Ace', `Chip resourceColor, error: ${r7.toString()}`);
            q7 = ColorMetrics.resourceColor(Color.Transparent);
        }
        if (!this.isShowPressedBackGroundColor) {
            return q7.color;
        }
        return q7.blendColor(ColorMetrics.resourceColor('#19000000'))
            .color;
    }

    getChipNodeHeight() {
        if (this.isChipSizeEnum()) {
            return this.chipSize === ChipSize.SMALL ? this.theme.chipNode.smallHeight :
            this.theme.chipNode.normalHeight;
        } else {
            this.chipNodeSize = this.chipSize;
            return (this.chipNodeSize?.height !== void (0) && this.toVp(this.chipNodeSize?.height) >= 0) ?
            this.toVp(this.chipNodeSize?.height) : this.theme.chipNode.normalHeight;
        }
    }

    getLabelWidth() {
        return px2vp(measure.measureText({
            textContent: this.label?.text ?? '',
            fontSize: this.getLabelFontSize(),
            fontFamily: this.label?.fontFamily ?? this.theme.label.fontFamily,
            fontWeight: this.getLabelFontWeight(),
            maxLines: 1,
            overflow: TextOverflow.Ellipsis,
            textAlign: TextAlign.Center
        }));
    }

    getCalculateChipNodeWidth() {
        let m7 = 0;
        let n7 = this.getLabelStartEndVp();
        m7 += this.getChipNodeBorderWidth() * 2;
        m7 += this.getChipNodePadding().start?.value ?? 0;
        m7 += this.toVp(this.getPrefixChipWidth());
        m7 += this.toVp(n7.start?.value ?? 0);
        m7 += this.getLabelWidth();
        m7 += this.toVp(n7.end?.value ?? 0);
        m7 += this.toVp(this.getSuffixChipWidth());
        m7 += this.getChipNodePadding().end?.value ?? 0;
        return m7;
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
        return this.getCalculateChipNodeWidth() - this.getLabelWidth() + this.theme.chipNode.minLabelWidth;
    }

    getChipEnable() {
        return this.chipEnabled || this.chipEnabled === void (0);
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

    handleTouch(l7) {
        if (!this.getChipEnable()) {
            return;
        }
        if (this.isHover) {
            if (l7.type === TouchType.Down || l7.type === TouchType.Move) {
                this.isShowPressedBackGroundColor = true;
            } else if (l7.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            } else {
                this.isShowPressedBackGroundColor = false;
            }
        } else {
            if (l7.type === TouchType.Down || l7.type === TouchType.Move) {
                this.isShowPressedBackGroundColor = true;
            } else if (l7.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            } else {
                this.isShowPressedBackGroundColor = false;
            }
        }
    }

    hoverAnimate(k7) {
        if (!this.getChipEnable()) {
            return;
        }
        this.isHover = k7;
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
        Context.animateTo({
            duration: 150, curve: Curve.FastOutLinearIn, onFinish: () => {
                this.deleteChip = true;
            }
        }, () => {
            this.chipScale = { x: 0.85, y: 0.85 };
        });
    }

    getSuffixIconSrc() {
        this.useDefaultSuffixIcon = !this.suffixIcon?.src && (this.allowClose ?? true);
        return this.useDefaultSuffixIcon ? this.theme.suffixIcon.defaultDeleteIcon : (this.suffixIcon?.src ?? void (0));
    }

    getChipNodeWidth() {
        if (!this.isChipSizeEnum()) {
            this.chipNodeSize = this.chipSize;
            if (this.chipNodeSize?.width !== void (0) && this.toVp(this.chipNodeSize.width) >= 0) {
                return this.toVp(this.chipNodeSize.width);
            }
        }
        let h7 = this.getChipConstraintWidth();
        return Math.min(Math.max(this.getCalculateChipNodeWidth(), h7.minWidth), h7.maxWidth);
    }

    getFocusOverlaySize() {
        return {
            width: Math.max(this.getChipNodeWidth(), this.getChipConstraintWidth().minWidth) + 8,
            height: this.getChipNodeHeight() + 8
        };
    }

    getChipConstraintWidth() {
        let e7 = this.getReserveChipNodeWidth();
        let f7 = this.getCalculateChipNodeWidth();
        let g7;
        switch (this.chipBreakPoints) {
            case BreakPointsType.SM:
                g7 = {
                    minWidth: e7,
                    maxWidth: Math.min(f7, this.theme.chipNode.breakPointConstraintWidth.breakPointSmMaxWidth)
                };
                break;
            case BreakPointsType.MD:
                g7 = {
                    minWidth: Math.max(f7, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(f7, this.theme.chipNode.breakPointConstraintWidth.breakPointMdMaxWidth)
                };
                break;
            case BreakPointsType.LG:
                g7 = {
                    minWidth: Math.max(f7, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(f7, this.theme.chipNode.breakPointConstraintWidth.breakPointLgMaxWidth)
                };
                break;
            default:
                g7 = { minWidth: e7, maxWidth: f7 };
                break;
        }
        g7.minWidth = Math.min(Math.max(this.getCalculateChipNodeWidth(), g7.minWidth), g7.maxWidth);
        g7.minHeight = this.getChipNodeHeight();
        if (!this.isChipSizeEnum() && this.chipNodeSize?.height !== void (0) &&
            this.toVp(this.chipNodeSize?.height) >= 0) {
            g7.maxHeight = this.toVp(this.chipNodeSize.height);
            g7.minHeight = this.toVp(this.chipNodeSize.height);
        }
        if (!this.isChipSizeEnum() && this.chipNodeSize?.width !== void (0) &&
            this.toVp(this.chipNodeSize?.width) >= 0) {
            g7.minWidth = this.toVp(this.chipNodeSize.width);
            g7.maxWidth = this.toVp(this.chipNodeSize.width);
        } else if (this.toVp(this.fontSizeScale) >= this.theme.chipNode.suitAgeScale) {
            g7.minWidth = void (0);
            g7.maxWidth = void (0);
        }
        return g7;
    }

    focusOverlay(s6 = null) {
        this.observeComponentCreation2((c7, d7) => {
            Stack.create();
            Stack.direction(this.chipDirection);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((v6, w6) => {
            If.create();
            if (this.chipNodeOnFocus && !this.suffixIconOnFocus) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a7, b7) => {
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
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Stack.pop();
    }

    aboutToAppear() {
        let l6 = this.getUIContext();
        this.fontSizeScale = l6.getHostContext()?.config?.fontSizeScale ?? 1;
        this.smListener.on('change', (r6) => {
            if (r6.matches) {
                this.chipBreakPoints = BreakPointsType.SM;
            }
        });
        this.mdListener.on('change', (q6) => {
            if (q6.matches) {
                this.chipBreakPoints = BreakPointsType.MD;
            }
        });
        this.lgListener.on('change', (p6) => {
            if (p6.matches) {
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
            return ColorMetrics.resourceColor(this.chipNodeActivatedBackgroundColor).color !==
            ColorMetrics.resourceColor(this.theme.chipNode.activatedBackgroundColor).color;
        } catch (k6) {
            console.error(`[Chip] failed to get resourceColor`);
            return false;
        }
    }

    isSetNormalChipBgColor() {
        if (!this.chipNodeBackgroundColor) {
            return false;
        }
        try {
            return ColorMetrics.resourceColor(this.chipNodeBackgroundColor).color !==
            ColorMetrics.resourceColor(this.theme.chipNode.backgroundColor).color;
        } catch (j6) {
            console.error(`[Chip] failed to get resourceColor`);
            return false;
        }
    }

    getShadowStyles() {
        if (!this.chipNodeOnFocus) {
            return undefined;
        }
        return this.resourceToNumber(this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ?
        this.theme.chipNode.smallShadowStyle :
        this.theme.chipNode.normalShadowStyle, -1);
    }

    aboutToDisappear() {
        this.smListener.off('change');
        this.mdListener.off('change');
        this.lgListener.off('change');
        if (this.callbackId) {
            this.getUIContext()
                .getHostContext()
            ?.getApplicationContext()
            ?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
    }

    chipBuilder(r3 = null) {
        this.observeComponentCreation2((x5, y5) => {
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
                        x: 1, y: 1
                    };
                }
            });
            Button.onTouch((i6) => {
                this.handleTouch(i6);
            });
            Button.onHover((h6) => {
                if (h6) {
                    this.isShowPressedBackGroundColor = true;
                } else {
                    if (!this.isShowPressedBackGroundColor && h6) {
                        this.isShowPressedBackGroundColor = true;
                    } else {
                        this.isShowPressedBackGroundColor = false;
                    }
                }
            });
            Button.onKeyEvent((e6) => {
                if (!e6 || e6.type === null || e6.type !== KeyType.Down) {
                    return;
                }
                let f6 = e6.keyCode === KeyCode.KEYCODE_FORWARD_DEL &&
                    !this.suffixIconOnFocus;
                let g6 = e6.keyCode === KeyCode.KEYCODE_ENTER && this.allowClose && !this.suffixIcon?.src &&
                this.isSuffixIconFocusStyleCustomized;
                if (f6 || g6) {
                    this.deleteChipNodeAnimate();
                }
            });
            Button.onClick(this.onClicked === noop ? undefined : this.onClicked.bind(this));
        }, Button);
        this.observeComponentCreation2((v5, w5) => {
            Row.create();
            Row.direction(this.chipDirection);
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.Center);
            Row.padding(this.getChipNodePadding());
            Row.constraintSize(this.getChipConstraintWidth());
        }, Row);
        this.observeComponentCreation2((h5, i5) => {
            If.create();
            if (this.prefixSymbol?.normal || this.prefixSymbol?.activated) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q5, r5) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.defaultSymbolFontsize());
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.PREFIX_SYMBOL));
                        SymbolGlyph.attributeModifier.bind(this)(this.getPrefixSymbolModifier());
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect),
                            this.theme.defaultSymbol.defaultEffect);
                        SymbolGlyph.onSizeChange((t5, u5) => {
                            this.prefixSymbolWidth = u5?.width;
                        });
                        SymbolGlyph.key('PrefixSymbolGlyph');
                    }, SymbolGlyph);
                });
            } else if (this.prefixIcon?.src !== '') {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((m5, n5) => {
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
                this.ifElseBranchUpdateFunction(2, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((f5, g5) => {
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
        this.observeComponentCreation2((x3, y3) => {
            If.create();
            if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d5, e5) => {
                        Button.createWithChild({ type: ButtonType.Normal });
                        Button.onClick(this.getSuffixSymbolAction());
                        Button.accessibilityText(this.getSuffixSymbolAccessibilityText());
                        Button.accessibilityDescription(this.getSuffixSymbolAccessibilityDescription());
                        Button.accessibilityLevel(this.getSuffixSymbolAccessibilityLevel());
                        Button.backgroundColor(Color.Transparent);
                        Button.borderRadius(0);
                        Button.padding(0);
                        Button.stateEffect(false);
                        Button.focusable(!this.isSuffixIconFocusStyleCustomized);
                    }, Button);
                    this.observeComponentCreation2((y4, z4) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.defaultSymbolFontsize());
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_SYMBOL));
                        SymbolGlyph.attributeModifier.bind(this)(this.getSuffixSymbolModifier());
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect),
                            this.theme.defaultSymbol.defaultEffect);
                        SymbolGlyph.onSizeChange((b5, c5) => {
                            this.suffixSymbolWidth = c5?.width;
                        });
                        SymbolGlyph.key('SuffixSymbolGlyph');
                    }, SymbolGlyph);
                    Button.pop();
                });
            } else if (this.suffixIcon?.src !== '') {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((s4, t4) => {
                        Button.createWithChild({ type: ButtonType.Normal });
                        Button.backgroundColor(Color.Transparent);
                        Button.borderRadius(0);
                        Button.padding(0);
                        Button.size(this.getSuffixIconSize());
                        Button.accessibilityText(this.getSuffixIconAccessibilityText());
                        Button.accessibilityDescription(this.getSuffixIconAccessibilityDescription());
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
                    this.observeComponentCreation2((o4, p4) => {
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
                    this.observeComponentCreation2((i4, j4) => {
                        Button.createWithChild({ type: ButtonType.Normal });
                        Button.backgroundColor(Color.Transparent);
                        Button.borderRadius(0);
                        Button.padding(0);
                        Button.accessibilityText(this.getCloseIconAccessibilityText());
                        Button.accessibilityDescription(this.getCloseIconAccessibilityDescription());
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
                    this.observeComponentCreation2((d4, e4) => {
                        SymbolGlyph.create({
                            'id': -1,
                            'type': 40000,
                            params: ['sys.symbol.xmark'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.fontSize(this.defaultSymbolFontsize());
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_SYMBOL));
                        SymbolGlyph.onSizeChange((g4, h4) => {
                            this.allowCloseSymbolWidth = h4?.width;
                        });
                        SymbolGlyph.key('AllowCloseSymbolGlyph');
                    }, SymbolGlyph);
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(3, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
        Button.pop();
    }

    getSuffixSymbolAccessibilityLevel() {
        if (this.getChipActive()) {
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
        if (this.getChipActive()) {
            if (typeof this.suffixSymbolOptions?.activatedAccessibility?.accessibilityDescription !== 'undefined') {
                return this.suffixSymbolOptions.activatedAccessibility.accessibilityDescription;
            }
            return undefined;
        }
        if (typeof this.suffixSymbolOptions?.normalAccessibility?.accessibilityDescription !== 'undefined') {
            return this.suffixSymbolOptions.normalAccessibility.accessibilityDescription;
        }
        return undefined;
    }

    getSuffixSymbolAccessibilityText() {
        if (this.getChipActive()) {
            if (typeof this.suffixSymbolOptions?.activatedAccessibility?.accessibilityText !== 'undefined') {
                return this.suffixSymbolOptions.activatedAccessibility.accessibilityText;
            }
            return undefined;
        }
        if (typeof this.suffixSymbolOptions?.normalAccessibility?.accessibilityText !== 'undefined') {
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
        if (this.getChipAccessibilitySelectedType() === AccessibilitySelectedType.SELECTED) {
            return this.getChipActive();
        }
        return undefined;
    }

    getAccessibilityChecked() {
        if (this.getChipAccessibilitySelectedType() === AccessibilitySelectedType.CHECKED) {
            return this.getChipActive();
        }
        return undefined;
    }

    getChipAccessibilitySelectedType() {
        if (typeof this.chipActivated === 'undefined') {
            return AccessibilitySelectedType.CLICKED;
        }
        return this.chipAccessibilitySelectedType ?? AccessibilitySelectedType.CHECKED;
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
            return undefined;
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

    getSuffixIconAccessibilityLevel() {
        if (this.suffixIcon?.accessibilityLevel === 'no' ||
            this.suffixIcon?.accessibilityLevel === 'no-hide-descendants') {
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

    resourceToNumber(m3, n3) {
        if (!m3 || !m3.type) {
            console.error('[Chip] failed: resource get fail.');
            return n3;
        }
        const o3 = this.getUIContext().getHostContext()?.resourceManager;
        if (!o3) {
            console.error('[Chip] failed to get resourceManager.');
            return n3;
        }
        switch (m3.type) {
            case RESOURCE_TYPE_FLOAT:
            case RESOURCE_TYPE_INTEGER:
                try {
                    if (m3.id !== -1) {
                        return o3.getNumber(m3);
                    }
                    return o3.getNumberByName(m3.params[0].split('.')[2]);
                } catch (p3) {
                    console.error(`[Chip] get resource error, return defaultValue`);
                    return n3;
                }
            default:
                return n3;
        }
    }

    initialRender() {
        this.observeComponentCreation2((i3, j3) => {
            If.create();
            if (!this.deleteChip) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.chipBuilder.bind(this)();
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