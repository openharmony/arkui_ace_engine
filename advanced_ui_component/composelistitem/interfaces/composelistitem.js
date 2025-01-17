
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
(function (a65) {
    a65[a65["BADGE"] = 1] = "BADGE";
    a65[a65["NORMAL_ICON"] = 2] = "NORMAL_ICON";
    a65[a65["SYSTEM_ICON"] = 3] = "SYSTEM_ICON";
    a65[a65["HEAD_SCULPTURE"] = 4] = "HEAD_SCULPTURE";
    a65[a65["APP_ICON"] = 5] = "APP_ICON";
    a65[a65["PREVIEW"] = 6] = "PREVIEW";
    a65[a65["LONGITUDINAL"] = 7] = "LONGITUDINAL";
    a65[a65["VERTICAL"] = 8] = "VERTICAL";
})(IconType || (IconType = {}));
var FontSizeScaleLevel;
(function (z64) {
    z64[z64["LEVEL1"] = 1.75] = "LEVEL1";
    z64[z64["LEVEL2"] = 2] = "LEVEL2";
    z64[z64["LEVEL3"] = 3.2] = "LEVEL3";
})(FontSizeScaleLevel || (FontSizeScaleLevel = {}));
var ItemHeight;
(function (y64) {
    y64[y64["FIRST_HEIGHT"] = 48] = "FIRST_HEIGHT";
    y64[y64["SECOND_HEIGHT"] = 56] = "SECOND_HEIGHT";
    y64[y64["THIRD_HEIGHT"] = 64] = "THIRD_HEIGHT";
    y64[y64["FOURTH_HEIGHT"] = 72] = "FOURTH_HEIGHT";
    y64[y64["FIFTH_HEIGHT"] = 96] = "FIFTH_HEIGHT";
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
    constructor(s64, t64, u64, v64 = -1, w64 = undefined, x64) {
        super(s64, u64, v64, x64);
        if (typeof w64 === "function") {
            this.paramsGenerator_ = w64;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(t64.iconStyle, this, "iconStyle");
        this.__icon = new SynchedPropertyObjectOneWayPU(t64.icon, this, "icon");
        this.__primaryText = new SynchedPropertyObjectOneWayPU(t64.primaryText, this, "primaryText");
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(t64.secondaryText, this, "secondaryText");
        this.__description = new SynchedPropertyObjectOneWayPU(t64.description, this, "description");
        this.__itemRowSpace = new ObservedPropertySimplePU(NORMAL_ITEM_ROW_SPACE, this, "itemRowSpace");
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(t64.leftWidth, this, "leftWidth");
        this.__primaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColor");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__descriptionColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "descriptionColor");
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(t64.fontSizeScale, this, "fontSizeScale");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(t64.parentDirection, this, "parentDirection");
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(t64.itemDirection, this, "itemDirection");
        this.setInitiallyProvidedValue(t64);
        this.declareWatch("iconStyle", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("primaryText", this.onPropChange);
        this.declareWatch("secondaryText", this.onPropChange);
        this.declareWatch("description", this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r64) {
        if (r64.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (r64.icon === undefined) {
            this.__icon.set(null);
        }
        if (r64.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (r64.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (r64.description === undefined) {
            this.__description.set(null);
        }
        if (r64.itemRowSpace !== undefined) {
            this.itemRowSpace = r64.itemRowSpace;
        }
        if (r64.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (r64.primaryTextColor !== undefined) {
            this.primaryTextColor = r64.primaryTextColor;
        }
        if (r64.secondaryTextColor !== undefined) {
            this.secondaryTextColor = r64.secondaryTextColor;
        }
        if (r64.descriptionColor !== undefined) {
            this.descriptionColor = r64.descriptionColor;
        }
    }
    updateStateVars(q64) {
        this.__iconStyle.reset(q64.iconStyle);
        this.__icon.reset(q64.icon);
        this.__primaryText.reset(q64.primaryText);
        this.__secondaryText.reset(q64.secondaryText);
        this.__description.reset(q64.description);
        this.__leftWidth.reset(q64.leftWidth);
        this.__fontSizeScale.reset(q64.fontSizeScale);
        this.__parentDirection.reset(q64.parentDirection);
        this.__itemDirection.reset(q64.itemDirection);
    }
    purgeVariableDependenciesOnElmtId(p64) {
        this.__iconStyle.purgeDependencyOnElmtId(p64);
        this.__icon.purgeDependencyOnElmtId(p64);
        this.__primaryText.purgeDependencyOnElmtId(p64);
        this.__secondaryText.purgeDependencyOnElmtId(p64);
        this.__description.purgeDependencyOnElmtId(p64);
        this.__itemRowSpace.purgeDependencyOnElmtId(p64);
        this.__leftWidth.purgeDependencyOnElmtId(p64);
        this.__primaryTextColor.purgeDependencyOnElmtId(p64);
        this.__secondaryTextColor.purgeDependencyOnElmtId(p64);
        this.__descriptionColor.purgeDependencyOnElmtId(p64);
        this.__fontSizeScale.purgeDependencyOnElmtId(p64);
        this.__parentDirection.purgeDependencyOnElmtId(p64);
        this.__itemDirection.purgeDependencyOnElmtId(p64);
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get iconStyle() {
        return this.__iconStyle.get();
    }
    set iconStyle(o64) {
        this.__iconStyle.set(o64);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(n64) {
        this.__icon.set(n64);
    }
    get primaryText() {
        return this.__primaryText.get();
    }
    set primaryText(m64) {
        this.__primaryText.set(m64);
    }
    get secondaryText() {
        return this.__secondaryText.get();
    }
    set secondaryText(l64) {
        this.__secondaryText.set(l64);
    }
    get description() {
        return this.__description.get();
    }
    set description(k64) {
        this.__description.set(k64);
    }
    get itemRowSpace() {
        return this.__itemRowSpace.get();
    }
    set itemRowSpace(j64) {
        this.__itemRowSpace.set(j64);
    }
    get leftWidth() {
        return this.__leftWidth.get();
    }
    set leftWidth(i64) {
        this.__leftWidth.set(i64);
    }
    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }
    set primaryTextColor(h64) {
        this.__primaryTextColor.set(h64);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(g64) {
        this.__secondaryTextColor.set(g64);
    }
    get descriptionColor() {
        return this.__descriptionColor.get();
    }
    set descriptionColor(f64) {
        this.__descriptionColor.set(f64);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(e64) {
        this.__fontSizeScale.set(e64);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(d64) {
        this.__parentDirection.set(d64);
    }
    get itemDirection() {
        return this.__itemDirection.get();
    }
    set itemDirection(c64) {
        this.__itemDirection.set(c64);
    }
    onWillApplyTheme(b64) {
        this.primaryTextColor = b64.colors.fontPrimary;
        this.secondaryTextColor = b64.colors.fontSecondary;
        this.descriptionColor = b64.colors.fontTertiary;
    }
    onPropChange() {
        if (this.icon == null && this.iconStyle == null) {
            this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
        }
        else {
            this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        }
    }
    aboutToAppear() {
        this.onPropChange();
    }
    createIcon(s63 = null) {
        this.observeComponentCreation2((t63, u63) => {
            If.create();
            if (this.icon != null && this.iconStyle != null && ICON_SIZE_MAP.has(this.iconStyle)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v63, w63) => {
                        If.create();
                        if (this.iconStyle <= IconType.PREVIEW) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((z63, a64) => {
                                    Image.create(this.icon);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.width(ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.height(ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.focusable(false);
                                    Image.draggable(false);
                                    Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.flexShrink(0);
                                }, Image);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((x63, y63) => {
                                    Image.create(this.icon);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.constraintSize({
                                        minWidth: SPECIAL_ICON_SIZE,
                                        maxWidth: ICON_SIZE_MAP.get(this.iconStyle),
                                        minHeight: SPECIAL_ICON_SIZE,
                                        maxHeight: ICON_SIZE_MAP.get(this.iconStyle)
                                    });
                                    Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.focusable(false);
                                    Image.draggable(false);
                                    Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
    createText(f63 = null) {
        this.observeComponentCreation2((q63, r63) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.margin(this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 ? undefined : {
                top: TEXT_SAFE_MARGIN,
                bottom: TEXT_SAFE_MARGIN
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((o63, p63) => {
            Text.create(this.primaryText);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(ObservedObject.GetRawObject(this.primaryTextColor));
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(true);
            Text.draggable(false);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((k63, l63) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m63, n63) => {
                        Text.create(this.secondaryText);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.draggable(false);
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
        this.observeComponentCreation2((g63, h63) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i63, j63) => {
                        Text.create(this.description);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(ObservedObject.GetRawObject(this.descriptionColor));
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.draggable(false);
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
    isParentColumnDirection() {
        return this.parentDirection === FlexDirection.Column;
    }
    getItemSpace() {
        if (this.isColumnDirection()) {
            return LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }
        return LengthMetrics.vp(this.itemRowSpace);
    }
    initialRender() {
        this.observeComponentCreation2((d63, e63) => {
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
    constructor(x62, y62, z62, a63 = -1, b63 = undefined, c63) {
        super(x62, z62, a63, c63);
        if (typeof b63 === "function") {
            this.paramsGenerator_ = b63;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(y62.arrow, this, "arrow");
        this.__icon = new SynchedPropertyObjectOneWayPU(y62.icon, this, "icon");
        this.__subIcon = new SynchedPropertyObjectOneWayPU(y62.subIcon, this, "subIcon");
        this.__button = new SynchedPropertyObjectOneWayPU(y62.button, this, "button");
        this.__switch = new SynchedPropertyObjectOneWayPU(y62.switch, this, "switch");
        this.__checkBox = new SynchedPropertyObjectOneWayPU(y62.checkBox, this, "checkBox");
        this.__radio = new SynchedPropertyObjectOneWayPU(y62.radio, this, "radio");
        this.__image = new SynchedPropertyObjectOneWayPU(y62.image, this, "image");
        this.__text = new SynchedPropertyObjectOneWayPU(y62.text, this, "text");
        this.__switchState = new ObservedPropertySimplePU(false, this, "switchState");
        this.__radioState = new ObservedPropertySimplePU(false, this, "radioState");
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, "checkBoxState");
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(y62.rightWidth, this, "rightWidth");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, "hoveringColor");
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, "activedColor");
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(y62.parentCanFocus, this, "parentCanFocus");
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(y62.parentCanTouch, this, "parentCanTouch");
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(y62.parentIsHover, this, "parentIsHover");
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(y62.parentCanHover, this, "parentCanHover");
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(y62.parentIsActive, this, "parentIsActive");
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(y62.parentFrontColor, this, "parentFrontColor");
        this.__parentDirection = new SynchedPropertySimpleTwoWayPU(y62.parentDirection, this, "parentDirection");
        this.__rowSpace = new ObservedPropertySimplePU(DEFAULT_ROW_SPACE, this, "rowSpace");
        this.setInitiallyProvidedValue(y62);
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
    setInitiallyProvidedValue(w62) {
        if (w62.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (w62.icon === undefined) {
            this.__icon.set(null);
        }
        if (w62.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (w62.button === undefined) {
            this.__button.set(null);
        }
        if (w62.switch === undefined) {
            this.__switch.set(null);
        }
        if (w62.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (w62.radio === undefined) {
            this.__radio.set(null);
        }
        if (w62.image === undefined) {
            this.__image.set(null);
        }
        if (w62.text === undefined) {
            this.__text.set(null);
        }
        if (w62.switchState !== undefined) {
            this.switchState = w62.switchState;
        }
        if (w62.radioState !== undefined) {
            this.radioState = w62.radioState;
        }
        if (w62.checkBoxState !== undefined) {
            this.checkBoxState = w62.checkBoxState;
        }
        if (w62.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (w62.secondaryTextColor !== undefined) {
            this.secondaryTextColor = w62.secondaryTextColor;
        }
        if (w62.hoveringColor !== undefined) {
            this.hoveringColor = w62.hoveringColor;
        }
        if (w62.activedColor !== undefined) {
            this.activedColor = w62.activedColor;
        }
        if (w62.rowSpace !== undefined) {
            this.rowSpace = w62.rowSpace;
        }
    }
    updateStateVars(v62) {
        this.__arrow.reset(v62.arrow);
        this.__icon.reset(v62.icon);
        this.__subIcon.reset(v62.subIcon);
        this.__button.reset(v62.button);
        this.__switch.reset(v62.switch);
        this.__checkBox.reset(v62.checkBox);
        this.__radio.reset(v62.radio);
        this.__image.reset(v62.image);
        this.__text.reset(v62.text);
        this.__rightWidth.reset(v62.rightWidth);
    }
    purgeVariableDependenciesOnElmtId(u62) {
        this.__arrow.purgeDependencyOnElmtId(u62);
        this.__icon.purgeDependencyOnElmtId(u62);
        this.__subIcon.purgeDependencyOnElmtId(u62);
        this.__button.purgeDependencyOnElmtId(u62);
        this.__switch.purgeDependencyOnElmtId(u62);
        this.__checkBox.purgeDependencyOnElmtId(u62);
        this.__radio.purgeDependencyOnElmtId(u62);
        this.__image.purgeDependencyOnElmtId(u62);
        this.__text.purgeDependencyOnElmtId(u62);
        this.__switchState.purgeDependencyOnElmtId(u62);
        this.__radioState.purgeDependencyOnElmtId(u62);
        this.__checkBoxState.purgeDependencyOnElmtId(u62);
        this.__rightWidth.purgeDependencyOnElmtId(u62);
        this.__secondaryTextColor.purgeDependencyOnElmtId(u62);
        this.__hoveringColor.purgeDependencyOnElmtId(u62);
        this.__activedColor.purgeDependencyOnElmtId(u62);
        this.__parentCanFocus.purgeDependencyOnElmtId(u62);
        this.__parentCanTouch.purgeDependencyOnElmtId(u62);
        this.__parentIsHover.purgeDependencyOnElmtId(u62);
        this.__parentCanHover.purgeDependencyOnElmtId(u62);
        this.__parentIsActive.purgeDependencyOnElmtId(u62);
        this.__parentFrontColor.purgeDependencyOnElmtId(u62);
        this.__parentDirection.purgeDependencyOnElmtId(u62);
        this.__rowSpace.purgeDependencyOnElmtId(u62);
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get arrow() {
        return this.__arrow.get();
    }
    set arrow(t62) {
        this.__arrow.set(t62);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(s62) {
        this.__icon.set(s62);
    }
    get subIcon() {
        return this.__subIcon.get();
    }
    set subIcon(r62) {
        this.__subIcon.set(r62);
    }
    get button() {
        return this.__button.get();
    }
    set button(q62) {
        this.__button.set(q62);
    }
    get switch() {
        return this.__switch.get();
    }
    set switch(p62) {
        this.__switch.set(p62);
    }
    get checkBox() {
        return this.__checkBox.get();
    }
    set checkBox(o62) {
        this.__checkBox.set(o62);
    }
    get radio() {
        return this.__radio.get();
    }
    set radio(n62) {
        this.__radio.set(n62);
    }
    get image() {
        return this.__image.get();
    }
    set image(m62) {
        this.__image.set(m62);
    }
    get text() {
        return this.__text.get();
    }
    set text(l62) {
        this.__text.set(l62);
    }
    get switchState() {
        return this.__switchState.get();
    }
    set switchState(k62) {
        this.__switchState.set(k62);
    }
    get radioState() {
        return this.__radioState.get();
    }
    set radioState(j62) {
        this.__radioState.set(j62);
    }
    get checkBoxState() {
        return this.__checkBoxState.get();
    }
    set checkBoxState(i62) {
        this.__checkBoxState.set(i62);
    }
    get rightWidth() {
        return this.__rightWidth.get();
    }
    set rightWidth(h62) {
        this.__rightWidth.set(h62);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(g62) {
        this.__secondaryTextColor.set(g62);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(f62) {
        this.__hoveringColor.set(f62);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(e62) {
        this.__activedColor.set(e62);
    }
    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }
    set parentCanFocus(d62) {
        this.__parentCanFocus.set(d62);
    }
    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }
    set parentCanTouch(c62) {
        this.__parentCanTouch.set(c62);
    }
    get parentIsHover() {
        return this.__parentIsHover.get();
    }
    set parentIsHover(b62) {
        this.__parentIsHover.set(b62);
    }
    get parentCanHover() {
        return this.__parentCanHover.get();
    }
    set parentCanHover(a62) {
        this.__parentCanHover.set(a62);
    }
    get parentIsActive() {
        return this.__parentIsActive.get();
    }
    set parentIsActive(z61) {
        this.__parentIsActive.set(z61);
    }
    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }
    set parentFrontColor(y61) {
        this.__parentFrontColor.set(y61);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(x61) {
        this.__parentDirection.set(x61);
    }
    get rowSpace() {
        return this.__rowSpace.get();
    }
    set rowSpace(w61) {
        this.__rowSpace.set(w61);
    }
    onWillApplyTheme(v61) {
        this.secondaryTextColor = v61.colors.fontSecondary;
        this.hoveringColor = v61.colors.interactiveHover;
        this.activedColor = v61.colors.interactiveActive;
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
        else {
            this.rowSpace = DEFAULT_ROW_SPACE;
        }
    }
    aboutToAppear() {
        this.onPropChange();
    }
    createButton(n61 = null) {
        this.observeComponentCreation2((s61, t61) => {
            Button.createWithChild();
            Button.padding({ top: 0, bottom: 0 });
            Button.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_activated_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.constraintSize({
                minHeight: BUTTON_SIZE
            });
            Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.labelStyle({
                maxLines: TEXT_MAX_LINE
            });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onHover((u61) => {
                this.parentCanHover = false;
                if (u61 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!u61) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((q61, r61) => {
            Row.create();
            Row.padding({
                left: TEXT_SAFE_MARGIN,
                right: TEXT_SAFE_MARGIN
            });
        }, Row);
        this.observeComponentCreation2((o61, p61) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(g61, h61 = null) {
        this.observeComponentCreation2((k61, l61) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onHover((m61) => {
                this.parentCanHover = false;
                if (m61 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!m61) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(g61.icon?.action);
            Button.flexShrink(0);
        }, Button);
        this.observeComponentCreation2((i61, j61) => {
            Image.create(g61.icon?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ICONLIKE_SIZE);
            Image.focusable(true);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createImage(d61 = null) {
        this.observeComponentCreation2((e61, f61) => {
            Image.create(this.image);
            Image.height(OPERATEITEM_IMAGE_SIZE);
            Image.width(OPERATEITEM_IMAGE_SIZE);
            Image.draggable(false);
            Image.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
        }, Image);
    }
    createText(a61 = null) {
        this.observeComponentCreation2((b61, c61) => {
            Text.create(this.text);
            Text.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
            Text.draggable(false);
            Text.flexShrink(1);
        }, Text);
        Text.pop();
    }
    createArrow(u60 = null) {
        this.observeComponentCreation2((x60, y60) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Button.hitTestBehavior(this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.stateEffect(this.arrow?.action !== undefined);
            Button.hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None);
            Button.onHover((z60) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                this.parentCanHover = false;
                if (z60) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!z60) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
        }, Button);
        this.observeComponentCreation2((v60, w60) => {
            Image.create(this.arrow?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.focusable(true);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
            Image.matchTextDirection(true);
        }, Image);
        Button.pop();
    }
    createRadio(q60 = null) {
        this.observeComponentCreation2((r60, s60) => {
            Radio.create({ value: '', group: '' });
            Radio.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Radio.checked(this.radioState);
            Radio.onChange(this.radio?.onChange);
            Radio.height(OPERATEITEM_ICONLIKE_SIZE);
            Radio.width(OPERATEITEM_ICONLIKE_SIZE);
            Radio.padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE);
            Radio.onFocus(() => {
                this.parentCanFocus = false;
            });
            Radio.hitTestBehavior(HitTestMode.Block);
            Radio.flexShrink(0);
            Radio.onHover((t60) => {
                this.parentCanHover = false;
                if (t60 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!t60) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Radio);
    }
    createCheckBox(m60 = null) {
        this.observeComponentCreation2((n60, o60) => {
            Checkbox.create();
            Checkbox.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange(this.checkBox?.onChange);
            Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.width(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE);
            Checkbox.onFocus(() => {
                this.parentCanFocus = false;
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.onHover((p60) => {
                this.parentCanHover = false;
                if (p60 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!p60) {
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
    createSwitch(g60 = null) {
        this.observeComponentCreation2((j60, k60) => {
            Row.create();
            Row.margin({ end: LengthMetrics.vp(SWITCH_PADDING) });
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onHover((l60) => {
                this.parentCanHover = false;
                if (l60 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!l60) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((h60, i60) => {
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
    createTextArrow(o59 = null) {
        this.observeComponentCreation2((d60, e60) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.hitTestBehavior(this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent);
            Button.labelStyle({
                maxLines: TEXT_MAX_LINE
            });
            Button.backgroundColor(Color.Transparent);
            Button.constraintSize({ minHeight: TEXT_ARROW_HEIGHT });
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
            Button.onHover((f60) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                this.parentCanHover = false;
                if (f60) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!f60) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
        }, Button);
        this.observeComponentCreation2((p59, q59) => {
            If.create();
            if (this.parentDirection === FlexDirection.Column) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b60, c60) => {
                        Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
                        Flex.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Flex);
                    this.observeComponentCreation2((z59, a60) => {
                        Text.create(this.text);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.constraintSize({
                            maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
                        });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((x59, y59) => {
                        Image.create(this.arrow?.value);
                        Image.height(OPERATEITEM_ICONLIKE_SIZE);
                        Image.width(OPERATEITEM_ARROW_WIDTH);
                        Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Image.focusable(false);
                        Image.draggable(false);
                        Image.matchTextDirection(true);
                    }, Image);
                    Flex.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((v59, w59) => {
                        Row.create({ space: SPECICAL_ROW_SPACE });
                        Row.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Row);
                    this.observeComponentCreation2((t59, u59) => {
                        Text.create(this.text);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.constraintSize({
                            maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
                        });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((r59, s59) => {
                        Image.create(this.arrow?.value);
                        Image.height(OPERATEITEM_ICONLIKE_SIZE);
                        Image.width(OPERATEITEM_ARROW_WIDTH);
                        Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
        let n59 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            n59.justifyContent = FlexAlign.SpaceBetween;
        }
        else {
            n59.space = { main: LengthMetrics.vp(this.rowSpace) };
            n59.justifyContent = FlexAlign.End;
        }
        return n59;
    }
    initialRender() {
        this.observeComponentCreation2((l59, m59) => {
            Flex.create(this.getFlexOptions());
            Flex.width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth);
        }, Flex);
        this.observeComponentCreation2((h59, i59) => {
            If.create();
            if (this.button != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.createButton.bind(this)();
                });
            }
            else if (this.image != null) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.createImage.bind(this)();
                });
            }
            else if (this.icon != null && this.text != null) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.createText.bind(this)();
                    this.createIcon.bind(this)(makeBuilderParameterProxy("createIcon", { icon: () => (this["__icon"] ? this["__icon"] : this["icon"]) }));
                });
            }
            else if (this.arrow != null && this.text == null) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.createArrow.bind(this)();
                });
            }
            else if (this.arrow != null && this.text != null) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.createTextArrow.bind(this)();
                });
            }
            else if (this.text != null) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.createText.bind(this)();
                });
            }
            else if (this.radio != null) {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.createRadio.bind(this)();
                });
            }
            else if (this.checkBox != null) {
                this.ifElseBranchUpdateFunction(7, () => {
                    this.createCheckBox.bind(this)();
                });
            }
            else if (this.switch != null) {
                this.ifElseBranchUpdateFunction(8, () => {
                    this.createSwitch.bind(this)();
                });
            }
            else if (this.icon != null) {
                this.ifElseBranchUpdateFunction(9, () => {
                    this.createIcon.bind(this)(makeBuilderParameterProxy("createIcon", { icon: () => (this["__icon"] ? this["__icon"] : this["icon"]) }));
                    this.observeComponentCreation2((j59, k59) => {
                        If.create();
                        if (this.subIcon != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.createIcon.bind(this)(makeBuilderParameterProxy("createIcon", { icon: () => (this["__subIcon"] ? this["__subIcon"] : this["subIcon"]) }));
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
export class ComposeListItem extends ViewPU {
    constructor(b59, c59, d59, e59 = -1, f59 = undefined, g59) {
        super(b59, d59, e59, g59);
        if (typeof f59 === "function") {
            this.paramsGenerator_ = f59;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(c59.contentItem, this, "contentItem");
        this.__operateItem = new SynchedPropertyObjectOneWayPU(c59.operateItem, this, "operateItem");
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
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, "fontSizeScale");
        this.__containerDirection = new ObservedPropertySimplePU(FlexDirection.Row, this, "containerDirection");
        this.__contentItemDirection = new ObservedPropertySimplePU(FlexDirection.Row, this, "contentItemDirection");
        this.__containerPadding = new ObservedPropertyObjectPU(undefined, this, "containerPadding");
        this.__textArrowLeftSafeOffset = new ObservedPropertySimplePU(0, this, "textArrowLeftSafeOffset");
        this.isFollowingSystemFontScale = this.getUIContext().isFollowingSystemFontScale();
        this.maxFontScale = this.getUIContext().getMaxFontScale();
        this.setInitiallyProvidedValue(c59);
        this.declareWatch("contentItem", this.onPropChange);
        this.declareWatch("operateItem", this.onPropChange);
        this.declareWatch("fontSizeScale", this.onFontSizeScaleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(a59) {
        if (a59.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (a59.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (a59.frontColor !== undefined) {
            this.frontColor = a59.frontColor;
        }
        if (a59.borderSize !== undefined) {
            this.borderSize = a59.borderSize;
        }
        if (a59.canFocus !== undefined) {
            this.canFocus = a59.canFocus;
        }
        if (a59.canTouch !== undefined) {
            this.canTouch = a59.canTouch;
        }
        if (a59.canHover !== undefined) {
            this.canHover = a59.canHover;
        }
        if (a59.isHover !== undefined) {
            this.isHover = a59.isHover;
        }
        if (a59.itemHeight !== undefined) {
            this.itemHeight = a59.itemHeight;
        }
        if (a59.isActive !== undefined) {
            this.isActive = a59.isActive;
        }
        if (a59.hoveringColor !== undefined) {
            this.hoveringColor = a59.hoveringColor;
        }
        if (a59.touchDownColor !== undefined) {
            this.touchDownColor = a59.touchDownColor;
        }
        if (a59.activedColor !== undefined) {
            this.activedColor = a59.activedColor;
        }
        if (a59.focusOutlineColor !== undefined) {
            this.focusOutlineColor = a59.focusOutlineColor;
        }
        if (a59.fontSizeScale !== undefined) {
            this.fontSizeScale = a59.fontSizeScale;
        }
        if (a59.containerDirection !== undefined) {
            this.containerDirection = a59.containerDirection;
        }
        if (a59.contentItemDirection !== undefined) {
            this.contentItemDirection = a59.contentItemDirection;
        }
        if (a59.containerPadding !== undefined) {
            this.containerPadding = a59.containerPadding;
        }
        if (a59.textArrowLeftSafeOffset !== undefined) {
            this.textArrowLeftSafeOffset = a59.textArrowLeftSafeOffset;
        }
        if (a59.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = a59.isFollowingSystemFontScale;
        }
        if (a59.maxFontScale !== undefined) {
            this.maxFontScale = a59.maxFontScale;
        }
    }
    updateStateVars(z58) {
        this.__contentItem.reset(z58.contentItem);
        this.__operateItem.reset(z58.operateItem);
    }
    purgeVariableDependenciesOnElmtId(y58) {
        this.__contentItem.purgeDependencyOnElmtId(y58);
        this.__operateItem.purgeDependencyOnElmtId(y58);
        this.__frontColor.purgeDependencyOnElmtId(y58);
        this.__borderSize.purgeDependencyOnElmtId(y58);
        this.__canFocus.purgeDependencyOnElmtId(y58);
        this.__canTouch.purgeDependencyOnElmtId(y58);
        this.__canHover.purgeDependencyOnElmtId(y58);
        this.__isHover.purgeDependencyOnElmtId(y58);
        this.__itemHeight.purgeDependencyOnElmtId(y58);
        this.__isActive.purgeDependencyOnElmtId(y58);
        this.__hoveringColor.purgeDependencyOnElmtId(y58);
        this.__touchDownColor.purgeDependencyOnElmtId(y58);
        this.__activedColor.purgeDependencyOnElmtId(y58);
        this.__focusOutlineColor.purgeDependencyOnElmtId(y58);
        this.__fontSizeScale.purgeDependencyOnElmtId(y58);
        this.__containerDirection.purgeDependencyOnElmtId(y58);
        this.__contentItemDirection.purgeDependencyOnElmtId(y58);
        this.__containerPadding.purgeDependencyOnElmtId(y58);
        this.__textArrowLeftSafeOffset.purgeDependencyOnElmtId(y58);
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get contentItem() {
        return this.__contentItem.get();
    }
    set contentItem(x58) {
        this.__contentItem.set(x58);
    }
    get operateItem() {
        return this.__operateItem.get();
    }
    set operateItem(w58) {
        this.__operateItem.set(w58);
    }
    get frontColor() {
        return this.__frontColor.get();
    }
    set frontColor(v58) {
        this.__frontColor.set(v58);
    }
    get borderSize() {
        return this.__borderSize.get();
    }
    set borderSize(u58) {
        this.__borderSize.set(u58);
    }
    get canFocus() {
        return this.__canFocus.get();
    }
    set canFocus(t58) {
        this.__canFocus.set(t58);
    }
    get canTouch() {
        return this.__canTouch.get();
    }
    set canTouch(s58) {
        this.__canTouch.set(s58);
    }
    get canHover() {
        return this.__canHover.get();
    }
    set canHover(r58) {
        this.__canHover.set(r58);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(q58) {
        this.__isHover.set(q58);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(p58) {
        this.__itemHeight.set(p58);
    }
    get isActive() {
        return this.__isActive.get();
    }
    set isActive(o58) {
        this.__isActive.set(o58);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(n58) {
        this.__hoveringColor.set(n58);
    }
    get touchDownColor() {
        return this.__touchDownColor.get();
    }
    set touchDownColor(m58) {
        this.__touchDownColor.set(m58);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(l58) {
        this.__activedColor.set(l58);
    }
    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }
    set focusOutlineColor(k58) {
        this.__focusOutlineColor.set(k58);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(j58) {
        this.__fontSizeScale.set(j58);
    }
    get containerDirection() {
        return this.__containerDirection.get();
    }
    set containerDirection(i58) {
        this.__containerDirection.set(i58);
    }
    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }
    set contentItemDirection(h58) {
        this.__contentItemDirection.set(h58);
    }
    get containerPadding() {
        return this.__containerPadding.get();
    }
    set containerPadding(g58) {
        this.__containerPadding.set(g58);
    }
    get textArrowLeftSafeOffset() {
        return this.__textArrowLeftSafeOffset.get();
    }
    set textArrowLeftSafeOffset(f58) {
        this.__textArrowLeftSafeOffset.set(f58);
    }
    onWillApplyTheme(e58) {
        this.hoveringColor = e58.colors.interactiveHover;
        this.touchDownColor = e58.colors.interactivePressed;
        this.activedColor = e58.colors.interactiveActive;
        this.focusOutlineColor = e58.colors.interactiveFocus;
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
    calculatedRightWidth() {
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return RIGHT_CONTENT_NULL_RIGHTWIDTH;
        }
        else if (this.operateItem?.switch != null && this.operateItem?.text == null) {
            return RIGHT_ONLY_SWITCH_WIDTH;
        }
        else if (this.operateItem?.checkbox != null && this.operateItem?.text == null) {
            return RIGHT_ONLY_CHECKBOX_WIDTH;
        }
        else if (this.operateItem?.radio != null && this.operateItem?.text == null) {
            return RIGHT_ONLY_RADIO_WIDTH;
        }
        else if (this.operateItem?.icon != null && this.operateItem?.text == null) {
            if (this.operateItem?.subIcon != null) {
                return RIGHT_ICON_SUB_ICON_WIDTH;
            }
            return RIGHT_ONLY_ICON_WIDTH;
        }
        else if (this.operateItem?.image != null && this.operateItem?.text == null) {
            return RIGHT_ONLY_IMAGE_WIDTH;
        }
        else if (this.operateItem?.arrow != null && this.operateItem?.text == null) {
            return RIGHT_ONLY_ARROW_WIDTH;
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
        if (this.fontSizeScale < FontSizeScaleLevel.LEVEL1 || !this.contentItem) {
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
            this.textArrowLeftSafeOffset = TEXT_SAFE_MARGIN;
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
            this.containerPadding = undefined;
        }
    }
    isSingleLine() {
        return !this.contentItem?.secondaryText && !this.contentItem?.description;
    }
    getOperateOffset() {
        if (this.containerDirection === FlexDirection.Row) {
            return LengthMetrics.vp(0);
        }
        let d58 = ICON_SIZE_MAP.get(this.contentItem?.iconStyle);
        if (this.contentItem?.icon && d58 && d58 <= HEADSCULPTURE_SIZE) {
            return LengthMetrics.vp(d58 + NORMAL_ITEM_ROW_SPACE + LISTITEM_PADDING - this.textArrowLeftSafeOffset);
        }
        return LengthMetrics.vp(LISTITEM_PADDING - this.textArrowLeftSafeOffset);
    }
    getMainSpace() {
        if (this.containerDirection === FlexDirection.Column) {
            return LengthMetrics.resource(this.isSingleLine() ? { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
    onMeasureSize(x57, y57, z57) {
        this.fontSizeScale = this.decideFontSizeScale();
        let a58 = { height: 0, width: 0 };
        y57.forEach((b58) => {
            let c58 = b58.measure(z57);
            a58.width = c58.width;
            a58.height = c58.height;
        });
        return a58;
    }
    initialRender() {
        this.observeComponentCreation2((v57, w57) => {
            Stack.create();
            Stack.width('100%');
            Stack.padding({
                left: STACK_PADDING,
                right: STACK_PADDING
            });
        }, Stack);
        this.observeComponentCreation2((s57, t57) => {
            Flex.create(this.getFlexOptions());
            Flex.constraintSize({
                minHeight: this.itemHeight
            });
            Flex.focusable(true);
            Flex.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Flex.backgroundColor(ObservedObject.GetRawObject(this.frontColor));
            Flex.onFocus(() => {
                this.canFocus = true;
            });
            Flex.onBlur(() => {
                this.canFocus = false;
            });
            Flex.onHover((u57) => {
                this.isHover = u57;
                if (this.canHover) {
                    this.frontColor = u57 ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
            });
            ViewStackProcessor.visualState("focused");
            Flex.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: ITEM_BORDER_SHOWN,
                color: this.focusOutlineColor,
                style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState("normal");
            Flex.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: ITEM_BORDER_SHOWN,
                color: Color.Transparent
            });
            ViewStackProcessor.visualState("pressed");
            Flex.backgroundColor(ObservedObject.GetRawObject(this.touchDownColor));
            ViewStackProcessor.visualState();
            Flex.padding(ObservedObject.GetRawObject(this.containerPadding));
        }, Flex);
        this.observeComponentCreation2((m57, n57) => {
            If.create();
            if (this.contentItem === null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((o57, p57) => {
                            if (p57) {
                                let q57 = new ContentItemStruct(this, {}, undefined, o57, () => { }, { page: "libs/composelistitem1108/src/main/ets/components/composelistitem.ets", line: 885, col: 11 });
                                ViewPU.create(q57);
                                let c = () => {
                                    return {};
                                };
                                q57.paramsGenerator_ = c;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(o57, {});
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
        this.observeComponentCreation2((g57, h57) => {
            If.create();
            if (this.contentItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((i57, j57) => {
                            if (j57) {
                                let k57 = new ContentItemStruct(this, {
                                    icon: this.contentItem?.icon,
                                    iconStyle: this.contentItem?.iconStyle,
                                    primaryText: this.contentItem?.primaryText,
                                    secondaryText: this.contentItem?.secondaryText,
                                    description: this.contentItem?.description,
                                    fontSizeScale: this.fontSizeScale,
                                    parentDirection: this.containerDirection,
                                    itemDirection: this.contentItemDirection,
                                }, undefined, i57, () => { }, { page: "libs/composelistitem1108/src/main/ets/components/composelistitem.ets", line: 888, col: 11 });
                                ViewPU.create(k57);
                                let b = () => {
                                    return {
                                        icon: this.contentItem?.icon,
                                        iconStyle: this.contentItem?.iconStyle,
                                        primaryText: this.contentItem?.primaryText,
                                        secondaryText: this.contentItem?.secondaryText,
                                        description: this.contentItem?.description,
                                        fontSizeScale: this.fontSizeScale,
                                        parentDirection: this.containerDirection,
                                        itemDirection: this.contentItemDirection
                                    };
                                };
                                k57.paramsGenerator_ = b;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(i57, {
                                    icon: this.contentItem?.icon,
                                    iconStyle: this.contentItem?.iconStyle,
                                    primaryText: this.contentItem?.primaryText,
                                    secondaryText: this.contentItem?.secondaryText,
                                    description: this.contentItem?.description,
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
        this.observeComponentCreation2((y56, z56) => {
            If.create();
            if (this.operateItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e57, f57) => {
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
                        this.observeComponentCreation2((a57, b57) => {
                            if (b57) {
                                let c57 = new OperateItemStruct(this, {
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
                                }, undefined, a57, () => { }, { page: "libs/composelistitem1108/src/main/ets/components/composelistitem.ets", line: 900, col: 11 });
                                ViewPU.create(c57);
                                let a = () => {
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
                                        parentDirection: this.containerDirection
                                    };
                                };
                                c57.paramsGenerator_ = a;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(a57, {
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