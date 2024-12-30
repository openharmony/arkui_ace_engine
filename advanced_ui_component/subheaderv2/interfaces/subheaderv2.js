/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
let TextModifier;
if (globalThis.__hasUIFramework__) {
    TextModifier = requireNapi('arkui.modifier').TextModifier;
} else {
    TextModifier = requireNapi('arkui.mock').TextModifier;
}

var __decorate = (this && this.__decorate) || function (g16, h16, i16, j16) {
    var k16 = arguments.length, l16 = k16 < 3 ? h16 : j16 === null ? j16 = Object.getOwnPropertyDescriptor(h16, i16) : j16, m16;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        l16 = Reflect.decorate(g16, h16, i16, j16);
    else
        for (var n16 = g16.length - 1; n16 >= 0; n16--)
            if (m16 = g16[n16])
                l16 = (k16 < 3 ? m16(l16) : k16 > 3 ? m16(h16, i16, l16) : m16(h16, i16)) || l16;
    return k16 > 3 && l16 && Object.defineProperty(h16, i16, l16), l16;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const arkuiNode = requireNapi('arkui.node');
const LengthMetrics = arkuiNode.LengthMetrics;
const ColorMetrics = arkuiNode.ColorMetrics;
const LengthUnit = arkuiNode.LengthUnit;
const resourceManager = requireNapi('resourceManager');
const BusinessError = requireNapi('base');
const common = requireNapi('app.ability.common');
const hilog = requireNapi('hilog');
const HashMap = requireNapi('util.HashMap');
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;

const INDEX_ZERO = 0;
const INDEX_ONE = 1;
const INDEX_TWO = 2;
const SINGLE_LINE_NUM = 1;
const DOUBLE_LINE_NUM = 2;
const RESOURCE_TYPE_SYMBOL = 40000;
const LEFT_ICON_SIZE = '16vp';
const LEFT_ICON_SIZE_NUMBER = 16;
const LEFT_TEXT_NUMBER = 8;
const OPERATE_ITEM_LENGTH = 24;
const ARROW_ICON_WIDTH = 12;
const SINGLE_ICON_ZONE_SIZE = 28;
const RIGHT_SINGLE_ICON_SIZE = '24vp';
const PADDING_LEVEL_2 = 4;
const MAX_RIGHT_WIDTH = '34%';
const MIN_FONT_SIZE = 1.75;
const MIN_HOT_AREA_LENGTH = 40;
const MULTI_ICON_REGION_WIDTH = 37;
const ICON_REGION_X = -9;
const ICON_REGION_Y = -6;
const SINGLE_ICON_REGION_X = -12;
const SINGLE_ICON_NUMBER = 1;
const PADDING_LEFT = 2;
let SubHeaderV2Title = class SubHeaderV2Title {
    constructor(e16) {
        this.primaryTitle = e16.primaryTitle;
        this.primaryTitleModifier = e16.primaryTitleModifier;
        this.secondaryTitle = e16.secondaryTitle;
        this.secondaryTitleModifier = e16.secondaryTitleModifier;
    }
};
__decorate([
    Trace
], SubHeaderV2Title.prototype, "primaryTitle", void 0);
__decorate([
    Trace
], SubHeaderV2Title.prototype, "primaryTitleModifier", void 0);
__decorate([
    Trace
], SubHeaderV2Title.prototype, "secondaryTitle", void 0);
__decorate([
    Trace
], SubHeaderV2Title.prototype, "secondaryTitleModifier", void 0);
SubHeaderV2Title = __decorate([
    ObservedV2
], SubHeaderV2Title);
export { SubHeaderV2Title };
let SubHeaderV2Select = class SubHeaderV2Select {
    constructor(d16) {
        this.options = d16.options;
        this.selectedIndex = d16.selectedIndex;
        this.selectedContent = d16.selectedContent;
        this.onSelect = d16.onSelect;
    }
};
__decorate([
    Trace
], SubHeaderV2Select.prototype, "options", void 0);
__decorate([
    Trace
], SubHeaderV2Select.prototype, "selectedIndex", void 0);
__decorate([
    Trace
], SubHeaderV2Select.prototype, "selectedContent", void 0);
__decorate([
    Trace
], SubHeaderV2Select.prototype, "onSelect", void 0);
SubHeaderV2Select = __decorate([
    ObservedV2
], SubHeaderV2Select);
export { SubHeaderV2Select };
export var SubHeaderV2OperationType;
(function (c16) {
    c16[c16["TEXT_ARROW"] = 0] = "TEXT_ARROW";
    c16[c16["BUTTON"] = 1] = "BUTTON";
    c16[c16["ICON_GROUP"] = 2] = "ICON_GROUP";
    c16[c16["LOADING"] = 3] = "LOADING";
})(SubHeaderV2OperationType || (SubHeaderV2OperationType = {}));
let SubHeaderV2OperationItem = class SubHeaderV2OperationItem {
    constructor(b16) {
        this.content = b16.content;
        this.action = b16.action;
        this.accessibilityText = b16.accessibilityText;
        this.accessibilityDescription = b16.accessibilityDescription;
        this.accessibilityLevel = b16.accessibilityLevel;
    }
};
__decorate([
    Trace
], SubHeaderV2OperationItem.prototype, "content", void 0);
__decorate([
    Trace
], SubHeaderV2OperationItem.prototype, "action", void 0);
__decorate([
    Trace
], SubHeaderV2OperationItem.prototype, "accessibilityText", void 0);
__decorate([
    Trace
], SubHeaderV2OperationItem.prototype, "accessibilityDescription", void 0);
__decorate([
    Trace
], SubHeaderV2OperationItem.prototype, "accessibilityLevel", void 0);
SubHeaderV2OperationItem = __decorate([
    ObservedV2
], SubHeaderV2OperationItem);
export { SubHeaderV2OperationItem };
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
function __Text__secondaryTitleStyles(a16) {
    Text.fontSize(`${getResourceValue('sys.float.Subtitle_S')}fp`);
    Text.fontColor(a16?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(a16?.fontWeight);
    Text.maxLines(a16?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(a16?.alignment);
}
function __Text__primaryTitleStyles(z15) {
    Text.fontSize(`${getResourceValue('sys.float.subheader_title_font_size')}fp`);
    Text.fontColor(z15?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(z15?.fontWeight);
    Text.maxLines(z15?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(z15?.alignment);
}
class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }
    applyNormalAttribute(y15) {
        if (this.isAgeing) {
            y15.width('100%');
        }
        else {
        }
    }
}
export class SubHeaderV2 extends ViewV2 {
    constructor(s15, t15, u15, v15 = -1, w15, x15) {
        super(s15, v15, x15);
        this.initParam("icon", (t15 && "icon" in t15) ? t15.icon : undefined);
        this.initParam("title", (t15 && "title" in t15) ? t15.title : undefined);
        this.initParam("select", (t15 && "select" in t15) ? t15.select : undefined);
        this.initParam("operationType", (t15 && "operationType" in t15) ? t15.operationType : SubHeaderV2OperationType.BUTTON);
        this.initParam("operationItems", (t15 && "operationItems" in t15) ? t15.operationItems : undefined);
        this.titleBuilder = "titleBuilder" in t15 ? t15.titleBuilder : undefined;
        this.fontSize = 1;
        this.ageing = true;
        this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.selectedIndex = -1;
        this.selectedContent = '';
        this.symbolWidth = LEFT_ICON_SIZE_NUMBER + LEFT_TEXT_NUMBER;
        this.subHeaderModifier = new SubHeaderModifier();
        this.isFollowingSystemFontScale = "isFollowingSystemFontScale" in t15 ? t15.isFollowingSystemFontScale : false;
        this.appMaxFontScale = "appMaxFontScale" in t15 ? t15.appMaxFontScale : 3.2;
        this.subHeaderV2Theme = new SubHeaderTheme();
        this.subHeaderMargin = "subHeaderMargin" in t15 ? t15.subHeaderMargin : {
            start: LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
            end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
        };
        this.finalizeConstruction();
    }
    onWillApplyTheme(r15) {
        this.subHeaderV2Theme.fontPrimaryColor = r15.colors.fontPrimary;
        this.subHeaderV2Theme.fontSecondaryColor = r15.colors.fontSecondary;
        this.subHeaderV2Theme.fontButtonColor = r15.colors.fontEmphasize;
        this.subHeaderV2Theme.iconArrowColor = r15.colors.iconTertiary;
        this.subHeaderV2Theme.textArrowHoverBgColor = r15.colors.interactiveHover;
        this.subHeaderV2Theme.borderFocusColor = r15.colors.interactiveFocus;
        this.subHeaderV2Theme.leftIconColor = r15.colors.iconSecondary;
        this.subHeaderV2Theme.rightIconColor = r15.colors.iconPrimary;
    }
    async aboutToAppear() {
        let q15 = this.getUIContext();
        this.isFollowingSystemFontScale = q15.isFollowingSystemFontScale();
        this.appMaxFontScale = q15.getMaxFontScale();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        if (this.select) {
            this.selectedIndex = this.select.selectedIndex;
            this.selectedContent = this.select.selectedContent;
        }
    }
    updateFontScale() {
        try {
            let o15 = this.getUIContext();
            let p15 = o15.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(p15, this.appMaxFontScale);
        }
        catch (l15) {
            let m15 = l15.code;
            let n15 = l15.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${m15}, message: ${n15}`);
            return 1;
        }
    }
    IconSecondaryTitleStyle(m14, n14 = null) {
        this.observeComponentCreation2((j15, k15) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
            });
        }, Flex);
        this.observeComponentCreation2((t14, u14) => {
            If.create();
            if (Util.isSymbolResource(m14.iconOptions)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((b15, c15) => {
                            if (c15) {
                                let d15 = new SymbolGlyphChild(ViewPU.__proto__ !== NativeViewPartialUpdate && n14 instanceof PUV2ViewBase ? n14 : this, {
                                    icon: m14.iconOptions,
                                    fontColor: [this.subHeaderV2Theme.leftIconColor],
                                    changeSymbolWidth: (i15) => {
                                        this.symbolWidth = i15.width;
                                    }
                                }, undefined, b15, () => { }, { page: "library/src/main/ets/components/subheaderv2.ets", line: 302 });
                                ViewV2.create(d15);
                                let e15 = () => {
                                    return {
                                        icon: m14.iconOptions,
                                        fontColor: [this.subHeaderV2Theme.leftIconColor],
                                        changeSymbolWidth: (h15) => {
                                            this.symbolWidth = h15.width;
                                        }
                                    };
                                };
                                d15.paramsGenerator_ = e15;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(b15, {
                                    icon: m14.iconOptions,
                                    fontColor: [this.subHeaderV2Theme.leftIconColor]
                                });
                            }
                        }, { name: "SymbolGlyphChild" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((x14, y14) => {
                        Image.create(m14.iconOptions);
                        Image.fillColor(this.subHeaderV2Theme.leftIconColor);
                        Image.width(LEFT_ICON_SIZE);
                        Image.height(LEFT_ICON_SIZE);
                        Image.margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) });
                        Image.draggable(false);
                        Image.flexShrink(0);
                    }, Image);
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((r14, s14) => {
            Text.create(m14.content);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
                fontColor: this.subHeaderV2Theme.fontSecondaryColor,
            });
            Text.attributeModifier.bind(this)(this.title?.secondaryTitleModifier);
            Text.flexShrink(1);
        }, Text);
        Text.pop();
        Flex.pop();
    }
    isSuitableAging() {
        return (this.fontSize >= MIN_FONT_SIZE) && ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW) ||
            this.operationType === SubHeaderV2OperationType.BUTTON) && this.operationItems !== undefined &&
            (this.operationItems?.length > 0) && this.operationItems[0].content !== '';
    }
    isLeftAreaAccessibilityGroup() {
        if (this.titleBuilder || this.title?.secondaryTitle) {
            return true;
        }
        if (this.select) {
            return false;
        }
        return true;
    }
    SelectStyle(e14, f14 = null) {
        this.observeComponentCreation2((h14, i14) => {
            Select.create(e14.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(this.selectedIndex);
            Select.value(this.selectedContent);
            Select.onSelect((k14, l14) => {
                this.selectedIndex = k14;
                if (l14) {
                    this.selectedContent = l14;
                }
                if (e14.onSelect) {
                    e14.onSelect(k14, l14);
                }
            });
            Select.font({
                size: `${getResourceValue('sys.float.Body_L')}fp`,
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
    }
    SubTitleStyle(t13, u13 = null) {
        this.observeComponentCreation2((c14, d14) => {
            Column.create();
            Column.width('100%');
            Column.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level0')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((a14, b14) => {
            Text.create(t13.content);
            __Text__primaryTitleStyles({
                fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderV2Theme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(this.title?.primaryTitleModifier);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((y13, z13) => {
            Text.create(t13.subContent);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Regular,
                alignment: Alignment.Start,
                fontColor: this.subHeaderV2Theme.fontSecondaryColor,
            });
            Text.margin({
                top: getResourceValue('sys.float.padding_level1'),
            });
            Text.attributeModifier.bind(this)(this.title?.secondaryTitleModifier);
        }, Text);
        Text.pop();
        Column.pop();
    }
    SecondTitleStyle(o13, p13 = null) {
        this.observeComponentCreation2((r13, s13) => {
            Text.create(o13.content);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
                fontColor: this.subHeaderV2Theme.fontSecondaryColor,
            });
            Text.attributeModifier.bind(this)(this.title?.secondaryTitleModifier);
            Text.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
            });
        }, Text);
        Text.pop();
    }
    PrimaryTitleStyle(j13, k13 = null) {
        this.observeComponentCreation2((m13, n13) => {
            Text.create(j13.content);
            __Text__primaryTitleStyles({
                fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderV2Theme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(this.title?.primaryTitleModifier);
            Text.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level0')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
            });
        }, Text);
        Text.pop();
    }
    leftArea(y12 = null) {
        this.observeComponentCreation2((a13, b13) => {
            If.create();
            if (this.titleBuilder) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.titleBuilder.bind(this)(y12 ? y12 : this);
                });
            }
            else if (this.title?.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy("IconSecondaryTitleStyle", { content: () => this.title?.secondaryTitle, iconOptions: () => (this["__icon"] ? this["__icon"] : this["icon"]) }), y12 ? y12 : this);
                });
            }
            else if (this.title?.secondaryTitle && this.title?.primaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy("SubTitleStyle", { content: () => this.title?.primaryTitle, subContent: () => this.title?.secondaryTitle }), y12 ? y12 : this);
                });
            }
            else if (this.title?.secondaryTitle) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy("SecondTitleStyle", { content: () => this.title?.secondaryTitle }), y12 ? y12 : this);
                });
            }
            else if (this.select) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.SelectStyle.bind(this)(this.select, y12 ? y12 : this);
                });
            }
            else if (this.title?.primaryTitle) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy("PrimaryTitleStyle", { content: () => this.title?.primaryTitle }), y12 ? y12 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.dummyFunction.bind(this)(y12 ? y12 : this);
                });
            }
        }, If);
        If.pop();
    }
    isRightAreaExists() {
        if (this.operationItems && this.operationItems.length > 0) {
            return true;
        }
        if (this.operationType === SubHeaderV2OperationType.LOADING) {
            return true;
        }
        return false;
    }
    getRightAreaMaxWidth() {
        if (this.operationType === SubHeaderV2OperationType.ICON_GROUP && (this.operationItems && this.operationItems.length > 0)) {
            return '100%';
        }
        return MAX_RIGHT_WIDTH;
    }
    getRightAreaMinWidth() {
        if (this.operationItems && this.operationItems.length > 0) {
            return MIN_HOT_AREA_LENGTH;
        }
        return 0;
    }
    getAccessibilityDescription() {
        if (!this.operationItems || this.operationItems.length <= 0) {
            return '';
        }
        if (this.operationItems[0]?.accessibilityDescription && this.operationItems[0]?.accessibilityDescription !== '') {
            return this.toStringFormat(this.operationItems[0]?.accessibilityDescription);
        }
        return '';
    }
    leftIconMargin() {
        if (this.titleBuilder) {
            return LengthMetrics.vp(0);
        }
        if (this.icon && Util.isSymbolResource(this.icon)) {
            return this.ageing ?
            LengthMetrics.vp(this.symbolWidth) :
            LengthMetrics.vp(0);
        }
        else {
            return (this.ageing && this.icon) ? LengthMetrics.vp(LEFT_ICON_SIZE_NUMBER +
                LEFT_TEXT_NUMBER) : LengthMetrics.vp(0);
        }
    }
    ButtonStyle(k12 = null) {
        this.observeComponentCreation2((m12, n12) => {
            If.create();
            if (this.operationItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u12, v12) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(true);
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderV2Theme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        Button.padding({
                            start: LengthMetrics.vp(getResourceValue('sys.float.padding_level1')),
                            end: LengthMetrics.vp(getResourceValue('sys.float.padding_level1')),
                            top: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
                            bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
                        });
                        Button.margin({
                            start: this.ageing ?
                            LengthMetrics.vp(LengthMetrics.vp(getResourceValue('sys.float.padding_level0')).value +
                            this.leftIconMargin().value) :
                            LengthMetrics.vp(LengthMetrics.vp(getResourceValue('sys.float.padding_level4')).value +
                            this.leftIconMargin().value),
                            bottom: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                            getResourceValue('sys.float.padding_level2')),
                        });
                        Button.backgroundColor(this.buttonBgColor);
                        Button.constraintSize({ minHeight: OPERATE_ITEM_LENGTH });
                        Button.align(Alignment.End);
                        Button.borderRadius(getResourceValue('sys.float.corner_radius_level4'));
                        Button.onHover((x12) => {
                            if (x12) {
                                this.buttonBgColor = this.subHeaderV2Theme.textArrowHoverBgColor;
                            }
                            else {
                                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        ViewStackProcessor.visualState("pressed");
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("disabled");
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                    }, Button);
                    this.observeComponentCreation2((s12, t12) => {
                        Text.create(this.operationItems[0].content);
                        __Text__secondaryTitleStyles({
                            fontWeight: FontWeight.Medium,
                            maxLines: DOUBLE_LINE_NUM,
                            fontColor: this.subHeaderV2Theme.fontButtonColor,
                        });
                        Text.focusable(true);
                    }, Text);
                    Text.pop();
                    Button.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    getTextArrowPaddingLeft() {
        if (this.operationItems && this.operationItems.length > 0 && this.operationItems[0].content) {
            return LengthMetrics.vp(getResourceValue('sys.float.padding_level1'));
        }
        return LengthMetrics.vp(getResourceValue('sys.float.padding_level0'));
    }
    getTextArrowMarginRight() {
        if (this.operationItems && this.operationItems.length > 0 && this.operationItems[0].content) {
            return LengthMetrics.vp(PADDING_LEVEL_2 + ARROW_ICON_WIDTH);
        }
        return LengthMetrics.vp(ARROW_ICON_WIDTH);
    }
    TextStyle(y11 = null) {
        this.observeComponentCreation2((i12, j12) => {
            Row.create();
            Row.attributeModifier.bind(this)(this.subHeaderModifier);
            Row.alignItems(VerticalAlign.Center);
            Row.focusable(true);
            Row.constraintSize({ minHeight: OPERATE_ITEM_LENGTH });
            Row.padding({
                start: this.getTextArrowPaddingLeft(),
                top: this.ageing ? LengthMetrics.vp(0) : LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
                bottom: this.ageing ? LengthMetrics.vp(0) : LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
            });
        }, Row);
        this.observeComponentCreation2((b12, c12) => {
            If.create();
            if (this.operationItems?.[0]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g12, h12) => {
                        Text.create(this.operationItems[0].content);
                        __Text__secondaryTitleStyles({
                            maxLines: DOUBLE_LINE_NUM,
                            fontWeight: FontWeight.Regular,
                            alignment: Alignment.End,
                            fontColor: this.subHeaderV2Theme.fontSecondaryColor,
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
    }
    ArrowStyle(r11 = null) {
        this.observeComponentCreation2((w11, x11) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((u11, v11) => {
            Image.create({ "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_arrow_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.fillColor(this.subHeaderV2Theme.iconArrowColor);
            Image.width(ARROW_ICON_WIDTH);
            Image.height(OPERATE_ITEM_LENGTH);
            Image.focusable(true);
            Image.draggable(false);
            Image.matchTextDirection(true);
        }, Image);
        Row.pop();
    }
    TextArrowStyle(n9 = null) {
        this.observeComponentCreation2((p9, q9) => {
            If.create();
            if (this.operationItems?.[0] && this.operationItems[0] && this.operationItems[0].content
                && this.operationItems[0].content.toString().length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p11, q11) => {
                        Stack.create();
                        Stack.focusable(true);
                        Stack.align(this.ageing ? Alignment.Start : Alignment.End);
                        Stack.margin({
                            start: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                            getResourceValue('sys.float.padding_level4')),
                            bottom: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                            getResourceValue('sys.float.padding_level2')),
                        });
                    }, Stack);
                    this.observeComponentCreation2((l11, m11) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.padding(INDEX_ZERO);
                        Button.margin({ start: this.leftIconMargin() });
                        Button.backgroundColor(this.textArrowBgColor);
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderV2Theme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        Button.borderRadius(getResourceValue('sys.float.corner_radius_level4'));
                        ViewStackProcessor.visualState("pressed");
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("disabled");
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                        Button.onHover((o11) => {
                            if (o11) {
                                this.textArrowBgColor = this.subHeaderV2Theme.textArrowHoverBgColor;
                            }
                            else {
                                this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                    }, Button);
                    {
                        this.observeComponentCreation2((h10, i10) => {
                            if (i10) {
                                let j10 = new TextArrowLayout(ViewPU.__proto__ !== NativeViewPartialUpdate && n9 instanceof PUV2ViewBase ? n9 : this, {
                                    textArrowBuilder: () => {
                                        this.observeComponentCreation2((a11, b11) => {
                                            ForEach.create();
                                            const c11 = e11 => {
                                                const f11 = e11;
                                                this.observeComponentCreation2((h11, i11) => {
                                                    If.create();
                                                    if (f11 === INDEX_ZERO) {
                                                        this.ifElseBranchUpdateFunction(0, () => {
                                                            this.TextStyle.bind(this)(n9 ? n9 : this);
                                                        });
                                                    }
                                                    else {
                                                        this.ifElseBranchUpdateFunction(1, () => {
                                                            this.ArrowStyle.bind(this)(n9 ? n9 : this);
                                                        });
                                                    }
                                                }, If);
                                                If.pop();
                                            };
                                            this.forEachUpdateFunction(a11, [INDEX_ZERO, INDEX_ONE], c11);
                                        }, ForEach);
                                        ForEach.pop();
                                    }
                                }, undefined, h10, () => { }, { page: "library/src/main/ets/components/subheaderv2.ets", line: 668 });
                                ViewPU.create(j10);
                                let k10 = () => {
                                    return {
                                        textArrowBuilder: () => {
                                            this.observeComponentCreation2((o10, p10) => {
                                                ForEach.create();
                                                const q10 = s10 => {
                                                    const t10 = s10;
                                                    this.observeComponentCreation2((v10, w10) => {
                                                        If.create();
                                                        if (t10 === INDEX_ZERO) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.TextStyle.bind(this)(n9 ? n9 : this);
                                                            });
                                                        }
                                                        else {
                                                            this.ifElseBranchUpdateFunction(1, () => {
                                                                this.ArrowStyle.bind(this)(n9 ? n9 : this);
                                                            });
                                                        }
                                                    }, If);
                                                    If.pop();
                                                };
                                                this.forEachUpdateFunction(o10, [INDEX_ZERO, INDEX_ONE], q10);
                                            }, ForEach);
                                            ForEach.pop();
                                        }
                                    };
                                };
                                j10.paramsGenerator_ = k10;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(h10, {});
                            }
                        }, { name: "TextArrowLayout" });
                    }
                    Button.pop();
                    Stack.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((b10, c10) => {
                        Row.create();
                        Row.focusable(true);
                        Row.constraintSize({ minWidth: this.getRightAreaMinWidth() });
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((x9, y9) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.width(ARROW_ICON_WIDTH);
                        Button.height(OPERATE_ITEM_LENGTH);
                        Button.backgroundColor(this.textArrowBgColor);
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderV2Theme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        Button.borderRadius(getResourceValue('sys.float.corner_radius_level4'));
                        ViewStackProcessor.visualState("pressed");
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("disabled");
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                        Button.onHover((a10) => {
                            if (a10) {
                                this.textArrowBgColor = this.subHeaderV2Theme.textArrowHoverBgColor;
                            }
                            else {
                                this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Button.focusable(true);
                        Button.margin({
                            start: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                            getResourceValue('sys.float.padding_level4')),
                            bottom: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                            getResourceValue('sys.float.padding_level2')),
                        });
                    }, Button);
                    this.observeComponentCreation2((v9, w9) => {
                        Image.create({ "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_arrow_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Image.fillColor(this.subHeaderV2Theme.iconArrowColor);
                        Image.width(ARROW_ICON_WIDTH);
                        Image.height(OPERATE_ITEM_LENGTH);
                        Image.focusable(true);
                        Image.draggable(false);
                        Image.matchTextDirection(true);
                    }, Image);
                    Button.pop();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }
    IconGroupStyle(e8 = null) {
        this.observeComponentCreation2((l9, m9) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((h8, i8) => {
            ForEach.create();
            const j8 = (o8, p8) => {
                const q8 = o8;
                this.observeComponentCreation2((s8, t8) => {
                    If.create();
                    if (Util.isResourceType(this.operationItems?.[p8].content)) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((x8, y8) => {
                                If.create();
                                if (p8 <= INDEX_TWO) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((j9, k9) => {
                                            __Common__.create();
                                            __Common__.margin({
                                                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                                                bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level3')),
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((d9, e9) => {
                                                if (e9) {
                                                    let f9 = new SingleIconStyle(ViewPU.__proto__ !== NativeViewPartialUpdate && e8 instanceof PUV2ViewBase ? e8 : this, {
                                                        item: {
                                                            iconOptions: this.operationItems?.[p8].content,
                                                            action: this.operationItems?.[p8].action,
                                                            accessibilityLevel: q8.accessibilityLevel,
                                                            accessibilityText: q8.accessibilityText,
                                                            accessibilityDescription: q8.accessibilityDescription,
                                                        },
                                                        isSingleIcon: this.operationItems?.length === SINGLE_ICON_NUMBER,
                                                    }, undefined, d9, () => { }, { page: "library/src/main/ets/components/subheaderv2.ets", line: 758 });
                                                    ViewV2.create(f9);
                                                    let g9 = () => {
                                                        return {
                                                            item: {
                                                                iconOptions: this.operationItems?.[p8].content,
                                                                action: this.operationItems?.[p8].action,
                                                                accessibilityLevel: q8.accessibilityLevel,
                                                                accessibilityText: q8.accessibilityText,
                                                                accessibilityDescription: q8.accessibilityDescription,
                                                            },
                                                            isSingleIcon: this.operationItems?.length === SINGLE_ICON_NUMBER
                                                        };
                                                    };
                                                    f9.paramsGenerator_ = g9;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(d9, {
                                                        item: {
                                                            iconOptions: this.operationItems?.[p8].content,
                                                            action: this.operationItems?.[p8].action,
                                                            accessibilityLevel: q8.accessibilityLevel,
                                                            accessibilityText: q8.accessibilityText,
                                                            accessibilityDescription: q8.accessibilityDescription,
                                                        },
                                                        isSingleIcon: this.operationItems?.length === SINGLE_ICON_NUMBER
                                                    });
                                                }
                                            }, { name: "SingleIconStyle" });
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
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(h8, this.operationItems, j8, (m8, n8) => {
                return `${n8}`;
            }, true, true);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rightArea(j7 = null) {
        this.observeComponentCreation2((a8, b8) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON && (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)(j7 ? j7 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((w7, x7) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW && (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextArrowStyle.bind(this)(j7 ? j7 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((s7, t7) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.ICON_GROUP && (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconGroupStyle.bind(this)(j7 ? j7 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((o7, p7) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.LOADING) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.LoadingProcessStyle.bind(this)(j7 ? j7 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    rightAreaParent(r6 = null) {
        this.observeComponentCreation2((t6, u6) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON || this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e7, f7) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItems ? true : false);
                        Button.margin(INDEX_ZERO);
                        Button.padding(INDEX_ZERO);
                        Button.align(Alignment.BottomEnd);
                        Button.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW || this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Button.onTouch((i7) => {
                            if (i7.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (i7.type === TouchType.Up || i7.type === TouchType.Cancel) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                        });
                        Button.constraintSize({
                            maxWidth: this.getRightAreaMaxWidth(),
                            minWidth: this.getRightAreaMinWidth(),
                            minHeight: MIN_HOT_AREA_LENGTH,
                        });
                        Button.flexShrink(0);
                        Button.accessibilityLevel(this.operationType === SubHeaderV2OperationType.BUTTON || this.operationType === SubHeaderV2OperationType.TEXT_ARROW ?
                        this.getRightAreaAccessibilityLevel() : 'no');
                        Button.hoverEffect(HoverEffect.None);
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                        Button.accessibilityDescription(this.getAccessibilityDescription());
                    }, Button);
                    this.rightArea.bind(this)(r6 ? r6 : this);
                    Button.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((x6, y6) => {
                        Row.create();
                        Row.focusable(this.operationItems && this.operationType !== SubHeaderV2OperationType.LOADING ? true : false);
                        Row.justifyContent(FlexAlign.End);
                        Row.alignItems(VerticalAlign.Bottom);
                        Row.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW || this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Row.onTouch((b7) => {
                            if (b7.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (b7.type === TouchType.Up || b7.type === TouchType.Cancel) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                        });
                        Row.constraintSize({
                            maxWidth: this.getRightAreaMaxWidth(),
                            minWidth: this.getRightAreaMinWidth(),
                            minHeight: MIN_HOT_AREA_LENGTH,
                        });
                        Row.flexShrink(0);
                        Row.accessibilityLevel(this.operationType === SubHeaderV2OperationType.BUTTON || this.operationType === SubHeaderV2OperationType.TEXT_ARROW ?
                        this.getRightAreaAccessibilityLevel() : 'no');
                    }, Row);
                    this.rightArea.bind(this)(r6 ? r6 : this);
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }
    rightAreaParentAging(z5 = null) {
        this.observeComponentCreation2((b6, c6) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON || this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m6, n6) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItems ? true : false);
                        Button.align(Alignment.Start);
                        Button.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW || this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Button.onTouch((q6) => {
                            if (q6.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (q6.type === TouchType.Up || q6.type === TouchType.Cancel) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                        });
                        Button.margin({
                            bottom: getResourceValue('sys.float.padding_level4'),
                        });
                        Button.padding({
                            start: LengthMetrics.vp(getResourceValue('sys.float.margin_left') - PADDING_LEFT),
                            end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
                        });
                        Button.accessibilityLevel(this.operationType === SubHeaderV2OperationType.BUTTON ||
                            this.operationType === SubHeaderV2OperationType.TEXT_ARROW ? this.getRightAreaAccessibilityLevel() : 'no');
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.hoverEffect(HoverEffect.None);
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                    }, Button);
                    this.rightArea.bind(this)(z5 ? z5 : this);
                    Button.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((f6, g6) => {
                        Row.create();
                        Row.focusable(this.operationItems && this.operationType !== SubHeaderV2OperationType.LOADING ? true : false);
                        Row.justifyContent(FlexAlign.Start);
                        Row.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW || this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Row.onTouch((j6) => {
                            if (j6.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (j6.type === TouchType.Up || j6.type === TouchType.Cancel) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                        });
                        Row.margin({
                            bottom: getResourceValue('sys.float.padding_level4'),
                        });
                        Row.padding({
                            start: LengthMetrics.vp(getResourceValue('sys.float.margin_left') - PADDING_LEFT),
                            end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
                        });
                        Row.accessibilityLevel(this.operationType === SubHeaderV2OperationType.BUTTON ||
                            this.operationType === SubHeaderV2OperationType.TEXT_ARROW ? this.getRightAreaAccessibilityLevel() : 'no');
                    }, Row);
                    this.rightArea.bind(this)(z5 ? z5 : this);
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }
    getRightAreaAccessibilityText() {
        if (!this.operationItems || this.operationItems?.length <= 0) {
            return '';
        }
        if (this.operationItems[0]?.accessibilityText && this.operationItems[0]?.accessibilityText !== '') {
            return this.toStringFormat(this.operationItems[0].accessibilityText);
        }
        else {
            if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW && this.operationItems[0]?.content.toString().length <= 0) {
                return Util.getStringByResource(125833704, '');
            }
        }
        return '';
    }
    getMinHeight() {
        if (this.title?.secondaryTitle && this.icon) {
            return getResourceValue('sys.float.subheader_single_subtitle_height');
        }
        else if (this.title?.secondaryTitle && this.title?.primaryTitle) {
            return getResourceValue('sys.float.subheader_double_height');
        }
        else if (this.title?.primaryTitle || this.select) {
            return getResourceValue('sys.float.subheader_single_title_height');
        }
        return getResourceValue('sys.float.subheader_single_subtitle_height');
    }
    getAreaPadding() {
        let y5 = {};
        if (!this.titleBuilder && ((this.title?.secondaryTitle && this.icon) ||
            (!this.title?.primaryTitle && this.title?.secondaryTitle))) {
            y5 = {
                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
            };
        }
        else if (this.select) {
            y5 = {
                top: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
                bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
            };
        }
        return y5;
    }
    initialRender() {
        this.observeComponentCreation2((y4, z4) => {
            If.create();
            if (this.isSuitableAging()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w5, x5) => {
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.padding(this.getAreaPadding());
                        Column.alignItems(HorizontalAlign.Start);
                    }, Column);
                    this.observeComponentCreation2((u5, v5) => {
                        Row.create();
                        Row.margin({
                            top: LengthMetrics.vp(getResourceValue('sys.float.padding_level8')),
                            bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level1')),
                        });
                        Row.padding({
                            start: LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
                            end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
                        });
                        Row.width('100%');
                        Row.accessibilityGroup(this.isLeftAreaAccessibilityGroup());
                        Row.accessibilityDescription(this.select ? '' : Util.getStringByResource(125834353, ''));
                    }, Row);
                    this.leftArea.bind(this)(this);
                    Row.pop();
                    this.observeComponentCreation2((q5, r5) => {
                        If.create();
                        if (this.isRightAreaExists()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.rightAreaParentAging.bind(this)(this);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((k5, l5) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((i5, j5) => {
                        Row.create();
                        Row.margin({
                            top: this.fontSize >= MIN_FONT_SIZE ? getResourceValue('sys.float.padding_level8') : '',
                            bottom: this.fontSize >= MIN_FONT_SIZE ? getResourceValue('sys.float.padding_level4') : '',
                        });
                        Row.width('100%');
                        Row.flexShrink(1);
                        Row.accessibilityGroup(this.isLeftAreaAccessibilityGroup());
                        Row.accessibilityDescription(this.select ? '' : Util.getStringByResource(125834353, ''));
                    }, Row);
                    this.leftArea.bind(this)(this);
                    Row.pop();
                    this.observeComponentCreation2((e5, f5) => {
                        If.create();
                        if (this.isRightAreaExists()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.rightAreaParent.bind(this)(this);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Flex.pop();
                });
            }
        }, If);
        If.pop();
    }
    toStringFormat(s4) {
        if (typeof s4 === 'string' || typeof s4 === 'undefined') {
            return s4;
        }
        else {
            let t4 = '';
            try {
                t4 = getContext()?.resourceManager?.getStringSync(s4);
            }
            catch (u4) {
                let v4 = u4?.code;
                let w4 = u4?.message;
                hilog.error(0x3900, 'Ace', `Faild to subHeader toStringFormat, code: ${v4}, message: ${w4}`);
            }
            return t4;
        }
    }
    getRightAreaAccessibilityLevel() {
        if (this.operationItems[0].accessibilityLevel && this.operationItems[0].accessibilityLevel !== '') {
            return this.operationItems[0].accessibilityLevel;
        }
        return 'yes';
    }
    LoadingProcessStyle(l4 = null) {
        this.observeComponentCreation2((q4, r4) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.padding({
                top: getResourceValue('sys.float.padding_level2'),
                bottom: getResourceValue('sys.float.padding_level2'),
            });
            Row.margin({
                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
            });
        }, Row);
        this.observeComponentCreation2((o4, p4) => {
            LoadingProgress.create();
            LoadingProgress.width(OPERATE_ITEM_LENGTH);
            LoadingProgress.height(OPERATE_ITEM_LENGTH);
            LoadingProgress.color({ "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, LoadingProgress);
        Row.pop();
    }
    dummyFunction(h4 = null) {
        this.observeComponentCreation2((j4, k4) => {
            Row.create();
        }, Row);
        Row.pop();
    }
    updateStateVars(g4) {
        if (g4 === undefined) {
            return;
        }
        if ("icon" in g4) {
            this.updateParam("icon", g4.icon);
        }
        if ("title" in g4) {
            this.updateParam("title", g4.title);
        }
        if ("select" in g4) {
            this.updateParam("select", g4.select);
        }
        if ("operationType" in g4) {
            this.updateParam("operationType", g4.operationType);
        }
        if ("operationItems" in g4) {
            this.updateParam("operationItems", g4.operationItems);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], SubHeaderV2.prototype, "icon", void 0);
__decorate([
    Param
], SubHeaderV2.prototype, "title", void 0);
__decorate([
    Param
], SubHeaderV2.prototype, "select", void 0);
__decorate([
    Param
], SubHeaderV2.prototype, "operationType", void 0);
__decorate([
    Param
], SubHeaderV2.prototype, "operationItems", void 0);
__decorate([
    Local
], SubHeaderV2.prototype, "fontSize", void 0);
__decorate([
    Local
], SubHeaderV2.prototype, "ageing", void 0);
__decorate([
    Local
], SubHeaderV2.prototype, "textArrowBgColor", void 0);
__decorate([
    Local
], SubHeaderV2.prototype, "buttonBgColor", void 0);
__decorate([
    Local
], SubHeaderV2.prototype, "selectedIndex", void 0);
__decorate([
    Local
], SubHeaderV2.prototype, "selectedContent", void 0);
__decorate([
    Local
], SubHeaderV2.prototype, "symbolWidth", void 0);
__decorate([
    Local
], SubHeaderV2.prototype, "subHeaderModifier", void 0);
__decorate([
    Provider('subHeaderV2Theme')
], SubHeaderV2.prototype, "subHeaderV2Theme", void 0);
class SymbolGlyphChild extends ViewV2 {
    constructor(z3, a4, b4, c4 = -1, d4, e4) {
        super(z3, c4, e4);
        this.initParam("icon", (a4 && "icon" in a4) ? a4.icon : undefined);
        this.initParam("fontColor", (a4 && "fontColor" in a4) ? a4.fontColor : undefined);
        this.changeSymbolWidth = "changeSymbolWidth" in a4 ? a4.changeSymbolWidth : () => { };
        this.result = "result" in a4 ? a4.result : {
            width: 0,
            height: 0
        };
        this.finalizeConstruction();
    }
    onMeasureSize(u3, v3, w3) {
        v3.forEach((y3) => {
            this.result = y3.measure(w3);
        });
        console.log(`zzzz Child onMeasureSize ${JSON.stringify(this.result)}`);
        this.changeSymbolWidth(this.result);
        return this.result;
    }
    initialRender() {
        this.observeComponentCreation2((s3, t3) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((q3, r3) => {
            SymbolGlyph.create(this.icon);
            SymbolGlyph.fontSize(LEFT_ICON_SIZE);
            SymbolGlyph.fontColor(this.fontColor);
            SymbolGlyph.attributeModifier.bind(this)(this.icon);
            SymbolGlyph.margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) });
            SymbolGlyph.flexShrink(0);
        }, SymbolGlyph);
        Column.pop();
    }
    updateStateVars(n3) {
        if (n3 === undefined) {
            return;
        }
        if ("icon" in n3) {
            this.updateParam("icon", n3.icon);
        }
        if ("fontColor" in n3) {
            this.updateParam("fontColor", n3.fontColor);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], SymbolGlyphChild.prototype, "icon", void 0);
__decorate([
    Param
], SymbolGlyphChild.prototype, "fontColor", void 0);
__decorate([
    Event
], SymbolGlyphChild.prototype, "changeSymbolWidth", void 0);
class SingleIconStyle extends ViewV2 {
    constructor(h3, i3, j3, k3 = -1, l3, m3) {
        super(h3, k3, m3);
        this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.isFocus = false;
        this.initParam("item", (i3 && "item" in i3) ? i3.item : null);
        this.subHeaderTheme = new SubHeaderTheme();
        this.initParam("isSingleIcon", (i3 && "isSingleIcon" in i3) ? i3.isSingleIcon : true);
        this.finalizeConstruction();
    }
    getRightIconAccessibilityText() {
        if (this.item?.accessibilityText) {
            let g3 = typeof this.item.accessibilityText === 'string' ? this.item.accessibilityText :
            getContext()?.resourceManager?.getStringSync(this.item.accessibilityText);
            return g3;
        }
        return '';
    }
    getRightIconAccessibilityLevel() {
        if (this.item?.accessibilityLevel && this.item?.accessibilityLevel !== '') {
            return this.item.accessibilityLevel;
        }
        return 'auto';
    }
    toStringFormat(b3) {
        if (typeof b3 === 'string' || typeof b3 === 'undefined') {
            return b3;
        }
        else {
            let c3 = '';
            try {
                c3 = getContext()?.resourceManager?.getStringSync(b3);
            }
            catch (d3) {
                let e3 = d3?.code;
                let f3 = d3?.message;
                hilog.error(0x3900, 'Ace', `Faild to subHeader toStringFormat, code: ${e3}, message: ${f3}`);
            }
            return c3;
        }
    }
    getRightIconAccessibilityDescription() {
        if (this.item?.accessibilityDescription && this.item?.accessibilityDescription !== '') {
            return this.toStringFormat(this.item?.accessibilityDescription);
        }
        return '';
    }
    initialRender() {
        this.observeComponentCreation2((o2, p2) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t2, u2) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(true);
                        Button.width(SINGLE_ICON_ZONE_SIZE);
                        Button.height(SINGLE_ICON_ZONE_SIZE);
                        Button.align(Alignment.Center);
                        Button.backgroundColor(this.bgColor);
                        Button.borderRadius(getResourceValue('sys.float.corner_radius_level4'));
                        Button.accessibilityLevel(this.getRightIconAccessibilityLevel());
                        Button.accessibilityText(this.getRightIconAccessibilityText());
                        Button.accessibilityDescription(this.getRightIconAccessibilityDescription());
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        ViewStackProcessor.visualState("pressed");
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("disabled");
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                        Button.onTouch((a3) => {
                            if (a3.type === TouchType.Down || TouchType.Cancel) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            if (a3.type === TouchType.Up) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Button.onHover((z2) => {
                            if (z2) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            else {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Button.responseRegion(this.iconResponseRegion());
                        Button.onClick((y2) => {
                            if (this.item?.action) {
                                this.item?.action();
                            }
                        });
                    }, Button);
                    this.IconZone.bind(this)(this);
                    Button.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    iconResponseRegion() {
        if (this.isSingleIcon) {
            return {
                x: SINGLE_ICON_REGION_X,
                y: ICON_REGION_Y,
                width: MIN_HOT_AREA_LENGTH,
                height: MIN_HOT_AREA_LENGTH,
            };
        }
        return {
            x: ICON_REGION_X,
            y: ICON_REGION_Y,
            width: MULTI_ICON_REGION_WIDTH,
            height: MIN_HOT_AREA_LENGTH,
        };
    }
    IconZone(w1 = null) {
        this.observeComponentCreation2((y1, z1) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d2, e2) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((l2, m2) => {
                                    SymbolGlyph.create(this.item.iconOptions);
                                    SymbolGlyph.fontSize(RIGHT_SINGLE_ICON_SIZE);
                                    SymbolGlyph.fontColor([this.subHeaderTheme.rightIconColor]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.item.iconOptions);
                                    SymbolGlyph.focusable(true);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((h2, i2) => {
                                    Image.create(this.item?.iconOptions);
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
    updateStateVars(v1) {
        if (v1 === undefined) {
            return;
        }
        if ("item" in v1) {
            this.updateParam("item", v1.item);
        }
        if ("isSingleIcon" in v1) {
            this.updateParam("isSingleIcon", v1.isSingleIcon);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Local
], SingleIconStyle.prototype, "bgColor", void 0);
__decorate([
    Local
], SingleIconStyle.prototype, "isFocus", void 0);
__decorate([
    Param
], SingleIconStyle.prototype, "item", void 0);
__decorate([
    Consumer('subHeaderV2Theme')
], SingleIconStyle.prototype, "subHeaderTheme", void 0);
__decorate([
    Param
], SingleIconStyle.prototype, "isSingleIcon", void 0);
class Util {
    static isSymbolResource(t1) {
        if (!Util.isResourceType(t1)) {
            return false;
        }
        if (t1 instanceof SymbolGlyphModifier) {
            return t1 instanceof SymbolGlyphModifier;
        }
        let u1 = t1;
        return u1.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(s1) {
        if (!s1) {
            return false;
        }
        if (typeof s1 === 'string' || typeof s1 === 'undefined') {
            return false;
        }
        return true;
    }
    static getNumberByResource(m1, n1) {
        try {
            let r1 = resourceManager.getSystemResourceManager().getNumber(m1);
            if (r1 === 0) {
                return n1;
            }
            else {
                return r1;
            }
        }
        catch (o1) {
            let p1 = o1.code;
            let q1 = o1.message;
            hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${p1}, message: ${q1}`);
            return 0;
        }
    }
    static getStringByResource(g1, h1) {
        try {
            let l1 = getContext().resourceManager.getStringSync(g1);
            if (l1 === '') {
                return h1;
            }
            else {
                return l1;
            }
        }
        catch (i1) {
            let j1 = i1.code;
            let k1 = i1.message;
            hilog.error(0x3900, 'Ace', `SubHeader getStringByResource error, code: ${j1}, message: ${k1}`);
            return '';
        }
    }
    static numberToSize(e1) {
        if (typeof e1 === 'string') {
            const f1 = parseInt(e1);
            return f1;
        }
        else if (typeof e1 === 'number') {
            return e1;
        }
        else {
            return getContext().resourceManager.getNumber(e1);
        }
    }
    static symbolFontSize(d1) {
        return Util.numberToSize(d1) + 'vp';
    }
}
const RESOURCE_CACHE_MAP = new HashMap();
RESOURCE_CACHE_MAP.set('sys.float.padding_level0', { resourceId: 125830919, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.padding_level1', { resourceId: 125830920, defaultValue: 2 });
RESOURCE_CACHE_MAP.set('sys.float.padding_level2', { resourceId: 125830921, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.padding_level3', { resourceId: 125830922, defaultValue: 6 });
RESOURCE_CACHE_MAP.set('sys.float.padding_level4', { resourceId: 125830923, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.padding_level6', { resourceId: 125830925, defaultValue: 12 });
RESOURCE_CACHE_MAP.set('sys.float.padding_level8', { resourceId: 125830927, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.margin_left', { resourceId: 125830936, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.margin_right', { resourceId: 125830937, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.outline_extra_larger', { resourceId: 125830951, defaultValue: 2 });
RESOURCE_CACHE_MAP.set('sys.float.corner_radius_level4', { resourceId: 125830909, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.Subtitle_S', { resourceId: 125830969, defaultValue: 14 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_title_font_size', { resourceId: 125834265, defaultValue: 18 });
RESOURCE_CACHE_MAP.set('sys.float.Body_L', { resourceId: 125830970, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.interactive_disable', { resourceId: 125831067, defaultValue: 0.4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_title_height', { resourceId: 125834252, defaultValue: 56 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_subtitle_height', { resourceId: 125834253, defaultValue: 56 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_double_height', { resourceId: 125834254, defaultValue: 72 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_title_font_weight', { resourceId: 125834255, defaultValue: 700 });
function getResourceValue(b1) {
    if (RESOURCE_CACHE_MAP.hasKey(b1)) {
        let c1 = RESOURCE_CACHE_MAP.get(b1).resourceValue;
        if (typeof c1 === 'number') {
            return c1;
        }
        else {
            c1 = Util.getNumberByResource(RESOURCE_CACHE_MAP.get(b1).resourceId, RESOURCE_CACHE_MAP.get(b1).defaultValue);
            RESOURCE_CACHE_MAP.get(b1).resourceValue = c1;
            return c1;
        }
    }
    return 0;
}
class TextArrowLayout extends ViewPU {
    constructor(v, w, x, y = -1, z = undefined, a1) {
        super(v, x, y, a1);
        if (typeof z === "function") {
            this.paramsGenerator_ = z;
        }
        this.textArrowBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(w);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(u) {
        if (u.textArrowBuilder !== undefined) {
            this.textArrowBuilder = u.textArrowBuilder;
        }
    }
    updateStateVars(t) {
    }
    purgeVariableDependenciesOnElmtId(s) {
    }
    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    doNothingBuilder(r = null) {
    }
    onPlaceChildren(k, l, m) {
        let n = 0;
        let o = 0;
        for (let p = 0; p < l.length; p++) {
            let q = l[p];
            q.layout({ x: n, y: o });
        }
    }
    onMeasureSize(a, b, c) {
        let d = ARROW_ICON_WIDTH;
        let e = OPERATE_ITEM_LENGTH;
        let f = b[INDEX_ZERO];
        let g = {
            minWidth: Math.max(d, Number(c.minWidth)),
            maxWidth: c.maxWidth,
            minHeight: Math.max(e, Number(c.minHeight)),
            maxHeight: c.maxHeight,
        };
        let h = f.measure(g);
        d = Math.max(d, h.width);
        e = Math.max(e, h.height);
        let i = b[INDEX_ONE];
        let j = {
            minWidth: d,
            maxWidth: d,
            minHeight: e,
            maxHeight: e,
        };
        i.measure(j);
        return { width: d, height: e };
    }
    initialRender() {
        this.textArrowBuilder.bind(this)(this);
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    SubHeaderV2Title, SubHeaderV2Select,
    SubHeaderV2, SubHeaderV2OperationType, SubHeaderV2OperationItem
};