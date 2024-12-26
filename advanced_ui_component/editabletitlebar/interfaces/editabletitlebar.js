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
(function (j17) {
    j17[j17['Back'] = 0] = 'Back';
    j17[j17['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (i17) {
    i17[i17['Image'] = 0] = 'Image';
    i17[i17['Icon'] = 1] = 'Icon';
    i17[i17['LeftIcon'] = 2] = 'LeftIcon';
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
    constructor(h17) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = h17;
    }
    applyGesture(g17) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            g17.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (g17) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            g17.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class EditableTitleBar extends ViewPU {
    constructor(a17, b17, c17, d17 = -1, e17 = undefined, f17) {
        super(a17, c17, d17, f17);
        if (typeof e17 === 'function') {
            this.paramsGenerator_ = e17;
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
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.__editableTitleBarTheme = new ObservedPropertyObjectPU(new EditableTitleBarTheme(), this, 'editableTitleBarTheme');
        this.addProvidedVar('editableTitleBarTheme', this.__editableTitleBarTheme, false);
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(b17.contentMargin, this, 'contentMargin');
        this.__titleBarMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
        }, this, 'titleBarMargin');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(b17);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z16) {
        if (z16.leftIconStyle !== undefined) {
            this.leftIconStyle = z16.leftIconStyle;
        }
        if (z16.title !== undefined) {
            this.title = z16.title;
        }
        if (z16.subtitle !== undefined) {
            this.subtitle = z16.subtitle;
        }
        if (z16.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = z16.isSaveIconRequired;
        }
        if (z16.imageItem !== undefined) {
            this.imageItem = z16.imageItem;
        }
        if (z16.menuItems !== undefined) {
            this.menuItems = z16.menuItems;
        }
        if (z16.options !== undefined) {
            this.options = z16.options;
        }
        if (z16.onSave !== undefined) {
            this.onSave = z16.onSave;
        }
        if (z16.onCancel !== undefined) {
            this.onCancel = z16.onCancel;
        }
        if (z16.constraintWidth !== undefined) {
            this.constraintWidth = z16.constraintWidth;
        }
        if (z16.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = z16.isFollowingSystemFontScale;
        }
        if (z16.maxFontScale !== undefined) {
            this.maxFontScale = z16.maxFontScale;
        }
        if (z16.systemFontScale !== undefined) {
            this.systemFontScale = z16.systemFontScale;
        }
        if (z16.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = z16.editableTitleBarTheme;
        }
        if (z16.titleBarMargin !== undefined) {
            this.titleBarMargin = z16.titleBarMargin;
        }
        if (z16.fontSize !== undefined) {
            this.fontSize = z16.fontSize;
        }
    }
    updateStateVars(y16) {
        this.__contentMargin.reset(y16.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(x16) {
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(x16);
        this.__contentMargin.purgeDependencyOnElmtId(x16);
        this.__titleBarMargin.purgeDependencyOnElmtId(x16);
        this.__fontSize.purgeDependencyOnElmtId(x16);
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
    set editableTitleBarTheme(w16) {
        this.__editableTitleBarTheme.set(w16);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(v16) {
        this.__contentMargin.set(v16);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(u16) {
        this.__titleBarMargin.set(u16);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(t16) {
        this.__fontSize.set(t16);
    }
    onWillApplyTheme(s16) {
        this.editableTitleBarTheme.iconColor = s16.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = s16.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = s16.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = s16.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = s16.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = s16.colors.interactiveFocus;
    }
    aboutToAppear() {
        try {
            let r16 = this.getUIContext();
            this.isFollowingSystemFontScale = r16.isFollowingSystemFontScale();
            this.maxFontScale = r16.getMaxFontScale();
        }
        catch (o16) {
            let p16 = o16.code;
            let q16 = o16.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${p16}, message: ${q16}`);
        }
    }
    decideFontScale() {
        let n16 = this.getUIContext();
        this.systemFontScale = n16.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    initialRender() {
        this.observeComponentCreation2((l16, m16) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes ? this.options.safeAreaTypes : [SafeAreaType.SYSTEM], this.options.safeAreaEdges ? this.options.safeAreaEdges : [SafeAreaEdge.TOP]);
        }, Flex);
        this.observeComponentCreation2((j16, k16) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((h16, i16) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((f16, g16) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
            Row.accessibilityGroup(true);
        }, Row);
        this.observeComponentCreation2((b16, c16) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d16, e16) => {
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
        this.observeComponentCreation2((z15, a16) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)();
        Row.pop();
        Row.pop();
        this.observeComponentCreation2((x15, y15) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)();
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    imageItemLayout(s15 = null) {
        {
            this.observeComponentCreation2((t15, u15) => {
                if (u15) {
                    let v15 = new ImageMenuItem(this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, t15, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 249, col: 5 });
                    ViewPU.create(v15);
                    let w15 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    v15.paramsGenerator_ = w15;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(t15, {});
                }
            }, { name: 'ImageMenuItem' });
        }
    }
    leftIconLayout(h15 = null) {
        this.observeComponentCreation2((i15, j15) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((o15, p15) => {
                            if (p15) {
                                let q15 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.getUIContext()?.getRouter()?.back()
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    imageMenuItemId: `BackMenuItem_${this.getUniqueId()}`
                                }, undefined, o15, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 258, col: 7 });
                                ViewPU.create(q15);
                                let r15 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: () => this.onCancel ? this.onCancel() : this.getUIContext()?.getRouter()?.back()
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon,
                                        imageMenuItemId: `BackMenuItem_${this.getUniqueId()}`
                                    };
                                };
                                q15.paramsGenerator_ = r15;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(o15, {
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
                        this.observeComponentCreation2((k15, l15) => {
                            if (l15) {
                                let m15 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    imageMenuItemId: `CancelMenuItem_${this.getUniqueId()}`
                                }, undefined, k15, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 269, col: 7 });
                                ViewPU.create(m15);
                                let n15 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_CANCEL,
                                            isEnabled: true,
                                            action: () => this.onCancel && this.onCancel(),
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon,
                                        imageMenuItemId: `CancelMenuItem_${this.getUniqueId()}`
                                    };
                                };
                                m15.paramsGenerator_ = n15;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(k15, {
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
    titleLayout(u14 = null) {
        this.observeComponentCreation2((f15, g15) => {
            Column.create();
            Column.height(EditableTitleBar.totalHeight);
            Column.justifyContent(FlexAlign.Center);
            Column.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((d15, e15) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((b15, c15) => {
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
        this.observeComponentCreation2((v14, w14) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z14, a15) => {
                        Row.create();
                        Row.margin({
                            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((x14, y14) => {
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
    rightMenuItemsLayout(p14 = null) {
        {
            this.observeComponentCreation2((q14, r14) => {
                if (r14) {
                    let s14 = new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                        parentUniqueId: this.getUniqueId()
                    }, undefined, q14, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 334, col: 5 });
                    ViewPU.create(s14);
                    let t14 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize,
                            parentUniqueId: this.getUniqueId()
                        };
                    };
                    s14.paramsGenerator_ = t14;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(q14, {
                        fontSize: this.fontSize,
                        parentUniqueId: this.getUniqueId()
                    });
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }
    onPlaceChildren(l14, m14, n14) {
        m14.forEach((o14) => {
            o14.layout({ x: 0, y: 0 });
        });
    }
    onMeasureSize(g14, h14, i14) {
        let j14 = { width: g14.width, height: g14.height };
        this.fontSize = this.decideFontScale();
        h14.forEach((k14) => {
            j14.height = k14.measure(i14).height;
            j14.width = Number(i14.maxWidth);
        });
        return j14;
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
    constructor(a14, b14, c14, d14 = -1, e14 = undefined, f14) {
        super(a14, c14, d14, f14);
        if (typeof e14 === 'function') {
            this.paramsGenerator_ = e14;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(b14.fontSize, this, 'fontSize');
        this.__parentUniqueId = new SynchedPropertySimpleOneWayPU(b14.parentUniqueId, this, 'parentUniqueId');
        this.setInitiallyProvidedValue(b14);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z13) {
        if (z13.menuItems !== undefined) {
            this.menuItems = z13.menuItems;
        }
        if (z13.onSave !== undefined) {
            this.onSave = z13.onSave;
        }
        if (z13.isSaveEnabled !== undefined) {
            this.isSaveEnabled = z13.isSaveEnabled;
        }
        if (z13.fontSize === undefined) {
            this.__fontSize.set(1);
        }
    }
    updateStateVars(y13) {
        this.__fontSize.reset(y13.fontSize);
        this.__parentUniqueId.reset(y13.parentUniqueId);
    }
    purgeVariableDependenciesOnElmtId(x13) {
        this.__fontSize.purgeDependencyOnElmtId(x13);
        this.__parentUniqueId.purgeDependencyOnElmtId(x13);
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
    set fontSize(w13) {
        this.__fontSize.set(w13);
    }
    get parentUniqueId() {
        return this.__parentUniqueId.get();
    }
    set parentUniqueId(v13) {
        this.__parentUniqueId.set(v13);
    }
    initialRender() {
        this.observeComponentCreation2((t13, u13) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((r13, s13) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((f13, g13) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h13, i13) => {
                        ForEach.create();
                        const j13 = (k13, l13) => {
                            const m13 = k13;
                            {
                                this.observeComponentCreation2((n13, o13) => {
                                    if (o13) {
                                        let p13 = new ImageMenuItem(this, {
                                            item: m13,
                                            attribute: ItemType.Icon,
                                            fontSize: this.fontSize,
                                            imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${l13}`
                                        }, undefined, n13, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 376, col: 15 });
                                        ViewPU.create(p13);
                                        let q13 = () => {
                                            return {
                                                item: m13,
                                                attribute: ItemType.Icon,
                                                fontSize: this.fontSize,
                                                imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${l13}`
                                            };
                                        };
                                        p13.paramsGenerator_ = q13;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(n13, {
                                            fontSize: this.fontSize
                                        });
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(h13, this.menuItems.slice(EditableTitleBar.commonZero, this.isSaveEnabled ?
                        EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems), j13, undefined, true, false);
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
        this.observeComponentCreation2((z12, a13) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((b13, c13) => {
                            if (c13) {
                                let d13 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                    imageMenuItemId: `SaveMenuItem_${this.parentUniqueId}`
                                }, undefined, b13, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 385, col: 11 });
                                ViewPU.create(d13);
                                let e13 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_OK,
                                            isEnabled: true,
                                            action: () => this.onSave && this.onSave(),
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.Icon,
                                        imageMenuItemId: `SaveMenuItem_${this.parentUniqueId}`
                                    };
                                };
                                d13.paramsGenerator_ = e13;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(b13, {
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
    constructor(r12, s12, t12, u12 = -1, v12 = undefined, w12) {
        super(r12, t12, u12, w12);
        if (typeof v12 === 'function') {
            this.paramsGenerator_ = v12;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(s12.fontSize, this, 'fontSize');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.imageMenuItemId = undefined;
        this.__editableTitleBarTheme = this.initializeConsume('editableTitleBarTheme', 'editableTitleBarTheme');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let x12 = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 424, col: 14 });
                x12.setController(this.dialogController);
                ViewPU.create(x12);
                let y12 = () => {
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
                x12.paramsGenerator_ = y12;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(s12);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q12) {
        if (q12.item !== undefined) {
            this.item = q12.item;
        }
        if (q12.attribute !== undefined) {
            this.attribute = q12.attribute;
        }
        if (q12.callbackId !== undefined) {
            this.callbackId = q12.callbackId;
        }
        if (q12.minFontSize !== undefined) {
            this.minFontSize = q12.minFontSize;
        }
        if (q12.maxFontSize !== undefined) {
            this.maxFontSize = q12.maxFontSize;
        }
        if (q12.longPressTime !== undefined) {
            this.longPressTime = q12.longPressTime;
        }
        if (q12.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (q12.isOnFocus !== undefined) {
            this.isOnFocus = q12.isOnFocus;
        }
        if (q12.isOnHover !== undefined) {
            this.isOnHover = q12.isOnHover;
        }
        if (q12.isOnClick !== undefined) {
            this.isOnClick = q12.isOnClick;
        }
        if (q12.imageMenuItemId !== undefined) {
            this.imageMenuItemId = q12.imageMenuItemId;
        }
        if (q12.dialogController !== undefined) {
            this.dialogController = q12.dialogController;
        }
        if (q12.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = q12.buttonGestureModifier;
        }
    }
    updateStateVars(p12) {
        this.__fontSize.reset(p12.fontSize);
    }
    purgeVariableDependenciesOnElmtId(o12) {
        this.__fontSize.purgeDependencyOnElmtId(o12);
        this.__isOnFocus.purgeDependencyOnElmtId(o12);
        this.__isOnHover.purgeDependencyOnElmtId(o12);
        this.__isOnClick.purgeDependencyOnElmtId(o12);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(o12);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(o12);
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
    set fontSize(n12) {
        this.__fontSize.set(n12);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(m12) {
        this.__isOnFocus.set(m12);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(l12) {
        this.__isOnHover.set(l12);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(k12) {
        this.__isOnClick.set(k12);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(j12) {
        this.__editableTitleBarTheme.set(j12);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(i12) {
        this.__buttonGestureModifier.set(i12);
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
    touchEventAction(h12) {
        if (!this.item.isEnabled) {
            return;
        }
        if (h12.type === TouchType.Down) {
            this.isOnClick = true;
        }
        if (h12.type === TouchType.Up || h12.type === TouchType.Cancel) {
            if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close();
            }
            this.isOnClick = false;
        }
    }
    keyEventAction(g12) {
        if (!this.item.isEnabled) {
            return;
        }
        if (g12.keyCode !== KeyCode.KEYCODE_ENTER && g12.keyCode !== KeyCode.KEYCODE_SPACE) {
            return;
        }
        if (g12.type === KeyType.Down) {
            this.isOnClick = true;
        }
        if (g12.type === KeyType.Up) {
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
    toStringFormat(b12) {
        if (typeof b12 === 'string' || typeof b12 === 'undefined') {
            return b12;
        }
        else {
            let c12 = '';
            try {
                c12 = getContext()?.resourceManager?.getStringSync(b12);
            }
            catch (d12) {
                let e12 = d12?.code;
                let f12 = d12?.message;
                hilog.error(0x3900, 'Ace', `Faild to subHeader toStringFormat, code: ${e12}, message: ${f12}`);
            }
            return c12;
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
    IconBuilder(l11 = null) {
        this.observeComponentCreation2((w11, x11) => {
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
            Button.onHover((a12) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = a12;
            });
            Button.onKeyEvent((z11) => {
                this.keyEventAction(z11);
            });
            Button.onTouch((y11) => {
                this.touchEventAction(y11);
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
        this.observeComponentCreation2((m11, n11) => {
            If.create();
            if (this.item.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u11, v11) => {
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
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((o11, p11) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((s11, t11) => {
                                    SymbolGlyph.create(this.item.value);
                                    SymbolGlyph.fontSize(SYMBOL_SIZE);
                                    SymbolGlyph.fontColor([this.editableTitleBarTheme.iconColor]);
                                    SymbolGlyph.focusable(this.item.isEnabled);
                                    SymbolGlyph.enabled(this.item.isEnabled);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.accessibilityText(this.getAccessibilityReadText());
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((q11, r11) => {
                                    Image.create(this.item.value);
                                    Image.fillColor(this.editableTitleBarTheme.iconColor);
                                    Image.matchTextDirection(this.item.value === PUBLIC_IMAGE_BACK ? true : false);
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
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }
    ImageBuilder(b11 = null) {
        this.observeComponentCreation2((j11, k11) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Stack);
        this.observeComponentCreation2((h11, i11) => {
            Image.create(this.item.value);
            Image.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.focusable(false);
            Image.enabled(this.item.isEnabled);
            Image.objectFit(ImageFit.Cover);
        }, Image);
        this.observeComponentCreation2((c11, d11) => {
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
            Button.onHover((g11) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = g11;
            });
            Button.onKeyEvent((f11) => {
                this.keyEventAction(f11);
            });
            Button.onTouch((e11) => {
                this.touchEventAction(e11);
            });
            Button.onClick(() => {
                if (this.item.isEnabled === undefined) {
                    this.item.isEnabled = true;
                }
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
        }, Button);
        Button.pop();
        Stack.pop();
    }
    initialRender() {
        this.observeComponentCreation2((z10, a11) => {
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
    constructor(t10, u10, v10, w10 = -1, x10 = undefined, y10) {
        super(t10, v10, w10, y10);
        if (typeof x10 === 'function') {
            this.paramsGenerator_ = x10;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(u10.fontSize, this, 'fontSize');
        this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
        this.setInitiallyProvidedValue(u10);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(s10) {
        if (s10.itemEditableDialog !== undefined) {
            this.itemEditableDialog = s10.itemEditableDialog;
        }
        if (s10.callbackId !== undefined) {
            this.callbackId = s10.callbackId;
        }
        if (s10.textEditableTitleBarDialog !== undefined) {
            this.textEditableTitleBarDialog = s10.textEditableTitleBarDialog;
        }
        if (s10.mainWindowStage !== undefined) {
            this.mainWindowStage = s10.mainWindowStage;
        }
        if (s10.controller !== undefined) {
            this.controller = s10.controller;
        }
        if (s10.minFontSize !== undefined) {
            this.minFontSize = s10.minFontSize;
        }
        if (s10.maxFontSize !== undefined) {
            this.maxFontSize = s10.maxFontSize;
        }
        if (s10.screenWidth !== undefined) {
            this.screenWidth = s10.screenWidth;
        }
        if (s10.verticalScreenLines !== undefined) {
            this.verticalScreenLines = s10.verticalScreenLines;
        }
        if (s10.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = s10.horizontalsScreenLines;
        }
        if (s10.cancel !== undefined) {
            this.cancel = s10.cancel;
        }
        if (s10.confirm !== undefined) {
            this.confirm = s10.confirm;
        }
        if (s10.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (s10.maxLines !== undefined) {
            this.maxLines = s10.maxLines;
        }
    }
    updateStateVars(r10) {
        this.__fontSize.reset(r10.fontSize);
    }
    purgeVariableDependenciesOnElmtId(q10) {
        this.__mainWindow.purgeDependencyOnElmtId(q10);
        this.__fontSize.purgeDependencyOnElmtId(q10);
        this.__maxLines.purgeDependencyOnElmtId(q10);
        this.__windowStandardHeight.purgeDependencyOnElmtId(q10);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(p10) {
        this.controller = p10;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(o10) {
        this.__mainWindow.set(o10);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(n10) {
        this.__fontSize.set(n10);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(m10) {
        this.__maxLines.set(m10);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(l10) {
        this.__windowStandardHeight.set(l10);
    }
    initialRender() {
        this.observeComponentCreation2((h9, i9) => {
            If.create();
            if (this.textEditableTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j10, k10) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }));
                    }, Column);
                    this.observeComponentCreation2((z9, a10) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((h10, i10) => {
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
                                this.observeComponentCreation2((b10, c10) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((f10, g10) => {
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
                                            this.observeComponentCreation2((d10, e10) => {
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
                    this.observeComponentCreation2((x9, y9) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                    }, Column);
                    this.observeComponentCreation2((v9, w9) => {
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
                    this.observeComponentCreation2((t9, u9) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }));
                        Column.justifyContent(FlexAlign.Center);
                        Column.direction(Direction.Ltr);
                    }, Column);
                    this.observeComponentCreation2((j9, k9) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((r9, s9) => {
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
                                this.observeComponentCreation2((l9, m9) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((p9, q9) => {
                                                SymbolGlyph.create(this.itemEditableDialog.value);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((n9, o9) => {
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
        let e9 = this.getUIContext().getHostContext();
        this.mainWindowStage = e9.windowStage.getMainWindowSync();
        let f9 = this.mainWindowStage.getWindowProperties();
        let g9 = f9.windowRect;
        if (px2vp(g9.height) > this.screenWidth) {
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
function getNumberByResource(y8, z8) {
    try {
        let d9 = resourceManager.getSystemResourceManager().getNumber(y8);
        if (d9 === 0) {
            return z8;
        }
        else {
            return d9;
        }
    }
    catch (a9) {
        let b9 = a9.code;
        let c9 = a9.message;
        hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${b9},message:${c9}`);
        return 0;
    }
}
class Util {
    static isSymbolResource(w8) {
        if (w8 === undefined) {
            return true;
        }
        if (!Util.isResourceType(w8)) {
            return false;
        }
        let x8 = w8;
        return x8.type === Util.RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(v8) {
        if (!v8) {
            return false;
        }
        return typeof v8 !== 'string';
    }
}
Util.RESOURCE_TYPE_SYMBOL = 40000;

export default {
    EditableLeftIconType: EditableLeftIconType,
    EditableTitleBar: EditableTitleBar,
};
