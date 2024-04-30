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

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}


export var ChipSize;
(function (l5) {
    l5["NORMAL"] = "NORMAL";
    l5["SMALL"] = "SMALL";
})(ChipSize || (ChipSize = {}));
var BreakPointsType;
(function (k5) {
    k5["SM"] = "SM";
    k5["MD"] = "MD";
    k5["LG"] = "LG";
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
        normalPadding: { left: 16, right: 16, top: 0, bottom: 0 },
        smallPadding: { left: 12, right: 12, top: 0, bottom: 0 },
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

export function Chip(a5, b5 = null) {
    const c5 = a5;
    {
        (b5 ? b5 : this).observeComponentCreation((e5, f5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e5);
            if (f5) {
                let g5 = new ChipComponent(b5 ? b5 : this, {
                    chipSize: a5.size,
                    prefixIcon: a5.prefixIcon,
                    prefixSymbol: a5.prefixSymbol,
                    label: a5.label,
                    suffixIcon: a5.suffixIcon,
                    suffixSymbol: a5.suffixSymbol,
                    allowClose: a5.allowClose,
                    chipEnabled: a5.enabled,
                    chipActivated: a5.activated,
                    chipNodeBackgroundColor: a5.backgroundColor,
                    chipNodeActivatedBackgroundColor: a5.activatedBackgroundColor,
                    chipNodeRadius: a5.borderRadius,
                    onClose: a5.onClose,
                    onClicked: a5.onClicked,
                }, undefined, e5, () => {
                }, { page: "library/src/main/ets/components/mainpage/chip.ets", line: 214, col: 3 });
                ViewPU.create(g5);
                let h5 = () => {
                    return {
                        chipSize: a5.size,
                        prefixIcon: a5.prefixIcon,
                        prefixSymbol: a5.prefixSymbol,
                        label: a5.label,
                        suffixIcon: a5.suffixIcon,
                        suffixSymbol: a5.suffixSymbol,
                        allowClose: a5.allowClose,
                        chipEnabled: a5.enabled,
                        chipActivated: a5.activated,
                        chipNodeBackgroundColor: a5.backgroundColor,
                        chipNodeActivatedBackgroundColor: a5.activatedBackgroundColor,
                        chipNodeRadius: a5.borderRadius,
                        onClose: a5.onClose,
                        onClicked: a5.onClicked
                    };
                };
                g5.paramsGenerator_ = h5;
            }
            else {
                (b5 ? b5 : this).updateStateVarsOfChildByElmtId(e5, {
                    chipSize: a5.size,
                    prefixIcon: a5.prefixIcon,
                    prefixSymbol: a5.prefixSymbol,
                    label: a5.label,
                    suffixIcon: a5.suffixIcon,
                    suffixSymbol: a5.suffixSymbol,
                    allowClose: a5.allowClose,
                    chipEnabled: a5.enabled,
                    chipActivated: a5.activated,
                    chipNodeBackgroundColor: a5.backgroundColor,
                    chipNodeActivatedBackgroundColor: a5.activatedBackgroundColor,
                    chipNodeRadius: a5.borderRadius
                });
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
    }
}

export class ChipComponent extends ViewPU {
    constructor(u4, v4, w4, x4 = -1, y4 = undefined, z4) {
        super(u4, w4, x4, z4);
        if (typeof y4 === "function") {
            this.paramsGenerator_ = y4;
        }
        this.theme = defaultTheme;
        this.__chipSize = new SynchedPropertyObjectOneWayPU(v4.chipSize, this, "chipSize");
        this.__allowClose = new SynchedPropertySimpleOneWayPU(v4.allowClose, this, "allowClose");
        this.__prefixIcon = new SynchedPropertyObjectOneWayPU(v4.prefixIcon, this, "prefixIcon");
        this.__prefixSymbol = new SynchedPropertyObjectOneWayPU(v4.prefixSymbol, this, "prefixSymbol");
        this.__label = new SynchedPropertyObjectOneWayPU(v4.label, this, "label");
        this.__suffixIcon = new SynchedPropertyObjectOneWayPU(v4.suffixIcon, this, "suffixIcon");
        this.__suffixSymbol = new SynchedPropertyObjectOneWayPU(v4.suffixSymbol, this, "suffixSymbol");
        this.__chipNodeBackgroundColor = new SynchedPropertyObjectOneWayPU(v4.chipNodeBackgroundColor, this, "chipNodeBackgroundColor");
        this.__chipNodeActivatedBackgroundColor = new SynchedPropertyObjectOneWayPU(v4.chipNodeActivatedBackgroundColor, this, "chipNodeActivatedBackgroundColor");
        this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(v4.chipNodeRadius, this, "chipNodeRadius");
        this.__chipEnabled = new SynchedPropertySimpleOneWayPU(v4.chipEnabled, this, "chipEnabled");
        this.__chipActivated = new SynchedPropertySimpleOneWayPU(v4.chipActivated, this, "chipActivated");
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
        this.__prefixSymbolWidth = new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById("PrefixSymbolGlyph")?.size?.width), this, "prefixSymbolWidth");
        this.__suffixSymbolWidth = new ObservedPropertyObjectPU(this.toVp(componentUtils.getRectangleById("SuffixSymbolGlyph")?.size?.width), this, "suffixSymbolWidth");
        this.setInitiallyProvidedValue(v4);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(t4) {
        if (t4.theme !== undefined) {
            this.theme = t4.theme;
        }
        if (t4.chipSize === undefined) {
            this.__chipSize.set(ChipSize.NORMAL);
        }
        if (t4.allowClose === undefined) {
            this.__allowClose.set(true);
        }
        if (t4.prefixIcon === undefined) {
            this.__prefixIcon.set({ src: "" });
        }
        if (t4.label === undefined) {
            this.__label.set({ text: "" });
        }
        if (t4.suffixIcon === undefined) {
            this.__suffixIcon.set({ src: "" });
        }
        if (t4.chipNodeBackgroundColor === undefined) {
            this.__chipNodeBackgroundColor.set(this.theme.chipNode.backgroundColor);
        }
        if (t4.chipNodeActivatedBackgroundColor === undefined) {
            this.__chipNodeActivatedBackgroundColor.set(this.theme.chipNode.activatedBackgroundColor);
        }
        if (t4.chipNodeRadius === undefined) {
            this.__chipNodeRadius.set(void (0));
        }
        if (t4.chipEnabled === undefined) {
            this.__chipEnabled.set(true);
        }
        if (t4.chipActivated === undefined) {
            this.__chipActivated.set(false);
        }
        if (t4.isHover !== undefined) {
            this.isHover = t4.isHover;
        }
        if (t4.chipScale !== undefined) {
            this.chipScale = t4.chipScale;
        }
        if (t4.chipOpacity !== undefined) {
            this.chipOpacity = t4.chipOpacity;
        }
        if (t4.chipBlendColor !== undefined) {
            this.chipBlendColor = t4.chipBlendColor;
        }
        if (t4.deleteChip !== undefined) {
            this.deleteChip = t4.deleteChip;
        }
        if (t4.chipNodeOnFocus !== undefined) {
            this.chipNodeOnFocus = t4.chipNodeOnFocus;
        }
        if (t4.useDefaultSuffixIcon !== undefined) {
            this.useDefaultSuffixIcon = t4.useDefaultSuffixIcon;
        }
        if (t4.chipNodeSize !== undefined) {
            this.chipNodeSize = t4.chipNodeSize;
        }
        if (t4.onClose !== undefined) {
            this.onClose = t4.onClose;
        }
        if (t4.onClicked !== undefined) {
            this.onClicked = t4.onClicked;
        }
        if (t4.suffixIconOnFocus !== undefined) {
            this.suffixIconOnFocus = t4.suffixIconOnFocus;
        }
        if (t4.chipBreakPoints !== undefined) {
            this.chipBreakPoints = t4.chipBreakPoints;
        }
        if (t4.smListener !== undefined) {
            this.smListener = t4.smListener;
        }
        if (t4.mdListener !== undefined) {
            this.mdListener = t4.mdListener;
        }
        if (t4.lgListener !== undefined) {
            this.lgListener = t4.lgListener;
        }
        if (t4.isShowPressedBackGroundColor !== undefined) {
            this.isShowPressedBackGroundColor = t4.isShowPressedBackGroundColor;
        }
        if (t4.prefixSymbolWidth !== undefined) {
            this.prefixSymbolWidth = t4.prefixSymbolWidth;
        }
        if (t4.suffixSymbolWidth !== undefined) {
            this.suffixSymbolWidth = t4.suffixSymbolWidth;
        }
    }

    updateStateVars(s4) {
        this.__chipSize.reset(s4.chipSize);
        this.__allowClose.reset(s4.allowClose);
        this.__prefixIcon.reset(s4.prefixIcon);
        this.__prefixSymbol.reset(s4.prefixSymbol);
        this.__label.reset(s4.label);
        this.__suffixIcon.reset(s4.suffixIcon);
        this.__suffixSymbol.reset(s4.suffixSymbol);
        this.__chipNodeBackgroundColor.reset(s4.chipNodeBackgroundColor);
        this.__chipNodeActivatedBackgroundColor.reset(s4.chipNodeActivatedBackgroundColor);
        this.__chipNodeRadius.reset(s4.chipNodeRadius);
        this.__chipEnabled.reset(s4.chipEnabled);
        this.__chipActivated.reset(s4.chipActivated);
    }

    purgeVariableDependenciesOnElmtId(r4) {
        this.__chipSize.purgeDependencyOnElmtId(r4);
        this.__allowClose.purgeDependencyOnElmtId(r4);
        this.__prefixIcon.purgeDependencyOnElmtId(r4);
        this.__prefixSymbol.purgeDependencyOnElmtId(r4);
        this.__label.purgeDependencyOnElmtId(r4);
        this.__suffixIcon.purgeDependencyOnElmtId(r4);
        this.__suffixSymbol.purgeDependencyOnElmtId(r4);
        this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(r4);
        this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(r4);
        this.__chipNodeRadius.purgeDependencyOnElmtId(r4);
        this.__chipEnabled.purgeDependencyOnElmtId(r4);
        this.__chipActivated.purgeDependencyOnElmtId(r4);
        this.__isHover.purgeDependencyOnElmtId(r4);
        this.__chipScale.purgeDependencyOnElmtId(r4);
        this.__chipOpacity.purgeDependencyOnElmtId(r4);
        this.__chipBlendColor.purgeDependencyOnElmtId(r4);
        this.__deleteChip.purgeDependencyOnElmtId(r4);
        this.__chipNodeOnFocus.purgeDependencyOnElmtId(r4);
        this.__useDefaultSuffixIcon.purgeDependencyOnElmtId(r4);
        this.__suffixIconOnFocus.purgeDependencyOnElmtId(r4);
        this.__chipBreakPoints.purgeDependencyOnElmtId(r4);
        this.__isShowPressedBackGroundColor.purgeDependencyOnElmtId(r4);
        this.__prefixSymbolWidth.purgeDependencyOnElmtId(r4);
        this.__suffixSymbolWidth.purgeDependencyOnElmtId(r4);
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
        this.__prefixSymbolWidth.aboutToBeDeleted();
        this.__suffixSymbolWidth.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get chipSize() {
        return this.__chipSize.get();
    }

    set chipSize(q4) {
        this.__chipSize.set(q4);
    }

    get allowClose() {
        return this.__allowClose.get();
    }

    set allowClose(p4) {
        this.__allowClose.set(p4);
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

    get chipNodeBackgroundColor() {
        return this.__chipNodeBackgroundColor.get();
    }

    set chipNodeBackgroundColor(j4) {
        this.__chipNodeBackgroundColor.set(j4);
    }

    get chipNodeActivatedBackgroundColor() {
        return this.__chipNodeActivatedBackgroundColor.get();
    }

    set chipNodeActivatedBackgroundColor(i4) {
        this.__chipNodeActivatedBackgroundColor.set(i4);
    }

    get chipNodeRadius() {
        return this.__chipNodeRadius.get();
    }

    set chipNodeRadius(h4) {
        this.__chipNodeRadius.set(h4);
    }

    get chipEnabled() {
        return this.__chipEnabled.get();
    }

    set chipEnabled(g4) {
        this.__chipEnabled.set(g4);
    }

    get chipActivated() {
        return this.__chipActivated.get();
    }

    set chipActivated(f4) {
        this.__chipActivated.set(f4);
    }

    get isHover() {
        return this.__isHover.get();
    }

    set isHover(e4) {
        this.__isHover.set(e4);
    }

    get chipScale() {
        return this.__chipScale.get();
    }

    set chipScale(d4) {
        this.__chipScale.set(d4);
    }

    get chipOpacity() {
        return this.__chipOpacity.get();
    }

    set chipOpacity(c4) {
        this.__chipOpacity.set(c4);
    }

    get chipBlendColor() {
        return this.__chipBlendColor.get();
    }

    set chipBlendColor(b4) {
        this.__chipBlendColor.set(b4);
    }

    get deleteChip() {
        return this.__deleteChip.get();
    }

    set deleteChip(a4) {
        this.__deleteChip.set(a4);
    }

    get chipNodeOnFocus() {
        return this.__chipNodeOnFocus.get();
    }

    set chipNodeOnFocus(z3) {
        this.__chipNodeOnFocus.set(z3);
    }

    get useDefaultSuffixIcon() {
        return this.__useDefaultSuffixIcon.get();
    }

    set useDefaultSuffixIcon(y3) {
        this.__useDefaultSuffixIcon.set(y3);
    }

    get suffixIconOnFocus() {
        return this.__suffixIconOnFocus.get();
    }

    set suffixIconOnFocus(x3) {
        this.__suffixIconOnFocus.set(x3);
    }

    get chipBreakPoints() {
        return this.__chipBreakPoints.get();
    }

    set chipBreakPoints(w3) {
        this.__chipBreakPoints.set(w3);
    }

    get isShowPressedBackGroundColor() {
        return this.__isShowPressedBackGroundColor.get();
    }

    set isShowPressedBackGroundColor(v3) {
        this.__isShowPressedBackGroundColor.set(v3);
    }

    get prefixSymbolWidth() {
        return this.__prefixSymbolWidth.get();
    }

    set prefixSymbolWidth(u3) {
        this.__prefixSymbolWidth.set(u3);
    }

    get suffixSymbolWidth() {
        return this.__suffixSymbolWidth.get();
    }

    set suffixSymbolWidth(t3) {
        this.__suffixSymbolWidth.set(t3);
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
                catch (x2) {
                    return this.theme.label.defaultFontSize;
                }
            }
            else {
                try {
                    resourceManager.getSystemResourceManager()
                        .getNumberByName((this.theme.label.normalFontSize.params[0]).split('.')[2]);
                    return this.theme.label.normalFontSize;
                }
                catch (w2) {
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

    toVp(m3) {
        if (m3 === void (0)) {
            return Number.NEGATIVE_INFINITY;
        }
        switch (typeof (m3)) {
            case 'number':
                return m3;
            case 'object':
                try {
                    if (m3.id !== -1) {
                        return px2vp(getContext(this).resourceManager.getNumber(m3.id));
                    }
                    else {
                        return px2vp(getContext(this)
                            .resourceManager
                            .getNumberByName((m3.params[0]).split('.')[2]));
                    }
                }
                catch (r3) {
                    return Number.NEGATIVE_INFINITY;
                }
            case 'string':
                let n3 = new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i");
                let o3 = m3.match(n3);
                if (!o3) {
                    return Number.NEGATIVE_INFINITY;
                }
                let p3 = Number(o3?.[1] ?? 0);
                let q3 = o3?.[2] ?? 'vp';
                switch (q3.toLowerCase()) {
                    case 'px':
                        p3 = px2vp(p3);
                        break;
                    case 'fp':
                        p3 = px2vp(fp2px(p3));
                        break;
                    case 'lpx':
                        p3 = px2vp(lpx2px(p3));
                        break;
                    case '%':
                        p3 = Number.NEGATIVE_INFINITY;
                        break;
                    case 'vp':
                        break;
                    default:
                        break;
                }
                return p3;
            default:
                return Number.NEGATIVE_INFINITY;
        }
    }

    getLabelMargin() {
        let l3 = { left: 0, right: 0 };
        if (this.label?.labelMargin?.left !== void (0) && this.toVp(this.label.labelMargin.left) >= 0) {
            l3.left = this.label?.labelMargin?.left;
        }
        else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                l3.left = this.theme.label.smallMargin.left;
            }
            else {
                l3.left = this.theme.label.normalMargin.left;
            }
        }
        if (this.label?.labelMargin?.right !== void (0) && this.toVp(this.label.labelMargin.right) >= 0) {
            l3.right = this.label?.labelMargin?.right;
        }
        else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
            this.suffixIcon?.src || this.useDefaultSuffixIcon) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                l3.right = this.theme.label.smallMargin.right;
            }
            else {
                l3.right = this.theme.label.normalMargin.right;
            }
        }
        return l3;
    }

    getSuffixIconSize() {
        let k3 = { width: 0, height: 0 };
        if (this.suffixIcon?.size?.width !== void (0) && this.toVp(this.suffixIcon?.size?.width) >= 0) {
            k3.width = this.suffixIcon?.size?.width;
        }
        else {
            if (this.getSuffixIconSrc()) {
                k3.width = this.theme.suffixIcon.size.width;
            }
            else {
                k3.width = 0;
            }
        }
        if (this.suffixIcon?.size?.height !== void (0) && this.toVp(this.suffixIcon?.size?.height) >= 0) {
            k3.height = this.suffixIcon?.size?.height;
        }
        else {
            if (this.getSuffixIconSrc()) {
                k3.height = this.theme.suffixIcon.size.height;
            }
            else {
                k3.height = 0;
            }
        }
        return k3;
    }

    getPrefixIconSize() {
        let j3 = { width: 0, height: 0 };
        if (this.prefixIcon?.size?.width !== void (0) && this.toVp(this.prefixIcon?.size?.width) >= 0) {
            j3.width = this.prefixIcon?.size?.width;
        }
        else {
            if (this.prefixIcon?.src) {
                j3.width = this.theme.prefixIcon.size.width;
            }
            else {
                j3.width = 0;
            }
        }
        if (this.prefixIcon?.size?.height !== void (0) && this.toVp(this.prefixIcon?.size?.height) >= 0) {
            j3.height = this.prefixIcon?.size?.height;
        }
        else {
            if (this.prefixIcon?.src) {
                j3.height = this.theme.prefixIcon.size.height;
            }
            else {
                j3.height = 0;
            }
        }
        return j3;
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
        let g3;
        if (this.getChipActive()) {
            g3 = this.chipNodeActivatedBackgroundColor ?? this.theme.chipNode.activatedBackgroundColor;
        }
        else {
            g3 = this.chipNodeBackgroundColor ?? this.theme.chipNode.backgroundColor;
        }
        if (!this.isShowPressedBackGroundColor) {
            return g3;
        }
        let h3;
        try {
            h3 = ColorMetrics.resourceColor(g3);
        }
        catch (i3) {
            hilog.error(0x3900, 'Ace', `Chip resourceColor, error: ${i3.toString()}`);
            if (this.getChipActive()) {
                h3 = ColorMetrics.resourceColor(this.theme.chipNode.activatedBackgroundColor);
            }
            else {
                h3 = ColorMetrics.resourceColor(this.theme.chipNode.backgroundColor);
            }
        }
        return h3.blendColor(ColorMetrics.resourceColor("#19000000"))
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
        let f3 = 0;
        f3 += this.getChipNodePadding().left;
        f3 += this.toVp(this.getPrefixChipWidth());
        f3 += this.toVp(this.getLabelMargin().left);
        f3 += this.getLabelWidth();
        f3 += this.toVp(this.getLabelMargin().right);
        f3 += this.toVp(this.getSuffixChipWidth());
        f3 += this.getChipNodePadding().right;
        return f3;
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

    handleTouch(e3) {
        if (!this.getChipEnable()) {
            return;
        }
        if (this.isHover) {
            if (e3.type === TouchType.Down) {
                this.isShowPressedBackGroundColor = true;
            }
            else if (e3.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            }
        }
        else {
            if (e3.type === TouchType.Down) {
                this.isShowPressedBackGroundColor = true;
            }
            else if (e3.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            }
        }
    }

    hoverAnimate(d3) {
        if (!this.getChipEnable()) {
            return;
        }
        this.isHover = d3;
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
        let a3 = this.getChipConstraintWidth();
        return Math.min(Math.max(this.getCalculateChipNodeWidth(), a3.minWidth), a3.maxWidth);
    }

    getFocusOverlaySize() {
        return {
            width: Math.max(this.getChipNodeWidth(), this.getChipConstraintWidth().minWidth) + 8,
            height: this.getChipNodeHeight() + 8
        };
    }

    getChipConstraintWidth() {
        let y2 = this.getReserveChipNodeWidth();
        if (!this.isChipSizeEnum()) {
            this.chipNodeSize = this.chipSize;
            if (this.chipNodeSize?.width !== void (0) && this.toVp(this.chipNodeSize?.width) >= 0) {
                return { minWidth: y2, maxWidth: this.chipNodeSize.width };
            }
        }
        let z2 = this.getCalculateChipNodeWidth();
        switch (this.chipBreakPoints) {
            case BreakPointsType.SM:
                return {
                    minWidth: y2,
                    maxWidth: Math.min(z2, this.theme.chipNode.breakPointConstraintWidth.breakPointSmMaxWidth)
                };
            case BreakPointsType.MD:
                return {
                    minWidth: Math.max(z2, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(z2, this.theme.chipNode.breakPointConstraintWidth.breakPointMdMaxWidth)
                };
            case BreakPointsType.LG:
                return {
                    minWidth: Math.max(z2, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(z2, this.theme.chipNode.breakPointConstraintWidth.breakPointLgMaxWidth)
                };
            default:
                return { minWidth: y2, maxWidth: z2 };
        }
    }

    focusOverlay(m2 = null) {
        this.observeComponentCreation((w2, x2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w2);
            Stack.create();
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
            if (!x2) {
                Stack.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((p2, q2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p2);
            If.create();
            if (this.chipNodeOnFocus && !this.suffixIconOnFocus) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((u2, v2) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(u2);
                        Stack.create();
                        Stack.borderRadius(this.toVp(this.getChipNodeRadius()) + 4);
                        Stack.size(this.getFocusOverlaySize());
                        Stack.borderColor(this.theme.chipNode.focusOutlineColor);
                        Stack.borderWidth(this.theme.chipNode.borderWidth);
                        if (!v2) {
                            Stack.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Stack.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!q2) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Stack.pop();
    }

    aboutToAppear() {
        this.smListener.on("change", (l2) => {
            if (l2.matches) {
                this.chipBreakPoints = BreakPointsType.SM;
            }
        });
        this.mdListener.on("change", (k2) => {
            if (k2.matches) {
                this.chipBreakPoints = BreakPointsType.MD;
            }
        });
        this.lgListener.on("change", (j2) => {
            if (j2.matches) {
                this.chipBreakPoints = BreakPointsType.LG;
            }
        });
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
    }

    chipBuilder(f = null) {
        this.observeComponentCreation((w1, x1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w1);
            Row.create();
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.Center);
            Row.clip(false);
            Row.padding(this.getChipNodePadding());
            Row.height(this.getChipNodeHeight());
            Row.width(this.getChipNodeWidth());
            Row.constraintSize(this.getChipConstraintWidth());
            Row.backgroundColor(this.getChipNodeBackGroundColor());
            Row.borderRadius(this.getChipNodeRadius());
            Row.enabled(this.getChipEnable());
            Row.scale(ObservedObject.GetRawObject(this.chipScale));
            Row.focusable(true);
            Row.opacity(this.getChipNodeOpacity());
            ViewStackProcessor.visualState("normal");
            Row.overlay(undefined);
            ViewStackProcessor.visualState("focused");
            Row.overlay({ builder: this.focusOverlay.bind(this) }, { align: Alignment.Center });
            ViewStackProcessor.visualState();
            Row.onFocus(() => {
                this.chipNodeOnFocus = true;
            });
            Row.onBlur(() => {
                this.chipNodeOnFocus = false;
            });
            Row.onTouch((f2) => {
                this.handleTouch(f2);
            });
            Row.onHover((e2) => {
                if (this.isShowPressedBackGroundColor == false) {
                    this.isShowPressedBackGroundColor = true;
                }
                else {
                    this.isShowPressedBackGroundColor = false;
                }
            });
            Row.onKeyEvent((d2) => {
                if (d2.type === KeyType.Down && d2.keyCode === KeyCode.KEYCODE_FORWARD_DEL && !this.suffixIconOnFocus) {
                    this.deleteChipNodeAnimate();
                }
            });
            Row.onClick(this.onClicked === noop ? undefined : this.onClicked.bind(this));
            if (!x1) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((i1, j1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i1);
            If.create();
            if (this.prefixSymbol?.normal || this.prefixSymbol?.activated) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((r1, s1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(r1);
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.theme.defaultSymbol.fontSize);
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor());
                        SymbolGlyph.attributeModifier.bind(this)(this.getPrefixSymbolModifier());
                        SymbolGlyph.onSizeChange((u1, v1) => {
                            this.prefixSymbolWidth = v1?.width;
                        });
                        SymbolGlyph.key("PrefixSymbolGlyph");
                        if (!s1) {
                            SymbolGlyph.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else if (this.prefixIcon?.src !== "") {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((n1, o1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(n1);
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
                        if (!o1) {
                            Image.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else {
                this.ifElseBranchUpdateFunction(2, () => {
                });
            }
            if (!j1) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((g1, h1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(g1);
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
            if (!h1) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        this.observeComponentCreation((k, l) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k);
            If.create();
            if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((b1, c1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(b1);
                        SymbolGlyph.create();
                        SymbolGlyph.fontSize(this.theme.defaultSymbol.fontSize);
                        SymbolGlyph.fontColor(this.getDefaultSymbolColor());
                        SymbolGlyph.attributeModifier.bind(this)(this.getSuffixSymbolModifier());
                        SymbolGlyph.onSizeChange((e1, f1) => {
                            this.suffixSymbolWidth = f1?.width;
                        });
                        SymbolGlyph.key("SuffixSymbolGlyph");
                        if (!c1) {
                            SymbolGlyph.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else if (this.suffixIcon?.src !== "") {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((u, v) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(u);
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
                        if (!v) {
                            Image.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else if (this.allowClose) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation((p, q) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(p);
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
                        if (!q) {
                            SymbolGlyph.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else {
                this.ifElseBranchUpdateFunction(3, () => {
                });
            }
            if (!l) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Row.pop();
    }

    initialRender() {
        this.observeComponentCreation((b, c) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b);
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
            if (!c) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    Chip, ChipSize
}