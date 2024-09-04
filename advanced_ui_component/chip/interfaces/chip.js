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
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const measure = requireNapi('measure');
const mediaquery = requireNapi('mediaquery');
const resourceManager = requireNapi('resourceManager');
const componentUtils = requireNapi('arkui.componentUtils');
const hilog = requireNapi('hilog');
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const EnvironmentCallback = requireNapi('EnvironmentCallback');

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}

const resourceFn = resourceManager.getSystemResourceManager();
export var ChipSize;
(function (ChipSize) {
    ChipSize["NORMAL"] = "NORMAL";
    ChipSize["SMALL"] = "SMALL";
})(ChipSize || (ChipSize = {}));
var IconType;
(function (IconType) {
    IconType["PREFIX_ICON"] = "PREFIXICON";
    IconType["SUFFIX_ICON"] = "SUFFIXICON";
})(IconType || (IconType = {}));
var BreakPointsType;
(function (BreakPointsType) {
    BreakPointsType["SM"] = "SM";
    BreakPointsType["MD"] = "MD";
    BreakPointsType["LG"] = "LG";
})(BreakPointsType || (BreakPointsType = {}));
export const defaultTheme = {
    prefixIcon: {
        normalSize: {
            width: { "id": -1, "type": 10002, params: ['sys.float.chip_normal_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            height: { "id": -1, "type": 10002, params: ['sys.float.chip_normal_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
        },
        smallSize: {
            width: { "id": -1, "type": 10002, params: ['sys.float.chip_small_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            height: { "id": -1, "type": 10002, params: ['sys.float.chip_small_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
        },
        fillColor: { "id": -1, "type": 10001, params: ['sys.color.chip_usually_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        activatedFillColor: { "id": -1, "type": 10001, params: ['sys.color.chip_active_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        focusFillColor: { "id": -1, "type": 10001, params: ['sys.color.chip_icon_focus_fill'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        focusActivatedColor: { "id": -1, "type": 10001, params: ['sys.color.chip_icon_focus_activated'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    },
    label: {
        normalFontSize: { "id": -1, "type": 10002, params: ['sys.float.chip_normal_font_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        smallFontSize: { "id": -1, "type": 10002, params: ['sys.float.chip_small_font_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        focusFontColor: { "id": -1, "type": 10001, params: ['sys.color.chip_focus_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        focusActiveFontColor: { "id": -1, "type": 10001, params: ['sys.color.chip_focus_activated_fontcolor'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fontColor: { "id": -1, "type": 10001, params: ['sys.color.chip_font_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        activatedFontColor: { "id": -1, "type": 10001, params: ['sys.color.chip_activated_fontcolor'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fontFamily: "HarmonyOS Sans",
        normalMargin: { left: 6, right: 6, top: 0, bottom: 0 },
        smallMargin: { left: 4, right: 4, top: 0, bottom: 0 },
        defaultFontSize: 14,
        localizedNormalMargin: {
            start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.chip_normal_text_margin'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.chip_normal_text_margin'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            top: LengthMetrics.vp(0),
            bottom: LengthMetrics.vp(0)
        },
        localizedSmallMargin: {
            start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.chip_small_text_margin'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.chip_small_text_margin'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            top: LengthMetrics.vp(0),
            bottom: LengthMetrics.vp(0),
        }
    },
    suffixIcon: {
        normalSize: {
            width: { "id": -1, "type": 10002, params: ['sys.float.chip_normal_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            height: { "id": -1, "type": 10002, params: ['sys.float.chip_normal_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
        },
        smallSize: {
            width: { "id": -1, "type": 10002, params: ['sys.float.chip_small_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            height: { "id": -1, "type": 10002, params: ['sys.float.chip_small_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
        },
        fillColor: { "id": -1, "type": 10001, params: ['sys.color.chip_usually_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        activatedFillColor: { "id": -1, "type": 10001, params: ['sys.color.chip_active_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        focusFillColor: { "id": -1, "type": 10001, params: ['sys.color.chip_icon_focus_fill'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        focusActivatedColor: { "id": -1, "type": 10001, params: ['sys.color.chip_icon_focus_activated'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        defaultDeleteIcon: { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_cancel', 16, 16], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        focusable: false,
    },
    defaultSymbol: {
        normalFontColor: [{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }],
        activatedFontColor: [{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }],
        normalFontSize: { "id": -1, "type": 10002, params: ['sys.float.chip_normal_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        smallFontSize: { "id": -1, "type": 10002, params: ['sys.float.chip_small_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        defaultEffect: -1,
    },
    chipNode: {
        suitAgeScale: 1.75,
        minLabelWidth: 12,
        normalHeight: { "id": -1, "type": 10002, params: ['sys.float.chip_normal_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        smallHeight: { "id": -1, "type": 10002, params: ['sys.float.chip_small_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        enabled: true,
        activated: false,
        backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.chip_background_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        activatedBackgroundColor: { "id": -1, "type": 10001, params: ['sys.color.chip_activated_background_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        focusOutlineColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        borderColor: { "id": -1, "type": 10001, params: ['sys.color.chip_border_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        defaultBorderWidth: { "id": -1, "type": 10002, params: ['sys.float.chip_border_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        activatedBorderColor: { "id": -1, "type": 10001, params: ['sys.color.chip_activated_border_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        normalBorderRadius: { "id": -1, "type": 10002, params: ['sys.float.chip_normal_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        smallBorderRadius: { "id": -1, "type": 10002, params: ['sys.float.chip_small_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        borderWidth: 2,
        focusBtnScaleX: { "id": -1, "type": 10002, params: ['sys.float.chip_focused_btn_scale'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        focusBtnScaleY: { "id": -1, "type": 10002, params: ['sys.float.chip_focused_btn_scale'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        localizedNormalPadding: {
            start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.chip_normal_text_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.chip_normal_text_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            top: LengthMetrics.vp(4),
            bottom: LengthMetrics.vp(4)
        },
        localizedSmallPadding: {
            start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.chip_small_text_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.chip_small_text_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            top: LengthMetrics.vp(4),
            bottom: LengthMetrics.vp(4)
        },
        hoverBlendColor: { "id": -1, "type": 10001, params: ['sys.color.chip_hover_fg'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        pressedBlendColor: { "id": -1, "type": 10001, params: ['sys.color.chip_press_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        focusBgColor: { "id": -1, "type": 10001, params: ['sys.color.chip_focus_bg'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        focusActivatedBgColor: { "id": -1, "type": 10001, params: ['sys.color.chip_focus_activated_bg'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        opacity: { normal: 1, hover: 0.95, pressed: 0.9, disabled: 0.4 },
        normalShadowStyle: { "id": -1, "type": 10002, params: ['sys.float.chip_normal_shadow_style'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        smallShadowStyle: { "id": -1, "type": 10002, params: ['sys.float.chip_small_shadow_style'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
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
export function Chip(options, parent = null) {
    const __options__ = options;
    {
        (parent ? parent : this).observeComponentCreation2((elmtId, isInitialRender, options = __options__) => {
            if (isInitialRender) {
                let componentCall = new ChipComponent(parent ? parent : this, {
                    chipSize: options.size,
                    prefixIcon: options.prefixIcon,
                    prefixSymbol: options.prefixSymbol,
                    label: options.label,
                    suffixIcon: options.suffixIcon,
                    suffixSymbol: options.suffixSymbol,
                    allowClose: options.allowClose,
                    chipEnabled: options.enabled,
                    chipActivated: options.activated,
                    chipNodeBackgroundColor: options.backgroundColor,
                    chipNodeActivatedBackgroundColor: options.activatedBackgroundColor,
                    chipNodeRadius: options.borderRadius,
                    chipDirection: options.direction,
                    onClose: options.onClose,
                    onClicked: options.onClicked,
                }, undefined, elmtId, () => { }, { page: "passwordLibrary/src/main/ets/components/mainpage/chip.ets", line: 305, col: 3 });
                ViewPU.create(componentCall);
                let paramsLambda = () => {
                    return {
                        chipSize: options.size,
                        prefixIcon: options.prefixIcon,
                        prefixSymbol: options.prefixSymbol,
                        label: options.label,
                        suffixIcon: options.suffixIcon,
                        suffixSymbol: options.suffixSymbol,
                        allowClose: options.allowClose,
                        chipEnabled: options.enabled,
                        chipActivated: options.activated,
                        chipNodeBackgroundColor: options.backgroundColor,
                        chipNodeActivatedBackgroundColor: options.activatedBackgroundColor,
                        chipNodeRadius: options.borderRadius,
                        chipDirection: options.direction,
                        onClose: options.onClose,
                        onClicked: options.onClicked
                    };
                };
                componentCall.paramsGenerator_ = paramsLambda;
            }
            else {
                (parent ? parent : this).updateStateVarsOfChildByElmtId(elmtId, {
                    chipSize: options.size,
                    prefixIcon: options.prefixIcon,
                    prefixSymbol: options.prefixSymbol,
                    label: options.label,
                    suffixIcon: options.suffixIcon,
                    suffixSymbol: options.suffixSymbol,
                    allowClose: options.allowClose,
                    chipEnabled: options.enabled,
                    chipActivated: options.activated,
                    chipNodeBackgroundColor: options.backgroundColor,
                    chipNodeActivatedBackgroundColor: options.activatedBackgroundColor,
                    chipNodeRadius: options.borderRadius,
                    chipDirection: options.direction
                });
            }
        }, { name: "ChipComponent" });
    }
}
export class ChipComponent extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.theme = defaultTheme;
        this.__chipSize = new SynchedPropertyObjectOneWayPU(params.chipSize, this, "chipSize");
        this.__allowClose = new SynchedPropertySimpleOneWayPU(params.allowClose, this, "allowClose");
        this.__chipDirection = new SynchedPropertySimpleOneWayPU(params.chipDirection, this, "chipDirection");
        this.__prefixIcon = new SynchedPropertyObjectOneWayPU(params.prefixIcon, this, "prefixIcon");
        this.__prefixSymbol = new SynchedPropertyObjectOneWayPU(params.prefixSymbol, this, "prefixSymbol");
        this.__label = new SynchedPropertyObjectOneWayPU(params.label, this, "label");
        this.__suffixIcon = new SynchedPropertyObjectOneWayPU(params.suffixIcon, this, "suffixIcon");
        this.__suffixSymbol = new SynchedPropertyObjectOneWayPU(params.suffixSymbol, this, "suffixSymbol");
        this.__chipNodeBackgroundColor = new SynchedPropertyObjectOneWayPU(params.chipNodeBackgroundColor, this, "chipNodeBackgroundColor");
        this.__isSetBg = new ObservedPropertySimplePU(false, this, "isSetBg");
        this.__chipNodeActivatedBackgroundColor = new SynchedPropertyObjectOneWayPU(params.chipNodeActivatedBackgroundColor, this, "chipNodeActivatedBackgroundColor");
        this.__isSetActiveBg = new ObservedPropertySimplePU(false, this, "isSetActiveBg");
        this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(params.chipNodeRadius, this, "chipNodeRadius");
        this.__chipEnabled = new SynchedPropertySimpleOneWayPU(params.chipEnabled, this, "chipEnabled");
        this.__chipActivated = new SynchedPropertySimpleOneWayPU(params.chipActivated, this, "chipActivated");
        this.__isHover = new ObservedPropertySimplePU(false, this, "isHover");
        this.__isHovering = new ObservedPropertySimplePU(false, this, "isHovering");
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
            onConfigurationUpdated: (configuration) => {
                this.fontSizeScale = configuration.fontSizeScale;
                this.fontWeightScale = configuration.fontWeightScale;
            }, onMemoryLevel() {
            }
        };
        this.callbackId = undefined;
        this.__prefixSymbolWidth = new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById('PrefixSymbolGlyph')?.size?.width), this, "prefixSymbolWidth");
        this.__suffixSymbolWidth = new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById('SuffixSymbolGlyph')?.size?.width), this, "suffixSymbolWidth");
        this.__allowCloseSymbolWidth = new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById('AllowCloseSymbolGlyph')?.size?.width), this, "allowCloseSymbolWidth");
        this.__symbolEffect = new ObservedPropertyObjectPU(new SymbolEffect(), this, "symbolEffect");
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
        if (params.allowClose === undefined) {
            this.__allowClose.set(true);
        }
        if (params.chipDirection === undefined) {
            this.__chipDirection.set(Direction.Auto);
        }
        if (params.prefixIcon === undefined) {
            this.__prefixIcon.set({ src: "" });
        }
        if (params.label === undefined) {
            this.__label.set({ text: "" });
        }
        if (params.suffixIcon === undefined) {
            this.__suffixIcon.set({ src: "" });
        }
        if (params.isSetBg !== undefined) {
            this.isSetBg = params.isSetBg;
        }
        if (params.isSetActiveBg !== undefined) {
            this.isSetActiveBg = params.isSetActiveBg;
        }
        if (params.chipNodeRadius === undefined) {
            this.__chipNodeRadius.set(void (0));
        }
        if (params.chipEnabled === undefined) {
            this.__chipEnabled.set(true);
        }
        if (params.chipActivated === undefined) {
            this.__chipActivated.set(false);
        }
        if (params.isHover !== undefined) {
            this.isHover = params.isHover;
        }
        if (params.isHovering !== undefined) {
            this.isHovering = params.isHovering;
        }
        if (params.chipScale !== undefined) {
            this.chipScale = params.chipScale;
        }
        if (params.chipOpacity !== undefined) {
            this.chipOpacity = params.chipOpacity;
        }
        if (params.chipBlendColor !== undefined) {
            this.chipBlendColor = params.chipBlendColor;
        }
        if (params.deleteChip !== undefined) {
            this.deleteChip = params.deleteChip;
        }
        if (params.chipNodeOnFocus !== undefined) {
            this.chipNodeOnFocus = params.chipNodeOnFocus;
        }
        if (params.useDefaultSuffixIcon !== undefined) {
            this.useDefaultSuffixIcon = params.useDefaultSuffixIcon;
        }
        if (params.chipNodeSize !== undefined) {
            this.chipNodeSize = params.chipNodeSize;
        }
        if (params.onClose !== undefined) {
            this.onClose = params.onClose;
        }
        if (params.onClicked !== undefined) {
            this.onClicked = params.onClicked;
        }
        if (params.suffixIconOnFocus !== undefined) {
            this.suffixIconOnFocus = params.suffixIconOnFocus;
        }
        if (params.chipBreakPoints !== undefined) {
            this.chipBreakPoints = params.chipBreakPoints;
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
        if (params.isShowPressedBackGroundColor !== undefined) {
            this.isShowPressedBackGroundColor = params.isShowPressedBackGroundColor;
        }
        if (params.fontSizeScale !== undefined) {
            this.fontSizeScale = params.fontSizeScale;
        }
        if (params.fontWeightScale !== undefined) {
            this.fontWeightScale = params.fontWeightScale;
        }
        if (params.callbacks !== undefined) {
            this.callbacks = params.callbacks;
        }
        if (params.callbackId !== undefined) {
            this.callbackId = params.callbackId;
        }
        if (params.prefixSymbolWidth !== undefined) {
            this.prefixSymbolWidth = params.prefixSymbolWidth;
        }
        if (params.suffixSymbolWidth !== undefined) {
            this.suffixSymbolWidth = params.suffixSymbolWidth;
        }
        if (params.allowCloseSymbolWidth !== undefined) {
            this.allowCloseSymbolWidth = params.allowCloseSymbolWidth;
        }
        if (params.symbolEffect !== undefined) {
            this.symbolEffect = params.symbolEffect;
        }
    }
    updateStateVars(params) {
        this.__chipSize.reset(params.chipSize);
        this.__allowClose.reset(params.allowClose);
        this.__chipDirection.reset(params.chipDirection);
        this.__prefixIcon.reset(params.prefixIcon);
        this.__prefixSymbol.reset(params.prefixSymbol);
        this.__label.reset(params.label);
        this.__suffixIcon.reset(params.suffixIcon);
        this.__suffixSymbol.reset(params.suffixSymbol);
        this.__chipNodeBackgroundColor.reset(params.chipNodeBackgroundColor);
        this.__chipNodeActivatedBackgroundColor.reset(params.chipNodeActivatedBackgroundColor);
        this.__chipNodeRadius.reset(params.chipNodeRadius);
        this.__chipEnabled.reset(params.chipEnabled);
        this.__chipActivated.reset(params.chipActivated);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__chipSize.purgeDependencyOnElmtId(rmElmtId);
        this.__allowClose.purgeDependencyOnElmtId(rmElmtId);
        this.__chipDirection.purgeDependencyOnElmtId(rmElmtId);
        this.__prefixIcon.purgeDependencyOnElmtId(rmElmtId);
        this.__prefixSymbol.purgeDependencyOnElmtId(rmElmtId);
        this.__label.purgeDependencyOnElmtId(rmElmtId);
        this.__suffixIcon.purgeDependencyOnElmtId(rmElmtId);
        this.__suffixSymbol.purgeDependencyOnElmtId(rmElmtId);
        this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(rmElmtId);
        this.__isSetBg.purgeDependencyOnElmtId(rmElmtId);
        this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(rmElmtId);
        this.__isSetActiveBg.purgeDependencyOnElmtId(rmElmtId);
        this.__chipNodeRadius.purgeDependencyOnElmtId(rmElmtId);
        this.__chipEnabled.purgeDependencyOnElmtId(rmElmtId);
        this.__chipActivated.purgeDependencyOnElmtId(rmElmtId);
        this.__isHover.purgeDependencyOnElmtId(rmElmtId);
        this.__isHovering.purgeDependencyOnElmtId(rmElmtId);
        this.__chipScale.purgeDependencyOnElmtId(rmElmtId);
        this.__chipOpacity.purgeDependencyOnElmtId(rmElmtId);
        this.__chipBlendColor.purgeDependencyOnElmtId(rmElmtId);
        this.__deleteChip.purgeDependencyOnElmtId(rmElmtId);
        this.__chipNodeOnFocus.purgeDependencyOnElmtId(rmElmtId);
        this.__useDefaultSuffixIcon.purgeDependencyOnElmtId(rmElmtId);
        this.__suffixIconOnFocus.purgeDependencyOnElmtId(rmElmtId);
        this.__chipBreakPoints.purgeDependencyOnElmtId(rmElmtId);
        this.__isShowPressedBackGroundColor.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
        this.__fontWeightScale.purgeDependencyOnElmtId(rmElmtId);
        this.__prefixSymbolWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__suffixSymbolWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__allowCloseSymbolWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__symbolEffect.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__chipSize.aboutToBeDeleted();
        this.__allowClose.aboutToBeDeleted();
        this.__chipDirection.aboutToBeDeleted();
        this.__prefixIcon.aboutToBeDeleted();
        this.__prefixSymbol.aboutToBeDeleted();
        this.__label.aboutToBeDeleted();
        this.__suffixIcon.aboutToBeDeleted();
        this.__suffixSymbol.aboutToBeDeleted();
        this.__chipNodeBackgroundColor.aboutToBeDeleted();
        this.__isSetBg.aboutToBeDeleted();
        this.__chipNodeActivatedBackgroundColor.aboutToBeDeleted();
        this.__isSetActiveBg.aboutToBeDeleted();
        this.__chipNodeRadius.aboutToBeDeleted();
        this.__chipEnabled.aboutToBeDeleted();
        this.__chipActivated.aboutToBeDeleted();
        this.__isHover.aboutToBeDeleted();
        this.__isHovering.aboutToBeDeleted();
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
    set chipSize(newValue) {
        this.__chipSize.set(newValue);
    }
    get allowClose() {
        return this.__allowClose.get();
    }
    set allowClose(newValue) {
        this.__allowClose.set(newValue);
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
    get chipNodeBackgroundColor() {
        return this.__chipNodeBackgroundColor.get();
    }
    set chipNodeBackgroundColor(newValue) {
        this.__chipNodeBackgroundColor.set(newValue);
    }
    get isSetBg() {
        return this.__isSetBg.get();
    }
    set isSetBg(newValue) {
        this.__isSetBg.set(newValue);
    }
    get chipNodeActivatedBackgroundColor() {
        return this.__chipNodeActivatedBackgroundColor.get();
    }
    set chipNodeActivatedBackgroundColor(newValue) {
        this.__chipNodeActivatedBackgroundColor.set(newValue);
    }
    get isSetActiveBg() {
        return this.__isSetActiveBg.get();
    }
    set isSetActiveBg(newValue) {
        this.__isSetActiveBg.set(newValue);
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
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(newValue) {
        this.__isHover.set(newValue);
    }
    get isHovering() {
        return this.__isHovering.get();
    }
    set isHovering(newValue) {
        this.__isHovering.set(newValue);
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
    get chipBlendColor() {
        return this.__chipBlendColor.get();
    }
    set chipBlendColor(newValue) {
        this.__chipBlendColor.set(newValue);
    }
    get deleteChip() {
        return this.__deleteChip.get();
    }
    set deleteChip(newValue) {
        this.__deleteChip.set(newValue);
    }
    get chipNodeOnFocus() {
        return this.__chipNodeOnFocus.get();
    }
    set chipNodeOnFocus(newValue) {
        this.__chipNodeOnFocus.set(newValue);
    }
    get useDefaultSuffixIcon() {
        return this.__useDefaultSuffixIcon.get();
    }
    set useDefaultSuffixIcon(newValue) {
        this.__useDefaultSuffixIcon.set(newValue);
    }
    get suffixIconOnFocus() {
        return this.__suffixIconOnFocus.get();
    }
    set suffixIconOnFocus(newValue) {
        this.__suffixIconOnFocus.set(newValue);
    }
    get chipBreakPoints() {
        return this.__chipBreakPoints.get();
    }
    set chipBreakPoints(newValue) {
        this.__chipBreakPoints.set(newValue);
    }
    get isShowPressedBackGroundColor() {
        return this.__isShowPressedBackGroundColor.get();
    }
    set isShowPressedBackGroundColor(newValue) {
        this.__isShowPressedBackGroundColor.set(newValue);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }
    get fontWeightScale() {
        return this.__fontWeightScale.get();
    }
    set fontWeightScale(newValue) {
        this.__fontWeightScale.set(newValue);
    }
    get prefixSymbolWidth() {
        return this.__prefixSymbolWidth.get();
    }
    set prefixSymbolWidth(newValue) {
        this.__prefixSymbolWidth.set(newValue);
    }
    get suffixSymbolWidth() {
        return this.__suffixSymbolWidth.get();
    }
    set suffixSymbolWidth(newValue) {
        this.__suffixSymbolWidth.set(newValue);
    }
    get allowCloseSymbolWidth() {
        return this.__allowCloseSymbolWidth.get();
    }
    set allowCloseSymbolWidth(newValue) {
        this.__allowCloseSymbolWidth.set(newValue);
    }
    get symbolEffect() {
        return this.__symbolEffect.get();
    }
    set symbolEffect(newValue) {
        this.__symbolEffect.set(newValue);
    }
    isChipSizeEnum() {
        return typeof (this.chipSize) === 'string';
    }
    getLabelFontSize() {
        if (this.label?.fontSize !== void (0) && this.toVp(this.label.fontSize) >= 0) {
            return this.label.fontSize;
        }
        let size = this.theme.label.smallFontSize;
        let defaultSize = this.theme.label.defaultFontSize;
        if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
            return this.verifyResource(size, defaultSize);
        }
        else {
            size = this.theme.label.normalFontSize;
            return this.verifyResource(size, defaultSize);
        }
    }
    getIconSize() {
        if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
            return this.theme.prefixIcon.smallSize.width;
        }
        else {
            return this.theme.prefixIcon.normalSize.width;
        }
    }
    defaultSymbolFontsize() {
        if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
            return this.theme.defaultSymbol.smallFontSize;
        }
        else {
            return this.theme.defaultSymbol.normalFontSize;
        }
    }
    sizeToVp(sizeResource) {
        let metrics = LengthMetrics.resource(sizeResource);
        return this.lengthMetricsToVp(metrics);
    }
    verifyResource(resourceValue, defaultValue) {
        if (resourceValue && resourceValue.params && Array.isArray(resourceValue.params) &&
        resourceValue.params[0] && resourceValue.params[0].includes('.') &&
            resourceValue.params[0].split('.').length > 2) {
            try {
                let getNum = resourceFn.getNumberByName((resourceValue.params[0]).split('.')[2]);
                return getNum;
            }
            catch (error) {
                return defaultValue;
            }
        }
        return defaultValue;
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
        return FontWeight.Regular;
    }
    lengthMetricsToVp(lengthMetrics) {
        let defaultValue = 0;
        if (lengthMetrics) {
            switch (lengthMetrics.unit) {
                case LengthUnit.PX:
                    return px2vp(lengthMetrics.value);
                case LengthUnit.VP:
                    return lengthMetrics.value;
                case LengthUnit.FP:
                    px2vp(fp2px(lengthMetrics.value));
                    break;
                case LengthUnit.PERCENT:
                    return Number.NEGATIVE_INFINITY;
                case LengthUnit.LPX:
                    return px2vp(lpx2px(lengthMetrics.value));
            }
        }
        return defaultValue;
    }
    toVp(value) {
        if (value === void (0)) {
            return Number.NEGATIVE_INFINITY;
        }
        switch (typeof (value)) {
            case 'number':
                return value;
            case 'object':
                try {
                    return this.lengthMetricsToVp(LengthMetrics.resource(value));
                }
                catch (error) {
                    return Number.NEGATIVE_INFINITY;
                }
            case 'string':
                let regex = new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i");
                let matches = value.match(regex);
                if (!matches) {
                    return Number.NEGATIVE_INFINITY;
                }
                let length = Number(matches?.[1] ?? 0);
                let unit = matches?.[2] ?? 'vp';
                switch (unit.toLowerCase()) {
                    case 'px':
                        length = px2vp(length);
                        break;
                    case 'fp':
                        length = px2vp(fp2px(length));
                        break;
                    case 'lpx':
                        length = px2vp(lpx2px(length));
                        break;
                    case '%':
                        length = Number.NEGATIVE_INFINITY;
                        break;
                    case 'vp':
                        break;
                    default:
                        break;
                }
                return length;
            default:
                return Number.NEGATIVE_INFINITY;
        }
    }
    getChipNodeBorderWidth() {
        if (!this.isSetBackgroundColor()) {
            return this.sizeToVp(this.theme.chipNode.defaultBorderWidth);
        }
        else {
            return 0;
        }
    }
    getChipNodeBorderColor() {
        let themeChipNode = this.theme.chipNode;
        if (this.getChipActive()) {
            return themeChipNode.activatedBorderColor;
        }
        else {
            return themeChipNode.borderColor;
        }
    }
    getLabelMargin() {
        let labelMargin = { left: 0, right: 0 };
        if (this.label?.labelMargin?.left !== void (0) && this.toVp(this.label.labelMargin.left) >= 0) {
            labelMargin.left = this.label?.labelMargin?.left;
        }
        else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                labelMargin.left = this.theme.label.smallMargin.left;
            }
            else {
                labelMargin.left = this.theme.label.normalMargin.left;
            }
        }
        if (this.label?.labelMargin?.right !== void (0) && this.toVp(this.label.labelMargin.right) >= 0) {
            labelMargin.right = this.label?.labelMargin?.right;
        }
        else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
            this.suffixIcon?.src || this.useDefaultSuffixIcon) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                labelMargin.right = this.theme.label.smallMargin.right;
            }
            else {
                labelMargin.right = this.theme.label.normalMargin.right;
            }
        }
        return labelMargin;
    }
    getLocalizedLabelMargin() {
        let localizedLabelMargin = { start: LengthMetrics.vp(0), end: LengthMetrics.vp(0) };
        if (this.label?.localizedLabelMargin?.start?.value !== void (0) &&
            this.lengthMetricsToVp(this.label.localizedLabelMargin.start) >= 0) {
            localizedLabelMargin.start = this.label?.localizedLabelMargin?.start;
        }
        else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                localizedLabelMargin.start = this.theme.label.localizedSmallMargin.start;
            }
            else {
                localizedLabelMargin.start = this.theme.label.localizedNormalMargin.start;
            }
        }
        if (this.label?.localizedLabelMargin?.end?.value !== void (0) &&
            this.lengthMetricsToVp(this.label.localizedLabelMargin.end) >= 0) {
            localizedLabelMargin.end = this.label?.localizedLabelMargin?.end;
        }
        else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
            this.suffixIcon?.src || this.useDefaultSuffixIcon) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                localizedLabelMargin.end = this.theme.label.localizedSmallMargin.end;
            }
            else {
                localizedLabelMargin.end = this.theme.label.localizedNormalMargin.end;
            }
        }
        return localizedLabelMargin;
    }
    getLabelStartEndVp() {
        let labelMargin = this.getLocalizedLabelMargin();
        if (this.label && (this.label.labelMargin !== void (0)) && (this.label.localizedLabelMargin === void (0))) {
            let margin = this.getLabelMargin();
            return {
                start: LengthMetrics.vp(this.toVp(margin.left)),
                end: LengthMetrics.vp(this.toVp(margin.right))
            };
        }
        return {
            start: LengthMetrics.vp(this.lengthMetricsToVp(labelMargin.start)),
            end: LengthMetrics.vp(this.lengthMetricsToVp(labelMargin.end))
        };
    }
    getActualLabelMargin() {
        let localizedLabelMargin = this.getLocalizedLabelMargin();
        if (this.label && this.label.localizedLabelMargin !== void (0)) {
            return localizedLabelMargin;
        }
        if (this.label && this.label.labelMargin !== void (0)) {
            return this.getLabelMargin();
        }
        return localizedLabelMargin;
    }
    getSuffixIconSize() {
        let suffixIconSize = { width: 0, height: 0 };
        if (this.suffixIcon?.size?.width !== void (0) && this.toVp(this.suffixIcon?.size?.width) >= 0) {
            suffixIconSize.width = this.suffixIcon?.size?.width;
        }
        else {
            suffixIconSize.width = this.getSuffixIconSrc() ?
            this.sizeToVp(this.getIconSize()) : 0;
        }
        if (this.suffixIcon?.size?.height !== void (0) && this.toVp(this.suffixIcon?.size?.height) >= 0) {
            suffixIconSize.height = this.suffixIcon?.size?.height;
        }
        else {
            suffixIconSize.height = this.getSuffixIconSrc() ?
            this.sizeToVp(this.getIconSize()) : 0;
        }
        return suffixIconSize;
    }
    getPrefixIconSize() {
        let prefixIconSize = { width: 0, height: 0 };
        if (this.prefixIcon?.size?.width !== void (0) && this.toVp(this.prefixIcon?.size?.width) >= 0) {
            prefixIconSize.width = this.prefixIcon?.size?.width;
        }
        else {
            if (this.prefixIcon?.src) {
                prefixIconSize.width = this.sizeToVp(this.getIconSize());
            }
            else {
                prefixIconSize.width = 0;
            }
        }
        if (this.prefixIcon?.size?.height !== void (0) && this.toVp(this.prefixIcon?.size?.height) >= 0) {
            prefixIconSize.height = this.prefixIcon?.size?.height;
        }
        else {
            if (this.prefixIcon?.src) {
                prefixIconSize.height = this.getIconSize();
            }
            else {
                prefixIconSize.height = 0;
            }
        }
        return prefixIconSize;
    }
    getActiveIconColor() {
        return this.chipNodeOnFocus ? this.theme.prefixIcon.focusActivatedColor :
        this.theme.prefixIcon.activatedFillColor;
    }
    getFillIconColor(iconType) {
        if (iconType === IconType.PREFIX_ICON) {
            if (this.prefixIcon?.fillColor) {
                return this.prefixIcon.fillColor;
            }
            return this.chipNodeOnFocus ? this.theme.prefixIcon.focusFillColor : this.theme.prefixIcon.fillColor;
        }
        else {
            if (this.suffixIcon?.fillColor) {
                return this.suffixIcon.fillColor;
            }
            return this.chipNodeOnFocus ? this.theme.suffixIcon.focusFillColor : this.theme.suffixIcon.fillColor;
        }
    }
    getActiveIconColorArray(iconType) {
        if (iconType === IconType.PREFIX_ICON) {
            return this.getColorArray(this.prefixIcon?.activatedFillColor, this.theme.prefixIcon.focusActivatedColor, this.theme.prefixIcon.activatedFillColor);
        }
        else {
            return this.getColorArray(this.suffixIcon?.activatedFillColor, this.theme.suffixIcon.focusActivatedColor, this.theme.suffixIcon.activatedFillColor);
        }
    }
    getColorArray(userDefined, focusColor, normalColor) {
        if (userDefined) {
            return [userDefined];
        }
        return this.chipNodeOnFocus ? [focusColor] : [normalColor];
    }
    getFillIconColorArray(iconType) {
        if (iconType === IconType.PREFIX_ICON) {
            return this.getColorArray(this.prefixIcon?.fillColor, this.theme.prefixIcon.focusFillColor, this.theme.prefixIcon.fillColor);
        }
        else {
            return this.getColorArray(this.suffixIcon?.fillColor, this.theme.suffixIcon.focusFillColor, this.theme.suffixIcon.fillColor);
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
    getDefaultSymbolColor(iconType) {
        if (this.getChipActive()) {
            return this.getActiveIconColorArray(iconType);
        }
        return this.getFillIconColorArray(iconType);
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
        return (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) ? this.theme.chipNode.localizedSmallPadding : this.theme.chipNode.localizedNormalPadding;
    }
    getChipNodeRadius() {
        if (this.chipNodeRadius !== void (0) && this.toVp(this.chipNodeRadius) >= 0) {
            return this.chipNodeRadius;
        }
        else {
            return ((this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) ?
            this.sizeToVp(this.theme.chipNode.smallBorderRadius) :
            this.sizeToVp(this.theme.chipNode.normalBorderRadius));
        }
    }
    getChipNodeBackGroundColor() {
        let themeChipNode = this.theme.chipNode;
        let currentColor;
        if (this.chipNodeOnFocus && !this.isSetBackgroundColor()) {
            currentColor = this.getChipActive() ? themeChipNode.focusActivatedBgColor :
            themeChipNode.focusBgColor;
            return currentColor;
        }
        if (this.getChipActive()) {
            currentColor = this.chipNodeActivatedBackgroundColor ?? themeChipNode.activatedBackgroundColor;
        }
        else {
            currentColor = this.chipNodeBackgroundColor ?? themeChipNode.backgroundColor;
        }
        let sourceColor;
        try {
            sourceColor = ColorMetrics.resourceColor(currentColor);
        }
        catch (err) {
            hilog.error(0x3900, 'Ace', `Chip resourceColor, error: ${err.toString()}`);
            sourceColor = ColorMetrics.resourceColor(Color.Transparent);
        }
        if (this.isShowPressedBackGroundColor) {
            this.isHovering = false;
            return sourceColor
                .blendColor(ColorMetrics.resourceColor(this.isSetBackgroundColor() ?
                Color.Transparent : themeChipNode.pressedBlendColor))
                .color;
        }
        if (this.isHovering) {
            return sourceColor
                .blendColor(ColorMetrics.resourceColor(this.isSetBackgroundColor() ?
                Color.Transparent : themeChipNode.hoverBlendColor))
                .color;
        }
        return currentColor;
    }
    getChipNodeHeight() {
        if (this.isChipSizeEnum()) {
            return this.chipSize === ChipSize.SMALL ? this.theme.chipNode.smallHeight : this.theme.chipNode.normalHeight;
        }
        else {
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
        let calWidth = 0;
        let startEndVp = this.getLabelStartEndVp();
        calWidth += this.getChipNodeBorderWidth() * 2;
        calWidth += this.getChipNodePadding().start?.value ?? 0;
        calWidth += this.toVp(this.getPrefixChipWidth());
        calWidth += this.toVp(startEndVp.start?.value ?? 0);
        calWidth += this.getLabelWidth();
        calWidth += this.toVp(startEndVp.end?.value ?? 0);
        calWidth += this.toVp(this.getSuffixChipWidth());
        calWidth += this.getChipNodePadding().end?.value ?? 0;
        return calWidth;
    }
    getPrefixChipWidth() {
        if (this.prefixSymbol?.normal || this.prefixSymbol?.activated) {
            return this.prefixSymbolWidth;
        }
        else if (this.prefixIcon?.src) {
            return this.getPrefixIconSize().width;
        }
        else {
            return 0;
        }
    }
    getSuffixChipWidth() {
        if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
            return this.suffixSymbolWidth;
        }
        else if (this.suffixIcon?.src) {
            return this.getSuffixIconSize().width;
        }
        else if (!this.suffixIcon?.src && (this.allowClose ?? true)) {
            return this.allowCloseSymbolWidth;
        }
        else {
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
        return this.chipActivated;
    }
    getChipNodeOpacity() {
        return this.getChipEnable() ? this.chipOpacity : this.theme.chipNode.opacity.disabled;
    }
    getfocusBox() {
        return this.chipNodeOnFocus ? { strokeWidth: LengthMetrics.vp(2) } : { strokeWidth: LengthMetrics.vp(0) };
    }
    handleTouch(event) {
        if (!this.getChipEnable()) {
            return;
        }
        if (this.isHover) {
            if (event.type === TouchType.Down || event.type === TouchType.Move) {
                this.isShowPressedBackGroundColor = true;
            }
            else if (event.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            }
            else {
                this.isShowPressedBackGroundColor = false;
            }
        }
        else {
            if (event.type === TouchType.Down || event.type === TouchType.Move) {
                this.isShowPressedBackGroundColor = true;
            }
            else if (event.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            }
            else {
                this.isShowPressedBackGroundColor = false;
            }
        }
    }
    hoverAnimate(isHover) {
        if (!this.getChipEnable()) {
            return;
        }
        this.isHover = isHover;
        if (this.isHover) {
            this.isShowPressedBackGroundColor = true;
        }
        else {
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
        let constraintWidth = this.getChipConstraintWidth();
        return Math.min(Math.max(this.getCalculateChipNodeWidth(), constraintWidth.minWidth), constraintWidth.maxWidth);
    }
    getFocusOverlaySize() {
        return {
            width: Math.max(this.getChipNodeWidth(), this.getChipConstraintWidth().minWidth) + 8,
            height: this.getChipNodeHeight() + 8
        };
    }
    getChipConstraintWidth() {
        let calcMinWidth = this.getReserveChipNodeWidth();
        let constraintWidth = this.getCalculateChipNodeWidth();
        let constraintSize;
        switch (this.chipBreakPoints) {
            case BreakPointsType.SM:
                constraintSize = {
                    minWidth: calcMinWidth,
                    maxWidth: Math.min(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointSmMaxWidth)
                };
                break;
            case BreakPointsType.MD:
                constraintSize = {
                    minWidth: Math.max(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointMdMaxWidth)
                };
                break;
            case BreakPointsType.LG:
                constraintSize = {
                    minWidth: Math.max(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointLgMaxWidth)
                };
                break;
            default:
                constraintSize = { minWidth: calcMinWidth, maxWidth: constraintWidth };
                break;
        }
        constraintSize.minWidth = Math.min(Math.max(this.getCalculateChipNodeWidth(), constraintSize.minWidth), constraintSize.maxWidth);
        constraintSize.minHeight = this.getChipNodeHeight();
        if (!this.isChipSizeEnum() && this.chipNodeSize?.height !== void (0) && this.toVp(this.chipNodeSize?.height) >= 0) {
            constraintSize.maxHeight = this.toVp(this.chipNodeSize.height);
            constraintSize.minHeight = this.toVp(this.chipNodeSize.height);
        }
        if (!this.isChipSizeEnum() && this.chipNodeSize?.width !== void (0) && this.toVp(this.chipNodeSize?.width) >= 0) {
            constraintSize.minWidth = this.toVp(this.chipNodeSize.width);
            constraintSize.maxWidth = this.toVp(this.chipNodeSize.width);
        }
        else if (this.toVp(this.fontSizeScale) >= this.theme.chipNode.suitAgeScale) {
            constraintSize.minWidth = void (0);
            constraintSize.maxWidth = void (0);
        }
        return constraintSize;
    }
    focusOverlay(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.direction(this.chipDirection);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.chipNodeOnFocus && !this.suffixIconOnFocus) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.direction(this.chipDirection);
                        Stack.borderRadius(this.toVp(this.getChipNodeRadius()) + 4);
                        Stack.size(this.getFocusOverlaySize());
                        Stack.borderColor(this.theme.chipNode.focusOutlineColor);
                        Stack.borderWidth(this.theme.chipNode.borderWidth);
                    }, Stack);
                    Stack.pop();
                });
            }
            else {
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
        }
        else {
            this.isSetBg = false;
            this.chipNodeBackgroundColor = this.theme.chipNode.backgroundColor;
        }
        if (this.chipNodeActivatedBackgroundColor) {
            this.isSetActiveBg = true;
        }
        else {
            this.isSetActiveBg = false;
            this.chipNodeActivatedBackgroundColor = this.theme.chipNode.activatedBackgroundColor;
        }
        this.smListener.on("change", (mediaQueryResult) => {
            if (mediaQueryResult.matches) {
                this.chipBreakPoints = BreakPointsType.SM;
            }
        });
        this.mdListener.on("change", (mediaQueryResult) => {
            if (mediaQueryResult.matches) {
                this.chipBreakPoints = BreakPointsType.MD;
            }
        });
        this.lgListener.on("change", (mediaQueryResult) => {
            if (mediaQueryResult.matches) {
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
        }
        else {
            return Visibility.None;
        }
    }
    isSetBackgroundColor() {
        return this.isSetBg || (this.isSetActiveBg && this.chipActivated);
    }
    getShadowStyles() {
        if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
            let smallShadow = this.theme.chipNode.smallShadowStyle;
            let smallShadowType = this.verifyResource(smallShadow, -1);
            return smallShadowType;
        }
        else {
            let normalShadow = this.theme.chipNode.normalShadowStyle;
            let normalShadowType = this.verifyResource(normalShadow, -1);
            return normalShadowType;
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
    chipBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild();
            Button.constraintSize(this.getChipConstraintWidth());
            Button.direction(this.chipDirection);
            Button.type(ButtonType.Normal);
            Button.clip(false);
            Button.backgroundColor(this.getChipNodeBackGroundColor());
            Button.borderWidth(this.getChipNodeBorderWidth());
            Button.borderColor(this.getChipNodeBorderColor());
            Button.borderRadius(this.getChipNodeRadius());
            Button.enabled(this.getChipEnable());
            Button.scale(ObservedObject.GetRawObject(this.chipScale));
            Button.focusable(true);
            Button.opacity(this.getChipNodeOpacity());
            Button.focusBox(this.getfocusBox());
            Button.shadow(this.chipNodeOnFocus ? this.getShadowStyles() : undefined);
            Button.onFocus(() => {
                this.focusBtnChipNodeAnimate();
                this.chipNodeOnFocus = true;
            });
            Button.onBlur(() => {
                this.chipNodeOnFocus = false;
                this.blurBtnChipNodeAnimate();
            });
            Button.onTouch((event) => {
                this.handleTouch(event);
            });
            Button.onHover((isHover) => {
                this.isHovering = isHover;
            });
            Button.onKeyEvent((event) => {
                if (!event && event.type !== KeyType.Down) {
                    return;
                }
                let forwardDelChip = event.keyCode === KeyCode.KEYCODE_FORWARD_DEL &&
                    !this.suffixIconOnFocus;
                let enterChip = event.keyCode === KeyCode.KEYCODE_ENTER &&
                this.allowClose && !this.suffixIcon?.src;
                if (forwardDelChip || enterChip) {
                    this.deleteChipNodeAnimate();
                }
            });
            Button.onClick(this.onClicked === noop ? undefined : this.onClicked.bind(this));
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.direction(this.chipDirection);
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.Center);
            Row.padding(this.getChipNodePadding());
            Row.constraintSize(this.getChipConstraintWidth());
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.prefixSymbol?.normal || this.prefixSymbol?.activated) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.defaultSymbolFontsize());
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.PREFIX_ICON));
                        SymbolGlyph.attributeModifier.bind(this)(this.getPrefixSymbolModifier());
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), this.theme.defaultSymbol.defaultEffect);
                        SymbolGlyph.onSizeChange((oldValue, newValue) => {
                            this.prefixSymbolWidth = newValue?.width;
                        });
                        SymbolGlyph.key('PrefixSymbolGlyph');
                    }, SymbolGlyph);
                });
            }
            else if (this.prefixIcon?.src !== "") {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            }
            else {
                this.ifElseBranchUpdateFunction(2, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.defaultSymbolFontsize());
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_ICON));
                        SymbolGlyph.attributeModifier.bind(this)(this.getSuffixSymbolModifier());
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), this.theme.defaultSymbol.defaultEffect);
                        SymbolGlyph.onSizeChange((oldValue, newValue) => {
                            this.suffixSymbolWidth = newValue?.width;
                        });
                        SymbolGlyph.key('SuffixSymbolGlyph');
                    }, SymbolGlyph);
                });
            }
            else if (this.suffixIcon?.src !== "") {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        Image.onClick(() => {
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
                    }, Image);
                });
            }
            else if (this.allowClose ?? true) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create({ "id": -1, "type": 40000, params: ['sys.symbol.xmark'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        SymbolGlyph.fontSize(this.defaultSymbolFontsize());
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_ICON));
                        SymbolGlyph.onSizeChange((oldValue, newValue) => {
                            this.allowCloseSymbolWidth = newValue?.width;
                        });
                        SymbolGlyph.key('AllowCloseSymbolGlyph');
                        SymbolGlyph.onClick(() => {
                            if (!this.getChipEnable()) {
                                return;
                            }
                            this.onClose();
                            this.deleteChipNodeAnimate();
                        });
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(3, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
        Button.pop();
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (!this.deleteChip) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.chipBuilder.bind(this)();
                });
            }
            else {
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
    Chip, ChipSize
}