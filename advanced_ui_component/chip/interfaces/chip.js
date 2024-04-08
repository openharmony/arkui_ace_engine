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

const KeyCode = requireNapi("multimodalInput.keyCode").KeyCode;
const measure = requireNapi('measure');
const mediaquery = requireNapi('mediaquery');
const resourceManager = requireNapi('resourceManager');

export var ChipSize;
(function (g7) {
    g7["NORMAL"] = "NORMAL";
    g7["SMALL"] = "SMALL";
})(ChipSize || (ChipSize = {}));
var BreakPointsType;
(function (f7) {
    f7["SM"] = "SM";
    f7["MD"] = "MD";
    f7["LG"] = "LG";
})(BreakPointsType || (BreakPointsType = {}));

export const defaultTheme = {
    prefixIcon: {
        size: { width: 16, height: 16 },
        fillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_secondary'],
            "bundleName": "",
            "moduleName": ""
        },
        activatedFillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_primary_contrary'],
            "bundleName": "",
            "moduleName": ""
        },
    },
    label: {
        normalFontSize: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_text_size_button2'],
            "bundleName": "",
            "moduleName": ""
        },
        smallFontSize: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_text_size_button2'],
            "bundleName": "",
            "moduleName": ""
        },
        fontColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_primary'],
            "bundleName": "",
            "moduleName": ""
        },
        activatedFontColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_primary_contrary'],
            "bundleName": "",
            "moduleName": ""
        },
        fontFamily: "HarmonyOS Sans",
        normalMargin: { left: 6, right: 6, top: 0, bottom: 0 },
        smallMargin: { left: 4, right: 4, top: 0, bottom: 0 },
    },
    suffixIcon: {
        size: { width: 16, height: 16 },
        fillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_secondary'],
            "bundleName": "",
            "moduleName": ""
        },
        activatedFillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_primary_contrary'],
            "bundleName": "",
            "moduleName": ""
        },
        defaultDeleteIcon: {
            "id": -1,
            "type": 20000,
            params: ['sys.media.ohos_ic_public_cancel', 16, 16],
            "bundleName": "",
            "moduleName": ""
        },
        focusable: false,
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
            "bundleName": "",
            "moduleName": ""
        },
        activatedBackgroundColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_emphasize'],
            "bundleName": "",
            "moduleName": ""
        },
        focusOutlineColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_focused_outline'],
            "bundleName": "",
            "moduleName": ""
        },
        normalBorderRadius: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_corner_radius_tips_instant_tip'],
            "bundleName": "",
            "moduleName": ""
        },
        smallBorderRadius: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_corner_radius_piece'],
            "bundleName": "",
            "moduleName": ""
        },
        borderWidth: 2,
        normalPadding: { left: 16, right: 16, top: 0, bottom: 0 },
        smallPadding: { left: 12, right: 12, top: 0, bottom: 0 },
        hoverBlendColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_hover'],
            "bundleName": "",
            "moduleName": ""
        },
        pressedBlendColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_click_effect'],
            "bundleName": "",
            "moduleName": ""
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

export function Chip(w6, x6 = null) {
    const y6 = w6;
    {
        (x6 ? x6 : this).observeComponentCreation2((a7, b7, c7 = y6) => {
            if (b7) {
                let d7 = () => {
                    return {
                        chipSize: c7.size,
                        prefixIcon: c7.prefixIcon,
                        label: c7.label,
                        suffixIcon: c7.suffixIcon,
                        allowClose: c7.allowClose,
                        chipEnabled: c7.enabled,
                        chipActivated: c7.activated,
                        chipNodeBackgroundColor: c7.backgroundColor,
                        chipNodeActivatedBackgroundColor: c7.activatedBackgroundColor,
                        chipNodeRadius: c7.borderRadius,
                        onClose: c7.onClose,
                        onClicked: c7.onClicked
                    };
                };
                ViewPU.create(new ChipComponent(x6 ? x6 : this, {
                    chipSize: c7.size,
                    prefixIcon: c7.prefixIcon,
                    label: c7.label,
                    suffixIcon: c7.suffixIcon,
                    allowClose: c7.allowClose,
                    chipEnabled: c7.enabled,
                    chipActivated: c7.activated,
                    chipNodeBackgroundColor: c7.backgroundColor,
                    chipNodeActivatedBackgroundColor: c7.activatedBackgroundColor,
                    chipNodeRadius: c7.borderRadius,
                    onClose: c7.onClose,
                    onClicked: c7.onClicked,
                }, undefined, a7, d7, { page: "library/src/main/ets/components/chip/chip.ets", line: 191 }));
            }
            else {
                (x6 ? x6 : this).updateStateVarsOfChildByElmtId(a7, {
                    chipSize: c7.size,
                    prefixIcon: c7.prefixIcon,
                    label: c7.label,
                    suffixIcon: c7.suffixIcon,
                    allowClose: c7.allowClose,
                    chipEnabled: c7.enabled,
                    chipActivated: c7.activated,
                    chipNodeBackgroundColor: c7.backgroundColor,
                    chipNodeActivatedBackgroundColor: c7.activatedBackgroundColor,
                    chipNodeRadius: c7.borderRadius
                });
            }
        }, { name: "ChipComponent" });
    }
}

export class ChipComponent extends ViewPU {
    constructor(q6, r6, s6, t6 = -1, u6 = undefined, v6) {
        super(q6, s6, t6, v6);
        if (typeof u6 === "function") {
            this.paramsGenerator_ = u6;
        }
        this.theme = defaultTheme;
        this.__chipSize = new SynchedPropertyObjectOneWayPU(r6.chipSize, this, "chipSize");
        this.__allowClose = new SynchedPropertySimpleOneWayPU(r6.allowClose, this, "allowClose");
        this.__prefixIcon = new SynchedPropertyObjectOneWayPU(r6.prefixIcon, this, "prefixIcon");
        this.__label = new SynchedPropertyObjectOneWayPU(r6.label, this, "label");
        this.__suffixIcon = new SynchedPropertyObjectOneWayPU(r6.suffixIcon, this, "suffixIcon");
        this.__chipNodeBackgroundColor = new SynchedPropertyObjectOneWayPU(r6.chipNodeBackgroundColor, this, "chipNodeBackgroundColor");
        this.__chipNodeActivatedBackgroundColor = new SynchedPropertyObjectOneWayPU(r6.chipNodeActivatedBackgroundColor, this, "chipNodeActivatedBackgroundColor");
        this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(r6.chipNodeRadius, this, "chipNodeRadius");
        this.__chipEnabled = new SynchedPropertySimpleOneWayPU(r6.chipEnabled, this, "chipEnabled");
        this.__chipActivated = new SynchedPropertySimpleOneWayPU(r6.chipActivated, this, "chipActivated");
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
        this.setInitiallyProvidedValue(r6);
    }

    setInitiallyProvidedValue(p6) {
        if (p6.theme !== undefined) {
            this.theme = p6.theme;
        }
        if (p6.chipSize === undefined) {
            this.__chipSize.set(ChipSize.NORMAL);
        }
        if (p6.allowClose === undefined) {
            this.__allowClose.set(true);
        }
        if (p6.prefixIcon === undefined) {
            this.__prefixIcon.set({ src: "" });
        }
        if (p6.label === undefined) {
            this.__label.set({ text: "" });
        }
        if (p6.suffixIcon === undefined) {
            this.__suffixIcon.set({ src: "" });
        }
        if (p6.chipNodeBackgroundColor === undefined) {
            this.__chipNodeBackgroundColor.set(this.theme.chipNode.backgroundColor);
        }
        if (p6.chipNodeActivatedBackgroundColor === undefined) {
            this.__chipNodeActivatedBackgroundColor.set(this.theme.chipNode.activatedBackgroundColor);
        }
        if (p6.chipNodeRadius === undefined) {
            this.__chipNodeRadius.set(void (0));
        }
        if (p6.chipEnabled === undefined) {
            this.__chipEnabled.set(true);
        }
        if (p6.chipActivated === undefined) {
            this.__chipActivated.set(false);
        }
        if (p6.isHover !== undefined) {
            this.isHover = p6.isHover;
        }
        if (p6.chipScale !== undefined) {
            this.chipScale = p6.chipScale;
        }
        if (p6.chipOpacity !== undefined) {
            this.chipOpacity = p6.chipOpacity;
        }
        if (p6.chipBlendColor !== undefined) {
            this.chipBlendColor = p6.chipBlendColor;
        }
        if (p6.deleteChip !== undefined) {
            this.deleteChip = p6.deleteChip;
        }
        if (p6.chipNodeOnFocus !== undefined) {
            this.chipNodeOnFocus = p6.chipNodeOnFocus;
        }
        if (p6.useDefaultSuffixIcon !== undefined) {
            this.useDefaultSuffixIcon = p6.useDefaultSuffixIcon;
        }
        if (p6.chipNodeSize !== undefined) {
            this.chipNodeSize = p6.chipNodeSize;
        }
        if (p6.onClose !== undefined) {
            this.onClose = p6.onClose;
        }
        if (p6.onClicked !== undefined) {
            this.onClicked = p6.onClicked;
        }
        if (p6.suffixIconOnFocus !== undefined) {
            this.suffixIconOnFocus = p6.suffixIconOnFocus;
        }
        if (p6.chipBreakPoints !== undefined) {
            this.chipBreakPoints = p6.chipBreakPoints;
        }
        if (p6.smListener !== undefined) {
            this.smListener = p6.smListener;
        }
        if (p6.mdListener !== undefined) {
            this.mdListener = p6.mdListener;
        }
        if (p6.lgListener !== undefined) {
            this.lgListener = p6.lgListener;
        }
    }

    updateStateVars(o6) {
        this.__chipSize.reset(o6.chipSize);
        this.__allowClose.reset(o6.allowClose);
        this.__prefixIcon.reset(o6.prefixIcon);
        this.__label.reset(o6.label);
        this.__suffixIcon.reset(o6.suffixIcon);
        this.__chipNodeBackgroundColor.reset(o6.chipNodeBackgroundColor);
        this.__chipNodeActivatedBackgroundColor.reset(o6.chipNodeActivatedBackgroundColor);
        this.__chipNodeRadius.reset(o6.chipNodeRadius);
        this.__chipEnabled.reset(o6.chipEnabled);
        this.__chipActivated.reset(o6.chipActivated);
    }

    purgeVariableDependenciesOnElmtId(n6) {
        this.__chipSize.purgeDependencyOnElmtId(n6);
        this.__allowClose.purgeDependencyOnElmtId(n6);
        this.__prefixIcon.purgeDependencyOnElmtId(n6);
        this.__label.purgeDependencyOnElmtId(n6);
        this.__suffixIcon.purgeDependencyOnElmtId(n6);
        this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(n6);
        this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(n6);
        this.__chipNodeRadius.purgeDependencyOnElmtId(n6);
        this.__chipEnabled.purgeDependencyOnElmtId(n6);
        this.__chipActivated.purgeDependencyOnElmtId(n6);
        this.__isHover.purgeDependencyOnElmtId(n6);
        this.__chipScale.purgeDependencyOnElmtId(n6);
        this.__chipOpacity.purgeDependencyOnElmtId(n6);
        this.__chipBlendColor.purgeDependencyOnElmtId(n6);
        this.__deleteChip.purgeDependencyOnElmtId(n6);
        this.__chipNodeOnFocus.purgeDependencyOnElmtId(n6);
        this.__useDefaultSuffixIcon.purgeDependencyOnElmtId(n6);
        this.__suffixIconOnFocus.purgeDependencyOnElmtId(n6);
        this.__chipBreakPoints.purgeDependencyOnElmtId(n6);
    }

    aboutToBeDeleted() {
        this.__chipSize.aboutToBeDeleted();
        this.__allowClose.aboutToBeDeleted();
        this.__prefixIcon.aboutToBeDeleted();
        this.__label.aboutToBeDeleted();
        this.__suffixIcon.aboutToBeDeleted();
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get chipSize() {
        return this.__chipSize.get();
    }

    set chipSize(m6) {
        this.__chipSize.set(m6);
    }

    get allowClose() {
        return this.__allowClose.get();
    }

    set allowClose(l6) {
        this.__allowClose.set(l6);
    }

    get prefixIcon() {
        return this.__prefixIcon.get();
    }

    set prefixIcon(k6) {
        this.__prefixIcon.set(k6);
    }

    get label() {
        return this.__label.get();
    }

    set label(j6) {
        this.__label.set(j6);
    }

    get suffixIcon() {
        return this.__suffixIcon.get();
    }

    set suffixIcon(i6) {
        this.__suffixIcon.set(i6);
    }

    get chipNodeBackgroundColor() {
        return this.__chipNodeBackgroundColor.get();
    }

    set chipNodeBackgroundColor(h6) {
        this.__chipNodeBackgroundColor.set(h6);
    }

    get chipNodeActivatedBackgroundColor() {
        return this.__chipNodeActivatedBackgroundColor.get();
    }

    set chipNodeActivatedBackgroundColor(g6) {
        this.__chipNodeActivatedBackgroundColor.set(g6);
    }

    get chipNodeRadius() {
        return this.__chipNodeRadius.get();
    }

    set chipNodeRadius(f6) {
        this.__chipNodeRadius.set(f6);
    }

    get chipEnabled() {
        return this.__chipEnabled.get();
    }

    set chipEnabled(e6) {
        this.__chipEnabled.set(e6);
    }

    get chipActivated() {
        return this.__chipActivated.get();
    }

    set chipActivated(d6) {
        this.__chipActivated.set(d6);
    }

    get isHover() {
        return this.__isHover.get();
    }

    set isHover(c6) {
        this.__isHover.set(c6);
    }

    get chipScale() {
        return this.__chipScale.get();
    }

    set chipScale(b6) {
        this.__chipScale.set(b6);
    }

    get chipOpacity() {
        return this.__chipOpacity.get();
    }

    set chipOpacity(a6) {
        this.__chipOpacity.set(a6);
    }

    get chipBlendColor() {
        return this.__chipBlendColor.get();
    }

    set chipBlendColor(z5) {
        this.__chipBlendColor.set(z5);
    }

    get deleteChip() {
        return this.__deleteChip.get();
    }

    set deleteChip(y5) {
        this.__deleteChip.set(y5);
    }

    get chipNodeOnFocus() {
        return this.__chipNodeOnFocus.get();
    }

    set chipNodeOnFocus(x5) {
        this.__chipNodeOnFocus.set(x5);
    }

    get useDefaultSuffixIcon() {
        return this.__useDefaultSuffixIcon.get();
    }

    set useDefaultSuffixIcon(w5) {
        this.__useDefaultSuffixIcon.set(w5);
    }

    get suffixIconOnFocus() {
        return this.__suffixIconOnFocus.get();
    }

    set suffixIconOnFocus(v5) {
        this.__suffixIconOnFocus.set(v5);
    }

    get chipBreakPoints() {
        return this.__chipBreakPoints.get();
    }

    set chipBreakPoints(u5) {
        this.__chipBreakPoints.set(u5);
    }

    isChipSizeEnum() {
        return typeof (this.chipSize) === 'string';
    }

    getLabelFontSize() {
        var s5;
        try {
            if (((s5 = this.label) === null || s5 === void 0 ? void 0 : s5.fontSize) !== void (0) && this.toVp(this.label.fontSize) >= 0) {
                return this.label.fontSize;
            }
            else {
                if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
                    return resourceManager.getSystemResourceManager()
                        .getNumberByName((this.theme.label.smallFontSize.params[0]).split('.')[2]);
                }
                else {
                    return resourceManager.getSystemResourceManager()
                        .getNumberByName((this.theme.label.normalFontSize.params[0]).split('.')[2]);
                }
            }
        }
        catch (t5) {
            return 0;
        }
    }

    getLabelFontColor() {
        var o5, p5, q5, r5;
        if (this.getChipActive()) {
            return (p5 = (o5 = this.label) === null || o5 === void 0 ? void 0 : o5.activatedFontColor) !== null && p5 !== void 0 ? p5 : this.theme.label.activatedFontColor;
        }
        return (r5 = (q5 = this.label) === null || q5 === void 0 ? void 0 : q5.fontColor) !== null && r5 !== void 0 ? r5 : this.theme.label.fontColor;
    }

    getLabelFontFamily() {
        var m5, n5;
        return (n5 = (m5 = this.label) === null || m5 === void 0 ? void 0 : m5.fontFamily) !== null && n5 !== void 0 ? n5 : this.theme.label.fontFamily;
    }

    getLabelFontWeight() {
        if (this.getChipActive()) {
            return FontWeight.Medium;
        }
        return FontWeight.Regular;
    }

    toVp(e5) {
        var f5, g5;
        if (e5 === void (0)) {
            return Number.NEGATIVE_INFINITY;
        }
        switch (typeof (e5)) {
            case 'number':
                return e5;
            case 'object':
                try {
                    if (e5.id !== -1) {
                        return px2vp(getContext(this).resourceManager.getNumber(e5.id));
                    }
                    else {
                        return px2vp(getContext(this)
                            .resourceManager
                            .getNumberByName((e5.params[0]).split('.')[2]));
                    }
                }
                catch (l5) {
                    return Number.NEGATIVE_INFINITY;
                }
            case 'string':
                let h5 = new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i");
                let i5 = e5.match(h5);
                if (!i5) {
                    return Number.NEGATIVE_INFINITY;
                }
                let j5 = Number((f5 = i5 === null || i5 === void 0 ? void 0 : i5[1]) !== null && f5 !== void 0 ? f5 : 0);
                let k5 = (g5 = i5 === null || i5 === void 0 ? void 0 : i5[2]) !== null && g5 !== void 0 ? g5 : 'vp';
                switch (k5.toLowerCase()) {
                    case 'px':
                        j5 = px2vp(j5);
                        break;
                    case 'fp':
                        j5 = px2vp(fp2px(j5));
                        break;
                    case 'lpx':
                        j5 = px2vp(lpx2px(j5));
                        break;
                    case '%':
                        j5 = Number.NEGATIVE_INFINITY;
                        break;
                    case 'vp':
                        break;
                    default:
                        break;
                }
                return j5;
            default:
                return Number.NEGATIVE_INFINITY;
        }
    }

    getLabelMargin() {
        var t4, u4, v4, w4, x4, y4, z4, a5, b5, c5;
        let d5 = { left: 0, right: 0 };
        if (((u4 = (t4 = this.label) === null || t4 === void 0 ? void 0 : t4.labelMargin) === null || u4 === void 0 ? void 0 : u4.left) !== void (0) && this.toVp(this.label.labelMargin.left) >= 0) {
            d5.left = (w4 = (v4 = this.label) === null || v4 === void 0 ? void 0 : v4.labelMargin) === null || w4 === void 0 ? void 0 : w4.left;
        }
        else if ((x4 = this.prefixIcon) === null || x4 === void 0 ? void 0 : x4.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                d5.left = this.theme.label.smallMargin.left;
            }
            else {
                d5.left = this.theme.label.normalMargin.left;
            }
        }
        if (((z4 = (y4 = this.label) === null || y4 === void 0 ? void 0 : y4.labelMargin) === null || z4 === void 0 ? void 0 : z4.right) !== void (0) && this.toVp(this.label.labelMargin.right) >= 0) {
            d5.right = (b5 = (a5 = this.label) === null || a5 === void 0 ? void 0 : a5.labelMargin) === null || b5 === void 0 ? void 0 : b5.right;
        }
        else if (((c5 = this.suffixIcon) === null || c5 === void 0 ? void 0 : c5.src) || this.useDefaultSuffixIcon) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                d5.right = this.theme.label.smallMargin.right;
            }
            else {
                d5.right = this.theme.label.normalMargin.right;
            }
        }
        return d5;
    }

    getSuffixIconSize() {
        var g4, h4, i4, j4, k4, l4, m4, n4, o4, p4, q4, r4;
        let s4 = { width: 0, height: 0 };
        if (((h4 = (g4 = this.suffixIcon) === null || g4 === void 0 ? void 0 : g4.size) === null || h4 === void 0 ? void 0 : h4.width) !== void (0) && this.toVp((j4 = (i4 = this.suffixIcon) === null || i4 === void 0 ? void 0 : i4.size) === null || j4 === void 0 ? void 0 : j4.width) >= 0) {
            s4.width = (l4 = (k4 = this.suffixIcon) === null || k4 === void 0 ? void 0 : k4.size) === null || l4 === void 0 ? void 0 : l4.width;
        }
        else {
            if (this.getSuffixIconSrc()) {
                s4.width = this.theme.suffixIcon.size.width;
            }
            else {
                s4.width = 0;
            }
        }
        if (((n4 = (m4 = this.suffixIcon) === null || m4 === void 0 ? void 0 : m4.size) === null || n4 === void 0 ? void 0 : n4.height) !== void (0) && this.toVp((p4 = (o4 = this.suffixIcon) === null || o4 === void 0 ? void 0 : o4.size) === null || p4 === void 0 ? void 0 : p4.height) >= 0) {
            s4.height = (r4 = (q4 = this.suffixIcon) === null || q4 === void 0 ? void 0 : q4.size) === null || r4 === void 0 ? void 0 : r4.height;
        }
        else {
            if (this.getSuffixIconSrc()) {
                s4.height = this.theme.suffixIcon.size.height;
            }
            else {
                s4.height = 0;
            }
        }
        return s4;
    }

    getPrefixIconSize() {
        var r3, s3, t3, u3, v3, w3, x3, y3, z3, a4, b4, c4, d4, e4;
        let f4 = { width: 0, height: 0 };
        if (((s3 = (r3 = this.prefixIcon) === null || r3 === void 0 ? void 0 : r3.size) === null || s3 === void 0 ? void 0 : s3.width) !== void (0) && this.toVp((u3 = (t3 = this.prefixIcon) === null || t3 === void 0 ? void 0 : t3.size) === null || u3 === void 0 ? void 0 : u3.width) >= 0) {
            f4.width = (w3 = (v3 = this.prefixIcon) === null || v3 === void 0 ? void 0 : v3.size) === null || w3 === void 0 ? void 0 : w3.width;
        }
        else {
            if ((x3 = this.prefixIcon) === null || x3 === void 0 ? void 0 : x3.src) {
                f4.width = this.theme.prefixIcon.size.width;
            }
            else {
                f4.width = 0;
            }
        }
        if (((z3 = (y3 = this.prefixIcon) === null || y3 === void 0 ? void 0 : y3.size) === null || z3 === void 0 ? void 0 : z3.height) !== void (0) && this.toVp((b4 = (a4 = this.prefixIcon) === null || a4 === void 0 ? void 0 : a4.size) === null || b4 === void 0 ? void 0 : b4.height) >= 0) {
            f4.height = (d4 = (c4 = this.prefixIcon) === null || c4 === void 0 ? void 0 : c4.size) === null || d4 === void 0 ? void 0 : d4.height;
        }
        else {
            if ((e4 = this.prefixIcon) === null || e4 === void 0 ? void 0 : e4.src) {
                f4.height = this.theme.prefixIcon.size.height;
            }
            else {
                f4.height = 0;
            }
        }
        return f4;
    }

    getPrefixIconFilledColor() {
        var n3, o3, p3, q3;
        if (this.getChipActive()) {
            return (o3 = (n3 = this.prefixIcon) === null || n3 === void 0 ? void 0 : n3.activatedFillColor) !== null && o3 !== void 0 ? o3 : this.theme.prefixIcon.activatedFillColor;
        }
        return (q3 = (p3 = this.prefixIcon) === null || p3 === void 0 ? void 0 : p3.fillColor) !== null && q3 !== void 0 ? q3 : this.theme.prefixIcon.fillColor;
    }

    getSuffixIconFilledColor() {
        var j3, k3, l3, m3;
        if (this.getChipActive()) {
            return (k3 = (j3 = this.suffixIcon) === null || j3 === void 0 ? void 0 : j3.activatedFillColor) !== null && k3 !== void 0 ? k3 : this.theme.suffixIcon.activatedFillColor;
        }
        return (m3 = (l3 = this.suffixIcon) === null || l3 === void 0 ? void 0 : l3.fillColor) !== null && m3 !== void 0 ? m3 : this.theme.suffixIcon.fillColor;
    }

    getSuffixIconFocusable() {
        var i3;
        return (this.useDefaultSuffixIcon && this.allowClose) || ((i3 = this.suffixIcon) === null || i3 === void 0 ? void 0 : i3.action) !== void (0);
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
        var g3, h3;
        if (this.getChipActive()) {
            return (g3 = this.chipNodeActivatedBackgroundColor) !== null && g3 !== void 0 ? g3 : this.theme.chipNode.activatedBackgroundColor;
        }
        return (h3 = this.chipNodeBackgroundColor) !== null && h3 !== void 0 ? h3 : this.theme.chipNode.backgroundColor;
    }

    getChipNodeHeight() {
        var d3, e3, f3;
        if (this.isChipSizeEnum()) {
            return this.chipSize === ChipSize.SMALL ? this.theme.chipNode.smallHeight : this.theme.chipNode.normalHeight;
        }
        else {
            this.chipNodeSize = this.chipSize;
            return (((d3 = this.chipNodeSize) === null || d3 === void 0 ? void 0 : d3.height) !== void (0) && this.toVp((e3 = this.chipNodeSize) === null || e3 === void 0 ? void 0 : e3.height) >= 0) ? this.toVp((f3 = this.chipNodeSize) === null || f3 === void 0 ? void 0 : f3.height) : this.theme.chipNode.normalHeight;
        }
    }

    getLabelWidth() {
        var z2, a3, b3, c3;
        return px2vp(measure.measureText({
            textContent: (a3 = (z2 = this.label) === null || z2 === void 0 ? void 0 : z2.text) !== null && a3 !== void 0 ? a3 : "",
            fontSize: this.getLabelFontSize(),
            fontFamily: (c3 = (b3 = this.label) === null || b3 === void 0 ? void 0 : b3.fontFamily) !== null && c3 !== void 0 ? c3 : this.theme.label.fontFamily,
            fontWeight: this.getLabelFontWeight(),
            maxLines: 1,
            overflow: TextOverflow.Ellipsis,
            textAlign: TextAlign.Center
        }));
    }

    getCalculateChipNodeWidth() {
        let y2 = 0;
        y2 += this.getChipNodePadding().left;
        y2 += this.toVp(this.getPrefixIconSize().width);
        y2 += this.toVp(this.getLabelMargin().left);
        y2 += this.getLabelWidth();
        y2 += this.toVp(this.getLabelMargin().right);
        y2 += this.toVp(this.getSuffixIconSize().width);
        y2 += this.getChipNodePadding().right;
        return y2;
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

    handleTouch(t2) {
        if (!this.getChipEnable()) {
            return;
        }
        if (this.isHover) {
            if (t2.type === TouchType.Down) {
                Context.animateTo({ curve: Curve.Sharp, duration: 100 }, () => {
                    this.chipBlendColor = this.theme.chipNode.pressedBlendColor;
                    this.chipOpacity = this.theme.chipNode.opacity.pressed;
                });
            }
            else if (t2.type === TouchType.Up) {
                Context.animateTo({ curve: Curve.Sharp, duration: 100 }, () => {
                    this.chipBlendColor = this.theme.chipNode.hoverBlendColor;
                    this.chipOpacity = this.theme.chipNode.opacity.hover;
                });
            }
        }
        else {
            if (t2.type === TouchType.Down) {
                Context.animateTo({ curve: Curve.Friction, duration: 350 }, () => {
                    this.chipBlendColor = this.theme.chipNode.pressedBlendColor;
                    this.chipOpacity = this.theme.chipNode.opacity.pressed;
                });
            }
            else if (t2.type === TouchType.Up) {
                Context.animateTo({ curve: Curve.Friction, duration: 350 }, () => {
                    this.chipBlendColor = Color.Transparent;
                    this.chipOpacity = this.theme.chipNode.opacity.normal;
                });
            }
        }
    }

    hoverAnimate(r2) {
        if (!this.getChipEnable()) {
            return;
        }
        this.isHover = r2;
        Context.animateTo({
            curve: Curve.Friction,
            duration: 250
        }, () => {
            if (r2) {
                this.chipBlendColor = this.theme.chipNode.hoverBlendColor;
                this.chipOpacity = this.theme.chipNode.opacity.hover;
            }
            else {
                this.chipBlendColor = Color.Transparent;
                this.chipOpacity = this.theme.chipNode.opacity.normal;
            }
        });
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
        var m2, n2, o2;
        this.useDefaultSuffixIcon = !((m2 = this.suffixIcon) === null || m2 === void 0 ? void 0 : m2.src) && this.allowClose;
        return this.useDefaultSuffixIcon ? this.theme.suffixIcon.defaultDeleteIcon : ((o2 = (n2 = this.suffixIcon) === null || n2 === void 0 ? void 0 : n2.src) !== null && o2 !== void 0 ? o2 : void (0));
    }

    getChipNodeWidth() {
        var k2;
        if (!this.isChipSizeEnum()) {
            this.chipNodeSize = this.chipSize;
            if (((k2 = this.chipNodeSize) === null || k2 === void 0 ? void 0 : k2.width) !== void (0) && this.toVp(this.chipNodeSize.width) >= 0) {
                return this.toVp(this.chipNodeSize.width);
            }
        }
        let l2 = this.getChipConstraintWidth();
        return Math.min(Math.max(this.getCalculateChipNodeWidth(), l2.minWidth), l2.maxWidth);
    }

    getFocusOverlaySize() {
        return {
            width: Math.max(this.getChipNodeWidth(), this.getChipConstraintWidth().minWidth) + 8,
            height: this.getChipNodeHeight() + 8
        };
    }

    getChipConstraintWidth() {
        var g2, h2;
        let i2 = this.getReserveChipNodeWidth();
        if (!this.isChipSizeEnum()) {
            this.chipNodeSize = this.chipSize;
            if (((g2 = this.chipNodeSize) === null || g2 === void 0 ? void 0 : g2.width) !== void (0) && this.toVp((h2 = this.chipNodeSize) === null || h2 === void 0 ? void 0 : h2.width) >= 0) {
                return { minWidth: i2, maxWidth: this.chipNodeSize.width };
            }
        }
        let j2 = this.getCalculateChipNodeWidth();
        switch (this.chipBreakPoints) {
            case BreakPointsType.SM:
                return {
                    minWidth: i2,
                    maxWidth: Math.min(j2, this.theme.chipNode.breakPointConstraintWidth.breakPointSmMaxWidth)
                };
            case BreakPointsType.MD:
                return {
                    minWidth: Math.max(j2, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(j2, this.theme.chipNode.breakPointConstraintWidth.breakPointMdMaxWidth)
                };
            case BreakPointsType.LG:
                return {
                    minWidth: Math.max(j2, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(j2, this.theme.chipNode.breakPointConstraintWidth.breakPointLgMaxWidth)
                };
            default:
                return { minWidth: i2, maxWidth: j2 };
        }
    }

    focusOverlay(u1 = null) {
        this.observeComponentCreation2((e2, f2) => {
            Stack.create();
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((x1, y1) => {
            If.create();
            if (this.chipNodeOnFocus && !this.suffixIconOnFocus) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c2, d2) => {
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
        this.smListener.on("change", (t1) => {
            if (t1.matches) {
                this.chipBreakPoints = BreakPointsType.SM;
            }
        });
        this.mdListener.on("change", (s1) => {
            if (s1.matches) {
                this.chipBreakPoints = BreakPointsType.MD;
            }
        });
        this.lgListener.on("change", (r1) => {
            if (r1.matches) {
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
        this.observeComponentCreation2((d1, e1) => {
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
            Row.colorBlend(ObservedObject.GetRawObject(this.chipBlendColor));
            Row.opacity(this.getChipNodeOpacity());
            Row.overlay({ builder: this.focusOverlay.bind(this) }, { align: Alignment.Center });
            Row.onFocus(() => {
                this.chipNodeOnFocus = true;
            });
            Row.onBlur(() => {
                this.chipNodeOnFocus = false;
            });
            Row.onTouch((n1) => {
                this.handleTouch(n1);
            });
            Row.onHover((m1) => {
                this.hoverAnimate(m1);
            });
            Row.onKeyEvent((l1) => {
                if (l1.type === KeyType.Down && l1.keyCode === KeyCode.KEYCODE_FORWARD_DEL && !this.suffixIconOnFocus) {
                    this.deleteChipNodeAnimate();
                }
            });
            Row.onClick(this.onClicked === noop ? undefined : this.onClicked.bind(this));
        }, Row);
        this.observeComponentCreation2((u, v) => {
            var w;
            If.create();
            if (((w = this.prefixIcon) === null || w === void 0 ? void 0 : w.src) !== "") {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a1, b1) => {
                        var c1;
                        Image.create((c1 = this.prefixIcon) === null || c1 === void 0 ? void 0 : c1.src);
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
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((q, r) => {
            var s, t;
            Text.create((t = (s = this.label) === null || s === void 0 ? void 0 : s.text) !== null && t !== void 0 ? t : "");
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
            ViewStackProcessor.visualState("focused");
            ViewStackProcessor.visualState();
        }, Text);
        Text.pop();
        this.observeComponentCreation2((k, l) => {
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
                var p;
                if (!this.getChipEnable()) {
                    return;
                }
                if ((p = this.suffixIcon) === null || p === void 0 ? void 0 : p.action) {
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
        Row.pop();
    }

    initialRender() {
        this.observeComponentCreation2((b, c) => {
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
