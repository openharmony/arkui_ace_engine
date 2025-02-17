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
(function (p10) {
    p10['NORMAL'] = 'NORMAL';
    p10['SMALL'] = 'SMALL';
})(ChipSize || (ChipSize = {}));
var IconType;
(function (o10) {
    o10['PREFIX_ICON'] = 'PREFIXICON';
    o10['SUFFIX_ICON'] = 'SUFFIXICON';
    o10['PREFIX_SYMBOL'] = 'PREFIXSYMBOL';
    o10['SUFFIX_SYMBOL'] = 'SUFFIXSYMBOL';
})(IconType || (IconType = {}));
var BreakPointsType;
(function (n10) {
    n10['SM'] = 'SM';
    n10['MD'] = 'MD';
    n10['LG'] = 'LG';
})(BreakPointsType || (BreakPointsType = {}));

export var AccessibilitySelectedType;
(function (m10) {
    m10[m10['CLICKED'] = 0] = 'CLICKED';
    m10[m10['CHECKED'] = 1] = 'CHECKED';
    m10[m10['SELECTED'] = 2] = 'SELECTED';
})(AccessibilitySelectedType || (AccessibilitySelectedType = {}));
const noop = () => {
};

export function Chip(e10, f10 = null) {
    const g10 = e10;
    {
        (f10 ? f10 : this).observeComponentCreation2((h10, i10, j10 = g10) => {
            if (i10) {
                let k10 = new ChipComponent(f10 ? f10 : this, {
                    chipSize: j10.size,
                    prefixIcon: j10.prefixIcon,
                    prefixSymbol: j10.prefixSymbol,
                    label: j10.label,
                    suffixIcon: j10.suffixIcon,
                    suffixSymbol: j10.suffixSymbol,
                    suffixSymbolOptions: j10.suffixSymbolOptions,
                    allowClose: j10.allowClose,
                    closeOptions: j10.closeOptions,
                    chipEnabled: j10.enabled,
                    chipActivated: j10.activated,
                    chipNodeBackgroundColor: j10.backgroundColor,
                    chipNodeActivatedBackgroundColor: j10.activatedBackgroundColor,
                    chipNodeRadius: j10.borderRadius,
                    chipDirection: j10.direction,
                    chipAccessibilitySelectedType: j10.accessibilitySelectedType,
                    chipAccessibilityDescription: j10.accessibilityDescription,
                    chipAccessibilityLevel: j10.accessibilityLevel,
                    onClose: j10.onClose,
                    onClicked: j10.onClicked,
                }, undefined, h10, () => {
                }, { page: 'library/src/main/ets/components/chip.ets', line: 231, col: 3 });
                ViewPU.create(k10);
                let l10 = () => {
                    return {
                        chipSize: j10.size,
                        prefixIcon: j10.prefixIcon,
                        prefixSymbol: j10.prefixSymbol,
                        label: j10.label,
                        suffixIcon: j10.suffixIcon,
                        suffixSymbol: j10.suffixSymbol,
                        suffixSymbolOptions: j10.suffixSymbolOptions,
                        allowClose: j10.allowClose,
                        closeOptions: j10.closeOptions,
                        chipEnabled: j10.enabled,
                        chipActivated: j10.activated,
                        chipNodeBackgroundColor: j10.backgroundColor,
                        chipNodeActivatedBackgroundColor: j10.activatedBackgroundColor,
                        chipNodeRadius: j10.borderRadius,
                        chipDirection: j10.direction,
                        chipAccessibilitySelectedType: j10.accessibilitySelectedType,
                        chipAccessibilityDescription: j10.accessibilityDescription,
                        chipAccessibilityLevel: j10.accessibilityLevel,
                        onClose: j10.onClose,
                        onClicked: j10.onClicked
                    };
                };
                k10.paramsGenerator_ = l10;
            } else {
                (f10 ? f10 : this).updateStateVarsOfChildByElmtId(h10, {
                    chipSize: j10.size,
                    prefixIcon: j10.prefixIcon,
                    prefixSymbol: j10.prefixSymbol,
                    label: j10.label,
                    suffixIcon: j10.suffixIcon,
                    suffixSymbol: j10.suffixSymbol,
                    suffixSymbolOptions: j10.suffixSymbolOptions,
                    allowClose: j10.allowClose,
                    closeOptions: j10.closeOptions,
                    chipEnabled: j10.enabled,
                    chipActivated: j10.activated,
                    chipNodeBackgroundColor: j10.backgroundColor,
                    chipNodeActivatedBackgroundColor: j10.activatedBackgroundColor,
                    chipNodeRadius: j10.borderRadius,
                    chipDirection: j10.direction,
                    chipAccessibilitySelectedType: j10.accessibilitySelectedType,
                    chipAccessibilityDescription: j10.accessibilityDescription,
                    chipAccessibilityLevel: j10.accessibilityLevel
                });
            }
        }, { name: 'ChipComponent' });
    }
}

function isValidString(a10, b10) {
    const c10 = a10.match(b10);
    if (!c10 || c10.length < 3) {
        return false;
    }
    const d10 = Number.parseFloat(c10[1]);
    return d10 >= 0;
}

function isValidDimensionString(z9) {
    return isValidString(z9, new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i'));
}

function isValidResource(w9, x9) {
    const y9 = w9?.resourceManager;
    if (x9 === void (0) || x9 === null || y9 === void (0)) {
        return false;
    }
    if (x9.type !== RESOURCE_TYPE_STRING && x9.type !== RESOURCE_TYPE_INTEGER &&
        x9.type !== RESOURCE_TYPE_FLOAT) {
        return false;
    }
    if (x9.type === RESOURCE_TYPE_INTEGER || x9.type === RESOURCE_TYPE_FLOAT) {
        if (y9.getNumber(x9.id) >= 0) {
            return true;
        } else {
            return false;
        }
    }
    if (x9.type === RESOURCE_TYPE_STRING && !isValidDimensionString(y9.getStringSync(x9.id))) {
        return false;
    } else {
        return true;
    }
}

export class ChipComponent extends ViewPU {
    constructor(p9, q9, r9, s9 = -1, t9 = undefined, u9) {
        super(p9, r9, s9, u9);
        if (typeof t9 === 'function') {
            this.paramsGenerator_ = t9;
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
        this.__chipSize = new SynchedPropertyObjectOneWayPU(q9.chipSize, this, 'chipSize');
        this.__allowClose = new SynchedPropertySimpleOneWayPU(q9.allowClose, this, 'allowClose');
        this.__closeOptions = new SynchedPropertyObjectOneWayPU(q9.closeOptions, this, 'closeOptions');
        this.__chipDirection = new SynchedPropertySimpleOneWayPU(q9.chipDirection, this, 'chipDirection');
        this.__prefixIcon = new SynchedPropertyObjectOneWayPU(q9.prefixIcon, this, 'prefixIcon');
        this.__prefixSymbol = new SynchedPropertyObjectOneWayPU(q9.prefixSymbol, this, 'prefixSymbol');
        this.__label = new SynchedPropertyObjectOneWayPU(q9.label, this, 'label');
        this.__suffixIcon = new SynchedPropertyObjectOneWayPU(q9.suffixIcon, this, 'suffixIcon');
        this.__suffixSymbol = new SynchedPropertyObjectOneWayPU(q9.suffixSymbol, this, 'suffixSymbol');
        this.__suffixSymbolOptions =
            new SynchedPropertyObjectOneWayPU(q9.suffixSymbolOptions, this, 'suffixSymbolOptions');
        this.__chipNodeBackgroundColor =
            new SynchedPropertyObjectOneWayPU(q9.chipNodeBackgroundColor, this, 'chipNodeBackgroundColor');
        this.__chipNodeActivatedBackgroundColor =
            new SynchedPropertyObjectOneWayPU(q9.chipNodeActivatedBackgroundColor, this,
                'chipNodeActivatedBackgroundColor');
        this.__isHovering = new ObservedPropertySimplePU(false, this, 'isHovering');
        this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(q9.chipNodeRadius, this, 'chipNodeRadius');
        this.__chipEnabled = new SynchedPropertySimpleOneWayPU(q9.chipEnabled, this, 'chipEnabled');
        this.__chipActivated = new SynchedPropertySimpleOneWayPU(q9.chipActivated, this, 'chipActivated');
        this.__chipAccessibilitySelectedType =
            new SynchedPropertySimpleOneWayPU(q9.chipAccessibilitySelectedType, this, 'chipAccessibilitySelectedType');
        this.__chipAccessibilityDescription =
            new SynchedPropertyObjectOneWayPU(q9.chipAccessibilityDescription, this, 'chipAccessibilityDescription');
        this.__chipAccessibilityLevel =
            new SynchedPropertySimpleOneWayPU(q9.chipAccessibilityLevel, this, 'chipAccessibilityLevel');
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
            onConfigurationUpdated: (v9) => {
                this.fontSizeScale = v9.fontSizeScale;
                this.fontWeightScale = v9.fontWeightScale;
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
        this.setInitiallyProvidedValue(q9);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(o9) {
        if (o9.theme !== undefined) {
            this.theme = o9.theme;
        }
        if (o9.chipSize === undefined) {
            this.__chipSize.set(ChipSize.NORMAL);
        }
        if (o9.allowClose === undefined) {
            this.__allowClose.set(true);
        }
        if (o9.chipDirection === undefined) {
            this.__chipDirection.set(Direction.Auto);
        }
        if (o9.prefixIcon === undefined) {
            this.__prefixIcon.set({ src: '' });
        }
        if (o9.label === undefined) {
            this.__label.set({ text: '' });
        }
        if (o9.suffixIcon === undefined) {
            this.__suffixIcon.set({ src: '' });
        }
        if (o9.chipNodeBackgroundColor === undefined) {
            this.__chipNodeBackgroundColor.set(this.theme.chipNode.backgroundColor);
        }
        if (o9.chipNodeActivatedBackgroundColor === undefined) {
            this.__chipNodeActivatedBackgroundColor.set(this.theme.chipNode.activatedBackgroundColor);
        }
        if (o9.isHovering !== undefined) {
            this.isHovering = o9.isHovering;
        }
        if (o9.chipNodeRadius === undefined) {
            this.__chipNodeRadius.set(void (0));
        }
        if (o9.chipEnabled === undefined) {
            this.__chipEnabled.set(true);
        }
        if (o9.isHover !== undefined) {
            this.isHover = o9.isHover;
        }
        if (o9.chipScale !== undefined) {
            this.chipScale = o9.chipScale;
        }
        if (o9.chipOpacity !== undefined) {
            this.chipOpacity = o9.chipOpacity;
        }
        if (o9.chipBlendColor !== undefined) {
            this.chipBlendColor = o9.chipBlendColor;
        }
        if (o9.deleteChip !== undefined) {
            this.deleteChip = o9.deleteChip;
        }
        if (o9.chipNodeOnFocus !== undefined) {
            this.chipNodeOnFocus = o9.chipNodeOnFocus;
        }
        if (o9.useDefaultSuffixIcon !== undefined) {
            this.useDefaultSuffixIcon = o9.useDefaultSuffixIcon;
        }
        if (o9.chipNodeSize !== undefined) {
            this.chipNodeSize = o9.chipNodeSize;
        }
        if (o9.onClose !== undefined) {
            this.onClose = o9.onClose;
        }
        if (o9.onClicked !== undefined) {
            this.onClicked = o9.onClicked;
        }
        if (o9.suffixIconOnFocus !== undefined) {
            this.suffixIconOnFocus = o9.suffixIconOnFocus;
        }
        if (o9.chipBreakPoints !== undefined) {
            this.chipBreakPoints = o9.chipBreakPoints;
        }
        if (o9.smListener !== undefined) {
            this.smListener = o9.smListener;
        }
        if (o9.mdListener !== undefined) {
            this.mdListener = o9.mdListener;
        }
        if (o9.lgListener !== undefined) {
            this.lgListener = o9.lgListener;
        }
        if (o9.isSuffixIconFocusStyleCustomized !== undefined) {
            this.isSuffixIconFocusStyleCustomized = o9.isSuffixIconFocusStyleCustomized;
        }
        if (o9.isShowPressedBackGroundColor !== undefined) {
            this.isShowPressedBackGroundColor = o9.isShowPressedBackGroundColor;
        }
        if (o9.fontSizeScale !== undefined) {
            this.fontSizeScale = o9.fontSizeScale;
        }
        if (o9.fontWeightScale !== undefined) {
            this.fontWeightScale = o9.fontWeightScale;
        }
        if (o9.callbacks !== undefined) {
            this.callbacks = o9.callbacks;
        }
        if (o9.callbackId !== undefined) {
            this.callbackId = o9.callbackId;
        }
        if (o9.prefixSymbolWidth !== undefined) {
            this.prefixSymbolWidth = o9.prefixSymbolWidth;
        }
        if (o9.suffixSymbolWidth !== undefined) {
            this.suffixSymbolWidth = o9.suffixSymbolWidth;
        }
        if (o9.allowCloseSymbolWidth !== undefined) {
            this.allowCloseSymbolWidth = o9.allowCloseSymbolWidth;
        }
        if (o9.symbolEffect !== undefined) {
            this.symbolEffect = o9.symbolEffect;
        }
    }

    updateStateVars(n9) {
        this.__chipSize.reset(n9.chipSize);
        this.__allowClose.reset(n9.allowClose);
        this.__closeOptions.reset(n9.closeOptions);
        this.__chipDirection.reset(n9.chipDirection);
        this.__prefixIcon.reset(n9.prefixIcon);
        this.__prefixSymbol.reset(n9.prefixSymbol);
        this.__label.reset(n9.label);
        this.__suffixIcon.reset(n9.suffixIcon);
        this.__suffixSymbol.reset(n9.suffixSymbol);
        this.__suffixSymbolOptions.reset(n9.suffixSymbolOptions);
        this.__chipNodeBackgroundColor.reset(n9.chipNodeBackgroundColor);
        this.__chipNodeActivatedBackgroundColor.reset(n9.chipNodeActivatedBackgroundColor);
        this.__chipNodeRadius.reset(n9.chipNodeRadius);
        this.__chipEnabled.reset(n9.chipEnabled);
        this.__chipActivated.reset(n9.chipActivated);
        this.__chipAccessibilitySelectedType.reset(n9.chipAccessibilitySelectedType);
        this.__chipAccessibilityDescription.reset(n9.chipAccessibilityDescription);
        this.__chipAccessibilityLevel.reset(n9.chipAccessibilityLevel);
    }

    purgeVariableDependenciesOnElmtId(m9) {
        this.__chipSize.purgeDependencyOnElmtId(m9);
        this.__allowClose.purgeDependencyOnElmtId(m9);
        this.__closeOptions.purgeDependencyOnElmtId(m9);
        this.__chipDirection.purgeDependencyOnElmtId(m9);
        this.__prefixIcon.purgeDependencyOnElmtId(m9);
        this.__prefixSymbol.purgeDependencyOnElmtId(m9);
        this.__label.purgeDependencyOnElmtId(m9);
        this.__suffixIcon.purgeDependencyOnElmtId(m9);
        this.__suffixSymbol.purgeDependencyOnElmtId(m9);
        this.__suffixSymbolOptions.purgeDependencyOnElmtId(m9);
        this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(m9);
        this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(m9);
        this.__isHovering.purgeDependencyOnElmtId(m9);
        this.__chipNodeRadius.purgeDependencyOnElmtId(m9);
        this.__chipEnabled.purgeDependencyOnElmtId(m9);
        this.__chipActivated.purgeDependencyOnElmtId(m9);
        this.__chipAccessibilitySelectedType.purgeDependencyOnElmtId(m9);
        this.__chipAccessibilityDescription.purgeDependencyOnElmtId(m9);
        this.__chipAccessibilityLevel.purgeDependencyOnElmtId(m9);
        this.__isHover.purgeDependencyOnElmtId(m9);
        this.__chipScale.purgeDependencyOnElmtId(m9);
        this.__chipOpacity.purgeDependencyOnElmtId(m9);
        this.__chipBlendColor.purgeDependencyOnElmtId(m9);
        this.__deleteChip.purgeDependencyOnElmtId(m9);
        this.__chipNodeOnFocus.purgeDependencyOnElmtId(m9);
        this.__useDefaultSuffixIcon.purgeDependencyOnElmtId(m9);
        this.__suffixIconOnFocus.purgeDependencyOnElmtId(m9);
        this.__chipBreakPoints.purgeDependencyOnElmtId(m9);
        this.__isShowPressedBackGroundColor.purgeDependencyOnElmtId(m9);
        this.__fontSizeScale.purgeDependencyOnElmtId(m9);
        this.__fontWeightScale.purgeDependencyOnElmtId(m9);
        this.__prefixSymbolWidth.purgeDependencyOnElmtId(m9);
        this.__suffixSymbolWidth.purgeDependencyOnElmtId(m9);
        this.__allowCloseSymbolWidth.purgeDependencyOnElmtId(m9);
        this.__symbolEffect.purgeDependencyOnElmtId(m9);
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

    set chipSize(l9) {
        this.__chipSize.set(l9);
    }

    get allowClose() {
        return this.__allowClose.get();
    }

    set allowClose(k9) {
        this.__allowClose.set(k9);
    }

    get closeOptions() {
        return this.__closeOptions.get();
    }

    set closeOptions(j9) {
        this.__closeOptions.set(j9);
    }

    get chipDirection() {
        return this.__chipDirection.get();
    }

    set chipDirection(i9) {
        this.__chipDirection.set(i9);
    }

    get prefixIcon() {
        return this.__prefixIcon.get();
    }

    set prefixIcon(h9) {
        this.__prefixIcon.set(h9);
    }

    get prefixSymbol() {
        return this.__prefixSymbol.get();
    }

    set prefixSymbol(g9) {
        this.__prefixSymbol.set(g9);
    }

    get label() {
        return this.__label.get();
    }

    set label(f9) {
        this.__label.set(f9);
    }

    get suffixIcon() {
        return this.__suffixIcon.get();
    }

    set suffixIcon(e9) {
        this.__suffixIcon.set(e9);
    }

    get suffixSymbol() {
        return this.__suffixSymbol.get();
    }

    set suffixSymbol(d9) {
        this.__suffixSymbol.set(d9);
    }

    get suffixSymbolOptions() {
        return this.__suffixSymbolOptions.get();
    }

    set suffixSymbolOptions(c9) {
        this.__suffixSymbolOptions.set(c9);
    }

    get chipNodeBackgroundColor() {
        return this.__chipNodeBackgroundColor.get();
    }

    set chipNodeBackgroundColor(b9) {
        this.__chipNodeBackgroundColor.set(b9);
    }

    get chipNodeActivatedBackgroundColor() {
        return this.__chipNodeActivatedBackgroundColor.get();
    }

    set chipNodeActivatedBackgroundColor(a9) {
        this.__chipNodeActivatedBackgroundColor.set(a9);
    }

    get isHovering() {
        return this.__isHovering.get();
    }

    set isHovering(z8) {
        this.__isHovering.set(z8);
    }

    get chipNodeRadius() {
        return this.__chipNodeRadius.get();
    }

    set chipNodeRadius(y8) {
        this.__chipNodeRadius.set(y8);
    }

    get chipEnabled() {
        return this.__chipEnabled.get();
    }

    set chipEnabled(x8) {
        this.__chipEnabled.set(x8);
    }

    get chipActivated() {
        return this.__chipActivated.get();
    }

    set chipActivated(w8) {
        this.__chipActivated.set(w8);
    }

    get chipAccessibilitySelectedType() {
        return this.__chipAccessibilitySelectedType.get();
    }

    set chipAccessibilitySelectedType(v8) {
        this.__chipAccessibilitySelectedType.set(v8);
    }

    get chipAccessibilityDescription() {
        return this.__chipAccessibilityDescription.get();
    }

    set chipAccessibilityDescription(u8) {
        this.__chipAccessibilityDescription.set(u8);
    }

    get chipAccessibilityLevel() {
        return this.__chipAccessibilityLevel.get();
    }

    set chipAccessibilityLevel(t8) {
        this.__chipAccessibilityLevel.set(t8);
    }

    get isHover() {
        return this.__isHover.get();
    }

    set isHover(s8) {
        this.__isHover.set(s8);
    }

    get chipScale() {
        return this.__chipScale.get();
    }

    set chipScale(r8) {
        this.__chipScale.set(r8);
    }

    get chipOpacity() {
        return this.__chipOpacity.get();
    }

    set chipOpacity(q8) {
        this.__chipOpacity.set(q8);
    }

    get chipBlendColor() {
        return this.__chipBlendColor.get();
    }

    set chipBlendColor(p8) {
        this.__chipBlendColor.set(p8);
    }

    get deleteChip() {
        return this.__deleteChip.get();
    }

    set deleteChip(o8) {
        this.__deleteChip.set(o8);
    }

    get chipNodeOnFocus() {
        return this.__chipNodeOnFocus.get();
    }

    set chipNodeOnFocus(n8) {
        this.__chipNodeOnFocus.set(n8);
    }

    get useDefaultSuffixIcon() {
        return this.__useDefaultSuffixIcon.get();
    }

    set useDefaultSuffixIcon(m8) {
        this.__useDefaultSuffixIcon.set(m8);
    }

    get suffixIconOnFocus() {
        return this.__suffixIconOnFocus.get();
    }

    set suffixIconOnFocus(l8) {
        this.__suffixIconOnFocus.set(l8);
    }

    get chipBreakPoints() {
        return this.__chipBreakPoints.get();
    }

    set chipBreakPoints(k8) {
        this.__chipBreakPoints.set(k8);
    }

    get isShowPressedBackGroundColor() {
        return this.__isShowPressedBackGroundColor.get();
    }

    set isShowPressedBackGroundColor(j8) {
        this.__isShowPressedBackGroundColor.set(j8);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(i8) {
        this.__fontSizeScale.set(i8);
    }

    get fontWeightScale() {
        return this.__fontWeightScale.get();
    }

    set fontWeightScale(h8) {
        this.__fontWeightScale.set(h8);
    }

    get prefixSymbolWidth() {
        return this.__prefixSymbolWidth.get();
    }

    set prefixSymbolWidth(g8) {
        this.__prefixSymbolWidth.set(g8);
    }

    get suffixSymbolWidth() {
        return this.__suffixSymbolWidth.get();
    }

    set suffixSymbolWidth(f8) {
        this.__suffixSymbolWidth.set(f8);
    }

    get allowCloseSymbolWidth() {
        return this.__allowCloseSymbolWidth.get();
    }

    set allowCloseSymbolWidth(e8) {
        this.__allowCloseSymbolWidth.set(e8);
    }

    get symbolEffect() {
        return this.__symbolEffect.get();
    }

    set symbolEffect(d8) {
        this.__symbolEffect.set(d8);
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
                } catch (c8) {
                    return this.theme.label.defaultFontSize;
                }
            } else {
                try {
                    resourceManager.getSystemResourceManager()
                        .getNumberByName((this.theme.label.normalFontSize.params[0]).split('.')[2]);
                    return this.theme.label.normalFontSize;
                } catch (b8) {
                    return this.theme.label.defaultFontSize;
                }
            }
        }
    }

    defaultSymbolFontsize() {
        return this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ? this.theme.defaultSymbol.smallSymbolFontSize :
        this.theme.defaultSymbol.normalSymbolFontSize;
    }

    resourceToVp(z7) {
        let a8 = LengthMetrics.resource(z7);
        return this.lengthMetricsToVp(a8);
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

    lengthMetricsToVp(x7) {
        let y7 = 0;
        if (x7) {
            switch (x7.unit) {
                case LengthUnit.PX:
                    return px2vp(x7.value);
                case LengthUnit.VP:
                    return x7.value;
                case LengthUnit.FP:
                    return px2vp(fp2px(x7.value));
                case LengthUnit.PERCENT:
                    return Number.NEGATIVE_INFINITY;
                case LengthUnit.LPX:
                    return px2vp(lpx2px(x7.value));
            }
        }
        return y7;
    }

    toVp(q7) {
        if (q7 === void (0)) {
            return Number.NEGATIVE_INFINITY;
        }
        switch (typeof (q7)) {
            case 'number':
                return q7;
            case 'object':
                try {
                    let w7 = this.lengthMetricsToVp(LengthMetrics.resource(q7));
                    if (w7 === 0 &&
                        !isValidResource(getContext(this), q7)) {
                        return Number.NEGATIVE_INFINITY;
                    }
                    return w7;
                } catch (v7) {
                    return Number.NEGATIVE_INFINITY;
                }
            case 'string':
                let r7 = new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i');
                let s7 = q7.match(r7);
                if (!s7) {
                    return Number.NEGATIVE_INFINITY;
                }
                let t7 = Number(s7?.[1] ?? 0);
                let u7 = s7?.[2] ?? 'vp';
                switch (u7.toLowerCase()) {
                    case 'px':
                        t7 = px2vp(t7);
                        break;
                    case 'fp':
                        t7 = px2vp(fp2px(t7));
                        break;
                    case 'lpx':
                        t7 = px2vp(lpx2px(t7));
                        break;
                    case '%':
                        t7 = Number.NEGATIVE_INFINITY;
                        break;
                    case 'vp':
                        break;
                    default:
                        break;
                }
                return t7;
            default:
                return Number.NEGATIVE_INFINITY;
        }
    }

    getChipNodeBorderWidth() {
        return this.resourceToVp(this.theme.chipNode.defaultBorderWidth);
    }

    getChipNodeBorderColor() {
        let p7 = this.theme.chipNode;
        return this.getChipActive() ? p7.activatedBorderColor : p7.borderColor;
    }

    getLabelMargin() {
        let o7 = { left: 0, right: 0 };
        if (this.label?.labelMargin?.left !== void (0) && this.toVp(this.label.labelMargin.left) >= 0) {
            o7.left = this.label?.labelMargin?.left;
        } else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                o7.left = this.theme.label.smallMargin.left;
            } else {
                o7.left = this.theme.label.normalMargin.left;
            }
        }
        if (this.label?.labelMargin?.right !== void (0) && this.toVp(this.label.labelMargin.right) >= 0) {
            o7.right = this.label?.labelMargin?.right;
        } else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
            this.suffixIcon?.src || this.useDefaultSuffixIcon) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                o7.right = this.theme.label.smallMargin.right;
            } else {
                o7.right = this.theme.label.normalMargin.right;
            }
        }
        return o7;
    }

    getLocalizedLabelMargin() {
        let n7 = { start: LengthMetrics.vp(0), end: LengthMetrics.vp(0) };
        if (this.label?.localizedLabelMargin?.start?.value !== void (0) &&
            this.lengthMetricsToVp(this.label.localizedLabelMargin.start) >= 0) {
            n7.start = this.label?.localizedLabelMargin?.start;
        } else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                n7.start = this.theme.label.localizedSmallMargin.start;
            } else {
                n7.start = this.theme.label.localizedNormalMargin.start;
            }
        }
        if (this.label?.localizedLabelMargin?.end?.value !== void (0) &&
            this.lengthMetricsToVp(this.label.localizedLabelMargin.end) >= 0) {
            n7.end = this.label?.localizedLabelMargin?.end;
        } else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
            this.suffixIcon?.src || this.useDefaultSuffixIcon || this.isShowCloseIconMargin()) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                n7.end = this.theme.label.localizedSmallMargin.end;
            } else {
                n7.end = this.theme.label.localizedNormalMargin.end;
            }
        }
        return n7;
    }

    getLabelStartEndVp() {
        let l7 = this.getLocalizedLabelMargin();
        if (this.label && (this.label.labelMargin !== void (0)) && (this.label.localizedLabelMargin === void (0))) {
            let m7 = this.getLabelMargin();
            return {
                start: LengthMetrics.vp(this.toVp(m7.left)),
                end: LengthMetrics.vp(this.toVp(m7.right))
            };
        }
        return {
            start: LengthMetrics.vp(this.lengthMetricsToVp(l7.start)),
            end: LengthMetrics.vp(this.lengthMetricsToVp(l7.end))
        };
    }

    getActualLabelMargin() {
        let k7 = this.getLocalizedLabelMargin();
        if (this.label && this.label.localizedLabelMargin !== void (0)) {
            return k7;
        }
        if (this.label && this.label.labelMargin !== void (0)) {
            return this.getLabelMargin();
        }
        return k7;
    }

    getSuffixIconSize() {
        let j7 = { width: 0, height: 0 };
        if (this.suffixIcon?.size?.width !== void (0) && this.toVp(this.suffixIcon?.size?.width) >= 0) {
            j7.width = this.suffixIcon?.size?.width;
        } else {
            if (this.getSuffixIconSrc()) {
                j7.width = this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ?
                this.theme.suffixIcon.smallSize.width : this.theme.suffixIcon.normalSize.width;
            } else {
                j7.width = 0;
            }
        }
        if (this.suffixIcon?.size?.height !== void (0) && this.toVp(this.suffixIcon?.size?.height) >= 0) {
            j7.height = this.suffixIcon?.size?.height;
        } else {
            if (this.getSuffixIconSrc()) {
                j7.height = this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ?
                this.theme.suffixIcon.smallSize.height : this.theme.suffixIcon.normalSize.height;
            } else {
                j7.height = 0;
            }
        }
        return j7;
    }

    getPrefixIconSize() {
        let i7 = { width: 0, height: 0 };
        if (this.prefixIcon?.size?.width !== void (0) && this.toVp(this.prefixIcon?.size?.width) >= 0) {
            i7.width = this.prefixIcon?.size?.width;
        } else {
            if (this.prefixIcon?.src) {
                i7.width =
                    this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ? this.theme.prefixIcon.smallSize.width :
                    this.theme.prefixIcon.normalSize.width;
            } else {
                i7.width = 0;
            }
        }
        if (this.prefixIcon?.size?.height !== void (0) && this.toVp(this.prefixIcon?.size?.height) >= 0) {
            i7.height = this.prefixIcon?.size?.height;
        } else {
            if (this.prefixIcon?.src) {
                i7.height =
                    this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ? this.theme.prefixIcon.smallSize.height :
                    this.theme.prefixIcon.normalSize.height;
            } else {
                i7.height = 0;
            }
        }
        return i7;
    }

    getDefaultActiveIconColor(h7) {
        if (h7 === IconType.PREFIX_ICON) {
            return this.chipNodeOnFocus ? this.theme.prefixIcon.focusActivatedColor :
            this.theme.prefixIcon.activatedFillColor;
        } else {
            return this.chipNodeOnFocus ? this.theme.suffixIcon.focusActivatedColor :
            this.theme.suffixIcon.activatedFillColor;
        }
    }

    getDefaultFillIconColor(g7) {
        if (g7 === IconType.PREFIX_ICON) {
            return this.chipNodeOnFocus ? this.theme.prefixIcon.focusFillColor : this.theme.prefixIcon.fillColor;
        } else {
            return this.chipNodeOnFocus ? this.theme.suffixIcon.focusFillColor : this.theme.suffixIcon.fillColor;
        }
    }

    getSymbolActiveColor(f7) {
        if (f7 === IconType.PREFIX_SYMBOL) {
            return this.getColorArray(this.prefixIcon?.activatedFillColor, this.theme.prefixIcon.focusActivatedColor,
                this.theme.prefixIcon.activatedFillColor);
        } else if (f7 === IconType.SUFFIX_SYMBOL) {
            return this.getColorArray(this.suffixIcon?.activatedFillColor, this.theme.suffixIcon.focusActivatedColor,
                this.theme.suffixIcon.activatedFillColor);
        } else {
            return this.theme.defaultSymbol.activatedFontColor;
        }
    }

    getSymbolFillColor(e7) {
        if (e7 === IconType.PREFIX_SYMBOL) {
            return this.getColorArray(this.prefixIcon?.fillColor, this.theme.prefixIcon.focusFillColor,
                this.theme.prefixIcon.fillColor);
        } else if (e7 === IconType.SUFFIX_SYMBOL) {
            return this.getColorArray(this.suffixIcon?.fillColor, this.theme.suffixIcon.focusFillColor,
                this.theme.suffixIcon.fillColor);
        } else {
            return this.theme.defaultSymbol.normalFontColor;
        }
    }

    getColorArray(b7, c7, d7) {
        if (b7) {
            return [b7];
        }
        return this.chipNodeOnFocus ? [c7] : [d7];
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

    getDefaultSymbolColor(a7) {
        if (this.getChipActive()) {
            return this.getSymbolActiveColor(a7);
        }
        return this.getSymbolFillColor(a7);
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
        let w6;
        let x6 = this.theme.chipNode;
        if (this.getChipActive()) {
            w6 = this.chipNodeOnFocus && !this.isSetActiveChipBgColor() ? x6.focusActivatedBgColor :
                this.chipNodeActivatedBackgroundColor ?? this.theme.chipNode.activatedBackgroundColor;
        } else {
            w6 = this.chipNodeOnFocus && !this.isSetNormalChipBgColor() ? x6.focusBgColor :
                this.chipNodeBackgroundColor ?? this.theme.chipNode.backgroundColor;
        }
        let y6;
        try {
            y6 = ColorMetrics.resourceColor(w6);
        } catch (z6) {
            hilog.error(0x3900, 'Ace', `Chip resourceColor, error: ${z6.toString()}`);
            y6 = ColorMetrics.resourceColor(Color.Transparent);
        }
        if (!this.isShowPressedBackGroundColor) {
            return y6.color;
        }
        return y6.blendColor(ColorMetrics.resourceColor('#19000000'))
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
        let u6 = 0;
        let v6 = this.getLabelStartEndVp();
        u6 += this.getChipNodeBorderWidth() * 2;
        u6 += this.getChipNodePadding().start?.value ?? 0;
        u6 += this.toVp(this.getPrefixChipWidth());
        u6 += this.toVp(v6.start?.value ?? 0);
        u6 += this.getLabelWidth();
        u6 += this.toVp(v6.end?.value ?? 0);
        u6 += this.toVp(this.getSuffixChipWidth());
        u6 += this.getChipNodePadding().end?.value ?? 0;
        return u6;
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

    handleTouch(t6) {
        if (!this.getChipEnable()) {
            return;
        }
        if (this.isHover) {
            if (t6.type === TouchType.Down || t6.type === TouchType.Move) {
                this.isShowPressedBackGroundColor = true;
            } else if (t6.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            } else {
                this.isShowPressedBackGroundColor = false;
            }
        } else {
            if (t6.type === TouchType.Down || t6.type === TouchType.Move) {
                this.isShowPressedBackGroundColor = true;
            } else if (t6.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            } else {
                this.isShowPressedBackGroundColor = false;
            }
        }
    }

    hoverAnimate(s6) {
        if (!this.getChipEnable()) {
            return;
        }
        this.isHover = s6;
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
        let r6 = this.getChipConstraintWidth();
        return Math.min(Math.max(this.getCalculateChipNodeWidth(), r6.minWidth), r6.maxWidth);
    }

    getFocusOverlaySize() {
        return {
            width: Math.max(this.getChipNodeWidth(), this.getChipConstraintWidth().minWidth) + 8,
            height: this.getChipNodeHeight() + 8
        };
    }

    getChipConstraintWidth() {
        let o6 = this.getReserveChipNodeWidth();
        let p6 = this.getCalculateChipNodeWidth();
        let q6;
        switch (this.chipBreakPoints) {
            case BreakPointsType.SM:
                q6 = {
                    minWidth: o6,
                    maxWidth: Math.min(p6, this.theme.chipNode.breakPointConstraintWidth.breakPointSmMaxWidth)
                };
                break;
            case BreakPointsType.MD:
                q6 = {
                    minWidth: Math.max(p6, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(p6, this.theme.chipNode.breakPointConstraintWidth.breakPointMdMaxWidth)
                };
                break;
            case BreakPointsType.LG:
                q6 = {
                    minWidth: Math.max(p6, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(p6, this.theme.chipNode.breakPointConstraintWidth.breakPointLgMaxWidth)
                };
                break;
            default:
                q6 = { minWidth: o6, maxWidth: p6 };
                break;
        }
        q6.minWidth = Math.min(Math.max(this.getCalculateChipNodeWidth(), q6.minWidth), q6.maxWidth);
        q6.minHeight = this.getChipNodeHeight();
        if (!this.isChipSizeEnum() && this.chipNodeSize?.height !== void (0) &&
            this.toVp(this.chipNodeSize?.height) >= 0) {
            q6.maxHeight = this.toVp(this.chipNodeSize.height);
            q6.minHeight = this.toVp(this.chipNodeSize.height);
        }
        if (!this.isChipSizeEnum() && this.chipNodeSize?.width !== void (0) &&
            this.toVp(this.chipNodeSize?.width) >= 0) {
            q6.minWidth = this.toVp(this.chipNodeSize.width);
            q6.maxWidth = this.toVp(this.chipNodeSize.width);
        } else if (this.toVp(this.fontSizeScale) >= this.theme.chipNode.suitAgeScale) {
            q6.minWidth = void (0);
            q6.maxWidth = void (0);
        }
        return q6;
    }

    focusOverlay(h6 = null) {
        this.observeComponentCreation2((m6, n6) => {
            Stack.create();
            Stack.direction(this.chipDirection);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((i6, j6) => {
            If.create();
            if (this.chipNodeOnFocus && !this.suffixIconOnFocus) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k6, l6) => {
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
        let d6 = this.getUIContext();
        this.fontSizeScale = d6.getHostContext()?.config?.fontSizeScale ?? 1;
        this.smListener.on('change', (g6) => {
            if (g6.matches) {
                this.chipBreakPoints = BreakPointsType.SM;
            }
        });
        this.mdListener.on('change', (f6) => {
            if (f6.matches) {
                this.chipBreakPoints = BreakPointsType.MD;
            }
        });
        this.lgListener.on('change', (e6) => {
            if (e6.matches) {
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
        } catch (c6) {
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
        } catch (b6) {
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

    chipBuilder(p4 = null) {
        this.observeComponentCreation2((u5, v5) => {
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
            Button.onTouch((a6) => {
                this.handleTouch(a6);
            });
            Button.onHover((z5) => {
                if (z5) {
                    this.isShowPressedBackGroundColor = true;
                } else {
                    if (!this.isShowPressedBackGroundColor && z5) {
                        this.isShowPressedBackGroundColor = true;
                    } else {
                        this.isShowPressedBackGroundColor = false;
                    }
                }
            });
            Button.onKeyEvent((w5) => {
                if (!w5 || w5.type === null || w5.type !== KeyType.Down) {
                    return;
                }
                let x5 = w5.keyCode === KeyCode.KEYCODE_FORWARD_DEL &&
                    !this.suffixIconOnFocus;
                let y5 = w5.keyCode === KeyCode.KEYCODE_ENTER && this.allowClose !== false &&
                    !this.suffixIcon?.src && this.isSuffixIconFocusStyleCustomized;
                if (x5 || y5) {
                    this.deleteChipNodeAnimate();
                }
            });
            Button.onClick(this.onClicked === noop ? undefined : this.onClicked.bind(this));
        }, Button);
        this.observeComponentCreation2((s5, t5) => {
            Row.create();
            Row.direction(this.chipDirection);
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.Center);
            Row.padding(this.getChipNodePadding());
            Row.constraintSize(this.getChipConstraintWidth());
        }, Row);
        this.observeComponentCreation2((k5, l5) => {
            If.create();
            if (this.prefixSymbol?.normal || this.prefixSymbol?.activated) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o5, p5) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.defaultSymbolFontsize());
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.PREFIX_SYMBOL));
                        SymbolGlyph.attributeModifier.bind(this)(this.getPrefixSymbolModifier());
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect),
                            this.theme.defaultSymbol.defaultEffect);
                        SymbolGlyph.onSizeChange((q5, r5) => {
                            this.prefixSymbolWidth = r5?.width;
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
        this.observeComponentCreation2((i5, j5) => {
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
        this.observeComponentCreation2((q4, r4) => {
            If.create();
            if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g5, h5) => {
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
                    this.observeComponentCreation2((c5, d5) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.defaultSymbolFontsize());
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_SYMBOL));
                        SymbolGlyph.attributeModifier.bind(this)(this.getSuffixSymbolModifier());
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect),
                            this.theme.defaultSymbol.defaultEffect);
                        SymbolGlyph.onSizeChange((e5, f5) => {
                            this.suffixSymbolWidth = f5?.width;
                        });
                        SymbolGlyph.key('SuffixSymbolGlyph');
                    }, SymbolGlyph);
                    Button.pop();
                });
            } else if (this.suffixIcon?.src !== '') {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((a5, b5) => {
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
                    this.observeComponentCreation2((y4, z4) => {
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
                    this.observeComponentCreation2((w4, x4) => {
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
                    this.observeComponentCreation2((s4, t4) => {
                        SymbolGlyph.create({
                            'id': -1,
                            'type': 40000,
                            params: ['sys.symbol.xmark'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.fontSize(this.defaultSymbolFontsize());
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_SYMBOL));
                        SymbolGlyph.onSizeChange((u4, v4) => {
                            this.allowCloseSymbolWidth = v4?.width;
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

    resourceToNumber(l4, m4) {
        if (!l4 || !l4.type) {
            console.error('[Chip] failed: resource get fail.');
            return m4;
        }
        const n4 = this.getUIContext().getHostContext()?.resourceManager;
        if (!n4) {
            console.error('[Chip] failed to get resourceManager.');
            return m4;
        }
        switch (l4.type) {
            case RESOURCE_TYPE_FLOAT:
            case RESOURCE_TYPE_INTEGER:
                try {
                    if (l4.id !== -1) {
                        return n4.getNumber(l4);
                    }
                    return n4.getNumberByName(l4.params[0].split('.')[2]);
                } catch (o4) {
                    console.error(`[Chip] get resource error, return defaultValue`);
                    return m4;
                }
            default:
                return m4;
        }
    }

    initialRender() {
        this.observeComponentCreation2((j4, k4) => {
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