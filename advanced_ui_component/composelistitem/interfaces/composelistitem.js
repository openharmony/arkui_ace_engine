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
export var IconType;
(function (a14) {
    a14[a14["BADGE"] = 1] = "BADGE";
    a14[a14["NORMAL_ICON"] = 2] = "NORMAL_ICON";
    a14[a14["SYSTEM_ICON"] = 3] = "SYSTEM_ICON";
    a14[a14["HEAD_SCULPTURE"] = 4] = "HEAD_SCULPTURE";
    a14[a14["APP_ICON"] = 5] = "APP_ICON";
    a14[a14["PREVIEW"] = 6] = "PREVIEW";
    a14[a14["LONGITUDINAL"] = 7] = "LONGITUDINAL";
    a14[a14["VERTICAL"] = 8] = "VERTICAL";
})(IconType || (IconType = {}));
var ItemHeight;
(function (z13) {
    z13[z13["FIRST_HEIGHT"] = 48] = "FIRST_HEIGHT";
    z13[z13["SECOND_HEIGHT"] = 56] = "SECOND_HEIGHT";
    z13[z13["THIRD_HEIGHT"] = 64] = "THIRD_HEIGHT";
    z13[z13["FOURTH_HEIGHT"] = 72] = "FOURTH_HEIGHT";
    z13[z13["FIFTH_HEIGHT"] = 96] = "FIFTH_HEIGHT";
})(ItemHeight || (ItemHeight = {}));
var FontSizeScaleLevel;
(function (y13) {
    y13[y13["LEVEL1"] = 1.75] = "LEVEL1";
    y13[y13["LEVEL2"] = 2] = "LEVEL2";
    y13[y13["LEVEL3"] = 3.2] = "LEVEL3";
})(FontSizeScaleLevel || (FontSizeScaleLevel = {}));
const TEXT_MAX_LINE = 1;
const ITEM_BORDER_SHOWN = 2;
const TEXT_COLUMN_SPACE = 4;
const TEXT_SAFE_MARGIN = 8;
const LISTITEM_PADDING = 6;
const SWITCH_PADDING = 4;
const STACK_PADDING = 12;
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
const OPERATEITEM_ARROW_WIDTH = 12;
const OPERATEITEM_ICON_CLICKABLE_SIZE = 40;
const OPERATEITEM_IMAGE_SIZE = 48;
const HOVERING_COLOR = '#0d000000';
const ACTIVED_COLOR = '#1a0a59f7';
const RIGHT_CONTENT_NULL_RIGHTWIDTH = '0vp';
const LEFT_PART_WIDTH = 'calc(66% - 16vp)';
const RIGHT_PART_WIDTH = '34%';
const RIGHT_ONLY_ARROW_WIDTH = '24vp';
const DEFAULT_ITEM_SPACE_WIDTH = 12;
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
const FOCUSABLE = LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focus_dynamic_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value !== 1;
const RECOVER_YSCALE = 1;
const CLEAR_SHADOW = -1;
const OPERATE_ITEM_RADIUS = 50;
const OPERATE_ITEM_BACKGROUND_COLOR = '#33000000';
const OPERATE_ITECOLOR = '#99000000';
const MARQUEE = 1;
const UNUSUAL = -1;
class ContentItemStruct extends ViewPU {
    constructor(s13, t13, u13, v13 = -1, w13 = undefined, x13) {
        super(s13, u13, v13, x13);
        if (typeof w13 === "function") {
            this.paramsGenerator_ = w13;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(t13.iconStyle, this, "iconStyle");
        this.__icon = new SynchedPropertyObjectOneWayPU(t13.icon, this, "icon");
        this.__primaryText = new SynchedPropertyObjectOneWayPU(t13.primaryText, this, "primaryText");
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(t13.secondaryText, this, "secondaryText");
        this.__description = new SynchedPropertyObjectOneWayPU(t13.description, this, "description");
        this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(t13.leftWidth, this, "leftWidth");
        this.__primaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColor");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__descriptionColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "descriptionColor");
        this.__iconImageModifier = new SynchedPropertyObjectOneWayPU(t13.iconImageModifier, this, "iconImageModifier");
        this.__primaryTextModifier = new SynchedPropertyObjectOneWayPU(t13.primaryTextModifier, this, "primaryTextModifier");
        this.__secondaryTextModifier = new SynchedPropertyObjectOneWayPU(t13.secondaryTextModifier, this, "secondaryTextModifier");
        this.__descriptionModifier = new SynchedPropertyObjectOneWayPU(t13.descriptionModifier, this, "descriptionModifier");
        this.__contentItemPadding = new SynchedPropertyObjectOneWayPU(t13.contentItemPadding, this, "contentItemPadding");
        this.__itemSpace = new SynchedPropertyObjectOneWayPU(t13.itemSpace, this, "itemSpace");
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(t13.fontSizeScale, this, "fontSizeScale");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(t13.parentDirection, this, "parentDirection");
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(t13.itemDirection, this, "itemDirection");
        this.__isFocus = new SynchedPropertySimpleOneWayPU(t13.isFocus, this, "isFocus");
        this.__primaryTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextSize");
        this.__primaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColors");
        this.__itemHeight = new SynchedPropertyObjectOneWayPU(t13.itemHeight, this, "itemHeight");
        this.__iconMagnitude = new ObservedPropertyObjectPU(null, this, "iconMagnitude");
        this.__iconColor = new ObservedPropertyObjectPU(null, this, "iconColor");
        this.__secondaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColors");
        this.__secondaryThirdTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryThirdTextSize");
        this.__descriptionColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "descriptionColors");
        this.setInitiallyProvidedValue(t13);
        this.declareWatch("iconStyle", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("primaryText", this.onPropChange);
        this.declareWatch("secondaryText", this.onPropChange);
        this.declareWatch("description", this.onPropChange);
        this.declareWatch("isFocus", this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r13) {
        if (r13.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (r13.icon === undefined) {
            this.__icon.set(null);
        }
        if (r13.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (r13.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (r13.description === undefined) {
            this.__description.set(null);
        }
        if (r13.itemRowSpace !== undefined) {
            this.itemRowSpace = r13.itemRowSpace;
        }
        if (r13.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (r13.primaryTextColor !== undefined) {
            this.primaryTextColor = r13.primaryTextColor;
        }
        if (r13.secondaryTextColor !== undefined) {
            this.secondaryTextColor = r13.secondaryTextColor;
        }
        if (r13.descriptionColor !== undefined) {
            this.descriptionColor = r13.descriptionColor;
        }
        if (r13.iconImageModifier === undefined) {
            this.__iconImageModifier.set(null);
        }
        if (r13.primaryTextModifier === undefined) {
            this.__primaryTextModifier.set(null);
        }
        if (r13.secondaryTextModifier === undefined) {
            this.__secondaryTextModifier.set(null);
        }
        if (r13.descriptionModifier === undefined) {
            this.__descriptionModifier.set(null);
        }
        if (r13.contentItemPadding === undefined) {
            this.__contentItemPadding.set(null);
        }
        if (r13.itemSpace === undefined) {
            this.__itemSpace.set(DEFAULT_ITEM_SPACE_WIDTH);
        }
        if (r13.isFocus === undefined) {
            this.__isFocus.set(false);
        }
        if (r13.primaryTextSize !== undefined) {
            this.primaryTextSize = r13.primaryTextSize;
        }
        if (r13.primaryTextColors !== undefined) {
            this.primaryTextColors = r13.primaryTextColors;
        }
        if (r13.itemHeight === undefined) {
            this.__itemHeight.set(null);
        }
        if (r13.iconMagnitude !== undefined) {
            this.iconMagnitude = r13.iconMagnitude;
        }
        if (r13.iconColor !== undefined) {
            this.iconColor = r13.iconColor;
        }
        if (r13.secondaryTextColors !== undefined) {
            this.secondaryTextColors = r13.secondaryTextColors;
        }
        if (r13.secondaryThirdTextSize !== undefined) {
            this.secondaryThirdTextSize = r13.secondaryThirdTextSize;
        }
        if (r13.descriptionColors !== undefined) {
            this.descriptionColors = r13.descriptionColors;
        }
    }
    updateStateVars(q13) {
        this.__iconStyle.reset(q13.iconStyle);
        this.__icon.reset(q13.icon);
        this.__primaryText.reset(q13.primaryText);
        this.__secondaryText.reset(q13.secondaryText);
        this.__description.reset(q13.description);
        this.__leftWidth.reset(q13.leftWidth);
        this.__iconImageModifier.reset(q13.iconImageModifier);
        this.__primaryTextModifier.reset(q13.primaryTextModifier);
        this.__secondaryTextModifier.reset(q13.secondaryTextModifier);
        this.__descriptionModifier.reset(q13.descriptionModifier);
        this.__contentItemPadding.reset(q13.contentItemPadding);
        this.__itemSpace.reset(q13.itemSpace);
        this.__fontSizeScale.reset(q13.fontSizeScale);
        this.__parentDirection.reset(q13.parentDirection);
        this.__itemDirection.reset(q13.itemDirection);
        this.__isFocus.reset(q13.isFocus);
        this.__itemHeight.reset(q13.itemHeight);
    }
    purgeVariableDependenciesOnElmtId(p13) {
        this.__iconStyle.purgeDependencyOnElmtId(p13);
        this.__icon.purgeDependencyOnElmtId(p13);
        this.__primaryText.purgeDependencyOnElmtId(p13);
        this.__secondaryText.purgeDependencyOnElmtId(p13);
        this.__description.purgeDependencyOnElmtId(p13);
        this.__leftWidth.purgeDependencyOnElmtId(p13);
        this.__primaryTextColor.purgeDependencyOnElmtId(p13);
        this.__secondaryTextColor.purgeDependencyOnElmtId(p13);
        this.__descriptionColor.purgeDependencyOnElmtId(p13);
        this.__iconImageModifier.purgeDependencyOnElmtId(p13);
        this.__primaryTextModifier.purgeDependencyOnElmtId(p13);
        this.__secondaryTextModifier.purgeDependencyOnElmtId(p13);
        this.__descriptionModifier.purgeDependencyOnElmtId(p13);
        this.__contentItemPadding.purgeDependencyOnElmtId(p13);
        this.__itemSpace.purgeDependencyOnElmtId(p13);
        this.__fontSizeScale.purgeDependencyOnElmtId(p13);
        this.__parentDirection.purgeDependencyOnElmtId(p13);
        this.__itemDirection.purgeDependencyOnElmtId(p13);
        this.__isFocus.purgeDependencyOnElmtId(p13);
        this.__primaryTextSize.purgeDependencyOnElmtId(p13);
        this.__primaryTextColors.purgeDependencyOnElmtId(p13);
        this.__itemHeight.purgeDependencyOnElmtId(p13);
        this.__iconMagnitude.purgeDependencyOnElmtId(p13);
        this.__iconColor.purgeDependencyOnElmtId(p13);
        this.__secondaryTextColors.purgeDependencyOnElmtId(p13);
        this.__secondaryThirdTextSize.purgeDependencyOnElmtId(p13);
        this.__descriptionColors.purgeDependencyOnElmtId(p13);
    }
    aboutToBeDeleted() {
        this.__iconStyle.aboutToBeDeleted();
        this.__icon.aboutToBeDeleted();
        this.__primaryText.aboutToBeDeleted();
        this.__secondaryText.aboutToBeDeleted();
        this.__description.aboutToBeDeleted();
        this.__leftWidth.aboutToBeDeleted();
        this.__primaryTextColor.aboutToBeDeleted();
        this.__secondaryTextColor.aboutToBeDeleted();
        this.__descriptionColor.aboutToBeDeleted();
        this.__iconImageModifier.aboutToBeDeleted();
        this.__primaryTextModifier.aboutToBeDeleted();
        this.__secondaryTextModifier.aboutToBeDeleted();
        this.__descriptionModifier.aboutToBeDeleted();
        this.__contentItemPadding.aboutToBeDeleted();
        this.__itemSpace.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__parentDirection.aboutToBeDeleted();
        this.__itemDirection.aboutToBeDeleted();
        this.__isFocus.aboutToBeDeleted();
        this.__primaryTextSize.aboutToBeDeleted();
        this.__primaryTextColors.aboutToBeDeleted();
        this.__itemHeight.aboutToBeDeleted();
        this.__iconMagnitude.aboutToBeDeleted();
        this.__iconColor.aboutToBeDeleted();
        this.__secondaryTextColors.aboutToBeDeleted();
        this.__secondaryThirdTextSize.aboutToBeDeleted();
        this.__descriptionColors.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get iconStyle() {
        return this.__iconStyle.get();
    }
    set iconStyle(o13) {
        this.__iconStyle.set(o13);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(n13) {
        this.__icon.set(n13);
    }
    get primaryText() {
        return this.__primaryText.get();
    }
    set primaryText(m13) {
        this.__primaryText.set(m13);
    }
    get secondaryText() {
        return this.__secondaryText.get();
    }
    set secondaryText(l13) {
        this.__secondaryText.set(l13);
    }
    get description() {
        return this.__description.get();
    }
    set description(k13) {
        this.__description.set(k13);
    }
    get leftWidth() {
        return this.__leftWidth.get();
    }
    set leftWidth(j13) {
        this.__leftWidth.set(j13);
    }
    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }
    set primaryTextColor(i13) {
        this.__primaryTextColor.set(i13);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(h13) {
        this.__secondaryTextColor.set(h13);
    }
    get descriptionColor() {
        return this.__descriptionColor.get();
    }
    set descriptionColor(g13) {
        this.__descriptionColor.set(g13);
    }
    get iconImageModifier() {
        return this.__iconImageModifier.get();
    }
    set iconImageModifier(f13) {
        this.__iconImageModifier.set(f13);
    }
    get primaryTextModifier() {
        return this.__primaryTextModifier.get();
    }
    set primaryTextModifier(e13) {
        this.__primaryTextModifier.set(e13);
    }
    get secondaryTextModifier() {
        return this.__secondaryTextModifier.get();
    }
    set secondaryTextModifier(d13) {
        this.__secondaryTextModifier.set(d13);
    }
    get descriptionModifier() {
        return this.__descriptionModifier.get();
    }
    set descriptionModifier(c13) {
        this.__descriptionModifier.set(c13);
    }
    get contentItemPadding() {
        return this.__contentItemPadding.get();
    }
    set contentItemPadding(b13) {
        this.__contentItemPadding.set(b13);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(a13) {
        this.__itemSpace.set(a13);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(z12) {
        this.__fontSizeScale.set(z12);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(y12) {
        this.__parentDirection.set(y12);
    }
    get itemDirection() {
        return this.__itemDirection.get();
    }
    set itemDirection(x12) {
        this.__itemDirection.set(x12);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(w12) {
        this.__isFocus.set(w12);
    }
    get primaryTextSize() {
        return this.__primaryTextSize.get();
    }
    set primaryTextSize(v12) {
        this.__primaryTextSize.set(v12);
    }
    get primaryTextColors() {
        return this.__primaryTextColors.get();
    }
    set primaryTextColors(u12) {
        this.__primaryTextColors.set(u12);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(t12) {
        this.__itemHeight.set(t12);
    }
    get iconMagnitude() {
        return this.__iconMagnitude.get();
    }
    set iconMagnitude(s12) {
        this.__iconMagnitude.set(s12);
    }
    get iconColor() {
        return this.__iconColor.get();
    }
    set iconColor(r12) {
        this.__iconColor.set(r12);
    }
    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }
    set secondaryTextColors(q12) {
        this.__secondaryTextColors.set(q12);
    }
    get secondaryThirdTextSize() {
        return this.__secondaryThirdTextSize.get();
    }
    set secondaryThirdTextSize(p12) {
        this.__secondaryThirdTextSize.set(p12);
    }
    get descriptionColors() {
        return this.__descriptionColors.get();
    }
    set descriptionColors(o12) {
        this.__descriptionColors.set(o12);
    }
    onWillApplyTheme(n12) {
        this.primaryTextColor = n12.colors.fontPrimary;
        this.secondaryTextColor = n12.colors.fontSecondary;
        this.descriptionColor = n12.colors.fontTertiary;
    }
    onPropChange() {
        if (this.icon == null && this.iconStyle == null) {
            this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
        }
        this.primaryTextSize = this.isFocus ? { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.primaryTextColors = this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.secondaryThirdTextSize = { "id": -1, "type": 10002, params: ['sys.float.composeListItem_left_secondary_description_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.secondaryTextColors = this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_left_secondary_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_left_secondary_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.descriptionColors = this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_left_description_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_left_description_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    }
    initIconColor() {
        switch (this.iconStyle) {
            case IconType.BADGE:
                this.iconColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_badge_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                break;
            case IconType.SYSTEM_ICON:
                this.iconColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                break;
            default:
                this.iconColor = null;
                break;
        }
    }
    aboutToAppear() {
        this.onPropChange();
        this.initIconColor();
    }
    createIcon(w11 = null) {
        this.observeComponentCreation2((y11, z11) => {
            If.create();
            if (this.icon != null && this.iconStyle != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d12, e12) => {
                        If.create();
                        if (this.iconStyle <= IconType.PREVIEW) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((l12, m12) => {
                                    Image.create(this.icon);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.width(this.iconMagnitude ?? ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.height(this.iconMagnitude ?? ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.focusable(true);
                                    Image.draggable(false);
                                    Image.fillColor(this.iconColor ?? { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.iconImageModifier));
                                    Image.flexShrink(0);
                                }, Image);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((h12, i12) => {
                                    Image.create(this.icon);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.constraintSize({
                                        minWidth: SPECIAL_ICON_SIZE,
                                        maxWidth: ICON_SIZE_MAP.get(this.iconStyle),
                                        minHeight: SPECIAL_ICON_SIZE,
                                        maxHeight: ICON_SIZE_MAP.get(this.iconStyle)
                                    });
                                    Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.focusable(true);
                                    Image.draggable(false);
                                    Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.iconImageModifier));
                                    Image.flexShrink(0);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    createText(z10 = null) {
        this.observeComponentCreation2((u11, v11) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((s11, t11) => {
            Text.create(this.primaryText);
            Text.fontSize(this.primaryTextSize ?? { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(this.primaryTextColors ?? this.primaryTextColor);
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(true);
            Text.draggable(false);
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTextModifier));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((l11, m11) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q11, r11) => {
                        Text.create(this.secondaryText);
                        Text.fontSize(this.secondaryThirdTextSize ?? { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(this.secondaryTextColors ?? this.secondaryTextColor);
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTextModifier));
                    }, Text);
                    Text.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((e11, f11) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j11, k11) => {
                        Text.create(this.description);
                        Text.fontSize(this.secondaryThirdTextSize ?? { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(this.descriptionColors ?? this.descriptionColor);
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.descriptionModifier));
                    }, Text);
                    Text.pop();
                });
            }
            else {
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
    getItemSpace() {
        if (this.isColumnDirection()) {
            return LengthMetrics.vp(2);
        }
        return LengthMetrics.vp(this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH);
    }
    initialRender() {
        this.observeComponentCreation2((x10, y10) => {
            Flex.create({
                space: { main: this.getItemSpace() },
                direction: this.itemDirection,
                justifyContent: FlexAlign.Start,
                alignItems: this.isColumnDirection() ? ItemAlign.Start : ItemAlign.Center,
            });
            Flex.margin({
                end: this.parentDirection === FlexDirection.Column ?
                LengthMetrics.vp(0) : LengthMetrics.vp(this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH)
            });
            Flex.constraintSize({ minWidth: this.leftWidth });
            Flex.flexShrink(1);
        }, Flex);
        this.createIcon.bind(this)(this);
        this.createText.bind(this)(this);
        Flex.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class CreateIconParam {
}
class OperateItemStruct extends ViewPU {
    constructor(q10, r10, s10, t10 = -1, u10 = undefined, v10) {
        super(q10, s10, t10, v10);
        if (typeof u10 === "function") {
            this.paramsGenerator_ = u10;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(r10.arrow, this, "arrow");
        this.__icon = new SynchedPropertyObjectOneWayPU(r10.icon, this, "icon");
        this.__subIcon = new SynchedPropertyObjectOneWayPU(r10.subIcon, this, "subIcon");
        this.__button = new SynchedPropertyObjectOneWayPU(r10.button, this, "button");
        this.__switch = new SynchedPropertyObjectOneWayPU(r10.switch, this, "switch");
        this.__checkBox = new SynchedPropertyObjectOneWayPU(r10.checkBox, this, "checkBox");
        this.__radio = new SynchedPropertyObjectOneWayPU(r10.radio, this, "radio");
        this.__image = new SynchedPropertyObjectOneWayPU(r10.image, this, "image");
        this.__text = new SynchedPropertyObjectOneWayPU(r10.text, this, "text");
        this.__switchState = new ObservedPropertySimplePU(false, this, "switchState");
        this.__radioState = new ObservedPropertySimplePU(false, this, "radioState");
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, "checkBoxState");
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(r10.rightWidth, this, "rightWidth");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, "hoveringColor");
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, "activedColor");
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(r10.parentCanFocus, this, "parentCanFocus");
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(r10.parentCanTouch, this, "parentCanTouch");
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(r10.parentIsHover, this, "parentIsHover");
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(r10.parentCanHover, this, "parentCanHover");
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(r10.parentIsActive, this, "parentIsActive");
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(r10.parentFrontColor, this, "parentFrontColor");
        this.__isParentCanTouch = new SynchedPropertySimpleTwoWayPU(r10.isParentCanTouch, this, "isParentCanTouch");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(r10.parentDirection, this, "parentDirection");
        this.rowSpace = DEFAULT_ROW_SPACE;
        this.__isFocus = new SynchedPropertySimpleTwoWayPU(r10.isFocus, this, "isFocus");
        this.__secondaryTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextSize");
        this.__secondaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColors");
        this.__iconColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "iconColor");
        this.__isOnClick = new SynchedPropertySimpleTwoWayPU(r10.isOnClick, this, "isOnClick");
        this.setInitiallyProvidedValue(r10);
        this.declareWatch("arrow", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("subIcon", this.onPropChange);
        this.declareWatch("button", this.onPropChange);
        this.declareWatch("switch", this.onPropChange);
        this.declareWatch("checkBox", this.onPropChange);
        this.declareWatch("radio", this.onPropChange);
        this.declareWatch("image", this.onPropChange);
        this.declareWatch("text", this.onPropChange);
        this.declareWatch("isFocus", this.onFocusChange);
        this.declareWatch("isOnClick", this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(p10) {
        if (p10.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (p10.icon === undefined) {
            this.__icon.set(null);
        }
        if (p10.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (p10.button === undefined) {
            this.__button.set(null);
        }
        if (p10.switch === undefined) {
            this.__switch.set(null);
        }
        if (p10.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (p10.radio === undefined) {
            this.__radio.set(null);
        }
        if (p10.image === undefined) {
            this.__image.set(null);
        }
        if (p10.text === undefined) {
            this.__text.set(null);
        }
        if (p10.switchState !== undefined) {
            this.switchState = p10.switchState;
        }
        if (p10.radioState !== undefined) {
            this.radioState = p10.radioState;
        }
        if (p10.checkBoxState !== undefined) {
            this.checkBoxState = p10.checkBoxState;
        }
        if (p10.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (p10.secondaryTextColor !== undefined) {
            this.secondaryTextColor = p10.secondaryTextColor;
        }
        if (p10.hoveringColor !== undefined) {
            this.hoveringColor = p10.hoveringColor;
        }
        if (p10.activedColor !== undefined) {
            this.activedColor = p10.activedColor;
        }
        if (p10.rowSpace !== undefined) {
            this.rowSpace = p10.rowSpace;
        }
        if (p10.secondaryTextSize !== undefined) {
            this.secondaryTextSize = p10.secondaryTextSize;
        }
        if (p10.secondaryTextColors !== undefined) {
            this.secondaryTextColors = p10.secondaryTextColors;
        }
        if (p10.iconColor !== undefined) {
            this.iconColor = p10.iconColor;
        }
    }
    updateStateVars(o10) {
        this.__arrow.reset(o10.arrow);
        this.__icon.reset(o10.icon);
        this.__subIcon.reset(o10.subIcon);
        this.__button.reset(o10.button);
        this.__switch.reset(o10.switch);
        this.__checkBox.reset(o10.checkBox);
        this.__radio.reset(o10.radio);
        this.__image.reset(o10.image);
        this.__text.reset(o10.text);
        this.__rightWidth.reset(o10.rightWidth);
        this.__parentDirection.reset(o10.parentDirection);
    }
    purgeVariableDependenciesOnElmtId(n10) {
        this.__arrow.purgeDependencyOnElmtId(n10);
        this.__icon.purgeDependencyOnElmtId(n10);
        this.__subIcon.purgeDependencyOnElmtId(n10);
        this.__button.purgeDependencyOnElmtId(n10);
        this.__switch.purgeDependencyOnElmtId(n10);
        this.__checkBox.purgeDependencyOnElmtId(n10);
        this.__radio.purgeDependencyOnElmtId(n10);
        this.__image.purgeDependencyOnElmtId(n10);
        this.__text.purgeDependencyOnElmtId(n10);
        this.__switchState.purgeDependencyOnElmtId(n10);
        this.__radioState.purgeDependencyOnElmtId(n10);
        this.__checkBoxState.purgeDependencyOnElmtId(n10);
        this.__rightWidth.purgeDependencyOnElmtId(n10);
        this.__secondaryTextColor.purgeDependencyOnElmtId(n10);
        this.__hoveringColor.purgeDependencyOnElmtId(n10);
        this.__activedColor.purgeDependencyOnElmtId(n10);
        this.__parentCanFocus.purgeDependencyOnElmtId(n10);
        this.__parentCanTouch.purgeDependencyOnElmtId(n10);
        this.__parentIsHover.purgeDependencyOnElmtId(n10);
        this.__parentCanHover.purgeDependencyOnElmtId(n10);
        this.__parentIsActive.purgeDependencyOnElmtId(n10);
        this.__parentFrontColor.purgeDependencyOnElmtId(n10);
        this.__isParentCanTouch.purgeDependencyOnElmtId(n10);
        this.__parentDirection.purgeDependencyOnElmtId(n10);
        this.__isFocus.purgeDependencyOnElmtId(n10);
        this.__secondaryTextSize.purgeDependencyOnElmtId(n10);
        this.__secondaryTextColors.purgeDependencyOnElmtId(n10);
        this.__iconColor.purgeDependencyOnElmtId(n10);
        this.__isOnClick.purgeDependencyOnElmtId(n10);
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
        this.__isParentCanTouch.aboutToBeDeleted();
        this.__parentDirection.aboutToBeDeleted();
        this.__isFocus.aboutToBeDeleted();
        this.__secondaryTextSize.aboutToBeDeleted();
        this.__secondaryTextColors.aboutToBeDeleted();
        this.__iconColor.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get arrow() {
        return this.__arrow.get();
    }
    set arrow(m10) {
        this.__arrow.set(m10);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(l10) {
        this.__icon.set(l10);
    }
    get subIcon() {
        return this.__subIcon.get();
    }
    set subIcon(k10) {
        this.__subIcon.set(k10);
    }
    get button() {
        return this.__button.get();
    }
    set button(j10) {
        this.__button.set(j10);
    }
    get switch() {
        return this.__switch.get();
    }
    set switch(i10) {
        this.__switch.set(i10);
    }
    get checkBox() {
        return this.__checkBox.get();
    }
    set checkBox(h10) {
        this.__checkBox.set(h10);
    }
    get radio() {
        return this.__radio.get();
    }
    set radio(g10) {
        this.__radio.set(g10);
    }
    get image() {
        return this.__image.get();
    }
    set image(f10) {
        this.__image.set(f10);
    }
    get text() {
        return this.__text.get();
    }
    set text(e10) {
        this.__text.set(e10);
    }
    get switchState() {
        return this.__switchState.get();
    }
    set switchState(d10) {
        this.__switchState.set(d10);
    }
    get radioState() {
        return this.__radioState.get();
    }
    set radioState(c10) {
        this.__radioState.set(c10);
    }
    get checkBoxState() {
        return this.__checkBoxState.get();
    }
    set checkBoxState(b10) {
        this.__checkBoxState.set(b10);
    }
    get rightWidth() {
        return this.__rightWidth.get();
    }
    set rightWidth(a10) {
        this.__rightWidth.set(a10);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(z9) {
        this.__secondaryTextColor.set(z9);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(y9) {
        this.__hoveringColor.set(y9);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(x9) {
        this.__activedColor.set(x9);
    }
    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }
    set parentCanFocus(w9) {
        this.__parentCanFocus.set(w9);
    }
    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }
    set parentCanTouch(v9) {
        this.__parentCanTouch.set(v9);
    }
    get parentIsHover() {
        return this.__parentIsHover.get();
    }
    set parentIsHover(u9) {
        this.__parentIsHover.set(u9);
    }
    get parentCanHover() {
        return this.__parentCanHover.get();
    }
    set parentCanHover(t9) {
        this.__parentCanHover.set(t9);
    }
    get parentIsActive() {
        return this.__parentIsActive.get();
    }
    set parentIsActive(s9) {
        this.__parentIsActive.set(s9);
    }
    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }
    set parentFrontColor(r9) {
        this.__parentFrontColor.set(r9);
    }
    get isParentCanTouch() {
        return this.__isParentCanTouch.get();
    }
    set isParentCanTouch(q9) {
        this.__isParentCanTouch.set(q9);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(p9) {
        this.__parentDirection.set(p9);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(o9) {
        this.__isFocus.set(o9);
    }
    get secondaryTextSize() {
        return this.__secondaryTextSize.get();
    }
    set secondaryTextSize(n9) {
        this.__secondaryTextSize.set(n9);
    }
    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }
    set secondaryTextColors(m9) {
        this.__secondaryTextColors.set(m9);
    }
    get iconColor() {
        return this.__iconColor.get();
    }
    set iconColor(l9) {
        this.__iconColor.set(l9);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(k9) {
        this.__isOnClick.set(k9);
    }
    onWillApplyTheme(j9) {
        this.secondaryTextColor = j9.colors.fontSecondary;
        this.hoveringColor = j9.colors.interactiveHover;
        this.activedColor = j9.colors.interactiveActive;
    }
    onFocusChange() {
        this.secondaryTextSize = this.isFocus ? { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_right_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.secondaryTextColors = this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_right_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.iconColor = this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_right_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    }
    onPropChange() {
        if (this.switch != null) {
            this.switchState = FOCUSABLE ? this.switch.isCheck : this.isOnClick;
        }
        if (this.radio != null) {
            this.radioState = FOCUSABLE ? this.radio.isCheck : this.isOnClick;
        }
        if (this.checkBox != null) {
            this.checkBoxState = FOCUSABLE ? this.checkBox.isCheck : this.isOnClick;
        }
        if ((this.button == null && this.image == null && this.icon != null && this.text != null) ||
            (this.button == null && this.image == null && this.icon == null && this.arrow != null && this.text != null)) {
            this.rowSpace = SPECICAL_ROW_SPACE;
        }
    }
    aboutToAppear() {
        this.onPropChange();
        this.onFocusChange();
    }
    createButton(u8 = null) {
        this.observeComponentCreation2((c9, d9) => {
            Button.createWithChild();
            Button.hitTestBehavior(HitTestMode.Block);
            Button.buttonStyle(ButtonStyleMode.NORMAL);
            Button.controlSize(ControlSize.SMALL);
            Button.constraintSize({
                minHeight: BUTTON_SIZE
            });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((i9) => {
                if (i9.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (i9.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((h9) => {
                this.parentCanHover = false;
                if (h9 && this.parentFrontColor === HOVERING_COLOR) {
                    this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
                }
                if (!h9) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR :
                            (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((a9, b9) => {
            Row.create();
            Row.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
            });
        }, Row);
        this.observeComponentCreation2((y8, z8) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(f8, g8 = null) {
        this.observeComponentCreation2((l8, m8) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL2) });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((t8) => {
                if (t8.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (t8.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((s8) => {
                this.parentCanHover = false;
                if (s8 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!s8) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onAppear(() => {
                this.isParentCanTouch = true;
            });
            Button.onClick(() => {
                if (FOCUSABLE && f8.icon?.action) {
                    f8.icon.action();
                }
            });
        }, Button);
        this.observeComponentCreation2((j8, k8) => {
            Image.create(f8.icon?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ICONLIKE_SIZE);
            Image.focusable(true);
            Image.fillColor(this.iconColor ?? { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createImage(a8 = null) {
        this.observeComponentCreation2((c8, d8) => {
            Image.create(this.image);
            Image.height(OPERATEITEM_IMAGE_SIZE);
            Image.width(OPERATEITEM_IMAGE_SIZE);
            Image.draggable(false);
            Image.onAppear(() => {
                this.isParentCanTouch = true;
            });
        }, Image);
    }
    createText(v7 = null) {
        this.observeComponentCreation2((x7, y7) => {
            Text.create(this.text);
            Text.fontSize(this.secondaryTextSize ?? { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(this.secondaryTextColors ?? this.secondaryTextColor);
            Text.textOverflow({
                overflow: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_right_textOverflow'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                    .value === MARQUEE ? TextOverflow.MARQUEE : TextOverflow.None
            });
            Text.marqueeOptions({
                start: this.isFocus,
                fadeout: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_marqueeOptions_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value === MARQUEE
            });
            Text.maxLines(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_maxLines_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value);
            Text.focusable(true);
            Text.draggable(false);
            Text.flexShrink(1);
            Text.onAppear(() => {
                this.isParentCanTouch = true;
            });
        }, Text);
        Text.pop();
    }
    createArrow(h7 = null) {
        this.observeComponentCreation2((m7, n7) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((u7) => {
                if (u7.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (u7.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((t7) => {
                this.parentCanHover = false;
                if (t7 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!t7) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onAppear(() => {
                this.isParentCanTouch = true;
            });
            Button.onClick(() => {
                if (FOCUSABLE && this.arrow?.action) {
                    this.arrow.action();
                }
            });
        }, Button);
        this.observeComponentCreation2((k7, l7) => {
            Image.create(this.arrow?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.focusable(true);
            Image.fillColor(FOCUSABLE ? { "id": -1, "type": 10001, params: ['sys.color.icon_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : this.iconColor);
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createRadio(w6 = null) {
        this.observeComponentCreation2((y6, z6) => {
            Radio.create({ value: '', group: '' });
            Radio.radioStyle({
                uncheckedBorderColor: !FOCUSABLE && this.isFocus ? OPERATE_ITECOLOR : UNUSUAL
            });
            Radio.backgroundColor(!FOCUSABLE && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR : Color.Transparent.toString());
            Radio.borderRadius(FOCUSABLE ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Radio.onClick(() => {
                if (!FOCUSABLE) {
                    this.radioState = !this.radioState;
                    this.isOnClick = this.radioState;
                }
            });
            Radio.margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL1) });
            Radio.checked(this.radioState);
            Radio.onChange(this.radio?.onChange);
            Radio.height(OPERATEITEM_ICONLIKE_SIZE);
            Radio.width(OPERATEITEM_ICONLIKE_SIZE);
            Radio.onFocus(() => {
                this.parentCanFocus = false;
            });
            Radio.hitTestBehavior(HitTestMode.Block);
            Radio.onTouch((g7) => {
                if (g7.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (g7.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Radio.onHover((f7) => {
                this.parentCanHover = false;
                if (f7 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!f7) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Radio.onAppear(() => {
                this.isParentCanTouch = true;
            });
        }, Radio);
    }
    createCheckBox(l6 = null) {
        this.observeComponentCreation2((n6, o6) => {
            Checkbox.create();
            Checkbox.borderRadius(FOCUSABLE ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Checkbox.unselectedColor(!FOCUSABLE && this.isFocus ? OPERATE_ITECOLOR : UNUSUAL);
            Checkbox.backgroundColor(!FOCUSABLE && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR : Color.Transparent.toString());
            Checkbox.onClick(() => {
                if (!FOCUSABLE) {
                    this.checkBoxState = !this.checkBoxState;
                    this.isOnClick = this.checkBoxState;
                }
            });
            Checkbox.margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL1) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange(this.checkBox?.onChange);
            Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.width(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.onFocus(() => {
                this.parentCanFocus = false;
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.onTouch((v6) => {
                if (v6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (v6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Checkbox.onHover((u6) => {
                this.parentCanHover = false;
                if (u6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!u6) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Checkbox.onAppear(() => {
                this.isParentCanTouch = true;
            });
        }, Checkbox);
        Checkbox.pop();
    }
    createSwitch(y5 = null) {
        this.observeComponentCreation2((e6, f6) => {
            Row.create();
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onTouch((k6) => {
                if (k6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (k6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Row.onHover((j6) => {
                this.parentCanHover = false;
                if (j6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!j6) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((b6, c6) => {
            Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
            Toggle.borderRadius(FOCUSABLE ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Toggle.backgroundColor(!FOCUSABLE && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR : Color.Transparent.toString());
            Toggle.switchPointColor(!FOCUSABLE && this.isFocus && !this.switchState ? OPERATE_ITECOLOR : UNUSUAL);
            Toggle.onChange(this.switch?.onChange);
            Toggle.onClick(() => {
                this.switchState = !this.switchState;
                if (!FOCUSABLE) {
                    this.isOnClick = this.switchState;
                }
            });
            Toggle.hitTestBehavior(HitTestMode.Block);
        }, Toggle);
        Toggle.pop();
        Row.pop();
    }
    createTextArrow(e5 = null) {
        this.observeComponentCreation2((p5, q5) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((x5) => {
                if (x5.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (x5.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((w5) => {
                this.parentCanHover = false;
                if (w5 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!w5) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onAppear(() => {
                this.isParentCanTouch = true;
            });
            Button.onClick(() => {
                if (FOCUSABLE && this.arrow?.action) {
                    this.arrow.action();
                }
            });
        }, Button);
        this.observeComponentCreation2((n5, o5) => {
            Row.create({ space: SPECICAL_ROW_SPACE });
        }, Row);
        this.observeComponentCreation2((l5, m5) => {
            Text.create(this.text);
            Text.fontSize(this.secondaryTextSize ?? { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(this.secondaryTextColors ?? { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.textOverflow({
                overflow: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_right_textOverflow'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                    .value === MARQUEE ? TextOverflow.MARQUEE : TextOverflow.None
            });
            Text.marqueeOptions({
                start: this.isFocus,
                fadeout: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_marqueeOptions_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value === MARQUEE
            });
            Text.maxLines(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_maxLines_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value);
            Text.focusable(true);
            Text.draggable(false);
            Text.constraintSize({
                maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((j5, k5) => {
            Image.create(this.arrow?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.fillColor(FOCUSABLE ? { "id": -1, "type": 10001, params: ['sys.color.icon_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : this.iconColor);
            Image.focusable(true);
            Image.draggable(false);
        }, Image);
        Row.pop();
        Button.pop();
    }
    getFlexOptions() {
        let d5 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            d5.justifyContent = FlexAlign.SpaceBetween;
        }
        else {
            d5.space = { main: LengthMetrics.vp(this.rowSpace) };
            d5.justifyContent = FlexAlign.End;
        }
        return d5;
    }
    initialRender() {
        this.observeComponentCreation2((b5, c5) => {
            Flex.create(this.getFlexOptions());
            Flex.flexShrink(1);
            Flex.constraintSize({ minWidth: this.rightWidth });
        }, Flex);
        this.observeComponentCreation2((b4, c4) => {
            If.create();
            if (this.button != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.createButton.bind(this)(this);
                });
            }
            else if (this.image != null) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.createImage.bind(this)(this);
                });
            }
            else if (this.icon != null && this.text != null) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.createText.bind(this)(this);
                    this.createIcon.bind(this)(makeBuilderParameterProxy("createIcon", { icon: () => (this["__icon"] ? this["__icon"] : this["icon"]) }), this);
                });
            }
            else if (this.arrow != null && this.text == null) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.createArrow.bind(this)(this);
                });
            }
            else if (this.arrow != null && this.text != null) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.observeComponentCreation2((q4, r4) => {
                        If.create();
                        if (this.parentDirection === FlexDirection.Column) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((v4, w4) => {
                                    Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
                                    Flex.flexShrink(0);
                                }, Flex);
                                this.createText.bind(this)(this);
                                this.createIcon.bind(this)(makeBuilderParameterProxy("createIcon", { icon: () => (this["__arrow"] ? this["__arrow"] : this["arrow"]) }), this);
                                Flex.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.createTextArrow.bind(this)(this);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
            else if (this.text != null) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.createText.bind(this)(this);
                });
            }
            else if (this.radio != null) {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.createRadio.bind(this)(this);
                });
            }
            else if (this.checkBox != null) {
                this.ifElseBranchUpdateFunction(7, () => {
                    this.createCheckBox.bind(this)(this);
                });
            }
            else if (this.switch != null) {
                this.ifElseBranchUpdateFunction(8, () => {
                    this.createSwitch.bind(this)(this);
                });
            }
            else if (this.icon != null) {
                this.ifElseBranchUpdateFunction(9, () => {
                    this.createIcon.bind(this)(makeBuilderParameterProxy("createIcon", { icon: () => (this["__icon"] ? this["__icon"] : this["icon"]) }), this);
                    this.observeComponentCreation2((g4, h4) => {
                        If.create();
                        if (this.subIcon != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.createIcon.bind(this)(makeBuilderParameterProxy("createIcon", { icon: () => (this["__subIcon"] ? this["__subIcon"] : this["subIcon"]) }), this);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
            else {
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
OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL1 = 0;
OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL2 = -8;
export class ComposeListItem extends ViewPU {
    constructor(t3, u3, v3, w3 = -1, x3 = undefined, y3) {
        super(t3, v3, w3, y3);
        if (typeof x3 === "function") {
            this.paramsGenerator_ = x3;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(u3.contentItem, this, "contentItem");
        this.__operateItem = new SynchedPropertyObjectOneWayPU(u3.operateItem, this, "operateItem");
        this.__itemSpace = new SynchedPropertySimpleOneWayPU(u3.itemSpace, this, "itemSpace");
        this.__composeItemPadding = new SynchedPropertyObjectOneWayPU(u3.composeItemPadding, this, "composeItemPadding");
        this.__frontColor = new ObservedPropertyObjectPU(Color.Transparent.toString(), this, "frontColor");
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
        this.__focusOutlineColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "focusOutlineColor");
        this.__isCanTouch = new ObservedPropertySimplePU(false, this, "isCanTouch");
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, "fontSizeScale");
        this.__containerDirection = new ObservedPropertySimplePU(FlexDirection.Row, this, "containerDirection");
        this.__contentItemDirection = new ObservedPropertySimplePU(FlexDirection.Row, this, "contentItemDirection");
        this.__containerPadding = new ObservedPropertyObjectPU({
            top: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
        }, this, "containerPadding");
        this.callbackId = -1;
        this.__isFocus = new ObservedPropertySimplePU(false, this, "isFocus");
        this.__isHoverBlend = new ObservedPropertySimplePU(false, this, "isHoverBlend");
        this.__isOnClick = new ObservedPropertySimplePU(false, this, "isOnClick");
        this.setInitiallyProvidedValue(u3);
        this.declareWatch("contentItem", this.onPropChange);
        this.declareWatch("operateItem", this.onPropChange);
        this.declareWatch("fontSizeScale", this.onFontSizeScaleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(s3) {
        if (s3.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (s3.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (s3.itemSpace === undefined) {
            this.__itemSpace.set(DEFAULT_ITEM_SPACE_WIDTH);
        }
        if (s3.composeItemPadding === undefined) {
            this.__composeItemPadding.set(null);
        }
        if (s3.frontColor !== undefined) {
            this.frontColor = s3.frontColor;
        }
        if (s3.borderSize !== undefined) {
            this.borderSize = s3.borderSize;
        }
        if (s3.canFocus !== undefined) {
            this.canFocus = s3.canFocus;
        }
        if (s3.canTouch !== undefined) {
            this.canTouch = s3.canTouch;
        }
        if (s3.canHover !== undefined) {
            this.canHover = s3.canHover;
        }
        if (s3.isHover !== undefined) {
            this.isHover = s3.isHover;
        }
        if (s3.itemHeight !== undefined) {
            this.itemHeight = s3.itemHeight;
        }
        if (s3.isActive !== undefined) {
            this.isActive = s3.isActive;
        }
        if (s3.hoveringColor !== undefined) {
            this.hoveringColor = s3.hoveringColor;
        }
        if (s3.touchDownColor !== undefined) {
            this.touchDownColor = s3.touchDownColor;
        }
        if (s3.activedColor !== undefined) {
            this.activedColor = s3.activedColor;
        }
        if (s3.focusOutlineColor !== undefined) {
            this.focusOutlineColor = s3.focusOutlineColor;
        }
        if (s3.isCanTouch !== undefined) {
            this.isCanTouch = s3.isCanTouch;
        }
        if (s3.fontSizeScale !== undefined) {
            this.fontSizeScale = s3.fontSizeScale;
        }
        if (s3.containerDirection !== undefined) {
            this.containerDirection = s3.containerDirection;
        }
        if (s3.contentItemDirection !== undefined) {
            this.contentItemDirection = s3.contentItemDirection;
        }
        if (s3.containerPadding !== undefined) {
            this.containerPadding = s3.containerPadding;
        }
        if (s3.callbackId !== undefined) {
            this.callbackId = s3.callbackId;
        }
        if (s3.isFocus !== undefined) {
            this.isFocus = s3.isFocus;
        }
        if (s3.isHoverBlend !== undefined) {
            this.isHoverBlend = s3.isHoverBlend;
        }
        if (s3.isOnClick !== undefined) {
            this.isOnClick = s3.isOnClick;
        }
    }
    updateStateVars(r3) {
        this.__contentItem.reset(r3.contentItem);
        this.__operateItem.reset(r3.operateItem);
        this.__itemSpace.reset(r3.itemSpace);
        this.__composeItemPadding.reset(r3.composeItemPadding);
    }
    purgeVariableDependenciesOnElmtId(q3) {
        this.__contentItem.purgeDependencyOnElmtId(q3);
        this.__operateItem.purgeDependencyOnElmtId(q3);
        this.__itemSpace.purgeDependencyOnElmtId(q3);
        this.__composeItemPadding.purgeDependencyOnElmtId(q3);
        this.__frontColor.purgeDependencyOnElmtId(q3);
        this.__borderSize.purgeDependencyOnElmtId(q3);
        this.__canFocus.purgeDependencyOnElmtId(q3);
        this.__canTouch.purgeDependencyOnElmtId(q3);
        this.__canHover.purgeDependencyOnElmtId(q3);
        this.__isHover.purgeDependencyOnElmtId(q3);
        this.__itemHeight.purgeDependencyOnElmtId(q3);
        this.__isActive.purgeDependencyOnElmtId(q3);
        this.__hoveringColor.purgeDependencyOnElmtId(q3);
        this.__touchDownColor.purgeDependencyOnElmtId(q3);
        this.__activedColor.purgeDependencyOnElmtId(q3);
        this.__focusOutlineColor.purgeDependencyOnElmtId(q3);
        this.__isCanTouch.purgeDependencyOnElmtId(q3);
        this.__fontSizeScale.purgeDependencyOnElmtId(q3);
        this.__containerDirection.purgeDependencyOnElmtId(q3);
        this.__contentItemDirection.purgeDependencyOnElmtId(q3);
        this.__containerPadding.purgeDependencyOnElmtId(q3);
        this.__isFocus.purgeDependencyOnElmtId(q3);
        this.__isHoverBlend.purgeDependencyOnElmtId(q3);
        this.__isOnClick.purgeDependencyOnElmtId(q3);
    }
    aboutToBeDeleted() {
        this.__contentItem.aboutToBeDeleted();
        this.__operateItem.aboutToBeDeleted();
        this.__itemSpace.aboutToBeDeleted();
        this.__composeItemPadding.aboutToBeDeleted();
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
        this.__isCanTouch.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__containerDirection.aboutToBeDeleted();
        this.__contentItemDirection.aboutToBeDeleted();
        this.__containerPadding.aboutToBeDeleted();
        this.__isFocus.aboutToBeDeleted();
        this.__isHoverBlend.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get contentItem() {
        return this.__contentItem.get();
    }
    set contentItem(p3) {
        this.__contentItem.set(p3);
    }
    get operateItem() {
        return this.__operateItem.get();
    }
    set operateItem(o3) {
        this.__operateItem.set(o3);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(n3) {
        this.__itemSpace.set(n3);
    }
    get composeItemPadding() {
        return this.__composeItemPadding.get();
    }
    set composeItemPadding(m3) {
        this.__composeItemPadding.set(m3);
    }
    get frontColor() {
        return this.__frontColor.get();
    }
    set frontColor(l3) {
        this.__frontColor.set(l3);
    }
    get borderSize() {
        return this.__borderSize.get();
    }
    set borderSize(k3) {
        this.__borderSize.set(k3);
    }
    get canFocus() {
        return this.__canFocus.get();
    }
    set canFocus(j3) {
        this.__canFocus.set(j3);
    }
    get canTouch() {
        return this.__canTouch.get();
    }
    set canTouch(i3) {
        this.__canTouch.set(i3);
    }
    get canHover() {
        return this.__canHover.get();
    }
    set canHover(h3) {
        this.__canHover.set(h3);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(g3) {
        this.__isHover.set(g3);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(f3) {
        this.__itemHeight.set(f3);
    }
    get isActive() {
        return this.__isActive.get();
    }
    set isActive(e3) {
        this.__isActive.set(e3);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(d3) {
        this.__hoveringColor.set(d3);
    }
    get touchDownColor() {
        return this.__touchDownColor.get();
    }
    set touchDownColor(c3) {
        this.__touchDownColor.set(c3);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(b3) {
        this.__activedColor.set(b3);
    }
    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }
    set focusOutlineColor(a3) {
        this.__focusOutlineColor.set(a3);
    }
    get isCanTouch() {
        return this.__isCanTouch.get();
    }
    set isCanTouch(z2) {
        this.__isCanTouch.set(z2);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(y2) {
        this.__fontSizeScale.set(y2);
    }
    get containerDirection() {
        return this.__containerDirection.get();
    }
    set containerDirection(x2) {
        this.__containerDirection.set(x2);
    }
    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }
    set contentItemDirection(w2) {
        this.__contentItemDirection.set(w2);
    }
    get containerPadding() {
        return this.__containerPadding.get();
    }
    set containerPadding(v2) {
        this.__containerPadding.set(v2);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(u2) {
        this.__isFocus.set(u2);
    }
    get isHoverBlend() {
        return this.__isHoverBlend.get();
    }
    set isHoverBlend(t2) {
        this.__isHoverBlend.set(t2);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(s2) {
        this.__isOnClick.set(s2);
    }
    onWillApplyTheme(r2) {
        this.hoveringColor = r2.colors.interactiveHover;
        this.touchDownColor = r2.colors.interactivePressed;
        this.activedColor = r2.colors.interactiveActive;
        this.focusOutlineColor = r2.colors.interactiveFocus;
    }
    onPropChange() {
        this.onFontSizeScaleChange();
        this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? Color.Transparent.toString();
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
            }
            else {
                this.itemHeight = this.contentItem.iconStyle <= IconType.HEAD_SCULPTURE ?
                ItemHeight.SECOND_HEIGHT : (LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_system_icon_line_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                        .value ?? ItemHeight.THIRD_HEIGHT);
            }
        }
        else if (this.contentItem.description === undefined) {
            if (this.contentItem.icon === undefined ||
                (this.contentItem.icon !== undefined && this.contentItem.iconStyle <= IconType.SYSTEM_ICON)) {
                this.itemHeight = ItemHeight.THIRD_HEIGHT;
            }
            else {
                this.itemHeight = ItemHeight.FOURTH_HEIGHT;
            }
        }
        else {
            this.itemHeight = ItemHeight.FIFTH_HEIGHT;
        }
        if (ICON_SIZE_MAP.get(this.contentItem?.iconStyle) >= this.itemHeight) {
            this.itemHeight = ICON_SIZE_MAP.get(this.contentItem?.iconStyle) + SAFE_LIST_PADDING;
        }
    }
    aboutToAppear() {
        this.onPropChange();
    }
    calculatedLeftWidth() {
        let q2 = this.composeItemPadding?.start?.value ?? STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return `calc(100% - ${q2}vp)`;
        }
        else if (this.operateItem !== null &&
            this.operateItem.button === undefined &&
            this.operateItem.text === undefined) {
            if (this.operateItem.subIcon !== null) {
                return `calc(100% - ${q2}vp - ${OPERATEITEM_ICON_CLICKABLE_SIZE}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
            }
            else {
                return `calc(100% - ${q2}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
            }
        }
        else {
            return `calc(66% - ${q2}vp)`;
        }
    }
    calculatedRightWidth() {
        let p2 = this.composeItemPadding?.end !== undefined ? this.composeItemPadding?.end?.value : STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return RIGHT_CONTENT_NULL_RIGHTWIDTH;
        }
        else if (this.operateItem !== null && this.operateItem.text === undefined) {
            if (this.operateItem.subIcon !== null) {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${RIGHT_ONLY_ARROW_WIDTH} + ${p2}vp)`;
            }
            else {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${p2}vp)`;
            }
        }
        else {
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
        if (this.fontSizeScale < FontSizeScaleLevel.LEVEL1) {
            return FlexDirection.Row;
        }
        if (this.operateItem?.button) {
            return FlexDirection.Column;
        }
        else if (this.operateItem?.image) {
            return FlexDirection.Row;
        }
        else if (this.operateItem?.icon && this.operateItem?.text) {
            return FlexDirection.Column;
        }
        else if (this.operateItem?.arrow) {
            if (!this.operateItem?.text) {
                return FlexDirection.Row;
            }
            return FlexDirection.Column;
        }
        else if (this.operateItem?.text) {
            return FlexDirection.Column;
        }
        else {
            return FlexDirection.Row;
        }
    }
    setContainerPadding(n2, o2) {
        this.containerPadding = {
            top: LengthMetrics.vp(LengthMetrics.resource(n2).value),
            end: LengthMetrics.vp(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value),
            bottom: LengthMetrics.vp(LengthMetrics.resource(o2).value),
            start: LengthMetrics.vp(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value),
        };
    }
    getContainerPadding() {
        if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL3) {
            this.setContainerPadding({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL2) {
            this.setContainerPadding({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? { "id": -1, "type": 10002, params: ['sys.float.padding_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? { "id": -1, "type": 10002, params: ['sys.float.padding_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1) {
            this.setContainerPadding({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }
        else {
            this.setContainerPadding({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }
    }
    onFontSizeScaleChange() {
        this.containerDirection = this.decideContainerDirection();
        this.contentItemDirection = this.decideContentItemDirection();
        this.getContainerPadding();
    }
    isSingleLine() {
        return !this.contentItem?.secondaryText && !this.contentItem?.description;
    }
    getOperateOffset() {
        if (this.containerDirection === FlexDirection.Row) {
            return LengthMetrics.vp(0);
        }
        let m2 = ICON_SIZE_MAP.get(this.contentItem?.iconStyle);
        if (m2 && m2 <= HEADSCULPTURE_SIZE) {
            return LengthMetrics.vp(m2 + (this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH));
        }
        return LengthMetrics.vp(0);
    }
    getMainSpace() {
        if (this.containerDirection === FlexDirection.Column) {
            return LengthMetrics.vp(this.isSingleLine() ? 2 : 16);
        }
        return LengthMetrics.vp(this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH);
    }
    getComposeItemLeftPadding() {
        return this.composeItemPadding?.start !== undefined ?
            this.composeItemPadding?.start : LengthMetrics.vp(STACK_PADDING);
    }
    getComposeItemRightPadding() {
        return this.composeItemPadding?.end !== undefined ?
            this.composeItemPadding?.end : LengthMetrics.vp(STACK_PADDING);
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
    onMeasureSize(e2, f2, g2) {
        let h2 = { height: 0, width: 0 };
        let i2 = this.getUIContext().getHostContext();
        this.fontSizeScale = i2.config?.fontSizeScale ?? 1;
        f2.forEach((k2) => {
            let l2 = k2.measure(g2);
            h2.width = l2.width;
            h2.height = l2.height;
        });
        return h2;
    }
    initialRender() {
        this.observeComponentCreation2((z1, a2) => {
            Stack.create();
            Stack.onFocus(() => {
                this.isFocus = true;
                this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_backboard'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? Color.Transparent.toString();
            });
            Stack.onBlur(() => {
                this.isFocus = false;
                this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? Color.Transparent.toString();
            });
            Stack.borderRadius(this.isFocus ? { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_radio'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_circular_bead'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Stack.onClick(() => {
                if (!FOCUSABLE) {
                    this.isOnClick = !this.isOnClick;
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
                x: this.isFocus ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_magnification'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                    .value : RECOVER_YSCALE,
                y: this.isFocus ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_magnification'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                    .value : RECOVER_YSCALE
            });
            Stack.shadow(this.isFocus ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_shadow_attribute'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                .value : LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_shadow_attribute'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                .value);
            Stack.margin({
                start: this.getComposeItemLeftPadding(),
                end: this.getComposeItemRightPadding()
            });
        }, Stack);
        this.observeComponentCreation2((r1, s1) => {
            Flex.create(this.getFlexOptions());
            Flex.constraintSize({ minHeight: this.itemHeight });
            Flex.focusable(FOCUSABLE);
            Flex.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Flex.backgroundColor(ObservedObject.GetRawObject(this.frontColor));
            Flex.onFocus(() => {
                this.canFocus = true;
            });
            Flex.onBlur(() => {
                this.canFocus = false;
            });
            Flex.onHover((y1) => {
                this.isHoverBlend = y1;
                this.isHover = y1;
                if (this.canHover) {
                    this.frontColor = y1 ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
                this.frontColor = y1 ? ({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? this.hoveringColor) :
                    (this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_backboard'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? Color.Transparent.toString());
            });
            Flex.onTouch((x1) => {
                if (this.isCanTouch) {
                    if (x1.type === TouchType.Down && this.canTouch) {
                        this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_press'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? this.touchDownColor;
                    }
                    if (x1.type === TouchType.Up) {
                        this.frontColor = this.isActive ? this.activedColor : (this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_backboard'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? Color.Transparent.toString());
                    }
                }
            });
            ViewStackProcessor.visualState("focused");
            Flex.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_circular_bead'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: ITEM_BORDER_SHOWN,
                color: this.focusOutlineColor,
                style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState("normal");
            Flex.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_radio'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_stroke_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } ?? Color.Transparent,
                width: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_stroke_thickness'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Flex.scale({
                x: RECOVER_YSCALE,
                y: RECOVER_YSCALE
            });
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
                                let n1 = new ContentItemStruct(this, {}, undefined, l1, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1038, col: 11 });
                                ViewPU.create(n1);
                                let o1 = () => {
                                    return {};
                                };
                                n1.paramsGenerator_ = o1;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(l1, {});
                            }
                        }, { name: "ContentItemStruct" });
                    }
                });
            }
            else {
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
                                    iconStyle: this.contentItem?.iconStyle,
                                    primaryText: this.contentItem?.primaryText,
                                    secondaryText: this.contentItem?.secondaryText,
                                    description: this.contentItem?.description,
                                    iconImageModifier: this.contentItem?.iconImageModifier,
                                    primaryTextModifier: this.contentItem?.primaryTextModifier,
                                    secondaryTextModifier: this.contentItem?.secondaryTextModifier,
                                    descriptionModifier: this.contentItem?.descriptionModifier,
                                    leftWidth: this.calculatedLeftWidth(),
                                    contentItemPadding: this.composeItemPadding,
                                    itemSpace: this.itemSpace,
                                    fontSizeScale: this.fontSizeScale,
                                    parentDirection: this.containerDirection,
                                    itemDirection: this.contentItemDirection,
                                    isFocus: this.isFocus,
                                    itemHeight: this.itemHeight,
                                }, undefined, a1, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1041, col: 11 });
                                ViewPU.create(c1);
                                let d1 = () => {
                                    return {
                                        icon: this.contentItem?.icon,
                                        iconStyle: this.contentItem?.iconStyle,
                                        primaryText: this.contentItem?.primaryText,
                                        secondaryText: this.contentItem?.secondaryText,
                                        description: this.contentItem?.description,
                                        iconImageModifier: this.contentItem?.iconImageModifier,
                                        primaryTextModifier: this.contentItem?.primaryTextModifier,
                                        secondaryTextModifier: this.contentItem?.secondaryTextModifier,
                                        descriptionModifier: this.contentItem?.descriptionModifier,
                                        leftWidth: this.calculatedLeftWidth(),
                                        contentItemPadding: this.composeItemPadding,
                                        itemSpace: this.itemSpace,
                                        fontSizeScale: this.fontSizeScale,
                                        parentDirection: this.containerDirection,
                                        itemDirection: this.contentItemDirection,
                                        isFocus: this.isFocus,
                                        itemHeight: this.itemHeight
                                    };
                                };
                                c1.paramsGenerator_ = d1;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(a1, {
                                    icon: this.contentItem?.icon,
                                    iconStyle: this.contentItem?.iconStyle,
                                    primaryText: this.contentItem?.primaryText,
                                    secondaryText: this.contentItem?.secondaryText,
                                    description: this.contentItem?.description,
                                    iconImageModifier: this.contentItem?.iconImageModifier,
                                    primaryTextModifier: this.contentItem?.primaryTextModifier,
                                    secondaryTextModifier: this.contentItem?.secondaryTextModifier,
                                    descriptionModifier: this.contentItem?.descriptionModifier,
                                    leftWidth: this.calculatedLeftWidth(),
                                    contentItemPadding: this.composeItemPadding,
                                    itemSpace: this.itemSpace,
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
            }
            else {
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
                        __Common__.align(Alignment.End);
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
                                    text: this.operateItem?.text,
                                    arrow: this.operateItem?.arrow,
                                    parentCanFocus: this.__canFocus,
                                    parentCanTouch: this.__canTouch,
                                    parentIsHover: this.__isHover,
                                    parentFrontColor: this.__frontColor,
                                    parentIsActive: this.__isActive,
                                    parentCanHover: this.__canHover,
                                    rightWidth: this.calculatedRightWidth(),
                                    isParentCanTouch: this.__isCanTouch,
                                    parentDirection: this.containerDirection,
                                    isFocus: this.__isFocus,
                                    isOnClick: this.__isOnClick,
                                }, undefined, l, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1062, col: 11 });
                                ViewPU.create(n);
                                let o = () => {
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
                                        isParentCanTouch: this.isCanTouch,
                                        parentDirection: this.containerDirection,
                                        isFocus: this.isFocus,
                                        isOnClick: this.isOnClick
                                    };
                                };
                                n.paramsGenerator_ = o;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(l, {
                                    icon: this.operateItem?.icon,
                                    subIcon: this.operateItem?.subIcon,
                                    button: this.operateItem?.button,
                                    switch: this.operateItem?.switch,
                                    checkBox: this.operateItem?.checkbox,
                                    radio: this.operateItem?.radio,
                                    image: this.operateItem?.image,
                                    text: this.operateItem?.text,
                                    arrow: this.operateItem?.arrow,
                                    rightWidth: this.calculatedRightWidth(),
                                    parentDirection: this.containerDirection
                                });
                            }
                        }, { name: "OperateItemStruct" });
                    }
                    __Common__.pop();
                });
            }
            else {
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
