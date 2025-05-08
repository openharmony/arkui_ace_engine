/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

var _a;
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
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;

const INDEX_ZERO = 0;
const INDEX_ONE = 1;
const INDEX_TWO = 2;
const DEFAULT_FONT_SCALE = 1;
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

export var OperationType;
(function (l16) {
    l16[l16['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
    l16[l16['BUTTON'] = 1] = 'BUTTON';
    l16[l16['ICON_GROUP'] = 2] = 'ICON_GROUP';
    l16[l16['LOADING'] = 3] = 'LOADING';
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
        this.fontPrimaryColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.fontSecondaryColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.fontButtonColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_emphasize'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.iconArrowColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.icon_tertiary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.textArrowHoverBgColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.interactive_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.borderFocusColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.interactive_focus'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.leftIconColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.icon_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.rightIconColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.icon_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
    }
}

function __Text__secondaryTitleStyles(k16) {
    Text.fontSize(`${getResourceValue('sys.float.Subtitle_S')}fp`);
    Text.fontColor(k16?.fontColor ?? {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_secondary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    });
    Text.fontWeight(k16?.fontWeight);
    Text.maxLines(k16?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(k16?.alignment);
}

function __Text__primaryTitleStyles(j16) {
    Text.fontSize(`${getResourceValue('sys.float.subheader_title_font_size')}fp`);
    Text.fontColor(j16?.fontColor ?? {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    });
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
        } else {
        }
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

export class SubHeader extends ViewPU {
    constructor(c16, d16, e16, f16 = -1, g16 = undefined, h16) {
        super(c16, e16, f16, h16);
        if (typeof g16 === 'function') {
            this.paramsGenerator_ = g16;
        }
        this.__icon = new SynchedPropertyObjectOneWayPU(d16.icon, this, 'icon');
        this.iconSymbolOptions = null;
        this.__primaryTitle = new SynchedPropertyObjectOneWayPU(d16.primaryTitle, this, 'primaryTitle');
        this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'primaryTitleModifier');
        this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(d16.secondaryTitle, this, 'secondaryTitle');
        this.__secondaryTitleModifier =
            new ObservedPropertyObjectPU(new TextModifier(), this, 'secondaryTitleModifier');
        this.__subHeaderModifier = new ObservedPropertyObjectPU(new SubHeaderModifier(), this, 'subHeaderModifier');
        this.select = null;
        this.__operationType = new SynchedPropertySimpleOneWayPU(d16.operationType, this, 'operationType');
        this.operationItem = null;
        this.operationSymbolOptions = null;
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.__ageing = new ObservedPropertySimplePU(true, this, 'ageing');
        this.__textArrowBgColor = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'textArrowBgColor');
        this.__buttonBgColor = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'buttonBgColor');
        this.__selectedIndex = new ObservedPropertyObjectPU(-1, this, 'selectedIndex');
        this.__selectValue = new ObservedPropertyObjectPU('', this, 'selectValue');
        this.titleBuilder = undefined;
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(d16.contentMargin, this, 'contentMargin');
        this.__contentPadding = new SynchedPropertyObjectOneWayPU(d16.contentPadding, this, 'contentPadding');
        this.subHeaderMargin = {
            start: LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
            end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
        };
        this.__subHeaderTheme = new ObservedPropertyObjectPU(new SubHeaderTheme(), this, 'subHeaderTheme');
        this.addProvidedVar('subHeaderTheme', this.__subHeaderTheme, false);
        this.isFollowingSystemFontScale = false;
        this.appMaxFontScale = 3.2;
        this.setInitiallyProvidedValue(d16);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(b16) {
        if (b16.icon === undefined) {
            this.__icon.set(null);
        }
        if (b16.iconSymbolOptions !== undefined) {
            this.iconSymbolOptions = b16.iconSymbolOptions;
        }
        if (b16.primaryTitle === undefined) {
            this.__primaryTitle.set(null);
        }
        if (b16.primaryTitleModifier !== undefined) {
            this.primaryTitleModifier = b16.primaryTitleModifier;
        }
        if (b16.secondaryTitle === undefined) {
            this.__secondaryTitle.set(null);
        }
        if (b16.secondaryTitleModifier !== undefined) {
            this.secondaryTitleModifier = b16.secondaryTitleModifier;
        }
        if (b16.subHeaderModifier !== undefined) {
            this.subHeaderModifier = b16.subHeaderModifier;
        }
        if (b16.select !== undefined) {
            this.select = b16.select;
        }
        if (b16.operationType === undefined) {
            this.__operationType.set(OperationType.BUTTON);
        }
        if (b16.operationItem !== undefined) {
            this.operationItem = b16.operationItem;
        }
        if (b16.operationSymbolOptions !== undefined) {
            this.operationSymbolOptions = b16.operationSymbolOptions;
        }
        if (b16.fontSize !== undefined) {
            this.fontSize = b16.fontSize;
        }
        if (b16.ageing !== undefined) {
            this.ageing = b16.ageing;
        }
        if (b16.textArrowBgColor !== undefined) {
            this.textArrowBgColor = b16.textArrowBgColor;
        }
        if (b16.buttonBgColor !== undefined) {
            this.buttonBgColor = b16.buttonBgColor;
        }
        if (b16.selectedIndex !== undefined) {
            this.selectedIndex = b16.selectedIndex;
        }
        if (b16.selectValue !== undefined) {
            this.selectValue = b16.selectValue;
        }
        if (b16.titleBuilder !== undefined) {
            this.titleBuilder = b16.titleBuilder;
        }
        if (b16.subHeaderMargin !== undefined) {
            this.subHeaderMargin = b16.subHeaderMargin;
        }
        if (b16.subHeaderTheme !== undefined) {
            this.subHeaderTheme = b16.subHeaderTheme;
        }
        if (b16.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = b16.isFollowingSystemFontScale;
        }
        if (b16.appMaxFontScale !== undefined) {
            this.appMaxFontScale = b16.appMaxFontScale;
        }
    }

    updateStateVars(a16) {
        this.__icon.reset(a16.icon);
        this.__primaryTitle.reset(a16.primaryTitle);
        this.__secondaryTitle.reset(a16.secondaryTitle);
        this.__operationType.reset(a16.operationType);
        this.__contentMargin.reset(a16.contentMargin);
        this.__contentPadding.reset(a16.contentPadding);
    }

    purgeVariableDependenciesOnElmtId(z15) {
        this.__icon.purgeDependencyOnElmtId(z15);
        this.__primaryTitle.purgeDependencyOnElmtId(z15);
        this.__primaryTitleModifier.purgeDependencyOnElmtId(z15);
        this.__secondaryTitle.purgeDependencyOnElmtId(z15);
        this.__secondaryTitleModifier.purgeDependencyOnElmtId(z15);
        this.__subHeaderModifier.purgeDependencyOnElmtId(z15);
        this.__operationType.purgeDependencyOnElmtId(z15);
        this.__fontSize.purgeDependencyOnElmtId(z15);
        this.__ageing.purgeDependencyOnElmtId(z15);
        this.__textArrowBgColor.purgeDependencyOnElmtId(z15);
        this.__buttonBgColor.purgeDependencyOnElmtId(z15);
        this.__selectedIndex.purgeDependencyOnElmtId(z15);
        this.__selectValue.purgeDependencyOnElmtId(z15);
        this.__contentMargin.purgeDependencyOnElmtId(z15);
        this.__contentPadding.purgeDependencyOnElmtId(z15);
        this.__subHeaderTheme.purgeDependencyOnElmtId(z15);
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
        this.__selectedIndex.aboutToBeDeleted();
        this.__selectValue.aboutToBeDeleted();
        this.__contentMargin.aboutToBeDeleted();
        this.__contentPadding.aboutToBeDeleted();
        this.__subHeaderTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get icon() {
        return this.__icon.get();
    }

    set icon(y15) {
        this.__icon.set(y15);
    }

    get primaryTitle() {
        return this.__primaryTitle.get();
    }

    set primaryTitle(x15) {
        this.__primaryTitle.set(x15);
    }

    get primaryTitleModifier() {
        return this.__primaryTitleModifier.get();
    }

    set primaryTitleModifier(w15) {
        this.__primaryTitleModifier.set(w15);
    }

    get secondaryTitle() {
        return this.__secondaryTitle.get();
    }

    set secondaryTitle(v15) {
        this.__secondaryTitle.set(v15);
    }

    get secondaryTitleModifier() {
        return this.__secondaryTitleModifier.get();
    }

    set secondaryTitleModifier(u15) {
        this.__secondaryTitleModifier.set(u15);
    }

    get subHeaderModifier() {
        return this.__subHeaderModifier.get();
    }

    set subHeaderModifier(t15) {
        this.__subHeaderModifier.set(t15);
    }

    get operationType() {
        return this.__operationType.get();
    }

    set operationType(s15) {
        this.__operationType.set(s15);
    }

    get fontSize() {
        return this.__fontSize.get();
    }

    set fontSize(r15) {
        this.__fontSize.set(r15);
    }

    get ageing() {
        return this.__ageing.get();
    }

    set ageing(q15) {
        this.__ageing.set(q15);
    }

    get textArrowBgColor() {
        return this.__textArrowBgColor.get();
    }

    set textArrowBgColor(p15) {
        this.__textArrowBgColor.set(p15);
    }

    get buttonBgColor() {
        return this.__buttonBgColor.get();
    }

    set buttonBgColor(o15) {
        this.__buttonBgColor.set(o15);
    }

    get selectedIndex() {
        return this.__selectedIndex.get();
    }

    set selectedIndex(n15) {
        this.__selectedIndex.set(n15);
    }

    get selectValue() {
        return this.__selectValue.get();
    }

    set selectValue(m15) {
        this.__selectValue.set(m15);
    }

    get contentMargin() {
        return this.__contentMargin.get();
    }

    set contentMargin(l15) {
        this.__contentMargin.set(l15);
    }

    get contentPadding() {
        return this.__contentPadding.get();
    }

    set contentPadding(k15) {
        this.__contentPadding.set(k15);
    }

    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }

    set subHeaderTheme(j15) {
        this.__subHeaderTheme.set(j15);
    }

    onWillApplyTheme(i15) {
        this.subHeaderTheme.fontPrimaryColor = i15.colors.fontPrimary;
        this.subHeaderTheme.fontSecondaryColor = i15.colors.fontSecondary;
        this.subHeaderTheme.fontButtonColor = i15.colors.fontEmphasize;
        this.subHeaderTheme.iconArrowColor = i15.colors.iconTertiary;
        this.subHeaderTheme.textArrowHoverBgColor = i15.colors.interactiveHover;
        this.subHeaderTheme.borderFocusColor = i15.colors.interactiveFocus;
        this.subHeaderTheme.leftIconColor = i15.colors.iconSecondary;
        this.subHeaderTheme.rightIconColor = i15.colors.iconPrimary;
    }

    updateFontScale() {
        try {
            let g15 = this.getUIContext();
            let h15 = g15?.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(h15, this.appMaxFontScale);
        } catch (d15) {
            let e15 = d15.code;
            let f15 = d15.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${e15}, message: ${f15}`);
            return 1;
        }
    }

    async aboutToAppear() {
        let c15 = this.getUIContext();
        this.isFollowingSystemFontScale = c15.isFollowingSystemFontScale();
        this.appMaxFontScale = c15.getMaxFontScale();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        } else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        if (this.select) {
            this.selectedIndex = this.select.selected;
            this.selectValue = this.select.value;
        }
    }

    isSuitableAging() {
        return (this.fontSize >= MIN_FONT_SIZE) && ((this.operationType === OperationType.TEXT_ARROW) ||
            this.operationType === OperationType.BUTTON) && this.operationItem &&
            (this.operationItem?.length > 0) && this.operationItem[0].value !== '';
    }

    isLeftAreaAccessibilityGroup() {
        if (this.titleBuilder || this.secondaryTitle) {
            return true;
        }
        if (this.select) {
            return false;
        }
        return true;
    }

    initialRender() {
        this.observeComponentCreation2((c14, d14) => {
            If.create();
            if (this.isSuitableAging()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a15, b15) => {
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.padding(this.getAreaPadding());
                        Column.alignItems(HorizontalAlign.Start);
                    }, Column);
                    this.observeComponentCreation2((y14, z14) => {
                        Row.create();
                        Row.margin({
                            top: LengthMetrics.vp(getResourceValue('sys.float.padding_level8')),
                            bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level1')),
                        });
                        Row.padding({
                            start: this.contentMargin ? this.contentMargin.start :
                            LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
                            end: this.contentMargin ? this.contentMargin.end :
                            LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
                        });
                        Row.width('100%');
                        Row.accessibilityGroup(this.isLeftAreaAccessibilityGroup());
                        Row.accessibilityDescription(this.select ? '' : Util.getStringByResource(125834353, ''));
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((u14, v14) => {
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
                    this.observeComponentCreation2((o14, p14) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.contentMargin ?? this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((m14, n14) => {
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
                    this.observeComponentCreation2((i14, j14) => {
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

    isRightAreaExists() {
        if (this.operationItem && this.operationItem.length > 0) {
            return true;
        }
        if (this.operationType === OperationType.LOADING) {
            return true;
        }
        return false;
    }

    getRightAreaAccessibilityLevel() {
        if (this.operationItem[0].accessibilityLevel && this.operationItem[0].accessibilityLevel !== '') {
            return this.operationItem[0].accessibilityLevel;
        }
        return 'yes';
    }

    getRightAreaAccessibilityText() {
        if (!this.operationItem || this.operationItem.length <= 0) {
            return '';
        }
        if (this.operationItem[0].accessibilityText && this.operationItem[0].accessibilityText !== '') {
            return this.operationItem[0].accessibilityText;
        } else {
            if (this.operationType === OperationType.TEXT_ARROW && this.operationItem[0].value.toString().length <= 0) {
                return Util.getStringByResource(125833704, '');
            }
        }
        return '';
    }

    getAccessibilityDescription() {
        if (!this.operationItem || this.operationItem.length <= 0) {
            return '';
        }
        if (this.operationItem[0].accessibilityDescription && this.operationItem[0].accessibilityDescription !== '') {
            return this.operationItem[0].accessibilityDescription;
        }
        return '';
    }

    rightAreaParentAging(f13 = null) {
        this.observeComponentCreation2((h13, i13) => {
            If.create();
            if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u13, v13) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItem ? true : false);
                        Button.align(Alignment.Start);
                        Button.onKeyEvent((a14) => {
                            if (!a14) {
                                return;
                            }
                            if ((a14.keyCode === KeyCode.KEYCODE_SPACE || a14.keyCode === KeyCode.KEYCODE_ENTER) &&
                                a14.type === KeyType.Down) {
                                if ((this.operationType === OperationType.TEXT_ARROW ||
                                    this.operationType === OperationType.BUTTON) &&
                                this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                    this.operationItem[0].action();
                                }
                                a14.stopPropagation();
                            }
                        });
                        Button.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Button.onTouch((z13) => {
                            if (z13.type === TouchType.Down) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                            }
                            if (z13.type === TouchType.Up || z13.type === TouchType.Cancel) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                            }
                        });
                        Button.margin({
                            bottom: getResourceValue('sys.float.padding_level4'),
                        });
                        Button.padding({
                            start: LengthMetrics.vp((this.contentMargin ?
                                (this.contentMargin.start ? this.contentMargin.start.value : 0) :
                            getResourceValue('sys.float.margin_left')) - PADDING_LEFT),
                            end: this.contentMargin ? this.contentMargin.end :
                            LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
                        });
                        Button.accessibilityLevel(this.operationType === OperationType.BUTTON ||
                            this.operationType === OperationType.TEXT_ARROW ?
                        this.getRightAreaAccessibilityLevel() : 'no');
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_sub_background_transparent'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
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
                    this.observeComponentCreation2((l13, m13) => {
                        Row.create();
                        Row.focusable(this.operationItem && this.operationType !== OperationType.LOADING ? true :
                            false);
                        Row.justifyContent(FlexAlign.Start);
                        Row.onKeyEvent((r13) => {
                            if (!r13) {
                                return;
                            }
                            if ((r13.keyCode === KeyCode.KEYCODE_SPACE || r13.keyCode === KeyCode.KEYCODE_ENTER) &&
                                r13.type === KeyType.Down) {
                                if ((this.operationType === OperationType.TEXT_ARROW ||
                                    this.operationType === OperationType.BUTTON) &&
                                this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                    this.operationItem[0].action();
                                }
                                r13.stopPropagation();
                            }
                        });
                        Row.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Row.onTouch((q13) => {
                            if (q13.type === TouchType.Down) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                            }
                            if (q13.type === TouchType.Up || q13.type === TouchType.Cancel) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                            }
                        });
                        Row.margin({
                            bottom: getResourceValue('sys.float.padding_level4'),
                        });
                        Row.padding({
                            start: LengthMetrics.vp((this.contentMargin ?
                                (this.contentMargin.start ? this.contentMargin.start.value : 0) :
                            getResourceValue('sys.float.margin_left')) - PADDING_LEFT),
                            end: this.contentMargin ? this.contentMargin.end :
                            LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
                        });
                        Row.accessibilityLevel(this.operationType === OperationType.BUTTON ||
                            this.operationType === OperationType.TEXT_ARROW ?
                        this.getRightAreaAccessibilityLevel() : 'no');
                    }, Row);
                    this.rightArea.bind(this)();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }

    rightAreaParent(j12 = null) {
        this.observeComponentCreation2((l12, m12) => {
            If.create();
            if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y12, z12) => {
                        Button.createWithChild({
                            type: ButtonType.Normal,
                            buttonStyle: ButtonStyleMode.TEXTUAL,
                            stateEffect: false
                        });
                        Button.focusable(this.operationItem ? true : false);
                        Button.margin(INDEX_ZERO);
                        Button.padding(INDEX_ZERO);
                        Button.align(Alignment.BottomEnd);
                        Button.onKeyEvent((e13) => {
                            if (!e13) {
                                return;
                            }
                            if ((e13.keyCode === KeyCode.KEYCODE_SPACE || e13.keyCode === KeyCode.KEYCODE_ENTER) &&
                                e13.type === KeyType.Down) {
                                if ((this.operationType === OperationType.TEXT_ARROW ||
                                    this.operationType === OperationType.BUTTON) &&
                                this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                    this.operationItem[0].action();
                                }
                                e13.stopPropagation();
                            }
                        });
                        Button.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Button.onTouch((d13) => {
                            if (d13.type === TouchType.Down) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                            }
                            if (d13.type === TouchType.Up || d13.type === TouchType.Cancel) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
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
                        Button.accessibilityLevel(this.operationType === OperationType.BUTTON ||
                            this.operationType === OperationType.TEXT_ARROW ?
                        this.getRightAreaAccessibilityLevel() : 'no');
                        Button.hoverEffect(HoverEffect.None);
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_sub_background_transparent'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
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
                    this.observeComponentCreation2((p12, q12) => {
                        Row.create();
                        Row.focusable(this.operationItem && this.operationType !== OperationType.LOADING ? true :
                            false);
                        Row.justifyContent(FlexAlign.End);
                        Row.alignItems(VerticalAlign.Bottom);
                        Row.onKeyEvent((v12) => {
                            if (!v12) {
                                return;
                            }
                            if ((v12.keyCode === KeyCode.KEYCODE_SPACE || v12.keyCode === KeyCode.KEYCODE_ENTER) &&
                                v12.type === KeyType.Down) {
                                if ((this.operationType === OperationType.TEXT_ARROW ||
                                    this.operationType === OperationType.BUTTON) &&
                                this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                    this.operationItem[0].action();
                                }
                                v12.stopPropagation();
                            }
                        });
                        Row.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Row.onTouch((u12) => {
                            if (u12.type === TouchType.Down) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                            }
                            if (u12.type === TouchType.Up || u12.type === TouchType.Cancel) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
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
                        Row.accessibilityLevel(this.operationType === OperationType.BUTTON ||
                            this.operationType === OperationType.TEXT_ARROW ?
                        this.getRightAreaAccessibilityLevel() : 'no');
                    }, Row);
                    this.rightArea.bind(this)();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }

    onMeasureSize(c12, d12, e12) {
        let f12 = { width: c12.width, height: c12.height };
        let g12 = this.getUIContext()?.getHostContext();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        } else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        d12.forEach((i12) => {
            e12.minHeight = Math.min(Number(this.getMinHeight()), Number(e12.maxHeight));
            f12.height = i12?.measure(e12).height;
            f12.width = Number(e12.maxWidth);
        });
        return f12;
    }

    onPlaceChildren(x11, y11, z11) {
        y11.forEach((b12) => {
            b12.layout({ x: 0, y: 0 });
        });
    }

    getRightAreaMaxWidth() {
        if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
            return '100%';
        }
        return MAX_RIGHT_WIDTH;
    }

    getRightAreaMinWidth() {
        if (this.operationItem && this.operationItem.length > 0) {
            return MIN_HOT_AREA_LENGTH;
        }
        return 0;
    }

    getMinHeight() {
        if (this.secondaryTitle && this.icon) {
            return getResourceValue('sys.float.subheader_single_subtitle_height');
        } else if (this.secondaryTitle && this.primaryTitle) {
            return getResourceValue('sys.float.subheader_double_height');
        } else if (this.primaryTitle || this.select) {
            return getResourceValue('sys.float.subheader_single_title_height');
        }
        return getResourceValue('sys.float.subheader_single_subtitle_height');
    }

    getTextArrowPaddingLeft() {
        if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
            return LengthMetrics.vp(getResourceValue('sys.float.padding_level1'));
        }
        return LengthMetrics.vp(getResourceValue('sys.float.padding_level0'));
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
        let w11 = {};
        if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
            (!this.primaryTitle && this.secondaryTitle))) {
            w11 = {
                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
            };
        } else if (this.select) {
            w11 = {
                top: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
                bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
            };
        }
        return w11;
    }

    leftArea(l11 = null) {
        this.observeComponentCreation2((n11, o11) => {
            If.create();
            if (this.titleBuilder) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.titleBuilder.bind(this)();
                });
            } else if (this.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondaryTitleStyle', {
                        content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']),
                        iconOptions: () => ({
                            icon: this.icon,
                            symbolicIconOption: this.iconSymbolOptions,
                        })
                    }));
                });
            } else if (this.secondaryTitle && this.primaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle', {
                        content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']),
                        subContent: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle'])
                    }));
                });
            } else if (this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle', {
                        content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle'])
                    }));
                });
            } else if (this.select) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.SelectStyle.bind(this)(this.select);
                });
            } else if (this.primaryTitle) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle',
                        { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']) }));
                });
            } else {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.dummyFunction.bind(this)();
                });
            }
        }, If);
        If.pop();
    }

    rightArea(l10 = null) {
        this.observeComponentCreation2((h11, i11) => {
            If.create();
            if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)(this.operationItem[0]);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((d11, e11) => {
            If.create();
            if (this.operationType === OperationType.TEXT_ARROW &&
                (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextArrowStyle.bind(this)(this.operationItem[0]);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((z10, a11) => {
            If.create();
            if (this.operationType === OperationType.ICON_GROUP &&
                (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconGroupStyle.bind(this)(this.operationItem);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((v10, w10) => {
            If.create();
            if (this.operationType === OperationType.LOADING) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.LoadingProcessStyle.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((r10, s10) => {
            If.create();
            if (this.operationType === undefined && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)(this.operationItem[0]);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    IconSecondaryTitleStyle(s9, t9 = null) {
        this.observeComponentCreation2((j10, k10) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
            });
        }, Flex);
        this.observeComponentCreation2((z9, a10) => {
            If.create();
            if (Util.isSymbolResource(s9.iconOptions?.icon)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h10, i10) => {
                        SymbolGlyph.create(s9.iconOptions?.icon);
                        SymbolGlyph.fontSize(s9.iconOptions?.symbolicIconOption?.fontSize ?
                        Util.symbolFontSize(s9.iconOptions?.symbolicIconOption?.fontSize) : LEFT_ICON_SIZE);
                        SymbolGlyph.fontColor(s9.iconOptions?.symbolicIconOption?.fontColor ??
                            [this.subHeaderTheme.leftIconColor]);
                        SymbolGlyph.fontWeight(s9.iconOptions?.symbolicIconOption?.fontWeight);
                        SymbolGlyph.renderingStrategy(s9.iconOptions?.symbolicIconOption?.renderingStrategy);
                        SymbolGlyph.effectStrategy(s9.iconOptions?.symbolicIconOption?.effectStrategy);
                        SymbolGlyph.margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) });
                        SymbolGlyph.flexShrink(0);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((d10, e10) => {
                        Image.create(s9.iconOptions?.icon);
                        Image.fillColor(this.subHeaderTheme.leftIconColor);
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
        this.observeComponentCreation2((x9, y9) => {
            Text.create(s9.content);
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

    SubTitleStyle(h9, i9 = null) {
        this.observeComponentCreation2((q9, r9) => {
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
        this.observeComponentCreation2((o9, p9) => {
            Text.create(h9.content);
            __Text__primaryTitleStyles({
                fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((m9, n9) => {
            Text.create(h9.subContent);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Regular,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.margin({
                top: getResourceValue('sys.float.padding_level1'),
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
        }, Text);
        Text.pop();
        Column.pop();
    }

    SecondTitleStyle(c9, d9 = null) {
        this.observeComponentCreation2((f9, g9) => {
            Text.create(c9.content);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
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

    SelectStyle(u8, v8 = null) {
        this.observeComponentCreation2((x8, y8) => {
            Select.create(u8.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
            Select.value(ObservedObject.GetRawObject(this.selectValue));
            Select.defaultFocus(u8.defaultFocus);
            Select.onSelect((a9, b9) => {
                this.selectedIndex = a9;
                if (b9) {
                    this.selectValue = b9;
                }
                if (u8.onSelect) {
                    u8.onSelect(a9, b9);
                }
            });
            Select.font({
                size: `${getResourceValue('sys.float.Body_L')}fp`,
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
    }

    PrimaryTitleStyle(p8, q8 = null) {
        this.observeComponentCreation2((s8, t8) => {
            Text.create(p8.content);
            __Text__primaryTitleStyles({
                fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
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

    ButtonStyle(a8, b8 = null) {
        this.observeComponentCreation2((d8, e8) => {
            If.create();
            if (a8) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l8, m8) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(true);
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
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
                        Button.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
                        Button.constraintSize({ minHeight: OPERATE_ITEM_LENGTH });
                        Button.align(Alignment.End);
                        Button.borderRadius(getResourceValue('sys.float.corner_radius_level4'));
                        Button.onHover((o8) => {
                            if (o8) {
                                this.buttonBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                            } else {
                                this.buttonBgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        ViewStackProcessor.visualState();
                    }, Button);
                    this.observeComponentCreation2((j8, k8) => {
                        Text.create(a8.value);
                        __Text__secondaryTitleStyles({
                            fontWeight: FontWeight.Medium,
                            maxLines: DOUBLE_LINE_NUM,
                            fontColor: this.subHeaderTheme.fontButtonColor,
                        });
                        Text.defaultFocus(a8.defaultFocus);
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

    leftIconMargin() {
        if (this.titleBuilder) {
            return LengthMetrics.vp(0);
        }
        if (this.icon && Util.isSymbolResource(this.icon)) {
            return this.ageing ? LengthMetrics.vp((this.iconSymbolOptions?.fontSize ?
            Util.numberToSize(this.iconSymbolOptions?.fontSize) : LEFT_ICON_SIZE_NUMBER) +
                LEFT_TEXT_NUMBER) : LengthMetrics.vp(0);
        } else {
            return (this.ageing && this.icon) ? LengthMetrics.vp(LEFT_ICON_SIZE_NUMBER +
                LEFT_TEXT_NUMBER) : LengthMetrics.vp(0);
        }
    }

    TextStyle(n7, o7 = null) {
        this.observeComponentCreation2((y7, z7) => {
            Row.create();
            Row.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.subHeaderModifier));
            Row.alignItems(VerticalAlign.Center);
            Row.focusable(true);
            Row.constraintSize({ minHeight: OPERATE_ITEM_LENGTH });
            Row.padding({
                start: this.getTextArrowPaddingLeft(),
                top: this.ageing ? LengthMetrics.vp(0) : LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
                bottom: this.ageing ? LengthMetrics.vp(0) :
                LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
            });
        }, Row);
        this.observeComponentCreation2((r7, s7) => {
            If.create();
            if (n7) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w7, x7) => {
                        Text.create(n7.value);
                        __Text__secondaryTitleStyles({
                            maxLines: DOUBLE_LINE_NUM,
                            fontWeight: FontWeight.Regular,
                            alignment: Alignment.End,
                            fontColor: this.subHeaderTheme.fontSecondaryColor,
                        });
                        Text.focusable(true);
                        Text.defaultFocus(n7.defaultFocus);
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

    ArrowStyle(g7 = null) {
        this.observeComponentCreation2((l7, m7) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((j7, k7) => {
            SymbolGlyph.create({
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.chevron_right'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            SymbolGlyph.fontSize(RIGHT_SINGLE_ICON_SIZE);
            SymbolGlyph.fontColor([this.subHeaderTheme.iconArrowColor]);
            SymbolGlyph.draggable(false);
            SymbolGlyph.width(ARROW_ICON_WIDTH);
            SymbolGlyph.height(OPERATE_ITEM_LENGTH);
        }, SymbolGlyph);
        Row.pop();
    }

    TextArrowStyle(b5, c5 = null) {
        this.observeComponentCreation2((e5, f5) => {
            If.create();
            if (b5 && b5.value && b5.value.toString().length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e7, f7) => {
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
                    this.observeComponentCreation2((a7, b7) => {
                        Button.createWithChild({
                            type: ButtonType.Normal,
                            buttonStyle: ButtonStyleMode.TEXTUAL,
                            stateEffect: false
                        });
                        Button.padding(INDEX_ZERO);
                        Button.margin({ start: this.leftIconMargin() });
                        Button.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        Button.borderRadius(getResourceValue('sys.float.corner_radius_level4'));
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        ViewStackProcessor.visualState();
                        Button.onHover((d7) => {
                            if (d7) {
                                this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                            } else {
                                this.textArrowBgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                        });
                    }, Button);
                    {
                        this.observeComponentCreation2((w5, x5) => {
                            if (x5) {
                                let y5 = new TextArrowLayout(this, {
                                    textArrowBuilder: () => {
                                        this.observeComponentCreation2((p6, q6) => {
                                            ForEach.create();
                                            const r6 = t6 => {
                                                const u6 = t6;
                                                this.observeComponentCreation2((w6, x6) => {
                                                    If.create();
                                                    if (u6 === INDEX_ZERO) {
                                                        this.ifElseBranchUpdateFunction(0, () => {
                                                            this.TextStyle.bind(this)(b5);
                                                        });
                                                    } else {
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
                                }, undefined, w5, () => {
                                }, { page: 'library/src/main/ets/components/MainPage.ets', line: 896, col: 11 });
                                ViewPU.create(y5);
                                let z5 = () => {
                                    return {
                                        textArrowBuilder: () => {
                                            this.observeComponentCreation2((d6, e6) => {
                                                ForEach.create();
                                                const f6 = h6 => {
                                                    const i6 = h6;
                                                    this.observeComponentCreation2((k6, l6) => {
                                                        If.create();
                                                        if (i6 === INDEX_ZERO) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.TextStyle.bind(this)(b5);
                                                            });
                                                        } else {
                                                            this.ifElseBranchUpdateFunction(1, () => {
                                                                this.ArrowStyle.bind(this)();
                                                            });
                                                        }
                                                    }, If);
                                                    If.pop();
                                                };
                                                this.forEachUpdateFunction(d6, [INDEX_ZERO, INDEX_ONE], f6);
                                            }, ForEach);
                                            ForEach.pop();
                                        }
                                    };
                                };
                                y5.paramsGenerator_ = z5;
                            } else {
                                this.updateStateVarsOfChildByElmtId(w5, {});
                            }
                        }, { name: 'TextArrowLayout' });
                    }
                    Button.pop();
                    Stack.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((q5, r5) => {
                        Row.create();
                        Row.focusable(true);
                        Row.constraintSize({ minWidth: this.getRightAreaMinWidth() });
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((m5, n5) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.width(ARROW_ICON_WIDTH);
                        Button.height(OPERATE_ITEM_LENGTH);
                        Button.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        Button.borderRadius(getResourceValue('sys.float.corner_radius_level4'));
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        ViewStackProcessor.visualState();
                        Button.onHover((p5) => {
                            if (p5) {
                                this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                            } else {
                                this.textArrowBgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
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
                    this.observeComponentCreation2((k5, l5) => {
                        SymbolGlyph.create({
                            'id': -1,
                            'type': 40000,
                            params: ['sys.symbol.chevron_right'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.fontSize(RIGHT_SINGLE_ICON_SIZE);
                        SymbolGlyph.fontColor([this.subHeaderTheme.iconArrowColor]);
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

    IconGroupStyle(z3, a4 = null) {
        this.observeComponentCreation2((z4, a5) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((d4, e4) => {
            ForEach.create();
            const f4 = (h4, i4) => {
                const j4 = h4;
                this.observeComponentCreation2((l4, m4) => {
                    If.create();
                    if (i4 <= INDEX_TWO) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((x4, y4) => {
                                __Common__.create();
                                __Common__.margin({
                                    start: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                                    bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level3')),
                                });
                            }, __Common__);
                            {
                                this.observeComponentCreation2((r4, s4) => {
                                    if (s4) {
                                        let t4 = new SingleIconStyle(this, {
                                            item: {
                                                iconOptions: {
                                                    icon: j4.value,
                                                    symbolicIconOption: this.operationSymbolOptions &&
                                                        this.operationSymbolOptions.length > i4 ?
                                                    this.operationSymbolOptions[i4] : null,
                                                },
                                                action: j4.action,
                                                defaultFocus: j4.defaultFocus,
                                                accessibilityLevel: j4.accessibilityLevel,
                                                accessibilityText: j4.accessibilityText,
                                                accessibilityDescription: j4.accessibilityDescription,
                                            },
                                            isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER,
                                        }, undefined, r4, () => {
                                        }, {
                                            page: 'library/src/main/ets/components/MainPage.ets',
                                            line: 985,
                                            col: 13
                                        });
                                        ViewPU.create(t4);
                                        let u4 = () => {
                                            return {
                                                item: {
                                                    iconOptions: {
                                                        icon: j4.value,
                                                        symbolicIconOption: this.operationSymbolOptions &&
                                                            this.operationSymbolOptions.length > i4 ?
                                                        this.operationSymbolOptions[i4] : null,
                                                    },
                                                    action: j4.action,
                                                    defaultFocus: j4.defaultFocus,
                                                    accessibilityLevel: j4.accessibilityLevel,
                                                    accessibilityText: j4.accessibilityText,
                                                    accessibilityDescription: j4.accessibilityDescription,
                                                },
                                                isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER
                                            };
                                        };
                                        t4.paramsGenerator_ = u4;
                                    } else {
                                        this.updateStateVarsOfChildByElmtId(r4, {});
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
            this.forEachUpdateFunction(d4, z3, f4, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    LoadingProcessStyle(s3 = null) {
        this.observeComponentCreation2((x3, y3) => {
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
        this.observeComponentCreation2((v3, w3) => {
            LoadingProgress.create();
            LoadingProgress.width(OPERATE_ITEM_LENGTH);
            LoadingProgress.height(OPERATE_ITEM_LENGTH);
            LoadingProgress.color({
                'id': -1,
                'type': 10001,
                params: ['sys.color.icon_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
        }, LoadingProgress);
        Row.pop();
    }

    dummyFunction(o3 = null) {
        this.observeComponentCreation2((q3, r3) => {
            Row.create();
        }, Row);
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SingleIconStyle extends ViewPU {
    constructor(i3, j3, k3, l3 = -1, m3 = undefined, n3) {
        super(i3, k3, l3, n3);
        if (typeof m3 === 'function') {
            this.paramsGenerator_ = m3;
        }
        this.__bgColor = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'bgColor');
        this.__isFocus = new ObservedPropertySimplePU(false, this, 'isFocus');
        this.item = null;
        this.__subHeaderTheme = this.initializeConsume('subHeaderTheme', 'subHeaderTheme');
        this.isSingleIcon = true;
        this.setInitiallyProvidedValue(j3);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(h3) {
        if (h3.bgColor !== undefined) {
            this.bgColor = h3.bgColor;
        }
        if (h3.isFocus !== undefined) {
            this.isFocus = h3.isFocus;
        }
        if (h3.item !== undefined) {
            this.item = h3.item;
        }
        if (h3.isSingleIcon !== undefined) {
            this.isSingleIcon = h3.isSingleIcon;
        }
    }

    updateStateVars(g3) {
    }

    purgeVariableDependenciesOnElmtId(f3) {
        this.__bgColor.purgeDependencyOnElmtId(f3);
        this.__isFocus.purgeDependencyOnElmtId(f3);
        this.__subHeaderTheme.purgeDependencyOnElmtId(f3);
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

    set bgColor(e3) {
        this.__bgColor.set(e3);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(d3) {
        this.__isFocus.set(d3);
    }

    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }

    set subHeaderTheme(c3) {
        this.__subHeaderTheme.set(c3);
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
                        Button.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
                        Button.borderRadius(getResourceValue('sys.float.corner_radius_level4'));
                        Button.accessibilityLevel(this.getRightIconAccessibilityLevel());
                        Button.accessibilityText(this.getRightIconAccessibilityText());
                        Button.accessibilityDescription(this.getRightIconAccessibilityDescription());
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        ViewStackProcessor.visualState();
                        Button.onTouch((a3) => {
                            if (a3.type === TouchType.Down || TouchType.Cancel) {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.interactive_pressed'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                            if (a3.type === TouchType.Up) {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                        });
                        Button.onHover((z2) => {
                            if (z2) {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.interactive_hover'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            } else {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
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

    fontSizeValue(m2) {
        return m2.iconOptions?.symbolicIconOption?.fontSize ?
        Util.symbolFontSize(m2.iconOptions?.symbolicIconOption?.fontSize) : RIGHT_SINGLE_ICON_SIZE;
    }

    IconZone(v1 = null) {
        this.observeComponentCreation2((x1, y1) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c2, d2) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((k2, l2) => {
                                    SymbolGlyph.create(this.item.iconOptions?.icon);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.fontSize(this.fontSizeValue(this.item));
                                    SymbolGlyph.fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ??
                                        [this.subHeaderTheme.rightIconColor]);
                                    SymbolGlyph.fontWeight(this.item.iconOptions?.symbolicIconOption?.fontWeight);
                                    SymbolGlyph.renderingStrategy(this.item.iconOptions?.symbolicIconOption?.renderingStrategy);
                                    SymbolGlyph.effectStrategy(this.item.iconOptions?.symbolicIconOption?.effectStrategy);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((g2, h2) => {
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
            } else {
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
    static isSymbolResource(t1) {
        if (!Util.isResourceType(t1)) {
            return false;
        }
        let u1 = t1;
        return u1?.type === RESOURCE_TYPE_SYMBOL;
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
            } else {
                return r1;
            }
        } catch (o1) {
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
            } else {
                return l1;
            }
        } catch (i1) {
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
        } else if (typeof e1 === 'number') {
            return e1;
        } else {
            return getContext().resourceManager.getNumber(e1);
        }
    }

    static symbolFontSize(d1) {
        return Util.numberToSize(d1) + 'vp';
    }
}

function getResourceValue(b1) {
    if (RESOURCE_CACHE_MAP.hasKey(b1)) {
        let c1 = RESOURCE_CACHE_MAP.get(b1).resourceValue;
        if (typeof c1 === 'number') {
            return c1;
        } else {
            c1 = Util.getNumberByResource(RESOURCE_CACHE_MAP.get(b1).resourceId,
                RESOURCE_CACHE_MAP.get(b1).defaultValue);
            RESOURCE_CACHE_MAP.get(b1).resourceValue = c1;
            return c1;
        }
    }
    return 0;
}

class TextArrowLayout extends ViewPU {
    constructor(v, w, x, y = -1, z = undefined, a1) {
        super(v, x, y, a1);
        if (typeof z === 'function') {
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
        i?.measure(j);
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
    OperationType, SubHeader
};