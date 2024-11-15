/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const measure = requireNapi('@ohos.measure');

export var IconType;
(function (x15) {
    x15[x15["BADGE"] = 1] = "BADGE";
    x15[x15["NORMAL_ICON"] = 2] = "NORMAL_ICON";
    x15[x15["SYSTEM_ICON"] = 3] = "SYSTEM_ICON";
    x15[x15["HEAD_SCULPTURE"] = 4] = "HEAD_SCULPTURE";
    x15[x15["APP_ICON"] = 5] = "APP_ICON";
    x15[x15["PREVIEW"] = 6] = "PREVIEW";
    x15[x15["LONGITUDINAL"] = 7] = "LONGITUDINAL";
    x15[x15["VERTICAL"] = 8] = "VERTICAL";
})(IconType || (IconType = {}));
var FontSizeScaleLevel;
(function (w15) {
    w15[w15["LEVEL1"] = 1.75] = "LEVEL1";
    w15[w15["LEVEL2"] = 2] = "LEVEL2";
    w15[w15["LEVEL3"] = 3.2] = "LEVEL3";
})(FontSizeScaleLevel || (FontSizeScaleLevel = {}));
var ItemHeight;
(function (v15) {
    v15[v15["FIRST_HEIGHT"] = 48] = "FIRST_HEIGHT";
    v15[v15["SECOND_HEIGHT"] = 56] = "SECOND_HEIGHT";
    v15[v15["THIRD_HEIGHT"] = 64] = "THIRD_HEIGHT";
    v15[v15["FOURTH_HEIGHT"] = 72] = "FOURTH_HEIGHT";
    v15[v15["FIFTH_HEIGHT"] = 96] = "FIFTH_HEIGHT";
})(ItemHeight || (ItemHeight = {}));
const TEXT_MAX_LINE = 1;
const ITEM_BORDER_SHOWN = 2;
const TEXT_COLUMN_SPACE = 4;
const TEXT_SAFE_MARGIN = 8;
const LISTITEM_PADDING = 6;
const SWITCH_PADDING = 4;
const STACK_PADDING = 4;
const BADGE_SIZE = 8;
const SMALL_ICON_SIZE = 16;
const SYSTEM_ICON_SIZE = 24;
const TEXT_ARROW_HEIGHT = 32;
const SAFE_LIST_PADDING = 32;
const HEADSCULPTURE_SIZE = 40;
const BUTTON_SIZE = 28;
const APP_ICON_SIZE = 64;
const PREVIEW_SIZE = 96;
const LONGITUDINAL_SIZE = 96;
const VERTICAL_SIZE = 96;
const NORMAL_ITEM_ROW_SPACE = 16;
const SPECIAL_ITEM_ROW_SPACE = 0;
const SPECIAL_ICON_SIZE = 0;
const DEFAULT_ROW_SPACE = 0;
const SPECICAL_ROW_SPACE = 4;
const OPERATEITEM_ICONLIKE_SIZE = 24;
const OPERATEITEM_SELECTIONBOX_PADDING_SIZE = 2;
const OPERATEITEM_ARROW_WIDTH = 12;
const OPERATEITEM_ICON_CLICKABLE_SIZE = 40;
const OPERATEITEM_IMAGE_SIZE = 48;
const RIGHT_CONTENT_NULL_LEFTWIDTH = '100%';
const RIGHT_CONTENT_NULL_RIGHTWIDTH = '0vp';
const LEFT_PART_WIDTH = 'calc(66% - 16vp)';
const RIGHT_PART_WIDTH = '34%';
const LEFT_ONLY_ARROW_WIDTH = 'calc(100% - 40vp)';
const RIGHT_ONLY_ARROW_WIDTH = '24vp';
const ACCESSIBILITY_LEVEL_NO = 'no';
const ICON_SIZE_MAP = new Map([
    [IconType.BADGE, BADGE_SIZE],
    [IconType.NORMAL_ICON, SMALL_ICON_SIZE],
    [IconType.SYSTEM_ICON, SYSTEM_ICON_SIZE],
    [IconType.HEAD_SCULPTURE, HEADSCULPTURE_SIZE],
    [IconType.APP_ICON, APP_ICON_SIZE],
    [IconType.PREVIEW, PREVIEW_SIZE],
    [IconType.LONGITUDINAL, LONGITUDINAL_SIZE],
    [IconType.VERTICAL, VERTICAL_SIZE]
]);
const IS_CLOSE_CHILD_FOCUS = LengthMetrics.resource({
    "id": -1,
    "type": 10002,
    params: ['sys.float.composeListItem_focus_dynamic_effect'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
}).value !== 1;
const RECOVER_YSCALE = 1;
const CLEAR_SHADOW = -1;
const OPERATE_ITEM_RADIUS = 50;
const OPERATE_ITEM_BACKGROUND_COLOR = '#33000000';
const DEFUALT_RADIO_CHECKBOX_BORDER_COLOR = {
    "id": -1,
    "type": 10001,
    params: ['sys.color.ohos_id_color_switch_outline_off'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
const OPERATE_ITECOLOR = '#99000000';
const MARQUEE_OR_ELLIPSIS = 1;
const IS_MARQUEE_OR_ELLIPSIS = LengthMetrics.resource({
    "id": -1,
    "type": 10002,
    params: ['sys.float.composeListItem_right_textOverflow'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
}).value;
const UNUSUAL = -1;
const FOCUSED_BG = {
    "id": -1,
    "type": 10001,
    params: ['sys.color.composeListItem_container_focus_color'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
const NORMAL_BG = {
    "id": -1,
    "type": 10001,
    params: ['sys.color.composeListItem_container_normal_color'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
const FOCUSED_SCALE = LengthMetrics.resource({
    "id": -1,
    "type": 10002,
    params: ['sys.float.composeListItem_focus_magnification'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
}).value;
const FOCUSED_SHADOW = LengthMetrics.resource({
    "id": -1,
    "type": 10002,
    params: ['sys.float.composeListItem_focus_shadow_attribute'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
})
    .value;
const NORMAL_SHADOW = LengthMetrics.resource({
    "id": -1,
    "type": 10002,
    params: ['sys.float.composeListItem_normal_shadow_attribute'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
})
    .value;
const PADDING = {
    "id": -1,
    "type": 10002,
    params: ['sys.float.composeListItem_padding'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};

class ContentItemStruct extends ViewPU {
    constructor(p15, q15, r15, s15 = -1, t15 = undefined, u15) {
        super(p15, r15, s15, u15);
        if (typeof t15 === "function") {
            this.paramsGenerator_ = t15;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(q15.iconStyle, this, "iconStyle");
        this.__icon = new SynchedPropertyObjectOneWayPU(q15.icon, this, "icon");
        this.__primaryText = new SynchedPropertyObjectOneWayPU(q15.primaryText, this, "primaryText");
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(q15.secondaryText, this, "secondaryText");
        this.__description = new SynchedPropertyObjectOneWayPU(q15.description, this, "description");
        this.__itemRowSpace = new ObservedPropertySimplePU(NORMAL_ITEM_ROW_SPACE, this, "itemRowSpace");
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(q15.leftWidth, this, "leftWidth");
        this.__primaryTextColor = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_primary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "primaryTextColor");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "secondaryTextColor");
        this.__descriptionColor = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "descriptionColor");
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(q15.fontSizeScale, this, "fontSizeScale");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(q15.parentDirection, this, "parentDirection");
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(q15.itemDirection, this, "itemDirection");
        this.__isFocus = new SynchedPropertySimpleOneWayPU(q15.isFocus, this, "isFocus");
        this.__primaryTextSize = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_text_size_body1'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "primaryTextSize");
        this.__primaryTextColors = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.font_primary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "primaryTextColors");
        this.__itemHeight = new SynchedPropertyObjectOneWayPU(q15.itemHeight, this, "itemHeight");
        this.__iconColor = new ObservedPropertyObjectPU(null, this, "iconColor");
        this.__secondaryTextColors = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.font_secondary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "secondaryTextColors");
        this.__secondaryThirdTextSize = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10002,
            params: ['sys.float.composeListItem_left_secondary_tertiary_text_size'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "secondaryThirdTextSize");
        this.__descriptionColors = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.font_tertiary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "descriptionColors");
        this.__isWrapText = new SynchedPropertyObjectTwoWayPU(q15.isWrapText, this, "isWrapText");
        this.__isWrapFristText = new ObservedPropertyObjectPU(false, this, "isWrapFristText");
        this.__isWrapSecondText = new ObservedPropertyObjectPU(false, this, "isWrapSecondText");
        this.__isWrapThirdText = new ObservedPropertyObjectPU(false, this, "isWrapThirdText");
        this.setInitiallyProvidedValue(q15);
        this.declareWatch("iconStyle", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("primaryText", this.onPropChange);
        this.declareWatch("secondaryText", this.onPropChange);
        this.declareWatch("description", this.onPropChange);
        this.declareWatch("primaryTextColor", this.onPropChange);
        this.declareWatch("secondaryTextColor", this.onPropChange);
        this.declareWatch("descriptionColor", this.onPropChange);
        this.declareWatch("isFocus", this.onPropChange);
        this.declareWatch("isWrapFristText", this.onWrapChange);
        this.declareWatch("isWrapSecondText", this.onWrapChange);
        this.declareWatch("isWrapThirdText", this.onWrapChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(o15) {
        if (o15.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (o15.icon === undefined) {
            this.__icon.set(null);
        }
        if (o15.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (o15.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (o15.description === undefined) {
            this.__description.set(null);
        }
        if (o15.itemRowSpace !== undefined) {
            this.itemRowSpace = o15.itemRowSpace;
        }
        if (o15.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (o15.primaryTextColor !== undefined) {
            this.primaryTextColor = o15.primaryTextColor;
        }
        if (o15.secondaryTextColor !== undefined) {
            this.secondaryTextColor = o15.secondaryTextColor;
        }
        if (o15.descriptionColor !== undefined) {
            this.descriptionColor = o15.descriptionColor;
        }
        if (o15.isFocus === undefined) {
            this.__isFocus.set(false);
        }
        if (o15.primaryTextSize !== undefined) {
            this.primaryTextSize = o15.primaryTextSize;
        }
        if (o15.primaryTextColors !== undefined) {
            this.primaryTextColors = o15.primaryTextColors;
        }
        if (o15.itemHeight === undefined) {
            this.__itemHeight.set(null);
        }
        if (o15.iconColor !== undefined) {
            this.iconColor = o15.iconColor;
        }
        if (o15.secondaryTextColors !== undefined) {
            this.secondaryTextColors = o15.secondaryTextColors;
        }
        if (o15.secondaryThirdTextSize !== undefined) {
            this.secondaryThirdTextSize = o15.secondaryThirdTextSize;
        }
        if (o15.descriptionColors !== undefined) {
            this.descriptionColors = o15.descriptionColors;
        }
        if (o15.isWrapFristText !== undefined) {
            this.isWrapFristText = o15.isWrapFristText;
        }
        if (o15.isWrapSecondText !== undefined) {
            this.isWrapSecondText = o15.isWrapSecondText;
        }
        if (o15.isWrapThirdText !== undefined) {
            this.isWrapThirdText = o15.isWrapThirdText;
        }
    }

    updateStateVars(n15) {
        this.__iconStyle.reset(n15.iconStyle);
        this.__icon.reset(n15.icon);
        this.__primaryText.reset(n15.primaryText);
        this.__secondaryText.reset(n15.secondaryText);
        this.__description.reset(n15.description);
        this.__leftWidth.reset(n15.leftWidth);
        this.__fontSizeScale.reset(n15.fontSizeScale);
        this.__parentDirection.reset(n15.parentDirection);
        this.__itemDirection.reset(n15.itemDirection);
        this.__isFocus.reset(n15.isFocus);
        this.__itemHeight.reset(n15.itemHeight);
    }

    purgeVariableDependenciesOnElmtId(m15) {
        this.__iconStyle.purgeDependencyOnElmtId(m15);
        this.__icon.purgeDependencyOnElmtId(m15);
        this.__primaryText.purgeDependencyOnElmtId(m15);
        this.__secondaryText.purgeDependencyOnElmtId(m15);
        this.__description.purgeDependencyOnElmtId(m15);
        this.__itemRowSpace.purgeDependencyOnElmtId(m15);
        this.__leftWidth.purgeDependencyOnElmtId(m15);
        this.__primaryTextColor.purgeDependencyOnElmtId(m15);
        this.__secondaryTextColor.purgeDependencyOnElmtId(m15);
        this.__descriptionColor.purgeDependencyOnElmtId(m15);
        this.__fontSizeScale.purgeDependencyOnElmtId(m15);
        this.__parentDirection.purgeDependencyOnElmtId(m15);
        this.__itemDirection.purgeDependencyOnElmtId(m15);
        this.__isFocus.purgeDependencyOnElmtId(m15);
        this.__primaryTextSize.purgeDependencyOnElmtId(m15);
        this.__primaryTextColors.purgeDependencyOnElmtId(m15);
        this.__itemHeight.purgeDependencyOnElmtId(m15);
        this.__iconColor.purgeDependencyOnElmtId(m15);
        this.__secondaryTextColors.purgeDependencyOnElmtId(m15);
        this.__secondaryThirdTextSize.purgeDependencyOnElmtId(m15);
        this.__descriptionColors.purgeDependencyOnElmtId(m15);
        this.__isWrapText.purgeDependencyOnElmtId(m15);
        this.__isWrapFristText.purgeDependencyOnElmtId(m15);
        this.__isWrapSecondText.purgeDependencyOnElmtId(m15);
        this.__isWrapThirdText.purgeDependencyOnElmtId(m15);
    }

    aboutToBeDeleted() {
        this.__iconStyle.aboutToBeDeleted();
        this.__icon.aboutToBeDeleted();
        this.__primaryText.aboutToBeDeleted();
        this.__secondaryText.aboutToBeDeleted();
        this.__description.aboutToBeDeleted();
        this.__itemRowSpace.aboutToBeDeleted();
        this.__leftWidth.aboutToBeDeleted();
        this.__primaryTextColor.aboutToBeDeleted();
        this.__secondaryTextColor.aboutToBeDeleted();
        this.__descriptionColor.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__parentDirection.aboutToBeDeleted();
        this.__itemDirection.aboutToBeDeleted();
        this.__isFocus.aboutToBeDeleted();
        this.__primaryTextSize.aboutToBeDeleted();
        this.__primaryTextColors.aboutToBeDeleted();
        this.__itemHeight.aboutToBeDeleted();
        this.__iconColor.aboutToBeDeleted();
        this.__secondaryTextColors.aboutToBeDeleted();
        this.__secondaryThirdTextSize.aboutToBeDeleted();
        this.__descriptionColors.aboutToBeDeleted();
        this.__isWrapText.aboutToBeDeleted();
        this.__isWrapFristText.aboutToBeDeleted();
        this.__isWrapSecondText.aboutToBeDeleted();
        this.__isWrapThirdText.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get iconStyle() {
        return this.__iconStyle.get();
    }

    set iconStyle(l15) {
        this.__iconStyle.set(l15);
    }

    get icon() {
        return this.__icon.get();
    }

    set icon(k15) {
        this.__icon.set(k15);
    }

    get primaryText() {
        return this.__primaryText.get();
    }

    set primaryText(j15) {
        this.__primaryText.set(j15);
    }

    get secondaryText() {
        return this.__secondaryText.get();
    }

    set secondaryText(i15) {
        this.__secondaryText.set(i15);
    }

    get description() {
        return this.__description.get();
    }

    set description(h15) {
        this.__description.set(h15);
    }

    get itemRowSpace() {
        return this.__itemRowSpace.get();
    }

    set itemRowSpace(g15) {
        this.__itemRowSpace.set(g15);
    }

    get leftWidth() {
        return this.__leftWidth.get();
    }

    set leftWidth(f15) {
        this.__leftWidth.set(f15);
    }

    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }

    set primaryTextColor(e15) {
        this.__primaryTextColor.set(e15);
    }

    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }

    set secondaryTextColor(d15) {
        this.__secondaryTextColor.set(d15);
    }

    get descriptionColor() {
        return this.__descriptionColor.get();
    }

    set descriptionColor(c15) {
        this.__descriptionColor.set(c15);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(b15) {
        this.__fontSizeScale.set(b15);
    }

    get parentDirection() {
        return this.__parentDirection.get();
    }

    set parentDirection(a15) {
        this.__parentDirection.set(a15);
    }

    get itemDirection() {
        return this.__itemDirection.get();
    }

    set itemDirection(z14) {
        this.__itemDirection.set(z14);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(y14) {
        this.__isFocus.set(y14);
    }

    get primaryTextSize() {
        return this.__primaryTextSize.get();
    }

    set primaryTextSize(x14) {
        this.__primaryTextSize.set(x14);
    }

    get primaryTextColors() {
        return this.__primaryTextColors.get();
    }

    set primaryTextColors(w14) {
        this.__primaryTextColors.set(w14);
    }

    get itemHeight() {
        return this.__itemHeight.get();
    }

    set itemHeight(v14) {
        this.__itemHeight.set(v14);
    }

    get iconColor() {
        return this.__iconColor.get();
    }

    set iconColor(u14) {
        this.__iconColor.set(u14);
    }

    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }

    set secondaryTextColors(t14) {
        this.__secondaryTextColors.set(t14);
    }

    get secondaryThirdTextSize() {
        return this.__secondaryThirdTextSize.get();
    }

    set secondaryThirdTextSize(s14) {
        this.__secondaryThirdTextSize.set(s14);
    }

    get descriptionColors() {
        return this.__descriptionColors.get();
    }

    set descriptionColors(r14) {
        this.__descriptionColors.set(r14);
    }

    get isWrapText() {
        return this.__isWrapText.get();
    }

    set isWrapText(q14) {
        this.__isWrapText.set(q14);
    }

    get isWrapFristText() {
        return this.__isWrapFristText.get();
    }

    set isWrapFristText(p14) {
        this.__isWrapFristText.set(p14);
    }

    get isWrapSecondText() {
        return this.__isWrapSecondText.get();
    }

    set isWrapSecondText(o14) {
        this.__isWrapSecondText.set(o14);
    }

    get isWrapThirdText() {
        return this.__isWrapThirdText.get();
    }

    set isWrapThirdText(n14) {
        this.__isWrapThirdText.set(n14);
    }

    onWillApplyTheme(m14) {
        this.primaryTextColor = m14.colors.fontPrimary;
        this.secondaryTextColor = m14.colors.fontSecondary;
        this.descriptionColor = m14.colors.fontTertiary;
    }

    onPropChange() {
        if (this.icon == null && this.iconStyle == null) {
            this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
        } else {
            this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        }
        if (!IS_CLOSE_CHILD_FOCUS && this.isFocus) {
            this.primaryTextColors = {
                "id": -1,
                "type": 10001,
                params: ['sys.color.composeListItem_left_text_focus_color'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            };
            this.secondaryTextColors = {
                "id": -1,
                "type": 10001,
                params: ['sys.color.composeListItem_left_secondary_text_focus_color'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            };
            this.descriptionColors = {
                "id": -1,
                "type": 10001,
                params: ['sys.color.composeListItem_left_secondary_text_focus_color'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            };
        } else {
            this.primaryTextColors = this.primaryTextColor;
            this.secondaryTextColors = this.secondaryTextColor;
            this.descriptionColors = this.descriptionColor;
        }
    }

    onWrapChange() {
        this.isWrapText = this.isWrapFristText || this.isWrapSecondText || this.isWrapThirdText;
    }

    getIconFillColor() {
        switch (this.iconStyle) {
            case IconType.BADGE:
                return {
                    "id": -1,
                    "type": 10001,
                    params: ['sys.color.composeListItem_badge_color'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                };
            case IconType.SYSTEM_ICON:
                return {
                    "id": -1,
                    "type": 10001,
                    params: ['sys.color.composeListItem_icon_normal_color'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                };
            default:
                return {
                    "id": -1,
                    "type": 10001,
                    params: ['sys.color.ohos_id_color_secondary'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                };
        }
    }

    judgeIsWrap(i14, j14, k14) {
        let l14 = this.getSingleRowTextHeight(i14, j14);
        return k14 > l14;
    }

    getSingleRowTextHeight(f14, g14) {
        if (f14 && g14) {
            let h14 = px2vp(measure.measureTextSize({
                textContent: f14 || '',
                fontSize: g14,
                maxLines: TEXT_MAX_LINE
            }).height);
            return h14;
        }
        return 0;
    }

    aboutToAppear() {
        this.onPropChange();
    }

    createIcon(w13 = null) {
        this.observeComponentCreation2((x13, y13) => {
            If.create();
            if (this.icon != null && this.iconStyle != null && ICON_SIZE_MAP.has(this.iconStyle)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z13, a14) => {
                        If.create();
                        if (this.iconStyle <= IconType.PREVIEW) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((d14, e14) => {
                                    Image.create(this.icon);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.width(ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.height(ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.borderRadius({
                                        "id": -1,
                                        "type": 10002,
                                        params: ['sys.float.ohos_id_corner_radius_default_m'],
                                        "bundleName": "__harDefaultBundleName__",
                                        "moduleName": "__harDefaultModuleName__"
                                    });
                                    Image.focusable(false);
                                    Image.draggable(false);
                                    Image.fillColor(this.getIconFillColor());
                                    Image.flexShrink(0);
                                }, Image);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((b14, c14) => {
                                    Image.create(this.icon);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.constraintSize({
                                        minWidth: SPECIAL_ICON_SIZE,
                                        maxWidth: ICON_SIZE_MAP.get(this.iconStyle),
                                        minHeight: SPECIAL_ICON_SIZE,
                                        maxHeight: ICON_SIZE_MAP.get(this.iconStyle)
                                    });
                                    Image.borderRadius({
                                        "id": -1,
                                        "type": 10002,
                                        params: ['sys.float.ohos_id_corner_radius_default_m'],
                                        "bundleName": "__harDefaultBundleName__",
                                        "moduleName": "__harDefaultModuleName__"
                                    });
                                    Image.focusable(false);
                                    Image.draggable(false);
                                    Image.fillColor({
                                        "id": -1,
                                        "type": 10001,
                                        params: ['sys.color.ohos_id_color_secondary'],
                                        "bundleName": "__harDefaultBundleName__",
                                        "moduleName": "__harDefaultModuleName__"
                                    });
                                    Image.flexShrink(0);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    createText(d13 = null) {
        this.observeComponentCreation2((u13, v13) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.margin(this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 ? undefined : {
                top: TEXT_SAFE_MARGIN,
                bottom: TEXT_SAFE_MARGIN
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((q13, r13) => {
            Text.create(this.primaryText);
            Text.fontSize(ObservedObject.GetRawObject(this.primaryTextSize));
            Text.fontColor(ObservedObject.GetRawObject(this.primaryTextColors));
            Text.maxLines(IS_MARQUEE_OR_ELLIPSIS === MARQUEE_OR_ELLIPSIS ? -TEXT_MAX_LINE : TEXT_MAX_LINE);
            Text.textOverflow({
                overflow: IS_MARQUEE_OR_ELLIPSIS === MARQUEE_OR_ELLIPSIS ? TextOverflow.None :
                TextOverflow.Ellipsis
            });
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(true);
            Text.draggable(false);
            Text.accessibilityLevel(ACCESSIBILITY_LEVEL_NO);
            Text.onSizeChange((s13, t13) => {
                this.isWrapFristText = this.judgeIsWrap(ObservedObject.GetRawObject(this.primaryText),
                    ObservedObject.GetRawObject(this.primaryTextSize), t13.height);
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((k13, l13) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m13, n13) => {
                        Text.create(this.secondaryText);
                        Text.fontSize(ObservedObject.GetRawObject(this.secondaryThirdTextSize));
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColors));
                        Text.maxLines(IS_MARQUEE_OR_ELLIPSIS === MARQUEE_OR_ELLIPSIS ? -TEXT_MAX_LINE : TEXT_MAX_LINE);
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === MARQUEE_OR_ELLIPSIS ? TextOverflow.None :
                            TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.accessibilityLevel(ACCESSIBILITY_LEVEL_NO);
                        Text.onSizeChange((o13, p13) => {
                            this.isWrapSecondText = this.judgeIsWrap(ObservedObject.GetRawObject(this.secondaryText),
                                ObservedObject.GetRawObject(this.secondaryThirdTextSize), p13.height);
                        });
                    }, Text);
                    Text.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((e13, f13) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g13, h13) => {
                        Text.create(this.description);
                        Text.fontSize(ObservedObject.GetRawObject(this.secondaryThirdTextSize));
                        Text.fontColor(ObservedObject.GetRawObject(this.descriptionColors));
                        Text.maxLines(IS_MARQUEE_OR_ELLIPSIS === MARQUEE_OR_ELLIPSIS ? -TEXT_MAX_LINE : TEXT_MAX_LINE);
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === MARQUEE_OR_ELLIPSIS ? TextOverflow.None :
                            TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.accessibilityLevel(ACCESSIBILITY_LEVEL_NO);
                        Text.onSizeChange((i13, j13) => {
                            this.isWrapThirdText = this.judgeIsWrap(ObservedObject.GetRawObject(this.description),
                                ObservedObject.GetRawObject(this.secondaryThirdTextSize), j13.height);
                        });
                    }, Text);
                    Text.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    isColumnDirection() {
        return this.itemDirection === FlexDirection.Column;
    }

    isParentColumnDirection() {
        return this.parentDirection === FlexDirection.Column;
    }

    getItemSpace() {
        if (this.isColumnDirection()) {
            return LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.padding_level1'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
        }
        return LengthMetrics.vp(this.itemRowSpace);
    }

    initialRender() {
        this.observeComponentCreation2((b13, c13) => {
            Flex.create({
                space: { main: this.getItemSpace() },
                direction: this.itemDirection,
                justifyContent: FlexAlign.Start,
                alignItems: this.isColumnDirection() ? ItemAlign.Start : ItemAlign.Center,
            });
            Flex.margin({
                end: this.isParentColumnDirection() ?
                LengthMetrics.vp(0) :
                LengthMetrics.vp(16)
            });
            Flex.padding({ start: LengthMetrics.vp(LISTITEM_PADDING) });
            Flex.width(this.isParentColumnDirection() ? undefined : this.leftWidth);
            Flex.flexShrink(this.isParentColumnDirection() ? 0 : 1);
        }, Flex);
        this.createIcon.bind(this)();
        this.createText.bind(this)();
        Flex.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class CreateIconParam {
}

class OperateItemStruct extends ViewPU {
    constructor(v12, w12, x12, y12 = -1, z12 = undefined, a13) {
        super(v12, x12, y12, a13);
        if (typeof z12 === "function") {
            this.paramsGenerator_ = z12;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(w12.arrow, this, "arrow");
        this.__icon = new SynchedPropertyObjectOneWayPU(w12.icon, this, "icon");
        this.__subIcon = new SynchedPropertyObjectOneWayPU(w12.subIcon, this, "subIcon");
        this.__button = new SynchedPropertyObjectOneWayPU(w12.button, this, "button");
        this.__switch = new SynchedPropertyObjectOneWayPU(w12.switch, this, "switch");
        this.__checkBox = new SynchedPropertyObjectOneWayPU(w12.checkBox, this, "checkBox");
        this.__radio = new SynchedPropertyObjectOneWayPU(w12.radio, this, "radio");
        this.__image = new SynchedPropertyObjectOneWayPU(w12.image, this, "image");
        this.__text = new SynchedPropertyObjectOneWayPU(w12.text, this, "text");
        this.__switchState = new ObservedPropertySimplePU(false, this, "switchState");
        this.__radioState = new ObservedPropertySimplePU(false, this, "radioState");
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, "checkBoxState");
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(w12.rightWidth, this, "rightWidth");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "secondaryTextColor");
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, "hoveringColor");
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, "activedColor");
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(w12.parentCanFocus, this, "parentCanFocus");
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(w12.parentCanTouch, this, "parentCanTouch");
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(w12.parentIsHover, this, "parentIsHover");
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(w12.parentCanHover, this, "parentCanHover");
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(w12.parentIsActive, this, "parentIsActive");
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(w12.parentFrontColor, this, "parentFrontColor");
        this.__parentDirection = new SynchedPropertySimpleTwoWayPU(w12.parentDirection, this, "parentDirection");
        this.__rowSpace = new ObservedPropertySimplePU(DEFAULT_ROW_SPACE, this, "rowSpace");
        this.__isFocus = new SynchedPropertySimpleTwoWayPU(w12.isFocus, this, "isFocus");
        this.__secondaryTextSize = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_text_size_body2'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "secondaryTextSize");
        this.__secondaryTextColors = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.font_secondary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "secondaryTextColors");
        this.__iconColor = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.composeListItem_right_icon_normal_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "iconColor");
        this.__isChecked = new SynchedPropertySimpleTwoWayPU(w12.isChecked, this, "isChecked");
        this.setInitiallyProvidedValue(w12);
        this.declareWatch("arrow", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("subIcon", this.onPropChange);
        this.declareWatch("button", this.onPropChange);
        this.declareWatch("switch", this.onPropChange);
        this.declareWatch("checkBox", this.onPropChange);
        this.declareWatch("radio", this.onPropChange);
        this.declareWatch("image", this.onPropChange);
        this.declareWatch("text", this.onPropChange);
        this.declareWatch("secondaryTextColor", this.onFocusChange);
        this.declareWatch("isFocus", this.onFocusChange);
        this.declareWatch("isChecked", this.onPropChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(u12) {
        if (u12.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (u12.icon === undefined) {
            this.__icon.set(null);
        }
        if (u12.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (u12.button === undefined) {
            this.__button.set(null);
        }
        if (u12.switch === undefined) {
            this.__switch.set(null);
        }
        if (u12.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (u12.radio === undefined) {
            this.__radio.set(null);
        }
        if (u12.image === undefined) {
            this.__image.set(null);
        }
        if (u12.text === undefined) {
            this.__text.set(null);
        }
        if (u12.switchState !== undefined) {
            this.switchState = u12.switchState;
        }
        if (u12.radioState !== undefined) {
            this.radioState = u12.radioState;
        }
        if (u12.checkBoxState !== undefined) {
            this.checkBoxState = u12.checkBoxState;
        }
        if (u12.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (u12.secondaryTextColor !== undefined) {
            this.secondaryTextColor = u12.secondaryTextColor;
        }
        if (u12.hoveringColor !== undefined) {
            this.hoveringColor = u12.hoveringColor;
        }
        if (u12.activedColor !== undefined) {
            this.activedColor = u12.activedColor;
        }
        if (u12.rowSpace !== undefined) {
            this.rowSpace = u12.rowSpace;
        }
        if (u12.secondaryTextSize !== undefined) {
            this.secondaryTextSize = u12.secondaryTextSize;
        }
        if (u12.secondaryTextColors !== undefined) {
            this.secondaryTextColors = u12.secondaryTextColors;
        }
        if (u12.iconColor !== undefined) {
            this.iconColor = u12.iconColor;
        }
    }

    updateStateVars(t12) {
        this.__arrow.reset(t12.arrow);
        this.__icon.reset(t12.icon);
        this.__subIcon.reset(t12.subIcon);
        this.__button.reset(t12.button);
        this.__switch.reset(t12.switch);
        this.__checkBox.reset(t12.checkBox);
        this.__radio.reset(t12.radio);
        this.__image.reset(t12.image);
        this.__text.reset(t12.text);
        this.__rightWidth.reset(t12.rightWidth);
    }

    purgeVariableDependenciesOnElmtId(s12) {
        this.__arrow.purgeDependencyOnElmtId(s12);
        this.__icon.purgeDependencyOnElmtId(s12);
        this.__subIcon.purgeDependencyOnElmtId(s12);
        this.__button.purgeDependencyOnElmtId(s12);
        this.__switch.purgeDependencyOnElmtId(s12);
        this.__checkBox.purgeDependencyOnElmtId(s12);
        this.__radio.purgeDependencyOnElmtId(s12);
        this.__image.purgeDependencyOnElmtId(s12);
        this.__text.purgeDependencyOnElmtId(s12);
        this.__switchState.purgeDependencyOnElmtId(s12);
        this.__radioState.purgeDependencyOnElmtId(s12);
        this.__checkBoxState.purgeDependencyOnElmtId(s12);
        this.__rightWidth.purgeDependencyOnElmtId(s12);
        this.__secondaryTextColor.purgeDependencyOnElmtId(s12);
        this.__hoveringColor.purgeDependencyOnElmtId(s12);
        this.__activedColor.purgeDependencyOnElmtId(s12);
        this.__parentCanFocus.purgeDependencyOnElmtId(s12);
        this.__parentCanTouch.purgeDependencyOnElmtId(s12);
        this.__parentIsHover.purgeDependencyOnElmtId(s12);
        this.__parentCanHover.purgeDependencyOnElmtId(s12);
        this.__parentIsActive.purgeDependencyOnElmtId(s12);
        this.__parentFrontColor.purgeDependencyOnElmtId(s12);
        this.__parentDirection.purgeDependencyOnElmtId(s12);
        this.__rowSpace.purgeDependencyOnElmtId(s12);
        this.__isFocus.purgeDependencyOnElmtId(s12);
        this.__secondaryTextSize.purgeDependencyOnElmtId(s12);
        this.__secondaryTextColors.purgeDependencyOnElmtId(s12);
        this.__iconColor.purgeDependencyOnElmtId(s12);
        this.__isChecked.purgeDependencyOnElmtId(s12);
    }

    aboutToBeDeleted() {
        this.__arrow.aboutToBeDeleted();
        this.__icon.aboutToBeDeleted();
        this.__subIcon.aboutToBeDeleted();
        this.__button.aboutToBeDeleted();
        this.__switch.aboutToBeDeleted();
        this.__checkBox.aboutToBeDeleted();
        this.__radio.aboutToBeDeleted();
        this.__image.aboutToBeDeleted();
        this.__text.aboutToBeDeleted();
        this.__switchState.aboutToBeDeleted();
        this.__radioState.aboutToBeDeleted();
        this.__checkBoxState.aboutToBeDeleted();
        this.__rightWidth.aboutToBeDeleted();
        this.__secondaryTextColor.aboutToBeDeleted();
        this.__hoveringColor.aboutToBeDeleted();
        this.__activedColor.aboutToBeDeleted();
        this.__parentCanFocus.aboutToBeDeleted();
        this.__parentCanTouch.aboutToBeDeleted();
        this.__parentIsHover.aboutToBeDeleted();
        this.__parentCanHover.aboutToBeDeleted();
        this.__parentIsActive.aboutToBeDeleted();
        this.__parentFrontColor.aboutToBeDeleted();
        this.__parentDirection.aboutToBeDeleted();
        this.__rowSpace.aboutToBeDeleted();
        this.__isFocus.aboutToBeDeleted();
        this.__secondaryTextSize.aboutToBeDeleted();
        this.__secondaryTextColors.aboutToBeDeleted();
        this.__iconColor.aboutToBeDeleted();
        this.__isChecked.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get arrow() {
        return this.__arrow.get();
    }

    set arrow(r12) {
        this.__arrow.set(r12);
    }

    get icon() {
        return this.__icon.get();
    }

    set icon(q12) {
        this.__icon.set(q12);
    }

    get subIcon() {
        return this.__subIcon.get();
    }

    set subIcon(p12) {
        this.__subIcon.set(p12);
    }

    get button() {
        return this.__button.get();
    }

    set button(o12) {
        this.__button.set(o12);
    }

    get switch() {
        return this.__switch.get();
    }

    set switch(n12) {
        this.__switch.set(n12);
    }

    get checkBox() {
        return this.__checkBox.get();
    }

    set checkBox(m12) {
        this.__checkBox.set(m12);
    }

    get radio() {
        return this.__radio.get();
    }

    set radio(l12) {
        this.__radio.set(l12);
    }

    get image() {
        return this.__image.get();
    }

    set image(k12) {
        this.__image.set(k12);
    }

    get text() {
        return this.__text.get();
    }

    set text(j12) {
        this.__text.set(j12);
    }

    get switchState() {
        return this.__switchState.get();
    }

    set switchState(i12) {
        this.__switchState.set(i12);
    }

    get radioState() {
        return this.__radioState.get();
    }

    set radioState(h12) {
        this.__radioState.set(h12);
    }

    get checkBoxState() {
        return this.__checkBoxState.get();
    }

    set checkBoxState(g12) {
        this.__checkBoxState.set(g12);
    }

    get rightWidth() {
        return this.__rightWidth.get();
    }

    set rightWidth(f12) {
        this.__rightWidth.set(f12);
    }

    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }

    set secondaryTextColor(e12) {
        this.__secondaryTextColor.set(e12);
    }

    get hoveringColor() {
        return this.__hoveringColor.get();
    }

    set hoveringColor(d12) {
        this.__hoveringColor.set(d12);
    }

    get activedColor() {
        return this.__activedColor.get();
    }

    set activedColor(c12) {
        this.__activedColor.set(c12);
    }

    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }

    set parentCanFocus(b12) {
        this.__parentCanFocus.set(b12);
    }

    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }

    set parentCanTouch(a12) {
        this.__parentCanTouch.set(a12);
    }

    get parentIsHover() {
        return this.__parentIsHover.get();
    }

    set parentIsHover(z11) {
        this.__parentIsHover.set(z11);
    }

    get parentCanHover() {
        return this.__parentCanHover.get();
    }

    set parentCanHover(y11) {
        this.__parentCanHover.set(y11);
    }

    get parentIsActive() {
        return this.__parentIsActive.get();
    }

    set parentIsActive(x11) {
        this.__parentIsActive.set(x11);
    }

    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }

    set parentFrontColor(w11) {
        this.__parentFrontColor.set(w11);
    }

    get parentDirection() {
        return this.__parentDirection.get();
    }

    set parentDirection(v11) {
        this.__parentDirection.set(v11);
    }

    get rowSpace() {
        return this.__rowSpace.get();
    }

    set rowSpace(u11) {
        this.__rowSpace.set(u11);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(t11) {
        this.__isFocus.set(t11);
    }

    get secondaryTextSize() {
        return this.__secondaryTextSize.get();
    }

    set secondaryTextSize(s11) {
        this.__secondaryTextSize.set(s11);
    }

    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }

    set secondaryTextColors(r11) {
        this.__secondaryTextColors.set(r11);
    }

    get iconColor() {
        return this.__iconColor.get();
    }

    set iconColor(q11) {
        this.__iconColor.set(q11);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(p11) {
        this.__isChecked.set(p11);
    }

    onWillApplyTheme(o11) {
        this.secondaryTextColor = o11.colors.fontSecondary;
        this.hoveringColor = o11.colors.interactiveHover;
        this.activedColor = o11.colors.interactiveActive;
    }

    onFocusChange() {
        if (!IS_CLOSE_CHILD_FOCUS && this.isFocus) {
            this.secondaryTextColors = {
                "id": -1,
                "type": 10001,
                params: ['sys.color.composeListItem_right_text_focus_color'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            };
        } else {
            this.secondaryTextColors = this.secondaryTextColor;
        }
        this.iconColor = this.isFocus ? {
            "id": -1,
            "type": 10001,
            params: ['sys.color.composeListItem_right_icon_focus_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        } : {
            "id": -1,
            "type": 10001,
            params: ['sys.color.composeListItem_right_icon_normal_color'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        };
    }

    onPropChange() {
        if (this.switch != null) {
            this.switchState = IS_CLOSE_CHILD_FOCUS ? this.switch.isCheck : this.isChecked;
        }
        if (this.radio != null) {
            this.radioState = IS_CLOSE_CHILD_FOCUS ? this.radio.isCheck : this.isChecked;
        }
        if (this.checkBox != null) {
            this.checkBoxState = IS_CLOSE_CHILD_FOCUS ? this.checkBox.isCheck : this.isChecked;
        }
        if ((this.button == null && this.image == null && this.icon != null && this.text != null) ||
            (this.button == null && this.image == null && this.icon == null && this.arrow != null &&
                this.text != null)) {
            this.rowSpace = SPECICAL_ROW_SPACE;
        } else {
            this.rowSpace = DEFAULT_ROW_SPACE;
        }
    }

    getUnselectedColor() {
        if (IS_CLOSE_CHILD_FOCUS) {
            return DEFUALT_RADIO_CHECKBOX_BORDER_COLOR;
        }
        return this.isFocus ? OPERATE_ITECOLOR : DEFUALT_RADIO_CHECKBOX_BORDER_COLOR;
    }

    aboutToAppear() {
        if (this.switch !== null) {
            this.isChecked = this.switch.isCheck;
        }
        if (this.radio !== null) {
            this.isChecked = this.radio.isCheck;
        }
        if (this.checkBox !== null) {
            this.isChecked = this.checkBox.isCheck;
        }
        this.onPropChange();
        this.onFocusChange();
    }

    createButton(g11 = null) {
        this.observeComponentCreation2((l11, m11) => {
            Button.createWithChild();
            Button.padding({ top: 0, bottom: 0 });
            Button.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Button.hitTestBehavior(IS_CLOSE_CHILD_FOCUS ? HitTestMode.Block : HitTestMode.None);
            Button.fontSize({
                "id": -1,
                "type": 10002,
                params: ['sys.float.ohos_id_text_size_button3'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
            Button.fontColor({
                "id": -1,
                "type": 10001,
                params: ['sys.color.ohos_id_color_text_primary_activated_transparent'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
            Button.constraintSize({
                minHeight: BUTTON_SIZE
            });
            Button.backgroundColor({
                "id": -1,
                "type": 10001,
                params: ['sys.color.ohos_id_color_button_normal'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
            Button.labelStyle({
                maxLines: TEXT_MAX_LINE
            });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onHover((n11) => {
                this.parentCanHover = false;
                if (n11 && this.parentFrontColor === this.hoveringColor && IS_CLOSE_CHILD_FOCUS) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!n11) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((j11, k11) => {
            Row.create();
            Row.padding({
                left: TEXT_SAFE_MARGIN,
                right: TEXT_SAFE_MARGIN
            });
        }, Row);
        this.observeComponentCreation2((h11, i11) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }

    createIcon(z10, a11 = null) {
        this.observeComponentCreation2((d11, e11) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.hitTestBehavior(IS_CLOSE_CHILD_FOCUS ? HitTestMode.Block : HitTestMode.None);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.borderRadius({
                "id": -1,
                "type": 10002,
                params: ['sys.float.ohos_id_corner_radius_clicked'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onHover((f11) => {
                this.parentCanHover = false;
                if (f11 && this.parentFrontColor === this.hoveringColor && IS_CLOSE_CHILD_FOCUS) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!f11) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(z10.icon?.action);
            Button.flexShrink(0);
        }, Button);
        this.observeComponentCreation2((b11, c11) => {
            Image.create(z10.icon?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ICONLIKE_SIZE);
            Image.focusable(true);
            Image.fillColor(ObservedObject.GetRawObject(this.iconColor));
            Image.draggable(false);
        }, Image);
        Button.pop();
    }

    createImage(w10 = null) {
        this.observeComponentCreation2((x10, y10) => {
            Image.create(this.image);
            Image.height(OPERATEITEM_IMAGE_SIZE);
            Image.width(OPERATEITEM_IMAGE_SIZE);
            Image.draggable(false);
            Image.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
        }, Image);
    }

    createText(t10 = null) {
        this.observeComponentCreation2((u10, v10) => {
            Text.create(this.text);
            Text.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Text.fontSize(ObservedObject.GetRawObject(this.secondaryTextSize));
            Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColors));
            Text.textOverflow({
                overflow: IS_MARQUEE_OR_ELLIPSIS === MARQUEE_OR_ELLIPSIS ? TextOverflow.MARQUEE :
                TextOverflow.None
            });
            Text.marqueeOptions({
                start: this.isFocus,
                fadeout: true,
                marqueeStartPolicy: MarqueeStartPolicy.DEFAULT
            });
            Text.maxLines(LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.composeListItem_maxLines_right'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }).value);
            Text.draggable(false);
            Text.flexShrink(1);
            Text.accessibilityLevel(ACCESSIBILITY_LEVEL_NO);
        }, Text);
        Text.pop();
    }

    createArrow(n10 = null) {
        this.observeComponentCreation2((q10, r10) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Button.hitTestBehavior(IS_CLOSE_CHILD_FOCUS ? HitTestMode.Transparent : HitTestMode.None);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.stateEffect(this.arrow?.action !== undefined);
            Button.hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None);
            Button.onHover((s10) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                this.parentCanHover = false;
                if (s10 && IS_CLOSE_CHILD_FOCUS) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!s10) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
        }, Button);
        this.observeComponentCreation2((o10, p10) => {
            Image.create(this.arrow?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.focusable(true);
            Image.fillColor(IS_CLOSE_CHILD_FOCUS ? {
                "id": -1,
                "type": 10001,
                params: ['sys.color.ohos_id_color_fourth'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            } : this.iconColor);
            Image.draggable(false);
            Image.matchTextDirection(true);
        }, Image);
        Button.pop();
    }

    createRadio(i10 = null) {
        this.observeComponentCreation2((j10, k10) => {
            Radio.create({ value: '', group: '' });
            Radio.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Radio.checked(this.radioState);
            Radio.radioStyle({
                uncheckedBorderColor: this.getUnselectedColor()
            });
            Radio.backgroundColor(!IS_CLOSE_CHILD_FOCUS && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Radio.borderRadius(OPERATE_ITEM_RADIUS);
            Radio.onChange((m10) => {
                this.radioState = m10;
                if (!IS_CLOSE_CHILD_FOCUS) {
                    this.isChecked = m10;
                }
                if (this.radio?.onChange) {
                    this.radio?.onChange(m10);
                }
            });
            Radio.height(OPERATEITEM_ICONLIKE_SIZE);
            Radio.width(OPERATEITEM_ICONLIKE_SIZE);
            Radio.padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE);
            Radio.onFocus(() => {
                this.parentCanFocus = false;
            });
            Radio.hitTestBehavior(IS_CLOSE_CHILD_FOCUS ? HitTestMode.Block : HitTestMode.None);
            Radio.onHover((l10) => {
                this.parentCanHover = false;
                if (l10 && this.parentFrontColor === this.hoveringColor && IS_CLOSE_CHILD_FOCUS) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!l10) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Radio);
    }

    createCheckBox(d10 = null) {
        this.observeComponentCreation2((e10, f10) => {
            Checkbox.create();
            Checkbox.borderRadius(IS_CLOSE_CHILD_FOCUS ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Checkbox.unselectedColor(this.getUnselectedColor());
            Checkbox.backgroundColor(!IS_CLOSE_CHILD_FOCUS && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Checkbox.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange((h10) => {
                this.checkBoxState = h10;
                if (!IS_CLOSE_CHILD_FOCUS) {
                    this.isChecked = h10;
                }
                if (this.checkBox?.onChange) {
                    this.checkBox?.onChange(h10);
                }
            });
            Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.width(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE);
            Checkbox.onFocus(() => {
                this.parentCanFocus = false;
            });
            Checkbox.hitTestBehavior(IS_CLOSE_CHILD_FOCUS ? HitTestMode.Block : HitTestMode.None);
            Checkbox.onHover((g10) => {
                this.parentCanHover = false;
                if (g10 && this.parentFrontColor === this.hoveringColor && IS_CLOSE_CHILD_FOCUS) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!g10) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Checkbox);
        Checkbox.pop();
    }

    createSwitch(w9 = null) {
        this.observeComponentCreation2((a10, b10) => {
            Row.create();
            Row.margin({ end: LengthMetrics.vp(SWITCH_PADDING) });
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onHover((c10) => {
                this.parentCanHover = false;
                if (c10 && this.parentFrontColor === this.hoveringColor && IS_CLOSE_CHILD_FOCUS) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!c10) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((x9, y9) => {
            Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
            Toggle.borderRadius(IS_CLOSE_CHILD_FOCUS ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Toggle.backgroundColor(!IS_CLOSE_CHILD_FOCUS && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Toggle.switchPointColor(!IS_CLOSE_CHILD_FOCUS && this.isFocus && !this.switchState ? OPERATE_ITECOLOR :
                UNUSUAL);
            Toggle.onChange((z9) => {
                this.switchState = z9;
                if (!IS_CLOSE_CHILD_FOCUS) {
                    this.isChecked = z9;
                }
                if (this.switch?.onChange) {
                    this.switch?.onChange(z9);
                }
            });
            Toggle.hitTestBehavior(IS_CLOSE_CHILD_FOCUS ? HitTestMode.Block : HitTestMode.None);
        }, Toggle);
        Toggle.pop();
        Row.pop();
    }

    createTextArrow(e9 = null) {
        this.observeComponentCreation2((t9, u9) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.hitTestBehavior(IS_CLOSE_CHILD_FOCUS ? HitTestMode.Transparent : HitTestMode.None);
            Button.labelStyle({
                maxLines: TEXT_MAX_LINE
            });
            Button.backgroundColor(Color.Transparent);
            Button.constraintSize({ minHeight: TEXT_ARROW_HEIGHT });
            Button.borderRadius({
                "id": -1,
                "type": 10002,
                params: ['sys.float.ohos_id_corner_radius_clicked'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.padding({
                top: 0,
                bottom: 0,
                left: 0,
                right: 0
            });
            Button.stateEffect(this.arrow?.action !== undefined);
            Button.hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None);
            Button.onHover((v9) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                this.parentCanHover = false;
                if (v9 && IS_CLOSE_CHILD_FOCUS) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!v9) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
        }, Button);
        this.observeComponentCreation2((f9, g9) => {
            If.create();
            if (this.parentDirection === FlexDirection.Column) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r9, s9) => {
                        Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
                        Flex.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Flex);
                    this.observeComponentCreation2((p9, q9) => {
                        Text.create(this.text);
                        Text.fontSize({
                            "id": -1,
                            "type": 10002,
                            params: ['sys.float.ohos_id_text_size_body2'],
                            "bundleName": "__harDefaultBundleName__",
                            "moduleName": "__harDefaultModuleName__"
                        });
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.constraintSize({
                            maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
                        });
                        Text.accessibilityLevel(ACCESSIBILITY_LEVEL_NO);
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((n9, o9) => {
                        Image.create(this.arrow?.value);
                        Image.height(OPERATEITEM_ICONLIKE_SIZE);
                        Image.width(OPERATEITEM_ARROW_WIDTH);
                        Image.fillColor({
                            "id": -1,
                            "type": 10001,
                            params: ['sys.color.ohos_id_color_fourth'],
                            "bundleName": "__harDefaultBundleName__",
                            "moduleName": "__harDefaultModuleName__"
                        });
                        Image.focusable(false);
                        Image.draggable(false);
                        Image.matchTextDirection(true);
                    }, Image);
                    Flex.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((l9, m9) => {
                        Row.create({ space: SPECICAL_ROW_SPACE });
                        Row.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Row);
                    this.observeComponentCreation2((j9, k9) => {
                        Text.create(this.text);
                        Text.fontSize(ObservedObject.GetRawObject(this.secondaryTextSize));
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColors));
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === MARQUEE_OR_ELLIPSIS ? TextOverflow.MARQUEE :
                            TextOverflow.None
                        });
                        Text.marqueeOptions({
                            start: this.isFocus,
                            fadeout: true,
                            marqueeStartPolicy: MarqueeStartPolicy.DEFAULT
                        });
                        Text.maxLines(LengthMetrics.resource({
                            "id": -1,
                            "type": 10002,
                            params: ['sys.float.composeListItem_maxLines_right'],
                            "bundleName": "__harDefaultBundleName__",
                            "moduleName": "__harDefaultModuleName__"
                        }).value);
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.constraintSize({
                            maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
                        });
                        Text.accessibilityLevel(ACCESSIBILITY_LEVEL_NO);
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((h9, i9) => {
                        Image.create(this.arrow?.value);
                        Image.height(OPERATEITEM_ICONLIKE_SIZE);
                        Image.width(OPERATEITEM_ARROW_WIDTH);
                        Image.fillColor(IS_CLOSE_CHILD_FOCUS ? {
                            "id": -1,
                            "type": 10001,
                            params: ['sys.color.icon_fourth'],
                            "bundleName": "__harDefaultBundleName__",
                            "moduleName": "__harDefaultModuleName__"
                        } : this.iconColor);
                        Image.focusable(false);
                        Image.draggable(false);
                        Image.matchTextDirection(true);
                    }, Image);
                    Row.pop();
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }

    getFlexOptions() {
        let d9 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            d9.justifyContent = FlexAlign.SpaceBetween;
        } else {
            d9.space = { main: LengthMetrics.vp(this.rowSpace) };
            d9.justifyContent = FlexAlign.End;
        }
        return d9;
    }

    initialRender() {
        this.observeComponentCreation2((b9, c9) => {
            Flex.create(this.getFlexOptions());
            Flex.width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth);
        }, Flex);
        this.observeComponentCreation2((x8, y8) => {
            If.create();
            if (this.button != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.createButton.bind(this)();
                });
            } else if (this.image != null) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.createImage.bind(this)();
                });
            } else if (this.icon != null && this.text != null) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.createText.bind(this)();
                    this.createIcon.bind(this)(makeBuilderParameterProxy("createIcon",
                        { icon: () => (this["__icon"] ? this["__icon"] : this["icon"]) }));
                });
            } else if (this.arrow != null && this.text == null) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.createArrow.bind(this)();
                });
            } else if (this.arrow != null && this.text != null) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.createTextArrow.bind(this)();
                });
            } else if (this.text != null) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.createText.bind(this)();
                });
            } else if (this.radio != null) {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.createRadio.bind(this)();
                });
            } else if (this.checkBox != null) {
                this.ifElseBranchUpdateFunction(7, () => {
                    this.createCheckBox.bind(this)();
                });
            } else if (this.switch != null) {
                this.ifElseBranchUpdateFunction(8, () => {
                    this.createSwitch.bind(this)();
                });
            } else if (this.icon != null) {
                this.ifElseBranchUpdateFunction(9, () => {
                    this.createIcon.bind(this)(makeBuilderParameterProxy("createIcon",
                        { icon: () => (this["__icon"] ? this["__icon"] : this["icon"]) }));
                    this.observeComponentCreation2((z8, a9) => {
                        If.create();
                        if (this.subIcon != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.createIcon.bind(this)(makeBuilderParameterProxy("createIcon",
                                    { icon: () => (this["__subIcon"] ? this["__subIcon"] : this["subIcon"]) }));
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(10, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class ComposeListItem extends ViewPU {
    constructor(r8, s8, t8, u8 = -1, v8 = undefined, w8) {
        super(r8, t8, u8, w8);
        if (typeof v8 === "function") {
            this.paramsGenerator_ = v8;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(s8.contentItem, this, "contentItem");
        this.__operateItem = new SynchedPropertyObjectOneWayPU(s8.operateItem, this, "operateItem");
        this.__frontColor = new ObservedPropertyObjectPU(NORMAL_BG, this, "frontColor");
        this.__borderSize = new ObservedPropertySimplePU(0, this, "borderSize");
        this.__canFocus = new ObservedPropertySimplePU(false, this, "canFocus");
        this.__canTouch = new ObservedPropertySimplePU(true, this, "canTouch");
        this.__canHover = new ObservedPropertySimplePU(true, this, "canHover");
        this.__isHover = new ObservedPropertySimplePU(true, this, "isHover");
        this.__itemHeight = new ObservedPropertySimplePU(ItemHeight.FIRST_HEIGHT, this, "itemHeight");
        this.__isActive = new ObservedPropertySimplePU(false, this, "isActive");
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, "hoveringColor");
        this.__touchDownColor = new ObservedPropertyObjectPU('#1a000000', this, "touchDownColor");
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, "activedColor");
        this.__focusOutlineColor = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_focused_outline'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "focusOutlineColor");
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, "fontSizeScale");
        this.__containerDirection = new ObservedPropertySimplePU(FlexDirection.Row, this, "containerDirection");
        this.__contentItemDirection = new ObservedPropertySimplePU(FlexDirection.Row, this, "contentItemDirection");
        this.__containerPadding = new ObservedPropertyObjectPU(undefined, this, "containerPadding");
        this.__textArrowLeftSafeOffset = new ObservedPropertySimplePU(0, this, "textArrowLeftSafeOffset");
        this.isFollowingSystemFontScale = this.getUIContext().isFollowingSystemFontScale();
        this.maxFontScale = this.getUIContext().getMaxFontScale();
        this.__accessibilityTextBuilder = new ObservedPropertySimplePU('', this, "accessibilityTextBuilder");
        this.__isFocus = new ObservedPropertySimplePU(false, this, "isFocus");
        this.__isChecked = new ObservedPropertySimplePU(false, this, "isChecked");
        this.__isWrapText = new ObservedPropertySimplePU(false, this, "isWrapText");
        this.setInitiallyProvidedValue(s8);
        this.declareWatch("contentItem", this.onPropChange);
        this.declareWatch("operateItem", this.onPropChange);
        this.declareWatch("fontSizeScale", this.onFontSizeScaleChange);
        this.declareWatch("isWrapText", this.onWrapChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(q8) {
        if (q8.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (q8.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (q8.frontColor !== undefined) {
            this.frontColor = q8.frontColor;
        }
        if (q8.borderSize !== undefined) {
            this.borderSize = q8.borderSize;
        }
        if (q8.canFocus !== undefined) {
            this.canFocus = q8.canFocus;
        }
        if (q8.canTouch !== undefined) {
            this.canTouch = q8.canTouch;
        }
        if (q8.canHover !== undefined) {
            this.canHover = q8.canHover;
        }
        if (q8.isHover !== undefined) {
            this.isHover = q8.isHover;
        }
        if (q8.itemHeight !== undefined) {
            this.itemHeight = q8.itemHeight;
        }
        if (q8.isActive !== undefined) {
            this.isActive = q8.isActive;
        }
        if (q8.hoveringColor !== undefined) {
            this.hoveringColor = q8.hoveringColor;
        }
        if (q8.touchDownColor !== undefined) {
            this.touchDownColor = q8.touchDownColor;
        }
        if (q8.activedColor !== undefined) {
            this.activedColor = q8.activedColor;
        }
        if (q8.focusOutlineColor !== undefined) {
            this.focusOutlineColor = q8.focusOutlineColor;
        }
        if (q8.fontSizeScale !== undefined) {
            this.fontSizeScale = q8.fontSizeScale;
        }
        if (q8.containerDirection !== undefined) {
            this.containerDirection = q8.containerDirection;
        }
        if (q8.contentItemDirection !== undefined) {
            this.contentItemDirection = q8.contentItemDirection;
        }
        if (q8.containerPadding !== undefined) {
            this.containerPadding = q8.containerPadding;
        }
        if (q8.textArrowLeftSafeOffset !== undefined) {
            this.textArrowLeftSafeOffset = q8.textArrowLeftSafeOffset;
        }
        if (q8.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = q8.isFollowingSystemFontScale;
        }
        if (q8.maxFontScale !== undefined) {
            this.maxFontScale = q8.maxFontScale;
        }
        if (q8.accessibilityTextBuilder !== undefined) {
            this.accessibilityTextBuilder = q8.accessibilityTextBuilder;
        }
        if (q8.isFocus !== undefined) {
            this.isFocus = q8.isFocus;
        }
        if (q8.isChecked !== undefined) {
            this.isChecked = q8.isChecked;
        }
        if (q8.isWrapText !== undefined) {
            this.isWrapText = q8.isWrapText;
        }
    }

    updateStateVars(p8) {
        this.__contentItem.reset(p8.contentItem);
        this.__operateItem.reset(p8.operateItem);
    }

    purgeVariableDependenciesOnElmtId(o8) {
        this.__contentItem.purgeDependencyOnElmtId(o8);
        this.__operateItem.purgeDependencyOnElmtId(o8);
        this.__frontColor.purgeDependencyOnElmtId(o8);
        this.__borderSize.purgeDependencyOnElmtId(o8);
        this.__canFocus.purgeDependencyOnElmtId(o8);
        this.__canTouch.purgeDependencyOnElmtId(o8);
        this.__canHover.purgeDependencyOnElmtId(o8);
        this.__isHover.purgeDependencyOnElmtId(o8);
        this.__itemHeight.purgeDependencyOnElmtId(o8);
        this.__isActive.purgeDependencyOnElmtId(o8);
        this.__hoveringColor.purgeDependencyOnElmtId(o8);
        this.__touchDownColor.purgeDependencyOnElmtId(o8);
        this.__activedColor.purgeDependencyOnElmtId(o8);
        this.__focusOutlineColor.purgeDependencyOnElmtId(o8);
        this.__fontSizeScale.purgeDependencyOnElmtId(o8);
        this.__containerDirection.purgeDependencyOnElmtId(o8);
        this.__contentItemDirection.purgeDependencyOnElmtId(o8);
        this.__containerPadding.purgeDependencyOnElmtId(o8);
        this.__textArrowLeftSafeOffset.purgeDependencyOnElmtId(o8);
        this.__accessibilityTextBuilder.purgeDependencyOnElmtId(o8);
        this.__isFocus.purgeDependencyOnElmtId(o8);
        this.__isChecked.purgeDependencyOnElmtId(o8);
        this.__isWrapText.purgeDependencyOnElmtId(o8);
    }

    aboutToBeDeleted() {
        this.__contentItem.aboutToBeDeleted();
        this.__operateItem.aboutToBeDeleted();
        this.__frontColor.aboutToBeDeleted();
        this.__borderSize.aboutToBeDeleted();
        this.__canFocus.aboutToBeDeleted();
        this.__canTouch.aboutToBeDeleted();
        this.__canHover.aboutToBeDeleted();
        this.__isHover.aboutToBeDeleted();
        this.__itemHeight.aboutToBeDeleted();
        this.__isActive.aboutToBeDeleted();
        this.__hoveringColor.aboutToBeDeleted();
        this.__touchDownColor.aboutToBeDeleted();
        this.__activedColor.aboutToBeDeleted();
        this.__focusOutlineColor.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__containerDirection.aboutToBeDeleted();
        this.__contentItemDirection.aboutToBeDeleted();
        this.__containerPadding.aboutToBeDeleted();
        this.__textArrowLeftSafeOffset.aboutToBeDeleted();
        this.__accessibilityTextBuilder.aboutToBeDeleted();
        this.__isFocus.aboutToBeDeleted();
        this.__isChecked.aboutToBeDeleted();
        this.__isWrapText.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get contentItem() {
        return this.__contentItem.get();
    }

    set contentItem(n8) {
        this.__contentItem.set(n8);
    }

    get operateItem() {
        return this.__operateItem.get();
    }

    set operateItem(m8) {
        this.__operateItem.set(m8);
    }

    get frontColor() {
        return this.__frontColor.get();
    }

    set frontColor(l8) {
        this.__frontColor.set(l8);
    }

    get borderSize() {
        return this.__borderSize.get();
    }

    set borderSize(k8) {
        this.__borderSize.set(k8);
    }

    get canFocus() {
        return this.__canFocus.get();
    }

    set canFocus(j8) {
        this.__canFocus.set(j8);
    }

    get canTouch() {
        return this.__canTouch.get();
    }

    set canTouch(i8) {
        this.__canTouch.set(i8);
    }

    get canHover() {
        return this.__canHover.get();
    }

    set canHover(h8) {
        this.__canHover.set(h8);
    }

    get isHover() {
        return this.__isHover.get();
    }

    set isHover(g8) {
        this.__isHover.set(g8);
    }

    get itemHeight() {
        return this.__itemHeight.get();
    }

    set itemHeight(f8) {
        this.__itemHeight.set(f8);
    }

    get isActive() {
        return this.__isActive.get();
    }

    set isActive(e8) {
        this.__isActive.set(e8);
    }

    get hoveringColor() {
        return this.__hoveringColor.get();
    }

    set hoveringColor(d8) {
        this.__hoveringColor.set(d8);
    }

    get touchDownColor() {
        return this.__touchDownColor.get();
    }

    set touchDownColor(c8) {
        this.__touchDownColor.set(c8);
    }

    get activedColor() {
        return this.__activedColor.get();
    }

    set activedColor(b8) {
        this.__activedColor.set(b8);
    }

    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }

    set focusOutlineColor(a8) {
        this.__focusOutlineColor.set(a8);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(z7) {
        this.__fontSizeScale.set(z7);
    }

    get containerDirection() {
        return this.__containerDirection.get();
    }

    set containerDirection(y7) {
        this.__containerDirection.set(y7);
    }

    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }

    set contentItemDirection(x7) {
        this.__contentItemDirection.set(x7);
    }

    get containerPadding() {
        return this.__containerPadding.get();
    }

    set containerPadding(w7) {
        this.__containerPadding.set(w7);
    }

    get textArrowLeftSafeOffset() {
        return this.__textArrowLeftSafeOffset.get();
    }

    set textArrowLeftSafeOffset(v7) {
        this.__textArrowLeftSafeOffset.set(v7);
    }

    get accessibilityTextBuilder() {
        return this.__accessibilityTextBuilder.get();
    }

    set accessibilityTextBuilder(u7) {
        this.__accessibilityTextBuilder.set(u7);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(t7) {
        this.__isFocus.set(t7);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(s7) {
        this.__isChecked.set(s7);
    }

    get isWrapText() {
        return this.__isWrapText.get();
    }

    set isWrapText(r7) {
        this.__isWrapText.set(r7);
    }

    onWillApplyTheme(q7) {
        this.hoveringColor = q7.colors.interactiveHover;
        this.touchDownColor = q7.colors.interactivePressed;
        this.activedColor = q7.colors.interactiveActive;
        this.focusOutlineColor = q7.colors.interactiveFocus;
    }

    onWrapChange() {
        this.containerPadding = this.getPadding();
    }

    onPropChange() {
        if (this.contentItem === undefined) {
            if (this.operateItem?.image !== undefined ||
                this.operateItem?.icon !== undefined ||
                this.operateItem?.subIcon !== undefined) {
                this.itemHeight = OPERATEITEM_IMAGE_SIZE + SAFE_LIST_PADDING;
            }
            return;
        }
        if (this.contentItem?.secondaryText === undefined && this.contentItem?.description === undefined) {
            if (this.contentItem?.icon === undefined) {
                this.itemHeight = ItemHeight.FIRST_HEIGHT;
            } else {
                this.itemHeight = this.contentItem.iconStyle <= IconType.HEAD_SCULPTURE ?
                ItemHeight.SECOND_HEIGHT : (LengthMetrics.resource({
                        "id": -1,
                        "type": 10002,
                        params: ['sys.float.composeListItem_system_icon_line_height'],
                        "bundleName": "__harDefaultBundleName__",
                        "moduleName": "__harDefaultModuleName__"
                    }).value);
            }
        } else if (this.contentItem.description === undefined) {
            if (this.contentItem.icon === undefined ||
                (this.contentItem.icon !== undefined && this.contentItem.iconStyle <= IconType.SYSTEM_ICON)) {
                this.itemHeight = ItemHeight.THIRD_HEIGHT;
            } else {
                this.itemHeight = ItemHeight.FOURTH_HEIGHT;
            }
        } else {
            this.itemHeight = ItemHeight.FIFTH_HEIGHT;
        }
        if (ICON_SIZE_MAP.get(this.contentItem?.iconStyle) >= this.itemHeight) {
            this.itemHeight = ICON_SIZE_MAP.get(this.contentItem?.iconStyle) + SAFE_LIST_PADDING;
        }
        this.accessibilityTextBuilder = `
      ${this.contentItem?.primaryText ?? ''}
      ${this.contentItem?.secondaryText ?? ''}
      ${this.contentItem?.description ?? ''}
      ${this.operateItem?.text ?? ''}
    `;
    }

    aboutToAppear() {
        this.onPropChange();
        if (IS_CLOSE_CHILD_FOCUS) {
            return;
        }
        this.onFontSizeScaleChange();
    }

    calculatedLeftWidth() {
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return RIGHT_CONTENT_NULL_LEFTWIDTH;
        } else if (this.operateItem?.arrow != null && this.operateItem?.text == null) {
            return LEFT_ONLY_ARROW_WIDTH;
        } else {
            return LEFT_PART_WIDTH;
        }
    }

    calculatedRightWidth() {
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return RIGHT_CONTENT_NULL_RIGHTWIDTH;
        } else if (this.operateItem?.arrow != null && this.operateItem?.text == null) {
            return RIGHT_ONLY_ARROW_WIDTH;
        } else {
            return RIGHT_PART_WIDTH;
        }
    }

    decideContentItemDirection() {
        if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 &&
            this.contentItem?.iconStyle && this.contentItem?.iconStyle > IconType.HEAD_SCULPTURE) {
            return FlexDirection.Column;
        }
        return FlexDirection.Row;
    }

    decideContainerDirection() {
        if (this.fontSizeScale < FontSizeScaleLevel.LEVEL1 || !this.contentItem) {
            return FlexDirection.Row;
        }
        if (this.operateItem?.button) {
            return FlexDirection.Column;
        } else if (this.operateItem?.image) {
            return FlexDirection.Row;
        } else if (this.operateItem?.icon && this.operateItem?.text) {
            return FlexDirection.Column;
        } else if (this.operateItem?.arrow) {
            if (!this.operateItem?.text) {
                return FlexDirection.Row;
            }
            this.textArrowLeftSafeOffset = TEXT_SAFE_MARGIN;
            return FlexDirection.Column;
        } else if (this.operateItem?.text) {
            return FlexDirection.Column;
        } else {
            return FlexDirection.Row;
        }
    }

    onFontSizeScaleChange() {
        this.containerDirection = this.decideContainerDirection();
        this.contentItemDirection = this.decideContentItemDirection();
        if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL3) {
            this.containerPadding = {
                top: {
                    "id": -1,
                    "type": 10002,
                    params: ['sys.float.padding_level12'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                },
                bottom: {
                    "id": -1,
                    "type": 10002,
                    params: ['sys.float.padding_level12'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                },
            };
        } else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL2) {
            this.containerPadding = {
                top: {
                    "id": -1,
                    "type": 10002,
                    params: ['sys.float.padding_level10'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                },
                bottom: {
                    "id": -1,
                    "type": 10002,
                    params: ['sys.float.padding_level10'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                },
            };
        } else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1) {
            this.containerPadding = {
                top: {
                    "id": -1,
                    "type": 10002,
                    params: ['sys.float.padding_level8'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                },
                bottom: {
                    "id": -1,
                    "type": 10002,
                    params: ['sys.float.padding_level8'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                },
            };
        } else {
            this.containerPadding = this.getPadding();
        }
    }

    isSingleLine() {
        return !this.contentItem?.secondaryText && !this.contentItem?.description;
    }

    getOperateOffset() {
        if (this.containerDirection === FlexDirection.Row) {
            return LengthMetrics.vp(0);
        }
        let p7 = ICON_SIZE_MAP.get(this.contentItem?.iconStyle);
        if (this.contentItem?.icon && p7 && p7 <= HEADSCULPTURE_SIZE) {
            return LengthMetrics.vp(p7 + NORMAL_ITEM_ROW_SPACE + LISTITEM_PADDING - this.textArrowLeftSafeOffset);
        }
        return LengthMetrics.vp(LISTITEM_PADDING - this.textArrowLeftSafeOffset);
    }

    getMainSpace() {
        if (this.containerDirection === FlexDirection.Column) {
            return LengthMetrics.resource(this.isSingleLine() ? {
                "id": -1,
                "type": 10002,
                params: ['sys.float.padding_level1'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            } : {
                "id": -1,
                "type": 10002,
                params: ['sys.float.padding_level8'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
        }
        return LengthMetrics.vp(0);
    }

    getFlexOptions() {
        if (this.containerDirection === FlexDirection.Column) {
            return {
                space: { main: this.getMainSpace() },
                justifyContent: FlexAlign.Center,
                alignItems: ItemAlign.Start,
                direction: this.containerDirection,
            };
        }
        return {
            justifyContent: FlexAlign.SpaceBetween,
            alignItems: ItemAlign.Center,
            direction: this.containerDirection,
        };
    }

    decideFontSizeScale() {
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.maxFontScale, this.getUIContext().getHostContext()?.config.fontSizeScale ?? 1);
    }

    getPadding() {
        let m7 = LengthMetrics.resource(PADDING).value;
        let n7 = m7 > LISTITEM_PADDING;
        let o7 = n7 ? m7 - LISTITEM_PADDING : 0;
        if (!IS_CLOSE_CHILD_FOCUS && this.isWrapText) {
            return {
                top: m7,
                bottom: m7,
                left: o7,
                right: o7
            };
        } else {
            return { left: o7, right: o7 };
        }
    }

    onMeasureSize(g7, h7, i7) {
        this.fontSizeScale = this.decideFontSizeScale();
        let j7 = { height: 0, width: 0 };
        h7.forEach((k7) => {
            let l7 = k7.measure(i7);
            j7.width = l7.width;
            j7.height = l7.height;
        });
        return j7;
    }

    initialRender() {
        this.observeComponentCreation2((e7, f7) => {
            Stack.create();
            Stack.accessibilityText(this.accessibilityTextBuilder);
            Stack.onFocus(() => {
                this.isFocus = true;
                this.frontColor = FOCUSED_BG;
            });
            Stack.onBlur(() => {
                this.isFocus = false;
                this.frontColor = NORMAL_BG;
            });
            Stack.borderRadius({
                "id": -1,
                "type": 10002,
                params: ['sys.float.composeListItem_radius'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
            Stack.onClick(() => {
                if (!IS_CLOSE_CHILD_FOCUS) {
                    this.isChecked = this.operateItem?.radio ? true : !this.isChecked;
                    if (this.operateItem?.icon && this.operateItem.icon?.action) {
                        this.operateItem.icon.action();
                    }
                    if (this.operateItem?.subIcon && this.operateItem.subIcon?.action) {
                        this.operateItem.subIcon.action();
                    }
                    if (this.operateItem?.arrow && this.operateItem.arrow?.action) {
                        this.operateItem.arrow.action();
                    }
                }
            });
            Stack.scale({
                x: this.isFocus ? FOCUSED_SCALE : RECOVER_YSCALE,
                y: this.isFocus ? FOCUSED_SCALE : RECOVER_YSCALE
            });
            Stack.shadow(this.isFocus ? FOCUSED_SHADOW : NORMAL_SHADOW);
            Stack.margin({
                left: STACK_PADDING,
                right: STACK_PADDING
            });
        }, Stack);
        this.observeComponentCreation2((b7, c7) => {
            Flex.create(this.getFlexOptions());
            Flex.constraintSize({
                minHeight: this.itemHeight
            });
            Flex.focusable(IS_CLOSE_CHILD_FOCUS);
            Flex.borderRadius({
                "id": -1,
                "type": 10002,
                params: ['sys.float.composeListItem_radius'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
            Flex.backgroundColor(ObservedObject.GetRawObject(this.frontColor));
            Flex.onFocus(() => {
                this.canFocus = true;
            });
            Flex.onBlur(() => {
                this.canFocus = false;
            });
            Flex.onHover((d7) => {
                if (this.isFocus && !IS_CLOSE_CHILD_FOCUS) {
                    this.isHover = false;
                    return;
                }
                this.isHover = d7;
                if (this.canHover) {
                    this.frontColor = d7 ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
                if (!IS_CLOSE_CHILD_FOCUS) {
                    this.frontColor = d7 ? this.hoveringColor : NORMAL_BG;
                }
            });
            ViewStackProcessor.visualState("pressed");
            Flex.backgroundColor(ObservedObject.GetRawObject(this.touchDownColor));
            ViewStackProcessor.visualState("normal");
            Flex.border({
                radius: {
                    "id": -1,
                    "type": 10002,
                    params: ['sys.float.composeListItem_radius'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                },
                color: {
                    "id": -1,
                    "type": 10001,
                    params: ['sys.color.composeListItem_stroke_normal_color'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                },
                width: {
                    "id": -1,
                    "type": 10002,
                    params: ['sys.float.composeListItem_stroke_normal_thickness'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                },
            });
            ViewStackProcessor.visualState("focused");
            Flex.border({
                radius: {
                    "id": -1,
                    "type": 10002,
                    params: ['sys.float.composeListItem_radius'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                },
                width: ITEM_BORDER_SHOWN,
                color: this.focusOutlineColor,
                style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState();
            Flex.padding(ObservedObject.GetRawObject(this.containerPadding));
        }, Flex);
        this.observeComponentCreation2((v6, w6) => {
            If.create();
            if (this.contentItem === null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((x6, y6) => {
                            if (y6) {
                                let z6 = new ContentItemStruct(this, {
                                    isWrapText: this.__isWrapText
                                }, undefined, x6, () => {
                                }, {
                                    page: "library/src/main/ets/components/composelistitem.ets",
                                    line: 1085,
                                    col: 11
                                });
                                ViewPU.create(z6);
                                let a7 = () => {
                                    return {
                                        isWrapText: this.isWrapText
                                    };
                                };
                                z6.paramsGenerator_ = a7;
                            } else {
                                this.updateStateVarsOfChildByElmtId(x6, {});
                            }
                        }, { name: "ContentItemStruct" });
                    }
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((p6, q6) => {
            If.create();
            if (this.contentItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((r6, s6) => {
                            if (s6) {
                                let t6 = new ContentItemStruct(this, {
                                    icon: this.contentItem?.icon,
                                    iconStyle: this.contentItem?.iconStyle,
                                    primaryText: this.contentItem?.primaryText,
                                    secondaryText: this.contentItem?.secondaryText,
                                    description: this.contentItem?.description,
                                    leftWidth: this.calculatedLeftWidth(),
                                    fontSizeScale: this.fontSizeScale,
                                    parentDirection: this.containerDirection,
                                    itemDirection: this.contentItemDirection,
                                    isFocus: this.isFocus,
                                    itemHeight: this.itemHeight,
                                    isWrapText: this.__isWrapText
                                }, undefined, r6, () => {
                                }, {
                                    page: "library/src/main/ets/components/composelistitem.ets",
                                    line: 1090,
                                    col: 11
                                });
                                ViewPU.create(t6);
                                let u6 = () => {
                                    return {
                                        icon: this.contentItem?.icon,
                                        iconStyle: this.contentItem?.iconStyle,
                                        primaryText: this.contentItem?.primaryText,
                                        secondaryText: this.contentItem?.secondaryText,
                                        description: this.contentItem?.description,
                                        leftWidth: this.calculatedLeftWidth(),
                                        fontSizeScale: this.fontSizeScale,
                                        parentDirection: this.containerDirection,
                                        itemDirection: this.contentItemDirection,
                                        isFocus: this.isFocus,
                                        itemHeight: this.itemHeight,
                                        isWrapText: this.isWrapText
                                    };
                                };
                                t6.paramsGenerator_ = u6;
                            } else {
                                this.updateStateVarsOfChildByElmtId(r6, {
                                    icon: this.contentItem?.icon,
                                    iconStyle: this.contentItem?.iconStyle,
                                    primaryText: this.contentItem?.primaryText,
                                    secondaryText: this.contentItem?.secondaryText,
                                    description: this.contentItem?.description,
                                    leftWidth: this.calculatedLeftWidth(),
                                    fontSizeScale: this.fontSizeScale,
                                    parentDirection: this.containerDirection,
                                    itemDirection: this.contentItemDirection,
                                    isFocus: this.isFocus,
                                    itemHeight: this.itemHeight
                                });
                            }
                        }, { name: "ContentItemStruct" });
                    }
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((h6, i6) => {
            If.create();
            if (this.operateItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n6, o6) => {
                        __Common__.create();
                        __Common__.flexShrink(0);
                        __Common__.onFocus(() => {
                            this.canFocus = false;
                        });
                        __Common__.onBlur(() => {
                            this.canFocus = true;
                        });
                        __Common__.padding({ start: this.getOperateOffset() });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((j6, k6) => {
                            if (k6) {
                                let l6 = new OperateItemStruct(this, {
                                    icon: this.operateItem?.icon,
                                    subIcon: this.operateItem?.subIcon,
                                    button: this.operateItem?.button,
                                    switch: this.operateItem?.switch,
                                    checkBox: this.operateItem?.checkbox,
                                    radio: this.operateItem?.radio,
                                    image: this.operateItem?.image,
                                    text: this.operateItem?.text,
                                    arrow: this.operateItem?.arrow,
                                    parentCanFocus: this.__canFocus,
                                    parentCanTouch: this.__canTouch,
                                    parentIsHover: this.__isHover,
                                    parentFrontColor: this.__frontColor,
                                    parentIsActive: this.__isActive,
                                    parentCanHover: this.__canHover,
                                    rightWidth: this.calculatedRightWidth(),
                                    parentDirection: this.__containerDirection,
                                    isFocus: this.__isFocus,
                                    isChecked: this.__isChecked,
                                }, undefined, j6, () => {
                                }, {
                                    page: "library/src/main/ets/components/composelistitem.ets",
                                    line: 1106,
                                    col: 11
                                });
                                ViewPU.create(l6);
                                let m6 = () => {
                                    return {
                                        icon: this.operateItem?.icon,
                                        subIcon: this.operateItem?.subIcon,
                                        button: this.operateItem?.button,
                                        switch: this.operateItem?.switch,
                                        checkBox: this.operateItem?.checkbox,
                                        radio: this.operateItem?.radio,
                                        image: this.operateItem?.image,
                                        text: this.operateItem?.text,
                                        arrow: this.operateItem?.arrow,
                                        parentCanFocus: this.canFocus,
                                        parentCanTouch: this.canTouch,
                                        parentIsHover: this.isHover,
                                        parentFrontColor: this.frontColor,
                                        parentIsActive: this.isActive,
                                        parentCanHover: this.canHover,
                                        rightWidth: this.calculatedRightWidth(),
                                        parentDirection: this.containerDirection,
                                        isFocus: this.isFocus,
                                        isChecked: this.isChecked
                                    };
                                };
                                l6.paramsGenerator_ = m6;
                            } else {
                                this.updateStateVarsOfChildByElmtId(j6, {
                                    icon: this.operateItem?.icon,
                                    subIcon: this.operateItem?.subIcon,
                                    button: this.operateItem?.button,
                                    switch: this.operateItem?.switch,
                                    checkBox: this.operateItem?.checkbox,
                                    radio: this.operateItem?.radio,
                                    image: this.operateItem?.image,
                                    text: this.operateItem?.text,
                                    arrow: this.operateItem?.arrow,
                                    rightWidth: this.calculatedRightWidth()
                                });
                            }
                        }, { name: "OperateItemStruct" });
                    }
                    __Common__.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
        Stack.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default { IconType, ComposeListItem };