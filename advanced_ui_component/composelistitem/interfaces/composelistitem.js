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
(function (z13) {
    z13[z13["BADGE"] = 1] = "BADGE";
    z13[z13["NORMAL_ICON"] = 2] = "NORMAL_ICON";
    z13[z13["SYSTEM_ICON"] = 3] = "SYSTEM_ICON";
    z13[z13["HEAD_SCULPTURE"] = 4] = "HEAD_SCULPTURE";
    z13[z13["APP_ICON"] = 5] = "APP_ICON";
    z13[z13["PREVIEW"] = 6] = "PREVIEW";
    z13[z13["LONGITUDINAL"] = 7] = "LONGITUDINAL";
    z13[z13["VERTICAL"] = 8] = "VERTICAL";
})(IconType || (IconType = {}));
var ItemHeight;
(function (y13) {
    y13[y13["FIRST_HEIGHT"] = 48] = "FIRST_HEIGHT";
    y13[y13["SECOND_HEIGHT"] = 56] = "SECOND_HEIGHT";
    y13[y13["THIRD_HEIGHT"] = 64] = "THIRD_HEIGHT";
    y13[y13["FOURTH_HEIGHT"] = 72] = "FOURTH_HEIGHT";
    y13[y13["FIFTH_HEIGHT"] = 96] = "FIFTH_HEIGHT";
})(ItemHeight || (ItemHeight = {}));
var FontSizeScaleLevel;
(function (x13) {
    x13[x13["LEVEL1"] = 1.75] = "LEVEL1";
    x13[x13["LEVEL2"] = 2] = "LEVEL2";
    x13[x13["LEVEL3"] = 3.2] = "LEVEL3";
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
const RECOVERYSCALE = 1;
const CLEARSHADOW = -1;
const CLEARBLUR = 0;
class ContentItemStruct extends ViewPU {
    constructor(r13, s13, t13, u13 = -1, v13 = undefined, w13) {
        super(r13, t13, u13, w13);
        if (typeof v13 === "function") {
            this.paramsGenerator_ = v13;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(s13.iconStyle, this, "iconStyle");
        this.__icon = new SynchedPropertyObjectOneWayPU(s13.icon, this, "icon");
        this.__primaryText = new SynchedPropertyObjectOneWayPU(s13.primaryText, this, "primaryText");
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(s13.secondaryText, this, "secondaryText");
        this.__description = new SynchedPropertyObjectOneWayPU(s13.description, this, "description");
        this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(s13.leftWidth, this, "leftWidth");
        this.__primaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColor");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__descriptionColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "descriptionColor");
        this.__iconImageModifier = new SynchedPropertyObjectOneWayPU(s13.iconImageModifier, this, "iconImageModifier");
        this.__primaryTextModifier = new SynchedPropertyObjectOneWayPU(s13.primaryTextModifier, this, "primaryTextModifier");
        this.__secondaryTextModifier = new SynchedPropertyObjectOneWayPU(s13.secondaryTextModifier, this, "secondaryTextModifier");
        this.__descriptionModifier = new SynchedPropertyObjectOneWayPU(s13.descriptionModifier, this, "descriptionModifier");
        this.__contentItemPadding = new SynchedPropertyObjectOneWayPU(s13.contentItemPadding, this, "contentItemPadding");
        this.__itemSpace = new SynchedPropertyObjectOneWayPU(s13.itemSpace, this, "itemSpace");
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(s13.fontSizeScale, this, "fontSizeScale");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(s13.parentDirection, this, "parentDirection");
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(s13.itemDirection, this, "itemDirection");
        this.__isFocus = new SynchedPropertySimpleOneWayPU(s13.isFocus, this, "isFocus");
        this.__primaryTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextSize");
        this.__primaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColors");
        this.__itemHeight = new SynchedPropertyObjectOneWayPU(s13.itemHeight, this, "itemHeight");
        this.__iconMagnitude = new ObservedPropertyObjectPU(null, this, "iconMagnitude");
        this.__iconColor = new ObservedPropertyObjectPU(null, this, "iconColor");
        this.__secondaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColors");
        this.__secondaryThirdTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryThirdTextSize");
        this.__descriptionColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "descriptionColors");
        this.setInitiallyProvidedValue(s13);
        this.declareWatch("iconStyle", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("primaryText", this.onPropChange);
        this.declareWatch("secondaryText", this.onPropChange);
        this.declareWatch("description", this.onPropChange);
        this.declareWatch("isFocus", this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q13) {
        if (q13.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (q13.icon === undefined) {
            this.__icon.set(null);
        }
        if (q13.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (q13.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (q13.description === undefined) {
            this.__description.set(null);
        }
        if (q13.itemRowSpace !== undefined) {
            this.itemRowSpace = q13.itemRowSpace;
        }
        if (q13.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (q13.primaryTextColor !== undefined) {
            this.primaryTextColor = q13.primaryTextColor;
        }
        if (q13.secondaryTextColor !== undefined) {
            this.secondaryTextColor = q13.secondaryTextColor;
        }
        if (q13.descriptionColor !== undefined) {
            this.descriptionColor = q13.descriptionColor;
        }
        if (q13.iconImageModifier === undefined) {
            this.__iconImageModifier.set(null);
        }
        if (q13.primaryTextModifier === undefined) {
            this.__primaryTextModifier.set(null);
        }
        if (q13.secondaryTextModifier === undefined) {
            this.__secondaryTextModifier.set(null);
        }
        if (q13.descriptionModifier === undefined) {
            this.__descriptionModifier.set(null);
        }
        if (q13.contentItemPadding === undefined) {
            this.__contentItemPadding.set(null);
        }
        if (q13.itemSpace === undefined) {
            this.__itemSpace.set(DEFAULT_ITEM_SPACE_WIDTH);
        }
        if (q13.isFocus === undefined) {
            this.__isFocus.set(false);
        }
        if (q13.primaryTextSize !== undefined) {
            this.primaryTextSize = q13.primaryTextSize;
        }
        if (q13.primaryTextColors !== undefined) {
            this.primaryTextColors = q13.primaryTextColors;
        }
        if (q13.itemHeight === undefined) {
            this.__itemHeight.set(null);
        }
        if (q13.iconMagnitude !== undefined) {
            this.iconMagnitude = q13.iconMagnitude;
        }
        if (q13.iconColor !== undefined) {
            this.iconColor = q13.iconColor;
        }
        if (q13.secondaryTextColors !== undefined) {
            this.secondaryTextColors = q13.secondaryTextColors;
        }
        if (q13.secondaryThirdTextSize !== undefined) {
            this.secondaryThirdTextSize = q13.secondaryThirdTextSize;
        }
        if (q13.descriptionColors !== undefined) {
            this.descriptionColors = q13.descriptionColors;
        }
    }
    updateStateVars(p13) {
        this.__iconStyle.reset(p13.iconStyle);
        this.__icon.reset(p13.icon);
        this.__primaryText.reset(p13.primaryText);
        this.__secondaryText.reset(p13.secondaryText);
        this.__description.reset(p13.description);
        this.__leftWidth.reset(p13.leftWidth);
        this.__iconImageModifier.reset(p13.iconImageModifier);
        this.__primaryTextModifier.reset(p13.primaryTextModifier);
        this.__secondaryTextModifier.reset(p13.secondaryTextModifier);
        this.__descriptionModifier.reset(p13.descriptionModifier);
        this.__contentItemPadding.reset(p13.contentItemPadding);
        this.__itemSpace.reset(p13.itemSpace);
        this.__fontSizeScale.reset(p13.fontSizeScale);
        this.__parentDirection.reset(p13.parentDirection);
        this.__itemDirection.reset(p13.itemDirection);
        this.__isFocus.reset(p13.isFocus);
        this.__itemHeight.reset(p13.itemHeight);
    }
    purgeVariableDependenciesOnElmtId(o13) {
        this.__iconStyle.purgeDependencyOnElmtId(o13);
        this.__icon.purgeDependencyOnElmtId(o13);
        this.__primaryText.purgeDependencyOnElmtId(o13);
        this.__secondaryText.purgeDependencyOnElmtId(o13);
        this.__description.purgeDependencyOnElmtId(o13);
        this.__leftWidth.purgeDependencyOnElmtId(o13);
        this.__primaryTextColor.purgeDependencyOnElmtId(o13);
        this.__secondaryTextColor.purgeDependencyOnElmtId(o13);
        this.__descriptionColor.purgeDependencyOnElmtId(o13);
        this.__iconImageModifier.purgeDependencyOnElmtId(o13);
        this.__primaryTextModifier.purgeDependencyOnElmtId(o13);
        this.__secondaryTextModifier.purgeDependencyOnElmtId(o13);
        this.__descriptionModifier.purgeDependencyOnElmtId(o13);
        this.__contentItemPadding.purgeDependencyOnElmtId(o13);
        this.__itemSpace.purgeDependencyOnElmtId(o13);
        this.__fontSizeScale.purgeDependencyOnElmtId(o13);
        this.__parentDirection.purgeDependencyOnElmtId(o13);
        this.__itemDirection.purgeDependencyOnElmtId(o13);
        this.__isFocus.purgeDependencyOnElmtId(o13);
        this.__primaryTextSize.purgeDependencyOnElmtId(o13);
        this.__primaryTextColors.purgeDependencyOnElmtId(o13);
        this.__itemHeight.purgeDependencyOnElmtId(o13);
        this.__iconMagnitude.purgeDependencyOnElmtId(o13);
        this.__iconColor.purgeDependencyOnElmtId(o13);
        this.__secondaryTextColors.purgeDependencyOnElmtId(o13);
        this.__secondaryThirdTextSize.purgeDependencyOnElmtId(o13);
        this.__descriptionColors.purgeDependencyOnElmtId(o13);
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
    set iconStyle(n13) {
        this.__iconStyle.set(n13);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(m13) {
        this.__icon.set(m13);
    }
    get primaryText() {
        return this.__primaryText.get();
    }
    set primaryText(l13) {
        this.__primaryText.set(l13);
    }
    get secondaryText() {
        return this.__secondaryText.get();
    }
    set secondaryText(k13) {
        this.__secondaryText.set(k13);
    }
    get description() {
        return this.__description.get();
    }
    set description(j13) {
        this.__description.set(j13);
    }
    get leftWidth() {
        return this.__leftWidth.get();
    }
    set leftWidth(i13) {
        this.__leftWidth.set(i13);
    }
    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }
    set primaryTextColor(h13) {
        this.__primaryTextColor.set(h13);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(g13) {
        this.__secondaryTextColor.set(g13);
    }
    get descriptionColor() {
        return this.__descriptionColor.get();
    }
    set descriptionColor(f13) {
        this.__descriptionColor.set(f13);
    }
    get iconImageModifier() {
        return this.__iconImageModifier.get();
    }
    set iconImageModifier(e13) {
        this.__iconImageModifier.set(e13);
    }
    get primaryTextModifier() {
        return this.__primaryTextModifier.get();
    }
    set primaryTextModifier(d13) {
        this.__primaryTextModifier.set(d13);
    }
    get secondaryTextModifier() {
        return this.__secondaryTextModifier.get();
    }
    set secondaryTextModifier(c13) {
        this.__secondaryTextModifier.set(c13);
    }
    get descriptionModifier() {
        return this.__descriptionModifier.get();
    }
    set descriptionModifier(b13) {
        this.__descriptionModifier.set(b13);
    }
    get contentItemPadding() {
        return this.__contentItemPadding.get();
    }
    set contentItemPadding(a13) {
        this.__contentItemPadding.set(a13);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(z12) {
        this.__itemSpace.set(z12);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(y12) {
        this.__fontSizeScale.set(y12);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(x12) {
        this.__parentDirection.set(x12);
    }
    get itemDirection() {
        return this.__itemDirection.get();
    }
    set itemDirection(w12) {
        this.__itemDirection.set(w12);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(v12) {
        this.__isFocus.set(v12);
    }
    get primaryTextSize() {
        return this.__primaryTextSize.get();
    }
    set primaryTextSize(u12) {
        this.__primaryTextSize.set(u12);
    }
    get primaryTextColors() {
        return this.__primaryTextColors.get();
    }
    set primaryTextColors(t12) {
        this.__primaryTextColors.set(t12);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(s12) {
        this.__itemHeight.set(s12);
    }
    get iconMagnitude() {
        return this.__iconMagnitude.get();
    }
    set iconMagnitude(r12) {
        this.__iconMagnitude.set(r12);
    }
    get iconColor() {
        return this.__iconColor.get();
    }
    set iconColor(q12) {
        this.__iconColor.set(q12);
    }
    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }
    set secondaryTextColors(p12) {
        this.__secondaryTextColors.set(p12);
    }
    get secondaryThirdTextSize() {
        return this.__secondaryThirdTextSize.get();
    }
    set secondaryThirdTextSize(o12) {
        this.__secondaryThirdTextSize.set(o12);
    }
    get descriptionColors() {
        return this.__descriptionColors.get();
    }
    set descriptionColors(n12) {
        this.__descriptionColors.set(n12);
    }
    onWillApplyTheme(m12) {
        this.primaryTextColor = m12.colors.fontPrimary;
        this.secondaryTextColor = m12.colors.fontSecondary;
        this.descriptionColor = m12.colors.fontTertiary;
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
                                    Image.focusable(true);
                                    Image.draggable(false);
                                    Image.fillColor(this.iconColor || { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
            Text.focusable(true);
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
                        Text.fontSize(this.secondaryThirdTextSize || { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(this.secondaryTextColors || this.secondaryTextColor);
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
        this.observeComponentCreation2((d11, e11) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i11, j11) => {
                        Text.create(this.description);
                        Text.fontSize(this.secondaryThirdTextSize || { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(this.descriptionColors || this.descriptionColor);
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
        this.observeComponentCreation2((w10, x10) => {
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
    createButton(s8 = null) {
        this.observeComponentCreation2((a9, b9) => {
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
        }, Row);
        this.observeComponentCreation2((w8, x8) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(d8, e8 = null) {
        this.observeComponentCreation2((j8, k8) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEARSHADOW);
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
            Button.onClick(() => {
                if (FOCUSABLE) {
                    d8.icon?.action();
                }
            });
        }, Button);
        this.observeComponentCreation2((h8, i8) => {
            Image.create(d8.icon?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ICONLIKE_SIZE);
            Image.focusable(true);
            Image.fillColor(this.iconColor || { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createImage(y7 = null) {
        this.observeComponentCreation2((a8, b8) => {
            Image.create(this.image);
            Image.height(OPERATEITEM_IMAGE_SIZE);
            Image.width(OPERATEITEM_IMAGE_SIZE);
            Image.draggable(false);
            Image.onAppear(() => {
                this.isParentCanTouch = true;
            });
        }, Image);
    }
    createText(t7 = null) {
        this.observeComponentCreation2((v7, w7) => {
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
            Text.focusable(true);
            Text.draggable(false);
            Text.flexShrink(1);
            Text.onAppear(() => {
                this.isParentCanTouch = true;
            });
        }, Text);
        Text.pop();
    }
    createArrow(f7 = null) {
        this.observeComponentCreation2((k7, l7) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEARSHADOW);
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((s7) => {
                if (s7.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (s7.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((r7) => {
                this.parentCanHover = false;
                if (r7 && this.parentFrontColor === this.hoveringColor) {
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
            Button.onAppear(() => {
                this.isParentCanTouch = true;
            });
            Button.onClick(() => {
                if (FOCUSABLE) {
                    this.arrow?.action();
                }
            });
        }, Button);
        this.observeComponentCreation2((i7, j7) => {
            Image.create(this.arrow?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.focusable(true);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createRadio(v6 = null) {
        this.observeComponentCreation2((x6, y6) => {
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
            Radio.onTouch((e7) => {
                if (e7.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (e7.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Radio.onHover((d7) => {
                this.parentCanHover = false;
                if (d7 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!d7) {
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
            Checkbox.margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL1) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange(this.checkBox?.onChange);
            Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.width(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.onFocus(() => {
                this.parentCanFocus = false;
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.onTouch((u6) => {
                if (u6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (u6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Checkbox.onHover((t6) => {
                this.parentCanHover = false;
                if (t6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!t6) {
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
            Toggle.onChange(this.switch?.onChange);
            Toggle.onClick(() => {
                this.switchState = !this.switchState;
            });
            Toggle.hitTestBehavior(HitTestMode.Block);
        }, Toggle);
        Toggle.pop();
        Row.pop();
    }
    createTextArrow(e5 = null) {
        this.observeComponentCreation2((p5, q5) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEARSHADOW);
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
                if (FOCUSABLE) {
                    this.arrow?.action();
                }
            });
        }, Button);
        this.observeComponentCreation2((n5, o5) => {
            Row.create({ space: SPECICAL_ROW_SPACE });
        }, Row);
        this.observeComponentCreation2((l5, m5) => {
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
        this.observeComponentCreation2((j5, k5) => {
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
        this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString();
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
                        .value || ItemHeight.THIRD_HEIGHT);
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
            end: LengthMetrics.vp(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null).value),
            bottom: LengthMetrics.vp(LengthMetrics.resource(o2).value),
            start: LengthMetrics.vp(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null).value),
        };
    }
    getContainerPadding() {
        if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL3) {
            this.setContainerPadding({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL2) {
            this.setContainerPadding({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1) {
            this.setContainerPadding({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }
        else {
            this.setContainerPadding({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_top'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, { "id": -1, "type": 10002, params: ['sys.float.composeListItem_single_line_list_left_text_bottom'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
                this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_backboard'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString();
            });
            Stack.onBlur(() => {
                this.isFocus = false;
                this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString();
            });
            Stack.borderRadius(this.isFocus ? { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_radio'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_circular_bead'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Stack.onClick(() => {
                if (!FOCUSABLE) {
                    this.isOnClick = !this.isOnClick;
                    if (this.operateItem?.icon) {
                        this.operateItem?.icon.action();
                    }
                    if (this.operateItem?.subIcon) {
                        this.operateItem?.subIcon.action();
                    }
                    if (this.operateItem?.arrow) {
                        this.operateItem?.arrow.action();
                    }
                }
            });
            Stack.scale({
                x: this.isFocus ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_magnification'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value : RECOVERYSCALE,
                y: this.isFocus ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_magnification'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value : RECOVERYSCALE
            });
            Stack.blur(this.isFocus ? CLEARBLUR : LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_fuzzy_value'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value);
            Stack.shadow(this.isFocus ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_shadow_attribute'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value : LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_shadow_attribute'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value);
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
                this.isFocus = true;
                this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_backboard'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString();
            });
            Flex.onBlur(() => {
                this.canFocus = false;
                this.isFocus = false;
                this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString();
            });
            Flex.onHover((y1) => {
                this.isHoverBlend = y1;
                this.isHover = y1;
                if (this.canHover) {
                    this.frontColor = y1 ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
                this.frontColor = y1 ? ({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || this.hoveringColor) :
                    ({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString());
            });
            Flex.onTouch((x1) => {
                if (this.isCanTouch) {
                    if (x1.type === TouchType.Down && this.canTouch) {
                        this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_press'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || this.touchDownColor;
                    }
                    if (x1.type === TouchType.Up) {
                        this.frontColor = this.isActive ? this.activedColor : ({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString());
                    }
                }
            });
            ViewStackProcessor.visualState("focused");
            Flex.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_circular_bead'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: (LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_border'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value || ITEM_BORDER_SHOWN) * LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_magnification'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                    .value,
                color: { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_border_focused'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || this.focusOutlineColor,
                style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState("normal");
            Flex.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_radio'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_stroke_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent,
                width: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_stroke_thickness'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
            });
            Flex.scale({
                x: RECOVERYSCALE,
                y: RECOVERYSCALE
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
                                let n1 = new ContentItemStruct(this, {}, undefined, l1, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1000, col: 11 });
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
                                }, undefined, a1, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1003, col: 11 });
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
                                    isOnClick: this.isOnClick,
                                }, undefined, l, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1024, col: 11 });
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

export default { IconType, ComposeListItem };
