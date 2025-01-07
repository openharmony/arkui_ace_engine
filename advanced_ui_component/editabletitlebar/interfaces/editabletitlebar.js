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
(function (m24) {
    m24[m24['Back'] = 0] = 'Back';
    m24[m24['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (c22) {
    c22[c22['Image'] = 0] = 'Image';
    c22[c22['Icon'] = 1] = 'Icon';
    c22[c22['LeftIcon'] = 2] = 'LeftIcon';
})(ItemType || (ItemType = {}));
const PUBLIC_CANCEL = { 'id': -1, 'type': 40000, params: ['sys.symbol.xmark'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_OK = { 'id': -1, 'type': 40000, params: ['sys.symbol.checkmark'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_BACK = { 'id': -1, 'type': 40000, params: ['sys.symbol.chevron_backward'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_IMAGE_BACK = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_compnent_titlebar_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
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
// 'sys.float.titlebar_title_tertiary_size' id,value: 20vp
const TITLE_F = getNumberByResource(125831095, TITLE_VP);
// 'sys.float.titlebar_subheader_size' id,value: 14vp
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
    constructor(t21) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = t21;
    }
    applyGesture(q21) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            q21.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (q21) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            q21.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class EditableTitleBar extends ViewPU {
    constructor(a21, d21, f21, i21 = -1, m21 = undefined, n21) {
        super(a21, f21, i21, n21);
        if (typeof m21 === 'function') {
            this.paramsGenerator_ = m21;
        }
        this.leftIconStyle = EditableLeftIconType.Back;
        this.title = '';
        this.subtitle = '';
        this.isSaveIconRequired = true;
        this.imageItem = undefined;
        this.menuItems = undefined;
        this.options = {};
        this.onSave = undefined;
        this.onCancel = undefined;
        this.constraintWidth = 0;
        this.leftIconDefaultFocus = false;
        this.saveIconDefaultFocus = false;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.__editableTitleBarTheme = new ObservedPropertyObjectPU(new EditableTitleBarTheme(), this, 'editableTitleBarTheme');
        this.addProvidedVar('editableTitleBarTheme', this.__editableTitleBarTheme, false);
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(d21.contentMargin, this, 'contentMargin');
        this.__titleBarMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
        }, this, 'titleBarMargin');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(d21);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(y20) {
        if (y20.leftIconStyle !== undefined) {
            this.leftIconStyle = y20.leftIconStyle;
        }
        if (y20.title !== undefined) {
            this.title = y20.title;
        }
        if (y20.subtitle !== undefined) {
            this.subtitle = y20.subtitle;
        }
        if (y20.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = y20.isSaveIconRequired;
        }
        if (y20.imageItem !== undefined) {
            this.imageItem = y20.imageItem;
        }
        if (y20.menuItems !== undefined) {
            this.menuItems = y20.menuItems;
        }
        if (y20.options !== undefined) {
            this.options = y20.options;
        }
        if (y20.onSave !== undefined) {
            this.onSave = y20.onSave;
        }
        if (y20.onCancel !== undefined) {
            this.onCancel = y20.onCancel;
        }
        if (y20.constraintWidth !== undefined) {
            this.constraintWidth = y20.constraintWidth;
        }
        if (y20.leftIconDefaultFocus !== undefined) {
            this.leftIconDefaultFocus = y20.leftIconDefaultFocus;
        }
        if (y20.saveIconDefaultFocus !== undefined) {
            this.saveIconDefaultFocus = y20.saveIconDefaultFocus;
        }
        if (y20.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = y20.isFollowingSystemFontScale;
        }
        if (y20.maxFontScale !== undefined) {
            this.maxFontScale = y20.maxFontScale;
        }
        if (y20.systemFontScale !== undefined) {
            this.systemFontScale = y20.systemFontScale;
        }
        if (y20.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = y20.editableTitleBarTheme;
        }
        if (y20.titleBarMargin !== undefined) {
            this.titleBarMargin = y20.titleBarMargin;
        }
        if (y20.fontSize !== undefined) {
            this.fontSize = y20.fontSize;
        }
    }
    updateStateVars(w20) {
        this.__contentMargin.reset(w20.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(p20) {
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(p20);
        this.__contentMargin.purgeDependencyOnElmtId(p20);
        this.__titleBarMargin.purgeDependencyOnElmtId(p20);
        this.__fontSize.purgeDependencyOnElmtId(p20);
    }
    aboutToBeDeleted() {
        this.__editableTitleBarTheme.aboutToBeDeleted();
        this.__contentMargin.aboutToBeDeleted();
        this.__titleBarMargin.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(f20) {
        this.__editableTitleBarTheme.set(f20);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(e20) {
        this.__contentMargin.set(e20);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(u19) {
        this.__titleBarMargin.set(u19);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(g19) {
        this.__fontSize.set(g19);
    }
    onWillApplyTheme(f19) {
        this.editableTitleBarTheme.iconColor = f19.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = f19.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = f19.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = f19.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = f19.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = f19.colors.interactiveFocus;
    }
    aboutToAppear() {
        try {
            let e19 = this.getUIContext();
            this.isFollowingSystemFontScale = e19.isFollowingSystemFontScale();
            this.maxFontScale = e19.getMaxFontScale();
        }
        catch (q18) {
            let y18 = q18.code;
            let a19 = q18.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${y18}, message: ${a19}`);
        }
    }
    decideFontScale() {
        let v15 = this.getUIContext();
        this.systemFontScale = v15.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    initialRender() {
        this.observeComponentCreation2((t15, u15) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes ? this.options.safeAreaTypes : [SafeAreaType.SYSTEM], this.options.safeAreaEdges ? this.options.safeAreaEdges : [SafeAreaEdge.TOP]);
        }, Flex);
        this.observeComponentCreation2((r15, s15) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((p15, q15) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((n15, o15) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
            Row.accessibilityGroup(true);
        }, Row);
        this.observeComponentCreation2((j15, k15) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l15, m15) => {
                        Row.create();
                        Row.flexShrink(0);
                    }, Row);
                    this.imageItemLayout.bind(this)();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((h15, i15) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)();
        Row.pop();
        Row.pop();
        this.observeComponentCreation2((f15, g15) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)();
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    imageItemLayout(a15 = null) {
        {
            this.observeComponentCreation2((b15, c15) => {
                if (c15) {
                    let d15 = new ImageMenuItem(this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, b15, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 252, col: 5 });
                    ViewPU.create(d15);
                    let e15 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    d15.paramsGenerator_ = e15;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(b15, {});
                }
            }, { name: "ImageMenuItem" });
        }
    }
    leftIconLayout(m14 = null) {
        this.observeComponentCreation2((n14, o14) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((v14, w14) => {
                            if (w14) {
                                let x14 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.getUIContext()?.getRouter()?.back(),
                                        defaultFocus: this.leftIconDefaultFocus
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    imageMenuItemId: `BackMenuItem_${this.getUniqueId()}`
                                }, undefined, v14, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 261, col: 7 });
                                ViewPU.create(x14);
                                let y14 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: () => this.onCancel ? this.onCancel() : this.getUIContext()?.getRouter()?.back(),
                                            defaultFocus: this.leftIconDefaultFocus
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon,
                                        imageMenuItemId: `BackMenuItem_${this.getUniqueId()}`
                                    };
                                };
                                x14.paramsGenerator_ = y14;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(v14, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: "ImageMenuItem" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((p14, r14) => {
                            if (r14) {
                                let s14 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                        defaultFocus: this.leftIconDefaultFocus
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    imageMenuItemId: `CancelMenuItem_${this.getUniqueId()}`
                                }, undefined, p14, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 273, col: 7 });
                                ViewPU.create(s14);
                                let t14 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_CANCEL,
                                            isEnabled: true,
                                            action: () => this.onCancel && this.onCancel(),
                                            defaultFocus: this.leftIconDefaultFocus
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon,
                                        imageMenuItemId: `CancelMenuItem_${this.getUniqueId()}`
                                    };
                                };
                                s14.paramsGenerator_ = t14;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(p14, {
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
    titleLayout(v13 = null) {
        this.observeComponentCreation2((k14, l14) => {
            Column.create();
            Column.height(EditableTitleBar.totalHeight);
            Column.justifyContent(FlexAlign.Center);
            Column.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((h14, j14) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((e14, g14) => {
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
        this.observeComponentCreation2((w13, x13) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c14, d14) => {
                        Row.create();
                        Row.margin({
                            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((y13, b14) => {
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
    rightMenuItemsLayout(p13 = null) {
        {
            this.observeComponentCreation2((q13, s13) => {
                if (s13) {
                    let t13 = new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                        parentUniqueId: this.getUniqueId(),
                        saveIconDefaultFocus: this.saveIconDefaultFocus
                    }, undefined, q13, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 339, col: 5 });
                    ViewPU.create(t13);
                    let u13 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize,
                            parentUniqueId: this.getUniqueId(),
                            saveIconDefaultFocus: this.saveIconDefaultFocus
                        };
                    };
                    t13.paramsGenerator_ = u13;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(q13, {
                        fontSize: this.fontSize,
                        parentUniqueId: this.getUniqueId()
                    });
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }
    onPlaceChildren(l13, m13, n13) {
        m13.forEach((o13) => {
            o13.layout({ x: 0, y: 0 });
        });
    }
    onMeasureSize(g13, h13, i13) {
        let j13 = { width: g13.width, height: g13.height };
        this.fontSize = this.decideFontScale();
        h13.forEach((k13) => {
            j13.height = k13.measure(i13).height;
            j13.width = Number(i13.maxWidth);
        });
        return j13;
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
    constructor(y12, z12, a13, b13 = -1, c13 = undefined, d13) {
        super(y12, a13, b13, d13);
        if (typeof c13 === 'function') {
            this.paramsGenerator_ = c13;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.saveIconDefaultFocus = false;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(z12.fontSize, this, 'fontSize');
        this.__parentUniqueId = new SynchedPropertySimpleOneWayPU(z12.parentUniqueId, this, 'parentUniqueId');
        this.setInitiallyProvidedValue(z12);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(x12) {
        if (x12.menuItems !== undefined) {
            this.menuItems = x12.menuItems;
        }
        if (x12.onSave !== undefined) {
            this.onSave = x12.onSave;
        }
        if (x12.isSaveEnabled !== undefined) {
            this.isSaveEnabled = x12.isSaveEnabled;
        }
        if (x12.saveIconDefaultFocus !== undefined) {
            this.saveIconDefaultFocus = x12.saveIconDefaultFocus;
        }
        if (x12.fontSize === undefined) {
            this.__fontSize.set(1);
        }
    }
    updateStateVars(v12) {
        this.__fontSize.reset(v12.fontSize);
        this.__parentUniqueId.reset(v12.parentUniqueId);
    }
    purgeVariableDependenciesOnElmtId(u12) {
        this.__fontSize.purgeDependencyOnElmtId(u12);
        this.__parentUniqueId.purgeDependencyOnElmtId(u12);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        this.__parentUniqueId.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(t12) {
        this.__fontSize.set(t12);
    }
    get parentUniqueId() {
        return this.__parentUniqueId.get();
    }
    set parentUniqueId(s12) {
        this.__parentUniqueId.set(s12);
    }
    initialRender() {
        this.observeComponentCreation2((q12, r12) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((m12, n12) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((u11, w11) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x11, z11) => {
                        ForEach.create();
                        const a12 = (c12, d12) => {
                            const e12 = c12;
                            {
                                this.observeComponentCreation2((g12, h12) => {
                                    if (h12) {
                                        let i12 = new ImageMenuItem(this, {
                                            item: e12,
                                            attribute: ItemType.Icon,
                                            fontSize: this.fontSize,
                                            imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${d12}`
                                        }, undefined, g12, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 383, col: 15 });
                                        ViewPU.create(i12);
                                        let j12 = () => {
                                            return {
                                                item: e12,
                                                attribute: ItemType.Icon,
                                                fontSize: this.fontSize,
                                                imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${d12}`
                                            };
                                        };
                                        i12.paramsGenerator_ = j12;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(g12, {
                                            fontSize: this.fontSize
                                        });
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(x11, this.menuItems.slice(EditableTitleBar.commonZero, this.isSaveEnabled ?
                        EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems), a12, undefined, true, false);
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
        this.observeComponentCreation2((j11, m11) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((n11, q11) => {
                            if (q11) {
                                let s11 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                        defaultFocus: this.saveIconDefaultFocus
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                    imageMenuItemId: `SaveMenuItem_${this.parentUniqueId}`
                                }, undefined, n11, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 392, col: 11 });
                                ViewPU.create(s11);
                                let t11 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_OK,
                                            isEnabled: true,
                                            action: () => this.onSave && this.onSave(),
                                            defaultFocus: this.saveIconDefaultFocus
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.Icon,
                                        imageMenuItemId: `SaveMenuItem_${this.parentUniqueId}`
                                    };
                                };
                                s11.paramsGenerator_ = t11;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(n11, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: "ImageMenuItem" });
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
    constructor(z10, a11, b11, c11 = -1, e11 = undefined, f11) {
        super(z10, b11, c11, f11);
        if (typeof e11 === 'function') {
            this.paramsGenerator_ = e11;
        }
        this.item = {
            value: '',
            isEnabled: true,
            label: '',
            accessibilityLevel: 'auto',
            accessibilityText: '',
            accessibilityDescription: '',
        };
        this.attribute = ItemType.Image;
        this.callbackId = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.2;
        this.longPressTime = 500;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(a11.fontSize, this, 'fontSize');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.imageMenuItemId = undefined;
        this.__editableTitleBarTheme = this.initializeConsume('editableTitleBarTheme', 'editableTitleBarTheme');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let h11 = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 432, col: 14 });
                h11.setController(this.dialogController);
                ViewPU.create(h11);
                let i11 = () => {
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
                h11.paramsGenerator_ = i11;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, "buttonGestureModifier");
        this.setInitiallyProvidedValue(a11);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(y10) {
        if (y10.item !== undefined) {
            this.item = y10.item;
        }
        if (y10.attribute !== undefined) {
            this.attribute = y10.attribute;
        }
        if (y10.callbackId !== undefined) {
            this.callbackId = y10.callbackId;
        }
        if (y10.minFontSize !== undefined) {
            this.minFontSize = y10.minFontSize;
        }
        if (y10.maxFontSize !== undefined) {
            this.maxFontSize = y10.maxFontSize;
        }
        if (y10.longPressTime !== undefined) {
            this.longPressTime = y10.longPressTime;
        }
        if (y10.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (y10.isOnFocus !== undefined) {
            this.isOnFocus = y10.isOnFocus;
        }
        if (y10.isOnHover !== undefined) {
            this.isOnHover = y10.isOnHover;
        }
        if (y10.isOnClick !== undefined) {
            this.isOnClick = y10.isOnClick;
        }
        if (y10.imageMenuItemId !== undefined) {
            this.imageMenuItemId = y10.imageMenuItemId;
        }
        if (y10.dialogController !== undefined) {
            this.dialogController = y10.dialogController;
        }
        if (y10.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = y10.buttonGestureModifier;
        }
    }
    updateStateVars(x10) {
        this.__fontSize.reset(x10.fontSize);
    }
    purgeVariableDependenciesOnElmtId(w10) {
        this.__fontSize.purgeDependencyOnElmtId(w10);
        this.__isOnFocus.purgeDependencyOnElmtId(w10);
        this.__isOnHover.purgeDependencyOnElmtId(w10);
        this.__isOnClick.purgeDependencyOnElmtId(w10);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(w10);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(w10);
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
    set fontSize(v10) {
        this.__fontSize.set(v10);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(t10) {
        this.__isOnFocus.set(t10);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(s10) {
        this.__isOnHover.set(s10);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(r10) {
        this.__isOnClick.set(r10);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(q10) {
        this.__editableTitleBarTheme.set(q10);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(p10) {
        this.__buttonGestureModifier.set(p10);
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
    touchEventAction(o10) {
        if (!this.item.isEnabled) {
            return;
        }
        if (o10.type === TouchType.Down) {
            this.isOnClick = true;
        }
        if (o10.type === TouchType.Up || o10.type === TouchType.Cancel) {
            if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close();
            }
            this.isOnClick = false;
        }
    }
    keyEventAction(n10) {
        if (!this.item.isEnabled) {
            return;
        }
        if (n10.keyCode !== KeyCode.KEYCODE_ENTER && n10.keyCode !== KeyCode.KEYCODE_SPACE) {
            return;
        }
        if (n10.type === KeyType.Down) {
            this.isOnClick = true;
        }
        if (n10.type === KeyType.Up) {
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
    toStringFormat(i10) {
        if (typeof i10 === 'string' || typeof i10 === 'undefined') {
            return i10;
        }
        else {
            let j10 = '';
            try {
                j10 = getContext()?.resourceManager?.getStringSync(i10);
            }
            catch (k10) {
                let l10 = k10?.code;
                let m10 = k10?.message;
                hilog.error(0x3900, 'Ace', `Faild to subHeader toStringFormat, code: ${l10}, message: ${m10}`);
            }
            return j10;
        }
    }
    getAccessibilityReadText() {
        if (this.item.value === PUBLIC_OK) {
            return getContext()?.resourceManager?.getStringByNameSync('icon_save');
        }
        else if (this.item.value === PUBLIC_CANCEL) {
            return getContext()?.resourceManager?.getStringByNameSync('icon_cancel');
        }
        else if (this.item.value === PUBLIC_BACK) {
            return getContext()?.resourceManager?.getStringByNameSync('icon_back');
        }
        else if (this.item.accessibilityText) {
            return this.toStringFormat(this.item.accessibilityText);
        }
        else if (this.item.label) {
            return this.toStringFormat(this.item.label);
        }
        return ' ';
    }
    getRightIconAccessibilityLevel() {
        if (this.item.accessibilityLevel && this.item.accessibilityLevel !== '') {
            return this.item.accessibilityLevel;
        }
        return 'auto';
    }
    getAccessibilityDescription() {
        if (this.item.accessibilityDescription && this.item.accessibilityDescription !== '') {
            return this.toStringFormat(this.item.accessibilityDescription);
        }
        return '';
    }
    IconBuilder(s9 = null) {
        this.observeComponentCreation2((d10, e10) => {
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.id(this.imageMenuItemId);
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
            Button.onHover((h10) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = h10;
            });
            Button.onKeyEvent((g10) => {
                this.keyEventAction(g10);
            });
            Button.onTouch((f10) => {
                this.touchEventAction(f10);
            });
            Button.onClick(() => {
                if (this.item.isEnabled === undefined) {
                    this.item.isEnabled = true;
                }
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
            Button.accessibilityLevel(this.getRightIconAccessibilityLevel());
            Button.accessibilityDescription(this.getAccessibilityDescription());
        }, Button);
        this.observeComponentCreation2((t9, u9) => {
            If.create();
            if (this.item.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b10, c10) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([this.editableTitleBarTheme.iconColor]);
                        SymbolGlyph.attributeModifier.bind(this)(this.item.symbolStyle);
                        SymbolGlyph.focusable(this.item.isEnabled);
                        SymbolGlyph.enabled(this.item.isEnabled);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.accessibilityText(this.getAccessibilityReadText());
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.fontSize(SYMBOL_SIZE);
                        SymbolGlyph.defaultFocus(this.item.isEnabled ? this.item.defaultFocus : false);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((v9, w9) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((z9, a10) => {
                                    SymbolGlyph.create(this.item.value);
                                    SymbolGlyph.fontSize(SYMBOL_SIZE);
                                    SymbolGlyph.fontColor([this.editableTitleBarTheme.iconColor]);
                                    SymbolGlyph.focusable(this.item.isEnabled);
                                    SymbolGlyph.enabled(this.item.isEnabled);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.accessibilityText(this.getAccessibilityReadText());
                                    SymbolGlyph.defaultFocus(this.item.isEnabled ? this.item.defaultFocus : false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((x9, y9) => {
                                    Image.create(this.item.value);
                                    Image.fillColor(this.editableTitleBarTheme.iconColor);
                                    Image.matchTextDirection(this.item.value === PUBLIC_IMAGE_BACK ? true : false);
                                    Image.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    Image.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    Image.focusable(this.item.isEnabled);
                                    Image.enabled(this.item.isEnabled);
                                    Image.draggable(false);
                                    Image.accessibilityText(this.getAccessibilityReadText());
                                    Image.defaultFocus(this.item.isEnabled ? this.item.defaultFocus : false);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }
    ImageBuilder(i9 = null) {
        this.observeComponentCreation2((q9, r9) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Stack);
        this.observeComponentCreation2((o9, p9) => {
            Image.create(this.item.value);
            Image.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.focusable(false);
            Image.enabled(this.item.isEnabled);
            Image.objectFit(ImageFit.Cover);
        }, Image);
        this.observeComponentCreation2((j9, k9) => {
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
            Button.onHover((n9) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = n9;
            });
            Button.onKeyEvent((m9) => {
                this.keyEventAction(m9);
            });
            Button.onTouch((l9) => {
                this.touchEventAction(l9);
            });
            Button.onClick(() => {
                if (this.item.isEnabled === undefined) {
                    this.item.isEnabled = true;
                }
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
            Button.defaultFocus(this.item.isEnabled ? this.item.defaultFocus : false);
        }, Button);
        Button.pop();
        Stack.pop();
    }
    initialRender() {
        this.observeComponentCreation2((g9, h9) => {
            If.create();
            if (this.attribute === ItemType.Icon || this.attribute === ItemType.LeftIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconBuilder.bind(this)();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.ImageBuilder.bind(this)();
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
    constructor(a9, b9, c9, d9 = -1, e9 = undefined, f9) {
        super(a9, c9, d9, f9);
        if (typeof e9 === 'function') {
            this.paramsGenerator_ = e9;
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
        this.cancel = () => {
        };
        this.confirm = () => {
        };
        this.__mainWindow = this.createStorageLink('mainWindow', undefined, 'mainWindow');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(b9.fontSize, this, 'fontSize');
        this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
        this.setInitiallyProvidedValue(b9);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z8) {
        if (z8.itemEditableDialog !== undefined) {
            this.itemEditableDialog = z8.itemEditableDialog;
        }
        if (z8.callbackId !== undefined) {
            this.callbackId = z8.callbackId;
        }
        if (z8.textEditableTitleBarDialog !== undefined) {
            this.textEditableTitleBarDialog = z8.textEditableTitleBarDialog;
        }
        if (z8.mainWindowStage !== undefined) {
            this.mainWindowStage = z8.mainWindowStage;
        }
        if (z8.controller !== undefined) {
            this.controller = z8.controller;
        }
        if (z8.minFontSize !== undefined) {
            this.minFontSize = z8.minFontSize;
        }
        if (z8.maxFontSize !== undefined) {
            this.maxFontSize = z8.maxFontSize;
        }
        if (z8.screenWidth !== undefined) {
            this.screenWidth = z8.screenWidth;
        }
        if (z8.verticalScreenLines !== undefined) {
            this.verticalScreenLines = z8.verticalScreenLines;
        }
        if (z8.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = z8.horizontalsScreenLines;
        }
        if (z8.cancel !== undefined) {
            this.cancel = z8.cancel;
        }
        if (z8.confirm !== undefined) {
            this.confirm = z8.confirm;
        }
        if (z8.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (z8.maxLines !== undefined) {
            this.maxLines = z8.maxLines;
        }
    }
    updateStateVars(y8) {
        this.__fontSize.reset(y8.fontSize);
    }
    purgeVariableDependenciesOnElmtId(x8) {
        this.__mainWindow.purgeDependencyOnElmtId(x8);
        this.__fontSize.purgeDependencyOnElmtId(x8);
        this.__maxLines.purgeDependencyOnElmtId(x8);
        this.__windowStandardHeight.purgeDependencyOnElmtId(x8);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(w8) {
        this.controller = w8;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(v8) {
        this.__mainWindow.set(v8);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(u8) {
        this.__fontSize.set(u8);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(t8) {
        this.__maxLines.set(t8);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(s8) {
        this.__windowStandardHeight.set(s8);
    }
    initialRender() {
        this.observeComponentCreation2((x4, a5) => {
            If.create();
            if (this.textEditableTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q8, r8) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }));
                    }, Column);
                    this.observeComponentCreation2((g8, h8) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((o8, p8) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemEditableDialog.symbolStyle);
                                    SymbolGlyph.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    });
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.direction(Direction.Ltr);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((i8, j8) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((m8, n8) => {
                                                SymbolGlyph.create(this.itemEditableDialog.value);
                                                SymbolGlyph.margin({
                                                    top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                    bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                });
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                                SymbolGlyph.direction(Direction.Ltr);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((k8, l8) => {
                                                Image.create(this.itemEditableDialog.value);
                                                Image.width(IMAGE_SIZE);
                                                Image.height(IMAGE_SIZE);
                                                Image.margin({
                                                    top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                    bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                });
                                                Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                Image.direction(Direction.Ltr);
                                            }, Image);
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((e8, f8) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                    }, Column);
                    this.observeComponentCreation2((c8, d8) => {
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
                    this.observeComponentCreation2((a8, b8) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }));
                        Column.justifyContent(FlexAlign.Center);
                        Column.direction(Direction.Ltr);
                    }, Column);
                    this.observeComponentCreation2((d5, g5) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((r7, x7) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemEditableDialog.symbolStyle);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((k5, l5) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((o6, o7) => {
                                                SymbolGlyph.create(this.itemEditableDialog.value);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((f6, j6) => {
                                                Image.create(this.itemEditableDialog.value);
                                                Image.width(IMAGE_SIZE);
                                                Image.height(IMAGE_SIZE);
                                                Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                            }, Image);
                                        });
                                    }
                                }, If);
                                If.pop();
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
        let j4 = this.getUIContext().getHostContext();
        this.mainWindowStage = j4.windowStage.getMainWindowSync();
        let q4 = this.mainWindowStage.getWindowProperties();
        let t4 = q4.windowRect;
        if (px2vp(t4.height) > this.screenWidth) {
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
function getNumberByResource(k1, r3) {
    try {
        let f4 = resourceManager.getSystemResourceManager().getNumber(k1);
        if (f4 === 0) {
            return r3;
        }
        else {
            return f4;
        }
    }
    catch (s3) {
        let y3 = s3.code;
        let d4 = s3.message;
        hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${y3},message:${d4}`);
        return 0;
    }
}
class Util {
    static isSymbolResource(i1) {
        if (i1 === undefined) {
            return true;
        }
        if (!Util.isResourceType(i1)) {
            return false;
        }
        let j1 = i1;
        return j1.type === Util.RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(e1) {
        if (!e1) {
            return false;
        }
        return typeof e1 !== 'string';
    }
}
Util.RESOURCE_TYPE_SYMBOL = 40000;

export default {
    EditableLeftIconType: EditableLeftIconType,
    EditableTitleBar: EditableTitleBar,
};
