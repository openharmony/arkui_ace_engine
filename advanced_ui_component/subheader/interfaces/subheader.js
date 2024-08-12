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
export var OperationType;
(function (b13) {
    b13[b13['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
    b13[b13['BUTTON'] = 1] = 'BUTTON';
    b13[b13['ICON_GROUP'] = 2] = 'ICON_GROUP';
    b13[b13['LOADING'] = 3] = 'LOADING';
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
        this.fontPrimaryColor = { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.fontSecondaryColor = { 'id': -1, 'type': 10001, params: ['sys.color.font_secondary'],
            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.fontButtonColor = { 'id': -1, 'type': 10001, params: ['sys.color.font_emphasize'],
            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.iconArrowColor = { 'id': -1, 'type': 10001, params: ['sys.color.icon_tertiary'],
            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.textArrowHoverBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_hover'],
            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.borderFocusColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_focus'],
            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.leftIconColor = { 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'],
            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.rightIconColor = { 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'],
            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
}
function __Text__secondaryTitleStyles(a13) {
    Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Subtitle_S'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontColor(a13?.fontColor ?? { 'id': -1, 'type': 10001, params: ['sys.color.font_secondary'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontWeight(a13?.fontWeight);
    Text.maxLines(a13?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(a13?.alignment);
}
function __Text__primaryTitleStyles(z12) {
    Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Subtitle_L'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontColor(z12?.fontColor ?? { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontWeight(z12?.fontWeight);
    Text.maxLines(z12?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(z12?.alignment);
}
class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }
    applyNormalAttribute(y12) {
        if (this.isAgeing) {
            y12.width('100%');
        }
        else {
        }
    }
}
export class SubHeader extends ViewPU {
    constructor(s12, t12, u12, v12 = -1, w12 = undefined, x12) {
        super(s12, u12, v12, x12);
        if (typeof w12 === 'function') {
            this.paramsGenerator_ = w12;
        }
        this.__icon = new SynchedPropertyObjectOneWayPU(t12.icon, this, 'icon');
        this.iconSymbolOptions = null;
        this.__primaryTitle = new SynchedPropertyObjectOneWayPU(t12.primaryTitle, this, 'primaryTitle');
        this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'primaryTitleModifier');
        this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(t12.secondaryTitle, this, 'secondaryTitle');
        this.__secondaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'secondaryTitleModifier');
        this.__subHeaderModifier = new ObservedPropertyObjectPU(new SubHeaderModifier(), this, 'subHeaderModifier');
        this.select = null;
        this.__operationType = new SynchedPropertySimpleOneWayPU(t12.operationType, this, 'operationType');
        this.operationItem = null;
        this.operationSymbolOptions = null;
        this.callbackId = undefined;
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.__ageing = new ObservedPropertySimplePU(true, this, 'ageing');
        this.__textArrowBgColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            this, 'textArrowBgColor');
        this.__buttonBgColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            this, 'buttonBgColor');
        this.__buttonStyleWidth = new ObservedPropertySimplePU(0, this, 'buttonStyleWidth');
        this.__buttonStyleHeight = new ObservedPropertySimplePU(0, this, 'buttonStyleHeight');
        this.__textArrowStyleWidth = new ObservedPropertySimplePU(0, this, 'textArrowStyleWidth');
        this.__textArrowStyleHeight = new ObservedPropertySimplePU(0, this, 'textArrowStyleHeight');
        this.__iconWidth = new ObservedPropertySimplePU(0, this, 'iconWidth');
        this.__selectedIndex = new ObservedPropertyObjectPU(-1, this, 'selectedIndex');
        this.__selectValue = new ObservedPropertyObjectPU('', this, 'selectValue');
        this.__flexAlign = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, 'flexAlign');
        this.titleBuilder = undefined;
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(t12.contentMargin, this, 'contentMargin');
        this.__contentPadding = new SynchedPropertyObjectOneWayPU(t12.contentPadding, this, 'contentPadding');
        this.__subHeaderMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_left'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_right'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
        }, this, 'subHeaderMargin');
        this.__subHeaderTheme = new ObservedPropertyObjectPU(new SubHeaderTheme(), this, 'subHeaderTheme');
        this.addProvidedVar('subHeaderTheme', this.__subHeaderTheme, false);
        this.isFollowingSystemFontScale = false;
        this.appMaxFontScale = 3.2;
        this.constraintWidth = 0;
        this.paddingLeft = 2;
        this.setInitiallyProvidedValue(t12);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r12) {
        if (r12.icon === undefined) {
            this.__icon.set(null);
        }
        if (r12.iconSymbolOptions !== undefined) {
            this.iconSymbolOptions = r12.iconSymbolOptions;
        }
        if (r12.primaryTitle === undefined) {
            this.__primaryTitle.set(null);
        }
        if (r12.primaryTitleModifier !== undefined) {
            this.primaryTitleModifier = r12.primaryTitleModifier;
        }
        if (r12.secondaryTitle === undefined) {
            this.__secondaryTitle.set(null);
        }
        if (r12.secondaryTitleModifier !== undefined) {
            this.secondaryTitleModifier = r12.secondaryTitleModifier;
        }
        if (r12.subHeaderModifier !== undefined) {
            this.subHeaderModifier = r12.subHeaderModifier;
        }
        if (r12.select !== undefined) {
            this.select = r12.select;
        }
        if (r12.operationType === undefined) {
            this.__operationType.set(OperationType.BUTTON);
        }
        if (r12.operationItem !== undefined) {
            this.operationItem = r12.operationItem;
        }
        if (r12.operationSymbolOptions !== undefined) {
            this.operationSymbolOptions = r12.operationSymbolOptions;
        }
        if (r12.callbackId !== undefined) {
            this.callbackId = r12.callbackId;
        }
        if (r12.fontSize !== undefined) {
            this.fontSize = r12.fontSize;
        }
        if (r12.ageing !== undefined) {
            this.ageing = r12.ageing;
        }
        if (r12.textArrowBgColor !== undefined) {
            this.textArrowBgColor = r12.textArrowBgColor;
        }
        if (r12.buttonBgColor !== undefined) {
            this.buttonBgColor = r12.buttonBgColor;
        }
        if (r12.buttonStyleWidth !== undefined) {
            this.buttonStyleWidth = r12.buttonStyleWidth;
        }
        if (r12.buttonStyleHeight !== undefined) {
            this.buttonStyleHeight = r12.buttonStyleHeight;
        }
        if (r12.textArrowStyleWidth !== undefined) {
            this.textArrowStyleWidth = r12.textArrowStyleWidth;
        }
        if (r12.textArrowStyleHeight !== undefined) {
            this.textArrowStyleHeight = r12.textArrowStyleHeight;
        }
        if (r12.iconWidth !== undefined) {
            this.iconWidth = r12.iconWidth;
        }
        if (r12.selectedIndex !== undefined) {
            this.selectedIndex = r12.selectedIndex;
        }
        if (r12.selectValue !== undefined) {
            this.selectValue = r12.selectValue;
        }
        if (r12.flexAlign !== undefined) {
            this.flexAlign = r12.flexAlign;
        }
        if (r12.titleBuilder !== undefined) {
            this.titleBuilder = r12.titleBuilder;
        }
        if (r12.subHeaderMargin !== undefined) {
            this.subHeaderMargin = r12.subHeaderMargin;
        }
        if (r12.subHeaderTheme !== undefined) {
            this.subHeaderTheme = r12.subHeaderTheme;
        }
        if (r12.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = r12.isFollowingSystemFontScale;
        }
        if (r12.appMaxFontScale !== undefined) {
            this.appMaxFontScale = r12.appMaxFontScale;
        }
        if (r12.constraintWidth !== undefined) {
            this.constraintWidth = r12.constraintWidth;
        }
        if (r12.paddingLeft !== undefined) {
            this.paddingLeft = r12.paddingLeft;
        }
    }
    updateStateVars(q12) {
        this.__icon.reset(q12.icon);
        this.__primaryTitle.reset(q12.primaryTitle);
        this.__secondaryTitle.reset(q12.secondaryTitle);
        this.__operationType.reset(q12.operationType);
        this.__contentMargin.reset(q12.contentMargin);
        this.__contentPadding.reset(q12.contentPadding);
    }
    purgeVariableDependenciesOnElmtId(p12) {
        this.__icon.purgeDependencyOnElmtId(p12);
        this.__primaryTitle.purgeDependencyOnElmtId(p12);
        this.__primaryTitleModifier.purgeDependencyOnElmtId(p12);
        this.__secondaryTitle.purgeDependencyOnElmtId(p12);
        this.__secondaryTitleModifier.purgeDependencyOnElmtId(p12);
        this.__subHeaderModifier.purgeDependencyOnElmtId(p12);
        this.__operationType.purgeDependencyOnElmtId(p12);
        this.__fontSize.purgeDependencyOnElmtId(p12);
        this.__ageing.purgeDependencyOnElmtId(p12);
        this.__textArrowBgColor.purgeDependencyOnElmtId(p12);
        this.__buttonBgColor.purgeDependencyOnElmtId(p12);
        this.__buttonStyleWidth.purgeDependencyOnElmtId(p12);
        this.__buttonStyleHeight.purgeDependencyOnElmtId(p12);
        this.__textArrowStyleWidth.purgeDependencyOnElmtId(p12);
        this.__textArrowStyleHeight.purgeDependencyOnElmtId(p12);
        this.__iconWidth.purgeDependencyOnElmtId(p12);
        this.__selectedIndex.purgeDependencyOnElmtId(p12);
        this.__selectValue.purgeDependencyOnElmtId(p12);
        this.__flexAlign.purgeDependencyOnElmtId(p12);
        this.__contentMargin.purgeDependencyOnElmtId(p12);
        this.__contentPadding.purgeDependencyOnElmtId(p12);
        this.__subHeaderMargin.purgeDependencyOnElmtId(p12);
        this.__subHeaderTheme.purgeDependencyOnElmtId(p12);
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
        this.__buttonStyleWidth.aboutToBeDeleted();
        this.__buttonStyleHeight.aboutToBeDeleted();
        this.__textArrowStyleWidth.aboutToBeDeleted();
        this.__textArrowStyleHeight.aboutToBeDeleted();
        this.__iconWidth.aboutToBeDeleted();
        this.__selectedIndex.aboutToBeDeleted();
        this.__selectValue.aboutToBeDeleted();
        this.__flexAlign.aboutToBeDeleted();
        this.__contentMargin.aboutToBeDeleted();
        this.__contentPadding.aboutToBeDeleted();
        this.__subHeaderMargin.aboutToBeDeleted();
        this.__subHeaderTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(o12) {
        this.__icon.set(o12);
    }
    get primaryTitle() {
        return this.__primaryTitle.get();
    }
    set primaryTitle(n12) {
        this.__primaryTitle.set(n12);
    }
    get primaryTitleModifier() {
        return this.__primaryTitleModifier.get();
    }
    set primaryTitleModifier(m12) {
        this.__primaryTitleModifier.set(m12);
    }
    get secondaryTitle() {
        return this.__secondaryTitle.get();
    }
    set secondaryTitle(l12) {
        this.__secondaryTitle.set(l12);
    }
    get secondaryTitleModifier() {
        return this.__secondaryTitleModifier.get();
    }
    set secondaryTitleModifier(k12) {
        this.__secondaryTitleModifier.set(k12);
    }
    get subHeaderModifier() {
        return this.__subHeaderModifier.get();
    }
    set subHeaderModifier(j12) {
        this.__subHeaderModifier.set(j12);
    }
    get operationType() {
        return this.__operationType.get();
    }
    set operationType(i12) {
        this.__operationType.set(i12);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(h12) {
        this.__fontSize.set(h12);
    }
    get ageing() {
        return this.__ageing.get();
    }
    set ageing(g12) {
        this.__ageing.set(g12);
    }
    get textArrowBgColor() {
        return this.__textArrowBgColor.get();
    }
    set textArrowBgColor(f12) {
        this.__textArrowBgColor.set(f12);
    }
    get buttonBgColor() {
        return this.__buttonBgColor.get();
    }
    set buttonBgColor(e12) {
        this.__buttonBgColor.set(e12);
    }
    get buttonStyleWidth() {
        return this.__buttonStyleWidth.get();
    }
    set buttonStyleWidth(d12) {
        this.__buttonStyleWidth.set(d12);
    }
    get buttonStyleHeight() {
        return this.__buttonStyleHeight.get();
    }
    set buttonStyleHeight(c12) {
        this.__buttonStyleHeight.set(c12);
    }
    get textArrowStyleWidth() {
        return this.__textArrowStyleWidth.get();
    }
    set textArrowStyleWidth(b12) {
        this.__textArrowStyleWidth.set(b12);
    }
    get textArrowStyleHeight() {
        return this.__textArrowStyleHeight.get();
    }
    set textArrowStyleHeight(a12) {
        this.__textArrowStyleHeight.set(a12);
    }
    get iconWidth() {
        return this.__iconWidth.get();
    }
    set iconWidth(z11) {
        this.__iconWidth.set(z11);
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(y11) {
        this.__selectedIndex.set(y11);
    }
    get selectValue() {
        return this.__selectValue.get();
    }
    set selectValue(x11) {
        this.__selectValue.set(x11);
    }
    get flexAlign() {
        return this.__flexAlign.get();
    }
    set flexAlign(w11) {
        this.__flexAlign.set(w11);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(v11) {
        this.__contentMargin.set(v11);
    }
    get contentPadding() {
        return this.__contentPadding.get();
    }
    set contentPadding(u11) {
        this.__contentPadding.set(u11);
    }
    get subHeaderMargin() {
        return this.__subHeaderMargin.get();
    }
    set subHeaderMargin(t11) {
        this.__subHeaderMargin.set(t11);
    }
    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }
    set subHeaderTheme(s11) {
        this.__subHeaderTheme.set(s11);
    }
    onWillApplyTheme(p11) {
        this.subHeaderTheme.fontPrimaryColor = p11.colors.fontPrimary;
        this.subHeaderTheme.fontSecondaryColor = p11.colors.fontSecondary;
        this.subHeaderTheme.fontButtonColor = p11.colors.fontEmphasize;
        this.subHeaderTheme.iconArrowColor = p11.colors.iconTertiary;
        this.subHeaderTheme.textArrowHoverBgColor = p11.colors.interactiveHover;
        this.subHeaderTheme.borderFocusColor = p11.colors.interactiveFocus;
        this.subHeaderTheme.leftIconColor = p11.colors.iconSecondary;
        this.subHeaderTheme.rightIconColor = p11.colors.iconPrimary;
    }
    updateFontScale() {
        try {
            let n11 = this.getUIContext();
            let o11 = n11.getHostContext()?.config.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(o11, this.appMaxFontScale);
        }
        catch (k11) {
            let l11 = k11.code;
            let m11 = k11.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${l11}, message: ${m11}`);
            return 1;
        }
    }
    async aboutToAppear() {
        let j11 = this.getUIContext();
        this.isFollowingSystemFontScale = j11.isFollowingSystemFontScale();
        this.appMaxFontScale = j11.getMaxFontScale();
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
            this.selectedIndex = this.select.selected;
            this.selectValue = this.select.value;
        }
    }
    isSuitableAging() {
        return (this.fontSize >= MIN_FONT_SIZE) && ((this.operationType === OperationType.TEXT_ARROW) ||
            this.operationType === OperationType.BUTTON) && this.operationItem &&
            (this.operationItem?.length > 0) && this.operationItem[0].value !== '';
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((h10, i10) => {
            If.create();
            if (this.isSuitableAging()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h11, i11) => {
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.padding(this.getAreaPadding());
                    }, Column);
                    this.observeComponentCreation2((f11, g11) => {
                        Row.create();
                        Row.margin({
                            top: LengthMetrics.resource({ 'id': -1, 'type': 10002,
                                params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__' }),
                            bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002,
                                params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__' }),
                        });
                        Row.padding({
                            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_left'],
                                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_right'],
                                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                        });
                        Row.width('100%');
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((a11, b11) => {
                        Row.create();
                        Row.margin({
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.padding({
                            start: LengthMetrics.vp(Util.getNumberByResource(125830936,
                                LEFT_ICON_SIZE_NUMBER) - this.paddingLeft),
                            end: LengthMetrics.vp(Util.getNumberByResource(125830937, LEFT_ICON_SIZE_NUMBER)),
                        });
                        Row.justifyContent(FlexAlign.Start);
                        Row.width('100%');
                        Row.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Row.onTouch((e11) => {
                            if (e11.type === TouchType.Down) {
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
                            if (e11.type === TouchType.Up || e11.type === TouchType.Cancel) {
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
                    }, Row);
                    this.rightArea.bind(this)();
                    Row.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((u10, v10) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.contentMargin ?? this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((s10, t10) => {
                        Row.create();
                        Row.margin({
                            top: this.fontSize >= MIN_FONT_SIZE ? {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level8'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__' } : ''
                        });
                        Row.width('100%');
                        Row.flexShrink(1);
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((n10, o10) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.End);
                        Row.alignItems(VerticalAlign.Bottom);
                        Row.constraintSize({
                            maxWidth: this.getRightAreaMaxWidth(),
                            minWidth: this.getRightAreaMinWidth(),
                            minHeight: MIN_HOT_AREA_LENGTH,
                        });
                        Row.flexShrink(0);
                        Row.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Row.onTouch((r10) => {
                            if (r10.type === TouchType.Down) {
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
                            if (r10.type === TouchType.Up || r10.type === TouchType.Cancel) {
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
                    }, Row);
                    this.rightArea.bind(this)();
                    Row.pop();
                    Flex.pop();
                });
            }
        }, If);
        If.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    onMeasureSize(z9, a10, b10) {
        let c10 = { width: z9.width, height: z9.height };
        let d10 = this.getUIContext().getHostContext();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        a10.forEach((f10) => {
            b10.minHeight = Math.min(Number(this.getMinHeight()), Number(b10.maxHeight));
            c10.height = f10.measure(b10).height;
            c10.width = Number(b10.maxWidth);
        });
        return c10;
    }
    onPlaceChildren(u9, v9, w9) {
        v9.forEach((y9) => {
            y9.layout({ x: 0, y: 0 });
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
        }
        else if (this.secondaryTitle && this.primaryTitle) {
            return DOUBLE_LINE_HEIGHT;
        }
        return SINGLE_LINE_HEIGHT;
    }
    getTextArrowPaddingLeft() {
        if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
            return LengthMetrics.resource({
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level1'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
        }
        return LengthMetrics.resource({
            'id': -1,
            'type': 10002,
            params: ['sys.float.padding_level0'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        });
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
        let t9 = {};
        if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
            (!this.primaryTitle && this.secondaryTitle))) {
            t9 = {
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            };
        }
        return t9;
    }
    leftArea(i9 = null) {
        this.observeComponentCreation2((k9, l9) => {
            If.create();
            if (this.titleBuilder) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.titleBuilder.bind(this)();
                });
            }
            else if (this.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondaryTitleStyle',
                        { content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] :
                        this['secondaryTitle']), iconOptions: () => ({
                            icon: this.icon,
                            symbolicIconOption: this.iconSymbolOptions,
                        }) }));
                });
            }
            else if (this.secondaryTitle && this.primaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle',
                        { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']),
                            subContent: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] :
                            this['secondaryTitle']) }));
                });
            }
            else if (this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle',
                        { content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] :
                        this['secondaryTitle']) }));
                });
            }
            else if (this.select) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.SelectStyle.bind(this)(this.select);
                });
            }
            else if (this.primaryTitle) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle',
                        { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']) }));
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
    rightArea(n8 = null) {
        this.observeComponentCreation2((e9, f9) => {
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
        this.observeComponentCreation2((a9, b9) => {
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
        this.observeComponentCreation2((w8, x8) => {
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
        this.observeComponentCreation2((s8, t8) => {
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
    IconSecondaryTitleStyle(t7, u7 = null) {
        this.observeComponentCreation2((k8, l8) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: this.fontSize >= MIN_FONT_SIZE ?
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) :
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: this.fontSize >= MIN_FONT_SIZE ?
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) :
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Flex.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Flex);
        this.observeComponentCreation2((a8, b8) => {
            If.create();
            if (Util.isSymbolResource(t7.iconOptions?.icon)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i8, j8) => {
                        SymbolGlyph.create(t7.iconOptions?.icon);
                        SymbolGlyph.fontSize(t7.iconOptions?.symbolicIconOption?.fontSize ?
                        Util.symbolFontSize(t7.iconOptions?.symbolicIconOption?.fontSize) : LEFT_ICON_SIZE);
                        SymbolGlyph.fontColor(t7.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.leftIconColor]);
                        SymbolGlyph.fontWeight(t7.iconOptions?.symbolicIconOption?.fontWeight);
                        SymbolGlyph.renderingStrategy(t7.iconOptions?.symbolicIconOption?.renderingStrategy);
                        SymbolGlyph.effectStrategy(t7.iconOptions?.symbolicIconOption?.effectStrategy);
                        SymbolGlyph.margin({ end: LengthMetrics.resource({ 'id': -1, 'type': 10002,
                            params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__' }) });
                        SymbolGlyph.flexShrink(0);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((e8, f8) => {
                        Image.create(t7.iconOptions?.icon);
                        Image.fillColor(this.subHeaderTheme.leftIconColor);
                        Image.width(LEFT_ICON_SIZE);
                        Image.height(LEFT_ICON_SIZE);
                        Image.margin({ end: LengthMetrics.resource({ 'id': -1, 'type': 10002,
                            params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__' }) });
                        Image.draggable(false);
                        Image.flexShrink(0);
                    }, Image);
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((y7, z7) => {
            Text.create(t7.content);
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
    SubTitleStyle(h7, i7 = null) {
        this.observeComponentCreation2((q7, r7) => {
            Column.create();
            Column.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: this.fontSize >= MIN_FONT_SIZE ?
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) :
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: this.fontSize >= MIN_FONT_SIZE ?
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) :
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Column.alignItems(HorizontalAlign.Start);
            Column.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Column);
        this.observeComponentCreation2((o7, p7) => {
            Text.create(h7.content);
            __Text__primaryTitleStyles({
                fontWeight: FontWeight.Bold,
                maxLines: SINGLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
            Text.accessibilityLevel('yes');
            Text.width('100%');
        }, Text);
        Text.pop();
        this.observeComponentCreation2((m7, n7) => {
            Text.create(h7.subContent);
            __Text__secondaryTitleStyles({
                maxLines: SINGLE_LINE_NUM,
                fontWeight: FontWeight.Regular,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.width('100%');
            Text.margin({
                top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
            Text.accessibilityLevel('yes');
        }, Text);
        Text.pop();
        Column.pop();
    }
    SecondTitleStyle(y6, z6 = null) {
        this.observeComponentCreation2((f7, g7) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: this.fontSize >= MIN_FONT_SIZE ?
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) :
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: this.fontSize >= MIN_FONT_SIZE ?
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) :
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Column);
        this.observeComponentCreation2((c7, d7) => {
            Text.create(y6.content);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.width('100%');
            Text.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
            Text.accessibilityLevel('yes');
        }, Text);
        Text.pop();
        Column.pop();
    }
    SelectStyle(m6, n6 = null) {
        this.observeComponentCreation2((v6, w6) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Column);
        this.observeComponentCreation2((q6, r6) => {
            Select.create(m6.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
            Select.value(ObservedObject.GetRawObject(this.selectValue));
            Select.onSelect((t6, u6) => {
                this.selectedIndex = t6;
                if (u6) {
                    this.selectValue = u6;
                }
                if (m6.onSelect) {
                    m6.onSelect(t6, u6);
                }
            });
            Select.font({
                size: { 'id': -1, 'type': 10002, params: ['sys.float.Body_L'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
        Column.pop();
    }
    PrimaryTitleStyle(d6, e6 = null) {
        this.observeComponentCreation2((k6, l6) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: this.fontSize >= MIN_FONT_SIZE ?
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) :
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: this.fontSize >= MIN_FONT_SIZE ?
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) :
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Column);
        this.observeComponentCreation2((h6, i6) => {
            Text.create(d6.content);
            __Text__primaryTitleStyles({
                fontWeight: FontWeight.Bold,
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.width('100%');
            Text.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
            Text.accessibilityLevel('yes');
        }, Text);
        Text.pop();
        Column.pop();
    }
    ButtonStyle(c5, d5 = null) {
        this.observeComponentCreation2((b6, c6) => {
            Row.create();
            Row.margin({
                start: LengthMetrics.resource(this.ageing ?
                    { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
                    { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: LengthMetrics.resource(this.ageing ?
                    { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
                    { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'],
                        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((z5, a6) => {
            Stack.create();
            Stack.focusable(true);
        }, Stack);
        this.observeComponentCreation2((h5, i5) => {
            If.create();
            if (c5) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s5, t5) => {
                        Row.create();
                        Row.padding({
                            start: LengthMetrics.resource({
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level1'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            }),
                            end: LengthMetrics.resource({
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level1'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            }),
                            top: LengthMetrics.resource({
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level2'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            }),
                            bottom: LengthMetrics.resource({
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level2'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            }),
                        });
                        Row.margin({
                            start: this.leftIconMargin(),
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'],
                                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
                        Row.focusable(true);
                        Row.constraintSize({ minHeight: OPERATE_ITEM_LENGTH });
                        Row.justifyContent(FlexAlign.End);
                        Row.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'],
                            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Row.onHover((y5) => {
                            if (y5) {
                                this.buttonBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                            }
                            else {
                                this.buttonBgColor = { 'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                        });
                        Row.onSizeChange((w5, x5) => {
                            this.buttonStyleWidth = Number(x5.width);
                            this.buttonStyleHeight = Number(x5.height);
                        });
                    }, Row);
                    this.observeComponentCreation2((q5, r5) => {
                        Text.create(c5.value);
                        __Text__secondaryTitleStyles({
                            fontWeight: FontWeight.Medium,
                            maxLines: DOUBLE_LINE_NUM,
                            fontColor: this.subHeaderTheme.fontButtonColor,
                        });
                    }, Text);
                    Text.pop();
                    Row.pop();
                    this.observeComponentCreation2((o5, p5) => {
                        Text.create();
                        Text.focusable(true);
                        Text.width(this.buttonStyleWidth);
                        Text.height(this.buttonStyleHeight);
                        Text.hitTestBehavior(HitTestMode.None);
                        ViewStackProcessor.visualState('focused');
                        Text.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'],
                                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: { 'id': -1, 'type': 10002, params: ['sys.float.outline_extra_larger'],
                                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            color: this.subHeaderTheme.borderFocusColor,
                        });
                        ViewStackProcessor.visualState('pressed');
                        Text.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        ViewStackProcessor.visualState('disabled');
                        Text.opacity({ 'id': -1, 'type': 10002, params: ['sys.float.interactive_disable'],
                            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        ViewStackProcessor.visualState('normal');
                        Text.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'],
                                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: { 'id': -1, 'type': 10002, params: ['sys.float.border_none'],
                                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            color: {
                                'id': -1,
                                'type': 10001,
                                params: ['sys.color.ohos_id_color_focused_outline_transparent'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
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
        if (this.icon && Util.isSymbolResource(this.icon)) {
            return this.ageing ? LengthMetrics.vp((this.iconSymbolOptions?.fontSize ?
            Util.numberToSize(this.iconSymbolOptions?.fontSize) : LEFT_ICON_SIZE_NUMBER) +
                LEFT_TEXT_NUMBER) : LengthMetrics.vp(0);
        }
        else {
            return (this.ageing && this.icon) ? LengthMetrics.vp(LEFT_ICON_SIZE_NUMBER +
                LEFT_TEXT_NUMBER) : LengthMetrics.vp(0);
        }
    }
    TextArrowStyle(y3, z3 = null) {
        this.observeComponentCreation2((a5, b5) => {
            Row.create();
            Row.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.subHeaderModifier));
            Row.focusable(true);
            Row.justifyContent(this.ageing ? FlexAlign.SpaceBetween : FlexAlign.End);
            Row.margin({
                start: LengthMetrics.resource(this.ageing ?
                    { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
                    { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: LengthMetrics.resource(this.ageing ?
                    { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'],
                        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
                    { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'],
                        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Row);
        this.observeComponentCreation2((w4, x4) => {
            Stack.create();
            Stack.margin({
                start: this.leftIconMargin(),
            });
            Stack.onHover((z4) => {
                if (z4) {
                    this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                }
                else {
                    this.textArrowBgColor = {
                        'id': -1,
                        'type': 10001,
                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    };
                }
            });
        }, Stack);
        this.observeComponentCreation2((r4, s4) => {
            Row.create();
            Row.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.subHeaderModifier));
            Row.alignItems(VerticalAlign.Center);
            Row.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Row.focusable(true);
            Row.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
            Row.constraintSize({ minHeight: OPERATE_ITEM_LENGTH });
            Row.padding({
                start: this.getTextArrowPaddingLeft(),
                top: this.ageing ? LengthMetrics.vp(0) :
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: this.ageing ? LengthMetrics.vp(0) :
                LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Row.onSizeChange((u4, v4) => {
                this.textArrowStyleWidth = Number(v4.width);
                this.textArrowStyleHeight = Number(v4.height);
            });
        }, Row);
        this.observeComponentCreation2((k4, l4) => {
            If.create();
            if (y3) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p4, q4) => {
                        Text.create(y3.value);
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
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
        this.observeComponentCreation2((i4, j4) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.height(this.textArrowStyleHeight);
            Row.width(this.textArrowStyleWidth);
            Row.hitTestBehavior(HitTestMode.None);
            ViewStackProcessor.visualState('focused');
            Row.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.outline_extra_larger'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: this.subHeaderTheme.borderFocusColor,
            });
            ViewStackProcessor.visualState('pressed');
            Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            ViewStackProcessor.visualState('disabled');
            Row.opacity({ 'id': -1, 'type': 10002, params: ['sys.float.interactive_disable'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            ViewStackProcessor.visualState('normal');
            Row.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.border_none'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline_transparent'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            ViewStackProcessor.visualState();
        }, Row);
        this.observeComponentCreation2((g4, h4) => {
            Image.create({ 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_arrow_right'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.fillColor(this.subHeaderTheme.iconArrowColor);
            Image.width(ARROW_ICON_WIDTH);
            Image.height(OPERATE_ITEM_LENGTH);
            Image.focusable(true);
            Image.draggable(false);
            Image.matchTextDirection(true);
        }, Image);
        Row.pop();
        Stack.pop();
        Row.pop();
    }
    IconGroupStyle(r2, s2 = null) {
        this.observeComponentCreation2((w3, x3) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((v2, w2) => {
            ForEach.create();
            const x2 = (z2, a3) => {
                const b3 = z2;
                this.observeComponentCreation2((d3, e3) => {
                    If.create();
                    if (Util.isResourceType(b3.value)) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((i3, j3) => {
                                If.create();
                                if (a3 <= INDEX_TWO) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((u3, v3) => {
                                            __Common__.create();
                                            __Common__.margin({
                                                start: LengthMetrics.resource({
                                                    'id': -1,
                                                    'type': 10002,
                                                    params: ['sys.float.padding_level4'],
                                                    'bundleName': '__harDefaultBundleName__',
                                                    'moduleName': '__harDefaultModuleName__'
                                                }),
                                                bottom: LengthMetrics.resource({
                                                    'id': -1,
                                                    'type': 10002,
                                                    params: ['sys.float.padding_level3'],
                                                    'bundleName': '__harDefaultBundleName__',
                                                    'moduleName': '__harDefaultModuleName__'
                                                }),
                                            });
                                        }, __Common__);
                                        {
                                            this.observeComponentCreation2((o3, p3) => {
                                                if (p3) {
                                                    let q3 = new SingleIconStyle(this, {
                                                        item: {
                                                            iconOptions: {
                                                                icon: b3.value,
                                                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > a3 ?
                                                                this.operationSymbolOptions[a3] : null,
                                                            },
                                                            action: b3.action,
                                                        },
                                                        isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER,
                                                    }, undefined, o3, () => { }, {
                                                        page: 'library/src/main/ets/components/mainpage/MainPage.ets',
                                                        line: 792, col: 13 });
                                                    ViewPU.create(q3);
                                                    let r3 = () => {
                                                        return {
                                                            item: {
                                                                iconOptions: {
                                                                    icon: b3.value,
                                                                    symbolicIconOption: this.operationSymbolOptions &&
                                                                        this.operationSymbolOptions.length > a3 ?
                                                                    this.operationSymbolOptions[a3] : null,
                                                                },
                                                                action: b3.action,
                                                            },
                                                            isSingleIcon: this.operationItem?.length ===
                                                                SINGLE_ICON_NUMBER
                                                        };
                                                    };
                                                    q3.paramsGenerator_ = r3;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(o3, {});
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
            this.forEachUpdateFunction(v2, r2, x2, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    LoadingProcessStyle(k2 = null) {
        this.observeComponentCreation2((p2, q2) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.padding({
                top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            Row.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Row);
        this.observeComponentCreation2((n2, o2) => {
            LoadingProgress.create();
            LoadingProgress.width(OPERATE_ITEM_LENGTH);
            LoadingProgress.height(OPERATE_ITEM_LENGTH);
            LoadingProgress.color({ 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }, LoadingProgress);
        Row.pop();
    }
    dummyFunction(f2 = null) {
        this.observeComponentCreation2((h2, i2) => {
            Row.create();
            Row.onAppear(() => {
                this.changeFlexAlign(FlexAlign.End);
            });
        }, Row);
        Row.pop();
    }
    changeFlexAlign(e2) {
        if (this.flexAlign === e2) {
            return;
        }
        this.flexAlign = e2;
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}
class SingleIconStyle extends ViewPU {
    constructor(y1, z1, a2, b2 = -1, c2 = undefined, d2) {
        super(y1, a2, b2, d2);
        if (typeof c2 === 'function') {
            this.paramsGenerator_ = c2;
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
        this.setInitiallyProvidedValue(z1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(x1) {
        if (x1.bgColor !== undefined) {
            this.bgColor = x1.bgColor;
        }
        if (x1.isFocus !== undefined) {
            this.isFocus = x1.isFocus;
        }
        if (x1.item !== undefined) {
            this.item = x1.item;
        }
        if (x1.isSingleIcon !== undefined) {
            this.isSingleIcon = x1.isSingleIcon;
        }
    }
    updateStateVars(w1) {
    }
    purgeVariableDependenciesOnElmtId(v1) {
        this.__bgColor.purgeDependencyOnElmtId(v1);
        this.__isFocus.purgeDependencyOnElmtId(v1);
        this.__subHeaderTheme.purgeDependencyOnElmtId(v1);
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
    set bgColor(u1) {
        this.__bgColor.set(u1);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(t1) {
        this.__isFocus.set(t1);
    }
    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }
    set subHeaderTheme(s1) {
        this.__subHeaderTheme.set(s1);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((f1, g1) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k1, l1) => {
                        Row.create();
                        Row.focusable(true);
                        Row.width(SINGLE_ICON_ZONE_SIZE);
                        Row.height(SINGLE_ICON_ZONE_SIZE);
                        Row.justifyContent(FlexAlign.Center);
                        Row.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
                        ViewStackProcessor.visualState('normal');
                        Row.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'],
                                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: { 'id': -1, 'type': 10002, params: ['sys.float.border_none'],
                                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            color: {
                                'id': -1,
                                'type': 10001,
                                params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                        });
                        ViewStackProcessor.visualState('focused');
                        Row.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'],
                                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: { 'id': -1, 'type': 10002, params: ['sys.float.outline_extra_larger'],
                                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            color: this.subHeaderTheme.borderFocusColor,
                            style: BorderStyle.Solid,
                        });
                        ViewStackProcessor.visualState('pressed');
                        Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        ViewStackProcessor.visualState('disabled');
                        Row.opacity({ 'id': -1, 'type': 10002, params: ['sys.float.interactive_disable'],
                            'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        ViewStackProcessor.visualState();
                        Row.onTouch((r1) => {
                            if (r1.type === TouchType.Down || TouchType.Cancel) {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.interactive_pressed'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                            if (r1.type === TouchType.Up) {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                        });
                        Row.onHover((q1) => {
                            if (q1) {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.interactive_hover'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                            else {
                                this.bgColor = {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                };
                            }
                        });
                        Row.responseRegion(this.iconResponseRegion());
                        Row.onClick((p1) => {
                            if (this.item?.action) {
                                this.item?.action();
                            }
                        });
                    }, Row);
                    this.IconZone.bind(this)();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    iconResponseRegion() {
        if (this.isSingleIcon) {
            return { x: SINGLE_ICON_REGION_X, y: ICON_REGION_Y, width: MIN_HOT_AREA_LENGTH, height: MIN_HOT_AREA_LENGTH };
        }
        return { x: ICON_REGION_X, y: ICON_REGION_Y, width: MULTI_ICON_REGION_WIDTH, height: MIN_HOT_AREA_LENGTH };
    }
    fontSizeValue(d1) {
        return d1.iconOptions?.symbolicIconOption?.fontSize ?
        Util.symbolFontSize(d1.iconOptions?.symbolicIconOption?.fontSize) : RIGHT_SINGLE_ICON_SIZE;
    }
    IconZone(m = null) {
        this.observeComponentCreation2((o, p) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t, u) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((b1, c1) => {
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
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((x, y) => {
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
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}
class Util {
    static isSymbolResource(k) {
        if (!Util.isResourceType(k)) {
            return false;
        }
        let l = k;
        return l.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(j) {
        if (!j) {
            return false;
        }
        if (typeof j === 'string' || typeof j === 'undefined') {
            return false;
        }
        return true;
    }
    static getNumberByResource(d, e) {
        try {
            let i = resourceManager.getSystemResourceManager().getNumber(d);
            if (i === 0) {
                return e;
            } else {
                return i;
            }
        } catch (f) {
            let g = f.code;
            let h = f.message;
            hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${g}, message: ${h}`);
            return 0;
        }
    }
    static numberToSize(b) {
        if (typeof b === 'string') {
            const c = parseInt(b);
            return c;
        } else if (typeof b === 'number') {
            return b;
        } else {
            return getContext().resourceManager.getNumber(b);
        }
    }
    static symbolFontSize(a) {
        return Util.numberToSize(a) + 'vp';
    }
}

export default { OperationType, SubHeader };