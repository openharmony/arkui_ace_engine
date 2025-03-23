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
(function (q67) {
    q67[q67['Back'] = 0] = 'Back';
    q67[q67['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (p67) {
    p67[p67['Image'] = 0] = 'Image';
    p67[p67['Icon'] = 1] = 'Icon';
    p67[p67['LeftIcon'] = 2] = 'LeftIcon';
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
    constructor(o67) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = o67;
    }
    applyGesture(n67) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            n67.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (n67) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            n67.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class EditableTitleBar extends ViewPU {
    constructor(h67, i67, j67, k67 = -1, l67 = undefined, m67) {
        super(h67, j67, k67, m67);
        if (typeof l67 === 'function') {
            this.paramsGenerator_ = l67;
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
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(i67.contentMargin, this, 'contentMargin');
        this.__titleBarMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
        }, this, 'titleBarMargin');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(i67);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(g67) {
        if (g67.leftIconStyle !== undefined) {
            this.leftIconStyle = g67.leftIconStyle;
        }
        if (g67.title !== undefined) {
            this.title = g67.title;
        }
        if (g67.subtitle !== undefined) {
            this.subtitle = g67.subtitle;
        }
        if (g67.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = g67.isSaveIconRequired;
        }
        if (g67.imageItem !== undefined) {
            this.imageItem = g67.imageItem;
        }
        if (g67.menuItems !== undefined) {
            this.menuItems = g67.menuItems;
        }
        if (g67.options !== undefined) {
            this.options = g67.options;
        }
        if (g67.onSave !== undefined) {
            this.onSave = g67.onSave;
        }
        if (g67.onCancel !== undefined) {
            this.onCancel = g67.onCancel;
        }
        if (g67.constraintWidth !== undefined) {
            this.constraintWidth = g67.constraintWidth;
        }
        if (g67.leftIconDefaultFocus !== undefined) {
            this.leftIconDefaultFocus = g67.leftIconDefaultFocus;
        }
        if (g67.saveIconDefaultFocus !== undefined) {
            this.saveIconDefaultFocus = g67.saveIconDefaultFocus;
        }
        if (g67.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = g67.isFollowingSystemFontScale;
        }
        if (g67.maxFontScale !== undefined) {
            this.maxFontScale = g67.maxFontScale;
        }
        if (g67.systemFontScale !== undefined) {
            this.systemFontScale = g67.systemFontScale;
        }
        if (g67.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = g67.editableTitleBarTheme;
        }
        if (g67.titleBarMargin !== undefined) {
            this.titleBarMargin = g67.titleBarMargin;
        }
        if (g67.fontSize !== undefined) {
            this.fontSize = g67.fontSize;
        }
    }
    updateStateVars(f67) {
        this.__contentMargin.reset(f67.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(e67) {
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(e67);
        this.__contentMargin.purgeDependencyOnElmtId(e67);
        this.__titleBarMargin.purgeDependencyOnElmtId(e67);
        this.__fontSize.purgeDependencyOnElmtId(e67);
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
    set editableTitleBarTheme(d67) {
        this.__editableTitleBarTheme.set(d67);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(c67) {
        this.__contentMargin.set(c67);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(b67) {
        this.__titleBarMargin.set(b67);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(a67) {
        this.__fontSize.set(a67);
    }
    onWillApplyTheme(z66) {
        this.editableTitleBarTheme.iconColor = z66.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = z66.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = z66.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = z66.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = z66.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = z66.colors.interactiveFocus;
    }
    aboutToAppear() {
        try {
            let y66 = this.getUIContext();
            this.isFollowingSystemFontScale = y66.isFollowingSystemFontScale();
            this.maxFontScale = y66.getMaxFontScale();
        }
        catch (v66) {
            let w66 = v66.code;
            let x66 = v66.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${w66}, message: ${x66}`);
        }
    }
    decideFontScale() {
        let u66 = this.getUIContext();
        this.systemFontScale = u66.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    initialRender() {
        this.observeComponentCreation2((s66, t66) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(
                this.options.backgroundBlurStyle ?? BlurStyle.NONE, undefined, { disableSystemAdaptation: true });
            Flex.expandSafeArea(this.options.safeAreaTypes ? this.options.safeAreaTypes : [SafeAreaType.SYSTEM], this.options.safeAreaEdges ? this.options.safeAreaEdges : [SafeAreaEdge.TOP]);
        }, Flex);
        this.observeComponentCreation2((q66, r66) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((o66, p66) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((m66, n66) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
            Row.accessibilityGroup(true);
            Row.accessibilityDescription({
                'id': -1,
                'type': 10003,
                params: ['sys.string.subheader_accessibility_title'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
        }, Row);
        this.observeComponentCreation2((i66, j66) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k66, l66) => {
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
        this.observeComponentCreation2((g66, h66) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)();
        Row.pop();
        Row.pop();
        this.observeComponentCreation2((e66, f66) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)();
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    imageItemLayout(z65 = null) {
        {
            this.observeComponentCreation2((a66, b66) => {
                if (b66) {
                    let c66 = new ImageMenuItem(this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, a66, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 253, col: 5 });
                    ViewPU.create(c66);
                    let i1 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    c66.paramsGenerator_ = i1;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(a66, {});
                }
            }, { name: 'ImageMenuItem' });
        }
    }
    leftIconLayout(o65 = null) {
        this.observeComponentCreation2((p65, q65) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((v65, w65) => {
                            if (w65) {
                                let x65 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.getUIContext()?.getRouter()?.back(),
                                        defaultFocus: this.leftIconDefaultFocus
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    imageMenuItemId: `BackMenuItem_${this.getUniqueId()}`
                                }, undefined, v65, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 262, col: 7 });
                                ViewPU.create(x65);
                                let h1 = () => {
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
                                x65.paramsGenerator_ = h1;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(v65, {});
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((r65, s65) => {
                            if (s65) {
                                let t65 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                        defaultFocus: this.leftIconDefaultFocus
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    imageMenuItemId: `CancelMenuItem_${this.getUniqueId()}`
                                }, undefined, r65, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 274, col: 7 });
                                ViewPU.create(t65);
                                let g1 = () => {
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
                                t65.paramsGenerator_ = g1;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(r65, {});
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
        }, If);
        If.pop();
    }
    titleLayout(b65 = null) {
        this.observeComponentCreation2((m65, n65) => {
            Column.create();
            Column.height(EditableTitleBar.totalHeight);
            Column.justifyContent(FlexAlign.Center);
            Column.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((k65, l65) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((i65, j65) => {
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
        this.observeComponentCreation2((c65, d65) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g65, h65) => {
                        Row.create();
                        Row.margin({
                            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((e65, f65) => {
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
    rightMenuItemsLayout(w64 = null) {
        {
            this.observeComponentCreation2((x64, y64) => {
                if (y64) {
                    let z64 = new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                        parentUniqueId: this.getUniqueId(),
                        saveIconDefaultFocus: this.saveIconDefaultFocus
                    }, undefined, x64, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 340, col: 5 });
                    ViewPU.create(z64);
                    let f1 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize,
                            parentUniqueId: this.getUniqueId(),
                            saveIconDefaultFocus: this.saveIconDefaultFocus
                        };
                    };
                    z64.paramsGenerator_ = f1;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(x64, {
                        fontSize: this.fontSize,
                        parentUniqueId: this.getUniqueId()
                    });
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }
    onPlaceChildren(s64, t64, u64) {
        t64.forEach((v64) => {
            v64.layout({ x: 0, y: 0 });
        });
    }
    onMeasureSize(n64, o64, p64) {
        let q64 = { width: n64.width, height: n64.height };
        this.fontSize = this.decideFontScale();
        o64.forEach((r64) => {
            q64.height = r64.measure(p64).height;
            q64.width = Number(p64.maxWidth);
        });
        return q64;
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
    constructor(h64, i64, j64, k64 = -1, l64 = undefined, m64) {
        super(h64, j64, k64, m64);
        if (typeof l64 === 'function') {
            this.paramsGenerator_ = l64;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.saveIconDefaultFocus = false;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(i64.fontSize, this, 'fontSize');
        this.__parentUniqueId = new SynchedPropertySimpleOneWayPU(i64.parentUniqueId, this, 'parentUniqueId');
        this.setInitiallyProvidedValue(i64);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(g64) {
        if (g64.menuItems !== undefined) {
            this.menuItems = g64.menuItems;
        }
        if (g64.onSave !== undefined) {
            this.onSave = g64.onSave;
        }
        if (g64.isSaveEnabled !== undefined) {
            this.isSaveEnabled = g64.isSaveEnabled;
        }
        if (g64.saveIconDefaultFocus !== undefined) {
            this.saveIconDefaultFocus = g64.saveIconDefaultFocus;
        }
        if (g64.fontSize === undefined) {
            this.__fontSize.set(1);
        }
    }
    updateStateVars(f64) {
        this.__fontSize.reset(f64.fontSize);
        this.__parentUniqueId.reset(f64.parentUniqueId);
    }
    purgeVariableDependenciesOnElmtId(e64) {
        this.__fontSize.purgeDependencyOnElmtId(e64);
        this.__parentUniqueId.purgeDependencyOnElmtId(e64);
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
    set fontSize(d64) {
        this.__fontSize.set(d64);
    }
    get parentUniqueId() {
        return this.__parentUniqueId.get();
    }
    set parentUniqueId(c64) {
        this.__parentUniqueId.set(c64);
    }
    initialRender() {
        this.observeComponentCreation2((a64, b64) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((y63, z63) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((m63, n63) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o63, p63) => {
                        ForEach.create();
                        const d1 = (r63, s63) => {
                            const t63 = r63;
                            {
                                this.observeComponentCreation2((u63, v63) => {
                                    if (v63) {
                                        let w63 = new ImageMenuItem(this, {
                                            item: t63,
                                            attribute: ItemType.Icon,
                                            imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${s63}`
                                        }, undefined, u63, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 384, col: 15 });
                                        ViewPU.create(w63);
                                        let e1 = () => {
                                            return {
                                                item: t63,
                                                attribute: ItemType.Icon,
                                                imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${s63}`
                                            };
                                        };
                                        w63.paramsGenerator_ = e1;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(u63, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(o63, this.menuItems.slice(EditableTitleBar.commonZero, this.isSaveEnabled ?
                        EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems), d1, undefined, true, false);
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
        this.observeComponentCreation2((g63, h63) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((i63, j63) => {
                            if (j63) {
                                let k63 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                        defaultFocus: this.saveIconDefaultFocus
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                    imageMenuItemId: `SaveMenuItem_${this.parentUniqueId}`
                                }, undefined, i63, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 392, col: 11 });
                                ViewPU.create(k63);
                                let c1 = () => {
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
                                k63.paramsGenerator_ = c1;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(i63, {});
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
    constructor(y62, z62, a63, b63 = -1, c63 = undefined, d63) {
        super(y62, a63, b63, d63);
        if (typeof c63 === 'function') {
            this.paramsGenerator_ = c63;
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
        this.systemFontScale = 1;
        this.isFollowingSystemFontScale = this.getUIContext().isFollowingSystemFontScale();
        this.maxFontScale = this.getUIContext().getMaxFontScale();
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.imageMenuItemId = undefined;
        this.__editableTitleBarTheme = this.initializeConsume('editableTitleBarTheme', 'editableTitleBarTheme');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let e63 = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 435, col: 14 });
                e63.setController(this.dialogController);
                ViewPU.create(e63);
                let b1 = () => {
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
                e63.paramsGenerator_ = b1;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.envCallback = {
            onConfigurationUpdated: (x) => {
                if (x === undefined || !this.isFollowingSystemFontScale) {
                    this.fontSize = 1;
                    return;
                }
                try {
                    this.fontSize = Math.min(this.maxFontScale, x.fontSizeScale ?? 1);
                    this.buttonGestureModifier.fontSize = this.fontSize;
                }
                catch (y) {
                    let z = y.code;
                    let a1 = y.message;
                    hilog.error(0x3900, 'Ace', `EditableTitleBar environmentCallback error: ${z}, ${a1}`);
                }
            },
            onMemoryLevel: (w) => {
            }
        };
        this.setInitiallyProvidedValue(z62);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(x62) {
        if (x62.item !== undefined) {
            this.item = x62.item;
        }
        if (x62.attribute !== undefined) {
            this.attribute = x62.attribute;
        }
        if (x62.callbackId !== undefined) {
            this.callbackId = x62.callbackId;
        }
        if (x62.minFontSize !== undefined) {
            this.minFontSize = x62.minFontSize;
        }
        if (x62.maxFontSize !== undefined) {
            this.maxFontSize = x62.maxFontSize;
        }
        if (x62.longPressTime !== undefined) {
            this.longPressTime = x62.longPressTime;
        }
        if (x62.systemFontScale !== undefined) {
            this.systemFontScale = x62.systemFontScale;
        }
        if (x62.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = x62.isFollowingSystemFontScale;
        }
        if (x62.maxFontScale !== undefined) {
            this.maxFontScale = x62.maxFontScale;
        }
        if (x62.fontSize !== undefined) {
            this.fontSize = x62.fontSize;
        }
        if (x62.isOnFocus !== undefined) {
            this.isOnFocus = x62.isOnFocus;
        }
        if (x62.isOnHover !== undefined) {
            this.isOnHover = x62.isOnHover;
        }
        if (x62.isOnClick !== undefined) {
            this.isOnClick = x62.isOnClick;
        }
        if (x62.imageMenuItemId !== undefined) {
            this.imageMenuItemId = x62.imageMenuItemId;
        }
        if (x62.dialogController !== undefined) {
            this.dialogController = x62.dialogController;
        }
        if (x62.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = x62.buttonGestureModifier;
        }
        if (x62.envCallback !== undefined) {
            this.envCallback = x62.envCallback;
        }
    }
    updateStateVars(w62) {
    }
    purgeVariableDependenciesOnElmtId(v62) {
        this.__fontSize.purgeDependencyOnElmtId(v62);
        this.__isOnFocus.purgeDependencyOnElmtId(v62);
        this.__isOnHover.purgeDependencyOnElmtId(v62);
        this.__isOnClick.purgeDependencyOnElmtId(v62);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(v62);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(v62);
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
    set fontSize(u62) {
        this.__fontSize.set(u62);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(t62) {
        this.__isOnFocus.set(t62);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(s62) {
        this.__isOnHover.set(s62);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(r62) {
        this.__isOnClick.set(r62);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(q62) {
        this.__editableTitleBarTheme.set(q62);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(p62) {
        this.__buttonGestureModifier.set(p62);
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
    aboutToAppear() {
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        }
        catch (t) {
            let u = t.code;
            let v = t.message;
            hilog.error(0x3900, 'Ace', `EditableTitleBar Faild to get environment param error: ${u}, ${v}`);
        }
        this.fontSize = this.decideFontScale();
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    decideFontScale() {
        try {
            let s = this.getUIContext();
            this.systemFontScale = s.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (p) {
            let q = p.code;
            let r = p.message;
            hilog.error(0x3900, 'EditableTitleBar', `Faild to decideFontScale,cause, code: ${q}, message: ${r}`);
            return 1;
        }
    }
    touchEventAction(o62) {
        if (!this.item.isEnabled) {
            return;
        }
        if (o62.type === TouchType.Down) {
            this.isOnClick = true;
        }
        if (o62.type === TouchType.Up || o62.type === TouchType.Cancel) {
            if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close();
            }
            this.isOnClick = false;
        }
    }
    keyEventAction(n62) {
        if (!this.item.isEnabled) {
            return;
        }
        if (n62.keyCode !== KeyCode.KEYCODE_ENTER && n62.keyCode !== KeyCode.KEYCODE_SPACE) {
            return;
        }
        if (n62.type === KeyType.Down) {
            this.isOnClick = true;
        }
        if (n62.type === KeyType.Up) {
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
    toStringFormat(i62) {
        if (typeof i62 === 'string' || typeof i62 === 'undefined') {
            return i62;
        }
        else {
            let j62 = '';
            try {
                if (i62.id === -1) {
                    j62 = getContext()?.resourceManager?.getStringByNameSync(i62.params?.[0]?.split('.').pop() ?? '');
                }
                else {
                    j62 = getContext()?.resourceManager?.getStringSync(i62);
                }
            }
            catch (k62) {
                let l62 = k62?.code;
                let m62 = k62?.message;
                hilog.error(0x3900, 'Ace', `Faild to EditableTitleBar toStringFormat, code: ${l62}, message: ${m62}`);
            }
            return j62;
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
    IconBuilder(w61 = null) {
        this.observeComponentCreation2((d62, e62) => {
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
            Button.onHover((h62) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = h62;
            });
            Button.onKeyEvent((g62) => {
                this.keyEventAction(g62);
            });
            Button.onTouch((f62) => {
                this.touchEventAction(f62);
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
        this.observeComponentCreation2((x61, y61) => {
            If.create();
            if (this.item.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b62, c62) => {
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
                    this.observeComponentCreation2((z61, a62) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((n, o) => {
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
                                this.observeComponentCreation2((l, m) => {
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
    ImageBuilder(i61 = null) {
        this.observeComponentCreation2((u61, v61) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Stack);
        this.observeComponentCreation2((o61, p61) => {
            Image.create(this.item.value);
            Image.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.focusable(false);
            Image.enabled(this.item.isEnabled);
            Image.objectFit(ImageFit.Cover);
        }, Image);
        this.observeComponentCreation2((j61, k61) => {
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
            Button.onHover((n61) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = n61;
            });
            Button.onKeyEvent((m61) => {
                this.keyEventAction(m61);
            });
            Button.onTouch((l61) => {
                this.touchEventAction(l61);
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
        this.observeComponentCreation2((g61, h61) => {
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
    constructor(a61, b61, c61, d61 = -1, e61 = undefined, f61) {
        super(a61, c61, d61, f61);
        if (typeof e61 === 'function') {
            this.paramsGenerator_ = e61;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(b61.fontSize, this, 'fontSize');
        this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
        this.setInitiallyProvidedValue(b61);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z60) {
        if (z60.itemEditableDialog !== undefined) {
            this.itemEditableDialog = z60.itemEditableDialog;
        }
        if (z60.callbackId !== undefined) {
            this.callbackId = z60.callbackId;
        }
        if (z60.textEditableTitleBarDialog !== undefined) {
            this.textEditableTitleBarDialog = z60.textEditableTitleBarDialog;
        }
        if (z60.mainWindowStage !== undefined) {
            this.mainWindowStage = z60.mainWindowStage;
        }
        if (z60.controller !== undefined) {
            this.controller = z60.controller;
        }
        if (z60.minFontSize !== undefined) {
            this.minFontSize = z60.minFontSize;
        }
        if (z60.maxFontSize !== undefined) {
            this.maxFontSize = z60.maxFontSize;
        }
        if (z60.screenWidth !== undefined) {
            this.screenWidth = z60.screenWidth;
        }
        if (z60.verticalScreenLines !== undefined) {
            this.verticalScreenLines = z60.verticalScreenLines;
        }
        if (z60.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = z60.horizontalsScreenLines;
        }
        if (z60.cancel !== undefined) {
            this.cancel = z60.cancel;
        }
        if (z60.confirm !== undefined) {
            this.confirm = z60.confirm;
        }
        if (z60.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (z60.maxLines !== undefined) {
            this.maxLines = z60.maxLines;
        }
    }
    updateStateVars(y60) {
        this.__fontSize.reset(y60.fontSize);
    }
    purgeVariableDependenciesOnElmtId(x60) {
        this.__mainWindow.purgeDependencyOnElmtId(x60);
        this.__fontSize.purgeDependencyOnElmtId(x60);
        this.__maxLines.purgeDependencyOnElmtId(x60);
        this.__windowStandardHeight.purgeDependencyOnElmtId(x60);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(w60) {
        this.controller = w60;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(v60) {
        this.__mainWindow.set(v60);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(u60) {
        this.__fontSize.set(u60);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(t60) {
        this.__maxLines.set(t60);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(s60) {
        this.__windowStandardHeight.set(s60);
    }
    initialRender() {
        this.observeComponentCreation2((w59, x59) => {
            If.create();
            if (this.textEditableTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q60, r60) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true });
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }));
                    }, Column);
                    this.observeComponentCreation2((k60, l60) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((o60, p60) => {
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
                                this.observeComponentCreation2((m60, n60) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((j, k) => {
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
                                            this.observeComponentCreation2((h, i) => {
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
                    this.observeComponentCreation2((i60, j60) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                    }, Column);
                    this.observeComponentCreation2((g60, h60) => {
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
                    this.observeComponentCreation2((e60, f60) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true });
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }));
                        Column.justifyContent(FlexAlign.Center);
                        Column.direction(Direction.Ltr);
                    }, Column);
                    this.observeComponentCreation2((y59, z59) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((c60, d60) => {
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
                                this.observeComponentCreation2((a60, b60) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((f, g) => {
                                                SymbolGlyph.create(this.itemEditableDialog.value);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((d, e) => {
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
        let t59 = this.getUIContext().getHostContext();
        this.mainWindowStage = t59.windowStage.getMainWindowSync();
        let u59 = this.mainWindowStage.getWindowProperties();
        let v59 = u59.windowRect;
        if (px2vp(v59.height) > this.screenWidth) {
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
function getNumberByResource(n59, o59) {
    try {
        let s59 = resourceManager.getSystemResourceManager().getNumber(n59);
        if (s59 === 0) {
            return o59;
        }
        else {
            return s59;
        }
    }
    catch (p59) {
        let q59 = p59.code;
        let r59 = p59.message;
        hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${q59},message:${r59}`);
        return 0;
    }
}
class Util {
    static isSymbolResource(b) {
        if (!Util.isResourceType(b)) {
            return false;
        }
        let c = b;
        return c.type === Util.RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(a) {
        if (!a) {
            return false;
        }
        if (typeof a === 'string' || typeof a === 'undefined') {
            return false;
        }
        return true;
    }
}
Util.RESOURCE_TYPE_SYMBOL = 40000;

export default {
    EditableLeftIconType: EditableLeftIconType,
    EditableTitleBar: EditableTitleBar,
};
