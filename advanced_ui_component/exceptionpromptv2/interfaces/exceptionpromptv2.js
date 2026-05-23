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

var __decorate = (this && this.__decorate) || function (b2, c2, d2, e2) {
    var f2 = arguments.length, g2 = f2 < 3 ? c2 : e2 === null ? e2 = Object.getOwnPropertyDescriptor(c2, d2) : e2, h2;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        g2 = Reflect.decorate(b2, c2, d2, e2);
    } else {
        for (var i2 = b2.length - 1; i2 >= 0; i2--) {
            if (h2 = b2[i2]) {
                g2 = (f2 < 3 ? h2(g2) : f2 > 3 ? h2(c2, d2, g2) : h2(c2, d2)) || g2;
            }
        }
    }
    return f2 > 3 && g2 && Object.defineProperty(c2, d2, g2), g2;
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
(function (a2) {
    a2[a2['DEFAULT_MARGIN'] = 0] = 'DEFAULT_MARGIN';
    a2[a2['FIT_MARGIN'] = 1] = 'FIT_MARGIN';
})(MarginTypeV2 || (MarginTypeV2 = {}));
let PromptOptionsV2 = class PromptOptionsV2 {
    constructor(z1) {
        if (z1) {
            this.marginType = z1.marginType;
            this.marginTop = z1.marginTop;
            if (z1.icon !== undefined) {
                this.icon = z1.icon;
            }
            if (z1.symbolStyle !== undefined) {
                this.symbolStyle = z1.symbolStyle;
            }
            if (z1.tip !== undefined) {
                this.tip = z1.tip;
            }
            if (z1.actionText !== undefined) {
                this.actionText = z1.actionText;
            }
            if (z1.isShown !== undefined) {
                this.isShown = z1.isShown;
            }
        } else {
            this.marginType = MarginTypeV2.DEFAULT_MARGIN;
            this.marginTop = 0;
        }
    }
};
__decorate([
    Trace
], PromptOptionsV2.prototype, 'icon', void 0);
__decorate([
    Trace
], PromptOptionsV2.prototype, 'symbolStyle', void 0);
__decorate([
    Trace
], PromptOptionsV2.prototype, 'tip', void 0);
__decorate([
    Trace
], PromptOptionsV2.prototype, 'marginType', void 0);
__decorate([
    Trace
], PromptOptionsV2.prototype, 'actionText', void 0);
__decorate([
    Trace
], PromptOptionsV2.prototype, 'marginTop', void 0);
__decorate([
    Trace
], PromptOptionsV2.prototype, 'isShown', void 0);
PromptOptionsV2 = __decorate([
    ObservedV2
], PromptOptionsV2);

export { PromptOptionsV2 };

export class ExceptionPromptV2 extends ViewV2 {
    constructor(s1, t1, u1, v1 = -1, w1, x1) {
        super(s1, v1, x1);
        this.initParam('options', (t1 && 'options' in t1) ? t1.options : new PromptOptionsV2({
            marginType: MarginTypeV2.DEFAULT_MARGIN,
            marginTop: 0
        }));
        this.initParam('onTipClick', (t1 && 'onTipClick' in t1) ? t1.onTipClick : undefined);
        this.initParam('onActionTextClick', (t1 && 'onActionTextClick' in t1) ? t1.onActionTextClick : undefined);
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
        this.callbackId = undefined;
        this.callbacks = {
            onConfigurationUpdated: (y1) => {
                this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
                this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
            },
            onMemoryLevel() {
            }
        };
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(r1) {
        this.resetParam('options', (r1 && 'options' in r1) ? r1.options : new PromptOptionsV2({
            marginType: MarginTypeV2.DEFAULT_MARGIN,
            marginTop: 0
        }));
        this.resetParam('onTipClick', (r1 && 'onTipClick' in r1) ? r1.onTipClick : undefined);
        this.resetParam('onActionTextClick', (r1 && 'onActionTextClick' in r1) ? r1.onActionTextClick : undefined);
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
        this.callbackId = undefined;
    }

    TextBuilder(q = null) {
        this.observeComponentCreation2((p1, q1) => {
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
        this.observeComponentCreation2((n1, o1) => {
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
        this.observeComponentCreation2((d1, e1) => {
            If.create();
            if (this.options?.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l1, m1) => {
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
                    this.observeComponentCreation2((f1, g1) => {
                        If.create();
                        if (Util.isSymbolResource(this.options?.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((j1, k1) => {
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
                                this.observeComponentCreation2((h1, i1) => {
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
        this.observeComponentCreation2((b1, c1) => {
            Text.create(this.options?.tip);
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
        this.observeComponentCreation2((r, s) => {
            If.create();
            if (this.options?.actionText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z, a1) => {
                        Button.createWithChild({
                            stateEffect: false,
                            type: ButtonType.Normal
                        });
                        Button.backgroundColor(this.touchBackgroundColor);
                        Button.width(this.options?.actionText ? 144 : 0);
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
                    this.observeComponentCreation2((x, y) => {
                        Row.create();
                        Row.width('100%');
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((v, w) => {
                        Text.create(this.options?.actionText);
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
                    this.observeComponentCreation2((t, u) => {
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
        this.observeComponentCreation2((o, p) => {
            Row.create();
            Row.width('100%');
            Row.position({ y: this.options?.marginTop });
            Row.zIndex(ZINDEX_NUM);
        }, Row);
        this.observeComponentCreation2((m, n) => {
            Column.create();
            Column.padding(this.options?.marginType === MarginTypeV2.DEFAULT_MARGIN
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
                duration: this.options?.isShown ? START_TIME : END_TIME
            }));
            Column.visibility(this.options?.isShown ? Visibility.Visible : Visibility.None);
        }, Column);
        this.observeComponentCreation2((k, l) => {
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
            let j = this.getUIContext();
            this.isFollowingSystemFontScale = j.isFollowingSystemFontScale();
            this.maxAppFontScale = j.getMaxFontScale();
            this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
            this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
            this.callbackId = j.getHostContext()?.getApplicationContext()?.on('environment', this.callbacks);
        } catch (g) {
            let h = g.code;
            let i = g.message;
            hilog.error(0x3900, 'Ace', `Failed to init fontsizescale info, cause, code: ${h}, message: ${i}`);
        }
    }

    aboutToDisappear() {
        if (this.callbackId) {
            this.getUIContext().getHostContext()?.getApplicationContext()?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
    }

    updateFontScale() {
        let e = this.getUIContext();
        let f = e.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(f, this.maxAppFontScale);
    }

    updateStateVars(d) {
        if (d === undefined) {
            return;
        }
        if ('options' in d) {
            this.updateParam('options', d.options);
        }
        if ('onTipClick' in d) {
            this.updateParam('onTipClick', d.onTipClick);
        }
        if ('onActionTextClick' in d) {
            this.updateParam('onActionTextClick', d.onActionTextClick);
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
    Param
], ExceptionPromptV2.prototype, 'onTipClick', void 0);
__decorate([
    Param
], ExceptionPromptV2.prototype, 'onActionTextClick', void 0);
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
    Local
], ExceptionPromptV2.prototype, 'callbackId', void 0);

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
    ExceptionPromptV2, PromptOptionsV2, MarginTypeV2
}