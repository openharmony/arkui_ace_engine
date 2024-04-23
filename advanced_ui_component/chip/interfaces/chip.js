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

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}


export var ChipSize;
(function (k4) {
    k4["NORMAL"] = "NORMAL";
    k4["SMALL"] = "SMALL";
})(ChipSize || (ChipSize = {}));
var BreakPointsType;
(function (j4) {
    j4["SM"] = "SM";
    j4["MD"] = "MD";
    j4["LG"] = "LG";
})(BreakPointsType || (BreakPointsType = {}));
export const defaultTheme = {
    prefixIcon: {
        size: { width: 16, height: 16 },
        fillColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        activatedFillColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    },
    label: {
        normalFontSize: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        smallFontSize: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fontColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        activatedFontColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fontFamily: "HarmonyOS Sans",
        normalMargin: { left: 6, right: 6, top: 0, bottom: 0 },
        smallMargin: { left: 4, right: 4, top: 0, bottom: 0 },
    },
    suffixIcon: {
        size: { width: 16, height: 16 },
        fillColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        activatedFillColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        defaultDeleteIcon: { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_cancel', 16, 16], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        focusable: false,
    },
    chipNode: {
        minLabelWidth: 12,
        normalHeight: 36,
        smallHeight: 28,
        enabled: true,
        activated: false,
        backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        activatedBackgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        focusOutlineColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        normalBorderRadius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_tips_instant_tip'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        smallBorderRadius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_piece'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        borderWidth: 2,
        normalPadding: { left: 16, right: 16, top: 0, bottom: 0 },
        smallPadding: { left: 12, right: 12, top: 0, bottom: 0 },
        hoverBlendColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        pressedBlendColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
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
export function Chip(y3, z3 = null) {
    const a4 = y3;
    {
        (z3 ? z3 : this).observeComponentCreation2((c4, d4, e4 = a4) => {
            if (d4) {
                let f4 = new ChipComponent(z3 ? z3 : this, {
                    chipSize: e4.size,
                    prefixIcon: e4.prefixIcon,
                    label: e4.label,
                    suffixIcon: e4.suffixIcon,
                    allowClose: e4.allowClose,
                    chipEnabled: e4.enabled,
                    chipActivated: e4.activated,
                    chipNodeBackgroundColor: e4.backgroundColor,
                    chipNodeActivatedBackgroundColor: e4.activatedBackgroundColor,
                    chipNodeRadius: e4.borderRadius,
                    onClose: e4.onClose,
                    onClicked: e4.onClicked,
                }, undefined, c4, () => { }, { page: "library/src/main/ets/components/chip/chip.ets", line: 192, col: 3 });
                ViewPU.create(f4);
                let g4 = () => {
                    return {
                        chipSize: e4.size,
                        prefixIcon: e4.prefixIcon,
                        label: e4.label,
                        suffixIcon: e4.suffixIcon,
                        allowClose: e4.allowClose,
                        chipEnabled: e4.enabled,
                        chipActivated: e4.activated,
                        chipNodeBackgroundColor: e4.backgroundColor,
                        chipNodeActivatedBackgroundColor: e4.activatedBackgroundColor,
                        chipNodeRadius: e4.borderRadius,
                        onClose: e4.onClose,
                        onClicked: e4.onClicked
                    };
                };
                f4.paramsGenerator_ = g4;
            }
            else {
                (z3 ? z3 : this).updateStateVarsOfChildByElmtId(c4, {
                    chipSize: e4.size,
                    prefixIcon: e4.prefixIcon,
                    label: e4.label,
                    suffixIcon: e4.suffixIcon,
                    allowClose: e4.allowClose,
                    chipEnabled: e4.enabled,
                    chipActivated: e4.activated,
                    chipNodeBackgroundColor: e4.backgroundColor,
                    chipNodeActivatedBackgroundColor: e4.activatedBackgroundColor,
                    chipNodeRadius: e4.borderRadius
                });
            }
        }, { name: "ChipComponent" });
    }
}
export class ChipComponent extends ViewPU {
    constructor(s3, t3, u3, v3 = -1, w3 = undefined, x3) {
        super(s3, u3, v3, x3);
        if (typeof w3 === "function") {
            this.paramsGenerator_ = w3;
        }
        this.theme = defaultTheme;
        this.__chipSize = new SynchedPropertyObjectOneWayPU(t3.chipSize, this, "chipSize");
        this.__allowClose = new SynchedPropertySimpleOneWayPU(t3.allowClose, this, "allowClose");
        this.__prefixIcon = new SynchedPropertyObjectOneWayPU(t3.prefixIcon, this, "prefixIcon");
        this.__label = new SynchedPropertyObjectOneWayPU(t3.label, this, "label");
        this.__suffixIcon = new SynchedPropertyObjectOneWayPU(t3.suffixIcon, this, "suffixIcon");
        this.__chipNodeBackgroundColor = new SynchedPropertyObjectOneWayPU(t3.chipNodeBackgroundColor, this, "chipNodeBackgroundColor");
        this.__chipNodeActivatedBackgroundColor = new SynchedPropertyObjectOneWayPU(t3.chipNodeActivatedBackgroundColor, this, "chipNodeActivatedBackgroundColor");
        this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(t3.chipNodeRadius, this, "chipNodeRadius");
        this.__chipEnabled = new SynchedPropertySimpleOneWayPU(t3.chipEnabled, this, "chipEnabled");
        this.__chipActivated = new SynchedPropertySimpleOneWayPU(t3.chipActivated, this, "chipActivated");
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
        this.setInitiallyProvidedValue(t3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r3) {
        if (r3.theme !== undefined) {
            this.theme = r3.theme;
        }
        if (r3.chipSize === undefined) {
            this.__chipSize.set(ChipSize.NORMAL);
        }
        if (r3.allowClose === undefined) {
            this.__allowClose.set(true);
        }
        if (r3.prefixIcon === undefined) {
            this.__prefixIcon.set({ src: "" });
        }
        if (r3.label === undefined) {
            this.__label.set({ text: "" });
        }
        if (r3.suffixIcon === undefined) {
            this.__suffixIcon.set({ src: "" });
        }
        if (r3.chipNodeBackgroundColor === undefined) {
            this.__chipNodeBackgroundColor.set(this.theme.chipNode.backgroundColor);
        }
        if (r3.chipNodeActivatedBackgroundColor === undefined) {
            this.__chipNodeActivatedBackgroundColor.set(this.theme.chipNode.activatedBackgroundColor);
        }
        if (r3.chipNodeRadius === undefined) {
            this.__chipNodeRadius.set(void (0));
        }
        if (r3.chipEnabled === undefined) {
            this.__chipEnabled.set(true);
        }
        if (r3.chipActivated === undefined) {
            this.__chipActivated.set(false);
        }
        if (r3.isHover !== undefined) {
            this.isHover = r3.isHover;
        }
        if (r3.chipScale !== undefined) {
            this.chipScale = r3.chipScale;
        }
        if (r3.chipOpacity !== undefined) {
            this.chipOpacity = r3.chipOpacity;
        }
        if (r3.chipBlendColor !== undefined) {
            this.chipBlendColor = r3.chipBlendColor;
        }
        if (r3.deleteChip !== undefined) {
            this.deleteChip = r3.deleteChip;
        }
        if (r3.chipNodeOnFocus !== undefined) {
            this.chipNodeOnFocus = r3.chipNodeOnFocus;
        }
        if (r3.useDefaultSuffixIcon !== undefined) {
            this.useDefaultSuffixIcon = r3.useDefaultSuffixIcon;
        }
        if (r3.chipNodeSize !== undefined) {
            this.chipNodeSize = r3.chipNodeSize;
        }
        if (r3.onClose !== undefined) {
            this.onClose = r3.onClose;
        }
        if (r3.onClicked !== undefined) {
            this.onClicked = r3.onClicked;
        }
        if (r3.suffixIconOnFocus !== undefined) {
            this.suffixIconOnFocus = r3.suffixIconOnFocus;
        }
        if (r3.chipBreakPoints !== undefined) {
            this.chipBreakPoints = r3.chipBreakPoints;
        }
        if (r3.smListener !== undefined) {
            this.smListener = r3.smListener;
        }
        if (r3.mdListener !== undefined) {
            this.mdListener = r3.mdListener;
        }
        if (r3.lgListener !== undefined) {
            this.lgListener = r3.lgListener;
        }
        if (r3.isShowPressedBackGroundColor !== undefined) {
            this.isShowPressedBackGroundColor = r3.isShowPressedBackGroundColor;
        }
    }
    updateStateVars(q3) {
        this.__chipSize.reset(q3.chipSize);
        this.__allowClose.reset(q3.allowClose);
        this.__prefixIcon.reset(q3.prefixIcon);
        this.__label.reset(q3.label);
        this.__suffixIcon.reset(q3.suffixIcon);
        this.__chipNodeBackgroundColor.reset(q3.chipNodeBackgroundColor);
        this.__chipNodeActivatedBackgroundColor.reset(q3.chipNodeActivatedBackgroundColor);
        this.__chipNodeRadius.reset(q3.chipNodeRadius);
        this.__chipEnabled.reset(q3.chipEnabled);
        this.__chipActivated.reset(q3.chipActivated);
    }
    purgeVariableDependenciesOnElmtId(p3) {
        this.__chipSize.purgeDependencyOnElmtId(p3);
        this.__allowClose.purgeDependencyOnElmtId(p3);
        this.__prefixIcon.purgeDependencyOnElmtId(p3);
        this.__label.purgeDependencyOnElmtId(p3);
        this.__suffixIcon.purgeDependencyOnElmtId(p3);
        this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(p3);
        this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(p3);
        this.__chipNodeRadius.purgeDependencyOnElmtId(p3);
        this.__chipEnabled.purgeDependencyOnElmtId(p3);
        this.__chipActivated.purgeDependencyOnElmtId(p3);
        this.__isHover.purgeDependencyOnElmtId(p3);
        this.__chipScale.purgeDependencyOnElmtId(p3);
        this.__chipOpacity.purgeDependencyOnElmtId(p3);
        this.__chipBlendColor.purgeDependencyOnElmtId(p3);
        this.__deleteChip.purgeDependencyOnElmtId(p3);
        this.__chipNodeOnFocus.purgeDependencyOnElmtId(p3);
        this.__useDefaultSuffixIcon.purgeDependencyOnElmtId(p3);
        this.__suffixIconOnFocus.purgeDependencyOnElmtId(p3);
        this.__chipBreakPoints.purgeDependencyOnElmtId(p3);
        this.__isShowPressedBackGroundColor.purgeDependencyOnElmtId(p3);
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
        this.__isShowPressedBackGroundColor.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get chipSize() {
        return this.__chipSize.get();
    }
    set chipSize(o3) {
        this.__chipSize.set(o3);
    }
    get allowClose() {
        return this.__allowClose.get();
    }
    set allowClose(n3) {
        this.__allowClose.set(n3);
    }
    get prefixIcon() {
        return this.__prefixIcon.get();
    }
    set prefixIcon(m3) {
        this.__prefixIcon.set(m3);
    }
    get label() {
        return this.__label.get();
    }
    set label(l3) {
        this.__label.set(l3);
    }
    get suffixIcon() {
        return this.__suffixIcon.get();
    }
    set suffixIcon(k3) {
        this.__suffixIcon.set(k3);
    }
    get chipNodeBackgroundColor() {
        return this.__chipNodeBackgroundColor.get();
    }
    set chipNodeBackgroundColor(j3) {
        this.__chipNodeBackgroundColor.set(j3);
    }
    get chipNodeActivatedBackgroundColor() {
        return this.__chipNodeActivatedBackgroundColor.get();
    }
    set chipNodeActivatedBackgroundColor(i3) {
        this.__chipNodeActivatedBackgroundColor.set(i3);
    }
    get chipNodeRadius() {
        return this.__chipNodeRadius.get();
    }
    set chipNodeRadius(h3) {
        this.__chipNodeRadius.set(h3);
    }
    get chipEnabled() {
        return this.__chipEnabled.get();
    }
    set chipEnabled(g3) {
        this.__chipEnabled.set(g3);
    }
    get chipActivated() {
        return this.__chipActivated.get();
    }
    set chipActivated(f3) {
        this.__chipActivated.set(f3);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(e3) {
        this.__isHover.set(e3);
    }
    get chipScale() {
        return this.__chipScale.get();
    }
    set chipScale(d3) {
        this.__chipScale.set(d3);
    }
    get chipOpacity() {
        return this.__chipOpacity.get();
    }
    set chipOpacity(c3) {
        this.__chipOpacity.set(c3);
    }
    get chipBlendColor() {
        return this.__chipBlendColor.get();
    }
    set chipBlendColor(b3) {
        this.__chipBlendColor.set(b3);
    }
    get deleteChip() {
        return this.__deleteChip.get();
    }
    set deleteChip(a3) {
        this.__deleteChip.set(a3);
    }
    get chipNodeOnFocus() {
        return this.__chipNodeOnFocus.get();
    }
    set chipNodeOnFocus(z2) {
        this.__chipNodeOnFocus.set(z2);
    }
    get useDefaultSuffixIcon() {
        return this.__useDefaultSuffixIcon.get();
    }
    set useDefaultSuffixIcon(y2) {
        this.__useDefaultSuffixIcon.set(y2);
    }
    get suffixIconOnFocus() {
        return this.__suffixIconOnFocus.get();
    }
    set suffixIconOnFocus(x2) {
        this.__suffixIconOnFocus.set(x2);
    }
    get chipBreakPoints() {
        return this.__chipBreakPoints.get();
    }
    set chipBreakPoints(w2) {
        this.__chipBreakPoints.set(w2);
    }
    get isShowPressedBackGroundColor() {
        return this.__isShowPressedBackGroundColor.get();
    }
    set isShowPressedBackGroundColor(v2) {
        this.__isShowPressedBackGroundColor.set(v2);
    }
    isChipSizeEnum() {
        return typeof (this.chipSize) === 'string';
    }
    getLabelFontSize() {
        try {
            if (this.label?.fontSize !== void (0) && this.toVp(this.label.fontSize) >= 0) {
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
        catch (u2) {
            return 0;
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
    toVp(o2) {
        if (o2 === void (0)) {
            return Number.NEGATIVE_INFINITY;
        }
        switch (typeof (o2)) {
            case 'number':
                return o2;
            case 'object':
                try {
                    if (o2.id !== -1) {
                        return px2vp(getContext(this).resourceManager.getNumber(o2.id));
                    }
                    else {
                        return px2vp(getContext(this)
                            .resourceManager
                            .getNumberByName((o2.params[0]).split('.')[2]));
                    }
                }
                catch (t2) {
                    return Number.NEGATIVE_INFINITY;
                }
            case 'string':
                let p2 = new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i");
                let q2 = o2.match(p2);
                if (!q2) {
                    return Number.NEGATIVE_INFINITY;
                }
                let r2 = Number(q2?.[1] ?? 0);
                let s2 = q2?.[2] ?? 'vp';
                switch (s2.toLowerCase()) {
                    case 'px':
                        r2 = px2vp(r2);
                        break;
                    case 'fp':
                        r2 = px2vp(fp2px(r2));
                        break;
                    case 'lpx':
                        r2 = px2vp(lpx2px(r2));
                        break;
                    case '%':
                        r2 = Number.NEGATIVE_INFINITY;
                        break;
                    case 'vp':
                        break;
                    default:
                        break;
                }
                return r2;
            default:
                return Number.NEGATIVE_INFINITY;
        }
    }
    getLabelMargin() {
        let n2 = { left: 0, right: 0 };
        if (this.label?.labelMargin?.left !== void (0) && this.toVp(this.label.labelMargin.left) >= 0) {
            n2.left = this.label?.labelMargin?.left;
        }
        else if (this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                n2.left = this.theme.label.smallMargin.left;
            }
            else {
                n2.left = this.theme.label.normalMargin.left;
            }
        }
        if (this.label?.labelMargin?.right !== void (0) && this.toVp(this.label.labelMargin.right) >= 0) {
            n2.right = this.label?.labelMargin?.right;
        }
        else if (this.suffixIcon?.src || this.useDefaultSuffixIcon) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                n2.right = this.theme.label.smallMargin.right;
            }
            else {
                n2.right = this.theme.label.normalMargin.right;
            }
        }
        return n2;
    }
    getSuffixIconSize() {
        let m2 = { width: 0, height: 0 };
        if (this.suffixIcon?.size?.width !== void (0) && this.toVp(this.suffixIcon?.size?.width) >= 0) {
            m2.width = this.suffixIcon?.size?.width;
        }
        else {
            if (this.getSuffixIconSrc()) {
                m2.width = this.theme.suffixIcon.size.width;
            }
            else {
                m2.width = 0;
            }
        }
        if (this.suffixIcon?.size?.height !== void (0) && this.toVp(this.suffixIcon?.size?.height) >= 0) {
            m2.height = this.suffixIcon?.size?.height;
        }
        else {
            if (this.getSuffixIconSrc()) {
                m2.height = this.theme.suffixIcon.size.height;
            }
            else {
                m2.height = 0;
            }
        }
        return m2;
    }
    getPrefixIconSize() {
        let l2 = { width: 0, height: 0 };
        if (this.prefixIcon?.size?.width !== void (0) && this.toVp(this.prefixIcon?.size?.width) >= 0) {
            l2.width = this.prefixIcon?.size?.width;
        }
        else {
            if (this.prefixIcon?.src) {
                l2.width = this.theme.prefixIcon.size.width;
            }
            else {
                l2.width = 0;
            }
        }
        if (this.prefixIcon?.size?.height !== void (0) && this.toVp(this.prefixIcon?.size?.height) >= 0) {
            l2.height = this.prefixIcon?.size?.height;
        }
        else {
            if (this.prefixIcon?.src) {
                l2.height = this.theme.prefixIcon.size.height;
            }
            else {
                l2.height = 0;
            }
        }
        return l2;
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
        let i2;
        if (this.getChipActive()) {
            i2 = this.chipNodeActivatedBackgroundColor ?? this.theme.chipNode.activatedBackgroundColor;
        }
        else {
            i2 = this.chipNodeBackgroundColor ?? this.theme.chipNode.backgroundColor;
        }
        if (!this.isShowPressedBackGroundColor) {
            return i2;
        }
        let j2;
        try {
            j2 = ColorMetrics.resourceColor(i2);
        }
        catch (k2) {
            console.log(k2.toString());
            if (this.getChipActive()) {
                j2 = ColorMetrics.resourceColor(this.theme.chipNode.activatedBackgroundColor);
            }
            else {
                j2 = ColorMetrics.resourceColor(this.theme.chipNode.backgroundColor);
            }
        }
        return j2.blendColor(ColorMetrics.resourceColor("#19000000"))
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
        let h2 = 0;
        h2 += this.getChipNodePadding().left;
        h2 += this.toVp(this.getPrefixIconSize().width);
        h2 += this.toVp(this.getLabelMargin().left);
        h2 += this.getLabelWidth();
        h2 += this.toVp(this.getLabelMargin().right);
        h2 += this.toVp(this.getSuffixIconSize().width);
        h2 += this.getChipNodePadding().right;
        return h2;
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
    handleTouch(g2) {
        if (!this.getChipEnable()) {
            return;
        }
        if (this.isHover) {
            if (g2.type === TouchType.Down) {
                this.isShowPressedBackGroundColor = true;
            }
            else if (g2.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            }
        }
        else {
            if (g2.type === TouchType.Down) {
                this.isShowPressedBackGroundColor = true;
            }
            else if (g2.type === TouchType.Up) {
                this.isShowPressedBackGroundColor = false;
            }
        }
    }
    hoverAnimate(f2) {
        if (!this.getChipEnable()) {
            return;
        }
        this.isHover = f2;
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
        let c2 = this.getChipConstraintWidth();
        return Math.min(Math.max(this.getCalculateChipNodeWidth(), c2.minWidth), c2.maxWidth);
    }
    getFocusOverlaySize() {
        return {
            width: Math.max(this.getChipNodeWidth(), this.getChipConstraintWidth().minWidth) + 8,
            height: this.getChipNodeHeight() + 8
        };
    }
    getChipConstraintWidth() {
        let a2 = this.getReserveChipNodeWidth();
        if (!this.isChipSizeEnum()) {
            this.chipNodeSize = this.chipSize;
            if (this.chipNodeSize?.width !== void (0) && this.toVp(this.chipNodeSize?.width) >= 0) {
                return { minWidth: a2, maxWidth: this.chipNodeSize.width };
            }
        }
        let b2 = this.getCalculateChipNodeWidth();
        switch (this.chipBreakPoints) {
            case BreakPointsType.SM:
                return {
                    minWidth: a2,
                    maxWidth: Math.min(b2, this.theme.chipNode.breakPointConstraintWidth.breakPointSmMaxWidth)
                };
            case BreakPointsType.MD:
                return {
                    minWidth: Math.max(b2, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(b2, this.theme.chipNode.breakPointConstraintWidth.breakPointMdMaxWidth)
                };
            case BreakPointsType.LG:
                return {
                    minWidth: Math.max(b2, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
                    maxWidth: Math.min(b2, this.theme.chipNode.breakPointConstraintWidth.breakPointLgMaxWidth)
                };
            default:
                return { minWidth: a2, maxWidth: b2 };
        }
    }
    focusOverlay(o1 = null) {
        this.observeComponentCreation2((y1, z1) => {
            Stack.create();
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((r1, s1) => {
            If.create();
            if (this.chipNodeOnFocus && !this.suffixIconOnFocus) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w1, x1) => {
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
        this.smListener.on("change", (n1) => {
            if (n1.matches) {
                this.chipBreakPoints = BreakPointsType.SM;
            }
        });
        this.mdListener.on("change", (m1) => {
            if (m1.matches) {
                this.chipBreakPoints = BreakPointsType.MD;
            }
        });
        this.lgListener.on("change", (l1) => {
            if (l1.matches) {
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
        this.observeComponentCreation2((y, z) => {
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
            Row.onTouch((h1) => {
                this.handleTouch(h1);
            });
            Row.onHover((g1) => {
                if (this.isShowPressedBackGroundColor == false) {
                    this.isShowPressedBackGroundColor = true;
                }
                else {
                    this.isShowPressedBackGroundColor = false;
                }
            });
            Row.onKeyEvent((f1) => {
                if (f1.type === KeyType.Down && f1.keyCode === KeyCode.KEYCODE_FORWARD_DEL && !this.suffixIconOnFocus) {
                    this.deleteChipNodeAnimate();
                }
            });
            Row.onClick(this.onClicked === noop ? undefined : this.onClicked.bind(this));
        }, Row);
        this.observeComponentCreation2((r, s) => {
            If.create();
            if (this.prefixIcon?.src !== "") {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w, x) => {
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
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((p, q) => {
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
