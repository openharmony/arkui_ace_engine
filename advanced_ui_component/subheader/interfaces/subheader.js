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
if (PUV2ViewBase.contextStack === undefined) {
    Reflect.set(PUV2ViewBase, 'contextStack', []);
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
const SINGLE_LINE_HEIGHT = 56;
const DOUBLE_LINE_HEIGHT = 72;
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
(function (c16) {
    c16[c16['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
    c16[c16['BUTTON'] = 1] = 'BUTTON';
    c16[c16['ICON_GROUP'] = 2] = 'ICON_GROUP';
    c16[c16['LOADING'] = 3] = 'LOADING';
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

function __Text__secondaryTitleStyles(b16) {
    Text.fontSize(`${getResourceValue('sys.float.Subtitle_S')}fp`);
    Text.fontColor(b16?.fontColor ?? {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_secondary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    });
    Text.fontWeight(b16?.fontWeight);
    Text.maxLines(b16?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(b16?.alignment);
}

function __Text__primaryTitleStyles(a16) {
    Text.fontSize(`${getResourceValue('sys.float.Subtitle_L')}fp`);
    Text.fontColor(a16?.fontColor ?? {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    });
    Text.fontWeight(a16?.fontWeight);
    Text.maxLines(a16?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(a16?.alignment);
}

class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }

    applyNormalAttribute(z15) {
        if (this.isAgeing) {
            z15.width('100%');
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
RESOURCE_CACHE_MAP.set('sys.float.Subtitle_L', { resourceId: 125830967, defaultValue: 18 });
RESOURCE_CACHE_MAP.set('sys.float.Body_L', { resourceId: 125830970, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.interactive_disable', { resourceId: 125831067, defaultValue: 0.4 });

export class SubHeader extends ViewPU {
    constructor(t15, u15, v15, w15 = -1, x15 = undefined, y15) {
        super(t15, v15, w15, y15);
        if (typeof x15 === 'function') {
            this.paramsGenerator_ = x15;
        }
        this.__icon = new SynchedPropertyObjectOneWayPU(u15.icon, this, 'icon');
        this.iconSymbolOptions = null;
        this.__primaryTitle = new SynchedPropertyObjectOneWayPU(u15.primaryTitle, this, 'primaryTitle');
        this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'primaryTitleModifier');
        this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(u15.secondaryTitle, this, 'secondaryTitle');
        this.__secondaryTitleModifier =
            new ObservedPropertyObjectPU(new TextModifier(), this, 'secondaryTitleModifier');
        this.__subHeaderModifier = new ObservedPropertyObjectPU(new SubHeaderModifier(), this, 'subHeaderModifier');
        this.select = null;
        this.__operationType = new SynchedPropertySimpleOneWayPU(u15.operationType, this, 'operationType');
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
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(u15.contentMargin, this, 'contentMargin');
        this.__contentPadding = new SynchedPropertyObjectOneWayPU(u15.contentPadding, this, 'contentPadding');
        this.subHeaderMargin = {
            start: LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
            end: LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
        };
        this.__subHeaderTheme = new ObservedPropertyObjectPU(new SubHeaderTheme(), this, 'subHeaderTheme');
        this.addProvidedVar('subHeaderTheme', this.__subHeaderTheme, false);
        this.isFollowingSystemFontScale = false;
        this.appMaxFontScale = 3.2;
        this.setInitiallyProvidedValue(u15);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(s15) {
        if (s15.icon === undefined) {
            this.__icon.set(null);
        }
        if (s15.iconSymbolOptions !== undefined) {
            this.iconSymbolOptions = s15.iconSymbolOptions;
        }
        if (s15.primaryTitle === undefined) {
            this.__primaryTitle.set(null);
        }
        if (s15.primaryTitleModifier !== undefined) {
            this.primaryTitleModifier = s15.primaryTitleModifier;
        }
        if (s15.secondaryTitle === undefined) {
            this.__secondaryTitle.set(null);
        }
        if (s15.secondaryTitleModifier !== undefined) {
            this.secondaryTitleModifier = s15.secondaryTitleModifier;
        }
        if (s15.subHeaderModifier !== undefined) {
            this.subHeaderModifier = s15.subHeaderModifier;
        }
        if (s15.select !== undefined) {
            this.select = s15.select;
        }
        if (s15.operationType === undefined) {
            this.__operationType.set(OperationType.BUTTON);
        }
        if (s15.operationItem !== undefined) {
            this.operationItem = s15.operationItem;
        }
        if (s15.operationSymbolOptions !== undefined) {
            this.operationSymbolOptions = s15.operationSymbolOptions;
        }
        if (s15.fontSize !== undefined) {
            this.fontSize = s15.fontSize;
        }
        if (s15.ageing !== undefined) {
            this.ageing = s15.ageing;
        }
        if (s15.textArrowBgColor !== undefined) {
            this.textArrowBgColor = s15.textArrowBgColor;
        }
        if (s15.buttonBgColor !== undefined) {
            this.buttonBgColor = s15.buttonBgColor;
        }
        if (s15.selectedIndex !== undefined) {
            this.selectedIndex = s15.selectedIndex;
        }
        if (s15.selectValue !== undefined) {
            this.selectValue = s15.selectValue;
        }
        if (s15.titleBuilder !== undefined) {
            this.titleBuilder = s15.titleBuilder;
        }
        if (s15.subHeaderMargin !== undefined) {
            this.subHeaderMargin = s15.subHeaderMargin;
        }
        if (s15.subHeaderTheme !== undefined) {
            this.subHeaderTheme = s15.subHeaderTheme;
        }
        if (s15.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = s15.isFollowingSystemFontScale;
        }
        if (s15.appMaxFontScale !== undefined) {
            this.appMaxFontScale = s15.appMaxFontScale;
        }
    }

    updateStateVars(r15) {
        this.__icon.reset(r15.icon);
        this.__primaryTitle.reset(r15.primaryTitle);
        this.__secondaryTitle.reset(r15.secondaryTitle);
        this.__operationType.reset(r15.operationType);
        this.__contentMargin.reset(r15.contentMargin);
        this.__contentPadding.reset(r15.contentPadding);
    }

    purgeVariableDependenciesOnElmtId(q15) {
        this.__icon.purgeDependencyOnElmtId(q15);
        this.__primaryTitle.purgeDependencyOnElmtId(q15);
        this.__primaryTitleModifier.purgeDependencyOnElmtId(q15);
        this.__secondaryTitle.purgeDependencyOnElmtId(q15);
        this.__secondaryTitleModifier.purgeDependencyOnElmtId(q15);
        this.__subHeaderModifier.purgeDependencyOnElmtId(q15);
        this.__operationType.purgeDependencyOnElmtId(q15);
        this.__fontSize.purgeDependencyOnElmtId(q15);
        this.__ageing.purgeDependencyOnElmtId(q15);
        this.__textArrowBgColor.purgeDependencyOnElmtId(q15);
        this.__buttonBgColor.purgeDependencyOnElmtId(q15);
        this.__selectedIndex.purgeDependencyOnElmtId(q15);
        this.__selectValue.purgeDependencyOnElmtId(q15);
        this.__contentMargin.purgeDependencyOnElmtId(q15);
        this.__contentPadding.purgeDependencyOnElmtId(q15);
        this.__subHeaderTheme.purgeDependencyOnElmtId(q15);
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

    set icon(p15) {
        this.__icon.set(p15);
    }

    get primaryTitle() {
        return this.__primaryTitle.get();
    }

    set primaryTitle(o15) {
        this.__primaryTitle.set(o15);
    }

    get primaryTitleModifier() {
        return this.__primaryTitleModifier.get();
    }

    set primaryTitleModifier(n15) {
        this.__primaryTitleModifier.set(n15);
    }

    get secondaryTitle() {
        return this.__secondaryTitle.get();
    }

    set secondaryTitle(m15) {
        this.__secondaryTitle.set(m15);
    }

    get secondaryTitleModifier() {
        return this.__secondaryTitleModifier.get();
    }

    set secondaryTitleModifier(l15) {
        this.__secondaryTitleModifier.set(l15);
    }

    get subHeaderModifier() {
        return this.__subHeaderModifier.get();
    }

    set subHeaderModifier(k15) {
        this.__subHeaderModifier.set(k15);
    }

    get operationType() {
        return this.__operationType.get();
    }

    set operationType(j15) {
        this.__operationType.set(j15);
    }

    get fontSize() {
        return this.__fontSize.get();
    }

    set fontSize(i15) {
        this.__fontSize.set(i15);
    }

    get ageing() {
        return this.__ageing.get();
    }

    set ageing(h15) {
        this.__ageing.set(h15);
    }

    get textArrowBgColor() {
        return this.__textArrowBgColor.get();
    }

    set textArrowBgColor(g15) {
        this.__textArrowBgColor.set(g15);
    }

    get buttonBgColor() {
        return this.__buttonBgColor.get();
    }

    set buttonBgColor(f15) {
        this.__buttonBgColor.set(f15);
    }

    get selectedIndex() {
        return this.__selectedIndex.get();
    }

    set selectedIndex(e15) {
        this.__selectedIndex.set(e15);
    }

    get selectValue() {
        return this.__selectValue.get();
    }

    set selectValue(d15) {
        this.__selectValue.set(d15);
    }

    get contentMargin() {
        return this.__contentMargin.get();
    }

    set contentMargin(c15) {
        this.__contentMargin.set(c15);
    }

    get contentPadding() {
        return this.__contentPadding.get();
    }

    set contentPadding(b15) {
        this.__contentPadding.set(b15);
    }

    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }

    set subHeaderTheme(a15) {
        this.__subHeaderTheme.set(a15);
    }

    onWillApplyTheme(z14) {
        this.subHeaderTheme.fontPrimaryColor = z14.colors.fontPrimary;
        this.subHeaderTheme.fontSecondaryColor = z14.colors.fontSecondary;
        this.subHeaderTheme.fontButtonColor = z14.colors.fontEmphasize;
        this.subHeaderTheme.iconArrowColor = z14.colors.iconTertiary;
        this.subHeaderTheme.textArrowHoverBgColor = z14.colors.interactiveHover;
        this.subHeaderTheme.borderFocusColor = z14.colors.interactiveFocus;
        this.subHeaderTheme.leftIconColor = z14.colors.iconSecondary;
        this.subHeaderTheme.rightIconColor = z14.colors.iconPrimary;
    }

    updateFontScale() {
        try {
            let x14 = this.getUIContext();
            let y14 = x14.getHostContext()?.config.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(y14, this.appMaxFontScale);
        } catch (u14) {
            let v14 = u14.code;
            let w14 = u14.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${v14}, message: ${w14}`);
            return 1;
        }
    }

    async aboutToAppear() {
        let t14 = this.getUIContext();
        this.isFollowingSystemFontScale = t14.isFollowingSystemFontScale();
        this.appMaxFontScale = t14.getMaxFontScale();
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
        this.observeComponentCreation2((t13, u13) => {
            If.create();
            if (this.isSuitableAging()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r14, s14) => {
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.padding(this.getAreaPadding());
                        Column.alignItems(HorizontalAlign.Start);
                    }, Column);
                    this.observeComponentCreation2((p14, q14) => {
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
                    this.leftArea.bind(this)(this);
                    Row.pop();
                    this.observeComponentCreation2((l14, m14) => {
                        If.create();
                        if (this.isRightAreaExists()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.rightAreaParentAging.bind(this)(this);
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
                    this.observeComponentCreation2((f14, g14) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.contentMargin ?? this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((d14, e14) => {
                        Row.create();
                        Row.margin({
                            top: this.fontSize >= MIN_FONT_SIZE ? getResourceValue('sys.float.padding_level8') : '',
                            bottom: this.fontSize >= MIN_FONT_SIZE ? getResourceValue('sys.float.padding_level4') : '',
                        });
                        Row.width('100%');
                        Row.flexShrink(1);
                        Row.accessibilityGroup(this.isLeftAreaAccessibilityGroup());
                    }, Row);
                    this.leftArea.bind(this)(this);
                    Row.pop();
                    this.observeComponentCreation2((z13, a14) => {
                        If.create();
                        if (this.isRightAreaExists()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.rightAreaParent.bind(this)(this);
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

    rightAreaParentAging(a13 = null) {
        this.observeComponentCreation2((c13, d13) => {
            If.create();
            if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n13, o13) => {
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
                        Button.onTouch((r13) => {
                            if (r13.type === TouchType.Down) {
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
                            if (r13.type === TouchType.Up || r13.type === TouchType.Cancel) {
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
                    this.rightArea.bind(this)(a13 ? a13 : this);
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((g13, h13) => {
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
                        Row.onTouch((k13) => {
                            if (k13.type === TouchType.Down) {
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
                            if (k13.type === TouchType.Up || k13.type === TouchType.Cancel) {
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
                    this.rightArea.bind(this)(a13 ? a13 : this);
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }

    rightAreaParent(i12 = null) {
        this.observeComponentCreation2((k12, l12) => {
            If.create();
            if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v12, w12) => {
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
                        Button.onTouch((z12) => {
                            if (z12.type === TouchType.Down) {
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
                            if (z12.type === TouchType.Up || z12.type === TouchType.Cancel) {
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
                    this.rightArea.bind(this)(i12 ? i12 : this);
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((o12, p12) => {
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
                        Row.onTouch((s12) => {
                            if (s12.type === TouchType.Down) {
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
                            if (s12.type === TouchType.Up || s12.type === TouchType.Cancel) {
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
                    this.rightArea.bind(this)(i12 ? i12 : this);
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }

    onMeasureSize(b12, c12, d12) {
        let e12 = { width: b12.width, height: b12.height };
        let f12 = this.getUIContext().getHostContext();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        } else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        c12.forEach((h12) => {
            d12.minHeight = Math.min(Number(this.getMinHeight()), Number(d12.maxHeight));
            e12.height = h12.measure(d12).height;
            e12.width = Number(d12.maxWidth);
        });
        return e12;
    }

    onPlaceChildren(w11, x11, y11) {
        x11.forEach((a12) => {
            a12.layout({ x: 0, y: 0 });
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
            return SINGLE_LINE_HEIGHT;
        } else if (this.secondaryTitle && this.primaryTitle) {
            return DOUBLE_LINE_HEIGHT;
        }
        return SINGLE_LINE_HEIGHT;
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
        let v11 = {};
        if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
            (!this.primaryTitle && this.secondaryTitle))) {
            v11 = {
                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
            };
        }
        return v11;
    }

    leftArea(k11 = null) {
        this.observeComponentCreation2((m11, n11) => {
            If.create();
            if (this.titleBuilder) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.titleBuilder.bind(this)(k11 ? k11 : this);
                });
            } else if (this.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondaryTitleStyle', {
                        content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']),
                        iconOptions: () => ({
                            icon: this.icon,
                            symbolicIconOption: this.iconSymbolOptions,
                        })
                    }), k11 ? k11 : this);
                });
            } else if (this.secondaryTitle && this.primaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle', {
                        content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']),
                        subContent: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle'])
                    }), k11 ? k11 : this);
                });
            } else if (this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle', {
                        content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle'])
                    }), k11 ? k11 : this);
                });
            } else if (this.select) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.SelectStyle.bind(this)(this.select, k11 ? k11 : this);
                });
            } else if (this.primaryTitle) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle',
                        { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']) }),
                        k11 ? k11 : this);
                });
            } else {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.dummyFunction.bind(this)(k11 ? k11 : this);
                });
            }
        }, If);
        If.pop();
    }

    rightArea(p10 = null) {
        this.observeComponentCreation2((g11, h11) => {
            If.create();
            if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)(this.operationItem[0], p10 ? p10 : this);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((c11, d11) => {
            If.create();
            if (this.operationType === OperationType.TEXT_ARROW &&
                (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextArrowStyle.bind(this)(this.operationItem[0], p10 ? p10 : this);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((y10, z10) => {
            If.create();
            if (this.operationType === OperationType.ICON_GROUP &&
                (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconGroupStyle.bind(this)(this.operationItem, p10 ? p10 : this);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((u10, v10) => {
            If.create();
            if (this.operationType === OperationType.LOADING) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.LoadingProcessStyle.bind(this)(p10 ? p10 : this);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    IconSecondaryTitleStyle(w9, x9 = null) {
        this.observeComponentCreation2((n10, o10) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
            });
        }, Flex);
        this.observeComponentCreation2((d10, e10) => {
            If.create();
            if (Util.isSymbolResource(w9.iconOptions?.icon)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l10, m10) => {
                        SymbolGlyph.create(w9.iconOptions?.icon);
                        SymbolGlyph.fontSize(w9.iconOptions?.symbolicIconOption?.fontSize ?
                        Util.symbolFontSize(w9.iconOptions?.symbolicIconOption?.fontSize) : LEFT_ICON_SIZE);
                        SymbolGlyph.fontColor(w9.iconOptions?.symbolicIconOption?.fontColor ??
                            [this.subHeaderTheme.leftIconColor]);
                        SymbolGlyph.fontWeight(w9.iconOptions?.symbolicIconOption?.fontWeight);
                        SymbolGlyph.renderingStrategy(w9.iconOptions?.symbolicIconOption?.renderingStrategy);
                        SymbolGlyph.effectStrategy(w9.iconOptions?.symbolicIconOption?.effectStrategy);
                        SymbolGlyph.margin({ end: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) });
                        SymbolGlyph.flexShrink(0);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((h10, i10) => {
                        Image.create(w9.iconOptions?.icon);
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
        this.observeComponentCreation2((b10, c10) => {
            Text.create(w9.content);
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

    SubTitleStyle(l9, m9 = null) {
        this.observeComponentCreation2((u9, v9) => {
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
        this.observeComponentCreation2((s9, t9) => {
            Text.create(l9.content);
            __Text__primaryTitleStyles({
                fontWeight: FontWeight.Bold,
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((q9, r9) => {
            Text.create(l9.subContent);
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

    SecondTitleStyle(g9, h9 = null) {
        this.observeComponentCreation2((j9, k9) => {
            Text.create(g9.content);
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

    SelectStyle(y8, z8 = null) {
        this.observeComponentCreation2((b9, c9) => {
            Select.create(y8.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
            Select.value(ObservedObject.GetRawObject(this.selectValue));
            Select.onSelect((e9, f9) => {
                this.selectedIndex = e9;
                if (f9) {
                    this.selectValue = f9;
                }
                if (y8.onSelect) {
                    y8.onSelect(e9, f9);
                }
            });
            Select.font({
                size: `${getResourceValue('sys.float.Body_L')}fp`,
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
    }

    PrimaryTitleStyle(t8, u8 = null) {
        this.observeComponentCreation2((w8, x8) => {
            Text.create(t8.content);
            __Text__primaryTitleStyles({
                fontWeight: FontWeight.Bold,
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

    ButtonStyle(e8, f8 = null) {
        this.observeComponentCreation2((h8, i8) => {
            If.create();
            if (e8) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p8, q8) => {
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
                        Button.onHover((s8) => {
                            if (s8) {
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
                    this.observeComponentCreation2((n8, o8) => {
                        Text.create(e8.value);
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

    TextStyle(r7, s7 = null) {
        this.observeComponentCreation2((c8, d8) => {
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
        this.observeComponentCreation2((v7, w7) => {
            If.create();
            if (r7) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a8, b8) => {
                        Text.create(r7.value);
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

    ArrowStyle(k7 = null) {
        this.observeComponentCreation2((p7, q7) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((n7, o7) => {
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

    TextArrowStyle(f5, g5 = null) {
        this.observeComponentCreation2((i5, j5) => {
            If.create();
            if (f5 && f5.value && f5.value.toString().length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i7, j7) => {
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
                    this.observeComponentCreation2((e7, f7) => {
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
                        Button.onHover((h7) => {
                            if (h7) {
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
                        this.observeComponentCreation2((a6, b6) => {
                            if (b6) {
                                let c6 = new TextArrowLayout(g5 ? g5 : this, {
                                    textArrowBuilder: () => {
                                        this.observeComponentCreation2((t6, u6) => {
                                            ForEach.create();
                                            const v6 = x6 => {
                                                const y6 = x6;
                                                this.observeComponentCreation2((a7, b7) => {
                                                    If.create();
                                                    if (y6 === INDEX_ZERO) {
                                                        this.ifElseBranchUpdateFunction(0, () => {
                                                            this.TextStyle.bind(this)(f5, g5 ? g5 : this);
                                                        });
                                                    } else {
                                                        this.ifElseBranchUpdateFunction(1, () => {
                                                            this.ArrowStyle.bind(this)(g5 ? g5 : this);
                                                        });
                                                    }
                                                }, If);
                                                If.pop();
                                            };
                                            this.forEachUpdateFunction(t6, [INDEX_ZERO, INDEX_ONE], v6);
                                        }, ForEach);
                                        ForEach.pop();
                                    }
                                }, undefined, a6, () => {
                                }, {
                                    page: 'library/src/main/ets/components/mainpage/MainPage.ets',
                                    line: 824,
                                    col: 11
                                });
                                ViewPU.create(c6);
                                let d6 = () => {
                                    return {
                                        textArrowBuilder: () => {
                                            this.observeComponentCreation2((h6, i6) => {
                                                ForEach.create();
                                                const j6 = l6 => {
                                                    const m6 = l6;
                                                    this.observeComponentCreation2((o6, p6) => {
                                                        If.create();
                                                        if (m6 === INDEX_ZERO) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.TextStyle.bind(this)(f5, g5 ? g5 : this);
                                                            });
                                                        } else {
                                                            this.ifElseBranchUpdateFunction(1, () => {
                                                                this.ArrowStyle.bind(this)(g5 ? g5 : this);
                                                            });
                                                        }
                                                    }, If);
                                                    If.pop();
                                                };
                                                this.forEachUpdateFunction(h6, [INDEX_ZERO, INDEX_ONE], j6);
                                            }, ForEach);
                                            ForEach.pop();
                                        }
                                    };
                                };
                                c6.paramsGenerator_ = d6;
                            } else {
                                this.updateStateVarsOfChildByElmtId(a6, {});
                            }
                        }, { name: 'TextArrowLayout' });
                    }
                    Button.pop();
                    Stack.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((u5, v5) => {
                        Row.create();
                        Row.focusable(true);
                        Row.constraintSize({ minWidth: this.getRightAreaMinWidth() });
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((q5, r5) => {
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
                        Button.onHover((t5) => {
                            if (t5) {
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
                    Button.pop();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }

    IconGroupStyle(y3, z3 = null) {
        this.observeComponentCreation2((d5, e5) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((c4, d4) => {
            ForEach.create();
            const e4 = (g4, h4) => {
                const i4 = g4;
                this.observeComponentCreation2((k4, l4) => {
                    If.create();
                    if (Util.isResourceType(i4.value)) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((p4, q4) => {
                                If.create();
                                if (h4 <= INDEX_TWO) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((b5, c5) => {
                                            __Common__.create();
                                            __Common__.margin({
                                                start: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')),
                                                bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level3')),
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((v4, w4) => {
                                                if (w4) {
                                                    let x4 = new SingleIconStyle(z3 ? z3 : this, {
                                                        item: {
                                                            iconOptions: {
                                                                icon: i4.value,
                                                                symbolicIconOption: this.operationSymbolOptions &&
                                                                    this.operationSymbolOptions.length > h4 ?
                                                                this.operationSymbolOptions[h4] : null,
                                                            },
                                                            action: i4.action,
                                                        },
                                                        isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER,
                                                    }, undefined, v4, () => {
                                                    }, {
                                                        page: 'library/src/main/ets/components/mainpage/MainPage.ets',
                                                        line: 914,
                                                        col: 13
                                                    });
                                                    ViewPU.create(x4);
                                                    let y4 = () => {
                                                        return {
                                                            item: {
                                                                iconOptions: {
                                                                    icon: i4.value,
                                                                    symbolicIconOption: this.operationSymbolOptions &&
                                                                        this.operationSymbolOptions.length > h4 ?
                                                                    this.operationSymbolOptions[h4] : null,
                                                                },
                                                                action: i4.action,
                                                            },
                                                            isSingleIcon: this.operationItem?.length ===
                                                                SINGLE_ICON_NUMBER
                                                        };
                                                    };
                                                    x4.paramsGenerator_ = y4;
                                                } else {
                                                    this.updateStateVarsOfChildByElmtId(v4, {});
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
            this.forEachUpdateFunction(c4, y3, e4, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    LoadingProcessStyle(r3 = null) {
        this.observeComponentCreation2((w3, x3) => {
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
        this.observeComponentCreation2((u3, v3) => {
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

    dummyFunction(n3 = null) {
        this.observeComponentCreation2((p3, q3) => {
            Row.create();
        }, Row);
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SingleIconStyle extends ViewPU {
    constructor(h3, i3, j3, k3 = -1, l3 = undefined, m3) {
        super(h3, j3, k3, m3);
        if (typeof l3 === 'function') {
            this.paramsGenerator_ = l3;
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
        this.setInitiallyProvidedValue(i3);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(g3) {
        if (g3.bgColor !== undefined) {
            this.bgColor = g3.bgColor;
        }
        if (g3.isFocus !== undefined) {
            this.isFocus = g3.isFocus;
        }
        if (g3.item !== undefined) {
            this.item = g3.item;
        }
        if (g3.isSingleIcon !== undefined) {
            this.isSingleIcon = g3.isSingleIcon;
        }
    }

    updateStateVars(f3) {
    }

    purgeVariableDependenciesOnElmtId(e3) {
        this.__bgColor.purgeDependencyOnElmtId(e3);
        this.__isFocus.purgeDependencyOnElmtId(e3);
        this.__subHeaderTheme.purgeDependencyOnElmtId(e3);
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

    set bgColor(d3) {
        this.__bgColor.set(d3);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(c3) {
        this.__isFocus.set(c3);
    }

    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }

    set subHeaderTheme(b3) {
        this.__subHeaderTheme.set(b3);
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
                    this.IconZone.bind(this)(this);
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
        this.textArrowBuilder.bind(this)(this);
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default { OperationType, SubHeader };