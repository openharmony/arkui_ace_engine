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
(function (z12) {
    z12[z12["BADGE"] = 1] = "BADGE";
    z12[z12["NORMAL_ICON"] = 2] = "NORMAL_ICON";
    z12[z12["SYSTEM_ICON"] = 3] = "SYSTEM_ICON";
    z12[z12["HEAD_SCULPTURE"] = 4] = "HEAD_SCULPTURE";
    z12[z12["APP_ICON"] = 5] = "APP_ICON";
    z12[z12["PREVIEW"] = 6] = "PREVIEW";
    z12[z12["LONGITUDINAL"] = 7] = "LONGITUDINAL";
    z12[z12["VERTICAL"] = 8] = "VERTICAL";
})(IconType || (IconType = {}));
var ItemHeight;
(function (y12) {
    y12[y12["FIRST_HEIGHT"] = 48] = "FIRST_HEIGHT";
    y12[y12["SECOND_HEIGHT"] = 56] = "SECOND_HEIGHT";
    y12[y12["THIRD_HEIGHT"] = 64] = "THIRD_HEIGHT";
    y12[y12["FOURTH_HEIGHT"] = 72] = "FOURTH_HEIGHT";
    y12[y12["FIFTH_HEIGHT"] = 96] = "FIFTH_HEIGHT";
})(ItemHeight || (ItemHeight = {}));
var FontSizeScaleLevel;
(function (x12) {
    x12[x12["LEVEL1"] = 1.75] = "LEVEL1";
    x12[x12["LEVEL2"] = 2] = "LEVEL2";
    x12[x12["LEVEL3"] = 3.2] = "LEVEL3";
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
class ContentItemStruct extends ViewPU {
    constructor(r12, s12, t12, u12 = -1, v12 = undefined, w12) {
        super(r12, t12, u12, w12);
        if (typeof v12 === "function") {
            this.paramsGenerator_ = v12;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(s12.iconStyle, this, "iconStyle");
        this.__icon = new SynchedPropertyObjectOneWayPU(s12.icon, this, "icon");
        this.__primaryText = new SynchedPropertyObjectOneWayPU(s12.primaryText, this, "primaryText");
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(s12.secondaryText, this, "secondaryText");
        this.__description = new SynchedPropertyObjectOneWayPU(s12.description, this, "description");
        this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(s12.leftWidth, this, "leftWidth");
        this.__primaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColor");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__descriptionColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "descriptionColor");
        this.__iconImageModifier = new SynchedPropertyObjectOneWayPU(s12.iconImageModifier, this, "iconImageModifier");
        this.__primaryTextModifier = new SynchedPropertyObjectOneWayPU(s12.primaryTextModifier, this, "primaryTextModifier");
        this.__secondaryTextModifier = new SynchedPropertyObjectOneWayPU(s12.secondaryTextModifier, this, "secondaryTextModifier");
        this.__descriptionModifier = new SynchedPropertyObjectOneWayPU(s12.descriptionModifier, this, "descriptionModifier");
        this.__contentItemPadding = new SynchedPropertyObjectOneWayPU(s12.contentItemPadding, this, "contentItemPadding");
        this.__itemSpace = new SynchedPropertySimpleOneWayPU(s12.itemSpace, this, "itemSpace");
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(s12.fontSizeScale, this, "fontSizeScale");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(s12.parentDirection, this, "parentDirection");
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(s12.itemDirection, this, "itemDirection");
        this.setInitiallyProvidedValue(s12);
        this.declareWatch("iconStyle", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("primaryText", this.onPropChange);
        this.declareWatch("secondaryText", this.onPropChange);
        this.declareWatch("description", this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q12) {
        if (q12.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (q12.icon === undefined) {
            this.__icon.set(null);
        }
        if (q12.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (q12.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (q12.description === undefined) {
            this.__description.set(null);
        }
        if (q12.itemRowSpace !== undefined) {
            this.itemRowSpace = q12.itemRowSpace;
        }
        if (q12.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (q12.primaryTextColor !== undefined) {
            this.primaryTextColor = q12.primaryTextColor;
        }
        if (q12.secondaryTextColor !== undefined) {
            this.secondaryTextColor = q12.secondaryTextColor;
        }
        if (q12.descriptionColor !== undefined) {
            this.descriptionColor = q12.descriptionColor;
        }
        if (q12.iconImageModifier === undefined) {
            this.__iconImageModifier.set(null);
        }
        if (q12.primaryTextModifier === undefined) {
            this.__primaryTextModifier.set(null);
        }
        if (q12.secondaryTextModifier === undefined) {
            this.__secondaryTextModifier.set(null);
        }
        if (q12.descriptionModifier === undefined) {
            this.__descriptionModifier.set(null);
        }
        if (q12.contentItemPadding === undefined) {
            this.__contentItemPadding.set(null);
        }
        if (q12.itemSpace === undefined) {
            this.__itemSpace.set(DEFAULT_ITEM_SPACE_WIDTH);
        }
    }
    updateStateVars(p12) {
        this.__iconStyle.reset(p12.iconStyle);
        this.__icon.reset(p12.icon);
        this.__primaryText.reset(p12.primaryText);
        this.__secondaryText.reset(p12.secondaryText);
        this.__description.reset(p12.description);
        this.__leftWidth.reset(p12.leftWidth);
        this.__iconImageModifier.reset(p12.iconImageModifier);
        this.__primaryTextModifier.reset(p12.primaryTextModifier);
        this.__secondaryTextModifier.reset(p12.secondaryTextModifier);
        this.__descriptionModifier.reset(p12.descriptionModifier);
        this.__contentItemPadding.reset(p12.contentItemPadding);
        this.__itemSpace.reset(p12.itemSpace);
        this.__fontSizeScale.reset(p12.fontSizeScale);
        this.__parentDirection.reset(p12.parentDirection);
        this.__itemDirection.reset(p12.itemDirection);
    }
    purgeVariableDependenciesOnElmtId(o12) {
        this.__iconStyle.purgeDependencyOnElmtId(o12);
        this.__icon.purgeDependencyOnElmtId(o12);
        this.__primaryText.purgeDependencyOnElmtId(o12);
        this.__secondaryText.purgeDependencyOnElmtId(o12);
        this.__description.purgeDependencyOnElmtId(o12);
        this.__leftWidth.purgeDependencyOnElmtId(o12);
        this.__primaryTextColor.purgeDependencyOnElmtId(o12);
        this.__secondaryTextColor.purgeDependencyOnElmtId(o12);
        this.__descriptionColor.purgeDependencyOnElmtId(o12);
        this.__iconImageModifier.purgeDependencyOnElmtId(o12);
        this.__primaryTextModifier.purgeDependencyOnElmtId(o12);
        this.__secondaryTextModifier.purgeDependencyOnElmtId(o12);
        this.__descriptionModifier.purgeDependencyOnElmtId(o12);
        this.__contentItemPadding.purgeDependencyOnElmtId(o12);
        this.__itemSpace.purgeDependencyOnElmtId(o12);
        this.__fontSizeScale.purgeDependencyOnElmtId(o12);
        this.__parentDirection.purgeDependencyOnElmtId(o12);
        this.__itemDirection.purgeDependencyOnElmtId(o12);
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get iconStyle() {
        return this.__iconStyle.get();
    }
    set iconStyle(n12) {
        this.__iconStyle.set(n12);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(m12) {
        this.__icon.set(m12);
    }
    get primaryText() {
        return this.__primaryText.get();
    }
    set primaryText(l12) {
        this.__primaryText.set(l12);
    }
    get secondaryText() {
        return this.__secondaryText.get();
    }
    set secondaryText(k12) {
        this.__secondaryText.set(k12);
    }
    get description() {
        return this.__description.get();
    }
    set description(j12) {
        this.__description.set(j12);
    }
    get leftWidth() {
        return this.__leftWidth.get();
    }
    set leftWidth(i12) {
        this.__leftWidth.set(i12);
    }
    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }
    set primaryTextColor(h12) {
        this.__primaryTextColor.set(h12);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(g12) {
        this.__secondaryTextColor.set(g12);
    }
    get descriptionColor() {
        return this.__descriptionColor.get();
    }
    set descriptionColor(f12) {
        this.__descriptionColor.set(f12);
    }
    get iconImageModifier() {
        return this.__iconImageModifier.get();
    }
    set iconImageModifier(e12) {
        this.__iconImageModifier.set(e12);
    }
    get primaryTextModifier() {
        return this.__primaryTextModifier.get();
    }
    set primaryTextModifier(d12) {
        this.__primaryTextModifier.set(d12);
    }
    get secondaryTextModifier() {
        return this.__secondaryTextModifier.get();
    }
    set secondaryTextModifier(c12) {
        this.__secondaryTextModifier.set(c12);
    }
    get descriptionModifier() {
        return this.__descriptionModifier.get();
    }
    set descriptionModifier(b12) {
        this.__descriptionModifier.set(b12);
    }
    get contentItemPadding() {
        return this.__contentItemPadding.get();
    }
    set contentItemPadding(a12) {
        this.__contentItemPadding.set(a12);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(z11) {
        this.__itemSpace.set(z11);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(y11) {
        this.__fontSizeScale.set(y11);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(x11) {
        this.__parentDirection.set(x11);
    }
    get itemDirection() {
        return this.__itemDirection.get();
    }
    set itemDirection(w11) {
        this.__itemDirection.set(w11);
    }
    onWillApplyTheme(v11) {
        this.primaryTextColor = v11.colors.fontPrimary;
        this.secondaryTextColor = v11.colors.fontSecondary;
        this.descriptionColor = v11.colors.fontTertiary;
    }
    onPropChange() {
        if (this.icon == null && this.iconStyle == null) {
            this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
        }
    }
    aboutToAppear() {
        this.onPropChange();
    }
    createIcon(e11 = null) {
        this.observeComponentCreation2((g11, h11) => {
            If.create();
            if (this.icon != null && this.iconStyle != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l11, m11) => {
                        If.create();
                        if (this.iconStyle <= IconType.PREVIEW) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((t11, u11) => {
                                    Image.create(this.icon);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.width(ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.height(ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.focusable(true);
                                    Image.draggable(false);
                                    Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.iconImageModifier));
                                    Image.flexShrink(0);
                                }, Image);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((p11, q11) => {
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
    createText(h10 = null) {
        this.observeComponentCreation2((c11, d11) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((a11, b11) => {
            Text.create(this.primaryText);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(ObservedObject.GetRawObject(this.primaryTextColor));
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(true);
            Text.draggable(false);
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTextModifier));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((t10, u10) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y10, z10) => {
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
        this.observeComponentCreation2((m10, n10) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r10, s10) => {
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
        this.observeComponentCreation2((f10, g10) => {
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
    constructor(y9, z9, a10, b10 = -1, c10 = undefined, d10) {
        super(y9, a10, b10, d10);
        if (typeof c10 === "function") {
            this.paramsGenerator_ = c10;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(z9.arrow, this, "arrow");
        this.__icon = new SynchedPropertyObjectOneWayPU(z9.icon, this, "icon");
        this.__subIcon = new SynchedPropertyObjectOneWayPU(z9.subIcon, this, "subIcon");
        this.__button = new SynchedPropertyObjectOneWayPU(z9.button, this, "button");
        this.__switch = new SynchedPropertyObjectOneWayPU(z9.switch, this, "switch");
        this.__checkBox = new SynchedPropertyObjectOneWayPU(z9.checkBox, this, "checkBox");
        this.__radio = new SynchedPropertyObjectOneWayPU(z9.radio, this, "radio");
        this.__image = new SynchedPropertyObjectOneWayPU(z9.image, this, "image");
        this.__text = new SynchedPropertyObjectOneWayPU(z9.text, this, "text");
        this.__switchState = new ObservedPropertySimplePU(false, this, "switchState");
        this.__radioState = new ObservedPropertySimplePU(false, this, "radioState");
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, "checkBoxState");
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(z9.rightWidth, this, "rightWidth");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, "hoveringColor");
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, "activedColor");
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(z9.parentCanFocus, this, "parentCanFocus");
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(z9.parentCanTouch, this, "parentCanTouch");
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(z9.parentIsHover, this, "parentIsHover");
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(z9.parentCanHover, this, "parentCanHover");
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(z9.parentIsActive, this, "parentIsActive");
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(z9.parentFrontColor, this, "parentFrontColor");
        this.__isParentCanTouch = new SynchedPropertySimpleTwoWayPU(z9.isParentCanTouch, this, "isParentCanTouch");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(z9.parentDirection, this, "parentDirection");
        this.rowSpace = DEFAULT_ROW_SPACE;
        this.setInitiallyProvidedValue(z9);
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
    setInitiallyProvidedValue(x9) {
        if (x9.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (x9.icon === undefined) {
            this.__icon.set(null);
        }
        if (x9.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (x9.button === undefined) {
            this.__button.set(null);
        }
        if (x9.switch === undefined) {
            this.__switch.set(null);
        }
        if (x9.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (x9.radio === undefined) {
            this.__radio.set(null);
        }
        if (x9.image === undefined) {
            this.__image.set(null);
        }
        if (x9.text === undefined) {
            this.__text.set(null);
        }
        if (x9.switchState !== undefined) {
            this.switchState = x9.switchState;
        }
        if (x9.radioState !== undefined) {
            this.radioState = x9.radioState;
        }
        if (x9.checkBoxState !== undefined) {
            this.checkBoxState = x9.checkBoxState;
        }
        if (x9.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (x9.secondaryTextColor !== undefined) {
            this.secondaryTextColor = x9.secondaryTextColor;
        }
        if (x9.hoveringColor !== undefined) {
            this.hoveringColor = x9.hoveringColor;
        }
        if (x9.activedColor !== undefined) {
            this.activedColor = x9.activedColor;
        }
        if (x9.rowSpace !== undefined) {
            this.rowSpace = x9.rowSpace;
        }
    }
    updateStateVars(w9) {
        this.__arrow.reset(w9.arrow);
        this.__icon.reset(w9.icon);
        this.__subIcon.reset(w9.subIcon);
        this.__button.reset(w9.button);
        this.__switch.reset(w9.switch);
        this.__checkBox.reset(w9.checkBox);
        this.__radio.reset(w9.radio);
        this.__image.reset(w9.image);
        this.__text.reset(w9.text);
        this.__rightWidth.reset(w9.rightWidth);
        this.__parentDirection.reset(w9.parentDirection);
    }
    purgeVariableDependenciesOnElmtId(v9) {
        this.__arrow.purgeDependencyOnElmtId(v9);
        this.__icon.purgeDependencyOnElmtId(v9);
        this.__subIcon.purgeDependencyOnElmtId(v9);
        this.__button.purgeDependencyOnElmtId(v9);
        this.__switch.purgeDependencyOnElmtId(v9);
        this.__checkBox.purgeDependencyOnElmtId(v9);
        this.__radio.purgeDependencyOnElmtId(v9);
        this.__image.purgeDependencyOnElmtId(v9);
        this.__text.purgeDependencyOnElmtId(v9);
        this.__switchState.purgeDependencyOnElmtId(v9);
        this.__radioState.purgeDependencyOnElmtId(v9);
        this.__checkBoxState.purgeDependencyOnElmtId(v9);
        this.__rightWidth.purgeDependencyOnElmtId(v9);
        this.__secondaryTextColor.purgeDependencyOnElmtId(v9);
        this.__hoveringColor.purgeDependencyOnElmtId(v9);
        this.__activedColor.purgeDependencyOnElmtId(v9);
        this.__parentCanFocus.purgeDependencyOnElmtId(v9);
        this.__parentCanTouch.purgeDependencyOnElmtId(v9);
        this.__parentIsHover.purgeDependencyOnElmtId(v9);
        this.__parentCanHover.purgeDependencyOnElmtId(v9);
        this.__parentIsActive.purgeDependencyOnElmtId(v9);
        this.__parentFrontColor.purgeDependencyOnElmtId(v9);
        this.__isParentCanTouch.purgeDependencyOnElmtId(v9);
        this.__parentDirection.purgeDependencyOnElmtId(v9);
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get arrow() {
        return this.__arrow.get();
    }
    set arrow(u9) {
        this.__arrow.set(u9);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(t9) {
        this.__icon.set(t9);
    }
    get subIcon() {
        return this.__subIcon.get();
    }
    set subIcon(s9) {
        this.__subIcon.set(s9);
    }
    get button() {
        return this.__button.get();
    }
    set button(r9) {
        this.__button.set(r9);
    }
    get switch() {
        return this.__switch.get();
    }
    set switch(q9) {
        this.__switch.set(q9);
    }
    get checkBox() {
        return this.__checkBox.get();
    }
    set checkBox(p9) {
        this.__checkBox.set(p9);
    }
    get radio() {
        return this.__radio.get();
    }
    set radio(o9) {
        this.__radio.set(o9);
    }
    get image() {
        return this.__image.get();
    }
    set image(n9) {
        this.__image.set(n9);
    }
    get text() {
        return this.__text.get();
    }
    set text(m9) {
        this.__text.set(m9);
    }
    get switchState() {
        return this.__switchState.get();
    }
    set switchState(l9) {
        this.__switchState.set(l9);
    }
    get radioState() {
        return this.__radioState.get();
    }
    set radioState(k9) {
        this.__radioState.set(k9);
    }
    get checkBoxState() {
        return this.__checkBoxState.get();
    }
    set checkBoxState(j9) {
        this.__checkBoxState.set(j9);
    }
    get rightWidth() {
        return this.__rightWidth.get();
    }
    set rightWidth(i9) {
        this.__rightWidth.set(i9);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(h9) {
        this.__secondaryTextColor.set(h9);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(g9) {
        this.__hoveringColor.set(g9);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(f9) {
        this.__activedColor.set(f9);
    }
    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }
    set parentCanFocus(e9) {
        this.__parentCanFocus.set(e9);
    }
    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }
    set parentCanTouch(d9) {
        this.__parentCanTouch.set(d9);
    }
    get parentIsHover() {
        return this.__parentIsHover.get();
    }
    set parentIsHover(c9) {
        this.__parentIsHover.set(c9);
    }
    get parentCanHover() {
        return this.__parentCanHover.get();
    }
    set parentCanHover(b9) {
        this.__parentCanHover.set(b9);
    }
    get parentIsActive() {
        return this.__parentIsActive.get();
    }
    set parentIsActive(a9) {
        this.__parentIsActive.set(a9);
    }
    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }
    set parentFrontColor(z8) {
        this.__parentFrontColor.set(z8);
    }
    get isParentCanTouch() {
        return this.__isParentCanTouch.get();
    }
    set isParentCanTouch(y8) {
        this.__isParentCanTouch.set(y8);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(x8) {
        this.__parentDirection.set(x8);
    }
    onWillApplyTheme(w8) {
        this.secondaryTextColor = w8.colors.fontSecondary;
        this.hoveringColor = w8.colors.interactiveHover;
        this.activedColor = w8.colors.interactiveActive;
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
    }
    aboutToAppear() {
        this.onPropChange();
    }
    createButton(h8 = null) {
        this.observeComponentCreation2((p8, q8) => {
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
                if (u8 && this.parentFrontColor === HOVERING_COLOR) {
                    this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
                }
                if (!u8) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR :
                            (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((n8, o8) => {
            Row.create();
            Row.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
            });
        }, Row);
        this.observeComponentCreation2((l8, m8) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(t7, u7 = null) {
        this.observeComponentCreation2((z7, a8) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL2) });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((g8) => {
                if (g8.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (g8.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((f8) => {
                this.parentCanHover = false;
                if (f8 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!f8) {
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
            Button.onClick(t7.icon?.action);
        }, Button);
        this.observeComponentCreation2((x7, y7) => {
            Image.create(t7.icon?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ICONLIKE_SIZE);
            Image.focusable(true);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createImage(o7 = null) {
        this.observeComponentCreation2((q7, r7) => {
            Image.create(this.image);
            Image.height(OPERATEITEM_IMAGE_SIZE);
            Image.width(OPERATEITEM_IMAGE_SIZE);
            Image.draggable(false);
            Image.onAppear(() => {
                this.isParentCanTouch = true;
            });
        }, Image);
    }
    createText(j7 = null) {
        this.observeComponentCreation2((l7, m7) => {
            Text.create(this.text);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
            Text.focusable(true);
            Text.draggable(false);
            Text.flexShrink(1);
            Text.onAppear(() => {
                this.isParentCanTouch = true;
            });
        }, Text);
        Text.pop();
    }
    createArrow(w6 = null) {
        this.observeComponentCreation2((b7, c7) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((i7) => {
                if (i7.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (i7.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((h7) => {
                this.parentCanHover = false;
                if (h7 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!h7) {
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
        this.observeComponentCreation2((z6, a7) => {
            Image.create(this.arrow?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.focusable(true);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createRadio(m6 = null) {
        this.observeComponentCreation2((o6, p6) => {
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
            Radio.onTouch((v6) => {
                if (v6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (v6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Radio.onHover((u6) => {
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
            Radio.onAppear(() => {
                this.isParentCanTouch = true;
            });
        }, Radio);
    }
    createCheckBox(c6 = null) {
        this.observeComponentCreation2((e6, f6) => {
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
            Checkbox.onTouch((l6) => {
                if (l6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (l6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Checkbox.onHover((k6) => {
                this.parentCanHover = false;
                if (k6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!k6) {
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
    createSwitch(p5 = null) {
        this.observeComponentCreation2((v5, w5) => {
            Row.create();
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onTouch((b6) => {
                if (b6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (b6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Row.onHover((a6) => {
                this.parentCanHover = false;
                if (a6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!a6) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((s5, t5) => {
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
    createTextArrow(w4 = null) {
        this.observeComponentCreation2((h5, i5) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((o5) => {
                if (o5.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (o5.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((n5) => {
                this.parentCanHover = false;
                if (n5 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!n5) {
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
        this.observeComponentCreation2((f5, g5) => {
            Row.create({ space: SPECICAL_ROW_SPACE });
        }, Row);
        this.observeComponentCreation2((d5, e5) => {
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
        this.observeComponentCreation2((b5, c5) => {
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
        let v4 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            v4.justifyContent = FlexAlign.SpaceBetween;
        }
        else {
            v4.space = { main: LengthMetrics.vp(this.rowSpace) };
            v4.justifyContent = FlexAlign.End;
        }
        return v4;
    }
    initialRender() {
        this.observeComponentCreation2((t4, u4) => {
            Flex.create(this.getFlexOptions());
            Flex.flexShrink(1);
            Flex.constraintSize({ minWidth: this.rightWidth });
        }, Flex);
        this.observeComponentCreation2((t3, u3) => {
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
                    this.observeComponentCreation2((i4, j4) => {
                        If.create();
                        if (this.parentDirection === FlexDirection.Column) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((n4, o4) => {
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
                    this.observeComponentCreation2((y3, z3) => {
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
    constructor(l3, m3, n3, o3 = -1, p3 = undefined, q3) {
        super(l3, n3, o3, q3);
        if (typeof p3 === "function") {
            this.paramsGenerator_ = p3;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(m3.contentItem, this, "contentItem");
        this.__operateItem = new SynchedPropertyObjectOneWayPU(m3.operateItem, this, "operateItem");
        this.__itemSpace = new SynchedPropertySimpleOneWayPU(m3.itemSpace, this, "itemSpace");
        this.__composeItemPadding = new SynchedPropertyObjectOneWayPU(m3.composeItemPadding, this, "composeItemPadding");
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
        this.setInitiallyProvidedValue(m3);
        this.declareWatch("contentItem", this.onPropChange);
        this.declareWatch("operateItem", this.onPropChange);
        this.declareWatch("fontSizeScale", this.onFontSizeScaleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(k3) {
        if (k3.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (k3.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (k3.itemSpace === undefined) {
            this.__itemSpace.set(DEFAULT_ITEM_SPACE_WIDTH);
        }
        if (k3.composeItemPadding === undefined) {
            this.__composeItemPadding.set(null);
        }
        if (k3.frontColor !== undefined) {
            this.frontColor = k3.frontColor;
        }
        if (k3.borderSize !== undefined) {
            this.borderSize = k3.borderSize;
        }
        if (k3.canFocus !== undefined) {
            this.canFocus = k3.canFocus;
        }
        if (k3.canTouch !== undefined) {
            this.canTouch = k3.canTouch;
        }
        if (k3.canHover !== undefined) {
            this.canHover = k3.canHover;
        }
        if (k3.isHover !== undefined) {
            this.isHover = k3.isHover;
        }
        if (k3.itemHeight !== undefined) {
            this.itemHeight = k3.itemHeight;
        }
        if (k3.isActive !== undefined) {
            this.isActive = k3.isActive;
        }
        if (k3.hoveringColor !== undefined) {
            this.hoveringColor = k3.hoveringColor;
        }
        if (k3.touchDownColor !== undefined) {
            this.touchDownColor = k3.touchDownColor;
        }
        if (k3.activedColor !== undefined) {
            this.activedColor = k3.activedColor;
        }
        if (k3.focusOutlineColor !== undefined) {
            this.focusOutlineColor = k3.focusOutlineColor;
        }
        if (k3.isCanTouch !== undefined) {
            this.isCanTouch = k3.isCanTouch;
        }
        if (k3.fontSizeScale !== undefined) {
            this.fontSizeScale = k3.fontSizeScale;
        }
        if (k3.containerDirection !== undefined) {
            this.containerDirection = k3.containerDirection;
        }
        if (k3.contentItemDirection !== undefined) {
            this.contentItemDirection = k3.contentItemDirection;
        }
        if (k3.containerPadding !== undefined) {
            this.containerPadding = k3.containerPadding;
        }
        if (k3.callbackId !== undefined) {
            this.callbackId = k3.callbackId;
        }
    }
    updateStateVars(j3) {
        this.__contentItem.reset(j3.contentItem);
        this.__operateItem.reset(j3.operateItem);
        this.__itemSpace.reset(j3.itemSpace);
        this.__composeItemPadding.reset(j3.composeItemPadding);
    }
    purgeVariableDependenciesOnElmtId(i3) {
        this.__contentItem.purgeDependencyOnElmtId(i3);
        this.__operateItem.purgeDependencyOnElmtId(i3);
        this.__itemSpace.purgeDependencyOnElmtId(i3);
        this.__composeItemPadding.purgeDependencyOnElmtId(i3);
        this.__frontColor.purgeDependencyOnElmtId(i3);
        this.__borderSize.purgeDependencyOnElmtId(i3);
        this.__canFocus.purgeDependencyOnElmtId(i3);
        this.__canTouch.purgeDependencyOnElmtId(i3);
        this.__canHover.purgeDependencyOnElmtId(i3);
        this.__isHover.purgeDependencyOnElmtId(i3);
        this.__itemHeight.purgeDependencyOnElmtId(i3);
        this.__isActive.purgeDependencyOnElmtId(i3);
        this.__hoveringColor.purgeDependencyOnElmtId(i3);
        this.__touchDownColor.purgeDependencyOnElmtId(i3);
        this.__activedColor.purgeDependencyOnElmtId(i3);
        this.__focusOutlineColor.purgeDependencyOnElmtId(i3);
        this.__isCanTouch.purgeDependencyOnElmtId(i3);
        this.__fontSizeScale.purgeDependencyOnElmtId(i3);
        this.__containerDirection.purgeDependencyOnElmtId(i3);
        this.__contentItemDirection.purgeDependencyOnElmtId(i3);
        this.__containerPadding.purgeDependencyOnElmtId(i3);
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get contentItem() {
        return this.__contentItem.get();
    }
    set contentItem(h3) {
        this.__contentItem.set(h3);
    }
    get operateItem() {
        return this.__operateItem.get();
    }
    set operateItem(g3) {
        this.__operateItem.set(g3);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(f3) {
        this.__itemSpace.set(f3);
    }
    get composeItemPadding() {
        return this.__composeItemPadding.get();
    }
    set composeItemPadding(e3) {
        this.__composeItemPadding.set(e3);
    }
    get frontColor() {
        return this.__frontColor.get();
    }
    set frontColor(d3) {
        this.__frontColor.set(d3);
    }
    get borderSize() {
        return this.__borderSize.get();
    }
    set borderSize(c3) {
        this.__borderSize.set(c3);
    }
    get canFocus() {
        return this.__canFocus.get();
    }
    set canFocus(b3) {
        this.__canFocus.set(b3);
    }
    get canTouch() {
        return this.__canTouch.get();
    }
    set canTouch(a3) {
        this.__canTouch.set(a3);
    }
    get canHover() {
        return this.__canHover.get();
    }
    set canHover(z2) {
        this.__canHover.set(z2);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(y2) {
        this.__isHover.set(y2);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(x2) {
        this.__itemHeight.set(x2);
    }
    get isActive() {
        return this.__isActive.get();
    }
    set isActive(w2) {
        this.__isActive.set(w2);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(v2) {
        this.__hoveringColor.set(v2);
    }
    get touchDownColor() {
        return this.__touchDownColor.get();
    }
    set touchDownColor(u2) {
        this.__touchDownColor.set(u2);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(t2) {
        this.__activedColor.set(t2);
    }
    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }
    set focusOutlineColor(s2) {
        this.__focusOutlineColor.set(s2);
    }
    get isCanTouch() {
        return this.__isCanTouch.get();
    }
    set isCanTouch(r2) {
        this.__isCanTouch.set(r2);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(q2) {
        this.__fontSizeScale.set(q2);
    }
    get containerDirection() {
        return this.__containerDirection.get();
    }
    set containerDirection(p2) {
        this.__containerDirection.set(p2);
    }
    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }
    set contentItemDirection(o2) {
        this.__contentItemDirection.set(o2);
    }
    get containerPadding() {
        return this.__containerPadding.get();
    }
    set containerPadding(n2) {
        this.__containerPadding.set(n2);
    }
    onWillApplyTheme(m2) {
        this.hoveringColor = m2.colors.interactiveHover;
        this.touchDownColor = m2.colors.interactivePressed;
        this.activedColor = m2.colors.interactiveActive;
        this.focusOutlineColor = m2.colors.interactiveFocus;
    }
    onPropChange() {
        this.onFontSizeScaleChange();
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
                ItemHeight.SECOND_HEIGHT : ItemHeight.THIRD_HEIGHT;
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
        let l2 = this.composeItemPadding?.start?.value ?? STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return `calc(100% - ${l2}vp)`;
        }
        else if (this.operateItem !== null &&
            this.operateItem.button === undefined &&
            this.operateItem.text === undefined) {
            if (this.operateItem.subIcon !== null) {
                return `calc(100% - ${l2}vp - ${OPERATEITEM_ICON_CLICKABLE_SIZE}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
            }
            else {
                return `calc(100% - ${l2}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
            }
        }
        else {
            return `calc(66% - ${l2}vp)`;
        }
    }
    calculatedRightWidth() {
        let k2 = this.composeItemPadding?.end !== undefined ? this.composeItemPadding?.end?.value : STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return RIGHT_CONTENT_NULL_RIGHTWIDTH;
        }
        else if (this.operateItem !== null && this.operateItem.text === undefined) {
            if (this.operateItem.subIcon !== null) {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${RIGHT_ONLY_ARROW_WIDTH} + ${k2}vp)`;
            }
            else {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${k2}vp)`;
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
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            };
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL2) {
            this.containerPadding = {
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            };
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1) {
            this.containerPadding = {
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            };
        }
        else {
            this.containerPadding = {
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
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
        let j2 = ICON_SIZE_MAP.get(this.contentItem?.iconStyle);
        if (j2 && j2 <= HEADSCULPTURE_SIZE) {
            return LengthMetrics.vp(j2 + (this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH));
        }
        return LengthMetrics.vp(0);
    }
    getMainSpace() {
        if (this.containerDirection === FlexDirection.Column) {
            return LengthMetrics.vp(this.isSingleLine() ? 2 : 16);
        }
        return LengthMetrics.vp(this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH);
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
    onMeasureSize(b2, c2, d2) {
        let e2 = { height: 0, width: 0 };
        let f2 = this.getUIContext().getHostContext();
        this.fontSizeScale = f2.config?.fontSizeScale ?? 1;
        c2.forEach((h2) => {
            let i2 = h2.measure(d2);
            e2.width = i2.width;
            e2.height = i2.height;
        });
        return e2;
    }
    initialRender() {
        this.observeComponentCreation2((z1, a2) => {
            Stack.create();
            Stack.clip(true);
            Stack.padding({
                start: this.getComposeItemLeftPadding(),
                end: this.getComposeItemRightPadding()
            });
        }, Stack);
        this.observeComponentCreation2((r1, s1) => {
            Flex.create(this.getFlexOptions());
            Flex.constraintSize({ minHeight: this.itemHeight });
            Flex.focusable(true);
            Flex.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Flex.backgroundColor(ObservedObject.GetRawObject(this.frontColor));
            Flex.onFocus(() => {
                this.canFocus = true;
            });
            Flex.onBlur(() => {
                this.canFocus = false;
            });
            Flex.onHover((y1) => {
                this.isHover = y1;
                if (this.canHover) {
                    this.frontColor = y1 ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
            });
            Flex.onTouch((x1) => {
                if (this.isCanTouch) {
                    if (x1.type === TouchType.Down && this.canTouch) {
                        this.frontColor = this.touchDownColor;
                    }
                    if (x1.type === TouchType.Up) {
                        this.frontColor = this.isActive ? this.activedColor : Color.Transparent.toString();
                    }
                }
            });
            ViewStackProcessor.visualState("focused");
            Flex.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: { left: this.getFlexLeftOutlineWidth(), right: this.getFlexRightOutlineWidth() },
                color: Color.Transparent
            });
            Flex.outline({
                radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: ITEM_BORDER_SHOWN,
                color: this.focusOutlineColor,
                style: OutlineStyle.SOLID
            });
            ViewStackProcessor.visualState("normal");
            Flex.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: { left: this.getFlexLeftOutlineWidth(), right: this.getFlexRightOutlineWidth() },
                color: Color.Transparent
            });
            Flex.outline({
                radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: 0,
                color: Color.Transparent,
                style: OutlineStyle.SOLID
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
                                let n1 = new ContentItemStruct(this, {}, undefined, l1, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 914, col: 11 });
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
                                    itemDirection: this.contentItemDirection
                                }, undefined, a1, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 917, col: 11 });
                                ViewPU.create(c1);
                                let d1 = () => {
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
                                        itemDirection: this.contentItemDirection
                                    };
                                };
                                c1.paramsGenerator_ = d1;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(a1, {
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
                                    itemDirection: this.contentItemDirection
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
                                }, undefined, l, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 936, col: 11 });
                                ViewPU.create(n);
                                let o = () => {
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
                                        parentDirection: this.containerDirection
                                    };
                                };
                                n.paramsGenerator_ = o;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(l, {
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
    getFlexLeftOutlineWidth() {
        return (this.composeItemPadding?.start !== undefined && this.composeItemPadding?.start?.value >= 12) ?
            (this.composeItemPadding?.start?.value - 4) :
            (this.composeItemPadding === null || this.composeItemPadding?.start === undefined ||
                (this.composeItemPadding?.start !== undefined && this.composeItemPadding?.start?.value >= 8 &&
                    this.composeItemPadding?.start?.value < 12)) ? 8 : this.composeItemPadding?.start?.value;
    }
    getFlexRightOutlineWidth() {
        return (this.composeItemPadding?.end !== undefined && this.composeItemPadding?.end?.value >= 12) ?
            (this.composeItemPadding?.end?.value - 4) :
            (this.composeItemPadding === null || this.composeItemPadding?.end === undefined ||
                (this.composeItemPadding?.end !== undefined && this.composeItemPadding?.end?.value >= 8 &&
                    this.composeItemPadding?.end?.value < 12)) ? 8 : this.composeItemPadding?.end?.value;
    }
    getComposeItemLeftPadding() {
        return this.composeItemPadding === null || this.composeItemPadding?.start === undefined ||
            (this.composeItemPadding?.start !== undefined && this.composeItemPadding?.start?.value >= 12) ?
        LengthMetrics.vp(4) :
            (this.composeItemPadding?.start !== undefined &&
                this.composeItemPadding?.start?.value >= 8 && this.composeItemPadding?.start?.value < 12) ?
            LengthMetrics.vp(this.composeItemPadding?.start?.value - 8) : LengthMetrics.vp(0);
    }
    getComposeItemRightPadding() {
        return this.composeItemPadding === null || this.composeItemPadding?.end === undefined ||
            (this.composeItemPadding?.end !== undefined && this.composeItemPadding?.end?.value >= 12) ?
        LengthMetrics.vp(4) : (this.composeItemPadding?.end !== undefined &&
                this.composeItemPadding?.end?.value >= 8 && this.composeItemPadding?.end?.value < 12) ?
            LengthMetrics.vp(this.composeItemPadding?.end?.value - 8) : LengthMetrics.vp(0);
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default { IconType, ComposeListItem };
