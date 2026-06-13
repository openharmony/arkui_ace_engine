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
var __decorate = (this && this.__decorate) || function (k10, l10, m10, n10) {
    var o10 = arguments.length,
        p10 = o10 < 3 ? l10 : n10 === null ? n10 = Object.getOwnPropertyDescriptor(l10, m10) : n10, q10;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        p10 = Reflect.decorate(k10, l10, m10, n10);
    } else {
        for (var r10 = k10.length - 1; r10 >= 0; r10--) {
            if (q10 = k10[r10]) {
                p10 = (o10 < 3 ? q10(p10) : o10 > 3 ? q10(l10, m10, p10) : q10(l10, m10)) || p10;
            }
        }
    }
    return o10 > 3 && p10 && Object.defineProperty(l10, m10, p10), p10;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const hilog = requireNapi('hilog');
const promptAction = requireNapi('promptAction');

let ComposeTitleBarV2MenuItem = class ComposeTitleBarV2MenuItem {
    constructor(j10) {
        this.isEnabled = true;
        this.accessibilityLevel = 'auto';
        if (j10) {
            this.value = j10.value;
            this.symbolStyle = j10.symbolStyle;
            this.isEnabled = j10.isEnabled ?? true;
            this.action = j10.action;
            this.label = j10.label;
            this.accessibilityText = j10.accessibilityText;
            this.accessibilityLevel = j10.accessibilityLevel ?? 'auto';
            this.accessibilityDescription = j10.accessibilityDescription;
        } else {
            this.value = '';
            this.isEnabled = true;
            this.accessibilityLevel = 'auto';
        }
    }
};
__decorate([
    Trace
], ComposeTitleBarV2MenuItem.prototype, 'value', void 0);
__decorate([
    Trace
], ComposeTitleBarV2MenuItem.prototype, 'symbolStyle', void 0);
__decorate([
    Trace
], ComposeTitleBarV2MenuItem.prototype, 'isEnabled', void 0);
__decorate([
    Trace
], ComposeTitleBarV2MenuItem.prototype, 'action', void 0);
__decorate([
    Trace
], ComposeTitleBarV2MenuItem.prototype, 'label', void 0);
__decorate([
    Trace
], ComposeTitleBarV2MenuItem.prototype, 'accessibilityText', void 0);
__decorate([
    Trace
], ComposeTitleBarV2MenuItem.prototype, 'accessibilityLevel', void 0);
__decorate([
    Trace
], ComposeTitleBarV2MenuItem.prototype, 'accessibilityDescription', void 0);
ComposeTitleBarV2MenuItem = __decorate([
    ObservedV2
], ComposeTitleBarV2MenuItem);

export { ComposeTitleBarV2MenuItem };
const PUBLIC_MORE = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.dot_grid_2x2'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const PUBLIC_BACK = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.arrow_left'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const RESOURCE_TYPE_SYMBOL = 40000;
const SCREEN_WIDTH_BREAK_POINT = 640;
const VERTICAL_SCREEN_TEXT_MAX_LINES = 6;
const HORIZONTAL_SCREEN_TEXT_MAX_LINES = 1;

class Util {
    static isSymbolResource(h10) {
        if (!Util.isResourceType(h10)) {
            return false;
        }
        let i10 = h10;
        return i10.type === RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(g10) {
        if (!g10) {
            return false;
        }
        if (typeof g10 === 'string' || typeof g10 === 'undefined') {
            return false;
        }
        return true;
    }
}

class ButtonGestureModifier {
    constructor() {
        this.gestureCallBack = undefined;
    }

    applyGesture(f10) {
        this.gestureCallBack?.(f10);
    }
}

ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;

export class ComposeTitleBarV2 extends ViewV2 {
    constructor(z9, a10, b10, c10 = -1, d10, e10) {
        super(z9, c10, e10);
        this.initParam('item', (a10 && 'item' in a10) ? a10.item : undefined);
        this.initParam('title', (a10 && 'title' in a10) ? a10.title : '');
        this.initParam('subtitle', (a10 && 'subtitle' in a10) ? a10.subtitle : '');
        this.initParam('menuItems', (a10 && 'menuItems' in a10) ? a10.menuItems : []);
        this.titleMaxWidth = 0;
        this.fontSize = 1;
        this.uniqueId = -1;
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(y9) {
        this.resetParam('item', (y9 && 'item' in y9) ? y9.item : undefined);
        this.resetParam('title', (y9 && 'title' in y9) ? y9.title : '');
        this.resetParam('subtitle', (y9 && 'subtitle' in y9) ? y9.subtitle : '');
        this.resetParam('menuItems', (y9 && 'menuItems' in y9) ? y9.menuItems : []);
        this.titleMaxWidth = 0;
        this.fontSize = 1;
        this.uniqueId = -1;
    }

    initialRender() {
        this.observeComponentCreation2((n9, o9) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.onAppear(() => {
                try {
                    let w9 = this.getUIContext().getFrameNodeByUniqueId(this.getUniqueId());
                    if (w9) {
                        let x9 = w9.getFirstChild();
                        if (x9) {
                            this.uniqueId = x9.getUniqueId() ?? -1;
                        }
                    }
                } catch (t9) {
                    let u9 = t9?.code;
                    let v9 = t9?.message;
                    hilog.error(0x3900, 'ComposeTitleBarV2',
                        `Faild to getFrameNodeByUniqueId,cause, code: ${u9}, message: ${v9}`);
                }
            });
            Flex.width('100%');
            Flex.height(ComposeTitleBarV2.totalHeight);
            Flex.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Flex.onAreaChange((p9, q9) => {
                let r9 = Number(q9.width);
                if (this.menuItems !== undefined) {
                    let s9 = this.menuItems.length;
                    if (s9 >= CollapsibleMenuSectionV2.maxCountOfVisibleItems) {
                        r9 = r9 - ImageMenuItemV2.imageHotZoneWidth * CollapsibleMenuSectionV2.maxCountOfVisibleItems;
                    } else if (s9 > 0) {
                        r9 = r9 - ImageMenuItemV2.imageHotZoneWidth * s9;
                    }
                }
                this.titleMaxWidth = r9;
                this.titleMaxWidth -= ComposeTitleBarV2.leftPadding;
                this.titleMaxWidth -= ImageMenuItemV2.imageHotZoneWidth;
                if (this.item !== undefined) {
                    this.titleMaxWidth -= ComposeTitleBarV2.portraitImageLeftPadding +
                        ComposeTitleBarV2.portraitImageSize +
                        ComposeTitleBarV2.portraitImageRightPadding;
                }
                this.titleMaxWidth -= ComposeTitleBarV2.rightPadding;
            });
        }, Flex);
        this.observeComponentCreation2((l9, m9) => {
            Row.create();
            Row.margin({
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_default_padding_start'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
        }, Row);
        {
            this.observeComponentCreation2((h9, i9) => {
                if (i9) {
                    let j9 = new ImageMenuItemV2(this, {
                        item: new ComposeTitleBarV2MenuItem({
                            value: PUBLIC_BACK,
                            isEnabled: true,
                            action: () => this.getUIContext()?.getRouter()?.back()
                        }),
                        index: -1,
                        itemIndex: -1
                    }, undefined, h9, () => {
                    }, { page: 'library/src/main/ets/components/composetitlebarv2.ets', line: 144, col: 9 });
                    ViewV2.create(j9);
                    let k9 = () => {
                        return {
                            item: new ComposeTitleBarV2MenuItem({
                                value: PUBLIC_BACK,
                                isEnabled: true,
                                action: () => this.getUIContext()?.getRouter()?.back()
                            }),
                            index: -1,
                            itemIndex: -1
                        };
                    };
                    j9.paramsGenerator_ = k9;
                } else {
                    this.updateStateVarsOfChildByElmtId(h9, {
                        item: new ComposeTitleBarV2MenuItem({
                            value: PUBLIC_BACK,
                            isEnabled: true,
                            action: () => this.getUIContext()?.getRouter()?.back()
                        }),
                        index: -1,
                        itemIndex: -1
                    });
                }
            }, { name: 'ImageMenuItemV2' });
        }
        this.observeComponentCreation2((f9, g9) => {
            Row.create();
            Row.accessibilityGroup(true);
            Row.accessibilityDescription({
                'id': -1,
                'type': 10003,
                params: ['sys.string.subheader_accessibility_title'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
        }, Row);
        this.observeComponentCreation2((b9, c9) => {
            If.create();
            if (this.item !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d9, e9) => {
                        Image.create(this.item.value);
                        Image.width(ComposeTitleBarV2.portraitImageSize);
                        Image.height(ComposeTitleBarV2.portraitImageSize);
                        Image.margin({
                            left: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_text_paragraph_margin_xs'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            right: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_text_paragraph_margin_m'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            }
                        });
                        Image.focusable(false);
                        Image.borderRadius(ImageMenuItemV2.buttonBorderRadius);
                    }, Image);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((z8, a9) => {
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.titleMaxWidth });
        }, Column);
        this.observeComponentCreation2((t8, u8) => {
            If.create();
            if (this.title !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x8, y8) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((v8, w8) => {
                        Text.create(this.title);
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_headline8'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_titlebar_text'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.maxLines(this.subtitle !== undefined ? 1 : 2);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.constraintSize({ maxWidth: this.titleMaxWidth });
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
        this.observeComponentCreation2((n8, o8) => {
            If.create();
            if (this.subtitle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r8, s8) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((p8, q8) => {
                        Text.create(this.subtitle);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_over_line'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_titlebar_subtitle_text'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.maxLines(1);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.constraintSize({ maxWidth: this.titleMaxWidth });
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
        Row.pop();
        Row.pop();
        this.observeComponentCreation2((h8, i8) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((j8, k8) => {
                            if (k8) {
                                let l8 = new CollapsibleMenuSectionV2(this, {
                                    menuItems: this.menuItems,
                                    index: 1 + ComposeTitleBarV2.instanceCount++
                                }, undefined, j8, () => {
                                }, {
                                    page: 'library/src/main/ets/components/composetitlebarv2.ets',
                                    line: 202,
                                    col: 9
                                });
                                ViewV2.create(l8);
                                let m8 = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + ComposeTitleBarV2.instanceCount++
                                    };
                                };
                                l8.paramsGenerator_ = m8;
                            } else {
                                this.updateStateVarsOfChildByElmtId(j8, {
                                    menuItems: this.menuItems,
                                    index: 1 + ComposeTitleBarV2.instanceCount++
                                });
                            }
                        }, { name: 'CollapsibleMenuSectionV2' });
                    }
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
    }

    updateStateVars(g8) {
        if (g8 === undefined) {
            return;
        }
        if ('item' in g8) {
            this.updateParam('item', g8.item);
        }
        if ('title' in g8) {
            this.updateParam('title', g8.title);
        }
        if ('subtitle' in g8) {
            this.updateParam('subtitle', g8.subtitle);
        }
        if ('menuItems' in g8) {
            this.updateParam('menuItems', g8.menuItems);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}
ComposeTitleBarV2.totalHeight = 56;
ComposeTitleBarV2.leftPadding = 12;
ComposeTitleBarV2.rightPadding = 12;
ComposeTitleBarV2.portraitImageSize = 40;
ComposeTitleBarV2.portraitImageLeftPadding = 4;
ComposeTitleBarV2.portraitImageRightPadding = 16;
ComposeTitleBarV2.instanceCount = 0;
__decorate([
    Param
], ComposeTitleBarV2.prototype, 'item', void 0);
__decorate([
    Param
], ComposeTitleBarV2.prototype, 'title', void 0);
__decorate([
    Param
], ComposeTitleBarV2.prototype, 'subtitle', void 0);
__decorate([
    Param
], ComposeTitleBarV2.prototype, 'menuItems', void 0);
__decorate([
    Local
], ComposeTitleBarV2.prototype, 'titleMaxWidth', void 0);
__decorate([
    Local
], ComposeTitleBarV2.prototype, 'fontSize', void 0);
__decorate([
    Provider('uniqueIdV2')
], ComposeTitleBarV2.prototype, 'uniqueId', void 0);

class CollapsibleMenuSectionV2 extends ViewV2 {
    constructor(a8, b8, c8, d8 = -1, e8, f8) {
        super(a8, d8, f8);
        this.initParam('menuItems', (b8 && 'menuItems' in b8) ? b8.menuItems : []);
        this.initParam('item', (b8 && 'item' in b8) ? b8.item : new ComposeTitleBarV2MenuItem({
            value: PUBLIC_MORE,
            label: {
                'id': -1,
                'type': 10003,
                params: ['sys.string.ohos_toolbar_more'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        }));
        this.initParam('index', (b8 && 'index' in b8) ? b8.index : 0);
        this.isPopupShown = false;
        this.isMoreIconOnFocus = false;
        this.isMoreIconOnHover = false;
        this.isMoreIconOnClick = false;
        this.fontSize = 1;
        this.itemDialogId = undefined;
        this.dialogTextMaxLine = 1;
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.firstFocusableIndex = -1;
        this.buttonGestureModifier = new ButtonGestureModifier();
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(z7) {
        this.resetParam('menuItems', (z7 && 'menuItems' in z7) ? z7.menuItems : []);
        this.resetParam('item', (z7 && 'item' in z7) ? z7.item : new ComposeTitleBarV2MenuItem({
            value: PUBLIC_MORE,
            label: {
                'id': -1,
                'type': 10003,
                params: ['sys.string.ohos_toolbar_more'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        }));
        this.resetParam('index', (z7 && 'index' in z7) ? z7.index : 0);
        this.isPopupShown = false;
        this.isMoreIconOnFocus = false;
        this.isMoreIconOnHover = false;
        this.isMoreIconOnClick = false;
        this.fontSize = 1;
        this.itemDialogId = undefined;
        this.dialogTextMaxLine = 1;
    }

    getMoreIconFgColor() {
        return this.isMoreIconOnClick ? {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_titlebar_icon_pressed'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        } : {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_titlebar_icon'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
    }

    getMoreIconBgColor() {
        if (this.isMoreIconOnClick) {
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_click_effect'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else if (this.isMoreIconOnHover) {
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_hover'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else {
            return Color.Transparent;
        }
    }

    aboutToAppear() {
        try {
            let y7 = this.getUIContext();
            this.isFollowingSystemFontScale = y7.isFollowingSystemFontScale();
            this.maxFontScale = y7.getMaxFontScale();
        } catch (v7) {
            let w7 = v7?.code;
            let x7 = v7?.message;
            hilog.error(0x3900, 'ComposeTitleBarV2',
                `Failed to init fontsizescale info, cause, code: ${w7}, message: ${x7}`);
        }
        if (this.menuItems) {
            this.menuItems.forEach((t7, u7) => {
                if (t7.isEnabled && this.firstFocusableIndex === -1 &&
                    u7 > CollapsibleMenuSectionV2.maxCountOfVisibleItems - 2) {
                    this.firstFocusableIndex = this.index * 1000 + u7 + 1;
                }
            });
        }
        this.fontSize = this.decideFontScale();
    }

    decideFontScale() {
        try {
            let s7 = this.getUIContext();
            this.systemFontScale = s7.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        } catch (p7) {
            let q7 = p7?.code;
            let r7 = p7?.message;
            hilog.error(0x3900, 'ComposeTitleBarV2', `Faild to decideFontScale,cause, code: ${q7}, message: ${r7}`);
            return 1;
        }
    }

    itemCardDialogBuilder(j6, k6 = null) {
        this.observeComponentCreation2((l6, m6) => {
            If.create();
            if (j6.label) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n7, o7) => {
                        Column.create();
                        Column.constraintSize({
                            minHeight: this.fontSize === ButtonGestureModifier.minFontSize ? MAX_DIALOG : MIN_DIALOG
                        });
                    }, Column);
                    this.observeComponentCreation2((d7, e7) => {
                        If.create();
                        if (j6.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((l7, m7) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                    SymbolGlyph.attributeModifier.bind(this)(j6.symbolStyle);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
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
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((f7, g7) => {
                                    If.create();
                                    if (Util.isSymbolResource(j6.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((j7, k7) => {
                                                SymbolGlyph.create(j6.value);
                                                SymbolGlyph.fontSize(IMAGE_SIZE);
                                                SymbolGlyph.fontColor([{
                                                    'id': -1,
                                                    'type': 10001,
                                                    params: ['sys.color.icon_primary'],
                                                    'bundleName': '__harDefaultBundleName__',
                                                    'moduleName': '__harDefaultModuleName__'
                                                }]);
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
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((h7, i7) => {
                                                Image.create(j6.value);
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
                    this.observeComponentCreation2((b7, c7) => {
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
                    this.observeComponentCreation2((z6, a7) => {
                        Text.create(j6.label);
                        Text.fontSize(TEXT_EDITABLE_DIALOG);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(this.dialogTextMaxLine);
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
                    this.observeComponentCreation2((x6, y6) => {
                        Column.create();
                        Column.constraintSize({
                            minHeight: this.fontSize === ButtonGestureModifier.minFontSize ? MAX_DIALOG : MIN_DIALOG
                        });
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((n6, o6) => {
                        If.create();
                        if (j6.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((v6, w6) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                    SymbolGlyph.attributeModifier.bind(this)(j6.symbolStyle);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((p6, q6) => {
                                    If.create();
                                    if (Util.isSymbolResource(j6.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((t6, u6) => {
                                                SymbolGlyph.create(j6.value);
                                                SymbolGlyph.fontSize(IMAGE_SIZE);
                                                SymbolGlyph.fontColor([{
                                                    'id': -1,
                                                    'type': 10001,
                                                    params: ['sys.color.icon_primary'],
                                                    'bundleName': '__harDefaultBundleName__',
                                                    'moduleName': '__harDefaultModuleName__'
                                                }]);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((r6, s6) => {
                                                Image.create(j6.value);
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

    initialRender() {
        this.observeComponentCreation2((h6, i6) => {
            Column.create();
            Column.height('100%');
            Column.margin({
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_default_padding_end'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((f6, g6) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((a5, b5) => {
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c5, d5) => {
                        If.create();
                        if (this.menuItems.length <= CollapsibleMenuSectionV2.maxCountOfVisibleItems) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((v5, w5) => {
                                    ForEach.create();
                                    const x5 = (y5, z5) => {
                                        const a6 = y5;
                                        {
                                            this.observeComponentCreation2((b6, c6) => {
                                                if (c6) {
                                                    let d6 = new ImageMenuItemV2(this,
                                                        { item: a6, index: this.index * 1000 + z5 + 1, itemIndex: z5 },
                                                        undefined, b6, () => {
                                                        }, {
                                                            page: 'library/src/main/ets/components/composetitlebarv2.ets',
                                                            line: 425,
                                                            col: 15
                                                        });
                                                    ViewV2.create(d6);
                                                    let e6 = () => {
                                                        return {
                                                            item: a6,
                                                            index: this.index * 1000 + z5 + 1,
                                                            itemIndex: z5
                                                        };
                                                    };
                                                    d6.paramsGenerator_ = e6;
                                                } else {
                                                    this.updateStateVarsOfChildByElmtId(b6, {
                                                        item: a6, index: this.index * 1000 + z5 + 1, itemIndex: z5
                                                    });
                                                }
                                            }, { name: 'ImageMenuItemV2' });
                                        }
                                    };
                                    this.forEachUpdateFunction(v5, this.menuItems, x5, undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((l5, m5) => {
                                    ForEach.create();
                                    const n5 = (o5, p5) => {
                                        const q5 = o5;
                                        {
                                            this.observeComponentCreation2((r5, s5) => {
                                                if (s5) {
                                                    let t5 = new ImageMenuItemV2(this,
                                                        { item: q5, index: this.index * 1000 + p5 + 1, itemIndex: p5 },
                                                        undefined, r5, () => {
                                                        }, {
                                                            page: 'library/src/main/ets/components/composetitlebarv2.ets',
                                                            line: 430,
                                                            col: 17
                                                        });
                                                    ViewV2.create(t5);
                                                    let u5 = () => {
                                                        return {
                                                            item: q5,
                                                            index: this.index * 1000 + p5 + 1,
                                                            itemIndex: p5
                                                        };
                                                    };
                                                    t5.paramsGenerator_ = u5;
                                                } else {
                                                    this.updateStateVarsOfChildByElmtId(r5, {
                                                        item: q5, index: this.index * 1000 + p5 + 1, itemIndex: p5
                                                    });
                                                }
                                            }, { name: 'ImageMenuItemV2' });
                                        }
                                    };
                                    this.forEachUpdateFunction(l5,
                                        this.menuItems.slice(0, CollapsibleMenuSectionV2.maxCountOfVisibleItems - 1),
                                        n5, undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                                this.observeComponentCreation2((g5, h5) => {
                                    Button.createWithChild({ type: ButtonType.Normal, stateEffect: true });
                                    Button.accessibilityText({
                                        'id': -1,
                                        'type': 10003,
                                        params: ['sys.string.ohos_toolbar_more'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
                                    Button.width(ImageMenuItemV2.imageHotZoneWidth);
                                    Button.height(ImageMenuItemV2.imageHotZoneWidth);
                                    Button.borderRadius(ImageMenuItemV2.buttonBorderRadius);
                                    Button.foregroundColor(this.getMoreIconFgColor());
                                    Button.backgroundColor(this.getMoreIconBgColor());
                                    ViewStackProcessor.visualState('focused');
                                    Button.border({
                                        radius: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.ohos_id_corner_radius_clicked'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        width: ImageMenuItemV2.focusBorderWidth,
                                        color: {
                                            'id': -1,
                                            'type': 10001,
                                            params: ['sys.color.ohos_id_color_focused_outline'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        style: BorderStyle.Solid
                                    });
                                    ViewStackProcessor.visualState('normal');
                                    Button.border({
                                        radius: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.ohos_id_corner_radius_clicked'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        width: 0
                                    });
                                    ViewStackProcessor.visualState();
                                    Button.onFocus(() => this.isMoreIconOnFocus = true);
                                    Button.onBlur(() => this.isMoreIconOnFocus = false);
                                    Button.onHover((k5) => this.isMoreIconOnHover = k5);
                                    Button.onKeyEvent((j5) => {
                                        if (j5.keyCode !== KeyCode.KEYCODE_ENTER &&
                                            j5.keyCode !== KeyCode.KEYCODE_SPACE) {
                                            return;
                                        }
                                        if (j5.type === KeyType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (j5.type === KeyType.Up) {
                                            this.isMoreIconOnClick = false;
                                        }
                                    });
                                    Button.onTouch((i5) => {
                                        if (i5.type === TouchType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (i5.type === TouchType.Up || i5.type === TouchType.Cancel) {
                                            this.isMoreIconOnClick = false;
                                            if (this.fontSize >= this.minFontSize && this.itemDialogId) {
                                                promptAction.closeCustomDialog(this.itemDialogId);
                                            }
                                        }
                                    });
                                    Button.onClick(() => this.isPopupShown = true);
                                    Button.gestureModifier(this.getItemGestureModifier());
                                    Button.bindPopup(this.isPopupShown, {
                                        builder: { builder: this.popupBuilder.bind(this) },
                                        placement: Placement.Bottom,
                                        popupColor: Color.White,
                                        enableArrow: false,
                                        onStateChange: (e) => {
                                            this.isPopupShown = e.isVisible;
                                            if (!e.isVisible) {
                                                this.isMoreIconOnClick = false;
                                            }
                                        }
                                    });
                                }, Button);
                                this.observeComponentCreation2((e5, f5) => {
                                    SymbolGlyph.create(PUBLIC_MORE);
                                    SymbolGlyph.fontSize(`${ImageMenuItemV2.imageSize}vp`);
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(true);
                                }, SymbolGlyph);
                                Button.pop();
                            });
                        }
                    }, If);
                    If.pop();
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

    getItemGestureModifier() {
        this.buttonGestureModifier.gestureCallBack = (s4) => {
            if (this.fontSize >= ButtonGestureModifier.minFontSize) {
                s4.addGesture(new LongPressGestureHandler({
                    repeat: false,
                    duration: ButtonGestureModifier.longPressTime
                })
                    .onAction(() => {
                        promptAction.openCustomDialog({
                            builder: () => {
                                this.itemCardDialogBuilder(this.item);
                            },
                            onWillAppear: () => {
                                try {
                                    let x4 = this.getUIContext().getHostContext();
                                    let y4 = x4.windowStage.getMainWindowSync();
                                    let z4 = y4.getWindowProperties();
                                    if (px2vp(z4.windowRect.height) > SCREEN_WIDTH_BREAK_POINT) {
                                        this.dialogTextMaxLine = VERTICAL_SCREEN_TEXT_MAX_LINES;
                                    } else {
                                        this.dialogTextMaxLine = HORIZONTAL_SCREEN_TEXT_MAX_LINES;
                                    }
                                } catch (u4) {
                                    let v4 = u4?.code;
                                    let w4 = u4?.message;
                                    hilog.error(0x3900, 'ComposeTitleBarV2',
                                        `Faild to get window height, code: ${v4}, message: ${w4}`);
                                }
                            },
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
                            width: this.fontSize === ButtonGestureModifier.minFontSize ? MAX_DIALOG : MIN_DIALOG
                        }).then((t4) => {
                            this.itemDialogId = t4;
                        });
                    })
                    .onActionEnd(() => {
                        if (this.itemDialogId) {
                            promptAction.closeCustomDialog(this.itemDialogId);
                        }
                    })
                    .onActionCancel(() => {
                        if (this.itemDialogId) {
                            promptAction.closeCustomDialog(this.itemDialogId);
                        }
                    }));
                return;
            }
            s4.clearGestures();
        };
        return this.buttonGestureModifier;
    }

    onPlaceChildren(o4, p4, q4) {
        p4.forEach((r4) => {
            r4.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }

    popupBuilder(z3 = null) {
        this.observeComponentCreation2((m4, n4) => {
            Column.create();
            Column.width(ImageMenuItemV2.imageHotZoneWidth +
                CollapsibleMenuSectionV2.focusPadding * CollapsibleMenuSectionV2.marginsNum);
            Column.margin({
                top: CollapsibleMenuSectionV2.focusPadding,
                bottom: CollapsibleMenuSectionV2.focusPadding
            });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItemV2.focusablePrefix +
                    this.firstFocusableIndex);
            });
        }, Column);
        this.observeComponentCreation2((a4, b4) => {
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c4, d4) => {
                        ForEach.create();
                        const e4 = (f4, g4) => {
                            const h4 = f4;
                            {
                                this.observeComponentCreation2((i4, j4) => {
                                    if (j4) {
                                        let k4 = new ImageMenuItemV2(this, {
                                            item: h4, index: this.index * 1000 +
                                                CollapsibleMenuSectionV2.maxCountOfVisibleItems + g4,
                                            isPopup: false
                                        }, undefined, i4, () => {
                                        }, {
                                            page: 'library/src/main/ets/components/composetitlebarv2.ets',
                                            line: 569,
                                            col: 13
                                        });
                                        ViewV2.create(k4);
                                        let l4 = () => {
                                            return {
                                                item: h4,
                                                index: this.index * 1000 +
                                                    CollapsibleMenuSectionV2.maxCountOfVisibleItems + g4,
                                                isPopup: false
                                            };
                                        };
                                        k4.paramsGenerator_ = l4;
                                    } else {
                                        this.updateStateVarsOfChildByElmtId(i4, {
                                            item: h4, index: this.index * 1000 +
                                                CollapsibleMenuSectionV2.maxCountOfVisibleItems + g4,
                                            isPopup: false
                                        });
                                    }
                                }, { name: 'ImageMenuItemV2' });
                            }
                        };
                        this.forEachUpdateFunction(c4,
                            this.menuItems.slice(CollapsibleMenuSectionV2.maxCountOfVisibleItems - 1,
                                this.menuItems.length), e4, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    updateStateVars(y3) {
        if (y3 === undefined) {
            return;
        }
        if ('menuItems' in y3) {
            this.updateParam('menuItems', y3.menuItems);
        }
        if ('item' in y3) {
            this.updateParam('item', y3.item);
        }
        if ('index' in y3) {
            this.updateParam('index', y3.index);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

CollapsibleMenuSectionV2.maxCountOfVisibleItems = 3;
CollapsibleMenuSectionV2.focusPadding = 4;
CollapsibleMenuSectionV2.marginsNum = 2;
__decorate([
    Param
], CollapsibleMenuSectionV2.prototype, 'menuItems', void 0);
__decorate([
    Param
], CollapsibleMenuSectionV2.prototype, 'item', void 0);
__decorate([
    Param
], CollapsibleMenuSectionV2.prototype, 'index', void 0);
__decorate([
    Local
], CollapsibleMenuSectionV2.prototype, 'isPopupShown', void 0);
__decorate([
    Local
], CollapsibleMenuSectionV2.prototype, 'isMoreIconOnFocus', void 0);
__decorate([
    Local
], CollapsibleMenuSectionV2.prototype, 'isMoreIconOnHover', void 0);
__decorate([
    Local
], CollapsibleMenuSectionV2.prototype, 'isMoreIconOnClick', void 0);
__decorate([
    Local
], CollapsibleMenuSectionV2.prototype, 'fontSize', void 0);
__decorate([
    Local
], CollapsibleMenuSectionV2.prototype, 'itemDialogId', void 0);
__decorate([
    Local
], CollapsibleMenuSectionV2.prototype, 'dialogTextMaxLine', void 0);

class ImageMenuItemV2 extends ViewV2 {
    constructor(s3, t3, u3, v3 = -1, w3, x3) {
        super(s3, v3, x3);
        this.initParam('item', (t3 && 'item' in t3) ? t3.item : new ComposeTitleBarV2MenuItem());
        this.initParam('index', (t3 && 'index' in t3) ? t3.index : 0);
        this.initParam('itemIndex', (t3 && 'itemIndex' in t3) ? t3.itemIndex : 0);
        this.initParam('isPopup', (t3 && 'isPopup' in t3) ? t3.isPopup : true);
        this.isOnFocus = false;
        this.isOnHover = false;
        this.isOnClick = false;
        this.fontSize = 1;
        this.itemDialogId = undefined;
        this.dialogTextMaxLine = 1;
        this.parentParentUniqueId = -1;
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.buttonGestureModifier = new ButtonGestureModifier();
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(r3) {
        this.resetParam('item', (r3 && 'item' in r3) ? r3.item : new ComposeTitleBarV2MenuItem());
        this.resetParam('index', (r3 && 'index' in r3) ? r3.index : 0);
        this.resetParam('itemIndex', (r3 && 'itemIndex' in r3) ? r3.itemIndex : 0);
        this.resetParam('isPopup', (r3 && 'isPopup' in r3) ? r3.isPopup : true);
        this.isOnFocus = false;
        this.isOnHover = false;
        this.isOnClick = false;
        this.fontSize = 1;
        this.itemDialogId = undefined;
        this.dialogTextMaxLine = 1;
        this.resetConsumer('parentParentUniqueId', -1);
    }

    textDialog() {
        if (this.item.value === PUBLIC_MORE) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.ohos_toolbar_more'],
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

    toStringFormat(m3) {
        if (typeof m3 === 'string') {
            return m3;
        } else if (typeof m3 === 'undefined') {
            return '';
        } else {
            let n3 = '';
            try {
                if (m3.id === -1) {
                    n3 = getContext()?.resourceManager?.getStringByNameSync(m3.params?.[0].split('.').pop());
                } else {
                    n3 = getContext()?.resourceManager?.getStringSync(m3);
                }
            } catch (o3) {
                let p3 = o3?.code;
                let q3 = o3?.message;
                hilog.error(0x3900, 'Ace', `Faild to ComposeTitleBarV2 toStringFormat,code: ${p3},message:${q3}`);
            }
            return n3;
        }
    }

    getAccessibilityReadText() {
        if (this.item.value === PUBLIC_BACK) {
            try {
                return getContext()?.resourceManager?.getStringByNameSync('icon_back');
            } catch (j3) {
                let k3 = j3?.code;
                let l3 = j3?.message;
                hilog.error(0x3900, 'Ace',
                    `Faild to ComposeTitleBarV2 getStringByNameSync icon_back,code: ${k3},message:${l3}`);
            }
        } else if (this.item.value === PUBLIC_MORE) {
            try {
                return getContext()?.resourceManager?.getStringByNameSync('ohos_toolbar_more');
            } catch (g3) {
                let h3 = g3?.code;
                let i3 = g3?.message;
                hilog.error(0x3900, 'Ace',
                    `Faild to ComposeTitleBarV2 getStringByNameSync ohos_toolbar_more,code: ${h3},message:${i3}`);
            }
        } else if (this.item.accessibilityText) {
            return this.item.accessibilityText;
        } else if (this.item.label) {
            return this.item.label;
        }
        return ' ';
    }

    onPlaceChildren(c3, d3, e3) {
        d3.forEach((f3) => {
            f3.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }

    getFgColor() {
        return this.isOnClick
            ? {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_titlebar_icon_pressed'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            } : {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_titlebar_icon'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
    }

    getBgColor() {
        if (this.isOnClick) {
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_click_effect'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else if (this.isOnHover) {
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_hover'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else {
            return Color.Transparent;
        }
    }

    aboutToAppear() {
        try {
            let b3 = this.getUIContext();
            this.isFollowingSystemFontScale = b3.isFollowingSystemFontScale();
            this.maxFontScale = b3.getMaxFontScale();
        } catch (y2) {
            let z2 = y2?.code;
            let a3 = y2?.message;
            hilog.error(0x3900, 'ComposeTitleBarV2',
                `Failed to init fontsizescale info, cause, code: ${z2}, message: ${a3}`);
        }
        this.fontSize = this.decideFontScale();
    }

    decideFontScale() {
        try {
            let x2 = this.getUIContext();
            this.systemFontScale = x2.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        } catch (u2) {
            let v2 = u2?.code;
            let w2 = u2?.message;
            hilog.error(0x3900, 'ComposeTitleBarV2', `Faild to decideFontScale,cause, code: ${v2}, message: ${w2}`);
            return 1;
        }
    }

    itemCardDialogBuilder(p1 = null) {
        this.observeComponentCreation2((q1, r1) => {
            If.create();
            if (this.item.label) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s2, t2) => {
                        Column.create();
                        Column.constraintSize({
                            minHeight: this.fontSize === this.minFontSize ? MAX_DIALOG : MIN_DIALOG
                        });
                    }, Column);
                    this.observeComponentCreation2((i2, j2) => {
                        If.create();
                        if (this.item.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((q2, r2) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.item.symbolStyle);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
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
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((k2, l2) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.item.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((o2, p2) => {
                                                SymbolGlyph.create(this.item.value);
                                                SymbolGlyph.fontSize(IMAGE_SIZE);
                                                SymbolGlyph.fontColor([{
                                                    'id': -1,
                                                    'type': 10001,
                                                    params: ['sys.color.icon_primary'],
                                                    'bundleName': '__harDefaultBundleName__',
                                                    'moduleName': '__harDefaultModuleName__'
                                                }]);
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
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((m2, n2) => {
                                                Image.create(this.item.value);
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
                    this.observeComponentCreation2((g2, h2) => {
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
                    this.observeComponentCreation2((e2, f2) => {
                        Text.create(this.item.label);
                        Text.fontSize(TEXT_EDITABLE_DIALOG);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(this.dialogTextMaxLine);
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
                    this.observeComponentCreation2((c2, d2) => {
                        Column.create();
                        Column.constraintSize({
                            minHeight: this.fontSize === this.minFontSize ? MAX_DIALOG : MIN_DIALOG
                        });
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((s1, t1) => {
                        If.create();
                        if (this.item.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((a2, b2) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.item.symbolStyle);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((u1, v1) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.item.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((y1, z1) => {
                                                SymbolGlyph.create(this.item.value);
                                                SymbolGlyph.fontSize(IMAGE_SIZE);
                                                SymbolGlyph.fontColor([{
                                                    'id': -1,
                                                    'type': 10001,
                                                    params: ['sys.color.icon_primary'],
                                                    'bundleName': '__harDefaultBundleName__',
                                                    'moduleName': '__harDefaultModuleName__'
                                                }]);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((w1, x1) => {
                                                Image.create(this.item.value);
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

    getItemGestureModifier() {
        this.buttonGestureModifier.gestureCallBack = (h1) => {
            if (this.fontSize >= this.minFontSize) {
                h1.addGesture(new LongPressGestureHandler({
                    repeat: false,
                    duration: ButtonGestureModifier.longPressTime
                })
                    .onAction(() => {
                        promptAction.openCustomDialog({
                            builder: () => {
                                this.itemCardDialogBuilder();
                            },
                            onWillAppear: () => {
                                try {
                                    let m1 = this.getUIContext().getHostContext();
                                    let n1 = m1.windowStage.getMainWindowSync();
                                    let o1 = n1.getWindowProperties();
                                    if (px2vp(o1.windowRect.height) > SCREEN_WIDTH_BREAK_POINT) {
                                        this.dialogTextMaxLine = VERTICAL_SCREEN_TEXT_MAX_LINES;
                                    } else {
                                        this.dialogTextMaxLine = HORIZONTAL_SCREEN_TEXT_MAX_LINES;
                                    }
                                } catch (j1) {
                                    let k1 = j1?.code;
                                    let l1 = j1?.message;
                                    hilog.error(0x3900, 'ComposeTitleBarV2',
                                        `Faild to get window height, code: ${k1}, message: ${l1}`);
                                }
                            },
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
                            width: this.fontSize === this.minFontSize ? MAX_DIALOG : MIN_DIALOG
                        }).then((i1) => {
                            this.itemDialogId = i1;
                        });
                    })
                    .onActionEnd(() => {
                        if (this.itemDialogId) {
                            promptAction.closeCustomDialog(this.itemDialogId);
                        }
                    })
                    .onActionCancel(() => {
                        if (this.itemDialogId) {
                            promptAction.closeCustomDialog(this.itemDialogId);
                        }
                    }));
                return;
            }
            h1.clearGestures();
        };
        return this.buttonGestureModifier;
    }

    initialRender() {
        this.observeComponentCreation2((b, c) => {
            If.create();
            if (this.isPopup) {
                this.ifElseBranchUpdateFunction(0, () => {
                    if (!If.canRetake(`ComposeTitleBarV2_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`)) {
                        this.observeComponentCreation2((c1, d1) => {
                            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
                            Button.id(`ComposeTitleBarV2_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`);
                            Button.accessibilityText(this.getAccessibilityReadText());
                            Button.accessibilityLevel(this.item?.accessibilityLevel ?? 'auto');
                            Button.accessibilityDescription(this.item?.accessibilityDescription);
                            Button.enabled(this.item.isEnabled ? this.item.isEnabled : false);
                            Button.width(ImageMenuItemV2.imageHotZoneWidth);
                            Button.height(ImageMenuItemV2.imageHotZoneWidth);
                            Button.borderRadius(ImageMenuItemV2.buttonBorderRadius);
                            Button.foregroundColor(this.getFgColor());
                            Button.backgroundColor(this.getBgColor());
                            ViewStackProcessor.visualState('focused');
                            Button.border({
                                radius: {
                                    'id': -1,
                                    'type': 10002,
                                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                },
                                width: ImageMenuItemV2.focusBorderWidth,
                                color: {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_focused_outline'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                },
                                style: BorderStyle.Solid
                            });
                            ViewStackProcessor.visualState('normal');
                            Button.border({
                                radius: {
                                    'id': -1,
                                    'type': 10002,
                                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                },
                                width: 0
                            });
                            ViewStackProcessor.visualState();
                            Button.onFocus(() => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                this.isOnFocus = true;
                            });
                            Button.onBlur(() => this.isOnFocus = false);
                            Button.onHover((g1) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                this.isOnHover = g1;
                            });
                            Button.onKeyEvent((f1) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (f1.keyCode !== KeyCode.KEYCODE_ENTER &&
                                    f1.keyCode !== KeyCode.KEYCODE_SPACE) {
                                    return;
                                }
                                if (f1.type === KeyType.Down) {
                                    this.isOnClick = true;
                                }
                                if (f1.type === KeyType.Up) {
                                    this.isOnClick = false;
                                }
                            });
                            Button.onTouch((e1) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (e1.type === TouchType.Down) {
                                    this.isOnClick = true;
                                }
                                if (e1.type === TouchType.Up || e1.type === TouchType.Cancel) {
                                    this.isOnClick = false;
                                    if (this.fontSize >= this.minFontSize && this.itemDialogId) {
                                        promptAction.closeCustomDialog(this.itemDialogId);
                                    }
                                }
                            });
                            Button.onClick(() => {
                                if (this.item) {
                                    return this.item.isEnabled && this.item.action?.();
                                }
                            });
                            Button.gestureModifier(this.getItemGestureModifier());
                        }, Button);
                        this.observeComponentCreation2((s, t) => {
                            If.create();
                            if (this.item?.symbolStyle) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((a1, b1) => {
                                        SymbolGlyph.create();
                                        SymbolGlyph.fontColor([{
                                            'id': -1,
                                            'type': 10001,
                                            params: ['sys.color.ohos_id_color_text_primary'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        }]);
                                        SymbolGlyph.attributeModifier.bind(this)(this.item?.symbolStyle);
                                        SymbolGlyph.fontSize(`${ImageMenuItemV2.imageSize}vp`);
                                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                        SymbolGlyph.draggable(false);
                                        SymbolGlyph.focusable(this.item?.isEnabled);
                                        SymbolGlyph.key(ImageMenuItemV2.focusablePrefix + this.index);
                                    }, SymbolGlyph);
                                });
                            } else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.observeComponentCreation2((u, v) => {
                                        If.create();
                                        if (Util.isSymbolResource(this.item.value)) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((y, z) => {
                                                    SymbolGlyph.create(this.item.value);
                                                    SymbolGlyph.fontSize(`${ImageMenuItemV2.imageSize}vp`);
                                                    SymbolGlyph.fontColor([{
                                                        'id': -1,
                                                        'type': 10001,
                                                        params: ['sys.color.ohos_id_color_text_primary'],
                                                        'bundleName': '__harDefaultBundleName__',
                                                        'moduleName': '__harDefaultModuleName__'
                                                    }]);
                                                    SymbolGlyph.draggable(false);
                                                    SymbolGlyph.focusable(this.item?.isEnabled);
                                                    SymbolGlyph.key(ImageMenuItemV2.focusablePrefix + this.index);
                                                }, SymbolGlyph);
                                            });
                                        } else {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((w, x) => {
                                                    Image.create(this.item?.value);
                                                    Image.matchTextDirection(this.item?.value === PUBLIC_BACK ? true :
                                                        false);
                                                    Image.width(ImageMenuItemV2.imageSize);
                                                    Image.draggable(false);
                                                    Image.height(ImageMenuItemV2.imageSize);
                                                    Image.focusable(this.item?.isEnabled);
                                                    Image.key(ImageMenuItemV2.focusablePrefix + this.index);
                                                    Image.fillColor({
                                                        'id': -1,
                                                        'type': 10001,
                                                        params: ['sys.color.ohos_id_color_text_primary'],
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
                        Button.pop();
                    }
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    if (!If.canRetake(`ComposeTitleBarV2_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`)) {
                        this.observeComponentCreation2((n, o) => {
                            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
                            Button.id(`ComposeTitleBarV2_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`);
                            Button.accessibilityText(this.getAccessibilityReadText());
                            Button.accessibilityLevel(this.item?.accessibilityLevel ?? 'auto');
                            Button.accessibilityDescription(this.item?.accessibilityDescription);
                            Button.enabled(this.item.isEnabled ? this.item.isEnabled : false);
                            Button.width(ImageMenuItemV2.imageHotZoneWidth);
                            Button.height(ImageMenuItemV2.imageHotZoneWidth);
                            Button.borderRadius(ImageMenuItemV2.buttonBorderRadius);
                            Button.foregroundColor(this.getFgColor());
                            Button.backgroundColor(this.getBgColor());
                            ViewStackProcessor.visualState('focused');
                            Button.border({
                                radius: {
                                    'id': -1,
                                    'type': 10002,
                                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                },
                                width: ImageMenuItemV2.focusBorderWidth,
                                color: {
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_focused_outline'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                },
                                style: BorderStyle.Solid
                            });
                            ViewStackProcessor.visualState('normal');
                            Button.border({
                                radius: {
                                    'id': -1,
                                    'type': 10002,
                                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                },
                                width: 0
                            });
                            ViewStackProcessor.visualState();
                            Button.onFocus(() => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                this.isOnFocus = true;
                            });
                            Button.onBlur(() => this.isOnFocus = false);
                            Button.onHover((r) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                this.isOnHover = r;
                            });
                            Button.onKeyEvent((q) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (q.keyCode !== KeyCode.KEYCODE_ENTER &&
                                    q.keyCode !== KeyCode.KEYCODE_SPACE) {
                                    return;
                                }
                                if (q.type === KeyType.Down) {
                                    this.isOnClick = true;
                                }
                                if (q.type === KeyType.Up) {
                                    this.isOnClick = false;
                                }
                            });
                            Button.onTouch((p) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (p.type === TouchType.Down) {
                                    this.isOnClick = true;
                                }
                                if (p.type === TouchType.Up || p.type === TouchType.Cancel) {
                                    this.isOnClick = false;
                                    if (this.fontSize >= this.minFontSize && this.itemDialogId) {
                                        promptAction.closeCustomDialog(this.itemDialogId);
                                    }
                                }
                            });
                            Button.onClick(() => {
                                if (this.item) {
                                    return this.item.isEnabled && this.item.action?.();
                                }
                            });
                        }, Button);
                        this.observeComponentCreation2((d, e) => {
                            If.create();
                            if (this.item?.symbolStyle) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((l, m) => {
                                        SymbolGlyph.create();
                                        SymbolGlyph.fontColor([{
                                            'id': -1,
                                            'type': 10001,
                                            params: ['sys.color.ohos_id_color_text_primary'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        }]);
                                        SymbolGlyph.attributeModifier.bind(this)(this.item?.symbolStyle);
                                        SymbolGlyph.fontSize(`${ImageMenuItemV2.imageSize}vp`);
                                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                        SymbolGlyph.draggable(false);
                                        SymbolGlyph.focusable(this.item?.isEnabled);
                                        SymbolGlyph.key(ImageMenuItemV2.focusablePrefix + this.index);
                                    }, SymbolGlyph);
                                });
                            } else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.observeComponentCreation2((f, g) => {
                                        If.create();
                                        if (Util.isSymbolResource(this.item.value)) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((j, k) => {
                                                    SymbolGlyph.create(this.item.value);
                                                    SymbolGlyph.fontSize(`${ImageMenuItemV2.imageSize}vp`);
                                                    SymbolGlyph.fontColor([{
                                                        'id': -1,
                                                        'type': 10001,
                                                        params: ['sys.color.ohos_id_color_text_primary'],
                                                        'bundleName': '__harDefaultBundleName__',
                                                        'moduleName': '__harDefaultModuleName__'
                                                    }]);
                                                    SymbolGlyph.draggable(false);
                                                    SymbolGlyph.focusable(this.item?.isEnabled);
                                                    SymbolGlyph.key(ImageMenuItemV2.focusablePrefix + this.index);
                                                }, SymbolGlyph);
                                            });
                                        } else {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((h, i) => {
                                                    Image.create(this.item?.value);
                                                    Image.matchTextDirection(this.item?.value === PUBLIC_BACK ? true :
                                                        false);
                                                    Image.width(ImageMenuItemV2.imageSize);
                                                    Image.draggable(false);
                                                    Image.height(ImageMenuItemV2.imageSize);
                                                    Image.focusable(this.item?.isEnabled);
                                                    Image.key(ImageMenuItemV2.focusablePrefix + this.index);
                                                    Image.fillColor({
                                                        'id': -1,
                                                        'type': 10001,
                                                        params: ['sys.color.ohos_id_color_text_primary'],
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
                        Button.pop();
                    }
                });
            }
        }, If);
        If.pop();
    }

    updateStateVars(a) {
        if (a === undefined) {
            return;
        }
        if ('item' in a) {
            this.updateParam('item', a.item);
        }
        if ('index' in a) {
            this.updateParam('index', a.index);
        }
        if ('itemIndex' in a) {
            this.updateParam('itemIndex', a.itemIndex);
        }
        if ('isPopup' in a) {
            this.updateParam('isPopup', a.isPopup);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

ImageMenuItemV2.imageSize = 24;
ImageMenuItemV2.imageHotZoneWidth = 48;
ImageMenuItemV2.buttonBorderRadius = 8;
ImageMenuItemV2.focusBorderWidth = 2;
ImageMenuItemV2.focusablePrefix = 'Id-ComposeTitleBarV2-ImageMenuItem-';
__decorate([
    Param
], ImageMenuItemV2.prototype, 'item', void 0);
__decorate([
    Param
], ImageMenuItemV2.prototype, 'index', void 0);
__decorate([
    Param
], ImageMenuItemV2.prototype, 'itemIndex', void 0);
__decorate([
    Param
], ImageMenuItemV2.prototype, 'isPopup', void 0);
__decorate([
    Local
], ImageMenuItemV2.prototype, 'isOnFocus', void 0);
__decorate([
    Local
], ImageMenuItemV2.prototype, 'isOnHover', void 0);
__decorate([
    Local
], ImageMenuItemV2.prototype, 'isOnClick', void 0);
__decorate([
    Local
], ImageMenuItemV2.prototype, 'fontSize', void 0);
__decorate([
    Local
], ImageMenuItemV2.prototype, 'itemDialogId', void 0);
__decorate([
    Local
], ImageMenuItemV2.prototype, 'dialogTextMaxLine', void 0);
__decorate([
    Consumer('uniqueIdV2')
], ImageMenuItemV2.prototype, 'parentParentUniqueId', void 0);

export default {
    ComposeTitleBarV2MenuItem, ComposeTitleBarV2
};