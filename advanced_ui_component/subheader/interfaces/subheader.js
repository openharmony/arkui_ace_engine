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
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
if (PUV2ViewBase.contextStack === undefined) {
    Reflect.set(PUV2ViewBase, 'contextStack', []);
}

const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const resourceManager = requireNapi('resourceManager');
const BusinessError = requireNapi('base');
const common = requireNapi('app.ability.common');
const hilog = requireNapi('hilog');

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
        this.b2 = { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.c2 = { 'id': -1, 'type': 10001, params: ['sys.color.font_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.d2 = { 'id': -1, 'type': 10001, params: ['sys.color.font_emphasize'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.e2 = { 'id': -1, 'type': 10001, params: ['sys.color.icon_tertiary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.f2 = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.g2 = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_focus'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.h2 = { 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.i2 = { 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
}
function i(fontStyle) {
    Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Subtitle_S'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontColor(fontStyle?.fontColor ?? { 'id': -1, 'type': 10001, params: ['sys.color.font_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontWeight(fontStyle?.fontWeight);
    Text.maxLines(fontStyle?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(fontStyle?.alignment);
}
function j(fontStyle) {
    Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Subtitle_L'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontColor(fontStyle?.fontColor ?? { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
        }
        else {
        }
    }
}
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
        this.callbackId = undefined;
        this.u2 = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.v2 = new ObservedPropertySimplePU(true, this, 'ageing');
        this.w2 = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'textArrowBgColor');
        this.z2 = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'buttonBgColor');
        this.a3 = new ObservedPropertySimplePU(0, this, 'buttonStyleWidth');
        this.b3 = new ObservedPropertySimplePU(0, this, 'buttonStyleHeight');
        this.c3 = new ObservedPropertySimplePU(0, this, 'textArrowStyleWidth');
        this.d3 = new ObservedPropertySimplePU(0, this, 'textArrowStyleHeight');
        this.e3 = new ObservedPropertySimplePU(0, this, 'iconWidth');
        this.f3 = new ObservedPropertyObjectPU(-1, this, 'selectedIndex');
        this.g3 = new ObservedPropertyObjectPU('', this, 'selectValue');
        this.h3 = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, 'flexAlign');
        this.titleBuilder = undefined;
        this.i3 = new SynchedPropertyObjectOneWayPU(params.contentMargin, this, 'contentMargin');
        this.j3 = new SynchedPropertyObjectOneWayPU(params.contentPadding, this, 'contentPadding');
        this.l3 = new ObservedPropertyObjectPU({
            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
        }, this, 'subHeaderMargin');
        this.m3 = new ObservedPropertyObjectPU(new w1(), this, 'subHeaderTheme');
        this.addProvidedVar('subHeaderTheme', this.m3, false);
        this.isFollowingSystemFontScale = false;
        this.appMaxFontScale = 3.2;
        this.constraintWidth = 0;
        this.paddingLeft = 2;
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
        if (params.callbackId !== undefined) {
            this.callbackId = params.callbackId;
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
        if (params.buttonStyleWidth !== undefined) {
            this.buttonStyleWidth = params.buttonStyleWidth;
        }
        if (params.buttonStyleHeight !== undefined) {
            this.buttonStyleHeight = params.buttonStyleHeight;
        }
        if (params.textArrowStyleWidth !== undefined) {
            this.textArrowStyleWidth = params.textArrowStyleWidth;
        }
        if (params.textArrowStyleHeight !== undefined) {
            this.textArrowStyleHeight = params.textArrowStyleHeight;
        }
        if (params.iconWidth !== undefined) {
            this.iconWidth = params.iconWidth;
        }
        if (params.selectedIndex !== undefined) {
            this.selectedIndex = params.selectedIndex;
        }
        if (params.selectValue !== undefined) {
            this.selectValue = params.selectValue;
        }
        if (params.flexAlign !== undefined) {
            this.flexAlign = params.flexAlign;
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
        if (params.constraintWidth !== undefined) {
            this.constraintWidth = params.constraintWidth;
        }
        if (params.paddingLeft !== undefined) {
            this.paddingLeft = params.paddingLeft;
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
        this.a3.purgeDependencyOnElmtId(rmElmtId);
        this.b3.purgeDependencyOnElmtId(rmElmtId);
        this.c3.purgeDependencyOnElmtId(rmElmtId);
        this.d3.purgeDependencyOnElmtId(rmElmtId);
        this.e3.purgeDependencyOnElmtId(rmElmtId);
        this.f3.purgeDependencyOnElmtId(rmElmtId);
        this.g3.purgeDependencyOnElmtId(rmElmtId);
        this.h3.purgeDependencyOnElmtId(rmElmtId);
        this.i3.purgeDependencyOnElmtId(rmElmtId);
        this.j3.purgeDependencyOnElmtId(rmElmtId);
        this.l3.purgeDependencyOnElmtId(rmElmtId);
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
        this.a3.aboutToBeDeleted();
        this.b3.aboutToBeDeleted();
        this.c3.aboutToBeDeleted();
        this.d3.aboutToBeDeleted();
        this.e3.aboutToBeDeleted();
        this.f3.aboutToBeDeleted();
        this.g3.aboutToBeDeleted();
        this.h3.aboutToBeDeleted();
        this.i3.aboutToBeDeleted();
        this.j3.aboutToBeDeleted();
        this.l3.aboutToBeDeleted();
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
    get buttonStyleWidth() {
        return this.a3.get();
    }
    set buttonStyleWidth(newValue) {
        this.a3.set(newValue);
    }
    get buttonStyleHeight() {
        return this.b3.get();
    }
    set buttonStyleHeight(newValue) {
        this.b3.set(newValue);
    }
    get textArrowStyleWidth() {
        return this.c3.get();
    }
    set textArrowStyleWidth(newValue) {
        this.c3.set(newValue);
    }
    get textArrowStyleHeight() {
        return this.d3.get();
    }
    set textArrowStyleHeight(newValue) {
        this.d3.set(newValue);
    }
    get iconWidth() {
        return this.e3.get();
    }
    set iconWidth(newValue) {
        this.e3.set(newValue);
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
    get flexAlign() {
        return this.h3.get();
    }
    set flexAlign(newValue) {
        this.h3.set(newValue);
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
    get subHeaderMargin() {
        return this.l3.get();
    }
    set subHeaderMargin(newValue) {
        this.l3.set(newValue);
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
        }
        catch (u6) {
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
        }
        else {
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
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.margin({
                            top: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                            bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                        });
                        Row.padding({
                            start: this.contentMargin ? this.contentMargin.start : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                            end: this.contentMargin ? this.contentMargin.end : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                        });
                        Row.width('100%');
                        Row.accessibilityGroup(this.isLeftAreaAccessibilityGroup());
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.rightAreaParentAging.bind(this)();
                    Column.pop();
                });
            }
            else {
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
                            top: this.fontSize >= m1 ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : '',
                            bottom: this.fontSize >= m1 ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : '',
                        });
                        Row.width('100%');
                        Row.flexShrink(1);
                        Row.accessibilityGroup(this.isLeftAreaAccessibilityGroup());
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.rightAreaParent.bind(this)();
                    Flex.pop();
                });
            }
        }, If);
        If.pop();
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
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
            Button.align(Alignment.Start);
            Button.onClick(() => {
                if ((this.operationType === OperationType.TEXT_ARROW || this.operationType === OperationType.BUTTON) &&
                this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                    this.operationItem[0].action();
                }
            });
            Button.onTouch((event) => {
                if (event.type === TouchType.Down) {
                    if (this.operationType === OperationType.TEXT_ARROW) {
                        this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                    }
                    if (this.operationType === OperationType.BUTTON) {
                        this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                    }
                }
                if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                    if (this.operationType === OperationType.TEXT_ARROW) {
                        this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                    }
                    if (this.operationType === OperationType.BUTTON) {
                        this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                    }
                }
            });
            Button.margin({
                bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            Button.padding({
                start: LengthMetrics.vp((this.contentMargin ? (this.contentMargin.start ? this.contentMargin.start.value : 0) :
                Util.n3(125830936, d1)) - this.paddingLeft),
                end: this.contentMargin ? this.contentMargin.end :
                LengthMetrics.vp(Util.n3(125830937, d1)),
            });
            Button.width('100%');
            Button.accessibilityLevel(this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW ?
                'yes' : 'no');
            Button.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.accessibilityText(this.getRightAreaAccessibilityText());
        }, Button);
        this.rightArea.bind(this)();
        Button.pop();
    }
    rightAreaParent(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
            Button.align(Alignment.BottomEnd);
            Button.onClick(() => {
                if ((this.operationType === OperationType.TEXT_ARROW || this.operationType === OperationType.BUTTON) &&
                this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                    this.operationItem[0].action();
                }
            });
            Button.onTouch((event) => {
                if (event.type === TouchType.Down) {
                    if (this.operationType === OperationType.TEXT_ARROW) {
                        this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                    }
                    if (this.operationType === OperationType.BUTTON) {
                        this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                    }
                }
                if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                    if (this.operationType === OperationType.TEXT_ARROW) {
                        this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                    }
                    if (this.operationType === OperationType.BUTTON) {
                        this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                    }
                }
            });
            Button.constraintSize({
                maxWidth: this.getRightAreaMaxWidth(),
                minWidth: this.getRightAreaMinWidth(),
                minHeight: n1,
            });
            Button.flexShrink(0);
            Button.accessibilityLevel(this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW ?
                'yes' : 'no');
            Button.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.accessibilityText(this.getRightAreaAccessibilityText());
        }, Button);
        this.rightArea.bind(this)();
        Button.pop();
    }
    onMeasureSize(selfLayoutInfo, children, constraint) {
        let result = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
        let context = this.getUIContext().getHostContext();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.j2 = this.ageing;
        }
        else {
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
        }
        else if (this.secondaryTitle && this.primaryTitle) {
            return a1;
        }
        return u;
    }
    getTextArrowPaddingLeft() {
        if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
            return LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }
        return LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
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
            }
            else if (this.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondaryTitleStyle', { content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']), q3: () => ({
                        icon: this.icon,
                        r3: this.iconSymbolOptions,
                    }) }));
                });
            }
            else if (this.secondaryTitle && this.primaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle', { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']), s3: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']) }));
                });
            }
            else if (this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle', { content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']) }));
                });
            }
            else if (this.select) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.SelectStyle.bind(this)(this.select);
                });
            }
            else if (this.primaryTitle) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle', { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']) }));
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
    rightArea(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)(this.operationItem[0]);
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
            if (this.operationType === OperationType.TEXT_ARROW && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextArrowStyle.bind(this)(this.operationItem[0]);
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
            if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconGroupStyle.bind(this)(this.operationItem);
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
            if (this.operationType === OperationType.LOADING) {
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
    IconSecondaryTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: this.fontSize >= m1 ? LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })
                    : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: this.fontSize >= m1 ? LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })
                    : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Flex.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
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
                        SymbolGlyph.margin({ end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) });
                        SymbolGlyph.flexShrink(0);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create($$.q3?.icon);
                        Image.fillColor(this.subHeaderTheme.h2);
                        Image.width(c1);
                        Image.height(c1);
                        Image.margin({ end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) });
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
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: this.fontSize >= m1 ? LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })
                    : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: this.fontSize >= m1 ? LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })
                    : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Column.alignItems(HorizontalAlign.Start);
            Column.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
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
                top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
        }, Text);
        Text.pop();
        Column.pop();
    }
    SecondTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: this.fontSize >= m1 ? LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })
                    : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: this.fontSize >= m1 ? LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })
                    : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
            i({
                maxLines: t,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.c2,
            });
            Text.width('100%');
            Text.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
        }, Text);
        Text.pop();
        Column.pop();
    }
    SelectStyle(r4, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Column);
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
                size: { 'id': -1, 'type': 10002, params: ['sys.float.Body_L'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
        Column.pop();
    }
    PrimaryTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: this.fontSize >= m1 ? LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })
                    : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: this.fontSize >= m1 ? LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })
                    : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
            j({
                fontWeight: FontWeight.Bold,
                maxLines: t,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.b2,
            });
            Text.width('100%');
            Text.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
        }, Text);
        Text.pop();
        Column.pop();
    }
    ButtonStyle(button, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.margin({
                start: LengthMetrics.resource(this.ageing ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: LengthMetrics.resource(this.ageing ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.focusable(true);
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (button) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.padding({
                            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                            top: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                            bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                        });
                        Row.margin({
                            start: this.leftIconMargin(),
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
                        Row.focusable(true);
                        Row.constraintSize({ minHeight: f1 });
                        Row.justifyContent(FlexAlign.End);
                        Row.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Row.onHover((isHover) => {
                            if (isHover) {
                                this.buttonBgColor = this.subHeaderTheme.f2;
                            }
                            else {
                                this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                            }
                        });
                        Row.onSizeChange((oldValue, newValue) => {
                            this.buttonStyleWidth = Number(newValue.width);
                            this.buttonStyleHeight = Number(newValue.height);
                        });
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(button.value);
                        i({
                            fontWeight: FontWeight.Medium,
                            maxLines: t,
                            fontColor: this.subHeaderTheme.d2,
                        });
                    }, Text);
                    Text.pop();
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create();
                        Text.focusable(true);
                        Text.width(this.buttonStyleWidth);
                        Text.height(this.buttonStyleHeight);
                        Text.hitTestBehavior(HitTestMode.None);
                        ViewStackProcessor.visualState('focused');
                        Text.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: { 'id': -1, 'type': 10002, params: ['sys.float.outline_extra_larger'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            color: this.subHeaderTheme.g2,
                        });
                        ViewStackProcessor.visualState('pressed');
                        Text.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        ViewStackProcessor.visualState('disabled');
                        Text.opacity({ 'id': -1, 'type': 10002, params: ['sys.float.interactive_disable'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        ViewStackProcessor.visualState('normal');
                        Text.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: { 'id': -1, 'type': 10002, params: ['sys.float.border_none'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        ViewStackProcessor.visualState();
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
        Stack.pop();
        Row.pop();
    }
    leftIconMargin() {
        if (this.titleBuilder) {
            return LengthMetrics.vp(0);
        }
        if (this.icon && Util.t3(this.icon)) {
            return this.ageing ? LengthMetrics.vp((this.iconSymbolOptions?.fontSize ?
            Util.v3(this.iconSymbolOptions?.fontSize) : d1) + e1) : LengthMetrics.vp(0);
        }
        else {
            return (this.ageing && this.icon) ? LengthMetrics.vp(d1 + e1) : LengthMetrics.vp(0);
        }
    }
    TextArrowStyle(s3, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.subHeaderModifier));
            Row.focusable(true);
            Row.justifyContent(this.ageing ? FlexAlign.SpaceBetween : FlexAlign.End);
            Row.margin({
                start: LengthMetrics.resource(this.ageing ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: LengthMetrics.resource(this.ageing ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.margin({
                start: this.leftIconMargin(),
            });
            Stack.onHover((isHover) => {
                if (isHover) {
                    this.textArrowBgColor = this.subHeaderTheme.f2;
                }
                else {
                    this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                }
            });
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.subHeaderModifier));
            Row.alignItems(VerticalAlign.Center);
            Row.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Row.focusable(true);
            Row.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
            Row.constraintSize({ minHeight: f1 });
            Row.padding({
                start: this.getTextArrowPaddingLeft(),
                top: this.ageing ? LengthMetrics.vp(0) : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: this.ageing ? LengthMetrics.vp(0) : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Row.onSizeChange((oldValue, newValue) => {
                this.textArrowStyleWidth = Number(newValue.width);
                this.textArrowStyleHeight = Number(newValue.height);
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (s3) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(s3.value);
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
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.height(this.textArrowStyleHeight);
            Row.width(this.textArrowStyleWidth);
            Row.hitTestBehavior(HitTestMode.None);
            ViewStackProcessor.visualState('focused');
            Row.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.outline_extra_larger'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: this.subHeaderTheme.g2,
            });
            ViewStackProcessor.visualState('pressed');
            Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            ViewStackProcessor.visualState('disabled');
            Row.opacity({ 'id': -1, 'type': 10002, params: ['sys.float.interactive_disable'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            ViewStackProcessor.visualState('normal');
            Row.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.border_none'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            ViewStackProcessor.visualState();
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create({ 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_arrow_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.fillColor(this.subHeaderTheme.e2);
            Image.width(g1);
            Image.height(f1);
            Image.focusable(true);
            Image.draggable(false);
            Image.matchTextDirection(true);
        }, Image);
        Row.pop();
        Stack.pop();
        Row.pop();
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
                                                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                                                bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                if (isInitialRender) {
                                                    let componentCall = new a2(this, {
                                                        item: {
                                                            q3: {
                                                                icon: item.value,
                                                                r3: this.operationSymbolOptions && this.operationSymbolOptions.length > index ?
                                                                this.operationSymbolOptions[index] : null,
                                                            },
                                                            action: item.action,
                                                        },
                                                        isSingleIcon: this.operationItem?.length === u1,
                                                    }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/subheader.ets', line: 844, x3: 13 });
                                                    ViewPU.create(componentCall);
                                                    let paramsLambda = () => {
                                                        return {
                                                            item: {
                                                                q3: {
                                                                    icon: item.value,
                                                                    r3: this.operationSymbolOptions && this.operationSymbolOptions.length > index ?
                                                                    this.operationSymbolOptions[index] : null,
                                                                },
                                                                action: item.action,
                                                            },
                                                            isSingleIcon: this.operationItem?.length === u1
                                                        };
                                                    };
                                                    componentCall.paramsGenerator_ = paramsLambda;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                                                }
                                            }, { name: 'SingleIconStyle' });
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
                top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            Row.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            LoadingProgress.create();
            LoadingProgress.width(f1);
            LoadingProgress.height(f1);
            LoadingProgress.color({ 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }, LoadingProgress);
        Row.pop();
    }
    dummyFunction(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.onAppear(() => {
                this.changeFlexAlign(FlexAlign.End);
            });
        }, Row);
        Row.pop();
    }
    changeFlexAlign(z2) {
        if (this.flexAlign === z2) {
            return;
        }
        this.flexAlign = z2;
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
        this.y3 = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'bgColor');
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
                        ViewStackProcessor.visualState('normal');
                        Button.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: { 'id': -1, 'type': 10002, params: ['sys.float.border_none'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        ViewStackProcessor.visualState('focused');
                        Button.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: { 'id': -1, 'type': 10002, params: ['sys.float.outline_extra_larger'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            color: this.subHeaderTheme.g2,
                            style: BorderStyle.Solid,
                        });
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity({ 'id': -1, 'type': 10002, params: ['sys.float.interactive_disable'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        ViewStackProcessor.visualState();
                        Button.onTouch((event) => {
                            if (event.type === TouchType.Down || TouchType.Cancel) {
                                this.bgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                            }
                            if (event.type === TouchType.Up) {
                                this.bgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                            }
                        });
                        Button.onHover((isHover) => {
                            if (isHover) {
                                this.bgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                            }
                            else {
                                this.bgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
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
                x: t1,
                y: s1,
                width: n1,
                height: n1
            };
        }
        return {
            x: q1,
            y: s1,
            width: o1,
            height: n1
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
                        }
                        else {
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
            }
            else {
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
            }
            else {
                return f2;
            }
        }
        catch (error) {
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
            }
            else {
                return e4;
            }
        }
        catch (error) {
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
        }
        else if (typeof fontSize === 'number') {
            return fontSize;
        }
        else {
            return getContext().resourceManager.getNumber(fontSize);
        }
    }
    static u3(fontSize) {
        return Util.v3(fontSize) + 'vp';
    }
}

export default { OperationType, SubHeader };