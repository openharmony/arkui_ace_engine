/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
var __decorate = (this && this.__decorate) || function (h9, i9, j9, k9) {
    var l9 = arguments.length, m9 = l9 < 3 ? i9 : k9 === null ? k9 = Object.getOwnPropertyDescriptor(i9, j9) : k9, n9;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        m9 = Reflect.decorate(h9, i9, j9, k9);
    } else {
        for (var o9 = h9.length - 1; o9 >= 0; o9--) {
            if (n9 = h9[o9]) {
                m9 = (l9 < 3 ? n9(m9) : l9 > 3 ? n9(i9, j9, m9) : n9(i9, j9)) || m9;
            }
        }
    }
    return l9 > 3 && m9 && Object.defineProperty(i9, j9, m9), m9;
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
(function (g9) {
    g9[g9['Back'] = 0] = 'Back';
    g9[g9['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconTypeV2 || (EditableLeftIconTypeV2 = {}));
let EditableLeftIconV2 = class EditableLeftIconV2 {
    constructor(f9) {
        this.iconType = EditableLeftIconTypeV2.Back;
        this.defaultFocus = false;
        if (f9) {
            if (f9.iconType !== undefined) {
                this.iconType = f9.iconType;
            }
            if (f9.defaultFocus !== undefined) {
                this.defaultFocus = f9.defaultFocus;
            }
            if (f9.onAction !== undefined) {
                this.onAction = f9.onAction;
            }
        }
    }
};
__decorate([
    Trace
], EditableLeftIconV2.prototype, 'iconType', void 0);
__decorate([
    Trace
], EditableLeftIconV2.prototype, 'defaultFocus', void 0);
__decorate([
    Trace
], EditableLeftIconV2.prototype, 'onAction', void 0);
EditableLeftIconV2 = __decorate([
    ObservedV2
], EditableLeftIconV2);

export { EditableLeftIconV2 };
let EditableTitleV2 = class EditableTitleV2 {
    constructor(e9) {
        this.mainTitle = '';
        if (e9) {
            if (e9.mainTitle !== undefined) {
                this.mainTitle = e9.mainTitle;
            }
            if (e9.subTitle !== undefined) {
                this.subTitle = e9.subTitle;
            }
        }
    }
};
__decorate([
    Trace
], EditableTitleV2.prototype, 'mainTitle', void 0);
__decorate([
    Trace
], EditableTitleV2.prototype, 'subTitle', void 0);
EditableTitleV2 = __decorate([
    ObservedV2
], EditableTitleV2);

export { EditableTitleV2 };
let EditableTitleBarMenuItemV2 = class EditableTitleBarMenuItemV2 {
    constructor(d9) {
        this.value = '';
        this.isEnabled = true;
        this.accessibilityLevel = 'auto';
        this.defaultFocus = false;
        if (d9) {
            if (d9.value !== undefined) {
                this.value = d9.value;
            }
            if (d9.symbolStyle !== undefined) {
                this.symbolStyle = d9.symbolStyle;
            }
            if (d9.isEnabled !== undefined) {
                this.isEnabled = d9.isEnabled;
            }
            if (d9.label !== undefined) {
                this.label = d9.label;
            }
            if (d9.action !== undefined) {
                this.action = d9.action;
            }
            if (d9.accessibilityLevel !== undefined) {
                this.accessibilityLevel = d9.accessibilityLevel;
            }
            if (d9.accessibilityText !== undefined) {
                this.accessibilityText = d9.accessibilityText;
            }
            if (d9.accessibilityDescription !== undefined) {
                this.accessibilityDescription = d9.accessibilityDescription;
            }
            if (d9.defaultFocus !== undefined) {
                this.defaultFocus = d9.defaultFocus;
            }
        }
    }
};
__decorate([
    Trace
], EditableTitleBarMenuItemV2.prototype, 'value', void 0);
__decorate([
    Trace
], EditableTitleBarMenuItemV2.prototype, 'symbolStyle', void 0);
__decorate([
    Trace
], EditableTitleBarMenuItemV2.prototype, 'isEnabled', void 0);
__decorate([
    Trace
], EditableTitleBarMenuItemV2.prototype, 'label', void 0);
__decorate([
    Trace
], EditableTitleBarMenuItemV2.prototype, 'action', void 0);
__decorate([
    Trace
], EditableTitleBarMenuItemV2.prototype, 'accessibilityLevel', void 0);
__decorate([
    Trace
], EditableTitleBarMenuItemV2.prototype, 'accessibilityText', void 0);
__decorate([
    Trace
], EditableTitleBarMenuItemV2.prototype, 'accessibilityDescription', void 0);
__decorate([
    Trace
], EditableTitleBarMenuItemV2.prototype, 'defaultFocus', void 0);
EditableTitleBarMenuItemV2 = __decorate([
    ObservedV2
], EditableTitleBarMenuItemV2);

export { EditableTitleBarMenuItemV2 };
let EditableSaveButtonV2 = class EditableSaveButtonV2 {
    constructor(c9) {
        this.isRequired = true;
        this.defaultFocus = false;
        if (c9) {
            if (c9.isRequired !== undefined) {
                this.isRequired = c9.isRequired;
            }
            if (c9.defaultFocus !== undefined) {
                this.defaultFocus = c9.defaultFocus;
            }
            if (c9.onAction !== undefined) {
                this.onAction = c9.onAction;
            }
        }
    }
};
__decorate([
    Trace
], EditableSaveButtonV2.prototype, 'isRequired', void 0);
__decorate([
    Trace
], EditableSaveButtonV2.prototype, 'defaultFocus', void 0);
__decorate([
    Trace
], EditableSaveButtonV2.prototype, 'onAction', void 0);
EditableSaveButtonV2 = __decorate([
    ObservedV2
], EditableSaveButtonV2);

export { EditableSaveButtonV2 };
let EditableTitleBarStyleV2 = class EditableTitleBarStyleV2 {
    constructor(b9) {
        if (b9) {
            if (b9.backgroundColor !== undefined) {
                this.backgroundColor = b9.backgroundColor;
            }
            if (b9.backgroundBlurStyle !== undefined) {
                this.backgroundBlurStyle = b9.backgroundBlurStyle;
            }
            if (b9.safeAreaTypes !== undefined) {
                this.safeAreaTypes = b9.safeAreaTypes;
            }
            if (b9.safeAreaEdges !== undefined) {
                this.safeAreaEdges = b9.safeAreaEdges;
            }
            if (b9.contentMargin !== undefined) {
                this.contentMargin = b9.contentMargin;
            }
        }
    }
};
__decorate([
    Trace
], EditableTitleBarStyleV2.prototype, 'backgroundColor', void 0);
__decorate([
    Trace
], EditableTitleBarStyleV2.prototype, 'backgroundBlurStyle', void 0);
__decorate([
    Trace
], EditableTitleBarStyleV2.prototype, 'safeAreaTypes', void 0);
__decorate([
    Trace
], EditableTitleBarStyleV2.prototype, 'safeAreaEdges', void 0);
__decorate([
    Trace
], EditableTitleBarStyleV2.prototype, 'contentMargin', void 0);
EditableTitleBarStyleV2 = __decorate([
    ObservedV2
], EditableTitleBarStyleV2);

export { EditableTitleBarStyleV2 };
var ItemType;
(function (a9) {
    a9[a9['Image'] = 0] = 'Image';
    a9[a9['Icon'] = 1] = 'Icon';
    a9[a9['LeftIcon'] = 2] = 'LeftIcon';
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
    constructor(y8, z8) {
        this.fontSize = 1;
        this.maxFontSize = 3.2;
        this.dialogId = null;
        this.builder = () => {
        };
        this.dialogId = y8;
        this.builder = z8;
    }

    applyGesture(v8) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            v8.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (v8) {
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
                        }).then((x8) => {
                            this.dialogId = x8;
                        }).catch((w8) => {
                            hilog.error(0x3900, 'EditableTitleBarV2', `Failed to open dialog, error: ${w8.message}`);
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
            v8.clearGestures();
        }
    }
}

ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;

export class EditableTitleBarV2 extends ViewV2 {
    constructor(p8, q8, r8, s8 = -1, t8, u8) {
        super(p8, s8, u8);
        this.initParam('leftIcon', (q8 && 'leftIcon' in q8) ? q8.leftIcon : undefined);
        this.initParam('title', (q8 && 'title' in q8) ? q8.title : new EditableTitleV2());
        this.initParam('imageItem', (q8 && 'imageItem' in q8) ? q8.imageItem : undefined);
        this.initParam('menuItems', (q8 && 'menuItems' in q8) ? q8.menuItems : undefined);
        this.initParam('saveButton', (q8 && 'saveButton' in q8) ? q8.saveButton : undefined);
        this.initParam('options', (q8 && 'options' in q8) ? q8.options : new EditableTitleBarStyleV2());
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.editableTitleBarTheme = new EditableTitleBarTheme();
        this.fontSize = 1;
        this.callbackId = undefined;
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(o8) {
        this.resetParam('leftIcon', (o8 && 'leftIcon' in o8) ? o8.leftIcon : undefined);
        this.resetParam('title', (o8 && 'title' in o8) ? o8.title : new EditableTitleV2());
        this.resetParam('imageItem', (o8 && 'imageItem' in o8) ? o8.imageItem : undefined);
        this.resetParam('menuItems', (o8 && 'menuItems' in o8) ? o8.menuItems : undefined);
        this.resetParam('saveButton', (o8 && 'saveButton' in o8) ? o8.saveButton : undefined);
        this.resetParam('options', (o8 && 'options' in o8) ? o8.options : new EditableTitleBarStyleV2());
        this.editableTitleBarTheme = new EditableTitleBarTheme();
        this.fontSize = 1;
    }

    getContentMargin() {
        if (this.options.contentMargin) {
            return this.options.contentMargin;
        }
        return {
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
    }

    onWillApplyTheme(n8) {
        this.editableTitleBarTheme.iconColor = n8.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = n8.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = n8.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = n8.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = n8.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = n8.colors.interactiveFocus;
    }

    aboutToAppear() {
        try {
            let m8 = this.getUIContext();
            this.isFollowingSystemFontScale = m8.isFollowingSystemFontScale();
            this.maxFontScale = m8.getMaxFontScale();
        } catch (j8) {
            let k8 = j8?.code;
            let l8 = j8?.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${k8}, message: ${l8}`);
        }
        emitter.on({ eventId: EVENT_FONT_SIZE_CHANGE }, (i8) => {
            if (i8.data && i8.data.fontSize !== undefined) {
                this.fontSize = i8.data.fontSize;
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
        let h8 = this.getUIContext();
        this.systemFontScale = h8.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }

    initialRender() {
        this.observeComponentCreation2((f8, g8) => {
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
        this.observeComponentCreation2((d8, e8) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.getContentMargin());
            Row.height(EditableTitleBarV2.totalHeight);
        }, Row);
        this.observeComponentCreation2((b8, c8) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.observeComponentCreation2((z7, a8) => {
            If.create();
            if (this.leftIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.leftIconLayout.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
        this.observeComponentCreation2((x7, y7) => {
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
        this.observeComponentCreation2((t7, u7) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v7, w7) => {
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
        this.observeComponentCreation2((r7, s7) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)();
        Row.pop();
        Row.pop();
        this.observeComponentCreation2((p7, q7) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)();
        Row.pop();
        Row.pop();
        Flex.pop();
    }

    imageItemLayout(k7 = null) {
        {
            this.observeComponentCreation2((l7, m7) => {
                if (m7) {
                    let n7 = new ImageMenuItem(this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                        editableTitleBarTheme: this.editableTitleBarTheme,
                    }, undefined, l7, () => {
                    }, { page: 'library/src/main/ets/components/editabletitlebarv2.ets', line: 439, col: 5 });
                    ViewV2.create(n7);
                    let o7 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image,
                            editableTitleBarTheme: this.editableTitleBarTheme
                        };
                    };
                    n7.paramsGenerator_ = o7;
                } else {
                    this.updateStateVarsOfChildByElmtId(l7, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                        editableTitleBarTheme: this.editableTitleBarTheme
                    });
                }
            }, { name: 'ImageMenuItem' });
        }
    }

    leftIconLayout(z6 = null) {
        this.observeComponentCreation2((a7, b7) => {
            If.create();
            if (this.leftIcon.iconType === EditableLeftIconTypeV2.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((g7, h7) => {
                            if (h7) {
                                let i7 = new ImageMenuItem(this, {
                                    item: new EditableTitleBarMenuItemV2({
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: this.leftIcon.onAction ? this.leftIcon.onAction :
                                            () => this.getUIContext()?.getRouter()?.back(),
                                        defaultFocus: this.leftIcon.defaultFocus
                                    }),
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    imageMenuItemId: `BackMenuItem_${this.getUniqueId()}`,
                                    editableTitleBarTheme: this.editableTitleBarTheme,
                                }, undefined, g7, () => {
                                }, {
                                    page: 'library/src/main/ets/components/editabletitlebarv2.ets',
                                    line: 449,
                                    col: 7
                                });
                                ViewV2.create(i7);
                                let j7 = () => {
                                    return {
                                        item: new EditableTitleBarMenuItemV2({
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: this.leftIcon.onAction ? this.leftIcon.onAction :
                                                () => this.getUIContext()?.getRouter()?.back(),
                                            defaultFocus: this.leftIcon.defaultFocus
                                        }),
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon,
                                        imageMenuItemId: `BackMenuItem_${this.getUniqueId()}`,
                                        editableTitleBarTheme: this.editableTitleBarTheme
                                    };
                                };
                                i7.paramsGenerator_ = j7;
                            } else {
                                this.updateStateVarsOfChildByElmtId(g7, {
                                    item: new EditableTitleBarMenuItemV2({
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: this.leftIcon.onAction ? this.leftIcon.onAction :
                                            () => this.getUIContext()?.getRouter()?.back(),
                                        defaultFocus: this.leftIcon.defaultFocus
                                    }),
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
                        this.observeComponentCreation2((c7, d7) => {
                            if (d7) {
                                let e7 = new ImageMenuItem(this, {
                                    item: new EditableTitleBarMenuItemV2({
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: this.leftIcon.onAction ? this.leftIcon.onAction : () => {
                                        },
                                        defaultFocus: this.leftIcon.defaultFocus
                                    }),
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    imageMenuItemId: `CancelMenuItem_${this.getUniqueId()}`,
                                    editableTitleBarTheme: this.editableTitleBarTheme,
                                }, undefined, c7, () => {
                                }, {
                                    page: 'library/src/main/ets/components/editabletitlebarv2.ets',
                                    line: 462,
                                    col: 7
                                });
                                ViewV2.create(e7);
                                let f7 = () => {
                                    return {
                                        item: new EditableTitleBarMenuItemV2({
                                            value: PUBLIC_CANCEL,
                                            isEnabled: true,
                                            action: this.leftIcon.onAction ? this.leftIcon.onAction : () => {
                                            },
                                            defaultFocus: this.leftIcon.defaultFocus
                                        }),
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon,
                                        imageMenuItemId: `CancelMenuItem_${this.getUniqueId()}`,
                                        editableTitleBarTheme: this.editableTitleBarTheme
                                    };
                                };
                                e7.paramsGenerator_ = f7;
                            } else {
                                this.updateStateVarsOfChildByElmtId(c7, {
                                    item: new EditableTitleBarMenuItemV2({
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: this.leftIcon.onAction ? this.leftIcon.onAction : () => {
                                        },
                                        defaultFocus: this.leftIcon.defaultFocus
                                    }),
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

    isTitleConfig(y6) {
        return y6 instanceof EditableTitleV2;
    }

    getMainTitle() {
        if (typeof this.title === 'string') {
            return this.title;
        }
        if (this.isTitleConfig(this.title)) {
            return this.title.mainTitle;
        }
        return this.title;
    }

    getSubTitle() {
        if (typeof this.title === 'string') {
            return undefined;
        }
        if (this.isTitleConfig(this.title)) {
            return this.title.subTitle;
        }
        return undefined;
    }

    titleLayout(l6 = null) {
        this.observeComponentCreation2((w6, x6) => {
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
        this.observeComponentCreation2((u6, v6) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((s6, t6) => {
            Text.create(this.getMainTitle());
            Text.maxFontSize(TITLE_F_VP);
            Text.minFontSize(SUBTITLE_F_VP);
            Text.fontColor(this.editableTitleBarTheme.titleColor);
            Text.maxLines(this.getSubTitle() ? MAX_LINE_ONE : MAX_LINES_TWO);
            Text.fontWeight(FontWeight.Bold);
            Text.textAlign(TextAlign.Start);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.heightAdaptivePolicy(this.getSubTitle() ?
                TextHeightAdaptivePolicy.MAX_LINES_FIRST : TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
            Text.constraintSize({
                maxHeight: this.getSubTitle() ? EditableTitleBarV2.maxMainTitleHeight : EditableTitleBarV2.totalHeight,
            });
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((m6, n6) => {
            If.create();
            if (this.getSubTitle()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q6, r6) => {
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
                    this.observeComponentCreation2((o6, p6) => {
                        Text.create(this.getSubTitle());
                        Text.maxFontSize(SUBTITLE_F_VP);
                        Text.minFontSize(MIN_SUBTITLE_SIZE);
                        Text.fontColor(this.editableTitleBarTheme.subTitleColor);
                        Text.maxLines(MAX_LINE_ONE);
                        Text.fontWeight(FontWeight.Regular);
                        Text.textAlign(TextAlign.Start);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST);
                        Text.constraintSize({
                            maxHeight: this.getMainTitle() ? EditableTitleBarV2.maxSubTitleHeight :
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

    rightMenuItemsLayout(g6 = null) {
        {
            this.observeComponentCreation2((h6, i6) => {
                if (i6) {
                    let j6 = new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        saveButton: this.saveButton,
                        fontSize: this.fontSize,
                        parentUniqueId: this.getUniqueId(),
                        editableTitleBarTheme: this.editableTitleBarTheme,
                    }, undefined, h6, () => {
                    }, { page: 'library/src/main/ets/components/editabletitlebarv2.ets', line: 552, col: 5 });
                    ViewV2.create(j6);
                    let k6 = () => {
                        return {
                            menuItems: this.menuItems,
                            saveButton: this.saveButton,
                            fontSize: this.fontSize,
                            parentUniqueId: this.getUniqueId(),
                            editableTitleBarTheme: this.editableTitleBarTheme
                        };
                    };
                    j6.paramsGenerator_ = k6;
                } else {
                    this.updateStateVarsOfChildByElmtId(h6, {
                        menuItems: this.menuItems,
                        saveButton: this.saveButton,
                        fontSize: this.fontSize,
                        parentUniqueId: this.getUniqueId(),
                        editableTitleBarTheme: this.editableTitleBarTheme
                    });
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }

    onPlaceChildren(c6, d6, e6) {
        d6.forEach((f6) => {
            f6.layout({ x: 0, y: 0 });
        });
    }

    onMeasureSize(x5, y5, z5) {
        let a6 = { width: x5.width, height: x5.height };
        this.fontSize = this.decideFontScale();
        emitter.emit({ eventId: EVENT_FONT_SIZE_CHANGE }, { data: { fontSize: this.fontSize } });
        y5.forEach((b6) => {
            a6.height = b6.measure(z5).height;
            a6.width = Number(z5.maxWidth);
        });
        return a6;
    }

    updateStateVars(w5) {
        if (w5 === undefined) {
            return;
        }
        if ('leftIcon' in w5) {
            this.updateParam('leftIcon', w5.leftIcon);
        }
        if ('title' in w5) {
            this.updateParam('title', w5.title);
        }
        if ('imageItem' in w5) {
            this.updateParam('imageItem', w5.imageItem);
        }
        if ('menuItems' in w5) {
            this.updateParam('menuItems', w5.menuItems);
        }
        if ('saveButton' in w5) {
            this.updateParam('saveButton', w5.saveButton);
        }
        if ('options' in w5) {
            this.updateParam('options', w5.options);
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
], EditableTitleBarV2.prototype, 'leftIcon', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'title', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'imageItem', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'menuItems', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'saveButton', void 0);
__decorate([
    Param
], EditableTitleBarV2.prototype, 'options', void 0);
__decorate([
    Local
], EditableTitleBarV2.prototype, 'editableTitleBarTheme', void 0);
__decorate([
    Local
], EditableTitleBarV2.prototype, 'fontSize', void 0);

class EditableTitleBarMenuSection extends ViewV2 {
    constructor(q5, r5, s5, t5 = -1, u5, v5) {
        super(q5, t5, v5);
        this.initParam('menuItems', (r5 && 'menuItems' in r5) ? r5.menuItems : undefined);
        this.initParam('saveButton', (r5 && 'saveButton' in r5) ? r5.saveButton : undefined);
        this.initParam('fontSize', (r5 && 'fontSize' in r5) ? r5.fontSize : 1);
        this.initParam('parentUniqueId', (r5 && 'parentUniqueId' in r5) ? r5.parentUniqueId : undefined);
        this.initParam('editableTitleBarTheme',
            (r5 && 'editableTitleBarTheme' in r5) ? r5.editableTitleBarTheme : new EditableTitleBarTheme());
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(p5) {
        this.resetParam('menuItems', (p5 && 'menuItems' in p5) ? p5.menuItems : undefined);
        this.resetParam('saveButton', (p5 && 'saveButton' in p5) ? p5.saveButton : undefined);
        this.resetParam('fontSize', (p5 && 'fontSize' in p5) ? p5.fontSize : 1);
        this.resetParam('parentUniqueId', (p5 && 'parentUniqueId' in p5) ? p5.parentUniqueId : undefined);
        this.resetParam('editableTitleBarTheme',
            (p5 && 'editableTitleBarTheme' in p5) ? p5.editableTitleBarTheme : new EditableTitleBarTheme());
    }

    getIsRequired() {
        if (this.saveButton) {
            return this.saveButton.isRequired;
        }
        return true;
    }

    getDefaultFocus() {
        if (this.saveButton) {
            return this.saveButton.defaultFocus;
        }
        return false;
    }

    getOnAction() {
        if (this.saveButton) {
            return this.saveButton.onAction;
        }
        return undefined;
    }

    initialRender() {
        this.observeComponentCreation2((n5, o5) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((l5, m5) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((z4, a5) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBarV2.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b5, c5) => {
                        ForEach.create();
                        const d5 = (e5, f5) => {
                            const g5 = e5;
                            {
                                this.observeComponentCreation2((h5, i5) => {
                                    if (i5) {
                                        let j5 = new ImageMenuItem(this, {
                                            item: g5,
                                            attribute: ItemType.Icon,
                                            imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${f5}`,
                                            editableTitleBarTheme: this.editableTitleBarTheme,
                                        }, undefined, h5, () => {
                                        }, {
                                            page: 'library/src/main/ets/components/editabletitlebarv2.ets',
                                            line: 616,
                                            col: 15
                                        });
                                        ViewV2.create(j5);
                                        let k5 = () => {
                                            return {
                                                item: g5,
                                                attribute: ItemType.Icon,
                                                imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${f5}`,
                                                editableTitleBarTheme: this.editableTitleBarTheme
                                            };
                                        };
                                        j5.paramsGenerator_ = k5;
                                    } else {
                                        this.updateStateVarsOfChildByElmtId(h5, {
                                            item: g5,
                                            attribute: ItemType.Icon,
                                            imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${f5}`,
                                            editableTitleBarTheme: this.editableTitleBarTheme
                                        });
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(b5,
                            this.menuItems.slice(EditableTitleBarV2.commonZero, this.getIsRequired() ?
                                EditableTitleBarV2.maxOtherCountOfExtraItems : EditableTitleBarV2.maxCountOfExtraItems),
                            d5, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((t4, u4) => {
            If.create();
            if (this.getIsRequired()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((v4, w4) => {
                            if (w4) {
                                let x4 = new ImageMenuItem(this, {
                                    item: new EditableTitleBarMenuItemV2({
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: this.getOnAction() ? this.getOnAction() : () => {
                                        },
                                        defaultFocus: this.getDefaultFocus()
                                    }),
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                    imageMenuItemId: `SaveMenuItem_${this.parentUniqueId}`,
                                    editableTitleBarTheme: this.editableTitleBarTheme,
                                }, undefined, v4, () => {
                                }, {
                                    page: 'library/src/main/ets/components/editabletitlebarv2.ets',
                                    line: 625,
                                    col: 11
                                });
                                ViewV2.create(x4);
                                let y4 = () => {
                                    return {
                                        item: new EditableTitleBarMenuItemV2({
                                            value: PUBLIC_OK,
                                            isEnabled: true,
                                            action: this.getOnAction() ? this.getOnAction() : () => {
                                            },
                                            defaultFocus: this.getDefaultFocus()
                                        }),
                                        fontSize: this.fontSize,
                                        attribute: ItemType.Icon,
                                        imageMenuItemId: `SaveMenuItem_${this.parentUniqueId}`,
                                        editableTitleBarTheme: this.editableTitleBarTheme
                                    };
                                };
                                x4.paramsGenerator_ = y4;
                            } else {
                                this.updateStateVarsOfChildByElmtId(v4, {
                                    item: new EditableTitleBarMenuItemV2({
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: this.getOnAction() ? this.getOnAction() : () => {
                                        },
                                        defaultFocus: this.getDefaultFocus()
                                    }),
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

    updateStateVars(s4) {
        if (s4 === undefined) {
            return;
        }
        if ('menuItems' in s4) {
            this.updateParam('menuItems', s4.menuItems);
        }
        if ('saveButton' in s4) {
            this.updateParam('saveButton', s4.saveButton);
        }
        if ('fontSize' in s4) {
            this.updateParam('fontSize', s4.fontSize);
        }
        if ('parentUniqueId' in s4) {
            this.updateParam('parentUniqueId', s4.parentUniqueId);
        }
        if ('editableTitleBarTheme' in s4) {
            this.updateParam('editableTitleBarTheme', s4.editableTitleBarTheme);
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
], EditableTitleBarMenuSection.prototype, 'saveButton', void 0);
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
    constructor(h4, i4, j4, k4 = -1, l4, m4) {
        super(h4, k4, m4);
        this.initParam('item', (i4 && 'item' in i4) ? i4.item : new EditableTitleBarMenuItemV2());
        this.initParam('attribute', (i4 && 'attribute' in i4) ? i4.attribute : ItemType.Image);
        this.callbackId = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.2;
        this.longPressTime = 500;
        this.systemFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.initParam('fontSize', (i4 && 'fontSize' in i4) ? i4.fontSize : 1);
        this.innerFontSize = 1;
        this.isOnFocus = false;
        this.isOnHover = false;
        this.isOnClick = false;
        this.initParam('imageMenuItemId', (i4 && 'imageMenuItemId' in i4) ? i4.imageMenuItemId : undefined);
        this.initParam('editableTitleBarTheme',
            (i4 && 'editableTitleBarTheme' in i4) ? i4.editableTitleBarTheme : new EditableTitleBarTheme());
        this.dialogId = null;
        this.buttonGestureModifier = null;
        this.envCallback = {
            onConfigurationUpdated: (o4) => {
                if (o4 === undefined || !this.isFollowingSystemFontScale) {
                    this.innerFontSize = 1;
                    return;
                }
                try {
                    this.innerFontSize = Math.min(this.maxFontScale, o4?.fontSizeScale ?? 1);
                    if (this.buttonGestureModifier) {
                        this.buttonGestureModifier.fontSize = this.innerFontSize;
                    }
                } catch (p4) {
                    let q4 = p4?.code;
                    let r4 = p4?.message;
                    hilog.error(0x3900, 'EditableTitleBarV2', `EnvironmentCallback error: ${q4}, ${r4}`);
                }
            },
            onMemoryLevel: (n4) => {
            }
        };
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(g4) {
        this.resetParam('item', (g4 && 'item' in g4) ? g4.item : new EditableTitleBarMenuItemV2());
        this.resetParam('attribute', (g4 && 'attribute' in g4) ? g4.attribute : ItemType.Image);
        this.resetParam('fontSize', (g4 && 'fontSize' in g4) ? g4.fontSize : 1);
        this.innerFontSize = 1;
        this.isOnFocus = false;
        this.isOnHover = false;
        this.isOnClick = false;
        this.resetParam('imageMenuItemId', (g4 && 'imageMenuItemId' in g4) ? g4.imageMenuItemId : undefined);
        this.resetParam('editableTitleBarTheme',
            (g4 && 'editableTitleBarTheme' in g4) ? g4.editableTitleBarTheme : new EditableTitleBarTheme());
        this.buttonGestureModifier = null;
    }

    aboutToAppear() {
        try {
            let f4 = this.getUIContext();
            this.isFollowingSystemFontScale = f4.isFollowingSystemFontScale();
            this.maxFontScale = f4.getMaxFontScale();
        } catch (c4) {
            let d4 = c4?.code;
            let e4 = c4?.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${d4}, message: ${e4}`);
        }
        this.buttonGestureModifier = new ButtonGestureModifier(this.dialogId, () => {
            this.EditableTitleBarDialogBuilder();
        });
        try {
            this.callbackId =
                this.getUIContext()?.getHostContext()?.getApplicationContext()?.on('environment', this.envCallback);
        } catch (z3) {
            let a4 = z3?.code;
            let b4 = z3?.message;
            hilog.error(0x3900, 'EditableTitleBarV2', `Failed to get environment param error: ${a4}, ${b4}`);
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
            let y3 = this.getUIContext();
            this.systemFontScale = y3?.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        } catch (v3) {
            let w3 = v3?.code;
            let x3 = v3?.message;
            hilog.error(0x3900, 'EditableTitleBarV2', `Failed to decideFontScale,cause, code: ${w3}, message: ${x3}`);
            return 1;
        }
    }

    touchEventAction(u3) {
        if (!this.item.isEnabled) {
            return;
        }
        if (u3.type === TouchType.Down) {
            this.isOnClick = true;
        }
        if (u3.type === TouchType.Up || u3.type === TouchType.Cancel) {
            if (this.innerFontSize >= this.minFontSize && this.dialogId !== null) {
                promptAction.closeCustomDialog(this.dialogId);
                this.dialogId = null;
            }
            this.isOnClick = false;
        }
    }

    keyEventAction(t3) {
        if (!this.item.isEnabled) {
            return;
        }
        if (t3.keyCode !== KeyCode.KEYCODE_ENTER && t3.keyCode !== KeyCode.KEYCODE_SPACE) {
            return;
        }
        if (t3.type === KeyType.Down) {
            this.isOnClick = true;
        }
        if (t3.type === KeyType.Up) {
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

    getStringByNameSync(o3) {
        let p3 = '';
        try {
            p3 = getContext()?.resourceManager?.getStringByNameSync(o3);
        } catch (q3) {
            let r3 = q3?.code;
            let s3 = q3?.message;
            hilog.error(0x3900, 'Ace', `Faild to getStringByNameSync,cause, code: ${r3}, message: ${s3}`);
        }
        return p3;
    }

    toStringFormat(j3) {
        if (typeof j3 === 'string' || typeof j3 === 'undefined') {
            return j3;
        } else {
            let k3 = '';
            try {
                if (j3.id === -1) {
                    k3 = getContext()?.resourceManager?.getStringByNameSync(j3.params?.[0]?.split('.').pop() ?? '');
                } else {
                    k3 = getContext()?.resourceManager?.getStringSync(j3);
                }
            } catch (l3) {
                let m3 = l3?.code;
                let n3 = l3?.message;
                hilog.error(0x3900, 'Ace', `Faild to EditableTitleBarV2 toStringFormat, code: ${m3}, message: ${n3}`);
            }
            return k3;
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

    EditableTitleBarDialogBuilder(e3 = null) {
        {
            this.observeComponentCreation2((f3, g3) => {
                if (g3) {
                    let h3 = new EditableTitleBarDialogContent(this, {
                        itemEditableDialog: this.item,
                        textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                        fontSize: this.fontSize,
                    }, undefined, f3, () => {
                    }, { page: 'library/src/main/ets/components/editabletitlebarv2.ets', line: 932, col: 5 });
                    ViewV2.create(h3);
                    let i3 = () => {
                        return {
                            itemEditableDialog: this.item,
                            textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                            fontSize: this.fontSize
                        };
                    };
                    h3.paramsGenerator_ = i3;
                } else {
                    this.updateStateVarsOfChildByElmtId(f3, {
                        itemEditableDialog: this.item,
                        textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                        fontSize: this.fontSize
                    });
                }
            }, { name: 'EditableTitleBarDialogContent' });
        }
    }

    IconBuilder(o2 = null) {
        this.observeComponentCreation2((z2, a3) => {
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
            Button.onHover((d3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = d3;
            });
            Button.onKeyEvent((c3) => {
                this.keyEventAction(c3);
            });
            Button.onTouch((b3) => {
                this.touchEventAction(b3);
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
        this.observeComponentCreation2((p2, q2) => {
            If.create();
            if (this.item.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x2, y2) => {
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
                    this.observeComponentCreation2((r2, s2) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((v2, w2) => {
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
                                this.observeComponentCreation2((t2, u2) => {
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

    ImageBuilder(e2 = null) {
        this.observeComponentCreation2((m2, n2) => {
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
        this.observeComponentCreation2((k2, l2) => {
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
        this.observeComponentCreation2((f2, g2) => {
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
            Button.onHover((j2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = j2;
            });
            Button.onKeyEvent((i2) => {
                this.keyEventAction(i2);
            });
            Button.onTouch((h2) => {
                this.touchEventAction(h2);
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
        this.observeComponentCreation2((c2, d2) => {
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

    updateStateVars(b2) {
        if (b2 === undefined) {
            return;
        }
        if ('item' in b2) {
            this.updateParam('item', b2.item);
        }
        if ('attribute' in b2) {
            this.updateParam('attribute', b2.attribute);
        }
        if ('fontSize' in b2) {
            this.updateParam('fontSize', b2.fontSize);
        }
        if ('imageMenuItemId' in b2) {
            this.updateParam('imageMenuItemId', b2.imageMenuItemId);
        }
        if ('editableTitleBarTheme' in b2) {
            this.updateParam('editableTitleBarTheme', b2.editableTitleBarTheme);
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
    constructor(v1, w1, x1, y1 = -1, z1, a2) {
        super(v1, y1, a2);
        this.initParam('itemEditableDialog',
            (w1 && 'itemEditableDialog' in w1) ? w1.itemEditableDialog : new EditableTitleBarMenuItemV2());
        this.callbackId = undefined;
        this.initParam('textEditableTitleBarDialog',
            (w1 && 'textEditableTitleBarDialog' in w1) ? w1.textEditableTitleBarDialog : '');
        this.mainWindowStage = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.2;
        this.screenWidth = 640;
        this.verticalScreenLines = 6;
        this.horizontalsScreenLines = 1;
        this.mainWindow = undefined;
        this.initParam('fontSize', (w1 && 'fontSize' in w1) ? w1.fontSize : 1);
        this.maxLines = 1;
        this.windowStandardHeight = 0;
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(u1) {
        this.resetParam('itemEditableDialog',
            (u1 && 'itemEditableDialog' in u1) ? u1.itemEditableDialog : new EditableTitleBarMenuItemV2());
        this.resetParam('textEditableTitleBarDialog',
            (u1 && 'textEditableTitleBarDialog' in u1) ? u1.textEditableTitleBarDialog : '');
        this.resetParam('fontSize', (u1 && 'fontSize' in u1) ? u1.fontSize : 1);
        this.maxLines = 1;
    }

    initialRender() {
        this.observeComponentCreation2((q, r) => {
            If.create();
            if (this.textEditableTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s1, t1) => {
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
                    this.observeComponentCreation2((i1, j1) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((q1, r1) => {
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
                                this.observeComponentCreation2((k1, l1) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((o1, p1) => {
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
                                            this.observeComponentCreation2((m1, n1) => {
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
                    this.observeComponentCreation2((g1, h1) => {
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
                    this.observeComponentCreation2((e1, f1) => {
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
                    this.observeComponentCreation2((c1, d1) => {
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
                    this.observeComponentCreation2((s, t) => {
                        If.create();
                        if (this.itemEditableDialog.symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((a1, b1) => {
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
                                this.observeComponentCreation2((u, v) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemEditableDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((y, z) => {
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
                                            this.observeComponentCreation2((w, x) => {
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
            let p = this.getUIContext().getHostContext();
            this.mainWindowStage = p.windowStage.getMainWindowSync();
        } catch (m) {
            let n = m?.code;
            let o = m?.message;
            hilog.error(0x3900, 'Ace', `EditableTitleBarV2 getMainWindowStage error, code: ${n},message:${o}`);
            return;
        }
        if (this.mainWindowStage) {
            let k = this.mainWindowStage.getWindowProperties();
            let l = k.windowRect;
            if (px2vp(l.height) > this.screenWidth) {
                this.maxLines = this.verticalScreenLines;
            } else {
                this.maxLines = this.horizontalsScreenLines;
            }
        }
    }

    updateStateVars(j) {
        if (j === undefined) {
            return;
        }
        if ('itemEditableDialog' in j) {
            this.updateParam('itemEditableDialog', j.itemEditableDialog);
        }
        if ('textEditableTitleBarDialog' in j) {
            this.updateParam('textEditableTitleBarDialog', j.textEditableTitleBarDialog);
        }
        if ('fontSize' in j) {
            this.updateParam('fontSize', j.fontSize);
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
        hilog.error(0x3900, 'Ace', `EditableTitleBarV2 getNumberByResource error, code: ${g},message:${h}`);
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
    EditableLeftIconTypeV2,
    EditableTitleBarV2,
    EditableLeftIconV2,
    EditableTitleV2,
    EditableTitleBarMenuItemV2,
    EditableSaveButtonV2,
    EditableTitleBarStyleV2
}