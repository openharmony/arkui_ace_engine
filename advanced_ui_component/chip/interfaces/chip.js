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
(function (i4) {
    i4["NORMAL"] = "NORMAL";
    i4["SMALL"] = "SMALL";
})(ChipSize || (ChipSize = {}));
var BreakPointsType;
(function (h4) {
    h4["SM"] = "SM";
    h4["MD"] = "MD";
    h4["LG"] = "LG";
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
export function Chip(w3, x3 = null) {
    const y3 = w3;
    {
        (x3 ? x3 : this).observeComponentCreation2((a4, b4, c4 = y3) => {
            if (b4) {
                let d4 = new ChipComponent(x3 ? x3 : this, {
                    chipSize: c4.size,
                    prefixIcon: c4.prefixIcon,
                    label: c4.label,
                    suffixIcon: c4.suffixIcon,
                    allowClose: c4.allowClose,
                    chipEnabled: c4.enabled,
                    chipActivated: c4.activated,
                    chipNodeBackgroundColor: c4.backgroundColor,
                    chipNodeActivatedBackgroundColor: c4.activatedBackgroundColor,
                    chipNodeRadius: c4.borderRadius,
                    onClose: c4.onClose,
                    onClicked: c4.onClicked,
                }, undefined, a4, () => { }, { page: "library/src/main/ets/components/chip/chip.ets", line: 192, col: 3 });
                ViewPU.create(d4);
                let e4 = () => {
                    return {
                        chipSize: c4.size,
                        prefixIcon: c4.prefixIcon,
                        label: c4.label,
                        suffixIcon: c4.suffixIcon,
                        allowClose: c4.allowClose,
                        chipEnabled: c4.enabled,
                        chipActivated: c4.activated,
                        chipNodeBackgroundColor: c4.backgroundColor,
                        chipNodeActivatedBackgroundColor: c4.activatedBackgroundColor,
                        chipNodeRadius: c4.borderRadius,
                        onClose: c4.onClose,
                        onClicked: c4.onClicked
                    };
                };
                d4.paramsGenerator_ = e4;
            }
            else {
                (x3 ? x3 : this).updateStateVarsOfChildByElmtId(a4, {
                    chipSize: c4.size,
                    prefixIcon: c4.prefixIcon,
                    label: c4.label,
                    suffixIcon: c4.suffixIcon,
                    allowClose: c4.allowClose,
                    chipEnabled: c4.enabled,
                    chipActivated: c4.activated,
                    chipNodeBackgroundColor: c4.backgroundColor,
                    chipNodeActivatedBackgroundColor: c4.activatedBackgroundColor,
                    chipNodeRadius: c4.borderRadius
                });
            }
        }, { name: "ChipComponent" });
    }
}
export class ChipComponent extends ViewPU {
    constructor(q3, r3, s3, t3 = -1, u3 = undefined, v3) {
        super(q3, s3, t3, v3);
        if (typeof u3 === "function") {
            this.paramsGenerator_ = u3;
        }
        this.theme = defaultTheme;
        this.__chipSize = new SynchedPropertyObjectOneWayPU(r3.chipSize, this, "chipSize");
        this.__allowClose = new SynchedPropertySimpleOneWayPU(r3.allowClose, this, "allowClose");
        this.__prefixIcon = new SynchedPropertyObjectOneWayPU(r3.prefixIcon, this, "prefixIcon");
        this.__label = new SynchedPropertyObjectOneWayPU(r3.label, this, "label");
        this.__suffixIcon = new SynchedPropertyObjectOneWayPU(r3.suffixIcon, this, "suffixIcon");
        this.__chipNodeBackgroundColor = new SynchedPropertyObjectOneWayPU(r3.chipNodeBackgroundColor, this, "chipNodeBackgroundColor");
        this.__chipNodeActivatedBackgroundColor = new SynchedPropertyObjectOneWayPU(r3.chipNodeActivatedBackgroundColor, this, "chipNodeActivatedBackgroundColor");
        this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(r3.chipNodeRadius, this, "chipNodeRadius");
        this.__chipEnabled = new SynchedPropertySimpleOneWayPU(r3.chipEnabled, this, "chipEnabled");
        this.__chipActivated = new SynchedPropertySimpleOneWayPU(r3.chipActivated, this, "chipActivated");
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
        this.setInitiallyProvidedValue(r3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(p3) {
        if (p3.theme !== undefined) {
            this.theme = p3.theme;
        }
        if (p3.chipSize === undefined) {
            this.__chipSize.set(ChipSize.NORMAL);
        }
        if (p3.allowClose === undefined) {
            this.__allowClose.set(true);
        }
        if (p3.prefixIcon === undefined) {
            this.__prefixIcon.set({ src: "" });
        }
        if (p3.label === undefined) {
            this.__label.set({ text: "" });
        }
        if (p3.suffixIcon === undefined) {
            this.__suffixIcon.set({ src: "" });
        }
        if (p3.chipNodeBackgroundColor === undefined) {
            this.__chipNodeBackgroundColor.set(this.theme.chipNode.backgroundColor);
        }
        if (p3.chipNodeActivatedBackgroundColor === undefined) {
            this.__chipNodeActivatedBackgroundColor.set(this.theme.chipNode.activatedBackgroundColor);
        }
        if (p3.chipNodeRadius === undefined) {
            this.__chipNodeRadius.set(void (0));
        }
        if (p3.chipEnabled === undefined) {
            this.__chipEnabled.set(true);
        }
        if (p3.chipActivated === undefined) {
            this.__chipActivated.set(false);
        }
        if (p3.isHover !== undefined) {
            this.isHover = p3.isHover;
        }
        if (p3.chipScale !== undefined) {
            this.chipScale = p3.chipScale;
        }
        if (p3.chipOpacity !== undefined) {
            this.chipOpacity = p3.chipOpacity;
        }
        if (p3.chipBlendColor !== undefined) {
            this.chipBlendColor = p3.chipBlendColor;
        }
        if (p3.deleteChip !== undefined) {
            this.deleteChip = p3.deleteChip;
        }
        if (p3.chipNodeOnFocus !== undefined) {
            this.chipNodeOnFocus = p3.chipNodeOnFocus;
        }
        if (p3.useDefaultSuffixIcon !== undefined) {
            this.useDefaultSuffixIcon = p3.useDefaultSuffixIcon;
        }
        if (p3.chipNodeSize !== undefined) {
            this.chipNodeSize = p3.chipNodeSize;
        }
        if (p3.onClose !== undefined) {
            this.onClose = p3.onClose;
        }
        if (p3.onClicked !== undefined) {
            this.onClicked = p3.onClicked;
        }
        if (p3.suffixIconOnFocus !== undefined) {
            this.suffixIconOnFocus = p3.suffixIconOnFocus;
        }
        if (p3.chipBreakPoints !== undefined) {
            this.chipBreakPoints = p3.chipBreakPoints;
        }
        if (p3.smListener !== undefined) {
            this.smListener = p3.smListener;
        }
        if (p3.mdListener !== undefined) {
            this.mdListener = p3.mdListener;
        }
        if (p3.lgListener !== undefined) {
            this.lgListener = p3.lgListener;
        }
        if (p3.isShowPressedBackGroundColor !== undefined) {
            this.isShowPressedBackGroundColor = p3.isShowPressedBackGroundColor;
        }
    }
    updateStateVars(o3) {
        this.__chipSize.reset(o3.chipSize);
        this.__allowClose.reset(o3.allowClose);
        this.__prefixIcon.reset(o3.prefixIcon);
        this.__label.reset(o3.label);
        this.__suffixIcon.reset(o3.suffixIcon);
        this.__chipNodeBackgroundColor.reset(o3.chipNodeBackgroundColor);
        this.__chipNodeActivatedBackgroundColor.reset(o3.chipNodeActivatedBackgroundColor);
        this.__chipNodeRadius.reset(o3.chipNodeRadius);
        this.__chipEnabled.reset(o3.chipEnabled);
        this.__chipActivated.reset(o3.chipActivated);
    }
    purgeVariableDependenciesOnElmtId(n3) {
        this.__chipSize.purgeDependencyOnElmtId(n3);
        this.__allowClose.purgeDependencyOnElmtId(n3);
        this.__prefixIcon.purgeDependencyOnElmtId(n3);
        this.__label.purgeDependencyOnElmtId(n3);
        this.__suffixIcon.purgeDependencyOnElmtId(n3);
        this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(n3);
        this.__chipNodeActivatedBackgroundColor.purgeDependencyOnElmtId(n3);
        this.__chipNodeRadius.purgeDependencyOnElmtId(n3);
        this.__chipEnabled.purgeDependencyOnElmtId(n3);
        this.__chipActivated.purgeDependencyOnElmtId(n3);
        this.__isHover.purgeDependencyOnElmtId(n3);
        this.__chipScale.purgeDependencyOnElmtId(n3);
        this.__chipOpacity.purgeDependencyOnElmtId(n3);
        this.__chipBlendColor.purgeDependencyOnElmtId(n3);
        this.__deleteChip.purgeDependencyOnElmtId(n3);
        this.__chipNodeOnFocus.purgeDependencyOnElmtId(n3);
        this.__useDefaultSuffixIcon.purgeDependencyOnElmtId(n3);
        this.__suffixIconOnFocus.purgeDependencyOnElmtId(n3);
        this.__chipBreakPoints.purgeDependencyOnElmtId(n3);
        this.__isShowPressedBackGroundColor.purgeDependencyOnElmtId(n3);
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
    set chipSize(m3) {
        this.__chipSize.set(m3);
    }
    get allowClose() {
        return this.__allowClose.get();
    }
    set allowClose(l3) {
        this.__allowClose.set(l3);
    }
    get prefixIcon() {
        return this.__prefixIcon.get();
    }
    set prefixIcon(k3) {
        this.__prefixIcon.set(k3);
    }
    get label() {
        return this.__label.get();
    }
    set label(j3) {
        this.__label.set(j3);
    }
    get suffixIcon() {
        return this.__suffixIcon.get();
    }
    set suffixIcon(i3) {
        this.__suffixIcon.set(i3);
    }
    get chipNodeBackgroundColor() {
        return this.__chipNodeBackgroundColor.get();
    }
    set chipNodeBackgroundColor(h3) {
        this.__chipNodeBackgroundColor.set(h3);
    }
    get chipNodeActivatedBackgroundColor() {
        return this.__chipNodeActivatedBackgroundColor.get();
    }
    set chipNodeActivatedBackgroundColor(g3) {
        this.__chipNodeActivatedBackgroundColor.set(g3);
    }
    get chipNodeRadius() {
        return this.__chipNodeRadius.get();
    }
    set chipNodeRadius(f3) {
        this.__chipNodeRadius.set(f3);
    }
    get chipEnabled() {
        return this.__chipEnabled.get();
    }
    set chipEnabled(e3) {
        this.__chipEnabled.set(e3);
    }
    get chipActivated() {
        return this.__chipActivated.get();
    }
    set chipActivated(d3) {
        this.__chipActivated.set(d3);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(c3) {
        this.__isHover.set(c3);
    }
    get chipScale() {
        return this.__chipScale.get();
    }
    set chipScale(b3) {
        this.__chipScale.set(b3);
    }
    get chipOpacity() {
        return this.__chipOpacity.get();
    }
    set chipOpacity(a3) {
        this.__chipOpacity.set(a3);
    }
    get chipBlendColor() {
        return this.__chipBlendColor.get();
    }
    set chipBlendColor(z2) {
        this.__chipBlendColor.set(z2);
    }
    get deleteChip() {
        return this.__deleteChip.get();
    }
    set deleteChip(y2) {
        this.__deleteChip.set(y2);
    }
    get chipNodeOnFocus() {
        return this.__chipNodeOnFocus.get();
    }
    set chipNodeOnFocus(x2) {
        this.__chipNodeOnFocus.set(x2);
    }
    get useDefaultSuffixIcon() {
        return this.__useDefaultSuffixIcon.get();
    }
    set useDefaultSuffixIcon(w2) {
        this.__useDefaultSuffixIcon.set(w2);
    }
    get suffixIconOnFocus() {
        return this.__suffixIconOnFocus.get();
    }
    set suffixIconOnFocus(v2) {
        this.__suffixIconOnFocus.set(v2);
    }
    get chipBreakPoints() {
        return this.__chipBreakPoints.get();
    }
    set chipBreakPoints(u2) {
        this.__chipBreakPoints.set(u2);
    }
    get isShowPressedBackGroundColor() {
        return this.__isShowPressedBackGroundColor.get();
    }
    set isShowPressedBackGroundColor(t2) {
        this.__isShowPressedBackGroundColor.set(t2);
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
        catch (s2) {
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
    toVp(m2) {
        if (m2 === void (0)) {
            return Number.NEGATIVE_INFINITY;
        }
        switch (typeof (m2)) {
            case 'number':
                return m2;
            case 'object':
                try {
                    if (m2.id !== -1) {
                        return px2vp(getContext(this).resourceManager.getNumber(m2.id));
                    }
                    else {
                        return px2vp(getContext(this)
                            .resourceManager
                            .getNumberByName((m2.params[0]).split('.')[2]));
                    }
                }
                catch (r2) {
                    return Number.NEGATIVE_INFINITY;
                }
            case 'string':
                let n2 = new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i");
                let o2 = m2.match(n2);
                if (!o2) {
                    return Number.NEGATIVE_INFINITY;
                }
                let p2 = Number(o2?.[1] ?? 0);
                let q2 = o2?.[2] ?? 'vp';
                switch (q2.toLowerCase()) {
                    case 'px':
                        p2 = px2vp(p2);
                        break;
                    case 'fp':
                        p2 = px2vp(fp2px(p2));
                        break;
                    case 'lpx':
                        p2 = px2vp(lpx2px(p2));
                        break;
                    case '%':
                        p2 = Number.NEGATIVE_INFINITY;
                        break;
                    case 'vp':
                        break;
                    default:
                        break;
                }
                return p2;
            default:
                return Number.NEGATIVE_INFINITY;
        }
    }
    getLabelMargin() {
        let l2 = { left: 0, right: 0 };
        if (this.label?.labelMargin?.left !== void (0) && this.toVp(this.label.labelMargin.left) >= 0) {
            l2.left = this.label?.labelMargin?.left;
        }
        else if (this.prefixIcon?.src) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                l2.left = this.theme.label.smallMargin.left;
            }
            else {
                l2.left = this.theme.label.normalMargin.left;
            }
        }
        if (this.label?.labelMargin?.right !== void (0) && this.toVp(this.label.labelMargin.right) >= 0) {
            l2.right = this.label?.labelMargin?.right;
        }
        else if (this.suffixIcon?.src || this.useDefaultSuffixIcon) {
            if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
                l2.right = this.theme.label.smallMargin.right;
            }
            else {
                l2.right = this.theme.label.normalMargin.right;
            }
        }
        return l2;
    }
    getSuffixIconSize() {
        let k2 = { width: 0, height: 0 };
        if (this.suffixIcon?.size?.width !== void (0) && this.toVp(this.suffixIcon?.size?.width) >= 0) {
            k2.width = this.suffixIcon?.size?.width;
        }
        else {
            if (this.getSuffixIconSrc()) {
                k2.width = this.theme.suffixIcon.size.width;
            }
            else {
                k2.width = 0;
            }
        }
        if (this.suffixIcon?.size?.height !== void (0) && this.toVp(this.suffixIcon?.size?.height) >= 0) {
            k2.height = this.suffixIcon?.size?.height;
        }
        else {
            if (this.getSuffixIconSrc()) {
                k2.height = this.theme.suffixIcon.size.height;
            }
            else {
                k2.height = 0;
            }
        }
        return k2;
    }
    getPrefixIconSize() {
        let j2 = { width: 0, height: 0 };
        if (this.prefixIcon?.size?.width !== void (0) && this.toVp(this.prefixIcon?.size?.width) >= 0) {
            j2.width = this.prefixIcon?.size?.width;
        }
        else {
            if (this.prefixIcon?.src) {
                j2.width = this.theme.prefixIcon.size.width;
            }
            else {
                j2.width = 0;
            }
        }
        if (this.prefixIcon?.size?.height !== void (0) && this.toVp(this.prefixIcon?.size?.height) >= 0) {
            j2.height = this.prefixIcon?.size?.height;
        }
        else {
            if (this.prefixIcon?.src) {
                j2.height = this.theme.prefixIcon.size.height;
            }
            else {
                j2.height = 0;
            }
        }
        return j2;
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
        return ColorMetrics
            .resourceColor(i2)
            .blendColor(ColorMetrics.resourceColor("#19000000"))
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
