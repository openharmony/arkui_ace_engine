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

const display = requireNapi('display');
const hilog = requireNapi('hilog');
const measure = requireNapi('measure');
const resourceManager = requireNapi('resourceManager');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const accessibility = requireNapi('accessibility');
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

class CustomThemeImpl {
    constructor(e32) {
        this.colors = e32;
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
const MAX_DIALOG_WIDTH = getNumberByResourceId(125831042, 400);
const BUTTON_HORIZONTAL_MARGIN = getNumberByResourceId(125831054, 16);
const BUTTON_HORIZONTAL_PADDING = getNumberByResourceId(125830927, 16);
const BUTTON_HORIZONTAL_SPACE = getNumberByResourceId(125831051, 8);
const BODY_L = getNumberByResourceId(125830970, 16);
const BODY_M = getNumberByResourceId(125830971, 14);
const BODY_S = getNumberByResourceId(125830972, 12);
const TITLE_S = getNumberByResourceId(125830966, 20);
const PADDING_LEVEL_8 = getNumberByResourceId(125830927, 16);
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
const IS_FADEOUT_ENABLE = lazyInit(() => {
    return getString(125831120) === FADEOUT_ENABLE;
});
const TITLE_FONT_WEIGHT = lazyInit(() => {
    let fontWeight = FontWeight[getString(125834679) || 'Bold'];
    return fontWeight;
});
const CONTENT_FONT_WEIGHT = lazyInit(() => {
    let fontWeight = FontWeight[getString(125834682) || 'Medium'];
    return fontWeight;
});
const SCROLL_BAR_OFFSET = 20;
export class TipsDialog extends ViewPU {
    constructor(x31, y31, z31, a32 = -1, b32 = undefined, c32) {
        super(x31, z31, a32, c32);
        if (typeof b32 === 'function') {
            this.paramsGenerator_ = b32;
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
        this.updateTextAlign = (d32) => {
            if (this.content) {
                this.textAlignment = getTextAlign(d32, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.appMaxFontScale = 3.2;
        this.setInitiallyProvidedValue(y31);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(w31) {
        if (w31.controller !== undefined) {
            this.controller = w31.controller;
        }
        if (w31.imageRes !== undefined) {
            this.imageRes = w31.imageRes;
        }
        if (w31.imageSize !== undefined) {
            this.imageSize = w31.imageSize;
        }
        if (w31.title !== undefined) {
            this.title = w31.title;
        }
        if (w31.content !== undefined) {
            this.content = w31.content;
        }
        if (w31.checkAction !== undefined) {
            this.checkAction = w31.checkAction;
        }
        if (w31.onCheckedChange !== undefined) {
            this.onCheckedChange = w31.onCheckedChange;
        }
        if (w31.checkTips !== undefined) {
            this.checkTips = w31.checkTips;
        }
        if (w31.isChecked !== undefined) {
            this.isChecked = w31.isChecked;
        }
        if (w31.primaryButton !== undefined) {
            this.primaryButton = w31.primaryButton;
        }
        if (w31.secondaryButton !== undefined) {
            this.secondaryButton = w31.secondaryButton;
        }
        if (w31.buttons !== undefined) {
            this.buttons = w31.buttons;
        }
        if (w31.textAlignment !== undefined) {
            this.textAlignment = w31.textAlignment;
        }
        if (w31.marginOffset !== undefined) {
            this.marginOffset = w31.marginOffset;
        }
        if (w31.contentScroller !== undefined) {
            this.contentScroller = w31.contentScroller;
        }
        if (w31.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = w31.fontColorWithTheme;
        }
        if (w31.theme !== undefined) {
            this.theme = w31.theme;
        }
        if (w31.themeColorMode !== undefined) {
            this.themeColorMode = w31.themeColorMode;
        }
        if (w31.fontSizeScale !== undefined) {
            this.fontSizeScale = w31.fontSizeScale;
        }
        if (w31.minContentHeight !== undefined) {
            this.minContentHeight = w31.minContentHeight;
        }
        if (w31.updateTextAlign !== undefined) {
            this.updateTextAlign = w31.updateTextAlign;
        }
        if (w31.imageIndex !== undefined) {
            this.imageIndex = w31.imageIndex;
        }
        if (w31.textIndex !== undefined) {
            this.textIndex = w31.textIndex;
        }
        if (w31.checkBoxIndex !== undefined) {
            this.checkBoxIndex = w31.checkBoxIndex;
        }
        if (w31.appMaxFontScale !== undefined) {
            this.appMaxFontScale = w31.appMaxFontScale;
        }
    }

    updateStateVars(v31) {
    }

    purgeVariableDependenciesOnElmtId(u31) {
        this.__imageSize.purgeDependencyOnElmtId(u31);
        this.__isChecked.purgeDependencyOnElmtId(u31);
        this.__textAlignment.purgeDependencyOnElmtId(u31);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(u31);
        this.__fontSizeScale.purgeDependencyOnElmtId(u31);
        this.__minContentHeight.purgeDependencyOnElmtId(u31);
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
    setController(t31) {
        this.controller = t31;
    }
    get imageSize() {
        return this.__imageSize.get();
    }
    set imageSize(s31) {
        this.__imageSize.set(s31);
    }
    get isChecked() {
        return this.__isChecked.get();
    }
    set isChecked(r31) {
        this.__isChecked.set(r31);
    }
    get textAlignment() {
        return this.__textAlignment.get();
    }
    set textAlignment(q31) {
        this.__textAlignment.set(q31);
    }
    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }
    set fontColorWithTheme(p31) {
        this.__fontColorWithTheme.set(p31);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(o31) {
        this.__fontSizeScale.set(o31);
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(n31) {
        this.__minContentHeight.set(n31);
    }
    initialRender() {
        this.observeComponentCreation2((l31, m31) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((h31, i31) => {
                if (i31) {
                    let j31 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, h31, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 125, col: 5 });
                    ViewPU.create(j31);
                    let k31 = () => {
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
                    j31.paramsGenerator_ = k31;
                } else {
                    this.updateStateVarsOfChildByElmtId(h31, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }
    contentBuilder(c30 = null) {
        {
            this.observeComponentCreation2((d30, e30) => {
                if (e30) {
                    let f30 = new TipsDialogContentLayout(this, {
                        title: this.title,
                        content: this.content,
                        checkTips: this.checkTips,
                        minContentHeight: this.__minContentHeight,
                        updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((u30, v30) => {
                                ForEach.create();
                                const w30 = x30 => {
                                    const y30 = x30;
                                    this.observeComponentCreation2((z30, a31) => {
                                        If.create();
                                        if (y30 === this.imageIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.imagePart.bind(this)();
                                            });
                                        } else if (y30 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((f31, g31) => {
                                                    Column.create();
                                                    Column.padding({ top: TIP_TEXT_TOP_PADDING() });
                                                }, Column);
                                                this.observeComponentCreation2((d31, e31) => {
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
                                                this.observeComponentCreation2((b31, c31) => {
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
                                this.forEachUpdateFunction(u30, [this.imageIndex, this.textIndex,
                                    this.checkBoxIndex], w30);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, d30, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 140, col: 5 });
                    ViewPU.create(f30);
                    let g30 = () => {
                        return {
                            title: this.title,
                            content: this.content,
                            checkTips: this.checkTips,
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((h30, i30) => {
                                    ForEach.create();
                                    const j30 = k30 => {
                                        const l30 = k30;
                                        this.observeComponentCreation2((m30, n30) => {
                                            If.create();
                                            if (l30 === this.imageIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.imagePart.bind(this)();
                                                });
                                            } else if (l30 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((s30, t30) => {
                                                        Column.create();
                                                        Column.padding({ top: TIP_TEXT_TOP_PADDING() });
                                                    }, Column);
                                                    this.observeComponentCreation2((q30, r30) => {
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
                                                    this.observeComponentCreation2((o30, p30) => {
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
                                    this.forEachUpdateFunction(h30,
                                        [this.imageIndex, this.textIndex, this.checkBoxIndex], j30);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    f30.paramsGenerator_ = g30;
                } else {
                    this.updateStateVarsOfChildByElmtId(d30, {});
                }
            }, { name: 'TipsDialogContentLayout' });
        }
    }
    checkBoxPart(r29 = null) {
        this.observeComponentCreation2((z29, a30) => {
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
                let b30 = ({
                    type: 'announceForAccessibility',
                    bundleName: getContext()?.abilityInfo?.bundleName,
                    triggerAction: 'click',
                    textAnnouncedForAccessibility: this.isChecked ?
                    getContext().resourceManager.getStringSync(125833934) :
                    getContext().resourceManager.getStringSync(125833935)
                });
                accessibility.sendAccessibilityEvent(b30).then(() => {
                    console.info(`Accessibility send event`);
                });
            });
            Row.padding({ top: TIP_CHECKBOX_TOP_PADDING(), bottom: TIP_CHECKBOX_BOTTOM_PADDING() });
            Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT() });
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((s29, t29) => {
            If.create();
            if (this.checkTips !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w29, x29) => {
                        Checkbox.create({ name: '', group: 'checkboxGroup' });
                        Checkbox.select(this.isChecked);
                        Checkbox.onChange((y29) => {
                            this.isChecked = y29;
                            if (this.checkAction) {
                                this.checkAction(y29);
                            }
                            if (this.onCheckedChange) {
                                this.onCheckedChange(y29);
                            }
                        });
                        Checkbox.margin({
                            start: LengthMetrics.vp(0),
                            end: LengthMetrics.vp(TIP_CHECKBOX_END_MARGIN())
                        });
                    }, Checkbox);
                    Checkbox.pop();
                    this.observeComponentCreation2((u29, v29) => {
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
    imagePart(m29 = null) {
        this.observeComponentCreation2((p29, q29) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((n29, o29) => {
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
    textPart(u28 = null) {
        this.observeComponentCreation2((k29, l29) => {
            Scroll.create(this.contentScroller);
            Scroll.fadingEdge(IS_FADEOUT_ENABLE(), { fadingEdgeLength: LengthMetrics.vp(FADEOUT_GRADIENT_WIDTH) });
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });            
            Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
        }, Scroll);
        this.observeComponentCreation2((i29, j29) => {
            Column.create();
            Column.margin({ end: LengthMetrics.vp(CONTENT_END_MARGIN()) });
        }, Column);
        this.observeComponentCreation2((c29, d29) => {
            If.create();
            if (this.title !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g29, h29) => {
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
                    this.observeComponentCreation2((e29, f29) => {
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
        this.observeComponentCreation2((v28, w28) => {
            If.create();
            if (this.content !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a29, b29) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((x28, y28) => {
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
                        Text.onKeyEvent((z28) => {
                            if (z28) {
                                resolveKeyEvent(z28, this.contentScroller);
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
        let t28 = this.getUIContext();
        this.appMaxFontScale = t28.getMaxFontScale();
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
    constructor(m28, n28, o28, p28 = -1, q28 = undefined, r28) {
        super(m28, o28, p28, r28);
        if (typeof q28 === 'function') {
            this.paramsGenerator_ = q28;
        }
        this.title = null;
        this.content = null;
        this.checkTips = null;
        this.updateTextAlign = (s28) => {
        };
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(n28.minContentHeight, this, 'minContentHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.childrenSize = 3;
        this.setInitiallyProvidedValue(n28);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l28) {
        if (l28.title !== undefined) {
            this.title = l28.title;
        }
        if (l28.content !== undefined) {
            this.content = l28.content;
        }
        if (l28.checkTips !== undefined) {
            this.checkTips = l28.checkTips;
        }
        if (l28.updateTextAlign !== undefined) {
            this.updateTextAlign = l28.updateTextAlign;
        }
        if (l28.dialogBuilder !== undefined) {
            this.dialogBuilder = l28.dialogBuilder;
        }
        if (l28.imageIndex !== undefined) {
            this.imageIndex = l28.imageIndex;
        }
        if (l28.textIndex !== undefined) {
            this.textIndex = l28.textIndex;
        }
        if (l28.checkBoxIndex !== undefined) {
            this.checkBoxIndex = l28.checkBoxIndex;
        }
        if (l28.childrenSize !== undefined) {
            this.childrenSize = l28.childrenSize;
        }
    }
    updateStateVars(k28) {
    }
    purgeVariableDependenciesOnElmtId(j28) {
        this.__minContentHeight.purgeDependencyOnElmtId(j28);
    }
    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    doNothingBuilder(i28 = null) {
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(h28) {
        this.__minContentHeight.set(h28);
    }
    onPlaceChildren(a28, b28, c28) {
        let d28 = 0;
        let e28 = 0;
        for (let f28 = 0; f28 < b28.length; f28++) {
            let g28 = b28[f28];
            g28.layout({ x: d28, y: e28 });
            e28 += g28.measureResult.height;
        }
    }
    onMeasureSize(i27, j27, k27) {
        let l27 = { width: Number(k27.maxWidth), height: 0 };
        if (j27.length < this.childrenSize) {
            return l27;
        }
        let m27 = 0;
        let n27 = 0;
        if (this.checkTips !== null) {
            let x27 = j27[this.checkBoxIndex];
            let y27 = {
                maxWidth: k27.maxWidth,
                minHeight: CHECKBOX_CONTAINER_HEIGHT(),
                maxHeight: k27.maxHeight
            };
            let z27 = x27.measure(y27);
            n27 = z27.height;
            m27 += n27;
        }
        let o27 = j27[this.imageIndex];
        let p27 = 0;
        if (this.title !== null || this.content !== null) {
            p27 = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
        }
        let q27 = Number(k27.maxHeight) - n27 - p27;
        let r27 = {
            maxWidth: k27.maxWidth,
            maxHeight: q27
        };
        let s27 = o27.measure(r27);
        m27 += s27.height;
        if (this.title !== null || this.content !== null) {
            let t27 = j27[this.textIndex];
            this.updateTextAlign(l27.width);
            let u27 = Number(k27.maxHeight) - s27.height - n27;
            let v27 = {
                maxWidth: k27.maxWidth,
                maxHeight: Math.max(u27, TEXT_MIN_HEIGHT)
            };
            let w27 = t27.measure(v27);
            m27 += w27.height;
        }
        l27.height = m27;
        this.minContentHeight = Math.max(n27 + s27.height + p27, MIN_CONTENT_HEIGHT);
        return l27;
    }
    initialRender() {
        this.dialogBuilder.bind(this)();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class SelectDialog extends ViewPU {
    constructor(c27, d27, e27, f27 = -1, g27 = undefined, h27) {
        super(c27, e27, f27, h27);
        if (typeof g27 === 'function') {
            this.paramsGenerator_ = g27;
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
        this.setInitiallyProvidedValue(d27);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(b27) {
        if (b27.controller !== undefined) {
            this.controller = b27.controller;
        }
        if (b27.title !== undefined) {
            this.title = b27.title;
        }
        if (b27.content !== undefined) {
            this.content = b27.content;
        }
        if (b27.confirm !== undefined) {
            this.confirm = b27.confirm;
        }
        if (b27.radioContent !== undefined) {
            this.radioContent = b27.radioContent;
        }
        if (b27.buttons !== undefined) {
            this.buttons = b27.buttons;
        }
        if (b27.contentPadding !== undefined) {
            this.contentPadding = b27.contentPadding;
        }
        if (b27.isFocus !== undefined) {
            this.isFocus = b27.isFocus;
        }
        if (b27.currentFocusIndex !== undefined) {
            this.currentFocusIndex = b27.currentFocusIndex;
        }
        if (b27.radioHeight !== undefined) {
            this.radioHeight = b27.radioHeight;
        }
        if (b27.itemHeight !== undefined) {
            this.itemHeight = b27.itemHeight;
        }
        if (b27.selectedIndex !== undefined) {
            this.selectedIndex = b27.selectedIndex;
        }
        if (b27.contentBuilder !== undefined) {
            this.contentBuilder = b27.contentBuilder;
        }
        if (b27.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = b27.fontColorWithTheme;
        }
        if (b27.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = b27.dividerColorWithTheme;
        }
        if (b27.theme !== undefined) {
            this.theme = b27.theme;
        }
        if (b27.themeColorMode !== undefined) {
            this.themeColorMode = b27.themeColorMode;
        }
        if (b27.contentScroller !== undefined) {
            this.contentScroller = b27.contentScroller;
        }
        if (b27.fontSizeScale !== undefined) {
            this.fontSizeScale = b27.fontSizeScale;
        }
        if (b27.minContentHeight !== undefined) {
            this.minContentHeight = b27.minContentHeight;
        }
    }
    updateStateVars(a27) {
    }
    purgeVariableDependenciesOnElmtId(z26) {
        this.__selectedIndex.purgeDependencyOnElmtId(z26);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(z26);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(z26);
        this.__fontSizeScale.purgeDependencyOnElmtId(z26);
        this.__minContentHeight.purgeDependencyOnElmtId(z26);
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
    setController(y26) {
        this.controller = y26;
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(x26) {
        this.__selectedIndex.set(x26);
    }
    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }
    set fontColorWithTheme(w26) {
        this.__fontColorWithTheme.set(w26);
    }
    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }
    set dividerColorWithTheme(v26) {
        this.__dividerColorWithTheme.set(v26);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(u26) {
        this.__fontSizeScale.set(u26);
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(t26) {
        this.__minContentHeight.set(t26);
    }
    buildContent(w24 = null) {
        this.observeComponentCreation2((o26, p26) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
            Scroll.onDidScroll((q26, r26) => {
                let s26 = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (r26 > 0) {
                            this.contentScroller.scrollBy(0, s26);
                        } else if (r26 < 0) {
                            this.contentScroller.scrollBy(0, 0 - s26);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((m26, n26) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((g26, h26) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k26, l26) => {
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
                    this.observeComponentCreation2((i26, j26) => {
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
        this.observeComponentCreation2((e26, f26) => {
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
        this.observeComponentCreation2((x24, y24) => {
            ForEach.create();
            const z24 = (a25, b25) => {
                const c25 = a25;
                {
                    const d25 = (c26, d26) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(c26);
                        e25(c26, d26);
                        if (!d26) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const e25 = (y25, z25) => {
                        ListItem.create(f25, true);
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
                        ListItem.onSizeChange((a26, b26) => {
                            this.itemHeight = Number(b26.height);
                        });
                    };
                    const f25 = (g25, h25) => {
                        d25(g25, h25);
                        this.observeComponentCreation2((w25, x25) => {
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
                            Column.accessibilityText(getAccessibilityText(c25.title, this.selectedIndex === b25));
                            Column.onClick(() => {
                                this.selectedIndex = b25;
                                c25.action && c25.action();
                                this.controller?.close();
                            });
                        }, Column);
                        this.observeComponentCreation2((u25, v25) => {
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
                        this.observeComponentCreation2((s25, t25) => {
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
                        this.observeComponentCreation2((q25, r25) => {
                            Text.create(c25.title);
                            Text.fontSize(`${BODY_L}fp`);
                            Text.fontWeight(FontWeight.Medium);
                            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                            Text.layoutWeight(1);
                        }, Text);
                        Text.pop();
                        this.observeComponentCreation2((m25, n25) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === b25);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(b25));
                            Radio.focusable(false);
                            Radio.accessibilityLevel('no');
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = b25;
                                if (b25 === FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (b25 === this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((o25, p25) => {
                                this.radioHeight = Number(p25.height);
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((i25, j25) => {
                            If.create();
                            if (b25 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((k25, l25) => {
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
                    this.observeComponentCreation2(e25, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(x24, this.radioContent, z24, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }
    initialRender() {
        this.observeComponentCreation2((u24, v24) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((q24, r24) => {
                if (r24) {
                    let s24 = new CustomDialogContentComponent(this, {
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
                    }, undefined, q24, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 535, col: 5 });
                    ViewPU.create(s24);
                    let t24 = () => {
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
                    s24.paramsGenerator_ = t24;
                } else {
                    this.updateStateVarsOfChildByElmtId(q24, {});
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
    constructor(j24, k24, l24, m24 = -1, n24 = undefined, o24) {
        super(j24, l24, m24, o24);
        if (typeof n24 === 'function') {
            this.paramsGenerator_ = n24;
        }
        this.textIndex = 0;
        this.checkboxIndex = 1;
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(k24.minContentHeight, this, 'minContentHeight');
        this.updateTextAlign = (p24) => {
        };
        this.dialogBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(k24);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(i24) {
        if (i24.textIndex !== undefined) {
            this.textIndex = i24.textIndex;
        }
        if (i24.checkboxIndex !== undefined) {
            this.checkboxIndex = i24.checkboxIndex;
        }
        if (i24.updateTextAlign !== undefined) {
            this.updateTextAlign = i24.updateTextAlign;
        }
        if (i24.dialogBuilder !== undefined) {
            this.dialogBuilder = i24.dialogBuilder;
        }
    }
    updateStateVars(h24) {
    }
    purgeVariableDependenciesOnElmtId(g24) {
        this.__minContentHeight.purgeDependencyOnElmtId(g24);
    }
    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(f24) {
        this.__minContentHeight.set(f24);
    }
    doNothingBuilder(e24 = null) {
    }
    onPlaceChildren(x23, y23, z23) {
        let a24 = 0;
        let b24 = 0;
        for (let c24 = 0; c24 < y23.length; c24++) {
            let d24 = y23[c24];
            d24.layout({ x: a24, y: b24 });
            b24 += d24.measureResult.height;
        }
    }
    onMeasureSize(l23, m23, n23) {
        let o23 = { width: Number(n23.maxWidth), height: 0 };
        let p23 = 2;
        if (m23.length < p23) {
            return o23;
        }
        this.updateTextAlign(o23.width);
        let q23 = 0;
        let r23 = m23[this.checkboxIndex];
        let s23 = {
            maxWidth: n23.maxWidth,
            minHeight: CHECKBOX_CONTAINER_HEIGHT(),
            maxHeight: n23.maxHeight
        };
        let t23 = r23.measure(s23);
        q23 += t23.height;
        let u23 = m23[this.textIndex];
        let v23 = {
            maxWidth: n23.maxWidth,
            maxHeight: Number(n23.maxHeight) - q23
        };
        let w23 = u23.measure(v23);
        q23 += w23.height;
        o23.height = q23;
        this.minContentHeight = Math.max(t23.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT);
        return o23;
    }
    initialRender() {
        this.dialogBuilder.bind(this)();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class ConfirmDialog extends ViewPU {
    constructor(e23, f23, g23, h23 = -1, i23 = undefined, j23) {
        super(e23, g23, h23, j23);
        if (typeof i23 === 'function') {
            this.paramsGenerator_ = i23;
        }
        this.controller = undefined;
        this.title = '';
        this.content = '';
        this.checkTips = '';
        this.__isChecked = new ObservedPropertySimplePU(false, this, 'isChecked');
        this.primaryButton = { value: "" };
        this.secondaryButton = { value: "" };
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
        this.updateTextAlign = (k23) => {
            if (this.content) {
                this.textAlign = getTextAlign(k23, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.setInitiallyProvidedValue(f23);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(d23) {
        if (d23.controller !== undefined) {
            this.controller = d23.controller;
        }
        if (d23.title !== undefined) {
            this.title = d23.title;
        }
        if (d23.content !== undefined) {
            this.content = d23.content;
        }
        if (d23.checkTips !== undefined) {
            this.checkTips = d23.checkTips;
        }
        if (d23.isChecked !== undefined) {
            this.isChecked = d23.isChecked;
        }
        if (d23.primaryButton !== undefined) {
            this.primaryButton = d23.primaryButton;
        }
        if (d23.secondaryButton !== undefined) {
            this.secondaryButton = d23.secondaryButton;
        }
        if (d23.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = d23.fontColorWithTheme;
        }
        if (d23.theme !== undefined) {
            this.theme = d23.theme;
        }
        if (d23.themeColorMode !== undefined) {
            this.themeColorMode = d23.themeColorMode;
        }
        if (d23.onCheckedChange !== undefined) {
            this.onCheckedChange = d23.onCheckedChange;
        }
        if (d23.contentScroller !== undefined) {
            this.contentScroller = d23.contentScroller;
        }
        if (d23.buttons !== undefined) {
            this.buttons = d23.buttons;
        }
        if (d23.textAlign !== undefined) {
            this.textAlign = d23.textAlign;
        }
        if (d23.marginOffset !== undefined) {
            this.marginOffset = d23.marginOffset;
        }
        if (d23.fontSizeScale !== undefined) {
            this.fontSizeScale = d23.fontSizeScale;
        }
        if (d23.minContentHeight !== undefined) {
            this.minContentHeight = d23.minContentHeight;
        }
        if (d23.textIndex !== undefined) {
            this.textIndex = d23.textIndex;
        }
        if (d23.checkboxIndex !== undefined) {
            this.checkboxIndex = d23.checkboxIndex;
        }
        if (d23.updateTextAlign !== undefined) {
            this.updateTextAlign = d23.updateTextAlign;
        }
    }
    updateStateVars(c23) {
    }
    purgeVariableDependenciesOnElmtId(b23) {
        this.__isChecked.purgeDependencyOnElmtId(b23);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(b23);
        this.__textAlign.purgeDependencyOnElmtId(b23);
        this.__fontSizeScale.purgeDependencyOnElmtId(b23);
        this.__minContentHeight.purgeDependencyOnElmtId(b23);
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
    setController(a23) {
        this.controller = a23;
    }
    get isChecked() {
        return this.__isChecked.get();
    }
    set isChecked(z22) {
        this.__isChecked.set(z22);
    }
    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }
    set fontColorWithTheme(y22) {
        this.__fontColorWithTheme.set(y22);
    }
    get textAlign() {
        return this.__textAlign.get();
    }
    set textAlign(x22) {
        this.__textAlign.set(x22);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(w22) {
        this.__fontSizeScale.set(w22);
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(v22) {
        this.__minContentHeight.set(v22);
    }
    textBuilder(l22 = null) {
        this.observeComponentCreation2((t22, u22) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((r22, s22) => {
            Scroll.create(this.contentScroller);
            Scroll.fadingEdge(IS_FADEOUT_ENABLE(), { fadingEdgeLength: LengthMetrics.vp(FADEOUT_GRADIENT_WIDTH) });
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
        }, Scroll);
        this.observeComponentCreation2((p22, q22) => {
            Column.create();
            Column.margin({ end: LengthMetrics.vp(CONTENT_END_MARGIN()) });
        }, Column);
        this.observeComponentCreation2((m22, n22) => {
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
            Text.onKeyEvent((o22) => {
                if (o22) {
                    resolveKeyEvent(o22, this.contentScroller);
                }
            });
            Text.width('100%');
        }, Text);
        Text.pop();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }
    checkBoxBuilder(c22 = null) {
        this.observeComponentCreation2((i22, j22) => {
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
                let k22 = ({
                    type: 'announceForAccessibility',
                    bundleName: getContext()?.abilityInfo?.bundleName,
                    triggerAction: 'click',
                    textAnnouncedForAccessibility: this.isChecked ?
                    getContext().resourceManager.getStringSync(125833934) :
                    getContext().resourceManager.getStringSync(125833935)
                });
                accessibility.sendAccessibilityEvent(k22).then(() => {
                    console.info(`Accessibility send event`);
                });
            });
            Row.width('100%');
            Row.padding({ top: TIP_CHECKBOX_TOP_PADDING(), bottom: TIP_CHECKBOX_BOTTOM_PADDING() });
        }, Row);
        this.observeComponentCreation2((f22, g22) => {
            Checkbox.create({ name: '', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((h22) => {
                this.isChecked = h22;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(TIP_CHECKBOX_END_MARGIN()) });
        }, Checkbox);
        Checkbox.pop();
        this.observeComponentCreation2((d22, e22) => {
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
    buildContent(b21 = null) {
        {
            this.observeComponentCreation2((c21, d21) => {
                if (d21) {
                    let e21 = new ConfirmDialogContentLayout(this, {
                        minContentHeight: this.__minContentHeight, updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((r21, s21) => {
                                ForEach.create();
                                const t21 = u21 => {
                                    const v21 = u21;
                                    this.observeComponentCreation2((w21, x21) => {
                                        If.create();
                                        if (v21 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((a22, b22) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.textBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else if (v21 === this.checkboxIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((y21, z21) => {
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
                                this.forEachUpdateFunction(r21,
                                    [this.textIndex, this.checkboxIndex], t21);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, c21, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 754, col: 5 });
                    ViewPU.create(e21);
                    let f21 = () => {
                        return {
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((g21, h21) => {
                                    ForEach.create();
                                    const i21 = j21 => {
                                        const k21 = j21;
                                        this.observeComponentCreation2((l21, m21) => {
                                            If.create();
                                            if (k21 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((p21, q21) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.textBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else if (k21 === this.checkboxIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((n21, o21) => {
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
                                    this.forEachUpdateFunction(g21,
                                        [this.textIndex, this.checkboxIndex], i21);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    e21.paramsGenerator_ = f21;
                } else {
                    this.updateStateVarsOfChildByElmtId(c21, {});
                }
            }, { name: 'ConfirmDialogContentLayout' });
        }
    }
    initialRender() {
        this.observeComponentCreation2((z20, a21) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((v20, w20) => {
                if (w20) {
                    let x20 = new CustomDialogContentComponent(this, {
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
                    }, undefined, v20, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 770, col: 5 });
                    ViewPU.create(x20);
                    let y20 = () => {
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
                    x20.paramsGenerator_ = y20;
                } else {
                    this.updateStateVarsOfChildByElmtId(v20, {});
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
    constructor(p20, q20, r20, s20 = -1, t20 = undefined, u20) {
        super(p20, r20, s20, u20);
        if (typeof t20 === 'function') {
            this.paramsGenerator_ = t20;
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
        this.setInitiallyProvidedValue(q20);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(o20) {
        if (o20.controller !== undefined) {
            this.controller = o20.controller;
        }
        if (o20.primaryTitle !== undefined) {
            this.primaryTitle = o20.primaryTitle;
        }
        if (o20.secondaryTitle !== undefined) {
            this.secondaryTitle = o20.secondaryTitle;
        }
        if (o20.content !== undefined) {
            this.content = o20.content;
        }
        if (o20.primaryButton !== undefined) {
            this.primaryButton = o20.primaryButton;
        }
        if (o20.secondaryButton !== undefined) {
            this.secondaryButton = o20.secondaryButton;
        }
        if (o20.buttons !== undefined) {
            this.buttons = o20.buttons;
        }
        if (o20.textAlign !== undefined) {
            this.textAlign = o20.textAlign;
        }
        if (o20.contentScroller !== undefined) {
            this.contentScroller = o20.contentScroller;
        }
        if (o20.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = o20.fontColorWithTheme;
        }
        if (o20.theme !== undefined) {
            this.theme = o20.theme;
        }
        if (o20.themeColorMode !== undefined) {
            this.themeColorMode = o20.themeColorMode;
        }
        if (o20.fontSizeScale !== undefined) {
            this.fontSizeScale = o20.fontSizeScale;
        }
        if (o20.minContentHeight !== undefined) {
            this.minContentHeight = o20.minContentHeight;
        }
    }
    updateStateVars(n20) {
    }
    purgeVariableDependenciesOnElmtId(m20) {
        this.__textAlign.purgeDependencyOnElmtId(m20);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(m20);
        this.__fontSizeScale.purgeDependencyOnElmtId(m20);
        this.__minContentHeight.purgeDependencyOnElmtId(m20);
    }
    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(l20) {
        this.controller = l20;
    }
    get textAlign() {
        return this.__textAlign.get();
    }
    set textAlign(k20) {
        this.__textAlign.set(k20);
    }
    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }
    set fontColorWithTheme(j20) {
        this.__fontColorWithTheme.set(j20);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(i20) {
        this.__fontSizeScale.set(i20);
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(h20) {
        this.__minContentHeight.set(h20);
    }
    initialRender() {
        this.observeComponentCreation2((f20, g20) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((b20, c20) => {
                if (c20) {
                    let d20 = new CustomDialogContentComponent(this, {
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
                    }, undefined, b20, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 828, col: 5 });
                    ViewPU.create(d20);
                    let e20 = () => {
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
                    d20.paramsGenerator_ = e20;
                } else {
                    this.updateStateVarsOfChildByElmtId(b20, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }
    AlertDialogContentBuilder(r19 = null) {
        this.observeComponentCreation2((z19, a20) => {
            Column.create();
            Column.margin({ end: LengthMetrics.vp(0 - SCROLL_BAR_OFFSET) });
        }, Column);
        this.observeComponentCreation2((x19, y19) => {
            Scroll.create(this.contentScroller);
            Scroll.fadingEdge(IS_FADEOUT_ENABLE(), { fadingEdgeLength: LengthMetrics.vp(FADEOUT_GRADIENT_WIDTH) });
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((s19, t19) => {
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
            Text.width(`calc(100% - ${PADDING_LEVEL_8}vp)`);
            Text.textAlign(this.textAlign);
            Text.onSizeChange((v19, w19) => {
                this.updateTextAlign(Number(w19.width));
            });
            Text.onKeyEvent((u19) => {
                if (u19) {
                    resolveKeyEvent(u19, this.contentScroller);
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
    updateTextAlign(q19) {
        this.textAlign = getTextAlign(q19, this.content, `${BODY_L * this.fontSizeScale}vp`);
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
    constructor(k19, l19, m19, n19 = -1, o19 = undefined, p19) {
        super(k19, m19, n19, p19);
        if (typeof o19 === 'function') {
            this.paramsGenerator_ = o19;
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
        this.setInitiallyProvidedValue(l19);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(j19) {
        if (j19.controller !== undefined) {
            this.controller = j19.controller;
        }
        if (j19.primaryTitle !== undefined) {
            this.primaryTitle = j19.primaryTitle;
        }
        if (j19.secondaryTitle !== undefined) {
            this.secondaryTitle = j19.secondaryTitle;
        }
        if (j19.contentBuilder !== undefined) {
            this.contentBuilder = j19.contentBuilder;
        }
        if (j19.contentAreaPadding !== undefined) {
            this.contentAreaPadding = j19.contentAreaPadding;
        }
        if (j19.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = j19.localizedContentAreaPadding;
        }
        if (j19.buttons !== undefined) {
            this.buttons = j19.buttons;
        }
        if (j19.theme !== undefined) {
            this.theme = j19.theme;
        }
        if (j19.themeColorMode !== undefined) {
            this.themeColorMode = j19.themeColorMode;
        }
        if (j19.fontSizeScale !== undefined) {
            this.fontSizeScale = j19.fontSizeScale;
        }
        if (j19.minContentHeight !== undefined) {
            this.minContentHeight = j19.minContentHeight;
        }
    }
    updateStateVars(i19) {
    }
    purgeVariableDependenciesOnElmtId(h19) {
        this.__fontSizeScale.purgeDependencyOnElmtId(h19);
        this.__minContentHeight.purgeDependencyOnElmtId(h19);
    }
    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(d19) {
        this.controller = d19;
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(c19) {
        this.__fontSizeScale.set(c19);
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(b19) {
        this.__minContentHeight.set(b19);
    }
    initialRender() {
        this.observeComponentCreation2((z18, a19) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((v18, w18) => {
                if (w18) {
                    let x18 = new CustomDialogContentComponent(this, {
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
                    }, undefined, v18, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 920, col: 5 });
                    ViewPU.create(x18);
                    let y18 = () => {
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
                    x18.paramsGenerator_ = y18;
                } else {
                    this.updateStateVarsOfChildByElmtId(v18, {});
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
    constructor(u18) {
        super(u18);
        this.arg_ = u18;
    }
}
class CustomDialogLayout extends ViewPU {
    constructor(o18, p18, q18, r18 = -1, s18 = undefined, t18) {
        super(o18, q18, r18, t18);
        if (typeof s18 === 'function') {
            this.paramsGenerator_ = s18;
        }
        this.__titleHeight = new SynchedPropertySimpleTwoWayPU(p18.titleHeight, this, 'titleHeight');
        this.__buttonHeight = new SynchedPropertySimpleTwoWayPU(p18.buttonHeight, this, 'buttonHeight');
        this.__titleMinHeight = new SynchedPropertyObjectTwoWayPU(p18.titleMinHeight, this, 'titleMinHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.titleIndex = 0;
        this.contentIndex = 1;
        this.buttonIndex = 2;
        this.setInitiallyProvidedValue(p18);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(n18) {
        if (n18.dialogBuilder !== undefined) {
            this.dialogBuilder = n18.dialogBuilder;
        }
        if (n18.titleIndex !== undefined) {
            this.titleIndex = n18.titleIndex;
        }
        if (n18.contentIndex !== undefined) {
            this.contentIndex = n18.contentIndex;
        }
        if (n18.buttonIndex !== undefined) {
            this.buttonIndex = n18.buttonIndex;
        }
    }
    updateStateVars(m18) {
    }
    purgeVariableDependenciesOnElmtId(l18) {
        this.__titleHeight.purgeDependencyOnElmtId(l18);
        this.__buttonHeight.purgeDependencyOnElmtId(l18);
        this.__titleMinHeight.purgeDependencyOnElmtId(l18);
    }
    aboutToBeDeleted() {
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__titleMinHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    doNothingBuilder(k18 = null) {
    }
    get titleHeight() {
        return this.__titleHeight.get();
    }
    set titleHeight(j18) {
        this.__titleHeight.set(j18);
    }
    get buttonHeight() {
        return this.__buttonHeight.get();
    }
    set buttonHeight(i18) {
        this.__buttonHeight.set(i18);
    }
    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }
    set titleMinHeight(h18) {
        this.__titleMinHeight.set(h18);
    }
    onPlaceChildren(a18, b18, c18) {
        let d18 = 0;
        let e18 = 0;
        for (let f18 = 0; f18 < b18.length; f18++) {
            let g18 = b18[f18];
            g18.layout({ x: d18, y: e18 });
            e18 += g18.measureResult.height;
        }
    }
    onMeasureSize(m17, n17, o17) {
        let p17 = { width: Number(o17.maxWidth), height: 0 };
        let q17 = 3;
        if (n17.length < q17) {
            return p17;
        }
        let r17 = 0;
        let s17 = n17[this.titleIndex];
        let t17 = {
            maxWidth: o17.maxWidth,
            minHeight: this.titleMinHeight,
            maxHeight: o17.maxHeight
        };
        let u17 = s17.measure(t17);
        this.titleHeight = u17.height;
        r17 += this.titleHeight;
        let v17 = n17[this.buttonIndex];
        let w17 = v17.measure(o17);
        this.buttonHeight = w17.height;
        r17 += this.buttonHeight;
        let x17 = n17[this.contentIndex];
        let y17 = {
            maxWidth: o17.maxWidth,
            maxHeight: Number(o17.maxHeight) - r17
        };
        let z17 = x17.measure(y17);
        r17 += z17.height;
        p17.height = r17;
        return p17;
    }
    initialRender() {
        this.dialogBuilder.bind(this)();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class CustomDialogContentComponent extends ViewPU {
    constructor(g17, h17, i17, j17 = -1, k17 = undefined, l17) {
        super(g17, i17, j17, l17);
        if (typeof k17 === 'function') {
            this.paramsGenerator_ = k17;
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
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(h17.minContentHeight, this, 'minContentHeight');
        this.__titleHeight = new ObservedPropertySimplePU(0, this, 'titleHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
        this.__contentMaxHeight = new ObservedPropertyObjectPU('100%', this, 'contentMaxHeight');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(h17.fontSizeScale, this, 'fontSizeScale');
        this.__customStyle = new ObservedPropertySimplePU(undefined, this, 'customStyle');
        this.__buttonMaxFontSize = new ObservedPropertyObjectPU(`${BODY_L}fp`, this, 'buttonMaxFontSize');
        this.__buttonMinFontSize = new ObservedPropertyObjectPU(9, this, 'buttonMinFontSize');
        this.__primaryTitleMaxFontSize = new ObservedPropertyObjectPU(`${TITLE_S}fp`, this, 'primaryTitleMaxFontSize');
        this.__primaryTitleMinFontSize = new ObservedPropertyObjectPU(`${BODY_L}fp`, this, 'primaryTitleMinFontSize');
        this.__secondaryTitleMaxFontSize =
            new ObservedPropertyObjectPU(`${SUBTITLE_SIZE()}fp`, this, 'secondaryTitleMaxFontSize');
        this.__secondaryTitleMinFontSize = new ObservedPropertyObjectPU(`${BODY_S}fp`, this, 'secondaryTitleMinFontSize');
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
        this.setInitiallyProvidedValue(h17);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(f17) {
        if (f17.controller !== undefined) {
            this.controller = f17.controller;
        }
        if (f17.primaryTitle !== undefined) {
            this.primaryTitle = f17.primaryTitle;
        }
        if (f17.secondaryTitle !== undefined) {
            this.secondaryTitle = f17.secondaryTitle;
        }
        if (f17.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = f17.localizedContentAreaPadding;
        }
        if (f17.contentBuilder !== undefined) {
            this.contentBuilder = f17.contentBuilder;
        }
        if (f17.buttons !== undefined) {
            this.buttons = f17.buttons;
        }
        if (f17.contentAreaPadding !== undefined) {
            this.contentAreaPadding = f17.contentAreaPadding;
        }
        if (f17.keyIndex !== undefined) {
            this.keyIndex = f17.keyIndex;
        }
        if (f17.theme !== undefined) {
            this.theme = f17.theme;
        }
        if (f17.themeColorMode !== undefined) {
            this.themeColorMode = f17.themeColorMode;
        }
        if (f17.titleHeight !== undefined) {
            this.titleHeight = f17.titleHeight;
        }
        if (f17.buttonHeight !== undefined) {
            this.buttonHeight = f17.buttonHeight;
        }
        if (f17.contentMaxHeight !== undefined) {
            this.contentMaxHeight = f17.contentMaxHeight;
        }
        if (f17.customStyle !== undefined) {
            this.customStyle = f17.customStyle;
        }
        if (f17.buttonMaxFontSize !== undefined) {
            this.buttonMaxFontSize = f17.buttonMaxFontSize;
        }
        if (f17.buttonMinFontSize !== undefined) {
            this.buttonMinFontSize = f17.buttonMinFontSize;
        }
        if (f17.primaryTitleMaxFontSize !== undefined) {
            this.primaryTitleMaxFontSize = f17.primaryTitleMaxFontSize;
        }
        if (f17.primaryTitleMinFontSize !== undefined) {
            this.primaryTitleMinFontSize = f17.primaryTitleMinFontSize;
        }
        if (f17.secondaryTitleMaxFontSize !== undefined) {
            this.secondaryTitleMaxFontSize = f17.secondaryTitleMaxFontSize;
        }
        if (f17.secondaryTitleMinFontSize !== undefined) {
            this.secondaryTitleMinFontSize = f17.secondaryTitleMinFontSize;
        }
        if (f17.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = f17.primaryTitleFontColorWithTheme;
        }
        if (f17.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = f17.secondaryTitleFontColorWithTheme;
        }
        if (f17.titleTextAlign !== undefined) {
            this.titleTextAlign = f17.titleTextAlign;
        }
        if (f17.isButtonVertical !== undefined) {
            this.isButtonVertical = f17.isButtonVertical;
        }
        if (f17.titleMinHeight !== undefined) {
            this.titleMinHeight = f17.titleMinHeight;
        }
        if (f17.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = f17.isFollowingSystemFontScale;
        }
        if (f17.appMaxFontScale !== undefined) {
            this.appMaxFontScale = f17.appMaxFontScale;
        }
        if (f17.titleIndex !== undefined) {
            this.titleIndex = f17.titleIndex;
        }
        if (f17.contentIndex !== undefined) {
            this.contentIndex = f17.contentIndex;
        }
        if (f17.buttonIndex !== undefined) {
            this.buttonIndex = f17.buttonIndex;
        }
    }
    updateStateVars(e17) {
    }
    purgeVariableDependenciesOnElmtId(d17) {
        this.__minContentHeight.purgeDependencyOnElmtId(d17);
        this.__titleHeight.purgeDependencyOnElmtId(d17);
        this.__buttonHeight.purgeDependencyOnElmtId(d17);
        this.__contentMaxHeight.purgeDependencyOnElmtId(d17);
        this.__fontSizeScale.purgeDependencyOnElmtId(d17);
        this.__customStyle.purgeDependencyOnElmtId(d17);
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(d17);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(d17);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(d17);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(d17);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(d17);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(d17);
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(d17);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(d17);
        this.__titleTextAlign.purgeDependencyOnElmtId(d17);
        this.__isButtonVertical.purgeDependencyOnElmtId(d17);
        this.__titleMinHeight.purgeDependencyOnElmtId(d17);
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
    set minContentHeight(c17) {
        this.__minContentHeight.set(c17);
    }
    defaultContentBuilder(b17 = null) {
    }
    get titleHeight() {
        return this.__titleHeight.get();
    }
    set titleHeight(a17) {
        this.__titleHeight.set(a17);
    }
    get buttonHeight() {
        return this.__buttonHeight.get();
    }
    set buttonHeight(z16) {
        this.__buttonHeight.set(z16);
    }
    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }
    set contentMaxHeight(y16) {
        this.__contentMaxHeight.set(y16);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(x16) {
        this.__fontSizeScale.set(x16);
    }
    get customStyle() {
        return this.__customStyle.get();
    }
    set customStyle(w16) {
        this.__customStyle.set(w16);
    }
    get buttonMaxFontSize() {
        return this.__buttonMaxFontSize.get();
    }
    set buttonMaxFontSize(v16) {
        this.__buttonMaxFontSize.set(v16);
    }
    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }
    set buttonMinFontSize(u16) {
        this.__buttonMinFontSize.set(u16);
    }
    get primaryTitleMaxFontSize() {
        return this.__primaryTitleMaxFontSize.get();
    }
    set primaryTitleMaxFontSize(t16) {
        this.__primaryTitleMaxFontSize.set(t16);
    }
    get primaryTitleMinFontSize() {
        return this.__primaryTitleMinFontSize.get();
    }
    set primaryTitleMinFontSize(s16) {
        this.__primaryTitleMinFontSize.set(s16);
    }
    get secondaryTitleMaxFontSize() {
        return this.__secondaryTitleMaxFontSize.get();
    }
    set secondaryTitleMaxFontSize(r16) {
        this.__secondaryTitleMaxFontSize.set(r16);
    }
    get secondaryTitleMinFontSize() {
        return this.__secondaryTitleMinFontSize.get();
    }
    set secondaryTitleMinFontSize(q16) {
        this.__secondaryTitleMinFontSize.set(q16);
    }
    get primaryTitleFontColorWithTheme() {
        return this.__primaryTitleFontColorWithTheme.get();
    }
    set primaryTitleFontColorWithTheme(p16) {
        this.__primaryTitleFontColorWithTheme.set(p16);
    }
    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }
    set secondaryTitleFontColorWithTheme(o16) {
        this.__secondaryTitleFontColorWithTheme.set(o16);
    }
    get titleTextAlign() {
        return this.__titleTextAlign.get();
    }
    set titleTextAlign(n16) {
        this.__titleTextAlign.set(n16);
    }
    get isButtonVertical() {
        return this.__isButtonVertical.get();
    }
    set isButtonVertical(m16) {
        this.__isButtonVertical.set(m16);
    }
    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }
    set titleMinHeight(l16) {
        this.__titleMinHeight.set(l16);
    }
    initialRender() {
        this.observeComponentCreation2((j16, k16) => {
            WithTheme.create({ theme: this.theme, colorMode: this.themeColorMode });
        }, WithTheme);
        this.observeComponentCreation2((h16, i16) => {
            Scroll.create();
            Scroll.backgroundColor(this.themeColorMode === ThemeColorMode.SYSTEM || undefined ?
            Color.Transparent : {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.comp_background_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
        }, Scroll);
        this.observeComponentCreation2((f16, g16) => {
            Column.create();
            Column.constraintSize({ maxHeight: this.contentMaxHeight });
            Column.backgroundBlurStyle(this.customStyle ? BlurStyle.Thick : BlurStyle.NONE);
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
            this.observeComponentCreation2((x7, y7) => {
                if (y7) {
                    let z7 = new CustomDialogLayout(this, {
                        buttonHeight: this.__buttonHeight,
                        titleHeight: this.__titleHeight,
                        titleMinHeight: this.__titleMinHeight,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((z13, a14) => {
                                ForEach.create();
                                const d14 = f14 => {
                                    const i14 = f14;
                                    this.observeComponentCreation2((l14, w15) => {
                                        If.create();
                                        if (i14 === this.titleIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((d16, e16) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.titleBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else if (i14 === this.contentIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((b16, c16) => {
                                                    Column.create();
                                                    Column.padding(this.getContentPadding());
                                                }, Column);
                                                this.observeComponentCreation2((z15, a16) => {
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
                                                this.observeComponentCreation2((x15, y15) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.ButtonBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        }
                                    }, If);
                                    If.pop();
                                };
                                this.forEachUpdateFunction(z13, [this.titleIndex, this.contentIndex,
                                    this.buttonIndex], d14);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, x7, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1058, col: 11 });
                    ViewPU.create(z7);
                    let a8 = () => {
                        return {
                            buttonHeight: this.buttonHeight,
                            titleHeight: this.titleHeight,
                            titleMinHeight: this.titleMinHeight,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((b8, d11) => {
                                    ForEach.create();
                                    const i11 = k11 => {
                                        const l11 = k11;
                                        this.observeComponentCreation2((p11, r11) => {
                                            If.create();
                                            if (l11 === this.titleIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((e13, f13) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.titleBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else if (l11 === this.contentIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((o12, r12) => {
                                                        Column.create();
                                                        Column.padding(this.getContentPadding());
                                                    }, Column);
                                                    this.observeComponentCreation2((z11, b12) => {
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
                                                    this.observeComponentCreation2((u11, v11) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.ButtonBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            }
                                        }, If);
                                        If.pop();
                                    };
                                    this.forEachUpdateFunction(b8, [this.titleIndex, this.contentIndex,
                                        this.buttonIndex], i11);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    z7.paramsGenerator_ = a8;
                } else {
                    this.updateStateVarsOfChildByElmtId(x7, {});
                }
            }, { name: 'CustomDialogLayout' });
        }
        Column.pop();
        Scroll.pop();
        WithTheme.pop();
    }
    onMeasureSize(m7, n7, p7) {
        let q7 = { width: m7.width, height: m7.height };
        let s7 = Number(p7.maxWidth);
        let t7 = Number(p7.maxHeight);
        this.fontSizeScale = this.updateFontScale();
        this.updateFontSize();
        this.isButtonVertical = this.isVerticalAlignButton(s7 - BUTTON_HORIZONTAL_MARGIN * 2);
        this.titleMinHeight = this.getTitleAreaMinHeight();
        let u7 = 0;
        n7.forEach((v7) => {
            this.contentMaxHeight = '100%';
            let w7 = v7.measure(p7);
            if (t7 - this.buttonHeight - this.titleHeight < this.minContentHeight) {
                this.contentMaxHeight = MAX_CONTENT_HEIGHT;
                w7 = v7.measure(p7);
            }
            u7 += w7.height;
        });
        q7.height = u7;
        q7.width = s7;
        return q7;
    }
    aboutToAppear() {
        let k7 = this.getUIContext();
        this.isFollowingSystemFontScale = k7.isFollowingSystemFontScale();
        this.appMaxFontScale = k7.getMaxFontScale();
        this.fontSizeScale = this.updateFontScale();
        if (this.controller && this.customStyle === undefined) {
            let l7 = this.controller;
            if (l7.arg_ && l7.arg_.customStyle && l7.arg_.customStyle === true) {
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
            let i7 = this.getUIContext();
            let j7 = i7.getHostContext()?.config.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(j7, this.appMaxFontScale);
        } catch (f7) {
            let g7 = f7.code;
            let h7 = f7.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${g7}, message: ${h7}`);
            return 1;
        }
    }
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
    titleBuilder(q6 = null) {
        this.observeComponentCreation2((d7, e7) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((b7, c7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((z6, a7) => {
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
        this.observeComponentCreation2((v6, w6) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x6, y6) => {
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
        this.observeComponentCreation2((t6, u6) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((r6, s6) => {
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
    initTitleTextAlign() {
        let p6 = ALERT_TITLE_ALIGNMENT();
        if (p6 === TextAlign.Start) {
            this.titleTextAlign = TextAlign.Start;
        } else if (p6 === TextAlign.Center) {
            this.titleTextAlign = TextAlign.Center;
        } else if (p6 === TextAlign.End) {
            this.titleTextAlign = TextAlign.End;
        } else if (p6 === TextAlign.JUSTIFY) {
            this.titleTextAlign = TextAlign.JUSTIFY;
        } else {
            this.titleTextAlign = TextAlign.Center;
        }
    }
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
    ButtonBuilder(g6 = null) {
        this.observeComponentCreation2((m6, n6) => {
            Column.create();
            Column.width('100%');
            Column.padding(this.getOperationAreaPadding());
        }, Column);
        this.observeComponentCreation2((h6, i6) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k6, l6) => {
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
    buildSingleButton(t5, u5 = null) {
        this.observeComponentCreation2((v5, w5) => {
            If.create();
            if (this.isNewPropertiesHighPriority(t5)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d6, e6) => {
                        Button.createWithLabel(t5.value);
                        __Button__setButtonProperties(t5, this.buttons, this.controller);
                        Button.role(t5.role ?? ButtonRole.NORMAL);
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
            } else if (t5.background !== undefined && t5.fontColor !== undefined) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((b6, c6) => {
                        Button.createWithLabel(t5.value);
                        __Button__setButtonProperties(t5, this.buttons, this.controller);
                        Button.backgroundColor(t5.background);
                        Button.fontColor(t5.fontColor);
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
            } else if (t5.background !== undefined) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((z5, a6) => {
                        Button.createWithLabel(t5.value);
                        __Button__setButtonProperties(t5, this.buttons, this.controller);
                        Button.backgroundColor(t5.background);
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
                    this.observeComponentCreation2((x5, y5) => {
                        Button.createWithLabel(t5.value);
                        __Button__setButtonProperties(t5, this.buttons, this.controller);
                        Button.fontColor(t5.fontColor);
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
    buildHorizontalAlignButtons(g5 = null) {
        this.observeComponentCreation2((h5, i5) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r5, s5) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[0]);
                    this.observeComponentCreation2((j5, m5) => {
                        If.create();
                        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((p5, q5) => {
                                    Row.create();
                                    Row.width(BUTTON_HORIZONTAL_SPACE * 2);
                                    Row.justifyContent(FlexAlign.Center);
                                }, Row);
                                this.observeComponentCreation2((n5, o5) => {
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
    buildVerticalAlignButtons(s4 = null) {
        this.observeComponentCreation2((t4, u4) => {
            If.create();
            if (this.buttons) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e5, f5) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((v4, w4) => {
                        ForEach.create();
                        const x4 = (z4, b5) => {
                            const c5 = z4;
                            this.buildButtonWithDivider.bind(this)(this.buttons?.length === HORIZON_BUTTON_MAX_COUNT ?
                                HORIZON_BUTTON_MAX_COUNT - b5 - 1 : b5);
                        };
                        this.forEachUpdateFunction(v4, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT),
                            x4, (y4) => y4.value.toString(), true, false);
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
    isNewPropertiesHighPriority(r4) {
        if (r4.role === ButtonRole.ERROR) {
            return true;
        }
        if (r4.buttonStyle !== undefined &&
            r4.buttonStyle !== ALERT_BUTTON_STYLE()) {
            return true;
        }
        if (r4.background === undefined && r4.fontColor === undefined) {
            return true;
        }
        return false;
    }
    buildButtonWithDivider(e4, g4 = null) {
        this.observeComponentCreation2((h4, i4) => {
            If.create();
            if (this.buttons && this.buttons[e4]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o4, p4) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[e4]);
                    Row.pop();
                    this.observeComponentCreation2((k4, l4) => {
                        If.create();
                        if ((this.buttons.length === HORIZON_BUTTON_MAX_COUNT ? HORIZON_BUTTON_MAX_COUNT - e4 - 1 : e4) <
                            Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((m4, n4) => {
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
    isVerticalAlignButton(x3) {
        if (this.buttons) {
            if (this.buttons.length === 1) {
                return false;
            }
            if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
                return true;
            }
            let z3 = false;
            let a4 = vp2px(x3 / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
                BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
            this.buttons.forEach((b4) => {
                let c4 = measure.measureTextSize({
                    textContent: b4.value,
                    fontSize: this.buttonMaxFontSize
                });
                if (Number(c4.width) > a4) {
                    z3 = true;
                }
            });
            return z3;
        }
        return false;
    }
    rerender() {
        this.updateDirtyElements();
    }
}
function __Button__setButtonProperties(u3, v3, w3) {
    Button.onKeyEvent((event) => {
        if (!event) {
            return;
        }
        if ((event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER) && 
            event.type === KeyType.Down) {
            if (u3.action) {
                u3.action();
            }
            w3?.close();
            event.stopPropagation();
        }
    });
    Button.onClick(() => {
        if (u3.action) {
            u3.action();
        }
        w3?.close();
    });
    Button.defaultFocus(u3.defaultFocus ? true : isHasDefaultFocus(v3) ? false : true);
    Button.buttonStyle(u3.buttonStyle ??
        (u3.role === ButtonRole.ERROR ? ERROR_BUTTON_STYLE() : ALERT_BUTTON_STYLE()));
    Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
    Button.type(ButtonType.ROUNDED_RECTANGLE);
}
function isHasDefaultFocus(m3) {
    try {
        let q3 = false;
        m3?.forEach((t3) => {
            if (t3.defaultFocus) {
                q3 = true;
            }
        });
        return q3;
    }
    catch (n3) {
        let o3 = n3.code;
        let p3 = n3.message;
        hilog.error(0x3900, 'Ace', `get defaultFocus exist error, code: ${o3}, message: ${p3}`);
        return false;
    }
}
function getNumberByResourceId(f3, g3, h3) {
    try {
        let l3 = resourceManager.getSystemResourceManager().getNumber(f3);
        if (l3 > 0 || h3) {
            return l3;
        } else {
            return g3;
        }
    } catch (i3) {
        let j3 = i3.code;
        let k3 = i3.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResourceId error, code: ${j3}, message: ${k3}`);
        return g3;
    }
}
function lazyInit(initializer) {
    let value = null;
    return () => {
        if (value === null) {
            value = initializer();
        }
        return value;
    };
}
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
function getAccessibilityText(s2, t2) {
    try {
        let x2 = getContext().resourceManager.getStringSync(125833934);
        let y2 = '';
        if (typeof s2 === 'string') {
            y2 = s2;
        } else {
            y2 = getContext().resourceManager.getStringSync(s2);
        }
        return t2 ? `${x2},${y2}` : y2;
    } catch (u2) {
        let v2 = u2.code;
        let w2 = u2.message;
        hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${v2}, message: ${w2}`);
        return '';
    }
}
function getTextAlign(n2, o2, p2) {
    let q2 = measure.measureTextSize({
        textContent: o2,
        fontSize: p2,
        constraintWidth: n2,
    });
    let r2 = measure.measureTextSize({
        textContent: o2,
        fontSize: p2,
    });
    if (getTextHeight(q2) <= getTextHeight(r2)) {
        return TextAlign.Center;
    }
    return TextAlign.Start;
}
function getTextHeight(m2) {
    if (m2 && m2.height !== null && m2.height !== undefined) {
        return Number(m2.height);
    }
    return 0;
}
function resolveKeyEvent(k2, l2) {
    if (k2.type === IGNORE_KEY_EVENT_TYPE) {
        return;
    }
    if (k2.keyCode === KEYCODE_UP) {
        l2.scrollPage({ next: false });
        k2.stopPropagation();
    } else if (k2.keyCode === KEYCODE_DOWN) {
        if (l2.isAtEnd()) {
            return;
        } else {
            l2.scrollPage({ next: true });
            k2.stopPropagation();
        }
    }
}
function getCheckTipsAccessibilityText(b2, c2) {
    try {
        let g2 = getContext().resourceManager.getStringSync(125833934);
        let h2 = getContext().resourceManager.getStringSync(125833935);
        let i2 = getContext().resourceManager.getStringSync(125834354);
        let j2 = '';
        if (typeof b2 === 'string') {
            j2 = b2;
        } else {
            j2 = getContext().resourceManager.getStringSync(b2);
        }
        return c2 ? `${g2},${j2},${i2}` :
            `${h2},${j2},${i2}`;
    } catch (d2) {
        let e2 = d2.code;
        let f2 = d2.message;
        hilog.error(0x3900, 'Ace', `getCheckTipsAccessibilityText error, code: ${e2}, message: ${f2}`);
        return '';
    }
}
export class LoadingDialog extends ViewPU {
    constructor(v1, w1, x1, y1 = -1, z1 = undefined, a2) {
        super(v1, x1, y1, a2);
        if (typeof z1 === 'function') {
            this.paramsGenerator_ = z1;
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
        this.setInitiallyProvidedValue(w1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(u1) {
        if (u1.controller !== undefined) {
            this.controller = u1.controller;
        }
        if (u1.content !== undefined) {
            this.content = u1.content;
        }
        if (u1.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = u1.fontColorWithTheme;
        }
        if (u1.loadingProgressIconColorWithTheme !== undefined) {
            this.loadingProgressIconColorWithTheme = u1.loadingProgressIconColorWithTheme;
        }
        if (u1.theme !== undefined) {
            this.theme = u1.theme;
        }
        if (u1.themeColorMode !== undefined) {
            this.themeColorMode = u1.themeColorMode;
        }
        if (u1.fontSizeScale !== undefined) {
            this.fontSizeScale = u1.fontSizeScale;
        }
        if (u1.minContentHeight !== undefined) {
            this.minContentHeight = u1.minContentHeight;
        }
    }
    updateStateVars(t1) {
    }
    purgeVariableDependenciesOnElmtId(s1) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(s1);
        this.__loadingProgressIconColorWithTheme.purgeDependencyOnElmtId(s1);
        this.__fontSizeScale.purgeDependencyOnElmtId(s1);
        this.__minContentHeight.purgeDependencyOnElmtId(s1);
    }
    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__loadingProgressIconColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(r1) {
        this.controller = r1;
    }
    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }
    set fontColorWithTheme(q1) {
        this.__fontColorWithTheme.set(q1);
    }
    get loadingProgressIconColorWithTheme() {
        return this.__loadingProgressIconColorWithTheme.get();
    }
    set loadingProgressIconColorWithTheme(p1) {
        this.__loadingProgressIconColorWithTheme.set(p1);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(o1) {
        this.__fontSizeScale.set(o1);
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(n1) {
        this.__minContentHeight.set(n1);
    }
    initialRender() {
        this.observeComponentCreation2((l1, m1) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((j1, k1) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((f1, g1) => {
                if (g1) {
                    let h1 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, f1, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1710, col: 7 });
                    ViewPU.create(h1);
                    let i1 = () => {
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
                    h1.paramsGenerator_ = i1;
                } else {
                    this.updateStateVarsOfChildByElmtId(f1, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        Column.pop();
    }
    contentBuilder(v = null) {
        this.observeComponentCreation2((c1, d1) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((a1, b1) => {
            Row.create();
            Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
        }, Row);
        this.observeComponentCreation2((y, z) => {
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
        this.observeComponentCreation2((w, x) => {
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
    constructor(p, q, r, s = -1, t = undefined, u) {
        super(p, r, s, u);
        if (typeof t === 'function') {
            this.paramsGenerator_ = t;
        }
        this.__visible = new SynchedPropertySimpleTwoWayPU(q.visible, this, 'visible');
        this.__popover = new SynchedPropertyObjectOneWayPU(q.popover, this, 'popover');
        this.targetBuilder = undefined;
        this.__dialogWidth = new ObservedPropertyObjectPU(this.popover?.width, this, 'dialogWidth');
        this.setInitiallyProvidedValue(q);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(o) {
        if (o.targetBuilder !== undefined) {
            this.targetBuilder = o.targetBuilder;
        }
        if (o.dialogWidth !== undefined) {
            this.dialogWidth = o.dialogWidth;
        }
    }
    updateStateVars(n) {
        this.__popover.reset(n.popover);
    }
    purgeVariableDependenciesOnElmtId(m) {
        this.__visible.purgeDependencyOnElmtId(m);
        this.__popover.purgeDependencyOnElmtId(m);
        this.__dialogWidth.purgeDependencyOnElmtId(m);
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
    set visible(l) {
        this.__visible.set(l);
    }
    get popover() {
        return this.__popover.get();
    }
    set popover(k) {
        this.__popover.set(k);
    }
    get dialogWidth() {
        return this.__dialogWidth.get();
    }
    set dialogWidth(j) {
        this.__dialogWidth.set(j);
    }
    emptyBuilder(i = null) {
    }
    aboutToAppear() {
        if (this.targetBuilder === undefined || this.targetBuilder === null) {
            this.targetBuilder = this.emptyBuilder;
        }
    }
    initialRender() {
        this.observeComponentCreation2((a, b) => {
            Column.create();
            Column.onClick(() => {
                try {
                    let g = display.getDefaultDisplaySync();
                    let h = px2vp(g.width);
                    if (h - BUTTON_HORIZONTAL_MARGIN - BUTTON_HORIZONTAL_MARGIN > MAX_DIALOG_WIDTH) {
                        this.popover.width = this.popover?.width ?? MAX_DIALOG_WIDTH;
                    } else {
                        this.popover.width = this.dialogWidth;
                    }
                    this.visible = !this.visible;
                } catch (d) {
                    let e = d.code;
                    let f = d.message;
                    hilog.error(0x3900, 'Ace', `dialog popup error, code: ${e}, message: ${f}`);
                }
            });
            Column.bindPopup(this.visible, {
                builder: this.popover?.builder,
                placement: this.popover?.placement ?? Placement.Bottom,
                popupColor: this.popover?.popupColor,
                enableArrow: this.popover?.enableArrow ?? true,
                autoCancel: this.popover?.autoCancel,
                onStateChange: this.popover?.onStateChange ?? ((c) => {
                    if (!c.isVisible) {
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

export default { TipsDialog, ConfirmDialog, SelectDialog, AlertDialog, LoadingDialog, CustomContentDialog, PopoverDialog };