/*
 * Copyright (c) 2026-2026 Huawei Device Co., Ltd.
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

var __decorate = (this && this.__decorate) || function (w83, x83, y83, z83) {
    var a84 = arguments.length,
        b84 = a84 < 3 ? x83 : z83 === null ? z83 = Object.getOwnPropertyDescriptor(x83, y83) : z83, c84;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        b84 = Reflect.decorate(w83, x83, y83, z83);
    } else {
        for (var d84 = w83.length - 1; d84 >= 0; d84--) {
            if (c84 = w83[d84]) {
                b84 = (a84 < 3 ? c84(b84) : a84 > 3 ? c84(x83, y83, b84) : c84(x83, y83)) || b84;
            }
        }
    }
    return a84 > 3 && b84 && Object.defineProperty(x83, y83, b84), b84;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
const hilog = requireNapi('hilog');
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const resourceManager = requireNapi('resourceManager');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const emitter = requireNapi('events.emitter');
const promptAction = requireNapi('promptAction');

export var EditableLeftIconTypeV2;
(function (v83) {
    v83[v83['Back'] = 0] = 'Back';
    v83[v83['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconTypeV2 || (EditableLeftIconTypeV2 = {}));
var ItemType;
(function (u83) {
    u83[u83['Image'] = 0] = 'Image';
    u83[u83['Icon'] = 1] = 'Icon';
    u83[u83['LeftIcon'] = 2] = 'LeftIcon';
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
const EVENT_FONT_SIZE_CHANGE = 20001;
let EditableTitleBarTheme = class EditableTitleBarTheme {
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
};
__decorate([
    Trace
], EditableTitleBarTheme.prototype, 'iconColor', void 0);
__decorate([
    Trace
], EditableTitleBarTheme.prototype, 'iconBackgroundColor', void 0);
__decorate([
    Trace
], EditableTitleBarTheme.prototype, 'iconBackgroundPressedColor', void 0);
__decorate([
    Trace
], EditableTitleBarTheme.prototype, 'iconBackgroundHoverColor', void 0);
__decorate([
    Trace
], EditableTitleBarTheme.prototype, 'iconBackgroundFocusOutlineColor', void 0);
__decorate([
    Trace
], EditableTitleBarTheme.prototype, 'titleColor', void 0);
__decorate([
    Trace
], EditableTitleBarTheme.prototype, 'subTitleColor', void 0);
EditableTitleBarTheme = __decorate([
    ObservedV2
], EditableTitleBarTheme);

class ButtonGestureModifier {
    constructor(s83, t83) {
        this.fontSize = 1;
        this.maxFontSize = 3.2;
        this.dialogId = null;
        this.builder = () => {
        };
        this.dialogId = s83;
        this.builder = t83;
    }

    applyGesture(p83) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            p83.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (p83) {
                        promptAction.openCustomDialog({
                            builder: this.builder,
                            maskColor: Color.Transparent,
                            isModal: true,
                            backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
                            backgroundColor: Color.Transparent,
                            shadow: ShadowStyle.OUTER_DEFAULT_LG,
                            cornerRadius: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.corner_radius_level10'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            width: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG,
                        }).then((r83) => {
                            this.dialogId = r83;
                        }).catch((q83) => {
                            hilog.error(0x3900, 'EditableTitleBarV2', `Failed to open dialog, error: ${q83.message}`);
                        });
                    }
                })
                .onActionEnd(() => {
                    if (this.dialogId !== null) {
                        promptAction.closeCustomDialog(this.dialogId);
                        this.dialogId = null;
                    }
                }));
        } else {
            p83.clearGestures();
        }
    }
}

ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;

export class EditableTitleBarV2 extends ViewV2 {
    constructor(j83, k83, l83, m83 = -1, n83, o83) {
        super(j83, m83, o83);
        this.initParam('leftIconStyle',
            (k83 && 'leftIconStyle' in k83) ? k83.leftIconStyle : EditableLeftIconTypeV2.Back);
        this.initParam('title', (k83 && 'title' in k83) ? k83.title : '');
        this.initParam('subtitle', (k83 && 'subtitle' in k83) ? k83.subtitle : '');
        this.initParam('isSaveIconRequired', (k83 && 'isSaveIconRequired' in k83) ? k83.isSaveIconRequired : true);
        this.initParam('imageItem', (k83 && 'imageItem' in k83) ? k83.imageItem : undefined);
        this.initParam('menuItems', (k83 && 'menuItems' in k83) ? k83.menuItems : undefined);
        this.initParam('options', (k83 && 'options' in k83) ? k83.options : {});
        this.initParam('onSave', (k83 && 'onSave' in k83) ? k83.onSave : undefined);
        this.initParam('onCancel', (k83 && 'onCancel' in k83) ? k83.onCancel : undefined);
        this.initParam('constraintWidth', (k83 && 'constraintWidth' in k83) ? k83.constraintWidth : 0);
        this.initParam('leftIconDefaultFocus',
            (k83 && 'leftIconDefaultFocus' in k83) ? k83.leftIconDefaultFocus : false);
        this.initParam('saveIconDefaultFocus',
            (k83 && 'saveIconDefaultFocus' in k83) ? k83.saveIconDefaultFocus : false);
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.editableTitleBarTheme = new EditableTitleBarTheme();
        this.initParam('contentMargin', (k83 && 'contentMargin' in k83) ? k83.contentMargin : undefined);
        this.titleBarMargin = {
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
        };
        this.fontSize = 1;
        this.callbackId = undefined;
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(i83) {
        this.resetParam('leftIconStyle',
            (i83 && 'leftIconStyle' in i83) ? i83.leftIconStyle : EditableLeftIconTypeV2.Back);
        this.resetParam('title', (i83 && 'title' in i83) ? i83.title : '');
        this.resetParam('subtitle', (i83 && 'subtitle' in i83) ? i83.subtitle : '');
        this.resetParam('isSaveIconRequired', (i83 && 'isSaveIconRequired' in i83) ? i83.isSaveIconRequired : true);
        this.resetParam('imageItem', (i83 && 'imageItem' in i83) ? i83.imageItem : undefined);
        this.resetParam('menuItems', (i83 && 'menuItems' in i83) ? i83.menuItems : undefined);
        this.resetParam('options', (i83 && 'options' in i83) ? i83.options : {});
        this.resetParam('onSave', (i83 && 'onSave' in i83) ? i83.onSave : undefined);
        this.resetParam('onCancel', (i83 && 'onCancel' in i83) ? i83.onCancel : undefined);
        this.resetParam('constraintWidth', (i83 && 'constraintWidth' in i83) ? i83.constraintWidth : 0);
        this.resetParam('leftIconDefaultFocus',
            (i83 && 'leftIconDefaultFocus' in i83) ? i83.leftIconDefaultFocus : false);
        this.resetParam('saveIconDefaultFocus',
            (i83 && 'saveIconDefaultFocus' in i83) ? i83.saveIconDefaultFocus : false);
        this.editableTitleBarTheme = new EditableTitleBarTheme();
        this.resetParam('contentMargin', (i83 && 'contentMargin' in i83) ? i83.contentMargin : undefined);
        this.titleBarMargin = {
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
        };
        this.fontSize = 1;
    }

    onWillApplyTheme(h83) {
        this.editableTitleBarTheme.iconColor = h83.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = h83.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = h83.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = h83.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = h83.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = h83.colors.interactiveFocus;
    }

    aboutToAppear() {
        try {
            let g83 = this.getUIContext();
            this.isFollowingSystemFontScale = g83.isFollowingSystemFontScale();
            this.maxFontScale = g83.getMaxFontScale();
        } catch (d83) {
            let e83 = d83?.code;
            let f83 = d83?.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${e83}, message: ${f83}`);
        }
        emitter.on({ eventId: EVENT_FONT_SIZE_CHANGE }, (c83) => {
            if (c83.data && c83.data.fontSize !== undefined) {
                this.fontSize = c83.data.fontSize;
            }
        });
    }

    aboutToDisappear() {
        emitter.off(EVENT_FONT_SIZE_CHANGE);
        if (this.callbackId) {
            this.getUIContext()?.getHostContext()?.getApplicationContext()?.off('environment', this.callbackId);
        }
    }

    decideFontScale() {
        let b83 = this.getUIContext();
        this.systemFontScale = b83.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }

    initialRender() {
        this.observeComponentCreation2((z82, a83) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBarV2.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE, undefined,
                { disableSystemAdaptation: true });
            Flex.expandSafeArea(this.options.safeAreaTypes ? this.options.safeAreaTypes : [SafeAreaType.SYSTEM],
                this.options.safeAreaEdges ? this.options.safeAreaEdges : [SafeAreaEdge.TOP]);
        }, Flex);
        this.observeComponentCreation2((x82, y82) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBarV2.totalHeight);
        }, Row);
        this.observeComponentCreation2((v82, w82) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((t82, u82) => {
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
        this.observeComponentCreation2((p82, q82) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r82, s82) => {
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
        this.observeComponentCreation2((n82, o82) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)();
        Row.pop();
        Row.pop();
        this.observeComponentCreation2((l82, m82) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)();
        Row.pop();
        Row.pop();
        Flex.pop();
    }

    imageItemLayout(g82 = null) {
        {
            this.observeComponentCreation2((h82, i82) => {
                if (i82) {
                    let j82 = new ImageMenuItem(this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                        editableTitleBarTheme: this.editableTitleBarTheme,
                    }, undefined, h82, () => {
                    }, {
                        page: 'library/src/main/ets/components/0508/editabletitlebarv2/source/editabletitlebarv2.ets',
                        line: 287,
                        col: 5
                    });
                    ViewV2.create(j82);
                    let k82 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image,
                            editableTitleBarTheme: this.editableTitleBarTheme
                        };
                    };
                    j82.paramsGenerator_ = k82;
                } else {
                    this.updateStateVarsOfChildByElmtId(h82, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                        editableTitleBarTheme: this.editableTitleBarTheme
                    });
                }
            }, { name: 'ImageMenuItem' });
        }
    }

    leftIconLayout(v81 = null) {
        this.observeComponentCreation2((w81, x81) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconTypeV2.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((c82, d82) => {
                            if (d82) {
                                let e82 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() :
                                            this.getUIContext()?.getRouter()?.back(),
                                        defaultFocus: this.leftIconDefaultFocus
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    imageMenuItemId: `BackMenuItem_${this.getUniqueId()}`,
                                    editableTitleBarTheme: this.editableTitleBarTheme,
                                }, undefined, c82, () => {
                                }, {
                                    page: 'library/src/main/ets/components/0508/editabletitlebarv2/source/editabletitlebarv2.ets',
                                    line: 297,
                                    col: 7
                                });
                                ViewV2.create(e82);
                                let f82 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: () => this.onCancel ? this.onCancel() :
                                                this.getUIContext()?.getRouter()?.back(),
                                            defaultFocus: this.leftIconDefaultFocus
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon,
                                        imageMenuItemId: `BackMenuItem_${this.getUniqueId()}`,
                                        editableTitleBarTheme: this.editableTitleBarTheme
                                    };
                                };
                                e82.paramsGenerator_ = f82;
                            } else {
                                this.updateStateVarsOfChildByElmtId(c82, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() :
                                            this.getUIContext()?.getRouter()?.back(),
                                        defaultFocus: this.leftIconDefaultFocus
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    imageMenuItemId: `BackMenuItem_${this.getUniqueId()}`,
                                    editableTitleBarTheme: this.editableTitleBarTheme
                                });
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((y81, z81) => {
                            if (z81) {
                                let a82 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                        defaultFocus: this.leftIconDefaultFocus
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    imageMenuItemId: `CancelMenuItem_${this.getUniqueId()}`,
                                    editableTitleBarTheme: this.editableTitleBarTheme,
                                }, undefined, y81, () => {
                                }, {
                                    page: 'library/src/main/ets/components/0508/editabletitlebarv2/source/editabletitlebarv2.ets',
                                    line: 310,
                                    col: 7
                                });
                                ViewV2.create(a82);
                                let b82 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_CANCEL,
                                            isEnabled: true,
                                            action: () => this.onCancel && this.onCancel(),
                                            defaultFocus: this.leftIconDefaultFocus
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon,
                                        imageMenuItemId: `CancelMenuItem_${this.getUniqueId()}`,
                                        editableTitleBarTheme: this.editableTitleBarTheme
                                    };
                                };
                                a82.paramsGenerator_ = b82;
                            } else {
                                this.updateStateVarsOfChildByElmtId(y81, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                        defaultFocus: this.leftIconDefaultFocus
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    imageMenuItemId: `CancelMenuItem_${this.getUniqueId()}`,
                                    editableTitleBarTheme: this.editableTitleBarTheme
                                });
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
        }, If);
        If.pop();
    }

    titleLayout(i81 = null) {
        this.observeComponentCreation2((t81, u81) => {
            Column.create();
            Column.height(EditableTitleBarV2.totalHeight);
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
        this.observeComponentCreation2((r81, s81) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((p81, q81) => {
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
                maxHeight: this.subtitle ? EditableTitleBarV2.maxMainTitleHeight : EditableTitleBarV2.totalHeight,
            });
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((j81, k81) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n81, o81) => {
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
                    this.observeComponentCreation2((l81, m81) => {
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
                            maxHeight: this.title ? EditableTitleBarV2.maxSubTitleHeight :
                                EditableTitleBarV2.totalHeight,
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

    rightMenuItemsLayout(d81 = null) {
        {
            this.observeComponentCreation2((e81, f81) => {
                if (f81) {
                    let g81 = new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                        parentUniqueId: this.getUniqueId(),
                        saveIconDefaultFocus: this.saveIconDefaultFocus,
                        editableTitleBarTheme: this.editableTitleBarTheme,
                    }, undefined, e81, () => {
                    }, {
                        page: 'library/src/main/ets/components/0508/editabletitlebarv2/source/editabletitlebarv2.ets',
                        line: 376,
                        col: 5
                    });
                    ViewV2.create(g81);
                    let h81 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize,
                            parentUniqueId: this.getUniqueId(),
                            saveIconDefaultFocus: this.saveIconDefaultFocus,
                            editableTitleBarTheme: this.editableTitleBarTheme
                        };
                    };
                    g81.paramsGenerator_ = h81;
                } else {
                    this.updateStateVarsOfChildByElmtId(e81, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                        parentUniqueId: this.getUniqueId(),
                        saveIconDefaultFocus: this.saveIconDefaultFocus,
                        editableTitleBarTheme: this.editableTitleBarTheme
                    });
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }

    onPlaceChildren(z80, a81, b81) {
        a81.forEach((c81) => {
            c81.layout({ x: 0, y: 0 });
        });
    }

    onMeasureSize(u80, v80, w80) {
        let x80 = { width: u80.width, height: u80.height };
        this.fontSize = this.decideFontScale();
        emitter.emit({ eventId: EVENT_FONT_SIZE_CHANGE }, { data: { fontSize: this.fontSize } });
        v80.forEach((y80) => {
            x80.height = y80.measure(w80).height;
            x80.width = Number(w80.maxWidth);
        });
        return x80;
    }

    updateStateVars(t80) {
        if (t80 === undefined) {
            return;
        }
        if ('leftIconStyle' in t80) {
            this.updateParam('leftIconStyle', t80.leftIconStyle);
        }
        if ('title' in t80) {
            this.updateParam('title', t80.title);
        }
        if ('subtitle' in t80) {
            this.updateParam('subtitle', t80.subtitle);
        }
        if ('isSaveIconRequired' in t80) {
            this.updateParam('isSaveIconRequired', t80.isSaveIconRequired);
        }
        if ('imageItem' in t80) {
            this.updateParam('imageItem', t80.imageItem);
        }
        if ('menuItems' in t80) {
            this.updateParam('menuItems', t80.menuItems);
        }
        if ('options' in t80) {
            this.updateParam('options', t80.options);
        }
        if ('onSave' in t80) {
            this.updateParam('onSave', t80.onSave);
        }
        if ('onCancel' in t80) {
            this.updateParam('onCancel', t80.onCancel);
        }
        if ('constraintWidth' in t80) {
            this.updateParam('constraintWidth', t80.constraintWidth);
        }
        if ('leftIconDefaultFocus' in t80) {
            this.updateParam('leftIconDefaultFocus', t80.leftIconDefaultFocus);
        }
        if ('saveIconDefaultFocus' in t80) {
            this.updateParam('saveIconDefaultFocus', t80.saveIconDefaultFocus);
        }
        if ('contentMargin' in t80) {
            this.updateParam('contentMargin', t80.contentMargin);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}
EditableTitleBarV2.maxCountOfExtraItems = 3;
EditableTitleBarV2.maxOtherCountOfExtraItems = 2;
EditableTitleBarV2.commonZero = 0;
EditableTitleBarV2.noneColor = '#00000000';
EditableTitleBarV2.defaultHeight = getNumberByResource(125831115, DEFAULT_TITLE_BAR_HEIGHT);
EditableTitleBarV2.defaultTitlePadding = getNumberByResource(125830920, DEFAULT_TITLE_PADDING);
EditableTitleBarV2.totalHeight =
    EditableTitleBarV2.defaultHeight === EditableTitleBarV2.commonZero ? DEFAULT_TITLE_BAR_HEIGHT :
        EditableTitleBarV2.defaultHeight;
EditableTitleBarV2.titlePadding = EditableTitleBarV2.defaultTitlePadding === EditableTitleBarV2.commonZero ?
    DEFAULT_TITLE_PADDING : EditableTitleBarV2.defaultTitlePadding;
EditableTitleBarV2.maxMainTitleHeight =
    (EditableTitleBarV2.totalHeight - EditableTitleBarV2.titlePadding) * MAX_MAIN_TITLE_PERCENT;
EditableTitleBarV2.maxSubTitleHeight =
    (EditableTitleBarV2.totalHeight - EditableTitleBarV2.titlePadding) * MAX_SUB_TITLE_PERCENT;
__decorate([
    Param
], EditableTitleBarV2.prototype, 'leftIconStyle', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'title', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'subtitle', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'isSaveIconRequired', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'imageItem', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'menuItems', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'options', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'onSave', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'onCancel', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'constraintWidth', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'leftIconDefaultFocus', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'saveIconDefaultFocus', void 0);
__decorate([
    Local
], EditableTitleBarV2.prototype, 'editableTitleBarTheme', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'contentMargin', void 0);
__decorate([
    Local
], EditableTitleBarV2.prototype, 'titleBarMargin', void 0);
__decorate([
    Local
], EditableTitleBarV2.prototype, 'fontSize', void 0);

class EditableTitleBarMenuSection extends ViewV2 {
    constructor(n80, o80, p80, q80 = -1, r80, s80) {
        super(n80, q80, s80);
        this.initParam('menuItems', (o80 && 'menuItems' in o80) ? o80.menuItems : undefined);
        this.initParam('onSave', (o80 && 'onSave' in o80) ? o80.onSave : undefined);
        this.initParam('isSaveEnabled', (o80 && 'isSaveEnabled' in o80) ? o80.isSaveEnabled : true);
        this.initParam('saveIconDefaultFocus',
            (o80 && 'saveIconDefaultFocus' in o80) ? o80.saveIconDefaultFocus : false);
        this.initParam('fontSize', (o80 && 'fontSize' in o80) ? o80.fontSize : 1);
        this.initParam('parentUniqueId', (o80 && 'parentUniqueId' in o80) ? o80.parentUniqueId : undefined);
        this.initParam('editableTitleBarTheme',
            (o80 && 'editableTitleBarTheme' in o80) ? o80.editableTitleBarTheme : new EditableTitleBarTheme());
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(m80) {
        this.resetParam('menuItems', (m80 && 'menuItems' in m80) ? m80.menuItems : undefined);
        this.resetParam('onSave', (m80 && 'onSave' in m80) ? m80.onSave : undefined);
        this.resetParam('isSaveEnabled', (m80 && 'isSaveEnabled' in m80) ? m80.isSaveEnabled : true);
        this.resetParam('saveIconDefaultFocus',
            (m80 && 'saveIconDefaultFocus' in m80) ? m80.saveIconDefaultFocus : false);
        this.resetParam('fontSize', (m80 && 'fontSize' in m80) ? m80.fontSize : 1);
        this.resetParam('parentUniqueId', (m80 && 'parentUniqueId' in m80) ? m80.parentUniqueId : undefined);
        this.resetParam('editableTitleBarTheme',
            (m80 && 'editableTitleBarTheme' in m80) ? m80.editableTitleBarTheme : new EditableTitleBarTheme());
    }

    initialRender() {
        this.observeComponentCreation2((k80, l80) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((i80, j80) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((w79, x79) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBarV2.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y79, z79) => {
                        ForEach.create();
                        const a80 = (b80, c80) => {
                            const d80 = b80;
                            {
                                this.observeComponentCreation2((e80, f80) => {
                                    if (f80) {
                                        let g80 = new ImageMenuItem(this, {
                                            item: d80,
                                            attribute: ItemType.Icon,
                                            imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${c80}`,
                                            editableTitleBarTheme: this.editableTitleBarTheme,
                                        }, undefined, e80, () => {
                                        }, {
                                            page: 'library/src/main/ets/components/0508/editabletitlebarv2/source/editabletitlebarv2.ets',
                                            line: 423,
                                            col: 15
                                        });
                                        ViewV2.create(g80);
                                        let h80 = () => {
                                            return {
                                                item: d80,
                                                attribute: ItemType.Icon,
                                                imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${c80}`,
                                                editableTitleBarTheme: this.editableTitleBarTheme
                                            };
                                        };
                                        g80.paramsGenerator_ = h80;
                                    } else {
                                        this.updateStateVarsOfChildByElmtId(e80, {
                                            item: d80,
                                            attribute: ItemType.Icon,
                                            imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${c80}`,
                                            editableTitleBarTheme: this.editableTitleBarTheme
                                        });
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(y79,
                            this.menuItems.slice(EditableTitleBarV2.commonZero, this.isSaveEnabled ?
                                EditableTitleBarV2.maxOtherCountOfExtraItems : EditableTitleBarV2.maxCountOfExtraItems),
                            a80, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((q79, r79) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((s79, t79) => {
                            if (t79) {
                                let u79 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                        defaultFocus: this.saveIconDefaultFocus
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                    imageMenuItemId: `SaveMenuItem_${this.parentUniqueId}`,
                                    editableTitleBarTheme: this.editableTitleBarTheme,
                                }, undefined, s79, () => {
                                }, {
                                    page: 'library/src/main/ets/components/0508/editabletitlebarv2/source/editabletitlebarv2.ets',
                                    line: 432,
                                    col: 11
                                });
                                ViewV2.create(u79);
                                let v79 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_OK,
                                            isEnabled: true,
                                            action: () => this.onSave && this.onSave(),
                                            defaultFocus: this.saveIconDefaultFocus
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.Icon,
                                        imageMenuItemId: `SaveMenuItem_${this.parentUniqueId}`,
                                        editableTitleBarTheme: this.editableTitleBarTheme
                                    };
                                };
                                u79.paramsGenerator_ = v79;
                            } else {
                                this.updateStateVarsOfChildByElmtId(s79, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                        defaultFocus: this.saveIconDefaultFocus
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                    imageMenuItemId: `SaveMenuItem_${this.parentUniqueId}`,
                                    editableTitleBarTheme: this.editableTitleBarTheme
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

    updateStateVars(p79) {
        if (p79 === undefined) {
            return;
        }
        if ('menuItems' in p79) {
            this.updateParam('menuItems', p79.menuItems);
        }
        if ('onSave' in p79) {
            this.updateParam('onSave', p79.onSave);
        }
        if ('isSaveEnabled' in p79) {
            this.updateParam('isSaveEnabled', p79.isSaveEnabled);
        }
        if ('saveIconDefaultFocus' in p79) {
            this.updateParam('saveIconDefaultFocus', p79.saveIconDefaultFocus);
        }
        if ('fontSize' in p79) {
            this.updateParam('fontSize', p79.fontSize);
        }
        if ('parentUniqueId' in p79) {
            this.updateParam('parentUniqueId', p79.parentUniqueId);
        }
        if ('editableTitleBarTheme' in p79) {
            this.updateParam('editableTitleBarTheme', p79.editableTitleBarTheme);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

__decorate([
    Param
], EditableTitleBarMenuSection.prototype, 'menuItems', void 0);
__decorate([
    Param
], EditableTitleBarMenuSection.prototype, 'onSave', void 0);
__decorate([
    Param
], EditableTitleBarMenuSection.prototype, 'isSaveEnabled', void 0);
__decorate([
    Param
], EditableTitleBarMenuSection.prototype, 'saveIconDefaultFocus', void 0);
__decorate([
    Param
], EditableTitleBarMenuSection.prototype, 'fontSize', void 0);
__decorate([
    Param
], EditableTitleBarMenuSection.prototype, 'parentUniqueId', void 0);
__decorate([
    Param
], EditableTitleBarMenuSection.prototype, 'editableTitleBarTheme', void 0);

class ImageMenuItem extends ViewV2 {
    constructor(e79, f79, g79, h79 = -1, i79, j79) {
        super(e79, h79, j79);
        this.initParam('item', (f79 && 'item' in f79) ? f79.item : {
            value: '',
            isEnabled: true,
            label: '',
            accessibilityLevel: 'auto',
            accessibilityText: '',
            accessibilityDescription: '',
        });
        this.initParam('attribute', (f79 && 'attribute' in f79) ? f79.attribute : ItemType.Image);
        this.callbackId = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.2;
        this.longPressTime = 500;
        this.systemFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.initParam('fontSize', (f79 && 'fontSize' in f79) ? f79.fontSize : 1);
        this.innerFontSize = 1;
        this.isOnFocus = false;
        this.isOnHover = false;
        this.isOnClick = false;
        this.initParam('imageMenuItemId', (f79 && 'imageMenuItemId' in f79) ? f79.imageMenuItemId : undefined);
        this.initParam('editableTitleBarTheme',
            (f79 && 'editableTitleBarTheme' in f79) ? f79.editableTitleBarTheme : new EditableTitleBarTheme());
        this.dialogId = null;
        this.buttonGestureModifier = null;
        this.envCallback = {
            onConfigurationUpdated: (l79) => {
                if (l79 === undefined || !this.isFollowingSystemFontScale) {
                    this.innerFontSize = 1;
                    return;
                }
                try {
                    this.innerFontSize = Math.min(this.maxFontScale, l79?.fontSizeScale ?? 1);
                    if (this.buttonGestureModifier) {
                        this.buttonGestureModifier.fontSize = this.innerFontSize;
                    }
                } catch (m79) {
                    let n79 = m79?.code;
                    let o79 = m79?.message;
                    hilog.error(0x3900, 'EditableTitleBarV2', `EnvironmentCallback error: ${n79}, ${o79}`);
                }
            },
            onMemoryLevel: (k79) => {
            }
        };
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(d79) {
        this.resetParam('item', (d79 && 'item' in d79) ? d79.item : {
            value: '',
            isEnabled: true,
            label: '',
            accessibilityLevel: 'auto',
            accessibilityText: '',
            accessibilityDescription: '',
        });
        this.resetParam('attribute', (d79 && 'attribute' in d79) ? d79.attribute : ItemType.Image);
        this.resetParam('fontSize', (d79 && 'fontSize' in d79) ? d79.fontSize : 1);
        this.innerFontSize = 1;
        this.isOnFocus = false;
        this.isOnHover = false;
        this.isOnClick = false;
        this.resetParam('imageMenuItemId', (d79 && 'imageMenuItemId' in d79) ? d79.imageMenuItemId : undefined);
        this.resetParam('editableTitleBarTheme',
            (d79 && 'editableTitleBarTheme' in d79) ? d79.editableTitleBarTheme : new EditableTitleBarTheme());
        this.buttonGestureModifier = null;
    }

    aboutToAppear() {
        try {
            let c79 = this.getUIContext();
            this.isFollowingSystemFontScale = c79.isFollowingSystemFontScale();
            this.maxFontScale = c79.getMaxFontScale();
        } catch (z78) {
            let a79 = z78?.code;
            let b79 = z78?.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${a79}, message: ${b79}`);
        }
        this.buttonGestureModifier = new ButtonGestureModifier(this.dialogId, () => {
            this.EditableTitleBarDialogBuilder();
        });
        try {
            this.callbackId =
                this.getUIContext()?.getHostContext()?.getApplicationContext()?.on('environment', this.envCallback);
        } catch (w78) {
            let x78 = w78?.code;
            let y78 = w78?.message;
            hilog.error(0x3900, 'EditableTitleBarV2', `Failed to get environment param error: ${x78}, ${y78}`);
        }
        this.innerFontSize = this.decideFontScale();
        if (this.buttonGestureModifier) {
            this.buttonGestureModifier.fontSize = this.innerFontSize;
            this.buttonGestureModifier.maxFontSize = this.maxFontSize;
        }
    }

    aboutToDisappear() {
        if (this.callbackId) {
            this.getUIContext()?.getHostContext()?.getApplicationContext()?.off('environment', this.callbackId);
            this.callbackId = undefined;
        }
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

    decideFontScale() {
        try {
            let v78 = this.getUIContext();
            this.systemFontScale = v78?.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        } catch (s78) {
            let t78 = s78?.code;
            let u78 = s78?.message;
            hilog.error(0x3900, 'EditableTitleBarV2', `Failed to decideFontScale,cause, code: ${t78}, message: ${u78}`);
            return 1;
        }
    }

    touchEventAction(r78) {
        if (!this.item.isEnabled) {
            return;
        }
        if (r78.type === TouchType.Down) {
            this.isOnClick = true;
        }
        if (r78.type === TouchType.Up || r78.type === TouchType.Cancel) {
            if (this.innerFontSize >= this.minFontSize && this.dialogId !== null) {
                promptAction.closeCustomDialog(this.dialogId);
                this.dialogId = null;
            }
            this.isOnClick = false;
        }
    }

    keyEventAction(q78) {
        if (!this.item.isEnabled) {
            return;
        }
        if (q78.keyCode !== KeyCode.KEYCODE_ENTER && q78.keyCode !== KeyCode.KEYCODE_SPACE) {
            return;
        }
        if (q78.type === KeyType.Down) {
            this.isOnClick = true;
        }
        if (q78.type === KeyType.Up) {
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
            return EditableTitleBarV2.noneColor;
        }
    }

    getStringByNameSync(l78) {
        let m78 = '';
        try {
            m78 = getContext()?.resourceManager?.getStringByNameSync(l78);
        } catch (n78) {
            let o78 = n78?.code;
            let p78 = n78?.message;
            hilog.error(0x3900, 'Ace', `Faild to getStringByNameSync,cause, code: ${o78}, message: ${p78}`);
        }
        return m78;
    }

    toStringFormat(g78) {
        if (typeof g78 === 'string' || typeof g78 === 'undefined') {
            return g78;
        } else {
            let h78 = '';
            try {
                if (g78.id === -1) {
                    h78 = getContext()?.resourceManager?.getStringByNameSync(g78.params?.[0]?.split('.').pop() ?? '');
                } else {
                    h78 = getContext()?.resourceManager?.getStringSync(g78);
                }
            } catch (i78) {
                let j78 = i78?.code;
                let k78 = i78?.message;
                hilog.error(0x3900, 'Ace', `Faild to EditableTitleBarV2 toStringFormat, code: ${j78}, message: ${k78}`);
            }
            return h78;
        }
    }

    getAccessibilityReadText() {
        if (this.item.value === PUBLIC_OK) {
            return this.getStringByNameSync('icon_save');
        } else if (this.item.value === PUBLIC_CANCEL) {
            return this.getStringByNameSync('icon_cancel');
        } else if (this.item.value === PUBLIC_BACK) {
            return this.getStringByNameSync('icon_back');
        } else if (this.item.accessibilityText) {
            return this.item.accessibilityText;
        } else if (this.item.label) {
            return this.item.label;
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
            return this.item.accessibilityDescription;
        }
        return '';
    }

    EditableTitleBarDialogBuilder(b78 = null) {
        {
            this.observeComponentCreation2((c78, d78) => {
                if (d78) {
                    let e78 = new EditableTitleBarDialogContent(this, {
                        itemEditableDialog: this.item,
                        textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                        fontSize: this.fontSize,
                    }, undefined, c78, () => {
                    }, {
                        page: 'library/src/main/ets/components/0508/editabletitlebarv2/source/editabletitlebarv2.ets',
                        line: 746,
                        col: 5
                    });
                    ViewV2.create(e78);
                    let f78 = () => {
                        return {
                            itemEditableDialog: this.item,
                            textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                            fontSize: this.fontSize
                        };
                    };
                    e78.paramsGenerator_ = f78;
                } else {
                    this.updateStateVarsOfChildByElmtId(c78, {
                        itemEditableDialog: this.item,
                        textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                        fontSize: this.fontSize
                    });
                }
            }, { name: 'EditableTitleBarDialogContent' });
        }
    }

    IconBuilder(l77 = null) {
        this.observeComponentCreation2((w77, x77) => {
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.id(this.imageMenuItemId);
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
                start: this.attribute === ItemType.LeftIcon ? LengthMetrics.vp(EditableTitleBarV2.commonZero) :
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
                width: EditableTitleBarV2.commonZero,
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
                width: EditableTitleBarV2.commonZero,
            });
            ViewStackProcessor.visualState();
            Button.onFocus(() => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnFocus = true;
            });
            Button.onBlur(() => this.isOnFocus = false);
            Button.onHover((a78) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = a78;
            });
            Button.onKeyEvent((z77) => {
                this.keyEventAction(z77);
            });
            Button.onTouch((y77) => {
                this.touchEventAction(y77);
            });
            Button.onClick(() => {
                if (this.item.isEnabled === undefined) {
                    this.item.isEnabled = true;
                }
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Button.gestureModifier(this.buttonGestureModifier);
            Button.accessibilityLevel(this.getRightIconAccessibilityLevel());
            Button.accessibilityDescription(this.getAccessibilityDescription());
            Button.defaultFocus(this.item.defaultFocus);
        }, Button);
        this.observeComponentCreation2((m77, n77) => {
            If.create();
            if (this.item.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u77, v77) => {
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
                    this.observeComponentCreation2((o77, p77) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((s77, t77) => {
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
                                this.observeComponentCreation2((q77, r77) => {
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

    ImageBuilder(b77 = null) {
        this.observeComponentCreation2((j77, k77) => {
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
        this.observeComponentCreation2((h77, i77) => {
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
        this.observeComponentCreation2((c77, d77) => {
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
            Button.backgroundColor(EditableTitleBarV2.noneColor);
            ViewStackProcessor.visualState('pressed');
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_shape'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: EditableTitleBarV2.commonZero,
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
                width: EditableTitleBarV2.commonZero,
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
            Button.onHover((g77) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = g77;
            });
            Button.onKeyEvent((f77) => {
                this.keyEventAction(f77);
            });
            Button.onTouch((e77) => {
                this.touchEventAction(e77);
            });
            Button.onClick(() => {
                if (this.item.isEnabled === undefined) {
                    this.item.isEnabled = true;
                }
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Button.gestureModifier(this.buttonGestureModifier);
            Button.defaultFocus(this.item.defaultFocus);
        }, Button);
        Button.pop();
        Stack.pop();
    }

    initialRender() {
        this.observeComponentCreation2((z76, a77) => {
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

    updateStateVars(y76) {
        if (y76 === undefined) {
            return;
        }
        if ('item' in y76) {
            this.updateParam('item', y76.item);
        }
        if ('attribute' in y76) {
            this.updateParam('attribute', y76.attribute);
        }
        if ('fontSize' in y76) {
            this.updateParam('fontSize', y76.fontSize);
        }
        if ('imageMenuItemId' in y76) {
            this.updateParam('imageMenuItemId', y76.imageMenuItemId);
        }
        if ('editableTitleBarTheme' in y76) {
            this.updateParam('editableTitleBarTheme', y76.editableTitleBarTheme);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

__decorate([
    Param
], ImageMenuItem.prototype, 'item', void 0);
__decorate([
    Param
], ImageMenuItem.prototype, 'attribute', void 0);
__decorate([
    Param
], ImageMenuItem.prototype, 'fontSize', void 0);
__decorate([
    Local
], ImageMenuItem.prototype, 'innerFontSize', void 0);
__decorate([
    Local
], ImageMenuItem.prototype, 'isOnFocus', void 0);
__decorate([
    Local
], ImageMenuItem.prototype, 'isOnHover', void 0);
__decorate([
    Local
], ImageMenuItem.prototype, 'isOnClick', void 0);
__decorate([
    Param
], ImageMenuItem.prototype, 'imageMenuItemId', void 0);
__decorate([
    Param
], ImageMenuItem.prototype, 'editableTitleBarTheme', void 0);
__decorate([
    Local
], ImageMenuItem.prototype, 'buttonGestureModifier', void 0);

class EditableTitleBarDialogContent extends ViewV2 {
    constructor(s76, t76, u76, v76 = -1, w76, x76) {
        super(s76, v76, x76);
        this.initParam('itemEditableDialog', (t76 && 'itemEditableDialog' in t76) ? t76.itemEditableDialog : {
            value: '',
            isEnabled: true,
        });
        this.callbackId = undefined;
        this.initParam('textEditableTitleBarDialog',
            (t76 && 'textEditableTitleBarDialog' in t76) ? t76.textEditableTitleBarDialog : '');
        this.mainWindowStage = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.2;
        this.screenWidth = 640;
        this.verticalScreenLines = 6;
        this.horizontalsScreenLines = 1;
        this.mainWindow = undefined;
        this.initParam('fontSize', (t76 && 'fontSize' in t76) ? t76.fontSize : 1);
        this.maxLines = 1;
        this.windowStandardHeight = 0;
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(r76) {
        this.resetParam('itemEditableDialog', (r76 && 'itemEditableDialog' in r76) ? r76.itemEditableDialog : {
            value: '',
            isEnabled: true,
        });
        this.resetParam('textEditableTitleBarDialog',
            (r76 && 'textEditableTitleBarDialog' in r76) ? r76.textEditableTitleBarDialog : '');
        this.resetParam('fontSize', (r76 && 'fontSize' in r76) ? r76.fontSize : 1);
        this.maxLines = 1;
    }

    initialRender() {
        this.observeComponentCreation2((n75, o75) => {
            If.create();
            if (this.textEditableTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p76, q76) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({
                            minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG
                        });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined,
                            { disableSystemAdaptation: true });
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.corner_radius_level10'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        }));
                    }, Column);
                    this.observeComponentCreation2((f76, g76) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((n76, o76) => {
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
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((h76, i76) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((l76, m76) => {
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
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((j76, k76) => {
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
                    this.observeComponentCreation2((d76, e76) => {
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
                    this.observeComponentCreation2((b76, c76) => {
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
                    this.observeComponentCreation2((z75, a76) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({
                            minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG
                        });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined,
                            { disableSystemAdaptation: true });
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
                    this.observeComponentCreation2((p75, q75) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((x75, y75) => {
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
                                this.observeComponentCreation2((r75, s75) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((v75, w75) => {
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
                                            this.observeComponentCreation2((t75, u75) => {
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
        try {
            let m75 = this.getUIContext().getHostContext();
            this.mainWindowStage = m75.windowStage.getMainWindowSync();
        } catch (j75) {
            let k75 = j75?.code;
            let l75 = j75?.message;
            hilog.error(0x3900, 'Ace', `EditableTitleBarV2 getMainWindowStage error, code: ${k75},message:${l75}`);
            return;
        }
        if (this.mainWindowStage) {
            let h75 = this.mainWindowStage.getWindowProperties();
            let i75 = h75.windowRect;
            if (px2vp(i75.height) > this.screenWidth) {
                this.maxLines = this.verticalScreenLines;
            } else {
                this.maxLines = this.horizontalsScreenLines;
            }
        }
    }

    updateStateVars(g75) {
        if (g75 === undefined) {
            return;
        }
        if ('itemEditableDialog' in g75) {
            this.updateParam('itemEditableDialog', g75.itemEditableDialog);
        }
        if ('textEditableTitleBarDialog' in g75) {
            this.updateParam('textEditableTitleBarDialog', g75.textEditableTitleBarDialog);
        }
        if ('fontSize' in g75) {
            this.updateParam('fontSize', g75.fontSize);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

__decorate([
    Param
], EditableTitleBarDialogContent.prototype, 'itemEditableDialog', void 0);
__decorate([
    Param
], EditableTitleBarDialogContent.prototype, 'textEditableTitleBarDialog', void 0);
__decorate([
    Param
], EditableTitleBarDialogContent.prototype, 'fontSize', void 0);
__decorate([
    Local
], EditableTitleBarDialogContent.prototype, 'maxLines', void 0);

function getNumberByResource(a75, b75) {
    try {
        let f75 = resourceManager.getSystemResourceManager().getNumber(a75);
        if (f75 === 0) {
            return b75;
        } else {
            return f75;
        }
    } catch (c75) {
        let d75 = c75.code;
        let e75 = c75.message;
        hilog.error(0x3900, 'Ace', `EditableTitleBarV2 getNumberByResource error, code: ${d75},message:${e75}`);
        return 0;
    }
}

class Util {
    static isSymbolResource(y74) {
        if (!Util.isResourceType(y74)) {
            return false;
        }
        let z74 = y74;
        return z74.type === Util.RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(x74) {
        if (!x74) {
            return false;
        }
        if (typeof x74 === 'string' || typeof x74 === 'undefined') {
            return false;
        }
        return true;
    }
}

Util.RESOURCE_TYPE_SYMBOL = 40000;

export default {
    EditableLeftIconTypeV2: EditableLeftIconTypeV2,
    EditableTitleBarV2: EditableTitleBarV2,
};
//# sourceMappingURL=MainPage.js.map