/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const hilog = requireNapi('hilog');
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const resourceManager = requireNapi('resourceManager');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
export var EditableLeftIconType;
(function (l10) {
    l10[l10['Back'] = 0] = 'Back';
    l10[l10['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (k10) {
    k10[k10['Image'] = 0] = 'Image';
    k10[k10['Icon'] = 1] = 'Icon';
    k10[k10['LeftIcon'] = 2] = 'LeftIcon';
})(ItemType || (ItemType = {}));
const PUBLIC_CANCEL = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_cancel'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_OK = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_ok'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_BACK = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_compnent_titlebar_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const DEFAULT_TITLE_BAR_HEIGHT = 56;
const DEFAULT_TITLE_PADDING = 2;
const MAX_LINE_ONE = 1;
const MAX_LINES_TWO = 2;
const MAX_MAIN_TITLE_PERCENT = 0.65;
const MAX_SUB_TITLE_PERCENT = 0.35;
const DEFAULT_BREAKPOINT_S = 600;
const DEFAULT_BREAKPOINT_M = 840;
const MIN_SUBTITLE_SIZE = '10.0vp';
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const TITLE_VP = 20;
const SUBTITLE_VP = 14;
const TITLE_F = getNumberByResource('titlebar_title_tertiary_size');
const SUBTITLE_F = getNumberByResource('titlebar_subheader_size');
const TITLE_F_VP = (TITLE_F > 0 ? TITLE_F : TITLE_VP) + 'vp';
const SUBTITLE_F_VP = (SUBTITLE_F > 0 ? SUBTITLE_F : SUBTITLE_VP) + 'vp';
class EditableTitleBarTheme {
    constructor() {
        this.iconColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.iconBackgroundColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.iconBackgroundPressedColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_pressed_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.iconBackgroundHoverColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_hover_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.iconBackgroundFocusOutlineColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_focus_outline_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.titleColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_title_tertiary_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.subTitleColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_subheader_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
}
export class EditableTitleBar extends ViewPU {
    constructor(e10, f10, g10, h10 = -1, i10 = undefined, j10) {
        super(e10, g10, h10, j10);
        if (typeof i10 === 'function') {
            this.paramsGenerator_ = i10;
        }
        this.leftIconStyle = EditableLeftIconType.Back;
        this.title = '';
        this.subtitle = '';
        this.isSaveIconRequired = true;
        this.imageItem = undefined;
        this.menuItems = undefined;
        this.options = {
            safeAreaTypes: [SafeAreaType.SYSTEM],
            safeAreaEdges: [SafeAreaEdge.TOP],
        };
        this.onSave = undefined;
        this.onCancel = undefined;
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(f10.contentMargin, this, 'contentMargin');
        this.__titleBarMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.vp(0),
            end: LengthMetrics.vp(0),
        }, this, 'titleBarMargin');
        this.__backActive = new ObservedPropertySimplePU(false, this, 'backActive');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.constraintWidth = 0;
        this.__editableTitleBarTheme = new ObservedPropertyObjectPU(new EditableTitleBarTheme(), this, 'editableTitleBarTheme');
        this.addProvidedVar('editableTitleBarTheme', this.__editableTitleBarTheme, false);
        this.setInitiallyProvidedValue(f10);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(d10) {
        if (d10.leftIconStyle !== undefined) {
            this.leftIconStyle = d10.leftIconStyle;
        }
        if (d10.title !== undefined) {
            this.title = d10.title;
        }
        if (d10.subtitle !== undefined) {
            this.subtitle = d10.subtitle;
        }
        if (d10.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = d10.isSaveIconRequired;
        }
        if (d10.imageItem !== undefined) {
            this.imageItem = d10.imageItem;
        }
        if (d10.menuItems !== undefined) {
            this.menuItems = d10.menuItems;
        }
        if (d10.options !== undefined) {
            this.options = d10.options;
        }
        if (d10.onSave !== undefined) {
            this.onSave = d10.onSave;
        }
        if (d10.onCancel !== undefined) {
            this.onCancel = d10.onCancel;
        }
        if (d10.titleBarMargin !== undefined) {
            this.titleBarMargin = d10.titleBarMargin;
        }
        if (d10.backActive !== undefined) {
            this.backActive = d10.backActive;
        }
        if (d10.fontSize !== undefined) {
            this.fontSize = d10.fontSize;
        }
        if (d10.constraintWidth !== undefined) {
            this.constraintWidth = d10.constraintWidth;
        }
        if (d10.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = d10.editableTitleBarTheme;
        }
    }
    updateStateVars(c10) {
        this.__contentMargin.reset(c10.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(b10) {
        this.__contentMargin.purgeDependencyOnElmtId(b10);
        this.__titleBarMargin.purgeDependencyOnElmtId(b10);
        this.__backActive.purgeDependencyOnElmtId(b10);
        this.__fontSize.purgeDependencyOnElmtId(b10);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(b10);
    }
    aboutToBeDeleted() {
        this.__contentMargin.aboutToBeDeleted();
        this.__titleBarMargin.aboutToBeDeleted();
        this.__backActive.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__editableTitleBarTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(a10) {
        this.__contentMargin.set(a10);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(z9) {
        this.__titleBarMargin.set(z9);
    }
    get backActive() {
        return this.__backActive.get();
    }
    set backActive(y9) {
        this.__backActive.set(y9);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(x9) {
        this.__fontSize.set(x9);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(w9) {
        this.__editableTitleBarTheme.set(w9);
    }
    onWillApplyTheme(v9) {
        this.editableTitleBarTheme.iconColor = v9.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = v9.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = v9.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundColor = v9.colors.compBackgroundTertiary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = v9.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = v9.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = v9.colors.interactiveFocus;
    }
    initialRender() {
        this.observeComponentCreation2((t9, u9) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes, this.options.safeAreaEdges);
        }, Flex);
        this.observeComponentCreation2((r9, s9) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((p9, q9) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)(this);
        Row.pop();
        this.observeComponentCreation2((i9, j9) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n9, o9) => {
                        Row.create();
                        Row.flexShrink(0);
                    }, Row);
                    this.imageItemLayout.bind(this)(this);
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((g9, h9) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)(this);
        Row.pop();
        this.observeComponentCreation2((e9, f9) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)(this);
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    leftIconLayout(b8 = null) {
        this.observeComponentCreation2((d8, e8) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w8, x8) => {
                        Navigator.create();
                        Navigator.active(this.backActive);
                    }, Navigator);
                    Navigator.pop();
                    {
                        this.observeComponentCreation2((q8, r8) => {
                            if (r8) {
                                let s8 = new ImageMenuItem(typeof PUV2ViewBase !== 'undefined' && b8 instanceof PUV2ViewBase ? b8 : this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                }, undefined, q8, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 197, col: 7 });
                                ViewPU.create(s8);
                                let t8 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon
                                    };
                                };
                                s8.paramsGenerator_ = t8;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(q8, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((h8, i8) => {
                            if (i8) {
                                let j8 = new ImageMenuItem(typeof PUV2ViewBase !== 'undefined' && b8 instanceof PUV2ViewBase ? b8 : this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                }, undefined, h8, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 207, col: 7 });
                                ViewPU.create(j8);
                                let k8 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_CANCEL,
                                            isEnabled: true,
                                            action: () => this.onCancel && this.onCancel(),
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon
                                    };
                                };
                                j8.paramsGenerator_ = k8;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(h8, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
        }, If);
        If.pop();
    }
    imageItemLayout(t7 = null) {
        {
            this.observeComponentCreation2((v7, w7) => {
                if (w7) {
                    let x7 = new ImageMenuItem(typeof PUV2ViewBase !== 'undefined' && t7 instanceof PUV2ViewBase ? t7 : this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, v7, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 221, col: 5 });
                    ViewPU.create(x7);
                    let y7 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    x7.paramsGenerator_ = y7;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(v7, {});
                }
            }, { name: 'ImageMenuItem' });
        }
    }
    titleLayout(y6 = null) {
        this.observeComponentCreation2((r7, s7) => {
            Column.create();
            Column.height(EditableTitleBar.totalHeight);
            Column.justifyContent(FlexAlign.Center);
            Column.margin({
                start: LengthMetrics.vp(EditableTitleBar.titlePadding),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((p7, q7) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((n7, o7) => {
            Text.create(this.title);
            Text.maxFontSize(TITLE_F_VP);
            Text.minFontSize(SUBTITLE_F_VP);
            Text.fontColor(this.editableTitleBarTheme.titleColor);
            Text.maxLines(this.subtitle ? MAX_LINE_ONE : MAX_LINES_TWO);
            Text.fontWeight(FontWeight.Bold);
            Text.textAlign(TextAlign.Start);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.heightAdaptivePolicy(this.subtitle ?
                TextHeightAdaptivePolicy.MAX_LINES_FIRST : TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
            Text.constraintSize({
                maxHeight: this.subtitle ? EditableTitleBar.maxMainTitleHeight : EditableTitleBar.totalHeight,
            });
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((d7, e7) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l7, m7) => {
                        Row.create();
                        Row.margin({
                            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((j7, k7) => {
                        Text.create(this.subtitle);
                        Text.maxFontSize(SUBTITLE_F_VP);
                        Text.minFontSize(MIN_SUBTITLE_SIZE);
                        Text.fontColor(this.editableTitleBarTheme.subTitleColor);
                        Text.maxLines(MAX_LINE_ONE);
                        Text.fontWeight(FontWeight.Regular);
                        Text.textAlign(TextAlign.Start);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST);
                        Text.constraintSize({
                            maxHeight: this.title ? EditableTitleBar.maxSubTitleHeight : EditableTitleBar.totalHeight,
                        });
                    }, Text);
                    Text.pop();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }
    rightMenuItemsLayout(q6 = null) {
        {
            this.observeComponentCreation2((s6, t6) => {
                if (t6) {
                    let u6 = new EditableTitleBarMenuSection(typeof PUV2ViewBase !== 'undefined' && q6 instanceof PUV2ViewBase ? q6 : this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                    }, undefined, s6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 278, col: 5 });
                    ViewPU.create(u6);
                    let v6 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize
                        };
                    };
                    u6.paramsGenerator_ = v6;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(s6, {
                        fontSize: this.fontSize
                    });
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }
    onMeasureSize(k6, l6, m6) {
        let n6 = { width: k6.width, height: k6.height };
        l6.forEach((p6) => {
            if (Math.abs(this.constraintWidth - Number(m6.maxWidth)) > Number.EPSILON) {
                if (!this.contentMargin) {
                    this.constraintWidth = Number(m6.maxWidth);
                    if (this.constraintWidth < EditableTitleBar.breakpointS) {
                        this.titleBarMargin = {
                            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                        };
                    }
                    else if (this.constraintWidth >= EditableTitleBar.breakpointM) {
                        this.titleBarMargin = {
                            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_level3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_level3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                        };
                    }
                    else {
                        this.titleBarMargin = {
                            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                        };
                    }
                }
            }
            n6.height = p6.measure(m6).height;
            n6.width = Number(m6.maxWidth);
        });
        return n6;
    }
    onPlaceChildren(f6, g6, h6) {
        g6.forEach((j6) => {
            j6.layout({ x: 0, y: 0 });
        });
    }
    rerender() {
        this.updateDirtyElements();
    }
}
EditableTitleBar.maxCountOfExtraItems = 3;
EditableTitleBar.maxOtherCountOfExtraItems = 2;
EditableTitleBar.commonZero = 0;
EditableTitleBar.noneColor = '#00000000';
EditableTitleBar.defaultHeight = getNumberByResource('titlebar_default_height');
EditableTitleBar.defaultMarginLevel1 = getNumberByResource('margin_level1');
EditableTitleBar.defaultMarginLevel2 = getNumberByResource('margin_level2');
EditableTitleBar.defaultMarginLevel3 = getNumberByResource('margin_level3');
EditableTitleBar.defaultTitlePadding = getNumberByResource('titlebar_icon_background_space_horizontal');
EditableTitleBar.defaultBreakpointS = getNumberByResource('breakpoint_horizontal_s');
EditableTitleBar.defaultBreakpointM = getNumberByResource('breakpoint_horizontal_m');
EditableTitleBar.totalHeight = EditableTitleBar.defaultHeight === EditableTitleBar.commonZero ? DEFAULT_TITLE_BAR_HEIGHT :
    EditableTitleBar.defaultHeight;
EditableTitleBar.titlePadding = EditableTitleBar.defaultTitlePadding === EditableTitleBar.commonZero ?
    DEFAULT_TITLE_PADDING : EditableTitleBar.defaultTitlePadding;
EditableTitleBar.maxMainTitleHeight = (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_MAIN_TITLE_PERCENT;
EditableTitleBar.maxSubTitleHeight = (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_SUB_TITLE_PERCENT;
EditableTitleBar.breakpointS = EditableTitleBar.defaultBreakpointS === EditableTitleBar.commonZero ? DEFAULT_BREAKPOINT_S :
    EditableTitleBar.defaultBreakpointS;
EditableTitleBar.breakpointM = EditableTitleBar.defaultBreakpointM === EditableTitleBar.commonZero ? DEFAULT_BREAKPOINT_M :
    EditableTitleBar.defaultBreakpointM;
class EditableTitleBarMenuSection extends ViewPU {
    constructor(z5, a6, b6, c6 = -1, d6 = undefined, e6) {
        super(z5, b6, c6, e6);
        if (typeof d6 === 'function') {
            this.paramsGenerator_ = d6;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(a6.fontSize, this, 'fontSize');
        this.setInitiallyProvidedValue(a6);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(y5) {
        if (y5.menuItems !== undefined) {
            this.menuItems = y5.menuItems;
        }
        if (y5.onSave !== undefined) {
            this.onSave = y5.onSave;
        }
        if (y5.isSaveEnabled !== undefined) {
            this.isSaveEnabled = y5.isSaveEnabled;
        }
        if (y5.fontSize === undefined) {
            this.__fontSize.set(1);
        }
    }
    updateStateVars(x5) {
        this.__fontSize.reset(x5.fontSize);
    }
    purgeVariableDependenciesOnElmtId(w5) {
        this.__fontSize.purgeDependencyOnElmtId(w5);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(v5) {
        this.__fontSize.set(v5);
    }
    initialRender() {
        this.observeComponentCreation2((t5, u5) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((r5, s5) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((z4, a5) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e5, f5) => {
                        ForEach.create();
                        const g5 = i5 => {
                            const j5 = i5;
                            {
                                this.observeComponentCreation2((l5, m5) => {
                                    if (m5) {
                                        let n5 = new ImageMenuItem(this, {
                                            item: j5,
                                            attribute: ItemType.Icon,
                                            fontSize: this.fontSize,
                                        }, undefined, l5, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 338, col: 15 });
                                        ViewPU.create(n5);
                                        let o5 = () => {
                                            return {
                                                item: j5,
                                                attribute: ItemType.Icon,
                                                fontSize: this.fontSize
                                            };
                                        };
                                        n5.paramsGenerator_ = o5;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(l5, {
                                            fontSize: this.fontSize
                                        });
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(e5, this.menuItems.slice(EditableTitleBar.commonZero, this.isSaveEnabled ?
                            EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems), g5);
                    }, ForEach);
                    ForEach.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((o4, p4) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((t4, u4) => {
                            if (u4) {
                                let v4 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                }, undefined, t4, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 346, col: 11 });
                                ViewPU.create(v4);
                                let w4 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_OK,
                                            isEnabled: true,
                                            action: () => this.onSave && this.onSave(),
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.Icon
                                    };
                                };
                                v4.paramsGenerator_ = w4;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(t4, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class ImageMenuItem extends ViewPU {
    constructor(a4, b4, c4, d4 = -1, e4 = undefined, f4) {
        super(a4, c4, d4, f4);
        if (typeof e4 === 'function') {
            this.paramsGenerator_ = e4;
        }
        this.item = {
            value: '',
            isEnabled: true,
            label: '',
        };
        this.attribute = ItemType.Image;
        this.callbackId = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.2;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(b4.fontSize, this, 'fontSize');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__editableTitleBarTheme = this.initializeConsume('editableTitleBarTheme', 'editableTitleBarTheme');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let g4 = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 379, col: 14 });
                g4.setController(this.dialogController);
                ViewPU.create(g4);
                let h4 = () => {
                    return {
                        cancel: () => {
                        },
                        confirm: () => {
                        },
                        itemEditableDialog: this.item,
                        textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                        fontSize: this.fontSize
                    };
                };
                g4.paramsGenerator_ = h4;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.setInitiallyProvidedValue(b4);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z3) {
        if (z3.item !== undefined) {
            this.item = z3.item;
        }
        if (z3.attribute !== undefined) {
            this.attribute = z3.attribute;
        }
        if (z3.callbackId !== undefined) {
            this.callbackId = z3.callbackId;
        }
        if (z3.minFontSize !== undefined) {
            this.minFontSize = z3.minFontSize;
        }
        if (z3.maxFontSize !== undefined) {
            this.maxFontSize = z3.maxFontSize;
        }
        if (z3.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (z3.isOnFocus !== undefined) {
            this.isOnFocus = z3.isOnFocus;
        }
        if (z3.isOnHover !== undefined) {
            this.isOnHover = z3.isOnHover;
        }
        if (z3.isOnClick !== undefined) {
            this.isOnClick = z3.isOnClick;
        }
        if (z3.dialogController !== undefined) {
            this.dialogController = z3.dialogController;
        }
    }
    updateStateVars(y3) {
        this.__fontSize.reset(y3.fontSize);
    }
    purgeVariableDependenciesOnElmtId(x3) {
        this.__fontSize.purgeDependencyOnElmtId(x3);
        this.__isOnFocus.purgeDependencyOnElmtId(x3);
        this.__isOnHover.purgeDependencyOnElmtId(x3);
        this.__isOnClick.purgeDependencyOnElmtId(x3);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(x3);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        this.__isOnFocus.aboutToBeDeleted();
        this.__isOnHover.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        this.__editableTitleBarTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(w3) {
        this.__fontSize.set(w3);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(v3) {
        this.__isOnFocus.set(v3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(u3) {
        this.__isOnHover.set(u3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(t3) {
        this.__isOnClick.set(t3);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(s3) {
        this.__editableTitleBarTheme.set(s3);
    }
    textDialog() {
        if (this.item.value === PUBLIC_OK) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.icon_save'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.item.value === PUBLIC_CANCEL) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.icon_cancel'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.item.value === PUBLIC_BACK) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.icon_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else {
            return this.item.label ? this.item.label : '';
        }
    }
    keyEventAction(r3) {
        if (!this.item.isEnabled) {
            return;
        }
        if (r3.keyCode !== KeyCode.KEYCODE_ENTER && r3.keyCode !== KeyCode.KEYCODE_SPACE) {
            return;
        }
        if (r3.type === KeyType.Down) {
            this.isOnClick = true;
        }
        if (r3.type === KeyType.Up) {
            this.isOnClick = false;
        }
    }
    touchEventAction(q3) {
        if (!this.item.isEnabled) {
            return;
        }
        if (q3.type === TouchType.Down) {
            this.isOnClick = true;
        }
        if (q3.type === TouchType.Up) {
            if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close();
            }
            this.isOnClick = false;
        }
    }
    getFgColor() {
        if (this.isOnClick) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_pressed_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.isOnHover) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_hover_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else {
            return EditableTitleBar.noneColor;
        }
    }
    getBgColor() {
        if (this.isOnClick) {
            return this.editableTitleBarTheme.iconBackgroundPressedColor;
        }
        else if (this.isOnHover) {
            return this.editableTitleBarTheme.iconBackgroundHoverColor;
        }
        else {
            return this.editableTitleBarTheme.iconBackgroundColor;
        }
    }
    IconBuilder(w2 = null) {
        this.observeComponentCreation2((b3, c3) => {
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            Button.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.margin({
                start: this.attribute === ItemType.LeftIcon ? LengthMetrics.vp(EditableTitleBar.commonZero) :
                    LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(this.getBgColor());
            ViewStackProcessor.visualState('focused');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_focus_outline_weight'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: this.editableTitleBarTheme.iconBackgroundFocusOutlineColor,
                style: BorderStyle.Solid,
            });
            ViewStackProcessor.visualState('normal');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('pressed');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState();
            Button.onFocus(() => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnFocus = true;
            });
            Button.onBlur(() => this.isOnFocus = false);
            Button.onHover((p3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = p3;
            });
            Button.onKeyEvent((o3) => {
                this.keyEventAction(o3);
            });
            Button.onTouch((n3) => {
                this.touchEventAction(n3);
            });
            Gesture.create(GesturePriority.Low);
            GestureGroup.create(GestureMode.Exclusive);
            LongPressGesture.create({ repeat: false, duration: 500 });
            LongPressGesture.onAction((l3) => {
                let m3 = this.getUIContext().getHostContext();
                this.fontSize = m3.config?.fontSizeScale ?? 1;
                if (l3) {
                    if (this.fontSize >= this.minFontSize) {
                        this.dialogController?.open();
                    }
                }
            });
            LongPressGesture.pop();
            TapGesture.create();
            TapGesture.onAction((k3) => {
                this.item.isEnabled && this.item.action && this.item.action();
            });
            TapGesture.pop();
            GestureGroup.pop();
            Gesture.pop();
        }, Button);
        this.observeComponentCreation2((z2, a3) => {
            Image.create(this.item.value);
            Image.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.fillColor(this.editableTitleBarTheme.iconColor);
            Image.focusable(this.item.isEnabled);
            Image.enabled(this.item.isEnabled);
            Image.matchTextDirection(this.item.value === PUBLIC_BACK ? true : false);
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    ImageBuilder(z1 = null) {
        this.observeComponentCreation2((u2, v2) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Stack);
        this.observeComponentCreation2((s2, t2) => {
            Image.create(this.item.value);
            Image.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.focusable(false);
            Image.enabled(this.item.isEnabled);
            Image.objectFit(ImageFit.Cover);
        }, Image);
        this.observeComponentCreation2((d2, e2) => {
            Button.createWithLabel({ type: ButtonType.Circle });
            Button.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(EditableTitleBar.noneColor);
            ViewStackProcessor.visualState('pressed');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('normal');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('focused');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_focus_outline_weight'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: this.editableTitleBarTheme.iconBackgroundFocusOutlineColor,
                style: BorderStyle.Solid,
            });
            ViewStackProcessor.visualState();
            Button.onFocus(() => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnFocus = true;
            });
            Button.onBlur(() => this.isOnFocus = false);
            Button.onHover((r2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = r2;
            });
            Button.onKeyEvent((q2) => {
                this.keyEventAction(q2);
            });
            Button.onTouch((p2) => {
                this.touchEventAction(p2);
            });
            Gesture.create(GesturePriority.Low);
            GestureGroup.create(GestureMode.Exclusive);
            LongPressGesture.create({ repeat: false, duration: 500 });
            LongPressGesture.onAction((n2) => {
                let o2 = this.getUIContext().getHostContext();
                this.fontSize = o2.config?.fontSizeScale ?? 1;
                if (n2) {
                    if (this.fontSize >= this.minFontSize) {
                        this.dialogController?.open();
                    }
                }
            });
            LongPressGesture.pop();
            TapGesture.create();
            TapGesture.onAction((m2) => {
                this.item.isEnabled && this.item.action && this.item.action();
            });
            TapGesture.pop();
            GestureGroup.pop();
            Gesture.pop();
        }, Button);
        Button.pop();
        Stack.pop();
    }
    initialRender() {
        this.observeComponentCreation2((v1, w1) => {
            If.create();
            if (this.attribute === ItemType.Icon || this.attribute === ItemType.LeftIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconBuilder.bind(this)(this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.ImageBuilder.bind(this)(this);
                });
            }
        }, If);
        If.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class EditableTitleBarDialog extends ViewPU {
    constructor(m1, n1, o1, p1 = -1, q1 = undefined, r1) {
        super(m1, o1, p1, r1);
        if (typeof q1 === 'function') {
            this.paramsGenerator_ = q1;
        }
        this.itemEditableDialog = {
            value: '',
            isEnabled: true,
        };
        this.callbackId = undefined;
        this.textEditableTitleBarDialog = '';
        this.mainWindowStage = undefined;
        this.controller = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.2;
        this.__mainWindow = this.createStorageLink('mainWindow', undefined, 'mainWindow');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(n1.fontSize, this, 'fontSize');
        this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
        this.cancel = () => {
        };
        this.confirm = () => {
        };
        this.setInitiallyProvidedValue(n1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l1) {
        if (l1.itemEditableDialog !== undefined) {
            this.itemEditableDialog = l1.itemEditableDialog;
        }
        if (l1.callbackId !== undefined) {
            this.callbackId = l1.callbackId;
        }
        if (l1.textEditableTitleBarDialog !== undefined) {
            this.textEditableTitleBarDialog = l1.textEditableTitleBarDialog;
        }
        if (l1.mainWindowStage !== undefined) {
            this.mainWindowStage = l1.mainWindowStage;
        }
        if (l1.controller !== undefined) {
            this.controller = l1.controller;
        }
        if (l1.minFontSize !== undefined) {
            this.minFontSize = l1.minFontSize;
        }
        if (l1.maxFontSize !== undefined) {
            this.maxFontSize = l1.maxFontSize;
        }
        if (l1.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (l1.maxLines !== undefined) {
            this.maxLines = l1.maxLines;
        }
        if (l1.cancel !== undefined) {
            this.cancel = l1.cancel;
        }
        if (l1.confirm !== undefined) {
            this.confirm = l1.confirm;
        }
    }
    updateStateVars(k1) {
        this.__fontSize.reset(k1.fontSize);
    }
    purgeVariableDependenciesOnElmtId(j1) {
        this.__mainWindow.purgeDependencyOnElmtId(j1);
        this.__fontSize.purgeDependencyOnElmtId(j1);
        this.__maxLines.purgeDependencyOnElmtId(j1);
        this.__windowStandardHeight.purgeDependencyOnElmtId(j1);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(i1) {
        this.controller = i1;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(h1) {
        this.__mainWindow.set(h1);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(g1) {
        this.__fontSize.set(g1);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(f1) {
        this.__maxLines.set(f1);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(e1) {
        this.__windowStandardHeight.set(e1);
    }
    initialRender() {
        this.observeComponentCreation2((i, j) => {
            If.create();
            if (this.textEditableTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c1, d1) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }));
                    }, Column);
                    this.observeComponentCreation2((a1, b1) => {
                        Image.create(this.itemEditableDialog.value);
                        Image.width(IMAGE_SIZE);
                        Image.height(IMAGE_SIZE);
                        Image.margin({
                            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Image);
                    this.observeComponentCreation2((y, z) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                    }, Column);
                    this.observeComponentCreation2((w, x) => {
                        Text.create(this.textEditableTitleBarDialog);
                        Text.fontSize(TEXT_EDITABLE_DIALOG);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(this.maxLines);
                        Text.width('100%');
                        Text.textAlign(TextAlign.Center);
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Text);
                    Text.pop();
                    Column.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((p, q) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }));
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((n, o) => {
                        Image.create(this.itemEditableDialog.value);
                        Image.width(IMAGE_SIZE);
                        Image.height(IMAGE_SIZE);
                        Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Image);
                    Column.pop();
                });
            }
        }, If);
        If.pop();
    }
    async aboutToAppear() {
        let e = this.getUIContext().getHostContext();
        this.mainWindowStage = e.windowStage.getMainWindowSync();
        let f = this.mainWindowStage.getWindowProperties();
        let g = f.windowRect;
        if (px2vp(g.height) > 640) {
            this.maxLines = 6;
        }
        else {
            this.maxLines = 1;
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
function getNumberByResource(a) {
    try {
        return resourceManager.getSystemResourceManager().getNumberByName(a);
    }
    catch (b) {
        let c = b.code;
        let d = b.message;
        hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${c},message:${d}`);
        return EditableTitleBar.commonZero;
    }
}

export default {
    EditableLeftIconType: EditableLeftIconType,
    EditableTitleBar: EditableTitleBar,
};