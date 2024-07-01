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
const BORDER_WIDTH = 2;
const RESOURCE_TYPE_SYMBOL = 40000;
const LEFT_ICON_SIZE = '16vp';
const LEFT_ICON_SIZE_NUMBER = 16;
const LEFT_TEXT_NUMBER = 8;
const BUTTON_ZONE_SIZE = 32;
const BUTTON_HEIGHT = 28;
const ARROW_ICON_WIDTH = 12;
const ARROW_ICON_HEIGHT = 24;
const SINGLE_ICON_ZONE_SIZE = 28;
const RIGHT_SINGLE_ICON_SIZE = '24vp';
const LOADING_SIZE = 24;
const PADDING_LEVEL_2 = 4;
const MAX_RIGHT_WIDTH = '34%';
const MIN_FONT_SIZE = 1.75;
const MIN_HOT_AREA_LENGTH = 40;
const MULTI_ICON_REGION_WIDTH = 36;
const ICON_REGION_X = -9;
const ICON_REGION_Y = -8;
const SINGLE_ICON_REGION_X = -12;
const SINGLE_ICON_NUMBER = 1;
export var OperationType;
(function (k12) {
    k12[k12['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
    k12[k12['BUTTON'] = 1] = 'BUTTON';
    k12[k12['ICON_GROUP'] = 2] = 'ICON_GROUP';
    k12[k12['LOADING'] = 3] = 'LOADING';
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
function __Text__secondaryTitleStyles(j12) {
    Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Subtitle_S'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontColor(j12?.fontColor ?? { 'id': -1, 'type': 10001, params: ['sys.color.font_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontWeight(j12?.fontWeight);
    Text.maxLines(j12?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(j12?.alignment);
}
function __Text__primaryTitleStyles(i12) {
    Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Subtitle_L'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontColor(i12?.fontColor ?? { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    Text.fontWeight(i12?.fontWeight);
    Text.maxLines(i12?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(i12?.alignment);
}
class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }
    applyNormalAttribute(h12) {
        if (this.isAgeing) {
            h12.width('100%');
        }
        else {
        }
    }
}
export class SubHeader extends ViewPU {
    constructor(b12, c12, d12, e12 = -1, f12 = undefined, g12) {
        super(b12, d12, e12, g12);
        if (typeof f12 === 'function') {
            this.paramsGenerator_ = f12;
        }
        this.__icon = new SynchedPropertyObjectOneWayPU(c12.icon, this, 'icon');
        this.iconSymbolOptions = null;
        this.__primaryTitle = new SynchedPropertyObjectOneWayPU(c12.primaryTitle, this, 'primaryTitle');
        this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'primaryTitleModifier');
        this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(c12.secondaryTitle, this, 'secondaryTitle');
        this.__secondaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'secondaryTitleModifier');
        this.__subHeaderModifier = new ObservedPropertyObjectPU(new SubHeaderModifier(), this, 'subHeaderModifier');
        this.select = null;
        this.__operationType = new SynchedPropertySimpleOneWayPU(c12.operationType, this, 'operationType');
        this.operationItem = null;
        this.operationSymbolOptions = null;
        this.callbackId = undefined;
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.__ageing = new ObservedPropertySimplePU(true, this, 'ageing');
        this.__textArrowBgColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'textArrowBgColor');
        this.__buttonBgColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'buttonBgColor');
        this.__textArrowStyleWidth = new ObservedPropertySimplePU(0, this, 'textArrowStyleWidth');
        this.__textArrowStyleHeight = new ObservedPropertySimplePU(0, this, 'textArrowStyleHeight');
        this.__iconWidth = new ObservedPropertySimplePU(0, this, 'iconWidth');
        this.__selectedIndex = new ObservedPropertyObjectPU(-1, this, 'selectedIndex');
        this.__selectValue = new ObservedPropertyObjectPU('', this, 'selectValue');
        this.__flexAlign = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, 'flexAlign');
        this.titleBuilder = undefined;
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(c12.contentMargin, this, 'contentMargin');
        this.__contentPadding = new SynchedPropertyObjectOneWayPU(c12.contentPadding, this, 'contentPadding');
        this.__subHeaderMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })
        }, this, 'subHeaderMargin');
        this.__subHeaderTheme = new ObservedPropertyObjectPU(new SubHeaderTheme(), this, 'subHeaderTheme');
        this.addProvidedVar('subHeaderTheme', this.__subHeaderTheme, false);
        this.constraintWidth = 0;
        this.setInitiallyProvidedValue(c12);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(a12) {
        if (a12.icon === undefined) {
            this.__icon.set(null);
        }
        if (a12.iconSymbolOptions !== undefined) {
            this.iconSymbolOptions = a12.iconSymbolOptions;
        }
        if (a12.primaryTitle === undefined) {
            this.__primaryTitle.set(null);
        }
        if (a12.primaryTitleModifier !== undefined) {
            this.primaryTitleModifier = a12.primaryTitleModifier;
        }
        if (a12.secondaryTitle === undefined) {
            this.__secondaryTitle.set(null);
        }
        if (a12.secondaryTitleModifier !== undefined) {
            this.secondaryTitleModifier = a12.secondaryTitleModifier;
        }
        if (a12.subHeaderModifier !== undefined) {
            this.subHeaderModifier = a12.subHeaderModifier;
        }
        if (a12.select !== undefined) {
            this.select = a12.select;
        }
        if (a12.operationType === undefined) {
            this.__operationType.set(OperationType.BUTTON);
        }
        if (a12.operationItem !== undefined) {
            this.operationItem = a12.operationItem;
        }
        if (a12.operationSymbolOptions !== undefined) {
            this.operationSymbolOptions = a12.operationSymbolOptions;
        }
        if (a12.callbackId !== undefined) {
            this.callbackId = a12.callbackId;
        }
        if (a12.fontSize !== undefined) {
            this.fontSize = a12.fontSize;
        }
        if (a12.ageing !== undefined) {
            this.ageing = a12.ageing;
        }
        if (a12.textArrowBgColor !== undefined) {
            this.textArrowBgColor = a12.textArrowBgColor;
        }
        if (a12.buttonBgColor !== undefined) {
            this.buttonBgColor = a12.buttonBgColor;
        }
        if (a12.textArrowStyleWidth !== undefined) {
            this.textArrowStyleWidth = a12.textArrowStyleWidth;
        }
        if (a12.textArrowStyleHeight !== undefined) {
            this.textArrowStyleHeight = a12.textArrowStyleHeight;
        }
        if (a12.iconWidth !== undefined) {
            this.iconWidth = a12.iconWidth;
        }
        if (a12.selectedIndex !== undefined) {
            this.selectedIndex = a12.selectedIndex;
        }
        if (a12.selectValue !== undefined) {
            this.selectValue = a12.selectValue;
        }
        if (a12.flexAlign !== undefined) {
            this.flexAlign = a12.flexAlign;
        }
        if (a12.titleBuilder !== undefined) {
            this.titleBuilder = a12.titleBuilder;
        }
        if (a12.subHeaderMargin !== undefined) {
            this.subHeaderMargin = a12.subHeaderMargin;
        }
        if (a12.subHeaderTheme !== undefined) {
            this.subHeaderTheme = a12.subHeaderTheme;
        }
        if (a12.constraintWidth !== undefined) {
            this.constraintWidth = a12.constraintWidth;
        }
    }
    updateStateVars(z11) {
        this.__icon.reset(z11.icon);
        this.__primaryTitle.reset(z11.primaryTitle);
        this.__secondaryTitle.reset(z11.secondaryTitle);
        this.__operationType.reset(z11.operationType);
        this.__contentMargin.reset(z11.contentMargin);
        this.__contentPadding.reset(z11.contentPadding);
    }
    purgeVariableDependenciesOnElmtId(y11) {
        this.__icon.purgeDependencyOnElmtId(y11);
        this.__primaryTitle.purgeDependencyOnElmtId(y11);
        this.__primaryTitleModifier.purgeDependencyOnElmtId(y11);
        this.__secondaryTitle.purgeDependencyOnElmtId(y11);
        this.__secondaryTitleModifier.purgeDependencyOnElmtId(y11);
        this.__subHeaderModifier.purgeDependencyOnElmtId(y11);
        this.__operationType.purgeDependencyOnElmtId(y11);
        this.__fontSize.purgeDependencyOnElmtId(y11);
        this.__ageing.purgeDependencyOnElmtId(y11);
        this.__textArrowBgColor.purgeDependencyOnElmtId(y11);
        this.__buttonBgColor.purgeDependencyOnElmtId(y11);
        this.__textArrowStyleWidth.purgeDependencyOnElmtId(y11);
        this.__textArrowStyleHeight.purgeDependencyOnElmtId(y11);
        this.__iconWidth.purgeDependencyOnElmtId(y11);
        this.__selectedIndex.purgeDependencyOnElmtId(y11);
        this.__selectValue.purgeDependencyOnElmtId(y11);
        this.__flexAlign.purgeDependencyOnElmtId(y11);
        this.__contentMargin.purgeDependencyOnElmtId(y11);
        this.__contentPadding.purgeDependencyOnElmtId(y11);
        this.__subHeaderMargin.purgeDependencyOnElmtId(y11);
        this.__subHeaderTheme.purgeDependencyOnElmtId(y11);
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
    set icon(x11) {
        this.__icon.set(x11);
    }
    get primaryTitle() {
        return this.__primaryTitle.get();
    }
    set primaryTitle(w11) {
        this.__primaryTitle.set(w11);
    }
    get primaryTitleModifier() {
        return this.__primaryTitleModifier.get();
    }
    set primaryTitleModifier(v11) {
        this.__primaryTitleModifier.set(v11);
    }
    get secondaryTitle() {
        return this.__secondaryTitle.get();
    }
    set secondaryTitle(u11) {
        this.__secondaryTitle.set(u11);
    }
    get secondaryTitleModifier() {
        return this.__secondaryTitleModifier.get();
    }
    set secondaryTitleModifier(t11) {
        this.__secondaryTitleModifier.set(t11);
    }
    get subHeaderModifier() {
        return this.__subHeaderModifier.get();
    }
    set subHeaderModifier(s11) {
        this.__subHeaderModifier.set(s11);
    }
    get operationType() {
        return this.__operationType.get();
    }
    set operationType(r11) {
        this.__operationType.set(r11);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(q11) {
        this.__fontSize.set(q11);
    }
    get ageing() {
        return this.__ageing.get();
    }
    set ageing(p11) {
        this.__ageing.set(p11);
    }
    get textArrowBgColor() {
        return this.__textArrowBgColor.get();
    }
    set textArrowBgColor(o11) {
        this.__textArrowBgColor.set(o11);
    }
    get buttonBgColor() {
        return this.__buttonBgColor.get();
    }
    set buttonBgColor(n11) {
        this.__buttonBgColor.set(n11);
    }
    get textArrowStyleWidth() {
        return this.__textArrowStyleWidth.get();
    }
    set textArrowStyleWidth(m11) {
        this.__textArrowStyleWidth.set(m11);
    }
    get textArrowStyleHeight() {
        return this.__textArrowStyleHeight.get();
    }
    set textArrowStyleHeight(l11) {
        this.__textArrowStyleHeight.set(l11);
    }
    get iconWidth() {
        return this.__iconWidth.get();
    }
    set iconWidth(k11) {
        this.__iconWidth.set(k11);
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(j11) {
        this.__selectedIndex.set(j11);
    }
    get selectValue() {
        return this.__selectValue.get();
    }
    set selectValue(i11) {
        this.__selectValue.set(i11);
    }
    get flexAlign() {
        return this.__flexAlign.get();
    }
    set flexAlign(h11) {
        this.__flexAlign.set(h11);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(g11) {
        this.__contentMargin.set(g11);
    }
    get contentPadding() {
        return this.__contentPadding.get();
    }
    set contentPadding(f11) {
        this.__contentPadding.set(f11);
    }
    get subHeaderMargin() {
        return this.__subHeaderMargin.get();
    }
    set subHeaderMargin(e11) {
        this.__subHeaderMargin.set(e11);
    }
    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }
    set subHeaderTheme(d11) {
        this.__subHeaderTheme.set(d11);
    }
    onWillApplyTheme(c11) {
        this.subHeaderTheme.fontPrimaryColor = c11.colors.fontPrimary;
        this.subHeaderTheme.fontSecondaryColor = c11.colors.fontSecondary;
        this.subHeaderTheme.fontButtonColor = c11.colors.fontEmphasize;
        this.subHeaderTheme.iconArrowColor = c11.colors.iconTertiary;
        this.subHeaderTheme.textArrowHoverBgColor = c11.colors.interactiveHover;
        this.subHeaderTheme.borderFocusColor = c11.colors.interactiveFocus;
        this.subHeaderTheme.leftIconColor = c11.colors.iconSecondary;
        this.subHeaderTheme.rightIconColor = c11.colors.iconPrimary;
    }
    async aboutToAppear() {
        let b11 = this.getUIContext().getHostContext();
        this.fontSize = b11.config?.fontSizeScale ?? 1;
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
        this.observeComponentCreation((z9, a10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(z9);
            If.create();
            if (this.isSuitableAging()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((z10, a11) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(z10);
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.margin(this.contentMargin ?? this.subHeaderMargin);
                        Column.padding(this.getAreaPadding());
                        if (!a11) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((x10, y10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(x10);
                        Row.create();
                        Row.margin({
                            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.width('100%');
                        if (!y10) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.leftArea.bind(this)(this);
                    Row.pop();
                    this.observeComponentCreation((s10, t10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(s10);
                        Row.create();
                        Row.margin({
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.justifyContent(FlexAlign.Start);
                        Row.width('100%');
                        Row.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW || this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Row.onTouch((w10) => {
                            if (w10.type === TouchType.Down) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                            }
                            if (w10.type === TouchType.Up) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                            }
                        });
                        if (!t10) {
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
                    this.observeComponentCreation((m10, n10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(m10);
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.contentMargin ?? this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                        if (!n10) {
                            Flex.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((k10, l10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(k10);
                        Row.create();
                        Row.width('100%');
                        Row.flexShrink(1);
                        if (!l10) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.leftArea.bind(this)(this);
                    Row.pop();
                    this.observeComponentCreation((f10, g10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(f10);
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
                        Row.onTouch((j10) => {
                            if (j10.type === TouchType.Down) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                            }
                            if (j10.type === TouchType.Up) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                                }
                            }
                        });
                        if (!g10) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.rightArea.bind(this)(this);
                    Row.pop();
                    Flex.pop();
                });
            }
            if (!a10) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
    }
    onMeasureSize(r9, s9, t9) {
        let u9 = { width: r9.width, height: r9.height };
        let v9 = this.getUIContext().getHostContext();
        this.fontSize = v9.config?.fontSizeScale ?? 1;
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        s9.forEach((x9) => {
            t9.minHeight = Math.min(Number(this.getMinHeight()), Number(t9.maxHeight));
            u9.height = x9.measure(t9).height;
            u9.width = Number(t9.maxWidth);
        });
        return u9;
    }
    onPlaceChildren(m9, n9, o9) {
        n9.forEach((q9) => {
            q9.layout({ x: 0, y: 0 });
        });
    }
    getRightAreaMaxWidth() {
        if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
            return '100%';
        }
        else {
            return MAX_RIGHT_WIDTH;
        }
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
        let l9 = {};
        if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
            (!this.primaryTitle && this.secondaryTitle))) {
            l9 = {
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            };
        }
        return l9;
    }
    leftArea(a9 = null) {
        this.observeComponentCreation((c9, d9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(c9);
            If.create();
            if (this.titleBuilder) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.titleBuilder.bind(this)(a9 ? a9 : this);
                });
            }
            else if (this.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondaryTitleStyle', { content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']), iconOptions: () => ({
                        icon: this.icon,
                        symbolicIconOption: this.iconSymbolOptions,
                    }) }), a9 ? a9 : this);
                });
            }
            else if (this.secondaryTitle && this.primaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle', { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']), subContent: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']) }), a9 ? a9 : this);
                });
            }
            else if (this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle', { content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']) }), a9 ? a9 : this);
                });
            }
            else if (this.select) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.SelectStyle.bind(this)(this.select, a9 ? a9 : this);
                });
            }
            else if (this.primaryTitle) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle', { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']) }), a9 ? a9 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.dummyFunction.bind(this)(a9 ? a9 : this);
                });
            }
            if (!d9) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
    }
    rightArea(f8 = null) {
        this.observeComponentCreation((w8, x8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w8);
            If.create();
            if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)(this.operationItem[0], f8 ? f8 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!x8) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((s8, t8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s8);
            If.create();
            if (this.operationType === OperationType.TEXT_ARROW && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextArrowStyle.bind(this)(this.operationItem[0], f8 ? f8 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!t8) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((o8, p8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o8);
            If.create();
            if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconGroupStyle.bind(this)(this.operationItem, f8 ? f8 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!p8) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((k8, l8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k8);
            If.create();
            if (this.operationType === OperationType.LOADING) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.LoadingProcessStyle.bind(this)(f8 ? f8 : this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!l8) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
    }
    IconSecondaryTitleStyle(l7, m7 = null) {
        this.observeComponentCreation((c8, d8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(c8);
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Flex.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
            if (!d8) {
                Flex.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((s7, t7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s7);
            If.create();
            if (Util.isSymbolResource(l7.iconOptions?.icon)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((a8, b8) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(a8);
                        SymbolGlyph.create(l7.iconOptions?.icon);
                        SymbolGlyph.fontSize(l7.iconOptions?.symbolicIconOption?.fontSize ?
                        Util.symbolFontSize(l7.iconOptions?.symbolicIconOption?.fontSize) : LEFT_ICON_SIZE);
                        SymbolGlyph.fontColor(l7.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.leftIconColor]);
                        SymbolGlyph.fontWeight(l7.iconOptions?.symbolicIconOption?.fontWeight);
                        SymbolGlyph.renderingStrategy(l7.iconOptions?.symbolicIconOption?.renderingStrategy);
                        SymbolGlyph.effectStrategy(l7.iconOptions?.symbolicIconOption?.effectStrategy);
                        SymbolGlyph.margin({ end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) });
                        SymbolGlyph.flexShrink(0);
                        if (!b8) {
                            SymbolGlyph.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((w7, x7) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(w7);
                        Image.create(l7.iconOptions?.icon);
                        Image.fillColor(this.subHeaderTheme.leftIconColor);
                        Image.width(LEFT_ICON_SIZE);
                        Image.height(LEFT_ICON_SIZE);
                        Image.margin({ end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }) });
                        Image.draggable(false);
                        Image.flexShrink(0);
                        if (!x7) {
                            Image.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            if (!t7) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((q7, r7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q7);
            Text.create(l7.content);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
            Text.flexShrink(1);
            if (!r7) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        Flex.pop();
    }
    SubTitleStyle(z6, a7 = null) {
        this.observeComponentCreation((i7, j7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i7);
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
            if (!j7) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((g7, h7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(g7);
            Text.create(z6.content);
            __Text__primaryTitleStyles({
                fontWeight: FontWeight.Bold,
                maxLines: SINGLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
            Text.width('100%');
            if (!h7) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        this.observeComponentCreation((e7, f7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e7);
            Text.create(z6.subContent);
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
            if (!f7) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        Column.pop();
    }
    SecondTitleStyle(q6, r6 = null) {
        this.observeComponentCreation((x6, y6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(x6);
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            if (!y6) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((u6, v6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u6);
            Text.create(q6.content);
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
            if (!v6) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        Column.pop();
    }
    SelectStyle(e6, f6 = null) {
        this.observeComponentCreation((n6, o6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n6);
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.onAppear(() => {
                this.changeFlexAlign(FlexAlign.SpaceBetween);
            });
            if (!o6) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((i6, j6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i6);
            Select.create(e6.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
            Select.value(ObservedObject.GetRawObject(this.selectValue));
            Select.onSelect((l6, m6) => {
                this.selectedIndex = l6;
                if (m6) {
                    this.selectValue = m6;
                }
                if (e6.onSelect) {
                    e6.onSelect(l6, m6);
                }
            });
            Select.font({
                size: { 'id': -1, 'type': 10002, params: ['sys.float.Body_L'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                weight: FontWeight.Medium,
            });
            if (!j6) {
                Select.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Select.pop();
        Column.pop();
    }
    PrimaryTitleStyle(v5, w5 = null) {
        this.observeComponentCreation((c6, d6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(c6);
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                top: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            if (!d6) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((z5, a6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(z5);
            Text.create(v5.content);
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
            if (!a6) {
                Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Text.pop();
        Column.pop();
    }
    ButtonStyle(a5, b5 = null) {
        this.observeComponentCreation((t5, u5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t5);
            Row.create();
            Row.margin({
                start: LengthMetrics.resource(this.ageing ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Row.justifyContent(FlexAlign.End);
            if (!u5) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((r5, s5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(r5);
            Stack.create();
            Stack.focusable(true);
            if (!s5) {
                Stack.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((f5, g5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f5);
            If.create();
            if (a5) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((n5, o5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(n5);
                        Row.create();
                        Row.padding({
                            start: LengthMetrics.resource(this.ageing ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
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
                        Row.constraintSize({ minHeight: BUTTON_HEIGHT });
                        Row.justifyContent(FlexAlign.End);
                        Row.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
                        Row.onHover((q5) => {
                            if (q5) {
                                this.buttonBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                            }
                            else {
                                this.buttonBgColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
                            }
                        });
                        if (!o5) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((l5, m5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(l5);
                        Text.create(a5.value);
                        __Text__secondaryTitleStyles({
                            fontWeight: FontWeight.Medium,
                            maxLines: DOUBLE_LINE_NUM,
                            fontColor: this.subHeaderTheme.fontButtonColor,
                        });
                        Text.focusable(true);
                        if (!m5) {
                            Text.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Text.pop();
                    Row.pop();
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
            Row.constraintSize({ minHeight: BUTTON_ZONE_SIZE });
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
            Row.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.outline_extra_larger'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: { 'id': -1, 'type': 10001, params: ['sys.color.interactive_focus'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
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
            Image.height(ARROW_ICON_HEIGHT);
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
                                                    }, undefined, m3, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 750, col: 13 });
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
            LoadingProgress.width(LOADING_SIZE);
            LoadingProgress.height(LOADING_SIZE);
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
                        Row.margin({
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.justifyContent(FlexAlign.Center);
                        Row.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Row.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
                        ViewStackProcessor.visualState('normal');
                        Row.border({ width: 0 });
                        Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_sub_background_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        ViewStackProcessor.visualState('focused');
                        Row.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: BORDER_WIDTH,
                            color: this.subHeaderTheme.borderFocusColor,
                            style: BorderStyle.Solid,
                        });
                        ViewStackProcessor.visualState('pressed');
                        Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.interactive_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        ViewStackProcessor.visualState('disabled');
                        Row.opacity({ 'id': -1, 'type': 10002, params: ['sys.float.interactive_disable'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        ViewStackProcessor.visualState();
                        Row.onTouch((p1) => {
                            if (p1.type === TouchType.Down) {
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
            return resourceManager.getSystemResourceManager().getNumberByName(d);
        }
        catch (e) {
            let f = e.code;
            let g = e.message;
            hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${f}, message: ${g}`);
            return Util.DEFAULT_VALUE;
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
Util.CALCULATE_BREAKPOINT_S = _a.getNumberByResource('breakpoint_horizontal_s');
Util.CALCULATE_BREAKPOINT_M = _a.getNumberByResource('breakpoint_horizontal_m');
Util.BREAKPOINT_S = _a.CALCULATE_BREAKPOINT_S === _a.DEFAULT_VALUE ? _a.DEFAULT_BREAKPOINT_S : _a.CALCULATE_BREAKPOINT_S;
Util.BREAKPOINT_M = _a.CALCULATE_BREAKPOINT_M === _a.DEFAULT_VALUE ? _a.DEFAULT_BREAKPOINT_M : _a.CALCULATE_BREAKPOINT_M;

export default { OperationType, SubHeader };