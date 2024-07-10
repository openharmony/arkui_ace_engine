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

var _a;
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
const TextModifier = requireNapi('arkui.modifier').TextModifier;
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
(function (s12) {
    s12[s12['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
    s12[s12['BUTTON'] = 1] = 'BUTTON';
    s12[s12['ICON_GROUP'] = 2] = 'ICON_GROUP';
    s12[s12['LOADING'] = 3] = 'LOADING';
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
        this.fontPrimaryColor = { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.fontSecondaryColor = { 'id': -1, 'type': 10001, params: ['sys.color.font_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.fontButtonColor = { 'id': -1, 'type': 10001, params: ['sys.color.font_emphasize'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.iconArrowColor = { 'id': -1, 'type': 10001, params: ['sys.color.icon_tertiary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.textArrowHoverBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.borderFocusColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_focus'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.leftIconColor = { 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.rightIconColor = { 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
}
function __Text__secondaryTitleStyles(r12) {
    Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Subtitle_S'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontColor(r12?.fontColor ?? { 'id': -1, 'type': 10001, params: ['sys.color.font_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontWeight(r12?.fontWeight);
    Text.maxLines(r12?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(r12?.alignment);
}
function __Text__primaryTitleStyles(q12) {
    Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Subtitle_L'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontColor(q12?.fontColor ?? { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontWeight(q12?.fontWeight);
    Text.maxLines(q12?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(q12?.alignment);
}
class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }
    applyNormalAttribute(p12) {
        if (this.isAgeing) {
            p12.width('100%');
        }
        else {
        }
    }
}
export class SubHeader extends ViewPU {
    constructor(j12, k12, l12, m12 = -1, n12 = undefined, o12) {
        super(j12, l12, m12, o12);
        if (typeof n12 === 'function') {
            this.paramsGenerator_ = n12;
        }
        this.__icon = new SynchedPropertyObjectOneWayPU(k12.icon, this, 'icon');
        this.iconSymbolOptions = null;
        this.__primaryTitle = new SynchedPropertyObjectOneWayPU(k12.primaryTitle, this, 'primaryTitle');
        this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'primaryTitleModifier');
        this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(k12.secondaryTitle, this, 'secondaryTitle');
        this.__secondaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'secondaryTitleModifier');
        this.__subHeaderModifier = new ObservedPropertyObjectPU(new SubHeaderModifier(), this, 'subHeaderModifier');
        this.select = null;
        this.__operationType = new SynchedPropertySimpleOneWayPU(k12.operationType, this, 'operationType');
        this.operationItem = null;
        this.operationSymbolOptions = null;
        this.callbackId = undefined;
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.__ageing = new ObservedPropertySimplePU(true, this, 'ageing');
        this.__textArrowBgColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'textArrowBgColor');
        this.__buttonBgColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'buttonBgColor');
        this.__buttonStyleWidth = new ObservedPropertySimplePU(0, this, 'buttonStyleWidth');
        this.__buttonStyleHeight = new ObservedPropertySimplePU(0, this, 'buttonStyleHeight');
        this.__textArrowStyleWidth = new ObservedPropertySimplePU(0, this, 'textArrowStyleWidth');
        this.__textArrowStyleHeight = new ObservedPropertySimplePU(0, this, 'textArrowStyleHeight');
        this.__iconWidth = new ObservedPropertySimplePU(0, this, 'iconWidth');
        this.__selectedIndex = new ObservedPropertyObjectPU(-1, this, 'selectedIndex');
        this.__selectValue = new ObservedPropertyObjectPU('', this, 'selectValue');
        this.__flexAlign = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, 'flexAlign');
        this.titleBuilder = undefined;
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(k12.contentMargin, this, 'contentMargin');
        this.__contentPadding = new SynchedPropertyObjectOneWayPU(k12.contentPadding, this, 'contentPadding');
        this.__subHeaderMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
        }, this, 'subHeaderMargin');
        this.__subHeaderTheme = new ObservedPropertyObjectPU(new SubHeaderTheme(), this, 'subHeaderTheme');
        this.addProvidedVar('subHeaderTheme', this.__subHeaderTheme, false);
        this.constraintWidth = 0;
        this.paddingLeft = 2;
        this.setInitiallyProvidedValue(k12);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(i12) {
        if (i12.icon === undefined) {
            this.__icon.set(null);
        }
        if (i12.iconSymbolOptions !== undefined) {
            this.iconSymbolOptions = i12.iconSymbolOptions;
        }
        if (i12.primaryTitle === undefined) {
            this.__primaryTitle.set(null);
        }
        if (i12.primaryTitleModifier !== undefined) {
            this.primaryTitleModifier = i12.primaryTitleModifier;
        }
        if (i12.secondaryTitle === undefined) {
            this.__secondaryTitle.set(null);
        }
        if (i12.secondaryTitleModifier !== undefined) {
            this.secondaryTitleModifier = i12.secondaryTitleModifier;
        }
        if (i12.subHeaderModifier !== undefined) {
            this.subHeaderModifier = i12.subHeaderModifier;
        }
        if (i12.select !== undefined) {
            this.select = i12.select;
        }
        if (i12.operationType === undefined) {
            this.__operationType.set(OperationType.BUTTON);
        }
        if (i12.operationItem !== undefined) {
            this.operationItem = i12.operationItem;
        }
        if (i12.operationSymbolOptions !== undefined) {
            this.operationSymbolOptions = i12.operationSymbolOptions;
        }
        if (i12.callbackId !== undefined) {
            this.callbackId = i12.callbackId;
        }
        if (i12.fontSize !== undefined) {
            this.fontSize = i12.fontSize;
        }
        if (i12.ageing !== undefined) {
            this.ageing = i12.ageing;
        }
        if (i12.textArrowBgColor !== undefined) {
            this.textArrowBgColor = i12.textArrowBgColor;
        }
        if (i12.buttonBgColor !== undefined) {
            this.buttonBgColor = i12.buttonBgColor;
        }
        if (i12.buttonStyleWidth !== undefined) {
            this.buttonStyleWidth = i12.buttonStyleWidth;
        }
        if (i12.buttonStyleHeight !== undefined) {
            this.buttonStyleHeight = i12.buttonStyleHeight;
        }
        if (i12.textArrowStyleWidth !== undefined) {
            this.textArrowStyleWidth = i12.textArrowStyleWidth;
        }
        if (i12.textArrowStyleHeight !== undefined) {
            this.textArrowStyleHeight = i12.textArrowStyleHeight;
        }
        if (i12.iconWidth !== undefined) {
            this.iconWidth = i12.iconWidth;
        }
        if (i12.selectedIndex !== undefined) {
            this.selectedIndex = i12.selectedIndex;
        }
        if (i12.selectValue !== undefined) {
            this.selectValue = i12.selectValue;
        }
        if (i12.flexAlign !== undefined) {
            this.flexAlign = i12.flexAlign;
        }
        if (i12.titleBuilder !== undefined) {
            this.titleBuilder = i12.titleBuilder;
        }
        if (i12.subHeaderMargin !== undefined) {
            this.subHeaderMargin = i12.subHeaderMargin;
        }
        if (i12.subHeaderTheme !== undefined) {
            this.subHeaderTheme = i12.subHeaderTheme;
        }
        if (i12.constraintWidth !== undefined) {
            this.constraintWidth = i12.constraintWidth;
        }
        if (i12.paddingLeft !== undefined) {
            this.paddingLeft = i12.paddingLeft;
        }
    }
    updateStateVars(h12) {
        this.__icon.reset(h12.icon);
        this.__primaryTitle.reset(h12.primaryTitle);
        this.__secondaryTitle.reset(h12.secondaryTitle);
        this.__operationType.reset(h12.operationType);
        this.__contentMargin.reset(h12.contentMargin);
        this.__contentPadding.reset(h12.contentPadding);
    }
    purgeVariableDependenciesOnElmtId(g12) {
        this.__icon.purgeDependencyOnElmtId(g12);
        this.__primaryTitle.purgeDependencyOnElmtId(g12);
        this.__primaryTitleModifier.purgeDependencyOnElmtId(g12);
        this.__secondaryTitle.purgeDependencyOnElmtId(g12);
        this.__secondaryTitleModifier.purgeDependencyOnElmtId(g12);
        this.__subHeaderModifier.purgeDependencyOnElmtId(g12);
        this.__operationType.purgeDependencyOnElmtId(g12);
        this.__fontSize.purgeDependencyOnElmtId(g12);
        this.__ageing.purgeDependencyOnElmtId(g12);
        this.__textArrowBgColor.purgeDependencyOnElmtId(g12);
        this.__buttonBgColor.purgeDependencyOnElmtId(g12);
        this.__buttonStyleWidth.purgeDependencyOnElmtId(g12);
        this.__buttonStyleHeight.purgeDependencyOnElmtId(g12);
        this.__textArrowStyleWidth.purgeDependencyOnElmtId(g12);
        this.__textArrowStyleHeight.purgeDependencyOnElmtId(g12);
        this.__iconWidth.purgeDependencyOnElmtId(g12);
        this.__selectedIndex.purgeDependencyOnElmtId(g12);
        this.__selectValue.purgeDependencyOnElmtId(g12);
        this.__flexAlign.purgeDependencyOnElmtId(g12);
        this.__contentMargin.purgeDependencyOnElmtId(g12);
        this.__contentPadding.purgeDependencyOnElmtId(g12);
        this.__subHeaderMargin.purgeDependencyOnElmtId(g12);
        this.__subHeaderTheme.purgeDependencyOnElmtId(g12);
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
    set icon(f12) {
        this.__icon.set(f12);
    }
    get primaryTitle() {
        return this.__primaryTitle.get();
    }
    set primaryTitle(e12) {
        this.__primaryTitle.set(e12);
    }
    get primaryTitleModifier() {
        return this.__primaryTitleModifier.get();
    }
    set primaryTitleModifier(d12) {
        this.__primaryTitleModifier.set(d12);
    }
    get secondaryTitle() {
        return this.__secondaryTitle.get();
    }
    set secondaryTitle(c12) {
        this.__secondaryTitle.set(c12);
    }
    get secondaryTitleModifier() {
        return this.__secondaryTitleModifier.get();
    }
    set secondaryTitleModifier(b12) {
        this.__secondaryTitleModifier.set(b12);
    }
    get subHeaderModifier() {
        return this.__subHeaderModifier.get();
    }
    set subHeaderModifier(a12) {
        this.__subHeaderModifier.set(a12);
    }
    get operationType() {
        return this.__operationType.get();
    }
    set operationType(z11) {
        this.__operationType.set(z11);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(y11) {
        this.__fontSize.set(y11);
    }
    get ageing() {
        return this.__ageing.get();
    }
    set ageing(x11) {
        this.__ageing.set(x11);
    }
    get textArrowBgColor() {
        return this.__textArrowBgColor.get();
    }
    set textArrowBgColor(w11) {
        this.__textArrowBgColor.set(w11);
    }
    get buttonBgColor() {
        return this.__buttonBgColor.get();
    }
    set buttonBgColor(v11) {
        this.__buttonBgColor.set(v11);
    }
    get buttonStyleWidth() {
        return this.__buttonStyleWidth.get();
    }
    set buttonStyleWidth(u11) {
        this.__buttonStyleWidth.set(u11);
    }
    get buttonStyleHeight() {
        return this.__buttonStyleHeight.get();
    }
    set buttonStyleHeight(t11) {
        this.__buttonStyleHeight.set(t11);
    }
    get textArrowStyleWidth() {
        return this.__textArrowStyleWidth.get();
    }
    set textArrowStyleWidth(s11) {
        this.__textArrowStyleWidth.set(s11);
    }
    get textArrowStyleHeight() {
        return this.__textArrowStyleHeight.get();
    }
    set textArrowStyleHeight(r11) {
        this.__textArrowStyleHeight.set(r11);
    }
    get iconWidth() {
        return this.__iconWidth.get();
    }
    set iconWidth(q11) {
        this.__iconWidth.set(q11);
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(p11) {
        this.__selectedIndex.set(p11);
    }
    get selectValue() {
        return this.__selectValue.get();
    }
    set selectValue(o11) {
        this.__selectValue.set(o11);
    }
    get flexAlign() {
        return this.__flexAlign.get();
    }
    set flexAlign(n11) {
        this.__flexAlign.set(n11);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(m11) {
        this.__contentMargin.set(m11);
    }
    get contentPadding() {
        return this.__contentPadding.get();
    }
    set contentPadding(l11) {
        this.__contentPadding.set(l11);
    }
    get subHeaderMargin() {
        return this.__subHeaderMargin.get();
    }
    set subHeaderMargin(k11) {
        this.__subHeaderMargin.set(k11);
    }
    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }
    set subHeaderTheme(j11) {
        this.__subHeaderTheme.set(j11);
    }
    onWillApplyTheme(i11) {
        this.subHeaderTheme.fontPrimaryColor = i11.colors.fontPrimary;
        this.subHeaderTheme.fontSecondaryColor = i11.colors.fontSecondary;
        this.subHeaderTheme.fontButtonColor = i11.colors.fontEmphasize;
        this.subHeaderTheme.iconArrowColor = i11.colors.iconTertiary;
        this.subHeaderTheme.textArrowHoverBgColor = i11.colors.interactiveHover;
        this.subHeaderTheme.borderFocusColor = i11.colors.interactiveFocus;
        this.subHeaderTheme.leftIconColor = i11.colors.iconSecondary;
        this.subHeaderTheme.rightIconColor = i11.colors.iconPrimary;
    }
    async aboutToAppear() {
        let h11 = this.getUIContext().getHostContext();
        this.fontSize = h11.config?.fontSizeScale ?? 1;
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
        this.observeComponentCreation((f10, g10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f10);
            If.create();
            if (this.isSuitableAging()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((f11, g11) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(f11);
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.padding(this.getAreaPadding());
                        if (!g11) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((d11, e11) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(d11);
                        Row.create();
                        Row.margin({
                            top: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                            bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                        });
                        Row.padding({
                            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                        });
                        Row.width('100%');
                        if (!e11) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.leftArea.bind(this)(this);
                    Row.pop();
                    this.observeComponentCreation((y10, z10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(y10);
                        Row.create();
                        Row.margin({
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.padding({
                            start: LengthMetrics.vp((Util.getNumberByResource(125830936) ?? 16) - this.paddingLeft),
                            end: LengthMetrics.vp(Util.getNumberByResource(125830937) ?? 16),
                        });
                        Row.justifyContent(FlexAlign.Start);
                        Row.width('100%');
                        Row.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW || this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Row.onTouch((c11) => {
                            if (c11.type === TouchType.Down) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                            }
                            if (c11.type === TouchType.Up || c11.type === TouchType.Cancel) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                            }
                        });
                        if (!z10) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.rightArea.bind(this)(this);
                    Row.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((s10, t10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(s10);
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.contentMargin ?? this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                        if (!t10) {
                            Flex.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((q10, r10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(q10);
                        Row.create();
                        Row.width('100%');
                        Row.flexShrink(1);
                        if (!r10) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.leftArea.bind(this)(this);
                    Row.pop();
                    this.observeComponentCreation((l10, m10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(l10);
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
                            if ((this.operationType === OperationType.TEXT_ARROW || this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Row.onTouch((p10) => {
                            if (p10.type === TouchType.Down) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                            }
                            if (p10.type === TouchType.Up || p10.type === TouchType.Cancel) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                            }
                        });
                        if (!m10) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.rightArea.bind(this)(this);
                    Row.pop();
                    Flex.pop();
                });
            }
            if (!g10) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
    }
    onMeasureSize(x9, y9, z9) {
        let a10 = { width: x9.width, height: x9.height };
        let b10 = this.getUIContext().getHostContext();
        this.fontSize = b10.config?.fontSizeScale ?? 1;
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        y9.forEach((d10) => {
            z9.minHeight = Math.min(Number(this.getMinHeight()), Number(z9.maxHeight));
            a10.height = d10.measure(z9).height;
            a10.width = Number(z9.maxWidth);
        });
        return a10;
    }
    onPlaceChildren(s9, t9, u9) {
        t9.forEach((w9) => {
            w9.layout({ x: 0, y: 0 });
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
            return LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }
        return LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
        let r9 = {};
        if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
            (!this.primaryTitle && this.secondaryTitle))) {
            r9 = {
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            };
        }
        return r9;
    }
    leftArea(g9 = null) {
        this.observeComponentCreation((i9, j9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i9);
            If.create();
            if (this.titleBuilder) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.titleBuilder.bind(this)(g9 ? g9 : this);
                });
            }
            else if (this.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondaryTitleStyle', { content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']), iconOptions: () => ({
                        icon: this.icon,
                        symbolicIconOption: this.iconSymbolOptions,
                    }) }), g9 ? g9 : this);
                });
            }
            else if (this.secondaryTitle && this.primaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle', { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']), subContent: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']) }), g9 ? g9 : this);
                });
            }
            else if (this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle', { content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']) }), g9 ? g9 : this);
                });
            }
            else if (this.select) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.SelectStyle.bind(this)(this.select, g9 ? g9 : this);
                });
            }
            else if (this.primaryTitle) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle', { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']) }), g9 ? g9 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.dummyFunction.bind(this)(g9 ? g9 : this);
                });
            }
            if (!j9) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
    }
    rightArea(l8 = null) {
        this.observeComponentCreation((c9, d9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(c9);
            If.create();
            if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)(this.operationItem[0], l8 ? l8 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!d9) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((y8, z8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(y8);
            If.create();
            if (this.operationType === OperationType.TEXT_ARROW && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextArrowStyle.bind(this)(this.operationItem[0], l8 ? l8 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!z8) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((u8, v8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u8);
            If.create();
            if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconGroupStyle.bind(this)(this.operationItem, l8 ? l8 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!v8) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((q8, r8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q8);
            If.create();
            if (this.operationType === OperationType.LOADING) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.LoadingProcessStyle.bind(this)(l8 ? l8 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!r8) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
    }
    IconSecondaryTitleStyle(r7, s7 = null) {
        this.observeComponentCreation((i8, j8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i8);
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Flex.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
            if (!j8) {
                Flex.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((y7, z7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(y7);
            If.create();
            if (Util.isSymbolResource(r7.iconOptions?.icon)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((g8, h8) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(g8);
                        SymbolGlyph.create(r7.iconOptions?.icon);
                        SymbolGlyph.fontSize(r7.iconOptions?.symbolicIconOption?.fontSize ?
                        Util.symbolFontSize(r7.iconOptions?.symbolicIconOption?.fontSize) : LEFT_ICON_SIZE);
                        SymbolGlyph.fontColor(r7.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.leftIconColor]);
                        SymbolGlyph.fontWeight(r7.iconOptions?.symbolicIconOption?.fontWeight);
                        SymbolGlyph.renderingStrategy(r7.iconOptions?.symbolicIconOption?.renderingStrategy);
                        SymbolGlyph.effectStrategy(r7.iconOptions?.symbolicIconOption?.effectStrategy);
                        SymbolGlyph.margin({ end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) });
                        SymbolGlyph.flexShrink(0);
                        if (!h8) {
                            SymbolGlyph.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((c8, d8) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(c8);
                        Image.create(r7.iconOptions?.icon);
                        Image.fillColor(this.subHeaderTheme.leftIconColor);
                        Image.width(LEFT_ICON_SIZE);
                        Image.height(LEFT_ICON_SIZE);
                        Image.margin({ end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) });
                        Image.draggable(false);
                        Image.flexShrink(0);
                        if (!d8) {
                            Image.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            if (!z7) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((w7, x7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w7);
            Text.create(r7.content);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
            Text.flexShrink(1);
            if (!x7) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        Flex.pop();
    }
    SubTitleStyle(f7, g7 = null) {
        this.observeComponentCreation((o7, p7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o7);
            Column.create();
            Column.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Column.alignItems(HorizontalAlign.Start);
            Column.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
            if (!p7) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((m7, n7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(m7);
            Text.create(f7.content);
            __Text__primaryTitleStyles({
                fontWeight: FontWeight.Bold,
                maxLines: SINGLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
            Text.width('100%');
            if (!n7) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        this.observeComponentCreation((k7, l7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k7);
            Text.create(f7.subContent);
            __Text__secondaryTitleStyles({
                maxLines: SINGLE_LINE_NUM,
                fontWeight: FontWeight.Regular,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.width('100%');
            Text.margin({
                top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
            if (!l7) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        Column.pop();
    }
    SecondTitleStyle(w6, x6 = null) {
        this.observeComponentCreation((d7, e7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(d7);
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            if (!e7) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((a7, b7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(a7);
            Text.create(w6.content);
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
            if (!b7) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        Column.pop();
    }
    SelectStyle(k6, l6 = null) {
        this.observeComponentCreation((t6, u6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t6);
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
            if (!u6) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((o6, p6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o6);
            Select.create(k6.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
            Select.value(ObservedObject.GetRawObject(this.selectValue));
            Select.onSelect((r6, s6) => {
                this.selectedIndex = r6;
                if (s6) {
                    this.selectValue = s6;
                }
                if (k6.onSelect) {
                    k6.onSelect(r6, s6);
                }
            });
            Select.font({
                size: { 'id': -1, 'type': 10002, params: ['sys.float.Body_L'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                weight: FontWeight.Medium,
            });
            if (!p6) {
                Select.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Select.pop();
        Column.pop();
    }
    PrimaryTitleStyle(b6, c6 = null) {
        this.observeComponentCreation((i6, j6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i6);
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            if (!j6) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((f6, g6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f6);
            Text.create(b6.content);
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
            if (!g6) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        Column.pop();
    }
    ButtonStyle(a5, b5 = null) {
        this.observeComponentCreation((z5, a6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(z5);
            Row.create();
            Row.margin({
                start: LengthMetrics.resource(this.ageing ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: LengthMetrics.resource(this.ageing ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Row.justifyContent(FlexAlign.End);
            if (!a6) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((x5, y5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(x5);
            Stack.create();
            Stack.focusable(true);
            if (!y5) {
                Stack.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((f5, g5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f5);
            If.create();
            if (a5) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((q5, r5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(q5);
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
                        Row.constraintSize({ minHeight: OPERATE_ITEM_LENGTH });
                        Row.justifyContent(FlexAlign.End);
                        Row.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Row.onHover((w5) => {
                            if (w5) {
                                this.buttonBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                            }
                            else {
                                this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                            }
                        });
                        Row.onSizeChange((u5, v5) => {
                            this.buttonStyleWidth = Number(v5.width);
                            this.buttonStyleHeight = Number(v5.height);
                        });
                        if (!r5) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((o5, p5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(o5);
                        Text.create(a5.value);
                        __Text__secondaryTitleStyles({
                            fontWeight: FontWeight.Medium,
                            maxLines: DOUBLE_LINE_NUM,
                            fontColor: this.subHeaderTheme.fontButtonColor,
                        });
                        if (!p5) {
                            Text.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Text.pop();
                    Row.pop();
                    this.observeComponentCreation((m5, n5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(m5);
                        Text.create();
                        Text.focusable(true);
                        Text.width(this.buttonStyleWidth);
                        Text.height(this.buttonStyleHeight);
                        Text.hitTestBehavior(HitTestMode.None);
                        ViewStackProcessor.visualState('focused');
                        Text.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: { 'id': -1, 'type': 10002, params: ['sys.float.outline_extra_larger'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            color: this.subHeaderTheme.borderFocusColor,
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
                        if (!n5) {
                            Text.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Text.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!g5) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
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
    TextArrowStyle(w3, x3 = null) {
        this.observeComponentCreation((y4, z4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(y4);
            Row.create();
            Row.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.subHeaderModifier));
            Row.focusable(true);
            Row.justifyContent(this.ageing ? FlexAlign.SpaceBetween : FlexAlign.End);
            Row.margin({
                start: LengthMetrics.resource(this.ageing ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: LengthMetrics.resource(this.ageing ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            if (!z4) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((u4, v4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u4);
            Stack.create();
            Stack.margin({
                start: this.leftIconMargin(),
            });
            Stack.onHover((x4) => {
                if (x4) {
                    this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                }
                else {
                    this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                }
            });
            if (!v4) {
                Stack.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((p4, q4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p4);
            Row.create();
            Row.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.subHeaderModifier));
            Row.alignItems(VerticalAlign.Center);
            Row.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Row.focusable(true);
            Row.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
            Row.constraintSize({ minHeight: OPERATE_ITEM_LENGTH });
            Row.padding({
                start: this.getTextArrowPaddingLeft(),
                top: this.ageing ? LengthMetrics.vp(0) : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: this.ageing ? LengthMetrics.vp(0) : LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Row.onSizeChange((s4, t4) => {
                this.textArrowStyleWidth = Number(t4.width);
                this.textArrowStyleHeight = Number(t4.height);
            });
            if (!q4) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((i4, j4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i4);
            If.create();
            if (w3) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((n4, o4) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(n4);
                        Text.create(w3.value);
                        __Text__secondaryTitleStyles({
                            maxLines: DOUBLE_LINE_NUM,
                            fontWeight: FontWeight.Regular,
                            alignment: Alignment.End,
                            fontColor: this.subHeaderTheme.fontSecondaryColor,
                        });
                        Text.margin({
                            end: this.getTextArrowMarginRight(),
                        });
                        if (!o4) {
                            Text.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Text.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!j4) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Row.pop();
        this.observeComponentCreation((g4, h4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(g4);
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.height(this.textArrowStyleHeight);
            Row.width(this.textArrowStyleWidth);
            Row.hitTestBehavior(HitTestMode.None);
            ViewStackProcessor.visualState('focused');
            Row.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.outline_extra_larger'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: this.subHeaderTheme.borderFocusColor,
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
            if (!h4) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((e4, f4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e4);
            Image.create({ 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_arrow_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.fillColor(this.subHeaderTheme.iconArrowColor);
            Image.width(ARROW_ICON_WIDTH);
            Image.height(OPERATE_ITEM_LENGTH);
            Image.focusable(true);
            Image.draggable(false);
            Image.matchTextDirection(true);
            if (!f4) {
                Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Row.pop();
        Stack.pop();
        Row.pop();
    }
    IconGroupStyle(p2, q2 = null) {
        this.observeComponentCreation((u3, v3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u3);
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
            if (!v3) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((t2, u2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t2);
            ForEach.create();
            const v2 = (x2, y2) => {
                const z2 = x2;
                this.observeComponentCreation((b3, c3) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(b3);
                    If.create();
                    if (Util.isResourceType(z2.value)) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation((g3, h3) => {
                                ViewStackProcessor.StartGetAccessRecordingFor(g3);
                                If.create();
                                if (y2 <= INDEX_TWO) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation((s3, t3) => {
                                            ViewStackProcessor.StartGetAccessRecordingFor(s3);
                                            __Common__.create();
                                            __Common__.margin({
                                                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                                                bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                                            });
                                            if (!t3) {
                                                __Common__.pop();
                                            }
                                            ViewStackProcessor.StopGetAccessRecording();
                                        });
                                        {
                                            this.observeComponentCreation((m3, n3) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(m3);
                                                if (n3) {
                                                    let o3 = new SingleIconStyle(typeof PUV2ViewBase !== 'undefined' && q2 instanceof PUV2ViewBase ? q2 : this, {
                                                        item: {
                                                            iconOptions: {
                                                                icon: z2.value,
                                                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > y2 ?
                                                                this.operationSymbolOptions[y2] : null,
                                                            },
                                                            action: z2.action,
                                                        },
                                                        isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER,
                                                    }, undefined, m3, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 760, col: 13 });
                                                    ViewPU.create(o3);
                                                    let p3 = () => {
                                                        return {
                                                            item: {
                                                                iconOptions: {
                                                                    icon: z2.value,
                                                                    symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > y2 ?
                                                                    this.operationSymbolOptions[y2] : null,
                                                                },
                                                                action: z2.action,
                                                            },
                                                            isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER
                                                        };
                                                    };
                                                    o3.paramsGenerator_ = p3;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(m3, {});
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        }
                                        __Common__.pop();
                                    });
                                }
                                else {
                                    this.ifElseBranchUpdateFunction(1, () => {
                                    });
                                }
                                if (!h3) {
                                    If.pop();
                                }
                                ViewStackProcessor.StopGetAccessRecording();
                            });
                            If.pop();
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                    if (!c3) {
                        If.pop();
                    }
                    ViewStackProcessor.StopGetAccessRecording();
                });
                If.pop();
            };
            this.forEachUpdateFunction(t2, p2, v2, undefined, true, false);
            if (!u2) {
                ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        ForEach.pop();
        Row.pop();
    }
    LoadingProcessStyle(i2 = null) {
        this.observeComponentCreation((n2, o2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n2);
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.padding({
                top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            Row.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            if (!o2) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((l2, m2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(l2);
            LoadingProgress.create();
            LoadingProgress.width(OPERATE_ITEM_LENGTH);
            LoadingProgress.height(OPERATE_ITEM_LENGTH);
            LoadingProgress.color({ 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            if (!m2) {
                LoadingProgress.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Row.pop();
    }
    dummyFunction(d2 = null) {
        this.observeComponentCreation((f2, g2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f2);
            Row.create();
            Row.onAppear(() => {
                this.changeFlexAlign(FlexAlign.End);
            });
            if (!g2) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Row.pop();
    }
    changeFlexAlign(c2) {
        if (this.flexAlign === c2) {
            return;
        }
        this.flexAlign = c2;
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class SingleIconStyle extends ViewPU {
    constructor(w1, x1, y1, z1 = -1, a2 = undefined, b2) {
        super(w1, y1, z1, b2);
        if (typeof a2 === 'function') {
            this.paramsGenerator_ = a2;
        }
        this.__bgColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'bgColor');
        this.__isFocus = new ObservedPropertySimplePU(false, this, 'isFocus');
        this.item = null;
        this.__subHeaderTheme = this.initializeConsume('subHeaderTheme', 'subHeaderTheme');
        this.isSingleIcon = true;
        this.setInitiallyProvidedValue(x1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(v1) {
        if (v1.bgColor !== undefined) {
            this.bgColor = v1.bgColor;
        }
        if (v1.isFocus !== undefined) {
            this.isFocus = v1.isFocus;
        }
        if (v1.item !== undefined) {
            this.item = v1.item;
        }
        if (v1.isSingleIcon !== undefined) {
            this.isSingleIcon = v1.isSingleIcon;
        }
    }
    updateStateVars(u1) {
    }
    purgeVariableDependenciesOnElmtId(t1) {
        this.__bgColor.purgeDependencyOnElmtId(t1);
        this.__isFocus.purgeDependencyOnElmtId(t1);
        this.__subHeaderTheme.purgeDependencyOnElmtId(t1);
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
    set bgColor(s1) {
        this.__bgColor.set(s1);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(r1) {
        this.__isFocus.set(r1);
    }
    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }
    set subHeaderTheme(q1) {
        this.__subHeaderTheme.set(q1);
    }
    initialRender() {
        this.observeComponentCreation((d1, e1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(d1);
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((i1, j1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(i1);
                        Row.create();
                        Row.focusable(true);
                        Row.width(SINGLE_ICON_ZONE_SIZE);
                        Row.height(SINGLE_ICON_ZONE_SIZE);
                        Row.justifyContent(FlexAlign.Center);
                        Row.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
                        ViewStackProcessor.visualState('normal');
                        Row.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: { 'id': -1, 'type': 10002, params: ['sys.float.border_none'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        ViewStackProcessor.visualState('focused');
                        Row.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: { 'id': -1, 'type': 10002, params: ['sys.float.outline_extra_larger'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            color: this.subHeaderTheme.borderFocusColor,
                            style: BorderStyle.Solid,
                        });
                        ViewStackProcessor.visualState('pressed');
                        Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        ViewStackProcessor.visualState('disabled');
                        Row.opacity({ 'id': -1, 'type': 10002, params: ['sys.float.interactive_disable'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        ViewStackProcessor.visualState();
                        Row.onTouch((p1) => {
                            if (p1.type === TouchType.Down || TouchType.Cancel) {
                                this.bgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                            }
                            if (p1.type === TouchType.Up) {
                                this.bgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                            }
                        });
                        Row.onHover((o1) => {
                            if (o1) {
                                this.bgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                            }
                            else {
                                this.bgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                            }
                        });
                        Row.responseRegion(this.iconResponseRegion());
                        Row.onClick((n1) => {
                            if (this.item?.action) {
                                this.item?.action();
                            }
                        });
                        if (!j1) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.IconZone.bind(this)(this);
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!e1) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
    }
    iconResponseRegion() {
        if (this.isSingleIcon) {
            return { x: SINGLE_ICON_REGION_X, y: ICON_REGION_Y, width: MIN_HOT_AREA_LENGTH, height: MIN_HOT_AREA_LENGTH };
        }
        return { x: ICON_REGION_X, y: ICON_REGION_Y, width: MULTI_ICON_REGION_WIDTH, height: MIN_HOT_AREA_LENGTH };
    }
    fontSizeValue(b1) {
        return b1.iconOptions?.symbolicIconOption?.fontSize ?
        Util.symbolFontSize(b1.iconOptions?.symbolicIconOption?.fontSize) : RIGHT_SINGLE_ICON_SIZE;
    }
    IconZone(k = null) {
        this.observeComponentCreation((m, n) => {
            ViewStackProcessor.StartGetAccessRecordingFor(m);
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((r, s) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(r);
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((z, a1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(z);
                                    SymbolGlyph.create(this.item.iconOptions?.icon);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.fontSize(this.fontSizeValue(this.item));
                                    SymbolGlyph.fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.rightIconColor]);
                                    SymbolGlyph.fontWeight(this.item.iconOptions?.symbolicIconOption?.fontWeight);
                                    SymbolGlyph.renderingStrategy(this.item.iconOptions?.symbolicIconOption?.renderingStrategy);
                                    SymbolGlyph.effectStrategy(this.item.iconOptions?.symbolicIconOption?.effectStrategy);
                                    if (!a1) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((v, w) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(v);
                                    Image.create(this.item?.iconOptions?.icon);
                                    Image.fillColor(this.subHeaderTheme.rightIconColor);
                                    Image.width(RIGHT_SINGLE_ICON_SIZE);
                                    Image.height(RIGHT_SINGLE_ICON_SIZE);
                                    Image.focusable(true);
                                    Image.draggable(false);
                                    if (!w) {
                                        Image.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        if (!s) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!n) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class Util {
    static isSymbolResource(i) {
        if (!Util.isResourceType(i)) {
            return false;
        }
        let j = i;
        return j.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(h) {
        if (!h) {
            return false;
        }
        if (typeof h === 'string' || typeof h === 'undefined') {
            return false;
        }
        return true;
    }
    static getNumberByResource(d) {
        try {
            return resourceManager.getSystemResourceManager().getNumber(d);
        }
        catch (e) {
            let f = e.code;
            let g = e.message;
            hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${f}, message: ${g}`);
            return null;
        }
    }
    static numberToSize(b) {
        if (typeof b === 'string') {
            const c = parseInt(b);
            return c;
        }
        else if (typeof b === 'number') {
            return b;
        }
        else {
            return resourceManager.getSystemResourceManager().getNumber(b);
        }
    }
    static symbolFontSize(a) {
        return Util.numberToSize(a) + 'vp';
    }
}
_a = Util;
Util.DEFAULT_VALUE = 0;
Util.DEFAULT_BREAKPOINT_S = 600;
Util.DEFAULT_BREAKPOINT_M = 840;
Util.CALCULATE_BREAKPOINT_S = _a.getNumberByResource(125832765) ?? 600;
Util.CALCULATE_BREAKPOINT_M = _a.getNumberByResource(125832766) ?? 840;
Util.BREAKPOINT_S = _a.CALCULATE_BREAKPOINT_S === _a.DEFAULT_VALUE ? _a.DEFAULT_BREAKPOINT_S : _a.CALCULATE_BREAKPOINT_S;
Util.BREAKPOINT_M = _a.CALCULATE_BREAKPOINT_M === _a.DEFAULT_VALUE ? _a.DEFAULT_BREAKPOINT_M : _a.CALCULATE_BREAKPOINT_M;

export default { OperationType, SubHeader };