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

(function (u7) {
    u7[u7['Back'] = 0] = 'Back';
    u7[u7['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;

(function (t7) {
    t7[t7['Image'] = 0] = 'Image';
    t7[t7['Icon'] = 1] = 'Icon';
    t7[t7['LeftIcon'] = 2] = 'LeftIcon';
})(ItemType || (ItemType = {}));

const PUBLIC_CANCEL = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.xmark'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const PUBLIC_OK = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.checkmark'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const PUBLIC_BACK = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.chevron_backward'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
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
        this.iconColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_icon_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.iconBackgroundColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_icon_background_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.iconBackgroundPressedColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_icon_background_pressed_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.iconBackgroundHoverColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_icon_background_hover_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.iconBackgroundFocusOutlineColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_icon_background_focus_outline_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.titleColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_title_tertiary_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.subTitleColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_subheader_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
    }
}
class ButtonGestureModifier {
    constructor(s7) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = s7;
    }
    applyGesture(r7) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            r7.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (r7) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            r7.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class EditableTitleBar extends ViewPU {
    constructor(l7, m7, n7, o7 = -1, p7 = undefined, q7) {
        super(l7, n7, o7, q7);
        if (typeof p7 === 'function') {
            this.paramsGenerator_ = p7;
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
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(m7.contentMargin, this, 'contentMargin');
        this.__titleBarMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.resource({
                'id': -1,
                'type': 10002,
                params: ['sys.float.margin_left'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }),
            end: LengthMetrics.resource({
                'id': -1,
                'type': 10002,
                params: ['sys.float.margin_left'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }),
        }, this, 'titleBarMargin');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(m7);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(k7) {
        if (k7.leftIconStyle !== undefined) {
            this.leftIconStyle = k7.leftIconStyle;
        }
        if (k7.title !== undefined) {
            this.title = k7.title;
        }
        if (k7.subtitle !== undefined) {
            this.subtitle = k7.subtitle;
        }
        if (k7.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = k7.isSaveIconRequired;
        }
        if (k7.imageItem !== undefined) {
            this.imageItem = k7.imageItem;
        }
        if (k7.menuItems !== undefined) {
            this.menuItems = k7.menuItems;
        }
        if (k7.options !== undefined) {
            this.options = k7.options;
        }
        if (k7.onSave !== undefined) {
            this.onSave = k7.onSave;
        }
        if (k7.onCancel !== undefined) {
            this.onCancel = k7.onCancel;
        }
        if (k7.constraintWidth !== undefined) {
            this.constraintWidth = k7.constraintWidth;
        }
        if (k7.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = k7.isFollowingSystemFontScale;
        }
        if (k7.maxFontScale !== undefined) {
            this.maxFontScale = k7.maxFontScale;
        }
        if (k7.systemFontScale !== undefined) {
            this.systemFontScale = k7.systemFontScale;
        }
        if (k7.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = k7.editableTitleBarTheme;
        }
        if (k7.titleBarMargin !== undefined) {
            this.titleBarMargin = k7.titleBarMargin;
        }
        if (k7.fontSize !== undefined) {
            this.fontSize = k7.fontSize;
        }
    }
    updateStateVars(j7) {
        this.__contentMargin.reset(j7.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(i7) {
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(i7);
        this.__contentMargin.purgeDependencyOnElmtId(i7);
        this.__titleBarMargin.purgeDependencyOnElmtId(i7);
        this.__fontSize.purgeDependencyOnElmtId(i7);
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
    set editableTitleBarTheme(h7) {
        this.__editableTitleBarTheme.set(h7);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(g7) {
        this.__contentMargin.set(g7);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(f7) {
        this.__titleBarMargin.set(f7);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(e7) {
        this.__fontSize.set(e7);
    }
    onWillApplyTheme(d7) {
        this.editableTitleBarTheme.iconColor = d7.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = d7.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = d7.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = d7.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = d7.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = d7.colors.interactiveFocus;
    }
    aboutToAppear() {
        try {
            let c7 = this.getUIContext();
            this.isFollowingSystemFontScale = c7.isFollowingSystemFontScale();
            this.maxFontScale = c7.getMaxFontScale();
        }
        catch (z6) {
            let a7 = z6.code;
            let b7 = z6.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${a7}, message: ${b7}`);
        }
    }
    decideFontScale() {
        let y6 = this.getUIContext();
        this.systemFontScale = y6.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    initialRender() {
        this.observeComponentCreation2((w6, x6) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes ? this.options.safeAreaTypes : [SafeAreaType.SYSTEM], this.options.safeAreaEdges ? this.options.safeAreaEdges : [SafeAreaEdge.TOP]);
        }, Flex);
        this.observeComponentCreation2((u6, v6) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((s6, t6) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((o6, p6) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q6, r6) => {
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
        this.observeComponentCreation2((m6, n6) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((k6, l6) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)();
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    imageItemLayout(f6 = null) {
        {
            this.observeComponentCreation2((g6, h6) => {
                if (h6) {
                    let i6 = new ImageMenuItem(this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, g6, () => { }, {
                        page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 237, col: 5 });
                    ViewPU.create(i6);
                    let j6 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    i6.paramsGenerator_ = j6;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(g6, {});
                }
            }, { name: 'ImageMenuItem' });
        }
    }
    leftIconLayout(u5 = null) {
        this.observeComponentCreation2((v5, w5) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((b6, c6) => {
                            if (c6) {
                                let d6 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() :
                                        this.getUIContext()?.getRouter()?.back()
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    useSymbol: true,
                                }, undefined, b6, () => { }, {
                                    page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 246, col: 7 });
                                ViewPU.create(d6);
                                let e6 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: () => this.onCancel ? this.onCancel() : this.getUIContext()?.getRouter()?.back()
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon,
                                        useSymbol: true
                                    };
                                };
                                d6.paramsGenerator_ = e6;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(b6, {
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
                        this.observeComponentCreation2((x5, y5) => {
                            if (y5) {
                                let z5 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    useSymbol: true,
                                }, undefined, x5, () => { }, {
                                    page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 257, col: 7 });
                                ViewPU.create(z5);
                                let a6 = () => {
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
                                z5.paramsGenerator_ = a6;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(x5, {
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
    titleLayout(h5 = null) {
        this.observeComponentCreation2((s5, t5) => {
            Column.create();
            Column.height(EditableTitleBar.totalHeight);
            Column.justifyContent(FlexAlign.Center);
            Column.margin({
                start: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_space_horizontal'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((q5, r5) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((o5, p5) => {
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
        this.observeComponentCreation2((i5, j5) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m5, n5) => {
                        Row.create();
                        Row.margin({
                            top: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level1'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((k5, l5) => {
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
    rightMenuItemsLayout(c5 = null) {
        {
            this.observeComponentCreation2((d5, e5) => {
                if (e5) {
                    let f5 = new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                    }, undefined, d5, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 322, col: 5 });
                    ViewPU.create(f5);
                    let g5 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize
                        };
                    };
                    f5.paramsGenerator_ = g5;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(d5, {
                        fontSize: this.fontSize
                    });
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }
    onPlaceChildren(y4, z4, a5) {
        z4.forEach((b5) => {
            b5.layout({ x: 0, y: 0 });
        });
    }
    onMeasureSize(t4, u4, v4) {
        let w4 = { width: t4.width, height: t4.height };
        this.fontSize = this.decideFontScale();
        u4.forEach((x4) => {
            w4.height = x4.measure(v4).height;
            w4.width = Number(v4.maxWidth);
        });
        return w4;
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
EditableTitleBar.totalHeight = EditableTitleBar.defaultHeight === EditableTitleBar.commonZero ?
    DEFAULT_TITLE_BAR_HEIGHT : EditableTitleBar.defaultHeight;
EditableTitleBar.titlePadding = EditableTitleBar.defaultTitlePadding === EditableTitleBar.commonZero ?
    DEFAULT_TITLE_PADDING : EditableTitleBar.defaultTitlePadding;
EditableTitleBar.maxMainTitleHeight =
    (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_MAIN_TITLE_PERCENT;
EditableTitleBar.maxSubTitleHeight =
    (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_SUB_TITLE_PERCENT;
class EditableTitleBarMenuSection extends ViewPU {
    constructor(n4, o4, p4, q4 = -1, r4 = undefined, s4) {
        super(n4, p4, q4, s4);
        if (typeof r4 === 'function') {
            this.paramsGenerator_ = r4;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(o4.fontSize, this, 'fontSize');
        this.setInitiallyProvidedValue(o4);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(m4) {
        if (m4.menuItems !== undefined) {
            this.menuItems = m4.menuItems;
        }
        if (m4.onSave !== undefined) {
            this.onSave = m4.onSave;
        }
        if (m4.isSaveEnabled !== undefined) {
            this.isSaveEnabled = m4.isSaveEnabled;
        }
        if (m4.fontSize === undefined) {
            this.__fontSize.set(1);
        }
    }
    updateStateVars(l4) {
        this.__fontSize.reset(l4.fontSize);
    }
    purgeVariableDependenciesOnElmtId(k4) {
        this.__fontSize.purgeDependencyOnElmtId(k4);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(j4) {
        this.__fontSize.set(j4);
    }
    initialRender() {
        this.observeComponentCreation2((h4, i4) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((f4, g4) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((u3, v3) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w3, x3) => {
                        ForEach.create();
                        const y3 = z3 => {
                            const a4 = z3;
                            {
                                this.observeComponentCreation2((b4, c4) => {
                                    if (c4) {
                                        let d4 = new ImageMenuItem(this, {
                                            item: a4,
                                            attribute: ItemType.Icon,
                                            fontSize: this.fontSize,
                                        }, undefined, b4, () => { }, {
                                            page: 'library/src/main/ets/components/EditableTitleBar.ets',
                                            line: 362, col: 15 });
                                        ViewPU.create(d4);
                                        let e4 = () => {
                                            return {
                                                item: a4,
                                                attribute: ItemType.Icon,
                                                fontSize: this.fontSize
                                            };
                                        };
                                        d4.paramsGenerator_ = e4;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(b4, {
                                            fontSize: this.fontSize
                                        });
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(w3, this.menuItems.slice(EditableTitleBar.commonZero,
                            this.isSaveEnabled ? EditableTitleBar.maxOtherCountOfExtraItems :
                            EditableTitleBar.maxCountOfExtraItems), y3);
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
        this.observeComponentCreation2((o3, p3) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((q3, r3) => {
                            if (r3) {
                                let s3 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                    useSymbol: true,
                                }, undefined, q3, () => { }, {
                                    page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 370, col: 11 });
                                ViewPU.create(s3);
                                let t3 = () => {
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
                                s3.paramsGenerator_ = t3;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(q3, {
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
    constructor(g3, h3, i3, j3 = -1, k3 = undefined, l3) {
        super(g3, i3, j3, l3);
        if (typeof k3 === 'function') {
            this.paramsGenerator_ = k3;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(h3.fontSize, this, 'fontSize');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__editableTitleBarTheme = this.initializeConsume('editableTitleBarTheme', 'editableTitleBarTheme');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let m3 = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                    useSymbol: this.useSymbol,
                }, undefined, -1, () => { }, {
                    page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 406, col: 14 });
                m3.setController(this.dialogController);
                ViewPU.create(m3);
                let n3 = () => {
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
                m3.paramsGenerator_ = n3;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, "buttonGestureModifier");
        this.setInitiallyProvidedValue(h3);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(f3) {
        if (f3.item !== undefined) {
            this.item = f3.item;
        }
        if (f3.attribute !== undefined) {
            this.attribute = f3.attribute;
        }
        if (f3.callbackId !== undefined) {
            this.callbackId = f3.callbackId;
        }
        if (f3.minFontSize !== undefined) {
            this.minFontSize = f3.minFontSize;
        }
        if (f3.maxFontSize !== undefined) {
            this.maxFontSize = f3.maxFontSize;
        }
        if (f3.longPressTime !== undefined) {
            this.longPressTime = f3.longPressTime;
        }
        if (f3.useSymbol !== undefined) {
            this.useSymbol = f3.useSymbol;
        }
        if (f3.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (f3.isOnFocus !== undefined) {
            this.isOnFocus = f3.isOnFocus;
        }
        if (f3.isOnHover !== undefined) {
            this.isOnHover = f3.isOnHover;
        }
        if (f3.isOnClick !== undefined) {
            this.isOnClick = f3.isOnClick;
        }
        if (f3.dialogController !== undefined) {
            this.dialogController = f3.dialogController;
        }
        if (f3.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = f3.buttonGestureModifier;
        }
    }
    updateStateVars(e3) {
        this.__fontSize.reset(e3.fontSize);
    }
    purgeVariableDependenciesOnElmtId(d3) {
        this.__fontSize.purgeDependencyOnElmtId(d3);
        this.__isOnFocus.purgeDependencyOnElmtId(d3);
        this.__isOnHover.purgeDependencyOnElmtId(d3);
        this.__isOnClick.purgeDependencyOnElmtId(d3);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(d3);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(d3);
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
    set fontSize(c3) {
        this.__fontSize.set(c3);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(b3) {
        this.__isOnFocus.set(b3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(a3) {
        this.__isOnHover.set(a3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(z2) {
        this.__isOnClick.set(z2);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(y2) {
        this.__editableTitleBarTheme.set(y2);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(x2) {
        this.__buttonGestureModifier.set(x2);
    }
    textDialog() {
        if (this.item.value === PUBLIC_OK) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_save'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else if (this.item.value === PUBLIC_CANCEL) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_cancel'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else if (this.item.value === PUBLIC_BACK) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_back'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else {
            return this.item.label ? this.item.label : '';
        }
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    touchEventAction(w2) {
        if (!this.item.isEnabled) {
            return;
        }
        if (w2.type === TouchType.Down) {
            this.isOnClick = true;
        }
        if (w2.type === TouchType.Up || w2.type === TouchType.Cancel) {
            if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close();
            }
            this.isOnClick = false;
        }
    }
    keyEventAction(v2) {
        if (!this.item.isEnabled) {
            return;
        }
        if (v2.keyCode !== KeyCode.KEYCODE_ENTER && v2.keyCode !== KeyCode.KEYCODE_SPACE) {
            return;
        }
        if (v2.type === KeyType.Down) {
            this.isOnClick = true;
        }
        if (v2.type === KeyType.Up) {
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
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.titlebar_icon_background_pressed_color'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else if (this.isOnHover) {
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.titlebar_icon_background_hover_color'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else {
            return EditableTitleBar.noneColor;
        }
    }
    getAccessibilityReadText() {
        if (this.item.value === PUBLIC_OK) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_save'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else if (this.item.value === PUBLIC_CANCEL) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_cancel'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else if (this.item.value === PUBLIC_BACK) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_back'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else if (this.item.label) {
            return this.item.label;
        }
        return undefined;
    }
    IconBuilder(j2 = null) {
        this.observeComponentCreation2((q2, r2) => {
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.width({
                'id': -1,
                'type': 10002,
                params: ['sys.float.titlebar_icon_background_width'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.height({
                'id': -1,
                'type': 10002,
                params: ['sys.float.titlebar_icon_background_height'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            Button.borderRadius({
                'id': -1,
                'type': 10002,
                params: ['sys.float.titlebar_icon_background_shape'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.margin({
                start: this.attribute === ItemType.LeftIcon ? LengthMetrics.vp(EditableTitleBar.commonZero) :
                    LengthMetrics.resource({
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.titlebar_icon_background_space_horizontal'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }),
            });
            Button.focusOnTouch(true);
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(this.getBgColor());
            ViewStackProcessor.visualState('focused');
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_shape'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_focus_outline_weight'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                color: this.editableTitleBarTheme.iconBackgroundFocusOutlineColor,
                style: BorderStyle.Solid,
            });
            ViewStackProcessor.visualState('normal');
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_shape'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('pressed');
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_shape'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
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
            Button.onHover((u2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = u2;
            });
            Button.onKeyEvent((t2) => {
                this.keyEventAction(t2);
            });
            Button.onTouch((s2) => {
                this.touchEventAction(s2);
            });
            Button.onClick(() => {
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
        }, Button);
        this.observeComponentCreation2((k2, l2) => {
            If.create();
            if (this.useSymbol) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o2, p2) => {
                        SymbolGlyph.create(this.item.value);
                        SymbolGlyph.fontColor([this.editableTitleBarTheme.iconColor]);
                        SymbolGlyph.width({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_width'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.height({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_height'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
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
                    this.observeComponentCreation2((m2, n2) => {
                        Image.create(this.item.value);
                        Image.fillColor(this.editableTitleBarTheme.iconColor);
                        Image.matchTextDirection(this.item.value === PUBLIC_BACK ? true : false);
                        Image.width({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_width'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Image.height({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_height'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
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
    ImageBuilder(v1 = null) {
        this.observeComponentCreation2((h2, i2) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                start: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_space_horizontal'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }),
            });
        }, Stack);
        this.observeComponentCreation2((b2, c2) => {
            If.create();
            if (this.useSymbol) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f2, g2) => {
                        SymbolGlyph.create(this.item.value);
                        SymbolGlyph.width({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_background_width'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.height({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_background_height'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.borderRadius({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.corner_radius_level10'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.focusable(false);
                        SymbolGlyph.enabled(this.item.isEnabled);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((d2, e2) => {
                        Image.create(this.item.value);
                        Image.width({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_background_width'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Image.height({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_background_height'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Image.borderRadius({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.corner_radius_level10'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Image.focusable(false);
                        Image.enabled(this.item.isEnabled);
                        Image.objectFit(ImageFit.Cover);
                    }, Image);
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((w1, x1) => {
            Button.createWithLabel({ type: ButtonType.Circle });
            Button.width({
                'id': -1,
                'type': 10002,
                params: ['sys.float.titlebar_icon_background_width'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.height({
                'id': -1,
                'type': 10002,
                params: ['sys.float.titlebar_icon_background_height'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(EditableTitleBar.noneColor);
            ViewStackProcessor.visualState('pressed');
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_shape'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('normal');
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_shape'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('focused');
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_shape'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_focus_outline_weight'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
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
            Button.onHover((a2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = a2;
            });
            Button.onKeyEvent((z1) => {
                this.keyEventAction(z1);
            });
            Button.onTouch((y1) => {
                this.touchEventAction(y1);
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
        this.observeComponentCreation2((t1, u1) => {
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
    constructor(n1, o1, p1, q1 = -1, r1 = undefined, s1) {
        super(n1, p1, q1, s1);
        if (typeof r1 === 'function') {
            this.paramsGenerator_ = r1;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(o1.fontSize, this, 'fontSize');
        this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
        this.setInitiallyProvidedValue(o1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(m1) {
        if (m1.itemEditableDialog !== undefined) {
            this.itemEditableDialog = m1.itemEditableDialog;
        }
        if (m1.callbackId !== undefined) {
            this.callbackId = m1.callbackId;
        }
        if (m1.textEditableTitleBarDialog !== undefined) {
            this.textEditableTitleBarDialog = m1.textEditableTitleBarDialog;
        }
        if (m1.mainWindowStage !== undefined) {
            this.mainWindowStage = m1.mainWindowStage;
        }
        if (m1.controller !== undefined) {
            this.controller = m1.controller;
        }
        if (m1.minFontSize !== undefined) {
            this.minFontSize = m1.minFontSize;
        }
        if (m1.maxFontSize !== undefined) {
            this.maxFontSize = m1.maxFontSize;
        }
        if (m1.screenWidth !== undefined) {
            this.screenWidth = m1.screenWidth;
        }
        if (m1.verticalScreenLines !== undefined) {
            this.verticalScreenLines = m1.verticalScreenLines;
        }
        if (m1.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = m1.horizontalsScreenLines;
        }
        if (m1.useSymbol !== undefined) {
            this.useSymbol = m1.useSymbol;
        }
        if (m1.cancel !== undefined) {
            this.cancel = m1.cancel;
        }
        if (m1.confirm !== undefined) {
            this.confirm = m1.confirm;
        }
        if (m1.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (m1.maxLines !== undefined) {
            this.maxLines = m1.maxLines;
        }
    }
    updateStateVars(l1) {
        this.__fontSize.reset(l1.fontSize);
    }
    purgeVariableDependenciesOnElmtId(k1) {
        this.__mainWindow.purgeDependencyOnElmtId(k1);
        this.__fontSize.purgeDependencyOnElmtId(k1);
        this.__maxLines.purgeDependencyOnElmtId(k1);
        this.__windowStandardHeight.purgeDependencyOnElmtId(k1);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(j1) {
        this.controller = j1;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(i1) {
        this.__mainWindow.set(i1);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(h1) {
        this.__fontSize.set(h1);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(g1) {
        this.__maxLines.set(g1);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(f1) {
        this.__windowStandardHeight.set(f1);
    }
    initialRender() {
        this.observeComponentCreation2((j, k) => {
            If.create();
            if (this.textEditableTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d1, e1) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.corner_radius_level10'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        }));
                    }, Column);
                    this.observeComponentCreation2((x, y) => {
                        If.create();
                        if (this.useSymbol) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((b1, c1) => {
                                    SymbolGlyph.create(this.itemEditableDialog.value);
                                    SymbolGlyph.width(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.height(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.margin({
                                        top: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.padding_level24'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        bottom: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.padding_level8'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                    });
                                    SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((z, a1) => {
                                    Image.create(this.itemEditableDialog.value);
                                    Image.width(IMAGE_SIZE);
                                    Image.height(IMAGE_SIZE);
                                    Image.margin({
                                        top: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.padding_level24'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        bottom: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.padding_level8'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                    });
                                    Image.fillColor({
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((v, w) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level4'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            right: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level4'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            bottom: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level12'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                        });
                    }, Column);
                    this.observeComponentCreation2((t, u) => {
                        Text.create(this.textEditableTitleBarDialog);
                        Text.fontSize(TEXT_EDITABLE_DIALOG);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(this.maxLines);
                        Text.width('100%');
                        Text.textAlign(TextAlign.Center);
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.font_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
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
                        Column.borderRadius(({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.corner_radius_level10'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        }));
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((l, m) => {
                        If.create();
                        if (this.useSymbol) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((p, q) => {
                                    SymbolGlyph.create(this.itemEditableDialog.value);
                                    SymbolGlyph.width(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.height(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((n, o) => {
                                    Image.create(this.itemEditableDialog.value);
                                    Image.width(IMAGE_SIZE);
                                    Image.height(IMAGE_SIZE);
                                    Image.fillColor({
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
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