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

const f4 = 0;
const j4 = 1;
const m = 2;
const o = 1;
const t = 2;
const u = 56;
const a1 = 72;
const b1 = 40000;
const c1 = '16vp';
const d1 = 16;
const e1 = 8;
const f1 = 24;
const g1 = 12;
const h1 = 28;
const i1 = '24vp';
const j1 = 4;
const l1 = '34%';
const m1 = 1.75;
const n1 = 40;
const o1 = 37;
const q1 = -9;
const s1 = -6;
const t1 = -12;
const u1 = 1;
const m4 = 2;

export var OperationType;
(function (OperationType) {
    OperationType[OperationType['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
    OperationType[OperationType['BUTTON'] = 1] = 'BUTTON';
    OperationType[OperationType['ICON_GROUP'] = 2] = 'ICON_GROUP';
    OperationType[OperationType['LOADING'] = 3] = 'LOADING';
})(OperationType || (OperationType = {}));

class IconOptions {
}

class v1 {
}

class FontStyle {
    constructor() {
        this.maxLines = 0;
        this.fontWeight = 0;
    }
}

class w1 {
    constructor() {
        this.b2 = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.c2 = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.d2 = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_emphasize'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.e2 = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.icon_tertiary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.f2 = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.interactive_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.g2 = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.interactive_focus'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.h2 = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.icon_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.i2 = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.icon_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
    }
}

function i(fontStyle) {
    Text.fontSize(`${b4('sys.float.Subtitle_S')}fp`);
    Text.fontColor(fontStyle?.fontColor ?? {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_secondary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    });
    Text.fontWeight(fontStyle?.fontWeight);
    Text.maxLines(fontStyle?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(fontStyle?.alignment);
}

function j(fontStyle) {
    Text.fontSize(`${b4('sys.float.Subtitle_L')}fp`);
    Text.fontColor(fontStyle?.fontColor ?? {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    });
    Text.fontWeight(fontStyle?.fontWeight);
    Text.maxLines(fontStyle?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(fontStyle?.alignment);
}

class z1 {
    constructor() {
        this.j2 = false;
    }

    applyNormalAttribute(instance) {
        if (this.j2) {
            instance.width('100%');
        } else {
        }
    }
}

const c4 = new HashMap();
c4.set('sys.float.padding_level0', { d4: 125830919, defaultValue: 0 });
c4.set('sys.float.padding_level1', { d4: 125830920, defaultValue: 2 });
c4.set('sys.float.padding_level2', { d4: 125830921, defaultValue: 4 });
c4.set('sys.float.padding_level3', { d4: 125830922, defaultValue: 6 });
c4.set('sys.float.padding_level4', { d4: 125830923, defaultValue: 8 });
c4.set('sys.float.padding_level6', { d4: 125830925, defaultValue: 12 });
c4.set('sys.float.padding_level8', { d4: 125830927, defaultValue: 16 });
c4.set('sys.float.margin_left', { d4: 125830936, defaultValue: 16 });
c4.set('sys.float.margin_right', { d4: 125830937, defaultValue: 16 });
c4.set('sys.float.outline_extra_larger', { d4: 125830951, defaultValue: 2 });
c4.set('sys.float.corner_radius_level4', { d4: 125830909, defaultValue: 8 });
c4.set('sys.float.Subtitle_S', { d4: 125830969, defaultValue: 14 });
c4.set('sys.float.Subtitle_L', { d4: 125830967, defaultValue: 18 });
c4.set('sys.float.Body_L', { d4: 125830970, defaultValue: 16 });
c4.set('sys.float.interactive_disable', { d4: 125831067, defaultValue: 0.4 });

export class SubHeader extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.l2 = new SynchedPropertyObjectOneWayPU(params.icon, this, 'icon');
        this.iconSymbolOptions = null;
        this.m2 = new SynchedPropertyObjectOneWayPU(params.primaryTitle, this, 'primaryTitle');
        this.n2 = new ObservedPropertyObjectPU(new TextModifier(), this, 'primaryTitleModifier');
        this.o2 = new SynchedPropertyObjectOneWayPU(params.secondaryTitle, this, 'secondaryTitle');
        this.q2 = new ObservedPropertyObjectPU(new TextModifier(), this, 'secondaryTitleModifier');
        this.s2 = new ObservedPropertyObjectPU(new z1(), this, 'subHeaderModifier');
        this.select = null;
        this.t2 = new SynchedPropertySimpleOneWayPU(params.operationType, this, 'operationType');
        this.operationItem = null;
        this.operationSymbolOptions = null;
        this.u2 = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.v2 = new ObservedPropertySimplePU(true, this, 'ageing');
        this.w2 = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'textArrowBgColor');
        this.z2 = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'buttonBgColor');
        this.f3 = new ObservedPropertyObjectPU(-1, this, 'selectedIndex');
        this.g3 = new ObservedPropertyObjectPU('', this, 'selectValue');
        this.titleBuilder = undefined;
        this.i3 = new SynchedPropertyObjectOneWayPU(params.contentMargin, this, 'contentMargin');
        this.j3 = new SynchedPropertyObjectOneWayPU(params.contentPadding, this, 'contentPadding');
        this.subHeaderMargin = {
            start: LengthMetrics.vp(b4('sys.float.margin_left')),
            end: LengthMetrics.vp(b4('sys.float.margin_right')),
        };
        this.m3 = new ObservedPropertyObjectPU(new w1(), this, 'subHeaderTheme');
        this.addProvidedVar('subHeaderTheme', this.m3, false);
        this.isFollowingSystemFontScale = false;
        this.appMaxFontScale = 3.2;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.icon === undefined) {
            this.l2.set(null);
        }
        if (params.iconSymbolOptions !== undefined) {
            this.iconSymbolOptions = params.iconSymbolOptions;
        }
        if (params.primaryTitle === undefined) {
            this.m2.set(null);
        }
        if (params.primaryTitleModifier !== undefined) {
            this.primaryTitleModifier = params.primaryTitleModifier;
        }
        if (params.secondaryTitle === undefined) {
            this.o2.set(null);
        }
        if (params.secondaryTitleModifier !== undefined) {
            this.secondaryTitleModifier = params.secondaryTitleModifier;
        }
        if (params.subHeaderModifier !== undefined) {
            this.subHeaderModifier = params.subHeaderModifier;
        }
        if (params.select !== undefined) {
            this.select = params.select;
        }
        if (params.operationType === undefined) {
            this.t2.set(OperationType.BUTTON);
        }
        if (params.operationItem !== undefined) {
            this.operationItem = params.operationItem;
        }
        if (params.operationSymbolOptions !== undefined) {
            this.operationSymbolOptions = params.operationSymbolOptions;
        }
        if (params.fontSize !== undefined) {
            this.fontSize = params.fontSize;
        }
        if (params.ageing !== undefined) {
            this.ageing = params.ageing;
        }
        if (params.textArrowBgColor !== undefined) {
            this.textArrowBgColor = params.textArrowBgColor;
        }
        if (params.buttonBgColor !== undefined) {
            this.buttonBgColor = params.buttonBgColor;
        }
        if (params.selectedIndex !== undefined) {
            this.selectedIndex = params.selectedIndex;
        }
        if (params.selectValue !== undefined) {
            this.selectValue = params.selectValue;
        }
        if (params.titleBuilder !== undefined) {
            this.titleBuilder = params.titleBuilder;
        }
        if (params.subHeaderMargin !== undefined) {
            this.subHeaderMargin = params.subHeaderMargin;
        }
        if (params.subHeaderTheme !== undefined) {
            this.subHeaderTheme = params.subHeaderTheme;
        }
        if (params.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
        }
        if (params.appMaxFontScale !== undefined) {
            this.appMaxFontScale = params.appMaxFontScale;
        }
    }

    updateStateVars(params) {
        this.l2.reset(params.icon);
        this.m2.reset(params.primaryTitle);
        this.o2.reset(params.secondaryTitle);
        this.t2.reset(params.operationType);
        this.i3.reset(params.contentMargin);
        this.j3.reset(params.contentPadding);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.l2.purgeDependencyOnElmtId(rmElmtId);
        this.m2.purgeDependencyOnElmtId(rmElmtId);
        this.n2.purgeDependencyOnElmtId(rmElmtId);
        this.o2.purgeDependencyOnElmtId(rmElmtId);
        this.q2.purgeDependencyOnElmtId(rmElmtId);
        this.s2.purgeDependencyOnElmtId(rmElmtId);
        this.t2.purgeDependencyOnElmtId(rmElmtId);
        this.u2.purgeDependencyOnElmtId(rmElmtId);
        this.v2.purgeDependencyOnElmtId(rmElmtId);
        this.w2.purgeDependencyOnElmtId(rmElmtId);
        this.z2.purgeDependencyOnElmtId(rmElmtId);
        this.f3.purgeDependencyOnElmtId(rmElmtId);
        this.g3.purgeDependencyOnElmtId(rmElmtId);
        this.i3.purgeDependencyOnElmtId(rmElmtId);
        this.j3.purgeDependencyOnElmtId(rmElmtId);
        this.m3.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.l2.aboutToBeDeleted();
        this.m2.aboutToBeDeleted();
        this.n2.aboutToBeDeleted();
        this.o2.aboutToBeDeleted();
        this.q2.aboutToBeDeleted();
        this.s2.aboutToBeDeleted();
        this.t2.aboutToBeDeleted();
        this.u2.aboutToBeDeleted();
        this.v2.aboutToBeDeleted();
        this.w2.aboutToBeDeleted();
        this.z2.aboutToBeDeleted();
        this.f3.aboutToBeDeleted();
        this.g3.aboutToBeDeleted();
        this.i3.aboutToBeDeleted();
        this.j3.aboutToBeDeleted();
        this.m3.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get icon() {
        return this.l2.get();
    }

    set icon(newValue) {
        this.l2.set(newValue);
    }

    get primaryTitle() {
        return this.m2.get();
    }

    set primaryTitle(newValue) {
        this.m2.set(newValue);
    }

    get primaryTitleModifier() {
        return this.n2.get();
    }

    set primaryTitleModifier(newValue) {
        this.n2.set(newValue);
    }

    get secondaryTitle() {
        return this.o2.get();
    }

    set secondaryTitle(newValue) {
        this.o2.set(newValue);
    }

    get secondaryTitleModifier() {
        return this.q2.get();
    }

    set secondaryTitleModifier(newValue) {
        this.q2.set(newValue);
    }

    get subHeaderModifier() {
        return this.s2.get();
    }

    set subHeaderModifier(newValue) {
        this.s2.set(newValue);
    }

    get operationType() {
        return this.t2.get();
    }

    set operationType(newValue) {
        this.t2.set(newValue);
    }

    get fontSize() {
        return this.u2.get();
    }

    set fontSize(newValue) {
        this.u2.set(newValue);
    }

    get ageing() {
        return this.v2.get();
    }

    set ageing(newValue) {
        this.v2.set(newValue);
    }

    get textArrowBgColor() {
        return this.w2.get();
    }

    set textArrowBgColor(newValue) {
        this.w2.set(newValue);
    }

    get buttonBgColor() {
        return this.z2.get();
    }

    set buttonBgColor(newValue) {
        this.z2.set(newValue);
    }

    get selectedIndex() {
        return this.f3.get();
    }

    set selectedIndex(newValue) {
        this.f3.set(newValue);
    }

    get selectValue() {
        return this.g3.get();
    }

    set selectValue(newValue) {
        this.g3.set(newValue);
    }

    get contentMargin() {
        return this.i3.get();
    }

    set contentMargin(newValue) {
        this.i3.set(newValue);
    }

    get contentPadding() {
        return this.j3.get();
    }

    set contentPadding(newValue) {
        this.j3.set(newValue);
    }

    get subHeaderTheme() {
        return this.m3.get();
    }

    set subHeaderTheme(newValue) {
        this.m3.set(newValue);
    }

    onWillApplyTheme(theme) {
        this.subHeaderTheme.b2 = theme.colors.fontPrimary;
        this.subHeaderTheme.c2 = theme.colors.fontSecondary;
        this.subHeaderTheme.d2 = theme.colors.fontEmphasize;
        this.subHeaderTheme.e2 = theme.colors.iconTertiary;
        this.subHeaderTheme.f2 = theme.colors.interactiveHover;
        this.subHeaderTheme.g2 = theme.colors.interactiveFocus;
        this.subHeaderTheme.h2 = theme.colors.iconSecondary;
        this.subHeaderTheme.i2 = theme.colors.iconPrimary;
    }

    updateFontScale() {
        try {
            let uiContext = this.getUIContext();
            let v6 = uiContext.getHostContext()?.config.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(v6, this.appMaxFontScale);
        } catch (u6) {
            let code = u6.code;
            let message = u6.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
            return 1;
        }
    }

    async aboutToAppear() {
        let uiContext = this.getUIContext();
        this.isFollowingSystemFontScale = uiContext.isFollowingSystemFontScale();
        this.appMaxFontScale = uiContext.getMaxFontScale();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.j2 = this.ageing;
        } else {
            this.ageing = false;
            this.subHeaderModifier.j2 = this.ageing;
        }
        if (this.select) {
            this.selectedIndex = this.select.selected;
            this.selectValue = this.select.value;
        }
    }

    isSuitableAging() {
        return (this.fontSize >= m1) && ((this.operationType === OperationType.TEXT_ARROW) ||
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
                            top: LengthMetrics.vp(b4('sys.float.padding_level8')),
                            bottom: LengthMetrics.vp(b4('sys.float.padding_level1')),
                        });
                        Row.padding({
                            start: this.contentMargin ? this.contentMargin.start :
                            LengthMetrics.vp(b4('sys.float.margin_left')),
                            end: this.contentMargin ? this.contentMargin.end :
                            LengthMetrics.vp(b4('sys.float.margin_right')),
                        });
                        Row.width('100%');
                        Row.accessibilityGroup(this.isLeftAreaAccessibilityGroup());
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.contentMargin ?? this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.margin({
                            top: this.fontSize >= m1 ? b4('sys.float.padding_level8') : '',
                            bottom: this.fontSize >= m1 ? b4('sys.float.padding_level4') : '',
                        });
                        Row.width('100%');
                        Row.flexShrink(1);
                        Row.accessibilityGroup(this.isLeftAreaAccessibilityGroup());
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            return Util.a4(125833704, '');
        }
        return '';
    }

    rightAreaParentAging(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        Button.onTouch((event) => {
                            if (event.type === TouchType.Down) {
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
                            if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
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
                            bottom: b4('sys.float.padding_level4'),
                        });
                        Button.padding({
                            start: LengthMetrics.vp((this.contentMargin ?
                                (this.contentMargin.start ? this.contentMargin.start.value : 0) :
                            b4('sys.float.margin_left')) - m4),
                            end: this.contentMargin ? this.contentMargin.end :
                            LengthMetrics.vp(b4('sys.float.margin_right')),
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        Row.onTouch((event) => {
                            if (event.type === TouchType.Down) {
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
                            if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
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
                            bottom: b4('sys.float.padding_level4'),
                        });
                        Row.padding({
                            start: LengthMetrics.vp((this.contentMargin ?
                                (this.contentMargin.start ? this.contentMargin.start.value : 0) :
                            b4('sys.float.margin_left')) - m4),
                            end: this.contentMargin ? this.contentMargin.end :
                            LengthMetrics.vp(b4('sys.float.margin_right')),
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

    rightAreaParent(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItem ? true : false);
                        Button.margin(f4);
                        Button.padding(f4);
                        Button.align(Alignment.BottomEnd);
                        Button.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Button.onTouch((event) => {
                            if (event.type === TouchType.Down) {
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
                            if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
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
                            minHeight: n1,
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        Row.onTouch((event) => {
                            if (event.type === TouchType.Down) {
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
                            if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
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
                            minHeight: n1,
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

    onMeasureSize(selfLayoutInfo, children, constraint) {
        let result = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
        let context = this.getUIContext().getHostContext();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.j2 = this.ageing;
        } else {
            this.ageing = false;
            this.subHeaderModifier.j2 = this.ageing;
        }
        children.forEach((child) => {
            constraint.minHeight = Math.min(Number(this.getMinHeight()), Number(constraint.maxHeight));
            result.height = child.measure(constraint).height;
            result.width = Number(constraint.maxWidth);
        });
        return result;
    }

    onPlaceChildren(selfLayoutInfo, children, constraint) {
        children.forEach((child) => {
            child.layout({ x: 0, y: 0 });
        });
    }

    getRightAreaMaxWidth() {
        if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
            return '100%';
        }
        return l1;
    }

    getRightAreaMinWidth() {
        if (this.operationItem && this.operationItem.length > 0) {
            return n1;
        }
        return 0;
    }

    getMinHeight() {
        if (this.secondaryTitle && this.icon) {
            return u;
        } else if (this.secondaryTitle && this.primaryTitle) {
            return a1;
        }
        return u;
    }

    getTextArrowPaddingLeft() {
        if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
            return LengthMetrics.vp(b4('sys.float.padding_level1'));
        }
        return LengthMetrics.vp(b4('sys.float.padding_level0'));
    }

    getTextArrowMarginRight() {
        if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
            return LengthMetrics.vp(j1 + g1);
        }
        return LengthMetrics.vp(g1);
    }

    getAreaPadding() {
        if (this.contentPadding) {
            return this.contentPadding;
        }
        let padding = {};
        if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
            (!this.primaryTitle && this.secondaryTitle))) {
            padding = {
                start: LengthMetrics.vp(b4('sys.float.padding_level6')),
                end: LengthMetrics.vp(b4('sys.float.padding_level6')),
            };
        }
        return padding;
    }

    leftArea(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.titleBuilder) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.titleBuilder.bind(this)();
                });
            } else if (this.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondaryTitleStyle', {
                        content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']),
                        q3: () => ({
                            icon: this.icon,
                            r3: this.iconSymbolOptions,
                        })
                    }));
                });
            } else if (this.secondaryTitle && this.primaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle', {
                        content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']),
                        s3: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle'])
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

    rightArea(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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

    IconSecondaryTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.vp(b4('sys.float.padding_level6')),
                top: this.fontSize >= m1 ? LengthMetrics.vp(b4('sys.float.padding_level0'))
                    : LengthMetrics.vp(b4('sys.float.padding_level4')),
                bottom: this.fontSize >= m1 ? LengthMetrics.vp(b4('sys.float.padding_level0'))
                    : LengthMetrics.vp(b4('sys.float.padding_level4')),
            });
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (Util.t3($$.q3?.icon)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create($$.q3?.icon);
                        SymbolGlyph.fontSize($$.q3?.r3?.fontSize ?
                        Util.u3($$.q3?.r3?.fontSize) : c1);
                        SymbolGlyph.fontColor($$.q3?.r3?.fontColor ?? [this.subHeaderTheme.h2]);
                        SymbolGlyph.fontWeight($$.q3?.r3?.fontWeight);
                        SymbolGlyph.renderingStrategy($$.q3?.r3?.renderingStrategy);
                        SymbolGlyph.effectStrategy($$.q3?.r3?.effectStrategy);
                        SymbolGlyph.margin({ end: LengthMetrics.vp(b4('sys.float.padding_level4')) });
                        SymbolGlyph.flexShrink(0);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create($$.q3?.icon);
                        Image.fillColor(this.subHeaderTheme.h2);
                        Image.width(c1);
                        Image.height(c1);
                        Image.margin({ end: LengthMetrics.vp(b4('sys.float.padding_level4')) });
                        Image.draggable(false);
                        Image.flexShrink(0);
                    }, Image);
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
            i({
                maxLines: t,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.c2,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
            Text.flexShrink(1);
        }, Text);
        Text.pop();
        Flex.pop();
    }

    SubTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.padding({
                end: LengthMetrics.vp(b4('sys.float.padding_level0')),
                top: this.fontSize >= m1 ? LengthMetrics.vp(b4('sys.float.padding_level0'))
                    : LengthMetrics.vp(b4('sys.float.padding_level4')),
                bottom: this.fontSize >= m1 ? LengthMetrics.vp(b4('sys.float.padding_level0'))
                    : LengthMetrics.vp(b4('sys.float.padding_level4')),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
            j({
                fontWeight: FontWeight.Bold,
                maxLines: t,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.b2,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
            Text.width('100%');
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.s3);
            i({
                maxLines: t,
                fontWeight: FontWeight.Regular,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.c2,
            });
            Text.width('100%');
            Text.margin({
                top: b4('sys.float.padding_level1'),
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
        }, Text);
        Text.pop();
        Column.pop();
    }

    SecondTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
            i({
                maxLines: t,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.c2,
            });
            Text.width('100%');
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
            Text.padding({
                end: LengthMetrics.vp(b4('sys.float.padding_level6')),
                top: this.fontSize >= m1 ? LengthMetrics.vp(b4('sys.float.padding_level0'))
                    : LengthMetrics.vp(b4('sys.float.padding_level4')),
                bottom: this.fontSize >= m1 ? LengthMetrics.vp(b4('sys.float.padding_level0'))
                    : LengthMetrics.vp(b4('sys.float.padding_level4')),
            });
        }, Text);
        Text.pop();
    }

    SelectStyle(r4, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Select.create(r4.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
            Select.value(ObservedObject.GetRawObject(this.selectValue));
            Select.onSelect((index, value) => {
                this.selectedIndex = index;
                if (value) {
                    this.selectValue = value;
                }
                if (r4.onSelect) {
                    r4.onSelect(index, value);
                }
            });
            Select.font({
                size: `${b4('sys.float.Body_L')}fp`,
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
    }

    PrimaryTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
            j({
                fontWeight: FontWeight.Bold,
                maxLines: t,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.b2,
            });
            Text.width('100%');
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
            Text.padding({
                end: LengthMetrics.vp(b4('sys.float.padding_level0')),
                top: this.fontSize >= m1 ? LengthMetrics.vp(b4('sys.float.padding_level0'))
                    : LengthMetrics.vp(b4('sys.float.padding_level4')),
                bottom: this.fontSize >= m1 ? LengthMetrics.vp(b4('sys.float.padding_level0'))
                    : LengthMetrics.vp(b4('sys.float.padding_level4')),
            });
        }, Text);
        Text.pop();
    }

    ButtonStyle(button, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (button) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(true);
                        Button.focusBox({
                            margin: { value: f4, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.g2),
                            strokeWidth: LengthMetrics.vp(b4('sys.float.outline_extra_larger')),
                        });
                        Button.padding({
                            start: LengthMetrics.vp(b4('sys.float.padding_level1')),
                            end: LengthMetrics.vp(b4('sys.float.padding_level1')),
                            top: LengthMetrics.vp(b4('sys.float.padding_level2')),
                            bottom: LengthMetrics.vp(b4('sys.float.padding_level2')),
                        });
                        Button.margin({
                            start: this.ageing ?
                            LengthMetrics.vp(LengthMetrics.vp(b4('sys.float.padding_level0')).value +
                            this.leftIconMargin().value) :
                            LengthMetrics.vp(LengthMetrics.vp(b4('sys.float.padding_level4')).value +
                            this.leftIconMargin().value),
                            bottom: LengthMetrics.vp(this.ageing ? b4('sys.float.padding_level0') :
                            b4('sys.float.padding_level2')),
                        });
                        Button.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
                        Button.constraintSize({ minHeight: f1 });
                        Button.align(Alignment.End);
                        Button.borderRadius(b4('sys.float.corner_radius_level4'));
                        Button.onHover((isHover) => {
                            if (isHover) {
                                this.buttonBgColor = this.subHeaderTheme.f2;
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
                        Button.opacity(b4('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                    }, Button);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(button.value);
                        i({
                            fontWeight: FontWeight.Medium,
                            maxLines: t,
                            fontColor: this.subHeaderTheme.d2,
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
        if (this.icon && Util.t3(this.icon)) {
            return this.ageing ? LengthMetrics.vp((this.iconSymbolOptions?.fontSize ?
            Util.v3(this.iconSymbolOptions?.fontSize) : d1) + e1) : LengthMetrics.vp(0);
        } else {
            return (this.ageing && this.icon) ? LengthMetrics.vp(d1 + e1) : LengthMetrics.vp(0);
        }
    }

    TextStyle(p7, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.subHeaderModifier));
            Row.alignItems(VerticalAlign.Center);
            Row.focusable(true);
            Row.constraintSize({ minHeight: f1 });
            Row.padding({
                start: this.getTextArrowPaddingLeft(),
                top: this.ageing ? LengthMetrics.vp(0) : LengthMetrics.vp(b4('sys.float.padding_level2')),
                bottom: this.ageing ? LengthMetrics.vp(0) : LengthMetrics.vp(b4('sys.float.padding_level2')),
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (p7) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(p7.value);
                        i({
                            maxLines: t,
                            fontWeight: FontWeight.Regular,
                            alignment: Alignment.End,
                            fontColor: this.subHeaderTheme.c2,
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

    ArrowStyle(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create({
                'id': -1,
                'type': 20000,
                params: ['sys.media.ohos_ic_public_arrow_right'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Image.fillColor(this.subHeaderTheme.e2);
            Image.width(g1);
            Image.height(f1);
            Image.focusable(true);
            Image.draggable(false);
            Image.matchTextDirection(true);
        }, Image);
        Row.pop();
    }

    TextArrowStyle(s3, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (s3 && s3.value && s3.value.toString().length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.focusable(true);
                        Stack.align(this.ageing ? Alignment.Start : Alignment.End);
                        Stack.margin({
                            start: LengthMetrics.vp(this.ageing ? b4('sys.float.padding_level0') :
                            b4('sys.float.padding_level4')),
                            bottom: LengthMetrics.vp(this.ageing ? b4('sys.float.padding_level0') :
                            b4('sys.float.padding_level2')),
                        });
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.padding(f4);
                        Button.margin({ start: this.leftIconMargin() });
                        Button.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
                        Button.focusBox({
                            margin: { value: f4, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.g2),
                            strokeWidth: LengthMetrics.vp(b4('sys.float.outline_extra_larger')),
                        });
                        Button.borderRadius(b4('sys.float.corner_radius_level4'));
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(b4('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                        Button.onHover((isHover) => {
                            if (isHover) {
                                this.textArrowBgColor = this.subHeaderTheme.f2;
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
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new o4(this, {
                                    textArrowBuilder: () => {
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            ForEach.create();
                                            const forEachItemGenFunction = _item => {
                                                const index = _item;
                                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                    If.create();
                                                    if (index === f4) {
                                                        this.ifElseBranchUpdateFunction(0, () => {
                                                            this.TextStyle.bind(this)(s3);
                                                        });
                                                    } else {
                                                        this.ifElseBranchUpdateFunction(1, () => {
                                                            this.ArrowStyle.bind(this)();
                                                        });
                                                    }
                                                }, If);
                                                If.pop();
                                            };
                                            this.forEachUpdateFunction(elmtId, [f4, j4], forEachItemGenFunction);
                                        }, ForEach);
                                        ForEach.pop();
                                    }
                                }, undefined, elmtId, () => {
                                }, { page: 'library/src/main/ets/components/subheader.ets', line: 827, x3: 11 });
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
                                                        if (index === f4) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.TextStyle.bind(this)(s3);
                                                            });
                                                        } else {
                                                            this.ifElseBranchUpdateFunction(1, () => {
                                                                this.ArrowStyle.bind(this)();
                                                            });
                                                        }
                                                    }, If);
                                                    If.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, [f4, j4], forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                        }
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            } else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {});
                            }
                        }, { name: 'TextArrowLayout' });
                    }
                    Button.pop();
                    Stack.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.focusable(true);
                        Row.constraintSize({ minWidth: this.getRightAreaMinWidth() });
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.width(g1);
                        Button.height(f1);
                        Button.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
                        Button.focusBox({
                            margin: { value: f4, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.g2),
                            strokeWidth: LengthMetrics.vp(b4('sys.float.outline_extra_larger')),
                        });
                        Button.borderRadius(b4('sys.float.corner_radius_level4'));
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(b4('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                        Button.onHover((isHover) => {
                            if (isHover) {
                                this.textArrowBgColor = this.subHeaderTheme.f2;
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
                            start: LengthMetrics.vp(this.ageing ? b4('sys.float.padding_level0') :
                            b4('sys.float.padding_level4')),
                            bottom: LengthMetrics.vp(this.ageing ? b4('sys.float.padding_level0') :
                            b4('sys.float.padding_level2')),
                        });
                    }, Button);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create({
                            'id': -1,
                            'type': 20000,
                            params: ['sys.media.ohos_ic_public_arrow_right'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Image.fillColor(this.subHeaderTheme.e2);
                        Image.width(g1);
                        Image.height(f1);
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

    IconGroupStyle(operationItem, parent = null) {
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
                    if (Util.w3(item.value)) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                If.create();
                                if (index <= m) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            __Common__.create();
                                            __Common__.margin({
                                                start: LengthMetrics.vp(b4('sys.float.padding_level4')),
                                                bottom: LengthMetrics.vp(b4('sys.float.padding_level3')),
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                if (isInitialRender) {
                                                    let componentCall = new a2(this, {
                                                        item: {
                                                            q3: {
                                                                icon: item.value,
                                                                r3: this.operationSymbolOptions &&
                                                                    this.operationSymbolOptions.length > index ?
                                                                this.operationSymbolOptions[index] : null,
                                                            },
                                                            action: item.action,
                                                        },
                                                        isSingleIcon: this.operationItem?.length === u1,
                                                    }, undefined, elmtId, () => {
                                                    }, {
                                                        page: 'library/src/main/ets/components/subheader.ets',
                                                        line: 917,
                                                        x3: 13
                                                    });
                                                    ViewPU.create(componentCall);
                                                    let paramsLambda = () => {
                                                        return {
                                                            item: {
                                                                q3: {
                                                                    icon: item.value,
                                                                    r3: this.operationSymbolOptions &&
                                                                        this.operationSymbolOptions.length > index ?
                                                                    this.operationSymbolOptions[index] : null,
                                                                },
                                                                action: item.action,
                                                            },
                                                            isSingleIcon: this.operationItem?.length === u1
                                                        };
                                                    };
                                                    componentCall.paramsGenerator_ = paramsLambda;
                                                } else {
                                                    this.updateStateVarsOfChildByElmtId(elmtId, {});
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
            this.forEachUpdateFunction(elmtId, operationItem, forEachItemGenFunction, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    LoadingProcessStyle(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.padding({
                top: b4('sys.float.padding_level2'),
                bottom: b4('sys.float.padding_level2'),
            });
            Row.margin({
                start: LengthMetrics.vp(b4('sys.float.padding_level4')),
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            LoadingProgress.create();
            LoadingProgress.width(f1);
            LoadingProgress.height(f1);
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

    dummyFunction(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
        }, Row);
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class a2 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.y3 = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'bgColor');
        this.z3 = new ObservedPropertySimplePU(false, this, 'isFocus');
        this.item = null;
        this.m3 = this.initializeConsume('subHeaderTheme', 'subHeaderTheme');
        this.isSingleIcon = true;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.bgColor !== undefined) {
            this.bgColor = params.bgColor;
        }
        if (params.isFocus !== undefined) {
            this.isFocus = params.isFocus;
        }
        if (params.item !== undefined) {
            this.item = params.item;
        }
        if (params.isSingleIcon !== undefined) {
            this.isSingleIcon = params.isSingleIcon;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.y3.purgeDependencyOnElmtId(rmElmtId);
        this.z3.purgeDependencyOnElmtId(rmElmtId);
        this.m3.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.y3.aboutToBeDeleted();
        this.z3.aboutToBeDeleted();
        this.m3.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get bgColor() {
        return this.y3.get();
    }

    set bgColor(newValue) {
        this.y3.set(newValue);
    }

    get isFocus() {
        return this.z3.get();
    }

    set isFocus(newValue) {
        this.z3.set(newValue);
    }

    get subHeaderTheme() {
        return this.m3.get();
    }

    set subHeaderTheme(newValue) {
        this.m3.set(newValue);
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.item && this.item.q3) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(true);
                        Button.width(h1);
                        Button.height(h1);
                        Button.align(Alignment.Center);
                        Button.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
                        Button.borderRadius(b4('sys.float.corner_radius_level4'));
                        Button.focusBox({
                            margin: { value: f4, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.g2),
                            strokeWidth: LengthMetrics.vp(b4('sys.float.outline_extra_larger')),
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
                        Button.opacity(b4('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState();
                        Button.onTouch((event) => {
                            if (event.type === TouchType.Down || TouchType.Cancel) {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.interactive_pressed'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                            if (event.type === TouchType.Up) {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                        });
                        Button.onHover((isHover) => {
                            if (isHover) {
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
                        Button.onClick((event) => {
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
                x: t1,
                y: s1,
                width: n1,
                height: n1,
            };
        }
        return {
            x: q1,
            y: s1,
            width: o1,
            height: n1,
        };
    }

    fontSizeValue(item) {
        return item.q3?.r3?.fontSize ?
        Util.u3(item.q3?.r3?.fontSize) : i1;
    }

    IconZone(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.item && this.item.q3) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (Util.t3(this.item.q3.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create(this.item.q3?.icon);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.fontSize(this.fontSizeValue(this.item));
                                    SymbolGlyph.fontColor(this.item.q3?.r3?.fontColor ?? [this.subHeaderTheme.i2]);
                                    SymbolGlyph.fontWeight(this.item.q3?.r3?.fontWeight);
                                    SymbolGlyph.renderingStrategy(this.item.q3?.r3?.renderingStrategy);
                                    SymbolGlyph.effectStrategy(this.item.q3?.r3?.effectStrategy);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Image.create(this.item?.q3?.icon);
                                    Image.fillColor(this.subHeaderTheme.i2);
                                    Image.width(i1);
                                    Image.height(i1);
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
    static t3(g2) {
        if (!Util.w3(g2)) {
            return false;
        }
        let resource = g2;
        return resource.type === b1;
    }

    static w3(resource) {
        if (!resource) {
            return false;
        }
        if (typeof resource === 'string' || typeof resource === 'undefined') {
            return false;
        }
        return true;
    }

    static n3(d2, e2) {
        try {
            let f2 = resourceManager.getSystemResourceManager().getNumber(d2);
            if (f2 === 0) {
                return e2;
            } else {
                return f2;
            }
        } catch (error) {
            let code = error.code;
            let message = error.message;
            hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${code}, message: ${message}`);
            return 0;
        }
    }

    static a4(v2, t3) {
        try {
            let e4 = getContext().resourceManager.getStringSync(v2);
            if (e4 === '') {
                return t3;
            } else {
                return e4;
            }
        } catch (error) {
            let code = error.code;
            let message = error.message;
            hilog.error(0x3900, 'Ace', `SubHeader getStringByResource error, code: ${code}, message: ${message}`);
            return '';
        }
    }

    static v3(fontSize) {
        if (typeof fontSize === 'string') {
            const c2 = parseInt(fontSize);
            return c2;
        } else if (typeof fontSize === 'number') {
            return fontSize;
        } else {
            return getContext().resourceManager.getNumber(fontSize);
        }
    }

    static u3(fontSize) {
        return Util.v3(fontSize) + 'vp';
    }
}

function b4(resourceName) {
    if (c4.hasKey(resourceName)) {
        let d4 = c4.get(resourceName).e4;
        if (typeof d4 === 'number') {
            return d4;
        } else {
            d4 = Util.n3(c4.get(resourceName).d4, c4.get(resourceName).defaultValue);
            c4.get(resourceName).e4 = d4;
            return d4;
        }
    }
    return 0;
}

class o4 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
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
        let j6 = 0;
        let k6 = 0;
        for (let index = 0; index < children.length; index++) {
            let child = children[index];
            child.layout({ x: j6, y: k6 });
        }
    }

    onMeasureSize(selfLayoutInfo, children, constraint) {
        let w4 = g1;
        let a5 = f1;
        let d5 = children[f4];
        let e5 = {
            minWidth: Math.max(w4, Number(constraint.minWidth)),
            maxWidth: constraint.maxWidth,
            minHeight: Math.max(a5, Number(constraint.minHeight)),
            maxHeight: constraint.maxHeight,
        };
        let l5 = d5.measure(e5);
        w4 = Math.max(w4, l5.width);
        a5 = Math.max(a5, l5.height);
        let m5 = children[j4];
        let n5 = {
            minWidth: w4,
            maxWidth: w4,
            minHeight: a5,
            maxHeight: a5,
        };
        m5.measure(n5);
        return { width: w4, height: a5 };
    }

    initialRender() {
        this.textArrowBuilder.bind(this)();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default { OperationType, SubHeader };