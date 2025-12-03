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

var __decorate = (this && this.__decorate) || function (w141, x141, y141, z141) {
    var a142 = arguments.length,
        b142 = a142 < 3 ? x141 : z141 === null ? z141 = Object.getOwnPropertyDescriptor(x141, y141) : z141, c142;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        b142 = Reflect.decorate(w141, x141, y141, z141);
    } else {
        for (var d142 = w141.length - 1; d142 >= 0; d142--) {
            if (c142 = w141[d142]) {
                b142 = (a142 < 3 ? c142(b142) : a142 > 3 ? c142(x141, y141, b142) : c142(x141, y141)) || b142;
            }
        }
    }
    return a142 > 3 && b142 && Object.defineProperty(x141, y141, b142), b142;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
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
const LEFT_ICON_SIZE_NUMBER = 16;
const LEFT_TEXT_NUMBER = 8;
const OPERATE_ITEM_LENGTH = lazyInit(() => {
    return getResourceValue('sys.float.subheader_right_arrow_height');
});
const ARROW_ICON_WIDTH = lazyInit(() => {
    return getResourceValue('sys.float.subheader_right_arrow_width');
});
const SINGLE_ICON_ZONE_SIZE = lazyInit(() => {
    return getResourceValue('sys.float.subheader_right_icon_zone_size');
});
const RIGHT_SINGLE_ICON_SIZE = lazyInit(() => {
    return getResourceValue('sys.float.subheader_right_icon_size') + 'vp';
});
const DEFAULT_FOCUS_STYLE = lazyInit(() => {
    return getResourceValue('sys.float.subheader_right_button_default_focus_style');
});
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
    constructor(v141) {
        this.primaryTitle = v141.primaryTitle;
        this.primaryTitleModifier = v141.primaryTitleModifier;
        this.secondaryTitle = v141.secondaryTitle;
        this.secondaryTitleModifier = v141.secondaryTitleModifier;
        this.titleAccessibilityText = v141.titleAccessibilityText;
    }
};
__decorate([
    Trace
], SubHeaderV2Title.prototype, 'primaryTitle', void 0);
__decorate([
    Trace
], SubHeaderV2Title.prototype, 'primaryTitleModifier', void 0);
__decorate([
    Trace
], SubHeaderV2Title.prototype, 'secondaryTitle', void 0);
__decorate([
    Trace
], SubHeaderV2Title.prototype, 'secondaryTitleModifier', void 0);
__decorate([
    Trace
], SubHeaderV2Title.prototype, 'titleAccessibilityText', void 0);
SubHeaderV2Title = __decorate([
    ObservedV2
], SubHeaderV2Title);

export { SubHeaderV2Title };
let SubHeaderV2Select = class SubHeaderV2Select {
    constructor(u141) {
        this.options = u141.options;
        this.selectedIndex = u141.selectedIndex;
        this.selectedContent = u141.selectedContent;
        this.onSelect = u141.onSelect;
        this.defaultFocus = u141.defaultFocus;
    }
};
__decorate([
    Trace
], SubHeaderV2Select.prototype, 'options', void 0);
__decorate([
    Trace
], SubHeaderV2Select.prototype, 'selectedIndex', void 0);
__decorate([
    Trace
], SubHeaderV2Select.prototype, 'selectedContent', void 0);
__decorate([
    Trace
], SubHeaderV2Select.prototype, 'onSelect', void 0);
__decorate([
    Trace
], SubHeaderV2Select.prototype, 'defaultFocus', void 0);
SubHeaderV2Select = __decorate([
    ObservedV2
], SubHeaderV2Select);

export { SubHeaderV2Select };

export var SubHeaderV2OperationType;
(function (y12) {
    y12[y12['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
    y12[y12['BUTTON'] = 1] = 'BUTTON';
    y12[y12['ICON_GROUP'] = 2] = 'ICON_GROUP';
    y12[y12['LOADING'] = 3] = 'LOADING';
})(SubHeaderV2OperationType || (SubHeaderV2OperationType = {}));
let SubHeaderV2OperationItem = class SubHeaderV2OperationItem {
    constructor(s141) {
        this.content = s141.content;
        this.action = s141.action;
        this.accessibilityText = s141.accessibilityText;
        this.accessibilityDescription = s141.accessibilityDescription;
        this.accessibilityLevel = s141.accessibilityLevel;
        this.defaultFocus = s141.defaultFocus;
    }
};
__decorate([
    Trace
], SubHeaderV2OperationItem.prototype, 'content', void 0);
__decorate([
    Trace
], SubHeaderV2OperationItem.prototype, 'action', void 0);
__decorate([
    Trace
], SubHeaderV2OperationItem.prototype, 'accessibilityText', void 0);
__decorate([
    Trace
], SubHeaderV2OperationItem.prototype, 'accessibilityDescription', void 0);
__decorate([
    Trace
], SubHeaderV2OperationItem.prototype, 'accessibilityLevel', void 0);
__decorate([
    Trace
], SubHeaderV2OperationItem.prototype, 'defaultFocus', void 0);
SubHeaderV2OperationItem = __decorate([
    ObservedV2
], SubHeaderV2OperationItem);

export { SubHeaderV2OperationItem };
let ContentIconOption = class ContentIconOption {
};
__decorate([
    Trace
], ContentIconOption.prototype, 'content', void 0);
__decorate([
    Trace
], ContentIconOption.prototype, 'subContent', void 0);
__decorate([
    Trace
], ContentIconOption.prototype, 'iconOptions', void 0);
__decorate([
    Trace
], ContentIconOption.prototype, 'action', void 0);
__decorate([
    Trace
], ContentIconOption.prototype, 'accessibilityLevel', void 0);
__decorate([
    Trace
], ContentIconOption.prototype, 'accessibilityText', void 0);
__decorate([
    Trace
], ContentIconOption.prototype, 'accessibilityDescription', void 0);
__decorate([
    Trace
], ContentIconOption.prototype, 'defaultFocus', void 0);
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
], FontStyle.prototype, 'maxLines', void 0);
__decorate([
    Trace
], FontStyle.prototype, 'fontWeight', void 0);
__decorate([
    Trace
], FontStyle.prototype, 'fontColor', void 0);
__decorate([
    Trace
], FontStyle.prototype, 'alignment', void 0);
FontStyle = __decorate([
    ObservedV2
], FontStyle);
let SubHeaderTheme = class SubHeaderTheme {
    constructor() {
        this.fontPrimaryColor = {
            'id': 125830982,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.fontSecondaryColor = {
            'id': 125830983,
            'type': 10001,
            params: ['sys.color.font_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.fontButtonColor = {
            'id': 125830986,
            'type': 10001,
            params: ['sys.color.font_emphasize'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.iconArrowColor = {
            'id': 125830993,
            'type': 10001,
            params: ['sys.color.icon_tertiary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.textArrowHoverBgColor = {
            'id': 125831019,
            'type': 10001,
            params: ['sys.color.interactive_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.borderFocusColor = {
            'id': 125831021,
            'type': 10001,
            params: ['sys.color.interactive_focus'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.leftIconColor = {
            'id': 125830992,
            'type': 10001,
            params: ['sys.color.icon_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.rightIconColor = {
            'id': 125830991,
            'type': 10001,
            params: ['sys.color.icon_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
    }
};
__decorate([
    Trace
], SubHeaderTheme.prototype, 'fontPrimaryColor', void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, 'fontSecondaryColor', void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, 'fontButtonColor', void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, 'iconArrowColor', void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, 'textArrowHoverBgColor', void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, 'borderFocusColor', void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, 'leftIconColor', void 0);
__decorate([
    Trace
], SubHeaderTheme.prototype, 'rightIconColor', void 0);
SubHeaderTheme = __decorate([
    ObservedV2
], SubHeaderTheme);

function __Text__secondaryTitleStyles(r141) {
    Text.fontSize(`${getResourceValue('sys.float.Subtitle_S')}fp`);
    Text.fontColor(r141?.fontColor ?? {
        'id': 125830983,
        'type': 10001,
        params: ['sys.color.font_secondary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
    });
    Text.fontWeight(r141?.fontWeight);
    Text.maxLines(r141?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(r141?.alignment);
}

function __Text__primaryTitleStyles(q141) {
    Text.fontSize(`${getResourceValue('sys.float.subheader_title_font_size')}fp`);
    Text.fontColor(q141?.fontColor ?? {
        'id': 125830982,
        'type': 10001,
        params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
    });
    Text.fontWeight(q141?.fontWeight);
    Text.maxLines(q141?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(q141?.alignment);
}

class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }

    applyNormalAttribute(p141) {
        if (this.isAgeing) {
            p141.width('100%');
        } else {
        }
    }
}

export class SubHeaderV2 extends ViewV2 {
    constructor(j141, k141, l141, m141 = -1, n141, o141) {
        super(j141, m141, o141);
        this.initParam('icon', (k141 && 'icon' in k141) ? k141.icon : undefined);
        this.initParam('title', (k141 && 'title' in k141) ? k141.title : undefined);
        this.initParam('select', (k141 && 'select' in k141) ? k141.select : undefined);
        this.initParam('operationType',
            (k141 && 'operationType' in k141) ? k141.operationType : SubHeaderV2OperationType.BUTTON);
        this.initParam('operationItems', (k141 && 'operationItems' in k141) ? k141.operationItems : undefined);
        this.titleBuilder = 'titleBuilder' in k141 ? k141.titleBuilder : undefined;
        this.fontSize = 1;
        this.ageing = true;
        this.textArrowBgColor = {
            'id': 125829134,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.buttonBgColor = {
            'id': 125829134,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.selectedIndex = -1;
        this.selectedContent = '';
        this.symbolWidth = LEFT_ICON_SIZE_NUMBER + LEFT_TEXT_NUMBER;
        this.subHeaderModifier = new SubHeaderModifier();
        this.isFollowingSystemFontScale = false;
        this.appMaxFontScale = 3.2;
        this.subHeaderV2Theme = new SubHeaderTheme();
        this.subHeaderMargin = {
            start: LengthMetrics.vp(getResourceValue('sys.float.subheader_content_margin_start')),
            end: LengthMetrics.vp(getResourceValue('sys.float.subheader_content_margin_end')),
        };
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(i141) {
        this.resetParam('icon', (i141 && 'icon' in i141) ? i141.icon : undefined);
        this.resetParam('title', (i141 && 'title' in i141) ? i141.title : undefined);
        this.resetParam('select', (i141 && 'select' in i141) ? i141.select : undefined);
        this.resetParam('operationType',
            (i141 && 'operationType' in i141) ? i141.operationType : SubHeaderV2OperationType.BUTTON);
        this.resetParam('operationItems', (i141 && 'operationItems' in i141) ? i141.operationItems : undefined);
        this.titleBuilder = 'titleBuilder' in i141 ? i141.titleBuilder : undefined;
        this.fontSize = 1;
        this.ageing = true;
        this.textArrowBgColor = {
            'id': 125829134,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.buttonBgColor = {
            'id': 125829134,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.selectedIndex = -1;
        this.selectedContent = '';
        this.symbolWidth = LEFT_ICON_SIZE_NUMBER + LEFT_TEXT_NUMBER;
        this.subHeaderModifier = new SubHeaderModifier();
        this.subHeaderV2Theme = new SubHeaderTheme();
        this.resetMonitorsOnReuse();
    }

    onWillApplyTheme(h141) {
        this.subHeaderV2Theme.fontPrimaryColor = h141.colors.fontPrimary;
        this.subHeaderV2Theme.fontSecondaryColor = h141.colors.fontSecondary;
        this.subHeaderV2Theme.fontButtonColor = h141.colors.fontEmphasize;
        this.subHeaderV2Theme.iconArrowColor = h141.colors.iconTertiary;
        this.subHeaderV2Theme.textArrowHoverBgColor = h141.colors.interactiveHover;
        this.subHeaderV2Theme.borderFocusColor = h141.colors.interactiveFocus;
        this.subHeaderV2Theme.leftIconColor = h141.colors.iconSecondary;
        this.subHeaderV2Theme.rightIconColor = h141.colors.iconPrimary;
    }

    async aboutToAppear() {
        let g141 = this.getUIContext();
        this.isFollowingSystemFontScale = g141.isFollowingSystemFontScale();
        this.appMaxFontScale = g141.getMaxFontScale();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        } else {
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
            let e141 = this.getUIContext();
            let f141 = e141.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(f141, this.appMaxFontScale);
        } catch (b141) {
            let c141 = b141.code;
            let d141 = b141.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${c141}, message: ${d141}`);
            return 1;
        }
    }

    IconSecondaryTitleStyle(l140, m140 = null) {
        this.observeComponentCreation2((z140, a141) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
            });
        }, Flex);
        this.observeComponentCreation2((p140, q140) => {
            If.create();
            if (Util.isSymbolResource(l140.iconOptions)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((t140, u140) => {
                            if (u140) {
                                let v140 = new SymbolGlyphChild(this, {
                                    icon: l140.iconOptions,
                                    fontColor: [this.subHeaderV2Theme.leftIconColor],
                                    changeSymbolWidth: (y140) => {
                                        this.symbolWidth = y140.width;
                                    }
                                }, undefined, t140, () => {
                                }, { page: 'library/src/main/ets/components/subheaderv2.ets', line: 349, col: 9 });
                                ViewV2.create(v140);
                                let w140 = () => {
                                    return {
                                        icon: l140.iconOptions,
                                        fontColor: [this.subHeaderV2Theme.leftIconColor],
                                        changeSymbolWidth: (x140) => {
                                            this.symbolWidth = x140.width;
                                        }
                                    };
                                };
                                v140.paramsGenerator_ = w140;
                            } else {
                                this.updateStateVarsOfChildByElmtId(t140, {
                                    icon: l140.iconOptions,
                                    fontColor: [this.subHeaderV2Theme.leftIconColor]
                                });
                            }
                        }, { name: 'SymbolGlyphChild' });
                    }
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((r140, s140) => {
                        Image.create(l140.iconOptions);
                        Image.fillColor(this.subHeaderV2Theme.leftIconColor);
                        Image.width(getResourceValue('sys.float.subheader_left_icon_size') + 'vp');
                        Image.height(getResourceValue('sys.float.subheader_left_icon_size') + 'vp');
                        Image.margin({
                            end: LengthMetrics.vp(getResourceValue('sys.float.subheader_left_icon_end_margin'))
                        });
                        Image.draggable(false);
                        Image.flexShrink(0);
                    }, Image);
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((n140, o140) => {
            Text.create(l140.content);
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

    infoChange(w12) {
        w12.dirty.forEach((x12) => {
            if ('select' === x12) {
                this.selectedIndex = w12.value(x12)?.now?.selectedIndex;
                this.selectedContent = w12.value(x12)?.now?.selectedContent;
            }
        });
    }

    SelectStyle(f140, g140 = null) {
        this.observeComponentCreation2((h140, i140) => {
            Select.create(f140.params.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(this.selectedIndex);
            Select.value(this.selectedContent);
            Select.defaultFocus(this.select?.defaultFocus);
            Select.onSelect((j140, k140) => {
                this.selectedIndex = j140;
                if (k140) {
                    this.selectedContent = k140;
                }
                if (f140.params.onSelect) {
                    f140.params.onSelect(j140, k140);
                }
            });
            Select.font({
                size: `${getResourceValue('sys.float.Body_L')}fp`,
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
    }

    SubTitleStyle(x139, y139 = null) {
        this.observeComponentCreation2((d140, e140) => {
            Column.create();
            Column.width('100%');
            Column.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level0')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((b140, c140) => {
            Text.create(x139.content);
            __Text__primaryTitleStyles({
                fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderV2Theme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(this.title?.primaryTitleModifier);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((z139, a140) => {
            Text.create(x139.subContent);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: getResourceValue('sys.float.subheader_subtitle_font_weight'),
                alignment: Alignment.Start,
                fontColor: this.subHeaderV2Theme.fontSecondaryColor,
            });
            Text.margin({
                top: getResourceValue('sys.float.subheader_titles_space'),
            });
            Text.attributeModifier.bind(this)(this.title?.secondaryTitleModifier);
        }, Text);
        Text.pop();
        Column.pop();
    }

    SecondTitleStyle(t139, u139 = null) {
        this.observeComponentCreation2((v139, w139) => {
            Text.create(t139.content);
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
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
            });
        }, Text);
        Text.pop();
    }

    PrimaryTitleStyle(p139, q139 = null) {
        this.observeComponentCreation2((r139, s139) => {
            Text.create(p139.content);
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
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
            });
        }, Text);
        Text.pop();
    }

    leftArea(m139 = null) {
        this.observeComponentCreation2((n139, o139) => {
            If.create();
            if (this.titleBuilder) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.titleBuilder.bind(this)();
                });
            } else if (this.title?.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondaryTitleStyle', {
                        content: () => this.title?.secondaryTitle,
                        iconOptions: () => (this['__icon'] ? this['__icon'] : this['icon'])
                    }));
                });
            } else if (this.title?.secondaryTitle && this.title?.primaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle',
                        { content: () => this.title?.primaryTitle, subContent: () => this.title?.secondaryTitle }));
                });
            } else if (this.title?.secondaryTitle) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle',
                        { content: () => this.title?.secondaryTitle }));
                });
            } else if (this.select) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.SelectStyle.bind(this)(makeBuilderParameterProxy('SelectStyle',
                        { params: () => (this['__select'] ? this['__select'] : this['select']) }));
                });
            } else if (this.title?.primaryTitle) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle',
                        { content: () => this.title?.primaryTitle }));
                });
            } else {
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
        if (this.operationItems[0]?.accessibilityDescription &&
            this.operationItems[0]?.accessibilityDescription !== '') {
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
        } else {
            return (this.ageing && this.icon) ? LengthMetrics.vp(LEFT_ICON_SIZE_NUMBER +
                LEFT_TEXT_NUMBER) : LengthMetrics.vp(0);
        }
    }

    onMeasureSize(q12, r12, s12) {
        let t12 = { width: q12.width, height: q12.height };
        let u12 = this.getUIContext().getHostContext();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        } else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        r12.forEach((v12) => {
            s12.minHeight = Math.min(Number(this.getMinHeight()), Number(s12.maxHeight));
            t12.height = v12.measure(s12).height;
            t12.width = Number(s12.maxWidth);
        });
        return t12;
    }

    ButtonStyle(e139 = null) {
        this.observeComponentCreation2((f139, g139) => {
            If.create();
            if (this.operationItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j139, k139) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(true);
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderV2Theme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        Button.padding({
                            start: LengthMetrics.vp(getResourceValue('sys.float.subheader_right_button_padding_horizontal')),
                            end: LengthMetrics.vp(getResourceValue('sys.float.subheader_right_button_padding_horizontal')),
                            top: LengthMetrics.vp(getResourceValue('sys.float.subheader_right_button_padding_vertical')),
                            bottom: LengthMetrics.vp(getResourceValue('sys.float.subheader_right_button_padding_vertical')),
                        });
                        Button.margin({
                            start: this.ageing ?
                                LengthMetrics.vp(LengthMetrics.vp(getResourceValue('sys.float.padding_level0')).value +
                                this.leftIconMargin().value) :
                                LengthMetrics.vp(LengthMetrics.vp(getResourceValue('sys.float.subheader_right_button_margin_start'))
                                    .value +
                                this.leftIconMargin().value),
                            bottom: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                                (this.title?.secondaryTitle && this.title?.primaryTitle ?
                                    getResourceValue('sys.float.subheader_right_button_margin_bottom') :
                                    getResourceValue('sys.float.subheader_single_right_button_margin_bottom'))),
                        });
                        Button.backgroundColor(this.buttonBgColor);
                        Button.constraintSize({ minHeight: OPERATE_ITEM_LENGTH() });
                        Button.align(Alignment.End);
                        Button.borderRadius(getResourceValue('sys.float.subheader_right_button_radius'));
                        Button.offset({ x: getResourceValue('sys.float.subheader_right_button_x_offset') });
                        Button.attributeModifier.bind(this)(!DEFAULT_FOCUS_STYLE() ? undefined :
                            new DefaultFocusStyleModifier((p12) => {
                                if (p12) {
                                    this.buttonBgColor = {
                                        'id': 125831015,
                                        'type': 10001,
                                        params: ['sys.color.comp_background_focus'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                } else {
                                    this.buttonBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }));
                        Button.onHover((o12) => {
                            if (o12) {
                                this.buttonBgColor = this.subHeaderV2Theme.textArrowHoverBgColor;
                            } else {
                                this.buttonBgColor = {
                                    'id': 125829134,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            }
                        });
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': 125831020,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                    }, Button);
                    this.observeComponentCreation2((h139, i139) => {
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
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    getTextArrowPaddingLeft() {
        if (this.operationItems && this.operationItems.length > 0 && this.operationItems[0].content) {
            return LengthMetrics.vp(getResourceValue('sys.float.subheader_right_text_padding_start'));
        }
        return LengthMetrics.vp(getResourceValue('sys.float.padding_level0'));
    }

    getTextArrowMarginRight() {
        if (this.operationItems && this.operationItems.length > 0 && this.operationItems[0].content) {
            return LengthMetrics.vp(getResourceValue('sys.float.subheader_right_font_arrow_space') +
            ARROW_ICON_WIDTH());
        }
        return LengthMetrics.vp(ARROW_ICON_WIDTH());
    }

    TextStyle(x138 = null) {
        this.observeComponentCreation2((c139, d139) => {
            Row.create();
            Row.attributeModifier.bind(this)(this.subHeaderModifier);
            Row.alignItems(VerticalAlign.Center);
            Row.focusable(true);
            Row.constraintSize({ minHeight: OPERATE_ITEM_LENGTH() });
            Row.padding({
                start: this.getTextArrowPaddingLeft(),
                top: this.ageing ? LengthMetrics.vp(0) :
                    LengthMetrics.vp(getResourceValue('sys.float.subheader_right_text_padding_vertical')),
                bottom: this.ageing ? LengthMetrics.vp(0) :
                    LengthMetrics.vp(getResourceValue('sys.float.subheader_right_text_padding_vertical')),
            });
        }, Row);
        this.observeComponentCreation2((y138, z138) => {
            If.create();
            if (this.operationItems?.[0]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a139, b139) => {
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
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
    }

    ArrowStyle(s138 = null) {
        this.observeComponentCreation2((v138, w138) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((t138, u138) => {
            SymbolGlyph.create({
                'id': 125832664,
                'type': 40000,
                params: ['sys.symbol.chevron_right'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            SymbolGlyph.fontSize(OPERATE_ITEM_LENGTH() + 'vp');
            SymbolGlyph.fontColor([this.subHeaderV2Theme.iconArrowColor]);
            SymbolGlyph.draggable(false);
            SymbolGlyph.width(ARROW_ICON_WIDTH());
            SymbolGlyph.height(OPERATE_ITEM_LENGTH());
        }, SymbolGlyph);
        Row.pop();
    }

    TextArrowStyle(l137 = null) {
        this.observeComponentCreation2((m137, n137) => {
            If.create();
            if (this.operationItems?.[0] && this.operationItems[0] && this.operationItems[0].content &&
                this.operationItems[0].content.toString().length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q138, r138) => {
                        Stack.create();
                        Stack.focusable(true);
                        Stack.align(this.ageing ? Alignment.Start : Alignment.End);
                        Stack.margin({
                            start: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                                getResourceValue('sys.float.subheader_right_text_arrow_margin_start')),
                            bottom: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                                (this.title?.secondaryTitle && this.title?.primaryTitle ?
                                    getResourceValue('sys.float.subheader_right_text_arrow_margin_bottom') :
                                    getResourceValue('sys.float.subheader_single_right_text_arrow_margin_bottom'))),
                        });
                    }, Stack);
                    this.observeComponentCreation2((n138, o138) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.padding({
                            top: INDEX_ZERO,
                            bottom: INDEX_ZERO,
                            left: getResourceValue('sys.float.subheader_right_text_arrow_padding_horizontal'),
                            right: getResourceValue('sys.float.subheader_right_text_arrow_padding_horizontal'),
                        });
                        Button.margin({ start: this.leftIconMargin() });
                        Button.backgroundColor(this.textArrowBgColor);
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderV2Theme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        Button.borderRadius(getResourceValue('sys.float.subheader_right_text_arrow_radius'));
                        Button.offset({ x: getResourceValue('sys.float.subheader_right_text_arrow_x_offset') });
                        Button.attributeModifier.bind(this)(!DEFAULT_FOCUS_STYLE() ? undefined :
                            new DefaultFocusStyleModifier((n12) => {
                                if (n12) {
                                    this.textArrowBgColor = {
                                        'id': 125831015,
                                        'type': 10001,
                                        params: ['sys.color.comp_background_focus'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                } else {
                                    this.textArrowBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }));
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': 125831020,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                        Button.onHover((m12) => {
                            if (m12) {
                                this.textArrowBgColor = this.subHeaderV2Theme.textArrowHoverBgColor;
                            } else {
                                this.textArrowBgColor = {
                                    'id': 125829134,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            }
                        });
                    }, Button);
                    {
                        this.observeComponentCreation2((v137, w137) => {
                            if (w137) {
                                let x137 = new TextArrowLayout(this, {
                                    textArrowBuilder: () => {
                                        this.observeComponentCreation2((g138, h138) => {
                                            ForEach.create();
                                            const i138 = j138 => {
                                                const k138 = j138;
                                                this.observeComponentCreation2((l138, m138) => {
                                                    If.create();
                                                    if (k138 === INDEX_ZERO) {
                                                        this.ifElseBranchUpdateFunction(0, () => {
                                                            this.TextStyle.bind(this)();
                                                        });
                                                    } else {
                                                        this.ifElseBranchUpdateFunction(1, () => {
                                                            this.ArrowStyle.bind(this)();
                                                        });
                                                    }
                                                }, If);
                                                If.pop();
                                            };
                                            this.forEachUpdateFunction(g138, [INDEX_ZERO, INDEX_ONE], i138);
                                        }, ForEach);
                                        ForEach.pop();
                                    }
                                }, undefined, v137, () => {
                                }, { page: 'library/src/main/ets/components/subheaderv2.ets', line: 777, col: 11 });
                                ViewPU.create(x137);
                                let y137 = () => {
                                    return {
                                        textArrowBuilder: () => {
                                            this.observeComponentCreation2((z137, a138) => {
                                                ForEach.create();
                                                const b138 = c138 => {
                                                    const d138 = c138;
                                                    this.observeComponentCreation2((e138, f138) => {
                                                        If.create();
                                                        if (d138 === INDEX_ZERO) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.TextStyle.bind(this)();
                                                            });
                                                        } else {
                                                            this.ifElseBranchUpdateFunction(1, () => {
                                                                this.ArrowStyle.bind(this)();
                                                            });
                                                        }
                                                    }, If);
                                                    If.pop();
                                                };
                                                this.forEachUpdateFunction(z137, [INDEX_ZERO, INDEX_ONE], b138);
                                            }, ForEach);
                                            ForEach.pop();
                                        }
                                    };
                                };
                                x137.paramsGenerator_ = y137;
                            } else {
                                this.updateStateVarsOfChildByElmtId(v137, {});
                            }
                        }, { name: 'TextArrowLayout' });
                    }
                    Button.pop();
                    Stack.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((t137, u137) => {
                        Row.create();
                        Row.margin({ bottom: getResourceValue('sys.float.subheader_right_only_arrow_margin_bottom') });
                        Row.focusable(true);
                        Row.constraintSize({ minWidth: this.getRightAreaMinWidth() });
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((q137, r137) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.width(ARROW_ICON_WIDTH());
                        Button.height(OPERATE_ITEM_LENGTH());
                        Button.backgroundColor(this.textArrowBgColor);
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderV2Theme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        Button.borderRadius(getResourceValue('sys.float.subheader_right_text_arrow_radius'));
                        Button.attributeModifier.bind(this)(!DEFAULT_FOCUS_STYLE() ? undefined :
                            new DefaultFocusStyleModifier((l12) => {
                                if (l12) {
                                    this.textArrowBgColor = {
                                        'id': 125831015,
                                        'type': 10001,
                                        params: ['sys.color.comp_background_focus'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                } else {
                                    this.textArrowBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }));
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': 125831020,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                        Button.onHover((k12) => {
                            if (k12) {
                                this.textArrowBgColor = this.subHeaderV2Theme.textArrowHoverBgColor;
                            } else {
                                this.textArrowBgColor = {
                                    'id': 125829134,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            }
                        });
                        Button.focusable(true);
                        Button.margin({
                            start: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                                getResourceValue('sys.float.subheader_right_text_arrow_margin_start')),
                            bottom: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                                (this.title?.secondaryTitle && this.title?.primaryTitle ?
                                    getResourceValue('sys.float.subheader_right_text_arrow_margin_bottom') :
                                    getResourceValue('sys.float.subheader_single_right_text_arrow_margin_bottom'))),
                        });
                    }, Button);
                    this.observeComponentCreation2((o137, p137) => {
                        SymbolGlyph.create({
                            'id': 125832664,
                            'type': 40000,
                            params: ['sys.symbol.chevron_right'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        SymbolGlyph.fontSize(OPERATE_ITEM_LENGTH() + 'vp');
                        SymbolGlyph.fontColor([this.subHeaderV2Theme.iconArrowColor]);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.width(ARROW_ICON_WIDTH());
                        SymbolGlyph.height(OPERATE_ITEM_LENGTH());
                    }, SymbolGlyph);
                    Button.pop();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }

    IconGroupStyle(q136 = null) {
        this.observeComponentCreation2((j137, k137) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((r136, s136) => {
            ForEach.create();
            const t136 = (w136, x136) => {
                const y136 = w136;
                this.observeComponentCreation2((z136, a137) => {
                    If.create();
                    if (x136 <= INDEX_TWO) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((b137, c137) => {
                                __Common__.create();
                                __Common__.margin({
                                    start: LengthMetrics.vp(getResourceValue('sys.float.subheader_right_icon_group_padding_start')),
                                    bottom: LengthMetrics.vp(this.title?.secondaryTitle && this.title?.primaryTitle ?
                                        getResourceValue('sys.float.subheader_right_icon_group_margin_bottom') :
                                        getResourceValue('sys.float.subheader_single_right_icon_group_margin_bottom')),
                                });
                                __Common__.offset({
                                    x: getResourceValue('sys.float.subheader_right_icon_group_x_offset')
                                });
                            }, __Common__);
                            {
                                this.observeComponentCreation2((g12, h12) => {
                                    if (h12) {
                                        let i12 = new SingleIconStyle(this, {
                                            item: {
                                                iconOptions: this.operationItems?.[x136].content,
                                                action: this.operationItems?.[x136].action,
                                                defaultFocus: this.operationItems?.[x136].defaultFocus,
                                                accessibilityLevel: this.operationItems?.[x136].accessibilityLevel,
                                                accessibilityText: this.operationItems?.[x136].accessibilityText,
                                                accessibilityDescription: this.operationItems?.[x136].accessibilityDescription,
                                            },
                                            isSingleIcon: this.operationItems?.length === SINGLE_ICON_NUMBER,
                                        }, undefined, g12, () => {
                                        }, {
                                            page: 'library/src/main/ets/components/subheaderv2.ets',
                                            line: 893,
                                            col: 11
                                        });
                                        ViewV2.create(i12);
                                        let j12 = () => {
                                            return {
                                                item: {
                                                    iconOptions: this.operationItems?.[x136].content,
                                                    action: this.operationItems?.[x136].action,
                                                    defaultFocus: this.operationItems?.[x136].defaultFocus,
                                                    accessibilityLevel: this.operationItems?.[x136].accessibilityLevel,
                                                    accessibilityText: this.operationItems?.[x136].accessibilityText,
                                                    accessibilityDescription: this.operationItems?.[x136].accessibilityDescription,
                                                },
                                                isSingleIcon: this.operationItems?.length === SINGLE_ICON_NUMBER
                                            };
                                        };
                                        i12.paramsGenerator_ = j12;
                                    } else {
                                        this.updateStateVarsOfChildByElmtId(g12, {
                                            item: {
                                                iconOptions: this.operationItems?.[x136].content,
                                                action: this.operationItems?.[x136].action,
                                                defaultFocus: this.operationItems?.[x136].defaultFocus,
                                                accessibilityLevel: this.operationItems?.[x136].accessibilityLevel,
                                                accessibilityText: this.operationItems?.[x136].accessibilityText,
                                                accessibilityDescription: this.operationItems?.[x136].accessibilityDescription,
                                            },
                                            isSingleIcon: this.operationItems?.length === SINGLE_ICON_NUMBER
                                        });
                                    }
                                }, { name: 'SingleIconStyle' });
                            }
                            __Common__.pop();
                        });
                    } else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(r136, this.operationItems, t136, (u136, v136) => {
                return `${v136}`;
            }, true, true);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    rightArea(h136 = null) {
        this.observeComponentCreation2((o136, p136) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON &&
                (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((m136, n136) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW &&
                (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextArrowStyle.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((k136, l136) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.ICON_GROUP &&
                (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconGroupStyle.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((i136, j136) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.LOADING) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.LoadingProcessStyle.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((e12, f12) => {
            If.create();
            if (this.operationType === undefined && (this.operationItems && this.operationItems.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    rightAreaParent(y135 = null) {
        this.observeComponentCreation2((z135, a136) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON ||
                this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e136, f136) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItems ? true : false);
                        Button.margin(INDEX_ZERO);
                        Button.padding(INDEX_ZERO);
                        Button.align(Alignment.BottomEnd);
                        Button.onKeyEvent((d12) => {
                            if (!d12) {
                                return;
                            }
                            if ((d12.keyCode === KeyCode.KEYCODE_SPACE || d12.keyCode === KeyCode.KEYCODE_ENTER) &&
                                d12.type === KeyType.Down) {
                                if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                    this.operationType === SubHeaderV2OperationType.BUTTON) &&
                                this.operationItems && this.operationItems.length > 0 &&
                                this.operationItems[0].action) {
                                    this.operationItems[0].action();
                                }
                                d12.stopPropagation();
                            }
                        });
                        Button.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Button.onTouch((c12) => {
                            if (c12.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }
                            if (c12.type === TouchType.Up || c12.type === TouchType.Cancel) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
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
                        Button.backgroundColor({
                            'id': 125829134,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_sub_background_transparent'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        Button.accessibilityGroup(true);
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                        Button.accessibilityDescription(this.getAccessibilityDescription());
                    }, Button);
                    this.rightArea.bind(this)();
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((b136, c136) => {
                        Row.create();
                        Row.focusable(this.operationItems && this.operationType !== SubHeaderV2OperationType.LOADING ?
                            true : false);
                        Row.justifyContent(FlexAlign.End);
                        Row.alignItems(VerticalAlign.Bottom);
                        Row.onKeyEvent((b12) => {
                            if (!b12) {
                                return;
                            }
                            if ((b12.keyCode === KeyCode.KEYCODE_SPACE || b12.keyCode === KeyCode.KEYCODE_ENTER) &&
                                b12.type === KeyType.Down) {
                                if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                    this.operationType === SubHeaderV2OperationType.BUTTON) &&
                                this.operationItems && this.operationItems.length > 0 &&
                                this.operationItems[0].action) {
                                    this.operationItems[0].action();
                                }
                                b12.stopPropagation();
                            }
                        });
                        Row.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Row.onTouch((a12) => {
                            if (a12.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }
                            if (a12.type === TouchType.Up || a12.type === TouchType.Cancel) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
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

    rightAreaParentAging(p135 = null) {
        this.observeComponentCreation2((q135, r135) => {
            If.create();
            if (this.operationType === SubHeaderV2OperationType.BUTTON ||
                this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v135, w135) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItems ? true : false);
                        Button.align(Alignment.Start);
                        Button.onKeyEvent((z11) => {
                            if (!z11) {
                                return;
                            }
                            if ((z11.keyCode === KeyCode.KEYCODE_SPACE || z11.keyCode === KeyCode.KEYCODE_ENTER) &&
                                z11.type === KeyType.Down) {
                                if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                    this.operationType === SubHeaderV2OperationType.BUTTON) &&
                                this.operationItems && this.operationItems.length > 0 &&
                                this.operationItems[0].action) {
                                    this.operationItems[0].action();
                                }
                                z11.stopPropagation();
                            }
                        });
                        Button.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Button.onTouch((y11) => {
                            if (y11.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }
                            if (y11.type === TouchType.Up || y11.type === TouchType.Cancel) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
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
                            this.operationType === SubHeaderV2OperationType.TEXT_ARROW ?
                            this.getRightAreaAccessibilityLevel() : 'no');
                        Button.backgroundColor({
                            'id': 125829134,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_sub_background_transparent'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        Button.hoverEffect(HoverEffect.None);
                        Button.accessibilityGroup(true);
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                        Button.accessibilityDescription(this.getAccessibilityDescription());
                    }, Button);
                    this.rightArea.bind(this)();
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((s135, t135) => {
                        Row.create();
                        Row.focusable(this.operationItems && this.operationType !== SubHeaderV2OperationType.LOADING ?
                            true : false);
                        Row.justifyContent(FlexAlign.Start);
                        Row.onKeyEvent((x11) => {
                            if (!x11) {
                                return;
                            }
                            if ((x11.keyCode === KeyCode.KEYCODE_SPACE || x11.keyCode === KeyCode.KEYCODE_ENTER) &&
                                x11.type === KeyType.Down) {
                                if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                    this.operationType === SubHeaderV2OperationType.BUTTON) &&
                                this.operationItems && this.operationItems.length > 0 &&
                                this.operationItems[0].action) {
                                    this.operationItems[0].action();
                                }
                                x11.stopPropagation();
                            }
                        });
                        Row.onClick(() => {
                            if ((this.operationType === SubHeaderV2OperationType.TEXT_ARROW ||
                                this.operationType === SubHeaderV2OperationType.BUTTON) &&
                            this.operationItems && this.operationItems.length > 0 && this.operationItems[0].action) {
                                this.operationItems[0].action();
                            }
                        });
                        Row.onTouch((w11) => {
                            if (w11.type === TouchType.Down) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }
                            if (w11.type === TouchType.Up || w11.type === TouchType.Cancel) {
                                if (this.operationType === SubHeaderV2OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === SubHeaderV2OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
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

    getRightAreaAccessibilityText() {
        if (!this.operationItems || this.operationItems?.length <= 0) {
            return '';
        }
        if (this.operationItems[0]?.accessibilityText && this.operationItems[0]?.accessibilityText !== '') {
            return this.operationItems[0].accessibilityText;
        } else {
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
        } else if (this.title?.secondaryTitle && this.title?.primaryTitle) {
            return getResourceValue('sys.float.subheader_double_height');
        } else if (this.title?.primaryTitle || this.select) {
            return getResourceValue('sys.float.subheader_single_title_height');
        }
        return getResourceValue('sys.float.subheader_single_subtitle_height');
    }

    getAreaPadding() {
        let o135 = {};
        if (!this.titleBuilder && ((this.title?.secondaryTitle && this.icon) ||
            (!this.title?.primaryTitle && this.title?.secondaryTitle))) {
            o135 = {
                start: LengthMetrics.vp(getResourceValue('sys.float.subheader_single_subtitle_padding')),
                end: LengthMetrics.vp(getResourceValue('sys.float.subheader_single_subtitle_padding')),
            };
        } else if (this.select) {
            o135 = {
                top: LengthMetrics.vp(getResourceValue('sys.float.subheader_select_padding')),
                bottom: LengthMetrics.vp(getResourceValue('sys.float.subheader_select_padding')),
            };
        }
        return o135;
    }

    getTitleAccessibilityText() {
        if (this.title?.titleAccessibilityText === undefined) {
            return '';
        }
        if (!this.select && this.title?.titleAccessibilityText) {
            return this.title?.titleAccessibilityText;
        }
        return '';
    }

    initialRender() {
        this.observeComponentCreation2((a135, b135) => {
            If.create();
            if (this.isSuitableAging()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m135, n135) => {
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.padding(this.getAreaPadding());
                        Column.alignItems(HorizontalAlign.Start);
                    }, Column);
                    this.observeComponentCreation2((k135, l135) => {
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
                        Row.accessibilityText(this.getTitleAccessibilityText());
                        Row.accessibilityRole(this.title ? AccessibilityRoleType.TITLE_BAR : undefined);
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((i135, j135) => {
                        If.create();
                        if (this.isRightAreaExists()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.rightAreaParentAging.bind(this)();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Column.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((g135, h135) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((e135, f135) => {
                        Row.create();
                        Row.margin({
                            top: this.fontSize >= MIN_FONT_SIZE ? getResourceValue('sys.float.padding_level8') : '',
                            bottom: this.fontSize >= MIN_FONT_SIZE ? getResourceValue('sys.float.padding_level4') : '',
                        });
                        Row.width('100%');
                        Row.flexShrink(1);
                        Row.accessibilityGroup(this.isLeftAreaAccessibilityGroup());
                        Row.accessibilityText(this.getTitleAccessibilityText());
                        Row.accessibilityRole(this.title ? AccessibilityRoleType.TITLE_BAR : undefined);
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((c135, d135) => {
                        If.create();
                        if (this.isRightAreaExists()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.rightAreaParent.bind(this)();
                            });
                        } else {
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

    LoadingProcessStyle(v134 = null) {
        this.observeComponentCreation2((y134, z134) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.padding({
                top: getResourceValue('sys.float.padding_level2'),
                bottom: this.title?.secondaryTitle && this.title?.primaryTitle ?
                    getResourceValue('sys.float.subheader_right_loading_padding_bottom') :
                    getResourceValue('sys.float.subheader_single_right_loading_padding_bottom'),
            });
            Row.margin({
                start: LengthMetrics.vp(getResourceValue('sys.float.subheader_right_loading_margin_start')),
            });
        }, Row);
        this.observeComponentCreation2((w134, x134) => {
            LoadingProgress.create();
            LoadingProgress.width(OPERATE_ITEM_LENGTH());
            LoadingProgress.height(OPERATE_ITEM_LENGTH());
            LoadingProgress.color({
                'id': 125830992,
                'type': 10001,
                params: ['sys.color.icon_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
        }, LoadingProgress);
        Row.pop();
    }

    dummyFunction(s134 = null) {
        this.observeComponentCreation2((t134, u134) => {
            Row.create();
        }, Row);
        Row.pop();
    }

    updateStateVars(r134) {
        if (r134 === undefined) {
            return;
        }
        if ('icon' in r134) {
            this.updateParam('icon', r134.icon);
        }
        if ('title' in r134) {
            this.updateParam('title', r134.title);
        }
        if ('select' in r134) {
            this.updateParam('select', r134.select);
        }
        if ('operationType' in r134) {
            this.updateParam('operationType', r134.operationType);
        }
        if ('operationItems' in r134) {
            this.updateParam('operationItems', r134.operationItems);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], SubHeaderV2.prototype, 'icon', void 0);
__decorate([
    Param
], SubHeaderV2.prototype, 'title', void 0);
__decorate([
    Param
], SubHeaderV2.prototype, 'select', void 0);
__decorate([
    Param
], SubHeaderV2.prototype, 'operationType', void 0);
__decorate([
    Param
], SubHeaderV2.prototype, 'operationItems', void 0);
__decorate([
    Local
], SubHeaderV2.prototype, 'fontSize', void 0);
__decorate([
    Local
], SubHeaderV2.prototype, 'ageing', void 0);
__decorate([
    Local
], SubHeaderV2.prototype, 'textArrowBgColor', void 0);
__decorate([
    Local
], SubHeaderV2.prototype, 'buttonBgColor', void 0);
__decorate([
    Local
], SubHeaderV2.prototype, 'selectedIndex', void 0);
__decorate([
    Local
], SubHeaderV2.prototype, 'selectedContent', void 0);
__decorate([
    Local
], SubHeaderV2.prototype, 'symbolWidth', void 0);
__decorate([
    Local
], SubHeaderV2.prototype, 'subHeaderModifier', void 0);
__decorate([
    Provider('subHeaderV2Theme')
], SubHeaderV2.prototype, 'subHeaderV2Theme', void 0);
__decorate([
    Monitor('select')
], SubHeaderV2.prototype, 'infoChange', null);

class SymbolGlyphChild extends ViewV2 {
    constructor(l134, m134, n134, o134 = -1, p134, q134) {
        super(l134, o134, q134);
        this.initParam('icon', (m134 && 'icon' in m134) ? m134.icon : undefined);
        this.initParam('fontColor', (m134 && 'fontColor' in m134) ? m134.fontColor : undefined);
        this.changeSymbolWidth = 'changeSymbolWidth' in m134 ? m134.changeSymbolWidth : () => {
        };
        this.result = {
            width: 0,
            height: 0
        };
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(k134) {
        this.resetParam('icon', (k134 && 'icon' in k134) ? k134.icon : undefined);
        this.resetParam('fontColor', (k134 && 'fontColor' in k134) ? k134.fontColor : undefined);
        this.changeSymbolWidth = 'changeSymbolWidth' in k134 ? k134.changeSymbolWidth : () => {
        };
    }

    onMeasureSize(g134, h134, i134) {
        h134.forEach((j134) => {
            this.result = j134.measure(i134);
        });
        console.log(`zzzz Child onMeasureSize ${JSON.stringify(this.result)}`);
        this.changeSymbolWidth(this.result);
        return this.result;
    }

    initialRender() {
        this.observeComponentCreation2((e134, f134) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((c134, d134) => {
            SymbolGlyph.create(this.icon);
            SymbolGlyph.fontSize(getResourceValue('sys.float.subheader_left_icon_size') + 'vp');
            SymbolGlyph.fontColor(this.fontColor);
            SymbolGlyph.attributeModifier.bind(this)(this.icon);
            SymbolGlyph.margin({ end: LengthMetrics.vp(getResourceValue('sys.float.subheader_left_icon_end_margin')) });
            SymbolGlyph.flexShrink(0);
        }, SymbolGlyph);
        Column.pop();
    }

    updateStateVars(b134) {
        if (b134 === undefined) {
            return;
        }
        if ('icon' in b134) {
            this.updateParam('icon', b134.icon);
        }
        if ('fontColor' in b134) {
            this.updateParam('fontColor', b134.fontColor);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

__decorate([
    Param
], SymbolGlyphChild.prototype, 'icon', void 0);
__decorate([
    Param
], SymbolGlyphChild.prototype, 'fontColor', void 0);
__decorate([
    Event
], SymbolGlyphChild.prototype, 'changeSymbolWidth', void 0);

class SingleIconStyle extends ViewV2 {
    constructor(v133, w133, x133, y133 = -1, z133, a134) {
        super(v133, y133, a134);
        this.bgColor = {
            'id': 125829134,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.isFocus = false;
        this.initParam('item', (w133 && 'item' in w133) ? w133.item : null);
        this.subHeaderTheme = new SubHeaderTheme();
        this.initParam('isSingleIcon', (w133 && 'isSingleIcon' in w133) ? w133.isSingleIcon : true);
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(u133) {
        this.bgColor = {
            'id': 125829134,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.isFocus = false;
        this.resetParam('item', (u133 && 'item' in u133) ? u133.item : null);
        this.resetConsumer('subHeaderTheme', new SubHeaderTheme());
        this.resetParam('isSingleIcon', (u133 && 'isSingleIcon' in u133) ? u133.isSingleIcon : true);
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
        this.observeComponentCreation2((n133, o133) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p133, q133) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(true);
                        Button.defaultFocus(this.item.defaultFocus);
                        Button.width(SINGLE_ICON_ZONE_SIZE());
                        Button.height(SINGLE_ICON_ZONE_SIZE());
                        Button.align(Alignment.Center);
                        Button.backgroundColor(this.bgColor);
                        Button.borderRadius(getResourceValue('sys.float.subheader_right_icon_radius'));
                        Button.accessibilityLevel(this.getRightIconAccessibilityLevel());
                        Button.accessibilityText(this.getRightIconAccessibilityText());
                        Button.accessibilityDescription(this.getRightIconAccessibilityDescription());
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': 125831020,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                        Button.attributeModifier.bind(this)(!DEFAULT_FOCUS_STYLE() ? undefined :
                            new DefaultFocusStyleModifier((v11) => {
                                if (v11) {
                                    this.bgColor = {
                                        'id': 125831015,
                                        'type': 10001,
                                        params: ['sys.color.comp_background_focus'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                } else {
                                    this.bgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }));
                        Button.onTouch((u11) => {
                            if (u11.type === TouchType.Down || TouchType.Cancel) {
                                this.bgColor = {
                                    'id': 125831020,
                                    'type': 10001,
                                    params: ['sys.color.interactive_pressed'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            }
                            if (u11.type === TouchType.Up) {
                                this.bgColor = {
                                    'id': 125829134,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            }
                        });
                        Button.onHover((t11) => {
                            if (t11) {
                                this.bgColor = {
                                    'id': 125831019,
                                    'type': 10001,
                                    params: ['sys.color.interactive_hover'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            } else {
                                this.bgColor = {
                                    'id': 125829134,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            }
                        });
                        Button.responseRegion(this.iconResponseRegion());
                        Button.onClick((s11) => {
                            if (this.item?.action) {
                                this.item?.action();
                            }
                        });
                    }, Button);
                    this.IconZone.bind(this)();
                    Button.pop();
                });
            } else {
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

    IconZone(e133 = null) {
        this.observeComponentCreation2((f133, g133) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h133, i133) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((l133, m133) => {
                                    SymbolGlyph.create(this.item.iconOptions);
                                    SymbolGlyph.fontSize(RIGHT_SINGLE_ICON_SIZE());
                                    SymbolGlyph.fontColor([this.subHeaderTheme.rightIconColor]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.item.iconOptions);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.borderRadius(getResourceValue('sys.float.subheader_right_image_radius'));
                                    SymbolGlyph.padding(getResourceValue('sys.float.subheader_right_image_padding'));
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((j133, k133) => {
                                    Image.create(this.item?.iconOptions);
                                    Image.fillColor(this.subHeaderTheme.rightIconColor);
                                    Image.width(RIGHT_SINGLE_ICON_SIZE());
                                    Image.height(RIGHT_SINGLE_ICON_SIZE());
                                    Image.focusable(true);
                                    Image.draggable(false);
                                    Image.borderRadius(getResourceValue('sys.float.subheader_right_image_radius'));
                                    Image.padding(getResourceValue('sys.float.subheader_right_image_padding'));
                                    Image.attributeModifier.bind(this)(!DEFAULT_FOCUS_STYLE() ? undefined :
                                        new DefaultImageButtonFocusStyle());
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    updateStateVars(d133) {
        if (d133 === undefined) {
            return;
        }
        if ('item' in d133) {
            this.updateParam('item', d133.item);
        }
        if ('isSingleIcon' in d133) {
            this.updateParam('isSingleIcon', d133.isSingleIcon);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

__decorate([
    Local
], SingleIconStyle.prototype, 'bgColor', void 0);
__decorate([
    Local
], SingleIconStyle.prototype, 'isFocus', void 0);
__decorate([
    Param
], SingleIconStyle.prototype, 'item', void 0);
__decorate([
    Consumer('subHeaderV2Theme')
], SingleIconStyle.prototype, 'subHeaderTheme', void 0);
__decorate([
    Param
], SingleIconStyle.prototype, 'isSingleIcon', void 0);

class Util {
    static isSymbolResource(b133) {
        if (!Util.isResourceType(b133)) {
            return false;
        }
        if (b133 instanceof SymbolGlyphModifier) {
            return b133 instanceof SymbolGlyphModifier;
        }
        let c133 = b133;
        return c133.type === RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(a133) {
        if (!a133) {
            return false;
        }
        if (typeof a133 === 'string' || typeof a133 === 'undefined') {
            return false;
        }
        return true;
    }

    static getNumberByResource(u132, v132) {
        try {
            let z132 = resourceManager.getSystemResourceManager().getNumber(u132);
            if (z132 === 0) {
                return v132;
            } else {
                return z132;
            }
        } catch (w132) {
            let x132 = w132.code;
            let y132 = w132.message;
            hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${x132}, message: ${y132}`);
            return v132;
        }
    }

    static getStringByResource(o132, p132) {
        try {
            let t132 = getContext().resourceManager.getStringSync(o132);
            if (t132 === '') {
                return p132;
            } else {
                return t132;
            }
        } catch (q132) {
            let r132 = q132.code;
            let s132 = q132.message;
            hilog.error(0x3900, 'Ace', `SubHeader getStringByResource error, code: ${r132}, message: ${s132}`);
            return '';
        }
    }

    static numberToSize(m132) {
        if (typeof m132 === 'string') {
            const n132 = parseInt(m132);
            return n132;
        } else if (typeof m132 === 'number') {
            return m132;
        } else {
            return getContext().resourceManager.getNumber(m132);
        }
    }

    static symbolFontSize(l132) {
        return Util.numberToSize(l132) + 'vp';
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
RESOURCE_CACHE_MAP.set('sys.float.subheader_left_icon_size', { resourceId: 125835678, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_content_margin_start', { resourceId: 125835679, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_content_margin_end', { resourceId: 125835680, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_content_padding', { resourceId: 125835681, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_subtitle_padding', { resourceId: 125835682, defaultValue: 12 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_select_padding', { resourceId: 125835683, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_left_icon_end_margin', { resourceId: 125835684, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_subtitle_font_weight', { resourceId: 125835685, defaultValue: 400 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_titles_space', { resourceId: 125835686, defaultValue: 2 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_padding_horizontal',
    { resourceId: 125835784, defaultValue: 2 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_padding_vertical', { resourceId: 125835785, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_x_offset', { resourceId: 125835786, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_radius', { resourceId: 125835787, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_default_focus_style',
    { resourceId: 125835788, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_margin_start', { resourceId: 125835789, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_margin_bottom', { resourceId: 125835790, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_right_button_margin_bottom',
    { resourceId: 125835791, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_padding_vertical', { resourceId: 125835792, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_padding_start', { resourceId: 125835793, defaultValue: 2 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_font_arrow_space', { resourceId: 125835794, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_arrow_padding_horizontal',
    { resourceId: 125835795, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_arrow_x_offset', { resourceId: 125835796, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_arrow_margin_start', { resourceId: 125835797, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_arrow_height', { resourceId: 125835798, defaultValue: 24 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_arrow_width', { resourceId: 125835799, defaultValue: 12 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_arrow_margin_bottom',
    { resourceId: 125835800, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_right_text_arrow_margin_bottom',
    { resourceId: 125835801, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_arrow_radius', { resourceId: 125835802, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_only_arrow_margin_bottom',
    { resourceId: 125835803, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_icon_group_padding_start',
    { resourceId: 125835804, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_icon_group_margin_bottom',
    { resourceId: 125835805, defaultValue: 6 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_right_icon_group_margin_bottom',
    { resourceId: 125835806, defaultValue: 6 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_icon_group_x_offset', { resourceId: 125835807, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_icon_radius', { resourceId: 125835808, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_image_radius', { resourceId: 125835809, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_image_padding', { resourceId: 125835810, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_icon_zone_size', { resourceId: 125835811, defaultValue: 28 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_icon_size', { resourceId: 125835812, defaultValue: 24 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_loading_padding_bottom', { resourceId: 125835813, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_right_loading_padding_bottom',
    { resourceId: 125835814, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_loading_margin_start', { resourceId: 125835815, defaultValue: 8 });

function getResourceValue(j132) {
    if (RESOURCE_CACHE_MAP.hasKey(j132)) {
        let k132 = RESOURCE_CACHE_MAP.get(j132).resourceValue;
        if (typeof k132 === 'number') {
            return k132;
        } else {
            k132 = Util.getNumberByResource(RESOURCE_CACHE_MAP.get(j132).resourceId,
                RESOURCE_CACHE_MAP.get(j132).defaultValue);
            RESOURCE_CACHE_MAP.get(j132).resourceValue = k132;
            return k132;
        }
    }
    return 0;
}

class TextArrowLayout extends ViewPU {
    constructor(d132, e132, f132, g132 = -1, h132 = undefined, i132) {
        super(d132, f132, g132, i132);
        if (typeof h132 === 'function') {
            this.paramsGenerator_ = h132;
        }
        this.textArrowBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(e132);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(c132) {
        if (c132.textArrowBuilder !== undefined) {
            this.textArrowBuilder = c132.textArrowBuilder;
        }
    }

    updateStateVars(b132) {
    }

    purgeVariableDependenciesOnElmtId(a132) {
    }

    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(z131 = null) {
    }

    onPlaceChildren(s131, t131, u131) {
        let v131 = 0;
        let w131 = 0;
        for (let x131 = 0; x131 < t131.length; x131++) {
            let y131 = t131[x131];
            y131.layout({ x: v131, y: w131 });
        }
    }

    onMeasureSize(i131, j131, k131) {
        let l131 = ARROW_ICON_WIDTH();
        let m131 = OPERATE_ITEM_LENGTH();
        let n131 = j131[INDEX_ZERO];
        let o131 = {
            minWidth: Math.max(l131, Number(k131.minWidth)),
            maxWidth: k131.maxWidth,
            minHeight: Math.max(m131, Number(k131.minHeight)),
            maxHeight: k131.maxHeight,
        };
        let p131 = n131.measure(o131);
        l131 = Math.max(l131, p131.width);
        m131 = Math.max(m131, p131.height);
        let q131 = j131[INDEX_ONE];
        let r131 = {
            minWidth: l131,
            maxWidth: l131,
            minHeight: m131,
            maxHeight: m131,
        };
        q131.measure(r131);
        return { width: l131, height: m131 };
    }

    initialRender() {
        this.textArrowBuilder.bind(this)();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

function lazyInit(q11) {
    let r11 = null;
    return () => {
        if (r11 === null) {
            r11 = q11();
        }
        return r11;
    };
}

class DefaultFocusStyleModifier {
    constructor(p11) {
        this.stateStyleAction = p11;
    }

    applyNormalAttribute(o11) {
        if (!o11) {
            return;
        }
        o11.focusBox(undefined)
            .scale(undefined)
            .onFocus(() => {
                this.stateStyleAction && this.stateStyleAction(true);
            })
            .onBlur(() => {
                this.stateStyleAction && this.stateStyleAction(false);
            });
    }
}

class DefaultImageButtonFocusStyle {
    applyNormalAttribute(n11) {
        if (!n11) {
            return;
        }
        n11.borderRadius(getResourceValue('sys.float.padding_level2'))
            .focusBox({ margin: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) });
    }
}

export default {
    SubHeaderV2Title,
    SubHeaderV2Select,
    SubHeaderV2,
    SubHeaderV2OperationType,
    SubHeaderV2OperationItem
};