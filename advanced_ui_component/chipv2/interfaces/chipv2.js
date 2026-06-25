/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        r = Reflect.decorate(decorators, target, key, desc);
    else
        for (var i = decorators.length - 1; i >= 0; i--)
            if (d = decorators[i])
                r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const mediaquery = requireNapi('mediaquery');
const deviceInfo = requireNapi('deviceInfo');
export var ChipV2Size;
(function (ChipV2Size) {
    ChipV2Size["NORMAL"] = "NORMAL";
    ChipV2Size["SMALL"] = "SMALL";
})(ChipV2Size || (ChipV2Size = {}));
var IconType;
(function (IconType) {
    IconType["PREFIX_ICON"] = "PREFIXICON";
    IconType["SUFFIX_ICON"] = "SUFFIXICON";
    IconType["PREFIX_SYMBOL"] = "PREFIXSYMBOL";
    IconType["SUFFIX_SYMBOL"] = "SUFFIXSYMBOL";
})(IconType || (IconType = {}));
var BreakPointsType;
(function (BreakPointsType) {
    BreakPointsType["SM"] = "SM";
    BreakPointsType["MD"] = "MD";
    BreakPointsType["LG"] = "LG";
})(BreakPointsType || (BreakPointsType = {}));
export var ChipV2AccessibilitySelectedType;
(function (ChipV2AccessibilitySelectedType) {
    ChipV2AccessibilitySelectedType[ChipV2AccessibilitySelectedType["CLICKED"] = 0] = "CLICKED";
    ChipV2AccessibilitySelectedType[ChipV2AccessibilitySelectedType["CHECKED"] = 1] = "CHECKED";
    ChipV2AccessibilitySelectedType[ChipV2AccessibilitySelectedType["SELECTED"] = 2] = "SELECTED";
})(ChipV2AccessibilitySelectedType || (ChipV2AccessibilitySelectedType = {}));
let ChipV2Icon = class ChipV2Icon {
    constructor() { }
};
ChipV2Icon = __decorate([
    ObservedV2
], ChipV2Icon);
export { ChipV2Icon };
let ChipV2ImageIcon = class ChipV2ImageIcon extends ChipV2Icon {
    constructor(config) {
        super();
        this.src = config.src;
        this.size = config.size;
        this.fillColor = config.fillColor;
        this.activatedFillColor = config.activatedFillColor;
        this.modifier = config.modifier;
    }
};
__decorate([
    Trace
], ChipV2ImageIcon.prototype, "src", void 0);
__decorate([
    Trace
], ChipV2ImageIcon.prototype, "size", void 0);
__decorate([
    Trace
], ChipV2ImageIcon.prototype, "fillColor", void 0);
__decorate([
    Trace
], ChipV2ImageIcon.prototype, "activatedFillColor", void 0);
__decorate([
    Trace
], ChipV2ImageIcon.prototype, "modifier", void 0);
ChipV2ImageIcon = __decorate([
    ObservedV2
], ChipV2ImageIcon);
export { ChipV2ImageIcon };
let ChipV2SuffixImageIcon = class ChipV2SuffixImageIcon extends ChipV2ImageIcon {
    constructor(config) {
        super(config);
        this.accessibilityLevel = config.accessibilityLevel;
        this.accessibilityText = config.accessibilityText;
        this.accessibilityDescription = config.accessibilityDescription;
        this.action = config.action;
    }
};
__decorate([
    Trace
], ChipV2SuffixImageIcon.prototype, "accessibilityLevel", void 0);
__decorate([
    Trace
], ChipV2SuffixImageIcon.prototype, "accessibilityText", void 0);
__decorate([
    Trace
], ChipV2SuffixImageIcon.prototype, "accessibilityDescription", void 0);
__decorate([
    Trace
], ChipV2SuffixImageIcon.prototype, "action", void 0);
ChipV2SuffixImageIcon = __decorate([
    ObservedV2
], ChipV2SuffixImageIcon);
export { ChipV2SuffixImageIcon };
let ChipV2PrefixImageIcon = class ChipV2PrefixImageIcon extends ChipV2ImageIcon {
    constructor(config) {
        super(config);
    }
};
ChipV2PrefixImageIcon = __decorate([
    ObservedV2
], ChipV2PrefixImageIcon);
export { ChipV2PrefixImageIcon };
let ChipV2Accessibility = class ChipV2Accessibility {
    constructor(config) {
        this.accessibilityLevel = config.accessibilityLevel;
        this.accessibilityText = config.accessibilityText;
        this.accessibilityDescription = config.accessibilityDescription;
    }
};
__decorate([
    Trace
], ChipV2Accessibility.prototype, "accessibilityLevel", void 0);
__decorate([
    Trace
], ChipV2Accessibility.prototype, "accessibilityText", void 0);
__decorate([
    Trace
], ChipV2Accessibility.prototype, "accessibilityDescription", void 0);
ChipV2Accessibility = __decorate([
    ObservedV2
], ChipV2Accessibility);
export { ChipV2Accessibility };
let ChipV2CloseIcon = class ChipV2CloseIcon extends ChipV2Accessibility {
    constructor(config) {
        super(config);
        this.fontSize = config.fontSize;
    }
};
__decorate([
    Trace
], ChipV2CloseIcon.prototype, "fontSize", void 0);
ChipV2CloseIcon = __decorate([
    ObservedV2
], ChipV2CloseIcon);
export { ChipV2CloseIcon };
let ChipV2SymbolIcon = class ChipV2SymbolIcon extends ChipV2Icon {
    constructor(config) {
        super();
        this.normal = config.normal;
        this.activated = config.activated;
    }
};
__decorate([
    Trace
], ChipV2SymbolIcon.prototype, "normal", void 0);
__decorate([
    Trace
], ChipV2SymbolIcon.prototype, "activated", void 0);
ChipV2SymbolIcon = __decorate([
    ObservedV2
], ChipV2SymbolIcon);
export { ChipV2SymbolIcon };
let ChipV2PrefixSymbolIcon = class ChipV2PrefixSymbolIcon extends ChipV2SymbolIcon {
    constructor(config) {
        super(config);
    }
};
ChipV2PrefixSymbolIcon = __decorate([
    ObservedV2
], ChipV2PrefixSymbolIcon);
export { ChipV2PrefixSymbolIcon };
let ChipV2SuffixSymbolIcon = class ChipV2SuffixSymbolIcon extends ChipV2SymbolIcon {
    constructor(config) {
        super(config);
        this.normalAccessibility =
            config.normalAccessibility ? new ChipV2Accessibility(config.normalAccessibility) : undefined;
        this.activatedAccessibility =
            config.activatedAccessibility ? new ChipV2Accessibility(config.activatedAccessibility) : undefined;
        this.action = config.action;
    }
};
__decorate([
    Trace
], ChipV2SuffixSymbolIcon.prototype, "normalAccessibility", void 0);
__decorate([
    Trace
], ChipV2SuffixSymbolIcon.prototype, "activatedAccessibility", void 0);
__decorate([
    Trace
], ChipV2SuffixSymbolIcon.prototype, "action", void 0);
ChipV2SuffixSymbolIcon = __decorate([
    ObservedV2
], ChipV2SuffixSymbolIcon);
export { ChipV2SuffixSymbolIcon };
let ChipV2Label = class ChipV2Label {
    constructor(config) {
        this.text = config.text;
        this.fontSize = config.fontSize;
        this.fontColor = config.fontColor;
        this.activatedFontColor = config.activatedFontColor;
        this.fontFamily = config.fontFamily;
        this.labelMargin = config.labelMargin;
        this.localizedLabelMargin = config.localizedLabelMargin;
        this.modifier = config.modifier;
    }
};
__decorate([
    Trace
], ChipV2Label.prototype, "text", void 0);
__decorate([
    Trace
], ChipV2Label.prototype, "fontSize", void 0);
__decorate([
    Trace
], ChipV2Label.prototype, "fontColor", void 0);
__decorate([
    Trace
], ChipV2Label.prototype, "activatedFontColor", void 0);
__decorate([
    Trace
], ChipV2Label.prototype, "fontFamily", void 0);
__decorate([
    Trace
], ChipV2Label.prototype, "labelMargin", void 0);
__decorate([
    Trace
], ChipV2Label.prototype, "localizedLabelMargin", void 0);
__decorate([
    Trace
], ChipV2Label.prototype, "modifier", void 0);
ChipV2Label = __decorate([
    ObservedV2
], ChipV2Label);
export { ChipV2Label };
const RESOURCE_TYPE_STRING = 10003;
const RESOURCE_TYPE_FLOAT = 10002;
const RESOURCE_TYPE_INTEGER = 10007;
const HOT_SPOT_MIN_HEIGHT = 32;
class LengthMetricsUtils {
    constructor() {
    }
    static getInstance() {
        if (!LengthMetricsUtils.instance) {
            LengthMetricsUtils.instance = new LengthMetricsUtils();
        }
        return LengthMetricsUtils.instance;
    }
    isNaturalNumber(metrics) {
        return metrics.value >= 0;
    }
}
class LengthMetricsCache {
    static get(key, defaultValue) {
        if (LengthMetricsCache._cache.has(key)) {
            return LengthMetricsCache._cache.get(key);
        }
        try {
            const res = {
                id: -1,
                type: 10002,
                params: [key],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
            };
            const metrics = LengthMetrics.resource(res);
            LengthMetricsCache._cache.set(key, metrics);
            return metrics;
        }
        catch (error) {
            return defaultValue;
        }
    }
}
LengthMetricsCache._cache = new Map();
let ChipV2Options = class ChipV2Options {
    constructor(config) {
        this.label = config.label;
        this.prefixIcon = config.prefixIcon;
        this.suffixIcon = config.suffixIcon;
        this.allowClose = config.allowClose;
        this.closeIcon = config.closeIcon;
        this.enabled = config.enabled ?? true;
        this.activated = config.activated;
        this.backgroundColor = config.backgroundColor;
        this.activatedBackgroundColor = config.activatedBackgroundColor;
        this.borderRadius = config.borderRadius;
        this.size = config.size ?? ChipV2Size.NORMAL;
        this.direction = config.direction ?? Direction.Auto;
        this.accessibilityDescription = config.accessibilityDescription;
        this.accessibilityLevel = config.accessibilityLevel;
        this.accessibilitySelectedType = config.accessibilitySelectedType;
        this.maxFontScale = config.maxFontScale;
        this.minFontScale = config.minFontScale;
        this.padding = config.padding;
        this.fontSize = config.fontSize;
        this.backgroundSystemMaterial = config.backgroundSystemMaterial;
        this.activatedBackgroundSystemMaterial = config.activatedBackgroundSystemMaterial;
        this.onClose = config.onClose;
        this.onClicked = config.onClicked;
    }
};
__decorate([
    Trace
], ChipV2Options.prototype, "label", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "prefixIcon", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "suffixIcon", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "allowClose", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "closeIcon", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "enabled", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "activated", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "backgroundColor", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "activatedBackgroundColor", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "borderRadius", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "size", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "direction", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "accessibilityDescription", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "accessibilityLevel", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "accessibilitySelectedType", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "maxFontScale", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "minFontScale", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "padding", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "fontSize", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "backgroundSystemMaterial", void 0);
__decorate([
    Trace
], ChipV2Options.prototype, "activatedBackgroundSystemMaterial", void 0);
ChipV2Options = __decorate([
    ObservedV2
], ChipV2Options);
export { ChipV2Options };
export class ChipV2 extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.theme = {
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
                focusActivatedColor: { "id": -1, "type": 10001, params: ['sys.color.chip_icon_activated_focus_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            },
            label: {
                normalFontSize: { "id": -1, "type": 10002, params: ['sys.float.chip_normal_font_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                smallFontSize: { "id": -1, "type": 10002, params: ['sys.float.chip_small_font_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                adaptiveItemFontSize: { "id": -1, "type": 10002, params: ['sys.float.Caption_M'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                focusFontColor: { "id": -1, "type": 10001, params: ['sys.color.chip_focus_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                focusActiveFontColor: { "id": -1, "type": 10001, params: ['sys.color.chip_activated_focus_font_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                fontColor: { "id": -1, "type": 10001, params: ['sys.color.chip_font_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                activatedFontColor: { "id": -1, "type": 10001, params: ['sys.color.chip_activated_fontcolor'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                fontFamily: 'HarmonyOS Sans',
                fontWeight: { "id": -1, "type": 10002, params: ['sys.float.chip_text_font_weight'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                activatedFontWeight: { "id": -1, "type": 10002, params: ['sys.float.chip_activated_text_font_weight'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
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
                    start: LengthMetricsCache.get('sys.float.chip_normal_text_margin', LengthMetrics.vp(6)),
                    end: LengthMetricsCache.get('sys.float.chip_normal_text_margin', LengthMetrics.vp(6)),
                    top: LengthMetrics.vp(0),
                    bottom: LengthMetrics.vp(0)
                },
                localizedSmallMargin: {
                    start: LengthMetricsCache.get('sys.float.chip_small_text_margin', LengthMetrics.vp(4)),
                    end: LengthMetricsCache.get('sys.float.chip_small_text_margin', LengthMetrics.vp(4)),
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
                focusActivatedColor: { "id": -1, "type": 10001, params: ['sys.color.chip_icon_activated_focus_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                defaultDeleteIcon: { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_cancel', 16, 16], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                focusable: false,
                isShowMargin: { "id": -1, "type": 10002, params: ['sys.float.chip_show_close_icon_margin'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            },
            defaultSymbol: {
                normalFontColor: [{ "id": -1, "type": 10001, params: ['sys.color.chip_usually_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }],
                activatedFontColor: [{ "id": -1, "type": 10001, params: ['sys.color.chip_active_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }],
                normalSymbolFontSize: LengthMetricsCache.get('sys.float.chip_normal_icon_size', LengthMetrics.vp(16)).value,
                smallSymbolFontSize: LengthMetricsCache.get('sys.float.chip_small_icon_size', LengthMetrics.vp(16)).value,
                defaultEffect: -1,
            },
            chipNode: {
                suitAgeScale: 1.75,
                minLabelWidth: 12,
                normalHeight: { "id": -1, "type": 10002, params: ['sys.float.chip_normal_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                smallHeight: { "id": -1, "type": 10002, params: ['sys.float.chip_small_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                activatedNormalHeight: { "id": -1, "type": 10002, params: ['sys.float.chip_activated_normal_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                activatedSmallHeight: { "id": -1, "type": 10002, params: ['sys.float.chip_activated_small_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                enabled: true,
                activated: false,
                backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.chip_background_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                activatedBackgroundColor: { "id": -1, "type": 10001, params: ['sys.color.chip_container_activated_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                focusOutlineColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                focusOutlineMargin: 2,
                borderColor: { "id": -1, "type": 10001, params: ['sys.color.chip_border_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                defaultBorderWidth: { "id": -1, "type": 10002, params: ['sys.float.chip_border_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                activatedBorderColor: { "id": -1, "type": 10001, params: ['sys.color.chip_activated_border_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                normalBorderRadius: { "id": -1, "type": 10002, params: ['sys.float.chip_border_radius_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                smallBorderRadius: { "id": -1, "type": 10002, params: ['sys.float.chip_border_radius_small'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                activatedBorderWidth: { "id": -1, "type": 10002, params: ['sys.float.chip_activated_border_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                borderWidth: 2,
                focusBtnScaleX: { "id": -1, "type": 10002, params: ['sys.float.chip_focused_btn_scale'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                focusBtnScaleY: { "id": -1, "type": 10002, params: ['sys.float.chip_focused_btn_scale'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                localizedNormalPadding: {
                    start: LengthMetricsCache.get('sys.float.chip_normal_text_padding', LengthMetrics.vp(16)),
                    end: LengthMetricsCache.get('sys.float.chip_normal_text_padding', LengthMetrics.vp(16)),
                    top: LengthMetrics.vp(4),
                    bottom: LengthMetrics.vp(4)
                },
                localizedSmallPadding: {
                    start: LengthMetricsCache.get('sys.float.chip_small_text_padding', LengthMetrics.vp(12)),
                    end: LengthMetricsCache.get('sys.float.chip_small_text_padding', LengthMetrics.vp(12)),
                    top: LengthMetrics.vp(4),
                    bottom: LengthMetrics.vp(4)
                },
                localizedActivatedNormalPadding: {
                    start: LengthMetricsCache.get('sys.float.chip_activated_normal_text_padding', LengthMetrics.vp(16)),
                    end: LengthMetricsCache.get('sys.float.chip_activated_normal_text_padding', LengthMetrics.vp(16)),
                    top: LengthMetrics.vp(4),
                    bottom: LengthMetrics.vp(4)
                },
                localizedActivatedSmallPadding: {
                    start: LengthMetricsCache.get('sys.float.chip_activated_small_text_padding', LengthMetrics.vp(12)),
                    end: LengthMetricsCache.get('sys.float.chip_activated_small_text_padding', LengthMetrics.vp(12)),
                    top: LengthMetrics.vp(4),
                    bottom: LengthMetrics.vp(4)
                },
                hoverBlendColor: { "id": -1, "type": 10001, params: ['sys.color.chip_hover_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                pressedBlendColor: { "id": -1, "type": 10001, params: ['sys.color.chip_press_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                focusBgColor: { "id": -1, "type": 10001, params: ['sys.color.chip_focus_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                focusActivatedBgColor: { "id": -1, "type": 10001, params: ['sys.color.chip_container_activated_focus_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                opacity: { normal: 1, hover: 0.95, pressed: 0.9 },
                normalShadowStyle: { "id": -1, "type": 10002, params: ['sys.float.chip_normal_shadow_style'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                smallShadowStyle: { "id": -1, "type": 10002, params: ['sys.float.chip_small_shadow_style'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                breakPointConstraintWidth: {
                    breakPointMinWidth: 128,
                    breakPointSmMaxWidth: 156,
                    breakPointMdMaxWidth: 280,
                    breakPointLgMaxWidth: 400
                },
            }
        };
        this.initParam("chipV2Options", (params && "chipV2Options" in params) ? params.chipV2Options : undefined);
        this.onClose = "onClose" in params ? params.onClose : () => { };
        this.onClicked = "onClicked" in params ? params.onClicked : () => { };
        this.isChipExist = true;
        this.chipScale = { x: 1, y: 1 };
        this.chipOpacity = 1;
        this.chipNodeInFocus = false;
        this.breakPoint = BreakPointsType.SM;
        this.fontSizeScale = 1;
        this.useAdaptiveLineHeight = false;
        this.smListener = mediaquery.matchMediaSync('(0vp<width) and (width<600vp)');
        this.mdListener = mediaquery.matchMediaSync('(600vp<=width) and (width<840vp)');
        this.lgListener = mediaquery.matchMediaSync('(840vp<=width)');
        this.symbolEffect = new SymbolEffect();
        this.environmentCallbackID = undefined;
        this.environmentCallback = {
            onConfigurationUpdated: (configuration) => {
                this.fontSizeScale = configuration.fontSizeScale ?? 1;
                this.updateLanguageLineHeight();
            },
            onMemoryLevel() {
            }
        };
        this.isSuffixIconFocusStyleCustomized = this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 0;
        this.isSuffixIconFocusable = this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 1;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("chipV2Options", (params && "chipV2Options" in params) ? params.chipV2Options : undefined);
        this.onClose = "onClose" in params ? params.onClose : () => { };
        this.onClicked = "onClicked" in params ? params.onClicked : () => { };
        this.isChipExist = true;
        this.chipScale = { x: 1, y: 1 };
        this.chipOpacity = 1;
        this.chipNodeInFocus = false;
        this.breakPoint = BreakPointsType.SM;
        this.fontSizeScale = 1;
        this.useAdaptiveLineHeight = false;
    }
    updateLanguageLineHeight() {
        if (deviceInfo.sdkApiVersion < 26) {
            return;
        }
        const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
        if (!resourceManager) {
            console.error(`[ChipV2] failed to get resourceManager`);
            return;
        }
        try {
            this.useAdaptiveLineHeight = resourceManager.getStringByNameSync('text_fallback_line_spacing') === 'true';
        }
        catch (e) {
            console.error(`[ChipV2] failed to get text_fallback_line_spacing resource`);
        }
    }
    aboutToAppear() {
        this.smListener.on('change', (mediaQueryResult) => {
            if (mediaQueryResult.matches) {
                this.breakPoint = BreakPointsType.SM;
            }
        });
        this.mdListener.on('change', (mediaQueryResult) => {
            if (mediaQueryResult.matches) {
                this.breakPoint = BreakPointsType.MD;
            }
        });
        this.lgListener.on('change', (mediaQueryResult) => {
            if (mediaQueryResult.matches) {
                this.breakPoint = BreakPointsType.LG;
            }
        });
        this.updateLanguageLineHeight();
        let abilityContext = this.getUIContext().getHostContext();
        if (abilityContext) {
            this.fontSizeScale = abilityContext.config?.fontSizeScale ?? 1;
            this.environmentCallbackID = abilityContext.getApplicationContext().on('environment', this.environmentCallback);
        }
        this.onClose = this.chipV2Options.onClose;
        this.onClicked = this.chipV2Options.onClicked;
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
        if (!this.chipV2Options.activatedBackgroundColor) {
            return false;
        }
        try {
            return this.chipV2Options.activatedBackgroundColor.color !==
                ColorMetrics.resourceColor(this.theme.chipNode.activatedBackgroundColor).color;
        }
        catch (error) {
            console.error(`[ChipV2] failed to get ColorMetrics.resourceColor`);
            return false;
        }
    }
    isSetNormalChipBgColor() {
        if (!this.chipV2Options.backgroundColor) {
            return false;
        }
        try {
            return this.chipV2Options.backgroundColor.color !==
                ColorMetrics.resourceColor(this.theme.chipNode.backgroundColor).color;
        }
        catch (error) {
            console.error(`[ChipV2] failed to get resourceColor`);
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
    ChipBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.clip(false);
            Button.shadow(this.getShadowStyles());
            Button.padding(0);
            Button.focusable(true);
            Button.size(this.getChipSize());
            Button.enabled(this.isChipEnabled());
            Button.direction(this.chipV2Options.direction);
            Button.backgroundColor(this.getChipBackgroundColor());
            Button.systemMaterial(this.getBackgroundSystemMaterial());
            Button.borderWidth(this.getChipNodeBorderWidth());
            Button.borderColor(this.getChipNodeBorderColor());
            Button.borderRadius(this.getChipBorderRadius());
            Button.responseRegion(this.getChipResponseRegion());
            Button.scale(this.chipScale);
            Button.opacity(this.chipOpacity);
            Button.accessibilityGroup(true);
            Button.accessibilityDescription(this.getAccessibilityDescription());
            Button.accessibilityLevel(this.chipV2Options.accessibilityLevel);
            Button.accessibilityChecked(this.getAccessibilityChecked());
            Button.accessibilitySelected(this.getAccessibilitySelected());
            Button.onClick(this.getChipOnClicked());
            Button.onKeyEvent((event) => {
                if (!event || event.type === null || event.type !== KeyType.Down) {
                    return;
                }
                let isDeleteChip = event.keyCode === KeyCode.KEYCODE_FORWARD_DEL;
                let isEnterDeleteChip = event.keyCode === KeyCode.KEYCODE_ENTER && this.chipV2Options.allowClose !== false &&
                    !this.hasSuffixImageIcon() && this.isSuffixIconFocusStyleCustomized;
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
            Button.onHover(!this.isSuffixIconFocusStyleCustomized ? undefined : (isHover) => {
                isHover ? this.chipZoomIn() : this.chipZoomOut();
            });
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
            Flex.direction(this.chipV2Options.direction);
            Flex.padding(this.getChipPadding());
            Flex.size(this.getChipSize());
            Flex.constraintSize(this.getChipConstraintSize());
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.hasPrefixSymbolIcon()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.getFontSizeForSymbol());
                        SymbolGlyph.maxFontScale(this.chipV2Options.maxFontScale);
                        SymbolGlyph.minFontScale(this.chipV2Options.minFontScale);
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.PREFIX_SYMBOL));
                        SymbolGlyph.flexShrink(0);
                        SymbolGlyph.attributeModifier.bind(this)(this.getPrefixSymbolModifier());
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(this.symbolEffect, false);
                        SymbolGlyph.symbolEffect(this.symbolEffect, this.theme.defaultSymbol.defaultEffect);
                    }, SymbolGlyph);
                });
            }
            else if (this.hasPrefixImageIcon()) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.getPrefixImageIcon().src);
                        Image.direction(this.chipV2Options.direction);
                        Image.size(this.getPrefixIconSize());
                        Image.fillColor(this.getPrefixIconFilledColor());
                        Image.objectFit(ImageFit.Cover);
                        Image.focusable(false);
                        Image.flexShrink(0);
                        Image.draggable(false);
                        Image.attributeModifier.bind(this)(this.getPrefixImageIcon().modifier);
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
            Text.create(this.chipV2Options.label.text);
            Text.draggable(false);
            Text.flexShrink(1);
            Text.focusable(true);
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
            Text.direction(this.chipV2Options.direction);
            Text.fontSize(this.getLabelFontSize());
            Text.fontColor(this.getLabelFontColor());
            Text.fontFamily(this.getLabelFontFamily());
            Text.fontWeight(this.getLabelFontWeight());
            Text.maxFontScale(this.chipV2Options.maxFontScale);
            Text.minFontScale(this.chipV2Options.minFontScale);
            Text.margin(this.getLabelMargin());
            Text.includeFontPadding(this.useAdaptiveLineHeight);
            Text.fallbackLineSpacing(this.useAdaptiveLineHeight);
            Text.attributeModifier.bind(this)(this.chipV2Options.label.modifier);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.hasSuffixSymbolIcon()) {
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
                        SymbolGlyph.fontSize(this.getFontSizeForSymbol());
                        SymbolGlyph.maxFontScale(this.chipV2Options.maxFontScale);
                        SymbolGlyph.minFontScale(this.chipV2Options.minFontScale);
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_SYMBOL));
                        SymbolGlyph.attributeModifier.bind(this)(this.getSuffixSymbolModifier());
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(this.symbolEffect, false);
                        SymbolGlyph.symbolEffect(this.symbolEffect, this.theme.defaultSymbol.defaultEffect);
                    }, SymbolGlyph);
                    Button.pop();
                });
            }
            else if (this.hasSuffixImageIcon()) {
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
                        Button.accessibilityText(this.getSuffixImageIconAccessibilityText());
                        Button.accessibilityDescription(this.getSuffixImageIconAccessibilityDescription());
                        Button.accessibilityLevel(this.getSuffixImageIconAccessibilityLevel());
                        Button.onClick(this.getSuffixIconAction());
                        Button.focusable(this.isSuffixIconFocusable);
                    }, Button);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.getSuffixImageIcon().src);
                        Image.direction(this.chipV2Options.direction);
                        Image.size(this.getSuffixIconSize());
                        Image.fillColor(this.getSuffixIconFilledColor());
                        Image.objectFit(ImageFit.Cover);
                        Image.draggable(false);
                        Image.attributeModifier.bind(this)(this.getSuffixImageIcon().modifier);
                    }, Image);
                    Button.pop();
                });
            }
            else if (this.isClosable()) {
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
                        Button.responseRegion({
                            x: { "id": -1, "type": 10002, params: ['sys.float.chip_touch_hot_zone_x'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            y: { "id": -1, "type": 10002, params: ['sys.float.chip_touch_hot_zone_y'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            width: { "id": -1, "type": 10002, params: ['sys.float.chip_touch_hot_zone_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            height: { "id": -1, "type": 10002, params: ['sys.float.chip_touch_hot_zone_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
                        });
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
                        SymbolGlyph.create({ "id": -1, "type": 40000, params: ['sys.symbol.xmark'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        SymbolGlyph.fontSize(this.getCloseOptionsFontsize());
                        SymbolGlyph.maxFontScale(this.chipV2Options.maxFontScale);
                        SymbolGlyph.minFontScale(this.chipV2Options.minFontScale);
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_SYMBOL));
                    }, SymbolGlyph);
                    Button.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(3, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
        Button.pop();
    }
    hasPrefixImageIcon() {
        return this.chipV2Options.prefixIcon instanceof ChipV2PrefixImageIcon;
    }
    hasPrefixSymbolIcon() {
        return this.chipV2Options.prefixIcon instanceof ChipV2PrefixSymbolIcon &&
            !!(this.chipV2Options.prefixIcon.normal ||
                this.chipV2Options.prefixIcon.activated);
    }
    hasSuffixImageIcon() {
        return this.chipV2Options.suffixIcon instanceof ChipV2SuffixImageIcon;
    }
    hasSuffixSymbolIcon() {
        return this.chipV2Options.suffixIcon instanceof ChipV2SuffixSymbolIcon &&
            !!(this.chipV2Options.suffixIcon.normal ||
                this.chipV2Options.suffixIcon.activated);
    }
    getPrefixImageIcon() {
        return this.hasPrefixImageIcon() ? this.chipV2Options.prefixIcon : undefined;
    }
    getSuffixImageIcon() {
        return this.hasSuffixImageIcon() ? this.chipV2Options.suffixIcon : undefined;
    }
    getSuffixSymbolIcon() {
        return this.hasSuffixSymbolIcon() ? this.chipV2Options.suffixIcon : undefined;
    }
    getCloseIconAccessibilityLevel() {
        if (this.chipV2Options.closeIcon?.accessibilityLevel === 'no' ||
            this.chipV2Options.closeIcon?.accessibilityLevel === 'no-hide-descendants') {
            return this.chipV2Options.closeIcon.accessibilityLevel;
        }
        return 'yes';
    }
    getCloseIconAccessibilityDescription() {
        if (typeof this.chipV2Options.closeIcon?.accessibilityDescription === 'undefined') {
            return void 0;
        }
        return this.chipV2Options.closeIcon.accessibilityDescription;
    }
    getCloseIconAccessibilityText() {
        if (typeof this.chipV2Options.closeIcon?.accessibilityText === 'undefined') {
            return { "id": -1, "type": 10003, params: ['sys.string.delete_used_for_accessibility_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        return this.chipV2Options.closeIcon.accessibilityText;
    }
    getSuffixIconAction() {
        if (this.hasSuffixImageIcon()) {
            const suffixImgIcon = this.getSuffixImageIcon();
            if (!suffixImgIcon.action) {
                return void 0;
            }
            return () => {
                if (this.isChipEnabled()) {
                    suffixImgIcon.action?.();
                }
            };
        }
        return void 0;
    }
    getSuffixIconFilledColor() {
        if (this.isChipActivated()) {
            return this.getSuffixImageIcon()?.activatedFillColor ?? this.getDefaultActiveIconColor(IconType.PREFIX_ICON);
        }
        return this.getSuffixImageIcon()?.fillColor ?? this.getDefaultFillIconColor(IconType.SUFFIX_ICON);
    }
    getSuffixIconSize() {
        let suffixIconSize = { width: 0, height: 0 };
        let width = this.getSuffixImageIcon()?.size?.width;
        if (typeof width !== 'undefined' && this.isValidLength(width)) {
            suffixIconSize.width = lengthMetricsToLength(width);
        }
        else {
            suffixIconSize.width =
                this.isSmallChipSize() ? this.theme.suffixIcon.smallSize.width : this.theme.suffixIcon.normalSize.width;
        }
        let height = this.getSuffixImageIcon()?.size?.height;
        if (typeof height !== 'undefined' && this.isValidLength(height)) {
            suffixIconSize.height = lengthMetricsToLength(height);
        }
        else {
            suffixIconSize.height =
                this.isSmallChipSize() ? this.theme.suffixIcon.smallSize.height : this.theme.suffixIcon.normalSize.height;
        }
        return suffixIconSize;
    }
    getSuffixImageIconAccessibilityLevel() {
        const suffixIcon = this.getSuffixImageIcon();
        if (suffixIcon?.accessibilityLevel === 'no' || suffixIcon?.accessibilityLevel === 'no-hide-descendants') {
            return suffixIcon.accessibilityLevel;
        }
        return suffixIcon?.action ? 'yes' : 'no';
    }
    getSuffixImageIconAccessibilityDescription() {
        const suffixIcon = this.getSuffixImageIcon();
        if (typeof suffixIcon?.accessibilityDescription === 'undefined') {
            return void 0;
        }
        return suffixIcon.accessibilityDescription;
    }
    getSuffixImageIconAccessibilityText() {
        const suffixIcon = this.getSuffixImageIcon();
        if (typeof suffixIcon?.accessibilityText === 'undefined') {
            return void 0;
        }
        return suffixIcon.accessibilityText;
    }
    isClosable() {
        return this.chipV2Options.allowClose ?? true;
    }
    getSuffixSymbolModifier() {
        if (this.isChipActivated()) {
            return this.getSuffixSymbolIcon()?.activated;
        }
        return this.getSuffixSymbolIcon()?.normal;
    }
    getSuffixSymbolAccessibilityLevel() {
        if (this.isChipActivated()) {
            if (this.getSuffixSymbolIcon()?.activatedAccessibility?.accessibilityLevel === 'no' ||
                this.getSuffixSymbolIcon()?.activatedAccessibility?.accessibilityLevel === 'no-hide-descendants') {
                return this.getSuffixSymbolIcon().activatedAccessibility.accessibilityLevel;
            }
            return this.getSuffixSymbolIcon()?.action ? 'yes' : 'no';
        }
        if (this.getSuffixSymbolIcon()?.normalAccessibility?.accessibilityLevel === 'no' ||
            this.getSuffixSymbolIcon()?.normalAccessibility?.accessibilityLevel === 'no-hide-descendants') {
            return this.getSuffixSymbolIcon().normalAccessibility.accessibilityLevel;
        }
        return this.getSuffixSymbolIcon()?.action ? 'yes' : 'no';
    }
    getSuffixSymbolAccessibilityDescription() {
        if (this.isChipActivated()) {
            if (typeof this.getSuffixSymbolIcon()?.activatedAccessibility?.accessibilityDescription !== 'undefined') {
                return this.getSuffixSymbolIcon().activatedAccessibility.accessibilityDescription;
            }
            return void 0;
        }
        if (typeof this.getSuffixSymbolIcon()?.normalAccessibility?.accessibilityDescription !== 'undefined') {
            return this.getSuffixSymbolIcon().normalAccessibility.accessibilityDescription;
        }
        return void 0;
    }
    getSuffixSymbolAccessibilityText() {
        if (this.isChipActivated()) {
            if (typeof this.getSuffixSymbolIcon()?.activatedAccessibility?.accessibilityText !== 'undefined') {
                return this.getSuffixSymbolIcon().activatedAccessibility.accessibilityText;
            }
            return void 0;
        }
        if (typeof this.getSuffixSymbolIcon()?.normalAccessibility?.accessibilityText !== 'undefined') {
            return this.getSuffixSymbolIcon().normalAccessibility.accessibilityText;
        }
        return void 0;
    }
    getSuffixSymbolAction() {
        if (typeof this.getSuffixSymbolIcon()?.action === 'undefined') {
            return void 0;
        }
        return () => {
            if (!this.isChipEnabled()) {
                return;
            }
            this.getSuffixSymbolIcon()?.action?.();
        };
    }
    getPrefixIconFilledColor() {
        if (this.isChipActivated()) {
            return this.getPrefixImageIcon()?.activatedFillColor ?? this.getDefaultActiveIconColor(IconType.PREFIX_ICON);
        }
        return this.getPrefixImageIcon()?.fillColor ?? this.getDefaultFillIconColor(IconType.PREFIX_ICON);
    }
    getPrefixIconSize() {
        let prefixIconSize = { width: 0, height: 0 };
        let width = this.getPrefixImageIcon()?.size?.width;
        if (typeof width !== 'undefined' && this.isValidLength(width)) {
            prefixIconSize.width = lengthMetricsToLength(width);
        }
        else {
            prefixIconSize.width =
                this.isSmallChipSize() ? this.theme.prefixIcon.smallSize.width : this.theme.prefixIcon.normalSize.width;
        }
        let height = this.getPrefixImageIcon()?.size?.height;
        if (typeof height !== 'undefined' && this.isValidLength(height)) {
            prefixIconSize.height = lengthMetricsToLength(height);
        }
        else {
            prefixIconSize.height =
                this.isSmallChipSize() ? this.theme.prefixIcon.smallSize.height : this.theme.prefixIcon.normalSize.height;
        }
        return prefixIconSize;
    }
    getPrefixSymbolModifier() {
        if (!(this.chipV2Options.prefixIcon instanceof ChipV2PrefixSymbolIcon)) {
            return undefined;
        }
        const prefixSymbol = this.chipV2Options.prefixIcon;
        if (this.isChipActivated()) {
            return prefixSymbol.activated;
        }
        return prefixSymbol.normal;
    }
    getDefaultSymbolColor(iconType) {
        return this.isChipActivated() ? this.getSymbolActiveColor(iconType) :
            this.getSymbolFillColor(iconType);
    }
    getDefaultActiveIconColor(iconType) {
        if (iconType === IconType.PREFIX_ICON) {
            return this.chipNodeInFocus ? this.theme.prefixIcon.focusActivatedColor :
                this.theme.prefixIcon.activatedFillColor;
        }
        else {
            return this.chipNodeInFocus ? this.theme.suffixIcon.focusActivatedColor :
                this.theme.suffixIcon.activatedFillColor;
        }
    }
    getDefaultFillIconColor(iconType) {
        if (iconType === IconType.PREFIX_ICON) {
            return this.chipNodeInFocus ? this.theme.prefixIcon.focusFillColor : this.theme.prefixIcon.fillColor;
        }
        else {
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
    getChipConstraintSize() {
        const constraintSize = {};
        if (typeof this.chipV2Options.size === 'string') {
            constraintSize.maxWidth = this.getChipMaxWidth();
            if (this.chipV2Options.size === ChipV2Size.SMALL) {
                constraintSize.minHeight =
                    this.isChipActivated() ? this.theme.chipNode.activatedSmallHeight : this.theme.chipNode.smallHeight;
            }
            else {
                constraintSize.minHeight =
                    this.isChipActivated() ? this.theme.chipNode.activatedNormalHeight : this.theme.chipNode.normalHeight;
            }
        }
        else {
            if (typeof this.chipV2Options.size?.width === 'undefined' ||
                !this.isValidLength(this.chipV2Options.size.width)) {
                constraintSize.maxWidth = this.getChipMaxWidth();
            }
            if (typeof this.chipV2Options.size?.height === 'undefined' ||
                !this.isValidLength(this.chipV2Options.size.height)) {
                constraintSize.minHeight =
                    this.isChipActivated() ? this.theme.chipNode.activatedNormalHeight : this.theme.chipNode.normalHeight;
            }
        }
        return constraintSize;
    }
    getChipHeight() {
        let height;
        if (typeof this.chipV2Options.size !== 'string') {
            if (typeof this.chipV2Options.size?.height !== 'undefined' &&
                this.isValidLength(this.chipV2Options.size.height)) {
                height = lengthMetricsToLength(this.chipV2Options.size.height);
            }
            else {
                height = this.isChipActivated() ? this.theme.chipNode.activatedNormalHeight : this.theme.chipNode.normalHeight;
            }
        }
        else if (this.chipV2Options.size === ChipV2Size.SMALL) {
            height = this.isChipActivated() ? this.theme.chipNode.activatedSmallHeight : this.theme.chipNode.smallHeight;
        }
        else {
            height = this.isChipActivated() ? this.theme.chipNode.activatedNormalHeight : this.theme.chipNode.normalHeight;
        }
        return this.parseLength(height) ?? HOT_SPOT_MIN_HEIGHT;
    }
    getChipResponseRegion() {
        if (deviceInfo.sdkApiVersion >= 26) {
            const chipHeight = this.getChipHeight();
            if (chipHeight < HOT_SPOT_MIN_HEIGHT) {
                return {
                    x: 0,
                    y: (chipHeight - HOT_SPOT_MIN_HEIGHT) / 2,
                    width: '100%',
                    height: HOT_SPOT_MIN_HEIGHT
                };
            }
        }
        return undefined;
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
            height: 'auto'
        };
        if (typeof this.chipV2Options.size !== 'string') {
            if (typeof this.chipV2Options.size?.width !== 'undefined' &&
                this.isValidLength(this.chipV2Options.size.width)) {
                chipSize.width = lengthMetricsToLength(this.chipV2Options.size.width);
            }
            if (typeof this.chipV2Options.size?.height !== 'undefined' &&
                this.isValidLength(this.chipV2Options.size.height)) {
                chipSize.height = lengthMetricsToLength(this.chipV2Options.size.height);
            }
        }
        return chipSize;
    }
    copyPadding(src) {
        return {
            top: src.top,
            bottom: src.bottom,
            start: src.start,
            end: src.end
        };
    }
    getChipPadding() {
        let chipTheme = this.theme.chipNode;
        let res;
        if (this.isSmallChipSize()) {
            res = this.isChipActivated() ? this.copyPadding(chipTheme.localizedActivatedSmallPadding) :
                this.copyPadding(chipTheme.localizedSmallPadding);
        }
        else {
            res = this.isChipActivated() ? this.copyPadding(chipTheme.localizedActivatedNormalPadding) :
                this.copyPadding(chipTheme.localizedNormalPadding);
        }
        if (this.chipV2Options.padding?.top &&
            LengthMetricsUtils.getInstance().isNaturalNumber(this.chipV2Options.padding.top)) {
            res.top = this.chipV2Options.padding.top;
        }
        if (this.chipV2Options.padding?.bottom &&
            LengthMetricsUtils.getInstance().isNaturalNumber(this.chipV2Options.padding.bottom)) {
            res.bottom = this.chipV2Options.padding.bottom;
        }
        if (this.chipV2Options.padding?.start &&
            LengthMetricsUtils.getInstance().isNaturalNumber(this.chipV2Options.padding.start)) {
            res.start = this.chipV2Options.padding.start;
        }
        if (this.chipV2Options.padding?.end &&
            LengthMetricsUtils.getInstance().isNaturalNumber(this.chipV2Options.padding.end)) {
            res.end = this.chipV2Options.padding.end;
        }
        return res;
    }
    getLabelMargin() {
        const localizedLabelMargin = {
            start: LengthMetrics.vp(0),
            end: LengthMetrics.vp(0),
        };
        const defaultLocalizedMargin = this.isSmallChipSize() ? this.theme.label.localizedSmallMargin : this.theme.label.localizedNormalMargin;
        if (typeof this.chipV2Options.label.localizedLabelMargin?.start !== 'undefined' &&
            this.chipV2Options.label.localizedLabelMargin.start.value >= 0) {
            localizedLabelMargin.start = this.chipV2Options.label.localizedLabelMargin.start;
        }
        else if (this.hasPrefix()) {
            localizedLabelMargin.start = defaultLocalizedMargin.start;
        }
        if (typeof this.chipV2Options.label.localizedLabelMargin?.end !== 'undefined' &&
            this.chipV2Options.label.localizedLabelMargin.end.value >= 0) {
            localizedLabelMargin.end = this.chipV2Options.label.localizedLabelMargin.end;
        }
        else if (this.hasSuffix() || this.isNeedShowCloseIconMargin()) {
            localizedLabelMargin.end = defaultLocalizedMargin.end;
        }
        if (typeof this.chipV2Options.label.localizedLabelMargin === 'object') {
            return localizedLabelMargin;
        }
        if (typeof this.chipV2Options.label.labelMargin === 'object') {
            const labelMargin = { left: 0, right: 0 };
            const defaultLabelMargin = this.isSmallChipSize() ? this.theme.label.smallMargin : this.theme.label.normalMargin;
            if (typeof this.chipV2Options.label.labelMargin?.left !== 'undefined' &&
                this.isValidLength(this.chipV2Options.label.labelMargin.left)) {
                labelMargin.left = lengthMetricsToLength(this.chipV2Options.label.labelMargin.left);
            }
            else if (this.hasPrefix()) {
                labelMargin.left = defaultLabelMargin.left;
            }
            if (typeof this.chipV2Options.label.labelMargin?.right !== 'undefined' &&
                this.isValidLength(this.chipV2Options.label.labelMargin.right)) {
                labelMargin.right = lengthMetricsToLength(this.chipV2Options.label.labelMargin.right);
            }
            else if (this.hasSuffix()) {
                labelMargin.right = defaultLabelMargin.right;
            }
            return labelMargin;
        }
        return localizedLabelMargin;
    }
    hasSuffix() {
        if (this.hasSuffixImageIcon()) {
            return true;
        }
        return this.isChipActivated() ? !!this.chipV2Options.suffixIcon?.activated :
            !!this.chipV2Options.suffixIcon?.normal;
    }
    hasPrefix() {
        if (this.hasPrefixImageIcon()) {
            return true;
        }
        return this.isChipActivated() ? !!this.chipV2Options.prefixIcon?.activated :
            !!this.chipV2Options.prefixIcon?.normal;
    }
    getLabelFontWeight() {
        if (this.isChipActivated()) {
            return this.resourceToNumber(this.theme.label.activatedFontWeight, FontWeight.Medium);
        }
        return this.resourceToNumber(this.theme.label.fontWeight, FontWeight.Regular);
    }
    getLabelFontFamily() {
        return this.chipV2Options.label.fontFamily ?? this.theme.label.fontFamily;
    }
    getFontSizeForSymbol() {
        if (!!this.chipV2Options.fontSize && this.isValidLength(this.chipV2Options.fontSize)) {
            return lengthMetricsToLength(this.chipV2Options.fontSize);
        }
        return this.isSmallChipSize() ? this.theme.defaultSymbol.smallSymbolFontSize :
            this.theme.defaultSymbol.normalSymbolFontSize;
    }
    getCloseOptionsFontsize() {
        if (!!this.chipV2Options.closeIcon?.fontSize && this.isValidLength(this.chipV2Options.closeIcon.fontSize)) {
            return lengthMetricsToLength(this.chipV2Options.closeIcon.fontSize);
        }
        if (!!this.chipV2Options.fontSize && this.isValidLength(this.chipV2Options.fontSize)) {
            return lengthMetricsToLength(this.chipV2Options.fontSize);
        }
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
        if (this.getBackgroundSystemMaterial()) {
            return undefined;
        }
        let themeChipNode = this.theme.chipNode;
        return this.isChipActivated() ? themeChipNode.activatedBorderColor : themeChipNode.borderColor;
    }
    getChipNodeBorderWidth() {
        if (this.getBackgroundSystemMaterial()) {
            return undefined;
        }
        let themeChipNode = this.theme.chipNode;
        return this.isChipActivated() ? themeChipNode.activatedBorderWidth : themeChipNode.defaultBorderWidth;
    }
    getLabelFontColor() {
        if (this.isChipActivated()) {
            return colorMetricsToResourceColor(this.chipV2Options.label.activatedFontColor) ?? this.getActiveFontColor();
        }
        return colorMetricsToResourceColor(this.chipV2Options.label.fontColor) ?? this.getFontColor();
    }
    getLabelFontSize() {
        if (typeof this.chipV2Options.label.fontSize !== 'undefined' &&
            this.isValidLength(this.chipV2Options.label.fontSize)) {
            return lengthMetricsToDimension(this.chipV2Options.label.fontSize);
        }
        if (!!this.chipV2Options.fontSize && this.isValidLength(this.chipV2Options.fontSize)) {
            return lengthMetricsToDimension(this.chipV2Options.fontSize);
        }
        if (this.isSmallChipSize()) {
            return this.useAdaptiveLineHeight ? this.theme.label.adaptiveItemFontSize : this.theme.label.smallFontSize;
        }
        return this.useAdaptiveLineHeight ? this.theme.label.adaptiveItemFontSize : this.theme.label.normalFontSize;
    }
    deleteChip() {
        this.getUIContext().animateTo({ curve: Curve.Sharp, duration: 150 }, () => {
            this.chipOpacity = 0;
        });
        this.getUIContext().animateTo({
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
            return (event) => {
                this.onClicked();
            };
        }
        return void 0;
    }
    getAccessibilitySelected() {
        if (this.getChipAccessibilitySelectedType() === ChipV2AccessibilitySelectedType.SELECTED) {
            return this.isChipActivated();
        }
        return void 0;
    }
    getAccessibilityChecked() {
        if (this.getChipAccessibilitySelectedType() === ChipV2AccessibilitySelectedType.CHECKED) {
            return this.isChipActivated();
        }
        return void 0;
    }
    getChipAccessibilitySelectedType() {
        if (typeof this.chipV2Options.activated === 'undefined') {
            return ChipV2AccessibilitySelectedType.CLICKED;
        }
        return this.chipV2Options.accessibilitySelectedType ?? ChipV2AccessibilitySelectedType.CHECKED;
    }
    getAccessibilityDescription() {
        if (typeof this.chipV2Options.accessibilityDescription === 'undefined') {
            return void 0;
        }
        return this.chipV2Options.accessibilityDescription;
    }
    isChipEnabled() {
        return this.chipV2Options.enabled ?? true;
    }
    getChipBorderRadius() {
        if (typeof this.chipV2Options.borderRadius !== 'undefined' && this.isValidLength(this.chipV2Options.borderRadius)) {
            return lengthMetricsToDimension(this.chipV2Options.borderRadius);
        }
        return this.isSmallChipSize() ? this.theme.chipNode.smallBorderRadius : this.theme.chipNode.normalBorderRadius;
    }
    isSmallChipSize() {
        return typeof this.chipV2Options.size === 'string' && this.chipV2Options.size === ChipV2Size.SMALL;
    }
    getChipBackgroundColor() {
        let themeChipNode = this.theme.chipNode;
        if (this.isChipActivated()) {
            return this.chipNodeInFocus && !this.isSetActiveChipBgColor() ? themeChipNode.focusActivatedBgColor :
                this.getColor(this.chipV2Options.activatedBackgroundColor, themeChipNode.activatedBackgroundColor);
        }
        return this.chipNodeInFocus && !this.isSetNormalChipBgColor() ? themeChipNode.focusBgColor :
            this.getColor(this.chipV2Options.backgroundColor, this.theme.chipNode.backgroundColor);
    }
    getBackgroundSystemMaterial() {
        if (deviceInfo.sdkApiVersion < 26) {
            return undefined;
        }
        if (this.isChipActivated()) {
            return this.chipV2Options.activatedBackgroundSystemMaterial;
        }
        return this.chipV2Options.backgroundSystemMaterial;
    }
    getColor(color, defaultColor) {
        if (!color) {
            return defaultColor;
        }
        try {
            return color.color;
        }
        catch (e) {
            console.error(`[ChipV2] failed to get color`);
            return Color.Transparent;
        }
    }
    isChipActivated() {
        return this.chipV2Options.activated ?? false;
    }
    getResourceNumber(resource) {
        const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
        if (!resourceManager) {
            console.error('[ChipV2] failed to get resourceManager');
            return null;
        }
        switch (resource.type) {
            case RESOURCE_TYPE_FLOAT:
            case RESOURCE_TYPE_INTEGER:
                try {
                    if (resource.id !== -1) {
                        return resourceManager.getNumber(resource.id);
                    }
                    return resourceManager.getNumberByName(resource.params[0].split('.')[2]);
                }
                catch (error) {
                    console.error(`[ChipV2] get resource error`);
                    return null;
                }
            default:
                return null;
        }
    }
    resourceToNumber(resource, defaultValue) {
        if (!resource || !resource.type) {
            console.error('[ChipV2] failed: resource get fail');
            return defaultValue;
        }
        const result = this.getResourceNumber(resource);
        return result !== null ? result : defaultValue;
    }
    isValidLength(length) {
        if (!length || length.unit === LengthUnit.PERCENT) {
            return false;
        }
        return length.value >= 0;
    }
    chipZoomOut() {
        if (this.isSuffixIconFocusStyleCustomized) {
            this.chipScale = {
                x: 1, y: 1
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
    isNeedShowCloseIconMargin() {
        return this.isClosable() && this.isSuffixIconFocusStyleCustomized;
    }
    parseLength(length) {
        if (typeof length === 'number') {
            return length;
        }
        if (typeof length === 'string') {
            if (/(\d+)(vp|px|lpx|fp)?/.test(length)) {
                const value = parseFloat(RegExp.$1);
                const unit = RegExp.$2;
                if (unit === 'vp' || unit === '') {
                    return value;
                }
                else if (unit === 'px') {
                    return this.getUIContext().px2vp(value);
                }
                else if (unit === 'fp') {
                    return this.getUIContext().px2vp(this.getUIContext().fp2px(value));
                }
                else if (unit === 'lpx') {
                    return this.getUIContext().px2vp(this.getUIContext().lpx2px(value));
                }
                else {
                    return undefined;
                }
            }
            return undefined;
        }
        if (typeof length === 'object') {
            try {
                const metrics = LengthMetrics.resource(length);
                if (metrics.unit === LengthUnit.VP) {
                    return metrics.value;
                }
                else if (metrics.unit === LengthUnit.PX) {
                    return this.getUIContext().px2vp(metrics.value);
                }
                else if (metrics.unit === LengthUnit.FP) {
                    return this.getUIContext().px2vp(this.getUIContext().fp2px(metrics.value));
                }
                else {
                    return this.getUIContext().px2vp(this.getUIContext().lpx2px(metrics.value));
                }
            }
            catch (error) {
                console.error('Failed to parse length because the type of resource is invalid');
                return undefined;
            }
        }
        return undefined;
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.isChipExist) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ChipBuilder.bind(this)();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("chipV2Options" in params) {
            this.updateParam("chipV2Options", params.chipV2Options);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], ChipV2.prototype, "chipV2Options", void 0);
__decorate([
    Event
], ChipV2.prototype, "onClose", void 0);
__decorate([
    Event
], ChipV2.prototype, "onClicked", void 0);
__decorate([
    Local
], ChipV2.prototype, "isChipExist", void 0);
__decorate([
    Local
], ChipV2.prototype, "chipScale", void 0);
__decorate([
    Local
], ChipV2.prototype, "chipOpacity", void 0);
__decorate([
    Local
], ChipV2.prototype, "chipNodeInFocus", void 0);
__decorate([
    Local
], ChipV2.prototype, "breakPoint", void 0);
__decorate([
    Local
], ChipV2.prototype, "fontSizeScale", void 0);
__decorate([
    Local
], ChipV2.prototype, "useAdaptiveLineHeight", void 0);
function lengthMetricsToLength(length) {
    if (length.unit === LengthUnit.PX) {
        return `${length.value}px`;
    }
    else if (length.unit === LengthUnit.VP) {
        return `${length.value}vp`;
    }
    else if (length.unit === LengthUnit.FP) {
        return `${length.value}fp`;
    }
    else if (length.unit === LengthUnit.PERCENT) {
        return `${length.value}%`;
    }
    else if (length.unit === LengthUnit.LPX) {
        return `${length.value}lpx`;
    }
    return 0;
}
function lengthMetricsToDimension(length) {
    if (length.unit === LengthUnit.PX) {
        return `${length.value}px`;
    }
    else if (length.unit === LengthUnit.VP) {
        return `${length.value}vp`;
    }
    else if (length.unit === LengthUnit.FP) {
        return `${length.value}fp`;
    }
    else if (length.unit === LengthUnit.PERCENT) {
        return `${length.value}%`;
    }
    else if (length.unit === LengthUnit.LPX) {
        return `${length.value}lpx`;
    }
    return 0;
}
function colorMetricsToResourceColor(color) {
    if (!color) {
        return undefined;
    }
    return color.color;
}
export default {
    ChipV2Size,
    ChipV2AccessibilitySelectedType,
    ChipV2Icon,
    ChipV2ImageIcon,
    ChipV2SuffixImageIcon,
    ChipV2PrefixImageIcon,
    ChipV2Accessibility,
    ChipV2CloseIcon,
    ChipV2SymbolIcon,
    ChipV2PrefixSymbolIcon,
    ChipV2SuffixSymbolIcon,
    ChipV2Label,
    ChipV2Options,
    ChipV2,
}