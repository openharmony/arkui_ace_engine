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
const EnvironmentCallback = requireNapi('app.ability.EnvironmentCallback');
const window = requireNapi('window');

const INDEX_ZERO = 0;
const INDEX_ONE = 1;
const INDEX_TWO = 2;
const SINGLE_LINE_NUM = 1;
const DOUBLE_LINE_NUM = 2;
const SINGLE_LINE_HEIGHT = 56;
const DOUBLE_LINE_HEIGHT = 72;
const BORDER_WIDTH = 2;
const RESOURCE_TYPE_SYMBOL = 40000;
const LEFT_ICON_SIZE = 16;
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
(function (l13) {
    l13[l13["TEXT_ARROW"] = 0] = "TEXT_ARROW";
    l13[l13["BUTTON"] = 1] = "BUTTON";
    l13[l13["ICON_GROUP"] = 2] = "ICON_GROUP";
    l13[l13["LOADING"] = 3] = "LOADING";
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
function __Text__secondaryTitleStyles(k13) {
    Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Subtitle_S'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontColor(k13?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(k13?.fontWeight);
    Text.maxLines(k13?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(k13?.alignment);
}
function __Text__primaryTitleStyles(j13) {
    Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Subtitle_L'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontColor(j13?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(j13?.fontWeight);
    Text.maxLines(j13?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(j13?.alignment);
}
class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }
    applyNormalAttribute(i13) {
        if (this.isAgeing) {
            i13.width("100%");
        }
        else {
        }
    }
}
export class SubHeader extends ViewPU {
    constructor(c13, d13, e13, f13 = -1, g13 = undefined, h13) {
        super(c13, e13, f13, h13);
        if (typeof g13 === "function") {
            this.paramsGenerator_ = g13;
        }
        this.__icon = new SynchedPropertyObjectOneWayPU(d13.icon, this, "icon");
        this.iconSymbolOptions = null;
        this.__primaryTitle = new SynchedPropertyObjectOneWayPU(d13.primaryTitle, this, "primaryTitle");
        this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, "primaryTitleModifier");
        this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(d13.secondaryTitle, this, "secondaryTitle");
        this.__secondaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, "secondaryTitleModifier");
        this.__subHeaderModifier = new ObservedPropertyObjectPU(new SubHeaderModifier(), this, "subHeaderModifier");
        this.select = null;
        this.__operationType = new SynchedPropertySimpleOneWayPU(d13.operationType, this, "operationType");
        this.operationItem = null;
        this.operationSymbolOptions = null;
        this.callbackId = undefined;
        this.__fontSize = new ObservedPropertySimplePU(1, this, "fontSize");
        this.__ageing = new ObservedPropertySimplePU(true, this, "ageing");
        this.__textArrowBgColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "textArrowBgColor");
        this.__buttonBgColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "buttonBgColor");
        this.__textArrowFocus = new ObservedPropertySimplePU(false, this, "textArrowFocus");
        this.__buttonFocus = new ObservedPropertySimplePU(false, this, "buttonFocus");
        this.__textArrowStyleWidth = new ObservedPropertySimplePU(0, this, "textArrowStyleWidth");
        this.__textArrowStyleHeight = new ObservedPropertySimplePU(0, this, "textArrowStyleHeight");
        this.__buttonStyleWidth = new ObservedPropertySimplePU(0, this, "buttonStyleWidth");
        this.__buttonStyleHeight = new ObservedPropertySimplePU(0, this, "buttonStyleHeight");
        this.__iconWidth = new ObservedPropertySimplePU(0, this, "iconWidth");
        this.__selectedIndex = new ObservedPropertyObjectPU(-1, this, "selectedIndex");
        this.__selectValue = new ObservedPropertyObjectPU('', this, "selectValue");
        this.__flexAlign = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, "flexAlign");
        this.titleBuilder = undefined;
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(d13.contentMargin, this, "contentMargin");
        this.__contentPadding = new SynchedPropertyObjectOneWayPU(d13.contentPadding, this, "contentPadding");
        this.__subHeaderMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.vp(0),
            end: LengthMetrics.vp(0)
        }, this, "subHeaderMargin");
        this.__subHeaderTheme = new ObservedPropertyObjectPU(new SubHeaderTheme(), this, "subHeaderTheme");
        this.addProvidedVar("subHeaderTheme", this.__subHeaderTheme, false);
        this.setInitiallyProvidedValue(d13);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(b13) {
        if (b13.icon === undefined) {
            this.__icon.set(null);
        }
        if (b13.iconSymbolOptions !== undefined) {
            this.iconSymbolOptions = b13.iconSymbolOptions;
        }
        if (b13.primaryTitle === undefined) {
            this.__primaryTitle.set(null);
        }
        if (b13.primaryTitleModifier !== undefined) {
            this.primaryTitleModifier = b13.primaryTitleModifier;
        }
        if (b13.secondaryTitle === undefined) {
            this.__secondaryTitle.set(null);
        }
        if (b13.secondaryTitleModifier !== undefined) {
            this.secondaryTitleModifier = b13.secondaryTitleModifier;
        }
        if (b13.subHeaderModifier !== undefined) {
            this.subHeaderModifier = b13.subHeaderModifier;
        }
        if (b13.select !== undefined) {
            this.select = b13.select;
        }
        if (b13.operationType === undefined) {
            this.__operationType.set(OperationType.BUTTON);
        }
        if (b13.operationItem !== undefined) {
            this.operationItem = b13.operationItem;
        }
        if (b13.operationSymbolOptions !== undefined) {
            this.operationSymbolOptions = b13.operationSymbolOptions;
        }
        if (b13.callbackId !== undefined) {
            this.callbackId = b13.callbackId;
        }
        if (b13.fontSize !== undefined) {
            this.fontSize = b13.fontSize;
        }
        if (b13.ageing !== undefined) {
            this.ageing = b13.ageing;
        }
        if (b13.textArrowBgColor !== undefined) {
            this.textArrowBgColor = b13.textArrowBgColor;
        }
        if (b13.buttonBgColor !== undefined) {
            this.buttonBgColor = b13.buttonBgColor;
        }
        if (b13.textArrowFocus !== undefined) {
            this.textArrowFocus = b13.textArrowFocus;
        }
        if (b13.buttonFocus !== undefined) {
            this.buttonFocus = b13.buttonFocus;
        }
        if (b13.textArrowStyleWidth !== undefined) {
            this.textArrowStyleWidth = b13.textArrowStyleWidth;
        }
        if (b13.textArrowStyleHeight !== undefined) {
            this.textArrowStyleHeight = b13.textArrowStyleHeight;
        }
        if (b13.buttonStyleWidth !== undefined) {
            this.buttonStyleWidth = b13.buttonStyleWidth;
        }
        if (b13.buttonStyleHeight !== undefined) {
            this.buttonStyleHeight = b13.buttonStyleHeight;
        }
        if (b13.iconWidth !== undefined) {
            this.iconWidth = b13.iconWidth;
        }
        if (b13.selectedIndex !== undefined) {
            this.selectedIndex = b13.selectedIndex;
        }
        if (b13.selectValue !== undefined) {
            this.selectValue = b13.selectValue;
        }
        if (b13.flexAlign !== undefined) {
            this.flexAlign = b13.flexAlign;
        }
        if (b13.titleBuilder !== undefined) {
            this.titleBuilder = b13.titleBuilder;
        }
        if (b13.subHeaderMargin !== undefined) {
            this.subHeaderMargin = b13.subHeaderMargin;
        }
        if (b13.subHeaderTheme !== undefined) {
            this.subHeaderTheme = b13.subHeaderTheme;
        }
    }
    updateStateVars(a13) {
        this.__icon.reset(a13.icon);
        this.__primaryTitle.reset(a13.primaryTitle);
        this.__secondaryTitle.reset(a13.secondaryTitle);
        this.__operationType.reset(a13.operationType);
        this.__contentMargin.reset(a13.contentMargin);
        this.__contentPadding.reset(a13.contentPadding);
    }
    purgeVariableDependenciesOnElmtId(z12) {
        this.__icon.purgeDependencyOnElmtId(z12);
        this.__primaryTitle.purgeDependencyOnElmtId(z12);
        this.__primaryTitleModifier.purgeDependencyOnElmtId(z12);
        this.__secondaryTitle.purgeDependencyOnElmtId(z12);
        this.__secondaryTitleModifier.purgeDependencyOnElmtId(z12);
        this.__subHeaderModifier.purgeDependencyOnElmtId(z12);
        this.__operationType.purgeDependencyOnElmtId(z12);
        this.__fontSize.purgeDependencyOnElmtId(z12);
        this.__ageing.purgeDependencyOnElmtId(z12);
        this.__textArrowBgColor.purgeDependencyOnElmtId(z12);
        this.__buttonBgColor.purgeDependencyOnElmtId(z12);
        this.__textArrowFocus.purgeDependencyOnElmtId(z12);
        this.__buttonFocus.purgeDependencyOnElmtId(z12);
        this.__textArrowStyleWidth.purgeDependencyOnElmtId(z12);
        this.__textArrowStyleHeight.purgeDependencyOnElmtId(z12);
        this.__buttonStyleWidth.purgeDependencyOnElmtId(z12);
        this.__buttonStyleHeight.purgeDependencyOnElmtId(z12);
        this.__iconWidth.purgeDependencyOnElmtId(z12);
        this.__selectedIndex.purgeDependencyOnElmtId(z12);
        this.__selectValue.purgeDependencyOnElmtId(z12);
        this.__flexAlign.purgeDependencyOnElmtId(z12);
        this.__contentMargin.purgeDependencyOnElmtId(z12);
        this.__contentPadding.purgeDependencyOnElmtId(z12);
        this.__subHeaderMargin.purgeDependencyOnElmtId(z12);
        this.__subHeaderTheme.purgeDependencyOnElmtId(z12);
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
    set icon(y12) {
        this.__icon.set(y12);
    }
    get primaryTitle() {
        return this.__primaryTitle.get();
    }
    set primaryTitle(x12) {
        this.__primaryTitle.set(x12);
    }
    get primaryTitleModifier() {
        return this.__primaryTitleModifier.get();
    }
    set primaryTitleModifier(w12) {
        this.__primaryTitleModifier.set(w12);
    }
    get secondaryTitle() {
        return this.__secondaryTitle.get();
    }
    set secondaryTitle(v12) {
        this.__secondaryTitle.set(v12);
    }
    get secondaryTitleModifier() {
        return this.__secondaryTitleModifier.get();
    }
    set secondaryTitleModifier(u12) {
        this.__secondaryTitleModifier.set(u12);
    }
    get subHeaderModifier() {
        return this.__subHeaderModifier.get();
    }
    set subHeaderModifier(t12) {
        this.__subHeaderModifier.set(t12);
    }
    get operationType() {
        return this.__operationType.get();
    }
    set operationType(s12) {
        this.__operationType.set(s12);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(r12) {
        this.__fontSize.set(r12);
    }
    get ageing() {
        return this.__ageing.get();
    }
    set ageing(q12) {
        this.__ageing.set(q12);
    }
    get textArrowBgColor() {
        return this.__textArrowBgColor.get();
    }
    set textArrowBgColor(p12) {
        this.__textArrowBgColor.set(p12);
    }
    get buttonBgColor() {
        return this.__buttonBgColor.get();
    }
    set buttonBgColor(o12) {
        this.__buttonBgColor.set(o12);
    }
    get textArrowFocus() {
        return this.__textArrowFocus.get();
    }
    set textArrowFocus(n12) {
        this.__textArrowFocus.set(n12);
    }
    get buttonFocus() {
        return this.__buttonFocus.get();
    }
    set buttonFocus(m12) {
        this.__buttonFocus.set(m12);
    }
    get textArrowStyleWidth() {
        return this.__textArrowStyleWidth.get();
    }
    set textArrowStyleWidth(l12) {
        this.__textArrowStyleWidth.set(l12);
    }
    get textArrowStyleHeight() {
        return this.__textArrowStyleHeight.get();
    }
    set textArrowStyleHeight(k12) {
        this.__textArrowStyleHeight.set(k12);
    }
    get buttonStyleWidth() {
        return this.__buttonStyleWidth.get();
    }
    set buttonStyleWidth(j12) {
        this.__buttonStyleWidth.set(j12);
    }
    get buttonStyleHeight() {
        return this.__buttonStyleHeight.get();
    }
    set buttonStyleHeight(i12) {
        this.__buttonStyleHeight.set(i12);
    }
    get iconWidth() {
        return this.__iconWidth.get();
    }
    set iconWidth(h12) {
        this.__iconWidth.set(h12);
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(g12) {
        this.__selectedIndex.set(g12);
    }
    get selectValue() {
        return this.__selectValue.get();
    }
    set selectValue(f12) {
        this.__selectValue.set(f12);
    }
    get flexAlign() {
        return this.__flexAlign.get();
    }
    set flexAlign(e12) {
        this.__flexAlign.set(e12);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(d12) {
        this.__contentMargin.set(d12);
    }
    get contentPadding() {
        return this.__contentPadding.get();
    }
    set contentPadding(c12) {
        this.__contentPadding.set(c12);
    }
    get subHeaderMargin() {
        return this.__subHeaderMargin.get();
    }
    set subHeaderMargin(b12) {
        this.__subHeaderMargin.set(b12);
    }
    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }
    set subHeaderTheme(a12) {
        this.__subHeaderTheme.set(a12);
    }
    onWillApplyTheme(z11) {
        this.subHeaderTheme.fontPrimaryColor = z11.colors.fontPrimary;
        this.subHeaderTheme.fontSecondaryColor = z11.colors.fontSecondary;
        this.subHeaderTheme.fontButtonColor = z11.colors.fontEmphasize;
        this.subHeaderTheme.iconArrowColor = z11.colors.iconTertiary;
        this.subHeaderTheme.textArrowHoverBgColor = z11.colors.interactiveHover;
        this.subHeaderTheme.borderFocusColor = z11.colors.interactiveFocus;
        this.subHeaderTheme.leftIconColor = z11.colors.iconSecondary;
        this.subHeaderTheme.rightIconColor = z11.colors.iconPrimary;
    }
    async aboutToAppear() {
        if (this.select) {
            this.selectedIndex = this.select.selected;
            this.selectValue = this.select.value;
        }
    }
    initialRender() {
        this.observeComponentCreation2((d11, e11) => {
            If.create();
            if (this.ageing && (this.operationType === OperationType.TEXT_ARROW ||
                this.operationType === OperationType.BUTTON)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x11, y11) => {
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.margin(this.contentMargin ?? this.subHeaderMargin);
                        Column.padding(this.getAreaPadding());
                    }, Column);
                    this.observeComponentCreation2((v11, w11) => {
                        Row.create();
                        Row.width('100%');
                    }, Row);
                    this.leftArea.bind(this)(this);
                    Row.pop();
                    this.observeComponentCreation2((t11, u11) => {
                        Row.create();
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
                    this.observeComponentCreation2((n11, o11) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.contentMargin ?? this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((l11, m11) => {
                        Row.create();
                        Row.width('100%');
                        Row.flexShrink(1);
                    }, Row);
                    this.leftArea.bind(this)(this);
                    Row.pop();
                    this.observeComponentCreation2((j11, k11) => {
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
    onMeasureSize(u10, v10, w10) {
        let x10 = { width: u10.width, height: u10.height };
        let y10 = this.getUIContext().getHostContext();
        this.fontSize = y10.config?.fontSizeScale ?? 1;
        this.ageing = this.fontSize >= MIN_FONT_SIZE ? true : false;
        v10.forEach((a11) => {
            if (!this.contentMargin) {
                let b11 = Number(w10.maxWidth);
                if (b11 < Util.BREAKPOINT_S) {
                    this.subHeaderMargin = {
                        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                    };
                }
                else if (b11 < Util.BREAKPOINT_M) {
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
            w10.minHeight = Math.min(Number(this.getMinHeight()), Number(w10.maxHeight));
            x10.height = a11.measure(w10).height;
            x10.width = Number(w10.maxWidth);
        });
        return x10;
    }
    onPlaceChildren(p10, q10, r10) {
        q10.forEach((t10) => {
            t10.layout({ x: 0, y: 0 });
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
        let o10 = {};
        if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
            (!this.primaryTitle && this.secondaryTitle))) {
            o10 = {
                start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            };
        }
        return o10;
    }
    leftArea(d10 = null) {
        this.observeComponentCreation2((f10, g10) => {
            If.create();
            if (this.titleBuilder) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.titleBuilder.bind(this)(d10 ? d10 : this);
                });
            }
            else if (this.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy("IconSecondaryTitleStyle", { content: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"]), iconOptions: () => ({
                            icon: this.icon,
                            symbolicIconOption: this.iconSymbolOptions,
                        }) }), d10 ? d10 : this);
                });
            }
            else if (this.secondaryTitle && this.primaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy("SubTitleStyle", { content: () => (this["__primaryTitle"] ? this["__primaryTitle"] : this["primaryTitle"]), subContent: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"]) }), d10 ? d10 : this);
                });
            }
            else if (this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy("SecondTitleStyle", { content: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"]) }), d10 ? d10 : this);
                });
            }
            else if (this.select) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.SelectStyle.bind(this)(this.select, d10 ? d10 : this);
                });
            }
            else if (this.primaryTitle) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy("PrimaryTitleStyle", { content: () => (this["__primaryTitle"] ? this["__primaryTitle"] : this["primaryTitle"]) }), d10 ? d10 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.dummyFunction.bind(this)(d10 ? d10 : this);
                });
            }
        }, If);
        If.pop();
    }
    rightArea(i9 = null) {
        this.observeComponentCreation2((z9, a10) => {
            If.create();
            if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)(this.operationItem[0], i9 ? i9 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((v9, w9) => {
            If.create();
            if (this.operationType === OperationType.TEXT_ARROW && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextArrowStyle.bind(this)(this.operationItem[0], i9 ? i9 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((r9, s9) => {
            If.create();
            if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconGroupStyle.bind(this)(this.operationItem, i9 ? i9 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((n9, o9) => {
            If.create();
            if (this.operationType === OperationType.LOADING) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.LoadingProcessStyle.bind(this)(i9 ? i9 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    IconSecondaryTitleStyle(o8, p8 = null) {
        this.observeComponentCreation2((f9, g9) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                top: this.ageing ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) :
                    LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                bottom: this.ageing ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) :
                    LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
            Flex.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Flex);
        this.observeComponentCreation2((v8, w8) => {
            If.create();
            if (Util.isSymbolResource(o8.iconOptions?.icon)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d9, e9) => {
                        SymbolGlyph.create(o8.iconOptions?.icon);
                        SymbolGlyph.fontSize(o8.iconOptions?.symbolicIconOption?.fontSize ?? LEFT_ICON_SIZE);
                        SymbolGlyph.fontColor(o8.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.leftIconColor]);
                        SymbolGlyph.fontWeight(o8.iconOptions?.symbolicIconOption?.fontWeight);
                        SymbolGlyph.renderingStrategy(o8.iconOptions?.symbolicIconOption?.renderingStrategy);
                        SymbolGlyph.effectStrategy(o8.iconOptions?.symbolicIconOption?.effectStrategy);
                        SymbolGlyph.margin({ end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) });
                        SymbolGlyph.flexShrink(0);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((z8, a9) => {
                        Image.create(o8.iconOptions?.icon);
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
        this.observeComponentCreation2((t8, u8) => {
            Text.create(o8.content);
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
    SubTitleStyle(c8, d8 = null) {
        this.observeComponentCreation2((l8, m8) => {
            Column.create();
            Column.padding({
                end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                top: this.ageing ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) :
                    LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                bottom: this.ageing ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) :
                    LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
            Column.alignItems(HorizontalAlign.Start);
            Column.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Column);
        this.observeComponentCreation2((j8, k8) => {
            Text.create(c8.content);
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
        this.observeComponentCreation2((h8, i8) => {
            Text.create(c8.subContent);
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
    SecondTitleStyle(t7, u7 = null) {
        this.observeComponentCreation2((a8, b8) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                top: this.ageing ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) :
                    LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                bottom: this.ageing ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) :
                    LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
        }, Column);
        this.observeComponentCreation2((x7, y7) => {
            Text.create(t7.content);
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
    SelectStyle(h7, i7 = null) {
        this.observeComponentCreation2((q7, r7) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Column);
        this.observeComponentCreation2((l7, m7) => {
            Select.create(h7.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
            Select.value(ObservedObject.GetRawObject(this.selectValue));
            Select.onSelect((o7, p7) => {
                this.selectedIndex = o7;
                if (p7) {
                    this.selectValue = p7;
                }
                if (h7.onSelect) {
                    h7.onSelect(o7, p7);
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
    PrimaryTitleStyle(y6, z6 = null) {
        this.observeComponentCreation2((f7, g7) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                top: this.ageing ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) :
                    LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                bottom: this.ageing ? LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) :
                    LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
        }, Column);
        this.observeComponentCreation2((c7, d7) => {
            Text.create(y6.content);
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
    ButtonStyle(m5, n5 = null) {
        this.observeComponentCreation2((w6, x6) => {
            Row.create();
            Row.margin({
                start: LengthMetrics.resource(this.ageing ? { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((u6, v6) => {
            Stack.create();
            Stack.focusable(true);
        }, Stack);
        this.observeComponentCreation2((z5, a6) => {
            If.create();
            if (m5) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h6, i6) => {
                        Row.create();
                        Row.padding({
                            start: LengthMetrics.resource(this.ageing ? { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                            end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                            top: LengthMetrics.resource(this.ageing ? { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                            bottom: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
                        });
                        Row.margin({
                            bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Row.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
                        Row.focusable(true);
                        Row.constraintSize({ minHeight: BUTTON_HEIGHT });
                        Row.justifyContent(FlexAlign.End);
                        Row.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Row.onFocus(() => {
                            this.buttonFocus = true;
                        });
                        Row.onBlur(() => {
                            this.buttonFocus = false;
                        });
                        Row.onHover((t6) => {
                            if (t6) {
                                this.buttonBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                            }
                            else {
                                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Row.onTouch((s6) => {
                            if (s6.type === TouchType.Down) {
                                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            if (s6.type === TouchType.Up) {
                                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Row.onClick((r6) => {
                            if (m5.action) {
                                m5.action();
                            }
                        });
                        Row.onAreaChange((p6, q6) => {
                            this.buttonStyleWidth = Number(q6.width);
                            this.buttonStyleHeight = Number(q6.height);
                        });
                    }, Row);
                    this.observeComponentCreation2((f6, g6) => {
                        Text.create(m5.value);
                        __Text__secondaryTitleStyles({
                            fontWeight: FontWeight.Medium,
                            maxLines: DOUBLE_LINE_NUM,
                            fontColor: this.subHeaderTheme.fontButtonColor,
                        });
                        Text.focusable(true);
                    }, Text);
                    Text.pop();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((s5, t5) => {
            If.create();
            if (this.buttonFocus) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x5, y5) => {
                        Row.create();
                        Row.height(this.buttonStyleHeight);
                        Row.width(this.buttonStyleWidth);
                        Row.hitTestBehavior(HitTestMode.None);
                        Row.border({
                            width: BORDER_WIDTH,
                            color: this.subHeaderTheme.borderFocusColor
                        });
                        Row.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                    }, Row);
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Stack.pop();
        Row.pop();
    }
    TextArrowStyle(c4, d4 = null) {
        this.observeComponentCreation2((e5, f5) => {
            Row.create();
            Row.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.subHeaderModifier));
            Row.onHover((l5) => {
                if (l5) {
                    this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                }
                else {
                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
            });
            Row.onTouch((k5) => {
                if (k5.type === TouchType.Down) {
                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
                if (k5.type === TouchType.Up) {
                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
            });
            Row.onClick((j5) => {
                if (c4.action) {
                    c4.action();
                }
            });
            Row.focusable(true);
            Row.justifyContent(this.ageing ? FlexAlign.SpaceBetween : FlexAlign.End);
            Row.margin({
                start: LengthMetrics.resource(this.ageing ? { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                bottom: LengthMetrics.resource(this.ageing ? { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
        }, Row);
        this.observeComponentCreation2((c5, d5) => {
            Stack.create();
        }, Stack);
        this.observeComponentCreation2((v4, w4) => {
            Row.create();
            Row.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.subHeaderModifier));
            Row.alignItems(VerticalAlign.Center);
            Row.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Row.focusable(true);
            Row.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
            Row.constraintSize({ minHeight: BUTTON_ZONE_SIZE });
            Row.onFocus(() => {
                this.textArrowFocus = true;
            });
            Row.onBlur(() => {
                this.textArrowFocus = false;
            });
            Row.padding({
                start: this.ageing ? LengthMetrics.vp(0) : this.getTextArrowPaddingLeft(),
                bottom: this.ageing ? LengthMetrics.vp(8) : LengthMetrics.vp(0),
            });
            Row.onAreaChange((a5, b5) => {
                this.textArrowStyleWidth = Number(b5.width);
                this.textArrowStyleHeight = Number(b5.height);
            });
        }, Row);
        this.observeComponentCreation2((o4, p4) => {
            If.create();
            if (c4) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t4, u4) => {
                        Text.create(c4.value);
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
        this.observeComponentCreation2((m4, n4) => {
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
        this.observeComponentCreation2((k4, l4) => {
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
    IconGroupStyle(n2, o2 = null) {
        this.observeComponentCreation2((a4, b4) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
            Row.margin({
                start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
        }, Row);
        this.observeComponentCreation2((r2, s2) => {
            ForEach.create();
            const t2 = (v2, w2) => {
                const x2 = v2;
                this.observeComponentCreation2((z2, a3) => {
                    If.create();
                    if (Util.isResourceType(x2.value)) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((e3, f3) => {
                                If.create();
                                if (w2 === INDEX_ZERO) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        {
                                            this.observeComponentCreation2((u3, v3) => {
                                                if (v3) {
                                                    let w3 = new SingleIconStyle(typeof PUV2ViewBase !== "undefined" && o2 instanceof PUV2ViewBase ? o2 : this, {
                                                        item: {
                                                            iconOptions: {
                                                                icon: x2.value,
                                                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > w2 ?
                                                                    this.operationSymbolOptions[w2] : null,
                                                            },
                                                            action: x2.action,
                                                        }
                                                    }, undefined, u3, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 724, col: 13 });
                                                    ViewPU.create(w3);
                                                    let x3 = () => {
                                                        return {
                                                            item: {
                                                                iconOptions: {
                                                                    icon: x2.value,
                                                                    symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > w2 ?
                                                                        this.operationSymbolOptions[w2] : null,
                                                                },
                                                                action: x2.action,
                                                            }
                                                        };
                                                    };
                                                    w3.paramsGenerator_ = x3;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(u3, {});
                                                }
                                            }, { name: "SingleIconStyle" });
                                        }
                                    });
                                }
                                else if (w2 === INDEX_ONE || w2 === INDEX_TWO) {
                                    this.ifElseBranchUpdateFunction(1, () => {
                                        this.observeComponentCreation2((q3, r3) => {
                                            __Common__.create();
                                            __Common__.margin({
                                                start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((k3, l3) => {
                                                if (l3) {
                                                    let m3 = new SingleIconStyle(typeof PUV2ViewBase !== "undefined" && o2 instanceof PUV2ViewBase ? o2 : this, {
                                                        item: {
                                                            action: x2.action,
                                                            iconOptions: {
                                                                icon: x2.value,
                                                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > w2 ?
                                                                    this.operationSymbolOptions[w2] : null,
                                                            },
                                                        }
                                                    }, undefined, k3, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 735, col: 13 });
                                                    ViewPU.create(m3);
                                                    let n3 = () => {
                                                        return {
                                                            item: {
                                                                action: x2.action,
                                                                iconOptions: {
                                                                    icon: x2.value,
                                                                    symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > w2 ?
                                                                        this.operationSymbolOptions[w2] : null,
                                                                },
                                                            }
                                                        };
                                                    };
                                                    m3.paramsGenerator_ = n3;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(k3, {});
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
            this.forEachUpdateFunction(r2, n2, t2, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    LoadingProcessStyle(g2 = null) {
        this.observeComponentCreation2((l2, m2) => {
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
        this.observeComponentCreation2((j2, k2) => {
            LoadingProgress.create();
            LoadingProgress.width(LOADING_SIZE);
            LoadingProgress.height(LOADING_SIZE);
            LoadingProgress.color({ "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, LoadingProgress);
        Row.pop();
    }
    dummyFunction(b2 = null) {
        this.observeComponentCreation2((d2, e2) => {
            Row.create();
            Row.onAppear(() => {
                this.changeFlexAlign(FlexAlign.End);
            });
        }, Row);
        Row.pop();
    }
    changeFlexAlign(a2) {
        if (this.flexAlign === a2) {
            return;
        }
        this.flexAlign = a2;
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class SingleIconStyle extends ViewPU {
    constructor(u1, v1, w1, x1 = -1, y1 = undefined, z1) {
        super(u1, w1, x1, z1);
        if (typeof y1 === "function") {
            this.paramsGenerator_ = y1;
        }
        this.__bgColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "bgColor");
        this.__isFocus = new ObservedPropertySimplePU(false, this, "isFocus");
        this.item = null;
        this.__subHeaderTheme = this.initializeConsume("subHeaderTheme", "subHeaderTheme");
        this.setInitiallyProvidedValue(v1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(t1) {
        if (t1.bgColor !== undefined) {
            this.bgColor = t1.bgColor;
        }
        if (t1.isFocus !== undefined) {
            this.isFocus = t1.isFocus;
        }
        if (t1.item !== undefined) {
            this.item = t1.item;
        }
    }
    updateStateVars(s1) {
    }
    purgeVariableDependenciesOnElmtId(r1) {
        this.__bgColor.purgeDependencyOnElmtId(r1);
        this.__isFocus.purgeDependencyOnElmtId(r1);
        this.__subHeaderTheme.purgeDependencyOnElmtId(r1);
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
    set bgColor(q1) {
        this.__bgColor.set(q1);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(p1) {
        this.__isFocus.set(p1);
    }
    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }
    set subHeaderTheme(o1) {
        this.__subHeaderTheme.set(o1);
    }
    initialRender() {
        this.observeComponentCreation2((b1, c1) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g1, h1) => {
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
                        Row.onTouch((n1) => {
                            if (n1.type === TouchType.Down) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            if (n1.type === TouchType.Up) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Row.onHover((m1) => {
                            if (m1) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            else {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Row.onClick((l1) => {
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
    symbolFontSize(y) {
        if (typeof y === 'string') {
            const z = parseInt(y);
            return z + 'vp';
        }
        else if (typeof y === 'number') {
            return y + 'vp';
        }
        else {
            return resourceManager.getSystemResourceManager().getNumber(y) + 'vp';
        }
    }
    IconZone(h = null) {
        this.observeComponentCreation2((j, k) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o, p) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((w, x) => {
                                    SymbolGlyph.create(this.item.iconOptions?.icon);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.fontSize(this.item.iconOptions?.symbolicIconOption?.fontSize ?
                                        this.symbolFontSize(this.item.iconOptions?.symbolicIconOption?.fontSize) : RIGHT_SINGLE_ICON_SIZE);
                                    SymbolGlyph.fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.rightIconColor]);
                                    SymbolGlyph.fontWeight(this.item.iconOptions?.symbolicIconOption?.fontWeight);
                                    SymbolGlyph.renderingStrategy(this.item.iconOptions?.symbolicIconOption?.renderingStrategy);
                                    SymbolGlyph.effectStrategy(this.item.iconOptions?.symbolicIconOption?.effectStrategy);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((s, t) => {
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
    static isSymbolResource(f) {
        if (!Util.isResourceType(f)) {
            return false;
        }
        let g = f;
        return g.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(e) {
        if (!e) {
            return false;
        }
        if (typeof e === 'string' || typeof e === 'undefined') {
            return false;
        }
        return true;
    }
    static getNumberByResource(a) {
        try {
            return resourceManager.getSystemResourceManager().getNumberByName(a);
        }
        catch (b) {
            let c = b.code;
            let d = b.message;
            hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${c}, message: ${d}`);
            return Util.DEFAULT_VALUE;
        }
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