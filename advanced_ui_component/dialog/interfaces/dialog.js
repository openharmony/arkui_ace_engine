/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
const display = requireNapi('display');
const hilog = requireNapi('hilog');
const measure = requireNapi('measure');
const resourceManager = requireNapi('resourceManager');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const accessibility = requireNapi('accessibility');
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const i18n = requireNapi('i18n')

class CustomThemeImpl {
    constructor(colors) {
        this.colors = colors;
    }
}

const TITLE_MAX_LINES = 2;
const HORIZON_BUTTON_MAX_COUNT = 2;
const VERTICAL_BUTTON_MAX_COUNT = 4;
const BUTTON_LAYOUT_WEIGHT = 1;
const CONTENT_MAX_LINES = 2;
const LOADING_PROGRESS_WIDTH = 40;
const LOADING_PROGRESS_HEIGHT = 40;
const LOADING_MAX_LINES = 10;
const LOADING_MAX_LINES_BIG_FONT = 4;
const LOADING_TEXT_LAYOUT_WEIGHT = 1;
const LOADING_TEXT_MARGIN_LEFT = 12;
const LOADING_MIN_HEIGHT = 48;
const LIST_MIN_HEIGHT = 48;
const CHECKBOX_CONTAINER_LENGTH = 20;
const TEXT_MIN_HEIGHT = 48;
const MIN_CONTENT_HEIGHT = 100;
const MAX_CONTENT_HEIGHT = 30000;
const KEYCODE_UP = 2012;
const KEYCODE_DOWN = 2013;
const IGNORE_KEY_EVENT_TYPE = 1;
const FIRST_ITEM_INDEX = 0;
const VERSION_TWELVE = 50000012;
const MAX_FONT_SCALE = 2;
const FADEOUT_GRADIENT_WIDTH = 32;
const FADEOUT_ENABLE = 'true';
// 'sys.float.alert_container_max_width'
const MAX_DIALOG_WIDTH = getNumberByResourceId(125831042, 400);
// 'sys.float.padding_level8'
const BUTTON_HORIZONTAL_PADDING = getNumberByResourceId(125830927, 16);
// 'sys.float.Body_L'
const BODY_L = getNumberByResourceId(125830970, 16);
// 'sys.float.Body_M'
const BODY_M = getNumberByResourceId(125830971, 14);
// 'sys.float.Body_S'
const BODY_S = getNumberByResourceId(125830972, 12);
// 'sys.float.Title_S'
const TITLE_S = getNumberByResourceId(125830966, 20);
// 'sys.float.padding_level8'
const PADDING_LEVEL_8 = getNumberByResourceId(125830927, 16);
const BUTTON_HORIZONTAL_MARGIN = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.alert_right_padding_horizontal'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 16);
});
const BUTTON_HORIZONTAL_SPACE = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.alert_button_horizontal_space'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 8);
});
const BUTTON_MIN_FONT_SIZE = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_button_font_min_size'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 9);
});
const BUTTON_MAX_FONT_SIZE = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_button_font_max_size'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 16);
});
const DEFAULT_IMAGE_SIZE = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_tip_image_size'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 64);
});
const DEFAULT_IMAGE_RADIUS = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_tip_image_radius'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 12);
});
const TIP_TEXT_TOP_PADDING = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_tip_text_top_padding'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 16);
});
const TIP_CHECKBOX_TOP_PADDING = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_checkbox_top_padding'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 8);
});
const TIP_CHECKBOX_BOTTOM_PADDING = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_checkbox_bottom_padding'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 8, true);
});
const TIP_CHECKBOX_END_MARGIN = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_checkbox_end_margin'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 8);
});
const SUBTITLE_SIZE = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_subtitle_font_size'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 14);
});
const CHECKBOX_CONTAINER_HEIGHT = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_checkbox_min_height'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 48, true);
});
const CONTENT_END_MARGIN = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_content_right_margin'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 16);
});
const SCROLL_END_MARGIN = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_scroll_right_margin'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 16);
});
const DIALOG_DIVIDER_SHOW = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_divider_show'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 1, true);
});
const ALERT_BUTTON_STYLE = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.alert_button_style'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 2, true);
});
const ALERT_TITLE_ALIGNMENT = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.alert_title_alignment'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 1);
});
const ERROR_BUTTON_STYLE = lazyInit(() => {
    return getLengthMetricsByResource({
        'id': -1,
        'type': 10002,
        params: ['sys.float.dialog_error_button_style'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    }, 2, true);
});
// 'sys.string.ohos_id_text_fadeout_enable_default'
const IS_FADEOUT_ENABLE = lazyInit(() => {
    return getString(125831120) === FADEOUT_ENABLE;
});
// 'sys.string.dialog_title_font_weight'
const TITLE_FONT_WEIGHT = lazyInit(() => {
    let fontWeight = FontWeight[getString(125834679) || 'Bold'];
    return fontWeight;
});
// 'sys.string.dialog_content_font_weight'
const CONTENT_FONT_WEIGHT = lazyInit(() => {
    let fontWeight = FontWeight[getString(125834682) || 'Medium'];
    return fontWeight;
});
const SCROLL_BAR_OFFSET = 20;

export class TipsDialog extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.controller = undefined;
        this.imageRes = null;
        this.__imageSize =
            new ObservedPropertyObjectPU({ width: DEFAULT_IMAGE_SIZE(), height: DEFAULT_IMAGE_SIZE() }, this,
                'imageSize');
        this.title = null;
        this.content = null;
        this.checkAction = undefined;
        this.onCheckedChange = undefined;
        this.checkTips = null;
        this.__isChecked = new ObservedPropertySimplePU(false, this, 'isChecked');
        this.primaryButton = null;
        this.secondaryButton = null;
        this.buttons = undefined;
        this.__textAlignment = new ObservedPropertySimplePU(TextAlign.Start, this, 'textAlignment');
        this.marginOffset = 0;
        this.contentScroller = new Scroller();
        this.__fontColorWithTheme = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'fontColorWithTheme');
        this.theme = new CustomThemeImpl({});
        this.themeColorMode = ThemeColorMode.SYSTEM;
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.__minContentHeight = new ObservedPropertySimplePU(160, this, 'minContentHeight');
        this.updateTextAlign = (maxWidth) => {
            if (this.content) {
                this.textAlignment = getTextAlign(maxWidth, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.appMaxFontScale = 3.2;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.controller !== undefined) {
            this.controller = params.controller;
        }
        if (params.imageRes !== undefined) {
            this.imageRes = params.imageRes;
        }
        if (params.imageSize !== undefined) {
            this.imageSize = params.imageSize;
        }
        if (params.title !== undefined) {
            this.title = params.title;
        }
        if (params.content !== undefined) {
            this.content = params.content;
        }
        if (params.checkAction !== undefined) {
            this.checkAction = params.checkAction;
        }
        if (params.onCheckedChange !== undefined) {
            this.onCheckedChange = params.onCheckedChange;
        }
        if (params.checkTips !== undefined) {
            this.checkTips = params.checkTips;
        }
        if (params.isChecked !== undefined) {
            this.isChecked = params.isChecked;
        }
        if (params.primaryButton !== undefined) {
            this.primaryButton = params.primaryButton;
        }
        if (params.secondaryButton !== undefined) {
            this.secondaryButton = params.secondaryButton;
        }
        if (params.buttons !== undefined) {
            this.buttons = params.buttons;
        }
        if (params.textAlignment !== undefined) {
            this.textAlignment = params.textAlignment;
        }
        if (params.marginOffset !== undefined) {
            this.marginOffset = params.marginOffset;
        }
        if (params.contentScroller !== undefined) {
            this.contentScroller = params.contentScroller;
        }
        if (params.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = params.fontColorWithTheme;
        }
        if (params.theme !== undefined) {
            this.theme = params.theme;
        }
        if (params.themeColorMode !== undefined) {
            this.themeColorMode = params.themeColorMode;
        }
        if (params.fontSizeScale !== undefined) {
            this.fontSizeScale = params.fontSizeScale;
        }
        if (params.minContentHeight !== undefined) {
            this.minContentHeight = params.minContentHeight;
        }
        if (params.updateTextAlign !== undefined) {
            this.updateTextAlign = params.updateTextAlign;
        }
        if (params.imageIndex !== undefined) {
            this.imageIndex = params.imageIndex;
        }
        if (params.textIndex !== undefined) {
            this.textIndex = params.textIndex;
        }
        if (params.checkBoxIndex !== undefined) {
            this.checkBoxIndex = params.checkBoxIndex;
        }
        if (params.appMaxFontScale !== undefined) {
            this.appMaxFontScale = params.appMaxFontScale;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__imageSize.purgeDependencyOnElmtId(rmElmtId);
        this.__isChecked.purgeDependencyOnElmtId(rmElmtId);
        this.__textAlignment.purgeDependencyOnElmtId(rmElmtId);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
        this.__minContentHeight.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__imageSize.aboutToBeDeleted();
        this.__isChecked.aboutToBeDeleted();
        this.__textAlignment.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(ctr) {
        this.controller = ctr;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(newValue) {
        this.__imageSize.set(newValue);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(newValue) {
        this.__isChecked.set(newValue);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(newValue) {
        this.__textAlignment.set(newValue);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(newValue) {
        this.__fontColorWithTheme.set(newValue);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(newValue) {
        this.__minContentHeight.set(newValue);
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, elmtId, () => {
                    }, { page: 'library/src/main/ets/components/dialog.ets', line: 182, col: 5 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            controller: this.controller,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            buttons: this.buttons,
                            theme: this.theme,
                            themeColorMode: this.themeColorMode,
                            fontSizeScale: this.fontSizeScale,
                            minContentHeight: this.minContentHeight
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    contentBuilder(parent = null) {
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new TipsDialogContentLayout(this, {
                        title: this.title,
                        content: this.content,
                        checkTips: this.checkTips,
                        minContentHeight: this.__minContentHeight,
                        updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                ForEach.create();
                                const forEachItemGenFunction = _item => {
                                    const index = _item;
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        If.create();
                                        if (index === this.imageIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.imagePart.bind(this)();
                                            });
                                        } else if (index === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                    Column.create();
                                                    Column.padding({ top: TIP_TEXT_TOP_PADDING() });
                                                }, Column);
                                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.textPart.bind(this)();
                                                WithTheme.pop();
                                                Column.pop();
                                            });
                                        } else {
                                            this.ifElseBranchUpdateFunction(2, () => {
                                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.checkBoxPart.bind(this)();
                                                WithTheme.pop();
                                            });
                                        }
                                    }, If);
                                    If.pop();
                                };
                                this.forEachUpdateFunction(elmtId,
                                    [this.imageIndex, this.textIndex, this.checkBoxIndex], forEachItemGenFunction);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, elmtId, () => {
                    }, { page: 'library/src/main/ets/components/dialog.ets', line: 197, col: 5 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            title: this.title,
                            content: this.content,
                            checkTips: this.checkTips,
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const index = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            If.create();
                                            if (index === this.imageIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.imagePart.bind(this)();
                                                });
                                            } else if (index === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Column.create();
                                                        Column.padding({ top: TIP_TEXT_TOP_PADDING() });
                                                    }, Column);
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.textPart.bind(this)();
                                                    WithTheme.pop();
                                                    Column.pop();
                                                });
                                            } else {
                                                this.ifElseBranchUpdateFunction(2, () => {
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.checkBoxPart.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            }
                                        }, If);
                                        If.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId,
                                        [this.imageIndex, this.textIndex, this.checkBoxIndex], forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'TipsDialogContentLayout' });
        }
    }

    checkBoxPart(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.accessibilityGroup(true);
            Row.accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.isChecked));
            Row.accessibilityDescription(this.isChecked ? {
                'id': -1,
                'type': 10003,
                params: ['sys.string.advanced_dialog_accessibility_cancel_checked_desc'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            } : {
                'id': -1,
                'type': 10003,
                params: ['sys.string.slider_accessibility_unselectedDesc'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Row.onClick(() => {
                this.isChecked = !this.isChecked;
                if (this.checkAction) {
                    this.checkAction(this.isChecked);
                }
                try {
                    let eventInfo = ({
                        type: 'announceForAccessibility',
                        bundleName: getContext()?.abilityInfo?.bundleName,
                        triggerAction: 'common',
                        textAnnouncedForAccessibility: this.isChecked ?
                        getContext().resourceManager.getStringSync(125833934) :
                        getContext().resourceManager.getStringSync(125833935)
                    });
                    accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                        console.info(`Accessibility send event`);
                    });
                } catch (exception) {
                    let code = exception.code;
                    let message = exception.message;
                    hilog.error(0x3900, 'Ace', `Faild to send event, cause, code: ${code}, message: ${message}`);
                }
            });
            Row.padding({ top: TIP_CHECKBOX_TOP_PADDING(), bottom: TIP_CHECKBOX_BOTTOM_PADDING() });
            Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT() });
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.checkTips !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Checkbox.create({ name: '', group: 'checkboxGroup' });
                        Checkbox.select(this.isChecked);
                        Checkbox.onChange((checked) => {
                            this.isChecked = checked;
                            if (this.checkAction) {
                                this.checkAction(checked);
                            }
                            if (this.onCheckedChange) {
                                this.onCheckedChange(checked);
                            }
                        });
                        Checkbox.margin({
                            start: LengthMetrics.vp(0),
                            end: LengthMetrics.vp(TIP_CHECKBOX_END_MARGIN())
                        });
                    }, Checkbox);
                    Checkbox.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.checkTips);
                        Text.fontSize(`${BODY_L}fp`);
                        Text.fontWeight(FontWeight.Regular);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.maxLines(CONTENT_MAX_LINES);
                        Text.layoutWeight(1);
                        Text.focusable(false);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                    }, Text);
                    Text.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
    }

    imagePart(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.imageRes);
            Image.objectFit(ImageFit.Contain);
            Image.borderRadius(DEFAULT_IMAGE_RADIUS());
            Image.constraintSize({
                maxWidth: this.imageSize?.width ?? DEFAULT_IMAGE_SIZE(),
                maxHeight: this.imageSize?.height ?? DEFAULT_IMAGE_SIZE()
            });
        }, Image);
        Column.pop();
    }

    textPart(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create(this.contentScroller);
            Scroll.fadingEdge(IS_FADEOUT_ENABLE(), { fadingEdgeLength: LengthMetrics.vp(FADEOUT_GRADIENT_WIDTH) });
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
        }, Scroll);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.margin({ end: LengthMetrics.vp(CONTENT_END_MARGIN()) });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.title !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.padding({
                            bottom: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level8'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            }
                        });
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.title);
                        Text.fontSize(`${TITLE_S}fp`);
                        Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
                        Text.fontWeight(TITLE_FONT_WEIGHT());
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(TextAlign.Center);
                        Text.maxLines(CONTENT_MAX_LINES);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.width('100%');
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.content !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.content);
                        Text.focusable(true);
                        Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
                        Text.focusBox({
                            strokeWidth: LengthMetrics.px(0)
                        });
                        Text.fontSize(this.getContentFontSize());
                        Text.fontWeight(CONTENT_FONT_WEIGHT());
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(this.textAlignment);
                        Text.width('100%');
                        Text.onKeyEvent((event) => {
                            if (event) {
                                resolveKeyEvent(event, this.contentScroller);
                            }
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
        Scroll.pop();
    }

    aboutToAppear() {
        this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
        this.theme.colors.fontPrimary : {
                'id': -1,
                'type': 10001,
                params: ['sys.color.font_primary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        let uiContext = this.getUIContext();
        this.appMaxFontScale = uiContext.getMaxFontScale();
        this.initButtons();
        this.initMargin();
    }

    getContentFontSize() {
        return BODY_L + 'fp';
    }

    initButtons() {
        if (!this.primaryButton && !this.secondaryButton) {
            return;
        }
        this.buttons = [];
        if (this.primaryButton) {
            this.buttons.push(this.primaryButton);
        }
        if (this.secondaryButton) {
            this.buttons.push(this.secondaryButton);
        }
    }

    initMargin() {
        this.marginOffset = 0 - SCROLL_END_MARGIN();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class TipsDialogContentLayout extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.title = null;
        this.content = null;
        this.checkTips = null;
        this.updateTextAlign = (maxWidth) => {
        };
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(params.minContentHeight, this, 'minContentHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.childrenSize = 3;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.title !== undefined) {
            this.title = params.title;
        }
        if (params.content !== undefined) {
            this.content = params.content;
        }
        if (params.checkTips !== undefined) {
            this.checkTips = params.checkTips;
        }
        if (params.updateTextAlign !== undefined) {
            this.updateTextAlign = params.updateTextAlign;
        }
        if (params.dialogBuilder !== undefined) {
            this.dialogBuilder = params.dialogBuilder;
        }
        if (params.imageIndex !== undefined) {
            this.imageIndex = params.imageIndex;
        }
        if (params.textIndex !== undefined) {
            this.textIndex = params.textIndex;
        }
        if (params.checkBoxIndex !== undefined) {
            this.checkBoxIndex = params.checkBoxIndex;
        }
        if (params.childrenSize !== undefined) {
            this.childrenSize = params.childrenSize;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__minContentHeight.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(parent = null) {
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(newValue) {
        this.__minContentHeight.set(newValue);
    }

    onPlaceChildren(selfLayoutInfo, children, constraint) {
        let currentX = 0;
        let currentY = 0;
        for (let index = 0; index < children.length; index++) {
            let child = children[index];
            child.layout({ x: currentX, y: currentY });
            currentY += child.measureResult.height;
        }
    }

    onMeasureSize(selfLayoutInfo, children, constraint) {
        let sizeResult = { width: Number(constraint.maxWidth), height: 0 };
        if (children.length < this.childrenSize) {
            return sizeResult;
        }
        let height = 0;
        let checkBoxHeight = 0;
        if (this.checkTips !== null) {
            let checkboxChild = children[this.checkBoxIndex];
            let checkboxConstraint = {
                maxWidth: constraint.maxWidth,
                minHeight: CHECKBOX_CONTAINER_HEIGHT(),
                maxHeight: constraint.maxHeight
            };
            let checkBoxMeasureResult = checkboxChild.measure(checkboxConstraint);
            checkBoxHeight = checkBoxMeasureResult.height;
            height += checkBoxHeight;
        }
        let imageChild = children[this.imageIndex];
        let textMinHeight = 0;
        if (this.title !== null || this.content !== null) {
            textMinHeight = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
        }
        let imageMaxHeight = Number(constraint.maxHeight) - checkBoxHeight - textMinHeight;
        let imageConstraint = {
            maxWidth: constraint.maxWidth,
            maxHeight: imageMaxHeight
        };
        let imageMeasureResult = imageChild.measure(imageConstraint);
        height += imageMeasureResult.height;
        if (this.title !== null || this.content !== null) {
            let textChild = children[this.textIndex];
            this.updateTextAlign(sizeResult.width);
            let contentMaxHeight = Number(constraint.maxHeight) - imageMeasureResult.height - checkBoxHeight;
            let contentConstraint = {
                maxWidth: constraint.maxWidth,
                maxHeight: Math.max(contentMaxHeight, TEXT_MIN_HEIGHT)
            };
            let contentMeasureResult = textChild.measure(contentConstraint);
            height += contentMeasureResult.height;
        }
        sizeResult.height = height;
        this.minContentHeight =
            Math.max(checkBoxHeight + imageMeasureResult.height + textMinHeight, MIN_CONTENT_HEIGHT);
        return sizeResult;
    }

    initialRender() {
        this.dialogBuilder.bind(this)();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class SelectDialog extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.controller = undefined;
        this.title = '';
        this.content = '';
        this.confirm = null;
        this.radioContent = [];
        this.buttons = [];
        this.contentPadding = undefined;
        this.isFocus = false;
        this.currentFocusIndex = -1;
        this.radioHeight = 0;
        this.itemHeight = 0;
        this.__selectedIndex = new ObservedPropertySimplePU(-1, this, 'selectedIndex');
        this.contentBuilder = this.buildContent;
        this.__fontColorWithTheme = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'fontColorWithTheme');
        this.__dividerColorWithTheme = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.comp_divider'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'dividerColorWithTheme');
        this.theme = new CustomThemeImpl({});
        this.themeColorMode = ThemeColorMode.SYSTEM;
        this.contentScroller = new Scroller();
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.__minContentHeight = new ObservedPropertySimplePU(MIN_CONTENT_HEIGHT, this, 'minContentHeight');
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.controller !== undefined) {
            this.controller = params.controller;
        }
        if (params.title !== undefined) {
            this.title = params.title;
        }
        if (params.content !== undefined) {
            this.content = params.content;
        }
        if (params.confirm !== undefined) {
            this.confirm = params.confirm;
        }
        if (params.radioContent !== undefined) {
            this.radioContent = params.radioContent;
        }
        if (params.buttons !== undefined) {
            this.buttons = params.buttons;
        }
        if (params.contentPadding !== undefined) {
            this.contentPadding = params.contentPadding;
        }
        if (params.isFocus !== undefined) {
            this.isFocus = params.isFocus;
        }
        if (params.currentFocusIndex !== undefined) {
            this.currentFocusIndex = params.currentFocusIndex;
        }
        if (params.radioHeight !== undefined) {
            this.radioHeight = params.radioHeight;
        }
        if (params.itemHeight !== undefined) {
            this.itemHeight = params.itemHeight;
        }
        if (params.selectedIndex !== undefined) {
            this.selectedIndex = params.selectedIndex;
        }
        if (params.contentBuilder !== undefined) {
            this.contentBuilder = params.contentBuilder;
        }
        if (params.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = params.fontColorWithTheme;
        }
        if (params.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = params.dividerColorWithTheme;
        }
        if (params.theme !== undefined) {
            this.theme = params.theme;
        }
        if (params.themeColorMode !== undefined) {
            this.themeColorMode = params.themeColorMode;
        }
        if (params.contentScroller !== undefined) {
            this.contentScroller = params.contentScroller;
        }
        if (params.fontSizeScale !== undefined) {
            this.fontSizeScale = params.fontSizeScale;
        }
        if (params.minContentHeight !== undefined) {
            this.minContentHeight = params.minContentHeight;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__selectedIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
        this.__minContentHeight.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__selectedIndex.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__dividerColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(ctr) {
        this.controller = ctr;
    }

    get selectedIndex() {
        return this.__selectedIndex.get();
    }

    set selectedIndex(newValue) {
        this.__selectedIndex.set(newValue);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(newValue) {
        this.__fontColorWithTheme.set(newValue);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(newValue) {
        this.__dividerColorWithTheme.set(newValue);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(newValue) {
        this.__minContentHeight.set(newValue);
    }

    buildContent(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.onDidScroll((xOffset, yOffset) => {
                let scrollHeight = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (yOffset > 0) {
                            this.contentScroller.scrollBy(0, scrollHeight);
                        } else if (yOffset < 0) {
                            this.contentScroller.scrollBy(0, 0 - scrollHeight);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.padding({
                            left: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level12'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            right: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level12'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            bottom: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level4'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            }
                        });
                        Row.width('100%');
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.content);
                        Text.fontSize(`${BODY_M}fp`);
                        Text.fontWeight(FontWeight.Regular);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            List.create();
            List.width('100%');
            List.clip(false);
            List.onFocus(() => {
                if (!this.contentScroller.isAtEnd()) {
                    this.contentScroller.scrollEdge(Edge.Top);
                    focusControl.requestFocus(String(FIRST_ITEM_INDEX));
                }
            });
            List.defaultFocus(this.buttons?.length === 0 ? true : false);
        }, List);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const item = _item;
                {
                    const itemCreation = (elmtId, isInitialRender) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
                        itemCreation2(elmtId, isInitialRender);
                        if (!isInitialRender) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const itemCreation2 = (elmtId, isInitialRender) => {
                        ListItem.create(deepRenderFunction, true);
                        ListItem.padding({
                            left: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level6'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            right: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level6'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            }
                        });
                        ListItem.onSizeChange((oldValue, newValue) => {
                            this.itemHeight = Number(newValue.height);
                        });
                    };
                    const deepRenderFunction = (elmtId, isInitialRender) => {
                        itemCreation(elmtId, isInitialRender);
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Column.create();
                            Column.borderRadius({
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.corner_radius_level8'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            });
                            Column.focusBox({
                                margin: { value: -2, unit: LengthUnit.VP }
                            });
                            Column.accessibilityText(getAccessibilityText(item.title, this.selectedIndex === index));
                            Column.onClick(() => {
                                this.selectedIndex = index;
                                item.action && item.action();
                                this.controller?.close();
                            });
                        }, Column);
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Button.createWithChild();
                            Button.type(ButtonType.Normal);
                            Button.borderRadius({
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.corner_radius_level8'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            });
                            Button.buttonStyle(ButtonStyleMode.TEXTUAL);
                            Button.padding({
                                left: {
                                    'id': -1,
                                    'type': 10002,
                                    params: ['sys.float.padding_level6'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                },
                                right: {
                                    'id': -1,
                                    'type': 10002,
                                    params: ['sys.float.padding_level6'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                }
                            });
                        }, Button);
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Row.create();
                            Row.constraintSize({ minHeight: LIST_MIN_HEIGHT });
                            Row.clip(false);
                            Row.padding({
                                top: {
                                    'id': -1,
                                    'type': 10002,
                                    params: ['sys.float.padding_level4'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                },
                                bottom: {
                                    'id': -1,
                                    'type': 10002,
                                    params: ['sys.float.padding_level4'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                }
                            });
                        }, Row);
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Text.create(item.title);
                            Text.fontSize(`${BODY_L}fp`);
                            Text.fontWeight(FontWeight.Medium);
                            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                            Text.layoutWeight(1);
                            Text.direction(i18n.isRTL(i18n.System.getSystemLanguage()) ? Direction.Rtl : Direction.Ltr);
                        }, Text);
                        Text.pop();
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === index);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(index));
                            Radio.focusable(false);
                            Radio.accessibilityLevel('no');
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = index;
                                if (index === FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (index === this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((oldValue, newValue) => {
                                this.radioHeight = Number(newValue.height);
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            If.create();
                            if (index < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        Divider.create();
                                        Divider.color(ObservedObject.GetRawObject(this.dividerColorWithTheme));
                                        Divider.padding({
                                            left: {
                                                'id': -1,
                                                'type': 10002,
                                                params: ['sys.float.padding_level6'],
                                                'bundleName': '__harDefaultBundleName__',
                                                'moduleName': '__harDefaultModuleName__'
                                            },
                                            right: {
                                                'id': -1,
                                                'type': 10002,
                                                params: ['sys.float.padding_level6'],
                                                'bundleName': '__harDefaultBundleName__',
                                                'moduleName': '__harDefaultModuleName__'
                                            }
                                        });
                                    }, Divider);
                                });
                            } else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                });
                            }
                        }, If);
                        If.pop();
                        Column.pop();
                        ListItem.pop();
                    };
                    this.observeComponentCreation2(itemCreation2, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(elmtId, this.radioContent, forEachItemGenFunction, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        primaryTitle: this.title,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        contentAreaPadding: this.contentPadding,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, elmtId, () => {
                    }, { page: 'library/src/main/ets/components/dialog.ets', line: 600, col: 5 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            controller: this.controller,
                            primaryTitle: this.title,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            buttons: this.buttons,
                            contentAreaPadding: this.contentPadding,
                            theme: this.theme,
                            themeColorMode: this.themeColorMode,
                            fontSizeScale: this.fontSizeScale,
                            minContentHeight: this.minContentHeight
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    aboutToAppear() {
        this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
        this.theme.colors.fontPrimary : {
                'id': -1,
                'type': 10001,
                params: ['sys.color.font_primary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        this.dividerColorWithTheme = this.theme?.colors?.compDivider ?
        this.theme.colors.compDivider : {
                'id': -1,
                'type': 10001,
                params: ['sys.color.comp_divider'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        this.initContentPadding();
        this.initButtons();
    }

    initContentPadding() {
        this.contentPadding = {
            left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level0'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }
        };
        if (!this.title && !this.confirm) {
            this.contentPadding = {
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level12'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level12'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            };
            return;
        }
        if (!this.title) {
            this.contentPadding = {
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level12'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            };
        } else if (!this.confirm) {
            this.contentPadding = {
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level12'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            };
        }
    }

    initButtons() {
        this.buttons = [];
        if (this.confirm) {
            this.buttons.push(this.confirm);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class ConfirmDialogContentLayout extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.textIndex = 0;
        this.checkboxIndex = 1;
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(params.minContentHeight, this, 'minContentHeight');
        this.updateTextAlign = (maxWidth) => {
        };
        this.dialogBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.textIndex !== undefined) {
            this.textIndex = params.textIndex;
        }
        if (params.checkboxIndex !== undefined) {
            this.checkboxIndex = params.checkboxIndex;
        }
        if (params.updateTextAlign !== undefined) {
            this.updateTextAlign = params.updateTextAlign;
        }
        if (params.dialogBuilder !== undefined) {
            this.dialogBuilder = params.dialogBuilder;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__minContentHeight.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(newValue) {
        this.__minContentHeight.set(newValue);
    }

    doNothingBuilder(parent = null) {
    }

    onPlaceChildren(selfLayoutInfo, children, constraint) {
        let currentX = 0;
        let currentY = 0;
        for (let index = 0; index < children.length; index++) {
            let child = children[index];
            child.layout({ x: currentX, y: currentY });
            currentY += child.measureResult.height;
        }
    }

    onMeasureSize(selfLayoutInfo, children, constraint) {
        let sizeResult = { width: Number(constraint.maxWidth), height: 0 };
        let childrenSize = 2;
        if (children.length < childrenSize) {
            return sizeResult;
        }
        this.updateTextAlign(sizeResult.width);
        let height = 0;
        let checkboxChild = children[this.checkboxIndex];
        let checkboxConstraint = {
            maxWidth: constraint.maxWidth,
            minHeight: CHECKBOX_CONTAINER_HEIGHT(),
            maxHeight: constraint.maxHeight
        };
        let checkBoxMeasureResult = checkboxChild.measure(checkboxConstraint);
        height += checkBoxMeasureResult.height;
        let textChild = children[this.textIndex];
        let textConstraint = {
            maxWidth: constraint.maxWidth,
            maxHeight: Number(constraint.maxHeight) - height
        };
        let textMeasureResult = textChild.measure(textConstraint);
        height += textMeasureResult.height;
        sizeResult.height = height;
        this.minContentHeight = Math.max(checkBoxMeasureResult.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT);
        return sizeResult;
    }

    initialRender() {
        this.dialogBuilder.bind(this)();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class ConfirmDialog extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.controller = undefined;
        this.title = '';
        this.content = '';
        this.checkTips = '';
        this.__isChecked = new ObservedPropertySimplePU(false, this, 'isChecked');
        this.primaryButton = null;
        this.secondaryButton = null;
        this.__fontColorWithTheme = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'fontColorWithTheme');
        this.theme = new CustomThemeImpl({});
        this.themeColorMode = ThemeColorMode.SYSTEM;
        this.onCheckedChange = undefined;
        this.contentScroller = new Scroller();
        this.buttons = undefined;
        this.__textAlign = new ObservedPropertySimplePU(TextAlign.Start, this, 'textAlign');
        this.marginOffset = 0;
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.__minContentHeight = new ObservedPropertySimplePU(MIN_CONTENT_HEIGHT, this, 'minContentHeight');
        this.textIndex = 0;
        this.checkboxIndex = 1;
        this.updateTextAlign = (maxWidth) => {
            if (this.content) {
                this.textAlign = getTextAlign(maxWidth, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.controller !== undefined) {
            this.controller = params.controller;
        }
        if (params.title !== undefined) {
            this.title = params.title;
        }
        if (params.content !== undefined) {
            this.content = params.content;
        }
        if (params.checkTips !== undefined) {
            this.checkTips = params.checkTips;
        }
        if (params.isChecked !== undefined) {
            this.isChecked = params.isChecked;
        }
        if (params.primaryButton !== undefined) {
            this.primaryButton = params.primaryButton;
        }
        if (params.secondaryButton !== undefined) {
            this.secondaryButton = params.secondaryButton;
        }
        if (params.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = params.fontColorWithTheme;
        }
        if (params.theme !== undefined) {
            this.theme = params.theme;
        }
        if (params.themeColorMode !== undefined) {
            this.themeColorMode = params.themeColorMode;
        }
        if (params.onCheckedChange !== undefined) {
            this.onCheckedChange = params.onCheckedChange;
        }
        if (params.contentScroller !== undefined) {
            this.contentScroller = params.contentScroller;
        }
        if (params.buttons !== undefined) {
            this.buttons = params.buttons;
        }
        if (params.textAlign !== undefined) {
            this.textAlign = params.textAlign;
        }
        if (params.marginOffset !== undefined) {
            this.marginOffset = params.marginOffset;
        }
        if (params.fontSizeScale !== undefined) {
            this.fontSizeScale = params.fontSizeScale;
        }
        if (params.minContentHeight !== undefined) {
            this.minContentHeight = params.minContentHeight;
        }
        if (params.textIndex !== undefined) {
            this.textIndex = params.textIndex;
        }
        if (params.checkboxIndex !== undefined) {
            this.checkboxIndex = params.checkboxIndex;
        }
        if (params.updateTextAlign !== undefined) {
            this.updateTextAlign = params.updateTextAlign;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__isChecked.purgeDependencyOnElmtId(rmElmtId);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__textAlign.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
        this.__minContentHeight.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__isChecked.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__textAlign.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(ctr) {
        this.controller = ctr;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(newValue) {
        this.__isChecked.set(newValue);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(newValue) {
        this.__fontColorWithTheme.set(newValue);
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(newValue) {
        this.__textAlign.set(newValue);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(newValue) {
        this.__minContentHeight.set(newValue);
    }

    textBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create(this.contentScroller);
            Scroll.fadingEdge(IS_FADEOUT_ENABLE(), { fadingEdgeLength: LengthMetrics.vp(FADEOUT_GRADIENT_WIDTH) });
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
        }, Scroll);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.margin({ end: LengthMetrics.vp(CONTENT_END_MARGIN()) });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.content);
            Text.focusable(true);
            Text.defaultFocus(!(this.primaryButton?.value || this.secondaryButton?.value));
            Text.focusBox({
                strokeWidth: LengthMetrics.px(0)
            });
            Text.fontSize(`${BODY_L}fp`);
            Text.fontWeight(CONTENT_FONT_WEIGHT());
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.textAlign(this.textAlign);
            Text.onKeyEvent((event) => {
                if (event) {
                    resolveKeyEvent(event, this.contentScroller);
                }
            });
            Text.width('100%');
        }, Text);
        Text.pop();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }

    checkBoxBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.accessibilityGroup(true);
            Row.accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.isChecked));
            Row.accessibilityDescription(this.isChecked ? {
                'id': -1,
                'type': 10003,
                params: ['sys.string.advanced_dialog_accessibility_cancel_checked_desc'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            } : {
                'id': -1,
                'type': 10003,
                params: ['sys.string.slider_accessibility_unselectedDesc'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Row.onClick(() => {
                this.isChecked = !this.isChecked;
                try {
                    let eventInfo = ({
                        type: 'announceForAccessibility',
                        bundleName: getContext()?.abilityInfo?.bundleName,
                        triggerAction: 'common',
                        textAnnouncedForAccessibility: this.isChecked ?
                        getContext().resourceManager.getStringSync(125833934) :
                        getContext().resourceManager.getStringSync(125833935)
                    });
                    accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                        console.info(`Accessibility send event`);
                    });
                } catch (exception) {
                    let code = exception.code;
                    let message = exception.message;
                    hilog.error(0x3900, 'Ace', `Faild to send event, cause, code: ${code}, message: ${message}`);
                }
            });
            Row.width('100%');
            Row.padding({ top: TIP_CHECKBOX_TOP_PADDING(), bottom: TIP_CHECKBOX_BOTTOM_PADDING() });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Checkbox.create({ name: '', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((checked) => {
                this.isChecked = checked;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(TIP_CHECKBOX_END_MARGIN()) });
        }, Checkbox);
        Checkbox.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.checkTips);
            Text.fontSize(`${SUBTITLE_SIZE()}fp`);
            Text.fontWeight(CONTENT_FONT_WEIGHT());
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.maxLines(CONTENT_MAX_LINES);
            Text.focusable(false);
            Text.layoutWeight(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
        }, Text);
        Text.pop();
        Row.pop();
    }

    buildContent(parent = null) {
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new ConfirmDialogContentLayout(this, {
                        minContentHeight: this.__minContentHeight, updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                ForEach.create();
                                const forEachItemGenFunction = _item => {
                                    const index = _item;
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        If.create();
                                        if (index === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.textBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else if (index === this.checkboxIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.checkBoxBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else {
                                            this.ifElseBranchUpdateFunction(2, () => {
                                            });
                                        }
                                    }, If);
                                    If.pop();
                                };
                                this.forEachUpdateFunction(elmtId, [this.textIndex, this.checkboxIndex],
                                    forEachItemGenFunction);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, elmtId, () => {
                    }, { page: 'library/src/main/ets/components/dialog.ets', line: 826, col: 5 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const index = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            If.create();
                                            if (index === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.textBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else if (index === this.checkboxIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.checkBoxBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else {
                                                this.ifElseBranchUpdateFunction(2, () => {
                                                });
                                            }
                                        }, If);
                                        If.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, [this.textIndex, this.checkboxIndex],
                                        forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'ConfirmDialogContentLayout' });
        }
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new CustomDialogContentComponent(this, {
                        primaryTitle: this.title,
                        controller: this.controller,
                        contentBuilder: () => {
                            this.buildContent();
                        },
                        minContentHeight: this.__minContentHeight,
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                    }, undefined, elmtId, () => {
                    }, { page: 'library/src/main/ets/components/dialog.ets', line: 842, col: 5 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            primaryTitle: this.title,
                            controller: this.controller,
                            contentBuilder: () => {
                                this.buildContent();
                            },
                            minContentHeight: this.minContentHeight,
                            buttons: this.buttons,
                            theme: this.theme,
                            themeColorMode: this.themeColorMode,
                            fontSizeScale: this.fontSizeScale
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    aboutToAppear() {
        this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
        this.theme.colors.fontPrimary : {
                'id': -1,
                'type': 10001,
                params: ['sys.color.font_primary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        this.initButtons();
        this.initMargin();
    }

    initMargin() {
        this.marginOffset = 0 - SCROLL_END_MARGIN();
    }

    initButtons() {
        if (!this.primaryButton && !this.secondaryButton) {
            return;
        }
        this.buttons = [];
        if (this.primaryButton) {
            this.buttons.push(this.primaryButton);
        }
        if (this.secondaryButton) {
            this.buttons.push(this.secondaryButton);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class AlertDialog extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.controller = undefined;
        this.primaryTitle = undefined;
        this.secondaryTitle = undefined;
        this.content = '';
        this.primaryButton = null;
        this.secondaryButton = null;
        this.buttons = undefined;
        this.__textAlign = new ObservedPropertySimplePU(TextAlign.Start, this, 'textAlign');
        this.contentScroller = new Scroller();
        this.__fontColorWithTheme = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'fontColorWithTheme');
        this.theme = new CustomThemeImpl({});
        this.themeColorMode = ThemeColorMode.SYSTEM;
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.__minContentHeight = new ObservedPropertySimplePU(MIN_CONTENT_HEIGHT, this, 'minContentHeight');
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.controller !== undefined) {
            this.controller = params.controller;
        }
        if (params.primaryTitle !== undefined) {
            this.primaryTitle = params.primaryTitle;
        }
        if (params.secondaryTitle !== undefined) {
            this.secondaryTitle = params.secondaryTitle;
        }
        if (params.content !== undefined) {
            this.content = params.content;
        }
        if (params.primaryButton !== undefined) {
            this.primaryButton = params.primaryButton;
        }
        if (params.secondaryButton !== undefined) {
            this.secondaryButton = params.secondaryButton;
        }
        if (params.buttons !== undefined) {
            this.buttons = params.buttons;
        }
        if (params.textAlign !== undefined) {
            this.textAlign = params.textAlign;
        }
        if (params.contentScroller !== undefined) {
            this.contentScroller = params.contentScroller;
        }
        if (params.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = params.fontColorWithTheme;
        }
        if (params.theme !== undefined) {
            this.theme = params.theme;
        }
        if (params.themeColorMode !== undefined) {
            this.themeColorMode = params.themeColorMode;
        }
        if (params.fontSizeScale !== undefined) {
            this.fontSizeScale = params.fontSizeScale;
        }
        if (params.minContentHeight !== undefined) {
            this.minContentHeight = params.minContentHeight;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__textAlign.purgeDependencyOnElmtId(rmElmtId);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
        this.__minContentHeight.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(ctr) {
        this.controller = ctr;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(newValue) {
        this.__textAlign.set(newValue);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(newValue) {
        this.__fontColorWithTheme.set(newValue);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(newValue) {
        this.__minContentHeight.set(newValue);
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new CustomDialogContentComponent(this, {
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        controller: this.controller,
                        contentBuilder: () => {
                            this.AlertDialogContentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, elmtId, () => {
                    }, { page: 'library/src/main/ets/components/dialog.ets', line: 900, col: 5 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            primaryTitle: this.primaryTitle,
                            secondaryTitle: this.secondaryTitle,
                            controller: this.controller,
                            contentBuilder: () => {
                                this.AlertDialogContentBuilder();
                            },
                            buttons: this.buttons,
                            theme: this.theme,
                            themeColorMode: this.themeColorMode,
                            fontSizeScale: this.fontSizeScale,
                            minContentHeight: this.minContentHeight
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    AlertDialogContentBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.margin({ end: LengthMetrics.vp(0 - SCROLL_BAR_OFFSET) });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create(this.contentScroller);
            Scroll.fadingEdge(IS_FADEOUT_ENABLE(), { fadingEdgeLength: LengthMetrics.vp(FADEOUT_GRADIENT_WIDTH) });
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.content);
            Text.focusable(true);
            Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
            Text.focusBox({
                strokeWidth: LengthMetrics.px(0)
            });
            Text.fontSize(`${BODY_L}fp`);
            Text.fontWeight(this.getFontWeight());
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.margin({ end: LengthMetrics.vp(SCROLL_BAR_OFFSET) });
            Text.width(`calc(100% - ${SCROLL_BAR_OFFSET}vp)`);
            Text.textAlign(this.textAlign);
            Text.onSizeChange((oldValue, newValue) => {
                this.updateTextAlign(Number(newValue.width));
            });
            Text.onKeyEvent((event) => {
                if (event) {
                    resolveKeyEvent(event, this.contentScroller);
                }
            });
        }, Text);
        Text.pop();
        Scroll.pop();
        Column.pop();
    }

    aboutToAppear() {
        this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
        this.theme.colors.fontPrimary : {
                'id': -1,
                'type': 10001,
                params: ['sys.color.font_primary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        this.initButtons();
    }

    updateTextAlign(maxWidth) {
        this.textAlign = getTextAlign(maxWidth, this.content, `${BODY_L * this.fontSizeScale}vp`);
    }

    initButtons() {
        if (!this.primaryButton && !this.secondaryButton) {
            return;
        }
        this.buttons = [];
        if (this.primaryButton) {
            this.buttons.push(this.primaryButton);
        }
        if (this.secondaryButton) {
            this.buttons.push(this.secondaryButton);
        }
    }

    getFontWeight() {
        if (this.primaryTitle || this.secondaryTitle) {
            return FontWeight.Regular;
        }
        return CONTENT_FONT_WEIGHT();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class CustomContentDialog extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.controller = undefined;
        this.primaryTitle = undefined;
        this.secondaryTitle = undefined;
        this.contentBuilder = undefined;
        this.contentAreaPadding = undefined;
        this.localizedContentAreaPadding = undefined;
        this.buttons = undefined;
        this.theme = new CustomThemeImpl({});
        this.themeColorMode = ThemeColorMode.SYSTEM;
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.__minContentHeight = new ObservedPropertySimplePU(MIN_CONTENT_HEIGHT, this, 'minContentHeight');
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.controller !== undefined) {
            this.controller = params.controller;
        }
        if (params.primaryTitle !== undefined) {
            this.primaryTitle = params.primaryTitle;
        }
        if (params.secondaryTitle !== undefined) {
            this.secondaryTitle = params.secondaryTitle;
        }
        if (params.contentBuilder !== undefined) {
            this.contentBuilder = params.contentBuilder;
        }
        if (params.contentAreaPadding !== undefined) {
            this.contentAreaPadding = params.contentAreaPadding;
        }
        if (params.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = params.localizedContentAreaPadding;
        }
        if (params.buttons !== undefined) {
            this.buttons = params.buttons;
        }
        if (params.theme !== undefined) {
            this.theme = params.theme;
        }
        if (params.themeColorMode !== undefined) {
            this.themeColorMode = params.themeColorMode;
        }
        if (params.fontSizeScale !== undefined) {
            this.fontSizeScale = params.fontSizeScale;
        }
        if (params.minContentHeight !== undefined) {
            this.minContentHeight = params.minContentHeight;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
        this.__minContentHeight.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(ctr) {
        this.controller = ctr;
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(newValue) {
        this.__minContentHeight.set(newValue);
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        contentAreaPadding: this.contentAreaPadding,
                        localizedContentAreaPadding: this.localizedContentAreaPadding,
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                        customStyle: false
                    }, undefined, elmtId, () => {
                    }, { page: 'library/src/main/ets/components/dialog.ets', line: 993, col: 5 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            controller: this.controller,
                            primaryTitle: this.primaryTitle,
                            secondaryTitle: this.secondaryTitle,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            contentAreaPadding: this.contentAreaPadding,
                            localizedContentAreaPadding: this.localizedContentAreaPadding,
                            buttons: this.buttons,
                            theme: this.theme,
                            themeColorMode: this.themeColorMode,
                            fontSizeScale: this.fontSizeScale,
                            minContentHeight: this.minContentHeight,
                            customStyle: false
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class CustomDialogControllerExtend extends CustomDialogController {
    constructor(value) {
        super(value);
        this.arg_ = value;
    }
}

class CustomDialogLayout extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__titleHeight = new SynchedPropertySimpleTwoWayPU(params.titleHeight, this, 'titleHeight');
        this.__buttonHeight = new SynchedPropertySimpleTwoWayPU(params.buttonHeight, this, 'buttonHeight');
        this.__titleMinHeight = new SynchedPropertyObjectTwoWayPU(params.titleMinHeight, this, 'titleMinHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.titleIndex = 0;
        this.contentIndex = 1;
        this.buttonIndex = 2;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.dialogBuilder !== undefined) {
            this.dialogBuilder = params.dialogBuilder;
        }
        if (params.titleIndex !== undefined) {
            this.titleIndex = params.titleIndex;
        }
        if (params.contentIndex !== undefined) {
            this.contentIndex = params.contentIndex;
        }
        if (params.buttonIndex !== undefined) {
            this.buttonIndex = params.buttonIndex;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__titleHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__titleMinHeight.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__titleMinHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(parent = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(newValue) {
        this.__titleHeight.set(newValue);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(newValue) {
        this.__buttonHeight.set(newValue);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(newValue) {
        this.__titleMinHeight.set(newValue);
    }

    onPlaceChildren(selfLayoutInfo, children, constraint) {
        let currentX = 0;
        let currentY = 0;
        for (let index = 0; index < children.length; index++) {
            let child = children[index];
            child.layout({ x: currentX, y: currentY });
            currentY += child.measureResult.height;
        }
    }

    onMeasureSize(selfLayoutInfo, children, constraint) {
        let sizeResult = { width: Number(constraint.maxWidth), height: 0 };
        let childrenSize = 3;
        if (children.length < childrenSize) {
            return sizeResult;
        }
        let height = 0;
        let titleChild = children[this.titleIndex];
        let titleConstraint = {
            maxWidth: constraint.maxWidth,
            minHeight: this.titleMinHeight,
            maxHeight: constraint.maxHeight
        };
        let titleMeasureResult = titleChild.measure(titleConstraint);
        this.titleHeight = titleMeasureResult.height;
        height += this.titleHeight;
        let buttonChild = children[this.buttonIndex];
        let buttonMeasureResult = buttonChild.measure(constraint);
        this.buttonHeight = buttonMeasureResult.height;
        height += this.buttonHeight;
        let contentChild = children[this.contentIndex];
        let contentConstraint = {
            maxWidth: constraint.maxWidth,
            maxHeight: Number(constraint.maxHeight) - height
        };
        let contentMeasureResult = contentChild.measure(contentConstraint);
        height += contentMeasureResult.height;
        sizeResult.height = height;
        return sizeResult;
    }

    initialRender() {
        this.dialogBuilder.bind(this)();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class CustomDialogContentComponent extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.controller = undefined;
        this.primaryTitle = undefined;
        this.secondaryTitle = undefined;
        this.localizedContentAreaPadding = undefined;
        this.contentBuilder = this.defaultContentBuilder;
        this.buttons = undefined;
        this.contentAreaPadding = undefined;
        this.keyIndex = 0;
        this.theme = new CustomThemeImpl({});
        this.themeColorMode = ThemeColorMode.SYSTEM;
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(params.minContentHeight, this, 'minContentHeight');
        this.__titleHeight = new ObservedPropertySimplePU(0, this, 'titleHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
        this.__contentMaxHeight = new ObservedPropertyObjectPU('100%', this, 'contentMaxHeight');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(params.fontSizeScale, this, 'fontSizeScale');
        this.__customStyle = new ObservedPropertySimplePU(undefined, this, 'customStyle');
        this.__buttonMaxFontSize = new ObservedPropertyObjectPU(`${BODY_L}fp`, this, 'buttonMaxFontSize');
        this.__buttonMinFontSize = new ObservedPropertyObjectPU(9, this, 'buttonMinFontSize');
        this.__primaryTitleMaxFontSize = new ObservedPropertyObjectPU(`${TITLE_S}fp`, this, 'primaryTitleMaxFontSize');
        this.__primaryTitleMinFontSize = new ObservedPropertyObjectPU(`${BODY_L}fp`, this, 'primaryTitleMinFontSize');
        this.__secondaryTitleMaxFontSize =
            new ObservedPropertyObjectPU(`${SUBTITLE_SIZE()}fp`, this, 'secondaryTitleMaxFontSize');
        this.__secondaryTitleMinFontSize =
            new ObservedPropertyObjectPU(`${BODY_S}fp`, this, 'secondaryTitleMinFontSize');
        this.__primaryTitleFontColorWithTheme = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'primaryTitleFontColorWithTheme');
        this.__secondaryTitleFontColorWithTheme = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'secondaryTitleFontColorWithTheme');
        this.__titleTextAlign = new ObservedPropertySimplePU(TextAlign.Center, this, 'titleTextAlign');
        this.__isButtonVertical = new ObservedPropertySimplePU(false, this, 'isButtonVertical');
        this.__titleMinHeight = new ObservedPropertyObjectPU(0, this, 'titleMinHeight');
        this.isFollowingSystemFontScale = false;
        this.appMaxFontScale = 3.2;
        this.titleIndex = 0;
        this.contentIndex = 1;
        this.buttonIndex = 2;
        this.isHasDefaultFocus = false;
        this.isAllFocusFalse = false;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.controller !== undefined) {
            this.controller = params.controller;
        }
        if (params.primaryTitle !== undefined) {
            this.primaryTitle = params.primaryTitle;
        }
        if (params.secondaryTitle !== undefined) {
            this.secondaryTitle = params.secondaryTitle;
        }
        if (params.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = params.localizedContentAreaPadding;
        }
        if (params.contentBuilder !== undefined) {
            this.contentBuilder = params.contentBuilder;
        }
        if (params.buttons !== undefined) {
            this.buttons = params.buttons;
        }
        if (params.contentAreaPadding !== undefined) {
            this.contentAreaPadding = params.contentAreaPadding;
        }
        if (params.keyIndex !== undefined) {
            this.keyIndex = params.keyIndex;
        }
        if (params.theme !== undefined) {
            this.theme = params.theme;
        }
        if (params.themeColorMode !== undefined) {
            this.themeColorMode = params.themeColorMode;
        }
        if (params.titleHeight !== undefined) {
            this.titleHeight = params.titleHeight;
        }
        if (params.buttonHeight !== undefined) {
            this.buttonHeight = params.buttonHeight;
        }
        if (params.contentMaxHeight !== undefined) {
            this.contentMaxHeight = params.contentMaxHeight;
        }
        if (params.customStyle !== undefined) {
            this.customStyle = params.customStyle;
        }
        if (params.buttonMaxFontSize !== undefined) {
            this.buttonMaxFontSize = params.buttonMaxFontSize;
        }
        if (params.buttonMinFontSize !== undefined) {
            this.buttonMinFontSize = params.buttonMinFontSize;
        }
        if (params.primaryTitleMaxFontSize !== undefined) {
            this.primaryTitleMaxFontSize = params.primaryTitleMaxFontSize;
        }
        if (params.primaryTitleMinFontSize !== undefined) {
            this.primaryTitleMinFontSize = params.primaryTitleMinFontSize;
        }
        if (params.secondaryTitleMaxFontSize !== undefined) {
            this.secondaryTitleMaxFontSize = params.secondaryTitleMaxFontSize;
        }
        if (params.secondaryTitleMinFontSize !== undefined) {
            this.secondaryTitleMinFontSize = params.secondaryTitleMinFontSize;
        }
        if (params.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = params.primaryTitleFontColorWithTheme;
        }
        if (params.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = params.secondaryTitleFontColorWithTheme;
        }
        if (params.titleTextAlign !== undefined) {
            this.titleTextAlign = params.titleTextAlign;
        }
        if (params.isButtonVertical !== undefined) {
            this.isButtonVertical = params.isButtonVertical;
        }
        if (params.titleMinHeight !== undefined) {
            this.titleMinHeight = params.titleMinHeight;
        }
        if (params.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
        }
        if (params.appMaxFontScale !== undefined) {
            this.appMaxFontScale = params.appMaxFontScale;
        }
        if (params.titleIndex !== undefined) {
            this.titleIndex = params.titleIndex;
        }
        if (params.contentIndex !== undefined) {
            this.contentIndex = params.contentIndex;
        }
        if (params.buttonIndex !== undefined) {
            this.buttonIndex = params.buttonIndex;
        }
        if (params.isHasDefaultFocus !== undefined) {
            this.isHasDefaultFocus = params.isHasDefaultFocus;
        }
        if (params.isAllFocusFalse !== undefined) {
            this.isAllFocusFalse = params.isAllFocusFalse;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__minContentHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__titleHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__contentMaxHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
        this.__customStyle.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(rmElmtId);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(rmElmtId);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(rmElmtId);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(rmElmtId);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(rmElmtId);
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__titleTextAlign.purgeDependencyOnElmtId(rmElmtId);
        this.__isButtonVertical.purgeDependencyOnElmtId(rmElmtId);
        this.__titleMinHeight.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__contentMaxHeight.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__customStyle.aboutToBeDeleted();
        this.__buttonMaxFontSize.aboutToBeDeleted();
        this.__buttonMinFontSize.aboutToBeDeleted();
        this.__primaryTitleMaxFontSize.aboutToBeDeleted();
        this.__primaryTitleMinFontSize.aboutToBeDeleted();
        this.__secondaryTitleMaxFontSize.aboutToBeDeleted();
        this.__secondaryTitleMinFontSize.aboutToBeDeleted();
        this.__primaryTitleFontColorWithTheme.aboutToBeDeleted();
        this.__secondaryTitleFontColorWithTheme.aboutToBeDeleted();
        this.__titleTextAlign.aboutToBeDeleted();
        this.__isButtonVertical.aboutToBeDeleted();
        this.__titleMinHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(newValue) {
        this.__minContentHeight.set(newValue);
    }

    defaultContentBuilder(parent = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(newValue) {
        this.__titleHeight.set(newValue);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(newValue) {
        this.__buttonHeight.set(newValue);
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(newValue) {
        this.__contentMaxHeight.set(newValue);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }

    get customStyle() {
        return this.__customStyle.get();
    }

    set customStyle(newValue) {
        this.__customStyle.set(newValue);
    }

    get buttonMaxFontSize() {
        return this.__buttonMaxFontSize.get();
    }

    set buttonMaxFontSize(newValue) {
        this.__buttonMaxFontSize.set(newValue);
    }

    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }

    set buttonMinFontSize(newValue) {
        this.__buttonMinFontSize.set(newValue);
    }

    get primaryTitleMaxFontSize() {
        return this.__primaryTitleMaxFontSize.get();
    }

    set primaryTitleMaxFontSize(newValue) {
        this.__primaryTitleMaxFontSize.set(newValue);
    }

    get primaryTitleMinFontSize() {
        return this.__primaryTitleMinFontSize.get();
    }

    set primaryTitleMinFontSize(newValue) {
        this.__primaryTitleMinFontSize.set(newValue);
    }

    get secondaryTitleMaxFontSize() {
        return this.__secondaryTitleMaxFontSize.get();
    }

    set secondaryTitleMaxFontSize(newValue) {
        this.__secondaryTitleMaxFontSize.set(newValue);
    }

    get secondaryTitleMinFontSize() {
        return this.__secondaryTitleMinFontSize.get();
    }

    set secondaryTitleMinFontSize(newValue) {
        this.__secondaryTitleMinFontSize.set(newValue);
    }

    get primaryTitleFontColorWithTheme() {
        return this.__primaryTitleFontColorWithTheme.get();
    }

    set primaryTitleFontColorWithTheme(newValue) {
        this.__primaryTitleFontColorWithTheme.set(newValue);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(newValue) {
        this.__secondaryTitleFontColorWithTheme.set(newValue);
    }

    get titleTextAlign() {
        return this.__titleTextAlign.get();
    }

    set titleTextAlign(newValue) {
        this.__titleTextAlign.set(newValue);
    }

    get isButtonVertical() {
        return this.__isButtonVertical.get();
    }

    set isButtonVertical(newValue) {
        this.__isButtonVertical.set(newValue);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(newValue) {
        this.__titleMinHeight.set(newValue);
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            WithTheme.create({ theme: this.theme, colorMode: this.themeColorMode });
        }, WithTheme);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create();
            Scroll.edgeEffect(EdgeEffect.None, { alwaysEnabled: false });
            Scroll.backgroundColor(this.themeColorMode === ThemeColorMode.SYSTEM || undefined ?
            Color.Transparent : {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.comp_background_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
        }, Scroll);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.constraintSize({ maxHeight: this.contentMaxHeight });
            Column.backgroundBlurStyle(this.customStyle ?
            BlurStyle.Thick : BlurStyle.NONE, undefined, { disableSystemAdaptation: true });
            Column.borderRadius(this.customStyle ? {
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_corner_radius_dialog'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            } : 0);
            Column.margin(this.customStyle ? {
                start: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_dialog_margin_start'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }),
                end: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_dialog_margin_end'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }),
                bottom: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_dialog_margin_bottom'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }),
            } : { left: 0, right: 0, bottom: 0 });
            Column.backgroundColor(this.customStyle ? {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_dialog_bg'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            } : Color.Transparent);
        }, Column);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new CustomDialogLayout(this, {
                        buttonHeight: this.__buttonHeight,
                        titleHeight: this.__titleHeight,
                        titleMinHeight: this.__titleMinHeight,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                ForEach.create();
                                const forEachItemGenFunction = _item => {
                                    const index = _item;
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        If.create();
                                        if (index === this.titleIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.titleBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else if (index === this.contentIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                    Column.create();
                                                    Column.padding(this.getContentPadding());
                                                }, Column);
                                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.contentBuilder.bind(this)();
                                                WithTheme.pop();
                                                Column.pop();
                                            });
                                        } else {
                                            this.ifElseBranchUpdateFunction(2, () => {
                                                this.buildButton.bind(this)();
                                            });
                                        }
                                    }, If);
                                    If.pop();
                                };
                                this.forEachUpdateFunction(elmtId,
                                    [this.titleIndex, this.contentIndex, this.buttonIndex], forEachItemGenFunction);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, elmtId, () => {
                    }, { page: 'library/src/main/ets/components/dialog.ets', line: 1133, col: 11 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            buttonHeight: this.buttonHeight,
                            titleHeight: this.titleHeight,
                            titleMinHeight: this.titleMinHeight,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const index = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            If.create();
                                            if (index === this.titleIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.titleBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else if (index === this.contentIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Column.create();
                                                        Column.padding(this.getContentPadding());
                                                    }, Column);
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.contentBuilder.bind(this)();
                                                    WithTheme.pop();
                                                    Column.pop();
                                                });
                                            } else {
                                                this.ifElseBranchUpdateFunction(2, () => {
                                                    this.buildButton.bind(this)();
                                                });
                                            }
                                        }, If);
                                        If.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId,
                                        [this.titleIndex, this.contentIndex, this.buttonIndex], forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'CustomDialogLayout' });
        }
        Column.pop();
        Scroll.pop();
        WithTheme.pop();
    }

    onMeasureSize(selfLayoutInfo, children, constraint) {
        let sizeResult = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
        let maxWidth = Number(constraint.maxWidth);
        let maxHeight = Number(constraint.maxHeight);
        this.fontSizeScale = this.updateFontScale();
        this.updateFontSize();
        this.isButtonVertical = this.isVerticalAlignButton(maxWidth - BUTTON_HORIZONTAL_MARGIN() * 2);
        this.titleMinHeight = this.getTitleAreaMinHeight();
        let height = 0;
        children.forEach((child) => {
            this.contentMaxHeight = '100%';
            let measureResult = child.measure(constraint);
            if (maxHeight - this.buttonHeight - this.titleHeight < this.minContentHeight) {
                this.contentMaxHeight = MAX_CONTENT_HEIGHT;
                measureResult = child.measure(constraint);
            }
            height += measureResult.height;
        });
        sizeResult.height = height;
        sizeResult.width = maxWidth;
        return sizeResult;
    }

    aboutToAppear() {
        try {
            let uiContext = this.getUIContext();
            this.isFollowingSystemFontScale = uiContext?.isFollowingSystemFontScale();
            this.appMaxFontScale = uiContext?.getMaxFontScale();
        } catch (err) {
            let code = err?.code;
            let message = err?.message;
            hilog.error(0x3900, 'Ace', `Faild to dialog getUIContext, code: ${code}, message: ${message}`);
        }
        this.fontSizeScale = this.updateFontScale();
        if (this.controller && this.customStyle === undefined) {
            let customController = this.controller;
            if (customController.arg_ && customController.arg_.customStyle &&
                customController.arg_.customStyle === true) {
                this.customStyle = true;
            }
        }
        if (this.customStyle === undefined) {
            this.customStyle = false;
        }
        this.primaryTitleFontColorWithTheme = this.theme?.colors?.fontPrimary ?
        this.theme.colors.fontPrimary : {
                'id': -1,
                'type': 10001,
                params: ['sys.color.font_primary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        this.secondaryTitleFontColorWithTheme = this.theme?.colors?.fontSecondary ?
        this.theme.colors.fontSecondary : {
                'id': -1,
                'type': 10001,
                params: ['sys.color.font_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        this.initTitleTextAlign();
        this.setDefaultFocusState(this.buttons);
    }

    updateFontSize() {
        if (this.fontSizeScale > MAX_FONT_SCALE) {
            this.buttonMaxFontSize = BUTTON_MAX_FONT_SIZE() * MAX_FONT_SCALE + 'vp';
            this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE() * MAX_FONT_SCALE + 'vp';
        } else {
            this.buttonMaxFontSize = BUTTON_MAX_FONT_SIZE() + 'fp';
            this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE() + 'fp';
        }
    }

    updateFontScale() {
        try {
            let uiContext = this.getUIContext();
            let systemFontScale = uiContext.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(systemFontScale, this.appMaxFontScale);
        } catch (exception) {
            let code = exception.code;
            let message = exception.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
            return 1;
        }
    }

    /**
     * get dialog content padding
     *
     * @returns content padding
     */
    getContentPadding() {
        if (this.localizedContentAreaPadding) {
            return this.localizedContentAreaPadding;
        }
        if (this.contentAreaPadding) {
            return this.contentAreaPadding;
        }
        if ((this.primaryTitle || this.secondaryTitle) && this.buttons && this.buttons.length > 0) {
            return {
                top: 0,
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_content_default_padding'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: 0,
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_content_default_padding'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            };
        } else if (this.primaryTitle || this.secondaryTitle) {
            return {
                top: 0,
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_content_default_padding'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_content_default_padding'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_content_default_padding'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            };
        } else if (this.buttons && this.buttons.length > 0) {
            return {
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_content_default_padding'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_content_default_padding'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: 0,
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_content_default_padding'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            };
        } else {
            return {
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_content_default_padding'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_content_default_padding'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_content_default_padding'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_content_default_padding'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            };
        }
    }

    titleBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.primaryTitle);
            Text.fontWeight(TITLE_FONT_WEIGHT());
            Text.fontColor(ObservedObject.GetRawObject(this.primaryTitleFontColorWithTheme));
            Text.textAlign(this.titleTextAlign);
            Text.maxFontSize(ObservedObject.GetRawObject(this.primaryTitleMaxFontSize));
            Text.minFontSize(ObservedObject.GetRawObject(this.primaryTitleMinFontSize));
            Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
            Text.maxLines(TITLE_MAX_LINES);
            Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.width('100%');
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.height({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.padding_level1'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                    }, Row);
                    Row.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.secondaryTitle);
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor(ObservedObject.GetRawObject(this.secondaryTitleFontColorWithTheme));
            Text.textAlign(this.titleTextAlign);
            Text.maxFontSize(ObservedObject.GetRawObject(this.secondaryTitleMaxFontSize));
            Text.minFontSize(ObservedObject.GetRawObject(this.secondaryTitleMinFontSize));
            Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
            Text.maxLines(TITLE_MAX_LINES);
            Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.width('100%');
        }, Text);
        Text.pop();
        Row.pop();
        Column.pop();
    }

    /**
     * get title area padding
     *
     * @returns padding
     */
    getTitleAreaPadding() {
        if (this.primaryTitle || this.secondaryTitle) {
            return {
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_title_padding_top'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_title_padding_right'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_title_padding_left'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_title_padding_bottom'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            };
        }
        return {
            top: 0,
            right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.alert_title_padding_right'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.alert_title_padding_left'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            bottom: 0,
        };
    }

    /**
     * get tile TextAlign
     * @returns TextAlign
     */
    initTitleTextAlign() {
        let textAlign = ALERT_TITLE_ALIGNMENT();
        if (textAlign === TextAlign.Start) {
            this.titleTextAlign = TextAlign.Start;
        } else if (textAlign === TextAlign.Center) {
            this.titleTextAlign = TextAlign.Center;
        } else if (textAlign === TextAlign.End) {
            this.titleTextAlign = TextAlign.End;
        } else if (textAlign === TextAlign.JUSTIFY) {
            this.titleTextAlign = TextAlign.JUSTIFY;
        } else {
            this.titleTextAlign = TextAlign.Center;
        }
    }

    /**
     * get title area min height
     *
     * @returns min height
     */
    getTitleAreaMinHeight() {
        if (this.secondaryTitle) {
            return {
                'id': -1,
                'type': 10002,
                params: ['sys.float.alert_title_secondary_height'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else if (this.primaryTitle) {
            return {
                'id': -1,
                'type': 10002,
                params: ['sys.float.alert_title_primary_height'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else {
            return 0;
        }
    }

    /**
     * set state of button focus
     */
    setDefaultFocusState(buttonList) {
        if (!buttonList) {
            return;
        }
        let falseNum = 0;
        buttonList.forEach((button) => {
            // 遍历查询按钮中存在是否存在默认按钮
            if (button.defaultFocus) {
                this.isHasDefaultFocus = true;
            }
            if (button.defaultFocus === false) {
                falseNum++;
            }
        });
        // 所有按钮defaultFocus都设置为false
        if (falseNum === buttonList.length) {
            this.isAllFocusFalse = true;
        }
    }

    ButtonBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
            Column.padding(this.getOperationAreaPadding());
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.isButtonVertical) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.buildVerticalAlignButtons.bind(this)();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.buildHorizontalAlignButtons.bind(this)();
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
        Column.pop();
    }

    isSetCustomButtonTheme() {
        // is set fadeout style: now only on TV
        if (IS_FADEOUT_ENABLE()) {
            // has set button background color prop
            if (this.theme?.colors?.compBackgroundTertiary || this.theme?.colors?.backgroundEmphasize) {
                return true;
            }
            // has set button font color prop
            if (this.theme?.colors?.fontEmphasize || this.theme?.colors?.fontOnPrimary || this.theme?.colors?.warning) {
                return true;
            }
            return false;
        }
        return true;
    }

    buildButton(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.isSetCustomButtonTheme()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        WithTheme.create({ theme: this.theme, colorMode: this.themeColorMode });
                    }, WithTheme);
                    this.ButtonBuilder.bind(this)();
                    WithTheme.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.ButtonBuilder.bind(this)();
                });
            }
        }, If);
        If.pop();
    }

    /**
     * get operation area padding
     *
     * @returns padding
     */
    getOperationAreaPadding() {
        if (this.isButtonVertical) {
            return {
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_button_top_padding'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_right_padding_vertical'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_left_padding_vertical'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_button_bottom_padding_vertical'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            };
        }
        return {
            top: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.alert_button_top_padding'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.alert_right_padding_horizontal'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.alert_left_padding_horizontal'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.alert_button_bottom_padding_horizontal'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        };
    }

    buildSingleButton(buttonOptions, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.isNewPropertiesHighPriority(buttonOptions)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel(buttonOptions.value);
                        __Button__setButtonProperties(buttonOptions, this.isHasDefaultFocus, this.isAllFocusFalse,
                            this.controller);
                        Button.role(buttonOptions.role ?? ButtonRole.NORMAL);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            overflow: IS_FADEOUT_ENABLE() ? TextOverflow.MARQUEE : TextOverflow.Ellipsis,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (buttonOptions.background !== undefined && buttonOptions.fontColor !== undefined) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel(buttonOptions.value);
                        __Button__setButtonProperties(buttonOptions, this.isHasDefaultFocus, this.isAllFocusFalse,
                            this.controller);
                        Button.backgroundColor(buttonOptions.background);
                        Button.fontColor(buttonOptions.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            overflow: IS_FADEOUT_ENABLE() ? TextOverflow.MARQUEE : TextOverflow.Ellipsis,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (buttonOptions.background !== undefined) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel(buttonOptions.value);
                        __Button__setButtonProperties(buttonOptions, this.isHasDefaultFocus, this.isAllFocusFalse,
                            this.controller);
                        Button.backgroundColor(buttonOptions.background);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            overflow: IS_FADEOUT_ENABLE() ? TextOverflow.MARQUEE : TextOverflow.Ellipsis,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Button.createWithLabel(buttonOptions.value);
                        __Button__setButtonProperties(buttonOptions, this.isHasDefaultFocus, this.isAllFocusFalse,
                            this.controller);
                        Button.fontColor(buttonOptions.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            overflow: IS_FADEOUT_ENABLE() ? TextOverflow.MARQUEE : TextOverflow.Ellipsis,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            }
        }, If);
        If.pop();
    }

    buildHorizontalAlignButtons(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[0]);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.width(BUTTON_HORIZONTAL_SPACE() * 2);
                                    Row.justifyContent(FlexAlign.Center);
                                }, Row);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Divider.create();
                                    Divider.width({
                                        'id': -1,
                                        'type': 10002,
                                        params: ['sys.float.alert_divider_width'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
                                    Divider.height({
                                        'id': -1,
                                        'type': 10002,
                                        params: ['sys.float.alert_divider_height'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
                                    Divider.color(this.getDividerColor());
                                    Divider.vertical(true);
                                }, Divider);
                                Row.pop();
                                this.buildSingleButton.bind(this)(this.buttons[HORIZON_BUTTON_MAX_COUNT - 1]);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Row.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    buildVerticalAlignButtons(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.buttons) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        ForEach.create();
                        const forEachItemGenFunction = (_item, index) => {
                            const item = _item;
                            this.buildButtonWithDivider.bind(this)(this.buttons?.length === HORIZON_BUTTON_MAX_COUNT ?
                                HORIZON_BUTTON_MAX_COUNT - index - 1 : index);
                        };
                        this.forEachUpdateFunction(elmtId, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT),
                            forEachItemGenFunction, (item) => item.value.toString(), true, false);
                    }, ForEach);
                    ForEach.pop();
                    Column.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    /**
     * get divider color
     *
     * @returns divider color
     */
    getDividerColor() {
        if (!this.buttons || this.buttons.length === 0 || !DIALOG_DIVIDER_SHOW()) {
            return Color.Transparent;
        }
        if (this.buttons[0].buttonStyle === ButtonStyleMode.TEXTUAL || this.buttons[0].buttonStyle === undefined) {
            if (this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === ButtonStyleMode.TEXTUAL ||
                this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === undefined) {
                return {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.alert_divider_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                };
            }
        }
        return Color.Transparent;
    }

    /**
     * is button buttonStyle and role properties high priority
     *
     * @param buttonOptions button properties
     * @returns check result
     */
    isNewPropertiesHighPriority(buttonOptions) {
        if (buttonOptions.role === ButtonRole.ERROR) {
            return true;
        }
        if (buttonOptions.buttonStyle !== undefined &&
            buttonOptions.buttonStyle !== ALERT_BUTTON_STYLE()) {
            return true;
        }
        if (buttonOptions.background === undefined && buttonOptions.fontColor === undefined) {
            return true;
        }
        return false;
    }

    buildButtonWithDivider(index, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.buttons && this.buttons[index]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[index]);
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if ((this.buttons.length === HORIZON_BUTTON_MAX_COUNT ? HORIZON_BUTTON_MAX_COUNT - index - 1 :
                            index) <
                            Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Row.create();
                                    Row.height({
                                        'id': -1,
                                        'type': 10002,
                                        params: ['sys.float.alert_button_vertical_space'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
                                }, Row);
                                Row.pop();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
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
    }

    isVerticalAlignButton(width) {
        if (this.buttons) {
            if (this.buttons.length === 1) {
                return false;
            }
            if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
                return true;
            }
            let isVertical = false;
            let maxButtonTextSize = vp2px(width / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN() -
            BUTTON_HORIZONTAL_SPACE() - 2 * BUTTON_HORIZONTAL_PADDING);
            this.buttons.forEach((button) => {
                try {
                    let contentSize = measure.measureTextSize({
                        textContent: button.value,
                        fontSize: this.buttonMaxFontSize
                    });
                    if (Number(contentSize?.width) > maxButtonTextSize) {
                        isVertical = true;
                    }
                } catch (err) {
                    let code = (err).code;
                    let message = (err).message;
                    hilog.error(0x3900, 'Ace', `Faild to dialog isVerticalAlignButton measureTextSize,cause,
                    code: ${code}, message: ${message}`);
                }
            });
            return isVertical;
        }
        return false;
    }

    rerender() {
        this.updateDirtyElements();
    }
}

function __Button__setButtonProperties(buttonOptions, isHasDefaultFocus, isAllFocusFalse, controller) {
    Button.onKeyEvent((event) => {
        if (!event) {
            return;
        }
        if ((event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER) &&
            event.type === KeyType.Down) {
            if (buttonOptions.action) {
                buttonOptions.action();
            }
            controller?.close();
            event.stopPropagation();
        }
    });
    Button.onClick(() => {
        if (buttonOptions.action) {
            buttonOptions.action();
        }
        controller?.close();
    });
    Button.defaultFocus(isDefaultFocus(buttonOptions, isHasDefaultFocus, isAllFocusFalse));
    Button.buttonStyle(buttonOptions.buttonStyle ??
        (buttonOptions.role === ButtonRole.ERROR ? ERROR_BUTTON_STYLE() : ALERT_BUTTON_STYLE()));
    Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
    Button.type(ButtonType.ROUNDED_RECTANGLE);
}

/**
 * is button set default focus
 *
 * @param singleButton button options
 * @param isHasDefaultFocus is button list has default focus button
 * @param isAllFocusFalse is all button in button list default focus false
 * @returns boolean
 */
function isDefaultFocus(singleButton, isHasDefaultFocus, isAllFocusFalse) {
    try {
        // 当前按钮为默认按钮
        if (singleButton.defaultFocus) {
            return true;
        }
        let isDefaultFocus = false;
        if (isHasDefaultFocus || isAllFocusFalse) {
            isDefaultFocus = false; // 存在默认按钮或者所有按钮的defaultFocus都为false
        } else {
            isDefaultFocus = true; // 默认第一个按钮获焦
        }
        return isDefaultFocus;
    } catch (error) {
        let code = error.code;
        let message = error.message;
        hilog.error(0x3900, 'Ace', `get defaultFocus exist error, code: ${code}, message: ${message}`);
        return true;
    }
}

/**
 * get resource size
 *
 * @param resourceId resource id
 * @param defaultValue default value
 * @returns resource size
 */
function getNumberByResourceId(resourceId, defaultValue, allowZero) {
    try {
        let sourceValue = resourceManager.getSystemResourceManager().getNumber(resourceId);
        if (sourceValue > 0 || allowZero) {
            return sourceValue;
        } else {
            return defaultValue;
        }
    } catch (error) {
        let code = error.code;
        let message = error.message;
        hilog.error(0x3900, 'Ace',
            `CustomContentDialog getNumberByResourceId error, code: ${code}, message: ${message}`);
        return defaultValue;
    }
}

/**
 * lazy init
 *
 * @param initializer  lazy initializer
 * @returns lazy init result
 */
function lazyInit(initializer) {
    let value = null;
    return () => {
        if (value === null) {
            value = initializer();
        }
        return value;
    };
}

/**
 * get LengthMetrics size
 *
 * @param resource resource
 * @param defaultValue default value
 * @param isAllowZero allow value zero
 * @returns LengthMetrics size
 */
function getLengthMetricsByResource(resource, defaultValue, isAllowZero) {
    if (!resource) {
        hilog.error(0x3900, 'Ace', 'CustomContentDialog getLengthMetricsByResource error');
        return defaultValue;
    }
    try {
        let sourceValue = LengthMetrics.resource(resource).value;
        if (sourceValue === 0) {
            return isAllowZero ? sourceValue : defaultValue;
        }
        return sourceValue;
    } catch (error) {
        let code = error.code;
        let message = error.message;
        hilog.error(0x3900, 'Ace',
            `CustomContentDialog getLengthMetricsByResource error, code: ${code}, message: ${message}`);
        return defaultValue;
    }
}

/**
 * get string value
 *
 * @param resourceId Resource id
 * @returns resource value
 */
function getString(resourceId) {
    let res = '';
    if (resourceId <= 0) {
        hilog.error(0x3900, 'Ace', 'CustomContentDialog getString error');
        return res;
    }
    try {
        res = getContext().resourceManager.getStringSync(resourceId);
    } catch (error) {
        let code = error.code;
        let message = error.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getString error, code: ${code}, message: ${message}`);
    }
    return res;
}

/**
 * 获取SelectDialog无障碍文本
 *
 * @param resource 资源
 * @param selected select state
 * @returns string
 */
function getAccessibilityText(resource, selected) {
    try {
        let selectText = getContext().resourceManager.getStringSync(125833934);
        let resourceString = '';
        if (typeof resource === 'string') {
            resourceString = resource;
        } else {
            resourceString = getContext().resourceManager.getStringSync(resource);
        }
        return selected ? `${selectText},${resourceString}` : resourceString;
    } catch (error) {
        let code = error.code;
        let message = error.message;
        hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${code}, message: ${message}`);
        return '';
    }
}

/**
 * get Text Align
 *
 * @param maxWidth maxWidth
 * @param content textContent
 * @param fontSize fontSize
 * @returns textAlign
 */
function getTextAlign(maxWidth, content, fontSize) {
    let contentSize = measure.measureTextSize({
        textContent: content,
        fontSize: fontSize,
        constraintWidth: maxWidth,
    });
    let oneLineSize = measure.measureTextSize({
        textContent: content,
        fontSize: fontSize,
    });
    if (getTextHeight(contentSize) <= getTextHeight(oneLineSize)) {
        return TextAlign.Center;
    }
    return TextAlign.Start;
}

/**
 * get text height
 *
 * @param textSize textSize
 * @returns text height
 */
function getTextHeight(textSize) {
    if (textSize && textSize.height !== null && textSize.height !== undefined) {
        return Number(textSize.height);
    }
    return 0;
}

/**
 * resolve content area keyEvent
 *
 * @param event keyEvent
 * @param controller the controller of content area
 * @returns undefined
 */
function resolveKeyEvent(event, controller) {
    if (event.type === IGNORE_KEY_EVENT_TYPE) {
        return;
    }
    if (event.keyCode === KEYCODE_UP) {
        controller.scrollPage({ next: false });
        event.stopPropagation();
    } else if (event.keyCode === KEYCODE_DOWN) {
        if (controller.isAtEnd()) {
            return;
        } else {
            controller.scrollPage({ next: true });
            event.stopPropagation();
        }
    }
}

/**
 * 获取checkTips无障碍文本
 *
 * @param resource 资源
 * @param selected select state
 * @returns string
 */
function getCheckTipsAccessibilityText(resource, selected) {
    try {
        // 'sys.string.slider_accessibility_selected'
        let selectText = getContext().resourceManager.getStringSync(125833934);
        // 'sys.string.slider_accessibility_unselected'
        let unselectText = getContext().resourceManager.getStringSync(125833935);
        // 'sys.string.advanced_dialog_accessibility_checkbox'
        let checkBoxText = getContext().resourceManager.getStringSync(125834354);
        let resourceString = '';
        if (typeof resource === 'string') {
            resourceString = resource;
        } else {
            resourceString = getContext().resourceManager.getStringSync(resource);
        }
        return selected ? `${selectText},${resourceString},${checkBoxText}` :
            `${unselectText},${resourceString},${checkBoxText}`;
    } catch (error) {
        let code = error.code;
        let message = error.message;
        hilog.error(0x3900, 'Ace', `getCheckTipsAccessibilityText error, code: ${code}, message: ${message}`);
        return '';
    }
}

export class LoadingDialog extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.controller = undefined;
        this.content = '';
        this.__fontColorWithTheme = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'fontColorWithTheme');
        this.__loadingProgressIconColorWithTheme = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.icon_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'loadingProgressIconColorWithTheme');
        this.theme = new CustomThemeImpl({});
        this.themeColorMode = ThemeColorMode.SYSTEM;
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.__minContentHeight = new ObservedPropertySimplePU(MIN_CONTENT_HEIGHT, this, 'minContentHeight');
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.controller !== undefined) {
            this.controller = params.controller;
        }
        if (params.content !== undefined) {
            this.content = params.content;
        }
        if (params.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = params.fontColorWithTheme;
        }
        if (params.loadingProgressIconColorWithTheme !== undefined) {
            this.loadingProgressIconColorWithTheme = params.loadingProgressIconColorWithTheme;
        }
        if (params.theme !== undefined) {
            this.theme = params.theme;
        }
        if (params.themeColorMode !== undefined) {
            this.themeColorMode = params.themeColorMode;
        }
        if (params.fontSizeScale !== undefined) {
            this.fontSizeScale = params.fontSizeScale;
        }
        if (params.minContentHeight !== undefined) {
            this.minContentHeight = params.minContentHeight;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__loadingProgressIconColorWithTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
        this.__minContentHeight.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__loadingProgressIconColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(ctr) {
        this.controller = ctr;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(newValue) {
        this.__fontColorWithTheme.set(newValue);
    }

    get loadingProgressIconColorWithTheme() {
        return this.__loadingProgressIconColorWithTheme.get();
    }

    set loadingProgressIconColorWithTheme(newValue) {
        this.__loadingProgressIconColorWithTheme.set(newValue);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(newValue) {
        this.__minContentHeight.set(newValue);
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, elmtId, () => {
                    }, { page: 'library/src/main/ets/components/dialog.ets', line: 1900, col: 7 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            controller: this.controller,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            theme: this.theme,
                            themeColorMode: this.themeColorMode,
                            fontSizeScale: this.fontSizeScale,
                            minContentHeight: this.minContentHeight
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        Column.pop();
    }

    contentBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.content);
            Text.fontSize(`${BODY_L}fp`);
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.layoutWeight(LOADING_TEXT_LAYOUT_WEIGHT);
            Text.maxLines(this.fontSizeScale > MAX_FONT_SCALE ? LOADING_MAX_LINES_BIG_FONT : LOADING_MAX_LINES);
            Text.focusable(true);
            Text.defaultFocus(true);
            Text.focusBox({
                strokeWidth: LengthMetrics.px(0)
            });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            LoadingProgress.create();
            LoadingProgress.color(ObservedObject.GetRawObject(this.loadingProgressIconColorWithTheme));
            LoadingProgress.width(LOADING_PROGRESS_WIDTH);
            LoadingProgress.height(LOADING_PROGRESS_HEIGHT);
            LoadingProgress.margin({ start: LengthMetrics.vp(LOADING_TEXT_MARGIN_LEFT) });
        }, LoadingProgress);
        Row.pop();
        Column.pop();
    }

    aboutToAppear() {
        this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
        this.theme.colors.fontPrimary : {
                'id': -1,
                'type': 10001,
                params: ['sys.color.font_primary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        this.loadingProgressIconColorWithTheme = this.theme?.colors?.iconSecondary ?
        this.theme.colors.iconSecondary : {
                'id': -1,
                'type': 10001,
                params: ['sys.color.icon_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class PopoverDialog extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__visible = new SynchedPropertySimpleTwoWayPU(params.visible, this, 'visible');
        this.__popover = new SynchedPropertyObjectOneWayPU(params.popover, this, 'popover');
        this.targetBuilder = undefined;
        this.__dialogWidth = new ObservedPropertyObjectPU(this.popover?.width, this, 'dialogWidth');
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.targetBuilder !== undefined) {
            this.targetBuilder = params.targetBuilder;
        }
        if (params.dialogWidth !== undefined) {
            this.dialogWidth = params.dialogWidth;
        }
    }

    updateStateVars(params) {
        this.__popover.reset(params.popover);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__visible.purgeDependencyOnElmtId(rmElmtId);
        this.__popover.purgeDependencyOnElmtId(rmElmtId);
        this.__dialogWidth.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__visible.aboutToBeDeleted();
        this.__popover.aboutToBeDeleted();
        this.__dialogWidth.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get visible() {
        return this.__visible.get();
    }

    set visible(newValue) {
        this.__visible.set(newValue);
    }

    get popover() {
        return this.__popover.get();
    }

    set popover(newValue) {
        this.__popover.set(newValue);
    }

    get dialogWidth() {
        return this.__dialogWidth.get();
    }

    set dialogWidth(newValue) {
        this.__dialogWidth.set(newValue);
    }

    emptyBuilder(parent = null) {
    }

    aboutToAppear() {
        if (this.targetBuilder === undefined || this.targetBuilder === null) {
            this.targetBuilder = this.emptyBuilder;
        }
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.onClick(() => {
                try {
                    let screenSize = display.getDefaultDisplaySync();
                    let screenWidth = px2vp(screenSize.width);
                    if (screenWidth - BUTTON_HORIZONTAL_MARGIN() - BUTTON_HORIZONTAL_MARGIN() > MAX_DIALOG_WIDTH) {
                        this.popover.width = this.popover?.width ?? MAX_DIALOG_WIDTH;
                    } else {
                        this.popover.width = this.dialogWidth;
                    }
                    this.visible = !this.visible;
                } catch (error) {
                    let code = error.code;
                    let message = error.message;
                    hilog.error(0x3900, 'Ace', `dialog popup error, code: ${code}, message: ${message}`);
                }
            });
            Column.bindPopup(this.visible, {
                builder: this.popover?.builder,
                placement: this.popover?.placement ?? Placement.Bottom,
                popupColor: this.popover?.popupColor,
                enableArrow: this.popover?.enableArrow ?? true,
                autoCancel: this.popover?.autoCancel,
                onStateChange: this.popover?.onStateChange ?? ((e) => {
                    if (!e.isVisible) {
                        this.visible = false;
                    }
                }),
                arrowOffset: this.popover?.arrowOffset,
                showInSubWindow: this.popover?.showInSubWindow,
                mask: this.popover?.mask,
                targetSpace: this.popover?.targetSpace,
                offset: this.popover?.offset,
                width: this.popover?.width,
                arrowPointPosition: this.popover?.arrowPointPosition,
                arrowWidth: this.popover?.arrowWidth,
                arrowHeight: this.popover?.arrowHeight,
                radius: this.popover?.radius ?? {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.corner_radius_level16'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                shadow: this.popover?.shadow ?? ShadowStyle.OUTER_DEFAULT_MD,
                backgroundBlurStyle: this.popover?.backgroundBlurStyle ?? BlurStyle.COMPONENT_ULTRA_THICK,
                focusable: this.popover?.focusable,
                transition: this.popover?.transition,
                onWillDismiss: this.popover?.onWillDismiss
            });
        }, Column);
        this.targetBuilder.bind(this)();
        Column.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    TipsDialog,
    ConfirmDialog,
    SelectDialog,
    AlertDialog,
    LoadingDialog,
    CustomContentDialog,
    PopoverDialog
};