/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const hilog = requireNapi('hilog');
const measure = requireNapi('measure');

export var IconType;
(function (t17) {
    t17[t17["BADGE"] = 1] = "BADGE";
    t17[t17["NORMAL_ICON"] = 2] = "NORMAL_ICON";
    t17[t17["SYSTEM_ICON"] = 3] = "SYSTEM_ICON";
    t17[t17["HEAD_SCULPTURE"] = 4] = "HEAD_SCULPTURE";
    t17[t17["APP_ICON"] = 5] = "APP_ICON";
    t17[t17["PREVIEW"] = 6] = "PREVIEW";
    t17[t17["LONGITUDINAL"] = 7] = "LONGITUDINAL";
    t17[t17["VERTICAL"] = 8] = "VERTICAL";
})(IconType || (IconType = {}));
var FontSizeScaleLevel;
(function (s17) {
    s17[s17["LEVEL1"] = 1.75] = "LEVEL1";
    s17[s17["LEVEL2"] = 2] = "LEVEL2";
    s17[s17["LEVEL3"] = 3.2] = "LEVEL3";
})(FontSizeScaleLevel || (FontSizeScaleLevel = {}));
var ItemHeight;
(function (r17) {
    r17[r17["FIRST_HEIGHT"] = 48] = "FIRST_HEIGHT";
    r17[r17["SECOND_HEIGHT"] = 56] = "SECOND_HEIGHT";
    r17[r17["THIRD_HEIGHT"] = 64] = "THIRD_HEIGHT";
    r17[r17["FOURTH_HEIGHT"] = 72] = "FOURTH_HEIGHT";
    r17[r17["FIFTH_HEIGHT"] = 96] = "FIFTH_HEIGHT";
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
const RIGHT_CONTENT_NULL_RIGHTWIDTH = '0vp';
const LEFT_PART_WIDTH = 'calc(66% - 16vp)';
const RIGHT_PART_WIDTH = '34%';
const RIGHT_ONLY_ARROW_WIDTH = '24vp';
const RIGHT_ONLY_IMAGE_WIDTH = '54vp';
const RIGHT_ONLY_ICON_WIDTH = '40vp';
const RIGHT_ICON_SUB_ICON_WIDTH = '80vp';
const RIGHT_ONLY_RADIO_WIDTH = '30vp';
const RIGHT_ONLY_CHECKBOX_WIDTH = '30vp';
const RIGHT_ONLY_SWITCH_WIDTH = '44vp';
const ACCESSIBILITY_LEVEL_AUTO = 'auto';
const RESOURCE_TYPE_SYMBOL = 40000;
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
const IS_SUPPORT_SUBCOMPONENT_EVENT = LengthMetrics.resource({
    "id": -1,
    "type": 10002,
    params: ['sys.float.composeListItem_focus_dynamic_effect'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
}).value !== 1;
const RECOVER_ITEM_SCALE = 1;
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
const OPERATE_ITEM_COLOR = '#99000000';
const TEXT_SUPPORT_MARQUEE = 1;
const IS_MARQUEE_OR_ELLIPSIS = LengthMetrics.resource({
    "id": -1,
    "type": 10002,
    params: ['sys.float.composeListItem_right_textOverflow'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
}).value;
const UNUSUAL = -1;
const FOCUSED_BG_COLOR = {
    "id": -1,
    "type": 10001,
    params: ['sys.color.composeListItem_container_focus_color'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
const NORMAL_BG_COLOR = {
    "id": -1,
    "type": 10001,
    params: ['sys.color.composeListItem_container_normal_color'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
const FOCUSED_ITEM_SCALE = LengthMetrics.resource({
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
const ITEM_PADDING = {
    "id": -1,
    "type": 10002,
    params: ['sys.float.composeListItem_padding'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
};
const OPERATEITEM_ARROW_MARGIN_WIDTH = LengthMetrics.resource({
    "id": -1,
    "type": 10002,
    params: ['sys.float.composeListItem_arrow_margin'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
}).value;
const APPICON_ITEMLENGTH = LengthMetrics.resource({
    "id": -1,
    "type": 10002,
    params: ['sys.float.composeListItem_AppIcon_ItemLength'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
}).value;

class Util {
    static isSymbolResource(p17) {
        if (!Util.isResourceType(p17)) {
            return false;
        }
        let q17 = p17;
        return q17.type === RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(o17) {
        if (!o17) {
            return false;
        }
        if (typeof o17 === 'string' || typeof o17 === 'undefined') {
            return false;
        }
        return true;
    }
}

class ContentItemStruct extends ViewPU {
    constructor(i17, j17, k17, l17 = -1, m17 = undefined, n17) {
        super(i17, k17, l17, n17);
        if (typeof m17 === "function") {
            this.paramsGenerator_ = m17;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(j17.iconStyle, this, "iconStyle");
        this.__icon = new SynchedPropertyObjectOneWayPU(j17.icon, this, "icon");
        this.__symbolStyle = new SynchedPropertyObjectOneWayPU(j17.symbolStyle, this, "symbolStyle");
        this.__primaryText = new SynchedPropertyObjectOneWayPU(j17.primaryText, this, "primaryText");
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(j17.secondaryText, this, "secondaryText");
        this.__description = new SynchedPropertyObjectOneWayPU(j17.description, this, "description");
        this.__itemRowSpace = new ObservedPropertySimplePU(NORMAL_ITEM_ROW_SPACE, this, "itemRowSpace");
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(j17.leftWidth, this, "leftWidth");
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
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(j17.fontSizeScale, this, "fontSizeScale");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(j17.parentDirection, this, "parentDirection");
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(j17.itemDirection, this, "itemDirection");
        this.__isFocus = new SynchedPropertySimpleOneWayPU(j17.isFocus, this, "isFocus");
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
        this.__itemHeight = new SynchedPropertyObjectOneWayPU(j17.itemHeight, this, "itemHeight");
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
        this.__isWrapText = new SynchedPropertyObjectTwoWayPU(j17.isWrapText, this, "isWrapText");
        this.__isWrapFirstText = new ObservedPropertyObjectPU(false, this, "isWrapFirstText");
        this.__isWrapSecondText = new ObservedPropertyObjectPU(false, this, "isWrapSecondText");
        this.__isWrapThirdText = new ObservedPropertyObjectPU(false, this, "isWrapThirdText");
        this.setInitiallyProvidedValue(j17);
        this.declareWatch("iconStyle", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("symbolStyle", this.onPropChange);
        this.declareWatch("primaryText", this.onPropChange);
        this.declareWatch("secondaryText", this.onPropChange);
        this.declareWatch("description", this.onPropChange);
        this.declareWatch("primaryTextColor", this.onPropChange);
        this.declareWatch("secondaryTextColor", this.onPropChange);
        this.declareWatch("descriptionColor", this.onPropChange);
        this.declareWatch("isFocus", this.onPropChange);
        this.declareWatch("isWrapFirstText", this.onWrapChange);
        this.declareWatch("isWrapSecondText", this.onWrapChange);
        this.declareWatch("isWrapThirdText", this.onWrapChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(h17) {
        if (h17.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (h17.icon === undefined) {
            this.__icon.set(null);
        }
        if (h17.symbolStyle === undefined) {
            this.__symbolStyle.set(null);
        }
        if (h17.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (h17.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (h17.description === undefined) {
            this.__description.set(null);
        }
        if (h17.itemRowSpace !== undefined) {
            this.itemRowSpace = h17.itemRowSpace;
        }
        if (h17.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (h17.primaryTextColor !== undefined) {
            this.primaryTextColor = h17.primaryTextColor;
        }
        if (h17.secondaryTextColor !== undefined) {
            this.secondaryTextColor = h17.secondaryTextColor;
        }
        if (h17.descriptionColor !== undefined) {
            this.descriptionColor = h17.descriptionColor;
        }
        if (h17.isFocus === undefined) {
            this.__isFocus.set(false);
        }
        if (h17.primaryTextSize !== undefined) {
            this.primaryTextSize = h17.primaryTextSize;
        }
        if (h17.primaryTextColors !== undefined) {
            this.primaryTextColors = h17.primaryTextColors;
        }
        if (h17.itemHeight === undefined) {
            this.__itemHeight.set(null);
        }
        if (h17.iconColor !== undefined) {
            this.iconColor = h17.iconColor;
        }
        if (h17.secondaryTextColors !== undefined) {
            this.secondaryTextColors = h17.secondaryTextColors;
        }
        if (h17.secondaryThirdTextSize !== undefined) {
            this.secondaryThirdTextSize = h17.secondaryThirdTextSize;
        }
        if (h17.descriptionColors !== undefined) {
            this.descriptionColors = h17.descriptionColors;
        }
        if (h17.isWrapFirstText !== undefined) {
            this.isWrapFirstText = h17.isWrapFirstText;
        }
        if (h17.isWrapSecondText !== undefined) {
            this.isWrapSecondText = h17.isWrapSecondText;
        }
        if (h17.isWrapThirdText !== undefined) {
            this.isWrapThirdText = h17.isWrapThirdText;
        }
    }

    updateStateVars(g17) {
        this.__iconStyle.reset(g17.iconStyle);
        this.__icon.reset(g17.icon);
        this.__symbolStyle.reset(g17.symbolStyle);
        this.__primaryText.reset(g17.primaryText);
        this.__secondaryText.reset(g17.secondaryText);
        this.__description.reset(g17.description);
        this.__leftWidth.reset(g17.leftWidth);
        this.__fontSizeScale.reset(g17.fontSizeScale);
        this.__parentDirection.reset(g17.parentDirection);
        this.__itemDirection.reset(g17.itemDirection);
        this.__isFocus.reset(g17.isFocus);
        this.__itemHeight.reset(g17.itemHeight);
    }

    purgeVariableDependenciesOnElmtId(f17) {
        this.__iconStyle.purgeDependencyOnElmtId(f17);
        this.__icon.purgeDependencyOnElmtId(f17);
        this.__symbolStyle.purgeDependencyOnElmtId(f17);
        this.__primaryText.purgeDependencyOnElmtId(f17);
        this.__secondaryText.purgeDependencyOnElmtId(f17);
        this.__description.purgeDependencyOnElmtId(f17);
        this.__itemRowSpace.purgeDependencyOnElmtId(f17);
        this.__leftWidth.purgeDependencyOnElmtId(f17);
        this.__primaryTextColor.purgeDependencyOnElmtId(f17);
        this.__secondaryTextColor.purgeDependencyOnElmtId(f17);
        this.__descriptionColor.purgeDependencyOnElmtId(f17);
        this.__fontSizeScale.purgeDependencyOnElmtId(f17);
        this.__parentDirection.purgeDependencyOnElmtId(f17);
        this.__itemDirection.purgeDependencyOnElmtId(f17);
        this.__isFocus.purgeDependencyOnElmtId(f17);
        this.__primaryTextSize.purgeDependencyOnElmtId(f17);
        this.__primaryTextColors.purgeDependencyOnElmtId(f17);
        this.__itemHeight.purgeDependencyOnElmtId(f17);
        this.__iconColor.purgeDependencyOnElmtId(f17);
        this.__secondaryTextColors.purgeDependencyOnElmtId(f17);
        this.__secondaryThirdTextSize.purgeDependencyOnElmtId(f17);
        this.__descriptionColors.purgeDependencyOnElmtId(f17);
        this.__isWrapText.purgeDependencyOnElmtId(f17);
        this.__isWrapFirstText.purgeDependencyOnElmtId(f17);
        this.__isWrapSecondText.purgeDependencyOnElmtId(f17);
        this.__isWrapThirdText.purgeDependencyOnElmtId(f17);
    }

    aboutToBeDeleted() {
        this.__iconStyle.aboutToBeDeleted();
        this.__icon.aboutToBeDeleted();
        this.__symbolStyle.aboutToBeDeleted();
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
        this.__isWrapFirstText.aboutToBeDeleted();
        this.__isWrapSecondText.aboutToBeDeleted();
        this.__isWrapThirdText.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get iconStyle() {
        return this.__iconStyle.get();
    }

    set iconStyle(e17) {
        this.__iconStyle.set(e17);
    }

    get icon() {
        return this.__icon.get();
    }

    set icon(d17) {
        this.__icon.set(d17);
    }

    get symbolStyle() {
        return this.__symbolStyle.get();
    }

    set symbolStyle(c17) {
        this.__symbolStyle.set(c17);
    }

    get primaryText() {
        return this.__primaryText.get();
    }

    set primaryText(b17) {
        this.__primaryText.set(b17);
    }

    get secondaryText() {
        return this.__secondaryText.get();
    }

    set secondaryText(a17) {
        this.__secondaryText.set(a17);
    }

    get description() {
        return this.__description.get();
    }

    set description(z16) {
        this.__description.set(z16);
    }

    get itemRowSpace() {
        return this.__itemRowSpace.get();
    }

    set itemRowSpace(y16) {
        this.__itemRowSpace.set(y16);
    }

    get leftWidth() {
        return this.__leftWidth.get();
    }

    set leftWidth(x16) {
        this.__leftWidth.set(x16);
    }

    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }

    set primaryTextColor(w16) {
        this.__primaryTextColor.set(w16);
    }

    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }

    set secondaryTextColor(v16) {
        this.__secondaryTextColor.set(v16);
    }

    get descriptionColor() {
        return this.__descriptionColor.get();
    }

    set descriptionColor(u16) {
        this.__descriptionColor.set(u16);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(t16) {
        this.__fontSizeScale.set(t16);
    }

    get parentDirection() {
        return this.__parentDirection.get();
    }

    set parentDirection(s16) {
        this.__parentDirection.set(s16);
    }

    get itemDirection() {
        return this.__itemDirection.get();
    }

    set itemDirection(r16) {
        this.__itemDirection.set(r16);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(q16) {
        this.__isFocus.set(q16);
    }

    get primaryTextSize() {
        return this.__primaryTextSize.get();
    }

    set primaryTextSize(p16) {
        this.__primaryTextSize.set(p16);
    }

    get primaryTextColors() {
        return this.__primaryTextColors.get();
    }

    set primaryTextColors(o16) {
        this.__primaryTextColors.set(o16);
    }

    get itemHeight() {
        return this.__itemHeight.get();
    }

    set itemHeight(n16) {
        this.__itemHeight.set(n16);
    }

    get iconColor() {
        return this.__iconColor.get();
    }

    set iconColor(m16) {
        this.__iconColor.set(m16);
    }

    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }

    set secondaryTextColors(l16) {
        this.__secondaryTextColors.set(l16);
    }

    get secondaryThirdTextSize() {
        return this.__secondaryThirdTextSize.get();
    }

    set secondaryThirdTextSize(k16) {
        this.__secondaryThirdTextSize.set(k16);
    }

    get descriptionColors() {
        return this.__descriptionColors.get();
    }

    set descriptionColors(j16) {
        this.__descriptionColors.set(j16);
    }

    get isWrapText() {
        return this.__isWrapText.get();
    }

    set isWrapText(i16) {
        this.__isWrapText.set(i16);
    }

    get isWrapFirstText() {
        return this.__isWrapFirstText.get();
    }

    set isWrapFirstText(h16) {
        this.__isWrapFirstText.set(h16);
    }

    get isWrapSecondText() {
        return this.__isWrapSecondText.get();
    }

    set isWrapSecondText(g16) {
        this.__isWrapSecondText.set(g16);
    }

    get isWrapThirdText() {
        return this.__isWrapThirdText.get();
    }

    set isWrapThirdText(f16) {
        this.__isWrapThirdText.set(f16);
    }

    onWillApplyTheme(e16) {
        this.primaryTextColor = e16.colors.fontPrimary;
        this.secondaryTextColor = e16.colors.fontSecondary;
        this.descriptionColor = e16.colors.fontTertiary;
    }

    onPropChange() {
        if (this.icon == null && this.symbolStyle == null && this.iconStyle == null) {
            this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
        } else {
            this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        }
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus) {
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
        this.isWrapText = this.isWrapFirstText || this.isWrapSecondText || this.isWrapThirdText;
    }

    getContentItemIconFillColor() {
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

    judgeIsWrap(a16, b16, c16) {
        let d16 = this.getSingleRowTextHeight(a16, b16);
        return c16 > d16;
    }

    getSingleRowTextHeight(x15, y15) {
        if (x15 && y15) {
            let z15 = px2vp(measure.measureTextSize({
                textContent: x15,
                fontSize: y15,
                maxLines: TEXT_MAX_LINE
            }).height);
            return z15;
        }
        return 0;
    }

    aboutToAppear() {
        this.onPropChange();
    }

    createIcon(p14 = null) {
        this.observeComponentCreation2((r14, s14) => {
            If.create();
            if (this.iconStyle != null && ICON_SIZE_MAP.has(this.iconStyle)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w14, x14) => {
                        If.create();
                        if (this.symbolStyle != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((v15, w15) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.symbolStyle));
                                    SymbolGlyph.fontSize(ICON_SIZE_MAP.get(this.iconStyle));
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.borderRadius({
                                        "id": -1,
                                        "type": 10002,
                                        params: ['sys.float.composeListItem_Image_Radius'],
                                        "bundleName": "__harDefaultBundleName__",
                                        "moduleName": "__harDefaultModuleName__"
                                    });
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.flexShrink(0);
                                }, SymbolGlyph);
                            });
                        } else if (this.icon != null) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((b15, c15) => {
                                    If.create();
                                    if (Util.isSymbolResource(ObservedObject.GetRawObject(this.icon))) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((r15, s15) => {
                                                SymbolGlyph.create(this.icon);
                                                SymbolGlyph.fontSize(ICON_SIZE_MAP.get(this.iconStyle));
                                                SymbolGlyph.fontColor([this.getContentItemIconFillColor()]);
                                                SymbolGlyph.borderRadius({
                                                    "id": -1,
                                                    "type": 10002,
                                                    params: ['sys.float.composeListItem_Image_Radius'],
                                                    "bundleName": "__harDefaultBundleName__",
                                                    "moduleName": "__harDefaultModuleName__"
                                                });
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                                SymbolGlyph.flexShrink(0);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((f15, g15) => {
                                                If.create();
                                                if (this.iconStyle <= IconType.PREVIEW) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((n15, o15) => {
                                                            Image.create(this.icon);
                                                            Image.objectFit(ImageFit.Contain);
                                                            Image.width(ICON_SIZE_MAP.get(this.iconStyle));
                                                            Image.height(ICON_SIZE_MAP.get(this.iconStyle));
                                                            Image.borderRadius({
                                                                "id": -1,
                                                                "type": 10002,
                                                                params: ['sys.float.composeListItem_Image_Radius'],
                                                                "bundleName": "__harDefaultBundleName__",
                                                                "moduleName": "__harDefaultModuleName__"
                                                            });
                                                            Image.focusable(false);
                                                            Image.draggable(false);
                                                            Image.fillColor(this.getContentItemIconFillColor());
                                                            Image.flexShrink(0);
                                                        }, Image);
                                                    });
                                                } else {
                                                    this.ifElseBranchUpdateFunction(1, () => {
                                                        this.observeComponentCreation2((j15, k15) => {
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
                                                                params: ['sys.float.composeListItem_Image_Radius'],
                                                                "bundleName": "__harDefaultBundleName__",
                                                                "moduleName": "__harDefaultModuleName__"
                                                            });
                                                            Image.focusable(false);
                                                            Image.draggable(false);
                                                            Image.fillColor(this.getContentItemIconFillColor());
                                                            Image.flexShrink(0);
                                                        }, Image);
                                                    });
                                                }
                                            }, If);
                                            If.pop();
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(2, () => {
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

    createText(j13 = null) {
        this.observeComponentCreation2((n14, o14) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.margin(this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 ? undefined : {
                top: TEXT_SAFE_MARGIN,
                bottom: TEXT_SAFE_MARGIN
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((i14, j14) => {
            Text.create(this.primaryText);
            Text.fontSize(ObservedObject.GetRawObject(this.primaryTextSize));
            Text.fontColor(ObservedObject.GetRawObject(this.primaryTextColors));
            Text.maxLines(LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.composeListItem_maxLines_right'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            }).value);
            Text.textOverflow({
                overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                TextOverflow.Ellipsis
            });
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(true);
            Text.draggable(false);
            Text.onSizeChange((l14, m14) => {
                this.isWrapFirstText = this.judgeIsWrap(ObservedObject.GetRawObject(this.primaryText),
                    ObservedObject.GetRawObject(this.primaryTextSize), m14.height);
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((y13, z13) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d14, e14) => {
                        Text.create(this.secondaryText);
                        Text.fontSize(ObservedObject.GetRawObject(this.secondaryThirdTextSize));
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColors));
                        Text.maxLines(LengthMetrics.resource({
                            "id": -1,
                            "type": 10002,
                            params: ['sys.float.composeListItem_maxLines_right'],
                            "bundleName": "__harDefaultBundleName__",
                            "moduleName": "__harDefaultModuleName__"
                        }).value);
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                            TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.onSizeChange((g14, h14) => {
                            this.isWrapSecondText = this.judgeIsWrap(ObservedObject.GetRawObject(this.secondaryText),
                                ObservedObject.GetRawObject(this.secondaryThirdTextSize), h14.height);
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
        this.observeComponentCreation2((o13, p13) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t13, u13) => {
                        Text.create(this.description);
                        Text.fontSize(ObservedObject.GetRawObject(this.secondaryThirdTextSize));
                        Text.fontColor(ObservedObject.GetRawObject(this.descriptionColors));
                        Text.maxLines(LengthMetrics.resource({
                            "id": -1,
                            "type": 10002,
                            params: ['sys.float.composeListItem_maxLines_right'],
                            "bundleName": "__harDefaultBundleName__",
                            "moduleName": "__harDefaultModuleName__"
                        }).value);
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                            TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.onSizeChange((w13, x13) => {
                            this.isWrapThirdText = this.judgeIsWrap(ObservedObject.GetRawObject(this.description),
                                ObservedObject.GetRawObject(this.secondaryThirdTextSize), x13.height);
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
        this.observeComponentCreation2((h13, i13) => {
            Flex.create({
                space: { main: this.getItemSpace() },
                direction: this.itemDirection,
                justifyContent: FlexAlign.Start,
                alignItems: this.isColumnDirection() ? ItemAlign.Start : ItemAlign.Center,
            });
            Flex.height(this.itemDirection === FlexDirection.Column ? 'auto' : undefined);
            Flex.margin({
                end: this.isParentColumnDirection() ?
                LengthMetrics.vp(0) :
                LengthMetrics.vp(16)
            });
            Flex.padding({ start: LengthMetrics.vp(LISTITEM_PADDING) });
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
    constructor(a13, b13, c13, d13 = -1, e13 = undefined, f13) {
        super(a13, c13, d13, f13);
        if (typeof e13 === "function") {
            this.paramsGenerator_ = e13;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(b13.arrow, this, "arrow");
        this.__icon = new SynchedPropertyObjectOneWayPU(b13.icon, this, "icon");
        this.__subIcon = new SynchedPropertyObjectOneWayPU(b13.subIcon, this, "subIcon");
        this.__button = new SynchedPropertyObjectOneWayPU(b13.button, this, "button");
        this.__switch = new SynchedPropertyObjectOneWayPU(b13.switch, this, "switch");
        this.__checkBox = new SynchedPropertyObjectOneWayPU(b13.checkBox, this, "checkBox");
        this.__radio = new SynchedPropertyObjectOneWayPU(b13.radio, this, "radio");
        this.__image = new SynchedPropertyObjectOneWayPU(b13.image, this, "image");
        this.__symbolStyle = new SynchedPropertyObjectOneWayPU(b13.symbolStyle, this, "symbolStyle");
        this.__text = new SynchedPropertyObjectOneWayPU(b13.text, this, "text");
        this.__switchState = new ObservedPropertySimplePU(false, this, "switchState");
        this.__radioState = new ObservedPropertySimplePU(false, this, "radioState");
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, "checkBoxState");
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(b13.rightWidth, this, "rightWidth");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "secondaryTextColor");
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, "hoveringColor");
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, "activedColor");
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(b13.parentCanFocus, this, "parentCanFocus");
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(b13.parentCanTouch, this, "parentCanTouch");
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(b13.parentIsHover, this, "parentIsHover");
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(b13.parentCanHover, this, "parentCanHover");
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(b13.parentIsActive, this, "parentIsActive");
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(b13.parentFrontColor, this, "parentFrontColor");
        this.__parentDirection = new SynchedPropertySimpleTwoWayPU(b13.parentDirection, this, "parentDirection");
        this.__rowSpace = new ObservedPropertySimplePU(DEFAULT_ROW_SPACE, this, "rowSpace");
        this.__isFocus = new SynchedPropertySimpleTwoWayPU(b13.isFocus, this, "isFocus");
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
        this.__isChecked = new SynchedPropertySimpleTwoWayPU(b13.isChecked, this, "isChecked");
        this.setInitiallyProvidedValue(b13);
        this.declareWatch("arrow", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("subIcon", this.onPropChange);
        this.declareWatch("button", this.onPropChange);
        this.declareWatch("switch", this.onPropChange);
        this.declareWatch("checkBox", this.onPropChange);
        this.declareWatch("radio", this.onPropChange);
        this.declareWatch("image", this.onPropChange);
        this.declareWatch("symbolStyle", this.onPropChange);
        this.declareWatch("text", this.onPropChange);
        this.declareWatch("secondaryTextColor", this.onFocusChange);
        this.declareWatch("isFocus", this.onFocusChange);
        this.declareWatch("isChecked", this.onPropChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(z12) {
        if (z12.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (z12.icon === undefined) {
            this.__icon.set(null);
        }
        if (z12.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (z12.button === undefined) {
            this.__button.set(null);
        }
        if (z12.switch === undefined) {
            this.__switch.set(null);
        }
        if (z12.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (z12.radio === undefined) {
            this.__radio.set(null);
        }
        if (z12.image === undefined) {
            this.__image.set(null);
        }
        if (z12.symbolStyle === undefined) {
            this.__symbolStyle.set(null);
        }
        if (z12.text === undefined) {
            this.__text.set(null);
        }
        if (z12.switchState !== undefined) {
            this.switchState = z12.switchState;
        }
        if (z12.radioState !== undefined) {
            this.radioState = z12.radioState;
        }
        if (z12.checkBoxState !== undefined) {
            this.checkBoxState = z12.checkBoxState;
        }
        if (z12.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (z12.secondaryTextColor !== undefined) {
            this.secondaryTextColor = z12.secondaryTextColor;
        }
        if (z12.hoveringColor !== undefined) {
            this.hoveringColor = z12.hoveringColor;
        }
        if (z12.activedColor !== undefined) {
            this.activedColor = z12.activedColor;
        }
        if (z12.rowSpace !== undefined) {
            this.rowSpace = z12.rowSpace;
        }
        if (z12.secondaryTextSize !== undefined) {
            this.secondaryTextSize = z12.secondaryTextSize;
        }
        if (z12.secondaryTextColors !== undefined) {
            this.secondaryTextColors = z12.secondaryTextColors;
        }
        if (z12.iconColor !== undefined) {
            this.iconColor = z12.iconColor;
        }
    }

    updateStateVars(y12) {
        this.__arrow.reset(y12.arrow);
        this.__icon.reset(y12.icon);
        this.__subIcon.reset(y12.subIcon);
        this.__button.reset(y12.button);
        this.__switch.reset(y12.switch);
        this.__checkBox.reset(y12.checkBox);
        this.__radio.reset(y12.radio);
        this.__image.reset(y12.image);
        this.__symbolStyle.reset(y12.symbolStyle);
        this.__text.reset(y12.text);
        this.__rightWidth.reset(y12.rightWidth);
    }

    purgeVariableDependenciesOnElmtId(x12) {
        this.__arrow.purgeDependencyOnElmtId(x12);
        this.__icon.purgeDependencyOnElmtId(x12);
        this.__subIcon.purgeDependencyOnElmtId(x12);
        this.__button.purgeDependencyOnElmtId(x12);
        this.__switch.purgeDependencyOnElmtId(x12);
        this.__checkBox.purgeDependencyOnElmtId(x12);
        this.__radio.purgeDependencyOnElmtId(x12);
        this.__image.purgeDependencyOnElmtId(x12);
        this.__symbolStyle.purgeDependencyOnElmtId(x12);
        this.__text.purgeDependencyOnElmtId(x12);
        this.__switchState.purgeDependencyOnElmtId(x12);
        this.__radioState.purgeDependencyOnElmtId(x12);
        this.__checkBoxState.purgeDependencyOnElmtId(x12);
        this.__rightWidth.purgeDependencyOnElmtId(x12);
        this.__secondaryTextColor.purgeDependencyOnElmtId(x12);
        this.__hoveringColor.purgeDependencyOnElmtId(x12);
        this.__activedColor.purgeDependencyOnElmtId(x12);
        this.__parentCanFocus.purgeDependencyOnElmtId(x12);
        this.__parentCanTouch.purgeDependencyOnElmtId(x12);
        this.__parentIsHover.purgeDependencyOnElmtId(x12);
        this.__parentCanHover.purgeDependencyOnElmtId(x12);
        this.__parentIsActive.purgeDependencyOnElmtId(x12);
        this.__parentFrontColor.purgeDependencyOnElmtId(x12);
        this.__parentDirection.purgeDependencyOnElmtId(x12);
        this.__rowSpace.purgeDependencyOnElmtId(x12);
        this.__isFocus.purgeDependencyOnElmtId(x12);
        this.__secondaryTextSize.purgeDependencyOnElmtId(x12);
        this.__secondaryTextColors.purgeDependencyOnElmtId(x12);
        this.__iconColor.purgeDependencyOnElmtId(x12);
        this.__isChecked.purgeDependencyOnElmtId(x12);
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
        this.__symbolStyle.aboutToBeDeleted();
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

    set arrow(w12) {
        this.__arrow.set(w12);
    }

    get icon() {
        return this.__icon.get();
    }

    set icon(v12) {
        this.__icon.set(v12);
    }

    get subIcon() {
        return this.__subIcon.get();
    }

    set subIcon(u12) {
        this.__subIcon.set(u12);
    }

    get button() {
        return this.__button.get();
    }

    set button(t12) {
        this.__button.set(t12);
    }

    get switch() {
        return this.__switch.get();
    }

    set switch(s12) {
        this.__switch.set(s12);
    }

    get checkBox() {
        return this.__checkBox.get();
    }

    set checkBox(r12) {
        this.__checkBox.set(r12);
    }

    get radio() {
        return this.__radio.get();
    }

    set radio(q12) {
        this.__radio.set(q12);
    }

    get image() {
        return this.__image.get();
    }

    set image(p12) {
        this.__image.set(p12);
    }

    get symbolStyle() {
        return this.__symbolStyle.get();
    }

    set symbolStyle(o12) {
        this.__symbolStyle.set(o12);
    }

    get text() {
        return this.__text.get();
    }

    set text(n12) {
        this.__text.set(n12);
    }

    get switchState() {
        return this.__switchState.get();
    }

    set switchState(m12) {
        this.__switchState.set(m12);
    }

    get radioState() {
        return this.__radioState.get();
    }

    set radioState(l12) {
        this.__radioState.set(l12);
    }

    get checkBoxState() {
        return this.__checkBoxState.get();
    }

    set checkBoxState(k12) {
        this.__checkBoxState.set(k12);
    }

    get rightWidth() {
        return this.__rightWidth.get();
    }

    set rightWidth(j12) {
        this.__rightWidth.set(j12);
    }

    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }

    set secondaryTextColor(i12) {
        this.__secondaryTextColor.set(i12);
    }

    get hoveringColor() {
        return this.__hoveringColor.get();
    }

    set hoveringColor(h12) {
        this.__hoveringColor.set(h12);
    }

    get activedColor() {
        return this.__activedColor.get();
    }

    set activedColor(g12) {
        this.__activedColor.set(g12);
    }

    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }

    set parentCanFocus(f12) {
        this.__parentCanFocus.set(f12);
    }

    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }

    set parentCanTouch(e12) {
        this.__parentCanTouch.set(e12);
    }

    get parentIsHover() {
        return this.__parentIsHover.get();
    }

    set parentIsHover(d12) {
        this.__parentIsHover.set(d12);
    }

    get parentCanHover() {
        return this.__parentCanHover.get();
    }

    set parentCanHover(c12) {
        this.__parentCanHover.set(c12);
    }

    get parentIsActive() {
        return this.__parentIsActive.get();
    }

    set parentIsActive(b12) {
        this.__parentIsActive.set(b12);
    }

    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }

    set parentFrontColor(a12) {
        this.__parentFrontColor.set(a12);
    }

    get parentDirection() {
        return this.__parentDirection.get();
    }

    set parentDirection(z11) {
        this.__parentDirection.set(z11);
    }

    get rowSpace() {
        return this.__rowSpace.get();
    }

    set rowSpace(y11) {
        this.__rowSpace.set(y11);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(x11) {
        this.__isFocus.set(x11);
    }

    get secondaryTextSize() {
        return this.__secondaryTextSize.get();
    }

    set secondaryTextSize(w11) {
        this.__secondaryTextSize.set(w11);
    }

    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }

    set secondaryTextColors(v11) {
        this.__secondaryTextColors.set(v11);
    }

    get iconColor() {
        return this.__iconColor.get();
    }

    set iconColor(u11) {
        this.__iconColor.set(u11);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(t11) {
        this.__isChecked.set(t11);
    }

    onWillApplyTheme(s11) {
        this.secondaryTextColor = s11.colors.fontSecondary;
        this.hoveringColor = s11.colors.interactiveHover;
        this.activedColor = s11.colors.interactiveActive;
    }

    onFocusChange() {
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus) {
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
            this.switchState = IS_SUPPORT_SUBCOMPONENT_EVENT ? this.switch.isCheck : this.isChecked;
        }
        if (this.radio != null) {
            this.radioState = IS_SUPPORT_SUBCOMPONENT_EVENT ? this.radio.isCheck : this.isChecked;
        }
        if (this.checkBox != null) {
            this.checkBoxState = IS_SUPPORT_SUBCOMPONENT_EVENT ? this.checkBox.isCheck : this.isChecked;
        }
        if ((this.button == null && this.image == null && this.symbolStyle == null && this.text != null) &&
            ((this.icon != null) || (this.icon == null && this.arrow != null))) {
            this.rowSpace = SPECICAL_ROW_SPACE;
        } else {
            this.rowSpace = DEFAULT_ROW_SPACE;
        }
    }

    getUnselectedColor() {
        if (IS_SUPPORT_SUBCOMPONENT_EVENT) {
            return DEFUALT_RADIO_CHECKBOX_BORDER_COLOR;
        }
        return this.isFocus ? OPERATE_ITEM_COLOR : DEFUALT_RADIO_CHECKBOX_BORDER_COLOR;
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

    createButton(f11 = null) {
        this.observeComponentCreation2((n11, o11) => {
            Button.createWithChild();
            Button.padding({ top: 0, bottom: 0 });
            Button.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Button.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
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
            Button.onHover((r11) => {
                this.parentCanHover = false;
                if (r11 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!r11) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.accessibilityLevel(this.button?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Button.accessibilityText(getAccessibilityText(this.button?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(this.button?.accessibilityDescription ?? ''));
        }, Button);
        this.observeComponentCreation2((l11, m11) => {
            Row.create();
            Row.padding({
                left: TEXT_SAFE_MARGIN,
                right: TEXT_SAFE_MARGIN
            });
        }, Row);
        this.observeComponentCreation2((j11, k11) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }

    createIcon(e10, f10 = null) {
        this.observeComponentCreation2((a11, b11) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
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
            Button.onHover((e11) => {
                this.parentCanHover = false;
                if (e11 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!e11) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(e10.icon?.action);
            Button.accessibilityLevel(e10.icon?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Button.accessibilityText(getAccessibilityText(e10.icon?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(e10.icon?.accessibilityDescription ?? ''));
            Button.flexShrink(0);
        }, Button);
        this.observeComponentCreation2((i10, j10) => {
            If.create();
            if (e10.icon?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y10, z10) => {
                        SymbolGlyph.create();
                        SymbolGlyph.attributeModifier.bind(this)(e10.icon?.symbolStyle);
                        SymbolGlyph.fontSize(OPERATEITEM_ICONLIKE_SIZE);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.draggable(false);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((m10, n10) => {
                        If.create();
                        if (Util.isSymbolResource(e10.icon?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((u10, v10) => {
                                    SymbolGlyph.create(e10.icon?.value);
                                    SymbolGlyph.fontSize(OPERATEITEM_ICONLIKE_SIZE);
                                    SymbolGlyph.fontColor([this.iconColor]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((q10, r10) => {
                                    Image.create(e10.icon?.value);
                                    Image.height(OPERATEITEM_ICONLIKE_SIZE);
                                    Image.width(OPERATEITEM_ICONLIKE_SIZE);
                                    Image.focusable(true);
                                    Image.fillColor(ObservedObject.GetRawObject(this.iconColor));
                                    Image.draggable(false);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }

    createImage(s9 = null) {
        this.observeComponentCreation2((u9, v9) => {
            If.create();
            if (Util.isSymbolResource(ObservedObject.GetRawObject(this.image))) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c10, d10) => {
                        SymbolGlyph.create(this.image);
                        SymbolGlyph.fontSize(OPERATEITEM_IMAGE_SIZE);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((y9, z9) => {
                        Image.create(this.image);
                        Image.height(OPERATEITEM_IMAGE_SIZE);
                        Image.width(OPERATEITEM_IMAGE_SIZE);
                        Image.draggable(false);
                        Image.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
                    }, Image);
                });
            }
        }, If);
        If.pop();
    }

    createSymbol(o9 = null) {
        this.observeComponentCreation2((q9, r9) => {
            SymbolGlyph.create();
            SymbolGlyph.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.symbolStyle));
            SymbolGlyph.fontSize(OPERATEITEM_IMAGE_SIZE);
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(new SymbolEffect(), false);
            SymbolGlyph.draggable(false);
            SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
        }, SymbolGlyph);
    }

    createText(k9 = null) {
        this.observeComponentCreation2((m9, n9) => {
            Text.create(this.text);
            Text.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Text.fontSize(ObservedObject.GetRawObject(this.secondaryTextSize));
            Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColors));
            Text.textOverflow({
                overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.MARQUEE :
                TextOverflow.None
            });
            Text.marqueeOptions({
                start: this.isFocus || this.parentIsHover,
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
        }, Text);
        Text.pop();
    }

    createArrow(k8 = null) {
        this.observeComponentCreation2((f9, g9) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Button.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ?
                (this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent) : HitTestMode.None);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.stateEffect(this.arrow?.action !== undefined);
            Button.hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None);
            Button.onHover((j9) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (j9 && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentCanHover = false;
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                } else {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
            Button.accessibilityLevel(this.arrow?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Button.accessibilityText(getAccessibilityText(this.arrow?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(this.arrow?.accessibilityDescription ?? ''));
        }, Button);
        this.observeComponentCreation2((n8, o8) => {
            If.create();
            if (this.arrow?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d9, e9) => {
                        SymbolGlyph.create();
                        SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                        SymbolGlyph.fontSize(OPERATEITEM_ARROW_WIDTH);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.draggable(false);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((r8, s8) => {
                        If.create();
                        if (Util.isSymbolResource(this.arrow?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((z8, a9) => {
                                    SymbolGlyph.create(this.arrow?.value);
                                    SymbolGlyph.fontSize(OPERATEITEM_ARROW_WIDTH);
                                    SymbolGlyph.fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? {
                                        "id": -1,
                                        "type": 10001,
                                        params: ['sys.color.ohos_id_color_fourth'],
                                        "bundleName": "__harDefaultBundleName__",
                                        "moduleName": "__harDefaultModuleName__"
                                    } : this.iconColor]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((v8, w8) => {
                                    Image.create(this.arrow?.value);
                                    Image.height(OPERATEITEM_ICONLIKE_SIZE);
                                    Image.width(OPERATEITEM_ARROW_WIDTH);
                                    Image.focusable(true);
                                    Image.fillColor(IS_SUPPORT_SUBCOMPONENT_EVENT ? {
                                        "id": -1,
                                        "type": 10001,
                                        params: ['sys.color.ohos_id_color_fourth'],
                                        "bundleName": "__harDefaultBundleName__",
                                        "moduleName": "__harDefaultModuleName__"
                                    } : this.iconColor);
                                    Image.draggable(false);
                                    Image.matchTextDirection(true);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }

    createRadio(b8 = null) {
        this.observeComponentCreation2((d8, e8) => {
            Radio.create({ value: '', group: '' });
            Radio.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Radio.checked(this.radioState);
            Radio.radioStyle({
                uncheckedBorderColor: this.getUnselectedColor()
            });
            Radio.backgroundColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Radio.borderRadius(OPERATE_ITEM_RADIUS);
            Radio.onChange((j8) => {
                this.radioState = j8;
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.isChecked = j8;
                }
                if (this.radio?.onChange) {
                    this.radio?.onChange(j8);
                }
            });
            Radio.height(OPERATEITEM_ICONLIKE_SIZE);
            Radio.width(OPERATEITEM_ICONLIKE_SIZE);
            Radio.padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE);
            Radio.onFocus(() => {
                this.parentCanFocus = false;
            });
            Radio.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Radio.flexShrink(0);
            Radio.onHover((i8) => {
                this.parentCanHover = false;
                if (i8 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!i8) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Radio.accessibilityLevel(this.radio?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Radio.accessibilityText(getAccessibilityText(this.radio?.accessibilityText ?? ''));
            Radio.accessibilityDescription(getAccessibilityText(this.radio?.accessibilityDescription ?? ''));
        }, Radio);
    }

    createCheckBox(s7 = null) {
        this.observeComponentCreation2((u7, v7) => {
            Checkbox.create();
            Checkbox.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Checkbox.unselectedColor(this.getUnselectedColor());
            Checkbox.backgroundColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Checkbox.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange((a8) => {
                this.checkBoxState = a8;
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.isChecked = a8;
                }
                if (this.checkBox?.onChange) {
                    this.checkBox?.onChange(a8);
                }
            });
            Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.width(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE);
            Checkbox.onFocus(() => {
                this.parentCanFocus = false;
            });
            Checkbox.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Checkbox.flexShrink(0);
            Checkbox.onHover((z7) => {
                this.parentCanHover = false;
                if (z7 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!z7) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Checkbox.accessibilityLevel(this.checkBox?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Checkbox.accessibilityText(getAccessibilityText(this.checkBox?.accessibilityText ?? ''));
            Checkbox.accessibilityDescription(getAccessibilityText(this.checkBox?.accessibilityDescription ?? ''));
        }, Checkbox);
        Checkbox.pop();
    }

    createSwitch(f7 = null) {
        this.observeComponentCreation2((n7, o7) => {
            Row.create();
            Row.margin({ end: LengthMetrics.vp(SWITCH_PADDING) });
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onHover((r7) => {
                this.parentCanHover = false;
                if (r7 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!r7) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((i7, j7) => {
            Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
            Toggle.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Toggle.backgroundColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Toggle.switchPointColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus && !this.switchState ?
                OPERATE_ITEM_COLOR : UNUSUAL);
            Toggle.onChange((m7) => {
                this.switchState = m7;
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.isChecked = m7;
                }
                if (this.switch?.onChange) {
                    this.switch?.onChange(m7);
                }
            });
            Toggle.onClick(() => {
                this.switchState = !this.switchState;
            });
            Toggle.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Toggle.accessibilityLevel(this.switch?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Toggle.accessibilityText(getAccessibilityText(this.switch?.accessibilityText ?? ''));
            Toggle.accessibilityDescription(getAccessibilityText(this.switch?.accessibilityDescription ?? ''));
        }, Toggle);
        Toggle.pop();
        Row.pop();
    }

    createTextArrow(v4 = null) {
        this.observeComponentCreation2((a7, b7) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ?
                (this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent) : HitTestMode.None);
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
            Button.onHover((e7) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (e7 && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentCanHover = false;
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                } else {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
            Button.accessibilityLevel(this.arrow?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Button.accessibilityText(`${this.text} ${getAccessibilityText(this.arrow?.accessibilityText ?? '')}`);
            Button.accessibilityDescription(getAccessibilityText(this.arrow?.accessibilityDescription ?? ''));
        }, Button);
        this.observeComponentCreation2((y4, z4) => {
            If.create();
            if (this.parentDirection === FlexDirection.Column) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y6, z6) => {
                        Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
                        Flex.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Flex);
                    this.observeComponentCreation2((w6, x6) => {
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
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((e6, f6) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((u6, v6) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                                    SymbolGlyph.fontSize(OPERATEITEM_ARROW_WIDTH);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((i6, j6) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((q6, r6) => {
                                                SymbolGlyph.create(this.arrow?.value);
                                                SymbolGlyph.fontSize(OPERATEITEM_ARROW_WIDTH);
                                                SymbolGlyph.fontColor([{
                                                    "id": -1,
                                                    "type": 10001,
                                                    params: ['sys.color.ohos_id_color_fourth'],
                                                    "bundleName": "__harDefaultBundleName__",
                                                    "moduleName": "__harDefaultModuleName__"
                                                }]);
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((m6, n6) => {
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
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    Flex.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((y5, z5) => {
                        Row.create({ space: SPECICAL_ROW_SPACE });
                        Row.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Row);
                    this.observeComponentCreation2((w5, x5) => {
                        Text.create(this.text);
                        Text.fontSize(ObservedObject.GetRawObject(this.secondaryTextSize));
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColors));
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.MARQUEE :
                            TextOverflow.None
                        });
                        Text.marqueeOptions({
                            start: this.isFocus || this.parentIsHover,
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
                            maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH + OPERATEITEM_ARROW_MARGIN_WIDTH}vp)`
                        });
                        Text.margin({ right: OPERATEITEM_ARROW_MARGIN_WIDTH });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((e5, f5) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((u5, v5) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                                    SymbolGlyph.fontSize(OPERATEITEM_ARROW_WIDTH);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((i5, j5) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((q5, r5) => {
                                                SymbolGlyph.create(this.arrow?.value);
                                                SymbolGlyph.fontSize(OPERATEITEM_ARROW_WIDTH);
                                                SymbolGlyph.fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? {
                                                    "id": -1,
                                                    "type": 10001,
                                                    params: ['sys.color.icon_fourth'],
                                                    "bundleName": "__harDefaultBundleName__",
                                                    "moduleName": "__harDefaultModuleName__"
                                                } : this.iconColor]);
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((m5, n5) => {
                                                Image.create(this.arrow?.value);
                                                Image.height(OPERATEITEM_ICONLIKE_SIZE);
                                                Image.width(OPERATEITEM_ARROW_WIDTH);
                                                Image.fillColor(IS_SUPPORT_SUBCOMPONENT_EVENT ? {
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
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }

    getFlexOptions() {
        let u4 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            u4.justifyContent = FlexAlign.SpaceBetween;
        } else {
            u4.space = { main: LengthMetrics.vp(this.rowSpace) };
            u4.justifyContent = FlexAlign.End;
        }
        return u4;
    }

    initialRender() {
        this.observeComponentCreation2((s4, t4) => {
            Flex.create(this.getFlexOptions());
            Flex.width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth);
        }, Flex);
        this.observeComponentCreation2((z3, a4) => {
            If.create();
            if (this.button != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.createButton.bind(this)();
                });
            } else if (this.symbolStyle != null) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.createSymbol.bind(this)();
                });
            } else if (this.image != null) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.createImage.bind(this)();
                });
            } else if (this.icon != null && this.text != null) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.createText.bind(this)();
                    this.createIcon.bind(this)(makeBuilderParameterProxy("createIcon",
                        { icon: () => (this["__icon"] ? this["__icon"] : this["icon"]) }));
                });
            } else if (this.arrow != null && this.text == null) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.createArrow.bind(this)();
                });
            } else if (this.arrow != null && this.text != null) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.createTextArrow.bind(this)();
                });
            } else if (this.text != null) {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.createText.bind(this)();
                });
            } else if (this.radio != null) {
                this.ifElseBranchUpdateFunction(7, () => {
                    this.createRadio.bind(this)();
                });
            } else if (this.checkBox != null) {
                this.ifElseBranchUpdateFunction(8, () => {
                    this.createCheckBox.bind(this)();
                });
            } else if (this.switch != null) {
                this.ifElseBranchUpdateFunction(9, () => {
                    this.createSwitch.bind(this)();
                });
            } else if (this.icon != null) {
                this.ifElseBranchUpdateFunction(10, () => {
                    this.createIcon.bind(this)(makeBuilderParameterProxy("createIcon",
                        { icon: () => (this["__icon"] ? this["__icon"] : this["icon"]) }));
                    this.observeComponentCreation2((e4, f4) => {
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
                this.ifElseBranchUpdateFunction(11, () => {
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

function getAccessibilityText(s3) {
    try {
        let w3 = '';
        if (typeof s3 === 'string') {
            w3 = s3;
        } else {
            w3 = getContext().resourceManager.getStringSync(s3);
        }
        return w3;
    } catch (t3) {
        let u3 = t3.code;
        let v3 = t3.message;
        hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${u3}, message: ${v3}`);
        return '';
    }
}

export class ComposeListItem extends ViewPU {
    constructor(k3, l3, m3, n3 = -1, o3 = undefined, p3) {
        super(k3, m3, n3, p3);
        if (typeof o3 === "function") {
            this.paramsGenerator_ = o3;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(l3.contentItem, this, "contentItem");
        this.__operateItem = new SynchedPropertyObjectOneWayPU(l3.operateItem, this, "operateItem");
        this.__frontColor = new ObservedPropertyObjectPU(NORMAL_BG_COLOR, this, "frontColor");
        this.__borderSize = new ObservedPropertySimplePU(0, this, "borderSize");
        this.__canFocus = new ObservedPropertySimplePU(false, this, "canFocus");
        this.__canTouch = new ObservedPropertySimplePU(true, this, "canTouch");
        this.__canHover = new ObservedPropertySimplePU(true, this, "canHover");
        this.__isHover = new ObservedPropertySimplePU(false, this, "isHover");
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
        this.isFollowingSystemFontScale = 1;
        this.maxFontScale = 1;
        this.callbackId = undefined;
        this.__accessibilityTextBuilder = new ObservedPropertySimplePU('', this, "accessibilityTextBuilder");
        this.__isFocus = new ObservedPropertySimplePU(false, this, "isFocus");
        this.__isChecked = new ObservedPropertySimplePU(false, this, "isChecked");
        this.__isWrapText = new ObservedPropertySimplePU(false, this, "isWrapText");
        this.envCallback = {
            onConfigurationUpdated: (r3) => {
                this.fontSizeScale = this.decideFontSizeScale();
            },
            onMemoryLevel: (q3) => {
            }
        };
        this.setInitiallyProvidedValue(l3);
        this.declareWatch("contentItem", this.onPropChange);
        this.declareWatch("operateItem", this.onPropChange);
        this.declareWatch("fontSizeScale", this.onFontSizeScaleChange);
        this.declareWatch("isWrapText", this.onWrapChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(j3) {
        if (j3.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (j3.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (j3.frontColor !== undefined) {
            this.frontColor = j3.frontColor;
        }
        if (j3.borderSize !== undefined) {
            this.borderSize = j3.borderSize;
        }
        if (j3.canFocus !== undefined) {
            this.canFocus = j3.canFocus;
        }
        if (j3.canTouch !== undefined) {
            this.canTouch = j3.canTouch;
        }
        if (j3.canHover !== undefined) {
            this.canHover = j3.canHover;
        }
        if (j3.isHover !== undefined) {
            this.isHover = j3.isHover;
        }
        if (j3.itemHeight !== undefined) {
            this.itemHeight = j3.itemHeight;
        }
        if (j3.isActive !== undefined) {
            this.isActive = j3.isActive;
        }
        if (j3.hoveringColor !== undefined) {
            this.hoveringColor = j3.hoveringColor;
        }
        if (j3.touchDownColor !== undefined) {
            this.touchDownColor = j3.touchDownColor;
        }
        if (j3.activedColor !== undefined) {
            this.activedColor = j3.activedColor;
        }
        if (j3.focusOutlineColor !== undefined) {
            this.focusOutlineColor = j3.focusOutlineColor;
        }
        if (j3.fontSizeScale !== undefined) {
            this.fontSizeScale = j3.fontSizeScale;
        }
        if (j3.containerDirection !== undefined) {
            this.containerDirection = j3.containerDirection;
        }
        if (j3.contentItemDirection !== undefined) {
            this.contentItemDirection = j3.contentItemDirection;
        }
        if (j3.containerPadding !== undefined) {
            this.containerPadding = j3.containerPadding;
        }
        if (j3.textArrowLeftSafeOffset !== undefined) {
            this.textArrowLeftSafeOffset = j3.textArrowLeftSafeOffset;
        }
        if (j3.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = j3.isFollowingSystemFontScale;
        }
        if (j3.maxFontScale !== undefined) {
            this.maxFontScale = j3.maxFontScale;
        }
        if (j3.callbackId !== undefined) {
            this.callbackId = j3.callbackId;
        }
        if (j3.accessibilityTextBuilder !== undefined) {
            this.accessibilityTextBuilder = j3.accessibilityTextBuilder;
        }
        if (j3.isFocus !== undefined) {
            this.isFocus = j3.isFocus;
        }
        if (j3.isChecked !== undefined) {
            this.isChecked = j3.isChecked;
        }
        if (j3.isWrapText !== undefined) {
            this.isWrapText = j3.isWrapText;
        }
        if (j3.envCallback !== undefined) {
            this.envCallback = j3.envCallback;
        }
    }

    updateStateVars(i3) {
        this.__contentItem.reset(i3.contentItem);
        this.__operateItem.reset(i3.operateItem);
    }

    purgeVariableDependenciesOnElmtId(h3) {
        this.__contentItem.purgeDependencyOnElmtId(h3);
        this.__operateItem.purgeDependencyOnElmtId(h3);
        this.__frontColor.purgeDependencyOnElmtId(h3);
        this.__borderSize.purgeDependencyOnElmtId(h3);
        this.__canFocus.purgeDependencyOnElmtId(h3);
        this.__canTouch.purgeDependencyOnElmtId(h3);
        this.__canHover.purgeDependencyOnElmtId(h3);
        this.__isHover.purgeDependencyOnElmtId(h3);
        this.__itemHeight.purgeDependencyOnElmtId(h3);
        this.__isActive.purgeDependencyOnElmtId(h3);
        this.__hoveringColor.purgeDependencyOnElmtId(h3);
        this.__touchDownColor.purgeDependencyOnElmtId(h3);
        this.__activedColor.purgeDependencyOnElmtId(h3);
        this.__focusOutlineColor.purgeDependencyOnElmtId(h3);
        this.__fontSizeScale.purgeDependencyOnElmtId(h3);
        this.__containerDirection.purgeDependencyOnElmtId(h3);
        this.__contentItemDirection.purgeDependencyOnElmtId(h3);
        this.__containerPadding.purgeDependencyOnElmtId(h3);
        this.__textArrowLeftSafeOffset.purgeDependencyOnElmtId(h3);
        this.__accessibilityTextBuilder.purgeDependencyOnElmtId(h3);
        this.__isFocus.purgeDependencyOnElmtId(h3);
        this.__isChecked.purgeDependencyOnElmtId(h3);
        this.__isWrapText.purgeDependencyOnElmtId(h3);
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

    set contentItem(g3) {
        this.__contentItem.set(g3);
    }

    get operateItem() {
        return this.__operateItem.get();
    }

    set operateItem(f3) {
        this.__operateItem.set(f3);
    }

    get frontColor() {
        return this.__frontColor.get();
    }

    set frontColor(e3) {
        this.__frontColor.set(e3);
    }

    get borderSize() {
        return this.__borderSize.get();
    }

    set borderSize(d3) {
        this.__borderSize.set(d3);
    }

    get canFocus() {
        return this.__canFocus.get();
    }

    set canFocus(c3) {
        this.__canFocus.set(c3);
    }

    get canTouch() {
        return this.__canTouch.get();
    }

    set canTouch(b3) {
        this.__canTouch.set(b3);
    }

    get canHover() {
        return this.__canHover.get();
    }

    set canHover(a3) {
        this.__canHover.set(a3);
    }

    get isHover() {
        return this.__isHover.get();
    }

    set isHover(z2) {
        this.__isHover.set(z2);
    }

    get itemHeight() {
        return this.__itemHeight.get();
    }

    set itemHeight(y2) {
        this.__itemHeight.set(y2);
    }

    get isActive() {
        return this.__isActive.get();
    }

    set isActive(x2) {
        this.__isActive.set(x2);
    }

    get hoveringColor() {
        return this.__hoveringColor.get();
    }

    set hoveringColor(w2) {
        this.__hoveringColor.set(w2);
    }

    get touchDownColor() {
        return this.__touchDownColor.get();
    }

    set touchDownColor(v2) {
        this.__touchDownColor.set(v2);
    }

    get activedColor() {
        return this.__activedColor.get();
    }

    set activedColor(u2) {
        this.__activedColor.set(u2);
    }

    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }

    set focusOutlineColor(t2) {
        this.__focusOutlineColor.set(t2);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(s2) {
        this.__fontSizeScale.set(s2);
    }

    get containerDirection() {
        return this.__containerDirection.get();
    }

    set containerDirection(r2) {
        this.__containerDirection.set(r2);
    }

    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }

    set contentItemDirection(q2) {
        this.__contentItemDirection.set(q2);
    }

    get containerPadding() {
        return this.__containerPadding.get();
    }

    set containerPadding(p2) {
        this.__containerPadding.set(p2);
    }

    get textArrowLeftSafeOffset() {
        return this.__textArrowLeftSafeOffset.get();
    }

    set textArrowLeftSafeOffset(o2) {
        this.__textArrowLeftSafeOffset.set(o2);
    }

    get accessibilityTextBuilder() {
        return this.__accessibilityTextBuilder.get();
    }

    set accessibilityTextBuilder(n2) {
        this.__accessibilityTextBuilder.set(n2);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(m2) {
        this.__isFocus.set(m2);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(l2) {
        this.__isChecked.set(l2);
    }

    get isWrapText() {
        return this.__isWrapText.get();
    }

    set isWrapText(k2) {
        this.__isWrapText.set(k2);
    }

    onWillApplyTheme(j2) {
        this.hoveringColor = j2.colors.interactiveHover;
        this.touchDownColor = j2.colors.interactivePressed;
        this.activedColor = j2.colors.interactiveActive;
        this.focusOutlineColor = j2.colors.interactiveFocus;
    }

    onWrapChange() {
        this.containerPadding = this.getPadding();
    }

    onPropChange() {
        this.containerDirection = this.decideContainerDirection();
        this.contentItemDirection = this.decideContentItemDirection();
        if (this.contentItem === undefined) {
            if (this.operateItem?.image !== undefined ||
                this.operateItem?.symbolStyle !== undefined ||
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
                ItemHeight.SECOND_HEIGHT :
                    (LengthMetrics.resource({
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
                this.itemHeight = APPICON_ITEMLENGTH;
            }
        } else {
            this.itemHeight = ItemHeight.FIFTH_HEIGHT;
        }
        if (ICON_SIZE_MAP.get(this.contentItem?.iconStyle) >= this.itemHeight) {
            this.itemHeight = ICON_SIZE_MAP.get(this.contentItem?.iconStyle) + SAFE_LIST_PADDING;
        }
        if (this.operateItem?.arrow && this.operateItem?.text && this.operateItem?.arrow?.action) {
            this.accessibilityTextBuilder = `
        ${getAccessibilityText(this.contentItem?.primaryText ?? '')}
        ${getAccessibilityText(this.contentItem?.secondaryText ?? '')}
        ${getAccessibilityText(this.contentItem?.description ?? '')}
      `;
        } else {
            this.accessibilityTextBuilder = `
        ${getAccessibilityText(this.contentItem?.primaryText ?? '')}
        ${getAccessibilityText(this.contentItem?.secondaryText ?? '')}
        ${getAccessibilityText(this.contentItem?.description ?? '')}
        ${getAccessibilityText(this.operateItem?.text ?? '')}
      `;
        }
    }

    aboutToAppear() {
        this.fontSizeScale = this.decideFontSizeScale();
        this.onPropChange();
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        } catch (g2) {
            let h2 = g2.code;
            let i2 = g2.message;
            hilog.error(0x3900, 'Ace', `ComposeListItem Faild to get environment param error: ${h2}, ${i2}`);
        }
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
            this.onFontSizeScaleChange();
        }
    }

    aboutToDisappear() {
        if (this.callbackId) {
            this.getUIContext()
                .getHostContext()
            ?.getApplicationContext()
            ?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
    }

    calculatedRightWidth() {
        if (this.operateItem?.text || this.operateItem?.button) {
            return RIGHT_PART_WIDTH;
        }
        if (this.operateItem?.switch) {
            return RIGHT_ONLY_SWITCH_WIDTH;
        } else if (this.operateItem?.checkbox) {
            return RIGHT_ONLY_CHECKBOX_WIDTH;
        } else if (this.operateItem?.radio) {
            return RIGHT_ONLY_RADIO_WIDTH;
        } else if (this.operateItem?.icon) {
            if (this.operateItem?.subIcon) {
                return RIGHT_ICON_SUB_ICON_WIDTH;
            }
            return RIGHT_ONLY_ICON_WIDTH;
        } else if (this.operateItem?.symbolStyle) {
            return RIGHT_ONLY_IMAGE_WIDTH;
        } else if (this.operateItem?.image) {
            return RIGHT_ONLY_IMAGE_WIDTH;
        } else if (this.operateItem?.arrow) {
            return RIGHT_ONLY_ARROW_WIDTH;
        }
        return RIGHT_CONTENT_NULL_RIGHTWIDTH;
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
        } else if (this.operateItem?.symbolStyle) {
            return FlexDirection.Row;
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
        let f2 = ICON_SIZE_MAP.get(this.contentItem?.iconStyle);
        if (this.contentItem?.icon && f2 && f2 <= HEADSCULPTURE_SIZE) {
            return LengthMetrics.vp(f2 + NORMAL_ITEM_ROW_SPACE + LISTITEM_PADDING - this.textArrowLeftSafeOffset);
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
        let c2 = LengthMetrics.resource(ITEM_PADDING).value;
        let d2 = c2 > LISTITEM_PADDING;
        let e2 = d2 ? c2 - LISTITEM_PADDING : 0;
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isWrapText) {
            return {
                top: c2,
                bottom: c2,
                left: e2,
                right: e2
            };
        } else {
            return { left: e2, right: e2 };
        }
    }

    initialRender() {
        this.observeComponentCreation2((x1, y1) => {
            Stack.create();
            Stack.width('100%');
            Stack.accessibilityGroup(true);
            Stack.accessibilityText(this.accessibilityTextBuilder);
            Stack.onFocus(() => {
                this.isFocus = true;
                this.frontColor = FOCUSED_BG_COLOR;
            });
            Stack.onBlur(() => {
                this.isFocus = false;
                this.frontColor = NORMAL_BG_COLOR;
            });
            Stack.borderRadius({
                "id": -1,
                "type": 10002,
                params: ['sys.float.composeListItem_radius'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            });
            Stack.onClick(IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : () => {
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
            });
            Stack.scale({
                x: this.isFocus ? FOCUSED_ITEM_SCALE : RECOVER_ITEM_SCALE,
                y: this.isFocus ? FOCUSED_ITEM_SCALE : RECOVER_ITEM_SCALE
            });
            Stack.shadow(this.isFocus ? FOCUSED_SHADOW : NORMAL_SHADOW);
            Stack.margin({
                left: STACK_PADDING,
                right: STACK_PADDING
            });
        }, Stack);
        this.observeComponentCreation2((r1, s1) => {
            Flex.create(this.getFlexOptions());
            Flex.height(this.containerDirection === FlexDirection.Column ? 'auto' : undefined);
            Flex.constraintSize({
                minHeight: this.itemHeight
            });
            Flex.focusable(IS_SUPPORT_SUBCOMPONENT_EVENT);
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
            Flex.onHover((w1) => {
                if (this.isFocus && !IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.isHover = false;
                    return;
                }
                this.isHover = w1;
                if (this.canHover) {
                    this.frontColor = w1 ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.frontColor = w1 ? this.hoveringColor : NORMAL_BG_COLOR;
                }
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
            ViewStackProcessor.visualState("pressed");
            Flex.backgroundColor(ObservedObject.GetRawObject(this.touchDownColor));
            ViewStackProcessor.visualState();
            Flex.padding(ObservedObject.GetRawObject(this.containerPadding));
        }, Flex);
        this.observeComponentCreation2((g1, h1) => {
            If.create();
            if (this.contentItem === null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((l1, m1) => {
                            if (m1) {
                                let n1 = new ContentItemStruct(this, {
                                    isWrapText: this.__isWrapText
                                }, undefined, l1, () => {
                                }, {
                                    page: "library/src/main/ets/components/composelistitem.ets",
                                    line: 1343,
                                    col: 11
                                });
                                ViewPU.create(n1);
                                let c = () => {
                                    return {
                                        isWrapText: this.isWrapText
                                    };
                                };
                                n1.paramsGenerator_ = c;
                            } else {
                                this.updateStateVarsOfChildByElmtId(l1, {});
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
        this.observeComponentCreation2((v, w) => {
            If.create();
            if (this.contentItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((a1, b1) => {
                            if (b1) {
                                let c1 = new ContentItemStruct(this, {
                                    icon: this.contentItem?.icon,
                                    symbolStyle: this.contentItem?.symbolStyle,
                                    iconStyle: this.contentItem?.iconStyle,
                                    primaryText: this.contentItem?.primaryText,
                                    secondaryText: this.contentItem?.secondaryText,
                                    description: this.contentItem?.description,
                                    fontSizeScale: this.fontSizeScale,
                                    parentDirection: this.containerDirection,
                                    itemDirection: this.contentItemDirection,
                                    isFocus: this.isFocus,
                                    itemHeight: this.itemHeight,
                                    isWrapText: this.__isWrapText
                                }, undefined, a1, () => {
                                }, {
                                    page: "library/src/main/ets/components/composelistitem.ets",
                                    line: 1348,
                                    col: 11
                                });
                                ViewPU.create(c1);
                                let b = () => {
                                    return {
                                        icon: this.contentItem?.icon,
                                        symbolStyle: this.contentItem?.symbolStyle,
                                        iconStyle: this.contentItem?.iconStyle,
                                        primaryText: this.contentItem?.primaryText,
                                        secondaryText: this.contentItem?.secondaryText,
                                        description: this.contentItem?.description,
                                        fontSizeScale: this.fontSizeScale,
                                        parentDirection: this.containerDirection,
                                        itemDirection: this.contentItemDirection,
                                        isFocus: this.isFocus,
                                        itemHeight: this.itemHeight,
                                        isWrapText: this.isWrapText
                                    };
                                };
                                c1.paramsGenerator_ = b;
                            } else {
                                this.updateStateVarsOfChildByElmtId(a1, {
                                    icon: this.contentItem?.icon,
                                    symbolStyle: this.contentItem?.symbolStyle,
                                    iconStyle: this.contentItem?.iconStyle,
                                    primaryText: this.contentItem?.primaryText,
                                    secondaryText: this.contentItem?.secondaryText,
                                    description: this.contentItem?.description,
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
        this.observeComponentCreation2((f, g) => {
            If.create();
            if (this.operateItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r, s) => {
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
                        this.observeComponentCreation2((l, m) => {
                            if (m) {
                                let n = new OperateItemStruct(this, {
                                    icon: this.operateItem?.icon,
                                    subIcon: this.operateItem?.subIcon,
                                    button: this.operateItem?.button,
                                    switch: this.operateItem?.switch,
                                    checkBox: this.operateItem?.checkbox,
                                    radio: this.operateItem?.radio,
                                    image: this.operateItem?.image,
                                    symbolStyle: this.operateItem?.symbolStyle,
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
                                }, undefined, l, () => {
                                }, {
                                    page: "library/src/main/ets/components/composelistitem.ets",
                                    line: 1364,
                                    col: 11
                                });
                                ViewPU.create(n);
                                let a = () => {
                                    return {
                                        icon: this.operateItem?.icon,
                                        subIcon: this.operateItem?.subIcon,
                                        button: this.operateItem?.button,
                                        switch: this.operateItem?.switch,
                                        checkBox: this.operateItem?.checkbox,
                                        radio: this.operateItem?.radio,
                                        image: this.operateItem?.image,
                                        symbolStyle: this.operateItem?.symbolStyle,
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
                                n.paramsGenerator_ = a;
                            } else {
                                this.updateStateVarsOfChildByElmtId(l, {
                                    icon: this.operateItem?.icon,
                                    subIcon: this.operateItem?.subIcon,
                                    button: this.operateItem?.button,
                                    switch: this.operateItem?.switch,
                                    checkBox: this.operateItem?.checkbox,
                                    radio: this.operateItem?.radio,
                                    image: this.operateItem?.image,
                                    symbolStyle: this.operateItem?.symbolStyle,
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

export default {
    IconType, ComposeListItem
};