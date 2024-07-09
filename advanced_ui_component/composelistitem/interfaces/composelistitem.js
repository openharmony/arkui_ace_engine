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
const resourceManager = requireNapi('resourceManager');
export var IconType;
(function (i14) {
    i14[i14["BADGE"] = 1] = "BADGE";
    i14[i14["NORMAL_ICON"] = 2] = "NORMAL_ICON";
    i14[i14["SYSTEM_ICON"] = 3] = "SYSTEM_ICON";
    i14[i14["HEAD_SCULPTURE"] = 4] = "HEAD_SCULPTURE";
    i14[i14["APP_ICON"] = 5] = "APP_ICON";
    i14[i14["PREVIEW"] = 6] = "PREVIEW";
    i14[i14["LONGITUDINAL"] = 7] = "LONGITUDINAL";
    i14[i14["VERTICAL"] = 8] = "VERTICAL";
})(IconType || (IconType = {}));
var ItemHeight;
(function (h14) {
    h14[h14["FIRST_HEIGHT"] = 48] = "FIRST_HEIGHT";
    h14[h14["SECOND_HEIGHT"] = 56] = "SECOND_HEIGHT";
    h14[h14["THIRD_HEIGHT"] = 64] = "THIRD_HEIGHT";
    h14[h14["FOURTH_HEIGHT"] = 72] = "FOURTH_HEIGHT";
    h14[h14["FIFTH_HEIGHT"] = 96] = "FIFTH_HEIGHT";
})(ItemHeight || (ItemHeight = {}));
var FontSizeScaleLevel;
(function (g14) {
    g14[g14["LEVEL1"] = 1.75] = "LEVEL1";
    g14[g14["LEVEL2"] = 2] = "LEVEL2";
    g14[g14["LEVEL3"] = 3.2] = "LEVEL3";
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
    [IconType.SYSTEM_ICON, getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_system_icon'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) || SYSTEM_ICON_SIZE],
    [IconType.HEAD_SCULPTURE, HEADSCULPTURE_SIZE],
    [IconType.APP_ICON, APP_ICON_SIZE],
    [IconType.PREVIEW, PREVIEW_SIZE],
    [IconType.LONGITUDINAL, LONGITUDINAL_SIZE],
    [IconType.VERTICAL, VERTICAL_SIZE]
]);
const FOCUSABLE = LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focus_dynamic_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value !== 1;
class ContentItemStruct extends ViewPU {
    constructor(a14, b14, c14, d14 = -1, e14 = undefined, f14) {
        super(a14, c14, d14, f14);
        if (typeof e14 === "function") {
            this.paramsGenerator_ = e14;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(b14.iconStyle, this, "iconStyle");
        this.__icon = new SynchedPropertyObjectOneWayPU(b14.icon, this, "icon");
        this.__primaryText = new SynchedPropertyObjectOneWayPU(b14.primaryText, this, "primaryText");
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(b14.secondaryText, this, "secondaryText");
        this.__description = new SynchedPropertyObjectOneWayPU(b14.description, this, "description");
        this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(b14.leftWidth, this, "leftWidth");
        this.__primaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColor");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__descriptionColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "descriptionColor");
        this.__iconImageModifier = new SynchedPropertyObjectOneWayPU(b14.iconImageModifier, this, "iconImageModifier");
        this.__primaryTextModifier = new SynchedPropertyObjectOneWayPU(b14.primaryTextModifier, this, "primaryTextModifier");
        this.__secondaryTextModifier = new SynchedPropertyObjectOneWayPU(b14.secondaryTextModifier, this, "secondaryTextModifier");
        this.__descriptionModifier = new SynchedPropertyObjectOneWayPU(b14.descriptionModifier, this, "descriptionModifier");
        this.__contentItemPadding = new SynchedPropertyObjectOneWayPU(b14.contentItemPadding, this, "contentItemPadding");
        this.__itemSpace = new SynchedPropertyObjectOneWayPU(b14.itemSpace, this, "itemSpace");
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(b14.fontSizeScale, this, "fontSizeScale");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(b14.parentDirection, this, "parentDirection");
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(b14.itemDirection, this, "itemDirection");
        this.__isFocus = new SynchedPropertySimpleOneWayPU(b14.isFocus, this, "isFocus");
        this.__primaryTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextSize");
        this.__primaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColors");
        this.__itemHeight = new SynchedPropertyObjectOneWayPU(b14.itemHeight, this, "itemHeight");
        this.__iconMagnitude = new ObservedPropertyObjectPU(null, this, "iconMagnitude");
        this.__iconHue = new ObservedPropertyObjectPU(null, this, "iconHue");
        this.__itemSpaces = new ObservedPropertyObjectPU(DEFAULT_ITEM_SPACE_WIDTH, this, "itemSpaces");
        this.setInitiallyProvidedValue(b14);
        this.declareWatch("iconStyle", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("primaryText", this.onPropChange);
        this.declareWatch("secondaryText", this.onPropChange);
        this.declareWatch("description", this.onPropChange);
        this.declareWatch("isFocus", this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z13) {
        if (z13.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (z13.icon === undefined) {
            this.__icon.set(null);
        }
        if (z13.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (z13.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (z13.description === undefined) {
            this.__description.set(null);
        }
        if (z13.itemRowSpace !== undefined) {
            this.itemRowSpace = z13.itemRowSpace;
        }
        if (z13.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (z13.primaryTextColor !== undefined) {
            this.primaryTextColor = z13.primaryTextColor;
        }
        if (z13.secondaryTextColor !== undefined) {
            this.secondaryTextColor = z13.secondaryTextColor;
        }
        if (z13.descriptionColor !== undefined) {
            this.descriptionColor = z13.descriptionColor;
        }
        if (z13.iconImageModifier === undefined) {
            this.__iconImageModifier.set(null);
        }
        if (z13.primaryTextModifier === undefined) {
            this.__primaryTextModifier.set(null);
        }
        if (z13.secondaryTextModifier === undefined) {
            this.__secondaryTextModifier.set(null);
        }
        if (z13.descriptionModifier === undefined) {
            this.__descriptionModifier.set(null);
        }
        if (z13.contentItemPadding === undefined) {
            this.__contentItemPadding.set(null);
        }
        if (z13.itemSpace === undefined) {
            this.__itemSpace.set(DEFAULT_ITEM_SPACE_WIDTH);
        }
        if (z13.isFocus === undefined) {
            this.__isFocus.set(false);
        }
        if (z13.primaryTextSize !== undefined) {
            this.primaryTextSize = z13.primaryTextSize;
        }
        if (z13.primaryTextColors !== undefined) {
            this.primaryTextColors = z13.primaryTextColors;
        }
        if (z13.itemHeight === undefined) {
            this.__itemHeight.set(null);
        }
        if (z13.iconMagnitude !== undefined) {
            this.iconMagnitude = z13.iconMagnitude;
        }
        if (z13.iconHue !== undefined) {
            this.iconHue = z13.iconHue;
        }
        if (z13.itemSpaces !== undefined) {
            this.itemSpaces = z13.itemSpaces;
        }
    }
    updateStateVars(y13) {
        this.__iconStyle.reset(y13.iconStyle);
        this.__icon.reset(y13.icon);
        this.__primaryText.reset(y13.primaryText);
        this.__secondaryText.reset(y13.secondaryText);
        this.__description.reset(y13.description);
        this.__leftWidth.reset(y13.leftWidth);
        this.__iconImageModifier.reset(y13.iconImageModifier);
        this.__primaryTextModifier.reset(y13.primaryTextModifier);
        this.__secondaryTextModifier.reset(y13.secondaryTextModifier);
        this.__descriptionModifier.reset(y13.descriptionModifier);
        this.__contentItemPadding.reset(y13.contentItemPadding);
        this.__itemSpace.reset(y13.itemSpace);
        this.__fontSizeScale.reset(y13.fontSizeScale);
        this.__parentDirection.reset(y13.parentDirection);
        this.__itemDirection.reset(y13.itemDirection);
        this.__isFocus.reset(y13.isFocus);
        this.__itemHeight.reset(y13.itemHeight);
    }
    purgeVariableDependenciesOnElmtId(x13) {
        this.__iconStyle.purgeDependencyOnElmtId(x13);
        this.__icon.purgeDependencyOnElmtId(x13);
        this.__primaryText.purgeDependencyOnElmtId(x13);
        this.__secondaryText.purgeDependencyOnElmtId(x13);
        this.__description.purgeDependencyOnElmtId(x13);
        this.__leftWidth.purgeDependencyOnElmtId(x13);
        this.__primaryTextColor.purgeDependencyOnElmtId(x13);
        this.__secondaryTextColor.purgeDependencyOnElmtId(x13);
        this.__descriptionColor.purgeDependencyOnElmtId(x13);
        this.__iconImageModifier.purgeDependencyOnElmtId(x13);
        this.__primaryTextModifier.purgeDependencyOnElmtId(x13);
        this.__secondaryTextModifier.purgeDependencyOnElmtId(x13);
        this.__descriptionModifier.purgeDependencyOnElmtId(x13);
        this.__contentItemPadding.purgeDependencyOnElmtId(x13);
        this.__itemSpace.purgeDependencyOnElmtId(x13);
        this.__fontSizeScale.purgeDependencyOnElmtId(x13);
        this.__parentDirection.purgeDependencyOnElmtId(x13);
        this.__itemDirection.purgeDependencyOnElmtId(x13);
        this.__isFocus.purgeDependencyOnElmtId(x13);
        this.__primaryTextSize.purgeDependencyOnElmtId(x13);
        this.__primaryTextColors.purgeDependencyOnElmtId(x13);
        this.__itemHeight.purgeDependencyOnElmtId(x13);
        this.__iconMagnitude.purgeDependencyOnElmtId(x13);
        this.__iconHue.purgeDependencyOnElmtId(x13);
        this.__itemSpaces.purgeDependencyOnElmtId(x13);
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
        this.__iconHue.aboutToBeDeleted();
        this.__itemSpaces.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get iconStyle() {
        return this.__iconStyle.get();
    }
    set iconStyle(w13) {
        this.__iconStyle.set(w13);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(v13) {
        this.__icon.set(v13);
    }
    get primaryText() {
        return this.__primaryText.get();
    }
    set primaryText(u13) {
        this.__primaryText.set(u13);
    }
    get secondaryText() {
        return this.__secondaryText.get();
    }
    set secondaryText(t13) {
        this.__secondaryText.set(t13);
    }
    get description() {
        return this.__description.get();
    }
    set description(s13) {
        this.__description.set(s13);
    }
    get leftWidth() {
        return this.__leftWidth.get();
    }
    set leftWidth(r13) {
        this.__leftWidth.set(r13);
    }
    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }
    set primaryTextColor(q13) {
        this.__primaryTextColor.set(q13);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(p13) {
        this.__secondaryTextColor.set(p13);
    }
    get descriptionColor() {
        return this.__descriptionColor.get();
    }
    set descriptionColor(o13) {
        this.__descriptionColor.set(o13);
    }
    get iconImageModifier() {
        return this.__iconImageModifier.get();
    }
    set iconImageModifier(n13) {
        this.__iconImageModifier.set(n13);
    }
    get primaryTextModifier() {
        return this.__primaryTextModifier.get();
    }
    set primaryTextModifier(m13) {
        this.__primaryTextModifier.set(m13);
    }
    get secondaryTextModifier() {
        return this.__secondaryTextModifier.get();
    }
    set secondaryTextModifier(l13) {
        this.__secondaryTextModifier.set(l13);
    }
    get descriptionModifier() {
        return this.__descriptionModifier.get();
    }
    set descriptionModifier(k13) {
        this.__descriptionModifier.set(k13);
    }
    get contentItemPadding() {
        return this.__contentItemPadding.get();
    }
    set contentItemPadding(j13) {
        this.__contentItemPadding.set(j13);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(i13) {
        this.__itemSpace.set(i13);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(h13) {
        this.__fontSizeScale.set(h13);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(g13) {
        this.__parentDirection.set(g13);
    }
    get itemDirection() {
        return this.__itemDirection.get();
    }
    set itemDirection(f13) {
        this.__itemDirection.set(f13);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(e13) {
        this.__isFocus.set(e13);
    }
    get primaryTextSize() {
        return this.__primaryTextSize.get();
    }
    set primaryTextSize(d13) {
        this.__primaryTextSize.set(d13);
    }
    get primaryTextColors() {
        return this.__primaryTextColors.get();
    }
    set primaryTextColors(c13) {
        this.__primaryTextColors.set(c13);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(b13) {
        this.__itemHeight.set(b13);
    }
    get iconMagnitude() {
        return this.__iconMagnitude.get();
    }
    set iconMagnitude(a13) {
        this.__iconMagnitude.set(a13);
    }
    get iconHue() {
        return this.__iconHue.get();
    }
    set iconHue(z12) {
        this.__iconHue.set(z12);
    }
    get itemSpaces() {
        return this.__itemSpaces.get();
    }
    set itemSpaces(y12) {
        this.__itemSpaces.set(y12);
    }
    onWillApplyTheme(x12) {
        this.primaryTextColor = x12.colors.fontPrimary;
        this.secondaryTextColor = x12.colors.fontSecondary;
        this.descriptionColor = x12.colors.fontTertiary;
    }
    onPropChange() {
        if (this.icon == null && this.iconStyle == null) {
            this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
        }
        this.primaryTextSize = this.isFocus ? { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.primaryTextColors = this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    }
    getIconType(t12, u12, v12, w12) {
        switch (t12) {
            case IconType.SYSTEM_ICON:
                this.getIconStyle(u12, null, w12);
                break;
            case IconType.HEAD_SCULPTURE:
                this.getIconStyle(u12, v12);
                break;
            case IconType.PREVIEW:
                this.getIconStyle(u12, v12);
                break;
            case IconType.APP_ICON:
                this.getIconStyle(u12, v12);
        }
    }
    getIconStyle(q12, r12, s12) {
        this.iconMagnitude = q12;
        this.itemSpaces = getNumberByResource(r12);
        this.iconHue = s12;
    }
    setIconStyle() {
        switch (this.itemHeight) {
            case ItemHeight.SECOND_HEIGHT:
                this.getIconType(IconType.SYSTEM_ICON, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_fifty_eight_normal_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || SYSTEM_ICON_SIZE, null, { "id": -1, "type": 10001, params: ['sys.color.composeListItem_fifty_eight_normal_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                break;
            case ItemHeight.THIRD_HEIGHT:
                this.getIconType(IconType.SYSTEM_ICON, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_sixty_four_normal_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || SYSTEM_ICON_SIZE, null, { "id": -1, "type": 10001, params: ['sys.color.composeListItem_sixty_four_normal_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                break;
            case ItemHeight.FOURTH_HEIGHT:
                this.getIconType(IconType.HEAD_SCULPTURE, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_seventy_two_normal_head_portrait_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || HEADSCULPTURE_SIZE, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_seventy_two_normal_head_portrait_and_text_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                this.getIconType(IconType.PREVIEW, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_seventy_two_normal_preview_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || (BADGE_SIZE + HEADSCULPTURE_SIZE), { "id": -1, "type": 10002, params: ['sys.float.composeListItem_seventy_two_normal_preview_and_text_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                break;
            case (ItemHeight.FIFTH_HEIGHT - ItemHeight.SECOND_HEIGHT) * 2:
                this.getIconType(IconType.APP_ICON, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_eighty_normal_app_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || (SMALL_ICON_SIZE + HEADSCULPTURE_SIZE), { "id": -1, "type": 10002, params: ['sys.float.composeListItem_eighty_normal_app_icon_and_text_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                break;
            case ItemHeight.FIFTH_HEIGHT:
                this.getIconType(IconType.APP_ICON, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_ninety_six_normal_app_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || (SMALL_ICON_SIZE + HEADSCULPTURE_SIZE), { "id": -1, "type": 10002, params: ['sys.float.composeListItem_ninety_six_normal_app_icon_and_text_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                break;
            default:
                this.iconMagnitude = null;
                this.iconHue = null;
                this.itemSpaces = DEFAULT_ITEM_SPACE_WIDTH;
                break;
        }
    }
    aboutToAppear() {
        this.onPropChange();
        this.setIconStyle();
    }
    createIcon(z11 = null) {
        this.observeComponentCreation2((b12, c12) => {
            If.create();
            if (this.icon != null && this.iconStyle != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g12, h12) => {
                        If.create();
                        if (this.iconStyle <= IconType.PREVIEW) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((o12, p12) => {
                                    Image.create(this.icon);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.width(this.iconMagnitude || ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.height(this.iconMagnitude || ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.focusable(FOCUSABLE);
                                    Image.draggable(false);
                                    Image.fillColor(this.iconHue || { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.iconImageModifier));
                                    Image.flexShrink(0);
                                }, Image);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((k12, l12) => {
                                    Image.create(this.icon);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.constraintSize({
                                        minWidth: SPECIAL_ICON_SIZE,
                                        maxWidth: ICON_SIZE_MAP.get(this.iconStyle),
                                        minHeight: SPECIAL_ICON_SIZE,
                                        maxHeight: ICON_SIZE_MAP.get(this.iconStyle)
                                    });
                                    Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.focusable(FOCUSABLE);
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
    createText(c11 = null) {
        this.observeComponentCreation2((x11, y11) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((v11, w11) => {
            Text.create(this.primaryText);
            Text.fontSize(this.primaryTextSize || { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(this.primaryTextColors || this.primaryTextColor);
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(FOCUSABLE);
            Text.draggable(false);
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTextModifier));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((o11, p11) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t11, u11) => {
                        Text.create(this.secondaryText);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
                        Text.focusable(FOCUSABLE);
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
        this.observeComponentCreation2((h11, i11) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m11, n11) => {
                        Text.create(this.description);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(ObservedObject.GetRawObject(this.descriptionColor));
                        Text.focusable(FOCUSABLE);
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
        this.observeComponentCreation2((a11, b11) => {
            Flex.create({
                space: { main: LengthMetrics.vp(ObservedObject.GetRawObject(this.itemSpaces)) || this.getItemSpace() },
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
    constructor(t10, u10, v10, w10 = -1, x10 = undefined, y10) {
        super(t10, v10, w10, y10);
        if (typeof x10 === "function") {
            this.paramsGenerator_ = x10;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(u10.arrow, this, "arrow");
        this.__icon = new SynchedPropertyObjectOneWayPU(u10.icon, this, "icon");
        this.__subIcon = new SynchedPropertyObjectOneWayPU(u10.subIcon, this, "subIcon");
        this.__button = new SynchedPropertyObjectOneWayPU(u10.button, this, "button");
        this.__switch = new SynchedPropertyObjectOneWayPU(u10.switch, this, "switch");
        this.__checkBox = new SynchedPropertyObjectOneWayPU(u10.checkBox, this, "checkBox");
        this.__radio = new SynchedPropertyObjectOneWayPU(u10.radio, this, "radio");
        this.__image = new SynchedPropertyObjectOneWayPU(u10.image, this, "image");
        this.__text = new SynchedPropertyObjectOneWayPU(u10.text, this, "text");
        this.__switchState = new ObservedPropertySimplePU(false, this, "switchState");
        this.__radioState = new ObservedPropertySimplePU(false, this, "radioState");
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, "checkBoxState");
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(u10.rightWidth, this, "rightWidth");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, "hoveringColor");
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, "activedColor");
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(u10.parentCanFocus, this, "parentCanFocus");
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(u10.parentCanTouch, this, "parentCanTouch");
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(u10.parentIsHover, this, "parentIsHover");
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(u10.parentCanHover, this, "parentCanHover");
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(u10.parentIsActive, this, "parentIsActive");
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(u10.parentFrontColor, this, "parentFrontColor");
        this.__isParentCanTouch = new SynchedPropertySimpleTwoWayPU(u10.isParentCanTouch, this, "isParentCanTouch");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(u10.parentDirection, this, "parentDirection");
        this.rowSpace = DEFAULT_ROW_SPACE;
        this.__isFocus = new SynchedPropertySimpleTwoWayPU(u10.isFocus, this, "isFocus");
        this.__secondaryTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextSize");
        this.__secondaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColors");
        this.__iconSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "iconSize");
        this.__iconColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "iconColor");
        this.__isOnClick = new SynchedPropertySimpleOneWayPU(u10.isOnClick, this, "isOnClick");
        this.setInitiallyProvidedValue(u10);
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
    setInitiallyProvidedValue(s10) {
        if (s10.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (s10.icon === undefined) {
            this.__icon.set(null);
        }
        if (s10.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (s10.button === undefined) {
            this.__button.set(null);
        }
        if (s10.switch === undefined) {
            this.__switch.set(null);
        }
        if (s10.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (s10.radio === undefined) {
            this.__radio.set(null);
        }
        if (s10.image === undefined) {
            this.__image.set(null);
        }
        if (s10.text === undefined) {
            this.__text.set(null);
        }
        if (s10.switchState !== undefined) {
            this.switchState = s10.switchState;
        }
        if (s10.radioState !== undefined) {
            this.radioState = s10.radioState;
        }
        if (s10.checkBoxState !== undefined) {
            this.checkBoxState = s10.checkBoxState;
        }
        if (s10.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (s10.secondaryTextColor !== undefined) {
            this.secondaryTextColor = s10.secondaryTextColor;
        }
        if (s10.hoveringColor !== undefined) {
            this.hoveringColor = s10.hoveringColor;
        }
        if (s10.activedColor !== undefined) {
            this.activedColor = s10.activedColor;
        }
        if (s10.rowSpace !== undefined) {
            this.rowSpace = s10.rowSpace;
        }
        if (s10.secondaryTextSize !== undefined) {
            this.secondaryTextSize = s10.secondaryTextSize;
        }
        if (s10.secondaryTextColors !== undefined) {
            this.secondaryTextColors = s10.secondaryTextColors;
        }
        if (s10.iconSize !== undefined) {
            this.iconSize = s10.iconSize;
        }
        if (s10.iconColor !== undefined) {
            this.iconColor = s10.iconColor;
        }
        if (s10.isOnClick === undefined) {
            this.__isOnClick.set(false);
        }
    }
    updateStateVars(r10) {
        this.__arrow.reset(r10.arrow);
        this.__icon.reset(r10.icon);
        this.__subIcon.reset(r10.subIcon);
        this.__button.reset(r10.button);
        this.__switch.reset(r10.switch);
        this.__checkBox.reset(r10.checkBox);
        this.__radio.reset(r10.radio);
        this.__image.reset(r10.image);
        this.__text.reset(r10.text);
        this.__rightWidth.reset(r10.rightWidth);
        this.__parentDirection.reset(r10.parentDirection);
        this.__isOnClick.reset(r10.isOnClick);
    }
    purgeVariableDependenciesOnElmtId(q10) {
        this.__arrow.purgeDependencyOnElmtId(q10);
        this.__icon.purgeDependencyOnElmtId(q10);
        this.__subIcon.purgeDependencyOnElmtId(q10);
        this.__button.purgeDependencyOnElmtId(q10);
        this.__switch.purgeDependencyOnElmtId(q10);
        this.__checkBox.purgeDependencyOnElmtId(q10);
        this.__radio.purgeDependencyOnElmtId(q10);
        this.__image.purgeDependencyOnElmtId(q10);
        this.__text.purgeDependencyOnElmtId(q10);
        this.__switchState.purgeDependencyOnElmtId(q10);
        this.__radioState.purgeDependencyOnElmtId(q10);
        this.__checkBoxState.purgeDependencyOnElmtId(q10);
        this.__rightWidth.purgeDependencyOnElmtId(q10);
        this.__secondaryTextColor.purgeDependencyOnElmtId(q10);
        this.__hoveringColor.purgeDependencyOnElmtId(q10);
        this.__activedColor.purgeDependencyOnElmtId(q10);
        this.__parentCanFocus.purgeDependencyOnElmtId(q10);
        this.__parentCanTouch.purgeDependencyOnElmtId(q10);
        this.__parentIsHover.purgeDependencyOnElmtId(q10);
        this.__parentCanHover.purgeDependencyOnElmtId(q10);
        this.__parentIsActive.purgeDependencyOnElmtId(q10);
        this.__parentFrontColor.purgeDependencyOnElmtId(q10);
        this.__isParentCanTouch.purgeDependencyOnElmtId(q10);
        this.__parentDirection.purgeDependencyOnElmtId(q10);
        this.__isFocus.purgeDependencyOnElmtId(q10);
        this.__secondaryTextSize.purgeDependencyOnElmtId(q10);
        this.__secondaryTextColors.purgeDependencyOnElmtId(q10);
        this.__iconSize.purgeDependencyOnElmtId(q10);
        this.__iconColor.purgeDependencyOnElmtId(q10);
        this.__isOnClick.purgeDependencyOnElmtId(q10);
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
        this.__iconSize.aboutToBeDeleted();
        this.__iconColor.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get arrow() {
        return this.__arrow.get();
    }
    set arrow(p10) {
        this.__arrow.set(p10);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(o10) {
        this.__icon.set(o10);
    }
    get subIcon() {
        return this.__subIcon.get();
    }
    set subIcon(n10) {
        this.__subIcon.set(n10);
    }
    get button() {
        return this.__button.get();
    }
    set button(m10) {
        this.__button.set(m10);
    }
    get switch() {
        return this.__switch.get();
    }
    set switch(l10) {
        this.__switch.set(l10);
    }
    get checkBox() {
        return this.__checkBox.get();
    }
    set checkBox(k10) {
        this.__checkBox.set(k10);
    }
    get radio() {
        return this.__radio.get();
    }
    set radio(j10) {
        this.__radio.set(j10);
    }
    get image() {
        return this.__image.get();
    }
    set image(i10) {
        this.__image.set(i10);
    }
    get text() {
        return this.__text.get();
    }
    set text(h10) {
        this.__text.set(h10);
    }
    get switchState() {
        return this.__switchState.get();
    }
    set switchState(g10) {
        this.__switchState.set(g10);
    }
    get radioState() {
        return this.__radioState.get();
    }
    set radioState(f10) {
        this.__radioState.set(f10);
    }
    get checkBoxState() {
        return this.__checkBoxState.get();
    }
    set checkBoxState(e10) {
        this.__checkBoxState.set(e10);
    }
    get rightWidth() {
        return this.__rightWidth.get();
    }
    set rightWidth(d10) {
        this.__rightWidth.set(d10);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(c10) {
        this.__secondaryTextColor.set(c10);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(b10) {
        this.__hoveringColor.set(b10);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(a10) {
        this.__activedColor.set(a10);
    }
    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }
    set parentCanFocus(z9) {
        this.__parentCanFocus.set(z9);
    }
    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }
    set parentCanTouch(y9) {
        this.__parentCanTouch.set(y9);
    }
    get parentIsHover() {
        return this.__parentIsHover.get();
    }
    set parentIsHover(x9) {
        this.__parentIsHover.set(x9);
    }
    get parentCanHover() {
        return this.__parentCanHover.get();
    }
    set parentCanHover(w9) {
        this.__parentCanHover.set(w9);
    }
    get parentIsActive() {
        return this.__parentIsActive.get();
    }
    set parentIsActive(v9) {
        this.__parentIsActive.set(v9);
    }
    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }
    set parentFrontColor(u9) {
        this.__parentFrontColor.set(u9);
    }
    get isParentCanTouch() {
        return this.__isParentCanTouch.get();
    }
    set isParentCanTouch(t9) {
        this.__isParentCanTouch.set(t9);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(s9) {
        this.__parentDirection.set(s9);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(r9) {
        this.__isFocus.set(r9);
    }
    get secondaryTextSize() {
        return this.__secondaryTextSize.get();
    }
    set secondaryTextSize(q9) {
        this.__secondaryTextSize.set(q9);
    }
    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }
    set secondaryTextColors(p9) {
        this.__secondaryTextColors.set(p9);
    }
    get iconSize() {
        return this.__iconSize.get();
    }
    set iconSize(o9) {
        this.__iconSize.set(o9);
    }
    get iconColor() {
        return this.__iconColor.get();
    }
    set iconColor(n9) {
        this.__iconColor.set(n9);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(m9) {
        this.__isOnClick.set(m9);
    }
    onWillApplyTheme(l9) {
        this.secondaryTextColor = l9.colors.fontSecondary;
        this.hoveringColor = l9.colors.interactiveHover;
        this.activedColor = l9.colors.interactiveActive;
    }
    onFocusChange() {
        this.secondaryTextSize = this.isFocus ? { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_right_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.secondaryTextColors = this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_right_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.iconSize = this.isFocus ? { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_right_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
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
    createButton(w8 = null) {
        this.observeComponentCreation2((e9, f9) => {
            Button.createWithChild();
            Button.focusable(FOCUSABLE);
            Button.hitTestBehavior(HitTestMode.Block);
            Button.buttonStyle(ButtonStyleMode.NORMAL);
            Button.controlSize(ControlSize.SMALL);
            Button.constraintSize({
                minHeight: BUTTON_SIZE
            });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((k9) => {
                if (k9.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (k9.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((j9) => {
                this.parentCanHover = false;
                if (j9 && this.parentFrontColor === HOVERING_COLOR) {
                    this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
                }
                if (!j9) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR :
                            (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((c9, d9) => {
            Row.create();
            Row.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
            });
            Row.focusable(FOCUSABLE);
        }, Row);
        this.observeComponentCreation2((a9, b9) => {
            Text.create(this.button?.text);
            Text.focusable(FOCUSABLE);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(i8, j8 = null) {
        this.observeComponentCreation2((o8, p8) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.focusable(FOCUSABLE);
            Button.margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL2) });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((v8) => {
                if (v8.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (v8.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((u8) => {
                this.parentCanHover = false;
                if (u8 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!u8) {
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
            Button.onClick(i8.icon?.action);
        }, Button);
        this.observeComponentCreation2((m8, n8) => {
            Image.create(i8.icon?.value);
            Image.height(this.iconSize || OPERATEITEM_ICONLIKE_SIZE);
            Image.width(this.iconSize || OPERATEITEM_ICONLIKE_SIZE);
            Image.focusable(FOCUSABLE);
            Image.fillColor(this.iconColor || { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createImage(d8 = null) {
        this.observeComponentCreation2((f8, g8) => {
            Image.create(this.image);
            Image.height(OPERATEITEM_IMAGE_SIZE);
            Image.width(OPERATEITEM_IMAGE_SIZE);
            Image.draggable(false);
            Image.onAppear(() => {
                this.isParentCanTouch = true;
            });
            Image.focusable(FOCUSABLE);
        }, Image);
    }
    createText(y7 = null) {
        this.observeComponentCreation2((a8, b8) => {
            Text.create(this.text);
            Text.fontSize(this.secondaryTextSize || { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(this.secondaryTextColors || this.secondaryTextColor);
            Text.textOverflow({
                overflow: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_right_textOverflow'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                    .value === 1 ? TextOverflow.MARQUEE : TextOverflow.None
            });
            Text.marqueeOptions({
                start: this.isFocus,
                fadeout: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_marqueeOptions_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value === 1
            });
            Text.maxLines(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_maxLines_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value === 1 ? 1 : null);
            Text.focusable(FOCUSABLE);
            Text.draggable(false);
            Text.flexShrink(1);
            Text.onAppear(() => {
                this.isParentCanTouch = true;
            });
        }, Text);
        Text.pop();
    }
    createArrow(l7 = null) {
        this.observeComponentCreation2((q7, r7) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.focusable(FOCUSABLE);
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((x7) => {
                if (x7.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (x7.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((w7) => {
                this.parentCanHover = false;
                if (w7 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!w7) {
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
            Button.onClick(this.arrow?.action);
        }, Button);
        this.observeComponentCreation2((o7, p7) => {
            Image.create(this.arrow?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.focusable(FOCUSABLE);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createRadio(b7 = null) {
        this.observeComponentCreation2((d7, e7) => {
            Radio.create({ value: '', group: '' });
            Radio.margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL1) });
            Radio.checked(this.radioState);
            Radio.onChange(this.radio?.onChange);
            Radio.height(OPERATEITEM_ICONLIKE_SIZE);
            Radio.width(OPERATEITEM_ICONLIKE_SIZE);
            Radio.focusable(FOCUSABLE);
            Radio.onFocus(() => {
                this.parentCanFocus = false;
            });
            Radio.hitTestBehavior(HitTestMode.Block);
            Radio.onTouch((k7) => {
                if (k7.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (k7.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Radio.onHover((j7) => {
                this.parentCanHover = false;
                if (j7 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!j7) {
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
    createCheckBox(r6 = null) {
        this.observeComponentCreation2((t6, u6) => {
            Checkbox.create();
            Checkbox.margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL1) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange(this.checkBox?.onChange);
            Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.width(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.focusable(FOCUSABLE);
            Checkbox.onFocus(() => {
                this.parentCanFocus = false;
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.onTouch((a7) => {
                if (a7.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (a7.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Checkbox.onHover((z6) => {
                this.parentCanHover = false;
                if (z6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!z6) {
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
    createSwitch(e6 = null) {
        this.observeComponentCreation2((k6, l6) => {
            Row.create();
            Row.focusable(FOCUSABLE);
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onTouch((q6) => {
                if (q6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (q6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Row.onHover((p6) => {
                this.parentCanHover = false;
                if (p6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!p6) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((h6, i6) => {
            Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
            Toggle.onChange(this.switch?.onChange);
            Toggle.onClick(() => {
                this.switchState = !this.switchState;
            });
            Toggle.hitTestBehavior(HitTestMode.Block);
        }, Toggle);
        Toggle.pop();
        Row.pop();
    }
    createTextArrow(l5 = null) {
        this.observeComponentCreation2((w5, x5) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.focusable(FOCUSABLE);
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((d6) => {
                if (d6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (d6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((c6) => {
                this.parentCanHover = false;
                if (c6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!c6) {
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
            Button.onClick(this.arrow?.action);
        }, Button);
        this.observeComponentCreation2((u5, v5) => {
            Row.create({ space: SPECICAL_ROW_SPACE });
        }, Row);
        this.observeComponentCreation2((s5, t5) => {
            Text.create(this.text);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.focusable(FOCUSABLE);
            Text.draggable(false);
            Text.constraintSize({
                maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((q5, r5) => {
            Image.create(this.arrow?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.focusable(FOCUSABLE);
            Image.draggable(false);
        }, Image);
        Row.pop();
        Button.pop();
    }
    getFlexOptions() {
        let k5 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            k5.justifyContent = FlexAlign.SpaceBetween;
        }
        else {
            k5.space = { main: LengthMetrics.vp(this.rowSpace) };
            k5.justifyContent = FlexAlign.End;
        }
        return k5;
    }
    initialRender() {
        this.observeComponentCreation2((i5, j5) => {
            Flex.create(this.getFlexOptions());
            Flex.flexShrink(1);
            Flex.constraintSize({ minWidth: this.rightWidth });
        }, Flex);
        this.observeComponentCreation2((i4, j4) => {
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
                    this.observeComponentCreation2((x4, y4) => {
                        If.create();
                        if (this.parentDirection === FlexDirection.Column) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((c5, d5) => {
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
                    this.observeComponentCreation2((n4, o4) => {
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
    constructor(a4, b4, c4, d4 = -1, e4 = undefined, f4) {
        super(a4, c4, d4, f4);
        if (typeof e4 === "function") {
            this.paramsGenerator_ = e4;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(b4.contentItem, this, "contentItem");
        this.__operateItem = new SynchedPropertyObjectOneWayPU(b4.operateItem, this, "operateItem");
        this.__itemSpace = new SynchedPropertySimpleOneWayPU(b4.itemSpace, this, "itemSpace");
        this.__composeItemPadding = new SynchedPropertyObjectOneWayPU(b4.composeItemPadding, this, "composeItemPadding");
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
        this.setInitiallyProvidedValue(b4);
        this.declareWatch("contentItem", this.onPropChange);
        this.declareWatch("operateItem", this.onPropChange);
        this.declareWatch("fontSizeScale", this.onFontSizeScaleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z3) {
        if (z3.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (z3.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (z3.itemSpace === undefined) {
            this.__itemSpace.set(DEFAULT_ITEM_SPACE_WIDTH);
        }
        if (z3.composeItemPadding === undefined) {
            this.__composeItemPadding.set(null);
        }
        if (z3.frontColor !== undefined) {
            this.frontColor = z3.frontColor;
        }
        if (z3.borderSize !== undefined) {
            this.borderSize = z3.borderSize;
        }
        if (z3.canFocus !== undefined) {
            this.canFocus = z3.canFocus;
        }
        if (z3.canTouch !== undefined) {
            this.canTouch = z3.canTouch;
        }
        if (z3.canHover !== undefined) {
            this.canHover = z3.canHover;
        }
        if (z3.isHover !== undefined) {
            this.isHover = z3.isHover;
        }
        if (z3.itemHeight !== undefined) {
            this.itemHeight = z3.itemHeight;
        }
        if (z3.isActive !== undefined) {
            this.isActive = z3.isActive;
        }
        if (z3.hoveringColor !== undefined) {
            this.hoveringColor = z3.hoveringColor;
        }
        if (z3.touchDownColor !== undefined) {
            this.touchDownColor = z3.touchDownColor;
        }
        if (z3.activedColor !== undefined) {
            this.activedColor = z3.activedColor;
        }
        if (z3.focusOutlineColor !== undefined) {
            this.focusOutlineColor = z3.focusOutlineColor;
        }
        if (z3.isCanTouch !== undefined) {
            this.isCanTouch = z3.isCanTouch;
        }
        if (z3.fontSizeScale !== undefined) {
            this.fontSizeScale = z3.fontSizeScale;
        }
        if (z3.containerDirection !== undefined) {
            this.containerDirection = z3.containerDirection;
        }
        if (z3.contentItemDirection !== undefined) {
            this.contentItemDirection = z3.contentItemDirection;
        }
        if (z3.containerPadding !== undefined) {
            this.containerPadding = z3.containerPadding;
        }
        if (z3.callbackId !== undefined) {
            this.callbackId = z3.callbackId;
        }
        if (z3.isFocus !== undefined) {
            this.isFocus = z3.isFocus;
        }
        if (z3.isHoverBlend !== undefined) {
            this.isHoverBlend = z3.isHoverBlend;
        }
        if (z3.isOnClick !== undefined) {
            this.isOnClick = z3.isOnClick;
        }
    }
    updateStateVars(y3) {
        this.__contentItem.reset(y3.contentItem);
        this.__operateItem.reset(y3.operateItem);
        this.__itemSpace.reset(y3.itemSpace);
        this.__composeItemPadding.reset(y3.composeItemPadding);
    }
    purgeVariableDependenciesOnElmtId(x3) {
        this.__contentItem.purgeDependencyOnElmtId(x3);
        this.__operateItem.purgeDependencyOnElmtId(x3);
        this.__itemSpace.purgeDependencyOnElmtId(x3);
        this.__composeItemPadding.purgeDependencyOnElmtId(x3);
        this.__frontColor.purgeDependencyOnElmtId(x3);
        this.__borderSize.purgeDependencyOnElmtId(x3);
        this.__canFocus.purgeDependencyOnElmtId(x3);
        this.__canTouch.purgeDependencyOnElmtId(x3);
        this.__canHover.purgeDependencyOnElmtId(x3);
        this.__isHover.purgeDependencyOnElmtId(x3);
        this.__itemHeight.purgeDependencyOnElmtId(x3);
        this.__isActive.purgeDependencyOnElmtId(x3);
        this.__hoveringColor.purgeDependencyOnElmtId(x3);
        this.__touchDownColor.purgeDependencyOnElmtId(x3);
        this.__activedColor.purgeDependencyOnElmtId(x3);
        this.__focusOutlineColor.purgeDependencyOnElmtId(x3);
        this.__isCanTouch.purgeDependencyOnElmtId(x3);
        this.__fontSizeScale.purgeDependencyOnElmtId(x3);
        this.__containerDirection.purgeDependencyOnElmtId(x3);
        this.__contentItemDirection.purgeDependencyOnElmtId(x3);
        this.__containerPadding.purgeDependencyOnElmtId(x3);
        this.__isFocus.purgeDependencyOnElmtId(x3);
        this.__isHoverBlend.purgeDependencyOnElmtId(x3);
        this.__isOnClick.purgeDependencyOnElmtId(x3);
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
    set contentItem(w3) {
        this.__contentItem.set(w3);
    }
    get operateItem() {
        return this.__operateItem.get();
    }
    set operateItem(v3) {
        this.__operateItem.set(v3);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(u3) {
        this.__itemSpace.set(u3);
    }
    get composeItemPadding() {
        return this.__composeItemPadding.get();
    }
    set composeItemPadding(t3) {
        this.__composeItemPadding.set(t3);
    }
    get frontColor() {
        return this.__frontColor.get();
    }
    set frontColor(s3) {
        this.__frontColor.set(s3);
    }
    get borderSize() {
        return this.__borderSize.get();
    }
    set borderSize(r3) {
        this.__borderSize.set(r3);
    }
    get canFocus() {
        return this.__canFocus.get();
    }
    set canFocus(q3) {
        this.__canFocus.set(q3);
    }
    get canTouch() {
        return this.__canTouch.get();
    }
    set canTouch(p3) {
        this.__canTouch.set(p3);
    }
    get canHover() {
        return this.__canHover.get();
    }
    set canHover(o3) {
        this.__canHover.set(o3);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(n3) {
        this.__isHover.set(n3);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(m3) {
        this.__itemHeight.set(m3);
    }
    get isActive() {
        return this.__isActive.get();
    }
    set isActive(l3) {
        this.__isActive.set(l3);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(k3) {
        this.__hoveringColor.set(k3);
    }
    get touchDownColor() {
        return this.__touchDownColor.get();
    }
    set touchDownColor(j3) {
        this.__touchDownColor.set(j3);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(i3) {
        this.__activedColor.set(i3);
    }
    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }
    set focusOutlineColor(h3) {
        this.__focusOutlineColor.set(h3);
    }
    get isCanTouch() {
        return this.__isCanTouch.get();
    }
    set isCanTouch(g3) {
        this.__isCanTouch.set(g3);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(f3) {
        this.__fontSizeScale.set(f3);
    }
    get containerDirection() {
        return this.__containerDirection.get();
    }
    set containerDirection(e3) {
        this.__containerDirection.set(e3);
    }
    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }
    set contentItemDirection(d3) {
        this.__contentItemDirection.set(d3);
    }
    get containerPadding() {
        return this.__containerPadding.get();
    }
    set containerPadding(c3) {
        this.__containerPadding.set(c3);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(b3) {
        this.__isFocus.set(b3);
    }
    get isHoverBlend() {
        return this.__isHoverBlend.get();
    }
    set isHoverBlend(a3) {
        this.__isHoverBlend.set(a3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(z2) {
        this.__isOnClick.set(z2);
    }
    onWillApplyTheme(y2) {
        this.hoveringColor = y2.colors.interactiveHover;
        this.touchDownColor = y2.colors.interactivePressed;
        this.activedColor = y2.colors.interactiveActive;
        this.focusOutlineColor = y2.colors.interactiveFocus;
    }
    onPropChange() {
        this.onFontSizeScaleChange();
        this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString();
        if (this.contentItem === undefined) {
            if (this.operateItem?.image !== undefined ||
                this.operateItem?.icon !== undefined ||
                this.operateItem?.subIcon !== undefined) {
                this.itemHeight = getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) || (OPERATEITEM_IMAGE_SIZE + SAFE_LIST_PADDING);
            }
            return;
        }
        if (this.contentItem?.secondaryText === undefined && this.contentItem?.description === undefined) {
            if (this.contentItem?.icon === undefined) {
                this.itemHeight = ItemHeight.FIRST_HEIGHT;
            }
            else {
                this.itemHeight = this.contentItem.iconStyle <= IconType.HEAD_SCULPTURE ?
                    ItemHeight.SECOND_HEIGHT : ItemHeight.THIRD_HEIGHT;
            }
        }
        else if (this.contentItem.description === undefined) {
            if (this.contentItem.icon === undefined ||
                (this.contentItem.icon !== undefined && this.contentItem.iconStyle <= IconType.SYSTEM_ICON)) {
                this.itemHeight = getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_system_icon_line_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) || ItemHeight.THIRD_HEIGHT;
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
        let x2 = this.composeItemPadding?.start?.value ?? STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return `calc(100% - ${x2}vp)`;
        }
        else if (this.operateItem !== null &&
            this.operateItem.button === undefined &&
            this.operateItem.text === undefined) {
            if (this.operateItem.subIcon !== null) {
                return `calc(100% - ${x2}vp - ${OPERATEITEM_ICON_CLICKABLE_SIZE}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
            }
            else {
                return `calc(100% - ${x2}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
            }
        }
        else {
            return `calc(66% - ${x2}vp)`;
        }
    }
    calculatedRightWidth() {
        let w2 = this.composeItemPadding?.end !== undefined ? this.composeItemPadding?.end?.value : STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return RIGHT_CONTENT_NULL_RIGHTWIDTH;
        }
        else if (this.operateItem !== null && this.operateItem.text === undefined) {
            if (this.operateItem.subIcon !== null) {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${RIGHT_ONLY_ARROW_WIDTH} + ${w2}vp)`;
            }
            else {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${w2}vp)`;
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
    setContainerPadding(s2, t2, u2, v2) {
        this.containerPadding = {
            top: s2,
            bottom: t2,
            left: u2,
            right: v2,
        };
    }
    getContainerPadding() {
        if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL3) {
            this.setContainerPadding({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null);
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL2) {
            this.setContainerPadding({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null);
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1) {
            this.setContainerPadding({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null);
        }
        else {
            this.setContainerPadding({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null);
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
        let r2 = ICON_SIZE_MAP.get(this.contentItem?.iconStyle);
        if (r2 && r2 <= HEADSCULPTURE_SIZE) {
            return LengthMetrics.vp(r2 + (this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH));
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
            this.composeItemPadding?.start : LengthMetrics.vp(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_margin_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) || STACK_PADDING);
    }
    getComposeItemRightPadding() {
        return this.composeItemPadding?.end !== undefined ?
            this.composeItemPadding?.end : LengthMetrics.vp(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_margin_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) || STACK_PADDING);
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
    onMeasureSize(j2, k2, l2) {
        let m2 = { height: 0, width: 0 };
        let n2 = this.getUIContext().getHostContext();
        this.fontSizeScale = n2.config?.fontSizeScale ?? 1;
        k2.forEach((p2) => {
            let q2 = p2.measure(l2);
            m2.width = q2.width;
            m2.height = q2.height;
        });
        return m2;
    }
    initialRender() {
        this.observeComponentCreation2((h2, i2) => {
            Stack.create();
            Stack.padding({
                start: this.getComposeItemLeftPadding(),
                end: this.getComposeItemRightPadding()
            });
        }, Stack);
        this.observeComponentCreation2((y1, z1) => {
            Flex.create(this.getFlexOptions());
            Flex.pointLight({ illuminated: IlluminatedType.BORDER });
            Flex.constraintSize({ minHeight: this.itemHeight });
            Flex.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Flex.backgroundColor(ObservedObject.GetRawObject(this.frontColor));
            Flex.onFocus(() => {
                this.canFocus = true;
                this.isFocus = true;
                this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_backboard'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString();
            });
            Flex.onClick(() => {
                this.isOnClick = !this.isOnClick;
            });
            Flex.pointLight({ illuminated: IlluminatedType.BORDER });
            Flex.onBlur(() => {
                this.canFocus = false;
                this.isFocus = false;
                this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString();
            });
            Flex.onHover((g2) => {
                this.isHoverBlend = g2;
                this.isHover = g2;
                if (this.canHover) {
                    this.frontColor = g2 ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
                this.frontColor = g2 ? ({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || this.hoveringColor) :
                    ({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString());
            });
            Flex.onTouch((f2) => {
                if (this.isCanTouch) {
                    if (f2.type === TouchType.Down && this.canTouch) {
                        this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_press'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || this.touchDownColor;
                    }
                    if (f2.type === TouchType.Up) {
                        this.frontColor = this.isActive ? this.activedColor : ({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString());
                    }
                }
            });
            ViewStackProcessor.visualState("focused");
            Flex.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_circular_bead'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_border'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || ITEM_BORDER_SHOWN,
                color: { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_border_focused'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || this.focusOutlineColor,
                style: BorderStyle.Solid
            });
            Flex.scale({
                x: getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_magnification'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                y: getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_magnification'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
            } || null);
            Flex.shadow({
                radius: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_circular_bead'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: Color.Transparent,
                offsetX: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_shadow_attribute'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
                offsetY: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_shadow_attribute'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
            });
            ViewStackProcessor.visualState("normal");
            Flex.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_radio'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_stroke_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent,
                width: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_stroke_thickness'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
            });
            Flex.blur(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_fuzzy_value'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }));
            Flex.shadow({
                radius: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_radio'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: Color.Transparent,
                offsetX: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_shadow_attribute'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
                offsetY: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_shadow_attribute'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
            });
            ViewStackProcessor.visualState();
            Flex.padding(ObservedObject.GetRawObject(this.containerPadding));
        }, Flex);
        this.observeComponentCreation2((k1, l1) => {
            If.create();
            if (this.contentItem === null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w1, x1) => {
                        __Common__.create();
                        __Common__.focusable(FOCUSABLE);
                    }, __Common__);
                    {
                        this.observeComponentCreation2((q1, r1) => {
                            if (r1) {
                                let s1 = new ContentItemStruct(this, {}, undefined, q1, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1019, col: 11 });
                                ViewPU.create(s1);
                                let t1 = () => {
                                    return {};
                                };
                                s1.paramsGenerator_ = t1;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(q1, {});
                            }
                        }, { name: "ContentItemStruct" });
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
        this.observeComponentCreation2((w, x) => {
            If.create();
            if (this.contentItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i1, j1) => {
                        __Common__.create();
                        __Common__.focusable(FOCUSABLE);
                    }, __Common__);
                    {
                        this.observeComponentCreation2((c1, d1) => {
                            if (d1) {
                                let e1 = new ContentItemStruct(this, {
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
                                }, undefined, c1, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1022, col: 11 });
                                ViewPU.create(e1);
                                let f1 = () => {
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
                                e1.paramsGenerator_ = f1;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(c1, {
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
                    __Common__.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((g, h) => {
            If.create();
            if (this.operateItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s, t) => {
                        __Common__.create();
                        __Common__.focusable(FOCUSABLE);
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
                        this.observeComponentCreation2((m, n) => {
                            if (n) {
                                let o = new OperateItemStruct(this, {
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
                                    isOnClick: this.isOnClick,
                                }, undefined, m, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1043, col: 11 });
                                ViewPU.create(o);
                                let p = () => {
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
                                o.paramsGenerator_ = p;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(m, {
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
                                    parentDirection: this.containerDirection,
                                    isOnClick: this.isOnClick
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
function getNumberByResource(a) {
    try {
        return resourceManager.getSystemResourceManager().getNumber(a);
    }
    catch {
        return null;
    }
}

export default { IconType, ComposeListItem };
