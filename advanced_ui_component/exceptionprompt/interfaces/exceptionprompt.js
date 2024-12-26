/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
if (PUV2ViewBase.contextStack === undefined) {
    Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const curves = requireNativeModule('ohos.curves');
const hilog = requireNapi('hilog');
const START_TIME = 250;
const END_TIME = 200;
const BORDER_RADIUS = 12;
const ZINDEX_NUM = 9;
const SYMBOL_SIZE = 24;
const MAX_SYMBOL_FONT_SCALE = 2;
const MIN_SYMBOL_FONT_SCALE = 1;
const DEFAULT_SYMBOL_FONT_SCALE = 1;

export var MarginType;
(function (z1) {
    z1[z1.DEFAULT_MARGIN = 0] = 'DEFAULT_MARGIN';
    z1[z1.FIT_MARGIN = 1] = 'FIT_MARGIN';
})(MarginType || (MarginType = {}));

export class ExceptionPrompt extends ViewPU {
    constructor(s1, t1, u1, v1 = -1, w1 = undefined, x1) {
        super(s1, u1, v1, x1);
        if (typeof w1 === 'function') {
            this.paramsGenerator_ = w1;
        }
        this.__options = new SynchedPropertyObjectOneWayPU(t1.options, this, 'options');
        this.__fontSizeScale = new ObservedPropertyObjectPU(undefined, this, 'fontSizeScale');
        this.touchBackgroundColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.onTipClick = undefined;
        this.onActionTextClick = undefined;
        this.callbackId = undefined;
        this.callbacks = {
            onConfigurationUpdated: (y1) => {
                this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
                this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
            },
            onMemoryLevel() {
            }
        };
        this.setInitiallyProvidedValue(t1);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(r1) {
        if (r1.fontSizeScale !== undefined) {
            this.fontSizeScale = r1.fontSizeScale;
        }
        if (r1.touchBackgroundColor !== undefined) {
            this.touchBackgroundColor = r1.touchBackgroundColor;
        }
        if (r1.maxAppFontScale !== undefined) {
            this.maxAppFontScale = r1.maxAppFontScale;
        }
        if (r1.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = r1.isFollowingSystemFontScale;
        }
        if (r1.onTipClick !== undefined) {
            this.onTipClick = r1.onTipClick;
        }
        if (r1.onActionTextClick !== undefined) {
            this.onActionTextClick = r1.onActionTextClick;
        }
        if (r1.callbackId !== undefined) {
            this.callbackId = r1.callbackId;
        }
        if (r1.callbacks !== undefined) {
            this.callbacks = r1.callbacks;
        }
    }

    updateStateVars(q1) {
        this.__options.reset(q1.options);
    }

    purgeVariableDependenciesOnElmtId(p1) {
        this.__options.purgeDependencyOnElmtId(p1);
        this.__fontSizeScale.purgeDependencyOnElmtId(p1);
    }

    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get options() {
        return this.__options.get();
    }

    set options(o1) {
        this.__options.set(o1);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(n1) {
        this.__fontSizeScale.set(n1);
    }

    TextBuilder(m = null) {
        this.observeComponentCreation2((k1, l1) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign
                    .Center
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
        this.observeComponentCreation2((i1, j1) => {
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
        this.observeComponentCreation2((g1, h1) => {
            Flex.create({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center });
        }, Flex);
        this.observeComponentCreation2((a1, b1) => {
            If.create();
            if (this.options?.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e1, f1) => {
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
                    this.observeComponentCreation2((c1, d1) => {
                        If.create();
                        if (Util.isSymbolResource(this.options?.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((f2, g2) => {
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
                                this.observeComponentCreation2((d2, e2) => {
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
        this.observeComponentCreation2((y, z) => {
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
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_dialog_margin_end'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_dialog_margin_end'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
        }, Text);
        Text.pop();
        Flex.pop();
        Row.pop();
        this.observeComponentCreation2((n, o) => {
            If.create();
            if (this.options.actionText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v, w) => {
                        Button.createWithChild({ stateEffect: false, type: ButtonType.Normal });
                        Button.backgroundColor(this.touchBackgroundColor);
                        Button.width(this.options.actionText ? 168 : 0);
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
                                params: ['sys.float.ohos_id_elements_margin_vertical_l'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            left: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_elements_margin_vertical_l'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            }
                        });
                        Button.accessibilityDescription(this.onActionTextClick ? '' : ' ');
                        Button.onClick(() => {
                            this.onActionTextClick && this.onActionTextClick();
                        });
                    }, Button);
                    this.observeComponentCreation2((t, u) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((r, s) => {
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
                            right: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_text_paragraph_margin_s'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            }
                        });
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((p, q) => {
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
        this.observeComponentCreation2((k, l) => {
            Row.create();
            Row.width('100%');
            Row.position({ y: this.options.marginTop });
            Row.zIndex(ZINDEX_NUM);
        }, Row);
        this.observeComponentCreation2((i, j) => {
            Column.create();
            Column.padding(this.options.marginType === MarginType.DEFAULT_MARGIN ? {
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
            } : {
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
        this.observeComponentCreation2((g, h) => {
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
            let f = this.getUIContext();
            this.isFollowingSystemFontScale = f.isFollowingSystemFontScale();
            this.maxAppFontScale = f.getMaxFontScale();
            this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
            this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
            this.callbackId = f.getHostContext()?.getApplicationContext()?.on('environment', this.callbacks);
        } catch (c) {
            let d = c.code;
            let e = c.message;
            hilog.error(0x3900, 'Ace', `Failed to init fontsizescale info, cause, code: ${d}, message: ${e}`);
        }
    }

    aboutToDisappear() {
        if (this.callbackId) {
            this.getUIContext().getHostContext()?.getApplicationContext()?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
    }

    updateFontScale() {
        let a = this.getUIContext();
        let b = a.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(b, this.maxAppFontScale);
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class Util {
    static isSymbolResource(b2) {
        if (b2 === undefined) {
            return true;
        }
        if (!Util.isResourceType(b2)) {
            return false;
        }
        let c2 = b2;
        return c2.type === Util.RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(a2) {
        if (!a2) {
            return false;
        }
        return typeof a2 !== 'string';
    }
}

Util.RESOURCE_TYPE_SYMBOL = 40000;

export default {
    MarginType,
    ExceptionPrompt
}