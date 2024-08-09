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
(function (OperationType) {
    OperationType[OperationType['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
    OperationType[OperationType['BUTTON'] = 1] = 'BUTTON';
    OperationType[OperationType['ICON_GROUP'] = 2] = 'ICON_GROUP';
    OperationType[OperationType['LOADING'] = 3] = 'LOADING';
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
function __Text__secondaryTitleStyles(fontStyle) {
    Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Subtitle_S'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontColor(fontStyle?.fontColor ?? { 'id': -1, 'type': 10001, params: ['sys.color.font_secondary'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontWeight(fontStyle?.fontWeight);
    Text.maxLines(fontStyle?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(fontStyle?.alignment);
}
function __Text__primaryTitleStyles(fontStyle) {
    Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Subtitle_L'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontColor(fontStyle?.fontColor ?? { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
export class SubHeader extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__icon = new SynchedPropertyObjectOneWayPU(params.icon, this, 'icon');
        this.iconSymbolOptions = null;
        this.__primaryTitle = new SynchedPropertyObjectOneWayPU(params.primaryTitle, this, 'primaryTitle');
        this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'primaryTitleModifier');
        this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(params.secondaryTitle, this, 'secondaryTitle');
        this.__secondaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'secondaryTitleModifier');
        this.__subHeaderModifier = new ObservedPropertyObjectPU(new SubHeaderModifier(), this, 'subHeaderModifier');
        this.select = null;
        this.__operationType = new SynchedPropertySimpleOneWayPU(params.operationType, this, 'operationType');
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
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(params.contentMargin, this, 'contentMargin');
        this.__contentPadding = new SynchedPropertyObjectOneWayPU(params.contentPadding, this, 'contentPadding');
        this.__subHeaderMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_left'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_right'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
        }, this, 'subHeaderMargin');
        this.__subHeaderTheme = new ObservedPropertyObjectPU(new SubHeaderTheme(), this, 'subHeaderTheme');
        this.addProvidedVar('subHeaderTheme', this.__subHeaderTheme, false);
        this.__isFollowingSystemFontScale = new ObservedPropertySimplePU(false, this, 'isFollowingSystemFontScale');
        this.__appMaxFontScale = new ObservedPropertySimplePU(3.2, this, 'appMaxFontScale');
        this.constraintWidth = 0;
        this.paddingLeft = 2;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.icon === undefined) {
            this.__icon.set(null);
        }
        if (params.iconSymbolOptions !== undefined) {
            this.iconSymbolOptions = params.iconSymbolOptions;
        }
        if (params.primaryTitle === undefined) {
            this.__primaryTitle.set(null);
        }
        if (params.primaryTitleModifier !== undefined) {
            this.primaryTitleModifier = params.primaryTitleModifier;
        }
        if (params.secondaryTitle === undefined) {
            this.__secondaryTitle.set(null);
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
            this.__operationType.set(OperationType.BUTTON);
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
        this.__icon.reset(params.icon);
        this.__primaryTitle.reset(params.primaryTitle);
        this.__secondaryTitle.reset(params.secondaryTitle);
        this.__operationType.reset(params.operationType);
        this.__contentMargin.reset(params.contentMargin);
        this.__contentPadding.reset(params.contentPadding);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__icon.purgeDependencyOnElmtId(rmElmtId);
        this.__primaryTitle.purgeDependencyOnElmtId(rmElmtId);
        this.__primaryTitleModifier.purgeDependencyOnElmtId(rmElmtId);
        this.__secondaryTitle.purgeDependencyOnElmtId(rmElmtId);
        this.__secondaryTitleModifier.purgeDependencyOnElmtId(rmElmtId);
        this.__subHeaderModifier.purgeDependencyOnElmtId(rmElmtId);
        this.__operationType.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSize.purgeDependencyOnElmtId(rmElmtId);
        this.__ageing.purgeDependencyOnElmtId(rmElmtId);
        this.__textArrowBgColor.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonBgColor.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonStyleWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonStyleHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__textArrowStyleWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__textArrowStyleHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__iconWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__selectValue.purgeDependencyOnElmtId(rmElmtId);
        this.__flexAlign.purgeDependencyOnElmtId(rmElmtId);
        this.__contentMargin.purgeDependencyOnElmtId(rmElmtId);
        this.__contentPadding.purgeDependencyOnElmtId(rmElmtId);
        this.__subHeaderMargin.purgeDependencyOnElmtId(rmElmtId);
        this.__subHeaderTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__isFollowingSystemFontScale.purgeDependencyOnElmtId(rmElmtId);
        this.__appMaxFontScale.purgeDependencyOnElmtId(rmElmtId);
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
        this.__isFollowingSystemFontScale.aboutToBeDeleted();
        this.__appMaxFontScale.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(newValue) {
        this.__icon.set(newValue);
    }
    get primaryTitle() {
        return this.__primaryTitle.get();
    }
    set primaryTitle(newValue) {
        this.__primaryTitle.set(newValue);
    }
    get primaryTitleModifier() {
        return this.__primaryTitleModifier.get();
    }
    set primaryTitleModifier(newValue) {
        this.__primaryTitleModifier.set(newValue);
    }
    get secondaryTitle() {
        return this.__secondaryTitle.get();
    }
    set secondaryTitle(newValue) {
        this.__secondaryTitle.set(newValue);
    }
    get secondaryTitleModifier() {
        return this.__secondaryTitleModifier.get();
    }
    set secondaryTitleModifier(newValue) {
        this.__secondaryTitleModifier.set(newValue);
    }
    get subHeaderModifier() {
        return this.__subHeaderModifier.get();
    }
    set subHeaderModifier(newValue) {
        this.__subHeaderModifier.set(newValue);
    }
    get operationType() {
        return this.__operationType.get();
    }
    set operationType(newValue) {
        this.__operationType.set(newValue);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(newValue) {
        this.__fontSize.set(newValue);
    }
    get ageing() {
        return this.__ageing.get();
    }
    set ageing(newValue) {
        this.__ageing.set(newValue);
    }
    get textArrowBgColor() {
        return this.__textArrowBgColor.get();
    }
    set textArrowBgColor(newValue) {
        this.__textArrowBgColor.set(newValue);
    }
    get buttonBgColor() {
        return this.__buttonBgColor.get();
    }
    set buttonBgColor(newValue) {
        this.__buttonBgColor.set(newValue);
    }
    get buttonStyleWidth() {
        return this.__buttonStyleWidth.get();
    }
    set buttonStyleWidth(newValue) {
        this.__buttonStyleWidth.set(newValue);
    }
    get buttonStyleHeight() {
        return this.__buttonStyleHeight.get();
    }
    set buttonStyleHeight(newValue) {
        this.__buttonStyleHeight.set(newValue);
    }
    get textArrowStyleWidth() {
        return this.__textArrowStyleWidth.get();
    }
    set textArrowStyleWidth(newValue) {
        this.__textArrowStyleWidth.set(newValue);
    }
    get textArrowStyleHeight() {
        return this.__textArrowStyleHeight.get();
    }
    set textArrowStyleHeight(newValue) {
        this.__textArrowStyleHeight.set(newValue);
    }
    get iconWidth() {
        return this.__iconWidth.get();
    }
    set iconWidth(newValue) {
        this.__iconWidth.set(newValue);
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(newValue) {
        this.__selectedIndex.set(newValue);
    }
    get selectValue() {
        return this.__selectValue.get();
    }
    set selectValue(newValue) {
        this.__selectValue.set(newValue);
    }
    get flexAlign() {
        return this.__flexAlign.get();
    }
    set flexAlign(newValue) {
        this.__flexAlign.set(newValue);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(newValue) {
        this.__contentMargin.set(newValue);
    }
    get contentPadding() {
        return this.__contentPadding.get();
    }
    set contentPadding(newValue) {
        this.__contentPadding.set(newValue);
    }
    get subHeaderMargin() {
        return this.__subHeaderMargin.get();
    }
    set subHeaderMargin(newValue) {
        this.__subHeaderMargin.set(newValue);
    }
    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }
    set subHeaderTheme(newValue) {
        this.__subHeaderTheme.set(newValue);
    }
    get isFollowingSystemFontScale() {
        return this.__isFollowingSystemFontScale.get();
    }
    set isFollowingSystemFontScale(newValue) {
        this.__isFollowingSystemFontScale.set(newValue);
    }
    get appMaxFontScale() {
        return this.__appMaxFontScale.get();
    }
    set appMaxFontScale(newValue) {
        this.__appMaxFontScale.set(newValue);
    }
    onWillApplyTheme(theme) {
        this.subHeaderTheme.fontPrimaryColor = theme.colors.fontPrimary;
        this.subHeaderTheme.fontSecondaryColor = theme.colors.fontSecondary;
        this.subHeaderTheme.fontButtonColor = theme.colors.fontEmphasize;
        this.subHeaderTheme.iconArrowColor = theme.colors.iconTertiary;
        this.subHeaderTheme.textArrowHoverBgColor = theme.colors.interactiveHover;
        this.subHeaderTheme.borderFocusColor = theme.colors.interactiveFocus;
        this.subHeaderTheme.leftIconColor = theme.colors.iconSecondary;
        this.subHeaderTheme.rightIconColor = theme.colors.iconPrimary;
    }
    updateFontScale() {
        try {
            let uiContext = this.getUIContext();
            let systemFontScale = uiContext.getHostContext()?.config.fontSizeScale ?? 1;
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                    }, Row);
                    this.rightArea.bind(this)();
                    Row.pop();
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    onPlaceChildren(selfLayoutInfo, children, constraint) {
        children.forEach((child) => {
            child.layout({ x: 0, y: 0 });
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
        let padding = {};
        if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
            (!this.primaryTitle && this.secondaryTitle))) {
            padding = {
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'],
                    'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (Util.isSymbolResource($$.iconOptions?.icon)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create($$.iconOptions?.icon);
                        SymbolGlyph.fontSize($$.iconOptions?.symbolicIconOption?.fontSize ?
                        Util.symbolFontSize($$.iconOptions?.symbolicIconOption?.fontSize) : LEFT_ICON_SIZE);
                        SymbolGlyph.fontColor($$.iconOptions?.symbolicIconOption?.fontColor ??
                            [this.subHeaderTheme.leftIconColor]);
                        SymbolGlyph.fontWeight($$.iconOptions?.symbolicIconOption?.fontWeight);
                        SymbolGlyph.renderingStrategy($$.iconOptions?.symbolicIconOption?.renderingStrategy);
                        SymbolGlyph.effectStrategy($$.iconOptions?.symbolicIconOption?.effectStrategy);
                        SymbolGlyph.margin({ end: LengthMetrics.resource({ 'id': -1, 'type': 10002,
                            params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__' }) });
                        SymbolGlyph.flexShrink(0);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create($$.iconOptions?.icon);
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
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
    SubTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
            __Text__primaryTitleStyles({
                fontWeight: FontWeight.Bold,
                maxLines: SINGLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
            Text.width('100%');
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.subContent);
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
        }, Text);
        Text.pop();
        Column.pop();
    }
    SecondTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
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
        }, Text);
        Text.pop();
        Column.pop();
    }
    SelectStyle(selectParam, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Select.create(selectParam.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
            Select.value(ObservedObject.GetRawObject(this.selectValue));
            Select.onSelect((index, value) => {
                this.selectedIndex = index;
                if (value) {
                    this.selectValue = value;
                }
                if (selectParam.onSelect) {
                    selectParam.onSelect(index, value);
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
    PrimaryTitleStyle($$, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create($$.content);
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
        }, Text);
        Text.pop();
        Column.pop();
    }
    ButtonStyle(button, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        Row.onHover((isHover) => {
                            if (isHover) {
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
                        Row.onSizeChange((oldValue, newValue) => {
                            this.buttonStyleWidth = Number(newValue.width);
                            this.buttonStyleHeight = Number(newValue.height);
                        });
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(button.value);
                        __Text__secondaryTitleStyles({
                            fontWeight: FontWeight.Medium,
                            maxLines: DOUBLE_LINE_NUM,
                            fontColor: this.subHeaderTheme.fontButtonColor,
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
    TextArrowStyle(textArrow, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.margin({
                start: this.leftIconMargin(),
            });
            Stack.onHover((isHover) => {
                if (isHover) {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            Row.onSizeChange((oldValue, newValue) => {
                this.textArrowStyleWidth = Number(newValue.width);
                this.textArrowStyleHeight = Number(newValue.height);
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (textArrow) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(textArrow.value);
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                    if (Util.isResourceType(item.value)) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                If.create();
                                if (index <= INDEX_TWO) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                if (isInitialRender) {
                                                    let componentCall = new SingleIconStyle(this, {
                                                        item: {
                                                            iconOptions: {
                                                                icon: item.value,
                                                                symbolicIconOption: this.operationSymbolOptions &&
                                                                    this.operationSymbolOptions.length > index ?
                                                                this.operationSymbolOptions[index] : null,
                                                            },
                                                            action: item.action,
                                                        },
                                                        isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER,
                                                    }, undefined, elmtId, () => { }, {
                                                        page: 'library/src/main/ets/components/mainpage/MainPage.ets',
                                                        line: 785, col: 13 });
                                                    ViewPU.create(componentCall);
                                                    let paramsLambda = () => {
                                                        return {
                                                            item: {
                                                                iconOptions: {
                                                                    icon: item.value,
                                                                    symbolicIconOption: this.operationSymbolOptions &&
                                                                        this.operationSymbolOptions.length > index ?
                                                                    this.operationSymbolOptions[index] : null,
                                                                },
                                                                action: item.action,
                                                            },
                                                            isSingleIcon: this.operationItem?.length ===
                                                                SINGLE_ICON_NUMBER
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            LoadingProgress.create();
            LoadingProgress.width(OPERATE_ITEM_LENGTH);
            LoadingProgress.height(OPERATE_ITEM_LENGTH);
            LoadingProgress.color({ 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
    changeFlexAlign(flex) {
        if (this.flexAlign === flex) {
            return;
        }
        this.flexAlign = flex;
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}
class SingleIconStyle extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
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
        this.__bgColor.purgeDependencyOnElmtId(rmElmtId);
        this.__isFocus.purgeDependencyOnElmtId(rmElmtId);
        this.__subHeaderTheme.purgeDependencyOnElmtId(rmElmtId);
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
    set bgColor(newValue) {
        this.__bgColor.set(newValue);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(newValue) {
        this.__isFocus.set(newValue);
    }
    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }
    set subHeaderTheme(newValue) {
        this.__subHeaderTheme.set(newValue);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        Row.onTouch((event) => {
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
                        Row.onHover((isHover) => {
                            if (isHover) {
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
                        Row.onClick((event) => {
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
    fontSizeValue(item) {
        return item.iconOptions?.symbolicIconOption?.fontSize ?
        Util.symbolFontSize(item.iconOptions?.symbolicIconOption?.fontSize) : RIGHT_SINGLE_ICON_SIZE;
    }
    IconZone(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    static isSymbolResource(resourceStr) {
        if (!Util.isResourceType(resourceStr)) {
            return false;
        }
        let resource = resourceStr;
        return resource.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(resource) {
        if (!resource) {
            return false;
        }
        if (typeof resource === 'string' || typeof resource === 'undefined') {
            return false;
        }
        return true;
    }
    static getNumberByResource(resourceId, defaultNumber) {
        try {
            let resourceNumber = resourceManager.getSystemResourceManager().getNumber(resourceId);
            if (resourceNumber === 0) {
                return defaultNumber;
            } else {
                return resourceNumber;
            }
        } catch (error) {
            let code = error.code;
            let message = error.message;
            hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${code}, message: ${message}`);
            return 0;
        }
    }
    static numberToSize(fontSize) {
        if (typeof fontSize === 'string') {
            const fontSizeNumber = parseInt(fontSize);
            return fontSizeNumber;
        } else if (typeof fontSize === 'number') {
            return fontSize;
        } else {
            return resourceManager.getSystemResourceManager().getNumber(fontSize);
        }
    }
    static symbolFontSize(fontSize) {
        return Util.numberToSize(fontSize) + 'vp';
    }
}

export default { OperationType, SubHeader };