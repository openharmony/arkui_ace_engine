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
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const TextModifier = requireNapi('arkui.modifier').TextModifier;
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const resourceManager = requireNapi('resourceManager');
const BusinessError = requireNapi('base');
const common = requireNapi('app.ability.common');

const INDEX_ZERO = 0;
const INDEX_ONE = 1;
const INDEX_TWO = 2;
const SINGLE_LINE_NUM = 1;
const DOUBLE_LINE_NUM = 2;
const SINGLE_LINE_HEIGHT = 56;
const DOUBLE_LINE_HEIGHT = 72;
const BORDER_WIDTH = 2;
const RESOURCE_TYPE_SYMBOL = 40000;
const LEFT_ICON_SIZE = '16vp';
const LEFT_ICON_SIZE_NUMBER = 16;
const LEFT_TEXT_NUMBER = 8;
const BUTTON_ZONE_SIZE = 32;
const BUTTON_HEIGHT = 28;
const ARROW_ICON_WIDTH = 12;
const ARROW_ICON_HEIGHT = 24;
const SINGLE_ICON_ZONE_SIZE = 28;
const RIGHT_SINGLE_ICON_SIZE = '24vp';
const LOADING_SIZE = 24;
const PADDING_LEVEL_2 = 4;
const MAX_RIGHT_WIDTH = '34%';
const MIN_FONT_SIZE = 1.75;
export var OperationType;
(function (m13) {
    m13[m13["TEXT_ARROW"] = 0] = "TEXT_ARROW";
    m13[m13["BUTTON"] = 1] = "BUTTON";
    m13[m13["ICON_GROUP"] = 2] = "ICON_GROUP";
    m13[m13["LOADING"] = 3] = "LOADING";
})(OperationType || (OperationType = {}));
class IconOptions {
}
class ContentIconOption {
}
class FontStyle {
    constructor() {
        this.maxLines = 0;
        this.fontWeight = 0;
    }
}
class SubHeaderTheme {
    constructor() {
        this.fontPrimaryColor = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.fontSecondaryColor = { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.fontButtonColor = { "id": -1, "type": 10001, params: ['sys.color.font_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.iconArrowColor = { "id": -1, "type": 10001, params: ['sys.color.icon_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.textArrowHoverBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.borderFocusColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_focus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.leftIconColor = { "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.rightIconColor = { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    }
}
function __Text__secondaryTitleStyles(l13) {
    Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Subtitle_S'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontColor(l13?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(l13?.fontWeight);
    Text.maxLines(l13?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(l13?.alignment);
}
function __Text__primaryTitleStyles(k13) {
    Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Subtitle_L'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontColor(k13?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(k13?.fontWeight);
    Text.maxLines(k13?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(k13?.alignment);
}
class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }
    applyNormalAttribute(j13) {
        if (this.isAgeing) {
            j13.width('100%');
        }
        else {
        }
    }
}
export class SubHeader extends ViewPU {
    constructor(d13, e13, f13, g13 = -1, h13 = undefined, i13) {
        super(d13, f13, g13, i13);
        if (typeof h13 === "function") {
            this.paramsGenerator_ = h13;
        }
        this.__icon = new SynchedPropertyObjectOneWayPU(e13.icon, this, "icon");
        this.iconSymbolOptions = null;
        this.__primaryTitle = new SynchedPropertyObjectOneWayPU(e13.primaryTitle, this, "primaryTitle");
        this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, "primaryTitleModifier");
        this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(e13.secondaryTitle, this, "secondaryTitle");
        this.__secondaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, "secondaryTitleModifier");
        this.__subHeaderModifier = new ObservedPropertyObjectPU(new SubHeaderModifier(), this, "subHeaderModifier");
        this.select = null;
        this.__operationType = new SynchedPropertySimpleOneWayPU(e13.operationType, this, "operationType");
        this.operationItem = null;
        this.operationSymbolOptions = null;
        this.callbackId = undefined;
        this.__fontSize = new ObservedPropertySimplePU(1, this, "fontSize");
        this.__ageing = new ObservedPropertySimplePU(true, this, "ageing");
        this.__textArrowBgColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "textArrowBgColor");
        this.__buttonBgColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "buttonBgColor");
        this.__textArrowStyleWidth = new ObservedPropertySimplePU(0, this, "textArrowStyleWidth");
        this.__textArrowStyleHeight = new ObservedPropertySimplePU(0, this, "textArrowStyleHeight");
        this.__iconWidth = new ObservedPropertySimplePU(0, this, "iconWidth");
        this.__selectedIndex = new ObservedPropertyObjectPU(-1, this, "selectedIndex");
        this.__selectValue = new ObservedPropertyObjectPU('', this, "selectValue");
        this.__flexAlign = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, "flexAlign");
        this.titleBuilder = undefined;
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(e13.contentMargin, this, "contentMargin");
        this.__contentPadding = new SynchedPropertyObjectOneWayPU(e13.contentPadding, this, "contentPadding");
        this.__subHeaderMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.vp(0),
            end: LengthMetrics.vp(0)
        }, this, "subHeaderMargin");
        this.__subHeaderTheme = new ObservedPropertyObjectPU(new SubHeaderTheme(), this, "subHeaderTheme");
        this.addProvidedVar("subHeaderTheme", this.__subHeaderTheme, false);
        this.setInitiallyProvidedValue(e13);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(c13) {
        if (c13.icon === undefined) {
            this.__icon.set(null);
        }
        if (c13.iconSymbolOptions !== undefined) {
            this.iconSymbolOptions = c13.iconSymbolOptions;
        }
        if (c13.primaryTitle === undefined) {
            this.__primaryTitle.set(null);
        }
        if (c13.primaryTitleModifier !== undefined) {
            this.primaryTitleModifier = c13.primaryTitleModifier;
        }
        if (c13.secondaryTitle === undefined) {
            this.__secondaryTitle.set(null);
        }
        if (c13.secondaryTitleModifier !== undefined) {
            this.secondaryTitleModifier = c13.secondaryTitleModifier;
        }
        if (c13.subHeaderModifier !== undefined) {
            this.subHeaderModifier = c13.subHeaderModifier;
        }
        if (c13.select !== undefined) {
            this.select = c13.select;
        }
        if (c13.operationType === undefined) {
            this.__operationType.set(OperationType.BUTTON);
        }
        if (c13.operationItem !== undefined) {
            this.operationItem = c13.operationItem;
        }
        if (c13.operationSymbolOptions !== undefined) {
            this.operationSymbolOptions = c13.operationSymbolOptions;
        }
        if (c13.callbackId !== undefined) {
            this.callbackId = c13.callbackId;
        }
        if (c13.fontSize !== undefined) {
            this.fontSize = c13.fontSize;
        }
        if (c13.ageing !== undefined) {
            this.ageing = c13.ageing;
        }
        if (c13.textArrowBgColor !== undefined) {
            this.textArrowBgColor = c13.textArrowBgColor;
        }
        if (c13.buttonBgColor !== undefined) {
            this.buttonBgColor = c13.buttonBgColor;
        }
        if (c13.textArrowStyleWidth !== undefined) {
            this.textArrowStyleWidth = c13.textArrowStyleWidth;
        }
        if (c13.textArrowStyleHeight !== undefined) {
            this.textArrowStyleHeight = c13.textArrowStyleHeight;
        }
        if (c13.iconWidth !== undefined) {
            this.iconWidth = c13.iconWidth;
        }
        if (c13.selectedIndex !== undefined) {
            this.selectedIndex = c13.selectedIndex;
        }
        if (c13.selectValue !== undefined) {
            this.selectValue = c13.selectValue;
        }
        if (c13.flexAlign !== undefined) {
            this.flexAlign = c13.flexAlign;
        }
        if (c13.titleBuilder !== undefined) {
            this.titleBuilder = c13.titleBuilder;
        }
        if (c13.subHeaderMargin !== undefined) {
            this.subHeaderMargin = c13.subHeaderMargin;
        }
        if (c13.subHeaderTheme !== undefined) {
            this.subHeaderTheme = c13.subHeaderTheme;
        }
    }
    updateStateVars(b13) {
        this.__icon.reset(b13.icon);
        this.__primaryTitle.reset(b13.primaryTitle);
        this.__secondaryTitle.reset(b13.secondaryTitle);
        this.__operationType.reset(b13.operationType);
        this.__contentMargin.reset(b13.contentMargin);
        this.__contentPadding.reset(b13.contentPadding);
    }
    purgeVariableDependenciesOnElmtId(a13) {
        this.__icon.purgeDependencyOnElmtId(a13);
        this.__primaryTitle.purgeDependencyOnElmtId(a13);
        this.__primaryTitleModifier.purgeDependencyOnElmtId(a13);
        this.__secondaryTitle.purgeDependencyOnElmtId(a13);
        this.__secondaryTitleModifier.purgeDependencyOnElmtId(a13);
        this.__subHeaderModifier.purgeDependencyOnElmtId(a13);
        this.__operationType.purgeDependencyOnElmtId(a13);
        this.__fontSize.purgeDependencyOnElmtId(a13);
        this.__ageing.purgeDependencyOnElmtId(a13);
        this.__textArrowBgColor.purgeDependencyOnElmtId(a13);
        this.__buttonBgColor.purgeDependencyOnElmtId(a13);
        this.__textArrowFocus.purgeDependencyOnElmtId(a13);
        this.__buttonFocus.purgeDependencyOnElmtId(a13);
        this.__textArrowStyleWidth.purgeDependencyOnElmtId(a13);
        this.__textArrowStyleHeight.purgeDependencyOnElmtId(a13);
        this.__buttonStyleWidth.purgeDependencyOnElmtId(a13);
        this.__buttonStyleHeight.purgeDependencyOnElmtId(a13);
        this.__iconWidth.purgeDependencyOnElmtId(a13);
        this.__selectedIndex.purgeDependencyOnElmtId(a13);
        this.__selectValue.purgeDependencyOnElmtId(a13);
        this.__flexAlign.purgeDependencyOnElmtId(a13);
        this.__contentMargin.purgeDependencyOnElmtId(a13);
        this.__contentPadding.purgeDependencyOnElmtId(a13);
        this.__subHeaderMargin.purgeDependencyOnElmtId(a13);
        this.__subHeaderTheme.purgeDependencyOnElmtId(a13);
    }
    aboutToBeDeleted() {
        this.__icon.aboutToBeDeleted();
        this.__primaryTitle.aboutToBeDeleted();
        this.__primaryTitleModifier.aboutToBeDeleted();
        this.__secondaryTitle.aboutToBeDeleted();
        this.__secondaryTitleModifier.aboutToBeDeleted();
        this.__subHeaderModifier.aboutToBeDeleted();
        this.__operationType.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__ageing.aboutToBeDeleted();
        this.__textArrowBgColor.aboutToBeDeleted();
        this.__buttonBgColor.aboutToBeDeleted();
        this.__textArrowFocus.aboutToBeDeleted();
        this.__buttonFocus.aboutToBeDeleted();
        this.__textArrowStyleWidth.aboutToBeDeleted();
        this.__textArrowStyleHeight.aboutToBeDeleted();
        this.__buttonStyleWidth.aboutToBeDeleted();
        this.__buttonStyleHeight.aboutToBeDeleted();
        this.__iconWidth.aboutToBeDeleted();
        this.__selectedIndex.aboutToBeDeleted();
        this.__selectValue.aboutToBeDeleted();
        this.__flexAlign.aboutToBeDeleted();
        this.__contentMargin.aboutToBeDeleted();
        this.__contentPadding.aboutToBeDeleted();
        this.__subHeaderMargin.aboutToBeDeleted();
        this.__subHeaderTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(z12) {
        this.__icon.set(z12);
    }
    get primaryTitle() {
        return this.__primaryTitle.get();
    }
    set primaryTitle(y12) {
        this.__primaryTitle.set(y12);
    }
    get primaryTitleModifier() {
        return this.__primaryTitleModifier.get();
    }
    set primaryTitleModifier(x12) {
        this.__primaryTitleModifier.set(x12);
    }
    get secondaryTitle() {
        return this.__secondaryTitle.get();
    }
    set secondaryTitle(w12) {
        this.__secondaryTitle.set(w12);
    }
    get secondaryTitleModifier() {
        return this.__secondaryTitleModifier.get();
    }
    set secondaryTitleModifier(v12) {
        this.__secondaryTitleModifier.set(v12);
    }
    get subHeaderModifier() {
        return this.__subHeaderModifier.get();
    }
    set subHeaderModifier(u12) {
        this.__subHeaderModifier.set(u12);
    }
    get operationType() {
        return this.__operationType.get();
    }
    set operationType(t12) {
        this.__operationType.set(t12);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(s12) {
        this.__fontSize.set(s12);
    }
    get ageing() {
        return this.__ageing.get();
    }
    set ageing(r12) {
        this.__ageing.set(r12);
    }
    get textArrowBgColor() {
        return this.__textArrowBgColor.get();
    }
    set textArrowBgColor(q12) {
        this.__textArrowBgColor.set(q12);
    }
    get buttonBgColor() {
        return this.__buttonBgColor.get();
    }
    set buttonBgColor(p12) {
        this.__buttonBgColor.set(p12);
    }
    get textArrowStyleWidth() {
        return this.__textArrowStyleWidth.get();
    }
    set textArrowStyleWidth(m12) {
        this.__textArrowStyleWidth.set(m12);
    }
    get textArrowStyleHeight() {
        return this.__textArrowStyleHeight.get();
    }
    set textArrowStyleHeight(l12) {
        this.__textArrowStyleHeight.set(l12);
    }
    get iconWidth() {
        return this.__iconWidth.get();
    }
    set iconWidth(i12) {
        this.__iconWidth.set(i12);
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(h12) {
        this.__selectedIndex.set(h12);
    }
    get selectValue() {
        return this.__selectValue.get();
    }
    set selectValue(g12) {
        this.__selectValue.set(g12);
    }
    get flexAlign() {
        return this.__flexAlign.get();
    }
    set flexAlign(f12) {
        this.__flexAlign.set(f12);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(e12) {
        this.__contentMargin.set(e12);
    }
    get contentPadding() {
        return this.__contentPadding.get();
    }
    set contentPadding(d12) {
        this.__contentPadding.set(d12);
    }
    get subHeaderMargin() {
        return this.__subHeaderMargin.get();
    }
    set subHeaderMargin(c12) {
        this.__subHeaderMargin.set(c12);
    }
    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }
    set subHeaderTheme(b12) {
        this.__subHeaderTheme.set(b12);
    }
    onWillApplyTheme(a12) {
        this.subHeaderTheme.fontPrimaryColor = a12.colors.fontPrimary;
        this.subHeaderTheme.fontSecondaryColor = a12.colors.fontSecondary;
        this.subHeaderTheme.fontButtonColor = a12.colors.fontEmphasize;
        this.subHeaderTheme.iconArrowColor = a12.colors.iconTertiary;
        this.subHeaderTheme.textArrowHoverBgColor = a12.colors.interactiveHover;
        this.subHeaderTheme.borderFocusColor = a12.colors.interactiveFocus;
        this.subHeaderTheme.leftIconColor = a12.colors.iconSecondary;
        this.subHeaderTheme.rightIconColor = a12.colors.iconPrimary;
    }
    async aboutToAppear() {
        if (this.select) {
            this.selectedIndex = this.select.selected;
            this.selectValue = this.select.value;
        }
    }
    initialRender() {
        this.observeComponentCreation2((e11, f11) => {
            If.create();
            if (this.ageing && ((this.operationType === OperationType.TEXT_ARROW) ||
                this.operationType === OperationType.BUTTON) && this.operationItem
                && (this.operationItem?.length > 0) && this.operationItem[0].value !== '') {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y11, z11) => {
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.margin(this.contentMargin ?? this.subHeaderMargin);
                        Column.padding(this.getAreaPadding());
                    }, Column);
                    this.observeComponentCreation2((w11, x11) => {
                        Row.create();
                        Row.margin({
                            top: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Row.width('100%');
                    }, Row);
                    this.leftArea.bind(this)(this);
                    Row.pop();
                    this.observeComponentCreation2((u11, v11) => {
                        Row.create();
                        Row.margin({
                            bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Row.justifyContent(FlexAlign.Start);
                        Row.width('100%');
                    }, Row);
                    this.rightArea.bind(this)(this);
                    Row.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((o11, p11) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.contentMargin ?? this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((m11, n11) => {
                        Row.create();
                        Row.width('100%');
                        Row.flexShrink(1);
                    }, Row);
                    this.leftArea.bind(this)(this);
                    Row.pop();
                    this.observeComponentCreation2((k11, l11) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.End);
                        Row.constraintSize({ maxWidth: this.getMaxWidth() });
                        Row.flexShrink(0);
                    }, Row);
                    this.rightArea.bind(this)(this);
                    Row.pop();
                    Flex.pop();
                });
            }
        }, If);
        If.pop();
    }
    onMeasureSize(v10, w10, x10) {
        let y10 = { width: v10.width, height: v10.height };
        let z10 = this.getUIContext().getHostContext();
        this.fontSize = z10.config?.fontSizeScale ?? 1;
        this.ageing = this.fontSize >= MIN_FONT_SIZE ? true : false;
        this.subHeaderModifier.isAgeing = this.ageing;
        w10.forEach((b11) => {
            if (!this.contentMargin) {
                let c11 = Number(x10.maxWidth);
                if (c11 < Util.BREAKPOINT_S) {
                    this.subHeaderMargin = {
                        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                    };
                }
                else if (c11 < Util.BREAKPOINT_M) {
                    this.subHeaderMargin = {
                        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                    };
                }
                else {
                    this.subHeaderMargin = {
                        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level16'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level16'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                    };
                }
            }
            x10.minHeight = Math.min(Number(this.getMinHeight()), Number(x10.maxHeight));
            y10.height = b11.measure(x10).height;
            y10.width = Number(x10.maxWidth);
        });
        return y10;
    }
    onPlaceChildren(q10, r10, s10) {
        r10.forEach((u10) => {
            u10.layout({ x: 0, y: 0 });
        });
    }
    getMaxWidth() {
        if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
            return '100%';
        }
        else {
            return MAX_RIGHT_WIDTH;
        }
    }
    getMinHeight() {
        if (this.secondaryTitle && this.icon) {
            return SINGLE_LINE_HEIGHT;
        }
        else if (this.secondaryTitle && this.primaryTitle) {
            return DOUBLE_LINE_HEIGHT;
        }
        return SINGLE_LINE_HEIGHT;
    }
    getTextArrowPaddingLeft() {
        if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
            return LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }
        return LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    }
    getTextArrowMarginRight() {
        if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
            return LengthMetrics.vp(PADDING_LEVEL_2 + ARROW_ICON_WIDTH);
        }
        return LengthMetrics.vp(ARROW_ICON_WIDTH);
    }
    getAreaPadding() {
        if (this.contentPadding) {
            return this.contentPadding;
        }
        let p10 = {};
        if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
            (!this.primaryTitle && this.secondaryTitle))) {
            p10 = {
                start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            };
        }
        return p10;
    }
    leftArea(e10 = null) {
        this.observeComponentCreation2((g10, h10) => {
            If.create();
            if (this.titleBuilder) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.titleBuilder.bind(this)(e10 ? e10 : this);
                });
            }
            else if (this.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy("IconSecondaryTitleStyle", { content: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"]), iconOptions: () => ({
                            icon: this.icon,
                            symbolicIconOption: this.iconSymbolOptions,
                        }) }), e10 ? e10 : this);
                });
            }
            else if (this.secondaryTitle && this.primaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy("SubTitleStyle", { content: () => (this["__primaryTitle"] ? this["__primaryTitle"] : this["primaryTitle"]), subContent: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"]) }), e10 ? e10 : this);
                });
            }
            else if (this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy("SecondTitleStyle", { content: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"]) }), e10 ? e10 : this);
                });
            }
            else if (this.select) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.SelectStyle.bind(this)(this.select, e10 ? e10 : this);
                });
            }
            else if (this.primaryTitle) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy("PrimaryTitleStyle", { content: () => (this["__primaryTitle"] ? this["__primaryTitle"] : this["primaryTitle"]) }), e10 ? e10 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.dummyFunction.bind(this)(e10 ? e10 : this);
                });
            }
        }, If);
        If.pop();
    }
    rightArea(j9 = null) {
        this.observeComponentCreation2((a10, b10) => {
            If.create();
            if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)(this.operationItem[0], j9 ? j9 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((w9, x9) => {
            If.create();
            if (this.operationType === OperationType.TEXT_ARROW && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextArrowStyle.bind(this)(this.operationItem[0], j9 ? j9 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((s9, t9) => {
            If.create();
            if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconGroupStyle.bind(this)(this.operationItem, j9 ? j9 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((o9, p9) => {
            If.create();
            if (this.operationType === OperationType.LOADING) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.LoadingProcessStyle.bind(this)(j9 ? j9 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    IconSecondaryTitleStyle(p8, q8 = null) {
        this.observeComponentCreation2((g9, h9) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                top: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                bottom: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
            Flex.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Flex);
        this.observeComponentCreation2((w8, x8) => {
            If.create();
            if (Util.isSymbolResource(p8.iconOptions?.icon)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e9, f9) => {
                        SymbolGlyph.create(p8.iconOptions?.icon);
                        SymbolGlyph.fontSize(p8.iconOptions?.symbolicIconOption?.fontSize ?
                            Util.symbolFontSize(p8.iconOptions?.symbolicIconOption?.fontSize) : LEFT_ICON_SIZE);
                        SymbolGlyph.fontColor(p8.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.leftIconColor]);
                        SymbolGlyph.fontWeight(p8.iconOptions?.symbolicIconOption?.fontWeight);
                        SymbolGlyph.renderingStrategy(p8.iconOptions?.symbolicIconOption?.renderingStrategy);
                        SymbolGlyph.effectStrategy(p8.iconOptions?.symbolicIconOption?.effectStrategy);
                        SymbolGlyph.margin({ end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) });
                        SymbolGlyph.flexShrink(0);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((a9, b9) => {
                        Image.create(p8.iconOptions?.icon);
                        Image.fillColor(this.subHeaderTheme.leftIconColor);
                        Image.width(LEFT_ICON_SIZE);
                        Image.height(LEFT_ICON_SIZE);
                        Image.margin({ end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) });
                        Image.draggable(false);
                        Image.flexShrink(0);
                    }, Image);
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((u8, v8) => {
            Text.create(p8.content);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
            Text.flexShrink(1);
        }, Text);
        Text.pop();
        Flex.pop();
    }
    SubTitleStyle(d8, e8 = null) {
        this.observeComponentCreation2((m8, n8) => {
            Column.create();
            Column.padding({
                end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                top: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                bottom: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
            Column.alignItems(HorizontalAlign.Start);
            Column.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Column);
        this.observeComponentCreation2((k8, l8) => {
            Text.create(d8.content);
            __Text__primaryTitleStyles({
                fontWeight: FontWeight.Bold,
                maxLines: SINGLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
            Text.width('100%');
        }, Text);
        Text.pop();
        this.observeComponentCreation2((i8, j8) => {
            Text.create(d8.subContent);
            __Text__secondaryTitleStyles({
                maxLines: SINGLE_LINE_NUM,
                fontWeight: FontWeight.Regular,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.width('100%');
            Text.margin({
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
        }, Text);
        Text.pop();
        Column.pop();
    }
    SecondTitleStyle(u7, v7 = null) {
        this.observeComponentCreation2((b8, c8) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                top: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                bottom: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
        }, Column);
        this.observeComponentCreation2((y7, z7) => {
            Text.create(u7.content);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.width('100%');
            Text.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
        }, Text);
        Text.pop();
        Column.pop();
    }
    SelectStyle(i7, j7 = null) {
        this.observeComponentCreation2((r7, s7) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Column);
        this.observeComponentCreation2((m7, n7) => {
            Select.create(i7.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
            Select.value(ObservedObject.GetRawObject(this.selectValue));
            Select.onSelect((p7, q7) => {
                this.selectedIndex = p7;
                if (q7) {
                    this.selectValue = q7;
                }
                if (i7.onSelect) {
                    i7.onSelect(p7, q7);
                }
            });
            Select.font({
                size: { "id": -1, "type": 10002, params: ['sys.float.Body_L'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
        Column.pop();
    }
    PrimaryTitleStyle(z6, a7 = null) {
        this.observeComponentCreation2((g7, h7) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                top: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                bottom: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
        }, Column);
        this.observeComponentCreation2((d7, e7) => {
            Text.create(z6.content);
            __Text__primaryTitleStyles({
                fontWeight: FontWeight.Bold,
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.width('100%');
            Text.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
        }, Text);
        Text.pop();
        Column.pop();
    }
    ButtonStyle(l5, m5 = null) {
        this.observeComponentCreation((i6, j6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i6);
            Row.create();
            Row.margin({
                start: LengthMetrics.resource(this.ageing ? { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
            Row.justifyContent(FlexAlign.End);
            if (!j6) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((g6, h6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(g6);
            Stack.create();
            Stack.focusable(true);
            if (!h6) {
                Stack.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((q5, r5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q5);
            If.create();
            if (l5) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((y5, z5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(y5);
                        Row.create();
                        Row.padding({
                            start: LengthMetrics.resource(this.ageing ? { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                            end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                            top: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                            bottom: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                        });
                        Row.margin({
                            start: (this.ageing && this.icon) ? LengthMetrics.vp((this.iconSymbolOptions?.fontSize ?
                            Util.numberToSize(this.iconSymbolOptions?.fontSize) : LEFT_ICON_SIZE_NUMBER) +
                                LEFT_TEXT_NUMBER) : LengthMetrics.vp(0),
                            bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Row.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
                        Row.focusable(true);
                        Row.constraintSize({ minHeight: BUTTON_HEIGHT });
                        Row.justifyContent(FlexAlign.End);
                        Row.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("focused");
                        Row.border({
                            radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            width: { "id": -1, "type": 10002, params: ['sys.float.outline_extra_larger'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            color: this.subHeaderTheme.borderFocusColor,
                        });
                        ViewStackProcessor.visualState("pressed");
                        Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("disabled");
                        Row.opacity({ "id": -1, "type": 10002, params: ['sys.float.interactive_disable'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("normal");
                        Row.border({
                            radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            width: { "id": -1, "type": 10002, params: ['sys.float.border_none'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            color: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        ViewStackProcessor.visualState();
                        Row.onHover((f6) => {
                            if (f6) {
                                this.buttonBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                            }
                            else {
                                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Row.onTouch((e6) => {
                            if (e6.type === TouchType.Down) {
                                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            if (e6.type === TouchType.Up) {
                                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Row.onClick((d6) => {
                            if (l5.action) {
                                l5.action();
                            }
                        });
                        if (!z5) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((w5, x5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(w5);
                        Text.create(l5.value);
                        __Text__secondaryTitleStyles({
                            fontWeight: FontWeight.Medium,
                            maxLines: DOUBLE_LINE_NUM,
                            fontColor: this.subHeaderTheme.fontButtonColor,
                        });
                        Text.focusable(true);
                        if (!x5) {
                            Text.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Text.pop();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!r5) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Stack.pop();
        Row.pop();
    }
    TextArrowStyle(d4, e4 = null) {
        this.observeComponentCreation2((l5, m5) => {
            Row.create();
            Row.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.subHeaderModifier));
            Row.focusable(true);
            Row.justifyContent(this.ageing ? FlexAlign.SpaceBetween : FlexAlign.End);
            Row.margin({
                start: LengthMetrics.resource(this.ageing ? { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                bottom: LengthMetrics.resource(this.ageing ? { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
        }, Row);
        this.observeComponentCreation2((d5, e5) => {
            Stack.create();
            Stack.margin({
                start: (this.ageing && this.icon) ? LengthMetrics.vp((this.iconSymbolOptions?.fontSize ?
                    Util.numberToSize(this.iconSymbolOptions?.fontSize) : LEFT_ICON_SIZE_NUMBER) +
                    LEFT_TEXT_NUMBER) : LengthMetrics.vp(0),
            });
            Stack.onHover((k5) => {
                if (k5) {
                    this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                }
                else {
                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
            });
            Stack.onTouch((j5) => {
                if (j5.type === TouchType.Down) {
                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
                if (j5.type === TouchType.Up) {
                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
            });
            Stack.onClick((i5) => {
                if (d4.action) {
                    d4.action();
                }
            });
        }, Stack);
        this.observeComponentCreation2((w4, x4) => {
            Row.create();
            Row.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.subHeaderModifier));
            Row.alignItems(VerticalAlign.Center);
            Row.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Row.focusable(true);
            Row.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
            Row.constraintSize({ minHeight: BUTTON_ZONE_SIZE });
            Row.padding({
                start: this.getTextArrowPaddingLeft(),
                bottom: LengthMetrics.vp(0),
            });
            Row.onAreaChange((b5, c5) => {
                this.textArrowStyleWidth = Number(c5.width);
                this.textArrowStyleHeight = Number(c5.height);
            });
        }, Row);
        this.observeComponentCreation2((p4, q4) => {
            If.create();
            if (d4) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u4, v4) => {
                        Text.create(d4.value);
                        __Text__secondaryTitleStyles({
                            maxLines: DOUBLE_LINE_NUM,
                            fontWeight: FontWeight.Regular,
                            alignment: Alignment.End,
                            fontColor: this.subHeaderTheme.fontSecondaryColor,
                        });
                        Text.margin({
                            end: this.getTextArrowMarginRight(),
                        });
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
        Row.pop();
        this.observeComponentCreation2((n4, o4) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.height(this.textArrowStyleHeight);
            Row.width(this.textArrowStyleWidth);
            Row.hitTestBehavior(HitTestMode.None);
            Row.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: { "id": -1, "type": 10002, params: ['sys.float.outline_extra_larger'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: { "id": -1, "type": 10001, params: ['sys.color.interactive_focus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            ViewStackProcessor.visualState("focused");
            Row.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: { "id": -1, "type": 10002, params: ['sys.float.outline_extra_larger'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: this.subHeaderTheme.borderFocusColor,
            });
            ViewStackProcessor.visualState("pressed");
            Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            ViewStackProcessor.visualState("disabled");
            Row.opacity({ "id": -1, "type": 10002, params: ['sys.float.interactive_disable'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            ViewStackProcessor.visualState("normal");
            Row.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: { "id": -1, "type": 10002, params: ['sys.float.border_none'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            ViewStackProcessor.visualState();
        }, Row);
        this.observeComponentCreation2((l4, m4) => {
            Image.create({ "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_arrow_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.fillColor(this.subHeaderTheme.iconArrowColor);
            Image.width(ARROW_ICON_WIDTH);
            Image.height(ARROW_ICON_HEIGHT);
            Image.focusable(true);
            Image.draggable(false);
            Image.matchTextDirection(true);
        }, Image);
        Row.pop();
        Stack.pop();
        Row.pop();
    }
    IconGroupStyle(o2, p2 = null) {
        this.observeComponentCreation2((b4, c4) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
            Row.margin({
                start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
        }, Row);
        this.observeComponentCreation2((s2, t2) => {
            ForEach.create();
            const u2 = (w2, x2) => {
                const y2 = w2;
                this.observeComponentCreation2((a3, b3) => {
                    If.create();
                    if (Util.isResourceType(y2.value)) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((f3, g3) => {
                                If.create();
                                if (x2 === INDEX_ZERO) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        {
                                            this.observeComponentCreation2((v3, w3) => {
                                                if (w3) {
                                                    let x3 = new SingleIconStyle(typeof PUV2ViewBase !== "undefined" && p2 instanceof PUV2ViewBase ? p2 : this, {
                                                        item: {
                                                            iconOptions: {
                                                                icon: y2.value,
                                                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > x2 ?
                                                                    this.operationSymbolOptions[x2] : null,
                                                            },
                                                            action: y2.action,
                                                        }
                                                    }, undefined, v3, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 736, col: 13 });
                                                    ViewPU.create(x3);
                                                    let y3 = () => {
                                                        return {
                                                            item: {
                                                                iconOptions: {
                                                                    icon: y2.value,
                                                                    symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > x2 ?
                                                                        this.operationSymbolOptions[x2] : null,
                                                                },
                                                                action: y2.action,
                                                            }
                                                        };
                                                    };
                                                    x3.paramsGenerator_ = y3;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(v3, {});
                                                }
                                            }, { name: "SingleIconStyle" });
                                        }
                                    });
                                }
                                else if (x2 === INDEX_ONE || x2 === INDEX_TWO) {
                                    this.ifElseBranchUpdateFunction(1, () => {
                                        this.observeComponentCreation2((r3, s3) => {
                                            __Common__.create();
                                            __Common__.margin({
                                                start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((l3, m3) => {
                                                if (m3) {
                                                    let n3 = new SingleIconStyle(typeof PUV2ViewBase !== "undefined" && p2 instanceof PUV2ViewBase ? p2 : this, {
                                                        item: {
                                                            action: y2.action,
                                                            iconOptions: {
                                                                icon: y2.value,
                                                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > x2 ?
                                                                    this.operationSymbolOptions[x2] : null,
                                                            },
                                                        }
                                                    }, undefined, l3, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 747, col: 13 });
                                                    ViewPU.create(n3);
                                                    let o3 = () => {
                                                        return {
                                                            item: {
                                                                action: y2.action,
                                                                iconOptions: {
                                                                    icon: y2.value,
                                                                    symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > x2 ?
                                                                        this.operationSymbolOptions[x2] : null,
                                                                },
                                                            }
                                                        };
                                                    };
                                                    n3.paramsGenerator_ = o3;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(l3, {});
                                                }
                                            }, { name: "SingleIconStyle" });
                                        }
                                        __Common__.pop();
                                    });
                                }
                                else {
                                    this.ifElseBranchUpdateFunction(2, () => {
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
            };
            this.forEachUpdateFunction(s2, o2, u2, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    LoadingProcessStyle(h2 = null) {
        this.observeComponentCreation2((m2, n2) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.padding({
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Row.margin({
                start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
        }, Row);
        this.observeComponentCreation2((k2, l2) => {
            LoadingProgress.create();
            LoadingProgress.width(LOADING_SIZE);
            LoadingProgress.height(LOADING_SIZE);
            LoadingProgress.color({ "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, LoadingProgress);
        Row.pop();
    }
    dummyFunction(c2 = null) {
        this.observeComponentCreation2((e2, f2) => {
            Row.create();
            Row.onAppear(() => {
                this.changeFlexAlign(FlexAlign.End);
            });
        }, Row);
        Row.pop();
    }
    changeFlexAlign(b2) {
        if (this.flexAlign === b2) {
            return;
        }
        this.flexAlign = b2;
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class SingleIconStyle extends ViewPU {
    constructor(v1, w1, x1, y1 = -1, z1 = undefined, a2) {
        super(v1, x1, y1, a2);
        if (typeof z1 === "function") {
            this.paramsGenerator_ = z1;
        }
        this.__bgColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "bgColor");
        this.__isFocus = new ObservedPropertySimplePU(false, this, "isFocus");
        this.item = null;
        this.__subHeaderTheme = this.initializeConsume("subHeaderTheme", "subHeaderTheme");
        this.setInitiallyProvidedValue(w1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(u1) {
        if (u1.bgColor !== undefined) {
            this.bgColor = u1.bgColor;
        }
        if (u1.isFocus !== undefined) {
            this.isFocus = u1.isFocus;
        }
        if (u1.item !== undefined) {
            this.item = u1.item;
        }
    }
    updateStateVars(t1) {
    }
    purgeVariableDependenciesOnElmtId(s1) {
        this.__bgColor.purgeDependencyOnElmtId(s1);
        this.__isFocus.purgeDependencyOnElmtId(s1);
        this.__subHeaderTheme.purgeDependencyOnElmtId(s1);
    }
    aboutToBeDeleted() {
        this.__bgColor.aboutToBeDeleted();
        this.__isFocus.aboutToBeDeleted();
        this.__subHeaderTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get bgColor() {
        return this.__bgColor.get();
    }
    set bgColor(r1) {
        this.__bgColor.set(r1);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(q1) {
        this.__isFocus.set(q1);
    }
    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }
    set subHeaderTheme(p1) {
        this.__subHeaderTheme.set(p1);
    }
    initialRender() {
        this.observeComponentCreation2((c1, d1) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h1, i1) => {
                        Row.create();
                        Row.focusable(true);
                        Row.width(SINGLE_ICON_ZONE_SIZE);
                        Row.height(SINGLE_ICON_ZONE_SIZE);
                        Row.margin({
                            bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Row.justifyContent(FlexAlign.Center);
                        Row.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Row.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
                        ViewStackProcessor.visualState("normal");
                        Row.border({ width: 0 });
                        Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("focused");
                        Row.border({
                            radius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            width: BORDER_WIDTH,
                            color: this.subHeaderTheme.borderFocusColor,
                            style: BorderStyle.Solid,
                        });
                        ViewStackProcessor.visualState("pressed");
                        Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("disabled");
                        Row.opacity({ "id": -1, "type": 10002, params: ['sys.float.interactive_disable'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState();
                        Row.onTouch((o1) => {
                            if (o1.type === TouchType.Down) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            if (o1.type === TouchType.Up) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Row.onHover((n1) => {
                            if (n1) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            else {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Row.onClick((m1) => {
                            if (this.item?.action) {
                                this.item?.action();
                            }
                        });
                    }, Row);
                    this.IconZone.bind(this)(this);
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    IconZone(k = null) {
        this.observeComponentCreation2((m, n) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r, s) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((z, a1) => {
                                    SymbolGlyph.create(this.item.iconOptions?.icon);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.fontSize(this.item.iconOptions?.symbolicIconOption?.fontSize ?
                                        Util.symbolFontSize(this.item.iconOptions?.symbolicIconOption?.fontSize) : RIGHT_SINGLE_ICON_SIZE);
                                    SymbolGlyph.fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.rightIconColor]);
                                    SymbolGlyph.fontWeight(this.item.iconOptions?.symbolicIconOption?.fontWeight);
                                    SymbolGlyph.renderingStrategy(this.item.iconOptions?.symbolicIconOption?.renderingStrategy);
                                    SymbolGlyph.effectStrategy(this.item.iconOptions?.symbolicIconOption?.effectStrategy);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((v, w) => {
                                    Image.create(this.item?.iconOptions?.icon);
                                    Image.fillColor(this.subHeaderTheme.rightIconColor);
                                    Image.width(RIGHT_SINGLE_ICON_SIZE);
                                    Image.height(RIGHT_SINGLE_ICON_SIZE);
                                    Image.focusable(true);
                                    Image.draggable(false);
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
    rerender() {
        this.updateDirtyElements();
    }
}
class Util {
    static isSymbolResource(i) {
        if (!Util.isResourceType(i)) {
            return false;
        }
        let j = i;
        return j.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(h) {
        if (!h) {
            return false;
        }
        if (typeof h === 'string' || typeof h === 'undefined') {
            return false;
        }
        return true;
    }
    static getNumberByResource(d) {
        try {
            return resourceManager.getSystemResourceManager().getNumberByName(d);
        }
        catch (e) {
            let f = e.code;
            let g = e.message;
            hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${f}, message: ${g}`);
            return Util.DEFAULT_VALUE;
        }
    }
    static numberToSize(b) {
        if (typeof b === 'string') {
            const c = parseInt(b);
            return c;
        }
        else if (typeof b === 'number') {
            return b;
        }
        else {
            return resourceManager.getSystemResourceManager().getNumber(b);
        }
    }
    static symbolFontSize(a) {
        return Util.numberToSize(a) + 'vp';
    }
}
_a = Util;
Util.DEFAULT_VALUE = 0;
Util.DEFAULT_BREAKPOINT_S = 600;
Util.DEFAULT_BREAKPOINT_M = 840;
Util.CALCULATE_BREAKPOINT_S = _a.getNumberByResource('breakpoint_horizontal_s');
Util.CALCULATE_BREAKPOINT_M = _a.getNumberByResource('breakpoint_horizontal_m');
Util.BREAKPOINT_S = _a.CALCULATE_BREAKPOINT_S === _a.DEFAULT_VALUE ? _a.DEFAULT_BREAKPOINT_S : _a.CALCULATE_BREAKPOINT_S;
Util.BREAKPOINT_M = _a.CALCULATE_BREAKPOINT_M === _a.DEFAULT_VALUE ? _a.DEFAULT_BREAKPOINT_M : _a.CALCULATE_BREAKPOINT_M;

export default { OperationType, SubHeader };