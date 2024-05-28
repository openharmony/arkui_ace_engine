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
const EnvironmentCallback = requireNapi('EnvironmentCallback');

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}


export var ChipSize;
(function (u5) {
    u5["NORMAL"] = "NORMAL";
    u5["SMALL"] = "SMALL";
})(ChipSize || (ChipSize = {}));
var BreakPointsType;
(function (t5) {
    t5["SM"] = "SM";
    t5["MD"] = "MD";
    t5["LG"] = "LG";
})(BreakPointsType || (BreakPointsType = {}));

export const defaultTheme = {
    prefixIcon: {
        size: { width: 16, height: 16 },
        fillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_secondary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        activatedFillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_primary_contrary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
    },
    label: {
        normalFontSize: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_text_size_button2'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        smallFontSize: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_text_size_button2'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        fontColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_primary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        activatedFontColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_primary_contrary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        fontFamily: "HarmonyOS Sans",
        normalMargin: { left: 6, right: 6, top: 0, bottom: 0 },
        smallMargin: { left: 4, right: 4, top: 0, bottom: 0 },
        defaultFontSize: 14,
    },
    suffixIcon: {
        size: { width: 16, height: 16 },
        fillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_secondary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        activatedFillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_primary_contrary'],
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
        fontSize: 16,
    },
    chipNode: {
        suitAgeScale: 1.75,
        minLabelWidth: 12,
        normalHeight: 36,
        smallHeight: 28,
        enabled: true,
        activated: false,
        backgroundColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_button_normal'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        activatedBackgroundColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_emphasize'],
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
        normalBorderRadius: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_corner_radius_tips_instant_tip'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        smallBorderRadius: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_corner_radius_piece'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        borderWidth: 2,
        normalPadding: { left: 16, right: 16, top: 4, bottom: 4 },
        smallPadding: { left: 12, right: 12, top: 4, bottom: 4 },
        hoverBlendColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_hover'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        pressedBlendColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_click_effect'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        opacity: { normal: 1, hover: 0.95, pressed: 0.9, disabled: 0.4 },
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

export function Chip(i5, j5 = null) {
    const k5 = i5;
    {
        (j5 ? j5 : this).observeComponentCreation2((m5, n5, o5 = k5) => {
            if (n5) {
                let p5 = new ChipComponent(j5 ? j5 : this, {
                    chipSize: o5.size,
                    prefixIcon: o5.prefixIcon,
                    prefixSymbol: o5.prefixSymbol,
                    label: o5.label,
                    suffixIcon: o5.suffixIcon,
                    suffixSymbol: o5.suffixSymbol,
                    allowClose: o5.allowClose,
                    chipEnabled: o5.enabled,
                    chipActivated: o5.activated,
                    chipNodeBackgroundColor: o5.backgroundColor,
                    chipNodeActivatedBackgroundColor: o5.activatedBackgroundColor,
                    chipNodeRadius: o5.borderRadius,
                    onClose: o5.onClose,
                    onClicked: o5.onClicked,
                }, undefined, m5, () => {
                }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 219, col: 3 });
                ViewPU.create(p5);
                let q5 = () => {
                    return {
                        chipSize: o5.size,
                        prefixIcon: o5.prefixIcon,
                        prefixSymbol: o5.prefixSymbol,
                        label: o5.label,
                        suffixIcon: o5.suffixIcon,
                        suffixSymbol: o5.suffixSymbol,
                        allowClose: o5.allowClose,
                        chipEnabled: o5.enabled,
                        chipActivated: o5.activated,
                        chipNodeBackgroundColor: o5.backgroundColor,
                        chipNodeActivatedBackgroundColor: o5.activatedBackgroundColor,
                        chipNodeRadius: o5.borderRadius,
                        onClose: o5.onClose,
                        onClicked: o5.onClicked
                    };
                };
                p5.paramsGenerator_ = q5;
            }
            else {
                (j5 ? j5 : this).updateStateVarsOfChildByElmtId(m5, {
                    chipSize: o5.size,
                    prefixIcon: o5.prefixIcon,
                    prefixSymbol: o5.prefixSymbol,
                    label: o5.label,
                    suffixIcon: o5.suffixIcon,
                    suffixSymbol: o5.suffixSymbol,
                    allowClose: o5.allowClose,
                    chipEnabled: o5.enabled,
                    chipActivated: o5.activated,
                    chipNodeBackgroundColor: o5.backgroundColor,
                    chipNodeActivatedBackgroundColor: o5.activatedBackgroundColor,
                    chipNodeRadius: o5.borderRadius
                });
            }
        }, { name: "ChipComponent" });
    }
}

export class ChipComponent extends ViewPU {
    constructor(b5, c5, d5, e5 = -1, f5 = undefined, g5) {
        super(b5, d5, e5, g5);
        if (typeof f5 === "function") {
            this.paramsGenerator_ = f5;
        }
        this.theme = defaultTheme;
        this.__chipSize = new SynchedPropertyObjectOneWayPU(c5.chipSize, this, "chipSize");
        this.__allowClose = new SynchedPropertySimpleOneWayPU(c5.allowClose, this, "allowClose");
        this.__prefixIcon = new SynchedPropertyObjectOneWayPU(c5.prefixIcon, this, "prefixIcon");
        this.__prefixSymbol = new SynchedPropertyObjectOneWayPU(c5.prefixSymbol, this, "prefixSymbol");
        this.__label = new SynchedPropertyObjectOneWayPU(c5.label, this, "label");
        this.__suffixIcon = new SynchedPropertyObjectOneWayPU(c5.suffixIcon, this, "suffixIcon");
        this.__suffixSymbol = new SynchedPropertyObjectOneWayPU(c5.suffixSymbol, this, "suffixSymbol");
        this.__chipNodeBackgroundColor = new SynchedPropertyObjectOneWayPU(c5.chipNodeBackgroundColor, this, "chipNodeBackgroundColor");
        this.__chipNodeActivatedBackgroundColor = new SynchedPropertyObjectOneWayPU(c5.chipNodeActivatedBackgroundColor, this, "chipNodeActivatedBackgroundColor");
        this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(c5.chipNodeRadius, this, "chipNodeRadius");
        this.__chipEnabled = new SynchedPropertySimpleOneWayPU(c5.chipEnabled, this, "chipEnabled");
        this.__chipActivated = new SynchedPropertySimpleOneWayPU(c5.chipActivated, this, "chipActivated");
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
        this.smListener = mediaquery.matchMediaSync("0vp<width<600vp");
        this.mdListener = mediaquery.matchMediaSync("600vp<=width<840vp");
        this.lgListener = mediaquery.matchMediaSync("840vp<=width");
        this.__isShowPressedBackGroundColor = new ObservedPropertySimplePU(false, this, "isShowPressedBackGroundColor");
        this.__fontSizeScale = new ObservedPropertyObjectPU(0, this, "fontSizeScale");
        this.__fontWeightScale = new ObservedPropertyObjectPU(0, this, "fontWeightScale");
        this.callbacks = {
            onConfigurationUpdated: (h5) => {
                this.fontSizeScale = h5.fontSizeScale;
                this.fontWeightScale = h5.fontWeightScale;
            },
            onMemoryLevel() {
            }
        };
        this.callbackId = undefined;
        this.__prefixSymbolWidth = new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById("PrefixSymbolGlyph")?.size?.width), this, "prefixSymbolWidth");
        this.__suffixSymbolWidth = new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById("SuffixSymbolGlyph")?.size?.width), this, "suffixSymbolWidth");
        this.setInitiallyProvidedValue(c5);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(a5) {
        if (a5.theme !== undefined) {
            this.theme = a5.theme;
        }
        if (a5.chipSize === undefined) {
            this.__chipSize.set(ChipSize.NORMAL);
        }
        if (a5.allowClose === undefined) {
            this.__allowClose.set(true);
        }
        if (a5.prefixIcon === undefined) {
            this.__prefixIcon.set({ src: "" });
        }
        if (a5.label === undefined) {
            this.__label.set({ text: "" });
        }
        if (a5.suffixIcon === undefined) {
            this.__suffixIcon.set({ src: "" });
        }
        if (a5.chipNodeBackgroundColor === undefined) {
            this.__chipNodeBackgroundColor.set(this.theme.chipNode.backgroundColor);
        }
        if (a5.chipNodeActivatedBackgroundColor === undefined) {
            this.__chipNodeActivatedBackgroundColor.set(this.theme.chipNode.activatedBackgroundColor);
        }
        if (a5.chipNodeRadius === undefined) {
            this.__chipNodeRadius.set(void (0));
        }
        if (a5.chipEnabled === undefined) {
            this.__chipEnabled.set(true);
        }
        if (a5.chipActivated === undefined) {
            this.__chipActivated.set(false);
        }
        if (a5.isHover !== undefined) {
            this.isHover = a5.isHover;
        }
        if (a5.chipScale !== undefined) {
            this.chipScale = a5.chipScale;
        }
        if (a5.chipOpacity !== undefined) {
            this.chipOpacity = a5.chipOpacity;
        }
        if (a5.chipBlendColor !== undefined) {
            this.chipBlendColor = a5.chipBlendColor;
        }
        if (a5.deleteChip !== undefined) {
            this.deleteChip = a5.deleteChip;
        }
        if (a5.chipNodeOnFocus !== undefined) {
            this.chipNodeOnFocus = a5.chipNodeOnFocus;
        }
        if (a5.useDefaultSuffixIcon !== undefined) {
            this.useDefaultSuffixIcon = a5.useDefaultSuffixIcon;
        }
        if (a5.chipNodeSize !== undefined) {
            this.chipNodeSize = a5.chipNodeSize;
        }
        if (a5.onClose !== undefined) {
            this.onClose = a5.onClose;
        }
        if (a5.onClicked !== undefined) {
            this.onClicked = a5.onClicked;
        }
        if (a5.suffixIconOnFocus !== undefined) {
            this.suffixIconOnFocus = a5.suffixIconOnFocus;
        }
        if (a5.chipBreakPoints !== undefined) {
            this.chipBreakPoints = a5.chipBreakPoints;
        }
        if (a5.smListener !== undefined) {
            this.smListener = a5.smListener;
        }
        if (a5.mdListener !== undefined) {
            this.mdListener = a5.mdListener;
        }
        if (a5.lgListener !== undefined) {
            this.lgListener = a5.lgListener;
        }
        if (a5.isShowPressedBackGroundColor !== undefined) {
            this.isShowPressedBackGroundColor = a5.isShowPressedBackGroundColor;
        }
        if (a5.fontSizeScale !== undefined) {
            this.fontSizeScale = a5.fontSizeScale;
        }
        if (a5.fontWeightScale !== undefined) {
            this.fontWeightScale = a5.fontWeightScale;
        }
        if (a5.callbacks !== undefined) {
            this.callbacks = a5.callbacks;
        }
        if (a5.callbackId !== undefined) {
            this.callbackId = a5.callbackId;
        }
        if (a5.prefixSymbolWidth !== undefined) {
            this.prefixSymbolWidth = a5.prefixSymbolWidth;
        }
        if (a5.suffixSymbolWidth !== undefined) {
            this.suffixSymbolWidth = a5.suffixSymbolWidth;
        }
    }

    updateStateVars(z4) {
        this.__chipSize.reset(z4.chipSize);
        this.__allowClose.reset(z4.allowClose);
        this.__prefixIcon.reset(z4.prefixIcon);
        this.__prefixSymbol.reset(z4.prefixSymbol);
        this.__label.reset(z4.label);
        this.__suffixIcon.reset(z4.suffixIcon);
        this.__suffixSymbol.reset(z4.suffixSymbol);
        this.__chipNodeBackgroundColor.reset(z4.chipNodeBackgroundColor);
        this.__chipNodeActivatedBackgroundColor.reset(z4.chipNodeActivatedBackgroundColor);
        this.__chipNodeRadius.reset(z4.chipNodeRadius);
        this.__chipEnabled.reset(z4.chipEnabled);
        this.__chipActivated.reset(z4.chipActivated);
    }

    purgeVariableDependenciesOnElmtId(y4) {
        this.__chipSize.purgeDependencyOnElmtId(y4);
        this.__allowClose.purgeDependencyOnElmtId(y4);
        this.__prefixIcon.purgeDependencyOnElmtId(y4);
        this.__prefixSymbol.purgeDependencyOnElmtId(y4);
        this.__label.purgeDependencyOnElmtId(y4);
        this.__suffixIcon.purgeDependencyOnElmtId(y4);
        this.__suffixSymbol.purgeDependencyOnElmtId(y4);
        this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(y4);
        this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(y4);
        this.__chipNodeRadius.purgeDependencyOnElmtId(y4);
        this.__chipEnabled.purgeDependencyOnElmtId(y4);
        this.__chipActivated.purgeDependencyOnElmtId(y4);
        this.__isHover.purgeDependencyOnElmtId(y4);
        this.__chipScale.purgeDependencyOnElmtId(y4);
        this.__chipOpacity.purgeDependencyOnElmtId(y4);
        this.__chipBlendColor.purgeDependencyOnElmtId(y4);
        this.__deleteChip.purgeDependencyOnElmtId(y4);
        this.__chipNodeOnFocus.purgeDependencyOnElmtId(y4);
        this.__useDefaultSuffixIcon.purgeDependencyOnElmtId(y4);
        this.__suffixIconOnFocus.purgeDependencyOnElmtId(y4);
        this.__chipBreakPoints.purgeDependencyOnElmtId(y4);
        this.__isShowPressedBackGroundColor.purgeDependencyOnElmtId(y4);
        this.__fontSizeScale.purgeDependencyOnElmtId(y4);
        this.__fontWeightScale.purgeDependencyOnElmtId(y4);
        this.__prefixSymbolWidth.purgeDependencyOnElmtId(y4);
        this.__suffixSymbolWidth.purgeDependencyOnElmtId(y4);
    }

    aboutToBeDeleted() {
        this.__chipSize.aboutToBeDeleted();
        this.__allowClose.aboutToBeDeleted();
        this.__prefixIcon.aboutToBeDeleted();
        this.__prefixSymbol.aboutToBeDeleted();
        this.__label.aboutToBeDeleted();
        this.__suffixIcon.aboutToBeDeleted();
        this.__suffixSymbol.aboutToBeDeleted();
        this.__chipNodeBackgroundColor.aboutToBeDeleted();
        this.__chipNodeActivatedBackgroundColor.aboutToBeDeleted();
        this.__chipNodeRadius.aboutToBeDeleted();
        this.__chipEnabled.aboutToBeDeleted();
        this.__chipActivated.aboutToBeDeleted();
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get chipSize() {
        return this.__chipSize.get();
    }

    set chipSize(x4) {
        this.__chipSize.set(x4);
    }

    get allowClose() {
        return this.__allowClose.get();
    }

    set allowClose(w4) {
        this.__allowClose.set(w4);
    }

    get prefixIcon() {
        return this.__prefixIcon.get();
    }

    set prefixIcon(v4) {
        this.__prefixIcon.set(v4);
    }

    get prefixSymbol() {
        return this.__prefixSymbol.get();
    }

    set prefixSymbol(u4) {
        this.__prefixSymbol.set(u4);
    }

    get label() {
        return this.__label.get();
    }

    set label(t4) {
        this.__label.set(t4);
    }

    get suffixIcon() {
        return this.__suffixIcon.get();
    }

    set suffixIcon(s4) {
        this.__suffixIcon.set(s4);
    }

    get suffixSymbol() {
        return this.__suffixSymbol.get();
    }

    set suffixSymbol(r4) {
        this.__suffixSymbol.set(r4);
    }

    get chipNodeBackgroundColor() {
        return this.__chipNodeBackgroundColor.get();
    }

    set chipNodeBackgroundColor(q4) {
        this.__chipNodeBackgroundColor.set(q4);
    }

    get chipNodeActivatedBackgroundColor() {
        return this.__chipNodeActivatedBackgroundColor.get();
    }

    set chipNodeActivatedBackgroundColor(p4) {
        this.__chipNodeActivatedBackgroundColor.set(p4);
    }

    get chipNodeRadius() {
        return this.__chipNodeRadius.get();
    }

    set chipNodeRadius(o4) {
        this.__chipNodeRadius.set(o4);
    }

    get chipEnabled() {
        return this.__chipEnabled.get();
    }

    set chipEnabled(n4) {
        this.__chipEnabled.set(n4);
    }

    get chipActivated() {
        return this.__chipActivated.get();
    }

    set chipActivated(m4) {
        this.__chipActivated.set(m4);
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

    isChipSizeEnum() {
        return typeof (this.chipSize) === 'string';
    }

    getLabelFontSize() {
        if (this.label?.fontSize !== void (0) && this.toVp(this.label.fontSize) >= 0) {
            return this.label.fontSize;
        }
        else {
            if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
                try {
                    resourceManager.getSystemResourceManager()
                        .getNumberByName((this.theme.label.smallFontSize.params[0]).split('.')[2]);
                    return this.theme.label.smallFontSize;
                }
                catch (x3) {
                    return this.theme.label.defaultFontSize;
                }
            }
            else {
                try {
                    resourceManager.getSystemResourceManager()
                        .getNumberByName((this.theme.label.normalFontSize.params[0]).split('.')[2]);
                    return this.theme.label.normalFontSize;
                }
                catch (w3) {
                    return this.theme.label.defaultFontSize;
                }
            }
        }
    }

    getLabelFontColor() {
        if (this.getChipActive()) {
            return this.label?.activatedFontColor ?? this.theme.label.activatedFontColor;
        }
        return this.label?.fontColor ?? this.theme.label.fontColor;
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

    toVp(q3) {
        if (q3 === void (0)) {
            return Number.NEGATIVE_INFINITY;
        }
        switch (typeof (q3)) {
            case 'number':
                return q3;
            case 'object':
                try {
                    if (q3.id !== -1) {
                        return px2vp(getContext(this).resourceManager.getNumber(q3.id));
                    }
                    else {
                        return px2vp(getContext(this)
                            .resourceManager
                            .getNumberByName((q3.params[0]).split('.')[2]));
                    }
                }
                catch (v3) {
                    return Number.NEGATIVE_INFINITY;
                }
            case 'string':
                let r3 = new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i");
                let s3 = q3.match(r3);
                if (!s3) {
                    return Number.NEGATIVE_INFINITY;
                }
                let t3 = Number(s3?.[1] ?? 0);
                let u3 = s3?.[2] ?? 'vp';
                switch (u3.toLowerCase()) {
                    case 'px':
                        t3 = px2vp(t3);
                        break;
                    case 'fp':
                        t3 = px2vp(fp2px(t3));
                        break;
                    case 'lpx':
                        t3 = px2vp(lpx2px(t3));
                        break;
                    case '%':
                        t3 = Number.NEGATIVE_INFINITY;
                        break;
                    case 'vp':
                        break;
                    default:
                        break;
                }
                return t3;
            default:
                return Number.NEGATIVE_INFINITY;
        }
    }

    getLabelMargin() {
        let p3 = { left: 0, right: 0 };
        if (this.label?.labelMargin?.left !== void (0) && this.toVp(this.label.labelMargin.left) >= 0) {
            p3.left = this.label?.labelMargin?.left;
        }
        else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                p3.left = this.theme.label.smallMargin.left;
            }
            else {
                p3.left = this.theme.label.normalMargin.left;
            }
        }
        if (this.label?.labelMargin?.right !== void (0) && this.toVp(this.label.labelMargin.right) >= 0) {
            p3.right = this.label?.labelMargin?.right;
        }
        else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
            this.suffixIcon?.src || this.useDefaultSuffixIcon) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                p3.right = this.theme.label.smallMargin.right;
            }
            else {
                p3.right = this.theme.label.normalMargin.right;
            }
        }
        return p3;
    }

    getSuffixIconSize() {
        let o3 = { width: 0, height: 0 };
        if (this.suffixIcon?.size?.width !== void (0) && this.toVp(this.suffixIcon?.size?.width) >= 0) {
            o3.width = this.suffixIcon?.size?.width;
        }
        else {
            if (this.getSuffixIconSrc()) {
                o3.width = this.theme.suffixIcon.size.width;
            }
            else {
                o3.width = 0;
            }
        }
        if (this.suffixIcon?.size?.height !== void (0) && this.toVp(this.suffixIcon?.size?.height) >= 0) {
            o3.height = this.suffixIcon?.size?.height;
        }
        else {
            if (this.getSuffixIconSrc()) {
                o3.height = this.theme.suffixIcon.size.height;
            }
            else {
                o3.height = 0;
            }
        }
        return o3;
    }

    getPrefixIconSize() {
        let n3 = { width: 0, height: 0 };
        if (this.prefixIcon?.size?.width !== void (0) && this.toVp(this.prefixIcon?.size?.width) >= 0) {
            n3.width = this.prefixIcon?.size?.width;
        }
        else {
            if (this.prefixIcon?.src) {
                n3.width = this.theme.prefixIcon.size.width;
            }
            else {
                n3.width = 0;
            }
        }
        if (this.prefixIcon?.size?.height !== void (0) && this.toVp(this.prefixIcon?.size?.height) >= 0) {
            n3.height = this.prefixIcon?.size?.height;
        }
        else {
            if (this.prefixIcon?.src) {
                n3.height = this.theme.prefixIcon.size.height;
            }
            else {
                n3.height = 0;
            }
        }
        return n3;
    }

    getPrefixIconFilledColor() {
        if (this.getChipActive()) {
            return this.prefixIcon?.activatedFillColor ?? this.theme.prefixIcon.activatedFillColor;
        }
        return this.prefixIcon?.fillColor ?? this.theme.prefixIcon.fillColor;
    }

    getSuffixIconFilledColor() {
        if (this.getChipActive()) {
            return this.suffixIcon?.activatedFillColor ?? this.theme.suffixIcon.activatedFillColor;
        }
        return this.suffixIcon?.fillColor ?? this.theme.suffixIcon.fillColor;
    }

    getDefaultSymbolColor() {
        if (this.getChipActive()) {
            return this.theme.defaultSymbol.activatedFontColor;
        }
        return this.theme.defaultSymbol.normalFontColor;
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
        return (this.useDefaultSuffixIcon && this.allowClose) || this.suffixIcon?.action !== void (0);
    }

    getChipNodePadding() {
        return (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) ? this.theme.chipNode.smallPadding : this.theme.chipNode.normalPadding;
    }

    getChipNodeRadius() {
        if (this.chipNodeRadius !== void (0) && this.toVp(this.chipNodeRadius) >= 0) {
            return this.chipNodeRadius;
        }
        else {
            return ((this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) ? this.theme.chipNode.smallBorderRadius : this.theme.chipNode.normalBorderRadius);
        }
    }

    getChipNodeBackGroundColor() {
        let k3;
        if (this.getChipActive()) {
            k3 = this.chipNodeActivatedBackgroundColor ?? this.theme.chipNode.activatedBackgroundColor;
        }
        else {
            k3 = this.chipNodeBackgroundColor ?? this.theme.chipNode.backgroundColor;
        }
        if (!this.isShowPressedBackGroundColor) {
            return k3;
        }
        let l3;
        try {
            l3 = ColorMetrics.resourceColor(k3);
        }
        catch (m3) {
            hilog.error(0x3900, 'Ace', `Chip resourceColor, error: ${m3.toString()}`);
            if (this.getChipActive()) {
                l3 = ColorMetrics.resourceColor(this.theme.chipNode.activatedBackgroundColor);
            }
            else {
                l3 = ColorMetrics.resourceColor(this.theme.chipNode.backgroundColor);
            }
        }
        return l3.blendColor(ColorMetrics.resourceColor("#19000000"))
            .color;
    }

    getChipNodeHeight() {
        if (this.isChipSizeEnum()) {
            return this.chipSize === ChipSize.SMALL ? this.theme.chipNode.smallHeight : this.theme.chipNode.normalHeight;
        }
        else {
            this.chipNodeSize = this.chipSize;
            return (this.chipNodeSize?.height !== void (0) && this.toVp(this.chipNodeSize?.height) >= 0) ? this.toVp(this.chipNodeSize?.height) : this.theme.chipNode.normalHeight;
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
        let j3 = 0;
        j3 += this.getChipNodePadding().left;
        j3 += this.toVp(this.getPrefixChipWidth());
        j3 += this.toVp(this.getLabelMargin().left);
        j3 += this.getLabelWidth();
        j3 += this.toVp(this.getLabelMargin().right);
        j3 += this.toVp(this.getSuffixChipWidth());
        j3 += this.getChipNodePadding().right;
        return j3;
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
        else if (!this.suffixIcon?.src && this.allowClose) {
            return this.theme.defaultSymbol.fontSize;
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

    handleTouch(i3) {
        if (!this.getChipEnable()) {
            return;
        }
        if (this.isHover) {
            if (i3.type === TouchType.Down) {
                this.isShowPressedBackGroundColor = true;
            }
            else if (i3.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            }
        }
        else {
            if (i3.type === TouchType.Down) {
                this.isShowPressedBackGroundColor = true;
            }
            else if (i3.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            }
        }
    }

    hoverAnimate(h3) {
        if (!this.getChipEnable()) {
            return;
        }
        this.isHover = h3;
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
        Context.animateTo({ duration: 150, curve: Curve.FastOutLinearIn, onFinish: () => {
            this.deleteChip = true;
        } }, () => {
            this.chipScale = { x: 0.85, y: 0.85 };
        });
    }

    getSuffixIconSrc() {
        this.useDefaultSuffixIcon = !this.suffixIcon?.src && this.allowClose;
        return this.useDefaultSuffixIcon ? this.theme.suffixIcon.defaultDeleteIcon : (this.suffixIcon?.src ?? void (0));
    }

    getChipNodeWidth() {
        if (!this.isChipSizeEnum()) {
            this.chipNodeSize = this.chipSize;
            if (this.chipNodeSize?.width !== void (0) && this.toVp(this.chipNodeSize.width) >= 0) {
                return this.toVp(this.chipNodeSize.width);
            }
        }
        let e3 = this.getChipConstraintWidth();
        return Math.min(Math.max(this.getCalculateChipNodeWidth(), e3.minWidth), e3.maxWidth);
    }

    getFocusOverlaySize() {
        return {
            width: Math.max(this.getChipNodeWidth(), this.getChipConstraintWidth().minWidth) + 8,
            height: this.getChipNodeHeight() + 8
        };
    }

    getChipConstraintWidth() {
        let b3 = this.getReserveChipNodeWidth();
        let c3 = this.getCalculateChipNodeWidth();
        let d3;
        switch (this.chipBreakPoints) {
            case BreakPointsType.SM:
                d3 = {
                    minWidth: b3,
                    maxWidth: Math.min(c3, this.theme.chipNode.breakPointConstraintWidth.breakPointSmMaxWidth)
                };
                break;
            case BreakPointsType.MD:
                d3 = {
                    minWidth: Math.max(c3, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(c3, this.theme.chipNode.breakPointConstraintWidth.breakPointMdMaxWidth)
                };
                break;
            case BreakPointsType.LG:
                d3 = {
                    minWidth: Math.max(c3, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(c3, this.theme.chipNode.breakPointConstraintWidth.breakPointLgMaxWidth)
                };
                break;
            default:
                d3 = { minWidth: b3, maxWidth: c3 };
                break;
        }
        d3.minWidth = Math.min(Math.max(this.getCalculateChipNodeWidth(), d3.minWidth), d3.maxWidth);
        d3.minHeight = this.getChipNodeHeight();
        if (!this.isChipSizeEnum() && this.chipNodeSize?.height !== void (0) && this.toVp(this.chipNodeSize?.height) >= 0) {
            d3.maxHeight = this.toVp(this.chipNodeSize.height);
            d3.minHeight = this.toVp(this.chipNodeSize.height);
        }
        if (!this.isChipSizeEnum() && this.chipNodeSize?.width !== void (0) && this.toVp(this.chipNodeSize?.width) >= 0) {
            d3.minWidth = this.toVp(this.chipNodeSize.width);
            d3.maxWidth = this.toVp(this.chipNodeSize.width);
        }
        else if (this.toVp(this.fontSizeScale) >= this.theme.chipNode.suitAgeScale) {
            d3.minWidth = void (0);
            d3.maxWidth = void (0);
        }
        return d3;
    }

    focusOverlay(p2 = null) {
        this.observeComponentCreation2((z2, a3) => {
            Stack.create();
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((s2, t2) => {
            If.create();
            if (this.chipNodeOnFocus && !this.suffixIconOnFocus) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x2, y2) => {
                        Stack.create();
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
        this.smListener.on("change", (o2) => {
            if (o2.matches) {
                this.chipBreakPoints = BreakPointsType.SM;
            }
        });
        this.mdListener.on("change", (n2) => {
            if (n2.matches) {
                this.chipBreakPoints = BreakPointsType.MD;
            }
        });
        this.lgListener.on("change", (m2) => {
            if (m2.matches) {
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

    chipBuilder(f = null) {
        this.observeComponentCreation2((z1, a2) => {
            Button.createWithChild();
            Button.type(ButtonType.Normal);
            Button.clip(false);
            Button.backgroundColor(this.getChipNodeBackGroundColor());
            Button.borderRadius(this.getChipNodeRadius());
            Button.enabled(this.getChipEnable());
            Button.scale(ObservedObject.GetRawObject(this.chipScale));
            Button.focusable(true);
            Button.opacity(this.getChipNodeOpacity());
            Button.onFocus(() => {
                this.chipNodeOnFocus = true;
            });
            Button.onBlur(() => {
                this.chipNodeOnFocus = false;
            });
            Button.onTouch((i2) => {
                this.handleTouch(i2);
            });
            Button.onHover((h2) => {
                if (this.isShowPressedBackGroundColor == false) {
                    this.isShowPressedBackGroundColor = true;
                }
                else {
                    this.isShowPressedBackGroundColor = false;
                }
            });
            Button.onKeyEvent((g2) => {
                if (g2.type === KeyType.Down && g2.keyCode === KeyCode.KEYCODE_FORWARD_DEL && !this.suffixIconOnFocus) {
                    this.deleteChipNodeAnimate();
                }
            });
            Button.onClick(this.onClicked === noop ? undefined : this.onClicked.bind(this));
        }, Button);
        this.observeComponentCreation2((x1, y1) => {
            Row.create();
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.Center);
            Row.padding(this.getChipNodePadding());
            Row.constraintSize(this.getChipConstraintWidth());
        }, Row);
        this.observeComponentCreation2((j1, k1) => {
            If.create();
            if (this.prefixSymbol?.normal || this.prefixSymbol?.activated) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s1, t1) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.theme.defaultSymbol.fontSize);
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor());
                        SymbolGlyph.attributeModifier.bind(this)(this.getPrefixSymbolModifier());
                        SymbolGlyph.onSizeChange((v1, w1) => {
                            this.prefixSymbolWidth = w1?.width;
                        });
                        SymbolGlyph.key("PrefixSymbolGlyph");
                    }, SymbolGlyph);
                });
            }
            else if (this.prefixIcon?.src !== "") {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((o1, p1) => {
                        Image.create(this.prefixIcon?.src);
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
        this.observeComponentCreation2((h1, i1) => {
            Text.create(this.label?.text ?? "");
            Text.opacity(this.getChipNodeOpacity());
            Text.fontSize(this.getLabelFontSize());
            Text.fontColor(this.getLabelFontColor());
            Text.fontFamily(this.getLabelFontFamily());
            Text.fontWeight(this.getLabelFontWeight());
            Text.margin(this.getLabelMargin());
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
        this.observeComponentCreation2((l, m) => {
            If.create();
            if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c1, d1) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.theme.defaultSymbol.fontSize);
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor());
                        SymbolGlyph.attributeModifier.bind(this)(this.getSuffixSymbolModifier());
                        SymbolGlyph.onSizeChange((f1, g1) => {
                            this.suffixSymbolWidth = g1?.width;
                        });
                        SymbolGlyph.key("SuffixSymbolGlyph");
                    }, SymbolGlyph);
                });
            }
            else if (this.suffixIcon?.src !== "") {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((v, w) => {
                        Image.create(this.getSuffixIconSrc());
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
                            if (this.allowClose && this.useDefaultSuffixIcon) {
                                this.onClose();
                                this.deleteChipNodeAnimate();
                                return;
                            }
                            this.onClicked();
                        });
                    }, Image);
                });
            }
            else if (this.allowClose) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((q, r) => {
                        SymbolGlyph.create({
                            "id": -1,
                            "type": 40000,
                            params: ['sys.symbol.xmark'],
                            "bundleName": "__harDefaultBundleName__",
                            "moduleName": "__harDefaultModuleName__"
                        });
                        SymbolGlyph.fontSize(this.theme.defaultSymbol.fontSize);
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor());
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
        this.observeComponentCreation2((b, c) => {
            If.create();
            if (!this.deleteChip) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.chipBuilder.bind(this)(this);
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
