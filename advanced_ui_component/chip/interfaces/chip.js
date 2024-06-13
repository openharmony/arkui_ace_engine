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

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}

export var ChipSize;
(function (d6) {
    d6["NORMAL"] = "NORMAL";
    d6["SMALL"] = "SMALL";
})(ChipSize || (ChipSize = {}));
var BreakPointsType;
(function (c6) {
    c6["SM"] = "SM";
    c6["MD"] = "MD";
    c6["LG"] = "LG";
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
        localizedNormalMargin: {
            start: LengthMetrics.vp(6),
            end: LengthMetrics.vp(6),
            top: LengthMetrics.vp(0),
            bottom: LengthMetrics.vp(0)
        },
        localizedSmallMargin: {
            start: LengthMetrics.vp(4),
            end: LengthMetrics.vp(4),
            top: LengthMetrics.vp(0),
            bottom: LengthMetrics.vp(0),
        }
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
        defaultEffect: -1,
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
        localizedNormalPadding: {
            start: LengthMetrics.vp(16),
            end: LengthMetrics.vp(16),
            top: LengthMetrics.vp(4),
            bottom: LengthMetrics.vp(4)
        },
        localizedSmallPadding: {
            start: LengthMetrics.vp(12),
            end: LengthMetrics.vp(12),
            top: LengthMetrics.vp(4),
            bottom: LengthMetrics.vp(4)
        },
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

export function Chip(r5, s5 = null) {
    const t5 = r5;
    {
        (s5 ? s5 : this).observeComponentCreation2((v5, w5, x5 = t5) => {
            if (w5) {
                let y5 = new ChipComponent(typeof PUV2ViewBase !== "undefined" && s5 instanceof PUV2ViewBase ? s5 : this, {
                    chipSize: x5.size,
                    prefixIcon: x5.prefixIcon,
                    prefixSymbol: x5.prefixSymbol,
                    label: x5.label,
                    suffixIcon: x5.suffixIcon,
                    suffixSymbol: x5.suffixSymbol,
                    allowClose: x5.allowClose,
                    chipEnabled: x5.enabled,
                    chipActivated: x5.activated,
                    chipNodeBackgroundColor: x5.backgroundColor,
                    chipNodeActivatedBackgroundColor: x5.activatedBackgroundColor,
                    chipNodeRadius: x5.borderRadius,
                    chipDirection: x5.direction,
                    onClose: x5.onClose,
                    onClicked: x5.onClicked,
                }, undefined, v5, () => {
                }, { page: "library/src/main/ets/components/chip/chip.ets", line: 250, col: 3 });
                ViewPU.create(y5);
                let z5 = () => {
                    return {
                        chipSize: x5.size,
                        prefixIcon: x5.prefixIcon,
                        prefixSymbol: x5.prefixSymbol,
                        label: x5.label,
                        suffixIcon: x5.suffixIcon,
                        suffixSymbol: x5.suffixSymbol,
                        allowClose: x5.allowClose,
                        chipEnabled: x5.enabled,
                        chipActivated: x5.activated,
                        chipNodeBackgroundColor: x5.backgroundColor,
                        chipNodeActivatedBackgroundColor: x5.activatedBackgroundColor,
                        chipNodeRadius: x5.borderRadius,
                        chipDirection: x5.direction,
                        onClose: x5.onClose,
                        onClicked: x5.onClicked
                    };
                };
                y5.paramsGenerator_ = z5;
            }
            else {
                (s5 ? s5 : this).updateStateVarsOfChildByElmtId(v5, {
                    chipSize: x5.size,
                    prefixIcon: x5.prefixIcon,
                    prefixSymbol: x5.prefixSymbol,
                    label: x5.label,
                    suffixIcon: x5.suffixIcon,
                    suffixSymbol: x5.suffixSymbol,
                    allowClose: x5.allowClose,
                    chipEnabled: x5.enabled,
                    chipActivated: x5.activated,
                    chipNodeBackgroundColor: x5.backgroundColor,
                    chipNodeActivatedBackgroundColor: x5.activatedBackgroundColor,
                    chipNodeRadius: x5.borderRadius,
                    chipDirection: x5.direction
                });
            }
        }, { name: "ChipComponent" });
    }
}

export class ChipComponent extends ViewPU {
    constructor(k5, l5, m5, n5 = -1, o5 = undefined, p5) {
        super(k5, m5, n5, p5);
        if (typeof o5 === "function") {
            this.paramsGenerator_ = o5;
        }
        this.theme = defaultTheme;
        this.__chipSize = new SynchedPropertyObjectOneWayPU(l5.chipSize, this, "chipSize");
        this.__allowClose = new SynchedPropertySimpleOneWayPU(l5.allowClose, this, "allowClose");
        this.__chipDirection = new SynchedPropertySimpleOneWayPU(l5.chipDirection, this, "chipDirection");
        this.__prefixIcon = new SynchedPropertyObjectOneWayPU(l5.prefixIcon, this, "prefixIcon");
        this.__prefixSymbol = new SynchedPropertyObjectOneWayPU(l5.prefixSymbol, this, "prefixSymbol");
        this.__label = new SynchedPropertyObjectOneWayPU(l5.label, this, "label");
        this.__suffixIcon = new SynchedPropertyObjectOneWayPU(l5.suffixIcon, this, "suffixIcon");
        this.__suffixSymbol = new SynchedPropertyObjectOneWayPU(l5.suffixSymbol, this, "suffixSymbol");
        this.__chipNodeBackgroundColor = new SynchedPropertyObjectOneWayPU(l5.chipNodeBackgroundColor, this, "chipNodeBackgroundColor");
        this.__chipNodeActivatedBackgroundColor = new SynchedPropertyObjectOneWayPU(l5.chipNodeActivatedBackgroundColor, this, "chipNodeActivatedBackgroundColor");
        this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(l5.chipNodeRadius, this, "chipNodeRadius");
        this.__chipEnabled = new SynchedPropertySimpleOneWayPU(l5.chipEnabled, this, "chipEnabled");
        this.__chipActivated = new SynchedPropertySimpleOneWayPU(l5.chipActivated, this, "chipActivated");
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
            onConfigurationUpdated: (q5) => {
                this.fontSizeScale = q5.fontSizeScale;
                this.fontWeightScale = q5.fontWeightScale;
            },
            onMemoryLevel() {
            }
        };
        this.callbackId = undefined;
        this.__prefixSymbolWidth = new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById("PrefixSymbolGlyph")?.size?.width), this, "prefixSymbolWidth");
        this.__suffixSymbolWidth = new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById("SuffixSymbolGlyph")?.size?.width), this, "suffixSymbolWidth");
        this.__symbolEffect = new ObservedPropertyObjectPU(new SymbolEffect(), this, "symbolEffect");
        this.setInitiallyProvidedValue(l5);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(j5) {
        if (j5.theme !== undefined) {
            this.theme = j5.theme;
        }
        if (j5.chipSize === undefined) {
            this.__chipSize.set(ChipSize.NORMAL);
        }
        if (j5.allowClose === undefined) {
            this.__allowClose.set(true);
        }
        if (j5.chipDirection === undefined) {
            this.__chipDirection.set(Direction.Auto);
        }
        if (j5.prefixIcon === undefined) {
            this.__prefixIcon.set({ src: "" });
        }
        if (j5.label === undefined) {
            this.__label.set({ text: "" });
        }
        if (j5.suffixIcon === undefined) {
            this.__suffixIcon.set({ src: "" });
        }
        if (j5.chipNodeBackgroundColor === undefined) {
            this.__chipNodeBackgroundColor.set(this.theme.chipNode.backgroundColor);
        }
        if (j5.chipNodeActivatedBackgroundColor === undefined) {
            this.__chipNodeActivatedBackgroundColor.set(this.theme.chipNode.activatedBackgroundColor);
        }
        if (j5.chipNodeRadius === undefined) {
            this.__chipNodeRadius.set(void (0));
        }
        if (j5.chipEnabled === undefined) {
            this.__chipEnabled.set(true);
        }
        if (j5.chipActivated === undefined) {
            this.__chipActivated.set(false);
        }
        if (j5.isHover !== undefined) {
            this.isHover = j5.isHover;
        }
        if (j5.chipScale !== undefined) {
            this.chipScale = j5.chipScale;
        }
        if (j5.chipOpacity !== undefined) {
            this.chipOpacity = j5.chipOpacity;
        }
        if (j5.chipBlendColor !== undefined) {
            this.chipBlendColor = j5.chipBlendColor;
        }
        if (j5.deleteChip !== undefined) {
            this.deleteChip = j5.deleteChip;
        }
        if (j5.chipNodeOnFocus !== undefined) {
            this.chipNodeOnFocus = j5.chipNodeOnFocus;
        }
        if (j5.useDefaultSuffixIcon !== undefined) {
            this.useDefaultSuffixIcon = j5.useDefaultSuffixIcon;
        }
        if (j5.chipNodeSize !== undefined) {
            this.chipNodeSize = j5.chipNodeSize;
        }
        if (j5.onClose !== undefined) {
            this.onClose = j5.onClose;
        }
        if (j5.onClicked !== undefined) {
            this.onClicked = j5.onClicked;
        }
        if (j5.suffixIconOnFocus !== undefined) {
            this.suffixIconOnFocus = j5.suffixIconOnFocus;
        }
        if (j5.chipBreakPoints !== undefined) {
            this.chipBreakPoints = j5.chipBreakPoints;
        }
        if (j5.smListener !== undefined) {
            this.smListener = j5.smListener;
        }
        if (j5.mdListener !== undefined) {
            this.mdListener = j5.mdListener;
        }
        if (j5.lgListener !== undefined) {
            this.lgListener = j5.lgListener;
        }
        if (j5.isShowPressedBackGroundColor !== undefined) {
            this.isShowPressedBackGroundColor = j5.isShowPressedBackGroundColor;
        }
        if (j5.fontSizeScale !== undefined) {
            this.fontSizeScale = j5.fontSizeScale;
        }
        if (j5.fontWeightScale !== undefined) {
            this.fontWeightScale = j5.fontWeightScale;
        }
        if (j5.callbacks !== undefined) {
            this.callbacks = j5.callbacks;
        }
        if (j5.callbackId !== undefined) {
            this.callbackId = j5.callbackId;
        }
        if (j5.prefixSymbolWidth !== undefined) {
            this.prefixSymbolWidth = j5.prefixSymbolWidth;
        }
        if (j5.suffixSymbolWidth !== undefined) {
            this.suffixSymbolWidth = j5.suffixSymbolWidth;
        }
        if (j5.symbolEffect !== undefined) {
            this.symbolEffect = j5.symbolEffect;
        }
    }

    updateStateVars(i5) {
        this.__chipSize.reset(i5.chipSize);
        this.__allowClose.reset(i5.allowClose);
        this.__chipDirection.reset(i5.chipDirection);
        this.__prefixIcon.reset(i5.prefixIcon);
        this.__prefixSymbol.reset(i5.prefixSymbol);
        this.__label.reset(i5.label);
        this.__suffixIcon.reset(i5.suffixIcon);
        this.__suffixSymbol.reset(i5.suffixSymbol);
        this.__chipNodeBackgroundColor.reset(i5.chipNodeBackgroundColor);
        this.__chipNodeActivatedBackgroundColor.reset(i5.chipNodeActivatedBackgroundColor);
        this.__chipNodeRadius.reset(i5.chipNodeRadius);
        this.__chipEnabled.reset(i5.chipEnabled);
        this.__chipActivated.reset(i5.chipActivated);
    }

    purgeVariableDependenciesOnElmtId(h5) {
        this.__chipSize.purgeDependencyOnElmtId(h5);
        this.__allowClose.purgeDependencyOnElmtId(h5);
        this.__chipDirection.purgeDependencyOnElmtId(h5);
        this.__prefixIcon.purgeDependencyOnElmtId(h5);
        this.__prefixSymbol.purgeDependencyOnElmtId(h5);
        this.__label.purgeDependencyOnElmtId(h5);
        this.__suffixIcon.purgeDependencyOnElmtId(h5);
        this.__suffixSymbol.purgeDependencyOnElmtId(h5);
        this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(h5);
        this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(h5);
        this.__chipNodeRadius.purgeDependencyOnElmtId(h5);
        this.__chipEnabled.purgeDependencyOnElmtId(h5);
        this.__chipActivated.purgeDependencyOnElmtId(h5);
        this.__isHover.purgeDependencyOnElmtId(h5);
        this.__chipScale.purgeDependencyOnElmtId(h5);
        this.__chipOpacity.purgeDependencyOnElmtId(h5);
        this.__chipBlendColor.purgeDependencyOnElmtId(h5);
        this.__deleteChip.purgeDependencyOnElmtId(h5);
        this.__chipNodeOnFocus.purgeDependencyOnElmtId(h5);
        this.__useDefaultSuffixIcon.purgeDependencyOnElmtId(h5);
        this.__suffixIconOnFocus.purgeDependencyOnElmtId(h5);
        this.__chipBreakPoints.purgeDependencyOnElmtId(h5);
        this.__isShowPressedBackGroundColor.purgeDependencyOnElmtId(h5);
        this.__fontSizeScale.purgeDependencyOnElmtId(h5);
        this.__fontWeightScale.purgeDependencyOnElmtId(h5);
        this.__prefixSymbolWidth.purgeDependencyOnElmtId(h5);
        this.__suffixSymbolWidth.purgeDependencyOnElmtId(h5);
        this.__symbolEffect.purgeDependencyOnElmtId(h5);
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
        this.__symbolEffect.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get chipSize() {
        return this.__chipSize.get();
    }

    set chipSize(g5) {
        this.__chipSize.set(g5);
    }

    get allowClose() {
        return this.__allowClose.get();
    }

    set allowClose(f5) {
        this.__allowClose.set(f5);
    }

    get chipDirection() {
        return this.__chipDirection.get();
    }

    set chipDirection(e5) {
        this.__chipDirection.set(e5);
    }

    get prefixIcon() {
        return this.__prefixIcon.get();
    }

    set prefixIcon(d5) {
        this.__prefixIcon.set(d5);
    }

    get prefixSymbol() {
        return this.__prefixSymbol.get();
    }

    set prefixSymbol(c5) {
        this.__prefixSymbol.set(c5);
    }

    get label() {
        return this.__label.get();
    }

    set label(b5) {
        this.__label.set(b5);
    }

    get suffixIcon() {
        return this.__suffixIcon.get();
    }

    set suffixIcon(a5) {
        this.__suffixIcon.set(a5);
    }

    get suffixSymbol() {
        return this.__suffixSymbol.get();
    }

    set suffixSymbol(z4) {
        this.__suffixSymbol.set(z4);
    }

    get chipNodeBackgroundColor() {
        return this.__chipNodeBackgroundColor.get();
    }

    set chipNodeBackgroundColor(y4) {
        this.__chipNodeBackgroundColor.set(y4);
    }

    get chipNodeActivatedBackgroundColor() {
        return this.__chipNodeActivatedBackgroundColor.get();
    }

    set chipNodeActivatedBackgroundColor(x4) {
        this.__chipNodeActivatedBackgroundColor.set(x4);
    }

    get chipNodeRadius() {
        return this.__chipNodeRadius.get();
    }

    set chipNodeRadius(w4) {
        this.__chipNodeRadius.set(w4);
    }

    get chipEnabled() {
        return this.__chipEnabled.get();
    }

    set chipEnabled(v4) {
        this.__chipEnabled.set(v4);
    }

    get chipActivated() {
        return this.__chipActivated.get();
    }

    set chipActivated(u4) {
        this.__chipActivated.set(u4);
    }

    get isHover() {
        return this.__isHover.get();
    }

    set isHover(t4) {
        this.__isHover.set(t4);
    }

    get chipScale() {
        return this.__chipScale.get();
    }

    set chipScale(s4) {
        this.__chipScale.set(s4);
    }

    get chipOpacity() {
        return this.__chipOpacity.get();
    }

    set chipOpacity(r4) {
        this.__chipOpacity.set(r4);
    }

    get chipBlendColor() {
        return this.__chipBlendColor.get();
    }

    set chipBlendColor(q4) {
        this.__chipBlendColor.set(q4);
    }

    get deleteChip() {
        return this.__deleteChip.get();
    }

    set deleteChip(p4) {
        this.__deleteChip.set(p4);
    }

    get chipNodeOnFocus() {
        return this.__chipNodeOnFocus.get();
    }

    set chipNodeOnFocus(o4) {
        this.__chipNodeOnFocus.set(o4);
    }

    get useDefaultSuffixIcon() {
        return this.__useDefaultSuffixIcon.get();
    }

    set useDefaultSuffixIcon(n4) {
        this.__useDefaultSuffixIcon.set(n4);
    }

    get suffixIconOnFocus() {
        return this.__suffixIconOnFocus.get();
    }

    set suffixIconOnFocus(m4) {
        this.__suffixIconOnFocus.set(m4);
    }

    get chipBreakPoints() {
        return this.__chipBreakPoints.get();
    }

    set chipBreakPoints(l4) {
        this.__chipBreakPoints.set(l4);
    }

    get isShowPressedBackGroundColor() {
        return this.__isShowPressedBackGroundColor.get();
    }

    set isShowPressedBackGroundColor(k4) {
        this.__isShowPressedBackGroundColor.set(k4);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(j4) {
        this.__fontSizeScale.set(j4);
    }

    get fontWeightScale() {
        return this.__fontWeightScale.get();
    }

    set fontWeightScale(i4) {
        this.__fontWeightScale.set(i4);
    }

    get prefixSymbolWidth() {
        return this.__prefixSymbolWidth.get();
    }

    set prefixSymbolWidth(h4) {
        this.__prefixSymbolWidth.set(h4);
    }

    get suffixSymbolWidth() {
        return this.__suffixSymbolWidth.get();
    }

    set suffixSymbolWidth(g4) {
        this.__suffixSymbolWidth.set(g4);
    }

    get symbolEffect() {
        return this.__symbolEffect.get();
    }

    set symbolEffect(a6) {
        this.__symbolEffect.set(a6);
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
                catch (f4) {
                    return this.theme.label.defaultFontSize;
                }
            }
            else {
                try {
                    resourceManager.getSystemResourceManager()
                        .getNumberByName((this.theme.label.normalFontSize.params[0]).split('.')[2]);
                    return this.theme.label.normalFontSize;
                }
                catch (e4) {
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

    lengthMetricsToVp(c4) {
        let d4 = 0;
        if (c4) {
            switch (c4.unit) {
                case LengthUnit.PX:
                    return px2vp(c4.value);
                case LengthUnit.VP:
                    return c4.value;
                case LengthUnit.FP:
                    px2vp(fp2px(c4.value));
                    break;
                case LengthUnit.PERCENT:
                    return Number.NEGATIVE_INFINITY;
                case LengthUnit.LPX:
                    return px2vp(lpx2px(c4.value));
            }
        }
        return d4;
    }

    toVp(w3) {
        if (w3 === void (0)) {
            return Number.NEGATIVE_INFINITY;
        }
        switch (typeof (w3)) {
            case 'number':
                return w3;
            case 'object':
                try {
                    if (w3.id !== -1) {
                        return px2vp(getContext(this).resourceManager.getNumber(w3.id));
                    }
                    else {
                        return px2vp(getContext(this)
                            .resourceManager
                            .getNumberByName((w3.params[0]).split('.')[2]));
                    }
                }
                catch (b4) {
                    return Number.NEGATIVE_INFINITY;
                }
            case 'string':
                let x3 = new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i");
                let y3 = w3.match(x3);
                if (!y3) {
                    return Number.NEGATIVE_INFINITY;
                }
                let z3 = Number(y3?.[1] ?? 0);
                let a4 = y3?.[2] ?? 'vp';
                switch (a4.toLowerCase()) {
                    case 'px':
                        z3 = px2vp(z3);
                        break;
                    case 'fp':
                        z3 = px2vp(fp2px(z3));
                        break;
                    case 'lpx':
                        z3 = px2vp(lpx2px(z3));
                        break;
                    case '%':
                        z3 = Number.NEGATIVE_INFINITY;
                        break;
                    case 'vp':
                        break;
                    default:
                        break;
                }
                return z3;
            default:
                return Number.NEGATIVE_INFINITY;
        }
    }

    getLabelMargin() {
        let v3 = { left: 0, right: 0 };
        if (this.label?.labelMargin?.left !== void (0) && this.toVp(this.label.labelMargin.left) >= 0) {
            v3.left = this.label?.labelMargin?.left;
        }
        else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                v3.left = this.theme.label.smallMargin.left;
            }
            else {
                v3.left = this.theme.label.normalMargin.left;
            }
        }
        if (this.label?.labelMargin?.right !== void (0) && this.toVp(this.label.labelMargin.right) >= 0) {
            v3.right = this.label?.labelMargin?.right;
        }
        else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
            this.suffixIcon?.src || this.useDefaultSuffixIcon) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                v3.right = this.theme.label.smallMargin.right;
            }
            else {
                v3.right = this.theme.label.normalMargin.right;
            }
        }
        return v3;
    }

    getLocalizedLabelMargin() {
        let u3 = { start: LengthMetrics.vp(0), end: LengthMetrics.vp(0) };
        if (this.label?.localizedLabelMargin?.start.value !== void (0) &&
            this.lengthMetricsToVp(this.label.localizedLabelMargin.start) >= 0) {
            u3.start = this.label?.localizedLabelMargin?.start;
        }
        else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                u3.start = this.theme.label.localizedSmallMargin.start;
            }
            else {
                u3.start = this.theme.label.localizedNormalMargin.start;
            }
        }
        if (this.label?.localizedLabelMargin?.end.value !== void (0) &&
            this.lengthMetricsToVp(this.label.localizedLabelMargin.end) >= 0) {
            u3.end = this.label?.localizedLabelMargin?.end;
        }
        else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
            this.suffixIcon?.src || this.useDefaultSuffixIcon) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                u3.end = this.theme.label.localizedSmallMargin.end;
            }
            else {
                u3.end = this.theme.label.localizedNormalMargin.end;
            }
        }
        return u3;
    }

    getLabelStartEndVp() {
        let r3 = { start: LengthMetrics.vp(0), end: LengthMetrics.vp(0) };
        if (this.label && this.label.labelMargin) {
            let t3 = this.getLabelMargin();
            return { start: LengthMetrics.vp(this.toVp(t3.left)), end: LengthMetrics.vp(this.toVp(t3.right)) };
        }
        if (this.label && this.label.localizedLabelMargin) {
            let s3 = this.getLocalizedLabelMargin();
            return {
                start: LengthMetrics.vp(this.lengthMetricsToVp(s3.start)),
                end: LengthMetrics.vp(this.lengthMetricsToVp(s3.end))
            };
        }
        return r3;
    }

    getActualLabelMargin() {
        let q3 = this.getLocalizedLabelMargin();
        if (this.label && this.label.localizedLabelMargin) {
            return q3;
        }
        if (this.label && this.label.labelMargin) {
            return this.getLabelMargin();
        }
        return q3;
    }

    getSuffixIconSize() {
        let p3 = { width: 0, height: 0 };
        if (this.suffixIcon?.size?.width !== void (0) && this.toVp(this.suffixIcon?.size?.width) >= 0) {
            p3.width = this.suffixIcon?.size?.width;
        }
        else {
            if (this.getSuffixIconSrc()) {
                p3.width = this.theme.suffixIcon.size.width;
            }
            else {
                p3.width = 0;
            }
        }
        if (this.suffixIcon?.size?.height !== void (0) && this.toVp(this.suffixIcon?.size?.height) >= 0) {
            p3.height = this.suffixIcon?.size?.height;
        }
        else {
            if (this.getSuffixIconSrc()) {
                p3.height = this.theme.suffixIcon.size.height;
            }
            else {
                p3.height = 0;
            }
        }
        return p3;
    }

    getPrefixIconSize() {
        let o3 = { width: 0, height: 0 };
        if (this.prefixIcon?.size?.width !== void (0) && this.toVp(this.prefixIcon?.size?.width) >= 0) {
            o3.width = this.prefixIcon?.size?.width;
        }
        else {
            if (this.prefixIcon?.src) {
                o3.width = this.theme.prefixIcon.size.width;
            }
            else {
                o3.width = 0;
            }
        }
        if (this.prefixIcon?.size?.height !== void (0) && this.toVp(this.prefixIcon?.size?.height) >= 0) {
            o3.height = this.prefixIcon?.size?.height;
        }
        else {
            if (this.prefixIcon?.src) {
                o3.height = this.theme.prefixIcon.size.height;
            }
            else {
                o3.height = 0;
            }
        }
        return o3;
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
        return (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) ? this.theme.chipNode.localizedSmallPadding : this.theme.chipNode.localizedNormalPadding;
    }

    getChipNodeRadius() {
        if (this.chipNodeRadius !== void (0) && this.toVp(this.chipNodeRadius) >= 0) {
            return this.chipNodeRadius;
        }
        else {
            return ((this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) ?
            this.theme.chipNode.smallBorderRadius : this.theme.chipNode.normalBorderRadius);
        }
    }

    getChipNodeBackGroundColor() {
        let l3;
        if (this.getChipActive()) {
            l3 = this.chipNodeActivatedBackgroundColor ?? this.theme.chipNode.activatedBackgroundColor;
        }
        else {
            l3 = this.chipNodeBackgroundColor ?? this.theme.chipNode.backgroundColor;
        }
        let m3;
        try {
            m3 = ColorMetrics.resourceColor(l3);
        }
        catch (n3) {
            hilog.error(0x3900, 'Ace', `Chip resourceColor, error: ${n3.toString()}`);
            if (this.getChipActive()) {
                m3 = ColorMetrics.resourceColor(this.theme.chipNode.activatedBackgroundColor);
            }
            else {
                m3 = ColorMetrics.resourceColor(this.theme.chipNode.backgroundColor);
            }
        }
        if (!this.isShowPressedBackGroundColor) {
            return m3.color;
        }
        return m3.blendColor(ColorMetrics.resourceColor("#19000000"))
            .color;
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
        let j3 = 0;
        let k3 = this.getLabelStartEndVp();
        j3 += this.getChipNodePadding().start.value;
        j3 += this.toVp(this.getPrefixChipWidth());
        j3 += this.toVp(k3.start.value);
        j3 += this.getLabelWidth();
        j3 += this.toVp(k3.end.value);
        j3 += this.toVp(this.getSuffixChipWidth());
        j3 += this.getChipNodePadding().end.value;
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
        Context.animateTo({
            duration: 150, curve: Curve.FastOutLinearIn, onFinish: () => {
                this.deleteChip = true;
            }
        }, () => {
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
            Stack.direction(this.chipDirection);
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((s2, t2) => {
            If.create();
            if (this.chipNodeOnFocus && !this.suffixIconOnFocus) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x2, y2) => {
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
            Row.direction(this.chipDirection);
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
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), this.theme.defaultSymbol.defaultEffect);
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
                        Image.direction(this.chipDirection);
                        Image.matchTextDirection(this.chipDirection == Direction.Ltr ? false : true);
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
        this.observeComponentCreation2((l, m) => {
            If.create();
            if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c1, d1) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.theme.defaultSymbol.fontSize);
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor());
                        SymbolGlyph.attributeModifier.bind(this)(this.getSuffixSymbolModifier());
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                        SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), this.theme.defaultSymbol.defaultEffect);
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
                        Image.direction(this.chipDirection);
                        Image.matchTextDirection(this.chipDirection == Direction.Ltr ? false : true);
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