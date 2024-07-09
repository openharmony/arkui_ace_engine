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
(function (b14) {
    b14[b14["BADGE"] = 1] = "BADGE";
    b14[b14["NORMAL_ICON"] = 2] = "NORMAL_ICON";
    b14[b14["SYSTEM_ICON"] = 3] = "SYSTEM_ICON";
    b14[b14["HEAD_SCULPTURE"] = 4] = "HEAD_SCULPTURE";
    b14[b14["APP_ICON"] = 5] = "APP_ICON";
    b14[b14["PREVIEW"] = 6] = "PREVIEW";
    b14[b14["LONGITUDINAL"] = 7] = "LONGITUDINAL";
    b14[b14["VERTICAL"] = 8] = "VERTICAL";
})(IconType || (IconType = {}));
var ItemHeight;
(function (a14) {
    a14[a14["FIRST_HEIGHT"] = 48] = "FIRST_HEIGHT";
    a14[a14["SECOND_HEIGHT"] = 56] = "SECOND_HEIGHT";
    a14[a14["THIRD_HEIGHT"] = 64] = "THIRD_HEIGHT";
    a14[a14["FOURTH_HEIGHT"] = 72] = "FOURTH_HEIGHT";
    a14[a14["FIFTH_HEIGHT"] = 96] = "FIFTH_HEIGHT";
})(ItemHeight || (ItemHeight = {}));
var FontSizeScaleLevel;
(function (z13) {
    z13[z13["LEVEL1"] = 1.75] = "LEVEL1";
    z13[z13["LEVEL2"] = 2] = "LEVEL2";
    z13[z13["LEVEL3"] = 3.2] = "LEVEL3";
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
    constructor(t13, u13, v13, w13 = -1, x13 = undefined, y13) {
        super(t13, v13, w13, y13);
        if (typeof x13 === "function") {
            this.paramsGenerator_ = x13;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(u13.iconStyle, this, "iconStyle");
        this.__icon = new SynchedPropertyObjectOneWayPU(u13.icon, this, "icon");
        this.__primaryText = new SynchedPropertyObjectOneWayPU(u13.primaryText, this, "primaryText");
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(u13.secondaryText, this, "secondaryText");
        this.__description = new SynchedPropertyObjectOneWayPU(u13.description, this, "description");
        this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(u13.leftWidth, this, "leftWidth");
        this.__primaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColor");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__descriptionColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "descriptionColor");
        this.__iconImageModifier = new SynchedPropertyObjectOneWayPU(u13.iconImageModifier, this, "iconImageModifier");
        this.__primaryTextModifier = new SynchedPropertyObjectOneWayPU(u13.primaryTextModifier, this, "primaryTextModifier");
        this.__secondaryTextModifier = new SynchedPropertyObjectOneWayPU(u13.secondaryTextModifier, this, "secondaryTextModifier");
        this.__descriptionModifier = new SynchedPropertyObjectOneWayPU(u13.descriptionModifier, this, "descriptionModifier");
        this.__contentItemPadding = new SynchedPropertyObjectOneWayPU(u13.contentItemPadding, this, "contentItemPadding");
        this.__itemSpace = new SynchedPropertyObjectOneWayPU(u13.itemSpace, this, "itemSpace");
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(u13.fontSizeScale, this, "fontSizeScale");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(u13.parentDirection, this, "parentDirection");
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(u13.itemDirection, this, "itemDirection");
        this.__isFocus = new SynchedPropertySimpleOneWayPU(u13.isFocus, this, "isFocus");
        this.__primaryTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextSize");
        this.__primaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColors");
        this.__itemHeight = new SynchedPropertyObjectOneWayPU(u13.itemHeight, this, "itemHeight");
        this.__iconMagnitude = new ObservedPropertyObjectPU(null, this, "iconMagnitude");
        this.__iconHue = new ObservedPropertyObjectPU(null, this, "iconHue");
        this.__itemSpaces = new ObservedPropertyObjectPU(DEFAULT_ITEM_SPACE_WIDTH, this, "itemSpaces");
        this.setInitiallyProvidedValue(u13);
        this.declareWatch("iconStyle", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("primaryText", this.onPropChange);
        this.declareWatch("secondaryText", this.onPropChange);
        this.declareWatch("description", this.onPropChange);
        this.declareWatch("isFocus", this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(s13) {
        if (s13.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (s13.icon === undefined) {
            this.__icon.set(null);
        }
        if (s13.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (s13.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (s13.description === undefined) {
            this.__description.set(null);
        }
        if (s13.itemRowSpace !== undefined) {
            this.itemRowSpace = s13.itemRowSpace;
        }
        if (s13.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (s13.primaryTextColor !== undefined) {
            this.primaryTextColor = s13.primaryTextColor;
        }
        if (s13.secondaryTextColor !== undefined) {
            this.secondaryTextColor = s13.secondaryTextColor;
        }
        if (s13.descriptionColor !== undefined) {
            this.descriptionColor = s13.descriptionColor;
        }
        if (s13.iconImageModifier === undefined) {
            this.__iconImageModifier.set(null);
        }
        if (s13.primaryTextModifier === undefined) {
            this.__primaryTextModifier.set(null);
        }
        if (s13.secondaryTextModifier === undefined) {
            this.__secondaryTextModifier.set(null);
        }
        if (s13.descriptionModifier === undefined) {
            this.__descriptionModifier.set(null);
        }
        if (s13.contentItemPadding === undefined) {
            this.__contentItemPadding.set(null);
        }
        if (s13.itemSpace === undefined) {
            this.__itemSpace.set(DEFAULT_ITEM_SPACE_WIDTH);
        }
        if (s13.isFocus === undefined) {
            this.__isFocus.set(false);
        }
        if (s13.primaryTextSize !== undefined) {
            this.primaryTextSize = s13.primaryTextSize;
        }
        if (s13.primaryTextColors !== undefined) {
            this.primaryTextColors = s13.primaryTextColors;
        }
        if (s13.itemHeight === undefined) {
            this.__itemHeight.set(null);
        }
        if (s13.iconMagnitude !== undefined) {
            this.iconMagnitude = s13.iconMagnitude;
        }
        if (s13.iconHue !== undefined) {
            this.iconHue = s13.iconHue;
        }
        if (s13.itemSpaces !== undefined) {
            this.itemSpaces = s13.itemSpaces;
        }
    }
    updateStateVars(r13) {
        this.__iconStyle.reset(r13.iconStyle);
        this.__icon.reset(r13.icon);
        this.__primaryText.reset(r13.primaryText);
        this.__secondaryText.reset(r13.secondaryText);
        this.__description.reset(r13.description);
        this.__leftWidth.reset(r13.leftWidth);
        this.__iconImageModifier.reset(r13.iconImageModifier);
        this.__primaryTextModifier.reset(r13.primaryTextModifier);
        this.__secondaryTextModifier.reset(r13.secondaryTextModifier);
        this.__descriptionModifier.reset(r13.descriptionModifier);
        this.__contentItemPadding.reset(r13.contentItemPadding);
        this.__itemSpace.reset(r13.itemSpace);
        this.__fontSizeScale.reset(r13.fontSizeScale);
        this.__parentDirection.reset(r13.parentDirection);
        this.__itemDirection.reset(r13.itemDirection);
        this.__isFocus.reset(r13.isFocus);
        this.__itemHeight.reset(r13.itemHeight);
    }
    purgeVariableDependenciesOnElmtId(q13) {
        this.__iconStyle.purgeDependencyOnElmtId(q13);
        this.__icon.purgeDependencyOnElmtId(q13);
        this.__primaryText.purgeDependencyOnElmtId(q13);
        this.__secondaryText.purgeDependencyOnElmtId(q13);
        this.__description.purgeDependencyOnElmtId(q13);
        this.__leftWidth.purgeDependencyOnElmtId(q13);
        this.__primaryTextColor.purgeDependencyOnElmtId(q13);
        this.__secondaryTextColor.purgeDependencyOnElmtId(q13);
        this.__descriptionColor.purgeDependencyOnElmtId(q13);
        this.__iconImageModifier.purgeDependencyOnElmtId(q13);
        this.__primaryTextModifier.purgeDependencyOnElmtId(q13);
        this.__secondaryTextModifier.purgeDependencyOnElmtId(q13);
        this.__descriptionModifier.purgeDependencyOnElmtId(q13);
        this.__contentItemPadding.purgeDependencyOnElmtId(q13);
        this.__itemSpace.purgeDependencyOnElmtId(q13);
        this.__fontSizeScale.purgeDependencyOnElmtId(q13);
        this.__parentDirection.purgeDependencyOnElmtId(q13);
        this.__itemDirection.purgeDependencyOnElmtId(q13);
        this.__isFocus.purgeDependencyOnElmtId(q13);
        this.__primaryTextSize.purgeDependencyOnElmtId(q13);
        this.__primaryTextColors.purgeDependencyOnElmtId(q13);
        this.__itemHeight.purgeDependencyOnElmtId(q13);
        this.__iconMagnitude.purgeDependencyOnElmtId(q13);
        this.__iconHue.purgeDependencyOnElmtId(q13);
        this.__itemSpaces.purgeDependencyOnElmtId(q13);
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
    set iconStyle(p13) {
        this.__iconStyle.set(p13);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(o13) {
        this.__icon.set(o13);
    }
    get primaryText() {
        return this.__primaryText.get();
    }
    set primaryText(n13) {
        this.__primaryText.set(n13);
    }
    get secondaryText() {
        return this.__secondaryText.get();
    }
    set secondaryText(m13) {
        this.__secondaryText.set(m13);
    }
    get description() {
        return this.__description.get();
    }
    set description(l13) {
        this.__description.set(l13);
    }
    get leftWidth() {
        return this.__leftWidth.get();
    }
    set leftWidth(k13) {
        this.__leftWidth.set(k13);
    }
    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }
    set primaryTextColor(j13) {
        this.__primaryTextColor.set(j13);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(i13) {
        this.__secondaryTextColor.set(i13);
    }
    get descriptionColor() {
        return this.__descriptionColor.get();
    }
    set descriptionColor(h13) {
        this.__descriptionColor.set(h13);
    }
    get iconImageModifier() {
        return this.__iconImageModifier.get();
    }
    set iconImageModifier(g13) {
        this.__iconImageModifier.set(g13);
    }
    get primaryTextModifier() {
        return this.__primaryTextModifier.get();
    }
    set primaryTextModifier(f13) {
        this.__primaryTextModifier.set(f13);
    }
    get secondaryTextModifier() {
        return this.__secondaryTextModifier.get();
    }
    set secondaryTextModifier(e13) {
        this.__secondaryTextModifier.set(e13);
    }
    get descriptionModifier() {
        return this.__descriptionModifier.get();
    }
    set descriptionModifier(d13) {
        this.__descriptionModifier.set(d13);
    }
    get contentItemPadding() {
        return this.__contentItemPadding.get();
    }
    set contentItemPadding(c13) {
        this.__contentItemPadding.set(c13);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(b13) {
        this.__itemSpace.set(b13);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(a13) {
        this.__fontSizeScale.set(a13);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(z12) {
        this.__parentDirection.set(z12);
    }
    get itemDirection() {
        return this.__itemDirection.get();
    }
    set itemDirection(y12) {
        this.__itemDirection.set(y12);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(x12) {
        this.__isFocus.set(x12);
    }
    get primaryTextSize() {
        return this.__primaryTextSize.get();
    }
    set primaryTextSize(w12) {
        this.__primaryTextSize.set(w12);
    }
    get primaryTextColors() {
        return this.__primaryTextColors.get();
    }
    set primaryTextColors(v12) {
        this.__primaryTextColors.set(v12);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(u12) {
        this.__itemHeight.set(u12);
    }
    get iconMagnitude() {
        return this.__iconMagnitude.get();
    }
    set iconMagnitude(t12) {
        this.__iconMagnitude.set(t12);
    }
    get iconHue() {
        return this.__iconHue.get();
    }
    set iconHue(s12) {
        this.__iconHue.set(s12);
    }
    get itemSpaces() {
        return this.__itemSpaces.get();
    }
    set itemSpaces(r12) {
        this.__itemSpaces.set(r12);
    }
    onWillApplyTheme(q12) {
        this.primaryTextColor = q12.colors.fontPrimary;
        this.secondaryTextColor = q12.colors.fontSecondary;
        this.descriptionColor = q12.colors.fontTertiary;
    }
    onPropChange() {
        if (this.icon == null && this.iconStyle == null) {
            this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
        }
        this.primaryTextSize = this.isFocus ? { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.primaryTextColors = this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    }
    getIconType(m12, n12, o12, p12) {
        switch (m12) {
            case IconType.SYSTEM_ICON:
                this.iconMagnitude = n12;
                this.iconHue = p12;
                break;
            case IconType.HEAD_SCULPTURE:
                this.iconMagnitude = n12;
                this.itemSpaces = getNumberByResource(o12);
                break;
            case IconType.PREVIEW:
                this.iconMagnitude = n12;
                this.itemSpaces = getNumberByResource(o12);
                break;
            case IconType.APP_ICON:
                this.iconMagnitude = n12;
                this.itemSpaces = getNumberByResource(o12);
        }
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
    createIcon(v11 = null) {
        this.observeComponentCreation2((x11, y11) => {
            If.create();
            if (this.icon != null && this.iconStyle != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c12, d12) => {
                        If.create();
                        if (this.iconStyle <= IconType.PREVIEW) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((k12, l12) => {
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
                                this.observeComponentCreation2((g12, h12) => {
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
    createText(y10 = null) {
        this.observeComponentCreation2((t11, u11) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((r11, s11) => {
            Text.create(this.primaryText);
            Text.fontSize(this.primaryTextSize || { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(this.primaryTextColors || this.primaryTextColor);
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(FOCUSABLE);
            Text.draggable(false);
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTextModifier));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((k11, l11) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p11, q11) => {
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
        this.observeComponentCreation2((d11, e11) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i11, j11) => {
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
        this.observeComponentCreation2((w10, x10) => {
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
    constructor(p10, q10, r10, s10 = -1, t10 = undefined, u10) {
        super(p10, r10, s10, u10);
        if (typeof t10 === "function") {
            this.paramsGenerator_ = t10;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(q10.arrow, this, "arrow");
        this.__icon = new SynchedPropertyObjectOneWayPU(q10.icon, this, "icon");
        this.__subIcon = new SynchedPropertyObjectOneWayPU(q10.subIcon, this, "subIcon");
        this.__button = new SynchedPropertyObjectOneWayPU(q10.button, this, "button");
        this.__switch = new SynchedPropertyObjectOneWayPU(q10.switch, this, "switch");
        this.__checkBox = new SynchedPropertyObjectOneWayPU(q10.checkBox, this, "checkBox");
        this.__radio = new SynchedPropertyObjectOneWayPU(q10.radio, this, "radio");
        this.__image = new SynchedPropertyObjectOneWayPU(q10.image, this, "image");
        this.__text = new SynchedPropertyObjectOneWayPU(q10.text, this, "text");
        this.__switchState = new ObservedPropertySimplePU(false, this, "switchState");
        this.__radioState = new ObservedPropertySimplePU(false, this, "radioState");
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, "checkBoxState");
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(q10.rightWidth, this, "rightWidth");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, "hoveringColor");
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, "activedColor");
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(q10.parentCanFocus, this, "parentCanFocus");
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(q10.parentCanTouch, this, "parentCanTouch");
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(q10.parentIsHover, this, "parentIsHover");
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(q10.parentCanHover, this, "parentCanHover");
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(q10.parentIsActive, this, "parentIsActive");
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(q10.parentFrontColor, this, "parentFrontColor");
        this.__isParentCanTouch = new SynchedPropertySimpleTwoWayPU(q10.isParentCanTouch, this, "isParentCanTouch");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(q10.parentDirection, this, "parentDirection");
        this.rowSpace = DEFAULT_ROW_SPACE;
        this.__isFocus = new SynchedPropertySimpleTwoWayPU(q10.isFocus, this, "isFocus");
        this.__secondaryTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextSize");
        this.__secondaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColors");
        this.__iconSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "iconSize");
        this.__iconColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "iconColor");
        this.__isOnClick = new SynchedPropertySimpleOneWayPU(q10.isOnClick, this, "isOnClick");
        this.setInitiallyProvidedValue(q10);
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
    setInitiallyProvidedValue(o10) {
        if (o10.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (o10.icon === undefined) {
            this.__icon.set(null);
        }
        if (o10.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (o10.button === undefined) {
            this.__button.set(null);
        }
        if (o10.switch === undefined) {
            this.__switch.set(null);
        }
        if (o10.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (o10.radio === undefined) {
            this.__radio.set(null);
        }
        if (o10.image === undefined) {
            this.__image.set(null);
        }
        if (o10.text === undefined) {
            this.__text.set(null);
        }
        if (o10.switchState !== undefined) {
            this.switchState = o10.switchState;
        }
        if (o10.radioState !== undefined) {
            this.radioState = o10.radioState;
        }
        if (o10.checkBoxState !== undefined) {
            this.checkBoxState = o10.checkBoxState;
        }
        if (o10.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (o10.secondaryTextColor !== undefined) {
            this.secondaryTextColor = o10.secondaryTextColor;
        }
        if (o10.hoveringColor !== undefined) {
            this.hoveringColor = o10.hoveringColor;
        }
        if (o10.activedColor !== undefined) {
            this.activedColor = o10.activedColor;
        }
        if (o10.rowSpace !== undefined) {
            this.rowSpace = o10.rowSpace;
        }
        if (o10.secondaryTextSize !== undefined) {
            this.secondaryTextSize = o10.secondaryTextSize;
        }
        if (o10.secondaryTextColors !== undefined) {
            this.secondaryTextColors = o10.secondaryTextColors;
        }
        if (o10.iconSize !== undefined) {
            this.iconSize = o10.iconSize;
        }
        if (o10.iconColor !== undefined) {
            this.iconColor = o10.iconColor;
        }
        if (o10.isOnClick === undefined) {
            this.__isOnClick.set(false);
        }
    }
    updateStateVars(n10) {
        this.__arrow.reset(n10.arrow);
        this.__icon.reset(n10.icon);
        this.__subIcon.reset(n10.subIcon);
        this.__button.reset(n10.button);
        this.__switch.reset(n10.switch);
        this.__checkBox.reset(n10.checkBox);
        this.__radio.reset(n10.radio);
        this.__image.reset(n10.image);
        this.__text.reset(n10.text);
        this.__rightWidth.reset(n10.rightWidth);
        this.__parentDirection.reset(n10.parentDirection);
        this.__isOnClick.reset(n10.isOnClick);
    }
    purgeVariableDependenciesOnElmtId(m10) {
        this.__arrow.purgeDependencyOnElmtId(m10);
        this.__icon.purgeDependencyOnElmtId(m10);
        this.__subIcon.purgeDependencyOnElmtId(m10);
        this.__button.purgeDependencyOnElmtId(m10);
        this.__switch.purgeDependencyOnElmtId(m10);
        this.__checkBox.purgeDependencyOnElmtId(m10);
        this.__radio.purgeDependencyOnElmtId(m10);
        this.__image.purgeDependencyOnElmtId(m10);
        this.__text.purgeDependencyOnElmtId(m10);
        this.__switchState.purgeDependencyOnElmtId(m10);
        this.__radioState.purgeDependencyOnElmtId(m10);
        this.__checkBoxState.purgeDependencyOnElmtId(m10);
        this.__rightWidth.purgeDependencyOnElmtId(m10);
        this.__secondaryTextColor.purgeDependencyOnElmtId(m10);
        this.__hoveringColor.purgeDependencyOnElmtId(m10);
        this.__activedColor.purgeDependencyOnElmtId(m10);
        this.__parentCanFocus.purgeDependencyOnElmtId(m10);
        this.__parentCanTouch.purgeDependencyOnElmtId(m10);
        this.__parentIsHover.purgeDependencyOnElmtId(m10);
        this.__parentCanHover.purgeDependencyOnElmtId(m10);
        this.__parentIsActive.purgeDependencyOnElmtId(m10);
        this.__parentFrontColor.purgeDependencyOnElmtId(m10);
        this.__isParentCanTouch.purgeDependencyOnElmtId(m10);
        this.__parentDirection.purgeDependencyOnElmtId(m10);
        this.__isFocus.purgeDependencyOnElmtId(m10);
        this.__secondaryTextSize.purgeDependencyOnElmtId(m10);
        this.__secondaryTextColors.purgeDependencyOnElmtId(m10);
        this.__iconSize.purgeDependencyOnElmtId(m10);
        this.__iconColor.purgeDependencyOnElmtId(m10);
        this.__isOnClick.purgeDependencyOnElmtId(m10);
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
    set arrow(l10) {
        this.__arrow.set(l10);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(k10) {
        this.__icon.set(k10);
    }
    get subIcon() {
        return this.__subIcon.get();
    }
    set subIcon(j10) {
        this.__subIcon.set(j10);
    }
    get button() {
        return this.__button.get();
    }
    set button(i10) {
        this.__button.set(i10);
    }
    get switch() {
        return this.__switch.get();
    }
    set switch(h10) {
        this.__switch.set(h10);
    }
    get checkBox() {
        return this.__checkBox.get();
    }
    set checkBox(g10) {
        this.__checkBox.set(g10);
    }
    get radio() {
        return this.__radio.get();
    }
    set radio(f10) {
        this.__radio.set(f10);
    }
    get image() {
        return this.__image.get();
    }
    set image(e10) {
        this.__image.set(e10);
    }
    get text() {
        return this.__text.get();
    }
    set text(d10) {
        this.__text.set(d10);
    }
    get switchState() {
        return this.__switchState.get();
    }
    set switchState(c10) {
        this.__switchState.set(c10);
    }
    get radioState() {
        return this.__radioState.get();
    }
    set radioState(b10) {
        this.__radioState.set(b10);
    }
    get checkBoxState() {
        return this.__checkBoxState.get();
    }
    set checkBoxState(a10) {
        this.__checkBoxState.set(a10);
    }
    get rightWidth() {
        return this.__rightWidth.get();
    }
    set rightWidth(z9) {
        this.__rightWidth.set(z9);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(y9) {
        this.__secondaryTextColor.set(y9);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(x9) {
        this.__hoveringColor.set(x9);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(w9) {
        this.__activedColor.set(w9);
    }
    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }
    set parentCanFocus(v9) {
        this.__parentCanFocus.set(v9);
    }
    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }
    set parentCanTouch(u9) {
        this.__parentCanTouch.set(u9);
    }
    get parentIsHover() {
        return this.__parentIsHover.get();
    }
    set parentIsHover(t9) {
        this.__parentIsHover.set(t9);
    }
    get parentCanHover() {
        return this.__parentCanHover.get();
    }
    set parentCanHover(s9) {
        this.__parentCanHover.set(s9);
    }
    get parentIsActive() {
        return this.__parentIsActive.get();
    }
    set parentIsActive(r9) {
        this.__parentIsActive.set(r9);
    }
    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }
    set parentFrontColor(q9) {
        this.__parentFrontColor.set(q9);
    }
    get isParentCanTouch() {
        return this.__isParentCanTouch.get();
    }
    set isParentCanTouch(p9) {
        this.__isParentCanTouch.set(p9);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(o9) {
        this.__parentDirection.set(o9);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(n9) {
        this.__isFocus.set(n9);
    }
    get secondaryTextSize() {
        return this.__secondaryTextSize.get();
    }
    set secondaryTextSize(m9) {
        this.__secondaryTextSize.set(m9);
    }
    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }
    set secondaryTextColors(l9) {
        this.__secondaryTextColors.set(l9);
    }
    get iconSize() {
        return this.__iconSize.get();
    }
    set iconSize(k9) {
        this.__iconSize.set(k9);
    }
    get iconColor() {
        return this.__iconColor.get();
    }
    set iconColor(j9) {
        this.__iconColor.set(j9);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(i9) {
        this.__isOnClick.set(i9);
    }
    onWillApplyTheme(h9) {
        this.secondaryTextColor = h9.colors.fontSecondary;
        this.hoveringColor = h9.colors.interactiveHover;
        this.activedColor = h9.colors.interactiveActive;
    }
    onFocusChange() {
        this.secondaryTextSize = this.isFocus ? { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_right_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.secondaryTextColors = this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_right_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.iconSize = this.isFocus ? { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_right_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.iconColor = this.isFocus ? { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_right_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    }
    onPropChange() {
        if (this.switch != null) {
            this.switchState = !FOCUSABLE ? this.isOnClick : this.switch.isCheck;
        }
        if (this.radio != null) {
            this.radioState = !FOCUSABLE ? this.isOnClick : this.radio.isCheck;
        }
        if (this.checkBox != null) {
            this.checkBoxState = !FOCUSABLE ? this.isOnClick : this.checkBox.isCheck;
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
    createButton(s8 = null) {
        this.observeComponentCreation2((a9, b9) => {
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
            Button.onTouch((g9) => {
                if (g9.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (g9.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((f9) => {
                this.parentCanHover = false;
                if (f9 && this.parentFrontColor === HOVERING_COLOR) {
                    this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
                }
                if (!f9) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR :
                            (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((y8, z8) => {
            Row.create();
            Row.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
            });
            Row.focusable(FOCUSABLE);
        }, Row);
        this.observeComponentCreation2((w8, x8) => {
            Text.create(this.button?.text);
            Text.focusable(FOCUSABLE);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(e8, f8 = null) {
        this.observeComponentCreation2((k8, l8) => {
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
            Button.onTouch((r8) => {
                if (r8.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (r8.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((q8) => {
                this.parentCanHover = false;
                if (q8 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!q8) {
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
            Button.onClick(e8.icon?.action);
        }, Button);
        this.observeComponentCreation2((i8, j8) => {
            Image.create(e8.icon?.value);
            Image.height(this.iconSize || OPERATEITEM_ICONLIKE_SIZE);
            Image.width(this.iconSize || OPERATEITEM_ICONLIKE_SIZE);
            Image.focusable(FOCUSABLE);
            Image.fillColor(this.iconColor || { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createImage(z7 = null) {
        this.observeComponentCreation2((b8, c8) => {
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
    createText(u7 = null) {
        this.observeComponentCreation2((w7, x7) => {
            Text.create(this.text);
            Text.fontSize(this.secondaryTextSize || { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(this.secondaryTextColors || this.secondaryTextColor);
            Text.textOverflow({
                overflow: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_right_textOverflow'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                    .value == 1 ? TextOverflow.MARQUEE : TextOverflow.None
            });
            Text.marqueeOptions({
                start: this.isFocus,
                fadeout: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_marqueeOptions_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value == 1 ? true : false
            });
            Text.maxLines(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_maxLines_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value == 1 ? 1 : null);
            Text.focusable(FOCUSABLE);
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
            Button.focusable(FOCUSABLE);
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((t7) => {
                if (t7.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (t7.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((s7) => {
                this.parentCanHover = false;
                if (s7 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!s7) {
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
        this.observeComponentCreation2((k7, l7) => {
            Image.create(this.arrow?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.focusable(FOCUSABLE);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createRadio(x6 = null) {
        this.observeComponentCreation2((z6, a7) => {
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
    createCheckBox(n6 = null) {
        this.observeComponentCreation2((p6, q6) => {
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
            Checkbox.onTouch((w6) => {
                if (w6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (w6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Checkbox.onHover((v6) => {
                this.parentCanHover = false;
                if (v6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!v6) {
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
    createSwitch(a6 = null) {
        this.observeComponentCreation2((g6, h6) => {
            Row.create();
            Row.focusable(FOCUSABLE);
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onTouch((m6) => {
                if (m6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (m6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Row.onHover((l6) => {
                this.parentCanHover = false;
                if (l6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!l6) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((d6, e6) => {
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
    createTextArrow(h5 = null) {
        this.observeComponentCreation2((s5, t5) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.focusable(FOCUSABLE);
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((z5) => {
                if (z5.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (z5.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((y5) => {
                this.parentCanHover = false;
                if (y5 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!y5) {
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
        this.observeComponentCreation2((q5, r5) => {
            Row.create({ space: SPECICAL_ROW_SPACE });
        }, Row);
        this.observeComponentCreation2((o5, p5) => {
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
        this.observeComponentCreation2((m5, n5) => {
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
        let g5 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            g5.justifyContent = FlexAlign.SpaceBetween;
        }
        else {
            g5.space = { main: LengthMetrics.vp(this.rowSpace) };
            g5.justifyContent = FlexAlign.End;
        }
        return g5;
    }
    initialRender() {
        this.observeComponentCreation2((e5, f5) => {
            Flex.create(this.getFlexOptions());
            Flex.flexShrink(1);
            Flex.constraintSize({ minWidth: this.rightWidth });
        }, Flex);
        this.observeComponentCreation2((e4, f4) => {
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
                    this.observeComponentCreation2((t4, u4) => {
                        If.create();
                        if (this.parentDirection === FlexDirection.Column) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((y4, z4) => {
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
                    this.observeComponentCreation2((j4, k4) => {
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
    constructor(w3, x3, y3, z3 = -1, a4 = undefined, b4) {
        super(w3, y3, z3, b4);
        if (typeof a4 === "function") {
            this.paramsGenerator_ = a4;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(x3.contentItem, this, "contentItem");
        this.__operateItem = new SynchedPropertyObjectOneWayPU(x3.operateItem, this, "operateItem");
        this.__itemSpace = new SynchedPropertySimpleOneWayPU(x3.itemSpace, this, "itemSpace");
        this.__composeItemPadding = new SynchedPropertyObjectOneWayPU(x3.composeItemPadding, this, "composeItemPadding");
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
        this.setInitiallyProvidedValue(x3);
        this.declareWatch("contentItem", this.onPropChange);
        this.declareWatch("operateItem", this.onPropChange);
        this.declareWatch("fontSizeScale", this.onFontSizeScaleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(v3) {
        if (v3.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (v3.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (v3.itemSpace === undefined) {
            this.__itemSpace.set(DEFAULT_ITEM_SPACE_WIDTH);
        }
        if (v3.composeItemPadding === undefined) {
            this.__composeItemPadding.set(null);
        }
        if (v3.frontColor !== undefined) {
            this.frontColor = v3.frontColor;
        }
        if (v3.borderSize !== undefined) {
            this.borderSize = v3.borderSize;
        }
        if (v3.canFocus !== undefined) {
            this.canFocus = v3.canFocus;
        }
        if (v3.canTouch !== undefined) {
            this.canTouch = v3.canTouch;
        }
        if (v3.canHover !== undefined) {
            this.canHover = v3.canHover;
        }
        if (v3.isHover !== undefined) {
            this.isHover = v3.isHover;
        }
        if (v3.itemHeight !== undefined) {
            this.itemHeight = v3.itemHeight;
        }
        if (v3.isActive !== undefined) {
            this.isActive = v3.isActive;
        }
        if (v3.hoveringColor !== undefined) {
            this.hoveringColor = v3.hoveringColor;
        }
        if (v3.touchDownColor !== undefined) {
            this.touchDownColor = v3.touchDownColor;
        }
        if (v3.activedColor !== undefined) {
            this.activedColor = v3.activedColor;
        }
        if (v3.focusOutlineColor !== undefined) {
            this.focusOutlineColor = v3.focusOutlineColor;
        }
        if (v3.isCanTouch !== undefined) {
            this.isCanTouch = v3.isCanTouch;
        }
        if (v3.fontSizeScale !== undefined) {
            this.fontSizeScale = v3.fontSizeScale;
        }
        if (v3.containerDirection !== undefined) {
            this.containerDirection = v3.containerDirection;
        }
        if (v3.contentItemDirection !== undefined) {
            this.contentItemDirection = v3.contentItemDirection;
        }
        if (v3.containerPadding !== undefined) {
            this.containerPadding = v3.containerPadding;
        }
        if (v3.callbackId !== undefined) {
            this.callbackId = v3.callbackId;
        }
        if (v3.isFocus !== undefined) {
            this.isFocus = v3.isFocus;
        }
        if (v3.isHoverBlend !== undefined) {
            this.isHoverBlend = v3.isHoverBlend;
        }
        if (v3.isOnClick !== undefined) {
            this.isOnClick = v3.isOnClick;
        }
    }
    updateStateVars(u3) {
        this.__contentItem.reset(u3.contentItem);
        this.__operateItem.reset(u3.operateItem);
        this.__itemSpace.reset(u3.itemSpace);
        this.__composeItemPadding.reset(u3.composeItemPadding);
    }
    purgeVariableDependenciesOnElmtId(t3) {
        this.__contentItem.purgeDependencyOnElmtId(t3);
        this.__operateItem.purgeDependencyOnElmtId(t3);
        this.__itemSpace.purgeDependencyOnElmtId(t3);
        this.__composeItemPadding.purgeDependencyOnElmtId(t3);
        this.__frontColor.purgeDependencyOnElmtId(t3);
        this.__borderSize.purgeDependencyOnElmtId(t3);
        this.__canFocus.purgeDependencyOnElmtId(t3);
        this.__canTouch.purgeDependencyOnElmtId(t3);
        this.__canHover.purgeDependencyOnElmtId(t3);
        this.__isHover.purgeDependencyOnElmtId(t3);
        this.__itemHeight.purgeDependencyOnElmtId(t3);
        this.__isActive.purgeDependencyOnElmtId(t3);
        this.__hoveringColor.purgeDependencyOnElmtId(t3);
        this.__touchDownColor.purgeDependencyOnElmtId(t3);
        this.__activedColor.purgeDependencyOnElmtId(t3);
        this.__focusOutlineColor.purgeDependencyOnElmtId(t3);
        this.__isCanTouch.purgeDependencyOnElmtId(t3);
        this.__fontSizeScale.purgeDependencyOnElmtId(t3);
        this.__containerDirection.purgeDependencyOnElmtId(t3);
        this.__contentItemDirection.purgeDependencyOnElmtId(t3);
        this.__containerPadding.purgeDependencyOnElmtId(t3);
        this.__isFocus.purgeDependencyOnElmtId(t3);
        this.__isHoverBlend.purgeDependencyOnElmtId(t3);
        this.__isOnClick.purgeDependencyOnElmtId(t3);
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
    set contentItem(s3) {
        this.__contentItem.set(s3);
    }
    get operateItem() {
        return this.__operateItem.get();
    }
    set operateItem(r3) {
        this.__operateItem.set(r3);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(q3) {
        this.__itemSpace.set(q3);
    }
    get composeItemPadding() {
        return this.__composeItemPadding.get();
    }
    set composeItemPadding(p3) {
        this.__composeItemPadding.set(p3);
    }
    get frontColor() {
        return this.__frontColor.get();
    }
    set frontColor(o3) {
        this.__frontColor.set(o3);
    }
    get borderSize() {
        return this.__borderSize.get();
    }
    set borderSize(n3) {
        this.__borderSize.set(n3);
    }
    get canFocus() {
        return this.__canFocus.get();
    }
    set canFocus(m3) {
        this.__canFocus.set(m3);
    }
    get canTouch() {
        return this.__canTouch.get();
    }
    set canTouch(l3) {
        this.__canTouch.set(l3);
    }
    get canHover() {
        return this.__canHover.get();
    }
    set canHover(k3) {
        this.__canHover.set(k3);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(j3) {
        this.__isHover.set(j3);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(i3) {
        this.__itemHeight.set(i3);
    }
    get isActive() {
        return this.__isActive.get();
    }
    set isActive(h3) {
        this.__isActive.set(h3);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(g3) {
        this.__hoveringColor.set(g3);
    }
    get touchDownColor() {
        return this.__touchDownColor.get();
    }
    set touchDownColor(f3) {
        this.__touchDownColor.set(f3);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(e3) {
        this.__activedColor.set(e3);
    }
    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }
    set focusOutlineColor(d3) {
        this.__focusOutlineColor.set(d3);
    }
    get isCanTouch() {
        return this.__isCanTouch.get();
    }
    set isCanTouch(c3) {
        this.__isCanTouch.set(c3);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(b3) {
        this.__fontSizeScale.set(b3);
    }
    get containerDirection() {
        return this.__containerDirection.get();
    }
    set containerDirection(a3) {
        this.__containerDirection.set(a3);
    }
    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }
    set contentItemDirection(z2) {
        this.__contentItemDirection.set(z2);
    }
    get containerPadding() {
        return this.__containerPadding.get();
    }
    set containerPadding(y2) {
        this.__containerPadding.set(y2);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(x2) {
        this.__isFocus.set(x2);
    }
    get isHoverBlend() {
        return this.__isHoverBlend.get();
    }
    set isHoverBlend(w2) {
        this.__isHoverBlend.set(w2);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(v2) {
        this.__isOnClick.set(v2);
    }
    onWillApplyTheme(u2) {
        this.hoveringColor = u2.colors.interactiveHover;
        this.touchDownColor = u2.colors.interactivePressed;
        this.activedColor = u2.colors.interactiveActive;
        this.focusOutlineColor = u2.colors.interactiveFocus;
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
        let t2 = this.composeItemPadding?.start?.value ?? STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return `calc(100% - ${t2}vp)`;
        }
        else if (this.operateItem !== null &&
            this.operateItem.button === undefined &&
            this.operateItem.text === undefined) {
            if (this.operateItem.subIcon !== null) {
                return `calc(100% - ${t2}vp - ${OPERATEITEM_ICON_CLICKABLE_SIZE}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
            }
            else {
                return `calc(100% - ${t2}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
            }
        }
        else {
            return `calc(66% - ${t2}vp)`;
        }
    }
    calculatedRightWidth() {
        let s2 = this.composeItemPadding?.end !== undefined ? this.composeItemPadding?.end?.value : STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return RIGHT_CONTENT_NULL_RIGHTWIDTH;
        }
        else if (this.operateItem !== null && this.operateItem.text === undefined) {
            if (this.operateItem.subIcon !== null) {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${RIGHT_ONLY_ARROW_WIDTH} + ${s2}vp)`;
            }
            else {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${s2}vp)`;
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
    getContainerPadding() {
        if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL3) {
            this.containerPadding = {
                top: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                left: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
                right: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
            };
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL2) {
            this.containerPadding = {
                top: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                left: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
                right: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
            };
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1) {
            this.containerPadding = {
                top: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                left: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
                right: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
            };
        }
        else {
            this.containerPadding = {
                top: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                left: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
                right: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
            };
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
                                let s1 = new ContentItemStruct(this, {}, undefined, q1, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1028, col: 11 });
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
                                }, undefined, c1, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1031, col: 11 });
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
                                }, undefined, m, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1052, col: 11 });
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
