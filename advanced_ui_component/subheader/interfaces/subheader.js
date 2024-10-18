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
(function (j18) {
    j18[j18['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
    j18[j18['BUTTON'] = 1] = 'BUTTON';
    j18[j18['ICON_GROUP'] = 2] = 'ICON_GROUP';
    j18[j18['LOADING'] = 3] = 'LOADING';
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

function __Text__secondaryTitleStyles(u17) {
    Text.fontSize(`${getResourceValue('sys.float.Subtitle_S')}fp`);
    Text.fontColor(u17?.fontColor ?? {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_secondary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    });
    Text.fontWeight(u17?.fontWeight);
    Text.maxLines(u17?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(u17?.alignment);
}

function __Text__primaryTitleStyles(r17) {
    Text.fontSize(`${getResourceValue('sys.float.subheader_title_font_size')}fp`);
    Text.fontColor(r17?.fontColor ?? {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    });
    Text.fontWeight(r17?.fontWeight);
    Text.maxLines(r17?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(r17?.alignment);
}

class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }

    applyNormalAttribute(x14) {
        if (this.isAgeing) {
            x14.width('100%');
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
    constructor(u10, v10, w10, x10 = -1, y10 = undefined, y11) {
        super(u10, w10, x10, y11);
        if (typeof y10 === 'function') {
            this.paramsGenerator_ = y10;
        }
        this.__icon = new SynchedPropertyObjectOneWayPU(v10.icon, this, 'icon');
        this.iconSymbolOptions = null;
        this.__primaryTitle = new SynchedPropertyObjectOneWayPU(v10.primaryTitle, this, 'primaryTitle');
        this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'primaryTitleModifier');
        this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(v10.secondaryTitle, this, 'secondaryTitle');
        this.__secondaryTitleModifier =
            new ObservedPropertyObjectPU(new TextModifier(), this, 'secondaryTitleModifier');
        this.__subHeaderModifier = new ObservedPropertyObjectPU(new SubHeaderModifier(), this, 'subHeaderModifier');
        this.select = null;
        this.__operationType = new SynchedPropertySimpleOneWayPU(v10.operationType, this, 'operationType');
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
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(v10.contentMargin, this, 'contentMargin');
        this.__contentPadding = new SynchedPropertyObjectOneWayPU(v10.contentPadding, this, 'contentPadding');
        this.subHeaderMargin = {
            start: LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
            end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
        };
        this.__subHeaderTheme = new ObservedPropertyObjectPU(new SubHeaderTheme(), this, 'subHeaderTheme');
        this.addProvidedVar('subHeaderTheme', this.__subHeaderTheme, false);
        this.isFollowingSystemFontScale = false;
        this.appMaxFontScale = 3.2;
        this.setInitiallyProvidedValue(v10);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(t10) {
        if (t10.icon === undefined) {
            this.__icon.set(null);
        }
        if (t10.iconSymbolOptions !== undefined) {
            this.iconSymbolOptions = t10.iconSymbolOptions;
        }
        if (t10.primaryTitle === undefined) {
            this.__primaryTitle.set(null);
        }
        if (t10.primaryTitleModifier !== undefined) {
            this.primaryTitleModifier = t10.primaryTitleModifier;
        }
        if (t10.secondaryTitle === undefined) {
            this.__secondaryTitle.set(null);
        }
        if (t10.secondaryTitleModifier !== undefined) {
            this.secondaryTitleModifier = t10.secondaryTitleModifier;
        }
        if (t10.subHeaderModifier !== undefined) {
            this.subHeaderModifier = t10.subHeaderModifier;
        }
        if (t10.select !== undefined) {
            this.select = t10.select;
        }
        if (t10.operationType === undefined) {
            this.__operationType.set(OperationType.BUTTON);
        }
        if (t10.operationItem !== undefined) {
            this.operationItem = t10.operationItem;
        }
        if (t10.operationSymbolOptions !== undefined) {
            this.operationSymbolOptions = t10.operationSymbolOptions;
        }
        if (t10.fontSize !== undefined) {
            this.fontSize = t10.fontSize;
        }
        if (t10.ageing !== undefined) {
            this.ageing = t10.ageing;
        }
        if (t10.textArrowBgColor !== undefined) {
            this.textArrowBgColor = t10.textArrowBgColor;
        }
        if (t10.buttonBgColor !== undefined) {
            this.buttonBgColor = t10.buttonBgColor;
        }
        if (t10.selectedIndex !== undefined) {
            this.selectedIndex = t10.selectedIndex;
        }
        if (t10.selectValue !== undefined) {
            this.selectValue = t10.selectValue;
        }
        if (t10.titleBuilder !== undefined) {
            this.titleBuilder = t10.titleBuilder;
        }
        if (t10.subHeaderMargin !== undefined) {
            this.subHeaderMargin = t10.subHeaderMargin;
        }
        if (t10.subHeaderTheme !== undefined) {
            this.subHeaderTheme = t10.subHeaderTheme;
        }
        if (t10.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = t10.isFollowingSystemFontScale;
        }
        if (t10.appMaxFontScale !== undefined) {
            this.appMaxFontScale = t10.appMaxFontScale;
        }
    }

    updateStateVars(s10) {
        this.__icon.reset(s10.icon);
        this.__primaryTitle.reset(s10.primaryTitle);
        this.__secondaryTitle.reset(s10.secondaryTitle);
        this.__operationType.reset(s10.operationType);
        this.__contentMargin.reset(s10.contentMargin);
        this.__contentPadding.reset(s10.contentPadding);
    }

    purgeVariableDependenciesOnElmtId(r10) {
        this.__icon.purgeDependencyOnElmtId(r10);
        this.__primaryTitle.purgeDependencyOnElmtId(r10);
        this.__primaryTitleModifier.purgeDependencyOnElmtId(r10);
        this.__secondaryTitle.purgeDependencyOnElmtId(r10);
        this.__secondaryTitleModifier.purgeDependencyOnElmtId(r10);
        this.__subHeaderModifier.purgeDependencyOnElmtId(r10);
        this.__operationType.purgeDependencyOnElmtId(r10);
        this.__fontSize.purgeDependencyOnElmtId(r10);
        this.__ageing.purgeDependencyOnElmtId(r10);
        this.__textArrowBgColor.purgeDependencyOnElmtId(r10);
        this.__buttonBgColor.purgeDependencyOnElmtId(r10);
        this.__selectedIndex.purgeDependencyOnElmtId(r10);
        this.__selectValue.purgeDependencyOnElmtId(r10);
        this.__contentMargin.purgeDependencyOnElmtId(r10);
        this.__contentPadding.purgeDependencyOnElmtId(r10);
        this.__subHeaderTheme.purgeDependencyOnElmtId(r10);
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

    set icon(q10) {
        this.__icon.set(q10);
    }

    get primaryTitle() {
        return this.__primaryTitle.get();
    }

    set primaryTitle(p10) {
        this.__primaryTitle.set(p10);
    }

    get primaryTitleModifier() {
        return this.__primaryTitleModifier.get();
    }

    set primaryTitleModifier(o10) {
        this.__primaryTitleModifier.set(o10);
    }

    get secondaryTitle() {
        return this.__secondaryTitle.get();
    }

    set secondaryTitle(n10) {
        this.__secondaryTitle.set(n10);
    }

    get secondaryTitleModifier() {
        return this.__secondaryTitleModifier.get();
    }

    set secondaryTitleModifier(m10) {
        this.__secondaryTitleModifier.set(m10);
    }

    get subHeaderModifier() {
        return this.__subHeaderModifier.get();
    }

    set subHeaderModifier(l10) {
        this.__subHeaderModifier.set(l10);
    }

    get operationType() {
        return this.__operationType.get();
    }

    set operationType(k10) {
        this.__operationType.set(k10);
    }

    get fontSize() {
        return this.__fontSize.get();
    }

    set fontSize(j10) {
        this.__fontSize.set(j10);
    }

    get ageing() {
        return this.__ageing.get();
    }

    set ageing(i10) {
        this.__ageing.set(i10);
    }

    get textArrowBgColor() {
        return this.__textArrowBgColor.get();
    }

    set textArrowBgColor(h10) {
        this.__textArrowBgColor.set(h10);
    }

    get buttonBgColor() {
        return this.__buttonBgColor.get();
    }

    set buttonBgColor(g10) {
        this.__buttonBgColor.set(g10);
    }

    get selectedIndex() {
        return this.__selectedIndex.get();
    }

    set selectedIndex(f10) {
        this.__selectedIndex.set(f10);
    }

    get selectValue() {
        return this.__selectValue.get();
    }

    set selectValue(e10) {
        this.__selectValue.set(e10);
    }

    get contentMargin() {
        return this.__contentMargin.get();
    }

    set contentMargin(d10) {
        this.__contentMargin.set(d10);
    }

    get contentPadding() {
        return this.__contentPadding.get();
    }

    set contentPadding(c10) {
        this.__contentPadding.set(c10);
    }

    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }

    set subHeaderTheme(b10) {
        this.__subHeaderTheme.set(b10);
    }

    onWillApplyTheme(a10) {
        this.subHeaderTheme.fontPrimaryColor = a10.colors.fontPrimary;
        this.subHeaderTheme.fontSecondaryColor = a10.colors.fontSecondary;
        this.subHeaderTheme.fontButtonColor = a10.colors.fontEmphasize;
        this.subHeaderTheme.iconArrowColor = a10.colors.iconTertiary;
        this.subHeaderTheme.textArrowHoverBgColor = a10.colors.interactiveHover;
        this.subHeaderTheme.borderFocusColor = a10.colors.interactiveFocus;
        this.subHeaderTheme.leftIconColor = a10.colors.iconSecondary;
        this.subHeaderTheme.rightIconColor = a10.colors.iconPrimary;
    }

    updateFontScale() {
        try {
            let y9 = this.getUIContext();
            let z9 = y9.getHostContext()?.config.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(z9, this.appMaxFontScale);
        } catch (v9) {
            let w9 = v9.code;
            let x9 = v9.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${w9}, message: ${x9}`);
            return 1;
        }
    }

    async aboutToAppear() {
        let u9 = this.getUIContext();
        this.isFollowingSystemFontScale = u9.isFollowingSystemFontScale();
        this.appMaxFontScale = u9.getMaxFontScale();
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
        this.observeComponentCreation2((g9, h9) => {
            If.create();
            if (this.isSuitableAging()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s9, t9) => {
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.padding(this.getAreaPadding());
                        Column.alignItems(HorizontalAlign.Start);
                    }, Column);
                    this.observeComponentCreation2((q9, r9) => {
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
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((o9, p9) => {
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
                    this.observeComponentCreation2((m9, n9) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.contentMargin ?? this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((k9, l9) => {
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
                    this.observeComponentCreation2((i9, j9) => {
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

    getRightAreaAccessibilityText() {
        if (this.operationType !== OperationType.TEXT_ARROW || !this.operationItem || this.operationItem.length <= 0) {
            return '';
        }
        if (this.operationItem[0].value.toString().length <= 0) {
            return Util.getStringByResource(125833704, '');
        }
        return '';
    }

    rightAreaParentAging(x8 = null) {
        this.observeComponentCreation2((y8, z8) => {
            If.create();
            if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d9, e9) => {
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
                        Button.onTouch((f9) => {
                            if (f9.type === TouchType.Down) {
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
                            if (f9.type === TouchType.Up || f9.type === TouchType.Cancel) {
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
                            'yes' : 'no');
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_sub_background_transparent'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Button.hoverEffect(HoverEffect.None);
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                    }, Button);
                    this.rightArea.bind(this)();
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((a9, b9) => {
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
                        Row.onTouch((c9) => {
                            if (c9.type === TouchType.Down) {
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
                            if (c9.type === TouchType.Up || c9.type === TouchType.Cancel) {
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
                            'yes' : 'no');
                    }, Row);
                    this.rightArea.bind(this)();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }

    rightAreaParent(o8 = null) {
        this.observeComponentCreation2((p8, q8) => {
            If.create();
            if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u8, v8) => {
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
                        Button.onTouch((w8) => {
                            if (w8.type === TouchType.Down) {
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
                            if (w8.type === TouchType.Up || w8.type === TouchType.Cancel) {
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
                            'yes' : 'no');
                        Button.hoverEffect(HoverEffect.None);
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_sub_background_transparent'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                    }, Button);
                    this.rightArea.bind(this)();
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((r8, s8) => {
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
                        Row.onTouch((t8) => {
                            if (t8.type === TouchType.Down) {
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
                            if (t8.type === TouchType.Up || t8.type === TouchType.Cancel) {
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
                            'yes' : 'no');
                    }, Row);
                    this.rightArea.bind(this)();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }

    onMeasureSize(i8, j8, k8) {
        let l8 = { width: i8.width, height: i8.height };
        let m8 = this.getUIContext().getHostContext();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        } else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        j8.forEach((n8) => {
            k8.minHeight = Math.min(Number(this.getMinHeight()), Number(k8.maxHeight));
            l8.height = n8.measure(k8).height;
            l8.width = Number(k8.maxWidth);
        });
        return l8;
    }

    onPlaceChildren(e8, f8, g8) {
        f8.forEach((h8) => {
            h8.layout({ x: 0, y: 0 });
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
        ;
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
        let d8 = {};
        if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
            (!this.primaryTitle && this.secondaryTitle))) {
            d8 = {
                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
            };
        }
        else if (this.select) {
            d8 = {
                top: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
                bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level2')),
            };
        }
        return d8;
    }

    leftArea(a8 = null) {
        this.observeComponentCreation2((b8, c8) => {
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

    rightArea(r7 = null) {
        this.observeComponentCreation2((y7, z7) => {
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
        this.observeComponentCreation2((w7, x7) => {
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
        this.observeComponentCreation2((u7, v7) => {
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
        this.observeComponentCreation2((s7, t7) => {
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

    IconSecondaryTitleStyle(f7, g7 = null) {
        this.observeComponentCreation2((p7, q7) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
            });
        }, Flex);
        this.observeComponentCreation2((j7, k7) => {
            If.create();
            if (Util.isSymbolResource(f7.iconOptions?.icon)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n7, o7) => {
                        SymbolGlyph.create(f7.iconOptions?.icon);
                        SymbolGlyph.fontSize(f7.iconOptions?.symbolicIconOption?.fontSize ?
                        Util.symbolFontSize(f7.iconOptions?.symbolicIconOption?.fontSize) : LEFT_ICON_SIZE);
                        SymbolGlyph.fontColor(f7.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.leftIconColor]);
                        SymbolGlyph.fontWeight(f7.iconOptions?.symbolicIconOption?.fontWeight);
                        SymbolGlyph.renderingStrategy(f7.iconOptions?.symbolicIconOption?.renderingStrategy);
                        SymbolGlyph.effectStrategy(f7.iconOptions?.symbolicIconOption?.effectStrategy);
                        SymbolGlyph.margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) });
                        SymbolGlyph.flexShrink(0);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((l7, m7) => {
                        Image.create(f7.iconOptions?.icon);
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
        this.observeComponentCreation2((h7, i7) => {
            Text.create(f7.content);
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

    SubTitleStyle(x6, y6 = null) {
        this.observeComponentCreation2((d7, e7) => {
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
        this.observeComponentCreation2((b7, c7) => {
            Text.create(x6.content);
            __Text__primaryTitleStyles({
                fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((z6, a7) => {
            Text.create(x6.subContent);
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

    SecondTitleStyle(t6, u6 = null) {
        this.observeComponentCreation2((v6, w6) => {
            Text.create(t6.content);
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

    SelectStyle(n6, o6 = null) {
        this.observeComponentCreation2((p6, q6) => {
            Select.create(n6.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
            Select.value(ObservedObject.GetRawObject(this.selectValue));
            Select.onSelect((r6, s6) => {
                this.selectedIndex = r6;
                if (s6) {
                    this.selectValue = s6;
                }
                if (n6.onSelect) {
                    n6.onSelect(r6, s6);
                }
            });
            Select.font({
                size: `${getResourceValue('sys.float.Body_L')}fp`,
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
    }

    PrimaryTitleStyle(j6, k6 = null) {
        this.observeComponentCreation2((l6, m6) => {
            Text.create(j6.content);
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

    ButtonStyle(a6, b6 = null) {
        this.observeComponentCreation2((c6, d6) => {
            If.create();
            if (a6) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g6, h6) => {
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
                        Button.onHover((i6) => {
                            if (i6) {
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
                    this.observeComponentCreation2((e6, f6) => {
                        Text.create(a6.value);
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

    TextStyle(s5, t5 = null) {
        this.observeComponentCreation2((y5, z5) => {
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
        this.observeComponentCreation2((u5, v5) => {
            If.create();
            if (s5) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w5, x5) => {
                        Text.create(s5.value);
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

    ArrowStyle(n5 = null) {
        this.observeComponentCreation2((q5, r5) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((o5, p5) => {
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

    TextArrowStyle(c4, d4 = null) {
        this.observeComponentCreation2((e4, f4) => {
            If.create();
            if (c4 && c4.value && c4.value.toString().length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l5, m5) => {
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
                    this.observeComponentCreation2((i5, j5) => {
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
                        Button.onHover((k5) => {
                            if (k5) {
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
                        this.observeComponentCreation2((n4, p4) => {
                            if (p4) {
                                let q4 = new TextArrowLayout(this, {
                                    textArrowBuilder: () => {
                                        this.observeComponentCreation2((b5, c5) => {
                                            ForEach.create();
                                            const d5 = e5 => {
                                                const f5 = e5;
                                                this.observeComponentCreation2((g5, h5) => {
                                                    If.create();
                                                    if (f5 === INDEX_ZERO) {
                                                        this.ifElseBranchUpdateFunction(0, () => {
                                                            this.TextStyle.bind(this)(c4);
                                                        });
                                                    } else {
                                                        this.ifElseBranchUpdateFunction(1, () => {
                                                            this.ArrowStyle.bind(this)();
                                                        });
                                                    }
                                                }, If);
                                                If.pop();
                                            };
                                            this.forEachUpdateFunction(b5, [INDEX_ZERO, INDEX_ONE], d5);
                                        }, ForEach);
                                        ForEach.pop();
                                    }
                                }, undefined, n4, () => { }, {
                                    page: 'library/src/main/ets/components/mainpage/MainPage.ets',
                                    line: 837,
                                    col: 11
                                });
                                ViewPU.create(q4);
                                let s4 = () => {
                                    return {
                                        textArrowBuilder: () => {
                                            this.observeComponentCreation2((t4, u4) => {
                                                ForEach.create();
                                                const v4 = w4 => {
                                                    const x4 = w4;
                                                    this.observeComponentCreation2((z4, a5) => {
                                                        If.create();
                                                        if (x4 === INDEX_ZERO) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.TextStyle.bind(this)(c4);
                                                            });
                                                        } else {
                                                            this.ifElseBranchUpdateFunction(1, () => {
                                                                this.ArrowStyle.bind(this)();
                                                            });
                                                        }
                                                    }, If);
                                                    If.pop();
                                                };
                                                this.forEachUpdateFunction(t4, [INDEX_ZERO, INDEX_ONE], v4);
                                            }, ForEach);
                                            ForEach.pop();
                                        }
                                    };
                                };
                                q4.paramsGenerator_ = s4;
                            } else {
                                this.updateStateVarsOfChildByElmtId(n4, {});
                            }
                        }, { name: 'TextArrowLayout' });
                    }
                    Button.pop();
                    Stack.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((l4, m4) => {
                        Row.create();
                        Row.focusable(true);
                        Row.constraintSize({ minWidth: this.getRightAreaMinWidth() });
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((i4, j4) => {
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
                        Button.onHover((k4) => {
                            if (k4) {
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
                    this.observeComponentCreation2((g4, h4) => {
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

    IconGroupStyle(g3, h3 = null) {
        this.observeComponentCreation2((a4, b4) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((i3, j3) => {
            ForEach.create();
            const l3 = (m3, n3) => {
                const o3 = m3;
                this.observeComponentCreation2((p3, q3) => {
                    If.create();
                    if (Util.isResourceType(o3.value)) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((r3, s3) => {
                                If.create();
                                if (n3 <= INDEX_TWO) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((y3, z3) => {
                                            __Common__.create();
                                            __Common__.margin({
                                                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                                                bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level3')),
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((t3, u3) => {
                                                if (u3) {
                                                    let w3 = new SingleIconStyle(this, {
                                                        item: {
                                                            iconOptions: {
                                                                icon: o3.value,
                                                                symbolicIconOption: this.operationSymbolOptions &&
                                                                    this.operationSymbolOptions.length > n3 ?
                                                                this.operationSymbolOptions[n3] : null,
                                                            },
                                                            action: o3.action,
                                                        },
                                                        isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER,
                                                    }, undefined, t3, () => { }, {
                                                        page: 'library/src/main/ets/components/mainpage/MainPage.ets',
                                                        line: 927,
                                                        col: 13
                                                    });
                                                    ViewPU.create(w3);
                                                    let x3 = () => {
                                                        return {
                                                            item: {
                                                                iconOptions: {
                                                                    icon: o3.value,
                                                                    symbolicIconOption: this.operationSymbolOptions &&
                                                                        this.operationSymbolOptions.length > n3 ?
                                                                    this.operationSymbolOptions[n3] : null,
                                                                },
                                                                action: o3.action,
                                                            },
                                                            isSingleIcon: this.operationItem?.length ===
                                                                SINGLE_ICON_NUMBER
                                                        };
                                                    };
                                                    w3.paramsGenerator_ = x3;
                                                } else {
                                                    this.updateStateVarsOfChildByElmtId(t3, {});
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
            this.forEachUpdateFunction(i3, g3, l3, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    LoadingProcessStyle(b3 = null) {
        this.observeComponentCreation2((e3, f3) => {
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
        this.observeComponentCreation2((c3, d3) => {
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

    dummyFunction(y2 = null) {
        this.observeComponentCreation2((z2, a3) => {
            Row.create();
        }, Row);
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SingleIconStyle extends ViewPU {
    constructor(s2, t2, u2, v2 = -1, w2 = undefined, x2) {
        super(s2, u2, v2, x2);
        if (typeof w2 === 'function') {
            this.paramsGenerator_ = w2;
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
        this.setInitiallyProvidedValue(t2);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(r2) {
        if (r2.bgColor !== undefined) {
            this.bgColor = r2.bgColor;
        }
        if (r2.isFocus !== undefined) {
            this.isFocus = r2.isFocus;
        }
        if (r2.item !== undefined) {
            this.item = r2.item;
        }
        if (r2.isSingleIcon !== undefined) {
            this.isSingleIcon = r2.isSingleIcon;
        }
    }

    updateStateVars(q2) {
    }

    purgeVariableDependenciesOnElmtId(p2) {
        this.__bgColor.purgeDependencyOnElmtId(p2);
        this.__isFocus.purgeDependencyOnElmtId(p2);
        this.__subHeaderTheme.purgeDependencyOnElmtId(p2);
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

    set bgColor(o2) {
        this.__bgColor.set(o2);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(n2) {
        this.__isFocus.set(n2);
    }

    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }

    set subHeaderTheme(m2) {
        this.__subHeaderTheme.set(m2);
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
                        Button.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
                        Button.borderRadius(getResourceValue('sys.float.corner_radius_level4'));
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
                        Button.onTouch((l2) => {
                            if (l2.type === TouchType.Down || TouchType.Cancel) {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.interactive_pressed'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                            if (l2.type === TouchType.Up) {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                        });
                        Button.onHover((k2) => {
                            if (k2) {
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
                        Button.onClick((j2) => {
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

    fontSizeValue(e2) {
        return e2.iconOptions?.symbolicIconOption?.fontSize ?
        Util.symbolFontSize(e2.iconOptions?.symbolicIconOption?.fontSize) : RIGHT_SINGLE_ICON_SIZE;
    }

    IconZone(v1 = null) {
        this.observeComponentCreation2((w1, x1) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y1, z1) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((c2, d2) => {
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
                                this.observeComponentCreation2((a2, b2) => {
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

export default { OperationType, SubHeader };