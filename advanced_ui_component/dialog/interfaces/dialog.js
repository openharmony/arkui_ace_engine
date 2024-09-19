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

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

if (PUV2ViewBase.contextStack === undefined) {
    Reflect.set(PUV2ViewBase, 'contextStack', []);
}

class CustomThemeImpl {
    constructor(p31) {
        this.colors = p31;
    }
}

const TITLE_MAX_LINES = 2;
const HORIZON_BUTTON_MAX_COUNT = 2;
const VERTICAL_BUTTON_MAX_COUNT = 4;
const BUTTON_LAYOUT_WEIGHT = 1;
const CHECKBOX_CONTAINER_HEIGHT = 48;
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
const DEFAULT_IMAGE_SIZE = 64;
const MIN_CONTENT_HEIGHT = 100;
const MAX_CONTENT_HEIGHT = 30000;
const KEYCODE_UP = 2012;
const KEYCODE_DOWN = 2013;
const IGNORE_KEY_EVENT_TYPE = 1;
const FIRST_ITEM_INDEX = 0;
const VERSION_TWELVE = 50000012;
const BUTTON_MIN_FONT_SIZE = 9;
const MAX_FONT_SCALE = 2;
const MAX_DIALOG_WIDTH = getNumberByResourceId(125831042, 400);
const BUTTON_HORIZONTAL_MARGIN = getNumberByResourceId(125831054, 16);
const BUTTON_HORIZONTAL_PADDING = getNumberByResourceId(125830927, 16);
const CHECK_BOX_MARGIN_END = getNumberByResourceId(125830923, 8);
const BUTTON_HORIZONTAL_SPACE = getNumberByResourceId(125831051, 8);
const BODY_L = getNumberByResourceId(125830970, 16);
const BODY_M = getNumberByResourceId(125830971, 14);
const BODY_S = getNumberByResourceId(125830972, 12);
const TITLE_S = getNumberByResourceId(125830966, 20);
const SUBTITLE_S = getNumberByResourceId(125830969, 14);
const PADDING_LEVEL_8 = getNumberByResourceId(125830927, 16);
const DIALOG_DIVIDER_SHOW = getNumberByResourceId(125831202, 1, true);
const ALERT_BUTTON_STYLE = getNumberByResourceId(125831085, 2, true);
const ALERT_TITLE_ALIGNMENT = getEnumNumberByResourceId(125831126, 1);

export class TipsDialog extends ViewPU {
    constructor(h31, i31, j31, k31 = -1, l31 = undefined, m31) {
        super(h31, j31, k31, m31);
        if (typeof l31 === 'function') {
            this.paramsGenerator_ = l31;
        }
        this.controller = undefined;
        this.imageRes = null;
        this.__imageSize =
            new ObservedPropertyObjectPU({ width: DEFAULT_IMAGE_SIZE, height: DEFAULT_IMAGE_SIZE }, this, 'imageSize');
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
        this.updateTextAlign = (o31) => {
            if (this.content) {
                this.textAlignment = getTextAlign(o31, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.setInitiallyProvidedValue(i31);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(g31) {
        if (g31.controller !== undefined) {
            this.controller = g31.controller;
        }
        if (g31.imageRes !== undefined) {
            this.imageRes = g31.imageRes;
        }
        if (g31.imageSize !== undefined) {
            this.imageSize = g31.imageSize;
        }
        if (g31.title !== undefined) {
            this.title = g31.title;
        }
        if (g31.content !== undefined) {
            this.content = g31.content;
        }
        if (g31.checkAction !== undefined) {
            this.checkAction = g31.checkAction;
        }
        if (g31.onCheckedChange !== undefined) {
            this.onCheckedChange = g31.onCheckedChange;
        }
        if (g31.checkTips !== undefined) {
            this.checkTips = g31.checkTips;
        }
        if (g31.isChecked !== undefined) {
            this.isChecked = g31.isChecked;
        }
        if (g31.primaryButton !== undefined) {
            this.primaryButton = g31.primaryButton;
        }
        if (g31.secondaryButton !== undefined) {
            this.secondaryButton = g31.secondaryButton;
        }
        if (g31.buttons !== undefined) {
            this.buttons = g31.buttons;
        }
        if (g31.textAlignment !== undefined) {
            this.textAlignment = g31.textAlignment;
        }
        if (g31.marginOffset !== undefined) {
            this.marginOffset = g31.marginOffset;
        }
        if (g31.contentScroller !== undefined) {
            this.contentScroller = g31.contentScroller;
        }
        if (g31.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = g31.fontColorWithTheme;
        }
        if (g31.theme !== undefined) {
            this.theme = g31.theme;
        }
        if (g31.themeColorMode !== undefined) {
            this.themeColorMode = g31.themeColorMode;
        }
        if (g31.fontSizeScale !== undefined) {
            this.fontSizeScale = g31.fontSizeScale;
        }
        if (g31.minContentHeight !== undefined) {
            this.minContentHeight = g31.minContentHeight;
        }
        if (g31.updateTextAlign !== undefined) {
            this.updateTextAlign = g31.updateTextAlign;
        }
        if (g31.imageIndex !== undefined) {
            this.imageIndex = g31.imageIndex;
        }
        if (g31.textIndex !== undefined) {
            this.textIndex = g31.textIndex;
        }
        if (g31.checkBoxIndex !== undefined) {
            this.checkBoxIndex = g31.checkBoxIndex;
        }
    }

    updateStateVars(f31) {
    }

    purgeVariableDependenciesOnElmtId(e31) {
        this.__imageSize.purgeDependencyOnElmtId(e31);
        this.__isChecked.purgeDependencyOnElmtId(e31);
        this.__textAlignment.purgeDependencyOnElmtId(e31);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(e31);
        this.__fontSizeScale.purgeDependencyOnElmtId(e31);
        this.__minContentHeight.purgeDependencyOnElmtId(e31);
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

    setController(d31) {
        this.controller = d31;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(c31) {
        this.__imageSize.set(c31);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(b31) {
        this.__isChecked.set(b31);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(a31) {
        this.__textAlignment.set(a31);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(z30) {
        this.__fontColorWithTheme.set(z30);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(y30) {
        this.__fontSizeScale.set(y30);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(x30) {
        this.__minContentHeight.set(x30);
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((v30, w30) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((p30, q30) => {
                if (q30) {
                    let r30 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, p30, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 122, col: 5 });
                    ViewPU.create(r30);
                    let s30 = () => {
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
                    r30.paramsGenerator_ = s30;
                } else {
                    this.updateStateVarsOfChildByElmtId(p30, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    contentBuilder(n28 = null) {
        {
            this.observeComponentCreation2((p28, q28) => {
                if (q28) {
                    let r28 = new TipsDialogContentLayout(this, {
                        title: this.title,
                        content: this.content,
                        checkTips: this.checkTips,
                        minContentHeight: this.__minContentHeight,
                        updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((s29, t29) => {
                                ForEach.create();
                                const u29 = w29 => {
                                    const x29 = w29;
                                    this.observeComponentCreation2((z29, a30) => {
                                        If.create();
                                        if (x29 === this.imageIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.imagePart.bind(this)();
                                            });
                                        } else if (x29 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((k30, l30) => {
                                                    Column.create();
                                                    Column.padding({
                                                        top: {
                                                            'id': -1,
                                                            'type': 10002,
                                                            params: ['sys.float.padding_level8'],
                                                            'bundleName': '__harDefaultBundleName__',
                                                            'moduleName': '__harDefaultModuleName__'
                                                        }
                                                    });
                                                }, Column);
                                                this.observeComponentCreation2((i30, j30) => {
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
                                                this.observeComponentCreation2((d30, e30) => {
                                                    WithTheme.create({ theme: this.theme,
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
                                this.forEachUpdateFunction(s29, [this.imageIndex, this.textIndex,
                                    this.checkBoxIndex], u29);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, p28, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 137, col: 5 });
                    ViewPU.create(r28);
                    let s28 = () => {
                        return {
                            title: this.title,
                            content: this.content,
                            checkTips: this.checkTips,
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((w28, x28) => {
                                    ForEach.create();
                                    const y28 = a29 => {
                                        const b29 = a29;
                                        this.observeComponentCreation2((d29, e29) => {
                                            If.create();
                                            if (b29 === this.imageIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.imagePart.bind(this)();
                                                });
                                            } else if (b29 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((o29, p29) => {
                                                        Column.create();
                                                        Column.padding({
                                                            top: {
                                                                'id': -1,
                                                                'type': 10002,
                                                                params: ['sys.float.padding_level8'],
                                                                'bundleName': '__harDefaultBundleName__',
                                                                'moduleName': '__harDefaultModuleName__'
                                                            }
                                                        });
                                                    }, Column);
                                                    this.observeComponentCreation2((m29, n29) => {
                                                        WithTheme.create({ theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.textPart.bind(this)();
                                                    WithTheme.pop();
                                                    Column.pop();
                                                });
                                            } else {
                                                this.ifElseBranchUpdateFunction(2, () => {
                                                    this.observeComponentCreation2((h29, i29) => {
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
                                    this.forEachUpdateFunction(w28,
                                        [this.imageIndex, this.textIndex, this.checkBoxIndex], y28);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    r28.paramsGenerator_ = s28;
                } else {
                    this.updateStateVarsOfChildByElmtId(p28, {});
                }
            }, { name: 'TipsDialogContentLayout' });
        }
    }

    checkBoxPart(v27 = null) {
        this.observeComponentCreation2((k28, l28) => {
            Row.create();
            Row.accessibilityGroup(true);
            Row.onClick(() => {
                this.isChecked = !this.isChecked;
                if (this.checkAction) {
                    this.checkAction(this.isChecked);
                }
            });
            Row.padding({ top: 8, bottom: 8 });
            Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((y27, z27) => {
            If.create();
            if (this.checkTips !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g28, h28) => {
                        Checkbox.create({ name: '', group: 'checkboxGroup' });
                        Checkbox.select(this.isChecked);
                        Checkbox.onChange((j28) => {
                            this.isChecked = j28;
                            if (this.checkAction) {
                                this.checkAction(j28);
                            }
                            if (this.onCheckedChange) {
                                this.onCheckedChange(j28);
                            }
                        });
                        Checkbox.accessibilityLevel('yes');
                        Checkbox.margin({
                            start: LengthMetrics.vp(0),
                            end: LengthMetrics.vp(CHECK_BOX_MARGIN_END)
                        });
                    }, Checkbox);
                    Checkbox.pop();
                    this.observeComponentCreation2((e28, f28) => {
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

    imagePart(o27 = null) {
        this.observeComponentCreation2((t27, u27) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((r27, s27) => {
            Image.create(this.imageRes);
            Image.objectFit(ImageFit.Contain);
            Image.borderRadius({
                'id': -1,
                'type': 10002,
                params: ['sys.float.corner_radius_level6'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Image.constraintSize({
                maxWidth: this.imageSize?.width ?? DEFAULT_IMAGE_SIZE,
                maxHeight: this.imageSize?.height ?? DEFAULT_IMAGE_SIZE
            });
        }, Image);
        Column.pop();
    }

    textPart(j26 = null) {
        this.observeComponentCreation2((m27, n27) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((k27, l27) => {
            Column.create();
            Column.margin({
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level8'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
        }, Column);
        this.observeComponentCreation2((a27, b27) => {
            If.create();
            if (this.title !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i27, j27) => {
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
                    this.observeComponentCreation2((g27, h27) => {
                        Text.create(this.title);
                        Text.fontSize(`${TITLE_S}fp`);
                        Text.fontWeight(FontWeight.Medium);
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
        this.observeComponentCreation2((o26, p26) => {
            If.create();
            if (this.content !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y26, z26) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((u26, v26) => {
                        Text.create(this.content);
                        Text.focusable(true);
                        Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
                        Text.focusBox({
                            strokeWidth: LengthMetrics.px(0)
                        });
                        Text.fontSize(this.getContentFontSize());
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(this.textAlignment);
                        Text.width('100%');
                        Text.onKeyEvent((x26) => {
                            if (x26) {
                                resolveKeyEvent(x26, this.contentScroller);
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
        this.marginOffset = 0 - PADDING_LEVEL_8;
    }

    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

class TipsDialogContentLayout extends ViewPU {
    constructor(b26, c26, d26, e26 = -1, f26 = undefined, g26) {
        super(b26, d26, e26, g26);
        if (typeof f26 === 'function') {
            this.paramsGenerator_ = f26;
        }
        this.title = null;
        this.content = null;
        this.checkTips = null;
        this.updateTextAlign = (i26) => {
        };
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(c26.minContentHeight, this, 'minContentHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.childrenSize = 3;
        this.setInitiallyProvidedValue(c26);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(a26) {
        if (a26.title !== undefined) {
            this.title = a26.title;
        }
        if (a26.content !== undefined) {
            this.content = a26.content;
        }
        if (a26.checkTips !== undefined) {
            this.checkTips = a26.checkTips;
        }
        if (a26.updateTextAlign !== undefined) {
            this.updateTextAlign = a26.updateTextAlign;
        }
        if (a26.dialogBuilder !== undefined) {
            this.dialogBuilder = a26.dialogBuilder;
        }
        if (a26.imageIndex !== undefined) {
            this.imageIndex = a26.imageIndex;
        }
        if (a26.textIndex !== undefined) {
            this.textIndex = a26.textIndex;
        }
        if (a26.checkBoxIndex !== undefined) {
            this.checkBoxIndex = a26.checkBoxIndex;
        }
        if (a26.childrenSize !== undefined) {
            this.childrenSize = a26.childrenSize;
        }
    }

    updateStateVars(z25) {
    }

    purgeVariableDependenciesOnElmtId(y25) {
        this.__minContentHeight.purgeDependencyOnElmtId(y25);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(x25 = null) {
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(w25) {
        this.__minContentHeight.set(w25);
    }

    onPlaceChildren(p25, q25, r25) {
        let s25 = 0;
        let t25 = 0;
        for (let u25 = 0; u25 < q25.length; u25++) {
            let v25 = q25[u25];
            v25.layout({ x: s25, y: t25 });
            t25 += v25.measureResult.height;
        }
    }

    onMeasureSize(x24, y24, z24) {
        let a25 = { width: Number(z24.maxWidth), height: 0 };
        if (y24.length < this.childrenSize) {
            return a25;
        }
        let b25 = 0;
        let c25 = 0;
        if (this.checkTips !== null) {
            let m25 = y24[this.checkBoxIndex];
            let n25 = {
                maxWidth: z24.maxWidth,
                minHeight: CHECKBOX_CONTAINER_HEIGHT,
                maxHeight: z24.maxHeight
            };
            let o25 = m25.measure(n25);
            c25 = o25.height;
            b25 += c25;
        }
        let d25 = y24[this.imageIndex];
        let e25 = 0;
        if (this.title !== null || this.content !== null) {
            e25 = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
        }
        let f25 = Number(z24.maxHeight) - c25 - e25;
        let g25 = {
            maxWidth: z24.maxWidth,
            maxHeight: f25
        };
        let h25 = d25.measure(g25);
        b25 += h25.height;
        if (this.title !== null || this.content !== null) {
            let i25 = y24[this.textIndex];
            this.updateTextAlign(a25.width);
            let j25 = Number(z24.maxHeight) - h25.height - c25;
            let k25 = {
                maxWidth: z24.maxWidth,
                maxHeight: Math.max(j25, TEXT_MIN_HEIGHT)
            };
            let l25 = i25.measure(k25);
            b25 += l25.height;
        }
        a25.height = b25;
        this.minContentHeight = Math.max(c25 + h25.height + e25, MIN_CONTENT_HEIGHT);
        return a25;
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.dialogBuilder.bind(this)();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

export class SelectDialog extends ViewPU {
    constructor(r24, s24, t24, u24 = -1, v24 = undefined, w24) {
        super(r24, t24, u24, w24);
        if (typeof v24 === 'function') {
            this.paramsGenerator_ = v24;
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
        this.setInitiallyProvidedValue(s24);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(q24) {
        if (q24.controller !== undefined) {
            this.controller = q24.controller;
        }
        if (q24.title !== undefined) {
            this.title = q24.title;
        }
        if (q24.content !== undefined) {
            this.content = q24.content;
        }
        if (q24.confirm !== undefined) {
            this.confirm = q24.confirm;
        }
        if (q24.radioContent !== undefined) {
            this.radioContent = q24.radioContent;
        }
        if (q24.buttons !== undefined) {
            this.buttons = q24.buttons;
        }
        if (q24.contentPadding !== undefined) {
            this.contentPadding = q24.contentPadding;
        }
        if (q24.isFocus !== undefined) {
            this.isFocus = q24.isFocus;
        }
        if (q24.currentFocusIndex !== undefined) {
            this.currentFocusIndex = q24.currentFocusIndex;
        }
        if (q24.radioHeight !== undefined) {
            this.radioHeight = q24.radioHeight;
        }
        if (q24.itemHeight !== undefined) {
            this.itemHeight = q24.itemHeight;
        }
        if (q24.selectedIndex !== undefined) {
            this.selectedIndex = q24.selectedIndex;
        }
        if (q24.contentBuilder !== undefined) {
            this.contentBuilder = q24.contentBuilder;
        }
        if (q24.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = q24.fontColorWithTheme;
        }
        if (q24.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = q24.dividerColorWithTheme;
        }
        if (q24.theme !== undefined) {
            this.theme = q24.theme;
        }
        if (q24.themeColorMode !== undefined) {
            this.themeColorMode = q24.themeColorMode;
        }
        if (q24.contentScroller !== undefined) {
            this.contentScroller = q24.contentScroller;
        }
        if (q24.fontSizeScale !== undefined) {
            this.fontSizeScale = q24.fontSizeScale;
        }
        if (q24.minContentHeight !== undefined) {
            this.minContentHeight = q24.minContentHeight;
        }
    }

    updateStateVars(p24) {
    }

    purgeVariableDependenciesOnElmtId(o24) {
        this.__selectedIndex.purgeDependencyOnElmtId(o24);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(o24);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(o24);
        this.__fontSizeScale.purgeDependencyOnElmtId(o24);
        this.__minContentHeight.purgeDependencyOnElmtId(o24);
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

    setController(n24) {
        this.controller = n24;
    }

    get selectedIndex() {
        return this.__selectedIndex.get();
    }

    set selectedIndex(m24) {
        this.__selectedIndex.set(m24);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(l24) {
        this.__fontColorWithTheme.set(l24);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(k24) {
        this.__dividerColorWithTheme.set(k24);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(j24) {
        this.__fontSizeScale.set(j24);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(i24) {
        this.__minContentHeight.set(i24);
    }

    buildContent(j21 = null) {
        this.observeComponentCreation2((c24, d24) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.onDidScroll((f24, g24) => {
                let h24 = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (g24 > 0) {
                            this.contentScroller.scrollBy(0, h24);
                        } else if (g24 < 0) {
                            this.contentScroller.scrollBy(0, 0 - h24);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((a24, b24) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((q23, r23) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y23, z23) => {
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
                    this.observeComponentCreation2((w23, x23) => {
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
        this.observeComponentCreation2((n23, o23) => {
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
        this.observeComponentCreation2((p21, q21) => {
            ForEach.create();
            const r21 = (t21, u21) => {
                const v21 = t21;
                {
                    const w21 = (l23, m23) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(l23);
                        x21(l23, m23);
                        if (!m23) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const x21 = (g23, h23) => {
                        ListItem.create(y21, true);
                        ListItem.onSizeChange((j23, k23) => {
                            this.itemHeight = Number(k23.height);
                        });
                    };
                    const y21 = (c22, d22) => {
                        w21(c22, d22);
                        this.observeComponentCreation2((e23, f23) => {
                            Column.create();
                            Column.padding({
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
                        }, Column);
                        this.observeComponentCreation2((b23, c23) => {
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
                            Button.focusBox({
                                margin: { value: -2, unit: LengthUnit.VP }
                            });
                            Button.onClick(() => {
                                this.selectedIndex = u21;
                                v21.action && v21.action();
                                this.controller?.close();
                            });
                        }, Button);
                        this.observeComponentCreation2((z22, a23) => {
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
                        this.observeComponentCreation2((x22, y22) => {
                            Text.create(v21.title);
                            Text.fontSize(`${BODY_L}fp`);
                            Text.fontWeight(FontWeight.Medium);
                            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                            Text.layoutWeight(1);
                        }, Text);
                        Text.pop();
                        this.observeComponentCreation2((r22, s22) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === u21);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(u21));
                            Radio.focusable(false);
                            Radio.accessibilityLevel('no');
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = u21;
                                if (u21 === FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (u21 === this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((v22, w22) => {
                                this.radioHeight = Number(w22.height);
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((k22, l22) => {
                            If.create();
                            if (u21 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((p22, q22) => {
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
                    this.observeComponentCreation2(x21, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(p21, this.radioContent, r21, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((h21, i21) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((b21, c21) => {
                if (c21) {
                    let d21 = new CustomDialogContentComponent(this, {
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
                    }, undefined, b21, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 514, col: 5 });
                    ViewPU.create(d21);
                    let e21 = () => {
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
                    d21.paramsGenerator_ = e21;
                } else {
                    this.updateStateVarsOfChildByElmtId(b21, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
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
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

class ConfirmDialogContentLayout extends ViewPU {
    constructor(r20, s20, t20, u20 = -1, v20 = undefined, w20) {
        super(r20, t20, u20, w20);
        if (typeof v20 === 'function') {
            this.paramsGenerator_ = v20;
        }
        this.textIndex = 0;
        this.checkboxIndex = 1;
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(s20.minContentHeight, this, 'minContentHeight');
        this.updateTextAlign = (y20) => {
        };
        this.dialogBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(s20);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(q20) {
        if (q20.textIndex !== undefined) {
            this.textIndex = q20.textIndex;
        }
        if (q20.checkboxIndex !== undefined) {
            this.checkboxIndex = q20.checkboxIndex;
        }
        if (q20.updateTextAlign !== undefined) {
            this.updateTextAlign = q20.updateTextAlign;
        }
        if (q20.dialogBuilder !== undefined) {
            this.dialogBuilder = q20.dialogBuilder;
        }
    }

    updateStateVars(p20) {
    }

    purgeVariableDependenciesOnElmtId(o20) {
        this.__minContentHeight.purgeDependencyOnElmtId(o20);
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

    doNothingBuilder(m20 = null) {
    }

    onPlaceChildren(f20, g20, h20) {
        let i20 = 0;
        let j20 = 0;
        for (let k20 = 0; k20 < g20.length; k20++) {
            let l20 = g20[k20];
            l20.layout({ x: i20, y: j20 });
            j20 += l20.measureResult.height;
        }
    }

    onMeasureSize(t19, u19, v19) {
        let w19 = { width: Number(v19.maxWidth), height: 0 };
        let x19 = 2;
        if (u19.length < x19) {
            return w19;
        }
        this.updateTextAlign(w19.width);
        let y19 = 0;
        let z19 = u19[this.checkboxIndex];
        let a20 = {
            maxWidth: v19.maxWidth,
            minHeight: CHECKBOX_CONTAINER_HEIGHT,
            maxHeight: v19.maxHeight
        };
        let b20 = z19.measure(a20);
        y19 += b20.height;
        let c20 = u19[this.textIndex];
        let d20 = {
            maxWidth: v19.maxWidth,
            maxHeight: Number(v19.maxHeight) - y19
        };
        let e20 = c20.measure(d20);
        y19 += e20.height;
        w19.height = y19;
        this.minContentHeight = Math.max(b20.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT);
        return w19;
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.dialogBuilder.bind(this)();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

export class ConfirmDialog extends ViewPU {
    constructor(l19, m19, n19, o19 = -1, p19 = undefined, q19) {
        super(l19, n19, o19, q19);
        if (typeof p19 === 'function') {
            this.paramsGenerator_ = p19;
        }
        this.controller = undefined;
        this.title = '';
        this.content = '';
        this.checkTips = '';
        this.__isChecked = new ObservedPropertySimplePU(false, this, 'isChecked');
        this.primaryButton = { value: '' };
        this.secondaryButton = { value: '' };
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
        this.updateTextAlign = (s19) => {
            if (this.content) {
                this.textAlign = getTextAlign(s19, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.setInitiallyProvidedValue(m19);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(k19) {
        if (k19.controller !== undefined) {
            this.controller = k19.controller;
        }
        if (k19.title !== undefined) {
            this.title = k19.title;
        }
        if (k19.content !== undefined) {
            this.content = k19.content;
        }
        if (k19.checkTips !== undefined) {
            this.checkTips = k19.checkTips;
        }
        if (k19.isChecked !== undefined) {
            this.isChecked = k19.isChecked;
        }
        if (k19.primaryButton !== undefined) {
            this.primaryButton = k19.primaryButton;
        }
        if (k19.secondaryButton !== undefined) {
            this.secondaryButton = k19.secondaryButton;
        }
        if (k19.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = k19.fontColorWithTheme;
        }
        if (k19.theme !== undefined) {
            this.theme = k19.theme;
        }
        if (k19.themeColorMode !== undefined) {
            this.themeColorMode = k19.themeColorMode;
        }
        if (k19.onCheckedChange !== undefined) {
            this.onCheckedChange = k19.onCheckedChange;
        }
        if (k19.contentScroller !== undefined) {
            this.contentScroller = k19.contentScroller;
        }
        if (k19.buttons !== undefined) {
            this.buttons = k19.buttons;
        }
        if (k19.textAlign !== undefined) {
            this.textAlign = k19.textAlign;
        }
        if (k19.marginOffset !== undefined) {
            this.marginOffset = k19.marginOffset;
        }
        if (k19.fontSizeScale !== undefined) {
            this.fontSizeScale = k19.fontSizeScale;
        }
        if (k19.minContentHeight !== undefined) {
            this.minContentHeight = k19.minContentHeight;
        }
        if (k19.textIndex !== undefined) {
            this.textIndex = k19.textIndex;
        }
        if (k19.checkboxIndex !== undefined) {
            this.checkboxIndex = k19.checkboxIndex;
        }
        if (k19.updateTextAlign !== undefined) {
            this.updateTextAlign = k19.updateTextAlign;
        }
    }

    updateStateVars(j19) {
    }

    purgeVariableDependenciesOnElmtId(i19) {
        this.__isChecked.purgeDependencyOnElmtId(i19);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(i19);
        this.__textAlign.purgeDependencyOnElmtId(i19);
        this.__fontSizeScale.purgeDependencyOnElmtId(i19);
        this.__minContentHeight.purgeDependencyOnElmtId(i19);
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

    setController(h19) {
        this.controller = h19;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(g19) {
        this.__isChecked.set(g19);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(f19) {
        this.__fontColorWithTheme.set(f19);
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(e19) {
        this.__textAlign.set(e19);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(d19) {
        this.__fontSizeScale.set(d19);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(c19) {
        this.__minContentHeight.set(c19);
    }

    textBuilder(n18 = null) {
        this.observeComponentCreation2((a19, b19) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((y18, z18) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((w18, x18) => {
            Column.create();
            Column.margin({
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level8'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
        }, Column);
        this.observeComponentCreation2((s18, t18) => {
            Text.create(this.content);
            Text.focusable(true);
            Text.defaultFocus(!(this.primaryButton?.value || this.secondaryButton?.value));
            Text.focusBox({
                strokeWidth: LengthMetrics.px(0)
            });
            Text.fontSize(`${BODY_L}fp`);
            Text.fontWeight(FontWeight.Medium);
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.textAlign(this.textAlign);
            Text.onKeyEvent((v18) => {
                if (v18) {
                    resolveKeyEvent(v18, this.contentScroller);
                }
            });
            Text.width('100%');
        }, Text);
        Text.pop();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }

    checkBoxBuilder(a18 = null) {
        this.observeComponentCreation2((k18, l18) => {
            Row.create();
            Row.accessibilityGroup(true);
            Row.onClick(() => {
                this.isChecked = !this.isChecked;
            });
            Row.width('100%');
            Row.padding({ top: 8, bottom: 8 });
        }, Row);
        this.observeComponentCreation2((g18, h18) => {
            Checkbox.create({ name: '', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((j18) => {
                this.isChecked = j18;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.accessibilityLevel('yes');
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(CHECK_BOX_MARGIN_END) });
        }, Checkbox);
        Checkbox.pop();
        this.observeComponentCreation2((e18, f18) => {
            Text.create(this.checkTips);
            Text.fontSize(`${BODY_M}fp`);
            Text.fontWeight(FontWeight.Medium);
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.maxLines(CONTENT_MAX_LINES);
            Text.focusable(false);
            Text.layoutWeight(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
        }, Text);
        Text.pop();
        Row.pop();
    }

    buildContent(g16 = null) {
        {
            this.observeComponentCreation2((i16, j16) => {
                if (j16) {
                    let k16 = new ConfirmDialogContentLayout(this, {
                        minContentHeight: this.__minContentHeight, updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((i17, j17) => {
                                ForEach.create();
                                const k17 = m17 => {
                                    const n17 = m17;
                                    this.observeComponentCreation2((p17, q17) => {
                                        If.create();
                                        if (n17 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((y17, z17) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.textBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else if (n17 === this.checkboxIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((u17, v17) => {
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
                                this.forEachUpdateFunction(i17, [this.textIndex, this.checkboxIndex],
                                    k17);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, i16, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 720, col: 5 });
                    ViewPU.create(k16);
                    let l16 = () => {
                        return {
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((p16, q16) => {
                                    ForEach.create();
                                    const r16 = t16 => {
                                        const u16 = t16;
                                        this.observeComponentCreation2((w16, x16) => {
                                            If.create();
                                            if (u16 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((f17, g17) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.textBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else if (u16 === this.checkboxIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((b17, c17) => {
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
                                    this.forEachUpdateFunction(p16, [this.textIndex, this.checkboxIndex],
                                        r16);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    k16.paramsGenerator_ = l16;
                } else {
                    this.updateStateVarsOfChildByElmtId(i16, {});
                }
            }, { name: 'ConfirmDialogContentLayout' });
        }
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((e16, f16) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((y15, z15) => {
                if (z15) {
                    let a16 = new CustomDialogContentComponent(this, {
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
                    }, undefined, y15, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 736, col: 5 });
                    ViewPU.create(a16);
                    let b16 = () => {
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
                    a16.paramsGenerator_ = b16;
                } else {
                    this.updateStateVarsOfChildByElmtId(y15, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
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
        this.marginOffset = 0 - PADDING_LEVEL_8;
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
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

export class AlertDialog extends ViewPU {
    constructor(q15, r15, s15, t15 = -1, u15 = undefined, v15) {
        super(q15, s15, t15, v15);
        if (typeof u15 === 'function') {
            this.paramsGenerator_ = u15;
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
        this.setInitiallyProvidedValue(r15);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(p15) {
        if (p15.controller !== undefined) {
            this.controller = p15.controller;
        }
        if (p15.primaryTitle !== undefined) {
            this.primaryTitle = p15.primaryTitle;
        }
        if (p15.secondaryTitle !== undefined) {
            this.secondaryTitle = p15.secondaryTitle;
        }
        if (p15.content !== undefined) {
            this.content = p15.content;
        }
        if (p15.primaryButton !== undefined) {
            this.primaryButton = p15.primaryButton;
        }
        if (p15.secondaryButton !== undefined) {
            this.secondaryButton = p15.secondaryButton;
        }
        if (p15.buttons !== undefined) {
            this.buttons = p15.buttons;
        }
        if (p15.textAlign !== undefined) {
            this.textAlign = p15.textAlign;
        }
        if (p15.contentScroller !== undefined) {
            this.contentScroller = p15.contentScroller;
        }
        if (p15.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = p15.fontColorWithTheme;
        }
        if (p15.theme !== undefined) {
            this.theme = p15.theme;
        }
        if (p15.themeColorMode !== undefined) {
            this.themeColorMode = p15.themeColorMode;
        }
        if (p15.fontSizeScale !== undefined) {
            this.fontSizeScale = p15.fontSizeScale;
        }
        if (p15.minContentHeight !== undefined) {
            this.minContentHeight = p15.minContentHeight;
        }
    }

    updateStateVars(o15) {
    }

    purgeVariableDependenciesOnElmtId(n15) {
        this.__textAlign.purgeDependencyOnElmtId(n15);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(n15);
        this.__fontSizeScale.purgeDependencyOnElmtId(n15);
        this.__minContentHeight.purgeDependencyOnElmtId(n15);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(m15) {
        this.controller = m15;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(l15) {
        this.__textAlign.set(l15);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(k15) {
        this.__fontColorWithTheme.set(k15);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(j15) {
        this.__fontSizeScale.set(j15);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(i15) {
        this.__minContentHeight.set(i15);
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((g15, h15) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((a15, b15) => {
                if (b15) {
                    let c15 = new CustomDialogContentComponent(this, {
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
                    }, undefined, a15, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 794, col: 5 });
                    ViewPU.create(c15);
                    let d15 = () => {
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
                    c15.paramsGenerator_ = d15;
                } else {
                    this.updateStateVarsOfChildByElmtId(a15, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    AlertDialogContentBuilder(j14 = null) {
        this.observeComponentCreation2((w14, x14) => {
            Column.create();
            Column.margin({ right: `${this.getMargin()}vp`, });
        }, Column);
        this.observeComponentCreation2((u14, v14) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((n14, o14) => {
            Text.create(this.content);
            Text.focusable(true);
            Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
            Text.focusBox({
                strokeWidth: LengthMetrics.px(0)
            });
            Text.fontSize(`${BODY_L}fp`);
            Text.fontWeight(this.getFontWeight());
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.margin({
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level8'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            });
            Text.width(`calc(100% - ${PADDING_LEVEL_8}vp)`);
            Text.textAlign(this.textAlign);
            Text.onAreaChange((s14, t14) => {
                this.updateTextAlign(Number(t14.width));
            });
            Text.onKeyEvent((r14) => {
                if (r14) {
                    resolveKeyEvent(r14, this.contentScroller);
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

    updateTextAlign(i14) {
        this.textAlign = getTextAlign(i14, this.content, `${BODY_L * this.fontSizeScale}vp`);
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

    getMargin() {
        return 0 - PADDING_LEVEL_8;
    }

    getFontWeight() {
        if (this.primaryTitle || this.secondaryTitle) {
            return FontWeight.Regular;
        }
        return FontWeight.Medium;
    }

    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

export class CustomContentDialog extends ViewPU {
    constructor(c14, d14, e14, f14 = -1, g14 = undefined, h14) {
        super(c14, e14, f14, h14);
        if (typeof g14 === 'function') {
            this.paramsGenerator_ = g14;
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
        this.setInitiallyProvidedValue(d14);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(b14) {
        if (b14.controller !== undefined) {
            this.controller = b14.controller;
        }
        if (b14.primaryTitle !== undefined) {
            this.primaryTitle = b14.primaryTitle;
        }
        if (b14.secondaryTitle !== undefined) {
            this.secondaryTitle = b14.secondaryTitle;
        }
        if (b14.contentBuilder !== undefined) {
            this.contentBuilder = b14.contentBuilder;
        }
        if (b14.contentAreaPadding !== undefined) {
            this.contentAreaPadding = b14.contentAreaPadding;
        }
        if (b14.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = b14.localizedContentAreaPadding;
        }
        if (b14.buttons !== undefined) {
            this.buttons = b14.buttons;
        }
        if (b14.theme !== undefined) {
            this.theme = b14.theme;
        }
        if (b14.themeColorMode !== undefined) {
            this.themeColorMode = b14.themeColorMode;
        }
        if (b14.fontSizeScale !== undefined) {
            this.fontSizeScale = b14.fontSizeScale;
        }
        if (b14.minContentHeight !== undefined) {
            this.minContentHeight = b14.minContentHeight;
        }
    }

    updateStateVars(a14) {
    }

    purgeVariableDependenciesOnElmtId(z13) {
        this.__fontSizeScale.purgeDependencyOnElmtId(z13);
        this.__minContentHeight.purgeDependencyOnElmtId(z13);
    }

    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(y13) {
        this.controller = y13;
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(x13) {
        this.__fontSizeScale.set(x13);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(w13) {
        this.__minContentHeight.set(w13);
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((u13, v13) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((o13, p13) => {
                if (p13) {
                    let q13 = new CustomDialogContentComponent(this, {
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
                    }, undefined, o13, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 890, col: 5 });
                    ViewPU.create(q13);
                    let r13 = () => {
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
                    q13.paramsGenerator_ = r13;
                } else {
                    this.updateStateVarsOfChildByElmtId(o13, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

class CustomDialogControllerExtend extends CustomDialogController {
    constructor(l13) {
        super(l13);
        this.arg_ = l13;
    }
}

class CustomDialogLayout extends ViewPU {
    constructor(f13, g13, h13, i13 = -1, j13 = undefined, k13) {
        super(f13, h13, i13, k13);
        if (typeof j13 === 'function') {
            this.paramsGenerator_ = j13;
        }
        this.__titleHeight = new SynchedPropertySimpleTwoWayPU(g13.titleHeight, this, "titleHeight");
        this.__buttonHeight = new SynchedPropertySimpleTwoWayPU(g13.buttonHeight, this, "buttonHeight");
        this.__titleMinHeight = new SynchedPropertyObjectTwoWayPU(g13.titleMinHeight, this, "titleMinHeight");
        this.dialogBuilder = this.doNothingBuilder;
        this.titleIndex = 0;
        this.contentIndex = 1;
        this.buttonIndex = 2;
        this.setInitiallyProvidedValue(g13);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(e13) {
        if (e13.dialogBuilder !== undefined) {
            this.dialogBuilder = e13.dialogBuilder;
        }
        if (e13.titleIndex !== undefined) {
            this.titleIndex = e13.titleIndex;
        }
        if (e13.contentIndex !== undefined) {
            this.contentIndex = e13.contentIndex;
        }
        if (e13.buttonIndex !== undefined) {
            this.buttonIndex = e13.buttonIndex;
        }
    }

    updateStateVars(d13) {
    }

    purgeVariableDependenciesOnElmtId(c13) {
        this.__titleHeight.purgeDependencyOnElmtId(c13);
        this.__buttonHeight.purgeDependencyOnElmtId(c13);
        this.__titleMinHeight.purgeDependencyOnElmtId(c13);
    }

    aboutToBeDeleted() {
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__titleMinHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(b13 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(a13) {
        this.__titleHeight.set(a13);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(z12) {
        this.__buttonHeight.set(z12);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(y12) {
        this.__titleMinHeight.set(y12);
    }

    onPlaceChildren(r12, s12, t12) {
        let u12 = 0;
        let v12 = 0;
        for (let w12 = 0; w12 < s12.length; w12++) {
            let x12 = s12[w12];
            x12.layout({ x: u12, y: v12 });
            v12 += x12.measureResult.height;
        }
    }

    onMeasureSize(d12, e12, f12) {
        let g12 = { width: Number(f12.maxWidth), height: 0 };
        let h12 = 3;
        if (e12.length < h12) {
            return g12;
        }
        let i12 = 0;
        let j12 = e12[this.titleIndex];
        let k12 = {
            maxWidth: f12.maxWidth,
            minHeight: this.titleMinHeight,
            maxHeight: f12.maxHeight
        };
        let l12 = j12.measure(k12);
        this.titleHeight = l12.height;
        i12 += this.titleHeight;
        let m12 = e12[this.buttonIndex];
        let n12 = m12.measure(f12);
        this.buttonHeight = n12.height;
        i12 += this.buttonHeight;
        let o12 = e12[this.contentIndex];
        let p12 = {
            maxWidth: f12.maxWidth,
            maxHeight: Number(f12.maxHeight) - i12
        };
        let q12 = o12.measure(p12);
        i12 += q12.height;
        g12.height = i12;
        return g12;
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.dialogBuilder.bind(this)();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

class CustomDialogContentComponent extends ViewPU {
    constructor(x11, y11, z11, a12 = -1, b12 = undefined, c12) {
        super(x11, z11, a12, c12);
        if (typeof b12 === 'function') {
            this.paramsGenerator_ = b12;
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
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(y11.minContentHeight, this, 'minContentHeight');
        this.__titleHeight = new ObservedPropertySimplePU(0, this, 'titleHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
        this.__contentMaxHeight = new ObservedPropertyObjectPU('100%', this, 'contentMaxHeight');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(y11.fontSizeScale, this, 'fontSizeScale');
        this.__customStyle = new ObservedPropertySimplePU(undefined, this, 'customStyle');
        this.__buttonMaxFontSize = new ObservedPropertyObjectPU(`${BODY_L}fp`, this, 'buttonMaxFontSize');
        this.__buttonMinFontSize = new ObservedPropertyObjectPU(9, this, 'buttonMinFontSize');
        this.__primaryTitleMaxFontSize = new ObservedPropertyObjectPU(`${TITLE_S}fp`, this, 'primaryTitleMaxFontSize');
        this.__primaryTitleMinFontSize = new ObservedPropertyObjectPU(`${BODY_L}fp`, this, 'primaryTitleMinFontSize');
        this.__secondaryTitleMaxFontSize = new ObservedPropertyObjectPU(`${SUBTITLE_S}fp`, this, 'secondaryTitleMaxFontSize');
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
        this.setInitiallyProvidedValue(y11);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(w11) {
        if (w11.controller !== undefined) {
            this.controller = w11.controller;
        }
        if (w11.primaryTitle !== undefined) {
            this.primaryTitle = w11.primaryTitle;
        }
        if (w11.secondaryTitle !== undefined) {
            this.secondaryTitle = w11.secondaryTitle;
        }
        if (w11.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = w11.localizedContentAreaPadding;
        }
        if (w11.contentBuilder !== undefined) {
            this.contentBuilder = w11.contentBuilder;
        }
        if (w11.buttons !== undefined) {
            this.buttons = w11.buttons;
        }
        if (w11.contentAreaPadding !== undefined) {
            this.contentAreaPadding = w11.contentAreaPadding;
        }
        if (w11.keyIndex !== undefined) {
            this.keyIndex = w11.keyIndex;
        }
        if (w11.theme !== undefined) {
            this.theme = w11.theme;
        }
        if (w11.themeColorMode !== undefined) {
            this.themeColorMode = w11.themeColorMode;
        }
        if (w11.titleHeight !== undefined) {
            this.titleHeight = w11.titleHeight;
        }
        if (w11.buttonHeight !== undefined) {
            this.buttonHeight = w11.buttonHeight;
        }
        if (w11.contentMaxHeight !== undefined) {
            this.contentMaxHeight = w11.contentMaxHeight;
        }
        if (w11.customStyle !== undefined) {
            this.customStyle = w11.customStyle;
        }
        if (w11.buttonMaxFontSize !== undefined) {
            this.buttonMaxFontSize = w11.buttonMaxFontSize;
        }
        if (w11.buttonMinFontSize !== undefined) {
            this.buttonMinFontSize = w11.buttonMinFontSize;
        }
        if (w11.primaryTitleMaxFontSize !== undefined) {
            this.primaryTitleMaxFontSize = w11.primaryTitleMaxFontSize;
        }
        if (w11.primaryTitleMinFontSize !== undefined) {
            this.primaryTitleMinFontSize = w11.primaryTitleMinFontSize;
        }
        if (w11.secondaryTitleMaxFontSize !== undefined) {
            this.secondaryTitleMaxFontSize = w11.secondaryTitleMaxFontSize;
        }
        if (w11.secondaryTitleMinFontSize !== undefined) {
            this.secondaryTitleMinFontSize = w11.secondaryTitleMinFontSize;
        }
        if (w11.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = w11.primaryTitleFontColorWithTheme;
        }
        if (w11.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = w11.secondaryTitleFontColorWithTheme;
        }
        if (w11.titleTextAlign !== undefined) {
            this.titleTextAlign = w11.titleTextAlign;
        }
        if (w11.isButtonVertical !== undefined) {
            this.isButtonVertical = w11.isButtonVertical;
        }
        if (w11.titleMinHeight !== undefined) {
            this.titleMinHeight = w11.titleMinHeight;
        }
        if (w11.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = w11.isFollowingSystemFontScale;
        }
        if (w11.appMaxFontScale !== undefined) {
            this.appMaxFontScale = w11.appMaxFontScale;
        }
        if (w11.titleIndex !== undefined) {
            this.titleIndex = w11.titleIndex;
        }
        if (w11.contentIndex !== undefined) {
            this.contentIndex = w11.contentIndex;
        }
        if (w11.buttonIndex !== undefined) {
            this.buttonIndex = w11.buttonIndex;
        }
    }

    updateStateVars(v11) {
    }

    purgeVariableDependenciesOnElmtId(u11) {
        this.__minContentHeight.purgeDependencyOnElmtId(u11);
        this.__titleHeight.purgeDependencyOnElmtId(u11);
        this.__buttonHeight.purgeDependencyOnElmtId(u11);
        this.__contentMaxHeight.purgeDependencyOnElmtId(u11);
        this.__fontSizeScale.purgeDependencyOnElmtId(u11);
        this.__customStyle.purgeDependencyOnElmtId(u11);
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(u11);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(u11);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(u11);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(u11);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(u11);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(u11);
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(u11);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(u11);
        this.__titleTextAlign.purgeDependencyOnElmtId(u11);
        this.__isButtonVertical.purgeDependencyOnElmtId(u11);
        this.__titleMinHeight.purgeDependencyOnElmtId(u11);
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

    set minContentHeight(t11) {
        this.__minContentHeight.set(t11);
    }

    defaultContentBuilder(s11 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(r11) {
        this.__titleHeight.set(r11);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(q11) {
        this.__buttonHeight.set(q11);
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(p11) {
        this.__contentMaxHeight.set(p11);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(o11) {
        this.__fontSizeScale.set(o11);
    }

    get customStyle() {
        return this.__customStyle.get();
    }

    set customStyle(n11) {
        this.__customStyle.set(n11);
    }

    get buttonMaxFontSize() {
        return this.__buttonMaxFontSize.get();
    }

    set buttonMaxFontSize(m11) {
        this.__buttonMaxFontSize.set(m11);
    }

    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }

    set buttonMinFontSize(l11) {
        this.__buttonMinFontSize.set(l11);
    }

    get primaryTitleMaxFontSize() {
        return this.__primaryTitleMaxFontSize.get();
    }

    set primaryTitleMaxFontSize(k11) {
        this.__primaryTitleMaxFontSize.set(k11);
    }

    get primaryTitleMinFontSize() {
        return this.__primaryTitleMinFontSize.get();
    }

    set primaryTitleMinFontSize(j11) {
        this.__primaryTitleMinFontSize.set(j11);
    }

    get secondaryTitleMaxFontSize() {
        return this.__secondaryTitleMaxFontSize.get();
    }

    set secondaryTitleMaxFontSize(i11) {
        this.__secondaryTitleMaxFontSize.set(i11);
    }

    get secondaryTitleMinFontSize() {
        return this.__secondaryTitleMinFontSize.get();
    }

    set secondaryTitleMinFontSize(h11) {
        this.__secondaryTitleMinFontSize.set(h11);
    }

    get primaryTitleFontColorWithTheme() {
        return this.__primaryTitleFontColorWithTheme.get();
    }

    set primaryTitleFontColorWithTheme(g11) {
        this.__primaryTitleFontColorWithTheme.set(g11);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(f11) {
        this.__secondaryTitleFontColorWithTheme.set(f11);
    }

    get titleTextAlign() {
        return this.__titleTextAlign.get();
    }

    set titleTextAlign(e11) {
        this.__titleTextAlign.set(e11);
    }

    get isButtonVertical() {
        return this.__isButtonVertical.get();
    }

    set isButtonVertical(d11) {
        this.__isButtonVertical.set(d11);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(c11) {
        this.__titleMinHeight.set(c11);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((a11, b11) => {
            WithTheme.create({ theme: this.theme, colorMode: this.themeColorMode });
        }, WithTheme);
        this.observeComponentCreation2((y10, z10) => {
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
        this.observeComponentCreation2((w10, x10) => {
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
                left: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_dialog_margin_start'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                right: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_dialog_margin_end'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_dialog_margin_bottom'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
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
            this.observeComponentCreation2((s8, t8) => {
                if (t8) {
                    let u8 = new CustomDialogLayout(this, {
                        buttonHeight: this.__buttonHeight,
                        titleHeight: this.__titleHeight,
                        titleMinHeight: this.__titleMinHeight,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((y9, z9) => {
                                ForEach.create();
                                const a10 = c10 => {
                                    const d10 = c10;
                                    this.observeComponentCreation2((f10, g10) => {
                                        If.create();
                                        if (d10 === this.titleIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((u10, v10) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.titleBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else if (d10 === this.contentIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((q10, r10) => {
                                                    Column.create();
                                                    Column.padding(this.getContentPadding());
                                                }, Column);
                                                this.observeComponentCreation2((o10, p10) => {
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
                                                this.observeComponentCreation2((j10, k10) => {
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
                                this.forEachUpdateFunction(y9, [this.titleIndex, this.contentIndex,
                                    this.buttonIndex], a10);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, s8, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1028, col: 11 });
                    ViewPU.create(u8);
                    let v8 = () => {
                        return {
                            buttonHeight: this.buttonHeight,
                            titleHeight: this.titleHeight,
                            titleMinHeight: this.titleMinHeight,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((z8, a9) => {
                                    ForEach.create();
                                    const b9 = d9 => {
                                        const e9 = d9;
                                        this.observeComponentCreation2((g9, h9) => {
                                            If.create();
                                            if (e9 === this.titleIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((v9, w9) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.titleBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else if (e9 === this.contentIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((r9, s9) => {
                                                        Column.create();
                                                        Column.padding(this.getContentPadding());
                                                    }, Column);
                                                    this.observeComponentCreation2((p9, q9) => {
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
                                                    this.observeComponentCreation2((k9, l9) => {
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
                                    this.forEachUpdateFunction(z8, [this.titleIndex, this.contentIndex,
                                        this.buttonIndex], b9);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    u8.paramsGenerator_ = v8;
                } else {
                    this.updateStateVarsOfChildByElmtId(s8, {});
                }
            }, { name: 'CustomDialogLayout' });
        }
        Column.pop();
        Scroll.pop();
        WithTheme.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    onMeasureSize(e8, f8, g8) {
        let h8 = { width: e8.width, height: e8.height };
        let i8 = Number(g8.maxWidth);
        let j8 = Number(g8.maxHeight);
        this.fontSizeScale = this.updateFontScale();
        this.updateFontSize();
        this.isButtonVertical = this.isVerticalAlignButton(i8 - BUTTON_HORIZONTAL_MARGIN * 2);
        this.titleMinHeight = this.getTitleAreaMinHeight();
        let k8 = 0;
        f8.forEach((m8) => {
            this.contentMaxHeight = '100%';
            let n8 = m8.measure(g8);
            if (j8 - this.buttonHeight - this.titleHeight < this.minContentHeight) {
                this.contentMaxHeight = MAX_CONTENT_HEIGHT;
                n8 = m8.measure(g8);
            }
            k8 += n8.height;
        });
        h8.height = k8;
        h8.width = i8;
        return h8;
    }

    aboutToAppear() {
        let c8 = this.getUIContext();
        this.isFollowingSystemFontScale = c8.isFollowingSystemFontScale();
        this.appMaxFontScale = c8.getMaxFontScale();
        this.fontSizeScale = this.updateFontScale();
        if (this.controller && this.customStyle === undefined) {
            let d8 = this.controller;
            if (d8.arg_ && d8.arg_.customStyle &&
                d8.arg_.customStyle === true) {
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
            this.buttonMaxFontSize = BODY_L * MAX_FONT_SCALE + 'vp';
            this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE * MAX_FONT_SCALE + 'vp';
        } else {
            this.buttonMaxFontSize = BODY_L + 'fp';
            this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE + 'fp';
        }
    }

    updateFontScale() {
        try {
            let a8 = this.getUIContext();
            let b8 = a8.getHostContext()?.config.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(b8, this.appMaxFontScale);
        } catch (x7) {
            let y7 = x7.code;
            let z7 = x7.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${y7}, message: ${z7}`);
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

    titleBuilder(z6 = null) {
        this.observeComponentCreation2((v7, w7) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((t7, u7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((r7, s7) => {
            Text.create(this.primaryTitle);
            Text.fontWeight(FontWeight.Bold);
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
        this.observeComponentCreation2((k7, l7) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p7, q7) => {
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
        this.observeComponentCreation2((i7, j7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((g7, h7) => {
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
        let y6 = ALERT_TITLE_ALIGNMENT;
        if (y6 === TextAlign.Start) {
            this.titleTextAlign = TextAlign.Start;
        } else if (y6 === TextAlign.Center) {
            this.titleTextAlign = TextAlign.Center;
        } else if (y6 === TextAlign.End) {
            this.titleTextAlign = TextAlign.End;
        } else if (y6 === TextAlign.JUSTIFY) {
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

    ButtonBuilder(k6 = null) {
        this.observeComponentCreation2((w6, x6) => {
            Column.create();
            Column.width('100%');
            Column.padding(this.getOperationAreaPadding());
        }, Column);
        this.observeComponentCreation2((n6, o6) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s6, t6) => {
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

    buildSingleButton(p5, q5 = null) {
        this.observeComponentCreation2((s5, t5) => {
            If.create();
            if (this.isNewPropertiesHighPriority(p5)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i6, j6) => {
                        Button.createWithLabel(p5.value);
                        __Button__setButtonProperties(p5, this.controller);
                        Button.role(p5.role ?? ButtonRole.NORMAL);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (p5.background !== undefined && p5.fontColor !== undefined) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((e6, f6) => {
                        Button.createWithLabel(p5.value);
                        __Button__setButtonProperties(p5, this.controller);
                        Button.backgroundColor(p5.background);
                        Button.fontColor(p5.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (p5.background !== undefined) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((a6, b6) => {
                        Button.createWithLabel(p5.value);
                        __Button__setButtonProperties(p5, this.controller);
                        Button.backgroundColor(p5.background);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.observeComponentCreation2((w5, x5) => {
                        Button.createWithLabel(p5.value);
                        __Button__setButtonProperties(p5, this.controller);
                        Button.fontColor(p5.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
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

    buildHorizontalAlignButtons(y4 = null) {
        this.observeComponentCreation2((a5, b5) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n5, o5) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[0]);
                    this.observeComponentCreation2((g5, h5) => {
                        If.create();
                        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((l5, m5) => {
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
                                    Divider.margin({
                                        left: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.alert_button_horizontal_space'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        right: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.alert_button_horizontal_space'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                    });
                                }, Divider);
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

    buildVerticalAlignButtons(f4 = null) {
        this.observeComponentCreation2((h4, i4) => {
            If.create();
            if (this.buttons) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w4, x4) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((n4, o4) => {
                        ForEach.create();
                        const p4 = (t4, u4) => {
                            const v4 = t4;
                            this.buildButtonWithDivider.bind(this)(this.buttons?.length === HORIZON_BUTTON_MAX_COUNT ?
                                HORIZON_BUTTON_MAX_COUNT - u4 - 1 : u4);
                        };
                        this.forEachUpdateFunction(n4, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), p4, (s4) => s4.value.toString(), true, false);
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
        if (!this.buttons || this.buttons.length === 0 || !DIALOG_DIVIDER_SHOW) {
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

    isNewPropertiesHighPriority(e4) {
        if (e4.role === ButtonRole.ERROR) {
            return true;
        }
        if (e4.buttonStyle !== undefined &&
            e4.buttonStyle !== ALERT_BUTTON_STYLE) {
            return true;
        }
        if (e4.background === undefined && e4.fontColor === undefined) {
            return true;
        }
        return false;
    }

    buildButtonWithDivider(m3, n3 = null) {
        this.observeComponentCreation2((p3, q3) => {
            If.create();
            if (this.buttons && this.buttons[m3]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c4, d4) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[m3]);
                    Row.pop();
                    this.observeComponentCreation2((v3, w3) => {
                        If.create();
                        if ((this.buttons.length === HORIZON_BUTTON_MAX_COUNT ? HORIZON_BUTTON_MAX_COUNT - m3 - 1 : m3) <
                            Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((a4, b4) => {
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

    isVerticalAlignButton(g3) {
        if (this.buttons) {
            if (this.buttons.length === 1) {
                return false;
            }
            if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
                return true;
            }
            let h3 = false;
            let i3 = vp2px(g3 / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
                BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
            this.buttons.forEach((k3) => {
                let l3 = measure.measureTextSize({
                    textContent: k3.value,
                    fontSize: this.buttonMaxFontSize
                });
                if (Number(l3.width) > i3) {
                    h3 = true;
                }
            });
            return h3;
        }
        return false;
    }

    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

function __Button__setButtonProperties(d3, e3) {
    Button.onClick(() => {
        if (d3.action) {
            d3.action();
        }
        e3?.close();
    });
    Button.defaultFocus(true);
    Button.buttonStyle(d3.buttonStyle ?? ALERT_BUTTON_STYLE);
    Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
    Button.type(ButtonType.Normal);
    Button.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.corner_radius_level10'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    });
}

function getNumberByResourceId(w2, x2, y2) {
    try {
        let c3 = resourceManager.getSystemResourceManager().getNumber(w2);
        if (c3 > 0 || y2) {
            return c3;
        } else {
            return x2;
        }
    } catch (z2) {
        let a3 = z2.code;
        let b3 = z2.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResourceId error, code: ${a3}, message: ${b3}`);
        return x2;
    }
}

function getEnumNumberByResourceId(q2, r2) {
    try {
        let v2 = getContext().resourceManager.getNumber(q2);
        if (v2 > 0) {
            return v2;
        } else {
            return r2;
        }
    } catch (s2) {
        let t2 = s2.code;
        let u2 = s2.message;
        hilog.error(0x3900, 'Ace', `getEnumNumberByResourceId error, code: ${t2}, message: ${u2}`);
        return r2;
    }
}

function getTextAlign(l2, m2, n2) {
    let o2 = measure.measureTextSize({
        textContent: m2,
        fontSize: n2,
        constraintWidth: l2,
    });
    let p2 = measure.measureTextSize({
        textContent: m2,
        fontSize: n2,
    });
    if (getTextHeight(o2) <= getTextHeight(p2)) {
        return TextAlign.Center;
    }
    return TextAlign.Start;
}

function getTextHeight(k2) {
    if (k2 && k2.height !== null && k2.height !== undefined) {
        return Number(k2.height);
    }
    return 0;
}

function resolveKeyEvent(i2, j2) {
    if (i2.type === IGNORE_KEY_EVENT_TYPE) {
        return;
    }
    if (i2.keyCode === KEYCODE_UP) {
        j2.scrollPage({ next: false });
        i2.stopPropagation();
    } else if (i2.keyCode === KEYCODE_DOWN) {
        if (j2.isAtEnd()) {
            return;
        } else {
            j2.scrollPage({ next: true });
            i2.stopPropagation();
        }
    }
}

export class LoadingDialog extends ViewPU {
    constructor(c2, d2, e2, f2 = -1, g2 = undefined, h2) {
        super(c2, e2, f2, h2);
        if (typeof g2 === 'function') {
            this.paramsGenerator_ = g2;
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
        this.setInitiallyProvidedValue(d2);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(b2) {
        if (b2.controller !== undefined) {
            this.controller = b2.controller;
        }
        if (b2.content !== undefined) {
            this.content = b2.content;
        }
        if (b2.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = b2.fontColorWithTheme;
        }
        if (b2.loadingProgressIconColorWithTheme !== undefined) {
            this.loadingProgressIconColorWithTheme = b2.loadingProgressIconColorWithTheme;
        }
        if (b2.theme !== undefined) {
            this.theme = b2.theme;
        }
        if (b2.themeColorMode !== undefined) {
            this.themeColorMode = b2.themeColorMode;
        }
        if (b2.fontSizeScale !== undefined) {
            this.fontSizeScale = b2.fontSizeScale;
        }
        if (b2.minContentHeight !== undefined) {
            this.minContentHeight = b2.minContentHeight;
        }
    }

    updateStateVars(a2) {
    }

    purgeVariableDependenciesOnElmtId(z1) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(z1);
        this.__loadingProgressIconColorWithTheme.purgeDependencyOnElmtId(z1);
        this.__fontSizeScale.purgeDependencyOnElmtId(z1);
        this.__minContentHeight.purgeDependencyOnElmtId(z1);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__loadingProgressIconColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(y1) {
        this.controller = y1;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(x1) {
        this.__fontColorWithTheme.set(x1);
    }

    get loadingProgressIconColorWithTheme() {
        return this.__loadingProgressIconColorWithTheme.get();
    }

    set loadingProgressIconColorWithTheme(w1) {
        this.__loadingProgressIconColorWithTheme.set(w1);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(v1) {
        this.__fontSizeScale.set(v1);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(u1) {
        this.__minContentHeight.set(u1);
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((s1, t1) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((q1, r1) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((k1, l1) => {
                if (l1) {
                    let m1 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, k1, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1600, col: 7 });
                    ViewPU.create(m1);
                    let n1 = () => {
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
                    m1.paramsGenerator_ = n1;
                } else {
                    this.updateStateVarsOfChildByElmtId(k1, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        Column.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    contentBuilder(u = null) {
        this.observeComponentCreation2((f1, g1) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((d1, e1) => {
            Row.create();
            Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
        }, Row);
        this.observeComponentCreation2((b1, c1) => {
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
        this.observeComponentCreation2((z, a1) => {
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
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

export class PopoverDialog extends ViewPU {
    constructor(o, p, q, r = -1, s = undefined, t) {
        super(o, q, r, t);
        if (typeof s === 'function') {
            this.paramsGenerator_ = s;
        }
        this.__visible = new SynchedPropertySimpleTwoWayPU(p.visible, this, 'visible');
        this.__popover = new SynchedPropertyObjectOneWayPU(p.popover, this, 'popover');
        this.targetBuilder = undefined;
        this.__dialogWidth = new ObservedPropertyObjectPU(this.popover?.width, this, 'dialogWidth');
        this.setInitiallyProvidedValue(p);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(n) {
        if (n.targetBuilder !== undefined) {
            this.targetBuilder = n.targetBuilder;
        }
        if (n.dialogWidth !== undefined) {
            this.dialogWidth = n.dialogWidth;
        }
    }

    updateStateVars(m) {
        this.__popover.reset(m.popover);
    }

    purgeVariableDependenciesOnElmtId(l) {
        this.__visible.purgeDependencyOnElmtId(l);
        this.__popover.purgeDependencyOnElmtId(l);
        this.__dialogWidth.purgeDependencyOnElmtId(l);
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

    set visible(k) {
        this.__visible.set(k);
    }

    get popover() {
        return this.__popover.get();
    }

    set popover(j) {
        this.__popover.set(j);
    }

    get dialogWidth() {
        return this.__dialogWidth.get();
    }

    set dialogWidth(i) {
        this.__dialogWidth.set(i);
    }

    emptyBuilder(h = null) {
    }

    aboutToAppear() {
        if (this.targetBuilder === undefined || this.targetBuilder === null) {
            this.targetBuilder = this.emptyBuilder;
        }
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((b, c) => {
            Column.create();
            Column.onClick(() => {
                let f = display.getDefaultDisplaySync();
                let g = px2vp(f.width);
                if (g - BUTTON_HORIZONTAL_MARGIN - BUTTON_HORIZONTAL_MARGIN > MAX_DIALOG_WIDTH) {
                    this.popover.width = this.popover?.width ?? MAX_DIALOG_WIDTH;
                } else {
                    this.popover.width = this.dialogWidth;
                }
                this.visible = !this.visible;
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
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

export default { TipsDialog, ConfirmDialog, SelectDialog, AlertDialog, LoadingDialog, CustomContentDialog, PopoverDialog };