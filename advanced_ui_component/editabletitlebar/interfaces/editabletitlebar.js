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

(function (w30) {
    w30[w30['Back'] = 0] = 'Back';
    w30[w30['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;

(function (j30) {
    j30[j30['Image'] = 0] = 'Image';
    j30[j30['Icon'] = 1] = 'Icon';
    j30[j30['LeftIcon'] = 2] = 'LeftIcon';
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
    "id": -1,
    "type": 20000,
    params: ['sys.media.ohos_ic_compnent_titlebar_back'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
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
    constructor(g30) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = g30;
    }
    applyGesture(f25) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            f25.addGesture(new LongPressGestureHandler({
                repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (f25) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            f25.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class EditableTitleBar extends ViewPU {
    constructor(i21, t21, t24, z24 = -1, d25 = undefined, e25) {
        super(i21, t24, z24, e25);
        if (typeof d25 === 'function') {
            this.paramsGenerator_ = d25;
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
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(t21.contentMargin, this, 'contentMargin');
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
        this.setInitiallyProvidedValue(t21);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(f21) {
        if (f21.leftIconStyle !== undefined) {
            this.leftIconStyle = f21.leftIconStyle;
        }
        if (f21.title !== undefined) {
            this.title = f21.title;
        }
        if (f21.subtitle !== undefined) {
            this.subtitle = f21.subtitle;
        }
        if (f21.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = f21.isSaveIconRequired;
        }
        if (f21.imageItem !== undefined) {
            this.imageItem = f21.imageItem;
        }
        if (f21.menuItems !== undefined) {
            this.menuItems = f21.menuItems;
        }
        if (f21.options !== undefined) {
            this.options = f21.options;
        }
        if (f21.onSave !== undefined) {
            this.onSave = f21.onSave;
        }
        if (f21.onCancel !== undefined) {
            this.onCancel = f21.onCancel;
        }
        if (f21.constraintWidth !== undefined) {
            this.constraintWidth = f21.constraintWidth;
        }
        if (f21.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = f21.isFollowingSystemFontScale;
        }
        if (f21.maxFontScale !== undefined) {
            this.maxFontScale = f21.maxFontScale;
        }
        if (f21.systemFontScale !== undefined) {
            this.systemFontScale = f21.systemFontScale;
        }
        if (f21.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = f21.editableTitleBarTheme;
        }
        if (f21.titleBarMargin !== undefined) {
            this.titleBarMargin = f21.titleBarMargin;
        }
        if (f21.fontSize !== undefined) {
            this.fontSize = f21.fontSize;
        }
    }
    updateStateVars(y20) {
        this.__contentMargin.reset(y20.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(e20) {
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(e20);
        this.__contentMargin.purgeDependencyOnElmtId(e20);
        this.__titleBarMargin.purgeDependencyOnElmtId(e20);
        this.__fontSize.purgeDependencyOnElmtId(e20);
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
    set editableTitleBarTheme(g19) {
        this.__editableTitleBarTheme.set(g19);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(f19) {
        this.__contentMargin.set(f19);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(e19) {
        this.__titleBarMargin.set(e19);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(y18) {
        this.__fontSize.set(y18);
    }
    onWillApplyTheme(v15) {
        this.editableTitleBarTheme.iconColor = v15.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = v15.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = v15.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = v15.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = v15.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = v15.colors.interactiveFocus;
    }
    aboutToAppear() {
        try {
            let u15 = this.getUIContext();
            this.isFollowingSystemFontScale = u15.isFollowingSystemFontScale();
            this.maxFontScale = u15.getMaxFontScale();
        }
        catch (r15) {
            let s15 = r15.code;
            let t15 = r15.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${s15}, message: ${t15}`);
        }
    }
    decideFontScale() {
        let q15 = this.getUIContext();
        this.systemFontScale = q15.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    initialRender() {
        this.observeComponentCreation2((o15, p15) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes ? this.options.safeAreaTypes :
                [SafeAreaType.SYSTEM], this.options.safeAreaEdges ? this.options.safeAreaEdges : [SafeAreaEdge.TOP]);
        }, Flex);
        this.observeComponentCreation2((m15, n15) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((k15, l15) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((i15, j15) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
            Row.accessibilityGroup(true);
        }, Row);
        this.observeComponentCreation2((e15, f15) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g15, h15) => {
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
        this.observeComponentCreation2((c15, d15) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)();
        Row.pop();
        Row.pop();
        this.observeComponentCreation2((a15, b15) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)();
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    imageItemLayout(v14 = null) {
        {
            this.observeComponentCreation2((w14, x14) => {
                if (x14) {
                    let y14 = new ImageMenuItem(this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, w14, () => {
                    }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 249, col: 5 });
                    ViewPU.create(y14);
                    let z14 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    y14.paramsGenerator_ = z14;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(w14, {});
                }
            }, { name: 'ImageMenuItem' });
        }
    }
    leftIconLayout(j14 = null) {
        this.observeComponentCreation2((k14, m14) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((r14, s14) => {
                            if (s14) {
                                let t14 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() :
                                        this.getUIContext()?.getRouter()?.back()
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                }, undefined, r14, () => {
                                }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 258, col: 7 });
                                ViewPU.create(t14);
                                let u14 = () => {
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
                                t14.paramsGenerator_ = u14;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(r14, {
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
                        this.observeComponentCreation2((n14, o14) => {
                            if (o14) {
                                let p14 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                }, undefined, n14, () => {
                                }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 268, col: 7 });
                                ViewPU.create(p14);
                                let q14 = () => {
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
                                p14.paramsGenerator_ = q14;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(n14, {
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
    titleLayout(s13 = null) {
        this.observeComponentCreation2((g14, h14) => {
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
        this.observeComponentCreation2((d14, e14) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((b14, c14) => {
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
        this.observeComponentCreation2((t13, u13) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x13, y13) => {
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
                    this.observeComponentCreation2((v13, w13) => {
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
    rightMenuItemsLayout(n13 = null) {
        {
            this.observeComponentCreation2((o13, p13) => {
                if (p13) {
                    let q13 = new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                    }, undefined, o13, () => {
                    }, { page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 332, col: 5 });
                    ViewPU.create(q13);
                    let r13 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize
                        };
                    };
                    q13.paramsGenerator_ = r13;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(o13, {
                        fontSize: this.fontSize
                    });
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }
    onPlaceChildren(j13, k13, l13) {
        k13.forEach((m13) => {
            m13.layout({ x: 0, y: 0 });
        });
    }
    onMeasureSize(c13, d13, g13) {
        let h13 = { width: c13.width, height: c13.height };
        this.fontSize = this.decideFontScale();
        d13.forEach((i13) => {
            h13.height = i13.measure(g13).height;
            h13.width = Number(g13.maxWidth);
        });
        return h13;
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
    constructor(w12, x12, y12, z12 = -1, a13 = undefined, b13) {
        super(w12, y12, z12, b13);
        if (typeof a13 === 'function') {
            this.paramsGenerator_ = a13;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(x12.fontSize, this, 'fontSize');
        this.setInitiallyProvidedValue(x12);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(v12) {
        if (v12.menuItems !== undefined) {
            this.menuItems = v12.menuItems;
        }
        if (v12.onSave !== undefined) {
            this.onSave = v12.onSave;
        }
        if (v12.isSaveEnabled !== undefined) {
            this.isSaveEnabled = v12.isSaveEnabled;
        }
        if (v12.fontSize === undefined) {
            this.__fontSize.set(1);
        }
    }
    updateStateVars(u12) {
        this.__fontSize.reset(u12.fontSize);
    }
    purgeVariableDependenciesOnElmtId(t12) {
        this.__fontSize.purgeDependencyOnElmtId(t12);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(s12) {
        this.__fontSize.set(s12);
    }
    initialRender() {
        this.observeComponentCreation2((p12, q12) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((m12, n12) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((a12, c12) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d12, e12) => {
                        ForEach.create();
                        const f12 = g12 => {
                            const h12 = g12;
                            {
                                this.observeComponentCreation2((i12, j12) => {
                                    if (j12) {
                                        let k12 = new ImageMenuItem(this, {
                                            item: h12,
                                            attribute: ItemType.Icon,
                                            fontSize: this.fontSize,
                                        }, undefined, i12, () => {
                                        }, { page: 'library/src/main/ets/components/EditableTitleBar.ets',
                                            line: 372, col: 15 });
                                        ViewPU.create(k12);
                                        let l12 = () => {
                                            return {
                                                item: h12,
                                                attribute: ItemType.Icon,
                                                fontSize: this.fontSize
                                            };
                                        };
                                        k12.paramsGenerator_ = l12;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(i12, {
                                            fontSize: this.fontSize
                                        });
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(d12, this.menuItems.slice(EditableTitleBar.commonZero,
                            this.isSaveEnabled ? EditableTitleBar.maxOtherCountOfExtraItems :
                            EditableTitleBar.maxCountOfExtraItems), f12);
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
        this.observeComponentCreation2((q11, s11) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((t11, w11) => {
                            if (w11) {
                                let x11 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                }, undefined, t11, () => {}, {
                                    page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 380, col: 11 });
                                ViewPU.create(x11);
                                let y11 = () => {
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
                                x11.paramsGenerator_ = y11;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(t11, {
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
    constructor(f11, g11, h11, i11 = -1, j11 = undefined, m11) {
        super(f11, h11, i11, m11);
        if (typeof j11 === 'function') {
            this.paramsGenerator_ = j11;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(g11.fontSize, this, 'fontSize');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__editableTitleBarTheme = this.initializeConsume('editableTitleBarTheme', 'editableTitleBarTheme');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let n11 = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, {
                    page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 417, col: 14 });
                n11.setController(this.dialogController);
                ViewPU.create(n11);
                let o11 = () => {
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
                n11.paramsGenerator_ = o11;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController),
            this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(g11);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(e11) {
        if (e11.item !== undefined) {
            this.item = e11.item;
        }
        if (e11.attribute !== undefined) {
            this.attribute = e11.attribute;
        }
        if (e11.callbackId !== undefined) {
            this.callbackId = e11.callbackId;
        }
        if (e11.minFontSize !== undefined) {
            this.minFontSize = e11.minFontSize;
        }
        if (e11.maxFontSize !== undefined) {
            this.maxFontSize = e11.maxFontSize;
        }
        if (e11.longPressTime !== undefined) {
            this.longPressTime = e11.longPressTime;
        }
        if (e11.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (e11.isOnFocus !== undefined) {
            this.isOnFocus = e11.isOnFocus;
        }
        if (e11.isOnHover !== undefined) {
            this.isOnHover = e11.isOnHover;
        }
        if (e11.isOnClick !== undefined) {
            this.isOnClick = e11.isOnClick;
        }
        if (e11.dialogController !== undefined) {
            this.dialogController = e11.dialogController;
        }
        if (e11.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = e11.buttonGestureModifier;
        }
    }
    updateStateVars(c11) {
        this.__fontSize.reset(c11.fontSize);
    }
    purgeVariableDependenciesOnElmtId(b11) {
        this.__fontSize.purgeDependencyOnElmtId(b11);
        this.__isOnFocus.purgeDependencyOnElmtId(b11);
        this.__isOnHover.purgeDependencyOnElmtId(b11);
        this.__isOnClick.purgeDependencyOnElmtId(b11);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(b11);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(b11);
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
    set fontSize(a11) {
        this.__fontSize.set(a11);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(z10) {
        this.__isOnFocus.set(z10);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(y10) {
        this.__isOnHover.set(y10);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(x10) {
        this.__isOnClick.set(x10);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(w10) {
        this.__editableTitleBarTheme.set(w10);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(v10) {
        this.__buttonGestureModifier.set(v10);
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
    touchEventAction(u10) {
        if (!this.item.isEnabled) {
            return;
        }
        if (u10.type === TouchType.Down) {
            this.isOnClick = true;
        }
        if (u10.type === TouchType.Up || u10.type === TouchType.Cancel) {
            if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close();
            }
            this.isOnClick = false;
        }
    }
    keyEventAction(t10) {
        if (!this.item.isEnabled) {
            return;
        }
        if (t10.keyCode !== KeyCode.KEYCODE_ENTER && t10.keyCode !== KeyCode.KEYCODE_SPACE) {
            return;
        }
        if (t10.type === KeyType.Down) {
            this.isOnClick = true;
        }
        if (t10.type === KeyType.Up) {
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
    toStringFormat(o10) {
        if (typeof o10 === 'string' || typeof o10 === 'undefined') {
            return o10;
        }
        else {
            let p10 = '';
            try {
                p10 = getContext()?.resourceManager?.getStringSync(o10);
            }
            catch (q10) {
                let r10 = q10?.code;
                let s10 = q10?.message;
                hilog.error(0x3900, 'Ace', `Faild to subHeader toStringFormat, code: ${r10}, message: ${s10}`);
            }
            return p10;
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
        } else if (this.item.label) {
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
    IconBuilder(y9 = null) {
        this.observeComponentCreation2((j10, k10) => {
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
            Button.onHover((n10) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = n10;
            });
            Button.onKeyEvent((m10) => {
                this.keyEventAction(m10);
            });
            Button.onTouch((l10) => {
                this.touchEventAction(l10);
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
        this.observeComponentCreation2((z9, a10) => {
            If.create();
            if (this.item.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h10, i10) => {
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
                    this.observeComponentCreation2((b10, c10) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((f10, g10) => {
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
                                this.observeComponentCreation2((d10, e10) => {
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
    ImageBuilder(o9 = null) {
        this.observeComponentCreation2((w9, x9) => {
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
        this.observeComponentCreation2((u9, v9) => {
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
        this.observeComponentCreation2((p9, q9) => {
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
            Button.onHover((t9) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = t9;
            });
            Button.onKeyEvent((s9) => {
                this.keyEventAction(s9);
            });
            Button.onTouch((r9) => {
                this.touchEventAction(r9);
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
        this.observeComponentCreation2((m9, n9) => {
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
    constructor(g9, h9, i9, j9 = -1, k9 = undefined, l9) {
        super(g9, i9, j9, l9);
        if (typeof k9 === 'function') {
            this.paramsGenerator_ = k9;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(h9.fontSize, this, 'fontSize');
        this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
        this.setInitiallyProvidedValue(h9);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(f9) {
        if (f9.itemEditableDialog !== undefined) {
            this.itemEditableDialog = f9.itemEditableDialog;
        }
        if (f9.callbackId !== undefined) {
            this.callbackId = f9.callbackId;
        }
        if (f9.textEditableTitleBarDialog !== undefined) {
            this.textEditableTitleBarDialog = f9.textEditableTitleBarDialog;
        }
        if (f9.mainWindowStage !== undefined) {
            this.mainWindowStage = f9.mainWindowStage;
        }
        if (f9.controller !== undefined) {
            this.controller = f9.controller;
        }
        if (f9.minFontSize !== undefined) {
            this.minFontSize = f9.minFontSize;
        }
        if (f9.maxFontSize !== undefined) {
            this.maxFontSize = f9.maxFontSize;
        }
        if (f9.screenWidth !== undefined) {
            this.screenWidth = f9.screenWidth;
        }
        if (f9.verticalScreenLines !== undefined) {
            this.verticalScreenLines = f9.verticalScreenLines;
        }
        if (f9.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = f9.horizontalsScreenLines;
        }
        if (f9.cancel !== undefined) {
            this.cancel = f9.cancel;
        }
        if (f9.confirm !== undefined) {
            this.confirm = f9.confirm;
        }
        if (f9.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (f9.maxLines !== undefined) {
            this.maxLines = f9.maxLines;
        }
    }
    updateStateVars(e9) {
        this.__fontSize.reset(e9.fontSize);
    }
    purgeVariableDependenciesOnElmtId(d9) {
        this.__mainWindow.purgeDependencyOnElmtId(d9);
        this.__fontSize.purgeDependencyOnElmtId(d9);
        this.__maxLines.purgeDependencyOnElmtId(d9);
        this.__windowStandardHeight.purgeDependencyOnElmtId(d9);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(c9) {
        this.controller = c9;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(b9) {
        this.__mainWindow.set(b9);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(a9) {
        this.__fontSize.set(a9);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(z8) {
        this.__maxLines.set(z8);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(y8) {
        this.__windowStandardHeight.set(y8);
    }
    initialRender() {
        this.observeComponentCreation2((k5, l5) => {
            If.create();
            if (this.textEditableTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w8, x8) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ?
                            MAX_DIALOG : MIN_DIALOG });
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
                    this.observeComponentCreation2((m8, n8) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((u8, v8) => {
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
                                    SymbolGlyph.direction(Direction.Ltr);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((o8, p8) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((s8, t8) => {
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
                                                SymbolGlyph.direction(Direction.Ltr);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((q8, r8) => {
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
                    this.observeComponentCreation2((k8, l8) => {
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
                    this.observeComponentCreation2((i8, j8) => {
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
                    this.observeComponentCreation2((g8, h8) => {
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
                        Column.direction(Direction.Ltr);
                    }, Column);
                    this.observeComponentCreation2((f6, j6) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((e8, f8) => {
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
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((o6, o7) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((c8, d8) => {
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
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((r7, a8) => {
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
        let x4 = this.getUIContext().getHostContext();
        this.mainWindowStage = x4.windowStage.getMainWindowSync();
        let a5 = this.mainWindowStage.getWindowProperties();
        let d5 = a5.windowRect;
        if (px2vp(d5.height) > this.screenWidth) {
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
function getNumberByResource(s3, y3) {
    try {
        let q4 = resourceManager.getSystemResourceManager().getNumber(s3);
        if (q4 === 0) {
            return y3;
        }
        else {
            return q4;
        }
    }
    catch (d4) {
        let f4 = d4.code;
        let j4 = d4.message;
        hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${f4},message:${j4}`);
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
        let r3 = i1;
        return r3.type === Util.RESOURCE_TYPE_SYMBOL;
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