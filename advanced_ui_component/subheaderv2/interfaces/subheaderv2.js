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

var __decorate = (this && this.__decorate) || function (c28, d28, e28, f28) {
    var g28 = arguments.length, h28 = g28 < 3 ? d28 : f28 === null ? f28 = Object.getOwnPropertyDescriptor(d28, e28) : f28, i28;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        h28 = Reflect.decorate(c28, d28, e28, f28);
    else
        for (var j28 = c28.length - 1; j28 >= 0; j28--)
            if (i28 = c28[j28])
                h28 = (g28 < 3 ? i28(h28) : g28 > 3 ? i28(d28, e28, h28) : i28(d28, e28)) || h28;
    return g28 > 3 && h28 && Object.defineProperty(d28, e28, h28), h28;
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
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;

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
    constructor(a28) {
        this.primaryTitle = a28.primaryTitle;
        this.primaryTitleModifier = a28.primaryTitleModifier;
        this.secondaryTitle = a28.secondaryTitle;
        this.secondaryTitleModifier = a28.secondaryTitleModifier;
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
    constructor(z27) {
        this.options = z27.options;
        this.selectedIndex = z27.selectedIndex;
        this.selectedContent = z27.selectedContent;
        this.onSelect = z27.onSelect;
        this.defaultFocus = z27.defaultFocus;
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
__decorate([
    Trace
], SubHeaderV2Select.prototype, "defaultFocus", void 0);
SubHeaderV2Select = __decorate([
    ObservedV2
], SubHeaderV2Select);
export { SubHeaderV2Select };
export var SubHeaderV2OperationType;
(function (y27) {
    y27[y27["TEXT_ARROW"] = 0] = "TEXT_ARROW";
    y27[y27["BUTTON"] = 1] = "BUTTON";
    y27[y27["ICON_GROUP"] = 2] = "ICON_GROUP";
    y27[y27["LOADING"] = 3] = "LOADING";
})(SubHeaderV2OperationType || (SubHeaderV2OperationType = {}));
let SubHeaderV2OperationItem = class SubHeaderV2OperationItem {
    constructor(x27) {
        this.content = x27.content;
        this.action = x27.action;
        this.accessibilityText = x27.accessibilityText;
        this.accessibilityDescription = x27.accessibilityDescription;
        this.accessibilityLevel = x27.accessibilityLevel;
        this.defaultFocus = x27.defaultFocus;
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
__decorate([
    Trace
], SubHeaderV2OperationItem.prototype, "defaultFocus", void 0);
SubHeaderV2OperationItem = __decorate([
    ObservedV2
], SubHeaderV2OperationItem);
export { SubHeaderV2OperationItem };
let ContentIconOption = class ContentIconOption {
};
__decorate([
    Trace
], ContentIconOption.prototype, "content", void 0);
__decorate([
    Trace
], ContentIconOption.prototype, "subContent", void 0);
__decorate([
    Trace
], ContentIconOption.prototype, "iconOptions", void 0);
__decorate([
    Trace
], ContentIconOption.prototype, "action", void 0);
__decorate([
    Trace
], ContentIconOption.prototype, "accessibilityLevel", void 0);
__decorate([
    Trace
], ContentIconOption.prototype, "accessibilityText", void 0);
__decorate([
    Trace
], ContentIconOption.prototype, "accessibilityDescription", void 0);
__decorate([
    Trace
], ContentIconOption.prototype, "defaultFocus", void 0);
ContentIconOption = __decorate([
    ObservedV2
], ContentIconOption);
let FontStyle = class FontStyle {
    constructor() {
        this.maxLines = 0;
        this.fontWeight = 0;
    }
};
__decorate([
    Trace
], FontStyle.prototype, "maxLines", void 0);
__decorate([
    Trace
], FontStyle.prototype, "fontWeight", void 0);
__decorate([
    Trace
], FontStyle.prototype, "fontColor", void 0);
__decorate([
    Trace
], FontStyle.prototype, "alignment", void 0);
FontStyle = __decorate([
    ObservedV2
], FontStyle);
let SubHeaderTheme = class SubHeaderTheme {
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
};
__decorate([
    Trace
], SubHeaderTheme.prototype, "fontPrimaryColor", void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, "fontSecondaryColor", void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, "fontButtonColor", void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, "iconArrowColor", void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, "textArrowHoverBgColor", void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, "borderFocusColor", void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, "leftIconColor", void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, "rightIconColor", void 0);
SubHeaderTheme = __decorate([
    ObservedV2
], SubHeaderTheme);
function __Text__secondaryTitleStyles(k16) {
    Text.fontSize(`${getResourceValue('sys.float.Subtitle_S')}fp`);
    Text.fontColor(k16?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(k16?.fontWeight);
    Text.maxLines(k16?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(k16?.alignment);
}
function __Text__primaryTitleStyles(j16) {
    Text.fontSize(`${getResourceValue('sys.float.subheader_title_font_size')}fp`);
    Text.fontColor(j16?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(j16?.fontWeight);
    Text.maxLines(j16?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(j16?.alignment);
}
class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }
    applyNormalAttribute(i16) {
        if (this.isAgeing) {
            i16.width('100%');
        }
        else {
        }
    }
}
export class SubHeaderV2 extends ViewV2 {
    constructor(r27, s27, t27, u27 = -1, v27, w27) {
        super(r27, u27, w27);
        this.initParam("icon", (s27 && "icon" in s27) ? s27.icon : undefined);
        this.initParam("title", (s27 && "title" in s27) ? s27.title : undefined);
        this.initParam("select", (s27 && "select" in s27) ? s27.select : undefined);
        this.initParam("operationType", (s27 && "operationType" in s27) ? s27.operationType : SubHeaderV2OperationType.BUTTON);
        this.initParam("operationItems", (s27 && "operationItems" in s27) ? s27.operationItems : undefined);
        this.titleBuilder = "titleBuilder" in s27 ? s27.titleBuilder : undefined;
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
    onWillApplyTheme(q27) {
        this.subHeaderV2Theme.fontPrimaryColor = q27.colors.fontPrimary;
        this.subHeaderV2Theme.fontSecondaryColor = q27.colors.fontSecondary;
        this.subHeaderV2Theme.fontButtonColor = q27.colors.fontEmphasize;
        this.subHeaderV2Theme.iconArrowColor = q27.colors.iconTertiary;
        this.subHeaderV2Theme.textArrowHoverBgColor = q27.colors.interactiveHover;
        this.subHeaderV2Theme.borderFocusColor = q27.colors.interactiveFocus;
        this.subHeaderV2Theme.leftIconColor = q27.colors.iconSecondary;
        this.subHeaderV2Theme.rightIconColor = q27.colors.iconPrimary;
    }
    async aboutToAppear() {
        let p27 = this.getUIContext();
        this.isFollowingSystemFontScale = p27.isFollowingSystemFontScale();
        this.appMaxFontScale = p27.getMaxFontScale();
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
            let n27 = this.getUIContext();
            let o27 = n27.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(o27, this.appMaxFontScale);
        }
        catch (k27) {
            let l27 = k27.code;
            let m27 = k27.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${l27}, message: ${m27}`);
            return 1;
        }
    }
    IconSecondaryTitleStyle(l26, m26 = null) {
        this.observeComponentCreation2((i27, j27) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
            });
        }, Flex);
        this.observeComponentCreation2((s26, t26) => {
            If.create();
            if (Util.isSymbolResource(l26.iconOptions)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((a27, b27) => {
                            if (b27) {
                                let c27 = new SymbolGlyphChild(this, {
                                    icon: l26.iconOptions,
                                    fontColor: [this.subHeaderV2Theme.leftIconColor],
                                    changeSymbolWidth: (h27) => {
                                        this.symbolWidth = h27.width;
                                    }
                                }, undefined, a27, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 331, col: 9 });
                                ViewV2.create(c27);
                                let d27 = () => {
                                    return {
                                        icon: l26.iconOptions,
                                        fontColor: [this.subHeaderV2Theme.leftIconColor],
                                        changeSymbolWidth: (g27) => {
                                            this.symbolWidth = g27.width;
                                        }
                                    };
                                };
                                c27.paramsGenerator_ = d27;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(a27, {
                                    icon: l26.iconOptions,
                                    fontColor: [this.subHeaderV2Theme.leftIconColor]
                                });
                            }
                        }, { name: "SymbolGlyphChild" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((w26, x26) => {
                        Image.create(l26.iconOptions);
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
        this.observeComponentCreation2((q26, r26) => {
            Text.create(l26.content);
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
    SelectStyle(d26, e26 = null) {
        this.observeComponentCreation2((g26, h26) => {
            Select.create(d26.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(this.selectedIndex);
            Select.value(this.selectedContent);
            Select.defaultFocus(this.select?.defaultFocus);
            Select.onSelect((j26, k26) => {
                this.selectedIndex = j26;
                if (k26) {
                    this.selectedContent = k26;
                }
                if (d26.onSelect) {
                    d26.onSelect(j26, k26);
                }
            });
            Select.font({
                size: `${getResourceValue('sys.float.Body_L')}fp`,
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
    }
    SubTitleStyle(s25, t25 = null) {
        this.observeComponentCreation2((b26, c26) => {
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
        this.observeComponentCreation2((z25, a26) => {
            Text.create(s25.content);
            __Text__primaryTitleStyles({
                fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderV2Theme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(this.title?.primaryTitleModifier);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((x25, y25) => {
            Text.create(s25.subContent);
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
    SecondTitleStyle(n25, o25 = null) {
        this.observeComponentCreation2((q25, r25) => {
            Text.create(n25.content);
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
    PrimaryTitleStyle(i25, j25 = null) {
        this.observeComponentCreation2((l25, m25) => {
            Text.create(i25.content);
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
    leftArea(x24 = null) {
        this.observeComponentCreation2((z24, a25) => {
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
        if (this.operationType === SubHeaderV2OperationType.ICON_GROUP &&
            (this.operationItems && this.operationItems.length > 0)) {
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
            return this.operationItems[0]?.accessibilityDescription;
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
    onMeasureSize(q24, r24, s24) {
        let t24 = { width: q24.width, height: q24.height };
        let u24 = this.getUIContext().getHostContext();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        r24.forEach((w24) => {
            s24.minHeight = Math.min(Number(this.getMinHeight()), Number(s24.maxHeight));
            t24.height = w24.measure(s24).height;
            t24.width = Number(s24.maxWidth);
        });
        return t24;
    }
    ButtonStyle(c24 = null) {
        this.observeComponentCreation2((e24, f24) => {
            If.create();
            if (this.operationItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m24, n24) => {
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
                        Button.onHover((p24) => {
                            if (p24) {
                                this.buttonBgColor = this.subHeaderV2Theme.textArrowHoverBgColor;
                            }
                            else {
                                this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        ViewStackProcessor.visualState("disabled");
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState("pressed");
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState();
                    }, Button);
                    this.observeComponentCreation2((k24, l24) => {
                        Text.create(this.operationItems[0].content);
                        __Text__secondaryTitleStyles({
                            fontWeight: FontWeight.Medium,
                            maxLines: DOUBLE_LINE_NUM,
                            fontColor: this.subHeaderV2Theme.fontButtonColor,
                        });
                        Text.defaultFocus(this.operationItems[0].defaultFocus);
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
    TextStyle(q23 = null) {
        this.observeComponentCreation2((a24, b24) => {
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
        this.observeComponentCreation2((t23, u23) => {
            If.create();
            if (this.operationItems?.[0]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y23, z23) => {
                        Text.create(this.operationItems[0].content);
                        __Text__secondaryTitleStyles({
                            maxLines: DOUBLE_LINE_NUM,
                            fontWeight: FontWeight.Regular,
                            alignment: Alignment.End,
                            fontColor: this.subHeaderV2Theme.fontSecondaryColor,
                        });
                        Text.focusable(true);
                        Text.defaultFocus(this.operationItems[0].defaultFocus);
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
    ArrowStyle(j23 = null) {
        this.observeComponentCreation2((o23, p23) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((m23, n23) => {
            SymbolGlyph.create({ "id": -1, "type": 40000, params: ['sys.symbol.chevron_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            SymbolGlyph.fontSize(RIGHT_SINGLE_ICON_SIZE);
            SymbolGlyph.fontColor([this.subHeaderV2Theme.iconArrowColor]);
            SymbolGlyph.draggable(false);
            SymbolGlyph.width(ARROW_ICON_WIDTH);
            SymbolGlyph.height(OPERATE_ITEM_LENGTH);
        }, SymbolGlyph);
        Row.pop();
    }
    TextArrowStyle(f21 = null) {
        this.observeComponentCreation2((h21, i21) => {
            If.create();
            if (this.operationItems?.[0] && this.operationItems[0] && this.operationItems[0].content &&
                this.operationItems[0].content.toString().length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h23, i23) => {
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
                    this.observeComponentCreation2((d23, e23) => {
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
                        ViewStackProcessor.visualState("disabled");
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState("pressed");
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState();
                        Button.onHover((g23) => {
                            if (g23) {
                                this.textArrowBgColor = this.subHeaderV2Theme.textArrowHoverBgColor;
                            }
                            else {
                                this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                    }, Button);
                    {
                        this.observeComponentCreation2((z21, a22) => {
                            if (a22) {
                                let b22 = new TextArrowLayout(this, {
                                    textArrowBuilder: () => {
                                        this.observeComponentCreation2((s22, t22) => {
                                            ForEach.create();
                                            const u22 = w22 => {
                                                const x22 = w22;
                                                this.observeComponentCreation2((z22, a23) => {
                                                    If.create();
                                                    if (x22 === INDEX_ZERO) {
                                                        this.ifElseBranchUpdateFunction(0, () => {
                                                            this.TextStyle.bind(this)();
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
                                            this.forEachUpdateFunction(s22, [INDEX_ZERO, INDEX_ONE], u22);
                                        }, ForEach);
                                        ForEach.pop();
                                    }
                                }, undefined, z21, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 736, col: 11 });
                                ViewPU.create(b22);
                                let c22 = () => {
                                    return {
                                        textArrowBuilder: () => {
                                            this.observeComponentCreation2((g22, h22) => {
                                                ForEach.create();
                                                const i22 = k22 => {
                                                    const l22 = k22;
                                                    this.observeComponentCreation2((n22, o22) => {
                                                        If.create();
                                                        if (l22 === INDEX_ZERO) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.TextStyle.bind(this)();
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
                                                this.forEachUpdateFunction(g22, [INDEX_ZERO, INDEX_ONE], i22);
                                            }, ForEach);
                                            ForEach.pop();
                                        }
                                    };
                                };
                                b22.paramsGenerator_ = c22;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(z21, {});
                            }
                        }, { name: "TextArrowLayout" });
                    }
                    Button.pop();
                    Stack.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((t21, u21) => {
                        Row.create();
                        Row.focusable(true);
                        Row.constraintSize({ minWidth: this.getRightAreaMinWidth() });
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((p21, q21) => {
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
                        ViewStackProcessor.visualState("disabled");
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState("pressed");
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState();
                        Button.onHover((s21) => {
                            if (s21) {
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
                    this.observeComponentCreation2((n21, o21) => {
                        SymbolGlyph.create({ "id": -1, "type": 40000, params: ['sys.symbol.chevron_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        SymbolGlyph.fontSize(RIGHT_SINGLE_ICON_SIZE);
                        SymbolGlyph.fontColor([this.subHeaderV2Theme.iconArrowColor]);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.width(ARROW_ICON_WIDTH);
                        SymbolGlyph.height(OPERATE_ITEM_LENGTH);
                    }, SymbolGlyph);
                    Button.pop();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }
    IconGroupStyle(b20 = null) {
        this.observeComponentCreation2((d21, e21) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((e20, f20) => {
            ForEach.create();
            const g20 = (l20, m20) => {
                const n20 = l20;
                this.observeComponentCreation2((p20, q20) => {
                    If.create();
                    if (m20 <= INDEX_TWO) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((b21, c21) => {
                                __Common__.create();
                                __Common__.margin({
                                    start: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                                    bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level3')),
                                });
                            }, __Common__);
                            {
                                this.observeComponentCreation2((v20, w20) => {
                                    if (w20) {
                                        let x20 = new SingleIconStyle(this, {
                                            item: {
                                                iconOptions: this.operationItems?.[m20].content,
                                                action: this.operationItems?.[m20].action,
                                                defaultFocus: this.operationItems?.[m20].defaultFocus,
                                                accessibilityLevel: this.operationItems?.[m20].accessibilityLevel,
                                                accessibilityText: this.operationItems?.[m20].accessibilityText,
                                                accessibilityDescription: this.operationItems?.[m20].accessibilityDescription,
                                            },
                                            isSingleIcon: this.operationItems?.length === SINGLE_ICON_NUMBER,
                                        }, undefined, v20, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 825, col: 13 });
                                        ViewV2.create(x20);
                                        let y20 = () => {
                                            return {
                                                item: {
                                                    iconOptions: this.operationItems?.[m20].content,
                                                    action: this.operationItems?.[m20].action,
                                                    defaultFocus: this.operationItems?.[m20].defaultFocus,
                                                    accessibilityLevel: this.operationItems?.[m20].accessibilityLevel,
                                                    accessibilityText: this.operationItems?.[m20].accessibilityText,
                                                    accessibilityDescription: this.operationItems?.[m20].accessibilityDescription,
                                                },
                                                isSingleIcon: this.operationItems?.length === SINGLE_ICON_NUMBER
                                            };
                                        };
                                        x20.paramsGenerator_ = y20;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(v20, {
                                            item: {
                                                iconOptions: this.operationItems?.[m20].content,
                                                action: this.operationItems?.[m20].action,
                                                defaultFocus: this.operationItems?.[m20].defaultFocus,
                                                accessibilityLevel: this.operationItems?.[m20].accessibilityLevel,
                                                accessibilityText: this.operationItems?.[m20].accessibilityText,
                                                accessibilityDescription: this.operationItems?.[m20].accessibilityDescription,
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
            };
            this.forEachUpdateFunction(e20, this.operationItems, g20, (j20, k20) => {
                return `${k20}`;
            }, true, true);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rightArea(b19 = null) {
        this.observeComponentCreation2((x19, y19) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON &&
                (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((t19, u19) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW &&
                (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextArrowStyle.bind(this)();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((p19, q19) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.ICON_GROUP &&
                (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconGroupStyle.bind(this)();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((l19, m19) => {
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
        this.observeComponentCreation2((h19, i19) => {
            If.create();
            if (this.operationType === undefined && (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    rightAreaParent(f18 = null) {
        this.observeComponentCreation2((h18, i18) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON ||
                this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u18, v18) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItems ? true : false);
                        Button.margin(INDEX_ZERO);
                        Button.padding(INDEX_ZERO);
                        Button.align(Alignment.BottomEnd);
                        Button.onKeyEvent((a19) => {
                            if (!a19) {
                                return;
                            }
                            if ((a19.keyCode === KeyCode.KEYCODE_SPACE || a19.keyCode === KeyCode.KEYCODE_ENTER) &&
                                a19.type === KeyType.Down) {
                                if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                    this.operationType === SubHeaderV2OperationType.BUTTON) &&
                                this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                    this.operationItems[0].action();
                                }
                                a19.stopPropagation();
                            }
                        });
                        Button.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Button.onTouch((z18) => {
                            if (z18.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (z18.type === TouchType.Up || z18.type === TouchType.Cancel) {
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
                        Button.accessibilityLevel(this.operationType === SubHeaderV2OperationType.BUTTON ||
                            this.operationType === SubHeaderV2OperationType.TEXT_ARROW ?
                        this.getRightAreaAccessibilityLevel() : 'no');
                        Button.hoverEffect(HoverEffect.None);
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Button.accessibilityGroup(true);
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                        Button.accessibilityDescription(this.getAccessibilityDescription());
                    }, Button);
                    this.rightArea.bind(this)();
                    Button.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((l18, m18) => {
                        Row.create();
                        Row.focusable(this.operationItems && this.operationType !== SubHeaderV2OperationType.LOADING ? true : false);
                        Row.justifyContent(FlexAlign.End);
                        Row.alignItems(VerticalAlign.Bottom);
                        Row.onKeyEvent((r18) => {
                            if (!r18) {
                                return;
                            }
                            if ((r18.keyCode === KeyCode.KEYCODE_SPACE || r18.keyCode === KeyCode.KEYCODE_ENTER) &&
                                r18.type === KeyType.Down) {
                                if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                    this.operationType === SubHeaderV2OperationType.BUTTON) &&
                                this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                    this.operationItems[0].action();
                                }
                                r18.stopPropagation();
                            }
                        });
                        Row.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Row.onTouch((q18) => {
                            if (q18.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (q18.type === TouchType.Up || q18.type === TouchType.Cancel) {
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
                        Row.accessibilityLevel(this.operationType === SubHeaderV2OperationType.BUTTON ||
                            this.operationType === SubHeaderV2OperationType.TEXT_ARROW ?
                        this.getRightAreaAccessibilityLevel() : 'no');
                    }, Row);
                    this.rightArea.bind(this)();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }
    rightAreaParentAging(j17 = null) {
        this.observeComponentCreation2((l17, m17) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON ||
                this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y17, z17) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItems ? true : false);
                        Button.align(Alignment.Start);
                        Button.onKeyEvent((e18) => {
                            if (!e18) {
                                return;
                            }
                            if ((e18.keyCode === KeyCode.KEYCODE_SPACE || e18.keyCode === KeyCode.KEYCODE_ENTER) &&
                                e18.type === KeyType.Down) {
                                if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                    this.operationType === SubHeaderV2OperationType.BUTTON) &&
                                this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                    this.operationItems[0].action();
                                }
                                e18.stopPropagation();
                            }
                        });
                        Button.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Button.onTouch((d18) => {
                            if (d18.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (d18.type === TouchType.Up || d18.type === TouchType.Cancel) {
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
                        Button.accessibilityGroup(true);
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                        Button.accessibilityDescription(this.getAccessibilityDescription());
                    }, Button);
                    this.rightArea.bind(this)();
                    Button.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((p17, q17) => {
                        Row.create();
                        Row.focusable(this.operationItems && this.operationType !== SubHeaderV2OperationType.LOADING ? true : false);
                        Row.justifyContent(FlexAlign.Start);
                        Row.onKeyEvent((v17) => {
                            if (!v17) {
                                return;
                            }
                            if ((v17.keyCode === KeyCode.KEYCODE_SPACE || v17.keyCode === KeyCode.KEYCODE_ENTER) &&
                                v17.type === KeyType.Down) {
                                if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                    this.operationType === SubHeaderV2OperationType.BUTTON) &&
                                this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                    this.operationItems[0].action();
                                }
                                v17.stopPropagation();
                            }
                        });
                        Row.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Row.onTouch((u17) => {
                            if (u17.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (u17.type === TouchType.Up || u17.type === TouchType.Cancel) {
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
                    this.rightArea.bind(this)();
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
            return this.operationItems[0].accessibilityText;
        }
        else {
            if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW &&
                this.operationItems[0]?.content.toString().length <= 0) {
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
        let i17 = {};
        if (!this.titleBuilder && ((this.title?.secondaryTitle && this.icon) ||
            (!this.title?.primaryTitle && this.title?.secondaryTitle))) {
            i17 = {
                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
            };
        }
        else if (this.select) {
            i17 = {
                top: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
                bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
            };
        }
        return i17;
    }
    initialRender() {
        this.observeComponentCreation2((x13, f14) => {
            If.create();
            if (this.isSuitableAging()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g17, h17) => {
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.padding(this.getAreaPadding());
                        Column.alignItems(HorizontalAlign.Start);
                    }, Column);
                    this.observeComponentCreation2((e17, f17) => {
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
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((a17, b17) => {
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
                    this.observeComponentCreation2((u16, v16) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((s16, t16) => {
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
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((o16, p16) => {
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
    getRightAreaAccessibilityLevel() {
        if (this.operationItems[0].accessibilityLevel && this.operationItems[0].accessibilityLevel !== '') {
            return this.operationItems[0].accessibilityLevel;
        }
        return 'yes';
    }
    LoadingProcessStyle(p10 = null) {
        this.observeComponentCreation2((n13, o13) => {
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
        this.observeComponentCreation2((a13, b13) => {
            LoadingProgress.create();
            LoadingProgress.width(OPERATE_ITEM_LENGTH);
            LoadingProgress.height(OPERATE_ITEM_LENGTH);
            LoadingProgress.color({ "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, LoadingProgress);
        Row.pop();
    }
    dummyFunction(v9 = null) {
        this.observeComponentCreation2((n10, o10) => {
            Row.create();
        }, Row);
        Row.pop();
    }
    updateStateVars(u9) {
        if (u9 === undefined) {
            return;
        }
        if ("icon" in u9) {
            this.updateParam("icon", u9.icon);
        }
        if ("title" in u9) {
            this.updateParam("title", u9.title);
        }
        if ("select" in u9) {
            this.updateParam("select", u9.select);
        }
        if ("operationType" in u9) {
            this.updateParam("operationType", u9.operationType);
        }
        if ("operationItems" in u9) {
            this.updateParam("operationItems", u9.operationItems);
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
    constructor(f6, r6, h7, p7 = -1, h8, j9) {
        super(f6, p7, j9);
        this.initParam("icon", (r6 && "icon" in r6) ? r6.icon : undefined);
        this.initParam("fontColor", (r6 && "fontColor" in r6) ? r6.fontColor : undefined);
        this.changeSymbolWidth = "changeSymbolWidth" in r6 ? r6.changeSymbolWidth : () => {
        };
        this.result = {
            width: 0,
            height: 0
        };
        this.finalizeConstruction();
    }
    onMeasureSize(h5, i5, t5) {
        i5.forEach((a6) => {
            this.result = a6.measure(t5);
        });
        console.log(`zzzz Child onMeasureSize ${JSON.stringify(this.result)}`);
        this.changeSymbolWidth(this.result);
        return this.result;
    }
    initialRender() {
        this.observeComponentCreation2((u4, v4) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((b4, f4) => {
            SymbolGlyph.create(this.icon);
            SymbolGlyph.fontSize(LEFT_ICON_SIZE);
            SymbolGlyph.fontColor(this.fontColor);
            SymbolGlyph.attributeModifier.bind(this)(this.icon);
            SymbolGlyph.margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) });
            SymbolGlyph.flexShrink(0);
        }, SymbolGlyph);
        Column.pop();
    }
    updateStateVars(v2) {
        if (v2 === undefined) {
            return;
        }
        if ("icon" in v2) {
            this.updateParam("icon", v2.icon);
        }
        if ("fontColor" in v2) {
            this.updateParam("fontColor", v2.fontColor);
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
    constructor(i3, j3, k3, l3 = -1, m3, n3) {
        super(i3, l3, n3);
        this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.isFocus = false;
        this.initParam("item", (j3 && "item" in j3) ? j3.item : null);
        this.subHeaderTheme = new SubHeaderTheme();
        this.initParam("isSingleIcon", (j3 && "isSingleIcon" in j3) ? j3.isSingleIcon : true);
        this.finalizeConstruction();
    }
    getRightIconAccessibilityText() {
        if (this.item?.accessibilityText) {
            return this.item.accessibilityText;
        }
        return '';
    }
    getRightIconAccessibilityLevel() {
        if (this.item?.accessibilityLevel && this.item?.accessibilityLevel !== '') {
            return this.item.accessibilityLevel;
        }
        return 'auto';
    }
    getRightIconAccessibilityDescription() {
        if (this.item?.accessibilityDescription && this.item?.accessibilityDescription !== '') {
            return this.item?.accessibilityDescription;
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
                        Button.defaultFocus(this.item.defaultFocus);
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
                        ViewStackProcessor.visualState("disabled");
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState("pressed");
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
    IconZone(v1 = null) {
        this.observeComponentCreation2((x1, y1) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c2, d2) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((k2, l2) => {
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
                                this.observeComponentCreation2((g2, h2) => {
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
    updateStateVars(g3) {
        if (g3 === undefined) {
            return;
        }
        if ("item" in g3) {
            this.updateParam("item", g3.item);
        }
        if ("isSingleIcon" in g3) {
            this.updateParam("isSingleIcon", g3.isSingleIcon);
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