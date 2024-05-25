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
(function (t11) {
    t11[t11["BADGE"] = 1] = "BADGE";
    t11[t11["NORMAL_ICON"] = 2] = "NORMAL_ICON";
    t11[t11["SYSTEM_ICON"] = 3] = "SYSTEM_ICON";
    t11[t11["HEAD_SCULPTURE"] = 4] = "HEAD_SCULPTURE";
    t11[t11["APP_ICON"] = 5] = "APP_ICON";
    t11[t11["PREVIEW"] = 6] = "PREVIEW";
    t11[t11["LONGITUDINAL"] = 7] = "LONGITUDINAL";
    t11[t11["VERTICAL"] = 8] = "VERTICAL";
})(IconType || (IconType = {}));
var ItemHeight;
(function (s11) {
    s11[s11["FIRST_HEIGHT"] = 48] = "FIRST_HEIGHT";
    s11[s11["SECOND_HEIGHT"] = 56] = "SECOND_HEIGHT";
    s11[s11["THIRD_HEIGHT"] = 64] = "THIRD_HEIGHT";
    s11[s11["FOURTH_HEIGHT"] = 72] = "FOURTH_HEIGHT";
    s11[s11["FIFTH_HEIGHT"] = 96] = "FIFTH_HEIGHT";
})(ItemHeight || (ItemHeight = {}));
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
    constructor(m11, n11, o11, p11 = -1, q11 = undefined, r11) {
        super(m11, o11, p11, r11);
        if (typeof q11 === "function") {
            this.paramsGenerator_ = q11;
        }
        this.iconStyle = null;
        this.icon = null;
        this.primaryText = null;
        this.secondaryText = null;
        this.description = null;
        this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        this.__leftWidth = new ObservedPropertySimplePU(LEFT_PART_WIDTH, this, "leftWidth");
        this.__primaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "primaryTextColor");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__descriptionColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "descriptionColor");
        this.__iconImageModifier = new ObservedPropertyObjectPU(null, this, "iconImageModifier");
        this.__primaryTextModifier = new ObservedPropertyObjectPU(null, this, "primaryTextModifier");
        this.__secondaryTextModifier = new ObservedPropertyObjectPU(null, this, "secondaryTextModifier");
        this.__descriptionTextModifier = new ObservedPropertyObjectPU(null, this, "descriptionTextModifier");
        this.__contentItemPadding = new ObservedPropertyObjectPU({ start: LengthMetrics.vp(12) }, this, "contentItemPadding");
        this.__itemSpace = new ObservedPropertySimplePU(DEFAULT_ITEM_SPACE_WIDTH, this, "itemSpace");
        this.setInitiallyProvidedValue(n11);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l11) {
        if (l11.iconStyle !== undefined) {
            this.iconStyle = l11.iconStyle;
        }
        if (l11.icon !== undefined) {
            this.icon = l11.icon;
        }
        if (l11.primaryText !== undefined) {
            this.primaryText = l11.primaryText;
        }
        if (l11.secondaryText !== undefined) {
            this.secondaryText = l11.secondaryText;
        }
        if (l11.description !== undefined) {
            this.description = l11.description;
        }
        if (l11.itemRowSpace !== undefined) {
            this.itemRowSpace = l11.itemRowSpace;
        }
        if (l11.leftWidth !== undefined) {
            this.leftWidth = l11.leftWidth;
        }
        if (l11.primaryTextColor !== undefined) {
            this.primaryTextColor = l11.primaryTextColor;
        }
        if (l11.secondaryTextColor !== undefined) {
            this.secondaryTextColor = l11.secondaryTextColor;
        }
        if (l11.descriptionColor !== undefined) {
            this.descriptionColor = l11.descriptionColor;
        }
        if (l11.iconImageModifier !== undefined) {
            this.iconImageModifier = l11.iconImageModifier;
        }
        if (l11.primaryTextModifier !== undefined) {
            this.primaryTextModifier = l11.primaryTextModifier;
        }
        if (l11.secondaryTextModifier !== undefined) {
            this.secondaryTextModifier = l11.secondaryTextModifier;
        }
        if (l11.descriptionTextModifier !== undefined) {
            this.descriptionTextModifier = l11.descriptionTextModifier;
        }
        if (l11.contentItemPadding !== undefined) {
            this.contentItemPadding = l11.contentItemPadding;
        }
        if (l11.itemSpace !== undefined) {
            this.itemSpace = l11.itemSpace;
        }
    }
    updateStateVars(k11) {
    }
    purgeVariableDependenciesOnElmtId(j11) {
        this.__leftWidth.purgeDependencyOnElmtId(j11);
        this.__primaryTextColor.purgeDependencyOnElmtId(j11);
        this.__secondaryTextColor.purgeDependencyOnElmtId(j11);
        this.__descriptionColor.purgeDependencyOnElmtId(j11);
        this.__iconImageModifier.purgeDependencyOnElmtId(j11);
        this.__primaryTextModifier.purgeDependencyOnElmtId(j11);
        this.__secondaryTextModifier.purgeDependencyOnElmtId(j11);
        this.__descriptionTextModifier.purgeDependencyOnElmtId(j11);
        this.__contentItemPadding.purgeDependencyOnElmtId(j11);
        this.__itemSpace.purgeDependencyOnElmtId(j11);
    }
    aboutToBeDeleted() {
        this.__leftWidth.aboutToBeDeleted();
        this.__primaryTextColor.aboutToBeDeleted();
        this.__secondaryTextColor.aboutToBeDeleted();
        this.__descriptionColor.aboutToBeDeleted();
        this.__iconImageModifier.aboutToBeDeleted();
        this.__primaryTextModifier.aboutToBeDeleted();
        this.__secondaryTextModifier.aboutToBeDeleted();
        this.__descriptionTextModifier.aboutToBeDeleted();
        this.__contentItemPadding.aboutToBeDeleted();
        this.__itemSpace.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get leftWidth() {
        return this.__leftWidth.get();
    }
    set leftWidth(i11) {
        this.__leftWidth.set(i11);
    }
    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }
    set primaryTextColor(h11) {
        this.__primaryTextColor.set(h11);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(g11) {
        this.__secondaryTextColor.set(g11);
    }
    get descriptionColor() {
        return this.__descriptionColor.get();
    }
    set descriptionColor(f11) {
        this.__descriptionColor.set(f11);
    }
    get iconImageModifier() {
        return this.__iconImageModifier.get();
    }
    set iconImageModifier(e11) {
        this.__iconImageModifier.set(e11);
    }
    get primaryTextModifier() {
        return this.__primaryTextModifier.get();
    }
    set primaryTextModifier(d11) {
        this.__primaryTextModifier.set(d11);
    }
    get secondaryTextModifier() {
        return this.__secondaryTextModifier.get();
    }
    set secondaryTextModifier(c11) {
        this.__secondaryTextModifier.set(c11);
    }
    get descriptionTextModifier() {
        return this.__descriptionTextModifier.get();
    }
    set descriptionTextModifier(b11) {
        this.__descriptionTextModifier.set(b11);
    }
    get contentItemPadding() {
        return this.__contentItemPadding.get();
    }
    set contentItemPadding(a11) {
        this.__contentItemPadding.set(a11);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(z10) {
        this.__itemSpace.set(z10);
    }
    onWillApplyTheme(y10) {
        this.primaryTextColor = y10.colors.fontPrimary;
        this.secondaryTextColor = y10.colors.fontSecondary;
        this.descriptionColor = y10.colors.fontTertiary;
    }
    aboutToAppear() {
        if (this.icon == null && this.iconStyle == null) {
            this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
        }
    }
    createIcon(h10 = null) {
        this.observeComponentCreation2((j10, k10) => {
            If.create();
            if (this.icon != null && this.iconStyle != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o10, p10) => {
                        If.create();
                        if (this.iconStyle <= IconType.PREVIEW) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((w10, x10) => {
                                    Image.create(this.icon);
                                    Image.objectFit(ImageFit.Contain);
                                    Image.width(ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.height(ICON_SIZE_MAP.get(this.iconStyle));
                                    Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.focusable(true);
                                    Image.draggable(false);
                                    Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Image.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.iconImageModifier));
                                }, Image);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((s10, t10) => {
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
    createText(k9 = null) {
        this.observeComponentCreation2((f10, g10) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.margin({
                top: TEXT_SAFE_MARGIN,
                bottom: TEXT_SAFE_MARGIN
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((d10, e10) => {
            Text.create(this.primaryText);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(ObservedObject.GetRawObject(this.primaryTextColor));
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(true);
            Text.draggable(false);
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTextModifier));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((w9, x9) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b10, c10) => {
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
        this.observeComponentCreation2((p9, q9) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u9, v9) => {
                        Text.create(this.description);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(ObservedObject.GetRawObject(this.descriptionColor));
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.descriptionTextModifier));
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
    initialRender() {
        this.observeComponentCreation2((i9, j9) => {
            Row.create({ space: this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH });
            Row.margin({ end: LengthMetrics.vp(this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH) });
            Row.constraintSize({ minWidth: this.leftWidth });
            Row.flexShrink(1);
        }, Row);
        this.createIcon.bind(this)(this);
        this.createText.bind(this)(this);
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class OperateItemStruct extends ViewPU {
    constructor(b9, c9, d9, e9 = -1, f9 = undefined, g9) {
        super(b9, d9, e9, g9);
        if (typeof f9 === "function") {
            this.paramsGenerator_ = f9;
        }
        this.arrow = null;
        this.icon = null;
        this.subIcon = null;
        this.button = null;
        this.switch = null;
        this.checkBox = null;
        this.radio = null;
        this.image = null;
        this.text = null;
        this.__switchState = new ObservedPropertySimplePU(false, this, "switchState");
        this.__radioState = new ObservedPropertySimplePU(false, this, "radioState");
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, "checkBoxState");
        this.__rightWidth = new ObservedPropertySimplePU(RIGHT_PART_WIDTH, this, "rightWidth");
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondaryTextColor");
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, "hoveringColor");
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, "activedColor");
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(c9.parentCanFocus, this, "parentCanFocus");
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(c9.parentCanTouch, this, "parentCanTouch");
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(c9.parentIsHover, this, "parentIsHover");
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(c9.parentCanHover, this, "parentCanHover");
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(c9.parentIsActive, this, "parentIsActive");
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(c9.parentFrontColor, this, "parentFrontColor");
        this.__isParentCanTouch = new SynchedPropertySimpleTwoWayPU(c9.isParentCanTouch, this, "isParentCanTouch");
        this.rowSpace = DEFAULT_ROW_SPACE;
        this.setInitiallyProvidedValue(c9);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(a9) {
        if (a9.arrow !== undefined) {
            this.arrow = a9.arrow;
        }
        if (a9.icon !== undefined) {
            this.icon = a9.icon;
        }
        if (a9.subIcon !== undefined) {
            this.subIcon = a9.subIcon;
        }
        if (a9.button !== undefined) {
            this.button = a9.button;
        }
        if (a9.switch !== undefined) {
            this.switch = a9.switch;
        }
        if (a9.checkBox !== undefined) {
            this.checkBox = a9.checkBox;
        }
        if (a9.radio !== undefined) {
            this.radio = a9.radio;
        }
        if (a9.image !== undefined) {
            this.image = a9.image;
        }
        if (a9.text !== undefined) {
            this.text = a9.text;
        }
        if (a9.switchState !== undefined) {
            this.switchState = a9.switchState;
        }
        if (a9.radioState !== undefined) {
            this.radioState = a9.radioState;
        }
        if (a9.checkBoxState !== undefined) {
            this.checkBoxState = a9.checkBoxState;
        }
        if (a9.rightWidth !== undefined) {
            this.rightWidth = a9.rightWidth;
        }
        if (a9.secondaryTextColor !== undefined) {
            this.secondaryTextColor = a9.secondaryTextColor;
        }
        if (a9.hoveringColor !== undefined) {
            this.hoveringColor = a9.hoveringColor;
        }
        if (a9.activedColor !== undefined) {
            this.activedColor = a9.activedColor;
        }
        if (a9.rowSpace !== undefined) {
            this.rowSpace = a9.rowSpace;
        }
    }
    updateStateVars(z8) {
    }
    purgeVariableDependenciesOnElmtId(y8) {
        this.__switchState.purgeDependencyOnElmtId(y8);
        this.__radioState.purgeDependencyOnElmtId(y8);
        this.__checkBoxState.purgeDependencyOnElmtId(y8);
        this.__rightWidth.purgeDependencyOnElmtId(y8);
        this.__secondaryTextColor.purgeDependencyOnElmtId(y8);
        this.__hoveringColor.purgeDependencyOnElmtId(y8);
        this.__activedColor.purgeDependencyOnElmtId(y8);
        this.__parentCanFocus.purgeDependencyOnElmtId(y8);
        this.__parentCanTouch.purgeDependencyOnElmtId(y8);
        this.__parentIsHover.purgeDependencyOnElmtId(y8);
        this.__parentCanHover.purgeDependencyOnElmtId(y8);
        this.__parentIsActive.purgeDependencyOnElmtId(y8);
        this.__parentFrontColor.purgeDependencyOnElmtId(y8);
        this.__isParentCanTouch.purgeDependencyOnElmtId(y8);
    }
    aboutToBeDeleted() {
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get switchState() {
        return this.__switchState.get();
    }
    set switchState(x8) {
        this.__switchState.set(x8);
    }
    get radioState() {
        return this.__radioState.get();
    }
    set radioState(w8) {
        this.__radioState.set(w8);
    }
    get checkBoxState() {
        return this.__checkBoxState.get();
    }
    set checkBoxState(v8) {
        this.__checkBoxState.set(v8);
    }
    get rightWidth() {
        return this.__rightWidth.get();
    }
    set rightWidth(u8) {
        this.__rightWidth.set(u8);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(t8) {
        this.__secondaryTextColor.set(t8);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(s8) {
        this.__hoveringColor.set(s8);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(r8) {
        this.__activedColor.set(r8);
    }
    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }
    set parentCanFocus(q8) {
        this.__parentCanFocus.set(q8);
    }
    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }
    set parentCanTouch(p8) {
        this.__parentCanTouch.set(p8);
    }
    get parentIsHover() {
        return this.__parentIsHover.get();
    }
    set parentIsHover(o8) {
        this.__parentIsHover.set(o8);
    }
    get parentCanHover() {
        return this.__parentCanHover.get();
    }
    set parentCanHover(n8) {
        this.__parentCanHover.set(n8);
    }
    get parentIsActive() {
        return this.__parentIsActive.get();
    }
    set parentIsActive(m8) {
        this.__parentIsActive.set(m8);
    }
    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }
    set parentFrontColor(l8) {
        this.__parentFrontColor.set(l8);
    }
    get isParentCanTouch() {
        return this.__isParentCanTouch.get();
    }
    set isParentCanTouch(k8) {
        this.__isParentCanTouch.set(k8);
    }
    onWillApplyTheme(j8) {
        this.secondaryTextColor = j8.colors.fontSecondary;
        this.hoveringColor = j8.colors.interactiveHover;
        this.activedColor = j8.colors.interactiveActive;
    }
    aboutToAppear() {
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
    createButton(t7, u7 = null) {
        this.observeComponentCreation2((c8, d8) => {
            Button.createWithChild();
            Button.hitTestBehavior(HitTestMode.Block);
            Button.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_activated_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.height(BUTTON_SIZE);
            Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.labelStyle({
                maxLines: TEXT_MAX_LINE
            });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((i8) => {
                if (i8.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (i8.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((h8) => {
                this.parentCanHover = false;
                if (h8 && this.parentFrontColor === HOVERING_COLOR) {
                    this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
                }
                if (!h8) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR :
                            (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
                    }
                }
            });
        }, Button);
        this.observeComponentCreation2((a8, b8) => {
            Row.create();
            Row.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
            });
        }, Row);
        this.observeComponentCreation2((y7, z7) => {
            Text.create(t7);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(f7, g7 = null) {
        this.observeComponentCreation2((l7, m7) => {
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
            Button.onClick((f7.action));
        }, Button);
        this.observeComponentCreation2((j7, k7) => {
            Image.create(f7.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ICONLIKE_SIZE);
            Image.focusable(true);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createImage(z6, a7 = null) {
        this.observeComponentCreation2((c7, d7) => {
            Image.create(z6);
            Image.height(OPERATEITEM_IMAGE_SIZE);
            Image.width(OPERATEITEM_IMAGE_SIZE);
            Image.draggable(false);
            Image.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Image.onAppear(() => {
                this.isParentCanTouch = true;
            });
        }, Image);
    }
    createText(t6, u6 = null) {
        this.observeComponentCreation2((w6, x6) => {
            Text.create(t6);
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
    createArrow(f6, g6 = null) {
        this.observeComponentCreation2((l6, m6) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((s6) => {
                if (s6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (s6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((r6) => {
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
            Button.onAppear(() => {
                this.isParentCanTouch = true;
            });
            Button.onClick(f6.action);
        }, Button);
        this.observeComponentCreation2((j6, k6) => {
            Image.create(f6.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.focusable(true);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    createRadio(u5, v5 = null) {
        this.observeComponentCreation2((x5, y5) => {
            Radio.create({ value: '', group: '' });
            Radio.margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL1) });
            Radio.checked(this.radioState);
            Radio.onChange(u5.onChange);
            Radio.height(OPERATEITEM_ICONLIKE_SIZE);
            Radio.width(OPERATEITEM_ICONLIKE_SIZE);
            Radio.onFocus(() => {
                this.parentCanFocus = false;
            });
            Radio.hitTestBehavior(HitTestMode.Block);
            Radio.onTouch((e6) => {
                if (e6.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (e6.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Radio.onHover((d6) => {
                this.parentCanHover = false;
                if (d6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!d6) {
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
    createCheckBox(j5, k5 = null) {
        this.observeComponentCreation2((m5, n5) => {
            Checkbox.create();
            Checkbox.margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL1) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange(j5.onChange);
            Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.width(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.onFocus(() => {
                this.parentCanFocus = false;
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.onTouch((t5) => {
                if (t5.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (t5.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Checkbox.onHover((s5) => {
                this.parentCanHover = false;
                if (s5 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!s5) {
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
    createSwitch(v4, w4 = null) {
        this.observeComponentCreation2((c5, d5) => {
            Row.create();
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onTouch((i5) => {
                if (i5.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (i5.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Row.onHover((h5) => {
                this.parentCanHover = false;
                if (h5 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!h5) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((z4, a5) => {
            Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
            Toggle.onChange(v4.onChange);
            Toggle.onClick(() => {
                this.switchState = !this.switchState;
            });
            Toggle.hitTestBehavior(HitTestMode.Block);
        }, Toggle);
        Toggle.pop();
        Row.pop();
    }
    createTextArrow(a4, b4, c4 = null) {
        this.observeComponentCreation2((n4, o4) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onTouch((u4) => {
                if (u4.type == TouchType.Down) {
                    this.parentCanTouch = false;
                }
                if (u4.type == TouchType.Up) {
                    this.parentCanTouch = true;
                }
            });
            Button.onHover((t4) => {
                this.parentCanHover = false;
                if (t4 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!t4) {
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
            Button.onClick(b4.action);
        }, Button);
        this.observeComponentCreation2((l4, m4) => {
            Row.create({ space: SPECICAL_ROW_SPACE });
        }, Row);
        this.observeComponentCreation2((j4, k4) => {
            Text.create(a4);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.focusable(true);
            Text.draggable(false);
            Text.constraintSize({
                maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((h4, i4) => {
            Image.create(b4.value);
            Image.height(OPERATEITEM_ICONLIKE_SIZE);
            Image.width(OPERATEITEM_ARROW_WIDTH);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_fourth'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.focusable(true);
            Image.draggable(false);
        }, Image);
        Row.pop();
        Button.pop();
    }
    initialRender() {
        this.observeComponentCreation2((y3, z3) => {
            Row.create({
                space: this.rowSpace
            });
            Row.flexShrink(1);
            Row.justifyContent(FlexAlign.End);
            Row.constraintSize({ minWidth: this.rightWidth });
        }, Row);
        this.observeComponentCreation2((g3, h3) => {
            If.create();
            if (this.button != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.createButton.bind(this)(this.button.text, this);
                });
            }
            else if (this.image != null) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.createImage.bind(this)(this.image, this);
                });
            }
            else if (this.icon != null && this.text != null) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.createText.bind(this)(this.text, this);
                    this.createIcon.bind(this)(this.icon, this);
                });
            }
            else if (this.arrow != null && this.text == null) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.createArrow.bind(this)(this.arrow, this);
                });
            }
            else if (this.arrow != null && this.text != null) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.createTextArrow.bind(this)(this.text, this.arrow, this);
                });
            }
            else if (this.text != null) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.createText.bind(this)(this.text, this);
                });
            }
            else if (this.radio != null) {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.createRadio.bind(this)(this.radio, this);
                });
            }
            else if (this.checkBox != null) {
                this.ifElseBranchUpdateFunction(7, () => {
                    this.createCheckBox.bind(this)(this.checkBox, this);
                });
            }
            else if (this.switch != null) {
                this.ifElseBranchUpdateFunction(8, () => {
                    this.createSwitch.bind(this)(this.switch, this);
                });
            }
            else if (this.icon != null) {
                this.ifElseBranchUpdateFunction(9, () => {
                    this.createIcon.bind(this)(this.icon, this);
                    this.observeComponentCreation2((l3, m3) => {
                        If.create();
                        if (this.subIcon != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.createIcon.bind(this)(this.subIcon, this);
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
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL1 = 0;
OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL2 = -4;
export class ComposeListItem extends ViewPU {
    constructor(y2, z2, a3, b3 = -1, c3 = undefined, d3) {
        super(y2, a3, b3, d3);
        if (typeof c3 === "function") {
            this.paramsGenerator_ = c3;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(z2.contentItem, this, "contentItem");
        this.__operateItem = new SynchedPropertyObjectOneWayPU(z2.operateItem, this, "operateItem");
        this.__itemSpace = new ObservedPropertyObjectPU(null, this, "itemSpace");
        this.__composeItemPadding = new ObservedPropertyObjectPU(null, this, "composeItemPadding");
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
        this.setInitiallyProvidedValue(z2);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(x2) {
        if (x2.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (x2.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (x2.itemSpace !== undefined) {
            this.itemSpace = x2.itemSpace;
        }
        if (x2.composeItemPadding !== undefined) {
            this.composeItemPadding = x2.composeItemPadding;
        }
        if (x2.frontColor !== undefined) {
            this.frontColor = x2.frontColor;
        }
        if (x2.borderSize !== undefined) {
            this.borderSize = x2.borderSize;
        }
        if (x2.canFocus !== undefined) {
            this.canFocus = x2.canFocus;
        }
        if (x2.canTouch !== undefined) {
            this.canTouch = x2.canTouch;
        }
        if (x2.canHover !== undefined) {
            this.canHover = x2.canHover;
        }
        if (x2.isHover !== undefined) {
            this.isHover = x2.isHover;
        }
        if (x2.itemHeight !== undefined) {
            this.itemHeight = x2.itemHeight;
        }
        if (x2.isActive !== undefined) {
            this.isActive = x2.isActive;
        }
        if (x2.hoveringColor !== undefined) {
            this.hoveringColor = x2.hoveringColor;
        }
        if (x2.touchDownColor !== undefined) {
            this.touchDownColor = x2.touchDownColor;
        }
        if (x2.activedColor !== undefined) {
            this.activedColor = x2.activedColor;
        }
        if (x2.focusOutlineColor !== undefined) {
            this.focusOutlineColor = x2.focusOutlineColor;
        }
        if (x2.isCanTouch !== undefined) {
            this.isCanTouch = x2.isCanTouch;
        }
    }
    updateStateVars(w2) {
        this.__contentItem.reset(w2.contentItem);
        this.__operateItem.reset(w2.operateItem);
    }
    purgeVariableDependenciesOnElmtId(v2) {
        this.__contentItem.purgeDependencyOnElmtId(v2);
        this.__operateItem.purgeDependencyOnElmtId(v2);
        this.__itemSpace.purgeDependencyOnElmtId(v2);
        this.__composeItemPadding.purgeDependencyOnElmtId(v2);
        this.__frontColor.purgeDependencyOnElmtId(v2);
        this.__borderSize.purgeDependencyOnElmtId(v2);
        this.__canFocus.purgeDependencyOnElmtId(v2);
        this.__canTouch.purgeDependencyOnElmtId(v2);
        this.__canHover.purgeDependencyOnElmtId(v2);
        this.__isHover.purgeDependencyOnElmtId(v2);
        this.__itemHeight.purgeDependencyOnElmtId(v2);
        this.__isActive.purgeDependencyOnElmtId(v2);
        this.__hoveringColor.purgeDependencyOnElmtId(v2);
        this.__touchDownColor.purgeDependencyOnElmtId(v2);
        this.__activedColor.purgeDependencyOnElmtId(v2);
        this.__focusOutlineColor.purgeDependencyOnElmtId(v2);
        this.__isCanTouch.purgeDependencyOnElmtId(v2);
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get contentItem() {
        return this.__contentItem.get();
    }
    set contentItem(u2) {
        this.__contentItem.set(u2);
    }
    get operateItem() {
        return this.__operateItem.get();
    }
    set operateItem(t2) {
        this.__operateItem.set(t2);
    }
    get itemSpace() {
        return this.__itemSpace.get();
    }
    set itemSpace(s2) {
        this.__itemSpace.set(s2);
    }
    get composeItemPadding() {
        return this.__composeItemPadding.get();
    }
    set composeItemPadding(r2) {
        this.__composeItemPadding.set(r2);
    }
    get frontColor() {
        return this.__frontColor.get();
    }
    set frontColor(q2) {
        this.__frontColor.set(q2);
    }
    get borderSize() {
        return this.__borderSize.get();
    }
    set borderSize(p2) {
        this.__borderSize.set(p2);
    }
    get canFocus() {
        return this.__canFocus.get();
    }
    set canFocus(o2) {
        this.__canFocus.set(o2);
    }
    get canTouch() {
        return this.__canTouch.get();
    }
    set canTouch(n2) {
        this.__canTouch.set(n2);
    }
    get canHover() {
        return this.__canHover.get();
    }
    set canHover(m2) {
        this.__canHover.set(m2);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(l2) {
        this.__isHover.set(l2);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(k2) {
        this.__itemHeight.set(k2);
    }
    get isActive() {
        return this.__isActive.get();
    }
    set isActive(j2) {
        this.__isActive.set(j2);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(i2) {
        this.__hoveringColor.set(i2);
    }
    get touchDownColor() {
        return this.__touchDownColor.get();
    }
    set touchDownColor(h2) {
        this.__touchDownColor.set(h2);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(g2) {
        this.__activedColor.set(g2);
    }
    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }
    set focusOutlineColor(f2) {
        this.__focusOutlineColor.set(f2);
    }
    get isCanTouch() {
        return this.__isCanTouch.get();
    }
    set isCanTouch(e2) {
        this.__isCanTouch.set(e2);
    }
    onWillApplyTheme(d2) {
        this.hoveringColor = d2.colors.interactiveHover;
        this.touchDownColor = d2.colors.interactivePressed;
        this.activedColor = d2.colors.interactiveActive;
        this.focusOutlineColor = d2.colors.interactiveFocus;
    }
    aboutToAppear() {
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
                this.itemHeight = this.contentItem.iconStyle <= IconType.HEAD_SCULPTURE ? ItemHeight.SECOND_HEIGHT : ItemHeight.THIRD_HEIGHT;
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
    calculatedLeftWidth() {
        let c2 = this.composeItemPadding?.start?.value ?? STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return `calc(100% - ${c2}vp)`;
        }
        else if (this.operateItem != null && this.operateItem.button == null && this.operateItem.text == null) {
            if (this.operateItem.subIcon != null) {
                return `calc(100% - ${c2}vp - 40vp - 26vp)`;
            }
            else {
                return `calc(100% - ${c2}vp - 40vp)`;
            }
        }
        else {
            return `calc(66% - ${c2}vp)`;
        }
    }
    calculatedRightWidth() {
        let b2 = this.composeItemPadding?.end !== undefined ? this.composeItemPadding?.end?.value : STACK_PADDING;
        if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
            return RIGHT_CONTENT_NULL_RIGHTWIDTH;
        }
        else if (this.operateItem != null && this.operateItem.text == null) {
            if (this.operateItem.subIcon != null) {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${RIGHT_ONLY_ARROW_WIDTH} + ${b2}vp)`;
            }
            else {
                return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${b2}vp)`;
            }
        }
        else {
            return RIGHT_PART_WIDTH;
        }
    }
    getComposeItemLeftPadding() {
        return this.composeItemPadding?.start !== undefined ?
            this.composeItemPadding?.start : LengthMetrics.vp(STACK_PADDING);
    }
    getComposeItemRightPadding() {
        return this.composeItemPadding?.end !== undefined ?
            this.composeItemPadding?.end : LengthMetrics.vp(STACK_PADDING);
    }
    initialRender() {
        this.observeComponentCreation2((z1, a2) => {
            Stack.create();
            Stack.padding({
                start: this.getComposeItemLeftPadding(),
                end: this.getComposeItemRightPadding()
            });
        }, Stack);
        this.observeComponentCreation2((r1, s1) => {
            Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
            Flex.constraintSize({ minHeight: this.itemHeight });
            Flex.focusable(true);
            Flex.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
            ViewStackProcessor.visualState();
        }, Flex);
        this.observeComponentCreation2((g1, h1) => {
            If.create();
            if (this.contentItem === null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((l1, m1) => {
                            if (m1) {
                                let n1 = new ContentItemStruct(this, {}, undefined, l1, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 750, col: 11 });
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
                                    descriptionTextModifier: this.contentItem.descriptionTextModifier,
                                    leftWidth: this.calculatedLeftWidth(),
                                    contentItemPadding: this.composeItemPadding
                                }, undefined, a1, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 753, col: 11 });
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
                                        descriptionTextModifier: this.contentItem.descriptionTextModifier,
                                        leftWidth: this.calculatedLeftWidth(),
                                        contentItemPadding: this.composeItemPadding
                                    };
                                };
                                c1.paramsGenerator_ = d1;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(a1, {});
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
                        __Common__.onFocus(() => {
                            this.canFocus = false;
                        });
                        __Common__.onBlur(() => {
                            this.canFocus = true;
                        });
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
                                    isParentCanTouch: this.__isCanTouch
                                }, undefined, l, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 768, col: 11 });
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
                                        isParentCanTouch: this.isCanTouch
                                    };
                                };
                                n.paramsGenerator_ = o;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(l, {});
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
