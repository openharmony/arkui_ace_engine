/*
 * Copyright (c) 2026-2026 Huawei Device Co., Ltd.
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
var __decorate = (this && this.__decorate) || function (g65, h65, i65, j65) {
    var k65 = arguments.length,
        l65 = k65 < 3 ? h65 : j65 === null ? j65 = Object.getOwnPropertyDescriptor(h65, i65) : j65, m65;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        l65 = Reflect.decorate(g65, h65, i65, j65);
    } else {
        for (var n65 = g65.length - 1; n65 >= 0; n65--) {
            if (m65 = g65[n65]) {
                l65 = (k65 < 3 ? m65(l65) : k65 > 3 ? m65(h65, i65, l65) : m65(h65, i65)) || l65;
            }
        }
    }
    return k65 > 3 && l65 && Object.defineProperty(h65, i65, l65), l65;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const hilog = requireNapi('hilog');
const promptAction = requireNapi('promptAction');

let ComposeTitleBarV2MenuItem = class ComposeTitleBarV2MenuItem {
    constructor(f65) {
        this.isEnabled = true;
        this.accessibilityLevel = 'auto';
        this.value = f65.value;
        this.symbolStyle = f65.symbolStyle;
        this.isEnabled = f65.isEnabled ?? true;
        this.action = f65.action;
        this.label = f65.label;
        this.accessibilityText = f65.accessibilityText;
        this.accessibilityLevel = f65.accessibilityLevel ?? 'auto';
        this.accessibilityDescription = f65.accessibilityDescription;
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
    static isSymbolResource(d65) {
        if (!Util.isResourceType(d65)) {
            return false;
        }
        let e65 = d65;
        return e65.type === RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(c65) {
        if (!c65) {
            return false;
        }
        if (typeof c65 === 'string' || typeof c65 === 'undefined') {
            return false;
        }
        return true;
    }
}

class ButtonGestureModifier {
    constructor() {
        this.gestureCallBack = undefined;
    }

    applyGesture(b65) {
        this.gestureCallBack?.(b65);
    }
}

ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;

class ComposeTitleBarV2 extends ViewV2 {
    constructor(v64, w64, x64, y64 = -1, z64, a65) {
        super(v64, y64, a65);
        this.initParam('item', (w64 && 'item' in w64) ? w64.item : undefined);
        this.initParam('title', (w64 && 'title' in w64) ? w64.title : '');
        this.initParam('subtitle', (w64 && 'subtitle' in w64) ? w64.subtitle : '');
        this.initParam('menuItems', (w64 && 'menuItems' in w64) ? w64.menuItems : []);
        this.titleMaxWidth = 0;
        this.fontSize = 1;
        this.uniqueId = -1;
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(u64) {
        this.resetParam('item', (u64 && 'item' in u64) ? u64.item : undefined);
        this.resetParam('title', (u64 && 'title' in u64) ? u64.title : '');
        this.resetParam('subtitle', (u64 && 'subtitle' in u64) ? u64.subtitle : '');
        this.resetParam('menuItems', (u64 && 'menuItems' in u64) ? u64.menuItems : []);
        this.titleMaxWidth = 0;
        this.fontSize = 1;
        this.uniqueId = -1;
    }

    initialRender() {
        this.observeComponentCreation2((j64, k64) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.onAppear(() => {
                try {
                    let s64 = this.getUIContext().getFrameNodeByUniqueId(this.getUniqueId());
                    if (s64) {
                        let t64 = s64.getFirstChild();
                        if (t64) {
                            this.uniqueId = t64.getUniqueId() ?? -1;
                        }
                    }
                } catch (p64) {
                    let q64 = p64?.code;
                    let r64 = p64?.message;
                    hilog.error(0x3900, 'ComposeTitleBarV2',
                        `Faild to getFrameNodeByUniqueId,cause, code: ${q64}, message: ${r64}`);
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
            Flex.onAreaChange((l64, m64) => {
                let n64 = Number(m64.width);
                if (this.menuItems !== undefined) {
                    let o64 = this.menuItems.length;
                    if (o64 >= CollapsibleMenuSectionV2.maxCountOfVisibleItems) {
                        n64 = n64 - ImageMenuItemV2.imageHotZoneWidth * CollapsibleMenuSectionV2.maxCountOfVisibleItems;
                    } else if (o64 > 0) {
                        n64 = n64 - ImageMenuItemV2.imageHotZoneWidth * o64;
                    }
                }
                this.titleMaxWidth = n64;
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
        this.observeComponentCreation2((h64, i64) => {
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
            this.observeComponentCreation2((d64, e64) => {
                if (e64) {
                    let f64 = new ImageMenuItemV2(this, {
                        item: new ComposeTitleBarV2MenuItem({
                            value: PUBLIC_BACK,
                            isEnabled: true,
                            action: () => this.getUIContext()?.getRouter()?.back()
                        }),
                        index: -1,
                        itemIndex: -1
                    }, undefined, d64, () => {
                    }, {
                        page: 'library/src/main/ets/components/0508/composetitlebarv2/source/composetitlebarv2.ets',
                        line: 136,
                        col: 9
                    });
                    ViewV2.create(f64);
                    let g64 = () => {
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
                    f64.paramsGenerator_ = g64;
                } else {
                    this.updateStateVarsOfChildByElmtId(d64, {
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
        this.observeComponentCreation2((b64, c64) => {
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
        this.observeComponentCreation2((x63, y63) => {
            If.create();
            if (this.item !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z63, a64) => {
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
        this.observeComponentCreation2((v63, w63) => {
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.titleMaxWidth });
        }, Column);
        this.observeComponentCreation2((p63, q63) => {
            If.create();
            if (this.title !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t63, u63) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((r63, s63) => {
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
        this.observeComponentCreation2((j63, k63) => {
            If.create();
            if (this.subtitle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n63, o63) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((l63, m63) => {
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
        this.observeComponentCreation2((d63, e63) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((f63, g63) => {
                            if (g63) {
                                let h63 = new CollapsibleMenuSectionV2(this, {
                                    menuItems: this.menuItems,
                                    index: 1 + ComposeTitleBarV2.instanceCount++
                                }, undefined, f63, () => {
                                }, {
                                    page: 'library/src/main/ets/components/0508/composetitlebarv2/source/composetitlebarv2.ets',
                                    line: 194,
                                    col: 9
                                });
                                ViewV2.create(h63);
                                let i63 = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + ComposeTitleBarV2.instanceCount++
                                    };
                                };
                                h63.paramsGenerator_ = i63;
                            } else {
                                this.updateStateVarsOfChildByElmtId(f63, {
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

    updateStateVars(c63) {
        if (c63 === undefined) {
            return;
        }
        if ('item' in c63) {
            this.updateParam('item', c63.item);
        }
        if ('title' in c63) {
            this.updateParam('title', c63.title);
        }
        if ('subtitle' in c63) {
            this.updateParam('subtitle', c63.subtitle);
        }
        if ('menuItems' in c63) {
            this.updateParam('menuItems', c63.menuItems);
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
    constructor(w62, x62, y62, z62 = -1, a63, b63) {
        super(w62, z62, b63);
        this.initParam('menuItems', (x62 && 'menuItems' in x62) ? x62.menuItems : []);
        this.initParam('item', (x62 && 'item' in x62) ? x62.item : new ComposeTitleBarV2MenuItem({
            value: PUBLIC_MORE,
            label: {
                'id': -1,
                'type': 10003,
                params: ['sys.string.ohos_toolbar_more'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        }));
        this.initParam('index', (x62 && 'index' in x62) ? x62.index : 0);
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

    resetStateVarsOnReuse(v62) {
        this.resetParam('menuItems', (v62 && 'menuItems' in v62) ? v62.menuItems : []);
        this.resetParam('item', (v62 && 'item' in v62) ? v62.item : new ComposeTitleBarV2MenuItem({
            value: PUBLIC_MORE,
            label: {
                'id': -1,
                'type': 10003,
                params: ['sys.string.ohos_toolbar_more'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        }));
        this.resetParam('index', (v62 && 'index' in v62) ? v62.index : 0);
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
            let u62 = this.getUIContext();
            this.isFollowingSystemFontScale = u62.isFollowingSystemFontScale();
            this.maxFontScale = u62.getMaxFontScale();
        } catch (r62) {
            let s62 = r62?.code;
            let t62 = r62?.message;
            hilog.error(0x3900, 'ComposeTitleBarV2',
                `Failed to init fontsizescale info, cause, code: ${s62}, message: ${t62}`);
        }
        if (this.menuItems) {
            this.menuItems.forEach((p62, q62) => {
                if (p62.isEnabled && this.firstFocusableIndex === -1 &&
                    q62 > CollapsibleMenuSectionV2.maxCountOfVisibleItems - 2) {
                    this.firstFocusableIndex = this.index * 1000 + q62 + 1;
                }
            });
        }
        this.fontSize = this.decideFontScale();
    }

    decideFontScale() {
        try {
            let o62 = this.getUIContext();
            this.systemFontScale = o62.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        } catch (l62) {
            let m62 = l62?.code;
            let n62 = l62?.message;
            hilog.error(0x3900, 'ComposeTitleBarV2', `Faild to decideFontScale,cause, code: ${m62}, message: ${n62}`);
            return 1;
        }
    }

    itemCardDialogBuilder(f61, g61 = null) {
        this.observeComponentCreation2((h61, i61) => {
            If.create();
            if (f61.label) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j62, k62) => {
                        Column.create();
                        Column.constraintSize({
                            minHeight: this.fontSize === ButtonGestureModifier.minFontSize ? MAX_DIALOG : MIN_DIALOG
                        });
                    }, Column);
                    this.observeComponentCreation2((z61, a62) => {
                        If.create();
                        if (f61.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((h62, i62) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                    SymbolGlyph.attributeModifier.bind(this)(f61.symbolStyle);
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
                                this.observeComponentCreation2((b62, c62) => {
                                    If.create();
                                    if (Util.isSymbolResource(f61.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((f62, g62) => {
                                                SymbolGlyph.create(f61.value);
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
                                            this.observeComponentCreation2((d62, e62) => {
                                                Image.create(f61.value);
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
                    this.observeComponentCreation2((x61, y61) => {
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
                    this.observeComponentCreation2((v61, w61) => {
                        Text.create(f61.label);
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
                    this.observeComponentCreation2((t61, u61) => {
                        Column.create();
                        Column.constraintSize({
                            minHeight: this.fontSize === ButtonGestureModifier.minFontSize ? MAX_DIALOG : MIN_DIALOG
                        });
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((j61, k61) => {
                        If.create();
                        if (f61.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((r61, s61) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                    SymbolGlyph.attributeModifier.bind(this)(f61.symbolStyle);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((l61, m61) => {
                                    If.create();
                                    if (Util.isSymbolResource(f61.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((p61, q61) => {
                                                SymbolGlyph.create(f61.value);
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
                                            this.observeComponentCreation2((n61, o61) => {
                                                Image.create(f61.value);
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
        this.observeComponentCreation2((d61, e61) => {
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
        this.observeComponentCreation2((b61, c61) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((w59, x59) => {
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y59, z59) => {
                        If.create();
                        if (this.menuItems.length <= CollapsibleMenuSectionV2.maxCountOfVisibleItems) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((r60, s60) => {
                                    ForEach.create();
                                    const t60 = (u60, v60) => {
                                        const w60 = u60;
                                        {
                                            this.observeComponentCreation2((x60, y60) => {
                                                if (y60) {
                                                    let z60 = new ImageMenuItemV2(this, {
                                                        item: w60,
                                                        index: this.index * 1000 + v60 + 1,
                                                        itemIndex: v60
                                                    }, undefined, x60, () => {
                                                    }, {
                                                        page: 'library/src/main/ets/components/0508/composetitlebarv2/source/composetitlebarv2.ets',
                                                        line: 417,
                                                        col: 15
                                                    });
                                                    ViewV2.create(z60);
                                                    let a61 = () => {
                                                        return {
                                                            item: w60,
                                                            index: this.index * 1000 + v60 + 1,
                                                            itemIndex: v60
                                                        };
                                                    };
                                                    z60.paramsGenerator_ = a61;
                                                } else {
                                                    this.updateStateVarsOfChildByElmtId(x60, {
                                                        item: w60, index: this.index * 1000 + v60 + 1, itemIndex: v60
                                                    });
                                                }
                                            }, { name: 'ImageMenuItemV2' });
                                        }
                                    };
                                    this.forEachUpdateFunction(r60, this.menuItems, t60, undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((h60, i60) => {
                                    ForEach.create();
                                    const j60 = (k60, l60) => {
                                        const m60 = k60;
                                        {
                                            this.observeComponentCreation2((n60, o60) => {
                                                if (o60) {
                                                    let p60 = new ImageMenuItemV2(this, {
                                                        item: m60,
                                                        index: this.index * 1000 + l60 + 1,
                                                        itemIndex: l60
                                                    }, undefined, n60, () => {
                                                    }, {
                                                        page: 'library/src/main/ets/components/0508/composetitlebarv2/source/composetitlebarv2.ets',
                                                        line: 422,
                                                        col: 17
                                                    });
                                                    ViewV2.create(p60);
                                                    let q60 = () => {
                                                        return {
                                                            item: m60,
                                                            index: this.index * 1000 + l60 + 1,
                                                            itemIndex: l60
                                                        };
                                                    };
                                                    p60.paramsGenerator_ = q60;
                                                } else {
                                                    this.updateStateVarsOfChildByElmtId(n60, {
                                                        item: m60, index: this.index * 1000 + l60 + 1, itemIndex: l60
                                                    });
                                                }
                                            }, { name: 'ImageMenuItemV2' });
                                        }
                                    };
                                    this.forEachUpdateFunction(h60,
                                        this.menuItems.slice(0, CollapsibleMenuSectionV2.maxCountOfVisibleItems - 1),
                                        j60, undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                                this.observeComponentCreation2((c60, d60) => {
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
                                    Button.onHover((g60) => this.isMoreIconOnHover = g60);
                                    Button.onKeyEvent((f60) => {
                                        if (f60.keyCode !== KeyCode.KEYCODE_ENTER &&
                                            f60.keyCode !== KeyCode.KEYCODE_SPACE) {
                                            return;
                                        }
                                        if (f60.type === KeyType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (f60.type === KeyType.Up) {
                                            this.isMoreIconOnClick = false;
                                        }
                                    });
                                    Button.onTouch((e60) => {
                                        if (e60.type === TouchType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (e60.type === TouchType.Up || e60.type === TouchType.Cancel) {
                                            this.isMoreIconOnClick = false;
                                            if (this.fontSize >= this.minFontSize && this.itemDialogId) {
                                                promptAction.closeCustomDialog(this.itemDialogId);
                                            }
                                        }
                                    });
                                    Button.onClick(() => this.isPopupShown = true);
                                    Button.gestureModifier(this.getItemGestureModifier());
                                }, Button);
                                this.observeComponentCreation2((a60, b60) => {
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
        this.buttonGestureModifier.gestureCallBack = (o59) => {
            if (this.fontSize >= ButtonGestureModifier.minFontSize) {
                o59.addGesture(new LongPressGestureHandler({
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
                                    let t59 = this.getUIContext().getHostContext();
                                    let u59 = t59.windowStage.getMainWindowSync();
                                    let v59 = u59.getWindowProperties();
                                    if (px2vp(v59.windowRect.height) > SCREEN_WIDTH_BREAK_POINT) {
                                        this.dialogTextMaxLine = VERTICAL_SCREEN_TEXT_MAX_LINES;
                                    } else {
                                        this.dialogTextMaxLine = HORIZONTAL_SCREEN_TEXT_MAX_LINES;
                                    }
                                } catch (q59) {
                                    let r59 = q59?.code;
                                    let s59 = q59?.message;
                                    hilog.error(0x3900, 'ComposeTitleBarV2',
                                        `Faild to get window height, code: ${r59}, message: ${s59}`);
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
                        }).then((p59) => {
                            this.itemDialogId = p59;
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
            o59.clearGestures();
        };
        return this.buttonGestureModifier;
    }

    onPlaceChildren(k59, l59, m59) {
        l59.forEach((n59) => {
            n59.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }

    popupBuilder(v58 = null) {
        this.observeComponentCreation2((i59, j59) => {
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
        this.observeComponentCreation2((w58, x58) => {
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y58, z58) => {
                        ForEach.create();
                        const a59 = (b59, c59) => {
                            const d59 = b59;
                            {
                                this.observeComponentCreation2((e59, f59) => {
                                    if (f59) {
                                        let g59 = new ImageMenuItemV2(this, {
                                            item: d59, index: this.index * 1000 +
                                                CollapsibleMenuSectionV2.maxCountOfVisibleItems + c59,
                                            isPopup: false
                                        }, undefined, e59, () => {
                                        }, {
                                            page: 'library/src/main/ets/components/0508/composetitlebarv2/source/composetitlebarv2.ets',
                                            line: 561,
                                            col: 13
                                        });
                                        ViewV2.create(g59);
                                        let h59 = () => {
                                            return {
                                                item: d59,
                                                index: this.index * 1000 +
                                                    CollapsibleMenuSectionV2.maxCountOfVisibleItems + c59,
                                                isPopup: false
                                            };
                                        };
                                        g59.paramsGenerator_ = h59;
                                    } else {
                                        this.updateStateVarsOfChildByElmtId(e59, {
                                            item: d59, index: this.index * 1000 +
                                                CollapsibleMenuSectionV2.maxCountOfVisibleItems + c59,
                                            isPopup: false
                                        });
                                    }
                                }, { name: 'ImageMenuItemV2' });
                            }
                        };
                        this.forEachUpdateFunction(y58,
                            this.menuItems.slice(CollapsibleMenuSectionV2.maxCountOfVisibleItems - 1,
                                this.menuItems.length), a59, undefined, true, false);
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

    updateStateVars(u58) {
        if (u58 === undefined) {
            return;
        }
        if ('menuItems' in u58) {
            this.updateParam('menuItems', u58.menuItems);
        }
        if ('item' in u58) {
            this.updateParam('item', u58.item);
        }
        if ('index' in u58) {
            this.updateParam('index', u58.index);
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
    constructor(o58, p58, q58, r58 = -1, s58, t58) {
        super(o58, r58, t58);
        this.initParam('item', (p58 && 'item' in p58) ? p58.item : new ComposeTitleBarV2MenuItem({ value: '' }));
        this.initParam('index', (p58 && 'index' in p58) ? p58.index : 0);
        this.initParam('itemIndex', (p58 && 'itemIndex' in p58) ? p58.itemIndex : 0);
        this.initParam('isPopup', (p58 && 'isPopup' in p58) ? p58.isPopup : true);
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

    resetStateVarsOnReuse(n58) {
        this.resetParam('item', (n58 && 'item' in n58) ? n58.item : new ComposeTitleBarV2MenuItem({ value: '' }));
        this.resetParam('index', (n58 && 'index' in n58) ? n58.index : 0);
        this.resetParam('itemIndex', (n58 && 'itemIndex' in n58) ? n58.itemIndex : 0);
        this.resetParam('isPopup', (n58 && 'isPopup' in n58) ? n58.isPopup : true);
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

    toStringFormat(i58) {
        if (typeof i58 === 'string') {
            return i58;
        } else if (typeof i58 === 'undefined') {
            return '';
        } else {
            let j58 = '';
            try {
                if (i58.id === -1) {
                    j58 = getContext()?.resourceManager?.getStringByNameSync(i58.params?.[0].split('.').pop());
                } else {
                    j58 = getContext()?.resourceManager?.getStringSync(i58);
                }
            } catch (k58) {
                let l58 = k58?.code;
                let m58 = k58?.message;
                hilog.error(0x3900, 'Ace', `Faild to ComposeTitleBarV2 toStringFormat,code: ${l58},message:${m58}`);
            }
            return j58;
        }
    }

    getAccessibilityReadText() {
        if (this.item.value === PUBLIC_BACK) {
            try {
                return getContext()?.resourceManager?.getStringByNameSync('icon_back');
            } catch (f58) {
                let g58 = f58?.code;
                let h58 = f58?.message;
                hilog.error(0x3900, 'Ace',
                    `Faild to ComposeTitleBarV2 getStringByNameSync icon_back,code: ${g58},message:${h58}`);
            }
        } else if (this.item.value === PUBLIC_MORE) {
            try {
                return getContext()?.resourceManager?.getStringByNameSync('ohos_toolbar_more');
            } catch (c58) {
                let d58 = c58?.code;
                let e58 = c58?.message;
                hilog.error(0x3900, 'Ace',
                    `Faild to ComposeTitleBarV2 getStringByNameSync ohos_toolbar_more,code: ${d58},message:${e58}`);
            }
        } else if (this.item.accessibilityText) {
            return this.item.accessibilityText;
        } else if (this.item.label) {
            return this.item.label;
        }
        return ' ';
    }

    onPlaceChildren(y57, z57, a58) {
        z57.forEach((b58) => {
            b58.layout({ x: 0, y: 0 });
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
            let x57 = this.getUIContext();
            this.isFollowingSystemFontScale = x57.isFollowingSystemFontScale();
            this.maxFontScale = x57.getMaxFontScale();
        } catch (u57) {
            let v57 = u57?.code;
            let w57 = u57?.message;
            hilog.error(0x3900, 'ComposeTitleBarV2',
                `Failed to init fontsizescale info, cause, code: ${v57}, message: ${w57}`);
        }
        this.fontSize = this.decideFontScale();
    }

    decideFontScale() {
        try {
            let t57 = this.getUIContext();
            this.systemFontScale = t57.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        } catch (q57) {
            let r57 = q57?.code;
            let s57 = q57?.message;
            hilog.error(0x3900, 'ComposeTitleBarV2', `Faild to decideFontScale,cause, code: ${r57}, message: ${s57}`);
            return 1;
        }
    }

    itemCardDialogBuilder(l56 = null) {
        this.observeComponentCreation2((m56, n56) => {
            If.create();
            if (this.item.label) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o57, p57) => {
                        Column.create();
                        Column.constraintSize({
                            minHeight: this.fontSize === this.minFontSize ? MAX_DIALOG : MIN_DIALOG
                        });
                    }, Column);
                    this.observeComponentCreation2((e57, f57) => {
                        If.create();
                        if (this.item.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((m57, n57) => {
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
                                this.observeComponentCreation2((g57, h57) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.item.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((k57, l57) => {
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
                                            this.observeComponentCreation2((i57, j57) => {
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
                    this.observeComponentCreation2((c57, d57) => {
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
                    this.observeComponentCreation2((a57, b57) => {
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
                    this.observeComponentCreation2((y56, z56) => {
                        Column.create();
                        Column.constraintSize({
                            minHeight: this.fontSize === this.minFontSize ? MAX_DIALOG : MIN_DIALOG
                        });
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((o56, p56) => {
                        If.create();
                        if (this.item.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((w56, x56) => {
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
                                this.observeComponentCreation2((q56, r56) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.item.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((u56, v56) => {
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
                                            this.observeComponentCreation2((s56, t56) => {
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
        this.buttonGestureModifier.gestureCallBack = (d56) => {
            if (this.fontSize >= this.minFontSize) {
                d56.addGesture(new LongPressGestureHandler({
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
                                    let i56 = this.getUIContext().getHostContext();
                                    let j56 = i56.windowStage.getMainWindowSync();
                                    let k56 = j56.getWindowProperties();
                                    if (px2vp(k56.windowRect.height) > SCREEN_WIDTH_BREAK_POINT) {
                                        this.dialogTextMaxLine = VERTICAL_SCREEN_TEXT_MAX_LINES;
                                    } else {
                                        this.dialogTextMaxLine = HORIZONTAL_SCREEN_TEXT_MAX_LINES;
                                    }
                                } catch (f56) {
                                    let g56 = f56?.code;
                                    let h56 = f56?.message;
                                    hilog.error(0x3900, 'ComposeTitleBarV2',
                                        `Faild to get window height, code: ${g56}, message: ${h56}`);
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
                        }).then((e56) => {
                            this.itemDialogId = e56;
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
            d56.clearGestures();
        };
        return this.buttonGestureModifier;
    }

    initialRender() {
        this.observeComponentCreation2((x54, y54) => {
            If.create();
            if (this.isPopup) {
                this.ifElseBranchUpdateFunction(0, () => {
                    if (!If.canRetake(`ComposeTitleBarV2_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`)) {
                        this.observeComponentCreation2((y55, z55) => {
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
                            Button.onHover((c56) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                this.isOnHover = c56;
                            });
                            Button.onKeyEvent((b56) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (b56.keyCode !== KeyCode.KEYCODE_ENTER &&
                                    b56.keyCode !== KeyCode.KEYCODE_SPACE) {
                                    return;
                                }
                                if (b56.type === KeyType.Down) {
                                    this.isOnClick = true;
                                }
                                if (b56.type === KeyType.Up) {
                                    this.isOnClick = false;
                                }
                            });
                            Button.onTouch((a56) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (a56.type === TouchType.Down) {
                                    this.isOnClick = true;
                                }
                                if (a56.type === TouchType.Up || a56.type === TouchType.Cancel) {
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
                        this.observeComponentCreation2((o55, p55) => {
                            If.create();
                            if (this.item?.symbolStyle) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((w55, x55) => {
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
                                    this.observeComponentCreation2((q55, r55) => {
                                        If.create();
                                        if (Util.isSymbolResource(this.item.value)) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((u55, v55) => {
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
                                                this.observeComponentCreation2((s55, t55) => {
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
                        this.observeComponentCreation2((j55, k55) => {
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
                            Button.onHover((n55) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                this.isOnHover = n55;
                            });
                            Button.onKeyEvent((m55) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (m55.keyCode !== KeyCode.KEYCODE_ENTER &&
                                    m55.keyCode !== KeyCode.KEYCODE_SPACE) {
                                    return;
                                }
                                if (m55.type === KeyType.Down) {
                                    this.isOnClick = true;
                                }
                                if (m55.type === KeyType.Up) {
                                    this.isOnClick = false;
                                }
                            });
                            Button.onTouch((l55) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (l55.type === TouchType.Down) {
                                    this.isOnClick = true;
                                }
                                if (l55.type === TouchType.Up || l55.type === TouchType.Cancel) {
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
                        this.observeComponentCreation2((z54, a55) => {
                            If.create();
                            if (this.item?.symbolStyle) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((h55, i55) => {
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
                                    this.observeComponentCreation2((b55, c55) => {
                                        If.create();
                                        if (Util.isSymbolResource(this.item.value)) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((f55, g55) => {
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
                                                this.observeComponentCreation2((d55, e55) => {
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

    updateStateVars(w54) {
        if (w54 === undefined) {
            return;
        }
        if ('item' in w54) {
            this.updateParam('item', w54.item);
        }
        if ('index' in w54) {
            this.updateParam('index', w54.index);
        }
        if ('itemIndex' in w54) {
            this.updateParam('itemIndex', w54.itemIndex);
        }
        if ('isPopup' in w54) {
            this.updateParam('isPopup', w54.isPopup);
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

export { ComposeTitleBarV2 };
