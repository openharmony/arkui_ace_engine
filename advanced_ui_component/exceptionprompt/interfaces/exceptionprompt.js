/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
const curves = requireNativeModule('ohos.curves');
const hilog = requireNapi('hilog');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const i18n = requireNapi('i18n');

const i14 = 250;
const j14 = 200;
const k14 = 12;
const l14 = 9;
const n14 = 24;
const o14 = 2;
const p14 = 1;
const q14 = 1;

export var MarginType;
(function (MarginType) {
    MarginType[MarginType['DEFAULT_MARGIN'] = 0] = 'DEFAULT_MARGIN';
    MarginType[MarginType['FIT_MARGIN'] = 1] = 'FIT_MARGIN';
})(MarginType || (MarginType = {}));

export class ExceptionPrompt extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__options = new SynchedPropertyObjectOneWayPU(params.options, this, 'options');
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
            onConfigurationUpdated: (config) => {
                this.fontSizeScale = Math.min(this.updateFontScale(), o14);
                this.fontSizeScale = Math.max(this.fontSizeScale, p14);
            },
            onMemoryLevel() {
            }
        };
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.fontSizeScale !== undefined) {
            this.fontSizeScale = params.fontSizeScale;
        }
        if (params.touchBackgroundColor !== undefined) {
            this.touchBackgroundColor = params.touchBackgroundColor;
        }
        if (params.maxAppFontScale !== undefined) {
            this.maxAppFontScale = params.maxAppFontScale;
        }
        if (params.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
        }
        if (params.onTipClick !== undefined) {
            this.onTipClick = params.onTipClick;
        }
        if (params.onActionTextClick !== undefined) {
            this.onActionTextClick = params.onActionTextClick;
        }
        if (params.callbackId !== undefined) {
            this.callbackId = params.callbackId;
        }
        if (params.callbacks !== undefined) {
            this.callbacks = params.callbacks;
        }
    }

    updateStateVars(params) {
        this.__options.reset(params.options);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__options.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
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

    set options(newValue) {
        this.__options.set(newValue);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }

    TextBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.options?.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                        SymbolGlyph.fontSize(`${(this.fontSizeScale ?? q14) * n14}vp`);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (Util.v14(this.options?.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                                    SymbolGlyph.fontSize(`${(this.fontSizeScale ?? q14) * n14}vp`);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.options.actionText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithChild({ stateEffect: false, type: ButtonType.Normal });
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.width('100%');
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create({
                            'id': -1,
                            'type': 40000,
                            params: ['sys.symbol.chevron_right'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.fontSize(`${(this.fontSizeScale ?? q14) * n14}vp`);
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.width('100%');
            Row.position({ y: this.options.marginTop });
            Row.zIndex(l14);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                duration: this.options.isShown ? i14 : j14
            }));
            Column.visibility(this.options.isShown ? Visibility.Visible : Visibility.None);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
            Column.borderRadius(k14);
            Column.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.comp_background_warning_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Column.zIndex(l14);
        }, Column);
        this.TextBuilder.bind(this)();
        Column.pop();
        Column.pop();
        Row.pop();
    }

    aboutToAppear() {
        try {
            let u14 = this.getUIContext();
            this.isFollowingSystemFontScale = u14.isFollowingSystemFontScale();
            this.maxAppFontScale = u14.getMaxFontScale();
            this.fontSizeScale = Math.min(this.updateFontScale(), o14);
            this.fontSizeScale = Math.max(this.fontSizeScale, p14);
            this.callbackId = u14.getHostContext()?.getApplicationContext()?.on('environment', this.callbacks);
        } catch (err) {
            let code = err.code;
            let message = err.message;
            hilog.error(0x3900, 'Ace', `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
        }
    }

    aboutToDisappear() {
        if (this.callbackId) {
            this.getUIContext().getHostContext()?.getApplicationContext()?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
    }

    updateFontScale() {
        let s14 = this.getUIContext();
        let t14 = s14.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(t14, this.maxAppFontScale);
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class Util {
    static v14(r14) {
        if (r14 === undefined) {
            return true;
        }
        if (!Util.w14(r14)) {
            return false;
        }
        let resource = r14;
        return resource.type === Util.x14;
    }

    static w14(resource) {
        if (!resource) {
            return false;
        }
        return typeof resource !== 'string';
    }
}

Util.x14 = 40000;

export default {
    MarginType,
    ExceptionPrompt
}