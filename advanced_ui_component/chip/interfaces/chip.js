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
(function (g6) {
    g6["NORMAL"] = "NORMAL";
    g6["SMALL"] = "SMALL";
})(ChipSize || (ChipSize = {}));
var IconType;
(function (f6) {
    f6["PREFIX_ICON"] = "PREFIXICON";
    f6["SUFFIX_ICON"] = "SUFFIXICON";
})(IconType || (IconType = {}));
var BreakPointsType;
(function (e6) {
    e6["SM"] = "SM";
    e6["MD"] = "MD";
    e6["LG"] = "LG";
})(BreakPointsType || (BreakPointsType = {}));

export var AccessibilitySelectedType;
(function (d6) {
    d6[d6["CLICKED"] = 0] = "CLICKED";
    d6[d6["CHECKED"] = 1] = "CHECKED";
    d6[d6["SELECTED"] = 2] = "SELECTED";
})(AccessibilitySelectedType || (AccessibilitySelectedType = {}));

export const defaultTheme = {
    prefixIcon: {
        normalSize: {
            width: {
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_normal_icon_size'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            },
            height: {
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_normal_icon_size'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }
        },
        smallSize: {
            width: {
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_small_icon_size'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            },
            height: {
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_small_icon_size'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }
        },
        fillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_usually_icon_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        activatedFillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_active_icon_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        focusFillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_icon_focus_fill'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        focusActivatedColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_icon_activated_focus_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
    },
    label: {
        normalFontSize: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_normal_font_size'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        smallFontSize: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_small_font_size'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        focusFontColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_focus_text'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        focusActiveFontColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_activated_focus_font_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        fontColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_font_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        activatedFontColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_activated_fontcolor'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        fontFamily: "HarmonyOS Sans",
        fontWeight: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_text_font_weight'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
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
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_normal_text_margin'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }),
            end: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_normal_text_margin'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }),
            top: LengthMetrics.vp(0),
            bottom: LengthMetrics.vp(0)
        },
        localizedSmallMargin: {
            start: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_small_text_margin'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }),
            end: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_small_text_margin'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }),
            top: LengthMetrics.vp(0),
            bottom: LengthMetrics.vp(0),
        }
    },
    suffixIcon: {
        normalSize: {
            width: {
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_normal_icon_size'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            },
            height: {
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_normal_icon_size'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }
        },
        smallSize: {
            width: {
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_small_icon_size'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            },
            height: {
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_small_icon_size'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }
        },
        fillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_usually_icon_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        activatedFillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_active_icon_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        focusFillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_icon_focus_fill'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        focusActivatedColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_icon_activated_focus_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        defaultDeleteIcon: {
            "id": -1,
            "type": 20000,
            params: ['sys.media.ohos_ic_public_cancel', 16, 16],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        focusable: false,
    },
    defaultSymbol: {
        normalFontColor: [{
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_secondary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }],
        activatedFontColor: [{
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_primary_contrary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }],
        normalFontSize: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_normal_icon_size'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        smallFontSize: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_small_icon_size'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        defaultEffect: -1,
        isShowMargin: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_show_close_icon_margin'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
    },
    chipNode: {
        suitAgeScale: 1.75,
        minLabelWidth: 12,
        normalHeight: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_normal_height'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        smallHeight: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_small_height'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        enabled: true,
        activated: false,
        backgroundColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_background_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        activatedBackgroundColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_container_activated_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        focusOutlineColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_focused_outline'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        focusOutlineMargin: 2,
        borderColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_border_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        defaultBorderWidth: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_border_width'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        activatedBorderColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_activated_border_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        normalBorderRadius: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_normal_radius'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        smallBorderRadius: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_small_radius'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        borderWidth: 2,
        focusBtnScaleX: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_focused_btn_scale'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        focusBtnScaleY: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_focused_btn_scale'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        localizedNormalPadding: {
            start: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_normal_text_padding'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }),
            end: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_normal_text_padding'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }),
            top: LengthMetrics.vp(4),
            bottom: LengthMetrics.vp(4)
        },
        localizedSmallPadding: {
            start: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_small_text_padding'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }),
            end: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.chip_small_text_padding'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }),
            top: LengthMetrics.vp(4),
            bottom: LengthMetrics.vp(4)
        },
        hoverBlendColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_hover_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        pressedBlendColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_press_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        focusBgColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_focus_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        focusActivatedBgColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.chip_container_activated_focus_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        opacity: { normal: 1, hover: 0.95, pressed: 0.9 },
        normalShadowStyle: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_normal_shadow_style'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        smallShadowStyle: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.chip_small_shadow_style'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
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

export function Chip(v5, w5 = null) {
    const x5 = v5;
    {
        (w5 ? w5 : this).observeComponentCreation2((y5, z5, a6 = x5) => {
            if (z5) {
                let b6 = new ChipComponent(w5 ? w5 : this, {
                    chipSize: a6.size,
                    prefixIcon: a6.prefixIcon,
                    prefixSymbol: a6.prefixSymbol,
                    label: a6.label,
                    suffixIcon: a6.suffixIcon,
                    suffixSymbol: a6.suffixSymbol,
                    suffixSymbolOptions: a6.suffixSymbolOptions,
                    allowClose: a6.allowClose,
                    closeOptions: a6.closeOptions,
                    chipEnabled: a6.enabled,
                    chipActivated: a6.activated,
                    chipNodeBackgroundColor: a6.backgroundColor,
                    chipNodeActivatedBackgroundColor: a6.activatedBackgroundColor,
                    chipNodeRadius: a6.borderRadius,
                    chipDirection: a6.direction,
                    chipAccessibilitySelectedType: a6.accessibilitySelectedType,
                    chipAccessibilityDescription: a6.accessibilityDescription,
                    chipAccessibilityLevel: a6.accessibilityLevel,
                    onClose: a6.onClose,
                    onClicked: a6.onClicked,
                }, undefined, y5, () => {
                }, { page: "library/src/main/ets/components/chip.ets", line: 350, col: 3 });
                ViewPU.create(b6);
                let j6 = () => {
                    return {
                        chipSize: a6.size,
                        prefixIcon: a6.prefixIcon,
                        prefixSymbol: a6.prefixSymbol,
                        label: a6.label,
                        suffixIcon: a6.suffixIcon,
                        suffixSymbol: a6.suffixSymbol,
                        suffixSymbolOptions: a6.suffixSymbolOptions,
                        allowClose: a6.allowClose,
                        closeOptions: a6.closeOptions,
                        chipEnabled: a6.enabled,
                        chipActivated: a6.activated,
                        chipNodeBackgroundColor: a6.backgroundColor,
                        chipNodeActivatedBackgroundColor: a6.activatedBackgroundColor,
                        chipNodeRadius: a6.borderRadius,
                        chipDirection: a6.direction,
                        chipAccessibilitySelectedType: a6.accessibilitySelectedType,
                        chipAccessibilityDescription: a6.accessibilityDescription,
                        chipAccessibilityLevel: a6.accessibilityLevel,
                        onClose: a6.onClose,
                        onClicked: a6.onClicked
                    };
                };
                b6.paramsGenerator_ = j6;
            } else {
                (w5 ? w5 : this).updateStateVarsOfChildByElmtId(y5, {
                    chipSize: a6.size,
                    prefixIcon: a6.prefixIcon,
                    prefixSymbol: a6.prefixSymbol,
                    label: a6.label,
                    suffixIcon: a6.suffixIcon,
                    suffixSymbol: a6.suffixSymbol,
                    suffixSymbolOptions: a6.suffixSymbolOptions,
                    allowClose: a6.allowClose,
                    closeOptions: a6.closeOptions,
                    chipEnabled: a6.enabled,
                    chipActivated: a6.activated,
                    chipNodeBackgroundColor: a6.backgroundColor,
                    chipNodeActivatedBackgroundColor: a6.activatedBackgroundColor,
                    chipNodeRadius: a6.borderRadius,
                    chipDirection: a6.direction,
                    chipAccessibilitySelectedType: a6.accessibilitySelectedType,
                    chipAccessibilityDescription: a6.accessibilityDescription,
                    chipAccessibilityLevel: a6.accessibilityLevel
                });
            }
        }, { name: "ChipComponent" });
    }
}

function isValidString(r5, s5) {
    const t5 = r5.match(s5);
    if (!t5 || t5.length < 3) {
        return false;
    }
    const u5 = Number.parseFloat(t5[1]);
    return u5 >= 0;
}

function isValidDimensionString(q5) {
    return isValidString(q5, new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i'));
}

function isValidResource(n5, o5) {
    const p5 = n5?.resourceManager;
    if (o5 === void (0) || o5 === null || p5 === void (0)) {
        return false;
    }
    if (o5.type !== RESOURCE_TYPE_STRING && o5.type !== RESOURCE_TYPE_INTEGER &&
        o5.type !== RESOURCE_TYPE_FLOAT) {
        return false;
    }
    if (o5.type === RESOURCE_TYPE_INTEGER || o5.type === RESOURCE_TYPE_FLOAT) {
        if (p5.getNumber(o5.id) >= 0) {
            return true;
        } else {
            return false;
        }
    }
    if (o5.type === RESOURCE_TYPE_STRING && !isValidDimensionString(p5.getStringSync(o5.id))) {
        return false;
    } else {
        return true;
    }
}

export class ChipComponent extends ViewPU {
    constructor(g5, h5, i5, j5 = -1, k5 = undefined, l5) {
        super(g5, i5, j5, l5);
        if (typeof k5 === "function") {
            this.paramsGenerator_ = k5;
        }
        this.theme = defaultTheme;
        this.__chipSize = new SynchedPropertyObjectOneWayPU(h5.chipSize, this, "chipSize");
        this.__allowClose = new SynchedPropertySimpleOneWayPU(h5.allowClose, this, "allowClose");
        this.__closeOptions = new SynchedPropertyObjectOneWayPU(h5.closeOptions, this, "closeOptions");
        this.__chipDirection = new SynchedPropertySimpleOneWayPU(h5.chipDirection, this, "chipDirection");
        this.__prefixIcon = new SynchedPropertyObjectOneWayPU(h5.prefixIcon, this, "prefixIcon");
        this.__prefixSymbol = new SynchedPropertyObjectOneWayPU(h5.prefixSymbol, this, "prefixSymbol");
        this.__label = new SynchedPropertyObjectOneWayPU(h5.label, this, "label");
        this.__suffixIcon = new SynchedPropertyObjectOneWayPU(h5.suffixIcon, this, "suffixIcon");
        this.__suffixSymbol = new SynchedPropertyObjectOneWayPU(h5.suffixSymbol, this, "suffixSymbol");
        this.__suffixSymbolOptions =
            new SynchedPropertyObjectOneWayPU(h5.suffixSymbolOptions, this, "suffixSymbolOptions");
        this.__chipNodeBackgroundColor =
            new SynchedPropertyObjectOneWayPU(h5.chipNodeBackgroundColor, this, "chipNodeBackgroundColor");
        this.__isSetBg = new ObservedPropertySimplePU(false, this, "isSetBg");
        this.__chipNodeActivatedBackgroundColor =
            new SynchedPropertyObjectOneWayPU(h5.chipNodeActivatedBackgroundColor, this,
                "chipNodeActivatedBackgroundColor");
        this.__isSetActiveBg = new ObservedPropertySimplePU(false, this, "isSetActiveBg");
        this.__isHovering = new ObservedPropertySimplePU(false, this, "isHovering");
        this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(h5.chipNodeRadius, this, "chipNodeRadius");
        this.__chipEnabled = new SynchedPropertySimpleOneWayPU(h5.chipEnabled, this, "chipEnabled");
        this.__chipActivated = new SynchedPropertySimpleOneWayPU(h5.chipActivated, this, "chipActivated");
        this.__chipAccessibilitySelectedType =
            new SynchedPropertySimpleOneWayPU(h5.chipAccessibilitySelectedType, this, "chipAccessibilitySelectedType");
        this.__chipAccessibilityDescription =
            new SynchedPropertyObjectOneWayPU(h5.chipAccessibilityDescription, this, "chipAccessibilityDescription");
        this.__chipAccessibilityLevel =
            new SynchedPropertySimpleOneWayPU(h5.chipAccessibilityLevel, this, "chipAccessibilityLevel");
        this.__isHover = new ObservedPropertySimplePU(false, this, "isHover");
        this.__chipScale = new ObservedPropertyObjectPU({ x: 1, y: 1 }, this, "chipScale");
        this.__chipOpacity = new ObservedPropertySimplePU(1, this, "chipOpacity");
        this.__chipBlendColor = new ObservedPropertyObjectPU(Color.Transparent, this, "chipBlendColor");
        this.__deleteChip = new ObservedPropertySimplePU(false, this, "deleteChip");
        this.__chipNodeOnFocus = new ObservedPropertySimplePU(false, this, "chipNodeOnFocus");
        this.__useDefaultSuffixIcon = new ObservedPropertySimplePU(false, this, "useDefaultSuffixIcon");
        this.chipNodeSize = {};
        this.onClose = noop;
        this.onClicked = noop;
        this.__suffixIconOnFocus = new ObservedPropertySimplePU(false, this, "suffixIconOnFocus");
        this.__chipBreakPoints = new ObservedPropertySimplePU(BreakPointsType.SM, this, "chipBreakPoints");
        this.smListener = mediaquery.matchMediaSync('(0vp<width) and (width<600vp)');
        this.mdListener = mediaquery.matchMediaSync('(600vp<=width) and (width<840vp)');
        this.lgListener = mediaquery.matchMediaSync('(840vp<=width)');
        this.__isShowPressedBackGroundColor = new ObservedPropertySimplePU(false, this, "isShowPressedBackGroundColor");
        this.__fontSizeScale = new ObservedPropertyObjectPU(0, this, "fontSizeScale");
        this.__fontWeightScale = new ObservedPropertyObjectPU(0, this, "fontWeightScale");
        this.callbacks = {
            onConfigurationUpdated: (m5) => {
                this.fontSizeScale = m5.fontSizeScale;
                this.fontWeightScale = m5.fontWeightScale;
            },
            onMemoryLevel() {
            }
        };
        this.callbackId = undefined;
        this.__prefixSymbolWidth =
            new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById('PrefixSymbolGlyph')?.size?.width),
                this, "prefixSymbolWidth");
        this.__suffixSymbolWidth =
            new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById('SuffixSymbolGlyph')?.size?.width),
                this, "suffixSymbolWidth");
        this.__allowCloseSymbolWidth =
            new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById('AllowCloseSymbolGlyph')?.size?.width),
                this, "allowCloseSymbolWidth");
        this.__symbolEffect = new ObservedPropertyObjectPU(new SymbolEffect(), this, "symbolEffect");
        this.setInitiallyProvidedValue(h5);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(f5) {
        if (f5.theme !== undefined) {
            this.theme = f5.theme;
        }
        if (f5.chipSize === undefined) {
            this.__chipSize.set(ChipSize.NORMAL);
        }
        if (f5.allowClose === undefined) {
            this.__allowClose.set(true);
        }
        if (f5.chipDirection === undefined) {
            this.__chipDirection.set(Direction.Auto);
        }
        if (f5.prefixIcon === undefined) {
            this.__prefixIcon.set({ src: "" });
        }
        if (f5.label === undefined) {
            this.__label.set({ text: "" });
        }
        if (f5.suffixIcon === undefined) {
            this.__suffixIcon.set({ src: "" });
        }
        if (f5.isSetBg !== undefined) {
            this.isSetBg = f5.isSetBg;
        }
        if (f5.isSetActiveBg !== undefined) {
            this.isSetActiveBg = f5.isSetActiveBg;
        }
        if (f5.isHovering !== undefined) {
            this.isHovering = f5.isHovering;
        }
        if (f5.chipNodeRadius === undefined) {
            this.__chipNodeRadius.set(void (0));
        }
        if (f5.chipEnabled === undefined) {
            this.__chipEnabled.set(true);
        }
        if (f5.isHover !== undefined) {
            this.isHover = f5.isHover;
        }
        if (f5.chipScale !== undefined) {
            this.chipScale = f5.chipScale;
        }
        if (f5.chipOpacity !== undefined) {
            this.chipOpacity = f5.chipOpacity;
        }
        if (f5.chipBlendColor !== undefined) {
            this.chipBlendColor = f5.chipBlendColor;
        }
        if (f5.deleteChip !== undefined) {
            this.deleteChip = f5.deleteChip;
        }
        if (f5.chipNodeOnFocus !== undefined) {
            this.chipNodeOnFocus = f5.chipNodeOnFocus;
        }
        if (f5.useDefaultSuffixIcon !== undefined) {
            this.useDefaultSuffixIcon = f5.useDefaultSuffixIcon;
        }
        if (f5.chipNodeSize !== undefined) {
            this.chipNodeSize = f5.chipNodeSize;
        }
        if (f5.onClose !== undefined) {
            this.onClose = f5.onClose;
        }
        if (f5.onClicked !== undefined) {
            this.onClicked = f5.onClicked;
        }
        if (f5.suffixIconOnFocus !== undefined) {
            this.suffixIconOnFocus = f5.suffixIconOnFocus;
        }
        if (f5.chipBreakPoints !== undefined) {
            this.chipBreakPoints = f5.chipBreakPoints;
        }
        if (f5.smListener !== undefined) {
            this.smListener = f5.smListener;
        }
        if (f5.mdListener !== undefined) {
            this.mdListener = f5.mdListener;
        }
        if (f5.lgListener !== undefined) {
            this.lgListener = f5.lgListener;
        }
        if (f5.isShowPressedBackGroundColor !== undefined) {
            this.isShowPressedBackGroundColor = f5.isShowPressedBackGroundColor;
        }
        if (f5.fontSizeScale !== undefined) {
            this.fontSizeScale = f5.fontSizeScale;
        }
        if (f5.fontWeightScale !== undefined) {
            this.fontWeightScale = f5.fontWeightScale;
        }
        if (f5.callbacks !== undefined) {
            this.callbacks = f5.callbacks;
        }
        if (f5.callbackId !== undefined) {
            this.callbackId = f5.callbackId;
        }
        if (f5.prefixSymbolWidth !== undefined) {
            this.prefixSymbolWidth = f5.prefixSymbolWidth;
        }
        if (f5.suffixSymbolWidth !== undefined) {
            this.suffixSymbolWidth = f5.suffixSymbolWidth;
        }
        if (f5.allowCloseSymbolWidth !== undefined) {
            this.allowCloseSymbolWidth = f5.allowCloseSymbolWidth;
        }
        if (f5.symbolEffect !== undefined) {
            this.symbolEffect = f5.symbolEffect;
  }
  }
  updateStateVars(params) {
    this.n2.reset(params.chipSize);
    this.o2.reset(params.allowClose);
    this.q2.reset(params.closeOptions);
    this.s2.reset(params.chipDirection);
    this.t2.reset(params.prefixIcon);
    this.u2.reset(params.prefixSymbol);
    this.v2.reset(params.label);
    this.w2.reset(params.suffixIcon);
    this.z2.reset(params.suffixSymbol);
    this.a3.reset(params.suffixSymbolOptions);
    this.b3.reset(params.chipNodeBackgroundColor);
    this.c3.reset(params.chipNodeActivatedBackgroundColor);
    this.d3.reset(params.chipNodeRadius);
    this.e3.reset(params.chipEnabled);
    this.f3.reset(params.chipActivated);
    this.g3.reset(params.chipAccessibilitySelectedType);
    this.h3.reset(params.chipAccessibilityDescription);
    this.i3.reset(params.chipAccessibilityLevel);
        }
  updateStateVars(params) {
    this.n2.reset(params.chipSize);
    this.o2.reset(params.allowClose);
    this.q2.reset(params.closeOptions);
    this.s2.reset(params.chipDirection);
    this.t2.reset(params.prefixIcon);
    this.u2.reset(params.prefixSymbol);
    this.v2.reset(params.label);
    this.w2.reset(params.suffixIcon);
    this.z2.reset(params.suffixSymbol);
    this.a3.reset(params.suffixSymbolOptions);
    this.b3.reset(params.chipNodeBackgroundColor);
    this.c3.reset(params.chipNodeActivatedBackgroundColor);
    this.d3.reset(params.chipNodeRadius);
    this.e3.reset(params.chipEnabled);
    this.f3.reset(params.chipActivated);
    this.g3.reset(params.chipAccessibilitySelectedType);
    this.h3.reset(params.chipAccessibilityDescription);
    this.i3.reset(params.chipAccessibilityLevel);
    }

    updateStateVars(e5) {
        this.__chipSize.reset(e5.chipSize);
        this.__allowClose.reset(e5.allowClose);
        this.__closeOptions.reset(e5.closeOptions);
        this.__chipDirection.reset(e5.chipDirection);
        this.__prefixIcon.reset(e5.prefixIcon);
        this.__prefixSymbol.reset(e5.prefixSymbol);
        this.__label.reset(e5.label);
        this.__suffixIcon.reset(e5.suffixIcon);
        this.__suffixSymbol.reset(e5.suffixSymbol);
        this.__suffixSymbolOptions.reset(e5.suffixSymbolOptions);
        this.__chipNodeBackgroundColor.reset(e5.chipNodeBackgroundColor);
        this.__chipNodeActivatedBackgroundColor.reset(e5.chipNodeActivatedBackgroundColor);
        this.__chipNodeRadius.reset(e5.chipNodeRadius);
        this.__chipEnabled.reset(e5.chipEnabled);
        this.__chipActivated.reset(e5.chipActivated);
        this.__chipAccessibilitySelectedType.reset(e5.chipAccessibilitySelectedType);
        this.__chipAccessibilityDescription.reset(e5.chipAccessibilityDescription);
        this.__chipAccessibilityLevel.reset(e5.chipAccessibilityLevel);
    }

    purgeVariableDependenciesOnElmtId(d5) {
        this.__chipSize.purgeDependencyOnElmtId(d5);
        this.__allowClose.purgeDependencyOnElmtId(d5);
        this.__closeOptions.purgeDependencyOnElmtId(d5);
        this.__chipDirection.purgeDependencyOnElmtId(d5);
        this.__prefixIcon.purgeDependencyOnElmtId(d5);
        this.__prefixSymbol.purgeDependencyOnElmtId(d5);
        this.__label.purgeDependencyOnElmtId(d5);
        this.__suffixIcon.purgeDependencyOnElmtId(d5);
        this.__suffixSymbol.purgeDependencyOnElmtId(d5);
        this.__suffixSymbolOptions.purgeDependencyOnElmtId(d5);
        this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(d5);
        this.__isSetBg.purgeDependencyOnElmtId(d5);
        this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(d5);
        this.__isSetActiveBg.purgeDependencyOnElmtId(d5);
        this.__isHovering.purgeDependencyOnElmtId(d5);
        this.__chipNodeRadius.purgeDependencyOnElmtId(d5);
        this.__chipEnabled.purgeDependencyOnElmtId(d5);
        this.__chipActivated.purgeDependencyOnElmtId(d5);
        this.__chipAccessibilitySelectedType.purgeDependencyOnElmtId(d5);
        this.__chipAccessibilityDescription.purgeDependencyOnElmtId(d5);
        this.__chipAccessibilityLevel.purgeDependencyOnElmtId(d5);
        this.__isHover.purgeDependencyOnElmtId(d5);
        this.__chipScale.purgeDependencyOnElmtId(d5);
        this.__chipOpacity.purgeDependencyOnElmtId(d5);
        this.__chipBlendColor.purgeDependencyOnElmtId(d5);
        this.__deleteChip.purgeDependencyOnElmtId(d5);
        this.__chipNodeOnFocus.purgeDependencyOnElmtId(d5);
        this.__useDefaultSuffixIcon.purgeDependencyOnElmtId(d5);
        this.__suffixIconOnFocus.purgeDependencyOnElmtId(d5);
        this.__chipBreakPoints.purgeDependencyOnElmtId(d5);
        this.__isShowPressedBackGroundColor.purgeDependencyOnElmtId(d5);
        this.__fontSizeScale.purgeDependencyOnElmtId(d5);
        this.__fontWeightScale.purgeDependencyOnElmtId(d5);
        this.__prefixSymbolWidth.purgeDependencyOnElmtId(d5);
        this.__suffixSymbolWidth.purgeDependencyOnElmtId(d5);
        this.__allowCloseSymbolWidth.purgeDependencyOnElmtId(d5);
        this.__symbolEffect.purgeDependencyOnElmtId(d5);
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
        this.__isSetBg.aboutToBeDeleted();
        this.__chipNodeActivatedBackgroundColor.aboutToBeDeleted();
        this.__isSetActiveBg.aboutToBeDeleted();
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

    set chipSize(c5) {
        this.__chipSize.set(c5);
    }

    get allowClose() {
        return this.__allowClose.get();
    }

    set allowClose(b5) {
        this.__allowClose.set(b5);
    }

    get closeOptions() {
        return this.__closeOptions.get();
    }

    set closeOptions(a5) {
        this.__closeOptions.set(a5);
    }

    get chipDirection() {
        return this.__chipDirection.get();
    }

    set chipDirection(z4) {
        this.__chipDirection.set(z4);
    }

    get prefixIcon() {
        return this.__prefixIcon.get();
    }

    set prefixIcon(y4) {
        this.__prefixIcon.set(y4);
    }

    get prefixSymbol() {
        return this.__prefixSymbol.get();
    }

    set prefixSymbol(x4) {
        this.__prefixSymbol.set(x4);
    }

    get label() {
        return this.__label.get();
    }

    set label(w4) {
        this.__label.set(w4);
    }

    get suffixIcon() {
        return this.__suffixIcon.get();
    }

    set suffixIcon(v4) {
        this.__suffixIcon.set(v4);
    }

    get suffixSymbol() {
        return this.__suffixSymbol.get();
    }

    set suffixSymbol(u4) {
        this.__suffixSymbol.set(u4);
    }

    get suffixSymbolOptions() {
        return this.__suffixSymbolOptions.get();
    }

    set suffixSymbolOptions(t4) {
        this.__suffixSymbolOptions.set(t4);
    }

    get chipNodeBackgroundColor() {
        return this.__chipNodeBackgroundColor.get();
    }

    set chipNodeBackgroundColor(s4) {
        this.__chipNodeBackgroundColor.set(s4);
    }

    get isSetBg() {
        return this.__isSetBg.get();
    }

    set isSetBg(r4) {
        this.__isSetBg.set(r4);
    }

    get chipNodeActivatedBackgroundColor() {
        return this.__chipNodeActivatedBackgroundColor.get();
    }

    set chipNodeActivatedBackgroundColor(q4) {
        this.__chipNodeActivatedBackgroundColor.set(q4);
    }

    get isSetActiveBg() {
        return this.__isSetActiveBg.get();
    }

    set isSetActiveBg(p4) {
        this.__isSetActiveBg.set(p4);
    }

    get isHovering() {
        return this.__isHovering.get();
    }

    set isHovering(o4) {
        this.__isHovering.set(o4);
    }

    get chipNodeRadius() {
        return this.__chipNodeRadius.get();
    }

    set chipNodeRadius(n4) {
        this.__chipNodeRadius.set(n4);
    }

    get chipEnabled() {
        return this.__chipEnabled.get();
    }

    set chipEnabled(m4) {
        this.__chipEnabled.set(m4);
    }

    get chipActivated() {
        return this.__chipActivated.get();
    }

    set chipActivated(l4) {
        this.__chipActivated.set(l4);
    }

    get chipAccessibilitySelectedType() {
        return this.__chipAccessibilitySelectedType.get();
    }

    set chipAccessibilitySelectedType(k4) {
        this.__chipAccessibilitySelectedType.set(k4);
    }

    get chipAccessibilityDescription() {
        return this.__chipAccessibilityDescription.get();
    }

    set chipAccessibilityDescription(j4) {
        this.__chipAccessibilityDescription.set(j4);
    }

    get chipAccessibilityLevel() {
        return this.__chipAccessibilityLevel.get();
    }

    set chipAccessibilityLevel(i4) {
        this.__chipAccessibilityLevel.set(i4);
    }

    get isHover() {
        return this.__isHover.get();
    }

    set isHover(h4) {
        this.__isHover.set(h4);
    }

    get chipScale() {
        return this.__chipScale.get();
    }

    set chipScale(g4) {
        this.__chipScale.set(g4);
    }

    get chipOpacity() {
        return this.__chipOpacity.get();
    }

    set chipOpacity(f4) {
        this.__chipOpacity.set(f4);
    }

    get chipBlendColor() {
        return this.__chipBlendColor.get();
    }

    set chipBlendColor(e4) {
        this.__chipBlendColor.set(e4);
    }

    get deleteChip() {
        return this.__deleteChip.get();
    }

    set deleteChip(d4) {
        this.__deleteChip.set(d4);
    }

    get chipNodeOnFocus() {
        return this.__chipNodeOnFocus.get();
    }

    set chipNodeOnFocus(c4) {
        this.__chipNodeOnFocus.set(c4);
    }

    get useDefaultSuffixIcon() {
        return this.__useDefaultSuffixIcon.get();
    }

    set useDefaultSuffixIcon(b4) {
        this.__useDefaultSuffixIcon.set(b4);
    }

    get suffixIconOnFocus() {
        return this.__suffixIconOnFocus.get();
    }

    set suffixIconOnFocus(a4) {
        this.__suffixIconOnFocus.set(a4);
    }

    get chipBreakPoints() {
        return this.__chipBreakPoints.get();
    }

    set chipBreakPoints(z3) {
        this.__chipBreakPoints.set(z3);
    }

    get isShowPressedBackGroundColor() {
        return this.__isShowPressedBackGroundColor.get();
    }

    set isShowPressedBackGroundColor(y3) {
        this.__isShowPressedBackGroundColor.set(y3);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(x3) {
        this.__fontSizeScale.set(x3);
    }

    get fontWeightScale() {
        return this.__fontWeightScale.get();
    }

    set fontWeightScale(w3) {
        this.__fontWeightScale.set(w3);
    }

    get prefixSymbolWidth() {
        return this.__prefixSymbolWidth.get();
    }

    set prefixSymbolWidth(v3) {
        this.__prefixSymbolWidth.set(v3);
    }

    get suffixSymbolWidth() {
        return this.__suffixSymbolWidth.get();
    }

    set suffixSymbolWidth(u3) {
        this.__suffixSymbolWidth.set(u3);
    }

    get allowCloseSymbolWidth() {
        return this.__allowCloseSymbolWidth.get();
    }

    set allowCloseSymbolWidth(t3) {
        this.__allowCloseSymbolWidth.set(t3);
    }

    get symbolEffect() {
        return this.__symbolEffect.get();
    }

    set symbolEffect(s3) {
        this.__symbolEffect.set(s3);
    }

    isChipSizeEnum() {
        return typeof (this.chipSize) === 'string';
    }

    isShowCloseIconMargin() {
        return this.verifyResource(this.theme.defaultSymbol.isShowMargin, 0) !== 0 && this.allowClose;
    }

    getLabelFontSize() {
        if (this.label?.fontSize !== void (0) && this.toVp(this.label.fontSize) >= 0) {
            return this.label.fontSize;
        }
        let q3 = this.theme.label.smallFontSize;
        if (this.isChipSizeEnum() && this.chipSize !== ChipSize.SMALL) {
            q3 = this.theme.label.normalFontSize;
        }
        return this.sizeToVp(q3);
    }

    verifyResource(m3, n3) {
        if (m3 && m3.params && Array.isArray(m3.params) &&
        m3.params[0] && m3.params[0].includes('.') &&
            m3.params[0].split('.').length > 2) {
            try {
                let p3 = getContext(this).resourceManager.getNumberByName((m3.params[0]).split('.')[2]);
                return p3;
            } catch (o3) {
                return n3;
            }
        }
        return n3;
    }

    getIconSize() {
        if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
            return this.theme.prefixIcon.smallSize.width;
        } else {
            return this.theme.prefixIcon.normalSize.width;
        }
    }

    defaultSymbolFontsize() {
        if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
            return this.theme.defaultSymbol.smallFontSize;
        } else {
            return this.theme.defaultSymbol.normalFontSize;
        }
    }

    sizeToVp(k3) {
        let l3 = LengthMetrics.resource(k3);
        return this.lengthMetricsToVp(l3);
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
        return this.verifyResource(this.theme.label.fontWeight, FontWeight.Regular);
    }

    lengthMetricsToVp(i3) {
        let j3 = 0;
        if (i3) {
            switch (i3.unit) {
                case LengthUnit.PX:
                    return px2vp(i3.value);
                case LengthUnit.VP:
                    return i3.value;
                case LengthUnit.FP:
                    return px2vp(fp2px(i3.value));
                case LengthUnit.PERCENT:
                    return Number.NEGATIVE_INFINITY;
                case LengthUnit.LPX:
                    return px2vp(lpx2px(i3.value));
            }
        }
        return j3;
    }

    toVp(b3) {
        if (b3 === void (0)) {
            return Number.NEGATIVE_INFINITY;
        }
        switch (typeof (b3)) {
            case 'number':
                return b3;
            case 'object':
                try {
                    let h3 = this.lengthMetricsToVp(LengthMetrics.resource(b3));
                    if (h3 === 0 &&
                        !isValidResource(getContext(this), b3)) {
                        return Number.NEGATIVE_INFINITY;
                    }
                    return h3;
                } catch (g3) {
                    return Number.NEGATIVE_INFINITY;
                }
            case 'string':
                let c3 = new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i");
                let d3 = b3.match(c3);
                if (!d3) {
                    return Number.NEGATIVE_INFINITY;
                }
                let e3 = Number(d3?.[1] ?? 0);
                let f3 = d3?.[2] ?? 'vp';
                switch (f3.toLowerCase()) {
                    case 'px':
                        e3 = px2vp(e3);
                        break;
                    case 'fp':
                        e3 = px2vp(fp2px(e3));
                        break;
                    case 'lpx':
                        e3 = px2vp(lpx2px(e3));
                        break;
                    case '%':
                        e3 = Number.NEGATIVE_INFINITY;
                        break;
                    case 'vp':
                        break;
                    default:
                        break;
                }
                return e3;
            default:
                return Number.NEGATIVE_INFINITY;
    }
    }

    getChipNodeBorderWidth() {
        return this.isSetBackgroundColor() ? 0 :
        this.sizeToVp(this.theme.chipNode.defaultBorderWidth);
    }

    getChipNodeBorderColor() {
        let a3 = this.theme.chipNode;
        return this.getChipActive() ? a3.activatedBorderColor : a3.borderColor;
    }

    getLabelMargin() {
        let z2 = { left: 0, right: 0 };
        if (this.label?.labelMargin?.left !== void (0) && this.toVp(this.label.labelMargin.left) >= 0) {
            z2.left = this.label?.labelMargin?.left;
        } else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                z2.left = this.theme.label.smallMargin.left;
            } else {
                z2.left = this.theme.label.normalMargin.left;
            }
        }
        if (this.label?.labelMargin?.right !== void (0) && this.toVp(this.label.labelMargin.right) >= 0) {
            z2.right = this.label?.labelMargin?.right;
        } else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
            this.suffixIcon?.src || this.useDefaultSuffixIcon) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                z2.right = this.theme.label.smallMargin.right;
            } else {
                z2.right = this.theme.label.normalMargin.right;
            }
        }
        return z2;
    }

    getLocalizedLabelMargin() {
        let y2 = { start: LengthMetrics.vp(0), end: LengthMetrics.vp(0) };
        if (this.label?.localizedLabelMargin?.start?.value !== void (0) &&
            this.lengthMetricsToVp(this.label.localizedLabelMargin.start) >= 0) {
            y2.start = this.label?.localizedLabelMargin?.start;
        } else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                y2.start = this.theme.label.localizedSmallMargin.start;
            } else {
                y2.start = this.theme.label.localizedNormalMargin.start;
            }
        }
        if (this.label?.localizedLabelMargin?.end?.value !== void (0) &&
            this.lengthMetricsToVp(this.label.localizedLabelMargin.end) >= 0) {
            y2.end = this.label?.localizedLabelMargin?.end;
        } else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
            this.suffixIcon?.src || this.useDefaultSuffixIcon || this.isShowCloseIconMargin()) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                y2.end = this.theme.label.localizedSmallMargin.end;
            } else {
                y2.end = this.theme.label.localizedNormalMargin.end;
            }
        }
        return y2;
    }

    getLabelStartEndVp() {
        let w2 = this.getLocalizedLabelMargin();
        if (this.label && (this.label.labelMargin !== void (0)) && (this.label.localizedLabelMargin === void (0))) {
            let x2 = this.getLabelMargin();
            return {
                start: LengthMetrics.vp(this.toVp(x2.left)),
                end: LengthMetrics.vp(this.toVp(x2.right))
            };
        }
        return {
            start: LengthMetrics.vp(this.lengthMetricsToVp(w2.start)),
            end: LengthMetrics.vp(this.lengthMetricsToVp(w2.end))
        };
    }

    getActualLabelMargin() {
        let v2 = this.getLocalizedLabelMargin();
        if (this.label && this.label.localizedLabelMargin !== void (0)) {
            return v2;
        }
        if (this.label && this.label.labelMargin !== void (0)) {
            return this.getLabelMargin();
        }
        return v2;
    }

    getSuffixIconSize() {
        let u2 = { width: 0, height: 0 };
        if (this.suffixIcon?.size?.width !== void (0) && this.toVp(this.suffixIcon?.size?.width) >= 0) {
            u2.width = this.suffixIcon?.size?.width;
        } else {
            u2.width = this.getSuffixIconSrc() ?
            this.sizeToVp(this.getIconSize()) : 0;
        }
        if (this.suffixIcon?.size?.height !== void (0) && this.toVp(this.suffixIcon?.size?.height) >= 0) {
            u2.height = this.suffixIcon?.size?.height;
        } else {
            u2.height = this.getSuffixIconSrc() ?
            this.sizeToVp(this.getIconSize()) : 0;
        }
        return u2;
    }

    getPrefixIconSize() {
        let t2 = { width: 0, height: 0 };
        if (this.prefixIcon?.size?.width !== void (0) && this.toVp(this.prefixIcon?.size?.width) >= 0) {
            t2.width = this.prefixIcon?.size?.width;
        } else {
            if (this.prefixIcon?.src) {
                t2.width = this.sizeToVp(this.getIconSize());
            } else {
                t2.width = 0;
            }
        }
        if (this.prefixIcon?.size?.height !== void (0) && this.toVp(this.prefixIcon?.size?.height) >= 0) {
            t2.height = this.prefixIcon?.size?.height;
        } else {
            if (this.prefixIcon?.src) {
                t2.height = this.getIconSize();
            } else {
                t2.height = 0;
            }
        }
        return t2;
    }

    getActiveIconColor() {
        return this.chipNodeOnFocus ? this.theme.prefixIcon.focusActivatedColor :
        this.theme.prefixIcon.activatedFillColor;
    }

    getFillIconColor(s2) {
        if (s2 === IconType.PREFIX_ICON) {
            if (this.prefixIcon?.fillColor) {
                return this.prefixIcon.fillColor;
            }
            return this.chipNodeOnFocus ? this.theme.prefixIcon.focusFillColor : this.theme.prefixIcon.fillColor;
        } else {
            if (this.suffixIcon?.fillColor) {
                return this.suffixIcon.fillColor;
            }
            return this.chipNodeOnFocus ? this.theme.suffixIcon.focusFillColor : this.theme.suffixIcon.fillColor;
        }
    }

    getActiveIconColorArray(r2) {
        if (r2 === IconType.PREFIX_ICON) {
            return this.getColorArray(this.prefixIcon?.activatedFillColor, this.theme.prefixIcon.focusActivatedColor,
                this.theme.prefixIcon.activatedFillColor);
        } else {
            return this.getColorArray(this.suffixIcon?.activatedFillColor, this.theme.suffixIcon.focusActivatedColor,
                this.theme.suffixIcon.activatedFillColor);
        }
    }

    getColorArray(o2, p2, q2) {
        if (o2) {
            return [o2];
        }
        return this.chipNodeOnFocus ? [p2] : [q2];
    }

    getFillIconColorArray(n2) {
        if (n2 === IconType.PREFIX_ICON) {
            return this.getColorArray(this.prefixIcon?.fillColor, this.theme.prefixIcon.focusFillColor,
                this.theme.prefixIcon.fillColor);
        } else {
            return this.getColorArray(this.suffixIcon?.fillColor, this.theme.suffixIcon.focusFillColor,
                this.theme.suffixIcon.fillColor);
        }
    }

    getPrefixIconFilledColor() {
        if (this.getChipActive()) {
            return this.prefixIcon?.activatedFillColor ?? this.getActiveIconColor();
        }
        return this.prefixIcon?.fillColor ?? this.getFillIconColor(IconType.PREFIX_ICON);
    }

    getSuffixIconFilledColor() {
        if (this.getChipActive()) {
            return this.suffixIcon?.activatedFillColor ?? this.getActiveIconColor();
        }
        return this.suffixIcon?.fillColor ?? this.getFillIconColor(IconType.SUFFIX_ICON);
    }

    getDefaultSymbolColor(m2) {
        if (this.getChipActive()) {
            return this.getActiveIconColorArray(m2);
        }
        return this.getFillIconColorArray(m2);
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
        return (this.useDefaultSuffixIcon && (this.allowClose ?? true)) || this.suffixIcon?.action !== void (0);
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
            this.sizeToVp(this.theme.chipNode.smallBorderRadius) :
            this.sizeToVp(this.theme.chipNode.normalBorderRadius));
        }
    }

    getChipNodeBackGroundColor() {
        let i2 = this.theme.chipNode;
        let j2;
        if (this.chipNodeOnFocus && !this.isSetBackgroundColor()) {
            j2 = this.getChipActive() ? i2.focusActivatedBgColor :
            i2.focusBgColor;
            return j2;
        }
        if (this.getChipActive()) {
            j2 = this.chipNodeActivatedBackgroundColor ?? i2.activatedBackgroundColor;
        } else {
            j2 = this.chipNodeBackgroundColor ?? i2.backgroundColor;
        }
        let k2;
        try {
            k2 = ColorMetrics.resourceColor(j2);
        } catch (l2) {
            hilog.error(0x3900, 'Ace', `Chip resourceColor, error: ${l2.toString()}`);
            k2 = ColorMetrics.resourceColor(Color.Transparent);
        }
        if (this.isShowPressedBackGroundColor) {
            this.isHovering = false;
            return k2.blendColor(ColorMetrics.resourceColor(this.isSetBackgroundColor() ?
            Color.Transparent : i2.pressedBlendColor))
                .color;
        }
        if (this.isHovering) {
            return k2.blendColor(ColorMetrics.resourceColor(this.isSetBackgroundColor() ?
            Color.Transparent : i2.hoverBlendColor))
                .color;
        }
        return j2;
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
            textContent: this.label?.text ?? "",
            fontSize: this.getLabelFontSize(),
            fontFamily: this.label?.fontFamily ?? this.theme.label.fontFamily,
            fontWeight: this.getLabelFontWeight(),
            maxLines: 1,
            overflow: TextOverflow.Ellipsis,
            textAlign: TextAlign.Center
        }));
    }

    getCalculateChipNodeWidth() {
        let g2 = 0;
        let h2 = this.getLabelStartEndVp();
        g2 += this.getChipNodeBorderWidth() * 2;
        g2 += this.getChipNodePadding().start?.value ?? 0;
        g2 += this.toVp(this.getPrefixChipWidth());
        g2 += this.toVp(h2.start?.value ?? 0);
        g2 += this.getLabelWidth();
        g2 += this.toVp(h2.end?.value ?? 0);
        g2 += this.toVp(this.getSuffixChipWidth());
        g2 += this.getChipNodePadding().end?.value ?? 0;
        return g2;
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

    getfocusBox() {
        return this.chipNodeOnFocus ? { strokeWidth: LengthMetrics.vp(2) } : { strokeWidth: LengthMetrics.vp(0) };
    }

    handleTouch(f2) {
        if (!this.getChipEnable()) {
            return;
        }
        if (this.isHover) {
            if (f2.type === TouchType.Down || f2.type === TouchType.Move) {
                this.isShowPressedBackGroundColor = true;
            } else if (f2.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            } else {
                this.isShowPressedBackGroundColor = false;
            }
        } else {
            if (f2.type === TouchType.Down || f2.type === TouchType.Move) {
                this.isShowPressedBackGroundColor = true;
            } else if (f2.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            } else {
                this.isShowPressedBackGroundColor = false;
            }
        }
    }

    hoverAnimate(e2) {
        if (!this.getChipEnable()) {
            return;
        }
        this.isHover = e2;
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

    focusBtnChipNodeAnimate() {
        this.chipScale = {
            x: this.verifyResource(this.theme.chipNode.focusBtnScaleX, 1),
            y: this.verifyResource(this.theme.chipNode.focusBtnScaleY, 1),
        };
    }

    blurBtnChipNodeAnimate() {
        this.chipScale = {
            x: 1,
            y: 1,
        };
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
        let d2 = this.getChipConstraintWidth();
        return Math.min(Math.max(this.getCalculateChipNodeWidth(), d2.minWidth), d2.maxWidth);
    }

    getFocusOverlaySize() {
        return {
            width: Math.max(this.getChipNodeWidth(), this.getChipConstraintWidth().minWidth) + 8,
            height: this.getChipNodeHeight() + 8
        };
    }

    getChipConstraintWidth() {
        let a2 = this.getReserveChipNodeWidth();
        let b2 = this.getCalculateChipNodeWidth();
        let c2;
        switch (this.chipBreakPoints) {
            case BreakPointsType.SM:
                c2 = {
                    minWidth: a2,
                    maxWidth: Math.min(b2, this.theme.chipNode.breakPointConstraintWidth.breakPointSmMaxWidth)
                };
                break;
            case BreakPointsType.MD:
                c2 = {
                    minWidth: Math.max(b2, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(b2, this.theme.chipNode.breakPointConstraintWidth.breakPointMdMaxWidth)
                };
                break;
            case BreakPointsType.LG:
                c2 = {
                    minWidth: Math.max(b2, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(b2, this.theme.chipNode.breakPointConstraintWidth.breakPointLgMaxWidth)
                };
                break;
            default:
                c2 = { minWidth: a2, maxWidth: b2 };
                break;
        }
        c2.minWidth = Math.min(Math.max(this.getCalculateChipNodeWidth(), c2.minWidth), c2.maxWidth);
        c2.minHeight = this.getChipNodeHeight();
        if (!this.isChipSizeEnum() && this.chipNodeSize?.height !== void (0) &&
            this.toVp(this.chipNodeSize?.height) >= 0) {
            c2.maxHeight = this.toVp(this.chipNodeSize.height);
            c2.minHeight = this.toVp(this.chipNodeSize.height);
        }
        if (!this.isChipSizeEnum() && this.chipNodeSize?.width !== void (0) &&
            this.toVp(this.chipNodeSize?.width) >= 0) {
            c2.minWidth = this.toVp(this.chipNodeSize.width);
            c2.maxWidth = this.toVp(this.chipNodeSize.width);
        } else if (this.toVp(this.fontSizeScale) >= this.theme.chipNode.suitAgeScale) {
            c2.minWidth = void (0);
            c2.maxWidth = void (0);
        }
        return c2;
    }

    focusOverlay(t1 = null) {
        this.observeComponentCreation2((y1, z1) => {
            Stack.create();
            Stack.direction(this.chipDirection);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((u1, v1) => {
            If.create();
            if (this.chipNodeOnFocus && !this.suffixIconOnFocus) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w1, x1) => {
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
        if (this.chipNodeBackgroundColor) {
            this.isSetBg = true;
        } else {
            this.isSetBg = false;
            this.chipNodeBackgroundColor = this.theme.chipNode.backgroundColor;
        }
        if (this.chipNodeActivatedBackgroundColor) {
            this.isSetActiveBg = true;
        } else {
            this.isSetActiveBg = false;
            this.chipNodeActivatedBackgroundColor = this.theme.chipNode.activatedBackgroundColor;
        }
        let p1 = this.getUIContext();
        this.fontSizeScale = p1.getHostContext()?.config?.fontSizeScale ?? 1;
        this.smListener.on("change", (s1) => {
            if (s1.matches) {
                this.chipBreakPoints = BreakPointsType.SM;
            }
        });
        this.mdListener.on("change", (r1) => {
            if (r1.matches) {
                this.chipBreakPoints = BreakPointsType.MD;
            }
        });
        this.lgListener.on("change", (q1) => {
            if (q1.matches) {
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

    isSetBackgroundColor() {
        return this.isSetBg || (this.isSetActiveBg && (this.chipActivated || false));
    }

    getShadowStyles() {
        if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
            let n1 = this.theme.chipNode.smallShadowStyle;
            let o1 = this.verifyResource(n1, -1);
            return o1;
        } else {
            let l1 = this.theme.chipNode.normalShadowStyle;
            let m1 = this.verifyResource(l1, -1);
            return m1;
        }
    }

    aboutToDisappear() {
        this.smListener.off("change");
        this.mdListener.off("change");
        this.lgListener.off("change");
        if (this.callbackId) {
            this.getUIContext()
                .getHostContext()
            ?.getApplicationContext()
            ?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
    }

    chipBuilder(c = null) {
        this.observeComponentCreation2((h1, i1) => {
            Button.createWithChild();
            Button.constraintSize(this.getChipConstraintWidth());
            Button.direction(this.chipDirection);
            Button.type(ButtonType.Normal);
            Button.clip(false);
            Button.backgroundColor(this.getChipNodeBackGroundColor());
            Button.borderRadius(this.getChipNodeRadius());
            Button.enabled(this.getChipEnable());
            Button.scale(ObservedObject.GetRawObject(this.chipScale));
            Button.focusable(true);
            Button.opacity(this.getChipNodeOpacity());
            Button.focusBox(this.getfocusBox());
            Button.shadow(this.chipNodeOnFocus ? this.getShadowStyles() : undefined);
            Button.padding(0);
            Button.accessibilityGroup(true);
            Button.accessibilityDescription(this.getAccessibilityDescription());
            Button.accessibilityLevel(this.getAccessibilityLevel());
            Button.accessibilityChecked(this.getAccessibilityChecked());
            Button.accessibilitySelected(this.getAccessibilitySelected());
            Button.onFocus(() => {
                this.focusBtnChipNodeAnimate();
                this.chipNodeOnFocus = true;
            });
            Button.onBlur(() => {
                this.chipNodeOnFocus = false;
                this.blurBtnChipNodeAnimate();
            });
            Button.onTouch((k1) => {
                this.handleTouch(k1);
            });
            Button.onHover((j1) => {
                this.isHovering = j1;
            });
            Button.onKeyEvent((c6) => {
                if (!c6 || c6.type !== KeyType.Down) {
                    return;
                }
                let h6 = c6.keyCode === KeyCode.KEYCODE_FORWARD_DEL &&
                    !this.suffixIconOnFocus;
                let i6 = c6.keyCode === KeyCode.KEYCODE_ENTER &&
                this.allowClose && !this.suffixIcon?.src;
                if (h6 || i6) {
                    this.deleteChipNodeAnimate();
                }
            });
            Button.onClick(this.onClicked === noop ? undefined : this.onClicked.bind(this));
        }, Button);
        this.observeComponentCreation2((f1, g1) => {
            Row.create();
            Row.direction(this.chipDirection);
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.Center);
            Row.padding(this.getChipNodePadding());
            Row.constraintSize(this.getChipConstraintWidth());
            Row.borderWidth(this.getChipNodeBorderWidth());
            Row.borderColor(this.getChipNodeBorderColor());
            Row.borderRadius(this.getChipNodeRadius());
        }, Row);
        this.observeComponentCreation2((x, y) => {
            If.create();
            if (this.prefixSymbol?.normal || this.prefixSymbol?.activated) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b1, c1) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.defaultSymbolFontsize());
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.PREFIX_ICON));
                        SymbolGlyph.attributeModifier.bind(this)(this.getPrefixSymbolModifier());
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect),
                            this.theme.defaultSymbol.defaultEffect);
                        SymbolGlyph.onSizeChange((d1, e1) => {
                            this.prefixSymbolWidth = e1?.width;
                        });
                        SymbolGlyph.key('PrefixSymbolGlyph');
                    }, SymbolGlyph);
                });
            } else if (this.prefixIcon?.src !== "") {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((z, a1) => {
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
        this.observeComponentCreation2((v, w) => {
            Text.create(this.label?.text ?? "");
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
        this.observeComponentCreation2((d, e) => {
            If.create();
            if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t, u) => {
                        Button.createWithChild({ type: ButtonType.Normal });
                        Button.onClick(this.getSuffixSymbolAction());
                        Button.accessibilityText(this.getSuffixSymbolAccessibilityText());
                        Button.accessibilityDescription(this.getSuffixSymbolAccessibilityDescription());
                        Button.accessibilityLevel(this.getSuffixSymbolAccessibilityLevel());
                        Button.backgroundColor(Color.Transparent);
                        Button.borderRadius(0);
                        Button.padding(0);
                        Button.stateEffect(false);
                    }, Button);
                    this.observeComponentCreation2((p, q) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.defaultSymbolFontsize());
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_ICON));
                        SymbolGlyph.attributeModifier.bind(this)(this.getSuffixSymbolModifier());
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect),
                            this.theme.defaultSymbol.defaultEffect);
                        SymbolGlyph.onSizeChange((r, s) => {
                            this.suffixSymbolWidth = s?.width;
                        });
                        SymbolGlyph.key('SuffixSymbolGlyph');
                    }, SymbolGlyph);
                    Button.pop();
                });
            } else if (this.suffixIcon?.src !== "") {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((n, o) => {
                        Button.createWithChild({ type: ButtonType.Normal });
                        Button.backgroundColor(Color.Transparent);
                        Button.borderRadius(0);
                        Button.padding(0);
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
                    }, Button);
                    this.observeComponentCreation2((l, m) => {
                        Image.create(this.getSuffixIconSrc());
                        Image.direction(this.chipDirection);
                        Image.opacity(this.getChipNodeOpacity());
                        Image.size(this.getSuffixIconSize());
                        Image.fillColor(this.getSuffixIconFilledColor());
                        Image.enabled(this.getChipEnable());
                        Image.focusable(this.getSuffixIconFocusable());
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
                    this.observeComponentCreation2((j, k) => {
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
                    }, Button);
                    this.observeComponentCreation2((f, g) => {
                        SymbolGlyph.create({
                            "id": -1,
                            "type": 40000,
                            params: ['sys.symbol.xmark'],
                            "bundleName": "__harDefaultBundleName__",
                            "moduleName": "__harDefaultModuleName__"
                        });
                        SymbolGlyph.fontSize(this.defaultSymbolFontsize());
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_ICON));
                        SymbolGlyph.onSizeChange((h, i) => {
                            this.allowCloseSymbolWidth = i?.width;
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
            if (!this.suffixSymbolOptions?.activatedAccessibility?.accessibilityLevel) {
                return this.suffixSymbolOptions?.action ? 'yes' : 'no';
            }
            return this.suffixSymbolOptions.activatedAccessibility.accessibilityLevel;
        }
        if (!this.suffixSymbolOptions?.normalAccessibility?.accessibilityLevel) {
            return this.suffixSymbolOptions?.action ? 'yes' : 'no';
        }
        return this.suffixSymbolOptions.normalAccessibility.accessibilityLevel;
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
        if (this.closeOptions?.accessibilityLevel) {
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
                "id": -1,
                "type": 10003,
                params: ['sys.string.delete_used_for_accessibility_text'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            };
        }
        return this.closeOptions.accessibilityText;
    }

    getSuffixIconAccessibilityLevel() {
        if (!this.suffixIcon.accessibilityLevel) {
            return !this.suffixIcon.action ? 'no' : 'yes';
        }
        return this.suffixIcon.accessibilityLevel;
    }

    getSuffixIconAccessibilityDescription() {
        if (typeof this.suffixIcon.accessibilityDescription === 'undefined') {
            return undefined;
        }
        return this.suffixIcon.accessibilityDescription;
    }

    getSuffixIconAccessibilityText() {
        if (typeof this.suffixIcon.accessibilityText === 'undefined') {
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

    initialRender() {
        this.observeComponentCreation2((a, b) => {
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
