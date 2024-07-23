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
(function (x13) {
    x13[x13["BADGE"] = 1] = "BADGE";
    x13[x13["NORMAL_ICON"] = 2] = "NORMAL_ICON";
    x13[x13["SYSTEM_ICON"] = 3] = "SYSTEM_ICON";
    x13[x13["HEAD_SCULPTURE"] = 4] = "HEAD_SCULPTURE";
    x13[x13["APP_ICON"] = 5] = "APP_ICON";
    x13[x13["PREVIEW"] = 6] = "PREVIEW";
    x13[x13["LONGITUDINAL"] = 7] = "LONGITUDINAL";
    x13[x13["VERTICAL"] = 8] = "VERTICAL";
})(IconType || (IconType = {}));
var ItemHeight;
(function (w13) {
    w13[w13["FIRST_HEIGHT"] = 48] = "FIRST_HEIGHT";
    w13[w13["SECOND_HEIGHT"] = 56] = "SECOND_HEIGHT";
    w13[w13["THIRD_HEIGHT"] = 64] = "THIRD_HEIGHT";
    w13[w13["FOURTH_HEIGHT"] = 72] = "FOURTH_HEIGHT";
    w13[w13["FIFTH_HEIGHT"] = 96] = "FIFTH_HEIGHT";
})(ItemHeight || (ItemHeight = {}));
var FontSizeScaleLevel;
(function (v13) {
    v13[v13["LEVEL1"] = 1.75] = "LEVEL1";
    v13[v13["LEVEL2"] = 2] = "LEVEL2";
    v13[v13["LEVEL3"] = 3.2] = "LEVEL3";
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
const recoveryScale = 1;
class ContentItemStruct extends ViewPU {
    constructor(p13, q13, r13, s13 = -1, t13 = undefined, u13) {
        super(p13, r13, s13, u13);
        if (typeof t13 === "function") {
            this.paramsGenerator_ = t13;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(q13.iconStyle, this, "iconStyle");
        this.__icon = new SynchedPropertyObjectOneWayPU(q13.icon, this, "icon");
        this.__primaryText = new SynchedPropertyObjectOneWayPU(q13.primaryText, this, "primaryText");
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(q13.secondaryText, this, "secondaryText");
        this.__description = new SynchedPropertyObjectOneWayPU(q13.description, this, "description");
        this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(q13.leftWidth, this, "leftWidth");
        this.__primaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColor");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__descriptionColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "descriptionColor");
        this.__iconImageModifier = new SynchedPropertyObjectOneWayPU(q13.iconImageModifier, this, "iconImageModifier");
        this.__primaryTextModifier = new SynchedPropertyObjectOneWayPU(q13.primaryTextModifier, this, "primaryTextModifier");
        this.__secondaryTextModifier = new SynchedPropertyObjectOneWayPU(q13.secondaryTextModifier, this, "secondaryTextModifier");
        this.__descriptionModifier = new SynchedPropertyObjectOneWayPU(q13.descriptionModifier, this, "descriptionModifier");
        this.__contentItemPadding = new SynchedPropertyObjectOneWayPU(q13.contentItemPadding, this, "contentItemPadding");
        this.__itemSpace = new SynchedPropertyObjectOneWayPU(q13.itemSpace, this, "itemSpace");
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(q13.fontSizeScale, this, "fontSizeScale");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(q13.parentDirection, this, "parentDirection");
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(q13.itemDirection, this, "itemDirection");
        this.__isFocus = new SynchedPropertySimpleOneWayPU(q13.isFocus, this, "isFocus");
        this.__primaryTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_left_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextSize");
        this.__primaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_left_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColors");
        this.__itemHeight = new SynchedPropertyObjectOneWayPU(q13.itemHeight, this, "itemHeight");
        this.__iconMagnitude = new ObservedPropertyObjectPU(null, this, "iconMagnitude");
        this.__iconColor = new ObservedPropertyObjectPU(null, this, "iconColor");
        this.__secondaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColors");
        this.__secondaryThirdTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryThirdTextSize");
        this.__descriptionColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "descriptionColors");
        this.setInitiallyProvidedValue(q13);
        this.declareWatch("iconStyle", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("primaryText", this.onPropChange);
        this.declareWatch("secondaryText", this.onPropChange);
        this.declareWatch("description", this.onPropChange);
        this.declareWatch("isFocus", this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(o13) {
        if (o13.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (o13.icon === undefined) {
            this.__icon.set(null);
        }
        if (o13.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (o13.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (o13.description === undefined) {
            this.__description.set(null);
        }
        if (o13.itemRowSpace !== undefined) {
            this.itemRowSpace = o13.itemRowSpace;
        }
        if (o13.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (o13.primaryTextColor !== undefined) {
            this.primaryTextColor = o13.primaryTextColor;
        }
        if (o13.secondaryTextColor !== undefined) {
            this.secondaryTextColor = o13.secondaryTextColor;
        }
        if (o13.descriptionColor !== undefined) {
            this.descriptionColor = o13.descriptionColor;
        }
        if (o13.iconImageModifier === undefined) {
            this.__iconImageModifier.set(null);
        }
        if (o13.primaryTextModifier === undefined) {
            this.__primaryTextModifier.set(null);
        }
        if (o13.secondaryTextModifier === undefined) {
            this.__secondaryTextModifier.set(null);
        }
        if (o13.descriptionModifier === undefined) {
            this.__descriptionModifier.set(null);
        }
        if (o13.contentItemPadding === undefined) {
            this.__contentItemPadding.set(null);
        }
        if (o13.itemSpace === undefined) {
            this.__itemSpace.set(DEFAULT_ITEM_SPACE_WIDTH);
        }
        if (o13.isFocus === undefined) {
            this.__isFocus.set(false);
        }
        if (o13.primaryTextSize !== undefined) {
            this.primaryTextSize = o13.primaryTextSize;
        }
        if (o13.primaryTextColors !== undefined) {
            this.primaryTextColors = o13.primaryTextColors;
        }
        if (o13.itemHeight === undefined) {
            this.__itemHeight.set(null);
        }
        if (o13.iconMagnitude !== undefined) {
            this.iconMagnitude = o13.iconMagnitude;
        }
        if (o13.iconColor !== undefined) {
            this.iconColor = o13.iconColor;
        }
        if (o13.secondaryTextColors !== undefined) {
            this.secondaryTextColors = o13.secondaryTextColors;
        }
        if (o13.secondaryThirdTextSize !== undefined) {
            this.secondaryThirdTextSize = o13.secondaryThirdTextSize;
        }
        if (o13.descriptionColors !== undefined) {
            this.descriptionColors = o13.descriptionColors;
        }
    }
    updateStateVars(n13) {
        this.__iconStyle.reset(n13.iconStyle);
        this.__icon.reset(n13.icon);
        this.__primaryText.reset(n13.primaryText);
        this.__secondaryText.reset(n13.secondaryText);
        this.__description.reset(n13.description);
        this.__leftWidth.reset(n13.leftWidth);
        this.__iconImageModifier.reset(n13.iconImageModifier);
        this.__primaryTextModifier.reset(n13.primaryTextModifier);
        this.__secondaryTextModifier.reset(n13.secondaryTextModifier);
        this.__descriptionModifier.reset(n13.descriptionModifier);
        this.__contentItemPadding.reset(n13.contentItemPadding);
        this.__itemSpace.reset(n13.itemSpace);
        this.__fontSizeScale.reset(n13.fontSizeScale);
        this.__parentDirection.reset(n13.parentDirection);
        this.__itemDirection.reset(n13.itemDirection);
        this.__isFocus.reset(n13.isFocus);
        this.__itemHeight.reset(n13.itemHeight);
    }
    purgeVariableDependenciesOnElmtId(m13) {
        this.__iconStyle.purgeDependencyOnElmtId(m13);
        this.__icon.purgeDependencyOnElmtId(m13);
        this.__primaryText.purgeDependencyOnElmtId(m13);
        this.__secondaryText.purgeDependencyOnElmtId(m13);
        this.__description.purgeDependencyOnElmtId(m13);
        this.__leftWidth.purgeDependencyOnElmtId(m13);
        this.__primaryTextColor.purgeDependencyOnElmtId(m13);
        this.__secondaryTextColor.purgeDependencyOnElmtId(m13);
        this.__descriptionColor.purgeDependencyOnElmtId(m13);
        this.__iconImageModifier.purgeDependencyOnElmtId(m13);
        this.__primaryTextModifier.purgeDependencyOnElmtId(m13);
        this.__secondaryTextModifier.purgeDependencyOnElmtId(m13);
        this.__descriptionModifier.purgeDependencyOnElmtId(m13);
        this.__contentItemPadding.purgeDependencyOnElmtId(m13);
        this.__itemSpace.purgeDependencyOnElmtId(m13);
        this.__fontSizeScale.purgeDependencyOnElmtId(m13);
        this.__parentDirection.purgeDependencyOnElmtId(m13);
        this.__itemDirection.purgeDependencyOnElmtId(m13);
        this.__isFocus.purgeDependencyOnElmtId(m13);
        this.__primaryTextSize.purgeDependencyOnElmtId(m13);
        this.__primaryTextColors.purgeDependencyOnElmtId(m13);
        this.__itemHeight.purgeDependencyOnElmtId(m13);
        this.__iconMagnitude.purgeDependencyOnElmtId(m13);
        this.__iconColor.purgeDependencyOnElmtId(m13);
        this.__secondaryTextColors.purgeDependencyOnElmtId(m13);
        this.__secondaryThirdTextSize.purgeDependencyOnElmtId(m13);
        this.__descriptionColors.purgeDependencyOnElmtId(m13);
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
    set iconStyle(l13) {
        this.__iconStyle.set(l13);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(k13) {
        this.__icon.set(k13);
    }
    get primaryText() {
        return this.__primaryText.get();
    }
    set primaryText(j13) {
        this.__primaryText.set(j13);
    }
    get secondaryText() {
        return this.__secondaryText.get();
    }
    set secondaryText(i13) {
        this.__secondaryText.set(i13);
    }
    get description() {
        return this.__description.get();
    }
    set description(h13) {
        this.__description.set(h13);
    }
    get leftWidth() {
        return this.__leftWidth.get();
    }
    set leftWidth(g13) {
        this.__leftWidth.set(g13);
    }
    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }
    set primaryTextColor(f13) {
        this.__primaryTextColor.set(f13);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(e13) {
        this.__secondaryTextColor.set(e13);
    }
    get descriptionColor() {
        return this.__descriptionColor.get();
    }
    set descriptionColor(d13) {
        this.__descriptionColor.set(d13);
    }
    get iconImageModifier() {
        return this.__iconImageModifier.get();
    }
    set iconImageModifier(c13) {
        this.__iconImageModifier.set(c13);
    }
    get primaryTextModifier() {
        return this.__primaryTextModifier.get();
    }
    set primaryTextModifier(b13) {
        this.__primaryTextModifier.set(b13);
    }
    get secondaryTextModifier() {
        return this.__secondaryTextModifier.get();
    }
    set secondaryTextModifier(a13) {
        this.__secondaryTextModifier.set(a13);
    }
    get descriptionModifier() {
        return this.__descriptionModifier.get();
    }
    set descriptionModifier(z12) {
        this.__descriptionModifier.set(z12);
    }
    get contentItemPadding() {
        return this.__contentItemPadding.get();
    }
    set contentItemPadding(y12) {
        this.__contentItemPadding.set(y12);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(x12) {
        this.__itemSpace.set(x12);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(w12) {
        this.__fontSizeScale.set(w12);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(v12) {
        this.__parentDirection.set(v12);
    }
    get itemDirection() {
        return this.__itemDirection.get();
    }
    set itemDirection(u12) {
        this.__itemDirection.set(u12);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(t12) {
        this.__isFocus.set(t12);
    }
    get primaryTextSize() {
        return this.__primaryTextSize.get();
    }
    set primaryTextSize(s12) {
        this.__primaryTextSize.set(s12);
    }
    get primaryTextColors() {
        return this.__primaryTextColors.get();
    }
    set primaryTextColors(r12) {
        this.__primaryTextColors.set(r12);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(q12) {
        this.__itemHeight.set(q12);
    }
    get iconMagnitude() {
        return this.__iconMagnitude.get();
    }
    set iconMagnitude(p12) {
        this.__iconMagnitude.set(p12);
    }
    get iconColor() {
        return this.__iconColor.get();
    }
    set iconColor(o12) {
        this.__iconColor.set(o12);
    }
    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }
    set secondaryTextColors(n12) {
        this.__secondaryTextColors.set(n12);
    }
    get secondaryThirdTextSize() {
        return this.__secondaryThirdTextSize.get();
    }
    set secondaryThirdTextSize(m12) {
        this.__secondaryThirdTextSize.set(m12);
    }
    get descriptionColors() {
        return this.__descriptionColors.get();
    }
    set descriptionColors(l12) {
        this.__descriptionColors.set(l12);
    }
    onWillApplyTheme(k12) {
        this.primaryTextColor = k12.colors.fontPrimary;
        this.secondaryTextColor = k12.colors.fontSecondary;
        this.descriptionColor = k12.colors.fontTertiary;
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
    createIcon(t11 = null) {
        this.observeComponentCreation2((v11, w11) => {
            If.create();
            if (this.icon != null && this.iconStyle != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a12, b12) => {
                        If.create();
                        if (this.iconStyle <= IconType.PREVIEW) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((i12, j12) => {
                                    Image.create(this.icon);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.width(this.iconMagnitude || ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.height(this.iconMagnitude || ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.focusable(FOCUSABLE);
                                    Image.draggable(false);
                                    Image.fillColor(this.iconColor || { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.iconImageModifier));
                                    Image.flexShrink(0);
                                }, Image);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((e12, f12) => {
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
    createText(w10 = null) {
        this.observeComponentCreation2((r11, s11) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((p11, q11) => {
            Text.create(this.primaryText);
            Text.fontSize(this.primaryTextSize || { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(this.primaryTextColors || this.primaryTextColor);
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(FOCUSABLE);
            Text.draggable(false);
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTextModifier));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((i11, j11) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n11, o11) => {
                        Text.create(this.secondaryText);
                        Text.fontSize(this.secondaryThirdTextSize || { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(this.secondaryTextColors || this.secondaryTextColor);
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
        this.observeComponentCreation2((b11, c11) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g11, h11) => {
                        Text.create(this.description);
                        Text.fontSize(this.secondaryThirdTextSize || { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(this.descriptionColors || this.descriptionColor);
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
        this.observeComponentCreation2((u10, v10) => {
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
    constructor(n10, o10, p10, q10 = -1, r10 = undefined, s10) {
        super(n10, p10, q10, s10);
        if (typeof r10 === "function") {
            this.paramsGenerator_ = r10;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(o10.arrow, this, "arrow");
        this.__icon = new SynchedPropertyObjectOneWayPU(o10.icon, this, "icon");
        this.__subIcon = new SynchedPropertyObjectOneWayPU(o10.subIcon, this, "subIcon");
        this.__button = new SynchedPropertyObjectOneWayPU(o10.button, this, "button");
        this.__switch = new SynchedPropertyObjectOneWayPU(o10.switch, this, "switch");
        this.__checkBox = new SynchedPropertyObjectOneWayPU(o10.checkBox, this, "checkBox");
        this.__radio = new SynchedPropertyObjectOneWayPU(o10.radio, this, "radio");
        this.__image = new SynchedPropertyObjectOneWayPU(o10.image, this, "image");
        this.__text = new SynchedPropertyObjectOneWayPU(o10.text, this, "text");
        this.__switchState = new ObservedPropertySimplePU(false, this, "switchState");
        this.__radioState = new ObservedPropertySimplePU(false, this, "radioState");
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, "checkBoxState");
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(o10.rightWidth, this, "rightWidth");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, "hoveringColor");
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, "activedColor");
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(o10.parentCanFocus, this, "parentCanFocus");
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(o10.parentCanTouch, this, "parentCanTouch");
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(o10.parentIsHover, this, "parentIsHover");
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(o10.parentCanHover, this, "parentCanHover");
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(o10.parentIsActive, this, "parentIsActive");
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(o10.parentFrontColor, this, "parentFrontColor");
        this.__isParentCanTouch = new SynchedPropertySimpleTwoWayPU(o10.isParentCanTouch, this, "isParentCanTouch");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(o10.parentDirection, this, "parentDirection");
        this.rowSpace = DEFAULT_ROW_SPACE;
        this.__isFocus = new SynchedPropertySimpleTwoWayPU(o10.isFocus, this, "isFocus");
        this.__secondaryTextSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_text_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextSize");
        this.__secondaryTextColors = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_text_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColors");
        this.__iconSize = new ObservedPropertyObjectPU({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_right_icon_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "iconSize");
        this.__iconColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_right_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "iconColor");
        this.__isOnClick = new SynchedPropertySimpleOneWayPU(o10.isOnClick, this, "isOnClick");
        this.setInitiallyProvidedValue(o10);
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
    setInitiallyProvidedValue(m10) {
        if (m10.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (m10.icon === undefined) {
            this.__icon.set(null);
        }
        if (m10.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (m10.button === undefined) {
            this.__button.set(null);
        }
        if (m10.switch === undefined) {
            this.__switch.set(null);
        }
        if (m10.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (m10.radio === undefined) {
            this.__radio.set(null);
        }
        if (m10.image === undefined) {
            this.__image.set(null);
        }
        if (m10.text === undefined) {
            this.__text.set(null);
        }
        if (m10.switchState !== undefined) {
            this.switchState = m10.switchState;
        }
        if (m10.radioState !== undefined) {
            this.radioState = m10.radioState;
        }
        if (m10.checkBoxState !== undefined) {
            this.checkBoxState = m10.checkBoxState;
        }
        if (m10.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (m10.secondaryTextColor !== undefined) {
            this.secondaryTextColor = m10.secondaryTextColor;
        }
        if (m10.hoveringColor !== undefined) {
            this.hoveringColor = m10.hoveringColor;
        }
        if (m10.activedColor !== undefined) {
            this.activedColor = m10.activedColor;
        }
        if (m10.rowSpace !== undefined) {
            this.rowSpace = m10.rowSpace;
        }
        if (m10.secondaryTextSize !== undefined) {
            this.secondaryTextSize = m10.secondaryTextSize;
        }
        if (m10.secondaryTextColors !== undefined) {
            this.secondaryTextColors = m10.secondaryTextColors;
        }
        if (m10.iconSize !== undefined) {
            this.iconSize = m10.iconSize;
        }
        if (m10.iconColor !== undefined) {
            this.iconColor = m10.iconColor;
        }
        if (m10.isOnClick === undefined) {
            this.__isOnClick.set(false);
        }
    }
    updateStateVars(l10) {
        this.__arrow.reset(l10.arrow);
        this.__icon.reset(l10.icon);
        this.__subIcon.reset(l10.subIcon);
        this.__button.reset(l10.button);
        this.__switch.reset(l10.switch);
        this.__checkBox.reset(l10.checkBox);
        this.__radio.reset(l10.radio);
        this.__image.reset(l10.image);
        this.__text.reset(l10.text);
        this.__rightWidth.reset(l10.rightWidth);
        this.__parentDirection.reset(l10.parentDirection);
        this.__isOnClick.reset(l10.isOnClick);
    }
    purgeVariableDependenciesOnElmtId(k10) {
        this.__arrow.purgeDependencyOnElmtId(k10);
        this.__icon.purgeDependencyOnElmtId(k10);
        this.__subIcon.purgeDependencyOnElmtId(k10);
        this.__button.purgeDependencyOnElmtId(k10);
        this.__switch.purgeDependencyOnElmtId(k10);
        this.__checkBox.purgeDependencyOnElmtId(k10);
        this.__radio.purgeDependencyOnElmtId(k10);
        this.__image.purgeDependencyOnElmtId(k10);
        this.__text.purgeDependencyOnElmtId(k10);
        this.__switchState.purgeDependencyOnElmtId(k10);
        this.__radioState.purgeDependencyOnElmtId(k10);
        this.__checkBoxState.purgeDependencyOnElmtId(k10);
        this.__rightWidth.purgeDependencyOnElmtId(k10);
        this.__secondaryTextColor.purgeDependencyOnElmtId(k10);
        this.__hoveringColor.purgeDependencyOnElmtId(k10);
        this.__activedColor.purgeDependencyOnElmtId(k10);
        this.__parentCanFocus.purgeDependencyOnElmtId(k10);
        this.__parentCanTouch.purgeDependencyOnElmtId(k10);
        this.__parentIsHover.purgeDependencyOnElmtId(k10);
        this.__parentCanHover.purgeDependencyOnElmtId(k10);
        this.__parentIsActive.purgeDependencyOnElmtId(k10);
        this.__parentFrontColor.purgeDependencyOnElmtId(k10);
        this.__isParentCanTouch.purgeDependencyOnElmtId(k10);
        this.__parentDirection.purgeDependencyOnElmtId(k10);
        this.__isFocus.purgeDependencyOnElmtId(k10);
        this.__secondaryTextSize.purgeDependencyOnElmtId(k10);
        this.__secondaryTextColors.purgeDependencyOnElmtId(k10);
        this.__iconSize.purgeDependencyOnElmtId(k10);
        this.__iconColor.purgeDependencyOnElmtId(k10);
        this.__isOnClick.purgeDependencyOnElmtId(k10);
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
    set arrow(j10) {
        this.__arrow.set(j10);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(i10) {
        this.__icon.set(i10);
    }
    get subIcon() {
        return this.__subIcon.get();
    }
    set subIcon(h10) {
        this.__subIcon.set(h10);
    }
    get button() {
        return this.__button.get();
    }
    set button(g10) {
        this.__button.set(g10);
    }
    get switch() {
        return this.__switch.get();
    }
    set switch(f10) {
        this.__switch.set(f10);
    }
    get checkBox() {
        return this.__checkBox.get();
    }
    set checkBox(e10) {
        this.__checkBox.set(e10);
    }
    get radio() {
        return this.__radio.get();
    }
    set radio(d10) {
        this.__radio.set(d10);
    }
    get image() {
        return this.__image.get();
    }
    set image(c10) {
        this.__image.set(c10);
    }
    get text() {
        return this.__text.get();
    }
    set text(b10) {
        this.__text.set(b10);
    }
    get switchState() {
        return this.__switchState.get();
    }
    set switchState(a10) {
        this.__switchState.set(a10);
    }
    get radioState() {
        return this.__radioState.get();
    }
    set radioState(z9) {
        this.__radioState.set(z9);
    }
    get checkBoxState() {
        return this.__checkBoxState.get();
    }
    set checkBoxState(y9) {
        this.__checkBoxState.set(y9);
    }
    get rightWidth() {
        return this.__rightWidth.get();
    }
    set rightWidth(x9) {
        this.__rightWidth.set(x9);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(w9) {
        this.__secondaryTextColor.set(w9);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(v9) {
        this.__hoveringColor.set(v9);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(u9) {
        this.__activedColor.set(u9);
    }
    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }
    set parentCanFocus(t9) {
        this.__parentCanFocus.set(t9);
    }
    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }
    set parentCanTouch(s9) {
        this.__parentCanTouch.set(s9);
    }
    get parentIsHover() {
        return this.__parentIsHover.get();
    }
    set parentIsHover(r9) {
        this.__parentIsHover.set(r9);
    }
    get parentCanHover() {
        return this.__parentCanHover.get();
    }
    set parentCanHover(q9) {
        this.__parentCanHover.set(q9);
    }
    get parentIsActive() {
        return this.__parentIsActive.get();
    }
    set parentIsActive(p9) {
        this.__parentIsActive.set(p9);
    }
    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }
    set parentFrontColor(o9) {
        this.__parentFrontColor.set(o9);
    }
    get isParentCanTouch() {
        return this.__isParentCanTouch.get();
    }
    set isParentCanTouch(n9) {
        this.__isParentCanTouch.set(n9);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(m9) {
        this.__parentDirection.set(m9);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(l9) {
        this.__isFocus.set(l9);
    }
    get secondaryTextSize() {
        return this.__secondaryTextSize.get();
    }
    set secondaryTextSize(k9) {
        this.__secondaryTextSize.set(k9);
    }
    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }
    set secondaryTextColors(j9) {
        this.__secondaryTextColors.set(j9);
    }
    get iconSize() {
        return this.__iconSize.get();
    }
    set iconSize(i9) {
        this.__iconSize.set(i9);
    }
    get iconColor() {
        return this.__iconColor.get();
    }
    set iconColor(h9) {
        this.__iconColor.set(h9);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(g9) {
        this.__isOnClick.set(g9);
    }
    onWillApplyTheme(f9) {
        this.secondaryTextColor = f9.colors.fontSecondary;
        this.hoveringColor = f9.colors.interactiveHover;
        this.activedColor = f9.colors.interactiveActive;
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
    createButton(q8 = null) {
        this.observeComponentCreation2((y8, z8) => {
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
            Button.onTouch((e9) => {
                if (e9.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (e9.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((d9) => {
                this.parentCanHover = false;
                if (d9 && this.parentFrontColor === HOVERING_COLOR) {
                    this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
                }
                if (!d9) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR :
                            (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((w8, x8) => {
            Row.create();
            Row.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
            });
            Row.focusable(FOCUSABLE);
        }, Row);
        this.observeComponentCreation2((u8, v8) => {
            Text.create(this.button?.text);
            Text.focusable(FOCUSABLE);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(b8, c8 = null) {
        this.observeComponentCreation2((h8, i8) => {
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
            Button.onTouch((p8) => {
                if (p8.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (p8.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((o8) => {
                this.parentCanHover = false;
                if (o8 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!o8) {
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
                    b8.icon?.action();
                }
            });
        }, Button);
        this.observeComponentCreation2((f8, g8) => {
            Image.create(b8.icon?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ICONLIKE_SIZE);
            Image.focusable(FOCUSABLE);
            Image.fillColor(this.iconColor || { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createImage(w7 = null) {
        this.observeComponentCreation2((y7, z7) => {
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
    createText(r7 = null) {
        this.observeComponentCreation2((t7, u7) => {
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
    createArrow(d7 = null) {
        this.observeComponentCreation2((i7, j7) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.focusable(FOCUSABLE);
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((q7) => {
                if (q7.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (q7.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((p7) => {
                this.parentCanHover = false;
                if (p7 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!p7) {
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
        this.observeComponentCreation2((g7, h7) => {
            Image.create(this.arrow?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.focusable(FOCUSABLE);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createRadio(t6 = null) {
        this.observeComponentCreation2((v6, w6) => {
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
            Radio.onTouch((c7) => {
                if (c7.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (c7.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Radio.onHover((b7) => {
                this.parentCanHover = false;
                if (b7 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!b7) {
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
    createCheckBox(j6 = null) {
        this.observeComponentCreation2((l6, m6) => {
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
            Checkbox.onTouch((s6) => {
                if (s6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (s6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Checkbox.onHover((r6) => {
                this.parentCanHover = false;
                if (r6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!r6) {
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
    createSwitch(w5 = null) {
        this.observeComponentCreation2((c6, d6) => {
            Row.create();
            Row.focusable(FOCUSABLE);
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onTouch((i6) => {
                if (i6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (i6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Row.onHover((h6) => {
                this.parentCanHover = false;
                if (h6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!h6) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((z5, a6) => {
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
    createTextArrow(c5 = null) {
        this.observeComponentCreation2((n5, o5) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.focusable(FOCUSABLE);
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((v5) => {
                if (v5.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (v5.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((u5) => {
                this.parentCanHover = false;
                if (u5 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!u5) {
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
        this.observeComponentCreation2((l5, m5) => {
            Row.create({ space: SPECICAL_ROW_SPACE });
        }, Row);
        this.observeComponentCreation2((j5, k5) => {
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
        this.observeComponentCreation2((h5, i5) => {
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
        let b5 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            b5.justifyContent = FlexAlign.SpaceBetween;
        }
        else {
            b5.space = { main: LengthMetrics.vp(this.rowSpace) };
            b5.justifyContent = FlexAlign.End;
        }
        return b5;
    }
    initialRender() {
        this.observeComponentCreation2((z4, a5) => {
            Flex.create(this.getFlexOptions());
            Flex.flexShrink(1);
            Flex.constraintSize({ minWidth: this.rightWidth });
        }, Flex);
        this.observeComponentCreation2((z3, a4) => {
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
                    this.observeComponentCreation2((o4, p4) => {
                        If.create();
                        if (this.parentDirection === FlexDirection.Column) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((t4, u4) => {
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
                    this.observeComponentCreation2((e4, f4) => {
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
    constructor(r3, s3, t3, u3 = -1, v3 = undefined, w3) {
        super(r3, t3, u3, w3);
        if (typeof v3 === "function") {
            this.paramsGenerator_ = v3;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(s3.contentItem, this, "contentItem");
        this.__operateItem = new SynchedPropertyObjectOneWayPU(s3.operateItem, this, "operateItem");
        this.__itemSpace = new SynchedPropertySimpleOneWayPU(s3.itemSpace, this, "itemSpace");
        this.__composeItemPadding = new SynchedPropertyObjectOneWayPU(s3.composeItemPadding, this, "composeItemPadding");
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
        this.setInitiallyProvidedValue(s3);
        this.declareWatch("contentItem", this.onPropChange);
        this.declareWatch("operateItem", this.onPropChange);
        this.declareWatch("fontSizeScale", this.onFontSizeScaleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q3) {
        if (q3.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (q3.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (q3.itemSpace === undefined) {
            this.__itemSpace.set(DEFAULT_ITEM_SPACE_WIDTH);
        }
        if (q3.composeItemPadding === undefined) {
            this.__composeItemPadding.set(null);
        }
        if (q3.frontColor !== undefined) {
            this.frontColor = q3.frontColor;
        }
        if (q3.borderSize !== undefined) {
            this.borderSize = q3.borderSize;
        }
        if (q3.canFocus !== undefined) {
            this.canFocus = q3.canFocus;
        }
        if (q3.canTouch !== undefined) {
            this.canTouch = q3.canTouch;
        }
        if (q3.canHover !== undefined) {
            this.canHover = q3.canHover;
        }
        if (q3.isHover !== undefined) {
            this.isHover = q3.isHover;
        }
        if (q3.itemHeight !== undefined) {
            this.itemHeight = q3.itemHeight;
        }
        if (q3.isActive !== undefined) {
            this.isActive = q3.isActive;
        }
        if (q3.hoveringColor !== undefined) {
            this.hoveringColor = q3.hoveringColor;
        }
        if (q3.touchDownColor !== undefined) {
            this.touchDownColor = q3.touchDownColor;
        }
        if (q3.activedColor !== undefined) {
            this.activedColor = q3.activedColor;
        }
        if (q3.focusOutlineColor !== undefined) {
            this.focusOutlineColor = q3.focusOutlineColor;
        }
        if (q3.isCanTouch !== undefined) {
            this.isCanTouch = q3.isCanTouch;
        }
        if (q3.fontSizeScale !== undefined) {
            this.fontSizeScale = q3.fontSizeScale;
        }
        if (q3.containerDirection !== undefined) {
            this.containerDirection = q3.containerDirection;
        }
        if (q3.contentItemDirection !== undefined) {
            this.contentItemDirection = q3.contentItemDirection;
        }
        if (q3.containerPadding !== undefined) {
            this.containerPadding = q3.containerPadding;
        }
        if (q3.callbackId !== undefined) {
            this.callbackId = q3.callbackId;
        }
        if (q3.isFocus !== undefined) {
            this.isFocus = q3.isFocus;
        }
        if (q3.isHoverBlend !== undefined) {
            this.isHoverBlend = q3.isHoverBlend;
        }
        if (q3.isOnClick !== undefined) {
            this.isOnClick = q3.isOnClick;
        }
    }
    updateStateVars(p3) {
        this.__contentItem.reset(p3.contentItem);
        this.__operateItem.reset(p3.operateItem);
        this.__itemSpace.reset(p3.itemSpace);
        this.__composeItemPadding.reset(p3.composeItemPadding);
    }
    purgeVariableDependenciesOnElmtId(o3) {
        this.__contentItem.purgeDependencyOnElmtId(o3);
        this.__operateItem.purgeDependencyOnElmtId(o3);
        this.__itemSpace.purgeDependencyOnElmtId(o3);
        this.__composeItemPadding.purgeDependencyOnElmtId(o3);
        this.__frontColor.purgeDependencyOnElmtId(o3);
        this.__borderSize.purgeDependencyOnElmtId(o3);
        this.__canFocus.purgeDependencyOnElmtId(o3);
        this.__canTouch.purgeDependencyOnElmtId(o3);
        this.__canHover.purgeDependencyOnElmtId(o3);
        this.__isHover.purgeDependencyOnElmtId(o3);
        this.__itemHeight.purgeDependencyOnElmtId(o3);
        this.__isActive.purgeDependencyOnElmtId(o3);
        this.__hoveringColor.purgeDependencyOnElmtId(o3);
        this.__touchDownColor.purgeDependencyOnElmtId(o3);
        this.__activedColor.purgeDependencyOnElmtId(o3);
        this.__focusOutlineColor.purgeDependencyOnElmtId(o3);
        this.__isCanTouch.purgeDependencyOnElmtId(o3);
        this.__fontSizeScale.purgeDependencyOnElmtId(o3);
        this.__containerDirection.purgeDependencyOnElmtId(o3);
        this.__contentItemDirection.purgeDependencyOnElmtId(o3);
        this.__containerPadding.purgeDependencyOnElmtId(o3);
        this.__isFocus.purgeDependencyOnElmtId(o3);
        this.__isHoverBlend.purgeDependencyOnElmtId(o3);
        this.__isOnClick.purgeDependencyOnElmtId(o3);
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
    set contentItem(n3) {
        this.__contentItem.set(n3);
    }
    get operateItem() {
        return this.__operateItem.get();
    }
    set operateItem(m3) {
        this.__operateItem.set(m3);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(l3) {
        this.__itemSpace.set(l3);
    }
    get composeItemPadding() {
        return this.__composeItemPadding.get();
    }
    set composeItemPadding(k3) {
        this.__composeItemPadding.set(k3);
    }
    get frontColor() {
        return this.__frontColor.get();
    }
    set frontColor(j3) {
        this.__frontColor.set(j3);
    }
    get borderSize() {
        return this.__borderSize.get();
    }
    set borderSize(i3) {
        this.__borderSize.set(i3);
    }
    get canFocus() {
        return this.__canFocus.get();
    }
    set canFocus(h3) {
        this.__canFocus.set(h3);
    }
    get canTouch() {
        return this.__canTouch.get();
    }
    set canTouch(g3) {
        this.__canTouch.set(g3);
    }
    get canHover() {
        return this.__canHover.get();
    }
    set canHover(f3) {
        this.__canHover.set(f3);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(e3) {
        this.__isHover.set(e3);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(d3) {
        this.__itemHeight.set(d3);
    }
    get isActive() {
        return this.__isActive.get();
    }
    set isActive(c3) {
        this.__isActive.set(c3);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(b3) {
        this.__hoveringColor.set(b3);
    }
    get touchDownColor() {
        return this.__touchDownColor.get();
    }
    set touchDownColor(a3) {
        this.__touchDownColor.set(a3);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(z2) {
        this.__activedColor.set(z2);
    }
    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }
    set focusOutlineColor(y2) {
        this.__focusOutlineColor.set(y2);
    }
    get isCanTouch() {
        return this.__isCanTouch.get();
    }
    set isCanTouch(x2) {
        this.__isCanTouch.set(x2);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(w2) {
        this.__fontSizeScale.set(w2);
    }
    get containerDirection() {
        return this.__containerDirection.get();
    }
    set containerDirection(v2) {
        this.__containerDirection.set(v2);
    }
    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }
    set contentItemDirection(u2) {
        this.__contentItemDirection.set(u2);
    }
    get containerPadding() {
        return this.__containerPadding.get();
    }
    set containerPadding(t2) {
        this.__containerPadding.set(t2);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(s2) {
        this.__isFocus.set(s2);
    }
    get isHoverBlend() {
        return this.__isHoverBlend.get();
    }
    set isHoverBlend(r2) {
        this.__isHoverBlend.set(r2);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(q2) {
        this.__isOnClick.set(q2);
    }
    onWillApplyTheme(p2) {
        this.hoveringColor = p2.colors.interactiveHover;
        this.touchDownColor = p2.colors.interactivePressed;
        this.activedColor = p2.colors.interactiveActive;
        this.focusOutlineColor = p2.colors.interactiveFocus;
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
        let o2 = this.composeItemPadding?.start?.value ?? STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return `calc(100% - ${o2}vp)`;
        }
        else if (this.operateItem !== null &&
            this.operateItem.button === undefined &&
            this.operateItem.text === undefined) {
            if (this.operateItem.subIcon !== null) {
                return `calc(100% - ${o2}vp - ${OPERATEITEM_ICON_CLICKABLE_SIZE}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
            }
            else {
                return `calc(100% - ${o2}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
            }
        }
        else {
            return `calc(66% - ${o2}vp)`;
        }
    }
    calculatedRightWidth() {
        let n2 = this.composeItemPadding?.end !== undefined ? this.composeItemPadding?.end?.value : STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return RIGHT_CONTENT_NULL_RIGHTWIDTH;
        }
        else if (this.operateItem !== null && this.operateItem.text === undefined) {
            if (this.operateItem.subIcon !== null) {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${RIGHT_ONLY_ARROW_WIDTH} + ${n2}vp)`;
            }
            else {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${n2}vp)`;
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
    setContainerPadding(l2, m2) {
        this.containerPadding = {
            top: LengthMetrics.vp(LengthMetrics.resource(l2).value),
            end: LengthMetrics.vp(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null).value),
            bottom: LengthMetrics.vp(LengthMetrics.resource(m2).value),
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
        let k2 = ICON_SIZE_MAP.get(this.contentItem?.iconStyle);
        if (k2 && k2 <= HEADSCULPTURE_SIZE) {
            return LengthMetrics.vp(k2 + (this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH));
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
    onMeasureSize(c2, d2, e2) {
        let f2 = { height: 0, width: 0 };
        let g2 = this.getUIContext().getHostContext();
        this.fontSizeScale = g2.config?.fontSizeScale ?? 1;
        d2.forEach((i2) => {
            let j2 = i2.measure(e2);
            f2.width = j2.width;
            f2.height = j2.height;
        });
        return f2;
    }
    initialRender() {
        this.observeComponentCreation2((a2, b2) => {
            Stack.create();
            Stack.padding({
                start: this.getComposeItemLeftPadding(),
                end: this.getComposeItemRightPadding()
            });
        }, Stack);
        this.observeComponentCreation2((r1, s1) => {
            Flex.create(this.getFlexOptions());
            Flex.constraintSize({ minHeight: this.itemHeight });
            Flex.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Flex.backgroundColor(ObservedObject.GetRawObject(this.frontColor));
            Flex.onFocus(() => {
                this.canFocus = true;
                this.isFocus = true;
                this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_focused_backboard'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString();
            });
            Flex.onClick(() => {
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
            Flex.onBlur(() => {
                this.canFocus = false;
                this.isFocus = false;
                this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString();
            });
            Flex.onHover((z1) => {
                this.isHoverBlend = z1;
                this.isHover = z1;
                if (this.canHover) {
                    this.frontColor = z1 ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
                this.frontColor = z1 ? ({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || this.hoveringColor) :
                    ({ "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_background_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent.toString());
            });
            Flex.onTouch((y1) => {
                if (this.isCanTouch) {
                    if (y1.type === TouchType.Down && this.canTouch) {
                        this.frontColor = { "id": -1, "type": 10001, params: ['sys.color.composeListItem_color_press'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || this.touchDownColor;
                    }
                    if (y1.type === TouchType.Up) {
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
            Flex.scale({
                x: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_magnification'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value,
                y: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_magnification'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value
            } || null);
            Flex.shadow(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_focused_shadow_attribute'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value);
            ViewStackProcessor.visualState("normal");
            Flex.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_radio'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: { "id": -1, "type": 10001, params: ['sys.color.composeListItem_normal_stroke_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || Color.Transparent,
                width: { "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_stroke_thickness'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } || null,
            });
            Flex.blur(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_fuzzy_value'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value);
            Flex.shadow(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.composeListItem_normal_shadow_attribute'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }).value);
            Flex.scale({
                x: recoveryScale,
                y: recoveryScale
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
                                let n1 = new ContentItemStruct(this, {}, undefined, l1, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1003, col: 11 });
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
                                }, undefined, a1, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1006, col: 11 });
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
                                }, undefined, l, () => { }, { page: "library/src/main/ets/components/mainpage/composelistitem.ets", line: 1027, col: 11 });
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
