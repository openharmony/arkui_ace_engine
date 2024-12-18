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

(function (m8) {
    m8[m8['Back'] = 0] = 'Back';
    m8[m8['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (l8) {
    l8[l8['Image'] = 0] = 'Image';
    l8[l8['Icon'] = 1] = 'Icon';
    l8[l8['LeftIcon'] = 2] = 'LeftIcon';
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
const PUBLIC_IMAGE_BACK = {
    'id': -1,
    'type': 20000,
    params: ['sys.media.ohos_ic_compnent_titlebar_back'],
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
    constructor(k8) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = k8;
    }

    applyGesture(j8) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            j8.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (j8) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        } else {
            j8.clearGestures();
        }
    }
}

ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;

export class EditableTitleBar extends ViewPU {
    constructor(d8, e8, f8, g8 = -1, h8 = undefined, i8) {
        super(d8, f8, g8, i8);
        if (typeof h8 === 'function') {
            this.paramsGenerator_ = h8;
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
        this.__editableTitleBarTheme =
            new ObservedPropertyObjectPU(new EditableTitleBarTheme(), this, 'editableTitleBarTheme');
        this.addProvidedVar('editableTitleBarTheme', this.__editableTitleBarTheme, false);
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(e8.contentMargin, this, 'contentMargin');
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
                params: ['sys.float.margin_right'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }),
        }, this, 'titleBarMargin');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(e8);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(c8) {
        if (c8.leftIconStyle !== undefined) {
            this.leftIconStyle = c8.leftIconStyle;
        }
        if (c8.title !== undefined) {
            this.title = c8.title;
        }
        if (c8.subtitle !== undefined) {
            this.subtitle = c8.subtitle;
        }
        if (c8.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = c8.isSaveIconRequired;
        }
        if (c8.imageItem !== undefined) {
            this.imageItem = c8.imageItem;
        }
        if (c8.menuItems !== undefined) {
            this.menuItems = c8.menuItems;
        }
        if (c8.options !== undefined) {
            this.options = c8.options;
        }
        if (c8.onSave !== undefined) {
            this.onSave = c8.onSave;
        }
        if (c8.onCancel !== undefined) {
            this.onCancel = c8.onCancel;
        }
        if (c8.constraintWidth !== undefined) {
            this.constraintWidth = c8.constraintWidth;
        }
        if (c8.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = c8.isFollowingSystemFontScale;
        }
        if (c8.maxFontScale !== undefined) {
            this.maxFontScale = c8.maxFontScale;
        }
        if (c8.systemFontScale !== undefined) {
            this.systemFontScale = c8.systemFontScale;
        }
        if (c8.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = c8.editableTitleBarTheme;
        }
        if (c8.titleBarMargin !== undefined) {
            this.titleBarMargin = c8.titleBarMargin;
        }
        if (c8.fontSize !== undefined) {
            this.fontSize = c8.fontSize;
        }
    }

    updateStateVars(b8) {
        this.__contentMargin.reset(b8.contentMargin);
    }

    purgeVariableDependenciesOnElmtId(a8) {
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(a8);
        this.__contentMargin.purgeDependencyOnElmtId(a8);
        this.__titleBarMargin.purgeDependencyOnElmtId(a8);
        this.__fontSize.purgeDependencyOnElmtId(a8);
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

    set editableTitleBarTheme(z7) {
        this.__editableTitleBarTheme.set(z7);
    }

    get contentMargin() {
        return this.__contentMargin.get();
    }

    set contentMargin(y7) {
        this.__contentMargin.set(y7);
    }

    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }

    set titleBarMargin(x7) {
        this.__titleBarMargin.set(x7);
    }

    get fontSize() {
        return this.__fontSize.get();
    }

    set fontSize(w7) {
        this.__fontSize.set(w7);
    }

    onWillApplyTheme(v7) {
        this.editableTitleBarTheme.iconColor = v7.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = v7.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = v7.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = v7.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = v7.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = v7.colors.interactiveFocus;
    }

    aboutToAppear() {
        try {
            let u7 = this.getUIContext();
            this.isFollowingSystemFontScale = u7.isFollowingSystemFontScale();
            this.maxFontScale = u7.getMaxFontScale();
        } catch (r7) {
            let s7 = r7.code;
            let t7 = r7.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${s7}, message: ${t7}`);
        }
    }

    decideFontScale() {
        let q7 = this.getUIContext();
        this.systemFontScale = q7.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }

    initialRender() {
        this.observeComponentCreation2((o7, p7) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes ? this.options.safeAreaTypes : [SafeAreaType.SYSTEM],
                this.options.safeAreaEdges ? this.options.safeAreaEdges : [SafeAreaEdge.TOP]);
        }, Flex);
        this.observeComponentCreation2((m7, n7) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((k7, l7) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((i7, j7) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n8, o8) => {
                        Row.create();
                        Row.flexShrink(0);
                    }, Row);
                    this.imageItemLayout.bind(this)();
                    Row.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((e7, f7) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((c7, d7) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)();
        Row.pop();
        Row.pop();
        Flex.pop();
    }

    imageItemLayout(v6 = null) {
        {
            this.observeComponentCreation2((w6, x6) => {
                if (x6) {
                    let y6 = new ImageMenuItem(this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, w6, () => {
                    }, { page: 'EditableTitleBar/src/main/ets/components/MainPage.ets', line: 241, col: 5 });
                    ViewPU.create(y6);
                    let z6 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    y6.paramsGenerator_ = z6;
                } else {
                    this.updateStateVarsOfChildByElmtId(w6, {});
                }
            }, { name: 'ImageMenuItem' });
        }
    }

    leftIconLayout(k6 = null) {
        this.observeComponentCreation2((l6, m6) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((r6, s6) => {
                            if (s6) {
                                let t6 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() :
                                        this.getUIContext()?.getRouter()?.back()
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                }, undefined, r6, () => {
                                }, {
                                    page: 'EditableTitleBar/src/main/ets/components/MainPage.ets',
                                    line: 250,
                                    col: 7
                                });
                                ViewPU.create(t6);
                                let u6 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: () => this.onCancel ? this.onCancel() :
                                            this.getUIContext()?.getRouter()?.back()
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon
                                    };
                                };
                                t6.paramsGenerator_ = u6;
                            } else {
                                this.updateStateVarsOfChildByElmtId(r6, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((n6, o6) => {
                            if (o6) {
                                let p6 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                }, undefined, n6, () => {
                                }, {
                                    page: 'EditableTitleBar/src/main/ets/components/MainPage.ets',
                                    line: 260,
                                    col: 7
                                });
                                ViewPU.create(p6);
                                let q6 = () => {
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
                                p6.paramsGenerator_ = q6;
                            } else {
                                this.updateStateVarsOfChildByElmtId(n6, {
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

    titleLayout(x5 = null) {
        this.observeComponentCreation2((i6, j6) => {
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
        this.observeComponentCreation2((g6, h6) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((e6, f6) => {
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
        this.observeComponentCreation2((y5, z5) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c6, d6) => {
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
                    this.observeComponentCreation2((a6, b6) => {
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
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    rightMenuItemsLayout(s5 = null) {
        {
            this.observeComponentCreation2((t5, u5) => {
                if (u5) {
                    let v5 = new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                    }, undefined, t5, () => {
                    }, { page: 'EditableTitleBar/src/main/ets/components/MainPage.ets', line: 324, col: 5 });
                    ViewPU.create(v5);
                    let w5 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize
                        };
                    };
                    v5.paramsGenerator_ = w5;
                } else {
                    this.updateStateVarsOfChildByElmtId(t5, {
                        fontSize: this.fontSize
                    });
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }

    onPlaceChildren(o5, p5, q5) {
        p5.forEach((r5) => {
            r5.layout({ x: 0, y: 0 });
        });
    }

    onMeasureSize(j5, k5, l5) {
        let m5 = { width: j5.width, height: j5.height };
        this.fontSize = this.decideFontScale();
        k5.forEach((n5) => {
            m5.height = n5.measure(l5).height;
            m5.width = Number(l5.maxWidth);
        });
        return m5;
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
EditableTitleBar.totalHeight =
    EditableTitleBar.defaultHeight === EditableTitleBar.commonZero ? DEFAULT_TITLE_BAR_HEIGHT :
    EditableTitleBar.defaultHeight;
EditableTitleBar.titlePadding = EditableTitleBar.defaultTitlePadding === EditableTitleBar.commonZero ?
    DEFAULT_TITLE_PADDING : EditableTitleBar.defaultTitlePadding;
EditableTitleBar.maxMainTitleHeight =
    (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_MAIN_TITLE_PERCENT;
EditableTitleBar.maxSubTitleHeight =
    (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_SUB_TITLE_PERCENT;

class EditableTitleBarMenuSection extends ViewPU {
    constructor(d5, e5, f5, g5 = -1, h5 = undefined, i5) {
        super(d5, f5, g5, i5);
        if (typeof h5 === 'function') {
            this.paramsGenerator_ = h5;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(e5.fontSize, this, 'fontSize');
        this.setInitiallyProvidedValue(e5);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(c5) {
        if (c5.menuItems !== undefined) {
            this.menuItems = c5.menuItems;
        }
        if (c5.onSave !== undefined) {
            this.onSave = c5.onSave;
        }
        if (c5.isSaveEnabled !== undefined) {
            this.isSaveEnabled = c5.isSaveEnabled;
        }
        if (c5.fontSize === undefined) {
            this.__fontSize.set(1);
        }
    }

    updateStateVars(b5) {
        this.__fontSize.reset(b5.fontSize);
    }

    purgeVariableDependenciesOnElmtId(a5) {
        this.__fontSize.purgeDependencyOnElmtId(a5);
    }

    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get fontSize() {
        return this.__fontSize.get();
    }

    set fontSize(z4) {
        this.__fontSize.set(z4);
    }

    initialRender() {
        this.observeComponentCreation2((x4, y4) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((v4, w4) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((k4, l4) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m4, n4) => {
                        ForEach.create();
                        const o4 = p4 => {
                            const q4 = p4;
                            {
                                this.observeComponentCreation2((r4, s4) => {
                                    if (s4) {
                                        let t4 = new ImageMenuItem(this, {
                                            item: q4,
                                            attribute: ItemType.Icon,
                                            fontSize: this.fontSize,
                                        }, undefined, r4, () => {
                                        }, {
                                            page: 'EditableTitleBar/src/main/ets/components/MainPage.ets',
                                            line: 364,
                                            col: 15
                                        });
                                        ViewPU.create(t4);
                                        let u4 = () => {
                                            return {
                                                item: q4,
                                                attribute: ItemType.Icon,
                                                fontSize: this.fontSize
                                            };
                                        };
                                        t4.paramsGenerator_ = u4;
                                    } else {
                                        this.updateStateVarsOfChildByElmtId(r4, {
                                            fontSize: this.fontSize
                                        });
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(m4,
                            this.menuItems.slice(EditableTitleBar.commonZero, this.isSaveEnabled ?
                            EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems), o4);
                    }, ForEach);
                    ForEach.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((e4, f4) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((g4, h4) => {
                            if (h4) {
                                let i4 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                }, undefined, g4, () => {
                                }, {
                                    page: 'EditableTitleBar/src/main/ets/components/MainPage.ets',
                                    line: 372,
                                    col: 11
                                });
                                ViewPU.create(i4);
                                let j4 = () => {
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
                                i4.paramsGenerator_ = j4;
                            } else {
                                this.updateStateVarsOfChildByElmtId(g4, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            } else {
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
    constructor(w3, x3, y3, z3 = -1, a4 = undefined, b4) {
        super(w3, y3, z3, b4);
        if (typeof a4 === 'function') {
            this.paramsGenerator_ = a4;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(x3.fontSize, this, 'fontSize');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__editableTitleBarTheme = this.initializeConsume('editableTitleBarTheme', 'editableTitleBarTheme');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let c4 = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => {
                }, { page: 'EditableTitleBar/src/main/ets/components/MainPage.ets', line: 406, col: 14 });
                c4.setController(this.dialogController);
                ViewPU.create(c4);
                let d4 = () => {
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
                c4.paramsGenerator_ = d4;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier =
            new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this,
                'buttonGestureModifier');
        this.setInitiallyProvidedValue(x3);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(v3) {
        if (v3.item !== undefined) {
            this.item = v3.item;
        }
        if (v3.attribute !== undefined) {
            this.attribute = v3.attribute;
        }
        if (v3.callbackId !== undefined) {
            this.callbackId = v3.callbackId;
        }
        if (v3.minFontSize !== undefined) {
            this.minFontSize = v3.minFontSize;
        }
        if (v3.maxFontSize !== undefined) {
            this.maxFontSize = v3.maxFontSize;
        }
        if (v3.longPressTime !== undefined) {
            this.longPressTime = v3.longPressTime;
        }
        if (v3.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (v3.isOnFocus !== undefined) {
            this.isOnFocus = v3.isOnFocus;
        }
        if (v3.isOnHover !== undefined) {
            this.isOnHover = v3.isOnHover;
        }
        if (v3.isOnClick !== undefined) {
            this.isOnClick = v3.isOnClick;
        }
        if (v3.dialogController !== undefined) {
            this.dialogController = v3.dialogController;
        }
        if (v3.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = v3.buttonGestureModifier;
        }
    }

    updateStateVars(u3) {
        this.__fontSize.reset(u3.fontSize);
    }

    purgeVariableDependenciesOnElmtId(t3) {
        this.__fontSize.purgeDependencyOnElmtId(t3);
        this.__isOnFocus.purgeDependencyOnElmtId(t3);
        this.__isOnHover.purgeDependencyOnElmtId(t3);
        this.__isOnClick.purgeDependencyOnElmtId(t3);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(t3);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(t3);
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

    set fontSize(s3) {
        this.__fontSize.set(s3);
    }

    get isOnFocus() {
        return this.__isOnFocus.get();
    }

    set isOnFocus(r3) {
        this.__isOnFocus.set(r3);
    }

    get isOnHover() {
        return this.__isOnHover.get();
    }

    set isOnHover(q3) {
        this.__isOnHover.set(q3);
    }

    get isOnClick() {
        return this.__isOnClick.get();
    }

    set isOnClick(p3) {
        this.__isOnClick.set(p3);
    }

    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }

    set editableTitleBarTheme(o3) {
        this.__editableTitleBarTheme.set(o3);
    }

    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }

    set buttonGestureModifier(n3) {
        this.__buttonGestureModifier.set(n3);
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
        } else if (this.item.value === PUBLIC_CANCEL) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_cancel'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else if (this.item.value === PUBLIC_BACK) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_back'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else {
            return this.item.label ? this.item.label : '';
        }
    }

    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }

    touchEventAction(m3) {
        if (!this.item.isEnabled) {
            return;
        }
        if (m3.type === TouchType.Down) {
            this.isOnClick = true;
        }
        if (m3.type === TouchType.Up || m3.type === TouchType.Cancel) {
            if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close();
            }
            this.isOnClick = false;
        }
    }

    keyEventAction(l3) {
        if (!this.item.isEnabled) {
            return;
        }
        if (l3.keyCode !== KeyCode.KEYCODE_ENTER && l3.keyCode !== KeyCode.KEYCODE_SPACE) {
            return;
        }
        if (l3.type === KeyType.Down) {
            this.isOnClick = true;
        }
        if (l3.type === KeyType.Up) {
            this.isOnClick = false;
        }
    }

    getBgColor() {
        if (this.isOnClick) {
            return this.editableTitleBarTheme.iconBackgroundPressedColor;
        } else if (this.isOnHover) {
            return this.editableTitleBarTheme.iconBackgroundHoverColor;
        } else {
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
        } else if (this.isOnHover) {
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.titlebar_icon_background_hover_color'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else {
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
        } else if (this.item.value === PUBLIC_CANCEL) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_cancel'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else if (this.item.value === PUBLIC_BACK) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_back'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else if (this.item.label) {
            return this.item.label;
        }
        return undefined;
    }

    IconBuilder(q2 = null) {
        this.observeComponentCreation2((b3, c3) => {
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
            Button.onHover((f3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = f3;
            });
            Button.onKeyEvent((e3) => {
                this.keyEventAction(e3);
            });
            Button.onTouch((d3) => {
                this.touchEventAction(d3);
            });
            Button.onClick(() => {
                if (this.item.isEnabled === undefined) {
                    this.item.isEnabled = true;
                }
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
        }, Button);
        this.observeComponentCreation2((r2, s2) => {
            If.create();
            if (this.item.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z2, a3) => {
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
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((t2, u2) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((x2, y2) => {
                                    SymbolGlyph.create(this.item.value);
                                    SymbolGlyph.fontSize(SYMBOL_SIZE);
                                    SymbolGlyph.fontColor([this.editableTitleBarTheme.iconColor]);
                                    SymbolGlyph.focusable(this.item.isEnabled);
                                    SymbolGlyph.enabled(this.item.isEnabled);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.accessibilityText(this.getAccessibilityReadText());
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((v2, w2) => {
                                    Image.create(this.item.value);
                                    Image.fillColor(this.editableTitleBarTheme.iconColor);
                                    Image.matchTextDirection(this.item.value === PUBLIC_IMAGE_BACK ? true : false);
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
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }

    ImageBuilder(g2 = null) {
        this.observeComponentCreation2((o2, p2) => {
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
        this.observeComponentCreation2((m2, n2) => {
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
        this.observeComponentCreation2((h2, i2) => {
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
            Button.onHover((l2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = l2;
            });
            Button.onKeyEvent((k2) => {
                this.keyEventAction(k2);
            });
            Button.onTouch((j2) => {
                this.touchEventAction(j2);
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
        this.observeComponentCreation2((e2, f2) => {
            If.create();
            if (this.attribute === ItemType.Icon || this.attribute === ItemType.LeftIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconBuilder.bind(this)();
                });
            } else {
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
    constructor(y1, z1, a2, b2 = -1, c2 = undefined, d2) {
        super(y1, a2, b2, d2);
        if (typeof c2 === 'function') {
            this.paramsGenerator_ = c2;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(z1.fontSize, this, 'fontSize');
        this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
        this.setInitiallyProvidedValue(z1);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(x1) {
        if (x1.itemEditableDialog !== undefined) {
            this.itemEditableDialog = x1.itemEditableDialog;
        }
        if (x1.callbackId !== undefined) {
            this.callbackId = x1.callbackId;
        }
        if (x1.textEditableTitleBarDialog !== undefined) {
            this.textEditableTitleBarDialog = x1.textEditableTitleBarDialog;
        }
        if (x1.mainWindowStage !== undefined) {
            this.mainWindowStage = x1.mainWindowStage;
        }
        if (x1.controller !== undefined) {
            this.controller = x1.controller;
        }
        if (x1.minFontSize !== undefined) {
            this.minFontSize = x1.minFontSize;
        }
        if (x1.maxFontSize !== undefined) {
            this.maxFontSize = x1.maxFontSize;
        }
        if (x1.screenWidth !== undefined) {
            this.screenWidth = x1.screenWidth;
        }
        if (x1.verticalScreenLines !== undefined) {
            this.verticalScreenLines = x1.verticalScreenLines;
        }
        if (x1.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = x1.horizontalsScreenLines;
        }
        if (x1.cancel !== undefined) {
            this.cancel = x1.cancel;
        }
        if (x1.confirm !== undefined) {
            this.confirm = x1.confirm;
        }
        if (x1.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (x1.maxLines !== undefined) {
            this.maxLines = x1.maxLines;
        }
    }

    updateStateVars(w1) {
        this.__fontSize.reset(w1.fontSize);
    }

    purgeVariableDependenciesOnElmtId(v1) {
        this.__mainWindow.purgeDependencyOnElmtId(v1);
        this.__fontSize.purgeDependencyOnElmtId(v1);
        this.__maxLines.purgeDependencyOnElmtId(v1);
        this.__windowStandardHeight.purgeDependencyOnElmtId(v1);
    }

    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(u1) {
        this.controller = u1;
    }

    get mainWindow() {
        return this.__mainWindow.get();
    }

    set mainWindow(t1) {
        this.__mainWindow.set(t1);
    }

    get fontSize() {
        return this.__fontSize.get();
    }

    set fontSize(s1) {
        this.__fontSize.set(s1);
    }

    get maxLines() {
        return this.__maxLines.get();
    }

    set maxLines(r1) {
        this.__maxLines.set(r1);
    }

    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }

    set windowStandardHeight(q1) {
        this.__windowStandardHeight.set(q1);
    }

    initialRender() {
        this.observeComponentCreation2((m, n) => {
            If.create();
            if (this.textEditableTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o1, p1) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({
                            minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG
                        });
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
                    this.observeComponentCreation2((e1, f1) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((m1, n1) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemEditableDialog.symbolStyle);
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
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((g1, h1) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((k1, l1) => {
                                                SymbolGlyph.create(this.itemEditableDialog.value);
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
                                                SymbolGlyph.fontColor([{
                                                    'id': -1,
                                                    'type': 10001,
                                                    params: ['sys.color.icon_primary'],
                                                    'bundleName': '__harDefaultBundleName__',
                                                    'moduleName': '__harDefaultModuleName__'
                                                }]);
                                                SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((i1, j1) => {
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
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((c1, d1) => {
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
                    this.observeComponentCreation2((a1, b1) => {
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
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((y, z) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({
                            minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG
                        });
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
                    this.observeComponentCreation2((o, p) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((w, x) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemEditableDialog.symbolStyle);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((q, r) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((u, v) => {
                                                SymbolGlyph.create(this.itemEditableDialog.value);
                                                SymbolGlyph.fontColor([{
                                                    'id': -1,
                                                    'type': 10001,
                                                    params: ['sys.color.icon_primary'],
                                                    'bundleName': '__harDefaultBundleName__',
                                                    'moduleName': '__harDefaultModuleName__'
                                                }]);
                                                SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((s, t) => {
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
        let j = this.getUIContext().getHostContext();
        this.mainWindowStage = j.windowStage.getMainWindowSync();
        let k = this.mainWindowStage.getWindowProperties();
        let l = k.windowRect;
        if (px2vp(l.height) > this.screenWidth) {
            this.maxLines = this.verticalScreenLines;
        } else {
            this.maxLines = this.horizontalsScreenLines;
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

function getNumberByResource(d, e) {
    try {
        let i = resourceManager.getSystemResourceManager().getNumber(d);
        if (i === 0) {
            return e;
        } else {
            return i;
        }
    } catch (f) {
        let g = f.code;
        let h = f.message;
        hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${g},message:${h}`);
        return 0;
    }
}

class Util {
    static isSymbolResource(b) {
        if (b === undefined) {
            return true;
        }
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
        return typeof a !== 'string';
    }
}

Util.RESOURCE_TYPE_SYMBOL = 40000;

export default {
    EditableLeftIconType: EditableLeftIconType,
    EditableTitleBar: EditableTitleBar,
};