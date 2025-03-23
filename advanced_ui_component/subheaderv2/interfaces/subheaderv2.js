/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
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
// 行数及整体高度
const SINGLE_LINE_NUM = 1;
const DOUBLE_LINE_NUM = 2;
// 资源数值
const RESOURCE_TYPE_SYMBOL = 40000;
// 左边尺寸常量
const LEFT_ICON_SIZE = '16vp';
const LEFT_ICON_SIZE_NUMBER = 16;
const LEFT_TEXT_NUMBER = 8;
// 右边尺寸常量
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
    constructor(options) {
        this.primaryTitle = options.primaryTitle;
        this.primaryTitleModifier = options.primaryTitleModifier;
        this.secondaryTitle = options.secondaryTitle;
        this.secondaryTitleModifier = options.secondaryTitleModifier;
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
    constructor(options) {
        this.options = options.options;
        this.selectedIndex = options.selectedIndex;
        this.selectedContent = options.selectedContent;
        this.onSelect = options.onSelect;
        this.defaultFocus = options.defaultFocus;
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
(function (SubHeaderV2OperationType) {
    SubHeaderV2OperationType[SubHeaderV2OperationType["TEXT_ARROW"] = 0] = "TEXT_ARROW";
    SubHeaderV2OperationType[SubHeaderV2OperationType["BUTTON"] = 1] = "BUTTON";
    SubHeaderV2OperationType[SubHeaderV2OperationType["ICON_GROUP"] = 2] = "ICON_GROUP";
    SubHeaderV2OperationType[SubHeaderV2OperationType["LOADING"] = 3] = "LOADING";
})(SubHeaderV2OperationType || (SubHeaderV2OperationType = {}));
let SubHeaderV2OperationItem = class SubHeaderV2OperationItem {
    constructor(options) {
        this.content = options.content;
        this.action = options.action;
        this.accessibilityText = options.accessibilityText;
        this.accessibilityDescription = options.accessibilityDescription;
        this.accessibilityLevel = options.accessibilityLevel;
        this.defaultFocus = options.defaultFocus;
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
function __Text__secondaryTitleStyles(fontStyle) {
    Text.fontSize(`${getResourceValue('sys.float.Subtitle_S')}fp`);
    Text.fontColor(fontStyle?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(fontStyle?.fontWeight);
    Text.maxLines(fontStyle?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(fontStyle?.alignment);
}
function __Text__primaryTitleStyles(fontStyle) {
    Text.fontSize(`${getResourceValue('sys.float.subheader_title_font_size')}fp`);
    Text.fontColor(fontStyle?.fontColor ?? { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    Text.fontWeight(fontStyle?.fontWeight);
    Text.maxLines(fontStyle?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(fontStyle?.alignment);
}
class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }
    applyNormalAttribute(instance) {
        if (this.isAgeing) {
            instance.width('100%');
        }
        else {
        }
    }
}
export class SubHeaderV2 extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("icon", (params && "icon" in params) ? params.icon : undefined);
        this.initParam("title", (params && "title" in params) ? params.title : undefined);
        this.initParam("select", (params && "select" in params) ? params.select : undefined);
        this.initParam("operationType", (params && "operationType" in params) ? params.operationType : SubHeaderV2OperationType.BUTTON);
        this.initParam("operationItems", (params && "operationItems" in params) ? params.operationItems : undefined);
        this.titleBuilder = "titleBuilder" in params ? params.titleBuilder : undefined;
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
    resetStateVarsOnReuse(params) {
        this.resetParam("icon", (params && "icon" in params) ? params.icon : undefined);
        this.resetParam("title", (params && "title" in params) ? params.title : undefined);
        this.resetParam("select", (params && "select" in params) ? params.select : undefined);
        this.resetParam("operationType", (params && "operationType" in params) ? params.operationType : SubHeaderV2OperationType.BUTTON);
        this.resetParam("operationItems", (params && "operationItems" in params) ? params.operationItems : undefined);
        this.titleBuilder = "titleBuilder" in params ? params.titleBuilder : undefined;
        this.fontSize = 1;
        this.ageing = true;
        this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.selectedIndex = -1;
        this.selectedContent = '';
        this.symbolWidth = LEFT_ICON_SIZE_NUMBER + LEFT_TEXT_NUMBER;
        this.subHeaderModifier = new SubHeaderModifier();
        this.subHeaderV2Theme = new SubHeaderTheme();
    }
    onWillApplyTheme(theme) {
        this.subHeaderV2Theme.fontPrimaryColor = theme.colors.fontPrimary;
        this.subHeaderV2Theme.fontSecondaryColor = theme.colors.fontSecondary;
        this.subHeaderV2Theme.fontButtonColor = theme.colors.fontEmphasize;
        this.subHeaderV2Theme.iconArrowColor = theme.colors.iconTertiary;
        this.subHeaderV2Theme.textArrowHoverBgColor = theme.colors.interactiveHover;
        this.subHeaderV2Theme.borderFocusColor = theme.colors.interactiveFocus;
        this.subHeaderV2Theme.leftIconColor = theme.colors.iconSecondary;
        this.subHeaderV2Theme.rightIconColor = theme.colors.iconPrimary;
    }
    async aboutToAppear() {
        let uiContext = this.getUIContext();
        this.isFollowingSystemFontScale = uiContext.isFollowingSystemFontScale();
        this.appMaxFontScale = uiContext.getMaxFontScale();
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
            let uiContext = this.getUIContext();
            let systemFontScale = uiContext.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(systemFontScale, this.appMaxFontScale);
        }
        catch (exception) {
            let code = exception.code;
            let message = exception.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
            return 1;
        }
    }
    IconSecondaryTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
            });
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (Util.isSymbolResource($$.iconOptions)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new SymbolGlyphChild(this, {
                                    icon: $$.iconOptions,
                                    fontColor: [this.subHeaderV2Theme.leftIconColor],
                                    changeSymbolWidth: (result) => {
                                        this.symbolWidth = result.width;
                                    }
                                }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/subheaderV2.ets", line: 331, col: 9 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        icon: $$.iconOptions,
                                        fontColor: [this.subHeaderV2Theme.leftIconColor],
                                        changeSymbolWidth: (result) => {
                                            this.symbolWidth = result.width;
                                        }
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    icon: $$.iconOptions,
                                    fontColor: [this.subHeaderV2Theme.leftIconColor]
                                });
                            }
                        }, { name: "SymbolGlyphChild" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create($$.iconOptions);
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
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
    SelectStyle(selectParam, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Select.create(selectParam.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(this.selectedIndex);
            Select.value(this.selectedContent);
            Select.defaultFocus(this.select?.defaultFocus);
            Select.onSelect((index, value) => {
                this.selectedIndex = index;
                if (value) {
                    this.selectedContent = value;
                }
                if (selectParam.onSelect) {
                    selectParam.onSelect(index, value);
                }
            });
            Select.font({
                size: `${getResourceValue('sys.float.Body_L')}fp`,
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
    }
    SubTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
            __Text__primaryTitleStyles({
                fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderV2Theme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(this.title?.primaryTitleModifier);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.subContent);
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
    SecondTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
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
    PrimaryTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
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
    leftArea(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                    // 其他不支持场景
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
    onMeasureSize(selfLayoutInfo, children, constraint) {
        let result = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
        let context = this.getUIContext().getHostContext();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        children.forEach((child) => {
            constraint.minHeight = Math.min(Number(this.getMinHeight()), Number(constraint.maxHeight));
            result.height = child.measure(constraint).height;
            result.width = Number(constraint.maxWidth);
        });
        return result;
    }
    ButtonStyle(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.operationItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        Button.onHover((isHover) => {
                            if (isHover) {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    TextStyle(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.operationItems?.[0]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    ArrowStyle(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create({ "id": -1, "type": 40000, params: ['sys.symbol.chevron_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            SymbolGlyph.fontSize(RIGHT_SINGLE_ICON_SIZE);
            SymbolGlyph.fontColor([this.subHeaderV2Theme.iconArrowColor]);
            SymbolGlyph.draggable(false);
            SymbolGlyph.width(ARROW_ICON_WIDTH);
            SymbolGlyph.height(OPERATE_ITEM_LENGTH);
        }, SymbolGlyph);
        Row.pop();
    }
    TextArrowStyle(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.operationItems?.[0] && this.operationItems[0] && this.operationItems[0].content &&
                this.operationItems[0].content.toString().length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        Button.onHover((isHover) => {
                            if (isHover) {
                                this.textArrowBgColor = this.subHeaderV2Theme.textArrowHoverBgColor;
                            }
                            else {
                                this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                    }, Button);
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new TextArrowLayout(this, {
                                    textArrowBuilder: () => {
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            ForEach.create();
                                            const forEachItemGenFunction = _item => {
                                                const index = _item;
                                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                    If.create();
                                                    if (index === INDEX_ZERO) {
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
                                            this.forEachUpdateFunction(elmtId, [INDEX_ZERO, INDEX_ONE], forEachItemGenFunction);
                                        }, ForEach);
                                        ForEach.pop();
                                    }
                                }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/subheaderV2.ets", line: 736, col: 11 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        textArrowBuilder: () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const index = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        If.create();
                                                        if (index === INDEX_ZERO) {
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
                                                this.forEachUpdateFunction(elmtId, [INDEX_ZERO, INDEX_ONE], forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                        }
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {});
                            }
                        }, { name: "TextArrowLayout" });
                    }
                    Button.pop();
                    Stack.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.focusable(true);
                        Row.constraintSize({ minWidth: this.getRightAreaMinWidth() });
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        Button.onHover((isHover) => {
                            if (isHover) {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    IconGroupStyle(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const item = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (index <= INDEX_TWO) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                __Common__.create();
                                __Common__.margin({
                                    start: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                                    bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level3')),
                                });
                            }, __Common__);
                            {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    if (isInitialRender) {
                                        let componentCall = new SingleIconStyle(this, {
                                            item: {
                                                iconOptions: this.operationItems?.[index].content,
                                                action: this.operationItems?.[index].action,
                                                defaultFocus: this.operationItems?.[index].defaultFocus,
                                                accessibilityLevel: this.operationItems?.[index].accessibilityLevel,
                                                accessibilityText: this.operationItems?.[index].accessibilityText,
                                                accessibilityDescription: this.operationItems?.[index].accessibilityDescription,
                                            },
                                            isSingleIcon: this.operationItems?.length === SINGLE_ICON_NUMBER,
                                        }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/subheaderV2.ets", line: 825, col: 11 });
                                        ViewV2.create(componentCall);
                                        let paramsLambda = () => {
                                            return {
                                                item: {
                                                    iconOptions: this.operationItems?.[index].content,
                                                    action: this.operationItems?.[index].action,
                                                    defaultFocus: this.operationItems?.[index].defaultFocus,
                                                    accessibilityLevel: this.operationItems?.[index].accessibilityLevel,
                                                    accessibilityText: this.operationItems?.[index].accessibilityText,
                                                    accessibilityDescription: this.operationItems?.[index].accessibilityDescription,
                                                },
                                                isSingleIcon: this.operationItems?.length === SINGLE_ICON_NUMBER
                                            };
                                        };
                                        componentCall.paramsGenerator_ = paramsLambda;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(elmtId, {
                                            item: {
                                                iconOptions: this.operationItems?.[index].content,
                                                action: this.operationItems?.[index].action,
                                                defaultFocus: this.operationItems?.[index].defaultFocus,
                                                accessibilityLevel: this.operationItems?.[index].accessibilityLevel,
                                                accessibilityText: this.operationItems?.[index].accessibilityText,
                                                accessibilityDescription: this.operationItems?.[index].accessibilityDescription,
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
            this.forEachUpdateFunction(elmtId, this.operationItems, forEachItemGenFunction, (item, index) => {
                return `${index}`;
            }, true, true);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rightArea(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    rightAreaParent(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON ||
                this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItems ? true : false);
                        Button.margin(INDEX_ZERO);
                        Button.padding(INDEX_ZERO);
                        Button.align(Alignment.BottomEnd);
                        Button.onKeyEvent((event) => {
                            if (!event) {
                                return;
                            }
                            if ((event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER) &&
                                event.type === KeyType.Down) {
                                if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                    this.operationType === SubHeaderV2OperationType.BUTTON) &&
                                this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                    this.operationItems[0].action();
                                }
                                event.stopPropagation();
                            }
                        });
                        Button.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Button.onTouch((event) => {
                            if (event.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.focusable(this.operationItems && this.operationType !== SubHeaderV2OperationType.LOADING ? true : false);
                        Row.justifyContent(FlexAlign.End);
                        Row.alignItems(VerticalAlign.Bottom);
                        Row.onKeyEvent((event) => {
                            if (!event) {
                                return;
                            }
                            if ((event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER) &&
                                event.type === KeyType.Down) {
                                if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                    this.operationType === SubHeaderV2OperationType.BUTTON) &&
                                this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                    this.operationItems[0].action();
                                }
                                event.stopPropagation();
                            }
                        });
                        Row.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Row.onTouch((event) => {
                            if (event.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
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
    rightAreaParentAging(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON ||
                this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItems ? true : false);
                        Button.align(Alignment.Start);
                        Button.onKeyEvent((event) => {
                            if (!event) {
                                return;
                            }
                            if ((event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER) &&
                                event.type === KeyType.Down) {
                                if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                    this.operationType === SubHeaderV2OperationType.BUTTON) &&
                                this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                    this.operationItems[0].action();
                                }
                                event.stopPropagation();
                            }
                        });
                        Button.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Button.onTouch((event) => {
                            if (event.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
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
                            // 'sys.float.margin_left' id,value: 16vp
                            start: LengthMetrics.vp(getResourceValue('sys.float.margin_left') - PADDING_LEFT),
                            // 'sys.float.margin_right' id,value: 16vp
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.focusable(this.operationItems && this.operationType !== SubHeaderV2OperationType.LOADING ? true : false);
                        Row.justifyContent(FlexAlign.Start);
                        Row.onKeyEvent((event) => {
                            if (!event) {
                                return;
                            }
                            if ((event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER) &&
                                event.type === KeyType.Down) {
                                if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                    this.operationType === SubHeaderV2OperationType.BUTTON) &&
                                this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                    this.operationItems[0].action();
                                }
                                event.stopPropagation();
                            }
                        });
                        Row.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Row.onTouch((event) => {
                            if (event.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                                }
                            }
                            if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
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
                            // 'sys.float.margin_left' id,value: 16vp
                            start: LengthMetrics.vp(getResourceValue('sys.float.margin_left') - PADDING_LEFT),
                            // 'sys.float.margin_right' id,value: 16vp
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
                // 播报：更多、more等, 使用的字段是：sys.string.ohos_toolbar_more
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
        let padding = {};
        if (!this.titleBuilder && ((this.title?.secondaryTitle && this.icon) ||
            (!this.title?.primaryTitle && this.title?.secondaryTitle))) {
            padding = {
                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
            };
        }
        else if (this.select) {
            padding = {
                top: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
                bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
            };
        }
        return padding;
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.isSuitableAging()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.padding(this.getAreaPadding());
                        Column.alignItems(HorizontalAlign.Start);
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    LoadingProcessStyle(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            LoadingProgress.create();
            LoadingProgress.width(OPERATE_ITEM_LENGTH);
            LoadingProgress.height(OPERATE_ITEM_LENGTH);
            LoadingProgress.color({ "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, LoadingProgress);
        Row.pop();
    }
    dummyFunction(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
        }, Row);
        Row.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("icon" in params) {
            this.updateParam("icon", params.icon);
        }
        if ("title" in params) {
            this.updateParam("title", params.title);
        }
        if ("select" in params) {
            this.updateParam("select", params.select);
        }
        if ("operationType" in params) {
            this.updateParam("operationType", params.operationType);
        }
        if ("operationItems" in params) {
            this.updateParam("operationItems", params.operationItems);
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
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("icon", (params && "icon" in params) ? params.icon : undefined);
        this.initParam("fontColor", (params && "fontColor" in params) ? params.fontColor : undefined);
        this.changeSymbolWidth = "changeSymbolWidth" in params ? params.changeSymbolWidth : () => {
        };
        this.result = {
            width: 0,
            height: 0
        };
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("icon", (params && "icon" in params) ? params.icon : undefined);
        this.resetParam("fontColor", (params && "fontColor" in params) ? params.fontColor : undefined);
        this.changeSymbolWidth = "changeSymbolWidth" in params ? params.changeSymbolWidth : () => {
        };
    }
    onMeasureSize(selfLayoutInfo, children, constraint) {
        children.forEach((child) => {
            this.result = child.measure(constraint);
        });
        console.log(`zzzz Child onMeasureSize ${JSON.stringify(this.result)}`);
        this.changeSymbolWidth(this.result);
        return this.result;
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create(this.icon);
            SymbolGlyph.fontSize(LEFT_ICON_SIZE);
            SymbolGlyph.fontColor(this.fontColor);
            SymbolGlyph.attributeModifier.bind(this)(this.icon);
            SymbolGlyph.margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) });
            SymbolGlyph.flexShrink(0);
        }, SymbolGlyph);
        Column.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("icon" in params) {
            this.updateParam("icon", params.icon);
        }
        if ("fontColor" in params) {
            this.updateParam("fontColor", params.fontColor);
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
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.isFocus = false;
        this.initParam("item", (params && "item" in params) ? params.item : null);
        this.subHeaderTheme = new SubHeaderTheme();
        this.initParam("isSingleIcon", (params && "isSingleIcon" in params) ? params.isSingleIcon : true);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.isFocus = false;
        this.resetParam("item", (params && "item" in params) ? params.item : null);
        this.resetConsumer("subHeaderTheme", new SubHeaderTheme());
        this.resetParam("isSingleIcon", (params && "isSingleIcon" in params) ? params.isSingleIcon : true);
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        ViewStackProcessor.visualState("pressed");
                        Button.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        ViewStackProcessor.visualState("disabled");
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                        Button.onTouch((event) => {
                            if (event.type === TouchType.Down || TouchType.Cancel) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            if (event.type === TouchType.Up) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Button.onHover((isHover) => {
                            if (isHover) {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.interactive_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                            else {
                                this.bgColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                            }
                        });
                        Button.responseRegion(this.iconResponseRegion());
                        Button.onClick((event) => {
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
    IconZone(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("item" in params) {
            this.updateParam("item", params.item);
        }
        if ("isSingleIcon" in params) {
            this.updateParam("isSingleIcon", params.isSingleIcon);
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
    /**
     * 是否symbol资源
     * @param resourceStr  资源
     * @returns true：symbol资源；false:非symbol资源
     */
    static isSymbolResource(resourceStr) {
        if (!Util.isResourceType(resourceStr)) {
            return false;
        }
        if (resourceStr instanceof SymbolGlyphModifier) {
            return resourceStr instanceof SymbolGlyphModifier;
        }
        let resource = resourceStr;
        return resource.type === RESOURCE_TYPE_SYMBOL;
    }
    /**
     * 是否Resource类型
     * @param resource 资源
     * @returns true：Resource类型；false:非Resource类型
     */
    static isResourceType(resource) {
        if (!resource) {
            return false;
        }
        if (typeof resource === 'string' || typeof resource === 'undefined') {
            return false;
        }
        return true;
    }
    /**
     * get resource size
     *
     * @param resourceName resource id
     * @returns resource size
     */
    static getNumberByResource(resourceId, defaultNumber) {
        try {
            let resourceNumber = resourceManager.getSystemResourceManager().getNumber(resourceId);
            if (resourceNumber === 0) {
                return defaultNumber;
            }
            else {
                return resourceNumber;
            }
        }
        catch (error) {
            let code = error.code;
            let message = error.message;
            hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${code}, message: ${message}`);
            return 0;
        }
    }
    /**
     * get resource string
     *
     * @param resourceId resource id
     * @param defaultString default value
     * @returns resource string
     */
    static getStringByResource(resourceId, defaultString) {
        try {
            let resourceString = getContext().resourceManager.getStringSync(resourceId);
            if (resourceString === '') {
                return defaultString;
            }
            else {
                return resourceString;
            }
        }
        catch (error) {
            let code = error.code;
            let message = error.message;
            hilog.error(0x3900, 'Ace', `SubHeader getStringByResource error, code: ${code}, message: ${message}`);
            return '';
        }
    }
    static numberToSize(fontSize) {
        if (typeof fontSize === 'string') {
            const fontSizeNumber = parseInt(fontSize);
            return fontSizeNumber;
        }
        else if (typeof fontSize === 'number') {
            return fontSize;
        }
        else {
            return getContext().resourceManager.getNumber(fontSize);
        }
    }
    static symbolFontSize(fontSize) {
        return Util.numberToSize(fontSize) + 'vp';
    }
}
const RESOURCE_CACHE_MAP = new HashMap();
// padding_level0: 125830919, 0
RESOURCE_CACHE_MAP.set('sys.float.padding_level0', { resourceId: 125830919, defaultValue: 0 });
// padding_level1: 125830920, 2
RESOURCE_CACHE_MAP.set('sys.float.padding_level1', { resourceId: 125830920, defaultValue: 2 });
// padding_level2: 125830921, 4
RESOURCE_CACHE_MAP.set('sys.float.padding_level2', { resourceId: 125830921, defaultValue: 4 });
// padding_level3: 125830922, 6
RESOURCE_CACHE_MAP.set('sys.float.padding_level3', { resourceId: 125830922, defaultValue: 6 });
// padding_level4: 125830923, 8
RESOURCE_CACHE_MAP.set('sys.float.padding_level4', { resourceId: 125830923, defaultValue: 8 });
// padding_level6: 125830925, 12
RESOURCE_CACHE_MAP.set('sys.float.padding_level6', { resourceId: 125830925, defaultValue: 12 });
// padding_level8: 125830927, 16
RESOURCE_CACHE_MAP.set('sys.float.padding_level8', { resourceId: 125830927, defaultValue: 16 });
// margin_left: 125830936, 16
RESOURCE_CACHE_MAP.set('sys.float.margin_left', { resourceId: 125830936, defaultValue: 16 });
// margin_right: 125830937, 16
RESOURCE_CACHE_MAP.set('sys.float.margin_right', { resourceId: 125830937, defaultValue: 16 });
// outline_extra_larger: 125830951, 2
RESOURCE_CACHE_MAP.set('sys.float.outline_extra_larger', { resourceId: 125830951, defaultValue: 2 });
// corner_radius_level4: 125830909, 8
RESOURCE_CACHE_MAP.set('sys.float.corner_radius_level4', { resourceId: 125830909, defaultValue: 8 });
// Subtitle_S: 125830969, 14
RESOURCE_CACHE_MAP.set('sys.float.Subtitle_S', { resourceId: 125830969, defaultValue: 14 });
// subheader_title_font_size: 125834265, 18
RESOURCE_CACHE_MAP.set('sys.float.subheader_title_font_size', { resourceId: 125834265, defaultValue: 18 });
// Body_L: 125830970, 16
RESOURCE_CACHE_MAP.set('sys.float.Body_L', { resourceId: 125830970, defaultValue: 16 });
// interactive_disable: 125831067, 0.4
RESOURCE_CACHE_MAP.set('sys.float.interactive_disable', { resourceId: 125831067, defaultValue: 0.4 });
// subheader_single_title_height: 125834252 56
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_title_height', { resourceId: 125834252, defaultValue: 56 });
// subheader_single_subtitle_height: 125834253 56
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_subtitle_height', { resourceId: 125834253, defaultValue: 56 });
// subheader_double_height: 125834254 72
RESOURCE_CACHE_MAP.set('sys.float.subheader_double_height', { resourceId: 125834254, defaultValue: 72 });
// subheader_title_font_weight: 125834255 700
RESOURCE_CACHE_MAP.set('sys.float.subheader_title_font_weight', { resourceId: 125834255, defaultValue: 700 });
function getResourceValue(resourceName) {
    if (RESOURCE_CACHE_MAP.hasKey(resourceName)) {
        let resourceValue = RESOURCE_CACHE_MAP.get(resourceName).resourceValue;
        if (typeof resourceValue === 'number') {
            return resourceValue;
        }
        else {
            resourceValue = Util.getNumberByResource(RESOURCE_CACHE_MAP.get(resourceName).resourceId, RESOURCE_CACHE_MAP.get(resourceName).defaultValue);
            RESOURCE_CACHE_MAP.get(resourceName).resourceValue = resourceValue;
            return resourceValue;
        }
    }
    return 0;
}
class TextArrowLayout extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.textArrowBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.textArrowBuilder !== undefined) {
            this.textArrowBuilder = params.textArrowBuilder;
        }
    }
    updateStateVars(params) {
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
    }
    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    doNothingBuilder(parent = null) {
    }
    onPlaceChildren(selfLayoutInfo, children, constraint) {
        let currentX = 0;
        let currentY = 0;
        for (let index = 0; index < children.length; index++) {
            let child = children[index];
            child.layout({ x: currentX, y: currentY });
        }
    }
    onMeasureSize(selfLayoutInfo, children, constraint) {
        let textArrowWidth = ARROW_ICON_WIDTH;
        let textArrowHeight = OPERATE_ITEM_LENGTH;
        let textChild = children[INDEX_ZERO];
        let textConstraint = {
            minWidth: Math.max(textArrowWidth, Number(constraint.minWidth)),
            maxWidth: constraint.maxWidth,
            minHeight: Math.max(textArrowHeight, Number(constraint.minHeight)),
            maxHeight: constraint.maxHeight,
        };
        let textMeasureResult = textChild.measure(textConstraint);
        textArrowWidth = Math.max(textArrowWidth, textMeasureResult.width);
        textArrowHeight = Math.max(textArrowHeight, textMeasureResult.height);
        let arrowChild = children[INDEX_ONE];
        let arrowConstraint = {
            minWidth: textArrowWidth,
            maxWidth: textArrowWidth,
            minHeight: textArrowHeight,
            maxHeight: textArrowHeight,
        };
        arrowChild.measure(arrowConstraint);
        return { width: textArrowWidth, height: textArrowHeight };
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