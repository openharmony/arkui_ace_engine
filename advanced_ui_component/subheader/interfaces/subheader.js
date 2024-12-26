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

export var OperationType;
(function (d19) {
    d19[d19['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
    d19[d19['BUTTON'] = 1] = 'BUTTON';
    d19[d19['ICON_GROUP'] = 2] = 'ICON_GROUP';
    d19[d19['LOADING'] = 3] = 'LOADING';
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

function __Text__secondaryTitleStyles(c19) {
    Text.fontSize(`${getResourceValue('sys.float.Subtitle_S')}fp`);
    Text.fontColor(c19?.fontColor ?? {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_secondary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    });
    Text.fontWeight(c19?.fontWeight);
    Text.maxLines(c19?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(c19?.alignment);
}

function __Text__primaryTitleStyles(b19) {
    Text.fontSize(`${getResourceValue('sys.float.subheader_title_font_size')}fp`);
    Text.fontColor(b19?.fontColor ?? {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    });
    Text.fontWeight(b19?.fontWeight);
    Text.maxLines(b19?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(b19?.alignment);
}

class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }

    applyNormalAttribute(a19) {
        if (this.isAgeing) {
            a19.width('100%');
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
    constructor(u18, v18, w18, x18 = -1, y18 = undefined, z18) {
        super(u18, w18, x18, z18);
        if (typeof y18 === 'function') {
            this.paramsGenerator_ = y18;
        }
        this.__icon = new SynchedPropertyObjectOneWayPU(v18.icon, this, 'icon');
        this.iconSymbolOptions = null;
        this.__primaryTitle = new SynchedPropertyObjectOneWayPU(v18.primaryTitle, this, 'primaryTitle');
        this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'primaryTitleModifier');
        this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(v18.secondaryTitle, this, 'secondaryTitle');
        this.__secondaryTitleModifier =
            new ObservedPropertyObjectPU(new TextModifier(), this, 'secondaryTitleModifier');
        this.__subHeaderModifier = new ObservedPropertyObjectPU(new SubHeaderModifier(), this, 'subHeaderModifier');
        this.select = null;
        this.__operationType = new SynchedPropertySimpleOneWayPU(v18.operationType, this, 'operationType');
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
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(v18.contentMargin, this, 'contentMargin');
        this.__contentPadding = new SynchedPropertyObjectOneWayPU(v18.contentPadding, this, 'contentPadding');
        this.subHeaderMargin = {
            start: LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
            end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
        };
        this.__subHeaderTheme = new ObservedPropertyObjectPU(new SubHeaderTheme(), this, 'subHeaderTheme');
        this.addProvidedVar('subHeaderTheme', this.__subHeaderTheme, false);
        this.isFollowingSystemFontScale = false;
        this.appMaxFontScale = 3.2;
        this.setInitiallyProvidedValue(v18);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(t18) {
        if (t18.icon === undefined) {
            this.__icon.set(null);
        }
        if (t18.iconSymbolOptions !== undefined) {
            this.iconSymbolOptions = t18.iconSymbolOptions;
        }
        if (t18.primaryTitle === undefined) {
            this.__primaryTitle.set(null);
        }
        if (t18.primaryTitleModifier !== undefined) {
            this.primaryTitleModifier = t18.primaryTitleModifier;
        }
        if (t18.secondaryTitle === undefined) {
            this.__secondaryTitle.set(null);
        }
        if (t18.secondaryTitleModifier !== undefined) {
            this.secondaryTitleModifier = t18.secondaryTitleModifier;
        }
        if (t18.subHeaderModifier !== undefined) {
            this.subHeaderModifier = t18.subHeaderModifier;
        }
        if (t18.select !== undefined) {
            this.select = t18.select;
        }
        if (t18.operationType === undefined) {
            this.__operationType.set(OperationType.BUTTON);
        }
        if (t18.operationItem !== undefined) {
            this.operationItem = t18.operationItem;
        }
        if (t18.operationSymbolOptions !== undefined) {
            this.operationSymbolOptions = t18.operationSymbolOptions;
        }
        if (t18.fontSize !== undefined) {
            this.fontSize = t18.fontSize;
        }
        if (t18.ageing !== undefined) {
            this.ageing = t18.ageing;
        }
        if (t18.textArrowBgColor !== undefined) {
            this.textArrowBgColor = t18.textArrowBgColor;
        }
        if (t18.buttonBgColor !== undefined) {
            this.buttonBgColor = t18.buttonBgColor;
        }
        if (t18.selectedIndex !== undefined) {
            this.selectedIndex = t18.selectedIndex;
        }
        if (t18.selectValue !== undefined) {
            this.selectValue = t18.selectValue;
        }
        if (t18.titleBuilder !== undefined) {
            this.titleBuilder = t18.titleBuilder;
        }
        if (t18.subHeaderMargin !== undefined) {
            this.subHeaderMargin = t18.subHeaderMargin;
        }
        if (t18.subHeaderTheme !== undefined) {
            this.subHeaderTheme = t18.subHeaderTheme;
        }
        if (t18.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = t18.isFollowingSystemFontScale;
        }
        if (t18.appMaxFontScale !== undefined) {
            this.appMaxFontScale = t18.appMaxFontScale;
        }
    }
    updateStateVars(s18) {
        this.__icon.reset(s18.icon);
        this.__primaryTitle.reset(s18.primaryTitle);
        this.__secondaryTitle.reset(s18.secondaryTitle);
        this.__operationType.reset(s18.operationType);
        this.__contentMargin.reset(s18.contentMargin);
        this.__contentPadding.reset(s18.contentPadding);
    }
    purgeVariableDependenciesOnElmtId(r18) {
        this.__icon.purgeDependencyOnElmtId(r18);
        this.__primaryTitle.purgeDependencyOnElmtId(r18);
        this.__primaryTitleModifier.purgeDependencyOnElmtId(r18);
        this.__secondaryTitle.purgeDependencyOnElmtId(r18);
        this.__secondaryTitleModifier.purgeDependencyOnElmtId(r18);
        this.__subHeaderModifier.purgeDependencyOnElmtId(r18);
        this.__operationType.purgeDependencyOnElmtId(r18);
        this.__fontSize.purgeDependencyOnElmtId(r18);
        this.__ageing.purgeDependencyOnElmtId(r18);
        this.__textArrowBgColor.purgeDependencyOnElmtId(r18);
        this.__buttonBgColor.purgeDependencyOnElmtId(r18);
        this.__selectedIndex.purgeDependencyOnElmtId(r18);
        this.__selectValue.purgeDependencyOnElmtId(r18);
        this.__contentMargin.purgeDependencyOnElmtId(r18);
        this.__contentPadding.purgeDependencyOnElmtId(r18);
        this.__subHeaderTheme.purgeDependencyOnElmtId(r18);
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

    set icon(q18) {
        this.__icon.set(q18);
    }

    get primaryTitle() {
        return this.__primaryTitle.get();
    }

    set primaryTitle(p18) {
        this.__primaryTitle.set(p18);
    }

    get primaryTitleModifier() {
        return this.__primaryTitleModifier.get();
    }

    set primaryTitleModifier(o18) {
        this.__primaryTitleModifier.set(o18);
    }

    get secondaryTitle() {
        return this.__secondaryTitle.get();
    }

    set secondaryTitle(n18) {
        this.__secondaryTitle.set(n18);
    }

    get secondaryTitleModifier() {
        return this.__secondaryTitleModifier.get();
    }

    set secondaryTitleModifier(m18) {
        this.__secondaryTitleModifier.set(m18);
    }

    get subHeaderModifier() {
        return this.__subHeaderModifier.get();
    }

    set subHeaderModifier(l18) {
        this.__subHeaderModifier.set(l18);
    }

    get operationType() {
        return this.__operationType.get();
    }

    set operationType(k18) {
        this.__operationType.set(k18);
    }

    get fontSize() {
        return this.__fontSize.get();
    }

    set fontSize(j18) {
        this.__fontSize.set(j18);
    }

    get ageing() {
        return this.__ageing.get();
    }

    set ageing(i18) {
        this.__ageing.set(i18);
    }

    get textArrowBgColor() {
        return this.__textArrowBgColor.get();
    }

    set textArrowBgColor(h18) {
        this.__textArrowBgColor.set(h18);
    }

    get buttonBgColor() {
        return this.__buttonBgColor.get();
    }

    set buttonBgColor(g18) {
        this.__buttonBgColor.set(g18);
    }

    get selectedIndex() {
        return this.__selectedIndex.get();
    }

    set selectedIndex(f18) {
        this.__selectedIndex.set(f18);
    }

    get selectValue() {
        return this.__selectValue.get();
    }

    set selectValue(e18) {
        this.__selectValue.set(e18);
    }

    get contentMargin() {
        return this.__contentMargin.get();
    }

    set contentMargin(d18) {
        this.__contentMargin.set(d18);
    }

    get contentPadding() {
        return this.__contentPadding.get();
    }

    set contentPadding(c18) {
        this.__contentPadding.set(c18);
    }

    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }

    set subHeaderTheme(b18) {
        this.__subHeaderTheme.set(b18);
    }

    onWillApplyTheme(a18) {
        this.subHeaderTheme.fontPrimaryColor = a18.colors.fontPrimary;
        this.subHeaderTheme.fontSecondaryColor = a18.colors.fontSecondary;
        this.subHeaderTheme.fontButtonColor = a18.colors.fontEmphasize;
        this.subHeaderTheme.iconArrowColor = a18.colors.iconTertiary;
        this.subHeaderTheme.textArrowHoverBgColor = a18.colors.interactiveHover;
        this.subHeaderTheme.borderFocusColor = a18.colors.interactiveFocus;
        this.subHeaderTheme.leftIconColor = a18.colors.iconSecondary;
        this.subHeaderTheme.rightIconColor = a18.colors.iconPrimary;
    }

    updateFontScale() {
        try {
            let y17 = this.getUIContext();
            let z17 = y17.getHostContext()?.config.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(z17, this.appMaxFontScale);
        } catch (v17) {
            let w17 = v17.code;
            let x17 = v17.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${w17}, message: ${x17}`);
            return 1;
        }
    }

    async aboutToAppear() {
        let u17 = this.getUIContext();
        this.isFollowingSystemFontScale = u17.isFollowingSystemFontScale();
        this.appMaxFontScale = u17.getMaxFontScale();
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
        this.observeComponentCreation2((g17, h17) => {
            If.create();
            if (this.isSuitableAging()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s17, t17) => {
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.padding(this.getAreaPadding());
                        Column.alignItems(HorizontalAlign.Start);
                    }, Column);
                    this.observeComponentCreation2((q17, r17) => {
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
                    this.observeComponentCreation2((o17, p17) => {
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
                    this.observeComponentCreation2((m17, n17) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.contentMargin ?? this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((k17, l17) => {
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
                    this.observeComponentCreation2((i17, j17) => {
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
    toStringFormat(b17) {
        if (typeof b17 === 'string' || typeof b17 === 'undefined') {
            return b17;
        }
        else {
            let c17 = '';
            try {
                c17 = getContext()?.resourceManager?.getStringSync(b17);
            }
            catch (d17) {
                let e17 = d17?.code;
                let f17 = d17?.message;
                hilog.error(0x3900, 'Ace', `Faild to subHeader toStringFormat, code: ${e17}, message: ${f17}`);
            }
            return c17;
        }
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
            return this.toStringFormat(this.operationItem[0].accessibilityText);
        }
        else {
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
            return this.toStringFormat(this.operationItem[0].accessibilityDescription);
        }
        return '';
    }

    rightAreaParentAging(s16 = null) {
        this.observeComponentCreation2((t16, u16) => {
            If.create();
            if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y16, z16) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItem ? true : false);
                        Button.align(Alignment.Start);
                        Button.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Button.onTouch((a17) => {
                            if (a17.type === TouchType.Down) {
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
                            if (a17.type === TouchType.Up || a17.type === TouchType.Cancel) {
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
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                        Button.accessibilityDescription(this.getAccessibilityDescription());
                    }, Button);
                    this.rightArea.bind(this)();
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((v16, w16) => {
                        Row.create();
                        Row.focusable(this.operationItem && this.operationType !== OperationType.LOADING ? true :
                            false);
                        Row.justifyContent(FlexAlign.Start);
                        Row.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Row.onTouch((x16) => {
                            if (x16.type === TouchType.Down) {
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
                            if (x16.type === TouchType.Up || x16.type === TouchType.Cancel) {
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

    rightAreaParent(j16 = null) {
        this.observeComponentCreation2((k16, l16) => {
            If.create();
            if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p16, q16) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItem ? true : false);
                        Button.margin(INDEX_ZERO);
                        Button.padding(INDEX_ZERO);
                        Button.align(Alignment.BottomEnd);
                        Button.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Button.onTouch((r16) => {
                            if (r16.type === TouchType.Down) {
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
                            if (r16.type === TouchType.Up || r16.type === TouchType.Cancel) {
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
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                        Button.accessibilityDescription(this.getAccessibilityDescription());
                    }, Button);
                    this.rightArea.bind(this)();
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((m16, n16) => {
                        Row.create();
                        Row.focusable(this.operationItem && this.operationType !== OperationType.LOADING ? true :
                            false);
                        Row.justifyContent(FlexAlign.End);
                        Row.alignItems(VerticalAlign.Bottom);
                        Row.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Row.onTouch((o16) => {
                            if (o16.type === TouchType.Down) {
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
                            if (o16.type === TouchType.Up || o16.type === TouchType.Cancel) {
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

    onMeasureSize(d16, e16, f16) {
        let g16 = { width: d16.width, height: d16.height };
        let h16 = this.getUIContext().getHostContext();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        } else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        e16.forEach((i16) => {
            f16.minHeight = Math.min(Number(this.getMinHeight()), Number(f16.maxHeight));
            g16.height = i16.measure(f16).height;
            g16.width = Number(f16.maxWidth);
        });
        return g16;
    }

    onPlaceChildren(z15, a16, b16) {
        a16.forEach((c16) => {
            c16.layout({ x: 0, y: 0 });
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
        }
        else if (this.secondaryTitle && this.primaryTitle) {
            return getResourceValue('sys.float.subheader_double_height');
        }
        else if (this.primaryTitle || this.select) {
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
        let y15 = {};
        if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
            (!this.primaryTitle && this.secondaryTitle))) {
            y15 = {
                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
            };
        }
        else if (this.select) {
            y15 = {
                top: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
                bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
            };
        }
        return y15;
    }

    leftArea(v15 = null) {
        this.observeComponentCreation2((w15, x15) => {
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
                        { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']) })
                    );
                });
            } else {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.dummyFunction.bind(this)();
                });
            }
        }, If);
        If.pop();
    }

    rightArea(m15 = null) {
        this.observeComponentCreation2((t15, u15) => {
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
        this.observeComponentCreation2((r15, s15) => {
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
        this.observeComponentCreation2((p15, q15) => {
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
        this.observeComponentCreation2((n15, o15) => {
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
    }

    IconSecondaryTitleStyle(a15, b15 = null) {
        this.observeComponentCreation2((k15, l15) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
            });
        }, Flex);
        this.observeComponentCreation2((e15, f15) => {
            If.create();
            if (Util.isSymbolResource(a15.iconOptions?.icon)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i15, j15) => {
                        SymbolGlyph.create(a15.iconOptions?.icon);
                        SymbolGlyph.fontSize(a15.iconOptions?.symbolicIconOption?.fontSize ?
                        Util.symbolFontSize(a15.iconOptions?.symbolicIconOption?.fontSize) : LEFT_ICON_SIZE);
                        SymbolGlyph.fontColor(a15.iconOptions?.symbolicIconOption?.fontColor ??
                            [this.subHeaderTheme.leftIconColor]);
                        SymbolGlyph.fontWeight(a15.iconOptions?.symbolicIconOption?.fontWeight);
                        SymbolGlyph.renderingStrategy(a15.iconOptions?.symbolicIconOption?.renderingStrategy);
                        SymbolGlyph.effectStrategy(a15.iconOptions?.symbolicIconOption?.effectStrategy);
                        SymbolGlyph.margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) });
                        SymbolGlyph.flexShrink(0);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((g15, h15) => {
                        Image.create(a15.iconOptions?.icon);
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
        this.observeComponentCreation2((c15, d15) => {
            Text.create(a15.content);
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

    SubTitleStyle(s14, t14 = null) {
        this.observeComponentCreation2((y14, z14) => {
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
        this.observeComponentCreation2((w14, x14) => {
            Text.create(s14.content);
            __Text__primaryTitleStyles({
                fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((u14, v14) => {
            Text.create(s14.subContent);
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

    SecondTitleStyle(o14, p14 = null) {
        this.observeComponentCreation2((q14, r14) => {
            Text.create(o14.content);
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

    SelectStyle(i14, j14 = null) {
        this.observeComponentCreation2((k14, l14) => {
            Select.create(i14.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
            Select.value(ObservedObject.GetRawObject(this.selectValue));
            Select.onSelect((m14, n14) => {
                this.selectedIndex = m14;
                if (n14) {
                    this.selectValue = n14;
                }
                if (i14.onSelect) {
                    i14.onSelect(m14, n14);
                }
            });
            Select.font({
                size: `${getResourceValue('sys.float.Body_L')}fp`,
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
    }

    PrimaryTitleStyle(e14, f14 = null) {
        this.observeComponentCreation2((g14, h14) => {
            Text.create(e14.content);
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

    ButtonStyle(v13, w13 = null) {
        this.observeComponentCreation2((x13, y13) => {
            If.create();
            if (v13) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b14, c14) => {
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
                        Button.onHover((d14) => {
                            if (d14) {
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
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                    }, Button);
                    this.observeComponentCreation2((z13, a14) => {
                        Text.create(v13.value);
                        __Text__secondaryTitleStyles({
                            fontWeight: FontWeight.Medium,
                            maxLines: DOUBLE_LINE_NUM,
                            fontColor: this.subHeaderTheme.fontButtonColor,
                        });
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

    TextStyle(n13, o13 = null) {
        this.observeComponentCreation2((t13, u13) => {
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
        this.observeComponentCreation2((p13, q13) => {
            If.create();
            if (n13) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r13, s13) => {
                        Text.create(n13.value);
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
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
    }

    ArrowStyle(i13 = null) {
        this.observeComponentCreation2((l13, m13) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((j13, k13) => {
            Image.create({
                'id': -1,
                'type': 20000,
                params: ['sys.media.ohos_ic_public_arrow_right'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Image.fillColor(this.subHeaderTheme.iconArrowColor);
            Image.width(ARROW_ICON_WIDTH);
            Image.height(OPERATE_ITEM_LENGTH);
            Image.focusable(true);
            Image.draggable(false);
            Image.matchTextDirection(true);
        }, Image);
        Row.pop();
    }

    TextArrowStyle(a12, b12 = null) {
        this.observeComponentCreation2((c12, d12) => {
            If.create();
            if (a12 && a12.value && a12.value.toString().length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g13, h13) => {
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
                    this.observeComponentCreation2((d13, e13) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.padding(INDEX_ZERO);
                        Button.margin({ start: this.leftIconMargin() });
                        Button.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        Button.borderRadius(getResourceValue('sys.float.corner_radius_level4'));
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                        Button.onHover((f13) => {
                            if (f13) {
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
                        this.observeComponentCreation2((l12, m12) => {
                            if (m12) {
                                let n12 = new TextArrowLayout(this, {
                                    textArrowBuilder: () => {
                                        this.observeComponentCreation2((w12, x12) => {
                                            ForEach.create();
                                            const y12 = z12 => {
                                                const a13 = z12;
                                                this.observeComponentCreation2((b13, c13) => {
                                                    If.create();
                                                    if (a13 === INDEX_ZERO) {
                                                        this.ifElseBranchUpdateFunction(0, () => {
                                                            this.TextStyle.bind(this)(a12);
                                                        });
                                                    } else {
                                                        this.ifElseBranchUpdateFunction(1, () => {
                                                            this.ArrowStyle.bind(this)();
                                                        });
                                                    }
                                                }, If);
                                                If.pop();
                                            };
                                            this.forEachUpdateFunction(w12, [INDEX_ZERO, INDEX_ONE], y12);
                                        }, ForEach);
                                        ForEach.pop();
                                    }
                                }, undefined, l12, () => { }, {
                                    page: 'library/src/main/ets/components/mainpage/MainPage.ets',
                                    line: 886,
                                    col: 11
                                });
                                ViewPU.create(n12);
                                let o12 = () => {
                                    return {
                                        textArrowBuilder: () => {
                                            this.observeComponentCreation2((p12, q12) => {
                                                ForEach.create();
                                                const r12 = s12 => {
                                                    const t12 = s12;
                                                    this.observeComponentCreation2((u12, v12) => {
                                                        If.create();
                                                        if (t12 === INDEX_ZERO) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.TextStyle.bind(this)(a12);
                                                            });
                                                        } else {
                                                            this.ifElseBranchUpdateFunction(1, () => {
                                                                this.ArrowStyle.bind(this)();
                                                            });
                                                        }
                                                    }, If);
                                                    If.pop();
                                                };
                                                this.forEachUpdateFunction(p12, [INDEX_ZERO, INDEX_ONE], r12);
                                            }, ForEach);
                                            ForEach.pop();
                                        }
                                    };
                                };
                                n12.paramsGenerator_ = o12;
                            } else {
                                this.updateStateVarsOfChildByElmtId(l12, {});
                            }
                        }, { name: 'TextArrowLayout' });
                    }
                    Button.pop();
                    Stack.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((j12, k12) => {
                        Row.create();
                        Row.focusable(true);
                        Row.constraintSize({ minWidth: this.getRightAreaMinWidth() });
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((g12, h12) => {
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
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                        Button.onHover((i12) => {
                            if (i12) {
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
                    this.observeComponentCreation2((e12, f12) => {
                        Image.create({
                            'id': -1,
                            'type': 20000,
                            params: ['sys.media.ohos_ic_public_arrow_right'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Image.fillColor(this.subHeaderTheme.iconArrowColor);
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

    IconGroupStyle(g11, h11 = null) {
        this.observeComponentCreation2((y11, z11) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((i11, j11) => {
            ForEach.create();
            const k11 = (l11, m11) => {
                const n11 = l11;
                this.observeComponentCreation2((o11, p11) => {
                    If.create();
                    if (Util.isResourceType(n11.value)) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((q11, r11) => {
                                If.create();
                                if (m11 <= INDEX_TWO) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((w11, x11) => {
                                            __Common__.create();
                                            __Common__.margin({
                                                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                                                bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level3')),
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((s11, t11) => {
                                                if (t11) {
                                                    let u11 = new SingleIconStyle(this, {
                                                        item: {
                                                            iconOptions: {
                                                                icon: n11.value,
                                                                symbolicIconOption: this.operationSymbolOptions &&
                                                                    this.operationSymbolOptions.length > m11 ?
                                                                this.operationSymbolOptions[m11] : null,
                                                            },
                                                            action: n11.action,
                                                            accessibilityLevel: n11.accessibilityLevel,
                                                            accessibilityText: n11.accessibilityText,
                                                            accessibilityDescription: n11.accessibilityDescription,
                                                        },
                                                        isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER,
                                                    }, undefined, s11, () => { }, {
                                                        page: 'library/src/main/ets/components/mainpage/MainPage.ets',
                                                        line: 976,
                                                        col: 13
                                                    });
                                                    ViewPU.create(u11);
                                                    let v11 = () => {
                                                        return {
                                                            item: {
                                                                iconOptions: {
                                                                    icon: n11.value,
                                                                    symbolicIconOption: this.operationSymbolOptions &&
                                                                        this.operationSymbolOptions.length > m11 ?
                                                                    this.operationSymbolOptions[m11] : null,
                                                                },
                                                                action: n11.action,
                                                                accessibilityLevel: n11.accessibilityLevel,
                                                                accessibilityText: n11.accessibilityText,
                                                                accessibilityDescription: n11.accessibilityDescription,
                                                            },
                                                            isSingleIcon: this.operationItem?.length ===
                                                                SINGLE_ICON_NUMBER
                                                        };
                                                    };
                                                    u11.paramsGenerator_ = v11;
                                                } else {
                                                    this.updateStateVarsOfChildByElmtId(s11, {});
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
                        });
                    } else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(i11, g11, k11, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    LoadingProcessStyle(b11 = null) {
        this.observeComponentCreation2((e11, f11) => {
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
        this.observeComponentCreation2((c11, d11) => {
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

    dummyFunction(y10 = null) {
        this.observeComponentCreation2((z10, a11) => {
            Row.create();
        }, Row);
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SingleIconStyle extends ViewPU {
    constructor(s10, t10, u10, v10 = -1, w10 = undefined, x10) {
        super(s10, u10, v10, x10);
        if (typeof w10 === 'function') {
            this.paramsGenerator_ = w10;
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
        this.setInitiallyProvidedValue(t10);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(r10) {
        if (r10.bgColor !== undefined) {
            this.bgColor = r10.bgColor;
        }
        if (r10.isFocus !== undefined) {
            this.isFocus = r10.isFocus;
        }
        if (r10.item !== undefined) {
            this.item = r10.item;
        }
        if (r10.isSingleIcon !== undefined) {
            this.isSingleIcon = r10.isSingleIcon;
        }
    }

    updateStateVars(q10) {
    }

    purgeVariableDependenciesOnElmtId(p10) {
        this.__bgColor.purgeDependencyOnElmtId(p10);
        this.__isFocus.purgeDependencyOnElmtId(p10);
        this.__subHeaderTheme.purgeDependencyOnElmtId(p10);
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

    set bgColor(o10) {
        this.__bgColor.set(o10);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(n10) {
        this.__isFocus.set(n10);
    }

    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }

    set subHeaderTheme(m10) {
        this.__subHeaderTheme.set(m10);
    }
    getRightIconAccessibilityText() {
        if (this.item?.accessibilityText) {
            let l10 = typeof this.item.accessibilityText === 'string' ? this.item.accessibilityText :
            getContext()?.resourceManager?.getStringSync(this.item.accessibilityText);
            return l10;
        }
        return '';
    }
    getRightIconAccessibilityLevel() {
        if (this.item?.accessibilityLevel && this.item?.accessibilityLevel !== '') {
            return this.item.accessibilityLevel;
        }
        return 'auto';
    }
    toStringFormat(g10) {
        if (typeof g10 === 'string' || typeof g10 === 'undefined') {
            return g10;
        }
        else {
            let h10 = '';
            try {
                h10 = getContext()?.resourceManager?.getStringSync(g10);
            }
            catch (i10) {
                let j10 = i10?.code;
                let k10 = i10?.message;
                hilog.error(0x3900, 'Ace', `Faild to subHeader toStringFormat, code: ${j10}, message: ${k10}`);
            }
            return h10;
        }
    }
    getRightIconAccessibilityDescription() {
        if (this.item?.accessibilityDescription && this.item?.accessibilityDescription !== '') {
            return this.toStringFormat(this.item?.accessibilityDescription);
        }
        return '';
    }
    initialRender() {
        this.observeComponentCreation2((z9, a10) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b10, c10) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(true);
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
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                        Button.onTouch((f10) => {
                            if (f10.type === TouchType.Down || TouchType.Cancel) {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.interactive_pressed'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                            if (f10.type === TouchType.Up) {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                        });
                        Button.onHover((e10) => {
                            if (e10) {
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
                        Button.onClick((d10) => {
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

    fontSizeValue(y9) {
        return y9.iconOptions?.symbolicIconOption?.fontSize ?
        Util.symbolFontSize(y9.iconOptions?.symbolicIconOption?.fontSize) : RIGHT_SINGLE_ICON_SIZE;
    }

    IconZone(p9 = null) {
        this.observeComponentCreation2((q9, r9) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s9, t9) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((w9, x9) => {
                                    SymbolGlyph.create(this.item.iconOptions?.icon);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.fontSize(this.fontSizeValue(this.item));
                                    SymbolGlyph.fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ??
                                        [this.subHeaderTheme.rightIconColor]);
                                    SymbolGlyph.fontWeight(this.item.iconOptions?.symbolicIconOption?.fontWeight);
                                    SymbolGlyph.renderingStrategy(
                                        this.item.iconOptions?.symbolicIconOption?.renderingStrategy);
                                    SymbolGlyph.effectStrategy(
                                        this.item.iconOptions?.symbolicIconOption?.effectStrategy);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((u9, v9) => {
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
    static isSymbolResource(n9) {
        if (!Util.isResourceType(n9)) {
            return false;
        }
        let o9 = n9;
        return o9.type === RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(m9) {
        if (!m9) {
            return false;
        }
        if (typeof m9 === 'string' || typeof m9 === 'undefined') {
            return false;
        }
        return true;
    }

    static getNumberByResource(g9, h9) {
        try {
            let l9 = resourceManager.getSystemResourceManager().getNumber(g9);
            if (l9 === 0) {
                return h9;
            } else {
                return l9;
            }
        } catch (i9) {
            let j9 = i9.code;
            let k9 = i9.message;
            hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${j9}, message: ${k9}`);
            return 0;
        }
    }

    static getStringByResource(a9, b9) {
        try {
            let f9 = getContext().resourceManager.getStringSync(a9);
            if (f9 === '') {
                return b9;
            } else {
                return f9;
            }
        } catch (c9) {
            let d9 = c9.code;
            let e9 = c9.message;
            hilog.error(0x3900, 'Ace', `SubHeader getStringByResource error, code: ${d9}, message: ${e9}`);
            return '';
        }
    }

    static numberToSize(y8) {
        if (typeof y8 === 'string') {
            const z8 = parseInt(y8);
            return z8;
        } else if (typeof y8 === 'number') {
            return y8;
        } else {
            return getContext().resourceManager.getNumber(y8);
        }
    }

    static symbolFontSize(x8) {
        return Util.numberToSize(x8) + 'vp';
    }
}

function getResourceValue(v8) {
    if (RESOURCE_CACHE_MAP.hasKey(v8)) {
        let w8 = RESOURCE_CACHE_MAP.get(v8).resourceValue;
        if (typeof w8 === 'number') {
            return w8;
        } else {
            w8 = Util.getNumberByResource(RESOURCE_CACHE_MAP.get(v8).resourceId,
                RESOURCE_CACHE_MAP.get(v8).defaultValue);
            RESOURCE_CACHE_MAP.get(v8).resourceValue = w8;
            return w8;
        }
    }
    return 0;
}

class TextArrowLayout extends ViewPU {
    constructor(p8, q8, r8, s8 = -1, t8 = undefined, u8) {
        super(p8, r8, s8, u8);
        if (typeof t8 === 'function') {
            this.paramsGenerator_ = t8;
        }
        this.textArrowBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(q8);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(o8) {
        if (o8.textArrowBuilder !== undefined) {
            this.textArrowBuilder = o8.textArrowBuilder;
        }
    }

    updateStateVars(n8) {
    }

    purgeVariableDependenciesOnElmtId(m8) {
    }

    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(l8 = null) {
    }

    onPlaceChildren(e8, f8, g8) {
        let h8 = 0;
        let i8 = 0;
        for (let j8 = 0; j8 < f8.length; j8++) {
            let k8 = f8[j8];
            k8.layout({ x: h8, y: i8 });
        }
    }

    onMeasureSize(s3, y3, d4) {
        let j4 = ARROW_ICON_WIDTH;
        let l5 = OPERATE_ITEM_LENGTH;
        let f6 = y3[INDEX_ZERO];
        let j6 = {
            minWidth: Math.max(j4, Number(d4.minWidth)),
            maxWidth: d4.maxWidth,
            minHeight: Math.max(l5, Number(d4.minHeight)),
            maxHeight: d4.maxHeight,
        };
        let o6 = f6.measure(j6);
        j4 = Math.max(j4, o6.width);
        l5 = Math.max(l5, o6.height);
        let c8 = y3[INDEX_ONE];
        let d8 = {
            minWidth: j4,
            maxWidth: j4,
            minHeight: l5,
            maxHeight: l5,
        };
        c8.measure(d8);
        return { width: j4, height: l5 };
    }

    initialRender() {
        this.textArrowBuilder.bind(this)();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default { OperationType, SubHeader };