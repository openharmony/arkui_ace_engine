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

(function (b8) {
    b8[b8['Back'] = 0] = 'Back';
    b8[b8['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;

(function (a8) {
    a8[a8['Image'] = 0] = 'Image';
    a8[a8['Icon'] = 1] = 'Icon';
    a8[a8['LeftIcon'] = 2] = 'LeftIcon';
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
// 'sys.float.titlebar_title_tertiary_size' id,value: 20vp
const TITLE_F = getNumberByResource(125831095, TITLE_VP);
// 'sys.float.titlebar_subheader_size' id,value: 14vp
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
    constructor(z7) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = z7;
    }
    applyGesture(y7) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            y7.addGesture(new LongPressGestureHandler({
                repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (y7) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            y7.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class EditableTitleBar extends ViewPU {
    constructor(s7, t7, u7, v7 = -1, w7 = undefined, x7) {
        super(s7, u7, v7, x7);
        if (typeof w7 === 'function') {
            this.paramsGenerator_ = w7;
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
        this.__editableTitleBarTheme = new ObservedPropertyObjectPU(new EditableTitleBarTheme(),
            this, 'editableTitleBarTheme');
        this.addProvidedVar('editableTitleBarTheme', this.__editableTitleBarTheme, false);
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(t7.contentMargin, this, 'contentMargin');
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
        this.setInitiallyProvidedValue(t7);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r7) {
        if (r7.leftIconStyle !== undefined) {
            this.leftIconStyle = r7.leftIconStyle;
        }
        if (r7.title !== undefined) {
            this.title = r7.title;
        }
        if (r7.subtitle !== undefined) {
            this.subtitle = r7.subtitle;
        }
        if (r7.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = r7.isSaveIconRequired;
        }
        if (r7.imageItem !== undefined) {
            this.imageItem = r7.imageItem;
        }
        if (r7.menuItems !== undefined) {
            this.menuItems = r7.menuItems;
        }
        if (r7.options !== undefined) {
            this.options = r7.options;
        }
        if (r7.onSave !== undefined) {
            this.onSave = r7.onSave;
        }
        if (r7.onCancel !== undefined) {
            this.onCancel = r7.onCancel;
        }
        if (r7.constraintWidth !== undefined) {
            this.constraintWidth = r7.constraintWidth;
        }
        if (r7.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = r7.isFollowingSystemFontScale;
        }
        if (r7.maxFontScale !== undefined) {
            this.maxFontScale = r7.maxFontScale;
        }
        if (r7.systemFontScale !== undefined) {
            this.systemFontScale = r7.systemFontScale;
        }
        if (r7.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = r7.editableTitleBarTheme;
        }
        if (r7.titleBarMargin !== undefined) {
            this.titleBarMargin = r7.titleBarMargin;
        }
        if (r7.fontSize !== undefined) {
            this.fontSize = r7.fontSize;
        }
    }
    updateStateVars(q7) {
        this.__contentMargin.reset(q7.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(p7) {
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(p7);
        this.__contentMargin.purgeDependencyOnElmtId(p7);
        this.__titleBarMargin.purgeDependencyOnElmtId(p7);
        this.__fontSize.purgeDependencyOnElmtId(p7);
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
    set editableTitleBarTheme(o7) {
        this.__editableTitleBarTheme.set(o7);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(n7) {
        this.__contentMargin.set(n7);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(m7) {
        this.__titleBarMargin.set(m7);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(l7) {
        this.__fontSize.set(l7);
    }
    onWillApplyTheme(k7) {
        this.editableTitleBarTheme.iconColor = k7.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = k7.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = k7.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = k7.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = k7.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = k7.colors.interactiveFocus;
    }
    aboutToAppear() {
        try {
            let j7 = this.getUIContext();
            this.isFollowingSystemFontScale = j7.isFollowingSystemFontScale();
            this.maxFontScale = j7.getMaxFontScale();
        }
        catch (g7) {
            let h7 = g7.code;
            let i7 = g7.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${h7}, message: ${i7}`);
        }
    }
    decideFontScale() {
        let f7 = this.getUIContext();
        this.systemFontScale = f7.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    initialRender() {
        this.observeComponentCreation2((d7, e7) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes ? this.options.safeAreaTypes : [SafeAreaType.SYSTEM], this.options.safeAreaEdges ? this.options.safeAreaEdges : [SafeAreaEdge.TOP]);
        }, Flex);
        this.observeComponentCreation2((b7, c7) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((z6, a7) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((x6, y6) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
            Row.accessibilityGroup(true);
        }, Row);
        this.observeComponentCreation2((t6, u6) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v6, w6) => {
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
        this.observeComponentCreation2((r6, s6) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)();
        Row.pop();
        Row.pop();
        this.observeComponentCreation2((p6, q6) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)();
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    imageItemLayout(k6 = null) {
        {
            this.observeComponentCreation2((l6, m6) => {
                if (m6) {
                    let n6 = new ImageMenuItem(this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, l6, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 245, col: 5 });
                    ViewPU.create(n6);
                    let o6 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    n6.paramsGenerator_ = o6;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(l6, {});
                }
            }, { name: 'ImageMenuItem' });
        }
    }
    leftIconLayout(z5 = null) {
        this.observeComponentCreation2((a6, b6) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((g6, h6) => {
                            if (h6) {
                                let i6 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.getUIContext()?.getRouter()?.back()
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    useSymbol: true,
                                }, undefined, g6, () => { }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 254, col: 7 });
                                ViewPU.create(i6);
                                let j6 = () => {
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
                                i6.paramsGenerator_ = j6;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(g6, {
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
                        this.observeComponentCreation2((c6, d6) => {
                            if (d6) {
                                let e6 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    useSymbol: true,
                                }, undefined, c6, () => { }, {
                                    page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 265, col: 7 });
                                ViewPU.create(e6);
                                let f6 = () => {
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
                                e6.paramsGenerator_ = f6;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(c6, {
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
    titleLayout(m5 = null) {
        this.observeComponentCreation2((x5, y5) => {
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
        this.observeComponentCreation2((v5, w5) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((t5, u5) => {
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
        this.observeComponentCreation2((n5, o5) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r5, s5) => {
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
                    this.observeComponentCreation2((p5, q5) => {
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
    rightMenuItemsLayout(h5 = null) {
        {
            this.observeComponentCreation2((i5, j5) => {
                if (j5) {
                    let k5 = new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                    }, undefined, i5, () => { }, {
                        page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 330, col: 5 });
                    ViewPU.create(k5);
                    let l5 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize
                        };
                    };
                    k5.paramsGenerator_ = l5;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(i5, {
                        fontSize: this.fontSize
                    });
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }
    onPlaceChildren(d5, e5, f5) {
        e5.forEach((g5) => {
            g5.layout({ x: 0, y: 0 });
        });
    }
    onMeasureSize(y4, z4, a5) {
        let b5 = { width: y4.width, height: y4.height };
        this.fontSize = this.decideFontScale();
        z4.forEach((c5) => {
            b5.height = c5.measure(a5).height;
            b5.width = Number(a5.maxWidth);
        });
        return b5;
    }
    rerender() {
        this.updateDirtyElements();
    }
}
EditableTitleBar.maxCountOfExtraItems = 3;
EditableTitleBar.maxOtherCountOfExtraItems = 2;
EditableTitleBar.commonZero = 0;
EditableTitleBar.noneColor = '#00000000';
// 'sys.float.titlebar_default_height' id,value: 56vp
EditableTitleBar.defaultHeight = getNumberByResource(125831115, DEFAULT_TITLE_BAR_HEIGHT);
// 'sys.float.padding_level1' id,value: 2vp
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
    constructor(s4, t4, u4, v4 = -1, w4 = undefined, x4) {
        super(s4, u4, v4, x4);
        if (typeof w4 === 'function') {
            this.paramsGenerator_ = w4;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(t4.fontSize, this, 'fontSize');
        this.setInitiallyProvidedValue(t4);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r4) {
        if (r4.menuItems !== undefined) {
            this.menuItems = r4.menuItems;
        }
        if (r4.onSave !== undefined) {
            this.onSave = r4.onSave;
        }
        if (r4.isSaveEnabled !== undefined) {
            this.isSaveEnabled = r4.isSaveEnabled;
        }
        if (r4.fontSize === undefined) {
            this.__fontSize.set(1);
        }
    }
    updateStateVars(q4) {
        this.__fontSize.reset(q4.fontSize);
    }
    purgeVariableDependenciesOnElmtId(p4) {
        this.__fontSize.purgeDependencyOnElmtId(p4);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(o4) {
        this.__fontSize.set(o4);
    }
    initialRender() {
        this.observeComponentCreation2((m4, n4) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((k4, l4) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((z3, a4) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b4, c4) => {
                        ForEach.create();
                        const d4 = e4 => {
                            const f4 = e4;
                            {
                                this.observeComponentCreation2((g4, h4) => {
                                    if (h4) {
                                        let i4 = new ImageMenuItem(this, {
                                            item: f4,
                                            attribute: ItemType.Icon,
                                            fontSize: this.fontSize,
                                        }, undefined, g4, () => { }, {
                                            page: 'library/src/main/ets/components/EditableTitleBar.ets',
                                            line: 370, col: 15 });
                                        ViewPU.create(i4);
                                        let j4 = () => {
                                            return {
                                                item: f4,
                                                attribute: ItemType.Icon,
                                                fontSize: this.fontSize
                                            };
                                        };
                                        i4.paramsGenerator_ = j4;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(g4, {
                                            fontSize: this.fontSize
                                        });
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(b4, this.menuItems.slice(EditableTitleBar.commonZero,
                            this.isSaveEnabled ? EditableTitleBar.maxOtherCountOfExtraItems :
                            EditableTitleBar.maxCountOfExtraItems), d4);
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
        this.observeComponentCreation2((t3, u3) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((v3, w3) => {
                            if (w3) {
                                let x3 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                    useSymbol: true,
                                }, undefined, v3, () => { }, {
                                    page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 378, col: 11 });
                                ViewPU.create(x3);
                                let y3 = () => {
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
                                x3.paramsGenerator_ = y3;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(v3, {
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
    constructor(l3, m3, n3, o3 = -1, p3 = undefined, q3) {
        super(l3, n3, o3, q3);
        if (typeof p3 === 'function') {
            this.paramsGenerator_ = p3;
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
        this.useSymbol = false;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(m3.fontSize, this, 'fontSize');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__editableTitleBarTheme = this.initializeConsume('editableTitleBarTheme', 'editableTitleBarTheme');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let r3 = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                    useSymbol: this.useSymbol,
                }, undefined, -1, () => { }, {
                    page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 417, col: 14 });
                r3.setController(this.dialogController);
                ViewPU.create(r3);
                let s3 = () => {
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
                r3.paramsGenerator_ = s3;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, "buttonGestureModifier");
        this.setInitiallyProvidedValue(m3);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(k3) {
        if (k3.item !== undefined) {
            this.item = k3.item;
        }
        if (k3.attribute !== undefined) {
            this.attribute = k3.attribute;
        }
        if (k3.callbackId !== undefined) {
            this.callbackId = k3.callbackId;
        }
        if (k3.minFontSize !== undefined) {
            this.minFontSize = k3.minFontSize;
        }
        if (k3.maxFontSize !== undefined) {
            this.maxFontSize = k3.maxFontSize;
        }
        if (k3.longPressTime !== undefined) {
            this.longPressTime = k3.longPressTime;
        }
        if (k3.useSymbol !== undefined) {
            this.useSymbol = k3.useSymbol;
        }
        if (k3.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (k3.isOnFocus !== undefined) {
            this.isOnFocus = k3.isOnFocus;
        }
        if (k3.isOnHover !== undefined) {
            this.isOnHover = k3.isOnHover;
        }
        if (k3.isOnClick !== undefined) {
            this.isOnClick = k3.isOnClick;
        }
        if (k3.dialogController !== undefined) {
            this.dialogController = k3.dialogController;
        }
        if (k3.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = k3.buttonGestureModifier;
        }
    }
    updateStateVars(j3) {
        this.__fontSize.reset(j3.fontSize);
    }
    purgeVariableDependenciesOnElmtId(i3) {
        this.__fontSize.purgeDependencyOnElmtId(i3);
        this.__isOnFocus.purgeDependencyOnElmtId(i3);
        this.__isOnHover.purgeDependencyOnElmtId(i3);
        this.__isOnClick.purgeDependencyOnElmtId(i3);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(i3);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(i3);
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
    set fontSize(h3) {
        this.__fontSize.set(h3);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(g3) {
        this.__isOnFocus.set(g3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(f3) {
        this.__isOnHover.set(f3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(e3) {
        this.__isOnClick.set(e3);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(d3) {
        this.__editableTitleBarTheme.set(d3);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(c3) {
        this.__buttonGestureModifier.set(c3);
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
    touchEventAction(b3) {
        if (!this.item.isEnabled) {
            return;
        }
        if (b3.type === TouchType.Down) {
            this.isOnClick = true;
        }
        if (b3.type === TouchType.Up || b3.type === TouchType.Cancel) {
            if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close();
            }
            this.isOnClick = false;
        }
    }
    keyEventAction(a3) {
        if (!this.item.isEnabled) {
            return;
        }
        if (a3.keyCode !== KeyCode.KEYCODE_ENTER && a3.keyCode !== KeyCode.KEYCODE_SPACE) {
            return;
        }
        if (a3.type === KeyType.Down) {
            this.isOnClick = true;
        }
        if (a3.type === KeyType.Up) {
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
    toStringFormat(v2) {
        if (typeof v2 === 'string' || typeof v2 === 'undefined') {
            return v2;
        }
        else {
            let w2 = '';
            try {
                w2 = getContext()?.resourceManager?.getStringSync(v2);
            }
            catch (x2) {
                let y2 = x2?.code;
                let z2 = x2?.message;
                hilog.error(0x3900, 'Ace', `Faild to subHeader toStringFormat, code: ${y2}, message: ${z2}`);
            }
            return w2;
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
            return this.toStringFormat({
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_back'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
        } else if (this.item.accessibilityText) {
            return this.toStringFormat(this.item.accessibilityText);
        } else if (this.item.label) {
            return this.toStringFormat(this.item.label);
        }
        return ' ';
    }
    getRightIconAccessibilityLevel() {
        if (this.item.accessibilityLevel === 'yes') {
            return 'yes';
        }
        else if (this.item.accessibilityLevel === 'no') {
            return 'no';
        }
        return 'auto';
    }
    getAccessibilityDescription() {
        if (this.item.accessibilityDescription && this.item.accessibilityDescription !== '') {
            return this.toStringFormat(this.item.accessibilityDescription);
        }
        return '';
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
                if (this.item.isEnabled === undefined) {
                    this.item.isEnabled = true;
                }
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
            Button.accessibilityDescription(this.getAccessibilityDescription());
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
                        SymbolGlyph.accessibilityLevel(this.getRightIconAccessibilityLevel());
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
                        Image.accessibilityLevel(this.getRightIconAccessibilityLevel());
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
/**
 * get resource size
 *
 * @param resourceId resource id
 * @return resource size
 */
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