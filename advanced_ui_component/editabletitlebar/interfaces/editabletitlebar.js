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

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
const hilog = requireNapi('hilog');
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const resourceManager = requireNapi('resourceManager');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
export var EditableLeftIconType;
(function (x10) {
    x10[x10['Back'] = 0] = 'Back';
    x10[x10['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (w10) {
    w10[w10['Image'] = 0] = 'Image';
    w10[w10['Icon'] = 1] = 'Icon';
    w10[w10['LeftIcon'] = 2] = 'LeftIcon';
})(ItemType || (ItemType = {}));
const PUBLIC_CANCEL = { 'id': -1, 'type': 40000, params: ['sys.symbol.xmark'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_OK = { 'id': -1, 'type': 40000, params: ['sys.symbol.checkmark'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_BACK = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_backward'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const DEFAULT_TITLE_BAR_HEIGHT = 56;
const DEFAULT_TITLE_PADDING = 2;
const MAX_LINE_ONE = 1;
const MAX_LINES_TWO = 2;
const MAX_MAIN_TITLE_PERCENT = 0.65;
const MAX_SUB_TITLE_PERCENT = 0.35;
const MIN_SUBTITLE_SIZE = '10.0vp';
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const SYMBOL_SIZE = '24vp';
const SYMBOL_TITLE_SIZE = '64vp';
const TITLE_VP = 20;
const SUBTITLE_VP = 14;
const TITLE_F = getNumberByResource(125831095, TITLE_VP);
const SUBTITLE_F = getNumberByResource(125831097, SUBTITLE_VP);
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
class ButtonGestureModifier {
    constructor(v10) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = v10;
    }
    applyGesture(s10) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            s10.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                if (s10) {
                    this.controller?.open();
                }
            })
                .onActionEnd(() => {
                this.controller?.close();
            }));
        }
        else {
            s10.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class EditableTitleBar extends ViewPU {
    constructor(m10, n10, o10, p10 = -1, q10 = undefined, r10) {
        super(m10, o10, p10, r10);
        if (typeof q10 === 'function') {
            this.paramsGenerator_ = q10;
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
        this.constraintWidth = 0;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.__editableTitleBarTheme = new ObservedPropertyObjectPU(new EditableTitleBarTheme(), this, 'editableTitleBarTheme');
        this.addProvidedVar('editableTitleBarTheme', this.__editableTitleBarTheme, false);
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(n10.contentMargin, this, 'contentMargin');
        this.__titleBarMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
        }, this, 'titleBarMargin');
        this.__backActive = new ObservedPropertySimplePU(false, this, 'backActive');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(n10);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l10) {
        if (l10.leftIconStyle !== undefined) {
            this.leftIconStyle = l10.leftIconStyle;
        }
        if (l10.title !== undefined) {
            this.title = l10.title;
        }
        if (l10.subtitle !== undefined) {
            this.subtitle = l10.subtitle;
        }
        if (l10.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = l10.isSaveIconRequired;
        }
        if (l10.imageItem !== undefined) {
            this.imageItem = l10.imageItem;
        }
        if (l10.menuItems !== undefined) {
            this.menuItems = l10.menuItems;
        }
        if (l10.options !== undefined) {
            this.options = l10.options;
        }
        if (l10.onSave !== undefined) {
            this.onSave = l10.onSave;
        }
        if (l10.onCancel !== undefined) {
            this.onCancel = l10.onCancel;
        }
        if (l10.constraintWidth !== undefined) {
            this.constraintWidth = l10.constraintWidth;
        }
        if (l10.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = l10.isFollowingSystemFontScale;
        }
        if (l10.maxFontScale !== undefined) {
            this.maxFontScale = l10.maxFontScale;
        }
        if (l10.systemFontScale !== undefined) {
            this.systemFontScale = l10.systemFontScale;
        }
        if (l10.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = l10.editableTitleBarTheme;
        }
        if (l10.titleBarMargin !== undefined) {
            this.titleBarMargin = l10.titleBarMargin;
        }
        if (l10.backActive !== undefined) {
            this.backActive = l10.backActive;
        }
        if (l10.fontSize !== undefined) {
            this.fontSize = l10.fontSize;
        }
    }
    updateStateVars(k10) {
        this.__contentMargin.reset(k10.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(j10) {
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(j10);
        this.__contentMargin.purgeDependencyOnElmtId(j10);
        this.__titleBarMargin.purgeDependencyOnElmtId(j10);
        this.__backActive.purgeDependencyOnElmtId(j10);
        this.__fontSize.purgeDependencyOnElmtId(j10);
    }
    aboutToBeDeleted() {
        this.__editableTitleBarTheme.aboutToBeDeleted();
        this.__contentMargin.aboutToBeDeleted();
        this.__titleBarMargin.aboutToBeDeleted();
        this.__backActive.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(i10) {
        this.__editableTitleBarTheme.set(i10);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(h10) {
        this.__contentMargin.set(h10);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(g10) {
        this.__titleBarMargin.set(g10);
    }
    get backActive() {
        return this.__backActive.get();
    }
    set backActive(f10) {
        this.__backActive.set(f10);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(e10) {
        this.__fontSize.set(e10);
    }
    onWillApplyTheme(d10) {
        this.editableTitleBarTheme.iconColor = d10.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = d10.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = d10.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = d10.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = d10.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = d10.colors.interactiveFocus;
    }
    aboutToAppear() {
        try {
            let c10 = this.getUIContext();
            this.isFollowingSystemFontScale = c10.isFollowingSystemFontScale();
            this.maxFontScale = c10.getMaxFontScale();
        }
        catch (z9) {
            let a10 = z9.code;
            let b10 = z9.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${a10}, message: ${b10}`);
        }
    }
    decideFontScale() {
        let y9 = this.getUIContext();
        this.systemFontScale = y9.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    initialRender() {
        this.observeComponentCreation2((w9, x9) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes, this.options.safeAreaEdges);
        }, Flex);
        this.observeComponentCreation2((u9, v9) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((s9, t9) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)(this);
        Row.pop();
        this.observeComponentCreation2((l9, m9) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q9, r9) => {
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
        this.observeComponentCreation2((j9, k9) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)(this);
        Row.pop();
        this.observeComponentCreation2((h9, i9) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)(this);
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    imageItemLayout(t8 = null) {
        {
            this.observeComponentCreation2((v8, w8) => {
                if (w8) {
                    let x8 = new ImageMenuItem(ViewPU.__proto__ !== NativeViewPartialUpdate && t8 instanceof PUV2ViewBase ? t8 : this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, v8, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 241, col: 5 });
                    ViewPU.create(x8);
                    let d7 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    x8.paramsGenerator_ = d7;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(v8, {});
                }
            }, { name: 'ImageMenuItem' });
        }
    }
    leftIconLayout(w7 = null) {
        this.observeComponentCreation2((y7, z7) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r8, s8) => {
                        Navigator.create();
                        Navigator.active(this.backActive);
                    }, Navigator);
                    Navigator.pop();
                    {
                        this.observeComponentCreation2((l8, m8) => {
                            if (m8) {
                                let n8 = new ImageMenuItem(ViewPU.__proto__ !== NativeViewPartialUpdate && w7 instanceof PUV2ViewBase ? w7 : this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    useSymbol: true,
                                }, undefined, l8, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 253, col: 7 });
                                ViewPU.create(n8);
                                let c7 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon,
                                        useSymbol: true
                                    };
                                };
                                n8.paramsGenerator_ = c7;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(l8, {
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
                        this.observeComponentCreation2((c8, d8) => {
                            if (d8) {
                                let e8 = new ImageMenuItem(ViewPU.__proto__ !== NativeViewPartialUpdate && w7 instanceof PUV2ViewBase ? w7 : this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    useSymbol: true,
                                }, undefined, c8, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 264, col: 7 });
                                ViewPU.create(e8);
                                let z6 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_CANCEL,
                                            isEnabled: true,
                                            action: () => this.onCancel && this.onCancel(),
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon,
                                        useSymbol: true
                                    };
                                };
                                e8.paramsGenerator_ = z6;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(c8, {
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
    titleLayout(b7 = null) {
        this.observeComponentCreation2((u7, v7) => {
            Column.create();
            Column.height(EditableTitleBar.totalHeight);
            Column.justifyContent(FlexAlign.Center);
            Column.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((s7, t7) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((q7, r7) => {
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
        this.observeComponentCreation2((g7, h7) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o7, p7) => {
                        Row.create();
                        Row.margin({
                            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((m7, n7) => {
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
    rightMenuItemsLayout(t6 = null) {
        {
            this.observeComponentCreation2((v6, w6) => {
                if (w6) {
                    let x6 = new EditableTitleBarMenuSection(ViewPU.__proto__ !== NativeViewPartialUpdate && t6 instanceof PUV2ViewBase ? t6 : this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                    }, undefined, v6, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 329, col: 5 });
                    ViewPU.create(x6);
                    let y6 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize
                        };
                    };
                    x6.paramsGenerator_ = y6;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(v6, {
                        fontSize: this.fontSize
                    });
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }
    onPlaceChildren(o6, p6, q6) {
        p6.forEach((s6) => {
            s6.layout({ x: 0, y: 0 });
        });
    }
    onMeasureSize(i6, j6, k6) {
        let l6 = { width: i6.width, height: i6.height };
        this.fontSize = this.decideFontScale();
        j6.forEach((n6) => {
            l6.height = n6.measure(k6).height;
            l6.width = Number(k6.maxWidth);
        });
        return l6;
    }
    rerender() {
        this.updateDirtyElements();
    }
}
EditableTitleBar.maxCountOfExtraItems = 3;
EditableTitleBar.maxOtherCountOfExtraItems = 2;
EditableTitleBar.commonZero = 0;
EditableTitleBar.noneColor = '#00000000';
EditableTitleBar.defaultHeight = getNumberByResource(125831115, DEFAULT_TITLE_BAR_HEIGHT);
EditableTitleBar.defaultTitlePadding = getNumberByResource(125830920, DEFAULT_TITLE_PADDING);
EditableTitleBar.totalHeight = EditableTitleBar.defaultHeight === EditableTitleBar.commonZero ? DEFAULT_TITLE_BAR_HEIGHT :
    EditableTitleBar.defaultHeight;
EditableTitleBar.titlePadding = EditableTitleBar.defaultTitlePadding === EditableTitleBar.commonZero ?
    DEFAULT_TITLE_PADDING : EditableTitleBar.defaultTitlePadding;
EditableTitleBar.maxMainTitleHeight = (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_MAIN_TITLE_PERCENT;
EditableTitleBar.maxSubTitleHeight = (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_SUB_TITLE_PERCENT;
class EditableTitleBarMenuSection extends ViewPU {
    constructor(c6, d6, e6, f6 = -1, g6 = undefined, h6) {
        super(c6, e6, f6, h6);
        if (typeof g6 === 'function') {
            this.paramsGenerator_ = g6;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(d6.fontSize, this, 'fontSize');
        this.setInitiallyProvidedValue(d6);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(b6) {
        if (b6.menuItems !== undefined) {
            this.menuItems = b6.menuItems;
        }
        if (b6.onSave !== undefined) {
            this.onSave = b6.onSave;
        }
        if (b6.isSaveEnabled !== undefined) {
            this.isSaveEnabled = b6.isSaveEnabled;
        }
        if (b6.fontSize === undefined) {
            this.__fontSize.set(1);
        }
    }
    updateStateVars(a6) {
        this.__fontSize.reset(a6.fontSize);
    }
    purgeVariableDependenciesOnElmtId(z5) {
        this.__fontSize.purgeDependencyOnElmtId(z5);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(y5) {
        this.__fontSize.set(y5);
    }
    initialRender() {
        this.observeComponentCreation2((w5, x5) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((u5, v5) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((c5, d5) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h5, i5) => {
                        ForEach.create();
                        const r5 = l5 => {
                            const m5 = l5;
                            {
                                this.observeComponentCreation2((o5, p5) => {
                                    if (p5) {
                                        let q5 = new ImageMenuItem(this, {
                                            item: m5,
                                            attribute: ItemType.Icon,
                                            fontSize: this.fontSize,
                                        }, undefined, o5, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 369, col: 15 });
                                        ViewPU.create(q5);
                                        let s5 = () => {
                                            return {
                                                item: m5,
                                                attribute: ItemType.Icon,
                                                fontSize: this.fontSize
                                            };
                                        };
                                        q5.paramsGenerator_ = s5;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(o5, {
                                            fontSize: this.fontSize
                                        });
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(h5, this.menuItems.slice(EditableTitleBar.commonZero, this.isSaveEnabled ?
                            EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems), r5);
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
        this.observeComponentCreation2((r4, s4) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((w4, x4) => {
                            if (x4) {
                                let y4 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                    useSymbol: true,
                                }, undefined, w4, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 377, col: 11 });
                                ViewPU.create(y4);
                                let j5 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_OK,
                                            isEnabled: true,
                                            action: () => this.onSave && this.onSave(),
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.Icon,
                                        useSymbol: true
                                    };
                                };
                                y4.paramsGenerator_ = j5;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(w4, {
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
    constructor(d4, e4, f4, g4 = -1, h4 = undefined, i4) {
        super(d4, f4, g4, i4);
        if (typeof h4 === 'function') {
            this.paramsGenerator_ = h4;
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
        this.longPressTime = 500;
        this.useSymbol = false;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(e4.fontSize, this, 'fontSize');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__editableTitleBarTheme = this.initializeConsume('editableTitleBarTheme', 'editableTitleBarTheme');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let j4 = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                    useSymbol: this.useSymbol,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 413, col: 14 });
                j4.setController(this.dialogController);
                ViewPU.create(j4);
                let a5 = () => {
                    return {
                        cancel: () => {
                        },
                        confirm: () => {
                        },
                        itemEditableDialog: this.item,
                        textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                        fontSize: this.fontSize,
                        useSymbol: this.useSymbol
                    };
                };
                j4.paramsGenerator_ = a5;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(e4);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(c4) {
        if (c4.item !== undefined) {
            this.item = c4.item;
        }
        if (c4.attribute !== undefined) {
            this.attribute = c4.attribute;
        }
        if (c4.callbackId !== undefined) {
            this.callbackId = c4.callbackId;
        }
        if (c4.minFontSize !== undefined) {
            this.minFontSize = c4.minFontSize;
        }
        if (c4.maxFontSize !== undefined) {
            this.maxFontSize = c4.maxFontSize;
        }
        if (c4.longPressTime !== undefined) {
            this.longPressTime = c4.longPressTime;
        }
        if (c4.useSymbol !== undefined) {
            this.useSymbol = c4.useSymbol;
        }
        if (c4.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (c4.isOnFocus !== undefined) {
            this.isOnFocus = c4.isOnFocus;
        }
        if (c4.isOnHover !== undefined) {
            this.isOnHover = c4.isOnHover;
        }
        if (c4.isOnClick !== undefined) {
            this.isOnClick = c4.isOnClick;
        }
        if (c4.dialogController !== undefined) {
            this.dialogController = c4.dialogController;
        }
        if (c4.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = c4.buttonGestureModifier;
        }
    }
    updateStateVars(b4) {
        this.__fontSize.reset(b4.fontSize);
    }
    purgeVariableDependenciesOnElmtId(a4) {
        this.__fontSize.purgeDependencyOnElmtId(a4);
        this.__isOnFocus.purgeDependencyOnElmtId(a4);
        this.__isOnHover.purgeDependencyOnElmtId(a4);
        this.__isOnClick.purgeDependencyOnElmtId(a4);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(a4);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(a4);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        this.__isOnFocus.aboutToBeDeleted();
        this.__isOnHover.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        this.__editableTitleBarTheme.aboutToBeDeleted();
        this.__buttonGestureModifier.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(z3) {
        this.__fontSize.set(z3);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(y3) {
        this.__isOnFocus.set(y3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(x3) {
        this.__isOnHover.set(x3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(w3) {
        this.__isOnClick.set(w3);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(v3) {
        this.__editableTitleBarTheme.set(v3);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(u3) {
        this.__buttonGestureModifier.set(u3);
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
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    touchEventAction(t3) {
        if (!this.item.isEnabled) {
            return;
        }
        if (t3.type === TouchType.Down) {
            this.isOnClick = true;
        }
        if (t3.type === TouchType.Up || t3.type === TouchType.Cancel) {
            if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close();
            }
            this.isOnClick = false;
        }
    }
    keyEventAction(s3) {
        if (!this.item.isEnabled) {
            return;
        }
        if (s3.keyCode !== KeyCode.KEYCODE_ENTER && s3.keyCode !== KeyCode.KEYCODE_SPACE) {
            return;
        }
        if (s3.type === KeyType.Down) {
            this.isOnClick = true;
        }
        if (s3.type === KeyType.Up) {
            this.isOnClick = false;
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
    getAccessibilityReadText() {
        if (this.item.value === PUBLIC_OK) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.icon_save'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.item.value === PUBLIC_CANCEL) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.icon_cancel'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.item.value === PUBLIC_BACK) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.icon_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.item.label) {
            return this.item.label;
        }
        return undefined;
    }
    IconBuilder(u2 = null) {
        this.observeComponentCreation2((h3, i3) => {
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
            Button.focusOnTouch(true);
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
            Button.onHover((r3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = r3;
            });
            Button.onKeyEvent((q3) => {
                this.keyEventAction(q3);
            });
            Button.onTouch((p3) => {
                this.touchEventAction(p3);
            });
            Button.onClick(() => {
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
        }, Button);
        this.observeComponentCreation2((x2, y2) => {
            If.create();
            if (this.useSymbol) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f3, g3) => {
                        SymbolGlyph.create(this.item.value);
                        SymbolGlyph.fontColor([this.editableTitleBarTheme.iconColor]);
                        SymbolGlyph.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        SymbolGlyph.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        SymbolGlyph.focusable(this.item.isEnabled);
                        SymbolGlyph.enabled(this.item.isEnabled);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontSize(SYMBOL_SIZE);
                        SymbolGlyph.accessibilityText(this.getAccessibilityReadText());
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((b3, c3) => {
                        Image.create(this.item.value);
                        Image.fillColor(this.editableTitleBarTheme.iconColor);
                        Image.matchTextDirection(this.item.value === PUBLIC_BACK ? true : false);
                        Image.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Image.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Image.focusable(this.item.isEnabled);
                        Image.enabled(this.item.isEnabled);
                        Image.draggable(false);
                        Image.accessibilityText(this.getAccessibilityReadText());
                    }, Image);
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }
    ImageBuilder(b2 = null) {
        this.observeComponentCreation2((s2, t2) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Stack);
        this.observeComponentCreation2((q2, r2) => {
            If.create();
            if (this.useSymbol) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p4, z4) => {
                        SymbolGlyph.create(this.item.value);
                        SymbolGlyph.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        SymbolGlyph.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        SymbolGlyph.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        SymbolGlyph.focusable(false);
                        SymbolGlyph.enabled(this.item.isEnabled);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((k4, l4) => {
                        Image.create(this.item.value);
                        Image.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Image.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Image.focusable(false);
                        Image.enabled(this.item.isEnabled);
                        Image.objectFit(ImageFit.Cover);
                    }, Image);
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((f2, g2) => {
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
            Button.onHover((p2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = p2;
            });
            Button.onKeyEvent((o2) => {
                this.keyEventAction(o2);
            });
            Button.onTouch((n2) => {
                this.touchEventAction(n2);
            });
            Button.onClick(() => {
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
        }, Button);
        Button.pop();
        Stack.pop();
    }
    initialRender() {
        this.observeComponentCreation2((x1, y1) => {
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
    constructor(o1, p1, q1, r1 = -1, s1 = undefined, t1) {
        super(o1, q1, r1, t1);
        if (typeof s1 === 'function') {
            this.paramsGenerator_ = s1;
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
        this.screenWidth = 640;
        this.verticalScreenLines = 6;
        this.horizontalsScreenLines = 1;
        this.useSymbol = false;
        this.cancel = () => {
        };
        this.confirm = () => {
        };
        this.__mainWindow = this.createStorageLink('mainWindow', undefined, 'mainWindow');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(p1.fontSize, this, 'fontSize');
        this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
        this.setInitiallyProvidedValue(p1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(n1) {
        if (n1.itemEditableDialog !== undefined) {
            this.itemEditableDialog = n1.itemEditableDialog;
        }
        if (n1.callbackId !== undefined) {
            this.callbackId = n1.callbackId;
        }
        if (n1.textEditableTitleBarDialog !== undefined) {
            this.textEditableTitleBarDialog = n1.textEditableTitleBarDialog;
        }
        if (n1.mainWindowStage !== undefined) {
            this.mainWindowStage = n1.mainWindowStage;
        }
        if (n1.controller !== undefined) {
            this.controller = n1.controller;
        }
        if (n1.minFontSize !== undefined) {
            this.minFontSize = n1.minFontSize;
        }
        if (n1.maxFontSize !== undefined) {
            this.maxFontSize = n1.maxFontSize;
        }
        if (n1.screenWidth !== undefined) {
            this.screenWidth = n1.screenWidth;
        }
        if (n1.verticalScreenLines !== undefined) {
            this.verticalScreenLines = n1.verticalScreenLines;
        }
        if (n1.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = n1.horizontalsScreenLines;
        }
        if (n1.useSymbol !== undefined) {
            this.useSymbol = n1.useSymbol;
        }
        if (n1.cancel !== undefined) {
            this.cancel = n1.cancel;
        }
        if (n1.confirm !== undefined) {
            this.confirm = n1.confirm;
        }
        if (n1.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (n1.maxLines !== undefined) {
            this.maxLines = n1.maxLines;
        }
    }
    updateStateVars(m1) {
        this.__fontSize.reset(m1.fontSize);
    }
    purgeVariableDependenciesOnElmtId(l1) {
        this.__mainWindow.purgeDependencyOnElmtId(l1);
        this.__fontSize.purgeDependencyOnElmtId(l1);
        this.__maxLines.purgeDependencyOnElmtId(l1);
        this.__windowStandardHeight.purgeDependencyOnElmtId(l1);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(k1) {
        this.controller = k1;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(j1) {
        this.__mainWindow.set(j1);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(i1) {
        this.__fontSize.set(i1);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(h1) {
        this.__maxLines.set(h1);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(g1) {
        this.__windowStandardHeight.set(g1);
    }
    initialRender() {
        this.observeComponentCreation2((k, l) => {
            If.create();
            if (this.textEditableTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e1, f1) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }));
                    }, Column);
                    this.observeComponentCreation2((c1, d1) => {
                        If.create();
                        if (this.useSymbol) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((k3, l3) => {
                                    SymbolGlyph.create(this.itemEditableDialog.value);
                                    SymbolGlyph.width(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.height(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    });
                                    SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((k2, l2) => {
                                    Image.create(this.itemEditableDialog.value);
                                    Image.width(IMAGE_SIZE);
                                    Image.height(IMAGE_SIZE);
                                    Image.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    });
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((a1, b1) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                    }, Column);
                    this.observeComponentCreation2((y, z) => {
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
                    this.observeComponentCreation2((r, s) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }));
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((p, q) => {
                        If.create();
                        if (this.useSymbol) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((d2, h2) => {
                                    SymbolGlyph.create(this.itemEditableDialog.value);
                                    SymbolGlyph.width(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.height(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((v, w) => {
                                    Image.create(this.itemEditableDialog.value);
                                    Image.width(IMAGE_SIZE);
                                    Image.height(IMAGE_SIZE);
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                    Column.pop();
                });
            }
        }, If);
        If.pop();
    }
    async aboutToAppear() {
        let g = this.getUIContext().getHostContext();
        this.mainWindowStage = g.windowStage.getMainWindowSync();
        let h = this.mainWindowStage.getWindowProperties();
        let i = h.windowRect;
        if (px2vp(i.height) > this.screenWidth) {
            this.maxLines = this.verticalScreenLines;
        }
        else {
            this.maxLines = this.horizontalsScreenLines;
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
function getNumberByResource(a, b) {
    try {
        let f = resourceManager.getSystemResourceManager().getNumber(a);
        if (f === 0) {
            return b;
        }
        else {
            return f;
        }
    }
    catch (c) {
        let d = c.code;
        let e = c.message;
        hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${d},message:${e}`);
        return 0;
    }
}

export default {
    EditableLeftIconType: EditableLeftIconType,
    EditableTitleBar: EditableTitleBar,
};