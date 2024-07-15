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
const resourceManager = requireNapi('resourceManager').resourceManager;
export var IconType;
(function (IconType) {
    IconType[IconType["BADGE"] = 1] = "BADGE";
    IconType[IconType["NORMAL_ICON"] = 2] = "NORMAL_ICON";
    IconType[IconType["SYSTEM_ICON"] = 3] = "SYSTEM_ICON";
    IconType[IconType["HEAD_SCULPTURE"] = 4] = "HEAD_SCULPTURE";
    IconType[IconType["APP_ICON"] = 5] = "APP_ICON";
    IconType[IconType["PREVIEW"] = 6] = "PREVIEW";
    IconType[IconType["LONGITUDINAL"] = 7] = "LONGITUDINAL";
    IconType[IconType["VERTICAL"] = 8] = "VERTICAL";
})(IconType || (IconType = {}));
var ItemHeight;
(function (ItemHeight) {
    ItemHeight[ItemHeight["FIRST_HEIGHT"] = 48] = "FIRST_HEIGHT";
    ItemHeight[ItemHeight["SECOND_HEIGHT"] = 56] = "SECOND_HEIGHT";
    ItemHeight[ItemHeight["THIRD_HEIGHT"] = 64] = "THIRD_HEIGHT";
    ItemHeight[ItemHeight["FOURTH_HEIGHT"] = 72] = "FOURTH_HEIGHT";
    ItemHeight[ItemHeight["FIFTH_HEIGHT"] = 96] = "FIFTH_HEIGHT";
})(ItemHeight || (ItemHeight = {}));
var FontSizeScaleLevel;
(function (FontSizeScaleLevel) {
    FontSizeScaleLevel[FontSizeScaleLevel["LEVEL1"] = 1.75] = "LEVEL1";
    FontSizeScaleLevel[FontSizeScaleLevel["LEVEL2"] = 2] = "LEVEL2";
    FontSizeScaleLevel[FontSizeScaleLevel["LEVEL3"] = 3.2] = "LEVEL3";
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
class ContentItemStruct extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(params.iconStyle, this, "iconStyle");
        this.__icon = new SynchedPropertyObjectOneWayPU(params.icon, this, "icon");
        this.__primaryText = new SynchedPropertyObjectOneWayPU(params.primaryText, this, "primaryText");
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(params.secondaryText, this, "secondaryText");
        this.__description = new SynchedPropertyObjectOneWayPU(params.description, this, "description");
        this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(params.leftWidth, this, "leftWidth");
        this.__primaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColor");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__descriptionColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "descriptionColor");
        this.__iconImageModifier = new SynchedPropertyObjectOneWayPU(params.iconImageModifier, this, "iconImageModifier");
        this.__primaryTextModifier = new SynchedPropertyObjectOneWayPU(params.primaryTextModifier, this, "primaryTextModifier");
        this.__secondaryTextModifier = new SynchedPropertyObjectOneWayPU(params.secondaryTextModifier, this, "secondaryTextModifier");
        this.__descriptionModifier = new SynchedPropertyObjectOneWayPU(params.descriptionModifier, this, "descriptionModifier");
        this.__contentItemPadding = new SynchedPropertyObjectOneWayPU(params.contentItemPadding, this, "contentItemPadding");
        this.__itemSpace = new SynchedPropertyObjectOneWayPU(params.itemSpace, this, "itemSpace");
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(params.fontSizeScale, this, "fontSizeScale");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(params.parentDirection, this, "parentDirection");
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(params.itemDirection, this, "itemDirection");
        this.__isFocus = new SynchedPropertySimpleOneWayPU(params.isFocus, this, "isFocus");
        this.__primaryTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextSize");
        this.__primaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColors");
        this.__itemHeight = new SynchedPropertyObjectOneWayPU(params.itemHeight, this, "itemHeight");
        this.__iconMagnitude = new ObservedPropertyObjectPU(null, this, "iconMagnitude");
        this.__iconHue = new ObservedPropertyObjectPU(null, this, "iconHue");
        this.__itemSpaces = new ObservedPropertyObjectPU(null, this, "itemSpaces");
        this.setInitiallyProvidedValue(params);
        this.declareWatch("iconStyle", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("primaryText", this.onPropChange);
        this.declareWatch("secondaryText", this.onPropChange);
        this.declareWatch("description", this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (params.icon === undefined) {
            this.__icon.set(null);
        }
        if (params.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (params.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (params.description === undefined) {
            this.__description.set(null);
        }
        if (params.itemRowSpace !== undefined) {
            this.itemRowSpace = params.itemRowSpace;
        }
        if (params.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (params.primaryTextColor !== undefined) {
            this.primaryTextColor = params.primaryTextColor;
        }
        if (params.secondaryTextColor !== undefined) {
            this.secondaryTextColor = params.secondaryTextColor;
        }
        if (params.descriptionColor !== undefined) {
            this.descriptionColor = params.descriptionColor;
        }
        if (params.iconImageModifier === undefined) {
            this.__iconImageModifier.set(null);
        }
        if (params.primaryTextModifier === undefined) {
            this.__primaryTextModifier.set(null);
        }
        if (params.secondaryTextModifier === undefined) {
            this.__secondaryTextModifier.set(null);
        }
        if (params.descriptionModifier === undefined) {
            this.__descriptionModifier.set(null);
        }
        if (params.contentItemPadding === undefined) {
            this.__contentItemPadding.set(null);
        }
        if (params.itemSpace === undefined) {
            this.__itemSpace.set(DEFAULT_ITEM_SPACE_WIDTH);
        }
        if (params.isFocus === undefined) {
            this.__isFocus.set(false);
        }
        if (params.primaryTextSize !== undefined) {
            this.primaryTextSize = params.primaryTextSize;
        }
        if (params.primaryTextColors !== undefined) {
            this.primaryTextColors = params.primaryTextColors;
        }
        if (params.itemHeight === undefined) {
            this.__itemHeight.set(null);
        }
        if (params.iconMagnitude !== undefined) {
            this.iconMagnitude = params.iconMagnitude;
        }
        if (params.iconHue !== undefined) {
            this.iconHue = params.iconHue;
        }
        if (params.itemSpaces !== undefined) {
            this.itemSpaces = params.itemSpaces;
        }
    }
    updateStateVars(params) {
        this.__iconStyle.reset(params.iconStyle);
        this.__icon.reset(params.icon);
        this.__primaryText.reset(params.primaryText);
        this.__secondaryText.reset(params.secondaryText);
        this.__description.reset(params.description);
        this.__leftWidth.reset(params.leftWidth);
        this.__iconImageModifier.reset(params.iconImageModifier);
        this.__primaryTextModifier.reset(params.primaryTextModifier);
        this.__secondaryTextModifier.reset(params.secondaryTextModifier);
        this.__descriptionModifier.reset(params.descriptionModifier);
        this.__contentItemPadding.reset(params.contentItemPadding);
        this.__itemSpace.reset(params.itemSpace);
        this.__fontSizeScale.reset(params.fontSizeScale);
        this.__parentDirection.reset(params.parentDirection);
        this.__itemDirection.reset(params.itemDirection);
        this.__isFocus.reset(params.isFocus);
        this.__itemHeight.reset(params.itemHeight);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__iconStyle.purgeDependencyOnElmtId(rmElmtId);
        this.__icon.purgeDependencyOnElmtId(rmElmtId);
        this.__primaryText.purgeDependencyOnElmtId(rmElmtId);
        this.__secondaryText.purgeDependencyOnElmtId(rmElmtId);
        this.__description.purgeDependencyOnElmtId(rmElmtId);
        this.__leftWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__primaryTextColor.purgeDependencyOnElmtId(rmElmtId);
        this.__secondaryTextColor.purgeDependencyOnElmtId(rmElmtId);
        this.__descriptionColor.purgeDependencyOnElmtId(rmElmtId);
        this.__iconImageModifier.purgeDependencyOnElmtId(rmElmtId);
        this.__primaryTextModifier.purgeDependencyOnElmtId(rmElmtId);
        this.__secondaryTextModifier.purgeDependencyOnElmtId(rmElmtId);
        this.__descriptionModifier.purgeDependencyOnElmtId(rmElmtId);
        this.__contentItemPadding.purgeDependencyOnElmtId(rmElmtId);
        this.__itemSpace.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
        this.__parentDirection.purgeDependencyOnElmtId(rmElmtId);
        this.__itemDirection.purgeDependencyOnElmtId(rmElmtId);
        this.__isFocus.purgeDependencyOnElmtId(rmElmtId);
        this.__primaryTextSize.purgeDependencyOnElmtId(rmElmtId);
        this.__primaryTextColors.purgeDependencyOnElmtId(rmElmtId);
        this.__itemHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__iconMagnitude.purgeDependencyOnElmtId(rmElmtId);
        this.__iconHue.purgeDependencyOnElmtId(rmElmtId);
        this.__itemSpaces.purgeDependencyOnElmtId(rmElmtId);
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
    set iconStyle(newValue) {
        this.__iconStyle.set(newValue);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(newValue) {
        this.__icon.set(newValue);
    }
    get primaryText() {
        return this.__primaryText.get();
    }
    set primaryText(newValue) {
        this.__primaryText.set(newValue);
    }
    get secondaryText() {
        return this.__secondaryText.get();
    }
    set secondaryText(newValue) {
        this.__secondaryText.set(newValue);
    }
    get description() {
        return this.__description.get();
    }
    set description(newValue) {
        this.__description.set(newValue);
    }
    get leftWidth() {
        return this.__leftWidth.get();
    }
    set leftWidth(newValue) {
        this.__leftWidth.set(newValue);
    }
    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }
    set primaryTextColor(newValue) {
        this.__primaryTextColor.set(newValue);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(newValue) {
        this.__secondaryTextColor.set(newValue);
    }
    get descriptionColor() {
        return this.__descriptionColor.get();
    }
    set descriptionColor(newValue) {
        this.__descriptionColor.set(newValue);
    }
    get iconImageModifier() {
        return this.__iconImageModifier.get();
    }
    set iconImageModifier(newValue) {
        this.__iconImageModifier.set(newValue);
    }
    get primaryTextModifier() {
        return this.__primaryTextModifier.get();
    }
    set primaryTextModifier(newValue) {
        this.__primaryTextModifier.set(newValue);
    }
    get secondaryTextModifier() {
        return this.__secondaryTextModifier.get();
    }
    set secondaryTextModifier(newValue) {
        this.__secondaryTextModifier.set(newValue);
    }
    get descriptionModifier() {
        return this.__descriptionModifier.get();
    }
    set descriptionModifier(newValue) {
        this.__descriptionModifier.set(newValue);
    }
    get contentItemPadding() {
        return this.__contentItemPadding.get();
    }
    set contentItemPadding(newValue) {
        this.__contentItemPadding.set(newValue);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(newValue) {
        this.__itemSpace.set(newValue);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(newValue) {
        this.__parentDirection.set(newValue);
    }
    get itemDirection() {
        return this.__itemDirection.get();
    }
    set itemDirection(newValue) {
        this.__itemDirection.set(newValue);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(newValue) {
        this.__isFocus.set(newValue);
    }
    get primaryTextSize() {
        return this.__primaryTextSize.get();
    }
    set primaryTextSize(newValue) {
        this.__primaryTextSize.set(newValue);
    }
    get primaryTextColors() {
        return this.__primaryTextColors.get();
    }
    set primaryTextColors(newValue) {
        this.__primaryTextColors.set(newValue);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(newValue) {
        this.__itemHeight.set(newValue);
    }
    get iconMagnitude() {
        return this.__iconMagnitude.get();
    }
    set iconMagnitude(newValue) {
        this.__iconMagnitude.set(newValue);
    }
    get iconHue() {
        return this.__iconHue.get();
    }
    set iconHue(newValue) {
        this.__iconHue.set(newValue);
    }
    get itemSpaces() {
        return this.__itemSpaces.get();
    }
    set itemSpaces(newValue) {
        this.__itemSpaces.set(newValue);
    }
    onWillApplyTheme(theme) {
        this.primaryTextColor = theme.colors.fontPrimary;
        this.secondaryTextColor = theme.colors.fontSecondary;
        this.descriptionColor = theme.colors.fontTertiary;
    }
    onPropChange() {
        if (this.icon == null && this.iconStyle == null) {
            this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
        }
        this.primaryTextSize = this.isFocus ? { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.primaryTextColors = this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    }
    setIconStyle() {
        switch (this.itemHeight) {
            case ItemHeight.SECOND_HEIGHT:
                if (this.iconStyle == IconType.SYSTEM_ICON) {
                    this.iconMagnitude = { "id": -1, "type": 10002, params: ['sys.float.composeListItem_fifty_eight_normal_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || SYSTEM_ICON_SIZE;
                    this.iconHue = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_fifty_eight_normal_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
                break;
            case ItemHeight.THIRD_HEIGHT:
                if (this.iconStyle == IconType.SYSTEM_ICON) {
                    this.iconMagnitude = { "id": -1, "type": 10002, params: ['sys.float.composeListItem_sixty_four_normal_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || SYSTEM_ICON_SIZE;
                    this.iconHue = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_sixty_four_normal_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
                break;
            case ItemHeight.FOURTH_HEIGHT:
                switch (this.iconStyle) {
                    case IconType.HEAD_SCULPTURE:
                        this.iconMagnitude = { "id": -1, "type": 10002, params: ['sys.float.composeListItem_seventy_two_normal_head_portrait_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || HEADSCULPTURE_SIZE;
                        this.itemSpace = getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_seventy_two_normal_head_portrait_and_text_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        break;
                    case IconType.PREVIEW:
                        this.iconMagnitude = { "id": -1, "type": 10002, params: ['sys.float.composeListItem_seventy_two_normal_preview_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || (BADGE_SIZE + HEADSCULPTURE_SIZE);
                        this.itemSpace = getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_seventy_two_normal_preview_and_text_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        break;
                }
                break;
            case (ItemHeight.FIFTH_HEIGHT - ItemHeight.SECOND_HEIGHT) * 2:
                if (this.iconStyle == IconType.APP_ICON) {
                    this.iconMagnitude = { "id": -1, "type": 10002, params: ['sys.float.composeListItem_eighty_normal_app_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || (SMALL_ICON_SIZE + HEADSCULPTURE_SIZE);
                    this.itemSpace = getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_eighty_normal_app_icon_and_text_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                }
                break;
            case ItemHeight.FIFTH_HEIGHT:
                if (this.iconStyle == IconType.APP_ICON) {
                    this.iconMagnitude = { "id": -1, "type": 10002, params: ['sys.float.composeListItem_ninety_six_normal_app_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || (SMALL_ICON_SIZE + HEADSCULPTURE_SIZE);
                    this.itemSpace = getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_ninety_six_normal_app_icon_and_text_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                }
                break;
            default:
                this.iconMagnitude = null;
                this.iconHue = null;
                this.itemSpace = null;
                break;
        }
    }
    aboutToAppear() {
        this.onPropChange();
        this.setIconStyle();
    }
    createIcon(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.icon != null && this.iconStyle != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.iconStyle <= IconType.PREVIEW) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Image.create(this.icon);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.width(this.iconMagnitude || ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.height(this.iconMagnitude || ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.focusable(true);
                                    Image.draggable(false);
                                    Image.fillColor(this.iconHue || { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.iconImageModifier));
                                    Image.flexShrink(0);
                                }, Image);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    createText(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.primaryText);
            Text.fontSize(this.primaryTextSize || { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(this.primaryTextColors || this.primaryTextColor);
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(true);
            Text.draggable(false);
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTextModifier));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.secondaryText);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.description);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(ObservedObject.GetRawObject(this.descriptionColor));
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(params.arrow, this, "arrow");
        this.__icon = new SynchedPropertyObjectOneWayPU(params.icon, this, "icon");
        this.__subIcon = new SynchedPropertyObjectOneWayPU(params.subIcon, this, "subIcon");
        this.__button = new SynchedPropertyObjectOneWayPU(params.button, this, "button");
        this.__switch = new SynchedPropertyObjectOneWayPU(params.switch, this, "switch");
        this.__checkBox = new SynchedPropertyObjectOneWayPU(params.checkBox, this, "checkBox");
        this.__radio = new SynchedPropertyObjectOneWayPU(params.radio, this, "radio");
        this.__image = new SynchedPropertyObjectOneWayPU(params.image, this, "image");
        this.__text = new SynchedPropertyObjectOneWayPU(params.text, this, "text");
        this.__switchState = new ObservedPropertySimplePU(false, this, "switchState");
        this.__radioState = new ObservedPropertySimplePU(false, this, "radioState");
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, "checkBoxState");
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(params.rightWidth, this, "rightWidth");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, "hoveringColor");
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, "activedColor");
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(params.parentCanFocus, this, "parentCanFocus");
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(params.parentCanTouch, this, "parentCanTouch");
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(params.parentIsHover, this, "parentIsHover");
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(params.parentCanHover, this, "parentCanHover");
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(params.parentIsActive, this, "parentIsActive");
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(params.parentFrontColor, this, "parentFrontColor");
        this.__isParentCanTouch = new SynchedPropertySimpleTwoWayPU(params.isParentCanTouch, this, "isParentCanTouch");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(params.parentDirection, this, "parentDirection");
        this.rowSpace = DEFAULT_ROW_SPACE;
        this.__isFocus = new SynchedPropertySimpleOneWayPU(params.isFocus, this, "isFocus");
        this.__secondaryTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextSize");
        this.__secondaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColors");
        this.__iconSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "iconSize");
        this.__iconColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "iconColor");
        this.__isTextFocus = new ObservedPropertySimplePU(false, this, "isTextFocus");
        this.setInitiallyProvidedValue(params);
        this.declareWatch("arrow", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("subIcon", this.onPropChange);
        this.declareWatch("button", this.onPropChange);
        this.declareWatch("switch", this.onPropChange);
        this.declareWatch("checkBox", this.onPropChange);
        this.declareWatch("radio", this.onPropChange);
        this.declareWatch("image", this.onPropChange);
        this.declareWatch("text", this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (params.icon === undefined) {
            this.__icon.set(null);
        }
        if (params.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (params.button === undefined) {
            this.__button.set(null);
        }
        if (params.switch === undefined) {
            this.__switch.set(null);
        }
        if (params.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (params.radio === undefined) {
            this.__radio.set(null);
        }
        if (params.image === undefined) {
            this.__image.set(null);
        }
        if (params.text === undefined) {
            this.__text.set(null);
        }
        if (params.switchState !== undefined) {
            this.switchState = params.switchState;
        }
        if (params.radioState !== undefined) {
            this.radioState = params.radioState;
        }
        if (params.checkBoxState !== undefined) {
            this.checkBoxState = params.checkBoxState;
        }
        if (params.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (params.secondaryTextColor !== undefined) {
            this.secondaryTextColor = params.secondaryTextColor;
        }
        if (params.hoveringColor !== undefined) {
            this.hoveringColor = params.hoveringColor;
        }
        if (params.activedColor !== undefined) {
            this.activedColor = params.activedColor;
        }
        if (params.rowSpace !== undefined) {
            this.rowSpace = params.rowSpace;
        }
        if (params.isFocus === undefined) {
            this.__isFocus.set(false);
        }
        if (params.secondaryTextSize !== undefined) {
            this.secondaryTextSize = params.secondaryTextSize;
        }
        if (params.secondaryTextColors !== undefined) {
            this.secondaryTextColors = params.secondaryTextColors;
        }
        if (params.iconSize !== undefined) {
            this.iconSize = params.iconSize;
        }
        if (params.iconColor !== undefined) {
            this.iconColor = params.iconColor;
        }
        if (params.isTextFocus !== undefined) {
            this.isTextFocus = params.isTextFocus;
        }
    }
    updateStateVars(params) {
        this.__arrow.reset(params.arrow);
        this.__icon.reset(params.icon);
        this.__subIcon.reset(params.subIcon);
        this.__button.reset(params.button);
        this.__switch.reset(params.switch);
        this.__checkBox.reset(params.checkBox);
        this.__radio.reset(params.radio);
        this.__image.reset(params.image);
        this.__text.reset(params.text);
        this.__rightWidth.reset(params.rightWidth);
        this.__parentDirection.reset(params.parentDirection);
        this.__isFocus.reset(params.isFocus);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__arrow.purgeDependencyOnElmtId(rmElmtId);
        this.__icon.purgeDependencyOnElmtId(rmElmtId);
        this.__subIcon.purgeDependencyOnElmtId(rmElmtId);
        this.__button.purgeDependencyOnElmtId(rmElmtId);
        this.__switch.purgeDependencyOnElmtId(rmElmtId);
        this.__checkBox.purgeDependencyOnElmtId(rmElmtId);
        this.__radio.purgeDependencyOnElmtId(rmElmtId);
        this.__image.purgeDependencyOnElmtId(rmElmtId);
        this.__text.purgeDependencyOnElmtId(rmElmtId);
        this.__switchState.purgeDependencyOnElmtId(rmElmtId);
        this.__radioState.purgeDependencyOnElmtId(rmElmtId);
        this.__checkBoxState.purgeDependencyOnElmtId(rmElmtId);
        this.__rightWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__secondaryTextColor.purgeDependencyOnElmtId(rmElmtId);
        this.__hoveringColor.purgeDependencyOnElmtId(rmElmtId);
        this.__activedColor.purgeDependencyOnElmtId(rmElmtId);
        this.__parentCanFocus.purgeDependencyOnElmtId(rmElmtId);
        this.__parentCanTouch.purgeDependencyOnElmtId(rmElmtId);
        this.__parentIsHover.purgeDependencyOnElmtId(rmElmtId);
        this.__parentCanHover.purgeDependencyOnElmtId(rmElmtId);
        this.__parentIsActive.purgeDependencyOnElmtId(rmElmtId);
        this.__parentFrontColor.purgeDependencyOnElmtId(rmElmtId);
        this.__isParentCanTouch.purgeDependencyOnElmtId(rmElmtId);
        this.__parentDirection.purgeDependencyOnElmtId(rmElmtId);
        this.__isFocus.purgeDependencyOnElmtId(rmElmtId);
        this.__secondaryTextSize.purgeDependencyOnElmtId(rmElmtId);
        this.__secondaryTextColors.purgeDependencyOnElmtId(rmElmtId);
        this.__iconSize.purgeDependencyOnElmtId(rmElmtId);
        this.__iconColor.purgeDependencyOnElmtId(rmElmtId);
        this.__isTextFocus.purgeDependencyOnElmtId(rmElmtId);
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
        this.__isTextFocus.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get arrow() {
        return this.__arrow.get();
    }
    set arrow(newValue) {
        this.__arrow.set(newValue);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(newValue) {
        this.__icon.set(newValue);
    }
    get subIcon() {
        return this.__subIcon.get();
    }
    set subIcon(newValue) {
        this.__subIcon.set(newValue);
    }
    get button() {
        return this.__button.get();
    }
    set button(newValue) {
        this.__button.set(newValue);
    }
    get switch() {
        return this.__switch.get();
    }
    set switch(newValue) {
        this.__switch.set(newValue);
    }
    get checkBox() {
        return this.__checkBox.get();
    }
    set checkBox(newValue) {
        this.__checkBox.set(newValue);
    }
    get radio() {
        return this.__radio.get();
    }
    set radio(newValue) {
        this.__radio.set(newValue);
    }
    get image() {
        return this.__image.get();
    }
    set image(newValue) {
        this.__image.set(newValue);
    }
    get text() {
        return this.__text.get();
    }
    set text(newValue) {
        this.__text.set(newValue);
    }
    get switchState() {
        return this.__switchState.get();
    }
    set switchState(newValue) {
        this.__switchState.set(newValue);
    }
    get radioState() {
        return this.__radioState.get();
    }
    set radioState(newValue) {
        this.__radioState.set(newValue);
    }
    get checkBoxState() {
        return this.__checkBoxState.get();
    }
    set checkBoxState(newValue) {
        this.__checkBoxState.set(newValue);
    }
    get rightWidth() {
        return this.__rightWidth.get();
    }
    set rightWidth(newValue) {
        this.__rightWidth.set(newValue);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(newValue) {
        this.__secondaryTextColor.set(newValue);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(newValue) {
        this.__hoveringColor.set(newValue);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(newValue) {
        this.__activedColor.set(newValue);
    }
    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }
    set parentCanFocus(newValue) {
        this.__parentCanFocus.set(newValue);
    }
    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }
    set parentCanTouch(newValue) {
        this.__parentCanTouch.set(newValue);
    }
    get parentIsHover() {
        return this.__parentIsHover.get();
    }
    set parentIsHover(newValue) {
        this.__parentIsHover.set(newValue);
    }
    get parentCanHover() {
        return this.__parentCanHover.get();
    }
    set parentCanHover(newValue) {
        this.__parentCanHover.set(newValue);
    }
    get parentIsActive() {
        return this.__parentIsActive.get();
    }
    set parentIsActive(newValue) {
        this.__parentIsActive.set(newValue);
    }
    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }
    set parentFrontColor(newValue) {
        this.__parentFrontColor.set(newValue);
    }
    get isParentCanTouch() {
        return this.__isParentCanTouch.get();
    }
    set isParentCanTouch(newValue) {
        this.__isParentCanTouch.set(newValue);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(newValue) {
        this.__parentDirection.set(newValue);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(newValue) {
        this.__isFocus.set(newValue);
    }
    get secondaryTextSize() {
        return this.__secondaryTextSize.get();
    }
    set secondaryTextSize(newValue) {
        this.__secondaryTextSize.set(newValue);
    }
    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }
    set secondaryTextColors(newValue) {
        this.__secondaryTextColors.set(newValue);
    }
    get iconSize() {
        return this.__iconSize.get();
    }
    set iconSize(newValue) {
        this.__iconSize.set(newValue);
    }
    get iconColor() {
        return this.__iconColor.get();
    }
    set iconColor(newValue) {
        this.__iconColor.set(newValue);
    }
    get isTextFocus() {
        return this.__isTextFocus.get();
    }
    set isTextFocus(newValue) {
        this.__isTextFocus.set(newValue);
    }
    onWillApplyTheme(theme) {
        this.secondaryTextColor = theme.colors.fontSecondary;
        this.hoveringColor = theme.colors.interactiveHover;
        this.activedColor = theme.colors.interactiveActive;
    }
    onPropChange() {
        if (this.switch != null) {
            this.switchState = this.switch.isCheck;
        }
        if (this.radio != null) {
            this.radioState = this.radio.isCheck;
        }
        if (this.checkBox != null) {
            this.checkBoxState = this.checkBox.isCheck;
        }
        if ((this.button == null && this.image == null && this.icon != null && this.text != null) ||
            (this.button == null && this.image == null && this.icon == null && this.arrow != null && this.text != null)) {
            this.rowSpace = SPECICAL_ROW_SPACE;
        }
        this.secondaryTextSize = this.isFocus ? { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_right_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.secondaryTextColors = this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_right_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.iconSize = this.isFocus ? { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_right_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.iconColor = this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_right_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    }
    aboutToAppear() {
        this.onPropChange();
    }
    createButton(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            Button.onTouch((event) => {
                if (event.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (event.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((isHover) => {
                this.parentCanHover = false;
                if (isHover && this.parentFrontColor === HOVERING_COLOR) {
                    this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
                }
                if (!isHover) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR :
                            (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(param, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL2) });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.onFocus(() => {
                this.parentCanFocus = false;
                this.isTextFocus = false;
            });
            Button.onTouch((event) => {
                if (event.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (event.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((isHover) => {
                this.parentCanHover = false;
                if (isHover && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!isHover) {
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
            Button.onClick(param.icon?.action);
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(param.icon?.value);
            Image.height(this.iconSize || OPERATEITEM_ICONLIKE_SIZE);
            Image.width(this.iconSize || OPERATEITEM_ICONLIKE_SIZE);
            Image.focusable(true);
            Image.fillColor(this.iconColor || { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createImage(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.image);
            Image.height(OPERATEITEM_IMAGE_SIZE);
            Image.width(OPERATEITEM_IMAGE_SIZE);
            Image.draggable(false);
            Image.onAppear(() => {
                this.isParentCanTouch = true;
            });
        }, Image);
    }
    createText(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.text);
            Text.fontSize(this.secondaryTextSize || { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(this.secondaryTextColors || this.secondaryTextColor);
            Text.textOverflow({ overflow: getBooleanByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_right_textOverflow'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) ? TextOverflow.MARQUEE : TextOverflow.None });
            Text.marqueeOptions({ start: this.isTextFocus, fadeout: getBooleanByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_marqueeOptions_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) || false });
            Text.maxLines(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_maxLines_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) || null);
            Text.focusable(true);
            Text.draggable(false);
            Text.flexShrink(1);
            Text.onAppear(() => {
                this.isParentCanTouch = true;
            });
            Text.onFocus(() => {
                this.isTextFocus = true;
            });
        }, Text);
        Text.pop();
    }
    createArrow(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((event) => {
                if (event.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (event.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((isHover) => {
                this.parentCanHover = false;
                if (isHover && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!isHover) {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.arrow?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.focusable(true);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createRadio(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Radio.create({ value: '', group: '' });
            Radio.margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL1) });
            Radio.checked(this.radioState);
            Radio.onChange(this.radio?.onChange);
            Radio.height(OPERATEITEM_ICONLIKE_SIZE);
            Radio.width(OPERATEITEM_ICONLIKE_SIZE);
            Radio.onFocus(() => {
                this.parentCanFocus = false;
            });
            Radio.hitTestBehavior(HitTestMode.Block);
            Radio.onTouch((event) => {
                if (event.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (event.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Radio.onHover((isHover) => {
                this.parentCanHover = false;
                if (isHover && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!isHover) {
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
    createCheckBox(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Checkbox.create();
            Checkbox.margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL1) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange(this.checkBox?.onChange);
            Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.width(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.onFocus(() => {
                this.parentCanFocus = false;
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.onTouch((event) => {
                if (event.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (event.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Checkbox.onHover((isHover) => {
                this.parentCanHover = false;
                if (isHover && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!isHover) {
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
    createSwitch(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onTouch((event) => {
                if (event.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (event.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Row.onHover((isHover) => {
                this.parentCanHover = false;
                if (isHover && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!isHover) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    createTextArrow(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((event) => {
                if (event.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (event.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((isHover) => {
                this.parentCanHover = false;
                if (isHover && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!isHover) {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: SPECICAL_ROW_SPACE });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.text);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.focusable(true);
            Text.draggable(false);
            Text.constraintSize({
                maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.arrow?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.focusable(true);
            Image.draggable(false);
        }, Image);
        Row.pop();
        Button.pop();
    }
    getFlexOptions() {
        let flexOptions = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            flexOptions.justifyContent = FlexAlign.SpaceBetween;
        }
        else {
            flexOptions.space = { main: LengthMetrics.vp(this.rowSpace) };
            flexOptions.justifyContent = FlexAlign.End;
        }
        return flexOptions;
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create(this.getFlexOptions());
            Flex.flexShrink(1);
            Flex.constraintSize({ minWidth: this.rightWidth });
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.parentDirection === FlexDirection.Column) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(params.contentItem, this, "contentItem");
        this.__operateItem = new SynchedPropertyObjectOneWayPU(params.operateItem, this, "operateItem");
        this.__itemSpace = new SynchedPropertySimpleOneWayPU(params.itemSpace, this, "itemSpace");
        this.__composeItemPadding = new SynchedPropertyObjectOneWayPU(params.composeItemPadding, this, "composeItemPadding");
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
        this.setInitiallyProvidedValue(params);
        this.declareWatch("contentItem", this.onPropChange);
        this.declareWatch("operateItem", this.onPropChange);
        this.declareWatch("fontSizeScale", this.onFontSizeScaleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (params.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (params.itemSpace === undefined) {
            this.__itemSpace.set(DEFAULT_ITEM_SPACE_WIDTH);
        }
        if (params.composeItemPadding === undefined) {
            this.__composeItemPadding.set(null);
        }
        if (params.frontColor !== undefined) {
            this.frontColor = params.frontColor;
        }
        if (params.borderSize !== undefined) {
            this.borderSize = params.borderSize;
        }
        if (params.canFocus !== undefined) {
            this.canFocus = params.canFocus;
        }
        if (params.canTouch !== undefined) {
            this.canTouch = params.canTouch;
        }
        if (params.canHover !== undefined) {
            this.canHover = params.canHover;
        }
        if (params.isHover !== undefined) {
            this.isHover = params.isHover;
        }
        if (params.itemHeight !== undefined) {
            this.itemHeight = params.itemHeight;
        }
        if (params.isActive !== undefined) {
            this.isActive = params.isActive;
        }
        if (params.hoveringColor !== undefined) {
            this.hoveringColor = params.hoveringColor;
        }
        if (params.touchDownColor !== undefined) {
            this.touchDownColor = params.touchDownColor;
        }
        if (params.activedColor !== undefined) {
            this.activedColor = params.activedColor;
        }
        if (params.focusOutlineColor !== undefined) {
            this.focusOutlineColor = params.focusOutlineColor;
        }
        if (params.isCanTouch !== undefined) {
            this.isCanTouch = params.isCanTouch;
        }
        if (params.fontSizeScale !== undefined) {
            this.fontSizeScale = params.fontSizeScale;
        }
        if (params.containerDirection !== undefined) {
            this.containerDirection = params.containerDirection;
        }
        if (params.contentItemDirection !== undefined) {
            this.contentItemDirection = params.contentItemDirection;
        }
        if (params.containerPadding !== undefined) {
            this.containerPadding = params.containerPadding;
        }
        if (params.callbackId !== undefined) {
            this.callbackId = params.callbackId;
        }
        if (params.isFocus !== undefined) {
            this.isFocus = params.isFocus;
        }
        if (params.isHoverBlend !== undefined) {
            this.isHoverBlend = params.isHoverBlend;
        }
    }
    updateStateVars(params) {
        this.__contentItem.reset(params.contentItem);
        this.__operateItem.reset(params.operateItem);
        this.__itemSpace.reset(params.itemSpace);
        this.__composeItemPadding.reset(params.composeItemPadding);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__contentItem.purgeDependencyOnElmtId(rmElmtId);
        this.__operateItem.purgeDependencyOnElmtId(rmElmtId);
        this.__itemSpace.purgeDependencyOnElmtId(rmElmtId);
        this.__composeItemPadding.purgeDependencyOnElmtId(rmElmtId);
        this.__frontColor.purgeDependencyOnElmtId(rmElmtId);
        this.__borderSize.purgeDependencyOnElmtId(rmElmtId);
        this.__canFocus.purgeDependencyOnElmtId(rmElmtId);
        this.__canTouch.purgeDependencyOnElmtId(rmElmtId);
        this.__canHover.purgeDependencyOnElmtId(rmElmtId);
        this.__isHover.purgeDependencyOnElmtId(rmElmtId);
        this.__itemHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__isActive.purgeDependencyOnElmtId(rmElmtId);
        this.__hoveringColor.purgeDependencyOnElmtId(rmElmtId);
        this.__touchDownColor.purgeDependencyOnElmtId(rmElmtId);
        this.__activedColor.purgeDependencyOnElmtId(rmElmtId);
        this.__focusOutlineColor.purgeDependencyOnElmtId(rmElmtId);
        this.__isCanTouch.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
        this.__containerDirection.purgeDependencyOnElmtId(rmElmtId);
        this.__contentItemDirection.purgeDependencyOnElmtId(rmElmtId);
        this.__containerPadding.purgeDependencyOnElmtId(rmElmtId);
        this.__isFocus.purgeDependencyOnElmtId(rmElmtId);
        this.__isHoverBlend.purgeDependencyOnElmtId(rmElmtId);
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get contentItem() {
        return this.__contentItem.get();
    }
    set contentItem(newValue) {
        this.__contentItem.set(newValue);
    }
    get operateItem() {
        return this.__operateItem.get();
    }
    set operateItem(newValue) {
        this.__operateItem.set(newValue);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(newValue) {
        this.__itemSpace.set(newValue);
    }
    get composeItemPadding() {
        return this.__composeItemPadding.get();
    }
    set composeItemPadding(newValue) {
        this.__composeItemPadding.set(newValue);
    }
    get frontColor() {
        return this.__frontColor.get();
    }
    set frontColor(newValue) {
        this.__frontColor.set(newValue);
    }
    get borderSize() {
        return this.__borderSize.get();
    }
    set borderSize(newValue) {
        this.__borderSize.set(newValue);
    }
    get canFocus() {
        return this.__canFocus.get();
    }
    set canFocus(newValue) {
        this.__canFocus.set(newValue);
    }
    get canTouch() {
        return this.__canTouch.get();
    }
    set canTouch(newValue) {
        this.__canTouch.set(newValue);
    }
    get canHover() {
        return this.__canHover.get();
    }
    set canHover(newValue) {
        this.__canHover.set(newValue);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(newValue) {
        this.__isHover.set(newValue);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(newValue) {
        this.__itemHeight.set(newValue);
    }
    get isActive() {
        return this.__isActive.get();
    }
    set isActive(newValue) {
        this.__isActive.set(newValue);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(newValue) {
        this.__hoveringColor.set(newValue);
    }
    get touchDownColor() {
        return this.__touchDownColor.get();
    }
    set touchDownColor(newValue) {
        this.__touchDownColor.set(newValue);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(newValue) {
        this.__activedColor.set(newValue);
    }
    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }
    set focusOutlineColor(newValue) {
        this.__focusOutlineColor.set(newValue);
    }
    get isCanTouch() {
        return this.__isCanTouch.get();
    }
    set isCanTouch(newValue) {
        this.__isCanTouch.set(newValue);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }
    get containerDirection() {
        return this.__containerDirection.get();
    }
    set containerDirection(newValue) {
        this.__containerDirection.set(newValue);
    }
    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }
    set contentItemDirection(newValue) {
        this.__contentItemDirection.set(newValue);
    }
    get containerPadding() {
        return this.__containerPadding.get();
    }
    set containerPadding(newValue) {
        this.__containerPadding.set(newValue);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(newValue) {
        this.__isFocus.set(newValue);
    }
    get isHoverBlend() {
        return this.__isHoverBlend.get();
    }
    set isHoverBlend(newValue) {
        this.__isHoverBlend.set(newValue);
    }
    onWillApplyTheme(theme) {
        this.hoveringColor = theme.colors.interactiveHover;
        this.touchDownColor = theme.colors.interactivePressed;
        this.activedColor = theme.colors.interactiveActive;
        this.focusOutlineColor = theme.colors.interactiveFocus;
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
        let leftPaddingWidth = this.composeItemPadding?.start?.value ?? STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return `calc(100% - ${leftPaddingWidth}vp)`;
        }
        else if (this.operateItem !== null &&
            this.operateItem.button === undefined &&
            this.operateItem.text === undefined) {
            if (this.operateItem.subIcon !== null) {
                return `calc(100% - ${leftPaddingWidth}vp - ${OPERATEITEM_ICON_CLICKABLE_SIZE}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
            }
            else {
                return `calc(100% - ${leftPaddingWidth}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
            }
        }
        else {
            return `calc(66% - ${leftPaddingWidth}vp)`;
        }
    }
    calculatedRightWidth() {
        let rightPaddingWidth = this.composeItemPadding?.end !== undefined ? this.composeItemPadding?.end?.value : STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return RIGHT_CONTENT_NULL_RIGHTWIDTH;
        }
        else if (this.operateItem !== null && this.operateItem.text === undefined) {
            if (this.operateItem.subIcon !== null) {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${RIGHT_ONLY_ARROW_WIDTH} + ${rightPaddingWidth}vp)`;
            }
            else {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${rightPaddingWidth}vp)`;
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
    onFontSizeScaleChange() {
        this.containerDirection = this.decideContainerDirection();
        this.contentItemDirection = this.decideContentItemDirection();
        if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL3) {
            this.containerPadding = {
                top: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                start: LengthMetrics.vp(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })) || null,
                end: LengthMetrics.vp(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })) || null,
            };
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL2) {
            this.containerPadding = {
                top: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                start: LengthMetrics.vp(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })) || null,
                end: LengthMetrics.vp(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })) || null,
            };
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1) {
            this.containerPadding = {
                top: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                start: LengthMetrics.vp(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })) || null,
                end: LengthMetrics.vp(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })) || null,
            };
        }
        else {
            this.containerPadding = {
                top: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                start: LengthMetrics.vp(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })) || null,
                end: LengthMetrics.vp(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })) || null,
            };
        }
    }
    isSingleLine() {
        return !this.contentItem?.secondaryText && !this.contentItem?.description;
    }
    getOperateOffset() {
        if (this.containerDirection === FlexDirection.Row) {
            return LengthMetrics.vp(0);
        }
        let iconSize = ICON_SIZE_MAP.get(this.contentItem?.iconStyle);
        if (iconSize && iconSize <= HEADSCULPTURE_SIZE) {
            return LengthMetrics.vp(iconSize + (this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH));
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
    onMeasureSize(selfLayoutInfo, children, constraint) {
        let sizeResult = { height: 0, width: 0 };
        let content = this.getUIContext().getHostContext();
        this.fontSizeScale = content.config?.fontSizeScale ?? 1;
        children.forEach((child) => {
            let childMeasureResult = child.measure(constraint);
            sizeResult.width = childMeasureResult.width;
            sizeResult.height = childMeasureResult.height;
        });
        return sizeResult;
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.padding({
                start: this.getComposeItemLeftPadding(),
                end: this.getComposeItemRightPadding()
            });
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create(this.getFlexOptions());
            Flex.constraintSize({ minHeight: this.itemHeight });
            Flex.focusable(true);
            Flex.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Flex.onFocus(() => {
                this.canFocus = true;
                this.isFocus = true;
            });
            Flex.onBlur(() => {
                this.canFocus = false;
                this.isFocus = false;
            });
            Flex.onHover((isHover) => {
                this.isHoverBlend = isHover;
                this.isHover = isHover;
                if (this.canHover) {
                    this.frontColor = isHover ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
            });
            Flex.onTouch((event) => {
                if (this.isCanTouch) {
                    if (event.type === TouchType.Down && this.canTouch) {
                        this.frontColor = this.touchDownColor;
                    }
                    if (event.type === TouchType.Up) {
                        this.frontColor = this.isActive ? this.activedColor : Color.Transparent.toString();
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
            Flex.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_backboard'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent);
            Flex.scale({
                x: getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_magnification'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                y: getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_magnification'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
            } || null);
            Flex.shadow(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_shadow_attribute'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) || null);
            ViewStackProcessor.visualState("normal");
            Flex.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_radio'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_stroke_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent,
                width: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_stroke_thickness'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null
            });
            Flex.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || this.frontColor);
            Flex.blur(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_fuzzy_value'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) || null);
            Flex.shadow(getNumberByResource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_shadow_attribute'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) || null);
            Flex.colorBlend((this.isHoverBlend ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : null) || null);
            ViewStackProcessor.visualState("pressed");
            Flex.colorBlend({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_press'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null);
            ViewStackProcessor.visualState();
            Flex.padding(ObservedObject.GetRawObject(this.containerPadding));
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.contentItem === null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new ContentItemStruct(this, {}, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1008, col: 11 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {};
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {});
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.contentItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new ContentItemStruct(this, {
                                    icon: this.contentItem.icon,
                                    iconStyle: this.contentItem.iconStyle,
                                    primaryText: this.contentItem.primaryText,
                                    secondaryText: this.contentItem.secondaryText,
                                    description: this.contentItem.description,
                                    iconImageModifier: this.contentItem.iconImageModifier,
                                    primaryTextModifier: this.contentItem.primaryTextModifier,
                                    secondaryTextModifier: this.contentItem.secondaryTextModifier,
                                    descriptionModifier: this.contentItem.descriptionModifier,
                                    leftWidth: this.calculatedLeftWidth(),
                                    contentItemPadding: this.composeItemPadding,
                                    itemSpace: this.itemSpace,
                                    fontSizeScale: this.fontSizeScale,
                                    parentDirection: this.containerDirection,
                                    itemDirection: this.contentItemDirection,
                                    isFocus: this.isFocus,
                                    itemHeight: this.itemHeight,
                                }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1011, col: 11 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        icon: this.contentItem.icon,
                                        iconStyle: this.contentItem.iconStyle,
                                        primaryText: this.contentItem.primaryText,
                                        secondaryText: this.contentItem.secondaryText,
                                        description: this.contentItem.description,
                                        iconImageModifier: this.contentItem.iconImageModifier,
                                        primaryTextModifier: this.contentItem.primaryTextModifier,
                                        secondaryTextModifier: this.contentItem.secondaryTextModifier,
                                        descriptionModifier: this.contentItem.descriptionModifier,
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
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    icon: this.contentItem.icon,
                                    iconStyle: this.contentItem.iconStyle,
                                    primaryText: this.contentItem.primaryText,
                                    secondaryText: this.contentItem.secondaryText,
                                    description: this.contentItem.description,
                                    iconImageModifier: this.contentItem.iconImageModifier,
                                    primaryTextModifier: this.contentItem.primaryTextModifier,
                                    secondaryTextModifier: this.contentItem.secondaryTextModifier,
                                    descriptionModifier: this.contentItem.descriptionModifier,
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.operateItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new OperateItemStruct(this, {
                                    icon: this.operateItem.icon,
                                    subIcon: this.operateItem.subIcon,
                                    button: this.operateItem.button,
                                    switch: this.operateItem.switch,
                                    checkBox: this.operateItem.checkbox,
                                    radio: this.operateItem.radio,
                                    image: this.operateItem.image,
                                    text: this.operateItem.text,
                                    arrow: this.operateItem.arrow,
                                    parentCanFocus: this.__canFocus,
                                    parentCanTouch: this.__canTouch,
                                    parentIsHover: this.__isHover,
                                    parentFrontColor: this.__frontColor,
                                    parentIsActive: this.__isActive,
                                    parentCanHover: this.__canHover,
                                    rightWidth: this.calculatedRightWidth(),
                                    isParentCanTouch: this.__isCanTouch,
                                    parentDirection: this.containerDirection,
                                    isFocus: this.isFocus,
                                }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1032, col: 11 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        icon: this.operateItem.icon,
                                        subIcon: this.operateItem.subIcon,
                                        button: this.operateItem.button,
                                        switch: this.operateItem.switch,
                                        checkBox: this.operateItem.checkbox,
                                        radio: this.operateItem.radio,
                                        image: this.operateItem.image,
                                        text: this.operateItem.text,
                                        arrow: this.operateItem.arrow,
                                        parentCanFocus: this.canFocus,
                                        parentCanTouch: this.canTouch,
                                        parentIsHover: this.isHover,
                                        parentFrontColor: this.frontColor,
                                        parentIsActive: this.isActive,
                                        parentCanHover: this.canHover,
                                        rightWidth: this.calculatedRightWidth(),
                                        isParentCanTouch: this.isCanTouch,
                                        parentDirection: this.containerDirection,
                                        isFocus: this.isFocus
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    icon: this.operateItem.icon,
                                    subIcon: this.operateItem.subIcon,
                                    button: this.operateItem.button,
                                    switch: this.operateItem.switch,
                                    checkBox: this.operateItem.checkbox,
                                    radio: this.operateItem.radio,
                                    image: this.operateItem.image,
                                    text: this.operateItem.text,
                                    arrow: this.operateItem.arrow,
                                    rightWidth: this.calculatedRightWidth(),
                                    parentDirection: this.containerDirection,
                                    isFocus: this.isFocus
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
/**
 * get resource size
 *
 * @param resourceName resource name
 * @returns resource size
 */
function getNumberByResource(resourceName) {
    try {
        return resourceManager.getSystemResourceManager().getNumber(resourceName);
    }
    catch {
        return null;
    }
}
function getBooleanByResource(resourceName) {
    try {
        return resourceManager.getSystemResourceManager().getBoolean(resourceName);
    }
    catch {
        return false;
    }
}

export default { IconType, ComposeListItem };
