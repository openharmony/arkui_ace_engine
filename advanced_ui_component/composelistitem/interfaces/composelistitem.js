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
const hilog = requireNapi('hilog');
export var IconType;
(function (a17) {
    a17[a17["BADGE"] = 1] = "BADGE";
    a17[a17["NORMAL_ICON"] = 2] = "NORMAL_ICON";
    a17[a17["SYSTEM_ICON"] = 3] = "SYSTEM_ICON";
    a17[a17["HEAD_SCULPTURE"] = 4] = "HEAD_SCULPTURE";
    a17[a17["APP_ICON"] = 5] = "APP_ICON";
    a17[a17["PREVIEW"] = 6] = "PREVIEW";
    a17[a17["LONGITUDINAL"] = 7] = "LONGITUDINAL";
    a17[a17["VERTICAL"] = 8] = "VERTICAL";
})(IconType || (IconType = {}));
var FontSizeScaleLevel;
(function (z16) {
    z16[z16["LEVEL1"] = 1.75] = "LEVEL1";
    z16[z16["LEVEL2"] = 2] = "LEVEL2";
    z16[z16["LEVEL3"] = 3.2] = "LEVEL3";
})(FontSizeScaleLevel || (FontSizeScaleLevel = {}));
var ItemHeight;
(function (y16) {
    y16[y16["FIRST_HEIGHT"] = 48] = "FIRST_HEIGHT";
    y16[y16["SECOND_HEIGHT"] = 56] = "SECOND_HEIGHT";
    y16[y16["THIRD_HEIGHT"] = 64] = "THIRD_HEIGHT";
    y16[y16["FOURTH_HEIGHT"] = 72] = "FOURTH_HEIGHT";
    y16[y16["FIFTH_HEIGHT"] = 96] = "FIFTH_HEIGHT";
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
    constructor(s16, t16, u16, v16 = -1, w16 = undefined, x16) {
        super(s16, u16, v16, x16);
        if (typeof w16 === "function") {
            this.paramsGenerator_ = w16;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(t16.iconStyle, this, "iconStyle");
        this.__icon = new SynchedPropertyObjectOneWayPU(t16.icon, this, "icon");
        this.__primaryText = new SynchedPropertyObjectOneWayPU(t16.primaryText, this, "primaryText");
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(t16.secondaryText, this, "secondaryText");
        this.__description = new SynchedPropertyObjectOneWayPU(t16.description, this, "description");
        this.__itemRowSpace = new ObservedPropertySimplePU(NORMAL_ITEM_ROW_SPACE, this, "itemRowSpace");
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(t16.leftWidth, this, "leftWidth");
        this.__primaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColor");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__descriptionColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "descriptionColor");
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(t16.fontSizeScale, this, "fontSizeScale");
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(t16.parentDirection, this, "parentDirection");
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(t16.itemDirection, this, "itemDirection");
        this.setInitiallyProvidedValue(t16);
        this.declareWatch("iconStyle", this.onPropChange);
        this.declareWatch("icon", this.onPropChange);
        this.declareWatch("primaryText", this.onPropChange);
        this.declareWatch("secondaryText", this.onPropChange);
        this.declareWatch("description", this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r16) {
        if (r16.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (r16.icon === undefined) {
            this.__icon.set(null);
        }
        if (r16.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (r16.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (r16.description === undefined) {
            this.__description.set(null);
        }
        if (r16.itemRowSpace !== undefined) {
            this.itemRowSpace = r16.itemRowSpace;
        }
        if (r16.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (r16.primaryTextColor !== undefined) {
            this.primaryTextColor = r16.primaryTextColor;
        }
        if (r16.secondaryTextColor !== undefined) {
            this.secondaryTextColor = r16.secondaryTextColor;
        }
        if (r16.descriptionColor !== undefined) {
            this.descriptionColor = r16.descriptionColor;
        }
    }
    updateStateVars(q16) {
        this.__iconStyle.reset(q16.iconStyle);
        this.__icon.reset(q16.icon);
        this.__primaryText.reset(q16.primaryText);
        this.__secondaryText.reset(q16.secondaryText);
        this.__description.reset(q16.description);
        this.__leftWidth.reset(q16.leftWidth);
        this.__fontSizeScale.reset(q16.fontSizeScale);
        this.__parentDirection.reset(q16.parentDirection);
        this.__itemDirection.reset(q16.itemDirection);
    }
    purgeVariableDependenciesOnElmtId(p16) {
        this.__iconStyle.purgeDependencyOnElmtId(p16);
        this.__icon.purgeDependencyOnElmtId(p16);
        this.__primaryText.purgeDependencyOnElmtId(p16);
        this.__secondaryText.purgeDependencyOnElmtId(p16);
        this.__description.purgeDependencyOnElmtId(p16);
        this.__itemRowSpace.purgeDependencyOnElmtId(p16);
        this.__leftWidth.purgeDependencyOnElmtId(p16);
        this.__primaryTextColor.purgeDependencyOnElmtId(p16);
        this.__secondaryTextColor.purgeDependencyOnElmtId(p16);
        this.__descriptionColor.purgeDependencyOnElmtId(p16);
        this.__fontSizeScale.purgeDependencyOnElmtId(p16);
        this.__parentDirection.purgeDependencyOnElmtId(p16);
        this.__itemDirection.purgeDependencyOnElmtId(p16);
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
    set iconStyle(o16) {
        this.__iconStyle.set(o16);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(n16) {
        this.__icon.set(n16);
    }
    get primaryText() {
        return this.__primaryText.get();
    }
    set primaryText(m16) {
        this.__primaryText.set(m16);
    }
    get secondaryText() {
        return this.__secondaryText.get();
    }
    set secondaryText(l16) {
        this.__secondaryText.set(l16);
    }
    get description() {
        return this.__description.get();
    }
    set description(k16) {
        this.__description.set(k16);
    }
    get itemRowSpace() {
        return this.__itemRowSpace.get();
    }
    set itemRowSpace(j16) {
        this.__itemRowSpace.set(j16);
    }
    get leftWidth() {
        return this.__leftWidth.get();
    }
    set leftWidth(i16) {
        this.__leftWidth.set(i16);
    }
    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }
    set primaryTextColor(h16) {
        this.__primaryTextColor.set(h16);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(g16) {
        this.__secondaryTextColor.set(g16);
    }
    get descriptionColor() {
        return this.__descriptionColor.get();
    }
    set descriptionColor(f16) {
        this.__descriptionColor.set(f16);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(e16) {
        this.__fontSizeScale.set(e16);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(d16) {
        this.__parentDirection.set(d16);
    }
    get itemDirection() {
        return this.__itemDirection.get();
    }
    set itemDirection(c16) {
        this.__itemDirection.set(c16);
    }
    onWillApplyTheme(b16) {
        this.primaryTextColor = b16.colors.fontPrimary;
        this.secondaryTextColor = b16.colors.fontSecondary;
        this.descriptionColor = b16.colors.fontTertiary;
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
    createIcon(s15 = null) {
        this.observeComponentCreation2((t15, u15) => {
            If.create();
            if (this.icon != null && this.iconStyle != null && ICON_SIZE_MAP.has(this.iconStyle)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v15, w15) => {
                        If.create();
                        if (this.iconStyle <= IconType.PREVIEW) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((z15, a16) => {
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
                                this.observeComponentCreation2((x15, y15) => {
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
    createText(f15 = null) {
        this.observeComponentCreation2((q15, r15) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.margin(this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 ? undefined : {
                top: TEXT_SAFE_MARGIN,
                bottom: TEXT_SAFE_MARGIN
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((o15, p15) => {
            Text.create(this.primaryText);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(ObservedObject.GetRawObject(this.primaryTextColor));
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(true);
            Text.draggable(false);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((k15, l15) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m15, n15) => {
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
        this.observeComponentCreation2((g15, h15) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i15, j15) => {
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
        this.observeComponentCreation2((d15, e15) => {
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
    constructor(x14, y14, z14, a15 = -1, b15 = undefined, c15) {
        super(x14, z14, a15, c15);
        if (typeof b15 === "function") {
            this.paramsGenerator_ = b15;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(y14.arrow, this, "arrow");
        this.__icon = new SynchedPropertyObjectOneWayPU(y14.icon, this, "icon");
        this.__subIcon = new SynchedPropertyObjectOneWayPU(y14.subIcon, this, "subIcon");
        this.__button = new SynchedPropertyObjectOneWayPU(y14.button, this, "button");
        this.__switch = new SynchedPropertyObjectOneWayPU(y14.switch, this, "switch");
        this.__checkBox = new SynchedPropertyObjectOneWayPU(y14.checkBox, this, "checkBox");
        this.__radio = new SynchedPropertyObjectOneWayPU(y14.radio, this, "radio");
        this.__image = new SynchedPropertyObjectOneWayPU(y14.image, this, "image");
        this.__text = new SynchedPropertyObjectOneWayPU(y14.text, this, "text");
        this.__switchState = new ObservedPropertySimplePU(false, this, "switchState");
        this.__radioState = new ObservedPropertySimplePU(false, this, "radioState");
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, "checkBoxState");
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(y14.rightWidth, this, "rightWidth");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, "hoveringColor");
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, "activedColor");
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(y14.parentCanFocus, this, "parentCanFocus");
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(y14.parentCanTouch, this, "parentCanTouch");
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(y14.parentIsHover, this, "parentIsHover");
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(y14.parentCanHover, this, "parentCanHover");
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(y14.parentIsActive, this, "parentIsActive");
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(y14.parentFrontColor, this, "parentFrontColor");
        this.__parentDirection = new SynchedPropertySimpleTwoWayPU(y14.parentDirection, this, "parentDirection");
        this.__rowSpace = new ObservedPropertySimplePU(DEFAULT_ROW_SPACE, this, "rowSpace");
        this.setInitiallyProvidedValue(y14);
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
    setInitiallyProvidedValue(w14) {
        if (w14.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (w14.icon === undefined) {
            this.__icon.set(null);
        }
        if (w14.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (w14.button === undefined) {
            this.__button.set(null);
        }
        if (w14.switch === undefined) {
            this.__switch.set(null);
        }
        if (w14.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (w14.radio === undefined) {
            this.__radio.set(null);
        }
        if (w14.image === undefined) {
            this.__image.set(null);
        }
        if (w14.text === undefined) {
            this.__text.set(null);
        }
        if (w14.switchState !== undefined) {
            this.switchState = w14.switchState;
        }
        if (w14.radioState !== undefined) {
            this.radioState = w14.radioState;
        }
        if (w14.checkBoxState !== undefined) {
            this.checkBoxState = w14.checkBoxState;
        }
        if (w14.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (w14.secondaryTextColor !== undefined) {
            this.secondaryTextColor = w14.secondaryTextColor;
        }
        if (w14.hoveringColor !== undefined) {
            this.hoveringColor = w14.hoveringColor;
        }
        if (w14.activedColor !== undefined) {
            this.activedColor = w14.activedColor;
        }
        if (w14.rowSpace !== undefined) {
            this.rowSpace = w14.rowSpace;
        }
    }
    updateStateVars(v14) {
        this.__arrow.reset(v14.arrow);
        this.__icon.reset(v14.icon);
        this.__subIcon.reset(v14.subIcon);
        this.__button.reset(v14.button);
        this.__switch.reset(v14.switch);
        this.__checkBox.reset(v14.checkBox);
        this.__radio.reset(v14.radio);
        this.__image.reset(v14.image);
        this.__text.reset(v14.text);
        this.__rightWidth.reset(v14.rightWidth);
    }
    purgeVariableDependenciesOnElmtId(u14) {
        this.__arrow.purgeDependencyOnElmtId(u14);
        this.__icon.purgeDependencyOnElmtId(u14);
        this.__subIcon.purgeDependencyOnElmtId(u14);
        this.__button.purgeDependencyOnElmtId(u14);
        this.__switch.purgeDependencyOnElmtId(u14);
        this.__checkBox.purgeDependencyOnElmtId(u14);
        this.__radio.purgeDependencyOnElmtId(u14);
        this.__image.purgeDependencyOnElmtId(u14);
        this.__text.purgeDependencyOnElmtId(u14);
        this.__switchState.purgeDependencyOnElmtId(u14);
        this.__radioState.purgeDependencyOnElmtId(u14);
        this.__checkBoxState.purgeDependencyOnElmtId(u14);
        this.__rightWidth.purgeDependencyOnElmtId(u14);
        this.__secondaryTextColor.purgeDependencyOnElmtId(u14);
        this.__hoveringColor.purgeDependencyOnElmtId(u14);
        this.__activedColor.purgeDependencyOnElmtId(u14);
        this.__parentCanFocus.purgeDependencyOnElmtId(u14);
        this.__parentCanTouch.purgeDependencyOnElmtId(u14);
        this.__parentIsHover.purgeDependencyOnElmtId(u14);
        this.__parentCanHover.purgeDependencyOnElmtId(u14);
        this.__parentIsActive.purgeDependencyOnElmtId(u14);
        this.__parentFrontColor.purgeDependencyOnElmtId(u14);
        this.__parentDirection.purgeDependencyOnElmtId(u14);
        this.__rowSpace.purgeDependencyOnElmtId(u14);
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
    set arrow(t14) {
        this.__arrow.set(t14);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(s14) {
        this.__icon.set(s14);
    }
    get subIcon() {
        return this.__subIcon.get();
    }
    set subIcon(r14) {
        this.__subIcon.set(r14);
    }
    get button() {
        return this.__button.get();
    }
    set button(q14) {
        this.__button.set(q14);
    }
    get switch() {
        return this.__switch.get();
    }
    set switch(p14) {
        this.__switch.set(p14);
    }
    get checkBox() {
        return this.__checkBox.get();
    }
    set checkBox(o14) {
        this.__checkBox.set(o14);
    }
    get radio() {
        return this.__radio.get();
    }
    set radio(n14) {
        this.__radio.set(n14);
    }
    get image() {
        return this.__image.get();
    }
    set image(m14) {
        this.__image.set(m14);
    }
    get text() {
        return this.__text.get();
    }
    set text(l14) {
        this.__text.set(l14);
    }
    get switchState() {
        return this.__switchState.get();
    }
    set switchState(k14) {
        this.__switchState.set(k14);
    }
    get radioState() {
        return this.__radioState.get();
    }
    set radioState(j14) {
        this.__radioState.set(j14);
    }
    get checkBoxState() {
        return this.__checkBoxState.get();
    }
    set checkBoxState(i14) {
        this.__checkBoxState.set(i14);
    }
    get rightWidth() {
        return this.__rightWidth.get();
    }
    set rightWidth(h14) {
        this.__rightWidth.set(h14);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(g14) {
        this.__secondaryTextColor.set(g14);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(f14) {
        this.__hoveringColor.set(f14);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(e14) {
        this.__activedColor.set(e14);
    }
    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }
    set parentCanFocus(d14) {
        this.__parentCanFocus.set(d14);
    }
    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }
    set parentCanTouch(c14) {
        this.__parentCanTouch.set(c14);
    }
    get parentIsHover() {
        return this.__parentIsHover.get();
    }
    set parentIsHover(b14) {
        this.__parentIsHover.set(b14);
    }
    get parentCanHover() {
        return this.__parentCanHover.get();
    }
    set parentCanHover(a14) {
        this.__parentCanHover.set(a14);
    }
    get parentIsActive() {
        return this.__parentIsActive.get();
    }
    set parentIsActive(z13) {
        this.__parentIsActive.set(z13);
    }
    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }
    set parentFrontColor(y13) {
        this.__parentFrontColor.set(y13);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(x13) {
        this.__parentDirection.set(x13);
    }
    get rowSpace() {
        return this.__rowSpace.get();
    }
    set rowSpace(w13) {
        this.__rowSpace.set(w13);
    }
    onWillApplyTheme(v13) {
        this.secondaryTextColor = v13.colors.fontSecondary;
        this.hoveringColor = v13.colors.interactiveHover;
        this.activedColor = v13.colors.interactiveActive;
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
    createButton(n13 = null) {
        this.observeComponentCreation2((s13, t13) => {
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
            Button.onHover((u13) => {
                this.parentCanHover = false;
                if (u13 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!u13) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((q13, r13) => {
            Row.create();
            Row.padding({
                left: TEXT_SAFE_MARGIN,
                right: TEXT_SAFE_MARGIN
            });
        }, Row);
        this.observeComponentCreation2((o13, p13) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(g13, h13 = null) {
        this.observeComponentCreation2((k13, l13) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onHover((m13) => {
                this.parentCanHover = false;
                if (m13 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!m13) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(g13.icon?.action);
            Button.flexShrink(0);
        }, Button);
        this.observeComponentCreation2((i13, j13) => {
            Image.create(g13.icon?.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ICONLIKE_SIZE);
            Image.focusable(true);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createImage(d13 = null) {
        this.observeComponentCreation2((e13, f13) => {
            Image.create(this.image);
            Image.height(OPERATEITEM_IMAGE_SIZE);
            Image.width(OPERATEITEM_IMAGE_SIZE);
            Image.draggable(false);
            Image.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
        }, Image);
    }
    createText(a13 = null) {
        this.observeComponentCreation2((b13, c13) => {
            Text.create(this.text);
            Text.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
            Text.draggable(false);
            Text.flexShrink(1);
        }, Text);
        Text.pop();
    }
    createArrow(u12 = null) {
        this.observeComponentCreation2((x12, y12) => {
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
            Button.onHover((z12) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                this.parentCanHover = false;
                if (z12) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!z12) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
        }, Button);
        this.observeComponentCreation2((v12, w12) => {
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
    createRadio(q12 = null) {
        this.observeComponentCreation2((r12, s12) => {
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
            Radio.onHover((t12) => {
                this.parentCanHover = false;
                if (t12 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!t12) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Radio);
    }
    createCheckBox(m12 = null) {
        this.observeComponentCreation2((n12, o12) => {
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
            Checkbox.flexShrink(0);
            Checkbox.onHover((p12) => {
                this.parentCanHover = false;
                if (p12 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!p12) {
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
    createSwitch(g12 = null) {
        this.observeComponentCreation2((j12, k12) => {
            Row.create();
            Row.margin({ end: LengthMetrics.vp(SWITCH_PADDING) });
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onHover((l12) => {
                this.parentCanHover = false;
                if (l12 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!l12) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((h12, i12) => {
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
    createTextArrow(o11 = null) {
        this.observeComponentCreation2((d12, e12) => {
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
            Button.onHover((f12) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                this.parentCanHover = false;
                if (f12) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!f12) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
        }, Button);
        this.observeComponentCreation2((p11, q11) => {
            If.create();
            if (this.parentDirection === FlexDirection.Column) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b12, c12) => {
                        Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
                        Flex.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Flex);
                    this.observeComponentCreation2((z11, a12) => {
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
                    this.observeComponentCreation2((x11, y11) => {
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
                    this.observeComponentCreation2((v11, w11) => {
                        Row.create({ space: SPECICAL_ROW_SPACE });
                        Row.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Row);
                    this.observeComponentCreation2((t11, u11) => {
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
                    this.observeComponentCreation2((r11, s11) => {
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
        let n11 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            n11.justifyContent = FlexAlign.SpaceBetween;
        }
        else {
            n11.space = { main: LengthMetrics.vp(this.rowSpace) };
            n11.justifyContent = FlexAlign.End;
        }
        return n11;
    }
    initialRender() {
        this.observeComponentCreation2((l11, m11) => {
            Flex.create(this.getFlexOptions());
            Flex.width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth);
        }, Flex);
        this.observeComponentCreation2((h11, i11) => {
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
                    this.observeComponentCreation2((j11, k11) => {
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
    constructor(b11, c11, d11, e11 = -1, f11 = undefined, g11) {
        super(b11, d11, e11, g11);
        if (typeof f11 === "function") {
            this.paramsGenerator_ = f11;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(c11.contentItem, this, "contentItem");
        this.__operateItem = new SynchedPropertyObjectOneWayPU(c11.operateItem, this, "operateItem");
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
        this.callbackId = undefined;
        this.envCallback = {
            onConfigurationUpdated: (h) => {
                this.fontSizeScale = this.decideFontSizeScale();
            },
            onMemoryLevel: (g) => { }
        };
        this.setInitiallyProvidedValue(c11);
        this.declareWatch("contentItem", this.onPropChange);
        this.declareWatch("operateItem", this.onPropChange);
        this.declareWatch("fontSizeScale", this.onFontSizeScaleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(a11) {
        if (a11.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (a11.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (a11.frontColor !== undefined) {
            this.frontColor = a11.frontColor;
        }
        if (a11.borderSize !== undefined) {
            this.borderSize = a11.borderSize;
        }
        if (a11.canFocus !== undefined) {
            this.canFocus = a11.canFocus;
        }
        if (a11.canTouch !== undefined) {
            this.canTouch = a11.canTouch;
        }
        if (a11.canHover !== undefined) {
            this.canHover = a11.canHover;
        }
        if (a11.isHover !== undefined) {
            this.isHover = a11.isHover;
        }
        if (a11.itemHeight !== undefined) {
            this.itemHeight = a11.itemHeight;
        }
        if (a11.isActive !== undefined) {
            this.isActive = a11.isActive;
        }
        if (a11.hoveringColor !== undefined) {
            this.hoveringColor = a11.hoveringColor;
        }
        if (a11.touchDownColor !== undefined) {
            this.touchDownColor = a11.touchDownColor;
        }
        if (a11.activedColor !== undefined) {
            this.activedColor = a11.activedColor;
        }
        if (a11.focusOutlineColor !== undefined) {
            this.focusOutlineColor = a11.focusOutlineColor;
        }
        if (a11.fontSizeScale !== undefined) {
            this.fontSizeScale = a11.fontSizeScale;
        }
        if (a11.containerDirection !== undefined) {
            this.containerDirection = a11.containerDirection;
        }
        if (a11.contentItemDirection !== undefined) {
            this.contentItemDirection = a11.contentItemDirection;
        }
        if (a11.containerPadding !== undefined) {
            this.containerPadding = a11.containerPadding;
        }
        if (a11.textArrowLeftSafeOffset !== undefined) {
            this.textArrowLeftSafeOffset = a11.textArrowLeftSafeOffset;
        }
        if (a11.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = a11.isFollowingSystemFontScale;
        }
        if (a11.maxFontScale !== undefined) {
            this.maxFontScale = a11.maxFontScale;
        }
        if (a11.callbackId !== undefined) {
            this.callbackId = a11.callbackId;
        }
        if (a11.envCallback !== undefined) {
            this.envCallback = a11.envCallback;
        }
    }
    updateStateVars(z10) {
        this.__contentItem.reset(z10.contentItem);
        this.__operateItem.reset(z10.operateItem);
    }
    purgeVariableDependenciesOnElmtId(y10) {
        this.__contentItem.purgeDependencyOnElmtId(y10);
        this.__operateItem.purgeDependencyOnElmtId(y10);
        this.__frontColor.purgeDependencyOnElmtId(y10);
        this.__borderSize.purgeDependencyOnElmtId(y10);
        this.__canFocus.purgeDependencyOnElmtId(y10);
        this.__canTouch.purgeDependencyOnElmtId(y10);
        this.__canHover.purgeDependencyOnElmtId(y10);
        this.__isHover.purgeDependencyOnElmtId(y10);
        this.__itemHeight.purgeDependencyOnElmtId(y10);
        this.__isActive.purgeDependencyOnElmtId(y10);
        this.__hoveringColor.purgeDependencyOnElmtId(y10);
        this.__touchDownColor.purgeDependencyOnElmtId(y10);
        this.__activedColor.purgeDependencyOnElmtId(y10);
        this.__focusOutlineColor.purgeDependencyOnElmtId(y10);
        this.__fontSizeScale.purgeDependencyOnElmtId(y10);
        this.__containerDirection.purgeDependencyOnElmtId(y10);
        this.__contentItemDirection.purgeDependencyOnElmtId(y10);
        this.__containerPadding.purgeDependencyOnElmtId(y10);
        this.__textArrowLeftSafeOffset.purgeDependencyOnElmtId(y10);
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
    set contentItem(x10) {
        this.__contentItem.set(x10);
    }
    get operateItem() {
        return this.__operateItem.get();
    }
    set operateItem(w10) {
        this.__operateItem.set(w10);
    }
    get frontColor() {
        return this.__frontColor.get();
    }
    set frontColor(v10) {
        this.__frontColor.set(v10);
    }
    get borderSize() {
        return this.__borderSize.get();
    }
    set borderSize(u10) {
        this.__borderSize.set(u10);
    }
    get canFocus() {
        return this.__canFocus.get();
    }
    set canFocus(t10) {
        this.__canFocus.set(t10);
    }
    get canTouch() {
        return this.__canTouch.get();
    }
    set canTouch(s10) {
        this.__canTouch.set(s10);
    }
    get canHover() {
        return this.__canHover.get();
    }
    set canHover(r10) {
        this.__canHover.set(r10);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(q10) {
        this.__isHover.set(q10);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(p10) {
        this.__itemHeight.set(p10);
    }
    get isActive() {
        return this.__isActive.get();
    }
    set isActive(o10) {
        this.__isActive.set(o10);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(n10) {
        this.__hoveringColor.set(n10);
    }
    get touchDownColor() {
        return this.__touchDownColor.get();
    }
    set touchDownColor(m10) {
        this.__touchDownColor.set(m10);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(l10) {
        this.__activedColor.set(l10);
    }
    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }
    set focusOutlineColor(k10) {
        this.__focusOutlineColor.set(k10);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(j10) {
        this.__fontSizeScale.set(j10);
    }
    get containerDirection() {
        return this.__containerDirection.get();
    }
    set containerDirection(i10) {
        this.__containerDirection.set(i10);
    }
    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }
    set contentItemDirection(h10) {
        this.__contentItemDirection.set(h10);
    }
    get containerPadding() {
        return this.__containerPadding.get();
    }
    set containerPadding(g10) {
        this.__containerPadding.set(g10);
    }
    get textArrowLeftSafeOffset() {
        return this.__textArrowLeftSafeOffset.get();
    }
    set textArrowLeftSafeOffset(f10) {
        this.__textArrowLeftSafeOffset.set(f10);
    }
    onWillApplyTheme(e10) {
        this.hoveringColor = e10.colors.interactiveHover;
        this.touchDownColor = e10.colors.interactivePressed;
        this.activedColor = e10.colors.interactiveActive;
        this.focusOutlineColor = e10.colors.interactiveFocus;
    }
    onPropChange() {
        this.containerDirection = this.decideContainerDirection();
        this.contentItemDirection = this.decideContentItemDirection();
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
        this.fontSizeScale = this.decideFontSizeScale();
        this.onPropChange();
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        }
        catch (d) {
            let e = d.code;
            let f = d.message;
            hilog.error(0x3900, 'Ace', `ComposeListItem Faild to get environment param error: ${e}, ${f}`);
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
        }
        else if (this.operateItem?.checkbox) {
            return RIGHT_ONLY_CHECKBOX_WIDTH;
        }
        else if (this.operateItem?.radio) {
            return RIGHT_ONLY_RADIO_WIDTH;
        }
        else if (this.operateItem?.icon) {
            if (this.operateItem?.subIcon) {
                return RIGHT_ICON_SUB_ICON_WIDTH;
            }
            return RIGHT_ONLY_ICON_WIDTH;
        }
        else if (this.operateItem?.image) {
            return RIGHT_ONLY_IMAGE_WIDTH;
        }
        else if (this.operateItem?.arrow) {
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
        let d10 = ICON_SIZE_MAP.get(this.contentItem?.iconStyle);
        if (this.contentItem?.icon && d10 && d10 <= HEADSCULPTURE_SIZE) {
            return LengthMetrics.vp(d10 + NORMAL_ITEM_ROW_SPACE + LISTITEM_PADDING - this.textArrowLeftSafeOffset);
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
    initialRender() {
        this.observeComponentCreation2((v9, w9) => {
            Stack.create();
            Stack.width('100%');
            Stack.padding({
                left: STACK_PADDING,
                right: STACK_PADDING
            });
        }, Stack);
        this.observeComponentCreation2((s9, t9) => {
            Flex.create(this.getFlexOptions());
            Flex.height(this.containerDirection === FlexDirection.Column ? 'auto' : undefined);
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
            Flex.onHover((u9) => {
                this.isHover = u9;
                if (this.canHover) {
                    this.frontColor = u9 ? this.hoveringColor :
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
        this.observeComponentCreation2((m9, n9) => {
            If.create();
            if (this.contentItem === null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((o9, p9) => {
                            if (p9) {
                                let q9 = new ContentItemStruct(this, {}, undefined, o9, () => { }, { page: "librarys/composelistitem/src/main/ets/components/composelistitem.ets", line: 903, col: 11 });
                                ViewPU.create(q9);
                                let c = () => {
                                    return {};
                                };
                                q9.paramsGenerator_ = c;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(o9, {});
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
        this.observeComponentCreation2((g9, h9) => {
            If.create();
            if (this.contentItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((i9, j9) => {
                            if (j9) {
                                let k9 = new ContentItemStruct(this, {
                                    icon: this.contentItem?.icon,
                                    iconStyle: this.contentItem?.iconStyle,
                                    primaryText: this.contentItem?.primaryText,
                                    secondaryText: this.contentItem?.secondaryText,
                                    description: this.contentItem?.description,
                                    fontSizeScale: this.fontSizeScale,
                                    parentDirection: this.containerDirection,
                                    itemDirection: this.contentItemDirection,
                                }, undefined, i9, () => { }, { page: "librarys/composelistitem/src/main/ets/components/composelistitem.ets", line: 906, col: 11 });
                                ViewPU.create(k9);
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
                                k9.paramsGenerator_ = b;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(i9, {
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
        this.observeComponentCreation2((y8, z8) => {
            If.create();
            if (this.operateItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e9, f9) => {
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
                        this.observeComponentCreation2((a9, b9) => {
                            if (b9) {
                                let c9 = new OperateItemStruct(this, {
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
                                }, undefined, a9, () => { }, { page: "librarys/composelistitem/src/main/ets/components/composelistitem.ets", line: 918, col: 11 });
                                ViewPU.create(c9);
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
                                c9.paramsGenerator_ = a;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(a9, {
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