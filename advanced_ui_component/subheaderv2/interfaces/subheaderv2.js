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

var __decorate = (this && this.__decorate) || function (n10, o10, p10, q10) {
    var r10 = arguments.length, s10 = r10 < 3 ? o10 : q10 === null ? q10 = Object.getOwnPropertyDescriptor(o10, p10) : q10, t10;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        s10 = Reflect.decorate(n10, o10, p10, q10);
    else
        for (var u10 = n10.length - 1; u10 >= 0; u10--)
            if (t10 = n10[u10])
                s10 = (r10 < 3 ? t10(s10) : r10 > 3 ? t10(o10, p10, s10) : t10(o10, p10)) || s10;
    return r10 > 3 && s10 && Object.defineProperty(o10, p10, s10), s10;
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
    constructor(m10) {
        this.primaryTitle = m10.primaryTitle;
        this.primaryTitleModifier = m10.primaryTitleModifier;
        this.secondaryTitle = m10.secondaryTitle;
        this.secondaryTitleModifier = m10.secondaryTitleModifier;
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
    constructor(l10) {
        this.options = l10.options;
        this.selectedIndex = l10.selectedIndex;
        this.selectedContent = l10.selectedContent;
        this.onSelect = l10.onSelect;
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
(function (k10) {
    k10[k10["TEXT_ARROW"] = 0] = "TEXT_ARROW";
    k10[k10["BUTTON"] = 1] = "BUTTON";
    k10[k10["ICON_GROUP"] = 2] = "ICON_GROUP";
    k10[k10["LOADING"] = 3] = "LOADING";
})(SubHeaderV2OperationType || (SubHeaderV2OperationType = {}));
let SubHeaderV2OperationItem = class SubHeaderV2OperationItem {
    constructor(j10) {
        this.content = j10.content;
        this.action = j10.action;
        this.accessibilityText = j10.accessibilityText;
        this.accessibilityDescription = j10.accessibilityDescription;
        this.accessibilityLevel = j10.accessibilityLevel;
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
function __Text__secondaryTitleStyles(i10) {
    Text.fontSize(`${getResourceValue('sys.float.Subtitle_S')}fp`);
    Text.fontColor(i10?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(i10?.fontWeight);
    Text.maxLines(i10?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(i10?.alignment);
}
function __Text__primaryTitleStyles(h10) {
    Text.fontSize(`${getResourceValue('sys.float.subheader_title_font_size')}fp`);
    Text.fontColor(h10?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(h10?.fontWeight);
    Text.maxLines(h10?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(h10?.alignment);
}
class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }
    applyNormalAttribute(g10) {
        if (this.isAgeing) {
            g10.width('100%');
        }
        else {
        }
    }
}
export class SubHeaderV2 extends ViewV2 {
    constructor(a10, b10, c10, d10 = -1, e10, f10) {
        super(a10, d10, f10);
        this.initParam("icon", (b10 && "icon" in b10) ? b10.icon : undefined);
        this.initParam("title", (b10 && "title" in b10) ? b10.title : undefined);
        this.initParam("select", (b10 && "select" in b10) ? b10.select : undefined);
        this.initParam("operationType", (b10 && "operationType" in b10) ? b10.operationType : SubHeaderV2OperationType.BUTTON);
        this.initParam("operationItems", (b10 && "operationItems" in b10) ? b10.operationItems : undefined);
        this.titleBuilder = "titleBuilder" in b10 ? b10.titleBuilder : undefined;
        this.fontSize = 1;
        this.ageing = true;
        this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.selectedIndex = -1;
        this.selectedContent = '';
        this.symbolWidth = LEFT_ICON_SIZE_NUMBER + LEFT_TEXT_NUMBER;
        this.subHeaderModifier = new SubHeaderModifier();
        this.isFollowingSystemFontScale = false;
        this.appMaxFontScale = 3.2;
        this.subHeaderV2Theme = new SubHeaderTheme();
        this.subHeaderMargin = {
            start: LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
            end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
        };
        this.finalizeConstruction();
    }
    onWillApplyTheme(z9) {
        this.subHeaderV2Theme.fontPrimaryColor = z9.colors.fontPrimary;
        this.subHeaderV2Theme.fontSecondaryColor = z9.colors.fontSecondary;
        this.subHeaderV2Theme.fontButtonColor = z9.colors.fontEmphasize;
        this.subHeaderV2Theme.iconArrowColor = z9.colors.iconTertiary;
        this.subHeaderV2Theme.textArrowHoverBgColor = z9.colors.interactiveHover;
        this.subHeaderV2Theme.borderFocusColor = z9.colors.interactiveFocus;
        this.subHeaderV2Theme.leftIconColor = z9.colors.iconSecondary;
        this.subHeaderV2Theme.rightIconColor = z9.colors.iconPrimary;
    }
    async aboutToAppear() {
        let y9 = this.getUIContext();
        this.isFollowingSystemFontScale = y9.isFollowingSystemFontScale();
        this.appMaxFontScale = y9.getMaxFontScale();
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
            let w9 = this.getUIContext();
            let x9 = w9.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(x9, this.appMaxFontScale);
        }
        catch (t9) {
            let u9 = t9.code;
            let v9 = t9.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${u9}, message: ${v9}`);
            return 1;
        }
    }
    IconSecondaryTitleStyle(d9, e9 = null) {
        this.observeComponentCreation2((r9, s9) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
            });
        }, Flex);
        this.observeComponentCreation2((h9, i9) => {
            If.create();
            if (Util.isSymbolResource(d9.iconOptions)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((l9, m9) => {
                            if (m9) {
                                let n9 = new SymbolGlyphChild(this, {
                                    icon: d9.iconOptions,
                                    fontColor: [this.subHeaderV2Theme.leftIconColor],
                                    changeSymbolWidth: (q9) => {
                                        this.symbolWidth = q9.width;
                                    }
                                }, undefined, l9, () => { }, { page: "library/src/main/ets/components/subheaderv2.ets", line: 300, col: 9 });
                                ViewV2.create(n9);
                                let o9 = () => {
                                    return {
                                        icon: d9.iconOptions,
                                        fontColor: [this.subHeaderV2Theme.leftIconColor],
                                        changeSymbolWidth: (p9) => {
                                            this.symbolWidth = p9.width;
                                        }
                                    };
                                };
                                n9.paramsGenerator_ = o9;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(l9, {
                                    icon: d9.iconOptions,
                                    fontColor: [this.subHeaderV2Theme.leftIconColor]
                                });
                            }
                        }, { name: "SymbolGlyphChild" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((j9, k9) => {
                        Image.create(d9.iconOptions);
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
        this.observeComponentCreation2((f9, g9) => {
            Text.create(d9.content);
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
    SelectStyle(x8, y8 = null) {
        this.observeComponentCreation2((z8, a9) => {
            Select.create(x8.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(this.selectedIndex);
            Select.value(this.selectedContent);
            Select.onSelect((b9, c9) => {
                this.selectedIndex = b9;
                if (c9) {
                    this.selectedContent = c9;
                }
                if (x8.onSelect) {
                    x8.onSelect(b9, c9);
                }
            });
            Select.font({
                size: `${getResourceValue('sys.float.Body_L')}fp`,
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
    }
    SubTitleStyle(p8, q8 = null) {
        this.observeComponentCreation2((v8, w8) => {
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
        this.observeComponentCreation2((t8, u8) => {
            Text.create(p8.content);
            __Text__primaryTitleStyles({
                fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderV2Theme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(this.title?.primaryTitleModifier);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((r8, s8) => {
            Text.create(p8.subContent);
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
    SecondTitleStyle(l8, m8 = null) {
        this.observeComponentCreation2((n8, o8) => {
            Text.create(l8.content);
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
    PrimaryTitleStyle(h8, i8 = null) {
        this.observeComponentCreation2((j8, k8) => {
            Text.create(h8.content);
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
    leftArea(e8 = null) {
        this.observeComponentCreation2((f8, g8) => {
            If.create();
            if (this.titleBuilder) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.titleBuilder.bind(this)();
                });
            }
            else if (this.title?.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy("IconSecondaryTitleStyle", { content: () => this.title?.secondaryTitle, iconOptions: () => (this["__icon"] ? this["__icon"] : this["icon"]) }));
                });
            }
            else if (this.title?.secondaryTitle && this.title?.primaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy("SubTitleStyle", { content: () => this.title?.primaryTitle, subContent: () => this.title?.secondaryTitle }));
                });
            }
            else if (this.title?.secondaryTitle) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy("SecondTitleStyle", { content: () => this.title?.secondaryTitle }));
                });
            }
            else if (this.select) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.SelectStyle.bind(this)(this.select);
                });
            }
            else if (this.title?.primaryTitle) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy("PrimaryTitleStyle", { content: () => this.title?.primaryTitle }));
                });
            }
            else {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.dummyFunction.bind(this)();
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
    getRightAreaAccessibilityText() {
        if (this.operationType !== SubHeaderV2OperationType.TEXT_ARROW || !this.operationItems || this.operationItems.length <= 0) {
            return '';
        }
        if (this.operationItems
            && this.operationItems[0]?.content?.toString().length
            && this.operationItems[0]?.content?.toString().length <= 0) {
            return Util.getStringByResource(125833704, '');
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
    ButtonStyle(v7, w7 = null) {
        this.observeComponentCreation2((x7, y7) => {
            If.create();
            if (v7) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b8, c8) => {
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
                        Button.onHover((d8) => {
                            if (d8) {
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
                    this.observeComponentCreation2((z7, a8) => {
                        Text.create(v7.content);
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
    TextStyle(n7, o7 = null) {
        this.observeComponentCreation2((t7, u7) => {
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
        this.observeComponentCreation2((p7, q7) => {
            If.create();
            if (n7) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r7, s7) => {
                        Text.create(n7.content);
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
    ArrowStyle(i7 = null) {
        this.observeComponentCreation2((l7, m7) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((j7, k7) => {
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
    TextArrowStyle(a6, b6 = null) {
        this.observeComponentCreation2((c6, d6) => {
            If.create();
            if (a6 && a6.content && a6.content.toString().length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g7, h7) => {
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
                    this.observeComponentCreation2((d7, e7) => {
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
                        Button.onHover((f7) => {
                            if (f7) {
                                this.textArrowBgColor = this.subHeaderV2Theme.textArrowHoverBgColor;
                            }
                            else {
                                this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                    }, Button);
                    {
                        this.observeComponentCreation2((l6, m6) => {
                            if (m6) {
                                let n6 = new TextArrowLayout(this, {
                                    textArrowBuilder: () => {
                                        this.observeComponentCreation2((w6, x6) => {
                                            ForEach.create();
                                            const y6 = z6 => {
                                                const a7 = z6;
                                                this.observeComponentCreation2((b7, c7) => {
                                                    If.create();
                                                    if (a7 === INDEX_ZERO) {
                                                        this.ifElseBranchUpdateFunction(0, () => {
                                                            this.TextStyle.bind(this)(a6);
                                                        });
                                                    }
                                                    else {
                                                        this.ifElseBranchUpdateFunction(1, () => {
                                                            this.ArrowStyle.bind(this)();
                                                        });
                                                    }
                                                }, If);
                                                If.pop();
                                            };
                                            this.forEachUpdateFunction(w6, [INDEX_ZERO, INDEX_ONE], y6);
                                        }, ForEach);
                                        ForEach.pop();
                                    }
                                }, undefined, l6, () => { }, { page: "library/src/main/ets/components/subheaderv2.ets", line: 668, col: 11 });
                                ViewPU.create(n6);
                                let o6 = () => {
                                    return {
                                        textArrowBuilder: () => {
                                            this.observeComponentCreation2((p6, q6) => {
                                                ForEach.create();
                                                const r6 = s6 => {
                                                    const t6 = s6;
                                                    this.observeComponentCreation2((u6, v6) => {
                                                        If.create();
                                                        if (t6 === INDEX_ZERO) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.TextStyle.bind(this)(a6);
                                                            });
                                                        }
                                                        else {
                                                            this.ifElseBranchUpdateFunction(1, () => {
                                                                this.ArrowStyle.bind(this)();
                                                            });
                                                        }
                                                    }, If);
                                                    If.pop();
                                                };
                                                this.forEachUpdateFunction(p6, [INDEX_ZERO, INDEX_ONE], r6);
                                            }, ForEach);
                                            ForEach.pop();
                                        }
                                    };
                                };
                                n6.paramsGenerator_ = o6;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(l6, {});
                            }
                        }, { name: "TextArrowLayout" });
                    }
                    Button.pop();
                    Stack.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((j6, k6) => {
                        Row.create();
                        Row.focusable(true);
                        Row.constraintSize({ minWidth: this.getRightAreaMinWidth() });
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((g6, h6) => {
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
                        Button.onHover((i6) => {
                            if (i6) {
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
                    this.observeComponentCreation2((e6, f6) => {
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
    IconGroupStyle(g5, h5 = null) {
        this.observeComponentCreation2((y5, z5) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((i5, j5) => {
            ForEach.create();
            const k5 = (l5, m5) => {
                const n5 = l5;
                this.observeComponentCreation2((o5, p5) => {
                    If.create();
                    if (Util.isResourceType(n5.content)) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((q5, r5) => {
                                If.create();
                                if (m5 <= INDEX_TWO) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((w5, x5) => {
                                            __Common__.create();
                                            __Common__.margin({
                                                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                                                bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level3')),
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((s5, t5) => {
                                                if (t5) {
                                                    let u5 = new SingleIconStyle(this, {
                                                        item: {
                                                            iconOptions: n5.content,
                                                            action: n5.action,
                                                        },
                                                        isSingleIcon: this.operationItems?.length === SINGLE_ICON_NUMBER,
                                                    }, undefined, s5, () => { }, { page: "library/src/main/ets/components/subheaderv2.ets", line: 758, col: 13 });
                                                    ViewV2.create(u5);
                                                    let v5 = () => {
                                                        return {
                                                            item: {
                                                                iconOptions: n5.content,
                                                                action: n5.action,
                                                            },
                                                            isSingleIcon: this.operationItems?.length === SINGLE_ICON_NUMBER
                                                        };
                                                    };
                                                    u5.paramsGenerator_ = v5;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(s5, {
                                                        item: {
                                                            iconOptions: n5.content,
                                                            action: n5.action,
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
            this.forEachUpdateFunction(i5, g5, k5, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rightArea(x4 = null) {
        this.observeComponentCreation2((e5, f5) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON && (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)(this.operationItems[0]);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((c5, d5) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW && (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextArrowStyle.bind(this)(this.operationItems[0]);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((a5, b5) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.ICON_GROUP && (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconGroupStyle.bind(this)(this.operationItems);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((y4, z4) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.LOADING) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.LoadingProcessStyle.bind(this)();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    rightAreaParent(o4 = null) {
        this.observeComponentCreation2((p4, q4) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON || this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u4, v4) => {
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
                        Button.onTouch((w4) => {
                            if (w4.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (w4.type === TouchType.Up || w4.type === TouchType.Cancel) {
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
                            'yes' : 'no');
                        Button.hoverEffect(HoverEffect.None);
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                    }, Button);
                    this.rightArea.bind(this)();
                    Button.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((r4, s4) => {
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
                        Row.onTouch((t4) => {
                            if (t4.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (t4.type === TouchType.Up || t4.type === TouchType.Cancel) {
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
                            'yes' : 'no');
                    }, Row);
                    this.rightArea.bind(this)();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }
    rightAreaParentAging(f4 = null) {
        this.observeComponentCreation2((g4, h4) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON || this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l4, m4) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItems ? true : false);
                        Button.align(Alignment.Start);
                        Button.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW || this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Button.onTouch((n4) => {
                            if (n4.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (n4.type === TouchType.Up || n4.type === TouchType.Cancel) {
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
                            this.operationType === SubHeaderV2OperationType.TEXT_ARROW ? 'yes' : 'no');
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.hoverEffect(HoverEffect.None);
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                    }, Button);
                    this.rightArea.bind(this)();
                    Button.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((i4, j4) => {
                        Row.create();
                        Row.focusable(this.operationItems && this.operationType !== SubHeaderV2OperationType.LOADING ? true : false);
                        Row.justifyContent(FlexAlign.Start);
                        Row.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW || this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Row.onTouch((k4) => {
                            if (k4.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (k4.type === TouchType.Up || k4.type === TouchType.Cancel) {
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
                            this.operationType === SubHeaderV2OperationType.TEXT_ARROW ? 'yes' : 'no');
                    }, Row);
                    this.rightArea.bind(this)();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
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
        let e4 = {};
        if (!this.titleBuilder && ((this.title?.secondaryTitle && this.icon) ||
            (!this.title?.primaryTitle && this.title?.secondaryTitle))) {
            e4 = {
                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
            };
        }
        else if (this.select) {
            e4 = {
                top: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
                bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
            };
        }
        return e4;
    }
    initialRender() {
        this.observeComponentCreation2((q3, r3) => {
            If.create();
            if (this.isSuitableAging()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c4, d4) => {
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.padding(this.getAreaPadding());
                        Column.alignItems(HorizontalAlign.Start);
                    }, Column);
                    this.observeComponentCreation2((a4, b4) => {
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
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((y3, z3) => {
                        If.create();
                        if (this.isRightAreaExists()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.rightAreaParentAging.bind(this)();
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
                    this.observeComponentCreation2((w3, x3) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((u3, v3) => {
                        Row.create();
                        Row.margin({
                            top: this.fontSize >= MIN_FONT_SIZE ? getResourceValue('sys.float.padding_level8') : '',
                            bottom: this.fontSize >= MIN_FONT_SIZE ? getResourceValue('sys.float.padding_level4') : '',
                        });
                        Row.width('100%');
                        Row.flexShrink(1);
                        Row.accessibilityGroup(this.isLeftAreaAccessibilityGroup());
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((s3, t3) => {
                        If.create();
                        if (this.isRightAreaExists()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.rightAreaParent.bind(this)();
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
    LoadingProcessStyle(l3 = null) {
        this.observeComponentCreation2((o3, p3) => {
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
        this.observeComponentCreation2((m3, n3) => {
            LoadingProgress.create();
            LoadingProgress.width(OPERATE_ITEM_LENGTH);
            LoadingProgress.height(OPERATE_ITEM_LENGTH);
            LoadingProgress.color({ "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, LoadingProgress);
        Row.pop();
    }
    dummyFunction(i3 = null) {
        this.observeComponentCreation2((j3, k3) => {
            Row.create();
        }, Row);
        Row.pop();
    }
    updateStateVars(h3) {
        if (h3 === undefined) {
            return;
        }
        if ("icon" in h3) {
            this.updateParam("icon", h3.icon);
        }
        if ("title" in h3) {
            this.updateParam("title", h3.title);
        }
        if ("select" in h3) {
            this.updateParam("select", h3.select);
        }
        if ("operationType" in h3) {
            this.updateParam("operationType", h3.operationType);
        }
        if ("operationItems" in h3) {
            this.updateParam("operationItems", h3.operationItems);
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
    constructor(b3, c3, d3, e3 = -1, f3, g3) {
        super(b3, e3, g3);
        this.initParam("icon", (c3 && "icon" in c3) ? c3.icon : undefined);
        this.initParam("fontColor", (c3 && "fontColor" in c3) ? c3.fontColor : undefined);
        this.changeSymbolWidth = "changeSymbolWidth" in c3 ? c3.changeSymbolWidth : () => { };
        this.result = {
            width: 0,
            height: 0
        };
        this.finalizeConstruction();
    }
    onMeasureSize(x2, y2, z2) {
        y2.forEach((a3) => {
            this.result = a3.measure(z2);
        });
        console.log(`zzzz Child onMeasureSize ${JSON.stringify(this.result)}`);
        this.changeSymbolWidth(this.result);
        return this.result;
    }
    initialRender() {
        this.observeComponentCreation2((v2, w2) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((t2, u2) => {
            SymbolGlyph.create(this.icon);
            SymbolGlyph.fontSize(LEFT_ICON_SIZE);
            SymbolGlyph.fontColor(this.fontColor);
            SymbolGlyph.attributeModifier.bind(this)(this.icon);
            SymbolGlyph.margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) });
            SymbolGlyph.flexShrink(0);
        }, SymbolGlyph);
        Column.pop();
    }
    updateStateVars(s2) {
        if (s2 === undefined) {
            return;
        }
        if ("icon" in s2) {
            this.updateParam("icon", s2.icon);
        }
        if ("fontColor" in s2) {
            this.updateParam("fontColor", s2.fontColor);
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
    constructor(m2, n2, o2, p2 = -1, q2, r2) {
        super(m2, p2, r2);
        this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.isFocus = false;
        this.initParam("item", (n2 && "item" in n2) ? n2.item : null);
        this.subHeaderTheme = new SubHeaderTheme();
        this.initParam("isSingleIcon", (n2 && "isSingleIcon" in n2) ? n2.isSingleIcon : true);
        this.finalizeConstruction();
    }
    initialRender() {
        this.observeComponentCreation2((f2, g2) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h2, i2) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(true);
                        Button.width(SINGLE_ICON_ZONE_SIZE);
                        Button.height(SINGLE_ICON_ZONE_SIZE);
                        Button.align(Alignment.Center);
                        Button.backgroundColor(this.bgColor);
                        Button.borderRadius(getResourceValue('sys.float.corner_radius_level4'));
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
                        Button.onTouch((l2) => {
                            if (l2.type === TouchType.Down || TouchType.Cancel) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            if (l2.type === TouchType.Up) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Button.onHover((k2) => {
                            if (k2) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            else {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Button.responseRegion(this.iconResponseRegion());
                        Button.onClick((j2) => {
                            if (this.item?.action) {
                                this.item?.action();
                            }
                        });
                    }, Button);
                    this.IconZone.bind(this)();
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
        this.observeComponentCreation2((x1, y1) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z1, a2) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((d2, e2) => {
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
                                this.observeComponentCreation2((b2, c2) => {
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
        this.textArrowBuilder.bind(this)();
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    SubHeaderV2Title, SubHeaderV2Select,
    SubHeaderV2, SubHeaderV2OperationType, SubHeaderV2OperationItem
};