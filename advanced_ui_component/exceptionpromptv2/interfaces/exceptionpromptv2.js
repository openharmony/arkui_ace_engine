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

var __decorate = (this && this.__decorate) || function (h88, i88, j88, k88) {
    var l88 = arguments.length,
        m88 = l88 < 3 ? i88 : k88 === null ? k88 = Object.getOwnPropertyDescriptor(i88, j88) : k88, n88;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        m88 = Reflect.decorate(h88, i88, j88, k88);
    } else {
        for (var o88 = h88.length - 1; o88 >= 0; o88--) {
            if (n88 = h88[o88]) {
                m88 = (l88 < 3 ? n88(m88) : l88 > 3 ? n88(i88, j88, m88) : n88(i88, j88)) || m88;
            }
        }
    }
    return l88 > 3 && m88 && Object.defineProperty(i88, j88, m88), m88;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
const curves = requireNativeModule('ohos.curves');
const hilog = requireNapi('hilog');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const i18n = requireNapi('i18n');

const START_TIME = 250;
const END_TIME = 200;
const BORDER_RADIUS = 12;
const ZINDEX_NUM = 9;
const SYMBOL_SIZE = 24;
const MAX_SYMBOL_FONT_SCALE = 2;
const MIN_SYMBOL_FONT_SCALE = 1;
const DEFAULT_SYMBOL_FONT_SCALE = 1;

export var MarginTypeV2;
(function (g88) {
    g88[g88['DEFAULT_MARGIN'] = 0] = 'DEFAULT_MARGIN';
    g88[g88['FIT_MARGIN'] = 1] = 'FIT_MARGIN';
})(MarginTypeV2 || (MarginTypeV2 = {}));

export class ExceptionPromptV2 extends ViewV2 {
    constructor(z87, a88, b88, c88 = -1, d88, e88) {
        super(z87, c88, e88);
        this.initParam('options', (a88 && 'options' in a88) ? a88.options : {
            marginType: MarginTypeV2.DEFAULT_MARGIN,
            marginTop: 0
        });
        this.fontSizeScale = undefined;
        this.touchBackgroundColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.onTipClick = 'onTipClick' in a88 ? a88.onTipClick : () => {
        };
        this.onActionTextClick = 'onActionTextClick' in a88 ? a88.onActionTextClick : () => {
        };
        this.callbackId = undefined;
        this.callbacks = {
            onConfigurationUpdated: (f88) => {
                this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
                this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
            },
            onMemoryLevel() {
            }
        };
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(y87) {
        this.resetParam('options', (y87 && 'options' in y87) ? y87.options : {
            marginType: MarginTypeV2.DEFAULT_MARGIN,
            marginTop: 0
        });
        this.fontSizeScale = undefined;
        this.touchBackgroundColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.onTipClick = 'onTipClick' in y87 ? y87.onTipClick : () => {
        };
        this.onActionTextClick = 'onActionTextClick' in y87 ? y87.onActionTextClick : () => {
        };
        this.callbackId = undefined;
    }

    TextBuilder(x86 = null) {
        this.observeComponentCreation2((w87, x87) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Center
            });
            Flex.padding({
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_notification_margin_start'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_text_paragraph_margin_s'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_default_padding_start'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_default_padding_end'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
        }, Flex);
        this.observeComponentCreation2((u87, v87) => {
            Row.create();
            Row.padding({
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_default_padding_end'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
            Row.width('100%');
            Row.accessibilityDescription(this.onTipClick ? '' : ' ');
            Row.onClick(() => {
                this.onTipClick && this.onTipClick();
            });
        }, Row);
        this.observeComponentCreation2((k87, l87) => {
            If.create();
            if (this.options?.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s87, t87) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([{
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_warning'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        }]);
                        SymbolGlyph.attributeModifier.bind(this)(this.options?.symbolStyle);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.fontSize(`${(this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE) * SYMBOL_SIZE}vp`);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((m87, n87) => {
                        If.create();
                        if (Util.isSymbolResource(this.options?.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((q87, r87) => {
                                    SymbolGlyph.create(this.options?.icon ?? {
                                        'id': -1,
                                        'type': 40000,
                                        params: ['sys.symbol.exclamationmark_circle'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_warning'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                    SymbolGlyph.fontSize(`${(this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE) *
                                        SYMBOL_SIZE}vp`);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((o87, p87) => {
                                    Image.create(this.options?.icon);
                                    Image.width('24vp');
                                    Image.height('24vp');
                                    Image.fillColor({
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_warning'],
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
        this.observeComponentCreation2((i87, j87) => {
            Text.create(this.options.tip);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body1'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.minFontScale(1);
            Text.maxFontScale(Math.min(this.updateFontScale(), 2));
            Text.fontColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_warning'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(2);
            Text.margin({
                start: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_dialog_margin_end'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                })
            });
            Text.flexShrink(1);
            Text.direction(i18n.isRTL(i18n.System.getSystemLanguage()) ? Direction.Rtl : Direction.Ltr);
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((y86, z86) => {
            If.create();
            if (this.options.actionText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g87, h87) => {
                        Button.createWithChild({
                            stateEffect: false,
                            type: ButtonType.Normal
                        });
                        Button.backgroundColor(this.touchBackgroundColor);
                        Button.width(this.options.actionText ? 144 : 0);
                        Button.borderRadius({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_corner_radius_subtab'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Button.padding({
                            right: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level2'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                        });
                        Button.accessibilityDescription(this.onActionTextClick ? '' : ' ');
                        Button.accessibilityRole(this.onActionTextClick ? AccessibilityRoleType.BUTTON :
                            AccessibilityRoleType.ROLE_NONE);
                        Button.onClick(() => {
                            this.onActionTextClick && this.onActionTextClick();
                        });
                    }, Button);
                    this.observeComponentCreation2((e87, f87) => {
                        Row.create();
                        Row.width('100%');
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((c87, d87) => {
                        Text.create(this.options.actionText);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_body2'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.minFontScale(1);
                        Text.maxFontScale(Math.min(this.updateFontScale(), 2));
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_secondary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.maxLines(2);
                        Text.padding(0);
                        Text.margin({
                            end: LengthMetrics.resource({
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_text_paragraph_margin_s'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            })
                        });
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.flexShrink(1);
                        Text.textAlign(TextAlign.End);
                        Text.direction(i18n.isRTL(i18n.System.getSystemLanguage()) ? Direction.Rtl : Direction.Ltr);
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((a87, b87) => {
                        SymbolGlyph.create({
                            'id': -1,
                            'type': 40000,
                            params: ['sys.symbol.chevron_right'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.fontSize(`${(this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE) * SYMBOL_SIZE}vp`);
                        SymbolGlyph.fontColor([{
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_tertiary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        }]);
                    }, SymbolGlyph);
                    Row.pop();
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
    }

    initialRender() {
        this.observeComponentCreation2((v86, w86) => {
            Row.create();
            Row.width('100%');
            Row.position({ y: this.options.marginTop });
            Row.zIndex(ZINDEX_NUM);
        }, Row);
        this.observeComponentCreation2((t86, u86) => {
            Column.create();
            Column.padding(this.options.marginType === MarginTypeV2.DEFAULT_MARGIN
                ? {
                    left: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_card_margin_start'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    },
                    right: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_card_margin_end'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }
                }
                : {
                    left: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_max_padding_start'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    },
                    right: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.ohos_id_max_padding_end'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }
                });
            Column.transition(TransitionEffect.OPACITY.animation({
                curve: curves.cubicBezierCurve(0.33, 0, 0.67, 1),
                duration: this.options.isShown ? START_TIME : END_TIME
            }));
            Column.visibility(this.options.isShown ? Visibility.Visible : Visibility.None);
        }, Column);
        this.observeComponentCreation2((r86, s86) => {
            Column.create();
            Column.width('100%');
            Column.borderRadius(BORDER_RADIUS);
            Column.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.comp_background_warning_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Column.zIndex(ZINDEX_NUM);
        }, Column);
        this.TextBuilder.bind(this)();
        Column.pop();
        Column.pop();
        Row.pop();
    }

    aboutToAppear() {
        try {
            let q86 = this.getUIContext();
            this.isFollowingSystemFontScale = q86.isFollowingSystemFontScale();
            this.maxAppFontScale = q86.getMaxFontScale();
            this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
            this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
            this.callbackId = q86.getHostContext()?.getApplicationContext()?.on('environment', this.callbacks);
        } catch (n86) {
            let o86 = n86.code;
            let p86 = n86.message;
            hilog.error(0x3900, 'Ace', `Failed to init fontsizescale info, cause, code: ${o86}, message: ${p86}`);
        }
    }

    aboutToDisappear() {
        if (this.callbackId) {
            this.getUIContext().getHostContext()?.getApplicationContext()?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
    }

    updateFontScale() {
        let l86 = this.getUIContext();
        let m86 = l86.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(m86, this.maxAppFontScale);
    }

    updateStateVars(k86) {
        if (k86 === undefined) {
            return;
        }
        if ('options' in k86) {
            this.updateParam('options', k86.options);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], ExceptionPromptV2.prototype, 'options', void 0);
__decorate([
    Local
], ExceptionPromptV2.prototype, 'fontSizeScale', void 0);
__decorate([
    Local
], ExceptionPromptV2.prototype, 'touchBackgroundColor', void 0);
__decorate([
    Local
], ExceptionPromptV2.prototype, 'maxAppFontScale', void 0);
__decorate([
    Local
], ExceptionPromptV2.prototype, 'isFollowingSystemFontScale', void 0);
__decorate([
    Event
], ExceptionPromptV2.prototype, 'onTipClick', void 0);
__decorate([
    Event
], ExceptionPromptV2.prototype, 'onActionTextClick', void 0);
__decorate([
    Local
], ExceptionPromptV2.prototype, 'callbackId', void 0);

class Util {
    static isSymbolResource(i86) {
        if (i86 === undefined) {
            return true;
        }
        if (!Util.isResourceType(i86)) {
            return false;
        }
        let j86 = i86;
        return j86.type === Util.RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(h86) {
        if (!h86) {
            return false;
        }
        return typeof h86 !== 'string';
    }
}

Util.RESOURCE_TYPE_SYMBOL = 40000;

export default {
  MarginTypeV2,
  ExceptionPromptV2
}